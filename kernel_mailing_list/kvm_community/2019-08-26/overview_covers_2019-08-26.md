

#### [PATCH kernel v2 0/4] powerpc/powernv/kvm: Invalidate multiple TCEs
##### From: Alexey Kardashevskiy <aik@ozlabs.ru>

```c
From patchwork Mon Aug 26 06:17:01 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexey Kardashevskiy <aik@ozlabs.ru>
X-Patchwork-Id: 11113947
Return-Path: <SRS0=XRLU=WW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0F5B8174A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 26 Aug 2019 06:17:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id EA4D3217F4
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 26 Aug 2019 06:17:18 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729477AbfHZGRR (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 26 Aug 2019 02:17:17 -0400
Received: from ozlabs.ru ([107.173.13.209]:55914 "EHLO ozlabs.ru"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725385AbfHZGRR (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 26 Aug 2019 02:17:17 -0400
Received: from fstn1-p1.ozlabs.ibm.com (localhost [IPv6:::1])
        by ozlabs.ru (Postfix) with ESMTP id 2CD15AE80011;
        Mon, 26 Aug 2019 02:16:53 -0400 (EDT)
From: Alexey Kardashevskiy <aik@ozlabs.ru>
To: linuxppc-dev@lists.ozlabs.org
Cc: David Gibson <david@gibson.dropbear.id.au>,
        kvm-ppc@vger.kernel.org, kvm@vger.kernel.org,
        Alistair Popple <alistair@popple.id.au>,
        Alex Williamson <alex.williamson@redhat.com>,
        Michael Ellerman <mpe@ellerman.id.au>,
        Paul Mackerras <paulus@ozlabs.org>,
        Alexey Kardashevskiy <aik@ozlabs.ru>,
        Paul Mackerras <paulus@samba.org>
Subject: [PATCH kernel v2 0/4] powerpc/powernv/kvm: Invalidate multiple TCEs
 at once
Date: Mon, 26 Aug 2019 16:17:01 +1000
Message-Id: <20190826061705.92048-1-aik@ozlabs.ru>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

So far TCE cache updates (IOMMU translation cache on POWER8/9
PHB/NPU units) were barely noticeable; however with 100+GB guests
we now see RCU stall warnings in guests because we spend too much
time in the host system firmware which does actual TCE cache
updates, hence this patchset.

This is a rework of https://patchwork.ozlabs.org/patch/1149003/
This depends on KVM-PPC's bugfix: https://patchwork.ozlabs.org/patch/1152937/

I expect 1/4 to go via the PPC tree, 2/4 via the KVM-PPC tree,
3/4 via the VFIO tree and 4/4 via the PPC tree so it is a loop.
There is always a hope it can go via one tree :)


This is based on sha1
42ac26d253eb Santosh Sivaraj "powerpc: add machine check safe copy_to_user".

Please comment. Thanks.



Alexey Kardashevskiy (4):
  powerpc/powernv/ioda: Split out TCE invalidation from TCE updates
  KVM: PPC: Invalidate multiple TCEs at once
  vfio/spapr_tce: Invalidate multiple TCEs at once
  powerpc/powernv/ioda: Remove obsolete iommu_table_ops::exchange
    callbacks

 arch/powerpc/include/asm/iommu.h          | 21 ++++++---
 arch/powerpc/kernel/iommu.c               | 23 ++++++----
 arch/powerpc/kvm/book3s_64_vio.c          | 29 ++++++++----
 arch/powerpc/kvm/book3s_64_vio_hv.c       | 38 +++++++++++----
 arch/powerpc/platforms/powernv/pci-ioda.c | 56 ++++-------------------
 drivers/vfio/vfio_iommu_spapr_tce.c       | 18 +++++---
 6 files changed, 96 insertions(+), 89 deletions(-)
```
#### [PATCH 00/23] KVM: PPC: BOok3S HV: Support for nested HPT guests
##### From: Suraj Jitindar Singh <sjitindarsingh@gmail.com>

