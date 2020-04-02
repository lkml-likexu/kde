

#### [kvm-unit-tests PATCH 0/2] arm/arm64: Add IPI/vtimer latency
##### From: Jingyi Wang <wangjingyi11@huawei.com>

```c
From patchwork Wed Apr  1 10:08:10 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jingyi Wang <wangjingyi11@huawei.com>
X-Patchwork-Id: 11468855
Return-Path: <SRS0=PGN4=5R=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3B5D4912
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  1 Apr 2020 10:08:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 23330208FE
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  1 Apr 2020 10:08:43 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731541AbgDAKIm (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 1 Apr 2020 06:08:42 -0400
Received: from szxga06-in.huawei.com ([45.249.212.32]:36290 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726335AbgDAKIm (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 1 Apr 2020 06:08:42 -0400
Received: from DGGEMS408-HUB.china.huawei.com (unknown [172.30.72.58])
        by Forcepoint Email with ESMTP id 85F868AB10D6DBB20258;
        Wed,  1 Apr 2020 18:08:35 +0800 (CST)
Received: from DESKTOP-FPN2511.china.huawei.com (10.173.222.58) by
 DGGEMS408-HUB.china.huawei.com (10.3.19.208) with Microsoft SMTP Server id
 14.3.487.0; Wed, 1 Apr 2020 18:08:27 +0800
From: Jingyi Wang <wangjingyi11@huawei.com>
To: <drjones@redhat.com>, <kvm@vger.kernel.org>,
        <kvmarm@lists.cs.columbia.edu>
CC: <wanghaibin.wang@huawei.com>, <yuzenghui@huawei.com>,
        Jingyi Wang <wangjingyi11@huawei.com>
Subject: [kvm-unit-tests PATCH 0/2] arm/arm64: Add IPI/vtimer latency
Date: Wed, 1 Apr 2020 18:08:10 +0800
Message-ID: <20200401100812.27616-1-wangjingyi11@huawei.com>
X-Mailer: git-send-email 2.14.1.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.173.222.58]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

With the development of arm gic architecture, we think it will be useful
to add some simple performance test in kut to measure the cost of
interrupts. X86 arch has implemented similar test.

Jingyi Wang (2):
  arm/arm64: gic: Add IPI latency test
  arm/arm64: Add vtimer latency test

 arm/gic.c   | 27 +++++++++++++++++++++++++++
 arm/timer.c | 11 +++++++++++
 2 files changed, 38 insertions(+)
```
#### [PATCH 0/2] KVM: arm64: PSCI fixes
##### From: Marc Zyngier <maz@kernel.org>
X-SA-Exim-Mail-From: maz@kernel.org

```c
From patchwork Wed Apr  1 16:58:14 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11469343
Return-Path: <SRS0=PGN4=5R=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B61131668
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  1 Apr 2020 16:58:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 89F462082F
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  1 Apr 2020 16:58:32 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1585760312;
	bh=CBZKD+m/KX3im6HA1XqrNu2FJtS3v/4jycpmEZoi/q4=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=hNSQZWDr2H4+f8ACXbKy+wPrJvzxUN6rbUn9PbxcMcxhYS+Nm4EMKVVm5lioy6Dzv
	 Z9bPQFy5DBBjYTPRbXoK1/MdU/exjGhng+oUkPUDQ+OMAnSjrx+KLcmzFnsRWpx+BN
	 U26Bb+hL6q6xrvnfO5TBR1F0IqeKBr4VL6xiiM7g=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732994AbgDAQ6b (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 1 Apr 2020 12:58:31 -0400
Received: from mail.kernel.org ([198.145.29.99]:57596 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1732241AbgDAQ6b (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 1 Apr 2020 12:58:31 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id ADA822063A;
        Wed,  1 Apr 2020 16:58:30 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1585760310;
        bh=CBZKD+m/KX3im6HA1XqrNu2FJtS3v/4jycpmEZoi/q4=;
        h=From:To:Cc:Subject:Date:From;
        b=j1gug4YUthSAfCSHVZmmWwy70QFl6X5tQUOrJ5xDx3OPiLRJpn6FOp3RTBHtjjKwZ
         YQNyuXzfKl14Oq3ixq8UltLEJVl0TulMcTzLckPULcjx3SpoaQySvVZtUrzN+s4Xlb
         G7oTZPpkbKeLfB0hIzIqMNzT4uOhrY7Yn9u5ln6k=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1jJghA-00Haev-ND; Wed, 01 Apr 2020 17:58:28 +0100
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: Christoffer Dall <Christoffer.Dall@arm.com>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>
Subject: [PATCH 0/2] KVM: arm64: PSCI fixes
Date: Wed,  1 Apr 2020 17:58:14 +0100
Message-Id: <20200401165816.530281-1-maz@kernel.org>
X-Mailer: git-send-email 2.25.0
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, Christoffer.Dall@arm.com,
 james.morse@arm.com, julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Christoffer recently pointed out that we don't narrow the arguments to
SMC32 PSCI functions called by a 64bit guest. This could result in a
guest failing to boot its secondary CPUs if it had junk in the upper
32bits. Yes, this is silly, but the guest is allowed to do that. Duh.

Whist I was looking at this, it became apparent that we allow a 32bit
guest to call 64bit functions, which the spec explicitly forbids. Oh
well, another patch.

This has been lightly tested, but I feel that we could do with a new
set of PSCI corner cases in KVM-unit-tests (hint, nudge... ;-).

Marc Zyngier (2):
  KVM: arm64: PSCI: Narrow input registers when using 32bit functions
  KVM: arm64: PSCI: Forbid 64bit functions for 32bit guests

 virt/kvm/arm/psci.c | 40 ++++++++++++++++++++++++++++++++++++++++
 1 file changed, 40 insertions(+)
```
#### [PATCH v4 0/7] vhost: Reset batched descriptors on SET_VRING_BASE
##### From: =?utf-8?q?Eugenio_P=C3=A9rez?= <eperezma@redhat.com>

