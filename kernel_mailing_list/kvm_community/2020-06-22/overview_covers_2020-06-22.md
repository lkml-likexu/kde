

#### [PATCH v2 0/5] KVM/arm64: Enable PtrAuth on non-VHE KVM
##### From: Marc Zyngier <maz@kernel.org>
X-SA-Exim-Mail-From: maz@kernel.org

```c
From patchwork Mon Jun 22 08:06:38 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11617167
Return-Path: <SRS0=pCMg=AD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6AD3292A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 22 Jun 2020 08:06:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4E131208B8
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 22 Jun 2020 08:06:55 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1592813215;
	bh=Ii14i7vMt5G0blEY8jOOtv2hk5ArajPnLztxOTdDv4o=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=I/kJWUjb/kytjcHrH7xoJVA09SOW4T7gBuze7PLxU4FZ4XYStxEsLZWoRTmqMa7TS
	 PDQNIBUCroUKc3SqdRJaI4/OypcnFgpQ1hV6GA7NhuQ+4P4GrtjVvdWVFStbwXL2sQ
	 VIr4xYNmHkqXMzh3F2uHOUp5xMK/51fG0nz0HrVs=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725883AbgFVIGy (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 22 Jun 2020 04:06:54 -0400
Received: from mail.kernel.org ([198.145.29.99]:42044 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725793AbgFVIGx (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 22 Jun 2020 04:06:53 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 1D60E207C3;
        Mon, 22 Jun 2020 08:06:53 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1592813213;
        bh=Ii14i7vMt5G0blEY8jOOtv2hk5ArajPnLztxOTdDv4o=;
        h=From:To:Cc:Subject:Date:From;
        b=tofBpQcybBeOKxwi8eoUa+ScRMUGCbQlt4sgu/nO4mJqbCzrEuGE1DgnIgIYns6VG
         Y+7ifpP6U5+arBiWpI32ti/Y2LlZa6Ve+oiwtHz2lO/zCvssW41I0leGdPqyVobmom
         2SP3RE7P4Ucv/BmtBeQRSRMIN7daLpqlPS2cOpGQ=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1jnHTf-005FG8-Br; Mon, 22 Jun 2020 09:06:51 +0100
From: Marc Zyngier <maz@kernel.org>
To: kvm@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
        kvmarm@lists.cs.columbia.edu
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Mark Rutland <mark.rutland@arm.com>,
        Andrew Scull <ascull@google.com>,
        Dave Martin <Dave.Martin@arm.com>, kernel-team@android.com
Subject: [PATCH v2 0/5] KVM/arm64: Enable PtrAuth on non-VHE KVM
Date: Mon, 22 Jun 2020 09:06:38 +0100
Message-Id: <20200622080643.171651-1-maz@kernel.org>
X-Mailer: git-send-email 2.27.0
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: kvm@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com, mark.rutland@arm.com,
 ascull@google.com, Dave.Martin@arm.com, kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Not having PtrAuth on non-VHE KVM (for whatever reason VHE is not
enabled on a v8.3 system) has always looked like an oddity. This
trivial series remedies it, and allows a non-VHE KVM to offer PtrAuth
to its guests.

In the tradition of not having separate security between host-EL1 and
EL2, EL2 reuses the keys set up by host-EL1. It is likely that, should
we switch to a mode where EL2 is more distrusting of EL1, we'd have
private keys there.

The last two patches are respectively an optimization when
save/restoring the PtrAuth context, and a cleanup of the alternatives
used by that same save/restore code.

* From v1 [1]:
  - Move the hand-crafted literal load to using a mov_q macro (Andrew, Mark)
  - Added a cleanup of the alternatives on the save/restore path (Mark)

[1] https://lore.kernel.org/kvm/20200615081954.6233-1-maz@kernel.org/

Marc Zyngier (5):
  KVM: arm64: Enable Address Authentication at EL2 if available
  KVM: arm64: Allow ARM64_PTR_AUTH when ARM64_VHE=n
  KVM: arm64: Allow PtrAuth to be enabled from userspace on non-VHE
    systems
  KVM: arm64: Check HCR_EL2 instead of shadow copy to swap PtrAuth
    registers
  KVM: arm64: Simplify PtrAuth alternative patching

 arch/arm64/Kconfig                   |  4 +---
 arch/arm64/include/asm/kvm_ptrauth.h | 30 ++++++++++------------------
 arch/arm64/kvm/hyp-init.S            |  5 +++++
 arch/arm64/kvm/reset.c               | 21 ++++++++++---------
 4 files changed, 27 insertions(+), 33 deletions(-)
```
#### [PATCH v9 0/2] Use DIAG318 to set Control Program Name & Version
##### From: Collin Walling <walling@linux.ibm.com>

