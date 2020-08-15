#### [kvm-unit-tests] pmu: make llc misses test to pass on more cpu types
##### From: Like Xu <like.xu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Like Xu <like.xu@linux.intel.com>
X-Patchwork-Id: 11713861
Return-Path: <SRS0=allB=BY=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BCC64722
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 14 Aug 2020 08:50:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A410020771
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 14 Aug 2020 08:50:45 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727011AbgHNIuo (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 14 Aug 2020 04:50:44 -0400
Received: from mga02.intel.com ([134.134.136.20]:32760 "EHLO mga02.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726641AbgHNIum (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 14 Aug 2020 04:50:42 -0400
IronPort-SDR: 
 ZrmwDM0x1YUoyA+oS8g3O98vmf61/4WbDf4LAmISkIambYIycgHYFWydAH8RdB1wD5SLjCk+VB
 J2jnqB0+nNmA==
X-IronPort-AV: E=McAfee;i="6000,8403,9712"; a="142219152"
X-IronPort-AV: E=Sophos;i="5.76,311,1592895600";
   d="scan'208";a="142219152"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga007.fm.intel.com ([10.253.24.52])
  by orsmga101.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 14 Aug 2020 01:50:41 -0700
IronPort-SDR: 
 QHqsEadkij4rUx+vVLKSKNbuW+hYqcDrheml63a9BCMd2RBbmBzM2yS26FtgkaDLsE8U7CszFe
 TxPJc6ijUbwg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.76,311,1592895600";
   d="scan'208";a="277073969"
Received: from sqa-gate.sh.intel.com (HELO clx-ap-likexu.tsp.org)
 ([10.239.48.212])
  by fmsmga007.fm.intel.com with ESMTP; 14 Aug 2020 01:50:40 -0700
From: Like Xu <like.xu@linux.intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org
Subject: [kvm-unit-tests] pmu: make llc misses test to pass on more cpu types
Date: Fri, 14 Aug 2020 16:48:10 +0800
Message-Id: <20200814084810.20960-1-like.xu@linux.intel.com>
X-Mailer: git-send-email 2.21.3
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Expand boundary of llc misses test since it was observed that
on some Atom Tremont cpus results do not fit.

1 >= 1002014 <= 1000000
FAIL: llc misses-0
1 >= 1002014 <= 1000000
FAIL: llc misses-1
1 >= 1002003 <= 1000000
FAIL: llc misses-2
1 >= 1002014 <= 1000000
FAIL: llc misses-3

Signed-off-by: Like Xu <like.xu@linux.intel.com>
---
 x86/pmu.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [kvm-unit-tests RFC v1 1/5] lib/vmalloc: vmalloc support for handling allocation metadata
##### From: Claudio Imbrenda <imbrenda@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Claudio Imbrenda <imbrenda@linux.ibm.com>
X-Patchwork-Id: 11714687
Return-Path: <SRS0=allB=BY=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C4FDC13A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 14 Aug 2020 15:10:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A6DDF20855
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 14 Aug 2020 15:10:27 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="J+NK9mw6"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728510AbgHNPK1 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 14 Aug 2020 11:10:27 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:5576 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727900AbgHNPKU (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 14 Aug 2020 11:10:20 -0400
Received: from pps.filterd (m0098409.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 07EF3nnk001439
        for <kvm@vger.kernel.org>; Fri, 14 Aug 2020 11:10:19 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=42z7/syVnL4rJ1PUj2m77ri03EIabqjzkgk4Sj1XGQI=;
 b=J+NK9mw6zkUuM8WPX6E++oSD1rkjKFxjoOoBY/mw4T/A5q5p/i5HMuguXOomoqP57A00
 VBpx4LnBDoFRGOG2O5Hf15R7frjLeTEHgn+ZVl/cD8xAyvMcrhjqzQD5uKiHwp/FWd3k
 xqJqAhO0vojUBX3k4D6VSYLsqlJozq6ouc6ZjC4GV1cX97Y3Wn2EIgVKHEjqYR9wtD0a
 Pblr3fraDmx+y5FgcgadeGK6iTu4gF0Caj34Y9cH5/KWxgu0jNKjlfiF7dd+p5INhOfQ
 I4cTQ5SHd2pz232b33lv85RvBmR7dqBNi2DrbnML5+oTNNPdjQ3FeVhH78j5tTKHcRL0 Kg==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 32w5mxgs5c-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT)
        for <kvm@vger.kernel.org>; Fri, 14 Aug 2020 11:10:19 -0400
Received: from m0098409.ppops.net (m0098409.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 07EF47pK002805
        for <kvm@vger.kernel.org>; Fri, 14 Aug 2020 11:10:19 -0400
Received: from ppma06fra.de.ibm.com (48.49.7a9f.ip4.static.sl-reverse.com
 [159.122.73.72])
        by mx0a-001b2d01.pphosted.com with ESMTP id 32w5mxgs3k-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 14 Aug 2020 11:10:19 -0400
Received: from pps.filterd (ppma06fra.de.ibm.com [127.0.0.1])
        by ppma06fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 07EF87oV006172;
        Fri, 14 Aug 2020 15:10:17 GMT
Received: from b06cxnps4075.portsmouth.uk.ibm.com
 (d06relay12.portsmouth.uk.ibm.com [9.149.109.197])
        by ppma06fra.de.ibm.com with ESMTP id 32skah45e6-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 14 Aug 2020 15:10:16 +0000
Received: from d06av23.portsmouth.uk.ibm.com (d06av23.portsmouth.uk.ibm.com
 [9.149.105.59])
        by b06cxnps4075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 07EFABe517826184
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 14 Aug 2020 15:10:11 GMT
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id EE51CA4040;
        Fri, 14 Aug 2020 15:10:10 +0000 (GMT)
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 861EAA404D;
        Fri, 14 Aug 2020 15:10:10 +0000 (GMT)
Received: from ibm-vm.ibmuc.com (unknown [9.145.4.223])
        by d06av23.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Fri, 14 Aug 2020 15:10:10 +0000 (GMT)
From: Claudio Imbrenda <imbrenda@linux.ibm.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com
Cc: frankja@linux.ibm.com, david@redhat.com, thuth@redhat.com,
        cohuck@redhat.com, lvivier@redhat.com
Subject: [kvm-unit-tests RFC v1 1/5] lib/vmalloc: vmalloc support for handling
 allocation metadata
Date: Fri, 14 Aug 2020 17:10:05 +0200
Message-Id: <20200814151009.55845-2-imbrenda@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20200814151009.55845-1-imbrenda@linux.ibm.com>
References: <20200814151009.55845-1-imbrenda@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-08-14_09:2020-08-14,2020-08-14 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 bulkscore=0 adultscore=0
 suspectscore=2 clxscore=1015 impostorscore=0 spamscore=0
 priorityscore=1501 mlxlogscore=999 mlxscore=0 lowpriorityscore=0
 phishscore=0 malwarescore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-2006250000 definitions=main-2008140114
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Signed-off-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
---
 lib/vmalloc.c | 105 +++++++++++++++++++++++++++++++++++++++++++++-----
 1 file changed, 95 insertions(+), 10 deletions(-)

```
#### [PATCH] selftests: kvm: Fix an unexpected failure with newer gcc compiler
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Weijiang <weijiang.yang@intel.com>
X-Patchwork-Id: 11714539
Return-Path: <SRS0=allB=BY=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6802414F6
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 14 Aug 2020 13:13:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5681522B47
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 14 Aug 2020 13:13:39 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726320AbgHNNNi (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 14 Aug 2020 09:13:38 -0400
Received: from mga12.intel.com ([192.55.52.136]:47285 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726139AbgHNNNi (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 14 Aug 2020 09:13:38 -0400
IronPort-SDR: 
 lnzseHRKWTM+w2UH8NF6bi+Be3ArVbtESSLIJL98NLKNCTvLqs1Au+ZgxfslYVw8LMNv9sutWc
 SDVAvfbqKyjQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9712"; a="133923589"
X-IronPort-AV: E=Sophos;i="5.76,312,1592895600";
   d="scan'208";a="133923589"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga003.jf.intel.com ([10.7.209.27])
  by fmsmga106.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 14 Aug 2020 06:13:37 -0700
IronPort-SDR: 
 xWjFTk7XDLma05PewkOHSyABfGlM7R2wqd/t1qTTmrVMsNoFCHzqoX73HW44s4NYxvpul2Bxf1
 D3ZT/ZXgpDYg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.76,312,1592895600";
   d="scan'208";a="291729778"
Received: from local-michael-cet-test.sh.intel.com ([10.239.159.128])
  by orsmga003.jf.intel.com with ESMTP; 14 Aug 2020 06:13:35 -0700
From: Yang Weijiang <weijiang.yang@intel.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com, shuah@kernel.org,
        peterx@redhat.com, linux-kselftest@vger.kernel.org
Cc: Yang Weijiang <weijiang.yang@intel.com>
Subject: [PATCH] selftests: kvm: Fix an unexpected failure with newer gcc
 compiler
Date: Fri, 14 Aug 2020 21:21:05 +0800
Message-Id: <20200814132105.5122-1-weijiang.yang@intel.com>
X-Mailer: git-send-email 2.17.2
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If debug_regs.c is built with newer gcc, e.g., 8.3.1 on my side, then the generated
binary looks like over-optimized by gcc:

asm volatile("ss_start: "
             "xor %%rax,%%rax\n\t"
             "cpuid\n\t"
             "movl $0x1a0,%%ecx\n\t"
             "rdmsr\n\t"
             : : : "rax", "ecx");

is translated to :

  000000000040194e <ss_start>:
  40194e:       31 c0                   xor    %eax,%eax     <----- rax->eax?
  401950:       0f a2                   cpuid
  401952:       b9 a0 01 00 00          mov    $0x1a0,%ecx
  401957:       0f 32                   rdmsr

As you can see rax is replaced with eax in taret binary code.
But if I replace %%rax with %%r8 or any GPR from r8~15, then I get below
expected binary:

0000000000401950 <ss_start>:
  401950:       45 31 ff                xor    %r15d,%r15d
  401953:       0f a2                   cpuid
  401955:       b9 a0 01 00 00          mov    $0x1a0,%ecx
  40195a:       0f 32                   rdmsr

The difference is the length of xor instruction(2 Byte vs 3 Byte),
so this makes below hard-coded instruction length cannot pass runtime check:

        /* Instruction lengths starting at ss_start */
        int ss_size[4] = {
                3,              /* xor */   <-------- 2 or 3?
                2,              /* cpuid */
                5,              /* mov */
                2,              /* rdmsr */
        };
Note:
Use 8.2.1 or older gcc, it generates expected 3 bytes xor target code.

I use the default Makefile to build the binaries, and I cannot figure out why this
happens, so it comes this patch, maybe you have better solution to resolve the
issue. If you know how things work in this way, please let me know, thanks!

Below is the capture from my environments:
========================================================================
gcc (GCC) 8.3.1 20190223 (Red Hat 8.3.1-2)
Copyright (C) 2018 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

0000000000401950 <ss_start>:
  401950:       45 31 ff                xor    %r15d,%r15d
  401953:       0f a2                   cpuid
  401955:       b9 a0 01 00 00          mov    $0x1a0,%ecx
  40195a:       0f 32                   rdmsr

  000000000040194f <ss_start>:
  40194f:       31 db                   xor    %ebx,%ebx
  401951:       0f a2                   cpuid
  401953:       b9 a0 01 00 00          mov    $0x1a0,%ecx
  401958:       0f 32                   rdmsr

  000000000040194e <ss_start>:
  40194e:       31 c0                   xor    %eax,%eax
  401950:       0f a2                   cpuid
  401952:       b9 a0 01 00 00          mov    $0x1a0,%ecx
  401957:       0f 32                   rdmsr

==========================================================================

gcc (GCC) 8.2.1 20180905 (Red Hat 8.2.1-3)
Copyright (C) 2018 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

0000000000401750 <ss_start>:
  401750:       48 31 c0                xor    %rax,%rax
  401753:       0f a2                   cpuid
  401755:       b9 a0 01 00 00          mov    $0x1a0,%ecx
  40175a:       0f 32                   rdmsr

Signed-off-by: Yang Weijiang <weijiang.yang@intel.com>
---
 tools/testing/selftests/kvm/x86_64/debug_regs.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH V2] vfio dma_map/unmap: optimized for hugetlbfs pages
##### From: Ming Mao <maoming.maoming@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ming Mao <maoming.maoming@huawei.com>
X-Patchwork-Id: 11713311
Return-Path: <SRS0=allB=BY=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9AAB8109B
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 14 Aug 2020 02:38:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7750420838
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 14 Aug 2020 02:38:00 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726596AbgHNCh5 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 13 Aug 2020 22:37:57 -0400
Received: from szxga06-in.huawei.com ([45.249.212.32]:48414 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726564AbgHNCh4 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 13 Aug 2020 22:37:56 -0400
Received: from DGGEMS409-HUB.china.huawei.com (unknown [172.30.72.60])
        by Forcepoint Email with ESMTP id 57CBFB3BDEE95E867C78;
        Fri, 14 Aug 2020 10:37:50 +0800 (CST)
Received: from localhost (10.174.151.124) by DGGEMS409-HUB.china.huawei.com
 (10.3.19.209) with Microsoft SMTP Server id 14.3.487.0; Fri, 14 Aug 2020
 10:37:44 +0800
From: Ming Mao <maoming.maoming@huawei.com>
To: <linux-kernel@vger.kernel.org>, <kvm@vger.kernel.org>,
        <alex.williamson@redhat.com>
CC: <cohuck@redhat.com>, <jianjay.zhou@huawei.com>,
        <weidong.huang@huawei.com>, <peterx@redhat.com>,
        <aarcange@redhat.com>, "Ming Mao" <maoming.maoming@huawei.com>
Subject: [PATCH V2] vfio dma_map/unmap: optimized for hugetlbfs pages
Date: Fri, 14 Aug 2020 10:37:29 +0800
Message-ID: <20200814023729.2270-1-maoming.maoming@huawei.com>
X-Mailer: git-send-email 2.26.2.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.151.124]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In the original process of pinning/unpinning pages for VFIO-devices,
to make sure the pages are contiguous, we have to check them one by one.
As a result, dma_map/unmap could spend a long time.
Using the hugetlb pages, we can avoid this problem.
All pages in hugetlb pages are contiguous.And the hugetlb
page should not be split.So we can delete the for loops and use
some operations(such as atomic_add,page_ref_add) instead.

Signed-off-by: Ming Mao <maoming.maoming@huawei.com>
---
 drivers/vfio/vfio_iommu_type1.c | 233 +++++++++++++++++++++++++++++++-
 1 file changed, 230 insertions(+), 3 deletions(-)

```
