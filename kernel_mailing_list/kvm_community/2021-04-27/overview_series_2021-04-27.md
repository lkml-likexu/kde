#### [PATCH v4 1/7] hyperv: Detect Nested virtualization support for SVM
##### From: Vineeth Pillai <viremana@linux.microsoft.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vineeth Pillai <viremana@linux.microsoft.com>
X-Patchwork-Id: 12227325
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.3 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 8EEABC43600
	for <kvm@archiver.kernel.org>; Tue, 27 Apr 2021 20:55:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 73A1C6140B
	for <kvm@archiver.kernel.org>; Tue, 27 Apr 2021 20:55:10 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S239104AbhD0Uzw (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 27 Apr 2021 16:55:52 -0400
Received: from linux.microsoft.com ([13.77.154.182]:35570 "EHLO
        linux.microsoft.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S239013AbhD0Uzt (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 27 Apr 2021 16:55:49 -0400
Received: from
 viremana-dev.fwjladdvyuiujdukmejncen4mf.xx.internal.cloudapp.net (unknown
 [13.66.132.26])
        by linux.microsoft.com (Postfix) with ESMTPSA id D8A1B20B8001;
        Tue, 27 Apr 2021 13:55:05 -0700 (PDT)
DKIM-Filter: OpenDKIM Filter v2.11.0 linux.microsoft.com D8A1B20B8001
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=linux.microsoft.com;
        s=default; t=1619556905;
        bh=Ej89Qm9LLMSPxt8OXtylVuc32Z7Yd+HfBt+EQT9qOcM=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=PDSa9QUPVYflfgMJWAgTbEJG+7+06T7vKyciYF1fXrbSVUcbE/FBojkyuHIrc6Cbt
         ldrKzzEEb56CaYP9qDhkS+uBdx/7fJilIdaSw7DpW3jAky2Lhcrrn20Ax8Uy5lB6jT
         RudJ8XQk73khY8QEpCt60IEDwyFrUOH09bjYb2z8=
From: Vineeth Pillai <viremana@linux.microsoft.com>
To: Lan Tianyu <Tianyu.Lan@microsoft.com>,
        Michael Kelley <mikelley@microsoft.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Tom Lendacky <thomas.lendacky@amd.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, Wei Liu <wei.liu@kernel.org>,
        Stephen Hemminger <sthemmin@microsoft.com>,
        Haiyang Zhang <haiyangz@microsoft.com>
Cc: Vineeth Pillai <viremana@linux.microsoft.com>,
        "H. Peter Anvin" <hpa@zytor.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        "K. Y. Srinivasan" <kys@microsoft.com>, x86@kernel.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        linux-hyperv@vger.kernel.org
Subject: [PATCH v4 1/7] hyperv: Detect Nested virtualization support for SVM
Date: Tue, 27 Apr 2021 20:54:50 +0000
Message-Id: 
 <8ffa88e6ceb55d283c76b4c5fd9ad0fb1a2cf667.1619556430.git.viremana@linux.microsoft.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <cover.1619556430.git.viremana@linux.microsoft.com>
References: <cover.1619556430.git.viremana@linux.microsoft.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Previously, to detect nested virtualization enlightenment support,
we were using HV_X64_ENLIGHTENED_VMCS_RECOMMENDED feature bit of
HYPERV_CPUID_ENLIGHTMENT_INFO.EAX CPUID as docuemented in TLFS:
 "Bit 14: Recommend a nested hypervisor using the enlightened VMCS
  interface. Also indicates that additional nested enlightenments
  may be available (see leaf 0x4000000A)".

Enlightened VMCS, however, is an Intel only feature so the above
detection method doesn't work for AMD. So, use the
HYPERV_CPUID_VENDOR_AND_MAX_FUNCTIONS.EAX CPUID information ("The
maximum input value for hypervisor CPUID information.") and this
works for both AMD and Intel.

Signed-off-by: Vineeth Pillai <viremana@linux.microsoft.com>
---
 arch/x86/kernel/cpu/mshyperv.c | 10 +++++++---
 1 file changed, 7 insertions(+), 3 deletions(-)

```
#### [kvm-unit-tests PATCH v1 1/1] MAINTAINERS: s390x: add myself as reviewer
##### From: Claudio Imbrenda <imbrenda@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Claudio Imbrenda <imbrenda@linux.ibm.com>
X-Patchwork-Id: 12226627
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 39DB4C433ED
	for <kvm@archiver.kernel.org>; Tue, 27 Apr 2021 12:16:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0F815613B2
	for <kvm@archiver.kernel.org>; Tue, 27 Apr 2021 12:16:16 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S235547AbhD0MQ6 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 27 Apr 2021 08:16:58 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:28092 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S235410AbhD0MQ5 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 27 Apr 2021 08:16:57 -0400
Received: from pps.filterd (m0098413.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 13RC2liB152839
        for <kvm@vger.kernel.org>; Tue, 27 Apr 2021 08:16:14 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=yhD1YNM89K2upDWov/ofq8a0LRVkPrK1zUWQRmieaHU=;
 b=B+nDHxD/BPOd9pg/iMebZ8xnM9QGbTEhdkoPXnRLegmpvRMMfy9V4Dugcfb2aVkwrRfB
 rJ7vIdNTdT+n8l8Zy5U7aXsGv9G7cE16ZP+NmB8JMOHUbx8dT+CIi9fQGUaCezs83Fuz
 OSUBjJSH/gYrWIbgOix3I4lqFc0CQZ7bgfdyeGSizVrftVYHPrlM6K7XAgo2n4X8V+h0
 9vEdg9K1wNPoVkEGv/KFbh+puCwp09cCdMxrKwWGWvoQ/W+qaLPb242IMHikfYfN16qw
 TtMPVPPxtXo5vuD56emhxnU6hW5sY+oLPDTifiFGnNqj3WoT1c1gAwdIxpqFFjUUGirt RQ==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 386gvx2y6c-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT)
        for <kvm@vger.kernel.org>; Tue, 27 Apr 2021 08:16:14 -0400
Received: from m0098413.ppops.net (m0098413.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 13RC38Q0154800
        for <kvm@vger.kernel.org>; Tue, 27 Apr 2021 08:16:13 -0400
Received: from ppma03ams.nl.ibm.com (62.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.98])
        by mx0b-001b2d01.pphosted.com with ESMTP id 386gvx2y5e-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 27 Apr 2021 08:16:13 -0400
Received: from pps.filterd (ppma03ams.nl.ibm.com [127.0.0.1])
        by ppma03ams.nl.ibm.com (8.16.0.43/8.16.0.43) with SMTP id
 13RCDkTZ029038;
        Tue, 27 Apr 2021 12:16:12 GMT
Received: from b06cxnps3074.portsmouth.uk.ibm.com
 (d06relay09.portsmouth.uk.ibm.com [9.149.109.194])
        by ppma03ams.nl.ibm.com with ESMTP id 384ay8hawc-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 27 Apr 2021 12:16:12 +0000
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 13RCG9bQ32768496
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 27 Apr 2021 12:16:09 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 0EEEEA4062;
        Tue, 27 Apr 2021 12:16:09 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 9E48EA4064;
        Tue, 27 Apr 2021 12:16:08 +0000 (GMT)
Received: from ibm-vm.ibmuc.com (unknown [9.145.13.42])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue, 27 Apr 2021 12:16:08 +0000 (GMT)
From: Claudio Imbrenda <imbrenda@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: frankja@linux.ibm.com, thuth@redhat.com, cohuck@redhat.com,
        david@redhat.com
Subject: [kvm-unit-tests PATCH v1 1/1] MAINTAINERS: s390x: add myself as
 reviewer
Date: Tue, 27 Apr 2021 14:16:08 +0200
Message-Id: <20210427121608.157783-1-imbrenda@linux.ibm.com>
X-Mailer: git-send-email 2.26.3
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-ORIG-GUID: _5K0ZkG2p1D7oxj7ah_t0IA6fRnsYbi-
X-Proofpoint-GUID: HjXb49lfKUPLpfZHNfK3WkigpMi91nhA
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.391,18.0.761
 definitions=2021-04-27_06:2021-04-27,2021-04-27 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 impostorscore=0 spamscore=0
 mlxscore=0 clxscore=1015 adultscore=0 bulkscore=0 phishscore=0
 mlxlogscore=984 suspectscore=0 lowpriorityscore=0 malwarescore=0
 priorityscore=1501 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2104060000 definitions=main-2104270091
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Signed-off-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
Acked-by: David Hildenbrand <david@redhat.com>
Acked-by: Cornelia Huck <cohuck@redhat.com>
Acked-by: Janosch Frank <frankja@linux.ibm.com>
---
 MAINTAINERS | 1 +
 1 file changed, 1 insertion(+)

```
#### [kvm-unit-tests PATCH v2] configure: arm: Replace --vmm with --target
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexandru Elisei <alexandru.elisei@arm.com>
X-Patchwork-Id: 12226995
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 2F6F4C433ED
	for <kvm@archiver.kernel.org>; Tue, 27 Apr 2021 16:34:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E9DED613DD
	for <kvm@archiver.kernel.org>; Tue, 27 Apr 2021 16:34:26 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S236616AbhD0QfG (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 27 Apr 2021 12:35:06 -0400
Received: from foss.arm.com ([217.140.110.172]:54822 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S238335AbhD0Qet (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 27 Apr 2021 12:34:49 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 65150D6E;
        Tue, 27 Apr 2021 09:34:05 -0700 (PDT)
Received: from monolith.localdoman (unknown [172.31.20.19])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 4CDE13F73B;
        Tue, 27 Apr 2021 09:34:04 -0700 (PDT)
From: Alexandru Elisei <alexandru.elisei@arm.com>
To: drjones@redhat.com, kvm@vger.kernel.org,
        kvmarm@lists.cs.columbia.edu
Cc: pbonzini@redhat.com
Subject: [kvm-unit-tests PATCH v2] configure: arm: Replace --vmm with --target
Date: Tue, 27 Apr 2021 17:34:37 +0100
Message-Id: <20210427163437.243839-1-alexandru.elisei@arm.com>
X-Mailer: git-send-email 2.31.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The --vmm configure option was added to distinguish between the two virtual
machine managers that kvm-unit-tests supports, qemu or kvmtool. There are
plans to make kvm-unit-tests work as an EFI app, which will require changes
to the way tests are compiled. Instead of adding a new configure option
specifically for EFI and have it coexist with --vmm, or overloading the
semantics of the existing --vmm option, let's replace --vmm with the more
generic name --target.

Signed-off-by: Alexandru Elisei <alexandru.elisei@arm.com>
---
Changes in v2:

* Removed the RFC tag and cover letter.
* Removed --vmm entirely.

 configure | 19 ++++++++++---------
 1 file changed, 10 insertions(+), 9 deletions(-)

```
#### [PATCH v4 1/2] kvm: x86: Allow userspace to handle emulation errorsFrom: Aaron Lewis <aaronlewis@google.com>
##### From: Aaron Lewis <aaronlewis@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Aaron Lewis <aaronlewis@google.com>
X-Patchwork-Id: 12227023
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 5F6D2C433ED
	for <kvm@archiver.kernel.org>; Tue, 27 Apr 2021 17:02:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 348DD61400
	for <kvm@archiver.kernel.org>; Tue, 27 Apr 2021 17:02:01 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S238802AbhD0RCn (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 27 Apr 2021 13:02:43 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:60772 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S238754AbhD0RCj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 27 Apr 2021 13:02:39 -0400
Received: from mail-qt1-x84a.google.com (mail-qt1-x84a.google.com
 [IPv6:2607:f8b0:4864:20::84a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 92EDCC061574
        for <kvm@vger.kernel.org>; Tue, 27 Apr 2021 10:01:55 -0700 (PDT)
Received: by mail-qt1-x84a.google.com with SMTP id
 y10-20020a05622a004ab029019d4ad3437cso23700420qtw.12
        for <kvm@vger.kernel.org>; Tue, 27 Apr 2021 10:01:55 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=aEVIchbQhPntYj9IZ23e6vw4PNTXNE8aNVePf+vlT80=;
        b=KfAbMd2OkVR9+gmcysn545F2poZHRthoXbijwPWROnnnyXb14sCbcMSBZD66k82i4Q
         Q1Zmer0aAk5WX4vgWs6F5RlHS7JqdaDx0xXzGyMUhO7IuOVebA44Zs1IiqqrH9jytsTr
         /QbqaGUC+W3RScQHZz3oPzEah6gGKpCXexsQmeL1ThZXvNDA1J/LXiSsMV6nK1uDVZpO
         FH+Es0aARr/2Zu2w6LzV0pQwFy1YjfuKQH6E3GLSa5hGEiAJIVmeEanqr9X0l8jOnPf6
         NnK7jtHv1eDuGb4fepbid7bXyBVW6tw6hoMaFkYu+tB3YQOWNVC6FO2GEdSdHN5pzOK3
         Tx/w==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=aEVIchbQhPntYj9IZ23e6vw4PNTXNE8aNVePf+vlT80=;
        b=T1ArW6PtwrohERbmC/3TL8TOUh1Kxq0i9ukZbiHTan9Tqx/IaIMIxV2rlpp5DWz3P9
         T43TR/J0wJAON1TYsoq2Jf2ULGN8YyjK5z2Lhr/v/dxl3fiOk609mYAClB7nt5dn2zTG
         zSI25KY/rLAzdur5RiqlCYORPtm0spuYt8eyzZkIiw1h8IomRX2/guKucd5g2WKX0NV5
         k48/VWAMjXJQWkqemxA+CUgr8dW6HQAyF9EwXp+Ewx8QrV/CWNQsJfiNZUrn+tv5i6k7
         r6gCPt10KD06H5Kgkc+MB6345IU5UhLxDx7I2c+Gw0YdorIn10Yk6nRSHtcyhpBn13TL
         Vuhw==
X-Gm-Message-State: AOAM532F9P7QiVe0x6rEHzPf+6vDEBJFSN8geRuQ7UzRYZ+tPqvQ4YZU
        YOx/N1K+JEDBhVL5xO9MmYm23oKrDdeqBEbJ
X-Google-Smtp-Source: 
 ABdhPJyjALWOKenDjuGnTo35BWcLUUTJsh+evAntzKKxCYu7Vm6QVTvIwTYnXbKyJ6pmWlhOAolUcUPRQiYzowV4
X-Received: from aaronlewis1.sea.corp.google.com
 ([2620:15c:100:202:de04:ef9c:253d:9ead])
 (user=aaronlewis job=sendgmr) by 2002:a0c:f392:: with SMTP id
 i18mr13053931qvk.10.1619542914656; Tue, 27 Apr 2021 10:01:54 -0700 (PDT)
Date: Tue, 27 Apr 2021 09:59:58 -0700
In-Reply-To: <20210427165958.705212-1-aaronlewis@google.com>
Message-Id: <20210427165958.705212-2-aaronlewis@google.com>
Mime-Version: 1.0
References: <20210427165958.705212-1-aaronlewis@google.com>
X-Mailer: git-send-email 2.31.1.498.g6c1eba8ee3d-goog
Subject: [PATCH v4 1/2] kvm: x86: Allow userspace to handle emulation errors
From: Aaron Lewis <aaronlewis@google.com>
To: david.edmondson@oracle.com, seanjc@google.com, jmattson@google.com
Cc: kvm@vger.kernel.org, Aaron Lewis <aaronlewis@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add a fallback mechanism to the in-kernel instruction emulator that
allows userspace the opportunity to process an instruction the emulator
was unable to.  When the in-kernel instruction emulator fails to process
an instruction it will either inject a #UD into the guest or exit to
userspace with exit reason KVM_INTERNAL_ERROR.  This is because it does
not know how to proceed in an appropriate manner.  This feature lets
userspace get involved to see if it can figure out a better path
forward.

Signed-off-by: Aaron Lewis <aaronlewis@google.com>
---
 Documentation/virt/kvm/api.rst  | 18 ++++++++++++++++
 arch/x86/include/asm/kvm_host.h |  6 ++++++
 arch/x86/kvm/x86.c              | 37 +++++++++++++++++++++++++++++----
 include/uapi/linux/kvm.h        | 23 ++++++++++++++++++++
 tools/include/uapi/linux/kvm.h  | 23 ++++++++++++++++++++
 5 files changed, 103 insertions(+), 4 deletions(-)

```
#### [PATCH 1/6] KVM: x86/mmu: Track if shadow MMU activeFrom: Ben Gardon <bgardon@google.com>
##### From: Ben Gardon <bgardon@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ben Gardon <bgardon@google.com>
X-Patchwork-Id: 12227647
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 9E312C433B4
	for <kvm@archiver.kernel.org>; Tue, 27 Apr 2021 22:36:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7E628610A2
	for <kvm@archiver.kernel.org>; Tue, 27 Apr 2021 22:36:46 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S237153AbhD0Wh2 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 27 Apr 2021 18:37:28 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:50038 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S237070AbhD0Wh1 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 27 Apr 2021 18:37:27 -0400
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 737B6C061760
        for <kvm@vger.kernel.org>; Tue, 27 Apr 2021 15:36:41 -0700 (PDT)
Received: by mail-yb1-xb4a.google.com with SMTP id
 c1-20020a5b0bc10000b02904e7c6399b20so39456037ybr.12
        for <kvm@vger.kernel.org>; Tue, 27 Apr 2021 15:36:41 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=hHwlLUDiyb5KZWQJivPUqbRlaxgxwy3BBJV8Ity3Kbo=;
        b=otlddGc/Vgp5GvUSMNcJTh8thjsLeNZa2+H0rpxyB2THPXRytUVAU/kVjwWQcB31l/
         +cHc9GCRnMX9FQdZMldUXENz/gkNNeJFSYobkrbLLAt8LA7C/VFJ/EmXPXrMSryfOZsw
         BB8SpdcCBMO2jSPQoDzsReBH2cZjGgx5Hc0PqfyBSQ/gW16xMTQkqx2U4ZkVJ80viWXh
         1qSweEBrnpVOCheuABaVrMshGTfAkupn9JVVTN234ddDv2ekSNWLNJ1NhRShqonPy5ea
         g9PW9noDnMdvxKNt3ZQRHkHuoVshsa5ITP5sD121l5t7Qw+vrxjPjPmjOacBrZ7IjZdj
         /uCg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=hHwlLUDiyb5KZWQJivPUqbRlaxgxwy3BBJV8Ity3Kbo=;
        b=BZO0dcrvWvRhyC5yEhct98zXEeB2mh/G9rf5mSgwfiYazjNKFjk7+1cXV9vRfdCauj
         UPUTSjj1cRRrLHMc9C8VgLwr7zR/dk83crYFfSvMJ3+qFOu2J4l9fK9UqYOnJwsY9Svu
         9z9nLDlErnNKRZ3Itbwk6+KGGzQAZKMTuTv/fK7BOpmMRCG5mr0ALXWTXpU1CHrJjukk
         0RzwSm28uVgP8Vrit3dLH0QMoIGZ7oarDrZcUMnZXHureLJEkNpXiZTbGLVXts1UTKRK
         CWYkrc1gf0fQ/IesoUJkOhUCeJp8LNBnHpkrG/UepCEwIiWyVVlXkOxBvdLgaNzXuwJE
         JFNw==
X-Gm-Message-State: AOAM533iortId5kbsm+0CL1Ez/Bb6bgandPvF+oxvfywgKmODSOfK9Cz
        mQ2Zxic1koVjSF/piBLcZZLLE6ZvmYEJ
X-Google-Smtp-Source: 
 ABdhPJxz5xOYP7MEBqOp+wqGfgfhga68bYGbJL5xGkLN3JunTQIxF+Yh/jbsJ4izS0k4xTwMTQdvpUF+tnPr
X-Received: from bgardon.sea.corp.google.com
 ([2620:15c:100:202:d0b5:c590:c6b:bd9c])
 (user=bgardon job=sendgmr) by 2002:a25:3bd7:: with SMTP id
 i206mr5225144yba.150.1619563000673; Tue, 27 Apr 2021 15:36:40 -0700 (PDT)
Date: Tue, 27 Apr 2021 15:36:30 -0700
In-Reply-To: <20210427223635.2711774-1-bgardon@google.com>
Message-Id: <20210427223635.2711774-2-bgardon@google.com>
Mime-Version: 1.0
References: <20210427223635.2711774-1-bgardon@google.com>
X-Mailer: git-send-email 2.31.1.498.g6c1eba8ee3d-goog
Subject: [PATCH 1/6] KVM: x86/mmu: Track if shadow MMU active
From: Ben Gardon <bgardon@google.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>, Peter Xu <peterx@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Peter Shier <pshier@google.com>,
        Junaid Shahid <junaids@google.com>,
        Jim Mattson <jmattson@google.com>,
        Yulei Zhang <yulei.kernel@gmail.com>,
        Wanpeng Li <kernellwp@gmail.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Xiao Guangrong <xiaoguangrong.eric@gmail.com>,
        Ben Gardon <bgardon@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add a field to each VM to track if the shadow / legacy MMU is actually
in use. If the shadow MMU is not in use, then that knowledge opens the
door to other optimizations which will be added in future patches.

Signed-off-by: Ben Gardon <bgardon@google.com>
---
 arch/x86/include/asm/kvm_host.h |  2 ++
 arch/x86/kvm/mmu/mmu.c          | 10 +++++++++-
 arch/x86/kvm/mmu/mmu_internal.h |  2 ++
 arch/x86/kvm/mmu/tdp_mmu.c      |  6 ++++--
 arch/x86/kvm/mmu/tdp_mmu.h      |  4 ++--
 5 files changed, 19 insertions(+), 5 deletions(-)

```
#### [PATCH] uio: uio_pci_generic: add memory resource mappings
##### From: Firas Ashkar <firas.ashkar@savoirfairelinux.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Firas Ashkar <firas.ashkar@savoirfairelinux.com>
X-Patchwork-Id: 12226803
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A92A9C433ED
	for <kvm@archiver.kernel.org>; Tue, 27 Apr 2021 15:07:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7E6D4610FA
	for <kvm@archiver.kernel.org>; Tue, 27 Apr 2021 15:07:10 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S237429AbhD0PHv (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 27 Apr 2021 11:07:51 -0400
Received: from mail.savoirfairelinux.com ([208.88.110.44]:33586 "EHLO
        mail.savoirfairelinux.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S237473AbhD0PHp (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 27 Apr 2021 11:07:45 -0400
Received: from localhost (localhost [127.0.0.1])
        by mail.savoirfairelinux.com (Postfix) with ESMTP id D60449C141B;
        Tue, 27 Apr 2021 11:06:58 -0400 (EDT)
Received: from mail.savoirfairelinux.com ([127.0.0.1])
        by localhost (mail.savoirfairelinux.com [127.0.0.1]) (amavisd-new,
 port 10032)
        with ESMTP id ZaogdT5ilxkI; Tue, 27 Apr 2021 11:06:58 -0400 (EDT)
Received: from localhost (localhost [127.0.0.1])
        by mail.savoirfairelinux.com (Postfix) with ESMTP id 7262C9C142A;
        Tue, 27 Apr 2021 11:06:58 -0400 (EDT)
X-Virus-Scanned: amavisd-new at mail.savoirfairelinux.com
Received: from mail.savoirfairelinux.com ([127.0.0.1])
        by localhost (mail.savoirfairelinux.com [127.0.0.1]) (amavisd-new,
 port 10026)
        with ESMTP id swTp57AS6AwL; Tue, 27 Apr 2021 11:06:58 -0400 (EDT)
Received: from barbarian.mtl.sfl (unknown [192.168.51.254])
        by mail.savoirfairelinux.com (Postfix) with ESMTPSA id 4AF7A9C141B;
        Tue, 27 Apr 2021 11:06:58 -0400 (EDT)
From: Firas Ashkar <firas.ashkar@savoirfairelinux.com>
To: gregkh@linuxfoundation.org, mst@redhat.com
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Firas Ashkar <firas.ashkar@savoirfairelinux.com>
Subject: [PATCH] uio: uio_pci_generic: add memory resource mappings
Date: Tue, 27 Apr 2021 11:06:46 -0400
Message-Id: <20210427150646.3074218-1-firas.ashkar@savoirfairelinux.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

import memory resources from underlying pci device, thus allowing
userspace applications to memory map those resources.

Signed-off-by: Firas Ashkar <firas.ashkar@savoirfairelinux.com>
---
:100644 100644 c7d681fef198 efc43869131d M	drivers/uio/uio_pci_generic.c
 drivers/uio/uio_pci_generic.c | 32 ++++++++++++++++++++++++++++++++
 1 file changed, 32 insertions(+)

```
#### [PATCH v2] uio: uio_pci_generic: add memory resource mappings
##### From: Firas Ashkar <firas.ashkar@savoirfairelinux.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Firas Ashkar <firas.ashkar@savoirfairelinux.com>
X-Patchwork-Id: 12227217
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 9989FC433ED
	for <kvm@archiver.kernel.org>; Tue, 27 Apr 2021 20:10:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5CB0D61178
	for <kvm@archiver.kernel.org>; Tue, 27 Apr 2021 20:10:52 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S236459AbhD0ULe (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 27 Apr 2021 16:11:34 -0400
Received: from mail.savoirfairelinux.com ([208.88.110.44]:48822 "EHLO
        mail.savoirfairelinux.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S235412AbhD0ULe (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 27 Apr 2021 16:11:34 -0400
Received: from localhost (localhost [127.0.0.1])
        by mail.savoirfairelinux.com (Postfix) with ESMTP id EF7369C02D0;
        Tue, 27 Apr 2021 16:10:49 -0400 (EDT)
Received: from mail.savoirfairelinux.com ([127.0.0.1])
        by localhost (mail.savoirfairelinux.com [127.0.0.1]) (amavisd-new,
 port 10032)
        with ESMTP id PINCznNH0R6Y; Tue, 27 Apr 2021 16:10:49 -0400 (EDT)
Received: from localhost (localhost [127.0.0.1])
        by mail.savoirfairelinux.com (Postfix) with ESMTP id 670A29C0D2A;
        Tue, 27 Apr 2021 16:10:49 -0400 (EDT)
X-Virus-Scanned: amavisd-new at mail.savoirfairelinux.com
Received: from mail.savoirfairelinux.com ([127.0.0.1])
        by localhost (mail.savoirfairelinux.com [127.0.0.1]) (amavisd-new,
 port 10026)
        with ESMTP id 6pLUmLbSCXfx; Tue, 27 Apr 2021 16:10:49 -0400 (EDT)
Received: from barbarian.mtl.sfl (unknown [192.168.51.254])
        by mail.savoirfairelinux.com (Postfix) with ESMTPSA id 3DA1E9C02D0;
        Tue, 27 Apr 2021 16:10:49 -0400 (EDT)
From: Firas Ashkar <firas.ashkar@savoirfairelinux.com>
To: gregkh@linuxfoundation.org, mst@redhat.com
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Firas Ashkar <firas.ashkar@savoirfairelinux.com>
Subject: [PATCH v2] uio: uio_pci_generic: add memory resource mappings
Date: Tue, 27 Apr 2021 16:10:46 -0400
Message-Id: <20210427201046.4005820-1-firas.ashkar@savoirfairelinux.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

import memory resources from underlying pci device, thus allowing
userspace applications to memory map those resources.

without this change, current implementation, does not populate the
memory maps and are not shown under the corresponding sysfs uio entry:

root@apalis-imx8:~# echo "ad00 0122" > \
			/sys/bus/pci/drivers/uio_pci_generic/new_id
[   55.736433] uio_pci_generic 0000:01:00.0: enabling device (0000 -> 0002)
root@apalis-imx8:~# ls -lsrt /sys/class/uio/uio0/
     0 -rw-r--r--    1 root     root          4096 Apr 27 18:52 uevent
     0 -r--r--r--    1 root     root          4096 Apr 27 18:52 version
     0 -r--r--r--    1 root     root          4096 Apr 27 18:52 suppliers
     0 lrwxrwxrwx    1 root     root             0 Apr 27 18:52 subsystem
-> ../../../../../../../../../class/uio
     0 drwxr-xr-x    2 root     root             0 Apr 27 18:52 power
     0 -r--r--r--    1 root     root          4096 Apr 27 18:52 name
     0 -r--r--r--    1 root     root          4096 Apr 27 18:52 event
     0 lrwxrwxrwx    1 root     root             0 Apr 27 18:52 device
-> ../../../0000:01:00.0
     0 -r--r--r--    1 root     root          4096 Apr 27 18:52 dev
     0 -r--r--r--    1 root     root          4096 Apr 27 18:52 consumers
root@apalis-imx8:~#

with the proposed changed, have following instead:
root@apalis-imx8:~# ls -lsrt /sys/class/uio/uio0/
     0 -rw-r--r--    1 root     root          4096 Apr 27 19:06 uevent
     0 -r--r--r--    1 root     root          4096 Apr 27 19:06 version
     0 -r--r--r--    1 root     root          4096 Apr 27 19:06 suppliers
     0 lrwxrwxrwx    1 root     root             0 Apr 27 19:06 subsystem
-> ../../../../../../../../../class/uio
     0 drwxr-xr-x    2 root     root             0 Apr 27 19:06 power
     0 -r--r--r--    1 root     root          4096 Apr 27 19:06 name
     0 drwxr-xr-x    4 root     root             0 Apr 27 19:06 maps
     0 -r--r--r--    1 root     root          4096 Apr 27 19:06 event
     0 lrwxrwxrwx    1 root     root             0 Apr 27 19:06 device
-> ../../../0000:01:00.0
     0 -r--r--r--    1 root     root          4096 Apr 27 19:06 dev
     0 -r--r--r--    1 root     root          4096 Apr 27 19:06 consumers
root@apalis-imx8:~#

root@apalis-imx8:~# ls -lsrt /sys/class/uio/uio0/maps/
     0 drwxr-xr-x    2 root     root             0 Apr 27 19:07 map1
     0 drwxr-xr-x    2 root     root             0 Apr 27 19:07 map0
root@apalis-imx8:~#

root@apalis-imx8:~# cat /sys/class/uio/uio0/maps/map1/addr
0x0000000062000000
root@apalis-imx8:~#

root@apalis-imx8:~# cat /sys/class/uio/uio0/maps/map1/size
0x0000000000200000
root@apalis-imx8:~#

tested on AltaData ARINC 429 MiniPCIE module on imx8qm-apalis-ixora-v1.2

Signed-off-by: Firas Ashkar <firas.ashkar@savoirfairelinux.com>
---

Notes:
    Changes in V2
    * add detailed description why this change is needed
    * add test hardware name and version

:100644 100644 c7d681fef198 efc43869131d M	drivers/uio/uio_pci_generic.c
 drivers/uio/uio_pci_generic.c | 32 ++++++++++++++++++++++++++++++++
 1 file changed, 32 insertions(+)

```
#### [PATCH v4 1/2] kvm: x86: Allow userspace to handle emulation errorsFrom: Aaron Lewis <aaronlewis@google.com>
##### From: Aaron Lewis <aaronlewis@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Aaron Lewis <aaronlewis@google.com>
X-Patchwork-Id: 12227027
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 465C4C433B4
	for <kvm@archiver.kernel.org>; Tue, 27 Apr 2021 17:03:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0E1B960240
	for <kvm@archiver.kernel.org>; Tue, 27 Apr 2021 17:03:47 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S235709AbhD0RE3 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 27 Apr 2021 13:04:29 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:32960 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S235647AbhD0RE2 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 27 Apr 2021 13:04:28 -0400
Received: from mail-qk1-x74a.google.com (mail-qk1-x74a.google.com
 [IPv6:2607:f8b0:4864:20::74a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 366A5C061574
        for <kvm@vger.kernel.org>; Tue, 27 Apr 2021 10:03:45 -0700 (PDT)
Received: by mail-qk1-x74a.google.com with SMTP id
 h190-20020a3785c70000b02902e022511825so23354766qkd.7
        for <kvm@vger.kernel.org>; Tue, 27 Apr 2021 10:03:45 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=aEVIchbQhPntYj9IZ23e6vw4PNTXNE8aNVePf+vlT80=;
        b=S3gBn4rr5F7xQ+aFuOiRo9zM1LuyLB/EcfbYheaWMljK0Rb3j6r1aoEGkcPHCcZ7Nc
         ArVaK7mKZgOFFzwP9rx9W0cb5sOSZPoB7coIWpYaExOmJ39uLc4fU7PBiR/tmB7wHHXE
         8NSFW3C3lBXfb8NLGOLtsoeQZa8weLbSMsQmE9YdpzThzumzpVbP7ARADWvpukyDxf5G
         c07g8FnxxTfa34p/9f68M5+FA0NWLnHi5Mqq4v80huhSeEuoth1fgkzg5RABGRxPi2nN
         JCYqdQ4NUPHaoEAVN2keQS60w6w6Ywm8Wo832ak92eekX/p/8EG4NqybjM2RQOomyiRQ
         3+Jw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=aEVIchbQhPntYj9IZ23e6vw4PNTXNE8aNVePf+vlT80=;
        b=eU+wkQqoWP8nOX6XwDIztHJDc2YpPakmUUTZSJUb+ZU+BrZecIdA1q1MFvk0Po41MK
         3dZShXU+hoBPxuugyVACmP9vnV+Z7vrt/mhdGI7x0Vfm5Qe+qljm8tTSP0f0nzZJYVt5
         yeTQy6iGx+CX5XX/FPn2bTyw6v3+6DoinO5M6PIsKxGT4JXeerlBdJSevUk7wVz+LENF
         NoqsUNEsdEtsnx7Mzd/A97raBmrb3GkcJBw/oI+EcFMcuU8jUiRXBkdGs21r5FHdcx3A
         OmR3sD2XFBMpEFAUyGmA4/loOgxe1YSGGILsHBd8ejyJndVGpK/UApznGWeh9yKq+3FS
         RymQ==
X-Gm-Message-State: AOAM531d7XS1yiYWjjzMeIFsIb0rr6YfvAxYDhskehiV1vZRPQ9ywo4Q
        dUq/gBzr84jrMcdOBS0k+Qb97JV/t9pJXuOg
X-Google-Smtp-Source: 
 ABdhPJyz8mi9GEoZ3rjDM33UFC6BVB/W3Kes/71OYPR+OK6Vi4mmWDBsOP+rs3816nnGt+f3sYnlVzmh7PGmbq/Y
X-Received: from aaronlewis1.sea.corp.google.com
 ([2620:15c:100:202:de04:ef9c:253d:9ead])
 (user=aaronlewis job=sendgmr) by 2002:a0c:bec3:: with SMTP id
 f3mr24654873qvj.49.1619543024411; Tue, 27 Apr 2021 10:03:44 -0700 (PDT)
Date: Tue, 27 Apr 2021 10:03:32 -0700
Message-Id: <20210427170332.706287-1-aaronlewis@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.1.498.g6c1eba8ee3d-goog
Subject: [PATCH v4 1/2] kvm: x86: Allow userspace to handle emulation errors
From: Aaron Lewis <aaronlewis@google.com>
To: david.edmondson@oracle.com, seanjc@google.com, jmattson@google.com
Cc: kvm@vger.kernel.org, Aaron Lewis <aaronlewis@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add a fallback mechanism to the in-kernel instruction emulator that
allows userspace the opportunity to process an instruction the emulator
was unable to.  When the in-kernel instruction emulator fails to process
an instruction it will either inject a #UD into the guest or exit to
userspace with exit reason KVM_INTERNAL_ERROR.  This is because it does
not know how to proceed in an appropriate manner.  This feature lets
userspace get involved to see if it can figure out a better path
forward.

Signed-off-by: Aaron Lewis <aaronlewis@google.com>
---
 Documentation/virt/kvm/api.rst  | 18 ++++++++++++++++
 arch/x86/include/asm/kvm_host.h |  6 ++++++
 arch/x86/kvm/x86.c              | 37 +++++++++++++++++++++++++++++----
 include/uapi/linux/kvm.h        | 23 ++++++++++++++++++++
 tools/include/uapi/linux/kvm.h  | 23 ++++++++++++++++++++
 5 files changed, 103 insertions(+), 4 deletions(-)

```
#### [PATCH 1/3] x86/sev-es: Rename sev-es.{ch} to sev.{ch}
##### From: Brijesh Singh <brijesh.singh@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Brijesh Singh <brijesh.singh@amd.com>
X-Patchwork-Id: 12226449
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,
	SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 948C8C433B4
	for <kvm@archiver.kernel.org>; Tue, 27 Apr 2021 11:17:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 646B06101D
	for <kvm@archiver.kernel.org>; Tue, 27 Apr 2021 11:17:47 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S235793AbhD0LSZ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 27 Apr 2021 07:18:25 -0400
Received: from mail-eopbgr750082.outbound.protection.outlook.com
 ([40.107.75.82]:21193
        "EHLO NAM02-BL2-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S235860AbhD0LSL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 27 Apr 2021 07:18:11 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=YlkbJoJoGq5WT/Twoh2hRZyOXn85qE0UpzENiov8USYixav0Wj9GhZneFIzRnwvF9L0Uf0X2LWDIHJnfkbAfIy5rxHM2bViXS3WT24O+9/XKzJndgoDKuJYkGKaixu8Ky/CLLSHWsNCCCEVENR5embdvMuWYMTHWZcrbsMagbG7WmRH0ZJWIE8FRlceVq0rVH0ljWU6SkiQnrhGiKVfDp5rzUjYoaew4EnyUbDNJRAZYRI0ealoLRh/1mw/xHMUshQVlOmS6jw6HZTjUaQBaDVvTw7nYl2Kq6oCaRV191FubXLkA+nH9sucZdY5N65OP32Df18aYJjKpPSHo94Q9CQ==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=2nOEZicBp1Y3rjtNv6M78nq8vWBASOcaGaeP5+7Aj0E=;
 b=I/bn4V6hsn9TwafW8RGF+o1j7fYYDE9LSeEx1g/kI5n4WEbh5LHuMWN44YsjZBHIblNXoOusm965p0UcTMcFU1xCgfcFcsG8fWMrdWqwsgIapHMqozHmzrC+w9fa1vF6OX9+dfogqRgNXfcAazk9qd78HQ6qbNfexpuggsa821nfCyLT+AjKhKv3HfdGjMiyfiuDYQURkTxJmiXNJE+vYyWzTsC0L0d4Uk9RKvS5n2gHnNoS/Qw/tMlb8aPlM148jiQXXuIOgMX0e1nfkhCfw8JvXh0OjtxF2tvBMoRdDQZdSJCz57DraJ2vBqbj+q4naFfHCnvQ9lWbod5No0vrCA==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=amd.com; s=selector1;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=2nOEZicBp1Y3rjtNv6M78nq8vWBASOcaGaeP5+7Aj0E=;
 b=0FQRl/XWpQzccfmsFdg43S5cNyFZGRCaCE9dxLdk4TwIN/gbXVIi9oWY4AIvKhop5OjCjfU/mZA8+FzTN3jNb3B2lHqcZuCkSJj2ZW4UyNNNhhtJ68nilBPk26qZFN+3lEePzuNyB4EfaY0r7qwzxdxle1dGFZeb2aRZSEdX57k=
Authentication-Results: kernel.org; dkim=none (message not signed)
 header.d=none;kernel.org; dmarc=none action=none header.from=amd.com;
Received: from SN6PR12MB2718.namprd12.prod.outlook.com (2603:10b6:805:6f::22)
 by SA0PR12MB4432.namprd12.prod.outlook.com (2603:10b6:806:98::16) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4065.26; Tue, 27 Apr
 2021 11:16:50 +0000
Received: from SN6PR12MB2718.namprd12.prod.outlook.com
 ([fe80::9898:5b48:a062:db94]) by SN6PR12MB2718.namprd12.prod.outlook.com
 ([fe80::9898:5b48:a062:db94%6]) with mapi id 15.20.4065.027; Tue, 27 Apr 2021
 11:16:50 +0000
From: Brijesh Singh <brijesh.singh@amd.com>
To: x86@kernel.org
Cc: tglx@linutronix.de, bp@alien8.de, jroedel@suse.de,
        thomas.lendacky@amd.com, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, pbonzini@redhat.com,
        Brijesh Singh <brijesh.singh@amd.com>
Subject: [PATCH 1/3] x86/sev-es: Rename sev-es.{ch} to sev.{ch}
Date: Tue, 27 Apr 2021 06:16:34 -0500
Message-Id: <20210427111636.1207-2-brijesh.singh@amd.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20210427111636.1207-1-brijesh.singh@amd.com>
References: <20210427111636.1207-1-brijesh.singh@amd.com>
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: SN4PR0201CA0054.namprd02.prod.outlook.com
 (2603:10b6:803:20::16) To SN6PR12MB2718.namprd12.prod.outlook.com
 (2603:10b6:805:6f::22)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from sbrijesh-desktop.amd.com (165.204.77.1) by
 SN4PR0201CA0054.namprd02.prod.outlook.com (2603:10b6:803:20::16) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4087.25 via Frontend
 Transport; Tue, 27 Apr 2021 11:16:49 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: c2059cdf-03e8-42b8-4883-08d9096df3e7
X-MS-TrafficTypeDiagnostic: SA0PR12MB4432:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SA0PR12MB4432083BF27C8506BBA7760FE5419@SA0PR12MB4432.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:8882;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 ArJzbGJWQY1a2sLb8ohcWfJ9FehhhMVuF2gcnDTAijGFiprJt5xfEgQzBaOi/xLTPbVakuK1Qaave7pT56Lmv4PUlzbYvJaTQe/7efVo5Vuq2M3hwnMpl0ouB7vUBB60f5bO8vn2zQEwVVJbu7K/EjImPYGf52Q2yvNnCI5OSpl3lFIm0TowT2mGJbLECegShFlt61KXsb6KZR9lThycDGzrFakqHPwmM63dnAyH7nLPG6QlrPx4qIU/2uzy6oVyR3HYT/goYfYZdDT1tLhAgzhQ7itjONQBKw5W6YLYJeRCWysFRvQhnlUBk/sc3LXBFCG9KbJCOVlmde+/u2B5y/DzeR3Spq6bBo8AqeeWPNTYXp7MvFGN8BI/ZabK+wPJLniQvi9vPeoqy8YHQaFGz5u5sIPxd+ohOhmoW+8yinhSn2/TixUEb2W9PfRYqODerZbA5iJejY3UAIvcdXN3aBs0SIrtzM+lj2L6HAAkFZPvq/VGz7y+hQnpiXYSvI2Ma4Nxm1BkDH/sue4+IwR9tLDYqdZrbSCHmw0/rywEf7UjXBmWC2wTaWRbn+WIYSK1a8mhLOwjuh9XINXfOO0siXxkGsrobFhE6obI/muO+FDTzbQON2jD8ce92xjQ0oMbZHsDg31lmrrOvT79IgqhFt7hFu1KUffSpV4Uyg3lucE=
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN6PR12MB2718.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(346002)(396003)(136003)(366004)(376002)(39860400002)(66556008)(66476007)(5660300002)(2616005)(956004)(478600001)(316002)(6916009)(66946007)(6666004)(44832011)(52116002)(86362001)(7696005)(1076003)(36756003)(8676002)(26005)(8936002)(16526019)(4326008)(2906002)(6486002)(83380400001)(186003)(38100700002)(38350700002);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 TuDExmeKGFXWd7k+qEU1r78Nb5W0r0IJqsAp/CH7m/63vjJOGxd+HsPqSN8mdLtdTW5P1gzHSxUtvTiiKn4EjXCPHarYi1Q0Se8BjlIOHtSQwDntsDFFHRqdepcYYCFIiwojuiZquDlVsSNwyYlyUgkgHaK4ZYWchr3rW3mqst/HykKHAushmzEkvkfuHOCPgpljybhkfFjF1/levTukjIp0pFotJWlOIeY8gqdG/zDnnBzlhjfu23/fpp4pAPXMxz5DAn8quW52LT2BgFRUNfbNx90aAnp1YDiwgNRD2QYQv8BXZmrKX9f4zD/231gFdhyfuzuKZY++154V8qD2I3CsGtPtWjAiJpqE/Hs7cGHiVquag5otqf+3SoMI5NKI2ok/v/XB4xSaNS9gD7clg5jmn0liEgcZjiAjPl2vzUpkCSKQovhqZDxPQ2eBma5arQwDuZQvl94bCZ1u8463DG+hzyrQ93V2qmpClsZxh2TzZ47q5AtD8UWFpede93kzVJiYnEExCikpch1E4p0I6N5yKK1kBrOqsveKIha10beUjxMUpy/PRV5oxUMsp16wnNsWloa2NKIFgZc7EIX5A58WYygySvopb/TxB37xaS3H9fkkTGG/omHyOlnf5jQGaZ1mCV+SlEYxZJBn4jhV3kTzb+tWrY/xugN4IfIva7ASACpCwcVWpInL2rK90YInRhH/bEKKs94LabPINC0pQoL4IaCvs5ssajAhIC1a5EBL3tSHyJETLEU3zbO0Pc/ncdbuzNV2K5S9WUsrtELN+XSt/WA0b8nQwEhSgokFbQD1cq32rIBaUx3fWhBrKqZczj0CXy6U3QGWR//OM/axmxwaFQ76zrl7ewzjf0Y+8U8u3v4rM+qq4AEq/YHT8QqI8MHijF/i8Ute4oNAwIX0UT3wvcEJ6gkiRozmeWlez2x6ywqahVQPwxhqjDhd4m8lvWmqQFPOWAFExCe/mD/tKp5tPUnR1kfCiWwRX82ZAAur2KUX6qWV95fy0PvsavrSvJknAzFSvDlnOwzbsKJXJM0YOrCyi1t3Ze2mILE67x96VU0zbG2F7e9RTX+FMjJJKattH0e9rCEl9eBQEiA/e/Z5H7+Y8ivlWAWkBUtSCOrn7S5uO7sAXEvJ5UBl+fJa7hyjkLMLNJ9M/AQ342E2P0mno9wvQD2tiuE5VoLpOY3RCuQMjDqkBRrRA5eSnLWsX9OmNOxA5qETnfuQO65tgLQthDtiJ08akFFsKAW8Nt4USWKdHRliXvotdSnihyDv4im+ERnY0L1iNVrlxuXdJ+GnpNFFWNJYiQRHR9Ezy6rPCvN8oOR3OdEyGHXvAR5K
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 c2059cdf-03e8-42b8-4883-08d9096df3e7
X-MS-Exchange-CrossTenant-AuthSource: SN6PR12MB2718.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 27 Apr 2021 11:16:49.9920
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 PK/e8WYIcGQnL2cMV44TO/Dm3QfyigKWe0CQdm8JDTHbWk+99mzQo/DqjxUTQvd9PjnmhLLq8f+AxpxNlXJFyA==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SA0PR12MB4432
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The SEV-SNP builds upon the SEV-ES functionality while adding new hardware
protection. Version 2 of the GHCB specification adds new NAE events that
are SEV-SNP specific. Rename the sev-es.{ch} to sev.{ch} so that we can
consolidate all the SEV-ES and SEV-SNP in a one place.

Signed-off-by: Brijesh Singh <brijesh.singh@amd.com>
---
 arch/x86/boot/compressed/Makefile                 | 6 +++---
 arch/x86/boot/compressed/{sev-es.c => sev.c}      | 4 ++--
 arch/x86/include/asm/{sev-es.h => sev.h}          | 0
 arch/x86/kernel/Makefile                          | 6 +++---
 arch/x86/kernel/head64.c                          | 2 +-
 arch/x86/kernel/nmi.c                             | 2 +-
 arch/x86/kernel/{sev-es-shared.c => sev-shared.c} | 0
 arch/x86/kernel/{sev-es.c => sev.c}               | 4 ++--
 arch/x86/mm/extable.c                             | 2 +-
 arch/x86/platform/efi/efi_64.c                    | 2 +-
 arch/x86/realmode/init.c                          | 2 +-
 11 files changed, 15 insertions(+), 15 deletions(-)
 rename arch/x86/boot/compressed/{sev-es.c => sev.c} (98%)
 rename arch/x86/include/asm/{sev-es.h => sev.h} (100%)
 rename arch/x86/kernel/{sev-es-shared.c => sev-shared.c} (100%)
 rename arch/x86/kernel/{sev-es.c => sev.c} (99%)

```
