#### [PATCH 1/4 v2] KVM: nSVM: CR3 MBZ bits are only 63:52
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11803069
Return-Path: <SRS0=x+XD=DF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6BE0F13B2
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 28 Sep 2020 07:21:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 49E092080A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 28 Sep 2020 07:21:13 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="ZWP9Qy6H"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726564AbgI1HVM (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 28 Sep 2020 03:21:12 -0400
Received: from aserp2120.oracle.com ([141.146.126.78]:42314 "EHLO
        aserp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726465AbgI1HVL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 28 Sep 2020 03:21:11 -0400
Received: from pps.filterd (aserp2120.oracle.com [127.0.0.1])
        by aserp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 08S7Jku8104719;
        Mon, 28 Sep 2020 07:21:08 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references; s=corp-2020-01-29;
 bh=708udkJmuvBzBN+G7FJxjGzlQoGjWc2P1e/kMUoa7m0=;
 b=ZWP9Qy6HK0dFFXmf6q+sydsjWk9bTm01puejcybLDCsASSLWzzkQgKsc9BSjRHG8zzmI
 a9g7a62HL2SDafwF2NE3Vp+ekD9pph+YnJb87pyhLJqmeCvCKLLqm5zLiIZfhvJSuCqu
 OLHu5opySJKh9EBnRa3cqMEzrU+yeVOkL3D1rkyC6U6FHL07hxG+IKBIhisKwGsnweZG
 X3B5WrMQf1JGU5Nj9gFqkBwyGcJeDl+5ulwxWNJ9bKWOQHmw7OeqdtlmtD0GMpRUleo0
 wZclkcOtwHOcRTPjp2UMU51rAuoQRTjNJZsgIajpY+NU/YiQ+WylXFSbcn3gsrhFF0Kn fA==
Received: from userp3030.oracle.com (userp3030.oracle.com [156.151.31.80])
        by aserp2120.oracle.com with ESMTP id 33swkkkdps-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=FAIL);
        Mon, 28 Sep 2020 07:21:08 +0000
Received: from pps.filterd (userp3030.oracle.com [127.0.0.1])
        by userp3030.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 08S7Jg7w131604;
        Mon, 28 Sep 2020 07:21:07 GMT
Received: from aserv0122.oracle.com (aserv0122.oracle.com [141.146.126.236])
        by userp3030.oracle.com with ESMTP id 33tfjujg4g-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 28 Sep 2020 07:21:07 +0000
Received: from abhmp0017.oracle.com (abhmp0017.oracle.com [141.146.116.23])
        by aserv0122.oracle.com (8.14.4/8.14.4) with ESMTP id 08S7L6DP024053;
        Mon, 28 Sep 2020 07:21:06 GMT
Received: from nsvm-sadhukhan-1.osdevelopmeniad.oraclevcn.com
 (/100.100.230.216)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Mon, 28 Sep 2020 00:21:06 -0700
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com
Subject: [PATCH 1/4 v2] KVM: nSVM: CR3 MBZ bits are only 63:52
Date: Mon, 28 Sep 2020 07:20:40 +0000
Message-Id: <20200928072043.9359-2-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.18.4
In-Reply-To: <20200928072043.9359-1-krish.sadhukhan@oracle.com>
References: <20200928072043.9359-1-krish.sadhukhan@oracle.com>
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9757
 signatures=668680
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 malwarescore=0
 spamscore=0 mlxscore=0
 phishscore=0 adultscore=0 bulkscore=0 mlxlogscore=999 suspectscore=1
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2006250000
 definitions=main-2009280061
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9757
 signatures=668680
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 malwarescore=0
 mlxscore=0 phishscore=0
 suspectscore=1 mlxlogscore=999 clxscore=1015 priorityscore=1501
 impostorscore=0 lowpriorityscore=0 bulkscore=0 spamscore=0 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2006250000
 definitions=main-2009280061
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
#### [PATCH 1/2] KVM: x86: rename KVM_REQ_GET_VMCS12_PAGES
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11803555
Return-Path: <SRS0=x+XD=DF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4CF946CA
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 28 Sep 2020 11:51:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2C29221D7F
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 28 Sep 2020 11:51:54 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="XpFCSNYo"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726610AbgI1Lvu (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 28 Sep 2020 07:51:50 -0400
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:48909 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726547AbgI1Lvu (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 28 Sep 2020 07:51:50 -0400
Dkim-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1601293908;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=QQBWknBGOINoO/rGGYREqBjY4abn68VKx7wYmghxbFA=;
        b=XpFCSNYo+vwH4iAegwJ+QC/R5UDvD5YTvhgjcp4R0xNgwkho7vb6igQcBxy6YAi4eBCGao
        czTL5FzLanhlstVhggwIkEDQSpyKT4eY/2OBoI5bRQY8jVKk0ZjxJqrWB2QxQbAPlaJVCv
        sh/B8Zz7gjqfXyPXXc2gc8pMB6l4/Lk=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-262-IwetUFYiMbWv6YKaCZARxQ-1; Mon, 28 Sep 2020 07:51:46 -0400
X-MC-Unique: IwetUFYiMbWv6YKaCZARxQ-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id B93B610050F6;
        Mon, 28 Sep 2020 11:51:45 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 64E8149F7;
        Mon, 28 Sep 2020 11:51:45 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: mlevitsk@redhat.com
Subject: [PATCH 1/2] KVM: x86: rename KVM_REQ_GET_VMCS12_PAGES
Date: Mon, 28 Sep 2020 07:51:43 -0400
Message-Id: <20200928115144.2446240-2-pbonzini@redhat.com>
In-Reply-To: <20200928115144.2446240-1-pbonzini@redhat.com>
References: <20200928115144.2446240-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We are going to use it for SVM too, so use a more generic name.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/include/asm/kvm_host.h | 4 ++--
 arch/x86/kvm/vmx/nested.c       | 8 ++++----
 arch/x86/kvm/x86.c              | 4 ++--
 3 files changed, 8 insertions(+), 8 deletions(-)

```
#### [kvm-unit-tests PULL 01/11] runtime.bash: remove outdated comment
##### From: Thomas Huth <thuth@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Huth <thuth@redhat.com>
X-Patchwork-Id: 11804407
Return-Path: <SRS0=x+XD=DF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 97CF1618
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 28 Sep 2020 17:50:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 717042083B
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 28 Sep 2020 17:50:15 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="F0WFuG4s"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726566AbgI1RuO (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 28 Sep 2020 13:50:14 -0400
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:45087 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726548AbgI1RuN (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 28 Sep 2020 13:50:13 -0400
Dkim-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1601315413;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:in-reply-to:in-reply-to:references:references;
        bh=DOZfFRPVyC+pOeVZsy5QetzWnL2NYBRY8w0e8CElX6k=;
        b=F0WFuG4so93hQd+QyF71UN/yAioBSekyrHXHok0er5sQXPwVFZepQlR8CcOQBwyTPnAKya
        6Q5ikEogYKVThyCQ+i1BkSd7YjsLG2xNrK3UCJWSx3GfifuPeeOu7kbW7YTatiS8SY3jTG
        0TP4GXwE66SrLhFO52ImRpmCQSPqGeM=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-128-VqaATA2QMX67L2vkEzNuzw-1; Mon, 28 Sep 2020 13:50:08 -0400
X-MC-Unique: VqaATA2QMX67L2vkEzNuzw-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id C27CF801AB1;
        Mon, 28 Sep 2020 17:50:04 +0000 (UTC)
Received: from thuth.com (unknown [10.40.192.131])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 8576510013C0;
        Mon, 28 Sep 2020 17:50:03 +0000 (UTC)
From: Thomas Huth <thuth@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Janosch Frank <frankja@linux.ibm.com>
Subject: [kvm-unit-tests PULL 01/11] runtime.bash: remove outdated comment
Date: Mon, 28 Sep 2020 19:49:48 +0200
Message-Id: <20200928174958.26690-2-thuth@redhat.com>
In-Reply-To: <20200928174958.26690-1-thuth@redhat.com>
References: <20200928174958.26690-1-thuth@redhat.com>
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Marc Hartmayer <mhartmay@linux.ibm.com>

Since commit 6e1d3752d7ca ("tap13: list testcases individually") the
comment is no longer valid. Therefore let's remove it.

Reviewed-by: Andrew Jones <drjones@redhat.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Signed-off-by: Marc Hartmayer <mhartmay@linux.ibm.com>
Message-Id: <20200825102036.17232-2-mhartmay@linux.ibm.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
Signed-off-by: Thomas Huth <thuth@redhat.com>
---
 scripts/runtime.bash | 3 ---
 1 file changed, 3 deletions(-)

```
#### [PATCH kvm-unit-tests] runtime.bash: fix check for parameter files
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11803475
Return-Path: <SRS0=x+XD=DF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 76D8F618
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 28 Sep 2020 11:34:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3CBE8221E8
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 28 Sep 2020 11:34:20 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Qg8A/cJS"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726796AbgI1LeT (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 28 Sep 2020 07:34:19 -0400
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:54044 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726559AbgI1LeS (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 28 Sep 2020 07:34:18 -0400
Dkim-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1601292857;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=nnytngNb/L/CTDPQQn5WTYGqtJoVY9N05tOcTzUYMM8=;
        b=Qg8A/cJSLuGNP8RK3/b0paYEVE31R/uTRm5NzYzRXTvKkGTCPEnzM/WqxAu/ncICqcOu/k
        n/mzxcgMhSEBAy5Ja2SQcZCB3T5C4U4qItIiTJubejhbRYXTq9WS3vFm9uU2OUmcWEQebl
        Q29/wx/P4h2qcYPpTSMD1vjswppeWMI=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-96-Cnlb5mGbP-Cmd6rVsE8omg-1; Mon, 28 Sep 2020 07:34:14 -0400
X-MC-Unique: Cnlb5mGbP-Cmd6rVsE8omg-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 56CFF800688
        for <kvm@vger.kernel.org>; Mon, 28 Sep 2020 11:34:13 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 0887A5D9CD;
        Mon, 28 Sep 2020 11:34:12 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: kvm@vger.kernel.org
Cc: drjones@redhat.com
Subject: [PATCH kvm-unit-tests] runtime.bash: fix check for parameter files
Date: Mon, 28 Sep 2020 07:34:12 -0400
Message-Id: <20200928113412.2419974-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We need to check if the file exists, not just if it is a non-empty string.
While an empty $path would have the unfortunate effect that "cat" would
read from stdin, that is not an issue as you can simply not do that.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
Reviewed-by: Andrew Jones <drjones@redhat.com>
---
 scripts/runtime.bash | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] KVM: x86: do not attempt TSC synchronization on guest writes
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11803583
Return-Path: <SRS0=x+XD=DF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7FDF9618
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 28 Sep 2020 12:02:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 56D882100A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 28 Sep 2020 12:02:00 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="ObUw6BD9"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726614AbgI1MB7 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 28 Sep 2020 08:01:59 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:54269 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726573AbgI1MB6 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 28 Sep 2020 08:01:58 -0400
Dkim-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1601294516;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=Y/UdGjPAJGJ2h0qtFm/U1BLa9fpLOzOU5/j4J/i16Gw=;
        b=ObUw6BD9XBHWmg3xTYPoxRxWHOpXpASxUAP4/Rr71o00RRJiX+Avv7hokzSv4BRZpblNH5
        kZjnGIilRTELWRaz2Bp5G2V4EEgjKDEoonQxNICfoqfvq0/JQDYt/YkrFpyk4GoyWz0wen
        dMPWEv+h31Hkn8NZjWnGxFggcUl3Pr4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-587-ku4Z5P0GOqCmhDkqN4pCtw-1; Mon, 28 Sep 2020 08:01:47 -0400
X-MC-Unique: ku4Z5P0GOqCmhDkqN4pCtw-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 4FBC81021D28;
        Mon, 28 Sep 2020 12:01:46 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id ECAD12C31E;
        Mon, 28 Sep 2020 12:01:45 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: mlevitsk@redhat.com
Subject: [PATCH] KVM: x86: do not attempt TSC synchronization on guest writes
Date: Mon, 28 Sep 2020 08:01:45 -0400
Message-Id: <20200928120145.2447718-2-pbonzini@redhat.com>
In-Reply-To: <20200928120145.2447718-1-pbonzini@redhat.com>
References: <20200928120145.2447718-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

KVM special-cases writes to MSR_IA32_TSC so that all CPUs have
the same base for the TSC.  This logic is complicated, and we
do not want it to have any effect once the VM is started.

In particular, if any guest started to synchronize its TSCs
with writes to MSR_IA32_TSC rather than MSR_IA32_TSC_ADJUST,
the additional effect of kvm_write_tsc code would be uncharted
territory.

Therefore, this patch makes writes to MSR_IA32_TSC behave
essentially the same as writes to MSR_IA32_TSC_ADJUST when
they come from the guest.  A new selftest (which passes
both before and after the patch) checks the current semantics
of writes to MSR_IA32_TSC and MSR_IA32_TSC_ADJUST originating
from both the host and the guest.

Upcoming work to remove the special side effects
of host-initiated writes to MSR_IA32_TSC and MSR_IA32_TSC_ADJUST
will be able to build onto this test, adjusting the host side
to use the new APIs and achieve the same effect.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/x86.c                            |  30 ++--
 tools/testing/selftests/kvm/Makefile          |   1 +
 .../selftests/kvm/x86_64/tsc_msrs_test.c      | 168 ++++++++++++++++++
 3 files changed, 179 insertions(+), 20 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/x86_64/tsc_msrs_test.c

```
#### [RFC PATCH 1/2] kvm/x86: intercept guest changes to X86_CR4_LA57
##### From: Lai Jiangshan <jiangshanlai@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Lai Jiangshan <jiangshanlai@gmail.com>
X-Patchwork-Id: 11803089
Return-Path: <SRS0=x+XD=DF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 26E2B618
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 28 Sep 2020 07:30:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 07DB4221E8
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 28 Sep 2020 07:30:29 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="UmOj2XUm"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726665AbgI1Ha0 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 28 Sep 2020 03:30:26 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:59772 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726380AbgI1Ha0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 28 Sep 2020 03:30:26 -0400
Received: from mail-pg1-x542.google.com (mail-pg1-x542.google.com
 [IPv6:2607:f8b0:4864:20::542])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 217F6C0613CE;
        Mon, 28 Sep 2020 00:30:26 -0700 (PDT)
Received: by mail-pg1-x542.google.com with SMTP id u24so119627pgi.1;
        Mon, 28 Sep 2020 00:30:26 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=SRDOrcOXo2fctkY7+23XpqsPfrMaqBHYhZz060zwT4Q=;
        b=UmOj2XUm/RnyvxN42kx1ehBHGEBvFHIY/zknL6770zTKMNoUrydl4/Z/5ORQASPRl0
         jvrZc+IPZRom//1jSEALkM7bGChyOpxeRouaw+BpUwmR2llvqmDSCSA7K60L0Jb9Kcsd
         Sy+P0p5yIsUAgdvNkXhLbhxEDNrMPKjjwmCbUq4OB5Kie5/MU2GkOlSFFA8K56GHI5Qy
         kWKB97zYkEp1wMWXuREglQnWlrWIcIoTLPVQ1OYTfWcfC/UOPOjstpm5KD4J2KX6JR5R
         uwYEkXwvUxC8vBxGfRLgVU5d+oKpV+rtC73Flcr/07L0YPanwHamHQaS7xEVUXKJXpBb
         9QJw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=SRDOrcOXo2fctkY7+23XpqsPfrMaqBHYhZz060zwT4Q=;
        b=jSMmN0UlLRehZJ9WxZSO0svcC866iEth/q4XUuUqCE/Fy8MGRg1WjJh6rRNEG47l2r
         9kXtfXzalV61Aata/wPQbcO50X78xWZaYcRwi19GsqtBbCm+d9aG5vQDf/jW70mtwX7J
         46qIUXKBTIsZhkHPMNEE8+4R8KRn4rtbHVZTmIynzHTzlBMhPFns1gqVcUrQqXVgTtZt
         4AUAERGEYih1G30sMBt5RCP1vj1LeJEB2bq+qOaZY3J2X1a9brVUu54a1oXNh3ysqCgQ
         H+nYCQx8tlB+idgqWYn52w+ZbCpVBpw+guoQ5MD21CT1zVaBmqgeIHAo+KTYasxskjEG
         PWgQ==
X-Gm-Message-State: AOAM532R4xr1vrcpv2Ooqrz4tOdq2egIpRdliMS3dmtzfbCb18OrELOG
        ZV31DNilws6nPQFMEWsD7UsxnqezQxk=
X-Google-Smtp-Source: 
 ABdhPJxny9MXVCI132op9NYkIA8MXVFiisGYHhNHNTyyqp/XYfn+gM9mGiHpfaKbSxFqjd2bdXaOLA==
X-Received: by 2002:aa7:904a:0:b029:142:2501:35d8 with SMTP id
 n10-20020aa7904a0000b0290142250135d8mr347011pfo.56.1601278225528;
        Mon, 28 Sep 2020 00:30:25 -0700 (PDT)
Received: from localhost ([47.251.3.230])
        by smtp.gmail.com with ESMTPSA id k7sm194840pjs.9.2020.09.28.00.30.24
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Mon, 28 Sep 2020 00:30:25 -0700 (PDT)
From: Lai Jiangshan <jiangshanlai@gmail.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Lai Jiangshan <laijs@linux.alibaba.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Yu Zhang <yu.c.zhang@linux.intel.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        x86@kernel.org, "H. Peter Anvin" <hpa@zytor.com>
Subject: [RFC PATCH 1/2] kvm/x86: intercept guest changes to X86_CR4_LA57
Date: Mon, 28 Sep 2020 16:30:46 +0800
Message-Id: <20200928083047.3349-1-jiangshanlai@gmail.com>
X-Mailer: git-send-email 2.19.1.6.gb485710b
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Lai Jiangshan <laijs@linux.alibaba.com>

When shadowpaping is enabled, guest should not be allowed
to toggle X86_CR4_LA57. And X86_CR4_LA57 is a rarely changed
bit, so we can just intercept all the attempts to toggle it
no matter shadowpaping is in used or not.

Fixes: fd8cb433734ee ("KVM: MMU: Expose the LA57 feature to VM.")
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Cc: Yu Zhang <yu.c.zhang@linux.intel.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Lai Jiangshan <laijs@linux.alibaba.com>
---
  No test to toggle X86_CR4_LA57 in guest since I can't access to
  any CPU supports it. Maybe it is not a real problem.

 arch/x86/kvm/kvm_cache_regs.h | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH v2 1/4] memory: allocation in low memory
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 11803909
Return-Path: <SRS0=x+XD=DF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4592D618
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 28 Sep 2020 14:23:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 29A00221E8
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 28 Sep 2020 14:23:47 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="WF5OUr24"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726325AbgI1OXq (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 28 Sep 2020 10:23:46 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:47758 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726526AbgI1OXp (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 28 Sep 2020 10:23:45 -0400
Received: from pps.filterd (m0098404.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 08SEJhYP137282;
        Mon, 28 Sep 2020 10:23:45 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references; s=pp1;
 bh=Etdk7PsqeLaD3Vusxf283pn0UpNfftluNM0Nl0Hj960=;
 b=WF5OUr24uXnLy6qDL+wZzMreSFVbnAfdZHxOgiML8BSJDhURlV6DfAeOzCYr4JmX5oQi
 7i015PuAjo1i6rk1Yy/4mbJKeY/k2AK4wptuuGVRSUAZOvgm8sBeGx5F7eDdiadOzgQ4
 +9B9kGEMqLn4ViA7KxgzoEBYic1TObOF5grkRi08fuwJVoWvsSDHMxcD56IG1p72rvRn
 CjCPNzT+Lamy3ZJzMqysQN4DifBGWeglRodA3dGTEla38AykuAyzJVUkHecPwjfPrYJt
 jt1nfizo3N9Zvanw3PK8QLqiOC9Ai8NvmCgJv67vpkLgVmJl14eOMvM5n8kdnG8+5s+T DA==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 33uhgf8227-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 28 Sep 2020 10:23:44 -0400
Received: from m0098404.ppops.net (m0098404.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 08SEKVl2142340;
        Mon, 28 Sep 2020 10:23:44 -0400
Received: from ppma06fra.de.ibm.com (48.49.7a9f.ip4.static.sl-reverse.com
 [159.122.73.72])
        by mx0a-001b2d01.pphosted.com with ESMTP id 33uhgf821s-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 28 Sep 2020 10:23:44 -0400
Received: from pps.filterd (ppma06fra.de.ibm.com [127.0.0.1])
        by ppma06fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 08SEMLNp008452;
        Mon, 28 Sep 2020 14:23:42 GMT
Received: from b06cxnps4075.portsmouth.uk.ibm.com
 (d06relay12.portsmouth.uk.ibm.com [9.149.109.197])
        by ppma06fra.de.ibm.com with ESMTP id 33svwgs5b8-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 28 Sep 2020 14:23:42 +0000
Received: from d06av24.portsmouth.uk.ibm.com (mk.ibm.com [9.149.105.60])
        by b06cxnps4075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 08SENdHi10551706
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 28 Sep 2020 14:23:39 GMT
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 3F73542041;
        Mon, 28 Sep 2020 14:23:39 +0000 (GMT)
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id D7BFF4204D;
        Mon, 28 Sep 2020 14:23:38 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.66.164])
        by d06av24.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Mon, 28 Sep 2020 14:23:38 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, frankja@linux.ibm.com,
        david@redhat.com, thuth@redhat.com, cohuck@redhat.com,
        imbrenda@linux.ibm.com
Subject: [kvm-unit-tests PATCH v2 1/4] memory: allocation in low memory
Date: Mon, 28 Sep 2020 16:23:34 +0200
Message-Id: <1601303017-8176-2-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1601303017-8176-1-git-send-email-pmorel@linux.ibm.com>
References: <1601303017-8176-1-git-send-email-pmorel@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-09-28_14:2020-09-28,2020-09-28 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 lowpriorityscore=0
 suspectscore=1 mlxscore=0 malwarescore=0 phishscore=0 priorityscore=1501
 impostorscore=0 mlxlogscore=999 spamscore=0 adultscore=0 clxscore=1015
 bulkscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2009280108
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Some architectures need allocations to be done under a
specific address limit to allow DMA from I/O.

We propose here a very simple page allocator to get
pages allocated under this specific limit.

The DMA page allocator will only use part of the available memory
under the DMA address limit to let room for the standard allocator.

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
---
 lib/alloc_dma_page.c | 57 ++++++++++++++++++++++++++++++++++++++++++++
 lib/alloc_dma_page.h | 24 +++++++++++++++++++
 lib/s390x/sclp.c     |  2 ++
 s390x/Makefile       |  1 +
 4 files changed, 84 insertions(+)
 create mode 100644 lib/alloc_dma_page.c
 create mode 100644 lib/alloc_dma_page.h

diff --git a/lib/alloc_dma_page.c b/lib/alloc_dma_page.c
new file mode 100644
index 0000000..6a16e38
--- /dev/null
+++ b/lib/alloc_dma_page.c
@@ -0,0 +1,57 @@
+/*
+ * Page allocator for DMA
+ *
+ * Copyright (c) IBM, Corp. 2020
+ *
+ * Authors:
+ *  Pierre Morel <pmorel@linux.ibm.com>
+ *
+ * This code is free software; you can redistribute it and/or modify it
+ * under the terms of the GNU Library General Public License version 2.
+ */
+#include <libcflat.h>
+#include <asm/spinlock.h>
+#include <alloc_dma_page.h>
+
+static struct spinlock lock;
+static void *dma_freelist = 0;
+
+void put_dma_page(void *dma_page)
+{
+	spin_lock(&lock);
+	*(void **)dma_page = dma_freelist;
+	dma_freelist = dma_page;
+	spin_unlock(&lock);
+}
+
+void *get_dma_page(void)
+{
+	void *p = NULL;
+
+	spin_lock(&lock);
+	if (!dma_freelist)
+		goto end_unlock;
+
+	p = dma_freelist;
+	dma_freelist = *(void **)dma_freelist;
+
+end_unlock:
+	spin_unlock(&lock);
+	return p;
+}
+
+phys_addr_t dma_page_alloc_init(phys_addr_t start, phys_addr_t end)
+{
+	int start_pfn = start >> PAGE_SHIFT;
+	int nb_pfn = ((end - start) >> PAGE_SHIFT) - 1;
+	int max, pfn;
+
+	max = start_pfn + nb_pfn / DMA_ALLOC_RATIO;
+	if (max > DMA_MAX_PFN)
+		max = DMA_MAX_PFN;
+
+	for (pfn = start_pfn; pfn < max; pfn++)
+		put_dma_page((void *)((unsigned long) pfn << PAGE_SHIFT));
+
+	return (phys_addr_t)pfn << PAGE_SHIFT;
+}
diff --git a/lib/alloc_dma_page.h b/lib/alloc_dma_page.h
new file mode 100644
index 0000000..85e1d2f
--- /dev/null
+++ b/lib/alloc_dma_page.h
@@ -0,0 +1,24 @@
+/*
+ * Page allocator for DMA definitions
+ *
+ * Copyright (c) IBM, Corp. 2020
+ *
+ * Authors:
+ *  Pierre Morel <pmorel@linux.ibm.com>
+ *
+ * This code is free software; you can redistribute it and/or modify it
+ * under the terms of the GNU Library General Public License version 2.
+ */
+#ifndef _ALLOC_DMA_PAGE_H_
+#define _ALLOC_DMA_PAGE_H_
+
+#include <asm/page.h>
+
+void put_dma_page(void *dma_page);
+void *get_dma_page(void);
+phys_addr_t dma_page_alloc_init(phys_addr_t start_pfn, phys_addr_t nb_pages);
+
+#define DMA_MAX_PFN	(0x80000000 >> PAGE_SHIFT)
+#define DMA_ALLOC_RATIO	8
+
+#endif /* _ALLOC_DMA_PAGE_H_ */
```
#### [PATCH v2] KVM: x86: do not attempt TSC synchronization on guest writes
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11803581
Return-Path: <SRS0=x+XD=DF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A77BF618
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 28 Sep 2020 12:01:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6693C2100A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 28 Sep 2020 12:01:58 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="K3cn0HIG"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726608AbgI1MB5 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 28 Sep 2020 08:01:57 -0400
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:40533 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726513AbgI1MB5 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 28 Sep 2020 08:01:57 -0400
Dkim-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1601294514;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=5x7ATKq2RaTYAIBg6iojDf/X7sQY/YDOVx3CTzTqz5Q=;
        b=K3cn0HIGh+KeqBs9MaG79W9mb/zIhAv9e+3wCCJR44nW+1sDNN7MrfMlLHVgIDXqQUpA9e
        TPqftE7OTSOWc87h9t8TaC7tFZcO8RhKPbQo+WCbCv7bRoig95dnukD2IP/zaBBp/ESyuI
        6XC4ysm0DlY8X+LLKQHiWpJMfDjlcH4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-278-aZL1OF69MC-xxJo59UgjlQ-1; Mon, 28 Sep 2020 08:01:46 -0400
X-MC-Unique: aZL1OF69MC-xxJo59UgjlQ-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id CD55E1021D25;
        Mon, 28 Sep 2020 12:01:45 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 6AF7055765;
        Mon, 28 Sep 2020 12:01:45 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: mlevitsk@redhat.com
Subject: [PATCH v2] KVM: x86: do not attempt TSC synchronization on guest
 writes
Date: Mon, 28 Sep 2020 08:01:44 -0400
Message-Id: <20200928120145.2447718-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

KVM special-cases writes to MSR_IA32_TSC so that all CPUs have
the same base for the TSC.  This logic is complicated, and we
do not want it to have any effect once the VM is started.

In particular, if any guest started to synchronize its TSCs
with writes to MSR_IA32_TSC rather than MSR_IA32_TSC_ADJUST,
the additional effect of kvm_write_tsc code would be uncharted
territory.

Therefore, this patch makes writes to MSR_IA32_TSC behave
essentially the same as writes to MSR_IA32_TSC_ADJUST when
they come from the guest.  A new selftest (which passes
both before and after the patch) checks the current semantics
of writes to MSR_IA32_TSC and MSR_IA32_TSC_ADJUST originating
from both the host and the guest.

Upcoming work to remove the special side effects
of host-initiated writes to MSR_IA32_TSC and MSR_IA32_TSC_ADJUST
will be able to build onto this test, adjusting the host side
to use the new APIs and achieve the same effect.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
        v1->v2: use l1_tsc_offset so as not to break vmx_tsc_adjust_test

 arch/x86/kvm/x86.c                            |  30 ++--
 tools/testing/selftests/kvm/Makefile          |   1 +
 .../selftests/kvm/x86_64/tsc_msrs_test.c      | 168 ++++++++++++++++++
 3 files changed, 179 insertions(+), 20 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/x86_64/tsc_msrs_test.c

```
#### [PATCH] vhost: Don't call vq_access_ok() when using IOTLBFrom: Greg Kurz <groug@kaod.org>
##### From: Greg Kurz <groug@kaod.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Greg Kurz <groug@kaod.org>
X-Patchwork-Id: 11803671
Return-Path: <SRS0=x+XD=DF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4C0F66CA
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 28 Sep 2020 12:41:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3BA8421531
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 28 Sep 2020 12:41:30 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726657AbgI1Ml3 convert rfc822-to-8bit (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 28 Sep 2020 08:41:29 -0400
Received: from us-smtp-delivery-44.mimecast.com ([207.211.30.44]:48927 "EHLO
        us-smtp-delivery-44.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726393AbgI1Ml3 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 28 Sep 2020 08:41:29 -0400
X-Greylist: delayed 303 seconds by postgrey-1.27 at vger.kernel.org;
 Mon, 28 Sep 2020 08:41:28 EDT
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-216-mF0ZdjI4MHKeMhrLaFIPOw-1; Mon, 28 Sep 2020 08:35:19 -0400
X-MC-Unique: mF0ZdjI4MHKeMhrLaFIPOw-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 9D96C5708B;
        Mon, 28 Sep 2020 12:35:18 +0000 (UTC)
Received: from bahia.lan (ovpn-112-195.ams2.redhat.com [10.36.112.195])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 415965C1BB;
        Mon, 28 Sep 2020 12:35:05 +0000 (UTC)
Subject: [PATCH] vhost: Don't call vq_access_ok() when using IOTLB
From: Greg Kurz <groug@kaod.org>
To: "Michael S. Tsirkin" <mst@redhat.com>,
        Jason Wang <jasowang@redhat.com>
Cc: kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org, Laurent Vivier <laurent@vivier.eu>,
        David Gibson <david@gibson.dropbear.id.au>
Date: Mon, 28 Sep 2020 14:35:04 +0200
Message-ID: <160129650442.480158.12085353517983890660.stgit@bahia.lan>
User-Agent: StGit/0.21
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Authentication-Results: relay.mimecast.com;
        auth=pass smtp.auth=CUSA124A263 smtp.mailfrom=groug@kaod.org
X-Mimecast-Spam-Score: 0
X-Mimecast-Originator: kaod.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When the IOTLB device is enabled, the vring addresses we get from
userspace are GIOVAs. It is thus wrong to pass them to vq_access_ok()
which only takes HVAs. The IOTLB map is likely empty at this stage,
so there isn't much that can be done with these GIOVAs. Access validation
will be performed at IOTLB prefetch time anyway.

BugLink: https://bugzilla.redhat.com/show_bug.cgi?id=1883084
Fixes: 6b1e6cc7855b ("vhost: new device IOTLB API")
Cc: jasowang@redhat.com
CC: stable@vger.kernel.org # 4.14+
Signed-off-by: Greg Kurz <groug@kaod.org>
---
 drivers/vhost/vhost.c |    5 ++++-
 1 file changed, 4 insertions(+), 1 deletion(-)

```
