#### [RFC v3 01/11] eventfd: track eventfd_signal() recursion depth separately in different cases
##### From: Xie Yongji <xieyongji@bytedance.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xie Yongji <xieyongji@bytedance.com>
X-Patchwork-Id: 12029567
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 3AEF4C433E0
	for <kvm@archiver.kernel.org>; Tue, 19 Jan 2021 08:42:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id EA2ED23121
	for <kvm@archiver.kernel.org>; Tue, 19 Jan 2021 08:41:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727933AbhASFVr (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 19 Jan 2021 00:21:47 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:44342 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2388564AbhASFGL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 19 Jan 2021 00:06:11 -0500
Received: from mail-pf1-x42a.google.com (mail-pf1-x42a.google.com
 [IPv6:2607:f8b0:4864:20::42a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 83368C0613CF
        for <kvm@vger.kernel.org>; Mon, 18 Jan 2021 21:04:38 -0800 (PST)
Received: by mail-pf1-x42a.google.com with SMTP id i63so4441357pfg.7
        for <kvm@vger.kernel.org>; Mon, 18 Jan 2021 21:04:38 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=bytedance-com.20150623.gappssmtp.com; s=20150623;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=hq6cLGhX+YOdloZCBCv76n2UjaYC8NZfkFs6/p+ZtOg=;
        b=W8y876Dbq8gZuEg5QYXKhKTizoMMwtFxcmKeIZtDQdx+XEt3dW/eHtSMhQvknQYW4K
         DnsCpn+GirhCRLFyk/uVDaIJoXZgyWsH6gU53zdrGPud9lsener1pfIQEwdiCZRktfE+
         Ne1ZR7dli2HUDcE+3V2rbyvftav5V4WgBCwhpQ0bHoynV0GboyaGO/cjnRSZdzh0GmFw
         r/A5ZX/PxqxanTpbUqh+VaClMqoh4p4eePPZY6MRWFJ7BiyHJsTxQWwUiwGliuSOKvLc
         PCreg4kS3gTI+lm3d0KE5HrHAWJ4B0/fMhjVOWrn+u+7Kwg0P9wxlbpTSDhJDbdRaU+G
         Y9Jg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=hq6cLGhX+YOdloZCBCv76n2UjaYC8NZfkFs6/p+ZtOg=;
        b=CDJzaNB9y3wPQ8I8u97aaGnxL/8KfrXqCw1VOQLosxFy9WhCX3HJjgcdzdgDlBJi8q
         WhxyP6njlfH4yooV660b/F8GHAvchYzgbNlexnjPgODClNTOcMIJzYcanvArpS45dKKE
         WTOqrIHTxEqgF0tudAZcRszTnV3jNb02Jh6WrK4NE0tXDW6pC1mexk/U9jfA5O9g+rqq
         CFANBzjkSGszG3fpAmLfazwcXuSBAJe4c4xz4ycUuVnGz//SztJ2n7APLDC04b6PQ/KF
         ZqGz7TYqnbVQVt94z411KR1hXC8iqoSJEoto9CJtSX4NSAr81n0jyecukj1jIETdQ2eo
         OjlQ==
X-Gm-Message-State: AOAM533kiUO/CuHUxcVdBW8/PjZZ20zZ6Wr1u7Rle/BJR24o2t7JIjx/
        Bpe+fiIewRd39LUpeI7Knt2T
X-Google-Smtp-Source: 
 ABdhPJwhMmXGRAF9exzwdYFbs4DDh7HaNjaSgRVmLvyUt1TO1CzzbUW14r26LDKrseM7tbJ/BRrzFA==
X-Received: by 2002:a62:ddcd:0:b029:1a6:99ff:a75e with SMTP id
 w196-20020a62ddcd0000b02901a699ffa75emr2486197pff.42.1611032678076;
        Mon, 18 Jan 2021 21:04:38 -0800 (PST)
Received: from localhost ([139.177.225.243])
        by smtp.gmail.com with ESMTPSA id
 gv22sm1047509pjb.56.2021.01.18.21.04.36
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 18 Jan 2021 21:04:37 -0800 (PST)
From: Xie Yongji <xieyongji@bytedance.com>
To: mst@redhat.com, jasowang@redhat.com, stefanha@redhat.com,
        sgarzare@redhat.com, parav@nvidia.com, bob.liu@oracle.com,
        hch@infradead.org, rdunlap@infradead.org, willy@infradead.org,
        viro@zeniv.linux.org.uk, axboe@kernel.dk, bcrl@kvack.org,
        corbet@lwn.net
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        kvm@vger.kernel.org, linux-aio@kvack.org,
        linux-fsdevel@vger.kernel.org
Subject: [RFC v3 01/11] eventfd: track eventfd_signal() recursion depth
 separately in different cases
Date: Tue, 19 Jan 2021 12:59:10 +0800
Message-Id: <20210119045920.447-2-xieyongji@bytedance.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20210119045920.447-1-xieyongji@bytedance.com>
References: <20210119045920.447-1-xieyongji@bytedance.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Now we have a global percpu counter to limit the recursion depth
of eventfd_signal(). This can avoid deadlock or stack overflow.
But in stack overflow case, it should be OK to increase the
recursion depth if needed. So we add a percpu counter in eventfd_ctx
to limit the recursion depth for deadlock case. Then it could be
fine to increase the global percpu counter later.

Signed-off-by: Xie Yongji <xieyongji@bytedance.com>
---
 fs/aio.c                |  3 ++-
 fs/eventfd.c            | 20 +++++++++++++++++++-
 include/linux/eventfd.h |  5 +----
 3 files changed, 22 insertions(+), 6 deletions(-)

```
#### [PATCH 1/2] s390: uv: Fix sysfs max number of VCPUs reporting
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 12030461
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id CDD4EC43219
	for <kvm@archiver.kernel.org>; Tue, 19 Jan 2021 18:27:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 92EDB22D71
	for <kvm@archiver.kernel.org>; Tue, 19 Jan 2021 18:27:11 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2390684AbhASOts (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 19 Jan 2021 09:49:48 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:10748 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S2389552AbhASKFs (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 19 Jan 2021 05:05:48 -0500
Received: from pps.filterd (m0098404.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 10JA3UxX030299;
        Tue, 19 Jan 2021 05:05:07 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=8H7BE5qafj9KsQRDUGOWKDm4V/rUGUehRQilH/Unm4w=;
 b=CcfsM8W/yq9Sj0dNXTzudrdOF4Ksw4zKsABGzSMuxMBrpTgEKlt897Uyay5BDkk4CGFC
 hGZvLX4n2pmqqD+60E3sqikOtDrR3Q/bZILD1e2Z8q8qhj3/L2ZviPkvZrh0fqAXKfSs
 OvYnRS1ZBKVwaUa5U1zk7VFYMxvfmMdVvNn007+Evuo/ObQR+hwFCqO80IZvTTaVm1G2
 sYa9gfKqBpM87fgN1H9OOUSiMblk6rzwIAmHTk9U7rh00Wdd0fghTMW7b5kLsMUChETe
 bUo+O2NHjK4KCuLf1EPCQDZyLb2AA0pHoHpGWp08XF1jCAFdJ3VQ8NXsmiTJSmKgqcxK Qg==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 365w2hgfts-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 19 Jan 2021 05:05:07 -0500
Received: from m0098404.ppops.net (m0098404.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 10JA56mm038560;
        Tue, 19 Jan 2021 05:05:06 -0500
Received: from ppma05fra.de.ibm.com (6c.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.108])
        by mx0a-001b2d01.pphosted.com with ESMTP id 365w2hgfrj-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 19 Jan 2021 05:05:06 -0500
Received: from pps.filterd (ppma05fra.de.ibm.com [127.0.0.1])
        by ppma05fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 10JA3Swq002255;
        Tue, 19 Jan 2021 10:05:03 GMT
Received: from b06cxnps3074.portsmouth.uk.ibm.com
 (d06relay09.portsmouth.uk.ibm.com [9.149.109.194])
        by ppma05fra.de.ibm.com with ESMTP id 363qs89gj0-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 19 Jan 2021 10:05:03 +0000
Received: from d06av22.portsmouth.uk.ibm.com (d06av22.portsmouth.uk.ibm.com
 [9.149.105.58])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 10JA50n77733530
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 19 Jan 2021 10:05:00 GMT
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 9216A4C046;
        Tue, 19 Jan 2021 10:05:00 +0000 (GMT)
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 8E1284C050;
        Tue, 19 Jan 2021 10:04:59 +0000 (GMT)
Received: from linux01.pok.stglabs.ibm.com (unknown [9.114.17.81])
        by d06av22.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue, 19 Jan 2021 10:04:59 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: linux-kernel@vger.kernel.org
Cc: kvm@vger.kernel.org, thuth@redhat.com, david@redhat.com,
        borntraeger@de.ibm.com, imbrenda@linux.ibm.com, cohuck@redhat.com,
        linux-s390@vger.kernel.org, gor@linux.ibm.com,
        mihajlov@linux.ibm.com
Subject: [PATCH 1/2] s390: uv: Fix sysfs max number of VCPUs reporting
Date: Tue, 19 Jan 2021 05:04:01 -0500
Message-Id: <20210119100402.84734-2-frankja@linux.ibm.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20210119100402.84734-1-frankja@linux.ibm.com>
References: <20210119100402.84734-1-frankja@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.343,18.0.737
 definitions=2021-01-19_02:2021-01-18,2021-01-19 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxlogscore=999
 impostorscore=0 bulkscore=0 mlxscore=0 lowpriorityscore=0 malwarescore=0
 priorityscore=1501 clxscore=1015 phishscore=0 adultscore=0 spamscore=0
 suspectscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2101190058
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The number reported by the query is N-1 and I think people reading the
sysfs file would expect N instead. For users creating VMs there's no
actual difference because KVM's limit is currently below the UV's
limit.

The naming of the field is a bit misleading. Number in this context is
used like ID and starts at 0. The query field denotes the maximum
number that can be put into the VCPU number field in the "create
secure CPU" UV call.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Fixes: a0f60f8431999 ("s390/protvirt: Add sysfs firmware interface for Ultravisor information")
Cc: stable@vger.kernel.org
Acked-by: Cornelia Huck <cohuck@redhat.com>
---
 arch/s390/boot/uv.c        | 2 +-
 arch/s390/include/asm/uv.h | 4 ++--
 arch/s390/kernel/uv.c      | 2 +-
 3 files changed, 4 insertions(+), 4 deletions(-)

```
#### [kvm-unit-tests PATCH v3 1/3] s390x: pv: implement routine to share/unshare memory
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 12030655
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 0B30FC433DB
	for <kvm@archiver.kernel.org>; Tue, 19 Jan 2021 19:54:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B53F82310D
	for <kvm@archiver.kernel.org>; Tue, 19 Jan 2021 19:54:08 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729810AbhASTyD (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 19 Jan 2021 14:54:03 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:4784 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S2392020AbhASTxX (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 19 Jan 2021 14:53:23 -0500
Received: from pps.filterd (m0098410.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 10JJXpXK068391;
        Tue, 19 Jan 2021 14:52:32 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references; s=pp1;
 bh=Nsj2S9g3UGYn0YL15B/RwQuQTozZIRIjXVlGiMkrA8U=;
 b=nm2UFjqdtv4KBUxLn9ZQI8kQQFGOVNZws21Yojyh3YtJ3oL9bwa8zZ9m9Sd3gDLCwz4c
 6ude27F+j+dEjG949bKYYNM/IH2zlGE1OrkVdGRqkcVjfgvP7PUOpy1qwK+H6OvosCOX
 17YT6rOGK0mcYLVTA3BUBYdKnuPj5yRxFc4guORqVuGK7SBD7PInFWjot/x9Ziao2Fyi
 fnkPgkO918/XuBEOVFzVMLz8ujYzpLH1LEU8zxxEp8Pn0H6gpB5XkvKho2hJkJ4R7hFo
 xl+w/vjvKZHF08LuS/8sq9AWu2PSFiX6SB/9EgWtlDlyw2sCubEtyhvvYevztgj5ZzYk TQ==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 36621p7nhg-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 19 Jan 2021 14:52:32 -0500
Received: from m0098410.ppops.net (m0098410.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 10JJncg2131754;
        Tue, 19 Jan 2021 14:52:31 -0500
Received: from ppma06fra.de.ibm.com (48.49.7a9f.ip4.static.sl-reverse.com
 [159.122.73.72])
        by mx0a-001b2d01.pphosted.com with ESMTP id 36621p7ngp-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 19 Jan 2021 14:52:31 -0500
Received: from pps.filterd (ppma06fra.de.ibm.com [127.0.0.1])
        by ppma06fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 10JJlq4l001790;
        Tue, 19 Jan 2021 19:52:29 GMT
Received: from b06cxnps4074.portsmouth.uk.ibm.com
 (d06relay11.portsmouth.uk.ibm.com [9.149.109.196])
        by ppma06fra.de.ibm.com with ESMTP id 363qdh9s7y-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 19 Jan 2021 19:52:29 +0000
Received: from d06av24.portsmouth.uk.ibm.com (mk.ibm.com [9.149.105.60])
        by b06cxnps4074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 10JJqQvG46662098
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 19 Jan 2021 19:52:26 GMT
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 5942742047;
        Tue, 19 Jan 2021 19:52:26 +0000 (GMT)
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id E6DCB4203F;
        Tue, 19 Jan 2021 19:52:25 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.38.46])
        by d06av24.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue, 19 Jan 2021 19:52:25 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, frankja@linux.ibm.com,
        david@redhat.com, thuth@redhat.com, cohuck@redhat.com,
        imbrenda@linux.ibm.com, drjones@redhat.com, pbonzini@redhat.com
Subject: [kvm-unit-tests PATCH v3 1/3] s390x: pv: implement routine to
 share/unshare memory
Date: Tue, 19 Jan 2021 20:52:22 +0100
Message-Id: <1611085944-21609-2-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1611085944-21609-1-git-send-email-pmorel@linux.ibm.com>
References: <1611085944-21609-1-git-send-email-pmorel@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.343,18.0.737
 definitions=2021-01-19_09:2021-01-18,2021-01-19 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 suspectscore=0
 priorityscore=1501 impostorscore=0 spamscore=0 lowpriorityscore=0
 malwarescore=0 bulkscore=0 phishscore=0 adultscore=0 mlxlogscore=999
 clxscore=1015 mlxscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2101190106
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When communicating with the host we need to share part of
the memory.

Let's implement the ultravisor calls for this.

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
Suggested-by: Janosch Frank <frankja@linux.ibm.com>
Acked-by: Cornelia Huck <cohuck@redhat.com>
---
 lib/s390x/asm/uv.h | 38 ++++++++++++++++++++++++++++++++++++++
 1 file changed, 38 insertions(+)

```
#### [PATCH 1/4] s390/pci: track alignment/length strictness for zpci_dev
##### From: Matthew Rosato <mjrosato@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Matthew Rosato <mjrosato@linux.ibm.com>
X-Patchwork-Id: 12030681
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E0F8BC433E0
	for <kvm@archiver.kernel.org>; Tue, 19 Jan 2021 20:07:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8E0F82310B
	for <kvm@archiver.kernel.org>; Tue, 19 Jan 2021 20:07:56 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729548AbhASUHa (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 19 Jan 2021 15:07:30 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:52826 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1728613AbhASUDW (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 19 Jan 2021 15:03:22 -0500
Received: from pps.filterd (m0098416.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 10JK2WFA177644;
        Tue, 19 Jan 2021 15:02:40 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references; s=pp1;
 bh=Ll19ePRbwoEsUoHXPbtitX6SHMdAUB9AHe5X2OcjHU8=;
 b=ohL4nccilAUlyQ016hVzZFb16hXWwJmdELJEsFv/ZMNGmOd5J60ao+MAidVdzXvTY2DW
 6eipx2VcitJQcgNXp55TrzcAH+6w+/zMEVFUcHT95iwRgbWTTfXI2hLeVtishY4+ACB0
 g/6So5+dYgvW4Av+3IVUne+Tw7fWBOX6jk2Y2U0XAd7qqaGv1duwePk5qUHxNL+s4Khk
 GSltmzZhkiy/mHjeGzikmRcYEzwtPt2+DKYsGDh5J03Pndk/PbpKeY/naafpfT0aZcgM
 o3+MyLoObbBAbRKpp7KtXRO/1tfuhWW594iBF3f5BWvNnFzY3wPlmF9QJcBmJEeMNGFH uA==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 366607g5tr-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 19 Jan 2021 15:02:40 -0500
Received: from m0098416.ppops.net (m0098416.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 10JK2aeN178104;
        Tue, 19 Jan 2021 15:02:39 -0500
Received: from ppma05wdc.us.ibm.com (1b.90.2fa9.ip4.static.sl-reverse.com
 [169.47.144.27])
        by mx0b-001b2d01.pphosted.com with ESMTP id 366607g5tc-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 19 Jan 2021 15:02:39 -0500
Received: from pps.filterd (ppma05wdc.us.ibm.com [127.0.0.1])
        by ppma05wdc.us.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 10JK2U4X025577;
        Tue, 19 Jan 2021 20:02:39 GMT
Received: from b01cxnp23032.gho.pok.ibm.com (b01cxnp23032.gho.pok.ibm.com
 [9.57.198.27])
        by ppma05wdc.us.ibm.com with ESMTP id 363qs90q6v-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 19 Jan 2021 20:02:39 +0000
Received: from b01ledav006.gho.pok.ibm.com (b01ledav006.gho.pok.ibm.com
 [9.57.199.111])
        by b01cxnp23032.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id 10JK2b9630933286
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 19 Jan 2021 20:02:37 GMT
Received: from b01ledav006.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 7783EAC05B;
        Tue, 19 Jan 2021 20:02:37 +0000 (GMT)
Received: from b01ledav006.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 87A93AC059;
        Tue, 19 Jan 2021 20:02:35 +0000 (GMT)
Received: from oc4221205838.ibm.com (unknown [9.211.56.144])
        by b01ledav006.gho.pok.ibm.com (Postfix) with ESMTP;
        Tue, 19 Jan 2021 20:02:35 +0000 (GMT)
From: Matthew Rosato <mjrosato@linux.ibm.com>
To: alex.williamson@redhat.com, cohuck@redhat.com,
        schnelle@linux.ibm.com
Cc: pmorel@linux.ibm.com, borntraeger@de.ibm.com, hca@linux.ibm.com,
        gor@linux.ibm.com, gerald.schaefer@linux.ibm.com,
        linux-s390@vger.kernel.org, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH 1/4] s390/pci: track alignment/length strictness for zpci_dev
Date: Tue, 19 Jan 2021 15:02:27 -0500
Message-Id: <1611086550-32765-2-git-send-email-mjrosato@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1611086550-32765-1-git-send-email-mjrosato@linux.ibm.com>
References: <1611086550-32765-1-git-send-email-mjrosato@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.343,18.0.737
 definitions=2021-01-19_09:2021-01-18,2021-01-19 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 lowpriorityscore=0
 mlxlogscore=999 malwarescore=0 suspectscore=0 mlxscore=0 impostorscore=0
 spamscore=0 phishscore=0 adultscore=0 clxscore=1015 priorityscore=1501
 bulkscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2101190106
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Some zpci device types (e.g., ISM) follow different rules for length
and alignment of pci instructions.  Recognize this and keep track of
it in the zpci_dev.

Signed-off-by: Matthew Rosato <mjrosato@linux.ibm.com>
Reviewed-by: Niklas Schnelle <schnelle@linux.ibm.com>
Reviewed-by: Pierre Morel <pmorel@linux.ibm.com>
---
 arch/s390/include/asm/pci.h     | 3 ++-
 arch/s390/include/asm/pci_clp.h | 4 +++-
 arch/s390/pci/pci_clp.c         | 1 +
 3 files changed, 6 insertions(+), 2 deletions(-)

```
#### [PATCH V2 1/9] vfio: option to unmap all
##### From: Steve Sistare <steven.sistare@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Steven Sistare <steven.sistare@oracle.com>
X-Patchwork-Id: 12030485
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.9 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	UNPARSEABLE_RELAY,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id BD1E9C10F07
	for <kvm@archiver.kernel.org>; Tue, 19 Jan 2021 18:30:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8D1BE22E01
	for <kvm@archiver.kernel.org>; Tue, 19 Jan 2021 18:30:15 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2392534AbhASS0O (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 19 Jan 2021 13:26:14 -0500
Received: from userp2130.oracle.com ([156.151.31.86]:48146 "EHLO
        userp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727414AbhASSQr (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 19 Jan 2021 13:16:47 -0500
Received: from pps.filterd (userp2130.oracle.com [127.0.0.1])
        by userp2130.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 10JI9Ujr129644;
        Tue, 19 Jan 2021 18:16:03 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references; s=corp-2020-01-29;
 bh=Jht8y0GDOpOhrB/UuJl9RZfl5NEsnAsBx4Quts4qYrY=;
 b=VsJGtCyy/gHugQPybD95kO8TPL/bKU14YxLQFoj+N0sk0I/eEKNk1exCs9peV8wHux1J
 fjivDVgOmCm6mHgGYQuUSfstzoBnXV0U1m38Vwv6PCfEe9WbXNF/CRT8du0uTFUlos0B
 XxCD7oXj/hgHAKdJ7C2vfYdYgTnzhzepCOEuoJPA7AUcLVuOzF7+LucbUzwBf7vGVPv5
 HO6UogPcpc0T3k6NBasrM8pWmUh/FYyn9AOewx7RtcPDStunxg89td8PqT195bSPeoAd
 NquJ+9OY19DGjhkx3nP3XjpSV6D7d9XGSL69D3xDNBMSKriBuQPsnGn3oD0ef8VRyKo3 Iw==
Received: from userp3030.oracle.com (userp3030.oracle.com [156.151.31.80])
        by userp2130.oracle.com with ESMTP id 363xyhsrrc-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 19 Jan 2021 18:16:02 +0000
Received: from pps.filterd (userp3030.oracle.com [127.0.0.1])
        by userp3030.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 10JIBdp7079540;
        Tue, 19 Jan 2021 18:16:00 GMT
Received: from aserv0122.oracle.com (aserv0122.oracle.com [141.146.126.236])
        by userp3030.oracle.com with ESMTP id 3661njmm8w-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 19 Jan 2021 18:16:00 +0000
Received: from abhmp0001.oracle.com (abhmp0001.oracle.com [141.146.116.7])
        by aserv0122.oracle.com (8.14.4/8.14.4) with ESMTP id 10JIFxVX018594;
        Tue, 19 Jan 2021 18:15:59 GMT
Received: from ca-dev63.us.oracle.com (/10.211.8.221)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Tue, 19 Jan 2021 10:15:59 -0800
From: Steve Sistare <steven.sistare@oracle.com>
To: kvm@vger.kernel.org
Cc: Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Kirti Wankhede <kwankhede@nvidia.com>,
        Steve Sistare <steven.sistare@oracle.com>
Subject: [PATCH V2 1/9] vfio: option to unmap all
Date: Tue, 19 Jan 2021 09:48:21 -0800
Message-Id: <1611078509-181959-2-git-send-email-steven.sistare@oracle.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1611078509-181959-1-git-send-email-steven.sistare@oracle.com>
References: <1611078509-181959-1-git-send-email-steven.sistare@oracle.com>
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9869
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=0
 adultscore=0
 phishscore=0 malwarescore=0 bulkscore=0 mlxscore=0 spamscore=0
 mlxlogscore=999 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2101190102
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9869
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 adultscore=1
 phishscore=0
 malwarescore=0 mlxlogscore=999 bulkscore=0 priorityscore=1501 spamscore=0
 mlxscore=0 impostorscore=0 lowpriorityscore=0 suspectscore=0 clxscore=1015
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2101190102
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

For the UNMAP_DMA ioctl, delete all mappings if VFIO_DMA_UNMAP_FLAG_ALL
is set.  Define the corresponding VFIO_UNMAP_ALL extension.

Signed-off-by: Steve Sistare <steven.sistare@oracle.com>
---
 include/uapi/linux/vfio.h | 8 ++++++++
 1 file changed, 8 insertions(+)

```
