

#### [PATCH kvm-unit-tests v2 0/4] s390x: Add Protected VM support
##### From: Marc Hartmayer <mhartmay@linux.ibm.com>

```c
From patchwork Wed Sep 23 13:47:54 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Hartmayer <mhartmay@linux.ibm.com>
X-Patchwork-Id: 11795091
Return-Path: <SRS0=+e/I=DA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A0CF56CB
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Sep 2020 13:48:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 78D4E2220D
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Sep 2020 13:48:17 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="VVIpT/It"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726605AbgIWNsQ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 23 Sep 2020 09:48:16 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:55962 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726540AbgIWNsP (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 23 Sep 2020 09:48:15 -0400
Received: from pps.filterd (m0098394.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 08NDhlIm178093;
        Wed, 23 Sep 2020 09:48:14 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=f9xs6nbYQF9K0l6Z+qgw4wTquMcjdeTfunMdB8pUoLA=;
 b=VVIpT/ItrL/XtnfYEejWW7iLTtX8AlOn035ttPRF8a/jUBr1Gq1QxEq32m+oQSV0bOA5
 X5i/ALXBSHs5Dmuju0IlDv3EL2f5fxt9WQM23bfjPh4k2S56a1RYOFKevF4AckIVM+pt
 qhNiiME0Mf15AUVxA0O8/XrB6EM7qU3nUl1sDcpV7ATjPaTvXAsRR13gMMLIE/9Ml8R5
 GSV9bEB0v7qHPEtL1Sapun2DDY4SwuELbG2ZFcRbKkfQpucM89zjAgJ9IGVCjpNg6Ubs
 Pps9f5jXtjk7rvOkZeCf540U9b00GFV7bQjJ1IAeXhKj/X3GcaP6ncuJmimpyb/OQUws BQ==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 33r7gg847p-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 23 Sep 2020 09:48:14 -0400
Received: from m0098394.ppops.net (m0098394.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 08NDj8qg186490;
        Wed, 23 Sep 2020 09:48:14 -0400
Received: from ppma03ams.nl.ibm.com (62.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.98])
        by mx0a-001b2d01.pphosted.com with ESMTP id 33r7gg844r-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 23 Sep 2020 09:48:14 -0400
Received: from pps.filterd (ppma03ams.nl.ibm.com [127.0.0.1])
        by ppma03ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 08NDkeVZ025146;
        Wed, 23 Sep 2020 13:48:10 GMT
Received: from b06cxnps3074.portsmouth.uk.ibm.com
 (d06relay09.portsmouth.uk.ibm.com [9.149.109.194])
        by ppma03ams.nl.ibm.com with ESMTP id 33n9m8c72y-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 23 Sep 2020 13:48:10 +0000
Received: from d06av22.portsmouth.uk.ibm.com (d06av22.portsmouth.uk.ibm.com
 [9.149.105.58])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 08NDm8S116777546
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 23 Sep 2020 13:48:08 GMT
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id E277E4C05E;
        Wed, 23 Sep 2020 13:48:07 +0000 (GMT)
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 852D84C046;
        Wed, 23 Sep 2020 13:48:07 +0000 (GMT)
Received: from marcibm.ibmuc.com (unknown [9.145.64.218])
        by d06av22.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Wed, 23 Sep 2020 13:48:07 +0000 (GMT)
From: Marc Hartmayer <mhartmay@linux.ibm.com>
To: <kvm@vger.kernel.org>
Cc: Thomas Huth <thuth@redhat.com>,
        David Hildenbrand <david@redhat.com>,
        Janosch Frank <frankja@linux.ibm.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Andrew Jones <drjones@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>, linux-s390@vger.kernel.org
Subject: [PATCH kvm-unit-tests v2 0/4] s390x: Add Protected VM support
Date: Wed, 23 Sep 2020 15:47:54 +0200
Message-Id: <20200923134758.19354-1-mhartmay@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-09-23_09:2020-09-23,2020-09-23 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 phishscore=0
 priorityscore=1501 suspectscore=1 malwarescore=0 spamscore=0 clxscore=1015
 mlxscore=0 adultscore=0 lowpriorityscore=0 bulkscore=0 impostorscore=0
 mlxlogscore=999 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2009230108
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add support for Protected Virtual Machine (PVM) tests. For starting a
PVM guest we must be able to generate a PVM image by using the
`genprotimg` tool from the s390-tools collection. This requires the
ability to pass a machine-specific host-key document, so the option
`--host-key-document` is added to the configure script.

For everybody's convenience there is a branch:
https://gitlab.com/mhartmay/kvm-unit-tests/-/tree/pv_v2

Changelog:
 v1 -> v2:
   + rebased
   + patches 1-3:
     - add r-b from Conny, Andrew, and David
   + patch 4:
     - add r-b from Janosch
     - renamed ${testname} to $testname (David)
     - fix `print_result` function calls and the arguments used
 RFC v2 -> v1:
  + Rebased
  + patch 1:
    - add r-b from Andrew
  + patch 2:
    - add explicit dependency on config.mak (Andrew)
    - add comment about the order of sourcing (Andrew)
  + patch 3:
    - drop dummy function (Andrew)
    - add arch_cmd hook function (Andrew)
  + patch 4:
    - rephrased the documentation of the configure option (Conny)
    - Skip test case if a PVM image wasn't built or the host-key document wasn't set (Conny)
    - Run PV tests by default
 RFC v1 -> RFC v2:
  + Remove `pv_support` option (Janosch, David)
  + Add some preliminary patches:
    - move "testname guard"
    - add support for architecture dependent functions
  + Add support for specifying a parmline file for the PV image
    generation. This is necessary for the `selftest` because the
    kernel cmdline set on the QEMU command line is ignored for PV
    guests

Marc Hartmayer (4):
  common.bash: run `cmd` only if a test case was found
  scripts: add support for architecture dependent functions
  run_tests/mkstandalone: add arch_cmd hook
  s390x: add Protected VM support

 README.md               |  3 ++-
 configure               |  9 +++++++++
 run_tests.sh            |  3 ---
 s390x/Makefile          | 17 +++++++++++++++--
 s390x/selftest.parmfile |  1 +
 s390x/unittests.cfg     |  1 +
 scripts/common.bash     | 21 +++++++++++++++++++--
 scripts/mkstandalone.sh |  4 ----
 scripts/s390x/func.bash | 36 ++++++++++++++++++++++++++++++++++++
 9 files changed, 83 insertions(+), 12 deletions(-)
 create mode 100644 s390x/selftest.parmfile
 create mode 100644 scripts/s390x/func.bash
```
#### [PATCH v2 0/3] KVM: VMX: Clean up RTIT MAXPHYADDR usage
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Wed Sep 23 16:36:26 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11795263
Return-Path: <SRS0=+e/I=DA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6CB386CB
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Sep 2020 16:36:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5AAD5208E4
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Sep 2020 16:36:51 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726476AbgIWQgb (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 23 Sep 2020 12:36:31 -0400
Received: from mga17.intel.com ([192.55.52.151]:7062 "EHLO mga17.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726130AbgIWQgb (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 23 Sep 2020 12:36:31 -0400
IronPort-SDR: 
 L8DtY5LCNaOPNeUnKpsF0dBrJNloeWGZisLM80oHK3UriqIeRZFLNZVClMpCBVqJ41mX41/Tv0
 7Jip7UOipKjg==
X-IronPort-AV: E=McAfee;i="6000,8403,9753"; a="140962211"
X-IronPort-AV: E=Sophos;i="5.77,293,1596524400";
   d="scan'208";a="140962211"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga004.jf.intel.com ([10.7.209.38])
  by fmsmga107.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 23 Sep 2020 09:36:30 -0700
IronPort-SDR: 
 kIzfA+tB1ndtmTmCzFbm3LjYtRwl5niqcSqxJ8ZH/n/LdAc/i3dDBSmue/9GW4gQIacswOI26w
 EMWcaBOIIUAw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,293,1596524400";
   d="scan'208";a="454981819"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.160])
  by orsmga004.jf.intel.com with ESMTP; 23 Sep 2020 09:36:30 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v2 0/3] KVM: VMX: Clean up RTIT MAXPHYADDR usage
