

#### [PATCH 00/17] target/mips: Convert MSA ASE to decodetree
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <f4bug@amsat.org>

```c
From patchwork Tue Dec  8 00:36:45 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
 <f4bug@amsat.org>
X-Patchwork-Id: 11957255
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id F2960C4361B
	for <kvm@archiver.kernel.org>; Tue,  8 Dec 2020 00:37:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BD761238EB
	for <kvm@archiver.kernel.org>; Tue,  8 Dec 2020 00:37:47 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728701AbgLHAhr (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 7 Dec 2020 19:37:47 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:50392 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728689AbgLHAhq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 7 Dec 2020 19:37:46 -0500
Received: from mail-ej1-x62a.google.com (mail-ej1-x62a.google.com
 [IPv6:2a00:1450:4864:20::62a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 5325CC06179C
        for <kvm@vger.kernel.org>; Mon,  7 Dec 2020 16:37:06 -0800 (PST)
Received: by mail-ej1-x62a.google.com with SMTP id f23so22197487ejk.2
        for <kvm@vger.kernel.org>; Mon, 07 Dec 2020 16:37:06 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=OWgkzaBL8Ks+W5c6hc//5jS9TAtR2BEXueICNpeXGzI=;
        b=dA3Jz1COIag7v1M7puPMdmwoXec5vp17JFsARrNCqYYWr9GEeAr97x4gvDHoEiUlRs
         61h7Vg50DmSQ25pu5RCo7FN4NlIixt75Dmh8aQCiiWYnU1GHti7ElSExMxy6xDh+YTTC
         0tUsR/1rk4BaEvtM4zpttMWb45vyR+RNfOsdA1yP6WuwRKk5+lrenQkpCkjuY3N2Gi1s
         VlnHCQBoRusSlPaQ6DnxhDFoTZJd46+WbYFizK7IRLMJld4kiQ1NzI+fKO/CY8/zFxHZ
         RVEK47YWVx6sSNuxdnrlY1ilkxemJKEwCSpwKP7wQamiBixRgdzEd8/6o/j2UqvlXJqP
         rw/g==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id
         :mime-version:content-transfer-encoding;
        bh=OWgkzaBL8Ks+W5c6hc//5jS9TAtR2BEXueICNpeXGzI=;
        b=E6nvlEG77qvjL6WnKOZamkPlCpq+IdWXJYppfpGslCNG2N6ZH8K6Zmg+2/yyex0g/Q
         RCnSSYVuB1bgbTleV1cHjq9yfD3oZMCI/fUrOOhiN6QOYozrYla1qaad7pu1g7XD3iWJ
         xA4z15UGdoEXrQMzjxWAnxYO0XjCRZqAnotr+0aQaGyV7RXo27Avo2DMVOUpXyw9UIj4
         9Ubcje+S6BvPAWYAh1zA4801qcexH0PHe2mJZT2dqXiT0hkTNpDV60IvMm86rSVyxy5Z
         vsNfSVXovmKFxNuhZoKfU/sCIkQoqcMVBBJXcLsY8QvbYE6QSiL5hOH3U8qWvGqfHjC9
         T1ew==
X-Gm-Message-State: AOAM531hyBO5APaedbJAXoQfnP3yZivUjyx0fgDp37FklkYNJMlFcHbb
        dyFL1r0agM7IRhYDs41JsS8=
X-Google-Smtp-Source: 
 ABdhPJyOLT7IrJOkvySteoCMLX7D7ldLNTWfL3J3pXoTi91sQP7BLNIp4IPEJBTN7t8ugtAPLoMvIQ==
X-Received: by 2002:a17:906:b74b:: with SMTP id
 fx11mr21056135ejb.410.1607387825097;
        Mon, 07 Dec 2020 16:37:05 -0800 (PST)
Received: from x1w.redhat.com (101.red-88-21-206.staticip.rima-tde.net.
 [88.21.206.101])
        by smtp.gmail.com with ESMTPSA id
 mb15sm13785560ejb.9.2020.12.07.16.37.03
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 07 Dec 2020 16:37:04 -0800 (PST)
Sender: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
  <philippe.mathieu.daude@gmail.com>
From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <f4bug@amsat.org>
To: qemu-devel@nongnu.org
Cc: Aleksandar Rikalo <aleksandar.rikalo@syrmia.com>,
 Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <f4bug@amsat.org>,
 kvm@vger.kernel.org, Richard Henderson <richard.henderson@linaro.org>,
 Aurelien Jarno <aurelien@aurel32.net>, Huacai Chen <chenhuacai@kernel.org>,
 Jiaxun Yang <jiaxun.yang@flygoat.com>
Subject: [PATCH 00/17] target/mips: Convert MSA ASE to decodetree
Date: Tue,  8 Dec 2020 01:36:45 +0100
Message-Id: <20201208003702.4088927-1-f4bug@amsat.org>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Finally, we use decodetree with the MIPS target.

Starting easy with the MSA ASE. 2700+ lines extracted
from helper.h and translate.c, now built as an new
object: mod-msa_translate.o.

While the diff stat is positive by 86 lines, we actually
(re)moved code, but added (C) notices.

The most interesting patches are the 2 last ones.

Please review,

Phil.

Based-on: <20201207224335.4030582-1-f4bug@amsat.org>
(linux-user: Rework get_elf_hwcap() and support MIPS Loongson 2F/3A)
Based-on: <20201207235539.4070364-1-f4bug@amsat.org>
(target/mips: Add translate.h and fpu_translate.h headers)

Philippe Mathieu-Daudé (17):
  target/mips: Introduce ase_msa_available() helper
  target/mips: Simplify msa_reset()
  target/mips: Use CP0_Config3 to set MIPS_HFLAG_MSA
  target/mips: Simplify MSA TCG logic
  target/mips: Remove now unused ASE_MSA definition
  target/mips: Alias MSA vector registers on FPU scalar registers
  target/mips: Extract msa_translate_init() from mips_tcg_init()
  target/mips: Remove CPUMIPSState* argument from gen_msa*() methods
  target/mips: Explode gen_msa_branch() as gen_msa_BxZ_V/BxZ()
  target/mips: Rename msa_helper.c as mod-msa_helper.c
  target/mips: Move msa_reset() to mod-msa_helper.c
  target/mips: Extract MSA helpers from op_helper.c
  target/mips: Extract MSA helper definitions
  target/mips: Declare gen_msa/_branch() in 'translate.h'
  target/mips: Extract MSA translation routines
  target/mips: Introduce decode tree bindings for MSA opcodes
  target/mips: Use decode_msa32() generated from decodetree

 target/mips/cpu.h                             |    6 +
 target/mips/fpu_translate.h                   |   10 -
 target/mips/helper.h                          |  436 +---
 target/mips/internal.h                        |    4 +-
 target/mips/mips-defs.h                       |    1 -
 target/mips/translate.h                       |    4 +
 target/mips/mod-msa32.decode                  |   24 +
 target/mips/kvm.c                             |   12 +-
 .../mips/{msa_helper.c => mod-msa_helper.c}   |  429 ++++
 target/mips/mod-msa_translate.c               | 2270 +++++++++++++++++
 target/mips/op_helper.c                       |  394 ---
 target/mips/translate.c                       | 2264 +---------------
 target/mips/meson.build                       |    9 +-
 target/mips/mod-msa_helper.h.inc              |  443 ++++
 target/mips/translate_init.c.inc              |   38 +-
 15 files changed, 3215 insertions(+), 3129 deletions(-)
 create mode 100644 target/mips/mod-msa32.decode
 rename target/mips/{msa_helper.c => mod-msa_helper.c} (93%)
 create mode 100644 target/mips/mod-msa_translate.c
 create mode 100644 target/mips/mod-msa_helper.h.inc
```
#### [PATCH 0/2] Enumerate and expose AVX512_FP16 feature 
##### From: Kyung Min Park <kyung.min.park@intel.com>

