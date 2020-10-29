#### [PATCH 1/4] configure: Add a --enable-debug-kvm option to configureReferences: <5F97FD61.4060804@huawei.com> <5F991331.4020604@huawei.com>
##### From: AlexChen <alex.chen@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: AlexChen <alex.chen@huawei.com>
X-Patchwork-Id: 11863695
Return-Path: <SRS0=Fh8n=ED=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.2 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_SANE_1 autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E9C83C56202
	for <kvm@archiver.kernel.org>; Wed, 28 Oct 2020 22:29:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9E2C420720
	for <kvm@archiver.kernel.org>; Wed, 28 Oct 2020 22:29:02 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2387495AbgJ1W3B (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 28 Oct 2020 18:29:01 -0400
Received: from szxga04-in.huawei.com ([45.249.212.190]:6703 "EHLO
        szxga04-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2387485AbgJ1W27 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 28 Oct 2020 18:28:59 -0400
Received: from DGGEMS407-HUB.china.huawei.com (unknown [172.30.72.59])
        by szxga04-in.huawei.com (SkyGuard) with ESMTP id 4CLfrV41sFzkbRj;
        Wed, 28 Oct 2020 15:11:38 +0800 (CST)
Received: from [10.174.187.138] (10.174.187.138) by
 DGGEMS407-HUB.china.huawei.com (10.3.19.207) with Microsoft SMTP Server id
 14.3.487.0; Wed, 28 Oct 2020 15:11:26 +0800
Message-ID: <5F99199D.2020601@huawei.com>
Date: Wed, 28 Oct 2020 15:11:25 +0800
From: AlexChen <alex.chen@huawei.com>
User-Agent: Mozilla/5.0 (Windows NT 6.2; WOW64;
 rv:17.0) Gecko/20130509 Thunderbird/17.0.6
MIME-Version: 1.0
To: <pbonzini@redhat.com>, <chenhc@lemote.com>, <pasic@linux.ibm.com>,
        <borntraeger@de.ibm.com>, <mtosatti@redhat.com>,
        <cohuck@redhat.com>
CC: <kvm@vger.kernel.org>, <qemu-devel@nongnu.org>,
        <qemu-s390x@nongnu.org>, <zhengchuan@huawei.com>,
        <zhang.zhanghailiang@huawei.com>
Subject: [PATCH 1/4] configure: Add a --enable-debug-kvm option to configure
References: <5F97FD61.4060804@huawei.com> <5F991331.4020604@huawei.com>
In-Reply-To: <5F991331.4020604@huawei.com>
X-Originating-IP: [10.174.187.138]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch allows CONFIG_DEBUG_KVM to be defined when passing
an option to the configure script.

Signed-off-by: AlexChen <alex.chen@huawei.com>
---
 configure | 10 ++++++++++
 1 file changed, 10 insertions(+)

```
