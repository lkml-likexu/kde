#### [PATCH 01/14] KVM: monolithic: x86: remove kvm.ko
##### From: Andrea Arcangeli <aarcange@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrea Arcangeli <aarcange@redhat.com>
X-Patchwork-Id: 11165499
Return-Path: <SRS0=Rq3I=XX=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F17FD112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 28 Sep 2019 17:24:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id CFE8B208E4
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 28 Sep 2019 17:24:38 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728666AbfI1RXZ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 28 Sep 2019 13:23:25 -0400
Received: from mx1.redhat.com ([209.132.183.28]:49530 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728569AbfI1RXY (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 28 Sep 2019 13:23:24 -0400
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id A0A8010576C4;
        Sat, 28 Sep 2019 17:23:24 +0000 (UTC)
Received: from mail (ovpn-125-159.rdu2.redhat.com [10.10.125.159])
        by smtp.corp.redhat.com (Postfix) with ESMTPS id 6232D60600;
        Sat, 28 Sep 2019 17:23:24 +0000 (UTC)
From: Andrea Arcangeli <aarcange@redhat.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>
Subject: [PATCH 01/14] KVM: monolithic: x86: remove kvm.ko
Date: Sat, 28 Sep 2019 13:23:10 -0400
Message-Id: <20190928172323.14663-2-aarcange@redhat.com>
In-Reply-To: <20190928172323.14663-1-aarcange@redhat.com>
References: <20190928172323.14663-1-aarcange@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.6.2 (mx1.redhat.com [10.5.110.64]);
 Sat, 28 Sep 2019 17:23:24 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is the first commit of a patch series that aims to replace the
modular kvm.ko kernel module with a monolithic kvm-intel/kvm-amd
model. This change has the only possible cons of wasting some disk
space in /lib/modules/. The pros are that it saves CPUS and some minor
RAM which are more scarse resources than disk space.

The pointer to function virtual template model cannot provide any
runtime benefit because kvm-intel and kvm-amd can't be loaded at the
same time.

This removes kvm.ko and it links and duplicates all kvm.ko objects to
both kvm-amd and kvm-intel.

Signed-off-by: Andrea Arcangeli <aarcange@redhat.com>
---
 arch/x86/kvm/Makefile | 5 ++---
 1 file changed, 2 insertions(+), 3 deletions(-)

```
#### [PATCH] KVM: Unlimit number of ioeventfd assignments for real
##### From: Peter Xu <peterx@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11165371
Return-Path: <SRS0=Rq3I=XX=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 13D7C17D4
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 28 Sep 2019 01:41:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E4AFF20869
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 28 Sep 2019 01:41:09 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728244AbfI1BlA (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 27 Sep 2019 21:41:00 -0400
Received: from mx1.redhat.com ([209.132.183.28]:52724 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725990AbfI1BlA (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 27 Sep 2019 21:41:00 -0400
Received: from mail-pf1-f197.google.com (mail-pf1-f197.google.com
 [209.85.210.197])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-GCM-SHA256 (128/128 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 5AA2718C37B
        for <kvm@vger.kernel.org>; Sat, 28 Sep 2019 01:40:59 +0000 (UTC)
Received: by mail-pf1-f197.google.com with SMTP id i28so3114775pfq.16
        for <kvm@vger.kernel.org>; Fri, 27 Sep 2019 18:40:59 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=ky42kKvEgu1tdZiOICEE1JQBSJf2IPpUikQsHQIbtbs=;
        b=auZX9s2I3GXDTWUSiS4dQAHJOcecMoH8tWr0qgur5N/uVBu8r7pBxaZZu5jllYGzrs
         SqhKDQxCTkty8xEjeBSwzGt9MWiakGbMHLGHGX49rcU4YcMfJ2rziQW9wdj8rrAGKuu8
         3+h/wUgdaCmdY8gueQd+QsHr71h7wCx6qyrlX86DpfNTU1W+Ual/lkM9foW51l4HC3kg
         AHzdFo7NJmGn22eAZsu5rR/EfkbrZ0grPz6LDo/HAx3iOONGdeeLpnb6EflVn6llvX32
         /CodLP1C+SD+qTbXBseqZDEOuN9KXeiciKUuX/T3NoxbVbEhEsSTJ8N+DaxGIhTlTczt
         4dXw==
X-Gm-Message-State: APjAAAWSJfMK9r8nj6li7t5wlsd3xjPwhKi8W82klBGncTSVWkzp2RDl
        5KxQhL7VR9Ys5mYc5zr9dR5lrdC7Ia9oNplBwkRCbDg1/S0q6a7JY1N++BY26siM0lLuZLj+TRP
        LAj18zxexkAJi
X-Received: by 2002:a17:902:6c:: with SMTP id 99mr8033102pla.89.1569634858863;
        Fri, 27 Sep 2019 18:40:58 -0700 (PDT)
X-Google-Smtp-Source: 
 APXvYqyBPMPLxsYGBRQQZkg2NdMe7+vlXq7pC8C3qOB86cmiFcfzkMiTyNDISkn8pQJFgJ8cCCb4FQ==
X-Received: by 2002:a17:902:6c:: with SMTP id 99mr8033093pla.89.1569634858663;
        Fri, 27 Sep 2019 18:40:58 -0700 (PDT)
Received: from xz-x1.redhat.com ([209.132.188.80])
        by smtp.gmail.com with ESMTPSA id
 z12sm4196455pfj.41.2019.09.27.18.40.55
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 27 Sep 2019 18:40:57 -0700 (PDT)
From: Peter Xu <peterx@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        "Dr . David Alan Gilbert" <dgilbert@redhat.com>, peterx@redhat.com,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>
Subject: [PATCH] KVM: Unlimit number of ioeventfd assignments for real
Date: Sat, 28 Sep 2019 09:40:45 +0800
Message-Id: <20190928014045.10721-1-peterx@redhat.com>
X-Mailer: git-send-email 2.21.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Previously we've tried to unlimit ioeventfd creation (6ea34c9b78c1,
"kvm: exclude ioeventfd from counting kvm_io_range limit",
2013-06-04), because that can be easily done by fd limitations and
otherwise it can easily reach the current maximum of 1000 iodevices.
Meanwhile, we still use the counter to limit the maximum allowed kvm
io devices to be created besides ioeventfd.

6ea34c9b78c1 achieved that in most cases, however it'll still fali the
ioeventfd creation when non-ioeventfd io devices overflows to 1000.
Then the next ioeventfd creation will fail while logically it should
be the next non-ioeventfd iodevice creation to fail.

That's not really a big problem at all because when it happens it
probably means something has leaked in userspace (or even malicious
program) so it's a bug to fix there.  However the error message like
"ioeventfd creation failed" with an -ENOSPACE is really confusing and
may let people think about the fact that it's the ioeventfd that is
leaked (while in most cases it's not!).

Let's use this patch to unlimit the creation of ioeventfd for real
this time, assuming this is also a bugfix of 6ea34c9b78c1.  To me more
importantly, when with a bug in userspace this patch can probably give
us another more meaningful failure on what has overflowed/leaked
rather than "ioeventfd creation failure: -ENOSPC".

CC: Dr. David Alan Gilbert <dgilbert@redhat.com>
Signed-off-by: Peter Xu <peterx@redhat.com>
---
 include/linux/kvm_host.h |  3 +++
 virt/kvm/eventfd.c       |  4 ++--
 virt/kvm/kvm_main.c      | 23 ++++++++++++++++++++---
 3 files changed, 25 insertions(+), 5 deletions(-)

```
