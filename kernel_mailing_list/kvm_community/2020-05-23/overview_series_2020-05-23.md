#### [PATCH 1/1] vfio/spapr_tce: convert get_user_pages() --> pin_user_pages()
##### From: John Hubbard <jhubbard@nvidia.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: John Hubbard <jhubbard@nvidia.com>
X-Patchwork-Id: 11566473
Return-Path: <SRS0=+Aw4=7F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9ECCE138A
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 23 May 2020 01:44:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7DD4E20727
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 23 May 2020 01:44:16 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=nvidia.com header.i=@nvidia.com
 header.b="fAaH855X"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2387477AbgEWBnt (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 22 May 2020 21:43:49 -0400
Received: from hqnvemgate24.nvidia.com ([216.228.121.143]:11739 "EHLO
        hqnvemgate24.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2387427AbgEWBnt (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 22 May 2020 21:43:49 -0400
Received: from hqpgpgate101.nvidia.com (Not Verified[216.228.121.13]) by
 hqnvemgate24.nvidia.com (using TLS: TLSv1.2, DES-CBC3-SHA)
        id <B5ec87f430000>; Fri, 22 May 2020 18:41:23 -0700
Received: from hqmail.nvidia.com ([172.20.161.6])
  by hqpgpgate101.nvidia.com (PGP Universal service);
  Fri, 22 May 2020 18:43:48 -0700
X-PGP-Universal: processed;
        by hqpgpgate101.nvidia.com on Fri, 22 May 2020 18:43:48 -0700
Received: from HQMAIL101.nvidia.com (172.20.187.10) by HQMAIL109.nvidia.com
 (172.20.187.15) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Sat, 23 May
 2020 01:43:48 +0000
Received: from hqnvemgw03.nvidia.com (10.124.88.68) by HQMAIL101.nvidia.com
 (172.20.187.10) with Microsoft SMTP Server (TLS) id 15.0.1473.3 via Frontend
 Transport; Sat, 23 May 2020 01:43:48 +0000
Received: from sandstorm.nvidia.com (Not Verified[10.2.52.1]) by
 hqnvemgw03.nvidia.com with Trustwave SEG (v7,5,8,10121)
        id <B5ec87fd40001>; Fri, 22 May 2020 18:43:48 -0700
From: John Hubbard <jhubbard@nvidia.com>
To: LKML <linux-kernel@vger.kernel.org>
CC: Souptick Joarder <jrdr.linux@gmail.com>,
        John Hubbard <jhubbard@nvidia.com>,
        Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>, <kvm@vger.kernel.org>
Subject: [PATCH 1/1] vfio/spapr_tce: convert get_user_pages() -->
 pin_user_pages()
Date: Fri, 22 May 2020 18:43:47 -0700
Message-ID: <20200523014347.193290-1-jhubbard@nvidia.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
X-NVConfidentiality: public
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1590198083; bh=aNxPaUMw4B6W9o4OKROyKEN8taVDg0VgvpxK29EQarg=;
        h=X-PGP-Universal:From:To:CC:Subject:Date:Message-ID:X-Mailer:
         MIME-Version:X-NVConfidentiality:Content-Transfer-Encoding:
         Content-Type;
        b=fAaH855X8qd9w/i41ulaTLwkNv7vNOo/uAIWw0g6ZIauJPn0I+dJ3tJBHQcvOiBHA
         /vQ2YrtqSNTbDY8zUKLuTFkGmAeGsYxXuGOCEUdUHEr/4+6L/cAhKxV31BOww26dfK
         EyAxjd/weu4sdSe5uy9jw+qi7/HLDMOlEHv5YoVoTkVJwXsg8JUDSMBlNxIMvB+WRQ
         TxtyMvrGfITDKeQVf5kOy0iYmNI2Dy6aUBnHDyPqTJYqndA/lj8uBb4Ib7ajcJceMY
         TAr8Cxhf0YHDO8J99+Gt55xHt0q9+YSRpsaa/LWtJTnkOD2apoN4WUWfePUblIkKJe
         whxoekKWcJLEA==
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This code was using get_user_pages*(), in a "Case 2" scenario
(DMA/RDMA), using the categorization from [1]. That means that it's
time to convert the get_user_pages*() + put_page() calls to
pin_user_pages*() + unpin_user_pages() calls.

There is some helpful background in [2]: basically, this is a small
part of fixing a long-standing disconnect between pinning pages, and
file systems' use of those pages.

[1] Documentation/core-api/pin_user_pages.rst

[2] "Explicit pinning of user-space pages":
    https://lwn.net/Articles/807108/

Cc: Alex Williamson <alex.williamson@redhat.com>
Cc: Cornelia Huck <cohuck@redhat.com>
Cc: kvm@vger.kernel.org
Signed-off-by: John Hubbard <jhubbard@nvidia.com>
---

Hi,

I'm compile-tested this, but am not able to run-time test, so any
testing help is much appreciated!

thanks,
John Hubbard
NVIDIA

 drivers/vfio/vfio_iommu_spapr_tce.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH 1/2] kvm/x86/vmx: enable X86_FEATURE_WAITPKG in KVM capabilities
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 11566841
Return-Path: <SRS0=+Aw4=7F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 40B04138A
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 23 May 2020 16:15:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2957920885
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 23 May 2020 16:15:25 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="g+cyEwqu"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728137AbgEWQPX (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 23 May 2020 12:15:23 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:47355 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1728025AbgEWQPW (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 23 May 2020 12:15:22 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1590250521;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=ytf9W2kex3b56H4BEKOUukloGENtrEZz4KuH9AmMNpQ=;
        b=g+cyEwquQ4ytNWuON3C3BagDVPR1LyAEYlnBJBg5tR8fo9+8F69pmhuu6BiaH4Im7RIW6c
        mXgpwhfYeWkaJRLzK4QVuoqPiSeMC6w49sQBszRTYtWI2LNAH3SlXi/tdHMSYoy9YPSZlB
        uop49GSr00Kuwl3njyfgPsdBZJbfp9E=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-85-3rESmGjfPumnQqjegbACfQ-1; Sat, 23 May 2020 12:15:17 -0400
X-MC-Unique: 3rESmGjfPumnQqjegbACfQ-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 8EBCF107ACCA;
        Sat, 23 May 2020 16:15:15 +0000 (UTC)
Received: from starship.f32vm (unknown [10.35.206.21])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 2DD6B600E5;
        Sat, 23 May 2020 16:15:01 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        "H. Peter Anvin" <hpa@zytor.com>, Tao Xu <tao3.xu@intel.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Jim Mattson <jmattson@google.com>,
        linux-kernel@vger.kernel.org, Joerg Roedel <joro@8bytes.org>,
        x86@kernel.org (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT)),
        Wanpeng Li <wanpengli@tencent.com>,
        Ingo Molnar <mingo@redhat.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Borislav Petkov <bp@alien8.de>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Jingqi Liu <jingqi.liu@intel.com>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH 1/2] kvm/x86/vmx: enable X86_FEATURE_WAITPKG in KVM
 capabilities
Date: Sat, 23 May 2020 19:14:54 +0300
Message-Id: <20200523161455.3940-2-mlevitsk@redhat.com>
In-Reply-To: <20200523161455.3940-1-mlevitsk@redhat.com>
References: <20200523161455.3940-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Even though we might not allow the guest to use
WAITPKG's new instructions, we should tell KVM
that the feature is supported by the host CPU.

Note that vmx_waitpkg_supported checks that WAITPKG
_can_ be set in secondary execution controls as specified
by VMX capability MSR, rather that we actually enable it for a guest.

Fixes: e69e72faa3a0 KVM: x86: Add support for user wait instructions

Suggested-by: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Maxim Levitsky <mlevitsk@redhat.com>
---
 arch/x86/kvm/vmx/vmx.c | 3 +++
 1 file changed, 3 insertions(+)

```
#### [PATCH v9 01/14] KVM: X86: Change parameter for fast_page_fault tracepoint
##### From: Peter Xu <peterx@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11567041
Return-Path: <SRS0=+Aw4=7F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9E2DD60D
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 23 May 2020 22:58:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 87D24207FB
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 23 May 2020 22:58:24 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="i7qAG21S"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388087AbgEWW5K (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 23 May 2020 18:57:10 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:51656 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S2388016AbgEWW5J (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 23 May 2020 18:57:09 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1590274627;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=Ble7s/BrlGwUPRHQ34ii4/VsZgKqdI5xssnXt1KNNb0=;
        b=i7qAG21S8ElRH5jg3tJFA514dY73cBaRyuN5fCCKfm+W97cvgP2RYEfMV+PseTq4DX85WY
        mLmj7/kcKJtWpyNBcjF2ksyYgTd5qAh3mpeJxQ3AM70dUqE7GUR/F/R4kkcnOPF9gMFERm
        nB7dBqJIjiFg//KN0RYiDwTJorrYdEc=
Received: from mail-qt1-f197.google.com (mail-qt1-f197.google.com
 [209.85.160.197]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-438-3MUodmNfP1uEc7tKxZO6mA-1; Sat, 23 May 2020 18:57:06 -0400
X-MC-Unique: 3MUodmNfP1uEc7tKxZO6mA-1
Received: by mail-qt1-f197.google.com with SMTP id p20so3052254qtq.13
        for <kvm@vger.kernel.org>; Sat, 23 May 2020 15:57:05 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=Ble7s/BrlGwUPRHQ34ii4/VsZgKqdI5xssnXt1KNNb0=;
        b=Xd14gj+H4kDIWkku2SgloYhZr7SAVFDWSny/VZihX5jZf8ZnD+JaTA5kW9TJiJAGHU
         QbU8rh3kzOmLQr7JXY2Ykfic3TMexfcfxavI7UIr55lr5MfSCYF3U2DKpBgsq3PJ1WRP
         HjEzSIbt3uHWRYF4gp7XS/wLmivMAqZzMcdwSHT8cO2xJzOGnKtEzEBDqgUDsyEX54xP
         GyDHtIEWTtxcZYSewEt6WD76bh5tACGIt9f9PuHMchJjXQJPKSseqc+lCcQWw5qeltyn
         gn9okx3L7TUz+8RgNlVi4P84d3anSIxVcSLJJwJ8k9hbMR1ua9L9IOFFBe9Lj0wfcVSt
         +N1w==
X-Gm-Message-State: AOAM532D0GfVgMpMcGjcdaYtYeQgi4nn7qBQcA4g1Owywn9dDfXxw8ji
        I3lxQF5CnKUjv8MW/5qHdvgd9cRKcXr9qf4hOBWwASmElrUvGh0o0/5wLbQ3vSWv3zIekKTWhHF
        YEZgY6RjOunal
X-Received: by 2002:ac8:4a88:: with SMTP id l8mr21356368qtq.337.1590274625496;
        Sat, 23 May 2020 15:57:05 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJzyfZidmD/ZSQV5cbmCS0RnT9AdYlS2aPMYmebfucXy9aWDUoU3As8I7YtAnly5gG9nM+kp4g==
X-Received: by 2002:ac8:4a88:: with SMTP id l8mr21356349qtq.337.1590274625276;
        Sat, 23 May 2020 15:57:05 -0700 (PDT)
Received: from xz-x1.hitronhub.home
 (CPEf81d0fb19163-CMf81d0fb19160.cpe.net.fido.ca. [72.137.123.47])
        by smtp.gmail.com with ESMTPSA id
 w14sm11630979qtt.82.2020.05.23.15.57.03
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Sat, 23 May 2020 15:57:04 -0700 (PDT)
From: Peter Xu <peterx@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>,
        Alex Williamson <alex.williamson@redhat.com>,
        "Michael S . Tsirkin" <mst@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        "Dr . David Alan Gilbert" <dgilbert@redhat.com>,
        Christophe de Dinechin <dinechin@redhat.com>,
        Jason Wang <jasowang@redhat.com>,
        Kevin Tian <kevin.tian@intel.com>, peterx@redhat.com,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Yan Zhao <yan.y.zhao@intel.com>
Subject: [PATCH v9 01/14] KVM: X86: Change parameter for fast_page_fault
 tracepoint
Date: Sat, 23 May 2020 18:56:46 -0400
Message-Id: <20200523225659.1027044-2-peterx@redhat.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20200523225659.1027044-1-peterx@redhat.com>
References: <20200523225659.1027044-1-peterx@redhat.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

It would be clearer to dump the return value to know easily on whether
did we go through the fast path for handling current page fault.
Remove the old two last parameters because after all the old/new sptes
were dumped in the same line.

Signed-off-by: Peter Xu <peterx@redhat.com>
---
 arch/x86/kvm/mmutrace.h | 9 ++-------
 1 file changed, 2 insertions(+), 7 deletions(-)

```
#### [PATCH V7 01/15] KVM: MIPS: Define KVM_ENTRYHI_ASID to cpu_asid_mask(&boot_cpu_data)
##### From: Huacai Chen <chenhc@lemote.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Huacai Chen <chenhc@lemote.com>
X-Patchwork-Id: 11566639
Return-Path: <SRS0=+Aw4=7F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5AADC13B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 23 May 2020 07:56:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 42FB8207DA
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 23 May 2020 07:56:39 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="qKt68FL6"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2387691AbgEWH4i (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 23 May 2020 03:56:38 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:46578 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2387627AbgEWH4h (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 23 May 2020 03:56:37 -0400
Received: from mail-pg1-x544.google.com (mail-pg1-x544.google.com
 [IPv6:2607:f8b0:4864:20::544])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 9C3DAC05BD43;
        Sat, 23 May 2020 00:56:37 -0700 (PDT)
Received: by mail-pg1-x544.google.com with SMTP id f21so3083446pgg.12;
        Sat, 23 May 2020 00:56:37 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id:in-reply-to:references;
        bh=Qfp4yZyJhFbbwPcF+vBxspab423+TYrLon5VaFM6mOQ=;
        b=qKt68FL6knNx22492KjI7dofR8nLWj1uFsCNtT9M+/7gH8jAfO4j90PM8e03Xne0Ug
         dNGBaboyHUe7RTkxi+tkMyTbTZ5sGq/RMiY5xHfzfeVyWs+hOV6Ox7BhiVIczUpThKLI
         fIKunyYzoK6AR1kqTvG+dlYXZL3SLbcprkvS7HXqQCy+94Fioj8wKTR0nMqXkdaaRO34
         j27N5+v1d74RHX49D8j/51v9YxM5oD1pVUQtN0WLf9LDY9WydgA9FcOK48pn7M9oemeC
         yLq8XoITOIFhL8U7aBcf7p03MRCMWem+t2G+O2whXLdrTJjoY7wwDfRkHipI6nSjESzS
         D6/Q==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id
         :in-reply-to:references;
        bh=Qfp4yZyJhFbbwPcF+vBxspab423+TYrLon5VaFM6mOQ=;
        b=RVn5G9hUaYynwsqTHlAS1tgu2dSWEd/Zpz4EFpgISf9W0oZztjAKfIiwPJ7zJWUiOa
         o5no2ieg8CMDgt+sr7P+tvsbkmLF9ROxeaO0LpdMoHHUipY/up3ES6SCmLajX1MQFMkd
         wbUA206bmJAWU6v5nWF3VRN6gg7j9hHuKFNv/sBUGDfoqWOlOSZ2+pyS+ZwpTAfOabKV
         YdIns60K5hEJWOxJArLi662Vyw/P0NiKbEFTWzshA4pQ/KcqrRzyry4CaECtYyDxyY1r
         9D9K+03j4d8YDwii+Tnbx6YjQXqDrvNUhkXEqCbt7Wh1WZflWS4q8giCY3JxSGaUaiEi
         9tEw==
X-Gm-Message-State: AOAM532ssyViVb2Xmp38viL3tKo2KP/mD8j3ISEK/e9ZKh2Gn3FXLlS3
        J0nM2znd4BV6qnaX3GcqmDg=
X-Google-Smtp-Source: 
 ABdhPJyNeZUAnuYrVDbTxjPNLgE78WW8noHorDS/yW0zaDqkSzMEvLMUwxZukXfB/c4DhEFNqmB+8A==
X-Received: by 2002:a62:b402:: with SMTP id h2mr7806324pfn.221.1590220597128;
        Sat, 23 May 2020 00:56:37 -0700 (PDT)
Received: from software.domain.org (28.144.92.34.bc.googleusercontent.com.
 [34.92.144.28])
        by smtp.gmail.com with ESMTPSA id
 w7sm678491pfu.117.2020.05.23.00.56.33
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Sat, 23 May 2020 00:56:36 -0700 (PDT)
From: Huacai Chen <chenhc@lemote.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Thomas Bogendoerfer <tsbogend@alpha.franken.de>,
        Aleksandar Markovic <aleksandar.qemu.devel@gmail.com>
Cc: kvm@vger.kernel.org, linux-mips@vger.kernel.org,
        Fuxin Zhang <zhangfx@lemote.com>,
        Huacai Chen <chenhuacai@gmail.com>,
        Jiaxun Yang <jiaxun.yang@flygoat.com>,
        Xing Li <lixing@loongson.cn>,
        "Stable #4 . 9+" <stable@vger.kernel.org>,
        Huacai Chen <chenhc@lemote.com>
Subject: [PATCH V7 01/15] KVM: MIPS: Define KVM_ENTRYHI_ASID to
 cpu_asid_mask(&boot_cpu_data)
Date: Sat, 23 May 2020 15:56:28 +0800
Message-Id: <1590220602-3547-2-git-send-email-chenhc@lemote.com>
X-Mailer: git-send-email 2.7.0
In-Reply-To: <1590220602-3547-1-git-send-email-chenhc@lemote.com>
References: <1590220602-3547-1-git-send-email-chenhc@lemote.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Xing Li <lixing@loongson.cn>

The code in decode_config4() of arch/mips/kernel/cpu-probe.c

        asid_mask = MIPS_ENTRYHI_ASID;
        if (config4 & MIPS_CONF4_AE)
                asid_mask |= MIPS_ENTRYHI_ASIDX;
        set_cpu_asid_mask(c, asid_mask);

set asid_mask to cpuinfo->asid_mask.

So in order to support variable ASID_MASK, KVM_ENTRYHI_ASID should also
be changed to cpu_asid_mask(&boot_cpu_data).

Cc: Stable <stable@vger.kernel.org>  #4.9+
Reviewed-by: Aleksandar Markovic <aleksandar.qemu.devel@gmail.com>
Signed-off-by: Xing Li <lixing@loongson.cn>
[Huacai: Change current_cpu_data to boot_cpu_data for optimization]
Signed-off-by: Huacai Chen <chenhc@lemote.com>
---
 arch/mips/include/asm/kvm_host.h | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH 1/3] kvm-unit-tests: nVMX: Test GUEST_BASE_GDTR and GUEST_BASE_IDTR on vmentry of nested guests
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11566465
Return-Path: <SRS0=+Aw4=7F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A4BC5739
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 23 May 2020 01:07:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8DBB320756
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 23 May 2020 01:07:25 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="nbw9m4B3"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2387515AbgEWBHM (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 22 May 2020 21:07:12 -0400
Received: from aserp2120.oracle.com ([141.146.126.78]:55010 "EHLO
        aserp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2387481AbgEWBHL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 22 May 2020 21:07:11 -0400
Received: from pps.filterd (aserp2120.oracle.com [127.0.0.1])
        by aserp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 04N12vmE141487;
        Sat, 23 May 2020 01:07:05 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=corp-2020-01-29;
 bh=b3wjFY2nfeMXo73nP9tjwYwmaSSSRj72YCwuvzzjD3A=;
 b=nbw9m4B3qT859CBxh2jLOHeFBXRihjs4aIVKHFlUnF6ShaAcCfbG4pYLTD9kktnX6kx/
 I17DabwF9f2XMou17mg45rUitjTmdvHGE7Nh0AkVX263qwL74MlCTK56RgIjGRk9Ke9V
 Lqr4LGm6vkRfdpwTpcvPSTfBSklpiBJDh8niyAep7F/aZPogCK+DOmkNOkzbJK6YPtq6
 j3btXj6tUmo1cXhrimxxL2M4TzdsJo8PUh3uPdmmgb6p2HPwRfH2F6vP4it5c7pY+1DH
 qKDpsANv2Ha9WouLe66yJa6dgChTtVZNskfSNlssGGw8ymNPVhjfveRVQjzSrboI4Gp5 Ag==
Received: from userp3020.oracle.com (userp3020.oracle.com [156.151.31.79])
        by aserp2120.oracle.com with ESMTP id 31284mg7qm-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=FAIL);
        Sat, 23 May 2020 01:07:05 +0000
Received: from pps.filterd (userp3020.oracle.com [127.0.0.1])
        by userp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 04N13LNU110813;
        Sat, 23 May 2020 01:07:05 GMT
Received: from userv0122.oracle.com (userv0122.oracle.com [156.151.31.75])
        by userp3020.oracle.com with ESMTP id 3150259y3q-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Sat, 23 May 2020 01:07:05 +0000
Received: from abhmp0006.oracle.com (abhmp0006.oracle.com [141.146.116.12])
        by userv0122.oracle.com (8.14.4/8.14.4) with ESMTP id 04N174BD021215;
        Sat, 23 May 2020 01:07:04 GMT
Received: from ban25x6uut29.us.oracle.com (/10.153.73.29)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Fri, 22 May 2020 18:07:04 -0700
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com,
        sean.j.christopherson@intel.com
Subject: [PATCH 1/3] kvm-unit-tests: nVMX: Test GUEST_BASE_GDTR and
 GUEST_BASE_IDTR on vmentry of nested guests
Date: Fri, 22 May 2020 20:26:01 -0400
Message-Id: <20200523002603.32450-2-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20200523002603.32450-1-krish.sadhukhan@oracle.com>
References: <20200523002603.32450-1-krish.sadhukhan@oracle.com>
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9629
 signatures=668686
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 spamscore=0
 mlxscore=0 mlxlogscore=999
 adultscore=0 bulkscore=0 suspectscore=13 phishscore=0 malwarescore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2004280000
 definitions=main-2005230005
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9629
 signatures=668686
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=13
 mlxscore=0
 cotscore=-2147483648 impostorscore=0 malwarescore=0 mlxlogscore=999
 lowpriorityscore=0 phishscore=0 spamscore=0 bulkscore=0 adultscore=0
 priorityscore=1501 clxscore=1015 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-2004280000 definitions=main-2005230005
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

According to section "Checks on Guest Descriptor-Table Registers" in Intel
SDM vol 3C, the following check is performed on the Guest Descriptor-Table
Registers on vmentry of nested guests:

    - On processors that support Intel 64 architecture, the base-address
      fields must contain canonical addresses.

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 x86/vmx_tests.c | 5 +++++
 1 file changed, 5 insertions(+)

```
#### [linux-next RFC] mm/gup.c: Convert to use get_user_pages_fast_only()
##### From: Souptick Joarder <jrdr.linux@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Souptick Joarder <jrdr.linux@gmail.com>
X-Patchwork-Id: 11566847
Return-Path: <SRS0=+Aw4=7F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EE83460D
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 23 May 2020 16:35:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C569C20787
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 23 May 2020 16:35:33 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="awwC905D"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728255AbgEWQf3 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 23 May 2020 12:35:29 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:42324 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728044AbgEWQf3 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 23 May 2020 12:35:29 -0400
Received: from mail-pf1-x441.google.com (mail-pf1-x441.google.com
 [IPv6:2607:f8b0:4864:20::441])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 2D827C061A0E;
        Sat, 23 May 2020 09:35:29 -0700 (PDT)
Received: by mail-pf1-x441.google.com with SMTP id x13so6618155pfn.11;
        Sat, 23 May 2020 09:35:29 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=SPwvsl09hB2hY7vOwt/I7H2rDDPUmLEvYZeiYLVmTxA=;
        b=awwC905DtOmsRxPl9VpH7xse2oOvoTCwphi2JL9ipFHZ1tJfd2S3NMEaTEM2Gtid7J
         G5XUB+7fUbIm7nd4HHwIi7YjHrQTbTarVbq+mjfpH1d2MouOlJhT6ZYgmWbrhan+4tcK
         mV7VS5kkri+kgMAFJEUD483avv0CzqKdHRTmU+6DzkWYspweoc6qfZs626ny01vuWKwX
         eyatucxyWAEgDQ2tjtcOHP+neHco2CfvWPXtBor1Y4x/1YUI7L6RE/pmXnsuIofRXH/V
         rxwLSQ96hZ8aciMBZ3t3Mx+Gm0Lec2sr0HwxytIAb7E8r2r1JTK9U4+anDWKzyypwA/A
         u7Gg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=SPwvsl09hB2hY7vOwt/I7H2rDDPUmLEvYZeiYLVmTxA=;
        b=PU9KJWebYft4nHuFxgJoLVzG2M4gZSkzIArg7frUs+7WX/8Qu3akOQslc8RfLwrEHR
         GdTGl51Li5D9Ad1wzVZenWqD4O6HfCwQGCq0onN8GF2Hjtwi2J0IaVsMvbi5hL1RGMUA
         urTySZw8lhnkfBooDrQoaeS3nlRDE3UPny6lRRTr2f4y+Y02K3190QamKBsWTlE3lRg9
         uCV0LiUnXmhX5rlvE3gc5CNvreUO8ZayffqcCYRpRrSdnh42K6Ea61F0P2MuAAqD4ODc
         YZyT7f546o0rHFwj5EoOJc3+ZLsKsMsZgS/M43mz9mwduEu5x00hjQT9apZnyeolHzLw
         i1CQ==
X-Gm-Message-State: AOAM530bj4JJ7BLYzm1bNONkRgrsO0mUIYUOLYA91a+EGTyQr/I9U6fR
        cM1hkuidvOXCtPZq7P1gbGw=
X-Google-Smtp-Source: 
 ABdhPJw+IhCIgVWqU4NAcraQunQOd43jmSnfk7GPbMKu7X2WVjajeWatsEAUCznsi/qFfbfvnJ+yLg==
X-Received: by 2002:a65:6496:: with SMTP id e22mr759651pgv.63.1590251728535;
        Sat, 23 May 2020 09:35:28 -0700 (PDT)
Received: from jordon-HP-15-Notebook-PC.domain.name ([122.166.90.90])
        by smtp.gmail.com with ESMTPSA id
 b74sm8415460pga.31.2020.05.23.09.35.21
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Sat, 23 May 2020 09:35:27 -0700 (PDT)
From: Souptick Joarder <jrdr.linux@gmail.com>
To: paulus@ozlabs.org, mpe@ellerman.id.au, benh@kernel.crashing.org,
        akpm@linux-foundation.org, peterz@infradead.org, mingo@redhat.com,
        acme@kernel.org, mark.rutland@arm.com,
        alexander.shishkin@linux.intel.com, namhyung@kernel.org,
        pbonzini@redhat.com, sfr@canb.auug.org.au, rppt@linux.ibm.com,
        msuchanek@suse.de, aneesh.kumar@linux.ibm.com
Cc: kvm-ppc@vger.kernel.org, linuxppc-dev@lists.ozlabs.org,
        linux-kernel@vger.kernel.org, linux-mm@kvack.org,
        kvm@vger.kernel.org, Souptick Joarder <jrdr.linux@gmail.com>,
        John Hubbard <jhubbard@nvidia.com>,
        Matthew Wilcox <willy@infradead.org>
Subject: [linux-next RFC] mm/gup.c: Convert to use get_user_pages_fast_only()
Date: Sat, 23 May 2020 22:11:12 +0530
Message-Id: <1590252072-2793-1-git-send-email-jrdr.linux@gmail.com>
X-Mailer: git-send-email 1.9.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Renaming the API __get_user_pages_fast() to get_user_pages_
fast_only() to align with pin_user_pages_fast_only().

As part of this we will get rid of write parameter.
Instead caller will pass FOLL_WRITE to get_user_pages_fast_only().
This will not change any existing functionality of the API.

All the callers are changed to pass FOLL_WRITE.

Updated the documentation of the API.

Signed-off-by: Souptick Joarder <jrdr.linux@gmail.com>
Cc: John Hubbard <jhubbard@nvidia.com>
Cc: Matthew Wilcox <willy@infradead.org>
---
 arch/powerpc/kvm/book3s_64_mmu_hv.c    |  2 +-
 arch/powerpc/kvm/book3s_64_mmu_radix.c |  2 +-
 arch/powerpc/perf/callchain_64.c       |  2 +-
 include/linux/mm.h                     |  4 ++--
 kernel/events/core.c                   |  4 ++--
 mm/gup.c                               | 29 ++++++++++++++++-------------
 virt/kvm/kvm_main.c                    |  6 +++---
 7 files changed, 26 insertions(+), 23 deletions(-)

```
