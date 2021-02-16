#### [PATCH v3 1/1] s390:kvm: diag9c forwarding
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 12088827
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id AEEE3C433E9
	for <kvm@archiver.kernel.org>; Mon, 15 Feb 2021 16:14:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 74A2564DF0
	for <kvm@archiver.kernel.org>; Mon, 15 Feb 2021 16:14:53 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232305AbhBOQOS (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 15 Feb 2021 11:14:18 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:20106 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S232089AbhBOQHm (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 15 Feb 2021 11:07:42 -0500
Received: from pps.filterd (m0098419.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 11FG0vQH115031;
        Mon, 15 Feb 2021 11:06:58 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references; s=pp1;
 bh=bNbbYdqX2UM/ffxVnvLCVYYfZKicGYi1Id5TkMWq7B4=;
 b=J8YQ/TPuPP7/vdHzX4Q6amXP5A2Dza+o75IUJSuvWAG3Lov1+i0vpkfUFQvzIhx0LTiN
 DUiVX0gBiI3IFdPSB0NnKOj/WcNMfVpssAIObksAsK7dR41vHDMAXP67eBAAiTXvt6rF
 OVWypuQZs3L+V3F4x9YYwRus3w39rKsOtvUxW/gkpTA0jTFYRE/zbY6sOBKeZZarG2IR
 5gon9VkpVQguB4UmalggYecyULq5oH7Wcosr3FPpEsDrEwGGDtTwRJINVjcROqX+k3xE
 0F7d8v1aDQg/oSphdR9LueICOY3ox59JsiXct+KrnF9AjsWBbHnL60aUKw+jVx9qXn5g Mg==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 36quumrs27-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 15 Feb 2021 11:06:57 -0500
Received: from m0098419.ppops.net (m0098419.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 11FG114n115137;
        Mon, 15 Feb 2021 11:06:57 -0500
Received: from ppma06fra.de.ibm.com (48.49.7a9f.ip4.static.sl-reverse.com
 [159.122.73.72])
        by mx0b-001b2d01.pphosted.com with ESMTP id 36quumrs17-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 15 Feb 2021 11:06:57 -0500
Received: from pps.filterd (ppma06fra.de.ibm.com [127.0.0.1])
        by ppma06fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 11FFsheD021670;
        Mon, 15 Feb 2021 16:06:55 GMT
Received: from b06cxnps4074.portsmouth.uk.ibm.com
 (d06relay11.portsmouth.uk.ibm.com [9.149.109.196])
        by ppma06fra.de.ibm.com with ESMTP id 36p61h921u-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 15 Feb 2021 16:06:55 +0000
Received: from d06av24.portsmouth.uk.ibm.com (mk.ibm.com [9.149.105.60])
        by b06cxnps4074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 11FG6qXs37290342
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 15 Feb 2021 16:06:52 GMT
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id C815B4203F;
        Mon, 15 Feb 2021 16:06:52 +0000 (GMT)
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 633E542041;
        Mon, 15 Feb 2021 16:06:52 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.73.68])
        by d06av24.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Mon, 15 Feb 2021 16:06:52 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, borntraeger@de.ibm.com,
        frankja@linux.ibm.com, cohuck@redhat.com, david@redhat.com,
        thuth@redhat.com, pmorel@linux.ibm.com
Subject: [PATCH v3 1/1] s390:kvm: diag9c forwarding
Date: Mon, 15 Feb 2021 17:06:50 +0100
Message-Id: <1613405210-16532-2-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1613405210-16532-1-git-send-email-pmorel@linux.ibm.com>
References: <1613405210-16532-1-git-send-email-pmorel@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.761
 definitions=2021-02-15_11:2021-02-12,2021-02-15 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 lowpriorityscore=0
 impostorscore=0 adultscore=0 spamscore=0 mlxscore=0 suspectscore=0
 mlxlogscore=999 malwarescore=0 priorityscore=1501 bulkscore=0
 clxscore=1015 phishscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2102150124
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When we receive intercept a DIAG_9C from the guest we verify
that the target real CPU associated with the virtual CPU
designated by the guest is running and if not we forward the
DIAG_9C to the target real CPU.

To avoid a diag9c storm we allow a maximal rate of diag9c forwarding.

The rate is calculated as a count per second defined as a
new parameter of the s390 kvm module: diag9c_forwarding_hz .

The default value is to not forward diag9c.

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
---
 Documentation/virt/kvm/s390-diag.rst | 33 ++++++++++++++++++++++++++++
 arch/s390/include/asm/kvm_host.h     |  1 +
 arch/s390/include/asm/smp.h          |  1 +
 arch/s390/kernel/smp.c               |  1 +
 arch/s390/kvm/diag.c                 | 31 +++++++++++++++++++++++---
 arch/s390/kvm/kvm-s390.c             |  6 +++++
 arch/s390/kvm/kvm-s390.h             |  8 +++++++
 7 files changed, 78 insertions(+), 3 deletions(-)

```
#### [PATCH] selftests: kvm: avoid uninitialized variable warning
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 12089003
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 827DAC433E0
	for <kvm@archiver.kernel.org>; Mon, 15 Feb 2021 16:45:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3BC6B64E32
	for <kvm@archiver.kernel.org>; Mon, 15 Feb 2021 16:45:16 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231393AbhBOQo4 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 15 Feb 2021 11:44:56 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:22024 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S229931AbhBOQnx (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 15 Feb 2021 11:43:53 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1613407336;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=p9NpBjihp4L1LCfyFyPncXipOV2lf7taXzySW8ZeP4U=;
        b=b6rd4F7qD4q5d5wmrZX/HZCjOb4mB19KIQwpUMhwYAJV/JpkNOQGi6gm65PxEha7ftyhoz
        Ww2vBBhSQDcGPNaaN/RVs6uVYFw3lV+dHsopG1cH5yZ/nvrUosCNixGpkruO1vi7KerooM
        ShYC0Hu4tx9vee+9GqUKLc065fzwjCM=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-62-YPZQay9xMYq7SdXdom77kQ-1; Mon, 15 Feb 2021 11:42:14 -0500
X-MC-Unique: YPZQay9xMYq7SdXdom77kQ-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 5368585EE62;
        Mon, 15 Feb 2021 16:42:13 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id EEF0110016F6;
        Mon, 15 Feb 2021 16:42:12 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [PATCH] selftests: kvm: avoid uninitialized variable warning
Date: Mon, 15 Feb 2021 11:42:12 -0500
Message-Id: <20210215164212.1126177-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The variable in practice will never be uninitialized, because the
loop will always go through at least one iteration.

In case it would not, make vcpu_get_cpuid report an assertion
failure.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 tools/testing/selftests/kvm/lib/x86_64/processor.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
