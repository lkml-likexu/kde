#### [RFC PATCH v7 1/7] arm/arm64: smccc/psci: add arm_smccc_1_1_get_conduit()
##### From: Jianyong Wu <jianyong.wu@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jianyong Wu <jianyong.wu@arm.com>
X-Patchwork-Id: 11243619
Return-Path: <SRS0=Qdv9=ZG=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2779A930
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 14 Nov 2019 12:14:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 128782071B
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 14 Nov 2019 12:14:28 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727001AbfKNMOY (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 14 Nov 2019 07:14:24 -0500
Received: from foss.arm.com ([217.140.110.172]:41846 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726115AbfKNMOX (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 14 Nov 2019 07:14:23 -0500
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 3BB1F328;
        Thu, 14 Nov 2019 04:14:23 -0800 (PST)
Received: from entos-d05.shanghai.arm.com (entos-d05.shanghai.arm.com
 [10.169.40.35])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPA id
 04BFD3F6C4;
        Thu, 14 Nov 2019 04:14:15 -0800 (PST)
From: Jianyong Wu <jianyong.wu@arm.com>
To: netdev@vger.kernel.org, yangbo.lu@nxp.com, john.stultz@linaro.org,
        tglx@linutronix.de, pbonzini@redhat.com,
        sean.j.christopherson@intel.com, maz@kernel.org,
        richardcochran@gmail.com, Mark.Rutland@arm.com, will@kernel.org,
        suzuki.poulose@arm.com
Cc: linux-kernel@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        Steve.Capper@arm.com, Kaly.Xin@arm.com, justin.he@arm.com,
        jianyong.wu@arm.com, nd@arm.com,
        Mark Rutland <mark.rutland@arm.com>,
        Catalin Marinas <catalin.marinas@arm.com>
Subject: [RFC PATCH v7 1/7] arm/arm64: smccc/psci: add
 arm_smccc_1_1_get_conduit()
Date: Thu, 14 Nov 2019 20:13:52 +0800
Message-Id: <20191114121358.6684-2-jianyong.wu@arm.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20191114121358.6684-1-jianyong.wu@arm.com>
References: <20191114121358.6684-1-jianyong.wu@arm.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Mark Rutland <mark.rutland@arm.com>

SMCCC callers are currently amassing a collection of enums for the SMCCC
conduit, and are having to dig into the PSCI driver's internals in order
to figure out what to do.

Let's clean this up, with common SMCCC_CONDUIT_* definitions, and an
arm_smccc_1_1_get_conduit() helper that abstracts the PSCI driver's
internal state.

We can kill off the PSCI_CONDUIT_* definitions once we've migrated users
over to the new interface.

Signed-off-by: Mark Rutland <mark.rutland@arm.com>
Acked-by: Lorenzo Pieralisi <lorenzo.pieralisi@arm.com>
Acked-by: Will Deacon <will.deacon@arm.com>
Signed-off-by: Catalin Marinas <catalin.marinas@arm.com>
---
 drivers/firmware/psci/psci.c | 15 +++++++++++++++
 include/linux/arm-smccc.h    | 16 ++++++++++++++++
 2 files changed, 31 insertions(+)

```
#### [PATCH] Fixup sida bouncing
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11243993
Return-Path: <SRS0=Qdv9=ZG=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5F44613BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 14 Nov 2019 16:22:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4914920715
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 14 Nov 2019 16:22:42 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726473AbfKNQWl (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 14 Nov 2019 11:22:41 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:37724 "EHLO
        mx0b-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726263AbfKNQWl (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 14 Nov 2019 11:22:41 -0500
Received: from pps.filterd (m0127361.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 xAEGLBCo071798
        for <kvm@vger.kernel.org>; Thu, 14 Nov 2019 11:22:39 -0500
Received: from e06smtp01.uk.ibm.com (e06smtp01.uk.ibm.com [195.75.94.97])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2w92jm6nwd-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Thu, 14 Nov 2019 11:22:36 -0500
Received: from localhost
        by e06smtp01.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Thu, 14 Nov 2019 16:22:03 -0000
Received: from b06cxnps3074.portsmouth.uk.ibm.com (9.149.109.194)
        by e06smtp01.uk.ibm.com (192.168.101.131) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Thu, 14 Nov 2019 16:22:00 -0000
Received: from d06av25.portsmouth.uk.ibm.com (d06av25.portsmouth.uk.ibm.com
 [9.149.105.61])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id xAEGLwxm65798238
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 14 Nov 2019 16:21:59 GMT
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id CDE4711C052;
        Thu, 14 Nov 2019 16:21:58 +0000 (GMT)
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 7F17F11C050;
        Thu, 14 Nov 2019 16:21:57 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.152.224.131])
        by d06av25.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Thu, 14 Nov 2019 16:21:57 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, david@redhat.com, thuth@redhat.com,
        borntraeger@de.ibm.com, imbrenda@linux.ibm.com,
        mihajlov@linux.ibm.com, mimu@linux.ibm.com, cohuck@redhat.com
Subject: [PATCH] Fixup sida bouncing
Date: Thu, 14 Nov 2019 11:21:53 -0500
X-Mailer: git-send-email 2.20.1
In-Reply-To: <ad0f9b90-3ce4-c2d2-b661-635fe439f7e2@redhat.com>
References: <ad0f9b90-3ce4-c2d2-b661-635fe439f7e2@redhat.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 19111416-4275-0000-0000-0000037DBE94
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19111416-4276-0000-0000-000038912593
Message-Id: <20191114162153.25349-1-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-11-14_05:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=649 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1910280000 definitions=main-1911140147
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
---
 arch/s390/kvm/kvm-s390.c | 19 +++++++++++++------
 1 file changed, 13 insertions(+), 6 deletions(-)

```
#### [PATCH v5 1/8] KVM: VMX: Add helper to check reserved bits in IA32_PERF_GLOBAL_CTRL
##### From: Oliver Upton <oupton@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Oliver Upton <oupton@google.com>
X-Patchwork-Id: 11242895
Return-Path: <SRS0=Qdv9=ZG=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A5EFE1393
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 14 Nov 2019 00:17:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 414A0206F2
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 14 Nov 2019 00:17:38 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="nb+hQLZC"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726557AbfKNARh (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 13 Nov 2019 19:17:37 -0500
Received: from mail-ua1-f73.google.com ([209.85.222.73]:36708 "EHLO
        mail-ua1-f73.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726195AbfKNARg (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 13 Nov 2019 19:17:36 -0500
Received: by mail-ua1-f73.google.com with SMTP id r39so1066066uad.3
        for <kvm@vger.kernel.org>; Wed, 13 Nov 2019 16:17:34 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=k+kFDmW+TZm9uAXFmGbrnJC5CPVNW5UAKaPtdur5YLA=;
        b=nb+hQLZC15W0K8WXRmuQy4fdq0rp5A4JbyupyxdXgL2X3VhQPx23GRz4EAcNgaCWlN
         wQ+aRlFjAJQ2MlwNjc5hIyqHU7HLxoNy1ts1s93b6f8JsgW1h6KIo47EDS1sX4ElD+Sy
         q06A8vJ7LWdUCphs18CBwzfh+XXgzRxnB7WvF0kGMjy0P3Arx8qhE/IRweOdUmbYlWlk
         Q2a4vTVh/uTOqqQv4eSD9IAzen8mdbyvt8gZMiOl7c66MdESQMTzBuwfU+A4Kk62sFTH
         sNR5oEKJdZUbEVcRBqatvxgLOHz3apKKscxYAhjP6QSf+0NRk64pSfLgofRWgW011NqA
         o0Ug==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=k+kFDmW+TZm9uAXFmGbrnJC5CPVNW5UAKaPtdur5YLA=;
        b=uYVmRiP7FCO/fzEvxhGPuhZx/wyMZzHgdLYe0jfsgFksCqSU4bmM4IVUsbHcl1JoU/
         2+CZtcghE8BS2zU1RRk8T+kwAKun5l0JW6/RDHkOVIHQgqihMQqcVc8zbgI86HvFNhZu
         alouIqEy9S7r6UuUk2qdqDorGN8SlcbAb2Yq2vK446RVHGouJS1fs6xToyUjcwIVfj0R
         JStzecPd2TN5JVgM5thcMsYHVQxrVkkDIA4HDDNboCpvIPrXIURmch8nu8be4IgAbqpT
         1bY/XemFdjSs8d7KTAb7npYOfN75tDIDMGSdPSy7YeVR3NvUSgA2180KzwWcJ2U45sYx
         bCtQ==
X-Gm-Message-State: APjAAAUDxE5uYcW5xB4xk3/gPn0ly6y81boN95MKMZ3Z9dXvRtAZdzs3
        NUmc5WQNO/OcxdkZp2kH85dUIhUzclzDOLOwgWRymxaB+9S29h4w9VvCye8trRaP5KFd0hyQTDz
        jQdALkRCqY1oO2gXepbqyUO3YiHSqBTXVgX/Crs4q0JxLgUuPJfe5irLrxQ==
X-Google-Smtp-Source: 
 APXvYqwna/gXQTrY9o3e39CR7hive+a2govJYQk8eL/5hYoyxFh3SYxseEVMt871AFGLc3oT3jqWQXPbWR8=
X-Received: by 2002:ab0:7d2:: with SMTP id d18mr4059285uaf.68.1573690653917;
 Wed, 13 Nov 2019 16:17:33 -0800 (PST)
Date: Wed, 13 Nov 2019 16:17:15 -0800
In-Reply-To: <20191114001722.173836-1-oupton@google.com>
Message-Id: <20191114001722.173836-2-oupton@google.com>
Mime-Version: 1.0
References: <20191114001722.173836-1-oupton@google.com>
X-Mailer: git-send-email 2.24.0.rc1.363.gb1bccd3e3d-goog
Subject: [PATCH v5 1/8] KVM: VMX: Add helper to check reserved bits in
 IA32_PERF_GLOBAL_CTRL
From: Oliver Upton <oupton@google.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>, "
	=?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= " <rkrcmar@redhat.com>
Cc: Jim Mattson <jmattson@google.com>, Peter Shier <pshier@google.com>,
        Krish Sadhukhan <krish.sadhukhan@oracle.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Oliver Upton <oupton@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Create a helper function to check the validity of a proposed value for
IA32_PERF_GLOBAL_CTRL from the existing check in intel_pmu_set_msr().

Per Intel's SDM, the reserved bits in IA32_PERF_GLOBAL_CTRL must be
cleared for the corresponding host/guest state fields.

Suggested-by: Jim Mattson <jmattson@google.com>
Co-developed-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Signed-off-by: Oliver Upton <oupton@google.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
---
 arch/x86/kvm/pmu.h           | 6 ++++++
 arch/x86/kvm/vmx/pmu_intel.c | 2 +-
 2 files changed, 7 insertions(+), 1 deletion(-)

```
#### [PATCH v5 01/18] kvm: x86: Modify kvm_x86_ops.get_enable_apicv() to use struct kvm parameter
##### From: Suravee Suthikulpanit <suravee.suthikulpanit@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Suravee Suthikulpanit <Suravee.Suthikulpanit@amd.com>
X-Patchwork-Id: 11244433
Return-Path: <SRS0=Qdv9=ZG=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AC62114E5
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 14 Nov 2019 20:15:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 83B5220723
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 14 Nov 2019 20:15:37 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="XKbsHqXd"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727016AbfKNUPg (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 14 Nov 2019 15:15:36 -0500
Received: from mail-eopbgr730059.outbound.protection.outlook.com
 ([40.107.73.59]:60877
        "EHLO NAM05-DM3-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726632AbfKNUPf (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 14 Nov 2019 15:15:35 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=RPxLtFDBiyYGfiBCdJxgrHa3ET/KKTLguog2cO4OUrLS2CP8+BzUB+P/wMMFRDDB/0chuaTp4WfDpO0QFwKqIgcufslXdc89x+0g6GKFfsu0O+opLgFxSTnk2tRO89U5pjC4LdMGyp7cmJ6DJHYcypdo18eClvYHgOeEkRg7EK2I2RbWNdD4rUFfBGY02HeqpfAt3g9aOycpEsb43ExFAYTEnmJ/CmgKMcurVSECEBdD2EFufoWtqrkY2hxs3NtN1tXD5fWcK0N92dDlrhga/yQsR1AD3OVRLcde++QX4DYZbZ4sxMJrZXsVRZad+bU6gTNVKDZuz2C+ar9by6M1vg==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=xzDipuGPRPvDcktOm15fhfWxGqoQnuRsVISBpEaSiCc=;
 b=fspMg41v12nY1lBy97iSSepKQdJTk7FzQ6Q+UT/YUT9NOugWrPW8h0cVOuPTFwquyQLfrdeJ+KfV/PxNhBFBu0LTzPS620PJDwR0V0bqSnMzuzWiABEzJfkdP0Bno6uEw76YFD66EdAurYaO0ggQDDWjFqJGCd3A55Dx8M7GNl1CUPFKVjWl+/mTNy1BLtoM6X9SpNJ05UOwgj0f7fNUUNHAAFUUO4KtwFiWrk9dWTdu+k9U6CL7YpGeuKycaQY9vWmnWQi3jF0WBVSikNE0EUgZmFyWWVoUMl5GMWW9cQbOXOup11Z8WQPQzvg4gL/uTMZSu7F8dhBHtw2yyXjv3w==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=xzDipuGPRPvDcktOm15fhfWxGqoQnuRsVISBpEaSiCc=;
 b=XKbsHqXdnvEiAERrlpX3ObD9BVgwLBEfLzQUYo5GXcqi6YqDXaB4OlQmc9nTuI3X/jvzdVg3k/pCttbuJLWSMMmKiHJxT5PwCCt9jqZ/HKZb79q9h8fBw8JgFUMk4fB1MexqxMrsGECsCrv8hCncPWgNDR9lGCU8JulCT650ey4=
Authentication-Results: spf=none (sender IP is )
 smtp.mailfrom=Suravee.Suthikulpanit@amd.com;
Received: from DM6PR12MB3865.namprd12.prod.outlook.com (10.255.173.210) by
 DM6PR12MB3739.namprd12.prod.outlook.com (10.255.172.140) with Microsoft SMTP
 Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.2451.23; Thu, 14 Nov 2019 20:15:32 +0000
Received: from DM6PR12MB3865.namprd12.prod.outlook.com
 ([fe80::4898:93e0:3c0c:d862]) by DM6PR12MB3865.namprd12.prod.outlook.com
 ([fe80::4898:93e0:3c0c:d862%6]) with mapi id 15.20.2451.027; Thu, 14 Nov 2019
 20:15:32 +0000
From: Suravee Suthikulpanit <suravee.suthikulpanit@amd.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: pbonzini@redhat.com, rkrcmar@redhat.com, joro@8bytes.org,
        vkuznets@redhat.com, rkagan@virtuozzo.com, graf@amazon.com,
        jschoenh@amazon.de, karahmed@amazon.de, rimasluk@amazon.com,
        jon.grimm@amd.com,
        Suravee Suthikulpanit <suravee.suthikulpanit@amd.com>
Subject: [PATCH v5 01/18] kvm: x86: Modify kvm_x86_ops.get_enable_apicv() to
 use struct kvm parameter
Date: Thu, 14 Nov 2019 14:15:03 -0600
Message-Id: <1573762520-80328-2-git-send-email-suravee.suthikulpanit@amd.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1573762520-80328-1-git-send-email-suravee.suthikulpanit@amd.com>
References: <1573762520-80328-1-git-send-email-suravee.suthikulpanit@amd.com>
X-ClientProxiedBy: SN1PR12CA0099.namprd12.prod.outlook.com
 (2603:10b6:802:21::34) To DM6PR12MB3865.namprd12.prod.outlook.com
 (2603:10b6:5:1c8::18)
MIME-Version: 1.0
X-Mailer: git-send-email 1.8.3.1
X-Originating-IP: [165.204.78.1]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 9afe5bb6-0b04-4f3f-c25d-08d7693f665b
X-MS-TrafficTypeDiagnostic: DM6PR12MB3739:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM6PR12MB3739AC21621C91AA77F73927F3710@DM6PR12MB3739.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:2582;
X-Forefront-PRVS: 02213C82F8
X-Forefront-Antispam-Report: 
 SFV:NSPM;SFS:(10009020)(4636009)(396003)(366004)(376002)(39860400002)(346002)(136003)(189003)(199004)(6506007)(25786009)(86362001)(6512007)(6436002)(8676002)(47776003)(7416002)(66066001)(6486002)(50226002)(4326008)(3846002)(8936002)(4720700003)(81156014)(2906002)(16586007)(7736002)(66556008)(305945005)(66476007)(2616005)(6116002)(66946007)(186003)(316002)(14454004)(486006)(478600001)(99286004)(81166006)(26005)(14444005)(476003)(5660300002)(44832011)(386003)(446003)(52116002)(51416003)(76176011)(50466002)(6666004)(36756003)(11346002)(48376002);DIR:OUT;SFP:1101;SCL:1;SRVR:DM6PR12MB3739;H:DM6PR12MB3865.namprd12.prod.outlook.com;FPR:;SPF:None;LANG:en;PTR:InfoNoRecords;MX:1;A:1;
Received-SPF: None (protection.outlook.com: amd.com does not designate
 permitted sender hosts)
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 gBAC2QZSyg/Z/gxV06BUE4bB6ixQk6f+GqYTMYz0PFRDS0CVCvDR9Q3eiYidJlCiarCCj4SNvGFqcXVm8rELMHdQBg/p4db+8DbG8WA3XJeRShWCcCKixfIHVFf83gsmyhhwUblH/rLStVRQCTsATWgGCS+os1lZKOFp3pjYgVuBayrUaahvDOm7fpjy7hApXnOYvFjytAZkKyErH8Xw5milhqpS6VxUyCwf4YupHCTKnzUO0kVRGRcHid8C77RrAh5QbtTYRInpwlvcnEO4HBka9QDFrOflrwSiiM19/bhgDe7GSexC+5DV4F4PWWE+3rxFvqAkUL0tfW2174vcAVdHviCmRBGWDwZ4yJY0jARWQor32zx+VCHCHAxxewy06hZt7wccH6SU4ZH8KaPBb4nOAxKZtIDeULATXbl9ShNT9K3L3TftW6kTm6XyMFD1
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 9afe5bb6-0b04-4f3f-c25d-08d7693f665b
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 14 Nov 2019 20:15:32.1297
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 PIS0HwEVCVghDHzKvgXj2A1Ybte0IWKuymGzwAzz/l+asIshtiLi8nz1UawYOSeX1BjiefEyOE+7pi9+DOmz0w==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6PR12MB3739
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Generally, APICv for all vcpus in the VM are enable/disable in the same
manner. So, get_enable_apicv() should represent APICv status of the VM
instead of each VCPU.

Modify kvm_x86_ops.get_enable_apicv() to take struct kvm as parameter
instead of struct kvm_vcpu.

Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Signed-off-by: Suravee Suthikulpanit <suravee.suthikulpanit@amd.com>
---
 arch/x86/include/asm/kvm_host.h | 2 +-
 arch/x86/kvm/svm.c              | 4 ++--
 arch/x86/kvm/vmx/vmx.c          | 2 +-
 arch/x86/kvm/x86.c              | 2 +-
 4 files changed, 5 insertions(+), 5 deletions(-)

```
#### [PATCH net-next v2 01/15] vsock/vmci: remove unused VSOCK_DEFAULT_CONNECT_TIMEOUT
##### From: Stefano Garzarella <sgarzare@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stefano Garzarella <sgarzare@redhat.com>
X-Patchwork-Id: 11243297
Return-Path: <SRS0=Qdv9=ZG=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 685651393
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 14 Nov 2019 09:58:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 498D2206D9
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 14 Nov 2019 09:58:10 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="V4eVAMxB"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726852AbfKNJ6J (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 14 Nov 2019 04:58:09 -0500
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:58853 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726628AbfKNJ6J (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 14 Nov 2019 04:58:09 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1573725488;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=ZC4IS+wABP7CjGBt1y2Fdpp5FeX+/EyGMLh5jKY6eME=;
        b=V4eVAMxB2+I2mwUj+kTMDx3DF2lNoeKxlLnwKFaMncOifVgjfelvPwHXiL3CFq9t9eTcHl
        FGlulHAjZ/w/z7DsYg/CR5xq4ZJ87830ZkGvZHjDJ42fgwNP9CpgXvrrJZ1sQ7P93USk+P
        uvI/yhOszCKVuXtT7pKB9YgXe8Jo+TQ=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-424-crdwlIMvN4K-IxoPHTS3jQ-1; Thu, 14 Nov 2019 04:58:06 -0500
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id E9AAB107ACC5;
        Thu, 14 Nov 2019 09:58:04 +0000 (UTC)
Received: from steredhat.redhat.com (ovpn-117-81.ams2.redhat.com
 [10.36.117.81])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 89442165D3;
        Thu, 14 Nov 2019 09:57:59 +0000 (UTC)
From: Stefano Garzarella <sgarzare@redhat.com>
To: netdev@vger.kernel.org
Cc: Stephen Hemminger <sthemmin@microsoft.com>,
        Arnd Bergmann <arnd@arndb.de>,
        Jorgen Hansen <jhansen@vmware.com>,
        Jason Wang <jasowang@redhat.com>,
        Greg Kroah-Hartman <gregkh@linuxfoundation.org>,
        linux-kernel@vger.kernel.org,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Haiyang Zhang <haiyangz@microsoft.com>,
        Stefan Hajnoczi <stefanha@redhat.com>,
        "David S. Miller" <davem@davemloft.net>,
        virtualization@lists.linux-foundation.org, kvm@vger.kernel.org,
        Sasha Levin <sashal@kernel.org>,
        "K. Y. Srinivasan" <kys@microsoft.com>,
        Dexuan Cui <decui@microsoft.com>, linux-hyperv@vger.kernel.org
Subject: [PATCH net-next v2 01/15] vsock/vmci: remove unused
 VSOCK_DEFAULT_CONNECT_TIMEOUT
Date: Thu, 14 Nov 2019 10:57:36 +0100
Message-Id: <20191114095750.59106-2-sgarzare@redhat.com>
In-Reply-To: <20191114095750.59106-1-sgarzare@redhat.com>
References: <20191114095750.59106-1-sgarzare@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
X-MC-Unique: crdwlIMvN4K-IxoPHTS3jQ-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The VSOCK_DEFAULT_CONNECT_TIMEOUT definition was introduced with
commit d021c344051af ("VSOCK: Introduce VM Sockets"), but it is
never used in the net/vmw_vsock/vmci_transport.c.

VSOCK_DEFAULT_CONNECT_TIMEOUT is used and defined in
net/vmw_vsock/af_vsock.c

Cc: Jorgen Hansen <jhansen@vmware.com>
Reviewed-by: Stefan Hajnoczi <stefanha@redhat.com>
Reviewed-by: Jorgen Hansen <jhansen@vmware.com>
Signed-off-by: Stefano Garzarella <sgarzare@redhat.com>
---
 net/vmw_vsock/vmci_transport.c | 5 -----
 1 file changed, 5 deletions(-)

```
