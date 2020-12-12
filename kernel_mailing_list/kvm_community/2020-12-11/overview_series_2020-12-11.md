#### [kvm-unit-tests PATCH] Makefile: fix use of PWD in target "all"From: Ricardo Koller <ricarkol@google.com>
##### From: Ricardo Koller <ricarkol@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ricardo Koller <ricarkol@google.com>
X-Patchwork-Id: 11969465
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.2 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 9E324C4361B
	for <kvm@archiver.kernel.org>; Fri, 11 Dec 2020 21:12:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 47AF32405A
	for <kvm@archiver.kernel.org>; Fri, 11 Dec 2020 21:12:53 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732403AbgLKTow (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 11 Dec 2020 14:44:52 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:36716 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727522AbgLKToQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 11 Dec 2020 14:44:16 -0500
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id F413BC0613D3
        for <kvm@vger.kernel.org>; Fri, 11 Dec 2020 11:43:35 -0800 (PST)
Received: by mail-yb1-xb4a.google.com with SMTP id c9so11948641ybs.8
        for <kvm@vger.kernel.org>; Fri, 11 Dec 2020 11:43:35 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:message-id:mime-version:subject:from:to:cc;
        bh=wSUM7ixh9VMkFpje5luwKIhgx5NDbvRWAu95CbNOjek=;
        b=SdZCI7liBQDfdKPOf+3HtJOCKPkLxZo91GpyiM7eFBFlVYLWfbdNBLtZdRNRc9NYrZ
         U14PRtDkJSYDwJaKhWCEU+SIWffC02zh25U3WTnY5zqpr/gzfsYZ8wCvw3Ztmy430SsI
         /hPS6xGSFMjm0mh2TR8GH3IMHYVf7JYoRLaCnU5ZicV/k3BTi9dLhA7hGxpAYQOE7a+5
         xmVqmDx99ozjk6Fw0/7bRhf5q9VcHcAcZT25ictfT1MbMmIkiD49Z0yde7e3Z5YCs3CT
         Fu9iLeTIV4/zzact8tjTn1jnMnR97cRQly2JD3bAKTegCtHE4iYJwDAb3AUmIyNFLh9S
         3VpA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:message-id:mime-version:subject:from
         :to:cc;
        bh=wSUM7ixh9VMkFpje5luwKIhgx5NDbvRWAu95CbNOjek=;
        b=cXtxde5lSklrEWwY6lLQE42bUX9eL/Od4FcZz64VRJcijFKpTHJsFd0m0a4myJia1c
         2hQAbjG3+MJ6r9UtdubJMzXO7GxA+l0UAvYZjZAXBTw1bXL9fH2p8TxtR/a2gP4Ck3pW
         bhracvBxAhZOWnQRVkrcBUxjVTdFWC93LH9kXYOA5cZMPQ539VVnd2YL0JRnA6IAV/0j
         26lrNI0P8z/I1nFIIMGXTc8hw3Gl2DXFwBKePUA0exvlDSzOnnlCShibBFfQU2w5sJgX
         RZe+cGifE4NPyLSq20qSql/xPO2tMQ0tq/XBhwgIgkQN6GwlCLvL7R2upb4po3u8p1sL
         wCwg==
X-Gm-Message-State: AOAM532Z7UZ8cFXDBfqrbMFYasNLauJQ0j9P6DgoOEtI/jy2xyP0aPTx
        czj1Rh+BDyRMM378DLv0pJMZ6kokn6iXwgaN+ZgvTHpTv0GyO65S3VQvTttWzqSQfyAcSaa/PYy
        RcsmrVZzcw3RnMJrxvWo0+fFCwY9sM8Nw9YEgBYjDOXpEgL/oqAo4WrUflaSAM+A=
X-Google-Smtp-Source: 
 ABdhPJy7nQk61k18lUIMoXF0Pu8Es+1J5Or00pUsL4eY84XbJ+XtlFQTjPgYL7VdVJG4XYd6Zrqiu0sTU3mOeA==
Sender: "ricarkol via sendgmr" <ricarkol@ricarkol2.c.googlers.com>
X-Received: from ricarkol2.c.googlers.com
 ([fda3:e722:ac3:10:24:72f4:c0a8:62fe])
 (user=ricarkol job=sendgmr) by 2002:a25:5f44:: with SMTP id
 h4mr5787020ybm.505.1607715815207; Fri, 11 Dec 2020 11:43:35 -0800 (PST)
Date: Fri, 11 Dec 2020 19:43:31 +0000
Message-Id: <20201211194331.3830000-1-ricarkol@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.29.2.576.ga3fc446d84-goog
Subject: [kvm-unit-tests PATCH] Makefile: fix use of PWD in target "all"
From: Ricardo Koller <ricarkol@google.com>
To: kvm@vger.kernel.org
Cc: Andrew Jones <drjones@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Ricardo Koller <ricarkol@google.com>,
        Jim Mattson <jmattson@google.com>,
        Oliver Upton <oupton@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The "all" target creates the build-head file in the wrong location when
using "make -C" or "sudo make". The reason is that the PWD environment
variable gets the value of the current directory when calling "make -C"
(before the -C changes directories), or is unset in the case of "sudo
make".  Note that the PWD is not changed by the previous "cd $(SRCDIR)".

	/a/b/c $ make -C ../kvm-unit-tests
	=====> creates /a/b/c/build-head

	/a/b/kvm-unit-tests $ sudo make
	=====> creates /build-head
		(note the root)

The consequence of this is that the standalone script can't find the
build-head file:

	/a/b/c $ make -C kvm-unit-tests standalone
	cat: build-head: No such file or directory
	...

	/a/b/kvm-unit-tests $ sudo make standalone
	cat: build-head: No such file or directory
	...

The fix is to not use PWD. "cd $SRCDIR && git rev-parse" is run in a
subshell in order to not break out-of-tree builds, which expect
build-head in the current directory (/a/b/c/build-head below).

Tested:
	out-of-tree build:
	/a/b/c $ ../kvm-unit-tests/configure && make standalone
	
	sudo make:
	/a/b/kvm-unit-tests $ ./configure && sudo make standalone
	
	make -C:
	/a/b/c $ (cd ../kvm-unit-tests && ./configure) && \
				make -C ../kvm-unit-tests standalone

Signed-off-by: Ricardo Koller <ricarkol@google.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Oliver Upton <oupton@google.com>
---
 Makefile | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] kvm:vmx:changes in handle_io() for code cleanup.
