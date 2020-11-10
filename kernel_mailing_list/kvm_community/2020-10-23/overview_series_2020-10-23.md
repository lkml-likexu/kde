#### [PATCH 1/2] vfio/fsl-mc: return -EFAULT if copy_to_user() fails
##### From: Dan Carpenter <dan.carpenter@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Dan Carpenter <dan.carpenter@oracle.com>
X-Patchwork-Id: 11852805
Return-Path: <SRS0=GVEW=D6=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-9.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,
	UNPARSEABLE_RELAY autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 3AB0EC388F9
	for <kvm@archiver.kernel.org>; Fri, 23 Oct 2020 11:35:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D7BE524640
	for <kvm@archiver.kernel.org>; Fri, 23 Oct 2020 11:35:39 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="ycyNbGIS"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S463085AbgJWLfh (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 23 Oct 2020 07:35:37 -0400
Received: from aserp2130.oracle.com ([141.146.126.79]:44820 "EHLO
        aserp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S463005AbgJWLfh (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 23 Oct 2020 07:35:37 -0400
Received: from pps.filterd (aserp2130.oracle.com [127.0.0.1])
        by aserp2130.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 09NBZBam038615;
        Fri, 23 Oct 2020 11:35:23 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=date : from : to : cc
 : subject : message-id : mime-version : content-type; s=corp-2020-01-29;
 bh=MZC7JzA0X48T2AyIDafeWsyEuoX/erVd04kR6+/WI6w=;
 b=ycyNbGIShAyaP6gtNubm3VeF9kduIaWjCbMRE9WBE7ZybGeVm8EEKEIIa3gvPpm/6JpR
 yS3fpNRcrpbu9hV0tieqMBwE+oHOTrzFpdVS1/+AuR9q2lsEuyR8AXvk2gzeCzpiqdLr
 3Z38ov1i8L/M6rmbPULb1anQdPZ1RqyeaCksO+hnjzGYxA+QuaP9mZZpbr8N79io7dG1
 Jqkke4Cay4weLjCoyOByzctch60yXSvP2z28v7FZl/Ao68bgmQXBqjG7H+O1tOJQuT/U
 EsN10ULx5ID0FMUUYDF+TZ4KF8dOEbCOvj6UwvlbqFz5d53JMnl58+PVzbiqnW97V4ep Og==
Received: from aserp3020.oracle.com (aserp3020.oracle.com [141.146.126.70])
        by aserp2130.oracle.com with ESMTP id 347p4bas0r-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=FAIL);
        Fri, 23 Oct 2020 11:35:23 +0000
Received: from pps.filterd (aserp3020.oracle.com [127.0.0.1])
        by aserp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 09NBPlEm123836;
        Fri, 23 Oct 2020 11:35:22 GMT
Received: from aserv0121.oracle.com (aserv0121.oracle.com [141.146.126.235])
        by aserp3020.oracle.com with ESMTP id 348ah1we9w-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 23 Oct 2020 11:35:22 +0000
Received: from abhmp0005.oracle.com (abhmp0005.oracle.com [141.146.116.11])
        by aserv0121.oracle.com (8.14.4/8.13.8) with ESMTP id 09NBZLCU011502;
        Fri, 23 Oct 2020 11:35:21 GMT
Received: from mwanda (/41.57.98.10)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Fri, 23 Oct 2020 04:34:57 -0700
Date: Fri, 23 Oct 2020 14:34:50 +0300
From: Dan Carpenter <dan.carpenter@oracle.com>
To: Diana Craciun <diana.craciun@oss.nxp.com>
Cc: Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Bharat Bhushan <Bharat.Bhushan@nxp.com>,
        Eric Auger <eric.auger@redhat.com>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, kernel-janitors@vger.kernel.org
Subject: [PATCH 1/2] vfio/fsl-mc: return -EFAULT if copy_to_user() fails
Message-ID: <20201023113450.GH282278@mwanda>
MIME-Version: 1.0
Content-Disposition: inline
X-Mailer: git-send-email haha only kidding
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9782
 signatures=668682
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 adultscore=0
 mlxscore=0 phishscore=0
 malwarescore=0 spamscore=0 suspectscore=0 bulkscore=0 mlxlogscore=999
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2010230081
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9782
 signatures=668682
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=0
 priorityscore=1501
 clxscore=1011 malwarescore=0 mlxscore=0 bulkscore=0 lowpriorityscore=0
 phishscore=0 adultscore=0 mlxlogscore=999 impostorscore=0 spamscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2010230082
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The copy_to_user() function returns the number of bytes remaining to be
copied, but this code should return -EFAULT.

Fixes: df747bcd5b21 ("vfio/fsl-mc: Implement VFIO_DEVICE_GET_REGION_INFO ioctl call")
Signed-off-by: Dan Carpenter <dan.carpenter@oracle.com>
Acked-by: Diana Craciun <diana.craciun@oss.nxp.com>
---
 drivers/vfio/fsl-mc/vfio_fsl_mc.c | 8 ++++++--
 1 file changed, 6 insertions(+), 2 deletions(-)

```
#### [PATCH 1/3] sched: better handling for busy polling loopsFrom: Josh Don <joshdon@google.com>
##### From: Josh Don <joshdon@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Josh Don <joshdon@google.com>
X-Patchwork-Id: 11852197
Return-Path: <SRS0=GVEW=D6=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-20.4 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=unavailable autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 93C2FC56201
	for <kvm@archiver.kernel.org>; Fri, 23 Oct 2020 03:30:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 234B22177B
	for <kvm@archiver.kernel.org>; Fri, 23 Oct 2020 03:30:22 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="i4wG/gwo"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S374825AbgJWDaS (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 22 Oct 2020 23:30:18 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:40688 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S374803AbgJWDaR (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 22 Oct 2020 23:30:17 -0400
Received: from mail-pl1-x649.google.com (mail-pl1-x649.google.com
 [IPv6:2607:f8b0:4864:20::649])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 740CDC0613D2
        for <kvm@vger.kernel.org>; Thu, 22 Oct 2020 20:30:16 -0700 (PDT)
Received: by mail-pl1-x649.google.com with SMTP id 88so168582pla.1
        for <kvm@vger.kernel.org>; Thu, 22 Oct 2020 20:30:16 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:message-id:mime-version:subject:from:to:cc;
        bh=1nY3WP57swg6MAG4MDM8yKEtar1GITDnzwO2HHJz44U=;
        b=i4wG/gwoPmGRZ6Mpz8QxDdp67CljbBwZPYy9aiHWtHbg4Yjk2zTjT5HniN2uRl+Qxv
         gRv7AZgHdFg7vtaVzteuxIsZ/JmDzxnbuP6QEPQaJ9wOrJzESY9tyUgJ1m1pBv21m8KJ
         hgT/1Ff73GDCmmnlabp4ozlnhXfW2f2muaShGzYcrkSkxd39qeaafQvRriM73XFnEuTY
         Jcj50rqDVJPXGgZGvLAUuVxwweSabtVnQxF6wPoKxc/BsejfXtcXgHUaOghv3xYhkdnr
         OsH4XdW+IsmDTCun6KJ5XbRjdwMI/OaApRCKkvVa5ZK3l3OfQKTuBJHfqLChyZMhXTlL
         ShPA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:message-id:mime-version:subject:from
         :to:cc;
        bh=1nY3WP57swg6MAG4MDM8yKEtar1GITDnzwO2HHJz44U=;
        b=ExCSZW1orepsY7+Hmm6pSstHuRxv75oK6QrKzYfg39Vrgoxoe9H5GJK1umd7pkzD/7
         iWzFGet70Aja95mSpuGJ+UDbLox0Jdvbs9txkfgENeojGIFElDbQ0PhRxib8eZBXBSfw
         Nl+F8NZxu1HsUfMFGiIg2CGCvd+zMD5lFUXVjwj/xE0Yi24Dj2AeJSLeqcMQf8epxVUi
         1oXa253HacgO5Hlz4IDr/MfI6JT7FSA3Eqgycr6OZgGDvppQeGZOpIjt9azEM3FLAkKy
         NDnijBLQ5vpUXhX7sDtBvMRDEoQeQ4lPLdNX/ixXQsKS3IqBCafLTJb14EQoPPzW4U1u
         z8pw==
X-Gm-Message-State: AOAM5323CzrxtxR74Fta3Ai4enCFvUwfi1QtRbwineu4l8RXrHS4B1rA
        9Bsi2ZFuSskRpYb6S3VJpd/iSTfHQ/7r
X-Google-Smtp-Source: 
 ABdhPJzQxmKmCLQEWloUtqGTBdjOj0/OiTQmKmDlMAVk1e0OUR2bLkyYPhuESGhvRCGjWYhVdmZxT/FuxztA
Sender: "joshdon via sendgmr" <joshdon@joshdon.svl.corp.google.com>
X-Received: from joshdon.svl.corp.google.com
 ([2620:15c:2cd:202:a28c:fdff:fee1:cc86])
 (user=joshdon job=sendgmr) by 2002:a05:6a00:8c5:b029:142:2501:39e6 with SMTP
 id s5-20020a056a0008c5b0290142250139e6mr184421pfu.53.1603423815689; Thu, 22
 Oct 2020 20:30:15 -0700 (PDT)
Date: Thu, 22 Oct 2020 20:29:42 -0700
Message-Id: <20201023032944.399861-1-joshdon@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.29.0.rc1.297.gfa9743e501-goog
Subject: [PATCH 1/3] sched: better handling for busy polling loops
From: Josh Don <joshdon@google.com>
To: Ingo Molnar <mingo@redhat.com>,
        Peter Zijlstra <peterz@infradead.org>,
        Juri Lelli <juri.lelli@redhat.com>,
        Vincent Guittot <vincent.guittot@linaro.org>,
        "David S. Miller" <davem@davemloft.net>,
        Jakub Kicinski <kuba@kernel.org>
Cc: Dietmar Eggemann <dietmar.eggemann@arm.com>,
        Steven Rostedt <rostedt@goodmis.org>,
        Ben Segall <bsegall@google.com>, Mel Gorman <mgorman@suse.de>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Eric Dumazet <edumazet@google.com>,
        linux-kernel@vger.kernel.org, netdev@vger.kernel.org,
        kvm@vger.kernel.org, Josh Don <joshdon@google.com>,
        Xi Wang <xii@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Busy polling loops in the kernel such as network socket poll and kvm
halt polling have performance problems related to process scheduler load
accounting.

Both of the busy polling examples are opportunistic - they relinquish
the cpu if another thread is ready to run. This design, however, doesn't
extend to multiprocessor load balancing very well. The scheduler still
sees the busy polling cpu as 100% busy and will be less likely to put
another thread on that cpu. In other words, if all cores are 100%
utilized and some of them are running real workloads and some others are
running busy polling loops, newly woken up threads will not prefer the
busy polling cpus. System wide throughput and latency may suffer.

This change allows the scheduler to detect busy polling cpus in order to
allow them to be more frequently considered for wake up balancing.

This change also disables preemption for the duration of the busy
polling loop. This is important, as it ensures that if a polling thread
decides to end its poll to relinquish cpu to another thread, the polling
thread will actually exit the busy loop and potentially block. When it
later becomes runnable, it will have the opportunity to find an idle cpu
via wakeup cpu selection.

Suggested-by: Xi Wang <xii@google.com>
Signed-off-by: Josh Don <joshdon@google.com>
Signed-off-by: Xi Wang <xii@google.com>
---
 include/linux/sched.h |  5 +++
 kernel/sched/core.c   | 94 +++++++++++++++++++++++++++++++++++++++++++
 kernel/sched/fair.c   | 25 ++++++++----
 kernel/sched/sched.h  |  2 +
 4 files changed, 119 insertions(+), 7 deletions(-)

```
#### [PATCH 39/65] vfio/type1: Mark follow_pfn as unsafe
##### From: Daniel Vetter <daniel.vetter@ffwll.ch>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Daniel Vetter <daniel.vetter@ffwll.ch>
X-Patchwork-Id: 11853041
Return-Path: <SRS0=GVEW=D6=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 02DCFC8301E
	for <kvm@archiver.kernel.org>; Fri, 23 Oct 2020 12:23:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A79C324673
	for <kvm@archiver.kernel.org>; Fri, 23 Oct 2020 12:23:13 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=ffwll.ch header.i=@ffwll.ch
 header.b="URbjYqZv"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S463656AbgJWMXM (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 23 Oct 2020 08:23:12 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:38062 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S463684AbgJWMXL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 23 Oct 2020 08:23:11 -0400
Received: from mail-wm1-x342.google.com (mail-wm1-x342.google.com
 [IPv6:2a00:1450:4864:20::342])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id CB6B1C0613D5
        for <kvm@vger.kernel.org>; Fri, 23 Oct 2020 05:23:09 -0700 (PDT)
Received: by mail-wm1-x342.google.com with SMTP id w23so143699wmi.4
        for <kvm@vger.kernel.org>; Fri, 23 Oct 2020 05:23:09 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=ffwll.ch; s=google;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=hp7lChw6Uow+58XPniSHemIeAoNErbB/sdK6im80Iug=;
        b=URbjYqZvij6vMp6zpIk/3WlniapSCelkh8qPhM9XSJmSi3JP0Pkq6JfYZq+gC0V2Ja
         Jq8vCQ4Ho/GAm6SQXrzJhiajzuA2XAwJXKB1Cll6tMyrVwJYz4NCmG2PdfE0KkUS7bh0
         l5/AnqPDLrJU4JyaIv3jCsFac60g5JtxDcFVQ=
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=hp7lChw6Uow+58XPniSHemIeAoNErbB/sdK6im80Iug=;
        b=UDfLGuZIm+rEuav9S7wAb8ozt1Pzuyw94nq4qFZ4V4A5z56D+dCM/bmTpt3LRzIQ1O
         nBNyPmZnsHs/xtMre+t3CxBbIr8OtKs+sHXJWoi7wJlckxjHKrVhMN6RIiOQNGAKdIrC
         Gaua9fDIsHvqfp7ZIpPBgeBFxRTIFZYXyXKG3Fsb6yPz9Go0YwnfxkAUv4tv2Ru8VbIM
         +KD9s9WlchChBU/CclfX57kBaYpoKVVr4LR7wy+z38aRMFi04dATo+2zPTXYj/lIHguM
         n+1zyFUQV2BmLmyYRHKgRJzeSm7oNLm6TFcwFNmVDJwhlo8jVyMkr5Y+FiOFAhzfVeGv
         qbAg==
X-Gm-Message-State: AOAM5319xPSTNfmpOuTeXmhCPdDhdftL5ldZ8GPsWfyReWPtmIl5wjhY
        l2d4wAZJzTDA4Vo3FQ1p7XL5yg==
X-Google-Smtp-Source: 
 ABdhPJwqZWBmXRQ8vY8ZKJrjdPXGP2WILf15a1TrVl8Pgis8iT7Odd2hX51Nk7fKP5ClvyukHiQ2vg==
X-Received: by 2002:a1c:4d05:: with SMTP id o5mr1994877wmh.94.1603455788583;
        Fri, 23 Oct 2020 05:23:08 -0700 (PDT)
Received: from phenom.ffwll.local ([2a02:168:57f4:0:efd0:b9e5:5ae6:c2fa])
        by smtp.gmail.com with ESMTPSA id
 y4sm3056484wrp.74.2020.10.23.05.23.07
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 23 Oct 2020 05:23:08 -0700 (PDT)
From: Daniel Vetter <daniel.vetter@ffwll.ch>
To: DRI Development <dri-devel@lists.freedesktop.org>
Cc: Intel Graphics Development <intel-gfx@lists.freedesktop.org>,
 Daniel Vetter <daniel.vetter@ffwll.ch>,
 Daniel Vetter <daniel.vetter@intel.com>, Jason Gunthorpe <jgg@ziepe.ca>,
 Kees Cook <keescook@chromium.org>, Dan Williams <dan.j.williams@intel.com>,
 Andrew Morton <akpm@linux-foundation.org>,
 John Hubbard <jhubbard@nvidia.com>,
 =?utf-8?b?SsOpcsO0bWUgR2xpc3Nl?= <jglisse@redhat.com>,
 Jan Kara <jack@suse.cz>, linux-mm@kvack.org,
 linux-arm-kernel@lists.infradead.org, linux-samsung-soc@vger.kernel.org,
 linux-media@vger.kernel.org, Alex Williamson <alex.williamson@redhat.com>,
 Cornelia Huck <cohuck@redhat.com>, kvm@vger.kernel.org
Subject: [PATCH 39/65] vfio/type1: Mark follow_pfn as unsafe
Date: Fri, 23 Oct 2020 14:21:50 +0200
Message-Id: <20201023122216.2373294-39-daniel.vetter@ffwll.ch>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20201023122216.2373294-1-daniel.vetter@ffwll.ch>
References: <20201021163242.1458885-1-daniel.vetter@ffwll.ch>
 <20201023122216.2373294-1-daniel.vetter@ffwll.ch>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The code seems to stuff these pfns into iommu pts (or something like
that, I didn't follow), but there's no mmu_notifier to ensure that
access is synchronized with pte updates.

Hence mark these as unsafe. This means that with
CONFIG_STRICT_FOLLOW_PFN, these will be rejected.

Real fix is to wire up an mmu_notifier ... somehow. Probably means any
invalidate is a fatal fault for this vfio device, but then this
shouldn't ever happen if userspace is reasonable.

Signed-off-by: Daniel Vetter <daniel.vetter@intel.com>
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
Cc: Alex Williamson <alex.williamson@redhat.com>
Cc: Cornelia Huck <cohuck@redhat.com>
Cc: kvm@vger.kernel.org
Signed-off-by: Daniel Vetter <daniel.vetter@ffwll.ch>
---
 drivers/vfio/vfio_iommu_type1.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH 37/65] mm: Add unsafe_follow_pfn
##### From: Daniel Vetter <daniel.vetter@ffwll.ch>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Daniel Vetter <daniel.vetter@ffwll.ch>
X-Patchwork-Id: 11853043
Return-Path: <SRS0=GVEW=D6=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 055E4C83018
	for <kvm@archiver.kernel.org>; Fri, 23 Oct 2020 12:23:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A872324631
	for <kvm@archiver.kernel.org>; Fri, 23 Oct 2020 12:23:10 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=ffwll.ch header.i=@ffwll.ch
 header.b="K0cS0ybR"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S463682AbgJWMXJ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 23 Oct 2020 08:23:09 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:38042 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S463674AbgJWMXI (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 23 Oct 2020 08:23:08 -0400
Received: from mail-wr1-x444.google.com (mail-wr1-x444.google.com
 [IPv6:2a00:1450:4864:20::444])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 29A8AC0613D2
        for <kvm@vger.kernel.org>; Fri, 23 Oct 2020 05:23:07 -0700 (PDT)
Received: by mail-wr1-x444.google.com with SMTP id x7so1596460wrl.3
        for <kvm@vger.kernel.org>; Fri, 23 Oct 2020 05:23:07 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=ffwll.ch; s=google;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=Jw8O4zHShCAt4bi/mdSwE8pqaQ/Ci7nnAmM3jj6tKas=;
        b=K0cS0ybRn+oowL57X6Nq5A66q23biV6d8Mh7nGNYpraDsikoql8NXlqFHPQVPGQZEq
         ZhmiEFHW8LcIIsLLB04p9O5em1Gy5Y5hrhfhfjs2YroaC/WrwZiQyslSzwbv6NtWleY1
         RjNBNdVMAomvkHW50DBDpEmjI0t0ipkA/M7JE=
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=Jw8O4zHShCAt4bi/mdSwE8pqaQ/Ci7nnAmM3jj6tKas=;
        b=mr09M3sV2o60taZtwg4ooyMnEx6DZ4NnPQAtf7uqrBoF8vIveujOgXzMbAa9pcZZFg
         7znH0pQBXvV+k8uHitPHYPDgo8zWlBdZX0lnp6SWyph0biqlf+SzQv3qrcTZIPNAEzqy
         ufrATjFEmzxoABePfGrtXGOqmFsjzkXxbxHIuUqBGwSGBOuI447lgaDbvncjhFy1pHrv
         1VDsS7joxXFHvkWaj8DdHjx82h6p3Sr+K1wmzjbwn7pm4egCPsN34YNmi6nM/HSox5j1
         H+WcOWAa6GhDy7i7fQNpP+ot/dNpabAQT+AiL99wZCxS/ZsKkV3sWUZfs6hBysVIABlR
         w2hA==
X-Gm-Message-State: AOAM533IueFCHlTKLOXch/8kGJBts5H8anww8xMVCsQD6bogEkAxxp0L
        yKB8IIj7znTxy96y4UNDRzc5lA==
X-Google-Smtp-Source: 
 ABdhPJyHNrzVnBA/1XZbDotdv4KJ/xMo2zJVR986ilnB2l49QrGJnJFipT6hqx9IUcARiSC9qfVVjQ==
X-Received: by 2002:a5d:6551:: with SMTP id z17mr2352471wrv.266.1603455785885;
        Fri, 23 Oct 2020 05:23:05 -0700 (PDT)
Received: from phenom.ffwll.local ([2a02:168:57f4:0:efd0:b9e5:5ae6:c2fa])
        by smtp.gmail.com with ESMTPSA id
 y4sm3056484wrp.74.2020.10.23.05.23.04
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 23 Oct 2020 05:23:05 -0700 (PDT)
From: Daniel Vetter <daniel.vetter@ffwll.ch>
To: DRI Development <dri-devel@lists.freedesktop.org>
Cc: Intel Graphics Development <intel-gfx@lists.freedesktop.org>,
 Daniel Vetter <daniel.vetter@ffwll.ch>,
 Daniel Vetter <daniel.vetter@intel.com>, Jason Gunthorpe <jgg@ziepe.ca>,
 Kees Cook <keescook@chromium.org>, Dan Williams <dan.j.williams@intel.com>,
 Andrew Morton <akpm@linux-foundation.org>,
 John Hubbard <jhubbard@nvidia.com>,
 =?utf-8?b?SsOpcsO0bWUgR2xpc3Nl?= <jglisse@redhat.com>,
 Jan Kara <jack@suse.cz>, linux-mm@kvack.org,
 linux-arm-kernel@lists.infradead.org, linux-samsung-soc@vger.kernel.org,
 linux-media@vger.kernel.org, kvm@vger.kernel.org
Subject: [PATCH 37/65] mm: Add unsafe_follow_pfn
Date: Fri, 23 Oct 2020 14:21:48 +0200
Message-Id: <20201023122216.2373294-37-daniel.vetter@ffwll.ch>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20201023122216.2373294-1-daniel.vetter@ffwll.ch>
References: <20201021163242.1458885-1-daniel.vetter@ffwll.ch>
 <20201023122216.2373294-1-daniel.vetter@ffwll.ch>
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

Signed-off-by: Daniel Vetter <daniel.vetter@intel.com>
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
 include/linux/mm.h |  2 ++
 mm/memory.c        | 32 +++++++++++++++++++++++++++++++-
 mm/nommu.c         | 17 +++++++++++++++++
 security/Kconfig   | 13 +++++++++++++
 4 files changed, 63 insertions(+), 1 deletion(-)

```
#### [GIT PULL] vhost,vdpa,virtio: cleanups, fixes
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 11853683
Return-Path: <SRS0=GVEW=D6=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.9 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PULL_REQUEST,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E7822C4363A
	for <kvm@archiver.kernel.org>; Fri, 23 Oct 2020 15:39:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8778620E65
	for <kvm@archiver.kernel.org>; Fri, 23 Oct 2020 15:39:03 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="ato4djox"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1750933AbgJWPjC (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 23 Oct 2020 11:39:02 -0400
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:39770 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1750909AbgJWPjB (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 23 Oct 2020 11:39:01 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1603467539;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type;
        bh=J409roG8zhXcXXCErK007R3MrYblBFNCZHcPyX0EW1c=;
        b=ato4djoxJfdL0DPdufQLUuA2IuDBu0X8yUSJyklvDkNC6173YgfMrb8eJggCJjth2SQWkM
        X8oija8Vnn9wN8n8oxEfeN5QNNaZY0NDcsm/k5flYvWWPYxf0sE3w/6DgmjuTF3juHA0JO
        wlB54QYgwWpzWbEi7i5wcSqJR7F0rmw=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-190-WxrfRJEEOtWeuf0CbspCdA-1; Fri, 23 Oct 2020 11:38:56 -0400
X-MC-Unique: WxrfRJEEOtWeuf0CbspCdA-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id B8F7E80400B;
        Fri, 23 Oct 2020 15:38:53 +0000 (UTC)
Received: from redhat.com (ovpn-113-117.ams2.redhat.com [10.36.113.117])
        by smtp.corp.redhat.com (Postfix) with ESMTPS id 948346EF5D;
        Fri, 23 Oct 2020 15:38:34 +0000 (UTC)
Date: Fri, 23 Oct 2020 11:38:32 -0400
From: "Michael S. Tsirkin" <mst@redhat.com>
To: Linus Torvalds <torvalds@linux-foundation.org>
Cc: kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org, linux-kernel@vger.kernel.org,
        borntraeger@de.ibm.com, david@redhat.com, elic@nvidia.com,
        jasowang@redhat.com, lingshan.zhu@intel.com, li.wang@windriver.com,
        mst@redhat.com, pankaj.gupta.linux@gmail.com, pmorel@linux.ibm.com,
        rikard.falkeborn@gmail.com, sgarzare@redhat.com,
        stable@vger.kernel.org, tiantao6@hisilicon.com
Subject: [GIT PULL] vhost,vdpa,virtio: cleanups, fixes
Message-ID: <20201023113832-mutt-send-email-mst@kernel.org>
MIME-Version: 1.0
Content-Disposition: inline
X-Mutt-Fcc: =sent
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Was holding out for a couple of big new features including vop and rpmsg
support for 1.0, but it looks like they won't make it in time.
virtio i2c might be ready soon but that's a new driver so
if it's ready soon it's probably ok to merge outside the merge
window ... we'll see.

The following changes since commit bbf5c979011a099af5dc76498918ed7df445635b:

  Linux 5.9 (2020-10-11 14:15:50 -0700)

are available in the Git repository at:

  https://git.kernel.org/pub/scm/linux/kernel/git/mst/vhost.git tags/for_linus

for you to fetch changes up to 88a0d60c6445f315fbcfff3db792021bb3a67b28:

  MAINTAINERS: add URL for virtio-mem (2020-10-21 10:48:11 -0400)

----------------------------------------------------------------
vhost,vdpa,virtio: cleanups, fixes

A very quiet cycle, no new features.

Signed-off-by: Michael S. Tsirkin <mst@redhat.com>

----------------------------------------------------------------
David Hildenbrand (1):
      MAINTAINERS: add URL for virtio-mem

Eli Cohen (3):
      vdpa/mlx5: Make use of a specific 16 bit endianness API
      vdpa/mlx5: Fix failure to bring link up
      vdpa/mlx5: Setup driver only if VIRTIO_CONFIG_S_DRIVER_OK

Li Wang (1):
      vhost: reduce stack usage in log_used

Pierre Morel (2):
      virtio: let arch advertise guest's memory access restrictions
      s390: virtio: PV needs VIRTIO I/O device protection

Rikard Falkeborn (3):
      virtio-balloon: Constify id_table
      virtio_input: Constify id_table
      virtio-mem: Constify mem_id_table

Stefano Garzarella (1):
      vringh: fix __vringh_iov() when riov and wiov are different

Tian Tao (1):
      vhost_vdpa: Fix duplicate included kernel.h

Zhu Lingshan (1):
      vhost_vdpa: remove unnecessary spin_lock in vhost_vring_call

 MAINTAINERS                       |  1 +
 arch/s390/Kconfig                 |  1 +
 arch/s390/mm/init.c               | 11 +++++++++++
 drivers/vdpa/mlx5/net/mlx5_vnet.c | 12 ++++++++++--
 drivers/vhost/vdpa.c              |  9 +--------
 drivers/vhost/vhost.c             |  5 +----
 drivers/vhost/vhost.h             |  2 +-
 drivers/vhost/vringh.c            |  9 +++++----
 drivers/virtio/Kconfig            |  6 ++++++
 drivers/virtio/virtio.c           | 15 +++++++++++++++
 drivers/virtio/virtio_balloon.c   |  2 +-
 drivers/virtio/virtio_input.c     |  2 +-
 drivers/virtio/virtio_mem.c       |  2 +-
 include/linux/virtio_config.h     | 10 ++++++++++
 14 files changed, 65 insertions(+), 22 deletions(-)
```
#### [PATCH 01/22] kvm: mmu: Separate making non-leaf sptes from link_shadow_page
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11854019
Return-Path: <SRS0=GVEW=D6=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-9.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 1EC40C388F9
	for <kvm@archiver.kernel.org>; Fri, 23 Oct 2020 16:32:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BE15C221F9
	for <kvm@archiver.kernel.org>; Fri, 23 Oct 2020 16:32:01 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Lmzy0GO/"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1751535AbgJWQae (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 23 Oct 2020 12:30:34 -0400
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:54642 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1751518AbgJWQad (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 23 Oct 2020 12:30:33 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1603470632;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=E+3IRJB6Q1/p5CmMrxkT9gnBU657hxEY63DzKc8Vg14=;
        b=Lmzy0GO/R7Qab7QilElPTjk/UEqjwbNlV/9BqFPIO8DeXTFXNw8Lb9XB+y9mj/bLAs38vJ
        qZ83oLECwN8Ds93Af/XVXhXSzMHNegwdbKqBLG/ZpOiZwOKiZ0qRxeEmd26hkZ8ws55OEI
        d+msXIyLsZwA0AJI76wcnzSyNMQ3euo=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-532-E-Q0nn2iM_atWqcOb2snhw-1; Fri, 23 Oct 2020 12:30:26 -0400
X-MC-Unique: E-Q0nn2iM_atWqcOb2snhw-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 66C39ADC3A;
        Fri, 23 Oct 2020 16:30:25 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 05FEF5DA78;
        Fri, 23 Oct 2020 16:30:24 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: bgardon@google.com
Subject: [PATCH 01/22] kvm: mmu: Separate making non-leaf sptes from
 link_shadow_page
Date: Fri, 23 Oct 2020 12:30:03 -0400
Message-Id: <20201023163024.2765558-2-pbonzini@redhat.com>
In-Reply-To: <20201023163024.2765558-1-pbonzini@redhat.com>
References: <20201023163024.2765558-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Ben Gardon <bgardon@google.com>

The TDP MMU page fault handler will need to be able to create non-leaf
SPTEs to build up the paging structures. Rather than re-implementing the
function, factor the SPTE creation out of link_shadow_page.

Tested by running kvm-unit-tests and KVM selftests on an Intel Haswell
machine. This series introduced no new failures.

This series can be viewed in Gerrit at:
	https://linux-review.googlesource.com/c/virt/kvm/kvm/+/2538

Signed-off-by: Ben Gardon <bgardon@google.com>
Message-Id: <20200925212302.3979661-9-bgardon@google.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/mmu/mmu.c | 21 +++++++++++++++------
 1 file changed, 15 insertions(+), 6 deletions(-)

```
#### [PATCH v15 01/14] KVM: Documentation: Update entry for KVM_X86_SET_MSR_FILTER
##### From: Peter Xu <peterx@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11854399
Return-Path: <SRS0=GVEW=D6=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.9 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id AF7CCC5517A
	for <kvm@archiver.kernel.org>; Fri, 23 Oct 2020 18:35:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5675720E65
	for <kvm@archiver.kernel.org>; Fri, 23 Oct 2020 18:35:45 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Xn/CXJbH"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1754830AbgJWSeH (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 23 Oct 2020 14:34:07 -0400
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:28185 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1754796AbgJWSeF (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 23 Oct 2020 14:34:05 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1603478044;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=f9RAo1p5Z3QHuNccDaVSZ9lEhBh3TGuTwN8hkmUR6Fw=;
        b=Xn/CXJbHQLDqvTwGjto5A2ieLmUwsxFkdov09erOIunRgDQM6cCnyowgDtOhkz7MznG0MX
        JA6LNgXJ2mTaakOxiyTPeYbkS/bjbjkUnPtjMn5Ht1lKFvIb9aHaDUq61DTBpCNZDc//gE
        Q6gZc1wGngLvB1spsQvUPo75RQOVoow=
Received: from mail-qv1-f71.google.com (mail-qv1-f71.google.com
 [209.85.219.71]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-218-ZjkYdkSuNL-7h7ecQesWmQ-1; Fri, 23 Oct 2020 14:34:02 -0400
X-MC-Unique: ZjkYdkSuNL-7h7ecQesWmQ-1
Received: by mail-qv1-f71.google.com with SMTP id k15so184074qvx.4
        for <kvm@vger.kernel.org>; Fri, 23 Oct 2020 11:34:02 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=f9RAo1p5Z3QHuNccDaVSZ9lEhBh3TGuTwN8hkmUR6Fw=;
        b=PllFPkD6vki9KjSEwU+PxtKxPL3hW+S5i29uHJpWgjDSzDfmKQYaIItHFb6zUYX3JY
         nr7NNh8/sqK85FaHM2ISQodzF+A7J9vYcGbt9OZH2ULX/tB1L513l8uQm5U1A3HEmIJY
         eXu4orsC63Jf965Nr5Xziv/0E4hl9DG9XkVqaV1Q9jgJ5+zIa4QsPagvABB/ynIfld0Z
         caS5/ZGsFeGcjEpZwLySNK/V9GiRMK2dL7900IfKlxiIpgdmK0MQRMpS6DQmZv2ikoYj
         l//kf8sp6kmVgUvjHVd9YwB7pxun866QdoAJkWKIuJdArWaZZ97aKciMTOPhBm1ZoWp2
         VHhg==
X-Gm-Message-State: AOAM532uVMXnBOc99HDig/hWzKR9elM1BX9CEFHHPI1oRIiIhnMPRhNp
        xQNfbYqADzMUpQGzegzu5VSISBrmJXQfgRs76KrOz8t9XZbLvite4yBMVY9SETOPVPsJdFe6u3N
        ue9l+Pr1Y9lh5
X-Received: by 2002:ac8:2f91:: with SMTP id l17mr3488387qta.252.1603478041961;
        Fri, 23 Oct 2020 11:34:01 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJyay/GTLlaHShgebWAWLZqPirAfvX+bQW7w7XUQEvI4fD7jH+bC1CjDWb2H2QxOTagrC/TUKA==
X-Received: by 2002:ac8:2f91:: with SMTP id l17mr3488368qta.252.1603478041747;
        Fri, 23 Oct 2020 11:34:01 -0700 (PDT)
Received: from xz-x1.redhat.com
 (toroon474qw-lp140-04-174-95-215-133.dsl.bell.ca. [174.95.215.133])
        by smtp.gmail.com with ESMTPSA id
 u11sm1490407qtk.61.2020.10.23.11.34.00
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 23 Oct 2020 11:34:01 -0700 (PDT)
From: Peter Xu <peterx@redhat.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        peterx@redhat.com, Andrew Jones <drjones@redhat.com>,
        "Dr . David Alan Gilbert" <dgilbert@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>
Subject: [PATCH v15 01/14] KVM: Documentation: Update entry for
 KVM_X86_SET_MSR_FILTER
Date: Fri, 23 Oct 2020 14:33:45 -0400
Message-Id: <20201023183358.50607-2-peterx@redhat.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20201023183358.50607-1-peterx@redhat.com>
References: <20201023183358.50607-1-peterx@redhat.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

It should be an accident when rebase, since we've already have section
8.25 (which is KVM_CAP_S390_DIAG318).  Fix the number.

Should be squashed into 1a155254ff937ac92cf9940d.

Signed-off-by: Peter Xu <peterx@redhat.com>
---
 Documentation/virt/kvm/api.rst | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH net] vhost_vdpa: Return -EFUALT if copy_from_user() fails
##### From: Dan Carpenter <dan.carpenter@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Dan Carpenter <dan.carpenter@oracle.com>
X-Patchwork-Id: 11852849
Return-Path: <SRS0=GVEW=D6=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-9.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,
	UNPARSEABLE_RELAY autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E295EC55179
	for <kvm@archiver.kernel.org>; Fri, 23 Oct 2020 12:09:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8991720EDD
	for <kvm@archiver.kernel.org>; Fri, 23 Oct 2020 12:09:09 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="g/GRiX9j"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S463451AbgJWMJH (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 23 Oct 2020 08:09:07 -0400
Received: from aserp2130.oracle.com ([141.146.126.79]:46530 "EHLO
        aserp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S463180AbgJWMJH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 23 Oct 2020 08:09:07 -0400
Received: from pps.filterd (aserp2130.oracle.com [127.0.0.1])
        by aserp2130.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 09NC5Au7095975;
        Fri, 23 Oct 2020 12:09:03 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=date : from : to : cc
 : subject : message-id : mime-version : content-type; s=corp-2020-01-29;
 bh=3u747VZC52iNeeNmOWRTKOGyZ8opg2btTPcZQUCsvGw=;
 b=g/GRiX9jjXejYbgaoQuSWf8mDKwf1QHkoc/k3V5GOM3mCrZ6r+su6cuS6jETcHwiCNdy
 T5lClorzd8RKcR0ifgboclLHVtg9aevcQqyI704DhbSq3Z6jH6H4jf9nSTa435BePGfK
 GKPsQivycYyys7T5j+4VixT+JP7JKgJ7MHFAJwv4LezfTxxPfb06pDDbar2Lp5dPHqDO
 1CLFnXX31cIlaqUVNLRxBQFGjy1P9wY6hYwfDvLLVQwtq+eVz6fbZuu388iTknY3lnY5
 c0nxcgHMCi4vaKMhyKDU/B74Xs2psh1yLMyP+gPOlNNnntABNohMFXcOYy9SP0JnjGPe qg==
Received: from userp3030.oracle.com (userp3030.oracle.com [156.151.31.80])
        by aserp2130.oracle.com with ESMTP id 347p4bavxq-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=FAIL);
        Fri, 23 Oct 2020 12:09:03 +0000
Received: from pps.filterd (userp3030.oracle.com [127.0.0.1])
        by userp3030.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 09NC558Y104567;
        Fri, 23 Oct 2020 12:09:02 GMT
Received: from aserv0121.oracle.com (aserv0121.oracle.com [141.146.126.235])
        by userp3030.oracle.com with ESMTP id 348aj0wyb3-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 23 Oct 2020 12:09:02 +0000
Received: from abhmp0017.oracle.com (abhmp0017.oracle.com [141.146.116.23])
        by aserv0121.oracle.com (8.14.4/8.13.8) with ESMTP id 09NC9099026344;
        Fri, 23 Oct 2020 12:09:01 GMT
Received: from mwanda (/41.57.98.10)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Fri, 23 Oct 2020 05:08:59 -0700
Date: Fri, 23 Oct 2020 15:08:53 +0300
From: Dan Carpenter <dan.carpenter@oracle.com>
To: "Michael S. Tsirkin" <mst@redhat.com>,
        Jason Wang <jasowang@redhat.com>
Cc: kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org, kernel-janitors@vger.kernel.org
Subject: [PATCH net] vhost_vdpa: Return -EFUALT if copy_from_user() fails
Message-ID: <20201023120853.GI282278@mwanda>
MIME-Version: 1.0
Content-Disposition: inline
X-Mailer: git-send-email haha only kidding
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9782
 signatures=668682
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 adultscore=0
 phishscore=0 bulkscore=0
 malwarescore=0 spamscore=0 mlxlogscore=999 mlxscore=0 suspectscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2010230086
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9782
 signatures=668682
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=0
 priorityscore=1501
 clxscore=1015 malwarescore=0 mlxscore=0 bulkscore=0 lowpriorityscore=0
 phishscore=0 adultscore=0 mlxlogscore=999 impostorscore=0 spamscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2010230086
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The copy_to/from_user() functions return the number of bytes which we
weren't able to copy but the ioctl should return -EFAULT if they fail.

Fixes: a127c5bbb6a8 ("vhost-vdpa: fix backend feature ioctls")
Signed-off-by: Dan Carpenter <dan.carpenter@oracle.com>
Acked-by: Michael S. Tsirkin <mst@redhat.com>
Acked-by: Jason Wang <jasowang@redhat.com>
---
 drivers/vhost/vdpa.c | 10 +++++-----
 1 file changed, 5 insertions(+), 5 deletions(-)

```
