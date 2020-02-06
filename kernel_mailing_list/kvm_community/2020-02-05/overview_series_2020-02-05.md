#### [PATCH v4 01/14] KVM: X86: Change parameter for fast_page_fault tracepoint
##### From: Peter Xu <peterx@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11365683
Return-Path: <SRS0=nIH0=3Z=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E66DF17E0
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  5 Feb 2020 02:51:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id BDE912253D
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  5 Feb 2020 02:51:21 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="ghyN+ezi"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727902AbgBECvP (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 4 Feb 2020 21:51:15 -0500
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:33780 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727796AbgBECvO (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 4 Feb 2020 21:51:14 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1580871074;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=aRATN7sKWcZdWDij4U02uLG0iob0fByx2e0Dt2ueT/w=;
        b=ghyN+ezigxQRPpt9/+YsXDURdcO6DUtSb9loBf5zsT9jmBsSfH/cvV2QqnOcLLkWbz29Gy
        dF8zz8omT/1Gb4xOcnQPY9r3rU66dJR5SSL9/RXlm8hK0tUljnfOKdA45I7OCyTxh4Zs1u
        hIFxDNd9bLAVC4fPxWUYv2j2wwykqQA=
Received: from mail-qt1-f199.google.com (mail-qt1-f199.google.com
 [209.85.160.199]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-309-XODNSm8kMQeugOF_DE0fyw-1; Tue, 04 Feb 2020 21:51:12 -0500
X-MC-Unique: XODNSm8kMQeugOF_DE0fyw-1
Received: by mail-qt1-f199.google.com with SMTP id c22so380893qtn.23
        for <kvm@vger.kernel.org>; Tue, 04 Feb 2020 18:51:12 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=aRATN7sKWcZdWDij4U02uLG0iob0fByx2e0Dt2ueT/w=;
        b=nTII+8lAoe1HKMcytn9qYDHbIqa+j8+ZTkPj6M90QGrhJUT21jP+idSng9eymBdSj0
         AjkVH5pAS15kslrHX2k9HySZ2CccPv6cF+Cu7jgViBlrZzJTuC5bPQx8sBoosCdiQlWb
         z47AR2VQA2VvB+rGQUdvsJLicE9/jTIBMuxjuVTh7gvKBkmpMZV6onl7fnWYEgIRggX+
         eyRj8ovNIcPbNTAko00i0TpDO3GbVOCUS6TuTfPtS3q2Z37wb3qOOlfIommNZ2zvXd77
         M/OvqKPDW9pDRrQJaJUiMoO2ESmaYqa4AipFmiQ5eA+tgcucSEnCw05bbdSYdblSjK/P
         GxcA==
X-Gm-Message-State: APjAAAX/Qsnz0+ZODG2TtgwPC89qTfDc8lwhoHGcj6kFco034Y9A0fNM
        BrJX2CRkiKGYsoLxOpUMi5I90px9uyYYwU9nC79oWek4CuEBqQ0oRuIOGngmMpCoO0RtSdaxNvn
        OpWS0uRfVwZvA
X-Received: by 2002:a05:6214:1428:: with SMTP id
 o8mr31031719qvx.87.1580871071594;
        Tue, 04 Feb 2020 18:51:11 -0800 (PST)
X-Google-Smtp-Source: 
 APXvYqwXJBNvuIFypmIVFhWk564W4B95sKGIgajPPJbgokUyyK+XPEQ6Y2igS687dPfdxxOzpb45IA==
X-Received: by 2002:a05:6214:1428:: with SMTP id
 o8mr31031696qvx.87.1580871071387;
        Tue, 04 Feb 2020 18:51:11 -0800 (PST)
Received: from xz-x1.redhat.com ([2607:9880:19c8:32::2])
        by smtp.gmail.com with ESMTPSA id
 b141sm12380923qkg.33.2020.02.04.18.51.09
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 04 Feb 2020 18:51:10 -0800 (PST)
From: Peter Xu <peterx@redhat.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: Christophe de Dinechin <dinechin@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Jason Wang <jasowang@redhat.com>,
        Yan Zhao <yan.y.zhao@intel.com>,
        "Michael S . Tsirkin" <mst@redhat.com>, peterx@redhat.com,
        Kevin Tian <kevin.tian@intel.com>,
        Alex Williamson <alex.williamson@redhat.com>,
        "Dr . David Alan Gilbert" <dgilbert@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>
Subject: [PATCH v4 01/14] KVM: X86: Change parameter for fast_page_fault
 tracepoint
Date: Tue,  4 Feb 2020 21:50:52 -0500
Message-Id: <20200205025105.367213-2-peterx@redhat.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20200205025105.367213-1-peterx@redhat.com>
References: <20200205025105.367213-1-peterx@redhat.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

It would be clearer to dump the return value to know easily on whether
did we go through the fast path for handling current page fault.
Remove the old two last parameters because after all the old/new sptes
were dumped in the same line.

Signed-off-by: Peter Xu <peterx@redhat.com>
---
 arch/x86/kvm/mmutrace.h | 9 ++-------
 1 file changed, 2 insertions(+), 7 deletions(-)

```
#### [PATCH] KVM: SVM: relax conditions for allowing MSR_IA32_SPEC_CTRL accesses
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11366449
Return-Path: <SRS0=nIH0=3Z=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4CF8F921
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  5 Feb 2020 15:20:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 2AE6B222D9
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  5 Feb 2020 15:20:31 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="b5JgSbc6"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726957AbgBEPUS (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 5 Feb 2020 10:20:18 -0500
Received: from mail-wm1-f66.google.com ([209.85.128.66]:37308 "EHLO
        mail-wm1-f66.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726534AbgBEPUR (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 5 Feb 2020 10:20:17 -0500
Received: by mail-wm1-f66.google.com with SMTP id f129so3267122wmf.2;
        Wed, 05 Feb 2020 07:20:16 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id;
        bh=Eu/czLrqDMFVqxZHLoEa1l5MyCiw1QB7Y2F2E91wwso=;
        b=b5JgSbc6vwObcogWIFqOdkOezS9kTXNdfyy/tlLf8DObaHOghHX8McPh9K4mcOiOKB
         85UssOj3VIaD1h+nwh5BdeqmGmJDmS5g4U5wkVdxkPjOHz9YJFxJar3htH96Vt7+ayPU
         WM6ka3hNGbsAWbiknIrYLmhLGQ9Tn0EZBb8Pg/xdCbEaSSz+IyRJhSLGcLfEbmkhngY0
         2x6ciCIVfpPBxkOazxKfJoVagfZ7yLz0FGCe/tY3X87XxX/Fx24mHowRqnGy9r3MCW34
         yLlEPw+vip+6ianwxrIrlL06NBD4Ihg27IkXdJwZzMQoadZLUZOhx6w80Vu+44E5L53+
         7+ZA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id;
        bh=Eu/czLrqDMFVqxZHLoEa1l5MyCiw1QB7Y2F2E91wwso=;
        b=XyRMYZl/UVvpu1lZmFBEk9bR5OEF+qvKzm7PAcV+XTHLkYKCxV7QGn1Y8LTKYMiWtp
         BJUA3DaOrlVdUiV1399Xo7lh2RXK2/kTNczUM6Nu3FTflisY8AfE1kMgz30zpuTOAtdV
         xTpd3OHi4FMXjhxCgf8zkcLc6TTpfb8p//cRLYl+yKs577DpI0cC90OijE9pt68zclD3
         ib+Esfctre7+sVJedLeQloyJJtkHc4C+7s37XO3CFm6MxysED5vLepZFS3e4dGEtRFGI
         yqH3sFWkx3kR4A6SMkIz6IuSMVFW1rraTSo6kCOoEULD8mRKZnpd8lR49l2LIiC3o+Uz
         zcWQ==
X-Gm-Message-State: APjAAAXTk0LS71sdMpGi3hjsq5Zz7XKme8PegMUqJOA+Dzqxy46w4/oW
        R9HNm33ueXprBumnDcZrPBCE0EY6
X-Google-Smtp-Source: 
 APXvYqwuVi7TatktuYrcptCy2OsCtreFpYhjY4vsG4aVYW8c+xoZYJfb6LlcgJJA4tkEcMtI/fcZ8A==
X-Received: by 2002:a1c:7c08:: with SMTP id x8mr6582758wmc.106.1580915630238;
        Wed, 05 Feb 2020 07:13:50 -0800 (PST)
Received: from 640k.localdomain.com ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id c15sm176452wrt.1.2020.02.05.07.13.49
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Wed, 05 Feb 2020 07:13:49 -0800 (PST)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: dgilbert@redhat.com, jmattson@google.com
Subject: [PATCH] KVM: SVM: relax conditions for allowing MSR_IA32_SPEC_CTRL
 accesses
Date: Wed,  5 Feb 2020 16:13:48 +0100
Message-Id: <1580915628-42930-1-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Userspace that does not know about the AMD_IBRS bit might still
allow the guest to protect itself with MSR_IA32_SPEC_CTRL using
the Intel SPEC_CTRL bit.  However, svm.c disallows this and will
cause a #GP in the guest when writing to the MSR.  Fix this by
loosening the test and allowing the Intel CPUID bit, and in fact
allow the AMD_STIBP bit as well since it allows writing to
MSR_IA32_SPEC_CTRL too.

Reported-by: Zhiyi Guo <zhguo@redhat.com>
Analyzed-by: Dr. David Alan Gilbert <dgilbert@redhat.com>
Analyzed-by: Laszlo Ersek <lersek@redhat.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/svm.c | 4 ++++
 1 file changed, 4 insertions(+)

```
#### [PATCH] kvm-unit-test: nSVM: Restructure nSVM test code
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11367211
Return-Path: <SRS0=nIH0=3Z=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 46C22924
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  5 Feb 2020 21:27:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id DB1BF2082E
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  5 Feb 2020 21:27:56 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="IzzgjfpW";
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="LC1SeT4Q"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727237AbgBEV14 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 5 Feb 2020 16:27:56 -0500
Received: from aserp2120.oracle.com ([141.146.126.78]:37244 "EHLO
        aserp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727106AbgBEV1z (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 5 Feb 2020 16:27:55 -0500
Received: from pps.filterd (aserp2120.oracle.com [127.0.0.1])
        by aserp2120.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 015LDcN4107390;
        Wed, 5 Feb 2020 21:27:44 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=corp-2020-01-29;
 bh=wINA1FZ+1noeRFPFibnUIyc3AoifCHyZq+EQlVcUHZ8=;
 b=IzzgjfpWyzaddzMjBrQz3bm+j/+kDgYhpHi/M9s4yyAgkRtMXdSHFexeAPhp7U9LJ7OR
 uepKuJ/5W/4HcG3qmV3vQf2HkRGKFnDT8JrKQPii/jQRUd6JA9sCMXDi9ALN2ZFRf8kY
 DXvSqtlgPz8dYPGyADZW6Cazc7WUoqKbsssjcY828Iz/DuEc29kiVJx4Rm0MU0StBUcE
 0ZDUwMZDXHIMAUOvV/0XcpnLIgfNir5mFcnBk7YR2Qr8LGPkSWb6EfuYtX/rWkrp8gB/
 I4hPzmqAW2SPNPWg5AZmaCqCldJmbjHzXDgnsuihT7dWjaOY4Lc9ldTg1Vc2W2uwZVVK 9w==
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=corp-2019-08-05;
 bh=wINA1FZ+1noeRFPFibnUIyc3AoifCHyZq+EQlVcUHZ8=;
 b=LC1SeT4Qmm5WSB4dzvOYT33gHZzmAKeykm9/CJCQnnhOb+OWm1mch51Yba7uECFK7t4r
 frCSQB2Tv9QlL+f6nNwEUHN+uBTvMxkWByTaDmI4KvPMVEPqveZVQ9H9x/tnEbuESICO
 C/bsv0a8oCMq41BSVejr0xOG+t+6apccX03p0qOPRQbOG8TNfO03W4vZwXpvlWEn4aki
 JSuBAEZ43bpkn02gU0JOHsZ3UmQogFB+EfkieoBrc0s0PE7UnIQCNbqPwDJ19jxaZ+j8
 ox2fNUV3oSKoysQx8wcKonBA1JmFu6PfkOD6uChjf1d7fOHrb6c+G0aHGIEM+UMxJ6Uy 4g==
Received: from userp3030.oracle.com (userp3030.oracle.com [156.151.31.80])
        by aserp2120.oracle.com with ESMTP id 2xykbp5ubr-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 05 Feb 2020 21:27:43 +0000
Received: from pps.filterd (userp3030.oracle.com [127.0.0.1])
        by userp3030.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 015LDYUw071742;
        Wed, 5 Feb 2020 21:27:42 GMT
Received: from aserv0122.oracle.com (aserv0122.oracle.com [141.146.126.236])
        by userp3030.oracle.com with ESMTP id 2xymutp80k-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 05 Feb 2020 21:27:42 +0000
Received: from abhmp0010.oracle.com (abhmp0010.oracle.com [141.146.116.16])
        by aserv0122.oracle.com (8.14.4/8.14.4) with ESMTP id 015LRebL006779;
        Wed, 5 Feb 2020 21:27:40 GMT
Received: from ban25x6uut29.us.oracle.com (/10.153.73.29)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Wed, 05 Feb 2020 13:27:40 -0800
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com
Subject: [PATCH] kvm-unit-test: nSVM: Restructure nSVM test code
Date: Wed,  5 Feb 2020 15:50:26 -0500
Message-Id: <20200205205026.16858-2-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20200205205026.16858-1-krish.sadhukhan@oracle.com>
References: <20200205205026.16858-1-krish.sadhukhan@oracle.com>
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9522
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=15
 malwarescore=0
 phishscore=0 bulkscore=0 spamscore=0 mlxscore=0 mlxlogscore=999
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.0.1-1911140001 definitions=main-2002050163
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9522
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 priorityscore=1501 malwarescore=0
 suspectscore=15 phishscore=0 bulkscore=0 spamscore=0 clxscore=1015
 lowpriorityscore=0 mlxscore=0 impostorscore=0 mlxlogscore=999 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.0.1-1911140001
 definitions=main-2002050163
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

..so that it matches its counterpart nVMX. This restructuring effort
  separates the test framework from the tests and puts them in different
  files.

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 x86/Makefile.x86_64 |    1 +
 x86/svm.c           | 1718 +++++++--------------------------------------------
 x86/svm.h           |   52 +-
 x86/svm_tests.c     | 1279 ++++++++++++++++++++++++++++++++++++++
 4 files changed, 1551 insertions(+), 1499 deletions(-)
 create mode 100644 x86/svm_tests.c

```
#### [kvm-unit-tests PATCH] Add Janosch as a s390x maintainer
##### From: Thomas Huth <thuth@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Huth <thuth@redhat.com>
X-Patchwork-Id: 11366029
Return-Path: <SRS0=nIH0=3Z=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A810F1820
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  5 Feb 2020 10:19:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7D99C2085B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  5 Feb 2020 10:19:47 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="RYykSmCW"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728238AbgBEKTq (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 5 Feb 2020 05:19:46 -0500
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:44901 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1727068AbgBEKTq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 5 Feb 2020 05:19:46 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1580897985;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc; bh=x7meg38MKtijGXRTHPEaSDs6h9nv3HE6yGYEcRdm//I=;
        b=RYykSmCWvzPFqs5h+Ono4uhkKoMjBzu/jM89AuIAy0sDG5lDbeNWrlvEoPgyi9tI+a1DUU
        rLX5OnbE/1l7Rw31sX5YnOWVNlxZGnSuHsR2fAveRUP3oXfFVuSQr+SLoklCzfk+w60tGx
        YrLtJQfeLEuwVZaf921N0EaBLH105LI=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-363-l8dsE0TiN5yLz9_gEWufbA-1; Wed, 05 Feb 2020 05:19:44 -0500
X-MC-Unique: l8dsE0TiN5yLz9_gEWufbA-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 4C12C1835A01;
        Wed,  5 Feb 2020 10:19:43 +0000 (UTC)
Received: from thuth.com (ovpn-116-132.ams2.redhat.com [10.36.116.132])
        by smtp.corp.redhat.com (Postfix) with ESMTP id E5A368DC09;
        Wed,  5 Feb 2020 10:19:38 +0000 (UTC)
From: Thomas Huth <thuth@redhat.com>
To: kvm@vger.kernel.org, David Hildenbrand <david@redhat.com>,
        Janosch Frank <frankja@linux.ibm.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Laurent Vivier <lvivier@redhat.com>,
        Drew Jones <drjones@redhat.com>
Subject: [kvm-unit-tests PATCH] Add Janosch as a s390x maintainer
Date: Wed,  5 Feb 2020 11:19:35 +0100
Message-Id: <20200205101935.19219-1-thuth@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Both, David and I, often do not have as much spare time for the
kvm-unit-tests as we would like to have, so we could use a little
bit of additional help here. Janosch did some excellent work for
the s390x kvm-unit-tests in the past months and is listed as reviewer
for these patches since quite a while already, so he's a very well
suited for the maintainer job here, too.

Signed-off-by: Thomas Huth <thuth@redhat.com>
Acked-by: David Hildenbrand <david@redhat.com>
Acked-by: Janosch Frank <frankja@de.ibm.com>
---
 MAINTAINERS | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH kvm-unit-tests] x86: provide enabled and disabled variation of the PCID test
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11366453
Return-Path: <SRS0=nIH0=3Z=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8F9A192A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  5 Feb 2020 15:29:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 6409B20702
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  5 Feb 2020 15:29:48 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="nEH7uJds"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726933AbgBEP3r (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 5 Feb 2020 10:29:47 -0500
Received: from mail-wr1-f54.google.com ([209.85.221.54]:35055 "EHLO
        mail-wr1-f54.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726592AbgBEP3r (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 5 Feb 2020 10:29:47 -0500
Received: by mail-wr1-f54.google.com with SMTP id w12so3269510wrt.2
        for <kvm@vger.kernel.org>; Wed, 05 Feb 2020 07:29:44 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id;
        bh=CdPJM86ZQ5sCp4YPhiWnGiejzLwA7DOCPC4pjKic284=;
        b=nEH7uJdsUOptDz6cDTzqswogbmPlecr1bvuUPiGcqAJVANrEvv67PGDs9FMtmWfZrY
         fyQE7binfcfObGf7kqaCZbWClmVBijUf60mezm7rirxrWbSotB62WFq8Vzvi/fm7uiFr
         pArhFHeujoL2i1QLl+EM28DoMXuByEmH7m8z8VLZGZWDnzl4hpdcEeZ9RhkVwqvnfkoM
         eky6Nf+pqtrVWaP9+a/U+mo2OphlQL9xBeNNxNMi3v+T3B/wA4LV4cuvnfv08/PGERwg
         rC/EiuOUU4QCcY8lk1n7jYhn4pgDyMK7NjefqG90hpMOMnENug+xWYtATjO2BuLJ6674
         /kaw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id;
        bh=CdPJM86ZQ5sCp4YPhiWnGiejzLwA7DOCPC4pjKic284=;
        b=UegxLzJb/mWpGyaXK8OQ1ZBthCaDorvgSYJcFtq+eUaJyZwLY7jvXcpQzG7G7FEkpl
         41hxBsOydJsoJF07OUWYocCq8t0d+x8bfiN9NH5vZJhnZGZIjYvZ1lUT4is7VjZ976fj
         0/5dE8yzF29hamDSr/sIMjqS+FPl8lD7GnMWV5SMZ3oMJA31Lld9damMgLb3/+zmHm8A
         +fR1Hvoz6KfOhDrrTaj48hA0KRe2hUu2TUu4d0r0HX6C/sVA1uvT2/VbBU7uGjiYDj5M
         MhDvuNys5wMq+rx6nzPOFiSgYHeWIptHN49M4vlho6M3Uzq/ba8TloKacWezH5AdEX/O
         vRew==
X-Gm-Message-State: APjAAAUSBId2y925dOuZcZgJGI3MgeGgw/0J4G3VmWkfL0E5tgz0dQ9R
        zIQwg+7oLCpUNBMnVJPcknMJLLPl
X-Google-Smtp-Source: 
 APXvYqx7jM3XG97FWHXNzQAX3am86LTdS8iKaJw5hkGK5NYYSiH6r/DdfmmvEfl7tErzxXi9oqb0bw==
X-Received: by 2002:adf:e446:: with SMTP id t6mr16275508wrm.222.1580916583678;
        Wed, 05 Feb 2020 07:29:43 -0800 (PST)
Received: from 640k.localdomain.com ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 p11sm215427wrn.40.2020.02.05.07.29.42
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Wed, 05 Feb 2020 07:29:42 -0800 (PST)
From: Paolo Bonzini <pbonzini@redhat.com>
To: kvm@vger.kernel.org
Cc: sean.j.christopherson@intel.com, vkuznets@redhat.com
Subject: [PATCH kvm-unit-tests] x86: provide enabled and disabled variation of
 the PCID test
Date: Wed,  5 Feb 2020 16:29:40 +0100
Message-Id: <1580916580-4098-1-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The PCID test checks for exceptions when PCID=0 or INVPCID=0 in
CPUID.  Cover that by adding a separate testcase with different
CPUID.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 x86/unittests.cfg | 7 ++++++-
 1 file changed, 6 insertions(+), 1 deletion(-)

```
#### [PATCH] KVM: vmx: delete meaningless vmx_decache_cr0_guest_bits() declaration
##### From: linmiaohe <linmiaohe@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: linmiaohe <linmiaohe@huawei.com>
X-Patchwork-Id: 11366455
Return-Path: <SRS0=nIH0=3Z=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9224A1395
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  5 Feb 2020 15:32:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 73C2E22464
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  5 Feb 2020 15:32:23 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726740AbgBEPcT (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 5 Feb 2020 10:32:19 -0500
Received: from szxga04-in.huawei.com ([45.249.212.190]:10154 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726416AbgBEPcT (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 5 Feb 2020 10:32:19 -0500
Received: from DGGEMS405-HUB.china.huawei.com (unknown [172.30.72.59])
        by Forcepoint Email with ESMTP id 43AB3AA846F77A695CEE;
        Wed,  5 Feb 2020 23:32:11 +0800 (CST)
Received: from huawei.com (10.175.105.18) by DGGEMS405-HUB.china.huawei.com
 (10.3.19.205) with Microsoft SMTP Server id 14.3.439.0; Wed, 5 Feb 2020
 23:32:04 +0800
From: linmiaohe <linmiaohe@huawei.com>
To: <pbonzini@redhat.com>, <rkrcmar@redhat.com>,
        <sean.j.christopherson@intel.com>, <vkuznets@redhat.com>,
        <wanpengli@tencent.com>, <jmattson@google.com>, <joro@8bytes.org>,
        <tglx@linutronix.de>, <mingo@redhat.com>, <bp@alien8.de>,
        <hpa@zytor.com>
CC: <linmiaohe@huawei.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <x86@kernel.org>
Subject: [PATCH] KVM: vmx: delete meaningless vmx_decache_cr0_guest_bits()
 declaration
Date: Wed, 5 Feb 2020 23:33:53 +0800
Message-ID: <1580916833-28905-1-git-send-email-linmiaohe@huawei.com>
X-Mailer: git-send-email 1.8.3.1
MIME-Version: 1.0
X-Originating-IP: [10.175.105.18]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Miaohe Lin <linmiaohe@huawei.com>

The function vmx_decache_cr0_guest_bits() is only called below its
implementation. So this is meaningless and should be removed.

Signed-off-by: Miaohe Lin <linmiaohe@huawei.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/vmx/vmx.c | 2 --
 1 file changed, 2 deletions(-)

```
#### [PATCH 1/3] x86/kvm/hyper-v: remove stale evmcs_already_enabled check from nested_enable_evmcs()
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11366229
Return-Path: <SRS0=nIH0=3Z=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6CDAA921
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  5 Feb 2020 12:30:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4BD95217BA
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  5 Feb 2020 12:30:43 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="UhMSQxZB"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727109AbgBEMam (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 5 Feb 2020 07:30:42 -0500
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:48960 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1727104AbgBEMam (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 5 Feb 2020 07:30:42 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1580905841;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=FHRLTiRDFk91fNbjqjjK4sS7PVxxMVDiLVR/Xqc6yrU=;
        b=UhMSQxZBTr4ZDU1KXea5GiQYdiZTJ5e236pRR6HEuH04ydIouBi5HFyoZrga6IJHecYk0U
        NgZEWaDUBldwiDLnS/5qxhKuI3Y7SfF5c1MDx4NtQQ+p92Eygn+dUQ6UuEXW9LohjHwqek
        WhruqKDJnSoNjMStdpJuVTRxzU9jat8=
Received: from mail-wr1-f72.google.com (mail-wr1-f72.google.com
 [209.85.221.72]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-292-7t-6ssc6M8qd8GTTwJr-qQ-1; Wed, 05 Feb 2020 07:30:39 -0500
X-MC-Unique: 7t-6ssc6M8qd8GTTwJr-qQ-1
Received: by mail-wr1-f72.google.com with SMTP id 50so1126652wrc.2
        for <kvm@vger.kernel.org>; Wed, 05 Feb 2020 04:30:39 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=FHRLTiRDFk91fNbjqjjK4sS7PVxxMVDiLVR/Xqc6yrU=;
        b=KULmGoz3EaBGS3UXLnLiLESgXQ1q9t9toty8rd3Juwmi1qEkOrdZE1wIecITBx5/dB
         8f2//v3SedvrUSfxXrln+bKdQKLcoQydu8VcqOdlrXSDlqtTAVeNUM+Tn8+haXg0RaC9
         jeaNbV+uGOYIAbBoxRgEP6FlD3f2WmHxo9m7gRO5pca44vs79PMWoS7C1dKsmoakwVG7
         +ofRnT8jZMsD1wamurIYNfGf3aEXxmCGlP58BuB/dRvyicX6kHoMWaw0o4SdiV0nCwr7
         rTS1Z63ZD+zFUanuC4ZXi7Mdn4YlWnZWCtSoY6K1yHUiF2Cx/jL/4J3/zCMWV7zKtevf
         Fb/Q==
X-Gm-Message-State: APjAAAVXZdfNxDahierXiwSuXTGCl7molhbcLG+R2DVN0GzgMOF5aXH7
        2jvAjXDyp2zVuO9XIne+BevKoZKkoIYtPgZzCaLnHfWlPDPO/Yw7B088WdW5FV3tRiUc8R8vAJI
        KdiIgTf9cKL2F
X-Received: by 2002:a5d:5263:: with SMTP id l3mr27754227wrc.405.1580905838387;
        Wed, 05 Feb 2020 04:30:38 -0800 (PST)
X-Google-Smtp-Source: 
 APXvYqwxd5Bz9WYMUVNFZyA/vAWEUrG6f9LLsByb0bUcfyGjRUNIQyI+6xv9t7EQ2SbgTUNWO2yOMw==
X-Received: by 2002:a5d:5263:: with SMTP id l3mr27754211wrc.405.1580905838179;
        Wed, 05 Feb 2020 04:30:38 -0800 (PST)
Received: from vitty.brq.redhat.com (nat-pool-brq-t.redhat.com.
 [213.175.37.10])
        by smtp.gmail.com with ESMTPSA id
 g7sm34227251wrq.21.2020.02.05.04.30.36
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 05 Feb 2020 04:30:37 -0800 (PST)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Jim Mattson <jmattson@google.com>,
        linux-kernel@vger.kernel.org, Liran Alon <liran.alon@oracle.com>,
        Roman Kagan <rkagan@virtuozzo.com>
Subject: [PATCH 1/3] x86/kvm/hyper-v: remove stale evmcs_already_enabled check
 from nested_enable_evmcs()
Date: Wed,  5 Feb 2020 13:30:32 +0100
Message-Id: <20200205123034.630229-2-vkuznets@redhat.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20200205123034.630229-1-vkuznets@redhat.com>
References: <20200205123034.630229-1-vkuznets@redhat.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In nested_enable_evmcs() evmcs_already_enabled check doesn't really do
anything: controls are already sanitized and we return '0' regardless.
Just drop the check.

Reviewed-by: Liran Alon <liran.alon@oracle.com>
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/vmx/evmcs.c | 5 -----
 1 file changed, 5 deletions(-)

```