```c
From patchwork Mon Jun 22 15:46:34 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Collin Walling <walling@linux.ibm.com>
X-Patchwork-Id: 11618301
Return-Path: <SRS0=pCMg=AD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7319660D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 22 Jun 2020 15:46:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5DCA22074D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 22 Jun 2020 15:46:54 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729462AbgFVPqx (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 22 Jun 2020 11:46:53 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:65326 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1729196AbgFVPqw (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 22 Jun 2020 11:46:52 -0400
Received: from pps.filterd (m0098394.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 05MFXkc1062606;
        Mon, 22 Jun 2020 11:46:52 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 31sey6jwrr-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 22 Jun 2020 11:46:52 -0400
Received: from m0098394.ppops.net (m0098394.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 05MFY0LQ064035;
        Mon, 22 Jun 2020 11:46:51 -0400
Received: from ppma01dal.us.ibm.com (83.d6.3fa9.ip4.static.sl-reverse.com
 [169.63.214.131])
        by mx0a-001b2d01.pphosted.com with ESMTP id 31sey6jwre-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 22 Jun 2020 11:46:51 -0400
Received: from pps.filterd (ppma01dal.us.ibm.com [127.0.0.1])
        by ppma01dal.us.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 05MFZYvo030858;
        Mon, 22 Jun 2020 15:46:50 GMT
Received: from b03cxnp07029.gho.boulder.ibm.com
 (b03cxnp07029.gho.boulder.ibm.com [9.17.130.16])
        by ppma01dal.us.ibm.com with ESMTP id 31sa38mtq6-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 22 Jun 2020 15:46:50 +0000
Received: from b03ledav002.gho.boulder.ibm.com
 (b03ledav002.gho.boulder.ibm.com [9.17.130.233])
        by b03cxnp07029.gho.boulder.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 05MFkkh354264148
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 22 Jun 2020 15:46:46 GMT
Received: from b03ledav002.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 4B34F136055;
        Mon, 22 Jun 2020 15:46:46 +0000 (GMT)
Received: from b03ledav002.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 71E1313604F;
        Mon, 22 Jun 2020 15:46:45 +0000 (GMT)
Received: from localhost.localdomain.com (unknown [9.85.169.243])
        by b03ledav002.gho.boulder.ibm.com (Postfix) with ESMTP;
        Mon, 22 Jun 2020 15:46:45 +0000 (GMT)
From: Collin Walling <walling@linux.ibm.com>
To: kvm@vger.kernel.org, linux-s390@vger.kernel.org
Cc: pbonzini@redhat.com, borntraeger@de.ibm.com, frankja@linux.ibm.com,
        david@redhat.com, cohuck@redhat.com, imbrenda@linux.ibm.com,
        heiko.carstens@de.ibm.com, gor@linux.ibm.com, thuth@redhat.com
Subject: [PATCH v9 0/2] Use DIAG318 to set Control Program Name & Version
 Codes
Date: Mon, 22 Jun 2020 11:46:34 -0400
Message-Id: <20200622154636.5499-1-walling@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.216,18.0.687
 definitions=2020-06-22_09:2020-06-22,2020-06-22 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxlogscore=999 mlxscore=0
 cotscore=-2147483648 phishscore=0 malwarescore=0 spamscore=0 bulkscore=0
 lowpriorityscore=0 impostorscore=0 adultscore=0 suspectscore=0
 priorityscore=1501 clxscore=1015 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-2004280000 definitions=main-2006220116
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Changelog:

    v9

    • No longer unshadowing CPNC in VSIE

    v8

    • Reset is handled in KVM during initial and clear resets
    • Sync/Store register handling
    • Removed device IOCTL code
    • Added KVM Capability for DIAG318
        - this is for determining if the CPU model can enable this feature
    • Reverted changes introduced by bullet 3 in v7
    • Unshadowing CPNC again, as it makes sense if the guest executing in
        VSIE sets a unique name/version code; this data should be preserved
        - reverts bullet 4 in v3 [removed in v9]
    • Diag318 is no longer reported via VM or CPU events
        - no place to put this such that the messages aren't flooding the logs
        - not necessary, as this data is primarily for IBM hardware/firmware
            service events, and is observable via such events (e.g. CPU ring
            dump)
        - was nice for testing purposes
    • A copy of the diag318 info (name & version code) is now stored in
        the kvm_vcpu_arch struct, as opposed to the kvm_arch struct

    v7

    • Removed diag handler, as it will now take place within userspace
    • Removed KVM_S390_VM_MISC_ENABLE_DIAG318 (undoes first bullet in v6)
    • Misc clean ups and fixes [removed in v8]
        - introduced a new patch to s/diag318/diag_318 and s/byte_134/fac134
          to keep things consistent with the rest of the code

    v6

    • KVM disables diag318 get/set by default [removed in v7]
    • added new IOCTL to tell KVM to enable diag318 [removed in v7]
    • removed VCPU event message in favor of VM_EVENT only [removed in v8]

    v5
    
    • s/cpc/diag318_info in order to make the relevant data more clear
    • removed mutex locks for diag318_info get/set

    v4
    
    • removed setup.c changes introduced in bullet 1 of v3
    • kept diag318_info struct cleanup
    • analogous QEMU patches:
        https://lists.gnu.org/archive/html/qemu-devel/2019-05/msg00164.html

    v3
    
    • kernel patch for diag 0x318 instruction call fixup [removed in v4]
    • removed CPU model code
    • cleaned up diag318_info struct
    • cpnc is no longer unshadowed as it was not needed [removed in v8]
    • rebased on 5.1.0-rc3

-------------------------------------------------------------------------------

This instruction call is executed once-and-only-once during Kernel setup.
The availability of this instruction depends on Read Info byte 134 (aka fac134),
bit 0.

DIAG 0x318's is handled by userspace and may be enabled for a guest even if the
host kernel cannot support it.

The diag318_info is composed of a Control Program Name Code (CPNC) and a
Control Program Version Code (CPVC). The CPNC is stored in the SIE block, and
the CPNC & CPVC pair is stored in the kvm_vcpu_arch struct. 

These values are used for problem diagnosis and allows IBM to identify control
program information by answering the following question:

    "What environment is this guest running in?" (CPNC)
    "What are more details regarding the OS?" (CPVC)

In the future, we will implement the CPVC to convey more information about the 
OS (such as Linux version and potentially some value denoting a specific 
distro + release). For now, we set this field to 0 until we come up with a solid 
plan.

Collin Walling (2):
  s390/setup: diag 318: refactor struct
  s390/kvm: diagnose 0x318 sync and reset

 arch/s390/include/asm/diag.h     |  6 ++----
 arch/s390/include/asm/kvm_host.h |  4 +++-
 arch/s390/include/uapi/asm/kvm.h |  5 ++++-
 arch/s390/kernel/setup.c         |  3 +--
 arch/s390/kvm/kvm-s390.c         | 11 ++++++++++-
 arch/s390/kvm/vsie.c             |  1 +
 include/uapi/linux/kvm.h         |  1 +
 7 files changed, 22 insertions(+), 9 deletions(-)
```
#### [kvm-unit-tests PATCH v1 0/8] Minor fixes, improvements,  and cleanup
##### From: Claudio Imbrenda <imbrenda@linux.ibm.com>

