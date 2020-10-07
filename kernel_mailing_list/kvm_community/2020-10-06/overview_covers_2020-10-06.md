

#### [PATCH 0/4 v3] KVM: nSVM: Add checks for CR3 and CR4 reserved bits to
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
From patchwork Tue Oct  6 19:06:50 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11819077
Return-Path: <SRS0=4WRu=DN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2BEE259D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  6 Oct 2020 19:07:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id F2FF5206B5
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  6 Oct 2020 19:07:10 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="mVAQDFa7"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727010AbgJFTHJ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 6 Oct 2020 15:07:09 -0400
Received: from userp2120.oracle.com ([156.151.31.85]:57530 "EHLO
        userp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727005AbgJFTHJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 6 Oct 2020 15:07:09 -0400
Received: from pps.filterd (userp2120.oracle.com [127.0.0.1])
        by userp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 096IxQOq088675;
        Tue, 6 Oct 2020 19:07:04 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id; s=corp-2020-01-29;
 bh=ndSK4g9KZoHOQRn8n6rYfB8krcATpjQavrXaq/WBQRQ=;
 b=mVAQDFa7oxkodt+nctOuWNww57z0WutnQeig/T4AUJJ0dnn7LWchMAFg6TKmXq6xAVsZ
 8pDSVoVTNH6aUe8fh0YcSYmt1lki3qTNnePSKEqVT4Z/0q7cssmI39FrLhMwKVDf/2rd
 eO8FqhnMc6rzb7X7LPsgRUZ0T23x2YWNZRaUAXlDufHZgrt19Y50zLxBaZSZaWjfogxV
 tRwpO54yX+i8Xb8vCnr1VgzOzVcf6AKqgqgb+ZS0CWBQZCtFwwbUXPpWwD836HcHU6hD
 LIk0lmXg2pcde1F49CtBc+43dsLfAc6iZrxQLIDPYp/OEg5mqOKItbb00D2lwtDBVONp Yw==
Received: from aserp3030.oracle.com (aserp3030.oracle.com [141.146.126.71])
        by userp2120.oracle.com with ESMTP id 33xhxmwuqc-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=FAIL);
        Tue, 06 Oct 2020 19:07:04 +0000
Received: from pps.filterd (aserp3030.oracle.com [127.0.0.1])
        by aserp3030.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 096J1HiI134063;
        Tue, 6 Oct 2020 19:07:04 GMT
Received: from userv0122.oracle.com (userv0122.oracle.com [156.151.31.75])
        by aserp3030.oracle.com with ESMTP id 33y2vnep17-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 06 Oct 2020 19:07:04 +0000
Received: from abhmp0015.oracle.com (abhmp0015.oracle.com [141.146.116.21])
        by userv0122.oracle.com (8.14.4/8.14.4) with ESMTP id 096J72Gu004242;
        Tue, 6 Oct 2020 19:07:02 GMT
Received: from nsvm-sadhukhan-1.osdevelopmeniad.oraclevcn.com
 (/100.100.230.216)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Tue, 06 Oct 2020 12:07:02 -0700
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com,
        sean.j.christopherson@intel.com
Subject: [PATCH 0/4 v3] KVM: nSVM: Add checks for CR3 and CR4 reserved bits to
 svm_set_nested_state() and test CR3 non-MBZ reserved bits
Date: Tue,  6 Oct 2020 19:06:50 +0000
Message-Id: <20201006190654.32305-1-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.18.4
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9766
 signatures=668680
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 adultscore=0
 mlxlogscore=803
 malwarescore=0 suspectscore=1 spamscore=0 phishscore=0 bulkscore=0
 mlxscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2010060123
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9766
 signatures=668680
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 mlxscore=0
 malwarescore=0 bulkscore=0
 impostorscore=0 lowpriorityscore=0 suspectscore=1 phishscore=0
 mlxlogscore=822 adultscore=0 clxscore=1015 spamscore=0 priorityscore=1501
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2006250000
 definitions=main-2010060123
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

