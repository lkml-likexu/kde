#### [PATCH v2 10/37] KVM: s390: protvirt: Secure memory is not mergeable
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11364563
Return-Path: <SRS0=QQOC=3Y=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C423C1395
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  4 Feb 2020 13:04:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id AC55A2166E
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  4 Feb 2020 13:04:25 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727210AbgBDNEY (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 4 Feb 2020 08:04:24 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:30232 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727126AbgBDNEY (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 4 Feb 2020 08:04:24 -0500
Received: from pps.filterd (m0098409.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 014CnwmM078109
        for <kvm@vger.kernel.org>; Tue, 4 Feb 2020 08:04:23 -0500
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2xxtbjr0r4-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT)
        for <kvm@vger.kernel.org>; Tue, 04 Feb 2020 08:04:23 -0500
Received: from m0098409.ppops.net (m0098409.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 014CoGJd080295
        for <kvm@vger.kernel.org>; Tue, 4 Feb 2020 08:04:22 -0500
Received: from ppma04dal.us.ibm.com (7a.29.35a9.ip4.static.sl-reverse.com
 [169.53.41.122])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2xxtbjr0qf-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 04 Feb 2020 08:04:22 -0500
Received: from pps.filterd (ppma04dal.us.ibm.com [127.0.0.1])
        by ppma04dal.us.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 014D46aw020599;
        Tue, 4 Feb 2020 13:04:21 GMT
Received: from b01cxnp22036.gho.pok.ibm.com (b01cxnp22036.gho.pok.ibm.com
 [9.57.198.26])
        by ppma04dal.us.ibm.com with ESMTP id 2xw0y6yqgc-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 04 Feb 2020 13:04:21 +0000
Received: from b01ledav003.gho.pok.ibm.com (b01ledav003.gho.pok.ibm.com
 [9.57.199.108])
        by b01cxnp22036.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id 014D4KWG39190886
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 4 Feb 2020 13:04:20 GMT
Received: from b01ledav003.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id F18EAB2065;
        Tue,  4 Feb 2020 13:04:19 +0000 (GMT)
Received: from b01ledav003.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id E26BCB2064;
        Tue,  4 Feb 2020 13:04:19 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.114.17.106])
        by b01ledav003.gho.pok.ibm.com (Postfix) with ESMTP;
        Tue,  4 Feb 2020 13:04:19 +0000 (GMT)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: david@redhat.com
Cc: Ulrich.Weigand@de.ibm.com, aarcange@redhat.com,
        borntraeger@de.ibm.com, cohuck@redhat.com,
        frankja@linux.vnet.ibm.com, imbrenda@linux.ibm.com,
        kvm@vger.kernel.org, thuth@redhat.com,
        Janosch Frank <frankja@linux.ibm.com>
Subject: [PATCH v2 10/37] KVM: s390: protvirt: Secure memory is not mergeable
Date: Tue,  4 Feb 2020 08:04:18 -0500
Message-Id: <20200204130418.226980-1-borntraeger@de.ibm.com>
X-Mailer: git-send-email 2.24.0
In-Reply-To: <04c69c18-52e8-c09e-d93e-dbf2c006ac5e@redhat.com>
References: <04c69c18-52e8-c09e-d93e-dbf2c006ac5e@redhat.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-02-04_03:2020-02-04,2020-02-04 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 lowpriorityscore=0
 malwarescore=0 adultscore=0 priorityscore=1501 bulkscore=0 suspectscore=1
 spamscore=0 phishscore=0 clxscore=1015 mlxscore=0 mlxlogscore=806
 impostorscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-1911200001 definitions=main-2002040091
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Janosch Frank <frankja@linux.ibm.com>

KSM will not work on secure pages, because when the kernel reads a
secure page, it will be encrypted and hence no two pages will look the
same.

Let's mark the guest pages as unmergeable when we transition to secure
mode.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
---
 arch/s390/include/asm/gmap.h |  1 +
 arch/s390/kvm/kvm-s390.c     |  6 ++++++
 arch/s390/mm/gmap.c          | 30 ++++++++++++++++++++----------
 3 files changed, 27 insertions(+), 10 deletions(-)

```
#### [PATCH] KVM: nVMX: Remove stale comment from nested_vmx_load_cr3()
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11364865
Return-Path: <SRS0=QQOC=3Y=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1EA81138D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  4 Feb 2020 15:33:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 071632087E
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  4 Feb 2020 15:33:05 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727415AbgBDPdB (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 4 Feb 2020 10:33:01 -0500
Received: from mga05.intel.com ([192.55.52.43]:6851 "EHLO mga05.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727310AbgBDPdB (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 4 Feb 2020 10:33:01 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga002.jf.intel.com ([10.7.209.21])
  by fmsmga105.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 04 Feb 2020 07:33:00 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,402,1574150400";
   d="scan'208";a="249375173"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by orsmga002.jf.intel.com with ESMTP; 04 Feb 2020 07:33:00 -0800
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: nVMX: Remove stale comment from nested_vmx_load_cr3()
Date: Tue,  4 Feb 2020 07:32:59 -0800
Message-Id: <20200204153259.16318-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The blurb pertaining to the return value of nested_vmx_load_cr3() no
longer matches reality, remove it entirely as the behavior it is
attempting to document is quite obvious when reading the actual code.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Reviewed-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 arch/x86/kvm/vmx/nested.c | 2 --
 1 file changed, 2 deletions(-)

```
#### [PATCH] KVM: Pre-allocate 1 cpumask variable per cpu for both pv tlb and pv ipis
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11363913
Return-Path: <SRS0=QQOC=3Y=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3904C921
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  4 Feb 2020 02:35:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 06E432086A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  4 Feb 2020 02:35:02 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="o75bXAf6"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726924AbgBDCe6 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 3 Feb 2020 21:34:58 -0500
Received: from mail-oi1-f193.google.com ([209.85.167.193]:45912 "EHLO
        mail-oi1-f193.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726561AbgBDCe6 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 3 Feb 2020 21:34:58 -0500
Received: by mail-oi1-f193.google.com with SMTP id v19so16928196oic.12;
        Mon, 03 Feb 2020 18:34:57 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=mime-version:from:date:message-id:subject:to:cc;
        bh=UwqlvjZg+P79VPrIKOEjrbePHOK7IvreNa3/f6eQCOM=;
        b=o75bXAf6EcCc8NRROr5wamAH15QCJpnm3lCm/gPrIArOLHNbmg9obJ8XlT6HnSuBMW
         /NtTIj3PTMGlXtbAZJyf7Ik6IaWWqtE6+vkhk/D4qWrDpoERF+gYpA1+AUE/klTr2+Gl
         xNNAY8/JWTpHYzdEgPQ/EMBron58kp3tGYBiYUf6B3e9CeB8RqWb9btVSxE3xPda6jxj
         MsUTzqvJmnaDNGnMGzMDuLWinT4KtBbek2tNmZXoO6VUsCR6KMBKlYoxMT7tktCGkfL8
         f7Up591RJ7olppBt8mVJKnnYtCe3EQ0RwlCCRyBuy+t1Bq4eFulNPhB3kMB/bzgUoJnk
         e3Ng==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:mime-version:from:date:message-id:subject:to:cc;
        bh=UwqlvjZg+P79VPrIKOEjrbePHOK7IvreNa3/f6eQCOM=;
        b=MvBlrsEoTJe+dMUkgYs/6Q1tC7YgGRVmlwVlegpDBt3y9yhgLNwk9wTtMPZgu7GtNk
         iBp8RaozBXAUzsweMrJF69B4TT6A6VkfkCe8ThhJ/NjdfmIgO2NktvQ8OJoaxzKybc3o
         GSlFS6Rvu6SCS3rrse5ysZmAmwZCP55tsmnN4pZjuTP9aqnihiU+k2TW7CPn8dmR/T+2
         nt5rBl2VpiXMDe8qUnCy7sAoZVjrHU3TORNtRCTDRZ2mAnzpXLqkpghDSQp/UP2+mQGI
         EE5EMAyqmVc7zN3+N/c7qacSNo1dyGZfe3LFsaKPzrfD+WDROYUPjZyHdSsAmRB/eDEC
         GhOA==
X-Gm-Message-State: APjAAAWDFYIuTYWJziIz+uCSNNyzE245Z+zCBQ9lt8h/ojHKpxz3Rtxu
        KWOmgYCi9LAoKaEmJHTlTKUhNlR9vDvRbQgUQsNMcO83sNKPjQ==
X-Google-Smtp-Source: 
 APXvYqxSBol/GUwnr4C2zHlwCSaop2fNuJ2r/nOZROjoa36uLclaEGvQi1JSWOolBvI76ZXljm8ybrq3c2xi/nJcrwY=
X-Received: by 2002:aca:1913:: with SMTP id l19mr1673868oii.47.1580783697159;
 Mon, 03 Feb 2020 18:34:57 -0800 (PST)
MIME-Version: 1.0
From: Wanpeng Li <kernellwp@gmail.com>
Date: Tue, 4 Feb 2020 10:34:45 +0800
Message-ID: 
 <CANRm+CwwYoSLeA3Squp-_fVZpmYmxEfqOB+DGoQN4Y_iMT347w@mail.gmail.com>
Subject: [PATCH] KVM: Pre-allocate 1 cpumask variable per cpu for both pv tlb
 and pv ipis
To: LKML <linux-kernel@vger.kernel.org>, kvm <kvm@vger.kernel.org>
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

Nick Desaulniers Reported:

  When building with:
  $ make CC=clang arch/x86/ CFLAGS=-Wframe-larger-than=1000
  The following warning is observed:
  arch/x86/kernel/kvm.c:494:13: warning: stack frame size of 1064 bytes in
  function 'kvm_send_ipi_mask_allbutself' [-Wframe-larger-than=]
  static void kvm_send_ipi_mask_allbutself(const struct cpumask *mask, int
  vector)
              ^
  Debugging with:
  https://github.com/ClangBuiltLinux/frame-larger-than
  via:
  $ python3 frame_larger_than.py arch/x86/kernel/kvm.o \
    kvm_send_ipi_mask_allbutself
  points to the stack allocated `struct cpumask newmask` in
  `kvm_send_ipi_mask_allbutself`. The size of a `struct cpumask` is
  potentially large, as it's CONFIG_NR_CPUS divided by BITS_PER_LONG for
  the target architecture. CONFIG_NR_CPUS for X86_64 can be as high as
  8192, making a single instance of a `struct cpumask` 1024 B.

This patch fixes it by pre-allocate 1 cpumask variable per cpu and use it for
both pv tlb and pv ipis..

Reported-by: Nick Desaulniers <ndesaulniers@google.com>
Acked-by: Nick Desaulniers <ndesaulniers@google.com>
Cc: Peter Zijlstra <peterz@infradead.org>
Cc: Nick Desaulniers <ndesaulniers@google.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kernel/kvm.c | 33 +++++++++++++++++++++------------
 1 file changed, 21 insertions(+), 12 deletions(-)

 }

@@ -575,7 +577,6 @@ static void __init kvm_apf_trap_init(void)
     update_intr_gate(X86_TRAP_PF, async_page_fault);
 }

