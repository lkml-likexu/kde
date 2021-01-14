#### [PATCH 1/3] KVM: nSVM: Check addresses of MSR and IO bitmap
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 12015645
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-19.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	UNPARSEABLE_RELAY,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id F3029C433DB
	for <kvm@archiver.kernel.org>; Wed, 13 Jan 2021 02:47:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BE54F207C8
	for <kvm@archiver.kernel.org>; Wed, 13 Jan 2021 02:47:28 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728282AbhAMCr1 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 12 Jan 2021 21:47:27 -0500
Received: from aserp2130.oracle.com ([141.146.126.79]:42942 "EHLO
        aserp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726724AbhAMCr1 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 12 Jan 2021 21:47:27 -0500
Received: from pps.filterd (aserp2130.oracle.com [127.0.0.1])
        by aserp2130.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 10D2isTC069864;
        Wed, 13 Jan 2021 02:46:43 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=corp-2020-01-29;
 bh=BvKQ+4rje6Vv4d5nG5NeVQcTFzmuWKNZ/3wRAXhWw2M=;
 b=EzH7esSvbtvT0+QGm+ga3TzUIFbxdcUfBxXfi69LFXBuCqviu756T6D+smFmaL1etCJn
 Aww+GB3qf2FzsZLRJxYxJqjbh0bqm68K720y7ZDk5xri/jq9Sy6Blf7jRkIRkmYs5mKu
 GzhvQ0JWii7bxAKCOI55uk2M4WPVRbPVZzS1zXP0PAVx9bvIBUEnhdaq7SsPoudsqc7/
 8l8Vo3AL56tgMtzq9CcRPhop02HGKTAxvrvux0fHYqeUkxRbmYdtAuugL82AXE8Eeib2
 IlYZsGYHT7wRSTbtxF9tDX1qv/bKzJFfyKIHnPdJSix+acSt5UmZnOAk2Z+9qgAYLY7S uw==
Received: from userp3020.oracle.com (userp3020.oracle.com [156.151.31.79])
        by aserp2130.oracle.com with ESMTP id 360kg1sb89-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 13 Jan 2021 02:46:43 +0000
Received: from pps.filterd (userp3020.oracle.com [127.0.0.1])
        by userp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 10D2kTdn051239;
        Wed, 13 Jan 2021 02:46:42 GMT
Received: from aserv0121.oracle.com (aserv0121.oracle.com [141.146.126.235])
        by userp3020.oracle.com with ESMTP id 360kf6mnn1-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 13 Jan 2021 02:46:42 +0000
Received: from abhmp0002.oracle.com (abhmp0002.oracle.com [141.146.116.8])
        by aserv0121.oracle.com (8.14.4/8.13.8) with ESMTP id 10D2kfEN012996;
        Wed, 13 Jan 2021 02:46:41 GMT
Received: from nsvm-sadhukhan.osdevelopmeniad.oraclevcn.com (/100.100.230.216)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Tue, 12 Jan 2021 18:46:41 -0800
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com, seanjc@google.com
Subject: [PATCH 1/3] KVM: nSVM: Check addresses of MSR and IO bitmap
Date: Wed, 13 Jan 2021 02:46:31 +0000
Message-Id: <20210113024633.8488-2-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.27.0
In-Reply-To: <20210113024633.8488-1-krish.sadhukhan@oracle.com>
References: <20210113024633.8488-1-krish.sadhukhan@oracle.com>
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9862
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=0
 malwarescore=0
 mlxlogscore=999 phishscore=0 bulkscore=0 spamscore=0 mlxscore=0
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2101130014
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9862
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 malwarescore=0
 suspectscore=0
 clxscore=1015 impostorscore=0 spamscore=0 priorityscore=1501 mlxscore=0
 phishscore=0 mlxlogscore=999 bulkscore=0 adultscore=0 lowpriorityscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2101130014
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

According to section "Canonicalization and Consistency Checks" in APM vol 2,
the following guest state is illegal:

    "The MSR or IOIO intercept tables extend to a physical address that
     is greater than or equal to the maximum supported physical address."

Also check that these addresses are aligned on page boundary.

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 arch/x86/kvm/svm/nested.c | 17 ++++++++++++++---
 1 file changed, 14 insertions(+), 3 deletions(-)

```
#### [PATCH 01/14] s390/mm: Code cleanups
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 12016297
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 93546C433E6
	for <kvm@archiver.kernel.org>; Wed, 13 Jan 2021 09:42:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4B22F233F8
	for <kvm@archiver.kernel.org>; Wed, 13 Jan 2021 09:42:41 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727389AbhAMJmY (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 13 Jan 2021 04:42:24 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:11380 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727345AbhAMJmW (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 13 Jan 2021 04:42:22 -0500
Received: from pps.filterd (m0187473.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 10D9XPpQ007838;
        Wed, 13 Jan 2021 04:41:41 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=OpoE8Y6bxTLR0nmKeCcXbkDvdT59x8h7/q2maMOCtC0=;
 b=IOFafx5V2oYaNd+lXH2BOJyekgSfMRDxAVB1VJ7R7qp5lp6xmm92Gp6yg+8bHDueXmuc
 iIEo9YzAdKhIfQbydwAtuLytiKR0bql4/OhM84Uvwn4lrr6M1WZez/x1HEdB3K+set1V
 V2bR0Nydb3t8ftUkwVU4D0NaW5ib+EHQPotu9Eaheu+GPMIJpPy6+capKz4yx/Ry5IiQ
 HdF+HPlPmmxJqID6WChWwnoZ5T6K/+K3IJEO4aZOVTeAeH9QNez7af2V5PldS7YF8/O0
 s7iux0nyZpNGNIFY2JyZCj+mEt2zfuoiqm8JRxRWN9TNFFidEHnFzHmv35+tmVYrPmjM Sw==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 361wdnsk1a-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 13 Jan 2021 04:41:41 -0500
Received: from m0187473.ppops.net (m0187473.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 10D9XRs1007869;
        Wed, 13 Jan 2021 04:41:40 -0500
Received: from ppma03ams.nl.ibm.com (62.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.98])
        by mx0a-001b2d01.pphosted.com with ESMTP id 361wdnsk0h-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 13 Jan 2021 04:41:40 -0500
Received: from pps.filterd (ppma03ams.nl.ibm.com [127.0.0.1])
        by ppma03ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 10D9QxQ9019232;
        Wed, 13 Jan 2021 09:41:38 GMT
Received: from b06cxnps4076.portsmouth.uk.ibm.com
 (d06relay13.portsmouth.uk.ibm.com [9.149.109.198])
        by ppma03ams.nl.ibm.com with ESMTP id 35y447vucb-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 13 Jan 2021 09:41:38 +0000
Received: from d06av23.portsmouth.uk.ibm.com (d06av23.portsmouth.uk.ibm.com
 [9.149.105.59])
        by b06cxnps4076.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 10D9fZqB31654146
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 13 Jan 2021 09:41:35 GMT
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 8E924A4040;
        Wed, 13 Jan 2021 09:41:35 +0000 (GMT)
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 5AF0BA4053;
        Wed, 13 Jan 2021 09:41:35 +0000 (GMT)
Received: from t46lp67.lnxne.boe (unknown [9.152.108.100])
        by d06av23.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Wed, 13 Jan 2021 09:41:35 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: borntraeger@de.ibm.com, david@redhat.com,
        linux-s390@vger.kernel.org, imbrenda@linux.ibm.com
Subject: [PATCH 01/14] s390/mm: Code cleanups
Date: Wed, 13 Jan 2021 09:41:00 +0000
Message-Id: <20210113094113.133668-2-frankja@linux.ibm.com>
X-Mailer: git-send-email 2.27.0
In-Reply-To: <20210113094113.133668-1-frankja@linux.ibm.com>
References: <20210113094113.133668-1-frankja@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.343,18.0.737
 definitions=2021-01-13_03:2021-01-13,2021-01-13 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 bulkscore=0 impostorscore=0
 adultscore=0 malwarescore=0 phishscore=0 clxscore=1015 priorityscore=1501
 spamscore=0 suspectscore=0 mlxlogscore=999 mlxscore=0 lowpriorityscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2101130056
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Let's clean up leftovers before introducing new code.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Acked-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 arch/s390/mm/gmap.c    | 8 ++++----
 arch/s390/mm/pgtable.c | 2 +-
 2 files changed, 5 insertions(+), 5 deletions(-)

```
#### [PATCH v2 1/2] KVM: nSVM: Track the physical cpu of the vmcb vmrun through the vmcb
##### From: Cathy Avery <cavery@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Cathy Avery <cavery@redhat.com>
X-Patchwork-Id: 12016881
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B6458C433DB
	for <kvm@archiver.kernel.org>; Wed, 13 Jan 2021 14:12:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7002D23382
	for <kvm@archiver.kernel.org>; Wed, 13 Jan 2021 14:12:25 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726631AbhAMOMI (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 13 Jan 2021 09:12:08 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:31283 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726456AbhAMOMI (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 13 Jan 2021 09:12:08 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1610547041;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=bJJPeCzPrT/sxj0yTskmiKmd9WxFd0iQ25eQQC8YKrI=;
        b=QZB/3+19iYvLP5dhO63w2Nj8R+TXeAcg/btI4Zt/+BXHN/KZyEssNmrPl9OKS7Nc8qQQF5
        vGL03abn3n3MRBX4yhoUc9JBfcDTYz0MOHlrbA65rJD3ud33CHTo79/0tWggxP2adhfab2
        WbfcbYCHv9ICtigVGWJ3JvAcVtGsZx4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-174-RiIOz881Myyh66FrWGwwaA-1; Wed, 13 Jan 2021 09:10:39 -0500
X-MC-Unique: RiIOz881Myyh66FrWGwwaA-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 270CD835BA7;
        Wed, 13 Jan 2021 14:10:21 +0000 (UTC)
Received: from virtlab710.virt.lab.eng.bos.redhat.com
 (virtlab710.virt.lab.eng.bos.redhat.com [10.19.152.252])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 84EE660BF1;
        Wed, 13 Jan 2021 14:10:20 +0000 (UTC)
From: Cathy Avery <cavery@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        pbonzini@redhat.com
Cc: vkuznets@redhat.com, wei.huang2@amd.com
Subject: [PATCH v2 1/2] KVM: nSVM: Track the physical cpu of the vmcb vmrun
 through the vmcb
Date: Wed, 13 Jan 2021 09:10:18 -0500
Message-Id: <20210113141019.5127-2-cavery@redhat.com>
In-Reply-To: <20210113141019.5127-1-cavery@redhat.com>
References: <20210113141019.5127-1-cavery@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch moves the physical cpu tracking from the vcpu
to the vmcb in svm_switch_vmcb. If either vmcb01 or vmcb02
change physical cpus from one vmrun to the next the vmcb's
previous cpu is preserved for comparison with the current
cpu and the vmcb is marked dirty if different. This prevents
the processor from using old cached data for a vmcb that may
have been updated on a prior run on a different processor.

It also moves the physical cpu check from svm_vcpu_load
to pre_svm_run as the check only needs to be done at run.

Suggested-by: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Cathy Avery <cavery@redhat.com>
---
 arch/x86/kvm/svm/svm.c | 23 +++++++++++++++--------
 arch/x86/kvm/svm/svm.h |  1 +
 2 files changed, 16 insertions(+), 8 deletions(-)

```
#### [PATCH] KVM: x86: Add more protection against undefined behavior in rsvd_bits()
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12017819
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=unavailable autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 17A2CC433DB
	for <kvm@archiver.kernel.org>; Wed, 13 Jan 2021 20:46:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DE7F12310A
	for <kvm@archiver.kernel.org>; Wed, 13 Jan 2021 20:46:16 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728923AbhAMUqA (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 13 Jan 2021 15:46:00 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:33994 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727554AbhAMUqA (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 13 Jan 2021 15:46:00 -0500
Received: from mail-qt1-x849.google.com (mail-qt1-x849.google.com
 [IPv6:2607:f8b0:4864:20::849])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 9D6CCC061575
        for <kvm@vger.kernel.org>; Wed, 13 Jan 2021 12:45:19 -0800 (PST)
Received: by mail-qt1-x849.google.com with SMTP id t7so2430591qtn.19
        for <kvm@vger.kernel.org>; Wed, 13 Jan 2021 12:45:19 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=dWjn342r4gchACatmFqBw1A1idiYczd8S0EYhHJ6cqk=;
        b=LXS3/ITVuk/SnWCJkR/nTg4MXjPt/brCtDBIjSa268qeWXDMMq0bw98grRjb4gSo/D
         Yr7m+C/5PGKWXusNkHcPVMhYTPJ2sVbVQxHIIrTd+Z8qhkUxwX4bVXE9fUD99RjF3+0N
         wAkNVxSfRvaLMPlhGjhgL56WC+aE1m05Sx4eY9rCgPnxa0ugufDJcyRmcnuxX0uU+nSh
         wCUVhh/upnrdv9BKmMtFxVLOBjtgz8R1wyGZv/+vk0lP5qNjhPV0PkyJFrM//U25ik6o
         yORifaOQzbA2M4IcWMXJ9SI7lewXs0MqLMamPwpIiHKY1F8/hf1Jswt0LkM/KOk5qu7t
         nkRA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:reply-to:date:message-id:mime-version
         :subject:from:to:cc;
        bh=dWjn342r4gchACatmFqBw1A1idiYczd8S0EYhHJ6cqk=;
        b=KY5c6NzRyP9PqHybdl2+kycffNnzgB9eXagLaL2OsS/V1HFf8MY0kQQ9qweJhGYLL1
         lk9NiTT7gGLcuhUryW2MgaR08DSpt31mPQQE8PcHMj8rxVCSZggwX/zhy8zqtDH+NfkI
         4gW97OtbwqHn2YI9TuqQLWYc6N5D3sem54Fw0v3HGi3dkzvDuIPlmks+WikXaWCaFNta
         gW2dzrCMnHqZhum1cJBwDgwK5RcM8U1Ipbb7rz352LSe/PSy0sYUVffqJiOFOZx1/ncA
         YQf7McS51zqHJFbw/JajiBmdLGWY+j4eLfwxCZ3xmowki9idbFFvLS2SvhvaZj0uTwxz
         7xUQ==
X-Gm-Message-State: AOAM5323xQT9eYHpAV9XMAFy1XUcbf3em7cbpuAcRVHFCRo4mIJL+sTD
        jzf5xqN0FOq3I8Tewf6HrjhWqwGFS58=
X-Google-Smtp-Source: 
 ABdhPJyF7RbfCRZcwkggVCSN3NJKobLj0tCZ/19NtoaDlqZFS8agG3ajSJPtaiX0BegIC2cNmKIQYvYUP10=
Sender: "seanjc via sendgmr" <seanjc@seanjc798194.pdx.corp.google.com>
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:1ea0:b8ff:fe73:50f5])
 (user=seanjc job=sendgmr) by 2002:a25:ca4f:: with SMTP id
 a76mr6085531ybg.140.1610570718745;
 Wed, 13 Jan 2021 12:45:18 -0800 (PST)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Wed, 13 Jan 2021 12:45:15 -0800
Message-Id: <20210113204515.3473079-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.30.0.284.gd98b1dd5eaa7-goog
Subject: [PATCH] KVM: x86: Add more protection against undefined behavior in
 rsvd_bits()
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add compile-time asserts in rsvd_bits() to guard against KVM passing in
garbage hardcoded values, and cap the upper bound at '63' for dynamic
values to prevent generating a mask that would overflow a u64.

Suggested-by: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Sean Christopherson <seanjc@google.com>
---
 arch/x86/kvm/mmu.h | 9 ++++++++-
 1 file changed, 8 insertions(+), 1 deletion(-)

```
#### [PATCH 1/7] selftests: kvm: Move kvm_get_supported_hv_cpuid() to common code
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 12016919
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 6E725C433E6
	for <kvm@archiver.kernel.org>; Wed, 13 Jan 2021 14:38:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2AB692343B
	for <kvm@archiver.kernel.org>; Wed, 13 Jan 2021 14:38:58 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726426AbhAMOi5 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 13 Jan 2021 09:38:57 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:38891 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1725771AbhAMOi4 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 13 Jan 2021 09:38:56 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1610548649;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=5zMyeAIJV4DWJz8SQHo1S/srnhlPuLS/oU/oJkunMYQ=;
        b=LyeaCS9WE3s98pQj2TXMgElE6RK52m4Zx09vm29Wq1CGk1wpULFYBx1bRMq9MTQBhWI6/X
        0Sy864bmnenwR7fEKbBQKAw2lM9xGeZGt7iHivABHehZHJQXZausJAKSJF/2NO5HrUFYTP
        cVLc78xKXJ5VuY2mi2m+afUtYh8PRFc=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-322-EHc_DoUMMDqgSPN9Vn4L0Q-1; Wed, 13 Jan 2021 09:37:28 -0500
X-MC-Unique: EHc_DoUMMDqgSPN9Vn4L0Q-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id C3E6D80A5C0;
        Wed, 13 Jan 2021 14:37:26 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.193.20])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 2AAFE5C3E0;
        Wed, 13 Jan 2021 14:37:24 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>
Subject: [PATCH 1/7] selftests: kvm: Move kvm_get_supported_hv_cpuid() to
 common code
Date: Wed, 13 Jan 2021 15:37:15 +0100
Message-Id: <20210113143721.328594-2-vkuznets@redhat.com>
In-Reply-To: <20210113143721.328594-1-vkuznets@redhat.com>
References: <20210113143721.328594-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

kvm_get_supported_hv_cpuid() may come handy in all Hyper-V related tests.
Split it off hyperv_cpuid test, create system-wide and vcpu versions.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 .../selftests/kvm/include/x86_64/processor.h  |  3 ++
 .../selftests/kvm/lib/x86_64/processor.c      | 33 +++++++++++++++++++
 .../selftests/kvm/x86_64/hyperv_cpuid.c       | 31 ++---------------
 3 files changed, 39 insertions(+), 28 deletions(-)

```
#### [PATCH] KVM: x86: Zap the oldest MMU pages, not the newestFrom: Sean Christopherson <seanjc@google.com>
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12017823
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id C3B59C433E0
	for <kvm@archiver.kernel.org>; Wed, 13 Jan 2021 20:51:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8B13023107
	for <kvm@archiver.kernel.org>; Wed, 13 Jan 2021 20:51:17 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728911AbhAMUvP (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 13 Jan 2021 15:51:15 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:35126 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728856AbhAMUvP (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 13 Jan 2021 15:51:15 -0500
Received: from mail-qt1-x84a.google.com (mail-qt1-x84a.google.com
 [IPv6:2607:f8b0:4864:20::84a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id E7EB6C061794
        for <kvm@vger.kernel.org>; Wed, 13 Jan 2021 12:50:34 -0800 (PST)
Received: by mail-qt1-x84a.google.com with SMTP id w3so2436489qti.17
        for <kvm@vger.kernel.org>; Wed, 13 Jan 2021 12:50:34 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=aIUBOyJyX6WGyseukIAcch3nn35rSww3/Zr/HwJ5908=;
        b=X46oEX+TtT0/gQq1+bgCMAGs5q+1p1nbBc5zmdukXctlvH4UtROQqOzXceid7TJNTu
         kyXXTX6tncyk3hxvujy/iyyVN4QcvZVqz9Ff/t7884507h2CcrZG99Qh7L5U9hFWnBEM
         p2T0UjyYtTsOq/O3JVLPMzJ46Be7mqYvRWwEKbOwDA9kgOnKQ2u0sAiQT/RkXj+LMmvi
         6dL4/+ctx1S3OZlfE5mxMgg9uAvMp82HbV08QrtHenL0NuGmPF05sLE3jYH1OY6q6yL9
         GvdecP8BRSOMRK0al+gWw/03Ja6TgBa3ksLeHvCVcztk6qd4SHkeguOWKFs1SzklcDim
         RSfg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:reply-to:date:message-id:mime-version
         :subject:from:to:cc;
        bh=aIUBOyJyX6WGyseukIAcch3nn35rSww3/Zr/HwJ5908=;
        b=dc09X/f7Qje5Dta/qCYrlSWuNumY5o83+bCipsIPGZIVMqNLC8w+BedL9d/xSfOr4q
         u+vGU8TmPvOGBDZKt2DO9iqQAAG0x0aMfL1cYjZZ7CxSzR6ZfQp086yP5EB4tI3dON1Q
         ECvaR5QUJHHn5k8kp2xfPGE/l8Oj7q0M/X5BguH2G8KkI+GGHJvuwmwLBd40f1DSbOXA
         B44T1TP17Ol9b+h/fTAoFVGXQEANsQITZBD7C6MLdLsDZpy+PohvdvQ6pWKCYlPrcu8N
         QXsLbvmF4YgrsLDJmr9o/VB3uvEKAd/8YB8zLY3hTEHgWQnGgrHuz9mfiHtnBRvzc+gf
         PBkg==
X-Gm-Message-State: AOAM532tvWJF7d6O2yWhorv/Fb/6p47C8u13ATAGHceORSG248fUvKoi
        yFLQgign15i5V/PAfhzVz41D8kA/imc=
X-Google-Smtp-Source: 
 ABdhPJwlo3gK+jvvCcXXwYoVkAhwO/EjVIRBiIUBMoTWB4pnwbc/n6HoZoeY/is8j0V6z8lDlU3WyBETvSY=
Sender: "seanjc via sendgmr" <seanjc@seanjc798194.pdx.corp.google.com>
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:1ea0:b8ff:fe73:50f5])
 (user=seanjc job=sendgmr) by 2002:a25:d60a:: with SMTP id
 n10mr6327286ybg.457.1610571034135;
 Wed, 13 Jan 2021 12:50:34 -0800 (PST)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Wed, 13 Jan 2021 12:50:30 -0800
Message-Id: <20210113205030.3481307-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.30.0.284.gd98b1dd5eaa7-goog
Subject: [PATCH] KVM: x86: Zap the oldest MMU pages, not the newest
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Zdenek Kaspar <zkaspar82@gmail.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Walk the list of MMU pages in reverse in kvm_mmu_zap_oldest_mmu_pages().
The list is FIFO, meaning new pages are inserted at the head and thus
the oldest pages are at the tail.  Using a "forward" iterator causes KVM
to zap MMU pages that were just added, which obliterates guest
performance once the max number of shadow MMU pages is reached.

Fixes: 6b82ef2c9cf1 ("KVM: x86/mmu: Batch zap MMU pages when recycling oldest pages")
Reported-by: Zdenek Kaspar <zkaspar82@gmail.com>
Cc: stable@vger.kernel.org
Signed-off-by: Sean Christopherson <seanjc@google.com>
---
 arch/x86/kvm/mmu/mmu.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