v2 -> v3:
	Patch# 2: The local variable "nested_vmcb_lma" in
		  nested_vmcb_check_cr3_cr4() has been removed.
	Patch# 3: Commit message has been enhanced to explain what the test
		  is doing and why, when testing the 1-setting of the
		  non-MBZ-reserved bits.
		  Also, the test for legacy-PAE mode has been added. Commit
		  header reflects this addition.


[PATCH 1/4 v3] KVM: nSVM: CR3 MBZ bits are only 63:52
[PATCH 2/4 v3] KVM: nSVM: Add check for reserved bits for CR3, CR4, DR6,
[PATCH 3/4 v3] nSVM: Test non-MBZ reserved bits in CR3 in long mode and
[PATCH 4/4 v3] KVM: nSVM: nested_vmcb_checks() needs to check all bits

 arch/x86/kvm/svm/nested.c | 52 ++++++++++++++++++++++++++---------------------
 arch/x86/kvm/svm/svm.h    |  2 +-
 2 files changed, 30 insertions(+), 24 deletions(-)

Krish Sadhukhan (3):
      KVM: nSVM: CR3 MBZ bits are only 63:52
      KVM: nSVM: Add check for reserved bits for CR3, CR4, DR6, DR7 and EFER to svm_set_nested_state()
      KVM: nSVM: nested_vmcb_checks() needs to check all bits of EFER

 x86/svm.h       |  4 +++-
 x86/svm_tests.c | 66 +++++++++++++++++++++++++++++++++++++++++++++++++++------
 2 files changed, 63 insertions(+), 7 deletions(-)

Krish Sadhukhan (1):
      nSVM: Test non-MBZ reserved bits in CR3 in long mode and legacy PAE mode
