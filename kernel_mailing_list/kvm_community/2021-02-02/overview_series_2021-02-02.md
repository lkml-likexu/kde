#### [PATCH v2 1/3] KVM: X86: Rename DR6_INIT to DR6_ACTIVE_LOW
##### From: Chenyi Qiang <chenyi.qiang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Chenyi Qiang <chenyi.qiang@intel.com>
X-Patchwork-Id: 12061165
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 05D48C433E0
	for <kvm@archiver.kernel.org>; Tue,  2 Feb 2021 09:02:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C9A1164F67
	for <kvm@archiver.kernel.org>; Tue,  2 Feb 2021 09:02:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232828AbhBBJCT (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 2 Feb 2021 04:02:19 -0500
Received: from mga02.intel.com ([134.134.136.20]:41961 "EHLO mga02.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S232733AbhBBJCH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 2 Feb 2021 04:02:07 -0500
IronPort-SDR: 
 Lg5Urppqis4XRE7RzKH2IO5JFP8y7UnXIVvsG6G0962HfDqgcwoXOv5APCqyjhY0bN1dZGWTWL
 PwpKg8Iv7fEA==
X-IronPort-AV: E=McAfee;i="6000,8403,9882"; a="167929215"
X-IronPort-AV: E=Sophos;i="5.79,394,1602572400";
   d="scan'208";a="167929215"
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by orsmga101.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 02 Feb 2021 01:01:25 -0800
IronPort-SDR: 
 gnUXbQ3V6kGW8lXVj6PIheLMNT4OxxLyIzr4p4IrWbEA/b+8sPPXzf14Q2xFmz6tLpfguSnX1f
 Ygo/Il9Y2maw==
X-IronPort-AV: E=Sophos;i="5.79,394,1602572400";
   d="scan'208";a="479491914"
Received: from chenyi-pc.sh.intel.com ([10.239.159.24])
  by fmsmga001-auth.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 02 Feb 2021 01:01:22 -0800
From: Chenyi Qiang <chenyi.qiang@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Xiaoyao Li <xiaoyao.li@intel.com>
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH v2 1/3] KVM: X86: Rename DR6_INIT to DR6_ACTIVE_LOW
Date: Tue,  2 Feb 2021 17:04:31 +0800
Message-Id: <20210202090433.13441-2-chenyi.qiang@intel.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20210202090433.13441-1-chenyi.qiang@intel.com>
References: <20210202090433.13441-1-chenyi.qiang@intel.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

DR6_INIT contains the 1-reserved bits as well as the bit that is cleared
to 0 when the condition (e.g. RTM) happens. The value can be used to
initialize dr6 and also be the XOR mask between the #DB exit
qualification (or payload) and DR6.

Concerning that DR6_INIT is used as initial value only once, rename it
to DR6_ACTIVE_LOW and apply it in other places, which would make the
incoming changes for bus lock debug exception more simple.

Signed-off-by: Chenyi Qiang <chenyi.qiang@intel.com>
---
 arch/x86/include/asm/kvm_host.h |  9 ++++++++-
 arch/x86/kvm/emulate.c          |  2 +-
 arch/x86/kvm/svm/nested.c       |  2 +-
 arch/x86/kvm/svm/svm.c          |  6 +++---
 arch/x86/kvm/vmx/nested.c       |  4 ++--
 arch/x86/kvm/vmx/vmx.c          |  4 ++--
 arch/x86/kvm/x86.c              | 33 +++++++++++++++++++--------------
 7 files changed, 36 insertions(+), 24 deletions(-)

```
#### [PATCH v2 01/28] KVM: x86/mmu: change TDP MMU yield function returns to match cond_resched
##### From: Ben Gardon <bgardon@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ben Gardon <bgardon@google.com>
X-Patchwork-Id: 12062661
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 8BE93C433DB
	for <kvm@archiver.kernel.org>; Tue,  2 Feb 2021 18:59:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5219964EC1
	for <kvm@archiver.kernel.org>; Tue,  2 Feb 2021 18:59:40 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S239249AbhBBS7O (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 2 Feb 2021 13:59:14 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:57276 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S239212AbhBBS6V (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 2 Feb 2021 13:58:21 -0500
Received: from mail-pg1-x549.google.com (mail-pg1-x549.google.com
 [IPv6:2607:f8b0:4864:20::549])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 3AF5CC061788
        for <kvm@vger.kernel.org>; Tue,  2 Feb 2021 10:57:41 -0800 (PST)
Received: by mail-pg1-x549.google.com with SMTP id l7so8695688pgj.4
        for <kvm@vger.kernel.org>; Tue, 02 Feb 2021 10:57:41 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:in-reply-to:message-id:mime-version:references:subject
         :from:to:cc;
        bh=JmOMIXWttp6i62xS7cuIM/ozODaFpac3D3d4bnLpAU8=;
        b=euAu6Opvq1y1VpidLQ8Oq09e/TrLgb/rbhNuIy2MmJdEzB5ZqUlxB1H8xT8zfEB6Vj
         3/BJsYUUVr/lDP04W+4nMyvJpPCOq38UjhDo51soy8LwSenYDFUqqpXnCT7SpBTbwtjY
         cbCcJh8qRfoDvwUktyeGxopGlmq167RyyhBBmzRG6lINudxDvwgHgItf/N1LJFQFjct/
         eibxVR8YJ95nhps7dxooxnJCCQlGca8uynQ1L9GlG9zvottVYQRO8M3aWUqgl6K84I6A
         OkPyluEoHxW6iVYkDeYqPK34PiUT4fA07x9XVkUuWgbmQu7E/m8Cj7PTnbNdgLKB8L7j
         tkpA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=JmOMIXWttp6i62xS7cuIM/ozODaFpac3D3d4bnLpAU8=;
        b=K/j/DC4QQp0RecMiAirr/WzJug4IfVCEU0nQ1/VJ4QwuHU+7L8YJHAZOEUb6kkj0cE
         M6TCdbzkFrsBUnzN/bP5HlaMJmMQ3fENRkuJluCxcFTsV+iFadh5NT0O48+ztP5CXS5M
         hI427UlIjiPL14m9XqTTx2iQwAqufUgdblFSsyBgof+yWtmluUGyuuDYVtIdwgQfV09u
         NlF1KkpeP6aEm7xG/nRMerXh/S78F7r6YVXucR7H3o6JenAaRyh4g3LM5rWk/GuN1o2D
         fh7XB1dXZOVusoyAoVPvlfGWTc26PcxzwzelaFOGGSpRL505WemmqRgH992lCdepKQlx
         Blbg==
X-Gm-Message-State: AOAM531wgoqM0UX4YModAPKFIF+CoNkKn3XpAGbW1KkMVA8fySIyJx3o
        ZiAspSi0IMbaSagQbCqWIHOFeI63hlwt
X-Google-Smtp-Source: 
 ABdhPJyALatEZ01ixKvjEw/9drTlyjjz5b4Lp2A/W9XIayTqqPdwvUTu2WeQErsecDzxzztrUEokK56l18Hf
Sender: "bgardon via sendgmr" <bgardon@bgardon.sea.corp.google.com>
X-Received: from bgardon.sea.corp.google.com
 ([2620:15c:100:202:9090:561:5a98:6d47])
 (user=bgardon job=sendgmr) by 2002:a05:6a00:2b8:b029:1b8:a114:f81f with SMTP
 id q24-20020a056a0002b8b02901b8a114f81fmr22719715pfs.19.1612292260621; Tue,
 02 Feb 2021 10:57:40 -0800 (PST)
Date: Tue,  2 Feb 2021 10:57:07 -0800
In-Reply-To: <20210202185734.1680553-1-bgardon@google.com>
Message-Id: <20210202185734.1680553-2-bgardon@google.com>
Mime-Version: 1.0
References: <20210202185734.1680553-1-bgardon@google.com>
X-Mailer: git-send-email 2.30.0.365.g02bc693789-goog
Subject: [PATCH v2 01/28] KVM: x86/mmu: change TDP MMU yield function returns
 to match cond_resched
From: Ben Gardon <bgardon@google.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>, Peter Xu <peterx@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Peter Shier <pshier@google.com>,
        Peter Feiner <pfeiner@google.com>,
        Junaid Shahid <junaids@google.com>,
        Jim Mattson <jmattson@google.com>,
        Yulei Zhang <yulei.kernel@gmail.com>,
        Wanpeng Li <kernellwp@gmail.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Xiao Guangrong <xiaoguangrong.eric@gmail.com>,
        Ben Gardon <bgardon@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Currently the TDP MMU yield / cond_resched functions either return
nothing or return true if the TLBs were not flushed. These are confusing
semantics, especially when making control flow decisions in calling
functions.

To clean things up, change both functions to have the same
return value semantics as cond_resched: true if the thread yielded,
false if it did not. If the function yielded in the _flush_ version,
then the TLBs will have been flushed.

Reviewed-by: Peter Feiner <pfeiner@google.com>
Acked-by: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Ben Gardon <bgardon@google.com>
---
 arch/x86/kvm/mmu/tdp_mmu.c | 39 ++++++++++++++++++++++++++++----------
 1 file changed, 29 insertions(+), 10 deletions(-)

```
#### [PATCH v8 01/13] qom: Allow optional sugar props
##### From: David Gibson <david@gibson.dropbear.id.au>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: David Gibson <david@gibson.dropbear.id.au>
X-Patchwork-Id: 12060565
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 76295C433DB
	for <kvm@archiver.kernel.org>; Tue,  2 Feb 2021 04:14:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 402D064ED3
	for <kvm@archiver.kernel.org>; Tue,  2 Feb 2021 04:14:06 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231597AbhBBEOE (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 1 Feb 2021 23:14:04 -0500
Received: from ozlabs.org ([203.11.71.1]:52103 "EHLO ozlabs.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S231575AbhBBEOB (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 1 Feb 2021 23:14:01 -0500
Received: by ozlabs.org (Postfix, from userid 1007)
        id 4DVBHy0M0Qz9tjs; Tue,  2 Feb 2021 15:13:17 +1100 (AEDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple;
        d=gibson.dropbear.id.au; s=201602; t=1612239198;
        bh=RfSzBSrTuKsV2JBEfuSIZjevzuR/AfKedHtEOaQArcc=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=EgqTWnM9gvAFXbtvPB+2L+8dobrnwUsmC2r8ivWAzDrnSyoUkglqLqYgP/8u/iBsA
         0OTBFEYPKL4QXB8e1LzlyaqtRkOE0a0AEAcW/E7/KCOxYfXLdnL/0pTC5WsGEt8waH
         quRQrBB5C4k/EhxZHmafEnr5mAENSh1e80KUehH8=
From: David Gibson <david@gibson.dropbear.id.au>
To: dgilbert@redhat.com, pair@us.ibm.com, qemu-devel@nongnu.org,
        brijesh.singh@amd.com, pasic@linux.ibm.com
Cc: pragyansri.pathi@intel.com, Greg Kurz <groug@kaod.org>,
 richard.henderson@linaro.org, berrange@redhat.com,
 David Hildenbrand <david@redhat.com>, mdroth@linux.vnet.ibm.com,
 kvm@vger.kernel.org, Marcel Apfelbaum <marcel.apfelbaum@gmail.com>,
 pbonzini@redhat.com, mtosatti@redhat.com, borntraeger@de.ibm.com,
 Cornelia Huck <cohuck@redhat.com>, qemu-ppc@nongnu.org,
 David Gibson <david@gibson.dropbear.id.au>, qemu-s390x@nongnu.org,
 thuth@redhat.com, mst@redhat.com, frankja@linux.ibm.com,
 jun.nakajima@intel.com, andi.kleen@intel.com,
 Eduardo Habkost <ehabkost@redhat.com>, =?utf-8?q?Philippe_Mathieu-Daud?=
	=?utf-8?q?=C3=A9?= <philmd@redhat.com>
Subject: [PATCH v8 01/13] qom: Allow optional sugar props
Date: Tue,  2 Feb 2021 15:13:03 +1100
Message-Id: <20210202041315.196530-2-david@gibson.dropbear.id.au>
X-Mailer: git-send-email 2.29.2
In-Reply-To: <20210202041315.196530-1-david@gibson.dropbear.id.au>
References: <20210202041315.196530-1-david@gibson.dropbear.id.au>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Greg Kurz <groug@kaod.org>

Global properties have an @optional field, which allows to apply a given
property to a given type even if one of its subclasses doesn't support
it. This is especially used in the compat code when dealing with the
"disable-modern" and "disable-legacy" properties and the "virtio-pci"
type.

Allow object_register_sugar_prop() to set this field as well.

Signed-off-by: Greg Kurz <groug@kaod.org>
Message-Id: <159738953558.377274.16617742952571083440.stgit@bahia.lan>
Signed-off-by: David Gibson <david@gibson.dropbear.id.au>
Reviewed-by: Eduardo Habkost <ehabkost@redhat.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: Philippe Mathieu-Daudé <philmd@redhat.com>
---
 include/qom/object.h |  3 ++-
 qom/object.c         |  4 +++-
 softmmu/rtc.c        |  3 ++-
 softmmu/vl.c         | 17 +++++++++++------
 4 files changed, 18 insertions(+), 9 deletions(-)

```
#### [GIT PULL] immutable branch for amba changes targeting v5.12-rc1
##### From: Uwe =?utf-8?q?Kleine-K=C3=B6nig?= <u.kleine-koenig@pengutronix.de>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Uwe_Kleine-K=C3=B6nig?=
 <u.kleine-koenig@pengutronix.de>
X-Patchwork-Id: 12062767
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,INCLUDES_PULL_REQUEST,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 99225C43381
	for <kvm@archiver.kernel.org>; Tue,  2 Feb 2021 19:34:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 81FE864F2C
	for <kvm@archiver.kernel.org>; Tue,  2 Feb 2021 19:34:12 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233386AbhBBTdw (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 2 Feb 2021 14:33:52 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:48620 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S233411AbhBBN5G (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 2 Feb 2021 08:57:06 -0500
Received: from metis.ext.pengutronix.de (metis.ext.pengutronix.de
 [IPv6:2001:67c:670:201:290:27ff:fe1d:cc33])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id CC402C06174A
        for <kvm@vger.kernel.org>; Tue,  2 Feb 2021 05:56:25 -0800 (PST)
Received: from ptx.hi.pengutronix.de ([2001:67c:670:100:1d::c0])
        by metis.ext.pengutronix.de with esmtps
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <ukl@pengutronix.de>)
        id 1l6w82-0000fW-TE; Tue, 02 Feb 2021 14:54:02 +0100
Received: from ukl by ptx.hi.pengutronix.de with local (Exim 4.92)
        (envelope-from <ukl@pengutronix.de>)
        id 1l6w7u-0006bW-5D; Tue, 02 Feb 2021 14:53:54 +0100
Date: Tue, 2 Feb 2021 14:53:50 +0100
From: Uwe =?utf-8?q?Kleine-K=C3=B6nig?= <u.kleine-koenig@pengutronix.de>
To: Russell King <linux+pull@armlinux.org.uk>,
        Mathieu Poirier <mathieu.poirier@linaro.org>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Alexander Shishkin <alexander.shishkin@linux.intel.com>,
        Greg Kroah-Hartman <gregkh@linuxfoundation.org>
Cc: linux-fbdev@vger.kernel.org, kvm@vger.kernel.org,
 alsa-devel@alsa-project.org, dri-devel@lists.freedesktop.org, Uwe
	=?utf-8?q?Kleine-K=C3=B6nig?=  <u.kleine-koenig.org@pengutronix.de>,
 linux-i2c@vger.kernel.org, linux-stm32@st-md-mailman.stormreply.com,
 linux-rtc@vger.kernel.org, linux-serial@vger.kernel.org,
 linux-input@vger.kernel.org, Mike Leach <mike.leach@linaro.org>,
 linux-watchdog@vger.kernel.org, Arnd Bergmann <arnd@arndb.de>,
 coresight@lists.linaro.org, linux-arm-kernel@lists.infradead.org,
 linux-mmc@vger.kernel.org, linux-kernel@vger.kernel.org,
 linux-spi@vger.kernel.org, linux-crypto@vger.kernel.org,
 kernel@pengutronix.de, Leo Yan <leo.yan@linaro.org>,
 dmaengine@vger.kernel.org, Matt Mackall <mpm@selenic.com>,
 Herbert Xu <herbert@gondor.apana.org.au>, Vinod Koul <vkoul@kernel.org>,
 Dan Williams <dan.j.williams@intel.com>, Eric Anholt <eric@anholt.net>,
 David Airlie <airlied@linux.ie>, Daniel Vetter <daniel@ffwll.ch>,
 Maxime Coquelin <mcoquelin.stm32@gmail.com>,
 Alexandre Torgue <alexandre.torgue@st.com>,
 Linus Walleij <linus.walleij@linaro.org>,
 Dmitry Torokhov <dmitry.torokhov@gmail.com>,
 Vladimir Zapolskiy <vz@mleia.com>, Krzysztof Kozlowski <krzk@kernel.org>,
 Ulf Hansson <ulf.hansson@linaro.org>,
 Alessandro Zummo <a.zummo@towertech.it>,
 Alexandre Belloni <alexandre.belloni@bootlin.com>,
 Mark Brown <broonie@kernel.org>, Jiri Slaby <jirislaby@kernel.org>,
 Eric Auger <eric.auger@redhat.com>,
 Alex Williamson <alex.williamson@redhat.com>,
 Cornelia Huck <cohuck@redhat.com>, Wim Van Sebroeck <wim@linux-watchdog.org>,
 Guenter Roeck <linux@roeck-us.net>, Jaroslav Kysela <perex@perex.cz>,
 Takashi Iwai <tiwai@suse.com>
Subject: [GIT PULL] immutable branch for amba changes targeting v5.12-rc1
Message-ID: <20210202135350.36nj3dmcoq3t7gcf@pengutronix.de>
References: <20210126165835.687514-1-u.kleine-koenig@pengutronix.de>
MIME-Version: 1.0
Content-Disposition: inline
In-Reply-To: <20210126165835.687514-1-u.kleine-koenig@pengutronix.de>
X-SA-Exim-Connect-IP: 2001:67c:670:100:1d::c0
X-SA-Exim-Mail-From: ukl@pengutronix.de
X-SA-Exim-Scanned: No (on metis.ext.pengutronix.de);
 SAEximRunCond expanded to false
X-PTX-Original-Recipient: kvm@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hello,

the following changes since commit 5c8fe583cce542aa0b84adc939ce85293de36e5e:

  Linux 5.11-rc1 (2020-12-27 15:30:22 -0800)

are available in the Git repository at:

  https://git.pengutronix.de/git/ukl/linux tags/amba-make-remove-return-void

for you to fetch changes up to f170b59fedd733b92f58c4d7c8357fbf7601d623:

  amba: Make use of bus_type functions (2021-02-02 14:26:02 +0100)

I expect this tag to be merged by Russell King as amba maintainer and by
Mathieu Poirier (or Greg Kroah-Hartman?) for coresight as there are some
pending conflicting changes. These are not hard to resolve but also
non-trivial. Tell me if you need assistance for resolving, also if it's only a
second pair of eyes to judge your resolution.

Best regards,
Uwe

----------------------------------------------------------------
Tag for adaptions to struct amba_driver::remove changing prototype

----------------------------------------------------------------
Uwe Kleine-König (5):
      amba: Fix resource leak for drivers without .remove
      amba: reorder functions
      vfio: platform: simplify device removal
      amba: Make the remove callback return void
      amba: Make use of bus_type functions

 drivers/amba/bus.c                                 | 234 +++++++++++++++++++++++++++++++++------------------------------
 drivers/char/hw_random/nomadik-rng.c               |   3 +-
 drivers/dma/pl330.c                                |   3 +-
 drivers/gpu/drm/pl111/pl111_drv.c                  |   4 +-
 drivers/hwtracing/coresight/coresight-catu.c       |   3 +-
 drivers/hwtracing/coresight/coresight-cpu-debug.c  |   4 +-
 drivers/hwtracing/coresight/coresight-cti-core.c   |   4 +-
 drivers/hwtracing/coresight/coresight-etb10.c      |   4 +-
 drivers/hwtracing/coresight/coresight-etm3x-core.c |   4 +-
 drivers/hwtracing/coresight/coresight-etm4x-core.c |   4 +-
 drivers/hwtracing/coresight/coresight-funnel.c     |   4 +-
 drivers/hwtracing/coresight/coresight-replicator.c |   4 +-
 drivers/hwtracing/coresight/coresight-stm.c        |   4 +-
 drivers/hwtracing/coresight/coresight-tmc-core.c   |   4 +-
 drivers/hwtracing/coresight/coresight-tpiu.c       |   4 +-
 drivers/i2c/busses/i2c-nomadik.c                   |   4 +-
 drivers/input/serio/ambakmi.c                      |   3 +-
 drivers/memory/pl172.c                             |   4 +-
 drivers/memory/pl353-smc.c                         |   4 +-
 drivers/mmc/host/mmci.c                            |   4 +-
 drivers/rtc/rtc-pl030.c                            |   4 +-
 drivers/rtc/rtc-pl031.c                            |   4 +-
 drivers/spi/spi-pl022.c                            |   5 +-
 drivers/tty/serial/amba-pl010.c                    |   4 +-
 drivers/tty/serial/amba-pl011.c                    |   3 +-
 drivers/vfio/platform/vfio_amba.c                  |  15 ++--
 drivers/video/fbdev/amba-clcd.c                    |   4 +-
 drivers/watchdog/sp805_wdt.c                       |   4 +-
 include/linux/amba/bus.h                           |   2 +-
 sound/arm/aaci.c                                   |   4 +-
 30 files changed, 157 insertions(+), 198 deletions(-)
```
#### [PATCH v17 1/7] arm/arm64: Probe for the presence of KVM hypervisor
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 12061851
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No,
 score=-17.0 required=3.0 tests=BAYES_00,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 0EF72C4332B
	for <kvm@archiver.kernel.org>; Tue,  2 Feb 2021 14:36:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D395064F50
	for <kvm@archiver.kernel.org>; Tue,  2 Feb 2021 14:36:07 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234537AbhBBOcq (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 2 Feb 2021 09:32:46 -0500
Received: from mail.kernel.org ([198.145.29.99]:52232 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S232072AbhBBOTQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 2 Feb 2021 09:19:16 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 771FF64E27;
        Tue,  2 Feb 2021 14:12:11 +0000 (UTC)
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1l6wPZ-00BVqw-Op; Tue, 02 Feb 2021 14:12:09 +0000
From: Marc Zyngier <maz@kernel.org>
To: netdev@vger.kernel.org, yangbo.lu@nxp.com, john.stultz@linaro.org,
        tglx@linutronix.de, pbonzini@redhat.com, seanjc@google.com,
        richardcochran@gmail.com, Mark.Rutland@arm.com, will@kernel.org,
        suzuki.poulose@arm.com, Andre.Przywara@arm.com,
        steven.price@arm.com
Cc: linux-kernel@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        Steve.Capper@arm.com, justin.he@arm.com, jianyong.wu@arm.com,
        kernel-team@android.com
Subject: [PATCH v17 1/7] arm/arm64: Probe for the presence of KVM hypervisor
Date: Tue,  2 Feb 2021 14:11:58 +0000
Message-Id: <20210202141204.3134855-2-maz@kernel.org>
X-Mailer: git-send-email 2.29.2
In-Reply-To: <20210202141204.3134855-1-maz@kernel.org>
References: <20210202141204.3134855-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: netdev@vger.kernel.org, yangbo.lu@nxp.com,
 john.stultz@linaro.org, tglx@linutronix.de, pbonzini@redhat.com,
 seanjc@google.com, richardcochran@gmail.com, Mark.Rutland@arm.com,
 will@kernel.org, suzuki.poulose@arm.com, Andre.Przywara@arm.com,
 steven.price@arm.com, linux-kernel@vger.kernel.org,
 linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
 kvm@vger.kernel.org, Steve.Capper@arm.com, justin.he@arm.com,
 jianyong.wu@arm.com, kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Will Deacon <will@kernel.org>

Although the SMCCC specification provides some limited functionality for
describing the presence of hypervisor and firmware services, this is
generally applicable only to functions designated as "Arm Architecture
Service Functions" and no portable discovery mechanism is provided for
standard hypervisor services, despite having a designated range of
function identifiers reserved by the specification.

In an attempt to avoid the need for additional firmware changes every
time a new function is added, introduce a UID to identify the service
provider as being compatible with KVM. Once this has been established,
additional services can be discovered via a feature bitmap.

Signed-off-by: Will Deacon <will@kernel.org>
Signed-off-by: Jianyong Wu <jianyong.wu@arm.com>
[maz: move code to its own file, plug it into PSCI]
Signed-off-by: Marc Zyngier <maz@kernel.org>
Link: https://lore.kernel.org/r/20201209060932.212364-2-jianyong.wu@arm.com
---
 arch/arm/include/asm/hypervisor.h   |  3 ++
 arch/arm64/include/asm/hypervisor.h |  3 ++
 drivers/firmware/psci/psci.c        |  2 ++
 drivers/firmware/smccc/Makefile     |  2 +-
 drivers/firmware/smccc/kvm_guest.c  | 51 +++++++++++++++++++++++++++++
 drivers/firmware/smccc/smccc.c      |  1 +
 include/linux/arm-smccc.h           | 25 ++++++++++++++
 7 files changed, 86 insertions(+), 1 deletion(-)
 create mode 100644 drivers/firmware/smccc/kvm_guest.c

```
#### [PATCH] KVM: cleanup DR6/DR7 reserved bits checks
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 12062373
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 17E24C433DB
	for <kvm@archiver.kernel.org>; Tue,  2 Feb 2021 17:06:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E015D64F8A
	for <kvm@archiver.kernel.org>; Tue,  2 Feb 2021 17:06:56 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S237161AbhBBRG3 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 2 Feb 2021 12:06:29 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:57131 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S237005AbhBBRES (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 2 Feb 2021 12:04:18 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1612285373;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=F9oAoXtAX+Cil+a1sW8Pz3+QVGLc8h16eVPUFtZSABM=;
        b=LgRsP0+gGX811rh8Wjopr3tCeT/PWO+G1Z2D6GYtTmsGPCqezyN9m0/80gTY+IbN8ZJSIY
        89ZDnXTku1UyLGOSXb1tOg3UmHGi27NSYMUDrGsR/zDk3rcrlawm9s855EsCOrM15wom+V
        yvbjtZSYcYveext1HMLp61jFty24xyA=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-252-l6UgDDbgPyelQPCboFbVhg-1; Tue, 02 Feb 2021 12:02:47 -0500
X-MC-Unique: l6UgDDbgPyelQPCboFbVhg-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id CFC87801817;
        Tue,  2 Feb 2021 17:02:46 +0000 (UTC)
Received: from virtlab511.virt.lab.eng.bos.redhat.com
 (virtlab511.virt.lab.eng.bos.redhat.com [10.19.152.198])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 7F8A75D9C6;
        Tue,  2 Feb 2021 17:02:46 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: seanjc@google.com
Subject: [PATCH] KVM: cleanup DR6/DR7 reserved bits checks
Date: Tue,  2 Feb 2021 12:02:46 -0500
Message-Id: <20210202170246.89436-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

kvm_dr6_valid and kvm_dr7_valid check that bits 63:32 are zero.  Using
them makes it easier to review the code for inconsistencies.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Sean Christopherson <seanjc@google.com> 
---
 arch/x86/kvm/x86.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH] KVM: MIPS: remove unneeded semicolon
##### From: Yang Li <yang.lee@linux.alibaba.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Li <yang.lee@linux.alibaba.com>
X-Patchwork-Id: 12060453
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,UNPARSEABLE_RELAY,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 3C046C433E6
	for <kvm@archiver.kernel.org>; Tue,  2 Feb 2021 02:16:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0F6A364EDF
	for <kvm@archiver.kernel.org>; Tue,  2 Feb 2021 02:16:50 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231158AbhBBCQY (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 1 Feb 2021 21:16:24 -0500
Received: from out30-133.freemail.mail.aliyun.com ([115.124.30.133]:38178
 "EHLO
        out30-133.freemail.mail.aliyun.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S230122AbhBBCQV (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 1 Feb 2021 21:16:21 -0500
X-Alimail-AntiSpam: 
 AC=PASS;BC=-1|-1;BR=01201311R851e4;CH=green;DM=||false|;DS=||;FP=0|-1|-1|-1|0|-1|-1|-1;HT=e01e04357;MF=yang.lee@linux.alibaba.com;NM=1;PH=DS;RN=7;SR=0;TI=SMTPD_---0UNdRSz6_1612232136;
Received: from
 j63c13417.sqa.eu95.tbsite.net(mailfrom:yang.lee@linux.alibaba.com
 fp:SMTPD_---0UNdRSz6_1612232136)
          by smtp.aliyun-inc.com(127.0.0.1);
          Tue, 02 Feb 2021 10:15:36 +0800
From: Yang Li <yang.lee@linux.alibaba.com>
To: chenhuacai@kernel.org
Cc: aleksandar.qemu.devel@gmail.com, tsbogend@alpha.franken.de,
        linux-mips@vger.kernel.org, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Yang Li <yang.lee@linux.alibaba.com>
Subject: [PATCH] KVM: MIPS: remove unneeded semicolon
Date: Tue,  2 Feb 2021 10:15:35 +0800
Message-Id: <1612232135-26683-1-git-send-email-yang.lee@linux.alibaba.com>
X-Mailer: git-send-email 1.8.3.1
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Eliminate the following coccicheck warning:
./arch/mips/kvm/mips.c:151:2-3: Unneeded semicolon

Reported-by: Abaci Robot <abaci@linux.alibaba.com>
Signed-off-by: Yang Li <yang.lee@linux.alibaba.com>
Reviewed-by: Huacai Chen <chenhuacai@kernel.org>
---
 arch/mips/kvm/mips.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] KVM: move EXIT_FASTPATH_REENTER_GUEST to common code
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 12062115
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id AD06EC433DB
	for <kvm@archiver.kernel.org>; Tue,  2 Feb 2021 16:13:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 55CAC64F55
	for <kvm@archiver.kernel.org>; Tue,  2 Feb 2021 16:13:37 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S235908AbhBBQNJ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 2 Feb 2021 11:13:09 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:29475 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S235959AbhBBQLr (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 2 Feb 2021 11:11:47 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1612282220;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=sYZzkVHR2ls3xvESHEyOkdDA3MfonApqwRfCSseBrz8=;
        b=TEIG5nGSvINMLGX9FsAbfccw2isTBm7Hhji9uAxq6ExChBCRrNzg5/b1X+Bh7hvGGZjCwh
        4oM7XymLhG0ElJreeKM9hjg+vhG6m0qIupiatm7VwRs9lt8WIuXYIiSeyyXYEPMfMb9F8j
        92Euuv3LvDVUy9Nzwm4xvw60em3xHVE=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-397-Zc6Hv7T2NGaAwYtEqRBMcA-1; Tue, 02 Feb 2021 11:10:16 -0500
X-MC-Unique: Zc6Hv7T2NGaAwYtEqRBMcA-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id A9DF581621;
        Tue,  2 Feb 2021 16:10:15 +0000 (UTC)
Received: from virtlab511.virt.lab.eng.bos.redhat.com
 (virtlab511.virt.lab.eng.bos.redhat.com [10.19.152.198])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 4F4B25C22B;
        Tue,  2 Feb 2021 16:10:15 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: jbaron@akamai.com
Subject: [PATCH] KVM: move EXIT_FASTPATH_REENTER_GUEST to common code
Date: Tue,  2 Feb 2021 11:10:14 -0500
Message-Id: <20210202161014.67093-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Now that KVM is using static calls, calling vmx_vcpu_run and
vmx_sync_pir_to_irr does not incur anymore the cost of a
retpoline.

Therefore there is no need anymore to handle EXIT_FASTPATH_REENTER_GUEST
in vendor code.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/vmx/vmx.c | 19 +------------------
 arch/x86/kvm/x86.c     | 17 ++++++++++++++---
 arch/x86/kvm/x86.h     |  1 -
 3 files changed, 15 insertions(+), 22 deletions(-)

```
#### [PATCH v4 1/3] KVM: SVM: use vmsave/vmload for saving/restoring additional host state
##### From: Michael Roth <michael.roth@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Michael Roth <michael.roth@amd.com>
X-Patchwork-Id: 12062689
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,
	SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 032EFC433DB
	for <kvm@archiver.kernel.org>; Tue,  2 Feb 2021 19:07:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BB1B964DA5
	for <kvm@archiver.kernel.org>; Tue,  2 Feb 2021 19:07:55 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S239313AbhBBTHh (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 2 Feb 2021 14:07:37 -0500
Received: from mail-mw2nam12hn2219.outbound.protection.outlook.com
 ([52.100.167.219]:28736
        "EHLO NAM12-MW2-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S239411AbhBBTDV (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 2 Feb 2021 14:03:21 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=MtJtpQkxn/9IDTPrarlO1wDHzkhuFZhzG0Qu6TiEfB8ZlYedv10ht3W4wKSDy4B13b0TzcXZ1egUht76FPEEocxdkd9PNVtEClzupRUx3lJPaZMd6X9UX3k6bzrjbTibaoW21gGRSPzOxgP81LRvYVJK4uk+eS7OxyYcJvCRd/buVnuRt75Wh170BbjSNtqDA/Sq7p4KL2M3I0rHjdQESLC/U+9iAzMT7M2XILkdGt8cwcoRrsxn0tc0JhifVtpQQDeoPptOSrGtAfOsyjUx45eOcSk7x8iBcjAJjzEEe0jRazi/yyNQDpGrBlhZOeZd4yAScOXolsc7gQCBWdHZ8Q==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=44wOblXdL5kqFLlvvvthkEjwALIAI0JsqHasc9b9oxc=;
 b=WE8baLDt0cXdbdbMpAAuu/R8q7JXcWIZhAXXkzQVkTDM+5sEh6Wi1D63uXc2Spr3vnI6js5zW8iSAJRefJh+UESDGmGreZGAJ48cZwcAcdxI7wJouji/utXf4VUhc6mChUwZH4NFl45NgCj/FEP+I34CDPvvkDEWdrOrppArDgVDvGN2vKVXzQcrbLcnU8e7At2PDAhhIFJcSqEJh1BBeG8u0sRZHLjTjlj7DtPuQ6VKDAoC1e3nc2KR1b3s005eaq2nHMqGluDhe7gJsITOJov4uIpGmKnVzuFQK+oR9DEfuakSUHj8kMt68mq6Uw+VxjpXv/5dJKArJAj4p7HJWA==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=amd.com; s=selector1;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=44wOblXdL5kqFLlvvvthkEjwALIAI0JsqHasc9b9oxc=;
 b=kpZwzOpDWBCCdhG7koy/77ct0fymLTstoJzXtHybmi1S90Gle6Caizs8YZSk68MXk8yJE8LubC2MsXhs7M6+DXZLiofE5H43Oxf1WzNsQhJGuzuZLlrrectM15oZ2SWZf672VKRr4Yh4xXfDWdiPP8w4e56bslEAUhCoy8ny0Ho=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=amd.com;
Received: from CH2PR12MB4133.namprd12.prod.outlook.com (2603:10b6:610:7a::13)
 by CH2PR12MB4264.namprd12.prod.outlook.com (2603:10b6:610:a4::15) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3805.24; Tue, 2 Feb
 2021 19:02:00 +0000
Received: from CH2PR12MB4133.namprd12.prod.outlook.com
 ([fe80::81f6:605c:f345:b99f]) by CH2PR12MB4133.namprd12.prod.outlook.com
 ([fe80::81f6:605c:f345:b99f%3]) with mapi id 15.20.3805.027; Tue, 2 Feb 2021
 19:02:00 +0000
From: Michael Roth <michael.roth@amd.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Andy Lutomirski <luto@amacapital.net>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        x86@kernel.org, "H . Peter Anvin" <hpa@zytor.com>,
        linux-kernel@vger.kernel.org,
        Tom Lendacky <thomas.lendacky@amd.com>
Subject: [PATCH v4 1/3] KVM: SVM: use vmsave/vmload for saving/restoring
 additional host state
Date: Tue,  2 Feb 2021 13:01:24 -0600
Message-Id: <20210202190126.2185715-2-michael.roth@amd.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20210202190126.2185715-1-michael.roth@amd.com>
References: <20210202190126.2185715-1-michael.roth@amd.com>
X-Originating-IP: [165.204.78.25]
X-ClientProxiedBy: SN6PR01CA0025.prod.exchangelabs.com (2603:10b6:805:b6::38)
 To CH2PR12MB4133.namprd12.prod.outlook.com (2603:10b6:610:7a::13)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from localhost (165.204.78.25) by
 SN6PR01CA0025.prod.exchangelabs.com (2603:10b6:805:b6::38) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3805.16 via Frontend
 Transport; Tue, 2 Feb 2021 19:02:00 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 8583233a-5021-4a9e-e748-08d8c7ad053a
X-MS-TrafficTypeDiagnostic: CH2PR12MB4264:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <CH2PR12MB42647444BE18CDC13EC2005E95B59@CH2PR12MB4264.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:10000;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 rLhHZD+TsUOau5rrSa1PxlaWbkjuYGcFCHHOl3Fc7MizXnRD0qQYgEa/JTdeydpTYIIHKNUP+U/A61JYFL+gbThRmJERg0BS944k6Aw35SoKBXfilSD0JLtj8O+MtMUYtxk7GGj+VhkwhAhuiL/QxeIOuD4EJICgNqKTkHnIjs9nINnXsxIIUxtoqDJMeOnmPoxErxUnYVu3OVsSC8XyydZNoPJGRkR/6vUTPjdtgpd4XMdiWRxt+Qt3wfPRNPNtzvxT5Cgacf25ANdzdirDMCNnspgggSlx+tJge1D0YSs81D5/z9JgInFWpR0t6+6RDiME2CGrD+XOuS5Q1B+kZJbAvzEirriz105VxJ2YM8cJSFO5kORiGzVGAbS3ypMbeTd2go+1idkDVtkw1yZ2KZONBQk8siCnitZ/bQPr3t81wjMZIHYPdzpZKz0TFKNxZqIJfHRDA61RupQr0inqUWEZb8It8ekI+k8jnQ9jGiqayNwFXVbw0c9iIJYz+FJ5EA8ES/P7aiGEJw9rSUnNdvRII2fj32aldxYiPBl0aPkHtRG5hSOJ7hU0UAr5lOg32367fpiGT5aPTeoV8jZUv2ybub9/xWcvWuaL6VqptjBuQiJshWnfwwAvZ047mtPE1UOP3UnaA5XLYfo7Dt3F+Sfh8pgGFlAx3746QblUibn4Ouh3hBpL5mm1Up05nMZzSTXQczidW/kB4DRbuXtJhb79m2iSmPt41nl9iFomxrCgBB0nKb9iDW80XT7zJ+kfWM8VYCTTPl+PJNMW4pCpY7q8nscFA3AQZUoaHnzTHz6DNoPFo/fZ9+ZqbyKMMNkCALZ1nLYilFepV9QCLJSVz5SGwKo4BZF2TtZJ55lp+f8MSAP52iwyFhYJw2+5M5hq
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:5;SRV:;IPV:NLI;SFV:SPM;H:CH2PR12MB4133.namprd12.prod.outlook.com;PTR:;CAT:OSPM;SFS:(4636009)(396003)(376002)(136003)(366004)(39860400002)(346002)(186003)(6666004)(16526019)(66476007)(66556008)(2616005)(956004)(36756003)(8936002)(44832011)(26005)(2906002)(54906003)(83380400001)(86362001)(478600001)(8676002)(6916009)(7416002)(1076003)(6486002)(52116002)(4326008)(5660300002)(66946007)(6496006)(316002)(23200700001);DIR:OUT;SFP:1501;
X-MS-Exchange-AntiSpam-MessageData: 
 gDk+oEIdTL6tkiX0EnjZ3ZrkPhWcxpOVtHAojjKjG0OjisDYPBHoksLrpF+udEowqOqmiciXOwjKe0EL5V2mi7E5kAweT4sU/0FAWMMY2j9X55PsS6ESC5dH2GooW4XilH7z/NTHAQcqIoq+T7G1bp0+aIeqfrtwW/vimQsXW3f9S2K5q9Xm1nV0fxQhtK5QDePSmYBxK450605R3QlxVi4BqtfVCzJ3xUxmssl5Ep+1sVjqS4286h57eSjUeIbboj9lrI/YRFaf7WagCuLHSPNSS4+7jm6Q5a2M2+wc9jRoPt8AfiE1e4M3U/X/ISfyG7tNUXAj6bx/2dkpLdR9g4WZDKKoYD+gjnFlJhp1KrT6Bb+eZLgX+lcNaqQc81xbj88vglcGeQGhE5jDl72TREAvU49wbv0vmWFFKvLgBxvgbWkrZjfRcV4ucd0BvqXtT5yuFwKVTJD9DlE0nWJku8znyZ/DicE+U7w+Hm0TF6YKhBGAmNzH7KGv+8KHQZD9TkUKM9GzYdW+CuRExuxjOjru/C6cE1sXxh/c3NUsE+TPQCdSS8BH2r5bprKySb1i4Yest7kqVbvNOGM/zUXAylbsZDO6TiNg0tSHiuqBxGbSnulKijGus4lBAbtcVeNrMOUfencrEwLUfgwJvxrZNfw+sqaO9gQphFae+gKddZP5gRFXQodFMc/NnHgT/OpDvLZoNiVDUFZZQs2lw6o0o/IXdNBsh8rrLM2NPE2U2Aa67jUo7io91L1hJiGi1IyPjr7/2BhvKWonwZIofAZVTtSegQvV+fb2hq8BXUsnatfnxMF3DcoiLakkjM/qoxq5Rx7pzcJNppX44Ul4WlrQS5DPEwyt9zTmDOJsw6BmdQSBbnCP+dgPefpxk334cq7RUfElccfuq9ixIkI6M3phIBnIQQrsbkV998jHIAsNiuztNE4mCtjLq9dok85JGZgKBhrbR2UdITU7o+J7FZrvz5or5d1ltNH1c3VgkhtA27Oq+zRb/LcDP4jU4bMoDiG6ng+k+36/a7Ey+Rwnp3mckRJE7TMpfX3Rb9qAvMED7HyLbUW3BUavY3oMv8Fv3DnyhGBhFskFP1qkcN7iATVlD6Xwt/qbexioZXxR3HUURrCai3+swC5l+IygyqlrQQ0yOmo1nO7RhN4/McSLDGxnzr1x0m2DTdOb+sg5mkQYw/IuViQQrABRh6nQNvNEizVVWyrFQ2Z+F6J7ysu5fGg857gNrGz8HL08RJayZbdTZGZ32VRdJ5T8bYD7BY2wExdTZIaN9cKXVyK4rCFOHxEaI9DeSN6Kf6ww6ieusuay2nJj4joxWDl7koor4lvtvVP1
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 8583233a-5021-4a9e-e748-08d8c7ad053a
X-MS-Exchange-CrossTenant-AuthSource: CH2PR12MB4133.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 02 Feb 2021 19:02:00.5185
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 KFp2xgZ0mwBk/nYegL37/MHaXIPLBWvoKpG72Iru7nOAPFNXdza4VRfVZW4LNv3RFZZ/GYnJ7Xg6ZtRtKTd0Uw==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: CH2PR12MB4264
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Using a guest workload which simply issues 'hlt' in a tight loop to
generate VMEXITs, it was observed (on a recent EPYC processor) that a
significant amount of the VMEXIT overhead measured on the host was the
result of MSR reads/writes in svm_vcpu_load/svm_vcpu_put according to
perf:

  67.49%--kvm_arch_vcpu_ioctl_run
          |
          |--23.13%--vcpu_put
          |          kvm_arch_vcpu_put
          |          |
          |          |--21.31%--native_write_msr
          |          |
          |           --1.27%--svm_set_cr4
          |
          |--16.11%--vcpu_load
          |          |
          |           --15.58%--kvm_arch_vcpu_load
          |                     |
          |                     |--13.97%--svm_set_cr4
          |                     |          |
          |                     |          |--12.64%--native_read_msr

Most of these MSRs relate to 'syscall'/'sysenter' and segment bases, and
can be saved/restored using 'vmsave'/'vmload' instructions rather than
explicit MSR reads/writes. In doing so there is a significant reduction
in the svm_vcpu_load/svm_vcpu_put overhead measured for the above
workload:

  50.92%--kvm_arch_vcpu_ioctl_run
          |
          |--19.28%--disable_nmi_singlestep
          |
          |--13.68%--vcpu_load
          |          kvm_arch_vcpu_load
          |          |
          |          |--9.19%--svm_set_cr4
          |          |          |
          |          |           --6.44%--native_read_msr
          |          |
          |           --3.55%--native_write_msr
          |
          |--6.05%--kvm_inject_nmi
          |--2.80%--kvm_sev_es_mmio_read
          |--2.19%--vcpu_put
          |          |
          |           --1.25%--kvm_arch_vcpu_put
          |                     native_write_msr

Quantifying this further, if we look at the raw cycle counts for a
normal iteration of the above workload (according to 'rdtscp'),
kvm_arch_vcpu_ioctl_run() takes ~4600 cycles from start to finish with
the current behavior. Using 'vmsave'/'vmload', this is reduced to
~2800 cycles, a savings of 39%.

While this approach doesn't seem to manifest in any noticeable
improvement for more realistic workloads like UnixBench, netperf, and
kernel builds, likely due to their exit paths generally involving IO
with comparatively high latencies, it does improve overall overhead
of KVM_RUN significantly, which may still be noticeable for certain
situations. It also simplifies some aspects of the code.

With this change, explicit save/restore is no longer needed for the
following host MSRs, since they are documented[1] as being part of the
VMCB State Save Area:

  MSR_STAR, MSR_LSTAR, MSR_CSTAR,
  MSR_SYSCALL_MASK, MSR_KERNEL_GS_BASE,
  MSR_IA32_SYSENTER_CS,
  MSR_IA32_SYSENTER_ESP,
  MSR_IA32_SYSENTER_EIP,
  MSR_FS_BASE, MSR_GS_BASE

and only the following MSR needs individual handling in
svm_vcpu_put/svm_vcpu_load:

  MSR_TSC_AUX

We could drop the host_save_user_msrs array/loop and instead handle
MSR read/write of MSR_TSC_AUX directly, but we leave that for now as
a potential follow-up.

Since 'vmsave'/'vmload' also handles the LDTR and FS/GS segment
registers (and associated hidden state)[2], some of the code
previously used to handle this is no longer needed, so we drop it
as well.

The first public release of the SVM spec[3] also documents the same
handling for the host state in question, so we make these changes
unconditionally.

Also worth noting is that we 'vmsave' to the same page that is
subsequently used by 'vmrun' to record some host additional state. This
is okay, since, in accordance with the spec[2], the additional state
written to the page by 'vmrun' does not overwrite any fields written by
'vmsave'. This has also been confirmed through testing (for the above
CPU, at least).

[1] AMD64 Architecture Programmer's Manual, Rev 3.33, Volume 2, Appendix B, Table B-2
[2] AMD64 Architecture Programmer's Manual, Rev 3.31, Volume 3, Chapter 4, VMSAVE/VMLOAD
[3] Secure Virtual Machine Architecture Reference Manual, Rev 3.01

Suggested-by: Tom Lendacky <thomas.lendacky@amd.com>
Signed-off-by: Michael Roth <michael.roth@amd.com>
---
 arch/x86/kvm/svm/svm.c     | 31 +++++--------------------------
 arch/x86/kvm/svm/svm.h     | 17 -----------------
 arch/x86/kvm/svm/svm_ops.h |  5 +++++
 3 files changed, 10 insertions(+), 43 deletions(-)

```
#### [PATCH] KVM: SVM: Treat SVM as unsupported when running as an SEV guest
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12062909
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id EA584C433DB
	for <kvm@archiver.kernel.org>; Tue,  2 Feb 2021 21:21:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B37C364F66
	for <kvm@archiver.kernel.org>; Tue,  2 Feb 2021 21:21:07 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229793AbhBBVVG (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 2 Feb 2021 16:21:06 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:59868 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229572AbhBBVVD (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 2 Feb 2021 16:21:03 -0500
Received: from mail-qk1-x74a.google.com (mail-qk1-x74a.google.com
 [IPv6:2607:f8b0:4864:20::74a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 14A3DC061573
        for <kvm@vger.kernel.org>; Tue,  2 Feb 2021 13:20:23 -0800 (PST)
Received: by mail-qk1-x74a.google.com with SMTP id t186so10704746qke.5
        for <kvm@vger.kernel.org>; Tue, 02 Feb 2021 13:20:23 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=SP8qMh2H5uKuGn56qQjTuaPHFsmbyYN2PVhXxr1Wb/c=;
        b=YVgAKVM6kkOctLgE8nCs1fKIlb2yjj7CHd7ZMzDwOLNGOg1gcc+QG4XlrVvzxeuREC
         HkE9XpZMfHkIW7M4bCKkSL6+T/I6pQxZNTkrJM5DakqOV6JzTqAy4Psv7jKepBs0oe3a
         gDFm/OJb00IflpNMMsyTFxsLIOCNRY7szyP5S6fYR3BfiGTnNErkeOIOsPzHHA2jrca5
         JSk8w+37IPlIoCohYf3ch4DQ3Ky47ODPI2Z4XOUVC+hODwpX7HnCjZp6fYslyiVovG4Y
         SeAFKRo9WIdo2FDDnBsEcQ/uEp4sNO+T9uzu2/vKM/rSrLjNKDxDCTI6lNHjZbAlsyw8
         GMhw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:reply-to:date:message-id:mime-version
         :subject:from:to:cc;
        bh=SP8qMh2H5uKuGn56qQjTuaPHFsmbyYN2PVhXxr1Wb/c=;
        b=Dw3p1NRLG7uWeW/SPDDt6MAndUTt+y8A+J+vXsavA4TA/d/MGc1dvXfpHsdVtqKKvQ
         UwLs1MPYQ0fLedQ0XhDKa7/JpsBegiF/GaTzAqLxNdfzIcNOFJIg0T/Ve1Z+NRyILC4J
         FBoMDoc+eWuquKymeJgu3S2twCjwc9N7niQDeYw0w/EAcJzMuf5oe/YZqcLmsaMJiKsL
         EVhrhyqKwg81yCYjuUlILbz8rOZV+5inndlMjakG3TzYI7QbVWLk4HpO9PIs9y93FMOa
         EAU2eLPhNiBuU4U7CL7lnA0uOtpIF1jv6qvl6HuE57p33KMlKCnFu5xpUhtY2hB5CNmc
         22mw==
X-Gm-Message-State: AOAM532rCcpvKPtcenVBa8mRsidOwtCr9+7Cy+5qZgiL82ZzApeyqho4
        zWz8pLu7fITrUMzxw5496UWrTS7kYTA=
X-Google-Smtp-Source: 
 ABdhPJzUzodN3KIBXul52n7bnjL2mGC4zihxwheFohK7KbF/xI/u+9+F9g5XC3z/JC0BgE/yM8E65dhtlMc=
Sender: "seanjc via sendgmr" <seanjc@seanjc798194.pdx.corp.google.com>
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:e1bc:da69:2e4b:ce97])
 (user=seanjc job=sendgmr) by 2002:a05:6214:403:: with SMTP id
 z3mr74190qvx.42.1612300822251; Tue, 02 Feb 2021 13:20:22 -0800 (PST)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Tue,  2 Feb 2021 13:20:17 -0800
Message-Id: <20210202212017.2486595-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.30.0.365.g02bc693789-goog
Subject: [PATCH] KVM: SVM: Treat SVM as unsupported when running as an SEV
 guest
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Dave Hansen <dave.hansen@linux.intel.com>,
        Andy Lutomirski <luto@kernel.org>,
        Peter Zijlstra <peterz@infradead.org>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Don't let KVM load when running as an SEV guest, regardless of what
CPUID says.  Memory is encrypted with a key that is not accessible to
the host (L0), thus it's impossible for L0 to emulate SVM, e.g. it'll
see garbage when reading the VMCB.

Technically, KVM could decrypt all memory that needs to be accessible to
the L0 and use shadow paging so that L0 does not need to shadow NPT, but
exposing such information to L0 largely defeats the purpose of running as
an SEV guest.  This can always be revisited if someone comes up with a
use case for running VMs inside SEV guests.

Note, VMLOAD, VMRUN, etc... will also #GP on GPAs with C-bit set, i.e. KVM
is doomed even if the SEV guest is debuggable and the hypervisor is willing
to decrypt the VMCB.  This may or may not be fixed on CPUs that have the
SVME_ADDR_CHK fix.

Cc: stable@vger.kernel.org
Signed-off-by: Sean Christopherson <seanjc@google.com>
---

FWIW, I did get nested SVM working on SEV by decrypting all structures
that are shadowed by L0, albeit with many restrictions.  So even though
there's unlikely to be a legitimate use case, I don't think KVM (as L0)
needs to be changed to disallow nSVM for SEV guests, userspace is
ultimately the one that should hide SVM from L1.

 arch/x86/kvm/svm/svm.c    | 5 +++++
 arch/x86/mm/mem_encrypt.c | 1 +
 2 files changed, 6 insertions(+)

```
#### [PATCH] KVM: SVM: Use 'unsigned long' for the physical address passed to VMSAVE
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12063065
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.2 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E1955C433E6
	for <kvm@archiver.kernel.org>; Tue,  2 Feb 2021 22:36:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AEF1464EDA
	for <kvm@archiver.kernel.org>; Tue,  2 Feb 2021 22:36:33 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S235103AbhBBWfo (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 2 Feb 2021 17:35:44 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:47582 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S235876AbhBBWfI (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 2 Feb 2021 17:35:08 -0500
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 0BC94C061788
        for <kvm@vger.kernel.org>; Tue,  2 Feb 2021 14:34:20 -0800 (PST)
Received: by mail-yb1-xb49.google.com with SMTP id q191so7637978ybg.4
        for <kvm@vger.kernel.org>; Tue, 02 Feb 2021 14:34:20 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=7LGHGvABVV/hOzEr/frM8n8zvokdVXHA8iCPP4kDUv4=;
        b=lf5FREXRqgS0lbB4idjJXbZpvN4HjC2s1M3lu3rgAs/mLwLhIl6y/k2g5pIEbI2n6r
         +XDZop1lxnku3Rlk1aF0K7L/sFMb5wSVjTpsxd8+GqrHqLWWzMxSfYIxm7X9lsT0Z+sB
         UmI/NR8IVaY/ur/OXd0g5UHgGesyFI/FcbFwAEOoSugxvCs8cSEvbNlcLhOG1FxgowCb
         oSIQ8alO9+1nzBUykFWmx6RUY4LqMP10+UFe+Em8YPGlrlfGmBVRT/tmMqZsZdy++I9G
         0WhQFI6c4NbDNRH5BAKlzeF+MB0CHlF/VZAy2x2wc7xP1Sz8v0tYLT7MZmKJvsjGoIvc
         YRFg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:reply-to:date:message-id:mime-version
         :subject:from:to:cc;
        bh=7LGHGvABVV/hOzEr/frM8n8zvokdVXHA8iCPP4kDUv4=;
        b=WC9CIwJZfby4pkbsYEzNreY3zGR9yN7grNOM7CFf0XRLoXjs8dJBl+4oi6iHqULptz
         jlnby6ZlcZ9feoHGtwAIhKg1uoNc5Jt1icEvYu00URskgpYcPu2bCXyIWLD1wOp/Zw1m
         +BYxkd7pqIDfzjxxjravuIeNFW7PCQGhTNBcekWClMBC9Vxl904H77HH+wb3tcsRQmlP
         ZujeAmR4U2oeZt48kAdc5cWrZouOGPzW8UvBwXlqnAbcI5+AuobwkyXTM62Lk5I/wt/a
         0c+/tj8K5+O+8lhkwtzi+drgf81Gh+Z/OiCepPVbmZR4X6Wu5sXNRuacCYrB2iKZACIZ
         EAfg==
X-Gm-Message-State: AOAM533acbDBv8aoFNZgM/YlbaZ79dmCw6XHy1qZcyI2Ni1A72g7lzjB
        n59wXEu+lfgrv9EqszFSC+iat5RUvPc=
X-Google-Smtp-Source: 
 ABdhPJxpO6ITfmyuFo8ObTMJgNF5wKHYFWmtXQY8xHo3eagkj9Tx2KSZR6I0YF/WkGlcza5jhZTvpHMiBvI=
Sender: "seanjc via sendgmr" <seanjc@seanjc798194.pdx.corp.google.com>
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:e1bc:da69:2e4b:ce97])
 (user=seanjc job=sendgmr) by 2002:a25:bd51:: with SMTP id
 p17mr195332ybm.274.1612305259277;
 Tue, 02 Feb 2021 14:34:19 -0800 (PST)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Tue,  2 Feb 2021 14:34:16 -0800
Message-Id: <20210202223416.2702336-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.30.0.365.g02bc693789-goog
Subject: [PATCH] KVM: SVM: Use 'unsigned long' for the physical address passed
 to VMSAVE
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Robert Hu <robert.hu@intel.com>,
        Farrah Chen <farrah.chen@intel.com>,
        Danmei Wei <danmei.wei@intel.com>,
        Tom Lendacky <Thomas.Lendacky@amd.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Take an 'unsigned long' instead of 'hpa_t' in the recently added vmsave()
helper, as loading a 64-bit GPR isn't possible in 32-bit mode.  This is
properly reflected in the SVM ISA, which explicitly states that VMSAVE,
VMLOAD, VMRUN, etc... consume rAX based on the effective address size.

Don't bother with a WARN to detect breakage on 32-bit KVM, the VMCB PA is
stored as an 'unsigned long', i.e. the bad address is long since gone.
Not to mention that a 32-bit kernel is completely hosed if alloc_page()
hands out pages in high memory.

Reported-by: kernel test robot <lkp@intel.com>
Cc: Robert Hu <robert.hu@intel.com>
Cc: Farrah Chen <farrah.chen@intel.com>
Cc: Danmei Wei <danmei.wei@intel.com>
Cc: Tom Lendacky <Thomas.Lendacky@amd.com>
Signed-off-by: Sean Christopherson <seanjc@google.com>
---
 arch/x86/kvm/svm/svm_ops.h | 7 ++++++-
 1 file changed, 6 insertions(+), 1 deletion(-)

```
#### [PATCH] KVM: x86: cleanup CR3 reserved bits checks
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 12062371
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 0E68CC433E0
	for <kvm@archiver.kernel.org>; Tue,  2 Feb 2021 17:06:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D6ABB64F87
	for <kvm@archiver.kernel.org>; Tue,  2 Feb 2021 17:06:22 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S237222AbhBBRGC (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 2 Feb 2021 12:06:02 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:42779 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S233840AbhBBREN (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 2 Feb 2021 12:04:13 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1612285368;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=9UCxeo6v7NOgmWOxRaq0ZSAmgBbuaMdBo8v8dZDVug4=;
        b=U6/WdOb5umOA6ttJvWFaM+EQ/6aE+H6a8qMqIWX8teVkY7qEbLrIYSKCdatfqrTjsR4Dht
        3SXKfDZYJClu34HldO8MUzIBvZMpNLRZyWT6t3NHYscOxz5zaFqlxjw7QRy8T9f3SMZXTN
        mSjosPkBlg6bZzxK5npMevpyQuEEmtA=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-471-vB5OzQl9PWiMRF2K2wsCIg-1; Tue, 02 Feb 2021 12:02:46 -0500
X-MC-Unique: vB5OzQl9PWiMRF2K2wsCIg-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 1BE1B192CC40;
        Tue,  2 Feb 2021 17:02:45 +0000 (UTC)
Received: from virtlab511.virt.lab.eng.bos.redhat.com
 (virtlab511.virt.lab.eng.bos.redhat.com [10.19.152.198])
        by smtp.corp.redhat.com (Postfix) with ESMTP id BDAA760C5F;
        Tue,  2 Feb 2021 17:02:44 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: seanjc@google.com
Subject: [PATCH] KVM: x86: cleanup CR3 reserved bits checks
Date: Tue,  2 Feb 2021 12:02:44 -0500
Message-Id: <20210202170244.89334-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If not in long mode, the low bits of CR3 are reserved but not enforced to
be zero, so remove those checks.  If in long mode, however, the MBZ bits
extend down to the highest physical address bit of the guest, excluding
the encryption bit.

Make the checks consistent with the above, and match them between
nested_vmcb_checks and KVM_SET_SREGS.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Sean Christopherson <seanjc@google.com> 
---
 arch/x86/kvm/svm/nested.c | 12 ++----------
 arch/x86/kvm/svm/svm.h    |  3 ---
 arch/x86/kvm/x86.c        |  2 ++
 3 files changed, 4 insertions(+), 13 deletions(-)

```
#### [PATCH] KVM: x86/mmu: Remove unused variable invalid_list
##### From: Stephen Brennan <stephen.s.brennan@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stephen Brennan <stephen.s.brennan@oracle.com>
X-Patchwork-Id: 12060283
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id BD87DC433DB
	for <kvm@archiver.kernel.org>; Tue,  2 Feb 2021 00:33:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9944A64ED7
	for <kvm@archiver.kernel.org>; Tue,  2 Feb 2021 00:33:25 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231459AbhBBAdJ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 1 Feb 2021 19:33:09 -0500
Received: from userp2130.oracle.com ([156.151.31.86]:55102 "EHLO
        userp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S231264AbhBBAdH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 1 Feb 2021 19:33:07 -0500
Received: from pps.filterd (userp2130.oracle.com [127.0.0.1])
        by userp2130.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 1120OGUb097502;
        Tue, 2 Feb 2021 00:30:51 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : content-transfer-encoding : content-type :
 mime-version; s=corp-2020-01-29;
 bh=ZD3O6UhLJAWSFXbqdeC30GFnxxsqy5F0A2XspSE2k3I=;
 b=PBia5cAmKQbTLfL02K1RqdfgADjeFbpPyPPXB+edblVO4k8uH4KbgexZd9qjwJgpTOCD
 t26wDioy/zJXbrC+Zwp08VpFF8Hk1scD4NnsgATR85J+G4ELVsTMoUqY5KforgIgi4mi
 lmBWxEq8z00CQB7gFSpSKzRmWg1iNZ3LyitbIIjKrrAAqSZP5jkf/lNW9vUmj6jVPMSo
 Hh2aesFDbkJpgRWPyU2l/f7rjaafi3Opqc6517FKc7Tl8zXQdJy5XB0DBzMYdl6i6vv3
 E7bsw85C9+oLoljjs9BzUkwhH2mmTfRdALhCIOxoPlhbAjf8rxa150FN/fuLyS/Axcdx cg==
Received: from userp3030.oracle.com (userp3030.oracle.com [156.151.31.80])
        by userp2130.oracle.com with ESMTP id 36cxvr07u7-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 02 Feb 2021 00:30:51 +0000
Received: from pps.filterd (userp3030.oracle.com [127.0.0.1])
        by userp3030.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 1120KV5P186621;
        Tue, 2 Feb 2021 00:30:51 GMT
Received: from nam10-bn7-obe.outbound.protection.outlook.com
 (mail-bn7nam10lp2109.outbound.protection.outlook.com [104.47.70.109])
        by userp3030.oracle.com with ESMTP id 36dhcvt94y-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 02 Feb 2021 00:30:51 +0000
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=lf4t45QDoB8vll5RTRng2L+O3TkPfHd9ckJcWVodwi4GawJMKYDpYZk0P1OcsROvpUty1ZbF+uiJ9cQhGrlA6GA9CyVVv+gS703oWInoicBFDuHqZp3+phPpXraVYeLVhZY8rHIAQx9KI4+03158RLMfkoeVIgQU0V9uxHkqBb3F0P6WQaKdIsfONCPEdRgOzF9cPnZaS9TbAXeRGJcHJZGFThErMCszIpNEP2GWnFDVcaXikK3Fr1W3r2x/pNoTI+L9n4uOUMGNnWlhCPR8xsltCbcMglEJH5uChlEV6O8WwewAqkVauYNZwCLSay8CwRZ41bSbDBmAURSVmPtyVQ==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=ZD3O6UhLJAWSFXbqdeC30GFnxxsqy5F0A2XspSE2k3I=;
 b=DfasdOxinepCiln9Dct2P7UCfhH8jxG2Jb1uFLu1+e0DT3i+0GhuYU+ZajCa40teQBtZ+lAS7vSMRZnMhyOC1D/rybPImxSBZP5oxEdDLthF1mib/2MhnLoAf+vGfW9gMTx27hCFIvy6/6rtFutKDUlXMnFYxoKIn9Ar3ZjseLyZyFaSJ/8N/G9sFMoeJLPDbbLT5EDyWc5UpDQrbsWyGF+uvKI8UlBXJMe0ORzoquubL1jkFjsqsL7e07cThFBri/+ZJ6bL02ClCw3J3a1BlQIvqow3RthVjGoFHtwqbB7cRuKhhVhx0tmXsMycNLVoCsaFXViyRzz84jf1REzQsA==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=oracle.com; dmarc=pass action=none header.from=oracle.com;
 dkim=pass header.d=oracle.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=oracle.onmicrosoft.com; s=selector2-oracle-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=ZD3O6UhLJAWSFXbqdeC30GFnxxsqy5F0A2XspSE2k3I=;
 b=FQiyxGGt/mSdey1cVbyrJdyugBVpA6nyKJT0SUNzOIs5GoSp53oQTA7Q0Ig17NYh843rGmx4y21BkEwpIAipXvFyEozqXffIiAnqWLLA1gxLsTSn21BzsQ1st+nC09VaFkod8yhpnZeVFLsWYNVGPSdpqkspsYUfK8/BHd1jP28=
Authentication-Results: redhat.com; dkim=none (message not signed)
 header.d=none;redhat.com; dmarc=none action=none header.from=oracle.com;
Received: from BYAPR10MB2823.namprd10.prod.outlook.com (2603:10b6:a03:87::15)
 by BYAPR10MB3080.namprd10.prod.outlook.com (2603:10b6:a03:87::13) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3805.21; Tue, 2 Feb
 2021 00:30:48 +0000
Received: from BYAPR10MB2823.namprd10.prod.outlook.com
 ([fe80::adef:30b8:ee4e:c772]) by BYAPR10MB2823.namprd10.prod.outlook.com
 ([fe80::adef:30b8:ee4e:c772%3]) with mapi id 15.20.3805.025; Tue, 2 Feb 2021
 00:30:48 +0000
From: Stephen Brennan <stephen.s.brennan@oracle.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        x86@kernel.org, "H. Peter Anvin" <hpa@zytor.com>,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: Stephen Brennan <stephen.s.brennan@oracle.com>
Subject: [PATCH] KVM: x86/mmu: Remove unused variable invalid_list
Date: Mon,  1 Feb 2021 16:30:37 -0800
Message-Id: <20210202003037.899504-1-stephen.s.brennan@oracle.com>
X-Mailer: git-send-email 2.27.0
X-Originating-IP: [2606:b400:8301:1041::13]
X-ClientProxiedBy: CH2PR07CA0038.namprd07.prod.outlook.com
 (2603:10b6:610:5b::12) To BYAPR10MB2823.namprd10.prod.outlook.com
 (2603:10b6:a03:87::15)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from localhost (2606:b400:8301:1041::13) by
 CH2PR07CA0038.namprd07.prod.outlook.com (2603:10b6:610:5b::12) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3805.16 via Frontend
 Transport; Tue, 2 Feb 2021 00:30:47 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: b5fd25a3-8ada-4c5f-ef53-08d8c711c95b
X-MS-TrafficTypeDiagnostic: BYAPR10MB3080:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <BYAPR10MB30808A3A30F038D70A9AC3EADBB59@BYAPR10MB3080.namprd10.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:270;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 xA+BF3XVoVWabkvzc4KdKX/6hwYg5mUtYZb6V9lr/skHEa6gCpvjyrNMYlbrrGiqPnCdTFyoh0bPq3fg6pSkASSgK5Vfrt+Iq5zSvHuAtIZC/UWvlgFJrmNJq8MiQns8fL26b7fFY7V1FST935c+3Q9k6M6DQC5xooB4PEEqsOJTDqSHzq8d1u4CaBrZ+TRjufYs+LuE0EYSXvPYMqPA2fijZyvew0aMZ2Ie0Y+lr2MehZZF1IdqdwX5gGVI5L+8jAxcGlqlemjLfAi7/HLwvPEJH05X7YaXPALfpNvM5XBAvdEzyoCszIssp6qNPEC9v1oAstCs/YM42OlyC5O2wfFdEQT8r6TMOg5j/aeBHT7j9znmE+Ylj4D6zgWnvU/H7yLLJyvWNs++efuc0IURg9vAcpENas64MMTOPC+MFxoVpowv9iecaD5QSQaJlSdsY3TIb6K2z0yzbquxHOK4u0zy7UgBg2/DiC1P+VhhUJmSxcequD9HmeUblbgzvmR0DZXg93PpEg74mGHpPgRj2iqqmuMitxPENDUVOHDy9AImk95XlqSz4A8oGfSglgKKAu3+vYkqNwtBey0b5zwP6pSsMS9xlFHs7taxPPkMQBXPPgXKbqWHq/2u7tSBhRgLDSeUhG4ag74o6DbelGKtI3qjUtA7tK7wsQ84z6KDbi6PvwphGwjZJW+dJ2VNMJebI+dadhBP6kcwmMM9Rs3SRPYhOz7SzMIZcI3d9w4yq+yqVF3oaYrGu5cjqTXFOL8Lx+mRc5YJsWQM0NWEcG62x/OWMh0Uc3ohE8AIiU+0+nW5YXBQx0ICz98qUY73QzbN3UlZ6neisLuk1ozBuWrwowC+nL8YVf21DnwXrTWx9wOdPLLnnILzdeQVmHNozGN9ElAVJuDX2J2u11sdsf0q0w==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:5;SRV:;IPV:NLI;SFV:SPM;H:BYAPR10MB2823.namprd10.prod.outlook.com;PTR:;CAT:OSPM;SFS:(376002)(39860400002)(136003)(396003)(366004)(346002)(110136005)(478600001)(52116002)(83380400001)(8936002)(16526019)(186003)(5660300002)(86362001)(6496006)(66946007)(316002)(6666004)(7416002)(1076003)(2616005)(4744005)(66476007)(66556008)(36756003)(921005)(2906002)(8676002)(4326008)(6486002)(103116003)(107886003)(23200700001);DIR:OUT;SFP:1501;
X-MS-Exchange-AntiSpam-MessageData: 
 7uwqWfKuaYGi6xC0qs2YTsFsiHASWmMSFs1V9AeOxZHgA3dr78aEdFL9P58nRHAds16noYtDm0giTnHQuRfausKFB52zxpSP1UI9BYqWTYIpY0jjv3wjZ8T6ZVWWDKXLtDdqyEcX1E2u3/3+OkQLNhT1Fl1R64XNESl7YG0TexnYRbel73hb6IAdUH4ulicyfm7BbtDyvy0314CgBtt4IaIrrk22gc/Cs9ymC282Zu5OPwILqP1DGVqi3gSGfXFxiyC++SQO5OZbCWFvgRYGMShvqzATPnoCCDvQK3OWAw3jUrKFjzHYli7375uUVIeBOmUmFxCvWjUaJnq+jyOiHDJNseSD1FoNNMXqHvKHgRdq9ljASx6ddThysdQ/Xi2mZADrQj2AWlrpuVf7UNxXoL4n0yfD/yWhUHjyd4XhWUWkbIN18luKEYHKdXztRLeMSaztz5VWRiADVn7LKyNjTdqskUUnUmgcP0s7IeuO9h14Z1LHIaB12ZXjY0eV4awphKpNdjGkjef5j0WhToKKL1SkBP2iXqw9XRrPMu+ZhIeEzLnN0ncPjHpl2eNq2tZd4+CkN7wZTXyPOYJMI0CBiKN4vb9u74h1WXgNgR7kIPdKkQ6/Xsv3z5px/Z098WOuzaQmnBYqpEzNjjzrIt1xatel2dMUkFbur6Gz0waYa886/QoZX+ZyoEC8GMn9a2hVoE3MCtDW3u60dOQB6gsPJ9+ELKODlixgMIB5S9aAY0GziPrNzootX4LjP9moLnhtFVr3i51OUHxXe9xw/GIAmk6vh9yP6EIRCKp/8i0DEBFKNNzYVbuVNbjTfFvpwBMcqRfktjxt2QboiqE5NhUZCRJlcW5uW4Uyy7Aw8qBYj+Gy3LvhdQvaxWZK3gfC+T9IQ9jeS33+eGGN5g2IgVDMnPvwjLdpRSUOgWH+/5RcdeittvYew6wW2XVGQW8HHohV4l0wxK3cKqMEVdlo8mMIEqMM9qpyDTOCejh2EAxEe4a9+fAKAwvh2xOGJZZoXj1rEOysEBkWn2FuuNDOlW4TP9t6GzH6JWzvDC/VjDhZC1R9rU2XG63uLN2IwCGXbGfUvPFGiB+CW9TZSxDAZd0pww==
X-OriginatorOrg: oracle.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 b5fd25a3-8ada-4c5f-ef53-08d8c711c95b
X-MS-Exchange-CrossTenant-AuthSource: BYAPR10MB2823.namprd10.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 02 Feb 2021 00:30:48.1341
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 4e2c6054-71cb-48f1-bd6c-3a9705aca71b
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 tQzYMFXyHn/XxK2nMYCdoHPmJZDTJA8VbEs4Z4QBh0OlOSZyjvLpvrNaHJquysrUR5OKV6taJ5OpGwE+g/Ho8OaGZkMlOUI9kThsCykSLmw=
X-MS-Exchange-Transport-CrossTenantHeadersStamped: BYAPR10MB3080
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9882
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 mlxscore=0
 mlxlogscore=999 phishscore=0
 spamscore=0 suspectscore=0 malwarescore=0 adultscore=0 bulkscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2102020001
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9882
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 malwarescore=0
 mlxlogscore=999
 mlxscore=0 priorityscore=1501 spamscore=0 impostorscore=0 clxscore=1011
 suspectscore=0 lowpriorityscore=0 phishscore=0 adultscore=0 bulkscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2102020001
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Since commit ebdb292dac79 ("KVM: x86/mmu: Batch zap MMU pages when
shrinking the slab"), invalid_list is no longer used in
mmu_shrink_scan(). Remove it.

Signed-off-by: Stephen Brennan <stephen.s.brennan@oracle.com>
---
 arch/x86/kvm/mmu/mmu.c | 1 -
 1 file changed, 1 deletion(-)

```
#### [PATCH] KVM: x86: Update emulator context mode if SYSENTER xfers to 64-bit mode
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12062331
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.2 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D183EC433E6
	for <kvm@archiver.kernel.org>; Tue,  2 Feb 2021 16:59:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 87DEE64F84
	for <kvm@archiver.kernel.org>; Tue,  2 Feb 2021 16:59:04 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S237065AbhBBQ6u (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 2 Feb 2021 11:58:50 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:58506 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S236856AbhBBQ4F (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 2 Feb 2021 11:56:05 -0500
Received: from mail-qv1-xf49.google.com (mail-qv1-xf49.google.com
 [IPv6:2607:f8b0:4864:20::f49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 9F6F5C061573
        for <kvm@vger.kernel.org>; Tue,  2 Feb 2021 08:55:50 -0800 (PST)
Received: by mail-qv1-xf49.google.com with SMTP id d8so15384272qvs.1
        for <kvm@vger.kernel.org>; Tue, 02 Feb 2021 08:55:50 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=4vQ54utvl5pYCDc2RGTnD5j/mRhLCg57OZJNdDMaGn4=;
        b=T0Z94yO1HKcNcauNpnGQV5NoiEPiLhWX96qMGEYfVm8iVuHq3WK0T3f48qxJmcP/L0
         MwxkiWpkpJeDBnPwg5tv2PaZ/LlFqABU9ikuqKHO6ZpJZ1dABjxSvbXfpvBwiY098jKA
         CNgR7EmkK/37q4cQxSJ/Wzz8piqqe6W5zPB2LfP3+00EisR/SeN9et5mgJnEY8jhMstA
         B6k0pMdDcmaJTtK1pHBQcle76Kvux6qaxNgGuqHtBG/rjy1/n7tu67JKcXlVVU88ukJQ
         9X5fhCz2DR2Bk05KxHXzM91nASnHsBSFGRrT76s8M27iZzfK+zXxTuBrWVilTqmbsYK+
         Is6g==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:reply-to:date:message-id:mime-version
         :subject:from:to:cc;
        bh=4vQ54utvl5pYCDc2RGTnD5j/mRhLCg57OZJNdDMaGn4=;
        b=isAYUJqmI2vThM/exOr8rQx0GPptPWzsSa4hqI+CxNzpaWEhu0XLiz7oBIM0j4ZrIM
         3f3TCfTwPZwMp7m965bT9ZOE8SWKSnyNz6SJsVNG68stwQUsfjVlW+CrXeBhmZloVDtN
         Wh7h/3uuvO5XoHthahcDCYu8pMmLneL11DN9auxD8viyUsHAf3lqcDRWhfpY/9gpREhf
         4JZmyldn8wGC8QpZUhBeRHK4xC/MwdzN/785ogxUr7VFU1YcHUe10LmeAc+qFluBeUMi
         6qtkqyiweI3hxsZE8HXLtD342VaSnzgJ8mhNkdyeI+QzN176jl3GN9U2DA7AO9gz+AXs
         U1HQ==
X-Gm-Message-State: AOAM530W+YENMbvxMkXNILuh3KsNIlnoyQND7B3dw8mdUX7Lj101wfiH
        C8+K+1EMoCRe4DXf0NuYtQN/4Tvk+jI=
X-Google-Smtp-Source: 
 ABdhPJxkq5VoLdV5TO59a0Enr0ROoksiV8FPHe+Pg9IjpRVfG1jvvaeGXaLW05XydcJXmkuiCs+SgAY6tpo=
Sender: "seanjc via sendgmr" <seanjc@seanjc798194.pdx.corp.google.com>
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:e1bc:da69:2e4b:ce97])
 (user=seanjc job=sendgmr) by 2002:ad4:4cd0:: with SMTP id
 i16mr21054987qvz.49.1612284949841;
 Tue, 02 Feb 2021 08:55:49 -0800 (PST)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Tue,  2 Feb 2021 08:55:46 -0800
Message-Id: <20210202165546.2390296-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.30.0.365.g02bc693789-goog
Subject: [PATCH] KVM: x86: Update emulator context mode if SYSENTER xfers to
 64-bit mode
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Jonny Barker <jonny@jonnybarker.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Set the emulator context to PROT64 if SYSENTER transitions from 32-bit
userspace (compat mode) to a 64-bit kernel, otherwise the RIP update at
the end of x86_emulate_insn() will incorrectly truncate the new RIP.

Note, this bug is mostly limited to running an Intel virtual CPU model on
an AMD physical CPU, as other combinations of virtual and physical CPUs
do not trigger full emulation.  On Intel CPUs, SYSENTER in compatibility
mode is legal, and unconditionally transitions to 64-bit mode.  On AMD
CPUs, SYSENTER is illegal in compatibility mode and #UDs.  If the vCPU is
AMD, KVM injects a #UD on SYSENTER in compat mode.  If the pCPU is Intel,
SYSENTER will execute natively and not trigger #UD->VM-Exit (ignoring
guest TLB shenanigans).

Fixes: fede8076aab4 ("KVM: x86: handle wrap around 32-bit address space")
Cc: stable@vger.kernel.org
Signed-off-by: Jonny Barker <jonny@jonnybarker.com>
[sean: wrote changelog]
Signed-off-by: Sean Christopherson <seanjc@google.com>
---
 arch/x86/kvm/emulate.c | 2 ++
 1 file changed, 2 insertions(+)

```
#### [PATCH] mailbox: arm_mhuv2: make remove callback return void
##### From: Uwe =?utf-8?q?Kleine-K=C3=B6nig?= <u.kleine-koenig@pengutronix.de>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Uwe_Kleine-K=C3=B6nig?=
 <u.kleine-koenig@pengutronix.de>
X-Patchwork-Id: 12062787
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 5F98FC433E6
	for <kvm@archiver.kernel.org>; Tue,  2 Feb 2021 19:45:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2BF3164E56
	for <kvm@archiver.kernel.org>; Tue,  2 Feb 2021 19:45:20 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S240008AbhBBTpH (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 2 Feb 2021 14:45:07 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:39168 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S239833AbhBBTo7 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 2 Feb 2021 14:44:59 -0500
Received: from metis.ext.pengutronix.de (metis.ext.pengutronix.de
 [IPv6:2001:67c:670:201:290:27ff:fe1d:cc33])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id C72DEC061788
        for <kvm@vger.kernel.org>; Tue,  2 Feb 2021 11:44:18 -0800 (PST)
Received: from ptx.hi.pengutronix.de ([2001:67c:670:100:1d::c0])
        by metis.ext.pengutronix.de with esmtps
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <ukl@pengutronix.de>)
        id 1l71a4-0002fO-D0; Tue, 02 Feb 2021 20:43:20 +0100
Received: from ukl by ptx.hi.pengutronix.de with local (Exim 4.92)
        (envelope-from <ukl@pengutronix.de>)
        id 1l71Zv-0004SH-BD; Tue, 02 Feb 2021 20:43:11 +0100
Date: Tue, 2 Feb 2021 20:43:08 +0100
From: Uwe =?utf-8?q?Kleine-K=C3=B6nig?= <u.kleine-koenig@pengutronix.de>
To: Russell King <linux+pull@armlinux.org.uk>,
        Mathieu Poirier <mathieu.poirier@linaro.org>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Alexander Shishkin <alexander.shishkin@linux.intel.com>,
        Greg Kroah-Hartman <gregkh@linuxfoundation.org>,
        Viresh Kumar <viresh.kumar@linaro.org>,
        Tushar Khandelwal <Tushar.Khandelwal@arm.com>,
        Jassi Brar <jassisinghbrar@gmail.com>
Cc: linux-fbdev@vger.kernel.org, Cornelia Huck <cohuck@redhat.com>,
 kvm@vger.kernel.org, David Airlie <airlied@linux.ie>,
 Linus Walleij <linus.walleij@linaro.org>, alsa-devel@alsa-project.org,
 dri-devel@lists.freedesktop.org, Jaroslav Kysela <perex@perex.cz>,
 Eric Anholt <eric@anholt.net>,
 Uwe =?utf-8?q?Kleine-K=C3=B6nig?=  <u.kleine-koenig.org@pengutronix.de>,
 linux-i2c@vger.kernel.org, Jiri Slaby <jirislaby@kernel.org>,
 linux-stm32@st-md-mailman.stormreply.com,
 Alexandre Torgue <alexandre.torgue@st.com>, linux-rtc@vger.kernel.org,
 Herbert Xu <herbert@gondor.apana.org.au>, Takashi Iwai <tiwai@suse.com>,
 Krzysztof Kozlowski <krzk@kernel.org>,
 Alexandre Belloni <alexandre.belloni@bootlin.com>,
 linux-serial@vger.kernel.org, linux-input@vger.kernel.org,
 Ulf Hansson <ulf.hansson@linaro.org>, Guenter Roeck <linux@roeck-us.net>,
 Mike Leach <mike.leach@linaro.org>, linux-watchdog@vger.kernel.org,
 Arnd Bergmann <arnd@arndb.de>, Alessandro Zummo <a.zummo@towertech.it>,
 coresight@lists.linaro.org, Vladimir Zapolskiy <vz@mleia.com>,
 Eric Auger <eric.auger@redhat.com>,
 Alex Williamson <alex.williamson@redhat.com>,
 Mark Brown <broonie@kernel.org>, Matt Mackall <mpm@selenic.com>,
 Daniel Vetter <daniel@ffwll.ch>, Dan Williams <dan.j.williams@intel.com>,
 Wim Van Sebroeck <wim@linux-watchdog.org>,
 linux-arm-kernel@lists.infradead.org,
 Maxime Coquelin <mcoquelin.stm32@gmail.com>,
 Dmitry Torokhov <dmitry.torokhov@gmail.com>, linux-mmc@vger.kernel.org,
 linux-kernel@vger.kernel.org, linux-spi@vger.kernel.org,
 Vinod Koul <vkoul@kernel.org>, linux-crypto@vger.kernel.org,
 kernel@pengutronix.de, Leo Yan <leo.yan@linaro.org>,
 dmaengine@vger.kernel.org
Subject: [PATCH] mailbox: arm_mhuv2: make remove callback return void
Message-ID: <20210202194308.jm66vblqjwr5wo6v@pengutronix.de>
References: <20210126165835.687514-1-u.kleine-koenig@pengutronix.de>
 <20210202135350.36nj3dmcoq3t7gcf@pengutronix.de>
MIME-Version: 1.0
Content-Disposition: inline
In-Reply-To: <20210202135350.36nj3dmcoq3t7gcf@pengutronix.de>
X-SA-Exim-Connect-IP: 2001:67c:670:100:1d::c0
X-SA-Exim-Mail-From: ukl@pengutronix.de
X-SA-Exim-Scanned: No (on metis.ext.pengutronix.de);
 SAEximRunCond expanded to false
X-PTX-Original-Recipient: kvm@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

My build tests failed to catch that amba driver that would have needed
adaption in commit 3fd269e74f2f ("amba: Make the remove callback return
void"). Change the remove function to make the driver build again.

Reported-by: kernel test robot <lkp@intel.com>
Fixes: 3fd269e74f2f ("amba: Make the remove callback return void")
Signed-off-by: Uwe Kleine-König <u.kleine-koenig@pengutronix.de>
---
Hello,

I guess I missed that driver during rebase as it was only introduced in
the last merge window. Sorry for that.

I'm unsure what is the right thing to do now. Should I redo the pull
request (with this patch squashed into 3fd269e74f2f)? Or do we just
apply this patch on top?

FTR, the test robot report is at https://lore.kernel.org/r/202102030343.D9j1wukx-lkp@intel.com

Best regards
Uwe

 drivers/mailbox/arm_mhuv2.c | 4 +---
 1 file changed, 1 insertion(+), 3 deletions(-)

```
#### [PATCH v2 1/2] s390/kvm: extend kvm_s390_shadow_fault to return entry pointer
##### From: Claudio Imbrenda <imbrenda@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Claudio Imbrenda <imbrenda@linux.ibm.com>
X-Patchwork-Id: 12062497
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id F36D3C433E6
	for <kvm@archiver.kernel.org>; Tue,  2 Feb 2021 18:05:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C92AB64F97
	for <kvm@archiver.kernel.org>; Tue,  2 Feb 2021 18:05:49 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S238228AbhBBSFk (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 2 Feb 2021 13:05:40 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:40296 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S237969AbhBBSBR (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 2 Feb 2021 13:01:17 -0500
Received: from pps.filterd (m0098410.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 112HVsq7128781;
        Tue, 2 Feb 2021 13:00:35 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=6eYRpj6gXCEngng6QMC0olHv2Awkx5YS4LdkWIcESyQ=;
 b=hg22eWiTkPiqAUIcmeTB/acAQ7RZrS7h6MkRMdFFsTNWO0583lO0S3Bd2Ic1hZU3Gdkv
 YV1EvuS9KGFqlaqWSR65nZlHyzNC2dqEXEcrcTeOutOJdjTdLF14glaRQkzUahC/+BU0
 CxnXnlnzeD2WNoySf+cNBUSR9H4bzKp4luDWXEXry0JpTLKAqDqcGd54+pRJ4AEYMRaO
 eI4zY/x2DRR/j8pPW02ht8FDYNX5p+6qkraCe9KRCrt3g5q13vUqgNjG2sagdIizpeIc
 ERmEa08LA8HaSMXozYwYhJhQaXmI3PJ1ylM3IRumGPj7hc0Oi0Nl3+4lcUufgyo3ehKm GQ==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 36fb5f8xkp-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 02 Feb 2021 13:00:35 -0500
Received: from m0098410.ppops.net (m0098410.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 112HW5mQ129935;
        Tue, 2 Feb 2021 13:00:35 -0500
Received: from ppma06ams.nl.ibm.com (66.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.102])
        by mx0a-001b2d01.pphosted.com with ESMTP id 36fb5f8xjb-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 02 Feb 2021 13:00:35 -0500
Received: from pps.filterd (ppma06ams.nl.ibm.com [127.0.0.1])
        by ppma06ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 112Hqivb018502;
        Tue, 2 Feb 2021 18:00:32 GMT
Received: from b06avi18878370.portsmouth.uk.ibm.com
 (b06avi18878370.portsmouth.uk.ibm.com [9.149.26.194])
        by ppma06ams.nl.ibm.com with ESMTP id 36evvf0rde-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 02 Feb 2021 18:00:32 +0000
Received: from d06av26.portsmouth.uk.ibm.com (d06av26.portsmouth.uk.ibm.com
 [9.149.105.62])
        by b06avi18878370.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 112I0LYg32047614
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 2 Feb 2021 18:00:21 GMT
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id D06C8AE053;
        Tue,  2 Feb 2021 18:00:29 +0000 (GMT)
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 73114AE05A;
        Tue,  2 Feb 2021 18:00:29 +0000 (GMT)
Received: from ibm-vm.ibmuc.com (unknown [9.145.15.83])
        by d06av26.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue,  2 Feb 2021 18:00:29 +0000 (GMT)
From: Claudio Imbrenda <imbrenda@linux.ibm.com>
To: linux-kernel@vger.kernel.org
Cc: borntraeger@de.ibm.com, frankja@linux.ibm.com, david@redhat.com,
        kvm@vger.kernel.org, linux-s390@vger.kernel.org,
        stable@vger.kernel.org
Subject: [PATCH v2 1/2] s390/kvm: extend kvm_s390_shadow_fault to return entry
 pointer
Date: Tue,  2 Feb 2021 19:00:27 +0100
Message-Id: <20210202180028.876888-2-imbrenda@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20210202180028.876888-1-imbrenda@linux.ibm.com>
References: <20210202180028.876888-1-imbrenda@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.737
 definitions=2021-02-02_08:2021-02-02,2021-02-02 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 bulkscore=0 clxscore=1011
 impostorscore=0 suspectscore=0 priorityscore=1501 lowpriorityscore=0
 phishscore=0 mlxscore=0 mlxlogscore=999 spamscore=0 adultscore=0
 malwarescore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2102020112
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Extend kvm_s390_shadow_fault to return the pointer to the valid leaf
DAT table entry, or to the invalid entry.

Also return some flags in the lower bits of the address:
DAT_PROT: indicates that DAT protection applies because of the
          protection bit in the segment (or, if EDAT, region) tables
NOT_PTE: indicates that the address of the DAT table entry returned
         does not refer to a PTE, but to a segment or region table.

Signed-off-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
Cc: stable@vger.kernel.org
---
 arch/s390/kvm/gaccess.c | 26 ++++++++++++++++++++++----
 arch/s390/kvm/gaccess.h |  5 ++++-
 arch/s390/kvm/vsie.c    |  8 ++++----
 3 files changed, 30 insertions(+), 9 deletions(-)

```
#### [PATCH 1/3] KVM: x86: move kvm_inject_gp up from kvm_set_xcr to callers
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 12062327
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 1C04CC433DB
	for <kvm@archiver.kernel.org>; Tue,  2 Feb 2021 16:57:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BDF4564F84
	for <kvm@archiver.kernel.org>; Tue,  2 Feb 2021 16:57:53 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S236964AbhBBQ5Z (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 2 Feb 2021 11:57:25 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:57647 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S236851AbhBBQxL (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 2 Feb 2021 11:53:11 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1612284705;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=WcL4iP7hBp43qywJjKYyk0ZVEk2naCJmHXvEkF498tQ=;
        b=fs53r/KRWAm4OyFV4xBxWF/ackzENi0ohf7onVla16i7KfRVkcuWC5vuLz4cIsiAiJ110p
        zyvO/tb+w5p5zELOJhMvUbz7ig+zorvkUV3I7Ms2t/l1GR3zWcpOYd1XlRwMU981lh6E6n
        KLSwFRSSa6bG2OWlnht1YLEpfAHS4do=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-520-t03N4MQ0NRCoqtyRnto8nw-1; Tue, 02 Feb 2021 11:51:43 -0500
X-MC-Unique: t03N4MQ0NRCoqtyRnto8nw-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id A5902195D56B;
        Tue,  2 Feb 2021 16:51:42 +0000 (UTC)
Received: from virtlab511.virt.lab.eng.bos.redhat.com
 (virtlab511.virt.lab.eng.bos.redhat.com [10.19.152.198])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 52E6C60862;
        Tue,  2 Feb 2021 16:51:42 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: seanjc@google.com
Subject: [PATCH 1/3] KVM: x86: move kvm_inject_gp up from kvm_set_xcr to
 callers
Date: Tue,  2 Feb 2021 11:51:39 -0500
Message-Id: <20210202165141.88275-2-pbonzini@redhat.com>
In-Reply-To: <20210202165141.88275-1-pbonzini@redhat.com>
References: <20210202165141.88275-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Push the injection of #GP up to the callers, so that they can just use
kvm_complete_insn_gp.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/svm/svm.c |  7 ++-----
 arch/x86/kvm/vmx/vmx.c |  5 ++---
 arch/x86/kvm/x86.c     | 10 ++++------
 3 files changed, 8 insertions(+), 14 deletions(-)

```
#### [PATCH v2] KVM: Stop using deprecated jump label APIs
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 12062035
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 1C384C433E0
	for <kvm@archiver.kernel.org>; Tue,  2 Feb 2021 15:23:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E637C64E40
	for <kvm@archiver.kernel.org>; Tue,  2 Feb 2021 15:23:09 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S235374AbhBBPXE (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 2 Feb 2021 10:23:04 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:54522 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S235487AbhBBPU6 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 2 Feb 2021 10:20:58 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1612279171;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=g76jh33f4NR+DjXTaiYSmk+NWUD/OnphJvhWM605zNI=;
        b=YdVqbDRj2Y9bpPqlFHxe8rahfPhjUIBFkZIZw0v4bnhKlzzRrBrtbTwJzHh+dLEemtAuCF
        sAn7EWFiJje/J8mdS4z747uL91LZLsu8w/6xP2gm+Eu0CBFUqJP4OrK2+X0Kzc+NMnXXc4
        cBUNWIssjDmgvR46B34Vp5D89anqFY4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-69-YxK_xyFPOwO2BUcWfF-wSw-1; Tue, 02 Feb 2021 10:19:29 -0500
X-MC-Unique: YxK_xyFPOwO2BUcWfF-wSw-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id C7B3D1020C20;
        Tue,  2 Feb 2021 15:19:27 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 65D6719EF1;
        Tue,  2 Feb 2021 15:19:27 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Cun Li <cun.jia.li@gmail.com>
Subject: [PATCH v2] KVM: Stop using deprecated jump label APIs
Date: Tue,  2 Feb 2021 10:19:26 -0500
Message-Id: <20210202151926.214916-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Cun Li <cun.jia.li@gmail.com>

The use of 'struct static_key' and 'static_key_false' is
deprecated. Use the new API.

Signed-off-by: Cun Li <cun.jia.li@gmail.com>
Message-Id: <20210111152435.50275-1-cun.jia.li@gmail.com>
[Make it compile.  While at it, rename kvm_no_apic_vcpu to
 kvm_has_noapic_vcpu; the former reads too much like "true if
 no vCPU has an APIC". - Paolo]
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/lapic.c         | 25 +++++++++----------------
 arch/x86/kvm/lapic.h         | 13 ++++++-------
 arch/x86/kvm/mmu/mmu_audit.c |  8 ++++----
 arch/x86/kvm/x86.c           |  9 ++++-----
 4 files changed, 23 insertions(+), 32 deletions(-)

```
