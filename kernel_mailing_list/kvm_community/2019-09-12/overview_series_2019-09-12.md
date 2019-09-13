#### [GIT PULL 1/2] KVM: s390: kvm_s390_vm_start_migration: check dirty_bitmap before using it as target for memset()
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11143095
Return-Path: <SRS0=ujOk=XH=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6C1B0912
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Sep 2019 13:39:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 524E520CC7
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Sep 2019 13:39:31 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732180AbfILNja (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 12 Sep 2019 09:39:30 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:33552 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1731818AbfILNj3 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 12 Sep 2019 09:39:29 -0400
Received: from pps.filterd (m0098393.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 x8CDWAGU090296
        for <kvm@vger.kernel.org>; Thu, 12 Sep 2019 09:39:28 -0400
Received: from e06smtp02.uk.ibm.com (e06smtp02.uk.ibm.com [195.75.94.98])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2uynjhbx00-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Thu, 12 Sep 2019 09:39:28 -0400
Received: from localhost
        by e06smtp02.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <borntraeger@de.ibm.com>;
        Thu, 12 Sep 2019 14:39:26 +0100
Received: from b06avi18626390.portsmouth.uk.ibm.com (9.149.26.192)
        by e06smtp02.uk.ibm.com (192.168.101.132) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Thu, 12 Sep 2019 14:39:23 +0100
Received: from d06av23.portsmouth.uk.ibm.com (d06av23.portsmouth.uk.ibm.com
 [9.149.105.59])
        by b06avi18626390.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id x8CDcvB439387586
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 12 Sep 2019 13:38:57 GMT
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 8647BA404D;
        Thu, 12 Sep 2019 13:39:22 +0000 (GMT)
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 746B1A4055;
        Thu, 12 Sep 2019 13:39:22 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av23.portsmouth.uk.ibm.com (Postfix) with ESMTPS;
        Thu, 12 Sep 2019 13:39:22 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 25651)
        id 2FE48E0443; Thu, 12 Sep 2019 15:39:22 +0200 (CEST)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>
Cc: KVM <kvm@vger.kernel.org>, Cornelia Huck <cohuck@redhat.com>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        linux-s390 <linux-s390@vger.kernel.org>,
        Janosch Frank <frankja@linux.vnet.ibm.com>,
        David Hildenbrand <david@redhat.com>
Subject: [GIT PULL 1/2] KVM: s390: kvm_s390_vm_start_migration: check
 dirty_bitmap before using it as target for memset()
Date: Thu, 12 Sep 2019 15:39:20 +0200
X-Mailer: git-send-email 2.21.0
In-Reply-To: <20190912133921.6886-1-borntraeger@de.ibm.com>
References: <20190912133921.6886-1-borntraeger@de.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 19091213-0008-0000-0000-00000314CBE5
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19091213-0009-0000-0000-00004A333BD5
Message-Id: <20190912133921.6886-2-borntraeger@de.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-09-12_06:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=0 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=940 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1906280000 definitions=main-1909120143
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Igor Mammedov <imammedo@redhat.com>

If userspace doesn't set KVM_MEM_LOG_DIRTY_PAGES on memslot before calling
kvm_s390_vm_start_migration(), kernel will oops with:

  Unable to handle kernel pointer dereference in virtual kernel address space
  Failing address: 0000000000000000 TEID: 0000000000000483
  Fault in home space mode while using kernel ASCE.
  AS:0000000002a2000b R2:00000001bff8c00b R3:00000001bff88007 S:00000001bff91000 P:000000000000003d
  Oops: 0004 ilc:2 [#1] SMP
  ...
  Call Trace:
  ([<001fffff804ec552>] kvm_s390_vm_set_attr+0x347a/0x3828 [kvm])
   [<001fffff804ecfc0>] kvm_arch_vm_ioctl+0x6c0/0x1998 [kvm]
   [<001fffff804b67e4>] kvm_vm_ioctl+0x51c/0x11a8 [kvm]
   [<00000000008ba572>] do_vfs_ioctl+0x1d2/0xe58
   [<00000000008bb284>] ksys_ioctl+0x8c/0xb8
   [<00000000008bb2e2>] sys_ioctl+0x32/0x40
   [<000000000175552c>] system_call+0x2b8/0x2d8
  INFO: lockdep is turned off.
  Last Breaking-Event-Address:
   [<0000000000dbaf60>] __memset+0xc/0xa0

due to ms->dirty_bitmap being NULL, which might crash the host.

Make sure that ms->dirty_bitmap is set before using it or
return -EINVAL otherwise.

Cc: <stable@vger.kernel.org>
Fixes: afdad61615cc ("KVM: s390: Fix storage attributes migration with memory slots")
Signed-off-by: Igor Mammedov <imammedo@redhat.com>
Link: https://lore.kernel.org/kvm/20190911075218.29153-1-imammedo@redhat.com/
Reviewed-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Christian Borntraeger <borntraeger@de.ibm.com>
Reviewed-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: Janosch Frank <frankja@linux.ibm.com>
Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 arch/s390/kvm/kvm-s390.c | 2 ++
 1 file changed, 2 insertions(+)

```
#### [PATCH] kvm: nvmx: limit atomic switch MSRsFrom: Marc Orr <marcorr@google.com>
##### From: Marc Orr <marcorr@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Orr <marcorr@google.com>
X-Patchwork-Id: 11143651
Return-Path: <SRS0=ujOk=XH=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7E33014ED
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Sep 2019 18:11:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5F9842081B
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Sep 2019 18:11:12 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="pjE+0Yr6"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727000AbfILSLL (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 12 Sep 2019 14:11:11 -0400
Received: from mail-pl1-f201.google.com ([209.85.214.201]:35977 "EHLO
        mail-pl1-f201.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726986AbfILSLL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 12 Sep 2019 14:11:11 -0400
Received: by mail-pl1-f201.google.com with SMTP id z7so14644325plo.3
        for <kvm@vger.kernel.org>; Thu, 12 Sep 2019 11:11:10 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=IOK6Oqh2vh89Leb/hwKJdMjwLKONo65EI6QbrZVSCqU=;
        b=pjE+0Yr6zBzBLtFpVEk4AM5T+jXJgc2AvcPMA8UTMAK7oUcaOEQGZRmMcXBU35gA/O
         6ZY65PHYl7V9q4/JF4leNKmCV7Apa5XY34Gu+Erpxi0j1fHI32U2VNrJ5oyAOz7wPRVv
         kE3xjFnn7Q2RRsQk4MHnS4sBd/MKvY/5TmVESijx5tRxDmb0RLozi2AOjFuRLhphATMt
         BSEq9AYb9DYJX8gH7cjty9mAI3SGkFgRgUKBmZnToviT154fJFPFu303Vs/7F0L5sSoG
         ZdHyQpGcy9GDiDH6k8ayc3MG3X8fTIjlWn6+7jjdSoQYxnncBTvEG1NKB5Gyp5zHpUlD
         3zuA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=IOK6Oqh2vh89Leb/hwKJdMjwLKONo65EI6QbrZVSCqU=;
        b=sGbBaBDwPoFBVnhqLZJVl29u0ijvJE97payA1rx6yI/RQsMzV2gG1e7N10d8t3X+cH
         B/8MdAwmrwXn+OYIsJd2ITsH3ODfJruNT+ROquMNIDeyJxXtTSgCa+Lb3CyEABV2FF0o
         S5biMNXd+xxh500YgsunMlBi+8e59XHe1cTa5Sx7T/g8IKMBrgqqIA18pKtoL2XGnqib
         9QA4bfgu324JgPWkOB70mN6kQHJN+jNm436yLVaSkaWr+SlDCYWXXg0R50JivakIC6DX
         EwgX3trNrdwzK1YiIjW048fA+1Z7Qhwg2ji6Oj8c7SCy+ns97IVLSd5EwR2tzKu0ittV
         S8Hg==
X-Gm-Message-State: APjAAAUuqsl6PMBeOzW+2hYqitN4NzHMRGDYmyhvFt/MLhBKW7yYtW28
        ktrBQ0OPkqgPtWKBCCh5BJSyPOX5AlB42nezzRro0whNxsY8bcy5gE8XZgmUjEpZcXq3YV7ox1V
        8Fur5JJP6khAIdWg8lyD05w8gA4OShtG9lD5caWw5H0QoK+zCEm+YZjPBMC3c
X-Google-Smtp-Source: 
 APXvYqyzrhzNt0OfGS2Hk3z+fpHkJgg3309ngNRCDtZlz6M8WbchENoPfyf+6FuvK45deOqrNsLiHMM7Tzr+
X-Received: by 2002:a65:6552:: with SMTP id a18mr7985263pgw.208.1568311870081;
 Thu, 12 Sep 2019 11:11:10 -0700 (PDT)
Date: Thu, 12 Sep 2019 11:11:00 -0700
Message-Id: <20190912181100.131124-1-marcorr@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.23.0.237.gc6a4ce50a0-goog
Subject: [PATCH] kvm: nvmx: limit atomic switch MSRs
From: Marc Orr <marcorr@google.com>
To: kvm@vger.kernel.org, jmattson@google.com, pshier@google.com
Cc: Marc Orr <marcorr@google.com>
Content-Type: text/plain; charset="UTF-8"
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Allowing an unlimited number of MSRs to be specified via the VMX
load/store MSR lists (e.g., vm-entry MSR load list) is bad for two
reasons. First, a guest can specify an unreasonable number of MSRs,
forcing KVM to process all of them in software. Second, the SDM bounds
the number of MSRs allowed to be packed into the atomic switch MSR lists.
Quoting the appendix chapter, titled "MISCELLANEOUS DATA":

"Bits 27:25 is used to compute the recommended maximum number of MSRs
that should appear in the VM-exit MSR-store list, the VM-exit MSR-load
list, or the VM-entry MSR-load list. Specifically, if the value bits
27:25 of IA32_VMX_MISC is N, then 512 * (N + 1) is the recommended
maximum number of MSRs to be included in each list. If the limit is
exceeded, undefined processor behavior may result (including a machine
check during the VMX transition)."

Thus, force a VM-entry to fail due to MSR loading when the MSR load
list is too large. Similarly, trigger an abort during a VM exit that
encounters an MSR load list or MSR store list that is too large.

Test these new checks with the kvm-unit-test "x86: nvmx: test max atomic
switch MSRs".

Suggested-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
Signed-off-by: Marc Orr <marcorr@google.com>
---
 arch/x86/include/asm/vmx.h |  1 +
 arch/x86/kvm/vmx/nested.c  | 19 +++++++++++++++++++
 2 files changed, 20 insertions(+)

```
#### [PATCH] KVM: s390: Do not leak kernel stack data in the KVM_S390_INTERRUPT ioctl
##### From: Thomas Huth <thuth@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Huth <thuth@redhat.com>
X-Patchwork-Id: 11142597
Return-Path: <SRS0=ujOk=XH=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 201CE924
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Sep 2019 09:01:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 06CB0208E4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Sep 2019 09:01:07 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730454AbfILJBD (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 12 Sep 2019 05:01:03 -0400
Received: from mx1.redhat.com ([209.132.183.28]:47556 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726159AbfILJBD (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 12 Sep 2019 05:01:03 -0400
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 137FDC053FDF;
        Thu, 12 Sep 2019 09:01:03 +0000 (UTC)
Received: from thuth.com (ovpn-204-41.brq.redhat.com [10.40.204.41])
        by smtp.corp.redhat.com (Postfix) with ESMTP id A00AB60C63;
        Thu, 12 Sep 2019 09:00:55 +0000 (UTC)
From: Thomas Huth <thuth@redhat.com>
To: Christian Borntraeger <borntraeger@de.ibm.com>,
        Janosch Frank <frankja@linux.ibm.com>, kvm@vger.kernel.org
Cc: David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>, linux-s390@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: s390: Do not leak kernel stack data in the
 KVM_S390_INTERRUPT ioctl
Date: Thu, 12 Sep 2019 11:00:50 +0200
Message-Id: <20190912090050.20295-1-thuth@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.5.16 (mx1.redhat.com [10.5.110.32]);
 Thu, 12 Sep 2019 09:01:03 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When the userspace program runs the KVM_S390_INTERRUPT ioctl to inject
an interrupt, we convert them from the legacy struct kvm_s390_interrupt
to the new struct kvm_s390_irq via the s390int_to_s390irq() function.
However, this function does not take care of all types of interrupts
that we can inject into the guest later (see do_inject_vcpu()). Since we
do not clear out the s390irq values before calling s390int_to_s390irq(),
there is a chance that we copy unwanted data from the kernel stack
into the guest memory later if the interrupt data has not been properly
initialized by s390int_to_s390irq().

Specifically, the problem exists with the KVM_S390_INT_PFAULT_INIT
interrupt: s390int_to_s390irq() does not handle it, but the function
__deliver_pfault_init() will later copy the uninitialized stack data
from the ext.ext_params2 into the guest memory.

Fix it by handling that interrupt type in s390int_to_s390irq(), too.
And while we're at it, make sure that s390int_to_s390irq() now
directly returns -EINVAL for unknown interrupt types, so that we
do not run into this problem again in case we add more interrupt
types to do_inject_vcpu() sometime in the future.

Signed-off-by: Thomas Huth <thuth@redhat.com>
Reviewed-by: Christian Borntraeger <borntraeger@de.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
---
 arch/s390/kvm/interrupt.c | 10 ++++++++++
 1 file changed, 10 insertions(+)

```
#### [PATCH] KVM: s390: Remove unused parameter from __inject_sigp_restart()
##### From: Thomas Huth <thuth@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Huth <thuth@redhat.com>
X-Patchwork-Id: 11142415
Return-Path: <SRS0=ujOk=XH=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C7D4514ED
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Sep 2019 07:03:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B061E21479
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Sep 2019 07:03:04 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729775AbfILHDB (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 12 Sep 2019 03:03:01 -0400
Received: from mx1.redhat.com ([209.132.183.28]:41922 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725940AbfILHDB (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 12 Sep 2019 03:03:01 -0400
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 37065C057EC0;
        Thu, 12 Sep 2019 07:03:01 +0000 (UTC)
Received: from thuth.com (ovpn-204-41.brq.redhat.com [10.40.204.41])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 11D7B5D6A5;
        Thu, 12 Sep 2019 07:02:55 +0000 (UTC)
From: Thomas Huth <thuth@redhat.com>
To: Christian Borntraeger <borntraeger@de.ibm.com>,
        Janosch Frank <frankja@linux.ibm.com>, kvm@vger.kernel.org
Cc: David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>, linux-s390@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: s390: Remove unused parameter from
 __inject_sigp_restart()
Date: Thu, 12 Sep 2019 09:02:50 +0200
Message-Id: <20190912070250.15131-1-thuth@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.5.16 (mx1.redhat.com [10.5.110.32]);
 Thu, 12 Sep 2019 07:03:01 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

It's not required, so drop it to make it clear that this interrupt
does not have any extra parameters.

Signed-off-by: Thomas Huth <thuth@redhat.com>
Reviewed-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
---
 arch/s390/kvm/interrupt.c | 5 ++---
 1 file changed, 2 insertions(+), 3 deletions(-)

```
#### [kvm-unit-tests PATCH] x86: nvmx: test max atomic switch MSRsFrom: Marc Orr <marcorr@google.com>
##### From: Marc Orr <marcorr@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Orr <marcorr@google.com>
X-Patchwork-Id: 11143629
Return-Path: <SRS0=ujOk=XH=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3D80E14ED
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Sep 2019 18:09:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1EBDA2084F
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Sep 2019 18:09:35 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="OAm4MKRj"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726908AbfILSJe (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 12 Sep 2019 14:09:34 -0400
Received: from mail-pf1-f201.google.com ([209.85.210.201]:52100 "EHLO
        mail-pf1-f201.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726894AbfILSJd (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 12 Sep 2019 14:09:33 -0400
Received: by mail-pf1-f201.google.com with SMTP id s137so4115914pfs.18
        for <kvm@vger.kernel.org>; Thu, 12 Sep 2019 11:09:32 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=rNlLuoXt847xgTY50/lD1HH4VbuMAi2bpwf2u9Y9kp4=;
        b=OAm4MKRjiy+QjqIJoQMW4ioVuY8A3qr8+5OZ8r++JZ1QaKXBRQNpL4JRD4Fz/fREXS
         hzSnH9edUGnOVQPCPHhaM06l70l/FXKlEQLEXPsBngQc+q+iXcdAWJUwSww2dQmtqAg7
         U0zxvfgTH5buPMEX6RfEUJg+sJDzlR2ygk6EXvmZ8iRmyAlcbcUo6FZJe/Ta+8uep4CQ
         WMDsKkvWF6D0l64WtrjzevAYmuF+ssy0fNpUJ5lJNlB+FJpOAkcWAdVN2XAOdK/+zKrv
         eWHUwymaesmcOkTQYerdP+USIlTEt/P+XG9EQwcePkgK8Z68m+WCkIekhKlVoTiEO1yV
         oBSQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=rNlLuoXt847xgTY50/lD1HH4VbuMAi2bpwf2u9Y9kp4=;
        b=ixfbKjBr9H34Y7JXdfKTaWqWv05jzceD6d4a0CAtzhNzJL9Ahq1nc5VkyHUS/RrgcN
         LiAWv/3JdtBFlXyG3qECs0TpPmoZMK8UIPGK/17zjbYWr4tRTvEmuJ8fDseGaAXJfijj
         czsJMYTjJMyIzHs4c8N2SQMKB9zIyB23UJnjHolLUJh6ZlHjeEtMd89isUZLPwYCeLQ4
         Jg3Yt7N2xxw7+q0MxPgisylSv7MSIajVa8EHh1MasjyC+LXylsLvVKZG7Nf1b6wEKahC
         ThHqePdgT9dDm0asv2QTOXd1212Jv8A61ku2S+W2GsHGm2xbNc2oOcsJXshERaDuuLMY
         oHjw==
X-Gm-Message-State: APjAAAXuwzQCHnyAj5eyGq+kxsxcYGXwz/Ij/zkAG1mlL4qHWjQj0dA0
        BHyuwTBdZNICb2+caZulaqQJKEgfMb9aPhZn20HjWDsrA/gz0rLfmXOg3UHVseM6VDbQvDzRRTG
        hCJ7GadX5sMXRmjhWgDZS9k8s56G+FabDhILrPxsFoGgSrN/tqNpL83Gth/Tm
X-Google-Smtp-Source: 
 APXvYqzvdawDQzUEnhgq2cknt6tQkqep9UAh99cabGlZ+VFfoOPOM/M3fY24RuaFI4vYifL1pMPQox8in0Ww
X-Received: by 2002:a63:546:: with SMTP id 67mr2894546pgf.429.1568311772187;
 Thu, 12 Sep 2019 11:09:32 -0700 (PDT)
Date: Thu, 12 Sep 2019 11:09:28 -0700
Message-Id: <20190912180928.123660-1-marcorr@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.23.0.237.gc6a4ce50a0-goog
Subject: [kvm-unit-tests PATCH] x86: nvmx: test max atomic switch MSRs
From: Marc Orr <marcorr@google.com>
To: kvm@vger.kernel.org, jmattson@google.com, pshier@google.com
Cc: Marc Orr <marcorr@google.com>
Content-Type: text/plain; charset="UTF-8"
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Excerise nested VMX's atomic MSR switch code (e.g., VM-entry MSR-load
list) at the maximum number of MSRs supported, as described in the SDM,
in the appendix chapter titled "MISCELLANEOUS DATA".

Suggested-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
Signed-off-by: Marc Orr <marcorr@google.com>
---
 x86/vmx_tests.c | 139 ++++++++++++++++++++++++++++++++++++++++++++++++
 1 file changed, 139 insertions(+)

```
#### [PATCH] kvm: x86: Add "significant index" flag to a few CPUID leavesFrom: Jim Mattson <jmattson@google.com>
##### From: Jim Mattson <jmattson@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jim Mattson <jmattson@google.com>
X-Patchwork-Id: 11143405
Return-Path: <SRS0=ujOk=XH=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2251E912
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Sep 2019 16:55:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E9C002081B
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Sep 2019 16:55:09 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="qy/eiIN8"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730547AbfILQzJ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 12 Sep 2019 12:55:09 -0400
Received: from mail-ua1-f74.google.com ([209.85.222.74]:40277 "EHLO
        mail-ua1-f74.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729855AbfILQzI (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 12 Sep 2019 12:55:08 -0400
Received: by mail-ua1-f74.google.com with SMTP id i15so5030909uak.7
        for <kvm@vger.kernel.org>; Thu, 12 Sep 2019 09:55:08 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=WGsN+0gnskfgmbT2Sq3qhm+zIRmQlrdOfG0pAfSyggA=;
        b=qy/eiIN8wnwN7m9OlWHDf1YGIOAWBPmtMkYywYLLYnKjc70RfNx4GGmlzWX4sfvoHk
         3jwcf88ZHCvu/6BEt3nSgzyX+D68Ig5vslzDYINTyJbHprpYIteGNlSLFErZvyma4GnW
         gz9+MgukeLA2OgvCHxvXluQHBAs6tSdie3QrFbTtlzX1I2qgWhOqtfhS5xVRRY3A+phe
         xbgAKv4JUMFdJojX3m2dnuXfZMPcPnwUUN2V1FgBM9jDHJ2MW1q15izmkZCjw7d9sgM2
         CF3W8jKQSP32TtKY3ii84mgdZdR4nflqY8J6ZzwFf/Ech8wMTFNP10IBZJiD/wW5A5ni
         0qZQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=WGsN+0gnskfgmbT2Sq3qhm+zIRmQlrdOfG0pAfSyggA=;
        b=lnWg5AlON47e+5RNCPo0peyMLhGVQ9hMHs5gGCp/sNFCwzJLsuyVY+vpvCje/3W3fN
         R68cjPXKbH5cPH9Tenlah+t5UapaviyK7v29iusGFVjSxpfp+4IwmDV5WoqD+uXGzpJ0
         xgZbVQ43qbtb8gOae1y6O877EgWCXZ1dyR5el9ULK2DqhV5KaUeA+i3Zr3J5TYF7T1CB
         rgSa+RuOjmkwkh0Fi1+iXIHyhCnxn/K6bKbqyZpZ3HL1OJRfToWMhRMY+HT+/CsZ7ivk
         Ur65KnXdBKls0nIs0LEfss7yprURQC11gd4cetBIGaYKk6FPG+RNKxPIUWFVH5uzGKqX
         +usQ==
X-Gm-Message-State: APjAAAULhA6VqnlZpFq5puhiKGiTUuk4kZBCNjPhPJZv2iTEFI1tx06J
        JCKp7Zv6L6ciRwSCt99aoqZ4Rom0mzyrwlvp8pw8fOZFt3CKRUslN/+jWo3m8Ifn5mXd53sVUXg
        UR1ELCSXijHYFz3qJzZBvncBJVczyrqS3QJ7y7+TJVmWjCVPhg3Uwaj8MJCjsUCE=
X-Google-Smtp-Source: 
 APXvYqxQ22ZGZXSY39xHw5bdGaja4waKjNK6QSqGVzMaeTb+CdAPVn+XgVJlHf6EIMIicgFomsa9GdaVIMjIxw==
X-Received: by 2002:a67:1a41:: with SMTP id a62mr24910467vsa.54.1568307307516;
 Thu, 12 Sep 2019 09:55:07 -0700 (PDT)
Date: Thu, 12 Sep 2019 09:55:03 -0700
Message-Id: <20190912165503.190905-1-jmattson@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.23.0.237.gc6a4ce50a0-goog
Subject: [PATCH] kvm: x86: Add "significant index" flag to a few CPUID leaves
From: Jim Mattson <jmattson@google.com>
To: kvm@vger.kernel.org
Cc: Jim Mattson <jmattson@google.com>, Peter Shier <pshier@google.com>,
        Steve Rutherford <srutherford@google.com>
Content-Type: text/plain; charset="UTF-8"
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

According to the Intel SDM, volume 2, "CPUID," the index is
significant (or partially significant) for CPUID leaves 0FH, 10H, 12H,
17H, 18H, and 1FH.

Add the corresponding flag to these CPUID leaves in do_host_cpuid().

Signed-off-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
Reviewed-by: Steve Rutherford <srutherford@google.com>
Fixes: a87f2d3a6eadab ("KVM: x86: Add Intel CPUID.1F cpuid emulation support")
Reviewed-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 arch/x86/kvm/cpuid.c | 6 ++++++
 1 file changed, 6 insertions(+)

```
#### [PATCH] KVM: x86: work around leak of uninitialized stack contents
##### From: Fuqian Huang <huangfq.daxian@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Fuqian Huang <huangfq.daxian@gmail.com>
X-Patchwork-Id: 11142243
Return-Path: <SRS0=ujOk=XH=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 00360912
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Sep 2019 04:18:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id C86D821A4C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Sep 2019 04:18:51 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="EKPvBwH1"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726277AbfILESf (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 12 Sep 2019 00:18:35 -0400
Received: from mail-pf1-f195.google.com ([209.85.210.195]:46384 "EHLO
        mail-pf1-f195.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725792AbfILESf (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 12 Sep 2019 00:18:35 -0400
Received: by mail-pf1-f195.google.com with SMTP id q5so15061736pfg.13;
        Wed, 11 Sep 2019 21:18:33 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=E78vnhmo9W2A2pNvQXFwnY+byAZLb8i8u9HyT6B3+sg=;
        b=EKPvBwH1+59k/jwqQdsSvQbO8k61IoR8he06AzVrsrO2S4NsaDCQj+9qXT4ifH95cA
         lStBOgUpKwZfOPXfuGwErlIXnIf/aTghhPz2KtzOPfGKEYQdagLqeEl2SZblxyZyEi/y
         RJmZb3iNgY5moYjUmvTiBw3ZeH3iD7braVQTDPznhRRcb9erM3N58YcaRlFwdlouj1A2
         nJpUVWNaCxbcbyJWc6HBs9Jeixb6LN2WjIFQpokWLIC8jXxd94OX+rP07KyEyZnZzUTU
         P0isEghZmhMU+1GBOygU1Ty4hoKqkfrs8qNbn2bEAlyYpWY7+Ir7lKSzpd48ghOnlA/d
         IbgQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=E78vnhmo9W2A2pNvQXFwnY+byAZLb8i8u9HyT6B3+sg=;
        b=LKJC7ut/fOCK9o2wG2ZuE0up0ZA/W8MZX9TkzdvrM6F6WVnBfapnQtinooxfjDvS/E
         V//8Xw/Ulwh1mBTNckhy/Zp2vXyDLqYlzz7skOuTOk9vkXLHi+gBvQsKjTFnA5SOHX6L
         4n0zBEYm7H24ojvjyj2q/joyj7XBlIQRf61myF/0NR8VfbcyfHOIS5lhzomtGhR/ExI6
         4A9xbgHFryY7ngwZFHl4GmjI4CGRM9NMWauMOusBebNFfmNVJfJtst0mBHVennKcqNgz
         DWbZ9JQh+K6qsOj2u5TmGDaIKsJltmfohMYGfeKXzpOUObxNbMZ+7MLpmq+q2CZdO2qg
         cOQg==
X-Gm-Message-State: APjAAAXJ1tbxikzCrgfG8zFY6y0aS2r7+2VVLm/DzyZblKU5PLr38DBE
        /eBE9yrc9HtPoieK/A88ebs=
X-Google-Smtp-Source: 
 APXvYqyk0x3J7D47e/P7P1oHEyTuMa/9I5ZW1O1HwuHLoVPHoU1p0ru3RMmYDsIaqnjqk5a/E1hmow==
X-Received: by 2002:a63:fa11:: with SMTP id
 y17mr36421144pgh.267.1568261913071;
        Wed, 11 Sep 2019 21:18:33 -0700 (PDT)
Received: from hfq-skylake.ipads-lab.se.sjtu.edu.cn ([202.120.40.82])
        by smtp.googlemail.com with ESMTPSA id
 s4sm24278875pfh.15.2019.09.11.21.18.26
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Wed, 11 Sep 2019 21:18:32 -0700 (PDT)
From: Fuqian Huang <huangfq.daxian@gmail.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Sean Christopherson <sean.j.christopherson@intel.com>,
 Vitaly Kuznetsov <vkuznets@redhat.com>, Wanpeng Li <wanpengli@tencent.com>,
 Jim Mattson <jmattson@google.com>, Joerg Roedel <joro@8bytes.org>,
 Thomas Gleixner <tglx@linutronix.de>, Ingo Molnar <mingo@redhat.com>,
 Borislav Petkov <bp@alien8.de>, "H . Peter Anvin" <hpa@zytor.com>,
 x86@kernel.org, kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
 Fuqian Huang <huangfq.daxian@gmail.com>
Subject: [PATCH] KVM: x86: work around leak of uninitialized stack contents
Date: Thu, 12 Sep 2019 12:18:17 +0800
Message-Id: <20190912041817.23984-1-huangfq.daxian@gmail.com>
X-Mailer: git-send-email 2.11.0
To: unlisted-recipients:; (no To-header on input)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Emulation of VMPTRST can incorrectly inject a page fault
when passed an operand that points to an MMIO address.
The page fault will use uninitialized kernel stack memory
as the CR2 and error code.

The right behavior would be to abort the VM with a KVM_EXIT_INTERNAL_ERROR
exit to userspace; however, it is not an easy fix, so for now just ensure
that the error code and CR2 are zero.

Signed-off-by: Fuqian Huang <huangfq.daxian@gmail.com>
---
 arch/x86/kvm/x86.c | 1 +
 1 file changed, 1 insertion(+)

```
#### [RFC PATCH 1/2] mdev: device id support
##### From: Jason Wang <jasowang@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 11142671
Return-Path: <SRS0=ujOk=XH=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7332F16B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Sep 2019 09:40:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 48381214D8
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Sep 2019 09:40:56 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730851AbfILJkx (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 12 Sep 2019 05:40:53 -0400
Received: from mx1.redhat.com ([209.132.183.28]:40356 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1730597AbfILJkw (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 12 Sep 2019 05:40:52 -0400
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 782F030860CB;
        Thu, 12 Sep 2019 09:40:51 +0000 (UTC)
Received: from jason-ThinkPad-X1-Carbon-6th.redhat.com
 (ovpn-12-89.pek2.redhat.com [10.72.12.89])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 31D6B60852;
        Thu, 12 Sep 2019 09:40:31 +0000 (UTC)
From: Jason Wang <jasowang@redhat.com>
To: kvm@vger.kernel.org, linux-s390@vger.kernel.org,
        linux-kernel@vger.kernel.org, dri-devel@lists.freedesktop.org,
        intel-gfx@lists.freedesktop.org,
        intel-gvt-dev@lists.freedesktop.org, kwankhede@nvidia.com,
        alex.williamson@redhat.com
Cc: mst@redhat.com, zhenyuw@linux.intel.com, zhi.a.wang@intel.com,
        jani.nikula@linux.intel.com, joonas.lahtinen@linux.intel.com,
        rodrigo.vivi@intel.com, airlied@linux.ie, daniel@ffwll.ch,
        cohuck@redhat.com, farman@linux.ibm.com, pasic@linux.ibm.com,
        sebott@linux.ibm.com, oberpar@linux.ibm.com,
        heiko.carstens@de.ibm.com, gor@linux.ibm.com,
        borntraeger@de.ibm.com, akrowiak@linux.ibm.com,
        pmorel@linux.ibm.com, freude@linux.ibm.com, tiwei.bie@intel.com,
        virtualization@lists.linux-foundation.org,
        maxime.coquelin@redhat.com, cunming.liang@intel.com,
        zhihong.wang@intel.com, rob.miller@broadcom.com, idos@mellanox.com,
        xiao.w.wang@intel.com, lingshan.zhu@intel.com,
        Jason Wang <jasowang@redhat.com>
Subject: [RFC PATCH 1/2] mdev: device id support
Date: Thu, 12 Sep 2019 17:40:11 +0800
Message-Id: <20190912094012.29653-2-jasowang@redhat.com>
In-Reply-To: <20190912094012.29653-1-jasowang@redhat.com>
References: <20190912094012.29653-1-jasowang@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.5.16 (mx1.redhat.com [10.5.110.44]);
 Thu, 12 Sep 2019 09:40:51 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Mdev bus only support vfio driver right now, so it doesn't implement
match method. But in the future, we may add drivers other than vfio,
one example is virtio-mdev[1] driver. This means we need to add device
id support in bus match method to pair the mdev device and mdev driver
correctly.

So this patch add id_table to mdev_driver and id for mdev parent, and
implement the match method for mdev bus.

[1] https://lkml.org/lkml/2019/9/10/135

Signed-off-by: Jason Wang <jasowang@redhat.com>
---
 drivers/gpu/drm/i915/gvt/kvmgt.c  |  2 +-
 drivers/s390/cio/vfio_ccw_ops.c   |  2 +-
 drivers/s390/crypto/vfio_ap_ops.c |  3 ++-
 drivers/vfio/mdev/mdev_core.c     | 14 ++++++++++++--
 drivers/vfio/mdev/mdev_driver.c   | 14 ++++++++++++++
 drivers/vfio/mdev/mdev_private.h  |  1 +
 drivers/vfio/mdev/vfio_mdev.c     |  6 ++++++
 include/linux/mdev.h              |  6 +++++-
 include/linux/mod_devicetable.h   |  6 ++++++
 samples/vfio-mdev/mbochs.c        |  2 +-
 samples/vfio-mdev/mdpy.c          |  2 +-
 samples/vfio-mdev/mtty.c          |  2 +-
 12 files changed, 51 insertions(+), 9 deletions(-)

```
#### [PATCH v2] KVM: s390: Do not leak kernel stack data in the KVM_S390_INTERRUPT ioctl
##### From: Thomas Huth <thuth@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Huth <thuth@redhat.com>
X-Patchwork-Id: 11142919
Return-Path: <SRS0=ujOk=XH=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EFE53912
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Sep 2019 11:54:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D5EAF2081B
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Sep 2019 11:54:49 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731477AbfILLyt (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 12 Sep 2019 07:54:49 -0400
Received: from mx1.redhat.com ([209.132.183.28]:52622 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1731466AbfILLyt (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 12 Sep 2019 07:54:49 -0400
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id C13EA30860D5;
        Thu, 12 Sep 2019 11:54:48 +0000 (UTC)
Received: from thuth.com (ovpn-204-41.brq.redhat.com [10.40.204.41])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 20AD75D713;
        Thu, 12 Sep 2019 11:54:42 +0000 (UTC)
From: Thomas Huth <thuth@redhat.com>
To: Christian Borntraeger <borntraeger@de.ibm.com>,
        Janosch Frank <frankja@linux.ibm.com>, kvm@vger.kernel.org
Cc: David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>, linux-s390@vger.kernel.org,
        linux-kernel@vger.kernel.org, stable@vger.kernel.org
Subject: [PATCH v2] KVM: s390: Do not leak kernel stack data in the
 KVM_S390_INTERRUPT ioctl
Date: Thu, 12 Sep 2019 13:54:38 +0200
Message-Id: <20190912115438.25761-1-thuth@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.5.16 (mx1.redhat.com [10.5.110.44]);
 Thu, 12 Sep 2019 11:54:48 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When the userspace program runs the KVM_S390_INTERRUPT ioctl to inject
an interrupt, we convert them from the legacy struct kvm_s390_interrupt
to the new struct kvm_s390_irq via the s390int_to_s390irq() function.
However, this function does not take care of all types of interrupts
that we can inject into the guest later (see do_inject_vcpu()). Since we
do not clear out the s390irq values before calling s390int_to_s390irq(),
there is a chance that we copy random data from the kernel stack which
could be leaked to the userspace later.

Specifically, the problem exists with the KVM_S390_INT_PFAULT_INIT
interrupt: s390int_to_s390irq() does not handle it, and the function
__inject_pfault_init() later copies irq->u.ext which contains the
random kernel stack data. This data can then be leaked either to
the guest memory in __deliver_pfault_init(), or the userspace might
retrieve it directly with the KVM_S390_GET_IRQ_STATE ioctl.

Fix it by handling that interrupt type in s390int_to_s390irq(), too,
and by making sure that the s390irq struct is properly pre-initialized.
And while we're at it, make sure that s390int_to_s390irq() now
directly returns -EINVAL for unknown interrupt types, so that we
immediately get a proper error code in case we add more interrupt
types to do_inject_vcpu() without updating s390int_to_s390irq()
sometime in the future.

Cc: stable@vger.kernel.org
Reviewed-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Christian Borntraeger <borntraeger@de.ibm.com>
Signed-off-by: Thomas Huth <thuth@redhat.com>
Reviewed-by: Janosch Frank <frankja@linux.ibm.com>
---
 arch/s390/kvm/interrupt.c | 10 ++++++++++
 arch/s390/kvm/kvm-s390.c  |  2 +-
 2 files changed, 11 insertions(+), 1 deletion(-)

```
#### [PATCH] x86: remove memory constraint from "mov" instructionFrom: Bill Wendling <morbo@google.com>
##### From: Bill Wendling <morbo@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Bill Wendling <morbo@google.com>
X-Patchwork-Id: 11143777
Return-Path: <SRS0=ujOk=XH=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B6C22924
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Sep 2019 21:00:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 8512A2084D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Sep 2019 21:00:08 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="XaBCzTB7"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728141AbfILVAH (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 12 Sep 2019 17:00:07 -0400
Received: from mail-pg1-f202.google.com ([209.85.215.202]:43904 "EHLO
        mail-pg1-f202.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726308AbfILVAH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 12 Sep 2019 17:00:07 -0400
Received: by mail-pg1-f202.google.com with SMTP id z35so15492145pgk.10
        for <kvm@vger.kernel.org>; Thu, 12 Sep 2019 14:00:07 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=KEnCjWSN0RCUKFn6Yi+r4JQOxCeOZvptNzKeCzkkya8=;
        b=XaBCzTB7Cg4gcPNf/BRm1CP5zmDjRJF8/2uuZ8WqCdcZ6APofH7Rdq4roiQR+wNfym
         sOP89AlcBgks14wWHUhZWB873NOASm1fIBxHHuQ7aWd5fF6fmpdSodQXfldKvYF5Jtpd
         fQV7MeWRHcEEU1J9PLoC2O3jkqJiLzz4W1MoPCRLyOHN9+kkW7WhdCz8k+KRX/87sZ1Z
         k0DYzpPFtDY5094GAz2FxKArXewwu7YYz4AW+4setCAxjHbMZBgVNJ751ZTf/QC9aoFE
         l70jNB7rCLlee5RyQoMmD5K7FyVD7npk8JncbyMlF5FnRbqCrYFgKXYShfOYt/+qbOFP
         MVEA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=KEnCjWSN0RCUKFn6Yi+r4JQOxCeOZvptNzKeCzkkya8=;
        b=nXaRC+eyFYNAxqKV9sCXWFGkB5JR2EizjifxDJR/2qKTavYCfd7YgpcFrjizy5QkZD
         UTP9y84N7yXE+X2/+qfVshktWjGGBUu6RHJ+bpHYb4Khi8IKmBHIFzmsCihijhO+EYVi
         QoQ0M920J0qJzKEO4OfCgfR/4ypfFZd8wv336mk6WBs0TMH+WRY44QwwdqMNPn9Ju4WW
         lR4i3iIW7fFbzyPSleMuCfRXGpx/gWVM4UPcKJ5MVpf3syWXVvgls9ZHdKLcR/sUK+J0
         OA3mJqPHQaCoxqhOpS9h4XerN3cbFEt9Bl7ZGUROjDM4GV3/463RkGmHcbvk5AdgaoKa
         29gw==
X-Gm-Message-State: APjAAAV65PTBAlPED11r0Bt1Xh/ZdDCBBmLpjL8ucjoQItJBllfB6TIS
        SDHCBz+XKUNbv5po9QmgJ9qwF1j2JNEzlE3p8jFYQe0bLRUV82yEjx9gh0LEm0b9QSi9IHBPIIc
        k1BMHJ1g0iPK68whY4H6sHUAA6myrKSMLiTaxDsRefAhkLf4sNGlobw==
X-Google-Smtp-Source: 
 APXvYqwyYgXVin35pBIYe1ELFKzmpN+CzIJcAcpFD17naVTg385Tt6qCR03TR3nScpyfJQu9N4S4yvbXkQ==
X-Received: by 2002:a65:6256:: with SMTP id
 q22mr40025673pgv.408.1568322006020;
 Thu, 12 Sep 2019 14:00:06 -0700 (PDT)
Date: Thu, 12 Sep 2019 13:59:44 -0700
In-Reply-To: 
 <CAGG=3QXxGVs-s0H2Emw1tYMtcGtQsEHrYnmHztL=vOFanZegMw@mail.gmail.com>
Message-Id: <20190912205944.120303-1-morbo@google.com>
Mime-Version: 1.0
References: 
 <CAGG=3QXxGVs-s0H2Emw1tYMtcGtQsEHrYnmHztL=vOFanZegMw@mail.gmail.com>
X-Mailer: git-send-email 2.23.0.237.gc6a4ce50a0-goog
Subject: [PATCH] x86: remove memory constraint from "mov" instruction
From: Bill Wendling <morbo@google.com>
To: kvm@vger.kernel.org
Cc: sean.j.christopherson@intel.com, Bill Wendling <morbo@google.com>
Content-Type: text/plain; charset="UTF-8"
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Remove a bogus memory constraint as x86 does not have a generic
memory-to-memory "mov" instruction.

Signed-off-by: Bill Wendling <morbo@google.com>
---
 lib/x86/desc.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
