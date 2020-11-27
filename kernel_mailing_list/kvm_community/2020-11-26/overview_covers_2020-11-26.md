

#### [PATCH 0/2] KVM: arm64: Fix DEMUX register access
##### From: Andrew Jones <drjones@redhat.com>

```c
From patchwork Thu Nov 26 13:46:39 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11934107
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-10.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 48D04C63697
	for <kvm@archiver.kernel.org>; Thu, 26 Nov 2020 13:47:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E872220644
	for <kvm@archiver.kernel.org>; Thu, 26 Nov 2020 13:47:04 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="OxEnoGUF"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2391101AbgKZNqs (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 26 Nov 2020 08:46:48 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:31888 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S2391098AbgKZNqs (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 26 Nov 2020 08:46:48 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1606398407;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=jbEexOfgcLFYaQsECYOca5p/Nm1XbLoVmOwp9Ym00nY=;
        b=OxEnoGUFdpw0WcAr0cm9EkzOIEJPOi/Ol3DabfqV3XPhWNprEINjTl8ZV2JnSYA0tq1H33
        KxCI96RaG+wrChGUCmWTGoljHi9bEzyyBPth7qiWKfsenBw/qcbKBsKPdeMpmiLuk5UXwT
        5qsF659//gRc+Fg7gDRp0XGHI5ZRCPs=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-187-wUDATl2NOrmSlKJ4D_Pw6Q-1; Thu, 26 Nov 2020 08:46:45 -0500
X-MC-Unique: wUDATl2NOrmSlKJ4D_Pw6Q-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 73821805BFA;
        Thu, 26 Nov 2020 13:46:44 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.40.192.141])
        by smtp.corp.redhat.com (Postfix) with ESMTP id DF6B310016F7;
        Thu, 26 Nov 2020 13:46:42 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu
Cc: maz@kernel.org, pbonzini@redhat.com
Subject: [PATCH 0/2] KVM: arm64: Fix DEMUX register access
Date: Thu, 26 Nov 2020 14:46:39 +0100
Message-Id: <20201126134641.35231-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The first patch is a fix, but not one likely to ever truly be needed,
as it's unlikely to find seven levels of cache. The bug was found
while code reading. Writing the second patch was actually why I was
reading the code. The issue being fixed for the get-reg-list test was
found when running it on a different machine than what was used to
develop it.

Thanks,
drew

Andrew Jones (2):
  KVM: arm64: CSSELR_EL1 max is 13
  KVM: selftests: Filter out DEMUX registers

 arch/arm64/kvm/sys_regs.c                     |  2 +-
 .../selftests/kvm/aarch64/get-reg-list.c      | 39 ++++++++++++++-----
 2 files changed, 31 insertions(+), 10 deletions(-)
```