Date: Wed, 23 Sep 2020 09:36:26 -0700
Message-Id: <20200923163629.20168-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Stop using cpuid_query_maxphyaddr() for a random RTIT MSR check and
unexport said function to discourage future use.

v2:
  - Rebased to kvm/queue, commit e1ba1a15af73 ("KVM: SVM: Enable INVPCID
    feature on AMD").

Sean Christopherson (3):
  KVM: VMX: Use precomputed MAXPHYADDR for RTIT base MSR check
  KVM: VMX: Replace MSR_IA32_RTIT_OUTPUT_BASE_MASK with helper function
  KVM: x86: Unexport cpuid_query_maxphyaddr()

 arch/x86/kvm/cpuid.c   |  1 -
 arch/x86/kvm/vmx/vmx.c | 11 +++++++----
 2 files changed, 7 insertions(+), 5 deletions(-)
```
#### [PATCH 0/4] KVM: VMX: Add helper+macros to do sec exec adjustment
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Wed Sep 23 16:50:44 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11795289
Return-Path: <SRS0=+e/I=DA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7022492C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Sep 2020 16:51:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5982420C09
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Sep 2020 16:51:11 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726796AbgIWQvI (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 23 Sep 2020 12:51:08 -0400
Received: from mga06.intel.com ([134.134.136.31]:17994 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726381AbgIWQut (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 23 Sep 2020 12:50:49 -0400
IronPort-SDR: 
 cAtwwTepbPSHsdCY3SV8hJC373gLA2yReXYPI+xqCpnpGcO9+uHRR4ZS1b+TE2C3ReA/zlQ3WQ
 9s8Dr6WylfiA==
X-IronPort-AV: E=McAfee;i="6000,8403,9753"; a="222529024"
X-IronPort-AV: E=Sophos;i="5.77,293,1596524400";
   d="scan'208";a="222529024"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga004.jf.intel.com ([10.7.209.38])
  by orsmga104.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 23 Sep 2020 09:50:48 -0700
IronPort-SDR: 
 S2ARUoPugkAvYLcEzjtZ6EXsuKeT46j6cDERXO6JItuC4CUm78wsMf1d3MVyMcMv+q/piNmTau
 pZYZ/TkcOVmg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,293,1596524400";
   d="scan'208";a="454985293"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.160])
  by orsmga004.jf.intel.com with ESMTP; 23 Sep 2020 09:50:48 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH 0/4] KVM: VMX: Add helper+macros to do sec exec adjustment
Date: Wed, 23 Sep 2020 09:50:44 -0700
Message-Id: <20200923165048.20486-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add a helper function and macro wrappers to consolidate code for adjusting
secondary execution controls based on guest CPUID.  The adjustments are
effectively 10+ lines of copy+paste for each control, with slight tweaks
to account for annoying differences, e.g. XSAVES has additional checks.

Patches 1-3 are prep work to make INVPCID and RDTSCP align with the
"standard" nomenclature so that they don't require special casing.

Sean Christopherson (4):
  KVM: VMX: Rename vmx_*_supported() helpers to cpu_has_vmx_*()
  KVM: VMX: Unconditionally clear CPUID.INVPCID if !CPUID.PCID
  KVM: VMX: Rename RDTSCP secondary exec control name to insert "ENABLE"
  KVM: VMX: Add a helper and macros to reduce boilerplate for sec exec
    ctls

 arch/x86/include/asm/vmx.h                    |   2 +-
 arch/x86/kvm/vmx/capabilities.h               |  10 +-
 arch/x86/kvm/vmx/nested.c                     |   4 +-
 arch/x86/kvm/vmx/vmx.c                        | 150 +++++++-----------
 .../selftests/kvm/include/x86_64/vmx.h        |   2 +-
 5 files changed, 64 insertions(+), 104 deletions(-)
```
#### [PATCH v2 00/15] KVM: x86: VMX: Fix MSR namespacing
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Wed Sep 23 18:03:54 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11795403
Return-Path: <SRS0=+e/I=DA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 02ED7618
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Sep 2020 18:04:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E0056235FD
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Sep 2020 18:04:25 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726766AbgIWSEV (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 23 Sep 2020 14:04:21 -0400
Received: from mga05.intel.com ([192.55.52.43]:39920 "EHLO mga05.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726515AbgIWSEV (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 23 Sep 2020 14:04:21 -0400
IronPort-SDR: 
 Vs5B0MXa0Oo1UaAYS1v20plHBXk9Xtds1fBMM7+MNalEBNjrjsfoqA7ULONvMZrS4yJmbRC1Ot
 gItbTncnq5+A==
X-IronPort-AV: E=McAfee;i="6000,8403,9753"; a="245808953"
X-IronPort-AV: E=Sophos;i="5.77,293,1596524400";
   d="scan'208";a="245808953"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga002.jf.intel.com ([10.7.209.21])
  by fmsmga105.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 23 Sep 2020 11:04:11 -0700
IronPort-SDR: 
 2viIkAbMaqgxezyhz3M8YAUjBhe6d1JCM8KNzKI9D5/T0YHugyB2geqRkrwbi/iqse+frU5+uZ
 gZaApIISwT3Q==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,293,1596524400";
   d="scan'208";a="322670253"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.160])
  by orsmga002.jf.intel.com with ESMTP; 23 Sep 2020 11:04:10 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v2 00/15] KVM: x86: VMX: Fix MSR namespacing
