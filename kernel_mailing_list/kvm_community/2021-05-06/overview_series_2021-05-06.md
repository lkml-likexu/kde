#### [RFC][PATCH v1 01/10] Extend the MemTxAttrs to include a 'debug' flag. The flag can be used as general indicator that operation was triggered
##### From: Yuan Yao <yuan.yao@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yuan Yao <yuan.yao@linux.intel.com>
X-Patchwork-Id: 12241445
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 5E57DC433ED
	for <kvm@archiver.kernel.org>; Thu,  6 May 2021 01:41:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3D170613BC
	for <kvm@archiver.kernel.org>; Thu,  6 May 2021 01:41:02 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230187AbhEFBl6 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 5 May 2021 21:41:58 -0400
Received: from mga12.intel.com ([192.55.52.136]:22915 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229465AbhEFBl6 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 5 May 2021 21:41:58 -0400
IronPort-SDR: 
 E6aK9f+POsUPp/FGVVUf8eh/egqTGRVbNRx04zYjCzd73oWxxGcSaTrRhlV79L/jlQ3CJEWnVb
 8OVSIYq8Wl8w==
X-IronPort-AV: E=McAfee;i="6200,9189,9975"; a="177907508"
X-IronPort-AV: E=Sophos;i="5.82,276,1613462400";
   d="scan'208";a="177907508"
Received: from orsmga001.jf.intel.com ([10.7.209.18])
  by fmsmga106.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 05 May 2021 18:41:01 -0700
IronPort-SDR: 
 gHpi7Qln+3G46fad71umHSqklKdUAnUOZATJGR5cUpLHIvB9k7Vq5oB08oueKINbpSYtqNJZ6J
 G8XX0TzS1N2w==
X-IronPort-AV: E=Sophos;i="5.82,276,1613462400";
   d="scan'208";a="469220304"
Received: from yy-desk-7060.sh.intel.com ([10.239.159.38])
  by orsmga001-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 05 May 2021 18:40:46 -0700
From: Yuan Yao <yuan.yao@linux.intel.com>
To: pbonzini@redhat.com
Cc: qemu-devel@nongnu.org, kvm@vger.kernel.org, dgilbert@redhat.com,
        ehabkost@redhat.com, mst@redhat.com, armbru@redhat.com,
        mtosatti@redhat.com, ashish.kalra@amd.com, Thomas.Lendacky@amd.com,
        brijesh.singh@amd.com, isaku.yamahata@intel.com, yuan.yao@intel.com
Subject: [RFC][PATCH v1 01/10] Extend the MemTxAttrs to include a 'debug'
 flag. The flag can be used as general indicator that operation was triggered
 by the debugger.
Date: Thu,  6 May 2021 09:40:28 +0800
Message-Id: <20210506014037.11982-2-yuan.yao@linux.intel.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20210506014037.11982-1-yuan.yao@linux.intel.com>
References: <20210506014037.11982-1-yuan.yao@linux.intel.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Brijesh Singh <brijesh.singh@amd.com>

A subsequent patch will set the debug=1 when issuing a memory access
from the gdbstub or HMP commands. This is a prerequisite to support
debugging an encrypted guest. When a request with debug=1 is seen, the
encryption APIs will be used to access the guest memory.

Signed-off-by: Brijesh Singh <brijesh.singh@amd.com>
Signed-off-by: Ashish Kalra <ashish.kalra@amd.com>

```
#### [GIT PULL] VFIO updates for v5.13-rc1 pt2
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alex Williamson <alex.williamson@redhat.com>
X-Patchwork-Id: 12242945
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.4 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,INCLUDES_PULL_REQUEST,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,
	SPF_HELO_NONE,SPF_PASS autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E7033C433ED
	for <kvm@archiver.kernel.org>; Thu,  6 May 2021 18:31:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B269C61154
	for <kvm@archiver.kernel.org>; Thu,  6 May 2021 18:31:18 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234358AbhEFScQ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 6 May 2021 14:32:16 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:24374 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S231839AbhEFScP (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 6 May 2021 14:32:15 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1620325877;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=RKug1+n7aNUKpd2/5y9E1AAuMfgec3Gz+e4TxaTVI6A=;
        b=C5LENBDArtySyBFU5b76iygBHTOpOtYFldYP4seV0zBMURLcohBlUvknlIvhlRo7psLdcn
        aKW7o8gGTqIW5+D8ptO8WWFeKYMwWoGok7tgxwv1tDRrw6Sds7RDDJcusNmrRku2KxP1br
        wH5AFj1n65fcPbD14Ewk/ukPAr8w7cE=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-265-tKPEBZXnM1CNUh-qlS8Vww-1; Thu, 06 May 2021 14:31:15 -0400
X-MC-Unique: tKPEBZXnM1CNUh-qlS8Vww-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 9C5D68014D8;
        Thu,  6 May 2021 18:31:13 +0000 (UTC)
Received: from redhat.com (ovpn-113-225.phx2.redhat.com [10.3.113.225])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 382D65D9DE;
        Thu,  6 May 2021 18:31:12 +0000 (UTC)
Date: Thu, 6 May 2021 12:31:11 -0600
From: Alex Williamson <alex.williamson@redhat.com>
To: Linus Torvalds <torvalds@linux-foundation.org>
Cc: <linux-kernel@vger.kernel.org>,
        "kvm@vger.kernel.org" <kvm@vger.kernel.org>, hi@alyssa.is,
        dan.carpenter@oracle.com
Subject: [GIT PULL] VFIO updates for v5.13-rc1 pt2
Message-ID: <20210506123111.6b6c0bf3@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Linus,

A 2nd small set of commits for this merge window, primarily to unbreak
some deletions from our uAPI header before rc1.  Thanks,

Alex

The following changes since commit 5e321ded302da4d8c5d5dd953423d9b748ab3775:

  Merge tag 'for-5.13/parisc' of git://git.kernel.org/pub/scm/linux/kernel/git/deller/parisc-linux (2021-05-03 13:47:17 -0700)

are available in the Git repository at:

  git://github.com/awilliam/linux-vfio.git tags/vfio-v5.13-rc1pt2

for you to fetch changes up to cc35518d29bc8e38902866b74874b4a3f1ad3617:

  docs: vfio: fix typo (2021-05-05 10:20:33 -0600)

----------------------------------------------------------------
VFIO updates for v5.13-rc1 pt2

 - Additional mdev sample driver cleanup (Dan Carpenter)

 - Doc fix (Alyssa Ross)

 - Unbreak uAPI from NVLink2 support removal (Alex Williamson)

----------------------------------------------------------------
Alex Williamson (1):
      vfio/pci: Revert nvlink removal uAPI breakage

Alyssa Ross (1):
      docs: vfio: fix typo

Dan Carpenter (1):
      vfio/mdev: remove unnecessary NULL check in mbochs_create()

 Documentation/driver-api/vfio.rst |  2 +-
 include/uapi/linux/vfio.h         | 46 +++++++++++++++++++++++++++++++++++----
 samples/vfio-mdev/mbochs.c        |  2 --
 samples/vfio-mdev/mdpy.c          |  3 +--
 4 files changed, 44 insertions(+), 9 deletions(-)
```
#### [PATCH] kvm: Cap halt polling at kvm->max_halt_poll_ns
##### From: Venkatesh Srinivas <venkateshs@chromium.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Venkatesh Srinivas <venkateshs@chromium.org>
X-Patchwork-Id: 12242421
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-19.4 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D8DCEC43460
	for <kvm@archiver.kernel.org>; Thu,  6 May 2021 15:25:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A6D0461626
	for <kvm@archiver.kernel.org>; Thu,  6 May 2021 15:25:46 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S235197AbhEFP0m (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 6 May 2021 11:26:42 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:59982 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S235542AbhEFP0C (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 6 May 2021 11:26:02 -0400
Received: from mail-pf1-x42a.google.com (mail-pf1-x42a.google.com
 [IPv6:2607:f8b0:4864:20::42a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 41CA0C06134E
        for <kvm@vger.kernel.org>; Thu,  6 May 2021 08:24:59 -0700 (PDT)
Received: by mail-pf1-x42a.google.com with SMTP id i190so5328163pfc.12
        for <kvm@vger.kernel.org>; Thu, 06 May 2021 08:24:59 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=chromium.org; s=google;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=shlq1RaufKc8PpYeWS/qnMOG5GjUOzt0+QikQVANxeE=;
        b=mMUovUXN46smRWzujAFi7lKyBjSRyXqPjmkFWpDBnl3SWxEroEqQUsqJ2+ZX16/5fF
         Cze1yJPAMKSmvtOb/Fdzu+1RxCIJRlli7tB+z6LX29WxGJkpKFPw8lz3H1R+Ch/DZiK1
         z0wbXgsEp6DPMjJ1AEGOeMNplVZhmJhoAo2ts=
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=shlq1RaufKc8PpYeWS/qnMOG5GjUOzt0+QikQVANxeE=;
        b=IgNEzuiK7qZbcGWgbLyexInc6tmDshaHXzx3bTt3i8m4YW+5mNASRStWK/dUEn9s5o
         cpWI6c9n0q1+SUjoZHhm9HlrH2PTdMzqn1OaJh5DrkYO49c/KHgcqo1S9h+g+mmNqBTv
         UL1ykrDExQmDTTYNrm1IBEE+d8zYP+HthfXabrsTYhSUHC/vuBa9mrr7/UV8PGh1LKwL
         MrADK5zow+Y9HV4ZEzdZbfCJsSKUq7SmRqZ8iOFipNymaLBKVWPC1/ktm0yeqz9EOE44
         oSo1kSyOpuwvZZM8I5Y15XmyyevXVzbnMXkcXRXzfGynVN3gfIHmkNjmuzk7KDd/rA1f
         ugGw==
X-Gm-Message-State: AOAM532uTJ2yp4CMPdkp/R8svM8hywuzl79J4yiDRov+VWCQgJsRku5Y
        j19XAf4p3goV3iRCRlqQiDGmuf/zhN67gQ==
X-Google-Smtp-Source: 
 ABdhPJz4FSt3yUXAuqeCbI3i38KjH8f3dIVyp1YL46NRW35t0PLETOSwrqqYSNW0mp7q8fZC73EeSw==
X-Received: by 2002:aa7:82c3:0:b029:276:1d63:cd0e with SMTP id
 f3-20020aa782c30000b02902761d63cd0emr5192264pfn.13.1620314698535;
        Thu, 06 May 2021 08:24:58 -0700 (PDT)
Received: from portland.c.googlers.com.com
 (254.80.82.34.bc.googleusercontent.com. [34.82.80.254])
        by smtp.gmail.com with ESMTPSA id
 d63sm10660556pjk.10.2021.05.06.08.24.58
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 06 May 2021 08:24:58 -0700 (PDT)
From: Venkatesh Srinivas <venkateshs@chromium.org>
To: kvm@vger.kernel.org, dmatlack@google.com, pbonzini@redhat.com
Cc: Venkatesh Srinivas <venkateshs@chromium.org>
Subject: [PATCH] kvm: Cap halt polling at kvm->max_halt_poll_ns
Date: Thu,  6 May 2021 15:24:43 +0000
Message-Id: <20210506152442.4010298-1-venkateshs@chromium.org>
X-Mailer: git-send-email 2.31.1.607.g51e8a6a459-goog
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: David Matlack <dmatlack@google.com>

When growing halt-polling, there is no check that the poll time exceeds
the per-VM limit. It's possible for vcpu->halt_poll_ns to grow past
kvm->max_halt_poll_ns and stay there until a halt which takes longer
than kvm->halt_poll_ns.

Signed-off-by: David Matlack <dmatlack@google.com>
Signed-off-by: Venkatesh Srinivas <venkateshs@chromium.org>
---
 virt/kvm/kvm_main.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH 1/2] KVM: SVM: Return -EFAULT if copy_to_user() for SEV mig packet header fails
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12242927
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 5A9FCC433ED
	for <kvm@archiver.kernel.org>; Thu,  6 May 2021 17:58:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1C3CD6113E
	for <kvm@archiver.kernel.org>; Thu,  6 May 2021 17:58:37 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S236509AbhEFR7e (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 6 May 2021 13:59:34 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:38218 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S236455AbhEFR7c (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 6 May 2021 13:59:32 -0400
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 6135FC061761
        for <kvm@vger.kernel.org>; Thu,  6 May 2021 10:58:34 -0700 (PDT)
Received: by mail-yb1-xb4a.google.com with SMTP id
 g27-20020a25b11b0000b02904f8641ec14cso992876ybj.12
        for <kvm@vger.kernel.org>; Thu, 06 May 2021 10:58:34 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=reply-to:date:in-reply-to:message-id:mime-version:references
         :subject:from:to:cc;
        bh=ancbaT0mva6sBIo0ZbeTujrtjNlUrJuCzlWUM3NuRWU=;
        b=iBQWdMoEMW3Ix1/ReNy3fOHblCht7nIjAJh+po7T62gIyn+JnfM7W/J3trRS/XlSnb
         0CCFtbs54UnbBNj0FpvqEfUQxdfdgPUz/IWsMZhsuu3qR9PcF2Sx8uKBzP0ThbyjhSOn
         DhlufWaq6xGppWddxvjDYsRu+Dz6KAFUnKs0FPrT6Z6kja8aAnWOW/798NEMAbP7ygg5
         aQZkFYH2d/lzyFoymM9ROM/u8KL5Wp9Mu2ahUM5MR5/o92SaFiytwAY++7U24zuD/DRC
         Tawrzt6QxOBqGT7J+XFFXfKWg4ZfoknNR0aCwsvP91/AL+ORQsxR0Gft/8h42wVzXt0V
         uM/w==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:reply-to:date:in-reply-to:message-id
         :mime-version:references:subject:from:to:cc;
        bh=ancbaT0mva6sBIo0ZbeTujrtjNlUrJuCzlWUM3NuRWU=;
        b=MCQAca6MbM+Cr49avG+Ro3YlyNJnmMAMvELZtZHjKg7NZV0NARIF5wcArGyrNnMJ5Z
         98C+5iqikxkSGbYa1bacx//f+fFzE8zNvE237GiuCEsg+lYkxplkBTmzR9AEJelwRb76
         yIiJqzpheXeRXnd78uMrabCZjwJ+i8rkxx1th7eBcXv3j/FmD54r4/HEJuWdR0UOQvEp
         YDLoag56LsD2RsCI3J1lRa05jBjNErosna5GWIf/AjPX+OckOEGdGfZktqHRuB7Naz3m
         q0YHpJ87CnXolnoEUNk72xWb1bSrWP/yeUn/ayx+p0lh3iEZA2UzCpCvuAs0VGDWVJZB
         6a3g==
X-Gm-Message-State: AOAM532Cm/ANrf5GQKlzWIO7M6AHQeChBmAwoGsi8nL++jseNnidtiY1
        Pl78/0Oz1CQfNOHxdiS5H4OFyQQsgjM=
X-Google-Smtp-Source: 
 ABdhPJzpNwdgxL8bgvjkEpy2HNyWm/BDq06M8OiZAT5LesPCEyeyB78+drO+mdx0UJf79Yi0C0IvJlCLWSo=
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:818d:5ca3:d49c:cfc8])
 (user=seanjc job=sendgmr) by 2002:a25:d082:: with SMTP id
 h124mr7327204ybg.381.1620323913557;
 Thu, 06 May 2021 10:58:33 -0700 (PDT)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Thu,  6 May 2021 10:58:25 -0700
In-Reply-To: <20210506175826.2166383-1-seanjc@google.com>
Message-Id: <20210506175826.2166383-2-seanjc@google.com>
Mime-Version: 1.0
References: <20210506175826.2166383-1-seanjc@google.com>
X-Mailer: git-send-email 2.31.1.607.g51e8a6a459-goog
Subject: [PATCH 1/2] KVM: SVM: Return -EFAULT if copy_to_user() for SEV mig
 packet header fails
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org,
        Dan Carpenter <dan.carpenter@oracle.com>,
        Steve Rutherford <srutherford@google.com>,
        Brijesh Singh <brijesh.singh@amd.com>,
        Ashish Kalra <ashish.kalra@amd.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Return -EFAULT if copy_to_user() fails; if accessing user memory faults,
copy_to_user() returns the number of bytes remaining, not an error code.

Reported-by: Dan Carpenter <dan.carpenter@oracle.com>
Cc: Steve Rutherford <srutherford@google.com>
Cc: Brijesh Singh <brijesh.singh@amd.com>
Cc: Ashish Kalra <ashish.kalra@amd.com>
Fixes: d3d1af85e2c7 ("KVM: SVM: Add KVM_SEND_UPDATE_DATA command")
Signed-off-by: Sean Christopherson <seanjc@google.com>
---
 arch/x86/kvm/svm/sev.c | 5 +++--
 1 file changed, 3 insertions(+), 2 deletions(-)

```
#### [PATCH] KVM: SVM: Move GHCB unmapping to fix RCU warning
##### From: Tom Lendacky <thomas.lendacky@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tom Lendacky <thomas.lendacky@amd.com>
X-Patchwork-Id: 12243505
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id BE1A2C433ED
	for <kvm@archiver.kernel.org>; Thu,  6 May 2021 20:14:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8165861075
	for <kvm@archiver.kernel.org>; Thu,  6 May 2021 20:14:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233666AbhEFUP4 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 6 May 2021 16:15:56 -0400
Received: from mail-bn7nam10on2083.outbound.protection.outlook.com
 ([40.107.92.83]:1825
        "EHLO NAM10-BN7-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S233572AbhEFUPz (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 6 May 2021 16:15:55 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=XcH/mAwgVUSiK3tmkFpf51O5MuWB2toFF8KzJvvdDOmhZ83oicUmldjB9BLxVns5r3ReA3ldfrha06lZ0pv5QIdoE8MwsCTa+JzsAL9bcbpK8scRBmLN149xtS2Ebh6OB2e0YdCFf/2E51AlO/kWLPXMAp77tSrqE+Jtd76K2NpNu3uctRGkO3EqJt+zuDQSuiWEQWI1m7jR9e4IApp80M0t9LD1ypi2g9XlcapzlqX9Ae3IS8Dwuxw5+hk2TOHXPjxuWpNhIozAcgW5qi5RIGa1ZsdZJEEv2ITw2yV+ayqvdZpvQ40syze4Grdu5cL7TpQLoI92Tobf7l757Yv6rw==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=z8CIZrvBAGJs/QawVq0AwmgWuOWA8aw6TENObZMBMO0=;
 b=llUvI9mpqTvpLtmfo1zhhVPCYLIxz9FcVDd1b1pP6DxP1Lr5L4sq6b/RdWnX4vBz+V+7lo2WIrQIxVMmBmPu72wd3Im4EWgKXO3dfnzZdBAVkOPrtyRHQ/HC+QIyoYtCwJsiu9xXNB1Nyfs03GXyvG04Xpx7UXhv6g7v9FJvYPKLAPGpnRG4rMu4B5DfXdlFbXfKyBNAZS+PTiqWlXvhuz0n33bv67R6BewL3bt3lL68GQe/1NYrc3tJCUCARWG8v2kJb183H0xoLEjrE1adwc3ijysXndzKzBu3tMCyLjmW1WLdkkHBxsTFefu/7EBeLNd613/p85QdYfmYJ6VCTw==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=amd.com; s=selector1;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=z8CIZrvBAGJs/QawVq0AwmgWuOWA8aw6TENObZMBMO0=;
 b=LkV2dp7GwSWc46RzDEFSmeWrnQX960ySBL00X0cPojSnaJSB5VIaVVzZjl5ToHW4lThMl2PguCrCrrEGoxGqQxC7GKE2UHt/DQF81Ii70Z/GV/Q/YFpLYEW1dqSEi3oX32y65Y08i6mQWwFWXKtwOQpo4amnh+YFgNxNyVaV0Tg=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=amd.com;
Received: from DM5PR12MB1355.namprd12.prod.outlook.com (2603:10b6:3:6e::7) by
 DM6PR12MB4958.namprd12.prod.outlook.com (2603:10b6:5:20a::8) with Microsoft
 SMTP Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.4108.26; Thu, 6 May 2021 20:14:55 +0000
Received: from DM5PR12MB1355.namprd12.prod.outlook.com
 ([fe80::b914:4704:ad6f:aba9]) by DM5PR12MB1355.namprd12.prod.outlook.com
 ([fe80::b914:4704:ad6f:aba9%12]) with mapi id 15.20.4108.026; Thu, 6 May 2021
 20:14:55 +0000
From: Tom Lendacky <thomas.lendacky@amd.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org, x86@kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        Brijesh Singh <brijesh.singh@amd.com>
Subject: [PATCH] KVM: SVM: Move GHCB unmapping to fix RCU warning
Date: Thu,  6 May 2021 15:14:41 -0500
Message-Id: 
 <b2f9b79d15166f2c3e4375c0d9bc3268b7696455.1620332081.git.thomas.lendacky@amd.com>
X-Mailer: git-send-email 2.31.0
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: SN1PR12CA0057.namprd12.prod.outlook.com
 (2603:10b6:802:20::28) To DM5PR12MB1355.namprd12.prod.outlook.com
 (2603:10b6:3:6e::7)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from tlendack-t1.amd.com (165.204.77.1) by
 SN1PR12CA0057.namprd12.prod.outlook.com (2603:10b6:802:20::28) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4108.25 via Frontend
 Transport; Thu, 6 May 2021 20:14:54 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: b4bb3163-5bd8-4ff0-c488-08d910cb9d59
X-MS-TrafficTypeDiagnostic: DM6PR12MB4958:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM6PR12MB4958C6FA8491B06A7E7C779EEC589@DM6PR12MB4958.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:6430;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 pZMatCLiMkY+i5XexglfvLanbwIjDhibxK44ktmw+OJf6zp9oyx9Dih+lu1RJtvGcG8CV0QTs/zd4ETjsSNs8lU/4+iOQ/oAMQVQ8Fmzorz+4BPP51h6YVHS5ULMjlb7vaJZXC05vMC7+S63eboe8e6gVjLYS3ZsgRWcFtTrR3p56rfjudJ/tUs+6wFvcRQ2HNv+L6y9LLSCnVT0IrzDG8x40TT2+b6ZTAupb14uIKkcIbwY4Nan2kBFDWpaLhXMGAbOvaBokTwHoaa0SkcEG0CbPbZ4TVxF9BecimEmsszplKj2h8cM/phb0jMdGd4Ukma3r5UCMiPDzE5dToG79RV6qstBrCIGR0kNXlD/QxZISEjro4Kj9Kp85bYWCas+mbQodn3kdC3MYHrdkAmEm21QxmDIn0y5IavnqIx3vt6sX/Jg9ukPR2kTYx15RAJO3qWPqidAXBNbr9eNLreMH0T9EIyOnMvsgdA8WRraV07MH4GCha+g6oqwY8jiMc7ezgnN0/lz1Wjk8Dp4oVPYdDZDh0KHtPUc7eCqWj3wSju+/gLTG1mrazG2YxR18UIdvPNUB945HzVP4cIWkSKbontTDE5jiJwWK9kNaEK2JXmj2Cqq3Ue0R5Gnh0+ropl6JnAAqp+XzEy7QW8ihd0M3w==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM5PR12MB1355.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(136003)(39860400002)(376002)(366004)(346002)(396003)(6486002)(16526019)(66556008)(5660300002)(956004)(83380400001)(38350700002)(66476007)(86362001)(8676002)(4326008)(38100700002)(66946007)(2616005)(316002)(7416002)(8936002)(52116002)(54906003)(2906002)(7696005)(26005)(6666004)(36756003)(186003)(478600001);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 MbqMK58H4s4dvNEqm4sE/yaburecBu3zwTkhzn2k5NcCQRT843IBSH9X/nDqBVQQncb5mqWHbX/FUeX4Ce8AEunmCu+NAOpP7y4YT4XjeSXbAiDwnG4Kq+uzj8jc9R+SCIpEawAinZjwcHomh0rCn3aQQ72HiNCF5RzrN0A2Wfmo2ozmYDBHBSZgmC7W8GY3MqZ7NsRbVUH29EKhrWO+qK0qCmCRAs+zOgQBUY/M32TTm18qWnjXDdGcDFPoJxFD/7g1SJIf7FTaHkLeTd581FF0kaJBTTb4FMrpJeT7455tO667RwLeDgmYZSekyQDTMnkJJQZfjasay4Sktpju3WQ53adQGXmin0n/HKDFLiIFH8rZYKhtAzYV3UTm+zDfg7TEyUVe/2nX+OPP7GVxrMPWU/euPvQwzHWb1Vgq3udTCpo6SAkWZpzYHfUU5P/Jbcif4b5TcCWAEksVjO9O3WIH+J3OOx6rFks5h7s/JsUiQ6G1sKbEzxmFL8cfgLgHHc1RYAzWf/QWIaKPYhMa0TvOzhBKPmzR/4PNFP6rQ5pnAmBDmH32hfVZIMg+utgpn0LQlvNi/Co8xRV8dNXWAYMRPGp05zNM9Ih5jHwDZNLDHffiH73AL7W7IpoNolsLudChd4fCi/6tbmMYik/vd3d2aNrRRCpQ2Yg5j2ZvR3qazAOHVKZFf0wRHOIxjtFajqlAM0QuqD8FLVq1pTeHyjrZTjKWG9Sr6pWnaa2Z9xLuFMzZH8+bcofB7/sOsYhmQq1AZnngXBWmIiv0YkzHTEersJfw6eS7U+xhB8LbcLZQ/wfDb3wWVJNtSTAMO5ZxMGvs7Kmt4+pazFzNzeNAk+FWvaBtwSHItz6HZV20okqlfRDD6fiXafqt/p4WxHP4Rq00qtkRMSPSZjsmApP+VdEdmXLt3Pe4jPIrNPwJTzchwquHgFk/8t1GB2bQe0KQk+bRwt+PzpyZvWpwlyGstnyop/Y/QvPCG+tee4GetarggLhBWsdk3RFyQFUnnxSuqGbokI9EAP98jdb25z/0rdqJOI2r2tI0s4/USnMOTQu8pQ9y7/GOKo5/7q8wagh91n63ZRXreifBBQwK2lvEkHkGupmeny/8AfDBz+XcxVoaaZ7opqg+aY4ksLL3Y/KJKMt8TvY8ancUxFNXRvqk9nUKA5rdFH5VlYoG/cb214aLOtZLXcR9y4qn9kIlqVVYP06dOoUkvduT2OQUPrlq7hrEH5Nt5ZpFSdtejCASJQJscrDOeoUOj2/s1jzomdS+MrVaGeJl1AU5nMc+WJ6zdeJ00zeQpmuQkeMnLolRSucEW9W/xNEbVspvlXudb5hx
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 b4bb3163-5bd8-4ff0-c488-08d910cb9d59
X-MS-Exchange-CrossTenant-AuthSource: DM5PR12MB1355.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 06 May 2021 20:14:55.5626
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 Z5EF1SkhDZGs7qLQeiQbOgHIakJyhVfm7vza5WG4CvoDkQj59aLWJpHbR0w2L+avfYaMruQneul79SwyWhMHow==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6PR12MB4958
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When an SEV-ES guest is running, the GHCB is unmapped as part of the
vCPU run support. However, kvm_vcpu_unmap() triggers an RCU dereference
warning with CONFIG_PROVE_LOCKING=y because the SRCU lock is released
before invoking the vCPU run support.

Move the GHCB unmapping into the prepare_guest_switch callback, which is
invoked while still holding the SRCU lock, eliminating the RCU dereference
warning.

Fixes: 291bd20d5d88 ("KVM: SVM: Add initial support for a VMGEXIT VMEXIT")
Reported-by: Borislav Petkov <bp@alien8.de>
Signed-off-by: Tom Lendacky <thomas.lendacky@amd.com>
---
 arch/x86/kvm/svm/sev.c | 5 +----
 arch/x86/kvm/svm/svm.c | 3 +++
 arch/x86/kvm/svm/svm.h | 1 +
 3 files changed, 5 insertions(+), 4 deletions(-)

```
#### [kvm-unit-tests PATCH v2] x86: Do not assign values to unaligned pointer to 128 bits
##### From: Jacob Xu <jacobhxu@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jacob Xu <jacobhxu@google.com>
X-Patchwork-Id: 12242977
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 15606C433B4
	for <kvm@archiver.kernel.org>; Thu,  6 May 2021 18:49:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DA03161164
	for <kvm@archiver.kernel.org>; Thu,  6 May 2021 18:49:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233669AbhEFSuc (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 6 May 2021 14:50:32 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:49608 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229622AbhEFSuc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 6 May 2021 14:50:32 -0400
Received: from mail-pj1-x1049.google.com (mail-pj1-x1049.google.com
 [IPv6:2607:f8b0:4864:20::1049])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 86241C061574
        for <kvm@vger.kernel.org>; Thu,  6 May 2021 11:49:33 -0700 (PDT)
Received: by mail-pj1-x1049.google.com with SMTP id
 mw15-20020a17090b4d0fb0290157199aadbaso3606263pjb.7
        for <kvm@vger.kernel.org>; Thu, 06 May 2021 11:49:33 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=JanHG7KPAUG1YRQS7P7hCl7vtCSTtYbhxlwMrWYEFEI=;
        b=n7ZK7u7ZkrlmGeKGJsfWiRxDKKowuULOq7dYJt5bgojYxbvSOH1ZjUmTUO0Dsf0VAi
         Z2UfGkCllfCFmRPXHpeapoDUT58J2dWLPg9A6VCzl10sSL56O50aJ9XRJ0572N3fHCZ6
         tQr+7sOz0yNwxaVxuOV8sp7HiQ/5TEwBPXxsYyZQd4HXaPIMPLbvTsEhi3o08t2+DPt1
         St/u3xNjZSlA500ZtetS1sTu8k2p5504I697r9cIoq09XHPlthBE4l5G4AdXpxk3Fh6H
         OBo0i54GU0YeQUXUNcvpkFVRBPk2gLhrWgM0JQ/XHgdDaAr/KysHJPKMiFdsJeC8hhTR
         ySsg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=JanHG7KPAUG1YRQS7P7hCl7vtCSTtYbhxlwMrWYEFEI=;
        b=CzAKW5GCDr5q4ynTn6GWCZNwNuzUXJQ/bDitQgD1bcNAd0CCqzqHYm598ut/bqs1sZ
         oPUHcO7RgdPRKJSZ5lz8nACZ4jBNqTT4wOulLsoPegXPTXienfgzt27qqF03zdPxP/h9
         ARejlWE4eUVxN7E2/9obYqnoophVMG+3HGV55bJ1VuXikAKzvKGwaQzgOUltBI1z4K+w
         wJgcgzxlb42H6c7LGY4bXd03VLzGMH7Z//yfnhNlWoL30mISepRQBYU2Aki2TtdHWu0k
         ba1iq84qgyLibSNLJQzerumGczLav2EXMJVjjg+pL49jwzVMxtq61kpIGCHg4CSffCUD
         fSvQ==
X-Gm-Message-State: AOAM5315D4eok5j5jFAH6mVgjCrJeCkr158+At9QSsbjCiCHTNIvEtgW
        93RouS/+3mCFW34DA/or4i7MbYuVVmHUSQ==
X-Google-Smtp-Source: 
 ABdhPJwdAm9E7lls89s9SILdpXU/0rETiH0p2FTA2p7wlhiqsiplQgzfiybmCpWPQnhVkAyddoTMnBvmovy8WQ==
X-Received: from mhmmm.sea.corp.google.com
 ([2620:15c:100:202:eeaf:2d87:56f1:7d73])
 (user=jacobhxu job=sendgmr) by 2002:a62:808b:0:b029:252:eddc:afb0 with SMTP
 id j133-20020a62808b0000b0290252eddcafb0mr6498401pfd.41.1620326973042; Thu,
 06 May 2021 11:49:33 -0700 (PDT)
Date: Thu,  6 May 2021 11:49:25 -0700
Message-Id: <20210506184925.290359-1-jacobhxu@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.1.607.g51e8a6a459-goog
Subject: [kvm-unit-tests PATCH v2] x86: Do not assign values to unaligned
 pointer to 128 bits
From: Jacob Xu <jacobhxu@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Sean Christopherson <seanjc@google.com>
Cc: kvm@vger.kernel.org, Jacob Xu <jacobhxu@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When compiled with clang, the following statement gets converted into a
movaps instructions.
mem->u[0] = 5; mem->u[1] = 6; mem->u[2] = 7; mem->u[3] = 8;

Since mem is an unaligned pointer to a union of an sse, we get a GP when
running.

All we want is to make the values between mem and v different for this
testcase, so let's just memset the pointer at mem, and convert to
uint32_t pointer. Then the compiler will not assume the pointer is
aligned to 128 bits.

Fixes: e5e76263b5 ("x86: add additional test cases for sse exceptions to
emulator.c")

Signed-off-by: Jacob Xu <jacobhxu@google.com>
---
 x86/emulator.c | 6 +++---
 1 file changed, 3 insertions(+), 3 deletions(-)

```
#### [PATCH 1/8] KVM: VMX: Add a TSC multiplier field in VMCS12
##### From: ilstam@mailbox.org

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: ilstam@mailbox.org
X-Patchwork-Id: 12241981
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 98B9EC433ED
	for <kvm@archiver.kernel.org>; Thu,  6 May 2021 10:34:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6517060249
	for <kvm@archiver.kernel.org>; Thu,  6 May 2021 10:34:27 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234540AbhEFKfY (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 6 May 2021 06:35:24 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:50808 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S234541AbhEFKfU (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 6 May 2021 06:35:20 -0400
Received: from mout-p-102.mailbox.org (mout-p-102.mailbox.org
 [IPv6:2001:67c:2050::465:102])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 8C2B4C061574
        for <kvm@vger.kernel.org>; Thu,  6 May 2021 03:34:21 -0700 (PDT)
Received: from smtp1.mailbox.org (smtp1.mailbox.org
 [IPv6:2001:67c:2050:105:465:1:1:0])
        (using TLSv1.3 with cipher TLS_AES_256_GCM_SHA384 (256/256 bits)
         key-exchange ECDHE (P-384) server-signature RSA-PSS (4096 bits)
 server-digest SHA256)
        (No client certificate requested)
        by mout-p-102.mailbox.org (Postfix) with ESMTPS id 4FbVLh02K8zQjZ5;
        Thu,  6 May 2021 12:34:20 +0200 (CEST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=mailbox.org; h=
        references:in-reply-to:message-id:date:date:subject:subject:from
        :from:received; s=mail20150812; t=1620297256; bh=O1U40Dm7VUdNCxB
        xbT9Ep1tJ7ZE9uqMfLstqOCkOmBw=; b=nnw1RoeckY1ckPDC+bqhzcjJQZUrmIL
        eFraoSGitETnCUrv/LypXHgdnIn0NDALC6KJxVtnf+mVYnOzKOKLQG8mKPGqX6KU
        QYa6oLXAe/lFzilWSgW44MQbIwKpQe8Y1iaVR0jEuTlYKK6pzp+8SdFbjrSvj5iX
        DQi+Vy1LTDzUhx1G3VVtXSPn80NtgGvXW1Wt4Nhf4uO5ZnJY0q+j/BUPi6Rbv1Z3
        sT8u+6FnMhlgE0Y3q9BaJMRtQPXrtpZ5CwIveMXhooCu9My0ulkkaCBtrENdST6E
        siSQf6PIrqarRTAfvr5p00CdThvdcicpJScWw6Pf1HXE+nQ1TE/nqPA==
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=mailbox.org;
 s=mail20150812;
        t=1620297258;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:in-reply-to:in-reply-to:references:references;
        bh=qjOhqsiDQgqlteS3wIV66YcLaaLpsfhzSy7BfJnvIUg=;
        b=X9l6wEIIAUdLG/AgVDAo62q+JMaWVbb8hfdrOsDKQBzvlkqCIY9ECzSJcomxvW+x1AxgP4
        cbbC0s67nwHfDItSzqP5lJrn0Yo+94wrq4VLUwo5Q4bR3X3QGnlOOjBffcnNUA2ssK+Mdo
        CqqpfoSAnuVPs4eXc5MMIgaVTHh6ja5O9cqqkVC0aU4GcMzu0c9xw78UPrdtwfcuT0howq
        +/IRxrV/Ywu1RW+LQnC8DRZCu9lbe224gsu22bTPIaNFMFS0Ewfjp17nLOjQnxJ2kgaxRT
        F1gq1KWR2iLaC0Zoh9R8h/B8cKp1TETjZIA+jwE3utGbxnuUzVpy1eA48b6FPg==
X-Virus-Scanned: amavisd-new at heinlein-support.de
Received: from smtp1.mailbox.org ([80.241.60.240])
        by spamfilter03.heinlein-hosting.de (spamfilter03.heinlein-hosting.de
 [80.241.56.117]) (amavisd-new, port 10030)
        with ESMTP id q8HnZlNLg9YY; Thu,  6 May 2021 12:34:16 +0200 (CEST)
From: ilstam@mailbox.org
To: kvm@vger.kernel.org, pbonzini@redhat.com
Cc: ilstam@amazon.com, seanjc@google.com, vkuznets@redhat.com,
        wanpengli@tencent.com, jmattson@google.com, joro@8bytes.org,
        haozhong.zhang@intel.com, zamsden@gmail.com, mtosatti@redhat.com,
        dplotnikov@virtuozzo.com, dwmw@amazon.co.uk
Subject: [PATCH 1/8] KVM: VMX: Add a TSC multiplier field in VMCS12
Date: Thu,  6 May 2021 10:32:21 +0000
Message-Id: <20210506103228.67864-2-ilstam@mailbox.org>
In-Reply-To: <20210506103228.67864-1-ilstam@mailbox.org>
References: <20210506103228.67864-1-ilstam@mailbox.org>
X-MBO-SPAM-Probability: 
X-Rspamd-Score: -4.11 / 15.00 / 15.00
X-Rspamd-Queue-Id: F42331891
X-Rspamd-UID: 13f4ac
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Ilias Stamatis <ilstam@amazon.com>

This is required for supporting nested TSC scaling.

Signed-off-by: Ilias Stamatis <ilstam@amazon.com>
Reported-by: kernel test robot <lkp@intel.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 arch/x86/kvm/vmx/vmcs12.c | 1 +
 arch/x86/kvm/vmx/vmcs12.h | 4 +++-
 2 files changed, 4 insertions(+), 1 deletion(-)

```
#### [PATCH] KVM: x86: move saving of arch.host_pkru to kvm_arch_vcpu_load in 5.4.y
##### From: Jon Kohler <jon@nutanix.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jon Kohler <jon@nutanix.com>
X-Patchwork-Id: 12242799
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.6 required=3.0 tests=BAYES_00,DKIM_INVALID,
	DKIM_SIGNED,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id EB1F2C43460
	for <kvm@archiver.kernel.org>; Thu,  6 May 2021 17:04:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AF99E610D2
	for <kvm@archiver.kernel.org>; Thu,  6 May 2021 17:04:15 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S236144AbhEFRFM (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 6 May 2021 13:05:12 -0400
Received: from mx0b-002c1b01.pphosted.com ([148.163.155.12]:22664 "EHLO
        mx0b-002c1b01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S236052AbhEFRFL (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 6 May 2021 13:05:11 -0400
Received: from pps.filterd (m0127841.ppops.net [127.0.0.1])
        by mx0b-002c1b01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 146GvSHv004005;
        Thu, 6 May 2021 10:03:10 -0700
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nutanix.com;
 h=from : to : cc :
 subject : date : message-id : content-transfer-encoding : content-type :
 mime-version; s=proofpoint20171006;
 bh=PI+3+N0cuqklw2gpE3JR2fvCp/DBCDavESkuZhmTGJA=;
 b=OC8RA8c4fjJ7x2QM2mBgzYmBVcDHD7yLxB7xsYDggsnRry5OOF8ORtGRBFvbg7IFaCX+
 WoxBCYkszZU3HCWHg1qkyOVUY3rxzR1L6X4gYrrryq5geHyz363MJegZV1MNdXukbPZb
 AK6JJXc6nnUgeNePKxGyobwj+bJXASojWnaO2FGuluv5n0hg5eiBkdfGeEK8d1iStSU9
 srsgBitAYlCFNfAhw5egmbG+E73RjDx1Dq/6W/Qd3Dr+guQwEWlsmg5/mcMagZ3ge29Q
 MQ17tkJP2YoUIk1mw6ZgtcipMK4ZNtr8RNzaBQPxMWu1K45cPqeSuR2jhvofqViOqqOg vA==
Received: from nam10-dm6-obe.outbound.protection.outlook.com
 (mail-dm6nam10lp2102.outbound.protection.outlook.com [104.47.58.102])
        by mx0b-002c1b01.pphosted.com with ESMTP id 38chwf8da4-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 06 May 2021 10:03:09 -0700
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=Mb1CwvcNlx3uCU2fGkcMLYAHKUCEVRTKoZAH8NzUZRE6zoi6aGx+ZKCfjKzAD8q9DeE4ozF403VkLknYOeBkgChFX5+jKlh7ChRSYvphzXjn7EXzaORr8V4l+cUw9PApGZu4bkenCZs2G6yT4qnt2Ozt4Ch5fIFd7hY2yfACg/R4yAQzbv71emPFB4ersbfMdhVPfRtAiNU+YmzoDUNAlYQOhcZmI/v3tOlCiuX52Hs93tsgiaVM9/aaRLqEIuHytR2yAg2oYFKDnHyQvJYPWxVzGq7026ptsd3wlg9EhtfmTHWO8hW/VqZfQvSvei7wqxdcTvwaocFuXcnQ19AQMQ==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=PI+3+N0cuqklw2gpE3JR2fvCp/DBCDavESkuZhmTGJA=;
 b=ZZSxe/8ZilEnbtGS+8xZ+/JLQ0Z9dXkkS1xqHVJ46iU8f4XE4MPuXXne0My7gHB4JUbXaXMmyNj0+Tl6L8ucxsuxq69gfZeZGdsyd8rpVtK5XA/lV0zdDIPtOadjbvGyXh8PZrpS1awJbxy5qktmaDe9sfFyihx8xoVNpPXDJeHMDM4ONAarHJLHqGEnzNYw9axlkSnyClexmQJUSR41HSfrx9Bzio0pvZ5GMdorbEy/5obPUP+ec6VsAeufs+bCEvu7R0c9QQejQVP5jIRGl6VLc9Z1yth/JNRLrmhzrjcufEg25G7kmijjL6xV8pLIa3L6Ut0gPPGRkGOp510nAw==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=nutanix.com; dmarc=pass action=none header.from=nutanix.com;
 dkim=pass header.d=nutanix.com; arc=none
Authentication-Results: nutanix.com; dkim=none (message not signed)
 header.d=none;nutanix.com; dmarc=none action=none header.from=nutanix.com;
Received: from BL0PR02MB4579.namprd02.prod.outlook.com (2603:10b6:208:4b::10)
 by MN2PR02MB6464.namprd02.prod.outlook.com (2603:10b6:208:184::29) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4087.25; Thu, 6 May
 2021 17:03:08 +0000
Received: from BL0PR02MB4579.namprd02.prod.outlook.com
 ([fe80::75cf:5b99:f963:cc07]) by BL0PR02MB4579.namprd02.prod.outlook.com
 ([fe80::75cf:5b99:f963:cc07%5]) with mapi id 15.20.4087.045; Thu, 6 May 2021
 17:03:07 +0000
From: Jon Kohler <jon@nutanix.com>
Cc: Jon Kohler <jon@nutanix.com>, stable@vger.kernel.org,
 Babu Moger <babu.moger@amd.com>, Paolo Bonzini <pbonzini@redhat.com>,
	=?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Sean Christopherson <sean.j.christopherson@intel.com>,
 Vitaly Kuznetsov <vkuznets@redhat.com>, Wanpeng Li <wanpengli@tencent.com>,
 Jim Mattson <jmattson@google.com>, Joerg Roedel <joro@8bytes.org>,
 Thomas Gleixner <tglx@linutronix.de>, Ingo Molnar <mingo@redhat.com>,
 Borislav Petkov <bp@alien8.de>, "H. Peter Anvin" <hpa@zytor.com>,
 x86@kernel.org, kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: x86: move saving of arch.host_pkru to kvm_arch_vcpu_load
 in 5.4.y
Date: Thu,  6 May 2021 13:02:41 -0400
Message-Id: <20210506170241.72133-1-jon@nutanix.com>
X-Mailer: git-send-email 2.30.1 (Apple Git-130)
X-Originating-IP: [2601:19b:c501:64d0:a9a2:6149:85cc:8a4]
X-ClientProxiedBy: BN9PR03CA0337.namprd03.prod.outlook.com
 (2603:10b6:408:f6::12) To BL0PR02MB4579.namprd02.prod.outlook.com
 (2603:10b6:208:4b::10)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from C02F13YVQ05N.corp.nutanix.com
 (2601:19b:c501:64d0:a9a2:6149:85cc:8a4) by
 BN9PR03CA0337.namprd03.prod.outlook.com (2603:10b6:408:f6::12) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4108.25 via Frontend
 Transport; Thu, 6 May 2021 17:03:06 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 910866a2-8cfe-4407-e8c4-08d910b0d231
X-MS-TrafficTypeDiagnostic: MN2PR02MB6464:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <MN2PR02MB6464A2C3D069594638756385AF589@MN2PR02MB6464.namprd02.prod.outlook.com>
x-proofpoint-crosstenant: true
X-MS-Oob-TLC-OOBClassifiers: OLM:612;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 o4UVTiCD4fEH3zDNwCD4XEMMjxXX4hIIDnjIO5hXX9Z1GTjdNAe/kpAch9UCAsSsUMYEjEUT8CUqqfXrjDCFj0eb9zkAy6p19X1VXGgk56UHzCcBfSusabZsexgfwUPxgnJJDFxl/GJL8uZWnYZhK2HJ3C9NrqcrRg7SnSaeP7LV3xJdiqi1YfXMgRLBm97sgNCqx/zWH7cv/Kx9wre5gyR7gjabEpwFgZK8oRVorSCRP1/c/55QFARlQe/PnW1R/8CiMoml7L2vk2kPV1p3W6JKOx9VfVoBohD3FcJ5u8QYhi99Qr74Wsj+lw4M035vEJi0Jsh9iApRx9D3HMfQpr8pOxufSJr/ngZkJEsjTYF5STm2c4vh9tZPwu4DU0YPgNNoAW4VVNRUYdJnFnrtDjdaUjCM1ZpYgcBrm/gwdJIlUsCyyRTisR0gV/iOtqCkalPpryNDZ5QvNBE0SX/VxqjrlawZwl0vfQydimn1XZfGP65zdPru7CPPmqx3OnOaioPlZ9URMyCegfSSQdDhBt9qbvB4jY/17iSx7nuVdUlbUl1xJUVUnxN/31LcAjUv4o2mTKWQIZbI+89CDuKFBoOW0FnxlSeob31VvjZiutSisMzYn66cSuqc+eToBkAaMnlGzyv0C5OtCxoJiX61cg==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:BL0PR02MB4579.namprd02.prod.outlook.com;PTR:;CAT:NONE;SFS:(346002)(376002)(39850400004)(396003)(136003)(366004)(83380400001)(66476007)(16526019)(186003)(66556008)(38100700002)(6666004)(1076003)(2616005)(66946007)(86362001)(54906003)(2906002)(7696005)(478600001)(6486002)(109986005)(316002)(7416002)(52116002)(8676002)(8936002)(36756003)(5660300002)(4326008)(266003);DIR:OUT;SFP:1102;
X-MS-Exchange-AntiSpam-MessageData-ChunkCount: 1
X-MS-Exchange-AntiSpam-MessageData-0: 
 ExFbT6AF0k8cJ4JwjCQWkqlV9C+gtHfrTR4b2VgmbYutbXqAbDbGoJihlJZLy4fs0bxIXn4U0YnSJUFSXepI4H4ovfT4Jz9Jlc+wDusQLu9MiePxNuALmY1yK4aac3mPNwMOZnZjmbmV9qFct8rrkvcefvJ9L638z4YshG/6YpDULQPISlhaa4MXJ6qJ6woMSeZ3mZXiWKR8WKsiy14AVfdKVzQKd/IT3FdCda2OiPws7W5zc7k2gfpHKJ/1eUDLO84l0IorsJPvJxBiB+Ur3bpoGjD6Hk79KH2wvHO7Rv84yL5ISmeu1ujZYdUfkiyr81p2fK6vUC78H3aYDxxSx0oWHHtRe27JNIADVgGMxNGQLTQix0rA0PfQ87LV5GZoqNMHvzSChqh0UCHV1yVNuynUdZ2BbzGmgZIMJs39eb0wuUqALK3xR4a30hl2joxt5Bg5P/MRLs4iIsM6wUD9S4EIom89+JLDm3cFtzRhtX0um4Qk+8MQ526puNADi2TUHy/YJ0tpcrSJVaf5BUFujGXXCsfZ904WtJyTpottpbKXK4iZ1z5OHEFSciHa52FuUhXT5RhAJzeFJfoRLstwRkXDdpCgxZE1RmAQZwye7uLvbzKNd+KcADt5fZp66rNBSre8uAkzbnrnbUvVvjHfAxenMPEA1QCaNXLcJCEOSUE+lA+G8xg5hQ57iDhvJrmjHhqnh28M3IR6bTXMF7pPxyPSp/Du+PuCQHOlxSd4D2VKQ4au4G4MIeQPqZZcEsHiPpeawfnh6m+Bcw90n4LIFuCMvHDku7s4uYboNqN9wWyvEMaO78Vr38cbmV6tpDZiDWlcjgeG1jYEDzsN2TZtmSUQONIxhL14SQRP1jnXKgSasYgoYpbDQgSBI+5FoKoUkriKYSLIn395BseYsLO7eYvbeuaPv75aUeFvBwrRxhTd4Psp2Gwfymx54I/cWE7EmpvIyxFk+ilB+bb8Hm5GqVzXmeiycAblY+CIBmJl9+INSw97OQk+Au5MygJb90cTH5u+Fm1pSFR+CPqErET8v7Goztb0WVJSP/gG08Tggr17+W8B3U4E6O8UgEEs4WwNcxSW3q8XY9tHPySJDV9QnOqbYwxsAn7dURomx53LZgHi7AjY8viYBrPZkhL5og8pclCSWvAtOWUD/TKHeFhY/wdGqCRp+o1R1TZCvpyK19L942rwd0yhV6+OxJxhX5lbhExLgvpBv0l8UQQWlbQwOXqUikaz37xAjOnaVxOyci/Zn525ZDLDy5Da8tlzVG8uL++xCas9dYuFe7De8c1+aNnIeYkksQKBf1+nzXux+7ert9AS4zRAwoBuMJRavz2l9dYI04vA3NFMQIcv6SZJTSdDQlX4AC6vR4p/UM3LAIRKts5mXFuv9o/EygNvxZcR
X-OriginatorOrg: nutanix.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 910866a2-8cfe-4407-e8c4-08d910b0d231
X-MS-Exchange-CrossTenant-AuthSource: BL0PR02MB4579.namprd02.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 06 May 2021 17:03:07.8049
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: bb047546-786f-4de1-bd75-24e5b6f79043
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 VHG/kIMnWfSftmRmrf4SKPtMfCbbVInLv/5s99id4YwkkEuC2fCkfUfyR0y4sUoXO/K+TqYY5+sDPR2pO+aD9MX/lk0QIzfrv6tOnK0pFBs=
X-MS-Exchange-Transport-CrossTenantHeadersStamped: MN2PR02MB6464
X-Proofpoint-ORIG-GUID: IjWa_SNOYMXzEnyYEdQFXr5blDfUhqlt
X-Proofpoint-GUID: IjWa_SNOYMXzEnyYEdQFXr5blDfUhqlt
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.391,18.0.761
 definitions=2021-05-06_10:2021-05-06,2021-05-06 signatures=0
X-Proofpoint-Spam-Reason: safe
To: unlisted-recipients:; (no To-header on input)
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

commit 37486135d3a7b03acc7755b63627a130437f066a upstream.

In 5.4.y only, vcpu->arch.host_pkru is being set on every run thru
of vcpu_enter_guest, when it really only needs to be set on load. As
a result, we're doing a rdpkru on supported CPUs on every iteration
of vcpu_enter_guest even though the value never changes.

Mainline and 5.10.y already has host_pkru being initialized in
kvm_arch_vcpu_load. This change is 5.4.y specific and moves
host_pkru save to kvm_arch_vcpu_load.

Fixes: 99e392a4979b ("KVM: x86: Fix pkru save/restore when guest CR4.PKE=0, move it to x86.c")
Cc: stable@vger.kernel.org # 5.4.y
Cc: Babu Moger <babu.moger@amd.com>
Signed-off-by: Jon Kohler <jon@nutanix.com>
---
 arch/x86/kvm/x86.c | 6 +++---
 1 file changed, 3 insertions(+), 3 deletions(-)

```
#### KVM: x86: Prevent deadlock against tk_core.seq
##### From: Thomas Gleixner <tglx@linutronix.de>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Gleixner <tglx@linutronix.de>
X-Patchwork-Id: 12242113
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id EBD57C433ED
	for <kvm@archiver.kernel.org>; Thu,  6 May 2021 13:21:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BBF83610FA
	for <kvm@archiver.kernel.org>; Thu,  6 May 2021 13:21:48 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234048AbhEFNWp (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 6 May 2021 09:22:45 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:60142 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S233973AbhEFNWi (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 6 May 2021 09:22:38 -0400
Received: from galois.linutronix.de (Galois.linutronix.de
 [IPv6:2a0a:51c0:0:12e:550::1])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 849CCC061574;
        Thu,  6 May 2021 06:21:40 -0700 (PDT)
From: Thomas Gleixner <tglx@linutronix.de>
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=linutronix.de;
        s=2020; t=1620307297;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type;
        bh=k3SAmK6PNHm2b2zFkrHARkJbvGAqBIerSBhAmmsNkFM=;
        b=OApNYyCD6aEdUkgUnti0+ogPOHAugcEFF8S9McbFYvTz4yS+6tx6RGxzKkSChnkU0qfOUj
        sYjDxz0ejpaXyQDVlinDUEExWHfkLn+3DIobnheS+9ylYYmGpsgeTrsBVjduAG90bHO3P8
        0tvijCl7Z+TNU1atlcnPQrPwB1frehR93OI8IveIMaqQaJeXdiJa9QTF5UE742LLgIUsQT
        /9mND3Jv2DbE4MaOWSObmNff1Bh1B84a2t/VPgyp56VCkg6q5sICWO1UcradqkJE3Ox6tE
        32XDhqKt+f7XIdFWoHgw/YQJWKBrbD2v8nUv81k5rtDBJQTdk4xbGGcy8pt3cQ==
DKIM-Signature: v=1; a=ed25519-sha256; c=relaxed/relaxed; d=linutronix.de;
        s=2020e; t=1620307297;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type;
        bh=k3SAmK6PNHm2b2zFkrHARkJbvGAqBIerSBhAmmsNkFM=;
        b=5HVx8sqEMjvqJ0Z615RK83KbwMf3vhMjvfhE20dwTHjYH2pvEai0C12uGtEFElVI3MYoxT
        XdZbaO3+A7uweiBQ==
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>, x86@kernel.org,
        LKML <linux-kernel@vger.kernel.org>
Subject: KVM: x86: Prevent deadlock against tk_core.seq
Date: Thu, 06 May 2021 15:21:37 +0200
Message-ID: <87h7jgm1zy.ffs@nanos.tec.linutronix.de>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

syzbot reported a possible deadlock in pvclock_gtod_notify():

CPU 0  		  	   	    	    CPU 1
write_seqcount_begin(&tk_core.seq);
  pvclock_gtod_notify()			    spin_lock(&pool->lock);
    queue_work(..., &pvclock_gtod_work)	    ktime_get()
     spin_lock(&pool->lock);		      do {
     						seq = read_seqcount_begin(tk_core.seq)
						...
				              } while (read_seqcount_retry(&tk_core.seq, seq);

While this is unlikely to happen, it's possible.

Delegate queue_work() to irq_work() which postpones it until the
tk_core.seq write held region is left and interrupts are reenabled.

Fixes: 16e8d74d2da9 ("KVM: x86: notifier for clocksource changes")
Reported-by: syzbot+6beae4000559d41d80f8@syzkaller.appspotmail.com
Signed-off-by: Thomas Gleixner <tglx@linutronix.de>
Acked-by: Peter Zijlstra (Intel) <peterz@infradead.org>
---
Link: https://lore.kernel.org/r/0000000000001d43ac05c0f5c6a0@google.com
---
 arch/x86/kvm/x86.c |   22 ++++++++++++++++++----
```
#### [PATCH v3 1/8] KVM: x86/mmu: Deduplicate rmap freeingFrom: Ben Gardon <bgardon@google.com>
##### From: Ben Gardon <bgardon@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ben Gardon <bgardon@google.com>
X-Patchwork-Id: 12242959
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B08D7C433B4
	for <kvm@archiver.kernel.org>; Thu,  6 May 2021 18:42:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 84AFC61003
	for <kvm@archiver.kernel.org>; Thu,  6 May 2021 18:42:54 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234757AbhEFSnv (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 6 May 2021 14:43:51 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:48000 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S234470AbhEFSnu (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 6 May 2021 14:43:50 -0400
Received: from mail-qk1-x749.google.com (mail-qk1-x749.google.com
 [IPv6:2607:f8b0:4864:20::749])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 1D496C061574
        for <kvm@vger.kernel.org>; Thu,  6 May 2021 11:42:51 -0700 (PDT)
Received: by mail-qk1-x749.google.com with SMTP id
 s10-20020a05620a030ab02902e061a1661fso4143496qkm.12
        for <kvm@vger.kernel.org>; Thu, 06 May 2021 11:42:51 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=Ma9cEaNYQpiK24KAk14C2pwYKbfgwwx99tQd6V1vKOE=;
        b=LYvO9qL1KxuwwY8zXKo8FEJSIkPJvM+7iXkMC0Ql2RmJ+Aw8djkGrqQ0nooXX6LCqN
         vMoOU9dJbIHD2f/Nulg/MfRdxBbl17p77oGdeUwkND0cORvXlBjaOFjLgCQRhzCDu+SZ
         57ndJ1qJcK22He2ba7+ttqL5NibboxrFqI1uEZBymduSL0WTc06py/ny14uFb6D2DIoX
         79gV/oWqiT52iuQhyOCI+RgJa8arP8yybkAdYC8woKQd5WlhpTuqrgCzZOKXa5248qY/
         22QKi4SBvhMs156Q7+cOLCExdqJMbUFMRqU1ahGdAAm5R95VxNuYQ69xcgFea9U+L6CW
         uJHg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=Ma9cEaNYQpiK24KAk14C2pwYKbfgwwx99tQd6V1vKOE=;
        b=gX9MwzjbUgVe8o22KSJm5KbA3RV35lE2Kk4oIylsO8ZY84M2paMJ8udpdTaaXAfVeU
         frdoRC5sf6qUhtWFi79LXYLVWJQQWl4Z4WwHG1DMzJwVfOhj7EtG/cDzvXZUQMS+XCld
         aRRjQ7sU0+W0nVV9IgNmglp1z8hUB5v/1Sttvel/Y42d6Oqqy0PtTIPjUdVQf8athag/
         QnE0TSrr2Vp/prDM3GkX+qYR+aJW064mo+8bYV5tLM8JAxZ6pNsUWI66EYOnAUBAI31L
         MboTikuvylWWFFvpSd9wY5AmDsR+SEBefDtxeGHbq/yq2MXMo5ztvbc+7lVzuVzwAkVq
         CAMQ==
X-Gm-Message-State: AOAM533xA8OUv0cNqHbYeEcVQYG1RYihlYmXBUtE9rc1AIUeUDcx0Wze
        erOeRhWmQa3bug2QxjmNjKs/fSLrQt27
X-Google-Smtp-Source: 
 ABdhPJyNENTXrdjoSVNfItEX8J3Wb9EZHsSLEqNWcC9gEkVhLgIiJnnSfDKBbjTgQAWFiU+dEWlxTpcpyu/k
X-Received: from bgardon.sea.corp.google.com
 ([2620:15c:100:202:9258:9474:54ca:4500])
 (user=bgardon job=sendgmr) by 2002:a0c:b28c:: with SMTP id
 r12mr3231963qve.32.1620326570257; Thu, 06 May 2021 11:42:50 -0700 (PDT)
Date: Thu,  6 May 2021 11:42:34 -0700
In-Reply-To: <20210506184241.618958-1-bgardon@google.com>
Message-Id: <20210506184241.618958-2-bgardon@google.com>
Mime-Version: 1.0
References: <20210506184241.618958-1-bgardon@google.com>
X-Mailer: git-send-email 2.31.1.607.g51e8a6a459-goog
Subject: [PATCH v3 1/8] KVM: x86/mmu: Deduplicate rmap freeing
From: Ben Gardon <bgardon@google.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>, Peter Xu <peterx@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Peter Shier <pshier@google.com>,
        Yulei Zhang <yulei.kernel@gmail.com>,
        Wanpeng Li <kernellwp@gmail.com>,
        Xiao Guangrong <xiaoguangrong.eric@gmail.com>,
        Kai Huang <kai.huang@intel.com>,
        Keqian Zhu <zhukeqian1@huawei.com>,
        Ben Gardon <bgardon@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Small code deduplication. No functional change expected.

Signed-off-by: Ben Gardon <bgardon@google.com>
---
 arch/x86/kvm/x86.c | 19 +++++++++++--------
 1 file changed, 11 insertions(+), 8 deletions(-)

```
#### [patch 2/2 V2] KVM: VMX: update vcpu posted-interrupt descriptor when assigning device
##### From: Marcelo Tosatti <mtosatti@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marcelo Tosatti <mtosatti@redhat.com>
X-Patchwork-Id: 12243417
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-17.9 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_SANE_1 autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A65E5C433ED
	for <kvm@archiver.kernel.org>; Thu,  6 May 2021 19:21:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7F05B6113E
	for <kvm@archiver.kernel.org>; Thu,  6 May 2021 19:21:39 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233890AbhEFTWh (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 6 May 2021 15:22:37 -0400
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:21321 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S230375AbhEFTWg (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 6 May 2021 15:22:36 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1620328898;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         in-reply-to:in-reply-to:references:references;
        bh=+Z0QjuQrLcOOXbkjH3icVUPr3o/oGH5cz14pM4ocImo=;
        b=Q49NgLU/4kErWeCpqhA7Y1ASxpvtj//oM0U+bR66TnUL6HTedMYSQ74Uv/T0OAjOPFBQRs
        lEsY0yZ5Ouycjj3tbqKZOcI4W9poJyAvZi0RofPjBXWXyUKsZKYK1oOUm8h8FAdh5pTuTh
        jhAyUuqrYGpyzDOONX2+gSu95fp5fIw=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-362-ntFDwCM6PoyvARZlNgf34w-1; Thu, 06 May 2021 15:21:36 -0400
X-MC-Unique: ntFDwCM6PoyvARZlNgf34w-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 4C32BA40C2;
        Thu,  6 May 2021 19:21:35 +0000 (UTC)
Received: from fuller.cnet (ovpn-112-4.gru2.redhat.com [10.97.112.4])
        by smtp.corp.redhat.com (Postfix) with ESMTPS id 788915D6AC;
        Thu,  6 May 2021 19:21:30 +0000 (UTC)
Received: by fuller.cnet (Postfix, from userid 1000)
        id 8D0CB418AE0D; Thu,  6 May 2021 16:21:25 -0300 (-03)
Date: Thu, 6 May 2021 16:21:25 -0300
From: Marcelo Tosatti <mtosatti@redhat.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Alex Williamson <alex.williamson@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Pei Zhang <pezhang@redhat.com>
Subject: [patch 2/2 V2] KVM: VMX: update vcpu posted-interrupt descriptor
 when assigning device
Message-ID: <20210506192125.GA350334@fuller.cnet>
References: <20210506185732.609010123@redhat.com>
 <20210506190419.481236922@redhat.com>
MIME-Version: 1.0
Content-Disposition: inline
In-Reply-To: <20210506190419.481236922@redhat.com>
User-Agent: Mutt/1.10.1 (2018-07-13)
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

For VMX, when a vcpu enters HLT emulation, pi_post_block will:

1) Add vcpu to per-cpu list of blocked vcpus.

2) Program the posted-interrupt descriptor "notification vector" 
to POSTED_INTR_WAKEUP_VECTOR

With interrupt remapping, an interrupt will set the PIR bit for the 
vector programmed for the device on the CPU, test-and-set the 
ON bit on the posted interrupt descriptor, and if the ON bit is clear
generate an interrupt for the notification vector.

This way, the target CPU wakes upon a device interrupt and wakes up
the target vcpu.

Problem is that pi_post_block only programs the notification vector
if kvm_arch_has_assigned_device() is true. Its possible for the
following to happen:

1) vcpu V HLTs on pcpu P, kvm_arch_has_assigned_device is false,
notification vector is not programmed
2) device is assigned to VM
3) device interrupts vcpu V, sets ON bit (notification vector not programmed,
so pcpu P remains in idle)
4) vcpu 0 IPIs vcpu V (in guest), but since pi descriptor ON bit is set,
kvm_vcpu_kick is skipped
5) vcpu 0 busy spins on vcpu V's response for several seconds, until
RCU watchdog NMIs all vCPUs.

To fix this, use the start_assignment kvm_x86_ops callback to program the
notification vector when assigned device count changes from 0 to 1.

Reported-by: Pei Zhang <pezhang@redhat.com>
Signed-off-by: Marcelo Tosatti <mtosatti@redhat.com>
---

v2: add vmx_pi_start_assignment to vmx's kvm_x86_ops

Index: kvm/arch/x86/kvm/vmx/posted_intr.c
===================================================================
--- kvm.orig/arch/x86/kvm/vmx/posted_intr.c
+++ kvm/arch/x86/kvm/vmx/posted_intr.c
@@ -114,7 +114,7 @@ static void __pi_post_block(struct kvm_v
 	} while (cmpxchg64(&pi_desc->control, old.control,
 			   new.control) != old.control);
 
-	if (!WARN_ON_ONCE(vcpu->pre_pcpu == -1)) {
+	if (vcpu->pre_pcpu != -1) {
 		spin_lock(&per_cpu(blocked_vcpu_on_cpu_lock, vcpu->pre_pcpu));
 		list_del(&vcpu->blocked_vcpu_list);
 		spin_unlock(&per_cpu(blocked_vcpu_on_cpu_lock, vcpu->pre_pcpu));
@@ -135,20 +135,13 @@ static void __pi_post_block(struct kvm_v
  *   this case, return 1, otherwise, return 0.
  *
  */
-int pi_pre_block(struct kvm_vcpu *vcpu)
+static int __pi_pre_block(struct kvm_vcpu *vcpu)
 {
 	unsigned int dest;
 	struct pi_desc old, new;
 	struct pi_desc *pi_desc = vcpu_to_pi_desc(vcpu);
 
-	if (!kvm_arch_has_assigned_device(vcpu->kvm) ||
-		!irq_remapping_cap(IRQ_POSTING_CAP)  ||
-		!kvm_vcpu_apicv_active(vcpu))
-		return 0;
-
-	WARN_ON(irqs_disabled());
-	local_irq_disable();
-	if (!WARN_ON_ONCE(vcpu->pre_pcpu != -1)) {
+	if (vcpu->pre_pcpu == -1) {
 		vcpu->pre_pcpu = vcpu->cpu;
 		spin_lock(&per_cpu(blocked_vcpu_on_cpu_lock, vcpu->pre_pcpu));
 		list_add_tail(&vcpu->blocked_vcpu_list,
@@ -188,12 +181,33 @@ int pi_pre_block(struct kvm_vcpu *vcpu)
 	if (pi_test_on(pi_desc) == 1)
 		__pi_post_block(vcpu);
 
+	return (vcpu->pre_pcpu == -1);
+}
+
+int pi_pre_block(struct kvm_vcpu *vcpu)
+{
+	struct vcpu_vmx *vmx = to_vmx(vcpu);
+
+	vmx->in_blocked_section = true;
+
+	if (!kvm_arch_has_assigned_device(vcpu->kvm) ||
+		!irq_remapping_cap(IRQ_POSTING_CAP)  ||
+		!kvm_vcpu_apicv_active(vcpu))
+		return 0;
+
+	WARN_ON(irqs_disabled());
+	local_irq_disable();
+	__pi_pre_block(vcpu);
 	local_irq_enable();
+
 	return (vcpu->pre_pcpu == -1);
 }
 
 void pi_post_block(struct kvm_vcpu *vcpu)
 {
+	struct vcpu_vmx *vmx = to_vmx(vcpu);
+
+	vmx->in_blocked_section = false;
 	if (vcpu->pre_pcpu == -1)
 		return;
 
@@ -236,6 +250,52 @@ bool pi_has_pending_interrupt(struct kvm
 		(pi_test_sn(pi_desc) && !pi_is_pir_empty(pi_desc));
 }
 
+static void pi_update_wakeup_vector(void *data)
+{
+	struct vcpu_vmx *vmx;
+	struct kvm_vcpu *vcpu = data;
+
+	vmx = to_vmx(vcpu);
+
+	/* race with pi_post_block ? */
+	if (vcpu->pre_pcpu != -1)
+		return;
+
+	if (!vmx->in_blocked_section)
+		return;
+
+	__pi_pre_block(vcpu);
+}
+
+void vmx_pi_start_assignment(struct kvm *kvm, int device_count)
+{
+	struct kvm_vcpu *vcpu;
+	int i;
+
+	if (!irq_remapping_cap(IRQ_POSTING_CAP))
+		return;
+
+	/* only care about first device assignment */
+	if (device_count != 1)
+		return;
+
+	/* Update wakeup vector and add vcpu to blocked_vcpu_list */
+	kvm_for_each_vcpu(i, vcpu, kvm) {
+		struct vcpu_vmx *vmx = to_vmx(vcpu);
+		int pcpu;
+
+		if (!kvm_vcpu_apicv_active(vcpu))
+			continue;
+
+		preempt_disable();
+		pcpu = vcpu->cpu;
+		if (vmx->in_blocked_section && vcpu->pre_pcpu == -1 &&
+		    pcpu != -1 && pcpu != smp_processor_id())
+			smp_call_function_single(pcpu, pi_update_wakeup_vector,
+						 vcpu, 1);
+		preempt_enable();
+	}
+}
 
 /*
  * pi_update_irte - set IRTE for Posted-Interrupts
Index: kvm/arch/x86/kvm/vmx/posted_intr.h
===================================================================
--- kvm.orig/arch/x86/kvm/vmx/posted_intr.h
+++ kvm/arch/x86/kvm/vmx/posted_intr.h
@@ -95,5 +95,6 @@ void __init pi_init_cpu(int cpu);
 bool pi_has_pending_interrupt(struct kvm_vcpu *vcpu);
 int pi_update_irte(struct kvm *kvm, unsigned int host_irq, uint32_t guest_irq,
 		   bool set);
+void vmx_pi_start_assignment(struct kvm *kvm, int device_count);
 
 #endif /* __KVM_X86_VMX_POSTED_INTR_H */
Index: kvm/arch/x86/kvm/vmx/vmx.h
===================================================================
--- kvm.orig/arch/x86/kvm/vmx/vmx.h
+++ kvm/arch/x86/kvm/vmx/vmx.h
@@ -336,6 +336,9 @@ struct vcpu_vmx {
 		DECLARE_BITMAP(read, MAX_POSSIBLE_PASSTHROUGH_MSRS);
 		DECLARE_BITMAP(write, MAX_POSSIBLE_PASSTHROUGH_MSRS);
 	} shadow_msr_intercept;
+
+	/* true if vcpu is between pre_block and post_block */
+	bool in_blocked_section;
 };
 
 enum ept_pointers_status {
Index: kvm/arch/x86/kvm/vmx/vmx.c
===================================================================
--- kvm.orig/arch/x86/kvm/vmx/vmx.c
+++ kvm/arch/x86/kvm/vmx/vmx.c
@@ -7732,7 +7732,7 @@ static struct kvm_x86_ops vmx_x86_ops __
 	.nested_ops = &vmx_nested_ops,
 
 	.update_pi_irte = pi_update_irte,
-	.start_assignment = NULL,
+	.start_assignment = vmx_pi_start_assignment,
 
 #ifdef CONFIG_X86_64
 	.set_hv_timer = vmx_set_hv_timer,
```
#### [PATCH v2 1/9] audio/alsaaudio: Replace ALSA alloca() by malloc() equivalent
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
 <philmd@redhat.com>
X-Patchwork-Id: 12242145
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-19.4 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 96BF3C433B4
	for <kvm@archiver.kernel.org>; Thu,  6 May 2021 13:38:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5EB0D613F9
	for <kvm@archiver.kernel.org>; Thu,  6 May 2021 13:38:09 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234310AbhEFNjG (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 6 May 2021 09:39:06 -0400
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:30329 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S234072AbhEFNjG (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 6 May 2021 09:39:06 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1620308288;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=/bdOhY3sBOcIHJeoCe6CkJ1QfZvAaT12hvfPxmFulM0=;
        b=diAk3LMOlfbES4tV7FjKNoalRYDIzxql+fuvw50YYXcjrxxjmW98+zMC6uRAF5HQrsAU7U
        X1MzwlvgmJLId0zYbCZutsDUbsq7JH3SjRoBb3iSDlRZljwSgcpEUpuuV/CUbXl3uJW9Ms
        gyNv0PZMEjVVs+XkW90LB4grNr5xT/4=
Received: from mail-wr1-f72.google.com (mail-wr1-f72.google.com
 [209.85.221.72]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-190-IUzylFh0Nz-lohi4v2qUBQ-1; Thu, 06 May 2021 09:38:06 -0400
X-MC-Unique: IUzylFh0Nz-lohi4v2qUBQ-1
Received: by mail-wr1-f72.google.com with SMTP id
 93-20020adf80e60000b0290106fab45006so2205420wrl.20
        for <kvm@vger.kernel.org>; Thu, 06 May 2021 06:38:06 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=/bdOhY3sBOcIHJeoCe6CkJ1QfZvAaT12hvfPxmFulM0=;
        b=RZS87O7GzTn8lL39Rexk2UXU9L3yM0JrQox4X/F47tqa9mGpWAKajgqzoMX/sz75lj
         JjtO1cWZMAcm4BwxIKoiMjFKinDltJv+1I1tDjwhtGWNT7qBgmmGKMUwp0yYAMSqWALy
         6q6KCZcxzFuf9mQIWg0hLfm4azm2a5aJ1yJNWQqpRKahDywXBSfsksD8aqfubr0ZveQw
         j8LgpKNx3pkAfs4NSw9xJE/1e1rCV26B2XumD0+1SJerX/I/FmGy5r8LWtGrkFYrRyr3
         rGIQIxtW21eql/9Pr6AfJirmj+pTiGsRbVdtiQcLghZkhxrjeGCSZemTM27P7yMUw7gg
         OHvA==
X-Gm-Message-State: AOAM531h/HROpZ2bMr1Ci2LfzehQKstnBlsDpJd1wDIE3WU0WqqBSh+e
        j5rywdckh9o3TX6kV7V/3D4/eECEDprhUTILhEd8BGqx3NId+2iYe14Spq8ZGJZtb7QGuTa7x73
        FDyFM5Es+3hcV
X-Received: by 2002:a1c:1bc9:: with SMTP id b192mr15231214wmb.3.1620308285136;
        Thu, 06 May 2021 06:38:05 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJwaU39xWPKmAxzTDnRmk4BpB3yHtP51ZUdmNXUtU3rYDqeE9UGHa8wm/T1yoDDa+r7xsmcCLw==
X-Received: by 2002:a1c:1bc9:: with SMTP id b192mr15231189wmb.3.1620308284991;
        Thu, 06 May 2021 06:38:04 -0700 (PDT)
Received: from localhost.localdomain
 (astrasbourg-652-1-219-60.w90-40.abo.wanadoo.fr. [90.40.114.60])
        by smtp.gmail.com with ESMTPSA id
 o17sm4231200wrs.48.2021.05.06.06.38.04
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 06 May 2021 06:38:04 -0700 (PDT)
From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>
To: qemu-devel@nongnu.org
Cc: kvm@vger.kernel.org, qemu-ppc@nongnu.org, qemu-arm@nongnu.org,
 Gerd Hoffmann <kraxel@redhat.com>, Paolo Bonzini <pbonzini@redhat.com>,
	=?utf-8?q?Alex_Benn=C3=A9e?= <alex.bennee@linaro.org>, =?utf-8?q?Philippe_M?=
	=?utf-8?q?athieu-Daud=C3=A9?= <philmd@redhat.com>
Subject: [PATCH v2 1/9] audio/alsaaudio: Replace ALSA alloca() by malloc()
 equivalent
Date: Thu,  6 May 2021 15:37:50 +0200
Message-Id: <20210506133758.1749233-2-philmd@redhat.com>
X-Mailer: git-send-email 2.26.3
In-Reply-To: <20210506133758.1749233-1-philmd@redhat.com>
References: <20210506133758.1749233-1-philmd@redhat.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The ALLOCA(3) man-page mentions its "use is discouraged".

Define the cleanup functions for the snd_pcm_[hw/sw]_params_t types,
and replace the ALSA alloca() calls by equivalent ALSA malloc().

Signed-off-by: Philippe Mathieu-Daudé <philmd@redhat.com>
---
 audio/alsaaudio.c | 11 +++++++----
 1 file changed, 7 insertions(+), 4 deletions(-)

```
#### [PATCH] tools/kvm_stat: Fix documentation typo
##### From: Stefan Raspl <raspl@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stefan Raspl <raspl@linux.ibm.com>
X-Patchwork-Id: 12242201
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id F1861C433B4
	for <kvm@archiver.kernel.org>; Thu,  6 May 2021 14:04:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BC3BB610E6
	for <kvm@archiver.kernel.org>; Thu,  6 May 2021 14:04:03 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234638AbhEFOFA (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 6 May 2021 10:05:00 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:26438 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S234489AbhEFOFA (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 6 May 2021 10:05:00 -0400
Received: from pps.filterd (m0187473.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 146E3nGS046689
        for <kvm@vger.kernel.org>; Thu, 6 May 2021 10:04:01 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=iFQCnsQsFzVQxEI2giGcwds7XDiCZ61hdo8CyZAPTM8=;
 b=j5CSYeIOyp1GNAQc/DFDNy8yF+ffG+SGYax1yEw4+9abxg2FsWCxnENpJpmOGyCeDo8E
 DA2U7oGILxqnIgs5lYbFYWZv3qYhcuzAkoRX/dLXvr+SfmA9M2wGmBFv1DCiJH0v8Wjq
 6w9Je38dyDUEJWhAsGxjv83tJ0woi69j4s5IIf/BLKkaEuzx34zqJRbEOhvB2vhnWdB7
 HNEeKnzWvw2BzbC+/+YbTQAUyn4SNMNxSx/ploHxv9K6nsnnkR7wknPEIdKbLzVem8aP
 QSL95lK5K8xRnDaNMswQRdn5OCDLywnV1gDreN+asPHYHP48rdYGXuO4m1ypMhsyFhC6 FQ==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 38ch7k9jtv-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT)
        for <kvm@vger.kernel.org>; Thu, 06 May 2021 10:04:01 -0400
Received: from m0187473.ppops.net (m0187473.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 146E41fG051382
        for <kvm@vger.kernel.org>; Thu, 6 May 2021 10:04:01 -0400
Received: from ppma06ams.nl.ibm.com (66.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.102])
        by mx0a-001b2d01.pphosted.com with ESMTP id 38ch7k9js5-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 06 May 2021 10:04:01 -0400
Received: from pps.filterd (ppma06ams.nl.ibm.com [127.0.0.1])
        by ppma06ams.nl.ibm.com (8.16.0.43/8.16.0.43) with SMTP id
 146E2cke002345;
        Thu, 6 May 2021 14:03:57 GMT
Received: from b06avi18878370.portsmouth.uk.ibm.com
 (b06avi18878370.portsmouth.uk.ibm.com [9.149.26.194])
        by ppma06ams.nl.ibm.com with ESMTP id 38bee590bm-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 06 May 2021 14:03:57 +0000
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06avi18878370.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 146E3TMg17236332
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 6 May 2021 14:03:29 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id E89BFA4068;
        Thu,  6 May 2021 14:03:54 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id B664AA4060;
        Thu,  6 May 2021 14:03:54 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Thu,  6 May 2021 14:03:54 +0000 (GMT)
From: Stefan Raspl <raspl@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: borntraeger@de.ibm.com, pbonzini@redhat.com
Subject: [PATCH] tools/kvm_stat: Fix documentation typo
Date: Thu,  6 May 2021 16:03:52 +0200
Message-Id: <20210506140352.4178789-1-raspl@linux.ibm.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-GUID: OTbtJEauIgG96cxNZZSZTUcB7kCY1iFr
X-Proofpoint-ORIG-GUID: yjYdPedxrzmiJP4xR2x-AfwIGYJXmq87
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.391,18.0.761
 definitions=2021-05-06_10:2021-05-06,2021-05-06 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 malwarescore=0 phishscore=0
 clxscore=1011 mlxlogscore=932 priorityscore=1501 spamscore=0 bulkscore=0
 mlxscore=0 adultscore=0 lowpriorityscore=0 suspectscore=0 impostorscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2104060000
 definitions=main-2105060103
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Makes the dash in front of option '-z' disappear in the generated
man-page.

Signed-off-by: Stefan Raspl <raspl@linux.ibm.com>
---
 tools/kvm/kvm_stat/kvm_stat.txt | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] vfio: Lock down no-IOMMU mode when kernel is locked down
##### From: Maxime Coquelin <maxime.coquelin@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxime Coquelin <maxime.coquelin@redhat.com>
X-Patchwork-Id: 12241905
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.4 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 82C46C433ED
	for <kvm@archiver.kernel.org>; Thu,  6 May 2021 09:19:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5B2B0610A2
	for <kvm@archiver.kernel.org>; Thu,  6 May 2021 09:19:26 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231864AbhEFJUW (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 6 May 2021 05:20:22 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:38181 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S230113AbhEFJUT (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 6 May 2021 05:20:19 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1620292760;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=9T3+gtqvRPWaN1kbhzEfYcsn4RQucKuVfAaPYhpIxaE=;
        b=fP+O2RVolWbMIF0CfCgVZxUqmmBd6cSLifyA0qSA5YOHi1c1jLGNryhRKuhH7hYJbS3ZRM
        sR1wTflR8OlchuWiF8ilvMEIl31PpwM2LqNSp4LkTO4VzDF+/6VIYAabLnNnyVX34w4LIw
        iNCEMd6ub0BbX8VGBUn6l1arIbTYyuI=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-225-YvqA8d_6MjelWBozQMda6Q-1; Thu, 06 May 2021 05:19:17 -0400
X-MC-Unique: YvqA8d_6MjelWBozQMda6Q-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 69970802B78;
        Thu,  6 May 2021 09:19:16 +0000 (UTC)
Received: from max-t490s.redhat.com (unknown [10.36.110.22])
        by smtp.corp.redhat.com (Postfix) with ESMTP id ABA2419D7C;
        Thu,  6 May 2021 09:19:07 +0000 (UTC)
From: Maxime Coquelin <maxime.coquelin@redhat.com>
To: alex.williamson@redhat.com, jmorris@namei.org, dhowells@redhat.com,
        linux-kernel@vger.kernel.org,
        linux-security-module@vger.kernel.org, kvm@vger.kernel.org
Cc: mjg59@srcf.ucam.org, keescook@chromium.org, cohuck@redhat.com,
        Maxime Coquelin <maxime.coquelin@redhat.com>
Subject: [PATCH] vfio: Lock down no-IOMMU mode when kernel is locked down
Date: Thu,  6 May 2021 11:18:59 +0200
Message-Id: <20210506091859.6961-1-maxime.coquelin@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When no-IOMMU mode is enabled, VFIO is as unsafe as accessing
the PCI BARs via the device's sysfs, which is locked down when
the kernel is locked down.

Indeed, it is possible for an attacker to craft DMA requests
to modify kernel's code or leak secrets stored in the kernel,
since the device is not isolated by an IOMMU.

This patch introduces a new integrity lockdown reason for the
unsafe VFIO no-iommu mode.

Signed-off-by: Maxime Coquelin <maxime.coquelin@redhat.com>
---
 drivers/vfio/vfio.c      | 13 +++++++++----
 include/linux/security.h |  1 +
 security/security.c      |  1 +
 3 files changed, 11 insertions(+), 4 deletions(-)

```
#### [patch 1/2] KVM: x86: add start_assignment hook to kvm_x86_opsReferences: <20210506185732.609010123@redhat.com>
##### From: Marcelo Tosatti <mtosatti@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marcelo Tosatti <mtosatti@redhat.com>
X-Patchwork-Id: 12243391
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.4 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 499D6C433B4
	for <kvm@archiver.kernel.org>; Thu,  6 May 2021 19:07:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 28F42613BA
	for <kvm@archiver.kernel.org>; Thu,  6 May 2021 19:07:30 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234694AbhEFTI1 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 6 May 2021 15:08:27 -0400
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:29991 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S233217AbhEFTI1 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 6 May 2021 15:08:27 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1620328048;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         references:references;
 bh=MveHt3pNOHJ4AJPORxOX037kRSEbnzFSeZIFDxPmdN0=;
        b=DEjMZhNTgAPPpIO1Rd6C4/e3YWq8mY6DJAGVKxGKDTipo7ZqDaMIv6GLf+iMLEtWYVWUhD
        K/Cgo67bSj1I4Bq5DG7VmjRwBQhcO3DAU6mccrLnquVPEmohj4CJgDpKFr/WboqR11GvBI
        X6HgC1GkD3WHpVNZf6nK+UCvS/PzGRg=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-472-BhDYdW1sO4SPcNsY0TORnA-1; Thu, 06 May 2021 15:07:24 -0400
X-MC-Unique: BhDYdW1sO4SPcNsY0TORnA-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id D2895801106;
        Thu,  6 May 2021 19:07:23 +0000 (UTC)
Received: from fuller.cnet (ovpn-112-4.gru2.redhat.com [10.97.112.4])
        by smtp.corp.redhat.com (Postfix) with ESMTPS id 922D360D06;
        Thu,  6 May 2021 19:07:23 +0000 (UTC)
Received: by fuller.cnet (Postfix, from userid 1000)
        id E9FAA40E6DFB; Thu,  6 May 2021 16:07:03 -0300 (-03)
Message-ID: <20210506190419.451446263@redhat.com>
User-Agent: quilt/0.66
Date: Thu, 06 May 2021 15:57:33 -0300
From: Marcelo Tosatti <mtosatti@redhat.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Alex Williamson <alex.williamson@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Marcelo Tosatti <mtosatti@redhat.com>
Subject: [patch 1/2] KVM: x86: add start_assignment hook to kvm_x86_ops
References: <20210506185732.609010123@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add a start_assignment hook to kvm_x86_ops, which is called when 
kvm_arch_start_assignment is done.

The hook is required to update the wakeup vector of a sleeping vCPU
when a device is assigned to the guest.

Signed-off-by: Marcelo Tosatti <mtosatti@redhat.com>

Index: kvm/arch/x86/include/asm/kvm_host.h
===================================================================
--- kvm.orig/arch/x86/include/asm/kvm_host.h
+++ kvm/arch/x86/include/asm/kvm_host.h
@@ -1322,6 +1322,7 @@ struct kvm_x86_ops {
 
 	int (*update_pi_irte)(struct kvm *kvm, unsigned int host_irq,
 			      uint32_t guest_irq, bool set);
+	void (*start_assignment)(struct kvm *kvm, int device_count);
 	void (*apicv_post_state_restore)(struct kvm_vcpu *vcpu);
 	bool (*dy_apicv_has_pending_interrupt)(struct kvm_vcpu *vcpu);
 
Index: kvm/arch/x86/kvm/svm/svm.c
===================================================================
--- kvm.orig/arch/x86/kvm/svm/svm.c
+++ kvm/arch/x86/kvm/svm/svm.c
@@ -4601,6 +4601,7 @@ static struct kvm_x86_ops svm_x86_ops __
 	.deliver_posted_interrupt = svm_deliver_avic_intr,
 	.dy_apicv_has_pending_interrupt = svm_dy_apicv_has_pending_interrupt,
 	.update_pi_irte = svm_update_pi_irte,
+	.start_assignment = NULL,
 	.setup_mce = svm_setup_mce,
 
 	.smi_allowed = svm_smi_allowed,
Index: kvm/arch/x86/kvm/vmx/vmx.c
===================================================================
--- kvm.orig/arch/x86/kvm/vmx/vmx.c
+++ kvm/arch/x86/kvm/vmx/vmx.c
@@ -7732,6 +7732,7 @@ static struct kvm_x86_ops vmx_x86_ops __
 	.nested_ops = &vmx_nested_ops,
 
 	.update_pi_irte = pi_update_irte,
+	.start_assignment = NULL,
 
 #ifdef CONFIG_X86_64
 	.set_hv_timer = vmx_set_hv_timer,
Index: kvm/arch/x86/kvm/x86.c
===================================================================
--- kvm.orig/arch/x86/kvm/x86.c
+++ kvm/arch/x86/kvm/x86.c
@@ -11295,7 +11295,11 @@ bool kvm_arch_can_dequeue_async_page_pre
 
 void kvm_arch_start_assignment(struct kvm *kvm)
 {
-	atomic_inc(&kvm->arch.assigned_device_count);
+	int ret;
+
+	ret = atomic_inc_return(&kvm->arch.assigned_device_count);
+	if (kvm_x86_ops.start_assignment)
+		kvm_x86_ops.start_assignment(kvm, ret);
 }
 EXPORT_SYMBOL_GPL(kvm_arch_start_assignment);
 

From patchwork Thu May  6 18:57:34 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marcelo Tosatti <mtosatti@redhat.com>
X-Patchwork-Id: 12243395
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.4 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 8DA41C43460
	for <kvm@archiver.kernel.org>; Thu,  6 May 2021 19:07:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 694D6613E4
	for <kvm@archiver.kernel.org>; Thu,  6 May 2021 19:07:40 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234751AbhEFTIi (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 6 May 2021 15:08:38 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:20396 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S234740AbhEFTIh (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 6 May 2021 15:08:37 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1620328058;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         references:references;
 bh=wLvxEYJuVXW97IlxUCoSSxvp9ugeIbjO4WWeDL9ilCI=;
        b=hBlS8EC4ugynh/Vk1n9XIvcT3FvHIm5vcFZ69V4tUpdaByEVdqdBpPFZsbVQOh5sZGb3Cu
        F0joawPPJwjhAqfbrz1KmcUAKocxlqiMsXx2Go/m7TuM8MqcoveAr0/FTNQrf8aQwXKYE4
        M4zIGmFcICkzg+eN6ChChAGRRCGCr/s=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-271-caUZCGBNPCqw_v0SUe_ZAw-1; Thu, 06 May 2021 15:07:34 -0400
X-MC-Unique: caUZCGBNPCqw_v0SUe_ZAw-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 8FEAA107ACCD;
        Thu,  6 May 2021 19:07:33 +0000 (UTC)
Received: from fuller.cnet (ovpn-112-4.gru2.redhat.com [10.97.112.4])
        by smtp.corp.redhat.com (Postfix) with ESMTPS id 92C2D10027A5;
        Thu,  6 May 2021 19:07:23 +0000 (UTC)
Received: by fuller.cnet (Postfix, from userid 1000)
        id EC62240B1EB1; Thu,  6 May 2021 16:07:03 -0300 (-03)
Message-ID: <20210506190419.481236922@redhat.com>
User-Agent: quilt/0.66
Date: Thu, 06 May 2021 15:57:34 -0300
From: Marcelo Tosatti <mtosatti@redhat.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Alex Williamson <alex.williamson@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Pei Zhang <pezhang@redhat.com>,
        Marcelo Tosatti <mtosatti@redhat.com>
Subject: [patch 2/2] KVM: VMX: update vcpu posted-interrupt descriptor when
 assigning device
References: <20210506185732.609010123@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

For VMX, when a vcpu enters HLT emulation, pi_post_block will:

1) Add vcpu to per-cpu list of blocked vcpus.

2) Program the posted-interrupt descriptor "notification vector" 
to POSTED_INTR_WAKEUP_VECTOR

With interrupt remapping, an interrupt will set the PIR bit for the 
vector programmed for the device on the CPU, test-and-set the 
ON bit on the posted interrupt descriptor, and if the ON bit is clear
generate an interrupt for the notification vector.

This way, the target CPU wakes upon a device interrupt and wakes up
the target vcpu.

Problem is that pi_post_block only programs the notification vector
if kvm_arch_has_assigned_device() is true. Its possible for the
following to happen:

1) vcpu V HLTs on pcpu P, kvm_arch_has_assigned_device is false,
notification vector is not programmed
2) device is assigned to VM
3) device interrupts vcpu V, sets ON bit (notification vector not programmed,
so pcpu P remains in idle)
4) vcpu 0 IPIs vcpu V (in guest), but since pi descriptor ON bit is set,
kvm_vcpu_kick is skipped
5) vcpu 0 busy spins on vcpu V's response for several seconds, until
RCU watchdog NMIs all vCPUs.

To fix this, use the start_assignment kvm_x86_ops callback to program the
notification vector when assigned device count changes from 0 to 1.

Reported-by: Pei Zhang <pezhang@redhat.com>
Signed-off-by: Marcelo Tosatti <mtosatti@redhat.com>

Index: kvm/arch/x86/kvm/vmx/posted_intr.c
===================================================================
--- kvm.orig/arch/x86/kvm/vmx/posted_intr.c
+++ kvm/arch/x86/kvm/vmx/posted_intr.c
@@ -114,7 +114,7 @@ static void __pi_post_block(struct kvm_v
 	} while (cmpxchg64(&pi_desc->control, old.control,
 			   new.control) != old.control);
 
-	if (!WARN_ON_ONCE(vcpu->pre_pcpu == -1)) {
+	if (vcpu->pre_pcpu != -1) {
 		spin_lock(&per_cpu(blocked_vcpu_on_cpu_lock, vcpu->pre_pcpu));
 		list_del(&vcpu->blocked_vcpu_list);
 		spin_unlock(&per_cpu(blocked_vcpu_on_cpu_lock, vcpu->pre_pcpu));
@@ -135,20 +135,13 @@ static void __pi_post_block(struct kvm_v
  *   this case, return 1, otherwise, return 0.
  *
  */
-int pi_pre_block(struct kvm_vcpu *vcpu)
+static int __pi_pre_block(struct kvm_vcpu *vcpu)
 {
 	unsigned int dest;
 	struct pi_desc old, new;
 	struct pi_desc *pi_desc = vcpu_to_pi_desc(vcpu);
 
-	if (!kvm_arch_has_assigned_device(vcpu->kvm) ||
-		!irq_remapping_cap(IRQ_POSTING_CAP)  ||
-		!kvm_vcpu_apicv_active(vcpu))
-		return 0;
-
-	WARN_ON(irqs_disabled());
-	local_irq_disable();
-	if (!WARN_ON_ONCE(vcpu->pre_pcpu != -1)) {
+	if (vcpu->pre_pcpu == -1) {
 		vcpu->pre_pcpu = vcpu->cpu;
 		spin_lock(&per_cpu(blocked_vcpu_on_cpu_lock, vcpu->pre_pcpu));
 		list_add_tail(&vcpu->blocked_vcpu_list,
@@ -188,12 +181,33 @@ int pi_pre_block(struct kvm_vcpu *vcpu)
 	if (pi_test_on(pi_desc) == 1)
 		__pi_post_block(vcpu);
 
+	return (vcpu->pre_pcpu == -1);
+}
+
+int pi_pre_block(struct kvm_vcpu *vcpu)
+{
+	struct vcpu_vmx *vmx = to_vmx(vcpu);
+
+	vmx->in_blocked_section = true;
+
+	if (!kvm_arch_has_assigned_device(vcpu->kvm) ||
+		!irq_remapping_cap(IRQ_POSTING_CAP)  ||
+		!kvm_vcpu_apicv_active(vcpu))
+		return 0;
+
+	WARN_ON(irqs_disabled());
+	local_irq_disable();
+	__pi_pre_block(vcpu);
 	local_irq_enable();
+
 	return (vcpu->pre_pcpu == -1);
 }
 
 void pi_post_block(struct kvm_vcpu *vcpu)
 {
+	struct vcpu_vmx *vmx = to_vmx(vcpu);
+
+	vmx->in_blocked_section = false;
 	if (vcpu->pre_pcpu == -1)
 		return;
 
@@ -236,6 +250,52 @@ bool pi_has_pending_interrupt(struct kvm
 		(pi_test_sn(pi_desc) && !pi_is_pir_empty(pi_desc));
 }
 
+static void pi_update_wakeup_vector(void *data)
+{
+	struct vcpu_vmx *vmx;
+	struct kvm_vcpu *vcpu = data;
+
+	vmx = to_vmx(vcpu);
+
+	/* race with pi_post_block ? */
+	if (vcpu->pre_pcpu != -1)
+		return;
+
+	if (!vmx->in_blocked_section)
+		return;
+
+	__pi_pre_block(vcpu);
+}
+
+void vmx_pi_start_assignment(struct kvm *kvm, int device_count)
+{
+	struct kvm_vcpu *vcpu;
+	int i;
+
+	if (!irq_remapping_cap(IRQ_POSTING_CAP))
+		return;
+
+	/* only care about first device assignment */
+	if (device_count != 1)
+		return;
+
+	/* Update wakeup vector and add vcpu to blocked_vcpu_list */
+	kvm_for_each_vcpu(i, vcpu, kvm) {
+		struct vcpu_vmx *vmx = to_vmx(vcpu);
+		int pcpu;
+
+		if (!kvm_vcpu_apicv_active(vcpu))
+			continue;
+
+		preempt_disable();
+		pcpu = vcpu->cpu;
+		if (vmx->in_blocked_section && vcpu->pre_pcpu == -1 &&
+		    pcpu != -1 && pcpu != smp_processor_id())
+			smp_call_function_single(pcpu, pi_update_wakeup_vector,
+						 vcpu, 1);
+		preempt_enable();
+	}
+}
 
 /*
  * pi_update_irte - set IRTE for Posted-Interrupts
Index: kvm/arch/x86/kvm/vmx/posted_intr.h
===================================================================
--- kvm.orig/arch/x86/kvm/vmx/posted_intr.h
+++ kvm/arch/x86/kvm/vmx/posted_intr.h
@@ -95,5 +95,6 @@ void __init pi_init_cpu(int cpu);
 bool pi_has_pending_interrupt(struct kvm_vcpu *vcpu);
 int pi_update_irte(struct kvm *kvm, unsigned int host_irq, uint32_t guest_irq,
 		   bool set);
+void vmx_pi_start_assignment(struct kvm *kvm, int device_count);
 
 #endif /* __KVM_X86_VMX_POSTED_INTR_H */
Index: kvm/arch/x86/kvm/vmx/vmx.h
===================================================================
--- kvm.orig/arch/x86/kvm/vmx/vmx.h
+++ kvm/arch/x86/kvm/vmx/vmx.h
@@ -336,6 +336,9 @@ struct vcpu_vmx {
 		DECLARE_BITMAP(read, MAX_POSSIBLE_PASSTHROUGH_MSRS);
 		DECLARE_BITMAP(write, MAX_POSSIBLE_PASSTHROUGH_MSRS);
 	} shadow_msr_intercept;
+
+	/* true if vcpu is between pre_block and post_block */
+	bool in_blocked_section;
 };
 
 enum ept_pointers_status {
```
#### [PATCH 1/2] kexec: Allow architecture code to opt-out at runtime
##### From: Joerg Roedel <joro@8bytes.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Joerg Roedel <joro@8bytes.org>
X-Patchwork-Id: 12241913
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E07D7C43461
	for <kvm@archiver.kernel.org>; Thu,  6 May 2021 09:32:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B3687610C8
	for <kvm@archiver.kernel.org>; Thu,  6 May 2021 09:32:01 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234117AbhEFJc5 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 6 May 2021 05:32:57 -0400
Received: from 8bytes.org ([81.169.241.247]:37654 "EHLO theia.8bytes.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229698AbhEFJc4 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 6 May 2021 05:32:56 -0400
Received: from cap.home.8bytes.org (p5b0069de.dip0.t-ipconnect.de
 [91.0.105.222])
        (using TLSv1.3 with cipher TLS_AES_256_GCM_SHA384 (256/256 bits))
        (No client certificate requested)
        by theia.8bytes.org (Postfix) with ESMTPSA id 73639379;
        Thu,  6 May 2021 11:31:56 +0200 (CEST)
From: Joerg Roedel <joro@8bytes.org>
To: Eric Biederman <ebiederm@xmission.com>, x86@kernel.org
Cc: kexec@lists.infradead.org, Joerg Roedel <jroedel@suse.de>,
        stable@vger.kernel.org, hpa@zytor.com,
        Andy Lutomirski <luto@kernel.org>,
        Dave Hansen <dave.hansen@linux.intel.com>,
        Peter Zijlstra <peterz@infradead.org>,
        Jiri Slaby <jslaby@suse.cz>,
        Dan Williams <dan.j.williams@intel.com>,
        Tom Lendacky <thomas.lendacky@amd.com>,
        Juergen Gross <jgross@suse.com>,
        Kees Cook <keescook@chromium.org>,
        David Rientjes <rientjes@google.com>,
        Cfir Cohen <cfir@google.com>,
        Erdem Aktas <erdemaktas@google.com>,
        Masami Hiramatsu <mhiramat@kernel.org>,
        Mike Stunes <mstunes@vmware.com>,
        Sean Christopherson <seanjc@google.com>,
        Martin Radev <martin.b.radev@gmail.com>,
        Arvind Sankar <nivedita@alum.mit.edu>,
        Joerg Roedel <joro@8bytes.org>, linux-coco@lists.linux.dev,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org
Subject: [PATCH 1/2] kexec: Allow architecture code to opt-out at runtime
Date: Thu,  6 May 2021 11:31:21 +0200
Message-Id: <20210506093122.28607-2-joro@8bytes.org>
X-Mailer: git-send-email 2.31.1
In-Reply-To: <20210506093122.28607-1-joro@8bytes.org>
References: <20210506093122.28607-1-joro@8bytes.org>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Joerg Roedel <jroedel@suse.de>

Allow a runtime opt-out of kexec support for architecture code in case
the kernel is running in an environment where kexec is not properly
supported yet.

This will be used on x86 when the kernel is running as an SEV-ES
guest. SEV-ES guests need special handling for kexec to hand over all
CPUs to the new kernel. This requires special hypervisor support and
handling code in the guest which is not yet implemented.

Cc: stable@vger.kernel.org # v5.10+
Signed-off-by: Joerg Roedel <jroedel@suse.de>
---
 kernel/kexec.c | 14 ++++++++++++++
 1 file changed, 14 insertions(+)

```
#### [PATCH] x86: Do not assign values to unaligned pointer to 128 bitsFrom: Jacob Xu <jacobhxu@google.com>
##### From: Jacob Xu <jacobhxu@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jacob Xu <jacobhxu@google.com>
X-Patchwork-Id: 12241409
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id EA59DC43460
	for <kvm@archiver.kernel.org>; Thu,  6 May 2021 00:48:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BFAF1610C8
	for <kvm@archiver.kernel.org>; Thu,  6 May 2021 00:48:54 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229662AbhEFAtv (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 5 May 2021 20:49:51 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:35104 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229465AbhEFAtu (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 5 May 2021 20:49:50 -0400
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 3216EC061574
        for <kvm@vger.kernel.org>; Wed,  5 May 2021 17:48:53 -0700 (PDT)
Received: by mail-yb1-xb49.google.com with SMTP id
 u3-20020a2509430000b02904e7f1a30cffso4228918ybm.8
        for <kvm@vger.kernel.org>; Wed, 05 May 2021 17:48:53 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=HOXBWmgxEesnlPSTtd8P6NnachLBXrmty/gg16gcyj0=;
        b=QoG1kbuEO+URMeJmt2aLsDGE2a3jrRLoMoaOV95XKXhNVndHGaUfPL0r1/Pp8KM7T0
         85j0RK/12lG0FoVkqWha7BNfpyxQoNgmbbQbt5gkfDS82Ucv667QFMyicp+T5qdOMDap
         8RZNFKALFW5WDfK50UZ1ouFwN9MMhjdz8lpLY2epU0tisNWpLS25mnSkRrOQyzOWSmht
         SVHQBIo0bFvSuRhTKRsZXpDcaI/l1TwUadu90ShVgvTDdFCuJSxzbin1MerFsfMI4qrs
         ts36tJRxmIsuzOmrv66UyRy8uAokLxh1+mdPVfpREopnePSYjkALjb1FpcHVGjozAU8F
         KRyw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=HOXBWmgxEesnlPSTtd8P6NnachLBXrmty/gg16gcyj0=;
        b=GZdua2WXmCnjIvsyAyZGvkq+v5GSMaDx4c1MT7VuPPw+yLjeW2Lg0eFik2Qzl09q/w
         mGB7CXiXR3xb6iONjJjARBUC/R3G5RtqmploN5Qaw/zliG8u+8GPXbOJd7hitYkbFrJL
         ugYbBBHBSkfKV+mgQUwwjTp/su1dg/DZ/Rd2bgrJf8sW9PgJSUhxlb+CjRDzXhZTDZ0I
         abuHcG9yPizRhbpRvz2/wy2ysr90dHjQFM6qebvCA8lii1e8gHKg2unNiWC+9Qbf+0WV
         S9r9/vlPQoQtma7wvDQbU2eCEtZBxqY2OPCH6NLxi0IMqTboWrluObOdwmBAP7KA0mb3
         t1yw==
X-Gm-Message-State: AOAM531EUHoHvrv7H1O0wCL+17uukQrbkNlrbiUYpNnGxmIbbatA4rbI
        j3s2IEip7pZuP8EnBP1dg1usZIHzsCF82A==
X-Google-Smtp-Source: 
 ABdhPJzdAoNO9Ji3PBaQIjl1+fxf+m55M3kiUvheBzR+AYJ3srK1Uhhe9/qiMofMjuhw998gBZg7SfFhEAGXPg==
X-Received: from mhmmm.sea.corp.google.com
 ([2620:15c:100:202:77e2:ac:d4b1:cc53])
 (user=jacobhxu job=sendgmr) by 2002:a25:9982:: with SMTP id
 p2mr2115438ybo.457.1620262132380; Wed, 05 May 2021 17:48:52 -0700 (PDT)
Date: Wed,  5 May 2021 17:48:47 -0700
Message-Id: <20210506004847.210466-1-jacobhxu@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.1.527.g47e6f16901-goog
Subject: [PATCH] x86: Do not assign values to unaligned pointer to 128 bits
From: Jacob Xu <jacobhxu@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Jim Mattson <jmattson@google.com>
Cc: kvm@vger.kernel.org, Jacob Xu <jacobhxu@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When compiled with clang, the following statement gets converted into a
movaps instructions.
mem->u[0] = 5; mem->u[1] = 6; mem->u[2] = 7; mem->u[3] = 8;

Since mem is an unaligned pointer to a union of an sse, we get a GP when
running.

All we want is to make the values between mem and v different for this
testcase, so let's just memset the pointer at mem, and convert to
uint8_t pointer. Then the compiler will not assume the pointer is
aligned to 128 bits.

Fixes: e5e76263b5 ("x86: add additional test cases for sse exceptions to
emulator.c")

Signed-off-by: Jacob Xu <jacobhxu@google.com>
---
 x86/emulator.c | 6 +++---
 1 file changed, 3 insertions(+), 3 deletions(-)

```
