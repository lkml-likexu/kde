#### [PATCH 1/3] KVM: nSVM: Check for CR0.CD and CR0.NW on VMRUN of nested guests
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11482483
Return-Path: <SRS0=jZn3=5Z=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0E11815AB
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Apr 2020 21:30:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E1E452083E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Apr 2020 21:30:52 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="P915doV1"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726973AbgDIVau (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 9 Apr 2020 17:30:50 -0400
Received: from aserp2120.oracle.com ([141.146.126.78]:36656 "EHLO
        aserp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726867AbgDIVau (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 9 Apr 2020 17:30:50 -0400
Received: from pps.filterd (aserp2120.oracle.com [127.0.0.1])
        by aserp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 039LNqQZ133444;
        Thu, 9 Apr 2020 21:30:48 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=corp-2020-01-29;
 bh=MKoaiJE892ogQi9MJkgkxyHIsK17J6JTkHiivbAxBmY=;
 b=P915doV1ZHqJfsq1FuIEpBmSZts5zY5W096kfiGt+NSG6UX5ExpMPmqgcR4awCh1YkfY
 0srVFQGBeL85IY3llLJ5k3/0hX56TxG6gdYDLUTVWa1WJvOSX6slTtHuzLm2C4X7pI4Z
 KQ0rtT0wM9F/0YY4fEpGZ1RR6MKpMmZJb/t/3vmi58suDJlWuWJuynnqX+xxWGxmZDwU
 vl5+wOnSwXEnmgfoJZ6/1X8I7Qus8cMfS4UW+RtNMsrID9WWUcIROB9ScrTMVZWPO8so
 V8dFTxc2wIl9TjvbCiDRhnell96KGxMvS18cP7CfWD4OS4WYIlxrhOWYx11PFdFPQKeY 7A==
Received: from aserp3030.oracle.com (aserp3030.oracle.com [141.146.126.71])
        by aserp2120.oracle.com with ESMTP id 3091m13x9d-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 09 Apr 2020 21:30:47 +0000
Received: from pps.filterd (aserp3030.oracle.com [127.0.0.1])
        by aserp3030.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 039LMolE003589;
        Thu, 9 Apr 2020 21:30:47 GMT
Received: from userv0122.oracle.com (userv0122.oracle.com [156.151.31.75])
        by aserp3030.oracle.com with ESMTP id 309ag5r05a-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 09 Apr 2020 21:30:47 +0000
Received: from abhmp0016.oracle.com (abhmp0016.oracle.com [141.146.116.22])
        by userv0122.oracle.com (8.14.4/8.14.4) with ESMTP id 039LUkQT024388;
        Thu, 9 Apr 2020 21:30:46 GMT
Received: from ban25x6uut29.us.oracle.com (/10.153.73.29)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Thu, 09 Apr 2020 14:30:46 -0700
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com
Subject: [PATCH 1/3] KVM: nSVM: Check for CR0.CD and CR0.NW on VMRUN of nested
 guests
Date: Thu,  9 Apr 2020 16:50:33 -0400
Message-Id: <20200409205035.16830-2-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20200409205035.16830-1-krish.sadhukhan@oracle.com>
References: <20200409205035.16830-1-krish.sadhukhan@oracle.com>
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9586
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 adultscore=1
 spamscore=0 malwarescore=0
 phishscore=0 mlxscore=0 bulkscore=0 mlxlogscore=959 suspectscore=1
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2003020000
 definitions=main-2004090151
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9586
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 adultscore=0
 mlxlogscore=999 mlxscore=0
 priorityscore=1501 phishscore=0 suspectscore=1 bulkscore=0
 lowpriorityscore=0 impostorscore=0 malwarescore=0 clxscore=1015
 spamscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2003020000 definitions=main-2004090151
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

According to section "Canonicalization and Consistency Checks" in APM vol. 2,
the following guest state combination is illegal:

	"CR0.CD is zero and CR0.NW is set"

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 arch/x86/kvm/svm/nested.c | 4 ++++
 1 file changed, 4 insertions(+)

```
#### [PATCH] KVM: SVM: Do not setup frame pointer in __svm_vcpu_run
##### From: Uros Bizjak <ubizjak@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Uros Bizjak <ubizjak@gmail.com>
X-Patchwork-Id: 11481665
Return-Path: <SRS0=jZn3=5Z=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 95AFF81
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Apr 2020 12:04:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 6B619208FE
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Apr 2020 12:04:51 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="LyKE1uLA"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726687AbgDIMEu (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 9 Apr 2020 08:04:50 -0400
Received: from mail-wr1-f67.google.com ([209.85.221.67]:37498 "EHLO
        mail-wr1-f67.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725971AbgDIMEt (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 9 Apr 2020 08:04:49 -0400
Received: by mail-wr1-f67.google.com with SMTP id w10so11639989wrm.4
        for <kvm@vger.kernel.org>; Thu, 09 Apr 2020 05:04:47 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=lCmPfTqm1cRtMIpvXq734SPUvTONQxpqo1sItgL7b4o=;
        b=LyKE1uLASPzUYs4GBcNp6r5h5YHAV2+DPhgSp5owG1mKLASYAvj0K/6/XGLWYj+ueC
         bPzhcZV40BHD59DIOki8xpnTLkDbNmVQkdl8zVyRD8SNO8TB69lfArzq/xpdDWxrkJTl
         kv+sArnR3jUnnLxlq01av6GlHGLZ5Uhe/Axq6Sfc3zVc5aUvkwis9errWskiyTwH0nha
         Sq0ZeUR4foe5hvgURdApv6TtaJV9ObwqlOceRyhgHfdaWKT414QUxjK5jfTt8UGofQTX
         tDWASp/CacC8RIPtD3Pa/kX8JIVEzBmCzL8fbDFDYmrtqiIHtPr2WiFFe6dNwnxBrGQu
         tbKA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=lCmPfTqm1cRtMIpvXq734SPUvTONQxpqo1sItgL7b4o=;
        b=jywSNMpyWrTbhRi16h2C26yzP3c8yF4LBNy+FeqVptEFDaHA3Qvlj3tN9iFnt+9wXU
         iVjaRcHXdr40lWFyF0PpgrppmykfPrTSmFoY9T2pkoRUXKIK2nzXQw0yEERZH03dN7tZ
         dJ3uoi9zOKFUrLGBOVbShtBTP5PP3aeF3pO3AGCNhGS3NhueUUmX01hS2iH8Dc/T9vrx
         aiWI6633ccTNAgaI6P+xQ/WnicMFFQdUuUQK73fA/wfMaKnsT3gber6dSoBGyfa49NKw
         ozp7rnRj421Utl9Patktb8BOKUduKlR0e6D4oYcn62UHK3N++Bc76xWq+wkqtG4tFdJi
         zHBw==
X-Gm-Message-State: AGi0PuZZUnWedOHe/WBkt4sDKzqrCSbMSreoddPUADCBxVOAiudorsVc
        /PMirJGwzYkXNvRbolB/mQSBxvRYC2k=
X-Google-Smtp-Source: 
 APiQypKOdYcsZ7tQmIT9Bg2GAIpd7YZFeplUbWXhnfvRK6Cb62GWg59W4mb0M2Hr44hx5k4YjxMJ9w==
X-Received: by 2002:adf:f8cd:: with SMTP id
 f13mr13466696wrq.119.1586433886815;
        Thu, 09 Apr 2020 05:04:46 -0700 (PDT)
Received: from localhost.localdomain (93-103-18-160.static.t-2.net.
 [93.103.18.160])
        by smtp.gmail.com with ESMTPSA id
 e5sm41110117wru.92.2020.04.09.05.04.45
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 09 Apr 2020 05:04:46 -0700 (PDT)
From: Uros Bizjak <ubizjak@gmail.com>
To: kvm@vger.kernel.org
Cc: Uros Bizjak <ubizjak@gmail.com>,
        Paolo Bonzini <pbonzini@redhat.com>
Subject: [PATCH] KVM: SVM: Do not setup frame pointer in __svm_vcpu_run
Date: Thu,  9 Apr 2020 14:04:40 +0200
Message-Id: <20200409120440.1427215-1-ubizjak@gmail.com>
X-Mailer: git-send-email 2.25.2
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

__svm_vcpu_run is a leaf function and does not need
a frame pointer.  %rbp is also destroyed a few instructions
later when guest registers are loaded.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Uros Bizjak <ubizjak@gmail.com>
---
 arch/x86/kvm/svm/vmenter.S | 1 -
 1 file changed, 1 deletion(-)

```
#### [PATCH] KVM: SVM: Fix __svm_vcpu_run declaration.
##### From: Uros Bizjak <ubizjak@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Uros Bizjak <ubizjak@gmail.com>
X-Patchwork-Id: 11481655
Return-Path: <SRS0=jZn3=5Z=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5A39781
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Apr 2020 11:49:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 381E420692
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Apr 2020 11:49:47 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="Wt/Hzy5j"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726718AbgDILtp (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 9 Apr 2020 07:49:45 -0400
Received: from mail-wm1-f66.google.com ([209.85.128.66]:53497 "EHLO
        mail-wm1-f66.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725971AbgDILtp (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 9 Apr 2020 07:49:45 -0400
Received: by mail-wm1-f66.google.com with SMTP id d77so3596769wmd.3
        for <kvm@vger.kernel.org>; Thu, 09 Apr 2020 04:49:44 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=NhCGDxyUnA14N2Q0P5fdjbo3qgE+I/ZWPpei6zT7QB8=;
        b=Wt/Hzy5jCHDeFSq6vISCyUT5iHJxSK17PQZZqlsUzoUhExC1Fwuj+ApvIcIogFgHpL
         ZtkhOUbflz/ISVh4fK/c0C/VQ2uwJD5YoFirHWxK5LVQbvwXCwSaCx/DTkB0l8yfI322
         J+6V/GTYl6ydXOqCcY4Jhh0AVlBEE7qjkyuM4Gd3s8ukJnXfmmh1i0BlNLtTJw0qD1Kv
         VCK97okxwa9Ii/6qReDouys5Otcvpid993rvMk+3d6cuNAcJjiKRSwiPF7bLiQMmZ0dH
         j2BnLWw5YBPnUyfuhAwIchy/awVZqD5u6Ur65P93e2u9PaXioxDpN3DbtDAMH1VgOl09
         7/Ug==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=NhCGDxyUnA14N2Q0P5fdjbo3qgE+I/ZWPpei6zT7QB8=;
        b=O3mh3pRGtNCxkpMCOWbauP9LqfdYYEDLGHTZqzilq5093IJRrTfBOaVOCEL9u/9dV2
         Q+YkzQFNw2eTy9eqs1GHfcueqb+62z2LMo+aoY7WEOjB1Fz7PfmzGlq1IZAQb7AhuLS8
         n65NCKQpUfaSjeN/AFHzfF7mvepTady6THAr0wRj4FQ13Of2MTDczzMjDHZxgZAZMRZ/
         PMEX7iBFjsurAMvNEhGUSLddNN2S8f5mIXdDChrZEemwSfkA1cR3AOHhyvl46o/Pk+uH
         bpuWOwnUe4YJcL6e9fJFCjBFtkMsBd+xGUEwR8PQo1J4YKGbGi9+vp4+w5lKO14A2FJP
         mYlQ==
X-Gm-Message-State: AGi0PuYOCBpcP2KhChQQ/NcMmtrQptezlnaxSxHplAAPM9ks3LNgtvvu
        BJhVYSLqt22cdiLuqa0Kedc412EGfTo=
X-Google-Smtp-Source: 
 APiQypKJ8z1OULVyZ3EW0TYT0OeWR4FPQQ5SvOB/2bf8DqgA1qZabS+lbTNx7l/55WwXFC7y5q4Fpg==
X-Received: by 2002:a1c:2b43:: with SMTP id r64mr10009732wmr.77.1586432983984;
        Thu, 09 Apr 2020 04:49:43 -0700 (PDT)
Received: from localhost.localdomain (93-103-18-160.static.t-2.net.
 [93.103.18.160])
        by smtp.gmail.com with ESMTPSA id
 e23sm29884251wra.43.2020.04.09.04.49.42
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 09 Apr 2020 04:49:43 -0700 (PDT)
From: Uros Bizjak <ubizjak@gmail.com>
To: kvm@vger.kernel.org
Cc: Uros Bizjak <ubizjak@gmail.com>,
        Paolo Bonzini <pbonzini@redhat.com>
Subject: [PATCH] KVM: SVM: Fix __svm_vcpu_run declaration.
Date: Thu,  9 Apr 2020 13:49:26 +0200
Message-Id: <20200409114926.1407442-1-ubizjak@gmail.com>
X-Mailer: git-send-email 2.25.2
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The function returns no value.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Fixes: 199cd1d7b534 ("KVM: SVM: Split svm_vcpu_run inline assembly to separate file")
Signed-off-by: Uros Bizjak <ubizjak@gmail.com>
---
 arch/x86/kvm/svm/svm.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH kvm-unit-tests] svm: add a test for exception injection
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11481505
Return-Path: <SRS0=jZn3=5Z=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 675A9912
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Apr 2020 09:43:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4758E221F9
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Apr 2020 09:43:13 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="ZE+i++rr"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726702AbgDIJnL (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 9 Apr 2020 05:43:11 -0400
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:20578 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726641AbgDIJnK (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 9 Apr 2020 05:43:10 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1586425390;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc; bh=6HrPdKOboS5D7jfHW3vNq4Ok66KCGk2a1g+aL7G4Ud4=;
        b=ZE+i++rrfOaru4g3uNjwX23qY1rdgyaR6QMQzU+j5yDx33yW4tE4qxtDM/0/F+hULJmVeq
        pH38+cLM8nxpSK+dQJm0ufXhVa/CYRszDqvkhYm3W5IGGq+xrNGFmXojtjMn3DX+iAp0+f
        44LHKMIpmqP3Jw6RZAQa5TfnoneV8vE=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-256-T0cC7uQ5O9GPPxJA6lkQjQ-1; Thu, 09 Apr 2020 05:43:05 -0400
X-MC-Unique: T0cC7uQ5O9GPPxJA6lkQjQ-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id BA8F813F9
        for <kvm@vger.kernel.org>; Thu,  9 Apr 2020 09:43:04 +0000 (UTC)
Received: from virtlab511.virt.lab.eng.bos.redhat.com
 (virtlab511.virt.lab.eng.bos.redhat.com [10.19.152.198])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 66E4B11481A
        for <kvm@vger.kernel.org>; Thu,  9 Apr 2020 09:43:04 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: kvm@vger.kernel.org
Subject: [PATCH kvm-unit-tests] svm: add a test for exception injection
Date: Thu,  9 Apr 2020 05:43:03 -0400
Message-Id: <20200409094303.949992-1-pbonzini@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Cover VMRUN's testing whether EVENTINJ.TYPE = 3 (exception) has been specified with
a vector that does not correspond to an exception.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 x86/svm.h       |  7 +++++
 x86/svm_tests.c | 70 +++++++++++++++++++++++++++++++++++++++++++++++++
 2 files changed, 77 insertions(+)

```
#### [PATCH kvm-unit-tests v2 1/2] svm: Add test cases around NMI injection
##### From: Cathy Avery <cavery@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Cathy Avery <cavery@redhat.com>
X-Patchwork-Id: 11481915
Return-Path: <SRS0=jZn3=5Z=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0CF101392
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Apr 2020 15:28:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E0FE12074F
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Apr 2020 15:28:57 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="NgToxMWo"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728224AbgDIP24 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 9 Apr 2020 11:28:56 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:42115 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1728191AbgDIP24 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 9 Apr 2020 11:28:56 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1586446135;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=FVUPLOZX5xr5YRaXLAPd3Mgvd0RbL/KcfmZ9/KPlJrk=;
        b=NgToxMWoDxquJtCt9ZqGYLIL++6Wf6zj/mN5RfELLUDfhfsQmzD/jEoTXkoQta+Tq20Bvv
        kUyqWKqAYdp0eF9AZ6TuipwUOTp4pTYnZRl+qJ59UXic0gA70GYm+ReDjYZsmoPPFI9W8P
        nZeuqlZgmOCP1sIljXtzeymeC2MRNPM=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-46-PwF-f56YN3S6QN6_21pWOg-1; Thu, 09 Apr 2020 11:28:50 -0400
X-MC-Unique: PwF-f56YN3S6QN6_21pWOg-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 46B93107ACC4
        for <kvm@vger.kernel.org>; Thu,  9 Apr 2020 15:28:49 +0000 (UTC)
Received: from localhost.localdomain.com (ovpn-113-69.rdu2.redhat.com
 [10.10.113.69])
        by smtp.corp.redhat.com (Postfix) with ESMTP id CED735D9CA;
        Thu,  9 Apr 2020 15:28:48 +0000 (UTC)
From: Cathy Avery <cavery@redhat.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com
Subject: [PATCH kvm-unit-tests v2 1/2] svm: Add test cases around NMI
 injection
Date: Thu,  9 Apr 2020 11:28:48 -0400
Message-Id: <20200409152848.17762-1-cavery@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This test checks for NMI delivery to L2 and
intercepted NMI (VMEXIT_NMI) delivery to L1.

Signed-off-by: Cathy Avery <cavery@redhat.com>
---
v2: Remove redundant NMI_VECTOR
---
 x86/svm_tests.c | 82 +++++++++++++++++++++++++++++++++++++++++++++++++
 1 file changed, 82 insertions(+)

```
#### [PATCH v5 1/2] selftests: kvm: Add vm_get_fd() in kvm_util
##### From: Wainer dos Santos Moschetta <wainersm@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wainer dos Santos Moschetta <wainersm@redhat.com>
X-Patchwork-Id: 11482527
Return-Path: <SRS0=jZn3=5Z=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 26E5692A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Apr 2020 22:09:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 06AC62084D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Apr 2020 22:09:26 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="dlCID5rM"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726977AbgDIWJW (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 9 Apr 2020 18:09:22 -0400
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:57620 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726713AbgDIWJW (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 9 Apr 2020 18:09:22 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1586470161;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:in-reply-to:in-reply-to:references:references;
        bh=YBQ+zxeaLD0yw/RzmwmvvS9Gvxa0mxHzlEt+c4z9U6U=;
        b=dlCID5rMz2icPvp7qB96Tv1qC16xZHq9yrzWsln//97PN1Z72wL5864uy5aGMXfSeeGBEd
        YaZnWFp1zzLRelXPKPrIXoLPJ8b+F7GVpNGaU12MS7QQ48dv4s8w+t64ui8cz40VSgIWdc
        gfftQlTEXvhCtIoqDa5c4sS65dTUcFw=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-297-pjkdSrLXN1O_qtpWNWJNfg-1; Thu, 09 Apr 2020 18:09:20 -0400
X-MC-Unique: pjkdSrLXN1O_qtpWNWJNfg-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id BD5C613FD;
        Thu,  9 Apr 2020 22:09:18 +0000 (UTC)
Received: from localhost.localdomain (ovpn-116-15.gru2.redhat.com
 [10.97.116.15])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 6A6A59D348;
        Thu,  9 Apr 2020 22:09:15 +0000 (UTC)
From: Wainer dos Santos Moschetta <wainersm@redhat.com>
To: pbonzini@redhat.com, kvm@vger.kernel.org
Cc: drjones@redhat.com, david@redhat.com, linux-kernel@vger.kernel.org,
        linux-kselftest@vger.kernel.org, krish.sadhukhan@oracle.com
Subject: [PATCH v5 1/2] selftests: kvm: Add vm_get_fd() in kvm_util
Date: Thu,  9 Apr 2020 19:09:04 -0300
Message-Id: <20200409220905.26573-2-wainersm@redhat.com>
In-Reply-To: <20200409220905.26573-1-wainersm@redhat.com>
References: <20200409220905.26573-1-wainersm@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Introduces the vm_get_fd() function in kvm_util which returns
the VM file descriptor.

Reviewed-by: Andrew Jones <drjones@redhat.com>
Signed-off-by: Wainer dos Santos Moschetta <wainersm@redhat.com>
---
 tools/testing/selftests/kvm/include/kvm_util.h | 1 +
 tools/testing/selftests/kvm/lib/kvm_util.c     | 5 +++++
 2 files changed, 6 insertions(+)

```
#### [PATCH kvm-unit-tests 1/2] svm: Add test cases around NMI injection
##### From: Cathy Avery <cavery@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Cathy Avery <cavery@redhat.com>
X-Patchwork-Id: 11481795
Return-Path: <SRS0=jZn3=5Z=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1A24D913
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Apr 2020 13:33:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id EE4BB20857
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Apr 2020 13:33:00 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="aXmWZf5S"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726872AbgDINc7 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 9 Apr 2020 09:32:59 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:36514 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726641AbgDINc7 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 9 Apr 2020 09:32:59 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1586439178;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=woDbbnutdla08US4iOa0Wjr9OpIuMoISMvO6V9wkEkM=;
        b=aXmWZf5Ss2u8RAwLIQLDaUuc+mzQlXIbzlpmIU3w26vIu5Gzlm3/E7Z9oAzCDnV9Me9x1e
        Hh3NSloOMKGD3J/mL+N336uozt3Tzygtx/PD3zRZLUxSg7nzk8C3s7Kn571+mnrw9Ta/CK
        sE7ksVYoCP8yewER+wZZFLQRLwuqjbQ=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-479-ZWniwjOnMzK2rhNlAHaVIQ-1; Thu, 09 Apr 2020 09:32:50 -0400
X-MC-Unique: ZWniwjOnMzK2rhNlAHaVIQ-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 8EBC618FF661
        for <kvm@vger.kernel.org>; Thu,  9 Apr 2020 13:32:49 +0000 (UTC)
Received: from localhost.localdomain.com (ovpn-113-69.rdu2.redhat.com
 [10.10.113.69])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 18F4F10027AC;
        Thu,  9 Apr 2020 13:32:49 +0000 (UTC)
From: Cathy Avery <cavery@redhat.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com
Subject: [PATCH kvm-unit-tests 1/2] svm: Add test cases around NMI injection
Date: Thu,  9 Apr 2020 09:32:46 -0400
Message-Id: <20200409133247.16653-2-cavery@redhat.com>
In-Reply-To: <20200409133247.16653-1-cavery@redhat.com>
References: <20200409133247.16653-1-cavery@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This test checks for NMI delivery to L2 and
intercepted NMI (VMEXIT_NMI) delivery to L1.

Signed-off-by: Cathy Avery <cavery@redhat.com>
---
 x86/svm_tests.c | 84 +++++++++++++++++++++++++++++++++++++++++++++++++
 1 file changed, 84 insertions(+)

```
#### [PATCH v1 1/1] x86/kvm/hyper-v: Add support to SYNIC exit on EOM
##### From: Jon Doron <arilou@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jon Doron <arilou@gmail.com>
X-Patchwork-Id: 11481989
Return-Path: <SRS0=jZn3=5Z=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1D33714B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Apr 2020 16:38:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E8DFB2082D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Apr 2020 16:38:06 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="Qzd7vNCx"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727703AbgDIQiG (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 9 Apr 2020 12:38:06 -0400
Received: from mail-wr1-f66.google.com ([209.85.221.66]:43149 "EHLO
        mail-wr1-f66.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726650AbgDIQiF (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 9 Apr 2020 12:38:05 -0400
Received: by mail-wr1-f66.google.com with SMTP id i10so6352048wrv.10;
        Thu, 09 Apr 2020 09:38:03 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=FZy/hx0dFV0MlwQD6zEDjIMh7JIfKHthxPFBWJ2qd2A=;
        b=Qzd7vNCx8chriIimQXaA03B4sENJuQOERkd2pFIPxM9PZrSPptuV/IwwWbiVO+r2H2
         ab+m2fr3UVLhHzx6eFE5CRBScgS+r0YuPTRwIWu7q2NMN3QTJpkh848y8LX0d3897cV3
         IVu0C9l9OmyVfj2l4Gik6ddweXHzFsolwQ9cj8xX3gIrcscVZCR9tek1RdZI6MvYUagd
         ucaGtRefbjJVY9XhyIWKl5dio1kwCPJq3Vo0OQtzUUi13mLKac3twZOnm22e++i1/Pd6
         wd+IoqraBbdX3vjglC9E4CKbc6AWvsyQzMi6S2WEQqM23c2dw93zTDtRL92Y7J0HYunX
         N7sw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=FZy/hx0dFV0MlwQD6zEDjIMh7JIfKHthxPFBWJ2qd2A=;
        b=OTWTQvpnhO8GkwokncMs7mzO8+grsOVDvJ/+r0CIY3FLJXjp6uVHj46kWAbSkWyAq4
         F+j0f/UyT2Dw3omR7mtLazCxzHigiGBYmwwhO+9bXxIi5VKXvVLdbH9FxfHrd05RGztC
         gyH72AC6+6gTw+8G3eEcf1DkiAcQuZwQuuM1IKb2bZ2pKn5RZYtcugp80YrRJfmKpQmZ
         h+s5LVGhM+/HbIwHggPS5In98bz6jNXVOK8ZkD78cQy+ayUbgUKgATpcMpgo6f2IxuGs
         zTAVuRJSnAGwZt6a71fu4Pk3XNluf0EPoT0R9bqqnlGamdVTKPrkh5go0ryhvMjp38Dl
         7Pdw==
X-Gm-Message-State: AGi0PuYE/Tai0UOvGP/lVotwcDRNWrsXUdhFhHQ8M64aosXZUDgXb0Wg
        uVCDwsFFIjjsrFS4myqMwwzeI1Ts7JlpMg==
X-Google-Smtp-Source: 
 APiQypKVQf2ccgkskFm0DByLZ6M5DU5iVXnGIoTyDMgIA0r+ZdYUN3v+CFSTlU0/ww2e2DLOvyILOg==
X-Received: by 2002:adf:9e8c:: with SMTP id
 a12mr14662907wrf.273.1586450282847;
        Thu, 09 Apr 2020 09:38:02 -0700 (PDT)
Received: from jondnuc.lan (IGLD-84-229-155-55.inter.net.il. [84.229.155.55])
        by smtp.gmail.com with ESMTPSA id
 f16sm4239240wmc.37.2020.04.09.09.38.01
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 09 Apr 2020 09:38:02 -0700 (PDT)
From: Jon Doron <arilou@gmail.com>
To: kvm@vger.kernel.org, linux-hyperv@vger.kernel.org
Cc: vkuznets@redhat.com, Jon Doron <arilou@gmail.com>
Subject: [PATCH v1 1/1] x86/kvm/hyper-v: Add support to SYNIC exit on EOM
Date: Thu,  9 Apr 2020 19:37:45 +0300
Message-Id: <20200409163745.573547-2-arilou@gmail.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20200409163745.573547-1-arilou@gmail.com>
References: <20200409163745.573547-1-arilou@gmail.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

According to the TLFS a write to the EOM register by the guest
causes the hypervisor to scan for any pending messages and if there
are any it will try to deliver them.

To do this we must exit so any pending messages can be written.

Signed-off-by: Jon Doron <arilou@gmail.com>
---
 arch/x86/include/asm/kvm_host.h |  1 +
 arch/x86/kvm/hyperv.c           | 65 +++++++++++++++++++++++++++++----
 arch/x86/kvm/hyperv.h           |  1 +
 arch/x86/kvm/x86.c              |  5 +++
 include/uapi/linux/kvm.h        |  1 +
 5 files changed, 65 insertions(+), 8 deletions(-)

```
