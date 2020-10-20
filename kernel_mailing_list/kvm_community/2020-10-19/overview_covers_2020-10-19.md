

#### [PATCH 0/2 v2] KVM: nSVM: Check reserved values for 'Type' and
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
From patchwork Mon Oct 19 22:35:55 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11845371
Return-Path: <SRS0=8juW=D2=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-6.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,UNPARSEABLE_RELAY,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=no autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B73ECC433E7
	for <kvm@archiver.kernel.org>; Mon, 19 Oct 2020 22:36:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6C5B222453
	for <kvm@archiver.kernel.org>; Mon, 19 Oct 2020 22:36:28 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="D9Jf5oxu"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388348AbgJSWg0 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 19 Oct 2020 18:36:26 -0400
Received: from aserp2120.oracle.com ([141.146.126.78]:49168 "EHLO
        aserp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2388203AbgJSWg0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 19 Oct 2020 18:36:26 -0400
Received: from pps.filterd (aserp2120.oracle.com [127.0.0.1])
        by aserp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 09JMJEGh085011;
        Mon, 19 Oct 2020 22:36:17 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id; s=corp-2020-01-29;
 bh=QZd3N7SULVpBAXzDHHK4dmuH3GbfB30qqV+dlmsI138=;
 b=D9Jf5oxuIAnTw201wQ0GrIGtg6mpmGTQmzw9SS8o1v7aaj3IwPYS5qAqHkv7KlHBrlv1
 MsT7mh64FUUWLrWWox7t3KkJCen6Fwvxu4FOTEkahf52BOXZlUX9MYiSY39drWu/Hjcw
 Qn3ed44/sfhq6Gryi3TzlK4aLlnzicRKudM5WYGmgMMfWF0Miko02sjtGAMCcAvgQQrT
 VcjzCustWBqYl/b3Zi2pFPB1F2O9fJ06PESyPKXdywPE61GNlQKwhTsv3UtCjBYbUUAp
 T8yQi1sZPICdbvDdjqewoj2jNbrc6WaoulX2FZL6DgAJPlvg980EWKIo2FeghAF+Qbf2 /w==
Received: from aserp3020.oracle.com (aserp3020.oracle.com [141.146.126.70])
        by aserp2120.oracle.com with ESMTP id 349jrpg6de-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=FAIL);
        Mon, 19 Oct 2020 22:36:17 +0000
Received: from pps.filterd (aserp3020.oracle.com [127.0.0.1])
        by aserp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 09JMLmRk096340;
        Mon, 19 Oct 2020 22:36:17 GMT
Received: from userv0121.oracle.com (userv0121.oracle.com [156.151.31.72])
        by aserp3020.oracle.com with ESMTP id 348agwpe0n-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 19 Oct 2020 22:36:16 +0000
Received: from abhmp0020.oracle.com (abhmp0020.oracle.com [141.146.116.26])
        by userv0121.oracle.com (8.14.4/8.13.8) with ESMTP id 09JMaFF0005174;
        Mon, 19 Oct 2020 22:36:15 GMT
Received: from nsvm-sadhukhan-1.osdevelopmeniad.oraclevcn.com
 (/100.100.230.216)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Mon, 19 Oct 2020 15:36:15 -0700
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com,
        sean.j.christopherson@intel.com
Subject: [PATCH 0/2 v2] KVM: nSVM: Check reserved values for 'Type' and
 invalid vectors in EVENTINJ
Date: Mon, 19 Oct 2020 22:35:55 +0000
Message-Id: <20201019223557.36491-1-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.18.4
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9779
 signatures=668682
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 adultscore=0
 mlxscore=0 phishscore=0
 malwarescore=0 spamscore=0 suspectscore=1 bulkscore=0 mlxlogscore=640
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2010190150
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9779
 signatures=668682
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 phishscore=0
 lowpriorityscore=0
 priorityscore=1501 impostorscore=0 adultscore=0 bulkscore=0 malwarescore=0
 mlxlogscore=652 mlxscore=0 spamscore=0 suspectscore=1 clxscore=1015
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2010190150
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

v1 -> v2:
	The 'while' loop in patch# 2 is replaced with a 'for' loop


According to sections "Canonicalization and Consistency Checks" and "Event
Injection" in APM vol 2,

    VMRUN exits with VMEXIT_INVALID error code if either:
      - Reserved values of TYPE have been specified, or
      - TYPE = 3 (exception) has been specified with a vector that does not
	correspond to an exception (this includes vector 2, which is an NMI,
	not an exception).

Patch# 1 adds these checks to KVM.
Patch# 2 adds tests for these checks.


[PATCH 1/2 v2] KVM: nSVM: Check reserved values for 'Type' and invalid
[PATCH 2/2 v2] nSVM: Test reserved values for 'Type' and invalid vectors in

 arch/x86/include/asm/svm.h |  4 ++++
 arch/x86/kvm/svm/nested.c  | 14 ++++++++++++++
 2 files changed, 18 insertions(+)

Krish Sadhukhan (1):
      KVM: nSVM: Check reserved values for 'Type' and invalid vectors in EVENTINJ

[root@nsvm-sadhukhan-1 kvm-unit-tests]# /root/Tools/git-format-patch.sh 4e259a7
 x86/svm_tests.c | 38 ++++++++++++++++++++++++++++++++++++++
 1 file changed, 38 insertions(+)

Krish Sadhukhan (1):
      nSVM: Test reserved values for 'Type' and invalid vectors in EVENTINJ
```