```c
From patchwork Mon Jun 22 16:21:33 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Claudio Imbrenda <imbrenda@linux.ibm.com>
X-Patchwork-Id: 11618365
Return-Path: <SRS0=pCMg=AD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DC19160D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 22 Jun 2020 16:21:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CC6E920760
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 22 Jun 2020 16:21:48 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729484AbgFVQVr (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 22 Jun 2020 12:21:47 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:21834 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1729407AbgFVQVr (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 22 Jun 2020 12:21:47 -0400
Received: from pps.filterd (m0098399.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 05MG0gGr017121
        for <kvm@vger.kernel.org>; Mon, 22 Jun 2020 12:21:47 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 31tysprtwk-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT)
        for <kvm@vger.kernel.org>; Mon, 22 Jun 2020 12:21:46 -0400
Received: from m0098399.ppops.net (m0098399.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 05MG1BS5019793
        for <kvm@vger.kernel.org>; Mon, 22 Jun 2020 12:21:46 -0400
Received: from ppma04ams.nl.ibm.com (63.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.99])
        by mx0a-001b2d01.pphosted.com with ESMTP id 31tysprtv4-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 22 Jun 2020 12:21:46 -0400
Received: from pps.filterd (ppma04ams.nl.ibm.com [127.0.0.1])
        by ppma04ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 05MG0LBJ019102;
        Mon, 22 Jun 2020 16:21:44 GMT
Received: from b06cxnps4075.portsmouth.uk.ibm.com
 (d06relay12.portsmouth.uk.ibm.com [9.149.109.197])
        by ppma04ams.nl.ibm.com with ESMTP id 31sa37umsw-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 22 Jun 2020 16:21:43 +0000
Received: from d06av21.portsmouth.uk.ibm.com (d06av21.portsmouth.uk.ibm.com
 [9.149.105.232])
        by b06cxnps4075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 05MGLfhf64749648
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 22 Jun 2020 16:21:41 GMT
Received: from d06av21.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id C491452051;
        Mon, 22 Jun 2020 16:21:41 +0000 (GMT)
Received: from ibm-vm.ibmuc.com (unknown [9.145.9.197])
        by d06av21.portsmouth.uk.ibm.com (Postfix) with ESMTP id 734345204F;
        Mon, 22 Jun 2020 16:21:41 +0000 (GMT)
From: Claudio Imbrenda <imbrenda@linux.ibm.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com
Cc: frankja@linux.ibm.com, thuth@redhat.com, david@redhat.com
Subject: [kvm-unit-tests PATCH v1 0/8] Minor fixes, improvements,  and cleanup
Date: Mon, 22 Jun 2020 18:21:33 +0200
Message-Id: <20200622162141.279716-1-imbrenda@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.216,18.0.687
 definitions=2020-06-22_09:2020-06-22,2020-06-22 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 spamscore=0 malwarescore=0
 mlxlogscore=749 mlxscore=0 lowpriorityscore=0 suspectscore=0 phishscore=0
 clxscore=1015 cotscore=-2147483648 impostorscore=0 adultscore=0
 bulkscore=0 priorityscore=1501 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-2004280000 definitions=main-2006220116
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch series provides a bunch of small improvements, fixes and
cleanups.
Some of these fixes are needed for an upcoming series that will
significantly refactor and improve the memory allocators.

Claudio Imbrenda (8):
  x86/cstart.S: initialize stack before using it
  x86: add missing PAGE_ALIGN macro from page.h
  lib: use PAGE_ALIGN
  lib/alloc.c: add overflow check for calloc
  lib: Fix a typo and add documentation comments
  lib/vmalloc: fix potential race and non-standard pointer arithmetic
  lib/alloc_page: make get_order return unsigned int
  lib/vmalloc: add locking and a check for initialization

 lib/x86/asm/page.h |  2 ++
 lib/alloc_page.h   |  2 +-
 lib/alloc_phys.h   |  2 +-
 lib/vmalloc.h      |  8 ++++++++
 lib/alloc.c        | 36 +++++++++++++++++++++++++++++++++++-
 lib/alloc_page.c   |  2 +-
 lib/vmalloc.c      | 34 +++++++++++++++++++++++-----------
 x86/cstart.S       |  2 +-
 8 files changed, 72 insertions(+), 16 deletions(-)
```
#### [PATCH v4 00/18] Add support for Nitro Enclaves
##### From: Andra Paraschiv <andraprs@amazon.com>