```c
From patchwork Wed Apr  1 18:31:11 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Eugenio Perez Martin <eperezma@redhat.com>
X-Patchwork-Id: 11469393
Return-Path: <SRS0=PGN4=5R=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9C73B1668
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  1 Apr 2020 18:31:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7A9C2206CC
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  1 Apr 2020 18:31:36 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="NZ+qupro"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1733027AbgDASbe (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 1 Apr 2020 14:31:34 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:47499 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1732880AbgDASbe (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 1 Apr 2020 14:31:34 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1585765893;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=XFWPG187HUhkSGxk00FG9TA0iVCphDpDrVtIpYx7KzE=;
        b=NZ+quproBE+kn77jrrNP2osXJPfthwFAUeKeVeWVt5WxUUwoS4GYAtJm79y7mp9kwFK4La
        KxrMkDWpbjl0ztddfI1JumIY+oPfeR0Mgu+kY15/dcgSmZ5Vl5MD3sHP3Mt56vBvVOg2Y2
        7LzRSCd9b3rXMYAw2+BprMmDTsTKh6k=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-200-o8ufVN_IPVGhpVSDAjVHrw-1; Wed, 01 Apr 2020 14:31:29 -0400
X-MC-Unique: o8ufVN_IPVGhpVSDAjVHrw-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 9962918C8C19;
        Wed,  1 Apr 2020 18:31:27 +0000 (UTC)
Received: from eperezma.remote.csb (ovpn-113-73.ams2.redhat.com
 [10.36.113.73])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 0887196F83;
        Wed,  1 Apr 2020 18:31:22 +0000 (UTC)
From: =?utf-8?q?Eugenio_P=C3=A9rez?= <eperezma@redhat.com>
To: "Michael S. Tsirkin" <mst@redhat.com>
Cc: "virtualization@lists.linux-foundation.org"
  <virtualization@lists.linux-foundation.org>,
 =?utf-8?q?Eugenio_P=C3=A9rez?= <eperezma@redhat.com>,
 Linux Next Mailing List <linux-next@vger.kernel.org>,
 Stephen Rothwell <sfr@canb.auug.org.au>, kvm list <kvm@vger.kernel.org>,
 Halil Pasic <pasic@linux.ibm.com>,
 "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>,
 Cornelia Huck <cohuck@redhat.com>,
 Christian Borntraeger <borntraeger@de.ibm.com>
Subject: [PATCH v4 0/7] vhost: Reset batched descriptors on SET_VRING_BASE
 call
Date: Wed,  1 Apr 2020 20:31:11 +0200
Message-Id: <20200401183118.8334-1-eperezma@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Vhost did not reset properly the batched descriptors on SET_VRING_BASE
event. Because of that, is possible to return an invalid descriptor to
the guest.

This series ammend this, resetting them every time backend changes, and
creates a test to assert correct behavior. To do that, they need to
expose a new function in virtio_ring, virtqueue_reset_free_head, only
on test code.

Another useful thing would be to check if mutex is properly get in
vq private_data accessors. Not sure if mutex debug code allow that,
similar to C++ unique lock::owns_lock. Not acquiring in the function
because caller code holds the mutex in order to perform more actions.

v4:
* Rebase with vhost_iotlb changes.

v3:
* Rename accesors functions.
* Make scsi and test use the accesors too.

v2:
* Squashed commits.
* Create vq private_data accesors (mst).

This serie is meant to be applied on top of
38dd2ba72ece18ec8398c8ddd13cfb02870b0309 in
git.kernel.org/pub/scm/linux/kernel/git/mst/vhost.git.

Eugenio Pérez (4):
  tools/virtio: Add --batch option
  tools/virtio: Add --batch=random option
  tools/virtio: Add --reset=random
  tools/virtio: Make --reset reset ring idx

Michael S. Tsirkin (3):
  vhost: option to fetch descriptors through an independent struct
  vhost: use batched version by default
  vhost: batching fetches

 drivers/vhost/test.c         |  59 +++++++-
 drivers/vhost/test.h         |   1 +
 drivers/vhost/vhost.c        | 271 +++++++++++++++++++++++------------
 drivers/vhost/vhost.h        |  17 ++-
 drivers/virtio/virtio_ring.c |  29 ++++
 tools/virtio/linux/virtio.h  |   2 +
 tools/virtio/virtio_test.c   | 123 ++++++++++++++--
 7 files changed, 395 insertions(+), 107 deletions(-)
```
#### [PATCH v5 0/3] SELinux support for anonymous inodes and UFFD
##### From: Daniel Colascione <dancol@google.com>

