#### [PULL kvm-unit-tests 01/17] arm: Add missing test name prefix for pl031 and spinlock
##### From: Andrew Jones <drjones@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11318893
Return-Path: <SRS0=wzsb=23=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 01DAF14BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  6 Jan 2020 10:03:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D3E22207FD
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  6 Jan 2020 10:03:55 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="ZttHOFaA"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726173AbgAFKDy (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 6 Jan 2020 05:03:54 -0500
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:37263 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1725446AbgAFKDy (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 6 Jan 2020 05:03:54 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1578305033;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=1uqMJ/dalG5f6I7arCU4SZG4PVAJtaN3KTr4RIMAf6Y=;
        b=ZttHOFaA9vyR4PSxfTEhlPCiIjr7QCYl0triXmAQqzYcaOFgIglaaqI98LqwSoRQAdzFw4
        WgnLCyow2IuzZ7kL9fML01HtT1RyDbmntL9u3l9v/zvm7ko9IY1ArjedrAfmdILyFklfzK
        UleTn4dDhj5/e2fyGfeIk8JUjGS2ce8=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-416-UXh7ykwhPr-u1k98hOkdTQ-1; Mon, 06 Jan 2020 05:03:52 -0500
X-MC-Unique: UXh7ykwhPr-u1k98hOkdTQ-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 1B4ED800D48;
        Mon,  6 Jan 2020 10:03:51 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.43.2.160])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 1C7F57BA4F;
        Mon,  6 Jan 2020 10:03:49 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com
Cc: Chen Qun <kuhn.chenqun@huawei.com>
Subject: [PULL kvm-unit-tests 01/17] arm: Add missing test name prefix for
 pl031 and spinlock
Date: Mon,  6 Jan 2020 11:03:31 +0100
Message-Id: <20200106100347.1559-2-drjones@redhat.com>
In-Reply-To: <20200106100347.1559-1-drjones@redhat.com>
References: <20200106100347.1559-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Chen Qun <kuhn.chenqun@huawei.com>

pl031 and spinlock testcase without prefix, when running
the unit tests in TAP mode (./run_tests.sh -t), it is
difficult to the test results.

The test results：
ok 13 - Periph/PCell IDs match
ok 14 - R/O fields are R/O
ok 15 - RTC ticks at 1HZ
ok 16 - RTC IRQ not pending yet
...
ok 24 -   RTC IRQ not pending anymore
ok 25 - CPU1: Done - Errors: 0
ok 26 - CPU0: Done - Errors: 0

It should be like this：
ok 13 - pl031: Periph/PCell IDs match
ok 14 - pl031: R/O fields are R/O
ok 15 - pl031: RTC ticks at 1HZ
ok 16 - pl031: RTC IRQ not pending yet
...
ok 24 - pl031:   RTC IRQ not pending anymore
ok 25 - spinlock: CPU0: Done - Errors: 0
ok 26 - spinlock: CPU1: Done - Errors: 0

Signed-off-by: Chen Qun <kuhn.chenqun@huawei.com>
Signed-off-by: Andrew Jones <drjones@redhat.com>
---
 arm/pl031.c         | 1 +
 arm/spinlock-test.c | 1 +
 2 files changed, 2 insertions(+)

```
