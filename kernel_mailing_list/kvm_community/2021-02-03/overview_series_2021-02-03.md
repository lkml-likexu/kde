#### [PATCH 01/12] x86/irq: Add DEV_MSI allocation type
##### From: Megha Dey <megha.dey@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Megha Dey <megha.dey@intel.com>
X-Patchwork-Id: 12065331
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E24FDC433E6
	for <kvm@archiver.kernel.org>; Wed,  3 Feb 2021 20:58:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A1C7D64F72
	for <kvm@archiver.kernel.org>; Wed,  3 Feb 2021 20:58:41 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232812AbhBCU6U (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 3 Feb 2021 15:58:20 -0500
Received: from mga01.intel.com ([192.55.52.88]:12604 "EHLO mga01.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S232784AbhBCU6K (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 3 Feb 2021 15:58:10 -0500
IronPort-SDR: 
 K21N+YgWdOY/YDXmcWfNW+1mtjdAo7tYF5zXgp/gVvjbMLG3YmtJI5kkS2jEVOQz2FUrnf/WXM
 CGctj5SPTNQQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9884"; a="200084222"
X-IronPort-AV: E=Sophos;i="5.79,399,1602572400";
   d="scan'208";a="200084222"
Received: from orsmga002.jf.intel.com ([10.7.209.21])
  by fmsmga101.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 03 Feb 2021 12:57:28 -0800
IronPort-SDR: 
 K26s3NvHcap36eZnRUHuzYw+PL6N+gSX1FVIK6Zy3LajbF9ZmnRbBLhVGu6pzRDCSlak4Uww72
 FqbIe5f0XY0A==
X-IronPort-AV: E=Sophos;i="5.79,399,1602572400";
   d="scan'208";a="372510543"
Received: from megha-z97x-ud7-th.sc.intel.com ([143.183.85.154])
  by orsmga002-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-SHA;
 03 Feb 2021 12:57:28 -0800
From: Megha Dey <megha.dey@intel.com>
To: tglx@linutronix.de
Cc: linux-kernel@vger.kernel.org, dave.jiang@intel.com,
        ashok.raj@intel.com, kevin.tian@intel.com, dwmw@amazon.co.uk,
        x86@kernel.org, tony.luck@intel.com, dan.j.williams@intel.com,
        megha.dey@intel.com, jgg@mellanox.com, kvm@vger.kernel.org,
        iommu@lists.linux-foundation.org, alex.williamson@redhat.com,
        bhelgaas@google.com, maz@kernel.org, linux-pci@vger.kernel.org,
        baolu.lu@linux.intel.com, ravi.v.shankar@intel.com
Subject: [PATCH 01/12] x86/irq: Add DEV_MSI allocation type
Date: Wed,  3 Feb 2021 12:56:34 -0800
Message-Id: <1612385805-3412-2-git-send-email-megha.dey@intel.com>
X-Mailer: git-send-email 2.7.4
In-Reply-To: <1612385805-3412-1-git-send-email-megha.dey@intel.com>
References: <1612385805-3412-1-git-send-email-megha.dey@intel.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Thomas Gleixner <tglx@linutronix.de>

For the upcoming device MSI support a new allocation type is
required.

Signed-off-by: Thomas Gleixner <tglx@linutronix.de>
Signed-off-by: Megha Dey <megha.dey@intel.com>
---
 arch/x86/include/asm/hw_irq.h | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH v15 01/14] KVM: x86: Report XSS as an MSR to be saved if there are supported features
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Weijiang <weijiang.yang@intel.com>
X-Patchwork-Id: 12064037
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id AC365C433DB
	for <kvm@archiver.kernel.org>; Wed,  3 Feb 2021 11:23:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4C28F64DE8
	for <kvm@archiver.kernel.org>; Wed,  3 Feb 2021 11:23:23 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234162AbhBCLWx (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 3 Feb 2021 06:22:53 -0500
Received: from mga01.intel.com ([192.55.52.88]:28338 "EHLO mga01.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S234141AbhBCLWs (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 3 Feb 2021 06:22:48 -0500
IronPort-SDR: 
 T+7htSVXndwn1ohFP5D447d8cIPakNw1tmXDr7bT7uyyhYxHObwbTlKJCcj2vhEtJhAnZd7nAu
 6jTWBICp0gGw==
X-IronPort-AV: E=McAfee;i="6000,8403,9883"; a="199981242"
X-IronPort-AV: E=Sophos;i="5.79,398,1602572400";
   d="scan'208";a="199981242"
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by fmsmga101.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 03 Feb 2021 03:22:08 -0800
IronPort-SDR: 
 Kmuh6o1jdahJ9iaXwcBWw6/DPf6Ajo67xkn8XZu8I+qbUbFfITiIouK4ClYiZhF5mHXMPFSfi3
 GauSTKsQDxjw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.79,398,1602572400";
   d="scan'208";a="480311076"
Received: from unknown (HELO local-michael-cet-test.sh.intel.com)
 ([10.239.159.166])
  by fmsmga001.fm.intel.com with ESMTP; 03 Feb 2021 03:22:06 -0800
From: Yang Weijiang <weijiang.yang@intel.com>
To: pbonzini@redhat.com, seanjc@google.com, jmattson@google.com,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: yu.c.zhang@linux.intel.com,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Yang Weijiang <weijiang.yang@intel.com>
Subject: [PATCH v15 01/14] KVM: x86: Report XSS as an MSR to be saved if there
 are supported features
Date: Wed,  3 Feb 2021 19:34:08 +0800
Message-Id: <20210203113421.5759-2-weijiang.yang@intel.com>
X-Mailer: git-send-email 2.17.2
In-Reply-To: <20210203113421.5759-1-weijiang.yang@intel.com>
References: <20210203113421.5759-1-weijiang.yang@intel.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Sean Christopherson <sean.j.christopherson@intel.com>

Add MSR_IA32_XSS to the list of MSRs reported to userspace if
supported_xss is non-zero, i.e. KVM supports at least one XSS based
feature.

Co-developed-by: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Yang Weijiang <weijiang.yang@intel.com>
---
 arch/x86/kvm/x86.c | 6 ++++++
 1 file changed, 6 insertions(+)

```
#### [PATCH v6 01/19] KVM: x86/xen: fix Xen hypercall page msr handling
##### From: David Woodhouse <dwmw2@infradead.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Woodhouse <dwmw2@infradead.org>
X-Patchwork-Id: 12064525
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 84E16C433DB
	for <kvm@archiver.kernel.org>; Wed,  3 Feb 2021 15:02:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 358CA64F86
	for <kvm@archiver.kernel.org>; Wed,  3 Feb 2021 15:02:41 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233265AbhBCPCj (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 3 Feb 2021 10:02:39 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:34048 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S232317AbhBCPCg (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 3 Feb 2021 10:02:36 -0500
Received: from merlin.infradead.org (merlin.infradead.org
 [IPv6:2001:8b0:10b:1231::1])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id A4A57C06178B
        for <kvm@vger.kernel.org>; Wed,  3 Feb 2021 07:01:21 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; q=dns/txt; c=relaxed/relaxed;
        d=infradead.org; s=merlin.20170209;
 h=Sender:Content-Transfer-Encoding:
        MIME-Version:References:In-Reply-To:Message-Id:Date:Subject:Cc:To:From:
        Reply-To:Content-Type:Content-ID:Content-Description;
        bh=WxoQ1CqwF7NNgJE6+LIgARHmwqvU7OUu+oZngDmfLnM=;
 b=Xdu3hUP226GQm/2LfyeFIk/N7W
        AGSHJL6qtt2FJEj9pMOEi4T/D7ZIPBEIRnTSnbfImn8jkGXIn96b0IEKyHr1F8j5PhIQkalZd5uxz
        zf51xk3dXudpQAGdhSaxeHptbeen7zEBDgDwsZZ2HIGWh3MYl/6XXKKnvlvtj0JwvD7D2bEY29lnd
        bD/UOUrne3mz/BhkKpzwt2xUxaKBVSNme6XJoCuEr/kfxJT1lI4TNq47BqhoHkzmbnbTqrQvVVQW5
        P4VxSvF2J96dT09YQ5KdWufoSVeQPfPmKBYxemyis1AWOiJntXvWodARam5I0Dm85DtkMPllcTzuP
        RwJE8DBw==;
Received: from i7.infradead.org ([2001:8b0:10b:1:21e:67ff:fecb:7a92])
        by merlin.infradead.org with esmtpsa (Exim 4.92.3 #3 (Red Hat Linux))
        id 1l7Jeg-00015h-4o; Wed, 03 Feb 2021 15:01:18 +0000
Received: from dwoodhou by i7.infradead.org with local (Exim 4.94 #2 (Red Hat
 Linux))
        id 1l7Jef-003reB-1j; Wed, 03 Feb 2021 15:01:17 +0000
From: David Woodhouse <dwmw2@infradead.org>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Ankur Arora <ankur.a.arora@oracle.com>,
        Joao Martins <joao.m.martins@oracle.com>,
        Boris Ostrovsky <boris.ostrovsky@oracle.com>,
        Sean Christopherson <seanjc@google.com>, graf@amazon.com,
        iaslan@amazon.de, pdurrant@amazon.com, aagch@amazon.com,
        fandree@amazon.com, hch@infradead.org
Subject: [PATCH v6 01/19] KVM: x86/xen: fix Xen hypercall page msr handling
Date: Wed,  3 Feb 2021 15:00:56 +0000
Message-Id: <20210203150114.920335-2-dwmw2@infradead.org>
X-Mailer: git-send-email 2.29.2
In-Reply-To: <20210203150114.920335-1-dwmw2@infradead.org>
References: <20210203150114.920335-1-dwmw2@infradead.org>
MIME-Version: 1.0
Sender: David Woodhouse <dwmw2@infradead.org>
X-SRS-Rewrite: SMTP reverse-path rewritten from <dwmw2@infradead.org> by
 merlin.infradead.org. See http://www.infradead.org/rpr.html
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Joao Martins <joao.m.martins@oracle.com>

Xen usually places its MSR at 0x40000000 or 0x40000200 depending on
whether it is running in viridian mode or not. Note that this is not
ABI guaranteed, so it is possible for Xen to advertise the MSR some
place else.

Given the way xen_hvm_config() is handled, if the former address is
selected, this will conflict with Hyper-V's MSR
(HV_X64_MSR_GUEST_OS_ID) which unconditionally uses the same address.

Given that the MSR location is arbitrary, move the xen_hvm_config()
handling to the top of kvm_set_msr_common() before falling through.

Signed-off-by: Joao Martins <joao.m.martins@oracle.com>
Signed-off-by: David Woodhouse <dwmw@amazon.co.uk>
---
 arch/x86/kvm/x86.c | 5 +++--
 1 file changed, 3 insertions(+), 2 deletions(-)

```
#### [PATCH 1/5 v3] KVM: SVM: Move IOPM_ALLOC_ORDER and MSRPM_ALLOC_ORDER #defines to svm.h
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 12063407
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 51375C433E6
	for <kvm@archiver.kernel.org>; Wed,  3 Feb 2021 04:22:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 14039614A7
	for <kvm@archiver.kernel.org>; Wed,  3 Feb 2021 04:22:47 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232171AbhBCEWe (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 2 Feb 2021 23:22:34 -0500
Received: from userp2120.oracle.com ([156.151.31.85]:55650 "EHLO
        userp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S233189AbhBCEU7 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 2 Feb 2021 23:20:59 -0500
Received: from pps.filterd (userp2120.oracle.com [127.0.0.1])
        by userp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 1131OPTO196046;
        Wed, 3 Feb 2021 01:28:39 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references :
 content-transfer-encoding : content-type : mime-version;
 s=corp-2020-01-29; bh=K/JC/iwkXinVeXeqOK1vvJXyi9JTK1hUBoMhLH2IIo0=;
 b=IOKTpro4IJ/REGZJeDwn0YGfT7xcSldKUIgaJLU5BT7P7WJkWu3sSvrni0h4ywTi9okP
 x9Rcub+eZkDSAxZ7iP1gG5/j1IG+X04Fk6sHEjBDwYGnfQVKtp9tjX4Iq04kKsD06xmi
 VsYUarx/saDlxcXL/hQV56BsazrIZKTDHV7XMMZTe/OsdCFS4VoEP1VQq3cOGBlNhDDa
 paCaqCNDnwZN1hg7ziI309BmXV3B9gqY6L228zqu6FnNud4BaZwGWeeiIvhmGCa1zw3s
 m9JCbuxvxUD3Tpx1exhejZy+K08q309SfL8YKAssWyLEePezOJPiGr9EvBOAJapSObjJ xA==
Received: from userp3030.oracle.com (userp3030.oracle.com [156.151.31.80])
        by userp2120.oracle.com with ESMTP id 36dn4wkg5p-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 03 Feb 2021 01:28:39 +0000
Received: from pps.filterd (userp3030.oracle.com [127.0.0.1])
        by userp3030.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 1131QYPk101028;
        Wed, 3 Feb 2021 01:28:39 GMT
Received: from nam12-dm6-obe.outbound.protection.outlook.com
 (mail-dm6nam12lp2172.outbound.protection.outlook.com [104.47.59.172])
        by userp3030.oracle.com with ESMTP id 36dhcxnvvt-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 03 Feb 2021 01:28:39 +0000
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=iRQK6sk5WGastNooi3i52iweq5RHLNv2mQAFC11sHuPls1idlBixY+rwWHm4i0xd7fkwuIFGQYOifmlY3jEgzmUaOCXtsApdliucAXCtmeYbBx4Q6D12AE20AX0XyAJrtCNQu8GlF9bhGpyf4df2T05PL2CHy2ZLLkJJ0AFPN9vPgzl6Cla9SKENxFdZ3Gh3WHPtne5BV4QvbW0ID2V95ph5JoIjERKyDB73pOewUgwso/OK+VLxG+D1CSIvulxJyG0LmMffqcTuuUo/Ahk3sMKzRiA2Z71ZppkSlRBfu2H2ctAmlpM/GgDmDHap82frnp/E3ZvmJafN1yoSbxGgdQ==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=K/JC/iwkXinVeXeqOK1vvJXyi9JTK1hUBoMhLH2IIo0=;
 b=O7vecxrYztrtotmX0vCyZb1eUYBHTn4RPmSV+ynrg1NavmXv0tuCYkhuLuo1R5ReJCz9Khh2U8IoO0TV9dTBM7beK1YbRC09DNpUlRs3hDowx8ymhxNTPC2usAzroznhap4E2h/xx9EFROPOsIKPy4po67VqsIqI4WJyZSGkUMHOEuf2mpae/Dlrygkb41yN1BS/xBQLPk0E7aZYH/tcbyLOLwJn4PIejno21DnzDmDq1Qf0iwSraagqfaRSDh8+FJGMnJJFwshxpAFbiDKigKIUkBVF3YStCYTlYlN8nQmzSQxEDge19cUzprfcA0SHAHWeO2op+bY4yaLt6DSZpA==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=oracle.com; dmarc=pass action=none header.from=oracle.com;
 dkim=pass header.d=oracle.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=oracle.onmicrosoft.com; s=selector2-oracle-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=K/JC/iwkXinVeXeqOK1vvJXyi9JTK1hUBoMhLH2IIo0=;
 b=z6ZQVNE8Thnbi6E6KsP1ilVs6xbYjj1eNME5WBAT518wM5lkquzGLnH34YICuc/8MKq6SvUZgrOY6sQuX7+wT1YKP3U/ZtZsU+3q+LBvJEt87693QvniGw4oAecDiSpQh9EubUHZv9mU6bVAvMedtTkKpPgVuJgvVKLsyIWKAO0=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=oracle.com;
Received: from DM6PR10MB3019.namprd10.prod.outlook.com (2603:10b6:5:6f::23) by
 DS7PR10MB4941.namprd10.prod.outlook.com (2603:10b6:5:38f::5) with Microsoft
 SMTP Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.3805.17; Wed, 3 Feb 2021 01:28:37 +0000
Received: from DM6PR10MB3019.namprd10.prod.outlook.com
 ([fe80::29f2:ddd5:36ac:dbba]) by DM6PR10MB3019.namprd10.prod.outlook.com
 ([fe80::29f2:ddd5:36ac:dbba%4]) with mapi id 15.20.3805.024; Wed, 3 Feb 2021
 01:28:37 +0000
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com, seanjc@google.com
Subject: [PATCH 1/5 v3] KVM: SVM: Move IOPM_ALLOC_ORDER and MSRPM_ALLOC_ORDER
 #defines to svm.h
Date: Tue,  2 Feb 2021 19:40:31 -0500
Message-Id: <20210203004035.101292-2-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.25.4
In-Reply-To: <20210203004035.101292-1-krish.sadhukhan@oracle.com>
References: <20210203004035.101292-1-krish.sadhukhan@oracle.com>
X-Originating-IP: [138.3.200.29]
X-ClientProxiedBy: SJ0PR05CA0073.namprd05.prod.outlook.com
 (2603:10b6:a03:332::18) To DM6PR10MB3019.namprd10.prod.outlook.com
 (2603:10b6:5:6f::23)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from ban25x6uut29.us.oracle.com (138.3.200.29) by
 SJ0PR05CA0073.namprd05.prod.outlook.com (2603:10b6:a03:332::18) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3825.15 via Frontend
 Transport; Wed, 3 Feb 2021 01:28:36 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 8f61fe6e-167a-4127-bd08-08d8c7e3079b
X-MS-TrafficTypeDiagnostic: DS7PR10MB4941:
X-Microsoft-Antispam-PRVS: 
 <DS7PR10MB494134FDF91485483186182481B49@DS7PR10MB4941.namprd10.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:3513;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 T/XJCh2OrFxTBXbe/IOHKmbMpfbgPj+34/UTq9b2ZGX6X3WBrFfm4TZOY4bvbohNcnKLN9f0fVJKgLLvYAd+A7ZSnu4+QWqlmMN5sDKo5z+jHdb2jW7fwGMk2MjXDiGMqDwYedHnuGHA25SmP7ZD5JM1MKc5P+dwsoqlO3WlaFNugl/sJJiZUCI0304l6k0qaWFD+qnDfVkSGCAE1bqaM/SDOp7iNlA80bPStdrFi67Y5OiPdNL3eHgw4RtC437hSg99qIdotQWMi/nzttGpV18QAVnEN0MXaPS/uncQFFMyS2RHDu15N62CHU7Qpr861yyZN4SGJOxGkeoCtXM39VO3Kcf1xLcvBmnyA1Hj2EeIrvyEzEUBz5BylRGIOe4XFIo0ftCDTMgwXE6beIPDRpiLMeH8CglC2tgGSsvddclS6moQoQUzOoitKYCVhHBduYeeKuVPsjSRTe6TfUHBq5kFkRwMOdkjTm8sK4ZqNuW8fBHH/NLLTr/rsTLV7bF4MgCbvI9xBjZrB4IXsYezsA==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM6PR10MB3019.namprd10.prod.outlook.com;PTR:;CAT:NONE;SFS:(136003)(366004)(376002)(346002)(39860400002)(396003)(316002)(36756003)(7696005)(6486002)(83380400001)(6666004)(2616005)(8936002)(1076003)(66946007)(2906002)(186003)(4326008)(5660300002)(86362001)(6916009)(66556008)(16526019)(44832011)(956004)(26005)(52116002)(66476007)(8676002)(478600001);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 4qqYfF1HV0kb789o9P12YKscQmX/rl+woVKlnVonnHF1qLySnSDIhdNGPrrshyI5SXsf5W29ML34s5E/7N754kJfRYQQDCXtR9bq9K5/e++Gizun6ntvd6SpRSXVVtz8uGi6sTgeqlKU9/MfUwemty0vW4vU2o3L/ewE6hLPIwB++AF/mlgXAS8AlnfMwWeb7TdFLXBMrp5FCXbo+uQGNDnt22RNqWgtnR28XoecvgFCMpi43t36HFAXQGJz+6E8GyFPsZ9tYmtaHg4QuNL+8XnUYad+/pj8zUckzsLPPSWS5iOaaLlPIPMzsvs1fuJimokfaH5GFczzKX/9VKEb2I7QmFpn5vgkfQ2hGRHTRVjETYkJdcMpudqA8J0nkHKJ8QHyKVH8JmK578dDMzmC3jUXj+kEj6YbZTWXeUzSjvHkiVoARVnVqeBlVl8+wqYrAe36jwuYq40D9YddSKUdFI2lyyb1ZrPNwgZ9yTpq5FnsVTcYYdpkJFD/AHEItH0a/KrjtZLZGK9cYyIO6o0/PqfEye3Beyj1iljfJB+WqqfQqsydPQV/OjP8I9OsmgVY0Yi7CnWp4LPuYv93l7XLa1WD3ogjVsq4KKUNjm3H6M7It9ztupp9fvqCifBusNHu0PAkk3mZ/nbTO9P5o+VnmLoYgGwMVBTq2Onv8Y+/nqe461OvLi7AwRAcB+Rf7V1DgGvZb0KyJxPhUbuZxrMpKgLY2SYnWjpc3ozJMOtvlHE2SR8084rxC6rIZW4IP+lT7Uukb3dv3FoNcgX4mHhu65pmVMRd9RZThNi/iZVzr5RnDGMdMoMJQr3Hz20Q2klki00wyYRFvB02iNZ/sUc5VDeZR5fylLKRAZqwtLcxim/UE/wIBXKGw6NzB8D1psGYfKs5ppGmJNevcFw5UDcjcWabsNHV9HS5W0GNRh0nP7CPtOJngrMaCAAt0dfPW6fRDwg3oYta2MZZhKYSDNFVPE/kn6kdmhgTeqc+fBwlhjRMubkkpzjcKexur3fmYOu3D5qclbJ2+xKYtQgwRHSFGTgxMKJWQ3qtVA3XxKZLGlfSHBH5ftF9gxO1YDR28Qa7
X-OriginatorOrg: oracle.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 8f61fe6e-167a-4127-bd08-08d8c7e3079b
X-MS-Exchange-CrossTenant-AuthSource: DM6PR10MB3019.namprd10.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 03 Feb 2021 01:28:37.5393
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 4e2c6054-71cb-48f1-bd6c-3a9705aca71b
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 alZq75si0vrNAYefmY4LmC2QvI0ksiiyvvGXNDejCu1iScLEUT/USXkKhVc6dyhXp2UelGxyLZzkBbckE3wmm2zjx99lf/0mV/tOm4Mcs+Q=
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DS7PR10MB4941
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9883
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 mlxscore=0
 mlxlogscore=999 phishscore=0
 spamscore=0 suspectscore=0 malwarescore=0 adultscore=0 bulkscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2102030004
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9883
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 impostorscore=0
 lowpriorityscore=0
 spamscore=0 priorityscore=1501 suspectscore=0 phishscore=0 mlxlogscore=999
 malwarescore=0 clxscore=1015 bulkscore=0 adultscore=0 mlxscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2102030004
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

These #defines will be used by nested.c in the next patch. So move these to
svm.h.

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 arch/x86/kvm/svm/svm.c | 3 ---
 arch/x86/kvm/svm/svm.h | 3 +++
 2 files changed, 3 insertions(+), 3 deletions(-)

```
#### [PATCH kvm-unit-tests] x86: add CR4.DE test to debug.flat
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 12064153
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.3 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C875BC433DB
	for <kvm@archiver.kernel.org>; Wed,  3 Feb 2021 11:44:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 746E564F6A
	for <kvm@archiver.kernel.org>; Wed,  3 Feb 2021 11:44:03 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234492AbhBCLnw (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 3 Feb 2021 06:43:52 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:56299 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S234309AbhBCLn2 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 3 Feb 2021 06:43:28 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1612352522;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=OfqkjnbtlUpza4EJUYhtV6VOU79DHIWSQvvvHKGSL+o=;
        b=RDo+UGja+iBHPnOFFS76RKo0A4L+lt/XwD83vdY2Jl055rLiuB8XNmZqPcP+8qY4DkiYcK
        WCJvERwlH/VQI7YBBnuJ3YLj2RMqgcECS1Lrr9rGX4S/CRj363iPWtcX0IOLWr7XHzjHSO
        5nP7zZke6Qn1I0BYMwydsdIM7Jk9uCQ=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-290-3kcqkNX4MCeKeWSwBXHHnQ-1; Wed, 03 Feb 2021 06:41:59 -0500
X-MC-Unique: 3kcqkNX4MCeKeWSwBXHHnQ-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id B7BE6801817
        for <kvm@vger.kernel.org>; Wed,  3 Feb 2021 11:41:58 +0000 (UTC)
Received: from virtlab511.virt.lab.eng.bos.redhat.com
 (virtlab511.virt.lab.eng.bos.redhat.com [10.19.152.198])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 866975B692
        for <kvm@vger.kernel.org>; Wed,  3 Feb 2021 11:41:58 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: kvm@vger.kernel.org
Subject: [PATCH kvm-unit-tests] x86: add CR4.DE test to debug.flat
Date: Wed,  3 Feb 2021 06:41:57 -0500
Message-Id: <20210203114157.132669-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Check whether reading/writing DR4 generates an undefined opcode exception.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 x86/debug.c | 36 ++++++++++++++++++++++++++++++++++++
 1 file changed, 36 insertions(+)

```
#### [PATCH] KVM: vmx/pmu: Add VMCS fields check before exposing LBR_FMT
##### From: Like Xu <like.xu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Like Xu <like.xu@linux.intel.com>
X-Patchwork-Id: 12063493
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B6EFEC433E9
	for <kvm@archiver.kernel.org>; Wed,  3 Feb 2021 06:59:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8A2D964F77
	for <kvm@archiver.kernel.org>; Wed,  3 Feb 2021 06:59:06 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231773AbhBCG6u (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 3 Feb 2021 01:58:50 -0500
Received: from mga09.intel.com ([134.134.136.24]:46077 "EHLO mga09.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S230193AbhBCG6t (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 3 Feb 2021 01:58:49 -0500
IronPort-SDR: 
 LKHcjCk+MCJOvNtZ5Ana8J3Ine1IkrgSWZnOOmdLa9Wo5Q6rIkeBZ2wQcSdP4s+6LswureBZWf
 Pm2Ed3Gwj8LA==
X-IronPort-AV: E=McAfee;i="6000,8403,9883"; a="181141693"
X-IronPort-AV: E=Sophos;i="5.79,397,1602572400";
   d="scan'208";a="181141693"
Received: from orsmga001.jf.intel.com ([10.7.209.18])
  by orsmga102.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 02 Feb 2021 22:57:02 -0800
IronPort-SDR: 
 yOYFXDoNims9sTqJO4yYV6ttQ36oBupccKAADmqXcJlbXrJY+OxBeeDTAfwotfwrqyU/ADOYoQ
 iCMOiQxyy+8w==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.79,397,1602572400";
   d="scan'208";a="433239012"
Received: from clx-ap-likexu.sh.intel.com ([10.239.48.108])
  by orsmga001.jf.intel.com with ESMTP; 02 Feb 2021 22:56:59 -0800
From: Like Xu <like.xu@linux.intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: vmx/pmu: Add VMCS fields check before exposing LBR_FMT
Date: Wed,  3 Feb 2021 14:50:27 +0800
Message-Id: <20210203065027.314622-1-like.xu@linux.intel.com>
X-Mailer: git-send-email 2.29.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Before KVM exposes guest LBR_FMT perf capabilities, it needs to check
whether VMCS has GUEST_IA32_DEBUGCTL guest status field and vmx switch
support on IA32_DEBUGCTL MSR (including VM_EXIT_SAVE_DEBUG_CONTROLS
and VM_ENTRY_LOAD_DEBUG_CONTROLS). It helps nested LBR enablement.

Signed-off-by: Like Xu <like.xu@linux.intel.com>
---
 arch/x86/kvm/vmx/capabilities.h | 9 ++++++++-
 1 file changed, 8 insertions(+), 1 deletion(-)

```
#### [PATCH v2 1/4] KVM: vmx/pmu: Add MSR_ARCH_LBR_DEPTH emulation for Arch LBR
##### From: Like Xu <like.xu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Like Xu <like.xu@linux.intel.com>
X-Patchwork-Id: 12064443
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A59B0C433E0
	for <kvm@archiver.kernel.org>; Wed,  3 Feb 2021 14:05:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5B62F64DDA
	for <kvm@archiver.kernel.org>; Wed,  3 Feb 2021 14:05:53 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232486AbhBCOFi (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 3 Feb 2021 09:05:38 -0500
Received: from mga06.intel.com ([134.134.136.31]:50302 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S232302AbhBCOFf (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 3 Feb 2021 09:05:35 -0500
IronPort-SDR: 
 nKgPjW8WSVK43il7hU8YGM4/fohudX1V2RTcadFSaEa4cBfvxaySjesaMsfyAIEA+O62v90kWf
 Ir1W4DhqKTbQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9883"; a="242555104"
X-IronPort-AV: E=Sophos;i="5.79,398,1602572400";
   d="scan'208";a="242555104"
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by orsmga104.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 03 Feb 2021 06:03:48 -0800
IronPort-SDR: 
 IdoAe0NWdoJtsMpMomGj4eKqv2iNsccsax1V1CVG3JDMYJ4VtIXTc3kgIckbg1KcWcYwS6zXDT
 yrQHMdtOAc2g==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.79,398,1602572400";
   d="scan'208";a="371490654"
Received: from clx-ap-likexu.sh.intel.com ([10.239.48.108])
  by fmsmga008.fm.intel.com with ESMTP; 03 Feb 2021 06:03:45 -0800
From: Like Xu <like.xu@linux.intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v2 1/4] KVM: vmx/pmu: Add MSR_ARCH_LBR_DEPTH emulation for
 Arch LBR
Date: Wed,  3 Feb 2021 21:57:11 +0800
Message-Id: <20210203135714.318356-2-like.xu@linux.intel.com>
X-Mailer: git-send-email 2.29.2
In-Reply-To: <20210203135714.318356-1-like.xu@linux.intel.com>
References: <20210203135714.318356-1-like.xu@linux.intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The number of Arch LBR entries available for recording operations
is dictated by the value in MSR_ARCH_LBR_DEPTH.DEPTH. The supported
LBR depth values can be found in CPUID.(EAX=01CH, ECX=0):EAX[7:0]
and for each bit n set in this field, the MSR_ARCH_LBR_DEPTH.DEPTH
value 8*(n+1) is supported.

On a software write to MSR_ARCH_LBR_DEPTH, all LBR entries are reset
to 0. Emulate the reset behavior by introducing lbr_desc->arch_lbr_reset
and sync it to the host MSR_ARCH_LBR_DEPTH msr when the guest LBR
event is ACTIVE and the LBR records msrs are pass-through to the guest.

Signed-off-by: Like Xu <like.xu@linux.intel.com>
---
 arch/x86/kvm/vmx/pmu_intel.c | 43 ++++++++++++++++++++++++++++++++++++
 arch/x86/kvm/vmx/vmx.h       |  3 +++
 2 files changed, 46 insertions(+)

```
#### [PATCH 1/3] KVM: SVM: Replace hard-coded value with #define
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 12063195
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B1E4AC433DB
	for <kvm@archiver.kernel.org>; Wed,  3 Feb 2021 02:17:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 79DBB64F50
	for <kvm@archiver.kernel.org>; Wed,  3 Feb 2021 02:17:56 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232027AbhBCCRx (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 2 Feb 2021 21:17:53 -0500
Received: from aserp2120.oracle.com ([141.146.126.78]:49754 "EHLO
        aserp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S230087AbhBCCRu (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 2 Feb 2021 21:17:50 -0500
Received: from pps.filterd (aserp2120.oracle.com [127.0.0.1])
        by aserp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 1132FliO008298;
        Wed, 3 Feb 2021 02:16:50 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references :
 content-transfer-encoding : content-type : mime-version;
 s=corp-2020-01-29; bh=cOTE7Y8ZqD5+Y50rLYXL8ENXmTwJEN8O4esUDbNCmqc=;
 b=0dnuyx8gQu9oPUkKEoLyiMRuCk/v7Pl7pEWUVu1Jj3LrTdWUxZNWq5m0ThOcPTaemIo7
 1CSDOaxPv6FiW170AfKHHJpvW/wMnmTKgGMIeee1gELYCvzQIY9I9Ro5Iby7Gx6devpa
 7NAWUnmQvo6lC4wZ+Bzbs5cAgJoRvutUZoA5gCCalTUT9nezuk2Ac/UUiaNqHjFII5I8
 rOVPL1nEQeqqH585MDJhuM+zLsSy2w+yqctKdygZdfZ5NXsnr+ztaQMEeRBAeiLIZw/q
 3Xw29xoz5V8bWzOaMhw/YVV94C0LdEzXrhBHQI4fn+VsaM0MSc5Rz05TaO/yMqZ+k4yG FA==
Received: from userp3030.oracle.com (userp3030.oracle.com [156.151.31.80])
        by aserp2120.oracle.com with ESMTP id 36cydkwq0v-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 03 Feb 2021 02:16:50 +0000
Received: from pps.filterd (userp3030.oracle.com [127.0.0.1])
        by userp3030.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 1132Eanb110778;
        Wed, 3 Feb 2021 02:16:49 GMT
Received: from nam10-bn7-obe.outbound.protection.outlook.com
 (mail-bn7nam10lp2102.outbound.protection.outlook.com [104.47.70.102])
        by userp3030.oracle.com with ESMTP id 36dhcxqdsa-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 03 Feb 2021 02:16:49 +0000
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=RD60Wu6p2y1tr7Ig5Pq7hAOVDqu9xdVJnFOyMoqW/z5qEl2FQiZgWxE80FTXRyc7PfuhevnMjlxo5jqOi55iYZ+mZJA++bU1JndGou0zP10TrWXqmnu9rt9Cy8fft4DudOgbGiv20QxcrZxk2oiiyUpc3Rg/x4VtTD7fSS45ADNPzELuls+UReLOlDhLMYxOgb+Z3EfTXRCNIYtwpj6R5MmBduQhSjkcF9Gn3HjwBu8QzwIKOQtjwB4aPWclbq4/wWrgRA3Ia5hoft6lBsFTUHuMuk4lDB3uSr6wjfH3l8nzkDBI5OTQ4CC+gUln8TARnE5vsvj9qVMH5jmjViC0LQ==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=cOTE7Y8ZqD5+Y50rLYXL8ENXmTwJEN8O4esUDbNCmqc=;
 b=CzOVDn2qLYzMM5ws1zt7LtOzixC7ZbOQVdINo6MI+Jblblbtghjah0LUEOT/4msaKPwlmfNNAdgZPf3y42VOoqSLYbctj0CQSeqG0iDHuJYd0XOmOOUrfxN2JSFo+Wtb8H3x5B3WWSsRTFziX3C+VJSUc1R+kc87Gt0cD4wBEDhxxycCd7u9V5lRnxJAxVBM0PLv9cevm0UZIZEFSSYE7ZxJATE3HFFzkxJ+fPTFvouRxmk3ANsNj/v+MOJ/XfpmGD4VzmC9r6aBiUuu+uH6wC2wKyLfB5ptXhSxAI18XsO09rPlXtN5mESSkwPHjbdvzPyqQbf+HmYwOwUBpxLBjw==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=oracle.com; dmarc=pass action=none header.from=oracle.com;
 dkim=pass header.d=oracle.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=oracle.onmicrosoft.com; s=selector2-oracle-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=cOTE7Y8ZqD5+Y50rLYXL8ENXmTwJEN8O4esUDbNCmqc=;
 b=Vove83Fe9nof2JZ6gacMN5/dNlPMx7W218oUmvUCvGMttfa3kcALrV1Tn5ygu180a6ORZnoc84clO9K3UDJ8wNlfaEVGErtJ74GGcwaOe3WISym8U2kWh99bSIMbTIFh8N9BC9rQOOoD03Q/cbBf3daOBFp2IRn55jwUFQ7e7FU=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=oracle.com;
Received: from SN6PR10MB3021.namprd10.prod.outlook.com (2603:10b6:805:cc::19)
 by SA2PR10MB4793.namprd10.prod.outlook.com (2603:10b6:806:110::24) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3805.17; Wed, 3 Feb
 2021 02:16:47 +0000
Received: from SN6PR10MB3021.namprd10.prod.outlook.com
 ([fe80::1871:3741:cc17:bcf7]) by SN6PR10MB3021.namprd10.prod.outlook.com
 ([fe80::1871:3741:cc17:bcf7%7]) with mapi id 15.20.3825.020; Wed, 3 Feb 2021
 02:16:47 +0000
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com, seanjc@google.com
Subject: [PATCH 1/3] KVM: SVM: Replace hard-coded value with #define
Date: Tue,  2 Feb 2021 20:28:40 -0500
Message-Id: <20210203012842.101447-2-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.25.4
In-Reply-To: <20210203012842.101447-1-krish.sadhukhan@oracle.com>
References: <20210203012842.101447-1-krish.sadhukhan@oracle.com>
X-Originating-IP: [138.3.200.29]
X-ClientProxiedBy: SJ0PR03CA0096.namprd03.prod.outlook.com
 (2603:10b6:a03:333::11) To SN6PR10MB3021.namprd10.prod.outlook.com
 (2603:10b6:805:cc::19)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from ban25x6uut29.us.oracle.com (138.3.200.29) by
 SJ0PR03CA0096.namprd03.prod.outlook.com (2603:10b6:a03:333::11) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3825.19 via Frontend
 Transport; Wed, 3 Feb 2021 02:16:45 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 3f5d3c58-c0c2-4856-e69e-08d8c7e9c182
X-MS-TrafficTypeDiagnostic: SA2PR10MB4793:
X-Microsoft-Antispam-PRVS: 
 <SA2PR10MB47937B05D025DAA1670E274E81B49@SA2PR10MB4793.namprd10.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:3044;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 MXbeph7s57xoFdBIbLZZ733u3GlhL8kSydX8IK7eBgJngM/CbXoqWYH588+iZk7Ez59aiW0DeUDTSOzEw083msjLkfpsKGVUX4pNLYwIimzDB2yTtSea4Xb+VmLYI6MjJuzZOiLPLdEXUuoOKIQ0WQKSwouPJF5IPMgq/uAMFWQkMJxkMSW/KyAaXxXuXLSMIh78V0jCy6q6oWTW6KyWYl3l3wyjD9x55ja7AE9yqmkBNzxvT63uwgd8liLlBe7LmWZJIaDpTIbCbWTyBOic6Qa29Pq1EW3yso2ULqfT0IwSgRzp4pTBWqGXAK6QLi+Ybdn36v46VQG6X2ztdU2AoZxV0ty/ng8xnXF5kMQxd5rMUVjJd4UpkB5ZPPSsRJVoOusNEf4Mp+YGYgNiKKc3LaWh9FgWrwpSCE6LI4IjBQSvtau6+ZXOr5bOcy5bru5u+BoyiFOnIzuyubavFudRxBlZa/gvapw5QjpRlOh0QW03cDug+OwOFnKDlEIasXMxSEWZaKjuIzrWq5MW8/lkzQ==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN6PR10MB3021.namprd10.prod.outlook.com;PTR:;CAT:NONE;SFS:(366004)(39860400002)(376002)(346002)(396003)(136003)(316002)(6666004)(36756003)(8676002)(66946007)(16526019)(66476007)(6486002)(7696005)(83380400001)(4326008)(6916009)(2906002)(86362001)(4744005)(5660300002)(956004)(186003)(1076003)(44832011)(52116002)(8936002)(26005)(478600001)(2616005)(66556008);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 m+tKoxS5gadJjLYOwMRb4i8bV4kz+TAnzAljPQXZ/5GOXZ8o0r3pVVCFG4FN7kvLbtKrhH8zGMBPP/cx9uTWjJchGdvB5qcf5ehrPJfoNst2JDyCCZMnd+rJKEAc5GadehYEUH2c8MzcN+jr8bEKzVM8+7jNeH9fzrHfd8NmqFHez7YXcoghtGIbHXv8CLIO3c3qcUbntzmhFmhKbsV9kTuWUAxBGti1+RhJvzNFRhEsX/3ujkLYYhJW6OaVOMYDLgZZWHwYgCuCJfTkPRU0/k4hHQGE+quKiHT8jajst/BEwUCdVBdXwwJjMYNWv5taX51dNb1n0pH170p3TbbEXu6Wc4nK9RHaCr2JYb5e6av4Ub7vJ/X6XGC+hD+ifbwIBVryqhomfxIOFeTtQO+uNM1jtFeDHCbRqas1mXXVZBlFT4s9Pk2ojSRsgJBfJUfVdSEZnP4MDvDuEZBCR/CVinwAjiBPfxIz7PwdblYfxQythjdPJsnUuviF7IJy7eL4KF2dYoxoywbDTs2PH+3vayOeKAe9oqibEWmSfwbGd8Hq/GPN1+ydRx1iXLBheB+x1N/Rdi+eY3tEdYcSr23QLh6trYGp8x1BZYJSwdS3eSQaZil7Mh/ByQEnh7wBCY9iECHxxm0OcE6g/jwcVAQO3cz3C7kJEqP21Lh2e2zlRshHKKpbTPezArwW4b3GIuCOhQtorTjaMXdNbiCg5wVHMcxSag+9/YfWs/wkOCxxWVysQeLSPKg6zwuMHd0yaZjkSBMEloAEbwOYXnUaOrwlstMA2MJ8ZpPW44l+YwPxiY6cVvPHwNchNghOI/F4tkv40J6VZU6FWVZgGptHhmLTy6L/NhWpkQ2g060c8OtoWIc7oEWVUewDk1lbGTQP9CC7sNkF68SaC5C/Ks1kGvbAErQzBnc5DSsPczhdjqBttnPMikBw2K7MAOTCOKCU5Z4Sdg0+ITgtOetF+DPg0OaGjMuQaWf0ggsI+O9Za5GApJRjzZMrA77lP6dyz5K0MlV+R4Zys/CXiNsExB3TviJhU4ag5DcO+832xpHfMAgUvYeWL+XTdXk4h+ucR9MkjUce
X-OriginatorOrg: oracle.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 3f5d3c58-c0c2-4856-e69e-08d8c7e9c182
X-MS-Exchange-CrossTenant-AuthSource: SN6PR10MB3021.namprd10.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 03 Feb 2021 02:16:47.1237
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 4e2c6054-71cb-48f1-bd6c-3a9705aca71b
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 rbf+U6OkSJ8nvckq35fG2oeoPm8XdQuk3rd6SJhRqY2XATCOIyvde0Bu49og3N5ZGV8/wAD5c7v8y9iysL9Qgf10eIioppGnAV2n0BYII0Q=
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SA2PR10MB4793
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9883
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 mlxscore=0
 mlxlogscore=849 phishscore=0
 spamscore=0 suspectscore=0 malwarescore=0 adultscore=0 bulkscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2102030007
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9883
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 bulkscore=0
 adultscore=0
 priorityscore=1501 impostorscore=0 malwarescore=0 clxscore=1015
 spamscore=0 lowpriorityscore=0 phishscore=0 mlxlogscore=906 mlxscore=0
 suspectscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2102030007
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Replace the hard-coded value for bit# 1 in EFLAGS, with the available
#define.

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 arch/x86/kvm/svm/svm.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH 1/3] vfio/type1: change success value of vaddr_get_pfn()
##### From: Daniel Jordan <daniel.m.jordan@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Daniel Jordan <daniel.m.jordan@oracle.com>
X-Patchwork-Id: 12065307
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 425C4C433E0
	for <kvm@archiver.kernel.org>; Wed,  3 Feb 2021 20:50:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DFD5A64F7C
	for <kvm@archiver.kernel.org>; Wed,  3 Feb 2021 20:50:22 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232508AbhBCUuS (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 3 Feb 2021 15:50:18 -0500
Received: from aserp2120.oracle.com ([141.146.126.78]:42628 "EHLO
        aserp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S232124AbhBCUtc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 3 Feb 2021 15:49:32 -0500
Received: from pps.filterd (aserp2120.oracle.com [127.0.0.1])
        by aserp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 113KdAmk067581;
        Wed, 3 Feb 2021 20:48:15 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references :
 content-transfer-encoding : content-type : mime-version;
 s=corp-2020-01-29; bh=2ZreSZ/bhNS5lb4e8nZsVdrMkQw3askAFxPJQlHc5xY=;
 b=JY9cJI9ZkFlN9vNaSl5K35lgzV+ZpVH8Fh9Gp+LeINbZFLdhMsjdA/bKn1jiE4YpS6Vt
 zcO7bYWKC3zq6mHbK1M/gw+8wmUe3FQU/Wmw/NNACE4moitw5d1ybc2zJ0mYEuwy6MX7
 4TD743/I2dhEP7GucAZ3PG3vnvambPt7WIpY18D0JCS9VErFZl+88i5ErNGUxmkqzEdJ
 zNxcdEbCrUviZY5olotqWT8DngVjOx6tozz2oF+V89ITEWgYSPul+/ubeHXETpbMKPQy
 lZGKN1UCO4ycsljJf34rqQREtBeXvyTEVXiIjyu6EhZuAU2Dd3jgckHGZdev2vj/GrVT qg==
Received: from aserp3020.oracle.com (aserp3020.oracle.com [141.146.126.70])
        by aserp2120.oracle.com with ESMTP id 36cydm255k-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 03 Feb 2021 20:48:15 +0000
Received: from pps.filterd (aserp3020.oracle.com [127.0.0.1])
        by aserp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 113Kj3ic135633;
        Wed, 3 Feb 2021 20:48:15 GMT
Received: from nam04-bn8-obe.outbound.protection.outlook.com
 (mail-bn8nam08lp2044.outbound.protection.outlook.com [104.47.74.44])
        by aserp3020.oracle.com with ESMTP id 36dhc1qb23-2
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 03 Feb 2021 20:48:14 +0000
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=m5Kdgr09DIzhzZtj2qzlMI1p5qR2jGugM1C+DT4ByWkmQpUqfzDM/VEXD+jrjvF8UMHY8uMyB0l95OC2RAROYRFK/TP017wOU9OtOfUNH3Q1XAcu3imr6NDexbMQHcr5KlYXonzXBuDupbJw3zLpM0ICLWooYc8iYQRJMGoS3qli/vhFPYjrEidNhz3kbTN65y+uHKl/Foz0ZMPYBG92XMtJDcAANwwQNHHDugXi//U3lMT9daWADp6DhXmTabIwGJoDpFWbkw9fB5ZDFEjo8h/tf5BpAEdGNza0tL389QbxqakZHXxfW1Q774/EiX/rs5ELsQPQ0IG/DGDw1+SZxg==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=2ZreSZ/bhNS5lb4e8nZsVdrMkQw3askAFxPJQlHc5xY=;
 b=DJujVk7QF6Ttnulmezs86K7yO3wNYux8OfhkxubUEq8IDa88F3lOmrtLICfHAT8kQ5vlZyq2wQpgLz+wn7dqFUTObO1Je6JKhePBBAwXLyD1Ox2u/MJpZ0NVvTAv7WmudWp+l6EpPZB3nPH3s781rp1uym6E0orXqkK5SlStdFB2mY0zRuw/r7z+HYIa+8pg5daWkvNVuiy6GLpSA38946nHBd+vxpTU6Zse/9fDuVAm1FADXbiDEwfbYTN5n3gGDqXrDPTaQcPU4hJXES/4H64+c6vUhTcoGCI+j+RoQPiWWZtM/c4rMWRGXvDBllDazxAPiE8Pinln6U7RGcrzNA==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=oracle.com; dmarc=pass action=none header.from=oracle.com;
 dkim=pass header.d=oracle.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=oracle.onmicrosoft.com; s=selector2-oracle-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=2ZreSZ/bhNS5lb4e8nZsVdrMkQw3askAFxPJQlHc5xY=;
 b=JfNiFdcSU//+HJlXAn13tnhjnXYkekikegIwsdwAovBA/b0kiG4HFTND6UtNkc6IDDaGLgSa61M5A7XU/VbsMsO3C4sK+1DhuXwhqXvh9i35e3TPtSzEXXn12SRB5oakgUttPeQfoTITxwKAANp6MzoSBHqxQBVkzwl1PTXfbio=
Authentication-Results: redhat.com; dkim=none (message not signed)
 header.d=none;redhat.com; dmarc=none action=none header.from=oracle.com;
Received: from MWHPR10MB1774.namprd10.prod.outlook.com (2603:10b6:301:9::13)
 by CO1PR10MB4691.namprd10.prod.outlook.com (2603:10b6:303:92::19) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3825.17; Wed, 3 Feb
 2021 20:48:13 +0000
Received: from MWHPR10MB1774.namprd10.prod.outlook.com
 ([fe80::24eb:1300:dd70:4183]) by MWHPR10MB1774.namprd10.prod.outlook.com
 ([fe80::24eb:1300:dd70:4183%3]) with mapi id 15.20.3805.027; Wed, 3 Feb 2021
 20:48:13 +0000
From: Daniel Jordan <daniel.m.jordan@oracle.com>
To: Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>
Cc: Jason Gunthorpe <jgg@nvidia.com>,
        Matthew Wilcox <willy@infradead.org>,
        Pavel Tatashin <pasha.tatashin@soleen.com>,
        Steven Sistare <steven.sistare@oracle.com>,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Daniel Jordan <daniel.m.jordan@oracle.com>
Subject: [PATCH 1/3] vfio/type1: change success value of vaddr_get_pfn()
Date: Wed,  3 Feb 2021 15:47:54 -0500
Message-Id: <20210203204756.125734-2-daniel.m.jordan@oracle.com>
X-Mailer: git-send-email 2.30.0
In-Reply-To: <20210203204756.125734-1-daniel.m.jordan@oracle.com>
References: <20210203204756.125734-1-daniel.m.jordan@oracle.com>
X-Originating-IP: [98.229.125.203]
X-ClientProxiedBy: BL1PR13CA0215.namprd13.prod.outlook.com
 (2603:10b6:208:2bf::10) To MWHPR10MB1774.namprd10.prod.outlook.com
 (2603:10b6:301:9::13)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from localhost.localdomain (98.229.125.203) by
 BL1PR13CA0215.namprd13.prod.outlook.com (2603:10b6:208:2bf::10) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3825.15 via Frontend
 Transport; Wed, 3 Feb 2021 20:48:12 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: ee5d1014-c7b5-4aef-a5fa-08d8c8850645
X-MS-TrafficTypeDiagnostic: CO1PR10MB4691:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <CO1PR10MB4691799EE6A0DAA786198AA7D9B49@CO1PR10MB4691.namprd10.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:6430;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 KkaCzmyKD1VImfgJpF8lqFm+7gARO33QQgvfFFPt7h5VsKQt9ZxEz6q93+/uYxUg9vHvO7W1h6NgAGm5E7w9AZRcnBD0ez0C2GAQIwvPr62Fg8wISq7ecXXeEvjjKUmy75TNgQublPj9HYFEmv874wvIPNjrM/lSEnwWaNY2ImI4NRikNxPVuqL7h1t/W4ehVlqr4i7VmZWyUsKo/oDb5vY5BHQ+Fl576IYBWKJ7Z0nU5w2x2YRQShQ0VGf4cqdpGeU8VbYh9nH4JTLiXHKhxRE48ps4GOqMOW1bzlG3eMKlMPfS/ACrt979pvI9qkVcjVGNzHoDMEVVWbxTdlSet0GVFvWQQi3+HBu035BhYaN5Aa1/V0mMbKI04whhtOlD30okcMq/SZmwgQXY6b4mCKCcUUQVP0M4+7qi5gCBDGnT+B758GJe90Oa5oXX4npbhErWLGVwky3fQuIEhzrZcD6/CYV/9p+MQIZnPbWbSZbH/k/KdUNRX/VVTsW1PhdjD7FOG9klx4bbYQr8wCcD2YUAFBAIremNMzldq5QMn5Z2YY0hyrDKTN/MzX+OyipyKbCPLeTyM00YmSHmkK7GXA==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:MWHPR10MB1774.namprd10.prod.outlook.com;PTR:;CAT:NONE;SFS:(396003)(39860400002)(376002)(366004)(136003)(346002)(103116003)(6486002)(478600001)(36756003)(107886003)(4326008)(66946007)(8936002)(1076003)(16526019)(5660300002)(110136005)(54906003)(26005)(186003)(6506007)(69590400011)(52116002)(8676002)(86362001)(83380400001)(316002)(2906002)(6512007)(956004)(66476007)(66556008)(2616005)(6666004);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 lO8YnXDteBPPAdDc7BCpABZ2U/MOoQpVMguxnpOc47mAKgNO3W0zJr8FHTXUSI8E8fask+Su9KvX8N5ZceKQB7qzP4oL6bSAu8VO2pMpDub2X2zyjCs5FmT4D3n6Fd1D58bcotLac/CMkcIkQTckSmVjaH+0llRMUAc6kveIGR+4i7fM+jWta11R0obtVIlVyldtBY66O/VhDPjxZEjW1hUSXT6xCtAJEh/g+qAxFN9JmCK2PyYEx3MZOXkqGLvpow0tM4BAlX0O0RGhT5iehrzXEmbXFV9bnNk6Otc2yWiBJX/aOJKsNpqaPmQkypTP1NbdWIhWZZrMaS8gL+lwJtJiogmUwWlMsObOIyFo06BACMPp2l76raVku3HYm5MuyTHIRzv4d8x5vcVKEe9ANRVIAE++zaIHwNhlZhAApVS1J4BFWwIPfoAxna0tpBSCcXH7JNrmxcE+72n/KCW76jmWVBeygIEn+sb/nKp/UD90hemSAsm1c6Uix36zEwRluqCYLXurpbBr0mXBlrhIueoKs9IcIaHRHPEL0ftDG6KjzJ8l45hyjJhvffwWVNcpuHRxBOGStp2+XMNibLj66RfH4aQLLGVG264IMspavZhyA0FUszf/GdK9IhhJgDl1foWdYmeMAi8oljHfoZyIEDOJCbrEIg5H9LFtVxOiBN0xSNu9wIKzZNNZUtfl0bA8oeEdAtRi41NjEsDNElJ5vo4nvY9CKSv/DuFWtnyBZyXKe2jh8T6KzgqNbgcKaXCjPA7ZjNYSpw336HzN3lUKAsiBtYfDcR0Nb2+Y5bCKE+Qiog97yuSEe66XymJE0/XoxGnsYybetWQbQhw3hkmU7MMj6hr/ShNNDWsmc/bHgs2jPpz+namhz1csgcXwZWtj1hTZY2j+mH/GTEe0LmjN83sO2fbYNkfAwyRGPv7bwQsZLaVRaz1aMLfv5RBx9UUDOlKkFM746q+i+YyraNJOFfdDyEL6tnYq5LwFuoC9MtpWG9ER2KSdccQqVglzS4eoZ1cNjXXc8xd/LkZG/RilFViAHdumFsCYfmONwgCRfwQzWr2z2G2wGAPJ6i8nsRZnMKd5IiplyD7PoVRMchXAwXeAFiRMU6WIpdkhRKqPxKj4V//X0JlpwtrAraCEPouoU0nAQtvkw5asqVInuauBVNI9EOTr5KKT4NeMN9h5I74W1uyWOR80qNlQJ+9nGsnd2H/NzlPdIq7UEnQUDsuUGFZ2cRy+7zYzv5IJowpsvfZn/T9PmRvII/AbkJ0XkZkYNBUcGkhzrwvsLBUtSbPg5cCCPPpKwBXz7UDq4XRUSLZg+HfRNO+LN9paTNgIKta1
X-OriginatorOrg: oracle.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 ee5d1014-c7b5-4aef-a5fa-08d8c8850645
X-MS-Exchange-CrossTenant-AuthSource: MWHPR10MB1774.namprd10.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 03 Feb 2021 20:48:13.5787
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 4e2c6054-71cb-48f1-bd6c-3a9705aca71b
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 u8l08Qz9uiQyo4BceVUPkMh6kPS5WT0y7/JFA5s61g/Dtw3UOU1yw+6Q/hKEBkM4wWF7TiTIa7wrE8cMMiGQqacP2rwePfM5ROzn7qBxXaQ=
X-MS-Exchange-Transport-CrossTenantHeadersStamped: CO1PR10MB4691
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9884
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 bulkscore=0
 adultscore=0 suspectscore=0
 spamscore=0 mlxscore=0 malwarescore=0 mlxlogscore=999 phishscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2102030124
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9884
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 bulkscore=0
 adultscore=0
 priorityscore=1501 impostorscore=0 malwarescore=0 clxscore=1015
 spamscore=0 lowpriorityscore=0 phishscore=0 mlxlogscore=999 mlxscore=0
 suspectscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2102030123
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

vaddr_get_pfn() simply returns 0 on success.  Have it report the number
of pfns successfully gotten instead, whether from page pinning or
follow_fault_pfn(), which will be used later when batching pinning.

Change the last check in vfio_pin_pages_remote() for consistency with
the other two.

Signed-off-by: Daniel Jordan <daniel.m.jordan@oracle.com>
---
 drivers/vfio/vfio_iommu_type1.c | 21 ++++++++++++++-------
 1 file changed, 14 insertions(+), 7 deletions(-)

```
