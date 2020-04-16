

#### [PATCH v2 00/10]  KVM: VMX: Unionize vcpu_vmx.exit_reason
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Wed Apr 15 17:55:09 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11491795
Return-Path: <SRS0=TyQv=57=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2D89A1392
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 15 Apr 2020 17:59:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1F1002084D
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 15 Apr 2020 17:59:00 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1416525AbgDORzf (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 15 Apr 2020 13:55:35 -0400
Received: from mga14.intel.com ([192.55.52.115]:26430 "EHLO mga14.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2437449AbgDORz0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 15 Apr 2020 13:55:26 -0400
IronPort-SDR: 
 SD3kBL3/MNWGAxxXyJ8CSTsfictFCgpK4W8UjKtnaC9F4ZKATkMBp+L717QKbjfk7zvC9JK+wF
 L/H/BOn/7XRA==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga001.jf.intel.com ([10.7.209.18])
  by fmsmga103.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 15 Apr 2020 10:55:22 -0700
IronPort-SDR: 
 9AQT2fPHHcmbXSk8vc4uuwqSR7T8sOOIjmbcjQpiEI14xL/xSQtIw7BdQ8c7nA1Iq1cyje/nPa
 K7/h1ke/QmMA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.72,387,1580803200";
   d="scan'208";a="332567335"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by orsmga001.jf.intel.com with ESMTP; 15 Apr 2020 10:55:22 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Xiaoyao Li <xiaoyao.li@intel.com>
Subject: [PATCH v2 00/10]  KVM: VMX: Unionize vcpu_vmx.exit_reason
Date: Wed, 15 Apr 2020 10:55:09 -0700
Message-Id: <20200415175519.14230-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Convert the exit_reason field in struct vcpu_vmx from a vanilla u32 to a
union, (ab)using the union to provide access to the basic exit reason and
flags.

There is a fairly substantial delta relative to v1, as I ran with Vitaly's
suggestion to split nested_vmx_exit_reflected() into VM-Fail, "L0 wants"
and "L1 wants", and move the tracepoint into nested_vmx_reflect_vmexit().
IMO, this yields cleaner and more understandable code overall, and helps
eliminate caching the basic exit reason (see below) by avoiding large
functions that repeatedly query the basic exit reason.  The refactoring
isn't strictly related to making exit_reason a union, but the code would
conflict horribly and the end code nicely demonstrates the value of using
a union for the exit reason.

There are three motivating factors for making exit_reason a union:

  - Help avoid bugs where a basic exit reason is compared against the full
    exit reason, e.g. there have been two bugs where MCE_DURING_VMENTRY
    was incorrectly compared against the full exit reason.

  - Clarify the intent of related flows, e.g. exit_reason is used for both
    "basic exit reason" and "full exit reason", and it's not always clear
    which of the two is intended without a fair bit of digging.

  - Prepare for future Intel features, e.g. SGX, that add new exit flags
    that are less restricted than FAILED_VMENTRY, i.e. can be set on what
    is otherwise a standard VM-Exit.

v2:
  - Don't snapshot the basic exit reason, i.e. either use vmx->exit_reason
    directly or snapshot the whole thing.  The resulting code is similar
    to Xiaoyao's original patch, e.g. vmx_handle_exit() now uses
    "exit_reason.basic" instead of "exit_reason" to reference the basic
    exit reason.
  - Split nested_vmx_exit_reflected() into VM-Fail, "L0 wants" and "L1
    wants", and move the tracepoint into nested_vmx_reflect_vmexit().
    [Vitaly]
  - Use a "union vmx_exit_reason exit_reason" to handle a consistency
    check VM-Exit on VM-Enter in nested_vmx_enter_non_root_mode() to avoid
    some implicit casting shenanigans. [Vitaly]
  - Collect tags. [Vitaly]

v1: https://lkml.kernel.org/r/20200312184521.24579-1-sean.j.christopherson@intel.com


Sean Christopherson (10):
  KVM: nVMX: Move reflection check into nested_vmx_reflect_vmexit()
  KVM: nVMX: Uninline nested_vmx_reflect_vmexit(), i.e. move it to
    nested.c
  KVM: nVMX: Move VM-Fail check out of nested_vmx_exit_reflected()
  KVM: nVMX: Move nested VM-Exit tracepoint into
    nested_vmx_reflect_vmexit()
  KVM: nVMX: Split VM-Exit reflection logic into L0 vs. L1 wants
  KVM: nVMX: Drop a superfluous WARN on reflecting EXTERNAL_INTERRUPT
  KVM: nVMX: Pull exit_reason from vcpu_vmx in
    nested_vmx_reflect_vmexit()
  KVM: nVMX: Cast exit_reason to u16 to check for nested
    EXTERNAL_INTERRUPT
  KVM: nVMX: Rename exit_reason to vm_exit_reason for nested VM-Exit
  KVM: VMX: Convert vcpu_vmx.exit_reason to a union

 arch/x86/kvm/vmx/nested.c | 237 +++++++++++++++++++++++++-------------
 arch/x86/kvm/vmx/nested.h |  32 +----
 arch/x86/kvm/vmx/vmx.c    |  66 ++++++-----
 arch/x86/kvm/vmx/vmx.h    |  25 +++-
 4 files changed, 219 insertions(+), 141 deletions(-)
```
#### [PATCH 0/2 v2] kvm-unit-test: nVMX: Test Selector and Base Address
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
From patchwork Wed Apr 15 18:30:45 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11491831
Return-Path: <SRS0=TyQv=57=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 484D613B2
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 15 Apr 2020 19:11:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2E4CF208E4
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 15 Apr 2020 19:11:24 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="UpDarNns"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2504366AbgDOTLW (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 15 Apr 2020 15:11:22 -0400
Received: from userp2120.oracle.com ([156.151.31.85]:45670 "EHLO
        userp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2411816AbgDOTLO (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 15 Apr 2020 15:11:14 -0400
Received: from pps.filterd (userp2120.oracle.com [127.0.0.1])
        by userp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 03FJ81im062677;
        Wed, 15 Apr 2020 19:11:03 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : mime-version : content-transfer-encoding;
 s=corp-2020-01-29; bh=m8H6UtNxuTOBnymt60AMZmFjPxTy2lbQkSEA1KZ4W5s=;
 b=UpDarNnsVSUHyUXseT4Ljz4tZmRW4s+JuxLdWy5kjJM66k2agHWpdE/bVSch4x0kgBy/
 7s6NuJu5Og8YyLg+9d0LxKUt/r6It6zQO20yGcnaVv+2XZITMmI9tNSdb8CRGvTIAkDR
 yNz5UZ/bTpKRsEIIB4khqIODF1tFYyDabeipMqqbqeAaKz5vILry+aEql85EF5HHUnb1
 AbzvuMHF8Kn+KsZ5VQn3VKrje0eRF6goiNtW8xhqdmMdEedoCdQf+DKjJ+SRxQjfiory
 wYs/Qi427kzArpVXWx6bKq7JXaRm3ffeD4Y+ITQvMe8qjS3i5nxkcOJGsQhD62AcoeaN 7g==
Received: from aserp3030.oracle.com (aserp3030.oracle.com [141.146.126.71])
        by userp2120.oracle.com with ESMTP id 30e0bfattg-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 15 Apr 2020 19:11:03 +0000
Received: from pps.filterd (aserp3030.oracle.com [127.0.0.1])
        by aserp3030.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 03FJ7I8f194297;
        Wed, 15 Apr 2020 19:11:02 GMT
Received: from aserv0122.oracle.com (aserv0122.oracle.com [141.146.126.236])
        by aserp3030.oracle.com with ESMTP id 30dn8wuaqj-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 15 Apr 2020 19:11:02 +0000
Received: from abhmp0004.oracle.com (abhmp0004.oracle.com [141.146.116.10])
        by aserv0122.oracle.com (8.14.4/8.14.4) with ESMTP id 03FJB2gs022938;
        Wed, 15 Apr 2020 19:11:02 GMT
Received: from ban25x6uut29.us.oracle.com (/10.153.73.29)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Wed, 15 Apr 2020 12:11:02 -0700
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com,
        sean.j.christopherson@intel.com
Subject: [PATCH 0/2 v2] kvm-unit-test: nVMX: Test Selector and Base Address
 fields of Guest Segment registers
Date: Wed, 15 Apr 2020 14:30:45 -0400
Message-Id: <20200415183047.11493-1-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9592
 signatures=668686
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 mlxscore=0
 mlxlogscore=859
 suspectscore=13 malwarescore=0 spamscore=0 phishscore=0 adultscore=0
 bulkscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2003020000 definitions=main-2004150141
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9592
 signatures=668686
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 malwarescore=0
 clxscore=1015
 priorityscore=1501 mlxscore=0 lowpriorityscore=0 mlxlogscore=911
 impostorscore=0 adultscore=0 suspectscore=13 phishscore=0 spamscore=0
 bulkscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2003020000 definitions=main-2004150141
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

v1 -> v2:
	1. A KVM fix has been added via patch# 1. This fix is required to test
	   the unsetting of "unrestricted guest" VM-execution control in
	   vmcs12.
	2. The kvm-unit-test has been enhanced by adding more combinations of
	   the conditions mentioned in the vmentry checks being tested here.
   

[PATCH 1/2 v2] KVM: nVMX: KVM needs to unset "unrestricted guest" VM-execution
[PATCH 2/2 v2] kvm-unit-tests: nVMX: Test Selector and Base Address fields of Guest Segment

 arch/x86/kvm/vmx/nested.c | 3 +++
 1 file changed, 3 insertions(+)

Krish Sadhukhan (1):
      nVMX: KVM needs to unset "unrestricted guest" VM-execution control in vmcs02 if vmcs12 doesn't set it

 Makefile            |   2 +-
 lib/x86/processor.h |   1 +
 x86/vmx_tests.c     | 201 ++++++++++++++++++++++++++++++++++++++++++++++++++++
 3 files changed, 203 insertions(+), 1 deletion(-)

Krish Sadhukhan (1):
      nVMX: Test Selector and Base Address fields of Guest Segment Registers on vmentry of nested guests
```
#### [PATCH 0/5] KVM: VMX: Add caching of EXIT_QUAL and INTR_INFO
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Wed Apr 15 20:34:49 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11491953
Return-Path: <SRS0=TyQv=57=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A68E56CA
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 15 Apr 2020 20:35:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8ECEB2078A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 15 Apr 2020 20:35:01 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S371305AbgDOUfA (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 15 Apr 2020 16:35:00 -0400
Received: from mga17.intel.com ([192.55.52.151]:20837 "EHLO mga17.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S371264AbgDOUe6 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 15 Apr 2020 16:34:58 -0400
IronPort-SDR: 
 DP5nnSE+MmmAeKfpA0yX+bamlUS0wVBXYZ+QRIjdlsucDxXKT06zbkqlkb6oq9HLuBkug0dznu
 i9SBaY47Hn2A==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga002.fm.intel.com ([10.253.24.26])
  by fmsmga107.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 15 Apr 2020 13:34:57 -0700
IronPort-SDR: 
 +eCiecRj5JwTD4XQ78Xz6RJ7HDntOl0+gxxtmn2Hag9EQuNFUnoGbbzTmLeZb+XnnCeFMoktER
 gVqknUIC4bkQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.72,388,1580803200";
   d="scan'208";a="288657636"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by fmsmga002.fm.intel.com with ESMTP; 15 Apr 2020 13:34:56 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH 0/5] KVM: VMX: Add caching of EXIT_QUAL and INTR_INFO
Date: Wed, 15 Apr 2020 13:34:49 -0700
Message-Id: <20200415203454.8296-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Patches 4-5 are the focus of this series, adding caching of
vmcs.EXIT_QUALIFICATION and proper caching of vmcs.INTR_INFO (instead of
caching it with ad hoc rules about when it's available).  Patches 1-3
are prep work to clean up the register caching to ensure correctness when
switching between vmcs01 and vmcs02.

The idea for this came about when working on the "unionize exit_reason"
series.  The nested VM-Exit logic looks at both fields multiple times,
which is ok-ish when everything is crammed into one or two functions, but
incurs multiple VMREADs when split up.  I really didn't want to solve that
issue by piling on more cases where vmx->exit_intr_info would be valid, or
by duplicating that fragile pattern for exit_qualification.

Paolo, this will conflict with the "unionize exit_reason" series, though
the conflict resolution is all mechnical in nature.  Let me know if you
want me to respin one on top of the other, send a single series, etc...

Sean Christopherson (5):
  KVM: nVMX: Invoke ept_save_pdptrs() if and only if PAE paging is
    enabled
  KVM: nVMX: Reset register cache (available and dirty masks) on VMCS
    switch
  KVM: nVMX: Drop manual clearing of segment cache on nested VMCS switch
  KVM: VMX: Cache vmcs.EXIT_QUALIFICATION using arch avail_reg flags
  KVM: VMX: Cache vmcs.EXIT_INTR_INFO using arch avail_reg flags

 arch/x86/include/asm/kvm_host.h |  2 +
 arch/x86/kvm/vmx/nested.c       | 29 +++++++------
 arch/x86/kvm/vmx/nested.h       |  4 +-
 arch/x86/kvm/vmx/vmx.c          | 73 ++++++++++++++++-----------------
 arch/x86/kvm/vmx/vmx.h          | 35 +++++++++++++++-
 5 files changed, 86 insertions(+), 57 deletions(-)
```
#### [PATCH 0/1] selftests: kvm: Overlapped memory regions test
##### From: Wainer dos Santos Moschetta <wainersm@redhat.com>

```c
From patchwork Wed Apr 15 20:45:04 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wainer dos Santos Moschetta <wainersm@redhat.com>
X-Patchwork-Id: 11491997
Return-Path: <SRS0=TyQv=57=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F299413B2
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 15 Apr 2020 20:45:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D9FD8208E4
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 15 Apr 2020 20:45:24 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="SRaOOkfT"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2442117AbgDOUpS (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 15 Apr 2020 16:45:18 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:22712 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S2442110AbgDOUpQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 15 Apr 2020 16:45:16 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1586983515;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc; bh=FVXdUC3nRqfOSbJCPvdVOcmnkWtSfavnoYKnSEh27Xc=;
        b=SRaOOkfTATpDeE/fSLr+Y14pGYfFxdCS/Z1ien01bj1c3PlbAaFy43jM8QFB3guy/+Z3Bh
        yiGErvQYKn3Vhyu1XUl9YzVHOzqoRjzMrU1SicAg6ZEJAxNRUdf3uqhez7fb+5jKxLhj4o
        o49a5ML44ibPSXVPjnZ3EOCUrulorO0=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-252-6Q5AUkr6P16CmMaFLJRvEA-1; Wed, 15 Apr 2020 16:45:13 -0400
X-MC-Unique: 6Q5AUkr6P16CmMaFLJRvEA-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 17C961005509;
        Wed, 15 Apr 2020 20:45:12 +0000 (UTC)
Received: from localhost.localdomain (ovpn-116-15.gru2.redhat.com
 [10.97.116.15])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 62EB15DA66;
        Wed, 15 Apr 2020 20:45:08 +0000 (UTC)
From: Wainer dos Santos Moschetta <wainersm@redhat.com>
To: pbonzini@redhat.com, kvm@vger.kernel.org
Cc: drjones@redhat.com, sean.j.christopherson@intel.com,
        linux-kernel@vger.kernel.org, linux-kselftest@vger.kernel.org,
        krish.sadhukhan@oracle.com
Subject: [PATCH 0/1] selftests: kvm: Overlapped memory regions test
Date: Wed, 15 Apr 2020 17:45:04 -0300
Message-Id: <20200415204505.10021-1-wainersm@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This introduces a test case to check memory slots with overlapped
regions on the guest address cannot be added. The cases checked
are described in the block comment upon test_overlap_memory_regions()
(see the patch 01).

I didn't see the need to calcute the addresses on compile/run-time, so I
just left them hard-coded (remember: aligned 1M to work on s390x).

It works on x86_64, aarch64, and s390x.

The patch is based on queue branch.

Ah, I did some cosmetic changes on test_add_max_memory_regions() too. If
it is not OK to be in a single patch...let me know.

Wainer dos Santos Moschetta (1):
  selftests: kvm: Add overlapped memory regions test

 .../selftests/kvm/set_memory_region_test.c    | 75 ++++++++++++++++++-
 1 file changed, 74 insertions(+), 1 deletion(-)
```
#### [PATCH 0/2] KVM: x86/mmu: Minor cleanup in try_async_pf()
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Wed Apr 15 21:44:12 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11492065
Return-Path: <SRS0=TyQv=57=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 96E5114DD
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 15 Apr 2020 21:45:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 86F5420784
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 15 Apr 2020 21:45:07 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730441AbgDOVoh (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 15 Apr 2020 17:44:37 -0400
Received: from mga02.intel.com ([134.134.136.20]:2384 "EHLO mga02.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729965AbgDOVoT (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 15 Apr 2020 17:44:19 -0400
IronPort-SDR: 
 wFj/djImGxDDMCfplq3+51oEMvM5fDzfHqb/4WjXi15ihaKNsqaj2zsTwwqxrKVqp5rSgEkLlg
 ie57TipOAffg==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga005.jf.intel.com ([10.7.209.41])
  by orsmga101.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 15 Apr 2020 14:44:15 -0700
IronPort-SDR: 
 mP2+PDzN60teQtLbePMMO6U7zyS3zNRQVJvl2S2ygWLdn0s77oMWgQjXcYG/cgnesKVh9vUGf3
 esKYMQl9hA8Q==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.72,388,1580803200";
   d="scan'208";a="427584259"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by orsmga005.jf.intel.com with ESMTP; 15 Apr 2020 14:44:15 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org,
        Rick Edgecombe <rick.p.edgecombe@intel.com>
Subject: [PATCH 0/2] KVM: x86/mmu: Minor cleanup in try_async_pf()
Date: Wed, 15 Apr 2020 14:44:12 -0700
Message-Id: <20200415214414.10194-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Two cleanups with no functional changes.

I'm not 100% on whether or not open coding the private memslot check in
patch 2 is a good idea.  Avoiding the extra memslot lookup is nice, but
that could be done by providing e.g. kvm_is_memslot_visible().  On one
hand, I like deferring the nonexistent and invalid checks to common code,
but on the other hand it creates the possibility of missing some future
case where kvm_is_gfn_visible() adds a check that's not also incoporated
into __gfn_to_hva_many(), though that seems like a rather unlikely
scenario.

Sean Christopherson (2):
  KVM: x86/mmu: Set @writable to false for non-visible accesses by L2
  KVM: x86/mmu: Avoid an extra memslot lookup in try_async_pf() for L2

 arch/x86/kvm/mmu/mmu.c | 10 ++++------
 1 file changed, 4 insertions(+), 6 deletions(-)
```
