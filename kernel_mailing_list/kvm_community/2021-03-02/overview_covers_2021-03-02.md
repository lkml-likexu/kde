

#### [RFC v2 0/2] cgroup: New misc cgroup controller
##### From: Vipin Sharma <vipinsh@google.com>

```c
From patchwork Tue Mar  2 08:17:03 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vipin Sharma <vipinsh@google.com>
X-Patchwork-Id: 12111733
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 36ED8C4160E
	for <kvm@archiver.kernel.org>; Tue,  2 Mar 2021 15:57:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D01F164EF0
	for <kvm@archiver.kernel.org>; Tue,  2 Mar 2021 15:57:27 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1838890AbhCBPzI (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 2 Mar 2021 10:55:08 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:42470 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1376913AbhCBIRv (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 2 Mar 2021 03:17:51 -0500
Received: from mail-pl1-x64a.google.com (mail-pl1-x64a.google.com
 [IPv6:2607:f8b0:4864:20::64a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id B80BDC061794
        for <kvm@vger.kernel.org>; Tue,  2 Mar 2021 00:17:10 -0800 (PST)
Received: by mail-pl1-x64a.google.com with SMTP id k16so10782883plk.20
        for <kvm@vger.kernel.org>; Tue, 02 Mar 2021 00:17:10 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:message-id:mime-version:subject:from:to:cc;
        bh=J5nM/aBIL0ud17qxWddLzc4+65+ykqSEziPOIHoR18E=;
        b=CLaHSQRRQuhzlrNUHt+Ee6dvdh/pvhmKVL23Vm4bjLSGpL9t3yxCRmBAVgHL6lsIyn
         05iAFmfLfOZZR9GHkYRXKHrHC0SJlD8qUu+AAvO9gfMPcV4vhR646pp/hEvI68QeA2Mb
         DBYpEVQWeUFHdRFXaub06Vwhv8jjJysBUfgnKx9+1KwWwrDjmMYv+jozyxcKVieG9COH
         DE7ZHKblBdBpTi6HTjHtr7iiM5+8AIUrueg5HzDkJVCaHvkxaOHcB1vGO3bNgFMavgSK
         JIqmGJgz7qn0J+SwCsXUdzaYEdBIOPxEJJe80J4+INK+OSDVp9jhM5+vKb5bRxmRrTWt
         lYag==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:message-id:mime-version:subject:from
         :to:cc;
        bh=J5nM/aBIL0ud17qxWddLzc4+65+ykqSEziPOIHoR18E=;
        b=lfg1qDwYmV8AcpDJGqvQlPSTF6Ihz1PCDO6yCLAPr8kZuBAip2indueuV7NaYK8Yj6
         LjjCW5UIy23NxUpMCte7AwtGBP325Nf3UgIO1Pl+SqobCK3sicfxGEu20pY4wyBdom/h
         8I7KdlJlvxMzXRJ89D1lqhiUxxjLgn1ocKy60P2AskKpHnZimgELWK29NBBtkHl8oZ9q
         Wik/bviRn9N89Iywiv/TEztnSCuHG/dZm9xbdcPzzXvxO3nJMkzt/KHpLWzLMw4AWPVI
         FeCtxMyM3EDDnXLMSM4pPhQxuzEwn3TF9zy8ltFYpDquF0+ikcl9ejMQXYPFQpfJpM9P
         kf9Q==
X-Gm-Message-State: AOAM531X6pJVWqBhOqoXAZIVhsFn5dkWPh6T+Fl6ObUOlpfc9M+LzSvJ
        /aiDqvsnMms0lSw6d/pLXtc86tYZxjDo
X-Google-Smtp-Source: 
 ABdhPJxpzOEermj6hCTqHdZMYKkcNIjK+rfabJvpEhcLm7hTMoPzPtCdKtmgNr1eNEsnSiBD1DsDg2OTL89T
Sender: "vipinsh via sendgmr" <vipinsh@vipinsh.kir.corp.google.com>
X-Received: from vipinsh.kir.corp.google.com
 ([2620:0:1008:10:e829:dc2a:968a:1370])
 (user=vipinsh job=sendgmr) by 2002:a62:6585:0:b029:1b9:d8d9:1af2 with SMTP id
 z127-20020a6265850000b02901b9d8d91af2mr2296150pfb.17.1614673030058; Tue, 02
 Mar 2021 00:17:10 -0800 (PST)
Date: Tue,  2 Mar 2021 00:17:03 -0800
Message-Id: <20210302081705.1990283-1-vipinsh@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.30.1.766.gb4fecdf3b7-goog
Subject: [RFC v2 0/2] cgroup: New misc cgroup controller
From: Vipin Sharma <vipinsh@google.com>
To: tj@kernel.org, mkoutny@suse.com, rdunlap@infradead.org,
        thomas.lendacky@amd.com, brijesh.singh@amd.com, jon.grimm@amd.com,
        eric.vantassell@amd.com, pbonzini@redhat.com, hannes@cmpxchg.org,
        frankja@linux.ibm.com, borntraeger@de.ibm.com
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

Hello

This patch series is creating a new misc cgroup controller for limiting
and tracking of resources which are not abstract like other cgroup
controllers.

This controller was initially proposed as encryption_id but after
the feedbacks, it is now changed to misc cgroup.
https://lore.kernel.org/lkml/20210108012846.4134815-2-vipinsh@google.com/

Changes in RFC v2:
1. Documentation fixes.
2. Added kernel log messages.
3. Changed charge API to treat misc_cg as input parameter.
4. Added helper APIs to get and release references on the cgroup.

[1] https://lore.kernel.org/lkml/20210218195549.1696769-1-vipinsh@google.com
Vipin Sharma (2):
  cgroup: sev: Add misc cgroup controller
  cgroup: sev: Miscellaneous cgroup documentation.

 Documentation/admin-guide/cgroup-v1/index.rst |   1 +
 Documentation/admin-guide/cgroup-v1/misc.rst  |   4 +
 Documentation/admin-guide/cgroup-v2.rst       |  69 ++-
 arch/x86/kvm/svm/sev.c                        |  65 ++-
 arch/x86/kvm/svm/svm.h                        |   1 +
 include/linux/cgroup_subsys.h                 |   4 +
 include/linux/misc_cgroup.h                   | 122 +++++
 init/Kconfig                                  |  14 +
 kernel/cgroup/Makefile                        |   1 +
 kernel/cgroup/misc.c                          | 423 ++++++++++++++++++
 10 files changed, 692 insertions(+), 12 deletions(-)
 create mode 100644 Documentation/admin-guide/cgroup-v1/misc.rst
 create mode 100644 include/linux/misc_cgroup.h
 create mode 100644 kernel/cgroup/misc.c
```
#### [kvm-unit-tests PATCH v4 0/3] s390x: mvpg test
##### From: Claudio Imbrenda <imbrenda@linux.ibm.com>

