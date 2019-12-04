#### [PATCH 4.19 242/321] kvm: properly check debugfs dentry before using it
##### From: Greg Kroah-Hartman <gregkh@linuxfoundation.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Greg Kroah-Hartman <gregkh@linuxfoundation.org>
X-Patchwork-Id: 11271943
Return-Path: <SRS0=eZxF=ZZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7B6AD930
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  3 Dec 2019 23:01:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 579F9207DD
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  3 Dec 2019 23:01:45 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1575414105;
	bh=E0sg7lpUyL7wlDReSjiLpi7Lh69WU5Wh/tgGnAYTUWY=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=aoROr0UM5LJ2rv22ajiUg5737wNPKsnCkCrqjrEXm2k+/kWqM7rEIehJFPvA9pWfw
	 BZo4jkK5Tq2NMbQ5SfT3KAEs4LczgYEgtfEqEB556PdYnLs1CFbRhZe/eMLtFjZ7kB
	 D02oKyEOay3FXaubuVhwp+WJfNdRm1luJ2vNTAH4=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730370AbfLCWzk (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 3 Dec 2019 17:55:40 -0500
Received: from mail.kernel.org ([198.145.29.99]:50136 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1730366AbfLCWzj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 3 Dec 2019 17:55:39 -0500
Received: from localhost (83-86-89-107.cable.dynamic.v4.ziggo.nl
 [83.86.89.107])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 1DB692053B;
        Tue,  3 Dec 2019 22:55:37 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1575413738;
        bh=E0sg7lpUyL7wlDReSjiLpi7Lh69WU5Wh/tgGnAYTUWY=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=EcvGsBeVWZAxtGbPd9NO+XarI8y0MWOw/UFbZAdY6ghP4leiDEJhwpA7F9CcBGWEi
         LbM3XH0stFbZ2Ko1y4VYCqrCKoaudqqSdt5fOwX0YdEXXbvOrGwzX33o9B521IbpTR
         9X+p+C5KlpM9rPcOgGZb6F8ByLmYrpDE+mePB0+U=
From: Greg Kroah-Hartman <gregkh@linuxfoundation.org>
To: linux-kernel@vger.kernel.org
Cc: Greg Kroah-Hartman <gregkh@linuxfoundation.org>, stable@vger.kernel.org,
 Eric Biggers <ebiggers@kernel.org>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>, kvm@vger.kernel.org,
 Paolo Bonzini <pbonzini@redhat.com>,
 Linus Torvalds <torvalds@linux-foundation.org>,
 Sasha Levin <sashal@kernel.org>,
 syzbot+7857962b4d45e602b8ad@syzkaller.appspotmail.com
Subject: [PATCH 4.19 242/321] kvm: properly check debugfs dentry before using
 it
Date: Tue,  3 Dec 2019 23:35:08 +0100
Message-Id: <20191203223439.731003476@linuxfoundation.org>
X-Mailer: git-send-email 2.24.0
In-Reply-To: <20191203223427.103571230@linuxfoundation.org>
References: <20191203223427.103571230@linuxfoundation.org>
User-Agent: quilt/0.66
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Greg Kroah-Hartman <gregkh@linuxfoundation.org>

[ Upstream commit 8ed0579c12b2fe56a1fac2f712f58fc26c1dc49b ]

debugfs can now report an error code if something went wrong instead of
just NULL.  So if the return value is to be used as a "real" dentry, it
needs to be checked if it is an error before dereferencing it.

This is now happening because of ff9fb72bc077 ("debugfs: return error
values, not NULL").  syzbot has found a way to trigger multiple debugfs
files attempting to be created, which fails, and then the error code
gets passed to dentry_path_raw() which obviously does not like it.

Reported-by: Eric Biggers <ebiggers@kernel.org>
Reported-and-tested-by: syzbot+7857962b4d45e602b8ad@syzkaller.appspotmail.com
Cc: "Radim Krčmář" <rkrcmar@redhat.com>
Cc: kvm@vger.kernel.org
Acked-by: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Greg Kroah-Hartman <gregkh@linuxfoundation.org>
Signed-off-by: Linus Torvalds <torvalds@linux-foundation.org>
Signed-off-by: Sasha Levin <sashal@kernel.org>
---
 virt/kvm/kvm_main.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] KVM: Remove duplicated declaration of kvm_vcpu_kick
##### From: Zenghui Yu <yuzenghui@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zenghui Yu <yuzenghui@huawei.com>
X-Patchwork-Id: 11270705
Return-Path: <SRS0=eZxF=ZZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 891DA6C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  3 Dec 2019 07:45:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 6F72E20726
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  3 Dec 2019 07:45:01 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727497AbfLCHo4 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 3 Dec 2019 02:44:56 -0500
Received: from szxga04-in.huawei.com ([45.249.212.190]:7192 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1727459AbfLCHoz (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 3 Dec 2019 02:44:55 -0500
Received: from DGGEMS405-HUB.china.huawei.com (unknown [172.30.72.58])
        by Forcepoint Email with ESMTP id 2F25094BB710449FBC82;
        Tue,  3 Dec 2019 15:44:53 +0800 (CST)
Received: from DESKTOP-8RFUVS3.china.huawei.com (10.173.222.27) by
 DGGEMS405-HUB.china.huawei.com (10.3.19.205) with Microsoft SMTP Server id
 14.3.439.0; Tue, 3 Dec 2019 15:44:46 +0800
From: Zenghui Yu <yuzenghui@huawei.com>
To: <pbonzini@redhat.com>, <rkrcmar@redhat.com>
CC: <kvm@vger.kernel.org>, <linux-kernel@vger.kernel.org>,
        <wanghaibin.wang@huawei.com>, Zenghui Yu <yuzenghui@huawei.com>
Subject: [PATCH] KVM: Remove duplicated declaration of kvm_vcpu_kick
Date: Tue, 3 Dec 2019 15:44:08 +0800
Message-ID: <20191203074408.1758-1-yuzenghui@huawei.com>
X-Mailer: git-send-email 2.23.0.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.173.222.27]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

There are two declarations of kvm_vcpu_kick() in kvm_host.h where
one of them is redundant. Remove to keep the git grep a bit cleaner.

Signed-off-by: Zenghui Yu <yuzenghui@huawei.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---
 include/linux/kvm_host.h | 1 -
 1 file changed, 1 deletion(-)

```
#### [PATCH kvm-unit-tests] svm: Verify the effect of V_INTR_MASKING on INTR interrupts
##### From: Cathy Avery <cavery@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Cathy Avery <cavery@redhat.com>
X-Patchwork-Id: 11271287
Return-Path: <SRS0=eZxF=ZZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6B0B4112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  3 Dec 2019 13:24:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4A90C2073C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  3 Dec 2019 13:24:34 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Q+L58909"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726254AbfLCNYd (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 3 Dec 2019 08:24:33 -0500
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:36785 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726105AbfLCNYd (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 3 Dec 2019 08:24:33 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1575379472;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=yUz5V0ICOk8/qnlm76z0FyFQ5SAkIpNDEqdcHIvOkpU=;
        b=Q+L58909qNG2y7HZfgX8EquoFzgXtQvRMCL0IV6nAbsUoMwwWgdKSMzVwt3wA0sca2JJV9
        xFCO0ol2xsfYj3IYkMwWXcOKPoME1zQ32wXtj/BPMshlmT4Lte6rAjAV5wNWfdXvTuntb0
        6YyeHGPoq5YJCdXUYz30VPdOkdtCKec=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-203-shKdd1JhOeWQn_ocK_BOug-1; Tue, 03 Dec 2019 08:24:28 -0500
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id E768F107ACC4
        for <kvm@vger.kernel.org>; Tue,  3 Dec 2019 13:24:27 +0000 (UTC)
Received: from localhost.localdomain.com (ovpn-121-180.rdu2.redhat.com
 [10.10.121.180])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 7B41919C68;
        Tue,  3 Dec 2019 13:24:27 +0000 (UTC)
From: Cathy Avery <cavery@redhat.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com
Subject: [PATCH kvm-unit-tests] svm: Verify the effect of V_INTR_MASKING on
 INTR interrupts
Date: Tue,  3 Dec 2019 08:24:26 -0500
Message-Id: <20191203132426.21244-1-cavery@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
X-MC-Unique: shKdd1JhOeWQn_ocK_BOug-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The test confirms the influence of the V_INTR_MASKING bit
on RFLAGS.IF. The expectation is while running a guest
with V_INTR_MASKING cleared to zero:

- EFLAGS.IF controls both virtual and physical interrupts.

While running a guest with V_INTR_MASKING set to 1:

- The host EFLAGS.IF at the time of the VMRUN is saved and
  controls physical interrupts while the guest is running.

- The guest value of EFLAGS.IF controls virtual interrupts only.

As discussed previously, this patch also modifies the vmrun
loop ( test_run ) to allow running with HIF=0

Signed-off-by: Cathy Avery <cavery@redhat.com>
---
 x86/svm.c | 106 ++++++++++++++++++++++++++++++++++++++++++++++++++++--
 1 file changed, 104 insertions(+), 2 deletions(-)

```
#### [PATCH kvm-unit-tests v2] svm: Verify the effect of V_INTR_MASKING on INTR interrupts
##### From: Cathy Avery <cavery@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Cathy Avery <cavery@redhat.com>
X-Patchwork-Id: 11271573
Return-Path: <SRS0=eZxF=ZZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 96B00138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  3 Dec 2019 16:25:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 747C9206EC
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  3 Dec 2019 16:25:38 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="bJfW38MX"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726645AbfLCQZh (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 3 Dec 2019 11:25:37 -0500
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:52027 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726319AbfLCQZh (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 3 Dec 2019 11:25:37 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1575390336;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=7gp/NLDCHcPBD7rTXpXJJ7UH2Y3VhuqxCT8Tk+uSXDc=;
        b=bJfW38MX9V+G2cXjA4pJrBQUu/NdjkcVIVg58uNp5jlWqEwXvjU1GFD/i58xudyFQnMhEu
        nNsZBhkbn/1O6k4HsWg0j3ergAuv+KSEAyV3NhaiNwfM2HIW8L5pBF7pmaUntaROZzd30P
        MuQVTtaMYXq+IZlOIltBSErKo2JlOs4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-35-HUL4w6-mOSKNPFPUgCa3sw-1; Tue, 03 Dec 2019 11:25:35 -0500
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 2E61C18A07C1
        for <kvm@vger.kernel.org>; Tue,  3 Dec 2019 16:25:34 +0000 (UTC)
Received: from localhost.localdomain.com (ovpn-121-180.rdu2.redhat.com
 [10.10.121.180])
        by smtp.corp.redhat.com (Postfix) with ESMTP id B71F1600C8;
        Tue,  3 Dec 2019 16:25:33 +0000 (UTC)
From: Cathy Avery <cavery@redhat.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com
Subject: [PATCH kvm-unit-tests v2] svm: Verify the effect of V_INTR_MASKING on
 INTR interrupts
Date: Tue,  3 Dec 2019 11:25:32 -0500
Message-Id: <20191203162532.24209-1-cavery@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
X-MC-Unique: HUL4w6-mOSKNPFPUgCa3sw-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The test confirms the influence of the V_INTR_MASKING bit
on RFLAGS.IF. The expectation is while running a guest
with V_INTR_MASKING cleared to zero:

- EFLAGS.IF controls both virtual and physical interrupts.

While running a guest with V_INTR_MASKING set to 1:

- The host EFLAGS.IF at the time of the VMRUN is saved and
  controls physical interrupts while the guest is running.

- The guest value of EFLAGS.IF controls virtual interrupts only.

As discussed previously, this patch also modifies the vmrun
loop ( test_run ) to allow running with HIF=0

Signed-off-by: Cathy Avery <cavery@redhat.com>
---

v2: Added suggested changes to set_host_if etc.
---
 x86/svm.c | 105 ++++++++++++++++++++++++++++++++++++++++++++++++++++--
 1 file changed, 103 insertions(+), 2 deletions(-)

```
#### [PATCH] kvm: vmx: Stop wasting a page for guest_msrsFrom: Jim Mattson <jmattson@google.com>
##### From: Jim Mattson <jmattson@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jim Mattson <jmattson@google.com>
X-Patchwork-Id: 11271909
Return-Path: <SRS0=eZxF=ZZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A4A0F112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  3 Dec 2019 21:08:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7D64820833
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  3 Dec 2019 21:08:31 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="gHZaPldS"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727483AbfLCVIa (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 3 Dec 2019 16:08:30 -0500
Received: from mail-pg1-f201.google.com ([209.85.215.201]:42493 "EHLO
        mail-pg1-f201.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727416AbfLCVIa (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 3 Dec 2019 16:08:30 -0500
Received: by mail-pg1-f201.google.com with SMTP id x189so2317450pgd.9
        for <kvm@vger.kernel.org>; Tue, 03 Dec 2019 13:08:30 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=DASVXSs5oWILH0sAvzGTTCKaB1RC91AoYiNLZyw2dxI=;
        b=gHZaPldSI9LEKFQ/ihgZl1LgWH5jVT3dO0odaKXcPGrstFHtODiy+L2QmfdAtImI86
         Z6dpEqR4MivzNR1to2+1UJbAXaZp+SQxYSFpPVRJyFtC+IwPKTTmLnvtD3CHwI2TII2N
         ufasLwR43qkTiAxEtrJP2zdKjcj8ICmpiTCESgtK1tWpLk7D8/RZ7NeDt8BqjgzI0oEF
         +woZg4+8XwIdg8jAOfA29TUgZ5jZquT6rjrZVe9Vr5M4NvWNDfCHJ4ndvRtYXFs8YgcR
         N6DfTGX2I1MRblm/F3rirWAp3Gpr/CwgXm6JcSi4nrdrcN4Yx7HBWoN0nylYYmKcar2t
         Vhzw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=DASVXSs5oWILH0sAvzGTTCKaB1RC91AoYiNLZyw2dxI=;
        b=Cli8v+yz9JDPw4RXE4UFxIDS2S1H2p+loraXmAh5/nQz3GCEZCaGKeZ7VPCkqYO0k/
         GPUiMgcUQe/vC0y4qaM5lFTG69LnvThbwTjPN0zLxeiJ3q00V8HsJuXjM5b5ApV0TPwV
         0cboxiMEIUZSzt1QoTMz7TGunSrfzgHMtXHpvuGpxDgvQE5hl+IVz1KrkaUxBPWH1c3d
         7N79qiofJv8EFHcbm5r/2kIhQD8z5g1D1I6Y/IX2oH/qnKc3dqD+X67wyg1gZeTIsDjX
         JSoaCQSQ1swBs41As082TO+k0gje66hg06Jgsl8R2HvLqlPF9lAb/BYu/PYm3+jY2Vuc
         OWSg==
X-Gm-Message-State: APjAAAUvXLXWnqWtk43PWxUaFsn89icYsbpm9cboDfaxtdMwSybyIIYY
        hitwC30IgprUSEI+fnxwQWKVW9QjTOz3AGyDsZMjXjw1JRB4mQ0XXtzgTOSgiUdgG4tDnEmMtl+
        48DLNUGELJxwxpaVn8KI+jNMJWJcaidVop8pRIWoVePvMTtNLDOL2olgfr8Em/lA=
X-Google-Smtp-Source: 
 APXvYqzDdPCX/Axm2kbMjLuWjQBtU1S0fU+UOxex/V+hWf66/Q5FtBzUMP5UAtGRCyLwP/pKA3VUgBiDs3le2g==
X-Received: by 2002:a65:66d7:: with SMTP id c23mr7740607pgw.40.1575407309430;
 Tue, 03 Dec 2019 13:08:29 -0800 (PST)
Date: Tue,  3 Dec 2019 13:08:25 -0800
Message-Id: <20191203210825.26827-1-jmattson@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.24.0.393.g34dc348eaf-goog
Subject: [PATCH] kvm: vmx: Stop wasting a page for guest_msrs
From: Jim Mattson <jmattson@google.com>
To: kvm@vger.kernel.org
Cc: Jim Mattson <jmattson@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We will never need more guest_msrs than there are indices in
vmx_msr_index. Thus, at present, the guest_msrs array will not exceed
168 bytes.

Signed-off-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Liran Alon <liran.alon@oracle.com>
---
 arch/x86/kvm/vmx/vmx.c | 14 ++------------
 arch/x86/kvm/vmx/vmx.h |  8 +++++++-
 2 files changed, 9 insertions(+), 13 deletions(-)

```
#### [PATCH v4 1/6] KVM: X86: Fix kvm_bitmap_or_dest_vcpus() to use irq shorthand
##### From: Peter Xu <peterx@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11271713
Return-Path: <SRS0=eZxF=ZZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 711F5112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  3 Dec 2019 16:59:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4EBF620803
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  3 Dec 2019 16:59:41 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Zn08heVy"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727192AbfLCQ7M (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 3 Dec 2019 11:59:12 -0500
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:49293 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1727154AbfLCQ7K (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 3 Dec 2019 11:59:10 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1575392349;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=kn/llSEPws9Kaihse6HkAcboPO6kvjhOBVqBu50kJWM=;
        b=Zn08heVy4i5cwuaWKecR8YKjhfSjACBEP5Q7tINwU0llVC8rSIY/9fpsPguox7yFDB3lsc
        rNgHpbtgxDq1m5L84HJvilI/vyLi3cKCLmKxYLaZ43LH73JevyiECp9rPPcNwNkMf5iYEb
        d7tzT6H+qAsTrNCRuPIigqdgeBUy5qA=
Received: from mail-qv1-f69.google.com (mail-qv1-f69.google.com
 [209.85.219.69]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-114-T-dleMvAO1eVjNjfE7xNJQ-1; Tue, 03 Dec 2019 11:59:08 -0500
Received: by mail-qv1-f69.google.com with SMTP id l1so2583748qvu.13
        for <kvm@vger.kernel.org>; Tue, 03 Dec 2019 08:59:07 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=qDMFszQpTCz8aKUy2p2BRtrOo8b1SfrY7qPPp6I+jnk=;
        b=g+W/jA/3/Wg4aDK+YFGj0TnyNBssjR3is37PfTMbkoQbnyM1gFXTUYhuq8UyaL+mMI
         SXiVHb/v1PYORtscaxOSD2eCuNyG7fD4mW8C0hZgOsyBuLPOOw84fMCRdauhwW0mnASZ
         3RttCGOehUeVc34b/cWd0N2qQZJcCXBbNkJcMX2sZ/9PsmseFppeoSGQoe6zJH2wRHaE
         R1w1fZXCECRTd6wn7o/sKKcZvQFqN7ROOt3y7HVtL2H/jsyrmWylWRbt7p03ugEeShbT
         iGwH594YBNCEWcFZTyDnNy4MJjNmVr6kGolOKacRi7OxJRYJb9mNfoaFoqc907tv/2r3
         OiVA==
X-Gm-Message-State: APjAAAVNM1VQHttqzRXnOMGkoXACtceXSOa2EXrWVacYYYsa1jMLr6Sd
        baQfPWX+xhrfONo7Q3eHh9o09cOKlkiPGBfy2Jjm5WiAUXSnHJmxt60YrLwI6uY+2OdMWsSq3AZ
        16ZyIcbkyoI/u
X-Received: by 2002:ac8:1017:: with SMTP id z23mr5821776qti.94.1575392347081;
        Tue, 03 Dec 2019 08:59:07 -0800 (PST)
X-Google-Smtp-Source: 
 APXvYqxg/JOE/OtM1jHS/faP8zXtfiNcD6HKzy7U3+/q3M6bfRuQ5NZYhl14b7ItPtyjdu5wi5+3bg==
X-Received: by 2002:ac8:1017:: with SMTP id z23mr5821756qti.94.1575392346887;
        Tue, 03 Dec 2019 08:59:06 -0800 (PST)
Received: from xz-x1.yyz.redhat.com ([104.156.64.74])
        by smtp.gmail.com with ESMTPSA id
 a16sm482585qkn.48.2019.12.03.08.59.05
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 03 Dec 2019 08:59:05 -0800 (PST)
From: Peter Xu <peterx@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Nitesh Narayan Lal <nitesh@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        peterx@redhat.com, Vitaly Kuznetsov <vkuznets@redhat.com>
Subject: [PATCH v4 1/6] KVM: X86: Fix kvm_bitmap_or_dest_vcpus() to use irq
 shorthand
Date: Tue,  3 Dec 2019 11:58:58 -0500
Message-Id: <20191203165903.22917-2-peterx@redhat.com>
X-Mailer: git-send-email 2.21.0
In-Reply-To: <20191203165903.22917-1-peterx@redhat.com>
References: <20191203165903.22917-1-peterx@redhat.com>
MIME-Version: 1.0
X-MC-Unique: T-dleMvAO1eVjNjfE7xNJQ-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The 3rd parameter of kvm_apic_match_dest() is the irq shorthand,
rather than the irq delivery mode.

Fixes: 7ee30bc132c6 ("KVM: x86: deliver KVM IOAPIC scan request to target vCPUs")
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Signed-off-by: Peter Xu <peterx@redhat.com>
---
 arch/x86/kvm/lapic.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v2] KVM: s390: Add new reset vcpu API
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11271561
Return-Path: <SRS0=eZxF=ZZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5146B138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  3 Dec 2019 16:21:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 399DB2080A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  3 Dec 2019 16:21:14 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726319AbfLCQVN (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 3 Dec 2019 11:21:13 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:54274 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1725848AbfLCQVN (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 3 Dec 2019 11:21:13 -0500
Received: from pps.filterd (m0098420.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 xB3GHo7Z006557
        for <kvm@vger.kernel.org>; Tue, 3 Dec 2019 11:21:12 -0500
Received: from e06smtp07.uk.ibm.com (e06smtp07.uk.ibm.com [195.75.94.103])
        by mx0b-001b2d01.pphosted.com with ESMTP id 2wnp8rqxu2-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Tue, 03 Dec 2019 11:21:11 -0500
Received: from localhost
        by e06smtp07.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Tue, 3 Dec 2019 16:21:10 -0000
Received: from b06cxnps4074.portsmouth.uk.ibm.com (9.149.109.196)
        by e06smtp07.uk.ibm.com (192.168.101.137) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Tue, 3 Dec 2019 16:21:08 -0000
Received: from d06av25.portsmouth.uk.ibm.com (d06av25.portsmouth.uk.ibm.com
 [9.149.105.61])
        by b06cxnps4074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id xB3GL6HD51577060
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 3 Dec 2019 16:21:06 GMT
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id C997C11C064;
        Tue,  3 Dec 2019 16:21:06 +0000 (GMT)
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id CFADC11C052;
        Tue,  3 Dec 2019 16:21:04 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.145.18.156])
        by d06av25.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue,  3 Dec 2019 16:21:04 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: thuth@redhat.com, david@redhat.com, borntraeger@de.ibm.com,
        mihajlov@linux.ibm.com, cohuck@redhat.com,
        linux-s390@vger.kernel.org
Subject: [PATCH v2] KVM: s390: Add new reset vcpu API
Date: Tue,  3 Dec 2019 11:20:55 -0500
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 19120316-0028-0000-0000-000003C42D3C
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19120316-0029-0000-0000-00002487480C
Message-Id: <20191203162055.3519-1-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.95,18.0.572
 definitions=2019-12-03_04:2019-12-02,2019-12-03 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxlogscore=999
 suspectscore=1 clxscore=1015 impostorscore=0 bulkscore=0 adultscore=0
 spamscore=0 phishscore=0 mlxscore=0 malwarescore=0 lowpriorityscore=0
 priorityscore=1501 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-1910280000 definitions=main-1912030123
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The architecture states that we need to reset local IRQs for all CPU
resets. Because the old reset interface did not support the normal CPU
reset we never did that.

Now that we have a new interface, let's properly clear out local IRQs
and let this commit be a reminder.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
---
 arch/s390/kvm/kvm-s390.c | 13 +++++++++++++
 include/uapi/linux/kvm.h |  4 ++++
 2 files changed, 17 insertions(+)

```
#### [PATCH v2] kvm: vmx: Pass through IA32_TSC_AUX for read iff guest has RDTSCP
##### From: Jim Mattson <jmattson@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jim Mattson <jmattson@google.com>
X-Patchwork-Id: 11271815
Return-Path: <SRS0=eZxF=ZZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CDF57930
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  3 Dec 2019 18:35:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A2A10206DF
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  3 Dec 2019 18:35:23 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="j69D55AN"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726131AbfLCSfW (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 3 Dec 2019 13:35:22 -0500
Received: from mail-pf1-f201.google.com ([209.85.210.201]:53079 "EHLO
        mail-pf1-f201.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726057AbfLCSfW (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 3 Dec 2019 13:35:22 -0500
Received: by mail-pf1-f201.google.com with SMTP id f20so2820732pfn.19
        for <kvm@vger.kernel.org>; Tue, 03 Dec 2019 10:35:21 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=M1yK6kqSKpTvb7Wty8pVnwVM+wqUB9MeH97VgIGp9/U=;
        b=j69D55AN4TGHFqbpdRfp1bluTFdRLP/XB/qiDlTPqu2D0HziOiK/GCcwrKKBi13VVB
         fuztoHP9i9J7immdBQDEfe2Oh37x5sdSUHnwfDwHgxfDOW4IksTiHLUoMJpvhE+5ik2L
         +W+ciTRonOzHVQTJZf5s81viORtMZnQTgHPQEos8fG75ODIWHlRCG4Tnl7W6sgpLX3Fq
         0OOaiNqqUm+2Fjt3O0akDgV/GqtPjJ5oREFwH8rLL0TsVvaiYYnZS7wX5Cea/6oi/Tbt
         qkv79NUs8Yyxdyx3cm0n8DhLr/PiRNpcIzLGeEaq329h8mVcnApVLyr7+5rQE5QEBAHC
         m5Ow==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=M1yK6kqSKpTvb7Wty8pVnwVM+wqUB9MeH97VgIGp9/U=;
        b=UYVi6i8+V5pr94HmlOQ4LvqkoG0t7l6wSq4XrGRxt8569fmgTQQjxAYjDe6d/ceLIE
         cQJhvxFvlaM/VYJL+lJ0eyMlmJIQ4hPm5UfQ4ei5lb4ubOwUMmztH21ZOXTh9UVQ+aLm
         VpRMOll3mdhkYdeTdWZwOQ9qs4uwx8q1h+v6XCLKkz4f5Ls+3bx4bkoOzarHbR2B2Pgr
         lQi48JJxRlIpBCexnm9Yuwa4Ou+MUAAgYcpd+5J/hx8UUGPMa2mudvXG+qpvW0MCUZYf
         Smus9LQBsB4ZIlXUIvkaP/N1bGRBhIif5csPihUckA6phuie6AqIzpmzfkHYWM/GPhtD
         MEXA==
X-Gm-Message-State: APjAAAVDW3Mk8sVOuV/BmK0GxbnBWxkoBMkvMafE9nzP/dh1w/aTXyv8
        rjJyTYg3orMW2X1sFiZ8DIlSSRbMAOsV0Jk5LAGd596xubVPlfcgdsWXjPUTCWrHU/gLL67llC+
        M3bgLxe3igUk7gBw1TW6yHPxnWzlvJ1+sDI859iYdXn3RlMFyo/qGmdKhM95b8Fg=
X-Google-Smtp-Source: 
 APXvYqyy06Xi9zE4HNDi5LLlMDDO5wISf9UXaY1EhFLIfZDQ8cL7mC8BffErVYM/soOyeg9CJUtiTIG/kC5O4w==
X-Received: by 2002:a63:2fc4:: with SMTP id v187mr6754444pgv.55.1575398121159;
 Tue, 03 Dec 2019 10:35:21 -0800 (PST)
Date: Tue,  3 Dec 2019 10:35:12 -0800
Message-Id: <20191203183512.146618-1-jmattson@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.24.0.393.g34dc348eaf-goog
Subject: [PATCH v2] kvm: vmx: Pass through IA32_TSC_AUX for read iff guest has
 RDTSCP
From: Jim Mattson <jmattson@google.com>
To: kvm@vger.kernel.org
Cc: Jim Mattson <jmattson@google.com>, Marc Orr <marcorr@google.com>,
        Peter Shier <pshier@google.com>,
        Krish Sadhukhan <krish.sadhukhan@oracle.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If the guest supports RDTSCP, it already has read access to the
hardware IA32_TSC_AUX MSR via RDTSCP, so we can allow it read access
via the RDMSR instruction as well. If the guest doesn't support
RDTSCP, intercept all accesses to the IA32_TSC_AUX MSR, so that kvm
can synthesize a #GP.  (IA32_TSC_AUX exists iff RDTSCP is supported.)

Signed-off-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Marc Orr <marcorr@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
Reviewed-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
Reviewed-by: Liran Alon <liran.alon@oracle.com>
---
v1 -> v2: Rebased across vmx directory creation.
          Modified commit message based on Sean's comments.

 arch/x86/kvm/vmx/vmx.c | 4 ++++
 1 file changed, 4 insertions(+)

```
#### [PATCH v3 11/12] samples: vfio-mdev: constify fb ops
##### From: Jani Nikula <jani.nikula@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jani Nikula <jani.nikula@intel.com>
X-Patchwork-Id: 11271687
Return-Path: <SRS0=eZxF=ZZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 15F04186E
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  3 Dec 2019 16:40:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id F2BD6205ED
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  3 Dec 2019 16:40:13 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727120AbfLCQkN (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 3 Dec 2019 11:40:13 -0500
Received: from mga02.intel.com ([134.134.136.20]:45679 "EHLO mga02.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726186AbfLCQkM (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 3 Dec 2019 11:40:12 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga007.fm.intel.com ([10.253.24.52])
  by orsmga101.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 03 Dec 2019 08:40:12 -0800
X-IronPort-AV: E=Sophos;i="5.69,273,1571727600";
   d="scan'208";a="208533501"
Received: from jnikula-mobl3.fi.intel.com (HELO localhost) ([10.237.66.161])
  by fmsmga007-auth.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 03 Dec 2019 08:40:09 -0800
From: Jani Nikula <jani.nikula@intel.com>
To: dri-devel@lists.freedesktop.org, linux-fbdev@vger.kernel.org
Cc: intel-gfx@lists.freedesktop.org, jani.nikula@intel.com,
        Kirti Wankhede <kwankhede@nvidia.com>, kvm@vger.kernel.org,
        Daniel Vetter <daniel.vetter@ffwll.ch>
Subject: [PATCH v3 11/12] samples: vfio-mdev: constify fb ops
Date: Tue,  3 Dec 2019 18:38:53 +0200
Message-Id: 
 <ddb10df1316ef585930cda7718643a580f4fe37b.1575390741.git.jani.nikula@intel.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <cover.1575390740.git.jani.nikula@intel.com>
References: <cover.1575390740.git.jani.nikula@intel.com>
MIME-Version: 1.0
Organization: Intel Finland Oy - BIC 0357606-4 - Westendinkatu 7, 02160 Espoo
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Now that the fbops member of struct fb_info is const, we can start
making the ops const as well.

v2: fix	typo (Christophe de Dinechin)

Cc: Kirti Wankhede <kwankhede@nvidia.com>
Cc: kvm@vger.kernel.org
Reviewed-by: Daniel Vetter <daniel.vetter@ffwll.ch>
Signed-off-by: Jani Nikula <jani.nikula@intel.com>
---
 samples/vfio-mdev/mdpy-fb.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
