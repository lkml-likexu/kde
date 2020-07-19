#### [PATCH] docs: kvm/api.rst: Fix indentation
##### From: "Daniel W. S. Almeida" <dwlsalmeida@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Daniel W. S. Almeida" <dwlsalmeida@gmail.com>
X-Patchwork-Id: 11671989
Return-Path: <SRS0=CTxd=A5=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A1A12913
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 18 Jul 2020 16:51:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7C18221775
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 18 Jul 2020 16:51:34 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="FHaO/NxH"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728092AbgGRQva (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 18 Jul 2020 12:51:30 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:60738 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727055AbgGRQv3 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 18 Jul 2020 12:51:29 -0400
Received: from mail-qk1-x744.google.com (mail-qk1-x744.google.com
 [IPv6:2607:f8b0:4864:20::744])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id AF02CC0619D2;
        Sat, 18 Jul 2020 09:51:29 -0700 (PDT)
Received: by mail-qk1-x744.google.com with SMTP id l6so11557988qkc.6;
        Sat, 18 Jul 2020 09:51:29 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=lIGof6uhpVZKmwpXjgyNaJcaBa8FLlzcFqyZDPjbpOc=;
        b=FHaO/NxHUOFcOqsNLqkObDHrJ8NKtxIFBDdP7zoImnujezq0cfyHkpz4CvGR+iBlNu
         tKr6ljahu9FVRmldf82wqWgjTTrVZk9C+rVGr2NG9e4zBsNLrzsaGGXDMvMfoF2dzLSK
         tM3Dl/26+BRVZjJMg2iDIDcJaYoZ1aAFIKenaLkMo6s70zPo6ehETtiAH92tYo1Qh2Vb
         5gVH8aUlLKgyhkyFRdyAVM/RSJ4ggLNTbHEDzTxtf/VoK8Bcsr/SgooMA/Qr9pr3Fu0C
         ei0Y8yrA8iK3G/rM5HGkYqk5xNcuWI2yZaFNN4MLl8grVxvVb19hilzgbADagMztdknS
         y0ug==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=lIGof6uhpVZKmwpXjgyNaJcaBa8FLlzcFqyZDPjbpOc=;
        b=dSZq97GQCbapVGOn2j+wgJO3OSzUFIpclSAjlo2Twda+HJ8ggLRnjEbwT2x/HtnUSV
         nGxkojOVTOCjCPOyTkFlrVuWGFxqi4VqsD/QBtposGp0LrDsRny6uEpe2pFckMozxkZ0
         RZNEo7eprgEDZVQ9L2wIeCD6mNQpKkMoMNnyqpRfLZiQHSBXozYuGnNmvK795xPzYv2F
         SgbTFvPFD830YmUeZ2rvK+iDhomtcAG6zFJglneHCEZi5Hkuvfj/8AQzjYksdDlrweHl
         In4z2C/jEqAK6H52ND+p8vKpdQxDgGIsT/Rt8BGYgldmppRoe0uu+8XBf/vfn6rwLKX/
         a4WA==
X-Gm-Message-State: AOAM531tLFTv3KTD+geB0/eUkwZ1TTs89W45PjmTcFRfw6E8PPIjPSVO
        RZXPPCqYCWD+gshqm4awSNM=
X-Google-Smtp-Source: 
 ABdhPJwAyyLQgydCgRLXXu7r8kcxHE/psJ0c6rdQ+7sbtq2ogG+Z9LOekUBi78aoG+v7Vt+7MIPiow==
X-Received: by 2002:a05:620a:40c1:: with SMTP id
 g1mr14360069qko.391.1595091088912;
        Sat, 18 Jul 2020 09:51:28 -0700 (PDT)
Received: from localhost.localdomain ([2804:18:602d:16d:d038:1a92:190d:65d2])
        by smtp.gmail.com with ESMTPSA id
 q5sm15361801qtf.12.2020.07.18.09.51.25
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Sat, 18 Jul 2020 09:51:28 -0700 (PDT)
From: "Daniel W. S. Almeida" <dwlsalmeida@gmail.com>
X-Google-Original-From: Daniel W. S. Almeida
To: corbet@lwn.net, pbonzini@redhat.com
Cc: "Daniel W . S . Almeida" <dwlsalmeida@gmail.com>,
        linux-doc@vger.kernel.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org
Subject: [PATCH] docs: kvm/api.rst: Fix indentation
Date: Sat, 18 Jul 2020 13:50:57 -0300
Message-Id: <20200718165107.625847-3-dwlsalmeida@gmail.com>
X-Mailer: git-send-email 2.27.0
In-Reply-To: <20200718165107.625847-1-dwlsalmeida@gmail.com>
References: <20200718165107.625847-1-dwlsalmeida@gmail.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Daniel W. S. Almeida <dwlsalmeida@gmail.com>

Fix the following warnings:

WARNING: Definition list ends without a blank line; unexpected unindent

Signed-off-by: Daniel W. S. Almeida <dwlsalmeida@gmail.com>
---
 Documentation/virt/kvm/api.rst | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH 1/7] KVM: x86: Add RIP to the kvm_entry, i.e. VM-Enter, tracepoint
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11671705
Return-Path: <SRS0=CTxd=A5=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F3CDB13B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 18 Jul 2020 06:39:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E50092083B
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 18 Jul 2020 06:39:46 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729030AbgGRGjm (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 18 Jul 2020 02:39:42 -0400
Received: from mga09.intel.com ([134.134.136.24]:30319 "EHLO mga09.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726551AbgGRGjB (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 18 Jul 2020 02:39:01 -0400
IronPort-SDR: 
 r0A0JB1oajJ29rhhkVdRyhJiFNBkgkw5/bH233KOrzWx14QjfOLubZhuMWRCYV34j903P6tUU6
 sVcgXATOp2CA==
X-IronPort-AV: E=McAfee;i="6000,8403,9685"; a="151079553"
X-IronPort-AV: E=Sophos;i="5.75,366,1589266800";
   d="scan'208";a="151079553"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga006.fm.intel.com ([10.253.24.20])
  by orsmga102.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 17 Jul 2020 23:39:00 -0700
IronPort-SDR: 
 WqBGYgKWUBAFm9qTIPSxn35YWrWClTpoBhdGM4JL6q7BDnxWQbuQ5EZQ6LUvWOyYLPpnOrth1y
 wIfRME2nTG3A==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,366,1589266800";
   d="scan'208";a="486690949"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.152])
  by fmsmga006.fm.intel.com with ESMTP; 17 Jul 2020 23:39:00 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH 1/7] KVM: x86: Add RIP to the kvm_entry, i.e. VM-Enter,
 tracepoint
