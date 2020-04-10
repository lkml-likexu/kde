

#### [PATCH kvm-unit-tests 0/2] svm: NMI injection and HLT tests
##### From: Cathy Avery <cavery@redhat.com>

```c
From patchwork Thu Apr  9 13:32:45 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Cathy Avery <cavery@redhat.com>
X-Patchwork-Id: 11481793
Return-Path: <SRS0=jZn3=5Z=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 187B292A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Apr 2020 13:32:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id EB2F120857
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Apr 2020 13:32:53 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="VokTll+q"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726597AbgDINcw (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 9 Apr 2020 09:32:52 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:44460 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726552AbgDINcw (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 9 Apr 2020 09:32:52 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1586439172;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=1rsPbNYR0vQvYBWNFefGkmqQV/ZkHcmo1vgmZC2vNyk=;
        b=VokTll+qLK31CtWc91+0MNBXBvaes3IK+Q8NbWei76/4q9S69WO6FH6cp761+ppBstIhmi
        jjYtpqluICe3KyuueoPJ0KJlKlyno15cXhTFLGDRLiM4uWLCYeur9uLIbd7ZNgOBrgh8oi
        K3Gyd75MN1NcXPltEst0dHu5q224wx8=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-431-MCxFUsmWO2u2PovlGx0EFw-1; Thu, 09 Apr 2020 09:32:49 -0400
X-MC-Unique: MCxFUsmWO2u2PovlGx0EFw-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id E81698017F6
        for <kvm@vger.kernel.org>; Thu,  9 Apr 2020 13:32:48 +0000 (UTC)
Received: from localhost.localdomain.com (ovpn-113-69.rdu2.redhat.com
 [10.10.113.69])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 7317110027AC;
        Thu,  9 Apr 2020 13:32:48 +0000 (UTC)
From: Cathy Avery <cavery@redhat.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com
Subject: [PATCH kvm-unit-tests 0/2] svm: NMI injection and HLT tests
Date: Thu,  9 Apr 2020 09:32:45 -0400
Message-Id: <20200409133247.16653-1-cavery@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Patch 1 is NMI injection and intercept. Patch 2 is the same test with guest in
HLT.

Cathy Avery (2):
  svm: Add test cases around NMI injection
  svm: Add test cases around NMI injection with HLT

 x86/svm_tests.c | 187 ++++++++++++++++++++++++++++++++++++++++++++++++
 1 file changed, 187 insertions(+)
```
#### [PATCH v1 0/1] x86/kvm/hyper-v: Add support to SYNIC exit on EOM
##### From: Jon Doron <arilou@gmail.com>