```c
From patchwork Tue Dec  8 03:34:39 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kyung Min Park <kyung.min.park@intel.com>
X-Patchwork-Id: 11957481
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 954D9C4361B
	for <kvm@archiver.kernel.org>; Tue,  8 Dec 2020 03:56:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 691FC239EB
	for <kvm@archiver.kernel.org>; Tue,  8 Dec 2020 03:56:33 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726653AbgLHD4P (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 7 Dec 2020 22:56:15 -0500
Received: from mga14.intel.com ([192.55.52.115]:59706 "EHLO mga14.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726556AbgLHD4P (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 7 Dec 2020 22:56:15 -0500
IronPort-SDR: 
 S78jpoF0QNdalHYH0mrKvDC521k/uhLx+oCgLXdAYuJ6pImjLdmXvVV060jTM5JRR1RWo2Wlws
 nbUny04lgLeg==
X-IronPort-AV: E=McAfee;i="6000,8403,9828"; a="173060178"
X-IronPort-AV: E=Sophos;i="5.78,401,1599548400";
   d="scan'208";a="173060178"
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by fmsmga103.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 07 Dec 2020 19:55:34 -0800
IronPort-SDR: 
 5VaoYfYOjT0IMeSQT265ZQRj5OkGBhDd2r6N47s5OhVUEHIPti3esmiz3cT4ndAAmFnFIN8xC+
 KIFlg74j+JXA==
X-IronPort-AV: E=Sophos;i="5.78,401,1599548400";
   d="scan'208";a="363469714"
Received: from km-skylake-client-platform.sc.intel.com ([10.3.52.146])
  by orsmga008-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 07 Dec 2020 19:55:34 -0800
From: Kyung Min Park <kyung.min.park@intel.com>
To: x86@kernel.org, linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: tglx@linutronix.de, mingo@redhat.com, bp@alien8.de, hpa@zytor.com,
        pbonzini@redhat.com, sean.j.christopherson@intel.com,
        jmattson@google.com, joro@8bytes.org, vkuznets@redhat.com,
        wanpengli@tencent.com, kyung.min.park@intel.com,
        cathy.zhang@intel.com
Subject: [PATCH 0/2] Enumerate and expose AVX512_FP16 feature 
Date: Mon,  7 Dec 2020 19:34:39 -0800
Message-Id: <20201208033441.28207-1-kyung.min.park@intel.com>
X-Mailer: git-send-email 2.17.1
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Introduce AVX512_FP16 feature and expose it to KVM CPUID for processors
that support it. KVM reports this information and guests can make use
of it.

Detailed information on the instruction and CPUID feature flag can be found
in the latest "extensions" manual [1].

Reference:
[1]. https://software.intel.com/content/www/us/en/develop/download/intel-architecture-instruction-set-extensions-programming-reference.html

Cathy Zhang (1):
  x86: Expose AVX512_FP16 for supported CPUID

Kyung Min Park (1):
  Enumerate AVX512 FP16 CPUID feature flag

 arch/x86/include/asm/cpufeatures.h | 1 +
 arch/x86/kernel/cpu/cpuid-deps.c   | 1 +
 arch/x86/kvm/cpuid.c               | 2 +-
 3 files changed, 3 insertions(+), 1 deletion(-)
```
#### [kvm-unit-tests PATCH 0/2] s390x: Move from LGPL 2 to GPL 2
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
From patchwork Tue Dec  8 15:09:00 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11958771
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 29F20C4361B
	for <kvm@archiver.kernel.org>; Tue,  8 Dec 2020 15:09:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E8C4A23A75
	for <kvm@archiver.kernel.org>; Tue,  8 Dec 2020 15:09:55 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729915AbgLHPJz (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 8 Dec 2020 10:09:55 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:51546 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727925AbgLHPJy (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 8 Dec 2020 10:09:54 -0500
Received: from pps.filterd (m0098396.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 0B8F3OGV136929;
        Tue, 8 Dec 2020 10:09:14 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=DDTALXsM0JFGwV6p5LS+C2/BmUHS2x1iSw4xTD1U66U=;
 b=EZ6gTxX3zUYCUBZmPQ141rMilaEktLX6T0jfswRNGttkCWjsYJjSq7FEKY7OvpHRHBX1
 LpwNBUiNGyaJFxo4YCznO2AQUsZOJZe35njVdaJOor+XVUHtIl4UrTX+oyg6ndbAEUMq
 ntS48etwgWv2vAthhiG0O3JYU8WRKBE4C9UHZu+mmPZ/XDZoyyO/NMXAqjPEp/loKCYH
 9R3CqKesejKxDI9i1j9IqBL2hQfu1fOVMtd0zSNmeo2hjMasih0vTtlrgkqlEdUQafoJ
 VFHAB9oBtVdkfUvfLEB4dAnP4GXXMfkKfVcfbGlZmFXAriNVLsBNozlq8VyolY0vw8o1 7Q==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 359s1ee81h-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 08 Dec 2020 10:09:14 -0500
Received: from m0098396.ppops.net (m0098396.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 0B8F3bSR139249;
        Tue, 8 Dec 2020 10:09:13 -0500
Received: from ppma03fra.de.ibm.com (6b.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.107])
        by mx0a-001b2d01.pphosted.com with ESMTP id 359s1ee80d-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 08 Dec 2020 10:09:13 -0500
Received: from pps.filterd (ppma03fra.de.ibm.com [127.0.0.1])
        by ppma03fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 0B8F828K018362;
        Tue, 8 Dec 2020 15:09:11 GMT
Received: from b06cxnps4074.portsmouth.uk.ibm.com
 (d06relay11.portsmouth.uk.ibm.com [9.149.109.196])
        by ppma03fra.de.ibm.com with ESMTP id 3581u8ne3n-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 08 Dec 2020 15:09:11 +0000
Received: from d06av26.portsmouth.uk.ibm.com (d06av26.portsmouth.uk.ibm.com
 [9.149.105.62])
        by b06cxnps4074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 0B8F98Eh6685284
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 8 Dec 2020 15:09:09 GMT
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id C981FAE05A;
        Tue,  8 Dec 2020 15:09:08 +0000 (GMT)
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 35DF1AE065;
        Tue,  8 Dec 2020 15:09:08 +0000 (GMT)
Received: from linux01.pok.stglabs.ibm.com (unknown [9.114.17.81])
        by d06av26.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue,  8 Dec 2020 15:09:08 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: thuth@redhat.com, david@redhat.com, cohuck@redhat.com,
        linux-s390@vger.kernel.org
Subject: [kvm-unit-tests PATCH 0/2] s390x: Move from LGPL 2 to GPL 2
Date: Tue,  8 Dec 2020 10:09:00 -0500
Message-Id: <20201208150902.32383-1-frankja@linux.ibm.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.343,18.0.737
 definitions=2020-12-08_09:2020-12-08,2020-12-08 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxscore=0 bulkscore=0
 mlxlogscore=999 clxscore=1015 suspectscore=1 adultscore=0 malwarescore=0
 phishscore=0 spamscore=0 priorityscore=1501 impostorscore=0
 lowpriorityscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2012080093
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

KVM and the KVM unit tests should be able to share code to improve
development speed and the LGPL is currently preventing us from doing
exactly that. Additionally we have a multitude of different licenses
in s390x files: GPL 2 only, GPL 2 or greater, LGPL 2 and LGPL 2.1 or
later.

This patch set tries to move the licenses to GPL 2 where
possible. Also we introduce the SPDX identifiers so the file headers
are more readable.

Janosch Frank (2):
  s390x: Move to GPL 2 and SPDX license identifiers
  s390x: lib: Move to GPL 2 and SPDX license identifiers

 lib/s390x/asm-offsets.c     | 4 +---
 lib/s390x/asm/arch_def.h    | 4 +---
 lib/s390x/asm/asm-offsets.h | 4 +---
 lib/s390x/asm/barrier.h     | 4 +---
 lib/s390x/asm/cpacf.h       | 1 +
 lib/s390x/asm/facility.h    | 4 +---
 lib/s390x/asm/float.h       | 4 +---
 lib/s390x/asm/interrupt.h   | 4 +---
 lib/s390x/asm/io.h          | 4 +---
 lib/s390x/asm/mem.h         | 4 +---
 lib/s390x/asm/page.h        | 4 +---
 lib/s390x/asm/pgtable.h     | 4 +---
 lib/s390x/asm/sigp.h        | 4 +---
 lib/s390x/asm/spinlock.h    | 4 +---
 lib/s390x/asm/stack.h       | 4 +---
 lib/s390x/asm/time.h        | 4 +---
 lib/s390x/css.h             | 4 +---
 lib/s390x/css_dump.c        | 4 +---
 lib/s390x/css_lib.c         | 4 +---
 lib/s390x/interrupt.c       | 4 +---
 lib/s390x/io.c              | 4 +---
 lib/s390x/mmu.c             | 4 +---
 lib/s390x/mmu.h             | 4 +---
 lib/s390x/sclp-console.c    | 5 +----
 lib/s390x/sclp.c            | 4 +---
 lib/s390x/sclp.h            | 5 +----
 lib/s390x/smp.c             | 4 +---
 lib/s390x/smp.h             | 4 +---
 lib/s390x/stack.c           | 4 +---
 lib/s390x/vm.c              | 3 +--
 lib/s390x/vm.h              | 3 +--
 s390x/cmm.c                 | 4 +---
 s390x/cpumodel.c            | 4 +---
 s390x/css.c                 | 4 +---
 s390x/cstart64.S            | 4 +---
 s390x/diag10.c              | 4 +---
 s390x/diag288.c             | 4 +---
 s390x/diag308.c             | 5 +----
 s390x/emulator.c            | 4 +---
 s390x/gs.c                  | 4 +---
 s390x/iep.c                 | 4 +---
 s390x/intercept.c           | 4 +---
 s390x/pfmf.c                | 4 +---
 s390x/sclp.c                | 4 +---
 s390x/selftest.c            | 4 +---
 s390x/skey.c                | 4 +---
 s390x/skrf.c                | 4 +---
 s390x/smp.c                 | 4 +---
 s390x/sthyi.c               | 4 +---
 s390x/sthyi.h               | 4 +---
 s390x/stsi.c                | 4 +---
 s390x/uv-guest.c            | 4 +---
 s390x/vector.c              | 4 +---
 53 files changed, 53 insertions(+), 157 deletions(-)
```
#### [Patch v2 0/2] cgroup: KVM: New Encryption IDs cgroup controller
##### From: Vipin Sharma <vipinsh@google.com>

```c
From patchwork Tue Dec  8 21:35:29 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vipin Sharma <vipinsh@google.com>
X-Patchwork-Id: 11959813
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 70FB4C19437
	for <kvm@archiver.kernel.org>; Tue,  8 Dec 2020 21:37:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3D37A23B40
	for <kvm@archiver.kernel.org>; Tue,  8 Dec 2020 21:37:02 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729996AbgLHVgh (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 8 Dec 2020 16:36:37 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:49640 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727660AbgLHVgh (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 8 Dec 2020 16:36:37 -0500
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 41E5CC0613D6
        for <kvm@vger.kernel.org>; Tue,  8 Dec 2020 13:35:51 -0800 (PST)
Received: by mail-yb1-xb49.google.com with SMTP id z83so89798ybz.2
        for <kvm@vger.kernel.org>; Tue, 08 Dec 2020 13:35:51 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:message-id:mime-version:subject:from:to:cc;
        bh=w7i58lgoN4yW28AWglPeAW5jTbGmkiCZtKgp4popZcc=;
        b=cmAFANNztRVo5bcJBIrm7/VkOuuWoHPWc5pigdvPJhC9R5k1TVvIwqVsfGvJ8Kqn2W
         LofKecjevhtSgJ+OJk+3xEAbq5qqz8xUZ4BwwQH1W8dZwmQTPRSIDki7p7K5EgIonnA3
         Pme7BumHABfVNEjYhRMry7dncrf+prQy/aqsOMM/B0rErRWp79zTH2kvnEmBGTFDy8e5
         pfvheV39CD1909OjKIaQGXjXAbhjF4Ky3pMisHQiqm1WozZDkDTYZ0IwhyXohyE1zc2I
         65almQXI8ocH7FM8BJbIHjLLSJ4RoaqwMrMqCx6orRI6v/Mw1vJ5eMGd+vdPV/Fy1z/B
         khjA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:message-id:mime-version:subject:from
         :to:cc;
        bh=w7i58lgoN4yW28AWglPeAW5jTbGmkiCZtKgp4popZcc=;
        b=pCOyU0tuHtJ1FerFU6V/3xTJ+bkVhiI+to0iv4ZHOwXyowiG3Sfkfi7ZBLph7ac4vX
         2iE40J7v/LnxwHTYxUMPh9mu+DegB4x7pXI9176if7rWRRXYZPW0bp2hO1H39vDqtUGq
         lKdYVnUtHWdJ5NLuZ2q4u++Kn+FbT5hIp1EeP2ew5YyvfaVWGFNKIixmjGsOgSNjBNDT
         CFpc97mNf+3cLnbFoXOX0ao8I2oncxEFqzyeSeuNyS53TjjxDwALZnIl9QAHZMZ7GdBk
         Un8257N7C9QwfDOswE7QKe67dkv+mzH4vvOJ/pr1xYUvhlJDRmik6MfkxAXD9eNBnHJI
         8d2w==
X-Gm-Message-State: AOAM530iI6xylwKe8ZR8GKmgru912b/3bUVKwNfOVO4gLUBATYBvoRol
        DeB+SYuLPDOChNEjhxP0SqZMAdCv+efg
X-Google-Smtp-Source: 
 ABdhPJxv9t+/Yf+hfpLCJJzCVk0GjB3OzRY53aMVm1Ux4RAJduUyT84FHqlVOMF6xIeuZn/bKfCVJO4kOJ4+
Sender: "vipinsh via sendgmr" <vipinsh@vipinsh.kir.corp.google.com>
X-Received: from vipinsh.kir.corp.google.com
 ([2620:0:1008:10:1ea0:b8ff:fe75:b885])
 (user=vipinsh job=sendgmr) by 2002:a25:ed7:: with SMTP id
 206mr30793524ybo.136.1607463350496;
 Tue, 08 Dec 2020 13:35:50 -0800 (PST)
Date: Tue,  8 Dec 2020 13:35:29 -0800
Message-Id: <20201208213531.2626955-1-vipinsh@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.29.2.576.ga3fc446d84-goog
Subject: [Patch v2 0/2] cgroup: KVM: New Encryption IDs cgroup controller
From: Vipin Sharma <vipinsh@google.com>
To: thomas.lendacky@amd.com, brijesh.singh@amd.com, jon.grimm@amd.com,
        eric.vantassell@amd.com, pbonzini@redhat.com, seanjc@google.com,
        tj@kernel.org, lizefan@huawei.com, hannes@cmpxchg.org,
        frankja@linux.ibm.com, borntraeger@de.ibm.com, corbet@lwn.net
Cc: joro@8bytes.org, vkuznets@redhat.com, wanpengli@tencent.com,
        jmattson@google.com, tglx@linutronix.de, mingo@redhat.com,
        bp@alien8.de, hpa@zytor.com, gingell@google.com,
        rientjes@google.com, dionnaglaze@google.com, kvm@vger.kernel.org,
        x86@kernel.org, cgroups@vger.kernel.org, linux-doc@vger.kernel.org,
        linux-kernel@vger.kernel.org, Vipin Sharma <vipinsh@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hello,

This patch adds a new cgroup controller, Encryption IDs, to track and
limit the usage of encryption IDs on a host.

AMD provides Secure Encrypted Virtualization (SEV) and SEV with
Encrypted State (SEV-ES) to encrypt the guest OS's memory using limited
number of Address Space Identifiers (ASIDs).

This limited number of ASIDs creates issues like SEV ASID starvation and
unoptimized scheduling in the cloud infrastucture.

In the RFC patch v1, I provided only SEV cgroup controller but based
on the feedback and discussion it became clear that this cgroup
controller can be extended to be used by Intel's Trusted Domain
Extension (TDX) and s390's protected virtualization Secure Execution IDs
(SEID)

This patch series provides a generic Encryption IDs controller with
tracking support of the SEV ASIDs.

Changes in v2:
- Changed cgroup name from sev to encryption_ids.
- Replaced SEV specific names in APIs and documentations with generic
  encryption IDs.
- Providing 3 cgroup files per encryption ID type. For example in SEV,
  - encryption_ids.sev.stat (only in the root cgroup directory).
  - encryption_ids.sev.max
  - encryption_ids.sev.current

Thanks
Vipin Sharma

[1] https://lore.kernel.org/lkml/20200922004024.3699923-1-vipinsh@google.com/#r

Vipin Sharma (2):
  cgroup: svm: Add Encryption ID controller
  cgroup: svm: Encryption IDs cgroup documentation.

 .../admin-guide/cgroup-v1/encryption_ids.rst  | 108 +++++
 Documentation/admin-guide/cgroup-v2.rst       |  78 +++-
 arch/x86/kvm/svm/sev.c                        |  28 +-
 include/linux/cgroup_subsys.h                 |   4 +
 include/linux/encryption_ids_cgroup.h         |  70 +++
 include/linux/kvm_host.h                      |   4 +
 init/Kconfig                                  |  14 +
 kernel/cgroup/Makefile                        |   1 +
 kernel/cgroup/encryption_ids.c                | 430 ++++++++++++++++++
 9 files changed, 728 insertions(+), 9 deletions(-)
 create mode 100644 Documentation/admin-guide/cgroup-v1/encryption_ids.rst
 create mode 100644 include/linux/encryption_ids_cgroup.h
 create mode 100644 kernel/cgroup/encryption_ids.c
---
2.29.2.576.ga3fc446d84-goog
```
#### [PATCH v9 00/18] Add AMD SEV guest live migration support
##### From: Ashish Kalra <Ashish.Kalra@amd.com>
From: Ashish Kalra <ashish.kalra@amd.com>

```c
From patchwork Tue Dec  8 22:02:51 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ashish Kalra <Ashish.Kalra@amd.com>
X-Patchwork-Id: 11959903
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 20823C19437
	for <kvm@archiver.kernel.org>; Tue,  8 Dec 2020 22:04:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E319C23A1D
	for <kvm@archiver.kernel.org>; Tue,  8 Dec 2020 22:04:13 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730571AbgLHWD5 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 8 Dec 2020 17:03:57 -0500
Received: from mail-dm6nam10on2071.outbound.protection.outlook.com
 ([40.107.93.71]:57761
        "EHLO NAM10-DM6-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1730495AbgLHWD5 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 8 Dec 2020 17:03:57 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=CYCdBBodJ0uxIhM3eJqHQKdrR0x0lsag4GNqe9TohITuzGoUuDtAVlK0nS4FH1etdcnwXDt+569A6AlrP2+xzQ7lwWGYjp8ghS2Ro8ZTzspy6nIO8AtcG76Y/9fJI1hlfgzgoBsLGjbSQLdR/fALF3+ztjYiSKjUFNYqG7EnM3ysKGh6Vx8dowzX+f3W5b5e/73k04gTeCZz0BoXwVEh3oa3PIdAcXqW7l9s7oRKeVD3HEmtAA/c84vEesSdsyK/LhCeoiH9wQUgJJr/ctil/j3iK5+BNbKnQqmFEeSIOLuVXak/CqQYlmxloy2PqBVMPU6Bf0j5hARdD6L6MA1k5Q==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=oqb9km6Xdj9sv4bC5TjdtD0HVPfNSBqbpBU7dlNqzBo=;
 b=EnScbryHnJlnOHAoEKtGDwl7WddeOhmIIlUq17oqFBMHDy3Es7X0xtZZnL700vZb1OZ4XyLJX2GCaKELXQ2+/NAjfqkZBHUcOGw7Qxpq3U0R/6ZKvwMVxobWVO9pA8h6GKcmTHPfovG1swA6U+hy+mYzXD3ck2yZeQ9DzT5XneUkNn/S+iv0Y7w1Z/8nb8rvW9LRsgOSKRaNTWug+sb/XfIKjKuCDBlxxJqzbV11b8Q5awV6mSDOxaBdlIXqfQAzxqcWwhZm2BDQkPYZ8uqviyMynh3XYTJMmsR2YGOADwGZ+0R5/Q+dOhEpBquIWSmotYQeY9pgfsHEXNC0WOyDKw==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=oqb9km6Xdj9sv4bC5TjdtD0HVPfNSBqbpBU7dlNqzBo=;
 b=hivDEw7qV5tbagUtYAwarlb1g4UWo1+MT+prPL3M+s6OC2W+iKm4kcq9LKylHJma2uRoQD2ANZpsZp32zml/UxAojWkIuTug+EM9WWiYA4g8LxcHoXJxsX23ARlQh3xrFN4WXKbnljncsgkACneCU0grBYEKyvuYf/zlSLKQkmo=
Authentication-Results: redhat.com; dkim=none (message not signed)
 header.d=none;redhat.com; dmarc=none action=none header.from=amd.com;
Received: from SN6PR12MB2767.namprd12.prod.outlook.com (2603:10b6:805:75::23)
 by SA0PR12MB4365.namprd12.prod.outlook.com (2603:10b6:806:96::22) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3632.17; Tue, 8 Dec
 2020 22:03:01 +0000
Received: from SN6PR12MB2767.namprd12.prod.outlook.com
 ([fe80::d8f2:fde4:5e1d:afec]) by SN6PR12MB2767.namprd12.prod.outlook.com
 ([fe80::d8f2:fde4:5e1d:afec%3]) with mapi id 15.20.3632.021; Tue, 8 Dec 2020
 22:03:01 +0000
From: Ashish Kalra <Ashish.Kalra@amd.com>
To: pbonzini@redhat.com
Cc: tglx@linutronix.de, mingo@redhat.com, hpa@zytor.com,
        rkrcmar@redhat.com, joro@8bytes.org, bp@suse.de,
        thomas.lendacky@amd.com, x86@kernel.org, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, srutherford@google.com,
        venu.busireddy@oracle.com, brijesh.singh@amd.com
Subject: [PATCH v9 00/18] Add AMD SEV guest live migration support
Date: Tue,  8 Dec 2020 22:02:51 +0000
Message-Id: <cover.1607460588.git.ashish.kalra@amd.com>
X-Mailer: git-send-email 2.17.1
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: SN6PR16CA0067.namprd16.prod.outlook.com
 (2603:10b6:805:ca::44) To SN6PR12MB2767.namprd12.prod.outlook.com
 (2603:10b6:805:75::23)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from ashkalra_ubuntu_server.amd.com (165.204.77.1) by
 SN6PR16CA0067.namprd16.prod.outlook.com (2603:10b6:805:ca::44) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3654.12 via Frontend
 Transport; Tue, 8 Dec 2020 22:03:01 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: aa2952ad-7ae3-47fa-14c0-08d89bc5080f
X-MS-TrafficTypeDiagnostic: SA0PR12MB4365:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SA0PR12MB436532B8B06B0C38E55B7D538ECD0@SA0PR12MB4365.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:229;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 t/nywQT84B0vCP+xZodJ1JHNwjcL1WWgDr9hnqiZjVOvyoE59WOdE7ZryzpUJhLoCgZ37kLaaPuSmcKJSpIKoEOE2fwaeqtzmj1elAOQATZ1YSjYX7DZJlYC4YwMiyRc4X3bGpyXr3+J+yEnkRhXL42WBXptSQkTHWZbMq3NRnaIh/8uymoH0qXXXF2ouvYsFHCklbQuoanX3+7PYb+I1tVWwuhu7l5qWfN/CIkjgrQybvF/UAtGK6k1HuYwCK6EFlRQ1vu920FXkLaWTSa0vd6bwhhdysrtb68VITF0WCWwNofDICOABtxw6/FxzMCUMwuzMYYF38cjdY0c5SV7dF3he3UC58xzyMzH05e44UjG8ZDetE7IWFkkx0A/nLFzFw97+ylsXSBRNm3zYh4jP7G+mwlxo9To6Bd/Mr1V20BB8Jd01ipLbEZ+bfwcrNSI8JFx1hrUk3uTz6J8YfYttQ==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN6PR12MB2767.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(376002)(346002)(366004)(136003)(7696005)(508600001)(6666004)(966005)(66476007)(66556008)(4326008)(66946007)(52116002)(5660300002)(186003)(2906002)(6916009)(34490700003)(86362001)(2616005)(16526019)(26005)(956004)(7416002)(8936002)(36756003)(6486002)(8676002)(83380400001);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: =?utf-8?q?1UXnNvz16eEJ4gAa7zeiQkfrji0don?=
	=?utf-8?q?3ghKXjwGz2/ghL/MfMS7xxC5Z3D0olCW53xc2zZVaTk7kHXOex4+aHTCus04Q/MTE?=
	=?utf-8?q?Ub2dsQRwNWfpuPQM3olSDhoH8VtliTUTQV5Grow7vFbeR0hAln++EsQ9TENpZjolb?=
	=?utf-8?q?jxX6etiq+Lom4ghdb7WYAB28WXxFOlx3YObTCtQGSq6JFZcv3RCNMnm7ZGOgxSIuA?=
	=?utf-8?q?nQIA3RrjiEqX9b3JCmH/OTz7pWbgS8Pg1mUsI+1WG0SeLVDSGpLuiMy5eniPdK8s1?=
	=?utf-8?q?mnk94USJoyvNlu0E2G+Xb/MZemeMDr9CZoDKKhqIkxwhWBqHipbkSzbx3nOuf9Bnu?=
	=?utf-8?q?NV6wi3NHktOhEF3Ggg7H8Xg7lYIKU4Nw/jBt1bqaMfbyXlhCY6WFtCr/AccN4FKPT?=
	=?utf-8?q?zKHnMI4mwWPrBDnWSbDS437b7JrhxX3T62ApPswWhtwdoXcACjo7yq8T+aoIgC6Yb?=
	=?utf-8?q?ljNCEuKbOBGqR5CxDTBfKJtBkm6KPnfmlmPMgD0NCeQqkAFlVLF5bI21rrF8JQfhi?=
	=?utf-8?q?lXkuGdzgDMd5zeGrDcB0OnMIJl5GYEljQQNjQfL5ufZNQQ5oUkXynKQOLI8LHdENk?=
	=?utf-8?q?ILeLipnCY9L1iQOmYt+vUU+HaOnwbxe8Q+rQVEXPFYku64Z8xdOSuuDFU3ubSDeel?=
	=?utf-8?q?+8WJ3MBb7QVCvqFYCAAQkSIaLN8nrxHRH3Mu0w59Rr58r81aE0K4MomD3Bw56I+FX?=
	=?utf-8?q?BrnKgih0Wa26xGdM/e7CFHOF5Qgo1OtlapvWkODNljA+hlaNonjh8RhPqQd8axZBK?=
	=?utf-8?q?GxXC26aZpvPSOirHMDaYC8PSj0k1h8eZQbsifdF04LUBOzKLJo+NKdx00wmYywqJi?=
	=?utf-8?q?Fs1R+Mnnj0Erw/hAt78Ji+tj5UH0RLPp1AL86vFKr7841cM9GB4pH0V2czb5npwB/?=
	=?utf-8?q?79+1RVHr9Qx+M4lZTrF7Br43zgTcduluNhveKIud/pgyiqGuiR8BKjBB9WtHTo0Fd?=
	=?utf-8?q?C1/zYZeyFo8lS90Tswu?=
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-AuthSource: SN6PR12MB2767.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 08 Dec 2020 22:03:01.7534
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 aa2952ad-7ae3-47fa-14c0-08d89bc5080f
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 jTe2UFDftKBVzL4LZD0S+G1PIKLA0egmcr9KCAgmF9w4U8dVx2ouvqlHEk6LLei2i5vl8Ge0QsSQNpwiisg7Ow==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SA0PR12MB4365
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Ashish Kalra <ashish.kalra@amd.com>

The series add support for AMD SEV guest live migration commands. To protect the
confidentiality of an SEV protected guest memory while in transit we need to
use the SEV commands defined in SEV API spec [1].

SEV guest VMs have the concept of private and shared memory. Private memory
is encrypted with the guest-specific key, while shared memory may be encrypted
with hypervisor key. The commands provided by the SEV FW are meant to be used
for the private memory only. The patch series introduces a new hypercall.
The guest OS can use this hypercall to notify the page encryption status.
If the page is encrypted with guest specific-key then we use SEV command during
the migration. If page is not encrypted then fallback to default.

The patch adds new ioctls KVM_{SET,GET}_PAGE_ENC_BITMAP. The ioctl can be used
by the qemu to get the page encrypted bitmap. Qemu can consult this bitmap
during the migration to know whether the page is encrypted.

This section descibes how the SEV live migration feature is negotiated
between the host and guest, the host indicates this feature support via 
KVM_FEATURE_CPUID. The guest firmware (OVMF) detects this feature and
sets a UEFI enviroment variable indicating OVMF support for live
migration, the guest kernel also detects the host support for this
feature via cpuid and in case of an EFI boot verifies if OVMF also
supports this feature by getting the UEFI enviroment variable and if it
set then enables live migration feature on host by writing to a custom
MSR, if not booted under EFI, then it simply enables the feature by
again writing to the custom MSR. The host returns error as part of
SET_PAGE_ENC_BITMAP ioctl if guest has not enabled live migration.

A branch containing these patches is available here:
https://github.com/AMDESE/linux/tree/sev-migration-v9

[1] https://developer.amd.com/wp-content/resources/55766.PDF

Changes since v8:
- Rebasing to kvm next branch.
- Fixed and added comments as per review feedback on v8 patches.
- Removed implicitly enabling live migration for incoming VMs in
  in KVM_SET_PAGE_ENC_BITMAP, it is now done via KVM_SET_MSR ioctl.
- Adds support for bypassing unencrypted guest memory regions for
  DBG_DECRYPT API calls, guest memory region encryption status in
  sev_dbg_decrypt() is referenced using the page encryption bitmap.

Changes since v7:
- Removed the hypervisor specific hypercall/paravirt callback for
  SEV live migration and moved back to calling kvm_sev_hypercall3 
  directly.
- Fix build errors as
  Reported-by: kbuild test robot <lkp@intel.com>, specifically fixed
  build error when CONFIG_HYPERVISOR_GUEST=y and
  CONFIG_AMD_MEM_ENCRYPT=n.
- Implicitly enabled live migration for incoming VM(s) to handle 
  A->B->C->... VM migrations.
- Fixed Documentation as per comments on v6 patches.
- Fixed error return path in sev_send_update_data() as per comments 
  on v6 patches. 

Changes since v6:
- Rebasing to mainline and refactoring to the new split SVM
  infrastructre.
- Move to static allocation of the unified Page Encryption bitmap
  instead of the dynamic resizing of the bitmap, the static allocation
  is done implicitly by extending kvm_arch_commit_memory_region() callack
  to add svm specific x86_ops which can read the userspace provided memory
  region/memslots and calculate the amount of guest RAM managed by the KVM
  and grow the bitmap.
- Fixed KVM_SET_PAGE_ENC_BITMAP ioctl to set the whole bitmap instead
  of simply clearing specific bits.
- Removed KVM_PAGE_ENC_BITMAP_RESET ioctl, which is now performed using
  KVM_SET_PAGE_ENC_BITMAP.
- Extended guest support for enabling Live Migration feature by adding a
  check for UEFI environment variable indicating OVMF support for Live
  Migration feature and additionally checking for KVM capability for the
  same feature. If not booted under EFI, then we simply check for KVM
  capability.
- Add hypervisor specific hypercall for SEV live migration by adding
  a new paravirt callback as part of x86_hyper_runtime.
  (x86 hypervisor specific runtime callbacks)
- Moving MSR handling for MSR_KVM_SEV_LIVE_MIG_EN into svm/sev code 
  and adding check for SEV live migration enabled by guest in the 
  KVM_GET_PAGE_ENC_BITMAP ioctl.
- Instead of the complete __bss_decrypted section, only specific variables
  such as hv_clock_boot and wall_clock are marked as decrypted in the
  page encryption bitmap

Changes since v5:
- Fix build errors as
  Reported-by: kbuild test robot <lkp@intel.com>

Changes since v4:
- Host support has been added to extend KVM capabilities/feature bits to 
  include a new KVM_FEATURE_SEV_LIVE_MIGRATION, which the guest can
  query for host-side support for SEV live migration and a new custom MSR
  MSR_KVM_SEV_LIVE_MIG_EN is added for guest to enable the SEV live
  migration feature.
- Ensure that _bss_decrypted section is marked as decrypted in the
  page encryption bitmap.
- Fixing KVM_GET_PAGE_ENC_BITMAP ioctl to return the correct bitmap
  as per the number of pages being requested by the user. Ensure that
  we only copy bmap->num_pages bytes in the userspace buffer, if
  bmap->num_pages is not byte aligned we read the trailing bits
  from the userspace and copy those bits as is. This fixes guest
  page(s) corruption issues observed after migration completion.
- Add kexec support for SEV Live Migration to reset the host's
  page encryption bitmap related to kernel specific page encryption
  status settings before we load a new kernel by kexec. We cannot
  reset the complete page encryption bitmap here as we need to
  retain the UEFI/OVMF firmware specific settings.

Changes since v3:
- Rebasing to mainline and testing.
- Adding a new KVM_PAGE_ENC_BITMAP_RESET ioctl, which resets the 
  page encryption bitmap on a guest reboot event.
- Adding a more reliable sanity check for GPA range being passed to
  the hypercall to ensure that guest MMIO ranges are also marked
  in the page encryption bitmap.

Changes since v2:
 - reset the page encryption bitmap on vcpu reboot

Changes since v1:
 - Add support to share the page encryption between the source and target
   machine.
 - Fix review feedbacks from Tom Lendacky.
 - Add check to limit the session blob length.
 - Update KVM_GET_PAGE_ENC_BITMAP icotl to use the base_gfn instead of
   the memory slot when querying the bitmap.

Ashish Kalra (7):
  KVM: SVM: Add support for static allocation of unified Page Encryption
    Bitmap.
  KVM: x86: Introduce new KVM_FEATURE_SEV_LIVE_MIGRATION feature &
    Custom MSR.
  EFI: Introduce the new AMD Memory Encryption GUID.
  KVM: x86: Add guest support for detecting and enabling SEV Live
    Migration feature.
  KVM: x86: Mark _bss_decrypted section variables as decrypted in page
    encryption bitmap.
  KVM: x86: Add kexec support for SEV Live Migration.
  KVM: SVM: Enable SEV live migration feature implicitly on Incoming
    VM(s).

Brijesh Singh (11):
  KVM: SVM: Add KVM_SEV SEND_START command
  KVM: SVM: Add KVM_SEND_UPDATE_DATA command
  KVM: SVM: Add KVM_SEV_SEND_FINISH command
  KVM: SVM: Add support for KVM_SEV_RECEIVE_START command
  KVM: SVM: Add KVM_SEV_RECEIVE_UPDATE_DATA command
  KVM: SVM: Add KVM_SEV_RECEIVE_FINISH command
  KVM: x86: Add AMD SEV specific Hypercall3
  KVM: X86: Introduce KVM_HC_PAGE_ENC_STATUS hypercall
  KVM: x86: Introduce KVM_GET_PAGE_ENC_BITMAP ioctl
  mm: x86: Invoke hypercall when page encryption status is changed
  KVM: x86: Introduce KVM_SET_PAGE_ENC_BITMAP ioctl

Ashish Kalra (7):
  KVM: SVM: Add support for static allocation of unified Page Encryption
    Bitmap.
  KVM: x86: Introduce new KVM_FEATURE_SEV_LIVE_MIGRATION feature &
    Custom MSR.
  EFI: Introduce the new AMD Memory Encryption GUID.
  KVM: x86: Add guest support for detecting and enabling SEV Live
    Migration feature.
  KVM: x86: Mark _bss_decrypted section variables as decrypted in page
    encryption bitmap.
  KVM: x86: Add kexec support for SEV Live Migration.
  KVM: SVM: Bypass DBG_DECRYPT API calls for unecrypted guest memory.

Brijesh Singh (11):
  KVM: SVM: Add KVM_SEV SEND_START command
  KVM: SVM: Add KVM_SEND_UPDATE_DATA command
  KVM: SVM: Add KVM_SEV_SEND_FINISH command
  KVM: SVM: Add support for KVM_SEV_RECEIVE_START command
  KVM: SVM: Add KVM_SEV_RECEIVE_UPDATE_DATA command
  KVM: SVM: Add KVM_SEV_RECEIVE_FINISH command
  KVM: x86: Add AMD SEV specific Hypercall3
  KVM: X86: Introduce KVM_HC_PAGE_ENC_STATUS hypercall
  KVM: x86: Introduce KVM_GET_PAGE_ENC_BITMAP ioctl
  mm: x86: Invoke hypercall when page encryption status is changed
  KVM: x86: Introduce KVM_SET_PAGE_ENC_BITMAP ioctl

 .../virt/kvm/amd-memory-encryption.rst        | 120 +++
 Documentation/virt/kvm/api.rst                |  71 ++
 Documentation/virt/kvm/cpuid.rst              |   5 +
 Documentation/virt/kvm/hypercalls.rst         |  15 +
 Documentation/virt/kvm/msr.rst                |  16 +
 arch/x86/include/asm/kvm_host.h               |   7 +
 arch/x86/include/asm/kvm_para.h               |  12 +
 arch/x86/include/asm/mem_encrypt.h            |  11 +
 arch/x86/include/asm/paravirt.h               |  10 +
 arch/x86/include/asm/paravirt_types.h         |   2 +
 arch/x86/include/uapi/asm/kvm_para.h          |   5 +
 arch/x86/kernel/kvm.c                         |  90 ++
 arch/x86/kernel/kvmclock.c                    |  12 +
 arch/x86/kernel/paravirt.c                    |   1 +
 arch/x86/kvm/svm/sev.c                        | 790 ++++++++++++++++++
 arch/x86/kvm/svm/svm.c                        |  21 +
 arch/x86/kvm/svm/svm.h                        |   9 +
 arch/x86/kvm/vmx/vmx.c                        |   1 +
 arch/x86/kvm/x86.c                            |  35 +
 arch/x86/mm/mem_encrypt.c                     |  68 +-
 arch/x86/mm/pat/set_memory.c                  |   7 +
 include/linux/efi.h                           |   1 +
 include/linux/psp-sev.h                       |   8 +-
 include/uapi/linux/kvm.h                      |  52 ++
 include/uapi/linux/kvm_para.h                 |   1 +
 25 files changed, 1365 insertions(+), 5 deletions(-)
```
