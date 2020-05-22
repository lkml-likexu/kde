#### [GIT PULL] vhost/vdpa: minor fixes
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 11563721
Return-Path: <SRS0=9zq6=7D=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 64D0B1392
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 21 May 2020 18:08:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4C1B220823
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 21 May 2020 18:08:49 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="AwaSGcsE"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729382AbgEUSIs (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 21 May 2020 14:08:48 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:24329 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1728455AbgEUSIq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 21 May 2020 14:08:46 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1590084524;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type;
        bh=CSwVUGMdm1SF/JKvVgrgcJwpikT7dcnsVODRPnenSIQ=;
        b=AwaSGcsE7chVA8hMIziG7fqggYULAnw5C+/8wc4ozWIMOrCSmlOQxM8hW3fBzoNxHtUQFk
        HgT1+YRKn3ZJFgAhhwzW1tvN0kIYNc9n4gMYwas2wYFNHjlBLWuiWdumx9p1kdkT43jeg2
        1ZuAHCDko7riyCWMjUB0L/kef77eRJI=
Received: from mail-wr1-f70.google.com (mail-wr1-f70.google.com
 [209.85.221.70]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-443-DWmaO1oqPBCXHcY75imMGg-1; Thu, 21 May 2020 14:08:42 -0400
X-MC-Unique: DWmaO1oqPBCXHcY75imMGg-1
Received: by mail-wr1-f70.google.com with SMTP id h12so3235010wrr.19
        for <kvm@vger.kernel.org>; Thu, 21 May 2020 11:08:39 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:mime-version
         :content-disposition;
        bh=CSwVUGMdm1SF/JKvVgrgcJwpikT7dcnsVODRPnenSIQ=;
        b=lJyE+qs+Vg1npAQaXUyxlsIg1af4xMHq6kN17nAo9UV9r7aSLAyDWk267lUKM+kds2
         d7nlOaVgNXIZ2lf51sbb+pPBhDuSwNeldsjHNA6BWAMql1vJObhr2s0uIRdTqVrkhgg3
         5IzRKx7abTNmiIi+yXbF3b1FSgnZSmkKwFOh7G2ltsaNVkPIGVSJKF3PJqsJ6Ewe3r3L
         X6aa+i9vEbcTGPHV+k/ebs9SPDrGsQtlNaDDHF82V6XMUT37W9S4p13kkgiKKVJ7OIxR
         B3VKBt2gnb6AkGvpESxW6GHqQBtAi3J/nxMiRw6eNPznrXvw+EoH8lWjk6QCawyTE+OZ
         nCRA==
X-Gm-Message-State: AOAM532OSQu72E4Bb/1LGMJYMbqmbaxM/SQQ1ovpToxTJg7HOs7DnyRR
        OsrMBu/9ojXerI1d5Kn43uaR7Ed9H66EZe/kOvyBMpUwMFa/lVg2vNm0u64BKeOIowzJLUj3L1B
        IToYY3S1x4owX
X-Received: by 2002:a5d:6087:: with SMTP id w7mr10437015wrt.158.1590084518725;
        Thu, 21 May 2020 11:08:38 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJxZ9o08gBH7tx0yYBsN8onaJW/OLPfFqqFDCwm2ORoSsfevxSpfrqifuC4Sj9PcOKKkhR/Jqg==
X-Received: by 2002:a5d:6087:: with SMTP id w7mr10436991wrt.158.1590084518323;
        Thu, 21 May 2020 11:08:38 -0700 (PDT)
Received: from redhat.com (bzq-109-64-41-91.red.bezeqint.net. [109.64.41.91])
        by smtp.gmail.com with ESMTPSA id
 j1sm7269700wrm.40.2020.05.21.11.08.36
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 21 May 2020 11:08:37 -0700 (PDT)
Date: Thu, 21 May 2020 14:08:35 -0400
From: "Michael S. Tsirkin" <mst@redhat.com>
To: Linus Torvalds <torvalds@linux-foundation.org>
Cc: kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org, linux-kernel@vger.kernel.org,
        jasowang@redhat.com, lkp@intel.com, mst@redhat.com,
        yuehaibing@huawei.com
Subject: [GIT PULL] vhost/vdpa: minor fixes
Message-ID: <20200521140835-mutt-send-email-mst@kernel.org>
MIME-Version: 1.0
Content-Disposition: inline
X-Mutt-Fcc: =sent
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The following changes since commit 0b841030625cde5f784dd62aec72d6a766faae70:

  vhost: vsock: kick send_pkt worker once device is started (2020-05-02 10:28:21 -0400)

are available in the Git repository at:

  https://git.kernel.org/pub/scm/linux/kernel/git/mst/vhost.git tags/for_linus

for you to fetch changes up to 1b0be99f1a426d9f17ced95c4118c6641a2ff13d:

  vhost: missing __user tags (2020-05-15 11:36:31 -0400)

----------------------------------------------------------------
virtio: build warning fixes

Fix a couple of build warnings.

Signed-off-by: Michael S. Tsirkin <mst@redhat.com>

----------------------------------------------------------------
Michael S. Tsirkin (1):
      vhost: missing __user tags

YueHaibing (1):
      vdpasim: remove unused variable 'ret'

 drivers/vdpa/vdpa_sim/vdpa_sim.c | 15 +++++++--------
 drivers/vhost/vhost.c            |  4 ++--
 2 files changed, 9 insertions(+), 10 deletions(-)
```
#### linux-next: build failure after merge of the kvm tree
##### From: Stephen Rothwell <sfr@canb.auug.org.au>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stephen Rothwell <sfr@canb.auug.org.au>
X-Patchwork-Id: 11562299
Return-Path: <SRS0=9zq6=7D=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C57EF912
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 21 May 2020 06:29:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AA2A120829
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 21 May 2020 06:29:01 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=canb.auug.org.au header.i=@canb.auug.org.au
 header.b="YQmRuFQ2"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728237AbgEUG27 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 21 May 2020 02:28:59 -0400
Received: from bilbo.ozlabs.org ([203.11.71.1]:51501 "EHLO ozlabs.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726938AbgEUG26 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 21 May 2020 02:28:58 -0400
Received: from authenticated.ozlabs.org (localhost [127.0.0.1])
        (using TLSv1.3 with cipher TLS_AES_256_GCM_SHA384 (256/256 bits)
         key-exchange ECDHE (P-256) server-signature RSA-PSS (4096 bits)
 server-digest SHA256)
        (No client certificate requested)
        by mail.ozlabs.org (Postfix) with ESMTPSA id 49SKT31jHSz9sT8;
        Thu, 21 May 2020 16:28:54 +1000 (AEST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=canb.auug.org.au;
        s=201702; t=1590042536;
        bh=4aGvZd/60yfG45VzmIh3YI/neYvcqholgfnSpAb2LPc=;
        h=Date:From:To:Cc:Subject:From;
        b=YQmRuFQ23F6R6pGXi6pJElvnF4hMRgCR9CD0IPF2A4giCXnuAN0gmNAtXQi5QeLaU
         JdHA0NnBj5x3Q7KadBmGZkjN60ldZHkx/1hYhvPBeQgp9Z0VjhGxB+uOt34c4ozA1A
         XYsa/8WyjSn42P9GFOncUOz+/NHk1EDQix8A1NL9MwfzSp5rdRvXLC8XwMdybqj9ez
         0f/hEWif2nXvv/tidiY4FhnJedkTar6A1MOsomLbjS6HuVf6VizMox83ohlJ9sL8cx
         tZoIOjjwoOZyQ5TDKDK4xcO895s+u7EWJxZicPqs7zEwtJQGlCmOtSBdVGuBXJ/iA+
         mTMPGSLctdJ+Q==
Date: Thu, 21 May 2020 16:28:54 +1000
From: Stephen Rothwell <sfr@canb.auug.org.au>
To: Paolo Bonzini <pbonzini@redhat.com>, KVM <kvm@vger.kernel.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@elte.hu>, "H. Peter Anvin" <hpa@zytor.com>,
        Peter Zijlstra <peterz@infradead.org>
Cc: Linux Next Mailing List <linux-next@vger.kernel.org>,
        Linux Kernel Mailing List <linux-kernel@vger.kernel.org>,
        Uros Bizjak <ubizjak@gmail.com>
Subject: linux-next: build failure after merge of the kvm tree
Message-ID: <20200521162854.70995699@canb.auug.org.au>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all,

After merging the kvm tree, today's linux-next build (x86_64 allmodconfig)
failed like this:

arch/x86/kvm/svm/svm.c: In function 'kvm_machine_check':
arch/x86/kvm/svm/svm.c:1834:2: error: too many arguments to function 'do_machine_check'
 1834 |  do_machine_check(&regs, 0);
      |  ^~~~~~~~~~~~~~~~
In file included from arch/x86/kvm/svm/svm.c:36:
arch/x86/include/asm/mce.h:254:6: note: declared here
  254 | void do_machine_check(struct pt_regs *pt_regs);
      |      ^~~~~~~~~~~~~~~~

Caused by commit

  1c164cb3ffd0 ("KVM: SVM: Use do_machine_check to pass MCE to the host")

interacting with commit

  aaa4947defff ("x86/entry: Convert Machine Check to IDTENTRY_IST")

from the tip tree.

I added the following merge fix patch.

From: Stephen Rothwell <sfr@canb.auug.org.au>
Date: Thu, 21 May 2020 16:24:59 +1000
Subject: [PATCH] KVM: SVM: fix up for do_machine_check() API change

Signed-off-by: Stephen Rothwell <sfr@canb.auug.org.au>
---
 arch/x86/kvm/svm/svm.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [RFC v2 02/18] target/i386: sev: Move local structure definitions into .c file
##### From: David Gibson <david@gibson.dropbear.id.au>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Gibson <david@gibson.dropbear.id.au>
X-Patchwork-Id: 11562163
Return-Path: <SRS0=9zq6=7D=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 04CEA138A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 21 May 2020 03:43:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E1AAF2078B
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 21 May 2020 03:43:16 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=gibson.dropbear.id.au
 header.i=@gibson.dropbear.id.au header.b="oCodzQxQ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728227AbgEUDnQ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 20 May 2020 23:43:16 -0400
Received: from bilbo.ozlabs.org ([203.11.71.1]:58701 "EHLO ozlabs.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728103AbgEUDnP (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 20 May 2020 23:43:15 -0400
Received: by ozlabs.org (Postfix, from userid 1007)
        id 49SFnr46D4z9sTM; Thu, 21 May 2020 13:43:12 +1000 (AEST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple;
        d=gibson.dropbear.id.au; s=201602; t=1590032592;
        bh=qt1SRH9INoxyxgglr9QeYCX23oCC/+kJcGSaqPbv7SA=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=oCodzQxQJSyz8Wn7Jsmit/eQ8OxfEseFlAV2jSTI7S+W2WGOXRr36p+AxAiQEHlwu
         X5x27w/rGSj0qLr4UbVu6tdvRNzBuzwVa1H0gsJ22ighBFfo5WY2K2d0RggbA4iDEC
         lBOJ6UsmnxWplajoHGFuNG/j0WOR+bEWYdrbJwUM=
From: David Gibson <david@gibson.dropbear.id.au>
To: qemu-devel@nongnu.org, brijesh.singh@amd.com,
        frankja@linux.ibm.com, dgilbert@redhat.com, pair@us.ibm.com
Cc: qemu-ppc@nongnu.org, kvm@vger.kernel.org,
        David Gibson <david@gibson.dropbear.id.au>,
        mdroth@linux.vnet.ibm.com, cohuck@redhat.com,
        Marcel Apfelbaum <marcel.apfelbaum@gmail.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Richard Henderson <rth@twiddle.net>,
        Eduardo Habkost <ehabkost@redhat.com>
Subject: [RFC v2 02/18] target/i386: sev: Move local structure definitions
 into .c file
Date: Thu, 21 May 2020 13:42:48 +1000
Message-Id: <20200521034304.340040-3-david@gibson.dropbear.id.au>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20200521034304.340040-1-david@gibson.dropbear.id.au>
References: <20200521034304.340040-1-david@gibson.dropbear.id.au>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Neither QSevGuestInfo nor SEVState (not to be confused with SevState) is
used anywhere outside target/i386/sev.c, so they might as well live in
there rather than in a (somewhat) exposed header.

Signed-off-by: David Gibson <david@gibson.dropbear.id.au>
---
 target/i386/sev.c      | 44 ++++++++++++++++++++++++++++++++++++++++++
 target/i386/sev_i386.h | 44 ------------------------------------------
 2 files changed, 44 insertions(+), 44 deletions(-)

```
#### [RFC v2 01/18] target/i386: sev: Remove unused QSevGuestInfoClass
##### From: David Gibson <david@gibson.dropbear.id.au>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Gibson <david@gibson.dropbear.id.au>
X-Patchwork-Id: 11562157
Return-Path: <SRS0=9zq6=7D=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3225690
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 21 May 2020 03:43:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C240C207C4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 21 May 2020 03:43:14 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=gibson.dropbear.id.au
 header.i=@gibson.dropbear.id.au header.b="ItLRJ9Kp"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728180AbgEUDnO (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 20 May 2020 23:43:14 -0400
Received: from bilbo.ozlabs.org ([203.11.71.1]:48623 "EHLO ozlabs.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727998AbgEUDnN (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 20 May 2020 23:43:13 -0400
Received: by ozlabs.org (Postfix, from userid 1007)
        id 49SFnr3J0lz9sTK; Thu, 21 May 2020 13:43:12 +1000 (AEST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple;
        d=gibson.dropbear.id.au; s=201602; t=1590032592;
        bh=b/ySedG6EPtDyWOrvJGyJDxoH9+NiT2I5+DDWgavmns=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=ItLRJ9KpIT0rlyJMStLLstOF0HYYFlpyWulI3c0dxJ8nha6BFpr+2qSz30UlBK9J3
         O/S6/P0+q3njZeUxbKrDpW0b+h6cgXyUgbx4NAMpji/gA/ACJr0h4bEKlPFSf+YWDD
         ESlGHcW8/1tsLgO7w1bsHou7vzvq/Pg/TOcY9IJY=
From: David Gibson <david@gibson.dropbear.id.au>
To: qemu-devel@nongnu.org, brijesh.singh@amd.com,
        frankja@linux.ibm.com, dgilbert@redhat.com, pair@us.ibm.com
Cc: qemu-ppc@nongnu.org, kvm@vger.kernel.org,
        David Gibson <david@gibson.dropbear.id.au>,
        mdroth@linux.vnet.ibm.com, cohuck@redhat.com,
        Marcel Apfelbaum <marcel.apfelbaum@gmail.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Richard Henderson <rth@twiddle.net>,
        Eduardo Habkost <ehabkost@redhat.com>
Subject: [RFC v2 01/18] target/i386: sev: Remove unused QSevGuestInfoClass
Date: Thu, 21 May 2020 13:42:47 +1000
Message-Id: <20200521034304.340040-2-david@gibson.dropbear.id.au>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20200521034304.340040-1-david@gibson.dropbear.id.au>
References: <20200521034304.340040-1-david@gibson.dropbear.id.au>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This structure is nothing but an empty wrapper around the parent class,
which by QOM conventions means we don't need it at all.

Signed-off-by: David Gibson <david@gibson.dropbear.id.au>
---
 target/i386/sev.c      | 1 -
 target/i386/sev_i386.h | 5 -----
 2 files changed, 6 deletions(-)

```
#### [PATCH v3 03/14] mips: Add MIPS Release 5 support
##### From: Serge Semin <Sergey.Semin@baikalelectronics.ru>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Serge Semin <Sergey.Semin@baikalelectronics.ru>
X-Patchwork-Id: 11561859
Return-Path: <SRS0=9zq6=7D=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6CEEA138A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 21 May 2020 00:36:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 493D22084C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 21 May 2020 00:36:06 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727055AbgEUAf0 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 20 May 2020 20:35:26 -0400
Received: from mail.baikalelectronics.com ([87.245.175.226]:32940 "EHLO
        mail.baikalelectronics.ru" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726819AbgEUAfY (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 20 May 2020 20:35:24 -0400
Received: from localhost (unknown [127.0.0.1])
        by mail.baikalelectronics.ru (Postfix) with ESMTP id 9836180307C7;
        Thu, 21 May 2020 00:35:15 +0000 (UTC)
X-Virus-Scanned: amavisd-new at baikalelectronics.ru
Received: from mail.baikalelectronics.ru ([127.0.0.1])
        by localhost (mail.baikalelectronics.ru [127.0.0.1]) (amavisd-new,
 port 10024)
        with ESMTP id QoM91emHazri; Thu, 21 May 2020 03:35:13 +0300 (MSK)
From: Serge Semin <Sergey.Semin@baikalelectronics.ru>
To: Thomas Bogendoerfer <tsbogend@alpha.franken.de>
CC: Serge Semin <Sergey.Semin@baikalelectronics.ru>,
 Serge Semin <fancer.lancer@gmail.com>,
 Alexey Malahov <Alexey.Malahov@baikalelectronics.ru>,
 Paul Burton <paulburton@kernel.org>, Ralf Baechle <ralf@linux-mips.org>,
 Arnd Bergmann <arnd@arndb.de>, Rob Herring <robh+dt@kernel.org>,
 <devicetree@vger.kernel.org>, Thomas Bogendoerfer <tbogendoerfer@suse.de>,
 Jiaxun Yang <jiaxun.yang@flygoat.com>, Alexander Lobakin <alobakin@dlink.ru>,
 Huacai Chen <chenhc@lemote.com>, Daniel Silsby <dansilsby@gmail.com>,
 Ard Biesheuvel <ardb@kernel.org>, Herbert Xu <herbert@gondor.apana.org.au>,
 Cedric Hombourger <Cedric_Hombourger@mentor.com>,
 Thomas Gleixner <tglx@linutronix.de>,
 Sebastian Andrzej Siewior <bigeasy@linutronix.de>,
 Ingo Molnar <mingo@kernel.org>,
 =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <f4bug@amsat.org>,
 Paul Cercueil <paul@crapouillou.net>, Guenter Roeck <linux@roeck-us.net>,
 Zhou Yanjie <zhouyanjie@zoho.com>, Masahiro Yamada <masahiroy@kernel.org>,
 Greg Kroah-Hartman <gregkh@linuxfoundation.org>,
 Allison Randal <allison@lohutok.net>,
 "Peter Zijlstra (Intel)" <peterz@infradead.org>,
 Jessica Yu <jeyu@kernel.org>,
 =?utf-8?b?5ZGo55Cw5p2wIChaaG91IFlhbmppZSk=?=  <zhouyanjie@wanyeetech.com>,
 YunQiang Su <syq@debian.org>, Oleksij Rempel <linux@rempel-privat.de>,
 Kamal Dasu <kdasu.kdev@gmail.com>, <linux-mips@vger.kernel.org>,
 <linux-kernel@vger.kernel.org>, <kvm@vger.kernel.org>
Subject: [PATCH v3 03/14] mips: Add MIPS Release 5 support
Date: Thu, 21 May 2020 03:34:32 +0300
Message-ID: <20200521003443.11385-4-Sergey.Semin@baikalelectronics.ru>
In-Reply-To: <20200521003443.11385-1-Sergey.Semin@baikalelectronics.ru>
References: <20200521003443.11385-1-Sergey.Semin@baikalelectronics.ru>
MIME-Version: 1.0
X-ClientProxiedBy: MAIL.baikal.int (192.168.51.25) To mail (192.168.51.25)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

There are five MIPS32/64 architecture releases currently available:
from 1 to 6 except fourth one, which was intentionally skipped.
Three of them can be called as major: 1st, 2nd and 6th, that not only
have some system level alterations, but also introduced significant
core/ISA level updates. The rest of the MIPS architecture releases are
minor.

Even though they don't have as much ISA/system/core level changes
as the major ones with respect to the previous releases, they still
provide a set of updates (I'd say they were intended to be the
intermediate releases before a major one) that might be useful for the
kernel and user-level code, when activated by the kernel or compiler.
In particular the following features were introduced or ended up being
available at/after MIPS32/64 Release 5 architecture:
+ the last release of the misaligned memory access instructions,
+ virtualisation - VZ ASE - is optional component of the arch,
+ SIMD - MSA ASE - is optional component of the arch,
+ DSP ASE is optional component of the arch,
+ CP0.Status.FR=1 for CP1.FIR.F64=1 (pure 64-bit FPU general registers)
  must be available if FPU is implemented,
+ CP1.FIR.Has2008 support is required so CP1.FCSR.{ABS2008,NAN2008} bits
  are available.
+ UFR/UNFR aliases to access CP0.Status.FR from user-space by means of
  ctc1/cfc1 instructions (enabled by CP0.Config5.UFR),
+ CP0.COnfig5.LLB=1 and eretnc instruction are implemented to without
  accidentally clearing LL-bit when returning from an interrupt,
  exception, or error trap,
+ XPA feature together with extended versions of CPx registers is
  introduced, which needs to have mfhc0/mthc0 instructions available.

So due to these changes GNU GCC provides an extended instructions set
support for MIPS32/64 Release 5 by default like eretnc/mfhc0/mthc0. Even
though the architecture alteration isn't that big, it still worth to be
taken into account by the kernel software. Finally we can't deny that
some optimization/limitations might be found in future and implemented
on some level in kernel or compiler. In this case having even
intermediate MIPS architecture releases support would be more than
useful.

So the most of the changes provided by this commit can be split into
either compile- or runtime configs related. The compile-time related
changes are caused by adding the new CONFIG_CPU_MIPS32_R5/CONFIG_CPU_MIPSR5
configs and concern the code activating MIPSR2 or MIPSR6 already
implemented features (like eretnc/LLbit, mthc0/mfhc0). In addition
CPU_HAS_MSA can be now freely enabled for MIPS32/64 release 5 based
platforms as this is done for CPU_MIPS32_R6 CPUs. The runtime changes
concerns the features which are handled with respect to the MIPS ISA
revision detected at run-time by means of CP0.Config.{AT,AR} bits. Alas
these fields can be used to detect either r1 or r2 or r6 releases.
But since we know which CPUs in fact support the R5 arch, we can manually
set MIPS_CPU_ISA_M32R5/MIPS_CPU_ISA_M64R5 bit of c->isa_level and then
use cpu_has_mips32r5/cpu_has_mips64r5 where it's appropriate.

Since XPA/EVA provide too complex alterationss and to have them used with
MIPS32 Release 2 charged kernels (for compatibility with current platform
configs) they are left to be setup as a separate kernel configs.

Co-developed-by: Alexey Malahov <Alexey.Malahov@baikalelectronics.ru>
Signed-off-by: Alexey Malahov <Alexey.Malahov@baikalelectronics.ru>
Signed-off-by: Serge Semin <Sergey.Semin@baikalelectronics.ru>
Cc: Thomas Bogendoerfer <tsbogend@alpha.franken.de>
Cc: Paul Burton <paulburton@kernel.org>
Cc: Ralf Baechle <ralf@linux-mips.org>
Cc: Arnd Bergmann <arnd@arndb.de>
Cc: Rob Herring <robh+dt@kernel.org>
Cc: devicetree@vger.kernel.org
---

Changelog v3:
- Together with MIPS32 add MIPS64 Release 5 support.
---
 arch/mips/Kconfig                    | 56 +++++++++++++++++++++++++---
 arch/mips/Makefile                   |  2 +
 arch/mips/include/asm/asmmacro.h     | 18 +++++----
 arch/mips/include/asm/compiler.h     |  5 +++
 arch/mips/include/asm/cpu-features.h | 27 ++++++++++----
 arch/mips/include/asm/cpu-info.h     |  2 +-
 arch/mips/include/asm/cpu-type.h     |  7 +++-
 arch/mips/include/asm/cpu.h          | 10 +++--
 arch/mips/include/asm/fpu.h          |  4 +-
 arch/mips/include/asm/hazards.h      |  8 ++--
 arch/mips/include/asm/stackframe.h   |  2 +-
 arch/mips/include/asm/switch_to.h    |  8 ++--
 arch/mips/include/asm/vermagic.h     |  4 ++
 arch/mips/kernel/cpu-probe.c         | 17 +++++++++
 arch/mips/kernel/entry.S             |  6 +--
 arch/mips/kernel/proc.c              |  4 ++
 arch/mips/kernel/r4k_fpu.S           | 14 +++----
 arch/mips/kvm/vz.c                   |  6 +--
 arch/mips/lib/csum_partial.S         |  6 ++-
 arch/mips/mm/c-r4k.c                 |  7 ++--
 arch/mips/mm/sc-mips.c               |  7 ++--
 21 files changed, 163 insertions(+), 57 deletions(-)

```
#### [PATCH v4 03/13] mips: Add MIPS Release 5 support
##### From: Serge Semin <Sergey.Semin@baikalelectronics.ru>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Serge Semin <Sergey.Semin@baikalelectronics.ru>
X-Patchwork-Id: 11563031
Return-Path: <SRS0=9zq6=7D=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EC8EC14C0
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 21 May 2020 14:08:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CC618206BE
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 21 May 2020 14:08:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729694AbgEUOIe (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 21 May 2020 10:08:34 -0400
Received: from mail.baikalelectronics.com ([87.245.175.226]:38342 "EHLO
        mail.baikalelectronics.ru" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729678AbgEUOIc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 21 May 2020 10:08:32 -0400
Received: from localhost (unknown [127.0.0.1])
        by mail.baikalelectronics.ru (Postfix) with ESMTP id 39EB48030791;
        Thu, 21 May 2020 14:08:24 +0000 (UTC)
X-Virus-Scanned: amavisd-new at baikalelectronics.ru
Received: from mail.baikalelectronics.ru ([127.0.0.1])
        by localhost (mail.baikalelectronics.ru [127.0.0.1]) (amavisd-new,
 port 10024)
        with ESMTP id ZPJgcHoYyniC; Thu, 21 May 2020 17:08:22 +0300 (MSK)
From: Serge Semin <Sergey.Semin@baikalelectronics.ru>
To: Thomas Bogendoerfer <tsbogend@alpha.franken.de>
CC: Serge Semin <Sergey.Semin@baikalelectronics.ru>,
 Serge Semin <fancer.lancer@gmail.com>,
 Alexey Malahov <Alexey.Malahov@baikalelectronics.ru>,
 Paul Burton <paulburton@kernel.org>, Ralf Baechle <ralf@linux-mips.org>,
 Arnd Bergmann <arnd@arndb.de>, Rob Herring <robh+dt@kernel.org>,
 <devicetree@vger.kernel.org>, Jiaxun Yang <jiaxun.yang@flygoat.com>,
 Alexander Lobakin <alobakin@dlink.ru>, Huacai Chen <chenhc@lemote.com>,
 Nathan Chancellor <natechancellor@gmail.com>,
 Ard Biesheuvel <ardb@kernel.org>,
 Cedric Hombourger <Cedric_Hombourger@mentor.com>,
 Thomas Gleixner <tglx@linutronix.de>, Ingo Molnar <mingo@kernel.org>,
 Sebastian Andrzej Siewior <bigeasy@linutronix.de>, =?utf-8?q?Philippe_Mathi?=
	=?utf-8?q?eu-Daud=C3=A9?= <f4bug@amsat.org>,
 Guenter Roeck <linux@roeck-us.net>, Paul Cercueil <paul@crapouillou.net>,
 Zhou Yanjie <zhouyanjie@zoho.com>, Masahiro Yamada <masahiroy@kernel.org>,
 Greg Kroah-Hartman <gregkh@linuxfoundation.org>,
 Allison Randal <allison@lohutok.net>,
 Liangliang Huang <huanglllzu@gmail.com>, =?utf-8?b?5ZGo55Cw5p2wIChaaG91IFlh?=
	=?utf-8?b?bmppZSk=?=  <zhouyanjie@wanyeetech.com>,
 YunQiang Su <syq@debian.org>, Zou Wei <zou_wei@huawei.com>,
 Oleksij Rempel <linux@rempel-privat.de>, Kamal Dasu <kdasu.kdev@gmail.com>,
 <linux-mips@vger.kernel.org>, <linux-kernel@vger.kernel.org>,
 <kvm@vger.kernel.org>
Subject: [PATCH v4 03/13] mips: Add MIPS Release 5 support
Date: Thu, 21 May 2020 17:07:14 +0300
Message-ID: <20200521140725.29571-4-Sergey.Semin@baikalelectronics.ru>
In-Reply-To: <20200521140725.29571-1-Sergey.Semin@baikalelectronics.ru>
References: <20200521140725.29571-1-Sergey.Semin@baikalelectronics.ru>
MIME-Version: 1.0
X-ClientProxiedBy: MAIL.baikal.int (192.168.51.25) To mail (192.168.51.25)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

There are five MIPS32/64 architecture releases currently available:
from 1 to 6 except fourth one, which was intentionally skipped.
Three of them can be called as major: 1st, 2nd and 6th, that not only
have some system level alterations, but also introduced significant
core/ISA level updates. The rest of the MIPS architecture releases are
minor.

Even though they don't have as much ISA/system/core level changes
as the major ones with respect to the previous releases, they still
provide a set of updates (I'd say they were intended to be the
intermediate releases before a major one) that might be useful for the
kernel and user-level code, when activated by the kernel or compiler.
In particular the following features were introduced or ended up being
available at/after MIPS32/64 Release 5 architecture:
+ the last release of the misaligned memory access instructions,
+ virtualisation - VZ ASE - is optional component of the arch,
+ SIMD - MSA ASE - is optional component of the arch,
+ DSP ASE is optional component of the arch,
+ CP0.Status.FR=1 for CP1.FIR.F64=1 (pure 64-bit FPU general registers)
  must be available if FPU is implemented,
+ CP1.FIR.Has2008 support is required so CP1.FCSR.{ABS2008,NAN2008} bits
  are available.
+ UFR/UNFR aliases to access CP0.Status.FR from user-space by means of
  ctc1/cfc1 instructions (enabled by CP0.Config5.UFR),
+ CP0.COnfig5.LLB=1 and eretnc instruction are implemented to without
  accidentally clearing LL-bit when returning from an interrupt,
  exception, or error trap,
+ XPA feature together with extended versions of CPx registers is
  introduced, which needs to have mfhc0/mthc0 instructions available.

So due to these changes GNU GCC provides an extended instructions set
support for MIPS32/64 Release 5 by default like eretnc/mfhc0/mthc0. Even
though the architecture alteration isn't that big, it still worth to be
taken into account by the kernel software. Finally we can't deny that
some optimization/limitations might be found in future and implemented
on some level in kernel or compiler. In this case having even
intermediate MIPS architecture releases support would be more than
useful.

So the most of the changes provided by this commit can be split into
either compile- or runtime configs related. The compile-time related
changes are caused by adding the new CONFIG_CPU_MIPS32_R5/CONFIG_CPU_MIPSR5
configs and concern the code activating MIPSR2 or MIPSR6 already
implemented features (like eretnc/LLbit, mthc0/mfhc0). In addition
CPU_HAS_MSA can be now freely enabled for MIPS32/64 release 5 based
platforms as this is done for CPU_MIPS32_R6 CPUs. The runtime changes
concerns the features which are handled with respect to the MIPS ISA
revision detected at run-time by means of CP0.Config.{AT,AR} bits. Alas
these fields can be used to detect either r1 or r2 or r6 releases.
But since we know which CPUs in fact support the R5 arch, we can manually
set MIPS_CPU_ISA_M32R5/MIPS_CPU_ISA_M64R5 bit of c->isa_level and then
use cpu_has_mips32r5/cpu_has_mips64r5 where it's appropriate.

Since XPA/EVA provide too complex alterationss and to have them used with
MIPS32 Release 2 charged kernels (for compatibility with current platform
configs) they are left to be setup as a separate kernel configs.

Co-developed-by: Alexey Malahov <Alexey.Malahov@baikalelectronics.ru>
Signed-off-by: Alexey Malahov <Alexey.Malahov@baikalelectronics.ru>
Signed-off-by: Serge Semin <Sergey.Semin@baikalelectronics.ru>
Cc: Thomas Bogendoerfer <tsbogend@alpha.franken.de>
Cc: Paul Burton <paulburton@kernel.org>
Cc: Ralf Baechle <ralf@linux-mips.org>
Cc: Arnd Bergmann <arnd@arndb.de>
Cc: Rob Herring <robh+dt@kernel.org>
Cc: devicetree@vger.kernel.org
---
 arch/mips/Kconfig                    | 56 +++++++++++++++++++++++++---
 arch/mips/Makefile                   |  2 +
 arch/mips/include/asm/asmmacro.h     | 18 +++++----
 arch/mips/include/asm/compiler.h     |  5 +++
 arch/mips/include/asm/cpu-features.h | 27 ++++++++++----
 arch/mips/include/asm/cpu-info.h     |  2 +-
 arch/mips/include/asm/cpu-type.h     |  7 +++-
 arch/mips/include/asm/cpu.h          | 10 +++--
 arch/mips/include/asm/fpu.h          |  4 +-
 arch/mips/include/asm/hazards.h      |  8 ++--
 arch/mips/include/asm/module.h       |  4 ++
 arch/mips/include/asm/stackframe.h   |  2 +-
 arch/mips/include/asm/switch_to.h    |  8 ++--
 arch/mips/kernel/cpu-probe.c         | 17 +++++++++
 arch/mips/kernel/entry.S             |  6 +--
 arch/mips/kernel/proc.c              |  4 ++
 arch/mips/kernel/r4k_fpu.S           | 14 +++----
 arch/mips/kvm/vz.c                   |  6 +--
 arch/mips/lib/csum_partial.S         |  6 ++-
 arch/mips/mm/c-r4k.c                 |  7 ++--
 arch/mips/mm/sc-mips.c               |  7 ++--
 21 files changed, 163 insertions(+), 57 deletions(-)

```
#### [PATCH v3] kvm/x86 : Remove redundant function implementThread-Topic: [PATCH v3] kvm/x86 : Remove redundant function implement
##### From: =?eucgb2312_cn?b?xe26xihSaWNoYXJkKQ==?= <richard.peng@oppo.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: =?utf-8?b?5b2t5rWpKFJpY2hhcmQp?=
 <richard.peng@oppo.com>
X-Patchwork-Id: 11562279
Return-Path: <SRS0=9zq6=7D=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 956BD912
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 21 May 2020 05:57:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7789720825
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 21 May 2020 05:57:59 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=oppoglobal.onmicrosoft.com
 header.i=@oppoglobal.onmicrosoft.com header.b="Rbp++ErR"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728083AbgEUF54 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 21 May 2020 01:57:56 -0400
Received: from mail-eopbgr1310070.outbound.protection.outlook.com
 ([40.107.131.70]:11440
        "EHLO APC01-SG2-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726869AbgEUF5z (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 21 May 2020 01:57:55 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=KyRyeaQH+NSrNqZFjECHNd69s7ltflQW/H3rjIbjZFwq9tJ7EgSCoKQhnnbbIbEWMiixdPJyQas1oYkc455nvp0UqlgJCQ4CO41R9I4DdYH7VrO0FlYXW5MerWEa8uzSG2xEECg6YUf1/THcwmq+b26Du0yUCHLcLVg9v2g/rZnD2hoi2tI90T1J/Vh5do4UOJfUOyDJPyhQPJVaERvX1QPjq/yOEzHfEeemBHMdVpzfHPU7QJWf7WNw+BRY2QHTpepSUUNiSmVl4Y+4rCcrwqpaQf857hRizep2smHU6PvXE7xFYQRsT7Iw+6qHnpxdJCc7p+jiub6lwl/XFfjExA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=9zKc6D+OtGRV1jtx43O1KVZP6EL0f/3uvVP4n8uZC50=;
 b=Gy/oIsYCVf4Ppmp5aT0R34fCmCsMoGzUs+tl+oXcmmR8RmnDpFMLLa6D2pheVZ3hqFcmldiswADaWexfM5ocR5KZdxmF0XhxaWW5VKyOiXkuMTba926AkfFLmxxIAGKOiE5uiXc9dv9osnr3zTxFQsGCfe1NDErPdSYt2h+irTe4DVTP+GBZ2qr06a7fSSeQS59ZNnmOE9rQmM1aUkNymPEWkjTaBRgXZmkLIV8GAMbacqhHZi8tKpXmnAzNDvKwEtyv3NzCns4dznBNHT9VP2jYy161yOvZeoBkYB9HZ2mCj7m1d7CxH8WaB3w36d1MXqiJA1DcORO1aFvZSwQVkA==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=oppo.com; dmarc=pass action=none header.from=oppo.com;
 dkim=pass header.d=oppo.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=oppoglobal.onmicrosoft.com; s=selector1-oppoglobal-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=9zKc6D+OtGRV1jtx43O1KVZP6EL0f/3uvVP4n8uZC50=;
 b=Rbp++ErRhn/sPpvVYXvUK3KiJHlDZR4qS90V7G5kpKvglr0vVvA7d6f3UNJbZi1y8w0fDYtzjb81g+RjBlL88Q4x2yDgYgYZtA3odlrCZtUo8e14+4EEGALggIPqaYLTJcm/k7aLpExu3PYrFxk8a0hoyIo0P5PR1pRk1mNvb0s=
Received: from HKAPR02MB4291.apcprd02.prod.outlook.com (2603:1096:203:d3::12)
 by HKAPR02MB4403.apcprd02.prod.outlook.com (2603:1096:203:d5::8) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3021.23; Thu, 21 May
 2020 05:57:49 +0000
Received: from HKAPR02MB4291.apcprd02.prod.outlook.com
 ([fe80::80ca:c698:988e:a999]) by HKAPR02MB4291.apcprd02.prod.outlook.com
 ([fe80::80ca:c698:988e:a999%5]) with mapi id 15.20.3021.020; Thu, 21 May 2020
 05:57:49 +0000
From: =?eucgb2312_cn?b?xe26xihSaWNoYXJkKQ==?= <richard.peng@oppo.com>
To: Paolo Bonzini <pbonzini@redhat.com>
CC: "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>,
        "kvm@vger.kernel.org" <kvm@vger.kernel.org>
Subject: [PATCH v3] kvm/x86 : Remove redundant function implement
Thread-Topic: [PATCH v3] kvm/x86 : Remove redundant function implement
Thread-Index: AdYvNGncuTv2pa/PRZeWvNnr93KTAw==
Date: Thu, 21 May 2020 05:57:49 +0000
Message-ID: 
 <HKAPR02MB4291D5926EA10B8BFE9EA0D3E0B70@HKAPR02MB4291.apcprd02.prod.outlook.com>
Accept-Language: zh-CN, en-US
Content-Language: zh-CN
X-MS-Has-Attach: 
X-MS-TNEF-Correlator: 
authentication-results: redhat.com; dkim=none (message not signed)
 header.d=none;redhat.com; dmarc=none action=none header.from=oppo.com;
x-originating-ip: [58.255.79.102]
x-ms-publictraffictype: Email
x-ms-office365-filtering-correlation-id: 5b49bb71-8b06-4612-6052-08d7fd4be4ac
x-ms-traffictypediagnostic: HKAPR02MB4403:
x-microsoft-antispam-prvs: 
 <HKAPR02MB440328797D61BB3BD7D2B0CCE0B70@HKAPR02MB4403.apcprd02.prod.outlook.com>
x-ms-oob-tlc-oobclassifiers: OLM:119;
x-forefront-prvs: 041032FF37
x-ms-exchange-senderadcheck: 1
x-microsoft-antispam: BCL:0;
x-microsoft-antispam-message-info: 
 IQyWPh9tKCanaO5483V3q4Eyoijqxyy44KSPS7LiaIddnjBR7oAs39IQPP561tQR7i7PK8pQVP6Sp0W/Had1LeS6IIjIKfaMv/3ohfT2/rJCR9RJ5OFiE/0xsPIlkokRS2sGxMq4FHYJ857HBi4N6pBvc/1GtTZTUP9mU2BSlDDD6vVvf5p62OvAs1bMvLQga5s9qa38npZirqsIIjv4GVOJsjwkJzfWPyd6o0AHjfOY1INkC2q8iri52sRbbIlTB33ZzKnkrnbTB7EvgRKCt3N4oLhQMPARe2YJJ+4H+rxbDfh933lJwCffq4m1c3xIDrGgBqjll+ie9udq6eT2VxKl2QwScmvhP1T/C3W7eOwSz60NPEvIEUihrE49fzGX
x-forefront-antispam-report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:HKAPR02MB4291.apcprd02.prod.outlook.com;PTR:;CAT:NONE;SFTY:;SFS:(396003)(346002)(136003)(39860400002)(376002)(366004)(4326008)(85182001)(86362001)(8676002)(5660300002)(8936002)(66446008)(64756008)(9686003)(55016002)(6916009)(71200400001)(66476007)(186003)(6506007)(478600001)(33656002)(52536014)(66946007)(76116006)(54906003)(66556008)(316002)(26005)(7696005)(2906002)(11606004);DIR:OUT;SFP:1101;
x-ms-exchange-antispam-messagedata: 
 pFto/N3jMm9e9mxV+w54/p7PEit6mnK6d6HswKMdneQzr6QohH3h23fxOMn/3puelH1qgdLy42KR/jY2fGG+7AahSwia9i4J63ef68HECMrR4NS4ck5GGhelOOzMmhI1y0Z3Iw3svFW6YonXuBByVbwyXrTPfPNC/xgakLEvcUf5QnScGmUlrjpzbgOr88hKHI2lbHh1IMu7z6IhVSV+09a4aCC4z936iQS1vDgoNMDctQzQ0dVn8WPcnLzGoOb99yjtzK8IhWATeBW+OH1QVVyxbAv+0qCbIx9PjWgaJ+piRna4ZJGnOEd/JK3Sb6KpmjMPjQsmVobHZ6tKCZXC7B1M2YmnFXVhotem1/mDJE1PpR9dNyUWoTlR5dngCgyJ+DPptPolZed+77fsOvHoY5TfpThY6lnBtJNMrOs4KmXyjDb/7VE+JqxcCoMWpy85drnHp4if8W4cdEjJy4H6+CYRO2JzXVZ/Pf/pS9Bq1EE=
x-ms-exchange-transport-forked: True
MIME-Version: 1.0
X-OriginatorOrg: oppo.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 5b49bb71-8b06-4612-6052-08d7fd4be4ac
X-MS-Exchange-CrossTenant-originalarrivaltime: 21 May 2020 05:57:49.4960
 (UTC)
X-MS-Exchange-CrossTenant-fromentityheader: Hosted
X-MS-Exchange-CrossTenant-id: f1905eb1-c353-41c5-9516-62b4a54b5ee6
X-MS-Exchange-CrossTenant-mailboxtype: HOSTED
X-MS-Exchange-CrossTenant-userprincipalname: 
 jeWj00RCj804FikMJx1Fwq9fnBGy9qElZiiwHgJF19dIl2IWEezXd1xF/sKVYHeANCsNIc/dK5hPgAQLwy1Zng==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: HKAPR02MB4403
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

pic_in_kernel(),ioapic_in_kernel() and irqchip_kernel() have the
same implementation.

Signed-off-by: Peng Hao <richard.peng@oppo.com>
---
 arch/x86/kvm/ioapic.h  |  8 ++------
 arch/x86/kvm/irq.h     | 14 ++++----------
 arch/x86/kvm/lapic.c   |  1 +
 arch/x86/kvm/mmu/mmu.c |  1 +
 arch/x86/kvm/x86.c     |  1 +
 5 files changed, 9 insertions(+), 16 deletions(-)

--
2.7.4

```
