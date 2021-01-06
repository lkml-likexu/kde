#### [PATCH] arm64/smp: Remove unused variable irq in arch_show_interrupts()
##### From: Keqian Zhu <zhukeqian1@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Keqian Zhu <zhukeqian1@huawei.com>
X-Patchwork-Id: 11998427
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B0C4AC433DB
	for <kvm@archiver.kernel.org>; Tue,  5 Jan 2021 09:23:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6705E20756
	for <kvm@archiver.kernel.org>; Tue,  5 Jan 2021 09:23:52 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727942AbhAEJXg (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 5 Jan 2021 04:23:36 -0500
Received: from szxga04-in.huawei.com ([45.249.212.190]:9715 "EHLO
        szxga04-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725860AbhAEJXe (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 5 Jan 2021 04:23:34 -0500
Received: from DGGEMS410-HUB.china.huawei.com (unknown [172.30.72.60])
        by szxga04-in.huawei.com (SkyGuard) with ESMTP id 4D96Sc6ynhzl16w;
        Tue,  5 Jan 2021 17:21:36 +0800 (CST)
Received: from DESKTOP-5IS4806.china.huawei.com (10.174.184.42) by
 DGGEMS410-HUB.china.huawei.com (10.3.19.210) with Microsoft SMTP Server id
 14.3.498.0; Tue, 5 Jan 2021 17:22:38 +0800
From: Keqian Zhu <zhukeqian1@huawei.com>
To: <linux-kernel@vger.kernel.org>,
        <linux-arm-kernel@lists.infradead.org>, <kvm@vger.kernel.org>,
        <kvmarm@lists.cs.columbia.edu>, Marc Zyngier <maz@kernel.org>,
        Will Deacon <will@kernel.org>,
        Mark Rutland <mark.rutland@arm.com>,
        Catalin Marinas <catalin.marinas@arm.com>
CC: Robin Murphy <robin.murphy@arm.com>,
        Joerg Roedel <joro@8bytes.org>,
        "James Morse" <james.morse@arm.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        <wanghaibin.wang@huawei.com>, Keqian Zhu <zhukeqian1@huawei.com>
Subject: [PATCH] arm64/smp: Remove unused variable irq in
 arch_show_interrupts()
Date: Tue, 5 Jan 2021 17:22:21 +0800
Message-ID: <20210105092221.15144-1-zhukeqian1@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.184.42]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The local variable irq is added in commit a26388152531 ("arm64:
Remove custom IRQ stat accounting"), but forget to remove in
commit 5089bc51f81f ("arm64/smp: Use irq_desc_kstat_cpu() in
arch_show_interrupts()"). Just remove it.

Signed-off-by: Keqian Zhu <zhukeqian1@huawei.com>
---
 arch/arm64/kernel/smp.c | 1 -
 1 file changed, 1 deletion(-)

```
#### [PATCH 1/2] Enumerate AVX Vector Neural Network instructions
##### From: Yang Zhong <yang.zhong@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Zhong <yang.zhong@intel.com>
X-Patchwork-Id: 11997967
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7BE11C433DB
	for <kvm@archiver.kernel.org>; Tue,  5 Jan 2021 01:42:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 57BCA22597
	for <kvm@archiver.kernel.org>; Tue,  5 Jan 2021 01:42:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727437AbhAEBmo (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 4 Jan 2021 20:42:44 -0500
Received: from mga03.intel.com ([134.134.136.65]:49891 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726026AbhAEBmn (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 4 Jan 2021 20:42:43 -0500
IronPort-SDR: 
 o8EyXBT9FLYg5TIhIb7erlK/i4Nr4NjCU+wsaRkLnZY4XDBo89igUI33SdGQ7rhVic/zaZU2vT
 r8+WAHdrWLog==
X-IronPort-AV: E=McAfee;i="6000,8403,9854"; a="177136727"
X-IronPort-AV: E=Sophos;i="5.78,475,1599548400";
   d="scan'208";a="177136727"
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by orsmga103.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 04 Jan 2021 17:42:02 -0800
IronPort-SDR: 
 Lq7r08yZwWLomQl0e7IrS4PvGvQ1H4hP/p5SEdnZFv6sJRhETI8ZJxPqa47zDoonhmWPuacX4V
 Anm3WH1KcqUg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.78,475,1599548400";
   d="scan'208";a="350166571"
Received: from icx-2s.bj.intel.com ([10.240.192.119])
  by fmsmga008.fm.intel.com with ESMTP; 04 Jan 2021 17:41:59 -0800
From: Yang Zhong <yang.zhong@intel.com>
To: linux-kernel@vger.kernel.org, x86@kernel.org, kvm@vger.kernel.org
Cc: tglx@linutronix.de, mingo@redhat.com, bp@alien8.de, hpa@zytor.com,
        tony.luck@intel.com, pbonzini@redhat.com, seanjc@google.com,
        vkuznets@redhat.com, wanpengli@tencent.com, jmattson@google.com,
        joro@8bytes.org, kyung.min.park@intel.com, yang.zhong@intel.com
Subject: [PATCH 1/2] Enumerate AVX Vector Neural Network instructions
Date: Tue,  5 Jan 2021 08:49:08 +0800
Message-Id: <20210105004909.42000-2-yang.zhong@intel.com>
X-Mailer: git-send-email 2.29.2.334.gfaefdd61ec
In-Reply-To: <20210105004909.42000-1-yang.zhong@intel.com>
References: <20210105004909.42000-1-yang.zhong@intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Kyung Min Park <kyung.min.park@intel.com>

Add AVX version of the Vector Neural Network (VNNI) Instructions.

A processor supports AVX VNNI instructions if CPUID.0x07.0x1:EAX[4] is
present. The following instructions are available when this feature is
present.
  1. VPDPBUS: Multiply and Add Unsigned and Signed Bytes
  2. VPDPBUSDS: Multiply and Add Unsigned and Signed Bytes with Saturation
  3. VPDPWSSD: Multiply and Add Signed Word Integers
  4. VPDPWSSDS: Multiply and Add Signed Integers with Saturation

The only in-kernel usage of this is kvm passthrough. The CPU feature
flag is shown as "avx_vnni" in /proc/cpuinfo.

This instruction is currently documented in the latest "extensions"
manual (ISE). It will appear in the "main" manual (SDM) in the future.

Signed-off-by: Kyung Min Park <kyung.min.park@intel.com>
Signed-off-by: Yang Zhong <yang.zhong@intel.com>
Reviewed-by: Tony Luck <tony.luck@intel.com>
Acked-by: Borislav Petkov <bp@suse.de>
---
 arch/x86/include/asm/cpufeatures.h | 1 +
 1 file changed, 1 insertion(+)

```
#### [GIT PULL] vhost: bugfix
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 11998731
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,INCLUDES_PULL_REQUEST,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 8A956C433E9
	for <kvm@archiver.kernel.org>; Tue,  5 Jan 2021 12:23:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 416CB229C4
	for <kvm@archiver.kernel.org>; Tue,  5 Jan 2021 12:23:38 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728438AbhAEMXT (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 5 Jan 2021 07:23:19 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:20434 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728381AbhAEMXS (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 5 Jan 2021 07:23:18 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1609849312;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type;
        bh=U39k5ipMHANWOJWrOXSYV59iZX09Ei6dL9ebZb8Ogeg=;
        b=h0lLt4/Tksg6sI88+7rwPMzNQCYPJcQNpokcL+CsnYogR/Knm6EeB1j/rMH0Xv7n/UlUQX
        LlkU39FznW/EwWqgsRi0jFX8bk+O+VXF0sqjFU3xTMPuUBN4p4SuN8NmJrzE+D7PpMZsIo
        x0Aay4OYfwQIX3GQJGqZpcZNh9OuCUg=
Received: from mail-wm1-f69.google.com (mail-wm1-f69.google.com
 [209.85.128.69]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-522-iKMYHQx1P2SVWYte9haiLA-1; Tue, 05 Jan 2021 07:21:51 -0500
X-MC-Unique: iKMYHQx1P2SVWYte9haiLA-1
Received: by mail-wm1-f69.google.com with SMTP id f187so1179176wme.3
        for <kvm@vger.kernel.org>; Tue, 05 Jan 2021 04:21:50 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:mime-version
         :content-disposition;
        bh=U39k5ipMHANWOJWrOXSYV59iZX09Ei6dL9ebZb8Ogeg=;
        b=PK4A1etEJ5mp6VSTjiet4uH9j8vzc4upDrqPkTxLopjVTcB0y5U55eU28m6tVDucxB
         u4zrrgjZB6uY1TU9FdktnsHWSD8WaSY9WPUox8dm+OHGVci71qjjyPEOIIusEWkmHJYp
         U8kiQ54gfPlWK+QvXNY9byNFo1+QYZEv4vjlo1h1vvH2o/ZefcOb15Yw+ilvXNGnSo2A
         tbEUxlWRjKI8CldySKl0dyqXE8PXjwBriZtLRHybEQe/TUwwfsvyQDsB8LHZdqgIIoj7
         Xy5mJO6HLhJY7mGubUIU9Ub4ldF5/bWRGCXD63aYckwVPtHf4zgzYNOcJS6UTXXf+DpJ
         tj2A==
X-Gm-Message-State: AOAM5307LMcSNhlqdABQydwtB103p2mD3H0/GbTNhou3XDWlo8aKdJw8
        fVL4B50ih3nmn/idqxDxQ19ZyEKrGSOJAG8ijNV7LhAIWZWnsYWy/hWzaS2xmd33qJitE9KXJV/
        r6rnMpwBIAVTx
X-Received: by 2002:adf:bb0e:: with SMTP id
 r14mr85949740wrg.159.1609849309287;
        Tue, 05 Jan 2021 04:21:49 -0800 (PST)
X-Google-Smtp-Source: 
 ABdhPJxRxC04NYGeb6WaL98Uxtwkp2M43zTcBL2qoRpI0IP4stOIB1HKct8R0XtAhgJEy1jrpROFhg==
X-Received: by 2002:adf:bb0e:: with SMTP id
 r14mr85949711wrg.159.1609849308953;
        Tue, 05 Jan 2021 04:21:48 -0800 (PST)
Received: from redhat.com (bzq-79-178-32-166.red.bezeqint.net.
 [79.178.32.166])
        by smtp.gmail.com with ESMTPSA id
 y7sm3716921wmb.37.2021.01.05.04.21.47
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 05 Jan 2021 04:21:48 -0800 (PST)
Date: Tue, 5 Jan 2021 07:21:45 -0500
From: "Michael S. Tsirkin" <mst@redhat.com>
To: Linus Torvalds <torvalds@linux-foundation.org>
Cc: kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org, linux-kernel@vger.kernel.org,
        jasowang@redhat.com, mst@redhat.com, sgarzare@redhat.com
Subject: [GIT PULL] vhost: bugfix
Message-ID: <20210105072145-mutt-send-email-mst@kernel.org>
MIME-Version: 1.0
Content-Disposition: inline
X-Mutt-Fcc: =sent
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The following changes since commit 418eddef050d5f6393c303a94e3173847ab85466:

  vdpa: Use simpler version of ida allocation (2020-12-18 16:14:31 -0500)

are available in the Git repository at:

  https://git.kernel.org/pub/scm/linux/kernel/git/mst/vhost.git tags/for_linus

for you to fetch changes up to e13a6915a03ffc3ce332d28c141a335e25187fa3:

  vhost/vsock: add IOTLB API support (2020-12-27 05:49:01 -0500)

----------------------------------------------------------------
vhost: bugfix

This fixes configs with vhost vsock behind a viommu.

Signed-off-by: Michael S. Tsirkin <mst@redhat.com>

----------------------------------------------------------------
Stefano Garzarella (1):
      vhost/vsock: add IOTLB API support

 drivers/vhost/vsock.c | 68 ++++++++++++++++++++++++++++++++++++++++++++++++---
 1 file changed, 65 insertions(+), 3 deletions(-)
```
#### [PATCH v3 1/3] KVM: SVM: use vmsave/vmload for saving/restoring additional host state
##### From: Michael Roth <michael.roth@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Michael Roth <michael.roth@amd.com>
X-Patchwork-Id: 11999161
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 26F48C433E9
	for <kvm@archiver.kernel.org>; Tue,  5 Jan 2021 14:39:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DCC7022BED
	for <kvm@archiver.kernel.org>; Tue,  5 Jan 2021 14:39:57 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727559AbhAEOjn (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 5 Jan 2021 09:39:43 -0500
Received: from mail-bn8nam11hn2203.outbound.protection.outlook.com
 ([52.100.171.203]:62816
        "EHLO NAM11-BN8-obe.outbound.protection.outlook.com"
        rhost-flags-OK-FAIL-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726352AbhAEOjl (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 5 Jan 2021 09:39:41 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=ABzoZnkbzlXcT4n4ucU2KP5/p8S2o501uOiozV/w6BJwyXea+NrHBuyjiMo7BYBvtN5j3u2J1vTErjXfnIsWH0OBlEzbUCSPKOWqacTPa/WX4HjbLXEkekGhnZcRYYx4WtKoNVpbMOAcxA2wU+Y+D69UCDp2VVLoZwwyphCjrbDzUxMgkCjZxZQlASdKxJ9NTbXS9Veawny0ZoYGDB1wpNEWKyWl0U2hjaIEJ1bVjRD7Y0MxP8PJA02sf4xClYw9oIQwbLQo1H8WUVwsvBB7lmAKFDSL+/FtBSCRwMIAA12tIXpFMN8m+IOaxjyCCr2OD4NK7LUk5PAjULQ97gyhjQ==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=ASThIUSUvobyLczmMW3lew/MzA6MTfONcQv8fMoHdRA=;
 b=XtC5cpfqa1O+kO4viffEMWwn6r+x7apPUiW1Y2j+RlfO++8df9nmnA3yuv64t+kJjaHoAiNtscyuyMC6xSI498RqNBKdXiyDXhb6PUs7o8cLYnyhhPdn5IggHtwqIHkcTx9rdMy8nsLJ+DJEagdbMatzqo5JZs/6ZI3/FiK5MQA8nOTVemDGTWoKn7jqm3BFiIELnlNfTp/KNHpBQmvDSrRk74jFypMRM1dhx8s+V9mkFiIG8B360LRUNCUNPHOX94kcb1wrpLkDo2htEguX2Rfzt3X7yCotwSIm1vATRWOSQaf0rYI4A+XzUmJLxl69vvLvWXdrcTAIu9iipPCQdQ==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=ASThIUSUvobyLczmMW3lew/MzA6MTfONcQv8fMoHdRA=;
 b=Z0E3dX9XswRuhVRpKB9VXsWQR0ugEwWdDZ6NScxoYNwiEWtTQkMLqZcobzHJhK+kYlB84aGsQqXBA2iLcB97jGKsQFzS4WF0U74LIt/mZ+wz9oYhZ3kxULCJpV+YIG+GnppMBmv347rLC04/l+LjrrFQadwBTdwsM/AjzEDuC+o=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=amd.com;
Received: from CH2PR12MB4133.namprd12.prod.outlook.com (2603:10b6:610:7a::13)
 by CH2PR12MB4134.namprd12.prod.outlook.com (2603:10b6:610:a7::15) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3721.19; Tue, 5 Jan
 2021 14:38:52 +0000
Received: from CH2PR12MB4133.namprd12.prod.outlook.com
 ([fe80::b965:3158:a370:d81e]) by CH2PR12MB4133.namprd12.prod.outlook.com
 ([fe80::b965:3158:a370:d81e%7]) with mapi id 15.20.3721.024; Tue, 5 Jan 2021
 14:38:52 +0000
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
Subject: [PATCH v3 1/3] KVM: SVM: use vmsave/vmload for saving/restoring
 additional host state
Date: Tue,  5 Jan 2021 08:37:48 -0600
Message-Id: <20210105143749.557054-2-michael.roth@amd.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20210105143749.557054-1-michael.roth@amd.com>
References: <20210105143749.557054-1-michael.roth@amd.com>
X-Originating-IP: [165.204.54.211]
X-ClientProxiedBy: YT1PR01CA0077.CANPRD01.PROD.OUTLOOK.COM
 (2603:10b6:b01:2d::16) To CH2PR12MB4133.namprd12.prod.outlook.com
 (2603:10b6:610:7a::13)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from localhost (165.204.54.211) by
 YT1PR01CA0077.CANPRD01.PROD.OUTLOOK.COM (2603:10b6:b01:2d::16) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3742.6 via Frontend
 Transport; Tue, 5 Jan 2021 14:38:51 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: b5b973be-a9a8-417b-2849-08d8b1879f58
X-MS-TrafficTypeDiagnostic: CH2PR12MB4134:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <CH2PR12MB413444E136437AC679D946BA95D10@CH2PR12MB4134.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:10000;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 Z4F0wG4GjTmZX2A84dkPJS6qH94KOLLA3ZXZV7ncj77XDhFeJHjr/0H2pppQf9xStNKOG+0CYO5+24SiOalcBniuw6w3Ncg6+BxiJwgpzVg0+yuxlkw2E6pUajMXvsH+CEWqvGfbam1oYRZdGUwUO7OyfnqAflTaNSNTdaOErXr3bWvLmcGcWwqmbG2ZL/zmNXkjpqpEslHdXk50W+jlCf4lnAzyK9wGgGFnUiTwj58Fr2vpSvW3OXssqLgkcwL8xEL2Jj2Cw2Jp0RCf/KpKLP3lUWPc0OnyjLjU69ogKnOUEp0ephLwkQme9VWcyYxPrc9GkwFxNPdB4/Q1LZNq20O5eMqx5MHX5Fe2UqQJ696AA4egJGnBlljlwX1IaP/VxrK2uC6Vhg/8CDrm0DSkX9Qf8C++RvSs8wuKR7bhF2XJrPuWbuaNHVSYYqDVaO832sSGKXK60lGqwFxl16jcvydmg8ODt315uFoL23Ao++Qu7fJDgBCBP2EEivnAdJvCL6noI9wwM9XD1i6rT0coAUwASlGbS1+nhHcWH9tmulysjY6L9NVS/RaQcVkZwSatLwyTzfIWuesF7dseuHC9jmQdfrIcb/oWGn9htnR9Xz9bixSP9+y+skG0OEYAIxQ1krHgAJ6Fkyt7CGVA/DbZ0Zmm417kT7GITUVFPrLUJ+WM6ND6l0DgOsMZ2slESL9aBg8OCgO4nPB6fw4HsD2shLKAukLUeKeZgc05aIrc9HkX5GksxgEaNTNxryjmRm1B
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:5;SRV:;IPV:NLI;SFV:SPM;H:CH2PR12MB4133.namprd12.prod.outlook.com;PTR:;CAT:OSPM;SFS:(4636009)(376002)(346002)(136003)(396003)(366004)(39860400002)(6496006)(52116002)(16526019)(956004)(2616005)(66946007)(54906003)(186003)(6916009)(2906002)(6486002)(26005)(86362001)(8936002)(1076003)(44832011)(4326008)(5660300002)(7416002)(83380400001)(478600001)(66556008)(316002)(6666004)(8676002)(66476007)(36756003)(23200700001);DIR:OUT;SFP:1501;
X-MS-Exchange-AntiSpam-MessageData: 
 NapcsAcj0ohY60L4g30hwf5YlJ0UzKvThiBmgEMTEPFlkrsR4JOy2DuxNeosKbJ4QTSbY1pwb5FdV8XUy9LB9/gcyiot5WzpIRWQGuQdsNSa7pzk0KDyKT2Sd5I+KIPrtkpAtnodlTZ/EmS9rvgO0G3KLPQjTKJFK+wTRk9Ro3FGc9a5/tD6g3Ji/Tl8QK63XTpcVO0ahNtD88/OPjpiSkwf638RAg1WRJh0XgwRQdHML8AGhkthhS6CMdY0D/1NBy2hX39F4342CCsQAOSfAg2YyeBMMaNAhCLHadd+iZfRFP4zlaN/3mHWZboRAQeVLfJXxVSeF8s1RzG55YqBwPvCZussRSUtn8B6jt/F+4PALC5dsEqHhJlz3H901DCwnNRWPXe5v29/3MSh9TRrYiUdfKdZo8yGCEOAjMqbcFJlHGe2SZNvRATjNAI+xNj5t3MXDEybzCR+rf+07QJLjm3nqzD6X7L2gC7iuTCNSVX39y854kcO+gOFAfWOZQqhhvkz6XcgVPCpAL9ztjh4AG+UQ+8PIshZ8uBhFtjtGWfal4PkWWu4RT6YiT9dnbVKz2Cxgy+6RLU0JKhxXYIn9CiWyEQ9QanB3PGUldFzdwn4bqfmHhFfjD+HLpq+vZ0exNxOJ9MYwHqP3aQzINX8GiLBJ/u6j+JsJTlf89hOm9Wn+NnduRdqlK2seG1JbCJkMpmPpfv0OvVDiy5k7kwlOrobHD6vtN1mZ9qLe1ezGrUw3LlziA1jAGUTkh5OrzoNiJi2bGNowgcZO072ONTvqY7P7I0Fv+ZtAJrGpgB0m7jSdWeUB5MjVNRmQd2RV18rbQzMARZAyWh7Phgy0+PZbY7pBrBbGbxqtNFgpGIUeVM7BCM90WcCv+hKR7/V3XZW00ARao4WxafF9gzHwBzSw9rAfNRvMJscOKULIhy3cBS4JOw0+NP2K3cJ/CyglY3gGBmU/YWNY9UOb7yxtx3zstfYWskIWjDUA1doSk2VZQy/+mo1aNn8mxSe03+Cvs1l
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-AuthSource: CH2PR12MB4133.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 05 Jan 2021 14:38:52.3677
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 b5b973be-a9a8-417b-2849-08d8b1879f58
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 QhbTViAdXONf6m2FfWfSGr7Ca/GuCaW8oeWVKAp3TbTfFwf++qGLkhjCGuI3W+J/C7VklBRZ7sq1TNMXFUXFDw==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: CH2PR12MB4134
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
 arch/x86/kvm/svm/svm.c     | 36 +++++++-----------------------------
 arch/x86/kvm/svm/svm.h     | 19 +------------------
 arch/x86/kvm/svm/vmenter.S | 10 ++++++++++
 3 files changed, 18 insertions(+), 47 deletions(-)

```
#### [PATCH] Revert "KVM: x86: Unconditionally enable irqs in guest context"
##### From: Nitesh Narayan Lal <nitesh@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Nitesh Narayan Lal <nitesh@redhat.com>
X-Patchwork-Id: 12000249
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 477DFC433DB
	for <kvm@archiver.kernel.org>; Tue,  5 Jan 2021 19:30:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0D62E22D6F
	for <kvm@archiver.kernel.org>; Tue,  5 Jan 2021 19:30:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730810AbhAETaS (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 5 Jan 2021 14:30:18 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:53350 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728230AbhAETaS (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 5 Jan 2021 14:30:18 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1609874932;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=Hugo6ZEFcgLqAbh5AX1tterJDrXPcf7pVF8nJ3VeGds=;
        b=IGeZ4KXY3hCxt6CDTXhcfTd8SFNpDn2tOdNkQ4iAo62kbpH9xUPM6TgEoz9mfKjnuw6ppM
        FtMhsE2wny07jy3Gu1RPHYh/WZEmWNmWi6ONkebGsVB30qVILjLIKCjCu4mrSCK2SQneXH
        P8Dfef5sB25rt0wq2XE6z3x8ZTydPdo=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-35-cyKzp4EYOGi4vuaXDDFyug-1; Tue, 05 Jan 2021 14:28:50 -0500
X-MC-Unique: cyKzp4EYOGi4vuaXDDFyug-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id E3166800D53;
        Tue,  5 Jan 2021 19:28:48 +0000 (UTC)
Received: from virtlab500.virt.lab.eng.bos.redhat.com
 (virtlab500.virt.lab.eng.bos.redhat.com [10.19.152.160])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 2A92D53C9F;
        Tue,  5 Jan 2021 19:28:45 +0000 (UTC)
From: Nitesh Narayan Lal <nitesh@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        seanjc@google.com, w90p710@gmail.com, pbonzini@redhat.com,
        vkuznets@redhat.com, nitesh@redhat.com
Subject: [PATCH] Revert "KVM: x86: Unconditionally enable irqs in guest
 context"
Date: Tue,  5 Jan 2021 14:28:44 -0500
Message-Id: <20210105192844.296277-1-nitesh@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This reverts commit d7a08882a0a4b4e176691331ee3f492996579534.

After the introduction of the patch:

	87fa7f3e9: x86/kvm: Move context tracking where it belongs

since we have moved guest_exit_irqoff closer to the VM-Exit, explicit
enabling of irqs to process pending interrupts should not be required
within vcpu_enter_guest anymore.

Conflicts:
	arch/x86/kvm/svm.c

Signed-off-by: Nitesh Narayan Lal <nitesh@redhat.com>
---
 arch/x86/kvm/svm/svm.c |  9 +++++++++
 arch/x86/kvm/x86.c     | 11 -----------
 2 files changed, 9 insertions(+), 11 deletions(-)

```
#### [PATCH v2] target/i386/sev: add support to query the attestation report
##### From: Brijesh Singh <brijesh.singh@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Brijesh Singh <brijesh.singh@amd.com>
X-Patchwork-Id: 11999763
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 3F297C433DB
	for <kvm@archiver.kernel.org>; Tue,  5 Jan 2021 16:41:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1223122CB2
	for <kvm@archiver.kernel.org>; Tue,  5 Jan 2021 16:41:21 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729897AbhAEQlH (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 5 Jan 2021 11:41:07 -0500
Received: from mail-dm6nam10on2069.outbound.protection.outlook.com
 ([40.107.93.69]:34305
        "EHLO NAM10-DM6-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1729878AbhAEQlH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 5 Jan 2021 11:41:07 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=jyyKzOFdP9cS01Or/CNvAJp/iE9I97KNj2+cRhqnfiHbw46ZrBYEj4oYOWn8gnNFOozm8r2mHN/fGNsEczm4M1ZE9rX4IDlNBqLd9oFfd9tzBJWonx1fbMjZNLG2IhN5Kd6cJtx/jZaUXXD1BQ62CgD7GEfJ3PKSxUu6VZgH5Yox23ksSTAdhacRx191UaiqVGcU4GYbj4LCkWVXK/Bfnur+0xuwBQre0ie6lIqvm0MoGtRWKw7waUOu4vo064jyAdjjccF0nnOUcRidZ+yeDaJrUH+400UubgGJLdTyOtB5tUgeugYUgCHYny/XhettBv5HAJ6q3kUIv0LuQNESdg==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=p/Nq6ERcvzdMzZjHNW8sKgBleQmIGLKc/KsoKWIOhMY=;
 b=FF09nivEQp9s8MPAZDdUbTlvauFYHprxC7vD7NL8IwjC3inS6jOpdJOmqSmIPbhPANVTlhoX8omsRoTfKS22M4woqWV8q8o1mPVXrfYPQhrNxIf+6tYdS3VohyAkv9jfm8Nm4BPKPN3UuPyCiRC1Up1zEWTvKNFouZXxH/Y257fUdLc/L78pg/CMwun/No5lrS7WUvxuf0CFdlHYzKqwLyEcI5GFfl5oTRrPXS3mAdkrrGNy/iWuYv2CSVOeJDdVK6Vucj3rvFA4vlJOHPuT7jsCJRMZ79r5txnctJfmvukHIePFD5zwq+oJ9HnCbXYYqoRTuHrb/MLduVY+zZs41g==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=p/Nq6ERcvzdMzZjHNW8sKgBleQmIGLKc/KsoKWIOhMY=;
 b=ZL2FU1Vz5vASiCkoYNcEf0Zi7Z8pfJqFrklWRunxtiocdzkrBN0Vannx4dxx4nwfQSga4PrKkUmnHNs7c9+rmkUnUNuhWEceubZxrqGYIsrNfvbFL7ab+zeJqQJ1pmbX5Ttd8UJ585goSVRI8dwhWkfxCLz0T7iblNmle/7yuNY=
Authentication-Results: nongnu.org; dkim=none (message not signed)
 header.d=none;nongnu.org; dmarc=none action=none header.from=amd.com;
Received: from SN6PR12MB2718.namprd12.prod.outlook.com (2603:10b6:805:6f::22)
 by SA0PR12MB4431.namprd12.prod.outlook.com (2603:10b6:806:95::11) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3721.20; Tue, 5 Jan
 2021 16:40:13 +0000
Received: from SN6PR12MB2718.namprd12.prod.outlook.com
 ([fe80::18a2:699:70b3:2b8a]) by SN6PR12MB2718.namprd12.prod.outlook.com
 ([fe80::18a2:699:70b3:2b8a%6]) with mapi id 15.20.3721.024; Tue, 5 Jan 2021
 16:40:13 +0000
From: Brijesh Singh <brijesh.singh@amd.com>
To: qemu-devel@nongnu.org
Cc: Brijesh Singh <brijesh.singh@amd.com>,
        James Bottomley <jejb@linux.ibm.com>,
        Tom Lendacky <Thomas.Lendacky@amd.com>,
        Eric Blake <eblake@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org
Subject: [PATCH v2] target/i386/sev: add support to query the attestation
 report
Date: Tue,  5 Jan 2021 10:39:42 -0600
Message-Id: <20210105163943.30510-1-brijesh.singh@amd.com>
X-Mailer: git-send-email 2.17.1
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: SN4PR0201CA0049.namprd02.prod.outlook.com
 (2603:10b6:803:20::11) To SN6PR12MB2718.namprd12.prod.outlook.com
 (2603:10b6:805:6f::22)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from sbrijesh-desktop.amd.com (165.204.77.1) by
 SN4PR0201CA0049.namprd02.prod.outlook.com (2603:10b6:803:20::11) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3742.6 via Frontend
 Transport; Tue, 5 Jan 2021 16:40:12 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 142e6d6e-c3cc-4ea8-384d-08d8b198930d
X-MS-TrafficTypeDiagnostic: SA0PR12MB4431:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SA0PR12MB44319E3BDF6878AFD21BCDE2E5D10@SA0PR12MB4431.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:1265;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 OYdiYNyoizsQe1EbeOct7ZsJettbtXu+kGhYBo4UEoCRKHDYgVhsbSkJcpTiUr+Bw0ok+ZdB4VdLG+QpWmkZ2QSjVV0jGqtP16Bc141n6prpFbc5bukXw9gHh8ZuEm9GXMJVxQc0uQo0z6lgQGrCerBFJgbc0P63L71oNO+Aw+EoJdtJ/zkrD/LTFZ9B9bERHsHOzYMLDyjuF6/lJR1qAsKt02BafEMS1EKr+qLEhTBRAi4AaqzZaAoeg6xnan4tFVRUBKzMplmJEG9sVCAvfRUD6rI3qsKIl2rDUWY4NURCSohl453TjQ/k1t96kLQ0Gb1HSgWJPmPf/r+Rl0Zsjoi+w29jNPcPULfPH51cEp2HYnXkTPQRx8g12sRB1NVVD9hKB4FR9C6m2YzgJIzX4w==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN6PR12MB2718.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(396003)(136003)(346002)(366004)(376002)(39850400004)(6666004)(316002)(66476007)(86362001)(2616005)(16526019)(26005)(6486002)(4326008)(8676002)(8936002)(2906002)(54906003)(83380400001)(36756003)(6916009)(52116002)(186003)(66556008)(7696005)(66946007)(5660300002)(478600001)(956004)(1076003)(44832011);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 8pxezmSwdLCH7/BmG7CCI5QNAjjI4hwqjWm0jsvL3cKvdrcqpraynw12B963fIVnTN3jDsMWLPmbmrWaLICeB//D3vLPNwWE0jMROBl9s7r5QO8tVSPVYQUiGUfRPHiLfqw6e1COtyCEYF86I9BKeBovefC6JciLFgWdU8RV+FbkB+fGGZbx0rIGYFOrn6LLKIfyQAqtsj1D61AIRgrE1zdbLTNFoXpeukvG+PHHKVjRastYfktGC5ykPAHzv2IynZ3BYsks0U5DURKw5hnLGaRd4mBQWRSSeR66uQoO71uHlPYzamzKRJ6IvgZSDsGkeSJYSXruW2RVuASem10Bqz0z+DrIrcGPZ7L3joq4pjTflhEiLPiLE8ILy4fX9ZaJ+jcZzuSARvnIDxCEnY7xwJdSVmNpXZjanuOl9NhWLRezEl5y+tbvMt1IN5e9EL43Nxhzp1/eAlawLrKtp5vIc/5kkozj+thmKx3JRcK7jWx6udKuu6766RP8fYAo6ZOJcvcSDKcw7crXgWlnMbK+2fjxI8/QwpA9ZynKQyWK3y8aSepXDhwOu9IWBjfjbD4KvbqvwtCihc8whM5jl8c+wOKmECQRYF1HxriHMDn5s5FPuhNtH73zb1bEflLVL+rCc5GG7Hz4J1opa9x2WQHYFJUTk/wUmQt8Vdel3wG1B03RA4tDl6qcT+a9+BjJAPe4fSoznWnmPpsK5G0hXG2ycw+4Co6fM10dzLylb5398FxxVeVUThkEIeEQtMNJkl56ANQut9kbv/PVhpFNXD272RV856JRegIUoxwphIPnfFbWzG0Nk2TjKMwDKqoOjdIJmZKQgDS7zZ5JEmUDd8M+DuP0vpNMMih+w+ozU1j+eKBkyV250JSewrF/DnNkz46ebeQMwz+X4oQBzPX84XVUdHzeCQNorEeaRElbSsL9ERpOZbU/3iamATItMzIOi1Wqy1Ku+5P3XfpXTL8AX1gN7WW/ZktUMJdEEDju+7EV4VfVaCN2q7wzgkwF8TckBCiw
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-AuthSource: SN6PR12MB2718.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 05 Jan 2021 16:40:13.2418
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 142e6d6e-c3cc-4ea8-384d-08d8b198930d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 yWsRJGt7YjtVzkFDD2XUH3WnO/QVU0p0h3tZ5+mcxSc1Hdet1/LS4PQUzH6IsJKr+oq4WGhW+Pr5mLsX9aZODw==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SA0PR12MB4431
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The SEV FW >= 0.23 added a new command that can be used to query the
attestation report containing the SHA-256 digest of the guest memory
and VMSA encrypted with the LAUNCH_UPDATE and sign it with the PEK.

Note, we already have a command (LAUNCH_MEASURE) that can be used to
query the SHA-256 digest of the guest memory encrypted through the
LAUNCH_UPDATE. The main difference between previous and this command
is that the report is signed with the PEK and unlike the LAUNCH_MEASURE
command the ATTESATION_REPORT command can be called while the guest
is running.

Add a QMP interface "query-sev-attestation-report" that can be used
to get the report encoded in base64.

Cc: James Bottomley <jejb@linux.ibm.com>
Cc: Tom Lendacky <Thomas.Lendacky@amd.com>
Cc: Eric Blake <eblake@redhat.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org
Signed-off-by: Brijesh Singh <brijesh.singh@amd.com>
Reviewed-by: James Bottomley <jejb@linux.ibm.com>
Tested-by: James Bottomley <jejb@linux.ibm.com>
---
v2:
  * add trace event.
  * fix the goto to return NULL on failure.
  * make the mnonce as a base64 encoded string

 linux-headers/linux/kvm.h |  8 +++++
 qapi/misc-target.json     | 38 ++++++++++++++++++++++
 target/i386/monitor.c     |  6 ++++
 target/i386/sev-stub.c    |  7 +++++
 target/i386/sev.c         | 66 +++++++++++++++++++++++++++++++++++++++
 target/i386/sev_i386.h    |  2 ++
 target/i386/trace-events  |  1 +
 7 files changed, 128 insertions(+)

```
#### [PATCH V1 1/5] vfio: maintain dma_list order
##### From: Steve Sistare <steven.sistare@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Steven Sistare <steven.sistare@oracle.com>
X-Patchwork-Id: 11999659
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-19.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	UNPARSEABLE_RELAY,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7E009C433DB
	for <kvm@archiver.kernel.org>; Tue,  5 Jan 2021 16:05:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4F14E22C9D
	for <kvm@archiver.kernel.org>; Tue,  5 Jan 2021 16:05:07 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726246AbhAEQEn (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 5 Jan 2021 11:04:43 -0500
Received: from aserp2130.oracle.com ([141.146.126.79]:40584 "EHLO
        aserp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725936AbhAEQEn (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 5 Jan 2021 11:04:43 -0500
Received: from pps.filterd (aserp2130.oracle.com [127.0.0.1])
        by aserp2130.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 105Fsji3094294;
        Tue, 5 Jan 2021 16:04:00 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references; s=corp-2020-01-29;
 bh=wlo2cVcl+/Th1nEAYhe73iPgHz0zOc5IAxfyoIhiGCE=;
 b=sdbrlKnvw3bc6Dyoey9JObZRK5QvDk9F1OehWrGc+Ytnv9+AZ9JqXbKeG5ai7nfwAWmW
 4HlImScCQPK8iKtsduCzrh2S8EVdHr5QfLtCO+0BFqLqRZH46V2XHCACXkdeKLzqI208
 dCdttiuzJpZZDwz8Dd0LLXOPyaNB0P5YvkdocOY1QKt3nor5se13gHcDIv62mvVe5U5f
 xyzTedyoXTMJUfhjjIdsOcGNI8DjBM1D0WEs4exJZcU0H+xowB0Yuv5Zzrm9J/Z5CfYm
 vFttUF7NmwBBvOtWn7MjzNHWvF2j/7GQUMHY2paF1/AXD3XgxOFpwP1VlmUWJOUdQIgm nA==
Received: from userp3030.oracle.com (userp3030.oracle.com [156.151.31.80])
        by aserp2130.oracle.com with ESMTP id 35tebasj32-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=FAIL);
        Tue, 05 Jan 2021 16:03:59 +0000
Received: from pps.filterd (userp3030.oracle.com [127.0.0.1])
        by userp3030.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 105FtL0a175884;
        Tue, 5 Jan 2021 16:03:59 GMT
Received: from userv0121.oracle.com (userv0121.oracle.com [156.151.31.72])
        by userp3030.oracle.com with ESMTP id 35vct61n8k-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 05 Jan 2021 16:03:59 +0000
Received: from abhmp0016.oracle.com (abhmp0016.oracle.com [141.146.116.22])
        by userv0121.oracle.com (8.14.4/8.13.8) with ESMTP id 105G3wQc015343;
        Tue, 5 Jan 2021 16:03:58 GMT
Received: from ca-dev63.us.oracle.com (/10.211.8.221)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Tue, 05 Jan 2021 16:03:58 +0000
From: Steve Sistare <steven.sistare@oracle.com>
To: kvm@vger.kernel.org
Cc: Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Kirti Wankhede <kwankhede@nvidia.com>,
        Steve Sistare <steven.sistare@oracle.com>
Subject: [PATCH V1 1/5] vfio: maintain dma_list order
Date: Tue,  5 Jan 2021 07:36:49 -0800
Message-Id: <1609861013-129801-2-git-send-email-steven.sistare@oracle.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1609861013-129801-1-git-send-email-steven.sistare@oracle.com>
References: <1609861013-129801-1-git-send-email-steven.sistare@oracle.com>
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9855
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 adultscore=0
 malwarescore=0
 phishscore=0 bulkscore=0 mlxlogscore=999 suspectscore=0 mlxscore=0
 spamscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2101050099
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9855
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=0
 phishscore=0
 priorityscore=1501 spamscore=0 mlxscore=0 clxscore=1011 bulkscore=0
 lowpriorityscore=0 impostorscore=0 mlxlogscore=999 adultscore=0
 malwarescore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2101050099
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Keep entries properly sorted in the dma_list rb_tree so that iterating
over multiple entries across a range with gaps works, without requiring
one to delete each visited entry as in vfio_dma_do_unmap.

Signed-off-by: Steve Sistare <steven.sistare@oracle.com>
Reported-by: kernel test robot <lkp@intel.com>
---
 drivers/vfio/vfio_iommu_type1.c | 18 +++++++++++-------
 1 file changed, 11 insertions(+), 7 deletions(-)

```
#### [RFC PATCH 2/7] vhost: support for hash report virtio-net feature
##### From: Yuri Benditovich <yuri.benditovich@daynix.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yuri Benditovich <yuri.benditovich@daynix.com>
X-Patchwork-Id: 11998733
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D21B9C433DB
	for <kvm@archiver.kernel.org>; Tue,  5 Jan 2021 12:26:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 95D0D229F0
	for <kvm@archiver.kernel.org>; Tue,  5 Jan 2021 12:26:05 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727995AbhAEMZk (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 5 Jan 2021 07:25:40 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:37332 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726602AbhAEMZk (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 5 Jan 2021 07:25:40 -0500
Received: from mail-wm1-x333.google.com (mail-wm1-x333.google.com
 [IPv6:2a00:1450:4864:20::333])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 91333C061798
        for <kvm@vger.kernel.org>; Tue,  5 Jan 2021 04:24:31 -0800 (PST)
Received: by mail-wm1-x333.google.com with SMTP id c133so2842232wme.4
        for <kvm@vger.kernel.org>; Tue, 05 Jan 2021 04:24:31 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=daynix-com.20150623.gappssmtp.com; s=20150623;
        h=from:to:cc:subject:date:message-id:in-reply-to:references;
        bh=95fcQ7XOzwxPXY92PHMXKGjY9iDFTd+3y3erYQ9GO9s=;
        b=iIG6RHpaEDCYDyHHaHHz5lfqneKL//162o6PaecyRMmpgqZZ5U5KUefBSFTnAGQi+R
         wqietjz3diqRGXleLo4HCy0fTHlUgUBSZ4kHjhT65Nrx9ckCvaqjWiDAqKCGMvNJos72
         fPOOnFKHjb9+rYcHOI6J73EafrnWkxZU1e+hM9c7kYg0Toh/jOYpWM9uSN1ePIsrOHdQ
         ZCB3nB0ECeEsFGdMh4nMnogIcT9zPeiTwG9At5oUkqW627rO+LCZZ1f9ZYn22xH+RxoJ
         qFBXGavyiC+ex0VSFxq+Y2baqg2Rfx1Fg6DMT1atmtOGPJ3aA/f8Z+CK2b3XcEvT/QXR
         SM4Q==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references;
        bh=95fcQ7XOzwxPXY92PHMXKGjY9iDFTd+3y3erYQ9GO9s=;
        b=t9YbfKSVj67zLLNnlW3jgERUSrl2UaT3/8WMOvFnqlKfNaOrsMYq1OKuC7wGGkTT5s
         CUJZvkDSyZ5EQYEV1Bb4DIkA4CARbz9p/1KuqwhJ5BmsLvf4UO7CbPTv0nllXJGZ5bYJ
         4CQVG1c3UgGT6JZTZeuPssuEl3FTYKf0Tm94Gw5N1GaCBrh9QKexi80N+z3P009xgtK4
         yvDh0uh55tJw+pC81oFW4IndtHuLmmklze/qlWGKKzCodTFJC4EbV/XEuPLAsU2uLHIC
         kohHFV6Z/f3FHfyZXnccwTD52q73fYey91KblV8hBAZmSFovxVj93MAHRloEuqEApEoo
         hhEQ==
X-Gm-Message-State: AOAM5301sJuC4E42t2cFnYPj9DpEhtHZy5fGwmkhpHu8ZLsDswWm2QnT
        es0ZR434axHA8LjwamSWu1ltQA==
X-Google-Smtp-Source: 
 ABdhPJzorTi7ks7HQy2lPJ0gpjzOHvfFV47zjsVnH3IZt0rAIvgZ6KHOYmU//Cm9oLOW/QQz86qGVg==
X-Received: by 2002:a1c:9c52:: with SMTP id f79mr3233640wme.3.1609849470379;
        Tue, 05 Jan 2021 04:24:30 -0800 (PST)
Received: from f2.redhat.com (bzq-79-183-72-147.red.bezeqint.net.
 [79.183.72.147])
        by smtp.gmail.com with ESMTPSA id
 138sm4242281wma.41.2021.01.05.04.24.29
        (version=TLS1_2 cipher=ECDHE-ECDSA-CHACHA20-POLY1305 bits=256/256);
        Tue, 05 Jan 2021 04:24:29 -0800 (PST)
From: Yuri Benditovich <yuri.benditovich@daynix.com>
To: "Michael S. Tsirkin" <mst@redhat.com>,
        Jason Wang <jasowang@redhat.com>
Cc: yan@daynix.com, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [RFC PATCH 2/7] vhost: support for hash report virtio-net feature
Date: Tue,  5 Jan 2021 14:24:11 +0200
Message-Id: <20210105122416.16492-3-yuri.benditovich@daynix.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20210105122416.16492-1-yuri.benditovich@daynix.com>
References: <20210105122416.16492-1-yuri.benditovich@daynix.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

According to the virtio specification if VIRTIO_NET_F_HASH_REPORT
feature acked the virtio-net header is extended to hold the hash
value and hash report type.

Signed-off-by: Yuri Benditovich <yuri.benditovich@daynix.com>
---
 drivers/vhost/net.c | 37 +++++++++++++++++++++++++++++--------
 1 file changed, 29 insertions(+), 8 deletions(-)

```
