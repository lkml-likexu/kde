#### [PATCH 1/2] SVM: Replace numeric value for SME CPUID leaf with a #define
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11743861
Return-Path: <SRS0=1t8w=CH=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 67CBC913
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 29 Aug 2020 01:01:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 48F7520CC7
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 29 Aug 2020 01:01:41 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="ZPSzMHwj"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726322AbgH2BBk (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 28 Aug 2020 21:01:40 -0400
Received: from userp2130.oracle.com ([156.151.31.86]:41586 "EHLO
        userp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726219AbgH2BBj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 28 Aug 2020 21:01:39 -0400
Received: from pps.filterd (userp2130.oracle.com [127.0.0.1])
        by userp2130.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 07T0wuWd132059;
        Sat, 29 Aug 2020 01:01:34 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id; s=corp-2020-01-29;
 bh=8Yu4qoaim9wRU4mKIq4d2rfXeWhJwg+RqYzZbfrqzgk=;
 b=ZPSzMHwjVko//1HfVm8iqN8AlriGVlJ2kUevwWcuwHFsOxr0AQV+0VSdmWuD9m7GCbrT
 DElVAUhHPBioI8A1lMRJWrlnS+f0Nk9u9kJ9rroI8HteRmLz5/DWciMpvpJpqKphgoWf
 hE2tHkNQgKBiqT3kcCp5lycOv404880HkcnuHnXf/rOlD/LeInMFG0yK98dMa+anIi5n
 EqyoF3Y5VxRT/lM6yoBPj+ZVFcAyjnMoybzMAGtsRtzvo06+r9wrcNbLuoE2WcOkA/BO
 VNcYexu6rDFSAEzrQoNfRRCStZLwVQHgzJuslQyHf4Ac2R3ylIOCKHg7ovRQ2IW5DFNp wA==
Received: from aserp3020.oracle.com (aserp3020.oracle.com [141.146.126.70])
        by userp2130.oracle.com with ESMTP id 336ht3pqty-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=FAIL);
        Sat, 29 Aug 2020 01:01:34 +0000
Received: from pps.filterd (aserp3020.oracle.com [127.0.0.1])
        by aserp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 07T0oNaI050688;
        Sat, 29 Aug 2020 00:59:33 GMT
Received: from aserv0122.oracle.com (aserv0122.oracle.com [141.146.126.236])
        by aserp3020.oracle.com with ESMTP id 333ruh4fya-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Sat, 29 Aug 2020 00:59:33 +0000
Received: from abhmp0007.oracle.com (abhmp0007.oracle.com [141.146.116.13])
        by aserv0122.oracle.com (8.14.4/8.14.4) with ESMTP id 07T0xWNi005713;
        Sat, 29 Aug 2020 00:59:32 GMT
Received: from nsvm-sadhukhan-1.osdevelopmeniad.oraclevcn.com
 (/100.100.230.216)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Fri, 28 Aug 2020 17:59:32 -0700
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com
Subject: [PATCH 1/2] SVM: Replace numeric value for SME CPUID leaf with a
 #define
Date: Sat, 29 Aug 2020 00:59:25 +0000
Message-Id: <20200829005926.5477-1-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.18.4
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9727
 signatures=668679
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 mlxlogscore=999
 phishscore=0
 bulkscore=0 suspectscore=1 spamscore=0 mlxscore=0 adultscore=0
 malwarescore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2008290001
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9727
 signatures=668679
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 bulkscore=0
 adultscore=0 malwarescore=0
 phishscore=0 priorityscore=1501 clxscore=1015 suspectscore=1 spamscore=0
 impostorscore=0 mlxscore=0 mlxlogscore=999 lowpriorityscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2006250000
 definitions=main-2008290002
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 arch/x86/include/asm/svm.h | 1 +
 arch/x86/kvm/svm/svm.c     | 4 ++--
 2 files changed, 3 insertions(+), 2 deletions(-)

```
#### [PATCH 1/3] KVM: nSVM: CR3 MBZ bits are only 63:52
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11743845
Return-Path: <SRS0=1t8w=CH=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 66C04109B
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 29 Aug 2020 00:48:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3A6F02098B
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 29 Aug 2020 00:48:45 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="DGdiCPA4"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726912AbgH2Asn (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 28 Aug 2020 20:48:43 -0400
Received: from aserp2120.oracle.com ([141.146.126.78]:57574 "EHLO
        aserp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726858AbgH2Asj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 28 Aug 2020 20:48:39 -0400
Received: from pps.filterd (aserp2120.oracle.com [127.0.0.1])
        by aserp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 07T0U0uD071603;
        Sat, 29 Aug 2020 00:48:34 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references; s=corp-2020-01-29;
 bh=708udkJmuvBzBN+G7FJxjGzlQoGjWc2P1e/kMUoa7m0=;
 b=DGdiCPA4JJ72UfgHPVEKkb6wiS9zi4T2Qu0+jSbCy35LZ1qa7mjCcKGgyKnqNc/EdVEf
 iG3a5FVXmusP6MdHguHGi9eoTyE3ZigotTRBTkhHph/zbEmhivU3okKVz/Xr6PQbIGD0
 6leIhh5aOfIF/IsqHIy4vCJMIgSRET4U4FtsQ0GMN3Tu5iBUI71V7b5c7Ot7Mt/1tf/c
 0jWJNJCNKiP6E7UsEWPJsR3S1oO9CZRkCZd/RWZyuQytXzDI3kZG+acsZd3jnPwH1N6A
 DzJE02iqU1vbzSN4O9KTJvJ6qGSXv36BDmMfkh6LejsHNx09wa8dRyxgY5jXoMgYtl0g Lw==
Received: from aserp3030.oracle.com (aserp3030.oracle.com [141.146.126.71])
        by aserp2120.oracle.com with ESMTP id 333dbsemft-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=FAIL);
        Sat, 29 Aug 2020 00:48:34 +0000
Received: from pps.filterd (aserp3030.oracle.com [127.0.0.1])
        by aserp3030.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 07T0V0DB139422;
        Sat, 29 Aug 2020 00:48:34 GMT
Received: from userv0122.oracle.com (userv0122.oracle.com [156.151.31.75])
        by aserp3030.oracle.com with ESMTP id 333r9q8ae3-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Sat, 29 Aug 2020 00:48:34 +0000
Received: from abhmp0020.oracle.com (abhmp0020.oracle.com [141.146.116.26])
        by userv0122.oracle.com (8.14.4/8.14.4) with ESMTP id 07T0mXAl030899;
        Sat, 29 Aug 2020 00:48:33 GMT
Received: from nsvm-sadhukhan-1.osdevelopmeniad.oraclevcn.com
 (/100.100.230.216)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Fri, 28 Aug 2020 17:48:33 -0700
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com
Subject: [PATCH 1/3] KVM: nSVM: CR3 MBZ bits are only 63:52
Date: Sat, 29 Aug 2020 00:48:22 +0000
Message-Id: <20200829004824.4577-2-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.18.4
In-Reply-To: <20200829004824.4577-1-krish.sadhukhan@oracle.com>
References: <20200829004824.4577-1-krish.sadhukhan@oracle.com>
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9727
 signatures=668679
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 malwarescore=0
 mlxscore=0 bulkscore=0
 adultscore=0 spamscore=0 mlxlogscore=999 phishscore=0 suspectscore=1
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2006250000
 definitions=main-2008290000
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9727
 signatures=668679
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 bulkscore=0
 clxscore=1015
 priorityscore=1501 impostorscore=0 phishscore=0 malwarescore=0
 mlxlogscore=999 spamscore=0 mlxscore=0 lowpriorityscore=0 suspectscore=1
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2008290000
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Commit 761e4169346553c180bbd4a383aedd72f905bc9a created a wrong mask for the
CR3 MBZ bits. According to APM vol 2, only the upper 12 bits are MBZ.

(Fixes 761e4169346553c180bbd4a383aedd72f905bc9a)

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 arch/x86/kvm/svm/svm.h | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] nSVM: Add a test for the P (present) bit in NPT entry
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11743857
Return-Path: <SRS0=1t8w=CH=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CD88A913
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 29 Aug 2020 00:57:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B71872098B
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 29 Aug 2020 00:57:33 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="s9UEc1F0"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726322AbgH2A5c (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 28 Aug 2020 20:57:32 -0400
Received: from aserp2120.oracle.com ([141.146.126.78]:33582 "EHLO
        aserp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726219AbgH2A5b (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 28 Aug 2020 20:57:31 -0400
Received: from pps.filterd (aserp2120.oracle.com [127.0.0.1])
        by aserp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 07T0sUEY102182;
        Sat, 29 Aug 2020 00:57:28 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id; s=corp-2020-01-29;
 bh=uDjbNBVuawhF3AVAtaXgZ+JUtMQ5C/TyIR+uXkkF68s=;
 b=s9UEc1F0z+tIz8s1tvvQXpeFqi7zqyD+TA/D+0stA8fowH8/q5FFYVekS1bsZ6um1SZR
 cbwE9O7Rdbizw2we/hv1FOucI5ECKd6E+GM0jipSTcvNn2T+T+jI+4qg8MeKXNpZfWtF
 zO+u0xJVoyycq69Pf5QSqfiGnsXbSt/RT3Fk552zeuQXOB0w+lzdo5ezAQjsC5908+WM
 pRRNLhfzFGNtCYy5Y88kGrx0xZg7ZDX4RqZK59yNFGqiufg6D7QVo5R6gnTL4g40235b
 cExZcb+FswVrUZZgjN9dxUMRY3/Pq6u4hjqpfEw76v8oXr7Xy1kHcd0i6ok874Mj+oxu NQ==
Received: from userp3030.oracle.com (userp3030.oracle.com [156.151.31.80])
        by aserp2120.oracle.com with ESMTP id 333dbsemu7-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=FAIL);
        Sat, 29 Aug 2020 00:57:28 +0000
Received: from pps.filterd (userp3030.oracle.com [127.0.0.1])
        by userp3030.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 07T0pT6l112662;
        Sat, 29 Aug 2020 00:57:27 GMT
Received: from aserv0121.oracle.com (aserv0121.oracle.com [141.146.126.235])
        by userp3030.oracle.com with ESMTP id 337c4s0veu-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Sat, 29 Aug 2020 00:57:27 +0000
Received: from abhmp0018.oracle.com (abhmp0018.oracle.com [141.146.116.24])
        by aserv0121.oracle.com (8.14.4/8.13.8) with ESMTP id 07T0vQbJ023955;
        Sat, 29 Aug 2020 00:57:26 GMT
Received: from nsvm-sadhukhan-1.osdevelopmeniad.oraclevcn.com
 (/100.100.230.216)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Fri, 28 Aug 2020 17:57:26 -0700
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com
Subject: [PATCH] nSVM: Add a test for the P (present) bit in NPT entry
Date: Sat, 29 Aug 2020 00:57:20 +0000
Message-Id: <20200829005720.5325-1-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.18.4
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9727
 signatures=668679
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 mlxscore=0
 suspectscore=1 adultscore=0
 mlxlogscore=999 bulkscore=0 phishscore=0 spamscore=0 malwarescore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2006250000
 definitions=main-2008290001
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9727
 signatures=668679
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 bulkscore=0
 clxscore=1015
 priorityscore=1501 impostorscore=0 phishscore=0 malwarescore=0
 mlxlogscore=999 spamscore=0 mlxscore=0 lowpriorityscore=0 suspectscore=1
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2008290001
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If the P (present) bit in an NPT entry is cleared, VMRUN will fail and the
guest will exit to the host with an exit code of 0x400 (#NPF). The following
bits of importance in EXITINFO1 will be set/cleared to indicate the failure:

	bit# 0: cleared
	bit# 32: set

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 x86/svm_tests.c | 29 +++++++++++++++++++++++++++++
 1 file changed, 29 insertions(+)

```
