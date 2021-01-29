#### [GIT PULL] KVM/arm64 fixes for 5.11, take #3
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 12054331
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-22.0 required=3.0 tests=BAYES_00,INCLUDES_PATCH,
	INCLUDES_PULL_REQUEST,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 2B132C433DB
	for <kvm@archiver.kernel.org>; Thu, 28 Jan 2021 18:01:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DC9D764E1C
	for <kvm@archiver.kernel.org>; Thu, 28 Jan 2021 18:01:10 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231175AbhA1SAl (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 28 Jan 2021 13:00:41 -0500
Received: from mail.kernel.org ([198.145.29.99]:34086 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S231327AbhA1R7X (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 28 Jan 2021 12:59:23 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 2C4C464E0E;
        Thu, 28 Jan 2021 17:58:43 +0000 (UTC)
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1l5BZ2-00AfSI-Va; Thu, 28 Jan 2021 17:58:41 +0000
From: Marc Zyngier <maz@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Andrew Scull <ascull@google.com>,
        David Brazdil <dbrazdil@google.com>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org, kernel-team@android.com
Subject: [GIT PULL] KVM/arm64 fixes for 5.11, take #3
Date: Thu, 28 Jan 2021 17:58:30 +0000
Message-Id: <20210128175830.3035035-1-maz@kernel.org>
X-Mailer: git-send-email 2.29.2
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: pbonzini@redhat.com, ascull@google.com,
 dbrazdil@google.com, james.morse@arm.com, julien.thierry.kdev@gmail.com,
 suzuki.poulose@arm.com, linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Paolo,

Hopefully this is the last KVM/arm64 fix for 5.11, addressing a
register corruption at boot time, which got unnoticed until Andrew had
a closer look at it. Thankfully, this is only in 5.11, so it was
caught in time.

Please pull,

	M.

The following changes since commit 139bc8a6146d92822c866cf2fd410159c56b3648:

  KVM: Forbid the use of tagged userspace addresses for memslots (2021-01-21 14:17:36 +0000)

are available in the Git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/kvmarm/kvmarm.git tags/kvmarm-fixes-5.11-3

for you to fetch changes up to e500b805c39daff2670494fff94909d7e3d094d9:

  KVM: arm64: Don't clobber x4 in __do_hyp_init (2021-01-25 15:50:35 +0000)

----------------------------------------------------------------
KVM/arm64 fixes for 5.11, take #3

- Avoid clobbering extra registers on initialisation

----------------------------------------------------------------
Andrew Scull (1):
      KVM: arm64: Don't clobber x4 in __do_hyp_init

 arch/arm64/kvm/hyp/nvhe/hyp-init.S | 20 +++++++++++---------
 1 file changed, 11 insertions(+), 9 deletions(-)
```
#### [RFC v2 2/4] KVM: x86: add support for ioregionfd signal handling
##### From: Elena Afanasova <eafanasova@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Elena Afanasova <eafanasova@gmail.com>
X-Patchwork-Id: 12054405
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 69460C433E0
	for <kvm@archiver.kernel.org>; Thu, 28 Jan 2021 18:48:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 09DB564E21
	for <kvm@archiver.kernel.org>; Thu, 28 Jan 2021 18:48:56 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232237AbhA1Srm (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 28 Jan 2021 13:47:42 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:41662 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S232452AbhA1Spe (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 28 Jan 2021 13:45:34 -0500
Received: from mail-lf1-x130.google.com (mail-lf1-x130.google.com
 [IPv6:2a00:1450:4864:20::130])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id B5A58C061756
        for <kvm@vger.kernel.org>; Thu, 28 Jan 2021 10:44:52 -0800 (PST)
Received: by mail-lf1-x130.google.com with SMTP id b2so9007790lfq.0
        for <kvm@vger.kernel.org>; Thu, 28 Jan 2021 10:44:52 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=XdnpkSHfGb6mFvfnchwjTHIUgI5G73VkKBRO+kD1NYU=;
        b=t83zFc/cQ4US3B7sl6V77Ae0jilyBuqaUBPtk5sx/71e503HU6U+y0kNq9KpvKKK5P
         vOIXVsuLxSZjoICWXCNCALPRSW1lYw3L02+r2Xd4MC7nl2u+mrmRdX1eyJp/qt0pFKwf
         fRE++57itKMhDKMvJDZm9gKZ4w4ZbjGHR4OyRfj34j5japOlq77oibRx0pHzllVq6eV0
         5uz7HuCiXe2mL9nVqIefWlGuispf7Zv0+wzp7+m9xxXZ7RrJl8jR9zO9KRruVc1xh5a4
         G67GWxeL6aOzJsMY8P8yFt9jWEugOoDCeZcWr6BTasRAMlvfcwpCKkmDXLzKLvEoKZjE
         b3Dw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=XdnpkSHfGb6mFvfnchwjTHIUgI5G73VkKBRO+kD1NYU=;
        b=AI9BVQmcaszhpvyQxjse43qggZCJ5LSDVaUs82F4i2SvM6mGB+bxT3RB5NzqlfDUx3
         +V690KjPQQ8Q3NYaoQasa+XSasq0v2cExjf8QKmFvCA5SXc05XjKlFM9jSCuxBXhZncp
         15icDX1KWo7o5PG3AyI5NJ4XXJnyRCGsYj12Oby7qEhOAhhp43A5lWhBoJnzDRumRmSb
         dNnlOCFkW56eDLwKYbpZ7T3HfWoAyED6ZjlY1AtBmCf+oS0YbNkDhxCJvfr07YIDLdVO
         BAKl/Up+mbM4iMHV2UJJ8Jb5yDpkymumBgvFYtDNW69xc0VrWqbcsBkVdz+upqJnROpk
         oKKA==
X-Gm-Message-State: AOAM533Ul4fYyjC2muZsiymClHs3p1adiRTIp76zKGs+cjJ7g+/aQ8lx
        TC/0kU0wCS9yLQuNtfHIvnxL0rpwbTw/4bd5
X-Google-Smtp-Source: 
 ABdhPJyl5F6f4G4d7n9knjiX/VYmdAwLQjvW24Oy9/oJ8aR1ZgQwzd+3bEGX5bOXrn51nEjTQgtxPw==
X-Received: by 2002:ac2:5462:: with SMTP id e2mr194719lfn.655.1611859490045;
        Thu, 28 Jan 2021 10:44:50 -0800 (PST)
Received: from localhost.localdomain (37-145-186-126.broadband.corbina.ru.
 [37.145.186.126])
        by smtp.gmail.com with ESMTPSA id
 k8sm1750508lfg.41.2021.01.28.10.44.49
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 28 Jan 2021 10:44:49 -0800 (PST)
From: Elena Afanasova <eafanasova@gmail.com>
To: kvm@vger.kernel.org
Cc: stefanha@redhat.com, jag.raman@oracle.com,
        elena.ufimtseva@oracle.com, Elena Afanasova <eafanasova@gmail.com>
Subject: [RFC v2 2/4] KVM: x86: add support for ioregionfd signal handling
Date: Thu, 28 Jan 2021 21:32:21 +0300
Message-Id: 
 <aa049c6e5bade3565c5ffa820bbbb67bd5d1bf4b.1611850291.git.eafanasova@gmail.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <cover.1611850290.git.eafanasova@gmail.com>
References: <cover.1611850290.git.eafanasova@gmail.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The vCPU thread may receive a signal during ioregionfd communication,
ioctl(KVM_RUN) needs to return to userspace and then ioctl(KVM_RUN)
must resume ioregionfd.

Signed-off-by: Elena Afanasova <eafanasova@gmail.com>
---
Changes in v2:
  - add support for x86 signal handling
  - changes after code review

 arch/x86/kvm/x86.c            | 196 +++++++++++++++++++++++++++++++---
 include/linux/kvm_host.h      |  13 +++
 include/uapi/linux/ioregion.h |  32 ++++++
 virt/kvm/ioregion.c           | 177 +++++++++++++++++++++++++++++-
 virt/kvm/kvm_main.c           |  16 ++-
 5 files changed, 415 insertions(+), 19 deletions(-)
 create mode 100644 include/uapi/linux/ioregion.h

```
#### [PATCH] KVM: Documentation: Fix documentation for nested.
##### From: Yu Zhang <yu.c.zhang@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yu Zhang <yu.c.zhang@linux.intel.com>
X-Patchwork-Id: 12052895
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-14.8 required=3.0 tests=BAYES_00,
	DATE_IN_FUTURE_06_12,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C0590C433E0
	for <kvm@archiver.kernel.org>; Thu, 28 Jan 2021 08:09:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6F07664DA1
	for <kvm@archiver.kernel.org>; Thu, 28 Jan 2021 08:09:19 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231560AbhA1IJQ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 28 Jan 2021 03:09:16 -0500
Received: from mga04.intel.com ([192.55.52.120]:16602 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S231744AbhA1IIh (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 28 Jan 2021 03:08:37 -0500
IronPort-SDR: 
 pk1OdI9ITonkx2UwJ1X5Le5lSh4E37oVNax9bSoG1nGaq4sKVtUpcXvs3Ow9j8mnOM+ZUO9qsc
 SXL46mq1osgA==
X-IronPort-AV: E=McAfee;i="6000,8403,9877"; a="177632199"
X-IronPort-AV: E=Sophos;i="5.79,381,1602572400";
   d="scan'208";a="177632199"
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by fmsmga104.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 28 Jan 2021 00:06:34 -0800
IronPort-SDR: 
 gwiJP6YaMxuscNhGYPs0q08Q4i/JkVYx3t24FPKwU8pngfnoy909ERwqCSOOScAVkG9IYu04mC
 PrqVQUjmjn8Q==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.79,381,1602572400";
   d="scan'208";a="362770166"
Received: from zhangyu-optiplex-7040.bj.intel.com ([10.238.154.148])
  by fmsmga008.fm.intel.com with ESMTP; 28 Jan 2021 00:06:33 -0800
From: Yu Zhang <yu.c.zhang@linux.intel.com>
To: pbonzini@redhat.com, kvm@vger.kernel.org
Cc: corbet@lwn.net, linux-doc@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: Documentation: Fix documentation for nested.
Date: Thu, 28 Jan 2021 23:47:47 +0800
Message-Id: <20210128154747.4242-1-yu.c.zhang@linux.intel.com>
X-Mailer: git-send-email 2.17.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Nested VMX was enabled by default in commit <1e58e5e59148> ("KVM:
VMX: enable nested virtualization by default"), which was merged
in Linux 4.20. This patch is to fix the documentation accordingly.

Signed-off-by: Yu Zhang <yu.c.zhang@linux.intel.com>
---
 Documentation/virt/kvm/nested-vmx.rst            | 6 ++++--
 Documentation/virt/kvm/running-nested-guests.rst | 2 +-
 2 files changed, 5 insertions(+), 3 deletions(-)

```
#### [PATCH] KVM: x86: Allow guests to see MSR_IA32_TSX_CTRL even if tsx=off
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 12054213
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 0CD4CC433E0
	for <kvm@archiver.kernel.org>; Thu, 28 Jan 2021 17:10:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C619A64E14
	for <kvm@archiver.kernel.org>; Thu, 28 Jan 2021 17:10:45 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232789AbhA1RKg (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 28 Jan 2021 12:10:36 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:42971 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S232805AbhA1RJc (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 28 Jan 2021 12:09:32 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1611853686;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=56oQ7o7FTqNZj3MPWTOvHCfMyHXwWD8QK/wEL2B1WRw=;
        b=MmjlWuw+xjdVtnfad9N6+tdGllMpQbB3Am+Opq+3hRLIh0wnZgX6Kub8P0IvnlCf1wjKXh
        /+LKQMBx89EzmtIxZV3K48BnGoWnyeAB+PXWqhMXZLrlWeQYVoSKWi6c+l0TyolOXRftNd
        STiYIz24b95K3nTNhEIni2ZU28PXlZ0=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-25-6MfMRXZwO1GQNqcfnJwJPQ-1; Thu, 28 Jan 2021 12:08:02 -0500
X-MC-Unique: 6MfMRXZwO1GQNqcfnJwJPQ-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 536FC84A5E7;
        Thu, 28 Jan 2021 17:08:01 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id E9CA75D9EF;
        Thu, 28 Jan 2021 17:08:00 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: jmattson@google.com, stable@vger.kernel.org
Subject: [PATCH] KVM: x86: Allow guests to see MSR_IA32_TSX_CTRL even if
 tsx=off
Date: Thu, 28 Jan 2021 12:08:00 -0500
Message-Id: <20210128170800.1783502-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Userspace that does not know about KVM_GET_MSR_FEATURE_INDEX_LIST will
generally use the default value for MSR_IA32_ARCH_CAPABILITIES.
When this happens and the host has tsx=on, it is possible to end up
with virtual machines that have HLE and RTM disabled, but TSX_CTRL
disabled.

If the fleet is then switched to tsx=off, kvm_get_arch_capabilities()
will clear the ARCH_CAP_TSX_CTRL_MSR bit and it will not be possible
to use the tsx=off as migration destinations, even though the guests
indeed do not have TSX enabled.

When tsx=off is used, however, we know that guests will not have
HLE and RTM (or if userspace sets bogus CPUID data, we do not
expect HLE and RTM to work in guests).  Therefore we can keep
TSX_CTRL_RTM_DISABLE set for the entire life of the guests and
save MSR reads and writes on KVM_RUN and in the user return
notifiers.

Cc: stable@vger.kernel.org
Fixes: cbbaa2727aa3 ("KVM: x86: fix presentation of TSX feature in ARCH_CAPABILITIES")
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/vmx/vmx.c | 12 +++++++++++-
 arch/x86/kvm/x86.c     |  2 +-
 2 files changed, 12 insertions(+), 2 deletions(-)

```
#### [PATCH] KVM: x86: fix CPUID entries returned by KVM_GET_CPUID2 ioctl
##### From: Michael Roth <michael.roth@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Michael Roth <michael.roth@amd.com>
X-Patchwork-Id: 12051657
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=unavailable autolearn_force=no
 version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 4DEC2C433E9
	for <kvm@archiver.kernel.org>; Thu, 28 Jan 2021 02:47:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 251A064DE3
	for <kvm@archiver.kernel.org>; Thu, 28 Jan 2021 02:47:03 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229872AbhA1Cqq (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 27 Jan 2021 21:46:46 -0500
Received: from mail-bgr052100131063.outbound.protection.outlook.com
 ([52.100.131.63]:23182
        "EHLO NAM02-BL2-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S229595AbhA1Cqo (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 27 Jan 2021 21:46:44 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=UWdzJUEBuhE8Z9GoGLyzUHyN8YFFxd8XpczaUE2hAyJWiALAT+NggjezBnPNaIJzAElQqxA7d/nHlBdnByqjxSDeKsOmfadT2MWBq/+IAY6geIQrivsam4vTOisGhp5976rRxUeRU8WYLOjDcW31AA2vmTiPlyv9yM9qMpKZ9ruYFFEky8Ai5OWwEZJsfXWlGhE6mqLLBJ/0ZYHSjsGLrewnWYoE1pGrWa/gJrqk00SgQsxie1kSmJaawkmayZfsvScyV4Tl62X8ry+OyIXQEkEa9JopXQkxzWS2wswT4LunjszKKxuD9Xt66U1Nv6OSxlH2bNC0Nat2CMBwnuVmLQ==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=ah+2WTeHV3cgZV+NQieR0mV66QREvWaoPTLB0UQhZ8s=;
 b=daIslSvkxGOC7dzHnv8l8b4KC4XCYjudnVoBKWtYtLesdlCa4OBPq0W8Iw4Hb/mXqoiWwIF+PSyZNCUus19xqUAsuK0/S0gdE7+Rg1IPklyKBe1GEGqz6djNyICWzmUeDab5TM08IjleJeHy/KGm/Y8Ul4xs+Cq5CTazIEMSvRsbHA+fylXCHEVEHR15HIW4HzlSUU7iWu4V3LpOItJWLUNPkkJ/t+vy6xyNidFNP0OEegQcxu0ogBCiujQFgcme4qJie0LMc88rsPbgvCb/MwhIr8pJ6IYS7z1BlSz4nkGXtah2vv2ChlfRRqsscaCfSPS+MHTsitQxJfKdUELe/w==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=amd.com; s=selector1;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=ah+2WTeHV3cgZV+NQieR0mV66QREvWaoPTLB0UQhZ8s=;
 b=ZC/h47ZOZ+F7UaoHxFkJZ6sguBOcIEr3ZUV82C9YBM/mfNPFWXaa+gjm26OSsLgwREx3xFjnFZSdtTx9AWkZp5TJx0HKK6MYkjiL61t+sqtdBmYhsaFaNWdTtQawKA3PsD3IGbRh8TATO5iGAU4Pe0jv7zWOJ6BdXnBeCegvN/Y=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=amd.com;
Received: from CH2PR12MB4133.namprd12.prod.outlook.com (2603:10b6:610:7a::13)
 by CH2PR12MB3702.namprd12.prod.outlook.com (2603:10b6:610:27::12) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3805.17; Thu, 28 Jan
 2021 02:45:54 +0000
Received: from CH2PR12MB4133.namprd12.prod.outlook.com
 ([fe80::81f6:605c:f345:b99f]) by CH2PR12MB4133.namprd12.prod.outlook.com
 ([fe80::81f6:605c:f345:b99f%3]) with mapi id 15.20.3784.019; Thu, 28 Jan 2021
 02:45:54 +0000
From: Michael Roth <michael.roth@amd.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        x86@kernel.org, "H . Peter Anvin" <hpa@zytor.com>,
        linux-kernel@vger.kernel.org,
        Michael Roth <michael.roth@amd.com.com>
Subject: [PATCH] KVM: x86: fix CPUID entries returned by KVM_GET_CPUID2 ioctl
Date: Wed, 27 Jan 2021 20:44:51 -0600
Message-Id: <20210128024451.1816770-1-michael.roth@amd.com>
X-Mailer: git-send-email 2.25.1
X-Originating-IP: [165.204.53.104]
X-ClientProxiedBy: BYAPR11CA0107.namprd11.prod.outlook.com
 (2603:10b6:a03:f4::48) To CH2PR12MB4133.namprd12.prod.outlook.com
 (2603:10b6:610:7a::13)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from localhost (165.204.53.104) by
 BYAPR11CA0107.namprd11.prod.outlook.com (2603:10b6:a03:f4::48) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3805.16 via Frontend
 Transport; Thu, 28 Jan 2021 02:45:53 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: ddd54df3-9f12-49d7-eb09-08d8c336d4d0
X-MS-TrafficTypeDiagnostic: CH2PR12MB3702:
X-Microsoft-Antispam-PRVS: 
 <CH2PR12MB3702DB5FDA618D34066CE2B695BA9@CH2PR12MB3702.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:800;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 +4DP4gAKJPGFZFYAjfiquvlYry8A22u04fL4oHP6lwo6XK4O2NIxRGupNSl+e1DJAYprGOiXmlplt+KSabGAdrjwfXFOKFt/XK2802cqZ/HPdJDHIv3TJucKRAXtHNjjBhLymIhscTQvdbpJ9nWrOfG/A3Rbr4zESdKOb8lfcQBHx0GsjyhIMf/AAa0FZ9EpqKWAzXdC1qpUOaMY01ldUGSpPmBHNJq5NBd69XV+2p/3mML12336PnzMECU8qe1T/B6/G+onQzDESdb+Bf67hzMzK0thai+4A/BznqEDazc+DkSMxcJccNj/Kh5FtoLysyGs773hbfgruv54U6uFviAmNWgxOeLK7zY8oZJKzuEFVdzue//lz+np4rt2d9y3r4EWFYOKahqw4cg21cecG5+MDFZjhPXeiKaV4/QHs8qeZh4P5uj3cqNmotcSGpHyWnUtI9EkBxpT8EA5fqy1MwxE2wSPfbau6Xj5iEmr0XYQV3T3kO3z7oG2JjgTQjNDNgIBGhDIY8fzPc1vGAR5n8PJxsvcT1wk3P9epIEaxuK1Jaj3eUCd0D+4PKECYnMmUWfnNYUEVZIik/nZyeRhFc94FjRVAPBO9zfc+MxPQEjWdUrt2G6mYqnV05TyTimqaqmRgASK0LCYInAk6PeVLSzMgeKxIQP+ZpnIJ2YAPM0YdhENjDT3ZoecoXcS8Q2ktLxUTuIh8NrXo2yYddV5lmLoKgILmDNoq8XiVMmqYpYbJvMpMuWcXTqfF78H228EH5PdbePzK6XRukpAU+e1JtNuIyC7E87eoPLZXn3C7a8Nm/4OB0UDVlewwKzVYS9foZLVJg9uHSN7ePAY/Yrz2tWD0Esm34Id6Dky/nVgUCNr6ZIBoOZA2EK/zjUs1kQ1+/ujFMAGp9EzDpXBWORAcA==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:5;SRV:;IPV:NLI;SFV:SPM;H:CH2PR12MB4133.namprd12.prod.outlook.com;PTR:;CAT:OSPM;SFS:(4636009)(376002)(39860400002)(346002)(136003)(366004)(396003)(1076003)(66476007)(956004)(2616005)(66556008)(26005)(6496006)(66946007)(316002)(7416002)(5660300002)(54906003)(52116002)(44832011)(83380400001)(36756003)(186003)(16526019)(86362001)(8936002)(8676002)(6486002)(6916009)(478600001)(2906002)(4326008)(23200700001);DIR:OUT;SFP:1501;
X-MS-Exchange-AntiSpam-MessageData: 
 mtRilc6IbyXs/KfESncKTg/YlkZieZoTO/sH6YL0oklxcxc6mTCnXDgrZSBOe4gLVeb6TD+0HYO4A1Q1Hh8s9s3bVkQeUl8GS1PjJpxE++2XyTnthkgmtmAzEiXStHJnLf2HVlJbmffsrR6Wv1gGd363U8QokLNtZlTr72pxscTNE7L3YyaMMfZaFSc+p21BHXPMZDP6zF7Nb/wHuUB9Y8rCvlmHDUjYSdUE+WHVpKZbsg8FrQjAUQaYoSNTlWoAqU1TS9GKY9pvqbYRhVgZW2oM37XI3Bm0xpJC+EYeUVhGc29jXGnZKiiGDFsbT4JUO6jYlP6jMSzD/fzeQGlB7WIrrxJ+9HvBTTiYLSoM1RwKZNAl5agWWbWphnRMkas9N8iF+AtP6DCA3DVPVAsHGf6K14uIeviRUc9JLls4u84J/+Pz4XE6U1blk82FWWTYYSSrDD/W6syUHc5BjgAnL/QnAVLdxbg4pO0CrzbQVrWcGONXFG9+ANv5nI1YTVCYQm2QJ4PPu04nY+1BqQOLH2rJDuxWSg+1JlW7Yuik13Gs0mccqzhTjcA19/qHpkxh1/iL0E8fs07dC2vDvA0F2gwAvv6xCogc4K2zPDMbPVVj4uGk66CpOkPWJ0f5z5EERi0OqACK0HlZS8sc5FXc/nqqUJLLK4TgOhwDGtii/vTN4fkwH5RdTJ7TSROnNzjIY6N09YJ/5HrG/dS3u0+7W/q/X7IPIIbKNLszZLIagU/e4NOPsbbFT4HFp3RYtLIqr1gsTJU+hsayUEZ4D8auyGUmmBg7TpXsStR4F+XUS/m++WNm4WXnSHJWzsHbFmNHUwWJAeH2duZuu5w8lyz3g8soVETZRgISLc29yLnI9rwRK0yIhzGwvN2g8ZiEn3xeuSUCnYuE9C6N+dDBfPo+Zr5RVM3ZXUHMwAVLKhIk7EHWvAZUZMXzGPrg0BD2d1IVgp7MwTUDfBovgwkOucnTL6+Xy/SlKZJz0S0907aEfBYeXQm7AABsA9AtMokbmnhB3xRC1O6B872aMQe2GPyAZMAZDr6Zak0qrZsSbFpIte0CJOX4Z6v2KKWJiyrwGO+C
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 ddd54df3-9f12-49d7-eb09-08d8c336d4d0
X-MS-Exchange-CrossTenant-AuthSource: CH2PR12MB4133.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 28 Jan 2021 02:45:54.0779
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 KPNo7LW3gNxirAYMyk1YzsOgp/bU/2fHY77kNNVS4/sFXuYoknjESBnhzxIJpvLqNkD65ly8WVhXKGcSgsrXXw==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: CH2PR12MB3702
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Recent commit 255cbecfe0 modified struct kvm_vcpu_arch to make
'cpuid_entries' a pointer to an array of kvm_cpuid_entry2 entries
rather than embedding the array in the struct. KVM_SET_CPUID and
KVM_SET_CPUID2 were updated accordingly, but KVM_GET_CPUID2 was missed.

As a result, KVM_GET_CPUID2 currently returns random fields from struct
kvm_vcpu_arch to userspace rather than the expected CPUID values. Fix
this by treating 'cpuid_entries' as a pointer when copying its
contents to userspace buffer.

Fixes: 255cbecfe0c9 ("KVM: x86: allocate vcpu->arch.cpuid_entries dynamically")
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>
Signed-off-by: Michael Roth <michael.roth@amd.com.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/cpuid.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v3 1/2] KVM: x86/mmu: Skip mmu_notifier check when handling MMIO page fault
##### From: David Stevens <stevensd@chromium.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Stevens <stevensd@chromium.org>
X-Patchwork-Id: 12051825
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-19.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 1D25AC433E6
	for <kvm@archiver.kernel.org>; Thu, 28 Jan 2021 06:06:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CC9EB64DDC
	for <kvm@archiver.kernel.org>; Thu, 28 Jan 2021 06:06:32 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231319AbhA1GGT (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 28 Jan 2021 01:06:19 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:47988 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S231310AbhA1GGQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 28 Jan 2021 01:06:16 -0500
Received: from mail-pg1-x536.google.com (mail-pg1-x536.google.com
 [IPv6:2607:f8b0:4864:20::536])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 1318AC0613ED
        for <kvm@vger.kernel.org>; Wed, 27 Jan 2021 22:05:36 -0800 (PST)
Received: by mail-pg1-x536.google.com with SMTP id i7so3587608pgc.8
        for <kvm@vger.kernel.org>; Wed, 27 Jan 2021 22:05:36 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=chromium.org; s=google;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=UygKOqEf59SFJHMhhfR+HLz4CGF5Uv9S4hRfcJbt+yk=;
        b=Qh8VODAieLH4894A4MDu3uPPXE5kLO4XxZpYmBxJ82EmJjvCd38+PvJXeC7WfYCIBI
         64aPWxpI+2Wuja2TEV1w1O7J/k/33st78VPhJvOw7GI1Ov6clXkA1iu5LQJ5MR4dUH8V
         v91cI0vNifEcoZnWwsn/8BSJmyZEYnqUhOWFg=
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=UygKOqEf59SFJHMhhfR+HLz4CGF5Uv9S4hRfcJbt+yk=;
        b=twy5rVazUjfcdA1+3BXkEN6+eAkzDkU6iSWpOpsMxI3dGPNKoIj9Dx5yPRWkb/BHBw
         Fll7utfVXOyzxgTHsHmEuC7up8B8x9YHt5/jyLc01x3xWGUC2mgMTS/ckw91F7Vm7TX6
         p3DC7N3vGUW1PGabuL5A9tL0944ESSz4Cgs8i3ASEKUhiKs7kOq5qY6vLyYPpkWDNKvG
         wxfiPpZ3DxFPF/vwJkjkFIEYkRx7z8LW2uukHK++VrPJ/PBSaNdjzUKcAugWA1emFLVB
         UgmzAkfqt7YGI0K5OydhcKyDLqvuuLNa0aqay+6bvrVHFLXBg8YzHsT3RAj/2SjqtYbO
         /vXQ==
X-Gm-Message-State: AOAM533frMNUgvRwYrHOoCrVa84fy3JN8Bct7VAW+zSfE09G4Mz7FlOs
        ar08fARYRDFXIbsdjJC6gCSijg==
X-Google-Smtp-Source: 
 ABdhPJx6bZB3eesMD+UMxqDOEfHH1P0CPHJvUJWhsABLqESuXZOj3BsZQpCR3iBz434VwICAw3KJ+g==
X-Received: by 2002:a62:bd05:0:b029:1ab:6d2:5edf with SMTP id
 a5-20020a62bd050000b02901ab06d25edfmr14361887pff.32.1611813935673;
        Wed, 27 Jan 2021 22:05:35 -0800 (PST)
Received: from localhost ([2401:fa00:8f:203:919f:d6:7815:52bc])
        by smtp.gmail.com with ESMTPSA id
 s73sm4388027pgc.46.2021.01.27.22.05.31
        (version=TLS1_3 cipher=TLS_AES_128_GCM_SHA256 bits=128/128);
        Wed, 27 Jan 2021 22:05:35 -0800 (PST)
From: David Stevens <stevensd@chromium.org>
X-Google-Original-From: David Stevens <stevensd@google.com>
To: Sean Christopherson <seanjc@google.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Marc Zyngier <maz@kernel.org>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        Huacai Chen <chenhuacai@kernel.org>,
        Aleksandar Markovic <aleksandar.qemu.devel@gmail.com>,
        linux-mips@vger.kernel.org, Paul Mackerras <paulus@ozlabs.org>,
        kvm-ppc@vger.kernel.org,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Janosch Frank <frankja@linux.ibm.com>,
        David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Claudio Imbrenda <imbrenda@linux.ibm.com>
Subject: [PATCH v3 1/2] KVM: x86/mmu: Skip mmu_notifier check when handling
 MMIO page fault
Date: Thu, 28 Jan 2021 15:05:14 +0900
Message-Id: <20210128060515.1732758-2-stevensd@google.com>
X-Mailer: git-send-email 2.30.0.280.ga3ce27912f-goog
In-Reply-To: <20210128060515.1732758-1-stevensd@google.com>
References: <20210128060515.1732758-1-stevensd@google.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Sean Christopherson <seanjc@google.com>

Don't retry a page fault due to an mmu_notifier invalidation when
handling a page fault for a GPA that did not resolve to a memslot, i.e.
an MMIO page fault.  Invalidations from the mmu_notifier signal a change
in a host virtual address (HVA) mapping; without a memslot, there is no
HVA and thus no possibility that the invalidation is relevant to the
page fault being handled.

Note, the MMIO vs. memslot generation checks handle the case where a
pending memslot will create a memslot overlapping the faulting GPA.  The
mmu_notifier checks are orthogonal to memslot updates.

Signed-off-by: Sean Christopherson <seanjc@google.com>
---
 arch/x86/kvm/mmu/mmu.c         | 2 +-
 arch/x86/kvm/mmu/paging_tmpl.h | 2 +-
 2 files changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH RFC v2 01/10] vdpa_sim: use iova module to allocate IOVA addresses
##### From: Stefano Garzarella <sgarzare@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stefano Garzarella <sgarzare@redhat.com>
X-Patchwork-Id: 12053875
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id EF197C433E0
	for <kvm@archiver.kernel.org>; Thu, 28 Jan 2021 14:53:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9923C64DD9
	for <kvm@archiver.kernel.org>; Thu, 28 Jan 2021 14:53:25 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232403AbhA1OwE (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 28 Jan 2021 09:52:04 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:44370 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S229870AbhA1OnL (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 28 Jan 2021 09:43:11 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1611844904;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=047Q+kHFTMwlZxZSB0OK+gVEKt1Ugj8Uih+TOE9Lvzk=;
        b=IdV7RC/jPOBb4qO/urZZZdVb3Pc5lnaV1WP7O2upTxQ0AdUvfs4eyrmpsxKEK9IC4L/+hu
        e6dasw5MPp3Jof+/9bYKdBUmLJR4QvQJUhlomhK1qSWTjx28R8KlJvINUaM7uhDRrAwUdq
        +1UZWsHU9OAm4YOBTPefDu4DG8vvKqM=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-125-l6v_Hj7jNeG3bOxw4CGzMA-1; Thu, 28 Jan 2021 09:41:40 -0500
X-MC-Unique: l6v_Hj7jNeG3bOxw4CGzMA-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 0023B8015DA;
        Thu, 28 Jan 2021 14:41:39 +0000 (UTC)
Received: from steredhat.redhat.com (ovpn-113-219.ams2.redhat.com
 [10.36.113.219])
        by smtp.corp.redhat.com (Postfix) with ESMTP id CA6EC60875;
        Thu, 28 Jan 2021 14:41:36 +0000 (UTC)
From: Stefano Garzarella <sgarzare@redhat.com>
To: virtualization@lists.linux-foundation.org
Cc: Xie Yongji <xieyongji@bytedance.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Stefano Garzarella <sgarzare@redhat.com>,
        Laurent Vivier <lvivier@redhat.com>,
        Stefan Hajnoczi <stefanha@redhat.com>,
        linux-kernel@vger.kernel.org, Max Gurtovoy <mgurtovoy@nvidia.com>,
        Jason Wang <jasowang@redhat.com>, kvm@vger.kernel.org
Subject: [PATCH RFC v2 01/10] vdpa_sim: use iova module to allocate IOVA
 addresses
Date: Thu, 28 Jan 2021 15:41:18 +0100
Message-Id: <20210128144127.113245-2-sgarzare@redhat.com>
In-Reply-To: <20210128144127.113245-1-sgarzare@redhat.com>
References: <20210128144127.113245-1-sgarzare@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The identical mapping used until now created issues when mapping
different virtual pages with the same physical address.
To solve this issue, we can use the iova module, to handle the IOVA
allocation.
For simplicity we use an IOVA allocator with byte granularity.

We add two new functions, vdpasim_map_range() and vdpasim_unmap_range(),
to handle the IOVA allocation and the registration into the IOMMU/IOTLB.
These functions are used by dma_map_ops callbacks.

Acked-by: Jason Wang <jasowang@redhat.com>
Signed-off-by: Stefano Garzarella <sgarzare@redhat.com>
---
v2:
- used ULONG_MAX instead of ~0UL [Jason]
- fixed typos in comment and patch description [Jason]
---
 drivers/vdpa/vdpa_sim/vdpa_sim.h |   2 +
 drivers/vdpa/vdpa_sim/vdpa_sim.c | 108 +++++++++++++++++++------------
 drivers/vdpa/Kconfig             |   1 +
 3 files changed, 69 insertions(+), 42 deletions(-)

```
#### [RFC PATCH 01/11] iommu/arm-smmu-v3: Add feature detection for HTTU
##### From: Keqian Zhu <zhukeqian1@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Keqian Zhu <zhukeqian1@huawei.com>
X-Patchwork-Id: 12053959
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id CEA98C433E0
	for <kvm@archiver.kernel.org>; Thu, 28 Jan 2021 15:19:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7A58164DE5
	for <kvm@archiver.kernel.org>; Thu, 28 Jan 2021 15:19:56 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231879AbhA1PTY (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 28 Jan 2021 10:19:24 -0500
Received: from szxga06-in.huawei.com ([45.249.212.32]:11463 "EHLO
        szxga06-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S231220AbhA1PSx (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 28 Jan 2021 10:18:53 -0500
Received: from DGGEMS413-HUB.china.huawei.com (unknown [172.30.72.59])
        by szxga06-in.huawei.com (SkyGuard) with ESMTP id 4DRPG938VYzjDJD;
        Thu, 28 Jan 2021 23:17:05 +0800 (CST)
Received: from DESKTOP-5IS4806.china.huawei.com (10.174.184.42) by
 DGGEMS413-HUB.china.huawei.com (10.3.19.213) with Microsoft SMTP Server id
 14.3.498.0; Thu, 28 Jan 2021 23:17:54 +0800
From: Keqian Zhu <zhukeqian1@huawei.com>
To: <linux-kernel@vger.kernel.org>,
        <linux-arm-kernel@lists.infradead.org>, <kvm@vger.kernel.org>,
        <kvmarm@lists.cs.columbia.edu>, <iommu@lists.linux-foundation.org>,
        Will Deacon <will@kernel.org>,
        "Alex Williamson" <alex.williamson@redhat.com>,
        Marc Zyngier <maz@kernel.org>,
        Catalin Marinas <catalin.marinas@arm.com>
CC: Kirti Wankhede <kwankhede@nvidia.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Mark Rutland <mark.rutland@arm.com>,
        James Morse <james.morse@arm.com>,
        "Robin Murphy" <robin.murphy@arm.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        <wanghaibin.wang@huawei.com>, <jiangkunkun@huawei.com>,
        <yuzenghui@huawei.com>, <lushenming@huawei.com>
Subject: [RFC PATCH 01/11] iommu/arm-smmu-v3: Add feature detection for HTTU
Date: Thu, 28 Jan 2021 23:17:32 +0800
Message-ID: <20210128151742.18840-2-zhukeqian1@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
In-Reply-To: <20210128151742.18840-1-zhukeqian1@huawei.com>
References: <20210128151742.18840-1-zhukeqian1@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.174.184.42]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: jiangkunkun <jiangkunkun@huawei.com>

The SMMU which supports HTTU (Hardware Translation Table Update) can
update the access flag and the dirty state of TTD by hardware. It is
essential to track dirty pages of DMA.

This adds feature detection, none functional change.

Co-developed-by: Keqian Zhu <zhukeqian1@huawei.com>
Signed-off-by: Kunkun Jiang <jiangkunkun@huawei.com>
---
 drivers/iommu/arm/arm-smmu-v3/arm-smmu-v3.c | 16 ++++++++++++++++
 drivers/iommu/arm/arm-smmu-v3/arm-smmu-v3.h |  8 ++++++++
 include/linux/io-pgtable.h                  |  1 +
 3 files changed, 25 insertions(+)

```