```c
From patchwork Mon Aug 26 06:20:46 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Suraj Jitindar Singh <sjitindarsingh@gmail.com>
X-Patchwork-Id: 11113961
Return-Path: <SRS0=XRLU=WW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5D9E81395
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 26 Aug 2019 06:21:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 2BD312190F
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 26 Aug 2019 06:21:18 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="Hm/X9JFG"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729540AbfHZGVR (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 26 Aug 2019 02:21:17 -0400
Received: from mail-pl1-f196.google.com ([209.85.214.196]:33894 "EHLO
        mail-pl1-f196.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725446AbfHZGVR (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 26 Aug 2019 02:21:17 -0400
Received: by mail-pl1-f196.google.com with SMTP id d3so9512940plr.1;
        Sun, 25 Aug 2019 23:21:16 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=PZm+QjbJpeqBhVMu1MgOUk3rJy79ptucuxQ3qToi7dY=;
        b=Hm/X9JFGAExB7v8O1zPkr2MP7YgJz3Rq+tx1WCNg56+4Ygck/hNaQd4g220ucrh7tA
         Va1+RBGcZuLZ54MO0BDbJBUUtMFimlPCl0Jm5SNkSGHHXbQV0+mEtsFbqE6Y0EN15yrA
         Cfew6qngvpq9DSIXSqtXSmBW8zBroGj7c575FcONqI2YvYywCJj7vWpHDumYLFKIYalM
         PKczgpO1341w/1ZRQFQ8nVtG6TlJEniMRrVTXQ2qp22PldfDLNdBmFzFsdzVcuxevVaW
         jcEY2vdYJfQCsdIqbFvYukGLVP/0dLHWaMQ0zO8gXvHqrQ6vrhfwCN2YizeDuYghfzWF
         UzTg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=PZm+QjbJpeqBhVMu1MgOUk3rJy79ptucuxQ3qToi7dY=;
        b=WCerSDS3HQ+OqDOI0AjwzGtxgOfKpirleBhDzIG69+cf4GGuRy0yxuKi5nTH1r2WcR
         UH1YVpAIZCoQYtzdUS+W2Eng8cXXsHh8on3iP0pd77T/b0o+Z/V7f0ijRkiiPAAFulbI
         G1yK0C4tSgW7tWAOT7mHd4e2r3b/P9cTZopc9f0jn6Qeu9kSvVpSLt4/p5KKsuDPnyvb
         bBnP1p8fvv/YFsHDGLzlrkJPPrp9vpAEOWGjIzLoY9Q8J/9t+16JFxDfIRojkfU1gv5V
         /WxR2zAWCLzZ+I5R5fC93/CKa42r04P79XSN3SRWAXVYyDOsEeG0H9slfJcw3DwR56vc
         d8kA==
X-Gm-Message-State: APjAAAWK536hcK048in4HHj1X2bKSQUavkxCZAqicYkRLWP6C82ZSTIk
        3uTLvh+fPRPWB0kBWGtHGA/VW8sHdAM=
X-Google-Smtp-Source: 
 APXvYqy4Pxq8ePvhXfj+ZAEL0ONi8PwLIYEp460xuzoWgKidEAPDA9nf2CvkvUf9XQZ7ySRjIOHSAQ==
X-Received: by 2002:a17:902:96a:: with SMTP id
 97mr10343227plm.264.1566800476205;
        Sun, 25 Aug 2019 23:21:16 -0700 (PDT)
Received: from surajjs2.ozlabs.ibm.com.ozlabs.ibm.com ([122.99.82.10])
        by smtp.gmail.com with ESMTPSA id
 f7sm10030353pfd.43.2019.08.25.23.21.14
        (version=TLS1_2 cipher=ECDHE-RSA-CHACHA20-POLY1305 bits=256/256);
        Sun, 25 Aug 2019 23:21:15 -0700 (PDT)
From: Suraj Jitindar Singh <sjitindarsingh@gmail.com>
To: kvm-ppc@vger.kernel.org
Cc: paulus@ozlabs.org, kvm@vger.kernel.org,
        Suraj Jitindar Singh <sjitindarsingh@gmail.com>
Subject: [PATCH 00/23] KVM: PPC: BOok3S HV: Support for nested HPT guests
Date: Mon, 26 Aug 2019 16:20:46 +1000
Message-Id: <20190826062109.7573-1-sjitindarsingh@gmail.com>
X-Mailer: git-send-email 2.13.6
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch series adds support for running a nested kvm guest which uses the hpt
(hash page table) mmu type.

Patch series based on v5.3-rc6.

The first 8 patches in this series enable a radix guest (L1) running under a
radix hypervisor (L0) to act as a guest hypervisor for it's own nested (L2)
guest where the nested guest is using hash page table translation. This mainly
involved ensuring that the guest hypervisor uses the new run_single_vcpu()
entry path and ensuring that the appropriate functions which are normally
called in the real mode entry path in book3s_hv_rmhandlers.S are called on the
new virtual mode entry path when a hpt guest is being run.

The remainder of the patches enable a (L0) hypervisor to perform hash page
table translation for a nested (L2) hpt guest which is running under one of
it's radix (L1) it's which is acting as a guest hypervisor. This primarily
required changes to the nested guest entry patch to ensure that a shadow hpt
would be allocated for the nested hpt guest, that the slb was context switched
and that the real mode entry path in book3s_hv_rmhandlers.S could be used to
enter/exit a nested hpt guest.

It was also necessary to be able to create translations by inserting ptes into
the shadow page table which provided the combination of the translation from L2
virtual address to L1 guest physical address and the translation from L1 guest
physical address to L0 host real address. Additionally invalidations of these
translations need to be handled at both levels, by L1 via the H_TLB_INVALIDATE
hcall to invalidate a L2 virtual address to L1 guest physical address
translation, and by L0 when paging out a L1 guest page which had been
subsequently mapped through to L2 thus invalidating the L1 guest physical
address to L0 host real address translation.

Still lacking support for:
Passthrough of emulated mmio devices to nested hpt guests since the current
method of reading nested guest memory relies on using quadrants which are only
available when using radix translation.

Paul Mackerras (1):
  KVM: PPC: Book3S HV: Use __gfn_to_pfn_memslot in HPT page fault
    handler

Suraj Jitindar Singh (22):
  KVM: PPC: Book3S HV: Increment mmu_notifier_seq when modifying radix
    pte rc bits
  KVM: PPC: Book3S HV: Nested: Don't allow hash guests to run nested
    guests
  KVM: PPC: Book3S HV: Handle making H_ENTER_NESTED hcall in a separate
    function
  KVM: PPC: Book3S HV: Enable calling kvmppc_hpte_hv_fault in virtual
    mode
  KVM: PPC: Book3S HV: Allow hpt manipulation hcalls to be called in
    virtual mode
  KVM: PPC: Book3S HV: Make kvmppc_invalidate_hpte() take lpid not a kvm
    struct
  KVM: PPC: Book3S HV: Nested: Allow pseries hypervisor to run hpt
    nested guest
  KVM: PPC: Book3S HV: Nested: Improve comments and naming of nest rmap
    functions
  KVM: PPC: Book3S HV: Nested: Increase gpa field in nest rmap to 46
    bits
  KVM: PPC: Book3S HV: Nested: Remove single nest rmap entries
  KVM: PPC: Book3S HV: Nested: add kvmhv_remove_all_nested_rmap_lpid()
  KVM: PPC: Book3S HV: Nested: Infrastructure for nested hpt guest setup
  KVM: PPC: Book3S HV: Nested: Context switch slb for nested hpt guest
  KVM: PPC: Book3S HV: Store lpcr and hdec_exp in the vcpu struct
  KVM: PPC: Book3S HV: Nested: Make kvmppc_run_vcpu() entry path nested
    capable
  KVM: PPC: Book3S HV: Nested: Rename kvmhv_xlate_addr_nested_radix
  KVM: PPC: Book3S HV: Separate out hashing from
    kvmppc_hv_find_lock_hpte()
  KVM: PPC: Book3S HV: Nested: Implement nested hpt mmu translation
  KVM: PPC: Book3S HV: Nested: Handle tlbie hcall for nested hpt guest
  KVM: PPC: Book3S HV: Nested: Implement nest rmap invalidations for hpt
    guests
  KVM: PPC: Book3S HV: Nested: Enable nested hpt guests
  KVM: PPC: Book3S HV: Add nested hpt pte information to debugfs

 arch/powerpc/include/asm/book3s/64/mmu-hash.h |   15 +
 arch/powerpc/include/asm/book3s/64/mmu.h      |    9 +
 arch/powerpc/include/asm/hvcall.h             |   36 -
 arch/powerpc/include/asm/kvm_asm.h            |    5 +
 arch/powerpc/include/asm/kvm_book3s.h         |   30 +-
 arch/powerpc/include/asm/kvm_book3s_64.h      |   87 +-
 arch/powerpc/include/asm/kvm_host.h           |   57 +
 arch/powerpc/include/asm/kvm_ppc.h            |    5 +-
 arch/powerpc/kernel/asm-offsets.c             |    5 +
 arch/powerpc/kvm/book3s.c                     |    1 +
 arch/powerpc/kvm/book3s_64_mmu_hv.c           |  136 ++-
 arch/powerpc/kvm/book3s_64_mmu_radix.c        |  167 +--
 arch/powerpc/kvm/book3s_hv.c                  |  327 ++++--
 arch/powerpc/kvm/book3s_hv_builtin.c          |   33 +-
 arch/powerpc/kvm/book3s_hv_interrupts.S       |   25 +-
 arch/powerpc/kvm/book3s_hv_nested.c           | 1381 ++++++++++++++++++++++---
 arch/powerpc/kvm/book3s_hv_rm_mmu.c           |  298 ++++--
 arch/powerpc/kvm/book3s_hv_rmhandlers.S       |  126 ++-
 arch/powerpc/kvm/book3s_xive.h                |   15 +
 arch/powerpc/kvm/powerpc.c                    |    3 +-
 20 files changed, 2136 insertions(+), 625 deletions(-)
```
#### [PATCH 0/2]: KVM: x86: Fix INIT signal handling in various CPU states
##### From: Liran Alon <liran.alon@oracle.com>

