

#### [PATCH 0/2] kvm-unit-test: nVMX: Test GUEST_BNDCFGS VM-Entry control
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
From patchwork Tue Mar 17 01:21:33 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11441611
Return-Path: <SRS0=C8aH=5C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0F3611874
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 17 Mar 2020 01:21:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E222B2051A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 17 Mar 2020 01:21:56 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="pffBb7sb"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1733124AbgCQBVy (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 16 Mar 2020 21:21:54 -0400
Received: from userp2120.oracle.com ([156.151.31.85]:57972 "EHLO
        userp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1733104AbgCQBVx (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 16 Mar 2020 21:21:53 -0400
Received: from pps.filterd (userp2120.oracle.com [127.0.0.1])
        by userp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 02H1I2Ro179228;
        Tue, 17 Mar 2020 01:21:48 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id; s=corp-2020-01-29;
 bh=f7CQW5yD+bNNHJvpMDW69FmUb46A0zpHFlOpybxLz4I=;
 b=pffBb7sbyQ1fMdVTzVH1FiPXnXiB/r8kPc1eebgAfs/CyyYFCYJjioDF2guA3u4vPhuv
 S+ypMiiCqGJtv4LaBewRM106NbJaZEPFqTemuEcq2RmHNO+Nhf+j5AyRQtYAAyVcSyOo
 u+84wa2dYer4+5rDbUv8flrL08ytMK8SlDeOwxBR5zveEwsxl1tvZ1QYoTwGlLZrZrhN
 A/DEDlJ46swaGar9epQ5X9vdeKPSSex+ntUaUOoLPgW9cVAUhkxkeJgR4SocG50MQYyF
 aDFAl60lwb4fawYi4d6N2/l9ilLx001XzdG3S1P6uRpXsD3kMl1VJpFlWOnkuDSorfCa zQ==
Received: from aserp3030.oracle.com (aserp3030.oracle.com [141.146.126.71])
        by userp2120.oracle.com with ESMTP id 2yrqwn1w3u-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 17 Mar 2020 01:21:48 +0000
Received: from pps.filterd (aserp3030.oracle.com [127.0.0.1])
        by aserp3030.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 02H1KgWS064787;
        Tue, 17 Mar 2020 01:21:47 GMT
Received: from userv0122.oracle.com (userv0122.oracle.com [156.151.31.75])
        by aserp3030.oracle.com with ESMTP id 2ys8tqs4t6-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 17 Mar 2020 01:21:47 +0000
Received: from abhmp0006.oracle.com (abhmp0006.oracle.com [141.146.116.12])
        by userv0122.oracle.com (8.14.4/8.14.4) with ESMTP id 02H1LknT008917;
        Tue, 17 Mar 2020 01:21:46 GMT
Received: from sadhukhan-nvmx.osdevelopmeniad.oraclevcn.com (/100.100.231.182)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Mon, 16 Mar 2020 18:21:45 -0700
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com,
        sean.j.christopherson@intel.com
Subject: [PATCH 0/2] kvm-unit-test: nVMX: Test GUEST_BNDCFGS VM-Entry control
 on vmentry of nested guests
Date: Tue, 17 Mar 2020 01:21:33 +0000
Message-Id: <1584408095-16591-1-git-send-email-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 1.8.3.1
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9562
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 adultscore=0
 phishscore=0 mlxscore=0
 malwarescore=0 suspectscore=13 mlxlogscore=626 spamscore=0 bulkscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2003020000
 definitions=main-2003170003
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9562
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 lowpriorityscore=0 mlxlogscore=703
 mlxscore=0 bulkscore=0 phishscore=0 spamscore=0 suspectscore=13
 malwarescore=0 priorityscore=1501 clxscore=1015 adultscore=0
 impostorscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2003020000 definitions=main-2003170003
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Patch# 1: Adds the required enum values to the header file
Patch# 2: Adds the test code


[PATCH 1/2] kvm-unit-test: VMX: Add enum for GUEST_BNDCFGS field and LOAD_BNDCFGS
[PATCH 2/2] kvm-unit-test: nVMX: Test GUEST_BNDCFGS VM-Entry control on vmentry of

 x86/vmx.h       |  2 ++
 x86/vmx_tests.c | 53 +++++++++++++++++++++++++++++++++++++++++++++++++++++
 2 files changed, 55 insertions(+)

Krish Sadhukhan (2):
      VMX: Add enum for GUEST_BNDCFGS field and LOAD_BNDCFGS vmentry control fie
      nVMX: Test GUEST_BNDCFGS VM-Entry control on vmentry of nested guests
```
#### [PATCH v6 0/5] x86/kvm/hyper-v: add support for synthetic debugger
##### From: Jon Doron <arilou@gmail.com>

```c
From patchwork Tue Mar 17 03:47:59 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jon Doron <arilou@gmail.com>
X-Patchwork-Id: 11441667
Return-Path: <SRS0=C8aH=5C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9FB9D13B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 17 Mar 2020 03:48:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 804E720663
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 17 Mar 2020 03:48:30 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="D0YlpZUx"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726416AbgCQDs0 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 16 Mar 2020 23:48:26 -0400
Received: from mail-wr1-f67.google.com ([209.85.221.67]:37171 "EHLO
        mail-wr1-f67.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726082AbgCQDs0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 16 Mar 2020 23:48:26 -0400
Received: by mail-wr1-f67.google.com with SMTP id 6so23825290wre.4;
        Mon, 16 Mar 2020 20:48:25 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=FrKlI3sd00+t1N/OzNDhMxZ6Gkz1BB4AwGkkgntEVIU=;
        b=D0YlpZUxZXl0ocStqqZ8JRBOU64KdAWnHdiKFg9shQ/OR4Op9SINZCdUQmm4gXN+Ul
         wLtpt98z6sc9LqYUwfcTqIcxjf3mgkKpY0Gw/rXk6FS90olTq44DQpHF94l1cHRW0Tz/
         gI818jSLzO1dx1NwwR/+d3ushN/uEMktaw+/XJzt2MMOol6SBKTQmFb5T5uc9XUycgCY
         Z6lJ4BSdd+MFvCr96qOue2seEd9LckycNO3Qdk5XYjENSaqlBxlvy3//7X8Xf7Jq9nbi
         Eq0GwhXGIW5JAaFU1yftfTGpdi6G2+wItF1gnwsil8eWRcBmf5JZKWrf0dqUPI+9/Vx+
         KaZA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=FrKlI3sd00+t1N/OzNDhMxZ6Gkz1BB4AwGkkgntEVIU=;
        b=GT8mOkhpQofmY0ky+blyx3FjWyFYFYLlhnxIuys7EMkY/UHXKmmQ34RoZv1Om83FGz
         8omHLbI82Bc+u3C91beKnv4lMlwV8uuNrqVa5MG6pcI8GZqmx4G9pSkaXh3Qsn/KGV/V
         wyrzQRAYMbP9tln6QjDJ0xP+7oxXe+5t1pga8ijnMmf4sp1qU4MKd0jnS5AV+nmccHwI
         NcEkKTP/O94+dfWrJo4ptLIBUdBZHupSuGiPwrALybIyTUmvRQbKfgoEi100+i6r6Fh0
         EvcjBthhm7n2Do4wbfuLaCR2GYkMD4BvFcmYYHKOWfNStyj4HssbVxe2hLSeBywooVV5
         gKWg==
X-Gm-Message-State: ANhLgQ1fwPGvX6h+FPwZE/hR2gS8rw7/HEccdI5P/KxHGacne1C0QSeX
        zEkD9GncDktgSE7PJ3craTnc8ZyoCK4=
X-Google-Smtp-Source: 
 ADFU+vsOLrCitUkZGjpfFFU6lT84rq+gBAhbdnqEN6gYJq5Z/Rs0bY3AKGXGLxi6NHK129Hkljb6jg==
X-Received: by 2002:a5d:69c1:: with SMTP id s1mr3239639wrw.351.1584416904565;
        Mon, 16 Mar 2020 20:48:24 -0700 (PDT)
Received: from jondnuc.lan (IGLD-84-229-155-229.inter.net.il.
 [84.229.155.229])
        by smtp.gmail.com with ESMTPSA id
 c23sm1457757wrb.79.2020.03.16.20.48.23
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 16 Mar 2020 20:48:23 -0700 (PDT)
From: Jon Doron <arilou@gmail.com>
To: kvm@vger.kernel.org, linux-hyperv@vger.kernel.org
Cc: vkuznets@redhat.com, Jon Doron <arilou@gmail.com>
Subject: [PATCH v6 0/5] x86/kvm/hyper-v: add support for synthetic debugger
Date: Tue, 17 Mar 2020 05:47:59 +0200
Message-Id: <20200317034804.112538-1-arilou@gmail.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add support for the synthetic debugger interface of hyper-v, the
synthetic debugger has 2 modes.
1. Use a set of MSRs to send/recv information (undocumented so it's not
   going to the hyperv-tlfs.h)
2. Use hypercalls

The first mode is based the following MSRs:
1. Control/Status MSRs which either asks for a send/recv .
2. Send/Recv MSRs each holds GPA where the send/recv buffers are.
3. Pending MSR, holds a GPA to a PAGE that simply has a boolean that
   indicates if there is data pending to issue a recv VMEXIT.

The first mode implementation is to simply exit to user-space when
either the control MSR or the pending MSR are being set.
Then it's up-to userspace to implement the rest of the logic of sending/recving.

In the second mode instead of using MSRs KNet will simply issue
Hypercalls with the information to send/recv, in this mode the data
being transferred is UDP encapsulated, unlike in the previous mode in
which you get just the data to send.

The new hypercalls will exit to userspace which will be incharge of
re-encapsulating if needed the UDP packets to be sent.

There is an issue though in which KDNet does not respect the hypercall
page and simply issues vmcall/vmmcall instructions depending on the cpu
type expecting them to be handled as it a real hypercall was issued.

It's important to note that part of this feature has been subject to be
removed in future versions of Windows, which is why some of the
defintions will not be present the the TLFS but in the kvm hyperv header
instead.

Jon Doron (5):
  x86/kvm/hyper-v: Explicitly align hcall param for kvm_hyperv_exit
  x86/hyper-v: Add synthetic debugger definitions
  x86/kvm/hyper-v: Add support for synthetic debugger capability
  x86/kvm/hyper-v: enable hypercalls regardless of hypercall page
  x86/kvm/hyper-v: Add support for synthetic debugger via hypercalls

 Documentation/virt/kvm/api.rst     |  18 ++++
 arch/x86/include/asm/hyperv-tlfs.h |   6 ++
 arch/x86/include/asm/kvm_host.h    |  13 +++
 arch/x86/kvm/hyperv.c              | 162 ++++++++++++++++++++++++++++-
 arch/x86/kvm/hyperv.h              |  32 ++++++
 arch/x86/kvm/trace.h               |  51 +++++++++
 arch/x86/kvm/x86.c                 |   9 ++
 include/uapi/linux/kvm.h           |  13 +++
 8 files changed, 302 insertions(+), 2 deletions(-)
```
#### [PATCH v2 00/32] KVM: x86: TLB flushing fixes and enhancements
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Tue Mar 17 04:52:06 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11441805
Return-Path: <SRS0=C8aH=5C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8F2CE1667
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 17 Mar 2020 04:56:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7A12C2071C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 17 Mar 2020 04:56:06 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726766AbgCQExJ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 17 Mar 2020 00:53:09 -0400
Received: from mga04.intel.com ([192.55.52.120]:34097 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726760AbgCQExJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 17 Mar 2020 00:53:09 -0400
IronPort-SDR: 
 3yMsGf9fnBLKMNiJZMyP47GgCyn6MAoSw/UWZu/xMiC3mNUecYCZwn5Y45T0dXkr+nPD3Omnb8
 uhypt6e7pMiw==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by fmsmga104.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 16 Mar 2020 21:53:08 -0700
IronPort-SDR: 
 3d28gK09PMBZ/J6yoSLgUKx3BNuzPShPJW+mwrgsT39SAcjuYY+Tl3QNShLTXf+TVPN7TXI5f3
 Ihjjsqj0XpqA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,563,1574150400";
   d="scan'208";a="355252721"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by fmsmga001.fm.intel.com with ESMTP; 16 Mar 2020 21:53:08 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Ben Gardon <bgardon@google.com>,
        Junaid Shahid <junaids@google.com>,
        Liran Alon <liran.alon@oracle.com>,
        Boris Ostrovsky <boris.ostrovsky@oracle.com>,
        John Haxby <john.haxby@oracle.com>,
        Miaohe Lin <linmiaohe@huawei.com>,
        Tom Lendacky <thomas.lendacky@amd.com>
Subject: [PATCH v2 00/32] KVM: x86: TLB flushing fixes and enhancements
Date: Mon, 16 Mar 2020 21:52:06 -0700
Message-Id: <20200317045238.30434-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is "v2" of the VMX TLB flushing cleanup series, but over 70% of the
patches are new in v2.  The new growth stems from two related revelations:

  1) Nested VMX doesn't properly flush all ASIDs/contexts on system events,
     e.g. on mmu_notifier invalidate all contexts for L1 *and* L2 need to
     be invalidated, but KVM generally only flushes L1 or L2 (or just L1).

  2) #1 is largely benign because nested VMX always flushes the new
     context on nested VM-Entry/VM-Exit.

High level overview:

  a) Fix the main TLB flushing bug with a big hammer.

  b) Fix a few other flushing related bugs.

  c) Clean up vmx_tlb_flush(), i.e. what was v1 of this series.

  d) Reintroduce current-ASID/context flushing to regain some of the
     precision that got blasted away by the big hammer in #1.

  e) Fix random code paths that unnecessarily trigger TLB flushes on
     nested VMX transitions.

  f) Stop flushing on every nested VMX transition.


v2:
  - Basically a new series.

v1:
  - https://patchwork.kernel.org/cover/11394987/

Junaid Shahid (2):
  KVM: nVMX: Invalidate all L2 roots when emulating INVVPID without EPT
  KVM: x86: Sync SPTEs when injecting page/EPT fault into L1

Sean Christopherson (30):
  KVM: VMX: Flush all EPTP/VPID contexts on remote TLB flush
  KVM: nVMX: Validate the EPTP when emulating INVEPT(EXTENT_CONTEXT)
  KVM: nVMX: Invalidate all EPTP contexts when emulating INVEPT for L1
  KVM: x86: Export kvm_propagate_fault() (as
    kvm_inject_emulated_page_fault)
  KVM: x86: Consolidate logic for injecting page faults to L1
  KVM: VMX: Skip global INVVPID fallback if vpid==0 in
    vpid_sync_context()
  KVM: VMX: Use vpid_sync_context() directly when possible
  KVM: VMX: Move vpid_sync_vcpu_addr() down a few lines
  KVM: VMX: Handle INVVPID fallback logic in vpid_sync_vcpu_addr()
  KVM: VMX: Drop redundant capability checks in low level INVVPID
    helpers
  KVM: nVMX: Use vpid_sync_vcpu_addr() to emulate INVVPID with address
  KVM: x86: Move "flush guest's TLB" logic to separate kvm_x86_ops hook
  KVM: VMX: Clean up vmx_flush_tlb_gva()
  KVM: x86: Drop @invalidate_gpa param from kvm_x86_ops' tlb_flush()
  KVM: SVM: Wire up ->tlb_flush_guest() directly to svm_flush_tlb()
  KVM: VMX: Move vmx_flush_tlb() to vmx.c
  KVM: nVMX: Move nested_get_vpid02() to vmx/nested.h
  KVM: VMX: Introduce vmx_flush_tlb_current()
  KVM: SVM: Document the ASID logic in svm_flush_tlb()
  KVM: x86: Rename ->tlb_flush() to ->tlb_flush_all()
  KVM: nVMX: Add helper to handle TLB flushes on nested VM-Enter/VM-Exit
  KVM: x86: Introduce KVM_REQ_TLB_FLUSH_CURRENT to flush current ASID
  KVM: x86/mmu: Use KVM_REQ_TLB_FLUSH_CURRENT for MMU specific flushes
  KVM: nVMX: Selectively use TLB_FLUSH_CURRENT for nested
    VM-Enter/VM-Exit
  KVM: nVMX: Reload APIC access page on nested VM-Exit only if necessary
  KVM: VMX: Retrieve APIC access page HPA only when necessary
  KVM: VMX: Don't reload APIC access page if its control is disabled
  KVM: x86/mmu: Add module param to force TLB flush on root reuse
  KVM: nVMX: Don't flush TLB on nested VM transition with EPT enabled
  KVM: nVMX: Free only the affected contexts when emulating INVEPT

 arch/x86/include/asm/kvm_host.h |  16 ++-
 arch/x86/kvm/mmu/mmu.c          |  26 ++--
 arch/x86/kvm/mmu/paging_tmpl.h  |   2 +-
 arch/x86/kvm/svm.c              |  19 ++-
 arch/x86/kvm/vmx/nested.c       | 202 ++++++++++++++++++++------------
 arch/x86/kvm/vmx/nested.h       |   7 ++
 arch/x86/kvm/vmx/ops.h          |  32 +++--
 arch/x86/kvm/vmx/vmx.c          | 110 ++++++++++++++---
 arch/x86/kvm/vmx/vmx.h          |  19 +--
 arch/x86/kvm/x86.c              |  65 ++++++----
 arch/x86/kvm/x86.h              |   6 +
 11 files changed, 334 insertions(+), 170 deletions(-)
```
#### [PATCH 0/2 v2] kvm-unit-test: nVMX: Test GUEST_BNDCFGS VM-Entry
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
From patchwork Tue Mar 17 19:15:28 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11443821
Return-Path: <SRS0=C8aH=5C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 445411668
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 17 Mar 2020 19:15:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 22C6320714
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 17 Mar 2020 19:15:53 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="kU60hfls"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726530AbgCQTPw (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 17 Mar 2020 15:15:52 -0400
Received: from userp2120.oracle.com ([156.151.31.85]:60648 "EHLO
        userp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726388AbgCQTPw (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 17 Mar 2020 15:15:52 -0400
Received: from pps.filterd (userp2120.oracle.com [127.0.0.1])
        by userp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 02HJDg6J080937;
        Tue, 17 Mar 2020 19:15:47 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id; s=corp-2020-01-29;
 bh=qD3tunIHYjcyV2L391CyBWutsEdfGEmsYgrnzEg7/do=;
 b=kU60hflsxvBEekTwCKSMxCW5dZPLXxIGcyq2+NUB/lCqMvYpIcaVf/fKaNksQxE3gf3q
 KLI03+tZ2ciPnp313V6x1f9c0fXOPlUQWcIS9MmwWEkd0dlW9E3Lm1kuPXmW9aGUbR0s
 sjj7aoTXVVDm28eyppldM3nD27j9o17rFXW0bl1jh7yd3xZLQ//D6vx09ow6OPjw0ABw
 J3WXHV1iWXvlOIWEoaN4Gz6NgdVq+oKiLyZseFmnwgjI5PPOEbzxF1wPQQ7rn/N6fPWN
 THznGhHw5PqaFfGkK1WTXCiko3fJ/PPzzhQ5NYoiTgBJdxkFx9BCIP9QZmtYfCQBEYGw Dw==
Received: from aserp3030.oracle.com (aserp3030.oracle.com [141.146.126.71])
        by userp2120.oracle.com with ESMTP id 2yrqwn6q4f-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 17 Mar 2020 19:15:46 +0000
Received: from pps.filterd (aserp3030.oracle.com [127.0.0.1])
        by aserp3030.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 02HJCacc021289;
        Tue, 17 Mar 2020 19:15:46 GMT
Received: from aserv0121.oracle.com (aserv0121.oracle.com [141.146.126.235])
        by aserp3030.oracle.com with ESMTP id 2ys8tscwg1-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 17 Mar 2020 19:15:46 +0000
Received: from abhmp0017.oracle.com (abhmp0017.oracle.com [141.146.116.23])
        by aserv0121.oracle.com (8.14.4/8.13.8) with ESMTP id 02HJFjL8010160;
        Tue, 17 Mar 2020 19:15:45 GMT
Received: from sadhukhan-nvmx.osdevelopmeniad.oraclevcn.com (/100.100.231.182)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Tue, 17 Mar 2020 12:15:45 -0700
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com,
        sean.j.christopherson@intel.com
Subject: [PATCH 0/2 v2] kvm-unit-test: nVMX: Test GUEST_BNDCFGS VM-Entry
 control on vmentry of nested guests
Date: Tue, 17 Mar 2020 19:15:28 +0000
Message-Id: <1584472530-31728-1-git-send-email-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 1.8.3.1
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9563
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 adultscore=0
 phishscore=0 mlxscore=0
 malwarescore=0 suspectscore=13 mlxlogscore=783 spamscore=0 bulkscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2003020000
 definitions=main-2003170074
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9563
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 lowpriorityscore=0 mlxlogscore=860
 mlxscore=0 bulkscore=0 phishscore=0 spamscore=0 suspectscore=13
 malwarescore=0 priorityscore=1501 clxscore=1015 adultscore=0
 impostorscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2003020000 definitions=main-2003170074
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

v1 -> v2:
	Rebased to the latest Upstream repo. No other changes.


Patch# 1: Adds the required enum values to the header file
Patch# 2: Adds the test code

[PATCH 1/2 v2] kvm-unit-test: VMX: Add enum for GUEST_BNDCFGS field and LOAD_BNDCFGS
[PATCH 2/2 v2] kvm-unit-test: nVMX: Test GUEST_BNDCFGS VM-Entry control on vmentry of

 x86/vmx.h       |  2 ++
 x86/vmx_tests.c | 45 +++++++++++++++++++++++++++++++++++++++++++++
 2 files changed, 47 insertions(+)

Krish Sadhukhan (2):
      VMX: Add enum for GUEST_BNDCFGS field and LOAD_BNDCFGS vmentry control fie
      nVMX: Test GUEST_BNDCFGS VM-Entry control on vmentry of nested guests
```
#### [PATCH 0/2] KVM: x86: CPUID tracepoint enhancements
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Tue Mar 17 19:53:52 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11443885
Return-Path: <SRS0=C8aH=5C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E71DF1668
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 17 Mar 2020 19:53:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id C674C206EC
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 17 Mar 2020 19:53:57 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726730AbgCQTx5 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 17 Mar 2020 15:53:57 -0400
Received: from mga07.intel.com ([134.134.136.100]:43598 "EHLO mga07.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726530AbgCQTx4 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 17 Mar 2020 15:53:56 -0400
IronPort-SDR: 
 nRHavrib3Ig8MbYf2o0K7mAiL+GxtPrCHGjtf9+LBqMW98TiLHwcohLBGsBAyuNh4DHFO3LtYu
 /o2Po1BrsOoQ==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga007.jf.intel.com ([10.7.209.58])
  by orsmga105.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 17 Mar 2020 12:53:55 -0700
IronPort-SDR: 
 sZRlNPJhdYT1bnnh1jFZqjJuXOWD5N4DSj5+9TdIF+zJ/lntfhmOTcP8eFFn+vt/JaH5koFds3
 Oiq6H8jciBxA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,565,1574150400";
   d="scan'208";a="233604297"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by orsmga007.jf.intel.com with ESMTP; 17 Mar 2020 12:53:55 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Xiaoyao Li <xiaoyao.li@intel.com>,
        Jan Kiszka <jan.kiszka@siemens.com>
Subject: [PATCH 0/2] KVM: x86: CPUID tracepoint enhancements
Date: Tue, 17 Mar 2020 12:53:52 -0700
Message-Id: <20200317195354.28384-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Two enhancements to the CPUID tracepoint.  Patch 01 was originally in the
CPUID ranges series, but I unintentionally dropped it in v2.

The final output looks like:

  kvm_cpuid: func 0 idx 0 rax d rbx 68747541 rcx 444d4163 rdx 69746e65, cpuid entry found
  kvm_cpuid: func d idx 444d4163 rax 0 rbx 0 rcx 0 rdx 0, cpuid entry not found
  kvm_cpuid: func 80000023 idx 1 rax f rbx 240 rcx 0 rdx 0, cpuid entry not found, used max basic
  kvm_cpuid: func 80000023 idx 2 rax 100 rbx 240 rcx 0 rdx 0, cpuid entry not found, used max basic

I also considered appending "exact" to the "found" case, which is more
directly what Jan suggested, but IMO "found exact" implies there's also a
"found inexact", which is not true.  AIUI, calling out that KVM is using
the max basic leaf values is what's really important to avoid confusion.

Ideally, the function of the max basic leaf would also be displayed, but
doing that without printing garbage for the other cases is a lot of ugly
code for marginal value.

Sean Christopherson (2):
  KVM: x86: Add requested index to the CPUID tracepoint
  KVM: x86: Add blurb to CPUID tracepoint when using max basic leaf
    values

 arch/x86/kvm/cpuid.c |  9 ++++++---
 arch/x86/kvm/trace.h | 18 ++++++++++++------
 2 files changed, 18 insertions(+), 9 deletions(-)
```
#### [PATCH 0/3] kvm-unit-test: nSVM: Add alternative (v2) test framework
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
From patchwork Tue Mar 17 20:05:34 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11443945
Return-Path: <SRS0=C8aH=5C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3A0101667
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 17 Mar 2020 20:44:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 11B8820714
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 17 Mar 2020 20:44:35 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="fSFwxW66"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726823AbgCQUoe (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 17 Mar 2020 16:44:34 -0400
Received: from userp2130.oracle.com ([156.151.31.86]:39276 "EHLO
        userp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726730AbgCQUod (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 17 Mar 2020 16:44:33 -0400
Received: from pps.filterd (userp2130.oracle.com [127.0.0.1])
        by userp2130.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 02HKiFu4046053;
        Tue, 17 Mar 2020 20:44:30 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=mime-version :
 message-id : date : from : to : cc : subject : content-type :
 content-transfer-encoding; s=corp-2020-01-29;
 bh=OdpgIhTvhAdO6ABMJZtItawg7Zcv3wS0co5iLt+/01w=;
 b=fSFwxW66DGK4ri9vd1VEfWy+7g58xiiLJ+eryuxqM9FpPyB+HUtgUYfuoGQgJN18IGp3
 Kh5RD6ATw9zKIg8yqsCon1kubZko1nkP0ey3c1+m5Q0dbjOeiNMmTUcGMkwJYs2mMKYF
 voViQdShBMhsPhFI4qAzzpXjDFVG8FrUzqkp4mvTIio8t8ymY7A7vWqXIOANipkVf4XD
 rAVtm+CQoI3CLgUxYx84aDzZUu8pcySFr0+hfUzvEr2ZqgdW1kj0GYOIfd9U5Ei9aL3q
 SbX21abxM3QvgWnHJFbD+Ebp91Ra0He3mTf3U0V2wy9potp1g1cR60Mbh3Ij1CkwkiTx 0Q==
Received: from userp3020.oracle.com (userp3020.oracle.com [156.151.31.79])
        by userp2130.oracle.com with ESMTP id 2yrppr79n3-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 17 Mar 2020 20:44:30 +0000
Received: from pps.filterd (userp3020.oracle.com [127.0.0.1])
        by userp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 02HKcVjR149082;
        Tue, 17 Mar 2020 20:44:30 GMT
Received: from aserv0122.oracle.com (aserv0122.oracle.com [141.146.126.236])
        by userp3020.oracle.com with ESMTP id 2ys8yyx3b0-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 17 Mar 2020 20:44:30 +0000
Received: from abhmp0010.oracle.com (abhmp0010.oracle.com [141.146.116.16])
        by aserv0122.oracle.com (8.14.4/8.14.4) with ESMTP id 02HKiTdD023933;
        Tue, 17 Mar 2020 20:44:29 GMT
Received: from ban25x6uut29.us.oracle.com (/10.153.73.29) by default (Oracle
 Beehive Gateway v4.0) with ESMTP ; Tue, 17 Mar 2020 13:43:16 -0700
MIME-Version: 1.0
Message-ID: <20200317200537.21593-1-krish.sadhukhan@oracle.com>
Date: Tue, 17 Mar 2020 13:05:34 -0700 (PDT)
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com
Subject: [PATCH 0/3] kvm-unit-test: nSVM: Add alternative (v2) test framework
 and add test for SVME.EFER vmcb field
X-Mailer: git-send-email 2.20.1
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9563
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 phishscore=0
 mlxlogscore=417 mlxscore=0
 adultscore=0 bulkscore=0 malwarescore=0 spamscore=0 suspectscore=13
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2003020000
 definitions=main-2003170077
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9563
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 malwarescore=0
 bulkscore=0
 suspectscore=13 lowpriorityscore=0 phishscore=0 adultscore=0 clxscore=1015
 impostorscore=0 priorityscore=1501 spamscore=0 mlxlogscore=472 mlxscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2003020000
 definitions=main-2003170077
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patchset builds on top of my previous patch titled:

	"[PATCH] kvm-unit-test: nSVM: Restructure nSVM test code"

The idea here is to create an alternative (v2) test framework that nVMX has
so that tests that don't need the functions that the current framework
requires, can be added.
Patch# 1: Adds the alternative (v2) framework.
Patch# 2: Adds helper functions for reading and writing vmcb fields by the
	  tests.
Patch# 3: Adds a test for SVME.EFER field.

[PATCH 1/3] kvm-unit-test: nSVM: Add alternative (v2) test format for nested guests
[PATCH 2/3] kvm-unit-test: nSVM: Add helper functions to write and read vmcb fields
[PATCH 3/3] kvm-unit-test: nSVM: Test SVME.EFER on VMRUN of nested guests

 x86/svm.c       | 91 ++++++++++++++++++++++++++++++++++++++++++++-------------
 x86/svm.h       |  8 +++++
 x86/svm_tests.c | 25 ++++++++++++++++
 3 files changed, 104 insertions(+), 20 deletions(-)

Krish Sadhukhan (3):
      nSVM: Add alternative (v2) test format for nested guests
      nSVM: Add helper functions to write and read vmcb fields
      nSVM: Test SVME.EFER on VMRUN of nested guests
```