```c
From patchwork Mon Jun 22 20:03:11 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andra Paraschiv <andraprs@amazon.com>
X-Patchwork-Id: 11618861
Return-Path: <SRS0=pCMg=AD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A8CEA138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 22 Jun 2020 20:03:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8B1632076A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 22 Jun 2020 20:03:54 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amazon.com header.i=@amazon.com
 header.b="b4uBcbjS"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728673AbgFVUDv (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 22 Jun 2020 16:03:51 -0400
Received: from smtp-fw-9101.amazon.com ([207.171.184.25]:63405 "EHLO
        smtp-fw-9101.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728435AbgFVUDu (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 22 Jun 2020 16:03:50 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.com; i=@amazon.com; q=dns/txt; s=amazon201209;
  t=1592856228; x=1624392228;
  h=from:to:cc:subject:date:message-id:mime-version:
   content-transfer-encoding;
  bh=EiUt6Oedptz4f3XfYR/pew/AoUF85rOaT6U9ZvC05Jc=;
  b=b4uBcbjSlpaCjz4Efya5+fsfln0Qs+FIg2uVhm08aeW8Kw1QOQsSEanr
   mcr3dYJyQO7btZIREiMiV9hROq7bi6rnmLYi++iuqrTzQpfpg+iSAfF7J
   NfKc3wq2+6etUVzxZhLiC6w0NVWpAHf3hpgauu9I8pk0xAsYqIO3bI/X7
   s=;
IronPort-SDR: 
 Mb5swMn+KcsFsZBMoka4+NcvherPj4dLUTzXSqCBvliS1qm01gNYlkmsZoG6juXvOsbsCPjMLQ
 Cje3C9vWRVSA==
X-IronPort-AV: E=Sophos;i="5.75,268,1589241600";
   d="scan'208";a="46040836"
Received: from sea32-co-svc-lb4-vlan3.sea.corp.amazon.com (HELO
 email-inbound-relay-2c-cc689b93.us-west-2.amazon.com) ([10.47.23.38])
  by smtp-border-fw-out-9101.sea19.amazon.com with ESMTP;
 22 Jun 2020 20:03:46 +0000
Received: from EX13MTAUEA002.ant.amazon.com
 (pdx4-ws-svc-p6-lb7-vlan3.pdx.amazon.com [10.170.41.166])
        by email-inbound-relay-2c-cc689b93.us-west-2.amazon.com (Postfix) with
 ESMTPS id DAFA1120F63;
        Mon, 22 Jun 2020 20:03:45 +0000 (UTC)
Received: from EX13D16EUB003.ant.amazon.com (10.43.166.99) by
 EX13MTAUEA002.ant.amazon.com (10.43.61.77) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Mon, 22 Jun 2020 20:03:45 +0000
Received: from 38f9d34ed3b1.ant.amazon.com (10.43.161.145) by
 EX13D16EUB003.ant.amazon.com (10.43.166.99) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Mon, 22 Jun 2020 20:03:35 +0000
From: Andra Paraschiv <andraprs@amazon.com>
To: <linux-kernel@vger.kernel.org>
CC: Anthony Liguori <aliguori@amazon.com>,
        Benjamin Herrenschmidt <benh@kernel.crashing.org>,
        Colm MacCarthaigh <colmmacc@amazon.com>,
        "Bjoern Doebel" <doebel@amazon.de>,
        David Woodhouse <dwmw@amazon.co.uk>,
        "Frank van der Linden" <fllinden@amazon.com>,
        Alexander Graf <graf@amazon.de>,
        Greg KH <gregkh@linuxfoundation.org>,
        Martin Pohlack <mpohlack@amazon.de>,
        "Matt Wilson" <msw@amazon.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Balbir Singh <sblbir@amazon.com>,
        Stefano Garzarella <sgarzare@redhat.com>,
        "Stefan Hajnoczi" <stefanha@redhat.com>,
        Stewart Smith <trawets@amazon.com>,
        "Uwe Dannowski" <uwed@amazon.de>, <kvm@vger.kernel.org>,
        <ne-devel-upstream@amazon.com>,
        Andra Paraschiv <andraprs@amazon.com>
Subject: [PATCH v4 00/18] Add support for Nitro Enclaves
Date: Mon, 22 Jun 2020 23:03:11 +0300
Message-ID: <20200622200329.52996-1-andraprs@amazon.com>
X-Mailer: git-send-email 2.20.1 (Apple Git-117)
MIME-Version: 1.0
X-Originating-IP: [10.43.161.145]
X-ClientProxiedBy: EX13D12UWC002.ant.amazon.com (10.43.162.253) To
 EX13D16EUB003.ant.amazon.com (10.43.166.99)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Nitro Enclaves (NE) is a new Amazon Elastic Compute Cloud (EC2) capability
that allows customers to carve out isolated compute environments within EC2
instances [1].

For example, an application that processes sensitive data and runs in a VM,
can be separated from other applications running in the same VM. This
application then runs in a separate VM than the primary VM, namely an enclave.

An enclave runs alongside the VM that spawned it. This setup matches low latency
applications needs. The resources that are allocated for the enclave, such as
memory and CPU, are carved out of the primary VM. Each enclave is mapped to a
process running in the primary VM, that communicates with the NE driver via an
ioctl interface.

In this sense, there are two components:

1. An enclave abstraction process - a user space process running in the primary
VM guest  that uses the provided ioctl interface of the NE driver to spawn an
enclave VM (that's 2 below).

There is a NE emulated PCI device exposed to the primary VM. The driver for this
new PCI device is included in the NE driver.

The ioctl logic is mapped to PCI device commands e.g. the NE_START_ENCLAVE ioctl
maps to an enclave start PCI command. The PCI device commands are then
translated into  actions taken on the hypervisor side; that's the Nitro
hypervisor running on the host where the primary VM is running. The Nitro
hypervisor is based on core KVM technology.

2. The enclave itself - a VM running on the same host as the primary VM that
spawned it. Memory and CPUs are carved out of the primary VM and are dedicated
for the enclave VM. An enclave does not have persistent storage attached.

The memory regions carved out of the primary VM and given to an enclave need to
be aligned 2 MiB / 1 GiB physically contiguous memory regions (or multiple of
this size e.g. 8 MiB). The memory can be allocated e.g. by using hugetlbfs from
user space [2][3]. The memory size for an enclave needs to be at least 64 MiB.
The enclave memory and CPUs need to be from the same NUMA node.

An enclave runs on dedicated cores. CPU 0 and its CPU siblings need to remain
available for the primary VM. A CPU pool has to be set for NE purposes by an
user with admin capability. See the cpu list section from the kernel
documentation [4] for how a CPU pool format looks.

An enclave communicates with the primary VM via a local communication channel,
using virtio-vsock [5]. The primary VM has virtio-pci vsock emulated device,
while the enclave VM has a virtio-mmio vsock emulated device. The vsock device
uses eventfd for signaling. The enclave VM sees the usual interfaces - local
APIC and IOAPIC - to get interrupts from virtio-vsock device. The virtio-mmio
device is placed in memory below the typical 4 GiB.

The application that runs in the enclave needs to be packaged in an enclave
image together with the OS ( e.g. kernel, ramdisk, init ) that will run in the
enclave VM. The enclave VM has its own kernel and follows the standard Linux
boot protocol.

The kernel bzImage, the kernel command line, the ramdisk(s) are part of the
Enclave Image Format (EIF); plus an EIF header including metadata such as magic
number, eif version, image size and CRC.

Hash values are computed for the entire enclave image (EIF), the kernel and
ramdisk(s). That's used, for example, to check that the enclave image that is
loaded in the enclave VM is the one that was intended to be run.

These crypto measurements are included in a signed attestation document
generated by the Nitro Hypervisor and further used to prove the identity of the
enclave; KMS is an example of service that NE is integrated with and that checks
the attestation doc.

The enclave image (EIF) is loaded in the enclave memory at offset 8 MiB. The
init process in the enclave connects to the vsock CID of the primary VM and a
predefined port - 9000 - to send a heartbeat value - 0xb7. This mechanism is
used to check in the primary VM that the enclave has booted.

If the enclave VM crashes or gracefully exits, an interrupt event is received by
the NE driver. This event is sent further to the user space enclave process
running in the primary VM via a poll notification mechanism. Then the user space
enclave process can exit.

Thank you.

Andra

[1] https://aws.amazon.com/ec2/nitro/nitro-enclaves/
[2] https://www.kernel.org/doc/Documentation/vm/hugetlbpage.txt
[3] https://lwn.net/Articles/807108/
[4] https://www.kernel.org/doc/html/latest/admin-guide/kernel-parameters.html
[5] https://man7.org/linux/man-pages/man7/vsock.7.html
---

Patch Series Changelog

The patch series is built on top of v5.8-rc2.

v3 -> v4

* Rebase on top of v5.8-rc2.
* Add NE API version and the corresponding ioctl call.
* Add enclave / image load flags options.
* Decouple NE ioctl interface from KVM API.
* Remove the "packed" attribute and include padding in the NE data structures.
* Update documentation based on the changes from v4.
* Update sample to match the updates in v4.
* Remove the NE CPU pool init during NE kernel module loading.
* Setup the NE CPU pool at runtime via a sysfs file for the kernel parameter.
* Check if the enclave memory and CPUs are from the same NUMA node.
* Add minimum enclave memory size definition.
* v3: https://lore.kernel.org/lkml/20200525221334.62966-1-andraprs@amazon.com/ 

v2 -> v3

* Rebase on top of v5.7-rc7.
* Add changelog to each patch in the series.
* Remove "ratelimited" from the logs that are not in the ioctl call paths.
* Update static calls sanity checks.
* Remove file ops that do nothing for now.
* Remove GPL additional wording as SPDX-License-Identifier is already in place.
* v2: https://lore.kernel.org/lkml/20200522062946.28973-1-andraprs@amazon.com/

v1 -> v2

* Rebase on top of v5.7-rc6.
* Adapt codebase based on feedback from v1.
* Update ioctl number definition - major and minor.
* Add sample / documentation for the ioctl interface basic flow usage.
* Update cover letter to include more context on the NE overall.
* Add fix for the enclave / vcpu fd creation error cleanup path.
* Add fix reported by kbuild test robot <lkp@intel.com>.
* v1: https://lore.kernel.org/lkml/20200421184150.68011-1-andraprs@amazon.com/

---

Andra Paraschiv (18):
  nitro_enclaves: Add ioctl interface definition
  nitro_enclaves: Define the PCI device interface
  nitro_enclaves: Define enclave info for internal bookkeeping
  nitro_enclaves: Init PCI device driver
  nitro_enclaves: Handle PCI device command requests
  nitro_enclaves: Handle out-of-band PCI device events
  nitro_enclaves: Init misc device providing the ioctl interface
  nitro_enclaves: Add logic for enclave vm creation
  nitro_enclaves: Add logic for enclave vcpu creation
  nitro_enclaves: Add logic for enclave image load info
  nitro_enclaves: Add logic for enclave memory region set
  nitro_enclaves: Add logic for enclave start
  nitro_enclaves: Add logic for enclave termination
  nitro_enclaves: Add Kconfig for the Nitro Enclaves driver
  nitro_enclaves: Add Makefile for the Nitro Enclaves driver
  nitro_enclaves: Add sample for ioctl interface usage
  nitro_enclaves: Add overview documentation
  MAINTAINERS: Add entry for the Nitro Enclaves driver

 Documentation/nitro_enclaves/ne_overview.rst  |   87 ++
 .../userspace-api/ioctl/ioctl-number.rst      |    5 +-
 MAINTAINERS                                   |   13 +
 drivers/virt/Kconfig                          |    2 +
 drivers/virt/Makefile                         |    2 +
 drivers/virt/nitro_enclaves/Kconfig           |   16 +
 drivers/virt/nitro_enclaves/Makefile          |   11 +
 drivers/virt/nitro_enclaves/ne_misc_dev.c     | 1364 +++++++++++++++++
 drivers/virt/nitro_enclaves/ne_misc_dev.h     |  115 ++
 drivers/virt/nitro_enclaves/ne_pci_dev.c      |  626 ++++++++
 drivers/virt/nitro_enclaves/ne_pci_dev.h      |  264 ++++
 include/linux/nitro_enclaves.h                |   11 +
 include/uapi/linux/nitro_enclaves.h           |  137 ++
 samples/nitro_enclaves/.gitignore             |    2 +
 samples/nitro_enclaves/Makefile               |   16 +
 samples/nitro_enclaves/ne_ioctl_sample.c      |  520 +++++++
 16 files changed, 3190 insertions(+), 1 deletion(-)
 create mode 100644 Documentation/nitro_enclaves/ne_overview.rst
 create mode 100644 drivers/virt/nitro_enclaves/Kconfig
 create mode 100644 drivers/virt/nitro_enclaves/Makefile
 create mode 100644 drivers/virt/nitro_enclaves/ne_misc_dev.c
 create mode 100644 drivers/virt/nitro_enclaves/ne_misc_dev.h
 create mode 100644 drivers/virt/nitro_enclaves/ne_pci_dev.c
 create mode 100644 drivers/virt/nitro_enclaves/ne_pci_dev.h
 create mode 100644 include/linux/nitro_enclaves.h
 create mode 100644 include/uapi/linux/nitro_enclaves.h
 create mode 100644 samples/nitro_enclaves/.gitignore
 create mode 100644 samples/nitro_enclaves/Makefile
 create mode 100644 samples/nitro_enclaves/ne_ioctl_sample.c
```
#### [PATCH v2 00/21] KVM: Cleanup and unify kvm_mmu_memory_cache usage
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Mon Jun 22 20:08:01 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11618917
Return-Path: <SRS0=pCMg=AD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7A35A138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 22 Jun 2020 20:09:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 695EE2076E
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 22 Jun 2020 20:09:14 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728475AbgFVUJM (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 22 Jun 2020 16:09:12 -0400
Received: from mga12.intel.com ([192.55.52.136]:60195 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728530AbgFVUJH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 22 Jun 2020 16:09:07 -0400
IronPort-SDR: 
 LFVSAjT7u+N5vZPa59QDReV12rIKpjnkbs0ZPYtCAaByNwjoV647sWDA9DyO2iqQvLylDTOiKB
 iudShdzF19fg==
X-IronPort-AV: E=McAfee;i="6000,8403,9660"; a="123527692"
X-IronPort-AV: E=Sophos;i="5.75,268,1589266800";
   d="scan'208";a="123527692"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga003.fm.intel.com ([10.253.24.29])
  by fmsmga106.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 22 Jun 2020 13:09:05 -0700
IronPort-SDR: 
 ACiGxnvdRH5yHzKRcBqEkHkrUW0Xmd5fP+wZakk5PUawdwmWwHSjFB8CI8ofv1H3JKPtVSPmv8
 o5YF/XigfYJw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,268,1589266800";
   d="scan'208";a="318877033"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.152])
  by FMSMGA003.fm.intel.com with ESMTP; 22 Jun 2020 13:09:05 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Marc Zyngier <maz@kernel.org>, Paolo Bonzini <pbonzini@redhat.com>,
        Arnd Bergmann <arnd@arndb.de>
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        linux-mips@vger.kernel.org, kvm@vger.kernel.org,
        linux-arch@vger.kernel.org, linux-kernel@vger.kernel.org,
        Ben Gardon <bgardon@google.com>,
        Peter Feiner <pfeiner@google.com>,
        Peter Shier <pshier@google.com>,
        Junaid Shahid <junaids@google.com>,
        Christoffer Dall <christoffer.dall@arm.com>
