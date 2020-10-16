#### [PATCH v2 1/2] s390/kvm: fix diag318 reset
##### From: Collin Walling <walling@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Collin Walling <walling@linux.ibm.com>
X-Patchwork-Id: 11840129
Return-Path: <SRS0=SCDt=DW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CD6E61580
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 15 Oct 2020 19:59:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 89986206DD
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 15 Oct 2020 19:59:32 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="VNeybYh2"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2392047AbgJOT7b (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 15 Oct 2020 15:59:31 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:37250 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S2392041AbgJOT7a (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 15 Oct 2020 15:59:30 -0400
Received: from pps.filterd (m0098399.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 09FJWK4r052334
        for <kvm@vger.kernel.org>; Thu, 15 Oct 2020 15:59:30 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=kkZA4dQ2SEiNmikp1aBvQd4Bikkx2QW8nE+Gl0l+ZLA=;
 b=VNeybYh2VV7P/I5mi25AynS2Wel0Z3Xopo7ltO39sVtKq0rGthWsRe8iDbndTQSHjhfm
 sav36f+ACOdwKZtByTcfpWKtOextTkme731E3TV+HFwXPsAZtKrLRh7iec+GNcBiQVu1
 010eC6SqEdnESxasA4d0EXoaRF874wd0mr7hwRB7VU3dayrb5PvDmC9oNCXda3wOglVL
 vUEyAzrb44f4eizBY5KBxmvC4XNMOh/8Z6DIXwV9aCCsa4yBOFpE91+d3V4n1W3SWo+6
 GAh4zxmAx5j2ZDbN5TFi+UCNkzwJfIgN5vgfhpRR+DhUkBV+AYpt0S10qOZfNSZ+d1Va UA==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 346uj1tse5-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT)
        for <kvm@vger.kernel.org>; Thu, 15 Oct 2020 15:59:29 -0400
Received: from m0098399.ppops.net (m0098399.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 09FJXqRj059888
        for <kvm@vger.kernel.org>; Thu, 15 Oct 2020 15:59:29 -0400
Received: from ppma02dal.us.ibm.com (a.bd.3ea9.ip4.static.sl-reverse.com
 [169.62.189.10])
        by mx0a-001b2d01.pphosted.com with ESMTP id 346uj1tsdx-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 15 Oct 2020 15:59:29 -0400
Received: from pps.filterd (ppma02dal.us.ibm.com [127.0.0.1])
        by ppma02dal.us.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 09FJvuFQ028663;
        Thu, 15 Oct 2020 19:59:28 GMT
Received: from b03cxnp08026.gho.boulder.ibm.com
 (b03cxnp08026.gho.boulder.ibm.com [9.17.130.18])
        by ppma02dal.us.ibm.com with ESMTP id 3434ka7ehm-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 15 Oct 2020 19:59:28 +0000
Received: from b03ledav004.gho.boulder.ibm.com
 (b03ledav004.gho.boulder.ibm.com [9.17.130.235])
        by b03cxnp08026.gho.boulder.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 09FJxK3E42861036
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 15 Oct 2020 19:59:20 GMT
Received: from b03ledav004.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 88DC978060;
        Thu, 15 Oct 2020 19:59:27 +0000 (GMT)
Received: from b03ledav004.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id CFB9E7805E;
        Thu, 15 Oct 2020 19:59:26 +0000 (GMT)
Received: from localhost.localdomain.com (unknown [9.85.130.217])
        by b03ledav004.gho.boulder.ibm.com (Postfix) with ESMTP;
        Thu, 15 Oct 2020 19:59:26 +0000 (GMT)
From: Collin Walling <walling@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: frankja@linux.ibm.com, david@redhat.com, thuth@redhat.com,
        cohuck@redhat.com
Subject: [PATCH v2 1/2] s390/kvm: fix diag318 reset
Date: Thu, 15 Oct 2020 15:59:12 -0400
Message-Id: <20201015195913.101065-2-walling@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20201015195913.101065-1-walling@linux.ibm.com>
References: <20201015195913.101065-1-walling@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-10-15_15:2020-10-14,2020-10-15 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 lowpriorityscore=0
 bulkscore=0 phishscore=0 clxscore=1015 mlxlogscore=999 suspectscore=13
 adultscore=0 impostorscore=0 spamscore=0 mlxscore=0 priorityscore=1501
 malwarescore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2010150126
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The DIAGNOSE 0x0318 instruction must be reset on a normal and clear
reset. However, this was missed for the clear reset case.

Let's fix this by resetting the information during a normal reset. 
Since clear reset is a superset of normal reset, the info will
still reset on a clear reset.

Signed-off-by: Collin Walling <walling@linux.ibm.com>
---
 arch/s390/kvm/kvm-s390.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v2 kvm-unit-tests] runtime.bash: skip test when checked file doesn't exist
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11838789
Return-Path: <SRS0=SCDt=DW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7125C14B3
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 15 Oct 2020 08:38:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 48FC02225F
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 15 Oct 2020 08:38:17 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="ZfmC8ovo"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2387514AbgJOIiQ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 15 Oct 2020 04:38:16 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:40747 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1729723AbgJOIiP (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 15 Oct 2020 04:38:15 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1602751094;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=6jK4Ei2H315PjcLRzKj4JaFTscxNE7NtNEtqf0KEIlI=;
        b=ZfmC8ovoxEbxquSK2CqF0s+xhiaeoKO0KatslQ+uA4o6cXxT2rNvROyMQgxsHb1bYNXwlZ
        uTeuNgccgDjteM529AEdLj3CIJofcCyn5wJrVvz4xiIns1VgR1UsDcn2ghWl5Mq3ioGVKj
        /lbfT30jTrQcYLFR6PRpVdCwQ2scHJA=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-223-qUiGZwBFMqSPwE5eBB0Jvg-1; Thu, 15 Oct 2020 04:38:13 -0400
X-MC-Unique: qUiGZwBFMqSPwE5eBB0Jvg-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 008E864082
        for <kvm@vger.kernel.org>; Thu, 15 Oct 2020 08:38:12 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.194.105])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 7B3255D9CD;
        Thu, 15 Oct 2020 08:38:10 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Thomas Huth <thuth@redhat.com>, Andrew Jones <drjones@redhat.com>
Subject: [PATCH v2 kvm-unit-tests] runtime.bash: skip test when checked file
 doesn't exist
Date: Thu, 15 Oct 2020 10:38:08 +0200
Message-Id: <20201015083808.2488268-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Currently, we have the following check condition in x86/unittests.cfg:

check = /sys/module/kvm_intel/parameters/allow_smaller_maxphyaddr=Y

the check, however, passes successfully on AMD because the checked file
is just missing. This doesn't sound right, reverse the check: fail
if the content of the file doesn't match the expectation or if the
file is not there.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Reviewed-by: Andrew Jones <drjones@redhat.com>
---
Changes since v1:
- tabs -> spaces [Thomas]
---
 scripts/runtime.bash | 5 ++++-
 1 file changed, 4 insertions(+), 1 deletion(-)

```
#### [PATCH] vfio/fsl-mc: Fix the dead code in vfio_fsl_mc_set_irq_trigger
##### From: Diana Craciun <diana.craciun@oss.nxp.com>

```c
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Static analysis discovered that some code in vfio_fsl_mc_set_irq_trigger
is dead code. Fixed the code by changing the conditions order.

Fixes: cc0ee20bd969 ("vfio/fsl-mc: trigger an interrupt via eventfd")
Reported-by: Colin Ian King <colin.king@canonical.com>
Signed-off-by: Diana Craciun <diana.craciun@oss.nxp.com>
---
 drivers/vfio/fsl-mc/vfio_fsl_mc_intr.c | 6 +++---
 1 file changed, 3 insertions(+), 3 deletions(-)

```
#### [PATCH] vfio/fsl-mc: fix the return of the uninitialized variable ret
##### From: Colin King <colin.king@canonical.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Colin King <colin.king@canonical.com>
X-Patchwork-Id: 11839143
Return-Path: <SRS0=SCDt=DW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9406D14B3
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 15 Oct 2020 12:22:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7C9CF22249
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 15 Oct 2020 12:22:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727873AbgJOMWb (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 15 Oct 2020 08:22:31 -0400
Received: from youngberry.canonical.com ([91.189.89.112]:35173 "EHLO
        youngberry.canonical.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727278AbgJOMWb (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 15 Oct 2020 08:22:31 -0400
Received: from 1.general.cking.uk.vpn ([10.172.193.212] helo=localhost)
        by youngberry.canonical.com with esmtpsa
 (TLS1.2:ECDHE_RSA_AES_128_GCM_SHA256:128)
        (Exim 4.86_2)
        (envelope-from <colin.king@canonical.com>)
        id 1kT2H4-0006lp-Q3; Thu, 15 Oct 2020 12:22:26 +0000
From: Colin King <colin.king@canonical.com>
To: Diana Craciun <diana.craciun@oss.nxp.com>,
        Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Eric Auger <eric.auger@redhat.com>, kvm@vger.kernel.org
Cc: kernel-janitors@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH] vfio/fsl-mc: fix the return of the uninitialized variable ret
Date: Thu, 15 Oct 2020 13:22:26 +0100
Message-Id: <20201015122226.485911-1-colin.king@canonical.com>
X-Mailer: git-send-email 2.27.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Colin Ian King <colin.king@canonical.com>

Currently the success path in function vfio_fsl_mc_reflck_attach is
returning an uninitialized value in variable ret. Fix this by setting
this to zero to indicate success.

Addresses-Coverity: ("Uninitialized scalar variable")
Fixes: f2ba7e8c947b ("vfio/fsl-mc: Added lock support in preparation for interrupt handling")
Signed-off-by: Colin Ian King <colin.king@canonical.com>
---
 drivers/vfio/fsl-mc/vfio_fsl_mc.c | 1 +
 1 file changed, 1 insertion(+)

```
