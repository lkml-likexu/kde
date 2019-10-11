#### [PATCH v2 1/2] KVM: s390: count invalid yields
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11183095
Return-Path: <SRS0=OAn+=YD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 22FC51668
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Oct 2019 11:05:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 0DE8B20B7C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Oct 2019 11:05:27 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727815AbfJJLF0 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 10 Oct 2019 07:05:26 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:58444 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726298AbfJJLF0 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 10 Oct 2019 07:05:26 -0400
Received: from pps.filterd (m0098399.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 x9AACcme044849
        for <kvm@vger.kernel.org>; Thu, 10 Oct 2019 07:05:24 -0400
Received: from e06smtp04.uk.ibm.com (e06smtp04.uk.ibm.com [195.75.94.100])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2vj2pmsk0e-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Thu, 10 Oct 2019 07:05:24 -0400
Received: from localhost
        by e06smtp04.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <borntraeger@de.ibm.com>;
        Thu, 10 Oct 2019 12:05:22 +0100
Received: from b06cxnps3075.portsmouth.uk.ibm.com (9.149.109.195)
        by e06smtp04.uk.ibm.com (192.168.101.134) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Thu, 10 Oct 2019 12:05:20 +0100
Received: from d06av26.portsmouth.uk.ibm.com (d06av26.portsmouth.uk.ibm.com
 [9.149.105.62])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id x9AB5JoA43188284
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 10 Oct 2019 11:05:19 GMT
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 32597AE056;
        Thu, 10 Oct 2019 11:05:19 +0000 (GMT)
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 1E2C0AE04D;
        Thu, 10 Oct 2019 11:05:19 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av26.portsmouth.uk.ibm.com (Postfix) with ESMTPS;
        Thu, 10 Oct 2019 11:05:19 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 25651)
        id C6CEEE0248; Thu, 10 Oct 2019 13:05:18 +0200 (CEST)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: Janosch Frank <frankja@linux.vnet.ibm.com>
Cc: KVM <kvm@vger.kernel.org>, Cornelia Huck <cohuck@redhat.com>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        David Hildenbrand <david@redhat.com>,
        linux-s390 <linux-s390@vger.kernel.org>,
        Thomas Huth <thuth@redhat.com>
Subject: [PATCH v2 1/2] KVM: s390: count invalid yields
Date: Thu, 10 Oct 2019 13:05:17 +0200
X-Mailer: git-send-email 2.21.0
In-Reply-To: <20191010110518.129256-1-borntraeger@de.ibm.com>
References: <20191010110518.129256-1-borntraeger@de.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 19101011-0016-0000-0000-000002B6D483
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19101011-0017-0000-0000-00003317E06E
Message-Id: <20191010110518.129256-2-borntraeger@de.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-10-10_04:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=0 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=999 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1908290000 definitions=main-1910100084
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

To analyze some performance issues with lock contention and scheduling
it is nice to know when diag9c did not result in any action or when
no action was tried.

Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---
 arch/s390/include/asm/kvm_host.h |  1 +
 arch/s390/kvm/diag.c             | 18 ++++++++++++++----
 arch/s390/kvm/kvm-s390.c         |  1 +
 3 files changed, 16 insertions(+), 4 deletions(-)

