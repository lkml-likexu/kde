#### [Bug 206579] KVM with passthrough generates "BUG: kernel NULL pointer dereference" and crashes
##### From: bugzilla-daemon@bugzilla.kernel.org

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: bugzilla-daemon@bugzilla.kernel.org
X-Patchwork-Id: 11408783
Return-Path: <SRS0=27T9=4P=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 677D51580
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 27 Feb 2020 14:49:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 47724246A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 27 Feb 2020 14:49:50 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730190AbgB0Ott convert rfc822-to-8bit (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 27 Feb 2020 09:49:49 -0500
Received: from mail.kernel.org ([198.145.29.99]:57796 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729517AbgB0Ott (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 27 Feb 2020 09:49:49 -0500
From: bugzilla-daemon@bugzilla.kernel.org
To: kvm@vger.kernel.org
Subject: [Bug 206579] KVM with passthrough generates "BUG: kernel NULL
 pointer dereference" and crashes
Date: Thu, 27 Feb 2020 14:49:47 +0000
X-Bugzilla-Reason: None
X-Bugzilla-Type: changed
X-Bugzilla-Watch-Reason: AssignedTo virtualization_kvm@kernel-bugs.osdl.org
X-Bugzilla-Product: Virtualization
X-Bugzilla-Component: kvm
X-Bugzilla-Version: unspecified
X-Bugzilla-Keywords: 
X-Bugzilla-Severity: normal
X-Bugzilla-Who: suravee.suthikulpanit@amd.com
X-Bugzilla-Status: NEW
X-Bugzilla-Resolution: 
X-Bugzilla-Priority: P1
X-Bugzilla-Assigned-To: virtualization_kvm@kernel-bugs.osdl.org
X-Bugzilla-Flags: 
X-Bugzilla-Changed-Fields: 
Message-ID: <bug-206579-28872-pjq6BvjJrG@https.bugzilla.kernel.org/>
In-Reply-To: <bug-206579-28872@https.bugzilla.kernel.org/>
References: <bug-206579-28872@https.bugzilla.kernel.org/>
X-Bugzilla-URL: https://bugzilla.kernel.org/
Auto-Submitted: auto-generated
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

https://bugzilla.kernel.org/show_bug.cgi?id=206579

--- Comment #26 from Suravee Suthikulpanit (suravee.suthikulpanit@amd.com) ---
There are several reason that could inhibit the AVIC from being activated even
though it is enabled during module load (i.e. modprobe kvm_amd avic=1).

Could you please try the following patch:

---- BEGIN PATCH ----

@@ -8051,6 +8052,7 @@ void kvm_request_apicv_update(struct kvm *kvm, bool
activate, ulong bit)
                        return;
        }

+       kvm->stat.apicv_inhibit_reasons = kvm->arch.apicv_inhibit_reasons;
        trace_kvm_apicv_update_request(activate, bit);
        if (kvm_x86_ops->pre_update_apicv_exec_ctrl)
                kvm_x86_ops->pre_update_apicv_exec_ctrl(kvm, activate);
---- END PATCH ----

Then, while running the VM, please run "cat
/sys/kernel/debug/kvm/*/apicv_inhibit_reasons". This should allow us to see why
KVM deactivate AVIC.

Trying your XML file in the description, I also noticed that AVIC is
deactivated for the VM. However, when I tries specifying EPYC-IBPB model in the
XML, then it creates the VM w/ AVIC activated. Could you please give it a try?

Thanks,
Suravee

```
#### [PATCH v4.1 36/36] KVM: s390: protvirt: Add KVM api documentation
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11408021
Return-Path: <SRS0=27T9=4P=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3387214BC
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 27 Feb 2020 08:47:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1BD222469E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 27 Feb 2020 08:47:24 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728854AbgB0IrX (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 27 Feb 2020 03:47:23 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:2224 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1728640AbgB0IrX (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 27 Feb 2020 03:47:23 -0500
Received: from pps.filterd (m0098420.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 01R8id0b079392;
        Thu, 27 Feb 2020 03:47:22 -0500
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 2ye711ew86-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 27 Feb 2020 03:47:22 -0500
Received: from m0098420.ppops.net (m0098420.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 01R8l2Ee118006;
        Thu, 27 Feb 2020 03:47:21 -0500
Received: from ppma01wdc.us.ibm.com (fd.55.37a9.ip4.static.sl-reverse.com
 [169.55.85.253])
        by mx0b-001b2d01.pphosted.com with ESMTP id 2ye711ew7x-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 27 Feb 2020 03:47:21 -0500
Received: from pps.filterd (ppma01wdc.us.ibm.com [127.0.0.1])
        by ppma01wdc.us.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 01R8is4U027674;
        Thu, 27 Feb 2020 08:47:21 GMT
Received: from b01cxnp22035.gho.pok.ibm.com (b01cxnp22035.gho.pok.ibm.com
 [9.57.198.25])
        by ppma01wdc.us.ibm.com with ESMTP id 2ydcmkkvfv-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 27 Feb 2020 08:47:21 +0000
Received: from b01ledav004.gho.pok.ibm.com (b01ledav004.gho.pok.ibm.com
 [9.57.199.109])
        by b01cxnp22035.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id 01R8lJ0L49742178
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 27 Feb 2020 08:47:19 GMT
Received: from b01ledav004.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 39B31112062;
        Thu, 27 Feb 2020 08:47:19 +0000 (GMT)
Received: from b01ledav004.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 2ACE1112061;
        Thu, 27 Feb 2020 08:47:19 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.114.17.106])
        by b01ledav004.gho.pok.ibm.com (Postfix) with ESMTP;
        Thu, 27 Feb 2020 08:47:19 +0000 (GMT)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: borntraeger@de.ibm.com, cohuck@redhat.com
Cc: Ulrich.Weigand@de.ibm.com, david@redhat.com, frankja@linux.ibm.com,
        frankja@linux.vnet.ibm.com, gor@linux.ibm.com,
        imbrenda@linux.ibm.com, kvm@vger.kernel.org,
        linux-s390@vger.kernel.org, mimu@linux.ibm.com, thuth@redhat.com
Subject: [PATCH v4.1 36/36] KVM: s390: protvirt: Add KVM api documentation
Date: Thu, 27 Feb 2020 03:47:17 -0500
Message-Id: <20200227084717.13449-1-borntraeger@de.ibm.com>
X-Mailer: git-send-email 2.25.0
In-Reply-To: <a392d135-c0aa-3513-b633-70aa6c7e88bd@de.ibm.com>
References: <a392d135-c0aa-3513-b633-70aa6c7e88bd@de.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-02-27_02:2020-02-26,2020-02-27 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 malwarescore=0 spamscore=0
 clxscore=1015 mlxlogscore=999 adultscore=0 mlxscore=0 bulkscore=0
 suspectscore=0 phishscore=0 lowpriorityscore=0 priorityscore=1501
 impostorscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2001150001 definitions=main-2002270071
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Janosch Frank <frankja@linux.ibm.com>

Add documentation for KVM_CAP_S390_PROTECTED capability and the
KVM_S390_PV_COMMAND ioctl.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
[borntraeger@de.ibm.com: patch merging, splitting, fixing]
Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---
 Documentation/virt/kvm/api.rst | 59 ++++++++++++++++++++++++++++++++++
 1 file changed, 59 insertions(+)

```
#### [PATCH] KVM: nVMX: Consult only the "basic" exit reason when routing nested exit
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11409071
Return-Path: <SRS0=27T9=4P=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E5E9713A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 27 Feb 2020 17:45:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id CEE30246B0
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 27 Feb 2020 17:45:02 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730788AbgB0RpA (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 27 Feb 2020 12:45:00 -0500
Received: from mga06.intel.com ([134.134.136.31]:18526 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1730669AbgB0Rok (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 27 Feb 2020 12:44:40 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga001.jf.intel.com ([10.7.209.18])
  by orsmga104.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 27 Feb 2020 09:44:38 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,492,1574150400";
   d="scan'208";a="317859094"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by orsmga001.jf.intel.com with ESMTP; 27 Feb 2020 09:44:38 -0800
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Xiaoyao Li <xiaoyao.li@intel.com>
Subject: [PATCH] KVM: nVMX: Consult only the "basic" exit reason when routing
 nested exit
Date: Thu, 27 Feb 2020 09:44:30 -0800
Message-Id: <20200227174430.26371-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Consult only the basic exit reason, i.e. bits 15:0 of vmcs.EXIT_REASON,
when determining whether a nested VM-Exit should be reflected into L1 or
handled by KVM in L0.

For better or worse, the switch statement in nested_vmx_exit_reflected()
currently defaults to "true", i.e. reflects any nested VM-Exit without
dedicated logic.  Because the case statements only contain the basic
exit reason, any VM-Exit with modifier bits set will be reflected to L1,
even if KVM intended to handle it in L0.

Practically speaking, this only affects EXIT_REASON_MCE_DURING_VMENTRY,
i.e. a #MC that occurs on nested VM-Enter would be incorrectly routed to
L1, as "failed VM-Entry" is the only modifier that KVM can currently
encounter.  The SMM modifiers will never be generated as KVM doesn't
support/employ a SMI Transfer Monitor.  Ditto for "exit from enclave",
as KVM doesn't yet support virtualizing SGX, i.e. it's impossible to
enter an enclave in a KVM guest (L1 or L2).

Fixes: 644d711aa0e1 ("KVM: nVMX: Deciding if L0 or L1 should handle an L2 exit")
Cc: Jim Mattson <jmattson@google.com>
Cc: Xiaoyao Li <xiaoyao.li@intel.com>
Cc: stable@vger.kernel.org
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Reviewed-by: Oliver Upton <oupton@google.com>
Reviewed-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 arch/x86/kvm/vmx/nested.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] KVM: s390: introduce module parameter kvm.use_gisa
##### From: Michael Mueller <mimu@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Michael Mueller <mimu@linux.ibm.com>
X-Patchwork-Id: 11408157
Return-Path: <SRS0=27T9=4P=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 55C2392A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 27 Feb 2020 09:10:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 3EB8F2467F
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 27 Feb 2020 09:10:44 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728621AbgB0JKn (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 27 Feb 2020 04:10:43 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:22082 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728624AbgB0JKn (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 27 Feb 2020 04:10:43 -0500
Received: from pps.filterd (m0098393.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 01R9597I084018
        for <kvm@vger.kernel.org>; Thu, 27 Feb 2020 04:10:42 -0500
Received: from e06smtp07.uk.ibm.com (e06smtp07.uk.ibm.com [195.75.94.103])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2ydxenx2gc-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Thu, 27 Feb 2020 04:10:41 -0500
Received: from localhost
        by e06smtp07.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <mimu@linux.ibm.com>;
        Thu, 27 Feb 2020 09:10:39 -0000
Received: from b06avi18626390.portsmouth.uk.ibm.com (9.149.26.192)
        by e06smtp07.uk.ibm.com (192.168.101.137) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Thu, 27 Feb 2020 09:10:37 -0000
Received: from d06av23.portsmouth.uk.ibm.com (d06av23.portsmouth.uk.ibm.com
 [9.149.105.59])
        by b06avi18626390.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 01R99dVM50921732
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 27 Feb 2020 09:09:39 GMT
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 5E813A4040;
        Thu, 27 Feb 2020 09:10:36 +0000 (GMT)
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 1BB1CA4051;
        Thu, 27 Feb 2020 09:10:36 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av23.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Thu, 27 Feb 2020 09:10:36 +0000 (GMT)
From: Michael Mueller <mimu@linux.ibm.com>
To: borntraeger@de.ibm.com, frankja@linux.vnet.ibm.com,
        mimu@linux.ibm.com
Cc: kvm@vger.kernel.org, cohuck@redhat.com, david@redhat.com,
        thuth@redhat.com, linux-s390@vger.kernel.org
Subject: [PATCH] KVM: s390: introduce module parameter kvm.use_gisa
Date: Thu, 27 Feb 2020 10:10:31 +0100
X-Mailer: git-send-email 2.17.1
X-TM-AS-GCONF: 00
x-cbid: 20022709-0028-0000-0000-000003DE6E4F
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 20022709-0029-0000-0000-000024A38CE3
Message-Id: <20200227091031.102993-1-mimu@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-02-27_02:2020-02-26,2020-02-27 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 bulkscore=0
 lowpriorityscore=0 priorityscore=1501 spamscore=0 suspectscore=0
 impostorscore=0 malwarescore=0 phishscore=0 mlxlogscore=999 mlxscore=0
 clxscore=1015 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2001150001 definitions=main-2002270074
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The boolean module parameter "kvm.use_gisa" controls if newly
created guests will use the GISA facility if provided by the
host system. The default is yes.

  # cat /sys/module/kvm/parameters/use_gisa
  Y

The parameter can be changed on the fly.

  # echo N > /sys/module/kvm/parameters/use_gisa

Already running guests are not affected by this change.

The kvm s390 debug feature shows if a guest is running with GISA.

  # grep gisa /sys/kernel/debug/s390dbf/kvm-$pid/sprintf
  00 01582725059:843303 3 - 08 00000000e119bc01  gisa 0x00000000c9ac2642 initialized
  00 01582725059:903840 3 - 11 000000004391ee22  00[0000000000000000-0000000000000000]: AIV gisa format-1 enabled for cpu 000
  ...
  00 01582725059:916847 3 - 08 0000000094fff572  gisa 0x00000000c9ac2642 cleared

In general, that value should not be changed as the GISA facility
enhances interruption delivery performance.

A reason to switch the GISA facility off might be a performance
comparison run or debugging.

Signed-off-by: Michael Mueller <mimu@linux.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---
 arch/s390/kvm/kvm-s390.c | 8 +++++++-
 1 file changed, 7 insertions(+), 1 deletion(-)

```
#### [PATCH 1/5] KVM: x86: Add function to inject guest page fault with reserved bits set
##### From: Mohammed Gamal <mgamal@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Mohammed Gamal <mgamal@redhat.com>
X-Patchwork-Id: 11409041
Return-Path: <SRS0=27T9=4P=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4258E92A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 27 Feb 2020 17:23:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 21739246A3
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 27 Feb 2020 17:23:42 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="AItJTnih"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730128AbgB0RXj (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 27 Feb 2020 12:23:39 -0500
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:51109 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1729863AbgB0RXi (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 27 Feb 2020 12:23:38 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1582824217;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=MHtHSwWIA/g7mfRIh25WqYXlQpnkyDs1uqDNi5kqsKE=;
        b=AItJTnih9pXuWGjHsGyTv7xfEOpAwEZIOZ6KnNQoZcucGcn3UK7AsTR6sygavyG6Pe/1lK
        fbiUL2z5lSH8JKNxELAZ88ztCIQMJ4m8f8KlJNl7ceyrM8hhY85TM+TmgBGMOP3fRfyodC
        P3zmSgC24JLU3AwCKO31jNVDO+1wHfI=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-436-Uu0QOX68O_eAddw1YEHCeQ-1; Thu, 27 Feb 2020 12:23:36 -0500
X-MC-Unique: Uu0QOX68O_eAddw1YEHCeQ-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id D221A13E5;
        Thu, 27 Feb 2020 17:23:33 +0000 (UTC)
Received: from millenium-falcon.redhat.com (unknown [10.36.118.42])
        by smtp.corp.redhat.com (Postfix) with ESMTP id ECCB11001B2C;
        Thu, 27 Feb 2020 17:23:30 +0000 (UTC)
From: Mohammed Gamal <mgamal@redhat.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com
Cc: sean.j.christopherson@intel.com, vkuznets@redhat.com,
        wanpengli@tencent.com, jmattson@google.com, joro@8bytes.org,
        linux-kernel@vger.kernel.org, Mohammed Gamal <mgamal@redhat.com>
Subject: [PATCH 1/5] KVM: x86: Add function to inject guest page fault with
 reserved bits set
Date: Thu, 27 Feb 2020 19:23:02 +0200
Message-Id: <20200227172306.21426-2-mgamal@redhat.com>
In-Reply-To: <20200227172306.21426-1-mgamal@redhat.com>
References: <20200227172306.21426-1-mgamal@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Signed-off-by: Mohammed Gamal <mgamal@redhat.com>
---
 arch/x86/kvm/x86.c | 14 ++++++++++++++
 arch/x86/kvm/x86.h |  1 +
 2 files changed, 15 insertions(+)

```
#### [kvm-unit-tests PATCH] x86: access: Add tests for reserved bits of guest physical address
##### From: Mohammed Gamal <mgamal@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Mohammed Gamal <mgamal@redhat.com>
X-Patchwork-Id: 11409055
Return-Path: <SRS0=27T9=4P=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 12926924
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 27 Feb 2020 17:28:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id DC755246A2
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 27 Feb 2020 17:28:52 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Rbstrgl+"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729832AbgB0R2u (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 27 Feb 2020 12:28:50 -0500
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:59772 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729382AbgB0R2u (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 27 Feb 2020 12:28:50 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1582824528;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=tgd24Z9DDO1trU7ZuAwbZRL98cQ9zB6qUkqBp/ykZi0=;
        b=Rbstrgl+0VsO9eHFawKOuSaOVoHe4hNnlIIvE48AXfNLpWOQaSxSx7s2t3GGqivy+34c/v
        rFZzedD+iaVUNazWYVx5714SPP4be2rA0Z1H2KjF6Oab5rblmSZaPYL/AmtQr4iq3sep/D
        GDGPux1cTYQX8LC+aYSJy8I8XK/+Xxo=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-7-n7XzXH7EPV6orn2Dq9Tjxg-1; Thu, 27 Feb 2020 12:28:43 -0500
X-MC-Unique: n7XzXH7EPV6orn2Dq9Tjxg-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 2FDA91005514;
        Thu, 27 Feb 2020 17:28:42 +0000 (UTC)
Received: from millenium-falcon.redhat.com (unknown [10.36.118.42])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 938956E3EE;
        Thu, 27 Feb 2020 17:28:36 +0000 (UTC)
From: Mohammed Gamal <mgamal@redhat.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com
Cc: sean.j.christopherson@intel.com, vkuznets@redhat.com,
        wanpengli@tencent.com, jmattson@google.com, joro@8bytes.org,
        linux-kernel@vger.kernel.org, Mohammed Gamal <mgamal@redhat.com>
Subject: [kvm-unit-tests PATCH] x86: access: Add tests for reserved bits of
 guest physical address
Date: Thu, 27 Feb 2020 19:28:26 +0200
Message-Id: <20200227172826.22004-1-mgamal@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This extends the access tests to also test for reserved bits
in guest physical addresses.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Mohammed Gamal <mgamal@redhat.com>
---
 x86/access.c | 31 +++++++++++++++++++++++++++++--
 1 file changed, 29 insertions(+), 2 deletions(-)

```
#### [kvm-unit-tests PATCH] x86: Add tests for user-mode CET
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Weijiang <weijiang.yang@intel.com>
X-Patchwork-Id: 11407735
Return-Path: <SRS0=27T9=4P=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id ABF8714B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 27 Feb 2020 04:40:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 81D5024670
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 27 Feb 2020 04:40:41 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728444AbgB0Ekk (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 26 Feb 2020 23:40:40 -0500
Received: from mga12.intel.com ([192.55.52.136]:12297 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728407AbgB0Ekk (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 26 Feb 2020 23:40:40 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by fmsmga106.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 26 Feb 2020 20:40:39 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,490,1574150400";
   d="scan'208";a="232044114"
Received: from local-michael-cet-test.sh.intel.com ([10.239.159.128])
  by fmsmga008.fm.intel.com with ESMTP; 26 Feb 2020 20:40:37 -0800
From: Yang Weijiang <weijiang.yang@intel.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com,
        sean.j.christopherson@intel.com, jmattson@google.com
Cc: Yang Weijiang <weijiang.yang@intel.com>
Subject: [kvm-unit-tests PATCH] x86: Add tests for user-mode CET
Date: Thu, 27 Feb 2020 12:43:57 +0800
Message-Id: <20200227044357.21646-1-weijiang.yang@intel.com>
X-Mailer: git-send-email 2.17.2
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This unit-test is intended to test user-mode CET support of KVM,
it's tested on Intel new platform. Two CET features: Shadow Stack
Protection(SHSTK) and Indirect-Branch Tracking(IBT) are enclosed.

In SHSTK test, if the function return-address in normal stack is
tampered with a value not equal to the one on shadow-stack, #CP
(Control Protection Exception)will generated on function returning.
This feature is supported by processor itself, no compiler/link
option is required.

However, to enabled IBT, we need to add -fcf-protection=full in
compiler options, this makes the compiler insert endbr64 at the
very beginning of each jmp/call target given the binary is for
x86_64.

To get PASS results, the following conditions must be met:
1) The processor is powered with CET feature.
2) The kernel is patched with the latest CET kernel patches.
3) The KVM and QEMU are patched with the latest CET patches.
4) Use CET-enabled gcc to compile the test app.

Signed-off-by: Yang Weijiang <weijiang.yang@intel.com>
---
 lib/x86/desc.c      |   2 +
 lib/x86/msr.h       |   2 +
 lib/x86/processor.h |   3 +
 x86/Makefile.common |   3 +-
 x86/Makefile.x86_64 |   3 +-
 x86/cet.c           | 212 ++++++++++++++++++++++++++++++++++++++++++++
 x86/unittests.cfg   |   6 ++
 7 files changed, 229 insertions(+), 2 deletions(-)
 create mode 100644 x86/cet.c

```
#### [PATCH 1/3] KVM: VMX: Always VMCLEAR in-use VMCSes during crash with kexec support
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11411037
Return-Path: <SRS0=27T9=4P=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1EABF138D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 27 Feb 2020 22:31:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id F3215246A6
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 27 Feb 2020 22:31:01 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730264AbgB0Wav (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 27 Feb 2020 17:30:51 -0500
Received: from mga04.intel.com ([192.55.52.120]:35152 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729850AbgB0Wav (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 27 Feb 2020 17:30:51 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga004.jf.intel.com ([10.7.209.38])
  by fmsmga104.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 27 Feb 2020 14:30:51 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,493,1574150400";
   d="scan'208";a="385312250"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by orsmga004.jf.intel.com with ESMTP; 27 Feb 2020 14:30:49 -0800
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH 1/3] KVM: VMX: Always VMCLEAR in-use VMCSes during crash with
 kexec support
Date: Thu, 27 Feb 2020 14:30:45 -0800
Message-Id: <20200227223047.13125-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20200227223047.13125-1-sean.j.christopherson@intel.com>
References: <20200227223047.13125-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

VMCLEAR all in-use VMCSes during a crash, even if kdump's NMI shootdown
interrupted a KVM update of the percpu in-use VMCS list.

Because NMIs are not blocked by disabling IRQs, it's possible that
crash_vmclear_local_loaded_vmcss() could be called while the percpu list
of VMCSes is being modified, e.g. in the middle of list_add() in
vmx_vcpu_load_vmcs().  This potential corner case was called out in the
original commit[*], but the analysis of its impact was wrong.

Skipping the VMCLEARs is wrong because it all but guarantees that a
loaded, and therefore cached, VMCS will live across kexec and corrupt
memory in the new kernel.  Corruption will occur because the CPU's VMCS
cache is non-coherent, i.e. not snooped, and so the writeback of VMCS
memory on its eviction will overwrite random memory in the new kernel.
The VMCS will live because the NMI shootdown also disables VMX, i.e. the
in-progress VMCLEAR will #UD, and existing Intel CPUs do not flush the
VMCS cache on VMXOFF.

Furthermore, interrupting list_add() and list_del() is safe due to
crash_vmclear_local_loaded_vmcss() using forward iteration.  list_add()
ensures the new entry is not visible to forward iteration unless the
entire add completes, via WRITE_ONCE(prev->next, new).  A bad "prev"
pointer could be observed if the NMI shootdown interrupted list_del() or
list_add(), but list_for_each_entry() does not consume ->prev.

In addition to removing the temporary disabling of VMCLEAR, move the
list_del() from __loaded_vmcs_clear() to loaded_vmcs_init() so that the
VMCS is deleted from the list only after it's been VMCLEAR'd.  Deleting
the VMCS before VMCLEAR would allow a race where the NMI shootdown could
arrive between list_del() and vmcs_clear() and thus neither flow would
execute a successful VMCLEAR.

Update the smp_*() comments related to the list manipulation, and
opportunistically reword them to improve clarity.

[*] https://patchwork.kernel.org/patch/1675731/#3720461

Fixes: 8f536b7697a0 ("KVM: VMX: provide the vmclear function and a bitmap to support VMCLEAR in kdump")
Cc: stable@vger.kernel.org
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/vmx/vmx.c | 79 +++++++++++-------------------------------
 arch/x86/kvm/vmx/vmx.h |  2 +-
 2 files changed, 22 insertions(+), 59 deletions(-)

```
#### [PATCH v2] KVM: Fix some obsolete comments
##### From: linmiaohe <linmiaohe@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: linmiaohe <linmiaohe@huawei.com>
X-Patchwork-Id: 11407689
Return-Path: <SRS0=27T9=4P=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BE196138D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 27 Feb 2020 03:19:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A73F82467B
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 27 Feb 2020 03:19:41 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728253AbgB0DTj (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 26 Feb 2020 22:19:39 -0500
Received: from szxga06-in.huawei.com ([45.249.212.32]:40744 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1728220AbgB0DTi (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 26 Feb 2020 22:19:38 -0500
Received: from DGGEMS408-HUB.china.huawei.com (unknown [172.30.72.59])
        by Forcepoint Email with ESMTP id 66B70344DEC26ED07C0F;
        Thu, 27 Feb 2020 11:19:35 +0800 (CST)
Received: from huawei.com (10.175.105.18) by DGGEMS408-HUB.china.huawei.com
 (10.3.19.208) with Microsoft SMTP Server id 14.3.439.0; Thu, 27 Feb 2020
 11:19:25 +0800
From: linmiaohe <linmiaohe@huawei.com>
To: <pbonzini@redhat.com>, <rkrcmar@redhat.com>,
        <sean.j.christopherson@intel.com>, <vkuznets@redhat.com>,
        <wanpengli@tencent.com>, <jmattson@google.com>, <joro@8bytes.org>,
        <tglx@linutronix.de>, <mingo@redhat.com>, <bp@alien8.de>,
        <hpa@zytor.com>
CC: <linmiaohe@huawei.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <x86@kernel.org>
Subject: [PATCH v2] KVM: Fix some obsolete comments
Date: Thu, 27 Feb 2020 11:20:54 +0800
Message-ID: <1582773654-4911-1-git-send-email-linmiaohe@huawei.com>
X-Mailer: git-send-email 1.8.3.1
MIME-Version: 1.0
X-Originating-IP: [10.175.105.18]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Miaohe Lin <linmiaohe@huawei.com>

Remove some obsolete comments, fix wrong function name and description.

Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Signed-off-by: Miaohe Lin <linmiaohe@huawei.com>
---
v1->v2:
Use Oxford comma
Collect Vitaly's R-b
---
 arch/x86/kvm/vmx/nested.c | 4 ++--
 arch/x86/kvm/vmx/vmx.c    | 2 +-
 2 files changed, 3 insertions(+), 3 deletions(-)

```
#### [PATCH v2] KVM: X86: deprecate obsolete KVM_GET_CPUID2 ioctl
##### From: linmiaohe <linmiaohe@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: linmiaohe <linmiaohe@huawei.com>
X-Patchwork-Id: 11407691
Return-Path: <SRS0=27T9=4P=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D6799138D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 27 Feb 2020 03:20:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id BF62B2467A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 27 Feb 2020 03:20:15 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728303AbgB0DUN (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 26 Feb 2020 22:20:13 -0500
Received: from szxga05-in.huawei.com ([45.249.212.191]:10701 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1728220AbgB0DUN (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 26 Feb 2020 22:20:13 -0500
Received: from DGGEMS406-HUB.china.huawei.com (unknown [172.30.72.58])
        by Forcepoint Email with ESMTP id 90D6C3EA773AAD8D60D2;
        Thu, 27 Feb 2020 11:20:08 +0800 (CST)
Received: from huawei.com (10.175.105.18) by DGGEMS406-HUB.china.huawei.com
 (10.3.19.206) with Microsoft SMTP Server id 14.3.439.0; Thu, 27 Feb 2020
 11:19:59 +0800
From: linmiaohe <linmiaohe@huawei.com>
To: <pbonzini@redhat.com>, <rkrcmar@redhat.com>,
        <sean.j.christopherson@intel.com>, <vkuznets@redhat.com>,
        <wanpengli@tencent.com>, <jmattson@google.com>, <joro@8bytes.org>,
        <tglx@linutronix.de>, <mingo@redhat.com>, <bp@alien8.de>,
        <hpa@zytor.com>
CC: <linmiaohe@huawei.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <x86@kernel.org>
Subject: [PATCH v2] KVM: X86: deprecate obsolete KVM_GET_CPUID2 ioctl
Date: Thu, 27 Feb 2020 11:21:28 +0800
Message-ID: <1582773688-4956-1-git-send-email-linmiaohe@huawei.com>
X-Mailer: git-send-email 1.8.3.1
MIME-Version: 1.0
X-Originating-IP: [10.175.105.18]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Miaohe Lin <linmiaohe@huawei.com>

When kvm_vcpu_ioctl_get_cpuid2() fails, we set cpuid->nent to the value of
vcpu->arch.cpuid_nent. But this is in vain as cpuid->nent is not copied to
userspace by copy_to_user() from call site. Also cpuid->nent is not updated
to indicate how many entries were retrieved on success case. So this ioctl
is straight up broken. And in fact, it's not used anywhere. So it should be
deprecated.

Suggested-by: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Miaohe Lin <linmiaohe@huawei.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/cpuid.c           | 20 --------------------
 arch/x86/kvm/cpuid.h           |  3 ---
 arch/x86/kvm/x86.c             | 16 ++--------------
 include/uapi/linux/kvm.h       |  1 +
 tools/include/uapi/linux/kvm.h |  1 +
 5 files changed, 4 insertions(+), 37 deletions(-)

```
#### [PATCH v2] kvm: x86: Limit the number of "kvm: disabled by bios" messages
##### From: Erwan Velu <erwanaliasr1@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Erwan Velu <erwanaliasr1@gmail.com>
X-Patchwork-Id: 11409109
Return-Path: <SRS0=27T9=4P=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2E8E9924
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 27 Feb 2020 18:01:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 0DA63246AC
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 27 Feb 2020 18:01:27 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="CacxHc1s"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730263AbgB0SBY (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 27 Feb 2020 13:01:24 -0500
Received: from mail-wr1-f65.google.com ([209.85.221.65]:36505 "EHLO
        mail-wr1-f65.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729162AbgB0SBX (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 27 Feb 2020 13:01:23 -0500
Received: by mail-wr1-f65.google.com with SMTP id j16so3028709wrt.3;
        Thu, 27 Feb 2020 10:01:21 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=E8ZWbS7tq2JVdfpTRDo8i0zrwTusfBz0dP/4sGTaYhE=;
        b=CacxHc1sX0lFECQt6xnPa7ab2DoBIXez7pUXgytY0T13W9k/YHrXteFuXYxvWcEtUL
         baWCq6Qjq1ofXIkAixN4zKjzxO6kA2z+bqxFXH8Qw+yoLwofFIeaEp+/Jhj0lWX//7nP
         sh8h/bX6nea9yMt/EZENdgjMMRbGV5qEuFHjj+kvap62I/5xBlT6LYb1aTH80jUYy1HR
         VDdb5vmtm8ksc5UEndBJRQAMSg24SVWx7f/g8HHE8is4YiwD/z7UU0sR1DXLe+pYvVqt
         Mvzcodidc1E5Fy+gWW11vodldtQoIjasP1oQkbE5JcCrt6u5hH+rlyviWCD2rJ0XH7tQ
         BzFA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=E8ZWbS7tq2JVdfpTRDo8i0zrwTusfBz0dP/4sGTaYhE=;
        b=WheFHmimv/nuAhsWh7A2xLg4Lm8U/Nwwj1CoHiR2v1oUXJlaT+eH50OstMp1jtx82D
         XCzI2+IUkerkqYYl6/IAVLLIRZIQNZC+Pf6P0+8NXnyX6UZgL0TO+ZrYJyakKld9x1y7
         +br0PT+vWEaLTmbhSdRy8jq2OuJKe2/qPOH2/RfedOCOjAvbNkAmvsfjVKQs0v9Q6zL/
         ResmSbEdjYhWZpPw5iVMFGlRI/LdcCy2bikjfeS88REyUKvjbxx9eNgGwB3XUABU64uY
         rgzaAVn39D4zsQPlgL5ZGJ4nW4KgvY6LMvlG+Bn8S36mQSHDjHz7bL3PVWbUSZ+2dvGV
         OzLQ==
X-Gm-Message-State: APjAAAXpCmbvqok6pnV6T3UjzIelgMsxf9uAX1zdr/z6/Ihpz9LBDuAf
        qm76eupUyhXxVK8BvgjRdss=
X-Google-Smtp-Source: 
 APXvYqzd3Adej9lxNHdKHQ4vxXxVbjCB5TS6CY9IBBvPvHdwJ/a5fmSIuHpqkTy37ODZrIE+SJGI8g==
X-Received: by 2002:adf:ef4e:: with SMTP id c14mr35395wrp.335.1582826480343;
        Thu, 27 Feb 2020 10:01:20 -0800 (PST)
Received: from laptop.criteo.prod ([2a01:e34:eecb:7400:6cb4:8756:33ca:8626])
        by smtp.gmail.com with ESMTPSA id
 b186sm8582287wmb.40.2020.02.27.10.01.18
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 27 Feb 2020 10:01:19 -0800 (PST)
From: Erwan Velu <erwanaliasr1@gmail.com>
X-Google-Original-From: Erwan Velu <e.velu@criteo.com>
Cc: Erwan Velu <e.velu@criteo.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        "H. Peter Anvin" <hpa@zytor.com>,
        x86@kernel.org (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT)),
        kvm@vger.kernel.org (open list:KERNEL VIRTUAL MACHINE FOR X86
 (KVM/x86)),
        linux-kernel@vger.kernel.org (open list:X86 ARCHITECTURE (32-BIT AND
        64-BIT))
Subject: [PATCH v2] kvm: x86: Limit the number of "kvm: disabled by bios"
 messages
Date: Thu, 27 Feb 2020 19:00:46 +0100
Message-Id: <20200227180047.53888-1-e.velu@criteo.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20200214143035.607115-1-e.velu@criteo.com>
References: <20200214143035.607115-1-e.velu@criteo.com>
MIME-Version: 1.0
To: unlisted-recipients:; (no To-header on input)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In older version of systemd(219), at boot time, udevadm is called with :
	/usr/bin/udevadm trigger --type=devices --action=add"

This program generates an echo "add" in /sys/devices/system/cpu/cpu<x>/uevent,
leading to the "kvm: disabled by bios" message in case of your Bios disabled
the virtualization extensions.

On a modern system running up to 256 CPU threads, this pollutes the Kernel logs.

This patch offers to ratelimit this message to avoid any userspace program triggering
this uevent printing this message too often.

This patch is only a workaround but greatly reduce the pollution without
breaking the current behavior of printing a message if some try to instantiate
KVM on a system that doesn't support it.

Note that recent versions of systemd (>239) do not have trigger this behavior.

This patch will be useful at least for some using older systemd with recent Kernels.

Signed-off-by: Erwan Velu <e.velu@criteo.com>
---
 arch/x86/kvm/x86.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH v4] KVM: x86: enable dirty log gradually in small chunks
##### From: Jay Zhou <jianjay.zhou@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jay Zhou <jianjay.zhou@huawei.com>
X-Patchwork-Id: 11407577
Return-Path: <SRS0=27T9=4P=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6B4FA14D5
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 27 Feb 2020 01:32:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 3A4B324670
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 27 Feb 2020 01:32:41 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728143AbgB0Bck (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 26 Feb 2020 20:32:40 -0500
Received: from szxga06-in.huawei.com ([45.249.212.32]:45766 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1728091AbgB0Bck (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 26 Feb 2020 20:32:40 -0500
Received: from DGGEMS404-HUB.china.huawei.com (unknown [172.30.72.58])
        by Forcepoint Email with ESMTP id 9E4164813647382ACC57;
        Thu, 27 Feb 2020 09:32:37 +0800 (CST)
Received: from localhost (10.173.228.206) by DGGEMS404-HUB.china.huawei.com
 (10.3.19.204) with Microsoft SMTP Server id 14.3.439.0; Thu, 27 Feb 2020
 09:32:30 +0800
From: Jay Zhou <jianjay.zhou@huawei.com>
To: <kvm@vger.kernel.org>
CC: <pbonzini@redhat.com>, <peterx@redhat.com>,
        <sean.j.christopherson@intel.com>, <wangxinxin.wang@huawei.com>,
        <weidong.huang@huawei.com>, <jianjay.zhou@huawei.com>,
        <liu.jinsong@huawei.com>
Subject: [PATCH v4] KVM: x86: enable dirty log gradually in small chunks
Date: Thu, 27 Feb 2020 09:32:27 +0800
Message-ID: <20200227013227.1401-1-jianjay.zhou@huawei.com>
X-Mailer: git-send-email 2.14.1.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.173.228.206]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

It could take kvm->mmu_lock for an extended period of time when
enabling dirty log for the first time. The main cost is to clear
all the D-bits of last level SPTEs. This situation can benefit from
manual dirty log protect as well, which can reduce the mmu_lock
time taken. The sequence is like this:

1. Initialize all the bits of the dirty bitmap to 1 when enabling
   dirty log for the first time
2. Only write protect the huge pages
3. KVM_GET_DIRTY_LOG returns the dirty bitmap info
4. KVM_CLEAR_DIRTY_LOG will clear D-bit for each of the leaf level
   SPTEs gradually in small chunks

Under the Intel(R) Xeon(R) Gold 6152 CPU @ 2.10GHz environment,
I did some tests with a 128G windows VM and counted the time taken
of memory_global_dirty_log_start, here is the numbers:

VM Size        Before    After optimization
128G           460ms     10ms

Signed-off-by: Jay Zhou <jianjay.zhou@huawei.com>
Reviewed-by: Peter Xu <peterx@redhat.com>
---
v4:
  * tweak the names, put the sub-cap definition into uapi and check
    against x86 [Peter]

v3:
  * add kvm_manual_dirty_log_init_set helper, add testcase on top and
    keep old behavior for KVM_MEM_READONLY [Peter]
  * tweak logic at enabling KVM_CAP_MANUAL_DIRTY_LOG_PROTECT2 [Sean, Peter]

v2:
  * add new bit to KVM_ENABLE_CAP for KVM_CAP_MANUAL_DIRTY_LOG_PROTECT2 [Paolo]
  * support non-PML path [Peter]
  * delete the unnecessary ifdef and make the initialization of bitmap
    more clear [Sean]
  * document the new bits and tweak the testcase

 Documentation/virt/kvm/api.rst  | 16 +++++++++++++---
 arch/x86/include/asm/kvm_host.h |  6 +++++-
 arch/x86/kvm/mmu/mmu.c          |  7 ++++---
 arch/x86/kvm/vmx/vmx.c          |  3 ++-
 arch/x86/kvm/x86.c              | 21 +++++++++++++++++----
 include/linux/kvm_host.h        | 11 ++++++++++-
 include/uapi/linux/kvm.h        |  3 +++
 virt/kvm/kvm_main.c             | 24 +++++++++++++++++-------
 8 files changed, 71 insertions(+), 20 deletions(-)

```
