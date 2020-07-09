

#### [PATCH 0/3 v4] KVM: nSVM: Check MBZ bits in CR3 and CR4 on vmrun of
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
From patchwork Wed Jul  8 00:39:54 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11650531
Return-Path: <SRS0=kMba=AT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6AC331709
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Jul 2020 00:40:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 51AD42064B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Jul 2020 00:40:15 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="NI03Rp1q"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728765AbgGHAkK (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 7 Jul 2020 20:40:10 -0400
Received: from userp2120.oracle.com ([156.151.31.85]:36776 "EHLO
        userp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728001AbgGHAkJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 7 Jul 2020 20:40:09 -0400
Received: from pps.filterd (userp2120.oracle.com [127.0.0.1])
        by userp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 0680WW94010604;
        Wed, 8 Jul 2020 00:40:07 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id; s=corp-2020-01-29;
 bh=98ZX2b7/Gzn1/H/GjRS7fzXCrqacNcK6JSXj56dzCJ4=;
 b=NI03Rp1qdos3raEmZF2lkH9h2QsMc7Ta1WkIClmxDP9jy5s1m0TTBcmGP1DC8yUzrUT5
 BQc0dJ52+9ecMUv2aZMQ8vEBegNiZGblpeRxusbw5QGQ2v6Q4V+afrj76t1RjL+oM/kd
 aOxwdn7a2bNACA/Z8pVOqh7iGIgEnFGuMwaGO7oWzgGog6Tht04ve8on+Luk5ChBE3mb
 wtvEK4e+7huCKW8vb4atqezuwCYYzqEZyLPUYFtBUmofw/PIzG/QTuO7NHv3DFxXBhQE
 GD6T+hmg0goGVkPNubNMaqgCY+73SxsdgjlvN1goE0kdi47D0A+KCA9ZGVgPMr4GlfeB RQ==
Received: from aserp3030.oracle.com (aserp3030.oracle.com [141.146.126.71])
        by userp2120.oracle.com with ESMTP id 323sxxuuqb-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=FAIL);
        Wed, 08 Jul 2020 00:40:06 +0000
Received: from pps.filterd (aserp3030.oracle.com [127.0.0.1])
        by aserp3030.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 0680XF74100897;
        Wed, 8 Jul 2020 00:40:06 GMT
Received: from aserv0121.oracle.com (aserv0121.oracle.com [141.146.126.235])
        by aserp3030.oracle.com with ESMTP id 3233bq0nup-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 08 Jul 2020 00:40:06 +0000
Received: from abhmp0008.oracle.com (abhmp0008.oracle.com [141.146.116.14])
        by aserv0121.oracle.com (8.14.4/8.13.8) with ESMTP id 0680e5mr007323;
        Wed, 8 Jul 2020 00:40:05 GMT
Received: from nsvm-sadhukhan.osdevelopmeniad.oraclevcn.com (/100.100.231.196)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Tue, 07 Jul 2020 17:40:05 -0700
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com
Subject: [PATCH 0/3 v4] KVM: nSVM: Check MBZ bits in CR3 and CR4 on vmrun of
 nested guests
Date: Wed,  8 Jul 2020 00:39:54 +0000
Message-Id: <1594168797-29444-1-git-send-email-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 1.8.3.1
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9675
 signatures=668680
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 phishscore=0
 mlxscore=0 adultscore=0
 malwarescore=0 spamscore=0 mlxlogscore=947 bulkscore=0 suspectscore=1
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2004280000
 definitions=main-2007080000
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9675
 signatures=668680
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 lowpriorityscore=0 mlxlogscore=947
 bulkscore=0 impostorscore=0 adultscore=0 cotscore=-2147483648 phishscore=0
 priorityscore=1501 clxscore=1015 malwarescore=0 suspectscore=1 spamscore=0
 mlxscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2004280000 definitions=main-2007080000
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

v3 -> v4:
	1. In patch# 1, 'guest_cr4_reserved_bits' has been renamed to
	   'cr4_guest_rsvd_bits' and it's now located where other CR4-related
	   members are.
	2. Rebased to the latest Upstream sources.


[PATCH 1/3 v4] KVM: x86: Create mask for guest CR4 reserved bits in
[PATCH 2/3 v4] KVM: nSVM: Check that MBZ bits in CR3 and CR4 are not set on
[PATCH 3/3 v4] kvm-unit-tests: nSVM: Test that MBZ bits in CR3 and CR4 are

 arch/x86/include/asm/kvm_host.h |  1 +
 arch/x86/kvm/cpuid.c            |  2 ++
 arch/x86/kvm/svm/nested.c       | 22 ++++++++++++++++++++--
 arch/x86/kvm/svm/svm.h          |  5 ++++-
 arch/x86/kvm/x86.c              | 27 ++++-----------------------
 arch/x86/kvm/x86.h              | 21 +++++++++++++++++++++
 6 files changed, 52 insertions(+), 26 deletions(-)

Krish Sadhukhan (2):
      KVM: x86: Create mask for guest CR4 reserved bits in kvm_update_cpuid()
      nSVM: Check that MBZ bits in CR3 and CR4 are not set on vmrun of nested gu

 x86/svm.h       |  5 +++
 x86/svm_tests.c | 94 ++++++++++++++++++++++++++++++++++++++++++++++++++++++---
 2 files changed, 95 insertions(+), 4 deletions(-)

Krish Sadhukhan (1):
      kvm-unit-tests: nSVM: Test that MBZ bits in CR3 and CR4 are not set on vmr
```
#### [PATCH v3 0/8] Refactor handling flow of KVM_SET_CPUID*
##### From: Xiaoyao Li <xiaoyao.li@intel.com>

```c
From patchwork Wed Jul  8 06:50:46 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xiaoyao Li <xiaoyao.li@intel.com>
X-Patchwork-Id: 11650715
Return-Path: <SRS0=kMba=AT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A914813B6
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Jul 2020 06:51:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9456A2078D
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Jul 2020 06:51:03 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729855AbgGHGvA (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 8 Jul 2020 02:51:00 -0400
Received: from mga11.intel.com ([192.55.52.93]:5284 "EHLO mga11.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726171AbgGHGvA (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 8 Jul 2020 02:51:00 -0400
IronPort-SDR: 
 TVXUIb7JUTtyAv+TRK7wXFPgHS6zpxPivp6jZ0KgICRMvpw7m6bsMZA6nYn2gw2/X6LwnsphAD
 BjepTfUrqSGQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9675"; a="145852056"
X-IronPort-AV: E=Sophos;i="5.75,326,1589266800";
   d="scan'208";a="145852056"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga005.jf.intel.com ([10.7.209.41])
  by fmsmga102.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 07 Jul 2020 23:50:59 -0700
IronPort-SDR: 
 2+VAslrMs72o338mVcRjdbGXU7ZUvJXZN3C3gdeN3BJfNTru2r5LOp56K5pPFLImHz98RHPVUb
 3Tp6FdFQ09uQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,326,1589266800";
   d="scan'208";a="457399062"
Received: from lxy-dell.sh.intel.com ([10.239.159.21])
  by orsmga005.jf.intel.com with ESMTP; 07 Jul 2020 23:50:57 -0700
From: Xiaoyao Li <xiaoyao.li@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Jim Mattson <jmattson@google.com>
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        linux-doc@vger.kernel.org, Jonathan Corbet <corbet@lwn.net>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Joerg Roedel <joro@8bytes.org>,
        Xiaoyao Li <xiaoyao.li@intel.com>
Subject: [PATCH v3 0/8] Refactor handling flow of KVM_SET_CPUID*
Date: Wed,  8 Jul 2020 14:50:46 +0800
Message-Id: <20200708065054.19713-1-xiaoyao.li@intel.com>
X-Mailer: git-send-email 2.18.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This serial is the extended version of
https://lkml.kernel.org/r/20200528151927.14346-1-xiaoyao.li@intel.com

First two patches are bug fixing, and the others aim to refactor the flow
of SET_CPUID* as:

1. cpuid check: check if userspace provides legal CPUID settings;

2. cpuid update: Update some special CPUID bits based on current vcpu
                 state, e.g., OSXSAVE, OSPKE, ...

3. update vcpu model: Update vcpu model (settings) based on the final CPUID
                      settings. 

v3:
 - Add a note in KVM api doc to state the previous CPUID configuration
   is not reliable if current KVM_SET_CPUID* fails [Jim]
 - Adjust Patch 2 to reduce code churn [Sean]
 - Commit message refine to add more justification [Sean]
 - Add a new patch (7)

v2:
https://lkml.kernel.org/r/20200623115816.24132-1-xiaoyao.li@intel.com
 - rebase to kvm/queue: a037ff353ba6 ("Merge branch 'kvm-master' into HEAD")
 - change the name of kvm_update_state_based_on_cpuid() to
   kvm_update_vcpu_model() [Sean]
 - Add patch 5 to rename kvm_x86_ops.cpuid_date() to
   kvm_x86_ops.update_vcpu_model()

v1:
https://lkml.kernel.org/r/20200529085545.29242-1-xiaoyao.li@intel.com

Xiaoyao Li (8):
  KVM: X86: Reset vcpu->arch.cpuid_nent to 0 if SET_CPUID* fails
  KVM: X86: Go on updating other CPUID leaves when leaf 1 is absent
  KVM: X86: Introduce kvm_check_cpuid()
  KVM: X86: Split kvm_update_cpuid()
  KVM: X86: Rename cpuid_update() to update_vcpu_model()
  KVM: X86: Move kvm_x86_ops.update_vcpu_model() into
    kvm_update_vcpu_model()
  KVM: lapic: Use guest_cpuid_has() in kvm_apic_set_version()
  KVM: X86: Move kvm_apic_set_version() to kvm_update_vcpu_model()

 Documentation/virt/kvm/api.rst  |   4 ++
 arch/x86/include/asm/kvm_host.h |   2 +-
 arch/x86/kvm/cpuid.c            | 107 ++++++++++++++++++++------------
 arch/x86/kvm/cpuid.h            |   3 +-
 arch/x86/kvm/lapic.c            |   4 +-
 arch/x86/kvm/svm/svm.c          |   4 +-
 arch/x86/kvm/vmx/nested.c       |   2 +-
 arch/x86/kvm/vmx/vmx.c          |   4 +-
 arch/x86/kvm/x86.c              |   1 +
 9 files changed, 81 insertions(+), 50 deletions(-)
```
#### [PATCH v2 0/3] KVM: nSVM: fix #TF from CR3 switch when entering guest
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
From patchwork Wed Jul  8 09:36:08 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11651215
Return-Path: <SRS0=kMba=AT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3B42314DD
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Jul 2020 09:36:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 21A1C206C3
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Jul 2020 09:36:24 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="hni3IOX2"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728263AbgGHJgX (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 8 Jul 2020 05:36:23 -0400
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:24436 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726445AbgGHJgV (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 8 Jul 2020 05:36:21 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1594200980;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=EXLv6hsZ/QhTdQkzMIaq3BPH71+im/fXOsDOYnL4M9A=;
        b=hni3IOX23dn4Dl54MrkHPIGiTZkDWlx323VWhRKNkGgc7HGgfG5kt1NdJ2y/OWYswjjyDX
        4hBjmiTcjoMy+ONTZkvfjRXlc5WWcmMl8q9UsMJ6ldjR746fEfJUk6WaodvXlCIQ1aO4Ve
        vvOtljLb0XYFpEHHj2uCkoyEBzodiM4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-440-Z9U-hLTZOPGhlVyBIK_szg-1; Wed, 08 Jul 2020 05:36:17 -0400
X-MC-Unique: Z9U-hLTZOPGhlVyBIK_szg-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 32429461;
        Wed,  8 Jul 2020 09:36:15 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.195.35])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 0EF215C221;
        Wed,  8 Jul 2020 09:36:12 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Junaid Shahid <junaids@google.com>,
        linux-kernel@vger.kernel.org
Subject: [PATCH v2 0/3] KVM: nSVM: fix #TF from CR3 switch when entering guest
Date: Wed,  8 Jul 2020 11:36:08 +0200
Message-Id: <20200708093611.1453618-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is a succesor of "[PATCH] KVM: x86: drop erroneous mmu_check_root()
from fast_pgd_switch()".

Undesired triple fault gets injected to L1 guest on SVM when L2 is
launched with certain CR3 values. #TF is raised by mmu_check_root()
check in fast_pgd_switch() and the root cause is that when
kvm_set_cr3() is called from nested_prepare_vmcb_save() with NPT
enabled CR3 points to a nGPA so we can't check it with
kvm_is_visible_gfn().

Fix the issue by moving kvm_mmu_new_pgd() to the right place when switching
to nested guest and drop the unneeded mmu_check_root() check from
fast_pgd_switch().

Vitaly Kuznetsov (3):
  KVM: nSVM: split kvm_init_shadow_npt_mmu() from kvm_init_shadow_mmu()
  KVM: nSVM: properly call kvm_mmu_new_pgd() upon switching to guest
  KVM: x86: drop superfluous mmu_check_root() from fast_pgd_switch()

 arch/x86/include/asm/kvm_host.h |  7 ++++++-
 arch/x86/kvm/mmu.h              |  3 ++-
 arch/x86/kvm/mmu/mmu.c          | 36 ++++++++++++++++++++++++---------
 arch/x86/kvm/svm/nested.c       |  5 +++--
 arch/x86/kvm/x86.c              |  8 +++++---
 5 files changed, 43 insertions(+), 16 deletions(-)
```
#### [PATCH v11 00/13] KVM: Dirty ring interface
##### From: Peter Xu <peterx@redhat.com>

```c
From patchwork Wed Jul  8 19:33:55 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11652381
Return-Path: <SRS0=kMba=AT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D561917CC
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Jul 2020 19:35:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B3CC120786
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Jul 2020 19:35:38 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Tc4GDvU8"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726974AbgGHTfV (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 8 Jul 2020 15:35:21 -0400
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:22678 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726786AbgGHTeZ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 8 Jul 2020 15:34:25 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1594236863;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=PfnzTH5TiQiBvj3tmmsIgK6HE3aerJ0LFD4YQueBCFU=;
        b=Tc4GDvU8JkRJxNxwrk4QIky+tIiZBfT0AuseNkqD6Ipllm+OmW5vXM2JFAFuaSj2MV/XRb
        MEweXhtNMXYVftZcCmAcUbJnB8PnEBgLNswJ0cX690Xm70A2aXAIi4qXR3ryCpQEwbAmp7
        Blnz4HVahM5+4nF8tJvFpdCUued81BI=
Received: from mail-qt1-f199.google.com (mail-qt1-f199.google.com
 [209.85.160.199]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-229-erdehuCwP4W1dbz0HCGpcg-1; Wed, 08 Jul 2020 15:34:13 -0400
X-MC-Unique: erdehuCwP4W1dbz0HCGpcg-1
Received: by mail-qt1-f199.google.com with SMTP id h30so33859031qtb.7
        for <kvm@vger.kernel.org>; Wed, 08 Jul 2020 12:34:13 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=PfnzTH5TiQiBvj3tmmsIgK6HE3aerJ0LFD4YQueBCFU=;
        b=eogwrDm+SciT5YP4WMOKiPN3kU775Njm2Toia++W9ydym5NvbIKqto8RgWQSMrKhUQ
         4umk6wRCxUakMHruon0a7UI5N8GGhj3pY0ya8T23m0WBVYnMzmm9F4WnlBpfAV5aNfnz
         QAiR3MrKPBZU8FVG8S6JMJWlZ0ETgJKnp6p2tDefIFrsHV5s81mB0jc0usRYsZkawrn5
         WdarWr1oTgTulde+yemK3uC+49u6Qs0bXr+9QZSiyAsTvA2z6dXzjhQUoXZ0FmOuOuJT
         ZOABpSuXQiLt8a5O2SWzuigtlC1shrLzu2P3yoi8EKN0cmRR6cHyu2x9g0imLoH1z/pv
         UsEw==
X-Gm-Message-State: AOAM533j+M82RVN5H9VpYPXLp7Tp9GbPzjuZ4B9y/ROqtElOImCisgJQ
        sCBQnKe/+NpGs9jccRIbR+sKxkQIkAv6pZ9c99fl8ARlOyzcojuwgCgI/cVRMoLNBQ71YH7iJ1/
        Gd63bNrZ1NI/F
X-Received: by 2002:a37:6781:: with SMTP id
 b123mr57977995qkc.376.1594236852382;
        Wed, 08 Jul 2020 12:34:12 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJwYBb6+Mm4RH21pOWVeozlDG+9ADy8RoK23SBwtH/e2gOU9vUpxZCvjP35j70ufqXPjKbxGwg==
X-Received: by 2002:a37:6781:: with SMTP id
 b123mr57977970qkc.376.1594236852003;
        Wed, 08 Jul 2020 12:34:12 -0700 (PDT)
Received: from xz-x1.redhat.com ([2607:9880:19c8:6f::1f4f])
        by smtp.gmail.com with ESMTPSA id
 f18sm664884qtc.28.2020.07.08.12.34.10
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 08 Jul 2020 12:34:11 -0700 (PDT)
From: Peter Xu <peterx@redhat.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: peterx@redhat.com,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        "Dr . David Alan Gilbert" <dgilbert@redhat.com>,
        Andrew Jones <drjones@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>
Subject: [PATCH v11 00/13] KVM: Dirty ring interface
Date: Wed,  8 Jul 2020 15:33:55 -0400
Message-Id: <20200708193408.242909-1-peterx@redhat.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

KVM branch:
  https://github.com/xzpeter/linux/tree/kvm-dirty-ring

QEMU branch for testing:
  https://github.com/xzpeter/qemu/tree/kvm-dirty-ring

v11:
- rebased to kvm/queue (seems the newest)
- removed kvm_dirty_ring_waitqueue() tracepoint since not used
- set memslot->as_id in kvm_delete_memslot() [Sean]
- let __copy_to_user() always return -EFAULT [Sean]
- rename 'r' in alloc_apic_access_page into 'hva' [Sean]

v10:
- remove unused identity_map_pfn in init_rmode_identity_map [syzbot]
- add "static" to kvm_dirty_ring_full [syzbot]
- kvm_page_in_dirty_ring() use "#if" macros for KVM_DIRTY_LOG_PAGE_OFFSET to
  quiesce syzbot [syzbot]
- s/false/null/ in gfn_to_memslot_dirty_bitmap() [syzbot]

v9:
- patch 3: __x86_set_memory_region: squash another trivial change to return
  (0xdeadull << 48) always for slot removal [Sean]
- pick r-bs for Drew

For previous versions, please refer to:

V1: https://lore.kernel.org/kvm/20191129213505.18472-1-peterx@redhat.com
V2: https://lore.kernel.org/kvm/20191221014938.58831-1-peterx@redhat.com
V3: https://lore.kernel.org/kvm/20200109145729.32898-1-peterx@redhat.com
V4: https://lore.kernel.org/kvm/20200205025105.367213-1-peterx@redhat.com
V5: https://lore.kernel.org/kvm/20200304174947.69595-1-peterx@redhat.com
V6: https://lore.kernel.org/kvm/20200309214424.330363-1-peterx@redhat.com
V7: https://lore.kernel.org/kvm/20200318163720.93929-1-peterx@redhat.com
V8: https://lore.kernel.org/kvm/20200331190000.659614-1-peterx@redhat.com
V9: https://lore.kernel.org/kvm/20200523225659.1027044-1-peterx@redhat.com
V10: https://lore.kernel.org/kvm/20200601115957.1581250-1-peterx@redhat.com/

Overview
============

This is a continued work from Lei Cao <lei.cao@stratus.com> and Paolo
Bonzini on the KVM dirty ring interface.

The new dirty ring interface is another way to collect dirty pages for
the virtual machines. It is different from the existing dirty logging
interface in a few ways, majorly:

  - Data format: The dirty data was in a ring format rather than a
    bitmap format, so dirty bits to sync for dirty logging does not
    depend on the size of guest memory any more, but speed of
    dirtying.  Also, the dirty ring is per-vcpu, while the dirty
    bitmap is per-vm.

  - Data copy: The sync of dirty pages does not need data copy any more,
    but instead the ring is shared between the userspace and kernel by
    page sharings (mmap() on vcpu fd)

  - Interface: Instead of using the old KVM_GET_DIRTY_LOG,
    KVM_CLEAR_DIRTY_LOG interfaces, the new ring uses the new
    KVM_RESET_DIRTY_RINGS ioctl when we want to reset the collected
    dirty pages to protected mode again (works like
    KVM_CLEAR_DIRTY_LOG, but ring based).  To collecting dirty bits,
    we only need to read the ring data, no ioctl is needed.

Ring Layout
===========

KVM dirty ring is per-vcpu.  Each ring is an array of kvm_dirty_gfn
defined as:

struct kvm_dirty_gfn {
        __u32 flags;
        __u32 slot; /* as_id | slot_id */
        __u64 offset;
};

Each GFN is a state machine itself.  The state is embeded in the flags
field, as defined in the uapi header:

/*
 * KVM dirty GFN flags, defined as:
 *
 * |---------------+---------------+--------------|
 * | bit 1 (reset) | bit 0 (dirty) | Status       |
 * |---------------+---------------+--------------|
 * |             0 |             0 | Invalid GFN  |
 * |             0 |             1 | Dirty GFN    |
 * |             1 |             X | GFN to reset |
 * |---------------+---------------+--------------|
 *
 * Lifecycle of a dirty GFN goes like:
 *
 *      dirtied         collected        reset
 * 00 -----------> 01 -------------> 1X -------+
 *  ^                                          |
 *  |                                          |
 *  +------------------------------------------+
 *
 * The userspace program is only responsible for the 01->1X state
 * conversion (to collect dirty bits).  Also, it must not skip any
 * dirty bits so that dirty bits are always collected in sequence.
 */

Testing
=======

This series provided both the implementation of the KVM dirty ring and
the test case.  Also I've implemented the QEMU counterpart that can
run with the new KVM, link can be found at the top of the cover
letter.  However that's still a very initial version which is prone to
change and future optimizations.

I did some measurement with the new method with 24G guest running some
dirty workload, I don't see any speedup so far, even in some heavy
dirty load it'll be slower (e.g., when 800MB/s random dirty rate, kvm
dirty ring takes average of ~73s to complete migration while dirty
logging only needs average of ~55s).  However that's understandable
because 24G guest means only 1M dirty bitmap, that's still a suitable
case for dirty logging.  Meanwhile heavier workload means worst case
for dirty ring.

More tests are welcomed if there's bigger host/guest, especially on
COLO-like workload.

Please review, thanks.

Peter Xu (13):
  KVM: Cache as_id in kvm_memory_slot
  KVM: X86: Don't track dirty for KVM_SET_[TSS_ADDR|IDENTITY_MAP_ADDR]
  KVM: Pass in kvm pointer into mark_page_dirty_in_slot()
  KVM: X86: Implement ring-based dirty memory tracking
  KVM: Make dirty ring exclusive to dirty bitmap log
  KVM: Don't allocate dirty bitmap if dirty ring is enabled
  KVM: selftests: Always clear dirty bitmap after iteration
  KVM: selftests: Sync uapi/linux/kvm.h to tools/
  KVM: selftests: Use a single binary for dirty/clear log test
  KVM: selftests: Introduce after_vcpu_run hook for dirty log test
  KVM: selftests: Add dirty ring buffer test
  KVM: selftests: Let dirty_log_test async for dirty ring test
  KVM: selftests: Add "-c" parameter to dirty log test

 Documentation/virt/kvm/api.rst                | 123 +++++
 arch/x86/include/asm/kvm_host.h               |   6 +-
 arch/x86/include/uapi/asm/kvm.h               |   1 +
 arch/x86/kvm/Makefile                         |   3 +-
 arch/x86/kvm/mmu/mmu.c                        |  10 +-
 arch/x86/kvm/svm/avic.c                       |   9 +-
 arch/x86/kvm/vmx/vmx.c                        |  96 ++--
 arch/x86/kvm/x86.c                            |  46 +-
 include/linux/kvm_dirty_ring.h                | 103 ++++
 include/linux/kvm_host.h                      |  19 +
 include/trace/events/kvm.h                    |  63 +++
 include/uapi/linux/kvm.h                      |  53 ++
 tools/include/uapi/linux/kvm.h                |  53 ++
 tools/testing/selftests/kvm/Makefile          |   2 -
 .../selftests/kvm/clear_dirty_log_test.c      |   6 -
 tools/testing/selftests/kvm/dirty_log_test.c  | 505 ++++++++++++++++--
 .../testing/selftests/kvm/include/kvm_util.h  |   4 +
 tools/testing/selftests/kvm/lib/kvm_util.c    |  72 ++-
 .../selftests/kvm/lib/kvm_util_internal.h     |   4 +
 virt/kvm/dirty_ring.c                         | 197 +++++++
 virt/kvm/kvm_main.c                           | 168 +++++-
 21 files changed, 1408 insertions(+), 135 deletions(-)
 create mode 100644 include/linux/kvm_dirty_ring.h
 delete mode 100644 tools/testing/selftests/kvm/clear_dirty_log_test.c
 create mode 100644 virt/kvm/dirty_ring.c
```
#### [patch V2 0/7] x86/kvm: RCU/context tracking and instrumentation
##### From: Thomas Gleixner <tglx@linutronix.de>

```c
From patchwork Wed Jul  8 19:51:53 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Gleixner <tglx@linutronix.de>
X-Patchwork-Id: 11652397
Return-Path: <SRS0=kMba=AT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9D47E60D
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Jul 2020 19:53:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8719C2078A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Jul 2020 19:53:42 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=linutronix.de header.i=@linutronix.de
 header.b="fhWKxJO8";
	dkim=permerror (0-bit key) header.d=linutronix.de header.i=@linutronix.de
 header.b="+TUlVf4V"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726302AbgGHTxj (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 8 Jul 2020 15:53:39 -0400
Received: from Galois.linutronix.de ([193.142.43.55]:53396 "EHLO
        galois.linutronix.de" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725446AbgGHTxj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 8 Jul 2020 15:53:39 -0400
Message-Id: <20200708195153.746357686@linutronix.de>
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=linutronix.de;
        s=2020; t=1594238017;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:content-transfer-encoding:content-transfer-encoding;
        bh=bNyLQ2pLAkRr83wZdq7rI6euSlnFR18flvxonxI4IPc=;
        b=fhWKxJO8AJQIGkBtx+zEZWMkxgE/gBzC2xEQWs1RGdbiGYNp8jTuTPdpwriTNdrii0praZ
        v6n/lTO2qEoXA/Camh+240xiDe/KsNE6bu27ldaCBDkY+Dfa7yHNYtouca5ujyAxbnM8gn
        dpaBNkwsWsnh3n75n0iCr8OIIUGOLvz8oN2XS42rmuJ5oTb65rLqUz9DLHwwSXqK1ooQLS
        Tl4KAi48kLeWWIIqV1ntRez1wboFVHWKTlEPAubbiDtTk6sjwhPvhX4/ysTV6RB9tfQOgA
        eCjuyKIeFQbIXpLKggzIEe7Gj8njkYeRjWf9dg3Ds6DybIJIlKKP3V/rS/rB4g==
DKIM-Signature: v=1; a=ed25519-sha256; c=relaxed/relaxed; d=linutronix.de;
        s=2020e; t=1594238017;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:content-transfer-encoding:content-transfer-encoding;
        bh=bNyLQ2pLAkRr83wZdq7rI6euSlnFR18flvxonxI4IPc=;
        b=+TUlVf4VktQeA7sSpjob2JKU4jDcApGvCeiZy1Ij6W47C62fLXBTy38rkYesfBN67HIqC7
        q7VvxLowuX7asaAg==
Date: Wed, 08 Jul 2020 21:51:53 +0200
From: Thomas Gleixner <tglx@linutronix.de>
To: LKML <linux-kernel@vger.kernel.org>
Cc: x86@kernel.org, Paolo Bonzini <pbonzini@redhat.com>,
        kvm@vger.kernel.org,
        Alexandre Chartre <alexandre.chartre@oracle.com>,
        Peter Zijlstra <peterz@infradead.org>,
        Juergen Gross <jgross@suse.com>
Subject: [patch V2 0/7] x86/kvm: RCU/context tracking and instrumentation
 protections
Content-transfer-encoding: 8-bit
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Folks,

this is a rebased and adopted version of the original series which is
available here:

     https://lore.kernel.org/r/20200519203128.773151484@linutronix.de
 
It deals with the RCU and context tracking state and the protection against
instrumentation in sensitive places:

  - Placing the guest_enter/exit() calls at the correct place

  - Moving the sensitive VMENTER/EXIT code into the non-instrumentable code
    section.

  - Fixup the tracing code to comply with the non-instrumentation rules

  - Use native functions to access CR2 and the GS base MSR in the critical
    code pathes to prevent them from being instrumented.

Thanks,

	tglx
```