Date: Wed, 23 Sep 2020 11:03:54 -0700
Message-Id: <20200923180409.32255-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
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

v2:
  - Rebased to kvm/queue, commit e1ba1a15af73 ("KVM: SVM: Enable INVPCID
    feature on AMD").

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
#### [PATCH 0/2] KVM: VMX: Super early file refactor for TDX
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Wed Sep 23 18:31:10 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11795485
Return-Path: <SRS0=+e/I=DA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8BEC21668
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Sep 2020 18:36:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7291D2193E
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Sep 2020 18:36:50 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726825AbgIWSgi (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 23 Sep 2020 14:36:38 -0400
Received: from mga01.intel.com ([192.55.52.88]:62893 "EHLO mga01.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726419AbgIWSgb (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 23 Sep 2020 14:36:31 -0400
IronPort-SDR: 
 pu1WlUPkEAIVm+sm7cktybZu5wOcnW59pPgT2MgJYtRAPptH1zevNzdRo5UrJDyHYWRNp98228
 r8oz/iwA83Zg==
X-IronPort-AV: E=McAfee;i="6000,8403,9753"; a="179071084"
X-IronPort-AV: E=Sophos;i="5.77,293,1596524400";
   d="scan'208";a="179071084"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by fmsmga101.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 23 Sep 2020 11:31:13 -0700
IronPort-SDR: 
 XCE25CZx9o4roeAASR1hBUV0R6VuwmCg7XyrXto6zd0cgXxwq7xYvcXnJIe5iTekicSGWKLzN+
 NqFRKAB0dYQQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,293,1596524400";
   d="scan'208";a="413082157"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.160])
  by fmsmga001.fm.intel.com with ESMTP; 23 Sep 2020 11:31:13 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Xiaoyao Li <xiaoyao.li@intel.com>
Subject: [PATCH 0/2] KVM: VMX: Super early file refactor for TDX
Date: Wed, 23 Sep 2020 11:31:10 -0700
Message-Id: <20200923183112.3030-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Rename vmx/ops.h to vmx/vmx_ops.h, and move VMX's posted interrupt support
to dedicated files in preparation for future Trust Domain Extensions (TDX)
enabling.

These changes are somewhat premature, as full TDX enabling is months away,
but the posted interrupts change is (IMO) valuable irrespective of TDX.

The value of the vmx_ops.h rename without TDX is debatable.  I have no
problem deferring the change to the actual TDX series if there are
objections.  I'm submitting the patch now as getting the rename upstream
will save us minor merge conflict pain if there are changes to vmx/ops.h
between now and whenever the TDX enabling series comes along.

https://software.intel.com/content/www/us/en/develop/articles/intel-trust-domain-extensions.html

Sean Christopherson (1):
  KVM: VMX: Rename ops.h to vmx_ops.h

Xiaoyao Li (1):
  KVM: VMX: Extract posted interrupt support to separate files

 arch/x86/kvm/Makefile                 |   3 +-
 arch/x86/kvm/vmx/posted_intr.c        | 332 ++++++++++++++++++++++++++
 arch/x86/kvm/vmx/posted_intr.h        |  99 ++++++++
 arch/x86/kvm/vmx/vmx.c                | 321 +------------------------
 arch/x86/kvm/vmx/vmx.h                |  92 +------
 arch/x86/kvm/vmx/{ops.h => vmx_ops.h} |   0
 6 files changed, 440 insertions(+), 407 deletions(-)
 create mode 100644 arch/x86/kvm/vmx/posted_intr.c
 create mode 100644 arch/x86/kvm/vmx/posted_intr.h
 rename arch/x86/kvm/vmx/{ops.h => vmx_ops.h} (100%)
```
#### [PATCH v2 0/8] KVM: x86/mmu: ITLB multi-hit workaround fixes
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Wed Sep 23 18:37:27 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11795491
Return-Path: <SRS0=+e/I=DA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3C785618
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Sep 2020 18:37:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 232AB2193E
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Sep 2020 18:37:41 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726861AbgIWShi (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 23 Sep 2020 14:37:38 -0400
Received: from mga14.intel.com ([192.55.52.115]:9454 "EHLO mga14.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726332AbgIWShi (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 23 Sep 2020 14:37:38 -0400
IronPort-SDR: 
 U7K1mg4muKoDpt4gMUOdyzARVDydOlwm06OBQvNkNstkrpstUsw/cPOlZTV7nYoGsAaYqOhkzl
 2VeuDJqHi0RA==
X-IronPort-AV: E=McAfee;i="6000,8403,9753"; a="160276859"
X-IronPort-AV: E=Sophos;i="5.77,293,1596524400";
   d="scan'208";a="160276859"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga005.jf.intel.com ([10.7.209.41])
  by fmsmga103.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 23 Sep 2020 11:37:37 -0700
IronPort-SDR: 
 xzdtHKopGeCmbqsC4quJMFzcNpajTENd5zQcy3HZ3WoY5zKm4LV5iC5ZpZEmgqz8j4dIJTFtCg
 3bFv1hzQmQrQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,293,1596524400";
   d="scan'208";a="486561611"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.160])
  by orsmga005.jf.intel.com with ESMTP; 23 Sep 2020 11:37:37 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Junaid Shahid <junaids@google.com>
Subject: [PATCH v2 0/8] KVM: x86/mmu: ITLB multi-hit workaround fixes
Date: Wed, 23 Sep 2020 11:37:27 -0700
Message-Id: <20200923183735.584-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Patch 1 is a minor fix for a very theoretical bug where KVM could skip
the final "commit zap" when recovering shadow pages for the NX huge
page mitigation.

Patch 2 is cleanup that's made possible by patch 1.

Patches 3-5 are the main course and fix bugs in the NX huge page
accounting where shadow pages are incorrectly added to the list of
disallowed huge pages.  KVM doesn't actually check to see if the page
could actually have been a large page when adding to the disallowed list.
This result in what are effectively spurious zaps.  The biggest issue is
likely with shadow pages in the upper levels, i.e. levels 3 and 4, as they
are either unlikely to be huge (1gb) or flat out can't be huge (512tb).
And because of the way KVM zaps, the upper levels will be zapped first,
i.e. KVM is likely zapping and rebuilding a decent number of its shadow
pages for zero benefit.

Ideally, patches 3-5 would be a single patch to ease backporting.  In the
end, I decided the change is probably not suitable for stable as at worst
it creates an infrequent performance spike (assuming the admin isn't going
crazy with the recovery frequency), and it's far from straightforward or
risk free.  Cramming everything into a single patch was a mess.

Patches 6-8 are cleanups in related code.  The 'hlevel' name in particular
has been on my todo list for a while.

v2:
  - Rebased to kvm/queue, commit e1ba1a15af73 ("KVM: SVM: Enable INVPCID
    feature on AMD").

Sean Christopherson (8):
  KVM: x86/mmu: Commit zap of remaining invalid pages when recovering
    lpages
  KVM: x86/mmu: Refactor the zap loop for recovering NX lpages
  KVM: x86/mmu: Move "huge page disallowed" calculation into mapping
    helpers
  KVM: x86/mmu: Capture requested page level before NX huge page
    workaround
  KVM: x86/mmu: Account NX huge page disallowed iff huge page was
    requested
  KVM: x86/mmu: Rename 'hlevel' to 'level' in FNAME(fetch)
  KVM: x86/mmu: Hoist ITLB multi-hit workaround check up a level
  KVM: x86/mmu: Track write/user faults using bools

 arch/x86/kvm/mmu/mmu.c         | 58 +++++++++++++++++++++-------------
 arch/x86/kvm/mmu/paging_tmpl.h | 39 ++++++++++++-----------
 2 files changed, 57 insertions(+), 40 deletions(-)
```
#### [PATCH v2 0/7]  KVM: nVMX: Bug fixes and cleanup
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Wed Sep 23 18:44:45 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11795521
Return-Path: <SRS0=+e/I=DA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5360C112E
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Sep 2020 18:45:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3BBF12376E
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Sep 2020 18:45:26 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726694AbgIWSoy (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 23 Sep 2020 14:44:54 -0400
Received: from mga07.intel.com ([134.134.136.100]:14506 "EHLO mga07.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726572AbgIWSoy (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 23 Sep 2020 14:44:54 -0400
IronPort-SDR: 
 e0/So8Fod/wGXYrSmkcRHgJLjmBa/PSCyUBh3/t4LKDYi8HGUQaUVVENF7YnxzLq50Q45YkNvu
 qhX1ckkkGkbg==
X-IronPort-AV: E=McAfee;i="6000,8403,9753"; a="225124469"
X-IronPort-AV: E=Sophos;i="5.77,293,1596524400";
   d="scan'208";a="225124469"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga003.fm.intel.com ([10.253.24.29])
  by orsmga105.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 23 Sep 2020 11:44:53 -0700
IronPort-SDR: 
 AG21uKJ436RIhpwWxjdI38cfG5EviAAvcqTu/07YPugVMhGwvDhfNfrDpdU+xlWpNDW1tcwOgi
 te3FdDBE8Dtg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,293,1596524400";
   d="scan'208";a="347457640"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.160])
  by FMSMGA003.fm.intel.com with ESMTP; 23 Sep 2020 11:44:52 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Dan Cross <dcross@google.com>,
        Peter Shier <pshier@google.com>
Subject: [PATCH v2 0/7]  KVM: nVMX: Bug fixes and cleanup
Date: Wed, 23 Sep 2020 11:44:45 -0700
Message-Id: <20200923184452.980-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Fix for a brutal segment caching bug that manifested as random nested
VM-Enter failures when running with unrestricted guest disabled.  A few
more bug fixes and cleanups for stuff found by inspection when hunting
down the caching issue.

v2:
  - Rebased to kvm/queue, commit e1ba1a15af73 ("KVM: SVM: Enable INVPCID
    feature on AMD").

Sean Christopherson (7):
  KVM: nVMX: Reset the segment cache when stuffing guest segs
  KVM: nVMX: Reload vmcs01 if getting vmcs12's pages fails
  KVM: nVMX: Explicitly check for valid guest state for !unrestricted
    guest
  KVM: nVMX: Move free_nested() below vmx_switch_vmcs()
  KVM: nVMX: Ensure vmcs01 is the loaded VMCS when freeing nested state
  KVM: nVMX: Drop redundant VMCS switch and free_nested() call
  KVM: nVMX: WARN on attempt to switch the currently loaded VMCS

 arch/x86/kvm/vmx/nested.c | 103 ++++++++++++++++++++------------------
 arch/x86/kvm/vmx/vmx.c    |   8 +--
 arch/x86/kvm/vmx/vmx.h    |   9 ++++
 3 files changed, 65 insertions(+), 55 deletions(-)
```
#### [PATCH v2 0/7] KVM: x86: Tracepoint improvements and fixes
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Wed Sep 23 20:13:42 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11795641
Return-Path: <SRS0=+e/I=DA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 32CE8618
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Sep 2020 20:14:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1FCA023899
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Sep 2020 20:14:14 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726599AbgIWUNu (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 23 Sep 2020 16:13:50 -0400
Received: from mga12.intel.com ([192.55.52.136]:49295 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726381AbgIWUNu (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 23 Sep 2020 16:13:50 -0400
IronPort-SDR: 
 wCdSiOs0vQx+K6ecUit0n5dkoIZWUio1IRk5CkYXWQeUe645YCqLRVc53YOq6Yae2BS853GBq3
 1ubL57nGuteA==
X-IronPort-AV: E=McAfee;i="6000,8403,9753"; a="140472231"
X-IronPort-AV: E=Sophos;i="5.77,293,1596524400";
   d="scan'208";a="140472231"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga007.jf.intel.com ([10.7.209.58])
  by fmsmga106.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 23 Sep 2020 13:13:50 -0700
IronPort-SDR: 
 JfVoEbr6rZsBOcmB4MbTv8wPbPNLewwFXo5cbufAx/Tcpkxlz7F6ztJku6Df5R/rIAvnGXEJGg
 maqhCJcxx9Sg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,293,1596524400";
   d="scan'208";a="349004933"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.160])
  by orsmga007.jf.intel.com with ESMTP; 23 Sep 2020 13:13:50 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v2 0/7] KVM: x86: Tracepoint improvements and fixes
Date: Wed, 23 Sep 2020 13:13:42 -0700
Message-Id: <20200923201349.16097-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Various improvements and fixes for the kvm_entry, kvm_exit and
kvm_nested_vmexit tracepoints.

  1. Capture the guest's RIP during kvm_entry for obvious reasons.

  2. Extend kvm_exit to report the same info as kvm_nested_vmexit, and
     macrofy its definition to reuse it verbatim for nested exits.

  3. Stop passing in params to kvm_nested_vmexit, and instead use the
     same approach (and now code) as kvm_exit where the tracepoint uses a
     dedicated kvm_x86_ops hook to retrieve the info.

  4. Stop reading GUEST_RIP, EXIT_QUAL, INTR_INFO, and ERROR_CODE on
     every VM-Exit from L2 (some of this comes in #3).  This saves ~100
     cycles (150+ with retpolines) on VM-Exits from L2 that are handled
     by L0, e.g. hardware interrupts.

As noted by Vitaly, these changes break trace-cmd[*].  I hereby pinky
swear that, if this series is merged, I will send patches to update
trace-cmd.

[*] git://git.kernel.org/pub/scm/utils/trace-cmd/trace-cmd.git

v2:
  - Fixed some goofs in the changelogs.
  - Rebased to kvm/queue, commit e1ba1a15af73 ("KVM: SVM: Enable INVPCID
    feature on AMD").

Sean Christopherson (7):
  KVM: x86: Add RIP to the kvm_entry, i.e. VM-Enter, tracepoint
  KVM: x86: Read guest RIP from within the kvm_nested_vmexit tracepoint
  KVM: VMX: Add a helper to test for a valid error code given an intr
    info
  KVM: x86: Add intr/vectoring info and error code to kvm_exit
    tracepoint
  KVM: x86: Add macro wrapper for defining kvm_exit tracepoint
  KVM: x86: Use common definition for kvm_nested_vmexit tracepoint
  KVM: nVMX: Read EXIT_QUAL and INTR_INFO only when needed for nested
    exit

 arch/x86/include/asm/kvm_host.h |   7 ++-
 arch/x86/kvm/svm/svm.c          |  16 ++---
 arch/x86/kvm/trace.h            | 107 +++++++++++++-------------------
 arch/x86/kvm/vmx/nested.c       |  14 ++---
 arch/x86/kvm/vmx/vmcs.h         |   7 +++
 arch/x86/kvm/vmx/vmx.c          |  18 +++++-
 arch/x86/kvm/x86.c              |   2 +-
 7 files changed, 86 insertions(+), 85 deletions(-)
```
#### [PATCH 0/4] KVM: x86/mmu: Page fault handling cleanups
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Wed Sep 23 22:04:21 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11795671
Return-Path: <SRS0=+e/I=DA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 00C71618
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Sep 2020 22:04:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E1D7B235FD
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Sep 2020 22:04:38 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726605AbgIWWE1 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 23 Sep 2020 18:04:27 -0400
Received: from mga11.intel.com ([192.55.52.93]:60138 "EHLO mga11.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726199AbgIWWE1 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 23 Sep 2020 18:04:27 -0400
IronPort-SDR: 
 hZJCBN3wvXXHfsSb94AwEm1htFsxaq8VIsV4Juj+AuI+bVL/bPK+cYo00o/H0jRBigRAFDXhm2
 d68LcKNxh0tg==
X-IronPort-AV: E=McAfee;i="6000,8403,9753"; a="158381351"
X-IronPort-AV: E=Sophos;i="5.77,295,1596524400";
   d="scan'208";a="158381351"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga004.fm.intel.com ([10.253.24.48])
  by fmsmga102.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 23 Sep 2020 15:04:26 -0700
IronPort-SDR: 
 SbBoppeSUtxVda/CYgowXFdVBdZnT58iPc+A9OzyJMZASltR2sLt4NyW4SnQpM3FYwtnYDkMxm
 +lwKs46mjqjA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,295,1596524400";
   d="scan'208";a="335647632"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.160])
  by fmsmga004.fm.intel.com with ESMTP; 23 Sep 2020 15:04:26 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Kai Huang <kai.huang@intel.com>
Subject: [PATCH 0/4] KVM: x86/mmu: Page fault handling cleanups
Date: Wed, 23 Sep 2020 15:04:21 -0700
Message-Id: <20200923220425.18402-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Cleanups for page fault handling that were encountered during early TDX
enabling, but are worthwhile on their own.  Specifically, patch 4 fixes an
issue where KVM doesn't detect a spurious page fault (due to the fault
being fixed by a different pCPU+vCPU) and does the full gamut of writing
the SPTE, updating stats, and prefetching SPTEs.

