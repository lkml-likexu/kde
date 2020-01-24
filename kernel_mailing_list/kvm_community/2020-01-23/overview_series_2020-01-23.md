#### [PATCH v2 kvmtool 01/30] Makefile: Use correct objcopy binary when cross-compiling for x86_64
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexandru Elisei <alexandru.elisei@arm.com>
X-Patchwork-Id: 11347911
Return-Path: <SRS0=w9Mo=3M=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8D56B92A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 23 Jan 2020 13:48:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 6B4DD24689
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 23 Jan 2020 13:48:24 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728057AbgAWNsW (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 23 Jan 2020 08:48:22 -0500
Received: from foss.arm.com ([217.140.110.172]:39646 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726871AbgAWNsW (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 23 Jan 2020 08:48:22 -0500
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 9F9E91007;
        Thu, 23 Jan 2020 05:48:20 -0800 (PST)
Received: from e123195-lin.cambridge.arm.com (e123195-lin.cambridge.arm.com
 [10.1.196.63])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPA id
 95DEF3F68E;
        Thu, 23 Jan 2020 05:48:19 -0800 (PST)
From: Alexandru Elisei <alexandru.elisei@arm.com>
To: kvm@vger.kernel.org
Cc: will@kernel.org, julien.thierry.kdev@gmail.com,
        andre.przywara@arm.com, sami.mujawar@arm.com,
        lorenzo.pieralisi@arm.com, maz@kernel.org
Subject: [PATCH v2 kvmtool 01/30] Makefile: Use correct objcopy binary when
 cross-compiling for x86_64
Date: Thu, 23 Jan 2020 13:47:36 +0000
Message-Id: <20200123134805.1993-2-alexandru.elisei@arm.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20200123134805.1993-1-alexandru.elisei@arm.com>
References: <20200123134805.1993-1-alexandru.elisei@arm.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Use the compiler toolchain version of objcopy instead of the native one
when cross-compiling for the x86_64 architecture.

Reviewed-by: Andre Przywara <andre.przywara@arm.com>
Tested-by: Andre Przywara <andre.przywara@arm.com>
Signed-off-by: Alexandru Elisei <alexandru.elisei@arm.com>
---
 Makefile | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [PATCH v4 01/10] KVM: selftests: Create a demand paging testFrom: Ben Gardon <bgardon@google.com>
##### From: Ben Gardon <bgardon@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ben Gardon <bgardon@google.com>
X-Patchwork-Id: 11348885
Return-Path: <SRS0=w9Mo=3M=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 000D317EA
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 23 Jan 2020 18:04:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B6CB722522
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 23 Jan 2020 18:04:46 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="rnm/qkL6"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729017AbgAWSEp (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 23 Jan 2020 13:04:45 -0500
Received: from mail-pg1-f201.google.com ([209.85.215.201]:55610 "EHLO
        mail-pg1-f201.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729094AbgAWSEo (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 23 Jan 2020 13:04:44 -0500
Received: by mail-pg1-f201.google.com with SMTP id v30so2196293pga.22
        for <kvm@vger.kernel.org>; Thu, 23 Jan 2020 10:04:43 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=bMP1ivEYoLfoo6BRmP/QM19zZPKbKMUaSN+cV58XwBY=;
        b=rnm/qkL6XwvQ9ewRf1qRycdXFqb5Sc/cWvYqnoSrhLhSHPYOBflIrl6zCRlWo5s9c7
         R1KW07O0CsdrMUmZfVRF3jFppovxYZEbk45pgwA3Bka+ES+Sc+dEjzZbhxID/HRamGZ1
         lusNwskr7vLxyRgBKsT2fIVMuFU+oE1hKp4E9GBjqygrFuOjPGA0cREvQIRmcOLBML8C
         C9szYjrGKi7lGH2AXomELIOHnCAsyOxUER7a92ISYiAQbp5CZn05kwGlTf5dDlLdyVyX
         taypNkkDKPQWJEC8lDplD/JcOkwOS/xMRVlluZJAVCACUMZ1RCl43clTfulS0wq5ji2i
         lgLw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=bMP1ivEYoLfoo6BRmP/QM19zZPKbKMUaSN+cV58XwBY=;
        b=U7IYW5GpN/ZdTp/kW5sB7izFM/DmovZTGd205nBXjG9+ls46kz8y+0EQRgtDZjVRhj
         btDL0Fu6kPj6VZzkHhCN/dwpNeO4Esm+Iz/wYBukrTn6okpDdGOiYBc7OyhrRKxwYQsR
         LZwGIG8MtLPjbGNFHe5l3vS/aAiaFkzTqXXq7qHbTPpipr1AUpfh+X0d7EgVjeOEXRYz
         l5dQr8fMl5VRrlIGK6yvShsNjuzrvJKJiYFqNfPho1lFocGpXAUmHczXGWMwUcaQ1puH
         0b+mfxx6038RP7oNsWWzNvN40lGqalG7krgOLTQx+q5fIOFjqnu5s9dgdYQLSSZPLRTp
         flYw==
X-Gm-Message-State: APjAAAU44HlhY7HQ44s/ZyWn/F1ioh6VRcqYMogkWLL8mt2gFDFKj6oN
        FNO2UA9Q4KQW77hkL+PLOovd2lK80Jrz
X-Google-Smtp-Source: 
 APXvYqyPWFqxAvupwDLIpRrTc0OQgiU48aRNgUulYGhJGc5OflL7FrsXvdpC//WzGV7MjoQkLJnRcIzWZ8aM
X-Received: by 2002:a65:6914:: with SMTP id s20mr31136pgq.44.1579802683140;
 Thu, 23 Jan 2020 10:04:43 -0800 (PST)
Date: Thu, 23 Jan 2020 10:04:27 -0800
In-Reply-To: <20200123180436.99487-1-bgardon@google.com>
Message-Id: <20200123180436.99487-2-bgardon@google.com>
Mime-Version: 1.0
References: <20200123180436.99487-1-bgardon@google.com>
X-Mailer: git-send-email 2.25.0.341.g760bfbb309-goog
Subject: [PATCH v4 01/10] KVM: selftests: Create a demand paging test
From: Ben Gardon <bgardon@google.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        linux-kselftest@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Cannon Matthews <cannonmatthews@google.com>,
        Peter Xu <peterx@redhat.com>,
        Andrew Jones <drjones@redhat.com>,
        Peter Shier <pshier@google.com>,
        Oliver Upton <oupton@google.com>,
        Ben Gardon <bgardon@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

While userfaultfd, KVM's demand paging implementation, is not specific
to KVM, having a benchmark for its performance will be useful for
guiding performance improvements to KVM. As a first step towards creating
a userfaultfd demand paging test, create a simple memory access test,
based on dirty_log_test.

Reviewed-by: Oliver Upton <oupton@google.com>
Signed-off-by: Ben Gardon <bgardon@google.com>
---
 tools/testing/selftests/kvm/.gitignore        |   1 +
 tools/testing/selftests/kvm/Makefile          |   3 +
 .../selftests/kvm/demand_paging_test.c        | 286 ++++++++++++++++++
 3 files changed, 290 insertions(+)
 create mode 100644 tools/testing/selftests/kvm/demand_paging_test.c

```
#### [PATCH] KVM: nVMX: delete meaningless nested_vmx_run() declaration
##### From: linmiaohe <linmiaohe@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: linmiaohe <linmiaohe@huawei.com>
X-Patchwork-Id: 11346691
Return-Path: <SRS0=w9Mo=3M=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1D7746C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 23 Jan 2020 02:06:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 055B724125
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 23 Jan 2020 02:06:37 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726227AbgAWCGa (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 22 Jan 2020 21:06:30 -0500
Received: from szxga04-in.huawei.com ([45.249.212.190]:10131 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1725911AbgAWCGa (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 22 Jan 2020 21:06:30 -0500
Received: from DGGEMS404-HUB.china.huawei.com (unknown [172.30.72.59])
        by Forcepoint Email with ESMTP id 1B545BF418CF57AB050E;
        Thu, 23 Jan 2020 10:06:28 +0800 (CST)
Received: from huawei.com (10.175.105.18) by DGGEMS404-HUB.china.huawei.com
 (10.3.19.204) with Microsoft SMTP Server id 14.3.439.0; Thu, 23 Jan 2020
 10:06:17 +0800
From: linmiaohe <linmiaohe@huawei.com>
To: <pbonzini@redhat.com>, <rkrcmar@redhat.com>,
        <sean.j.christopherson@intel.com>, <vkuznets@redhat.com>,
        <wanpengli@tencent.com>, <jmattson@google.com>, <joro@8bytes.org>,
        <tglx@linutronix.de>, <mingo@redhat.com>, <bp@alien8.de>,
        <hpa@zytor.com>
CC: <linmiaohe@huawei.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <x86@kernel.org>
Subject: [PATCH] KVM: nVMX: delete meaningless nested_vmx_run() declaration
Date: Thu, 23 Jan 2020 10:08:20 +0800
Message-ID: <1579745300-13029-1-git-send-email-linmiaohe@huawei.com>
X-Mailer: git-send-email 1.8.3.1
MIME-Version: 1.0
X-Originating-IP: [10.175.105.18]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Miaohe Lin <linmiaohe@huawei.com>

The function nested_vmx_run() declaration is below its implementation. So
this is meaningless and should be removed.

Signed-off-by: Miaohe Lin <linmiaohe@huawei.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Reviewed-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 arch/x86/kvm/vmx/nested.c | 2 --
 1 file changed, 2 deletions(-)

```
#### [PATCH] KVM: nVMX: set rflags to specify success in handle_invvpid() default case
##### From: linmiaohe <linmiaohe@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: linmiaohe <linmiaohe@huawei.com>
X-Patchwork-Id: 11346717
Return-Path: <SRS0=w9Mo=3M=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 44C596C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 23 Jan 2020 03:12:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 236412465B
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 23 Jan 2020 03:12:15 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726181AbgAWDMI (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 22 Jan 2020 22:12:08 -0500
Received: from szxga05-in.huawei.com ([45.249.212.191]:9236 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1725911AbgAWDMI (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 22 Jan 2020 22:12:08 -0500
Received: from DGGEMS402-HUB.china.huawei.com (unknown [172.30.72.58])
        by Forcepoint Email with ESMTP id 38780C59AB2450DB0290;
        Thu, 23 Jan 2020 11:12:05 +0800 (CST)
Received: from huawei.com (10.175.105.18) by DGGEMS402-HUB.china.huawei.com
 (10.3.19.202) with Microsoft SMTP Server id 14.3.439.0; Thu, 23 Jan 2020
 11:11:58 +0800
From: linmiaohe <linmiaohe@huawei.com>
To: <pbonzini@redhat.com>, <rkrcmar@redhat.com>,
        <sean.j.christopherson@intel.com>, <vkuznets@redhat.com>,
        <wanpengli@tencent.com>, <jmattson@google.com>, <joro@8bytes.org>,
        <tglx@linutronix.de>, <mingo@redhat.com>, <bp@alien8.de>,
        <hpa@zytor.com>
CC: <linmiaohe@huawei.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <x86@kernel.org>
Subject: [PATCH] KVM: nVMX: set rflags to specify success in handle_invvpid()
 default case
Date: Thu, 23 Jan 2020 11:14:01 +0800
Message-ID: <1579749241-712-1-git-send-email-linmiaohe@huawei.com>
X-Mailer: git-send-email 1.8.3.1
MIME-Version: 1.0
X-Originating-IP: [10.175.105.18]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Miaohe Lin <linmiaohe@huawei.com>

In handle_invvpid() default case, we just skip emulated instruction and
forget to set rflags to specify success. This would result in indefinite
rflags value and thus indeterminate return value for guest.

Signed-off-by: Miaohe Lin <linmiaohe@huawei.com>
---
	Chinese New Year is coming. Happy Spring Festival! ^_^
---
 arch/x86/kvm/vmx/nested.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH] s390x: Add cpu id to interrupt error prints
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11347211
Return-Path: <SRS0=w9Mo=3M=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DEADC109A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 23 Jan 2020 10:04:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id C64BE24684
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 23 Jan 2020 10:04:04 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728665AbgAWKEE (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 23 Jan 2020 05:04:04 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:32888 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727278AbgAWKED (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 23 Jan 2020 05:04:03 -0500
Received: from pps.filterd (m0098409.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 00N9v6hU083615
        for <kvm@vger.kernel.org>; Thu, 23 Jan 2020 05:04:03 -0500
Received: from e06smtp07.uk.ibm.com (e06smtp07.uk.ibm.com [195.75.94.103])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2xnx9cqe56-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Thu, 23 Jan 2020 05:04:02 -0500
Received: from localhost
        by e06smtp07.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Thu, 23 Jan 2020 10:04:00 -0000
Received: from b06cxnps3074.portsmouth.uk.ibm.com (9.149.109.194)
        by e06smtp07.uk.ibm.com (192.168.101.137) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Thu, 23 Jan 2020 10:03:58 -0000
Received: from d06av24.portsmouth.uk.ibm.com (d06av24.portsmouth.uk.ibm.com
 [9.149.105.60])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 00NA3vhr58917046
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 23 Jan 2020 10:03:57 GMT
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id D29E242045;
        Thu, 23 Jan 2020 10:03:57 +0000 (GMT)
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id E5CED42041;
        Thu, 23 Jan 2020 10:03:56 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.152.224.146])
        by d06av24.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Thu, 23 Jan 2020 10:03:56 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: thuth@redhat.com, borntraeger@de.ibm.com,
        linux-s390@vger.kernel.org, david@redhat.com, cohuck@redhat.com
Subject: [kvm-unit-tests PATCH] s390x: Add cpu id to interrupt error prints
Date: Thu, 23 Jan 2020 05:03:53 -0500
X-Mailer: git-send-email 2.20.1
In-Reply-To: <0eb69c66-5aa7-1609-9de0-c3d0efaed30a@linux.ibm.com>
References: <0eb69c66-5aa7-1609-9de0-c3d0efaed30a@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 20012310-0028-0000-0000-000003D3AD74
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 20012310-0029-0000-0000-00002497E807
Message-Id: <20200123100353.13501-1-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-01-23_01:2020-01-23,2020-01-22 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 malwarescore=0 spamscore=0
 priorityscore=1501 impostorscore=0 bulkscore=0 clxscore=1015
 lowpriorityscore=0 mlxlogscore=754 phishscore=0 mlxscore=0 suspectscore=1
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-1910280000 definitions=main-2001230085
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

It's good to know which cpu broke the test.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---

Fixed stap location in ext handler.


---
 lib/s390x/interrupt.c | 20 ++++++++++----------
 1 file changed, 10 insertions(+), 10 deletions(-)

```
#### [kvm-unit-tests PATCH] s390x: smp: Rework cpu start and active tracking
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11347105
Return-Path: <SRS0=w9Mo=3M=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4D25813A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 23 Jan 2020 09:14:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 358402467E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 23 Jan 2020 09:14:45 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726188AbgAWJOo (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 23 Jan 2020 04:14:44 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:41832 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1725785AbgAWJOo (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 23 Jan 2020 04:14:44 -0500
Received: from pps.filterd (m0098399.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 00N9DCbK050516
        for <kvm@vger.kernel.org>; Thu, 23 Jan 2020 04:14:43 -0500
Received: from e06smtp05.uk.ibm.com (e06smtp05.uk.ibm.com [195.75.94.101])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2xp3u88m55-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Thu, 23 Jan 2020 04:14:42 -0500
Received: from localhost
        by e06smtp05.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Thu, 23 Jan 2020 09:14:40 -0000
Received: from b06cxnps4075.portsmouth.uk.ibm.com (9.149.109.197)
        by e06smtp05.uk.ibm.com (192.168.101.135) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Thu, 23 Jan 2020 09:14:38 -0000
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06cxnps4075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 00N9EbWQ60293258
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 23 Jan 2020 09:14:37 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 41C84A4066;
        Thu, 23 Jan 2020 09:14:37 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 55D8EA4054;
        Thu, 23 Jan 2020 09:14:36 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.152.224.146])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Thu, 23 Jan 2020 09:14:36 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: thuth@redhat.com, borntraeger@de.ibm.com,
        linux-s390@vger.kernel.org, david@redhat.com, cohuck@redhat.com
Subject: [kvm-unit-tests PATCH] s390x: smp: Rework cpu start and active
 tracking
Date: Thu, 23 Jan 2020 04:14:21 -0500
X-Mailer: git-send-email 2.20.1
In-Reply-To: <bf356a2c-702e-0ecd-d24c-f7a1b7c18d2a@redhat.com>
References: <bf356a2c-702e-0ecd-d24c-f7a1b7c18d2a@redhat.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 20012309-0020-0000-0000-000003A33EDD
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 20012309-0021-0000-0000-000021FAD773
Message-Id: <20200123091421.3409-1-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-01-23_01:2020-01-23,2020-01-22 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 phishscore=0 bulkscore=0
 adultscore=0 mlxlogscore=881 lowpriorityscore=0 mlxscore=0 spamscore=0
 malwarescore=0 priorityscore=1501 impostorscore=0 suspectscore=1
 clxscore=1015 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-1910280000 definitions=main-2001230079
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The architecture specifies that processing sigp orders may be
asynchronous, and this is indeed the case on some hypervisors, so we
need to wait until the cpu runs before we return from the setup/start
function.

As there was a lot of duplicate code, a common function for cpu
restarts has been introduced.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---
 lib/s390x/smp.c | 56 ++++++++++++++++++++++++++++++-------------------
 1 file changed, 35 insertions(+), 21 deletions(-)

```
#### [PATCH] KVM: x86: avoid some unnecessary copy in __x86_set_memory_region()
##### From: linmiaohe <linmiaohe@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: linmiaohe <linmiaohe@huawei.com>
X-Patchwork-Id: 11346715
Return-Path: <SRS0=w9Mo=3M=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E344617EF
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 23 Jan 2020 02:58:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id C5F4D24125
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 23 Jan 2020 02:58:37 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726118AbgAWC60 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 22 Jan 2020 21:58:26 -0500
Received: from szxga06-in.huawei.com ([45.249.212.32]:47510 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1725911AbgAWC60 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 22 Jan 2020 21:58:26 -0500
Received: from DGGEMS402-HUB.china.huawei.com (unknown [172.30.72.59])
        by Forcepoint Email with ESMTP id ABB2152DA18A987470E2;
        Thu, 23 Jan 2020 10:58:23 +0800 (CST)
Received: from huawei.com (10.175.105.18) by DGGEMS402-HUB.china.huawei.com
 (10.3.19.202) with Microsoft SMTP Server id 14.3.439.0; Thu, 23 Jan 2020
 10:58:13 +0800
From: linmiaohe <linmiaohe@huawei.com>
To: <pbonzini@redhat.com>, <rkrcmar@redhat.com>,
        <sean.j.christopherson@intel.com>, <vkuznets@redhat.com>,
        <wanpengli@tencent.com>, <jmattson@google.com>, <joro@8bytes.org>,
        <tglx@linutronix.de>, <mingo@redhat.com>, <bp@alien8.de>,
        <hpa@zytor.com>
CC: <linmiaohe@huawei.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <x86@kernel.org>
Subject: [PATCH] KVM: x86: avoid some unnecessary copy in
 __x86_set_memory_region()
Date: Thu, 23 Jan 2020 11:00:13 +0800
Message-ID: <1579748413-432-1-git-send-email-linmiaohe@huawei.com>
X-Mailer: git-send-email 1.8.3.1
MIME-Version: 1.0
X-Originating-IP: [10.175.105.18]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Miaohe Lin <linmiaohe@huawei.com>

Only userspace_addr and npages are passed to vm_munmap() when remove a
memory region. So we shouldn't copy the integral kvm_memory_slot struct.

No functional change intended.

Signed-off-by: Miaohe Lin <linmiaohe@huawei.com>
---
 arch/x86/kvm/x86.c | 9 +++++----
 1 file changed, 5 insertions(+), 4 deletions(-)

```
#### [PATCH v2] KVM: x86: fix overlap between SPTE_MMIO_MASK and generation
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11347071
Return-Path: <SRS0=w9Mo=3M=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F419A13A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 23 Jan 2020 08:50:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id CEF052087E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 23 Jan 2020 08:50:52 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="Bcdjx5nP"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728057AbgAWIut (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 23 Jan 2020 03:50:49 -0500
Received: from mail-wm1-f68.google.com ([209.85.128.68]:52577 "EHLO
        mail-wm1-f68.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726194AbgAWIut (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 23 Jan 2020 03:50:49 -0500
Received: by mail-wm1-f68.google.com with SMTP id p9so1642932wmc.2;
        Thu, 23 Jan 2020 00:50:47 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id;
        bh=ocf97TvHPaFYNxscXDRJHUBlARjdRQtQP9awJzp3ggM=;
        b=Bcdjx5nP2PyF1pD8yL4cLQIT8pTkxYXjeP4r69kS+xEJBu1ilgChEknhOfsLIpb/m1
         uYUwh2rCIbs01lUBhwr9Ou1/mCfI0nKcdIrUIB2LgaDUPXETNPOZkVl9LFWp7/DHO28m
         W4iygarapFuxapjwDs7UG+d7Fox3AnM9UMgjmLwHF4ALPAWBMFP1VyRW/p7TKSafRqOB
         GVTkXg7fZCad8ImlnWFtG9YHq7koXjsBLfQlJo7I01WC2kYc5if3fkIfkk8g6RommRYQ
         pu5M6GaJsOV0WH1QBgMfYxS35e3Tnt5AvAIcszGPVbJMHyG6oGdISsmqZ+k06tEgcIF4
         vogw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id;
        bh=ocf97TvHPaFYNxscXDRJHUBlARjdRQtQP9awJzp3ggM=;
        b=M1PIcahXXPQaXEXC9qQnvv73hdFoNPMNmhWBGb3MQ/DBhV3YaO154wXXYLddtz76ZL
         o2Ioqg3yGv13cPKO0BYzj82sgE2NOsLeQ13M832ocjpRPcf61WiM8KWRe1vBRnQBHJrN
         trHk7YMl25eik7kZCm6J9s9+g1xLeA+5NgxE4s6dv1BbYaVAJNk0rw6IabF2Y/LPYESZ
         wsft5gyqSkFQdk18v4zQrM1OfWD7SGwoZ6yHCPRJ1YO22CzUFxJhstmtp/68eUL3je6Z
         bC8i1jyHemDj6KIs5ooxqEShymqPIDVCt6znz2d4MVaq3YmG31nPT5LpZkSPIEA0ihZv
         OlOg==
X-Gm-Message-State: APjAAAWCdQkjnMJCV6w6gvYUzp6OqiWjK093XFq5ZZ+7FZ5RZn0kggIy
        X4mW8sSnzRXbGna0be+JWbTY3j2O
X-Google-Smtp-Source: 
 APXvYqyCK86pGbQYwiwOZKZZWQekIpHNgNyyVHOM0H3y6SCCn8bVX3KEWezFnmRAmGxSKEL2HCBFYw==
X-Received: by 2002:a05:600c:2150:: with SMTP id
 v16mr2907767wml.156.1579769446157;
        Thu, 23 Jan 2020 00:50:46 -0800 (PST)
Received: from 640k.localdomain.com ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 b16sm2198739wrj.23.2020.01.23.00.50.45
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Thu, 23 Jan 2020 00:50:45 -0800 (PST)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Ben Gardon <bgardon@google.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        stable@vger.kernel.org
Subject: [PATCH v2] KVM: x86: fix overlap between SPTE_MMIO_MASK and
 generation
Date: Thu, 23 Jan 2020 09:50:42 +0100
Message-Id: <1579769442-13698-1-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The SPTE_MMIO_MASK overlaps with the bits used to track MMIO
generation number.  A high enough generation number would overwrite the
SPTE_SPECIAL_MASK region and cause the MMIO SPTE to be misinterpreted.

Likewise, setting bits 52 and 53 would also cause an incorrect generation
number to be read from the PTE, though this was partially mitigated by the
(useless if it weren't for the bug) removal of SPTE_SPECIAL_MASK from
the spte in get_mmio_spte_generation.  Drop that removal, and replace
it with a compile-time assertion.

Fixes: 6eeb4ef049e7 ("KVM: x86: assign two bits to track SPTE kinds")
Reported-by: Ben Gardon <bgardon@google.com>
Cc: stable@vger.kernel.org
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Ben Gardon <bgardon@google.com>
---
 arch/x86/kvm/mmu/mmu.c | 10 +++++-----
 1 file changed, 5 insertions(+), 5 deletions(-)

```
#### [PATCH v2] x86/cpu: Move prototype for get_umwait_control_msr() to global location
##### From: Benjamin Thiel <b.thiel@posteo.de>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Benjamin Thiel <b.thiel@posteo.de>
X-Patchwork-Id: 11348829
Return-Path: <SRS0=w9Mo=3M=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1262D1398
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 23 Jan 2020 17:30:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E427321569
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 23 Jan 2020 17:30:12 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=posteo.de header.i=@posteo.de
 header.b="B/+QAD5P"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729012AbgAWRaM (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 23 Jan 2020 12:30:12 -0500
Received: from mout02.posteo.de ([185.67.36.66]:39953 "EHLO mout02.posteo.de"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727296AbgAWRaK (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 23 Jan 2020 12:30:10 -0500
Received: from submission (posteo.de [89.146.220.130])
        by mout02.posteo.de (Postfix) with ESMTPS id 1BAB92400FE
        for <kvm@vger.kernel.org>; Thu, 23 Jan 2020 18:30:08 +0100 (CET)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=posteo.de; s=2017;
        t=1579800608; bh=jswBLxzmjtwYk5Kuv4nAGpKgQNsVvBOU2fXHpQ4y5Gs=;
        h=From:To:Cc:Subject:Date:From;
        b=B/+QAD5PeIhk8ZzLMAIJLIf3n/rKfM3CU3W8F4FslYtVshYN8F+1kpTEn7+IrqA5G
         XJ05YHac7uYguFVgEP8OF8ksjX8QCn9s+VvzFPGRTqV8mQQ+bEpH2aM7QVXcEGdMYE
         YO/PZX68RhqNtZ9MZove5GVY2KaQinsMXLqFulaoewxct1IC3U5rRFUO9McT53dRN+
         IRSGC2FM/w5Pkgh7RVn0PHy4BwA0RB9dQcWRuKNGuZvVrZCA2NJZNscR8wH25TZKCJ
         LLCzB6WdzmxLOWK3LGRCEOr0+f89yBqt+rlmXnKhs9D/oI53YAznDfawUaqL4wmzKg
         30VhPiBrLuEEQ==
Received: from customer (localhost [127.0.0.1])
        by submission (posteo.de) with ESMTPSA id 483Tmv4HFFz9rxM;
        Thu, 23 Jan 2020 18:30:07 +0100 (CET)
From: Benjamin Thiel <b.thiel@posteo.de>
To: kvm@vger.kernel.org
Cc: X86 ML <x86@kernel.org>, LKML <linux-kernel@vger.kernel.org>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Benjamin Thiel <b.thiel@posteo.de>
Subject: [PATCH v2] x86/cpu: Move prototype for get_umwait_control_msr() to
 global location
Date: Thu, 23 Jan 2020 18:29:45 +0100
Message-Id: <20200123172945.7235-1-b.thiel@posteo.de>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

.. in order to fix a -Wmissing-prototype warning.

No functional change.

Signed-off-by: Benjamin Thiel <b.thiel@posteo.de>
---
 arch/x86/include/asm/mwait.h | 2 ++
 arch/x86/kernel/cpu/umwait.c | 1 +
 arch/x86/kvm/vmx/vmx.c       | 1 +
 arch/x86/kvm/vmx/vmx.h       | 2 --
 4 files changed, 4 insertions(+), 2 deletions(-)

```
#### [PATCH] x86/cpu: Move prototype for get_umwait_control_msr() to global location
##### From: Benjamin Thiel <b.thiel@posteo.de>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Benjamin Thiel <b.thiel@posteo.de>
X-Patchwork-Id: 11348137
Return-Path: <SRS0=w9Mo=3M=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 143A3139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 23 Jan 2020 14:01:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E5C942467F
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 23 Jan 2020 14:01:22 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=posteo.de header.i=@posteo.de
 header.b="EyV02xAn"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729016AbgAWOBW (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 23 Jan 2020 09:01:22 -0500
Received: from mout02.posteo.de ([185.67.36.66]:57195 "EHLO mout02.posteo.de"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726796AbgAWOBU (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 23 Jan 2020 09:01:20 -0500
Received: from submission (posteo.de [89.146.220.130])
        by mout02.posteo.de (Postfix) with ESMTPS id 096EE2400FE
        for <kvm@vger.kernel.org>; Thu, 23 Jan 2020 15:01:17 +0100 (CET)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=posteo.de; s=2017;
        t=1579788077; bh=ZVtVWPk2nLjF6dSYv8YBCQyVws1d8uWihyfKP1Ac6VI=;
        h=From:To:Cc:Subject:Date:From;
        b=EyV02xAnENVfXhyv4Lhbtdbc/olaRO5FYvIkqCnWKpl/4uChQbKdPJwpQ986uX9m0
         6wLwTgXbJp+dpo5ZyG6OBhZW7yklu4U5ynvToY0PCa/zPyBvzJYzCrGJ4hTEjX64yL
         gn6d8680yoI0EVTEVK8hmVy7APo/RHLI5ohdMyuAbxtHrnggAdncYlHT3MkSXtUex4
         YRkSjTz9DeaGpVQJbs9AQMF894DtHWn93BXa1WMWlwq/9jGJvL4QoQgJb9+EHGomA4
         3zoHSly76K9sb9zpvHwD/CUGGW903PJZHgRMCqapLpFvI7S0nGvYx/so/1/x4fbt4Q
         A0qr4x0ZcMgKw==
Received: from customer (localhost [127.0.0.1])
        by submission (posteo.de) with ESMTPSA id 483P7w5D0gz9rxS;
        Thu, 23 Jan 2020 15:01:16 +0100 (CET)
From: Benjamin Thiel <b.thiel@posteo.de>
To: X86 ML <x86@kernel.org>
Cc: kvm@vger.kernel.org, LKML <linux-kernel@vger.kernel.org>,
        Benjamin Thiel <b.thiel@posteo.de>
Subject: [PATCH] x86/cpu: Move prototype for get_umwait_control_msr() to
 global location
Date: Thu, 23 Jan 2020 15:01:13 +0100
Message-Id: <20200123140113.8447-1-b.thiel@posteo.de>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

.. in order to fix a -Wmissing-prototype warning.

No functional change.

Signed-off-by: Benjamin Thiel <b.thiel@posteo.de>
---
 arch/x86/include/asm/mwait.h | 2 ++
 arch/x86/kernel/cpu/umwait.c | 1 +
 arch/x86/kvm/vmx/vmx.c       | 1 +
 arch/x86/kvm/vmx/vmx.h       | 2 --
 4 files changed, 4 insertions(+), 2 deletions(-)

```