```c
From patchwork Tue Mar  2 11:41:04 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Claudio Imbrenda <imbrenda@linux.ibm.com>
X-Patchwork-Id: 12111747
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E9CFDC43603
	for <kvm@archiver.kernel.org>; Tue,  2 Mar 2021 16:07:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BA6DD64F14
	for <kvm@archiver.kernel.org>; Tue,  2 Mar 2021 16:07:09 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1449029AbhCBQDg (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 2 Mar 2021 11:03:36 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:32962 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1379954AbhCBLzk (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 2 Mar 2021 06:55:40 -0500
Received: from pps.filterd (m0187473.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 122BXMXP036655
        for <kvm@vger.kernel.org>; Tue, 2 Mar 2021 06:41:14 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=7PZgR+6w3Q+iyqOLwhgPHcOOjdby5a4K82j+edNuU6s=;
 b=bl71tMlkf0vufG2oazxMhPuJ5X8hYd1KbITvPZ/X9KWKAUA9YR04OzofcJz7/l0IGb4I
 JcXHS0+ZhgQ+hFlmP7qx69xFJxSO8DhA5s2o37vMOUdl4yQr08uUjAxukP9++whs0mIX
 OeHXbzwVjMKM/+1CjUVDU1Y98myXztJqfMKxLHC/c2M9nRTgtW7I359K+DR9YcWskGIw
 N/XQdkBeYcywmHYaozr8QbwvwZHJHESXx5ggTIEgjE2FjudkdIsJAX9yIog4AYFz4FFJ
 5ZgGXaCoYp5x9YagYaf1Txa7WqL0ApUv9FgDh0Qz49GhEL5+Z+tKlGVFNxz/F1CGC/eQ 7A==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 371mjp88fd-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT)
        for <kvm@vger.kernel.org>; Tue, 02 Mar 2021 06:41:13 -0500
Received: from m0187473.ppops.net (m0187473.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 122BXTG0037617
        for <kvm@vger.kernel.org>; Tue, 2 Mar 2021 06:41:13 -0500
Received: from ppma04ams.nl.ibm.com (63.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.99])
        by mx0a-001b2d01.pphosted.com with ESMTP id 371mjp88em-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 02 Mar 2021 06:41:13 -0500
Received: from pps.filterd (ppma04ams.nl.ibm.com [127.0.0.1])
        by ppma04ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 122BbBC1009192;
        Tue, 2 Mar 2021 11:41:11 GMT
Received: from b06cxnps3075.portsmouth.uk.ibm.com
 (d06relay10.portsmouth.uk.ibm.com [9.149.109.195])
        by ppma04ams.nl.ibm.com with ESMTP id 3712fmgsqu-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 02 Mar 2021 11:41:10 +0000
Received: from d06av26.portsmouth.uk.ibm.com (d06av26.portsmouth.uk.ibm.com
 [9.149.105.62])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 122Bf8Vv49086878
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 2 Mar 2021 11:41:08 GMT
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 26412AE051;
        Tue,  2 Mar 2021 11:41:08 +0000 (GMT)
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id BE7B9AE053;
        Tue,  2 Mar 2021 11:41:07 +0000 (GMT)
Received: from ibm-vm.ibmuc.com (unknown [9.145.10.194])
        by d06av26.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue,  2 Mar 2021 11:41:07 +0000 (GMT)
From: Claudio Imbrenda <imbrenda@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: david@redhat.com, thuth@redhat.com, frankja@linux.ibm.com,
        cohuck@redhat.com, pmorel@linux.ibm.com, borntraeger@de.ibm.com
Subject: [kvm-unit-tests PATCH v4 0/3] s390x: mvpg test
Date: Tue,  2 Mar 2021 12:41:04 +0100
Message-Id: <20210302114107.501837-1-imbrenda@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.761
 definitions=2021-03-02_03:2021-03-01,2021-03-02 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 lowpriorityscore=0
 adultscore=0 suspectscore=0 mlxlogscore=931 spamscore=0 malwarescore=0
 phishscore=0 clxscore=1015 priorityscore=1501 bulkscore=0 impostorscore=0
 mlxscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2103020098
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

A simple unit test for the MVPG instruction.

The timeout is set to 10 seconds because the test should complete in a
fraction of a second even on busy machines. If the test is run in VSIE
and the host of the host is not handling MVPG properly, the test will
probably hang.

Testing MVPG behaviour in VSIE is the main motivation for this test.

Anything related to storage keys is not tested.

v3->v4
* add memset after the first successful mvpg to make sure memory is really
  copied successfully
* add a comment and an additional prefix to the tests skipped when running
  in TCG

v2->v3
* fix copyright (2020 is over!)
* add the third patch to skip some known issues when running in TCG

v1->v2
* droppped patch 2 which introduced is_pgm();
* patch 1: replace a hardcoded value with the new macro SVC_LEAVE_PSTATE
* patch 2: clear_pgm_int() returns the old value, use that instad of is_pgm()

Claudio Imbrenda (3):
  s390x: introduce leave_pstate to leave userspace
  s390x: mvpg: simple test
  s390x: mvpg: skip some tests when using TCG

 s390x/Makefile           |   1 +
 lib/s390x/asm/arch_def.h |   7 +
 lib/s390x/interrupt.c    |  12 +-
 s390x/mvpg.c             | 277 +++++++++++++++++++++++++++++++++++++++
 s390x/unittests.cfg      |   4 +
 5 files changed, 299 insertions(+), 2 deletions(-)
 create mode 100644 s390x/mvpg.c
```
#### [Patch v8 00/10] vfio: expose virtual Shared Virtual Addressing to
##### From: Liu Yi L <yi.l.liu@intel.com>