```
#### [PATCH] kvm: clear kvmclock MSR on reset
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11183083
Return-Path: <SRS0=OAn+=YD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E925714ED
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Oct 2019 10:50:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id C96142196E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Oct 2019 10:50:27 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="Yb24pgwv"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726869AbfJJKuY (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 10 Oct 2019 06:50:24 -0400
Received: from mail-wr1-f68.google.com ([209.85.221.68]:38081 "EHLO
        mail-wr1-f68.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726230AbfJJKuY (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 10 Oct 2019 06:50:24 -0400
Received: by mail-wr1-f68.google.com with SMTP id w12so7281560wro.5;
        Thu, 10 Oct 2019 03:50:21 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id;
        bh=nq8aTTwxoQayVKhvN2A/zAYVKjb3yhvqqfb15ovxI+M=;
        b=Yb24pgwv0com25khkQ7ORavf/pBJRJm3rpESqTdZkOZtcXq+ARHRuW+CRxkr1sJsWR
         KE6YW+UzKirDnW0aIcPiVPt1kM3xQuxe9FLmpwRkOEIbvRIz2WFALGdAK/UIgoIDiu9t
         em7GV6TWc4GphRF9D12b5S/BEhygUD3xcY8qR31ht7A8mAwHAFFLzt9FhCUurF/l8zBG
         okEmUb+TZiaXsP/7OByG0ZtGpNCeCko+fxF9IWuCKAhKnI3+DbNLrpfLW39WFJWuwWYL
         hQRdMB5eKvDS6YzE/fUs/VxQhyHDom4p0tQ3Z1+g36Mds6PGcJjK4tlb1vTjuKPnqUgF
         Hulw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id;
        bh=nq8aTTwxoQayVKhvN2A/zAYVKjb3yhvqqfb15ovxI+M=;
        b=RsrfSRZ09sRN74NA9XKO6PsxyYMTv0f+w+G+Xq9e4KorbqXNP21J6EnId2BTaFaUYr
         6HH6w1vGUNz/9MSNA3kVOgWPirlDDlzTcfUUKP5Q9Ojrf7NKrBCFpHhhVxe8c2c09vGj
         kcIm9se0j99/LtG3y4hptFt+NLP7GyNXSeFflZxKSaPgQw/G2BHTwO6tT0Qvi8FPhW3n
         rc3LlFJsXDVK3RE0v/+EdO0VdYssXhG8kRN8B5QYcgHPkVtUx7Ry8WOjuVXR9F7DjOC6
         He8kYGsqiCrWd/h7Kbo+Z+SbELKpRY1tUXqpBSXp1b6qGkptuRHBVKDMTNE0nfYB+kMD
         TxwA==
X-Gm-Message-State: APjAAAXiw38Qy4tL+3PpZaHrI+fppozq3Iwjrzaye+QmU4AdtmBdjh4B
        5y9tgwxukLbCExzuzMrlYuL3cF3F
X-Google-Smtp-Source: 
 APXvYqxNdZDbsK/iylAAYtWtc/CfhmfYlIQCb8cl6+RLKC/VLgmHbsWHZm5/d3QSMOjUDMV90ZJnyw==
X-Received: by 2002:adf:e3cb:: with SMTP id k11mr8573250wrm.80.1570704620325;
        Thu, 10 Oct 2019 03:50:20 -0700 (PDT)
Received: from 640k.localdomain ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 r13sm8259118wrn.0.2019.10.10.03.50.18
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Thu, 10 Oct 2019 03:50:18 -0700 (PDT)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: vkuznets@redhat.com, suleiman@google.com
Subject: [PATCH] kvm: clear kvmclock MSR on reset
Date: Thu, 10 Oct 2019 12:50:17 +0200
Message-Id: <1570704617-32285-1-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

After resetting the vCPU, the kvmclock MSR keeps the previous value but it is
not enabled.  This can be confusing, so fix it.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/x86.c | 6 ++----
 1 file changed, 2 insertions(+), 4 deletions(-)

```
#### [PATCH] KVM: s390: filter and count invalid yields
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11183073
Return-Path: <SRS0=OAn+=YD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 189891668
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Oct 2019 10:21:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 027EA21BE5
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Oct 2019 10:21:40 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726722AbfJJKVj (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 10 Oct 2019 06:21:39 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:48156 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1725923AbfJJKVi (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 10 Oct 2019 06:21:38 -0400
Received: from pps.filterd (m0098419.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 x9A9RcIR102560
        for <kvm@vger.kernel.org>; Thu, 10 Oct 2019 06:21:38 -0400
Received: from e06smtp03.uk.ibm.com (e06smtp03.uk.ibm.com [195.75.94.99])
        by mx0b-001b2d01.pphosted.com with ESMTP id 2vj1nathdk-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Thu, 10 Oct 2019 06:21:37 -0400
Received: from localhost
        by e06smtp03.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <borntraeger@de.ibm.com>;
        Thu, 10 Oct 2019 11:21:35 +0100
Received: from b06avi18626390.portsmouth.uk.ibm.com (9.149.26.192)
        by e06smtp03.uk.ibm.com (192.168.101.133) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Thu, 10 Oct 2019 11:21:32 +0100
Received: from d06av26.portsmouth.uk.ibm.com (d06av26.portsmouth.uk.ibm.com
 [9.149.105.62])
        by b06avi18626390.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id x9AAL19S37749016
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 10 Oct 2019 10:21:01 GMT
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id B4964AE056;
        Thu, 10 Oct 2019 10:21:31 +0000 (GMT)
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id A017EAE04D;
        Thu, 10 Oct 2019 10:21:31 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av26.portsmouth.uk.ibm.com (Postfix) with ESMTPS;
        Thu, 10 Oct 2019 10:21:31 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 25651)
        id 46072E01C6; Thu, 10 Oct 2019 12:21:31 +0200 (CEST)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: Janosch Frank <frankja@linux.vnet.ibm.com>
Cc: KVM <kvm@vger.kernel.org>, Cornelia Huck <cohuck@redhat.com>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        David Hildenbrand <david@redhat.com>,
        linux-s390 <linux-s390@vger.kernel.org>,
        Thomas Huth <thuth@redhat.com>
Subject: [PATCH] KVM: s390: filter and count invalid yields
Date: Thu, 10 Oct 2019 12:21:31 +0200
X-Mailer: git-send-email 2.21.0
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 19101010-0012-0000-0000-00000356D1DD
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19101010-0013-0000-0000-00002191DA44
Message-Id: <20191010102131.109736-1-borntraeger@de.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-10-10_04:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=0 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=925 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1908290000 definitions=main-1910100084
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

To analyze some performance issues with lock contention and scheduling
it is nice to know when diag9c did not result in any action.
At the same time avoid calling the scheduler (which can be expensive)
if we know that it does not make sense.

Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
---
 arch/s390/include/asm/kvm_host.h |  2 ++
 arch/s390/kvm/diag.c             | 23 +++++++++++++++++++----
 arch/s390/kvm/kvm-s390.c         |  2 ++
 3 files changed, 23 insertions(+), 4 deletions(-)

```
#### [PATCH kvmtool] virtio: Ensure virt_queue is always initialised
##### From: Will Deacon <will@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Will Deacon <will@kernel.org>
X-Patchwork-Id: 11183681
Return-Path: <SRS0=OAn+=YD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 992CD112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Oct 2019 14:28:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7AC0F2196E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Oct 2019 14:28:59 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1570717739;
	bh=JFPH/A6NZ3j9qzNoCJjMrAN/lWSFEF0+cBX8xEbnPnw=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=0+wAWYIPViuMXMNZs6KXISqAk3sYrU5gv5eTxnD+lWWT00TUwp6Y62karSBg5K62o
	 YdtbXi+d43937gJqIqHWaop2gq+SC//wETrggeIQ87xYraBmsCQaBrwj2drElfpxX6
	 hC45NXjOPtKvsviIMeuqFvBc64yl8eKOJFpuEycI=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726354AbfJJO26 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 10 Oct 2019 10:28:58 -0400
Received: from mail.kernel.org ([198.145.29.99]:40356 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725923AbfJJO26 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 10 Oct 2019 10:28:58 -0400
Received: from localhost.localdomain (236.31.169.217.in-addr.arpa
 [217.169.31.236])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-GCM-SHA256 (128/128 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id B5579206B6;
        Thu, 10 Oct 2019 14:28:56 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1570717737;
        bh=JFPH/A6NZ3j9qzNoCJjMrAN/lWSFEF0+cBX8xEbnPnw=;
        h=From:To:Cc:Subject:Date:From;
        b=bLpTpHbKuY0f3fbqL+b9781T4xlsCwiddWV9OsL5iA9IbyKgg7jYcUySuSV3D/n69
         2YDFa/THxKFyT0ySIEkIkz+6n4U11bNlWo9+qp8hRjKCtiPbapCQg71Ynv2hDd44Hu
         kKYnJ3ZdDKjLS+UfttDpL1KYG/lNpb4ZhNf4tCaI=
From: Will Deacon <will@kernel.org>
To: kvm@vger.kernel.org
Cc: Will Deacon <will@kernel.org>, Marc Zyngier <maz@kernel.org>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Andre Przywara <andre.przywara@arm.com>
Subject: [PATCH kvmtool] virtio: Ensure virt_queue is always initialised
Date: Thu, 10 Oct 2019 15:28:52 +0100
Message-Id: <20191010142852.15437-1-will@kernel.org>
X-Mailer: git-send-email 2.11.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Failing to initialise the virt_queue via virtio_init_device_vq() leaves,
amongst other things, the endianness unspecified. On arm/arm64 this
results in virtio_guest_to_host_uxx() treating the queue as big-endian
and trying to translate bogus addresses:

  Warning: unable to translate guest address 0x80b8249800000000 to host

Ensure the virt_queue is always initialised by the virtio device during
setup.

Cc: Marc Zyngier <maz@kernel.org>
Cc: Julien Thierry <julien.thierry.kdev@gmail.com>
Cc: Andre Przywara <andre.przywara@arm.com>
Signed-off-by: Will Deacon <will@kernel.org>
---
 virtio/balloon.c | 1 +
 virtio/rng.c     | 1 +
 virtio/scsi.c    | 1 +
 3 files changed, 3 insertions(+)

```
#### [RFC v2 1/2] kvm: Mechanism to copy host timekeeping parameters into guest.
##### From: Suleiman Souhlal <suleiman@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Suleiman Souhlal <suleiman@google.com>
X-Patchwork-Id: 11182813
Return-Path: <SRS0=OAn+=YD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 64E8614ED
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Oct 2019 07:39:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 3C72221D56
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Oct 2019 07:39:17 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="C/ywy926"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1733135AbfJJHiK (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 10 Oct 2019 03:38:10 -0400
Received: from mail-qk1-f202.google.com ([209.85.222.202]:40191 "EHLO
        mail-qk1-f202.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1733062AbfJJHbL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 10 Oct 2019 03:31:11 -0400
Received: by mail-qk1-f202.google.com with SMTP id x62so4621583qkb.7
        for <kvm@vger.kernel.org>; Thu, 10 Oct 2019 00:31:08 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=cqfOgbBFq1cuCJ9mBVUN432MN6WUG2Cztrp58NLs2Vw=;
        b=C/ywy926tafCeZE7HfHuO7rwVEIl1bPrxo0phIi3BlyVKKzbYBsdlulXvZwVmVv152
         pSDnC5TXL5u/rIOqk5sCwwe9zTponYR5613RtFPYKxAnp1P2hQy46QRdfWSTvAyKgHxT
         +s8OWL8JsfxGoGswhx87REvg1bxy6UD5+Z5N5/cwKMK++NsW9zmTgwvwrmXvdsO+RD46
         /CW3FiWNnaeM+/a58dWILDDj6hT3tHScRgNcUFz14HaFjyNfynJpHIgxuskOLZUyUB3u
         A58hwqSvLbz9Bz6p6Nydy/epNL3Cu9kha1GvBWk/w8LyVjBW7G6GiF68ffWwZtt7wfWn
         Xjlw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=cqfOgbBFq1cuCJ9mBVUN432MN6WUG2Cztrp58NLs2Vw=;
        b=ZGFWua94nRDszJMiwm1utT/gpE/25P3kbSiP5DhQBRyuNNw1OLeLmgl74jSuwLxMJ3
         7M2EkAZv+pEa64Oi9V0dh5YTWJZetMonzzhmsAvQYR8KykjRmYxInod8n82wonQIK7+D
         k10t0Lw6ddrOKTmFWhzDeYJenOteqQtDMxm9BVBz52EtfKeEwxZ580bG1ERWWDKS+WEd
         uXFhfBzTfYGz1HNqk+ng6MJ8gOpmVe+j2loSXSuUm/9/8+N1fgEJCSRKGJ2fz1F5u0PL
         aaoHtlvV7RACD6oBy9rcZXGtnvavwRBA9EaP0hqXJw+7z9vqurE5lMez7QI9ulg1Yfhm
         1V1Q==
X-Gm-Message-State: APjAAAVbaAcg5zLn8GrqgbLCKB4T90abhxE1bxYPENCLkoMDT+DtWBNA
        71RcarD9TGM3LqLg7K6nEpDDjs6+oqrnmQ==
X-Google-Smtp-Source: 
 APXvYqwCqV1V0a/8Ms8j/bNzW6sJqTHXo4TnK3h/ScttMp4kqMIWGm+wYIgZKsfhzUHRlf4rOEsV57bcyS0uBw==
X-Received: by 2002:a05:620a:136e:: with SMTP id
 d14mr8147013qkl.393.1570692668234;
 Thu, 10 Oct 2019 00:31:08 -0700 (PDT)
Date: Thu, 10 Oct 2019 16:30:54 +0900
In-Reply-To: <20191010073055.183635-1-suleiman@google.com>
Message-Id: <20191010073055.183635-2-suleiman@google.com>
Mime-Version: 1.0
References: <20191010073055.183635-1-suleiman@google.com>
X-Mailer: git-send-email 2.23.0.581.g78d2f28ef7-goog
Subject: [RFC v2 1/2] kvm: Mechanism to copy host timekeeping parameters into
 guest.
From: Suleiman Souhlal <suleiman@google.com>
To: pbonzini@redhat.com, rkrcmar@redhat.com, tglx@linutronix.de
Cc: john.stultz@linaro.org, sboyd@kernel.org,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        ssouhlal@freebsd.org, tfiga@chromium.org, vkuznets@redhat.com,
        Suleiman Souhlal <suleiman@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is used to synchronize time between host and guest.
The guest can request the (guest) physical address it wants the
data in through the MSR_KVM_TIMEKEEPER_EN MSR.

It currently assumes the host timekeeper is "tsc".

Signed-off-by: Suleiman Souhlal <suleiman@google.com>
---
 arch/x86/include/asm/kvm_host.h      |   3 +
 arch/x86/include/asm/pvclock-abi.h   |  27 ++++++
 arch/x86/include/uapi/asm/kvm_para.h |   1 +
 arch/x86/kvm/x86.c                   | 121 +++++++++++++++++++++++++++
 4 files changed, 152 insertions(+)

```
#### [PATCH] kvm/x86 : Replace BUG_ON(1) with BUG()X-Priority: 3
##### From: "richard.peng@oppo.com" <richard.peng@oppo.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: "richard.peng@oppo.com" <richard.peng@oppo.com>
X-Patchwork-Id: 11182547
Return-Path: <SRS0=OAn+=YD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AC889112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Oct 2019 03:01:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 971E2206C0
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Oct 2019 03:01:31 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732448AbfJJDBa (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 9 Oct 2019 23:01:30 -0400
Received: from m17617.mail.qiye.163.com ([59.111.176.17]:10034 "EHLO
        m17617.mail.qiye.163.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726621AbfJJDBa (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 9 Oct 2019 23:01:30 -0400
X-Greylist: delayed 522 seconds by postgrey-1.27 at vger.kernel.org;
 Wed, 09 Oct 2019 23:01:29 EDT
Received: from P80254710 (unknown [121.12.147.249])
        by m17617.mail.qiye.163.com (Hmail) with ESMTPA id 3A9C7261AAB;
        Thu, 10 Oct 2019 10:52:45 +0800 (CST)
Date: Thu, 10 Oct 2019 10:52:49 +0800
From: "richard.peng@oppo.com" <richard.peng@oppo.com>
To: pbonzini <pbonzini@redhat.com>, rkrcmar <rkrcmar@redhat.com>
Cc: kvm <kvm@vger.kernel.org>,
        linux-kernel <linux-kernel@vger.kernel.org>
Subject: [PATCH] kvm/x86 : Replace BUG_ON(1) with BUG()
X-Priority: 3
X-GUID: DC6DBE28-1918-4988-81E0-F1DEDA6BAD10
X-Has-Attach: no
X-Mailer: Foxmail 7.2.10.151[cn]
Mime-Version: 1.0
Message-ID: <201910101052488242114@oppo.com>
X-HM-Spam-Status: e1kfGhgUHx5ZQUtXWQgYFAkeWUFZVk9VTE5NS0tKT0xJT0xISk9ZV1koWU
        FJSUtLSjdXWS1ZQUlXWQkOFx4IWUFZNTQpNjo3JCkuNz5ZBg++
X-HM-Sender-Digest: e1kMHhlZQR0aFwgeV1kSHx4VD1lBWUc6MSI6Tgw4QzlNFUw9AywJGh0a
        NhxPFEtVSlVKTkxLTUxOQk1OTE5JVTMWGhIXVQkSGBMaCR9VCx4VHDsUCwsUVRgUFkVZV1kSC1lB
        WUpJSlVKSVVKT0xVSU9CWVdZCAFZQUpNSk03Bg++
X-HM-Tid: 0a6db3953e9b9375kuws3a9c7261aab
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Signed-off-by: Peng Hao <richard.peng@oppo.com>
---
 arch/x86/kvm/vmx/nested.c | 3 +--
 1 file changed, 1 insertion(+), 2 deletions(-)

-- 
2.7.4

```
#### [kvm-unit-tests PATCH 1/3] x86: emulator: use "SSE2" for the targetFrom: Bill Wendling <morbo@google.com>
##### From: Bill Wendling <morbo@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Bill Wendling <morbo@google.com>
X-Patchwork-Id: 11184053
Return-Path: <SRS0=OAn+=YD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CBEA517EE
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Oct 2019 18:35:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A3A1421835
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Oct 2019 18:35:44 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="kKdN3OX3"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726628AbfJJSfo (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 10 Oct 2019 14:35:44 -0400
Received: from mail-pl1-f202.google.com ([209.85.214.202]:56927 "EHLO
        mail-pl1-f202.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725901AbfJJSfn (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 10 Oct 2019 14:35:43 -0400
Received: by mail-pl1-f202.google.com with SMTP id x8so4371069plr.23
        for <kvm@vger.kernel.org>; Thu, 10 Oct 2019 11:35:42 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=XTuI7th3+9dwO3nKtBiY4qgOMbcjEb2zppHYOAbpHRc=;
        b=kKdN3OX3CtBaAFl02mXXGN9Uw9dpGcwGpg9dBRYNrYe+L/yTf7H2ZLZJZK2knPepwa
         vtBZYFcyb3823+jWUniHF+ovklg4cHR2CBJfkXCDjshpGhSBhiJu8S8GD1OErEsr2JvN
         Uml0+MFhqs0Ium2VRXFp9k7RE9Xl5XBRbmn5a7f9AGxS5oaDXK60PowXAILjTwM5Oopm
         +B4GqcXZv7sEth/Ua24ySRWpbRxXDB8pngGF4dzalrsSWROXSglxtog6gTlGS93vyrPI
         ngK2v2GbXlm+bcn9/WGl5IrpaO2sjzv3PDRj5D7MH55T3Lh65HRW7FiRFQnmusHLQhlq
         tiwA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=XTuI7th3+9dwO3nKtBiY4qgOMbcjEb2zppHYOAbpHRc=;
        b=P1g40f5LmZ1ZSSLL+BkxBrelPR71kfsURUqD2h3IRVvC15VIwyqRXitW6QjWhArnHP
         3OgnyjOeETD20hCUME/svvfVuWwyy2+hfi+keIE5R0agAFi66Ov9GaVYj87BXPimgGUu
         xKFVguOoD43E+zCaxSW+7ZTj6IoK6vQ7YbOKTYRWQELoxicj8pIIkYMZISNEkqnoOsUC
         yFtpuAi+Tx7GJJpHf9q7kBCn+jDL3mD+0+cXAAAAv6Hx2wOlFTxapMDza9ZveiIuCX0t
         gyno80RlOs95I0QWMsqegkG6soAj1VWDjEzgXmFc5NJkqU5yjFjfTWq8MwG19dldd29k
         bqrA==
X-Gm-Message-State: APjAAAVJki3iGVs9QMw9rxHXJONqNG704fLSIfux5f2N4mv8CiC2x8v+
        LwGWqQTRDlOCRyCFiMhN49v1odyNRgrHEVil1vsB7TWfW65Ew/ymKdDDDvFTxLAERDlf18MI7o0
        ZFuXXJR6A/fQYvARajCDqdf3/NuAT35EgfcEOWu5cE1PzJG5ljBljnA==
X-Google-Smtp-Source: 
 APXvYqxaFHpZyRfjoYxSLO8vh1f5AyAY5wQ6uNQfo+9W+NQpK40h4qWKe74eEGWtwF+3QqinDw94Z3UU9w==
X-Received: by 2002:a63:dc49:: with SMTP id f9mr12828634pgj.91.1570732541309;
 Thu, 10 Oct 2019 11:35:41 -0700 (PDT)
Date: Thu, 10 Oct 2019 11:35:04 -0700
In-Reply-To: <20191010183506.129921-1-morbo@google.com>
Message-Id: <20191010183506.129921-2-morbo@google.com>
Mime-Version: 1.0
References: <20191010183506.129921-1-morbo@google.com>
X-Mailer: git-send-email 2.23.0.700.g56cf767bdb-goog
Subject: [kvm-unit-tests PATCH 1/3] x86: emulator: use "SSE2" for the target
From: Bill Wendling <morbo@google.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com
Cc: jmattson@google.com, Bill Wendling <morbo@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The movdqu and movapd instructions are SSE2 instructions. Clang
interprets the __attribute__((target("sse"))) as allowing SSE only
instructions. Using SSE2 instructions cause an error.

Signed-off-by: Bill Wendling <morbo@google.com>
---
 x86/emulator.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] selftests: kvm: make syncregs more reliable on s390
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11182829
Return-Path: <SRS0=OAn+=YD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 59A571575
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Oct 2019 07:53:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 445602190F
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Oct 2019 07:53:45 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726923AbfJJHxo (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 10 Oct 2019 03:53:44 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:32454 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727130AbfJJHxo (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 10 Oct 2019 03:53:44 -0400
Received: from pps.filterd (m0098419.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 x9A7rbJq004672
        for <kvm@vger.kernel.org>; Thu, 10 Oct 2019 03:53:42 -0400
Received: from e06smtp04.uk.ibm.com (e06smtp04.uk.ibm.com [195.75.94.100])
        by mx0b-001b2d01.pphosted.com with ESMTP id 2vhx4dcedq-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Thu, 10 Oct 2019 03:53:39 -0400
Received: from localhost
        by e06smtp04.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <borntraeger@de.ibm.com>;
        Thu, 10 Oct 2019 08:52:42 +0100
Received: from b06cxnps3074.portsmouth.uk.ibm.com (9.149.109.194)
        by e06smtp04.uk.ibm.com (192.168.101.134) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Thu, 10 Oct 2019 08:52:38 +0100
Received: from d06av26.portsmouth.uk.ibm.com (d06av26.portsmouth.uk.ibm.com
 [9.149.105.62])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id x9A7qbbR41615564
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 10 Oct 2019 07:52:37 GMT
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 4AC9DAE053;
        Thu, 10 Oct 2019 07:52:37 +0000 (GMT)
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 3656AAE04D;
        Thu, 10 Oct 2019 07:52:37 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av26.portsmouth.uk.ibm.com (Postfix) with ESMTPS;
        Thu, 10 Oct 2019 07:52:37 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 25651)
        id D8F05E0174; Thu, 10 Oct 2019 09:52:36 +0200 (CEST)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: Thomas Huth <thuth@redhat.com>
Cc: KVM <kvm@vger.kernel.org>, Cornelia Huck <cohuck@redhat.com>,
 Christian Borntraeger <borntraeger@de.ibm.com>,
 Janosch Frank <frankja@linux.vnet.ibm.com>,
 David Hildenbrand <david@redhat.com>, Paolo Bonzini <pbonzini@redhat.com>,
	=?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 linux-s390 <linux-s390@vger.kernel.org>
Subject: [PATCH] selftests: kvm: make syncregs more reliable on s390
Date: Thu, 10 Oct 2019 09:52:36 +0200
X-Mailer: git-send-email 2.21.0
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 19101007-0016-0000-0000-000002B6C504
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19101007-0017-0000-0000-00003317CF89
Message-Id: <20191010075236.100247-1-borntraeger@de.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-10-10_04:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=0 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=999 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1908290000 definitions=main-1910100074
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

similar to commit 2c57da356800 ("selftests: kvm: fix sync_regs_test with
newer gccs") and commit 204c91eff798a ("KVM: selftests: do not blindly
clobber registers in guest asm") we better do not rely on gcc leaving
r11 untouched.  We can write the simple ucall inline and have the guest
code completely as small assembler function.

Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
Suggested-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
---
 .../testing/selftests/kvm/s390x/sync_regs_test.c  | 15 +++++++++------
 1 file changed, 9 insertions(+), 6 deletions(-)

```
#### [PATCH v4] x86/hyperv: make vapic support x2apic modeThread-Topic: [PATCH v4] x86/hyperv: make vapic support x2apic mode
##### From: Roman Kagan <rkagan@virtuozzo.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Roman Kagan <rkagan@virtuozzo.com>
X-Patchwork-Id: 11183385
Return-Path: <SRS0=OAn+=YD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9175C76
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Oct 2019 12:33:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 667BD21A4A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Oct 2019 12:33:25 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=virtuozzo.com header.i=@virtuozzo.com
 header.b="lVZ70xQx"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2387583AbfJJMdW (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 10 Oct 2019 08:33:22 -0400
Received: from mail-eopbgr70134.outbound.protection.outlook.com
 ([40.107.7.134]:51810
        "EHLO EUR04-HE1-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726923AbfJJMdW (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 10 Oct 2019 08:33:22 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=Ay26mq05w/y77uUjxGA2gU3omDIgyQ1/Hu4+2+kNMdGUaaKMOlVoiS5JB5cEfYkrYeUQnRln4d/mMEiUWH7kK8fPwOgUf+7HcBLg8yh0QQrd9HkDytEGs2xt+FyxqOMV11EzZ0IA3lXid7UBPLDJG5PiKRJ5AwWchFBCr44K2P23kmB86tNxYZmqJPqynZVvrE7EY05pljY+ESX8/VHWWzvUn9vCX2gTJhacWHG2jD9fEVuV+RqBRYUOA0nNzJzHWMqAXvs2xxKx1bAwj5y+Tj0sFe/tRYODen6pdxu1FMHqoLqToSvIz67AxrPIXTLXoaTWPkpi82/hlSDwlyaPxw==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=lrk0oUG60Jr/2lcLKT0L9p6LapgtXHX/LG9XubPNpmw=;
 b=BWyEfnAmRKUXmxHGEXYexNlr7mon1PLp9niDzr8EPtB8J8ucKIjadZInkz6Kj2ChPOs9CU87TI/IbJTJkylLNyj+RHQYY3GyUTqBVGNJqHy4mHepHfV9ug/IrMnWmeX30+vqnm4w66pdyo5S6U5TVwbRnQGG5OSwTUFD7YjyLrG9kt8Jjo/lU4y3sypHoCMlIfxicwCrQvEHiduyCRimDw6dggHTcxnxgXXruC2C03nGTrm+sU/fC4IYj6SdTtcKA/apRoW9zJ73HTzhm3uKQX9tzBsHyQ7433lOszMas8kO6aASKyJ2BquySpeG4uK6xTrHx7XjJlGizpirUH063w==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=virtuozzo.com; dmarc=pass action=none
 header.from=virtuozzo.com; dkim=pass header.d=virtuozzo.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=virtuozzo.com;
 s=selector2;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=lrk0oUG60Jr/2lcLKT0L9p6LapgtXHX/LG9XubPNpmw=;
 b=lVZ70xQxwNpjxeyoaDa0o1tXnpn8fadRikV+n3XCHcgutql85k1I2ud/XDjMiT58drHl8YrxdCZ9oyrTZ9G9sv4TNkvkH1OX7gqGyZaO5+n1ZgdWFADmL0+h0DIF63GSzPkvK3CGq8V1RkeUVgJLtEBk0rGxW90BmhVqG6qExyY=
Received: from AM0PR08MB5537.eurprd08.prod.outlook.com (20.179.36.87) by
 AM0PR08MB3953.eurprd08.prod.outlook.com (20.178.117.157) with Microsoft SMTP
 Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.2347.16; Thu, 10 Oct 2019 12:33:06 +0000
Received: from AM0PR08MB5537.eurprd08.prod.outlook.com
 ([fe80::a8ea:5223:db78:dd3]) by AM0PR08MB5537.eurprd08.prod.outlook.com
 ([fe80::a8ea:5223:db78:dd3%7]) with mapi id 15.20.2347.016; Thu, 10 Oct 2019
 12:33:05 +0000
From: Roman Kagan <rkagan@virtuozzo.com>
To: Michael Kelley <mikelley@microsoft.com>,
        Lan Tianyu <Tianyu.Lan@microsoft.com>,
        Joerg Roedel <jroedel@suse.de>,
        "K. Y. Srinivasan" <kys@microsoft.com>,
        Haiyang Zhang <haiyangz@microsoft.com>,
        Stephen Hemminger <sthemmin@microsoft.com>,
        Sasha Levin <sashal@kernel.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        "H. Peter Anvin" <hpa@zytor.com>,
        "x86@kernel.org" <x86@kernel.org>,
        "linux-hyperv@vger.kernel.org" <linux-hyperv@vger.kernel.org>,
        "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>,
        Vitaly Kuznetsov <vkuznets@redhat.com>
CC: "kvm@vger.kernel.org" <kvm@vger.kernel.org>
Subject: [PATCH v4] x86/hyperv: make vapic support x2apic mode
Thread-Topic: [PATCH v4] x86/hyperv: make vapic support x2apic mode
Thread-Index: AQHVf2bd3sDcAG/lCUuldIC8p8n4Qw==
Date: Thu, 10 Oct 2019 12:33:05 +0000
Message-ID: <20191010123258.16919-1-rkagan@virtuozzo.com>
Accept-Language: en-US, ru-RU
Content-Language: en-US
X-MS-Has-Attach: 
X-MS-TNEF-Correlator: 
x-originating-ip: [185.231.240.5]
x-clientproxiedby: HE1P190CA0004.EURP190.PROD.OUTLOOK.COM (2603:10a6:3:bc::14)
 To AM0PR08MB5537.eurprd08.prod.outlook.com (2603:10a6:208:148::23)
authentication-results: spf=none (sender IP is )
 smtp.mailfrom=rkagan@virtuozzo.com;
x-ms-exchange-messagesentrepresentingtype: 1
x-mailer: git-send-email 2.21.0
x-ms-publictraffictype: Email
x-ms-office365-filtering-correlation-id: 9c6076ea-86bb-4fd6-ee67-08d74d7e0001
x-ms-traffictypediagnostic: AM0PR08MB3953:
x-microsoft-antispam-prvs: 
 <AM0PR08MB3953803B65CFE212FAAB4BF5C9940@AM0PR08MB3953.eurprd08.prod.outlook.com>
x-ms-oob-tlc-oobclassifiers: OLM:8882;
x-forefront-prvs: 018632C080
x-forefront-antispam-report: 
 SFV:NSPM;SFS:(10019020)(136003)(346002)(39850400004)(376002)(396003)(366004)(199004)(189003)(71200400001)(14444005)(478600001)(66556008)(81156014)(316002)(5660300002)(99286004)(71190400001)(52116002)(2906002)(110136005)(81166006)(8676002)(66066001)(66446008)(6436002)(26005)(6486002)(6506007)(1511001)(256004)(8936002)(386003)(64756008)(1076003)(6512007)(2501003)(66476007)(102836004)(186003)(50226002)(66946007)(25786009)(4326008)(2616005)(486006)(6116002)(2201001)(86362001)(3846002)(14454004)(7736002)(305945005)(36756003)(7416002)(476003)(921003)(1121003);DIR:OUT;SFP:1102;SCL:1;SRVR:AM0PR08MB3953;H:AM0PR08MB5537.eurprd08.prod.outlook.com;FPR:;SPF:None;LANG:en;PTR:InfoNoRecords;A:1;MX:1;
received-spf: None (protection.outlook.com: virtuozzo.com does not designate
 permitted sender hosts)
x-ms-exchange-senderadcheck: 1
x-microsoft-antispam: BCL:0;
x-microsoft-antispam-message-info: 
 +QgMTUgx10hm4a7+gr7C7Nstc9JegdK7eKzYtERDa66Z9Yx1JUXMqS4NOLrNaYFrZCYae5D2bHcw/wpZGm3KYfVTAtCrnSNRKIpKU9MzAuljrK10ASvbkiZo7253615E/5nuzFygk7IguPeBT/worZ4Din2UeveW86/DT0F15Tr5hoJbbKxB1iGLTLX/trnRNNhzoiLYGYdudy8UJ66JdtAS/ItsOuOMwPLo9FBHxHZrxxpqnDS16WvXdWzK53PcxK15p5WY0FUjrF2w2Ldl45w24wmfZoH1iOcSgtsOA3AWXS5HmXRhBzFUJg20uZuMmqqIrfu5quES+c0+B1CNA1e17NjlLUoo8zQKhITFpFYynnDVzzlknztJ2frTyJAEDsHiQPom1wPUXYjrmAOUKqHi1O29yaqLHkXY6RjF0Xk=
x-ms-exchange-transport-forked: True
MIME-Version: 1.0
X-OriginatorOrg: virtuozzo.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 9c6076ea-86bb-4fd6-ee67-08d74d7e0001
X-MS-Exchange-CrossTenant-originalarrivaltime: 10 Oct 2019 12:33:05.8738
 (UTC)
X-MS-Exchange-CrossTenant-fromentityheader: Hosted
X-MS-Exchange-CrossTenant-id: 0bc7f26d-0264-416e-a6fc-8352af79c58f
X-MS-Exchange-CrossTenant-mailboxtype: HOSTED
X-MS-Exchange-CrossTenant-userprincipalname: 
 QUrkhrEgdL6NseTTYaDK8cvu5MWPf+5NuF/xnluFppJdyRNHZI+oUnywM4SW0KaHawQO++85kjuZUA09NNVMew==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: AM0PR08MB3953
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Now that there's Hyper-V IOMMU driver, Linux can switch to x2apic mode
when supported by the vcpus.

However, the apic access functions for Hyper-V enlightened apic assume
xapic mode only.

As a result, Linux fails to bring up secondary cpus when run as a guest
in QEMU/KVM with both hv_apic and x2apic enabled.

According to Michael Kelley, when in x2apic mode, the Hyper-V synthetic
apic MSRs behave exactly the same as the corresponding architectural
x2apic MSRs, so there's no need to override the apic accessors.  The
only exception is hv_apic_eoi_write, which benefits from lazy EOI when
available; however, its implementation works for both xapic and x2apic
modes.

Fixes: 29217a474683 ("iommu/hyper-v: Add Hyper-V stub IOMMU driver")
Fixes: 6b48cb5f8347 ("X86/Hyper-V: Enlighten APIC access")
Cc: stable@vger.kernel.org
Suggested-by: Michael Kelley <mikelley@microsoft.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Reviewed-by: Michael Kelley <mikelley@microsoft.com>
Signed-off-by: Roman Kagan <rkagan@virtuozzo.com>
---
v3 -> v4:
- adjust the log message [Vitaly, Michael]

v2 -> v3:
- do not introduce x2apic-capable hv_apic accessors; leave original
  x2apic accessors instead

v1 -> v2:
- add ifdefs to handle !CONFIG_X86_X2APIC

 arch/x86/hyperv/hv_apic.c | 20 +++++++++++++++-----
 1 file changed, 15 insertions(+), 5 deletions(-)

```
#### [PATCH v6 1/2] x86/cpu: Add support for UMONITOR/UMWAIT/TPAUSE
##### From: Tao Xu <tao3.xu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Tao Xu <tao3.xu@intel.com>
X-Patchwork-Id: 11182597
Return-Path: <SRS0=OAn+=YD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0572313BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Oct 2019 05:17:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E4884218DE
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Oct 2019 05:17:03 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729045AbfJJFRD (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 10 Oct 2019 01:17:03 -0400
Received: from mga07.intel.com ([134.134.136.100]:13392 "EHLO mga07.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726065AbfJJFRC (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 10 Oct 2019 01:17:02 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by orsmga105.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 09 Oct 2019 22:17:02 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.67,279,1566889200";
   d="scan'208";a="193089179"
Received: from tao-optiplex-7060.sh.intel.com ([10.239.159.36])
  by fmsmga008.fm.intel.com with ESMTP; 09 Oct 2019 22:17:00 -0700
From: Tao Xu <tao3.xu@intel.com>
To: pbonzini@redhat.com, rth@twiddle.net, ehabkost@redhat.com,
        mtosatti@redhat.com
Cc: qemu-devel@nongnu.org, kvm@vger.kernel.org, tao3.xu@intel.com,
        jingqi.liu@intel.com
Subject: [PATCH v6 1/2] x86/cpu: Add support for UMONITOR/UMWAIT/TPAUSE
Date: Thu, 10 Oct 2019 13:16:56 +0800
Message-Id: <20191010051657.28163-2-tao3.xu@intel.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20191010051657.28163-1-tao3.xu@intel.com>
References: <20191010051657.28163-1-tao3.xu@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

UMONITOR, UMWAIT and TPAUSE are a set of user wait instructions.
This patch adds support for user wait instructions in KVM. Availability
of the user wait instructions is indicated by the presence of the CPUID
feature flag WAITPKG CPUID.0x07.0x0:ECX[5]. User wait instructions may
be executed at any privilege level, and use IA32_UMWAIT_CONTROL MSR to
set the maximum time.

The patch enable the umonitor, umwait and tpause features in KVM.
Because umwait and tpause can put a (psysical) CPU into a power saving
state, by default we dont't expose it to kvm and enable it only when
guest CPUID has it. And use QEMU command-line "-overcommit cpu-pm=on"
(enable_cpu_pm is enabled), a VM can use UMONITOR, UMWAIT and TPAUSE
instructions. If the instruction causes a delay, the amount of time
delayed is called here the physical delay. The physical delay is first
computed by determining the virtual delay (the time to delay relative to
the VM’s timestamp counter). Otherwise, UMONITOR, UMWAIT and TPAUSE cause
an invalid-opcode exception(#UD).

The release document ref below link:
https://software.intel.com/sites/default/files/\
managed/39/c5/325462-sdm-vol-1-2abcd-3abcd.pdf

Co-developed-by: Jingqi Liu <jingqi.liu@intel.com>
Signed-off-by: Jingqi Liu <jingqi.liu@intel.com>
Signed-off-by: Tao Xu <tao3.xu@intel.com>
---

Changes in v6:
    - Only remove CPUID_7_0_ECX_WAITPKG if enable_cpu_pm is not set.
    (Paolo)
---
 target/i386/cpu.c | 3 ++-
 target/i386/cpu.h | 1 +
 target/i386/kvm.c | 4 ++++
 3 files changed, 7 insertions(+), 1 deletion(-)

```
#### [PATCH] x86/kvm: Fix -Wmissing-prototypes warnings
##### From: Yi Wang <wang.yi59@zte.com.cn>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Yi Wang <wang.yi59@zte.com.cn>
X-Patchwork-Id: 11182695
Return-Path: <SRS0=OAn+=YD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DF8D91575
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Oct 2019 06:35:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id BFC3E218DE
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Oct 2019 06:35:18 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732759AbfJJGfP convert rfc822-to-8bit (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 10 Oct 2019 02:35:15 -0400
Received: from mxhk.zte.com.cn ([63.217.80.70]:48394 "EHLO mxhk.zte.com.cn"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727041AbfJJGfP (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 10 Oct 2019 02:35:15 -0400
Received: from mse-fl2.zte.com.cn (unknown [10.30.14.239])
        by Forcepoint Email with ESMTPS id D24F9A31057175D3B519;
        Thu, 10 Oct 2019 14:35:12 +0800 (CST)
Received: from notes_smtp.zte.com.cn (notes_smtp.zte.com.cn [10.30.1.239])
        by mse-fl2.zte.com.cn with ESMTP id x9A6Z01J026849;
        Thu, 10 Oct 2019 14:35:00 +0800 (GMT-8)
        (envelope-from wang.yi59@zte.com.cn)
Received: from fox-host8.localdomain ([10.74.120.8])
          by szsmtp06.zte.com.cn (Lotus Domino Release 8.5.3FP6)
          with ESMTP id 2019101014352792-4203136 ;
          Thu, 10 Oct 2019 14:35:27 +0800
From: Yi Wang <wang.yi59@zte.com.cn>
To: pbonzini@redhat.com
Cc: rkrcmar@redhat.com, sean.j.christopherson@intel.com,
        vkuznets@redhat.com, wanpengli@tencent.com, jmattson@google.com,
        joro@8bytes.org, tglx@linutronix.de, mingo@redhat.com,
        bp@alien8.de, hpa@zytor.com, x86@kernel.org, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, xue.zhihong@zte.com.cn,
        wang.yi59@zte.com.cn, up2wing@gmail.com, wang.liang82@zte.com.cn
Subject: [PATCH] x86/kvm: Fix -Wmissing-prototypes warnings
Date: Thu, 10 Oct 2019 14:37:25 +0800
Message-Id: <1570689445-43358-1-git-send-email-wang.yi59@zte.com.cn>
X-Mailer: git-send-email 1.8.3.1
MIME-Version: 1.0
X-MIMETrack: Itemize by SMTP Server on SZSMTP06/server/zte_ltd(Release
 8.5.3FP6|November
 21, 2013) at 2019-10-10 14:35:28,
        Serialize by Router on notes_smtp/zte_ltd(Release 9.0.1FP7|August  17,
 2016) at
 2019-10-10 14:35:04
X-MAIL: mse-fl2.zte.com.cn x9A6Z01J026849
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We get two warning when build kernel with W=1:
arch/x86/kernel/kvm.c:872:6: warning: no previous prototype for ‘arch_haltpoll_enable’ [-Wmissing-prototypes]
arch/x86/kernel/kvm.c:885:6: warning: no previous prototype for ‘arch_haltpoll_disable’ [-Wmissing-prototypes]

Including the missing head file can fix this.

Signed-off-by: Yi Wang <wang.yi59@zte.com.cn>
---
 arch/x86/kernel/kvm.c | 1 +
 1 file changed, 1 insertion(+)

```
