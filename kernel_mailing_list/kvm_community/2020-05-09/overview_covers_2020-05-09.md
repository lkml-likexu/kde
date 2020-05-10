

#### [PATCH 0/3 v2] KVM: nSVM: Check MBZ bits in CR3 and CR4 on vmrun of
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
From patchwork Sat May  9 00:36:49 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11537849
Return-Path: <SRS0=tS7s=6X=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B895A139F
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat,  9 May 2020 01:17:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A2CCB24954
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat,  9 May 2020 01:17:30 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="BDcanLEe"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728468AbgEIBR3 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 8 May 2020 21:17:29 -0400
Received: from aserp2120.oracle.com ([141.146.126.78]:51028 "EHLO
        aserp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728165AbgEIBR1 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 8 May 2020 21:17:27 -0400
Received: from pps.filterd (aserp2120.oracle.com [127.0.0.1])
        by aserp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 0491DJLB178991;
        Sat, 9 May 2020 01:17:23 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : mime-version : content-transfer-encoding;
 s=corp-2020-01-29; bh=iwocHYqZ4bnDXJUcJGr0L71fFplDLTZ+2sRGP6AzNOU=;
 b=BDcanLEe7QXuF4bnzqZ2N2epQJc3hkvQVHOIWcGFKvowX2A6Reds1N9AedHaIpnRuSZJ
 YUrQyitKc9gAwqRqHW1wrm/XAEWmFcg9ic+8J1DXeCoBrbdNWEnNrXVBWR+/cxeDV+S9
 OeucVtQ+qucbi2LLruDJ/KGyHH27ZpXN0pqKe93+GAXsuT+Ai9vtCwP20lgD72oGNzYA
 SDdKH0nWx9ED2sfhJulCXjTGvpH7OrThwurI8SAq4bhQaIp28yTMsnKpo53ngFS6SZE/
 gvLKu30RyAbx6KzkAIqAK6a1zte4q9zOzOhOPV9Yra6yiBZD9xvBHxEPzXmdb39ZNZGA lg==
Received: from aserp3020.oracle.com (aserp3020.oracle.com [141.146.126.70])
        by aserp2120.oracle.com with ESMTP id 30vtepnw2u-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Sat, 09 May 2020 01:17:23 +0000
Received: from pps.filterd (aserp3020.oracle.com [127.0.0.1])
        by aserp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 04917cdA048468;
        Sat, 9 May 2020 01:17:22 GMT
Received: from aserv0121.oracle.com (aserv0121.oracle.com [141.146.126.235])
        by aserp3020.oracle.com with ESMTP id 30vte1p7su-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Sat, 09 May 2020 01:17:22 +0000
Received: from abhmp0010.oracle.com (abhmp0010.oracle.com [141.146.116.16])
        by aserv0121.oracle.com (8.14.4/8.13.8) with ESMTP id 0491HMak016042;
        Sat, 9 May 2020 01:17:22 GMT
Received: from ban25x6uut29.us.oracle.com (/10.153.73.29)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Fri, 08 May 2020 18:17:22 -0700
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com
Subject: [PATCH 0/3 v2] KVM: nSVM: Check MBZ bits in CR3 and CR4 on vmrun of
 nested guests
Date: Fri,  8 May 2020 20:36:49 -0400
Message-Id: <20200509003652.25178-1-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9615
 signatures=668687
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 mlxlogscore=539
 phishscore=0
 bulkscore=0 malwarescore=0 suspectscore=1 adultscore=0 mlxscore=0
 spamscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2003020000 definitions=main-2005090008
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9615
 signatures=668687
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 adultscore=0
 spamscore=0
 impostorscore=0 phishscore=0 clxscore=1015 priorityscore=1501
 lowpriorityscore=0 malwarescore=0 suspectscore=1 mlxscore=0
 mlxlogscore=594 bulkscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-2003020000 definitions=main-2005090008
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

v1 -> v2:
	1. Removed the formation of the mask for guest CR4 bits, from
	   kvm_valid_cr4() to kvm_update_cpuid(). The mask is stashed
	   in a global variable called '__guest_cr4_reserved_bits'.
	   Patch# 1 contains these changes.
	2. nested_vmcb_checks() now uses is_long_mode(), instead of the
	   guest EFER, to check for Long Mode. Patch# 2 contains these
	   changes.
	3. Patch# 3 contains the kvm-unit-tests. No changes have been
	   made to the tests.


[PATCH 1/3 v2] KVM: x86: Create mask for guest CR4 reserved bits in
[PATCH 2/3 v2] KVM: nSVM: Check that MBZ bits in CR3 and CR4 are not set on
[PATCH 3/3 v2] KVM: nSVM: Test that MBZ bits in CR3 and CR4 are not set on vmrun

 arch/x86/kvm/cpuid.c      |  3 +++
 arch/x86/kvm/svm/nested.c | 22 ++++++++++++++++++++--
 arch/x86/kvm/svm/svm.h    |  5 ++++-
 arch/x86/kvm/x86.c        | 27 ++++-----------------------
 arch/x86/kvm/x86.h        | 21 +++++++++++++++++++++
 5 files changed, 52 insertions(+), 26 deletions(-)

Krish Sadhukhan (2):
      KVM: x86: Create mask for guest CR4 reserved bits in kvm_update_cpuid()
      nSVM: Check that MBZ bits in CR3 and CR4 are not set on vmrun of nested gu

 x86/svm.h       |   6 ++++
 x86/svm_tests.c | 105 +++++++++++++++++++++++++++++++++++++++++++++++++-------
 2 files changed, 99 insertions(+), 12 deletions(-)

Krish Sadhukhan (1):
      nSVM: Test that MBZ bits in CR3 and CR4 are not set on vmrun of nested gue
```
#### [PATCH v9 0/8] KVM: Add virtualization support of split lock
##### From: Xiaoyao Li <xiaoyao.li@intel.com>

```c
From patchwork Sat May  9 11:05:34 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xiaoyao Li <xiaoyao.li@intel.com>
X-Patchwork-Id: 11537903
Return-Path: <SRS0=tS7s=6X=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4F14915E6
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat,  9 May 2020 03:03:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3F25220731
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat,  9 May 2020 03:03:44 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728698AbgEIDDh (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 8 May 2020 23:03:37 -0400
Received: from mga12.intel.com ([192.55.52.136]:55091 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728353AbgEIDDh (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 8 May 2020 23:03:37 -0400
IronPort-SDR: 
 H/exOR5zLCH2BknVlS9DIuuMIAdgvN9porSu+yK0g11VOsiYSDj/CN4BHp2/vrrfl8WMg2fLUt
 Wl0XqacIck1Q==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga004.jf.intel.com ([10.7.209.38])
  by fmsmga106.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 08 May 2020 20:03:35 -0700
IronPort-SDR: 
 p5F7squzwX9c0HwlHNy+7Iqc3has7qwLimi8ARJJMnrHTFNWFEWS56rV4WCz7a3wrbwy0ns8R8
 dGYT+QawcOgg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,370,1583222400";
   d="scan'208";a="408310940"
Received: from lxy-dell.sh.intel.com ([10.239.159.21])
  by orsmga004.jf.intel.com with ESMTP; 08 May 2020 20:03:31 -0700
From: Xiaoyao Li <xiaoyao.li@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, x86@kernel.org,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        "H. Peter Anvin" <hpa@zytor.com>,
        Andy Lutomirski <luto@kernel.org>, peterz@infradead.org,
        Arvind Sankar <nivedita@alum.mit.edu>,
        Tony Luck <tony.luck@intel.com>,
        Fenghua Yu <fenghua.yu@intel.com>,
        Xiaoyao Li <xiaoyao.li@intel.com>
Subject: [PATCH v9 0/8] KVM: Add virtualization support of split lock
 detection
Date: Sat,  9 May 2020 19:05:34 +0800
Message-Id: <20200509110542.8159-1-xiaoyao.li@intel.com>
X-Mailer: git-send-email 2.18.2
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series aims to add the virtualization of split lock detection in
KVM.

Due to the fact that split lock detection is tightly coupled with CPU
model and CPU model is configurable by host VMM, we elect to use
paravirt method to expose and enumerate it for guest.

Changes in v9
 - rebase to v5.7-rc4
 - Add one patch to rename TIF_SLD to TIF_SLD_DISABLED;
 - Add one patch to remove bogus case in handle_guest_split_lock;
 - Introduce flag X86_FEATURE_SPLIT_LOCK_DETECT_FATAL and thus drop
   sld_state;
 - Use X86_FEATURE_SPLIT_LOCK_DETECT and X86_FEATURE_SPLIT_LOCK_DETECT_FATAL
   to determine the SLD state of host;
 - Introduce split_lock_virt_switch() and two wrappers for KVM instead
   of sld_update_to(); 
 - Use paravirt to expose and enumerate split lock detection for guest;
 - Split lock detection can be exposed to guest when host is sld_fatal,
   even though host is SMT available. 

Changes in v8:
https://lkml.kernel.org/r/20200414063129.133630-1-xiaoyao.li@intel.com
 - rebase to v5.7-rc1.
 - basic enabling of split lock detection already merged.
 - When host is sld_warn and nosmt, load guest's sld bit when in KVM
   context, i.e., between vmx_prepare_switch_to_guest() and before
   vmx_prepare_switch_to_host(), KVM uses guest sld setting.  

Changes in v7:
https://lkml.kernel.org/r/20200325030924.132881-1-xiaoyao.li@intel.com
 - only pick patch 1 and patch 2, and hold all the left.
 - Update SLD bit on each processor based on sld_state.

Changes in v6:
https://lkml.kernel.org/r/20200324151859.31068-1-xiaoyao.li@intel.com
 - Drop the sld_not_exist flag and use X86_FEATURE_SPLIT_LOCK_DETECT to
   check whether need to init split lock detection. [tglx]
 - Use tglx's method to verify the existence of split lock detectoin.
 - small optimization of sld_update_msr() that the default value of
   msr_test_ctrl_cache has split_lock_detect bit cleared.
 - Drop the patch3 in v5 that introducing kvm_only option. [tglx]
 - Rebase patch4-8 to kvm/queue.
 - use the new kvm-cpu-cap to expose X86_FEATURE_CORE_CAPABILITIES in
   Patch 6.

Changes in v5:
https://lkml.kernel.org/r/20200315050517.127446-1-xiaoyao.li@intel.com
 - Use X86_FEATURE_SPLIT_LOCK_DETECT flag in kvm to ensure split lock
   detection is really supported.
 - Add and export sld related helper functions in their related usecase 
   kvm patches.

Xiaoyao Li (8):
  x86/split_lock: Rename TIF_SLD to TIF_SLD_DISABLED
  x86/split_lock: Remove bogus case in handle_guest_split_lock()
  x86/split_lock: Introduce flag X86_FEATURE_SLD_FATAL and drop
    sld_state
  x86/split_lock: Introduce split_lock_virt_switch() and two wrappers
  x86/kvm: Introduce paravirt split lock detection enumeration
  KVM: VMX: Enable MSR TEST_CTRL for guest
  KVM: VMX: virtualize split lock detection
  x86/split_lock: Enable split lock detection initialization when
    running as an guest on KVM

 Documentation/virt/kvm/cpuid.rst     | 29 +++++++----
 arch/x86/include/asm/cpu.h           | 35 ++++++++++++++
 arch/x86/include/asm/cpufeatures.h   |  1 +
 arch/x86/include/asm/thread_info.h   |  6 +--
 arch/x86/include/uapi/asm/kvm_para.h |  8 ++--
 arch/x86/kernel/cpu/intel.c          | 59 ++++++++++++++++-------
 arch/x86/kernel/kvm.c                |  3 ++
 arch/x86/kernel/process.c            |  2 +-
 arch/x86/kvm/cpuid.c                 |  6 +++
 arch/x86/kvm/vmx/vmx.c               | 72 +++++++++++++++++++++++++---
 arch/x86/kvm/vmx/vmx.h               |  3 ++
 arch/x86/kvm/x86.c                   |  6 ++-
 arch/x86/kvm/x86.h                   |  7 +++
 13 files changed, 196 insertions(+), 41 deletions(-)
```