```
#### [PATCH 0/4] Test MSR exits to userspace
##### From: Aaron Lewis <aaronlewis@google.com>

```c
From patchwork Tue Oct  6 21:04:40 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Aaron Lewis <aaronlewis@google.com>
X-Patchwork-Id: 11819229
Return-Path: <SRS0=4WRu=DN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4E00B17D2
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  6 Oct 2020 21:04:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2B67E208B6
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  6 Oct 2020 21:04:53 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="nmOfGm8q"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727394AbgJFVEw (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 6 Oct 2020 17:04:52 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:40198 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727176AbgJFVEw (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 6 Oct 2020 17:04:52 -0400
Received: from mail-pl1-x64a.google.com (mail-pl1-x64a.google.com
 [IPv6:2607:f8b0:4864:20::64a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id DA353C061755
        for <kvm@vger.kernel.org>; Tue,  6 Oct 2020 14:04:51 -0700 (PDT)
Received: by mail-pl1-x64a.google.com with SMTP id a6so2055756plm.5
        for <kvm@vger.kernel.org>; Tue, 06 Oct 2020 14:04:51 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:message-id:mime-version:subject:from:to:cc;
        bh=MFre2+dcFzdHRgPZJmfgfvp9RN1biBCw0qHlmo0+6ho=;
        b=nmOfGm8qbIS9vS716qew27tWEbd9Vl50uOHN7t7Zqyn1KYoSSluuq+Wc64dKtsS2p+
         M/sEfOpKIclbf2ikyVxJgv9UnHyQEsiNlY7+J1glDHQdlVkI3NZgFu754l/8r4k4eQ3f
         QIWQgbmoIpXR+d18fL4p6901A8iUW72UNuNAR3rBTF/HT/wSrEWrv9PwPdg+pTnQSTcV
         OhxDaIE6A7YMPKJrihbwRuU53HIM2GJS6jQtmBu03wCS3MFhYP8+4P14S1R5DC89oReQ
         td1BoMW4RpliHEXp4PKuGEXSgfyHf+Wg0gzJ8yeQWen+EesmYOyziZKsMbFVeK6Xsk+L
         kVcA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:message-id:mime-version:subject:from
         :to:cc;
        bh=MFre2+dcFzdHRgPZJmfgfvp9RN1biBCw0qHlmo0+6ho=;
        b=Yb+mQsBgvtR6TeWqzZY9mbijwSvXHm/SsgsXT9qMgASWH4DaqlMdvQMSRuQ9wAubXl
         MB0hgApphDWHpwHC/Hfcrs3MMKZ4zjsE/iLQrNjGbAndcQXKXvnfv1NuNDc3stgMcIJI
         3jBQiCu0y2pNLvSexfIMtuyATYjYk53BZ9aozQsd2qL0lSEsxaPuk/8bY1pYcQj9KqPl
         VTSkfqzyDevYLynWVG3BplEqXF5gCTADcFtAMLKJiSRDxH99VtaRx9RvX3meQL3pOX2+
         60LddTgbZ7VRsNBHDroC5N5pTREwUP9L3mWP5NNR5VoQcIRASq5gYbfzywCAciBhddi+
         u4uA==
X-Gm-Message-State: AOAM532aFBShBtR2px8NAUuQfhiIX/Cw9/BwTm10F6mJ0nxoxkSxX4Uj
        2VbRYNopbJO0xzXW3ukeEGoRO0qBl+3yMQ9d
X-Google-Smtp-Source: 
 ABdhPJwRF3ugv7AFp4UqFcNH2ZthNDxpR1qtMgYgz4BQI+AchCgivf1BshBYHxT2cn4bUqde3GT47M5IqmzIX73h
Sender: "aaronlewis via sendgmr" <aaronlewis@aaronlewis1.sea.corp.google.com>
X-Received: from aaronlewis1.sea.corp.google.com
 ([2620:15c:100:202:a28c:fdff:fed8:8d46])
 (user=aaronlewis job=sendgmr) by 2002:a17:902:b087:b029:d3:e6c5:5271 with
 SMTP id p7-20020a170902b087b02900d3e6c55271mr4973254plr.47.1602018290987;
 Tue, 06 Oct 2020 14:04:50 -0700 (PDT)
Date: Tue,  6 Oct 2020 14:04:40 -0700
Message-Id: <20201006210444.1342641-1-aaronlewis@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.28.0.806.g8561365e88-goog
Subject: [PATCH 0/4] Test MSR exits to userspace
From: Aaron Lewis <aaronlewis@google.com>
To: graf@amazon.com
Cc: pshier@google.com, jmattson@google.com, kvm@vger.kernel.org,
        Aaron Lewis <aaronlewis@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patchset adds additional testing to the series ("Allow user space to
restrict and augment MSR emulation") by Alexander Graf <graf@amazon.com>,
and supliments the selftest in that series.

This patchset introduces exception handling into the kvm selftest framework
which is then used in the test to be able to handle #GPs that are injected
into the guest from userspace.

The test focuses on two main areas:
  1) It tests the MSR filter API.
  2) It tests MSR permission bitmaps.

Aaron Lewis (4):
  selftests: kvm: Fix the segment descriptor layout to match the actual
    layout
  selftests: kvm: Clear uc so UCALL_NONE is being properly reported
  selftests: kvm: Add exception handling to selftests
  selftests: kvm: Test MSR exiting to userspace

 tools/testing/selftests/kvm/.gitignore        |   1 +
 tools/testing/selftests/kvm/Makefile          |  20 +-
 .../selftests/kvm/include/x86_64/processor.h  |  26 +-
 .../testing/selftests/kvm/lib/aarch64/ucall.c |   3 +
 tools/testing/selftests/kvm/lib/kvm_util.c    |  17 +
 .../selftests/kvm/lib/kvm_util_internal.h     |   2 +
 tools/testing/selftests/kvm/lib/s390x/ucall.c |   3 +
 .../selftests/kvm/lib/x86_64/handlers.S       |  81 +++
 .../selftests/kvm/lib/x86_64/processor.c      | 103 +++-
 .../testing/selftests/kvm/lib/x86_64/ucall.c  |   3 +
 .../kvm/x86_64/userspace_msr_exit_test.c      | 547 ++++++++++++++++++
 11 files changed, 795 insertions(+), 11 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/lib/x86_64/handlers.S
 create mode 100644 tools/testing/selftests/kvm/x86_64/userspace_msr_exit_test.c
```
