#### [PATCH 1/2] s390/uv: handle destroy page legacy interface
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11914673
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 90E97C63697
	for <kvm@archiver.kernel.org>; Wed, 18 Nov 2020 09:39:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2D2E4221F1
	for <kvm@archiver.kernel.org>; Wed, 18 Nov 2020 09:39:52 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="rMTgizFL"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726754AbgKRJjv (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 18 Nov 2020 04:39:51 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:56476 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1725964AbgKRJju (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 18 Nov 2020 04:39:50 -0500
Received: from pps.filterd (m0098420.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 0AI9Vm9w070697;
        Wed, 18 Nov 2020 04:39:49 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=xktAxGBOdEZvx7tyc+6+MDC+lnv6CTwONXvIwAGOYhk=;
 b=rMTgizFLN1dl+HA3Slzw3Z78zryRPdM1lcj4KbfAlc0EryVkz9bH+bu6pJvh3oJFyn2+
 jncmIUn0BfgvZLzH0dkdVnTX6TFHNvSC3+2KgWWe8BHXGZrB7W7spIrXMKmGo9INtkuN
 fVB+n2BQRdRiCk2TwGzZM8o84uC6dD1PoS9KiEyFfsaCo3Xos7Ga8JbkodTfREbDqpJ8
 9eEn/7kQfb34f2/FtzUGxg4y8WmzpSBVpYr5QIOdcniojXh3Gga7Jn1IcY+wyz3pYPx8
 E+c5k7rwA95JOPvJTe3yzJfEV16aF4+g/qwbRBLjF9i1BB6E/whHV0woa49Y4HC0/gpJ Uw==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 34w12g07uw-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 18 Nov 2020 04:39:49 -0500
Received: from m0098420.ppops.net (m0098420.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 0AI9VqiA070976;
        Wed, 18 Nov 2020 04:39:49 -0500
Received: from ppma06ams.nl.ibm.com (66.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.102])
        by mx0b-001b2d01.pphosted.com with ESMTP id 34w12g07ts-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 18 Nov 2020 04:39:49 -0500
Received: from pps.filterd (ppma06ams.nl.ibm.com [127.0.0.1])
        by ppma06ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 0AI9bFIB020355;
        Wed, 18 Nov 2020 09:39:46 GMT
Received: from b06cxnps4076.portsmouth.uk.ibm.com
 (d06relay13.portsmouth.uk.ibm.com [9.149.109.198])
        by ppma06ams.nl.ibm.com with ESMTP id 34t6gh40v3-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 18 Nov 2020 09:39:46 +0000
Received: from d06av21.portsmouth.uk.ibm.com (d06av21.portsmouth.uk.ibm.com
 [9.149.105.232])
        by b06cxnps4076.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 0AI9diDZ6488692
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 18 Nov 2020 09:39:44 GMT
Received: from d06av21.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id E164452050;
        Wed, 18 Nov 2020 09:39:43 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av21.portsmouth.uk.ibm.com (Postfix) with ESMTPS id CE67C52051;
        Wed, 18 Nov 2020 09:39:43 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 25651)
        id 91597E23AF; Wed, 18 Nov 2020 10:39:43 +0100 (CET)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: Janosch Frank <frankja@linux.vnet.ibm.com>
Cc: KVM <kvm@vger.kernel.org>, Cornelia Huck <cohuck@redhat.com>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        David Hildenbrand <david@redhat.com>,
        linux-s390 <linux-s390@vger.kernel.org>,
        Heiko Carstens <hca@linux.ibm.com>,
        Vasily Gorbik <gor@linux.ibm.com>,
        Janosch Frank <frankja@linux.ibm.com>
Subject: [PATCH 1/2] s390/uv: handle destroy page legacy interface
Date: Wed, 18 Nov 2020 10:39:41 +0100
Message-Id: <20201118093942.457191-2-borntraeger@de.ibm.com>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20201118093942.457191-1-borntraeger@de.ibm.com>
References: <20201118093942.457191-1-borntraeger@de.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.312,18.0.737
 definitions=2020-11-18_04:2020-11-17,2020-11-18 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 malwarescore=0 spamscore=0
 adultscore=0 clxscore=1015 bulkscore=0 impostorscore=0 suspectscore=0
 lowpriorityscore=0 mlxlogscore=984 priorityscore=1501 mlxscore=0
 phishscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2011180062
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Older firmware can return rc=0x107 rrc=0xd for destroy page if the
page is already non-secure. This should be handled like a success
as already done by newer firmware.

Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
Fixes: 1a80b54d1ce1 ("s390/uv: add destroy page call")
Reviewed-by: Janosch Frank <frankja@linux.ibm.com>
---
 arch/s390/kernel/uv.c | 9 ++++++++-
 1 file changed, 8 insertions(+), 1 deletion(-)

```
#### [GIT PULL 1/2] s390/uv: handle destroy page legacy interface
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11915453
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id AF238C63777
	for <kvm@archiver.kernel.org>; Wed, 18 Nov 2020 17:02:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4844D24883
	for <kvm@archiver.kernel.org>; Wed, 18 Nov 2020 17:02:54 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="rUAjaBn5"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727196AbgKRRCk (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 18 Nov 2020 12:02:40 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:20946 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727117AbgKRRCj (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 18 Nov 2020 12:02:39 -0500
Received: from pps.filterd (m0098410.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 0AIGg25F096937;
        Wed, 18 Nov 2020 12:02:39 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=F4R1xVKOfLPBffxpB6TbUmxJsHZtMlfMkdttB86CPt8=;
 b=rUAjaBn5BSEbfoFHJZx/6JLUwec1s86vVIaGkbr6tSR9zbQXKVquqZELdHIXkHSBF/Nt
 AS4GfO4rKG1/Hc8lVN+anrHPsJbyZ/Rg8YQT74kdjyjNMJvagCqVR6j7kycvXKSs2y+w
 fe/kgH7cPkgSzz7aE74bTBUBsp6Ve8+O83r76HsapZsmGyQHjehb39wjicthMTQ2J4mn
 y60PW86mS8KqcdNUC9O+4nJA+oQ2HlubjhDo2OdjcE2qE6xB5POayjHxejCV0fp79KrF
 7CuajSN5IocjqEueVv9B4TUiNmRqzSsc01pcR8wGC5l5lzaaRYb/T9gIGyPGc2vwYsWh Uw==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 34w31vk72f-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 18 Nov 2020 12:02:38 -0500
Received: from m0098410.ppops.net (m0098410.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 0AIGgUct099667;
        Wed, 18 Nov 2020 12:02:38 -0500
Received: from ppma02fra.de.ibm.com (47.49.7a9f.ip4.static.sl-reverse.com
 [159.122.73.71])
        by mx0a-001b2d01.pphosted.com with ESMTP id 34w31vk715-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 18 Nov 2020 12:02:38 -0500
Received: from pps.filterd (ppma02fra.de.ibm.com [127.0.0.1])
        by ppma02fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 0AIH1OnP003357;
        Wed, 18 Nov 2020 17:02:36 GMT
Received: from b06cxnps3074.portsmouth.uk.ibm.com
 (d06relay09.portsmouth.uk.ibm.com [9.149.109.194])
        by ppma02fra.de.ibm.com with ESMTP id 34t6v8as98-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 18 Nov 2020 17:02:35 +0000
Received: from d06av22.portsmouth.uk.ibm.com (d06av22.portsmouth.uk.ibm.com
 [9.149.105.58])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 0AIH1HHN6226458
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 18 Nov 2020 17:01:18 GMT
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id DDEDE4C058;
        Wed, 18 Nov 2020 17:01:17 +0000 (GMT)
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id CB84E4C04E;
        Wed, 18 Nov 2020 17:01:17 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av22.portsmouth.uk.ibm.com (Postfix) with ESMTPS;
        Wed, 18 Nov 2020 17:01:17 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 25651)
        id 8F91DE01E9; Wed, 18 Nov 2020 18:01:17 +0100 (CET)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: KVM <kvm@vger.kernel.org>, Janosch Frank <frankja@linux.ibm.com>,
        David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        linux-s390 <linux-s390@vger.kernel.org>,
        Christian Borntraeger <borntraeger@de.ibm.com>
Subject: [GIT PULL 1/2] s390/uv: handle destroy page legacy interface
Date: Wed, 18 Nov 2020 18:01:15 +0100
Message-Id: <20201118170116.8239-2-borntraeger@de.ibm.com>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20201118170116.8239-1-borntraeger@de.ibm.com>
References: <20201118170116.8239-1-borntraeger@de.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.312,18.0.737
 definitions=2020-11-18_04:2020-11-17,2020-11-18 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 phishscore=0 mlxlogscore=999
 bulkscore=0 adultscore=0 mlxscore=0 impostorscore=0 lowpriorityscore=0
 spamscore=0 priorityscore=1501 clxscore=1015 malwarescore=0 suspectscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2011180115
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Older firmware can return rc=0x107 rrc=0xd for destroy page if the
page is already non-secure. This should be handled like a success
as already done by newer firmware.

Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
Fixes: 1a80b54d1ce1 ("s390/uv: add destroy page call")
Reviewed-by: David Hildenbrand <david@redhat.com>
Acked-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: Janosch Frank <frankja@linux.ibm.com>
---
 arch/s390/kernel/uv.c | 9 ++++++++-
 1 file changed, 8 insertions(+), 1 deletion(-)

```
#### [RESEND kvm-unit-tests PATCH] x86: remove extra includes
##### From: Pankaj Gupta <pankaj.gupta.linux@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pankaj Gupta <pankaj.gupta.linux@gmail.com>
X-Patchwork-Id: 11915351
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id D4AD9C5519F
	for <kvm@archiver.kernel.org>; Wed, 18 Nov 2020 15:31:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 530042476E
	for <kvm@archiver.kernel.org>; Wed, 18 Nov 2020 15:31:56 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="NlgRJL/C"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727423AbgKRPbz (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 18 Nov 2020 10:31:55 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:48674 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726502AbgKRPby (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 18 Nov 2020 10:31:54 -0500
Received: from mail-ed1-x542.google.com (mail-ed1-x542.google.com
 [IPv6:2a00:1450:4864:20::542])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id A2690C0613D6
        for <kvm@vger.kernel.org>; Wed, 18 Nov 2020 07:31:54 -0800 (PST)
Received: by mail-ed1-x542.google.com with SMTP id ay21so2451761edb.2
        for <kvm@vger.kernel.org>; Wed, 18 Nov 2020 07:31:54 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=FwP65fTRBjJQOZTuLRa465u12tCsPFehRRoZ9l9M4Ak=;
        b=NlgRJL/Cae3P8zfPrpG7Ys7H2L1c/bhLjHaY1tJqTVN/HIcCl137mJ+M7tjQii7HSz
         7/13IqpUAed32nJyOyu8h6fm6e1cLJBaAAwr3klfcwyh2PK4acgPm4HAQWbR1q04IJrY
         XHUPbx033YZzTDMBGvQD2bMVv/B0ckiTJDFWjK21/rcc0Flp3uWD5+1UWR8rQo5JQzDM
         aKWFjTO88c3aIVkHqGQgSdigM9WqRWBl35taQkNEqj4gxaXRPAJA/+uNrwaJkA/MozNx
         szHOKXFVo0sUYe++Q62xVTGCkMfqn97t7yyAg6hW+jNHexWjL2uPVngJEOjjv9a3yzq1
         AyHg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=FwP65fTRBjJQOZTuLRa465u12tCsPFehRRoZ9l9M4Ak=;
        b=lsnDPXyExUslAMcxp1Hx+OWBhKQyB1QPNQrH3kZ2i1hoPHpRAkAyhbAj0MxNjwJm9y
         vdX//Cye82fF6I7zJU+27zklDhJw9qhv8GafPU3Ij3Htigwm+8lF145n997bRQWk+GJi
         H6YJYwYWGDr2H+VyCl9AekmfRNDjezdfD4MnfBsQ87YQPZgDwbqbtfO+y7dpfJwXONhU
         KP7fECivhHM0iBGF3XAfnZRoLKfzM90z/NEBjEgKhDKvsSGM7sxu20nZJVZ3vM2Ov//p
         o6pO3aodvd6hJp5j/uR/fkH+Xng+nEGBpHKQAnFQFXfXaQ3H2JHUMFWEw9rtbiAqSqt5
         wDuA==
X-Gm-Message-State: AOAM532HRN9H0707x7D4PEMHq5Gj2AhqPqSla6H5br3dWELYm3Ukb8k/
        hTD+UiSSdsM8CqXolQjuU40=
X-Google-Smtp-Source: 
 ABdhPJw6ucG29s9FXIqAGWTrU8gli8mtYZvzOjyI+qbTm0g2sBMjhDFe/vm8hQe+/EpnaWRe7LFt7w==
X-Received: by 2002:aa7:cdd9:: with SMTP id
 h25mr26649646edw.294.1605713513399;
        Wed, 18 Nov 2020 07:31:53 -0800 (PST)
Received: from lb01399.pb.local
 (p200300ca573cea22894fd6f5c6d10f88.dip0.t-ipconnect.de.
 [2003:ca:573c:ea22:894f:d6f5:c6d1:f88])
        by smtp.gmail.com with ESMTPSA id
 k12sm13150456ejz.48.2020.11.18.07.31.52
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 18 Nov 2020 07:31:52 -0800 (PST)
From: Pankaj Gupta <pankaj.gupta.linux@gmail.com>
To: pbonzini@redhat.com
Cc: kvm@vger.kernel.org, pankaj.gupta.linux@gmail.com,
        Pankaj Gupta <pankaj.gupta@cloud.ionos.com>
Subject: [RESEND kvm-unit-tests PATCH] x86: remove extra includes
Date: Wed, 18 Nov 2020 16:31:47 +0100
Message-Id: <20201118153147.8069-1-pankaj.gupta.linux@gmail.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Pankaj Gupta <pankaj.gupta@cloud.ionos.com>

Remove extra includes.

Signed-off-by: Pankaj Gupta <pankaj.gupta@cloud.ionos.com>
---
 x86/vmexit.c | 2 --
 1 file changed, 2 deletions(-)

```
#### [PATCH v13 01/15] iommu: Introduce attach/detach_pasid_table API
##### From: Eric Auger <eric.auger@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Auger Eric <eric.auger@redhat.com>
X-Patchwork-Id: 11914837
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D1BB7C63777
	for <kvm@archiver.kernel.org>; Wed, 18 Nov 2020 11:22:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8C58D2463B
	for <kvm@archiver.kernel.org>; Wed, 18 Nov 2020 11:22:38 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="XBLdsWA3"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727233AbgKRLW0 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 18 Nov 2020 06:22:26 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:57880 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726297AbgKRLWZ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 18 Nov 2020 06:22:25 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1605698543;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=er5AfFvbl7FNodZGRRvh/xhkiPYuVO/KHG2tiFhZjXQ=;
        b=XBLdsWA3k+xE/m6QAIZcCIPZQh8x4W3tUE7UQrOxiIJ/WR38LfTjeUn4M8VyTTVLce2jnW
        AR9DanLaWeuq2rkzgVrWJpIzndO+eUo1dXf4MEFOBuL4SO0DlevV39fFhecpwEwRX73mtO
        GZ2rZ+3e49wtYe33vRxQSMmlFWBJEjs=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-355-L7dGrYXMNC6v5R5_IPD9Qw-1; Wed, 18 Nov 2020 06:22:19 -0500
X-MC-Unique: L7dGrYXMNC6v5R5_IPD9Qw-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 9318E1891E83;
        Wed, 18 Nov 2020 11:22:16 +0000 (UTC)
Received: from laptop.redhat.com (ovpn-115-104.ams2.redhat.com
 [10.36.115.104])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 051C451512;
        Wed, 18 Nov 2020 11:22:07 +0000 (UTC)
From: Eric Auger <eric.auger@redhat.com>
To: eric.auger.pro@gmail.com, eric.auger@redhat.com,
        iommu@lists.linux-foundation.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu, will@kernel.org,
        joro@8bytes.org, maz@kernel.org, robin.murphy@arm.com,
        alex.williamson@redhat.com
Cc: jean-philippe@linaro.org, zhangfei.gao@linaro.org,
        zhangfei.gao@gmail.com, vivek.gautam@arm.com,
        shameerali.kolothum.thodi@huawei.com,
        jacob.jun.pan@linux.intel.com, yi.l.liu@intel.com, tn@semihalf.com,
        nicoleotsuka@gmail.com, yuzenghui@huawei.com
Subject: [PATCH v13 01/15] iommu: Introduce attach/detach_pasid_table API
Date: Wed, 18 Nov 2020 12:21:37 +0100
Message-Id: <20201118112151.25412-2-eric.auger@redhat.com>
In-Reply-To: <20201118112151.25412-1-eric.auger@redhat.com>
References: <20201118112151.25412-1-eric.auger@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In virtualization use case, when a guest is assigned
a PCI host device, protected by a virtual IOMMU on the guest,
the physical IOMMU must be programmed to be consistent with
the guest mappings. If the physical IOMMU supports two
translation stages it makes sense to program guest mappings
onto the first stage/level (ARM/Intel terminology) while the host
owns the stage/level 2.

In that case, it is mandated to trap on guest configuration
settings and pass those to the physical iommu driver.

This patch adds a new API to the iommu subsystem that allows
to set/unset the pasid table information.

A generic iommu_pasid_table_config struct is introduced in
a new iommu.h uapi header. This is going to be used by the VFIO
user API.

Signed-off-by: Jean-Philippe Brucker <jean-philippe.brucker@arm.com>
Signed-off-by: Liu, Yi L <yi.l.liu@linux.intel.com>
Signed-off-by: Ashok Raj <ashok.raj@intel.com>
Signed-off-by: Jacob Pan <jacob.jun.pan@linux.intel.com>
Signed-off-by: Eric Auger <eric.auger@redhat.com>
---

v12 -> v13:
- Fix config check

v11 -> v12:
- add argsz, name the union
---
 drivers/iommu/iommu.c      | 68 ++++++++++++++++++++++++++++++++++++++
 include/linux/iommu.h      | 21 ++++++++++++
 include/uapi/linux/iommu.h | 54 ++++++++++++++++++++++++++++++
 3 files changed, 143 insertions(+)

```
#### [PATCH] x86: remove extra includes
##### From: Pankaj Gupta <pankaj.gupta.linux@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pankaj Gupta <pankaj.gupta.linux@gmail.com>
X-Patchwork-Id: 11915327
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id CDE22C6369E
	for <kvm@archiver.kernel.org>; Wed, 18 Nov 2020 15:24:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 70D5624766
	for <kvm@archiver.kernel.org>; Wed, 18 Nov 2020 15:24:56 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="OEi1SA2l"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727019AbgKRPYz (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 18 Nov 2020 10:24:55 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:47570 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725446AbgKRPYz (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 18 Nov 2020 10:24:55 -0500
Received: from mail-ed1-x542.google.com (mail-ed1-x542.google.com
 [IPv6:2a00:1450:4864:20::542])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 05DBDC0613D4
        for <kvm@vger.kernel.org>; Wed, 18 Nov 2020 07:24:55 -0800 (PST)
Received: by mail-ed1-x542.google.com with SMTP id ay21so2426563edb.2
        for <kvm@vger.kernel.org>; Wed, 18 Nov 2020 07:24:54 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=FwP65fTRBjJQOZTuLRa465u12tCsPFehRRoZ9l9M4Ak=;
        b=OEi1SA2lJD02HfGZ2ZOAcIlcEsEk+vn6Xl4rPm6qVoAEKNoFe/590nTKkN6CYxoQkT
         4KA/Leefb5ifFrFJujfvTIR3BHZKTEojrX6RjUhTIuKqARH8AHmHYsScHT5FqUtrxwbz
         rcwIi2hZBqpH3CsyoCeTd3yWkfj57/1iojTSRIbC9iVU6w4l00IDrOS5Cl9/6uq5UNkk
         Wep8htTKSk6DFZEjouS6Bg9VEvqSqcrd9+884MZWKkemMu2bGxfQ71pX86R6AKgJiUX8
         t0VWD4GZFiYVhZ2zrfaxNK/ufZO1Bl6P1NSrDML3oLZUJS2JyLgwwdrN2+PJYWj4d8PG
         /uJw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=FwP65fTRBjJQOZTuLRa465u12tCsPFehRRoZ9l9M4Ak=;
        b=WEvxWfR6tH4m2zJzVzsQxepbeFGeJCxhpl2Nsm0SMJ3lKS2SKJCUP46FMIswIW2S4G
         hZsGucNTHY6ZN3Mnr43Z4IwkwssJ58UaDuh2hDEci3w+qvJqmuhaDxSDfjii9kVFnv+g
         xfcrVDYs5E2sz01zFE1iqR2c/d0cBV68iTejcTFNJiOG3LuehuJ2q60QT17/G3stsPaD
         PHdNjiF9eosO+sQfvyUuiuyvZNG7cEZkrmIRJ/t3IjxtMx0LodOp0EiVFrbFsKpmH1Tu
         71zfFObfbcbgzsd8NFKjiuL7v51rEWV41IQUwYXEj3uRYwfzLOxP0bpAsHQ60uNGJNWA
         D/4Q==
X-Gm-Message-State: AOAM533bZVB7X4I5HakolvWxpRxO5z0G6oeLG69ZUuGaJVzq1sXh/YOk
        H3jXjH6ITtu6f3mE7ir9InA=
X-Google-Smtp-Source: 
 ABdhPJyW7tBCD+0GY8Fjihq8azddmx2u+UMZVXLscO0Zd6/pw3sTE8CszjTP3lut2/wjGRvOYLFKcQ==
X-Received: by 2002:aa7:d502:: with SMTP id y2mr26671308edq.120.1605713093726;
        Wed, 18 Nov 2020 07:24:53 -0800 (PST)
Received: from lb01399.pb.local
 (p200300ca573cea22894fd6f5c6d10f88.dip0.t-ipconnect.de.
 [2003:ca:573c:ea22:894f:d6f5:c6d1:f88])
        by smtp.gmail.com with ESMTPSA id
 b15sm597083ejz.114.2020.11.18.07.24.52
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 18 Nov 2020 07:24:53 -0800 (PST)
From: Pankaj Gupta <pankaj.gupta.linux@gmail.com>
To: pbonzini@redhat.com
Cc: kvm@vger.kernel.org, pankaj.gupta.linux@gmail.com,
        Pankaj Gupta <pankaj.gupta@cloud.ionos.com>
Subject: [PATCH] x86: remove extra includes
Date: Wed, 18 Nov 2020 16:24:47 +0100
Message-Id: <20201118152447.7638-1-pankaj.gupta.linux@gmail.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Pankaj Gupta <pankaj.gupta@cloud.ionos.com>

Remove extra includes.

Signed-off-by: Pankaj Gupta <pankaj.gupta@cloud.ionos.com>
---
 x86/vmexit.c | 2 --
 1 file changed, 2 deletions(-)

```
#### [kvm-unit-tests PATCH v2 1/1] x86: check that clflushopt of an MMIO address succeeds
##### From: David Edmondson <david.edmondson@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Edmondson <david.edmondson@oracle.com>
X-Patchwork-Id: 11914993
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	UNPARSEABLE_RELAY,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 0EFE8C5519F
	for <kvm@archiver.kernel.org>; Wed, 18 Nov 2020 12:11:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9D9C0221F1
	for <kvm@archiver.kernel.org>; Wed, 18 Nov 2020 12:11:56 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="MJs4iVVP"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727050AbgKRMLf (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 18 Nov 2020 07:11:35 -0500
Received: from aserp2130.oracle.com ([141.146.126.79]:57304 "EHLO
        aserp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726189AbgKRMLf (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 18 Nov 2020 07:11:35 -0500
Received: from pps.filterd (aserp2130.oracle.com [127.0.0.1])
        by aserp2130.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 0AICALWR010130
        for <kvm@vger.kernel.org>; Wed, 18 Nov 2020 12:11:34 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=corp-2020-01-29;
 bh=ckQ0zCtD692qCVbG4gPGcSRkah2dYeTD2+liRIXf0KE=;
 b=MJs4iVVPRK/G4gAiOykwFru7Mv7ucV/aKuY77UbRzfZ/SGLKigAd1nM0QjeKIoTuWyUM
 IgRrIQ6jogLTQlEpPaI3v0/RpbHghRrrLIxo8U1sBa5t40hpRkRWTvZDPloDGYR/FFYW
 1zD7z9v8x13LJkLSvyR5L6o+x9e4MWZ/xsz7Y0QHOPg+kaMI19QtPwR4Bff8KvsmB9vu
 mjTA6Rb+FZz0zadU1oVMMpO3jSpZqTcZtPyzp6EVMjgXYS7ZDHy39EgxNMBtvtsWUVqO
 +uPSZiFEwMO5hSTwrfa0IvpOqMp6NMmM4XYFm+KZ+9m86DFuDMXElGgZc+Wq2cVQPZeV 6Q==
Received: from userp3030.oracle.com (userp3030.oracle.com [156.151.31.80])
        by aserp2130.oracle.com with ESMTP id 34t4rayuup-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=FAIL)
        for <kvm@vger.kernel.org>; Wed, 18 Nov 2020 12:11:34 +0000
Received: from pps.filterd (userp3030.oracle.com [127.0.0.1])
        by userp3030.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 0AICAZih115322
        for <kvm@vger.kernel.org>; Wed, 18 Nov 2020 12:11:33 GMT
Received: from aserv0121.oracle.com (aserv0121.oracle.com [141.146.126.235])
        by userp3030.oracle.com with ESMTP id 34ts5xeg62-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK)
        for <kvm@vger.kernel.org>; Wed, 18 Nov 2020 12:11:33 +0000
Received: from abhmp0012.oracle.com (abhmp0012.oracle.com [141.146.116.18])
        by aserv0121.oracle.com (8.14.4/8.13.8) with ESMTP id 0AICBWuT027928
        for <kvm@vger.kernel.org>; Wed, 18 Nov 2020 12:11:32 GMT
Received: from disaster-area.hh.sledj.net (/81.187.26.238)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Wed, 18 Nov 2020 04:11:32 -0800
Received: from localhost (disaster-area.hh.sledj.net [local])
        by disaster-area.hh.sledj.net (OpenSMTPD) with ESMTPA id fa0b1899;
        Wed, 18 Nov 2020 12:11:29 +0000 (UTC)
From: David Edmondson <david.edmondson@oracle.com>
To: kvm@vger.kernel.org
Cc: David Edmondson <david.edmondson@oracle.com>,
        Joao Martins <joao.m.martins@oracle.com>
Subject: [kvm-unit-tests PATCH v2 1/1] x86: check that clflushopt of an MMIO
 address succeeds
Date: Wed, 18 Nov 2020 12:11:29 +0000
Message-Id: <20201118121129.6276-2-david.edmondson@oracle.com>
X-Mailer: git-send-email 2.29.2
In-Reply-To: <20201118121129.6276-1-david.edmondson@oracle.com>
References: <20201118121129.6276-1-david.edmondson@oracle.com>
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9808
 signatures=668682
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 adultscore=0
 spamscore=0 phishscore=0
 suspectscore=1 mlxscore=0 malwarescore=0 bulkscore=0 mlxlogscore=999
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2011180087
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9808
 signatures=668682
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 bulkscore=0
 clxscore=1015
 malwarescore=0 impostorscore=0 lowpriorityscore=0 priorityscore=1501
 mlxlogscore=999 adultscore=0 phishscore=0 suspectscore=1 spamscore=0
 mlxscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2011180087
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Verify that the clflushopt instruction succeeds when applied to an
MMIO address at both cpl0 and cpl3.

Suggested-by: Joao Martins <joao.m.martins@oracle.com>
Signed-off-by: David Edmondson <david.edmondson@oracle.com>
---
 x86/Makefile.common   |  3 ++-
 x86/clflushopt_mmio.c | 45 +++++++++++++++++++++++++++++++++++++++++++
 x86/unittests.cfg     |  5 +++++
 3 files changed, 52 insertions(+), 1 deletion(-)
 create mode 100644 x86/clflushopt_mmio.c

```