Sean Christopherson (4):
  KVM: x86/mmu: Return -EIO if page fault returns RET_PF_INVALID
  KVM: x86/mmu: Invert RET_PF_* check when falling through to emulation
  KVM: x86/mmu: Return unique RET_PF_* values if the fault was fixed
  KVM: x86/mmu: Bail early from final #PF handling on spurious faults

 arch/x86/kvm/mmu/mmu.c         | 70 +++++++++++++++++++++-------------
 arch/x86/kvm/mmu/mmutrace.h    | 13 +++----
 arch/x86/kvm/mmu/paging_tmpl.h |  3 ++
 3 files changed, 52 insertions(+), 34 deletions(-)
```
#### [PATCH v3 0/2] KVM: x86/mmu: Zap orphaned kids for nested TDP MMU
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Wed Sep 23 22:14:04 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11795697
Return-Path: <SRS0=+e/I=DA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1B1D56CA
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Sep 2020 22:14:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0B090235FD
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Sep 2020 22:14:20 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726697AbgIWWOI (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 23 Sep 2020 18:14:08 -0400
Received: from mga11.intel.com ([192.55.52.93]:60899 "EHLO mga11.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726199AbgIWWOH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 23 Sep 2020 18:14:07 -0400
IronPort-SDR: 
 c3liBWrM2rqCvsng6CHEU/FDF+s31HoPe1zpeIBl374ZzOSfdjs9MdiIjaQIrE8Y0tQvZNj7IK
 lc9ko7XUFu5g==
X-IronPort-AV: E=McAfee;i="6000,8403,9753"; a="158382290"
X-IronPort-AV: E=Sophos;i="5.77,295,1596524400";
   d="scan'208";a="158382290"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga004.fm.intel.com ([10.253.24.48])
  by fmsmga102.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 23 Sep 2020 15:14:07 -0700
IronPort-SDR: 
 t2lbPFx3mpDlDBLib5ZflI7Sf5jj87656N7h2EACIRLu1xRytYiaCtCjwFTqkLB/C7eMErVZpZ
 snvTKTwPWpdQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,295,1596524400";
   d="scan'208";a="335651271"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.160])
  by fmsmga004.fm.intel.com with ESMTP; 23 Sep 2020 15:14:07 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Peter Shier <pshier@google.com>,
        Ben Gardon <bgardon@google.com>
Subject: [PATCH v3 0/2] KVM: x86/mmu: Zap orphaned kids for nested TDP MMU
Date: Wed, 23 Sep 2020 15:14:04 -0700
Message-Id: <20200923221406.16297-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Refreshed version of Ben's patch to zap orphaned MMU shadow pages so that
they don't turn into zombies.

v3:
  - Rebased to kvm/queue, commit e1ba1a15af73 ("KVM: SVM: Enable INVPCID
    feature on AMD").

Ben Gardon (1):
  KVM: x86/MMU: Recursively zap nested TDP SPs when zapping last/only
    parent

Sean Christopherson (1):
  KVM: x86/mmu: Move flush logic from mmu_page_zap_pte() to
    FNAME(invlpg)

 arch/x86/kvm/mmu/mmu.c         | 38 ++++++++++++++++++++++------------
 arch/x86/kvm/mmu/paging_tmpl.h |  7 +++++--
 2 files changed, 30 insertions(+), 15 deletions(-)
```
#### [RFC PATCH 0/3] KVM: Introduce "VM bugged" concept
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Wed Sep 23 22:45:27 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11795765
Return-Path: <SRS0=+e/I=DA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BF67E139F
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Sep 2020 22:45:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AB419208E4
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Sep 2020 22:45:51 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726684AbgIWWpd (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 23 Sep 2020 18:45:33 -0400
Received: from mga02.intel.com ([134.134.136.20]:41185 "EHLO mga02.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726199AbgIWWpc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 23 Sep 2020 18:45:32 -0400
IronPort-SDR: 
 2IVVcutblxPLIHmNyjGNuwUpFak5783EmNgbLQ6zbP/8vey/jMevbsny7xwceSVzby2C4pwroa
 /kAR4zYWcJAw==
X-IronPort-AV: E=McAfee;i="6000,8403,9753"; a="148698553"
X-IronPort-AV: E=Sophos;i="5.77,295,1596524400";
   d="scan'208";a="148698553"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga004.fm.intel.com ([10.253.24.48])
  by orsmga101.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 23 Sep 2020 15:45:32 -0700
IronPort-SDR: 
 J1/Cph9zE2IoIv9FqaGC+ceWMFJHwxEkjhilb2ZOjNuk9oeKV7hF68XZI2S5RsFxBN95q0EqeM
 KiQhOpKHilBg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,295,1596524400";
   d="scan'208";a="335660058"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.160])
  by fmsmga004.fm.intel.com with ESMTP; 23 Sep 2020 15:45:31 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Marc Zyngier <maz@kernel.org>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        linux-arm-kernel@lists.infradead.org,
        Huacai Chen <chenhc@lemote.com>,
        Aleksandar Markovic <aleksandar.qemu.devel@gmail.com>,
        linux-mips@vger.kernel.org, Paul Mackerras <paulus@ozlabs.org>,
        kvm-ppc@vger.kernel.org,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Janosch Frank <frankja@linux.ibm.com>,
        David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Claudio Imbrenda <imbrenda@linux.ibm.com>
