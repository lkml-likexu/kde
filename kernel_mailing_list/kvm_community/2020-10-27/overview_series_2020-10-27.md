#### [PATCH 1/2] kvm: x86/mmu: Add existing trace points to TDP MMUFrom: Ben Gardon <bgardon@google.com>
##### From: Ben Gardon <bgardon@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ben Gardon <bgardon@google.com>
X-Patchwork-Id: 11861265
Return-Path: <SRS0=+pC+=EC=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-20.4 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id AC057C55178
	for <kvm@archiver.kernel.org>; Tue, 27 Oct 2020 18:01:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5CB1921655
	for <kvm@archiver.kernel.org>; Tue, 27 Oct 2020 18:01:58 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="ETkQP5HG"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1823940AbgJ0SA7 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 27 Oct 2020 14:00:59 -0400
Received: from mail-pj1-f74.google.com ([209.85.216.74]:55818 "EHLO
        mail-pj1-f74.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1823703AbgJ0R7s (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 27 Oct 2020 13:59:48 -0400
Received: by mail-pj1-f74.google.com with SMTP id r1so1206096pjp.5
        for <kvm@vger.kernel.org>; Tue, 27 Oct 2020 10:59:48 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:message-id:mime-version:subject:from:to:cc;
        bh=ZbaL988uKrohM7H6ZS9XBC1GZUReqphtGwoVjHruBgI=;
        b=ETkQP5HGCh/KwMlK6Oa4F6JkS2Vrb4/abSeRSBvhnNdoh7fS6XT3reiyLt2vKVEC0z
         M9iipXbsW21hYHi4VY4x6NVg9OXjZAUZPAZnHb7jYSlaf4x1ZFfY0FUxi1xSxbrBP5f/
         +F5/GDtp3fd8zI9NK/53rWJ6NJurivwnp9kVLRvzrui/mQTKomi0YHubwm/FCoviFIT3
         Ozgg0HEh4WKWyKEIjr4VumLXFvyuC1skb2uVBq/lkf46H/hvZAtgFyg17x/qvSZkyUsF
         8ZTcFNbTXGcZI883jiYK3JocvhaDa/1CI4lDm53uHpwtHEkWyzhHpBepYSwTuTlQw8uo
         ArSg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:message-id:mime-version:subject:from
         :to:cc;
        bh=ZbaL988uKrohM7H6ZS9XBC1GZUReqphtGwoVjHruBgI=;
        b=lmBDTy3d7H0skHwRVMTU5znPLmH2EFZwZ8TsnNMDcsD1TCMQDHFpEjg/z3OmCSIlVU
         E4n1vQ969SlPZd+a3i3cIH6zf3GDqIj6bKT6BbB6h/ZaSdfXlgz4EFFXCHGioabu73yv
         JPL1LqcwaXE976ajrah0IbZOhRH5L9b+1sH2+cXAjjANbAYnU4H4ckOTpFwWLqYu83j7
         fQuySBjCR+RPQiILNhyA/t7lo1dau+Q7f1bRbZ9BxgQiIewJlaVmYvNrh6Nt4FNc0LZ2
         v6VIytEoKJtrRC5nwEhOf6hjPCleFi7EVphQnlWsGlbY3fzHDWMmKCTXWpZwXuqmNgm7
         U3dw==
X-Gm-Message-State: AOAM53073pYo/B61m4hUvFNiSiq7+jwC6XgDYumgEENDToGgqIfRjGC/
        vgZqzmefTNIB+x4Ig2CJW1NmE2NLnjJ/
X-Google-Smtp-Source: 
 ABdhPJxHHWvVxLU1UFqepNXpxQRVm0nystR88ugkX/J00ithmflQf37LyJF5KikOJDXp10J+BKeVZjWT3LcQ
Sender: "bgardon via sendgmr" <bgardon@bgardon.sea.corp.google.com>
X-Received: from bgardon.sea.corp.google.com
 ([2620:15c:100:202:f693:9fff:fef4:a293])
 (user=bgardon job=sendgmr) by 2002:a17:90b:f85:: with SMTP id
 ft5mr266022pjb.1.1603821587576; Tue, 27 Oct 2020 10:59:47 -0700 (PDT)
Date: Tue, 27 Oct 2020 10:59:43 -0700
Message-Id: <20201027175944.1183301-1-bgardon@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.29.0.rc2.309.g374f81d7ae-goog
Subject: [PATCH 1/2] kvm: x86/mmu: Add existing trace points to TDP MMU
From: Ben Gardon <bgardon@google.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>, Peter Xu <peterx@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Peter Shier <pshier@google.com>,
        Junaid Shahid <junaids@google.com>,
        Peter Feiner <pfeiner@google.com>,
        Ben Gardon <bgardon@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The TDP MMU was initially implemented without some of the usual
tracepoints found in mmu.c. Correct this discrepancy by adding the
missing trace points to the TDP MMU.

Tested: ran the demand paging selftest on an Intel Skylake machine with
	all the trace points used by the TDP MMU enabled and observed
	them firing with expected values.

This patch can be viewed in Gerrit at:
https://linux-review.googlesource.com/c/virt/kvm/kvm/+/3812

Signed-off-by: Ben Gardon <bgardon@google.com>
---
 arch/x86/kvm/mmu/tdp_mmu.c | 12 +++++++++++-
 1 file changed, 11 insertions(+), 1 deletion(-)

```
#### [PATCH 1/3] locking/rwlocks: Add contention detection for rwlocksFrom: Ben Gardon <bgardon@google.com>
##### From: Ben Gardon <bgardon@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ben Gardon <bgardon@google.com>
X-Patchwork-Id: 11860911
Return-Path: <SRS0=+pC+=EC=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-20.4 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=unavailable autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id EB80DC55178
	for <kvm@archiver.kernel.org>; Tue, 27 Oct 2020 16:51:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9317822202
	for <kvm@archiver.kernel.org>; Tue, 27 Oct 2020 16:51:32 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="DubVR4Rd"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1813379AbgJ0Qvb (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 27 Oct 2020 12:51:31 -0400
Received: from mail-qv1-f74.google.com ([209.85.219.74]:45665 "EHLO
        mail-qv1-f74.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1813381AbgJ0Qtz (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 27 Oct 2020 12:49:55 -0400
Received: by mail-qv1-f74.google.com with SMTP id eh4so1152267qvb.12
        for <kvm@vger.kernel.org>; Tue, 27 Oct 2020 09:49:54 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:message-id:mime-version:subject:from:to:cc;
        bh=U+Sl1viisZnw2P5KbSyNcmWeiRs170Jsspt/5pdErgI=;
        b=DubVR4RdHZixj/MazoAiQa7LsELMe7q1j1wcRQtxAhIt8M0+qeroeNmHD6iw8d0SoT
         Vn9FoAs+W07E50WA9CmV1mSfGy6K9ZbVSsWhc83TFGc3jV6w53F2n366neyttweh3dMC
         mFbA15X775tTR+yX4VtaX4HIjQy7TPDPbadAdDGwC3hLD7enHNYSVpcF2PTrNXgWk2lm
         YRXwQNnH9+wgtv0BUvufXORocXPacbXMEaWP8I8UYasrW2d4p/OMRlKVZ+owH6CUStUz
         C3PQ+xNz7nbT91DarInhuvcueeYKu2UhcJtdSRJdvblc8c8upj4QCiB3TNx3oHKD7atD
         DakA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:message-id:mime-version:subject:from
         :to:cc;
        bh=U+Sl1viisZnw2P5KbSyNcmWeiRs170Jsspt/5pdErgI=;
        b=C+Itt6qiaXulR5+NOD9oCOFbyh/pxBcrsTO7BOscY/WhgIznnMHlYP8/DaA/b7KLGj
         BQCNmt4+msmHXSh5hZz3jKFJDE/N2F4AU7tBUvf8jWqBMyl4gRtn64METwkJeHEVhcFy
         y7SB61tGT0a13zu8VJg+cnVpoB3dmahhOOULRNIXUku0TsTXNtErPlHYiKH+r/sTi/E0
         St13ehhTCQDkHfB1Oxa2E2I1bkqlJPhCQrF9/8DAufAymSHzTIpy1K1O0h5lvAk+D89b
         ZhwJBaAtfAh9QCFJx3m1IM+znM/IImHyz4X9DV4aT3+nkR2JYpSjNaMtOD3LxNm4LFLr
         LQqA==
X-Gm-Message-State: AOAM532HtOC3ArlFBgB7WUeDaQM/cESpm3tZy1l7nxoqMD1vADPNC6s7
        8MgocIOR3wS3jezI72BNThjXysGD23oC
X-Google-Smtp-Source: 
 ABdhPJy7jmfOQfx/bywu9bX0ELil5fzyHmKvy6d8QjRjocYnZAR09IfqYu76mv2cNBj5hnzjZWSZp9IUjefG
Sender: "bgardon via sendgmr" <bgardon@bgardon.sea.corp.google.com>
X-Received: from bgardon.sea.corp.google.com
 ([2620:15c:100:202:f693:9fff:fef4:a293])
 (user=bgardon job=sendgmr) by 2002:a0c:aa98:: with SMTP id
 f24mr3241618qvb.62.1603817394270; Tue, 27 Oct 2020 09:49:54 -0700 (PDT)
Date: Tue, 27 Oct 2020 09:49:48 -0700
Message-Id: <20201027164950.1057601-1-bgardon@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.29.0.rc2.309.g374f81d7ae-goog
Subject: [PATCH 1/3] locking/rwlocks: Add contention detection for rwlocks
From: Ben Gardon <bgardon@google.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Peter Shier <pshier@google.com>,
        Peter Zijlstra <peterz@infradead.org>,
        Ingo Molnar <mingo@redhat.com>, Will Deacon <will@kernel.org>,
        Waiman Long <longman@redhat.com>,
        Davidlohr Bueso <dave@stgolabs.net>,
        Ben Gardon <bgardon@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

rwlocks do not currently have any facility to detect contention
like spinlocks do. In order to allow users of rwlocks to better manage
latency, add contention detection for queued rwlocks.

Signed-off-by: Ben Gardon <bgardon@google.com>
---
 include/asm-generic/qrwlock.h | 23 +++++++++++++++++------
 include/linux/rwlock.h        |  7 +++++++
 2 files changed, 24 insertions(+), 6 deletions(-)

```
#### [PATCH 1/3] eventfd: Export eventfd_ctx_do_read()
##### From: David Woodhouse <dwmw2@infradead.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Woodhouse <dwmw2@infradead.org>
X-Patchwork-Id: 11860503
Return-Path: <SRS0=+pC+=EC=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.9 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C5F39C55178
	for <kvm@archiver.kernel.org>; Tue, 27 Oct 2020 13:55:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 83DBA218AC
	for <kvm@archiver.kernel.org>; Tue, 27 Oct 2020 13:55:41 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=infradead.org header.i=@infradead.org
 header.b="u+kVoBLb"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S368011AbgJ0Nzk (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 27 Oct 2020 09:55:40 -0400
Received: from casper.infradead.org ([90.155.50.34]:41602 "EHLO
        casper.infradead.org" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S368005AbgJ0Nzg (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 27 Oct 2020 09:55:36 -0400
DKIM-Signature: v=1; a=rsa-sha256; q=dns/txt; c=relaxed/relaxed;
        d=infradead.org; s=casper.20170209;
 h=Sender:Content-Transfer-Encoding:
        MIME-Version:References:In-Reply-To:Message-Id:Date:Subject:Cc:To:From:
        Reply-To:Content-Type:Content-ID:Content-Description;
        bh=pWNWXU0q2YTOp9LS6CIUuWc+DOyY6dTv9ZJgSxrytoA=;
 b=u+kVoBLbLajl9QDJRDWxaY+83/
        kr4BsivC1jiJYACOGKucrHQfU91AaP4S9sGGpl7EKOSXufEKnwDNcx5x1ndBpwRAd3MNeKwRB5xx0
        owgw2wA+y00Bj+5ZjaPZol5Vcf/0aacpfcKfE5/UJBfJrfHgp5fCpVjRONDEwJq4MjFgyyOw66Rj+
        fLNsCmO+GnbPmIE/rSKL8DWiYtY7yjA0WrdQ7HSBd9WQlgkeX33AdEKH+HWnXW56nIuY/pMiAqobL
        kEFCkRYWdczGCkwnFanEM9m/XWvVS3kTKyQYE8KnvURJCYvYW9+UPN5TnjnCAuobFn4XCU5WtCqgi
        5Mbj0H5A==;
Received: from i7.infradead.org ([2001:8b0:10b:1:21e:67ff:fecb:7a92])
        by casper.infradead.org with esmtpsa (Exim 4.92.3 #3 (Red Hat Linux))
        id 1kXPRe-00009T-1M; Tue, 27 Oct 2020 13:55:26 +0000
Received: from dwoodhou by i7.infradead.org with local (Exim 4.93 #3 (Red Hat
 Linux))
        id 1kXPRd-002iLb-KB; Tue, 27 Oct 2020 13:55:25 +0000
From: David Woodhouse <dwmw2@infradead.org>
To: bonzini@redhat.com
Cc: Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Alexander Viro <viro@zeniv.linux.org.uk>,
        Jens Axboe <axboe@kernel.dk>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, linux-fsdevel@vger.kernel.org
Subject: [PATCH 1/3] eventfd: Export eventfd_ctx_do_read()
Date: Tue, 27 Oct 2020 13:55:21 +0000
Message-Id: <20201027135523.646811-2-dwmw2@infradead.org>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20201027135523.646811-1-dwmw2@infradead.org>
References: <1faa5405-3640-f4ad-5cd9-89a9e5e834e9@redhat.com>
 <20201027135523.646811-1-dwmw2@infradead.org>
MIME-Version: 1.0
Sender: David Woodhouse <dwmw2@infradead.org>
X-SRS-Rewrite: SMTP reverse-path rewritten from <dwmw2@infradead.org> by
 casper.infradead.org. See http://www.infradead.org/rpr.html
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: David Woodhouse <dwmw@amazon.co.uk>

Where events are consumed in the kernel, for example by KVM's
irqfd_wakeup() and VFIO's virqfd_wakeup(), they currently lack a
mechanism to drain the eventfd's counter.

Since the wait queue is already locked while the wakeup functions are
invoked, all they really need to do is call eventfd_ctx_do_read().

Add a check for the lock, and export it for them.

Signed-off-by: David Woodhouse <dwmw@amazon.co.uk>
---
 fs/eventfd.c            | 5 ++++-
 include/linux/eventfd.h | 6 ++++++
 2 files changed, 10 insertions(+), 1 deletion(-)

```
#### [PATCH v2 1/2] sched/wait: Add add_wait_queue_priority()
##### From: David Woodhouse <dwmw2@infradead.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Woodhouse <dwmw2@infradead.org>
X-Patchwork-Id: 11860641
Return-Path: <SRS0=+pC+=EC=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.9 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 484C8C63697
	for <kvm@archiver.kernel.org>; Tue, 27 Oct 2020 14:41:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C8D0E22284
	for <kvm@archiver.kernel.org>; Tue, 27 Oct 2020 14:41:02 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=infradead.org header.i=@infradead.org
 header.b="FGIqjYJG"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1762123AbgJ0Ok4 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 27 Oct 2020 10:40:56 -0400
Received: from casper.infradead.org ([90.155.50.34]:43762 "EHLO
        casper.infradead.org" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S368455AbgJ0Ojv (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 27 Oct 2020 10:39:51 -0400
DKIM-Signature: v=1; a=rsa-sha256; q=dns/txt; c=relaxed/relaxed;
        d=infradead.org; s=casper.20170209;
 h=Sender:Content-Transfer-Encoding:
        MIME-Version:References:In-Reply-To:Message-Id:Date:Subject:Cc:To:From:
        Reply-To:Content-Type:Content-ID:Content-Description;
        bh=Kqa4yz0KkuVBYzisYBgpS52crCT6S1zza5R6m2vJgLM=;
 b=FGIqjYJGytS879QBSS19P1et+/
        G83SLYh56u2jo3v9R4Xl7YAnYA/1nHPvC48yrrdY4hC5n2QEx48roKnw2B2GHbbzDAsmMqDY0MG7m
        ZGeFqpplzjYZj/9mDMyPQRZn+aRnVb9TfzSX+foN04QdCIpSh22fm6GU1XkDixzN7z9IXP1qoIFIJ
        r4Q180PqX4f92Xv+3lUOVyL4CkmIL5wA/4mIWnTrYUnVvZ+6pxrLbJqDZ0pECLtMVEG0SegS4bxBK
        4Ev9yPfxhnk98PhWNLi/kiL7sdTWhNcGM4x6nFQeGNjgUY2riSArBS83oPyyA1q2QhOM46i8Jwpfk
        ld4HXjmQ==;
Received: from i7.infradead.org ([2001:8b0:10b:1:21e:67ff:fecb:7a92])
        by casper.infradead.org with esmtpsa (Exim 4.92.3 #3 (Red Hat Linux))
        id 1kXQ8Z-0005C4-1A; Tue, 27 Oct 2020 14:39:47 +0000
Received: from dwoodhou by i7.infradead.org with local (Exim 4.93 #3 (Red Hat
 Linux))
        id 1kXQ8Y-002iqf-Eo; Tue, 27 Oct 2020 14:39:46 +0000
From: David Woodhouse <dwmw2@infradead.org>
To: linux-kernel@vger.kernel.org
Cc: Ingo Molnar <mingo@redhat.com>,
        Peter Zijlstra <peterz@infradead.org>,
        Juri Lelli <juri.lelli@redhat.com>,
        Vincent Guittot <vincent.guittot@linaro.org>,
        Dietmar Eggemann <dietmar.eggemann@arm.com>,
        Steven Rostedt <rostedt@goodmis.org>,
        Ben Segall <bsegall@google.com>, Mel Gorman <mgorman@suse.de>,
        Daniel Bristot de Oliveira <bristot@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org
Subject: [PATCH v2 1/2] sched/wait: Add add_wait_queue_priority()
Date: Tue, 27 Oct 2020 14:39:43 +0000
Message-Id: <20201027143944.648769-2-dwmw2@infradead.org>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20201027143944.648769-1-dwmw2@infradead.org>
References: <20201026175325.585623-1-dwmw2@infradead.org>
 <20201027143944.648769-1-dwmw2@infradead.org>
MIME-Version: 1.0
Sender: David Woodhouse <dwmw2@infradead.org>
X-SRS-Rewrite: SMTP reverse-path rewritten from <dwmw2@infradead.org> by
 casper.infradead.org. See http://www.infradead.org/rpr.html
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: David Woodhouse <dwmw@amazon.co.uk>

This allows an exclusive wait_queue_entry to be added at the head of the
queue, instead of the tail as normal. Thus, it gets to consume events
first without allowing non-exclusive waiters to be woken at all.

The (first) intended use is for KVM IRQFD, which currently has
inconsistent behaviour depending on whether posted interrupts are
available or not. If they are, KVM will bypass the eventfd completely
and deliver interrupts directly to the appropriate vCPU. If not, events
are delivered through the eventfd and userspace will receive them when
polling on the eventfd.

By using add_wait_queue_priority(), KVM will be able to consistently
consume events within the kernel without accidentally exposing them
to userspace when they're supposed to be bypassed. This, in turn, means
that userspace doesn't have to jump through hoops to avoid listening
on the erroneously noisy eventfd and injecting duplicate interrupts.

Signed-off-by: David Woodhouse <dwmw@amazon.co.uk>
---
 include/linux/wait.h | 12 +++++++++++-
 kernel/sched/wait.c  | 17 ++++++++++++++++-
 2 files changed, 27 insertions(+), 2 deletions(-)

```
#### [kvm-unit-tests RFC PATCH v2 1/5] arm64: Move get_id_aa64dfr0() in processor.h
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexandru Elisei <alexandru.elisei@arm.com>
X-Patchwork-Id: 11861127
Return-Path: <SRS0=+pC+=EC=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 07F23C56201
	for <kvm@archiver.kernel.org>; Tue, 27 Oct 2020 17:20:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A8963222E9
	for <kvm@archiver.kernel.org>; Tue, 27 Oct 2020 17:20:46 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1818317AbgJ0RS6 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 27 Oct 2020 13:18:58 -0400
Received: from foss.arm.com ([217.140.110.172]:47648 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1818301AbgJ0RSz (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 27 Oct 2020 13:18:55 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 3A49B139F;
        Tue, 27 Oct 2020 10:18:54 -0700 (PDT)
Received: from monolith.localdoman (unknown [172.31.20.19])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 D640B3F719;
        Tue, 27 Oct 2020 10:18:50 -0700 (PDT)
From: Alexandru Elisei <alexandru.elisei@arm.com>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu
Cc: drjones@redhat.com, pbonzini@redhat.com,
        Eric Auger <eric.auger@redhat.com>
Subject: [kvm-unit-tests RFC PATCH v2 1/5] arm64: Move get_id_aa64dfr0() in
 processor.h
Date: Tue, 27 Oct 2020 17:19:40 +0000
Message-Id: <20201027171944.13933-2-alexandru.elisei@arm.com>
X-Mailer: git-send-email 2.29.1
In-Reply-To: <20201027171944.13933-1-alexandru.elisei@arm.com>
References: <20201027171944.13933-1-alexandru.elisei@arm.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Eric Auger <eric.auger@redhat.com>

SPE support is reported in the ID_AA64DFR0_EL1 register. Move the function
get_id_aa64dfr0() from the pmu test to processor.h so it can be reused by
the SPE tests.

[ Alexandru E: Reworded commit ]

Signed-off-by: Eric Auger <eric.auger@redhat.com>
Signed-off-by: Alexandru Elisei <alexandru.elisei@arm.com>
---
 lib/arm64/asm/processor.h | 5 +++++
 arm/pmu.c                 | 1 -
 2 files changed, 5 insertions(+), 1 deletion(-)

```
#### [PATCH 3/8] vhost: vringh: use krealloc_array()
##### From: Bartosz Golaszewski <brgl@bgdev.pl>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Bartosz Golaszewski <brgl@bgdev.pl>
X-Patchwork-Id: 11860213
Return-Path: <SRS0=+pC+=EC=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id BDE79C55178
	for <kvm@archiver.kernel.org>; Tue, 27 Oct 2020 12:18:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 828E822202
	for <kvm@archiver.kernel.org>; Tue, 27 Oct 2020 12:18:30 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=bgdev-pl.20150623.gappssmtp.com
 header.i=@bgdev-pl.20150623.gappssmtp.com header.b="zjDtGi7Y"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2899714AbgJ0MRq (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 27 Oct 2020 08:17:46 -0400
Received: from mail-wr1-f67.google.com ([209.85.221.67]:39150 "EHLO
        mail-wr1-f67.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2899691AbgJ0MRp (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 27 Oct 2020 08:17:45 -0400
Received: by mail-wr1-f67.google.com with SMTP id y12so1641457wrp.6
        for <kvm@vger.kernel.org>; Tue, 27 Oct 2020 05:17:43 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=bgdev-pl.20150623.gappssmtp.com; s=20150623;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=83y0wprNKfgsPdFQwYqYyBfxNCy5k5K/4PHHSUQ4ytQ=;
        b=zjDtGi7YCC7prpyZ+g0XEgVkSu5ur1n0Z+4Onn8lSH6l5HhaPb2usVEdHqyUF70A1t
         aUTOf8Tq+CbFmCsQoZg/QZDfe6BYR/DFPrrBJwD6HiW7tjdfR/sBEWsWaZKnLZINtomX
         mE7Ig/cZHx2rYZqBTjkzv3ijY8hAIfVQDit/QeJSY5MeOkcFLBiM+J08PWHqktFzZQwX
         UlgrIFCSx9xqlv1zNEtaXs3tPI9VHBmr65ek6JPy/L/FS56cLdvQizETmDuasggJPK/w
         ztxubnZy+sT2oOAiJOCkZTqyimYvjT8WSyK/j0zpzQcNL15qg7LbhswKDAJng2PiYjm9
         YBtA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=83y0wprNKfgsPdFQwYqYyBfxNCy5k5K/4PHHSUQ4ytQ=;
        b=mZBSu6mU4fKukWRLcp0GRm/JL4gV8uPbpkO8OXE+tgO27vZdQoZ7vZH50Zr3lQ9ldw
         i9HK32PGLABertbpvlJin6i7fdTzqX5A0XK05vjdDF2CKsxLfKLnefPQeGUUlKsYSAjw
         F+CYgAvxpEHCr9QFqJzePoqks9F1J2x0WJ1ISJzOI5ASVr5ih22mYYDxXOfO3jJ/SbhQ
         RKfaAifqXLVODZghF5dgc/H9DKylw2y919AtCWRtoN/tI6+nlnuKECVrg1uNJjZf565f
         Fow7kUuMwjR05x+LUBNfYSjuerH1l9mHl2x84hpfiwJkJYfjFfdpFNMv5+LzA1gKtdMP
         YPdg==
X-Gm-Message-State: AOAM530wjjVqzm0cwZ+ShFk8VIWGT45MdSW4bJVFeZqkLPEfz+ePhYF7
        idLvOzti07gPSfe7zY3ZZFtCPA==
X-Google-Smtp-Source: 
 ABdhPJxMHI/sTmjLh3ji2z2BWBH7Xp+55j5r8SrJ3qqB6liqhHnL/S90fy042cmGylsf7I4Q+2Y+Yg==
X-Received: by 2002:a5d:6a49:: with SMTP id t9mr2477521wrw.194.1603801062271;
        Tue, 27 Oct 2020 05:17:42 -0700 (PDT)
Received: from debian-brgl.home (amarseille-656-1-4-167.w90-8.abo.wanadoo.fr.
 [90.8.158.167])
        by smtp.gmail.com with ESMTPSA id
 a2sm1731908wrs.55.2020.10.27.05.17.40
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 27 Oct 2020 05:17:41 -0700 (PDT)
From: Bartosz Golaszewski <brgl@bgdev.pl>
To: Andy Shevchenko <andriy.shevchenko@linux.intel.com>,
 Sumit Semwal <sumit.semwal@linaro.org>,
 Gustavo Padovan <gustavo@padovan.org>,
 =?utf-8?q?Christian_K=C3=B6nig?= <christian.koenig@amd.com>,
 Mauro Carvalho Chehab <mchehab@kernel.org>, Borislav Petkov <bp@alien8.de>,
 Tony Luck <tony.luck@intel.com>, James Morse <james.morse@arm.com>,
 Robert Richter <rric@kernel.org>,
 Maarten Lankhorst <maarten.lankhorst@linux.intel.com>,
 Maxime Ripard <mripard@kernel.org>, Thomas Zimmermann <tzimmermann@suse.de>,
 David Airlie <airlied@linux.ie>, Daniel Vetter <daniel@ffwll.ch>,
 Alexander Shishkin <alexander.shishkin@linux.intel.com>,
 Linus Walleij <linus.walleij@linaro.org>,
 "Michael S . Tsirkin" <mst@redhat.com>, Jason Wang <jasowang@redhat.com>,
 Christoph Lameter <cl@linux.com>, Pekka Enberg <penberg@kernel.org>,
 David Rientjes <rientjes@google.com>, Joonsoo Kim <iamjoonsoo.kim@lge.com>,
 Andrew Morton <akpm@linux-foundation.org>, Jaroslav Kysela <perex@perex.cz>,
 Takashi Iwai <tiwai@suse.com>
Cc: linux-media@vger.kernel.org, dri-devel@lists.freedesktop.org,
        linaro-mm-sig@lists.linaro.org, linux-kernel@vger.kernel.org,
        linux-edac@vger.kernel.org, linux-gpio@vger.kernel.org,
        kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org, linux-mm@kvack.org,
        alsa-devel@alsa-project.org,
        Bartosz Golaszewski <bgolaszewski@baylibre.com>
Subject: [PATCH 3/8] vhost: vringh: use krealloc_array()
Date: Tue, 27 Oct 2020 13:17:20 +0100
Message-Id: <20201027121725.24660-4-brgl@bgdev.pl>
X-Mailer: git-send-email 2.29.1
In-Reply-To: <20201027121725.24660-1-brgl@bgdev.pl>
References: <20201027121725.24660-1-brgl@bgdev.pl>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Bartosz Golaszewski <bgolaszewski@baylibre.com>

Use the helper that checks for overflows internally instead of manually
calculating the size of the new array.

Signed-off-by: Bartosz Golaszewski <bgolaszewski@baylibre.com>
Acked-by: Michael S. Tsirkin <mst@redhat.com>
---
 drivers/vhost/vringh.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [PATCH 2/8] ALSA: pcm: use krealloc_array()
##### From: Bartosz Golaszewski <brgl@bgdev.pl>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Bartosz Golaszewski <brgl@bgdev.pl>
X-Patchwork-Id: 11860211
Return-Path: <SRS0=+pC+=EC=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 64615C61DD8
	for <kvm@archiver.kernel.org>; Tue, 27 Oct 2020 12:18:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 36C4622284
	for <kvm@archiver.kernel.org>; Tue, 27 Oct 2020 12:18:36 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=bgdev-pl.20150623.gappssmtp.com
 header.i=@bgdev-pl.20150623.gappssmtp.com header.b="GYoAOUdp"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2899690AbgJ0MRn (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 27 Oct 2020 08:17:43 -0400
Received: from mail-wr1-f66.google.com ([209.85.221.66]:43230 "EHLO
        mail-wr1-f66.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2899670AbgJ0MRm (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 27 Oct 2020 08:17:42 -0400
Received: by mail-wr1-f66.google.com with SMTP id g12so1624779wrp.10
        for <kvm@vger.kernel.org>; Tue, 27 Oct 2020 05:17:41 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=bgdev-pl.20150623.gappssmtp.com; s=20150623;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=BD6BZhiJRXUg2mUZGG0fkwDlbzmZ0eUsKwHAsGlj294=;
        b=GYoAOUdpehA8D5iOITnO5eSHqy74EWPa2UIAtVbkWsImVc99HZ2Meqd4q5mrUiPwJi
         1APAlHnt2Cb4RjSuekciaevLzEzJMqfqHXfoSP/8Nqsfy2vu/QE/h1rKpHfgBNuem/9E
         bOYwNpK5Rv+6EItbQEiKit8Nwszh+pcjtDbIO4wjR4xJz/1weNgEVHMghJunm+Jmvs3D
         DwFELNR01LinoQoxBBCOkfLlLHqTKRB+bYhg8Wi8nXmI+1DlDpMCRqOKS/1P7aEomQVd
         T289FY4bD7H12YIHjVFYqTifMYdbsOOawVKJDDr9Ow0FRgVTPhbXfojcEyRGy0x+TbG2
         NISQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=BD6BZhiJRXUg2mUZGG0fkwDlbzmZ0eUsKwHAsGlj294=;
        b=Rk0OQ624wm0IwEKU0s0YH2TVagHv4MfYvznLEMxxtZRy5jp5Vj0nzy6ihwp3rxbToW
         hzzJY8PKOBD/fcdsuUGV9QNWk1plKAcPOJmdCYj6VYtJMJp7ChQ94PEWCSM/b4RAyDoJ
         05U2Hp5XCTQ/07ohYndJhKC0edZIA4nHiCo5qAMw/EB2Ne2UQNc9q4v5LhCpX623cyux
         qMYgQv5y4S9QFICcWhSnw/bfHDXHLN1EhkphJb79Ux8Pf6EAqXL4dcTCB/lVBdtsByV6
         6W+CcdDoTB3Hnizg3BStvZuACzIKd4UW91jpAAKQFprJnlD8fd0U1iVycx43/WNbFYeL
         rU5g==
X-Gm-Message-State: AOAM533NdincRRxNDjeHvAkun45MvwYX8vl9gKTsfRset3iY82QmQymt
        PtHcGtjPqtosBm4ci2M5QwNjlg==
X-Google-Smtp-Source: 
 ABdhPJycS5PuqPPHWbBOB4wuxjdkw4uku7T6ocjCFZm8vDs8KzBrNQe0wHUyzYWAYWc0X5WB+59JaQ==
X-Received: by 2002:a5d:6cc8:: with SMTP id c8mr2428078wrc.233.1603801060190;
        Tue, 27 Oct 2020 05:17:40 -0700 (PDT)
Received: from debian-brgl.home (amarseille-656-1-4-167.w90-8.abo.wanadoo.fr.
 [90.8.158.167])
        by smtp.gmail.com with ESMTPSA id
 a2sm1731908wrs.55.2020.10.27.05.17.38
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 27 Oct 2020 05:17:39 -0700 (PDT)
From: Bartosz Golaszewski <brgl@bgdev.pl>
To: Andy Shevchenko <andriy.shevchenko@linux.intel.com>,
 Sumit Semwal <sumit.semwal@linaro.org>,
 Gustavo Padovan <gustavo@padovan.org>,
 =?utf-8?q?Christian_K=C3=B6nig?= <christian.koenig@amd.com>,
 Mauro Carvalho Chehab <mchehab@kernel.org>, Borislav Petkov <bp@alien8.de>,
 Tony Luck <tony.luck@intel.com>, James Morse <james.morse@arm.com>,
 Robert Richter <rric@kernel.org>,
 Maarten Lankhorst <maarten.lankhorst@linux.intel.com>,
 Maxime Ripard <mripard@kernel.org>, Thomas Zimmermann <tzimmermann@suse.de>,
 David Airlie <airlied@linux.ie>, Daniel Vetter <daniel@ffwll.ch>,
 Alexander Shishkin <alexander.shishkin@linux.intel.com>,
 Linus Walleij <linus.walleij@linaro.org>,
 "Michael S . Tsirkin" <mst@redhat.com>, Jason Wang <jasowang@redhat.com>,
 Christoph Lameter <cl@linux.com>, Pekka Enberg <penberg@kernel.org>,
 David Rientjes <rientjes@google.com>, Joonsoo Kim <iamjoonsoo.kim@lge.com>,
 Andrew Morton <akpm@linux-foundation.org>, Jaroslav Kysela <perex@perex.cz>,
 Takashi Iwai <tiwai@suse.com>
Cc: linux-media@vger.kernel.org, dri-devel@lists.freedesktop.org,
        linaro-mm-sig@lists.linaro.org, linux-kernel@vger.kernel.org,
        linux-edac@vger.kernel.org, linux-gpio@vger.kernel.org,
        kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org, linux-mm@kvack.org,
        alsa-devel@alsa-project.org,
        Bartosz Golaszewski <bgolaszewski@baylibre.com>
Subject: [PATCH 2/8] ALSA: pcm: use krealloc_array()
Date: Tue, 27 Oct 2020 13:17:19 +0100
Message-Id: <20201027121725.24660-3-brgl@bgdev.pl>
X-Mailer: git-send-email 2.29.1
In-Reply-To: <20201027121725.24660-1-brgl@bgdev.pl>
References: <20201027121725.24660-1-brgl@bgdev.pl>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Bartosz Golaszewski <bgolaszewski@baylibre.com>

Use the helper that checks for overflows internally instead of manually
calculating the size of the new array.

Signed-off-by: Bartosz Golaszewski <bgolaszewski@baylibre.com>
Reviewed-by: Takashi Iwai <tiwai@suse.de>
---
 sound/core/pcm_lib.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH v3 01/11] KVM: x86: Get active PCID only when writing a CR3 value
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11861921
Return-Path: <SRS0=+pC+=EC=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 08B00C4363A
	for <kvm@archiver.kernel.org>; Tue, 27 Oct 2020 21:25:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6F963218AC
	for <kvm@archiver.kernel.org>; Tue, 27 Oct 2020 21:25:32 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S374004AbgJ0VZ3 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 27 Oct 2020 17:25:29 -0400
Received: from mga02.intel.com ([134.134.136.20]:56181 "EHLO mga02.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S373767AbgJ0VXx (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 27 Oct 2020 17:23:53 -0400
IronPort-SDR: 
 v7dvIGVwOkSq59LDxxMSfjrtdKgfvpeAOojNrSaM/O1jCD0+d6UGvAazJeVjnCO6EfZqQV6Ljr
 VUlLVjlqT+Gw==
X-IronPort-AV: E=McAfee;i="6000,8403,9787"; a="155133698"
X-IronPort-AV: E=Sophos;i="5.77,424,1596524400";
   d="scan'208";a="155133698"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga006.fm.intel.com ([10.253.24.20])
  by orsmga101.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 27 Oct 2020 14:23:50 -0700
IronPort-SDR: 
 RfwQ6NaYvaDPLuW8O5i3P4kMqOe3xLBXkmptCtlN7HyRuXl5fw6nq+oPiqKpL0zYB4Ta7Z/i10
 nJDsr6nhz5kg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,424,1596524400";
   d="scan'208";a="524886376"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.160])
  by fmsmga006.fm.intel.com with ESMTP; 27 Oct 2020 14:23:50 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v3 01/11] KVM: x86: Get active PCID only when writing a CR3
 value
Date: Tue, 27 Oct 2020 14:23:36 -0700
Message-Id: <20201027212346.23409-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20201027212346.23409-1-sean.j.christopherson@intel.com>
References: <20201027212346.23409-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Retrieve the active PCID only when writing a guest CR3 value, i.e. don't
get the PCID when using EPT.  The PCID is not used when EPT is enabled,
and must be manually stripped, which is annoying and unnecessary.
And on VMX, getting the active PCID also involves reading the guest's
CR3 and CR4.PCIDE, i.e. may add pointless VMREADs.

Opportunistically rename the pgd/pgd_level params to root_hpa and
root_level to better reflect their new roles.  Keep the function names,
as "load the guest PGD" is still accurate/correct.

Last, and probably least, pass root_hpa as a hpa_t/u64 instead of an
unsigned long.  The EPTP holds a 64-bit value, even in 32-bit mode, so
in theory EPT could support HIGHMEM for 32-bit KVM.  Never mind that
doing so would require changing the MMU page allocators and reworking
the MMU to use kmap().

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/include/asm/kvm_host.h |  4 ++--
 arch/x86/kvm/mmu.h              |  2 +-
 arch/x86/kvm/svm/svm.c          |  4 ++--
 arch/x86/kvm/vmx/vmx.c          | 13 ++++++-------
 arch/x86/kvm/vmx/vmx.h          |  3 +--
 5 files changed, 12 insertions(+), 14 deletions(-)

```
#### [PATCH 1/3] KVM: x86/mmu: Add helper macro for computing hugepage GFN mask
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11861933
Return-Path: <SRS0=+pC+=EC=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 45F18C4363A
	for <kvm@archiver.kernel.org>; Tue, 27 Oct 2020 21:43:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DD6F020829
	for <kvm@archiver.kernel.org>; Tue, 27 Oct 2020 21:43:06 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S374280AbgJ0VnF (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 27 Oct 2020 17:43:05 -0400
Received: from mga11.intel.com ([192.55.52.93]:17169 "EHLO mga11.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S374256AbgJ0VnC (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 27 Oct 2020 17:43:02 -0400
IronPort-SDR: 
 G1BL6UqfP8e9w1uAw3pawX4/jIOer0mXCNhWKo3WWgghNBPUBZKfLEX3jzSbP6/bwEZ46M2iSN
 TfHBinkFOXIQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9787"; a="164667231"
X-IronPort-AV: E=Sophos;i="5.77,424,1596524400";
   d="scan'208";a="164667231"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga002.jf.intel.com ([10.7.209.21])
  by fmsmga102.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 27 Oct 2020 14:43:01 -0700
IronPort-SDR: 
 xQnbAFZdcwU6l7YPlAUFUl22HWnmmfHRRxcXko/s2rlFVORmc34FIxI4Uz4/1gDt/33HytAuKQ
 VwoRw9ylPNRg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,424,1596524400";
   d="scan'208";a="334537304"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.160])
  by orsmga002.jf.intel.com with ESMTP; 27 Oct 2020 14:43:01 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Ben Gardon <bgardon@google.com>
Subject: [PATCH 1/3] KVM: x86/mmu: Add helper macro for computing hugepage GFN
 mask
Date: Tue, 27 Oct 2020 14:42:58 -0700
Message-Id: <20201027214300.1342-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20201027214300.1342-1-sean.j.christopherson@intel.com>
References: <20201027214300.1342-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add a helper to compute the GFN mask given a hugepage level, KVM is
accumulating quite a few users with the addition of the TDP MMU.

Note, gcc is clever enough to use a single NEG instruction instead of
SUB+NOT, i.e. use the more common "~(level -1)" pattern instead of
round_gfn_for_level()'s direct two's complement trickery.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Reviewed-by: Ben Gardon <bgardon@google.com>
---
 arch/x86/include/asm/kvm_host.h | 1 +
 arch/x86/kvm/mmu/mmu.c          | 2 +-
 arch/x86/kvm/mmu/paging_tmpl.h  | 4 ++--
 arch/x86/kvm/mmu/tdp_iter.c     | 2 +-
 4 files changed, 5 insertions(+), 4 deletions(-)

```
#### [PATCH 1/8] mm: slab: provide krealloc_array()
##### From: Bartosz Golaszewski <brgl@bgdev.pl>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Bartosz Golaszewski <brgl@bgdev.pl>
X-Patchwork-Id: 11860217
Return-Path: <SRS0=+pC+=EC=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A4A18C5DF9E
	for <kvm@archiver.kernel.org>; Tue, 27 Oct 2020 12:18:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7346522281
	for <kvm@archiver.kernel.org>; Tue, 27 Oct 2020 12:18:56 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=bgdev-pl.20150623.gappssmtp.com
 header.i=@bgdev-pl.20150623.gappssmtp.com header.b="I6NX/4rt"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1751008AbgJ0MSz (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 27 Oct 2020 08:18:55 -0400
Received: from mail-wm1-f67.google.com ([209.85.128.67]:38899 "EHLO
        mail-wm1-f67.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2411726AbgJ0MRk (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 27 Oct 2020 08:17:40 -0400
Received: by mail-wm1-f67.google.com with SMTP id l15so1203371wmi.3
        for <kvm@vger.kernel.org>; Tue, 27 Oct 2020 05:17:38 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=bgdev-pl.20150623.gappssmtp.com; s=20150623;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=2L3lr/8sLf7Z5y8Aim//8p5VZua449ayHzLh+PHsAEM=;
        b=I6NX/4rt5CDmPWW1saFsLZWRkPzrAH2KBDwRbhX67CXdUXPPBiQxknBpev7HNopX7v
         T4hCqsqEQ+8slSjg9oVsWiouDFBCjUxT2tQhZ7IsbEhntldfWt0pGCC18RYKkF8HyqJx
         9RTh6mcLw4a5t85mWwIRiBjPnX8DfWDpwoFyv2x3tXDUqIcE4ydx14krTVgwR7Mujyzi
         c7FeX7rajI1jIGSq0UFLTHM/eXW6rmNIQ+ewJ8tVOZErdCBzyF6pzeFt8JKoMnrfmiqh
         HH4RQszopE21d3R0VoR6twetVnWG7wRPJVw9OB9Ugbj6v6iDFbcVtXVpkFtNwEVIqDq0
         2QCw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=2L3lr/8sLf7Z5y8Aim//8p5VZua449ayHzLh+PHsAEM=;
        b=T68TUh+GmdrFsi5DCS3Xj90jaG/6an26PPYob945qnNd3Zudi4W5CtIoLws48/F+Xh
         JlqW0DWxytaPtAZcE1uY3C/XQc4Gb902tVTqKnGZY2Y5Hr2nrjyfPo1pb0a2XVUspm52
         A/A5CTh8trdUe0I//WhedW7njkC0vpGWsku0DBNC7kelbm56pvG7Q5wqGGgbtd4HJgex
         Z3/1ayMEaLGs8uQ2n4oiZS4TWfCEXkcjBzGzvdRCl0j2HtYZLD5MF2xcZtGwFve4A73Z
         CL2Ambk1yEZGWmXhYUIfCSwqpBL/fOxjG+7nZGmbXxkQ6bmwth5Yfeywgrngw2MtIpoK
         HV8Q==
X-Gm-Message-State: AOAM533ABySwDawTs8ggnh+6xqQWzBJRU8k+we1R5pL9vXfvCYfvHmY7
        pDSlIcy7Pti797Q61ox5cf5Pyg==
X-Google-Smtp-Source: 
 ABdhPJwnQfDZtXuM3jzzK38lXBwCGy/kfsjXsJcKEg+cED0SodtStCj40BizmPHJbimBDnnjg0sfuQ==
X-Received: by 2002:a1c:7c1a:: with SMTP id x26mr2463834wmc.4.1603801057987;
        Tue, 27 Oct 2020 05:17:37 -0700 (PDT)
Received: from debian-brgl.home (amarseille-656-1-4-167.w90-8.abo.wanadoo.fr.
 [90.8.158.167])
        by smtp.gmail.com with ESMTPSA id
 a2sm1731908wrs.55.2020.10.27.05.17.36
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 27 Oct 2020 05:17:37 -0700 (PDT)
From: Bartosz Golaszewski <brgl@bgdev.pl>
To: Andy Shevchenko <andriy.shevchenko@linux.intel.com>,
 Sumit Semwal <sumit.semwal@linaro.org>,
 Gustavo Padovan <gustavo@padovan.org>,
 =?utf-8?q?Christian_K=C3=B6nig?= <christian.koenig@amd.com>,
 Mauro Carvalho Chehab <mchehab@kernel.org>, Borislav Petkov <bp@alien8.de>,
 Tony Luck <tony.luck@intel.com>, James Morse <james.morse@arm.com>,
 Robert Richter <rric@kernel.org>,
 Maarten Lankhorst <maarten.lankhorst@linux.intel.com>,
 Maxime Ripard <mripard@kernel.org>, Thomas Zimmermann <tzimmermann@suse.de>,
 David Airlie <airlied@linux.ie>, Daniel Vetter <daniel@ffwll.ch>,
 Alexander Shishkin <alexander.shishkin@linux.intel.com>,
 Linus Walleij <linus.walleij@linaro.org>,
 "Michael S . Tsirkin" <mst@redhat.com>, Jason Wang <jasowang@redhat.com>,
 Christoph Lameter <cl@linux.com>, Pekka Enberg <penberg@kernel.org>,
 David Rientjes <rientjes@google.com>, Joonsoo Kim <iamjoonsoo.kim@lge.com>,
 Andrew Morton <akpm@linux-foundation.org>, Jaroslav Kysela <perex@perex.cz>,
 Takashi Iwai <tiwai@suse.com>
Cc: linux-media@vger.kernel.org, dri-devel@lists.freedesktop.org,
        linaro-mm-sig@lists.linaro.org, linux-kernel@vger.kernel.org,
        linux-edac@vger.kernel.org, linux-gpio@vger.kernel.org,
        kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org, linux-mm@kvack.org,
        alsa-devel@alsa-project.org,
        Bartosz Golaszewski <bgolaszewski@baylibre.com>
Subject: [PATCH 1/8] mm: slab: provide krealloc_array()
Date: Tue, 27 Oct 2020 13:17:18 +0100
Message-Id: <20201027121725.24660-2-brgl@bgdev.pl>
X-Mailer: git-send-email 2.29.1
In-Reply-To: <20201027121725.24660-1-brgl@bgdev.pl>
References: <20201027121725.24660-1-brgl@bgdev.pl>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Bartosz Golaszewski <bgolaszewski@baylibre.com>

When allocating an array of elements, users should check for
multiplication overflow or preferably use one of the provided helpers
like: kmalloc_array().

There's no krealloc_array() counterpart but there are many users who use
regular krealloc() to reallocate arrays. Let's provide an actual
krealloc_array() implementation.

Signed-off-by: Bartosz Golaszewski <bgolaszewski@baylibre.com>
Acked-by: Vlastimil Babka <vbabka@suse.cz>
---
 include/linux/slab.h | 11 +++++++++++
 1 file changed, 11 insertions(+)

```
#### [RFC PATCH kvmtool v3 1/3] update_headers: Sync kvm UAPI headers with linux 5.10-rc1
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexandru Elisei <alexandru.elisei@arm.com>
X-Patchwork-Id: 11861121
Return-Path: <SRS0=+pC+=EC=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 63160C6379D
	for <kvm@archiver.kernel.org>; Tue, 27 Oct 2020 17:16:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0F5D920809
	for <kvm@archiver.kernel.org>; Tue, 27 Oct 2020 17:16:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1818028AbgJ0RQ6 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 27 Oct 2020 13:16:58 -0400
Received: from foss.arm.com ([217.140.110.172]:47486 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1818013AbgJ0RQx (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 27 Oct 2020 13:16:53 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 61DA2139F;
        Tue, 27 Oct 2020 10:16:51 -0700 (PDT)
Received: from monolith.localdoman (unknown [172.31.20.19])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 797C13F719;
        Tue, 27 Oct 2020 10:16:48 -0700 (PDT)
From: Alexandru Elisei <alexandru.elisei@arm.com>
To: kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org
Cc: will@kernel.org, julien.thierry.kdev@gmail.com,
        Sudeep Holla <sudeep.holla@arm.com>
Subject: [RFC PATCH kvmtool v3 1/3] update_headers: Sync kvm UAPI headers with
 linux 5.10-rc1
Date: Tue, 27 Oct 2020 17:17:33 +0000
Message-Id: <20201027171735.13638-2-alexandru.elisei@arm.com>
X-Mailer: git-send-email 2.29.1
In-Reply-To: <20201027171735.13638-1-alexandru.elisei@arm.com>
References: <20201027171735.13638-1-alexandru.elisei@arm.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Sudeep Holla <sudeep.holla@arm.com>

The local copies of the kvm user API headers are getting stale.  In
preparation for some arch-specific updated, this patch reflects a re-run of
util/update_headers.sh to pull in upstream updates from linux v5.10-rc1.

[ Alexandru E: Updated headers to Linux tag v5.10-rc1 ]

Signed-off-by: Sudeep Holla <sudeep.holla@arm.com>
Signed-off-by: Alexandru Elisei <alexandru.elisei@arm.com>
---
 arm/aarch64/include/asm/kvm.h |  53 +++++++++++++--
 include/linux/kvm.h           | 117 ++++++++++++++++++++++++++++++++--
 powerpc/include/asm/kvm.h     |   8 +++
 x86/include/asm/kvm.h         |  42 +++++++++++-
 4 files changed, 209 insertions(+), 11 deletions(-)

```
#### [PATCH v1 1/5] driver core: platform: Introduce platform_get_mem_or_io_resource()
##### From: Andy Shevchenko <andriy.shevchenko@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andy Shevchenko <andriy.shevchenko@linux.intel.com>
X-Patchwork-Id: 11861257
Return-Path: <SRS0=+pC+=EC=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 38B29C55178
	for <kvm@archiver.kernel.org>; Tue, 27 Oct 2020 17:59:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D6D5C21556
	for <kvm@archiver.kernel.org>; Tue, 27 Oct 2020 17:59:44 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1823657AbgJ0R7Z (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 27 Oct 2020 13:59:25 -0400
Received: from mga03.intel.com ([134.134.136.65]:34126 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1823203AbgJ0R6L (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 27 Oct 2020 13:58:11 -0400
IronPort-SDR: 
 fW7T60hx1U28IPgMbQ/ufL/NsJsLrDr8h6qOpKkB5QSrnKFjB6eeDphAXriX73rCczz297b1SU
 KEzTXfMmJZLg==
X-IronPort-AV: E=McAfee;i="6000,8403,9787"; a="168230686"
X-IronPort-AV: E=Sophos;i="5.77,424,1596524400";
   d="scan'208";a="168230686"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by orsmga103.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 27 Oct 2020 10:58:10 -0700
IronPort-SDR: 
 pVBI96o6WMqJ6mq5a8oXe8bATKbSaxP/VCM1wYfH+mNa36hNrOtpMcv+1HKUfbt7UIprRLPVTs
 BcddLyFjzpHQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,424,1596524400";
   d="scan'208";a="303841822"
Received: from black.fi.intel.com ([10.237.72.28])
  by fmsmga008.fm.intel.com with ESMTP; 27 Oct 2020 10:58:07 -0700
Received: by black.fi.intel.com (Postfix, from userid 1003)
        id E4DE0179; Tue, 27 Oct 2020 19:58:06 +0200 (EET)
From: Andy Shevchenko <andriy.shevchenko@linux.intel.com>
To: Greg Kroah-Hartman <gregkh@linuxfoundation.org>,
        linux-kernel@vger.kernel.org
Cc: Andy Shevchenko <andriy.shevchenko@linux.intel.com>,
        Eric Auger <eric.auger@redhat.com>,
        Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>, kvm@vger.kernel.org,
        linux-usb@vger.kernel.org, Peng Hao <peng.hao2@zte.com.cn>,
        Arnd Bergmann <arnd@arndb.de>
Subject: [PATCH v1 1/5] driver core: platform: Introduce
 platform_get_mem_or_io_resource()
Date: Tue, 27 Oct 2020 19:58:02 +0200
Message-Id: <20201027175806.20305-1-andriy.shevchenko@linux.intel.com>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

There are at least few existing users of the proposed API which
retrieves either MEM or IO resource from platform device.

Make it common to utilize in the existing and new users.

Signed-off-by: Andy Shevchenko <andriy.shevchenko@linux.intel.com>
Cc: Eric Auger <eric.auger@redhat.com>
Cc: Alex Williamson <alex.williamson@redhat.com>
Cc: Cornelia Huck <cohuck@redhat.com>
Cc: kvm@vger.kernel.org
Cc: linux-usb@vger.kernel.org
Cc: Peng Hao <peng.hao2@zte.com.cn>
Cc: Arnd Bergmann <arnd@arndb.de>
---
 include/linux/platform_device.h | 13 +++++++++++++
 1 file changed, 13 insertions(+)

```
