#### [PATCH] accel/kvm: ensure ret always set
##### From: =?utf-8?q?Alex_Benn=C3=A9e?= <alex.bennee@linaro.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Alex_Benn=C3=A9e?= <alex.bennee@linaro.org>
X-Patchwork-Id: 11170737
Return-Path: <SRS0=50xr=X3=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0C67E13B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  2 Oct 2019 10:22:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id DDEBA21924
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  2 Oct 2019 10:22:31 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=linaro.org header.i=@linaro.org
 header.b="K5gVLW+/"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727724AbfJBKWa (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 2 Oct 2019 06:22:30 -0400
Received: from mail-wr1-f68.google.com ([209.85.221.68]:44870 "EHLO
        mail-wr1-f68.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726411AbfJBKWa (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 2 Oct 2019 06:22:30 -0400
Received: by mail-wr1-f68.google.com with SMTP id z9so5855398wrl.11
        for <kvm@vger.kernel.org>; Wed, 02 Oct 2019 03:22:29 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=linaro.org; s=google;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=IYA27I4k+X20iMhTgUDiQt+Kq5nsLRsXVXPBklSSwWM=;
        b=K5gVLW+/19CuDqiUfAEqgTBp/wCUKyTN5LGJLQuQEV0ROhN/YiKVvzv+uC39cqKd1V
         hXrbf+0jiyIRoEzMGw5Jf77iBQLv883VS/43ka06txWzjYI4lDoVqB1v53Qog3TwJvdW
         PdKs61iUxcxfEFzgkeqGhDOf77tlV6FRIMm+DrwTUonYA5nAAh2QRjUA29vquUWnk1K+
         W+d5nrP398aE8LKZMDDubIm30ooGPm3kVdAx+1V8G3XxDEWSglkQFpTuI4ihZJHgbbun
         tewpIxjnqOozbwtNIQT+5xRbjcjAsm3bJ/YDaElpPjGpMG+z7wbBmJtmrgveBlf8Auz7
         QLOA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=IYA27I4k+X20iMhTgUDiQt+Kq5nsLRsXVXPBklSSwWM=;
        b=dXpqJePT5GKrQyHU9rsYWmDPx4U2LdBFjFB8UFzgueqkcPNLP4YYWkY7TwbzL/ASxw
         odzZMGlIcXXFzrY22zAEOXfu0boL/ppRDcPI5h1P/RC1OHL1b3QqvBzrOPjnoVTsZfVd
         HqK0WmoIJ8xvPcu0L7JISCeluMKS9kMZ3ymotlltq+p7jKORbj1mm6QacCckUg+Byl3I
         2te4c3Ujm5cZqXYnr2hiyHiBNPcGp9XM2yR7tQQVu/+OXY1VQ1SWyiLNCCYpwh+ruQwd
         RbjJTRZjo8F4MOnrmY9d4V4QHspIgdKyUk6iLnbvme/ELBU67GmUU8yLvqnSoojCnt9s
         0EEw==
X-Gm-Message-State: APjAAAVVUTgHwwNUEKt7wBSExX3fJQ1f4imHYopuBLslWZOOmuP2u4XP
        8ajFqV82+HhsDZbokCYUTVbq7Q==
X-Google-Smtp-Source: 
 APXvYqxgRqSiSoPjrsprBlIeWNOCrME4vyWqfcmoAgUJonf+cuG6+6hd0A+XGFvc82HBKSLBvZpRYw==
X-Received: by 2002:a5d:63ca:: with SMTP id c10mr2195782wrw.314.1570011748341;
        Wed, 02 Oct 2019 03:22:28 -0700 (PDT)
Received: from zen.linaroharston ([51.148.130.216])
        by smtp.gmail.com with ESMTPSA id
 a13sm48250121wrf.73.2019.10.02.03.22.27
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 02 Oct 2019 03:22:27 -0700 (PDT)
Received: from zen.lan (localhost [127.0.0.1])
        by zen.linaroharston (Postfix) with ESMTP id DC71E1FF87;
        Wed,  2 Oct 2019 11:22:26 +0100 (BST)
From: =?utf-8?q?Alex_Benn=C3=A9e?= <alex.bennee@linaro.org>
To: qemu-devel@nongnu.org
Cc: =?utf-8?q?Alex_Benn=C3=A9e?= <alex.bennee@linaro.org>,
 Paolo Bonzini <pbonzini@redhat.com>,
 kvm@vger.kernel.org (open list:Overall KVM CPUs)
Subject: [PATCH] accel/kvm: ensure ret always set
Date: Wed,  2 Oct 2019 11:22:12 +0100
Message-Id: <20191002102212.6100-1-alex.bennee@linaro.org>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Some of the cross compilers rightly complain there are cases where ret
may not be set. 0 seems to be the reasonable default unless particular
slot explicitly returns -1.

Signed-off-by: Alex Bennée <alex.bennee@linaro.org>
---
 accel/kvm/kvm-all.c | 6 +++---
 1 file changed, 3 insertions(+), 3 deletions(-)

```
#### [PATCH v5 01/10] KVM: arm64: Document PV-time interface
##### From: Steven Price <steven.price@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Steven Price <Steven.Price@arm.com>
X-Patchwork-Id: 11171247
Return-Path: <SRS0=50xr=X3=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 95F5D17EE
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  2 Oct 2019 14:50:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7E8B721D7B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  2 Oct 2019 14:50:56 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728523AbfJBOuz (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 2 Oct 2019 10:50:55 -0400
Received: from foss.arm.com ([217.140.110.172]:46200 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726411AbfJBOuz (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 2 Oct 2019 10:50:55 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 3DC1F1597;
        Wed,  2 Oct 2019 07:50:54 -0700 (PDT)
Received: from e112269-lin.arm.com (e112269-lin.cambridge.arm.com
 [10.1.196.133])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 37F153F706;
        Wed,  2 Oct 2019 07:50:52 -0700 (PDT)
From: Steven Price <steven.price@arm.com>
To: Marc Zyngier <maz@kernel.org>, Will Deacon <will@kernel.org>,
        linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu
Cc: Steven Price <steven.price@arm.com>,
 Catalin Marinas <catalin.marinas@arm.com>,
 Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Russell King <linux@armlinux.org.uk>, James Morse <james.morse@arm.com>,
 Julien Thierry <julien.thierry.kdev@gmail.com>,
 Suzuki K Pouloze <suzuki.poulose@arm.com>,
 Mark Rutland <mark.rutland@arm.com>, kvm@vger.kernel.org,
 linux-doc@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH v5 01/10] KVM: arm64: Document PV-time interface
Date: Wed,  2 Oct 2019 15:50:28 +0100
Message-Id: <20191002145037.51630-2-steven.price@arm.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20191002145037.51630-1-steven.price@arm.com>
References: <20191002145037.51630-1-steven.price@arm.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Introduce a paravirtualization interface for KVM/arm64 based on the
"Arm Paravirtualized Time for Arm-Base Systems" specification DEN 0057A.

This only adds the details about "Stolen Time" as the details of "Live
Physical Time" have not been fully agreed.

User space can specify a reserved area of memory for the guest and
inform KVM to populate the memory with information on time that the host
kernel has stolen from the guest.

A hypercall interface is provided for the guest to interrogate the
hypervisor's support for this interface and the location of the shared
memory structures.

Signed-off-by: Steven Price <steven.price@arm.com>
---
 Documentation/virt/kvm/arm/pvtime.txt   | 65 +++++++++++++++++++++++++
 Documentation/virt/kvm/devices/vcpu.txt | 14 ++++++
 2 files changed, 79 insertions(+)
 create mode 100644 Documentation/virt/kvm/arm/pvtime.txt

diff --git a/Documentation/virt/kvm/arm/pvtime.txt b/Documentation/virt/kvm/arm/pvtime.txt
new file mode 100644
index 000000000000..fa15c12eec91
--- /dev/null
+++ b/Documentation/virt/kvm/arm/pvtime.txt
@@ -0,0 +1,65 @@
+Paravirtualized time support for arm64
+======================================
+
+Arm specification DEN0057/A defined a standard for paravirtualised time
+support for AArch64 guests:
+
+https://developer.arm.com/docs/den0057/a
+
+KVM/arm64 implements the stolen time part of this specification by providing
+some hypervisor service calls to support a paravirtualized guest obtaining a
+view of the amount of time stolen from its execution.
+
+Two new SMCCC compatible hypercalls are defined:
+
+PV_FEATURES 0xC5000020
+PV_TIME_ST  0xC5000022
+
+These are only available in the SMC64/HVC64 calling convention as
+paravirtualized time is not available to 32 bit Arm guests. The existence of
+the PV_FEATURES hypercall should be probed using the SMCCC 1.1 ARCH_FEATURES
+mechanism before calling it.
+
+PV_FEATURES
+    Function ID:  (uint32)  : 0xC5000020
+    PV_func_id:   (uint32)  : The function to query for support.
+                              Currently only PV_TIME_ST is supported.
+    Return value: (int32)   : NOT_SUPPORTED (-1) or SUCCESS (0) if the relevant
+                              PV-time feature is supported by the hypervisor.
+
+PV_TIME_ST
+    Function ID:  (uint32)  : 0xC5000022
+    Return value: (int64)   : IPA of the stolen time data structure for this
+                              VCPU. On failure:
+                              NOT_SUPPORTED (-1)
+
+The IPA returned by PV_TIME_ST should be mapped by the guest as normal memory
+with inner and outer write back caching attributes, in the inner shareable
+domain. A total of 16 bytes from the IPA returned are guaranteed to be
+meaningfully filled by the hypervisor (see structure below).
+
+PV_TIME_ST returns the structure for the calling VCPU.
+
+Stolen Time
+-----------
+
+The structure pointed to by the PV_TIME_ST hypercall is as follows:
+
+  Field       | Byte Length | Byte Offset | Description
+  ----------- | ----------- | ----------- | --------------------------
+  Revision    |      4      |      0      | Must be 0 for version 0.1
+  Attributes  |      4      |      4      | Must be 0
+  Stolen time |      8      |      8      | Stolen time in unsigned
+              |             |             | nanoseconds indicating how
+              |             |             | much time this VCPU thread
+              |             |             | was involuntarily not
+              |             |             | running on a physical CPU.
+
+The structure will be updated by the hypervisor prior to scheduling a VCPU. It
+will be present within a reserved region of the normal memory given to the
+guest. The guest should not attempt to write into this memory. There is a
+structure per VCPU of the guest.
+
+For the user space interface see Documentation/virt/kvm/devices/vcpu.txt
+section "3. GROUP: KVM_ARM_VCPU_PVTIME_CTRL".
+
```
#### [PATCH] KVM: s390: Cleanup kvm_arch_init error path
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11170593
Return-Path: <SRS0=50xr=X3=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 81BEC13BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  2 Oct 2019 07:56:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 69DFA2133F
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  2 Oct 2019 07:56:50 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726942AbfJBH4t (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 2 Oct 2019 03:56:49 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:56874 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1725852AbfJBH4t (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 2 Oct 2019 03:56:49 -0400
Received: from pps.filterd (m0098394.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 x927qpVf111097
        for <kvm@vger.kernel.org>; Wed, 2 Oct 2019 03:56:48 -0400
Received: from e06smtp03.uk.ibm.com (e06smtp03.uk.ibm.com [195.75.94.99])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2vckugxnxp-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Wed, 02 Oct 2019 03:56:47 -0400
Received: from localhost
        by e06smtp03.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Wed, 2 Oct 2019 08:56:44 +0100
Received: from b06cxnps4074.portsmouth.uk.ibm.com (9.149.109.196)
        by e06smtp03.uk.ibm.com (192.168.101.133) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Wed, 2 Oct 2019 08:56:41 +0100
Received: from d06av23.portsmouth.uk.ibm.com (d06av23.portsmouth.uk.ibm.com
 [9.149.105.59])
        by b06cxnps4074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id x927ueP144499084
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 2 Oct 2019 07:56:40 GMT
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id B122AA405F;
        Wed,  2 Oct 2019 07:56:40 +0000 (GMT)
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id F21EDA405E;
        Wed,  2 Oct 2019 07:56:39 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.152.224.131])
        by d06av23.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Wed,  2 Oct 2019 07:56:39 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, borntraeger@de.ibm.com,
        david@redhat.com
Subject: [PATCH] KVM: s390: Cleanup kvm_arch_init error path
Date: Wed,  2 Oct 2019 03:56:27 -0400
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 19100207-0012-0000-0000-000003534296
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19100207-0013-0000-0000-0000218E44B3
Message-Id: <20191002075627.3582-1-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-10-02_04:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=999 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1908290000 definitions=main-1910020074
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Both kvm_s390_gib_destroy and debug_unregister test if the needed
pointers are not NULL and hence can be called unconditionally.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
---
 arch/s390/kvm/kvm-s390.c | 18 +++++++-----------
 1 file changed, 7 insertions(+), 11 deletions(-)

```
#### [PATCH v2] selftests: kvm: Fix libkvm build error
##### From: Shuah Khan <skhan@linuxfoundation.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Shuah Khan <skhan@linuxfoundation.org>
X-Patchwork-Id: 11171891
Return-Path: <SRS0=50xr=X3=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0455113BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  2 Oct 2019 23:03:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D77CF21D82
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  2 Oct 2019 23:03:50 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1570057430;
	bh=rGgf3M8E8cdrPPfviqTZz+CC5G0oBSB873QG+Zz57Gk=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=pXwDNnaPUQGkmBdGYs4pvzLC0jvYRsF1po7JwJ7yE4JnIENbmEut22Ao38uP3XwYH
	 zXdODJEhlVNFc45Dp6NvhrP156MaJsiLL3ohdX0ZX2S0AZFPDCjJXiaD//HsDEbodK
	 OsGTPgvl2D4vPXBwJAk4LlfzW1Pe/zvxzl+cmeo4=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728140AbfJBXDr (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 2 Oct 2019 19:03:47 -0400
Received: from mail-io1-f66.google.com ([209.85.166.66]:38299 "EHLO
        mail-io1-f66.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727976AbfJBXDq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 2 Oct 2019 19:03:46 -0400
Received: by mail-io1-f66.google.com with SMTP id u8so1200030iom.5
        for <kvm@vger.kernel.org>; Wed, 02 Oct 2019 16:03:46 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=linuxfoundation.org; s=google;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=oV/9b2AKj59V2uwPpS7RJHBFX/8QSHfj0AU6FMbpQCA=;
        b=dK+p1sIqIAJ8RGyefAphtb6lEwlpOLd/UkICw4usv/JjWR6t1kHw7a+p1pq3Qsqkj9
         URSJmGJkWDsHaeuLD2TGa7MWq+2juzA/OirywcxzN3IXLaSzy7LVKAXYH0Q+B54Ejfr4
         6PWic2A87QP2n0FYWCnFub7PPs/KIdmW0Lp+A=
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=oV/9b2AKj59V2uwPpS7RJHBFX/8QSHfj0AU6FMbpQCA=;
        b=P8xPUELAtfsfXNeFH5sISf5laOuP6qhvlppf4Oyw7slVXAMJJrobD/BJwNBXRUcMGl
         eGkldRL9IJZUpn7C/kQMiRJ1rTxtIDYpBsuByncKbcMk3zGu3GpoUI6tbstGd4MSXMkg
         ylSW2xe5BZPCxWDK8RXYVFUAjMguEa8DTpv1tndfST7KkJ0r0iZzei1UpmFY6fhqtZrC
         jLkzrI6ySTh3tHSlNhcDkxQE5nauhGbYMW54rhcrOwXHMAxdMPZsq7XlEbVuL8/vytgF
         /fPKhDNQHpYVlM05DOcAi47VOrKL/RmH45/UOKeDLM1OXRbLl2+rv6V7G/JGYl+8Kxzk
         BjHw==
X-Gm-Message-State: APjAAAVNx10ccANcx4o+Dc7d17XrmyxHslcAyTP2VdVgE6uGQPJ3/DHQ
        e2BE4XcdGbN20meZn8pebSoj0A==
X-Google-Smtp-Source: 
 APXvYqygZWjkzv74/ZqaLQIipRxpUSbpqKXqXE5cRKwBIa0D4JgiRCE/Hg8dKE+sssxzkBGZVNthGA==
X-Received: by 2002:a92:b74f:: with SMTP id c15mr6837193ilm.43.1570057425858;
        Wed, 02 Oct 2019 16:03:45 -0700 (PDT)
Received: from shuah-t480s.internal (c-24-9-64-241.hsd1.co.comcast.net.
 [24.9.64.241])
        by smtp.gmail.com with ESMTPSA id
 128sm212298iox.35.2019.10.02.16.03.44
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 02 Oct 2019 16:03:45 -0700 (PDT)
From: Shuah Khan <skhan@linuxfoundation.org>
To: pbonzini@redhat.com, rkrcmar@redhat.com, shuah@kernel.org
Cc: Shuah Khan <skhan@linuxfoundation.org>, kvm@vger.kernel.org,
        linux-kselftest@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH v2] selftests: kvm: Fix libkvm build error
Date: Wed,  2 Oct 2019 17:03:43 -0600
Message-Id: <20191002230343.5243-1-skhan@linuxfoundation.org>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Fix the following build error from "make TARGETS=kvm kselftest":

libkvm.a(assert.o): relocation R_X86_64_32 against `.rodata.str1.1' can not be used when making a PIE object; recompile with -fPIC

This error is seen when build is done from the main Makefile using
kselftest target. In this case KBUILD_CPPFLAGS and CC_OPTION_CFLAGS
are defined. When build is invoked using:

"make -C tools/testing/selftests/kvm" KBUILD_CPPFLAGS and CC_OPTION_CFLAGS
aren't defined.

There is no need to pass in KBUILD_CPPFLAGS and CC_OPTION_CFLAGS for the
check to determine if --no-pie is necessary1s, which is the when these
two aren't defined when "make -C tools/testing/selftests/kvm" runs.

Fix it by simplifying the no-pie-option logic. With this change, bith
build variations work.

"make TARGETS=kvm kselftest"
"make -C tools/testing/selftests/kvm"

Signed-off-by: Shuah Khan <skhan@linuxfoundation.org>
---
 tools/testing/selftests/kvm/Makefile | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [PATCH v2] x86/hyperv: make vapic support x2apic modeThread-Topic: [PATCH v2] x86/hyperv: make vapic support x2apic mode
##### From: Roman Kagan <rkagan@virtuozzo.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Roman Kagan <rkagan@virtuozzo.com>
X-Patchwork-Id: 11170735
Return-Path: <SRS0=50xr=X3=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E9AD914DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  2 Oct 2019 10:20:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id BBF6721929
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  2 Oct 2019 10:20:15 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=virtuozzo.com header.i=@virtuozzo.com
 header.b="TowX0301"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727465AbfJBKUP (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 2 Oct 2019 06:20:15 -0400
Received: from mail-eopbgr20115.outbound.protection.outlook.com
 ([40.107.2.115]:31977
        "EHLO EUR02-VE1-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726411AbfJBKUP (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 2 Oct 2019 06:20:15 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=mQTKo4470sUFZP3UCvS/oH3lOU4uyRGSu5xTmuT1/NRKrdMoJM6x7xclWF0UATdRk57tUbo+IohzNHYRX8cP8ryHyt9dbcKOMGUfMmFhxzJRW724Niop8O3pXJrhW4c54ak9kfFqk44LCeVHjGreUS06WBwY4Fo9cfV63UO2XX04cF5i92em6MFwGxb6efOujx1R/r42VmZ5lejzy07Dhj7mHXUrmtHLpEfZrgQW3mKQZEQLBxVOvJPXeoLGN5A2EeDSiXvH3W5WgW5UPNOd2YUfbncsjr/nqu/TK3Gzn7FXClumUcq2NC9pkn3JmuapQXbmIJcqth+yo3BKPWIGug==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=teYjUxnfLXRvMoHaB7k3rl6IWtZWWierVtlYdyFJjZ0=;
 b=GZgZ7NiDavF83c1frYRjdJpnsdCarYqxwipIz5DrPajVErMB3HyRB02PlPG+PC8OTUHFgZPrhohyf7uipvFeAG+6qVwaaEI/0cleM+gMcu1ulGgb9YaWEVQxNu8VO+5YT8XgnCB8wKB2UChPi/8MYbQD7+/vTWzF2XQWSPukyOe4k8P+A7ekxvZWvpsrJi2q/4NS08cY1NA7MvD4yPHETuRtwPlOo6kTTyYMJuyEvGwfmX9Nr/k7OnBgrjFkP1CniGPdayPxduazRK5Qi3Ht6L/IoPTs6wiCEX2V6n9NQWWtYhQC6jx7wph0dE+KywxTk2rQ9W59kR5ec8oYER8XhQ==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=virtuozzo.com; dmarc=pass action=none
 header.from=virtuozzo.com; dkim=pass header.d=virtuozzo.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=virtuozzo.com;
 s=selector2;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=teYjUxnfLXRvMoHaB7k3rl6IWtZWWierVtlYdyFJjZ0=;
 b=TowX03018vR7oSKrUxQtIMSupDgT4qeDDlMvmvKj+/3PXEe18F4IUdV+X3gEP6sFHHVB5WInCQ2qUl4bpx+vpPBiQMpNwNwNh5voFqJ+6whZcv9i1wC3cbnREm7M8N0grpaLztJ0HGHWiVf6CeJyYLl1BkAt9f3ZJpNOnQsVisM=
Received: from AM0PR08MB5537.eurprd08.prod.outlook.com (20.179.36.87) by
 AM0PR08MB3844.eurprd08.prod.outlook.com (20.178.22.156) with Microsoft SMTP
 Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.2305.20; Wed, 2 Oct 2019 10:19:30 +0000
Received: from AM0PR08MB5537.eurprd08.prod.outlook.com
 ([fe80::a8ea:5223:db78:dd3]) by AM0PR08MB5537.eurprd08.prod.outlook.com
 ([fe80::a8ea:5223:db78:dd3%7]) with mapi id 15.20.2305.022; Wed, 2 Oct 2019
 10:19:30 +0000
From: Roman Kagan <rkagan@virtuozzo.com>
To: Michael Kelley <mikelley@microsoft.com>,
        Lan Tianyu <Tianyu.Lan@microsoft.com>,
        Joerg Roedel <jroedel@suse.de>,
        "K. Y. Srinivasan" <kys@microsoft.com>,
        Haiyang Zhang <haiyangz@microsoft.com>,
        Stephen Hemminger <sthemmin@microsoft.com>,
        Sasha Levin <sashal@kernel.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        "H. Peter Anvin" <hpa@zytor.com>,
        "x86@kernel.org" <x86@kernel.org>,
        "linux-hyperv@vger.kernel.org" <linux-hyperv@vger.kernel.org>,
        "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>
CC: "kvm@vger.kernel.org" <kvm@vger.kernel.org>
Subject: [PATCH v2] x86/hyperv: make vapic support x2apic mode
Thread-Topic: [PATCH v2] x86/hyperv: make vapic support x2apic mode
Thread-Index: AQHVeQrgrl6z6kaUqkyr6D3zFBAn2A==
Date: Wed, 2 Oct 2019 10:19:30 +0000
Message-ID: <20191002101923.4981-1-rkagan@virtuozzo.com>
Accept-Language: en-US, ru-RU
Content-Language: en-US
X-MS-Has-Attach: 
X-MS-TNEF-Correlator: 
x-originating-ip: [185.231.240.5]
x-clientproxiedby: HE1PR02CA0119.eurprd02.prod.outlook.com
 (2603:10a6:7:29::48) To AM0PR08MB5537.eurprd08.prod.outlook.com
 (2603:10a6:208:148::23)
authentication-results: spf=none (sender IP is )
 smtp.mailfrom=rkagan@virtuozzo.com;
x-ms-exchange-messagesentrepresentingtype: 1
x-mailer: git-send-email 2.21.0
x-ms-publictraffictype: Email
x-ms-office365-filtering-correlation-id: dca16743-704c-4b16-b003-08d747220324
x-ms-traffictypediagnostic: AM0PR08MB3844:
x-microsoft-antispam-prvs: 
 <AM0PR08MB3844BD7556A066C2EA3CF868C99C0@AM0PR08MB3844.eurprd08.prod.outlook.com>
x-ms-oob-tlc-oobclassifiers: OLM:7691;
x-forefront-prvs: 0178184651
x-forefront-antispam-report: 
 SFV:NSPM;SFS:(10019020)(136003)(39850400004)(366004)(346002)(396003)(376002)(199004)(189003)(486006)(86362001)(81156014)(8676002)(81166006)(4326008)(25786009)(99286004)(8936002)(1076003)(71190400001)(6486002)(66476007)(66556008)(64756008)(66446008)(2201001)(71200400001)(6436002)(2616005)(476003)(2501003)(102836004)(110136005)(5660300002)(186003)(478600001)(52116002)(7736002)(6116002)(3846002)(316002)(2906002)(305945005)(1511001)(14454004)(14444005)(7416002)(256004)(6512007)(50226002)(66946007)(26005)(386003)(6506007)(66066001)(36756003)(921003)(1121003);DIR:OUT;SFP:1102;SCL:1;SRVR:AM0PR08MB3844;H:AM0PR08MB5537.eurprd08.prod.outlook.com;FPR:;SPF:None;LANG:en;PTR:InfoNoRecords;A:1;MX:1;
received-spf: None (protection.outlook.com: virtuozzo.com does not designate
 permitted sender hosts)
x-ms-exchange-senderadcheck: 1
x-microsoft-antispam: BCL:0;
x-microsoft-antispam-message-info: 
 vuFvy4Ej0x1Ys6P9L6/eS0o46QOQdZY7lx5u0QexIdHOyqS2Ei2DOErW1Q9fVVYwNTeQZBRQWyvA0CvjLwFKMARqb8sPB38iE6321TS+Khvrx7EYHMJfEc5ecTUkeeoJXIjV5y9hJ5JwispQePT9tYY+bl0P/xkRdb3ZW78bHMfeNTCDQZYLAk1+Ux6TZdV5s2M+ENDGzbKVbJc09qnrUUFIt9qznoqQyeW2RTRpExZtfUy+JA844VHG8BJZVlo9WfNLyDccV/OTYgfW8Ym455RpTDqyI1u4bjeykFgtYpZQMQgHvn0cKnJVTwzLg3Bevz+lDpwzDM2fmo51myMILI/7mesI2fsLB1IBmXnW6fwPJsKto9MFqoE405HlvFvPpOJ2rS7X5VD5oT3rik438VGFmiQKdFrUX8JNhzPSwC0=
x-ms-exchange-transport-forked: True
Content-Type: text/plain; charset="iso-8859-1"
MIME-Version: 1.0
X-OriginatorOrg: virtuozzo.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 dca16743-704c-4b16-b003-08d747220324
X-MS-Exchange-CrossTenant-originalarrivaltime: 02 Oct 2019 10:19:30.6209
 (UTC)
X-MS-Exchange-CrossTenant-fromentityheader: Hosted
X-MS-Exchange-CrossTenant-id: 0bc7f26d-0264-416e-a6fc-8352af79c58f
X-MS-Exchange-CrossTenant-mailboxtype: HOSTED
X-MS-Exchange-CrossTenant-userprincipalname: 
 mElhHLYs8j38eJaROShcUpGtNcwYsYFKSwDh9qwlor+xI7IgSMO58xKwBWdaypFWy9hUm7GKpp8wxwl4DzILtA==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: AM0PR08MB3844
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Now that there's Hyper-V IOMMU driver, Linux can switch to x2apic mode
when supported by the vcpus.

However, the apic access functions for Hyper-V enlightened apic assume
xapic mode only.

As a result, Linux fails to bring up secondary cpus when run as a guest
in QEMU/KVM with both hv_apic and x2apic enabled.

I didn't manage to make my instance of Hyper-V expose x2apic to the
guest; nor does Hyper-V spec document the expected behavior.  However,
a Windows guest running in QEMU/KVM with hv_apic and x2apic and a big
number of vcpus (so that it turns on x2apic mode) does use enlightened
apic MSRs passing unshifted 32bit destination id and falls back to the
regular x2apic MSRs for less frequently used apic fields.

So implement the same behavior, by replacing enlightened apic access
functions (only those where it makes a difference) with their
x2apic-aware versions when x2apic is in use.

Fixes: 29217a474683 ("iommu/hyper-v: Add Hyper-V stub IOMMU driver")
Fixes: 6b48cb5f8347 ("X86/Hyper-V: Enlighten APIC access")
Cc: stable@vger.kernel.org
Signed-off-by: Roman Kagan <rkagan@virtuozzo.com>
---
v1 -> v2:
- add ifdefs to handle !CONFIG_X86_X2APIC

 arch/x86/hyperv/hv_apic.c | 54 ++++++++++++++++++++++++++++++++++++---
 1 file changed, 51 insertions(+), 3 deletions(-)

```