Subject: [RFC PATCH 0/3] KVM: Introduce "VM bugged" concept
Date: Wed, 23 Sep 2020 15:45:27 -0700
Message-Id: <20200923224530.17735-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series introduces a concept we've discussed a few times in x86 land.
The crux of the problem is that x86 has a few cases where KVM could
theoretically encounter a software or hardware bug deep in a call stack
without any sane way to propagate the error out to userspace.

Another use case would be for scenarios where letting the VM live will
do more harm than good, e.g. we've been using KVM_BUG_ON for early TDX
enabling as botching anything related to secure paging all but guarantees
there will be a flood of WARNs and error messages because lower level PTE
operations will fail if an upper level operation failed.

The basic idea is to WARN_ONCE if a bug is encountered, kick all vCPUs out
to userspace, and mark the VM as bugged so that no ioctls() can be issued
on the VM or its devices/vCPUs.

RFC as I've done nowhere near enough testing to verify that rejecting the
ioctls(), evicting running vCPUs, etc... works as intended.

Sean Christopherson (3):
  KVM: Export kvm_make_all_cpus_request() for use in marking VMs as
    bugged
  KVM: Add infrastructure and macro to mark VM as bugged
  KVM: x86: Use KVM_BUG/KVM_BUG_ON to handle bugs that are fatal to the
    VM

 arch/x86/kvm/svm/svm.c   |  2 +-
 arch/x86/kvm/vmx/vmx.c   | 23 ++++++++++++--------
 arch/x86/kvm/x86.c       |  4 ++++
 include/linux/kvm_host.h | 45 ++++++++++++++++++++++++++++++++--------
 virt/kvm/kvm_main.c      | 11 +++++-----
 5 files changed, 61 insertions(+), 24 deletions(-)
```