Subject: [PATCH v2 00/21] KVM: Cleanup and unify kvm_mmu_memory_cache usage
Date: Mon, 22 Jun 2020 13:08:01 -0700
Message-Id: <20200622200822.4426-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Note, patch 18 will conflict with the p4d rework in 5.8.  I originally
stated I would send v2 only after that got pulled into Paolo's tree, but
I got my timing wrong, i.e. I was thinking that would have already
happened.  I'll send v3 if necessary.  I wanted to get v2 out there now
that I actually compile tested other architectures.

Marc, I interpreted your "nothing caught fire" as Tested-by for the arm64
patches, let me know if that's not what you intended.


This series resurrects Christoffer Dall's series[1] to provide a common
MMU memory cache implementation that can be shared by x86, arm64 and MIPS.

It also picks up a suggested change from Ben Gardon[2] to clear shadow
page tables during initial allocation so as to avoid clearing entire
pages while holding mmu_lock.

The front half of the patches do house cleaning on x86's memory cache
implementation in preparation for moving it to common code, along with a
fair bit of cleanup on the usage.  The middle chunk moves the patches to
common KVM, and the last two chunks convert arm64 and MIPS to the common
implementation.

Fully tested on x86 only.  Compile tested patches 14-21 on arm64, MIPS,
s390 and PowerPC.