-static DEFINE_PER_CPU(cpumask_var_t, __pv_tlb_mask);

 static void kvm_flush_tlb_others(const struct cpumask *cpumask,
             const struct flush_tlb_info *info)
@@ -583,7 +584,7 @@ static void kvm_flush_tlb_others(const struct
cpumask *cpumask,
     u8 state;
     int cpu;
     struct kvm_steal_time *src;
-    struct cpumask *flushmask = this_cpu_cpumask_var_ptr(__pv_tlb_mask);
+    struct cpumask *flushmask = this_cpu_cpumask_var_ptr(__pv_cpu_mask);

     cpumask_copy(flushmask, cpumask);
     /*
@@ -624,6 +625,7 @@ static void __init kvm_guest_init(void)
         kvm_para_has_feature(KVM_FEATURE_STEAL_TIME)) {
         pv_ops.mmu.flush_tlb_others = kvm_flush_tlb_others;
         pv_ops.mmu.tlb_remove_table = tlb_remove_table;
+        pr_info("KVM setup pv remote TLB flush\n");
     }

     if (kvm_para_has_feature(KVM_FEATURE_PV_EOI))
@@ -732,23 +734,30 @@ static __init int activate_jump_labels(void)
 }
 arch_initcall(activate_jump_labels);

-static __init int kvm_setup_pv_tlb_flush(void)
+static __init int kvm_alloc_cpumask(void)
 {
     int cpu;
+    bool alloc = false;

     if (kvm_para_has_feature(KVM_FEATURE_PV_TLB_FLUSH) &&
         !kvm_para_has_hint(KVM_HINTS_REALTIME) &&
-        kvm_para_has_feature(KVM_FEATURE_STEAL_TIME)) {
+        kvm_para_has_feature(KVM_FEATURE_STEAL_TIME))
+        alloc = true;
+
+#if defined(CONFIG_SMP)
+    if (!alloc && kvm_para_has_feature(KVM_FEATURE_PV_SEND_IPI))
+        alloc = true;
+#endif
+
+    if (alloc)
         for_each_possible_cpu(cpu) {
-            zalloc_cpumask_var_node(per_cpu_ptr(&__pv_tlb_mask, cpu),
+            zalloc_cpumask_var_node(per_cpu_ptr(&__pv_cpu_mask, cpu),
                 GFP_KERNEL, cpu_to_node(cpu));
         }
-        pr_info("KVM setup pv remote TLB flush\n");
-    }

     return 0;
 }
-arch_initcall(kvm_setup_pv_tlb_flush);
+arch_initcall(kvm_alloc_cpumask);

 #ifdef CONFIG_PARAVIRT_SPINLOCKS

--
1.8.3.1

```
#### [kvm-unit-tests PULL 1/9] s390x: smp: Cleanup smp.c
##### From: Thomas Huth <thuth@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Huth <thuth@redhat.com>
X-Patchwork-Id: 11364117
Return-Path: <SRS0=QQOC=3Y=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7CA2013A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  4 Feb 2020 07:13:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 50A2F21775
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  4 Feb 2020 07:13:49 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="W+JnyaHi"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726378AbgBDHNs (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 4 Feb 2020 02:13:48 -0500
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:20592 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726053AbgBDHNs (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 4 Feb 2020 02:13:48 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1580800427;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:in-reply-to:in-reply-to:references:references;
        bh=uYQgQSLkVmftwYeud7Lp3Fio62OSlQzGpPE26l50Te0=;
        b=W+JnyaHi5c3tsZMUhBOXs3gtqWOVEW/0lF2ixORJEQp2D/EMkiRWM8MI0pvEeOh+q0cSUl
        1+wsQ28Je7wj2pCQuTwJ65ooJnHrYB5q9A+uxx2RsbAAYguTuaGmB7QdcqznmOQ24Ysqhs
        mBE/AfqLhuJcIyXMFyUOsx1RrSFELPo=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-179-F9MBVDcYO0OIxrbFqOzQJA-1; Tue, 04 Feb 2020 02:13:45 -0500
X-MC-Unique: F9MBVDcYO0OIxrbFqOzQJA-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 366F01090785;
        Tue,  4 Feb 2020 07:13:44 +0000 (UTC)
Received: from thuth.com (ovpn-116-39.ams2.redhat.com [10.36.116.39])
        by smtp.corp.redhat.com (Postfix) with ESMTP id D33E45C1D8;
        Tue,  4 Feb 2020 07:13:42 +0000 (UTC)
From: Thomas Huth <thuth@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: david@redhat.com, Janosch Frank <frankja@linux.ibm.com>
Subject: [kvm-unit-tests PULL 1/9] s390x: smp: Cleanup smp.c
Date: Tue,  4 Feb 2020 08:13:27 +0100
Message-Id: <20200204071335.18180-2-thuth@redhat.com>
In-Reply-To: <20200204071335.18180-1-thuth@redhat.com>
References: <20200204071335.18180-1-thuth@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Janosch Frank <frankja@linux.ibm.com>

Let's remove a lot of badly formatted code by introducing the
wait_for_flag() and set_flag functions.

Also let's remove some stray spaces and always set the testflag before
using it.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Message-Id: <20200201152851.82867-2-frankja@linux.ibm.com>
Signed-off-by: Thomas Huth <thuth@redhat.com>
---
 s390x/smp.c | 55 ++++++++++++++++++++++++++++++++---------------------
 1 file changed, 33 insertions(+), 22 deletions(-)

```
#### [kvm-unit-tests PATCH] x86: Fix the name for the SMEP CPUID bit
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11365105
Return-Path: <SRS0=QQOC=3Y=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 95C92139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  4 Feb 2020 17:50:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7B15020674
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  4 Feb 2020 17:50:37 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727458AbgBDRug (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 4 Feb 2020 12:50:36 -0500
Received: from mga09.intel.com ([134.134.136.24]:49214 "EHLO mga09.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727392AbgBDRug (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 4 Feb 2020 12:50:36 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by orsmga102.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 04 Feb 2020 09:50:35 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,402,1574150400";
   d="scan'208";a="225579763"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by fmsmga008.fm.intel.com with ESMTP; 04 Feb 2020 09:50:35 -0800
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org
Subject: [kvm-unit-tests PATCH] x86: Fix the name for the SMEP CPUID bit
Date: Tue,  4 Feb 2020 09:50:34 -0800
Message-Id: <20200204175034.18201-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Fix the X86_FEATURE_* name for SMEP, which is incorrectly named
X86_FEATURE_INVPCID_SINGLE and is a wee bit confusing when looking at
the SMEP unit tests.

Note, there is no INVPCID_SINGLE CPUID bit, the bogus name likely came
from the Linux kernel, which has a synthetic feature flag for
INVPCID_SINGLE in word 7, bit 7 (CPUID 0x7.EBX is stored in word 9).

Fixes: 6ddcc29 ("kvm-unit-test: x86: Implement a generic wrapper for cpuid/cpuid_indexed functions")
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Reviewed-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 lib/x86/processor.h | 2 +-
 x86/access.c        | 4 ++--
 2 files changed, 3 insertions(+), 3 deletions(-)

```
#### [kvm-unit-tests PATCH] x86: pmu: Test WRMSR on a running counterFrom: Eric Hankland <ehankland@google.com>
##### From: Eric Hankland <ehankland@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Hankland <ehankland@google.com>
X-Patchwork-Id: 11363753
Return-Path: <SRS0=QQOC=3Y=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3710A1398
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  4 Feb 2020 01:25:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 14DC92084E
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  4 Feb 2020 01:25:16 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="LMaPXvTV"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727102AbgBDBZK (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 3 Feb 2020 20:25:10 -0500
Received: from mail-pl1-f201.google.com ([209.85.214.201]:40973 "EHLO
        mail-pl1-f201.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726872AbgBDBZJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 3 Feb 2020 20:25:09 -0500
Received: by mail-pl1-f201.google.com with SMTP id p19so7190705plr.8
        for <kvm@vger.kernel.org>; Mon, 03 Feb 2020 17:25:09 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=QUGZT2MVbSZ5vv9JAqfeam9eYCtpwd6NYyrPTQGL4Vw=;
        b=LMaPXvTVHWRjR4OY/kwNL2KfAHa8UpJCbQ0fB/vH0vTkR8weS3+o9HmWUvxODuRA4v
         9eGAqaftuBVncplz+Wug33AL9+V/WCN7uk+FPQfHd5+A1AsXHSPQlSeQaweYV0uSixD2
         +R7y90zPyGDs/57TAHOvUZrRDaToG9qNnQvZcYcBx92QXf7LzAJPBkrN8fwwAWzqO8xR
         z2+Fz4CR8lpoCEsdkzQo+V70TvTVhNfa5MSC3MpGeLYmhY9RxuxWO7+JNbPLoS67HTNK
         OLQ4bDNxSF/Zyg0ujWp5pA9GN9o3W70W9mJr4rJmiqr3bu4xFkH4ZeZl4YSzsyVQymwL
         IFJg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=QUGZT2MVbSZ5vv9JAqfeam9eYCtpwd6NYyrPTQGL4Vw=;
        b=Az8qZy+pNCf6i8Auelh6q2K0p3k0cgfVyP+mJD/ILpZKH3XMf/FlPyywLsz6BP9Szz
         sODgQO+ePYpd+tcRmIB8vLbybNlAjoutTwUbM2++UFaPVxZf4PC3rpNTti2lkCGZ6bgk
         6r+Uz5Cymy2gWzia5+yLySFmY3T+B0cFetwKGi5qT0ctIOaBqxQUedPKd8vCtpeTscW8
         bvWV4mtxzgNX5Fz0EuGcgEitsfnuKxt5yCYHJJ098bsjF1FXzjRSQZl8wRDfwDXHuh7S
         1xM1RIfljlpajxFtQZGQOsNljfrpRY6klmxRpu/Xc0XgCfeWjrE0Xlk6qN4cggoww3Dm
         Y19Q==
X-Gm-Message-State: APjAAAVeTk/fVjEXXCuL+lZhUzVNRz33imuobVKxspIBI48xC3NpFVOJ
        GSQmIpdlyozdGKObQrmx1tBUw6Aeg2JSQRc=
X-Google-Smtp-Source: 
 APXvYqyOkoVhkCWzz0zCy43+eQxoSu+yTApt3/SxLxfSIAKMDlDHWIT8cwq3rPNiC0x1HQmUNKFf5+CNs1BjSLo=
X-Received: by 2002:a63:cd04:: with SMTP id i4mr20017956pgg.281.1580779508971;
 Mon, 03 Feb 2020 17:25:08 -0800 (PST)
Date: Mon,  3 Feb 2020 17:25:04 -0800
Message-Id: <20200204012504.9590-1-ehankland@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.25.0.341.g760bfbb309-goog
Subject: [kvm-unit-tests PATCH] x86: pmu: Test WRMSR on a running counter
From: Eric Hankland <ehankland@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Peter Shier <pshier@google.com>
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        Eric Hankland <ehankland@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Ensure that the value of the counter was successfully set to 0 after
writing it while the counter was running.

Signed-off-by: Eric Hankland <ehankland@google.com>
---
 x86/pmu.c | 16 ++++++++++++++++
 1 file changed, 16 insertions(+)

```
#### [kvm-unit-tests PATCH] x86: Use "-cpu host" for PCID tests
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11365225
Return-Path: <SRS0=QQOC=3Y=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 34950138D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  4 Feb 2020 19:48:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1C9B62087E
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  4 Feb 2020 19:48:12 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727412AbgBDTsL (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 4 Feb 2020 14:48:11 -0500
Received: from mga11.intel.com ([192.55.52.93]:7061 "EHLO mga11.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727314AbgBDTsL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 4 Feb 2020 14:48:11 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by fmsmga102.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 04 Feb 2020 11:48:10 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,402,1574150400";
   d="scan'208";a="224405634"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by orsmga008.jf.intel.com with ESMTP; 04 Feb 2020 11:48:10 -0800
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org
Subject: [kvm-unit-tests PATCH] x86: Use "-cpu host" for PCID tests
Date: Tue,  4 Feb 2020 11:48:09 -0800
Message-Id: <20200204194809.2077-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Use the host CPU model for the PCID tests to allow testing the various
combinations of PCID and INVPCID enabled/disabled without having to
manually change the kvm-unit-tests command line.  I.e. give users the
option of changing the command line *OR* running on a (virtual) CPU
with or without PCID and/or INVPCID.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 x86/unittests.cfg | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v3 1/3] selftests: KVM: Replace get_gdt/idt_base() by get_gdt/idt()
##### From: Eric Auger <eric.auger@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Auger <eric.auger@redhat.com>
X-Patchwork-Id: 11364783
Return-Path: <SRS0=QQOC=3Y=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 917EA112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  4 Feb 2020 15:01:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 6F3CA2087E
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  4 Feb 2020 15:01:05 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="AkPCO3Ff"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727431AbgBDPBC (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 4 Feb 2020 10:01:02 -0500
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:60715 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727258AbgBDPBB (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 4 Feb 2020 10:01:01 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1580828460;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=tdKFql9kzBw3LkuIPbGwq21dgvZE7z2ME9ERxXZaGCk=;
        b=AkPCO3FfCzAYyO702alyx4Cd2rSyfQiy3GeRtaPgFgEkQLpNpowtlU9pFxaG0urTG7/8sK
        9Q2jYozi3TlG1AM2Ke209bzhS9FLXSnmoQ9LrLIyrwXmSJ2waC2K/y1SsgvBhuGnmCKN4j
        HS4+VUE0Z1wDlvUyETz2ASqRrum6InM=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-432-awNdZRw6MvyU8Dp4mk0rtw-1; Tue, 04 Feb 2020 10:00:56 -0500
X-MC-Unique: awNdZRw6MvyU8Dp4mk0rtw-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 0DAF11083691;
        Tue,  4 Feb 2020 15:00:55 +0000 (UTC)
Received: from laptop.redhat.com (ovpn-116-37.ams2.redhat.com [10.36.116.37])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 27B467FB79;
        Tue,  4 Feb 2020 15:00:51 +0000 (UTC)
From: Eric Auger <eric.auger@redhat.com>
To: eric.auger.pro@gmail.com, eric.auger@redhat.com,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        pbonzini@redhat.com, vkuznets@redhat.com
Cc: thuth@redhat.com, drjones@redhat.com, wei.huang2@amd.com
Subject: [PATCH v3 1/3] selftests: KVM: Replace get_gdt/idt_base() by
 get_gdt/idt()
Date: Tue,  4 Feb 2020 16:00:38 +0100
Message-Id: <20200204150040.2465-2-eric.auger@redhat.com>
In-Reply-To: <20200204150040.2465-1-eric.auger@redhat.com>
References: <20200204150040.2465-1-eric.auger@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
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
---
 tools/testing/selftests/kvm/include/x86_64/processor.h | 8 ++++----
 tools/testing/selftests/kvm/lib/x86_64/vmx.c           | 6 +++---
 2 files changed, 7 insertions(+), 7 deletions(-)

```
#### [RFC PATCH 1/7] vfio: Include optional device match in vfio_device_ops callbacks
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alex Williamson <alex.williamson@redhat.com>
X-Patchwork-Id: 11365333
Return-Path: <SRS0=QQOC=3Y=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A95DE92A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  4 Feb 2020 23:05:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 83DA9217F4
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  4 Feb 2020 23:05:58 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="JJtA95se"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727828AbgBDXF5 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 4 Feb 2020 18:05:57 -0500
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:56272 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1727814AbgBDXFz (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 4 Feb 2020 18:05:55 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1580857554;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=IvMgKRo9UcBxsKQ0k8mTNazf7kcSB0yWVPnP1lD/+n4=;
        b=JJtA95seA6vkuUAIJjc4Hz5rXh+50CBdx1ZoV87/EdMu81nB/uw1558AwTVr/lEkyNJGi9
        uEJdx7vmcFJIdrFwp8Yr1BHxA/1OXlLaPKVX9r88RCJfeJaQAMQJLQeh3+pMeSV1uFbsEW
        XGeE4sQmvlRIJad48kkaTn4rwLUUccY=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-58-PYYDho4mMBSpdySKOACwxw-1; Tue, 04 Feb 2020 18:05:50 -0500
X-MC-Unique: PYYDho4mMBSpdySKOACwxw-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 90EBDA0CBF;
        Tue,  4 Feb 2020 23:05:46 +0000 (UTC)
Received: from gimli.home (ovpn-116-28.phx2.redhat.com [10.3.116.28])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 642A660BF3;
        Tue,  4 Feb 2020 23:05:43 +0000 (UTC)
Subject: [RFC PATCH 1/7] vfio: Include optional device match in
 vfio_device_ops callbacks
From: Alex Williamson <alex.williamson@redhat.com>
To: kvm@vger.kernel.org
Cc: linux-pci@vger.kernel.org, linux-kernel@vger.kernel.org,
        dev@dpdk.org, mtosatti@redhat.com, thomas@monjalon.net,
        bluca@debian.org, jerinjacobk@gmail.com,
        bruce.richardson@intel.com, cohuck@redhat.com
Date: Tue, 04 Feb 2020 16:05:43 -0700
Message-ID: <158085754299.9445.4389176548645142886.stgit@gimli.home>
In-Reply-To: <158085337582.9445.17682266437583505502.stgit@gimli.home>
References: <158085337582.9445.17682266437583505502.stgit@gimli.home>
User-Agent: StGit/0.19-dirty
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Allow bus drivers to provide their own callback to match a device to
the user provided string.

Signed-off-by: Alex Williamson <alex.williamson@redhat.com>
---
 drivers/vfio/vfio.c  |   19 +++++++++++++++----
 include/linux/vfio.h |    3 +++
 2 files changed, 18 insertions(+), 4 deletions(-)

```
