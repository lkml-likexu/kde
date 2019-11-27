#### [PATCH 1/1] powerpc/kvm/book3s: Fixes possible 'use after release' of kvm
##### From: Leonardo Bras <leonardo@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Leonardo Bras <leonardo@linux.ibm.com>
X-Patchwork-Id: 11262919
Return-Path: <SRS0=Fa6O=ZS=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CBAA7930
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 26 Nov 2019 17:52:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B104720659
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 26 Nov 2019 17:52:55 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727006AbfKZRwn (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 26 Nov 2019 12:52:43 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:4936 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726005AbfKZRwn (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 26 Nov 2019 12:52:43 -0500
Received: from pps.filterd (m0098417.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 xAQHnISc145507;
        Tue, 26 Nov 2019 12:52:24 -0500
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2wh4yrb92v-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 26 Nov 2019 12:52:24 -0500
Received: from m0098417.ppops.net (m0098417.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id xAQHnNLg145900;
        Tue, 26 Nov 2019 12:52:24 -0500
Received: from ppma03dal.us.ibm.com (b.bd.3ea9.ip4.static.sl-reverse.com
 [169.62.189.11])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2wh4yrb92c-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 26 Nov 2019 12:52:23 -0500
Received: from pps.filterd (ppma03dal.us.ibm.com [127.0.0.1])
        by ppma03dal.us.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 xAQHpCNQ029315;
        Tue, 26 Nov 2019 17:52:23 GMT
Received: from b03cxnp08027.gho.boulder.ibm.com
 (b03cxnp08027.gho.boulder.ibm.com [9.17.130.19])
        by ppma03dal.us.ibm.com with ESMTP id 2wevd6mk8s-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 26 Nov 2019 17:52:23 +0000
Received: from b03ledav006.gho.boulder.ibm.com
 (b03ledav006.gho.boulder.ibm.com [9.17.130.237])
        by b03cxnp08027.gho.boulder.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id xAQHqLow36438320
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 26 Nov 2019 17:52:21 GMT
Received: from b03ledav006.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id C22A0C6055;
        Tue, 26 Nov 2019 17:52:21 +0000 (GMT)
Received: from b03ledav006.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 8E9B2C6059;
        Tue, 26 Nov 2019 17:52:19 +0000 (GMT)
Received: from LeoBras.aus.stglabs.ibm.com (unknown [9.18.235.137])
        by b03ledav006.gho.boulder.ibm.com (Postfix) with ESMTP;
        Tue, 26 Nov 2019 17:52:19 +0000 (GMT)
From: Leonardo Bras <leonardo@linux.ibm.com>
To: Sean Christopherson <sean.j.christopherson@intel.com>,
        kvm-ppc@vger.kernel.org, linuxppc-dev@lists.ozlabs.org,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Leonardo Bras <leonardo@linux.ibm.com>,
 Paul Mackerras <paulus@ozlabs.org>,
 Benjamin Herrenschmidt <benh@kernel.crashing.org>,
 Michael Ellerman <mpe@ellerman.id.au>, Paolo Bonzini <pbonzini@redhat.com>,
	=?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>
Subject: [PATCH 1/1] powerpc/kvm/book3s: Fixes possible 'use after release' of
 kvm
Date: Tue, 26 Nov 2019 14:52:12 -0300
Message-Id: <20191126175212.377171-1-leonardo@linux.ibm.com>
X-Mailer: git-send-email 2.23.0
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.95,18.0.572
 definitions=2019-11-26_05:2019-11-26,2019-11-26 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxscore=0 suspectscore=2
 adultscore=0 mlxlogscore=999 impostorscore=0 clxscore=1015
 priorityscore=1501 lowpriorityscore=0 bulkscore=0 malwarescore=0
 spamscore=0 phishscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-1910280000 definitions=main-1911260149
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Fixes a possible 'use after free' of kvm variable.
It does use mutex_unlock(&kvm->lock) after possible freeing a variable
with kvm_put_kvm(kvm).

Signed-off-by: Leonardo Bras <leonardo@linux.ibm.com>
---
 arch/powerpc/kvm/book3s_64_vio.c | 3 +--
 virt/kvm/kvm_main.c              | 8 ++++----
 2 files changed, 5 insertions(+), 6 deletions(-)

```
#### [GIT PULL] Please pull my kvm-ppc-uvmem-5.5 tag
##### From: Paul Mackerras <paulus@ozlabs.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paul Mackerras <paulus@ozlabs.org>
X-Patchwork-Id: 11261403
Return-Path: <SRS0=Fa6O=ZS=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 852F4913
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 26 Nov 2019 05:25:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5A95A20637
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 26 Nov 2019 05:25:12 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ozlabs.org header.i=@ozlabs.org
 header.b="OrrjmxLz"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725972AbfKZFZJ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 26 Nov 2019 00:25:09 -0500
Received: from bilbo.ozlabs.org ([203.11.71.1]:56447 "EHLO ozlabs.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725895AbfKZFZJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 26 Nov 2019 00:25:09 -0500
Received: by ozlabs.org (Postfix, from userid 1003)
        id 47MXR43wDqz9sPZ; Tue, 26 Nov 2019 16:25:04 +1100 (AEDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=ozlabs.org; s=201707;
        t=1574745904; bh=wPLhJcunPY8dkJ+oWckDI2juIpu0G8ZeGW0AcJ2jvJI=;
        h=Date:From:To:Cc:Subject:From;
        b=OrrjmxLzDliZAKH/FxojbSzirNUahnWtylp+5b9FlRKDxK9CaXMPRu1XavOD7DUVV
         x3B0nporBsgbWMTqcniJvYz4mssTpADGe/3pHGbZCxrFdhuSCb2Qp2FiVP7J9TB4DN
         2Ppc9p3E3126V1IijWTK6HAaBi/X4KkF+a+iml2VQyqmvKrXWYTIHbxwFAPhsa/++M
         IXpI8f0ZUdUjwfvHAoh7qgTSkSvYQvMV2GCsZRm+dvFVZmElnc7EWud5d9PTmqfsja
         lPgbeCQY75u9umHINWzDpPWF/TRFRUIfrCq3jdRbpuXtSw+6cLykHak7MEb2e7cblb
         odDqolf4nagew==
Date: Tue, 26 Nov 2019 16:24:55 +1100
From: Paul Mackerras <paulus@ozlabs.org>
To: Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org
Cc: kvm-ppc@vger.kernel.org, Bharata B Rao <bharata@linux.vnet.ibm.com>
Subject: [GIT PULL] Please pull my kvm-ppc-uvmem-5.5 tag
Message-ID: <20191126052455.GA2922@oak.ozlabs.ibm.com>
MIME-Version: 1.0
Content-Disposition: inline
User-Agent: Mutt/1.10.1 (2018-07-13)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Paolo,

If you are intending to send a second pull request for Linus for this
merge window, and you are OK with taking a new feature in PPC KVM code
at this stage, then please do a pull from my kvm-ppc-uvmem-5.5 tag.
This adds code to manage the movement of pages for a secure KVM guest
between normal memory managed by the host kernel and secure memory
managed by the ultravisor on Power systems with Protected Execution
Facility hardware and firmware.  Secure memory is not accessible to
the host kernel and is represented as device memory using the
ZONE_DEVICE facility.

The patch set has been around for a while and has been reasonably well
reviewed -- this branch contains v11 of the patch set.  The code
changes are confined to PPC KVM code with the exception of a one-line
change to mm/ksm.c to export the ksm_madvise function, the addition of
a new ioctl number in include/uapi/linux/kvm.h, and the addition of a
Kconfig option in arch/powerpc/Kconfig (which Michael Ellerman is OK
with).

If you prefer not to pull this for 5.5 then we'll submit it for 5.6.

Thanks,
Paul.

The following changes since commit 96710247298df52a4b8150a62a6fe87083093ff3:

  Merge tag 'kvm-ppc-next-5.5-2' of git://git.kernel.org/pub/scm/linux/kernel/git/paulus/powerpc into HEAD (2019-11-25 11:29:05 +0100)

are available in the Git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/paulus/powerpc tags/kvm-ppc-uvmem-5.5

for you to fetch changes up to 177707824f27d258cf5e20f1a122570e3df011b4:

  powerpc: Ultravisor: Add PPC_UV config option (2019-11-26 14:33:27 +1100)

----------------------------------------------------------------
KVM: Add support for secure guests under the Protected Execution
Framework (PEF) Ultravisor on POWER.

This enables secure memory to be represented as device memory,
which provides a way for the host to keep track of which pages of a
secure guest have been moved into secure memory managed by the
ultravisor and are no longer accessible by the host, and manage
movement of pages between secure and normal memory.

----------------------------------------------------------------
Anshuman Khandual (1):
      powerpc: Ultravisor: Add PPC_UV config option

Bharata B Rao (6):
      mm: ksm: Export ksm_madvise()
      KVM: PPC: Book3S HV: Support for running secure guests
      KVM: PPC: Book3S HV: Shared pages support for secure guests
      KVM: PPC: Book3S HV: Radix changes for secure guest
      KVM: PPC: Book3S HV: Handle memory plug/unplug to secure VM
      KVM: PPC: Book3S HV: Support reset of secure guest

 Documentation/virt/kvm/api.txt              |  18 +
 arch/powerpc/Kconfig                        |  17 +
 arch/powerpc/include/asm/hvcall.h           |   9 +
 arch/powerpc/include/asm/kvm_book3s_uvmem.h |  74 +++
 arch/powerpc/include/asm/kvm_host.h         |   6 +
 arch/powerpc/include/asm/kvm_ppc.h          |   1 +
 arch/powerpc/include/asm/ultravisor-api.h   |   6 +
 arch/powerpc/include/asm/ultravisor.h       |  36 ++
 arch/powerpc/kvm/Makefile                   |   3 +
 arch/powerpc/kvm/book3s_64_mmu_radix.c      |  25 +
 arch/powerpc/kvm/book3s_hv.c                | 143 +++++
 arch/powerpc/kvm/book3s_hv_uvmem.c          | 774 ++++++++++++++++++++++++++++
 arch/powerpc/kvm/powerpc.c                  |  12 +
 include/uapi/linux/kvm.h                    |   1 +
 mm/ksm.c                                    |   1 +
 15 files changed, 1126 insertions(+)
 create mode 100644 arch/powerpc/include/asm/kvm_book3s_uvmem.h
 create mode 100644 arch/powerpc/kvm/book3s_hv_uvmem.c
```
#### [kvm-unit-tests PATCH v2] x86: Add RDTSC testFrom: Aaron Lewis <aaronlewis@google.com>
##### From: Aaron Lewis <aaronlewis@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Aaron Lewis <aaronlewis@google.com>
X-Patchwork-Id: 11263087
Return-Path: <SRS0=Fa6O=ZS=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5FB31930
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 26 Nov 2019 21:46:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 34B252064B
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 26 Nov 2019 21:46:41 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="fPLlBo14"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727010AbfKZVqj (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 26 Nov 2019 16:46:39 -0500
Received: from mail-pj1-f74.google.com ([209.85.216.74]:41588 "EHLO
        mail-pj1-f74.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726033AbfKZVqj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 26 Nov 2019 16:46:39 -0500
Received: by mail-pj1-f74.google.com with SMTP id h11so9905353pjq.8
        for <kvm@vger.kernel.org>; Tue, 26 Nov 2019 13:46:37 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=kgrb4wy/9+Q5wK6RZmvuK7OIH9bJhLzwwghsOTMvclU=;
        b=fPLlBo14xmZmR7d5P+QcQ9UuLflFTMtxMRERTcDkubKoPxoTGSNqRPQecufChKfyee
         1OyWDvmDJQIesQ7gjuJIEeQuZ6rA0SgWFGevuQ+nI3rqE/co1zyCWfESrRS/ib4CJEUf
         NjZ0U+KRJxHD2FNZM92nb2ULsHMwKy0y9g7d2NC241gYGcKdWix70ytMW2+f1vQSzp7J
         vpxmcNM4gu8XVNw2UzostTTLTp+YvI4vDj5vQJf/2Z8GplHASAOywmaLnNt6PWwETltZ
         bd1i/v6rpYDKDsFrt7LacQLF2SfTog1mFqfSJps0ogsxyunqDMcuMaNlY1FgB0v8vv6A
         cuFA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=kgrb4wy/9+Q5wK6RZmvuK7OIH9bJhLzwwghsOTMvclU=;
        b=iXgKQInIrhpVIbgPq6YvprHiSFbeLDThcwTGzrOXzRJVLGBEj6NfVz7k9SH/ijmLnr
         ansKe2EvixitZBug8mliLyjgSDqFEBLSkomtDhlbwzSZNN4HkHAcQenHGE+3ROLxWiAT
         /k3oovffMrhHdCKihiS6H0dWPgzktbB5R2pBkoVBnLCFtngiWI9jr19iH3RoKK5pq9cl
         Elhyv13drBPbkoneq6dr1hijqH5YfYBM9U1nnTEBb4SObHaVwXUVzEcxOqRSaf592UNN
         /S9LdKLPECoqjSjGRFGaUScjGn4vd/6cQlewx5tW4IDySd4iXhGt+YsYj49CxgsAXX/w
         KQEw==
X-Gm-Message-State: APjAAAUfYb7qD+E8dvLEG+9U4GiuI8tD0PVEI5y1j6ocyKk9fWD3nvez
        0+bvC+KCQ4XBbQ58qMmzu2HDV9whU3W4uudr
X-Google-Smtp-Source: 
 APXvYqzopno2M5Eo/eSSKW7+KBZOw0QpbZLrQkz+NCwSa0WLY779OnlNBnO9ZbgFov3Tyd6IXMGzI+ovWOO1/vhc
X-Received: by 2002:a63:d70f:: with SMTP id d15mr794420pgg.424.1574804796692;
 Tue, 26 Nov 2019 13:46:36 -0800 (PST)
Date: Tue, 26 Nov 2019 13:44:44 -0800
Message-Id: <20191126214443.99189-1-aaronlewis@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.24.0.432.g9d3f5f5b63-goog
Subject: [kvm-unit-tests PATCH v2] x86: Add RDTSC test
From: Aaron Lewis <aaronlewis@google.com>
To: Liran Alon <liran.alon@oracle.com>,
        Jim Mattson <jmattson@google.com>, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Aaron Lewis <aaronlewis@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Verify that the difference between a guest RDTSC instruction and the
IA32_TIME_STAMP_COUNTER MSR value stored in the VMCS12's VM-exit
MSR-store list is less than 750 cycles, 99.9% of the time.

Signed-off-by: Aaron Lewis <aaronlewis@google.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 x86/unittests.cfg |  6 ++++
 x86/vmx.h         |  1 +
 x86/vmx_tests.c   | 91 +++++++++++++++++++++++++++++++++++++++++++++++
 3 files changed, 98 insertions(+)

```
#### [PATCH] KVM: x86/mmu: fix comparison of u8 with -1
##### From: Colin King <colin.king@canonical.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Colin King <colin.king@canonical.com>
X-Patchwork-Id: 11262709
Return-Path: <SRS0=Fa6O=ZS=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 784A714DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 26 Nov 2019 16:21:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 6384420862
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 26 Nov 2019 16:21:55 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727269AbfKZQVw (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 26 Nov 2019 11:21:52 -0500
Received: from youngberry.canonical.com ([91.189.89.112]:36157 "EHLO
        youngberry.canonical.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725972AbfKZQVv (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 26 Nov 2019 11:21:51 -0500
Received: from 1.general.cking.uk.vpn ([10.172.193.212] helo=localhost)
        by youngberry.canonical.com with esmtpsa
 (TLS1.2:ECDHE_RSA_AES_128_GCM_SHA256:128)
        (Exim 4.86_2)
        (envelope-from <colin.king@canonical.com>)
        id 1iZdSS-0002hL-31; Tue, 26 Nov 2019 16:12:56 +0000
From: Colin King <colin.king@canonical.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Sean Christopherson <sean.j.christopherson@intel.com>,
 Vitaly Kuznetsov <vkuznets@redhat.com>, Wanpeng Li <wanpengli@tencent.com>,
 Jim Mattson <jmattson@google.com>, Joerg Roedel <joro@8bytes.org>,
 Thomas Gleixner <tglx@linutronix.de>, Ingo Molnar <mingo@redhat.com>,
 Borislav Petkov <bp@alien8.de>, "H . Peter Anvin" <hpa@zytor.com>,
 x86@kernel.org, kvm@vger.kernel.org, clang-built-linux@googlegroups.com
Cc: kernel-janitors@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: x86/mmu: fix comparison of u8 with -1
Date: Tue, 26 Nov 2019 16:12:55 +0000
Message-Id: <20191126161255.323992-1-colin.king@canonical.com>
X-Mailer: git-send-email 2.24.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Colin Ian King <colin.king@canonical.com>

The comparison of the u8 value __entry->u with -1 is always
going to be false because a __entry-u can never be negative.
Fix this by casting it to a s8 integer.

Addresses clang warning:
arch/x86/kvm/./mmutrace.h:360:16: warning: result of comparison
of constant -1 with expression of type 'u8' (aka 'unsigned char')
is always false [-Wtautological-constant-out-of-range-compare]

Fixes: 335e192a3fa4 ("KVM: x86: add tracepoints around __direct_map and FNAME(fetch)")
Signed-off-by: Colin Ian King <colin.king@canonical.com>
Reviewed-by: Nick Desaulniers <ndesaulniers@google.com>
---
 arch/x86/kvm/mmutrace.h | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [RFC 1/3] configure: add libbpf support
##### From: Prashant Bhole <prashantbhole.linux@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Prashant Bhole <prashantbhole.linux@gmail.com>
X-Patchwork-Id: 11261837
Return-Path: <SRS0=Fa6O=ZS=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 52B5B15AC
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 26 Nov 2019 10:10:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 310072089D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 26 Nov 2019 10:10:20 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="d+YYczk4"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728017AbfKZKKO (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 26 Nov 2019 05:10:14 -0500
Received: from mail-pg1-f194.google.com ([209.85.215.194]:39365 "EHLO
        mail-pg1-f194.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728010AbfKZKKO (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 26 Nov 2019 05:10:14 -0500
Received: by mail-pg1-f194.google.com with SMTP id b137so6442664pga.6;
        Tue, 26 Nov 2019 02:10:13 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=ecShvr+Zq6STOGx1l0iQ8cCvKv5lb6vZ/WjknM9nD6E=;
        b=d+YYczk4lJH43WHRgPgABeQW5AYRNcl7DJRbNi1c4p2WWFqkvolmM2XsQ44czI+mWp
         aVmIt6CW9B+7OpTNN+ps0zReed0nBfjwq9pklcNZKWKoIW7k1EQMTOHSi4d0/BCnYQee
         jinDCFwA6wNeZ4cBOG9cHPVSHcKoTCX0NlPdmJVevRHmMaf97cZDvXxtiWam3BPVOLr9
         RFEZ0ncycDTNPn5Urku5wMT1KOZ8+LKL42IakRmapDH1VNSLE/H9DD99CM6pQ9LMRigI
         y0T8KiZRlGegkVpLl3zTTtrATMEXAozU32i+jHRlYa3drVFQX+N2oBh6kWr44Z3T2zcB
         SEaQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=ecShvr+Zq6STOGx1l0iQ8cCvKv5lb6vZ/WjknM9nD6E=;
        b=DeWsz7cvyOT96qeoXmPmrT16zTTQuqg0n0i4Gqhb9cUmzRb0p6rZe/MVpcv9Wavevl
         Hpkj7R6mOIFQ0GLBDg95hioXfwzO9YyDufp9P9FiGoSPjUf3O+uVHcf20rEhBBWvN08m
         uja5QKFFx3zjsdFWR9fiZ6Cuw7P+9FuOylA11h5rgdH0u/eWzp2suu0Ayt8VgWludHpi
         D9EVoYA3iVMTK7EbnDRgJw7ClEKtZaHHYsgu7lO+uT2b/caEy2oGDUOaC5QJlngaVGKJ
         bxWYiF02bo5QSN1FHFwv2KYC4ux3wHhzZSSPIPw3N+mTmONkL6+XuDAkF437HHHXdMAL
         GI2w==
X-Gm-Message-State: APjAAAUUc6aRz1JCNBB/kTSPkzKPkiVI7A0iBsOpeZfQP2jdoir64455
        K7px3UCEoupDnsMbP4KzB1E=
X-Google-Smtp-Source: 
 APXvYqxLnUahtpS2ezzELlW12TWhqW19OSB0jtp9PSXtwd5yFTcnaRJ86M926/WsXnNPNpvBgZKE9Q==
X-Received: by 2002:a63:e4a:: with SMTP id 10mr35864959pgo.121.1574763013362;
        Tue, 26 Nov 2019 02:10:13 -0800 (PST)
Received: from localhost.localdomain ([222.151.198.97])
        by smtp.gmail.com with ESMTPSA id
 h9sm12059065pgk.84.2019.11.26.02.10.09
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 26 Nov 2019 02:10:12 -0800 (PST)
From: Prashant Bhole <prashantbhole.linux@gmail.com>
To: "Michael S . Tsirkin" <mst@redhat.com>,
        Jason Wang <jasowang@redhat.com>, qemu-devel@nongnu.org
Cc: Prashant Bhole <prashantbhole.linux@gmail.com>,
        "David S . Miller" <davem@davemloft.net>,
        Alexei Starovoitov <ast@kernel.org>,
        Daniel Borkmann <daniel@iogearbox.net>,
        Jakub Kicinski <jakub.kicinski@netronome.com>,
        Jesper Dangaard Brouer <hawk@kernel.org>,
        John Fastabend <john.fastabend@gmail.com>,
        Martin KaFai Lau <kafai@fb.com>,
        Song Liu <songliubraving@fb.com>, Yonghong Song <yhs@fb.com>,
        Andrii Nakryiko <andriin@fb.com>, netdev@vger.kernel.org,
        kvm@vger.kernel.org
Subject: [RFC 1/3] configure: add libbpf support
Date: Tue, 26 Nov 2019 19:09:12 +0900
Message-Id: <20191126100914.5150-2-prashantbhole.linux@gmail.com>
X-Mailer: git-send-email 2.21.0
In-Reply-To: <20191126100914.5150-1-prashantbhole.linux@gmail.com>
References: <20191126100914.5150-1-prashantbhole.linux@gmail.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is a preparation to add libbpf support for Qemu. When it is
enabled Qemu can load eBPF programs and manipulated eBPF maps
libbpf APIs.

When configured with --enable-libbpf, availability of libbpf is
checked. If it exists then CONFIG_LIBBPF is defined and the qemu
binary is linked with libbpf.

Signed-off-by: Prashant Bhole <prashantbhole.linux@gmail.com>
---
 configure | 23 +++++++++++++++++++++++
 1 file changed, 23 insertions(+)

```
#### [RFC net-next 01/18] bpf: introduce bpf_prog_offload_verifier_setup()
##### From: Prashant Bhole <prashantbhole.linux@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Prashant Bhole <prashantbhole.linux@gmail.com>
X-Patchwork-Id: 11261785
Return-Path: <SRS0=Fa6O=ZS=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 15BDB6C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 26 Nov 2019 10:08:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id EAAE220835
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 26 Nov 2019 10:08:48 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="rA6x08ok"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727800AbfKZKIr (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 26 Nov 2019 05:08:47 -0500
Received: from mail-pl1-f193.google.com ([209.85.214.193]:41684 "EHLO
        mail-pl1-f193.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727482AbfKZKIq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 26 Nov 2019 05:08:46 -0500
Received: by mail-pl1-f193.google.com with SMTP id t8so7862979plr.8;
        Tue, 26 Nov 2019 02:08:46 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=1Sl43iVtC4+YcjLflynrQtIj0zEs25bg62I/x2OEQu0=;
        b=rA6x08okN9S24McUdG2LHlghnPmhIHd24jmymmQaGlT2PAs6RXcIrFN4KgQ3vtEJQH
         ienFzUlPPNlyI9b9KsozGHG9jQpVMUrYON+jnaQvRyei7uhWiVfPBjDJK/c0EY88qnZp
         ZDkq7a+rI2J1MXnLhIb+/EQ22pDhhmb3BAM7x8wEHqFYQ02bE0rYvl/KjEMarmxBop+q
         p94+hXB+SsDfHHCvbR+iONGBx5fsJeIFS9XDNF/UJ7uD0+X9HjxSjqCZa8oiIpnB76Hg
         UUUoXmIcImh1gfbohC0t5i//haGFawSR5oYyXeA/IjzMZkOh/+g99F3i75HTqeit7+cx
         TveQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=1Sl43iVtC4+YcjLflynrQtIj0zEs25bg62I/x2OEQu0=;
        b=lUXdYO1z8ShuHf00pGQ3lfGv76p2GfSL0c171Kgr4bhMpbfML5s4IlrqtgkGiK8kf0
         znp/A5cd6LGhCTEqpAw3U3RFedFSeAp/A/V76nMEF7W1qq6LsdKJMd3zZYcK2Mk7G1d8
         EBh/O2Fc4s5e8K3QlT44wfZGJMlIfac6KhsF9pKyhiSzcROIV7g+zpp5mWauqcLH0VTF
         oGAUAJzFcZUBBBYeK0QBacNeeJ1IVVkfJQMv2UGkEtDngTIXWtbTkm1jGYO9UDvriiAi
         NswRWo3THH/oEeEVV8GsDNcFf29j9Np4vN7UiKhdFMjiJcVHj5205XcPzRD1yhf4dMJQ
         2MUQ==
X-Gm-Message-State: APjAAAUT1eZcJA1LzvTGPo0+e6lvrqCOKbGpMvkdRgyGo6mJLwUgH/Ap
        It6Wr0q0VfOrNDRu5n2uwgQ=
X-Google-Smtp-Source: 
 APXvYqxA6tuNs0G2K7BYOi/UgwxlWXR+3qbxnD5Hrpm6hj4529qhKxDgIXplkY5qr6yeBIl6U2CJIw==
X-Received: by 2002:a17:90a:5aa3:: with SMTP id
 n32mr5651673pji.97.1574762926051;
        Tue, 26 Nov 2019 02:08:46 -0800 (PST)
Received: from localhost.localdomain ([222.151.198.97])
        by smtp.gmail.com with ESMTPSA id
 s24sm11848485pfh.108.2019.11.26.02.08.42
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 26 Nov 2019 02:08:45 -0800 (PST)
From: Prashant Bhole <prashantbhole.linux@gmail.com>
To: "David S . Miller" <davem@davemloft.net>,
        "Michael S . Tsirkin" <mst@redhat.com>
Cc: Jason Wang <jasowang@redhat.com>,
        Alexei Starovoitov <ast@kernel.org>,
        Daniel Borkmann <daniel@iogearbox.net>,
        Jakub Kicinski <jakub.kicinski@netronome.com>,
        Jesper Dangaard Brouer <hawk@kernel.org>,
        John Fastabend <john.fastabend@gmail.com>,
        Martin KaFai Lau <kafai@fb.com>,
        Song Liu <songliubraving@fb.com>, Yonghong Song <yhs@fb.com>,
        Andrii Nakryiko <andriin@fb.com>, netdev@vger.kernel.org,
        qemu-devel@nongnu.org, kvm@vger.kernel.org,
        Prashant Bhole <prashantbhole.linux@gmail.com>
Subject: [RFC net-next 01/18] bpf: introduce bpf_prog_offload_verifier_setup()
Date: Tue, 26 Nov 2019 19:07:27 +0900
Message-Id: <20191126100744.5083-2-prashantbhole.linux@gmail.com>
X-Mailer: git-send-email 2.21.0
In-Reply-To: <20191126100744.5083-1-prashantbhole.linux@gmail.com>
References: <20191126100744.5083-1-prashantbhole.linux@gmail.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Jason Wang <jasowang@redhat.com>

Background:
This change was initiated from virtio_net XDP offload work. As per
the implementation plan, a copy of original program with map fds from
guest replaced with map fds from host needs to be offloaded to the
host. To implement this fd replacement, insn_hook() must provide an
insn with map fd intact. bpf_map and driver specific map data can be
derived from map_fd.

Since verifier calls all the offload callbacks after replacing map
fds, it was difficult to implement virtio_net XDP offload feature.
If virtio_net gets only one callback with original bpf program, it
will get a chance to perform the fd replacement in its own copy of the
program.

Solution:
Let's introduce a setup() callback in bpf_prog_offload_ops. It will be
non mandetory. The verifier will call it just before replacing the map
fds.

Signed-off-by: Jason Wang <jasowang@redhat.com>
Signed-off-by: Prashant Bhole <prashantbhole.linux@gmail.com>
---
 include/linux/bpf.h          |  1 +
 include/linux/bpf_verifier.h |  1 +
 kernel/bpf/offload.c         | 14 ++++++++++++++
 kernel/bpf/verifier.c        |  6 ++++++
 4 files changed, 22 insertions(+)

```
