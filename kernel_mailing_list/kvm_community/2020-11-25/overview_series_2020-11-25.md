#### [PATCH v2 3/6] kvm: Remove kvm_available() function
##### From: Eduardo Habkost <ehabkost@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eduardo Habkost <ehabkost@redhat.com>
X-Patchwork-Id: 11932211
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id AE2A8C56202
	for <kvm@archiver.kernel.org>; Wed, 25 Nov 2020 20:57:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 39A7D207BB
	for <kvm@archiver.kernel.org>; Wed, 25 Nov 2020 20:57:03 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="BOi//STM"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730804AbgKYU5B (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 25 Nov 2020 15:57:01 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:60064 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1730546AbgKYU5B (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 25 Nov 2020 15:57:01 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1606337820;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=UZZQRbSxpJbfML8IkKeWrdc8btDAgjJ9BXbeofnw+dE=;
        b=BOi//STMfN4gh/2ehf8/LmpUb6c7bA06PhvheaIo3EH38e4iSydXzctJiaslgNOdrPhMQQ
        eLsD809SAOhL/cSDbE7qpIrsTyLO8rIk1RZNrOw3ZA3WLIyCuVhck3qY0tFxAF2kmkt/jM
        gjFvZSePcUHRfT7njGq7y0uYsFu0Pko=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-159-uPzmHt8iMk6LKtSdDdHVQg-1; Wed, 25 Nov 2020 15:56:56 -0500
X-MC-Unique: uPzmHt8iMk6LKtSdDdHVQg-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id C3F1A180E49C;
        Wed, 25 Nov 2020 20:56:54 +0000 (UTC)
Received: from localhost (unknown [10.10.67.22])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 85F3560854;
        Wed, 25 Nov 2020 20:56:54 +0000 (UTC)
From: Eduardo Habkost <ehabkost@redhat.com>
To: qemu-devel@nongnu.org
Cc: Gerd Hoffmann <kraxel@redhat.com>, Thomas Huth <thuth@redhat.com>,
        Markus Armbruster <armbru@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org,
        Richard Henderson <richard.henderson@linaro.org>,
        Claudio Fontana <cfontana@suse.de>,
        Roman Bolshakov <r.bolshakov@yadro.com>
Subject: [PATCH v2 3/6] kvm: Remove kvm_available() function
Date: Wed, 25 Nov 2020 15:56:33 -0500
Message-Id: <20201125205636.3305257-4-ehabkost@redhat.com>
In-Reply-To: <20201125205636.3305257-1-ehabkost@redhat.com>
References: <20201125205636.3305257-1-ehabkost@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The only caller can use accel_available("kvm") instead.

Signed-off-by: Eduardo Habkost <ehabkost@redhat.com>
---
Cc: Markus Armbruster <armbru@redhat.com>
Cc: qemu-devel@nongnu.org
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org
Cc: Richard Henderson <richard.henderson@linaro.org>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Claudio Fontana <cfontana@suse.de>
Cc: Roman Bolshakov <r.bolshakov@yadro.com>
---
 include/sysemu/arch_init.h | 1 -
 monitor/qmp-cmds.c         | 2 +-
 softmmu/arch_init.c        | 9 ---------
 3 files changed, 1 insertion(+), 11 deletions(-)

```
#### [kvm-unit-tests PATCH 01/10] lib: arm/arm64: gicv3: Add missing barrier when sending IPIs
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexandru Elisei <alexandru.elisei@arm.com>
X-Patchwork-Id: 11931417
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 3ED39C63798
	for <kvm@archiver.kernel.org>; Wed, 25 Nov 2020 15:50:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 01D46206CA
	for <kvm@archiver.kernel.org>; Wed, 25 Nov 2020 15:50:36 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731603AbgKYPuE (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 25 Nov 2020 10:50:04 -0500
Received: from foss.arm.com ([217.140.110.172]:55794 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1730318AbgKYPuE (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 25 Nov 2020 10:50:04 -0500
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id DA8FD11D4;
        Wed, 25 Nov 2020 07:50:03 -0800 (PST)
Received: from monolith.localdoman (unknown [172.31.20.19])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 1657E3F7BB;
        Wed, 25 Nov 2020 07:50:02 -0800 (PST)
From: Alexandru Elisei <alexandru.elisei@arm.com>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
        drjones@redhat.com
Cc: eric.auger@redhat.com, andre.przywara@arm.com
Subject: [kvm-unit-tests PATCH 01/10] lib: arm/arm64: gicv3: Add missing
 barrier when sending IPIs
Date: Wed, 25 Nov 2020 15:51:04 +0000
Message-Id: <20201125155113.192079-2-alexandru.elisei@arm.com>
X-Mailer: git-send-email 2.29.2
In-Reply-To: <20201125155113.192079-1-alexandru.elisei@arm.com>
References: <20201125155113.192079-1-alexandru.elisei@arm.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

One common usage for IPIs is for one CPU to write to a shared memory
location, send the IPI to kick another CPU, and the receiver to read from
the same location. Proper synchronization is needed to make sure that the
IPI receiver reads the most recent value and not stale data (for example,
the write from the sender CPU might still be in a store buffer).

For GICv3, IPIs are generated with a write to the ICC_SGI1R_EL1 register.
To make sure the memory stores are observable by other CPUs, we need a
wmb() barrier (DSB ST), which waits for stores to complete.

From the definition of DSB from ARM DDI 0487F.b, page B2-139:

"In addition, no instruction that appears in program order after the DSB
instruction can alter any state of the system or perform any part of its
functionality until the DSB completes other than:

- Being fetched from memory and decoded.
- Reading the general-purpose, SIMD and floating-point, Special-purpose, or
System registers that are directly or indirectly read without causing
side-effects."

Similar definition for armv7 (ARM DDI 0406C.d, page A3-150).

The DSB instruction is enough to prevent reordering of the GIC register
write which comes in program order after the memory access.

This also matches what the Linux GICv3 irqchip driver does (commit
21ec30c0ef52 ("irqchip/gic-v3: Use wmb() instead of smb_wmb() in
gic_raise_softirq()")).

Signed-off-by: Alexandru Elisei <alexandru.elisei@arm.com>
---
 lib/arm/gic-v3.c | 3 +++
 arm/gic.c        | 2 ++
 2 files changed, 5 insertions(+)

```
#### [PATCH] KVM: s390: track synchronous pfault events in kvm_stat
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11930651
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 738D2C5519F
	for <kvm@archiver.kernel.org>; Wed, 25 Nov 2020 09:07:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0CE8A206B5
	for <kvm@archiver.kernel.org>; Wed, 25 Nov 2020 09:07:06 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="haV1423+"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726345AbgKYJHG (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 25 Nov 2020 04:07:06 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:18900 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1725836AbgKYJHF (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 25 Nov 2020 04:07:05 -0500
Received: from pps.filterd (m0098394.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 0AP94UBq160234;
        Wed, 25 Nov 2020 04:07:04 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=2DWrLZN/AMjBuA8TzWNiQ+ZPU8UThgTKLRNsgUQGFFw=;
 b=haV1423+T9HvYt9thxikbVTtZo3SKLwMIO36wzj9w0h9iygSZ406hsUiYKlEqo+9kOKI
 ZsjPnMPJ6LAp4fDUu7lOL5jD6eCvSmzuy5Yy7fjmC/h0wgtOpFlZKowy4X5sJ0Wo42OX
 W5NXzzIyj1qDcsMQAXZvbvSExklzGiyg97Y4eZJW+tr3q8sKE0DFlrYiIgIe9F1AAtDD
 7VwuRRaGiQ7d66JiZyUheL3BFJ5WQX5CUL8NjROqogvojxNcDWtvwQLVhANjUbbIY8lN
 zV6Re1Ljj0mA0yR841aI1yCruisMp7vXTNBZQ7n8B5KsZRZNMpsV++qgK9dcAXVxJQoV OA==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 351dd3tw44-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 25 Nov 2020 04:07:04 -0500
Received: from m0098394.ppops.net (m0098394.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 0AP94s7Z162639;
        Wed, 25 Nov 2020 04:07:04 -0500
Received: from ppma03ams.nl.ibm.com (62.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.98])
        by mx0a-001b2d01.pphosted.com with ESMTP id 351dd3tw2n-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 25 Nov 2020 04:07:04 -0500
Received: from pps.filterd (ppma03ams.nl.ibm.com [127.0.0.1])
        by ppma03ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 0AP9252o006316;
        Wed, 25 Nov 2020 09:07:01 GMT
Received: from b06cxnps3074.portsmouth.uk.ibm.com
 (d06relay09.portsmouth.uk.ibm.com [9.149.109.194])
        by ppma03ams.nl.ibm.com with ESMTP id 34xth8cf67-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 25 Nov 2020 09:07:01 +0000
Received: from d06av26.portsmouth.uk.ibm.com (d06av26.portsmouth.uk.ibm.com
 [9.149.105.62])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 0AP96xhc64356734
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 25 Nov 2020 09:06:59 GMT
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 699AEAE057;
        Wed, 25 Nov 2020 09:06:59 +0000 (GMT)
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 615A3AE072;
        Wed, 25 Nov 2020 09:06:59 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av26.portsmouth.uk.ibm.com (Postfix) with ESMTPS;
        Wed, 25 Nov 2020 09:06:59 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 25651)
        id 1D963E1472; Wed, 25 Nov 2020 10:06:59 +0100 (CET)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: Janosch Frank <frankja@linux.vnet.ibm.com>
Cc: KVM <kvm@vger.kernel.org>, Cornelia Huck <cohuck@redhat.com>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        David Hildenbrand <david@redhat.com>,
        linux-s390 <linux-s390@vger.kernel.org>
Subject: [PATCH] KVM: s390: track synchronous pfault events in kvm_stat
Date: Wed, 25 Nov 2020 10:06:58 +0100
Message-Id: <20201125090658.38463-1-borntraeger@de.ibm.com>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.312,18.0.737
 definitions=2020-11-25_04:2020-11-25,2020-11-25 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxscore=0 lowpriorityscore=0
 impostorscore=0 bulkscore=0 mlxlogscore=999 priorityscore=1501
 malwarescore=0 clxscore=1015 suspectscore=0 phishscore=0 spamscore=0
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2011250051
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Right now we do count pfault (pseudo page faults aka async page faults
start and completion events). What we do not count is, if an async page
fault would have been possible by the host, but it was disabled by the
guest (e.g. interrupts off, pfault disabled, secure execution....).  Let
us count those as well in the pfault_sync counter.

Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---
 arch/s390/include/asm/kvm_host.h | 1 +
 arch/s390/kvm/kvm-s390.c         | 2 ++
 2 files changed, 3 insertions(+)

```
#### [kvm-unit-tests][PATCH v1] x86: Add a new test case for ret/iret with a nullified segment
##### From: Bin Meng <bmeng.cn@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Bin Meng <bmeng.cn@gmail.com>
X-Patchwork-Id: 11930049
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id C83E7C56202
	for <kvm@archiver.kernel.org>; Wed, 25 Nov 2020 01:22:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6D7222151B
	for <kvm@archiver.kernel.org>; Wed, 25 Nov 2020 01:22:56 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="SjYzIQ/3"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728438AbgKYBWz (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 24 Nov 2020 20:22:55 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:59850 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726788AbgKYBWz (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 24 Nov 2020 20:22:55 -0500
Received: from mail-pf1-x42e.google.com (mail-pf1-x42e.google.com
 [IPv6:2607:f8b0:4864:20::42e])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id ED363C0613D4
        for <kvm@vger.kernel.org>; Tue, 24 Nov 2020 17:22:54 -0800 (PST)
Received: by mail-pf1-x42e.google.com with SMTP id 131so764834pfb.9
        for <kvm@vger.kernel.org>; Tue, 24 Nov 2020 17:22:54 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=D1nug8CnSSYJdY2nygQV8051AV6UmGP0HDotUH63z+Q=;
        b=SjYzIQ/3Tmjt/8zU/mE8Ibpn8t4ESgOQeiD21rBi/ByaYigmYymufaNaECRp5QSJe6
         HSCUiQ0ZKyH85HiHWjqA/EimBejPUNUDonvlfq22OF1QO1cZz22dpgCj5eAKSt4648i3
         3U2OB1dBEagPB07MPbtgBZBVZkJM8/Xg4a9ohrvszRjFJJmCCj00rKPg//HbdOZ7VbvL
         SQbxU94CsSOKUBMXr3Nk7nZS3WYHs/7MdSQoJj9mg46ujVofS6me6iWrsJw1+bBqiGiF
         I24QfBUR0a0ZpbgnhacSUwTB+vD6wmVxDYvAzs4/qF+ZdnRi0+sVpSApYfxu1Ki1Hu57
         Lsiw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=D1nug8CnSSYJdY2nygQV8051AV6UmGP0HDotUH63z+Q=;
        b=MsXfxqb1oIMO6hs6voXjpGZWnsoAwar3/+1tzX+mPd0KcbJvv2hcj3g37q3bMRrmX4
         x+Q9ZaHM/LFYlGT9ClcOVf1gOBTiglEOPuU6vbnuTROH+U26SJ359Vg5h5xTtUwwqgl5
         Ly9eqa9KDiFUnoSzquelCePFywR5VCOLtHr0mwToYppZp5DrDlVjAo4tnbnrypHksNMP
         b0lCZ5d1D5xMfLk+oJSQ3n191Qkqlb6zZsV5wzK5mNV36ge3/2UN1TnrdZlNjswjKcxI
         9p9IQxcRMzp8d4fW58J9Rh3VxPuDGQz3/0WvICS57M1VoKFW1FUqZj/zLJ+MfqRJ1Dvj
         kEBQ==
X-Gm-Message-State: AOAM530qEIpOXZN1fWviPpDeCaLdIL/lteSOinSqMHRFI/r+AGZfoaHe
        WdIsJaQMMHsnc4qlZ3O07q9reJF4dTl3hw==
X-Google-Smtp-Source: 
 ABdhPJwDbcPhZdfDVVvGJD5aYRAQrwY11+FCX6nrTkk2u9BYYM55Czh4TBU5TU5/6sx88KdoAN4JHQ==
X-Received: by 2002:a17:90a:d3d3:: with SMTP id
 d19mr1206595pjw.0.1606267374570;
        Tue, 24 Nov 2020 17:22:54 -0800 (PST)
Received: from pek-vx-bsp2.wrs.com (unknown-124-94.windriver.com.
 [147.11.124.94])
        by smtp.gmail.com with ESMTPSA id
 205sm346757pge.76.2020.11.24.17.22.52
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Tue, 24 Nov 2020 17:22:54 -0800 (PST)
From: Bin Meng <bmeng.cn@gmail.com>
To: Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org
Cc: Bin Meng <bin.meng@windriver.com>
Subject: [kvm-unit-tests][PATCH v1] x86: Add a new test case for ret/iret with
 a nullified segment
Date: Wed, 25 Nov 2020 09:22:43 +0800
Message-Id: <1606267363-86660-1-git-send-email-bmeng.cn@gmail.com>
X-Mailer: git-send-email 2.7.4
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Bin Meng <bin.meng@windriver.com>

This makes up the test case for one QEMU x86 emulation issue that
was fixed by the following QEMU patch:
https://lists.nongnu.org/archive/html/qemu-devel/2020-11/msg03534.html

Note the test case only fails on an unpatched QEMU with "accel=tcg".

Signed-off-by: Bin Meng <bin.meng@windriver.com>
---

Changes in v1:
- reworded the commit message to be clearer
- removed the RFC tag as it looked good to Paolo

 x86/emulator.c | 38 ++++++++++++++++++++++++++++++++++++++
 1 file changed, 38 insertions(+)

```
#### [RFC PATCH] Fix split-irqchip vs interrupt injection window request.From: David Woodhouse <dwmw2@infradead.org>
##### From: David Woodhouse <dwmw2@infradead.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Woodhouse <dwmw2@infradead.org>
X-Patchwork-Id: 11931405
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.3 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_SANE_2 autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A0770C63798
	for <kvm@archiver.kernel.org>; Wed, 25 Nov 2020 15:10:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2705B2083E
	for <kvm@archiver.kernel.org>; Wed, 25 Nov 2020 15:10:27 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=infradead.org header.i=@infradead.org
 header.b="W5tFAUXg"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729949AbgKYPKU (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 25 Nov 2020 10:10:20 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:46094 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726295AbgKYPKT (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 25 Nov 2020 10:10:19 -0500
Received: from merlin.infradead.org (merlin.infradead.org
 [IPv6:2001:8b0:10b:1231::1])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 789A1C0613D4
        for <kvm@vger.kernel.org>; Wed, 25 Nov 2020 07:10:19 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; q=dns/txt; c=relaxed/relaxed;
        d=infradead.org; s=merlin.20170209;
 h=Mime-Version:Content-Type:References:
        In-Reply-To:Date:Cc:To:From:Subject:Message-ID:Sender:Reply-To:
        Content-Transfer-Encoding:Content-ID:Content-Description;
        bh=Fq0H+7D6WCHp5sD/cqPJk3IRLiLIxxWtxQQNsf72xQ0=;
 b=W5tFAUXg1mE/WS0Ze2VyB2yN+b
        yp8GDGY6Fxl4HSJ+1IaKbR4Rdr/HSV77I1QP3cAFXQ4d4gyKKud9pTOwYpNjB1hoe/RG04gLg96K8
        j/uCNIq3QHhHW4bhhAhZanIk9Z6ATw89yBqnAXusvEwxtrd9vd6pedTM9CmhtkIQFCw1PRdbu1QpP
        0sDeE6QVPiDGJ+vK+U0jrI1L4o/zl3Z5qH62XloN/gpM9UCl8dQEaU4NoCgRve3365DHSJbU7NNN1
        QYIbGlh25nnHzUmB590FDmqzPhBlnTUTMr0G0atJmMDg4SZDcIMg9TAgKTq/NTpOv4j5o+3/QXVdj
        GfCDOusA==;
Received: from 54-240-197-238.amazon.com ([54.240.197.238]
 helo=u3832b3a9db3152.ant.amazon.com)
        by merlin.infradead.org with esmtpsa (Exim 4.92.3 #3 (Red Hat Linux))
        id 1khwQy-0007Yd-Fm; Wed, 25 Nov 2020 15:10:16 +0000
Message-ID: <017de9019136b5d2ec34132b96b9f0273c21d6f1.camel@infradead.org>
Subject: [RFC PATCH] Fix split-irqchip vs interrupt injection window request.
From: David Woodhouse <dwmw2@infradead.org>
To: kvm <kvm@vger.kernel.org>
Cc: "Sironi, Filippo" <sironi@amazon.de>,
        "Raslan, KarimAllah" <karahmed@amazon.de>,
        Matt Gingell <gingell@google.com>,
        Steve Rutherford <srutherford@google.com>, liran@amazon.com
Date: Wed, 25 Nov 2020 15:10:13 +0000
In-Reply-To: <62918f65ec78f8990278a6a0db0567968fa23e49.camel@infradead.org>
References: <62918f65ec78f8990278a6a0db0567968fa23e49.camel@infradead.org>
X-Mailer: Evolution 3.28.5-0ubuntu0.18.04.2 
Mime-Version: 1.0
X-SRS-Rewrite: SMTP reverse-path rewritten from <dwmw2@infradead.org> by
 merlin.infradead.org. See http://www.infradead.org/rpr.html
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

On Thu, 2020-11-12 at 13:03 +0000, David Woodhouse wrote:
> I'm using nested VMX for testing, while I add split-irqchip support to
> my VMM. I see the vCPU lock up when attempting to deliver an interrupt.

Turns out I don't need nesting or my own VMM to reproduce this; all I
need to do is boot a guest in qemu with split-irqchip and 'noapic' on
the guest command line. It locks up before getting to a login prompt,
every time.

qemu-system-x86_64 -serial mon:stdio -machine q35,accel=kvm,kernel-irqchip=split -m 2G -display none -drive file=foo.qcow2,if=virtio

Commit 782d422bc ("KVM: x86: split kvm_vcpu_ready_for_interrupt_injection
out of dm_request_for_irq_injection") made dm_request_for_irq_injection()
return true even when kvm_cpu_has_interrupt() is true.

So we enable the vmexit on interrupt window because userspace asked for
it, but then kvm_vcpu_ready_for_interrupt_injection() returns false,
causing us *not* to exit all the way to userspace but just to loop in
vcpu_run() instead.

But we *didn't* have an injectable interrupt from the kernel, so we
just go straight back into the guest, vmexit again, loop again, ad
infinitum.

```
#### [RFC PATCH] vfio/pci: Allow force needs_pm_restore as specified by device:vendor
##### From: Colin Xu <colin.xu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Colin Xu <colin.xu@intel.com>
X-Patchwork-Id: 11930083
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 86706C63798
	for <kvm@archiver.kernel.org>; Wed, 25 Nov 2020 02:18:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4D32821D1A
	for <kvm@archiver.kernel.org>; Wed, 25 Nov 2020 02:18:50 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726188AbgKYCS2 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 24 Nov 2020 21:18:28 -0500
Received: from mga01.intel.com ([192.55.52.88]:3710 "EHLO mga01.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725616AbgKYCS2 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 24 Nov 2020 21:18:28 -0500
IronPort-SDR: 
 mE2EYBsCJ8aWVvveXOTun/vK0rYq/ifdV/q4BxW5GGP62gFWwFREKDR10QcesjQyoVnezk6kUZ
 JWCS4Ae2l65g==
X-IronPort-AV: E=McAfee;i="6000,8403,9815"; a="190186325"
X-IronPort-AV: E=Sophos;i="5.78,367,1599548400";
   d="scan'208";a="190186325"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga005.fm.intel.com ([10.253.24.32])
  by fmsmga101.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 24 Nov 2020 18:18:27 -0800
IronPort-SDR: 
 PxDT7wIK6vg4ude8q+gVTZm2n/bqdKFL/4Kk0K22bSnazJY6R5cpC6pUfv2wGkpL2iXAVQBULd
 sgzRD+N6EvGQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.78,367,1599548400";
   d="scan'208";a="536696759"
Received: from unknown (HELO coxu-arch-shz.sh.intel.com) ([10.239.160.22])
  by fmsmga005.fm.intel.com with ESMTP; 24 Nov 2020 18:18:26 -0800
From: Colin Xu <colin.xu@intel.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: colin.xu@intel.com, swee.yee.fonn@intel.com
Subject: [RFC PATCH] vfio/pci: Allow force needs_pm_restore as specified by
 device:vendor
Date: Wed, 25 Nov 2020 10:18:24 +0800
Message-Id: <20201125021824.27411-1-colin.xu@intel.com>
X-Mailer: git-send-email 2.29.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Force specific device listed in params pm_restore_ids to follow
device state save/restore as needs_pm_restore.
Some device has NoSoftRst so will skip current state save/restore enabled
by needs_pm_restore. However once the device experienced power state
D3<->D0 transition, either by idle_d3 or the guest driver changes PM_CTL,
the guest driver won't get correct devie state although the configure
space doesn't change.

Cc: Swee Yee Fonn <swee.yee.fonn@intel.com>
Signed-off-by: Colin Xu <colin.xu@intel.com>
---
 drivers/vfio/pci/vfio_pci.c | 66 ++++++++++++++++++++++++++++++++++++-
 1 file changed, 65 insertions(+), 1 deletion(-)

```
#### [PATCH v10 01/81] KVM: UAPI: add error codes used by the VM introspection code
##### From: =?utf-8?q?Adalbert_Laz=C4=83r?= <alazar@bitdefender.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Adalbert_Laz=C4=83r?=
 <alazar@bitdefender.com>
X-Patchwork-Id: 11930925
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id BD68AC5519F
	for <kvm@archiver.kernel.org>; Wed, 25 Nov 2020 09:43:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 70BFE2083E
	for <kvm@archiver.kernel.org>; Wed, 25 Nov 2020 09:43:04 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727794AbgKYJl4 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 25 Nov 2020 04:41:56 -0500
Received: from mx01.bbu.dsd.mx.bitdefender.com ([91.199.104.161]:57142 "EHLO
        mx01.bbu.dsd.mx.bitdefender.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727403AbgKYJlz (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 25 Nov 2020 04:41:55 -0500
Received: from smtp.bitdefender.com (smtp01.buh.bitdefender.com [10.17.80.75])
        by mx01.bbu.dsd.mx.bitdefender.com (Postfix) with ESMTPS id
 5F8FC30462CD;
        Wed, 25 Nov 2020 11:35:43 +0200 (EET)
Received: from localhost.localdomain (unknown [91.199.104.27])
        by smtp.bitdefender.com (Postfix) with ESMTPSA id 43FF93072785;
        Wed, 25 Nov 2020 11:35:43 +0200 (EET)
From: =?utf-8?q?Adalbert_Laz=C4=83r?= <alazar@bitdefender.com>
To: kvm@vger.kernel.org
Cc: virtualization@lists.linux-foundation.org,
 Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?q?Adalbert_Laz=C4=83r?= <alazar@bitdefender.com>
Subject: [PATCH v10 01/81] KVM: UAPI: add error codes used by the VM
 introspection code
Date: Wed, 25 Nov 2020 11:34:40 +0200
Message-Id: <20201125093600.2766-2-alazar@bitdefender.com>
In-Reply-To: <20201125093600.2766-1-alazar@bitdefender.com>
References: <20201125093600.2766-1-alazar@bitdefender.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

These new error codes help the introspection tool to identify the cause
of the introspection command failure and to recover from some error
cases or to give more information to the user.

Signed-off-by: Adalbert Lazăr <alazar@bitdefender.com>
---
 include/uapi/linux/kvm_para.h | 4 ++++
 1 file changed, 4 insertions(+)

```
