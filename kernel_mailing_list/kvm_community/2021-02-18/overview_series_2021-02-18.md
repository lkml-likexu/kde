#### [PATCH 1/1] vfio/pci: remove CONFIG_VFIO_PCI_ZDEV from Kconfig
##### From: Max Gurtovoy <mgurtovoy@nvidia.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Max Gurtovoy <mgurtovoy@nvidia.com>
X-Patchwork-Id: 12093507
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 61B55C433DB
	for <kvm@archiver.kernel.org>; Thu, 18 Feb 2021 12:32:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 23E7B64E2F
	for <kvm@archiver.kernel.org>; Thu, 18 Feb 2021 12:32:41 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231310AbhBRMb7 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 18 Feb 2021 07:31:59 -0500
Received: from hqnvemgate26.nvidia.com ([216.228.121.65]:15528 "EHLO
        hqnvemgate26.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S231816AbhBRKpl (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 18 Feb 2021 05:45:41 -0500
Received: from hqmail.nvidia.com (Not Verified[216.228.121.13]) by
 hqnvemgate26.nvidia.com (using TLS: TLSv1.2, AES256-SHA)
        id <B602e45170000>; Thu, 18 Feb 2021 02:44:39 -0800
Received: from HQMAIL101.nvidia.com (172.20.187.10) by HQMAIL105.nvidia.com
 (172.20.187.12) with Microsoft SMTP Server (TLS) id 15.0.1497.2; Thu, 18 Feb
 2021 10:44:38 +0000
Received: from r-nvmx02.mtr.labs.mlnx (172.20.145.6) by mail.nvidia.com
 (172.20.187.10) with Microsoft SMTP Server id 15.0.1497.2 via Frontend
 Transport; Thu, 18 Feb 2021 10:44:36 +0000
From: Max Gurtovoy <mgurtovoy@nvidia.com>
To: <cohuck@redhat.com>, <kvm@vger.kernel.org>,
        <alex.williamson@redhat.com>, <mjrosato@linux.ibm.com>
CC: <oren@nvidia.com>, <jgg@nvidia.com>,
        Max Gurtovoy <mgurtovoy@nvidia.com>
Subject: [PATCH 1/1] vfio/pci: remove CONFIG_VFIO_PCI_ZDEV from Kconfig
Date: Thu, 18 Feb 2021 10:44:35 +0000
Message-ID: <20210218104435.464773-1-mgurtovoy@nvidia.com>
X-Mailer: git-send-email 2.25.4
MIME-Version: 1.0
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1613645079; bh=z2phGOCqsGlG23NkwT0WdBZvXJFqLh5AY6/Xzsk4+mQ=;
        h=From:To:CC:Subject:Date:Message-ID:X-Mailer:MIME-Version:
         Content-Transfer-Encoding:Content-Type;
        b=QmUdS800XC58UxFQBISKN5DXtpgXL2KZskaZrwhwa5FWPs/3w0V8VNK83jlDHd6Ix
         tSgwftDYaFyKwAenbPcOfSQzFjE2b5cSrAq5ye80jsD9QE7Z65CpMr/dbF5cmg5oPI
         nJQl9viRFxLdI7DAFYuN4sTfo62rD8Bq/2tZ3Ws39GE1KSETuCGrH9vUNIBeCOHO3s
         kmRCQt4QWivpitelyTIrVEdnpxwss6ToGcemx9DmBlleuHU/E9YIv3BxCSmvGjfXOe
         RbthU7aq2idf8DXND5OZRT3umVQ6/GrwzGmcH4RCHhEfomGlAQRzZdQ9KHLyOp/UgK
         ZndGZnQdw0zcg==
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In case we're running on s390 system always expose the capabilities for
configuration of zPCI devices. In case we're running on different
platform, continue as usual.

Signed-off-by: Max Gurtovoy <mgurtovoy@nvidia.com>
Reviewed-by: Matthew Rosato <mjrosato@linux.ibm.com>
---
 drivers/vfio/pci/Kconfig            | 12 ------------
 drivers/vfio/pci/Makefile           |  2 +-
 drivers/vfio/pci/vfio_pci.c         | 12 +++++-------
 drivers/vfio/pci/vfio_pci_private.h |  2 +-
 4 files changed, 7 insertions(+), 21 deletions(-)

```
#### [RFC 1/2] cgroup: sev: Add misc cgroup controllerFrom: Vipin Sharma <vipinsh@google.com>
##### From: Vipin Sharma <vipinsh@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vipin Sharma <vipinsh@google.com>
X-Patchwork-Id: 12094229
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id A3996C433DB
	for <kvm@archiver.kernel.org>; Thu, 18 Feb 2021 20:02:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4878064EC0
	for <kvm@archiver.kernel.org>; Thu, 18 Feb 2021 20:02:15 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232128AbhBRUBy (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 18 Feb 2021 15:01:54 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:60406 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S231964AbhBRT7W (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 18 Feb 2021 14:59:22 -0500
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id AB061C061793
        for <kvm@vger.kernel.org>; Thu, 18 Feb 2021 11:56:14 -0800 (PST)
Received: by mail-yb1-xb4a.google.com with SMTP id o9so3881865yba.18
        for <kvm@vger.kernel.org>; Thu, 18 Feb 2021 11:56:14 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:in-reply-to:message-id:mime-version:references:subject
         :from:to:cc;
        bh=ZBosNCHMy/K4UhQNyIcNsMYaIPpohD0WhsOGoDNClZ8=;
        b=hQPsoHOImh7pWNIyWvtCCOOaS6yimib+r2qpJh5vQ3CvKZ63S8uRFBQ5T1r0qlwmb4
         18vhgXvpNXLALDGfEYUouez+KWT10FHGDWGPCeQpARC+rpNWtR2E0DUHnfux/DrZVGJH
         PbXFVVDVQWXSep+NmDpFJOI2EJ9oEbVVvoxx8fdeqaSBDvE1I4T5EdXEqD/KviZ/AqP/
         QbCnEVJ/RdoFp2raLcprZSNRH+ba2I5YapvWS5fGIWTIThvl7lhT1C5fhAFMYqN1LQ6i
         uv1tyUsf2fWGv43bCJ2izrGP3gdhshZAbEx90CA5O2aRy4oqU10+0XNjpR4Wd5m+62NR
         S5QQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=ZBosNCHMy/K4UhQNyIcNsMYaIPpohD0WhsOGoDNClZ8=;
        b=U0Ejg62QJcz01K3MhSI7vKk55BuYDLDIe5qWDSS0jGk40kRbcwfS496TII3Kl3ESI4
         eWfrRThfS1Nlq7xXsLT9XQGy/suifWrv2sWOGcu0A4OT6x1Mvj2ul18V6KGPPtK2hTdB
         o7C/9IPEo8/gIUVTJ0VFxbAzlcfypPCKP6epbHPNWzlK/vEk46DmzvTzQ5DddiK27HDS
         Q4SkkyHS84W047Io7FXPAyIZKChC1KDi/bGt3AL+2WZk0EWsbzoWk8gespUDl08bJklu
         CM2IFWhOSA+LCS92DsCyUvOpDwv5v6B0kkfRV/BPaCiEWfoQ2v1vVkKe9TwWbGORxomk
         tyKw==
X-Gm-Message-State: AOAM5339t/OSUTYG1et71ApzCG7nmHYyPi+iUFFmQQlET/XbEXa8f6F6
        GhMP52cR8wiTW2EG2ZIHx/bb4taawXI3
X-Google-Smtp-Source: 
 ABdhPJwaXYwnxDvPC3nmGcON+fEff/iK4/lpPOlGhvwAQ7qmPyMoncsNty2geR2O47P88vmPkPNtqnj09Mna
Sender: "vipinsh via sendgmr" <vipinsh@vipinsh.kir.corp.google.com>
X-Received: from vipinsh.kir.corp.google.com
 ([2620:0:1008:10:580f:a4a0:74ce:b3b4])
 (user=vipinsh job=sendgmr) by 2002:a25:55c3:: with SMTP id
 j186mr9311553ybb.357.1613678173863; Thu, 18 Feb 2021 11:56:13 -0800 (PST)
Date: Thu, 18 Feb 2021 11:55:48 -0800
In-Reply-To: <20210218195549.1696769-1-vipinsh@google.com>
Message-Id: <20210218195549.1696769-2-vipinsh@google.com>
Mime-Version: 1.0
References: <20210218195549.1696769-1-vipinsh@google.com>
X-Mailer: git-send-email 2.30.0.617.g56c4b15f3c-goog
Subject: [RFC 1/2] cgroup: sev: Add misc cgroup controller
From: Vipin Sharma <vipinsh@google.com>
To: tj@kernel.org, thomas.lendacky@amd.com, brijesh.singh@amd.com,
        jon.grimm@amd.com, eric.vantassell@amd.com, pbonzini@redhat.com,
        hannes@cmpxchg.org, frankja@linux.ibm.com, borntraeger@de.ibm.com
Cc: corbet@lwn.net, seanjc@google.com, vkuznets@redhat.com,
        wanpengli@tencent.com, jmattson@google.com, joro@8bytes.org,
        tglx@linutronix.de, mingo@redhat.com, bp@alien8.de, hpa@zytor.com,
        gingell@google.com, rientjes@google.com, dionnaglaze@google.com,
        kvm@vger.kernel.org, x86@kernel.org, cgroups@vger.kernel.org,
        linux-doc@vger.kernel.org, linux-kernel@vger.kernel.org,
        Vipin Sharma <vipinsh@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The Miscellaneous cgroup provides the resource allocation and tracking
mechanism for the scalar resources which cannot be abstracted like the
other cgroup resources. Controller is enabled by the CONFIG_CGROUP_MISC
config option.

The first two resources added to the miscellaneous controller are Secure
Encrypted Virtualization (SEV) ASIDs and SEV - Encrypted State (SEV-ES)
ASIDs. These limited ASIDs are used for encrypting virtual machines
memory on the AMD platform

Miscellaneous controller provides 3 interface files:

misc.capacity
  A read-only flat-keyed file shown only in the root cgroup.  It shows
  miscellaneous scalar resources available on the platform along with
  their quantities
	$ cat misc.capacity
	sev 50
	sev_es 10

misc.current
  A read-only flat-keyed file shown in the non-root cgroups.  It shows
  the current usage of the resources in the cgroup and its children.
	$ cat misc.current
	sev 3
	sev_es 0

misc.max
  A read-write flat-keyed file shown in the non root cgroups. Allowed
  maximum usage of the resources in the cgroup and its children.::
	$ cat misc.max
	sev max
	sev_es 4

  Limit can be set by::
	# echo sev 1 > misc.max

  Limit can be set to max by::
	# echo sev max > misc.max

  Limits can be set more than the capacity value in the misc.capacity
  file.

Signed-off-by: Vipin Sharma <vipinsh@google.com>
Reviewed-by: David Rientjes <rientjes@google.com>
---
 arch/x86/kvm/svm/sev.c        |  60 ++++-
 arch/x86/kvm/svm/svm.h        |   1 +
 include/linux/cgroup_subsys.h |   4 +
 include/linux/misc_cgroup.h   |  75 ++++++
 init/Kconfig                  |  14 ++
 kernel/cgroup/Makefile        |   1 +
 kernel/cgroup/misc.c          | 456 ++++++++++++++++++++++++++++++++++
 7 files changed, 601 insertions(+), 10 deletions(-)
 create mode 100644 include/linux/misc_cgroup.h
 create mode 100644 kernel/cgroup/misc.c

```
#### [kvm-unit-tests PATCH v3 1/5] s390x: css: Store CSS Characteristics
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 12093857
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id BDA7EC433E0
	for <kvm@archiver.kernel.org>; Thu, 18 Feb 2021 18:31:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6BD0A64E2F
	for <kvm@archiver.kernel.org>; Thu, 18 Feb 2021 18:31:41 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230218AbhBRSbd (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 18 Feb 2021 13:31:33 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:2954 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S233160AbhBRR1w (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 18 Feb 2021 12:27:52 -0500
Received: from pps.filterd (m0098410.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 11IHKcdR029242
        for <kvm@vger.kernel.org>; Thu, 18 Feb 2021 12:26:52 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references; s=pp1;
 bh=VtrUzpFFWn58R6s39JdNagmRhLdyoxu/DuWKOSH3op8=;
 b=Z4YNJqDwmvLA1p/LiwmSuygElbojbQtySQ3v+2ahWc6SBeWD1yQGGLqR7eVUOTW3M4sD
 5buEHREFJdvW6NvTPqJg0cU5QgUyniVF263pPfeLKcItiG/sebgs2NdGmzkiERsmm98D
 5nIqKjtgQsg1wKx8GeQgWf2UDrszeBpVs5RGBIdn3Sr05ppc4Gec6VAihdD9I5O2EmqR
 CfXxqNzyk+pRzMYLtOquTma0CfLIyw2CnPEct1a2RoydI2K9HVdAmT8KIGTnontRGe9k
 5dm7eSttWD1tZElyQnmicJjL3ilpdY0xOMW7yNG9eWlP0nQZvd/KjLZS8Ml+RRYZ0pGk yg==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 36stphvxmm-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT)
        for <kvm@vger.kernel.org>; Thu, 18 Feb 2021 12:26:52 -0500
Received: from m0098410.ppops.net (m0098410.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 11IHLQNV034221
        for <kvm@vger.kernel.org>; Thu, 18 Feb 2021 12:26:51 -0500
Received: from ppma06ams.nl.ibm.com (66.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.102])
        by mx0a-001b2d01.pphosted.com with ESMTP id 36stphvxkp-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 18 Feb 2021 12:26:51 -0500
Received: from pps.filterd (ppma06ams.nl.ibm.com [127.0.0.1])
        by ppma06ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 11IHNvuv025810;
        Thu, 18 Feb 2021 17:26:49 GMT
Received: from b06cxnps4074.portsmouth.uk.ibm.com
 (d06relay11.portsmouth.uk.ibm.com [9.149.109.196])
        by ppma06ams.nl.ibm.com with ESMTP id 36p61hcv5e-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 18 Feb 2021 17:26:49 +0000
Received: from d06av23.portsmouth.uk.ibm.com (d06av23.portsmouth.uk.ibm.com
 [9.149.105.59])
        by b06cxnps4074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 11IHQkgr44433826
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 18 Feb 2021 17:26:46 GMT
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 7BED8A4040;
        Thu, 18 Feb 2021 17:26:46 +0000 (GMT)
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 233CBA404D;
        Thu, 18 Feb 2021 17:26:46 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.94.58])
        by d06av23.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Thu, 18 Feb 2021 17:26:46 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: frankja@linux.ibm.com, david@redhat.com, thuth@redhat.com,
        cohuck@redhat.com, imbrenda@linux.ibm.com
Subject: [kvm-unit-tests PATCH v3 1/5] s390x: css: Store CSS Characteristics
Date: Thu, 18 Feb 2021 18:26:40 +0100
Message-Id: <1613669204-6464-2-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1613669204-6464-1-git-send-email-pmorel@linux.ibm.com>
References: <1613669204-6464-1-git-send-email-pmorel@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.761
 definitions=2021-02-18_08:2021-02-18,2021-02-18 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 impostorscore=0 spamscore=0
 clxscore=1015 suspectscore=0 bulkscore=0 mlxscore=0 malwarescore=0
 mlxlogscore=999 priorityscore=1501 adultscore=0 phishscore=0
 lowpriorityscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2102180144
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

CSS characteristics exposes the features of the Channel SubSystem.
Let's use Store Channel Subsystem Characteristics to retrieve
the features of the CSS.

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---
 lib/s390x/css.h     |  67 +++++++++++++++++++++++++++
 lib/s390x/css_lib.c | 110 +++++++++++++++++++++++++++++++++++++++++++-
 s390x/css.c         |  12 +++++
 3 files changed, 188 insertions(+), 1 deletion(-)

```
#### [PATCH 1/1] css: SCHIB measurement block origin must be aligned
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 12093863
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 9797CC433E6
	for <kvm@archiver.kernel.org>; Thu, 18 Feb 2021 18:33:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 406D964E92
	for <kvm@archiver.kernel.org>; Thu, 18 Feb 2021 18:33:36 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232405AbhBRSck (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 18 Feb 2021 13:32:40 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:3194 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S234440AbhBRReg (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 18 Feb 2021 12:34:36 -0500
Received: from pps.filterd (m0098409.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 11IHWuww137831
        for <kvm@vger.kernel.org>; Thu, 18 Feb 2021 12:33:51 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references; s=pp1;
 bh=XngdBw/B77KioqbuoRrCqR7QL3zmo4cvAzyuaTHcdqA=;
 b=EZneu/sgesPbYJZ1TG5OPhrFqFV0HNWO7RhhDCyT9dCVjJ50e4rKlnqKEZWpqJ8/rmyp
 9oKjPfTUBsFp7K1RxACgAd+bZCmrbg9iQTqafhDv0KK6CWO2dqGHpjGegVb955GFvfP9
 pY7eESJF98H9iKHZe+K3wSTbpu/JT6yNYz9KGZr7jMPIHf+bBt8NDAzDG8uKrOO1nwjJ
 NQFGMh36RaBuQlvOHjQ/85lb+c+HyNe3qgeMLH+B9tT6q9Xlp59K1IVh4gWUCd3/hWMl
 bNUwbB+VGJsKDfyV62WV7mjzTGimqH9abiSh+38nOt31vOW+RsxLSWfsD9EhxnCyfAdF pg==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 36sveggggy-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT)
        for <kvm@vger.kernel.org>; Thu, 18 Feb 2021 12:33:50 -0500
Received: from m0098409.ppops.net (m0098409.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 11IHXEPU139182
        for <kvm@vger.kernel.org>; Thu, 18 Feb 2021 12:33:50 -0500
Received: from ppma04ams.nl.ibm.com (63.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.99])
        by mx0a-001b2d01.pphosted.com with ESMTP id 36svegggfe-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 18 Feb 2021 12:33:50 -0500
Received: from pps.filterd (ppma04ams.nl.ibm.com [127.0.0.1])
        by ppma04ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 11IHNv9u011693;
        Thu, 18 Feb 2021 17:33:48 GMT
Received: from b06cxnps4074.portsmouth.uk.ibm.com
 (d06relay11.portsmouth.uk.ibm.com [9.149.109.196])
        by ppma04ams.nl.ibm.com with ESMTP id 36p6d8cvs9-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 18 Feb 2021 17:33:47 +0000
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06cxnps4074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 11IHXjjQ45220304
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 18 Feb 2021 17:33:45 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 3307DA405F;
        Thu, 18 Feb 2021 17:33:45 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id CFE65A4062;
        Thu, 18 Feb 2021 17:33:44 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.94.58])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Thu, 18 Feb 2021 17:33:44 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: frankja@linux.ibm.com, david@redhat.com, thuth@redhat.com,
        cohuck@redhat.com, imbrenda@linux.ibm.com, pasic@linux.ibm.com
Subject: [PATCH 1/1] css: SCHIB measurement block origin must be aligned
Date: Thu, 18 Feb 2021 18:33:43 +0100
Message-Id: <1613669623-7328-2-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1613669623-7328-1-git-send-email-pmorel@linux.ibm.com>
References: <1613669623-7328-1-git-send-email-pmorel@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.761
 definitions=2021-02-18_08:2021-02-18,2021-02-18 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 phishscore=0 bulkscore=0
 mlxscore=0 adultscore=0 suspectscore=0 spamscore=0 priorityscore=1501
 clxscore=1015 mlxlogscore=999 malwarescore=0 lowpriorityscore=0
 impostorscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2102180144
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The Measurement Block Origin inside the SCHIB is used when
Mesurement Block format 1 is in used and must be aligned
on 128bits.

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
---
 target/s390x/ioinst.c | 6 ++++++
 1 file changed, 6 insertions(+)

```
#### [PATCH] KVM: nSVM: prepare guest save area while is_guest_mode is true
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 12093845
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D7A51C433E0
	for <kvm@archiver.kernel.org>; Thu, 18 Feb 2021 18:28:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8EE6364DEC
	for <kvm@archiver.kernel.org>; Thu, 18 Feb 2021 18:28:43 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231903AbhBRS2K (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 18 Feb 2021 13:28:10 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:27174 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S233597AbhBRQaE (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 18 Feb 2021 11:30:04 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1613665718;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=7n6Dv7TL968Ih5U8eggCJpLl9IZAG+GVZ7m57WR0dUw=;
        b=bQ7RmRx+usdoqvOCdNeSof+U2ghbPa9y+E2FJG9WRHBU/HTpOlq+ZPAWgavst/D5vkr/lH
        BH+Uu3/rfbqfUHADrrDGQG6gtIcEMopuygy7sG9D+QIBMfeuHMEhTgYKDyZwrNtIOAqMlE
        XRNjP4adfwikJarjzCqWxGkoo+eCnBE=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-511-NcuK9xVoObOOMUB8lotdwA-1; Thu, 18 Feb 2021 11:28:34 -0500
X-MC-Unique: NcuK9xVoObOOMUB8lotdwA-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 71EC980196C;
        Thu, 18 Feb 2021 16:28:32 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id EC39C5C1C4;
        Thu, 18 Feb 2021 16:28:31 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: jroedel@suse.de, seanjc@google.com, mlevitsk@redhat.com
Subject: [PATCH] KVM: nSVM: prepare guest save area while is_guest_mode is
 true
Date: Thu, 18 Feb 2021 11:28:31 -0500
Message-Id: <20210218162831.1407616-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Right now, enter_svm_guest_mode is calling nested_prepare_vmcb_save and
nested_prepare_vmcb_control.  This results in is_guest_mode being false
until the end of nested_prepare_vmcb_control.

This is a problem because nested_prepare_vmcb_save can in turn cause
changes to the intercepts and these have to be applied to the "host VMCB"
(stored in svm->nested.hsave) and then merged with the VMCB12 intercepts
into svm->vmcb.

In particular, without this change we forget to set the CR0 read and CR0
write intercepts when running a real mode L2 guest with NPT disabled.
The guest is therefore able to see the CR0.PG bit that KVM sets to
enable "paged real mode".  This patch fixes the svm.flat mode_switch
test case with npt=0.  There are no other problematic calls in
nested_prepare_vmcb_save.

The bug is present since commit 06fc7772690d ("KVM: SVM: Activate nested
state only when guest state is complete", 2010-04-25).  Unfortunately,
it is not clear from the commit message what issue exactly led to the
change back then.  It was probably related to svm_set_cr0 however because
the patch series cover letter[1] mentioned lazy FPU switching.

[1] https://lore.kernel.org/kvm/1266493115-28386-1-git-send-email-joerg.roedel@amd.com/

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Sean Christopherson <seanjc@google.com>
---
 arch/x86/kvm/svm/nested.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH] s390x: Remove sthyi partition number check
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 12093351
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7A944C433DB
	for <kvm@archiver.kernel.org>; Thu, 18 Feb 2021 08:29:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3D57664E6F
	for <kvm@archiver.kernel.org>; Thu, 18 Feb 2021 08:29:32 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230517AbhBRI25 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 18 Feb 2021 03:28:57 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:14226 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S230414AbhBRIZq (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 18 Feb 2021 03:25:46 -0500
Received: from pps.filterd (m0098399.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 11I82xs1073958;
        Thu, 18 Feb 2021 03:25:02 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=pHf1GQg/rDXhUhPT7iQkQ9FeW+N/gnO3ojXYnxwBWAI=;
 b=LMjuI39zAwHP3meDCCOH2uPUIE5N/17JlWfqy4YE04/xWRdscgrdijA++pQ2ecMOk10/
 EqmXqhcIG/WS/fS1Wm0A58MccXkpTYFgYQ4Vf3muIIBgPr1pISbjEfuXsdS5RCSgV8I8
 Rp+ypDnqgHI6WWOZYBxBly3QHL1l7TxE+HVvHdzPziKTZEVpkGKngrUlPLDu1S3r4TJU
 9cOFF+KG2KmAoEZqNbMNGXxFIsS5iyWR6wL7n0/aNmkTNwUad0XbEfX3WmFmZQhYDzw1
 l6zlv31fFOfRAF/j7yrFpNTr7XomxNVyvIj551bCQOQAQVfBl3n5IVFLU1AY1xbrQb2u aw==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 36smbp8qjy-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 18 Feb 2021 03:25:01 -0500
Received: from m0098399.ppops.net (m0098399.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 11I82wcR073893;
        Thu, 18 Feb 2021 03:25:01 -0500
Received: from ppma03ams.nl.ibm.com (62.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.98])
        by mx0a-001b2d01.pphosted.com with ESMTP id 36smbp8qht-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 18 Feb 2021 03:25:01 -0500
Received: from pps.filterd (ppma03ams.nl.ibm.com [127.0.0.1])
        by ppma03ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 11I8LvJQ008135;
        Thu, 18 Feb 2021 08:24:59 GMT
Received: from b06cxnps3075.portsmouth.uk.ibm.com
 (d06relay10.portsmouth.uk.ibm.com [9.149.109.195])
        by ppma03ams.nl.ibm.com with ESMTP id 36rw3u912g-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 18 Feb 2021 08:24:59 +0000
Received: from d06av24.portsmouth.uk.ibm.com (mk.ibm.com [9.149.105.60])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 11I8OvX933882508
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 18 Feb 2021 08:24:57 GMT
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id F27244203F;
        Thu, 18 Feb 2021 08:24:56 +0000 (GMT)
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 5487F42042;
        Thu, 18 Feb 2021 08:24:56 +0000 (GMT)
Received: from linux01.pok.stglabs.ibm.com (unknown [9.114.17.81])
        by d06av24.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Thu, 18 Feb 2021 08:24:56 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, imbrenda@linux.ibm.com,
        david@redhat.com, thuth@redhat.com
Subject: [kvm-unit-tests PATCH] s390x: Remove sthyi partition number check
Date: Thu, 18 Feb 2021 03:24:49 -0500
Message-Id: <20210218082449.29876-1-frankja@linux.ibm.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.761
 definitions=2021-02-18_03:2021-02-18,2021-02-18 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 suspectscore=0
 priorityscore=1501 mlxscore=0 bulkscore=0 clxscore=1015 spamscore=0
 phishscore=0 malwarescore=0 adultscore=0 mlxlogscore=871 impostorscore=0
 lowpriorityscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2102180066
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Turns out that partition numbers start from 0 and not from 1 so a 0
check doesn't make sense here.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
---
 s390x/sthyi.c | 1 -
 1 file changed, 1 deletion(-)

```
#### [PATCH kvm-unit-tests] vmx: make !EPT error messages consistent
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 12093645
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 22EC2C433E0
	for <kvm@archiver.kernel.org>; Thu, 18 Feb 2021 16:11:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DD29560238
	for <kvm@archiver.kernel.org>; Thu, 18 Feb 2021 16:11:55 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232995AbhBRQLO (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 18 Feb 2021 11:11:14 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:60735 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S229907AbhBRNRd (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 18 Feb 2021 08:17:33 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1613654160;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=x1InpcjNtn1WO1uMr7ydGzVJe3PkHnP+TrsVrmd764k=;
        b=FcK5y7vRtPZDPrw7KF24uqUPfbe5BQYBE7x/lcUmMZcMdkn4cVBAsSqmllAjEn1yBZzPzO
        JlQ3cMxuZ64mX+LzBuGdda373L2dBF0liu89f54fxwphNPBB8I+hzOhT9QZiY5ca2CrsJW
        F3vyWc3r9ZmDxrJ1D3WkuyNTWBJ7P/o=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-323-10RtWFfOPgO36-bSX8_3_A-1; Thu, 18 Feb 2021 08:15:56 -0500
X-MC-Unique: 10RtWFfOPgO36-bSX8_3_A-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id C9211835E3C
        for <kvm@vger.kernel.org>; Thu, 18 Feb 2021 13:15:55 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 8CA7F50EDF
        for <kvm@vger.kernel.org>; Thu, 18 Feb 2021 13:15:55 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: kvm@vger.kernel.org
Subject: [PATCH kvm-unit-tests] vmx: make !EPT error messages consistent
Date: Thu, 18 Feb 2021 08:15:54 -0500
Message-Id: <20210218131554.1396965-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Always add a \t at the beginning and a \n at the end.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 x86/vmx_tests.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH kvm-unit-tests] x86: clean up EFER definitions
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 12093647
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 04C6AC433E0
	for <kvm@archiver.kernel.org>; Thu, 18 Feb 2021 16:13:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A959C64E85
	for <kvm@archiver.kernel.org>; Thu, 18 Feb 2021 16:13:14 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233019AbhBRQMd (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 18 Feb 2021 11:12:33 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:46978 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S233534AbhBRN24 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 18 Feb 2021 08:28:56 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1613654812;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=bhnfXN4CfJadCOJu0k85BVIxh2VnYixTtm/U1XJMPFM=;
        b=eA3rwuv10bZjOZOEE49k2xKfnGb0/oe8kBcyB2SxbNBjQVSuTlwJXG17f2VbsnGeEIoe/e
        r50x/hIVzmiOCs43EGBoWqC2/CJ62A+MHaFbMZPxMWtvCG8U2IH1UTSjMnlkEBxU6GeOvw
        QCRY/HKi76x1+qJki6QDuEG7gErITWw=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-572-xfRKVqxvNEqUUb6rTXPIFg-1; Thu, 18 Feb 2021 08:26:50 -0500
X-MC-Unique: xfRKVqxvNEqUUb6rTXPIFg-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id EE60710066F0
        for <kvm@vger.kernel.org>; Thu, 18 Feb 2021 13:26:49 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id B17C0614F0
        for <kvm@vger.kernel.org>; Thu, 18 Feb 2021 13:26:49 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: kvm@vger.kernel.org
Subject: [PATCH kvm-unit-tests] x86: clean up EFER definitions
Date: Thu, 18 Feb 2021 08:26:48 -0500
Message-Id: <20210218132648.1397421-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The X86_EFER_LMA definition is wrong, while X86_IA32_EFER is unused.
There are also two useless WRMSRs that try to set EFER_LMA in
x86/pks.c and x86/pku.c.  Clean them all up.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Sean Christopherson <seanjc@google.com>
---
 lib/x86/processor.h | 2 --
 x86/pks.c           | 1 -
 x86/pku.c           | 1 -
 3 files changed, 4 deletions(-)

```
#### [PATCH] KVM: x86: dump_vmcs should not assume GUEST_IA32_EFER is valid
##### From: David Edmondson <david.edmondson@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Edmondson <david.edmondson@oracle.com>
X-Patchwork-Id: 12093519
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,
	SPF_PASS,UNPARSEABLE_RELAY,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 8D5CFC43381
	for <kvm@archiver.kernel.org>; Thu, 18 Feb 2021 12:37:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4DFB261606
	for <kvm@archiver.kernel.org>; Thu, 18 Feb 2021 12:37:33 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233059AbhBRMf6 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 18 Feb 2021 07:35:58 -0500
Received: from userp2120.oracle.com ([156.151.31.85]:54356 "EHLO
        userp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S232078AbhBRL7B (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 18 Feb 2021 06:59:01 -0500
Received: from pps.filterd (userp2120.oracle.com [127.0.0.1])
        by userp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 11IA16Bs136764;
        Thu, 18 Feb 2021 10:05:00 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : content-transfer-encoding : content-type :
 mime-version; s=corp-2020-01-29;
 bh=t+3R5pgJIjLlnnNl4rgE5n5ibxQZ22hAk8W+prOmarE=;
 b=NCbm/ePttfFQcbPUvVgqSrtvFAMlDFnSVk/0hYwzYqd57lhrQJl8hbudPAaav46shVb6
 4qcBHX5O3pYDXjoquW14CVf6Br6TSMG6lYpXhtEASlVO4WvB7Eh66F/QQhxqVKLk3qD1
 rvMeUBfEGHkgKgLIL+oKsOV2/tR6ooS5AfHSaIqvnHeLz9JYhjOe/aq9Vy6Dy6md6O0l
 9z8hzgHhTgHNpDS2blzfXGtNseXqizr9xS8CUCrfrbbx2div59GvnRjz+q+brtAIrz7/
 2l50FGBOMkpGZVjow/3LIv17s69xUF8QdfdZnB+MWaemdcDfGPtGYrF4yFI347fWkn0+ 8w==
Received: from userp3020.oracle.com (userp3020.oracle.com [156.151.31.79])
        by userp2120.oracle.com with ESMTP id 36p7dnn9vs-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 18 Feb 2021 10:05:00 +0000
Received: from pps.filterd (userp3020.oracle.com [127.0.0.1])
        by userp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 11I9xkJd109819;
        Thu, 18 Feb 2021 10:05:00 GMT
Received: from nam02-cy1-obe.outbound.protection.outlook.com
 (mail-cys01nam02lp2058.outbound.protection.outlook.com [104.47.37.58])
        by userp3020.oracle.com with ESMTP id 36prhu179f-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 18 Feb 2021 10:04:59 +0000
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=F4Q4UH4ogjTYObvTvE3/XCpcsHmdCZvjW2BSk5Oykw/wq2xeMnlXhcIBW6mJe/6UhJb+A+OePbFh05mQRxUinDwUD2wLeJ38ltFSvKz2R8TNkUxUhoVedACdR2scmHM4QUPRGUPj2e7MckHyl5uEbjcrZ67d+74mJ8ZdanMmfAy9rsw71FwLOB3gFShpbAemOzQfIsVXob0w7BaThia2xe3RHSpkV2Wi4b7bZ18Ok7Q6C0YPSmaH54bkGgK867JYLcO6SlcQw0sxGofLCAmtkqGufZFfz8EOVVPRmhU2ORh6+vFAqXNZf/b4dX8LA/gRiUWLfwWsGvR4VWuzXBnwcw==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=t+3R5pgJIjLlnnNl4rgE5n5ibxQZ22hAk8W+prOmarE=;
 b=oImjUEj0QLEo0wCOhhgB0QDPmREXBBb7+nUJRDAxUUPnVIQM62mJhmjExxJox9hHv2Jqd6RdJ/gl7Ilb4gD/N0vMh2JMDPIUCmfugyAnwU3D2T7idfKOeV1FPR1jcmF4n4MtV75nL4JQkzE0C5Ad9jLNvHWyBP6ZrlIW0hLxDagomDGRAyZ8qqlfcaYhtlgFzkKLxkPIo9CSJtM2vdNKLvTaoRW+/jhT6bvh7JJdLtBSXWrTDSFRRrTZPGwZVQY1SCatTY9n/pnFvTbkeTXPxXYsnncaNq2j87PIKDZ2Ty6v7efwSxlB0elhpE72KKV3FAQYobJHfq23orSxAvxEJA==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=oracle.com; dmarc=pass action=none header.from=oracle.com;
 dkim=pass header.d=oracle.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=oracle.onmicrosoft.com; s=selector2-oracle-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=t+3R5pgJIjLlnnNl4rgE5n5ibxQZ22hAk8W+prOmarE=;
 b=Hq2LSvRPz+rXeoVu3vu7sybD/9b90+DeRokozSSjDZPvQ9nQGgT0wOM3R8ldCqQSMDrEsVq35ZyMM2wBzgCl962VZatGJvZSuFeU16Uc2oqkEDZH0ODF2aTNJgh3uNN7JgJzPyQLrVqNH/SHL4dAA91RbMlQBstnB21aXp7Bi2w=
Authentication-Results: redhat.com; dkim=none (message not signed)
 header.d=none;redhat.com; dmarc=none action=none header.from=oracle.com;
Received: from DM6PR10MB3148.namprd10.prod.outlook.com (2603:10b6:5:1a4::21)
 by DM6PR10MB2427.namprd10.prod.outlook.com (2603:10b6:5:a9::10) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3846.34; Thu, 18 Feb
 2021 10:04:57 +0000
Received: from DM6PR10MB3148.namprd10.prod.outlook.com
 ([fe80::f871:5965:2081:3934]) by DM6PR10MB3148.namprd10.prod.outlook.com
 ([fe80::f871:5965:2081:3934%5]) with mapi id 15.20.3846.027; Thu, 18 Feb 2021
 10:04:57 +0000
From: David Edmondson <david.edmondson@oracle.com>
To: linux-kernel@vger.kernel.org
Cc: Borislav Petkov <bp@alien8.de>, Wanpeng Li <wanpengli@tencent.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>, x86@kernel.org,
        "H. Peter Anvin" <hpa@zytor.com>,
        Sean Christopherson <seanjc@google.com>, kvm@vger.kernel.org,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        David Edmondson <david.edmondson@oracle.com>
Subject: [PATCH] KVM: x86: dump_vmcs should not assume GUEST_IA32_EFER is
 valid
Date: Thu, 18 Feb 2021 10:04:50 +0000
Message-Id: <20210218100450.2157308-1-david.edmondson@oracle.com>
X-Mailer: git-send-email 2.30.0
X-Originating-IP: [2001:8b0:bb71:7140:64::1]
X-ClientProxiedBy: LO4P123CA0416.GBRP123.PROD.OUTLOOK.COM
 (2603:10a6:600:18b::7) To DM6PR10MB3148.namprd10.prod.outlook.com
 (2603:10b6:5:1a4::21)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from disaster-area.hh.sledj.net (2001:8b0:bb71:7140:64::1) by
 LO4P123CA0416.GBRP123.PROD.OUTLOOK.COM (2603:10a6:600:18b::7) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3846.35 via Frontend
 Transport; Thu, 18 Feb 2021 10:04:55 +0000
Received: from localhost (disaster-area.hh.sledj.net [local])   by
 disaster-area.hh.sledj.net (OpenSMTPD) with ESMTPA id 2e495f13;
      Thu, 18 Feb 2021 10:04:50 +0000 (UTC)
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 3337368d-fd3c-49b9-9fdd-08d8d3f4a587
X-MS-TrafficTypeDiagnostic: DM6PR10MB2427:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM6PR10MB24272CC26DBEA10F0B3829F688859@DM6PR10MB2427.namprd10.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:2449;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 ks1ruvLv2FnU45ksWsSvnliPfxesObCIcVbx1hChU40lhG6kn0W8wM7GmyQP5pEZS/ariquNZq8m4M+AjXBuMhOakivHKIwfHMuVMGHdn8CHsYRzVm8nqwpX8vNvtmP6PlZQDF1Y2eYMArqyijr/Zy+1hzHGYFVda5VEiLG2OPtbqzH9Urzn6oH30And9XIsHSG4Wga3AAuSL5zS1cYk398/1tWGI6dCCsJa6sVTb9DRDxQI0ZBcJ0RWA9PX3tmZqiINbeZ5tJ8OgTFjvZKn9a7XzgkxTJ9Wj5hdxpywFHJKE1nGce7tNat5hLB/GyIU6mzclSq61jxNxUzCm+iBH4gT1gOIvbX9X1K7uJhCM/vQznjq/7y1G+sMvD9HQj4Vwt+4QkOn+epNDNC4PV7jcR6gYpUUVN+CI/ZI0x2Uyj1yKLRvmGQCHl72QI0HKz93cyiX+7PmIxStI/ZrKVIZtZEZ300q0hXJVkfUbUgGQuSxcOpLIUYBjAvwBVAeKLRbbLeLctGGLFN+/HBL3GlWzQ==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM6PR10MB3148.namprd10.prod.outlook.com;PTR:;CAT:NONE;SFS:(366004)(396003)(39860400002)(376002)(136003)(346002)(6916009)(66946007)(36756003)(86362001)(52116002)(4326008)(186003)(478600001)(54906003)(316002)(44832011)(107886003)(66556008)(66476007)(83380400001)(2906002)(2616005)(5660300002)(1076003)(8676002)(8936002)(7416002);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 Wl67R7BXgm2Kne1+g0G7HD8rSzbEpc32N+TZTEuqFhsj64DKjurPLgcqhG8uvVesq6XaP9Xcqkxs9uEMYmvB2vxFxRUsadhpOZq2V/vdSa4PKq8rDpfVMZuXjOi6oiD7VG0jpdcH/ZYeE5tMi43nS49Gwp67o+MBiMOqzpvZFNK5eX7RbqZkp8IwHGI0MY0xErmeYGKIhbqcHqF28WtQxri4vdElBxqs18HtqFqVmBmEoYMHf/6gZbRZy+VPQZPe85D15UIpP5Dq5EQmOBSoHbpIR3WCC8C0PnIAKbF7yo0lRSgOLJLgwDoZxLkkeSHxWrFLTSRYxFbPntCUdDDuH24Iuj2pdjhOJvsgZkM+OSQ7PZ+tEEOkWIgAKxqLgsPpVQUpIUbKr5ojD7Kki+5FDNvd260x2VbJLzbGMHbAmRLMihmn4o4Z5hGEwfAyWQEywWprWEtpwjF6Sr6MVbYCmaqVPF0wo85JVvkxjgxPQy32z7Qo8FOT5Qlh1aUClcBDe4mk6CzedRv32qjpBalUgirx4LSwgOg0TgPm99MjaY/+cvrEXvI70+fXjKLkFwTnl1C7GD42jY7OUAL2EKlE6w+Xxv6+9r0yb5eHPHzWuyavSCuUeuXOp70rocBUbrrDbe21c665wI7VIYWbhlKGyxy9Rl04x1Qar7aIBWGxXegdmegcW9fRQOp1ZcYt0Sc4vuDhYjIasLB6JI9IgZzuHMl2Y8mkN67zpStdaoBZ72sbWV8uBPVB/DsRHMlBIOxDF63CoQS/+bqBlqvyqGDs+3ZoneYdhLARFGvTyj3GJiHapabaqYdIVfKISoLjJALKkqv/YD+L82QUetV7US0qxi9c8zk65nVEWDyRWmCL9JDHHnX0brnFMTuMCStU1YXk/wkAIwk1n2F2X1n4yH5fklECB1j5uc8/eyuX8wR2/+UXkhQH8kUnrGdmN0GI06O1rqTwKHRjcwFhDbwVmmLUAiFe0gnxdc/QwBTCyS5yx4/nAAAthtZ1U5/mdkS2CCtZC3MACjIALeq1VZwXJbUAZxyBhn9aCTT1hikojLYDHKkv+S/dTBV9x0DQyfELP4z114ClNN3Pa6wQ5WTa9VWwc0MISCYMDUyUj+Udz7QlGxr6c6v2z8xwU6/xTp1srZzKQO+yMFyx1WUspYuVNpJRMHcrbOOgPV9AhU83jk5khOKwlePuJ3yrbZVLdPLn3tnnQ3BqJJ26iTiJKjl/VEYjPjrNOMit+pPwnceebnij0IkV76jJXcKa3UUX7j1FDgb2OjfG4RojZUubaNQC8IatltL6KPkJEFKDL2VBhzW6X/0Ogxh56M9SKdCVUTdKjOETR4rztKdcBT6/ps7ImdOuEg==
X-OriginatorOrg: oracle.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 3337368d-fd3c-49b9-9fdd-08d8d3f4a587
X-MS-Exchange-CrossTenant-AuthSource: DM6PR10MB3148.namprd10.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 18 Feb 2021 10:04:57.7973
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 4e2c6054-71cb-48f1-bd6c-3a9705aca71b
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 SBLXitLIIedDA8W0WNTP3LZwDS9WePgOmgy8NA492/wW/hufO5vH1HD0aJXDcglot2f7uWCcc0InugpwxQvYB/Dl1wZZSj0RhRXF3M34jno=
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6PR10MB2427
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9898
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 mlxlogscore=999
 adultscore=0 mlxscore=0
 bulkscore=0 suspectscore=0 malwarescore=0 spamscore=0 phishscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2102180087
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9898
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 bulkscore=0
 suspectscore=0 mlxscore=0
 phishscore=0 spamscore=0 adultscore=0 clxscore=1011 impostorscore=0
 priorityscore=1501 lowpriorityscore=0 malwarescore=0 mlxlogscore=999
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2102180087
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When dumping the VMCS, retrieve the current guest value of EFER from
the kvm_vcpu structure if neither VM_EXIT_SAVE_IA32_EFER or
VM_ENTRY_LOAD_IA32_EFER is set, which can occur if the processor does
not support the relevant VM-exit/entry controls.

Fixes: 4eb64dce8d0a ("KVM: x86: dump VMCS on invalid entry")
Signed-off-by: David Edmondson <david.edmondson@oracle.com>
---
 arch/x86/kvm/vmx/vmx.c | 14 +++++++++-----
 arch/x86/kvm/vmx/vmx.h |  2 +-
 2 files changed, 10 insertions(+), 6 deletions(-)

```
#### [PATCH] vfio/iommu_type1: Fix duplicate included kthread.h
##### From: Tian Tao <tiantao6@hisilicon.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tian Tao <tiantao6@hisilicon.com>
X-Patchwork-Id: 12092859
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 27DCEC433DB
	for <kvm@archiver.kernel.org>; Thu, 18 Feb 2021 02:19:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 02B8E64E4B
	for <kvm@archiver.kernel.org>; Thu, 18 Feb 2021 02:19:06 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230071AbhBRCSu (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 17 Feb 2021 21:18:50 -0500
Received: from szxga04-in.huawei.com ([45.249.212.190]:12181 "EHLO
        szxga04-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S230064AbhBRCSt (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 17 Feb 2021 21:18:49 -0500
Received: from DGGEMS405-HUB.china.huawei.com (unknown [172.30.72.58])
        by szxga04-in.huawei.com (SkyGuard) with ESMTP id 4DgyxK6hxYzlLgj;
        Thu, 18 Feb 2021 10:16:05 +0800 (CST)
Received: from localhost.localdomain (10.69.192.56) by
 DGGEMS405-HUB.china.huawei.com (10.3.19.205) with Microsoft SMTP Server id
 14.3.498.0; Thu, 18 Feb 2021 10:17:58 +0800
From: Tian Tao <tiantao6@hisilicon.com>
To: <alex.williamson@redhat.com>, <cohuck@redhat.com>
CC: <kvm@vger.kernel.org>
Subject: [PATCH] vfio/iommu_type1: Fix duplicate included kthread.h
Date: Thu, 18 Feb 2021 10:17:29 +0800
Message-ID: <1613614649-59501-1-git-send-email-tiantao6@hisilicon.com>
X-Mailer: git-send-email 2.7.4
MIME-Version: 1.0
X-Originating-IP: [10.69.192.56]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

linux/kthread.h is included more than once, remove the one that isn't
necessary.

Signed-off-by: Tian Tao <tiantao6@hisilicon.com>
---
 drivers/vfio/vfio_iommu_type1.c | 1 -
 1 file changed, 1 deletion(-)

```
#### [RFC PATCH v5 01/19] af_vsock: update functions for connectible socket
##### From: Arseny Krasnov <arseny.krasnov@kaspersky.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Arseny Krasnov <arseny.krasnov@kaspersky.com>
X-Patchwork-Id: 12093147
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 02686C433DB
	for <kvm@archiver.kernel.org>; Thu, 18 Feb 2021 05:40:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B064260238
	for <kvm@archiver.kernel.org>; Thu, 18 Feb 2021 05:40:29 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230464AbhBRFj4 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 18 Feb 2021 00:39:56 -0500
Received: from mx12.kaspersky-labs.com ([91.103.66.155]:47046 "EHLO
        mx12.kaspersky-labs.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S231150AbhBRFhy (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 18 Feb 2021 00:37:54 -0500
Received: from relay12.kaspersky-labs.com (unknown [127.0.0.10])
        by relay12.kaspersky-labs.com (Postfix) with ESMTP id 099F875E97;
        Thu, 18 Feb 2021 08:36:53 +0300 (MSK)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=kaspersky.com;
        s=mail202102; t=1613626613;
        bh=pV0QvfBMinK5smHWRgbZ7HjLwewVO8NstcEoz6rw9iU=;
        h=From:To:Subject:Date:Message-ID:MIME-Version:Content-Type;
        b=ZGFbtOgoIK/TFWmMBeF4xvevKB1xP/Tine/jGsPDIKr+lF0I/je+Kp84m3HR4RfBE
         xC3elQGHXbnaqrK+sPWPsfEbLcgIPO1i+JgjWnY1WPnuV9gfxlW+KlqxUgYZYS1yQ2
         ilXV5rO+GDPjvbZz+ePb4E5yomqPgYA3qx46J+8RdF2vQeKTAEc7UHbz3LUyJncxYT
         2b+taMW37ZxOz4J137eNzwnQkwRXfqsfvgJiEFzKymkinCwT4cfjPzYzxLIKL6sW0y
         raHxOfb/ZsyXsASl3xyf4Z5Yu03jZcy+vTKhGivzSoUlnh4D57NjdaSqFpics/tSUL
         kllvZQCneav/w==
Received: from mail-hq2.kaspersky.com (unknown [91.103.66.206])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-SHA256 (128/128 bits))
        (Client CN "mail-hq2.kaspersky.com",
 Issuer "Kaspersky MailRelays CA G3" (verified OK))
        by mailhub12.kaspersky-labs.com (Postfix) with ESMTPS id 822D275F98;
        Thu, 18 Feb 2021 08:36:52 +0300 (MSK)
Received: from arseniy-pc.avp.ru (10.64.68.129) by hqmailmbx3.avp.ru
 (10.64.67.243) with Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256_P256) id 15.1.2044.4; Thu, 18
 Feb 2021 08:36:17 +0300
From: Arseny Krasnov <arseny.krasnov@kaspersky.com>
To: Stefan Hajnoczi <stefanha@redhat.com>,
        Stefano Garzarella <sgarzare@redhat.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Jason Wang <jasowang@redhat.com>,
        "David S. Miller" <davem@davemloft.net>,
        Jakub Kicinski <kuba@kernel.org>,
        Arseny Krasnov <arseny.krasnov@kaspersky.com>,
        Jorgen Hansen <jhansen@vmware.com>,
        Norbert Slusarek <nslusarek@gmx.net>,
        Colin Ian King <colin.king@canonical.com>,
        Andra Paraschiv <andraprs@amazon.com>
CC: <kvm@vger.kernel.org>, <virtualization@lists.linux-foundation.org>,
        <netdev@vger.kernel.org>, <linux-kernel@vger.kernel.org>,
        <stsp2@yandex.ru>, <oxffffaa@gmail.com>
Subject: [RFC PATCH v5 01/19] af_vsock: update functions for connectible
 socket
Date: Thu, 18 Feb 2021 08:36:03 +0300
Message-ID: <20210218053607.1066783-1-arseny.krasnov@kaspersky.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20210218053347.1066159-1-arseny.krasnov@kaspersky.com>
References: <20210218053347.1066159-1-arseny.krasnov@kaspersky.com>
MIME-Version: 1.0
X-Originating-IP: [10.64.68.129]
X-ClientProxiedBy: hqmailmbx2.avp.ru (10.64.67.242) To hqmailmbx3.avp.ru
 (10.64.67.243)
X-KSE-ServerInfo: hqmailmbx3.avp.ru, 9
X-KSE-AntiSpam-Interceptor-Info: scan successful
X-KSE-AntiSpam-Version: 5.9.16, Database issued on: 02/06/2021 23:52:08
X-KSE-AntiSpam-Status: KAS_STATUS_NOT_DETECTED
X-KSE-AntiSpam-Method: none
X-KSE-AntiSpam-Rate: 10
X-KSE-AntiSpam-Info: Lua profiles 161679 [Feb 06 2021]
X-KSE-AntiSpam-Info: LuaCore: 422 422 763e61bea9fcfcd94e075081cb96e065bc0509b4
X-KSE-AntiSpam-Info: Version: 5.9.16.0
X-KSE-AntiSpam-Info: Envelope from: arseny.krasnov@kaspersky.com
X-KSE-AntiSpam-Info: {Prob_from_in_msgid}
X-KSE-AntiSpam-Info: {Tracking_date, moscow}
X-KSE-AntiSpam-Info: {Tracking_from_domain_doesnt_match_to}
X-KSE-AntiSpam-Info: Rate: 10
X-KSE-AntiSpam-Info: Status: not_detected
X-KSE-AntiSpam-Info: Method: none
X-KSE-Antiphishing-Info: Clean
X-KSE-Antiphishing-ScanningType: Deterministic
X-KSE-Antiphishing-Method: None
X-KSE-Antiphishing-Bases: 02/06/2021 23:55:00
X-KSE-AttachmentFiltering-Interceptor-Info: no applicable attachment filtering
 rules found
X-KSE-Antivirus-Interceptor-Info: scan successful
X-KSE-Antivirus-Info: Clean, bases: 06.02.2021 21:17:00
X-KSE-BulkMessagesFiltering-Scan-Result: InTheLimit
X-KSE-AttachmentFiltering-Interceptor-Info: no applicable attachment filtering
 rules found
X-KSE-BulkMessagesFiltering-Scan-Result: InTheLimit
X-KLMS-Rule-ID: 52
X-KLMS-Message-Action: clean
X-KLMS-AntiSpam-Status: not scanned, disabled by settings
X-KLMS-AntiSpam-Interceptor-Info: not scanned
X-KLMS-AntiPhishing: Clean, bases: 2021/02/18 04:51:00
X-KLMS-AntiVirus: Kaspersky Security for Linux Mail Server, version 8.0.3.30,
 bases: 2021/02/18 04:31:00 #16269527
X-KLMS-AntiVirus-Status: Clean, skipped
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This prepares af_vsock.c for SEQPACKET support: some functions such
as setsockopt(), getsockopt(), connect(), recvmsg(), sendmsg() are
shared between both types of sockets, so rename them in general
manner.

Signed-off-by: Arseny Krasnov <arseny.krasnov@kaspersky.com>
---
 net/vmw_vsock/af_vsock.c | 64 +++++++++++++++++++++-------------------
 1 file changed, 34 insertions(+), 30 deletions(-)

```
#### [kvm-unit-tests PATCH 1/6] x86: nVMX: Verify unrestricted guest is supported in segment tests
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12092711
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 43474C433DB
	for <kvm@archiver.kernel.org>; Thu, 18 Feb 2021 00:23:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E97D564DEC
	for <kvm@archiver.kernel.org>; Thu, 18 Feb 2021 00:23:13 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230031AbhBRAXB (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 17 Feb 2021 19:23:01 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:34540 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S230018AbhBRAXA (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 17 Feb 2021 19:23:00 -0500
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id C5117C0613D6
        for <kvm@vger.kernel.org>; Wed, 17 Feb 2021 16:22:19 -0800 (PST)
Received: by mail-yb1-xb49.google.com with SMTP id j4so569624ybt.23
        for <kvm@vger.kernel.org>; Wed, 17 Feb 2021 16:22:19 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:reply-to:date:in-reply-to:message-id:mime-version:references
         :subject:from:to:cc;
        bh=PRyE4DuvxmKcKdm5ROiIEhCflgy/4d0H0JxsOnzUrZk=;
        b=aKznqUyu3qCbvyr9Jjmwnij/oFYrNnrZjcqBVtget+UuMDTnH52TPhLLszKagVon1w
         b3U7RMelO28y5X0QEUmYnqlzNl2E7/YUmBeXNWu3WMnGcK13dAmc3afYWDILLPsJYU84
         LTqW3EkOV6LN/SmX/2PTxoW36BTCbsqBsEdN0kIJgRiY6LNxWIrWKXwgjDe7aa3117ET
         ROmR2upAvSlV6RG2iDjKjLzNv06m3LwHUxk7bYKYKBOmndIO1jOGcdTrezclQsllcUEU
         rHIfy6mZij/Di8nqw9KpsrhMUXvJtFv6Z82/rnErz5c0WUKjVUO6lRHPeI2SdLb6ESkw
         j9AQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:reply-to:date:in-reply-to:message-id
         :mime-version:references:subject:from:to:cc;
        bh=PRyE4DuvxmKcKdm5ROiIEhCflgy/4d0H0JxsOnzUrZk=;
        b=RdjndschXnOF3xw44Q54TTh7NbFwD5CMLVR5sKXy0gyxpIM1JHmOMtptg8M4OtCj/d
         qe6916ZoPwQ8sWPhA92zhWOc7znMZ16wJRtJATv9YAxSyff572QAI3x6VZ5k9jnUBW3a
         iNYy6asi8cAN33+hYZSJdKMeZ1Xg7pYoNB88uElDo0KEF2wAeIlyB+6gD8laOeyzGlmv
         o9mQrfLSQQC3w39Bo0OHtEOAFA1xvVuwZ2WIrOwd33k4iakT2imeVfonhRNgYg19QWVx
         vWWwbzCApv+P7lwQmE4G/n5RbCqNbICXBP6pn/FmeeyenM2au8KRTpL1uVjHxrQGWx0D
         Tetg==
X-Gm-Message-State: AOAM530OotMmCBc3WdOiC1aOd1cUzarSjkPHmRMSY2TTs176f5DmX5Dl
        gyfKgc/9GuyZXlwu9hpl+YwdxNJDZaM=
X-Google-Smtp-Source: 
 ABdhPJyflWiTey/5gO0p/MU+xC5QuBxKNa5CJ3MQS718L2AxRFywQOTJgp42z3w4+6dHbgJgaGoN612yVRw=
Sender: "seanjc via sendgmr" <seanjc@seanjc798194.pdx.corp.google.com>
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:dc76:757f:9e9e:647c])
 (user=seanjc job=sendgmr) by 2002:a25:6e02:: with SMTP id
 j2mr2847972ybc.247.1613607739007;
 Wed, 17 Feb 2021 16:22:19 -0800 (PST)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Wed, 17 Feb 2021 16:22:07 -0800
In-Reply-To: <20210218002212.2904647-1-seanjc@google.com>
Message-Id: <20210218002212.2904647-2-seanjc@google.com>
Mime-Version: 1.0
References: <20210218002212.2904647-1-seanjc@google.com>
X-Mailer: git-send-email 2.30.0.478.g8a0d178c01-goog
Subject: [kvm-unit-tests PATCH 1/6] x86: nVMX: Verify unrestricted guest is
 supported in segment tests
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org, Krish Sadhukhan <krish.sadhukhan@oracle.com>,
        Sean Christopherson <seanjc@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Enhance enable_unrestricted_guest() to allow configuring a fully valid
EPT tree, and use the updated helper to verify unrestricted guest can be
enabled before testing SS segment properties that are specific to
unrestricted guest.

Fixes: 7820ac5 ("nVMX: Test Selector and Base Address fields of Guest Segment Registers on vmentry of nested guests")
Cc: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Signed-off-by: Sean Christopherson <seanjc@google.com>
---
 x86/vmx_tests.c | 21 +++++++++++++--------
 1 file changed, 13 insertions(+), 8 deletions(-)

```