Date: Fri, 17 Jul 2020 23:38:48 -0700
Message-Id: <20200718063854.16017-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
In-Reply-To: <20200718063854.16017-1-sean.j.christopherson@intel.com>
References: <20200718063854.16017-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add RIP to the kvm_entry tracepoint to help debug if the kvm_exit
tracepoint is disable or if VM-Enter fails, in which case the kvm_exit
tracepoint won't be hit.

Read RIP from within the tracepoint itself to avoid a potential VMREAD
and retpoline if the guest's RIP isn't available.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/trace.h | 10 ++++++----
 arch/x86/kvm/x86.c   |  2 +-
 2 files changed, 7 insertions(+), 5 deletions(-)

```
#### [PATCH] linux/mdev.h: drop duplicated word in a commentTo: LKML <linux-kernel@vger.kernel.org>,
##### From: Randy Dunlap <rdunlap@infradead.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Randy Dunlap <rdunlap@infradead.org>
X-Patchwork-Id: 11671547
Return-Path: <SRS0=CTxd=A5=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E3D1F138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 18 Jul 2020 02:53:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CAAD12070E
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 18 Jul 2020 02:53:42 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=infradead.org header.i=@infradead.org header.b="dyRxCxkB"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728890AbgGRCxi (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 17 Jul 2020 22:53:38 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:45800 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726262AbgGRCxi (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 17 Jul 2020 22:53:38 -0400
Received: from merlin.infradead.org (merlin.infradead.org
 [IPv6:2001:8b0:10b:1231::1])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 0E5DEC0619D2;
        Fri, 17 Jul 2020 19:53:38 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; q=dns/txt; c=relaxed/relaxed;
        d=infradead.org; s=merlin.20170209;
 h=Content-Transfer-Encoding:Content-Type:
        MIME-Version:Date:Message-ID:To:Subject:From:Sender:Reply-To:Cc:Content-ID:
        Content-Description:In-Reply-To:References;
        bh=+ZE3FpDlcsZJaSCdlANHvwXhVh4c14KCBuPZ5HWYZG8=;
 b=dyRxCxkBtOX+Fcxvh5psUO8Jp0
        Mk7hADTBD9vus9AOajZuiBFIWnXFGV9ZO72ufZLNJS1DIdqTc0zmyBWhWM1WjkD3rclwgxcLYrxDi
        6YxBoXfeDvMcTd/CmuL1yIZhvdLh+trfgsp+PjcUMppOZqunQ5eK46/T4DUhhdFRrVIGCDanz8bF1
        fpDy8jHykSyG7AQccpX4MP9cwReE8QqhC2Auy8nhYtaqVScTiWBDQ7V+gRw9EarxpO9yr6Q4WlVud
        wg3IZWYcADjvqio6ne1RnpZluznfQZuM9RkvIRDYjGoMOSadTF90paefHRoqm4/LGYzMJumKlrlLr
        A0dRVrWQ==;
Received: from [2601:1c0:6280:3f0::19c2]
        by merlin.infradead.org with esmtpsa (Exim 4.92.3 #3 (Red Hat Linux))
        id 1jwcyl-0006lP-0Q; Sat, 18 Jul 2020 02:53:35 +0000
From: Randy Dunlap <rdunlap@infradead.org>
Subject: [PATCH] linux/mdev.h: drop duplicated word in a comment
To: LKML <linux-kernel@vger.kernel.org>,
        Kirti Wankhede <kwankhede@nvidia.com>,
        KVM <kvm@vger.kernel.org>
Message-ID: <ae55d252-04e9-843c-94a9-5a211c247718@infradead.org>
Date: Fri, 17 Jul 2020 19:53:31 -0700
User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:68.0) Gecko/20100101
 Thunderbird/68.9.0
MIME-Version: 1.0
Content-Language: en-US
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Randy Dunlap <rdunlap@infradead.org>

Drop the doubled word "a" in a comment.

Signed-off-by: Randy Dunlap <rdunlap@infradead.org>
Cc: Kirti Wankhede <kwankhede@nvidia.com>
Cc: kvm@vger.kernel.org
---
 include/linux/mdev.h |    2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

--- linux-next-20200714.orig/include/linux/mdev.h
+++ linux-next-20200714/include/linux/mdev.h
@@ -42,7 +42,7 @@ struct device *mdev_get_iommu_device(str
  *			@mdev: mdev_device structure on of mediated device
  *			      that is being created
  *			Returns integer: success (0) or error (< 0)
- * @remove:		Called to free resources in parent device's driver for a
+ * @remove:		Called to free resources in parent device's driver for
  *			a mediated device. It is mandatory to provide 'remove'
  *			ops.
  *			@mdev: mdev_device device structure which is being
```