```c
From patchwork Tue Mar  2 20:35:35 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Liu Yi L <yi.l.liu@intel.com>
X-Patchwork-Id: 12111759
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.7 required=3.0 tests=BAYES_00,
	DATE_IN_FUTURE_03_06,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 9EB7DC28D13
	for <kvm@archiver.kernel.org>; Tue,  2 Mar 2021 16:07:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6E0D664F17
	for <kvm@archiver.kernel.org>; Tue,  2 Mar 2021 16:07:11 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1575915AbhCBQEo (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 2 Mar 2021 11:04:44 -0500
Received: from mga06.intel.com ([134.134.136.31]:20180 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1444870AbhCBMlY (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 2 Mar 2021 07:41:24 -0500
IronPort-SDR: 
 OZF29G6vnbznlkSb3whUu3ug+ygNTTMM3k9W0cFp9SwAoAH09b3Z2iPAIWn16z+pkc9/mGHqL7
 EQirb3VJGhLw==
X-IronPort-AV: E=McAfee;i="6000,8403,9910"; a="248204697"
X-IronPort-AV: E=Sophos;i="5.81,216,1610438400";
   d="scan'208";a="248204697"
Received: from fmsmga004.fm.intel.com ([10.253.24.48])
  by orsmga104.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 02 Mar 2021 04:36:47 -0800
IronPort-SDR: 
 /P+Qc/iEKgAQks6WSjR7kEqlqYljDwvgWcGDkQl4X/J8RtV0FH1TNS4nMoqLEy2E0DNSOVfSYm
 MbkLpwsVgXMg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.81,216,1610438400";
   d="scan'208";a="427471978"
Received: from yiliu-dev.bj.intel.com (HELO dual-ub.bj.intel.com)
 ([10.238.156.135])
  by fmsmga004.fm.intel.com with ESMTP; 02 Mar 2021 04:36:42 -0800
From: Liu Yi L <yi.l.liu@intel.com>
To: alex.williamson@redhat.com, eric.auger@redhat.com,
        baolu.lu@linux.intel.com, joro@8bytes.org
Cc: kevin.tian@intel.com, jacob.jun.pan@linux.intel.com,
        ashok.raj@intel.com, yi.l.liu@intel.com, jun.j.tian@intel.com,
        yi.y.sun@intel.com, jean-philippe@linaro.org, peterx@redhat.com,
        jasowang@redhat.com, hao.wu@intel.com, stefanha@gmail.com,
        iommu@lists.linux-foundation.org, kvm@vger.kernel.org,
        jgg@nvidia.com, Lingshan.Zhu@intel.com, vivek.gautam@arm.com
Subject: [Patch v8 00/10] vfio: expose virtual Shared Virtual Addressing to
 VMs
Date: Wed,  3 Mar 2021 04:35:35 +0800
Message-Id: <20210302203545.436623-1-yi.l.liu@intel.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Shared Virtual Addressing (SVA), a.k.a, Shared Virtual Memory (SVM) on
Intel platforms allows address space sharing between device DMA and
applications. SVA can reduce programming complexity and enhance security.

This VFIO series is intended to expose SVA usage to VMs. i.e. Sharing
guest application address space with passthru devices. This is called
vSVA in this series. The whole vSVA enabling requires QEMU/VFIO/IOMMU
changes. For IOMMU and QEMU changes, they are in separate series (listed
in the "Related series").

The high-level architecture for SVA virtualization is as below, the key
design of vSVA support is to utilize the dual-stage IOMMU translation (
also known as IOMMU nesting translation) capability in host IOMMU.


    .-------------.  .---------------------------.
    |   vIOMMU    |  | Guest process CR3, FL only|
    |             |  '---------------------------'
    .----------------/
    | PASID Entry |--- PASID cache flush -
    '-------------'                       |
    |             |                       V
    |             |                CR3 in GPA
    '-------------'
Guest
------| Shadow |--------------------------|--------
      v        v                          v
Host
    .-------------.  .----------------------.
    |   pIOMMU    |  | Bind FL for GVA-GPA  |
    |             |  '----------------------'
    .----------------/  |
    | PASID Entry |     V (Nested xlate)
    '----------------\.------------------------------.
    |             |   |SL for GPA-HPA, default domain|
    |             |   '------------------------------'
    '-------------'
Where:
 - FL = First level/stage one page tables
 - SL = Second level/stage two page tables

This patch series has been updated regards to the disscussion around PASID
allocation in v7 [1]. This series has removed the PASID allocation, and
adapted to the /dev/ioasid solution [2]. Therefore the patches in this series
has been re-ordered. And the Patch Overview is as below:

 1. reports IOMMU nesting info to userspace ( patch 0001, 0002, 0003, 0010)
 2. vfio support for binding guest page table to host (patch 0004)
 3. vfio support for IOMMU cache invalidation from VMs (patch 0005)
 4. vfio support for vSVA usage on IOMMU-backed mdevs (patch 0006, 0007)
 5. expose PASID capability to VM (patch 0008)
 6. add doc for VFIO dual stage control (patch 0009)

The complete vSVA kernel upstream patches are divided into three phases:
    1. Common APIs and PCI device direct assignment
    2. IOMMU-backed Mediated Device assignment
    3. Page Request Services (PRS) support

This patchset is aiming for the phase 1 and phase 2. And it has dependency on IOASID
extension from Jacobd Pan [3]. Complete set for current vSVA kernel and QEMU can be
found in [4] and [5].

[1] https://lore.kernel.org/kvm/DM5PR11MB14351121729909028D6EB365C31D0@DM5PR11MB1435.namprd11.prod.outlook.com/
[2] https://lore.kernel.org/linux-iommu/1614463286-97618-19-git-send-email-jacob.jun.pan@linux.intel.com/
[3] https://lore.kernel.org/linux-iommu/1614463286-97618-1-git-send-email-jacob.jun.pan@linux.intel.com/
[4] https://github.com/jacobpan/linux/tree/vsva-linux-5.12-rc1-v8
[5] https://github.com/luxis1999/qemu/tree/vsva_5.12_rc1_qemu_rfcv11

Regards,
Yi Liu

Changelog:
	- Patch v7 -> Patch v8:
	  a) removed the PASID allocation out of this series, it is covered by below patch:
	     https://lore.kernel.org/linux-iommu/1614463286-97618-19-git-send-email-jacob.jun.pan@linux.intel.com/
	  Patch v7: https://lore.kernel.org/kvm/1599734733-6431-1-git-send-email-yi.l.liu@intel.com/

	- Patch v6 -> Patch v7:
	  a) drop [PATCH v6 01/15] of v6 as it's merged by Alex.
	  b) rebase on Jacob's v8 IOMMU uapi enhancement and v2 IOASID extension patchset.
	  c) Address comments against v6 from Alex and Eric.
	  Patch v6: https://lore.kernel.org/kvm/1595917664-33276-1-git-send-email-yi.l.liu@intel.com/

	- Patch v5 -> Patch v6:
	  a) Address comments against v5 from Eric.
	  b) rebase on Jacob's v6 IOMMU uapi enhancement
	  Patch v5: https://lore.kernel.org/kvm/1594552870-55687-1-git-send-email-yi.l.liu@intel.com/

	- Patch v4 -> Patch v5:
	  a) Address comments against v4
	  Patch v4: https://lore.kernel.org/kvm/1593861989-35920-1-git-send-email-yi.l.liu@intel.com/

	- Patch v3 -> Patch v4:
	  a) Address comments against v3
	  b) Add rb from Stefan on patch 14/15
	  Patch v3: https://lore.kernel.org/kvm/1592988927-48009-1-git-send-email-yi.l.liu@intel.com/

	- Patch v2 -> Patch v3:
	  a) Rebase on top of Jacob's v3 iommu uapi patchset
	  b) Address comments from Kevin and Stefan Hajnoczi
	  c) Reuse DOMAIN_ATTR_NESTING to get iommu nesting info
	  d) Drop [PATCH v2 07/15] iommu/uapi: Add iommu_gpasid_unbind_data
	  Patch v2: https://lore.kernel.org/kvm/1591877734-66527-1-git-send-email-yi.l.liu@intel.com/

	- Patch v1 -> Patch v2:
	  a) Refactor vfio_iommu_type1_ioctl() per suggestion from Christoph
	     Hellwig.
	  b) Re-sequence the patch series for better bisect support.
	  c) Report IOMMU nesting cap info in detail instead of a format in
	     v1.
	  d) Enforce one group per nesting type container for vfio iommu type1
	     driver.
	  e) Build the vfio_mm related code from vfio.c to be a separate
	     vfio_pasid.ko.
	  f) Add PASID ownership check in IOMMU driver.
	  g) Adopted to latest IOMMU UAPI design. Removed IOMMU UAPI version
	     check. Added iommu_gpasid_unbind_data for unbind requests from
	     userspace.
	  h) Define a single ioctl:VFIO_IOMMU_NESTING_OP for bind/unbind_gtbl
	     and cahce_invld.
	  i) Document dual stage control in vfio.rst.
	  Patch v1: https://lore.kernel.org/kvm/1584880325-10561-1-git-send-email-yi.l.liu@intel.com/

	- RFC v3 -> Patch v1:
	  a) Address comments to the PASID request(alloc/free) path
	  b) Report PASID alloc/free availabitiy to user-space
	  c) Add a vfio_iommu_type1 parameter to support pasid quota tuning
	  d) Adjusted to latest ioasid code implementation. e.g. remove the
	     code for tracking the allocated PASIDs as latest ioasid code
	     will track it, VFIO could use ioasid_free_set() to free all
	     PASIDs.
	  RFC v3: https://lore.kernel.org/kvm/1580299912-86084-1-git-send-email-yi.l.liu@intel.com/

	- RFC v2 -> v3:
	  a) Refine the whole patchset to fit the roughly parts in this series
	  b) Adds complete vfio PASID management framework. e.g. pasid alloc,
	  free, reclaim in VM crash/down and per-VM PASID quota to prevent
	  PASID abuse.
	  c) Adds IOMMU uAPI version check and page table format check to ensure
	  version compatibility and hardware compatibility.
	  d) Adds vSVA vfio support for IOMMU-backed mdevs.
	  RFC v2: https://lore.kernel.org/kvm/1571919983-3231-1-git-send-email-yi.l.liu@intel.com/

	- RFC v1 -> v2:
	  Dropped vfio: VFIO_IOMMU_ATTACH/DETACH_PASID_TABLE.
	  RFC v1: https://lore.kernel.org/kvm/1562324772-3084-1-git-send-email-yi.l.liu@intel.com/
---
Eric Auger (1):
  vfio: Document dual stage control

Liu Yi L (8):
  iommu: Report domain nesting info
  iommu/smmu: Report empty domain nesting info
  vfio/type1: Report iommu nesting info to userspace
  vfio/type1: Support binding guest page tables to PASID
  vfio/type1: Allow invalidating first-level/stage IOMMU cache
  vfio/type1: Add vSVA support for IOMMU-backed mdevs
  vfio/pci: Expose PCIe PASID capability to userspace
  iommu/vt-d: Support reporting nesting capability info

Yi Sun (1):
  iommu: Pass domain to sva_unbind_gpasid()

 Documentation/driver-api/vfio.rst           |  77 +++++
 Documentation/userspace-api/iommu.rst       |   5 +-
 drivers/iommu/arm/arm-smmu-v3/arm-smmu-v3.c |  29 +-
 drivers/iommu/arm/arm-smmu/arm-smmu.c       |  29 +-
 drivers/iommu/intel/cap_audit.h             |   7 +
 drivers/iommu/intel/iommu.c                 |  68 ++++-
 drivers/iommu/intel/svm.c                   |   3 +-
 drivers/iommu/iommu.c                       |   2 +-
 drivers/vfio/pci/vfio_pci_config.c          |   2 +-
 drivers/vfio/vfio_iommu_type1.c             | 321 +++++++++++++++++++-
 include/linux/intel-iommu.h                 |   3 +-
 include/linux/iommu.h                       |   3 +-
 include/uapi/linux/iommu.h                  |  72 +++++
 include/uapi/linux/vfio.h                   |  57 ++++
 14 files changed, 651 insertions(+), 27 deletions(-)
```
#### [RFC v11 00/25] intel_iommu: expose Shared Virtual Addressing to VMs
##### From: Liu Yi L <yi.l.liu@intel.com>

