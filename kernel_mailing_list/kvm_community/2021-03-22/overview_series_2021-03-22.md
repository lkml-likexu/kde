#### [PATCH 1/2] vfio/pci: remove vfio_pci_nvlink2
##### From: Christoph Hellwig <hch@lst.de>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christoph Hellwig <hch@lst.de>
X-Patchwork-Id: 12155091
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 2E2D3C433DB
	for <kvm@archiver.kernel.org>; Mon, 22 Mar 2021 15:05:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CD2586192E
	for <kvm@archiver.kernel.org>; Mon, 22 Mar 2021 15:05:10 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229890AbhCVPEi (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 22 Mar 2021 11:04:38 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:57062 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S231510AbhCVPEa (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 22 Mar 2021 11:04:30 -0400
Received: from casper.infradead.org (casper.infradead.org
 [IPv6:2001:8b0:10b:1236::1])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 70814C061574;
        Mon, 22 Mar 2021 08:04:30 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; q=dns/txt; c=relaxed/relaxed;
        d=infradead.org; s=casper.20170209;
 h=Content-Transfer-Encoding:MIME-Version:
        References:In-Reply-To:Message-Id:Date:Subject:Cc:To:From:Sender:Reply-To:
        Content-Type:Content-ID:Content-Description;
        bh=HHuVtAjN6un2JcueF0x5G8JDOHJ+C030gBx+oVSVxhU=;
 b=oLJ+8HoPiPfD7nD7XxxRrwam4h
        st1DWLaGS1XukkE1O033FZp19mzqQyzMzQiNm+EHojZSz7jW7t9xp45ImQaghS6blqC1YC5EJsrq2
        eyZ5ZWYEtN6FUF8mAWc7cFqfc54v9lyFk5oIA6TmC+K4+cwJ1RQPyTSgwZOOrBCPLmjqeisX/35Vd
        42Dbt0H4A8Kq1ajsHTjmQcWpDI5LBfHBY0gxPvuD++Rd/UPrOrZ72iKndlnZaZWmLtpcGnSVPtR7L
        IkLhfGEwWwcRDNJksiF8O6/bP2HUmYVOBceQy/6kVlfr4DFeFPJbKhuOUt3qpRx+cf/8r3ZCoZyTC
        0r3BAeUw==;
Received: from [2001:4bb8:191:f692:8c8d:c425:8476:e5e8] (helo=localhost)
        by casper.infradead.org with esmtpsa (Exim 4.94 #2 (Red Hat Linux))
        id 1lOM4S-008gVL-OR; Mon, 22 Mar 2021 15:02:28 +0000
From: Christoph Hellwig <hch@lst.de>
To: Michael Ellerman <mpe@ellerman.id.au>,
        Alex Williamson <alex.williamson@redhat.com>
Cc: Benjamin Herrenschmidt <benh@kernel.crashing.org>,
        Greg Kroah-Hartman <gregkh@linuxfoundation.org>,
        Jason Gunthorpe <jgg@nvidia.com>,
        David Airlie <airlied@linux.ie>,
        Daniel Vetter <daniel@ffwll.ch>,
        dri-devel@lists.freedesktop.org, Paul Mackerras <paulus@samba.org>,
        linuxppc-dev@lists.ozlabs.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, linux-api@vger.kernel.org
Subject: [PATCH 1/2] vfio/pci: remove vfio_pci_nvlink2
Date: Mon, 22 Mar 2021 16:01:54 +0100
Message-Id: <20210322150155.797882-2-hch@lst.de>
X-Mailer: git-send-email 2.30.1
In-Reply-To: <20210322150155.797882-1-hch@lst.de>
References: <20210322150155.797882-1-hch@lst.de>
MIME-Version: 1.0
X-SRS-Rewrite: SMTP reverse-path rewritten from <hch@infradead.org> by
 casper.infradead.org. See http://www.infradead.org/rpr.html
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This driver never had any open userspace (which for VFIO would include
VM kernel drivers) that use it, and thus should never have been added
by our normal userspace ABI rules.

Signed-off-by: Christoph Hellwig <hch@lst.de>
---
 drivers/vfio/pci/Kconfig            |   6 -
 drivers/vfio/pci/Makefile           |   1 -
 drivers/vfio/pci/vfio_pci.c         |  18 -
 drivers/vfio/pci/vfio_pci_nvlink2.c | 490 ----------------------------
 drivers/vfio/pci/vfio_pci_private.h |  14 -
 include/uapi/linux/vfio.h           |  40 ---
 6 files changed, 569 deletions(-)
 delete mode 100644 drivers/vfio/pci/vfio_pci_nvlink2.c

```
#### [PATCH v5 1/6] irqchip/gic-v3-its: Add a cache invalidation right after vPE unmapping
##### From: Shenming Lu <lushenming@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Shenming Lu <lushenming@huawei.com>
X-Patchwork-Id: 12153799
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 6748BC433E1
	for <kvm@archiver.kernel.org>; Mon, 22 Mar 2021 06:03:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2674D6196C
	for <kvm@archiver.kernel.org>; Mon, 22 Mar 2021 06:03:37 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230045AbhCVGDG (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 22 Mar 2021 02:03:06 -0400
Received: from szxga06-in.huawei.com ([45.249.212.32]:14422 "EHLO
        szxga06-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229547AbhCVGCf (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 22 Mar 2021 02:02:35 -0400
Received: from DGGEMS412-HUB.china.huawei.com (unknown [172.30.72.60])
        by szxga06-in.huawei.com (SkyGuard) with ESMTP id 4F3kQ05R0kzkdDb;
        Mon, 22 Mar 2021 14:00:56 +0800 (CST)
Received: from DESKTOP-7FEPK9S.china.huawei.com (10.174.184.135) by
 DGGEMS412-HUB.china.huawei.com (10.3.19.212) with Microsoft SMTP Server id
 14.3.498.0; Mon, 22 Mar 2021 14:02:24 +0800
From: Shenming Lu <lushenming@huawei.com>
To: Marc Zyngier <maz@kernel.org>, Eric Auger <eric.auger@redhat.com>,
        "Will Deacon" <will@kernel.org>,
        <linux-arm-kernel@lists.infradead.org>,
        <kvmarm@lists.cs.columbia.edu>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>
CC: Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Lorenzo Pieralisi <lorenzo.pieralisi@arm.com>,
        <wanghaibin.wang@huawei.com>, <yuzenghui@huawei.com>,
        <lushenming@huawei.com>
Subject: [PATCH v5 1/6] irqchip/gic-v3-its: Add a cache invalidation right
 after vPE unmapping
Date: Mon, 22 Mar 2021 14:01:53 +0800
Message-ID: <20210322060158.1584-2-lushenming@huawei.com>
X-Mailer: git-send-email 2.27.0.windows.1
In-Reply-To: <20210322060158.1584-1-lushenming@huawei.com>
References: <20210322060158.1584-1-lushenming@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.174.184.135]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Marc Zyngier <maz@kernel.org>

Since there may be a direct read from the CPU side to the VPT after
unmapping the vPE, we add a cache coherency maintenance at the end
of its_vpe_irq_domain_deactivate() to ensure the validity of the VPT
read later.

Signed-off-by: Marc Zyngier <maz@kernel.org>
Signed-off-by: Shenming Lu <lushenming@huawei.com>
---
 drivers/irqchip/irq-gic-v3-its.c | 9 +++++++++
 1 file changed, 9 insertions(+)

```
#### [PATCH kvm-unit-tests] arm/arm64: Zero BSS and stack at startup
##### From: Andrew Jones <drjones@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 12154667
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id F231AC433DB
	for <kvm@archiver.kernel.org>; Mon, 22 Mar 2021 12:12:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AAC5B61998
	for <kvm@archiver.kernel.org>; Mon, 22 Mar 2021 12:12:13 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229764AbhCVMLg (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 22 Mar 2021 08:11:36 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:37131 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S230046AbhCVMLE (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 22 Mar 2021 08:11:04 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1616415063;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=vnhtieZpahpelU+t3Df5KXSLUwwj4GJ8KlluqBDp3oc=;
        b=S7pSBBmACb9t51tuMntTID5q5Uw8D1hhr69qR+IipGTzqJeoXi7jwbknKLo89SsRKhbCef
        fUm0Z3XeUtNjtHbFjDHv464DEfkOfpsl2pzxx19BjXMi6b6qV/LoDK7zIzhQuiz0WGmdyC
        yNMSp8e8eDm8zFLqashPlk8XLwQWw6w=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-151-xpOtqZrDOA24SdXDiDh6_A-1; Mon, 22 Mar 2021 08:11:02 -0400
X-MC-Unique: xpOtqZrDOA24SdXDiDh6_A-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id CDF0680006E;
        Mon, 22 Mar 2021 12:11:00 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.40.194.23])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 7226317D85;
        Mon, 22 Mar 2021 12:10:59 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org
Cc: Nikos Nikoleris <nikos.nikoleris@arm.com>,
        Alexandru Elisei <alexandru.elisei@arm.com>
Subject: [PATCH kvm-unit-tests] arm/arm64: Zero BSS and stack at startup
Date: Mon, 22 Mar 2021 13:10:58 +0100
Message-Id: <20210322121058.62072-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

So far we've counted on QEMU or kvmtool implicitly zeroing all memory.
With our goal of eventually supporting bare-metal targets with
target-efi we should explicitly zero any memory we expect to be zeroed
ourselves. This obviously includes the BSS, but also the bootcpu's
stack, as the bootcpu's thread-info lives in the stack and may get
used in early setup to get the cpu index. Note, this means we still
assume the bootcpu's cpu index to be zero. That assumption can be
removed later.

Cc: Nikos Nikoleris <nikos.nikoleris@arm.com>
Cc: Alexandru Elisei <alexandru.elisei@arm.com>
Signed-off-by: Andrew Jones <drjones@redhat.com>
Reviewed-by: Nikos Nikoleris <nikos.nikoleris@arm.com>
---
 arm/cstart.S   | 22 ++++++++++++++++++++++
 arm/cstart64.S | 23 ++++++++++++++++++++++-
 arm/flat.lds   |  6 ++++++
 3 files changed, 50 insertions(+), 1 deletion(-)

```
#### [PATCH kvm-unit-tests v2] arm/arm64: Zero BSS and stack at startup
##### From: Andrew Jones <drjones@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 12155465
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 18601C433E2
	for <kvm@archiver.kernel.org>; Mon, 22 Mar 2021 16:28:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E2D4B619A0
	for <kvm@archiver.kernel.org>; Mon, 22 Mar 2021 16:28:24 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231852AbhCVQ1w (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 22 Mar 2021 12:27:52 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:25336 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S231846AbhCVQ1b (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 22 Mar 2021 12:27:31 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1616430449;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=hB4ao7MgBVQEa0+4DPXxKWvIIlNaPGOvZXTUciQhDGE=;
        b=IglHJyZrrvYrV56PXO2lQQcYTxnqI0n1FfxmmcbrYt34ANAD2qSQXZ/weBDuWAoSpzdict
        gIqtIwqa9g6Y94YM67eEBdz0z0miXjT8zLbe3WKn7HmcK8bgsv/DiJ8tSbOdNmM8U/Q4SE
        nENmoNxQ7EHvwbMi8ueqSDCWk3xyCIU=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-191-Hb1HaCVTMeuRLKHGoSJ0qQ-1; Mon, 22 Mar 2021 12:27:26 -0400
X-MC-Unique: Hb1HaCVTMeuRLKHGoSJ0qQ-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id F378E84BA43;
        Mon, 22 Mar 2021 16:27:24 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.40.194.23])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 368A35C1A3;
        Mon, 22 Mar 2021 16:27:23 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org
Cc: Nikos Nikoleris <nikos.nikoleris@arm.com>,
        Alexandru Elisei <alexandru.elisei@arm.com>
Subject: [PATCH kvm-unit-tests v2] arm/arm64: Zero BSS and stack at startup
Date: Mon, 22 Mar 2021 17:27:21 +0100
Message-Id: <20210322162721.108514-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

So far we've counted on QEMU or kvmtool implicitly zeroing all memory.
With our goal of eventually supporting bare-metal targets with
target-efi we should explicitly zero any memory we expect to be zeroed
ourselves. This obviously includes the BSS, but also the bootcpu's
stack, as the bootcpu's thread-info lives in the stack and may get
used in early setup to get the cpu index. Note, this means we still
assume the bootcpu's cpu index to be zero. That assumption can be
removed later.

Cc: Nikos Nikoleris <nikos.nikoleris@arm.com>
Cc: Alexandru Elisei <alexandru.elisei@arm.com>
Reviewed-by: Nikos Nikoleris <nikos.nikoleris@arm.com>
Signed-off-by: Andrew Jones <drjones@redhat.com>
---
 arm/cstart.S   | 20 ++++++++++++++++++++
 arm/cstart64.S | 22 +++++++++++++++++++++-
 arm/flat.lds   |  4 ++++
 3 files changed, 45 insertions(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH v2 1/6] arm64: Remove unnecessary ISB when writing to SPSel
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexandru Elisei <alexandru.elisei@arm.com>
X-Patchwork-Id: 12155109
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id BEB3DC433E8
	for <kvm@archiver.kernel.org>; Mon, 22 Mar 2021 15:07:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8C471619C5
	for <kvm@archiver.kernel.org>; Mon, 22 Mar 2021 15:07:23 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231635AbhCVPGz (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 22 Mar 2021 11:06:55 -0400
Received: from foss.arm.com ([217.140.110.172]:33486 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S231637AbhCVPGV (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 22 Mar 2021 11:06:21 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 9DAA31063;
        Mon, 22 Mar 2021 08:06:20 -0700 (PDT)
Received: from monolith.localdoman (unknown [172.31.20.19])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 DE1A33F719;
        Mon, 22 Mar 2021 08:06:19 -0700 (PDT)
From: Alexandru Elisei <alexandru.elisei@arm.com>
To: drjones@redhat.com, kvm@vger.kernel.org,
        kvmarm@lists.cs.columbia.edu
Cc: andre.przywara@arm.com
Subject: [kvm-unit-tests PATCH v2 1/6] arm64: Remove unnecessary ISB when
 writing to SPSel
Date: Mon, 22 Mar 2021 15:06:36 +0000
Message-Id: <20210322150641.58878-2-alexandru.elisei@arm.com>
X-Mailer: git-send-email 2.31.0
In-Reply-To: <20210322150641.58878-1-alexandru.elisei@arm.com>
References: <20210322150641.58878-1-alexandru.elisei@arm.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Software can use the SPSel operand to write directly to PSTATE.SP.
According to ARM DDI 0487F.b, page D1-2332, writes to PSTATE are
self-synchronizing and no ISB is needed:

"Writes to the PSTATE fields have side-effects on various aspects of the PE
operation. All of these side-effects are guaranteed:
- Not to be visible to earlier instructions in the execution stream.
- To be visible to later instructions in the execution stream."

Reviewed-by: Andre Przywara <andre.przywara@arm.com>
Signed-off-by: Alexandru Elisei <alexandru.elisei@arm.com>
---
 arm/cstart64.S | 1 -
 1 file changed, 1 deletion(-)

```
#### [PATCH 1/4 v4] KVM: nSVM: Trigger synthetic #DB intercept following completion of single-stepped VMRUN instruction
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 12155957
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 8B59EC433E2
	for <kvm@archiver.kernel.org>; Mon, 22 Mar 2021 18:59:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 44D8D619A1
	for <kvm@archiver.kernel.org>; Mon, 22 Mar 2021 18:59:27 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232262AbhCVS7B (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 22 Mar 2021 14:59:01 -0400
Received: from userp2120.oracle.com ([156.151.31.85]:53962 "EHLO
        userp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S231643AbhCVS6r (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 22 Mar 2021 14:58:47 -0400
Received: from pps.filterd (userp2120.oracle.com [127.0.0.1])
        by userp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 12MInu5S005223;
        Mon, 22 Mar 2021 18:58:43 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references :
 content-transfer-encoding : content-type : mime-version;
 s=corp-2020-01-29; bh=GapxKE9GulK0jHGJWCpUwhHJ1St2QDENULrhnSqfhuQ=;
 b=EqWPUxbuyzkbgLYtxhmWRGFMc4U96RYFvwF8WLfWgeUPGxY+gKkH6F8BUFhHWsmqy5mU
 BwE/ZsmvLWmY99Wg7q1RtvoCn8A/5RPZ/FxSdW5Q9MqYo1z7qV9Ft10LImgDn6FPbjja
 1/2Z8+6Y8M/IihBhN0eGLqTKHR1s+8aC08kaKaeJoJuJ7OM5+eKwmPt80sk75vvCrjln
 XfM6igVUZ5T+9QHTpjmKXifgL731UUy381EdnNxCLjwMd8nrXiTVysaFeXNdAD30TIPS
 SyPdakE3N5X8l61wcZHNQoKj0FDqazEi3QvK5jUNt+Vf8za2uhm6qqDce5HCFTJNyKdK JQ==
Received: from userp3020.oracle.com (userp3020.oracle.com [156.151.31.79])
        by userp2120.oracle.com with ESMTP id 37d9pmvg45-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 22 Mar 2021 18:58:42 +0000
Received: from pps.filterd (userp3020.oracle.com [127.0.0.1])
        by userp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 12MIo8Ir135034;
        Mon, 22 Mar 2021 18:58:42 GMT
Received: from nam12-mw2-obe.outbound.protection.outlook.com
 (mail-mw2nam12lp2042.outbound.protection.outlook.com [104.47.66.42])
        by userp3020.oracle.com with ESMTP id 37dttqxyc5-2
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 22 Mar 2021 18:58:42 +0000
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=EaqaDkeAhHGnN3L0svMA5ADMWTAcagQ5voVDcVB6MIwpv5imWXh/sv/65CVVrxPZj2aQDONZegsM90tuoQEMf5Zgmn4Gt0eIJCTcrczP9Mh808C4VSZLMX0PCuf4r+LmRHijYv5u4KWNBVaOwXUGINKk8VTmeVOr+WV1KsGwi02L20IR6d99S39TNwkaSbpp1bF8yHb17OMyVzWLkWEijYAOkd9uDQtJQtOda794ghl7BMipY/7/cC5CjmhhTlOS8TtYf86B/2a8/dYgTj3EQ0YiO4KAgKFUTyi5hdP/gctxIZZWiT7oBqFzvvcMWtIklEXuze99QBQ9YKNhJssfOg==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=GapxKE9GulK0jHGJWCpUwhHJ1St2QDENULrhnSqfhuQ=;
 b=iEDgAE3cyLrjJYfiL8d2l3K4/SFCoZhMK9flVpJ2Jk9aG0evwYTQ5/Q/dM8CnW+I8UZ/EsCy8kQlceAtC9AcFOZEz06qVah9ekqOftjMF8qvXH0CEIj2jxoz2dSQBCJX+ImPjYnVLmUvKcjGa23vmQRT6HGmv1+cLt8So6VdDHtfnzry6RQE1kx3+buOo+DuZtZ1YX4ENGzSDC89dm70CAGsBbG6rXxNURrZ2DSM2Hq/+o0A9LUqTWVTSwsNSIW/U+qU44qkmqlT9aE5QK+a8W5bHD4pyjE/Q5XfVkLqxFAgkriV+GUpaYwg1VMLpIdfuXMJ593nwTZNBe7sgozTPQ==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=oracle.com; dmarc=pass action=none header.from=oracle.com;
 dkim=pass header.d=oracle.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=oracle.onmicrosoft.com; s=selector2-oracle-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=GapxKE9GulK0jHGJWCpUwhHJ1St2QDENULrhnSqfhuQ=;
 b=N77jW3eP531TcHl4VQW0GkP+IJL3vN5GQ/aWulnm9AaDPGjGeJjfGg5KqIQWKFuThqqSCb1Rur7d7WdIBaDBIKE3F2px4ynVCtngtTPZXtO8n+OEMeutBpXhSaIy+1trJcd3emruUgpdZAKMvV4NbeiLrs9k7H5KAajK+//w+RE=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=oracle.com;
Received: from SN6PR10MB3021.namprd10.prod.outlook.com (2603:10b6:805:cc::19)
 by SA2PR10MB4795.namprd10.prod.outlook.com (2603:10b6:806:11d::14) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3955.18; Mon, 22 Mar
 2021 18:58:41 +0000
Received: from SN6PR10MB3021.namprd10.prod.outlook.com
 ([fe80::1871:3741:cc17:bcf7]) by SN6PR10MB3021.namprd10.prod.outlook.com
 ([fe80::1871:3741:cc17:bcf7%7]) with mapi id 15.20.3955.025; Mon, 22 Mar 2021
 18:58:41 +0000
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com, seanjc@google.com
Subject: [PATCH 1/4 v4] KVM: nSVM: Trigger synthetic #DB intercept following
 completion of single-stepped VMRUN instruction
Date: Mon, 22 Mar 2021 14:10:04 -0400
Message-Id: <20210322181007.71519-2-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.25.4
In-Reply-To: <20210322181007.71519-1-krish.sadhukhan@oracle.com>
References: <20210322181007.71519-1-krish.sadhukhan@oracle.com>
X-Originating-IP: [138.3.201.29]
X-ClientProxiedBy: CH2PR14CA0021.namprd14.prod.outlook.com
 (2603:10b6:610:60::31) To SN6PR10MB3021.namprd10.prod.outlook.com
 (2603:10b6:805:cc::19)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from ban25x6uut29.us.oracle.com (138.3.201.29) by
 CH2PR14CA0021.namprd14.prod.outlook.com (2603:10b6:610:60::31) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3955.18 via Frontend
 Transport; Mon, 22 Mar 2021 18:58:40 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 706d0823-cd26-43a3-dcf0-08d8ed648226
X-MS-TrafficTypeDiagnostic: SA2PR10MB4795:
X-Microsoft-Antispam-PRVS: 
 <SA2PR10MB479518AC6C8323D00FE530F881659@SA2PR10MB4795.namprd10.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:6108;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 zJSzcsl4I9Vav1NL8I5wpI28Oa8KOBzctwU8/qZYyVogO7T7TiPyIVvAw6gTZ71yNi322HRgQtyO57jdHrOpIMeclXECXrbXZCzpZoC4rkezNoafo80M7wy6b7tPbG9DYhD2rvXRZ2yCa549U/Loje5SBK0duwVxRmqTl/68Bzl/5unWVhmmhKVznyoPl7S/vhNQoKda7tsjWsB2xgCiOctxjpLd9BIoJawzVBoPZHADjQe8lRQ0QIU5fto38t5QK4m/gJlfKq1UezPrzfswpd927vCa838GYptT4nEiYEkZ/x/XUeJC2WSi7OwM9RZYdP74wEqJF12ofATKCWpRmwVgjFBgSbAghdRAkypaskTiBRDYaP/wbthxQ8+VKCa8yBuipBwCiDxX783MmHvtD47Ear9UHQKNxPFHz2uX923jccHojp1+nEwrvktG0p0MS+wTFlOp+pJSopWpsFbj5lQZUvDJawBIGVT7KFc6+1EJLgL9zcRGOpYEUb8iJ6CgyFDBCxFt2TC5ydd88KkkjgbnZCtgADvOoCd9IgyK+LcMtd2G1j8ykUhyW9F73bo/ZHR0weQlJefU8ZQIqgGWHrYqWdxomGazFYC2/TgWV8q34BwVJMYwOXAGngBF4RH5JDFEMgnDcbnsSTIi5bMzPw==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN6PR10MB3021.namprd10.prod.outlook.com;PTR:;CAT:NONE;SFS:(346002)(366004)(136003)(396003)(376002)(39860400002)(6486002)(2906002)(16526019)(186003)(6666004)(26005)(44832011)(5660300002)(66556008)(86362001)(52116002)(4326008)(2616005)(316002)(8936002)(1076003)(7696005)(38100700001)(36756003)(478600001)(66946007)(8676002)(956004)(66476007)(83380400001)(6916009);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 E6g0jRrKYn4gxVXvJ3QWoXI/l6C5mNRdHyNll2+1imj0JlE8JjV0CJYoEMVa6AvYRIacmeZW+V8RNXEuUeH9/2KnaF0xaLXLgDAttp53jmLbSeo+7v2VJ/tV/S8JpK1PycHhX/M9rG+JBxG0VIWT6in07IvIzywzLFz/ZhZ0YgT/IQ7A2eMWYjPV8Ot4S5etCLHcJ+WVxvBWxehGGABtc0iLKhRqxIeCdjYjer91+q4KO5ZaFmaoF885mPwtMsiLfpvg4Td6qLeEjMl38RacN4r4M3Kfms+MXzwal9et+yMF9wD7dL3jBpVgrmmDuFl+LV+ovJw+Jdgr2klRRSaNI2TAkv2NI137RfiJ3B92DWZN3TcNmKr3b5Iw6irSfWxbwd3sgHKURCBBdZnIU6wzgcZr3vE/AdoMxgCVUJ9s5IRy9WO6YAqWfvbaFVzZEOGwR4tzEb21vpT6n64fA0yFyFzzv2qvDV6OEOEa3+055Pz6tvQl2p0c8NHqsMgtloHgKy1Zx/g4m3XHUrUEZcLeSZdyR/GpV+gtHDbxmi5rW/Ab82GTj7A19vTbMmnXWTQzGFOLD47SoZLS/srH/uSNdmoV1aAyPOdlin4vnPHsRpc3HEyB1DgrgTzqSt5x4HGc5NPG4vdXwl91kI0nr8ksC/cx/trHWx7XiI8v9zLXyWkgVczKTolIahoWG4/VNgpqGsLCGAfubfMfPud9+avYdVXvxu1OnHt9b0+oFbeGndmFcH2sGRePLpj05Bytof8i/5p5vAtASssbaukD2RIfc0khyaOaAgFGszSPFB7Hd0GiRPyPGoyBdYBgYJbQdkNZgAXUFA7nxEZV/ZTcK14zHtmZ9fZQlN5Ur0wnaxVtpHi0BAMU19EnGlyjQZ0ztmZ1SrTRVc+0TKGVuzdHPsTcTMIhXrAqVtjFk+aB3GKo3YAg5plc6tpiQc7zQGvMio35Scm3N9rBm6Ziu1U8fbRvXD1ttZkLR0m6GzJ3ME2utoLg0k41uvA9fIJRlgC/X7Z89dlp7XsjkquKZvq+MiN5KQjX4N0prUxj/Kkam11x0ghfEGqOSqwbuH8ptqgxKrc/0FPvSiqzZ7vp1D7jLNLtNJiv4aQphvSfIz/oV9tu7EfPOFUIyqueJvkJZ5wJhlcpiPxwhn2BIh5kOtvcIcWYfDos4YM5ElldTpA0iMvjdiYIFFetXv5Bk6Yr3Ntodpd2P6NTzO9n9bM8fOKg41b/44joO2JY5TwO0VtT+t7vgza6vIwi/Zmrzk+v05kWF3pl4l9qxTUqpv3hJeIoBZp/grwtQjxGWZh7BQ5vv9VgcnOTx8udPc4y9h2OL+Jnbgn8
X-OriginatorOrg: oracle.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 706d0823-cd26-43a3-dcf0-08d8ed648226
X-MS-Exchange-CrossTenant-AuthSource: SN6PR10MB3021.namprd10.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 22 Mar 2021 18:58:41.2840
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 4e2c6054-71cb-48f1-bd6c-3a9705aca71b
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 8U8G/zxJgD+qzPNq5+FuFBpoLoqBeKx7+vlQqHKJgHwr22EWLVKhmTe1wezoLwdsFp5pT5E9Pg6x1enuwQIKZMnEd9lZIZ69tKjuekPj0Eg=
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SA2PR10MB4795
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9931
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 adultscore=0
 malwarescore=0 spamscore=0
 mlxscore=0 phishscore=0 suspectscore=0 mlxlogscore=999 bulkscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2103220136
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9931
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 lowpriorityscore=0 phishscore=0
 mlxlogscore=999 priorityscore=1501 impostorscore=0 bulkscore=0 spamscore=0
 adultscore=0 clxscore=1015 malwarescore=0 mlxscore=0 suspectscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2103220136
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

According to APM, the #DB intercept for a single-stepped VMRUN must happen
after the completion of that instruction, when the guest does #VMEXIT to
the host. However, in the current implementation of KVM, the #DB intercept
for a single-stepped VMRUN happens after the completion of the instruction
that follows the VMRUN instruction. When the #DB intercept handler is
invoked, it shows the RIP of the instruction that follows VMRUN, instead of
of VMRUN itself. This is an incorrect RIP as far as single-stepping VMRUN
is concerned.

This patch fixes the problem by checking for the condtion that the VMRUN
instruction is being single-stepped and if so, triggers a synthetic #DB
intercept so that the #DB for the VMRUN is accounted for at the right time.

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oraacle.com>
---
 arch/x86/kvm/svm/svm.c | 15 +++++++++++++++
 1 file changed, 15 insertions(+)

```
#### [PATCH v2 1/2] s390/kvm: split kvm_s390_real_to_abs
##### From: Claudio Imbrenda <imbrenda@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Claudio Imbrenda <imbrenda@linux.ibm.com>
X-Patchwork-Id: 12154875
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 8627BC433E2
	for <kvm@archiver.kernel.org>; Mon, 22 Mar 2021 14:06:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5434061972
	for <kvm@archiver.kernel.org>; Mon, 22 Mar 2021 14:06:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230267AbhCVOG1 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 22 Mar 2021 10:06:27 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:63584 "EHLO
        mx0b-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S230467AbhCVOGH (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 22 Mar 2021 10:06:07 -0400
Received: from pps.filterd (m0098421.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 12ME4CZT118087;
        Mon, 22 Mar 2021 10:06:07 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=/FH/BY9cKHJnsdtLem9lZfE4bqb2oejz5WbHJAJtWLo=;
 b=o9AydZfQWQduFxlcHOSE+1ikbUG78EIYLh4rXAHnVY9AsdgkvI1KuFg8hFUU6Pleas5q
 bIvfsVZL7ObDLZ0TqBS3lCvKv81r9xb1GCdHSqgSxk8uUjnZi4A56fTft4wIA73nCmzs
 HhWs2p1Y0V7gUpQw05ZYvUyAnvk9yz+PEQLvBycra1g1eXirZo/+nAnrKu9oqEAHz+4H
 iBe1hDboNwKrOUNUfUoXvPqwj8hEiW4Iz9GWOJ/u6/ToZ0+a+XHepHjcNLdiShsoSFbo
 6PPqEl0AbaAUwDj0BtkfPR5jA+IWZ4y+obAv+PTKz2CsYYX27/1j29IHYpEXyq2RINtN OQ==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 37ef8b2t8r-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 22 Mar 2021 10:06:05 -0400
Received: from m0098421.ppops.net (m0098421.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 12ME5TZ2128701;
        Mon, 22 Mar 2021 10:06:05 -0400
Received: from ppma03ams.nl.ibm.com (62.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.98])
        by mx0a-001b2d01.pphosted.com with ESMTP id 37ef8b2t86-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 22 Mar 2021 10:06:05 -0400
Received: from pps.filterd (ppma03ams.nl.ibm.com [127.0.0.1])
        by ppma03ams.nl.ibm.com (8.16.0.43/8.16.0.43) with SMTP id
 12ME3OaA010532;
        Mon, 22 Mar 2021 14:06:03 GMT
Received: from b06cxnps3075.portsmouth.uk.ibm.com
 (d06relay10.portsmouth.uk.ibm.com [9.149.109.195])
        by ppma03ams.nl.ibm.com with ESMTP id 37df68a0p5-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 22 Mar 2021 14:06:03 +0000
Received: from d06av22.portsmouth.uk.ibm.com (d06av22.portsmouth.uk.ibm.com
 [9.149.105.58])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 12ME601949021314
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 22 Mar 2021 14:06:01 GMT
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id BF2BE4C04A;
        Mon, 22 Mar 2021 14:06:00 +0000 (GMT)
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 5ABCD4C052;
        Mon, 22 Mar 2021 14:06:00 +0000 (GMT)
Received: from ibm-vm.ibmuc.com (unknown [9.145.2.56])
        by d06av22.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Mon, 22 Mar 2021 14:06:00 +0000 (GMT)
From: Claudio Imbrenda <imbrenda@linux.ibm.com>
To: linux-kernel@vger.kernel.org
Cc: borntraeger@de.ibm.com, frankja@linux.ibm.com, david@redhat.com,
        cohuck@redhat.com, kvm@vger.kernel.org, linux-s390@vger.kernel.org,
        stable@vger.kernel.org, Thomas Huth <thuth@redhat.com>
Subject: [PATCH v2 1/2] s390/kvm: split kvm_s390_real_to_abs
Date: Mon, 22 Mar 2021 15:05:58 +0100
Message-Id: <20210322140559.500716-2-imbrenda@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20210322140559.500716-1-imbrenda@linux.ibm.com>
References: <20210322140559.500716-1-imbrenda@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.761
 definitions=2021-03-22_07:2021-03-22,2021-03-22 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 suspectscore=0
 priorityscore=1501 phishscore=0 impostorscore=0 lowpriorityscore=0
 bulkscore=0 adultscore=0 mlxscore=0 mlxlogscore=999 spamscore=0
 malwarescore=0 clxscore=1015 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-2009150000 definitions=main-2103220103
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

A new function _kvm_s390_real_to_abs will apply prefixing to a real address
with a given prefix value.

The old kvm_s390_real_to_abs becomes now a wrapper around the new function.

This is needed to avoid code duplication in vSIE.

Cc: stable@vger.kernel.org
Signed-off-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
---
 arch/s390/kvm/gaccess.h | 23 +++++++++++++++++------
 1 file changed, 17 insertions(+), 6 deletions(-)

```
#### [PATCH V2] KVM: x86: A typo fix
##### From: Bhaskar Chowdhury <unixbhaskar@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Bhaskar Chowdhury <unixbhaskar@gmail.com>
X-Patchwork-Id: 12153813
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B04CCC433C1
	for <kvm@archiver.kernel.org>; Mon, 22 Mar 2021 06:05:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8A6C86192E
	for <kvm@archiver.kernel.org>; Mon, 22 Mar 2021 06:05:11 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229930AbhCVGEl (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 22 Mar 2021 02:04:41 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:53136 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229786AbhCVGEi (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 22 Mar 2021 02:04:38 -0400
Received: from mail-qt1-x832.google.com (mail-qt1-x832.google.com
 [IPv6:2607:f8b0:4864:20::832])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 1C67BC061574;
        Sun, 21 Mar 2021 23:04:38 -0700 (PDT)
Received: by mail-qt1-x832.google.com with SMTP id u7so11506822qtq.12;
        Sun, 21 Mar 2021 23:04:38 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=lwaHqCUEUERMsP+lSCCck+2lPknx9eDdkaf0NX52J94=;
        b=as2anY9IFqju8x6xmgL5aH/SQphhMHkDAgXdwcLNMU13gTcRuXYE44AmAZWjM5gwE2
         8X+J8KJmgUqvCplTWsiw7JMWKfmGSG+x0mEgk+jP3CpO7C7gVynfY1qpWd0x99BI5AiA
         zQc+CMFC6jwVg3l3r+CgB2o7XLnmmjKaKP0sANg4RODIJDlfVRKZyV7ffhHP5ilHvusw
         a++3Q7Oes0TARj/hVRgkwbtBiL/ruQmHxPKdTjUMdirGsw8oXLIYS606FamkJBThHCwb
         tq+pB75OVLo2ZhXd4Tofnqw/I1+bspgyHBbpOGo5UKg6PaLGK8RS94T6LNXnlphRSKO2
         vesA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=lwaHqCUEUERMsP+lSCCck+2lPknx9eDdkaf0NX52J94=;
        b=fEuFvrFbo2zAJSmoWEXbtsIpIhnmqrJShX92RvC4i9wuM3b0ED14IPSOZ5S2ltTohm
         1fceRfy/QDMfXy8wK/7a2mi+IgyXWa5EGZpo2cb2RGtf3Fxegkw3XxT9vS+NjeuzGLMe
         doJ0XMkVtJ1Dsp5Xhjv+wEXNEdpAgKuFl0p6gvCYby+8FOw3Oc/XUvXoCnm16feDD8+3
         QmGYQFe/onbiT8cr62cBFn43D++WzUSx++Xuxtmot3YMGfWiw4S/dgRgmDzpTg6TyouG
         LX/V/CvSlgQdpZkVAEM9VyYwURscnwWz3e0UZ7Q7kW26txwhiE5GKI6MPvKRKk0qZfAE
         squQ==
X-Gm-Message-State: AOAM530Zz/wgwKPZZa15877/XsedWl2pBGaR1FJjHR/0OLYVrtgIuzkR
        lEPH/0Fr+8BiY0ooaxWyvIw=
X-Google-Smtp-Source: 
 ABdhPJyX6kPawbK5ls3W+DAKqZ3kKOxuwuIlod6H79ptvldVx6BkKPOe2vmjJ39w3EYwDOHkRRO/cw==
X-Received: by 2002:a05:622a:114:: with SMTP id
 u20mr8193244qtw.317.1616393077407;
        Sun, 21 Mar 2021 23:04:37 -0700 (PDT)
Received: from localhost.localdomain ([37.19.198.40])
        by smtp.gmail.com with ESMTPSA id
 r7sm8387041qtm.88.2021.03.21.23.04.30
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Sun, 21 Mar 2021 23:04:36 -0700 (PDT)
From: Bhaskar Chowdhury <unixbhaskar@gmail.com>
To: pbonzini@redhat.com, seanjc@google.com, vkuznets@redhat.com,
        wanpengli@tencent.com, jmattson@google.com, joro@8bytes.org,
        tglx@linutronix.de, mingo@redhat.com, bp@alien8.de, x86@kernel.org,
        hpa@zytor.com, kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: rdunlap@infradead.org, Bhaskar Chowdhury <unixbhaskar@gmail.com>
Subject: [PATCH V2] KVM: x86: A typo fix
Date: Mon, 22 Mar 2021 11:34:09 +0530
Message-Id: <20210322060409.2605006-1-unixbhaskar@gmail.com>
X-Mailer: git-send-email 2.31.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

s/resued/reused/


Signed-off-by: Bhaskar Chowdhury <unixbhaskar@gmail.com>
---
 Changes from V1:
 As Ingo found the correct word for replacement, so incorporating.

 arch/x86/include/asm/kvm_host.h | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

--
2.31.0

```
