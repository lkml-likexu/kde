#### [PATCH 01/18] iommu: remove the unused domain_window_disable method
##### From: Christoph Hellwig <hch@lst.de>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christoph Hellwig <hch@lst.de>
X-Patchwork-Id: 12142583
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 454B5C433DB
	for <kvm@archiver.kernel.org>; Tue, 16 Mar 2021 15:49:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 291FA650FC
	for <kvm@archiver.kernel.org>; Tue, 16 Mar 2021 15:49:35 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S237411AbhCPPtF (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 16 Mar 2021 11:49:05 -0400
Received: from casper.infradead.org ([90.155.50.34]:39180 "EHLO
        casper.infradead.org" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S230118AbhCPPst (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 16 Mar 2021 11:48:49 -0400
DKIM-Signature: v=1; a=rsa-sha256; q=dns/txt; c=relaxed/relaxed;
        d=infradead.org; s=casper.20170209;
 h=Content-Transfer-Encoding:MIME-Version:
        References:In-Reply-To:Message-Id:Date:Subject:Cc:To:From:Sender:Reply-To:
        Content-Type:Content-ID:Content-Description;
        bh=iw+fifO7jrg/z05+P9SvlFTQmtqEOKLWF4/W63fZSxg=;
 b=t8rWyJbHNRA+UdMLiAjEgLyDck
        M+oVJgU7mMVSpeTyf1YPJI2RGqBN3Sn9PFh94Tt6X8WVm0claWr2KRveHeGUslpukjM6021i8VVBe
        ssNC9EADHuhaXovE2EAOdZ4HeCHi3cv5pZI4mIecJDA/63eHhSIoS9Z1+v7buOcgx4JwQLb8XLsyx
        xRZ3DxAOxonTDtzuxqSHKRwT0oOjxGyH/gr3wj9utxLuYw9mok8rdNoakTiZj7k/VNJiBlfkYDt+a
        qHIiUMUrvM9EkvpjGvbvgckkoVGdIgUJSCpXRj+w1toY53CSWJG7Tpu5DPfUwLKKgwCdjYatVnt4k
        eXidtaZQ==;
Received: from 089144199244.atnat0008.highway.a1.net ([89.144.199.244]
 helo=localhost)
        by casper.infradead.org with esmtpsa (Exim 4.94 #2 (Red Hat Linux))
        id 1lMBqQ-000Fk5-G4; Tue, 16 Mar 2021 15:42:58 +0000
From: Christoph Hellwig <hch@lst.de>
To: Joerg Roedel <joro@8bytes.org>, Will Deacon <will@kernel.org>,
        Li Yang <leoyang.li@nxp.com>
Cc: Michael Ellerman <mpe@ellerman.id.au>,
        David Woodhouse <dwmw2@infradead.org>,
        Lu Baolu <baolu.lu@linux.intel.com>,
        linuxppc-dev@lists.ozlabs.org, linux-arm-msm@vger.kernel.org,
        dri-devel@lists.freedesktop.org, freedreno@lists.freedesktop.org,
        iommu@lists.linux-foundation.org,
        linux-arm-kernel@lists.infradead.org, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org
Subject: [PATCH 01/18] iommu: remove the unused domain_window_disable method
Date: Tue, 16 Mar 2021 16:38:07 +0100
Message-Id: <20210316153825.135976-2-hch@lst.de>
X-Mailer: git-send-email 2.30.1
In-Reply-To: <20210316153825.135976-1-hch@lst.de>
References: <20210316153825.135976-1-hch@lst.de>
MIME-Version: 1.0
X-SRS-Rewrite: SMTP reverse-path rewritten from <hch@infradead.org> by
 casper.infradead.org. See http://www.infradead.org/rpr.html
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

domain_window_disable is wired up by fsl_pamu, but never actually called.

Signed-off-by: Christoph Hellwig <hch@lst.de>
Acked-by: Li Yang <leoyang.li@nxp.com>
---
 drivers/iommu/fsl_pamu_domain.c | 48 ---------------------------------
 include/linux/iommu.h           |  2 --
 2 files changed, 50 deletions(-)

```
#### [PATCH] docs: virt: kvm: Trivial typo fix in the file timekeeping.rst
##### From: Bhaskar Chowdhury <unixbhaskar@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Bhaskar Chowdhury <unixbhaskar@gmail.com>
X-Patchwork-Id: 12141239
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id DB270C433E6
	for <kvm@archiver.kernel.org>; Tue, 16 Mar 2021 04:45:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AF1FC65111
	for <kvm@archiver.kernel.org>; Tue, 16 Mar 2021 04:45:39 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234097AbhCPEpL (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 16 Mar 2021 00:45:11 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:38506 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229962AbhCPEot (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 16 Mar 2021 00:44:49 -0400
Received: from mail-qt1-x832.google.com (mail-qt1-x832.google.com
 [IPv6:2607:f8b0:4864:20::832])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 3C571C06174A;
        Mon, 15 Mar 2021 21:44:49 -0700 (PDT)
Received: by mail-qt1-x832.google.com with SMTP id h7so4027120qtx.3;
        Mon, 15 Mar 2021 21:44:49 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=Ln6IROcL0oqmiyWgZVylBCyeTAvDQnVtqaLoFG3jsSA=;
        b=Lkh6Qx6Q7o3RBAorjTjSkvKFkltnLwjRXu/3fiMeGJEQEMoLLu59QV6qN7aDvOo/21
         JnVdfWhhzEjz9Ytx66L0CDdqcIHYlV/H5cITChcr+ZvL/TtNtc3W79q807BHlHZNnB3A
         a1H+tR//ncYKigcDknno3igITuo7a55hTEivqGv77MnSjrx+3oOCng49rOD5UTt52NpY
         J4nVZjCyz5m+xCvT1cKOlffLFgHjUNPSpbOpOXY0bD+eBA+OxthhUL5jo+pTrpqEOEy7
         oXMKOVEiRdUfXS+GJHjbyIivWCQPgpTXXIuYLx+eyBsqxl3fACNx3MXb776Tm/7XB7xS
         LPvg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=Ln6IROcL0oqmiyWgZVylBCyeTAvDQnVtqaLoFG3jsSA=;
        b=h4nXQipthQ5VHsq9RetQ0CY+R0JS346n1d5KIA6a1D18Eqh+GHyrfCbT26O0qds/if
         ZVgxCiijjVdu3bQZW+2GVnx9G0hDdyN36emS/ya3Lhe1mRe8XB73lFQSbxCIaXt85Fhw
         OkEl9I0ol5IV7aPYEijjmFRmj2pywzJHd9VMWL/n9dFLIbqMjWnaell29hUa0J1VlrBU
         n3SSSzUS959wDyfHnNl8e8VfZ5Z6LVdF5PPJR0O1IOk1iFylAXBzcfLb2GGFKqtTYLv3
         U7RougDanxLXyMCZuUGYRiF4Z6YbKOD+EqZmXqXxzyZvbrwCNaWyJZzARu9rpRKzC11A
         Z33w==
X-Gm-Message-State: AOAM532PDROGGMuqLgfZ2zhcFephPn5nmAJlCd3aLRGUSZa0Wm1zI/9r
        wxKakbdmLhJMTzAeYV2Koyw=
X-Google-Smtp-Source: 
 ABdhPJxRoDEvfZK3pGTpLK8ocuHyLorhAGB8PQ4JCJWBaKlabF+nz/DW1jipdHChWgkcJtt8glqz5Q==
X-Received: by 2002:ac8:6b8a:: with SMTP id z10mr6231616qts.243.1615869888471;
        Mon, 15 Mar 2021 21:44:48 -0700 (PDT)
Received: from localhost.localdomain ([156.146.58.45])
        by smtp.gmail.com with ESMTPSA id
 g14sm14306322qkm.98.2021.03.15.21.44.44
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 15 Mar 2021 21:44:47 -0700 (PDT)
From: Bhaskar Chowdhury <unixbhaskar@gmail.com>
To: pbonzini@redhat.com, corbet@lwn.net, kvm@vger.kernel.org,
        linux-doc@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: rdunlap@infradead.org, Bhaskar Chowdhury <unixbhaskar@gmail.com>
Subject: [PATCH] docs: virt: kvm: Trivial typo fix in the file timekeeping.rst
Date: Tue, 16 Mar 2021 10:14:24 +0530
Message-Id: <20210316044424.3068802-1-unixbhaskar@gmail.com>
X-Mailer: git-send-email 2.30.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

s/extremal/external/

Signed-off-by: Bhaskar Chowdhury <unixbhaskar@gmail.com>
---
 But...Paolo,is it also "extreme"? I am in a catch-22?

 Documentation/virt/kvm/timekeeping.rst | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

--
2.30.2

```
#### [PATCH] doc/virt/kvm: move KVM_X86_SET_MSR_FILTER in section 8
##### From: Emanuele Giuseppe Esposito <eesposit@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Emanuele Giuseppe Esposito <eesposit@redhat.com>
X-Patchwork-Id: 12143143
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id EC4EEC433E6
	for <kvm@archiver.kernel.org>; Tue, 16 Mar 2021 17:08:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CCB7265122
	for <kvm@archiver.kernel.org>; Tue, 16 Mar 2021 17:08:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S235214AbhCPRI3 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 16 Mar 2021 13:08:29 -0400
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:21316 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S238334AbhCPRIX (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 16 Mar 2021 13:08:23 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1615914502;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=UXcIwAYQJO7er3n8t1vDQmVg3HZL2SMIlbQJ9A3NI5E=;
        b=gQscFF5H6KUTJ0FWCxxk5L0SE3y9dYAMDwx9JgjSo9nbKAmUs2NGX+C6da33FsJgfpW+BJ
        yJkcpw7U7d7wFLx449qZVGo/kuHkDil2jAwvFP17IOsYoP92hvQJiMTn0Aieh2X6v+ms/K
        Lx3RTyi1dYZV9aLgASiYPb0P+NHS5lU=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-594-ULJuriCgNAClr2HeXhANLw-1; Tue, 16 Mar 2021 13:08:20 -0400
X-MC-Unique: ULJuriCgNAClr2HeXhANLw-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 744CE800FF0;
        Tue, 16 Mar 2021 17:08:19 +0000 (UTC)
Received: from localhost.localdomain.com (ovpn-113-30.ams2.redhat.com
 [10.36.113.30])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 0DB075D9D3;
        Tue, 16 Mar 2021 17:08:16 +0000 (UTC)
From: Emanuele Giuseppe Esposito <eesposit@redhat.com>
To: linux-doc@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Jonathan Corbet <corbet@lwn.net>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH] doc/virt/kvm: move KVM_X86_SET_MSR_FILTER in section 8
Date: Tue, 16 Mar 2021 18:08:14 +0100
Message-Id: <20210316170814.64286-1-eesposit@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

KVM_X86_SET_MSR_FILTER is a capability, not an ioctl.
Therefore move it from section 4.97 to the new 8.31 (other capabilities).

To fill the gap, move KVM_X86_SET_MSR_FILTER (was 4.126) to
4.97, and shifted Xen-related ioctl (were 4.127 - 4.130) by
one place (4.126 - 4.129).

Also fixed minor typo in KVM_GET_MSR_INDEX_LIST ioctl description
(section 4.3).

Signed-off-by: Emanuele Giuseppe Esposito <eesposit@redhat.com>
---
 Documentation/virt/kvm/api.rst | 250 ++++++++++++++++-----------------
 1 file changed, 125 insertions(+), 125 deletions(-)

```
#### [kvm-unit-tests PATCH 1/4] lib/string: add strnlen and strrchr
##### From: Nikos Nikoleris <nikos.nikoleris@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Nikos Nikoleris <nikos.nikoleris@arm.com>
X-Patchwork-Id: 12142465
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 9740AC4332D
	for <kvm@archiver.kernel.org>; Tue, 16 Mar 2021 15:25:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 731EF650E8
	for <kvm@archiver.kernel.org>; Tue, 16 Mar 2021 15:25:06 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234021AbhCPPYj (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 16 Mar 2021 11:24:39 -0400
Received: from foss.arm.com ([217.140.110.172]:46160 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229973AbhCPPYN (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 16 Mar 2021 11:24:13 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 18C94101E;
        Tue, 16 Mar 2021 08:24:13 -0700 (PDT)
Received: from localhost.localdomain (unknown [172.31.20.19])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 3B0643F792;
        Tue, 16 Mar 2021 08:24:12 -0700 (PDT)
From: Nikos Nikoleris <nikos.nikoleris@arm.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, drjones@redhat.com, alexandru.elisei@arm.com,
        andre.przywara@arm.com
Subject: [kvm-unit-tests PATCH 1/4] lib/string: add strnlen and strrchr
Date: Tue, 16 Mar 2021 15:24:02 +0000
Message-Id: <20210316152405.50363-2-nikos.nikoleris@arm.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20210316152405.50363-1-nikos.nikoleris@arm.com>
References: <20210316152405.50363-1-nikos.nikoleris@arm.com>
MIME-Version: 1.0
X-ARM-No-Footer: FoSSMail
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This change adds two functions from <string.h> in preparation for an
update in the libfdt.

Signed-off-by: Nikos Nikoleris <nikos.nikoleris@arm.com>
---
 lib/string.h |  4 +++-
 lib/string.c | 23 +++++++++++++++++++++--
 2 files changed, 24 insertions(+), 3 deletions(-)

```
#### [PATCH 01/10] KVM: arm64: Provide KVM's own save/restore SVE primitives
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 12141689
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No,
 score=-17.0 required=3.0 tests=BAYES_00,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7CAD8C433E9
	for <kvm@archiver.kernel.org>; Tue, 16 Mar 2021 10:14:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 47AE764F8A
	for <kvm@archiver.kernel.org>; Tue, 16 Mar 2021 10:14:19 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S236563AbhCPKNt (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 16 Mar 2021 06:13:49 -0400
Received: from mail.kernel.org ([198.145.29.99]:56472 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S236565AbhCPKNc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 16 Mar 2021 06:13:32 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id E74E26501D;
        Tue, 16 Mar 2021 10:13:31 +0000 (UTC)
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1lM6he-001uep-65; Tue, 16 Mar 2021 10:13:30 +0000
From: Marc Zyngier <maz@kernel.org>
To: kvmarm@lists.cs.columbia.edu, linux-arm-kernel@lists.infradead.org,
        kvm@vger.kernel.org
Cc: dave.martin@arm.com, daniel.kiss@arm.com,
        Will Deacon <will@kernel.org>,
        Catalin Marinas <catalin.marinas@arm.com>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        broonie@kernel.org, kernel-team@android.com
Subject: [PATCH 01/10] KVM: arm64: Provide KVM's own save/restore SVE
 primitives
Date: Tue, 16 Mar 2021 10:13:03 +0000
Message-Id: <20210316101312.102925-2-maz@kernel.org>
X-Mailer: git-send-email 2.29.2
In-Reply-To: <20210316101312.102925-1-maz@kernel.org>
References: <20210316101312.102925-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: kvmarm@lists.cs.columbia.edu,
 linux-arm-kernel@lists.infradead.org, kvm@vger.kernel.org,
 dave.martin@arm.com, daniel.kiss@arm.com, will@kernel.org,
 catalin.marinas@arm.com, james.morse@arm.com, julien.thierry.kdev@gmail.com,
 suzuki.poulose@arm.com, broonie@kernel.org, kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

as we are about to change the way KVM deals with SVE, provide
KVM with its own save/restore SVE primitives.

No functional change intended.

Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 arch/arm64/include/asm/fpsimdmacros.h   |  2 ++
 arch/arm64/include/asm/kvm_hyp.h        |  2 ++
 arch/arm64/kvm/hyp/fpsimd.S             | 10 ++++++++++
 arch/arm64/kvm/hyp/include/hyp/switch.h | 10 +++++-----
 4 files changed, 19 insertions(+), 5 deletions(-)

```
#### [PATCH 01/11] irqchip/gic: Split vGIC probing information from the GIC code
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 12143351
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No,
 score=-17.0 required=3.0 tests=BAYES_00,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 1E97FC43381
	for <kvm@archiver.kernel.org>; Tue, 16 Mar 2021 17:47:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CBAE66513E
	for <kvm@archiver.kernel.org>; Tue, 16 Mar 2021 17:47:23 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S239294AbhCPRrD (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 16 Mar 2021 13:47:03 -0400
Received: from mail.kernel.org ([198.145.29.99]:39910 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S239218AbhCPRql (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 16 Mar 2021 13:46:41 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 269FD6511D;
        Tue, 16 Mar 2021 17:46:41 +0000 (UTC)
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1lMDmB-0021ao-C8; Tue, 16 Mar 2021 17:46:39 +0000
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvm@vger.kernel.org,
        kvmarm@lists.cs.columbia.edu
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Alexandru Elisei <alexandru.elisei@arm.com>,
        Eric Auger <eric.auger@redhat.com>,
        Hector Martin <marcan@marcan.st>,
        Mark Rutland <mark.rutland@arm.com>, kernel-team@android.com
Subject: [PATCH 01/11] irqchip/gic: Split vGIC probing information from the
 GIC code
Date: Tue, 16 Mar 2021 17:46:06 +0000
Message-Id: <20210316174617.173033-2-maz@kernel.org>
X-Mailer: git-send-email 2.29.2
In-Reply-To: <20210316174617.173033-1-maz@kernel.org>
References: <20210316174617.173033-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org, kvm@vger.kernel.org,
 kvmarm@lists.cs.columbia.edu, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 alexandru.elisei@arm.com, eric.auger@redhat.com, marcan@marcan.st,
 mark.rutland@arm.com, kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The vGIC advertising code is unsurprisingly very much tied to
the GIC implementations. However, we are about to extend the
support to lesser implementations.

Let's dissociate the vgic registration from the GIC code and
move it into KVM, where it makes a bit more sense. This also
allows us to mark the gic_kvm_info structures as __initdata.

Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 arch/arm64/kvm/vgic/vgic-init.c        | 17 +++++++++--
 drivers/irqchip/irq-gic-common.c       | 13 --------
 drivers/irqchip/irq-gic-common.h       |  2 --
 drivers/irqchip/irq-gic-v3.c           |  6 ++--
 drivers/irqchip/irq-gic.c              |  6 ++--
 include/linux/irqchip/arm-gic-common.h | 25 +---------------
 include/linux/irqchip/arm-vgic-info.h  | 41 ++++++++++++++++++++++++++
 7 files changed, 62 insertions(+), 48 deletions(-)
 create mode 100644 include/linux/irqchip/arm-vgic-info.h

```
#### [RFC PATCH v2 1/2] kvm/arm64: Remove the creation time's mapping of MMIO regions
##### From: Keqian Zhu <zhukeqian1@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Keqian Zhu <zhukeqian1@huawei.com>
X-Patchwork-Id: 12142239
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id CD306C433E0
	for <kvm@archiver.kernel.org>; Tue, 16 Mar 2021 13:45:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A32B265053
	for <kvm@archiver.kernel.org>; Tue, 16 Mar 2021 13:45:08 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S235459AbhCPNoh (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 16 Mar 2021 09:44:37 -0400
Received: from szxga05-in.huawei.com ([45.249.212.191]:13547 "EHLO
        szxga05-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S235446AbhCPNoM (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 16 Mar 2021 09:44:12 -0400
Received: from DGGEMS406-HUB.china.huawei.com (unknown [172.30.72.60])
        by szxga05-in.huawei.com (SkyGuard) with ESMTP id 4F0DwQ47S1zNngp;
        Tue, 16 Mar 2021 21:41:42 +0800 (CST)
Received: from DESKTOP-5IS4806.china.huawei.com (10.174.184.42) by
 DGGEMS406-HUB.china.huawei.com (10.3.19.206) with Microsoft SMTP Server id
 14.3.498.0; Tue, 16 Mar 2021 21:43:55 +0800
From: Keqian Zhu <zhukeqian1@huawei.com>
To: <linux-kernel@vger.kernel.org>,
        <linux-arm-kernel@lists.infradead.org>, <kvm@vger.kernel.org>,
        <kvmarm@lists.cs.columbia.edu>, Will Deacon <will@kernel.org>,
        Marc Zyngier <maz@kernel.org>
CC: Catalin Marinas <catalin.marinas@arm.com>,
        Mark Rutland <mark.rutland@arm.com>,
        James Morse <james.morse@arm.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        <wanghaibin.wang@huawei.com>, <jiangkunkun@huawei.com>,
        <yuzenghui@huawei.com>, <lushenming@huawei.com>
Subject: [RFC PATCH v2 1/2] kvm/arm64: Remove the creation time's mapping of
 MMIO regions
Date: Tue, 16 Mar 2021 21:43:37 +0800
Message-ID: <20210316134338.18052-2-zhukeqian1@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
In-Reply-To: <20210316134338.18052-1-zhukeqian1@huawei.com>
References: <20210316134338.18052-1-zhukeqian1@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.174.184.42]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The MMIO regions may be unmapped for many reasons and can be remapped
by stage2 fault path. Map MMIO regions at creation time becomes a
minor optimization and makes these two mapping path hard to sync.

Remove the mapping code while keep the useful sanity check.

Signed-off-by: Keqian Zhu <zhukeqian1@huawei.com>
---
 arch/arm64/kvm/mmu.c | 38 +++-----------------------------------
 1 file changed, 3 insertions(+), 35 deletions(-)

```
#### [PATCH v2 1/4] KVM: x86: hyper-v: Limit guest to writing zero to HV_X64_MSR_TSC_EMULATION_STATUS
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 12142305
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 87667C433E0
	for <kvm@archiver.kernel.org>; Tue, 16 Mar 2021 14:38:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5C90A6505E
	for <kvm@archiver.kernel.org>; Tue, 16 Mar 2021 14:38:52 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S236685AbhCPOi1 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 16 Mar 2021 10:38:27 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:46510 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S236603AbhCPOhr (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 16 Mar 2021 10:37:47 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1615905466;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=O5Co9d4ozrTngCdGCM1S57GEotFMyYjlIiNeBZ4sqxk=;
        b=HELIEJsh1rW8+Rncv04RgjHnYzqtIvh0y14smFbb8RIRl86G7ujCYrC6w7WfCIiuokQ9Is
        CgE3ntv7XopozwxDlvzWKiT+u1oSQIDcUXf0ZXZ2cg83/XiA2rl0C8WFxL/AlapysuEqDQ
        lT0RzRDQgRC4XlagffvmOAIT9V4f+CU=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-383-8c4DSKPmMzOUr2hW85FC2A-1; Tue, 16 Mar 2021 10:37:45 -0400
X-MC-Unique: 8c4DSKPmMzOUr2hW85FC2A-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 23E69100C662;
        Tue, 16 Mar 2021 14:37:44 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.195.229])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 916835D9D3;
        Tue, 16 Mar 2021 14:37:40 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Marcelo Tosatti <mtosatti@redhat.com>
Subject: [PATCH v2 1/4] KVM: x86: hyper-v: Limit guest to writing zero to
 HV_X64_MSR_TSC_EMULATION_STATUS
Date: Tue, 16 Mar 2021 15:37:33 +0100
Message-Id: <20210316143736.964151-2-vkuznets@redhat.com>
In-Reply-To: <20210316143736.964151-1-vkuznets@redhat.com>
References: <20210316143736.964151-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

HV_X64_MSR_TSC_EMULATION_STATUS indicates whether TSC accesses are emulated
after migration (to accommodate for a different host TSC frequency when TSC
scaling is not supported; we don't implement this in KVM). Guest can use
the same MSR to stop TSC access emulation by writing zero. Writing anything
else is forbidden.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/hyperv.c | 3 +++
 1 file changed, 3 insertions(+)

```
#### [PATCH 1/4] KVM: x86: Protect userspace MSR filter with SRCU, and set atomically-ish
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12143497
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 62E34C4332E
	for <kvm@archiver.kernel.org>; Tue, 16 Mar 2021 18:45:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3897C6513A
	for <kvm@archiver.kernel.org>; Tue, 16 Mar 2021 18:45:44 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S240111AbhCPSpW (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 16 Mar 2021 14:45:22 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:50932 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S240094AbhCPSou (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 16 Mar 2021 14:44:50 -0400
Received: from mail-qk1-x74a.google.com (mail-qk1-x74a.google.com
 [IPv6:2607:f8b0:4864:20::74a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id AB4C9C061762
        for <kvm@vger.kernel.org>; Tue, 16 Mar 2021 11:44:48 -0700 (PDT)
Received: by mail-qk1-x74a.google.com with SMTP id p133so3776432qka.17
        for <kvm@vger.kernel.org>; Tue, 16 Mar 2021 11:44:48 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=reply-to:date:in-reply-to:message-id:mime-version:references
         :subject:from:to:cc;
        bh=GOg8aEutRplmgR/4P/VzxUp6Yi8jfdN0FR519oaYWrc=;
        b=Iy72Y99kOz5uKye1akbdGo6zr4Gnee7C6OlDNU7Cw9It0wztc7FisaN1686t+1ZqJ0
         VBx3s6LjfEkRBhWQTshWvKvkt5uwGRE0x5UgH03AaR/v+si0sMoJX9tuwqhwGqaYgUsS
         lBoXct8kipIr5YSPA93aSWScN8sUfmZFcAV7GwQ99XU/jrulQq2xKUvh4jn22CGf1HsX
         scffnoFTN3An3b0ToSy9auJyJscOJLPzm40ZAC8SMgCvLNogZ7yaasTqqNJVkrGS+PDJ
         VYaUzKhbJEgeRSp0s+bCo9ye9fH1S9Rff9qyuN7ytdsX+k6/AOrf4FQ28QPdiwqTwWWp
         ndww==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:reply-to:date:in-reply-to:message-id
         :mime-version:references:subject:from:to:cc;
        bh=GOg8aEutRplmgR/4P/VzxUp6Yi8jfdN0FR519oaYWrc=;
        b=I+/OdrbC4jzrTfpnBDo9aVmH+XyBL1tBCyTQUmFkFVCLKqd4Mp5lonrSqcXDFg8dIx
         rAzED2AcSoLv0OPCNiBHCTzFCD9Xkt5xfWXCRoi5WzAv6av7LzQue38wLzAHfqd/04zs
         N4jzv7vI+d91WNB5lcQVBeCbAYTbg2Sgyb1XqYzv+dOAzQyPvQEozYviYEN5gfdn6ozU
         kMW6WjjwNnYkRfNzOXDExDUKzS5EDDEIeEToykOMpXTU4vzPnWCfhfUwjiC7xRonV+1r
         Nw6VOFblMoOOnYFncdMeOFp/5cNeMI5wY7VE9CH2tC2ZUWZtwm01ZH0C8mr6yNU1yI+0
         6w+A==
X-Gm-Message-State: AOAM533TzF5XjQqdrHDttNTsH9LY/MkKMV+LyOIz6kOAID07mEJXN9op
        YrnBzwZhnltg4NKFfVVNmqWbWyq7WVs=
X-Google-Smtp-Source: 
 ABdhPJxBlkuFU89c8G0sun/hbzG5+J/NDhCEAGF/cUpeVhBUZUnHmEQmi/Xz9ljf6tHnMp1SUcDksj0mNrM=
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:e113:95c2:2d1:e304])
 (user=seanjc job=sendgmr) by 2002:ad4:5d46:: with SMTP id
 jk6mr870821qvb.22.1615920287805;
 Tue, 16 Mar 2021 11:44:47 -0700 (PDT)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Tue, 16 Mar 2021 11:44:33 -0700
In-Reply-To: <20210316184436.2544875-1-seanjc@google.com>
Message-Id: <20210316184436.2544875-2-seanjc@google.com>
Mime-Version: 1.0
References: <20210316184436.2544875-1-seanjc@google.com>
X-Mailer: git-send-email 2.31.0.rc2.261.g7f71774620-goog
Subject: [PATCH 1/4] KVM: x86: Protect userspace MSR filter with SRCU,
 and set atomically-ish
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Alexander Graf <graf@amazon.com>,
        Yuan Yao <yaoyuan0329os@gmail.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Fix a plethora of issues with MSR filtering by installing the resulting
filter as an atomic bundle instead of updating the live filter one range
at a time.  The KVM_X86_SET_MSR_FILTER ioctl() isn't truly atomic, as
the hardware MSR bitmaps won't be updated until the next VM-Enter, but
the relevant software struct is atomically updated, which is what KVM
really needs.

Similar to the approach used for modifying memslots, make arch.msr_filter
a SRCU-protected pointer, do all the work configuring the new filter
outside of kvm->lock, and then acquire kvm->lock only when the new filter
has been vetted and created.  That way vCPU readers either see the old
filter or the new filter in their entirety, not some half-baked state.

Yuan Yao pointed out a use-after-free in ksm_msr_allowed() due to a
TOCTOU bug, but that's just the tip of the iceberg...

  - Nothing is __rcu annotated, making it nigh impossible to audit the
    code for correctness.
  - kvm_add_msr_filter() has an unpaired smp_wmb().  Violation of kernel
    coding style aside, the lack of a smb_rmb() anywhere casts all code
    into doubt.
  - kvm_clear_msr_filter() has a double free TOCTOU bug, as it grabs
    count before taking the lock.
  - kvm_clear_msr_filter() also has memory leak due to the same TOCTOU bug.

The entire approach of updating the live filter is also flawed.  While
installing a new filter is inherently racy if vCPUs are running, fixing
the above issues also makes it trivial to ensure certain behavior is
deterministic, e.g. KVM can provide deterministic behavior for MSRs with
identical settings in the old and new filters.  An atomic update of the
filter also prevents KVM from getting into a half-baked state, e.g. if
installing a filter fails, the existing approach would leave the filter
in a half-baked state, having already committed whatever bits of the
filter were already processed.

[*] https://lkml.kernel.org/r/20210312083157.25403-1-yaoyuan0329os@gmail.com

Fixes: 1a155254ff93 ("KVM: x86: Introduce MSR filtering")
Cc: stable@vger.kernel.org
Cc: Alexander Graf <graf@amazon.com>
Reported-by: Yuan Yao <yaoyuan0329os@gmail.com>
Signed-off-by: Sean Christopherson <seanjc@google.com>
---
 Documentation/virt/kvm/api.rst  |   6 +-
 arch/x86/include/asm/kvm_host.h |  17 ++---
 arch/x86/kvm/x86.c              | 109 +++++++++++++++++++-------------
 3 files changed, 78 insertions(+), 54 deletions(-)

```
#### [RFC v2] KVM: x86: Support KVM VMs sharing SEV contextFrom: Nathan Tempelman <natet@google.com>
##### From: Nathan Tempelman <natet@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Nathan Tempelman <natet@google.com>
X-Patchwork-Id: 12140947
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id B3C2EC433DB
	for <kvm@archiver.kernel.org>; Tue, 16 Mar 2021 01:42:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7361864FB5
	for <kvm@archiver.kernel.org>; Tue, 16 Mar 2021 01:42:49 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231833AbhCPBlD (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 15 Mar 2021 21:41:03 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:55370 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S230137AbhCPBkx (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 15 Mar 2021 21:40:53 -0400
Received: from mail-pg1-x54a.google.com (mail-pg1-x54a.google.com
 [IPv6:2607:f8b0:4864:20::54a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 18463C061756
        for <kvm@vger.kernel.org>; Mon, 15 Mar 2021 18:40:53 -0700 (PDT)
Received: by mail-pg1-x54a.google.com with SMTP id w31so8465593pgl.22
        for <kvm@vger.kernel.org>; Mon, 15 Mar 2021 18:40:53 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=J4ZGCuBPSlskTRsMADAlGIpcOZlKe9iPnSm86m/uI+Q=;
        b=W8OAAxo47nuSfIj90mxeommfa0lA9hlsoGhdeehL2GtkYxt8siqHEtMCmLZEd3+EM8
         oAn+CaJxWYDVLx2CxPCYhY1Pr4Rjay9XTanPTwwW3PC5E0INxR8X3QtZ37sY/NXhKhwC
         z2YnJLTmm/eAKMY/k+gikluFKPHpTaAqtUSxLcNE1TaamEEe5OypTlK4+BubGBw5bw2g
         Affip0NUGk0VshDEeubLJsBrH4LLsNOCj0zs3y99xSNoszziv43oEUHg5gL4vWUBC4Hl
         htgOIO0vTBRy3oXDF7zTdwJUOMjt+iw/FJqM14cS1Eb6ySHAovBaWyh/MFRPKuczXDWJ
         AIDA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=J4ZGCuBPSlskTRsMADAlGIpcOZlKe9iPnSm86m/uI+Q=;
        b=I0JbHeX/iXtyclJ/+u9FQSySVTHgcah8zuiV6L5rlP7j9EJk+dPozjR/Js/TAKWhWJ
         2iZgHoP3nzt1LilnHggHj9hDA/qFfKz4mmdvm8O6xi0OsNWV7nvET8osJ/Etk17NfIOe
         e4F3T07se6TP8QmcrTkZMU1/1WEhOFqQkWF6pQNbbKVINR9K65H2hzii7L98QoPJE9qA
         D++YLuyMR6D+ZRt1upy+Jeg6PPtYJt6UsnV7yEEJy5fRdYn0hSIbgRfEiyRPbs8YZoIF
         VNOK770yImMSMqw/YKuAGGx11xRbCWoupa2529Wbik7rRfFuibxB2FvKI3W5j9gBuqZU
         OOVw==
X-Gm-Message-State: AOAM530ROczx1/PNGIoe9+LGMdkpycDOiEYeMSrOhXIgLyUNzSaElrf4
        phWNR+fV+jzugcg3jrOZKnGpfTF8Zg==
X-Google-Smtp-Source: 
 ABdhPJzBap6VHfcUoWnOyfuXkDZ/m5aeOIF9nyLt6qog1HCck/YMHn113os6xGsZYQ5+8gA5zM4vZd3/YQ==
X-Received: from natesp.c.googlers.com ([fda3:e722:ac3:10:24:72f4:c0a8:5758])
 (user=natet job=sendgmr) by 2002:a65:4c01:: with SMTP id
 u1mr1701216pgq.182.1615858852331;
 Mon, 15 Mar 2021 18:40:52 -0700 (PDT)
Date: Tue, 16 Mar 2021 01:40:27 +0000
Message-Id: <20210316014027.3116119-1-natet@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.0.rc2.261.g7f71774620-goog
Subject: [RFC v2] KVM: x86: Support KVM VMs sharing SEV context
From: Nathan Tempelman <natet@google.com>
To: pbonzini@redhat.com
Cc: natet@google.com, thomas.lendacky@amd.com, x86@kernel.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        srutherford@google.com, seanjc@google.com, rientjes@google.com,
        brijesh.singh@amd.com, Ashish.Kalra@amd.com,
        dovmurik@linux.vnet.ibm.com, lersek@redhat.com, jejb@linux.ibm.com,
        frankeh@us.ibm.com
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add a capability for userspace to mirror SEV encryption context from
one vm to another. On our side, this is intended to support a
Migration Helper vCPU, but it can also be used generically to support
other in-guest workloads scheduled by the host. The intention is for
the primary guest and the mirror to have nearly identical memslots.

The primary benefits of this are that:
1) The VMs do not share KVM contexts (think APIC/MSRs/etc), so they
can't accidentally clobber each other.
2) The VMs can have different memory-views, which is necessary for post-copy
migration (the migration vCPUs on the target need to read and write to
pages, when the primary guest would VMEXIT).

This does not change the threat model for AMD SEV. Any memory involved
is still owned by the primary guest and its initial state is still
attested to through the normal SEV_LAUNCH_* flows. If userspace wanted
to circumvent SEV, they could achieve the same effect by simply attaching
a vCPU to the primary VM.
This patch deliberately leaves userspace in charge of the memslots for the
mirror, as it already has the power to mess with them in the primary guest.

This patch does not support SEV-ES (much less SNP), as it does not
handle handing off attested VMSAs to the mirror.

For additional context, we need a Migration Helper because SEV PSP migration
is far too slow for our live migration on its own. Using an in-guest
migrator lets us speed this up significantly.

Signed-off-by: Nathan Tempelman <natet@google.com>
---
 Documentation/virt/kvm/api.rst  | 17 +++++++
 arch/x86/include/asm/kvm_host.h |  1 +
 arch/x86/kvm/svm/sev.c          | 88 +++++++++++++++++++++++++++++++++
 arch/x86/kvm/svm/svm.c          |  2 +
 arch/x86/kvm/svm/svm.h          |  2 +
 arch/x86/kvm/x86.c              |  7 ++-
 include/linux/kvm_host.h        |  1 +
 include/uapi/linux/kvm.h        |  1 +
 virt/kvm/kvm_main.c             |  6 +++
 9 files changed, 124 insertions(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH 1/6] s390x: uv-guest: Add invalid share location test
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 12141511
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 8D459C43332
	for <kvm@archiver.kernel.org>; Tue, 16 Mar 2021 09:20:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6C82065023
	for <kvm@archiver.kernel.org>; Tue, 16 Mar 2021 09:20:52 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S235988AbhCPJU1 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 16 Mar 2021 05:20:27 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:39296 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S232584AbhCPJUF (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 16 Mar 2021 05:20:05 -0400
Received: from pps.filterd (m0098409.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 12G93B0S047405;
        Tue, 16 Mar 2021 05:20:05 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=n98KZT57rRerIs5/wFjWGc8mi2iOF4J+0ZSNe9MRX70=;
 b=gwFCHn+n0c6y2FgQMXv7mXx30Vv7/eISyxqvT+sSIgkyQVLzeFakoOMKvMzXCYDIrTy6
 4j6F3D18RwgTqJOhWmZ6pbUiLN7tDdojKFg7LNe8wkLJ+TvIznABhxIIRKKpKpVXCSxj
 2ebGoLpW3u4dzHSmWoZUyvMCML57MilQZieBAQJfSh020jly9PsW9HrNZ3+Mkemo7XIH
 bNkYLHslnQBjEyEuXA9ACRxlMwZ2EBC4+xWVO3lL0T33NWoJtecG8l2kbDtFRo+tBFCi
 R8D7psKRHQusKcei16a5Im4C/ji9jRyHzYGNtbiGKweX/w1CfWibnL18iTfquVcmAgWG fw==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 37arhuafmt-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 16 Mar 2021 05:20:05 -0400
Received: from m0098409.ppops.net (m0098409.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 12G93Axr047299;
        Tue, 16 Mar 2021 05:20:04 -0400
Received: from ppma06ams.nl.ibm.com (66.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.102])
        by mx0a-001b2d01.pphosted.com with ESMTP id 37arhuafkp-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 16 Mar 2021 05:20:04 -0400
Received: from pps.filterd (ppma06ams.nl.ibm.com [127.0.0.1])
        by ppma06ams.nl.ibm.com (8.16.0.43/8.16.0.43) with SMTP id
 12G9C3EP005481;
        Tue, 16 Mar 2021 09:20:02 GMT
Received: from b06cxnps4075.portsmouth.uk.ibm.com
 (d06relay12.portsmouth.uk.ibm.com [9.149.109.197])
        by ppma06ams.nl.ibm.com with ESMTP id 378mnh2pfw-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 16 Mar 2021 09:20:02 +0000
Received: from d06av22.portsmouth.uk.ibm.com (d06av22.portsmouth.uk.ibm.com
 [9.149.105.58])
        by b06cxnps4075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 12G9K02a2753156
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 16 Mar 2021 09:20:00 GMT
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 271DA4C058;
        Tue, 16 Mar 2021 09:20:00 +0000 (GMT)
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id E62464C040;
        Tue, 16 Mar 2021 09:19:58 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.145.146.129])
        by d06av22.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue, 16 Mar 2021 09:19:58 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, thuth@redhat.com, david@redhat.com,
        imbrenda@linux.ibm.com
Subject: [kvm-unit-tests PATCH 1/6] s390x: uv-guest: Add invalid share
 location test
Date: Tue, 16 Mar 2021 09:16:49 +0000
Message-Id: <20210316091654.1646-2-frankja@linux.ibm.com>
X-Mailer: git-send-email 2.27.0
In-Reply-To: <20210316091654.1646-1-frankja@linux.ibm.com>
References: <20210316091654.1646-1-frankja@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.761
 definitions=2021-03-16_03:2021-03-15,2021-03-16 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 lowpriorityscore=0
 malwarescore=0 bulkscore=0 spamscore=0 clxscore=1015 mlxscore=0
 phishscore=0 impostorscore=0 suspectscore=0 adultscore=0 mlxlogscore=999
 priorityscore=1501 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2103160063
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Let's also test sharing unavailable memory.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
---
 s390x/uv-guest.c | 5 +++++
 1 file changed, 5 insertions(+)

```
#### [PATCH] selftests: remove duplicate include
##### From: menglong8.dong@gmail.com

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Menglong Dong <menglong8.dong@gmail.com>
X-Patchwork-Id: 12141351
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 50D79C433E6
	for <kvm@archiver.kernel.org>; Tue, 16 Mar 2021 07:34:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1F28C64F90
	for <kvm@archiver.kernel.org>; Tue, 16 Mar 2021 07:34:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231476AbhCPHeB (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 16 Mar 2021 03:34:01 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:46492 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S232549AbhCPHdo (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 16 Mar 2021 03:33:44 -0400
Received: from mail-pl1-x643.google.com (mail-pl1-x643.google.com
 [IPv6:2607:f8b0:4864:20::643])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id D0740C06174A;
        Tue, 16 Mar 2021 00:33:43 -0700 (PDT)
Received: by mail-pl1-x643.google.com with SMTP id n17so12976750plc.7;
        Tue, 16 Mar 2021 00:33:43 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=4uwGLw4oyBg2siguHNzqzxEJ2zioYts2IjBxF9nVxAg=;
        b=SdXcCZp5eAj0eG7le1UodFJ9kJpKFCcQXFQp8y9qS8SdgjuQUyQtykgdEoNmnyyzKW
         IQ1GtYSUBCwWSC3WBh0bAoZ1T7a7sfvhhxTRkgQjODrJjpZBbfucYpPO1DICYL7y46U5
         kVnaM9dnC+obTvaD/Pyd4n4TjkZkW4PzW+0l8hSS3H3HbX+yTGRz1cuTTefF98kwU7/9
         9jyskWUQbxOckPjq60RBOooNAgPyiBqm2eqoD6AYFhZoYW7UqkZI+ejXh2XmO80BklJ8
         C/uD2l2ry6DUrtnjfwjnWoB4JMxx2v6vYiNyXeiSwuyG9FbMSR2nPHCgnDmBRLpNRsXe
         6uew==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=4uwGLw4oyBg2siguHNzqzxEJ2zioYts2IjBxF9nVxAg=;
        b=X6gA/qSlTVxWah5/YczMbVHaD+iWPPIiRXzdbkxD5Gu9kaQQFsvZaEgS9MSNZ7uxzH
         BNTchcTxviMiR6aK0J0+mXuTn5K1LZCJywkMOjioWZOElD36RCPyFJ7FA9z7dxif5YVo
         3Y4W0Whe2Ro5eZsp6Ctd6OHXXZVYwWNY2Tx9AK8yuq5gDzdE0A3n6beZNaUuk97W1ZPW
         GlCBxlZRGMPn32PdHemiIPDdAlmb3niM6QPFTsg2mt2ZON1ss7Z2kGMsnceyWFGuMmY5
         J7OXugJEa2tGAuftgREuT2jxbzlpX7u2U9J1melE+kL0//MhRpPXPo4R2nCcVtou0nmt
         lw+Q==
X-Gm-Message-State: AOAM533g7q/ACucvqH1YuZvvrvgLSFhoC8pEYwyaakutxCcDQVTl7OG4
        /YkGiGfuuNTVDUbsZ8WeTXk=
X-Google-Smtp-Source: 
 ABdhPJz2vO1LkuhskFr46Ba09gSjtiCwL5zhzdrTzGXkiqsvd3q1KCoj2T2CQeDKwYaintJT/FE2Ew==
X-Received: by 2002:a17:90a:cb12:: with SMTP id
 z18mr3298352pjt.132.1615880023387;
        Tue, 16 Mar 2021 00:33:43 -0700 (PDT)
Received: from localhost.localdomain ([178.236.46.205])
        by smtp.gmail.com with ESMTPSA id
 d20sm1850131pjv.47.2021.03.16.00.33.40
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 16 Mar 2021 00:33:42 -0700 (PDT)
From: menglong8.dong@gmail.com
X-Google-Original-From: zhang.yunkai@zte.com.cn
To: pbonzini@redhat.com
Cc: shuah@kernel.org, mpe@ellerman.id.au, benh@kernel.crashing.org,
        paulus@samba.org, zhang.yunkai@zte.com.cn,
        akpm@linux-foundation.org, ricardo.canuelo@collabora.com,
        kvm@vger.kernel.org, linux-kselftest@vger.kernel.org,
        linux-kernel@vger.kernel.org, linuxppc-dev@lists.ozlabs.org
Subject: [PATCH] selftests: remove duplicate include
Date: Tue, 16 Mar 2021 00:33:36 -0700
Message-Id: <20210316073336.426255-1-zhang.yunkai@zte.com.cn>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Zhang Yunkai <zhang.yunkai@zte.com.cn>

'assert.h' included in 'sparsebit.c' is duplicated.
It is also included in the 161th line.
'string.h' included in 'mincore_selftest.c' is duplicated.
It is also included in the 15th line.
'sched.h' included in 'tlbie_test.c' is duplicated.
It is also included in the 33th line.

Signed-off-by: Zhang Yunkai <zhang.yunkai@zte.com.cn>
---
 tools/testing/selftests/kvm/lib/sparsebit.c        | 1 -
 tools/testing/selftests/mincore/mincore_selftest.c | 1 -
 tools/testing/selftests/powerpc/mm/tlbie_test.c    | 1 -
 3 files changed, 3 deletions(-)

```
#### [PATCH 1/3] mm: Add unsafe_follow_pfn
##### From: Daniel Vetter <daniel.vetter@ffwll.ch>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Daniel Vetter <daniel.vetter@ffwll.ch>
X-Patchwork-Id: 12142517
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 9F70BC43381
	for <kvm@archiver.kernel.org>; Tue, 16 Mar 2021 15:33:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 77F71650EB
	for <kvm@archiver.kernel.org>; Tue, 16 Mar 2021 15:33:51 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S237253AbhCPPd3 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 16 Mar 2021 11:33:29 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:36866 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S238091AbhCPPdP (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 16 Mar 2021 11:33:15 -0400
Received: from mail-wm1-x336.google.com (mail-wm1-x336.google.com
 [IPv6:2a00:1450:4864:20::336])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id A3329C061763
        for <kvm@vger.kernel.org>; Tue, 16 Mar 2021 08:33:14 -0700 (PDT)
Received: by mail-wm1-x336.google.com with SMTP id g8so10349278wmd.4
        for <kvm@vger.kernel.org>; Tue, 16 Mar 2021 08:33:14 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=ffwll.ch; s=google;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=uUoRAMQqissgQiWNySzwnJOq0uwZjWt9LOiB5Qw/2Hk=;
        b=hFVpCvjsIApl22/AeCmNwSGg8SmuSyxqnnKJy4mQhR6BGEUcb+6lgx2UbMK4kBz1xN
         ULwJLX7V5bTAyN4GQ47VfP+7rqU5DByCia8kU6BZffozRa+USNu2ThKAIIOMLY56Z3rg
         BUM2+rVAKxKT7KfANn1fMFkXKRqHHvmbjo1v4=
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=uUoRAMQqissgQiWNySzwnJOq0uwZjWt9LOiB5Qw/2Hk=;
        b=aq+Kz4v3Mj8sQW8iDs8l1oJqSLX74PitwKbQBKEPlBO8WqO1LwXaBK1d+dNfgI084d
         J3sGlKW7EbJzZSLLTpn2JHJjQGQuE94lRiLnuBPibotHRu7F56LOA9bXpyU5CU6GLKO2
         b4L6/UDxBJSzdJaat/6+xYu2HDadhBJiBbDyFTx8GPHNMWzHz85MZ7Wwyf5PdniA2qgO
         qQYCxevlir0cmXhZNjL/I1d++IPaDVqu/N9aUYIPliTYj0ta1S927IZXTGwG49Gq3uet
         2clafxJoYSp7ACf7+QWfY1wo1fkwnbzd4N40Csb0w4E8puHE1x/plfR/FeKZSBp8VZm0
         YMcA==
X-Gm-Message-State: AOAM532sCMw/ULAi9iIJoCLlov6jUyrx4tDPVB/edihGD3fvheFn9MsS
        pwnUImDWlqqor6rpGjQ+t1RBzg==
X-Google-Smtp-Source: 
 ABdhPJzQL7u7xXceY/a/6NO6FFVvbZrOOoq5J4p9hCKPlG2yrzzaPNHWsT+RvFgxM6YyCQy3Zb0SVw==
X-Received: by 2002:a1c:43c5:: with SMTP id q188mr228308wma.94.1615908793379;
        Tue, 16 Mar 2021 08:33:13 -0700 (PDT)
Received: from phenom.ffwll.local ([2a02:168:57f4:0:efd0:b9e5:5ae6:c2fa])
        by smtp.gmail.com with ESMTPSA id
 h22sm3985078wmb.36.2021.03.16.08.33.12
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 16 Mar 2021 08:33:12 -0700 (PDT)
From: Daniel Vetter <daniel.vetter@ffwll.ch>
To: DRI Development <dri-devel@lists.freedesktop.org>,
        LKML <linux-kernel@vger.kernel.org>
Cc: kvm@vger.kernel.org, linux-mm@kvack.org,
 linux-arm-kernel@lists.infradead.org, linux-samsung-soc@vger.kernel.org,
 linux-media@vger.kernel.org, Daniel Vetter <daniel.vetter@ffwll.ch>,
 Daniel Vetter <daniel.vetter@intel.com>,
 Christoph Hellwig <hch@infradead.org>, Jason Gunthorpe <jgg@ziepe.ca>,
 Kees Cook <keescook@chromium.org>, Dan Williams <dan.j.williams@intel.com>,
 Andrew Morton <akpm@linux-foundation.org>,
 John Hubbard <jhubbard@nvidia.com>,
 =?utf-8?b?SsOpcsO0bWUgR2xpc3Nl?= <jglisse@redhat.com>,
 Jan Kara <jack@suse.cz>
Subject: [PATCH 1/3] mm: Add unsafe_follow_pfn
Date: Tue, 16 Mar 2021 16:33:01 +0100
Message-Id: <20210316153303.3216674-2-daniel.vetter@ffwll.ch>
X-Mailer: git-send-email 2.30.0
In-Reply-To: <20210316153303.3216674-1-daniel.vetter@ffwll.ch>
References: <20210316153303.3216674-1-daniel.vetter@ffwll.ch>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Way back it was a reasonable assumptions that iomem mappings never
change the pfn range they point at. But this has changed:

- gpu drivers dynamically manage their memory nowadays, invalidating
ptes with unmap_mapping_range when buffers get moved

- contiguous dma allocations have moved from dedicated carvetouts to
cma regions. This means if we miss the unmap the pfn might contain
pagecache or anon memory (well anything allocated with GFP_MOVEABLE)

- even /dev/mem now invalidates mappings when the kernel requests that
iomem region when CONFIG_IO_STRICT_DEVMEM is set, see 3234ac664a87
("/dev/mem: Revoke mappings when a driver claims the region")

Accessing pfns obtained from ptes without holding all the locks is
therefore no longer a good idea.

Unfortunately there's some users where this is not fixable (like v4l
userptr of iomem mappings) or involves a pile of work (vfio type1
iommu). For now annotate these as unsafe and splat appropriately.

This patch adds an unsafe_follow_pfn, which later patches will then
roll out to all appropriate places.

Also mark up follow_pfn as EXPORT_SYMBOL_GPL. The only safe way to use
that by drivers/modules is together with an mmu_notifier, and that's
all _GPL stuff.

Signed-off-by: Daniel Vetter <daniel.vetter@intel.com>
Cc: Christoph Hellwig <hch@infradead.org>
Cc: Jason Gunthorpe <jgg@ziepe.ca>
Cc: Kees Cook <keescook@chromium.org>
Cc: Dan Williams <dan.j.williams@intel.com>
Cc: Andrew Morton <akpm@linux-foundation.org>
Cc: John Hubbard <jhubbard@nvidia.com>
Cc: Jérôme Glisse <jglisse@redhat.com>
Cc: Jan Kara <jack@suse.cz>
Cc: Dan Williams <dan.j.williams@intel.com>
Cc: linux-mm@kvack.org
Cc: linux-arm-kernel@lists.infradead.org
Cc: linux-samsung-soc@vger.kernel.org
Cc: linux-media@vger.kernel.org
Cc: kvm@vger.kernel.org
Signed-off-by: Daniel Vetter <daniel.vetter@ffwll.ch>
---
v5: Suggestions from Christoph
- reindent for less weirdness
- use IS_ENABLED instead of #ifdef
- same checks for nommu, for consistency
- EXPORT_SYMBOL_GPL for follow_pfn.
- kerneldoc was already updated in previous versions to explain when
  follow_pfn can be used safely
---
 include/linux/mm.h |  2 ++
 mm/memory.c        | 34 ++++++++++++++++++++++++++++++++--
 mm/nommu.c         | 27 ++++++++++++++++++++++++++-
 security/Kconfig   | 13 +++++++++++++
 4 files changed, 73 insertions(+), 3 deletions(-)

```