v2:
  - Rebase to kvm-5.8-2, commit 49b3deaad345 ("Merge tag ...").
  - Use an asm-generic kvm_types.h for s390 and PowerPC instead of an
    empty arch-specific file. [Marc]
  - Explicit document "GFP_PGTABLE_USER == GFP_KERNEL_ACCOUNT | GFP_ZERO"
    in the arm64 conversion patch. [Marc]
  - Collect review tags. [Ben]

[1] https://lkml.kernel.org/r/20191105110357.8607-1-christoffer.dall@arm
[2] https://lkml.kernel.org/r/20190926231824.149014-4-bgardon@google.com

Sean Christopherson (21):
  KVM: x86/mmu: Track the associated kmem_cache in the MMU caches
  KVM: x86/mmu: Consolidate "page" variant of memory cache helpers
  KVM: x86/mmu: Use consistent "mc" name for kvm_mmu_memory_cache locals
  KVM: x86/mmu: Remove superfluous gotos from mmu_topup_memory_caches()
  KVM: x86/mmu: Try to avoid crashing KVM if a MMU memory cache is empty
  KVM: x86/mmu: Move fast_page_fault() call above
    mmu_topup_memory_caches()
  KVM: x86/mmu: Topup memory caches after walking GVA->GPA
  KVM: x86/mmu: Clean up the gorilla math in mmu_topup_memory_caches()
  KVM: x86/mmu: Separate the memory caches for shadow pages and gfn
    arrays
  KVM: x86/mmu: Make __GFP_ZERO a property of the memory cache
  KVM: x86/mmu: Zero allocate shadow pages (outside of mmu_lock)
  KVM: x86/mmu: Skip filling the gfn cache for guaranteed direct MMU
    topups
  KVM: x86/mmu: Prepend "kvm_" to memory cache helpers that will be
    global
  KVM: Move x86's version of struct kvm_mmu_memory_cache to common code
  KVM: Move x86's MMU memory cache helpers to common KVM code
  KVM: arm64: Drop @max param from mmu_topup_memory_cache()
  KVM: arm64: Use common code's approach for __GFP_ZERO with memory
    caches
  KVM: arm64: Use common KVM implementation of MMU memory caches
  KVM: MIPS: Drop @max param from mmu_topup_memory_cache()
  KVM: MIPS: Account pages used for GPA page tables
  KVM: MIPS: Use common KVM implementation of MMU memory caches

 arch/arm64/include/asm/kvm_host.h  |  11 ---
 arch/arm64/include/asm/kvm_types.h |   8 ++
 arch/arm64/kvm/arm.c               |   2 +
 arch/arm64/kvm/mmu.c               |  54 +++---------
 arch/mips/include/asm/kvm_host.h   |  11 ---
 arch/mips/include/asm/kvm_types.h  |   7 ++
 arch/mips/kvm/mmu.c                |  44 ++--------
 arch/powerpc/include/asm/Kbuild    |   1 +
 arch/s390/include/asm/Kbuild       |   1 +
 arch/x86/include/asm/kvm_host.h    |  14 +---
 arch/x86/include/asm/kvm_types.h   |   7 ++
 arch/x86/kvm/mmu/mmu.c             | 129 +++++++++--------------------
 arch/x86/kvm/mmu/paging_tmpl.h     |  10 +--
 include/asm-generic/kvm_types.h    |   5 ++
 include/linux/kvm_host.h           |   7 ++
 include/linux/kvm_types.h          |  19 +++++
 virt/kvm/kvm_main.c                |  55 ++++++++++++
 17 files changed, 175 insertions(+), 210 deletions(-)
 create mode 100644 arch/arm64/include/asm/kvm_types.h
 create mode 100644 arch/mips/include/asm/kvm_types.h
 create mode 100644 arch/x86/include/asm/kvm_types.h
 create mode 100644 include/asm-generic/kvm_types.h
```
#### [PATCH 0/6] KVM: x86/mmu: Files and sp helper cleanups
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Mon Jun 22 20:20:28 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11619083
Return-Path: <SRS0=pCMg=AD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 35469618
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 22 Jun 2020 20:21:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1ABC32076A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 22 Jun 2020 20:21:09 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728555AbgFVUUh (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 22 Jun 2020 16:20:37 -0400
Received: from mga07.intel.com ([134.134.136.100]:62017 "EHLO mga07.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728405AbgFVUUh (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 22 Jun 2020 16:20:37 -0400
IronPort-SDR: 
 rpPC6FH9qWpRYypU/6l+4vVDhStTbgIYVyScAsZrdFpD1A1LCVjQUOBC+1g+78SJCR6VHy3L1z
 QRSbqRz5Udiw==
X-IronPort-AV: E=McAfee;i="6000,8403,9660"; a="209057474"
X-IronPort-AV: E=Sophos;i="5.75,268,1589266800";
   d="scan'208";a="209057474"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga006.fm.intel.com ([10.253.24.20])
  by orsmga105.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 22 Jun 2020 13:20:36 -0700
IronPort-SDR: 
 IIknzzp2CyZi4jR/40NntXy9138dMaGyEd1yeTT7VXR8VLoz6c8hb1nfpUfRP1ZHEwfK0e6wZN
 9eKCRXf06pkw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,268,1589266800";
   d="scan'208";a="478506313"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.152])
  by fmsmga006.fm.intel.com with ESMTP; 22 Jun 2020 13:20:36 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH 0/6] KVM: x86/mmu: Files and sp helper cleanups
Date: Mon, 22 Jun 2020 13:20:28 -0700
Message-Id: <20200622202034.15093-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Move more files to the mmu/ directory, and an mmu_internal.h to share
stuff amongst the mmu/ files, and clean up the helpers for retrieving a
shadow page from a sptep and/or hpa.

Sean Christopherson (6):
  KVM: x86/mmu: Move mmu_audit.c and mmutrace.h into the mmu/
    sub-directory
  KVM: x86/mmu: Move kvm_mmu_available_pages() into mmu.c
  KVM: x86/mmu: Add MMU-internal header
  KVM: x86/mmu: Make kvm_mmu_page definition and accessor internal-only
  KVM: x86/mmu: Add sptep_to_sp() helper to wrap shadow page lookup
  KVM: x86/mmu: Rename page_header() to to_shadow_page()

 arch/x86/include/asm/kvm_host.h    | 46 +---------------------
 arch/x86/kvm/mmu.h                 | 13 ------
 arch/x86/kvm/mmu/mmu.c             | 58 +++++++++++++++------------
 arch/x86/kvm/{ => mmu}/mmu_audit.c | 12 +++---
 arch/x86/kvm/mmu/mmu_internal.h    | 63 ++++++++++++++++++++++++++++++
 arch/x86/kvm/{ => mmu}/mmutrace.h  |  2 +-
 arch/x86/kvm/mmu/page_track.c      |  2 +-
 arch/x86/kvm/mmu/paging_tmpl.h     |  4 +-
 8 files changed, 108 insertions(+), 92 deletions(-)
 rename arch/x86/kvm/{ => mmu}/mmu_audit.c (96%)
 create mode 100644 arch/x86/kvm/mmu/mmu_internal.h
 rename arch/x86/kvm/{ => mmu}/mmutrace.h (99%)
```
#### [PATCH 0/4] KVM: x86: nVMX: Nested PML bug fix and cleanup
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Mon Jun 22 21:58:28 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11619243
Return-Path: <SRS0=pCMg=AD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2F9126C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 22 Jun 2020 21:58:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2270320767
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 22 Jun 2020 21:58:58 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730763AbgFVV6f (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 22 Jun 2020 17:58:35 -0400
Received: from mga11.intel.com ([192.55.52.93]:15498 "EHLO mga11.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727006AbgFVV6f (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 22 Jun 2020 17:58:35 -0400
IronPort-SDR: 
 KRvkcQRT4rBNCr/B1TE60VYKH5cLZXHpRpq1ncq91NPWlGvODwT812H1YPbfF3TZ/+8krUAwxS
 8sveclPsje3A==
X-IronPort-AV: E=McAfee;i="6000,8403,9660"; a="142148017"
X-IronPort-AV: E=Sophos;i="5.75,268,1589266800";
   d="scan'208";a="142148017"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga004.fm.intel.com ([10.253.24.48])
  by fmsmga102.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 22 Jun 2020 14:58:34 -0700
IronPort-SDR: 
 LSYAsMODyMOxQuUrr1xHH7LlZh+uKR68WRuRiXJlBaJjIzaCCo/v0DqzSskgDc6DO3RqBjo+d0
 XbSi2dPDo16w==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,268,1589266800";
   d="scan'208";a="300987312"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.152])
  by fmsmga004.fm.intel.com with ESMTP; 22 Jun 2020 14:58:33 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH 0/4] KVM: x86: nVMX: Nested PML bug fix and cleanup