```c
From patchwork Mon Aug 26 10:24:47 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Liran Alon <liran.alon@oracle.com>
X-Patchwork-Id: 11114333
Return-Path: <SRS0=XRLU=WW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3C7BF14E5
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 26 Aug 2019 10:25:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1A42A217F5
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 26 Aug 2019 10:25:47 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="scv5mNbj"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730020AbfHZKZo (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 26 Aug 2019 06:25:44 -0400
Received: from aserp2120.oracle.com ([141.146.126.78]:42590 "EHLO
        aserp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729960AbfHZKZn (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 26 Aug 2019 06:25:43 -0400
Received: from pps.filterd (aserp2120.oracle.com [127.0.0.1])
        by aserp2120.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 x7QANsM2180794;
        Mon, 26 Aug 2019 10:25:10 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : mime-version : content-transfer-encoding;
 s=corp-2019-08-05; bh=wE+aQuhohhsLT2Z0OcpD+5HotwrzSl3jHizphpm4ABk=;
 b=scv5mNbjjORLe7jmth49adhP/aICRH5W3vsJ/onOBV+fJ4FJzsyOSg1kcERTPZVQKzbv
 QSa1btA3tEx6RUxywBPeFj7AdKLlFEasSP0RogUh+FjVTlFdAjJPBr6BU6PgKNFvQfB8
 9xmkh39IaBzUtwIdZ+W9bySie1QBL+dAruLU/QX5+ZZhNkLlyGI5riAcA4RSR9byrS3V
 EU2dBE2eCs681+BBbrsQTFM8pnpd44x6PAwH+zuNsVlwpoOUeewyTu/XQSS3IedqURho
 Jf01aqBXBoonOzEgFjpx0YzH6C+IHJr7KovmpMZ6E/kQ0J65Z36907A67Q4g8fBxtbSw iQ==
Received: from aserp3020.oracle.com (aserp3020.oracle.com [141.146.126.70])
        by aserp2120.oracle.com with ESMTP id 2ujw700523-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 26 Aug 2019 10:25:10 +0000
Received: from pps.filterd (aserp3020.oracle.com [127.0.0.1])
        by aserp3020.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 x7QANW9G000788;
        Mon, 26 Aug 2019 10:25:10 GMT
Received: from aserv0122.oracle.com (aserv0122.oracle.com [141.146.126.236])
        by aserp3020.oracle.com with ESMTP id 2ujw79csj9-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 26 Aug 2019 10:25:10 +0000
Received: from abhmp0006.oracle.com (abhmp0006.oracle.com [141.146.116.12])
        by aserv0122.oracle.com (8.14.4/8.14.4) with ESMTP id x7QAP9Wt001547;
        Mon, 26 Aug 2019 10:25:09 GMT
Received: from spark.ravello.local (/213.57.127.2)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Mon, 26 Aug 2019 10:25:09 +0000
From: Liran Alon <liran.alon@oracle.com>
To: pbonzini@redhat.com, rkrcmar@redhat.com, kvm@vger.kernel.org
Cc: sean.j.christopherson@intel.com, jmattson@google.com,
        vkuznets@redhat.com
Subject: [PATCH 0/2]: KVM: x86: Fix INIT signal handling in various CPU states
Date: Mon, 26 Aug 2019 13:24:47 +0300
Message-Id: <20190826102449.142687-1-liran.alon@oracle.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9360
 signatures=668684
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=0
 malwarescore=0
 phishscore=0 bulkscore=0 spamscore=0 mlxscore=0 mlxlogscore=902
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.0.1-1906280000 definitions=main-1908260115
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9360
 signatures=668684
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 priorityscore=1501 malwarescore=0
 suspectscore=0 phishscore=0 bulkscore=0 spamscore=0 clxscore=1015
 lowpriorityscore=0 mlxscore=0 impostorscore=0 mlxlogscore=963 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.0.1-1906280000
 definitions=main-1908260116
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

This patch series aims to fix how KVM handles INIT signal in various CPU
states.

1st patch just introduce a new exit-reason that should be reported to
guest in case vCPU runs in VMX non-root mode and INIT signal is
received.

The 2nd patch is the fix itself. For more information, refer to
commit message of patch.

I have also writen kvm-unit-tests to verify this code. I will
submit it as a separate patch-series.

Regards,
-Liran
```
#### [kvm-unit-tests PATCH v3 0/5] s390x: More emulation tests
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
From patchwork Mon Aug 26 16:34:57 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11115051
Return-Path: <SRS0=XRLU=WW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 743B41800
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 26 Aug 2019 16:35:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5CBAE21852
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 26 Aug 2019 16:35:21 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732452AbfHZQfU (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 26 Aug 2019 12:35:20 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:28698 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727261AbfHZQfU (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 26 Aug 2019 12:35:20 -0400
Received: from pps.filterd (m0098419.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 x7QGOPFi026504
        for <kvm@vger.kernel.org>; Mon, 26 Aug 2019 12:35:18 -0400
Received: from e06smtp04.uk.ibm.com (e06smtp04.uk.ibm.com [195.75.94.100])
        by mx0b-001b2d01.pphosted.com with ESMTP id 2umjea1hsm-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Mon, 26 Aug 2019 12:35:18 -0400
Received: from localhost
        by e06smtp04.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Mon, 26 Aug 2019 17:35:17 +0100
Received: from b06cxnps3075.portsmouth.uk.ibm.com (9.149.109.195)
        by e06smtp04.uk.ibm.com (192.168.101.134) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Mon, 26 Aug 2019 17:35:14 +0100
Received: from d06av25.portsmouth.uk.ibm.com (d06av25.portsmouth.uk.ibm.com
 [9.149.105.61])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id x7QGZDem38338702
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 26 Aug 2019 16:35:13 GMT
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 379C111C04A;
        Mon, 26 Aug 2019 16:35:13 +0000 (GMT)
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 0663711C054;
        Mon, 26 Aug 2019 16:35:12 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.145.27.33])
        by d06av25.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Mon, 26 Aug 2019 16:35:11 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, david@redhat.com, thuth@redhat.com
Subject: [kvm-unit-tests PATCH v3 0/5] s390x: More emulation tests
Date: Mon, 26 Aug 2019 18:34:57 +0200
X-Mailer: git-send-email 2.17.0
X-TM-AS-GCONF: 00
x-cbid: 19082616-0016-0000-0000-000002A32DF1
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19082616-0017-0000-0000-000033037537
Message-Id: <20190826163502.1298-1-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-08-26_08:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=858 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1906280000 definitions=main-1908260162
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The first patch allows for CECSIM booting via PSW restart.
The other ones add diag288 and STSI tests, as well as diag308 subcode 0.

v3:
* Addressed review
* Added review-bys

v2:

* Tested under TCG
* Split out stsi into library
* Addressed review

Janosch Frank (5):
  s390x: Support PSW restart boot
  s390x: Diag288 test
  s390x: Move stsi to library
  s390x: STSI tests
  s390x: Add diag308 subcode 0 testing

 lib/s390x/asm/arch_def.h |  17 +++++
 s390x/Makefile           |   2 +
 s390x/cstart64.S         |  27 ++++++++
 s390x/diag288.c          | 130 +++++++++++++++++++++++++++++++++++++++
 s390x/diag308.c          |  31 +++-------
 s390x/flat.lds           |  14 +++--
 s390x/skey.c             |  18 ------
 s390x/stsi.c             |  84 +++++++++++++++++++++++++
 s390x/unittests.cfg      |   7 +++
 9 files changed, 286 insertions(+), 44 deletions(-)
 create mode 100644 s390x/diag288.c
 create mode 100644 s390x/stsi.c
```
#### [PATCH 0/4] Introduce variable length mdev alias
##### From: Parav Pandit <parav@mellanox.com>

```c
From patchwork Mon Aug 26 20:41:15 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Parav Pandit <parav@mellanox.com>
X-Patchwork-Id: 11115519
Return-Path: <SRS0=XRLU=WW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E394614DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 26 Aug 2019 20:41:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id CB0AF21872
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 26 Aug 2019 20:41:35 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727538AbfHZUle (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 26 Aug 2019 16:41:34 -0400
Received: from mail-il-dmz.mellanox.com ([193.47.165.129]:37882 "EHLO
        mellanox.co.il" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1727901AbfHZUle (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 26 Aug 2019 16:41:34 -0400
Received: from Internal Mail-Server by MTLPINE1 (envelope-from
 parav@mellanox.com)
        with ESMTPS (AES256-SHA encrypted); 26 Aug 2019 23:41:27 +0300
Received: from sw-mtx-036.mtx.labs.mlnx (sw-mtx-036.mtx.labs.mlnx
 [10.12.150.149])
        by labmailer.mlnx (8.13.8/8.13.8) with ESMTP id x7QKfPDO021168;
        Mon, 26 Aug 2019 23:41:26 +0300
From: Parav Pandit <parav@mellanox.com>
To: alex.williamson@redhat.com, jiri@mellanox.com,
        kwankhede@nvidia.com, cohuck@redhat.com, davem@davemloft.net
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        netdev@vger.kernel.org, Parav Pandit <parav@mellanox.com>
Subject: [PATCH 0/4] Introduce variable length mdev alias
Date: Mon, 26 Aug 2019 15:41:15 -0500
Message-Id: <20190826204119.54386-1-parav@mellanox.com>
X-Mailer: git-send-email 2.19.2
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

To have consistent naming for the netdevice of a mdev and to have
consistent naming of the devlink port [1] of a mdev, which is formed using
phys_port_name of the devlink port, current UUID is not usable because
UUID is too long.

UUID in string format is 36-characters long and in binary 128-bit.
Both formats are not able to fit within 15 characters limit of netdev
name.

It is desired to have mdev device naming consistent using UUID.
So that widely used user space framework such as ovs [2] can make use
of mdev representor in similar way as PCIe SR-IOV VF and PF representors.

Hence,
(a) mdev alias is created which is derived using sha1 from the mdev name.
(b) Vendor driver describes how long an alias should be for the child mdev
created for a given parent.
(c) Mdev aliases are unique at system level.
(d) alias is created optionally whenever parent requested.
This ensures that non networking mdev parents can function without alias
creation overhead.

This design is discussed at [3].

An example systemd/udev extension will have,

1. netdev name created using mdev alias available in sysfs.

mdev UUID=83b8f4f2-509f-382f-3c1e-e6bfe0fa1001
mdev 12 character alias=cd5b146a80a5

netdev name of this mdev = enmcd5b146a80a5
Here en = Ethernet link
m = mediated device

2. devlink port phys_port_name created using mdev alias.
devlink phys_port_name=pcd5b146a80a5

This patchset enables mdev core to maintain unique alias for a mdev.

Patch-1 Introduces mdev alias using sha1.
Patch-2 Ensures that mdev alias is unique in a system.
Patch-3 Exposes mdev alias in a sysfs hirerchy.
Patch-4 Extends mtty driver to optionally provide alias generation.
This also enables to test UUID based sha1 collision and trigger
error handling for duplicate sha1 results.

In future when networking driver wants to use mdev alias, mdev_alias()
API will be added to derive devlink port name.

[1] http://man7.org/linux/man-pages/man8/devlink-port.8.html
[2] https://docs.openstack.org/os-vif/latest/user/plugins/ovs.html
[3] https://patchwork.kernel.org/cover/11084231/

Parav Pandit (4):
  mdev: Introduce sha1 based mdev alias
  mdev: Make mdev alias unique among all mdevs
  mdev: Expose mdev alias in sysfs tree
  mtty: Optionally support mtty alias

 drivers/vfio/mdev/mdev_core.c    | 103 ++++++++++++++++++++++++++++++-
 drivers/vfio/mdev/mdev_private.h |   5 +-
 drivers/vfio/mdev/mdev_sysfs.c   |  26 ++++++--
 include/linux/mdev.h             |   4 ++
 samples/vfio-mdev/mtty.c         |  10 +++
 5 files changed, 139 insertions(+), 9 deletions(-)
```
