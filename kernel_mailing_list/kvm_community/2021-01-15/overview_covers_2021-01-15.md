

#### [PATCH v2 0/3] Use static_call for kvm_x86_ops
##### From: Jason Baron <jbaron@akamai.com>

```c
From patchwork Fri Jan 15 03:27:53 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Baron <jbaron@akamai.com>
X-Patchwork-Id: 12021299
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-14.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A94B6C433E9
	for <kvm@archiver.kernel.org>; Fri, 15 Jan 2021 03:31:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 78FF623AFC
	for <kvm@archiver.kernel.org>; Fri, 15 Jan 2021 03:31:13 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732519AbhAODbC (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 14 Jan 2021 22:31:02 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:35630 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725950AbhAODbC (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 14 Jan 2021 22:31:02 -0500
Received: from mx0a-00190b01.pphosted.com (mx0a-00190b01.pphosted.com
 [IPv6:2620:100:9001:583::1])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 1C34AC061757;
        Thu, 14 Jan 2021 19:30:22 -0800 (PST)
Received: from pps.filterd (m0122332.ppops.net [127.0.0.1])
        by mx0a-00190b01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 10F3QZTB018319;
        Fri, 15 Jan 2021 03:30:14 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=akamai.com;
 h=from : to : cc :
 subject : date : message-id; s=jan2016.eng;
 bh=EsJzEXD057xgLTgHuE096X9huCN/rxWgiXs1QEyg+cQ=;
 b=lIY8zkl3ULhghHuuqjZVvAoLWXhv124Dbke+SwuEULytVwW04OReAJl5JxmVtz77K32e
 QvO7eNoos2Yei6itN/naiJtBLS8xBogNL9w+5MPM1Qwlg685xGLS1HTAnx0q8+DIlxs7
 xhcawYZIun4KJPHphdZEPsfbNfaIj9lj0xUCNftxjrnXaPA/AMXISK0Ib8J6xnjzIXIw
 7U7BizD+Xumoo2uPRXSQcU6oy7upB3M1aWV6r8KMWMBrXzjLBzRNkGKcSDHxIIBy7HxN
 feDZZUOwaSCo+WUlDn6FGLgrGU81mQSiGJHKHRidxV1tUxtCPHq9yo7MS8+53Wd1OfP+ OQ==
Received: from prod-mail-ppoint5 (prod-mail-ppoint5.akamai.com [184.51.33.60]
 (may be forged))
        by mx0a-00190b01.pphosted.com with ESMTP id 35y5ep43kv-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 15 Jan 2021 03:30:13 +0000
Received: from pps.filterd (prod-mail-ppoint5.akamai.com [127.0.0.1])
        by prod-mail-ppoint5.akamai.com (8.16.0.43/8.16.0.43) with SMTP id
 10F3Pqsf007085;
        Thu, 14 Jan 2021 19:30:04 -0800
Received: from prod-mail-relay10.akamai.com ([172.27.118.251])
        by prod-mail-ppoint5.akamai.com with ESMTP id 35ybbec9rw-1;
        Thu, 14 Jan 2021 19:30:04 -0800
Received: from bos-lpjec.145bw.corp.akamai.com
 (bos-lpjec.145bw.corp.akamai.com [172.28.3.71])
        by prod-mail-relay10.akamai.com (Postfix) with ESMTP id 9F445406AD;
        Fri, 15 Jan 2021 03:30:04 +0000 (GMT)
From: Jason Baron <jbaron@akamai.com>
To: pbonzini@redhat.com, seanjc@google.com
Cc: kvm@vger.kernel.org, x86@kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH v2 0/3] Use static_call for kvm_x86_ops
Date: Thu, 14 Jan 2021 22:27:53 -0500
Message-Id: <cover.1610680941.git.jbaron@akamai.com>
X-Mailer: git-send-email 2.7.4
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.343,18.0.737
 definitions=2021-01-15_01:2021-01-15,2021-01-15 signatures=0
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 phishscore=0
 malwarescore=0 mlxscore=0
 mlxlogscore=632 suspectscore=0 spamscore=0 adultscore=0 bulkscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2101150015
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.343,18.0.737
 definitions=2021-01-15_01:2021-01-15,2021-01-15 signatures=0
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 phishscore=0
 priorityscore=1501
 suspectscore=0 bulkscore=0 mlxlogscore=575 mlxscore=0 lowpriorityscore=0
 malwarescore=0 adultscore=0 impostorscore=0 spamscore=0 clxscore=1015
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2101150015
X-Agari-Authentication-Results: mx.akamai.com;
 spf=${SPFResult} (sender IP is 184.51.33.60)
 smtp.mailfrom=jbaron@akamai.com smtp.helo=prod-mail-ppoint5
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

Convert kvm_x86_ops to use static_call. Shows good performance
gains for cpuid loop micro-benchmark (results in patch 3/3).

Thanks,

-Jason


Changes from v1:
-Introduce kvm-x86-ops header with eye towards using this to define
 svm_x86_ops and vmx_x86_ops in follow on patches (Paolo, Sean)
-add new patch (1/3), that adds a vmx/svm prefix to help facilitate
 svm_x86_ops and vmx_x86_ops future conversions.
-added amd perf numbres to description of patch 3/3

Jason Baron (3):
  KVM: X86: append vmx/svm prefix to additional kvm_x86_ops functions
  KVM: x86: introduce definitions to support static calls for kvm_x86_ops
  KVM: x86: use static calls to reduce kvm_x86_ops overhead

 arch/x86/include/asm/kvm-x86-ops.h | 127 +++++++++++++++
 arch/x86/include/asm/kvm_host.h    |  21 ++-
 arch/x86/kvm/cpuid.c               |   2 +-
 arch/x86/kvm/hyperv.c              |   4 +-
 arch/x86/kvm/irq.c                 |   3 +-
 arch/x86/kvm/kvm_cache_regs.h      |  10 +-
 arch/x86/kvm/lapic.c               |  30 ++--
 arch/x86/kvm/mmu.h                 |   6 +-
 arch/x86/kvm/mmu/mmu.c             |  15 +-
 arch/x86/kvm/mmu/spte.c            |   2 +-
 arch/x86/kvm/pmu.c                 |   2 +-
 arch/x86/kvm/svm/svm.c             |  20 +--
 arch/x86/kvm/trace.h               |   4 +-
 arch/x86/kvm/vmx/nested.c          |   2 +-
 arch/x86/kvm/vmx/vmx.c             |  30 ++--
 arch/x86/kvm/vmx/vmx.h             |   2 +-
 arch/x86/kvm/x86.c                 | 307 +++++++++++++++++++------------------
 arch/x86/kvm/x86.h                 |   6 +-
 18 files changed, 369 insertions(+), 224 deletions(-)
 create mode 100644 arch/x86/include/asm/kvm-x86-ops.h
```
#### [RFC PATCH v2 00/13] virtio/vsock: introduce SOCK_SEQPACKET support.
##### From: Arseny Krasnov <arseny.krasnov@kaspersky.com>