##### From: Stephen Zhang <stephenzhangzsd@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stephen Zhang <stephenzhangzsd@gmail.com>
X-Patchwork-Id: 11966909
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 9B299C4361B
	for <kvm@archiver.kernel.org>; Fri, 11 Dec 2020 00:35:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 60BA323DE3
	for <kvm@archiver.kernel.org>; Fri, 11 Dec 2020 00:35:36 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2394564AbgLKAfE (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 10 Dec 2020 19:35:04 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:57478 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1730504AbgLKAeg (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 10 Dec 2020 19:34:36 -0500
Received: from mail-pf1-x443.google.com (mail-pf1-x443.google.com
 [IPv6:2607:f8b0:4864:20::443])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 28F75C0613CF;
        Thu, 10 Dec 2020 16:33:56 -0800 (PST)
Received: by mail-pf1-x443.google.com with SMTP id p4so5839111pfg.0;
        Thu, 10 Dec 2020 16:33:56 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=ofn+qwCdvU5zL1EmyJaz3NlaG2uiyQzoZVTIMzLIfWM=;
        b=eiHHVhCkWHULf2Tt3Yob7BaBni3m9kP8aFddsiZrtL7lTW7djoG9/saJ4DlVrRAeiS
         Wuq+7nCel7krxILaE1lSAzMoGW9+UVQf6dhxAOLu2UsPH2ug7IbTVTYNfJWQvDdulvyJ
         /xIsVdhLZKs6nTOkwsJ0UzKMW9SRTWJjfRxg4QO5XBcYEd+hvDsRhq/7ouNKwLRI4trq
         grXiHTVQGkFS65CA7L6h26fSmy32bbhUvFc8QJ+dLBCP/wsXzL1BAUGmlMCmpo4AMi2f
         pWEUP8ylvFSLR28dFjurA5xRcyn1D6wF+4UwZ4+cJyegUbxrSSKUIWX35dOxkQ5ffsKP
         7g0Q==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=ofn+qwCdvU5zL1EmyJaz3NlaG2uiyQzoZVTIMzLIfWM=;
        b=H+aJvLVeyU1u8a4e4V+T+teKjPzUrf1Ocz8Wvonv8QloZxS+rF2fOzlODVtsigR02W
         21py6FsYsMyD1FzHeP5J2tvs82IQDY+QH9YTxnLNSGhNMMvN/1ZXcn2Di5/JmS1Q00cE
         JlMsYmoSX+nIWVo/Cc5f72awLWTRho0bFgh6jUzXYekwCoTxnpzlD1vNBE50xuGb5fCt
         s2w5cWYHjsbrE9G/obWp0TP5xvmnCBSSmBJy7IjvWQdlpyuB2zpiukXUo+/b7leScWyT
         R3/VnBB0lYPVX/t8sphtVgPOzx8MkN1nzMSi66NBzEhtfRY7svMlLcM6K0TWMkchBDrr
         ZcXQ==
X-Gm-Message-State: AOAM532PT8AICn+YnT3ktZyAJb6JLti9f2BUGXsRKimzwP11Zi+/Ma1S
        cYAkAKjalzXTI7YbFCf8nkw=
X-Google-Smtp-Source: 
 ABdhPJzvxci3wICE8s2QLeWV/fRZEgpNiN2zMvjo9TGppkTlxV2fPkZIUiAWhM+q8laARvxiZEf25g==
X-Received: by 2002:a17:90a:380c:: with SMTP id
 w12mr10210531pjb.117.1607646835722;
        Thu, 10 Dec 2020 16:33:55 -0800 (PST)
Received: from localhost.localdomain ([168.63.153.116])
        by smtp.gmail.com with ESMTPSA id
 f90sm8216116pjd.32.2020.12.10.16.33.51
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Thu, 10 Dec 2020 16:33:55 -0800 (PST)
From: Stephen Zhang <stephenzhangzsd@gmail.com>
To: pbonzini@redhat.com, seanjc@google.com, vkuznets@redhat.com,
        wanpengli@tencent.com, jmattson@google.com, joro@8bytes.org,
        tglx@linutronix.de, mingo@redhat.com, bp@alien8.de, x86@kernel.org,
        hpa@zytor.com
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Stephen Zhang <stephenzhangzsd@gmail.com>
Subject: [PATCH] kvm:vmx:changes in handle_io() for code cleanup.
Date: Fri, 11 Dec 2020 08:33:46 +0800
Message-Id: <1607646826-97297-1-git-send-email-stephenzhangzsd@gmail.com>
X-Mailer: git-send-email 1.8.3.1
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Signed-off-by: Stephen Zhang <stephenzhangzsd@gmail.com>
---
 arch/x86/kvm/vmx/vmx.c | 6 +++---
 1 file changed, 3 insertions(+), 3 deletions(-)

```
#### [kvm-unit-tests PATCH v3 1/8] s390x: Add test_bit to library
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11967803
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7B044C4361B
	for <kvm@archiver.kernel.org>; Fri, 11 Dec 2020 10:03:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3987B23F38
	for <kvm@archiver.kernel.org>; Fri, 11 Dec 2020 10:03:43 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2405730AbgLKKDM (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 11 Dec 2020 05:03:12 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:9450 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S2394098AbgLKKCV (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 11 Dec 2020 05:02:21 -0500
Received: from pps.filterd (m0098409.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 0BBA1X7P024715;
        Fri, 11 Dec 2020 05:01:36 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=2LJYac0SJdUeudi8lVHchq42sr3/3XaeFkP2reo3xbA=;
 b=BaMkkw+i51nyJ84gGS+9eTP3wxun3BELxQj9hNX3COXd77hyJNE08Co9ARFq8fT8lAkg
 s3ztilcisTzyzv9fbui7LT90k1XddMNJWSAyxN0nQHL512czaJXIz3LPXYZ2c9TW8Oat
 IJ7oq+MPRJSEkDD/088lqXTSP+bA7bW0bgl8kBWm3Ox2z1f2YT+P6T1+A4Sakra50XJT
 05zvXGYKe4pPhIBVDI9FPH26JDK7f+ISxkpYGIeT7XHA+iCaWjQEi7QwJC189kaIannu
 y1kOPTt5e6ayxFtEapH7b4ezVPH6b+AEc128ICfnO72GNzVUMo+tHWWM+pbEWjs3eWQy DA==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 35c6ka82c1-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 11 Dec 2020 05:01:36 -0500
Received: from m0098409.ppops.net (m0098409.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 0BBA1ZFv024898;
        Fri, 11 Dec 2020 05:01:35 -0500
Received: from ppma03ams.nl.ibm.com (62.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.98])
        by mx0a-001b2d01.pphosted.com with ESMTP id 35c6ka82ay-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 11 Dec 2020 05:01:35 -0500
Received: from pps.filterd (ppma03ams.nl.ibm.com [127.0.0.1])
        by ppma03ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 0BB9romo022873;
        Fri, 11 Dec 2020 10:01:32 GMT
Received: from b06cxnps3074.portsmouth.uk.ibm.com
 (d06relay09.portsmouth.uk.ibm.com [9.149.109.194])
        by ppma03ams.nl.ibm.com with ESMTP id 3581u86unh-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 11 Dec 2020 10:01:32 +0000
Received: from d06av23.portsmouth.uk.ibm.com (d06av23.portsmouth.uk.ibm.com
 [9.149.105.59])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 0BBA1UZd6291886
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 11 Dec 2020 10:01:30 GMT
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id DA90FA405E;
        Fri, 11 Dec 2020 10:01:29 +0000 (GMT)
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 23404A404D;
        Fri, 11 Dec 2020 10:01:29 +0000 (GMT)
Received: from linux01.pok.stglabs.ibm.com (unknown [9.114.17.81])
        by d06av23.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Fri, 11 Dec 2020 10:01:29 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: thuth@redhat.com, david@redhat.com, borntraeger@de.ibm.com,
        imbrenda@linux.ibm.com, cohuck@redhat.com,
        linux-s390@vger.kernel.org
Subject: [kvm-unit-tests PATCH v3 1/8] s390x: Add test_bit to library
Date: Fri, 11 Dec 2020 05:00:32 -0500
Message-Id: <20201211100039.63597-2-frankja@linux.ibm.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20201211100039.63597-1-frankja@linux.ibm.com>
References: <20201211100039.63597-1-frankja@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.343,18.0.737
 definitions=2020-12-11_01:2020-12-09,2020-12-11 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 malwarescore=0 suspectscore=1
 clxscore=1015 impostorscore=0 bulkscore=0 priorityscore=1501
 lowpriorityscore=0 spamscore=0 phishscore=0 mlxlogscore=999 mlxscore=0
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2012110059
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Query/feature bits are commonly tested via MSB bit numbers on
s390. Let's add test bit functions, so we don't need to copy code to
test query bits.

The test_bit code has been taken from the kernel since most s390x KVM unit
test developers are used to them.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
---
 lib/s390x/asm/bitops.h   | 26 ++++++++++++++++++++++++++
 lib/s390x/asm/facility.h |  3 ++-
 s390x/uv-guest.c         |  6 +++---
 3 files changed, 31 insertions(+), 4 deletions(-)

```
#### [PATCH v2] selftests: kvm: remove reassignment of non-absolute variables
##### From: Bill Wendling <morbo@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Bill Wendling <morbo@google.com>
X-Patchwork-Id: 11967037
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id D6B0FC433FE
	for <kvm@archiver.kernel.org>; Fri, 11 Dec 2020 01:25:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8F37923DE3
	for <kvm@archiver.kernel.org>; Fri, 11 Dec 2020 01:25:13 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2389706AbgLKBYU (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 10 Dec 2020 20:24:20 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:36962 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2389606AbgLKBYD (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 10 Dec 2020 20:24:03 -0500
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 827CAC0613D6
        for <kvm@vger.kernel.org>; Thu, 10 Dec 2020 17:23:23 -0800 (PST)
Received: by mail-yb1-xb49.google.com with SMTP id z1so9090410ybg.22
        for <kvm@vger.kernel.org>; Thu, 10 Dec 2020 17:23:23 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:in-reply-to:message-id:mime-version:references:subject
         :from:to:cc;
        bh=76I2HkR/QhH41Al/kavpSZwfOHx+HGfAs7s/cIpsiMQ=;
        b=v26DmsxffYDRU0SN13OvI97KA4NYXbgOXESuqmnU7acvsDpH+XEhpF4Mq5ih4E2Nhz
         PvuKDtqI5UeZ0ESZl48s2g+ferGE6tdYrvXccAmjkobyTOMSnhsk+r1GIcnUTQ9fUsf+
         +udv2LLfV623oLgbJAhIPyTPC2/Z5VkbufNxrc6IEVSGnNJjcxH+tu9LtI7GdYQeg8f/
         2wu+W3m/t4WhECfKWze5Ddyec5+RHpIY4KrtRIK2R0cM5u1FJX5ezs4z+XpikFvl+LGg
         La+IqcaIs4XK2LwYmGt7xk0iUvsRpxS+lqvmGS5mIMHIhVA5QqOyVy9O7JH8+2zLUQqE
         LV3Q==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=76I2HkR/QhH41Al/kavpSZwfOHx+HGfAs7s/cIpsiMQ=;
        b=rV9nX3er/dD+1CKBq13cdYdwyOdAH6XYDAlSOiNzJP5asreR6IiinQSpuxmJkJj4rI
         faNx6EROs3+V9FIN48Cw1kOZMqoc/kmBp9KQGeJI7B5EyQgJ0bmJ5ldeJEIc7aSTw/Xc
         Itf5PJzsehiSqLIr7XPA73NyAk96x5yZ8SFbMP3Il8cEclFxk/Sz1OZbysJnO+RD7+dR
         OhWHIon1WExTS2GGE45/pQh82xBedysjMv2a6pgdVF2Uk7VRQvSkPTvCeWO3t9eSlIwj
         ZkdUGQbn1S7IzC7Aj7bs+STCVX8ejBDY6b2KjKsm/uauULTTXO+nMJCkSngsoybcN28M
         iltQ==
X-Gm-Message-State: AOAM5311khG5mzQ/RxG136uQYb8pCsvJlI5+hNlt5srkfGvXOXdE2HOW
        ECewNnTGpyUlZzAo7jihIvjLUVDJ
X-Google-Smtp-Source: 
 ABdhPJzXE1mavmdvah8ChyCslZLxYWJzdsnmppMUbOd4X2HEw6nIUy3OJgKoq6nRbulcMKSwI+gIwb8HCQ==
Sender: "morbo via sendgmr" <morbo@fawn.svl.corp.google.com>
X-Received: from fawn.svl.corp.google.com
 ([2620:15c:2cd:202:7220:84ff:fe0f:9f6a])
 (user=morbo job=sendgmr) by 2002:a25:ca17:: with SMTP id
 a23mr16202134ybg.229.1607649802623;
 Thu, 10 Dec 2020 17:23:22 -0800 (PST)
Date: Thu, 10 Dec 2020 17:23:17 -0800
In-Reply-To: <X9LJE6ElVfKECnno@google.com>
Message-Id: <20201211012317.3722214-1-morbo@google.com>
Mime-Version: 1.0
References: <X9LJE6ElVfKECnno@google.com>
X-Mailer: git-send-email 2.29.2.576.ga3fc446d84-goog
Subject: [PATCH v2] selftests: kvm: remove reassignment of non-absolute
 variables
From: Bill Wendling <morbo@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        linux-kselftest@vger.kernel.org, kvm@vger.kernel.org,
        Sean Christopherson <seanjc@google.com>
Cc: Benjamin Herrenschmidt <benh@kernel.crashing.org>,
        Shuah Khan <shuah@kernel.org>,
        Bill Wendling <morbo@google.com>, Jian Cai <caij2003@gmail.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Clang's integrated assembler does not allow symbols with non-absolute
values to be reassigned. Modify the interrupt entry loop macro to be
compatible with IAS by using a label and an offset.

Cc: Jian Cai <caij2003@gmail.com>
Signed-off-by: Bill Wendling <morbo@google.com>
References: https://lore.kernel.org/lkml/20200714233024.1789985-1-caij2003@gmail.com/
---
 tools/testing/selftests/kvm/lib/x86_64/handlers.S | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
