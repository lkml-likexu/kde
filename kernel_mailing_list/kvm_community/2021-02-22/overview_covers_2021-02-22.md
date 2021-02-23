

#### [PATCH v4 0/2] KVM: x86/mmu: Skip mmu_notifier changes when possible
##### From: David Stevens <stevensd@chromium.org>
X-Google-Original-From: David Stevens <stevensd@google.com>

```c
From patchwork Mon Feb 22 02:45:20 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Stevens <stevensd@chromium.org>
X-Patchwork-Id: 12097859
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-14.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 8C6C3C433DB
	for <kvm@archiver.kernel.org>; Mon, 22 Feb 2021 02:46:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 579E4614A5
	for <kvm@archiver.kernel.org>; Mon, 22 Feb 2021 02:46:41 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231810AbhBVCqV (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sun, 21 Feb 2021 21:46:21 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:49826 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S231756AbhBVCqU (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 21 Feb 2021 21:46:20 -0500
Received: from mail-pg1-x52b.google.com (mail-pg1-x52b.google.com
 [IPv6:2607:f8b0:4864:20::52b])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 33950C061574
        for <kvm@vger.kernel.org>; Sun, 21 Feb 2021 18:45:40 -0800 (PST)
Received: by mail-pg1-x52b.google.com with SMTP id n10so9343782pgl.10
        for <kvm@vger.kernel.org>; Sun, 21 Feb 2021 18:45:40 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=chromium.org; s=google;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=XvYAYuW5s5qinuMeBbssbbRBBrYSpWkKVGWmhyi6aks=;
        b=SQN3YewJJCVgPoZW33ilUolg2UKuFOff9YMoNynS6YazfZf97j6rEtP8B4hdFiJUPN
         x/+/LdV2d+MwWs94nVraKcNpabBohd6yIfVxdjN8tCWQAmrhxeIDMdGhw9RCBtskVaLN
         c+y9iCUVvhRpZuYVo8HdTUkA1R+B6hSVeK8BI=
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=XvYAYuW5s5qinuMeBbssbbRBBrYSpWkKVGWmhyi6aks=;
        b=pCv/X0QfbDMcMeO5tFvPSt8Yb13kSNRFd2+t9bo+/7HbH/VaLQ4p5H35X1WlCu/Qzj
         aW3JhMy0xNKwm2PP0WP+g1IaHCiZm6di3gURkhPykS0tp3PPNdZPTNUkNpzHUfM/j2zq
         H0K8qeJ9cVjPhsemMq0gqVRI/158/w89lP6e7j+UYFPR0ohNL3BwlT8ZWkWlYoQPUPVX
         e+itxXnsSHK2gwKLXOXjG5bp/PeLasgrPricGT5XwZxvbYyDLi7CBkjP4W0rc8szQZ3/
         nbAakc30e1ZmR/Jj6FIdi3kEBSBZWlOyYUX019YSkO6nInpaQGBPCeaDkCBrZlUt1Uda
         KdFQ==
X-Gm-Message-State: AOAM531PE3V5wL5u3FXEoKj2v07kbwL0CREQeXMkwv/Utb6qBC8Sv22s
        SV/iImijd5ZFRHwOkjdfQ4Q7BQ==
X-Google-Smtp-Source: 
 ABdhPJxZBJ5R6P+6KWCdQ/BarGMyXsUR+MHf6ansvmPqZOtFJPNjlFfXgwH4tftoJWaWtQXpcQFE4w==
X-Received: by 2002:aa7:961b:0:b029:1db:532c:9030 with SMTP id
 q27-20020aa7961b0000b02901db532c9030mr20358294pfg.30.1613961939826;
        Sun, 21 Feb 2021 18:45:39 -0800 (PST)
Received: from localhost ([2401:fa00:8f:203:11b3:5e1a:7cb:7e1f])
        by smtp.gmail.com with UTF8SMTPSA id
 77sm15847696pgd.65.2021.02.21.18.45.34
        (version=TLS1_3 cipher=TLS_AES_128_GCM_SHA256 bits=128/128);
        Sun, 21 Feb 2021 18:45:39 -0800 (PST)
From: David Stevens <stevensd@chromium.org>
X-Google-Original-From: David Stevens <stevensd@google.com>
To: Sean Christopherson <seanjc@google.com>,
        Paolo Bonzini <pbonzini@redhat.com>
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Marc Zyngier <maz@kernel.org>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        Huacai Chen <chenhuacai@kernel.org>,
        Aleksandar Markovic <aleksandar.qemu.devel@gmail.com>,
        linux-mips@vger.kernel.org, Paul Mackerras <paulus@ozlabs.org>,
        kvm-ppc@vger.kernel.org,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Janosch Frank <frankja@linux.ibm.com>,
        David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Claudio Imbrenda <imbrenda@linux.ibm.com>,
        David Stevens <stevensd@google.com>
Subject: [PATCH v4 0/2] KVM: x86/mmu: Skip mmu_notifier changes when possible
Date: Mon, 22 Feb 2021 11:45:20 +0900
Message-Id: <20210222024522.1751719-1-stevensd@google.com>
X-Mailer: git-send-email 2.30.0.617.g56c4b15f3c-goog
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

These patches reduce how often mmu_notifier updates block guest page
faults. The primary benefit of this is the reduction in the likelihood
of extreme latency when handling a page fault due to another thread
having been preempted while modifying host virtual addresses.

v3 -> v4:
 - Fix bug by skipping prefetch during invalidation

v2 -> v3:
 - Added patch to skip check for MMIO page faults
 - Style changes

David Stevens (1):
  KVM: x86/mmu: Consider the hva in mmu_notifier retry

Sean Christopherson (1):
  KVM: x86/mmu: Skip mmu_notifier check when handling MMIO page fault

 arch/powerpc/kvm/book3s_64_mmu_hv.c    |  2 +-
 arch/powerpc/kvm/book3s_64_mmu_radix.c |  2 +-
 arch/x86/kvm/mmu/mmu.c                 | 23 ++++++++++++++------
 arch/x86/kvm/mmu/paging_tmpl.h         |  7 ++++---
 include/linux/kvm_host.h               | 25 +++++++++++++++++++++-
 virt/kvm/kvm_main.c                    | 29 ++++++++++++++++++++++----
 6 files changed, 72 insertions(+), 16 deletions(-)
```
#### [kvm-unit-tests PATCH v3 0/7] s390x: Cleanup exception register
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
From patchwork Mon Feb 22 08:57:49 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 12098185
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 25D62C433E0
	for <kvm@archiver.kernel.org>; Mon, 22 Feb 2021 09:30:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B3B0964EE9
	for <kvm@archiver.kernel.org>; Mon, 22 Feb 2021 09:30:01 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230036AbhBVJ3q (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 22 Feb 2021 04:29:46 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:11936 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S229863AbhBVJ3o (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 22 Feb 2021 04:29:44 -0500
Received: from pps.filterd (m0098393.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 11M9RdZE138736;
        Mon, 22 Feb 2021 04:29:03 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=+cbhk8kI2bEmLFXN30z5ezQEltoLjE9PpEM040R4HCQ=;
 b=UJ9+ovbmwS0R+jElxTUYdSX4NevLrBP4qw30yEfpJzjkAChqgorMI/4TDseQezatxi+r
 jkBw12wYDEdAISkQEI1cnpzqcoQEiAYfdsmUo6NLJ08gXDaEPBdafvgxalkY+ihlG7x+
 D5xkiHcYhh+YDg5PYU/u0QnnsgQL81ppTpU/2AxFF2CtWJMrP2SFowbqTCebNQWZv0t5
 QQwXt/+8Kn0wDlpnFvKL/njsAqZar1bGFLTVhp7Y8iDgWRZPxAXMsTYiIEfAv4eHNHL2
 esyyxjZgzir04jaTsmZeznQDsX1cAjknhHApxnU1yNEgQZPfeEwPvtq8zPGiGzw39P96 GA==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 36va0d8325-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 22 Feb 2021 04:29:02 -0500
Received: from m0098393.ppops.net (m0098393.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 11M9RrRL140225;
        Mon, 22 Feb 2021 04:28:34 -0500
Received: from ppma01fra.de.ibm.com (46.49.7a9f.ip4.static.sl-reverse.com
 [159.122.73.70])
        by mx0a-001b2d01.pphosted.com with ESMTP id 36va0d8255-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 22 Feb 2021 04:28:33 -0500
Received: from pps.filterd (ppma01fra.de.ibm.com [127.0.0.1])
        by ppma01fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 11M8vxI3024945;
        Mon, 22 Feb 2021 08:59:11 GMT
Received: from b06cxnps4076.portsmouth.uk.ibm.com
 (d06relay13.portsmouth.uk.ibm.com [9.149.109.198])
        by ppma01fra.de.ibm.com with ESMTP id 36tt288rbw-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 22 Feb 2021 08:59:11 +0000
Received: from d06av26.portsmouth.uk.ibm.com (d06av26.portsmouth.uk.ibm.com
 [9.149.105.62])
        by b06cxnps4076.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 11M8x8Wh41353606
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 22 Feb 2021 08:59:08 GMT
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 79A25AE059;
        Mon, 22 Feb 2021 08:59:08 +0000 (GMT)
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id CE066AE056;
        Mon, 22 Feb 2021 08:59:07 +0000 (GMT)
Received: from linux01.pok.stglabs.ibm.com (unknown [9.114.17.81])
        by d06av26.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Mon, 22 Feb 2021 08:59:07 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, imbrenda@linux.ibm.com,
        pmorel@linux.ibm.com, david@redhat.com, thuth@redhat.com
Subject: [kvm-unit-tests PATCH v3 0/7] s390x: Cleanup exception register
 save/restore and implement backtrace
Date: Mon, 22 Feb 2021 03:57:49 -0500
Message-Id: <20210222085756.14396-1-frankja@linux.ibm.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.761
 definitions=2021-02-22_02:2021-02-18,2021-02-22 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxscore=0 lowpriorityscore=0
 mlxlogscore=999 phishscore=0 malwarescore=0 impostorscore=0 clxscore=1015
 bulkscore=0 priorityscore=1501 suspectscore=0 spamscore=0 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2102220081
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Having two sets of macros for saving and restoring registers on
exceptions doesn't seem optimal to me. Therefore this patch set
removes the old macros that use the lowcore as storage in favor of the
stack using ones. At the same time we move over to generated offsets
instead of subtracting from the stack piece by piece. Changes to the
stack struct are easier that way.

Additionally let's add backtrace support and print the GRs on
exception so we get a bit more information when something goes wrong.

v3:
	* Squashed the STACK_FRAME_INT_SIZE definition patch
	* Added a backchain store before we branch to the C pgm handler
	* Switched to the *int*_t types from kernel style types
	* Added comments

v2:
	* Added full CR saving to fix diag308 test
	* Added rev-bys

Janosch Frank (7):
  s390x: Fix fpc store address in RESTORE_REGS_STACK
  s390x: Fully commit to stack save area for exceptions
  s390x: Introduce and use CALL_INT_HANDLER macro
  s390x: Provide preliminary backtrace support
  s390x: Print more information on program exceptions
  s390x: Move diag308_load_reset to stack saving
  s390x: Remove SAVE/RESTORE_STACK and lowcore fpc and fprs save areas

 lib/s390x/asm-offsets.c   | 17 ++++---
 lib/s390x/asm/arch_def.h  | 35 ++++++++++----
 lib/s390x/asm/interrupt.h |  4 +-
 lib/s390x/interrupt.c     | 43 +++++++++++++++---
 lib/s390x/stack.c         | 20 +++++---
 s390x/Makefile            |  1 +
 s390x/cpu.S               |  6 ++-
 s390x/cstart64.S          | 25 ++--------
 s390x/macros.S            | 96 ++++++++++++++++++++-------------------
 9 files changed, 148 insertions(+), 99 deletions(-)
```
#### [PATCH v6 0/2] System Generation ID driver and VMGENID backend
##### From: Adrian Catangiu <acatan@amazon.com>

```c
From patchwork Mon Feb 22 09:41:24 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Adrian Catangiu <acatan@amazon.com>
X-Patchwork-Id: 12098207
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 3ADBBC433E9
	for <kvm@archiver.kernel.org>; Mon, 22 Feb 2021 09:43:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DCDD464EE6
	for <kvm@archiver.kernel.org>; Mon, 22 Feb 2021 09:43:23 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230138AbhBVJnR (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 22 Feb 2021 04:43:17 -0500
Received: from smtp-fw-6002.amazon.com ([52.95.49.90]:59981 "EHLO
        smtp-fw-6002.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S230141AbhBVJmx (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 22 Feb 2021 04:42:53 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.com; i=@amazon.com; q=dns/txt; s=amazon201209;
  t=1613986971; x=1645522971;
  h=from:to:cc:subject:date:message-id:mime-version:
   content-transfer-encoding;
  bh=kck/xR2x6Hs/rrwKMHWfVaM9BsndkG+d3cLhoGv+WGM=;
  b=ZpYxSjBGErX/6ywPAwILw2JNeCetiRGdYvFU4lTwOzpGtr1PzHfpbi/E
   WxhVY66g54q1ALw9hkwEEORFpjGcbColdHkwX791hlF6hSWqtUM5CEKty
   Dr/1yZr4UPoq3XvZlz8o2qQSZ4rUWC22iw4KfIRiypZIU0cVAOwWxnzbF
   g=;
X-IronPort-AV: E=Sophos;i="5.81,196,1610409600";
   d="scan'208";a="89090694"
Received: from iad12-co-svc-p1-lb1-vlan2.amazon.com (HELO
 email-inbound-relay-2b-81e76b79.us-west-2.amazon.com) ([10.43.8.2])
  by smtp-border-fw-out-6002.iad6.amazon.com with ESMTP;
 22 Feb 2021 09:41:59 +0000
Received: from EX13D08EUB004.ant.amazon.com
 (pdx1-ws-svc-p6-lb9-vlan3.pdx.amazon.com [10.236.137.198])
        by email-inbound-relay-2b-81e76b79.us-west-2.amazon.com (Postfix) with
 ESMTPS id DBAA4A03F3;
        Mon, 22 Feb 2021 09:41:55 +0000 (UTC)
Received: from uf6ed9c851f4556.ant.amazon.com (10.43.161.87) by
 EX13D08EUB004.ant.amazon.com (10.43.166.158) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Mon, 22 Feb 2021 09:41:41 +0000
From: Adrian Catangiu <acatan@amazon.com>
To: <linux-doc@vger.kernel.org>, <linux-kernel@vger.kernel.org>,
        <qemu-devel@nongnu.org>, <kvm@vger.kernel.org>,
        <linux-s390@vger.kernel.org>
CC: <gregkh@linuxfoundation.org>, <graf@amazon.com>,
        <rdunlap@infradead.org>, <arnd@arndb.de>, <ebiederm@xmission.com>,
        <rppt@kernel.org>, <0x7f454c46@gmail.com>,
        <borntraeger@de.ibm.com>, <Jason@zx2c4.com>, <jannh@google.com>,
        <w@1wt.eu>, <colmmacc@amazon.com>, <luto@kernel.org>,
        <tytso@mit.edu>, <ebiggers@kernel.org>, <dwmw@amazon.co.uk>,
        <bonzini@gnu.org>, <sblbir@amazon.com>, <raduweis@amazon.com>,
        <corbet@lwn.net>, <mst@redhat.com>, <mhocko@kernel.org>,
        <rafael@kernel.org>, <pavel@ucw.cz>, <mpe@ellerman.id.au>,
        <areber@redhat.com>, <ovzxemul@gmail.com>, <avagin@gmail.com>,
        <ptikhomirov@virtuozzo.com>, <gil@azul.com>, <asmehra@redhat.com>,
        <dgunigun@redhat.com>, <vijaysun@ca.ibm.com>, <oridgar@gmail.com>,
        <ghammer@redhat.com>, <acatan@amazon.com>
Subject: [PATCH v6 0/2] System Generation ID driver and VMGENID backend
Date: Mon, 22 Feb 2021 11:41:24 +0200
Message-ID: <1613986886-29493-1-git-send-email-acatan@amazon.com>
X-Mailer: git-send-email 2.7.4
MIME-Version: 1.0
X-Originating-IP: [10.43.161.87]
X-ClientProxiedBy: EX13D41UWC004.ant.amazon.com (10.43.162.31) To
 EX13D08EUB004.ant.amazon.com (10.43.166.158)
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This feature is aimed at virtualized or containerized environments
where VM or container snapshotting duplicates memory state, which is a
challenge for applications that want to generate unique data such as
request IDs, UUIDs, and cryptographic nonces.

The patch set introduces a mechanism that provides a userspace
interface for applications and libraries to be made aware of uniqueness
breaking events such as VM or container snapshotting, and allow them to
react and adapt to such events.

Solving the uniqueness problem strongly enough for cryptographic
purposes requires a mechanism which can deterministically reseed
userspace PRNGs with new entropy at restore time. This mechanism must
also support the high-throughput and low-latency use-cases that led
programmers to pick a userspace PRNG in the first place; be usable by
both application code and libraries; allow transparent retrofitting
behind existing popular PRNG interfaces without changing application
code; it must be efficient, especially on snapshot restore; and be
simple enough for wide adoption.

The first patch in the set implements a device driver which exposes a
the /dev/sysgenid char device to userspace. Its associated filesystem
operations operations can be used to build a system level safe workflow
that guest software can follow to protect itself from negative system
snapshot effects.

The second patch in the set adds a VmGenId driver which makes use of
the ACPI vmgenid device to drive SysGenId and to reseed kernel entropy
following VM snapshots.

**Please note**, SysGenID alone does not guarantee complete snapshot
safety to applications using it. A certain workflow needs to be
followed at the system level, in order to make the system
snapshot-resilient. Please see the "Snapshot Safety Prerequisites"
section in the included SysGenID documentation.
---

v5 -> v6:

  - sysgenid: watcher tracking disabled by default
  - sysgenid: add SYSGENID_SET_WATCHER_TRACKING ioctl to allow each
    file descriptor to set whether they should be tracked as watchers
  - rename SYSGENID_FORCE_GEN_UPDATE -> SYSGENID_TRIGGER_GEN_UPDATE
  - rework all documentation to clearly capture all prerequisites for
    achieving snapshot safety when using the provided mechanism
  - sysgenid documentation: replace individual filesystem operations
    examples with a higher level example showcasing system-level
    snapshot-safe workflow

v4 -> v5:

  - sysgenid: generation changes are also exported through uevents
  - remove SYSGENID_GET_OUTDATED_WATCHERS ioctl
  - document sysgenid ioctl major/minor numbers

v3 -> v4:

  - split functionality in two separate kernel modules: 
    1. drivers/misc/sysgenid.c which provides the generic userspace
       interface and mechanisms
    2. drivers/virt/vmgenid.c as VMGENID acpi device driver that seeds
       kernel entropy and acts as a driving backend for the generic
       sysgenid
  - rename /dev/vmgenid -> /dev/sysgenid
  - rename uapi header file vmgenid.h -> sysgenid.h
  - rename ioctls VMGENID_* -> SYSGENID_*
  - add ‘min_gen’ parameter to SYSGENID_FORCE_GEN_UPDATE ioctl
  - fix races in documentation examples

v2 -> v3:

  - separate the core driver logic and interface, from the ACPI device
    The ACPI vmgenid device is now one possible backend
  - fix issue when timeout=0 in VMGENID_WAIT_WATCHERS
  - add locking to avoid races between fs ops handlers and hw irq
    driven generation updates
  - change VMGENID_WAIT_WATCHERS ioctl so if the current caller is
    outdated or a generation change happens while waiting (thus making
    current caller outdated), the ioctl returns -EINTR to signal the
    user to handle event and retry. Fixes blocking on oneself
  - add VMGENID_FORCE_GEN_UPDATE ioctl conditioned by
    CAP_CHECKPOINT_RESTORE capability, through which software can force
    generation bump

v1 -> v2:

  - expose to userspace a monotonically increasing u32 Vm Gen Counter
    instead of the hw VmGen UUID
  - since the hw/hypervisor-provided 128-bit UUID is not public
    anymore, add it to the kernel RNG as device randomness
  - insert driver page containing Vm Gen Counter in the user vma in
    the driver's mmap handler instead of using a fault handler
  - turn driver into a misc device driver to auto-create /dev/vmgenid
  - change ioctl arg to avoid leaking kernel structs to userspace
  - update documentation

Adrian Catangiu (2):
  drivers/misc: sysgenid: add system generation id driver
  drivers/virt: vmgenid: add vm generation id driver

 Documentation/misc-devices/sysgenid.rst            | 234 ++++++++++++++
 Documentation/userspace-api/ioctl/ioctl-number.rst |   1 +
 Documentation/virt/vmgenid.rst                     |  36 +++
 MAINTAINERS                                        |  15 +
 drivers/misc/Kconfig                               |  15 +
 drivers/misc/Makefile                              |   1 +
 drivers/misc/sysgenid.c                            | 338 +++++++++++++++++++++
 drivers/virt/Kconfig                               |  13 +
 drivers/virt/Makefile                              |   1 +
 drivers/virt/vmgenid.c                             | 153 ++++++++++
 include/uapi/linux/sysgenid.h                      |  18 ++
 11 files changed, 825 insertions(+)
 create mode 100644 Documentation/misc-devices/sysgenid.rst
 create mode 100644 Documentation/virt/vmgenid.rst
 create mode 100644 drivers/misc/sysgenid.c
 create mode 100644 drivers/virt/vmgenid.c
 create mode 100644 include/uapi/linux/sysgenid.h
```
#### [PATCH v4 0/1] KVM: s390: diag9c (directed yield) forwarding
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
From patchwork Mon Feb 22 12:41:00 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 12098739
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id ADE68C433E0
	for <kvm@archiver.kernel.org>; Mon, 22 Feb 2021 14:10:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6900164E5C
	for <kvm@archiver.kernel.org>; Mon, 22 Feb 2021 14:10:57 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232198AbhBVOKh (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 22 Feb 2021 09:10:37 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:34300 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S231419AbhBVOJt (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 22 Feb 2021 09:09:49 -0500
Received: from pps.filterd (m0098393.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 11ME589S018816;
        Mon, 22 Feb 2021 09:09:08 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id; s=pp1;
 bh=srmRYY9KOXm2In6DQzRA90ulNGhW3frH5GXWf7daVz0=;
 b=gPley3eGNat4tk6BdkBqQ+Rt+G0D0WwyrDD9mTU3fLBUsbX0vc2qOdjCatwNFt0yYXtN
 iQYMxRHbxld/KRC2jXl6iF57/PXDi9SdqYb3otSbAkTGsCiA+Cbg+K3FLZQacoK3Yqfj
 bUvwoahE5Qsk66IW2MElZV2kvc8hw0Q6bCl1KZY6JyEm33CHYHNO2wyxEhfkguuoGG8b
 bRTBzSLyg6Mi85bc8fHwNCcQGuNZsrmx+NVO9kOqp2WxjQifU5D6IDCX1nR26GVKirBA
 UsMUEmcWZvctXOxle5fbhP4kvMGROC/dmmdtZWc+NQ5gTEhnS7yJFnAnmT0yuH526sMs Uw==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 36ve1brdcr-42
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 22 Feb 2021 09:09:07 -0500
Received: from m0098393.ppops.net (m0098393.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 11MDQbjc013935;
        Mon, 22 Feb 2021 08:31:54 -0500
Received: from ppma03ams.nl.ibm.com (62.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.98])
        by mx0a-001b2d01.pphosted.com with ESMTP id 36vdgeg67e-13
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 22 Feb 2021 08:31:54 -0500
Received: from pps.filterd (ppma03ams.nl.ibm.com [127.0.0.1])
        by ppma03ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 11MCRww8028401;
        Mon, 22 Feb 2021 12:41:06 GMT
Received: from b06avi18878370.portsmouth.uk.ibm.com
 (b06avi18878370.portsmouth.uk.ibm.com [9.149.26.194])
        by ppma03ams.nl.ibm.com with ESMTP id 36tt281mn5-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 22 Feb 2021 12:41:06 +0000
Received: from d06av26.portsmouth.uk.ibm.com (d06av26.portsmouth.uk.ibm.com
 [9.149.105.62])
        by b06avi18878370.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 11MCepMA26608126
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 22 Feb 2021 12:40:51 GMT
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 512B6AE051;
        Mon, 22 Feb 2021 12:41:03 +0000 (GMT)
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id DDB2FAE045;
        Mon, 22 Feb 2021 12:41:02 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.71.218])
        by d06av26.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Mon, 22 Feb 2021 12:41:02 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, borntraeger@de.ibm.com,
        frankja@linux.ibm.com, cohuck@redhat.com, david@redhat.com,
        thuth@redhat.com, pmorel@linux.ibm.com
Subject: [PATCH v4 0/1] KVM: s390: diag9c (directed yield) forwarding
Date: Mon, 22 Feb 2021 13:41:00 +0100
Message-Id: <1613997661-22525-1-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.761
 definitions=2021-02-22_02:2021-02-22,2021-02-22 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 malwarescore=0 clxscore=1015
 lowpriorityscore=0 phishscore=0 mlxlogscore=999 adultscore=0 spamscore=0
 suspectscore=0 priorityscore=1501 impostorscore=0 bulkscore=0 mlxscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2102220130
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch will forward the yield_to hypercall (diag9c) if in the host
the target CPU is also not running. As we do not yet have performance
data (and recommendations) the default is turned off, but this can
be changed during runtime.

The documentation notation for the titles is kept coherent with
the other DIAGNOSE entries using the zVM notation DIAGNOSE 'X'9C,
While in the explanation part we use the standard Linux notation
DIAGNOSE 0x9c.

Regards,
Pierre


Pierre Morel (1):
  KVM: s390: diag9c (directed yield) forwarding

 Documentation/virt/kvm/s390-diag.rst | 33 ++++++++++++++++++++++++++++
 arch/s390/include/asm/kvm_host.h     |  1 +
 arch/s390/include/asm/smp.h          |  1 +
 arch/s390/kernel/smp.c               |  1 +
 arch/s390/kvm/diag.c                 | 31 +++++++++++++++++++++++---
 arch/s390/kvm/kvm-s390.c             |  6 +++++
 arch/s390/kvm/kvm-s390.h             |  8 +++++++
 7 files changed, 78 insertions(+), 3 deletions(-)
```
#### [RFC PATCH 00/10] vfio: Device memory DMA mapping improvements
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
From patchwork Mon Feb 22 16:50:22 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alex Williamson <alex.williamson@redhat.com>
X-Patchwork-Id: 12099171
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-10.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 6C3E8C433E0
	for <kvm@archiver.kernel.org>; Mon, 22 Feb 2021 16:52:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 37EDC64EF5
	for <kvm@archiver.kernel.org>; Mon, 22 Feb 2021 16:52:24 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230441AbhBVQwF (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 22 Feb 2021 11:52:05 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:54820 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S229952AbhBVQwA (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 22 Feb 2021 11:52:00 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1614012634;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=CgcpckDo9UEWBagLaIjLCEPd9ZKR8yZthDIdNf7Trmc=;
        b=iqEmFTrbr6PuSzXSjQX4wO2CKRv4h2PwG0jgnsIlArmYlQ/6DoCDHL69WMQcyl9RC7RTfx
        qV4DPsoW+ZFGZvavyUMMKLiL7eAylddS12d6fSwBaCAWoMUGErt6xNs4FY+3D4laGBKYYI
        9caPjFxXtotnmcysN+MCbQIpW0KkvlY=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-65-TU9vfHv_MuKmOaZx2C8S7Q-1; Mon, 22 Feb 2021 11:50:32 -0500
X-MC-Unique: TU9vfHv_MuKmOaZx2C8S7Q-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 1764ECC627;
        Mon, 22 Feb 2021 16:50:30 +0000 (UTC)
Received: from gimli.home (ovpn-112-255.phx2.redhat.com [10.3.112.255])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 5A3FA5D9D3;
        Mon, 22 Feb 2021 16:50:23 +0000 (UTC)
Subject: [RFC PATCH 00/10] vfio: Device memory DMA mapping improvements
From: Alex Williamson <alex.williamson@redhat.com>
To: alex.williamson@redhat.com
Cc: cohuck@redhat.com, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, jgg@nvidia.com, peterx@redhat.com
Date: Mon, 22 Feb 2021 09:50:22 -0700
Message-ID: <161401167013.16443.8389863523766611711.stgit@gimli.home>
User-Agent: StGit/0.21-dirty
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is a re-implementation of [1] following suggestions and code from
Jason Gunthorpe.  This is lightly tested but seems functional and
throws no lockdep warnings.  In this series we tremendously simplify
zapping of vmas mapping device memory using unmap_mapping_range(), we
create a protocol for looking up a vfio_device from a vma and provide
an interface to get a reference from that vma, using that device
reference, the caller can register a notifier for the device to
trigger on events such as device release.  This notifier is only
enabled here for vfio-pci, but both the vma policy and the notifier
trigger should be trivial to add to any vfio bus driver after RFC.

Does this look more like the direction we should go?

Note that like the last series we're still not dropping DMA mappings
on device memory disable as this would likely break userspace in some
instances, we don't have IOMMU interfaces to modify protection bits,
and it's not clear an IOMMU fault is absolutely better than the bus
error.  Thanks,

Alex

[1]https://lore.kernel.org/kvm/161315658638.7320.9686203003395567745.stgit@gimli.home/T/#m64859ccd7d92f39a924759c7423f2dcf7d367c84
---

Alex Williamson (10):
      vfio: Create vfio_fs_type with inode per device
      vfio: Update vfio_add_group_dev() API
      vfio: Export unmap_mapping_range() wrapper
      vfio/pci: Use vfio_device_unmap_mapping_range()
      vfio: Create a vfio_device from vma lookup
      vfio: Add a device notifier interface
      vfio/pci: Notify on device release
      vfio/type1: Refactor pfn_list clearing
      vfio/type1: Pass iommu and dma objects through to vaddr_get_pfn
      vfio/type1: Register device notifier


 drivers/vfio/Kconfig                         |    1 
 drivers/vfio/fsl-mc/vfio_fsl_mc.c            |    6 -
 drivers/vfio/mdev/vfio_mdev.c                |    5 -
 drivers/vfio/pci/vfio_pci.c                  |  223 ++++----------------------
 drivers/vfio/pci/vfio_pci_private.h          |    3 
 drivers/vfio/platform/vfio_platform_common.c |    7 +
 drivers/vfio/vfio.c                          |  143 +++++++++++++++--
 drivers/vfio/vfio_iommu_type1.c              |  211 ++++++++++++++++++++-----
 include/linux/vfio.h                         |   19 ++
 9 files changed, 368 insertions(+), 250 deletions(-)
```