```c
From patchwork Fri Jan 15 05:35:50 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Arseny Krasnov <arseny.krasnov@kaspersky.com>
X-Patchwork-Id: 12021473
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-19.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 06FD4C433E0
	for <kvm@archiver.kernel.org>; Fri, 15 Jan 2021 05:37:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D0700239FD
	for <kvm@archiver.kernel.org>; Fri, 15 Jan 2021 05:37:52 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731947AbhAOFhf (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 15 Jan 2021 00:37:35 -0500
Received: from mx13.kaspersky-labs.com ([91.103.66.164]:44727 "EHLO
        mx13.kaspersky-labs.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729948AbhAOFhd (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 15 Jan 2021 00:37:33 -0500
Received: from relay13.kaspersky-labs.com (unknown [127.0.0.10])
        by relay13.kaspersky-labs.com (Postfix) with ESMTP id 7B4D352116F;
        Fri, 15 Jan 2021 08:36:48 +0300 (MSK)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=kaspersky.com;
        s=mail; t=1610689008;
        bh=d1C9LPm5LAzmiTpkTjxAIHdop1GWcTlE4FAGAdIkrRM=;
        h=From:To:Subject:Date:Message-ID:MIME-Version:Content-Type;
        b=saTY2gsmg7bb7K0SHdKQNO9Tz47bAf3UBsbEAusgClnCh5ZCAXOrAAFibQKcxYqjW
         n4tK0N1J3pv8ErgrkHLlEwi61TPK7CwF7Zx5D9KQsEcynSQ4OBJCLKPOW1ABGyzbb/
         4LmcKcZwgf3rTMFWHU4fUgXV/QTXIegz22Tljp/A=
Received: from mail-hq2.kaspersky.com (unknown [91.103.66.206])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-SHA256 (128/128 bits))
        (Client CN "mail-hq2.kaspersky.com",
 Issuer "Kaspersky MailRelays CA G3" (verified OK))
        by mailhub13.kaspersky-labs.com (Postfix) with ESMTPS id 99404520ED7;
        Fri, 15 Jan 2021 08:36:47 +0300 (MSK)
Received: from arseniy-pc.avp.ru (10.64.68.128) by hqmailmbx3.avp.ru
 (10.64.67.243) with Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256_P256) id 15.1.2044.4; Fri, 15
 Jan 2021 08:36:47 +0300
From: Arseny Krasnov <arseny.krasnov@kaspersky.com>
To: Stefan Hajnoczi <stefanha@redhat.com>,
        Stefano Garzarella <sgarzare@redhat.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Jason Wang <jasowang@redhat.com>,
        "David S. Miller" <davem@davemloft.net>,
        Jakub Kicinski <kuba@kernel.org>,
        Arseny Krasnov <arseny.krasnov@kaspersky.com>,
        Colin Ian King <colin.king@canonical.com>,
        Andra Paraschiv <andraprs@amazon.com>,
        Jeff Vander Stoep <jeffv@google.com>
CC: <kvm@vger.kernel.org>, <virtualization@lists.linux-foundation.org>,
        <netdev@vger.kernel.org>, <linux-kernel@vger.kernel.org>,
        <stsp2@yandex.ru>, <oxffffaa@gmail.com>
Subject: [RFC PATCH v2 00/13] virtio/vsock: introduce SOCK_SEQPACKET support.
Date: Fri, 15 Jan 2021 08:35:50 +0300
Message-ID: <20210115053553.1454517-1-arseny.krasnov@kaspersky.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
X-Originating-IP: [10.64.68.128]
X-ClientProxiedBy: hqmailmbx2.avp.ru (10.64.67.242) To hqmailmbx3.avp.ru
 (10.64.67.243)
X-KSE-ServerInfo: hqmailmbx3.avp.ru, 9
X-KSE-AntiSpam-Interceptor-Info: scan successful
X-KSE-AntiSpam-Version: 5.9.16, Database issued on: 01/15/2021 05:18:27
X-KSE-AntiSpam-Status: KAS_STATUS_NOT_DETECTED
X-KSE-AntiSpam-Method: none
X-KSE-AntiSpam-Rate: 10
X-KSE-AntiSpam-Info: Lua profiles 161159 [Jan 15 2021]
X-KSE-AntiSpam-Info: LuaCore: 420 420 0b339e70b2b1bb108f53ec9b40aa316bba18ceea
X-KSE-AntiSpam-Info: Version: 5.9.16.0
X-KSE-AntiSpam-Info: Envelope from: arseny.krasnov@kaspersky.com
X-KSE-AntiSpam-Info: {Prob_from_in_msgid}
X-KSE-AntiSpam-Info: {Tracking_date, moscow}
X-KSE-AntiSpam-Info: {Tracking_from_domain_doesnt_match_to}
X-KSE-AntiSpam-Info: 
 arseniy-pc.avp.ru:7.1.1;kaspersky.com:7.1.1;127.0.0.199:7.1.2;d41d8cd98f00b204e9800998ecf8427e.com:7.1.1
X-KSE-AntiSpam-Info: Rate: 10
X-KSE-AntiSpam-Info: Status: not_detected
X-KSE-AntiSpam-Info: Method: none
X-KSE-Antiphishing-Info: Clean
X-KSE-Antiphishing-ScanningType: Deterministic
X-KSE-Antiphishing-Method: None
X-KSE-Antiphishing-Bases: 01/15/2021 05:21:00
X-KSE-AttachmentFiltering-Interceptor-Info: no applicable attachment filtering
 rules found
X-KSE-Antivirus-Interceptor-Info: scan successful
X-KSE-Antivirus-Info: Clean, bases: 15.01.2021 2:12:00
X-KSE-BulkMessagesFiltering-Scan-Result: InTheLimit
X-KSE-AttachmentFiltering-Interceptor-Info: no applicable attachment filtering
 rules found
X-KSE-BulkMessagesFiltering-Scan-Result: InTheLimit
X-KLMS-Rule-ID: 52
X-KLMS-Message-Action: clean
X-KLMS-AntiSpam-Status: not scanned, disabled by settings
X-KLMS-AntiSpam-Interceptor-Info: not scanned
X-KLMS-AntiPhishing: Clean, bases: 2021/01/15 05:03:00
X-KLMS-AntiVirus: Kaspersky Security for Linux Mail Server, version 8.0.3.30,
 bases: 2021/01/15 02:12:00 #16041563
X-KLMS-AntiVirus-Status: Clean, skipped
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patchset impelements support of SOCK_SEQPACKET for virtio
transport.
	As SOCK_SEQPACKET guarantees to save record boundaries, so to
do it, new packet operation was added: it marks start of record (with
record length in header), such packet doesn't carry any data.  To send
record, packet with start marker is sent first, then all data is sent
as usual 'RW' packets. On receiver's side, length of record is known
from packet with start record marker. Now as  packets of one socket
are not reordered neither on vsock nor on vhost transport layers, such
marker allows to restore original record on receiver's side. If user's
buffer is smaller that record length, when all out of size data is
dropped.
	Maximum length of datagram is not limited as in stream socket,
because same credit logic is used. Difference with stream socket is
that user is not woken up until whole record is received or error
occurred. Implementation also supports 'MSG_EOR' and 'MSG_TRUNC' flags.
	Tests also implemented.

 Arseny Krasnov (13):
  af_vsock: implement 'vsock_wait_data()'.
  af_vsock: separate rx loops for STREAM/SEQPACKET.
  af_vsock: implement rx loops entry point
  af_vsock: replace previous stream rx loop.
  af_vsock: implement send logic for SOCK_SEQPACKET
  af_vsock: general support of SOCK_SEQPACKET type.
  af_vsock: update comments for stream sockets.
  virtio/vsock: dequeue callback for SOCK_SEQPACKET.
  virtio/vsock: implement fetch of record length
  virtio/vsock: update receive logic
  virtio/vsock: rest of SOCK_SEQPACKET support
  vhost/vsock: support for SOCK_SEQPACKET socket.
  vsock_test: add SOCK_SEQPACKET tests.

 drivers/vhost/vsock.c                   |   7 +-
 include/linux/virtio_vsock.h            |  12 +
 include/net/af_vsock.h                  |   6 +
 include/uapi/linux/virtio_vsock.h       |   9 +
 net/vmw_vsock/af_vsock.c                | 483 ++++++++++++++++------
 net/vmw_vsock/virtio_transport.c        |   4 +
 net/vmw_vsock/virtio_transport_common.c | 294 +++++++++++--
 tools/testing/vsock/util.c              |  32 +-
 tools/testing/vsock/util.h              |   3 +
 tools/testing/vsock/vsock_test.c        | 126 ++++++
 10 files changed, 824 insertions(+), 152 deletions(-)

 v1 -> v2:
 - patches reordered: af_vsock.c changes now before virtio vsock
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
#### [PATCH v2 0/2] vfio/iommu_type1: some fixes
##### From: Keqian Zhu <zhukeqian1@huawei.com>

```c
From patchwork Fri Jan 15 09:26:41 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Keqian Zhu <zhukeqian1@huawei.com>
X-Patchwork-Id: 12022007
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B4B1CC433E0
	for <kvm@archiver.kernel.org>; Fri, 15 Jan 2021 09:28:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 707D523403
	for <kvm@archiver.kernel.org>; Fri, 15 Jan 2021 09:28:28 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730556AbhAOJ1z (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 15 Jan 2021 04:27:55 -0500
Received: from szxga07-in.huawei.com ([45.249.212.35]:11393 "EHLO
        szxga07-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1730543AbhAOJ1w (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 15 Jan 2021 04:27:52 -0500
Received: from DGGEMS411-HUB.china.huawei.com (unknown [172.30.72.59])
        by szxga07-in.huawei.com (SkyGuard) with ESMTP id 4DHG5D1fXyz7Vlk;
        Fri, 15 Jan 2021 17:26:08 +0800 (CST)
Received: from DESKTOP-5IS4806.china.huawei.com (10.174.184.42) by
 DGGEMS411-HUB.china.huawei.com (10.3.19.211) with Microsoft SMTP Server id
 14.3.498.0; Fri, 15 Jan 2021 17:27:02 +0800
From: Keqian Zhu <zhukeqian1@huawei.com>
To: <linux-kernel@vger.kernel.org>,
        <linux-arm-kernel@lists.infradead.org>,
        <iommu@lists.linux-foundation.org>, <kvm@vger.kernel.org>,
        <kvmarm@lists.cs.columbia.edu>,
        Alex Williamson <alex.williamson@redhat.com>,
        Kirti Wankhede <kwankhede@nvidia.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Will Deacon <will@kernel.org>, Marc Zyngier <maz@kernel.org>,
        Catalin Marinas <catalin.marinas@arm.com>
CC: Mark Rutland <mark.rutland@arm.com>,
        James Morse <james.morse@arm.com>,
        Robin Murphy <robin.murphy@arm.com>,
        Joerg Roedel <joro@8bytes.org>,
        "Daniel Lezcano" <daniel.lezcano@linaro.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Andrew Morton <akpm@linux-foundation.org>,
        Alexios Zavras <alexios.zavras@intel.com>,
        <wanghaibin.wang@huawei.com>, <jiangkunkun@huawei.com>
Subject: [PATCH v2 0/2] vfio/iommu_type1: some fixes
Date: Fri, 15 Jan 2021 17:26:41 +0800
Message-ID: <20210115092643.728-1-zhukeqian1@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.184.42]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

changelog:

v2:
 - Address suggestions from Alex.
 - Remove unnecessary patches.

Keqian Zhu (2):
  vfio/iommu_type1: Populate full dirty when detach non-pinned group
  vfio/iommu_type1: Sanity check pfn_list when remove vfio_dma

 drivers/vfio/vfio_iommu_type1.c | 42 +++++++++++++++++----------------
 1 file changed, 22 insertions(+), 20 deletions(-)
```
#### [RESEND PATCH v2 0/2] vfio/iommu_type1: some fixes
##### From: Keqian Zhu <zhukeqian1@huawei.com>

```c
From patchwork Fri Jan 15 10:13:19 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Keqian Zhu <zhukeqian1@huawei.com>
X-Patchwork-Id: 12022153
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=unavailable autolearn_force=no
 version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 2F457C433E0
	for <kvm@archiver.kernel.org>; Fri, 15 Jan 2021 10:15:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D1C36221FA
	for <kvm@archiver.kernel.org>; Fri, 15 Jan 2021 10:15:08 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728890AbhAOKOf (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 15 Jan 2021 05:14:35 -0500
Received: from szxga04-in.huawei.com ([45.249.212.190]:10661 "EHLO
        szxga04-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728260AbhAOKOf (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 15 Jan 2021 05:14:35 -0500
Received: from DGGEMS413-HUB.china.huawei.com (unknown [172.30.72.60])
        by szxga04-in.huawei.com (SkyGuard) with ESMTP id 4DHH744pPGz15tPQ;
        Fri, 15 Jan 2021 18:12:48 +0800 (CST)
Received: from DESKTOP-5IS4806.china.huawei.com (10.174.184.42) by
 DGGEMS413-HUB.china.huawei.com (10.3.19.213) with Microsoft SMTP Server id
 14.3.498.0; Fri, 15 Jan 2021 18:13:40 +0800
From: Keqian Zhu <zhukeqian1@huawei.com>
To: <linux-kernel@vger.kernel.org>,
        <linux-arm-kernel@lists.infradead.org>,
        <iommu@lists.linux-foundation.org>, <kvm@vger.kernel.org>,
        <kvmarm@lists.cs.columbia.edu>,
        Alex Williamson <alex.williamson@redhat.com>,
        Kirti Wankhede <kwankhede@nvidia.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Will Deacon <will@kernel.org>, Marc Zyngier <maz@kernel.org>,
        Catalin Marinas <catalin.marinas@arm.com>
CC: Mark Rutland <mark.rutland@arm.com>,
        James Morse <james.morse@arm.com>,
        Robin Murphy <robin.murphy@arm.com>,
        Joerg Roedel <joro@8bytes.org>,
        "Daniel Lezcano" <daniel.lezcano@linaro.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Andrew Morton <akpm@linux-foundation.org>,
        Alexios Zavras <alexios.zavras@intel.com>,
        <wanghaibin.wang@huawei.com>, <jiangkunkun@huawei.com>
Subject: [RESEND PATCH v2 0/2] vfio/iommu_type1: some fixes
Date: Fri, 15 Jan 2021 18:13:19 +0800
Message-ID: <20210115101321.12084-1-zhukeqian1@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.184.42]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

changelog:

v2:
 - Address suggestions from Alex.
 - Remove unnecessary patches.

Keqian Zhu (2):
  vfio/iommu_type1: Populate full dirty when detach non-pinned group
  vfio/iommu_type1: Sanity check pfn_list when remove vfio_dma

 drivers/vfio/vfio_iommu_type1.c | 42 +++++++++++++++++----------------
 1 file changed, 22 insertions(+), 20 deletions(-)
```
#### [PATCH v16 00/17] KVM RISC-V Support
##### From: Anup Patel <anup.patel@wdc.com>

```c
From patchwork Fri Jan 15 12:18:29 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Anup Patel <Anup.Patel@wdc.com>
X-Patchwork-Id: 12022439
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B5254C433E6
	for <kvm@archiver.kernel.org>; Fri, 15 Jan 2021 12:20:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 73A8523888
	for <kvm@archiver.kernel.org>; Fri, 15 Jan 2021 12:20:42 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729050AbhAOMU0 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 15 Jan 2021 07:20:26 -0500
Received: from esa4.hgst.iphmx.com ([216.71.154.42]:38938 "EHLO
        esa4.hgst.iphmx.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726286AbhAOMUZ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 15 Jan 2021 07:20:25 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=simple/simple;
  d=wdc.com; i=@wdc.com; q=dns/txt; s=dkim.wdc.com;
  t=1610713223; x=1642249223;
  h=from:to:cc:subject:date:message-id:
   content-transfer-encoding:mime-version;
  bh=HjHYj/CfkWaO17JqLvpm9Iqvbr2hzJ+ymedApuQUNNc=;
  b=hVHA9HbkGPrMRoy65FOjqJe1wXPxE2eAV8q0f8CJsx0SF0YktFViR9GF
   36dOsZjt8z+txFWKdxkvPYGL8oiiO9oAFpMr4BIOm4nrFKFCEH/KQgToa
   TtiN0qUfw8gJJj0FK6UJ6KHVnum6ANACxobUPfySovEHx/+U5pR70turs
   vYoLB2uzG27mVNO+UL5UqHOTbpJxIWSiWCSTAI7fo2DF8I0k0Yf6UuIF1
   S8uoQsDPew95RAO1Fylpd7cCrhTxMWKZVddaf9ODxZQhRu/qP9qnOvkm0
   u8G/LzD9cXtd6b1fs3uyK5WHlltnnkp0S8OzOQQfRXEd0qVxXJ+VSoyGQ
   Q==;
IronPort-SDR: 
 /XyA3GEDkMTOt5D+KzVKwuPg+om8Amcc28PrUVJsbMrLxW5/bZrNeq9VJ1i4v58srICFC8YyFN
 yn8ugU6x+3y0inFKDDu77loaJIYB+ZBRzW5pv9QdYi0/rKJ42WRsmweIPPH8lfdKE27FZ3n13W
 Qx5hXf8q+wclh0VaouLIvQnzMrL+AGn8/biNokRZMDy8kqUIfWk5xSCQfOeiEksuu0h+H9Y+s5
 5DrPDQnguw2mLCVnm411GKFbLKMZHHvpdO/E4r9w6Pvr2Wg6r2rGEkd1OFksn90VqlrrV5axni
 QPs=
X-IronPort-AV: E=Sophos;i="5.79,349,1602518400";
   d="scan'208";a="157514079"
Received: from mail-bl2nam02lp2059.outbound.protection.outlook.com (HELO
 NAM02-BL2-obe.outbound.protection.outlook.com) ([104.47.38.59])
  by ob1.hgst.iphmx.com with ESMTP; 15 Jan 2021 20:19:16 +0800
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=k+56vsZudHwVg6XEIvDOnq4Hxvvo8121wFgBUbGdTpE5Jn3kIhCB6aMaK1t2ndDznjd99DmBbUvQZqffJ0MJpYRYQ3EWK/6Zq5yfcKGDtz8rTPZNr3yJPpldfWFWKDTSSNK3G5VzYZFBMo0VqxFeu+s9NB1ztixXdGUfO7rR24KydBZZOJLeK2fbhF/UFGXUvi2lNuakwMaGRDltV38m3qjRbtBxlz2sMp+N/uwr74kBJuglE4TyQgw4SRT6jlJycdrYi/roY+pf8ntVA6Ky/TNnJloXeK92yiFgz6ddmo6PLugI2XnB5wLbVtyCu+/ckQfOQ5zV2ts+Kd72D2K9cg==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=WIxsMC+QcX1LOJwShuzcQ7uhebKVAfzVAKr7gO2Y6no=;
 b=KLZbENrJBrIjsqDjV7n3kXjB0WawFfbZgdn/y/rlRamS56qAMizm1VgjiGoePjo+Zygq5XHDO67rwd7MQ4kXVwU2wsQ+CmHaRml1meTyixE1FzdSqlEcw24EtJqoFk5GR581rviQkiMi/UUZUtWZcChZgiJDnpsqWsY/hO/pxxfkK460Kb9PBxUXVpKFDrsef4DlMxi5MqV9OwK8JG7EM2wg1VOJwN0FeDIQMs5F24WNnkmioIMnZ/V6/+Pab5PzJNg/khDySrxANYYmaHl7SN+0ClHdFH55UM1O5zOOehSAN//Z7mIzo892y79gWWmt2SgydszATiZvN0IMXsJNdQ==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=wdc.com; dmarc=pass action=none header.from=wdc.com; dkim=pass
 header.d=wdc.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=sharedspace.onmicrosoft.com; s=selector2-sharedspace-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=WIxsMC+QcX1LOJwShuzcQ7uhebKVAfzVAKr7gO2Y6no=;
 b=gz7IbC04bdrfbTKRp39gRoyIZQzpyY2kR+1Fj6WEtDC2qGG4CpVC6cA4EdQm3X2x5JJoCEhvVx05a10yAWzgpxKiHaW/8djgYmH6WtbAGASyyhV36jHgz4qNSeP6N4+16bX3PqZ5laJx0zTkPuLF0QWFinywm2NaXdK1YLy4EBc=
Authentication-Results: dabbelt.com; dkim=none (message not signed)
 header.d=none;dabbelt.com; dmarc=none action=none header.from=wdc.com;
Received: from DM6PR04MB6201.namprd04.prod.outlook.com (2603:10b6:5:127::32)
 by DM5PR04MB3769.namprd04.prod.outlook.com (2603:10b6:3:fc::13) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3763.10; Fri, 15 Jan
 2021 12:19:14 +0000
Received: from DM6PR04MB6201.namprd04.prod.outlook.com
 ([fe80::2513:b200:bdc8:b97]) by DM6PR04MB6201.namprd04.prod.outlook.com
 ([fe80::2513:b200:bdc8:b97%5]) with mapi id 15.20.3742.012; Fri, 15 Jan 2021
 12:19:14 +0000
From: Anup Patel <anup.patel@wdc.com>
To: Palmer Dabbelt <palmer@dabbelt.com>,
        Palmer Dabbelt <palmerdabbelt@google.com>,
        Paul Walmsley <paul.walmsley@sifive.com>,
        Albert Ou <aou@eecs.berkeley.edu>,
        Paolo Bonzini <pbonzini@redhat.com>
Cc: Alexander Graf <graf@amazon.com>,
        Atish Patra <atish.patra@wdc.com>,
        Alistair Francis <Alistair.Francis@wdc.com>,
        Damien Le Moal <damien.lemoal@wdc.com>,
        Anup Patel <anup@brainfault.org>, kvm@vger.kernel.org,
        kvm-riscv@lists.infradead.org, linux-riscv@lists.infradead.org,
        linux-kernel@vger.kernel.org, Anup Patel <anup.patel@wdc.com>
Subject: [PATCH v16 00/17] KVM RISC-V Support
Date: Fri, 15 Jan 2021 17:48:29 +0530
Message-Id: <20210115121846.114528-1-anup.patel@wdc.com>
X-Mailer: git-send-email 2.25.1
X-Originating-IP: [122.167.152.18]
X-ClientProxiedBy: MAXPR0101CA0024.INDPRD01.PROD.OUTLOOK.COM
 (2603:1096:a00:c::34) To DM6PR04MB6201.namprd04.prod.outlook.com
 (2603:10b6:5:127::32)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from wdc.com (122.167.152.18) by
 MAXPR0101CA0024.INDPRD01.PROD.OUTLOOK.COM (2603:1096:a00:c::34) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3763.10 via Frontend
 Transport; Fri, 15 Jan 2021 12:19:10 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 5515c33b-2d33-48af-2cc8-08d8b94fc5cb
X-MS-TrafficTypeDiagnostic: DM5PR04MB3769:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM5PR04MB376961C27076E771238CF9AF8DA70@DM5PR04MB3769.namprd04.prod.outlook.com>
WDCIPOUTBOUND: EOP-TRUE
X-MS-Oob-TLC-OOBClassifiers: OLM:79;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 /5YPMhCE4/2CKXqB2VTDRvwMht2mh1DiUVPW8TtFozzUugA6H6ufFwexwwJ/xiyxHpE9+3y2OBttW2I+fiDFWAPE/Aqu7X3shXXCF6ZQ2Tg9OMjizQuiGHtzAuHnlilIymdrFi2Jd3dIIHozIqVAYAUv332zmLqen9zaE63O+VJPwBi7SvSGFOSKRivHcfppBSF1zxwdn9MIvjFkBhse0PbxZmuHXyF8AsTVwsHezf05EsRP9TeRk++xjkGybG8QHRZaQqMryOkow0fN3DvwI071DogIqYEo78cAd8PXgOMmE+wX7yprvWsFsnNku3eE5L26Rc8fJsFam5VUJI5QzFuj9PP0gVuPoirIY4Rgw0muJIgDb8sYtB0hPTR0WLLdWo4rU7K+N5xIiy1cSxnasVS/qA0jeWBOeah0BaNU1embj1V2w+uydasnk6CN+rv1zKg3p99AFhA4NMXYGURDXSSoZTAaNvcs1mz+k8dj0NiRUsu2Vn4pYFAm6l7ukxFAlnspbzFEQJ6+pFuD8znaLQ==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM6PR04MB6201.namprd04.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(39860400002)(346002)(136003)(366004)(376002)(396003)(66476007)(6666004)(55016002)(7696005)(54906003)(66946007)(110136005)(956004)(5660300002)(2616005)(186003)(52116002)(44832011)(478600001)(66556008)(8936002)(26005)(86362001)(2906002)(83380400001)(966005)(7416002)(30864003)(16526019)(8676002)(316002)(4326008)(36756003)(8886007)(1076003)(42580500001);DIR:OUT;SFP:1102;
X-MS-Exchange-AntiSpam-MessageData: 
 aHDKcv9JeDh/0OjKEGm7JDLCIdZHg8Iv/DbdRTumGiamYZQHGVx9TFdxaWaTyaD2oUq8r0DTk1wGmuGT5ENJlQGHXEyKlwcRf/tZK+JyH9xKQmh1xLSlWsaPk1FORXcG8M5ITHcFf9+ImaXPmh5GCflGrb0xSVEcw+WP9NpRAruf8u5lUd+vGGiBZri6yGV9Euxw6i3Eh7r0f8G3MWC8GMlVChC/dS9T08pyK/MsSJTWoVImzD4yhCQaGs65802RjMEGPnCaxPHN6KXXiCjvTNA3Hgxyv1T7qcLXD7vPM7jHdwlp+CON1c/32P/Utem3xWekSeEElHLCF9/y6M1efirmCRsoRPH7OqQMoOXtbOSVW9n9BVtYPco6uJbRq9p557x0w3FpHw0hPuGnDgjq18PqsldDWfC7U5s63J18oTBSg73K/jkBIwPRO1if0t2bBreVgqYrhA6BX2ZOo4R/6EANVl7U9DQOqgubp3/vEmdVsMAmPDz450wSWrTnL3+7nRGXcgdjRLcVD/vg5bYNPLUM2olhZMMjEqX/dMj7kIQOzw5AaNNMoUNP7mU1kCgDyZ9YuWD95Ipl4FRLObilqS0uBu62qZy4y96GWzxju08ynbYhNbMkswoOa335mRn0RUvJS83OB3Psr1WhQJoFgytHXMHJnnDDl5V7qtJZbr78QmZvjbZbGz/ojTkCLGl2VZec8b6pGLMjlZ7xJiApyKbKu64bid1S5+09zfzKK1j7Nu4yZyZQFdUy+QiZeVMu7//wVUpUiZz0klG/yHOMxoxFuJ/B6i0OGiawu4BwjfOuzouMZl4ZvWldayhZZoc+yDLvZEtBvmaG2Gaw5g220sz3jBIcMti0DMZmmT+E4g+Eq9Bh4wV6TRzoiDOydrZEA3pC5EiWiknywkwJSntMPo2HInvI4YaqOSCzLTDZsfSilAf83Dv2IwmNXHB9fh21ByQUt2pwNf0Wky25FwliMlk2evFJNaKWbvE89TZhM3wytBHmgCkJHanl1fMKw6vJ
X-OriginatorOrg: wdc.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 5515c33b-2d33-48af-2cc8-08d8b94fc5cb
X-MS-Exchange-CrossTenant-AuthSource: DM6PR04MB6201.namprd04.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 15 Jan 2021 12:19:14.7205
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: b61c8803-16f3-4c35-9b17-6f65f441df86
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 TrtqYvltyH+AVakmOzWBYG4RQ1/PDEo/cwqfI9/TtO6Syg0tgzbZreLhAqj8y33TMXfaRtG67oVtRecLC6aleg==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM5PR04MB3769
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series adds initial KVM RISC-V support. Currently, we are able to boot
Linux on RV64/RV32 Guest with multiple VCPUs.

Key aspects of KVM RISC-V added by this series are:
1. No RISC-V specific KVM IOCTL
2. Minimal possible KVM world-switch which touches only GPRs and few CSRs
3. Both RV64 and RV32 host supported
4. Full Guest/VM switch is done via vcpu_get/vcpu_put infrastructure
5. KVM ONE_REG interface for VCPU register access from user-space
6. PLIC emulation is done in user-space
7. Timer and IPI emuation is done in-kernel
8. Both Sv39x4 and Sv48x4 supported for RV64 host
9. MMU notifiers supported
10. Generic dirtylog supported
11. FP lazy save/restore supported
12. SBI v0.1 emulation for KVM Guest available
13. Forward unhandled SBI calls to KVM userspace
14. Hugepage support for Guest/VM
15. IOEVENTFD support for Vhost

Here's a brief TODO list which we will work upon after this series:
1. SBI v0.2 emulation in-kernel
2. SBI v0.2 hart state management emulation in-kernel
3. In-kernel PLIC emulation
4. ..... and more .....

This series can be found in riscv_kvm_v16 branch at:
https//github.com/avpatel/linux.git

Our work-in-progress KVMTOOL RISC-V port can be found in riscv_v6 branch
at: https//github.com/avpatel/kvmtool.git

The QEMU RISC-V hypervisor emulation is done by Alistair and is available
in master branch at: https://git.qemu.org/git/qemu.git

To play around with KVM RISC-V, refer KVM RISC-V wiki at:
https://github.com/kvm-riscv/howto/wiki
https://github.com/kvm-riscv/howto/wiki/KVM-RISCV64-on-QEMU
https://github.com/kvm-riscv/howto/wiki/KVM-RISCV64-on-Spike

Changes since v15:
 - Rebased on Linux-5.11-rc3
 - Fixed kvm_stage2_map() to use gfn_to_pfn_prot() for determing
   writeability of a host pfn.
 - Use "__u64" in-place of "u64" and "__u32" in-place of "u32" for
   uapi/asm/kvm.h

Changes since v14:
 - Rebased on Linux-5.10-rc3
 - Fixed Stage2 (G-stage) PDG allocation to ensure it is 16KB aligned

Changes since v13:
 - Rebased on Linux-5.9-rc3
 - Fixed kvm_riscv_vcpu_set_reg_csr() for SIP updation in PATCH5
 - Fixed instruction length computation in PATCH7
 - Added ioeventfd support in PATCH7
 - Ensure HSTATUS.SPVP is set to correct value before using HLV/HSV
   intructions in PATCH7
 - Fixed stage2_map_page() to set PTE 'A' and 'D' bits correctly
   in PATCH10
 - Added stage2 dirty page logging in PATCH10
 - Allow KVM user-space to SET/GET SCOUNTER CSR in PATCH5
 - Save/restore SCOUNTEREN in PATCH6
 - Reduced quite a few instructions for __kvm_riscv_switch_to() by
   using CSR swap instruction in PATCH6
 - Detect and use Sv48x4 when available in PATCH10

Changes since v12:
 - Rebased patches on Linux-5.8-rc4
 - By default enable all counters in HCOUNTEREN
 - RISC-V H-Extension v0.6.1 spec support

Changes since v11:
 - Rebased patches on Linux-5.7-rc3
 - Fixed typo in typecast of stage2_map_size define
 - Introduced struct kvm_cpu_trap to represent trap details and
   use it as function parameter wherever applicable
 - Pass memslot to kvm_riscv_stage2_map() for supporing dirty page
   logging in future
 - RISC-V H-Extension v0.6 spec support
 - Send-out first three patches as separate series so that it can
   be taken by Palmer for Linux RISC-V

Changes since v10:
 - Rebased patches on Linux-5.6-rc5
 - Reduce RISCV_ISA_EXT_MAX from 256 to 64
 - Separate PATCH for removing N-extension related defines
 - Added comments as requested by Palmer
 - Fixed HIDELEG CSR programming

Changes since v9:
 - Rebased patches on Linux-5.5-rc3
 - Squash PATCH19 and PATCH20 into PATCH5
 - Squash PATCH18 into PATCH11
 - Squash PATCH17 into PATCH16
 - Added ONE_REG interface for VCPU timer in PATCH13
 - Use HTIMEDELTA for VCPU timer in PATCH13
 - Updated KVM RISC-V mailing list in MAINTAINERS entry
 - Update KVM kconfig option to depend on RISCV_SBI and MMU
 - Check for SBI v0.2 and SBI v0.2 RFENCE extension at boot-time
 - Use SBI v0.2 RFENCE extension in VMID implementation
 - Use SBI v0.2 RFENCE extension in Stage2 MMU implementation
 - Use SBI v0.2 RFENCE extension in SBI implementation
 - Moved to RISC-V Hypervisor v0.5 draft spec
 - Updated Documentation/virt/kvm/api.txt for timer ONE_REG interface

Changes since v8:
 - Rebased series on Linux-5.4-rc3 and Atish's SBI v0.2 patches
 - Use HRTIMER_MODE_REL instead of HRTIMER_MODE_ABS in timer emulation
 - Fixed kvm_riscv_stage2_map() to handle hugepages
 - Added patch to forward unhandled SBI calls to user-space
 - Added patch for iterative/recursive stage2 page table programming
 - Added patch to remove per-CPU vsip_shadow variable
 - Added patch to fix race-condition in kvm_riscv_vcpu_sync_interrupts()

Changes since v7:
 - Rebased series on Linux-5.4-rc1 and Atish's SBI v0.2 patches
 - Removed PATCH1, PATCH3, and PATCH20 because these already merged
 - Use kernel doc style comments for ISA bitmap functions
 - Don't parse X, Y, and Z extension in riscv_fill_hwcap() because it will
   be added in-future
 - Mark KVM RISC-V kconfig option as EXPERIMENTAL
 - Typo fix in commit description of PATCH6 of v7 series
 - Use separate structs for CORE and CSR registers of ONE_REG interface
 - Explicitly include asm/sbi.h in kvm/vcpu_sbi.c
 - Removed implicit switch-case fall-through in kvm_riscv_vcpu_exit()
 - No need to set VSSTATUS.MXR bit in kvm_riscv_vcpu_unpriv_read()
 - Removed register for instruction length in kvm_riscv_vcpu_unpriv_read()
 - Added defines for checking/decoding instruction length
 - Added separate patch to forward unhandled SBI calls to userspace tool

Changes since v6:
 - Rebased patches on Linux-5.3-rc7
 - Added "return_handled" in struct kvm_mmio_decode to ensure that
   kvm_riscv_vcpu_mmio_return() updates SEPC only once
 - Removed trap_stval parameter from kvm_riscv_vcpu_unpriv_read()
 - Updated git repo URL in MAINTAINERS entry

Changes since v5:
 - Renamed KVM_REG_RISCV_CONFIG_TIMEBASE register to
   KVM_REG_RISCV_CONFIG_TBFREQ register in ONE_REG interface
 - Update SPEC in kvm_riscv_vcpu_mmio_return() for MMIO exits
 - Use switch case instead of illegal instruction opcode table for simplicity
 - Improve comments in stage2_remote_tlb_flush() for a potential remote TLB
  flush optimization
 - Handle all unsupported SBI calls in default case of
   kvm_riscv_vcpu_sbi_ecall() function
 - Fixed kvm_riscv_vcpu_sync_interrupts() for software interrupts
 - Improved unprivilege reads to handle traps due to Guest stage1 page table
 - Added separate patch to document RISC-V specific things in
   Documentation/virt/kvm/api.txt

Changes since v4:
 - Rebased patches on Linux-5.3-rc5
 - Added Paolo's Acked-by and Reviewed-by
 - Updated mailing list in MAINTAINERS entry

Changes since v3:
 - Moved patch for ISA bitmap from KVM prep series to this series
 - Make vsip_shadow as run-time percpu variable instead of compile-time
 - Flush Guest TLBs on all Host CPUs whenever we run-out of VMIDs

Changes since v2:
 - Removed references of KVM_REQ_IRQ_PENDING from all patches
 - Use kvm->srcu within in-kernel KVM run loop
 - Added percpu vsip_shadow to track last value programmed in VSIP CSR
 - Added comments about irqs_pending and irqs_pending_mask
 - Used kvm_arch_vcpu_runnable() in-place-of kvm_riscv_vcpu_has_interrupt()
   in system_opcode_insn()
 - Removed unwanted smp_wmb() in kvm_riscv_stage2_vmid_update()
 - Use kvm_flush_remote_tlbs() in kvm_riscv_stage2_vmid_update()
 - Use READ_ONCE() in kvm_riscv_stage2_update_hgatp() for vmid

Changes since v1:
 - Fixed compile errors in building KVM RISC-V as module
 - Removed unused kvm_riscv_halt_guest() and kvm_riscv_resume_guest()
 - Set KVM_CAP_SYNC_MMU capability only after MMU notifiers are implemented
 - Made vmid_version as unsigned long instead of atomic
 - Renamed KVM_REQ_UPDATE_PGTBL to KVM_REQ_UPDATE_HGATP
 - Renamed kvm_riscv_stage2_update_pgtbl() to kvm_riscv_stage2_update_hgatp()
 - Configure HIDELEG and HEDELEG in kvm_arch_hardware_enable()
 - Updated ONE_REG interface for CSR access to user-space
 - Removed irqs_pending_lock and use atomic bitops instead
 - Added separate patch for FP ONE_REG interface
 - Added separate patch for updating MAINTAINERS file

Anup Patel (13):
  RISC-V: Add hypervisor extension related CSR defines
  RISC-V: Add initial skeletal KVM support
  RISC-V: KVM: Implement VCPU create, init and destroy functions
  RISC-V: KVM: Implement VCPU interrupts and requests handling
  RISC-V: KVM: Implement KVM_GET_ONE_REG/KVM_SET_ONE_REG ioctls
  RISC-V: KVM: Implement VCPU world-switch
  RISC-V: KVM: Handle MMIO exits for VCPU
  RISC-V: KVM: Handle WFI exits for VCPU
  RISC-V: KVM: Implement VMID allocator
  RISC-V: KVM: Implement stage2 page table programming
  RISC-V: KVM: Implement MMU notifiers
  RISC-V: KVM: Document RISC-V specific parts of KVM API
  RISC-V: KVM: Add MAINTAINERS entry

Atish Patra (4):
  RISC-V: KVM: Add timer functionality
  RISC-V: KVM: FP lazy save/restore
  RISC-V: KVM: Implement ONE REG interface for FP registers
  RISC-V: KVM: Add SBI v0.1 support

 Documentation/virt/kvm/api.rst          |  193 ++++-
 MAINTAINERS                             |   11 +
 arch/riscv/Kconfig                      |    1 +
 arch/riscv/Makefile                     |    2 +
 arch/riscv/include/asm/csr.h            |   89 ++
 arch/riscv/include/asm/kvm_host.h       |  278 +++++++
 arch/riscv/include/asm/kvm_types.h      |    7 +
 arch/riscv/include/asm/kvm_vcpu_timer.h |   44 +
 arch/riscv/include/asm/pgtable-bits.h   |    1 +
 arch/riscv/include/uapi/asm/kvm.h       |  128 +++
 arch/riscv/kernel/asm-offsets.c         |  156 ++++
 arch/riscv/kvm/Kconfig                  |   36 +
 arch/riscv/kvm/Makefile                 |   15 +
 arch/riscv/kvm/main.c                   |  118 +++
 arch/riscv/kvm/mmu.c                    |  860 +++++++++++++++++++
 arch/riscv/kvm/tlb.S                    |   74 ++
 arch/riscv/kvm/vcpu.c                   | 1012 +++++++++++++++++++++++
 arch/riscv/kvm/vcpu_exit.c              |  701 ++++++++++++++++
 arch/riscv/kvm/vcpu_sbi.c               |  173 ++++
 arch/riscv/kvm/vcpu_switch.S            |  400 +++++++++
 arch/riscv/kvm/vcpu_timer.c             |  225 +++++
 arch/riscv/kvm/vm.c                     |   81 ++
 arch/riscv/kvm/vmid.c                   |  120 +++
 drivers/clocksource/timer-riscv.c       |    8 +
 include/clocksource/timer-riscv.h       |   16 +
 include/uapi/linux/kvm.h                |    8 +
 26 files changed, 4748 insertions(+), 9 deletions(-)
 create mode 100644 arch/riscv/include/asm/kvm_host.h
 create mode 100644 arch/riscv/include/asm/kvm_types.h
 create mode 100644 arch/riscv/include/asm/kvm_vcpu_timer.h
 create mode 100644 arch/riscv/include/uapi/asm/kvm.h
 create mode 100644 arch/riscv/kvm/Kconfig
 create mode 100644 arch/riscv/kvm/Makefile
 create mode 100644 arch/riscv/kvm/main.c
 create mode 100644 arch/riscv/kvm/mmu.c
 create mode 100644 arch/riscv/kvm/tlb.S
 create mode 100644 arch/riscv/kvm/vcpu.c
 create mode 100644 arch/riscv/kvm/vcpu_exit.c
 create mode 100644 arch/riscv/kvm/vcpu_sbi.c
 create mode 100644 arch/riscv/kvm/vcpu_switch.S
 create mode 100644 arch/riscv/kvm/vcpu_timer.c
 create mode 100644 arch/riscv/kvm/vm.c
 create mode 100644 arch/riscv/kvm/vmid.c
 create mode 100644 include/clocksource/timer-riscv.h
```
#### [PATCH v6 0/8] KVMTOOL RISC-V Support
##### From: Anup Patel <anup.patel@wdc.com>

```c
From patchwork Fri Jan 15 12:21:52 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Anup Patel <Anup.Patel@wdc.com>
X-Patchwork-Id: 12022489
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 90A2CC433E6
	for <kvm@archiver.kernel.org>; Fri, 15 Jan 2021 12:23:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 663392256F
	for <kvm@archiver.kernel.org>; Fri, 15 Jan 2021 12:23:45 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729053AbhAOMXg (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 15 Jan 2021 07:23:36 -0500
Received: from esa6.hgst.iphmx.com ([216.71.154.45]:48743 "EHLO
        esa6.hgst.iphmx.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727357AbhAOMXf (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 15 Jan 2021 07:23:35 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=simple/simple;
  d=wdc.com; i=@wdc.com; q=dns/txt; s=dkim.wdc.com;
  t=1610713414; x=1642249414;
  h=from:to:cc:subject:date:message-id:
   content-transfer-encoding:mime-version;
  bh=pYSeM6HCZ1tEDHzJmPc7xFWn3Pwv/Js36rYOgKihgZI=;
  b=hMB1NXkb1zwX31cYDGlaSUaM0XfG6Ya6cq8cfh8RTcEW6H9/nwanU1nC
   jZfx235sCdtGDSUiaL9iJAT9F+L8lN4nbgwN/Hb0dFx8S7y/qZ3jSFU5l
   qfKe/WV74QgRNMzawe8LW0cKAmo3wizbspLgHv5bTGJVPyA4E6g3wSN/u
   oa/P7tI5ly4f6hp49lrZUyNkQJvUuw63ikhsKgGZpjMQiJcO1CI2ZPtuX
   TtnORhf9rC+sUsex5S5rTyc9HK/7MUx63opQXif5S0i2z+P0Tm+3DRGI5
   PXzC8MzT4DpdgYvk1r0ueDaHSB3EJSOuCPL2wUbfyoei6d3WXuOOskynD
   A==;
IronPort-SDR: 
 IPaoweSqlXKTeaZSZhBmm67U6DVbldooeJ89aK52mrPkIs1QnTGXmW5Rm60tarygLa/d81iv83
 HNLofWQ+9FOdmYekpJq8zofh4NIgcgx61sSWMZju9znBlhgWAdnqffX+TJ4K9uBwLwSi82mvTk
 O/q4RwM8cBhR/T3kJLooM01pPEMaO+Rly6h3GQV4Smp9on976ynP1d8VfGIe6kAokS49ztYuBX
 n0cKVhZCcjnyWdnueqI97+dKScSe/9/n4aXDOCE+LqlDvkZ0RJw6Nr8ojI2uA2zlfsyzhfIOs4
 z80=
X-IronPort-AV: E=Sophos;i="5.79,349,1602518400";
   d="scan'208";a="158687532"
Received: from mail-co1nam11lp2175.outbound.protection.outlook.com (HELO
 NAM11-CO1-obe.outbound.protection.outlook.com) ([104.47.56.175])
  by ob1.hgst.iphmx.com with ESMTP; 15 Jan 2021 20:22:28 +0800
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=YqoXNZDGK/FfbE4OkHrArx2Fs8+HUGF7PtqLjAEheiFZnFMPOSUhVK046Eqg4VioscwoyqrAO6xt5y9zKxux7PBvmgDh4xsdJvW80nDGN+Hdbt6u966SOHdxwnFavbFvnpVzosW1pPaqNVG+EK316VKdWiMrCJOpPmK3LWc9Ag6l6UmSNJ5TsGVL9HKrecuJHa28ALF7Rour5eIDSP1zPdc9bH5ZaZgOUsWs+XndzGb5hlXVG5n3xWV2F7J9nMX3gZJWu42SIJfJql916tbGLRXtnFt1V3XY76AbeJnNdaWWchPABxV2KSrgag6pxKCkthPyIBVxuZIwq0d78PejsQ==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=KruYcEbb5cdiO74ZOYvYL3cCWz3qI5JLsssmLn1Qgys=;
 b=UogV0Tz4FmSXEq7VNRlgmQM+jH0K0aCmSO/4E34+XzI4m3TOuojq5+2/AV+ctI59rCYfwN0Hnc5AQMfzWiOqP9dmPFRuEZhdXU8/GByPc5sSIN2bfzHri3ot7v+PvOEZ+xRqnKNebjFKlVmeT2Qx5Py05edsbw05d3o/LLIgzjuxEnyHg9s1TM77F3yiHyshQ9UGQ1ee8Mef7vgDb4pTTYI+iKesHMWWGW1AUBBcbOAvkVuYZyh9Xtu15VTySrlDXrziclJTKVOAWcPlTZDA4ztLIonw4anv7ZV99isQaB0HCZsrvnlmXaVRuwqiNL3JQPG0s92pS2VRgSked0+FZA==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=wdc.com; dmarc=pass action=none header.from=wdc.com; dkim=pass
 header.d=wdc.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=sharedspace.onmicrosoft.com; s=selector2-sharedspace-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=KruYcEbb5cdiO74ZOYvYL3cCWz3qI5JLsssmLn1Qgys=;
 b=tZEuUMHfHILq63l2v/MdO/rdAArmDDsd78BOLOXv0g5nYyczH2K4U/+SZ0wtMDVk+u4d2txYoJqGZKsnvoTVUN0rGjvIZWhTYYhrN2BIuL/dCH3f9JuSJSzbwC1ZNFrLw2nxEb0HgiWxK+IJswGL06tbXKoYbdqXEOxUapktiM0=
Authentication-Results: kernel.org; dkim=none (message not signed)
 header.d=none;kernel.org; dmarc=none action=none header.from=wdc.com;
Received: from DM6PR04MB6201.namprd04.prod.outlook.com (2603:10b6:5:127::32)
 by DM6PR04MB4330.namprd04.prod.outlook.com (2603:10b6:5:a0::16) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3742.6; Fri, 15 Jan
 2021 12:22:25 +0000
Received: from DM6PR04MB6201.namprd04.prod.outlook.com
 ([fe80::2513:b200:bdc8:b97]) by DM6PR04MB6201.namprd04.prod.outlook.com
 ([fe80::2513:b200:bdc8:b97%5]) with mapi id 15.20.3742.012; Fri, 15 Jan 2021
 12:22:25 +0000
From: Anup Patel <anup.patel@wdc.com>
To: Will Deacon <will@kernel.org>
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Atish Patra <atish.patra@wdc.com>,
        Alistair Francis <Alistair.Francis@wdc.com>,
        Anup Patel <anup@brainfault.org>, kvm@vger.kernel.org,
        kvm-riscv@lists.infradead.org, Anup Patel <anup.patel@wdc.com>
Subject: [PATCH v6 0/8] KVMTOOL RISC-V Support
Date: Fri, 15 Jan 2021 17:51:52 +0530
Message-Id: <20210115122200.114625-1-anup.patel@wdc.com>
X-Mailer: git-send-email 2.25.1
X-Originating-IP: [122.167.152.18]
X-ClientProxiedBy: MA1PR0101CA0031.INDPRD01.PROD.OUTLOOK.COM
 (2603:1096:a00:22::17) To DM6PR04MB6201.namprd04.prod.outlook.com
 (2603:10b6:5:127::32)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from wdc.com (122.167.152.18) by
 MA1PR0101CA0031.INDPRD01.PROD.OUTLOOK.COM (2603:1096:a00:22::17) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3763.10 via Frontend
 Transport; Fri, 15 Jan 2021 12:22:22 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 23f81e71-4239-4561-c5e1-08d8b9503738
X-MS-TrafficTypeDiagnostic: DM6PR04MB4330:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM6PR04MB4330B196087ED773366B19638DA70@DM6PR04MB4330.namprd04.prod.outlook.com>
WDCIPOUTBOUND: EOP-TRUE
X-MS-Oob-TLC-OOBClassifiers: OLM:1923;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 eqPET2eEjyboUvFztxcn3ZbfMGM2fN9pFw6mqiXFnSozbxS9DgY9IGkyHQ5SoFYKhV/rWzpzN+L3K5LnhZlsAd+pf9WAWibQKkr1OblpPbt8TxotS7Qxeug/xWYqfYY6rQsuWqfKOTrN6MO9b8o068qONUshqKeVnc18fnaNP7eZJX43UDKmhiWEir22wmufITrnoN3elthOLXDokMzJ9Qq5j/2XBzV/6/G2b6aTCWX8ukhZlbNRJHu3aSxzMlFW1AYbzv5nAjVkVkRJqMLwLnXoMdywR6J+YC54aIiSpVRsL0FGE0M4yCJFfwE5LLSXqa0/DJSdmUj8k/6lt+v0LNXzKsvIVqtCx/GascG/f6N2XqJDZW+DvuYTkGCAsTvbhO82oEmpO619AabWfFHt1L/zSQMskdLHDAOsjtyp4fEN+VkNMBvaCIDun5Uo7sWPLWOGynzKW/3l1u+maiquaT5WLP/f3ifSu06xevqIrowJPz3FL15vmk51i4klWzb3+mEh5M0SNGuvSXQG6sxK1Q==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM6PR04MB6201.namprd04.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(136003)(346002)(39860400002)(376002)(366004)(396003)(966005)(66946007)(316002)(1076003)(66476007)(8936002)(186003)(66556008)(86362001)(16526019)(36756003)(6916009)(44832011)(6666004)(7696005)(4326008)(26005)(52116002)(8676002)(2616005)(478600001)(2906002)(54906003)(956004)(8886007)(55016002)(83380400001)(5660300002)(42580500001);DIR:OUT;SFP:1102;
X-MS-Exchange-AntiSpam-MessageData: 
 LPJU25ZT/BuRih+1MxXopxQRMBnPcrxNf8+q7gsig0XcxAi+GjOxM31rFz1SVss7OtEczwM7e1WcvJxw/IFO0Y89Z0C5oGpyblqsAwkx+/aPOwDZmjJvtzzBYIWXvFvEHIhkf7kIPLb4Lj+5XOJ+LoTZD+APW+T1YmK2uHi2vBZ1yT25miOikD6TGs7/8xBC3qxThxmQGfMxUlXMj9r0mg5B3hnlNqE2DjpnQcXWa2JEVZ6Bl3UR0noJEfzfTspSs3xRtbjNJUewMMKhIWBm0RRrd1JlaxYTcT83UYs5NBHQLCxIhoSFqMe98OAGg7ME9a9CwGdJj+gofsO9RlhyuE5S5WEjkY1dPbubV7pYGsn/AuCpjMPEtT8VmTspq/viqsM99pLW+cLFOmEKqoR3dArbZhDD/c5LHk9PE2wWf8oL8n8nPdw0qzz3nfbSjIGMsk09NsrxWEC3vq0QzHlGiB/txwIMC9pf8gW0cOaPcKiIOvAdfdXjysvJF8UPG6HtSI7sI3qMqbx9iWPVUsXyOzsZlC5pxGa1TI51QodVrMqkK94LcBBV/NIcTih9srFKXSzwykzih7/loMEX+mTarBBKmHYMJazi9v/zY2JgY6UwoBfIjVWijv4lKbuFoDkgF8pDGHYf3wO6tLpw0D8msoci2TmrQ2mghTJ5jwmemmGWglOdJP4V+Kf8iexX8bAZnz+G87FN60aE8IeRq+qiAsds/iGW9QW6grfWiDcROhzKwzzCTGY6xeIwIyYsrK/USzsiXc93ZN9xw2qwYYtoBjGjFUMQ80gCRAniH/g82tQjdHa8sW6fb4CouphfySAn+/B0DC9yPMTJXZzsgkzJwZSDiuy59HLi9lkGv4/fYqsoeop8C25ZRaAzA35AEIHR+ktXbvBCy3DDrPmkI+C0ZEgcYpI6dslKfBrx1ngDSGF/eULSUPIgfHsSO5PST0fjiMiMEZ0jMlDN+0l0jshxPPEVEvkPzlwWmPqtpROoWn4ToT+/9B4Tk3TYrGKDBwiZ
X-OriginatorOrg: wdc.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 23f81e71-4239-4561-c5e1-08d8b9503738
X-MS-Exchange-CrossTenant-AuthSource: DM6PR04MB6201.namprd04.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 15 Jan 2021 12:22:25.0863
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: b61c8803-16f3-4c35-9b17-6f65f441df86
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 QG6n2KGH84HNjolcZGRFYb6K8xhjdXo42T9apHlxR0OOq8o2u8ulfs3LDkIbotEqLFwE4IYEFWrcERQ1F2B6sw==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6PR04MB4330
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series adds RISC-V support for KVMTOOL and it is based on
the v10 of KVM RISC-V series. The KVM RISC-V patches are not yet
merged in Linux kernel but it will be good to get early review
for KVMTOOL RISC-V support.

The KVMTOOL RISC-V patches can be found in riscv_master branch at:
https//github.com/kvm-riscv/kvmtool.git

The KVM RISC-V patches can be found in riscv_kvm_master branch at:
https//github.com/kvm-riscv/linux.git

The QEMU RISC-V hypervisor emulation is done by Alistair and is
available in master branch at: https://git.qemu.org/git/qemu.git

Changes since v5:
 - Sync-up headers with latest KVM RISC-V v16 series which is based
   on Linux-5.11-rc3

Changes since v4:
 - Rebased on recent commit 90b2d3adadf218dfc6bdfdfcefe269843360223c
 - Sync-up headers with latest KVM RISC-V v15 series which is based
   on Linux-5.10-rc3

Changes since v3:
 - Rebased on recent commit 351d931f496aeb2e97b8daa44c943d8b59351d07
 - Improved kvm_cpu__show_registers() implementation

Changes since v2:
 - Support compiling KVMTOOL for both RV32 and RV64 systems using
   a multilib toolchain
 - Fix kvm_cpu__arch_init() for RV32 system

Changes since v1:
 - Use linux/sizes.h in kvm/kvm-arch.h
 - Added comment in kvm/kvm-arch.h about why PCI config space is 256M
 - Remove forward declaration of "struct kvm" from kvm/kvm-cpu-arch.h
 - Fixed placement of DTB and INITRD in guest RAM
 - Use __riscv_xlen instead of sizeof(unsigned long) in __kvm_reg_id()

Anup Patel (8):
  update_headers: Sync-up ABI headers with Linux-5.11-rc3
  riscv: Initial skeletal support
  riscv: Implement Guest/VM arch functions
  riscv: Implement Guest/VM VCPU arch functions
  riscv: Add PLIC device emulation
  riscv: Generate FDT at runtime for Guest/VM
  riscv: Handle SBI calls forwarded to user space
  riscv: Generate PCI host DT node

 INSTALL                             |   7 +-
 Makefile                            |  24 +-
 arm/aarch64/include/asm/kvm.h       |  45 ++-
 include/linux/kvm.h                 | 182 ++++++++-
 powerpc/include/asm/kvm.h           |   8 +
 riscv/fdt.c                         | 195 ++++++++++
 riscv/include/asm/kvm.h             | 128 +++++++
 riscv/include/kvm/barrier.h         |  14 +
 riscv/include/kvm/fdt-arch.h        |   8 +
 riscv/include/kvm/kvm-arch.h        |  85 +++++
 riscv/include/kvm/kvm-config-arch.h |  15 +
 riscv/include/kvm/kvm-cpu-arch.h    |  51 +++
 riscv/include/kvm/sbi.h             |  48 +++
 riscv/ioport.c                      |  12 +
 riscv/irq.c                         |  13 +
 riscv/kvm-cpu.c                     | 490 ++++++++++++++++++++++++
 riscv/kvm.c                         | 174 +++++++++
 riscv/pci.c                         | 109 ++++++
 riscv/plic.c                        | 563 ++++++++++++++++++++++++++++
 util/update_headers.sh              |   2 +-
 x86/include/asm/kvm.h               |  43 ++-
 21 files changed, 2198 insertions(+), 18 deletions(-)
 create mode 100644 riscv/fdt.c
 create mode 100644 riscv/include/asm/kvm.h
 create mode 100644 riscv/include/kvm/barrier.h
 create mode 100644 riscv/include/kvm/fdt-arch.h
 create mode 100644 riscv/include/kvm/kvm-arch.h
 create mode 100644 riscv/include/kvm/kvm-config-arch.h
 create mode 100644 riscv/include/kvm/kvm-cpu-arch.h
 create mode 100644 riscv/include/kvm/sbi.h
 create mode 100644 riscv/ioport.c
 create mode 100644 riscv/irq.c
 create mode 100644 riscv/kvm-cpu.c
 create mode 100644 riscv/kvm.c
 create mode 100644 riscv/pci.c
 create mode 100644 riscv/plic.c
```
#### [kvm-unit-tests PATCH v2 00/11] Fix and improve the page allocator
##### From: Claudio Imbrenda <imbrenda@linux.ibm.com>

```c
From patchwork Fri Jan 15 12:37:19 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Claudio Imbrenda <imbrenda@linux.ibm.com>
X-Patchwork-Id: 12022553
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 51857C433DB
	for <kvm@archiver.kernel.org>; Fri, 15 Jan 2021 12:44:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0A66A221F7
	for <kvm@archiver.kernel.org>; Fri, 15 Jan 2021 12:44:53 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731448AbhAOMiY (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 15 Jan 2021 07:38:24 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:33404 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S2388151AbhAOMiU (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 15 Jan 2021 07:38:20 -0500
Received: from pps.filterd (m0098409.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 10FCYfJe175231;
        Fri, 15 Jan 2021 07:37:37 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=FfM/3CEd1frObqGH3db7krvBpA6LObXCxovIaDzO2Xk=;
 b=Eq8sqJUcn1GSM5R2nik+okA6IAJXl3+5xORBryrQRJaDiZHjZuqgTj/WxURrMMcjwXco
 arMKI+8l6ZyNtdiLFJDA3AXAGOikLtXW08Repw/L4oLxcOTBzWN9rCiTwLdrM8U5k+Ov
 crdCK/B5DAYav58gbOtdqb3aN1gPGBXgL8GBZ8f0h35OrgAjpkugqCkmnOQGciQ0pmPb
 iIzg8SQ3q8vOUb22ZsVXDax/FG4oW3efz/cNS/mTGhX5B5fJVXXFJ4qHYoV4ySYYSU/q
 fcj/23CrD0WN34e9389Rh4kWwgy/sd5kUXFkc2ikQPcL+/mN9M1/l0j9HTkoSHnKRkL6 lA==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 363axcgep8-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 15 Jan 2021 07:37:36 -0500
Received: from m0098409.ppops.net (m0098409.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 10FCZ8SV177288;
        Fri, 15 Jan 2021 07:37:36 -0500
Received: from ppma03ams.nl.ibm.com (62.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.98])
        by mx0a-001b2d01.pphosted.com with ESMTP id 363axcgen1-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 15 Jan 2021 07:37:36 -0500
Received: from pps.filterd (ppma03ams.nl.ibm.com [127.0.0.1])
        by ppma03ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 10FCb9ZS032538;
        Fri, 15 Jan 2021 12:37:34 GMT
Received: from b06cxnps3074.portsmouth.uk.ibm.com
 (d06relay09.portsmouth.uk.ibm.com [9.149.109.194])
        by ppma03ams.nl.ibm.com with ESMTP id 35y447yp48-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 15 Jan 2021 12:37:34 +0000
Received: from d06av26.portsmouth.uk.ibm.com (d06av26.portsmouth.uk.ibm.com
 [9.149.105.62])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 10FCbVDM34275630
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 15 Jan 2021 12:37:31 GMT
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 99D2EAE056;
        Fri, 15 Jan 2021 12:37:31 +0000 (GMT)
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 2C553AE05F;
        Fri, 15 Jan 2021 12:37:31 +0000 (GMT)
Received: from ibm-vm.ibmuc.com (unknown [9.145.4.167])
        by d06av26.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Fri, 15 Jan 2021 12:37:31 +0000 (GMT)
From: Claudio Imbrenda <imbrenda@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: frankja@linux.ibm.com, david@redhat.com, thuth@redhat.com,
        pbonzini@redhat.com, cohuck@redhat.com, lvivier@redhat.com,
        nadav.amit@gmail.com, krish.sadhukhan@oracle.com
Subject: [kvm-unit-tests PATCH v2 00/11] Fix and improve the page allocator
Date: Fri, 15 Jan 2021 13:37:19 +0100
Message-Id: <20210115123730.381612-1-imbrenda@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.343,18.0.737
 definitions=2021-01-15_07:2021-01-15,2021-01-15 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 impostorscore=0
 lowpriorityscore=0 mlxlogscore=999 spamscore=0 adultscore=0 suspectscore=0
 mlxscore=0 malwarescore=0 clxscore=1015 phishscore=0 priorityscore=1501
 bulkscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2101150077
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

My previous patchseries was rushed and not polished enough. Furthermore it
introduced some regressions.

This patchseries fixes hopefully all the issues reported, and introduces
some new features.

It also simplifies the code and hopefully makes it more readable.

Fixed:
* allocated memory is now zeroed by default

New features:
* per-allocation flags to specify not just the area (like before) but also
  other parameters
  - dontzero flag: the allocation will not be zeroed
  - fresh flag: the returned memory has never been read or written to before

I would appreciate if people could test these patches, especially on
strange, unusual or exotic hardware (I tested only on s390x)


GitLab:
  https://gitlab.com/imbrenda/kvm-unit-tests/-/tree/page_allocator_fixes
CI:
  https://gitlab.com/imbrenda/kvm-unit-tests/-/pipelines/241819726


v1->v2
* have DONTZERO flag instead of a ZERO flag, this way there is no need
  for a default.
* drop the last patch, since there is no need for a default now.
* fixed a pre-existing bug that caused wrong allocations
* renamed alloc_pages_special to reserve_pages, to make it clear it is
  not a normal allocation. The function now returns 0 on success and -1
  on failure.
* added a NULL check in vm_free; freeing a NULL pointer is now a no-op.
* fix and improve some comments
* remove a spurious return 

Claudio Imbrenda (11):
  lib/x86: fix page.h to include the generic header
  lib/list.h: add list_add_tail
  lib/vmalloc: add some asserts and improvements
  lib/asm: Fix definitions of memory areas
  lib/alloc_page: fix and improve the page allocator
  lib/alloc.h: remove align_min from struct alloc_ops
  lib/alloc_page: Optimization to skip known empty freelists
  lib/alloc_page: rework metadata format
  lib/alloc: replace areas with more generic flags
  lib/alloc_page: Wire up FLAG_DONTZERO
  lib/alloc_page: Properly handle requests for fresh blocks

 lib/asm-generic/memory_areas.h |   9 +-
 lib/arm/asm/memory_areas.h     |  11 +-
 lib/arm64/asm/memory_areas.h   |  11 +-
 lib/powerpc/asm/memory_areas.h |  11 +-
 lib/ppc64/asm/memory_areas.h   |  11 +-
 lib/s390x/asm/memory_areas.h   |  13 +-
 lib/x86/asm/memory_areas.h     |  27 ++--
 lib/x86/asm/page.h             |   4 +-
 lib/alloc.h                    |   1 -
 lib/alloc_page.h               |  76 ++++++---
 lib/list.h                     |   9 ++
 lib/alloc_page.c               | 283 +++++++++++++++++++--------------
 lib/alloc_phys.c               |   9 +-
 lib/s390x/smp.c                |   2 +-
 lib/vmalloc.c                  |  23 +--
 15 files changed, 284 insertions(+), 216 deletions(-)
```
#### [PATCH RFC 0/4] KVM: x86: Drastically raise KVM_USER_MEM_SLOTS limit
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
From patchwork Fri Jan 15 13:18:40 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 12022727
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 607D0C433DB
	for <kvm@archiver.kernel.org>; Fri, 15 Jan 2021 13:21:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2DB2323359
	for <kvm@archiver.kernel.org>; Fri, 15 Jan 2021 13:21:30 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732886AbhAONVM (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 15 Jan 2021 08:21:12 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:35684 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1732822AbhAONVL (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 15 Jan 2021 08:21:11 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1610716730;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=bCrvudd8WM+aVyudRWSq4Vs5HPTCK/SkatpqJMHjO6c=;
        b=C/DiDYrHvDNnvAI3XyNHjchpDBUgH4CvfiXuvVfqQdngaHcf4dIWoNQv94N2tZst+m241p
        SAd4mhFlvIN/mF8r8FiXE2Ljkh0MUiwhMFXEh6/85EwNXrA32Ao0EwBBkTPH41LHNLCndW
        mFbgLQBAxXFI47qTwxxRHB2ydf87RvE=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-169-yiRhxk8DNjyVVqxQRxW9-w-1; Fri, 15 Jan 2021 08:18:49 -0500
X-MC-Unique: yiRhxk8DNjyVVqxQRxW9-w-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 72B5F100F340;
        Fri, 15 Jan 2021 13:18:47 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.195.14])
        by smtp.corp.redhat.com (Postfix) with ESMTP id A6C73608BA;
        Fri, 15 Jan 2021 13:18:45 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>
Subject: [PATCH RFC 0/4] KVM: x86: Drastically raise KVM_USER_MEM_SLOTS limit
Date: Fri, 15 Jan 2021 14:18:40 +0100
Message-Id: <20210115131844.468982-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

TL;DR: any particular reason why KVM_USER_MEM_SLOTS is so low?

Longer version:

Current KVM_USER_MEM_SLOTS limit (509) can be a limiting factor for some
configurations. In particular, when QEMU tries to start a Windows guest
with Hyper-V SynIC enabled and e.g. 256 vCPUs the limit is hit as SynIC
requires two pages per vCPU and the guest is free to pick any GFN for
each of them, this fragments memslots as QEMU wants to have a separate
memslot for each of these pages (which are supposed to act as 'overlay'
pages).

Memory slots are allocated dynamically in KVM when added so the only real
limitation is 'id_to_index' array which is 'short'. We don't have any
KVM_MEM_SLOTS_NUM/KVM_USER_MEM_SLOTS-sized statically defined arrays.

We could've just raised the limit to e.g. '1021' (we have 3 private
memslots on x86) and this should be enough for now as KVM_MAX_VCPUS is
'288' but AFAIK there are plans to raise this limit as well.

Vitaly Kuznetsov (4):
  KVM: x86: Drop redundant KVM_MEM_SLOTS_NUM definition
  KVM: mips: Drop KVM_PRIVATE_MEM_SLOTS definition
  KVM: Define KVM_USER_MEM_SLOTS in arch-neutral
    include/linux/kvm_host.h
  KVM: x86: Stop limiting KVM_USER_MEM_SLOTS

 arch/mips/include/asm/kvm_host.h | 2 --
 arch/x86/include/asm/kvm_host.h  | 3 +--
 include/linux/kvm_host.h         | 4 ++++
 3 files changed, 5 insertions(+), 4 deletions(-)
```
#### [PATCH v3 0/2] x86: Add the feature Virtual SPEC_CTRL
##### From: Babu Moger <babu.moger@amd.com>

```c
From patchwork Fri Jan 15 17:21:26 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Babu Moger <babu.moger@amd.com>
X-Patchwork-Id: 12023401
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-10.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 56077C4332E
	for <kvm@archiver.kernel.org>; Fri, 15 Jan 2021 17:22:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 242992399C
	for <kvm@archiver.kernel.org>; Fri, 15 Jan 2021 17:22:44 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728910AbhAORW1 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 15 Jan 2021 12:22:27 -0500
Received: from mail-co1nam11on2062.outbound.protection.outlook.com
 ([40.107.220.62]:31456
        "EHLO NAM11-CO1-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1727902AbhAORW0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 15 Jan 2021 12:22:26 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=Wy1PQrikKe27Y2fWpLmqL8zFjzHBC+5L6PXzD/HwaK9w+kz1GAl2PhxyEIgUFlpehS3rH2CPlD16Ah52GQBie8iABIFqxe0lCtf1QGQzSfH8h+67bSEj0cV5KJ2Ljf2hZCTi7w/3GN0/XLu7bgbbD6bltcU0D5YEFW+ruQh5dpyJYb3GRWlimNz9Bb1TcJ91Ij+8Eob8pzm8MBgd2hEGlQuiFO29HyJDjYz355EFK/W6s2+muSuAN/cUeQYUdRk2gv9zEhEv2vvQpNUeSPO16RhZhI7/m2Y4fPrlWMtQhzvs5Lr8PJLzu11Uzi/ppDGRydn6rygrI9BuK1UMno5bwg==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=aU+cEoFG20fBtXeFBdLKxb25bP2RxVKXyqGS9kJG8y8=;
 b=hyw00snUuz7s9lzuNDhhBUs2sF3YYkjsuYmgoXs1D0ouDERnjz0U539kZnln+E0rtjWfK2NXCb/jhko4tuOWqyGjPO+xEZsixS2QqPrAAL1/Wk3K7wY4pyGWJXZAFoTfC+NUDzrCPshq3rF95peQDLGrhZxtJfu1WIZGxrFIRC3o6IJUEecex6vL+U5EN3OdswQVy1FlI1xWslTEBJlAzEGO1mjtAIGcUeZz5UqYzCIsddx4MvTBE3pTDWOGlz1i2Lrn6sB++22KNlL1X7jz/FKwXr12GOGeP46/nYTAdv72lb3/8d/twphNikOOdHOCDHdYu+/N50G18CZnoIfQCw==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=amd.com; s=selector1;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=aU+cEoFG20fBtXeFBdLKxb25bP2RxVKXyqGS9kJG8y8=;
 b=WcPmIgOIQKFK9YoGpGI9kIz5Uy2w/7a+YgrYlL4cvAIHeaiCD6poc7cqTyUs7pFAsCsuQZfBVEGmqfOEi8DPs2FYqi+Rn1l53sMq/aP0HhXYJWTbwSm3gszjSoTBt14D7W6ftRNVQb0rOywrn07+YvFFEneuBEeqhFXfJL9M7yM=
Authentication-Results: tencent.com; dkim=none (message not signed)
 header.d=none;tencent.com; dmarc=none action=none header.from=amd.com;
Received: from SN1PR12MB2560.namprd12.prod.outlook.com (2603:10b6:802:26::19)
 by SA0PR12MB4383.namprd12.prod.outlook.com (2603:10b6:806:94::12) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3742.9; Fri, 15 Jan
 2021 17:21:28 +0000
Received: from SN1PR12MB2560.namprd12.prod.outlook.com
 ([fe80::8c0e:9a64:673b:4fff]) by SN1PR12MB2560.namprd12.prod.outlook.com
 ([fe80::8c0e:9a64:673b:4fff%5]) with mapi id 15.20.3763.010; Fri, 15 Jan 2021
 17:21:28 +0000
Subject: [PATCH v3 0/2] x86: Add the feature Virtual SPEC_CTRL
From: Babu Moger <babu.moger@amd.com>
To: pbonzini@redhat.com, tglx@linutronix.de, mingo@redhat.com,
        bp@alien8.de
Cc: fenghua.yu@intel.com, tony.luck@intel.com, wanpengli@tencent.com,
        kvm@vger.kernel.org, thomas.lendacky@amd.com, peterz@infradead.org,
        seanjc@google.com, joro@8bytes.org, x86@kernel.org,
        kyung.min.park@intel.com, linux-kernel@vger.kernel.org,
        krish.sadhukhan@oracle.com, hpa@zytor.com, mgross@linux.intel.com,
        vkuznets@redhat.com, kim.phillips@amd.com, wei.huang2@amd.com,
        jmattson@google.com
Date: Fri, 15 Jan 2021 11:21:26 -0600
Message-ID: <161073115461.13848.18035972823733547803.stgit@bmoger-ubuntu>
User-Agent: StGit/0.17.1-dirty
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: SA0PR11CA0136.namprd11.prod.outlook.com
 (2603:10b6:806:131::21) To SN1PR12MB2560.namprd12.prod.outlook.com
 (2603:10b6:802:26::19)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from [127.0.1.1] (165.204.77.1) by
 SA0PR11CA0136.namprd11.prod.outlook.com (2603:10b6:806:131::21) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3763.11 via Frontend
 Transport; Fri, 15 Jan 2021 17:21:27 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 6dde84e2-aed4-4c3c-30bf-08d8b979fe31
X-MS-TrafficTypeDiagnostic: SA0PR12MB4383:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SA0PR12MB4383182CC7A067E73A78A81995A70@SA0PR12MB4383.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:8273;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 FJIF/4JfN1OQOEh0UGiydCKFJg4FpVjRr+h71TcA0u6OjrOyoVp1hiCdIuYZIORWPBNYmi2jD7TbJ/+msoZba6n7/FBO5lEbwLmDEjwcbODUDKjOkZ8fjoZ3v7rFRcHA5jxZ7Ab/tgQJOVLltqcbTYXdaNhaDHTey+qEI5bVU2aTaV9Z0xmDEaCf5x6KtGX0CRbco+dAHfOS//75vwpWfPFTqb1sZSWwFTgTGvuwf1Ol+8g/oAgWboliZg94qMTNHOrRE2rDrZRyPcHTBSQZO18tg8APAJskFLXk3a7P1HvbAh/AT6lA9BURsBWoDCZ46PwehkpPG3Vfqv26obli/7AmjP1mq8rk7c9H6y5y7npupcqtFRC82LlTH8kno0foOptspgykg9/+6ZcroIBkF6Z+4r68RGraSwehFhfy6engCjsN9gVB3WAh2yisZoHBUOU3NfcSSINjzOBAjmOZtA==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN1PR12MB2560.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(7916004)(4636009)(396003)(136003)(39860400002)(376002)(366004)(346002)(4326008)(956004)(16526019)(33716001)(7416002)(316002)(44832011)(83380400001)(478600001)(52116002)(966005)(9686003)(66556008)(103116003)(66476007)(8936002)(26005)(16576012)(6486002)(8676002)(186003)(86362001)(2906002)(5660300002)(66946007);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: =?utf-8?q?39HJsjkZ9qVoJnENa5b/h/1Jlwmmyw?=
	=?utf-8?q?SjwGdFY07MxSEPoZIQQHr+ZGlwSuSDmOkh1ABZeDU0HdBBSN8j8l18PrmQAL93gAa?=
	=?utf-8?q?rtYCM3Xyzsp6ih8fNB1Lu/AM7Zj0pCrHC7GLrQx9MUiUqHzjkpjv+HsvfCRCJuSQn?=
	=?utf-8?q?fgx7K5cxgeyp450bJSYFufCnNUq1vFspocfpbBKrgidPYnsmKI/DOEHf93vVsdX08?=
	=?utf-8?q?c2nLSEt8jyw9jxt9aGW4aGeLXTdAnAVQXDfdqzDp3TEY/vsK2Gr2UZCWpPFMnYfTN?=
	=?utf-8?q?0PTr2O2Eetf5tQQqr3e52K+ylvct/drtwS7r0vp6kmld/RYmoPZaXuUxrx5SimW+D?=
	=?utf-8?q?jQDnXFDIlV546MIKrgipcUjMd3Rd9DgAn4LXcLG70UV8Qg+pkouqcspEauaJWNHnV?=
	=?utf-8?q?dDpq+H+ZlTIKR5pcxbTo862i30UgRPVCIsYf2Lc/yWcJALakNyZqP6bUatxOTFvbk?=
	=?utf-8?q?3A/KdFZJ0JSjXXREWJn6+/EXGsSNhnrlZyajFCRLBD3KH7Q1l8wcVpBtPlRLt84Wu?=
	=?utf-8?q?g2Md61Bn4L8IPa6bcgjd88Dawez5D12a3WH6Jt09aqf2fsBu1XC3blEwPH6X0Pf9X?=
	=?utf-8?q?CHkqA7PMTwe+EJNfUESuD5z9ZfBIYA5pBC+WwxoCng4eYuSK5G/xEy2J+6UA+uHJi?=
	=?utf-8?q?QASc/WUZe8o2Mkn8IlyBXK7BpuSTrFpSo/vAjINoMQeRKutFkpkxNNgnXVTTVK3OG?=
	=?utf-8?q?rbJHCkL3rc38tHawjDKS0DsfRvctDXECO6c7oFAjpPkSriNz8oiTje9l3l9b27mOE?=
	=?utf-8?q?/STRz/1hYCkUCiDOFCkkzs9fzcJvHB0CSCVsGCABjs1k1alhZRCkSOYCgslX0CpRq?=
	=?utf-8?q?x1x09KfSMZp+nY9Q/00AR9+fqcG+Eh9pGiAlG8IVWkHbIAro8g+6Guos5k/FeqA4C?=
	=?utf-8?q?UU3vmgCs/h3N+xGCA6IHkgu3UqWSblxjJHGnmC+IH9TdyoHymfc/L72mVsdfU5gfY?=
	=?utf-8?q?W+xZUzOnzXeJ9hnVAlD?=
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 6dde84e2-aed4-4c3c-30bf-08d8b979fe31
X-MS-Exchange-CrossTenant-AuthSource: SN1PR12MB2560.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 15 Jan 2021 17:21:28.0962
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 Rr33v0Qx7pRrxZLyHZ6rb4srJx0uNt+pD3W45ny/B5BM3dd8Z7AEybJrHd5VHEN6
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SA0PR12MB4383
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Newer AMD processors have a feature to virtualize the use of the
SPEC_CTRL MSR on the guest. The series adds the feature support
and enables the feature on SVM.
---
v3:
  1. Taken care of recent changes in vmcb_save_area. Needed to adjust the save
     area spec_ctrl definition.
  2. Taken care of few comments from Tom.
     a. Initialised the save area spec_ctrl in case of SEV-ES.
     b. Removed the changes in svm_get_msr/svm_set_msr.
     c. Reverted the changes to disable the msr interception to avoid compatibility
        issue.
  3. Updated the patch #1 with Acked-by from Boris.
  
v2:
  https://lore.kernel.org/kvm/160867624053.3471.7106539070175910424.stgit@bmoger-ubuntu/
  NOTE: This is not final yet. Sending out the patches to make
  sure I captured all the comments correctly.

  1. Most of the changes are related to Jim and Sean's feedback.
  2. Improved the description of patch #2.
  3. Updated the vmcb save area's guest spec_ctrl value(offset 0x2E0)
     properly. Initialized during init_vmcb and svm_set_msr and
     returned the value from save area for svm_get_msr.
  4. As Jim commented, transferred the value into the VMCB prior
     to VMRUN and out of the VMCB after #VMEXIT.
  5. Added kvm-unit-test to detect the SPEC CTRL feature.
     https://lore.kernel.org/kvm/160865324865.19910.5159218511905134908.stgit@bmoger-ubuntu/
  6. Sean mantioned of renaming MSR_AMD64_VIRT_SPEC_CTRL. But, it might
     create even more confusion, so dropped the idea for now.

v1:
https://lore.kernel.org/kvm/160738054169.28590.5171339079028237631.stgit@bmoger-ubuntu/

Babu Moger (2):
      x86/cpufeatures: Add the Virtual SPEC_CTRL feature
      KVM: SVM: Add support for Virtual SPEC_CTRL


 arch/x86/include/asm/cpufeatures.h |    1 +
 arch/x86/include/asm/svm.h         |    4 +++-
 arch/x86/kvm/svm/sev.c             |    4 ++++
 arch/x86/kvm/svm/svm.c             |   19 +++++++++++++++----
 4 files changed, 23 insertions(+), 5 deletions(-)

--
```
#### [PATCH 0/2] KVM: VMX: Avoid RDMSRs in PI x2APIC checks
##### From: Sean Christopherson <seanjc@google.com>

```c
From patchwork Fri Jan 15 22:03:52 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12024227
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 61EF5C433E0
	for <kvm@archiver.kernel.org>; Fri, 15 Jan 2021 22:05:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2CAD4239FC
	for <kvm@archiver.kernel.org>; Fri, 15 Jan 2021 22:05:02 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726853AbhAOWEm (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 15 Jan 2021 17:04:42 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:49678 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725918AbhAOWEl (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 15 Jan 2021 17:04:41 -0500
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 55BEFC061794
        for <kvm@vger.kernel.org>; Fri, 15 Jan 2021 14:04:01 -0800 (PST)
Received: by mail-yb1-xb4a.google.com with SMTP id e74so8335685ybh.19
        for <kvm@vger.kernel.org>; Fri, 15 Jan 2021 14:04:01 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=F4qSiyP6qNsDhBMqCUY6h5QJboOTRDoltedUrihSiWc=;
        b=Q93aXvTiT7/Nuaby+dCOgqxB4DbUiRhsGWJtdcyTmjoKE+RnZiQv4StLdlcVhg3c4+
         +C6RVz/EmcpRQwaNHk3miO89hu8VDzZQJvBDZV8c7GfRbUm0MvlXaI3g516WvDqcQqt5
         1sl+h4A/FyHrwyxN9KMZ9C2n8dhJ4vzFY8MImNedDbK0+8WZSmZGXKeNumERlFsFPqOR
         eQ8aGrA41ytuI/yjSNQCkUwN3KAQuG04WDY3S9zqhceUmqOuB5bZzESTKuvybupAleME
         BpJ1v24GtegZoRz1EtV1LoFC6fF5aanVOIxVS7xQtVKsfSI29PLZnIT6OgxJb35gvH8+
         N5jw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:reply-to:date:message-id:mime-version
         :subject:from:to:cc;
        bh=F4qSiyP6qNsDhBMqCUY6h5QJboOTRDoltedUrihSiWc=;
        b=BCRV5jC2OOk/oJA+QdYtRCw4WGPRpF/H95jICKL7UbSYRdTsWvqPv1UE0dUwb8B/J5
         3wVcCye+yBvSp8N5QmXnHQ6JFB7fI98Ziq7vuFlxgzarmDPOprA5q2p1fpM8ESzv8Xk6
         LT0aUT+BAXIdvKdZjPeMWZSZ5pfDrUHtPXVgCJbvQjjTnRaWBbBEV6nyBHRMBl7Qfw98
         OrWXXrn/c+kW/NczjwaDyCO0IrqmkfRJKR8RPF0ElGwEiqMixiL0eKqemDwKqlc/Fca1
         nJVblBRWGJYM/w/K8ij3fYYXuluBKLInjahCJuZTs2USAAdOPnsrf0OrK005z/suR4zL
         R04A==
X-Gm-Message-State: AOAM532RJAHTW+s73gOHOSE/0TsqHEQAk5hRjS0Njo4foM2CzkLBHK/4
        qBu/NCfD6i8q5YmIH7H2kt1YHN3NKWc=
X-Google-Smtp-Source: 
 ABdhPJzp4A3W1q3Tqhar2/Evi1HCTQ5/uUoQIM/i7LHvbvw5BJaOYCPfssOfhCcdTCa/dJEeGjj4v/SjFps=
Sender: "seanjc via sendgmr" <seanjc@seanjc798194.pdx.corp.google.com>
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:1ea0:b8ff:fe73:50f5])
 (user=seanjc job=sendgmr) by 2002:a05:6902:20a:: with SMTP id
 j10mr21842753ybs.293.1610748240590; Fri, 15 Jan 2021 14:04:00 -0800 (PST)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Fri, 15 Jan 2021 14:03:52 -0800
Message-Id: <20210115220354.434807-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.30.0.284.gd98b1dd5eaa7-goog
Subject: [PATCH 0/2] KVM: VMX: Avoid RDMSRs in PI x2APIC checks
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, luferry <luferry@163.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Resurrect a patch[*] from over a year ago to avoid RDMSR in a fairly hot
path in KVM's posted interrupt support.  Note, in my response to that
patch, I suggested checking x2apic_supported() as well as x2apic_mode.  I
have no idea why I suggested that; unless I'm missing something,
x2apic_mode can never be set if x2apic_supported() is false.

[*] https://lkml.kernel.org/r/20190723130608.26528-1-luferry@163.com/

Sean Christopherson (2):
  x86/apic: Export x2apic_mode for use by KVM in "warm" path
  KVM: VMX: Use x2apic_mode to avoid RDMSR when querying PI state

 arch/x86/kernel/apic/apic.c    | 1 +
 arch/x86/kvm/vmx/posted_intr.c | 6 +++---
 2 files changed, 4 insertions(+), 3 deletions(-)
```
