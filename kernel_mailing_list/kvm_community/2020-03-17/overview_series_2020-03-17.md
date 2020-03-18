#### [PATCH 1/2] kvm-unit-test: VMX: Add enum for GUEST_BNDCFGS field and LOAD_BNDCFGS vmentry control field
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11441607
Return-Path: <SRS0=C8aH=5C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BA97D913
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 17 Mar 2020 01:21:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 940A820674
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 17 Mar 2020 01:21:56 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="ihoM27JS"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1733112AbgCQBVx (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 16 Mar 2020 21:21:53 -0400
Received: from userp2130.oracle.com ([156.151.31.86]:46930 "EHLO
        userp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1733100AbgCQBVx (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 16 Mar 2020 21:21:53 -0400
Received: from pps.filterd (userp2130.oracle.com [127.0.0.1])
        by userp2130.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 02H1Imxc098530;
        Tue, 17 Mar 2020 01:21:47 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references; s=corp-2020-01-29;
 bh=cDDq+2csZ2Ig9rWpSfkpLtxHgXmnawO/NWkLoKYH/9c=;
 b=ihoM27JSxuTw4EsvOR2eVU1bVSvnD2ECF+zKHBT7zhW9qMyybn5pWoYjLbhXr2VZW+iA
 dkwVrxKMNzO7wezrKVF9q4PCPv/94IZfzp9mtb5TchjCRXmGLFzrV3NX7q1gqmwwWB5F
 TyJsFB/8Jyq1o5pqy8J5QIBDdeDGBMc6/+a5TJjNzWIIB/gLJdykvtz72CwDceHg/TFt
 uSZ6x10fCRWvZEISFRfi38/8vZKBYfOzxs4xlAs/1idyutpZoyO+0VZhxnhREKHzazSN
 NkhTojPRXKA0JDii7s+0ZRXk2GX5EKxsCMJ6fw/iXDCXB41QDwZ1+ZFBeHrJRWWxca6e SA==
Received: from userp3020.oracle.com (userp3020.oracle.com [156.151.31.79])
        by userp2130.oracle.com with ESMTP id 2yrppr224n-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 17 Mar 2020 01:21:47 +0000
Received: from pps.filterd (userp3020.oracle.com [127.0.0.1])
        by userp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 02H1LEws196466;
        Tue, 17 Mar 2020 01:21:47 GMT
Received: from userv0121.oracle.com (userv0121.oracle.com [156.151.31.72])
        by userp3020.oracle.com with ESMTP id 2ys8yx07n0-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 17 Mar 2020 01:21:47 +0000
Received: from abhmp0006.oracle.com (abhmp0006.oracle.com [141.146.116.12])
        by userv0121.oracle.com (8.14.4/8.13.8) with ESMTP id 02H1LkwG002071;
        Tue, 17 Mar 2020 01:21:46 GMT
Received: from sadhukhan-nvmx.osdevelopmeniad.oraclevcn.com (/100.100.231.182)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Mon, 16 Mar 2020 18:21:46 -0700
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com,
        sean.j.christopherson@intel.com
Subject: [PATCH 1/2] kvm-unit-test: VMX: Add enum for GUEST_BNDCFGS field and
 LOAD_BNDCFGS vmentry control field
Date: Tue, 17 Mar 2020 01:21:34 +0000
Message-Id: <1584408095-16591-2-git-send-email-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1584408095-16591-1-git-send-email-krish.sadhukhan@oracle.com>
References: <1584408095-16591-1-git-send-email-krish.sadhukhan@oracle.com>
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9562
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 phishscore=0
 mlxlogscore=999 mlxscore=0
 adultscore=0 bulkscore=0 malwarescore=0 spamscore=0 suspectscore=13
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2003020000
 definitions=main-2003170003
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9562
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 malwarescore=0
 bulkscore=0
 suspectscore=13 lowpriorityscore=0 phishscore=0 adultscore=0 clxscore=1015
 impostorscore=0 priorityscore=1501 spamscore=0 mlxlogscore=999 mlxscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2003020000
 definitions=main-2003170003
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 x86/vmx.h | 2 ++
 1 file changed, 2 insertions(+)

```
#### [PATCH 2/2] kvm-unit-test: nVMX: Test GUEST_BNDCFGS VM-Entry control on vmentry of nested guests
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11441609
Return-Path: <SRS0=C8aH=5C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DA22B14B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 17 Mar 2020 01:21:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id BB54B2051A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 17 Mar 2020 01:21:56 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="t7zvSEMY"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1733127AbgCQBVy (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 16 Mar 2020 21:21:54 -0400
Received: from userp2120.oracle.com ([156.151.31.85]:57960 "EHLO
        userp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1733101AbgCQBVx (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 16 Mar 2020 21:21:53 -0400
Received: from pps.filterd (userp2120.oracle.com [127.0.0.1])
        by userp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 02H1Hawe179121;
        Tue, 17 Mar 2020 01:21:48 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references : mime-version :
 content-type : content-transfer-encoding; s=corp-2020-01-29;
 bh=pfIwU/PXEpuf5XuEm6c4PZ/De0gyTs4w+BvLHNHU4bQ=;
 b=t7zvSEMYIfsYYfK5eOqCkVMiunCD+HP4HInEx04d4GuGtBZHs/E4QPz7GWGe1lXj+an+
 t2qf+fnPDhwvvA53zGJlrJKf1xZAtlQ86eNS8mzWaixJb4fQDVnH1vknmFkwMShgLmYj
 hwSy/z4TMCFJ2bqGlhhxFmgP8fuyY0llNqAeq0s5TTxbhd/hdDrhJ5uYZsEQHUd7IGua
 SY9Lz+hL3/t5UIf5DGteQ0pmEVrmJlYjz9Smq5mYiYm8sXaATXIh3h5FDh/9TojWVFq2
 /5q/IkbdMO7ENMalySwvfcLX67oCC4nsYZkurIs59E5OElBBwNEK1uZgQbLPbX91dmj7 Yw==
Received: from aserp3030.oracle.com (aserp3030.oracle.com [141.146.126.71])
        by userp2120.oracle.com with ESMTP id 2yrqwn1w3v-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 17 Mar 2020 01:21:48 +0000
Received: from pps.filterd (aserp3030.oracle.com [127.0.0.1])
        by aserp3030.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 02H1KgXg064756;
        Tue, 17 Mar 2020 01:21:47 GMT
Received: from aserv0122.oracle.com (aserv0122.oracle.com [141.146.126.236])
        by aserp3030.oracle.com with ESMTP id 2ys8tqs4tg-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 17 Mar 2020 01:21:47 +0000
Received: from abhmp0006.oracle.com (abhmp0006.oracle.com [141.146.116.12])
        by aserv0122.oracle.com (8.14.4/8.14.4) with ESMTP id 02H1LkmN008354;
        Tue, 17 Mar 2020 01:21:46 GMT
Received: from sadhukhan-nvmx.osdevelopmeniad.oraclevcn.com (/100.100.231.182)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Mon, 16 Mar 2020 18:21:46 -0700
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com,
        sean.j.christopherson@intel.com
Subject: [PATCH 2/2] kvm-unit-test: nVMX: Test GUEST_BNDCFGS VM-Entry control
 on vmentry of nested guests
Date: Tue, 17 Mar 2020 01:21:35 +0000
Message-Id: <1584408095-16591-3-git-send-email-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1584408095-16591-1-git-send-email-krish.sadhukhan@oracle.com>
References: <1584408095-16591-1-git-send-email-krish.sadhukhan@oracle.com>
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9562
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 adultscore=0
 phishscore=0 mlxscore=0
 malwarescore=0 suspectscore=13 mlxlogscore=999 spamscore=0 bulkscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2003020000
 definitions=main-2003170003
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9562
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 lowpriorityscore=0 mlxlogscore=999
 mlxscore=0 bulkscore=0 phishscore=0 spamscore=0 suspectscore=13
 malwarescore=0 priorityscore=1501 clxscore=1015 adultscore=0
 impostorscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2003020000 definitions=main-2003170003
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

According to section "Checks on Guest Control Registers, Debug Registers,
and MSRs" in Intel SDM vol 3C, the following checks are performed on
vmentry of nested guests:

    If the "load IA32_BNDCFGS" VM-entry control is 1, the following
    checks are performed on the field for the IA32_BNDCFGS MSR:

      —  Bits reserved in the IA32_BNDCFGS MSR must be 0.
      —  The linear address in bits 63:12 must be canonical.

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 x86/vmx_tests.c | 53 +++++++++++++++++++++++++++++++++++++++++++++++++++++
 1 file changed, 53 insertions(+)

```
#### [PATCH] KVM: nVMX: remove side effects from nested_vmx_exit_reflected
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11443681
Return-Path: <SRS0=C8aH=5C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3365A1667
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 17 Mar 2020 18:01:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 0460620753
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 17 Mar 2020 18:01:12 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="lzLaNmkp"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726747AbgCQSBI (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 17 Mar 2020 14:01:08 -0400
Received: from mail-wm1-f68.google.com ([209.85.128.68]:38269 "EHLO
        mail-wm1-f68.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726278AbgCQSBI (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 17 Mar 2020 14:01:08 -0400
Received: by mail-wm1-f68.google.com with SMTP id t13so278690wmi.3;
        Tue, 17 Mar 2020 11:01:07 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id;
        bh=T32itqq2iG4R5xS3SgZFa5iW2a5HV4efCuB1zt7pHvc=;
        b=lzLaNmkppxWDxmNZQ5aCmmzdE6ZG+qKLm+AhRSLlpp5qilmm1HBdRI8dHLwrCc2a7W
         dl8Af4rsjAmG4zMHhS1/8xMtyuOAYQOP6NmYRxsV16FV+tqgshQwUge9Xhw82Kym+deb
         uSq856n67xzcF1GRNnLoR6yHYqfSxaOUWbPnFaPCgcLuURldLm1TwChTH1dYRRjWRY11
         TjKkghMQ/3dS1qyHwCKjpy3V4kpgg5WOy3Ez7bqq8iKa5m1ipM2U2LtPGFgXOTk9dezm
         WovKDgMsAin2jESSMlq1FNryLUkl4FdAQlAzhQZ9V55pdHIyJVKOMW+VnAoLcNDPx0G7
         O5SA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id;
        bh=T32itqq2iG4R5xS3SgZFa5iW2a5HV4efCuB1zt7pHvc=;
        b=tazGW23eQ7ldr4jhnPlH9k0yGmfd+8E9Xc/GUXYEu9HTJKXHuN7zR3q5hff7fKBv8B
         KLSFjD6apgs1PffiWIBeYwt6nOwVdY/D80BxLTp43RCVKfM/s0EXL7ooOoToUvMgjqP1
         zwUMnKT4RQjG4IxotMf6vL3Si8Add+iMwN0F7smoFB1NdjaebREnZZyl76Dtx7WiucMG
         ll99ByP+sYzZ/o15Wo8a/j3guhe8McdPIl9w8ghdeN5UKdoi5Vu5Hv6Ssfz3Lqoby4JP
         svWnEXAMSL2Mc8H1Ad0w30tYDO7p/dWrydJCS3W0wfRR4ZQWx5dnafRY1j5zm+EudNut
         chzg==
X-Gm-Message-State: ANhLgQ0uD4AYna2JTQF+Of5uUd86d+8ZMJdiNc5tfj4pI0n2GWvB5h7E
        6nm3Q19KMo32CXn3d/9upyDaxhLb
X-Google-Smtp-Source: 
 ADFU+vt3RGoK8s2yNUjqUV+NqdyImargYWiitWSLtlUNk1uRN2/kGm+q/TY2uiVncgJvOTLctkSeTg==
X-Received: by 2002:a05:600c:2c06:: with SMTP id
 q6mr246073wmg.52.1584468065931;
        Tue, 17 Mar 2020 11:01:05 -0700 (PDT)
Received: from 640k.localdomain.com ([93.56.174.5])
        by smtp.gmail.com with ESMTPSA id
 j39sm5955220wre.11.2020.03.17.11.01.04
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Tue, 17 Mar 2020 11:01:04 -0700 (PDT)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: vkuznets@redhat.com, sean.j.christopherson@intel.com
Subject: [PATCH] KVM: nVMX: remove side effects from nested_vmx_exit_reflected
Date: Tue, 17 Mar 2020 19:00:59 +0100
Message-Id: <1584468059-3585-1-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The name of nested_vmx_exit_reflected suggests that it's purely
a test, but it actually marks VMCS12 pages as dirty.  Move this to
vmx_handle_exit, observing that the initial nested_run_pending check in
nested_vmx_exit_reflected is pointless---nested_run_pending has just
been cleared in vmx_vcpu_run and won't be set until handle_vmlaunch
or handle_vmresume.

Suggested-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/vmx/nested.c | 18 ++----------------
 arch/x86/kvm/vmx/nested.h |  1 +
 arch/x86/kvm/vmx/vmx.c    | 19 +++++++++++++++++--
 3 files changed, 20 insertions(+), 18 deletions(-)

```
#### [PATCH 1/3] kvm-unit-test: nSVM: Add alternative (v2) test format for nested guests
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11443947
Return-Path: <SRS0=C8aH=5C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6C9191820
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 17 Mar 2020 20:44:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 416E220738
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 17 Mar 2020 20:44:35 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="hg87H2yX"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726840AbgCQUoe (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 17 Mar 2020 16:44:34 -0400
Received: from userp2120.oracle.com ([156.151.31.85]:43226 "EHLO
        userp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726756AbgCQUoe (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 17 Mar 2020 16:44:34 -0400
Received: from pps.filterd (userp2120.oracle.com [127.0.0.1])
        by userp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 02HKi1w1096892;
        Tue, 17 Mar 2020 20:44:31 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=mime-version :
 message-id : date : from : to : cc : subject : references : in-reply-to :
 content-type : content-transfer-encoding; s=corp-2020-01-29;
 bh=YaEWJRYmTz3xvGH/0lUtNUZOBaSClgLzgeRw5k7RCSc=;
 b=hg87H2yXn+pp8f++mJfwFXPXek/nbAdPqOianarkt7I7Z9WWydJYk5CMJYvR0mOmyvE4
 AFiiI2RrgktVehxejH2ToDNL43J9G+inove+NuwfyeJg3ohLun65Z8+zHiDC5JrzDDUz
 5p155XD5+M/AjKJu5MzZAzQUzNdnHiHZSHW7fiEg3TbBJ7mD9FpzmknLxmT1SD1U1QYc
 Qu7VAUQi1Wz07dJogd99dR6PFY4uoeyp20NJ6oHf26UaLEkNPhVgfztBGc7nRbtTYyvn
 x4jQD7cbslb+LofHK1xjzr/r8Z91bDdStt9Scpx+V2Yoznyl0i0ZDXQeQuJ6TImRfhHa Vw==
Received: from aserp3020.oracle.com (aserp3020.oracle.com [141.146.126.70])
        by userp2120.oracle.com with ESMTP id 2yrqwn73ga-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 17 Mar 2020 20:44:31 +0000
Received: from pps.filterd (aserp3020.oracle.com [127.0.0.1])
        by aserp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 02HKbZSd005211;
        Tue, 17 Mar 2020 20:44:30 GMT
Received: from userv0121.oracle.com (userv0121.oracle.com [156.151.31.72])
        by aserp3020.oracle.com with ESMTP id 2ys92e3244-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 17 Mar 2020 20:44:30 +0000
Received: from abhmp0010.oracle.com (abhmp0010.oracle.com [141.146.116.16])
        by userv0121.oracle.com (8.14.4/8.13.8) with ESMTP id 02HKiTZX030758;
        Tue, 17 Mar 2020 20:44:29 GMT
Received: from ban25x6uut29.us.oracle.com (/10.153.73.29) by default (Oracle
 Beehive Gateway v4.0) with ESMTP ; Tue, 17 Mar 2020 13:43:16 -0700
MIME-Version: 1.0
Message-ID: <20200317200537.21593-2-krish.sadhukhan@oracle.com>
Date: Tue, 17 Mar 2020 13:05:35 -0700 (PDT)
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com
Subject: [PATCH 1/3] kvm-unit-test: nSVM: Add alternative (v2) test format for
 nested guests
References: <20200317200537.21593-1-krish.sadhukhan@oracle.com>
In-Reply-To: <20200317200537.21593-1-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.20.1
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9563
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 malwarescore=0
 mlxlogscore=999
 mlxscore=0 spamscore=0 bulkscore=0 adultscore=0 suspectscore=15
 phishscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2003020000 definitions=main-2003170077
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9563
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 lowpriorityscore=0 mlxlogscore=999
 mlxscore=0 bulkscore=0 phishscore=0 spamscore=0 suspectscore=15
 malwarescore=0 priorityscore=1501 clxscore=1015 adultscore=0
 impostorscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2003020000 definitions=main-2003170077
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

..so that we can add tests such as VMCB consistency tests, that require
  the tests to only proceed up to the execution of the first guest (nested)
  instruction and do not require us to define all the functions that the
  current format dictates.

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 x86/svm.c       | 75 ++++++++++++++++++++++++++++++++++++++++++---------------
 x86/svm.h       |  6 +++++
 x86/svm_tests.c |  2 ++
 3 files changed, 63 insertions(+), 20 deletions(-)

```
#### 
##### 

```c
```
#### [PATCH 1/2 v2] kvm-unit-test: VMX: Add enum for GUEST_BNDCFGS field and LOAD_BNDCFGS vmentry control field
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11443823
Return-Path: <SRS0=C8aH=5C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AA1781392
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 17 Mar 2020 19:15:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 8A49120738
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 17 Mar 2020 19:15:54 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="K+Rb/qVd"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726575AbgCQTPx (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 17 Mar 2020 15:15:53 -0400
Received: from aserp2120.oracle.com ([141.146.126.78]:55054 "EHLO
        aserp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726388AbgCQTPx (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 17 Mar 2020 15:15:53 -0400
Received: from pps.filterd (aserp2120.oracle.com [127.0.0.1])
        by aserp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 02HJCiTx020725;
        Tue, 17 Mar 2020 19:15:48 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references; s=corp-2020-01-29;
 bh=fSfXYgyHzEMx9gbiq8n7yU8fgmIGczt0UqMQJeziZa0=;
 b=K+Rb/qVdu/sg4M703EQOoiXk0oECmtfQ3nOUcj+iaBM4ZExa8gzEVctANF32O1+qL6KR
 axpOTwKmfyH4ZacBPFfhX9Vk45J81gzTIoNVS9zym2oQsn8GxXMaVMVLPF4WFBS62A2q
 N+1F0O2WVjNKCJscT2uWmzcmlxcyawC7zQYMx3YokxFEXNOazLcSurnCj1oVB5ySYoz2
 bA2NutBxvANf3Q/NSrUpkd7YHoMTjtF3iWRsnNyLO480D/kd9nE9apyoPj5pxCbbHohh
 lPLqAI3EQZ6uicznapDFS+1O0REm48a2aDcZ5+xljMFXZUPs/2IQ3FyrFXGa3kBe9k8S dw==
Received: from aserp3030.oracle.com (aserp3030.oracle.com [141.146.126.71])
        by aserp2120.oracle.com with ESMTP id 2yrq7kxt8t-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 17 Mar 2020 19:15:48 +0000
Received: from pps.filterd (aserp3030.oracle.com [127.0.0.1])
        by aserp3030.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 02HJCvjB022088;
        Tue, 17 Mar 2020 19:15:47 GMT
Received: from userv0121.oracle.com (userv0121.oracle.com [156.151.31.72])
        by aserp3030.oracle.com with ESMTP id 2ys8tscwgk-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 17 Mar 2020 19:15:47 +0000
Received: from abhmp0017.oracle.com (abhmp0017.oracle.com [141.146.116.23])
        by userv0121.oracle.com (8.14.4/8.13.8) with ESMTP id 02HJFjgb025935;
        Tue, 17 Mar 2020 19:15:46 GMT
Received: from sadhukhan-nvmx.osdevelopmeniad.oraclevcn.com (/100.100.231.182)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Tue, 17 Mar 2020 12:15:45 -0700
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com,
        sean.j.christopherson@intel.com
Subject: [PATCH 1/2 v2] kvm-unit-test: VMX: Add enum for GUEST_BNDCFGS field
 and LOAD_BNDCFGS vmentry control field
Date: Tue, 17 Mar 2020 19:15:29 +0000
Message-Id: <1584472530-31728-2-git-send-email-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1584472530-31728-1-git-send-email-krish.sadhukhan@oracle.com>
References: <1584472530-31728-1-git-send-email-krish.sadhukhan@oracle.com>
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9563
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 adultscore=0
 phishscore=0 mlxscore=0
 malwarescore=0 suspectscore=13 mlxlogscore=999 spamscore=0 bulkscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2003020000
 definitions=main-2003170074
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9563
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 lowpriorityscore=0 suspectscore=13
 adultscore=0 bulkscore=0 mlxlogscore=999 priorityscore=1501 clxscore=1015
 malwarescore=0 mlxscore=0 phishscore=0 impostorscore=0 spamscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2003020000
 definitions=main-2003170074
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 x86/vmx.h | 2 ++
 1 file changed, 2 insertions(+)

```
#### [PATCH 1/2] KVM: x86: Add requested index to the CPUID tracepoint
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11443889
Return-Path: <SRS0=C8aH=5C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8797A913
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 17 Mar 2020 19:54:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 70EDE206EC
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 17 Mar 2020 19:54:07 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726555AbgCQTx4 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 17 Mar 2020 15:53:56 -0400
Received: from mga07.intel.com ([134.134.136.100]:43598 "EHLO mga07.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726294AbgCQTx4 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 17 Mar 2020 15:53:56 -0400
IronPort-SDR: 
 YAMXTaUQvhbfi9/EglHLIBThxC7TJN/SYy/Z1tvvfsLa3onwntOUlu4LFI0+jUaK0JwFKSVcaR
 iyTND9zr+BRg==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga007.jf.intel.com ([10.7.209.58])
  by orsmga105.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 17 Mar 2020 12:53:55 -0700
IronPort-SDR: 
 6bQH3deRFaoj7AMo2kEC84Wui6P91HGfgh+8j69z3O5xM+wIxLPd9Kp/jkmPr7vwKmp+RTVxnR
 WLm903I6jmQQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,565,1574150400";
   d="scan'208";a="233604300"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by orsmga007.jf.intel.com with ESMTP; 17 Mar 2020 12:53:55 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Xiaoyao Li <xiaoyao.li@intel.com>,
        Jan Kiszka <jan.kiszka@siemens.com>
Subject: [PATCH 1/2] KVM: x86: Add requested index to the CPUID tracepoint
Date: Tue, 17 Mar 2020 12:53:53 -0700
Message-Id: <20200317195354.28384-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20200317195354.28384-1-sean.j.christopherson@intel.com>
References: <20200317195354.28384-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Output the requested index when tracing CPUID emulation; it's basically
mandatory for leafs where the index is meaningful, and is helpful for
verifying KVM correctness even when the index isn't meaningful, e.g. the
trace for a Linux guest's hypervisor_cpuid_base() probing appears to
be broken (returns all zeroes) at first glance, but is correct because
the index is non-zero, i.e. the output values correspond to a random
index in the maximum basic leaf.

Suggested-by: Xiaoyao Li <xiaoyao.li@intel.com>
Cc: Jan Kiszka <jan.kiszka@siemens.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/cpuid.c |  2 +-
 arch/x86/kvm/trace.h | 13 ++++++++-----
 2 files changed, 9 insertions(+), 6 deletions(-)

```
#### [PATCH] KVM: x86: Expose AVX512 VP2INTERSECT in cpuid for TGL
##### From: Zhenyu Wang <zhenyuw@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhenyu Wang <zhenyuw@linux.intel.com>
X-Patchwork-Id: 11441885
Return-Path: <SRS0=C8aH=5C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4823D913
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 17 Mar 2020 06:55:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 32C3C2074D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 17 Mar 2020 06:55:31 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726272AbgCQGzG (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 17 Mar 2020 02:55:06 -0400
Received: from mga14.intel.com ([192.55.52.115]:25817 "EHLO mga14.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726207AbgCQGzF (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 17 Mar 2020 02:55:05 -0400
IronPort-SDR: 
 9URtp7CndDTfHErMEtxwd6mIexQMGiaZub9bvI7xpo62rRn3SrBAeLdJgXZaJvkNmOSFlIMzlV
 r8RsRuZ7xuyg==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga007.jf.intel.com ([10.7.209.58])
  by fmsmga103.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 16 Mar 2020 23:55:05 -0700
IronPort-SDR: 
 Ks2lyFR4oQi+/qPyHNM8E+gog2qCtpLm5wZsCX9HHOT8ta1lsCwXUxodY71dHg89zhK5itHWIN
 FBE4ui/9eucg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,563,1574150400";
   d="scan'208";a="233412448"
Received: from debian-skl.sh.intel.com ([10.239.160.44])
  by orsmga007.jf.intel.com with ESMTP; 16 Mar 2020 23:55:03 -0700
From: Zhenyu Wang <zhenyuw@linux.intel.com>
To: pbonzini@redhat.com
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        "Zhong, Yang" <yang.zhong@intel.com>
Subject: [PATCH] KVM: x86: Expose AVX512 VP2INTERSECT in cpuid for TGL
Date: Tue, 17 Mar 2020 14:55:53 +0800
Message-Id: <20200317065553.64790-1-zhenyuw@linux.intel.com>
X-Mailer: git-send-email 2.25.0.rc2
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

On Tigerlake new AVX512 VP2INTERSECT feature is available.
This would expose it for KVM supported cpuid.

Cc: "Zhong, Yang" <yang.zhong@intel.com>
Signed-off-by: Zhenyu Wang <zhenyuw@linux.intel.com>
---
 arch/x86/kvm/cpuid.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] kvm/x86: Reduce counter period change overhead and delay the effective time
##### From: Like Xu <like.xu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Like Xu <like.xu@linux.intel.com>
X-Patchwork-Id: 11441963
Return-Path: <SRS0=C8aH=5C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8CBE41667
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 17 Mar 2020 07:55:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7168720663
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 17 Mar 2020 07:55:56 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726077AbgCQHzr (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 17 Mar 2020 03:55:47 -0400
Received: from mga04.intel.com ([192.55.52.120]:45769 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725872AbgCQHzr (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 17 Mar 2020 03:55:47 -0400
IronPort-SDR: 
 /Hm/qcicNixH3kqTxbs+O+3dJLb4Jt6PP3Cqu3/GtmgKSjRYdUGXW/qy7Le92p0+wMapf+6AW1
 VtgoPra1XLBw==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga002.fm.intel.com ([10.253.24.26])
  by fmsmga104.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 17 Mar 2020 00:55:47 -0700
IronPort-SDR: 
 eOFSdfZVZQknN6RXM/9BeO2Nd2xpz2d7sQp4msxwVTTZseODz8LEN/z76AcPAdzF9Scm4iCM4c
 1r3hOkOnq9mg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,563,1574150400";
   d="scan'208";a="279314858"
Received: from sqa-gate.sh.intel.com (HELO clx-ap-likexu.tsp.org)
 ([10.239.48.212])
  by fmsmga002.fm.intel.com with ESMTP; 17 Mar 2020 00:55:44 -0700
From: Like Xu <like.xu@linux.intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Eric Hankland <ehankland@google.com>,
        Wanpeng Li <wanpengli@tencent.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Like Xu <like.xu@linux.intel.com>
Subject: [PATCH] kvm/x86: Reduce counter period change overhead and delay the
 effective time
Date: Tue, 17 Mar 2020 15:53:15 +0800
Message-Id: <20200317075315.70933-1-like.xu@linux.intel.com>
X-Mailer: git-send-email 2.21.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The cost of perf_event_period() is unstable, and when the guest samples
multiple events, the overhead increases dramatically (5378 ns on E5-2699).

For a non-running counter, the effective time of the new period is when
its corresponding enable bit is enabled. Calling perf_event_period()
in advance is superfluous. For a running counter, it's safe to delay the
effective time until the KVM_REQ_PMU event is handled. If there are
multiple perf_event_period() calls before handling KVM_REQ_PMU,
it helps to reduce the total cost.

Signed-off-by: Like Xu <like.xu@linux.intel.com>
---
 arch/x86/kvm/pmu.c           | 11 -----------
 arch/x86/kvm/pmu.h           | 11 +++++++++++
 arch/x86/kvm/vmx/pmu_intel.c | 10 ++++------
 3 files changed, 15 insertions(+), 17 deletions(-)

```
#### [PATCH v2 01/32] KVM: VMX: Flush all EPTP/VPID contexts on remote TLB flush
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11441803
Return-Path: <SRS0=C8aH=5C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 789461667
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 17 Mar 2020 04:56:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 625B920658
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 17 Mar 2020 04:56:01 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726787AbgCQExK (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 17 Mar 2020 00:53:10 -0400
Received: from mga04.intel.com ([192.55.52.120]:34097 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726769AbgCQExJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 17 Mar 2020 00:53:09 -0400
IronPort-SDR: 
 9srsuqLzq/C/FrDOlIBzBrwPWhMNNsZXK19aReCgmeIMPXAJKUwoB6sYh9rQ8dpnpGk5rTUgnI
 1V++kReEsPoA==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by fmsmga104.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 16 Mar 2020 21:53:09 -0700
IronPort-SDR: 
 4DUYEdUSKfeA49dlutWOLnwfCIrqTNcO7T5ZFwMo8tK8/cVfRpXpvUAsx/OElJZh50RppwXuoc
 JC1AA4fnkyiw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,563,1574150400";
   d="scan'208";a="355252727"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by fmsmga001.fm.intel.com with ESMTP; 16 Mar 2020 21:53:08 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Ben Gardon <bgardon@google.com>,
        Junaid Shahid <junaids@google.com>,
        Liran Alon <liran.alon@oracle.com>,
        Boris Ostrovsky <boris.ostrovsky@oracle.com>,
        John Haxby <john.haxby@oracle.com>,
        Miaohe Lin <linmiaohe@huawei.com>,
        Tom Lendacky <thomas.lendacky@amd.com>
Subject: [PATCH v2 01/32] KVM: VMX: Flush all EPTP/VPID contexts on remote TLB
 flush
Date: Mon, 16 Mar 2020 21:52:07 -0700
Message-Id: <20200317045238.30434-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20200317045238.30434-1-sean.j.christopherson@intel.com>
References: <20200317045238.30434-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Flush all EPTP/VPID contexts if a TLB flush _may_ have been triggered by
a remote or deferred TLB flush, i.e. by KVM_REQ_TLB_FLUSH.  Remote TLB
flushes require all contexts to be invalidated, not just the active
contexts, e.g. all mappings in all contexts for a given HVA need to be
invalidated on a mmu_notifier invalidation.  Similarly, the instigator
of the deferred TLB flush may be expecting all contexts to be flushed,
e.g. vmx_vcpu_load_vmcs().

Without nested VMX, flushing only the current EPTP/VPID context isn't
problematic because KVM uses a constant VPID for each vCPU, and
mmu_alloc_direct_roots() all but guarantees KVM will use a single EPTP
for L1.  In the rare case where a different EPTP is created or reused,
KVM (currently) unconditionally flushes the new EPTP context prior to
entering the guest.

With nested VMX, KVM conditionally uses a different VPID for L2, and
unconditionally uses a different EPTP for L2.  Because KVM doesn't
_intentionally_ guarantee L2's EPTP/VPID context is flushed on nested
VM-Enter, it'd be possible for a malicious L1 to attack the host and/or
different VMs by exploiting the lack of flushing for L2.

  1) Launch nested guest from malicious L1.

  2) Nested VM-Enter to L2.

  3) Access target GPA 'g'.  CPU inserts TLB entry tagged with L2's ASID
     mapping 'g' to host PFN 'x'.

  2) Nested VM-Exit to L1.

  3) L1 triggers kernel same-page merging (ksm) by duplicating/zeroing
     the page for PFN 'x'.

  4) Host kernel merges PFN 'x' with PFN 'y', i.e. unmaps PFN 'x' and
     remaps the page to PFN 'y'.  mmu_notifier sends invalidate command,
     KVM flushes TLB only for L1's ASID.

  4) Host kernel reallocates PFN 'x' to some other task/guest.

  5) Nested VM-Enter to L2.  KVM does not invalidate L2's EPTP or VPID.

  6) L2 accesses GPA 'g' and gains read/write access to PFN 'x' via its
     stale TLB entry.

However, current KVM unconditionally flushes L1's EPTP/VPID context on
nested VM-Exit.  But, that behavior is mostly unintentional, KVM doesn't
go out of its way to flush EPTP/VPID on nested VM-Enter/VM-Exit, rather
a TLB flush is guaranteed to occur prior to re-entering L1 due to
__kvm_mmu_new_cr3() always being called with skip_tlb_flush=false.  On
nested VM-Enter, this happens via kvm_init_shadow_ept_mmu() (nested EPT
enabled) or in nested_vmx_load_cr3() (nested EPT disabled).  On nested
VM-Exit it occurs via nested_vmx_load_cr3().

This also fixes a bug where a deferred TLB flush in the context of L2,
with EPT disabled, would flush L1's VPID instead of L2's VPID, as
vmx_flush_tlb() flushes L1's VPID regardless of is_guest_mode().

Cc: Vitaly Kuznetsov <vkuznets@redhat.com>
Cc: Ben Gardon <bgardon@google.com>
Cc: Jim Mattson <jmattson@google.com>
Cc: Junaid Shahid <junaids@google.com>
Cc: Liran Alon <liran.alon@oracle.com>
Cc: Boris Ostrovsky <boris.ostrovsky@oracle.com>
Cc: John Haxby <john.haxby@oracle.com>
Reviewed-by: Liran Alon <liran.alon@oracle.com>
Fixes: efebf0aaec3d ("KVM: nVMX: Do not flush TLB on L1<->L2 transitions if L1 uses VPID and EPT")
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/vmx/vmx.h | 28 +++++++++++++++++++++++++++-
 1 file changed, 27 insertions(+), 1 deletion(-)

```
#### [PATCH 09/12] docs: fix broken references for ReST files that moved around
##### From: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
X-Patchwork-Id: 11442897
Return-Path: <SRS0=C8aH=5C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 72747913
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 17 Mar 2020 13:11:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4ADC220754
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 17 Mar 2020 13:11:08 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1584450668;
	bh=OpWwr+Km4TTAToy65wz5kahjfMtDK5MxnhQXtb2oJcY=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=XEhwiBLL4y5CE/tZabvYZftek+LdFihdWYxiGhGQMnKK4Ndf9f0I1ON+GtAS4d+qR
	 RLtljhdFbLC2Yks5JlebYU+prk1wem6xkpFgpJwjH4NttoxIkJeVAFxIKsGbwiSrOr
	 KkNt8RAm7k02+rRmSdMEDaiy8AFLt0ZaUewdOXNA=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726956AbgCQNK7 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 17 Mar 2020 09:10:59 -0400
Received: from mail.kernel.org ([198.145.29.99]:37864 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726845AbgCQNK5 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 17 Mar 2020 09:10:57 -0400
Received: from mail.kernel.org (ip5f5ad4e9.dynamic.kabel-deutschland.de
 [95.90.212.233])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 246E92077B;
        Tue, 17 Mar 2020 13:10:56 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1584450656;
        bh=OpWwr+Km4TTAToy65wz5kahjfMtDK5MxnhQXtb2oJcY=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=Kl8fBUmrp3OvNgwKJOtJt/PT90JpUEB3vX7kd/7VsSBVfsl3/xX/QrBIv2MNpFe4u
         I3Wvx9p3nzZb9ODwkOjJsZvS+XdsCFRlvNkcuIogMe4dDffgLRo93z7hED6V6jcWqG
         C3XcWYTUlKORwDI37Vf4lPT0g+r7O4HkCB9Zsn6Q=
Received: from mchehab by mail.kernel.org with local (Exim 4.92.3)
        (envelope-from <mchehab@kernel.org>)
        id 1jEBzh-0006SO-RR; Tue, 17 Mar 2020 14:10:53 +0100
From: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
To: Linux Doc Mailing List <linux-doc@vger.kernel.org>
Cc: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>,
        linux-kernel@vger.kernel.org, Jonathan Corbet <corbet@lwn.net>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        "H. Peter Anvin" <hpa@zytor.com>, x86@kernel.org,
        Corentin Labbe <clabbe.montjoie@gmail.com>,
        Herbert Xu <herbert@gondor.apana.org.au>,
        "David S. Miller" <davem@davemloft.net>,
        Maxime Ripard <mripard@kernel.org>,
        Chen-Yu Tsai <wens@csie.org>, kvm@vger.kernel.org,
        linux-crypto@vger.kernel.org, linux-arm-kernel@lists.infradead.org
Subject: [PATCH 09/12] docs: fix broken references for ReST files that moved
 around
Date: Tue, 17 Mar 2020 14:10:48 +0100
Message-Id: 
 <6ea0adf72ae55935f3649f87e4b596830b616594.1584450500.git.mchehab+huawei@kernel.org>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <cover.1584450500.git.mchehab+huawei@kernel.org>
References: <cover.1584450500.git.mchehab+huawei@kernel.org>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Some broken references happened due to shifting files around
and ReST renames. Those can't be auto-fixed by the script,
so let's fix them manually.

Signed-off-by: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
---
 Documentation/doc-guide/maintainer-profile.rst      | 2 +-
 Documentation/virt/kvm/mmu.rst                      | 2 +-
 Documentation/virt/kvm/review-checklist.rst         | 2 +-
 arch/x86/kvm/mmu/mmu.c                              | 2 +-
 drivers/crypto/allwinner/sun8i-ce/sun8i-ce-cipher.c | 2 +-
 drivers/crypto/allwinner/sun8i-ce/sun8i-ce-core.c   | 2 +-
 drivers/crypto/allwinner/sun8i-ss/sun8i-ss-cipher.c | 2 +-
 drivers/crypto/allwinner/sun8i-ss/sun8i-ss-core.c   | 2 +-
 drivers/media/v4l2-core/v4l2-fwnode.c               | 2 +-
 include/uapi/linux/kvm.h                            | 4 ++--
 tools/include/uapi/linux/kvm.h                      | 4 ++--
 11 files changed, 13 insertions(+), 13 deletions(-)

```
#### [PATCH v2] KVM: x86/pmu: Reduce counter period change overhead and delay the effective time
##### From: Like Xu <like.xu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Like Xu <like.xu@linux.intel.com>
X-Patchwork-Id: 11442047
Return-Path: <SRS0=C8aH=5C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 987BC1668
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 17 Mar 2020 08:17:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 82A28205ED
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 17 Mar 2020 08:17:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725906AbgCQIRb (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 17 Mar 2020 04:17:31 -0400
Received: from mga11.intel.com ([192.55.52.93]:17620 "EHLO mga11.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725536AbgCQIRa (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 17 Mar 2020 04:17:30 -0400
IronPort-SDR: 
 JWpHzikvSX4FPH3+JvEfRalfolr5JXzm/ewvSdi61VKpicIbCcgt6CQHzPNDv1oJpKq/XdR1Oq
 s2g0FZz6rOnA==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga006.fm.intel.com ([10.253.24.20])
  by fmsmga102.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 17 Mar 2020 01:17:30 -0700
IronPort-SDR: 
 PogRVo52L4c/bHJT8ZMdD3bunGoSsLhHQc/kjfz1lqeJ2kBhfpOnK+G1yBjX10VJVMqJyVoXWX
 HHJzp5nQh2ig==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,563,1574150400";
   d="scan'208";a="445419123"
Received: from sqa-gate.sh.intel.com (HELO clx-ap-likexu.tsp.org)
 ([10.239.48.212])
  by fmsmga006.fm.intel.com with ESMTP; 17 Mar 2020 01:17:27 -0700
From: Like Xu <like.xu@linux.intel.com>
To: pbonzini@redhat.com, like.xu@linux.intel.com
Cc: ehankland@google.com, jmattson@google.com, joro@8bytes.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        sean.j.christopherson@intel.com, vkuznets@redhat.com,
        wanpengli@tencent.com
Subject: [PATCH v2] KVM: x86/pmu: Reduce counter period change overhead and
 delay the effective time
Date: Tue, 17 Mar 2020 16:14:58 +0800
Message-Id: <20200317081458.88714-1-like.xu@linux.intel.com>
X-Mailer: git-send-email 2.21.1
In-Reply-To: <20200317075315.70933-1-like.xu@linux.intel.com>
References: <20200317075315.70933-1-like.xu@linux.intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The cost of perf_event_period() is unstable, and when the guest samples
multiple events, the overhead increases dramatically (5378 ns on E5-2699).

For a non-running counter, the effective time of the new period is when
its corresponding enable bit is enabled. Calling perf_event_period()
in advance is superfluous. For a running counter, it's safe to delay the
effective time until the KVM_REQ_PMU event is handled. If there are
multiple perf_event_period() calls before handling KVM_REQ_PMU,
it helps to reduce the total cost.

Signed-off-by: Like Xu <like.xu@linux.intel.com>
---
 arch/x86/kvm/pmu.c           | 11 -----------
 arch/x86/kvm/pmu.h           | 11 +++++++++++
 arch/x86/kvm/vmx/pmu_intel.c | 10 ++++------
 3 files changed, 15 insertions(+), 17 deletions(-)

```
#### [PATCH v6 1/5] x86/kvm/hyper-v: Explicitly align hcall param for kvm_hyperv_exit
##### From: Jon Doron <arilou@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jon Doron <arilou@gmail.com>
X-Patchwork-Id: 11441669
Return-Path: <SRS0=C8aH=5C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C6AA992A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 17 Mar 2020 03:48:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A7D2220663
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 17 Mar 2020 03:48:30 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="N5bu65WG"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726444AbgCQDs2 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 16 Mar 2020 23:48:28 -0400
Received: from mail-wm1-f54.google.com ([209.85.128.54]:39680 "EHLO
        mail-wm1-f54.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726345AbgCQDs1 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 16 Mar 2020 23:48:27 -0400
Received: by mail-wm1-f54.google.com with SMTP id f7so20333322wml.4;
        Mon, 16 Mar 2020 20:48:26 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=0wyf1C6fvDgXY4wvk08Bh1opszF62aUSzjowFRYBQm0=;
        b=N5bu65WGQe4to2kj6cRbT91ksKW+ulaqmcan0SE0LeqlmvpjI38tsYN6oLpXkh8T4Q
         4HdOLIhAgJJsXh2NvydGHDESmU2B1J1fcJPwrDa2fo/mYy3k7zMLkXyDw0fzjGpeSHLQ
         zth4awAk10OfVpYiUec90RqnvkatGTPAt0hq7Im918p+9MxLLgv7hW2m6YS9v0Hq6H3E
         E6ygD0QSmBnUmBI5VN+fyGX2txlaVdi6ug81zX+Uczvoj72MWCySxn0N2tq47csgW7Hi
         Um0EfDREDyyK1WjiagHW86hfLIlKUSvZMidef4HRc8GTgzbPJO4tvg0rmvc5bBKalO1v
         UavQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=0wyf1C6fvDgXY4wvk08Bh1opszF62aUSzjowFRYBQm0=;
        b=o1xdNrrtgC7beY4kt63kgLVlGQSMi6mGgFCdc15E+xT03aN9PnolhRWS5tpIQQV0fA
         g0Ig3ggLpuFO1Gx+Nj21HVGwDnkyrRxOakbvZ+sjcMzoUYvtyLIw6RT52aa9zpGnDH9K
         lUYpUXx8h+J+6po+IJe2BYphONek7prwUG+jJhAHp1D7ChiYeFX+Bxn6kn/YSstYkhqH
         JI7iGvqRbmMvQBKnvDAS57soPdjLHmqCzpaKquRhrGhxckTJxlgDSIBX1xsn6N+VOLlM
         x5SpJOP7GDEmbvDIjZ+U/7PYKClMd/p9ggX2yQuJ5vvHtjfoAbBrqdfC4SJ6wFvOjLoQ
         +MZg==
X-Gm-Message-State: ANhLgQ2bY2W2TaHEmj7RvVjrGeTU2EHJjeNC0Q8boXsxgh8Qwhok8/yA
        kj+ZiHjBU272FCDFMw4JLnubBIIWonQ=
X-Google-Smtp-Source: 
 ADFU+vtjGgmes94M/UmfLe+nc+uaJFj49wmHRIBao9RmhseNbQ0AkiNQzvNZb3EMuqo7FsrZhqM4Qw==
X-Received: by 2002:a1c:5401:: with SMTP id i1mr2556256wmb.177.1584416905577;
        Mon, 16 Mar 2020 20:48:25 -0700 (PDT)
Received: from jondnuc.lan (IGLD-84-229-155-229.inter.net.il.
 [84.229.155.229])
        by smtp.gmail.com with ESMTPSA id
 c23sm1457757wrb.79.2020.03.16.20.48.24
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 16 Mar 2020 20:48:25 -0700 (PDT)
From: Jon Doron <arilou@gmail.com>
To: kvm@vger.kernel.org, linux-hyperv@vger.kernel.org
Cc: vkuznets@redhat.com, Jon Doron <arilou@gmail.com>
Subject: [PATCH v6 1/5] x86/kvm/hyper-v: Explicitly align hcall param for
 kvm_hyperv_exit
Date: Tue, 17 Mar 2020 05:48:00 +0200
Message-Id: <20200317034804.112538-2-arilou@gmail.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20200317034804.112538-1-arilou@gmail.com>
References: <20200317034804.112538-1-arilou@gmail.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Signed-off-by: Jon Doron <arilou@gmail.com>
---
 Documentation/virt/kvm/api.rst | 2 ++
 include/uapi/linux/kvm.h       | 2 ++
 2 files changed, 4 insertions(+)

```
