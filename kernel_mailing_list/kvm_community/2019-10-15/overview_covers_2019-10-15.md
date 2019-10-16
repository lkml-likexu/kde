

#### [kvm-unit-tests PATCH v2 0/4] Patches for clang compilation
##### From: Bill Wendling <morbo@google.com>

```c
From patchwork Tue Oct 15 00:04:07 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Bill Wendling <morbo@google.com>
X-Patchwork-Id: 11189521
Return-Path: <SRS0=XGHp=YI=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4591917E6
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Oct 2019 00:04:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 21E752089C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Oct 2019 00:04:18 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="kAQuyzHO"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726784AbfJOAER (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 14 Oct 2019 20:04:17 -0400
Received: from mail-pf1-f202.google.com ([209.85.210.202]:45067 "EHLO
        mail-pf1-f202.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726740AbfJOAER (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 14 Oct 2019 20:04:17 -0400
Received: by mail-pf1-f202.google.com with SMTP id a2so14512547pfo.12
        for <kvm@vger.kernel.org>; Mon, 14 Oct 2019 17:04:16 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=SRhEAAU8/+3Mdz5PZ+SYtqxO9uMOiDzHiECPRjG6fk0=;
        b=kAQuyzHOfAQerpV9y4OXwjS1OCWE6791uDCtjizPZgKKT3Q5gwfkdAdOlAvsCvUPrf
         03m9EPozMrOWjy8ElECcl+EE62BWrzam7NjjpY6xOnkRNTQO8YDZKQZRB43N+J400Nnd
         NmXrD3I86h/SHCyrOJ31FHvq6WtbwIn2YVG0JnfRrrlVPDH5SrCMYsRe+SqxTGeg4nVM
         pIxN3Osy56dZG3bweeTL52XBpCPD5qg15xbhRolST2+19REVgQkcIY5Sh5StHUQgqBUK
         5ijuh807wdqtskaV1wEo/fXB1Mx2KcQSj92XmvISjtnCXOLshPx9BJUA0OZM5tNis+Nd
         ODpw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=SRhEAAU8/+3Mdz5PZ+SYtqxO9uMOiDzHiECPRjG6fk0=;
        b=fpdh1vpgSu36LCmLFuflGJCv8OS/hOQYn4XkV7uSuMqdgOuLnMGggluyj9fByR4XTC
         b4Y06YrKp9nHZdsF3fte+zpXiIc9KYmj+jV+ZMGHrqsrnYf0ZK+t/cFQPI0nVn1R0jSH
         iw1gY3jE+QpqCoslbMIv20P6595opZdPdnpfkHggrq8jb5DRmWXPxqzg+MPscVoJEEjv
         ahsq6XPKEJa7LYirrARNOQF0s5CkUlUoYdAcZdcsXWOmKoGqazhlVTM0PLH2OzBifvcQ
         yheiXE8PE1fqU4U0u2vMhcRjFGzqrWffiyzp3FL2KAQAAQafDqomvN6qMbqiJzyxzsaF
         vCuA==
X-Gm-Message-State: APjAAAXg8NEMo8i2reWOD2vzgIUDLjMRqGpcUKVopnNYbolfJqQtOuSB
        r2f31QgN76mUhBUwlg7CcLrlGyHqtBYq3mbfc4qMhY4yv8UchduTS9Y3NWC1cMX5JUzAvuuDDzv
        t5WLwBb42QZs+aBZtnRfGdaCuiegwcv+ky/Qa9r2zSoFCpSf50EgYOQ==
X-Google-Smtp-Source: 
 APXvYqz+WG+YGqvbWfd4R+p3KvLl4jSxenaPXWbh0VyD9Vni4lvT7Pw3u40bxLMKlLUnLVn9/QGD9Gba3A==
X-Received: by 2002:a65:638a:: with SMTP id
 h10mr34899856pgv.388.1571097855656;
 Mon, 14 Oct 2019 17:04:15 -0700 (PDT)
Date: Mon, 14 Oct 2019 17:04:07 -0700
In-Reply-To: <20191010183506.129921-1-morbo@google.com>
Message-Id: <20191015000411.59740-1-morbo@google.com>
Mime-Version: 1.0
References: <20191010183506.129921-1-morbo@google.com>
X-Mailer: git-send-email 2.23.0.700.g56cf767bdb-goog
Subject: [kvm-unit-tests PATCH v2 0/4] Patches for clang compilation
From: Bill Wendling <morbo@google.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com
Cc: jmattson@google.com, sean.j.christopherson@intel.com,
        Bill Wendling <morbo@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

These four patches fix compilation issues that clang's encountering.

I ran the tests and there are no regressions with gcc.

Bill Wendling (4):
  x86: emulator: use "SSE2" for the target
  pci: cast the masks to the appropriate size
  Makefile: use "-Werror" in cc-option
  Makefile: add "cxx-option" for C++ builds

 Makefile       | 23 +++++++++++++++--------
 lib/pci.c      |  3 ++-
 x86/emulator.c |  2 +-
 3 files changed, 18 insertions(+), 10 deletions(-)
```
#### [PATCH 0/2 v2] KVM: nVMX: Defer error from VM-entry MSR-load area to
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
From patchwork Tue Oct 15 00:04:44 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11189541
Return-Path: <SRS0=XGHp=YI=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B8E79139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Oct 2019 00:41:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 9868521925
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Oct 2019 00:41:02 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="CNzydutU"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727131AbfJOAlB (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 14 Oct 2019 20:41:01 -0400
Received: from userp2120.oracle.com ([156.151.31.85]:38964 "EHLO
        userp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726525AbfJOAlB (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 14 Oct 2019 20:41:01 -0400
Received: from pps.filterd (userp2120.oracle.com [127.0.0.1])
        by userp2120.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 x9F0dRfb191849;
        Tue, 15 Oct 2019 00:40:49 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : mime-version : content-transfer-encoding;
 s=corp-2019-08-05; bh=sxyKiRJ4bzUtMpCBs8jUg7kEwo3d//uN0WhGuYjqjiY=;
 b=CNzydutU/FJkT0mnT+elEWeXHhxVUQ8SjSrKM6y9z1XhxKx+JqW1Z4BERX/6bUfVh2iJ
 AXdHtK7F/8jvrYcf+6Y81bQlT88G2L5jegSbFrpoL9Iy/nSbLQUqjFJCq8cNwueIeBiw
 0qFrjbztDaC31ZIIF+eBAjTyh5NfCGH/QefHGlykxfq/4w8JD+jKbVwBmsgHBsAi6AV6
 x5svtzpq5e7EaYkHT1voCTtonjEFuqWrPbIzWEw1Sytz2GBKQ3R+YT8fHy4aguNkA1HT
 vKw6/P+fkCUMKc7uMzytDD4mozGjsDOD2GQsFSO03fOvknNL3p5WnS3JAWH2hbZKTsS0 mg==
Received: from userp3030.oracle.com (userp3030.oracle.com [156.151.31.80])
        by userp2120.oracle.com with ESMTP id 2vk7fr4555-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 15 Oct 2019 00:40:48 +0000
Received: from pps.filterd (userp3030.oracle.com [127.0.0.1])
        by userp3030.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 x9F0baEf001083;
        Tue, 15 Oct 2019 00:40:48 GMT
Received: from userv0121.oracle.com (userv0121.oracle.com [156.151.31.72])
        by userp3030.oracle.com with ESMTP id 2vkr9y5vcr-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 15 Oct 2019 00:40:48 +0000
Received: from abhmp0008.oracle.com (abhmp0008.oracle.com [141.146.116.14])
        by userv0121.oracle.com (8.14.4/8.13.8) with ESMTP id x9F0elk7010618;
        Tue, 15 Oct 2019 00:40:47 GMT
Received: from ban25x6uut29.us.oracle.com (/10.153.73.29)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Tue, 15 Oct 2019 00:40:47 +0000
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, rkrcmar@redhat.com, jmattson@google.com
Subject: [PATCH 0/2 v2] KVM: nVMX: Defer error from VM-entry MSR-load area to
 until after hardware verifies VMCS guest state-area
Date: Mon, 14 Oct 2019 20:04:44 -0400
Message-Id: <20191015000446.8099-1-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9410
 signatures=668684
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=1
 malwarescore=0
 phishscore=0 bulkscore=0 spamscore=0 mlxscore=0 mlxlogscore=850
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.0.1-1908290000 definitions=main-1910150005
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9410
 signatures=668684
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 priorityscore=1501 malwarescore=0
 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0 clxscore=1015
 lowpriorityscore=0 mlxscore=0 impostorscore=0 mlxlogscore=927 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.0.1-1908290000
 definitions=main-1910150005
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

v1 -> v2:
        1. In patch# 1, the invalid VM-entry MSR-load area for vmcs02 is 
           now a system-wide entity. It is allocated and initialized 
           during VMX initialization. The exit qualification is now
           contained in a 32-bit variable in 'struct nested_vmx'.
        2. Patch# 2 is new. It rolls back MSR updates when VM-entry
           fails due to invalid VM-entry MSR-load area.


Some VM-entry checks can be offloaded from KVM to hardware. But if we want to
do that, the current implementation of KVM creates a priority issue where the
order in which VM-entry checks need to be performed according to the SDM, is
not maintained. VM-entry fails in nested_vmx_enter_non_root_mode() if an error
is encountered while processing the entries in VM-entry MSR-load area. This
leads to VM-exit due to a VM-entry check that is supposed to be done after
any guest-state checks done in hardware. This patch fixes this priority issue
so that checks that can be offloaded to hardware can now be offloaded.


[PATCH 1/2 v2] nVMX: Defer error from VM-entry MSR-load area to until
[PATCH 2/2 v2] nVMX: Rollback MSR-load if VM-entry fails due to VM-entry

 arch/x86/kvm/vmx/nested.c | 84 +++++++++++++++++++++++++++++++++++++++++++----
 arch/x86/kvm/vmx/nested.h | 29 ++++++++++++++--
 arch/x86/kvm/vmx/vmx.c    | 18 ++++++++++
 arch/x86/kvm/vmx/vmx.h    | 14 ++++++++
 4 files changed, 136 insertions(+), 9 deletions(-)

Krish Sadhukhan (2):
      nVMX: Defer error from VM-entry MSR-load area to until after hardware verifies VMCS guest state-area
      nVMX: Rollback MSR-load if VM-entry fails due to VM-entry MSR-loading
```
#### [PATCH 0/4]: kvm-unit-test: nVMX: Test deferring of error from
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
From patchwork Tue Oct 15 00:16:29 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11189553
Return-Path: <SRS0=XGHp=YI=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D424A1390
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Oct 2019 00:53:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B50EB2089C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Oct 2019 00:53:00 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="kHsDmBLS"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727268AbfJOAw7 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 14 Oct 2019 20:52:59 -0400
Received: from aserp2120.oracle.com ([141.146.126.78]:59244 "EHLO
        aserp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727011AbfJOAw7 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 14 Oct 2019 20:52:59 -0400
Received: from pps.filterd (aserp2120.oracle.com [127.0.0.1])
        by aserp2120.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 x9F0nw9i188611;
        Tue, 15 Oct 2019 00:52:37 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : mime-version : content-transfer-encoding;
 s=corp-2019-08-05; bh=hotD8gkd9LN3gSxavXQRklzT0OQBMnwsghE5Qo2RJzM=;
 b=kHsDmBLSA7AJqwW51GMDXJH2RYkuYyngUq7RJUc3D521NHCc8TY1C7KxYSIgcW8id+g6
 yARxRU3F9Ynrxhe8gHqfbzjzAS4DCv6fvQQaERTSrlMhQ5G56Vnj2Gt0emXEd6UbmlKO
 8wIe6l324qd6zSwdIlRGCcbETUqGzTI5hjMexPZ1aAeBxdv5Ik2KenLxOrz76J7wXx7Y
 XlVEgZIWJjOfumKJedujNoF9USxH529QDP/6Kx4DpCR0r1mogrTRSSaeqaJK4yW95ups
 rSw6+OgDL+fLRImEsl4dP4/yHlCTl6HqNZeguOpZxoHrPUTZEuqJXDeakK2lJovwqwF1 6w==
Received: from aserp3030.oracle.com (aserp3030.oracle.com [141.146.126.71])
        by aserp2120.oracle.com with ESMTP id 2vk6sqcab7-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 15 Oct 2019 00:52:37 +0000
Received: from pps.filterd (aserp3030.oracle.com [127.0.0.1])
        by aserp3030.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 x9F0mAFl077474;
        Tue, 15 Oct 2019 00:52:37 GMT
Received: from userv0122.oracle.com (userv0122.oracle.com [156.151.31.75])
        by aserp3030.oracle.com with ESMTP id 2vks07swna-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 15 Oct 2019 00:52:37 +0000
Received: from abhmp0016.oracle.com (abhmp0016.oracle.com [141.146.116.22])
        by userv0122.oracle.com (8.14.4/8.14.4) with ESMTP id x9F0qZEk005230;
        Tue, 15 Oct 2019 00:52:36 GMT
Received: from ban25x6uut29.us.oracle.com (/10.153.73.29)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Tue, 15 Oct 2019 00:52:35 +0000
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, rkrcmar@redhat.com, jmattson@google.com
Subject: [PATCH 0/4]: kvm-unit-test: nVMX: Test deferring of error from
 VM-entry MSR-load area
Date: Mon, 14 Oct 2019 20:16:29 -0400
Message-Id: <20191015001633.8603-1-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9410
 signatures=668684
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=13
 malwarescore=0
 phishscore=0 bulkscore=0 spamscore=0 mlxscore=0 mlxlogscore=749
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.0.1-1908290000 definitions=main-1910150007
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9410
 signatures=668684
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 priorityscore=1501 malwarescore=0
 suspectscore=13 phishscore=0 bulkscore=0 spamscore=0 clxscore=1015
 lowpriorityscore=0 mlxscore=0 impostorscore=0 mlxlogscore=826 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.0.1-1908290000
 definitions=main-1910150007
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Patch# 1: Replaces hard-coded value with instruction length read from VMCS
	  field.
Patch# 2: Adds an extra check to __enter_guest() so that it can distinguish
	  between VM-entry failure due to invalid guest state and that due to
	  invalid VM-entry MSR-load area.
Patch# 3: Verifies that when VM-entry fails due to invalid VM-entry MSR-load
	  area in vmcs12, the error is deferred and caught by hardware when
	  it is done processing higher priority checks such as guest state etc.
	  This patch also verifies that when VM-entry fails due to invalid
	  VM-entry MSR-load area in vmcs12, MSRs that were loaded from  that
	  MSR-load area are rolled back to their original values.
Patch# 4: Replaces hard-coded value with corresponding #define.


[PATCH 1/4] kvm-unit-test: VMX: Replace hard-coded exit instruction length
[PATCH 2/4] kvm-unit-test: nVMX: __enter_guest() needs to also check for
[PATCH 3/4] kvm-unit-test: nVMX: Test deferring of error from VM-entry MSR-load area
[PATCH 4/4] kvm-unit-test: nVMX: Use #defines for exit reason in

 x86/vmx.c       |   3 +-
 x86/vmx_tests.c | 139 ++++++++++++++++++++++++++++++++++++++++++++++++++++++--
 2 files changed, 136 insertions(+), 6 deletions(-)

Krish Sadhukhan (4):
      VMX: Replace hard-coded exit instruction length
      VMX: __enter_guest() needs to also check for VMX_FAIL_STATE
      nVMX: Test deferring of error from VM-entry MSR-load area
      nVMX: Use #defines for exit reason in advance_guest_state_test()
```
#### [PATCH v6 0/5] Add a unified parameter "nopvspin"
##### From: Zhenzhong Duan <zhenzhong.duan@oracle.com>

```c
From patchwork Tue Oct 15 01:19:22 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhenzhong Duan <zhenzhong.duan@oracle.com>
X-Patchwork-Id: 11189565
Return-Path: <SRS0=XGHp=YI=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8D34814E5
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Oct 2019 01:21:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 6D2F620873
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Oct 2019 01:21:28 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="fZKvlsdV"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727343AbfJOBV1 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 14 Oct 2019 21:21:27 -0400
Received: from userp2120.oracle.com ([156.151.31.85]:42718 "EHLO
        userp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727225AbfJOBV0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 14 Oct 2019 21:21:26 -0400
Received: from pps.filterd (userp2120.oracle.com [127.0.0.1])
        by userp2120.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 x9F1EY4r020318;
        Tue, 15 Oct 2019 01:19:43 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id; s=corp-2019-08-05;
 bh=og0nReRT1S8qBVN5P7l1DoHNjDEWAEndMK6ePaGXWpk=;
 b=fZKvlsdVEtC4diYLDfLOjEQp5brudI20L4g8Rd/9prh0hvl0la2YUoJDGTsMr1BJ7M+l
 g6QUGaC/uSFLtRe61VKLmtmVRwhLJsfEpiwhty5i3RCxIguFawBrVe9cq67vG6xiBIxl
 RdIglSeCvNYwB3BRDbIU6sosF06L8+32tIADlVCJAQQNaPCvRUhDY4ZlDwZHsjIQOa1t
 FjnZMmNnIKrOa63MhW2ydwXuHcrwzM3zo3QopzNzbAty6uMHYCwRHYp1UQblr/dfH5+X
 z1Cy8kK2jiGCL+wphe+tJmduFe+qkAUCOAc5bcq0lXXKoqTi6AhtPo+4cuKx57TV/0LG CA==
Received: from aserp3020.oracle.com (aserp3020.oracle.com [141.146.126.70])
        by userp2120.oracle.com with ESMTP id 2vk7fr48q5-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 15 Oct 2019 01:19:43 +0000
Received: from pps.filterd (aserp3020.oracle.com [127.0.0.1])
        by aserp3020.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 x9F1J6jU152922;
        Tue, 15 Oct 2019 01:19:42 GMT
Received: from aserv0121.oracle.com (aserv0121.oracle.com [141.146.126.235])
        by aserp3020.oracle.com with ESMTP id 2vkrbkx3jn-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 15 Oct 2019 01:19:42 +0000
Received: from abhmp0019.oracle.com (abhmp0019.oracle.com [141.146.116.25])
        by aserv0121.oracle.com (8.14.4/8.13.8) with ESMTP id x9F1JYme011219;
        Tue, 15 Oct 2019 01:19:40 GMT
Received: from z2.cn.oracle.com (/10.182.70.159)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Mon, 14 Oct 2019 18:19:33 -0700
From: Zhenzhong Duan <zhenzhong.duan@oracle.com>
To: linux-kernel@vger.kernel.org
Cc: vkuznets@redhat.com, linux-hyperv@vger.kernel.org,
        kvm@vger.kernel.org, kys@microsoft.com, haiyangz@microsoft.com,
        sthemmin@microsoft.com, sashal@kernel.org, tglx@linutronix.de,
        mingo@redhat.com, bp@alien8.de, pbonzini@redhat.com,
        rkrcmar@redhat.com, sean.j.christopherson@intel.com,
        wanpengli@tencent.com, jmattson@google.com, joro@8bytes.org,
        boris.ostrovsky@oracle.com, jgross@suse.com,
        sstabellini@kernel.org, peterz@infradead.org,
        Zhenzhong Duan <zhenzhong.duan@oracle.com>
Subject: [PATCH v6 0/5] Add a unified parameter "nopvspin"
Date: Tue, 15 Oct 2019 09:19:22 +0800
Message-Id: <1571102367-31595-1-git-send-email-zhenzhong.duan@oracle.com>
X-Mailer: git-send-email 1.8.3.1
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9410
 signatures=668684
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=1
 malwarescore=0
 phishscore=0 bulkscore=0 spamscore=0 mlxscore=0 mlxlogscore=999
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.0.1-1908290000 definitions=main-1910150010
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9410
 signatures=668684
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 priorityscore=1501 malwarescore=0
 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0 clxscore=1015
 lowpriorityscore=0 mlxscore=0 impostorscore=0 mlxlogscore=999 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.0.1-1908290000
 definitions=main-1910150010
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

There are cases folks want to disable spinlock optimization for
debug/test purpose. Xen and hyperv already have parameters "xen_nopvspin"
and "hv_nopvspin" to support that, but kvm doesn't.

The first patch adds that feature to KVM guest with "nopvspin".

For compatibility reason original parameters "xen_nopvspin" and
"hv_nopvspin" are retained and marked obsolete.

v6:
PATCH1: add Reviewed-by                                  [Vitaly Kuznetsov]
PATCH2: change 'pv' to 'PV', add Reviewed-by             [Vitaly Kuznetsov]
PATCH3: refactor 'if' branch in kvm_spinlock_init()      [Vitaly Kuznetsov]

v5:
PATCH1: new patch to revert a currently unnecessory commit,
        code is simpler a bit after that change.         [Boris Ostrovsky]
PATCH3: fold 'if' statement,add comments on virt_spin_lock_key,
        reorder with PATCH2 to better reflect dependency                               
PATCH4: fold 'if' statement, add Reviewed-by             [Boris Ostrovsky]
PATCH5: add Reviewed-by                                  [Michael Kelley]

v4:
PATCH1: use variable name nopvspin instead of pvspin and
        defined it as __initdata, changed print message,
        updated patch description                     [Sean Christopherson]
PATCH2: remove Suggested-by, use "kvm-guest:" prefix  [Sean Christopherson]
PATCH3: make variable nopvsin and xen_pvspin coexist
        remove Reviewed-by due to code change         [Sean Christopherson]
PATCH4: make variable nopvsin and hv_pvspin coexist   [Sean Christopherson]

v3:
PATCH2: Fix indentation

v2:
PATCH1: pick the print code change into separate PATCH2,
        updated patch description             [Vitaly Kuznetsov]
PATCH2: new patch with print code change      [Vitaly Kuznetsov]
PATCH3: add Reviewed-by                       [Juergen Gross]

Zhenzhong Duan (5):
  Revert "KVM: X86: Fix setup the virt_spin_lock_key before static key
    get initialized"
  x86/kvm: Change print code to use pr_*() format
  x86/kvm: Add "nopvspin" parameter to disable PV spinlocks
  xen: Mark "xen_nopvspin" parameter obsolete
  x86/hyperv: Mark "hv_nopvspin" parameter obsolete

 Documentation/admin-guide/kernel-parameters.txt | 14 ++++-
 arch/x86/hyperv/hv_spinlock.c                   |  4 ++
 arch/x86/include/asm/qspinlock.h                |  1 +
 arch/x86/kernel/kvm.c                           | 76 ++++++++++++++++---------
 arch/x86/xen/spinlock.c                         |  4 +-
 kernel/locking/qspinlock.c                      |  7 +++
 6 files changed, 75 insertions(+), 31 deletions(-)
```
#### [RFC PATCH v5 0/6] Enable ptp_kvm for arm64
##### From: Jianyong Wu <jianyong.wu@arm.com>

```c
From patchwork Tue Oct 15 10:48:16 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jianyong Wu <jianyong.wu@arm.com>
X-Patchwork-Id: 11190049
Return-Path: <SRS0=XGHp=YI=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 939AF1668
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Oct 2019 10:48:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7E058217F9
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Oct 2019 10:48:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731038AbfJOKsy (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 15 Oct 2019 06:48:54 -0400
Received: from foss.arm.com ([217.140.110.172]:35070 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726054AbfJOKsy (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 15 Oct 2019 06:48:54 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 64EFE28;
        Tue, 15 Oct 2019 03:48:53 -0700 (PDT)
Received: from entos-d05.shanghai.arm.com (entos-d05.shanghai.arm.com
 [10.169.40.35])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPA id
 A23423F68E;
        Tue, 15 Oct 2019 03:48:48 -0700 (PDT)
From: Jianyong Wu <jianyong.wu@arm.com>
To: netdev@vger.kernel.org, yangbo.lu@nxp.com, john.stultz@linaro.org,
        tglx@linutronix.de, pbonzini@redhat.com,
        sean.j.christopherson@intel.com, maz@kernel.org,
        richardcochran@gmail.com, Mark.Rutland@arm.com, will@kernel.org,
        suzuki.poulose@arm.com
Cc: linux-kernel@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        Steve.Capper@arm.com, Kaly.Xin@arm.com, justin.he@arm.com,
        jianyong.wu@arm.com, nd@arm.com
Subject: [RFC PATCH v5 0/6] Enable ptp_kvm for arm64
Date: Tue, 15 Oct 2019 18:48:16 +0800
Message-Id: <20191015104822.13890-1-jianyong.wu@arm.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

kvm ptp targets to provide high precision time sync between guest
and host in virtualization environment. This patch enable kvm ptp
for arm64.
This patch set base on [1][2][3]

change log:
from v4 to v5:
        (1) remove hvc delay compensasion as it should leave to userspace.
        (2) check current clocksource in hvc call service.
        (3) expose current clocksource by adding it to
system_time_snapshot.
        (4) add helper to check if clocksource is arm_arch_counter.
        (5) rename kvm_ptp.c to ptp_kvm_common.c
from v3 to v4:
        (1) fix clocksource of ptp_kvm to arch_sys_counter.
        (2) move kvm_arch_ptp_get_clock_fn into arm_arch_timer.c
        (3) subtract cntvoff before return cycles from host.
        (4) use ktime_get_snapshot instead of getnstimeofday and
get_current_counterval to return time and counter value.
        (5) split ktime and counter into two 32-bit block respectively
to avoid Y2038-safe issue.
        (6) set time compensation to device time as half of the delay of hvc call.
        (7) add ARM_ARCH_TIMER as dependency of ptp_kvm for
arm64.
from v2 to v3:
        (1) fix some issues in commit log.
        (2) add some receivers in send list.
from v1 to v2:
        (1) move arch-specific code from arch/ to driver/ptp/
        (2) offer mechanism to inform userspace if ptp_kvm service is
available.
        (3) separate ptp_kvm code for arm64 into hypervisor part and
guest part.
	(4) add API to expose monotonic clock and counter value.
        (5) refine code: remove no necessary part and reconsitution.

[1]https://git.kernel.org/pub/scm/linux/kernel/git/will/linux.git/
commit/?h=kvm/hvc&id=125ea89e4a21e2fc5235410f966a996a1a7148bf
[2]https://git.kernel.org/pub/scm/linux/kernel/git/will/linux.git/
commit/?h=kvm/hvc&id=464f5a1741e5959c3e4d2be1966ae0093b4dce06
[3]https://git.kernel.org/pub/scm/linux/kernel/git/will/linux.git/
commit/?h=kvm/hvc&id=6597490e005d0eeca8ed8c1c1d7b4318ee014681

Jianyong Wu (6):
  psci: Export psci_ops.conduit symbol as modules will use it.
  ptp: Reorganize ptp_kvm modules to make it arch-independent.
  timekeeping: Add clocksource to system_time_snapshot
  psci: Add hvc call service for ptp_kvm.
  ptp: arm64: Enable ptp_kvm for arm64
  kvm: arm64: Add capability check extension for ptp_kvm

 drivers/clocksource/arm_arch_timer.c        | 27 +++++++
 drivers/firmware/psci/psci.c                |  6 ++
 drivers/ptp/Kconfig                         |  2 +-
 drivers/ptp/Makefile                        |  1 +
 drivers/ptp/ptp_kvm_arm64.c                 | 54 +++++++++++++
 drivers/ptp/{ptp_kvm.c => ptp_kvm_common.c} | 77 +++++-------------
 drivers/ptp/ptp_kvm_x86.c                   | 87 +++++++++++++++++++++
 include/asm-generic/ptp_kvm.h               | 12 +++
 include/clocksource/arm_arch_timer.h        |  5 ++
 include/linux/arm-smccc.h                   | 14 +++-
 include/linux/psci.h                        |  1 +
 include/linux/timekeeping.h                 | 35 +++++----
 include/uapi/linux/kvm.h                    |  1 +
 kernel/time/timekeeping.c                   |  7 +-
 virt/kvm/arm/arm.c                          |  1 +
 virt/kvm/arm/psci.c                         | 21 +++++
 16 files changed, 270 insertions(+), 81 deletions(-)
 create mode 100644 drivers/ptp/ptp_kvm_arm64.c
 rename drivers/ptp/{ptp_kvm.c => ptp_kvm_common.c} (63%)
 create mode 100644 drivers/ptp/ptp_kvm_x86.c
 create mode 100644 include/asm-generic/ptp_kvm.h
```
#### [PATCH v19 0/5] Add ARMv8 RAS virtualization support in QEMU
##### From: Xiang Zheng <zhengxiang9@huawei.com>

```c
From patchwork Tue Oct 15 14:01:35 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xiang Zheng <zhengxiang9@huawei.com>
X-Patchwork-Id: 11190413
Return-Path: <SRS0=XGHp=YI=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4344214ED
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Oct 2019 14:02:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 18BA021925
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Oct 2019 14:02:56 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732387AbfJOOCz (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 15 Oct 2019 10:02:55 -0400
Received: from szxga04-in.huawei.com ([45.249.212.190]:4156 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1732011AbfJOOCy (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 15 Oct 2019 10:02:54 -0400
Received: from DGGEMS410-HUB.china.huawei.com (unknown [172.30.72.60])
        by Forcepoint Email with ESMTP id 023BA1553AB263705643;
        Tue, 15 Oct 2019 22:02:52 +0800 (CST)
Received: from HGHY4Z004218071.china.huawei.com (10.133.224.57) by
 DGGEMS410-HUB.china.huawei.com (10.3.19.210) with Microsoft SMTP Server id
 14.3.439.0; Tue, 15 Oct 2019 22:02:45 +0800
From: Xiang Zheng <zhengxiang9@huawei.com>
To: <pbonzini@redhat.com>, <mst@redhat.com>, <imammedo@redhat.com>,
        <shannon.zhaosl@gmail.com>, <peter.maydell@linaro.org>,
        <lersek@redhat.com>, <james.morse@arm.com>,
        <gengdongjiu@huawei.com>, <mtosatti@redhat.com>, <rth@twiddle.net>,
        <ehabkost@redhat.com>, <jonathan.cameron@huawei.com>,
        <xuwei5@huawei.com>, <kvm@vger.kernel.org>,
        <qemu-devel@nongnu.org>, <qemu-arm@nongnu.org>,
        <linuxarm@huawei.com>
CC: <zhengxiang9@huawei.com>, <wanghaibin.wang@huawei.com>
Subject: [PATCH v19 0/5] Add ARMv8 RAS virtualization support in QEMU
Date: Tue, 15 Oct 2019 22:01:35 +0800
Message-ID: <20191015140140.34748-1-zhengxiang9@huawei.com>
X-Mailer: git-send-email 2.15.1.windows.2
MIME-Version: 1.0
X-Originating-IP: [10.133.224.57]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In the ARMv8 platform, the CPU error types are synchronous external abort(SEA)
and SError Interrupt (SEI). If exception happens in guest, sometimes it's better
for guest to perform the recovery, because host does not know the detailed
information of guest. For example, if an exception happens in a user-space
application within guest, host does not know which application encounters
errors.

For the ARMv8 SEA/SEI, KVM or host kernel delivers SIGBUS to notify userspace.
After user space gets the notification, it will record the CPER into guest GHES
buffer and inject an exception or IRQ into guest.

In the current implementation, if the type of SIGBUS is BUS_MCEERR_AR, we will
treat it as a synchronous exception, and notify guest with ARMv8 SEA
notification type after recording CPER into guest.

This series of patches are based on Qemu 4.1, which include two parts:
1. Generate APEI/GHES table.
2. Handle the SIGBUS signal, record the CPER in runtime and fill it into guest
   memory, then notify guest according to the type of SIGBUS.

The whole solution was suggested by James(james.morse@arm.com); The solution of
APEI section was suggested by Laszlo(lersek@redhat.com).
Show some discussions in [1].

This series of patches have already been tested on ARM64 platform with RAS
feature enabled:
Show the APEI part verification result in [2].
Show the BUS_MCEERR_AR SIGBUS handling verification result in [3].
---
Change since v18:
1. Fix some code-style and typo/grammar problems.
2. Remove no_ras in the VirtMachineClass struct.
3. Convert documentation to rst format.
4. Simplize the code and add comments for some magic value.
5. Move kvm_inject_arm_sea() function into the patch where it's used.
6. Register the reset handler(kvm_unpoison_all()) in the kvm_init() function.

Change since v17:
1. Improve some commit messages and comments.
2. Fix some code-style problems.
3. Add a *ras* machine option.
4. Move HEST/GHES related structures and macros into "hw/acpi/acpi_ghes.*".
5. Move HWPoison page functions into "include/sysemu/kvm_int.h".
6. Fix some bugs.
7. Improve the design document.

Change since v16:
1. check whether ACPI table is enabled when handling the memory error in the SIGBUS handler.

Change since v15:
1. Add a doc-comment in the proper format for 'include/exec/ram_addr.h'
2. Remove write_part_cpustate_to_list() because there is another bug fix patch
   has been merged "arm: Allow system registers for KVM guests to be changed by QEMU code"
3. Add some comments for kvm_inject_arm_sea() in 'target/arm/kvm64.c'
4. Compare the arm_current_el() return value to 0,1,2,3, not to PSTATE_MODE_* constants.
5. Change the RAS support wasn't introduced before 4.1 QEMU version.
6. Move the no_ras flag  patch to begin in this series

Change since v14:
1. Remove the BUS_MCEERR_AO handling logic because this asynchronous signal was masked by main thread
2. Address some Igor Mammedov's comments(ACPI part)
   1) change the comments for the enum AcpiHestNotifyType definition and remove ditto in patch 1
   2) change some patch commit messages and separate "APEI GHES table generation" patch to more patches.
3. Address some peter's comments(arm64 Synchronous External Abort injection)
   1) change some code notes
   2) using arm_current_el() for current EL
   2) use the helper functions for those (syn_data_abort_*).

Change since v13:
1. Move the patches that set guest ESR and inject virtual SError out of this series
2. Clean and optimize the APEI part patches
3. Update the commit messages and add some comments for the code

Change since v12:
1. Address Paolo's comments to move HWPoisonPage definition to accel/kvm/kvm-all.c
2. Only call kvm_cpu_synchronize_state() when get the BUS_MCEERR_AR signal
3. Only add and enable GPIO-Signal and ARMv8 SEA two hardware error sources
4. Address Michael's comments to not sync SPDX from Linux kernel header file

Change since v11:
Address James's comments(james.morse@arm.com)
1. Check whether KVM has the capability to to set ESR instead of detecting host CPU RAS capability
2. For SIGBUS_MCEERR_AR SIGBUS, use Synchronous-External-Abort(SEA) notification type
   for SIGBUS_MCEERR_AO SIGBUS, use GPIO-Signal notification


Address Shannon's comments(for ACPI part):
1. Unify hest_ghes.c and hest_ghes.h license declaration
2. Remove unnecessary including "qmp-commands.h" in hest_ghes.c
3. Unconditionally add guest APEI table based on James's comments(james.morse@arm.com)
4. Add a option to virt machine for migration compatibility. On new virt machine it's on
   by default while off for old ones, we enabled it since 2.12
5. Refer to the ACPI spec version which introduces Hardware Error Notification first time
6. Add ACPI_HEST_NOTIFY_RESERVED notification type

Address Igor's comments(for ACPI part):
1. Add doc patch first which will describe how it's supposed to work between QEMU/firmware/guest
   OS with expected flows.
2. Move APEI diagrams into doc/spec patch
3. Remove redundant g_malloc in ghes_record_cper()
4. Use build_append_int_noprefix() API to compose whole error status block and whole APEI table,
   and try to get rid of most structures in patch 1, as they will be left unused after that
5. Reuse something like https://github.com/imammedo/qemu/commit/3d2fd6d13a3ea298d2ee814835495ce6241d085c
   to build GAS
6. Remove much offsetof() in the function
7. Build independent tables first and only then build dependent tables passing to it pointers
   to previously build table if necessary.
8. Redefine macro GHES_ACPI_HEST_NOTIFY_RESERVED to ACPI_HEST_ERROR_SOURCE_COUNT to avoid confusion


Address Peter Maydell's comments
1. linux-headers is done as a patch of their own created using scripts/update-linux-headers.sh run against a
   mainline kernel tree
2. Tested whether this patchset builds OK on aarch32
3. Abstract Hwpoison page adding code  out properly into a cpu-independent source file from target/i386/kvm.c,
   such as kvm-all.c
4. Add doc-comment formatted documentation comment for new globally-visible function prototype in a header

---
[1]:
https://lkml.org/lkml/2017/2/27/246
https://patchwork.kernel.org/patch/9633105/
https://patchwork.kernel.org/patch/9925227/

[2]:
Note: the UEFI(QEMU_EFI.fd) is needed if guest want to use ACPI table.

After guest boot up, dump the APEI table, then can see the initialized table
(1) # iasl -p ./HEST -d /sys/firmware/acpi/tables/HEST
(2) # cat HEST.dsl
    /*
     * Intel ACPI Component Architecture
     * AML/ASL+ Disassembler version 20170728 (64-bit version)
     * Copyright (c) 2000 - 2017 Intel Corporation
     *
     * Disassembly of /sys/firmware/acpi/tables/HEST, Mon Sep  5 07:59:17 2016
     *
     * ACPI Data Table [HEST]
     *
     * Format: [HexOffset DecimalOffset ByteLength]  FieldName : FieldValue
     */

    ..................................................................................
    [308h 0776   2]                Subtable Type : 000A [Generic Hardware Error Source V2]
    [30Ah 0778   2]                    Source Id : 0001
    [30Ch 0780   2]            Related Source Id : FFFF
    [30Eh 0782   1]                     Reserved : 00
    [30Fh 0783   1]                      Enabled : 01
    [310h 0784   4]       Records To Preallocate : 00000001
    [314h 0788   4]      Max Sections Per Record : 00000001
    [318h 0792   4]          Max Raw Data Length : 00001000

    [31Ch 0796  12]         Error Status Address : [Generic Address Structure]
    [31Ch 0796   1]                     Space ID : 00 [SystemMemory]
    [31Dh 0797   1]                    Bit Width : 40
    [31Eh 0798   1]                   Bit Offset : 00
    [31Fh 0799   1]         Encoded Access Width : 04 [QWord Access:64]
    [320h 0800   8]                      Address : 00000000785D0040

    [328h 0808  28]                       Notify : [Hardware Error Notification Structure]
    [328h 0808   1]                  Notify Type : 08 [SEA]
    [329h 0809   1]                Notify Length : 1C
    [32Ah 0810   2]   Configuration Write Enable : 0000
    [32Ch 0812   4]                 PollInterval : 00000000
    [330h 0816   4]                       Vector : 00000000
    [334h 0820   4]      Polling Threshold Value : 00000000
    [338h 0824   4]     Polling Threshold Window : 00000000
    [33Ch 0828   4]        Error Threshold Value : 00000000
    [340h 0832   4]       Error Threshold Window : 00000000

    [344h 0836   4]    Error Status Block Length : 00001000
    [348h 0840  12]            Read Ack Register : [Generic Address Structure]
    [348h 0840   1]                     Space ID : 00 [SystemMemory]
    [349h 0841   1]                    Bit Width : 40
    [34Ah 0842   1]                   Bit Offset : 00
    [34Bh 0843   1]         Encoded Access Width : 04 [QWord Access:64]
    [34Ch 0844   8]                      Address : 00000000785D0098

    [354h 0852   8]            Read Ack Preserve : 00000000FFFFFFFE
    [35Ch 0860   8]               Read Ack Write : 0000000000000001

    .....................................................................................

(3) After a synchronous external abort(SEA) happen, Qemu receive a SIGBUS and 
    filled the CPER into guest GHES memory.  For example, according to above table,
    the address that contains the physical address of a block of memory that holds
    the error status data for this abort is 0x00000000785D0040
(4) the address for SEA notification error source is 0x785d80b0
    (qemu) xp /1 0x00000000785D0040
    00000000785d0040: 0x785d80b0

(5) check the content of generic error status block and generic error data entry
    (qemu) xp /100x 0x785d80b0
    00000000785d80b0: 0x00000001 0x00000000 0x00000000 0x00000098
    00000000785d80c0: 0x00000000 0xa5bc1114 0x4ede6f64 0x833e63b8
    00000000785d80d0: 0xb1837ced 0x00000000 0x00000300 0x00000050
    00000000785d80e0: 0x00000000 0x00000000 0x00000000 0x00000000
    00000000785d80f0: 0x00000000 0x00000000 0x00000000 0x00000000
    00000000785d8100: 0x00000000 0x00000000 0x00000000 0x00004002
(6) check the OSPM's ACK value(for example SEA)
    /* Before OSPM acknowledges the error, check the ACK value */
    (qemu) xp /1 0x00000000785D0098
    00000000785d00f0: 0x00000000

    /* After OSPM acknowledges the error, check the ACK value, it change to 1 from 0 */
    (qemu) xp /1 0x00000000785D0098
    00000000785d00f0: 0x00000001

[3]: KVM deliver "BUS_MCEERR_AR" to Qemu, Qemu record the guest CPER and inject
    synchronous external abort to notify guest, then guest do the recovery.

[ 1552.516170] Synchronous External Abort: synchronous external abort (0x92000410) at 0x000000003751c6b4
[ 1553.074073] {1}[Hardware Error]: Hardware error from APEI Generic Hardware Error Source: 8
[ 1553.081654] {1}[Hardware Error]: event severity: recoverable
[ 1554.034191] {1}[Hardware Error]:  Error 0, type: recoverable
[ 1554.037934] {1}[Hardware Error]:   section_type: memory error
[ 1554.513261] {1}[Hardware Error]:   physical_address: 0x0000000040fa6000
[ 1554.513944] {1}[Hardware Error]:   error_type: 0, unknown
[ 1555.041451] Memory failure: 0x40fa6: Killing mca-recover:1296 due to hardware memory corruption
[ 1555.373116] Memory failure: 0x40fa6: recovery action for dirty LRU page: Recovered

Dongjiu Geng (5):
  hw/arm/virt: Introduce a RAS machine option
  docs: APEI GHES generation and CPER record description
  ACPI: Add APEI GHES table generation support
  KVM: Move hwpoison page related functions into kvm-all.c
  target-arm: kvm64: handle SIGBUS signal from kernel or KVM

 accel/kvm/kvm-all.c             |  36 +++
 default-configs/arm-softmmu.mak |   1 +
 docs/specs/acpi_hest_ghes.rst   |  94 ++++++++
 docs/specs/index.rst            |   1 +
 hw/acpi/Kconfig                 |   4 +
 hw/acpi/Makefile.objs           |   1 +
 hw/acpi/acpi_ghes.c             | 476 ++++++++++++++++++++++++++++++++++++++++
 hw/acpi/aml-build.c             |   2 +
 hw/arm/virt-acpi-build.c        |  12 +
 hw/arm/virt.c                   |  23 ++
 include/hw/acpi/acpi_ghes.h     | 148 +++++++++++++
 include/hw/acpi/aml-build.h     |   1 +
 include/hw/arm/virt.h           |   1 +
 include/sysemu/kvm.h            |   3 +-
 include/sysemu/kvm_int.h        |  12 +
 target/arm/cpu.h                |   4 +
 target/arm/helper.c             |   2 +-
 target/arm/internals.h          |   5 +-
 target/arm/kvm64.c              |  64 ++++++
 target/arm/tlb_helper.c         |   2 +-
 target/i386/cpu.h               |   2 +
 target/i386/kvm.c               |  36 ---
 22 files changed, 888 insertions(+), 42 deletions(-)
 create mode 100644 docs/specs/acpi_hest_ghes.rst
 create mode 100644 hw/acpi/acpi_ghes.c
 create mode 100644 include/hw/acpi/acpi_ghes.h
```
#### [PATCH V2 0/2] target/i386/kvm: Add Hyper-V direct tlb flush support
##### From: lantianyu1986@gmail.com
X-Google-Original-From: Tianyu.Lan@microsoft.com
From: Tianyu Lan <Tianyu.Lan@microsoft.com>

```c
From patchwork Tue Oct 15 14:36:08 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tianyu Lan <lantianyu1986@gmail.com>
X-Patchwork-Id: 11190543
Return-Path: <SRS0=XGHp=YI=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3B8081390
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Oct 2019 14:36:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1A41C217D6
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Oct 2019 14:36:23 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="hMPbKjDk"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732721AbfJOOgW (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 15 Oct 2019 10:36:22 -0400
Received: from mail-pl1-f195.google.com ([209.85.214.195]:41808 "EHLO
        mail-pl1-f195.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1732599AbfJOOgV (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 15 Oct 2019 10:36:21 -0400
Received: by mail-pl1-f195.google.com with SMTP id t10so9689421plr.8
        for <kvm@vger.kernel.org>; Tue, 15 Oct 2019 07:36:20 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=cLAwBrnafbrt9J1uJn5jsQACw4S4ae1p8THVsWr/E1g=;
        b=hMPbKjDkqDoi0WTHeuY3YNKQOZURFyiBP95maDFM8tmxUOUUb5LxRgI8zktGTVcF5S
         40qdEJLj4Tv6MITgm3lvDhtfRXIwhdExKHpln6zYABvcUPrBcibPxzn+oPCsyoa0cSGi
         SSWMF29uPKgpRPix6BL5YV/38X6io8hhwci8tCVzYAREAOmRIRXcgO/jTYphbQNB7c9Y
         srgLqZz/gsc+1qJPjJBD8txC+K/WVNghN9EL7l4T8rAKHEYxdvCOmp8PJIhzZbBEWim4
         1BLc/+su3BDOyDN5SxHJNtEPvXnPR+DwP3g1rYBhImPvz5OQPhLyVzpjiaHaKuFcMPzw
         hmXQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=cLAwBrnafbrt9J1uJn5jsQACw4S4ae1p8THVsWr/E1g=;
        b=DMG6Xq9/XTg3GM9c9e7Hj9ukibDOQY2VukGz5NUkPBPatDFrtfqZ1hNHJNXk5He/m3
         e/4EwLVEBP2wL52wBLAvHGKVm+L+njvTOM92NV3ueSWLyj3kJUbtKby9nRJORfyvB8Dn
         2+gc8eC8dq7npSsGBPpQYJgHMMaysdW1c1FPAX1lqsgESH3hpEcYUn2Deb4GYzjfie8e
         /n9Mz/1t5/KXEiugDZuPfqhW0LKpnS1nJ+bONWp51miyCAceO+zOvi6mX9PscxsyrNYL
         VSHcnZlpvT3MoDw/KEmN+cz0+PCA7sTFo4Oob3zgtrbkkUOe2CPxV35IS4pCWD+F8KeD
         kxZQ==
X-Gm-Message-State: APjAAAX68D9paGk1PnOjWY2gAtYiJO3jZ9apZFrpWViZiKHpMbwP+mcY
        KgR9yG6UiuJuM7TTsrAjHGg=
X-Google-Smtp-Source: 
 APXvYqzF5pVPQErQhvHW99GLzPBhE8631lYzEVomzsVgfCIHBcKlZ9qSzfVbW15Q253AW9Hl83LDHw==
X-Received: by 2002:a17:902:8ecc:: with SMTP id
 x12mr36755018plo.189.1571150179735;
        Tue, 15 Oct 2019 07:36:19 -0700 (PDT)
Received: from localhost.corp.microsoft.com ([167.220.255.39])
        by smtp.googlemail.com with ESMTPSA id
 v43sm4913165pjb.1.2019.10.15.07.36.16
        (version=TLS1_2 cipher=ECDHE-RSA-CHACHA20-POLY1305 bits=256/256);
        Tue, 15 Oct 2019 07:36:18 -0700 (PDT)
From: lantianyu1986@gmail.com
X-Google-Original-From: Tianyu.Lan@microsoft.com
To: mst@redhat.com, cohuck@redhat.com, pbonzini@redhat.com,
        rth@twiddle.net, ehabkost@redhat.com, mtosatti@redhat.com,
        rkagan@virtuozzo.com
Cc: Tianyu Lan <Tianyu.Lan@microsoft.com>, kvm@vger.kernel.org,
        qemu-devel@nongnu.org
Subject: [PATCH V2 0/2] target/i386/kvm: Add Hyper-V direct tlb flush support
Date: Tue, 15 Oct 2019 22:36:08 +0800
Message-Id: <20191015143610.31857-1-Tianyu.Lan@microsoft.com>
X-Mailer: git-send-email 2.14.5
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Tianyu Lan <Tianyu.Lan@microsoft.com>

This patchset is to enable Hyper-V direct tlbflush
feature. The feature is to let L0 hypervisor to handle
tlb flush hypercall for L1 hypervisor.

Tianyu Lan (2):
  linux headers: update against Linux 5.4-rc2
  target/i386/kvm: Add Hyper-V direct tlb flush support

 docs/hyperv.txt                              | 12 +++++
 include/standard-headers/asm-x86/bootparam.h |  2 +
 include/standard-headers/asm-x86/kvm_para.h  |  1 +
 include/standard-headers/linux/ethtool.h     | 24 ++++++++++
 include/standard-headers/linux/pci_regs.h    | 19 +++++++-
 include/standard-headers/linux/virtio_ids.h  |  2 +
 include/standard-headers/linux/virtio_pmem.h |  6 +--
 linux-headers/asm-arm/kvm.h                  | 16 ++++++-
 linux-headers/asm-arm/unistd-common.h        |  2 +
 linux-headers/asm-arm64/kvm.h                | 21 +++++++-
 linux-headers/asm-generic/mman-common.h      | 18 ++++---
 linux-headers/asm-generic/mman.h             | 10 ++--
 linux-headers/asm-generic/unistd.h           | 10 +++-
 linux-headers/asm-mips/mman.h                |  3 ++
 linux-headers/asm-mips/unistd_n32.h          |  2 +
 linux-headers/asm-mips/unistd_n64.h          |  2 +
 linux-headers/asm-mips/unistd_o32.h          |  2 +
 linux-headers/asm-powerpc/mman.h             |  6 +--
 linux-headers/asm-powerpc/unistd_32.h        |  2 +
 linux-headers/asm-powerpc/unistd_64.h        |  2 +
 linux-headers/asm-s390/kvm.h                 |  6 +++
 linux-headers/asm-s390/unistd_32.h           |  2 +
 linux-headers/asm-s390/unistd_64.h           |  2 +
 linux-headers/asm-x86/kvm.h                  | 28 ++++++++---
 linux-headers/asm-x86/unistd.h               |  2 +-
 linux-headers/asm-x86/unistd_32.h            |  2 +
 linux-headers/asm-x86/unistd_64.h            |  2 +
 linux-headers/asm-x86/unistd_x32.h           |  2 +
 linux-headers/linux/kvm.h                    | 12 ++++-
 linux-headers/linux/psp-sev.h                |  5 +-
 linux-headers/linux/vfio.h                   | 71 ++++++++++++++++++++--------
 target/i386/cpu.c                            |  2 +
 target/i386/cpu.h                            |  1 +
 target/i386/kvm.c                            | 23 +++++++++
 34 files changed, 263 insertions(+), 59 deletions(-)
```
#### [PATCH 00/32] hw/i386/pc: Split PIIX3 southbridge from i440FX
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>

```c
From patchwork Tue Oct 15 16:26:33 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
 <philmd@redhat.com>
X-Patchwork-Id: 11190927
Return-Path: <SRS0=XGHp=YI=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 779A01390
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Oct 2019 16:27:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 56E3420872
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Oct 2019 16:27:22 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727938AbfJOQ1V (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 15 Oct 2019 12:27:21 -0400
Received: from mx1.redhat.com ([209.132.183.28]:56564 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726775AbfJOQ1V (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 15 Oct 2019 12:27:21 -0400
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 287453084051;
        Tue, 15 Oct 2019 16:27:20 +0000 (UTC)
Received: from x1w.redhat.com (ovpn-204-35.brq.redhat.com [10.40.204.35])
        by smtp.corp.redhat.com (Postfix) with ESMTPS id DB09319C58;
        Tue, 15 Oct 2019 16:27:08 +0000 (UTC)
From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>
To: qemu-devel@nongnu.org
Cc: Aleksandar Markovic <amarkovic@wavecomp.com>,
 Aurelien Jarno <aurelien@aurel32.net>, Eduardo Habkost <ehabkost@redhat.com>,
 Thomas Huth <thuth@redhat.com>, Igor Mammedov <imammedo@redhat.com>,
 Anthony Perard <anthony.perard@citrix.com>,
 Stefano Stabellini <sstabellini@kernel.org>, Paul Durrant <paul@xen.org>,
	=?utf-8?q?Herv=C3=A9_Poussineau?= <hpoussin@reactos.org>,
 Aleksandar Rikalo <aleksandar.rikalo@rt-rk.com>,
 xen-devel@lists.xenproject.org, Laurent Vivier <lvivier@redhat.com>,
 "Michael S. Tsirkin" <mst@redhat.com>,
 Marcel Apfelbaum <marcel.apfelbaum@gmail.com>,
 Paolo Bonzini <pbonzini@redhat.com>, Richard Henderson <rth@twiddle.net>,
 kvm@vger.kernel.org,
 =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>
Subject: [PATCH 00/32] hw/i386/pc: Split PIIX3 southbridge from i440FX
 northbridge
Date: Tue, 15 Oct 2019 18:26:33 +0200
Message-Id: <20191015162705.28087-1-philmd@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.5.16 (mx1.redhat.com [10.5.110.40]);
 Tue, 15 Oct 2019 16:27:20 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

This series is a rework of "piix4: cleanup and improvements" [1]
from Hervé, and my "remove i386/pc dependency: PIIX cleanup" [2].

Still trying to remove the strong X86/PC dependency 2 years later,
one step at a time.
Here we split the PIIX3 southbridge from i440FX northbridge.
The i440FX northbridge is only used by the PC machine, while the
PIIX southbridge is also used by the Malta MIPS machine.

This is also a step forward using KConfig with the Malta board.
Without this split, it was impossible to compile the Malta without
pulling various X86 pieces of code.

The overall design cleanup is not yet perfect, but enough to post
as a series.

Now that the PIIX3 code is extracted, the code duplication with the
PIIX4 chipset is obvious. Not worth improving for now because it
isn't broken.

Next step is probably:

1/ Extract i8259 from "pc.h" and sort all the places where we call
   pic_*() using global variables
2/ Refactor common PIIX code from hw/i386/pc_*.c to piix*.c

Please review,

Phil.

Series available here:
branch pc_split_i440fx_piix-v1 on https://gitlab.com/philmd/qemu.git

[1] https://www.mail-archive.com/qemu-devel@nongnu.org/msg500737.html
[2] https://www.mail-archive.com/qemu-devel@nongnu.org/msg504081.html

Hervé Poussineau (9):
  mc146818rtc: move structure to header file
  mc146818rtc: always register rtc to rtc list
  piix4: rename some variables in realize function
  piix4: add Reset Control Register
  piix4: add a i8259 interrupt controller as specified in datasheet
  piix4: rename PIIX4 object to piix4-isa
  piix4: convert reset function to QOM
  piix4: add a i8257 dma controller as specified in datasheet
  piix4: add a i8254 pit controller as specified in datasheet

Philippe Mathieu-Daudé (23):
  hw/i386: Remove obsolete LoadStateHandler::load_state_old handlers
  hw/i386/pc: Move kvm_i8259_init() declaration to sysemu/kvm.h
  mc146818rtc: Move RTC_ISA_IRQ definition
  mc146818rtc: Include "mc146818rtc_regs.h" directly in mc146818rtc.c
  MAINTAINERS: Keep PIIX4 South Bridge separate from PC Chipsets
  Revert "irq: introduce qemu_irq_proxy()"
  piix4: add a mc146818rtc controller as specified in datasheet
  hw/mips/mips_malta: Create IDE hard drive array dynamically
  hw/mips/mips_malta: Extract the PIIX4 creation code as piix4_create()
  hw/isa/piix4: Move piix4_create() to hw/isa/piix4.c
  hw/i386/pc: Extract pc_gsi_create()
  hw/i386/pc: Reduce gsi_handler scope
  hw/i386/pc: Move gsi_state creation code
  hw/i386/pc: Extract pc_i8259_create()
  hw/i386/pc: Remove kvm_i386.h include
  hw/pci-host/piix: Extract piix3_create()
  hw/pci-host/piix: Move RCR_IOPORT register definition
  hw/pci-host/piix: Define and use the PIIX IRQ Route Control Registers
  hw/pci-host/piix: Move i440FX declarations to hw/pci-host/i440fx.h
  hw/pci-host/piix: Fix code style issues
  hw/pci-host/piix: Extract PIIX3 functions to hw/isa/piix3.c
  hw/pci-host: Rename incorrectly named 'piix' as 'i440fx'
  hw/pci-host/i440fx: Remove the last PIIX3 traces

 MAINTAINERS                         |  14 +-
 hw/acpi/pcihp.c                     |   2 +-
 hw/acpi/piix4.c                     |  42 +--
 hw/core/irq.c                       |  14 -
 hw/i386/Kconfig                     |   3 +-
 hw/i386/acpi-build.c                |   3 +-
 hw/i386/pc.c                        |  36 ++-
 hw/i386/pc_piix.c                   |  33 +--
 hw/i386/pc_q35.c                    |  28 +-
 hw/i386/xen/xen-hvm.c               |   5 +-
 hw/intc/apic_common.c               |  49 ----
 hw/isa/Kconfig                      |   4 +
 hw/isa/Makefile.objs                |   1 +
 hw/isa/piix3.c                      | 399 ++++++++++++++++++++++++++
 hw/isa/piix4.c                      | 155 ++++++++--
 hw/mips/gt64xxx_pci.c               |   5 +-
 hw/mips/mips_malta.c                |  46 +--
 hw/pci-host/Kconfig                 |   3 +-
 hw/pci-host/Makefile.objs           |   2 +-
 hw/pci-host/{piix.c => i440fx.c}    | 424 +---------------------------
 hw/timer/i8254_common.c             |  40 ---
 hw/timer/mc146818rtc.c              |  39 +--
 include/hw/acpi/piix4.h             |   6 -
 include/hw/i386/pc.h                |  41 +--
 include/hw/irq.h                    |   5 -
 include/hw/isa/isa.h                |   2 +
 include/hw/pci-host/i440fx.h        |  36 +++
 include/hw/southbridge/piix.h       |  74 +++++
 include/hw/timer/mc146818rtc.h      |  36 ++-
 include/hw/timer/mc146818rtc_regs.h |   2 -
 include/sysemu/kvm.h                |   1 +
 stubs/pci-host-piix.c               |   3 +-
 tests/rtc-test.c                    |   1 +
 33 files changed, 781 insertions(+), 773 deletions(-)
 create mode 100644 hw/isa/piix3.c
 rename hw/pci-host/{piix.c => i440fx.c} (58%)
 delete mode 100644 include/hw/acpi/piix4.h
 create mode 100644 include/hw/pci-host/i440fx.h
 create mode 100644 include/hw/southbridge/piix.h
```
#### [PATCH 0/4] Refactor vcpu creation flow of x86 arch
##### From: Xiaoyao Li <xiaoyao.li@intel.com>

```c
From patchwork Tue Oct 15 16:40:29 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xiaoyao Li <xiaoyao.li@intel.com>
X-Patchwork-Id: 11191223
Return-Path: <SRS0=XGHp=YI=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7A1321668
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Oct 2019 16:55:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 6317220659
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Oct 2019 16:55:58 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388304AbfJOQz3 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 15 Oct 2019 12:55:29 -0400
Received: from mga11.intel.com ([192.55.52.93]:46844 "EHLO mga11.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726362AbfJOQz2 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 15 Oct 2019 12:55:28 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga003.fm.intel.com ([10.253.24.29])
  by fmsmga102.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 15 Oct 2019 09:55:28 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.67,300,1566889200";
   d="scan'208";a="201811346"
Received: from lxy-clx-4s.sh.intel.com ([10.239.43.57])
  by FMSMGA003.fm.intel.com with ESMTP; 15 Oct 2019 09:55:26 -0700
From: Xiaoyao Li <xiaoyao.li@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Sean Christopherson <sean.j.christopherson@intel.com>,
 Vitaly Kuznetsov <vkuznets@redhat.com>, Jim Mattson <jmattson@google.com>,
 Joerg Roedel <joro@8bytes.org>
Cc: Xiaoyao Li <xiaoyao.li@intel.com>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH 0/4] Refactor vcpu creation flow of x86 arch
Date: Wed, 16 Oct 2019 00:40:29 +0800
Message-Id: <20191015164033.87276-1-xiaoyao.li@intel.com>
X-Mailer: git-send-email 2.19.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When reading the vcpu creationg flow of vmx, I find it hard to follow since it
mixes the data structure allocation and initilization together.

This series tries to make the vcpu creation flow more clear that first
allocating data structure and then initializing them. In this way, it helps
move FPU allocation to generic x86 code (Patch 4).

This series intends to do no functional change. I just tested it with
kvm_unit_tests for vmx since I have no AMD machine at hand.

Xiaoyao Li (4):
  KVM: VMX: rename {vmx,nested_vmx}_vcpu_setup functions
  KVM: VMX: Setup MSR bitmap only when has msr_bitmap capability
  KVM: X86: Refactor kvm_arch_vcpu_create
  KVM: X86: Make vcpu's FPU allocation a common function

 arch/x86/include/asm/kvm_host.h |   1 +
 arch/x86/kvm/svm.c              |  81 ++++++---------
 arch/x86/kvm/vmx/nested.c       |   2 +-
 arch/x86/kvm/vmx/nested.h       |   2 +-
 arch/x86/kvm/vmx/vmx.c          | 173 ++++++++++++++------------------
 arch/x86/kvm/x86.c              |  40 ++++++++
 6 files changed, 150 insertions(+), 149 deletions(-)
```
#### [kvm-unit-tests v2 PATCH 0/2] Clang compilation fixes
##### From: Bill Wendling <morbo@google.com>

```c
From patchwork Tue Oct 15 20:45:04 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Bill Wendling <morbo@google.com>
X-Patchwork-Id: 11191625
Return-Path: <SRS0=XGHp=YI=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 09CA413BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Oct 2019 20:45:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id DD7DC20873
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Oct 2019 20:45:12 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="aPdtL5U6"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2389266AbfJOUpM (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 15 Oct 2019 16:45:12 -0400
Received: from mail-yw1-f74.google.com ([209.85.161.74]:41727 "EHLO
        mail-yw1-f74.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727673AbfJOUpL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 15 Oct 2019 16:45:11 -0400
Received: by mail-yw1-f74.google.com with SMTP id y70so17070682ywd.8
        for <kvm@vger.kernel.org>; Tue, 15 Oct 2019 13:45:11 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=BaoYZBJuvyQJEKwW7QcwZniyRVyyFXFGu3N+2oefdI4=;
        b=aPdtL5U6tR3YXhZ6VuXKWfkJVMFZlZeMUmh5DgRY2b+YJyPVXfvOteZIGTM6nB8kWX
         XA4wlS+XUuEIiE2WS+xzJd7G2L4o1uf4nPrjG5H9iedKie7abG5Nc+fX+78F1joRvKHB
         tXiDrgzpIkhyYq678d61L4F+OULqgwA5mO5F9SXiGPRsewP12aG39djFonA+7O7H89kh
         y9+M9DWHnMe/q4Rm7dvXrk16RR+bfzi3BaC1q+QPqa7amsJf6Vq8WnXUZqPDLuZ17XKt
         WRte/g4zzq8vJvF5k32fQAZTE+ywegtU2HtHmgwZsz2ER83nWBOQX5C2JNy+1VqM0FCe
         mbLA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=BaoYZBJuvyQJEKwW7QcwZniyRVyyFXFGu3N+2oefdI4=;
        b=D3Pv+devYClxI2nm1ESmovMtuBfSsZcI+4tTak/L7C9pLpuERAoZuX2SrYu4PMV1FW
         ch7bgeW0wYtmNqnwCCescexY6mSNkHSht2qmdu60fO5EM49RTtDSMdTNg+VteT++zrLB
         QIFJELW51qAUZIjsIIVzFz+mP4dMlgLVwax0UjA/CDR3WSeH/gNrk3LTGUy4YgVHBM4P
         EDX65cbW1xCoR1b5D0DcV9V7LvVCpE/ZJctlBgZx5jnGozLcNo0irrMrhjEZVQjfXlXQ
         AOPaL/Dlq1jrUgOoopGoY6W0RqhCLPAG7yeY3NWl3TkAwdmlGU0LOP9SxdF3OE+CDRkK
         BlUQ==
X-Gm-Message-State: APjAAAV3K9VxGBzRSJvEyxChsyuDF9DQvCiUXvgjMtOFVZ2gTaXRwOT4
        97+xjWO4YAIUbNxBy9/OevUYY1d8NuS9iI6I+bteo7idXTM5AIFLlFd4lQsIYANBUMgK9BzACfk
        FRYYXn4t2VB4bXkMs12N/WJ22WDEnMwL0a6jPZSYEdDDjaAPr2IM5HA==
X-Google-Smtp-Source: 
 APXvYqym9f/1xr4NKCIpVb79zh2UVPHacIf9saOCXW4q3yUNcnD/88A8nYN4HMLE1ytrmz27KdOKP9eSkA==
X-Received: by 2002:a25:790a:: with SMTP id
 u10mr25895639ybc.273.1571172310555;
 Tue, 15 Oct 2019 13:45:10 -0700 (PDT)
Date: Tue, 15 Oct 2019 13:45:04 -0700
Message-Id: <20191015204506.46872-1-morbo@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.23.0.700.g56cf767bdb-goog
Subject: [kvm-unit-tests v2 PATCH 0/2] Clang compilation fixes
From: Bill Wendling <morbo@google.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com, alexandru.elisei@arm.com,
        thuth@redhat.com
Cc: jmattson@google.com, Bill Wendling <morbo@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The attached patches have fixes for clang compilation and some failures
seen from the previous "report()" fix.

The first, changing the "report()" function to accept an "enum status"
instead of "unsigned pass" is under discussion, with others making
alternative suggestions. I add the patch here for completeness, but you
may want to wait until the discussion has settled.

The second, using "less than" to compare two global objects' addresses
for inequality, should be less controversial. 

This replaces the previous two patches I sent. I apologize for the
spammage.

    [kvm-unit-tests PATCH 1/2] Use a status enum for reporting pass/fail
    [kvm-unit-tests PATCH 2/2] x86: use pointer for end of exception table

Bill Wendling (2):
  lib: use a status enum for reporting pass/fail
  x86: don't compare two global objects' addrs for inequality

 lib/libcflat.h | 13 +++++++++++--
 lib/report.c   | 24 ++++++++++++------------
 lib/x86/desc.c |  2 +-
 3 files changed, 24 insertions(+), 15 deletions(-)
```
