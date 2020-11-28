

#### [PATCH 0/2] KVM: x86: cleanup and fix userspace interrupt window
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
From patchwork Fri Nov 27 11:21:12 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11935561
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-10.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7ECB6C64E7B
	for <kvm@archiver.kernel.org>; Fri, 27 Nov 2020 11:21:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0F7B520B80
	for <kvm@archiver.kernel.org>; Fri, 27 Nov 2020 11:21:36 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="FjJbbtbN"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729450AbgK0LVW (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 27 Nov 2020 06:21:22 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:52194 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1729250AbgK0LVV (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 27 Nov 2020 06:21:21 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1606476080;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=TFopWmrISNwds4exxKn1UKy4OMpKOwgTBLOgK+CrW5U=;
        b=FjJbbtbNapn03UseK1BGAesbhIyFkOf+/JLrnwbgwvEaNzm9W1H7kT7+eqZWOgYYVUd6wN
        4GgQoGahjPTBB5HZfH+1tzIDwn/AI2SNM+nEcDjqyuaLQ30eyTAmsJVlgEPr8XPSdu5KQt
        XH0I9CB3e+uNHiwQVy0jIwc1jUtIiJI=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-517-c1VOEJhHMfGykp8joBBrvw-1; Fri, 27 Nov 2020 06:21:16 -0500
X-MC-Unique: c1VOEJhHMfGykp8joBBrvw-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 1408F1006C96;
        Fri, 27 Nov 2020 11:21:15 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 8D09C5D6D1;
        Fri, 27 Nov 2020 11:21:14 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: seanjc@google.com, Filippo Sironi <sironi@amazon.de>
Subject: [PATCH 0/2] KVM: x86: cleanup and fix userspace interrupt window
Date: Fri, 27 Nov 2020 06:21:12 -0500
Message-Id: <20201127112114.3219360-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is my take on the split irqchip bug that David reported.  It's a
much more complicated patch, but I think it really gets to the bottom
of the issue and the code is clearer.

Paolo

Paolo Bonzini (2):
  KVM: x86: handle !lapic_in_kernel case in kvm_cpu_*_extint
  KVM: x86: Fix split-irqchip vs interrupt injection window request

 arch/x86/include/asm/kvm_host.h |  1 +
 arch/x86/kvm/irq.c              | 87 +++++++++++++--------------------
 arch/x86/kvm/lapic.c            |  2 +-
 arch/x86/kvm/x86.c              | 17 +++----
 4 files changed, 44 insertions(+), 63 deletions(-)
Reviewed-by: David Woodhouse <dwmw@amazon.co.uk>
Tested-by: David Woodhouse <dwmw@amazon.co.uk>
```
#### [kvm-unit-tests PATCH v2 0/7] s390x: Add SIE library and simple test
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
From patchwork Fri Nov 27 13:06:22 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11936277
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 10911C2D0E4
	for <kvm@archiver.kernel.org>; Fri, 27 Nov 2020 13:06:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A456620B80
	for <kvm@archiver.kernel.org>; Fri, 27 Nov 2020 13:06:55 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="ACjp2fPe"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729939AbgK0NGj (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 27 Nov 2020 08:06:39 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:14712 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1729913AbgK0NGj (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 27 Nov 2020 08:06:39 -0500
Received: from pps.filterd (m0098416.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 0ARCWTvs043296;
        Fri, 27 Nov 2020 08:06:38 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=Xy817aY861S7OaNIC59NI4hXOCA0DA3HMYWO4B/cY/I=;
 b=ACjp2fPeeaAD03RPnUrEGqJ8byrDL8DLPByiQQTGb5h/SyhbbaIrMcTPkFMe1TTRGNBM
 2Jl7KWNQ99FWPOJXZ8rJoGzxA9b3+zICeoWTdm+mAwaKxx/7Lsqel5vrBiiFfQvEIfs9
 /LmgYGCLnRD0gGiSJFN1hm80JvMrYvHhBihONSikiYA0/sWWVCVoqvOcVw0wT3tBUv6Q
 6FM+jXMguWCUl1lLEADrz1yxvhloUz0+cenn5DjeBavzS8lgIwLpJJ2XhGrB166VW4E1
 BEe6zE5y7GyX2bM7BJs2bYrg0zNETQKpm5811iDWpQO1vzEqkAUdbxnn9C8v4YYhYsVx ag==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 352y94vrr4-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 27 Nov 2020 08:06:38 -0500
Received: from m0098416.ppops.net (m0098416.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 0ARCZA26056085;
        Fri, 27 Nov 2020 08:06:37 -0500
Received: from ppma04ams.nl.ibm.com (63.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.99])
        by mx0b-001b2d01.pphosted.com with ESMTP id 352y94vrqg-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 27 Nov 2020 08:06:37 -0500
Received: from pps.filterd (ppma04ams.nl.ibm.com [127.0.0.1])
        by ppma04ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 0ARCRVSr006449;
        Fri, 27 Nov 2020 13:06:36 GMT
Received: from b06cxnps3075.portsmouth.uk.ibm.com
 (d06relay10.portsmouth.uk.ibm.com [9.149.109.195])
        by ppma04ams.nl.ibm.com with ESMTP id 3518j8jnwc-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 27 Nov 2020 13:06:36 +0000
Received: from d06av22.portsmouth.uk.ibm.com (d06av22.portsmouth.uk.ibm.com
 [9.149.105.58])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 0ARD6XZ147579538
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 27 Nov 2020 13:06:33 GMT
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 24AC94C063;
        Fri, 27 Nov 2020 13:06:33 +0000 (GMT)
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 5F0F14C076;
        Fri, 27 Nov 2020 13:06:32 +0000 (GMT)
Received: from linux01.pok.stglabs.ibm.com (unknown [9.114.17.81])
        by d06av22.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Fri, 27 Nov 2020 13:06:32 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: thuth@redhat.com, david@redhat.com, borntraeger@de.ibm.com,
        imbrenda@linux.ibm.com, cohuck@redhat.com,
        linux-s390@vger.kernel.org
Subject: [kvm-unit-tests PATCH v2 0/7] s390x: Add SIE library and simple test
Date: Fri, 27 Nov 2020 08:06:22 -0500
Message-Id: <20201127130629.120469-1-frankja@linux.ibm.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.312,18.0.737
 definitions=2020-11-27_06:2020-11-26,2020-11-27 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxscore=0 priorityscore=1501
 clxscore=1015 mlxlogscore=980 impostorscore=0 lowpriorityscore=0
 malwarescore=0 bulkscore=0 phishscore=0 adultscore=0 spamscore=0
 suspectscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2011270076
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is the absolute minimum needed to run VMs inside the KVM Unit
Tests. It's more of a base for other tests that I can't (yet) publish
than an addition of tests that check KVM functionality. However, I
wanted to decrease the number of WIP patches in my private
branch. Once the library is available maybe others will come and
extend the SIE test itself.

Yes, I have added VM management functionality like VM create/destroy,
etc but as it is not needed right now, I'd like to exclude it from
this patch set for now.

Gitlab:
https://gitlab.com/frankja/kvm-unit-tests/-/tree/sie

CI:
https://gitlab.com/frankja/kvm-unit-tests/-/pipelines/222217716

v2:
	* Added license and source identifiers to test_bit patch
	* Changed the way I test for sclp feature bits
	* Removed the cpu info page itself and all references
	* Added the diag318 and a sclp.h style fix patch

Janosch Frank (7):
  s390x: Add test_bit to library
  s390x: Consolidate sclp read info
  s390x: SCLP feature checking
  s390x: sie: Add SIE to lib
  s390x: sie: Add first SIE test
  s390x: Add diag318 intercept test
  s390x: Fix sclp.h style issues

 lib/s390x/asm-offsets.c  |  13 +++
 lib/s390x/asm/arch_def.h |   7 ++
 lib/s390x/asm/bitops.h   |  26 ++++++
 lib/s390x/asm/facility.h |   3 +-
 lib/s390x/interrupt.c    |   7 ++
 lib/s390x/io.c           |   2 +
 lib/s390x/sclp.c         |  50 ++++++++--
 lib/s390x/sclp.h         | 178 +++++++++++++++++++----------------
 lib/s390x/sie.h          | 197 +++++++++++++++++++++++++++++++++++++++
 lib/s390x/smp.c          |  28 +++---
 s390x/Makefile           |   1 +
 s390x/cstart64.S         |  56 +++++++++++
 s390x/intercept.c        |  19 ++++
 s390x/sie.c              | 125 +++++++++++++++++++++++++
 s390x/unittests.cfg      |   3 +
 15 files changed, 611 insertions(+), 104 deletions(-)
 create mode 100644 lib/s390x/sie.h
 create mode 100644 s390x/sie.c
```
#### [PATCH v7 00/17] follow_pfn and other iomap races
##### From: Daniel Vetter <daniel.vetter@ffwll.ch>

```c
From patchwork Fri Nov 27 16:41:14 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Daniel Vetter <daniel.vetter@ffwll.ch>
X-Patchwork-Id: 11936789
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 2C292C64E7A
	for <kvm@archiver.kernel.org>; Fri, 27 Nov 2020 16:42:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CC7C22224A
	for <kvm@archiver.kernel.org>; Fri, 27 Nov 2020 16:42:11 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=ffwll.ch header.i=@ffwll.ch
 header.b="jQ8QYtZG"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731505AbgK0Ql7 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 27 Nov 2020 11:41:59 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:54006 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1731405AbgK0Ql6 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 27 Nov 2020 11:41:58 -0500
Received: from mail-wm1-x343.google.com (mail-wm1-x343.google.com
 [IPv6:2a00:1450:4864:20::343])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 76E56C0613D4
        for <kvm@vger.kernel.org>; Fri, 27 Nov 2020 08:41:58 -0800 (PST)
Received: by mail-wm1-x343.google.com with SMTP id p22so5643369wmg.3
        for <kvm@vger.kernel.org>; Fri, 27 Nov 2020 08:41:58 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=ffwll.ch; s=google;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=ESkSp6C7mvKV6tnu0bv0a5NUd9H7UZA/j9+KxBk62a8=;
        b=jQ8QYtZGE95X+kQNlT31arGz3fYSGvIwxc8CIQGHUAFqEsxjgCe3vvJrRkP5zcoBFd
         kyw+1PRtr/v1Vnaw3uyD+fyAim2cfgkJDD5Q3S0vbKD9lObKqNzb5ybH/JvOzGAGkiei
         EIiVoJbv/O7eYs/rJVz+0K/a9SqrRGH8KrGbM=
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=ESkSp6C7mvKV6tnu0bv0a5NUd9H7UZA/j9+KxBk62a8=;
        b=Ek3kwYo0VnRzLiWsmf4opN61wYh04KlV2QEGlW7cIaFw323UlD078CMVn0XcdUf5HD
         nU649Yap8DCMrsoQ4Gr4K0fLYyEv9NFvNvAsknk+7sKqi+h9/z/ON1CB+gyxzEhH/KTc
         JeJRrGX6c527aqpgZ+ZlZa58LY1z9Anwg34TRdfML5akUpF8hc75a56AvCanjdNaKvDn
         FNif3zi/4/bXbRU7Y4psRukYZIiUaQa1QvYA6zFmRbJ6Hxo1/LsMO1o4oR99wrgWq4y0
         5q10Angjp2r5wt6pKtjvOzl15Tc4322m3BrIA9POAS/Djf5S8mu0PXtFTqO0AAsOeV57
         yqag==
X-Gm-Message-State: AOAM531k/so4+x2iUDkNrkyGVS8N7BvTZq07jT+rkymP3tHP5xYHTdyC
        KyYjtOZMiw2o6pWYUuQ9tLBQXA==
X-Google-Smtp-Source: 
 ABdhPJy6H3y4sUz3l7M4JNsS6NM9YkD0oMXLhvCp0ba6p25GYS5KJlvCz2mFh2Zqh4wJSE93buN0qg==
X-Received: by 2002:a1c:6a0d:: with SMTP id
 f13mr10199588wmc.172.1606495316997;
        Fri, 27 Nov 2020 08:41:56 -0800 (PST)
Received: from phenom.ffwll.local ([2a02:168:57f4:0:efd0:b9e5:5ae6:c2fa])
        by smtp.gmail.com with ESMTPSA id
 q12sm14859078wrx.86.2020.11.27.08.41.55
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 27 Nov 2020 08:41:56 -0800 (PST)
From: Daniel Vetter <daniel.vetter@ffwll.ch>
To: DRI Development <dri-devel@lists.freedesktop.org>,
        LKML <linux-kernel@vger.kernel.org>
Cc: kvm@vger.kernel.org, linux-mm@kvack.org,
        linux-arm-kernel@lists.infradead.org,
        linux-samsung-soc@vger.kernel.org, linux-media@vger.kernel.org,
        Daniel Vetter <daniel.vetter@ffwll.ch>
Subject: [PATCH v7 00/17] follow_pfn and other iomap races
Date: Fri, 27 Nov 2020 17:41:14 +0100
Message-Id: <20201127164131.2244124-1-daniel.vetter@ffwll.ch>
X-Mailer: git-send-email 2.29.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all

Another update of my patch series to clamp down a bunch of races and gaps
around follow_pfn and other access to iomem mmaps. Previous version:

v1: https://lore.kernel.org/dri-devel/20201007164426.1812530-1-daniel.vetter@ffwll.ch/
v2: https://lore.kernel.org/dri-devel/20201009075934.3509076-1-daniel.vetter@ffwll.ch
v3: https://lore.kernel.org/dri-devel/20201021085655.1192025-1-daniel.vetter@ffwll.ch/
v4: https://lore.kernel.org/dri-devel/20201026105818.2585306-1-daniel.vetter@ffwll.ch/
v5: https://lore.kernel.org/dri-devel/20201030100815.2269-1-daniel.vetter@ffwll.ch/
v6: https://lore.kernel.org/dri-devel/20201119144146.1045202-1-daniel.vetter@ffwll.ch/

And the discussion that sparked this journey:

https://lore.kernel.org/dri-devel/20201007164426.1812530-1-daniel.vetter@ffwll.ch/

I think the first 12 patches are ready for landing. The parts starting
with "mm: Add unsafe_follow_pfn" probably need more baking time.

Andrew, can you please pick these up, or do you prefer I do a topic branch
and send them to Linus directly in the next merge window?

Changes in v7:
- more acks/reviews
- reordered with the ready pieces at the front
- simplified the new follow_pfn function as Jason suggested

Changes in v6:
- Tested v4l userptr as Tomasz suggested. No boom observed
- Added RFC for locking down follow_pfn, per discussion with Christoph and
  Jason.
- Explain why pup_fast is safe in relevant patches, there was a bit a
  confusion when discussing v5.
- Fix up the resource patch, with CONFIG_IO_STRICT_DEVMEM it crashed on
  boot due to an unintended change (reported by John)

Changes in v5:
- Tomasz found some issues in the media patches
- Polish suggested by Christoph for the unsafe_follow_pfn patch

Changes in v4:
- Drop the s390 patch, that was very stand-alone and now queued up to land
  through s390 trees.
- Comment polish per Dan's review.

Changes in v3:
- Bunch of polish all over, no functional changes aside from one barrier
  in the resource code, for consistency.
- A few more r-b tags.

Changes in v2:
- tons of small polish&fixes all over, thanks to all the reviewers who
  spotted issues
- I managed to test at least the generic_access_phys and pci mmap revoke
  stuff with a few gdb sessions using our i915 debug tools (hence now also
  the drm/i915 patch to properly request all the pci bar regions)
- reworked approach for the pci mmap revoke: Infrastructure moved into
  kernel/resource.c, address_space mapping is now set up at open time for
  everyone (which required some sysfs changes). Does indeed look a lot
  cleaner and a lot less invasive than I feared at first.

Coments and review on the remaining bits very much welcome, especially
from the kvm and vfio side.

Cheers, Daniel

Daniel Vetter (17):
  drm/exynos: Stop using frame_vector helpers
  drm/exynos: Use FOLL_LONGTERM for g2d cmdlists
  misc/habana: Stop using frame_vector helpers
  misc/habana: Use FOLL_LONGTERM for userptr
  mm/frame-vector: Use FOLL_LONGTERM
  media: videobuf2: Move frame_vector into media subsystem
  mm: Close race in generic_access_phys
  PCI: Obey iomem restrictions for procfs mmap
  /dev/mem: Only set filp->f_mapping
  resource: Move devmem revoke code to resource framework
  sysfs: Support zapping of binary attr mmaps
  PCI: Revoke mappings like devmem
  mm: Add unsafe_follow_pfn
  media/videobuf1|2: Mark follow_pfn usage as unsafe
  vfio/type1: Mark follow_pfn as unsafe
  kvm: pass kvm argument to follow_pfn callsites
  mm: add mmu_notifier argument to follow_pfn

 arch/powerpc/kvm/book3s_64_mmu_hv.c           |   2 +-
 arch/powerpc/kvm/book3s_64_mmu_radix.c        |   2 +-
 arch/powerpc/kvm/e500_mmu_host.c              |   2 +-
 arch/x86/kvm/mmu/mmu.c                        |   8 +-
 drivers/char/mem.c                            |  86 +-------------
 drivers/gpu/drm/exynos/Kconfig                |   1 -
 drivers/gpu/drm/exynos/exynos_drm_g2d.c       |  48 ++++----
 drivers/media/common/videobuf2/Kconfig        |   1 -
 drivers/media/common/videobuf2/Makefile       |   1 +
 .../media/common/videobuf2}/frame_vector.c    |  57 ++++-----
 .../media/common/videobuf2/videobuf2-memops.c |   3 +-
 drivers/media/platform/omap/Kconfig           |   1 -
 drivers/media/v4l2-core/videobuf-dma-contig.c |   2 +-
 drivers/misc/habanalabs/Kconfig               |   1 -
 drivers/misc/habanalabs/common/habanalabs.h   |   6 +-
 drivers/misc/habanalabs/common/memory.c       |  52 +++-----
 drivers/pci/pci-sysfs.c                       |   4 +
 drivers/pci/proc.c                            |   6 +
 drivers/vfio/vfio_iommu_type1.c               |   4 +-
 fs/sysfs/file.c                               |  11 ++
 include/linux/ioport.h                        |   6 +-
 include/linux/kvm_host.h                      |   9 +-
 include/linux/mm.h                            |  50 +-------
 include/linux/sysfs.h                         |   2 +
 include/media/frame_vector.h                  |  47 ++++++++
 include/media/videobuf2-core.h                |   1 +
 kernel/resource.c                             |  98 ++++++++++++++-
 mm/Kconfig                                    |   3 -
 mm/Makefile                                   |   1 -
 mm/memory.c                                   | 112 +++++++++++++++---
 mm/nommu.c                                    |  16 ++-
 security/Kconfig                              |  13 ++
 virt/kvm/kvm_main.c                           |  56 +++++----
 33 files changed, 413 insertions(+), 299 deletions(-)
 rename {mm => drivers/media/common/videobuf2}/frame_vector.c (84%)
 create mode 100644 include/media/frame_vector.h
```