Date: Mon, 22 Jun 2020 14:58:28 -0700
Message-Id: <20200622215832.22090-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Fix for a theoretical bug in nested PML emulation, and additional clean up
of the related code.

Tested by doing a few rounds of intra-VM migration (same L1) of an L2
guest with PML confirmed enabled in L1.

This has a trivial conflict with patch 3 of the MMU files series[*], both
remove function prototypes from mmu.h.

[*] https://lkml.kernel.org/r/20200622202034.15093-4-sean.j.christopherson@intel.com

Sean Christopherson (4):
  KVM: nVMX: Plumb L2 GPA through to PML emulation
  KVM: x86/mmu: Drop kvm_arch_write_log_dirty() wrapper
  KVM: nVMX: WARN if PML emulation helper is invoked outside of nested
    guest
  KVM: x86/mmu: Make .write_log_dirty a nested operation

 arch/x86/include/asm/kvm_host.h |  2 +-
 arch/x86/kvm/mmu.h              |  1 -
 arch/x86/kvm/mmu/mmu.c          | 15 -------------
 arch/x86/kvm/mmu/paging_tmpl.h  |  7 +++---
 arch/x86/kvm/vmx/nested.c       | 38 +++++++++++++++++++++++++++++++++
 arch/x86/kvm/vmx/vmx.c          | 37 --------------------------------
 6 files changed, 43 insertions(+), 57 deletions(-)
