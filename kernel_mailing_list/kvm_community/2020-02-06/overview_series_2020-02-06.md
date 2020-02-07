#### [PATCH 1/1] vfio-pci/nvlink2: Allow fallback to ibm,mmio-atsd[0]
##### From: Sam Bobroff <sbobroff@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sam Bobroff <sbobroff@linux.ibm.com>
X-Patchwork-Id: 11367603
Return-Path: <SRS0=ZRkH=32=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5D17014D5
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  6 Feb 2020 03:17:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 3C6B920674
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  6 Feb 2020 03:17:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727663AbgBFDRd (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 5 Feb 2020 22:17:33 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:7152 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727572AbgBFDRd (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 5 Feb 2020 22:17:33 -0500
Received: from pps.filterd (m0098413.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 0163Dgfx094664
        for <kvm@vger.kernel.org>; Wed, 5 Feb 2020 22:17:31 -0500
Received: from e06smtp07.uk.ibm.com (e06smtp07.uk.ibm.com [195.75.94.103])
        by mx0b-001b2d01.pphosted.com with ESMTP id 2xyhmhvpef-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Wed, 05 Feb 2020 22:17:31 -0500
Received: from localhost
        by e06smtp07.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <sbobroff@linux.ibm.com>;
        Thu, 6 Feb 2020 03:17:29 -0000
Received: from b06cxnps4075.portsmouth.uk.ibm.com (9.149.109.197)
        by e06smtp07.uk.ibm.com (192.168.101.137) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Thu, 6 Feb 2020 03:17:28 -0000
Received: from d06av24.portsmouth.uk.ibm.com (d06av24.portsmouth.uk.ibm.com
 [9.149.105.60])
        by b06cxnps4075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 0163HROY47775860
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 6 Feb 2020 03:17:27 GMT
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 3881E4203F;
        Thu,  6 Feb 2020 03:17:27 +0000 (GMT)
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id D7DEF42041;
        Thu,  6 Feb 2020 03:17:26 +0000 (GMT)
Received: from ozlabs.au.ibm.com (unknown [9.192.253.14])
        by d06av24.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Thu,  6 Feb 2020 03:17:26 +0000 (GMT)
Received: from osmium.ozlabs.ibm.com (haven.au.ibm.com [9.192.254.114])
        (using TLSv1.2 with cipher DHE-RSA-AES128-GCM-SHA256 (128/128 bits))
        (No client certificate requested)
        by ozlabs.au.ibm.com (Postfix) with ESMTPSA id AB959A00EE;
        Thu,  6 Feb 2020 14:17:22 +1100 (AEDT)
From: Sam Bobroff <sbobroff@linux.ibm.com>
To: kvm@vger.kernel.org, linuxppc-dev@lists.ozlabs.org
Cc: aik@ozlabs.ru
Subject: [PATCH 1/1] vfio-pci/nvlink2: Allow fallback to ibm,mmio-atsd[0]
Date: Thu,  6 Feb 2020 14:17:25 +1100
X-Mailer: git-send-email 2.22.0.216.g00a2a96fc9
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 20020603-0028-0000-0000-000003D7D5E5
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 20020603-0029-0000-0000-0000249C365F
Message-Id: 
 <426f75e09ac1a6879a6d51f592bf683c698b4bda.1580959044.git.sbobroff@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-02-05_06:2020-02-04,2020-02-05 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 phishscore=0 clxscore=1011
 impostorscore=0 malwarescore=0 priorityscore=1501 adultscore=0
 mlxlogscore=999 suspectscore=0 bulkscore=0 lowpriorityscore=0 spamscore=0
 mlxscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2001150001 definitions=main-2002060023
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Older versions of skiboot only provide a single value in the device
tree property "ibm,mmio-atsd", even when multiple Address Translation
Shoot Down (ATSD) registers are present. This prevents NVLink2 devices
(other than the first) from being used with vfio-pci because vfio-pci
expects to be able to assign a dedicated ATSD register to each NVLink2
device.

However, ATSD registers can be shared among devices. This change
allows vfio-pci to fall back to sharing the register at index 0 if
necessary.

Signed-off-by: Sam Bobroff <sbobroff@linux.ibm.com>
Reviewed-by: Alexey Kardashevskiy <aik@ozlabs.ru>
---
 drivers/vfio/pci/vfio_pci_nvlink2.c | 13 +++++++++++--
 1 file changed, 11 insertions(+), 2 deletions(-)

```
#### [PATCH v2 01/27] docs: kvm: add arm/pvtime.rst to index.rst
##### From: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
X-Patchwork-Id: 11368549
Return-Path: <SRS0=ZRkH=32=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A1EB21398
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  6 Feb 2020 14:50:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 74227218AC
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  6 Feb 2020 14:50:43 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1581000643;
	bh=RQJBSrCBQoRjRPzNpPiEOUwoi4zmhWHM5Ddo22O4ojU=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=urqdGx3PpgWsLoF2rk2ibcB1uD2v0pA3ydRcVzy26fA5NUb0N0OvH8sOpC3RMrktk
	 3AF/gd6wOQTxY2acT9CA7cRDidVW2+pBxd768hOmJ3rlvOAQMIME/SJCVHyn3RzGWH
	 4F57zJqPT1LOBviGWSbLvee63lQtHiz6zZmL6+Zg=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727698AbgBFOum (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 6 Feb 2020 09:50:42 -0500
Received: from bombadil.infradead.org ([198.137.202.133]:55590 "EHLO
        bombadil.infradead.org" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727600AbgBFOuj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 6 Feb 2020 09:50:39 -0500
DKIM-Signature: v=1; a=rsa-sha256; q=dns/txt; c=relaxed/relaxed;
        d=infradead.org; s=bombadil.20170209;
 h=Sender:Content-Transfer-Encoding:
        MIME-Version:References:In-Reply-To:Message-Id:Date:Subject:Cc:To:From:
        Reply-To:Content-Type:Content-ID:Content-Description;
        bh=/hfBTm+pwI/qMUzI6610HUXH01FV0FRb49kTIzGz0Ww=;
 b=LfpvsZBaXM5g9XucN26IWuUeSw
        ZVGgsj7wgaRPNQBmLfaAdDJKH0YaGTMakxkpr8DD8YykhTx7bc5q6wqCk1n0hjpRZTN2jQmxmCDvF
        ZhvBwfHRUrUEcTJDIhG41uCZFPnAUYoNIg6ooDr1+f/s+C3RsWUTnOgjf1j4+BIlYZ4J9Cm+RUBAz
        eOPOtMfkwYT++sjrD/kl+kH+LOKKKS1b8FpLOopc4yvsdaq4VU6HVtiyxaILTD22ziSaXaPaGdW5F
        3bIresYAibGbzgfYUw0A0s9LxsZIn+jtjLQMTyN9zROlAVSwL4gO22kWdp2CGpwTm9/8/24/6tXcc
        cMvxHJzA==;
Received: from [179.95.15.160] (helo=bombadil.infradead.org)
        by bombadil.infradead.org with esmtpsa (Exim 4.92.3 #3 (Red Hat
 Linux))
        id 1iziUI-0004Ik-V2; Thu, 06 Feb 2020 14:50:38 +0000
Received: from mchehab by bombadil.infradead.org with local (Exim 4.92.3)
        (envelope-from <mchehab@bombadil.infradead.org>)
        id 1iziU6-002nKL-7F; Thu, 06 Feb 2020 15:50:26 +0100
From: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
To: Linux Media Mailing List <linux-media@vger.kernel.org>
Cc: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>,
        Mauro Carvalho Chehab <mchehab@infradead.org>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Jonathan Corbet <corbet@lwn.net>, kvm@vger.kernel.org,
        linux-doc@vger.kernel.org
Subject: [PATCH v2 01/27] docs: kvm: add arm/pvtime.rst to index.rst
Date: Thu,  6 Feb 2020 15:49:58 +0100
Message-Id: 
 <cdea3a1899e21395073b8e4a02fb3db88dc63974.1581000481.git.mchehab+huawei@kernel.org>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <cover.1581000481.git.mchehab+huawei@kernel.org>
References: <cover.1581000481.git.mchehab+huawei@kernel.org>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add this file to a new kvm/arm index.rst, in order for it to
be shown as part of the virt book.

Signed-off-by: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
---
 Documentation/virt/kvm/arm/index.rst | 10 ++++++++++
 Documentation/virt/kvm/index.rst     |  2 ++
 2 files changed, 12 insertions(+)
 create mode 100644 Documentation/virt/kvm/arm/index.rst

diff --git a/Documentation/virt/kvm/arm/index.rst b/Documentation/virt/kvm/arm/index.rst
new file mode 100644
index 000000000000..e039d9b1e076
--- /dev/null
+++ b/Documentation/virt/kvm/arm/index.rst
@@ -0,0 +1,10 @@
+.. SPDX-License-Identifier: GPL-2.0
+
+===
+ARM
+===
+
+.. toctree::
+   :maxdepth: 2
+
+   pvtime
```
#### [GIT PULL] Second batch of KVM changes for 5.6 merge window
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11368669
Return-Path: <SRS0=ZRkH=32=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8419F924
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  6 Feb 2020 15:10:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 59FA221741
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  6 Feb 2020 15:10:47 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="pDMRkwPJ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727762AbgBFPKk (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 6 Feb 2020 10:10:40 -0500
Received: from mail-wr1-f66.google.com ([209.85.221.66]:45323 "EHLO
        mail-wr1-f66.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727481AbgBFPKi (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 6 Feb 2020 10:10:38 -0500
Received: by mail-wr1-f66.google.com with SMTP id a6so7592925wrx.12;
        Thu, 06 Feb 2020 07:10:35 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id;
        bh=y0Ojwov/p4Jd1JXFXjHbwQfCbylx1jkuhxgufPLa1OA=;
        b=pDMRkwPJqrBih1TASmqx/inhRtwNlegH4FgcuQa+x+0CuZ1W4in1lZNkwWLXutEDYZ
         12nmARn2+gmNSdGIYBSmmQsMzLOAe9RrR0CUvsiT9GjIrSAmwCHjAWtjWtxxYwIIFcLI
         8D0lrNW0ARRm/4Y9m4gA2FOU5ULq0CPMfBtQiRIdgjKwmvGaPIWP/ut6kBSxt5RPrlA6
         Zkcixz2Afs8bnRPmo7sQrszeJPHFJA7lHDpp9YH9TAgizTAipHcgahKaS8mOTifKnbYM
         gc+xXupHP0pkrL8u98nyQoQc7JmnVs2PkGRc70RMfiwNaR0i1JHXpwVAoNlJfKdsIQsz
         HUNA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id;
        bh=y0Ojwov/p4Jd1JXFXjHbwQfCbylx1jkuhxgufPLa1OA=;
        b=E+49KTC9RKh9L2FBcp2YK1dUMp1AaCXZc8lj95NeLkjk3Cn2VK3A/DDGozUCk3yost
         yUj5cL7iuHlDDZHRaQJ7DUfRM1MejcyDu8kjn37I+O8dcz2KjZF1kMrR+6Kd7rgBz+2q
         530/E3vU5QQnj51Xth/REkS8Zj9lq+ZVzp58gA6Trrj1eLOSBcs2Op5y0KcwmcywfbNe
         KqlJTxm0lV3VNRYHgCkDPxveM+4yeYHuoHWUf496SyxCzE6fsHJKEnm93HhGWtIl9cMl
         QBFGtQifpu0NzkVSriRE9Gt9OHyb7TPifeQbbMVTBBRXWg03cVv2fr36GWbcE6c4EKFz
         kKjQ==
X-Gm-Message-State: APjAAAWWrTFz02E5kMH9UK8u1oy7dygbXCGOLEb38WBK6+oHceS/BVP+
        Js8QFTXErhJtleHK5gWp2MAZ4pIL
X-Google-Smtp-Source: 
 APXvYqx2ijJjkVCaZvijNI6ErmO4C3TqUYvFIXxr/sRwhZDfu7TKh1eWF55YylJGpsaCn1bwx5lUMA==
X-Received: by 2002:adf:ca07:: with SMTP id o7mr4135355wrh.49.1581001834954;
        Thu, 06 Feb 2020 07:10:34 -0800 (PST)
Received: from 640k.localdomain.com ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 r5sm4471032wrt.43.2020.02.06.07.10.33
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Thu, 06 Feb 2020 07:10:34 -0800 (PST)
From: Paolo Bonzini <pbonzini@redhat.com>
To: torvalds@linux-foundation.org
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [GIT PULL] Second batch of KVM changes for 5.6 merge window
Date: Thu,  6 Feb 2020 16:10:31 +0100
Message-Id: <1581001831-17609-1-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Linus,

The following changes since commit e813e65038389b66d2f8dd87588694caf8dc2923:

  Merge tag 'kvm-5.6-1' of git://git.kernel.org/pub/scm/virt/kvm/kvm (2020-01-31 09:30:41 -0800)

are available in the git repository at:


  https://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/kvm-5.6-2

for you to fetch changes up to a8be1ad01b795bd2a13297ddbaecdb956ab0efd0:

  KVM: vmx: delete meaningless vmx_decache_cr0_guest_bits() declaration (2020-02-05 16:44:06 +0100)

----------------------------------------------------------------
s390:
* fix register corruption
* ENOTSUPP/EOPNOTSUPP mixed
* reset cleanups/fixes
* selftests

x86:
* Bug fixes and cleanups
* AMD support for APIC virtualization even in combination with
  in-kernel PIT or IOAPIC.

MIPS:
* Compilation fix.

Generic:
* Fix refcount overflow for zero page.

----------------------------------------------------------------
Ben Gardon (2):
      kvm: mmu: Replace unsigned with unsigned int for PTE access
      kvm: mmu: Separate generating and setting mmio ptes

Christian Borntraeger (2):
      KVM: s390: ENOTSUPP -> EOPNOTSUPP fixups
      KVM: s390: do not clobber registers during guest reset/store status

Eric Hankland (1):
      KVM: x86: Fix perfctr WRMSR for running counters

Janosch Frank (4):
      KVM: s390: Cleanup initial cpu reset
      KVM: s390: Add new reset vcpu API
      selftests: KVM: Add fpu and one reg set/get library functions
      selftests: KVM: s390x: Add reset tests

Miaohe Lin (2):
      KVM: nVMX: delete meaningless nested_vmx_run() declaration
      KVM: vmx: delete meaningless vmx_decache_cr0_guest_bits() declaration

Paolo Bonzini (7):
      KVM: x86: remove get_enable_apicv from kvm_x86_ops
      KVM: SVM: allow AVIC without split irqchip
      KVM: x86: reorganize pvclock_gtod_data members
      KVM: x86: use raw clock values consistently
      KVM: SVM: relax conditions for allowing MSR_IA32_SPEC_CTRL accesses
      Merge tag 'kvm-s390-next-5.6-1' of git://git.kernel.org/.../kvms390/linux into HEAD
      x86: vmxfeatures: rename features for consistency with KVM and manual

Pierre Morel (1):
      selftests: KVM: testing the local IRQs resets

Sean Christopherson (5):
      KVM: x86: Take a u64 when checking for a valid dr7 value
      KVM: MIPS: Fix a build error due to referencing not-yet-defined function
      KVM: MIPS: Fold comparecount_func() into comparecount_wakeup()
      KVM: nVMX: Remove stale comment from nested_vmx_load_cr3()
      KVM: x86: Mark CR4.UMIP as reserved based on associated CPUID bit

Suravee Suthikulpanit (15):
      kvm: lapic: Introduce APICv update helper function
      kvm: x86: Introduce APICv inhibit reason bits
      kvm: x86: Add support for dynamic APICv activation
      kvm: x86: Add APICv (de)activate request trace points
      kvm: x86: svm: Add support to (de)activate posted interrupts
      KVM: svm: avic: Add support for dynamic setup/teardown of virtual APIC backing page
      kvm: x86: Introduce APICv x86 ops for checking APIC inhibit reasons
      kvm: x86: Introduce x86 ops hook for pre-update APICv
      svm: Add support for dynamic APICv
      kvm: x86: hyperv: Use APICv update request interface
      svm: Deactivate AVIC when launching guest with nested SVM support
      svm: Temporarily deactivate AVIC during ExtINT handling
      kvm: i8254: Deactivate APICv when using in-kernel PIT re-injection mode.
      kvm: ioapic: Refactor kvm_ioapic_update_eoi()
      kvm: ioapic: Lazy update IOAPIC EOI

Thadeu Lima de Souza Cascardo (1):
      x86/kvm: do not setup pv tlb flush when not paravirtualized

Vitaly Kuznetsov (2):
      x86/kvm/hyper-v: move VMX controls sanitization out of nested_enable_evmcs()
      x86/kvm/hyper-v: don't allow to turn on unsupported VMX controls for nested guests

Zhuang Yanying (1):
      KVM: fix overflow of zero page refcount with ksm running

 Documentation/virt/kvm/api.txt                 |  43 ++++++
 arch/mips/kvm/mips.c                           |  37 ++---
 arch/s390/include/asm/kvm_host.h               |   5 +
 arch/s390/kvm/interrupt.c                      |   6 +-
 arch/s390/kvm/kvm-s390.c                       |  92 +++++++-----
 arch/x86/include/asm/kvm_host.h                |  18 ++-
 arch/x86/include/asm/vmx.h                     |   6 +-
 arch/x86/include/asm/vmxfeatures.h             |   6 +-
 arch/x86/kernel/kvm.c                          |   3 +
 arch/x86/kvm/hyperv.c                          |   5 +-
 arch/x86/kvm/i8254.c                           |  12 ++
 arch/x86/kvm/ioapic.c                          | 149 ++++++++++++-------
 arch/x86/kvm/lapic.c                           |  22 ++-
 arch/x86/kvm/lapic.h                           |   1 +
 arch/x86/kvm/mmu/mmu.c                         |  37 +++--
 arch/x86/kvm/svm.c                             | 166 ++++++++++++++++++---
 arch/x86/kvm/trace.h                           |  19 +++
 arch/x86/kvm/vmx/evmcs.c                       |  85 ++++++++++-
 arch/x86/kvm/vmx/evmcs.h                       |   3 +
 arch/x86/kvm/vmx/nested.c                      |  13 +-
 arch/x86/kvm/vmx/pmu_intel.c                   |   9 +-
 arch/x86/kvm/vmx/vmx.c                         |  34 +++--
 arch/x86/kvm/x86.c                             | 139 +++++++++++------
 arch/x86/kvm/x86.h                             |   2 +-
 include/uapi/linux/kvm.h                       |   5 +
 tools/testing/selftests/kvm/Makefile           |   1 +
 tools/testing/selftests/kvm/include/kvm_util.h |   6 +
 tools/testing/selftests/kvm/lib/kvm_util.c     |  36 +++++
 tools/testing/selftests/kvm/s390x/resets.c     | 197 +++++++++++++++++++++++++
 virt/kvm/kvm_main.c                            |   1 +
 30 files changed, 925 insertions(+), 233 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/s390x/resets.c
```
#### [PATCH] KVM: apic: reuse smp_wmb() in kvm_make_request()
##### From: linmiaohe <linmiaohe@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: linmiaohe <linmiaohe@huawei.com>
X-Patchwork-Id: 11367531
Return-Path: <SRS0=ZRkH=32=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D378D139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  6 Feb 2020 01:58:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B01DD20730
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  6 Feb 2020 01:58:04 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727628AbgBFB6A (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 5 Feb 2020 20:58:00 -0500
Received: from szxga05-in.huawei.com ([45.249.212.191]:9703 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1727307AbgBFB6A (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 5 Feb 2020 20:58:00 -0500
Received: from DGGEMS408-HUB.china.huawei.com (unknown [172.30.72.60])
        by Forcepoint Email with ESMTP id 49465B4B612BD9E8A9D8;
        Thu,  6 Feb 2020 09:57:57 +0800 (CST)
Received: from huawei.com (10.175.105.18) by DGGEMS408-HUB.china.huawei.com
 (10.3.19.208) with Microsoft SMTP Server id 14.3.439.0; Thu, 6 Feb 2020
 09:57:47 +0800
From: linmiaohe <linmiaohe@huawei.com>
To: <pbonzini@redhat.com>, <rkrcmar@redhat.com>,
        <sean.j.christopherson@intel.com>, <vkuznets@redhat.com>,
        <wanpengli@tencent.com>, <jmattson@google.com>, <joro@8bytes.org>,
        <tglx@linutronix.de>, <mingo@redhat.com>, <bp@alien8.de>,
        <hpa@zytor.com>
CC: <linmiaohe@huawei.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <x86@kernel.org>
Subject: [PATCH] KVM: apic: reuse smp_wmb() in kvm_make_request()
Date: Thu, 6 Feb 2020 09:59:35 +0800
Message-ID: <1580954375-5030-1-git-send-email-linmiaohe@huawei.com>
X-Mailer: git-send-email 1.8.3.1
MIME-Version: 1.0
X-Originating-IP: [10.175.105.18]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Miaohe Lin <linmiaohe@huawei.com>

There is already an smp_mb() barrier in kvm_make_request(). We reuse it
here.

Signed-off-by: Miaohe Lin <linmiaohe@huawei.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/lapic.c | 9 ++++++---
 1 file changed, 6 insertions(+), 3 deletions(-)

```
#### [PATCH] KVM: nVMX: Fix some comment typos and coding style
##### From: linmiaohe <linmiaohe@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: linmiaohe <linmiaohe@huawei.com>
X-Patchwork-Id: 11367541
Return-Path: <SRS0=ZRkH=32=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3D31414E3
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  6 Feb 2020 02:27:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 25803214AF
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  6 Feb 2020 02:27:50 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727681AbgBFC1q (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 5 Feb 2020 21:27:46 -0500
Received: from szxga04-in.huawei.com ([45.249.212.190]:10155 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1727307AbgBFC1q (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 5 Feb 2020 21:27:46 -0500
Received: from DGGEMS406-HUB.china.huawei.com (unknown [172.30.72.58])
        by Forcepoint Email with ESMTP id D2F2FD7277A99D30D65F;
        Thu,  6 Feb 2020 10:27:42 +0800 (CST)
Received: from huawei.com (10.175.105.18) by DGGEMS406-HUB.china.huawei.com
 (10.3.19.206) with Microsoft SMTP Server id 14.3.439.0; Thu, 6 Feb 2020
 10:27:32 +0800
From: linmiaohe <linmiaohe@huawei.com>
To: <pbonzini@redhat.com>, <rkrcmar@redhat.com>,
        <sean.j.christopherson@intel.com>, <vkuznets@redhat.com>,
        <wanpengli@tencent.com>, <jmattson@google.com>, <joro@8bytes.org>,
        <tglx@linutronix.de>, <mingo@redhat.com>, <bp@alien8.de>,
        <hpa@zytor.com>
CC: <linmiaohe@huawei.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <x86@kernel.org>
Subject: [PATCH] KVM: nVMX: Fix some comment typos and coding style
Date: Thu, 6 Feb 2020 10:29:22 +0800
Message-ID: <1580956162-5609-1-git-send-email-linmiaohe@huawei.com>
X-Mailer: git-send-email 1.8.3.1
MIME-Version: 1.0
X-Originating-IP: [10.175.105.18]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Miaohe Lin <linmiaohe@huawei.com>

Fix some typos in the comments. Also fix coding style.

Signed-off-by: Miaohe Lin <linmiaohe@huawei.com>
---
 arch/x86/include/asm/kvm_host.h | 2 +-
 arch/x86/kvm/vmx/nested.c       | 5 +++--
 2 files changed, 4 insertions(+), 3 deletions(-)

```
#### [PATCH v3 1/8] x86/split_lock: Export handle_user_split_lock()
##### From: Xiaoyao Li <xiaoyao.li@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xiaoyao Li <xiaoyao.li@intel.com>
X-Patchwork-Id: 11367737
Return-Path: <SRS0=ZRkH=32=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4C511924
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  6 Feb 2020 07:10:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 35B94217BA
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  6 Feb 2020 07:10:02 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727917AbgBFHJY (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 6 Feb 2020 02:09:24 -0500
Received: from mga04.intel.com ([192.55.52.120]:56103 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725895AbgBFHJX (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 6 Feb 2020 02:09:23 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga003.jf.intel.com ([10.7.209.27])
  by fmsmga104.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 05 Feb 2020 23:09:23 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,408,1574150400";
   d="scan'208";a="231957189"
Received: from lxy-dell.sh.intel.com ([10.239.13.109])
  by orsmga003.jf.intel.com with ESMTP; 05 Feb 2020 23:09:20 -0800
From: Xiaoyao Li <xiaoyao.li@intel.com>
To: Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        hpa@zytor.com, Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Andy Lutomirski <luto@kernel.org>, tony.luck@intel.com
Cc: peterz@infradead.org, fenghua.yu@intel.com, x86@kernel.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Xiaoyao Li <xiaoyao.li@intel.com>
Subject: [PATCH v3 1/8] x86/split_lock: Export handle_user_split_lock()
Date: Thu,  6 Feb 2020 15:04:05 +0800
Message-Id: <20200206070412.17400-2-xiaoyao.li@intel.com>
X-Mailer: git-send-email 2.23.0
In-Reply-To: <20200206070412.17400-1-xiaoyao.li@intel.com>
References: <20200206070412.17400-1-xiaoyao.li@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Move the EFLAGS.AC check to do_alignment_check() so that
handle_user_split_lock() can be used by KVM in the future to handle #AC
caused by split lock in guest.

Suggested-by: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Xiaoyao Li <xiaoyao.li@intel.com>
---
 arch/x86/include/asm/cpu.h  | 4 ++--
 arch/x86/kernel/cpu/intel.c | 7 ++++---
 arch/x86/kernel/traps.c     | 2 +-
 3 files changed, 7 insertions(+), 6 deletions(-)

```
#### [PATCH] KVM: x86/mmu: Avoid retpoline on ->page_fault() with TDP
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11369345
Return-Path: <SRS0=ZRkH=32=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9BB0F921
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  6 Feb 2020 22:14:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 81588217BA
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  6 Feb 2020 22:14:40 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727579AbgBFWOg (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 6 Feb 2020 17:14:36 -0500
Received: from mga18.intel.com ([134.134.136.126]:33157 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727441AbgBFWOg (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 6 Feb 2020 17:14:36 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by orsmga106.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 06 Feb 2020 14:14:35 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,411,1574150400";
   d="scan'208";a="226291753"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by fmsmga008.fm.intel.com with ESMTP; 06 Feb 2020 14:14:35 -0800
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: x86/mmu: Avoid retpoline on ->page_fault() with TDP
Date: Thu,  6 Feb 2020 14:14:34 -0800
Message-Id: <20200206221434.23790-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Wrap calls to ->page_fault() with a small shim to directly invoke the
TDP fault handler when the kernel is using retpolines and TDP is being
used.  Denote the TDP fault handler by nullifying mmu->page_fault, and
annotate the TDP path as likely to coerce the compiler into preferring
the TDP path.

Rename tdp_page_fault() to kvm_tdp_page_fault() as it's exposed outside
of mmu.c to allow inlining the shim.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---

Haven't done any performance testing, this popped into my head when mucking
with the 5-level page table crud as an easy way to shave cycles in the
happy path.

 arch/x86/kvm/mmu.h     | 13 +++++++++++++
 arch/x86/kvm/mmu/mmu.c | 16 ++++++++++------
 arch/x86/kvm/x86.c     |  2 +-
 3 files changed, 24 insertions(+), 7 deletions(-)

```
#### [PATCH 1/7] KVM: nVMX: Use correct root level for nested EPT shadow page tables
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11369343
Return-Path: <SRS0=ZRkH=32=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F3D2E1398
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  6 Feb 2020 22:09:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id DB1F222527
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  6 Feb 2020 22:09:11 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727872AbgBFWJI (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 6 Feb 2020 17:09:08 -0500
Received: from mga14.intel.com ([192.55.52.115]:64211 "EHLO mga14.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727481AbgBFWIi (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 6 Feb 2020 17:08:38 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga005.jf.intel.com ([10.7.209.41])
  by fmsmga103.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 06 Feb 2020 14:08:37 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,411,1574150400";
   d="scan'208";a="404625083"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by orsmga005.jf.intel.com with ESMTP; 06 Feb 2020 14:08:37 -0800
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH 1/7] KVM: nVMX: Use correct root level for nested EPT shadow
 page tables
Date: Thu,  6 Feb 2020 14:08:30 -0800
Message-Id: <20200206220836.22743-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20200206220836.22743-1-sean.j.christopherson@intel.com>
References: <20200206220836.22743-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hardcode the EPT page-walk level for L2 to be 4 levels, as KVM's MMU
currently also hardcodes the page walk level for nested EPT to be 4
levels.  The L2 guest is all but guaranteed to soft hang on its first
instruction when L1 is using EPT, as KVM will construct 4-level page
tables and then tell hardware to use 5-level page tables.

Fixes: 855feb673640 ("KVM: MMU: Add 5 level EPT & Shadow page table support.")
Cc: stable@vger.kernel.org
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/vmx/vmx.c | 3 +++
 1 file changed, 3 insertions(+)

```
#### [PATCH] KVM: x86: remove duplicated KVM_REQ_EVENT request
##### From: linmiaohe <linmiaohe@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: linmiaohe <linmiaohe@huawei.com>
X-Patchwork-Id: 11367523
Return-Path: <SRS0=ZRkH=32=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 25798139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  6 Feb 2020 01:44:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 0D785214AF
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  6 Feb 2020 01:44:13 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727705AbgBFBoJ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 5 Feb 2020 20:44:09 -0500
Received: from szxga05-in.huawei.com ([45.249.212.191]:9701 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1727170AbgBFBoJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 5 Feb 2020 20:44:09 -0500
Received: from DGGEMS403-HUB.china.huawei.com (unknown [172.30.72.58])
        by Forcepoint Email with ESMTP id F400A1F6CA1EBF20BB35;
        Thu,  6 Feb 2020 09:44:04 +0800 (CST)
Received: from huawei.com (10.175.105.18) by DGGEMS403-HUB.china.huawei.com
 (10.3.19.203) with Microsoft SMTP Server id 14.3.439.0; Thu, 6 Feb 2020
 09:43:55 +0800
From: linmiaohe <linmiaohe@huawei.com>
To: <pbonzini@redhat.com>, <rkrcmar@redhat.com>,
        <sean.j.christopherson@intel.com>, <vkuznets@redhat.com>,
        <wanpengli@tencent.com>, <jmattson@google.com>, <joro@8bytes.org>,
        <tglx@linutronix.de>, <mingo@redhat.com>, <bp@alien8.de>,
        <hpa@zytor.com>
CC: <linmiaohe@huawei.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <x86@kernel.org>
Subject: [PATCH] KVM: x86: remove duplicated KVM_REQ_EVENT request
Date: Thu, 6 Feb 2020 09:45:44 +0800
Message-ID: <1580953544-4778-1-git-send-email-linmiaohe@huawei.com>
X-Mailer: git-send-email 1.8.3.1
MIME-Version: 1.0
X-Originating-IP: [10.175.105.18]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Miaohe Lin <linmiaohe@huawei.com>

The KVM_REQ_EVENT request is already made in kvm_set_rflags(). We should
not make it again.

Signed-off-by: Miaohe Lin <linmiaohe@huawei.com>
---
 arch/x86/kvm/x86.c | 1 -
 1 file changed, 1 deletion(-)

```
#### [PULL 35/46] scripts: Explicit usage of Python 3 (scripts with __main__)
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
 <philmd@redhat.com>
X-Patchwork-Id: 11369159
Return-Path: <SRS0=ZRkH=32=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8CE3D138D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  6 Feb 2020 21:22:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 615DF218AC
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  6 Feb 2020 21:22:22 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="NiZHnueQ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727591AbgBFVWV (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 6 Feb 2020 16:22:21 -0500
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:23596 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726765AbgBFVWV (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 6 Feb 2020 16:22:21 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1581024138;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=HHOznj/ZLUmcjiY1djflG2PfXcttBGCcGAXARz0NWsA=;
        b=NiZHnueQuSJeAJCYu3k1SPlgCvitXXb8/r666plPhI0lHnCVgwKUSukKWU3/3o1jE0yIcB
        DMTXMFfi/6WXYwrml1S0M4koutesSDJjB6G4Dfhpo6yWYF9Ii3P3HruWYxZGaG3FOG1CLN
        iMoMYYfJUq/zV0oj/m8xpgIaVIks/5o=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-424-sEABhFsTMJic7gR3Hyvlpg-1; Thu, 06 Feb 2020 16:22:12 -0500
X-MC-Unique: sEABhFsTMJic7gR3Hyvlpg-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id B5047106BC09;
        Thu,  6 Feb 2020 21:22:11 +0000 (UTC)
Received: from x1w.redhat.com (ovpn-204-120.brq.redhat.com [10.40.204.120])
        by smtp.corp.redhat.com (Postfix) with ESMTPS id 90BFD60BEC;
        Thu,  6 Feb 2020 21:21:55 +0000 (UTC)
From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>
To: qemu-devel@nongnu.org
Cc: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>,
 Cleber Rosa <crosa@redhat.com>, Eduardo Habkost <ehabkost@redhat.com>,
 Vladimir Sementsov-Ogievskiy <vsementsov@virtuozzo.com>, =?utf-8?q?Daniel_P?=
	=?utf-8?q?_=2E_Berrang=C3=A9?= <berrange@redhat.com>,
 Stefan Hajnoczi <stefanha@redhat.com>, Juan Quintela <quintela@redhat.com>,
 Paolo Bonzini <pbonzini@redhat.com>, Richard Henderson <rth@twiddle.net>,
 Markus Armbruster <armbru@redhat.com>,
 Michael Roth <mdroth@linux.vnet.ibm.com>,
 "Dr. David Alan Gilbert" <dgilbert@redhat.com>,
 kvm@vger.kernel.org (open list:Overall KVM CPUs)
Subject: [PULL 35/46] scripts: Explicit usage of Python 3 (scripts with
 __main__)
Date: Thu,  6 Feb 2020 22:19:25 +0100
Message-Id: <20200206211936.17098-36-philmd@redhat.com>
In-Reply-To: <20200206211936.17098-1-philmd@redhat.com>
References: <20200206211936.17098-1-philmd@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Use the program search path to find the Python 3 interpreter.

Patch created mechanically by running:

  $ sed -i "s,^#\!/usr/bin/\(env\ \)\?python$,#\!/usr/bin/env python3," \
       $(git grep -l 'if __name__.*__main__')

Reported-by: Vladimir Sementsov-Ogievskiy <vsementsov@virtuozzo.com>
Suggested-by: Daniel P. Berrangé <berrange@redhat.com>
Suggested-by: Stefan Hajnoczi <stefanha@redhat.com>
Reviewed-by: Juan Quintela <quintela@redhat.com>
Acked-by: Stefan Hajnoczi <stefanha@redhat.com>
Acked-by: Paolo Bonzini <pbonzini@redhat.com>
Message-Id: <20200130163232.10446-6-philmd@redhat.com>
Signed-off-by: Philippe Mathieu-Daudé <philmd@redhat.com>
---
 scripts/analyse-locks-simpletrace.py | 2 +-
 scripts/decodetree.py                | 2 +-
 scripts/device-crash-test            | 2 +-
 scripts/kvm/kvm_flightrecorder       | 2 +-
 scripts/qapi-gen.py                  | 2 +-
 scripts/qmp/qemu-ga-client           | 2 +-
 scripts/qmp/qmp                      | 2 +-
 scripts/qmp/qmp-shell                | 2 +-
 scripts/qmp/qom-fuse                 | 2 +-
 scripts/render_block_graph.py        | 2 +-
 scripts/replay-dump.py               | 2 +-
 scripts/simpletrace.py               | 2 +-
 scripts/tracetool.py                 | 2 +-
 scripts/vmstate-static-checker.py    | 2 +-
 14 files changed, 14 insertions(+), 14 deletions(-)

```
#### [PULL 1/1] vfio-ccw: Use the correct style for SPDX License Identifier
##### From: Cornelia Huck <cohuck@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Cornelia Huck <cohuck@redhat.com>
X-Patchwork-Id: 11368933
Return-Path: <SRS0=ZRkH=32=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3AD16924
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  6 Feb 2020 17:03:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 19AF921741
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  6 Feb 2020 17:03:55 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="hdcVWHyC"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727771AbgBFRDz (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 6 Feb 2020 12:03:55 -0500
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:33733 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726990AbgBFRDy (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 6 Feb 2020 12:03:54 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1581008633;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=MZ+wCDHlpmj2MEIpeb0HAQG2PkMc60gWNqQ5c6sbTrw=;
        b=hdcVWHyCfH5MYXpTMzynMlZGrr0+G4okZkOnKc8Zamy58HvnZpp6/uRsFxWNHtFs+91RmN
        4Knr8AdJHXICOpRjemGIelRJTVuAM6Zw8OI/C5MW+vTJzElzeeWREfdMQlyU0npzSeuL6a
        aA38e8iyjY2QBD3FEiY7OjZSs9xecT0=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-281-mAVvcrbBMauYviiyOp0GoA-1; Thu, 06 Feb 2020 12:03:37 -0500
X-MC-Unique: mAVvcrbBMauYviiyOp0GoA-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 731FA1835A24;
        Thu,  6 Feb 2020 17:03:35 +0000 (UTC)
Received: from localhost (dhcp-192-195.str.redhat.com [10.33.192.195])
        by smtp.corp.redhat.com (Postfix) with ESMTPS id 1D45348;
        Thu,  6 Feb 2020 17:03:34 +0000 (UTC)
From: Cornelia Huck <cohuck@redhat.com>
To: Heiko Carstens <heiko.carstens@de.ibm.com>,
        Vasily Gorbik <gor@linux.ibm.com>,
        Christian Borntraeger <borntraeger@de.ibm.com>
Cc: Eric Farman <farman@linux.ibm.com>,
        Halil Pasic <pasic@linux.ibm.com>, linux-s390@vger.kernel.org,
        kvm@vger.kernel.org, Nishad Kamdar <nishadkamdar@gmail.com>,
        Cornelia Huck <cohuck@redhat.com>
Subject: [PULL 1/1] vfio-ccw: Use the correct style for SPDX License
 Identifier
Date: Thu,  6 Feb 2020 18:03:31 +0100
Message-Id: <20200206170331.1032-2-cohuck@redhat.com>
In-Reply-To: <20200206170331.1032-1-cohuck@redhat.com>
References: <20200206170331.1032-1-cohuck@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Nishad Kamdar <nishadkamdar@gmail.com>

This patch corrects the SPDX License Identifier style in
header file related to S/390 common i/o drivers.
It assigns explicit block comment to the SPDX License
Identifier.

Changes made by using a script provided by Joe Perches here:
https://lkml.org/lkml/2019/2/7/46.

Fixes: 3cd90214b70f ("vfio: ccw: add tracepoints for interesting error paths")
Suggested-by: Joe Perches <joe@perches.com>
Signed-off-by: Nishad Kamdar <nishadkamdar@gmail.com>
Message-Id: <20191225122054.GA4598@nishad>
Signed-off-by: Cornelia Huck <cohuck@redhat.com>
---
 drivers/s390/cio/vfio_ccw_trace.h | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PULL kvm-unit-tests 01/10] Makefile: Use no-stack-protector compiler options
##### From: Andrew Jones <drjones@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11368845
Return-Path: <SRS0=ZRkH=32=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D9AE3924
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  6 Feb 2020 16:24:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B8925217BA
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  6 Feb 2020 16:24:46 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="XCj9pxPA"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727516AbgBFQYp (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 6 Feb 2020 11:24:45 -0500
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:27779 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1727392AbgBFQYp (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 6 Feb 2020 11:24:45 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1581006284;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=QVn3KA9sEn9fMwY63Oid8rmv0wn5jHhT2Lb83C9NoNE=;
        b=XCj9pxPAnCNaGUI33Qpro8K8DYJOss1vDDsOFcWoL9YcUc9agTzT+mcN2JQfyXJIyMge6V
        NORzJi8yQkte0Zq63KyqS73LeQu+LrC3cdYKP91MrVAEoq6NqS231lMROEemE0hDrLWPGU
        ehUF9qemR6ODiZTuT67jw0cYsJ8Q0QA=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-244-lLGbsx5PPqO-h-8cZbfiCw-1; Thu, 06 Feb 2020 11:24:41 -0500
X-MC-Unique: lLGbsx5PPqO-h-8cZbfiCw-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 9FCDA800D54;
        Thu,  6 Feb 2020 16:24:40 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.43.2.160])
        by smtp.corp.redhat.com (Postfix) with ESMTP id A20A91001B05;
        Thu,  6 Feb 2020 16:24:36 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, Alexandru Elisei <alexandru.elisei@arm.com>,
        Drew Jones <drjones@redhat.com>,
        Laurent Vivier <lvivier@redhat.com>,
        Thomas Huth <thuth@redhat.com>,
        David Hildenbrand <david@redhat.com>,
        Janosch Frank <frankja@linux.ibm.com>
Subject: [PULL kvm-unit-tests 01/10] Makefile: Use no-stack-protector compiler
 options
Date: Thu,  6 Feb 2020 17:24:25 +0100
Message-Id: <20200206162434.14624-2-drjones@redhat.com>
In-Reply-To: <20200206162434.14624-1-drjones@redhat.com>
References: <20200206162434.14624-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Alexandru Elisei <alexandru.elisei@arm.com>

Let's fix the typos so that the -fno-stack-protector and
-fno-stack-protector-all compiler options are actually used.

Tested by compiling for arm64, x86_64 and ppc64 little endian. Before the
patch, the arguments were missing from the gcc invocation; after the patch,
they were present. Also fixes a compilation error that I was seeing with
aarch64 gcc version 9.2.0, where the linker was complaining about an
undefined reference to the symbol __stack_chk_guard.

Fixes: e5c73790f5f0 ("build: don't reevaluate cc-option shell command")
CC: Paolo Bonzini <pbonzini@redhat.com>
CC: Drew Jones <drjones@redhat.com>
CC: Laurent Vivier <lvivier@redhat.com>
CC: Thomas Huth <thuth@redhat.com>
CC: David Hildenbrand <david@redhat.com>
CC: Janosch Frank <frankja@linux.ibm.com>
Signed-off-by: Alexandru Elisei <alexandru.elisei@arm.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
Reviewed-by: Laurent Vivier <lvivier@redhat.com>
Signed-off-by: Andrew Jones <drjones@redhat.com>
---
 Makefile | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [RFCv2.1] KVM: S390: protvirt: Introduce instruction data area bounce buffer
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11368003
Return-Path: <SRS0=ZRkH=32=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3771C13A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  6 Feb 2020 09:39:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 0C66A214AF
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  6 Feb 2020 09:39:16 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727548AbgBFJjP (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 6 Feb 2020 04:39:15 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:46360 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726452AbgBFJjP (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 6 Feb 2020 04:39:15 -0500
Received: from pps.filterd (m0098410.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 0169bhCt032529
        for <kvm@vger.kernel.org>; Thu, 6 Feb 2020 04:39:14 -0500
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2xyhmna9ty-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT)
        for <kvm@vger.kernel.org>; Thu, 06 Feb 2020 04:39:14 -0500
Received: from m0098410.ppops.net (m0098410.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 0169cLmR035595
        for <kvm@vger.kernel.org>; Thu, 6 Feb 2020 04:39:14 -0500
Received: from ppma02wdc.us.ibm.com (aa.5b.37a9.ip4.static.sl-reverse.com
 [169.55.91.170])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2xyhmna9tf-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 06 Feb 2020 04:39:13 -0500
Received: from pps.filterd (ppma02wdc.us.ibm.com [127.0.0.1])
        by ppma02wdc.us.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 0169a5fQ024853;
        Thu, 6 Feb 2020 09:39:12 GMT
Received: from b03cxnp08027.gho.boulder.ibm.com
 (b03cxnp08027.gho.boulder.ibm.com [9.17.130.19])
        by ppma02wdc.us.ibm.com with ESMTP id 2xykc9kuhm-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 06 Feb 2020 09:39:12 +0000
Received: from b03ledav006.gho.boulder.ibm.com
 (b03ledav006.gho.boulder.ibm.com [9.17.130.237])
        by b03cxnp08027.gho.boulder.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 0169d98546596538
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 6 Feb 2020 09:39:09 GMT
Received: from b03ledav006.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id A766BC6055;
        Thu,  6 Feb 2020 09:39:09 +0000 (GMT)
Received: from b03ledav006.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id E8F50C6057;
        Thu,  6 Feb 2020 09:39:08 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.114.17.106])
        by b03ledav006.gho.boulder.ibm.com (Postfix) with ESMTP;
        Thu,  6 Feb 2020 09:39:08 +0000 (GMT)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: david@redhat.com
Cc: Ulrich.Weigand@de.ibm.com, aarcange@redhat.com,
        borntraeger@de.ibm.com, cohuck@redhat.com, frankja@linux.ibm.com,
        frankja@linux.vnet.ibm.com, imbrenda@linux.ibm.com,
        kvm@vger.kernel.org, thuth@redhat.com
Subject: [RFCv2.1] KVM: S390: protvirt: Introduce instruction data area bounce
 buffer
Date: Thu,  6 Feb 2020 04:39:07 -0500
Message-Id: <20200206093907.5784-1-borntraeger@de.ibm.com>
X-Mailer: git-send-email 2.24.0
In-Reply-To: <4508d11e-455e-1496-f4a3-5a9c994a9126@redhat.com>
References: <4508d11e-455e-1496-f4a3-5a9c994a9126@redhat.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-02-05_06:2020-02-04,2020-02-05 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 lowpriorityscore=0
 impostorscore=0 mlxscore=0 phishscore=0 malwarescore=0 priorityscore=1501
 mlxlogscore=999 suspectscore=3 bulkscore=0 adultscore=0 spamscore=0
 clxscore=1015 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2001150001 definitions=main-2002060074
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Janosch Frank <frankja@linux.ibm.com>

Now that we can't access guest memory anymore, we have a dedicated
sattelite block that's a bounce buffer for instruction data.

We re-use the memop interface to copy the instruction data to / from
userspace. This lets us re-use a lot of QEMU code which used that
interface to make logical guest memory accesses which are not possible
anymore in protected mode anyway.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
---
 arch/s390/include/asm/kvm_host.h | 11 ++++++-
 arch/s390/kvm/kvm-s390.c         | 49 ++++++++++++++++++++++++++++++++
 arch/s390/kvm/pv.c               |  9 ++++++
 include/uapi/linux/kvm.h         | 10 +++++--
 4 files changed, 76 insertions(+), 3 deletions(-)

```
#### [RFC PATCH v2 1/9] vfio-ccw: Introduce new helper functions to free/destroy regions
##### From: Eric Farman <farman@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Farman <farman@linux.ibm.com>
X-Patchwork-Id: 11369247
Return-Path: <SRS0=ZRkH=32=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 33525138D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  6 Feb 2020 21:38:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1D462217BA
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  6 Feb 2020 21:38:43 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727473AbgBFVim (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 6 Feb 2020 16:38:42 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:21206 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727443AbgBFVid (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 6 Feb 2020 16:38:33 -0500
Received: from pps.filterd (m0098409.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 016LaTLM088644
        for <kvm@vger.kernel.org>; Thu, 6 Feb 2020 16:38:33 -0500
Received: from e06smtp02.uk.ibm.com (e06smtp02.uk.ibm.com [195.75.94.98])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2y0n7gm14r-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Thu, 06 Feb 2020 16:38:32 -0500
Received: from localhost
        by e06smtp02.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <farman@linux.ibm.com>;
        Thu, 6 Feb 2020 21:38:30 -0000
Received: from b06avi18878370.portsmouth.uk.ibm.com (9.149.26.194)
        by e06smtp02.uk.ibm.com (192.168.101.132) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Thu, 6 Feb 2020 21:38:28 -0000
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06avi18878370.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 016LcQYv31523082
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 6 Feb 2020 21:38:26 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 48501A4065;
        Thu,  6 Feb 2020 21:38:26 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 3707EA4062;
        Thu,  6 Feb 2020 21:38:26 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTPS;
        Thu,  6 Feb 2020 21:38:26 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 4958)
        id A7A43E0264; Thu,  6 Feb 2020 22:38:25 +0100 (CET)
From: Eric Farman <farman@linux.ibm.com>
To: Cornelia Huck <cohuck@redhat.com>
Cc: Halil Pasic <pasic@linux.ibm.com>,
        Jason Herne <jjherne@linux.ibm.com>,
        Jared Rossi <jrossi@linux.ibm.com>,
        Eric Farman <farman@linux.ibm.com>, linux-s390@vger.kernel.org,
        kvm@vger.kernel.org
Subject: [RFC PATCH v2 1/9] vfio-ccw: Introduce new helper functions to
 free/destroy regions
Date: Thu,  6 Feb 2020 22:38:17 +0100
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200206213825.11444-1-farman@linux.ibm.com>
References: <20200206213825.11444-1-farman@linux.ibm.com>
X-TM-AS-GCONF: 00
x-cbid: 20020621-0008-0000-0000-000003506F12
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 20020621-0009-0000-0000-00004A710457
Message-Id: <20200206213825.11444-2-farman@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-02-06_04:2020-02-06,2020-02-06 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 bulkscore=0 impostorscore=0
 adultscore=0 suspectscore=2 priorityscore=1501 malwarescore=0 phishscore=0
 mlxscore=0 clxscore=1015 spamscore=0 mlxlogscore=755 lowpriorityscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2001150001
 definitions=main-2002060157
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Farhan Ali <alifm@linux.ibm.com>

Consolidate some of the cleanup code for the regions, so that
as more are added we reduce code duplication.

Signed-off-by: Farhan Ali <alifm@linux.ibm.com>
Signed-off-by: Eric Farman <farman@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---

Notes:
    v1->v2:
     - Add Conny's r-b
    
    v0->v1: [EF]
     - Commit message

 drivers/s390/cio/vfio_ccw_drv.c | 28 ++++++++++++++++++----------
 1 file changed, 18 insertions(+), 10 deletions(-)

```
#### [PATCH v4 1/3] selftests: KVM: Replace get_gdt/idt_base() by get_gdt/idt()
##### From: Eric Auger <eric.auger@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Auger Eric <eric.auger@redhat.com>
X-Patchwork-Id: 11368145
Return-Path: <SRS0=ZRkH=32=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 474611398
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  6 Feb 2020 10:47:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 271E1217F4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  6 Feb 2020 10:47:34 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="X6ahpDdR"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728269AbgBFKra (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 6 Feb 2020 05:47:30 -0500
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:37272 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1728254AbgBFKra (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 6 Feb 2020 05:47:30 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1580986048;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=DjACAqq/wYOhXLsaJL3aNxs4eglM1cTnecpkHCb5DHE=;
        b=X6ahpDdRjvCJxfcS9Vt+EqkPpWlq9QmGRb6/6dl5l558sMFD/o4nDayvxQyiXKWDe56+Tx
        ydclHYYDUVeCQ0GWFSK/AV8FAbuUoLvMgkNAZSC+7uwtbq0kvpR0aFxh/l5bmrEsm3RRvb
        xc4RegZyoyzV6XclCcqR1yJW4T/IgIM=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-142-fX7PJ7G2Oy-0MdddfipMpA-1; Thu, 06 Feb 2020 05:47:27 -0500
X-MC-Unique: fX7PJ7G2Oy-0MdddfipMpA-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 2BE81800D54;
        Thu,  6 Feb 2020 10:47:26 +0000 (UTC)
Received: from laptop.redhat.com (ovpn-116-37.ams2.redhat.com [10.36.116.37])
        by smtp.corp.redhat.com (Postfix) with ESMTP id EDF058ECE3;
        Thu,  6 Feb 2020 10:47:21 +0000 (UTC)
From: Eric Auger <eric.auger@redhat.com>
To: eric.auger.pro@gmail.com, eric.auger@redhat.com,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        pbonzini@redhat.com, vkuznets@redhat.com
Cc: thuth@redhat.com, drjones@redhat.com, wei.huang2@amd.com
Subject: [PATCH v4 1/3] selftests: KVM: Replace get_gdt/idt_base() by
 get_gdt/idt()
Date: Thu,  6 Feb 2020 11:47:08 +0100
Message-Id: <20200206104710.16077-2-eric.auger@redhat.com>
In-Reply-To: <20200206104710.16077-1-eric.auger@redhat.com>
References: <20200206104710.16077-1-eric.auger@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

get_gdt_base() and get_idt_base() only return the base address
of the descriptor tables. Soon we will need to get the size as well.
Change the prototype of those functions so that they return
the whole desc_ptr struct instead of the address field.

Signed-off-by: Eric Auger <eric.auger@redhat.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Reviewed-by: Miaohe Lin <linmiaohe@huawei.com>
Reviewed-by: Wei Huang <wei.huang2@amd.com>
---

v3 -> v4:
- Collected R-b's
---
 tools/testing/selftests/kvm/include/x86_64/processor.h | 8 ++++----
 tools/testing/selftests/kvm/lib/x86_64/vmx.c           | 6 +++---
 2 files changed, 7 insertions(+), 7 deletions(-)

```