```c
From patchwork Tue Mar  2 20:38:02 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Liu Yi L <yi.l.liu@intel.com>
X-Patchwork-Id: 12111763
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.7 required=3.0 tests=BAYES_00,
	DATE_IN_FUTURE_03_06,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 2904DC28CC5
	for <kvm@archiver.kernel.org>; Tue,  2 Mar 2021 16:07:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id F165864F14
	for <kvm@archiver.kernel.org>; Tue,  2 Mar 2021 16:07:10 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1449110AbhCBQE1 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 2 Mar 2021 11:04:27 -0500
Received: from mga04.intel.com ([192.55.52.120]:29670 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1444907AbhCBMlX (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 2 Mar 2021 07:41:23 -0500
IronPort-SDR: 
 IV/PHukfCWqXcKNDaSQu768qIeCT/orpLZATVl6cjSb4UBv+X3xEKZWx4u6aUKvPeVgo8i2Chl
 z/Tsld6YVirQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9910"; a="184363115"
X-IronPort-AV: E=Sophos;i="5.81,216,1610438400";
   d="scan'208";a="184363115"
Received: from fmsmga004.fm.intel.com ([10.253.24.48])
  by fmsmga104.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 02 Mar 2021 04:39:27 -0800
IronPort-SDR: 
 EjvOZzD0TPPiJusCauhC+4vlQW0ZZc8zSpZ9FXH/5Dat8RMJemU89uSJIP0efeaM4gBoYCocqB
 rQbkbLBTgidQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.81,216,1610438400";
   d="scan'208";a="427472642"
Received: from yiliu-dev.bj.intel.com (HELO dual-ub.bj.intel.com)
 ([10.238.156.135])
  by fmsmga004.fm.intel.com with ESMTP; 02 Mar 2021 04:39:23 -0800
From: Liu Yi L <yi.l.liu@intel.com>
To: qemu-devel@nongnu.org, alex.williamson@redhat.com,
        peterx@redhat.com, jasowang@redhat.com
Cc: mst@redhat.com, pbonzini@redhat.com, eric.auger@redhat.com,
        david@gibson.dropbear.id.au, jean-philippe@linaro.org,
        kevin.tian@intel.com, yi.l.liu@intel.com, jun.j.tian@intel.com,
        yi.y.sun@intel.com, hao.wu@intel.com, kvm@vger.kernel.org,
        Lingshan.Zhu@intel.com
Subject: [RFC v11 00/25] intel_iommu: expose Shared Virtual Addressing to VMs
Date: Wed,  3 Mar 2021 04:38:02 +0800
Message-Id: <20210302203827.437645-1-yi.l.liu@intel.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Shared Virtual Addressing (SVA), a.k.a, Shared Virtual Memory (SVM) on
Intel platforms allows address space sharing between device DMA and
applications. SVA can reduce programming complexity and enhance security.

This QEMU series is intended to expose SVA usage to VMs. i.e. Sharing
guest application address space with passthru devices. This is called
vSVA in this series. The whole vSVA enabling requires QEMU/VFIO/IOMMU
changes.

The high-level architecture for SVA virtualization is as below, the key
design of vSVA support is to utilize the dual-stage IOMMU translation (
also known as IOMMU nesting translation) capability in host IOMMU.

    .-------------.  .---------------------------.
    |   vIOMMU    |  | Guest process CR3, FL only|
    |             |  '---------------------------'
    .----------------/
    | PASID Entry |--- PASID cache flush -
    '-------------'                       |
    |             |                       V
    |             |                CR3 in GPA
    '-------------'
Guest
------| Shadow |--------------------------|--------
      v        v                          v
Host
    .-------------.  .----------------------.
    |   pIOMMU    |  | Bind FL for GVA-GPA  |
    |             |  '----------------------'
    .----------------/  |
    | PASID Entry |     V (Nested xlate)
    '----------------\.------------------------------.
    |             |   |SL for GPA-HPA, default domain|
    |             |   '------------------------------'
    '-------------'
Where:
 - FL = First level/stage one page tables
 - SL = Second level/stage two page tables

The complete vSVA kernel upstream patches are divided into three phases:
    1. Common APIs and PCI device direct assignment
    2. IOMMU-backed Mediated Device assignment
    3. Page Request Services (PRS) support

This QEMU patchset is aiming for the phase 1 and phase 2. Compared with
last version, the major change in this series is the PASID allocation.
Instead of utilizing VFIO's uAPI to request PASID from kernel, this
series uses /dev/ioasid uAPI to do it. For the reason of the change, please
refer to [1]. This series is based on two kernel series [2] and [3] posted
earlier.

Patch Overview:
 1. patch 0001 - 0003: update kernel header files
 2. patch 0004 - 0008: select VFIO_TYPE1_NESTING_IOMMU for vIOMMU built
                       on IOMMU nesting translation.
 3. patch 0009 - 0013: introduce HostIOMMUContext, and implements in VFIO.
 4. patch 0014       : IOMMU nesting capability sync between vIOMMU and host.
 5. patch 0015       : PASID allocation/free support in Intel vIOMMU.
 6. patch 0016 - 0017: PASID cache management for Intel vIOMMU.
 7. patch 0018 - 0020: bind guest page table to host.
 8. patch 0021 - 0024: flush first level/stage cache for vIOMMU.
 9. patch 0025       : expose SVA to VM by x-scalable-mode="modern"

The complete QEMU set can be found in [4], and complete kernel can be found
in [5].

Tests: basci vSVA functionality test, VM reboot/shutdown/crash, kernel build in
guest, boot VM with vSVA disabled, full comapilation with all archs, passthru
entire PCI device, passthru Scalable IOV ADI.

[1] https://lore.kernel.org/kvm/DM5PR11MB14351121729909028D6EB365C31D0@DM5PR11MB1435.namprd11.prod.outlook.com/
[2] https://lore.kernel.org/linux-iommu/20210302203545.436623-1-yi.l.liu@intel.com/
[3] https://lore.kernel.org/linux-iommu/1614463286-97618-1-git-send-email-jacob.jun.pan@linux.intel.com/
[4] https://github.com/jacobpan/linux/tree/vsva-linux-5.12-rc1-v8
[5] https://github.com/luxis1999/qemu/tree/vsva_5.12_rc1_qemu_rfcv11

Regards,
Yi Liu

Changelog:
	- RFC v10 -> RFC v11:
	  a) Rebase to latest kernel implementation (5.12-rc1 vsva v8) and adopt to /dev/ioasid for
	     requesting PASID from host.
	  RFC v10: https://lore.kernel.org/qemu-devel/1599735398-6829-1-git-send-email-yi.l.liu@intel.com/

	- RFC v9 -> RFC v10:
	  a) Rebase to latest kernel implementation (5.9-rc2 vsva v7)
	  RFC v9: https://lore.kernel.org/kvm/1595918058-33392-1-git-send-email-yi.l.liu@intel.com/

	- RFC v8 -> RFC v9:
	  a) Rebase to latest kernel implementation (5.8-rc6 vsva v6)
	  RFC v8: https://lore.kernel.org/kvm/1594553181-55810-1-git-send-email-yi.l.liu@intel.com/

	- RFC v7 -> RFC v8:
	  a) Rebase to latest kernel implementation (5.8-rc3 vsva v5)
	  RFC v7: https://lore.kernel.org/kvm/1593862609-36135-1-git-send-email-yi.l.liu@intel.com/

	- RFC v6 -> RFC v7:
	  a) Rebase to latest kernel implementation (5.8-rc3 vsva)
	  RFC v6: https://lore.kernel.org/kvm/1591880064-30638-1-git-send-email-yi.l.liu@intel.com/

	- RFC v5 -> RFC v6:
	  a) Use RFC instead of formal patch as kernel patch is in progress.
	  b) Address comments from Peter and Eric.
	  c) Add get_iommu_attr() to advertise vIOMMU nesting requirement to
	     VFIO.
	  d) Update per latest kernel UAPI definition.
	  e) Add patch 0017 to check iommu nesting cap info in set_iommu().
	  RFC v5: https://www.spinics.net/lists/kvm/msg211475.html

	- RFC v4 -> RFC v5:
	  a) Refactor the vfio HostIOMMUContext init code (patch 0008 - 0009 of v1 series)
	  b) Refactor the pasid binding handling (patch 0011 - 0016 of v1 series)
	  RFC v4: https://patchwork.ozlabs.org/cover/1259648/

	- RFC v3.1 -> RFC v4:
	  a) Implement HostIOMMUContext in QOM manner.
	  b) Add pci_set/unset_iommu_context() to register HostIOMMUContext to
	     vIOMMU, thus the lifecircle of HostIOMMUContext is awared in vIOMMU
	     side. In such way, vIOMMU could use the methods provided by the
	     HostIOMMUContext safely.
	  c) Add back patch "[RFC v3 01/25] hw/pci: modify pci_setup_iommu() to set PCIIOMMUOps"
	  RFCv3.1: https://patchwork.kernel.org/cover/11397879/

	- RFC v3 -> v3.1:
	  a) Drop IOMMUContext, and rename DualStageIOMMUObject to HostIOMMUContext.
	     HostIOMMUContext is per-vfio-container, it is exposed to  vIOMMU via PCI
	     layer. VFIO registers a PCIHostIOMMUFunc callback to PCI layer, vIOMMU
	     could get HostIOMMUContext instance via it.
	  b) Check IOMMU uAPI version by VFIO_CHECK_EXTENSION
	  c) Add a check on VFIO_PASID_REQ availability via VFIO_GET_IOMMU_IHNFO
	  d) Reorder the series, put vSVA linux header file update in the beginning
	     put the x-scalable-mode option mofification in the end of the series.
	  e) Dropped patch "[RFC v3 01/25] hw/pci: modify pci_setup_iommu() to set PCIIOMMUOps"
	  RFCv3: https://patchwork.kernel.org/cover/11356033/

	- RFC v2 -> v3:
	  a) Introduce DualStageIOMMUObject to abstract the host IOMMU programming
	  capability. e.g. request PASID from host, setup IOMMU nesting translation
	  on host IOMMU. The pasid_alloc/bind_guest_page_table/iommu_cache_flush
	  operations are moved to be DualStageIOMMUOps. Thus, DualStageIOMMUObject
	  is an abstract layer which provides QEMU vIOMMU emulators with an explicit
	  method to program host IOMMU.
	  b) Compared with RFC v2, the IOMMUContext has also been updated. It is
	  modified to provide an abstract for vIOMMU emulators. It provides the
	  method for pass-through modules (like VFIO) to communicate with host IOMMU.
	  e.g. tell vIOMMU emulators about the IOMMU nesting capability on host side
	  and report the host IOMMU DMA translation faults to vIOMMU emulators.
	  RFC v2: https://www.spinics.net/lists/kvm/msg198556.html

	- RFC v1 -> v2:
	  Introduce IOMMUContext to abstract the connection between VFIO
	  and vIOMMU emulators, which is a replacement of the PCIPASIDOps
	  in RFC v1. Modify x-scalable-mode to be string option instead of
	  adding a new option as RFC v1 did. Refined the pasid cache management
	  and addressed the TODOs mentioned in RFC v1. 
	  RFC v1: https://patchwork.kernel.org/cover/11033657/
---
Eric Auger (1):
  scripts/update-linux-headers: Import iommu.h

Liu Yi L (24):
  scripts/update-linux-headers: Import ioasid.h
  header file update VFIO/IOMMU vSVA APIs kernel 5.12-rc1
  hw/pci: modify pci_setup_iommu() to set PCIIOMMUOps
  hw/pci: introduce pci_device_get_iommu_attr()
  intel_iommu: add get_iommu_attr() callback
  vfio: pass nesting requirement into vfio_get_group()
  vfio: check VFIO_TYPE1_NESTING_IOMMU support
  hw/iommu: introduce HostIOMMUContext
  hw/pci: introduce pci_device_set/unset_iommu_context()
  intel_iommu: add set/unset_iommu_context callback
  vfio: add HostIOMMUContext support
  vfio: init HostIOMMUContext per-container
  intel_iommu: sync IOMMU nesting cap info for assigned devices
  intel_iommu: add virtual command capability support
  intel_iommu: process PASID cache invalidation
  intel_iommu: add PASID cache management infrastructure
  intel_iommu: bind/unbind guest page table to host
  intel_iommu: replay pasid binds after context cache invalidation
  intel_iommu: do not pass down pasid bind for PASID #0
  vfio: add support for flush iommu stage-1 cache
  intel_iommu: process PASID-based iotlb invalidation
  intel_iommu: propagate PASID-based iotlb invalidation to host
  intel_iommu: process PASID-based Device-TLB invalidation
  intel_iommu: modify x-scalable-mode to be string option

 hw/Kconfig                            |    3 +
 hw/alpha/typhoon.c                    |    6 +-
 hw/arm/smmu-common.c                  |    6 +-
 hw/hppa/dino.c                        |    6 +-
 hw/i386/amd_iommu.c                   |    6 +-
 hw/i386/intel_iommu.c                 | 1279 ++++++++++++++++++++++++-
 hw/i386/intel_iommu_internal.h        |  132 +++
 hw/i386/trace-events                  |    6 +
 hw/iommu/Kconfig                      |    4 +
 hw/iommu/host_iommu_context.c         |  125 +++
 hw/iommu/meson.build                  |    6 +
 hw/meson.build                        |    1 +
 hw/pci-host/designware.c              |    6 +-
 hw/pci-host/pnv_phb3.c                |    6 +-
 hw/pci-host/pnv_phb4.c                |    6 +-
 hw/pci-host/ppce500.c                 |    6 +-
 hw/pci-host/prep.c                    |    6 +-
 hw/pci-host/sabre.c                   |    6 +-
 hw/pci/pci.c                          |   73 +-
 hw/ppc/ppc440_pcix.c                  |    6 +-
 hw/ppc/spapr_pci.c                    |    6 +-
 hw/s390x/s390-pci-bus.c               |    8 +-
 hw/vfio/ap.c                          |    2 +-
 hw/vfio/ccw.c                         |    2 +-
 hw/vfio/common.c                      |  249 ++++-
 hw/vfio/pci.c                         |   26 +-
 hw/vfio/platform.c                    |    2 +-
 hw/virtio/virtio-iommu.c              |    6 +-
 include/hw/i386/intel_iommu.h         |   65 +-
 include/hw/iommu/host_iommu_context.h |   86 ++
 include/hw/pci/pci.h                  |   25 +-
 include/hw/pci/pci_bus.h              |    2 +-
 include/hw/vfio/vfio-common.h         |    7 +-
 linux-headers/linux/iommu.h           |  413 ++++++++
 linux-headers/linux/vfio.h            |   84 ++
 scripts/update-linux-headers.sh       |    2 +-
 36 files changed, 2595 insertions(+), 85 deletions(-)
 create mode 100644 hw/iommu/Kconfig
 create mode 100644 hw/iommu/host_iommu_context.c
 create mode 100644 hw/iommu/meson.build
 create mode 100644 include/hw/iommu/host_iommu_context.h
 create mode 100644 linux-headers/linux/iommu.h
```
#### [RFC PATCH v4 0/9] KVM: selftests: some improvement and a new test
##### From: Yanan Wang <wangyanan55@huawei.com>