```
#### [PATCH 0/2] KVM: X86: A few fixes around ignore_msrs
##### From: Peter Xu <peterx@redhat.com>

```c
From patchwork Mon Jun 22 22:04:40 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11619251
Return-Path: <SRS0=pCMg=AD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 37F3D912
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 22 Jun 2020 22:04:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 20B0320767
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 22 Jun 2020 22:04:54 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="bNCQ3/cn"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730922AbgFVWEv (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 22 Jun 2020 18:04:51 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:52742 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1730736AbgFVWEu (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 22 Jun 2020 18:04:50 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1592863489;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=D9zKETShESnlmbV3mu0MXm27L6L0w57VJPQLcTIPbrk=;
        b=bNCQ3/cnaPQ11zk3dqoQnHvKwmyBrrPHQL2KW4BbrAcZmDuLmXkTNNAmNxoQf8jNkZAPpQ
        JrrDZy4GJynpNfEUXftQrZdh/x88EXxKuv9HAkVUkm58SBrCKUIEm2qQgAqV0LtoXy7vIg
        7qsU/6S3jiBtoXT0E849sHJx3vU7KL4=
Received: from mail-qt1-f197.google.com (mail-qt1-f197.google.com
 [209.85.160.197]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-11-JkegwOwZMrapsB0DOCA9nA-1; Mon, 22 Jun 2020 18:04:47 -0400
X-MC-Unique: JkegwOwZMrapsB0DOCA9nA-1
Received: by mail-qt1-f197.google.com with SMTP id r25so2757955qtj.11
        for <kvm@vger.kernel.org>; Mon, 22 Jun 2020 15:04:47 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=D9zKETShESnlmbV3mu0MXm27L6L0w57VJPQLcTIPbrk=;
        b=hEc6hSGHAmu+qkXRJ9bfdz85MpqfkmsGyA9868JdSD9sYHmxcC4raZE7lgen3w62Mb
         ZH29TbVfqrx2merJKgYYgj74FKvSrf6bLqVmPju3Kze5pE9G1XhwhUBYFiben1fQWO+T
         ur9I4EOlObfsClVRqz2m9AAR1WwlNL16z72LXvLgKT1hEKFEdYnBgeWE88BWqWDpYuwL
         1TEUPNtRReSe8cWHKS6fYCCtyVSvRIsf8X1MUgElv7ZgJP4tI3OBTStFZBFlYO1ITKH5
         Yn5dUt3hRdF4/ya//v93nfVUGjqhCKC8NKZVEL2p5ZHcdsKFf65Di4w2FWVTaHrjk2XU
         D0Sg==
X-Gm-Message-State: AOAM533zfkQ5UVXhid2olxbmtK3rM1Yo3LPV6DGR+r20qJfcyCaZ7qYy
        3N3YInByb78DX3QQXerdPxEfkqCegw5RM0T1zit2oC5hiihzsaAvSL6qQLAvO2paA0jykH1O1X0
        1g1LMqbd6humi
X-Received: by 2002:ac8:39a5:: with SMTP id v34mr3750921qte.377.1592863486981;
        Mon, 22 Jun 2020 15:04:46 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJzPioSIYBbZtgP/PBxkHkqJOw9BSt46b64TzBxG1INjx9E7Vg9ObXsPvQdo2rC0ZKklAQiWMQ==
X-Received: by 2002:ac8:39a5:: with SMTP id v34mr3750894qte.377.1592863486754;
        Mon, 22 Jun 2020 15:04:46 -0700 (PDT)
Received: from xz-x1.redhat.com ([2607:9880:19c0:32::2])
        by smtp.gmail.com with ESMTPSA id h6sm3506810qtu.2.2020.06.22.15.04.44
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 22 Jun 2020 15:04:45 -0700 (PDT)
From: Peter Xu <peterx@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Paolo Bonzini <pbonzini@redhat.com>, peterx@redhat.com,
        Vitaly Kuznetsov <vkuznets@redhat.com>
Subject: [PATCH 0/2] KVM: X86: A few fixes around ignore_msrs
Date: Mon, 22 Jun 2020 18:04:40 -0400
Message-Id: <20200622220442.21998-1-peterx@redhat.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Currently ignore_msrs and report_ignored_msrs have a few issues:

  - Errors could be dumped to dmesg even if the msr access is triggered inside
    kvm itself (e.g., kvm_cpuid), while what we really want to trap should be
    either guest msr accesses, or KVM_SET_MSRS.

  - These two parameters didn't apply to feature msrs.

Each of the patch in this series tries to handle one of the issues.

Here KVM_MSR_RET_INVALID is introduced.  Ideally it can be an enum with both
0/1 defined too, but I'll see whether there's any feedback first about this
version.

This originates from a discussion between Paolo and me on an unexpected warning
msr access message that triggered on a RT system, which seemed to have caused
some system jitters.

Please have a look, thanks.

Peter Xu (2):
  KVM: X86: Move ignore_msrs handling upper the stack
  KVM: X86: Do the same ignore_msrs check for feature msrs

 arch/x86/kvm/svm/svm.c |  2 +-
 arch/x86/kvm/vmx/vmx.c |  2 +-
 arch/x86/kvm/x86.c     | 90 +++++++++++++++++++++++++++++-------------
 arch/x86/kvm/x86.h     |  2 +
 4 files changed, 66 insertions(+), 30 deletions(-)
```
#### [PATCH 00/15] KVM: x86: VMX: Fix MSR namespacing
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Mon Jun 22 22:42:34 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11619331
Return-Path: <SRS0=pCMg=AD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6C3EA13A0
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 22 Jun 2020 22:45:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5E11720786
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 22 Jun 2020 22:45:42 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731030AbgFVWmw (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 22 Jun 2020 18:42:52 -0400
Received: from mga18.intel.com ([134.134.136.126]:27423 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1730785AbgFVWmw (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 22 Jun 2020 18:42:52 -0400
IronPort-SDR: 
 SZzMoYu9k/bsi0TippxRgeAI4JxXAfP+FR3M3cob+SM0FTxCcKX6hb1BoUzXHmKgvl2y7BM79t
 spMgJg8usHSg==
X-IronPort-AV: E=McAfee;i="6000,8403,9660"; a="131303559"
X-IronPort-AV: E=Sophos;i="5.75,268,1589266800";
   d="scan'208";a="131303559"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by orsmga106.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 22 Jun 2020 15:42:51 -0700
IronPort-SDR: 
 MYHhyweIOug5uQxuzf6wMIfLHQQjD0kMpblb0upFpf1vVCk42LvEPB8R3p8Bk8lpnjgXvaWDhW
 Ehq4FpvIUOmQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,268,1589266800";
   d="scan'208";a="264634897"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.152])
  by fmsmga008.fm.intel.com with ESMTP; 22 Jun 2020 15:42:50 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH 00/15] KVM: x86: VMX: Fix MSR namespacing
Date: Mon, 22 Jun 2020 15:42:34 -0700
Message-Id: <20200622224249.29562-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series attempts to clean up VMX's MSR namespacing, which is in
unimitigated disaster (keeping things PG).

There are a variety of ways VMX saves and restores guest MSRs, all with
unique properties and mechanisms, but with haphazard namespacing (assuming
there is any namespacing at all).  Some fun collisions:

  __find_msr_index(), find_msr_entry() and vmx_find_msr_index()

  vmx_set_guest_msr() and vmx_set_msr() 

  structs vmx_msrs, vmx_msr_entry, shared_msr_entry, kvm_shared_msrs and
  kvm_shared_msrs_values

  vcpu_vmx fields guest_msrs, msr_autoload.guest and msr_autostore.guest

Probably the most infurating/confusing nomenclature is "index", which can
mean MSR's ECX index, index into one of several VMX arrays, or index into
a common x86 array.  __find_msr_index() even manages to mix at least three
different meanings in about as many lines of code.

The biggest change is to rename the "shared MSRs" mechanism to "user
return MSRs" (details in patch 1), most everything else is either derived
from that rename or is fairly straightforward cleanup.

No true functional changes, although the update_transition_efer() change
in patch 10 dances pretty close to being a functional change.

Sean Christopherson (15):
  KVM: x86: Rename "shared_msrs" to "user_return_msrs"
  KVM: VMX: Prepend "MAX_" to MSR array size defines
  KVM: VMX: Rename "vmx_find_msr_index" to "vmx_find_loadstore_msr_slot"
  KVM: VMX: Rename the "shared_msr_entry" struct to "vmx_uret_msr"
  KVM: VMX: Rename vcpu_vmx's "nmsrs" to "nr_uret_msrs"
  KVM: VMX: Rename vcpu_vmx's "save_nmsrs" to "nr_active_uret_msrs"
  KVM: VMX: Rename vcpu_vmx's "guest_msrs_ready" to
    "guest_uret_msrs_loaded"
  KVM: VMX: Rename "__find_msr_index" to "__vmx_find_uret_msr"
  KVM: VMX: Check guest support for RDTSCP before processing MSR_TSC_AUX
  KVM: VMX: Move uret MSR lookup into update_transition_efer()
  KVM: VMX: Add vmx_setup_uret_msr() to handle lookup and swap
  KVM: VMX: Rename "find_msr_entry" to "vmx_find_uret_msr"
  KVM: VMX: Rename "vmx_set_guest_msr" to "vmx_set_guest_uret_msr"
  KVM: VMX: Rename "vmx_msr_index" to "vmx_uret_msrs_list"
  KVM: VMX: Rename vmx_uret_msr's "index" to "slot"

 arch/x86/include/asm/kvm_host.h |   4 +-
 arch/x86/kvm/vmx/nested.c       |  22 ++--
 arch/x86/kvm/vmx/vmx.c          | 184 ++++++++++++++++----------------
 arch/x86/kvm/vmx/vmx.h          |  24 ++---
 arch/x86/kvm/x86.c              | 101 +++++++++---------
 5 files changed, 168 insertions(+), 167 deletions(-)
```
