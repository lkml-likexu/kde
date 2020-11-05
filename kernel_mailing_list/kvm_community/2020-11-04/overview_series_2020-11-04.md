#### [kvm-unit-tests PATCH v3 1/2] arm64: Check if the configured translation granule is supported
##### From: Nikos Nikoleris <nikos.nikoleris@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Nikos Nikoleris <nikos.nikoleris@arm.com>
X-Patchwork-Id: 11880573
Return-Path: <SRS0=TbV3=EK=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 9B958C388F7
	for <kvm@archiver.kernel.org>; Wed,  4 Nov 2020 13:03:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4544D221F8
	for <kvm@archiver.kernel.org>; Wed,  4 Nov 2020 13:03:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729816AbgKDND6 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 4 Nov 2020 08:03:58 -0500
Received: from foss.arm.com ([217.140.110.172]:36820 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726350AbgKDND5 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 4 Nov 2020 08:03:57 -0500
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 58E85142F;
        Wed,  4 Nov 2020 05:03:56 -0800 (PST)
Received: from camtx2.cambridge.arm.com (camtx2.cambridge.arm.com [10.1.7.22])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 59F823F719;
        Wed,  4 Nov 2020 05:03:55 -0800 (PST)
From: Nikos Nikoleris <nikos.nikoleris@arm.com>
To: kvm@vger.kernel.org
Cc: mark.rutland@arm.com, jade.alglave@arm.com, luc.maranget@inria.fr,
        andre.przywara@arm.com, alexandru.elisei@arm.com,
        drjones@redhat.com
Subject: [kvm-unit-tests PATCH v3 1/2] arm64: Check if the configured
 translation granule is supported
Date: Wed,  4 Nov 2020 13:03:51 +0000
Message-Id: <20201104130352.17633-2-nikos.nikoleris@arm.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20201104130352.17633-1-nikos.nikoleris@arm.com>
References: <20201104130352.17633-1-nikos.nikoleris@arm.com>
X-ARM-No-Footer: FoSSMail
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

As arm64 implementations may support a subset of the architecturally
defined granules, we need to check and warn the user if the configured
translation granule is not supported.

Signed-off-by: Nikos Nikoleris <nikos.nikoleris@arm.com>
---
 lib/arm64/asm/processor.h | 36 ++++++++++++++++++++++++++++++++++++
 lib/arm/mmu.c             |  3 +++
 2 files changed, 39 insertions(+)

```
#### [PATCH 01/11] KVM: selftests: Add x86_64/tsc_msrs_test to .gitignore
##### From: Andrew Jones <drjones@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11882167
Return-Path: <SRS0=TbV3=EK=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-9.9 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id DAA1FC4741F
	for <kvm@archiver.kernel.org>; Wed,  4 Nov 2020 21:24:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7D56A2080D
	for <kvm@archiver.kernel.org>; Wed,  4 Nov 2020 21:24:11 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="JQZlGmJq"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731941AbgKDVYK (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 4 Nov 2020 16:24:10 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:55921 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1731641AbgKDVYJ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 4 Nov 2020 16:24:09 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1604525048;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=BgfqlHiVzPQV0alMIDRscA9ajfbeWecA6MPXXpKz1Ro=;
        b=JQZlGmJqGkoTfVRlSf5alKS0T/IJPz+YXXgL0XMTPL6yRZRlqry38B6mh620v9LJ3MPOkq
        P6N3LlWvK9lkxNGNUiQxBIaWwBLJDcS2IV42AeXFyM9ggxFkq0hVJpm214aEWDmY/I8HXC
        s0sZyBE8CKzwn2YD52Kc8Y8cR7Og8Xo=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-132-IVVCkqhGP-O1OinQi1LsGg-1; Wed, 04 Nov 2020 16:24:07 -0500
X-MC-Unique: IVVCkqhGP-O1OinQi1LsGg-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id CD645100F775;
        Wed,  4 Nov 2020 21:24:05 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.40.192.66])
        by smtp.corp.redhat.com (Postfix) with ESMTP id D577E5DA6B;
        Wed,  4 Nov 2020 21:24:03 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, borntraeger@de.ibm.com, frankja@linux.ibm.com,
        bgardon@google.com, peterx@redhat.com
Subject: [PATCH 01/11] KVM: selftests: Add x86_64/tsc_msrs_test to .gitignore
Date: Wed,  4 Nov 2020 22:23:47 +0100
Message-Id: <20201104212357.171559-2-drjones@redhat.com>
In-Reply-To: <20201104212357.171559-1-drjones@redhat.com>
References: <20201104212357.171559-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Signed-off-by: Andrew Jones <drjones@redhat.com>
---
 tools/testing/selftests/kvm/.gitignore | 1 +
 1 file changed, 1 insertion(+)

```
#### [PULL 01/33] accel/kvm: add PIO ioeventfds only in case kvm_eventfds_allowed is true
##### From: Stefan Hajnoczi <stefanha@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stefan Hajnoczi <stefanha@redhat.com>
X-Patchwork-Id: 11880967
Return-Path: <SRS0=TbV3=EK=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-8.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MIME_BASE64_TEXT,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 76ECCC388F9
	for <kvm@archiver.kernel.org>; Wed,  4 Nov 2020 15:18:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0F04A2074F
	for <kvm@archiver.kernel.org>; Wed,  4 Nov 2020 15:18:50 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="i+iOPrzo"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730508AbgKDPSs (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 4 Nov 2020 10:18:48 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:33019 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1730490AbgKDPSo (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 4 Nov 2020 10:18:44 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1604503123;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=uWbsFp7DBE9N9DNywJF9TpUh112RLQk5tV8p3cqgf6g=;
        b=i+iOPrzoqcn1c53qEt1TcfEvO7YDVWjyoJGdqF45ETgdzpYskv/FJZRRT6LxG++jeTC84S
        gfkZJ6sIrUXXXm6LxsTzVDPk6ccIp2ClGJpLscnYtgQh4+YwdwL/gPjPtySBoi68dsnRJB
        29bF1QURnb90cKtHs51y4JLMfLRO/18=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-222-VPQui5vfNhu2ohf8eAiOMQ-1; Wed, 04 Nov 2020 10:18:39 -0500
X-MC-Unique: VPQui5vfNhu2ohf8eAiOMQ-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 892431018F64;
        Wed,  4 Nov 2020 15:18:37 +0000 (UTC)
Received: from localhost (ovpn-115-145.ams2.redhat.com [10.36.115.145])
        by smtp.corp.redhat.com (Postfix) with ESMTP id DBF5673664;
        Wed,  4 Nov 2020 15:18:33 +0000 (UTC)
From: Stefan Hajnoczi <stefanha@redhat.com>
To: qemu-devel@nongnu.org, Peter Maydell <peter.maydell@linaro.org>
Cc: kvm@vger.kernel.org, "Dr. David Alan Gilbert" <dgilbert@redhat.com>,
	=?utf-8?q?Daniel_P=2E_Berrang=C3=A9?= <berrange@redhat.com>,
 Eduardo Habkost <ehabkost@redhat.com>, Markus Armbruster <armbru@redhat.com>,
 Eric Blake <eblake@redhat.com>, Fam Zheng <fam@euphon.net>,
 Stefan Hajnoczi <stefanha@redhat.com>, Keith Busch <kbusch@kernel.org>,
 Max Reitz <mreitz@redhat.com>, qemu-block@nongnu.org,
 Kevin Wolf <kwolf@redhat.com>, Coiby Xu <Coiby.Xu@gmail.com>,
 Paolo Bonzini <pbonzini@redhat.com>, Klaus Jensen <its@irrelevant.dk>,
 Elena Afanasova <eafanasova@gmail.com>
Subject: [PULL 01/33] accel/kvm: add PIO ioeventfds only in case
 kvm_eventfds_allowed is true
Date: Wed,  4 Nov 2020 15:17:56 +0000
Message-Id: <20201104151828.405824-2-stefanha@redhat.com>
In-Reply-To: <20201104151828.405824-1-stefanha@redhat.com>
References: <20201104151828.405824-1-stefanha@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Elena Afanasova <eafanasova@gmail.com>

Signed-off-by: Stefan Hajnoczi <stefanha@redhat.com>
Signed-off-by: Elena Afanasova <eafanasova@gmail.com>
Message-Id: <20201017210102.26036-1-eafanasova@gmail.com>
Signed-off-by: Stefan Hajnoczi <stefanha@redhat.com>
---
 accel/kvm/kvm-all.c | 6 ++++--
 1 file changed, 4 insertions(+), 2 deletions(-)

```
#### [PATCH] s390/kvm: remove diag318 reset code
##### From: Collin Walling <walling@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Collin Walling <walling@linux.ibm.com>
X-Patchwork-Id: 11881863
Return-Path: <SRS0=TbV3=EK=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 63095C2D0A3
	for <kvm@archiver.kernel.org>; Wed,  4 Nov 2020 18:11:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0715F2072C
	for <kvm@archiver.kernel.org>; Wed,  4 Nov 2020 18:11:22 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="AMAcMxAb"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732306AbgKDSLW (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 4 Nov 2020 13:11:22 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:5600 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1730052AbgKDSLU (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 4 Nov 2020 13:11:20 -0500
Received: from pps.filterd (m0098416.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 0A4IBIbm126539
        for <kvm@vger.kernel.org>; Wed, 4 Nov 2020 13:11:19 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=G8xuG92S8oL8aT+HGs+EKJ6b+qEWT49kDAyWabJeKmA=;
 b=AMAcMxAbWWwSZqpvYBEXSMUIMFyQBL32pFDksa1uhBr6UmCVAJ3vPKhJ/OjPxzdrQ4Zd
 lbBd9N5JJ+InZLz1WFxUuMzTWoMqbtyl8pUy38sa0p4DIYCHO/bbTAQzfL36WJZE0qUK
 4smaat17OjNL9mx18DIV+kezSYNcHR2QMVcEIuKnElZCci04f/X4Rt52RT/eV4bD7zXI
 5XfI2M2iShSlv2VRECtlk6/FDtLaIaNTrHefcOJZaf8C6hfkDmYTm5/RmhvmBNk2rk/q
 XO/i1SWEQdSuSrA8ZiSrlERKeRPIFOBfRE/gg5549FYb68yxjzGp0ysvGGMPc/Fe9rSW 8Q==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 34ksrurfgx-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT)
        for <kvm@vger.kernel.org>; Wed, 04 Nov 2020 13:11:19 -0500
Received: from m0098416.ppops.net (m0098416.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 0A4IBIik126536
        for <kvm@vger.kernel.org>; Wed, 4 Nov 2020 13:11:18 -0500
Received: from ppma04wdc.us.ibm.com (1a.90.2fa9.ip4.static.sl-reverse.com
 [169.47.144.26])
        by mx0b-001b2d01.pphosted.com with ESMTP id 34ksrurfcc-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 04 Nov 2020 13:11:18 -0500
Received: from pps.filterd (ppma04wdc.us.ibm.com [127.0.0.1])
        by ppma04wdc.us.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 0A4I7rPp021911;
        Wed, 4 Nov 2020 18:11:04 GMT
Received: from b03cxnp07029.gho.boulder.ibm.com
 (b03cxnp07029.gho.boulder.ibm.com [9.17.130.16])
        by ppma04wdc.us.ibm.com with ESMTP id 34h0ej0bag-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 04 Nov 2020 18:11:04 +0000
Received: from b03ledav006.gho.boulder.ibm.com
 (b03ledav006.gho.boulder.ibm.com [9.17.130.237])
        by b03cxnp07029.gho.boulder.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 0A4IB0KU66584996
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 4 Nov 2020 18:11:01 GMT
Received: from b03ledav006.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id E161EC6055;
        Wed,  4 Nov 2020 18:11:00 +0000 (GMT)
Received: from b03ledav006.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 2E515C6057;
        Wed,  4 Nov 2020 18:11:00 +0000 (GMT)
Received: from localhost.localdomain.com (unknown [9.85.157.224])
        by b03ledav006.gho.boulder.ibm.com (Postfix) with ESMTP;
        Wed,  4 Nov 2020 18:11:00 +0000 (GMT)
From: Collin Walling <walling@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: gor@linux.ibm.com, hca@linux.ibm.com, imbrenda@linux.ibm.com,
        cohuck@redhat.com, david@redhat.com, frankja@linux.ibm.com,
        borntraeger@de.ibm.com
Subject: [PATCH] s390/kvm: remove diag318 reset code
Date: Wed,  4 Nov 2020 13:10:32 -0500
Message-Id: <20201104181032.109800-1-walling@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.312,18.0.737
 definitions=2020-11-04_12:2020-11-04,2020-11-04 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxlogscore=948 mlxscore=0
 bulkscore=0 clxscore=1015 malwarescore=0 lowpriorityscore=0
 priorityscore=1501 impostorscore=0 suspectscore=13 adultscore=0
 spamscore=0 phishscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2011040128
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The diag318 data must be set to 0 by VM-wide reset events
triggered by diag308. As such, KVM should not handle
resetting this data via the VCPU ioctls.

Fixes: 23a60f834406 (s390/kvm: diagnose 0x318 sync and reset)
Signed-off-by: Collin Walling <walling@linux.ibm.com>
Reviewed-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 arch/s390/kvm/kvm-s390.c | 2 --
 1 file changed, 2 deletions(-)

```
#### [PULL 02/33] softmmu/memory: fix memory_region_ioeventfd_equal()
##### From: Stefan Hajnoczi <stefanha@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stefan Hajnoczi <stefanha@redhat.com>
X-Patchwork-Id: 11880961
Return-Path: <SRS0=TbV3=EK=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-8.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MIME_BASE64_TEXT,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C4FA8C2D0A3
	for <kvm@archiver.kernel.org>; Wed,  4 Nov 2020 15:18:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 59AA52074F
	for <kvm@archiver.kernel.org>; Wed,  4 Nov 2020 15:18:49 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="gPSF/Xvt"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730613AbgKDPSs (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 4 Nov 2020 10:18:48 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:57725 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1730596AbgKDPSr (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 4 Nov 2020 10:18:47 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1604503126;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=G0IJggGzUw2GPdTll1DH6CRZ2qMV3yjaBdQfe9tm6qw=;
        b=gPSF/XvtfCIQ8B4NXm/VScF1EzK22nfpK0+AR1vfk7O2jX+5tQA/LWfqpRF8h3olszBw0D
        6YembEmf+Y/nx/rf6rGgbOtfBH7RxvJtiZNlGWpbomU0HlE+cmNQfxb48X+yDWPT0wvcXO
        HKMkwx7ynro1PcjQ8POVRoHY1mELl9g=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-9-jY2_geqPPsmyTdX4PI8Uvw-1; Wed, 04 Nov 2020 10:18:44 -0500
X-MC-Unique: jY2_geqPPsmyTdX4PI8Uvw-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 925E81087D71;
        Wed,  4 Nov 2020 15:18:42 +0000 (UTC)
Received: from localhost (ovpn-115-145.ams2.redhat.com [10.36.115.145])
        by smtp.corp.redhat.com (Postfix) with ESMTP id EEFFE1007517;
        Wed,  4 Nov 2020 15:18:38 +0000 (UTC)
From: Stefan Hajnoczi <stefanha@redhat.com>
To: qemu-devel@nongnu.org, Peter Maydell <peter.maydell@linaro.org>
Cc: kvm@vger.kernel.org, "Dr. David Alan Gilbert" <dgilbert@redhat.com>,
	=?utf-8?q?Daniel_P=2E_Berrang=C3=A9?= <berrange@redhat.com>,
 Eduardo Habkost <ehabkost@redhat.com>, Markus Armbruster <armbru@redhat.com>,
 Eric Blake <eblake@redhat.com>, Fam Zheng <fam@euphon.net>,
 Stefan Hajnoczi <stefanha@redhat.com>, Keith Busch <kbusch@kernel.org>,
 Max Reitz <mreitz@redhat.com>, qemu-block@nongnu.org,
 Kevin Wolf <kwolf@redhat.com>, Coiby Xu <Coiby.Xu@gmail.com>,
 Paolo Bonzini <pbonzini@redhat.com>, Klaus Jensen <its@irrelevant.dk>,
 Elena Afanasova <eafanasova@gmail.com>
Subject: [PULL 02/33] softmmu/memory: fix memory_region_ioeventfd_equal()
Date: Wed,  4 Nov 2020 15:17:57 +0000
Message-Id: <20201104151828.405824-3-stefanha@redhat.com>
In-Reply-To: <20201104151828.405824-1-stefanha@redhat.com>
References: <20201104151828.405824-1-stefanha@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Elena Afanasova <eafanasova@gmail.com>

Eventfd can be registered with a zero length when fast_mmio is true.
Handle this case properly when dispatching through QEMU.

Signed-off-by: Elena Afanasova <eafanasova@gmail.com>
Message-id: cf71a62eb04e61932ff8ffdd02e0b2aab4f495a0.camel@gmail.com
Signed-off-by: Stefan Hajnoczi <stefanha@redhat.com>
---
 softmmu/memory.c | 11 +++++++++--
 1 file changed, 9 insertions(+), 2 deletions(-)

```
#### [PULL 03/33] MAINTAINERS: Cover "block/nvme.h" file
##### From: Stefan Hajnoczi <stefanha@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Stefan Hajnoczi <stefanha@redhat.com>
X-Patchwork-Id: 11880963
Return-Path: <SRS0=TbV3=EK=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-14.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A7ABBC388F9
	for <kvm@archiver.kernel.org>; Wed,  4 Nov 2020 15:18:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3FC802074F
	for <kvm@archiver.kernel.org>; Wed,  4 Nov 2020 15:18:58 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="VFw7TVHr"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730640AbgKDPS5 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 4 Nov 2020 10:18:57 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:41197 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1730616AbgKDPS4 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 4 Nov 2020 10:18:56 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1604503135;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=oL3ELJHJad57HtFMYj3OrTr7NYemUoxtUw7hulfPZF0=;
        b=VFw7TVHr+3ub1P0ggUbVdbb3WPVTER2/Z+/mACzs1HX0iLqwBi/Bb8D2qdRPhVhECvfGdN
        xNnucBRf8U9s5AIBBl3sY4jXRx1E0ZvW4o4fgoicpZUlPPeOlBzkgi02CBtnR9d4Kcta9k
        b72xgL6TRBzxGaPD6vJUC6dxySZlLwA=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-435-AW5D_4UkOR6iBI34-Klj4Q-1; Wed, 04 Nov 2020 10:18:48 -0500
X-MC-Unique: AW5D_4UkOR6iBI34-Klj4Q-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 2F7A31018F60;
        Wed,  4 Nov 2020 15:18:47 +0000 (UTC)
Received: from localhost (ovpn-115-145.ams2.redhat.com [10.36.115.145])
        by smtp.corp.redhat.com (Postfix) with ESMTP id CD20B610F3;
        Wed,  4 Nov 2020 15:18:43 +0000 (UTC)
From: Stefan Hajnoczi <stefanha@redhat.com>
To: qemu-devel@nongnu.org, Peter Maydell <peter.maydell@linaro.org>
Cc: kvm@vger.kernel.org, "Dr. David Alan Gilbert" <dgilbert@redhat.com>,
	=?utf-8?q?Daniel_P=2E_Berrang=C3=A9?= <berrange@redhat.com>,
 Eduardo Habkost <ehabkost@redhat.com>, Markus Armbruster <armbru@redhat.com>,
 Eric Blake <eblake@redhat.com>, Fam Zheng <fam@euphon.net>,
 Stefan Hajnoczi <stefanha@redhat.com>, Keith Busch <kbusch@kernel.org>,
 Max Reitz <mreitz@redhat.com>, qemu-block@nongnu.org,
 Kevin Wolf <kwolf@redhat.com>, Coiby Xu <Coiby.Xu@gmail.com>,
 Paolo Bonzini <pbonzini@redhat.com>, Klaus Jensen <its@irrelevant.dk>,
	=?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>,
 Klaus Jensen <k.jensen@samsung.com>
Subject: [PULL 03/33] MAINTAINERS: Cover "block/nvme.h" file
Date: Wed,  4 Nov 2020 15:17:58 +0000
Message-Id: <20201104151828.405824-4-stefanha@redhat.com>
In-Reply-To: <20201104151828.405824-1-stefanha@redhat.com>
References: <20201104151828.405824-1-stefanha@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Philippe Mathieu-Daudé <philmd@redhat.com>

The "block/nvme.h" header is shared by both the NVMe block
driver and the NVMe emulated device. Add the 'F:' entry on
both sections, so all maintainers/reviewers are notified
when it is changed.

Signed-off-by: Philippe Mathieu-Daudé <philmd@redhat.com>
Signed-off-by: Stefan Hajnoczi <stefanha@redhat.com>
Reviewed-by: Klaus Jensen <k.jensen@samsung.com>
Message-Id: <20200701140634.25994-1-philmd@redhat.com>
---
 MAINTAINERS | 2 ++
 1 file changed, 2 insertions(+)

```
