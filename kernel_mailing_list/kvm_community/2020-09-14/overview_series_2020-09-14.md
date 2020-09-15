#### [PATCH 1/2] KVM: Fix the build error
##### From: lihaiwei.kernel@gmail.com

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Haiwei Li <lihaiwei.kernel@gmail.com>
X-Patchwork-Id: 11773373
Return-Path: <SRS0=+Hxv=CX=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 77B1E92C
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 14 Sep 2020 09:12:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4DE7221D24
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 14 Sep 2020 09:12:07 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="Uurm7Jd4"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726244AbgINJMG (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 14 Sep 2020 05:12:06 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:45008 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726198AbgINJMC (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 14 Sep 2020 05:12:02 -0400
Received: from mail-pg1-x542.google.com (mail-pg1-x542.google.com
 [IPv6:2607:f8b0:4864:20::542])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 6066CC061788;
        Mon, 14 Sep 2020 02:12:02 -0700 (PDT)
Received: by mail-pg1-x542.google.com with SMTP id t14so11007339pgl.10;
        Mon, 14 Sep 2020 02:12:02 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=ypxASSpGv9RIPFq+dUkv+nkukyOjiOQi2ZMQ5W1mvNk=;
        b=Uurm7Jd47CcO0M+kkGP0tmTl8T9VQR/tQQa1rDxBBvHy82vEyY3rqxEpnFLxSMnvQu
         7qIlSd/7ctImd9YmtQB6m0XJNOXZLgEwArVoGLDNdExMuF2NEg5FOKL/nTN7KJ2DUNGv
         31rcOaRlSzCsJnm+alV9aFYc/AQYkdyMcgXlt3Val9V+3ma/PrdvlWkgjDcTTBALLV13
         lj9vFFAQ/vXNu6cbNmHj/KmfzHhm97h0a450AG9A5aZQLNVuWmdSJVbreQtBnpZmbfm8
         kCub3VTlDnnnnYewjCJC7bpie/qfBs+OBTXzX8BazvkK+R4DmBlISUS+l4/nFw/khP9R
         tJ1Q==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=ypxASSpGv9RIPFq+dUkv+nkukyOjiOQi2ZMQ5W1mvNk=;
        b=nAuhy+t+1rIRw6qKoKQKdqilYtrpr2S3FQWL7rkIwtdpWGFyrqvGknDWCa0VXABHWx
         FAs6cJ43aa+SRCm9LwLsIDmpCbaVKz73rwkGFKDtTXhNpa+zn6kVzrYaXATnVuEIOvLE
         aDV4F3kSswksPm9MaTsGA7ItPJrXpDLtdgioD7RhFeLUDdXgnnAXC6rZwsVHZKgGuukZ
         1pFmucepwbjXlat4meOceXyKZZGVnHRhpd3JWiTAxxNGWSNqewmsH7XlB4sIDHL7KgZS
         qVwiYCoIc5JGvX8tI+kAjp9885OnfiMFsR0jOHch8CRsuuEiJwuO4bu9mzSaMyZwC1SN
         Ianw==
X-Gm-Message-State: AOAM532xADwSizGpNw3AV7VgDTYYZvb4nx/3MajjAHveO2Wxlgs+Z+sO
        ck7UkP3jfq4l0N1Zb4MVDP2/RQk47rhc
X-Google-Smtp-Source: 
 ABdhPJw3LSalbk6bdlfVzuY79OzxpwkR1KzT5aX3N76A2GkC//bQUISzqr0TMsDOQCG67FaFcx8a9w==
X-Received: by 2002:a17:902:8c89:: with SMTP id
 t9mr13290222plo.66.1600074721684;
        Mon, 14 Sep 2020 02:12:01 -0700 (PDT)
Received: from LiHaiwei.tencent.com ([203.205.141.65])
        by smtp.gmail.com with ESMTPSA id
 m13sm8765179pjl.45.2020.09.14.02.11.57
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Mon, 14 Sep 2020 02:12:00 -0700 (PDT)
From: lihaiwei.kernel@gmail.com
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org, x86@kernel.org
Cc: pbonzini@redhat.com, sean.j.christopherson@intel.com,
        vkuznets@redhat.com, wanpengli@tencent.com, jmattson@google.com,
        joro@8bytes.org, tglx@linutronix.de, mingo@redhat.com,
        bp@alien8.de, hpa@zytor.com, lihaiwei@tencent.com,
        kernel test robot <lkp@intel.com>
Subject: [PATCH 1/2] KVM: Fix the build error
Date: Mon, 14 Sep 2020 17:11:47 +0800
Message-Id: <20200914091148.95654-2-lihaiwei.kernel@gmail.com>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20200914091148.95654-1-lihaiwei.kernel@gmail.com>
References: <20200914091148.95654-1-lihaiwei.kernel@gmail.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Haiwei Li <lihaiwei@tencent.com>

When CONFIG_SMP is not set, an build error occurs with message "error:
use of undeclared identifier 'kvm_send_ipi_mask_allbutself'"

Fixes: 0f990222108d ("KVM: Check the allocation of pv cpu mask", 2020-09-01)
Reported-by: kernel test robot <lkp@intel.com>
Signed-off-by: Haiwei Li <lihaiwei@tencent.com>
---
 arch/x86/kernel/kvm.c | 2 ++
 1 file changed, 2 insertions(+)

```
#### [GIT PULL 1/1] docs: kvm: add documentation for KVM_CAP_S390_DIAG318
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11773247
Return-Path: <SRS0=+Hxv=CX=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1B184746
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 14 Sep 2020 08:22:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E7926221F0
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 14 Sep 2020 08:22:26 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="BynVaRT1"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726232AbgINIW0 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 14 Sep 2020 04:22:26 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:14916 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726139AbgINIWX (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 14 Sep 2020 04:22:23 -0400
Received: from pps.filterd (m0098396.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 08E82Lr9168862;
        Mon, 14 Sep 2020 04:22:22 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : content-transfer-encoding
 : mime-version; s=pp1; bh=i+OwX1kg/u3h4oRJPcu0H6VxX72SaJLtZbABQK7m36w=;
 b=BynVaRT1h4Cd3qcVDL9O7Rz81Qq5WHQSyFcfsDxeC3rCHj2dYIbWkLyt/Pg/PUGj5LHK
 vVult16AmkS0szCRuc+l7dar7ejfko9hfqNSzvZZTWdmLiXUiZMu2zQii2Tt/NHY7Hdh
 /cogDdb7aEU4nBWkzGq9ufLqYFBiQ5zCFKexOIE2JL09c+9a5EU9QUQrthGqYCckwP/W
 qRuonKmcgt9tAgUMOhdKeC0Ni9VMvZaT/x3Cny52//UkSggEi2RWsDp6CQZipKIsOm85
 A8vsYt2ybNm+5tee/99JqXjB4K6OsrqnqMMmfaLTd2A61SSBAFaWkW5iS36u6yHvdYE7 3g==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 33j4g4rvbf-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 14 Sep 2020 04:22:22 -0400
Received: from m0098396.ppops.net (m0098396.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 08E82uiK171395;
        Mon, 14 Sep 2020 04:22:22 -0400
Received: from ppma01fra.de.ibm.com (46.49.7a9f.ip4.static.sl-reverse.com
 [159.122.73.70])
        by mx0a-001b2d01.pphosted.com with ESMTP id 33j4g4rvas-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 14 Sep 2020 04:22:22 -0400
Received: from pps.filterd (ppma01fra.de.ibm.com [127.0.0.1])
        by ppma01fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 08E8KvgW028114;
        Mon, 14 Sep 2020 08:22:20 GMT
Received: from b06cxnps4074.portsmouth.uk.ibm.com
 (d06relay11.portsmouth.uk.ibm.com [9.149.109.196])
        by ppma01fra.de.ibm.com with ESMTP id 33hkfagcfp-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 14 Sep 2020 08:22:19 +0000
Received: from d06av22.portsmouth.uk.ibm.com (d06av22.portsmouth.uk.ibm.com
 [9.149.105.58])
        by b06cxnps4074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 08E8MHXu20840938
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 14 Sep 2020 08:22:17 GMT
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id E92A84C046;
        Mon, 14 Sep 2020 08:22:16 +0000 (GMT)
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id D5F484C040;
        Mon, 14 Sep 2020 08:22:16 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av22.portsmouth.uk.ibm.com (Postfix) with ESMTPS;
        Mon, 14 Sep 2020 08:22:16 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 25651)
        id 969DCE235D; Mon, 14 Sep 2020 10:22:16 +0200 (CEST)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: KVM <kvm@vger.kernel.org>, Janosch Frank <frankja@linux.ibm.com>,
        David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        linux-s390 <linux-s390@vger.kernel.org>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Claudio Imbrenda <imbrenda@linux.ibm.com>,
        Collin Walling <walling@linux.ibm.com>
Subject: [GIT PULL 1/1] docs: kvm: add documentation for KVM_CAP_S390_DIAG318
Date: Mon, 14 Sep 2020 10:22:15 +0200
Message-Id: <20200914082215.6143-2-borntraeger@de.ibm.com>
X-Mailer: git-send-email 2.25.4
In-Reply-To: <20200914082215.6143-1-borntraeger@de.ibm.com>
References: <20200914082215.6143-1-borntraeger@de.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-UnRewURL: 0 URL was un-rewritten
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-09-13_09:2020-09-10,2020-09-13 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 bulkscore=0 phishscore=0
 lowpriorityscore=0 malwarescore=0 clxscore=1015 priorityscore=1501
 mlxlogscore=999 mlxscore=0 suspectscore=0 spamscore=0 impostorscore=0
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2009140062
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Collin Walling <walling@linux.ibm.com>

Documentation for the s390 DIAGNOSE 0x318 instruction handling.

Signed-off-by: Collin Walling <walling@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Link: https://lore.kernel.org/kvm/20200625150724.10021-2-walling@linux.ibm.com/
Message-Id: <20200625150724.10021-2-walling@linux.ibm.com>
Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 Documentation/virt/kvm/api.rst | 20 ++++++++++++++++++++
 1 file changed, 20 insertions(+)

```
#### [PATCH] KVM: SVM: Analyze is_guest_mode() in svm_vcpu_run()
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11772979
Return-Path: <SRS0=+Hxv=CX=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 02E80618
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 14 Sep 2020 06:56:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DB09C207EA
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 14 Sep 2020 06:56:07 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="iTmA1RwG"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726073AbgING4E (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 14 Sep 2020 02:56:04 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:52288 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726039AbgING4D (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 14 Sep 2020 02:56:03 -0400
Received: from mail-pf1-x442.google.com (mail-pf1-x442.google.com
 [IPv6:2607:f8b0:4864:20::442])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id D8495C06174A;
        Sun, 13 Sep 2020 23:56:02 -0700 (PDT)
Received: by mail-pf1-x442.google.com with SMTP id v196so11928673pfc.1;
        Sun, 13 Sep 2020 23:56:02 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=SNAtT/7LYD5SCZCVb8HK7FrqwZpKd7aSBFmTnXlZfF8=;
        b=iTmA1RwGEKhqrwJIhpyQHf2zlosnkt2ZbfSnljTQECHiuIqQ7d6/lvqMHbReo3CkbW
         TNkM1CfV2IW1w1FvbZyWY6JZRDMZCLLPDB6k5c9bFHX+b72qcDMYua1fyqUrSRCspe91
         S94VF8dRaozBaJjBkuQesHS4TWOsoWmAwy4gcAGGRDqf2rFXy8MLSbQ5D9CuDt76IG9C
         7/yIBAUdRry/F6nLZeQZUkz0Z/I4fauXOmomXLQY4N1Ep2xjiglEDIpBSVxIFetJryb6
         Plt1dJ7WrXIjbPk3nqLEmA2ShZ9zwGuSZwNmOleHBC63/6EHi9j/UFCRR2Wv+OKosLcl
         lpLg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=SNAtT/7LYD5SCZCVb8HK7FrqwZpKd7aSBFmTnXlZfF8=;
        b=qdnIdL6hm7OUAZnYI7iA2NKLzfEfVqFIXjoUVGt6vfE3Uy65iBcUcLijkvS+sgiTAn
         dL+J2X9ResSJ6EvvPdA9JrbFx2YHnMY5ojI8VdHtjm/HIkvzJUFYYtBTwvV0cEOQW9rU
         +hhLEOz+KCfkskC4W5E1zlsd4OyfYvwiIsoKopqNGnPrZgUlLsjTfK+XjyO5+RwZzvxR
         Qe/miEaRFM4ROAtv2ybN6+DK+q7mpl80BUCgsvaw04yglerylTXJ/LC7gH0CdyWGYAp4
         2tl3rtDivgjOzZmzydEiStDiwonNmQvVa8wKvgBWWyDoxKXqh9dZFvZED23T7r8yR3FL
         c5LQ==
X-Gm-Message-State: AOAM532yDL6kbHEMXCjO3LmOeHUAScmpK94i/XkljtqlXnRSR3fmSbcN
        fn3W1MC9fdmKjrA8el6jUT998bIn4qM=
X-Google-Smtp-Source: 
 ABdhPJxgIfKdBiY8KoK5z/OxRVNQcszhxv0ghYoIp/yRS4i8N7G3nOOysCt95Pf1by6Sfe6OweJhTw==
X-Received: by 2002:aa7:9f99:0:b029:13e:d13d:a134 with SMTP id
 z25-20020aa79f990000b029013ed13da134mr12287868pfr.28.1600066562216;
        Sun, 13 Sep 2020 23:56:02 -0700 (PDT)
Received: from localhost.localdomain ([103.7.29.6])
        by smtp.googlemail.com with ESMTPSA id
 p29sm7245400pgl.34.2020.09.13.23.55.59
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Sun, 13 Sep 2020 23:56:01 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>
Subject: [PATCH] KVM: SVM: Analyze is_guest_mode() in svm_vcpu_run()
Date: Mon, 14 Sep 2020 14:55:48 +0800
Message-Id: <1600066548-4343-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

Analyze is_guest_mode() in svm_vcpu_run() instead of svm_exit_handlers_fastpath()
in conformity with VMX version.

Suggested-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kvm/svm/svm.c | 7 +++++--
 1 file changed, 5 insertions(+), 2 deletions(-)

```