```c
From patchwork Tue Mar  2 12:57:42 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yanan Wang <wangyanan55@huawei.com>
X-Patchwork-Id: 12111847
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id EC0D2C4332E
	for <kvm@archiver.kernel.org>; Tue,  2 Mar 2021 16:23:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BDF1364F11
	for <kvm@archiver.kernel.org>; Tue,  2 Mar 2021 16:23:49 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1447344AbhCBQO0 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 2 Mar 2021 11:14:26 -0500
Received: from szxga05-in.huawei.com ([45.249.212.191]:13040 "EHLO
        szxga05-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1350919AbhCBM7L (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 2 Mar 2021 07:59:11 -0500
Received: from DGGEMS412-HUB.china.huawei.com (unknown [172.30.72.58])
        by szxga05-in.huawei.com (SkyGuard) with ESMTP id 4DqcZ11GsMzMhCS;
        Tue,  2 Mar 2021 20:55:53 +0800 (CST)
Received: from DESKTOP-TMVL5KK.china.huawei.com (10.174.187.128) by
 DGGEMS412-HUB.china.huawei.com (10.3.19.212) with Microsoft SMTP Server id
 14.3.498.0; Tue, 2 Mar 2021 20:57:53 +0800
From: Yanan Wang <wangyanan55@huawei.com>
To: <kvm@vger.kernel.org>, <linux-kselftest@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>
CC: Paolo Bonzini <pbonzini@redhat.com>,
        Ben Gardon <bgardon@google.com>,
        "Sean Christopherson" <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Andrew Jones <drjones@redhat.com>,
        Peter Xu <peterx@redhat.com>, Marc Zyngier <maz@kernel.org>,
        Ingo Molnar <mingo@kernel.org>,
        Adrian Hunter <adrian.hunter@intel.com>,
        Jiri Olsa <jolsa@redhat.com>,
        "Arnaldo Carvalho de Melo" <acme@redhat.com>,
        Arnd Bergmann <arnd@arndb.de>,
        Michael Kerrisk <mtk.manpages@gmail.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        <wanghaibin.wang@huawei.com>, <yezengruan@huawei.com>,
        <yuzenghui@huawei.com>, Yanan Wang <wangyanan55@huawei.com>
Subject: [RFC PATCH v4 0/9] KVM: selftests: some improvement and a new test
 for kvm page table
Date: Tue, 2 Mar 2021 20:57:42 +0800
Message-ID: <20210302125751.19080-1-wangyanan55@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.187.128]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,
This v4 series can mainly include two parts.
Based on kvm queue branch: https://git.kernel.org/pub/scm/virt/kvm/kvm.git/log/?h=queue
Links of v1: https://lore.kernel.org/lkml/20210208090841.333724-1-wangyanan55@huawei.com/
Links of v2: https://lore.kernel.org/lkml/20210225055940.18748-1-wangyanan55@huawei.com/
Links of v3: https://lore.kernel.org/lkml/20210301065916.11484-1-wangyanan55@huawei.com/

In the first part, all the known hugetlb backing src types specified
with different hugepage sizes are listed, so that we can specify use
of hugetlb source of the exact granularity that we want, instead of
the system default ones. And as all the known hugetlb page sizes are
listed, it's appropriate for all architectures. Besides, a helper that
can get granularity of different backing src types(anonumous/thp/hugetlb)
is added, so that we can use the accurate backing src granularity for
kinds of alignment or guest memory accessing of vcpus.

In the second part, a new test is added:
This test is added to serve as a performance tester and a bug reproducer
for kvm page table code (GPA->HPA mappings), it gives guidance for the
people trying to make some improvement for kvm. And the following explains
what we can exactly do through this test.

The function guest_code() can cover the conditions where a single vcpu or
multiple vcpus access guest pages within the same memory region, in three
VM stages(before dirty logging, during dirty logging, after dirty logging).
Besides, the backing src memory type(ANONYMOUS/THP/HUGETLB) of the tested
memory region can be specified by users, which means normal page mappings
or block mappings can be chosen by users to be created in the test.

If ANONYMOUS memory is specified, kvm will create normal page mappings
for the tested memory region before dirty logging, and update attributes
of the page mappings from RO to RW during dirty logging. If THP/HUGETLB
memory is specified, kvm will create block mappings for the tested memory
region before dirty logging, and split the blcok mappings into normal page
mappings during dirty logging, and coalesce the page mappings back into
block mappings after dirty logging is stopped.

So in summary, as a performance tester, this test can present the
performance of kvm creating/updating normal page mappings, or the
performance of kvm creating/splitting/recovering block mappings,
through execution time.

When we need to coalesce the page mappings back to block mappings after
dirty logging is stopped, we have to firstly invalidate *all* the TLB
entries for the page mappings right before installation of the block entry,
because a TLB conflict abort error could occur if we can't invalidate the
TLB entries fully. We have hit this TLB conflict twice on aarch64 software
implementation and fixed it. As this test can imulate process from dirty
logging enabled to dirty logging stopped of a VM with block mappings,
so it can also reproduce this TLB conflict abort due to inadequate TLB
invalidation when coalescing tables.

Links about the TLB conflict abort:
https://lore.kernel.org/lkml/20201201201034.116760-3-wangyanan55@huawei.com/
---

Change logs:

v3->v4:
- Add a helper to get system default hugetlb page size
- Add tags of Reviewed-by of Ben in the patches

v2->v3:
- Add tags of Suggested-by, Reviewed-by in the patches
- Add a generic micro to get hugetlb page sizes
- Some changes for suggestions about v2 series

v1->v2:
- Add a patch to sync header files
- Add helpers to get granularity of different backing src types
- Some changes for suggestions about v1 series

---

Yanan Wang (9):
  tools headers: sync headers of asm-generic/hugetlb_encode.h
  tools headers: Add a macro to get HUGETLB page sizes for mmap
  KVM: selftests: Use flag CLOCK_MONOTONIC_RAW for timing
  KVM: selftests: Make a generic helper to get vm guest mode strings
  KVM: selftests: Add a helper to get system configured THP page size
  KVM: selftests: Add a helper to get system default hugetlb page size
  KVM: selftests: List all hugetlb src types specified with page sizes
  KVM: selftests: Adapt vm_userspace_mem_region_add to new helpers
  KVM: selftests: Add a test for kvm page table code

 include/uapi/linux/mman.h                     |   2 +
 tools/include/asm-generic/hugetlb_encode.h    |   3 +
 tools/include/uapi/linux/mman.h               |   2 +
 tools/testing/selftests/kvm/Makefile          |   3 +
 .../selftests/kvm/demand_paging_test.c        |   8 +-
 .../selftests/kvm/dirty_log_perf_test.c       |  14 +-
 .../testing/selftests/kvm/include/kvm_util.h  |   4 +-
 .../testing/selftests/kvm/include/test_util.h |  21 +-
 .../selftests/kvm/kvm_page_table_test.c       | 476 ++++++++++++++++++
 tools/testing/selftests/kvm/lib/kvm_util.c    |  59 ++-
 tools/testing/selftests/kvm/lib/test_util.c   | 122 ++++-
 tools/testing/selftests/kvm/steal_time.c      |   4 +-
 12 files changed, 659 insertions(+), 59 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/kvm_page_table_test.c
```
