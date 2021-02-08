#### [PATCH RFC 1/7] kvm: x86: Expose XFD CPUID to guest
##### From: Jing Liu <jing2.liu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jing Liu <jing2.liu@linux.intel.com>
X-Patchwork-Id: 12072547
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-14.8 required=3.0 tests=BAYES_00,
	DATE_IN_FUTURE_06_12,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id F1815C433E6
	for <kvm@archiver.kernel.org>; Sun,  7 Feb 2021 06:56:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B870964E72
	for <kvm@archiver.kernel.org>; Sun,  7 Feb 2021 06:56:47 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229626AbhBGG4d (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sun, 7 Feb 2021 01:56:33 -0500
Received: from mga07.intel.com ([134.134.136.100]:48431 "EHLO mga07.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229611AbhBGG4d (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 7 Feb 2021 01:56:33 -0500
IronPort-SDR: 
 3GTvJJnbRjzp4nUoXOTww258BFH+aZoQgA97PqCiZajHDHzReqZsijm9zl/ObGlEV1NouFVKCj
 ql7diPm3UH5g==
X-IronPort-AV: E=McAfee;i="6000,8403,9887"; a="245660843"
X-IronPort-AV: E=Sophos;i="5.81,159,1610438400";
   d="scan'208";a="245660843"
Received: from fmsmga004.fm.intel.com ([10.253.24.48])
  by orsmga105.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 06 Feb 2021 22:54:45 -0800
IronPort-SDR: 
 bZjtW2cyg+iTRXU9kcYbw194kx7IhBTOrbnlSPqgzGgDPId9vZLjXGEEmx4zyOK1aMt90Mn+TD
 qYpI1/P4LIOw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.81,159,1610438400";
   d="scan'208";a="410376574"
Received: from vmmteam.bj.intel.com ([10.240.193.86])
  by fmsmga004.fm.intel.com with ESMTP; 06 Feb 2021 22:54:43 -0800
From: Jing Liu <jing2.liu@linux.intel.com>
To: pbonzini@redhat.com, seanjc@google.com, kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, jing2.liu@intel.com
Subject: [PATCH RFC 1/7] kvm: x86: Expose XFD CPUID to guest
Date: Sun,  7 Feb 2021 10:42:50 -0500
Message-Id: <20210207154256.52850-2-jing2.liu@linux.intel.com>
X-Mailer: git-send-email 2.18.4
In-Reply-To: <20210207154256.52850-1-jing2.liu@linux.intel.com>
References: <20210207154256.52850-1-jing2.liu@linux.intel.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Intel's Extended Feature Disable (XFD) feature is an extension
to the XSAVE feature that allows an operating system to enable
a feature while preventing specific user threads from using
the feature. A processor that supports XFD enumerates
CPUID.(EAX=0DH,ECX=1):EAX[4] as 1.

Signed-off-by: Jing Liu <jing2.liu@linux.intel.com>
---
 arch/x86/kvm/cpuid.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v2] KVM: x86/MMU: Do not check unsync status for root SP.
##### From: Yu Zhang <yu.c.zhang@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yu Zhang <yu.c.zhang@linux.intel.com>
X-Patchwork-Id: 12072469
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-14.8 required=3.0 tests=BAYES_00,
	DATE_IN_FUTURE_06_12,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A4E7EC433E0
	for <kvm@archiver.kernel.org>; Sun,  7 Feb 2021 04:43:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 58B9C64E8F
	for <kvm@archiver.kernel.org>; Sun,  7 Feb 2021 04:43:53 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229731AbhBGEn3 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sat, 6 Feb 2021 23:43:29 -0500
Received: from mga12.intel.com ([192.55.52.136]:51358 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229716AbhBGEn2 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 6 Feb 2021 23:43:28 -0500
IronPort-SDR: 
 jHaulizGzHvYvaVPL8f95MvnA2+eOyRS2aRGHvTWEyp5nqiULqy7GMAcjoU6r7QNZjz5Gz7khw
 AOG9hGt6GpZw==
X-IronPort-AV: E=McAfee;i="6000,8403,9887"; a="160738821"
X-IronPort-AV: E=Sophos;i="5.81,158,1610438400";
   d="scan'208";a="160738821"
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by fmsmga106.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 06 Feb 2021 20:41:41 -0800
IronPort-SDR: 
 zLoETFuczy8Gk4DSBOAKv2O33JzVPzOSRfVuX+iLAGm+5/ZXoQfQmVNt6qK+HgCWel57jEV96t
 Izy++QQ5Tacg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.81,158,1610438400";
   d="scan'208";a="374846616"
Received: from zhangyu-optiplex-7040.bj.intel.com ([10.238.154.148])
  by fmsmga008.fm.intel.com with ESMTP; 06 Feb 2021 20:41:40 -0800
From: Yu Zhang <yu.c.zhang@linux.intel.com>
To: seanjc@google.com, pbonzini@redhat.com
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        vkuznets@redhat.com, wanpengli@tencent.com, jmattson@google.com,
        joro@8bytes.org
Subject: [PATCH v2] KVM: x86/MMU: Do not check unsync status for root SP.
Date: Sun,  7 Feb 2021 20:22:54 +0800
Message-Id: <20210207122254.23056-1-yu.c.zhang@linux.intel.com>
X-Mailer: git-send-email 2.17.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In shadow page table, only leaf SPs may be marked as unsync.
And for non-leaf SPs, we use unsync_children to keep the number
of the unsynced children. In kvm_mmu_sync_root(), sp->unsync
shall always be zero for the root SP, , hence no need to check
it. Instead, a warning inside mmu_sync_children() is added, in
case someone incorrectly used it.

Also, clarify the mmu_need_write_protect(), by moving the warning
into kvm_unsync_page().

Signed-off-by: Yu Zhang <yu.c.zhang@linux.intel.com>
Signed-off-by: Sean Christopherson <seanjc@google.com>
---
Changes in V2:
- warnings added based on Sean's suggestion.

 arch/x86/kvm/mmu/mmu.c | 12 +++++++++---
 1 file changed, 9 insertions(+), 3 deletions(-)

```
#### [RFC PATCH v4 01/17] af_vsock: update functions for connectible socket
##### From: Arseny Krasnov <arseny.krasnov@kaspersky.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Arseny Krasnov <arseny.krasnov@kaspersky.com>
X-Patchwork-Id: 12072979
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-19.3 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 1EF84C433E0
	for <kvm@archiver.kernel.org>; Sun,  7 Feb 2021 15:15:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DA05364E0B
	for <kvm@archiver.kernel.org>; Sun,  7 Feb 2021 15:15:51 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229681AbhBGPPf (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sun, 7 Feb 2021 10:15:35 -0500
Received: from mx12.kaspersky-labs.com ([91.103.66.155]:12283 "EHLO
        mx12.kaspersky-labs.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229562AbhBGPPc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 7 Feb 2021 10:15:32 -0500
Received: from relay12.kaspersky-labs.com (unknown [127.0.0.10])
        by relay12.kaspersky-labs.com (Postfix) with ESMTP id 9640675BDD;
        Sun,  7 Feb 2021 18:14:39 +0300 (MSK)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=kaspersky.com;
        s=mail; t=1612710879;
        bh=+BJT0p4wLlF+uinBv9HlifTXu5xsC6yZ+ZgMGINHYY8=;
        h=From:To:Subject:Date:Message-ID:MIME-Version:Content-Type;
        b=WdiVOt3Ys60LtIoQ/wG1ssYMEH5AnuUUKl8Hm0yOOCXdko9cNpTryiKrq3rKCnNct
         NwQYTOk2PKcwIi2bXoegLEgdLvi+kUqLnvkQsNFk6K8o9/h4fPlbz+w8DilDOCGaM5
         m1ujqO1kMzS14K/eYT+8KLOcDzqAW9TiwEd3ZwCg=
Received: from mail-hq2.kaspersky.com (unknown [91.103.66.206])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-SHA256 (128/128 bits))
        (Client CN "mail-hq2.kaspersky.com",
 Issuer "Kaspersky MailRelays CA G3" (verified OK))
        by mailhub12.kaspersky-labs.com (Postfix) with ESMTPS id C323175BAB;
        Sun,  7 Feb 2021 18:14:38 +0300 (MSK)
Received: from arseniy-pc.avp.ru (10.64.64.121) by hqmailmbx3.avp.ru
 (10.64.67.243) with Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256_P256) id 15.1.2044.4; Sun, 7 Feb
 2021 18:14:38 +0300
From: Arseny Krasnov <arseny.krasnov@kaspersky.com>
To: Stefan Hajnoczi <stefanha@redhat.com>,
        Stefano Garzarella <sgarzare@redhat.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Jason Wang <jasowang@redhat.com>,
        "David S. Miller" <davem@davemloft.net>,
        Jakub Kicinski <kuba@kernel.org>,
        Arseny Krasnov <arseny.krasnov@kaspersky.com>,
        Jorgen Hansen <jhansen@vmware.com>,
        Colin Ian King <colin.king@canonical.com>,
        Andra Paraschiv <andraprs@amazon.com>,
        Jeff Vander Stoep <jeffv@google.com>
CC: <kvm@vger.kernel.org>, <virtualization@lists.linux-foundation.org>,
        <netdev@vger.kernel.org>, <linux-kernel@vger.kernel.org>,
        <stsp2@yandex.ru>, <oxffffaa@gmail.com>
Subject: [RFC PATCH v4 01/17] af_vsock: update functions for connectible
 socket
Date: Sun, 7 Feb 2021 18:14:23 +0300
Message-ID: <20210207151426.804348-1-arseny.krasnov@kaspersky.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20210207151259.803917-1-arseny.krasnov@kaspersky.com>
References: <20210207151259.803917-1-arseny.krasnov@kaspersky.com>
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

This prepares af_vsock.c for SEQPACKET support: some functions such
as setsockopt(), getsockopt(), connect(), recvmsg(), sendmsg() are
shared between both types of sockets, so rename them in general
manner.

Signed-off-by: Arseny Krasnov <arseny.krasnov@kaspersky.com>
---
 net/vmw_vsock/af_vsock.c | 64 +++++++++++++++++++++-------------------
 1 file changed, 34 insertions(+), 30 deletions(-)

```
