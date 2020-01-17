#### [PATCH] KVM: Adding 'else' to reduce checking.
##### From: Haiwei Li <lihaiwei.kernel@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Haiwei Li <lihaiwei.kernel@gmail.com>
X-Patchwork-Id: 11336129
Return-Path: <SRS0=nLL1=3F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 834C592A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Jan 2020 06:03:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5ABE1208C3
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Jan 2020 06:03:18 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="Jl3n9t2/"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729546AbgAPGDP (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 16 Jan 2020 01:03:15 -0500
Received: from mail-pj1-f67.google.com ([209.85.216.67]:51715 "EHLO
        mail-pj1-f67.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727026AbgAPGDP (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 16 Jan 2020 01:03:15 -0500
Received: by mail-pj1-f67.google.com with SMTP id d15so1024902pjw.1;
        Wed, 15 Jan 2020 22:03:14 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=to:cc:from:subject:message-id:date:user-agent:mime-version
         :content-language:content-transfer-encoding;
        bh=dPqB30Bque1a9xdQca0yHVUONu8Rkkk23AZbtBFoqN0=;
        b=Jl3n9t2/YTDOuYoiVgGPHFsJsyZ3+fU3dIIf8t9Iwil/iQtRl6iU+ydPdNETEDxZXQ
         S0mZAwv2gG7bTooBUzPiH+qTTdpUAwmAJEOL8weqbTj9F50Bh1AmkwTQ6uFurcp5Ewzc
         NIKhfnXGn/p2m+FAs59d+4f+Un+V0WomKNDHt2aRbOvGUNwHS3kMo6+4z9dmTCjroJ50
         knbv2fpyA2lYn4IU3OKYMd+Qz9FkwPzCVyruxkfHGZxTgRKux5R17NfoSdBJx4yEcuki
         f8UDl7GSNPArYDNtaK4T4XIyePvR49+MOIAspG1jsChLqP7rEOMZUVzCRXmvTGpDzC1M
         xYfw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:to:cc:from:subject:message-id:date:user-agent
         :mime-version:content-language:content-transfer-encoding;
        bh=dPqB30Bque1a9xdQca0yHVUONu8Rkkk23AZbtBFoqN0=;
        b=RZWh6WrnvRLxGDJ7zFaLlg70O8+1WloBnI+erZxwVhYZGYDAiBoHySS6FlscQGROSj
         h7loU8yAnFtxbgbEEKzTkGlzc93V+Wl7i6LN0fvNa46b2neh7J7SDNLa386RIr8sYZeb
         KsykIYsuKIymb87fa0GhO+JC7jH+uULa9a/zinaTty/+VJmbJNpyez2+9yPbDSIJ80/K
         3+09zcr3B/QQzQ/rmGYmr5P6+wIOkucJ/VogdreYqRKbqA5crx4oh2iykwDyOpcmQBTB
         zzrP5ipA6OnNpwGOCsgRy/rHJ1d5SdRpNbjBxHGdQbgva+GTlfaniiQQpceHQR19iQ9D
         tg7Q==
X-Gm-Message-State: APjAAAX3XC4+joGzzpHVTorzfjWr84QOdxjlSyDdMAXCCwkiX4wgtQn1
        IPyun4s9Km7t9UNOW9qq/g==
X-Google-Smtp-Source: 
 APXvYqz3LduDxHDVbF5g2WN3h6iZ3dA8WNbXYcZfN0VJe6IA8uAo9nRsS6DW76p0g3x2WMGQiak9lg==
X-Received: by 2002:a17:90a:b30b:: with SMTP id
 d11mr4723790pjr.22.1579154594426;
        Wed, 15 Jan 2020 22:03:14 -0800 (PST)
Received: from [127.0.0.1] ([103.7.29.9])
        by smtp.gmail.com with ESMTPSA id
 q6sm23636677pfh.127.2020.01.15.22.03.10
        (version=TLS1_3 cipher=TLS_AES_128_GCM_SHA256 bits=128/128);
        Wed, 15 Jan 2020 22:03:13 -0800 (PST)
To: "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>,
        "kvm@vger.kernel.org" <kvm@vger.kernel.org>,
        "x86@kernel.org" <x86@kernel.org>
Cc: "pbonzini@redhat.com" <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        "vkuznets@redhat.com" <vkuznets@redhat.com>,
        "wanpengli@tencent.com" <wanpengli@tencent.com>,
        "jmattson@google.com" <jmattson@google.com>,
        "joro@8bytes.org" <joro@8bytes.org>,
        "tglx@linutronix.de" <tglx@linutronix.de>,
        "mingo@redhat.com" <mingo@redhat.com>, bp@alien8.de,
        "hpa@zytor.com" <hpa@zytor.com>
From: Haiwei Li <lihaiwei.kernel@gmail.com>
Subject: [PATCH] KVM: Adding 'else' to reduce checking.
Message-ID: <2a1a3b72-acc5-4977-5621-439aac53f243@gmail.com>
Date: Thu, 16 Jan 2020 14:03:04 +0800
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:68.0)
 Gecko/20100101 Thunderbird/68.3.1
MIME-Version: 1.0
Content-Language: en-US
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From 4e19436679a97e3cee73b4ae613ff91580c721d2 Mon Sep 17 00:00:00 2001
From: Haiwei Li <lihaiwei@tencent.com>
Date: Thu, 16 Jan 2020 13:51:03 +0800
Subject: [PATCH] Adding 'else' to reduce checking.

These two conditions are in conflict, adding 'else' to reduce checking.

Signed-off-by: Haiwei Li <lihaiwei@tencent.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
  arch/x86/kvm/lapic.c | 2 +-
  1 file changed, 1 insertion(+), 1 deletion(-)

         }
--
1.8.3.1

```
#### [PATCH v3 1/8] KVM: arm64: Document PV-lock interface
##### From: Zengruan Ye <yezengruan@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zengruan Ye <yezengruan@huawei.com>
X-Patchwork-Id: 11336681
Return-Path: <SRS0=nLL1=3F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 05C5A139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Jan 2020 12:47:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E258E22525
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Jan 2020 12:47:01 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727026AbgAPMrB (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 16 Jan 2020 07:47:01 -0500
Received: from szxga04-in.huawei.com ([45.249.212.190]:9639 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726752AbgAPMq6 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 16 Jan 2020 07:46:58 -0500
Received: from DGGEMS401-HUB.china.huawei.com (unknown [172.30.72.59])
        by Forcepoint Email with ESMTP id B12F5C83404AD649F118;
        Thu, 16 Jan 2020 20:46:54 +0800 (CST)
Received: from DESKTOP-1NISPDV.china.huawei.com (10.173.221.248) by
 DGGEMS401-HUB.china.huawei.com (10.3.19.201) with Microsoft SMTP Server id
 14.3.439.0; Thu, 16 Jan 2020 20:46:45 +0800
From: Zengruan Ye <yezengruan@huawei.com>
To: <linux-kernel@vger.kernel.org>,
        <linux-arm-kernel@lists.infradead.org>,
        <kvmarm@lists.cs.columbia.edu>, <kvm@vger.kernel.org>,
        <linux-doc@vger.kernel.org>,
        <virtualization@lists.linux-foundation.org>
CC: <yezengruan@huawei.com>, <maz@kernel.org>, <james.morse@arm.com>,
        <linux@armlinux.org.uk>, <suzuki.poulose@arm.com>,
        <julien.thierry.kdev@gmail.com>, <catalin.marinas@arm.com>,
        <mark.rutland@arm.com>, <will@kernel.org>, <steven.price@arm.com>,
        <daniel.lezcano@linaro.org>, <wanghaibin.wang@huawei.com>,
        <peterz@infradead.org>, <longman@redhat.com>
Subject: [PATCH v3 1/8] KVM: arm64: Document PV-lock interface
Date: Thu, 16 Jan 2020 20:46:19 +0800
Message-ID: <20200116124626.1155-2-yezengruan@huawei.com>
X-Mailer: git-send-email 2.23.0.windows.1
In-Reply-To: <20200116124626.1155-1-yezengruan@huawei.com>
References: <20200116124626.1155-1-yezengruan@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.173.221.248]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Introduce a paravirtualization interface for KVM/arm64 to obtain the vCPU
that is currently running or not.

The PV lock structure of the guest is allocated by user space.

A hypercall interface is provided for the guest to interrogate the
hypervisor's support for this interface and the location of the shared
memory structures.

Signed-off-by: Zengruan Ye <yezengruan@huawei.com>
---
 Documentation/virt/kvm/arm/pvlock.rst   | 68 +++++++++++++++++++++++++
 Documentation/virt/kvm/devices/vcpu.txt | 14 +++++
 2 files changed, 82 insertions(+)
 create mode 100644 Documentation/virt/kvm/arm/pvlock.rst

diff --git a/Documentation/virt/kvm/arm/pvlock.rst b/Documentation/virt/kvm/arm/pvlock.rst
new file mode 100644
index 000000000000..11776273c0a4
--- /dev/null
+++ b/Documentation/virt/kvm/arm/pvlock.rst
@@ -0,0 +1,68 @@
+.. SPDX-License-Identifier: GPL-2.0
+
+Paravirtualized lock support for arm64
+======================================
+
+KVM/arm64 provides some hypervisor service calls to support a paravirtualized
+guest obtaining whether the vCPU is currently running or not.
+
+Two new SMCCC compatible hypercalls are defined:
+* ARM_SMCCC_VENDOR_HYP_KVM_PV_LOCK_FUNC_ID:  0x86000001
+  - KVM_PV_LOCK_FEATURES   0
+  - KVM_PV_LOCK_PREEMPTED  1
+
+The existence of the PV_LOCK hypercall should be probed using the SMCCC 1.1
+ARCH_FEATURES mechanism and the hypervisor should be KVM before calling it.
+
+KVM_PV_LOCK_FEATURES
+    ============= ========    ==========
+    Function ID:  (uint32)    0x86000001
+    PV_call_id:   (uint32)    0
+    Return value: (int64)     NOT_SUPPORTED (-1) or SUCCESS (0) if the relevant
+                              PV-lock feature is supported by the hypervisor.
+    ============= ========    ==========
+
+KVM_PV_LOCK_PREEMPTED
+    ============= ========    ==========
+    Function ID:  (uint32)    0x86000001
+    PV_call_id:   (uint32)    1
+    Return value: (int64)     IPA of the PV-lock data structure for this vCPU.
+                              On failure:
+                              NOT_SUPPORTED (-1)
+    ============= ========    ==========
+
+The IPA returned by KVM_PV_LOCK_PREEMPTED should be mapped by the guest as
+normal memory with inner and outer write back caching attributes, in the inner
+shareable domain.
+
+KVM_PV_LOCK_PREEMPTED returns the structure for the calling vCPU.
+
+PV lock state
+-------------
+
+The structure pointed to by the KVM_PV_LOCK_PREEMPTED hypercall is as follows:
+
++-----------+-------------+-------------+-----------------------------------+
+| Field     | Byte Length | Byte Offset | Description                       |
++===========+=============+=============+===================================+
+| preempted |      8      |      0      | Indicates that the vCPU that owns |
+|           |             |             | this struct is running or not.    |
+|           |             |             | Non-zero values mean the vCPU has |
+|           |             |             | been preempted. Zero means the    |
+|           |             |             | vCPU is not preempted.            |
++-----------+-------------+-------------+-----------------------------------+
+
+The preempted field will be updated to 1 by the hypervisor prior to scheduling
+a vCPU. When the vCPU is scheduled out, the preempted field will be updated
+to 0 by the hypervisor.
+
+The structure will be present within a reserved region of the normal memory
+given to the guest. The guest should not attempt to write into this memory.
+There is a structure per vCPU of the guest.
+
+It is advisable that one or more 64k pages are set aside for the purpose of
+these structures and not used for other purposes, this enables the guest to map
+the region using 64k pages and avoids conflicting attributes with other memory.
+
+For the user space interface see Documentation/virt/kvm/devices/vcpu.txt
+section "4. GROUP: KVM_ARM_VCPU_PVLOCK_CTRL".
```
#### [PATCH 1/2 v3] KVM: nVMX: Check GUEST_DR7 on vmentry of nested guests
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11335811
Return-Path: <SRS0=nLL1=3F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3F0EA92A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Jan 2020 01:31:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1D9ED2081E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Jan 2020 01:31:40 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="SOhhfxqc"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729652AbgAPBbj (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 15 Jan 2020 20:31:39 -0500
Received: from userp2130.oracle.com ([156.151.31.86]:34836 "EHLO
        userp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729043AbgAPBbi (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 15 Jan 2020 20:31:38 -0500
Received: from pps.filterd (userp2130.oracle.com [127.0.0.1])
        by userp2130.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 00G1UkNb051201;
        Thu, 16 Jan 2020 01:31:34 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=corp-2019-08-05;
 bh=h6hKM2858almYGlayqdY4gPzaV9oHrE0gFn9bFNB5O8=;
 b=SOhhfxqcYP/T31b1aVJXLUIwjKWmQ5BPO2/oh9sKU84fNbsy0jjKb8uOHCEkLTHpPHo1
 4KioxiUbhcGiocn0hRwSBKvZkk3vmXzTkFBUlIjvUmu+w3NtEAPnhislYE5cZP11yXUZ
 o9N/9pq5nJkYxxuFCY0DccqHob7nDSXwU9LiU6tEe4fbTfbdXnhowp7W/r02CvTXigoO
 KWZmgS393+t9QNldg1UwApEpMKe6fPAFCLgZGrHuCh1zWKCq8RTP5V7B143lB3usg4e6
 6G0DhsrE69OfqrVIzDNSLo3nokQtO48fV7/QdSZqUDwBiPLiJA8Lp4r3bSjP9KQhFET0 fQ==
Received: from aserp3020.oracle.com (aserp3020.oracle.com [141.146.126.70])
        by userp2130.oracle.com with ESMTP id 2xf74sfnkb-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 16 Jan 2020 01:31:34 +0000
Received: from pps.filterd (aserp3020.oracle.com [127.0.0.1])
        by aserp3020.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 00G1UgmU015692;
        Thu, 16 Jan 2020 01:31:33 GMT
Received: from userv0121.oracle.com (userv0121.oracle.com [156.151.31.72])
        by aserp3020.oracle.com with ESMTP id 2xj1as85yf-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 16 Jan 2020 01:31:33 +0000
Received: from abhmp0015.oracle.com (abhmp0015.oracle.com [141.146.116.21])
        by userv0121.oracle.com (8.14.4/8.13.8) with ESMTP id 00G1VWuh019780;
        Thu, 16 Jan 2020 01:31:32 GMT
Received: from ban25x6uut29.us.oracle.com (/10.153.73.29)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Wed, 15 Jan 2020 17:31:32 -0800
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com
Subject: [PATCH 1/2 v3] KVM: nVMX: Check GUEST_DR7 on vmentry of nested guests
Date: Wed, 15 Jan 2020 19:54:32 -0500
Message-Id: <20200116005433.5242-2-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20200116005433.5242-1-krish.sadhukhan@oracle.com>
References: <20200116005433.5242-1-krish.sadhukhan@oracle.com>
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9501
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=1
 malwarescore=0
 phishscore=0 bulkscore=0 spamscore=0 mlxscore=0 mlxlogscore=999
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.0.1-1911140001 definitions=main-2001160010
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9501
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 priorityscore=1501 malwarescore=0
 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0 clxscore=1015
 lowpriorityscore=0 mlxscore=0 impostorscore=0 mlxlogscore=999 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.0.1-1911140001
 definitions=main-2001160010
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

According to section "Checks on Guest Control Registers, Debug Registers, and
and MSRs" in Intel SDM vol 3C, the following checks are performed on vmentry
of nested guests:

    If the "load debug controls" VM-entry control is 1, bits 63:32 in the DR7
    field must be 0.

In KVM, GUEST_DR7 is set prior to the vmcs02 VM-entry by kvm_set_dr() and the
latter synthesizes a #GP if any bit in the high dword in the former is set.
Hence this field needs to be checked in software.

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Reviewed-by: Karl Heubaum <karl.heubaum@oracle.com>
---
 arch/x86/kvm/vmx/nested.c | 4 ++++
 arch/x86/kvm/x86.c        | 2 +-
 arch/x86/kvm/x86.h        | 6 ++++++
 3 files changed, 11 insertions(+), 1 deletion(-)

```
#### [kvm-unit-tests] README: fix markdown formatting and general improvements
##### From: Wainer dos Santos Moschetta <wainersm@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wainer dos Santos Moschetta <wainersm@redhat.com>
X-Patchwork-Id: 11337827
Return-Path: <SRS0=nLL1=3F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C0F59139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Jan 2020 21:21:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 962332064C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Jan 2020 21:21:03 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="cGSRaHV9"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388836AbgAPVVB (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 16 Jan 2020 16:21:01 -0500
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:58134 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1731198AbgAPVVA (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 16 Jan 2020 16:21:00 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1579209659;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=CnJdiWKNpePsvTLrp2v2Ngi9pPBH1s+lxHBCjP93pVU=;
        b=cGSRaHV94MznzED05+ncUOGt4Dj7KHiXAuNu4RSCVLgDKdSGYwQkGWnTt+SamdFZ9VBRV0
        aiLMWnvRDxh3N5xu+0tcFUuXptq1BSzGjyheJ6dz1YGRi5We5tSlgq31xasOtQf4vZkB2E
        d50PTD5ENmM0vJ0lSG/iq9xYVatmzMM=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-252-clv3_kXAM9uJgUL_ipgtYQ-1; Thu, 16 Jan 2020 16:20:58 -0500
X-MC-Unique: clv3_kXAM9uJgUL_ipgtYQ-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 52F821800D48
        for <kvm@vger.kernel.org>; Thu, 16 Jan 2020 21:20:57 +0000 (UTC)
Received: from localhost.localdomain (ovpn-116-88.gru2.redhat.com
 [10.97.116.88])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 188D588867;
        Thu, 16 Jan 2020 21:20:55 +0000 (UTC)
From: Wainer dos Santos Moschetta <wainersm@redhat.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com
Subject: [kvm-unit-tests] README: fix markdown formatting and general
 improvements
Date: Thu, 16 Jan 2020 18:20:54 -0300
Message-Id: <20200116212054.4041-1-wainersm@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

There are some formatting fixes on this change:
- Some blocks weren't indented correctly;
- Some statements needed escape.

Also the text is improved in some ways:
- Variables and options are bold now;
- Files path are set to italic;
- Inline commands are marked;
- Added a section about the tests configuration file.

Signed-off-by: Wainer dos Santos Moschetta <wainersm@redhat.com>
---
 See the results here: https://github.com/wainersm/kvm-unit-tests/tree/docs

 README.md | 100 ++++++++++++++++++++++++++++++------------------------
 1 file changed, 55 insertions(+), 45 deletions(-)

```
#### [kvm-unit-tests PATCH v2] x86: Add a kvm module parameter check for vmware_backdoors test
##### From: Babu Moger <babu.moger@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Babu Moger <babu.moger@amd.com>
X-Patchwork-Id: 11337725
Return-Path: <SRS0=nLL1=3F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 118D413BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Jan 2020 19:48:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E3621207FF
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Jan 2020 19:47:59 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="icdPi1ZK"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729538AbgAPTru (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 16 Jan 2020 14:47:50 -0500
Received: from mail-eopbgr760081.outbound.protection.outlook.com
 ([40.107.76.81]:20804
        "EHLO NAM02-CY1-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1729485AbgAPTru (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 16 Jan 2020 14:47:50 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=VkaC7PD3r8IRDgD4DdTThxOEhrUvHApymGMixLNsUkMxzlbJkf4FSJ1eigbg4i+RiQsUYf21bAetyZRcDphYsTYTRuZN/x5X3vZJ7oAWIsdlwwDSYdxUCSJlZr4A6oV6e2BYmT/KxaUrlm5+TYJ8Pr3j4DbbrMFsLDd+0zU7Lmxf/nRJSDfjjh9bdBuOTU68KC1vq0kPBeLYZbhIRDcdiZNclVI/xqRJ5Kfa/rcBZerB3ymzZrK84uWxPiQ9Zxs1tCE8UQqwsSO7Uk2CuEW2PzQqL2syXzJlbu06+5+ikm7KL5mUyzXztI0Lxqvhe18Lm8zjS2EP9Rgxdlc5c/NfVQ==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=ofDM2olXIfCyrBbqaAPvqsScVB5fJMiXCWaadGsq018=;
 b=IgETSF0AXMDx+oY9CS50ypYI85QEu/AtkBNswHEHeRKoA94iKE+3G7W7HbmYbmZTiqTjYFXUgkNCWFU47hEFlOnPmK4L/qPh9xsMM3MiVsML4svudzOs4X6llO/V+u2Ir82kSslDx+svGHRuUS13/wCaaYEuVVquugMWr/lMWbXUkUyhl3papvIfOF2rPIa4yeGjw5EbfK2YoFtQDCYGq1vvf5XCszY6VIbiwRu32hLx5XwmgsnAUDXJFdKW61b50ODU4EWtaaE3VS4MX47jsiuaJqcM+GUjRHwHi5quQByPJphplRd8R5ULRdC6BYnOtOakMwiFQpcHxIhJWxQRzw==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=ofDM2olXIfCyrBbqaAPvqsScVB5fJMiXCWaadGsq018=;
 b=icdPi1ZKTwIGLBV0HeDrQ7yzFYrZSDfSeF9L5yNvMztGwRQFzS3ejr+sVPpGiUYfG9YL8FnaBwYNCFz/ZdkCpLbcE14dbeV3yYmw1GiI5tqGIW5g/UvlYOgQ/Fx/s7rXwHI8lCtYroSgkOXnAG7EuqmUYPapZc7VhAz4k5BCTDM=
Authentication-Results: spf=none (sender IP is )
 smtp.mailfrom=Babu.Moger@amd.com;
Received: from CY4PR12MB1574.namprd12.prod.outlook.com (10.172.71.23) by
 CY4PR12MB1799.namprd12.prod.outlook.com (10.175.60.9) with Microsoft SMTP
 Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.2644.19; Thu, 16 Jan 2020 19:47:47 +0000
Received: from CY4PR12MB1574.namprd12.prod.outlook.com
 ([fe80::610a:6908:1e18:49fd]) by CY4PR12MB1574.namprd12.prod.outlook.com
 ([fe80::610a:6908:1e18:49fd%7]) with mapi id 15.20.2644.015; Thu, 16 Jan 2020
 19:47:47 +0000
Subject: [kvm-unit-tests PATCH v2] x86: Add a kvm module parameter check for
 vmware_backdoors test
From: Babu Moger <babu.moger@amd.com>
To: pbonzini@redhat.com
Cc: kvm@vger.kernel.org
Date: Thu, 16 Jan 2020 13:47:46 -0600
Message-ID: 
 <157920400074.15031.16850091609715260458.stgit@naples-babu.amd.com>
User-Agent: StGit/unknown-version
X-ClientProxiedBy: SN1PR12CA0072.namprd12.prod.outlook.com
 (2603:10b6:802:20::43) To CY4PR12MB1574.namprd12.prod.outlook.com
 (2603:10b6:910:e::23)
MIME-Version: 1.0
Received: from naples-babu.amd.com (165.204.78.2) by
 SN1PR12CA0072.namprd12.prod.outlook.com (2603:10b6:802:20::43) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.2623.9 via Frontend
 Transport; Thu, 16 Jan 2020 19:47:46 +0000
X-Originating-IP: [165.204.78.2]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: a0cbe64c-9472-4cba-d3e5-08d79abcf637
X-MS-TrafficTypeDiagnostic: CY4PR12MB1799:|CY4PR12MB1799:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <CY4PR12MB17993C2D898840B29ADA00B395360@CY4PR12MB1799.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:2089;
X-Forefront-PRVS: 02843AA9E0
X-Forefront-Antispam-Report: 
 SFV:NSPM;SFS:(10009020)(4636009)(39860400002)(136003)(346002)(396003)(366004)(376002)(189003)(199004)(956004)(81166006)(6916009)(316002)(26005)(52116002)(103116003)(81156014)(7696005)(8676002)(2906002)(186003)(66556008)(86362001)(4326008)(8936002)(66476007)(478600001)(16526019)(44832011)(5660300002)(4744005)(66946007)(55016002);DIR:OUT;SFP:1101;SCL:1;SRVR:CY4PR12MB1799;H:CY4PR12MB1574.namprd12.prod.outlook.com;FPR:;SPF:None;LANG:en;PTR:InfoNoRecords;MX:1;A:1;
Received-SPF: None (protection.outlook.com: amd.com does not designate
 permitted sender hosts)
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 7S6WSiAtg82tegA/A1gQilNxG/YbDZWmWn1yr/6rPXlWUyYq6GxdwKYpSfEFDD5tivxvjU9Bu9lFgY2yZVoH0nC5fh6fYGTBuy2onLzLrGTdmZyfwCVmVA8N7HPbVVgAfuJK45/W08OREszNbCkm2D8dvu/hLKDmNA7HBnb2Q6zvKq2ZOCr3t7t1bKp1yskNSn6awCKwHjR5uBwCu58rMFrgFuadarR7rkwG9O0OUZtpY82RsADgmLjpbvKhFrBIrrtXb7jM4LwvLvFK5MYtpejTaMmgvT4LaJ9F2HB32IpcTzIDrsp0cAb0J2n+mMA1CcaulzEz3UypTFiRGtsPnUvOURYL4uZ1WCicaaKwIOJmkLWDXjH8NKaT9+u2M7yRzMBwdh57vZhhTxXezEDaoY41x0PV2sCegnf/iJ9iJRi3MghYAuCKjyOUvawrwW+1
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 a0cbe64c-9472-4cba-d3e5-08d79abcf637
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 16 Jan 2020 19:47:47.3596
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 /Fw7y35/sbnIqmkaVF6Kc3Iyz6BYIemqZwrRJc1/VBgD1VsAbu9p+eNR2+GcoWya
X-MS-Exchange-Transport-CrossTenantHeadersStamped: CY4PR12MB1799
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

vmware_backdoors test fails if the kvm module parameter
enable_vmware_backdoor is not set to Y. Add a check before
running the test.

Suggested-by: Wei Huang <Wei.Huang2@amd.com>
Signed-off-by: Babu Moger <babu.moger@amd.com>
Reviewed-by: Liran Alon <liran.alon@oracle.com>
---
v2: Fixed Wei's name.
    Added reviwed by Liran Alon.

 x86/unittests.cfg |    1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH] kvm: x86: Don't dirty guest memory on every vcpu_put()From: Jim Mattson <jmattson@google.com>
##### From: Jim Mattson <jmattson@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jim Mattson <jmattson@google.com>
X-Patchwork-Id: 11335759
Return-Path: <SRS0=nLL1=3F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 54F0213A0
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Jan 2020 00:16:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 2F4472081E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Jan 2020 00:16:56 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="tOuQX0ex"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730090AbgAPAQz (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 15 Jan 2020 19:16:55 -0500
Received: from mail-pl1-f201.google.com ([209.85.214.201]:46722 "EHLO
        mail-pl1-f201.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726310AbgAPAQz (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 15 Jan 2020 19:16:55 -0500
Received: by mail-pl1-f201.google.com with SMTP id t17so7771731plr.13
        for <kvm@vger.kernel.org>; Wed, 15 Jan 2020 16:16:54 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=t5hhiMVaGy2q0E/z2T4ycE665LCZYtF+TTm8Tr1smIg=;
        b=tOuQX0exFrlUtIawNreCUMl5ovbrJjoQ387lqvKrIjWgH/iE3VZ0K1ng2Ksq2hNC0I
         ltp2RJULwVsQphki50fmjuWZYJ2gkb8tSuzWo+JwVXO3QVj5m+9oRgVbOtj6mZNgrIO0
         jK1jP88lWKP9T+kBzi3Bg2f11tvTTrFor6fNSwnvGc9hIxdP/0J0hEElDvUtVZT94gf+
         QCC0CykWQ7KjG5VzJDAD/YAD4KjRalEs1jkLh4w3EMgt92QtYM3urk7tp+Qbu2Yau8Gl
         uPshjpFpIc5Fsv4kmFFLnVHWr/qmKu5M6EYnNK9hNGu3lXQ0LZuGWfJ7oEfIp6wCrr/2
         eOcA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=t5hhiMVaGy2q0E/z2T4ycE665LCZYtF+TTm8Tr1smIg=;
        b=snh5QPevCxDM8Wql63REZJ7yZzQhp+6ig1TD9bfvXw/6NE8zRNTKW3DACjtuomoYsa
         F5qHKxH57rwxX04LEkPg3Mk2+M+fzVQY49PToxig/aBCcsKvTsVq/81CiGGMC9vKt5IU
         P3NzeOs4FVmFleyo4PpG6ezz4uucuFESbn3YDuqzzyii2kf5ESIggx+oHAuW/ToonFPO
         e9GGE07xPkXktbwLF7bz2nIwUi9+AV5wIclXqaBPfkIdBUfWAw/KK33mFZrL7X4ftPKm
         FilB6rOP60HK776spS5i9ZdFN8YmoUsf9H6bG1/mw7uFV7pGsowCS3C+qeRkuHajl2kZ
         +r0g==
X-Gm-Message-State: APjAAAUDRv5RL4WbjUYH4kTYGd85fmE6Xxk8y/4LHsHr2ehStcFzGU8C
        t4USiXDVN3grLPUh4Ea2zYILvq1KXZ5he3E0EjBbXt/CLE1+Q4fKnjZaz3G+B+m6cGdluTB81dt
        P8ox2UbMzwr+neoe81AZq0YyepWH1e+Z+ptaW699LzrU9XvKNkbSCsb8kdG0iqsQ=
X-Google-Smtp-Source: 
 APXvYqzYOrXmkuotXUi1BcXQtiDrkmbf0DY4rTwfJCnnNJ/jNSYeIZwrPXL3Jgyqs+kgCMk87xe9KNpGynZknQ==
X-Received: by 2002:a65:5608:: with SMTP id l8mr36747108pgs.210.1579133814000;
 Wed, 15 Jan 2020 16:16:54 -0800 (PST)
Date: Wed, 15 Jan 2020 16:16:35 -0800
Message-Id: <20200116001635.174948-1-jmattson@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.25.0.rc1.283.g88dfdc4193-goog
Subject: [PATCH] kvm: x86: Don't dirty guest memory on every vcpu_put()
From: Jim Mattson <jmattson@google.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Jim Mattson <jmattson@google.com>,
        Kevin Mcgaire <kevinmcgaire@google.com>,
        Ben Gardon <bgardon@google.com>,
        Oliver Upton <oupton@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Beginning with commit 0b9f6c4615c99 ("x86/kvm: Support the vCPU
preemption check"), the KVM_VCPU_PREEMPTED flag is set in the guest
copy of the kvm_steal_time struct on every call to vcpu_put(). As a
result, guest memory is dirtied on every call to vcpu_put(), even when
the VM is quiescent.

To avoid dirtying guest memory unnecessarily, don't bother setting the
flag in the guest copy of the struct if it is already set in the
kernel copy of the struct.

If a different vCPU thread clears the guest copy of the flag, it will
no longer get reset on the next call to vcpu_put, but it's not clear
that resetting the flag in this case was intentional to begin with.

Signed-off-by: Jim Mattson <jmattson@google.com>
Tested-by: Kevin Mcgaire <kevinmcgaire@google.com>
Reviewed-by: Ben Gardon <bgardon@google.com>
Reviewed-by: Oliver Upton <oupton@google.com>
Reviewed-by: Liran Alon <liran.alon@oracle.com>
---
 arch/x86/kvm/x86.c | 3 +++
 1 file changed, 3 insertions(+)

```
#### linux-next: manual merge of the kvm tree with the tip tree
##### From: Stephen Rothwell <sfr@canb.auug.org.au>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stephen Rothwell <sfr@canb.auug.org.au>
X-Patchwork-Id: 11335907
Return-Path: <SRS0=nLL1=3F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AEB9D139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Jan 2020 02:49:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7C6132084D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Jan 2020 02:49:10 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=canb.auug.org.au header.i=@canb.auug.org.au
 header.b="leyAg/8D"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729076AbgAPCtG (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 15 Jan 2020 21:49:06 -0500
Received: from bilbo.ozlabs.org ([203.11.71.1]:38455 "EHLO ozlabs.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726552AbgAPCtG (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 15 Jan 2020 21:49:06 -0500
Received: from authenticated.ozlabs.org (localhost [127.0.0.1])
        (using TLSv1.3 with cipher TLS_AES_256_GCM_SHA384 (256/256 bits)
         key-exchange ECDHE (P-256) server-signature RSA-PSS (4096 bits)
 server-digest SHA256)
        (No client certificate requested)
        by mail.ozlabs.org (Postfix) with ESMTPSA id 47ypYS49Njz9sR0;
        Thu, 16 Jan 2020 13:49:00 +1100 (AEDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=canb.auug.org.au;
        s=201702; t=1579142943;
        bh=pOkguxtakW7odgcyaEbAn/6knPxLxlPQVmo68XZDtCo=;
        h=Date:From:To:Cc:Subject:From;
        b=leyAg/8DW7ay+aNLPmZjNSzU286S50440mIwwQJEyVWhqed7pedb+12yFfHF5ho2o
         +AbAov3T/Vqc0bMnVyUFDc4ohXQBOQUXFnWHWkMqT4akhDwj3WLIY6WaegZ1Cbc/uP
         KUaE1bwtaEbZLzj3ziARkZHOethZ6qM6mQdK5XpxbpRNJiuIOtuOxP7M3nnhy6Fqrj
         n60/9zxPDQwY1XtlJyzvgTuMDTVyKkt6OwGckDRfnQJKsJXOjscSoRazT4oipfAL8d
         1VJx07TQc7lNKmfP2geeWdylS+nQpL8h9RC6fusnwPMqxdRL0H/s+UiFNDVRV/xU8T
         TKaHBPkHlooZQ==
Date: Thu, 16 Jan 2020 13:48:59 +1100
From: Stephen Rothwell <sfr@canb.auug.org.au>
To: Paolo Bonzini <pbonzini@redhat.com>,
 Radim =?utf-8?b?S3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 KVM <kvm@vger.kernel.org>, Thomas Gleixner <tglx@linutronix.de>,
 Ingo Molnar <mingo@elte.hu>, "H. Peter Anvin" <hpa@zytor.com>,
 Peter Zijlstra <peterz@infradead.org>
Cc: Linux Next Mailing List <linux-next@vger.kernel.org>,
        Linux Kernel Mailing List <linux-kernel@vger.kernel.org>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Xiaoyao Li <xiaoyao.li@intel.com>
Subject: linux-next: manual merge of the kvm tree with the tip tree
Message-ID: <20200116134859.36d203de@canb.auug.org.au>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all,

Today's linux-next merge of the kvm tree got a conflict in:

  arch/x86/include/asm/vmx.h

between commit:

  b39033f504a7 ("KVM: VMX: Use VMX_FEATURE_* flags to define VMCS control bits")

from the tip tree and commits:

  9dadc2f918df ("KVM: VMX: Rename INTERRUPT_PENDING to INTERRUPT_WINDOW")
  4e2a0bc56ad1 ("KVM: VMX: Rename NMI_PENDING to NMI_WINDOW")
  5e3d394fdd9e ("KVM: VMX: Fix the spelling of CPU_BASED_USE_TSC_OFFSETTING")

from the kvm tree.

I fixed it up (see below) and can carry the fix as necessary. This
is now fixed as far as linux-next is concerned, but any non trivial
conflicts should be mentioned to your upstream maintainer when your tree
is submitted for merging.  You may also want to consider cooperating
with the maintainer of the conflicting tree to minimise any particularly
complex conflicts.

```
#### [kvm-unit-tests PATCH v2 1/7] s390x: smp: Cleanup smp.c
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11336629
Return-Path: <SRS0=nLL1=3F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F1BB71398
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Jan 2020 12:05:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id CFD952073A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Jan 2020 12:05:32 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726897AbgAPMFc (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 16 Jan 2020 07:05:32 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:64170 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726366AbgAPMFb (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 16 Jan 2020 07:05:31 -0500
Received: from pps.filterd (m0098396.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 00GBvVtP062592
        for <kvm@vger.kernel.org>; Thu, 16 Jan 2020 07:05:31 -0500
Received: from e06smtp02.uk.ibm.com (e06smtp02.uk.ibm.com [195.75.94.98])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2xh8d64awr-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Thu, 16 Jan 2020 07:05:30 -0500
Received: from localhost
        by e06smtp02.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Thu, 16 Jan 2020 12:05:28 -0000
Received: from b06cxnps4074.portsmouth.uk.ibm.com (9.149.109.196)
        by e06smtp02.uk.ibm.com (192.168.101.132) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Thu, 16 Jan 2020 12:05:25 -0000
Received: from d06av21.portsmouth.uk.ibm.com (d06av21.portsmouth.uk.ibm.com
 [9.149.105.232])
        by b06cxnps4074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 00GC5O8r21168138
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 16 Jan 2020 12:05:24 GMT
Received: from d06av21.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id C2C955205A;
        Thu, 16 Jan 2020 12:05:24 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.152.224.123])
        by d06av21.portsmouth.uk.ibm.com (Postfix) with ESMTP id E49CA52052;
        Thu, 16 Jan 2020 12:05:23 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: thuth@redhat.com, borntraeger@de.ibm.com,
        linux-s390@vger.kernel.org, david@redhat.com, cohuck@redhat.com
Subject: [kvm-unit-tests PATCH v2 1/7] s390x: smp: Cleanup smp.c
Date: Thu, 16 Jan 2020 07:05:07 -0500
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20200116120513.2244-1-frankja@linux.ibm.com>
References: <20200116120513.2244-1-frankja@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 20011612-0008-0000-0000-00000349E287
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 20011612-0009-0000-0000-00004A6A3C1A
Message-Id: <20200116120513.2244-2-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-01-16_03:2020-01-16,2020-01-15 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 lowpriorityscore=0
 malwarescore=0 mlxscore=0 mlxlogscore=979 spamscore=0 bulkscore=0
 phishscore=0 suspectscore=3 adultscore=0 impostorscore=0 clxscore=1015
 priorityscore=1501 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-1910280000 definitions=main-2001160103
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Let's remove a lot of badly formatted code by introducing the
wait_for_flag() function.

Also let's remove some stray spaces.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---
 s390x/smp.c | 42 ++++++++++++++++++++++++------------------
 1 file changed, 24 insertions(+), 18 deletions(-)

```
#### [PATCH v2] KVM: Adding 'else' to reduce checking.
##### From: Haiwei Li <lihaiwei.kernel@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Haiwei Li <lihaiwei.kernel@gmail.com>
X-Patchwork-Id: 11336383
Return-Path: <SRS0=nLL1=3F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6A05D921
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Jan 2020 09:04:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 483EE207E0
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Jan 2020 09:04:12 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="umn+IqrA"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730523AbgAPJEH (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 16 Jan 2020 04:04:07 -0500
Received: from mail-pj1-f67.google.com ([209.85.216.67]:35320 "EHLO
        mail-pj1-f67.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725973AbgAPJEH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 16 Jan 2020 04:04:07 -0500
Received: by mail-pj1-f67.google.com with SMTP id s7so1281783pjc.0;
        Thu, 16 Jan 2020 01:04:07 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=to:cc:from:subject:message-id:date:user-agent:mime-version
         :content-language:content-transfer-encoding;
        bh=U+3BCSnWn4TsegpodIg+CCuuc8hYDYmEd54pNj+hQe8=;
        b=umn+IqrAkUg8Lczfv/av+jmNOPAaBCCOriIQM0WcqEyLpzjtkocNVLbEa7HftEDRCp
         ZXrgkUD/Q8sbt85K9wh9BNGjWywMrU348smx5dZlr7zow7tbxh81IZg9j6v3yfsbWOab
         r6o+KuBm8NxqDy3DaRLejhSGZ5oR9PGwbL3n5sY5WG0g7DnpcE6hxt1YdENgv5vsQopZ
         kC5zM/ktRUwjGnmlKrT4/zl87zRwnno7CzLsYApMSABEJYU9o1glLtqbYhAKssFDYJk8
         OrD7gC9jgvYm6xZLBRn96UidFDSwYaCjiUnXuUeHE4261LVOm1JiyWYfnUbuIpnve7fr
         AOQw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:to:cc:from:subject:message-id:date:user-agent
         :mime-version:content-language:content-transfer-encoding;
        bh=U+3BCSnWn4TsegpodIg+CCuuc8hYDYmEd54pNj+hQe8=;
        b=ge7tcrX56Da29lm7zsrVSlvS6o6jutM3CBVSfu0U1uUUokGGvS64ihWdS/oXvRqDpP
         v9OorUlPNLbDj8vT+NOyHY0k9io4jRC5+t/Ug37uv83Y6oWu9AajHKXjuTHjvHQogixE
         TWeMi+wUkB+nHWK76hn+bAFjP0XS8zwXKg+eQu7aSt8zIfdjh9S32HB62a0XHox00Zeb
         WbamovQw4blHKkWZeWRvfW25Gy2QhCj2hbd6FdP+JeK/O2lgdGXu1+z/Qoqp5OtPFC8m
         /pMq5Mvj2XwAxhyY7UvNw8fVuosskWQba8aD2ScbsdtWMhLb6vieJf6GlDUPXlhzNKsJ
         VPTA==
X-Gm-Message-State: APjAAAWq+szGLfqqrmxWu+Qlxk03glccqwqA4r/T2SSeP4hmX/taB0Kw
        bUdNGd8t/WEsV44XmcW0/Q==
X-Google-Smtp-Source: 
 APXvYqzw0XcAtZanZ7artcVDGxxVLV/xsH+qbe+U725HIgRi07bmtp2XMXD8Wos42K2GvIsNfJAESA==
X-Received: by 2002:a17:90b:2286:: with SMTP id
 kx6mr5562347pjb.95.1579165446729;
        Thu, 16 Jan 2020 01:04:06 -0800 (PST)
Received: from [127.0.0.1] ([103.7.29.6])
        by smtp.gmail.com with ESMTPSA id 3sm2646801pjg.27.2020.01.16.01.04.03
        (version=TLS1_3 cipher=TLS_AES_128_GCM_SHA256 bits=128/128);
        Thu, 16 Jan 2020 01:04:06 -0800 (PST)
To: "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>,
        "kvm@vger.kernel.org" <kvm@vger.kernel.org>,
        "x86@kernel.org" <x86@kernel.org>
Cc: "pbonzini@redhat.com" <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        "vkuznets@redhat.com" <vkuznets@redhat.com>,
        "wanpengli@tencent.com" <wanpengli@tencent.com>,
        "jmattson@google.com" <jmattson@google.com>,
        "joro@8bytes.org" <joro@8bytes.org>,
        "tglx@linutronix.de" <tglx@linutronix.de>,
        "mingo@redhat.com" <mingo@redhat.com>,
        "bp@alien8.de" <bp@alien8.de>, "hpa@zytor.com" <hpa@zytor.com>
From: Haiwei Li <lihaiwei.kernel@gmail.com>
Subject: [PATCH v2] KVM: Adding 'else' to reduce checking.
Message-ID: <abea81a5-266f-7e0d-558a-b4b7aa49d3d4@gmail.com>
Date: Thu, 16 Jan 2020 17:03:56 +0800
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:68.0)
 Gecko/20100101 Thunderbird/68.3.1
MIME-Version: 1.0
Content-Language: en-US
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From 009bfba9b6f6b41018708323d9ca651ae2075900 Mon Sep 17 00:00:00 2001
From: Haiwei Li <lihaiwei@tencent.com>
Date: Thu, 16 Jan 2020 16:50:21 +0800
Subject: [PATCH] Adding 'else' to reduce checking.

These two conditions are in conflict, adding 'else' to reduce checking.

Signed-off-by: Haiwei Li <lihaiwei@tencent.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Reviewed-by: Miaohe Lin <linmiaohe@huawei.com>
---
  arch/x86/kvm/lapic.c | 4 ++--
  1 file changed, 2 insertions(+), 2 deletions(-)

         }
--
1.8.3.1

```
#### [PATCH 1/5] vhost: factor out IOTLB
##### From: Jason Wang <jasowang@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 11336671
Return-Path: <SRS0=nLL1=3F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5C3A3139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Jan 2020 12:43:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1D5BA206E6
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Jan 2020 12:43:09 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="UMqjCZQe"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726887AbgAPMnI (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 16 Jan 2020 07:43:08 -0500
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:29370 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726689AbgAPMnH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 16 Jan 2020 07:43:07 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1579178585;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=1GLqIKZp6y/3ql8wE4T8tedUPoVAaUd7Pb+nPMeJRXU=;
        b=UMqjCZQeLJI+eiSDYhwDuOX9r7/tWBom/I0t/+Jp6AFBRGBlEJPxa+LRKcGf41o/+D2/jG
        nbKWIItB5HM0d74seMK2fdO1G4VAhYJw33wynFPRGKgIGM991dRVA4K28sEjO0mUbL235H
        VltKx4Xx/VJO9R6oD2dP99iKgA5wEVc=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-185-HhRhfeFvOQaixLx3wX0_dA-1; Thu, 16 Jan 2020 07:43:04 -0500
X-MC-Unique: HhRhfeFvOQaixLx3wX0_dA-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 233CA1B18BC0;
        Thu, 16 Jan 2020 12:43:01 +0000 (UTC)
Received: from jason-ThinkPad-X1-Carbon-6th.redhat.com
 (ovpn-12-70.pek2.redhat.com [10.72.12.70])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 3EF305C296;
        Thu, 16 Jan 2020 12:42:49 +0000 (UTC)
From: Jason Wang <jasowang@redhat.com>
To: mst@redhat.com, jasowang@redhat.com, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org
Cc: tiwei.bie@intel.com, jgg@mellanox.com, maxime.coquelin@redhat.com,
        cunming.liang@intel.com, zhihong.wang@intel.com,
        rob.miller@broadcom.com, xiao.w.wang@intel.com,
        haotian.wang@sifive.com, lingshan.zhu@intel.com,
        eperezma@redhat.com, lulu@redhat.com, parav@mellanox.com,
        kevin.tian@intel.com, stefanha@redhat.com, rdunlap@infradead.org,
        hch@infradead.org, aadam@redhat.com, jakub.kicinski@netronome.com,
        jiri@mellanox.com, shahafs@mellanox.com, hanand@xilinx.com,
        mhabets@solarflare.com
Subject: [PATCH 1/5] vhost: factor out IOTLB
Date: Thu, 16 Jan 2020 20:42:27 +0800
Message-Id: <20200116124231.20253-2-jasowang@redhat.com>
In-Reply-To: <20200116124231.20253-1-jasowang@redhat.com>
References: <20200116124231.20253-1-jasowang@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch factors out IOTLB into a dedicated module in order to be
reused by other modules like vringh. User may choose to enable the
automatic retiring by specifying VHOST_IOTLB_FLAG_RETIRE flag to fit
for the case of vhost device IOTLB implementation.

Signed-off-by: Jason Wang <jasowang@redhat.com>
---
 MAINTAINERS                 |   1 +
 drivers/vhost/Kconfig       |   7 ++
 drivers/vhost/Makefile      |   2 +
 drivers/vhost/net.c         |   2 +-
 drivers/vhost/vhost.c       | 221 +++++++++++-------------------------
 drivers/vhost/vhost.h       |  36 ++----
 drivers/vhost/vhost_iotlb.c | 171 ++++++++++++++++++++++++++++
 include/linux/vhost_iotlb.h |  45 ++++++++
 8 files changed, 304 insertions(+), 181 deletions(-)
 create mode 100644 drivers/vhost/vhost_iotlb.c
 create mode 100644 include/linux/vhost_iotlb.h

```
#### [RFC PATCH 1/3] vfio/type1: Convert vfio_iommu.lock from mutex to rwsem
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alex Williamson <alex.williamson@redhat.com>
X-Patchwork-Id: 11337539
Return-Path: <SRS0=nLL1=3F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EAFBF14B7
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Jan 2020 18:18:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id C7D9B20684
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Jan 2020 18:18:10 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="b2hJqLWe"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2392755AbgAPSSJ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 16 Jan 2020 13:18:09 -0500
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:24803 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S2391646AbgAPSSG (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 16 Jan 2020 13:18:06 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1579198685;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=niuGWb81Q8zr23FXcglCGpZUWD+TFqFFh4zn2anjs0s=;
        b=b2hJqLWeO4Od0oZHkg9fqdKheEF5YGfL2XwSqf0pqawmWqHpy961NLtKVY8V7g5aYLNmz7
        rylkERsO83yAut8OeFjLuY9jYKjU3ULjvQvz1DtivYoe8vDu9lT3eKnQZ+4pQzadyE/0rm
        /SDTfl7UyCSfs9VyCGN0jQd3YSf3U/0=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-327-2pz5OV7JOFemg2VndDEo1Q-1; Thu, 16 Jan 2020 13:18:01 -0500
X-MC-Unique: 2pz5OV7JOFemg2VndDEo1Q-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id A06B7800D5C;
        Thu, 16 Jan 2020 18:18:00 +0000 (UTC)
Received: from gimli.home (ovpn-116-28.phx2.redhat.com [10.3.116.28])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 496AF80617;
        Thu, 16 Jan 2020 18:17:57 +0000 (UTC)
Subject: [RFC PATCH 1/3] vfio/type1: Convert vfio_iommu.lock from mutex to
 rwsem
From: Alex Williamson <alex.williamson@redhat.com>
To: yan.y.zhao@intel.com
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Date: Thu, 16 Jan 2020 11:17:57 -0700
Message-ID: <157919867745.21002.3239982207630090516.stgit@gimli.home>
In-Reply-To: <157919849533.21002.4782774695733669879.stgit@gimli.home>
References: <157919849533.21002.4782774695733669879.stgit@gimli.home>
User-Agent: StGit/0.19-dirty
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

As a first step reducing lock contention, maintain the same locking
granularity using a rwsem rather than a mutex.

Signed-off-by: Alex Williamson <alex.williamson@redhat.com>
---
 drivers/vfio/vfio_iommu_type1.c |   51 ++++++++++++++++++++-------------------
 1 file changed, 26 insertions(+), 25 deletions(-)

```
#### [PATCH net-next 1/3] vsock: add network namespace support
##### From: Stefano Garzarella <sgarzare@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stefano Garzarella <sgarzare@redhat.com>
X-Patchwork-Id: 11337563
Return-Path: <SRS0=nLL1=3F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 677EE1398
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Jan 2020 18:33:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 31E7F2073A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Jan 2020 18:33:47 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="MPa5EpIF"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2436770AbgAPSdp (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 16 Jan 2020 13:33:45 -0500
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:47514 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S2387537AbgAPRYt (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 16 Jan 2020 12:24:49 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1579195488;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=+VGSKYYAvkNoF8+cprFtOeKETpEfAOiLdOWkQthdSJs=;
        b=MPa5EpIFiKBNMhzGSOiCBcHx2AWuH0CcnIXp0q9/uccj3wffJacmneGYv/hQ8B0cA2mPA5
        pGAwUgZpR64Nnt82YvTUjDPcJJqWwa6gzxAr+rr3LO/CZVDm+jfc4pY2o426CYdnFVdl8S
        n9pp3GVzTZdWN8rRP+fZRj5hM0QVuC4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-97-UUN55USqMMi3d6FObijG9Q-1; Thu, 16 Jan 2020 12:24:47 -0500
X-MC-Unique: UUN55USqMMi3d6FObijG9Q-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 0951A8010C7;
        Thu, 16 Jan 2020 17:24:45 +0000 (UTC)
Received: from steredhat.redhat.com (ovpn-117-242.ams2.redhat.com
 [10.36.117.242])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 88F2F5C1D8;
        Thu, 16 Jan 2020 17:24:42 +0000 (UTC)
From: Stefano Garzarella <sgarzare@redhat.com>
To: davem@davemloft.net, netdev@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, Jorgen Hansen <jhansen@vmware.com>,
        Jason Wang <jasowang@redhat.com>, kvm@vger.kernel.org,
        Stefan Hajnoczi <stefanha@redhat.com>,
        Stefano Garzarella <sgarzare@redhat.com>,
        virtualization@lists.linux-foundation.org,
        linux-hyperv@vger.kernel.org,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Dexuan Cui <decui@microsoft.com>
Subject: [PATCH net-next 1/3] vsock: add network namespace support
Date: Thu, 16 Jan 2020 18:24:26 +0100
Message-Id: <20200116172428.311437-2-sgarzare@redhat.com>
In-Reply-To: <20200116172428.311437-1-sgarzare@redhat.com>
References: <20200116172428.311437-1-sgarzare@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch adds a check of the "net" assigned to a socket during
the vsock_find_bound_socket() and vsock_find_connected_socket()
to support network namespace, allowing to share the same address
(cid, port) across different network namespaces.

This patch adds 'netns' module param to enable this new feature
(disabled by default), because it changes vsock's behavior with
network namespaces and could break existing applications.

G2H transports will use the default network namepsace (init_net).
H2G transports can use different network namespace for different
VMs.

This patch uses default network namepsace (init_net) in all
transports.

Signed-off-by: Stefano Garzarella <sgarzare@redhat.com>
---
RFC -> v1
 * added 'netns' module param
 * added 'vsock_net_eq()' to check the "net" assigned to a socket
   only when 'netns' support is enabled
---
 include/net/af_vsock.h                  |  7 +++--
 net/vmw_vsock/af_vsock.c                | 41 +++++++++++++++++++------
 net/vmw_vsock/hyperv_transport.c        |  5 +--
 net/vmw_vsock/virtio_transport_common.c |  5 +--
 net/vmw_vsock/vmci_transport.c          |  5 +--
 5 files changed, 46 insertions(+), 17 deletions(-)

```
