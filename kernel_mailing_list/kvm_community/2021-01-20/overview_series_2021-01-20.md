#### [kvm-unit-tests GIT PULL 01/11] s390x: Move to GPL 2 and SPDX license identifiers
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 12032233
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D8B31C433E0
	for <kvm@archiver.kernel.org>; Wed, 20 Jan 2021 12:49:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8FF2823382
	for <kvm@archiver.kernel.org>; Wed, 20 Jan 2021 12:49:16 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729522AbhATMtJ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 20 Jan 2021 07:49:09 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:28828 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S2388394AbhATLoR (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 20 Jan 2021 06:44:17 -0500
Received: from pps.filterd (m0098396.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 10KBYDXS077116;
        Wed, 20 Jan 2021 06:43:35 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=f38t3+EMIJAVt/6OrrruLz2QLaRxfKGo09TbV1r+30c=;
 b=ZqUVMEzGP7xKiwRM9uCF3NLLV9HTMroNKsh3GA12Vm+ChG2JS0LIIm/s0YwqcjUyRtyl
 jXVhRfM1aTNE0SUUIOVXQ5/YB7+6khbS0uQ7VFyV7fLN6PG8QiwTyWS0eq3v8j4qypEN
 IYm7qK/EJzIv9z8dYh8ba3kjeNz16HFr4hZS4QBFa4fQFo0Uz4EsKvH7nIBtliiVmnwt
 VY6W7wj748hCpgxpJGH99pP8ke1020aw4SncP5fb3aUyIFnyBHLEvUO0SxF+9zVrqLxI
 gqDTjY2t9rd7iKBoj9faA9INrBFjHm2MGu4RkSTHIRcAkBfrgukjSUhsZpbnhYmBZQ7B 6w==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 366j4bu69n-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 20 Jan 2021 06:43:35 -0500
Received: from m0098396.ppops.net (m0098396.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 10KBYxqG081483;
        Wed, 20 Jan 2021 06:43:34 -0500
Received: from ppma06ams.nl.ibm.com (66.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.102])
        by mx0a-001b2d01.pphosted.com with ESMTP id 366j4bu690-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 20 Jan 2021 06:43:34 -0500
Received: from pps.filterd (ppma06ams.nl.ibm.com [127.0.0.1])
        by ppma06ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 10KBgpAa005129;
        Wed, 20 Jan 2021 11:43:32 GMT
Received: from b06cxnps3074.portsmouth.uk.ibm.com
 (d06relay09.portsmouth.uk.ibm.com [9.149.109.194])
        by ppma06ams.nl.ibm.com with ESMTP id 3668nwrhd0-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 20 Jan 2021 11:43:32 +0000
Received: from d06av26.portsmouth.uk.ibm.com (d06av26.portsmouth.uk.ibm.com
 [9.149.105.62])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 10KBhT1517432942
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 20 Jan 2021 11:43:29 GMT
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 03B9BAE05F;
        Wed, 20 Jan 2021 11:43:29 +0000 (GMT)
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 2BEB9AE056;
        Wed, 20 Jan 2021 11:43:28 +0000 (GMT)
Received: from linux01.pok.stglabs.ibm.com (unknown [9.114.17.81])
        by d06av26.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Wed, 20 Jan 2021 11:43:28 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: pbonzini@redhat.com
Cc: kvm@vger.kernel.org, frankja@linux.ibm.com, david@redhat.com,
        borntraeger@de.ibm.com, cohuck@redhat.com,
        linux-s390@vger.kernel.org, imbrenda@linux.ibm.com
Subject: [kvm-unit-tests GIT PULL 01/11] s390x: Move to GPL 2 and SPDX license
 identifiers
Date: Wed, 20 Jan 2021 06:41:48 -0500
Message-Id: <20210120114158.104559-2-frankja@linux.ibm.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20210120114158.104559-1-frankja@linux.ibm.com>
References: <20210120114158.104559-1-frankja@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.343,18.0.737
 definitions=2021-01-20_02:2021-01-18,2021-01-20 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 bulkscore=0 spamscore=0
 mlxscore=0 impostorscore=0 malwarescore=0 adultscore=0 clxscore=1015
 lowpriorityscore=0 phishscore=0 priorityscore=1501 suspectscore=0
 mlxlogscore=999 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2101200064
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In the past we had some issues when developers wanted to use code
snippets or constants from the kernel in a test or in the library. To
remedy that the s390x maintainers decided to move all files to GPL
2 (if possible).

At the same time let's move to SPDX identifiers as they are much nicer
to read.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Acked-by: David Hildenbrand <david@redhat.com>
Acked-by: Pierre Morel <pmorel@linux.ibm.com>
---
 s390x/cmm.c       | 4 +---
 s390x/cpumodel.c  | 4 +---
 s390x/css.c       | 4 +---
 s390x/cstart64.S  | 4 +---
 s390x/diag10.c    | 4 +---
 s390x/diag288.c   | 4 +---
 s390x/diag308.c   | 5 +----
 s390x/emulator.c  | 4 +---
 s390x/gs.c        | 4 +---
 s390x/iep.c       | 4 +---
 s390x/intercept.c | 4 +---
 s390x/pfmf.c      | 4 +---
 s390x/sclp.c      | 4 +---
 s390x/selftest.c  | 4 +---
 s390x/skey.c      | 4 +---
 s390x/skrf.c      | 4 +---
 s390x/smp.c       | 4 +---
 s390x/sthyi.c     | 4 +---
 s390x/sthyi.h     | 4 +---
 s390x/stsi.c      | 4 +---
 s390x/uv-guest.c  | 4 +---
 s390x/vector.c    | 4 +---
 22 files changed, 22 insertions(+), 67 deletions(-)

```
#### [kvm-unit-tests PATCH] travis.yml: Remove the CI file for Travis, it's of no use anymore
##### From: Thomas Huth <thuth@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Huth <thuth@redhat.com>
X-Patchwork-Id: 12032039
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.9 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C602AC4332E
	for <kvm@archiver.kernel.org>; Wed, 20 Jan 2021 11:12:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8193922AAA
	for <kvm@archiver.kernel.org>; Wed, 20 Jan 2021 11:12:16 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728883AbhATLJG (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 20 Jan 2021 06:09:06 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:27109 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1731491AbhATJhA (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 20 Jan 2021 04:37:00 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1611135331;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=z772Qt9JiJWD0EmElx1f24c9GfndbwsLkJfCmUU+Pe0=;
        b=S/jnafcYfqcZssJ2VTqzkGi5RqM8LNMmDVe5UjmCdv/NYHjnRswXBfcZ/k2/XWxVFBdQB+
        /Y+8H6OpSVxomAUrniV84qiMh1ZFzxoCuDO6Y1+h8DEvtX05za96tY8LN8VpZ7sBdUl3pb
        kdGbYSWA8Tq3vGCJMRRq/XdrzT4n+FM=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-338-EPgEeZn6OJ-74YRC-5IiBw-1; Wed, 20 Jan 2021 04:35:29 -0500
X-MC-Unique: EPgEeZn6OJ-74YRC-5IiBw-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 68E08E743
        for <kvm@vger.kernel.org>; Wed, 20 Jan 2021 09:35:28 +0000 (UTC)
Received: from thuth.com (ovpn-114-135.ams2.redhat.com [10.36.114.135])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 821285D755;
        Wed, 20 Jan 2021 09:35:27 +0000 (UTC)
From: Thomas Huth <thuth@redhat.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com
Subject: [kvm-unit-tests PATCH] travis.yml: Remove the CI file for Travis,
 it's of no use anymore
Date: Wed, 20 Jan 2021 10:35:25 +0100
Message-Id: <20210120093525.463974-1-thuth@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

With its new policy, Travis-CI has become completely useless for
OSS projects like kvm-unit-tests. Thus remove the YML file now.

Signed-off-by: Thomas Huth <thuth@redhat.com>
---
 .travis.yml | 180 ----------------------------------------------------
 1 file changed, 180 deletions(-)
 delete mode 100644 .travis.yml

diff --git a/.travis.yml b/.travis.yml
```
#### [PATCH v4 07/15] x86/paravirt: switch time pvops functions to use static_call()
##### From: Juergen Gross <jgross@suse.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Juergen Gross <jgross@suse.com>
X-Patchwork-Id: 12032429
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 5C138C433DB
	for <kvm@archiver.kernel.org>; Wed, 20 Jan 2021 13:51:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1324323371
	for <kvm@archiver.kernel.org>; Wed, 20 Jan 2021 13:51:42 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732904AbhATNqu (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 20 Jan 2021 08:46:50 -0500
Received: from mx2.suse.de ([195.135.220.15]:46786 "EHLO mx2.suse.de"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727909AbhATN3B (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 20 Jan 2021 08:29:01 -0500
X-Virus-Scanned: by amavisd-new at test-mx.suse.de
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=suse.com; s=susede1;
        t=1611149175;
 h=from:from:reply-to:date:date:message-id:message-id:to:to:cc:
         mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=gPBshvehzp6blrUnnUW76rGI6e9WlnGmkT7jZvn/5h4=;
        b=ip5cvQkQhZ0x35CzXVMatPB+PdfjIPbcH257epLyzqGy2HKLQ6bo8MxnEnBcmP5CJsKot2
        F2HpYRSwoDeIPqWRWHu75teld+o7A5CwB8T90xznJZ9EPpLMLG0YrNjpUsWMxXvFRFmk9D
        yVHbUGreWfGE7cx1Z9yH95VaHuQ0cfM=
Received: from relay2.suse.de (unknown [195.135.221.27])
        by mx2.suse.de (Postfix) with ESMTP id 03DB5AE89;
        Wed, 20 Jan 2021 13:26:15 +0000 (UTC)
From: Juergen Gross <jgross@suse.com>
To: bpetkov@suse.com, x86@kernel.org, linux-kernel@vger.kernel.org,
        linux-hyperv@vger.kernel.org,
        virtualization@lists.linux-foundation.org, kvm@vger.kernel.org
Subject: [PATCH v4 07/15] x86/paravirt: switch time pvops functions to use
 static_call()
Date: Wed, 20 Jan 2021 14:26:05 +0100
Message-Id: <20210120132613.31487-8-jgross@suse.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20210120132613.31487-1-jgross@suse.com>
References: <20210120132613.31487-1-jgross@suse.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The time pvops functions are the only ones left which might be
used in 32-bit mode and which return a 64-bit value.

Switch them to use the static_call() mechanism instead of pvops, as
this allows quite some simplification of the pvops implementation.

Signed-off-by: Juergen Gross <jgross@suse.com>
---
V4:
- drop paravirt_time.h again
- don't move Hyper-V code (Michael Kelley)
---
 arch/x86/Kconfig                      |  1 +
 arch/x86/include/asm/mshyperv.h       |  2 +-
 arch/x86/include/asm/paravirt.h       | 17 ++++++++++++++---
 arch/x86/include/asm/paravirt_types.h |  6 ------
 arch/x86/kernel/cpu/vmware.c          |  5 +++--
 arch/x86/kernel/kvm.c                 |  2 +-
 arch/x86/kernel/kvmclock.c            |  2 +-
 arch/x86/kernel/paravirt.c            | 16 ++++++++++++----
 arch/x86/kernel/tsc.c                 |  2 +-
 arch/x86/xen/time.c                   | 11 ++++-------
 drivers/clocksource/hyperv_timer.c    |  5 +++--
 drivers/xen/time.c                    |  2 +-
 12 files changed, 42 insertions(+), 29 deletions(-)

```
#### [PATCH v4 07/15] x86/paravirt: switch time pvops functions to use static_call()
##### From: Juergen Gross <jgross@suse.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Juergen Gross <jgross@suse.com>
X-Patchwork-Id: 12033609
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 4D696C433E0
	for <kvm@archiver.kernel.org>; Wed, 20 Jan 2021 20:16:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DEA5823442
	for <kvm@archiver.kernel.org>; Wed, 20 Jan 2021 20:16:39 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388106AbhATUPv (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 20 Jan 2021 15:15:51 -0500
Received: from mx2.suse.de ([195.135.220.15]:59160 "EHLO mx2.suse.de"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1731298AbhATOA6 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 20 Jan 2021 09:00:58 -0500
X-Virus-Scanned: by amavisd-new at test-mx.suse.de
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=suse.com; s=susede1;
        t=1611150962;
 h=from:from:reply-to:date:date:message-id:message-id:to:to:cc:cc:
         mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=gPBshvehzp6blrUnnUW76rGI6e9WlnGmkT7jZvn/5h4=;
        b=uOewyFTuTYGcYqxaS0f68MyKay0eqqN+HXVU32cgfoN5DndxAGzsBwPYX4CD6fN0eTpUcR
        /VUme5cGWuqQmclhE5Inn0NwniOKuwJXX92yJG2xnqXDL4txCiknH035LivyF1x+J+r1ps
        3w2LJEjyzXQ9RfDjMg2CU4hqw5bP95Q=
Received: from relay2.suse.de (unknown [195.135.221.27])
        by mx2.suse.de (Postfix) with ESMTP id C1D49B699;
        Wed, 20 Jan 2021 13:56:01 +0000 (UTC)
From: Juergen Gross <jgross@suse.com>
To: xen-devel@lists.xenproject.org, x86@kernel.org,
        linux-kernel@vger.kernel.org, linux-hyperv@vger.kernel.org,
        virtualization@lists.linux-foundation.org, kvm@vger.kernel.org
Cc: Juergen Gross <jgross@suse.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        "H. Peter Anvin" <hpa@zytor.com>,
        "K. Y. Srinivasan" <kys@microsoft.com>,
        Haiyang Zhang <haiyangz@microsoft.com>,
        Stephen Hemminger <sthemmin@microsoft.com>,
        Wei Liu <wei.liu@kernel.org>, Deep Shah <sdeep@vmware.com>,
        "VMware, Inc." <pv-drivers@vmware.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Boris Ostrovsky <boris.ostrovsky@oracle.com>,
        Stefano Stabellini <sstabellini@kernel.org>,
        Daniel Lezcano <daniel.lezcano@linaro.org>
Subject: [PATCH v4 07/15] x86/paravirt: switch time pvops functions to use
 static_call()
Date: Wed, 20 Jan 2021 14:55:47 +0100
Message-Id: <20210120135555.32594-8-jgross@suse.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20210120135555.32594-1-jgross@suse.com>
References: <20210120135555.32594-1-jgross@suse.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The time pvops functions are the only ones left which might be
used in 32-bit mode and which return a 64-bit value.

Switch them to use the static_call() mechanism instead of pvops, as
this allows quite some simplification of the pvops implementation.

Signed-off-by: Juergen Gross <jgross@suse.com>
---
V4:
- drop paravirt_time.h again
- don't move Hyper-V code (Michael Kelley)
---
 arch/x86/Kconfig                      |  1 +
 arch/x86/include/asm/mshyperv.h       |  2 +-
 arch/x86/include/asm/paravirt.h       | 17 ++++++++++++++---
 arch/x86/include/asm/paravirt_types.h |  6 ------
 arch/x86/kernel/cpu/vmware.c          |  5 +++--
 arch/x86/kernel/kvm.c                 |  2 +-
 arch/x86/kernel/kvmclock.c            |  2 +-
 arch/x86/kernel/paravirt.c            | 16 ++++++++++++----
 arch/x86/kernel/tsc.c                 |  2 +-
 arch/x86/xen/time.c                   | 11 ++++-------
 drivers/clocksource/hyperv_timer.c    |  5 +++--
 drivers/xen/time.c                    |  2 +-
 12 files changed, 42 insertions(+), 29 deletions(-)

```