```c
From patchwork Wed Apr  1 21:39:00 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Daniel Colascione <dancol@google.com>
X-Patchwork-Id: 11469575
Return-Path: <SRS0=PGN4=5R=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 17078912
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  1 Apr 2020 21:39:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E62B520772
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  1 Apr 2020 21:39:13 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="HtoDxjxy"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1733134AbgDAVjN (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 1 Apr 2020 17:39:13 -0400
Received: from mail-pg1-f202.google.com ([209.85.215.202]:47455 "EHLO
        mail-pg1-f202.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1732385AbgDAVjM (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 1 Apr 2020 17:39:12 -0400
Received: by mail-pg1-f202.google.com with SMTP id x1so1167266pgb.14
        for <kvm@vger.kernel.org>; Wed, 01 Apr 2020 14:39:12 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=HAGgUYyHHln+iAOn6yXYvlgWPJe/4zWvRIw0PRHR3XY=;
        b=HtoDxjxyzs5b33ZeGM32Er5kRybPkg8YGOpir27RQ+bUpw6BX/dsJ2vwWdB3AAxCmG
         bjMfAIMdlb4UR1AIOIFCN+uc1kmAxsGNUeUv/O7Of7mXZUnwD7KGKYartbCqcARuZu5S
         pfkX1UGvumlx5lTd6PNZtdcgvvGSJ7bd4ydHOqBQDCYH8LMYmqHxRXGVp/ZzYI03Cvnf
         V4GJQtkEQ2I/BOGpkkbnC2McxJw07GBcQ5N+j9kMTmPQ3mXOmGip3EI4TVF0z+UmDcdV
         yHb87MmDuy1wgu53qGGYxbpjE5SRwjOxs4/Vz56t9Aqd6UVnoio9UyUMS51Lxck57Al/
         2iVg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=HAGgUYyHHln+iAOn6yXYvlgWPJe/4zWvRIw0PRHR3XY=;
        b=KgBlm3OuZ4XG33w1zvEtJS8rpM8w/NtoUqn+mHpcQJdZQkin7znpGNk8v650S+rfrr
         O88Js63xYCZErosQJgdudYMwJcP91zk9tqivfqLBzoHKYZAfV7wO4zUPJVBXLrAamVG1
         en+3v3KnylOtOeWxybs1sOCOwE+4Gka9NIHPcYlLubceNSROW+7FGyd2kjDPZqFQHQJN
         ycjhxL/dxtYYdfelA7H4E0fd2djul+rSVhOuFntS5EFShP+NLVJryOtJH3S1zHd9WLey
         cvpxm23cRKRpu+40CoQ0aIXXNRbU8TSrNAN0ilt9k7FmDLo+VrI7odMaQCdhoz1SwFj2
         ByCA==
X-Gm-Message-State: AGi0PuZkjsqILxvNfm7/ILPBeeZEuVa8TBmXvyMUpIEV0APKB3AMKvpo
        bl+DgTdxPGMQkJIco04qOygrt0W106U=
X-Google-Smtp-Source: 
 APiQypJ3mXXgEz84cKvOfB4JITXTTQgCH9bS0I77D6jC/rreVESODIDpq8LIxGqLwRsYwdoGgUvE2wVKYE8=
X-Received: by 2002:a17:90b:3583:: with SMTP id
 mm3mr13268pjb.123.1585777151523;
 Wed, 01 Apr 2020 14:39:11 -0700 (PDT)
Date: Wed,  1 Apr 2020 14:39:00 -0700
In-Reply-To: <20200326200634.222009-1-dancol@google.com>
Message-Id: <20200401213903.182112-1-dancol@google.com>
Mime-Version: 1.0
References: <20200326200634.222009-1-dancol@google.com>
X-Mailer: git-send-email 2.26.0.rc2.310.g2932bb562d-goog
Subject: [PATCH v5 0/3] SELinux support for anonymous inodes and UFFD
From: Daniel Colascione <dancol@google.com>
To: timmurray@google.com, selinux@vger.kernel.org,
        linux-security-module@vger.kernel.org,
        linux-fsdevel@vger.kernel.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, viro@zeniv.linux.org.uk, paul@paul-moore.com,
        nnk@google.com, sds@tycho.nsa.gov, lokeshgidra@google.com,
        jmorris@namei.org
Cc: Daniel Colascione <dancol@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Userfaultfd in unprivileged contexts could be potentially very
useful. We'd like to harden userfaultfd to make such unprivileged use
less risky. This patch series allows SELinux to manage userfaultfd
file descriptors and in the future, other kinds of
anonymous-inode-based file descriptor.  SELinux policy authors can
apply policy types to anonymous inodes by providing name-based
transition rules keyed off the anonymous inode internal name (
"[userfaultfd]" in the case of userfaultfd(2) file descriptors) and
applying policy to the new SIDs thus produced.

Inside the kernel, a pair of new anon_inodes interface,
anon_inode_getfile_secure and anon_inode_getfd_secure, allow callers
to opt into this SELinux management. In this new "secure" mode,
anon_inodes creates new ephemeral inodes for anonymous file objects
instead of reusing the normal anon_inodes singleton dummy inode. A new
LSM hook gives security modules an opportunity to configure and veto
these ephemeral inodes.

This patch series is one of two fork of [1] and is an
alternative to [2].

The primary difference between the two patch series is that this
partch series creates a unique inode for each "secure" anonymous
inode, while the other patch series ([2]) continues using the
singleton dummy anonymous inode and adds a way to attach SELinux
security information directly to file objects.

I prefer the approach in this patch series because 1) it's a smaller
patch than [2], and 2) it produces a more regular security
architecture: in this patch series, secure anonymous inodes aren't
S_PRIVATE and they maintain the SELinux property that the label for a
file is in its inode. We do need an additional inode per anonymous
file, but per-struct-file inode creation doesn't seem to be a problem
for pipes and sockets.

The previous version of this feature ([1]) created a new SELinux
security class for userfaultfd file descriptors. This version adopts
the generic transition-based approach of [2].

This patch series also differs from [2] in that it doesn't affect all
anonymous inodes right away --- instead requiring anon_inodes callers
to opt in --- but this difference isn't one of basic approach. The
important question to resolve is whether we should be creating new
inodes or enhancing per-file data.

Changes from the first version of the patch:

  - Removed some error checks
  - Defined a new anon_inode SELinux class to resolve the
    ambiguity in [3]
  - Inherit sclass as well as descriptor from context inode

Changes from the second version of the patch:

  - Fixed example policy in the commit message to reflect the use of
    the new anon_inode class.

Changes from the third version of the patch:

  - Dropped the fops parameter to the LSM hook
  - Documented hook parameters
  - Fixed incorrect class used for SELinux transition
  - Removed stray UFFD changed early in the series
  - Removed a redundant ERR_PTR(PTR_ERR())

Changes from the fourth version of the patch:

  - Removed an unused parameter from an internal function
  - Fixed function documentation

[1] https://lore.kernel.org/lkml/20200211225547.235083-1-dancol@google.com/
[2] https://lore.kernel.org/linux-fsdevel/20200213194157.5877-1-sds@tycho.nsa.gov/
[3] https://lore.kernel.org/lkml/23f725ca-5b5a-5938-fcc8-5bbbfc9ba9bc@tycho.nsa.gov/

Daniel Colascione (3):
  Add a new LSM-supporting anonymous inode interface
  Teach SELinux about anonymous inodes
  Wire UFFD up to SELinux

 fs/anon_inodes.c                    | 191 ++++++++++++++++++++++------
 fs/userfaultfd.c                    |  30 ++++-
 include/linux/anon_inodes.h         |  13 ++
 include/linux/lsm_hooks.h           |  11 ++
 include/linux/security.h            |   3 +
 security/security.c                 |   9 ++
 security/selinux/hooks.c            |  53 ++++++++
 security/selinux/include/classmap.h |   2 +
 8 files changed, 267 insertions(+), 45 deletions(-)
```