```c
From patchwork Thu Apr  9 16:37:44 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jon Doron <arilou@gmail.com>
X-Patchwork-Id: 11481987
Return-Path: <SRS0=jZn3=5Z=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5654E1392
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Apr 2020 16:38:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 373CF20771
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Apr 2020 16:38:05 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="Pu1D2EHm"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727612AbgDIQiD (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 9 Apr 2020 12:38:03 -0400
Received: from mail-wr1-f45.google.com ([209.85.221.45]:45126 "EHLO
        mail-wr1-f45.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726837AbgDIQiD (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 9 Apr 2020 12:38:03 -0400
Received: by mail-wr1-f45.google.com with SMTP id v5so12635084wrp.12;
        Thu, 09 Apr 2020 09:38:02 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=4AVcBDvhexR6mBdaQRyvT90vU+CQBIsl+K2COSOrYtw=;
        b=Pu1D2EHmyzcO/fceKBaMG8H2e5Wke+nExGr58gOz3gL1VCXd2kHRJUlHwmG30idKq4
         Msev0hZ72tccRypTtonEje+v4tLDOwUlArXFv757tqPLIJj4lZS7QktYEyyXdi+HnohG
         HF93IYNB0ifQR2rwJCuHni8uGvbT1qfSqnF1mUcbskihk7TYDWih5XItXZq6OtnkqB2d
         Nc2wrxauVwUxQKJ7Dg87E41z6f0rIA6cLQZQ3k1izJ0l44UAKD5YygSX9AjiTtRjG0u7
         ZntL6zH30Z+HlKbDqevKXMe4QCX9eFtZ4cKkhSigTaSw6rHbCIOt8Epj8EKEizzq+Q7m
         v4aA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=4AVcBDvhexR6mBdaQRyvT90vU+CQBIsl+K2COSOrYtw=;
        b=d1rillUwoiofFsvUl3NKhURyzM312n8hKFDaLlB2XPbYp8iPCxBySzA2gycStHhUKQ
         ThWIao/L4gRmQsDVCeUbzzMHgO3KwwrcLHovpZZYoT8enKwRqU6L8dx5EW8M8ZuWNXtS
         OpiWCTxE1LDxlneTxEuerhl17/YNtUNA49jR9HGpGXuFegiyNGqJO154kVl5WaNEdHWx
         UhVf+HLS+PfAxqKrfjA6nKb2Xog8f+QgzrM9c7zYDQns9gtcMQsWY+xApMyG5wnzvnoI
         mLBgq7PHVt3EfMQr0n3SDE94LLhxJy0fz1KAuOpRlUiiIIJEeBD8hD+cbVdyAG99bVMv
         7fzw==
X-Gm-Message-State: AGi0PuZKTYsX8w3Whoj6dguP2OFUSqAktGghr8KOtLKxpyk3O3ZK0Qvc
        AfF9jmA6RS85pxU1VHtA+tgK+XeI1ZpyLQ==
X-Google-Smtp-Source: 
 APiQypL7HW3KK+VyLASTjR2EDm47BhJ5WgxYBASliRtC0CvhqdVbf4AWEZNPJdFhKJQDme6e3ydUgQ==
X-Received: by 2002:adf:fa4f:: with SMTP id y15mr44534wrr.118.1586450281881;
        Thu, 09 Apr 2020 09:38:01 -0700 (PDT)
Received: from jondnuc.lan (IGLD-84-229-155-55.inter.net.il. [84.229.155.55])
        by smtp.gmail.com with ESMTPSA id
 f16sm4239240wmc.37.2020.04.09.09.38.00
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 09 Apr 2020 09:38:01 -0700 (PDT)
From: Jon Doron <arilou@gmail.com>
To: kvm@vger.kernel.org, linux-hyperv@vger.kernel.org
Cc: vkuznets@redhat.com, Jon Doron <arilou@gmail.com>
Subject: [PATCH v1 0/1] x86/kvm/hyper-v: Add support to SYNIC exit on EOM
Date: Thu,  9 Apr 2020 19:37:44 +0300
Message-Id: <20200409163745.573547-1-arilou@gmail.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

According to the TLFS:
"A write to the end of message (EOM) register by the guest causes the
hypervisor to scan the internal message buffer queue(s) associated with
the virtual processor.

If a message buffer queue contains a queued message buffer, the hypervisor
attempts to deliver the message.

Message delivery succeeds if the SIM page is enabled and the message slot
corresponding to the SINTx is empty (that is, the message type in the
header is set to HvMessageTypeNone).
If a message is successfully delivered, its corresponding internal message
buffer is dequeued and marked free.
If the corresponding SINTx is not masked, an edge-triggered interrupt is
delivered (that is, the corresponding bit in the IRR is set).

This register can be used by guests to poll for messages. It can also be
used as a way to drain the message queue for a SINTx that has
been disabled (that is, masked)."

So basically this means that we need to exit on EOM so the hypervisor
will have a chance to send all the pending messages regardless of the
SCONTROL mechnaisim.

Jon Doron (1):
  x86/kvm/hyper-v: Add support to SYNIC exit on EOM

 arch/x86/include/asm/kvm_host.h |  1 +
 arch/x86/kvm/hyperv.c           | 65 +++++++++++++++++++++++++++++----
 arch/x86/kvm/hyperv.h           |  1 +
 arch/x86/kvm/x86.c              |  5 +++
 include/uapi/linux/kvm.h        |  1 +
 5 files changed, 65 insertions(+), 8 deletions(-)
```
#### [PATCH 0/3] KVM: nSVM: Check CR0.CD and CR0.NW on VMRUN of nested
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
From patchwork Thu Apr  9 20:50:32 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11482479
Return-Path: <SRS0=jZn3=5Z=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8643F14B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Apr 2020 21:30:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 609ED2083E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Apr 2020 21:30:51 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="esnhiLRd"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726928AbgDIVau (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 9 Apr 2020 17:30:50 -0400
Received: from userp2130.oracle.com ([156.151.31.86]:53134 "EHLO
        userp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726806AbgDIVat (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 9 Apr 2020 17:30:49 -0400
Received: from pps.filterd (userp2130.oracle.com [127.0.0.1])
        by userp2130.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 039LOSd9023082;
        Thu, 9 Apr 2020 21:30:47 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : mime-version : content-transfer-encoding;
 s=corp-2020-01-29; bh=+KL6ijpPOJ6Ij2K5bOtSEem/97JNwCGEfRxIViHvcJ8=;
 b=esnhiLRdiK1jwlTUPOLFn37iK3SXKbwECdmEoBOiaz6ltWF7ftkM8s9gwqn6VMHmUFGu
 nryMJ9Ku0L2mCvHrMRW21APWfecxabHYmA/ckeAAg+l59W1NJ8KYu8nBVpF0/FOekKx/
 xf6asiQMMbz/PRaHbl+Dj34t6820XQKMcEnpI6PSFF1eO+7qaKZGT1TVJVZOfRWpg12G
 ydH9UlS85XJ36TE3NHYZAIZERPa0Zz2vQ5PArp0vEYAPPyrjt/wWeDLeWTQXJg2ZHcUx
 0PIfHwysgpkSzv8OB/XStkKe2YL4EJr5y27Ht3OlfCHr6WCsEgpu8qr+lMot7xDpKQLP 7Q==
Received: from userp3020.oracle.com (userp3020.oracle.com [156.151.31.79])
        by userp2130.oracle.com with ESMTP id 3091m3kwv6-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 09 Apr 2020 21:30:47 +0000
Received: from pps.filterd (userp3020.oracle.com [127.0.0.1])
        by userp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 039LMeCl067938;
        Thu, 9 Apr 2020 21:30:47 GMT
Received: from aserv0121.oracle.com (aserv0121.oracle.com [141.146.126.235])
        by userp3020.oracle.com with ESMTP id 309gdcvrvs-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 09 Apr 2020 21:30:46 +0000
Received: from abhmp0016.oracle.com (abhmp0016.oracle.com [141.146.116.22])
        by aserv0121.oracle.com (8.14.4/8.13.8) with ESMTP id 039LUjMg031367;
        Thu, 9 Apr 2020 21:30:45 GMT
Received: from ban25x6uut29.us.oracle.com (/10.153.73.29)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Thu, 09 Apr 2020 14:30:45 -0700
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com
Subject: [PATCH 0/3] KVM: nSVM: Check CR0.CD and CR0.NW on VMRUN of nested
 guests
Date: Thu,  9 Apr 2020 16:50:32 -0400
Message-Id: <20200409205035.16830-1-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9586
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 mlxlogscore=473
 malwarescore=0
 adultscore=0 mlxscore=0 spamscore=0 bulkscore=0 phishscore=0
 suspectscore=1 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2003020000 definitions=main-2004090151
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9586
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 spamscore=0
 adultscore=0
 impostorscore=0 malwarescore=0 lowpriorityscore=0 mlxlogscore=550
 priorityscore=1501 clxscore=1015 bulkscore=0 phishscore=0 mlxscore=0
 suspectscore=1 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2003020000 definitions=main-2004090151
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Patch# 1: Adds the KVM check.
Patch# 2: Adds the required #defines for the two CR0 bits.
Patch# 3: Adds the kvm-unit-test

[PATCH 1/3] KVM: nSVM: Check for CR0.CD and CR0.NW on VMRUN of nested guests
[PATCH 2/3] kvm-unit-tests: SVM: Add #defines for CR0.CD and CR0.NW
[PATCH 3/3] kvm-unit-tests: nSVM: Test CR0.CD and CR0.NW combination on VMRUN of

 arch/x86/kvm/svm/nested.c | 4 ++++
 1 file changed, 4 insertions(+)

Krish Sadhukhan (1):
      nSVM: Check for CR0.CD and CR0.NW on VMRUN of nested guests

 lib/x86/processor.h |  2 ++
 x86/svm_tests.c     | 28 +++++++++++++++++++++++++++-
 2 files changed, 29 insertions(+), 1 deletion(-)

Krish Sadhukhan (2):
      SVM: Add #defines for CR0.CD and CR0.NW
      nSVM: Test CR0.CD and CR0.NW combination on VMRUN of nested guests
```
#### [PATCH v5 0/2] selftests: kvm: Introduce the mem_slot_test test
##### From: Wainer dos Santos Moschetta <wainersm@redhat.com>

```c
From patchwork Thu Apr  9 22:09:03 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wainer dos Santos Moschetta <wainersm@redhat.com>
X-Patchwork-Id: 11482535
Return-Path: <SRS0=jZn3=5Z=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4BE9792A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Apr 2020 22:09:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 2D03C208E4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Apr 2020 22:09:35 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="RWFHgXcA"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726930AbgDIWJV (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 9 Apr 2020 18:09:21 -0400
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:57702 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726797AbgDIWJU (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 9 Apr 2020 18:09:20 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1586470160;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc; bh=d0YWsJp6o5xV2UL2uS6Ygl+hmCi+0Eyl441GMe3mK+4=;
        b=RWFHgXcAGp5D+FvzAq++KyZR7mp8T7f/a3kqnWF7LrlucDHbL/imgjyMtjLdldjizFSjcs
        XBc3aLa3691AdCmlbrBOvJzHxMeq5wwicWCSoriUnEBynCsG8Ploi1hLcNXdeYa1PpNZER
        vNfiJEkxMhnYZJYoxlRuAfU0MLIgaqc=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-475-GMJ2DFMMM52FoRdkcOgzgg-1; Thu, 09 Apr 2020 18:09:15 -0400
X-MC-Unique: GMJ2DFMMM52FoRdkcOgzgg-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id B06421007268;
        Thu,  9 Apr 2020 22:09:14 +0000 (UTC)
Received: from localhost.localdomain (ovpn-116-15.gru2.redhat.com
 [10.97.116.15])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 983379D348;
        Thu,  9 Apr 2020 22:09:08 +0000 (UTC)
From: Wainer dos Santos Moschetta <wainersm@redhat.com>
To: pbonzini@redhat.com, kvm@vger.kernel.org
Cc: drjones@redhat.com, david@redhat.com, linux-kernel@vger.kernel.org,
        linux-kselftest@vger.kernel.org, krish.sadhukhan@oracle.com
Subject: [PATCH v5 0/2] selftests: kvm: Introduce the mem_slot_test test
Date: Thu,  9 Apr 2020 19:09:03 -0300
Message-Id: <20200409220905.26573-1-wainersm@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series introduces a new KVM selftest (mem_slot_test) that goal
is to verify memory slots can be added up to the maximum allowed. An
extra slot is attempted which should occur on error.

The patch 01 is needed so that the VM fd can be accessed from the
test code (for the ioctl call attempting to add an extra slot).

I ran the test successfully on x86_64, aarch64, and s390x.  This
is why it is enabled to build on those arches.

- Changelog -

v4 -> v5:
 - Initialize the guest_addr and mem_reg_size variables on definition
   [krish.sadhukhan]

v3 -> v4:
 - Discarded mem_reg_flags variable. Simply using 0 instead [drjones]
 - Discarded kvm_region pointer. Instead passing a compound literal in
   the ioctl [drjones]
 - All variables are declared on the declaration block [drjones]

v2 -> v3:
 - Keep alphabetical order of .gitignore and Makefile [drjones]
 - Use memory region flags equals to zero [drjones]
 - Changed mmap() assert from 'mem != NULL' to 'mem != MAP_FAILED' [drjones]
 - kvm_region is declared along side other variables and malloc()'ed
   later [drjones]
 - Combined two asserts into a single 'ret == -1 && errno == EINVAL'
   [drjones]

v1 -> v2:
 - Rebased to queue
 - vm_get_fd() returns int instead of unsigned int (patch 01) [drjones]
 - Removed MEM_REG_FLAGS and GUEST_VM_MODE defines [drjones]
 - Replaced DEBUG() with pr_info() [drjones]
 - Calculate number of guest pages with vm_calc_num_guest_pages()
   [drjones]
 - Using memory region of 1 MB sized (matches mininum needed
   for s390x)
 - Removed the increment of guest_addr after the loop [drjones]
 - Added assert for the errno when adding a slot beyond-the-limit [drjones]
 - Prefer KVM_MEM_READONLY flag but on s390x it switch to KVM_MEM_LOG_DIRTY_PAGES,
   so ensure the coverage of both flags. Also somewhat tests the KVM_CAP_READONLY_MEM capability check [drjones]
 - Moved the test logic to test_add_max_slots(), this allows to more easily add new cases in the "suite".

v1: https://lore.kernel.org/kvm/20200330204310.21736-1-wainersm@redhat.com

Wainer dos Santos Moschetta (2):
  selftests: kvm: Add vm_get_fd() in kvm_util
  selftests: kvm: Add mem_slot_test test

 tools/testing/selftests/kvm/.gitignore        |  1 +
 tools/testing/selftests/kvm/Makefile          |  3 +
 .../testing/selftests/kvm/include/kvm_util.h  |  1 +
 tools/testing/selftests/kvm/lib/kvm_util.c    |  5 ++
 tools/testing/selftests/kvm/mem_slot_test.c   | 69 +++++++++++++++++++
 5 files changed, 79 insertions(+)
 create mode 100644 tools/testing/selftests/kvm/mem_slot_test.c
```
