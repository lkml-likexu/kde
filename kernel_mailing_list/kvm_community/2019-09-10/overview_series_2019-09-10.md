#### [PATCH 1/2] KVM: PPC: Book3S HV: XIVE: initialize private pointer when VPs are allocated
##### From: Greg Kurz <groug@kaod.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Greg Kurz <groug@kaod.org>
X-Patchwork-Id: 11139539
Return-Path: <SRS0=WlTH=XF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A81F1112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Sep 2019 13:44:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 8E72F208E4
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Sep 2019 13:44:08 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732952AbfIJNoH (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 10 Sep 2019 09:44:07 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:60794 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1729662AbfIJNoH (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 10 Sep 2019 09:44:07 -0400
Received: from pps.filterd (m0098399.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 x8ADgRDQ125390
        for <kvm@vger.kernel.org>; Tue, 10 Sep 2019 09:44:06 -0400
Received: from e06smtp05.uk.ibm.com (e06smtp05.uk.ibm.com [195.75.94.101])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2uxaafpjr4-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Tue, 10 Sep 2019 09:44:06 -0400
Received: from localhost
        by e06smtp05.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <groug@kaod.org>;
        Tue, 10 Sep 2019 14:44:02 +0100
Received: from b06cxnps3075.portsmouth.uk.ibm.com (9.149.109.195)
        by e06smtp05.uk.ibm.com (192.168.101.135) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Tue, 10 Sep 2019 14:43:59 +0100
Received: from d06av24.portsmouth.uk.ibm.com (mk.ibm.com [9.149.105.60])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id x8ADhxw135651692
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 10 Sep 2019 13:43:59 GMT
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id E7EC442049;
        Tue, 10 Sep 2019 13:43:58 +0000 (GMT)
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id AE6624203F;
        Tue, 10 Sep 2019 13:43:58 +0000 (GMT)
Received: from bahia.tls.ibm.com (unknown [9.101.4.41])
        by d06av24.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue, 10 Sep 2019 13:43:58 +0000 (GMT)
Subject: [PATCH 1/2] KVM: PPC: Book3S HV: XIVE: initialize private pointer
 when VPs are allocated
From: Greg Kurz <groug@kaod.org>
To: Paul Mackerras <paulus@ozlabs.org>
Cc: David Gibson <david@gibson.dropbear.id.au>,
 =?utf-8?q?C=C3=A9dric?= Le Goater <clg@kaod.org>, kvm-ppc@vger.kernel.org,
 kvm@vger.kernel.org
Date: Tue, 10 Sep 2019 15:43:58 +0200
User-Agent: StGit/unknown-version
MIME-Version: 1.0
Content-Type: text/plain; charset="utf-8"
X-TM-AS-GCONF: 00
x-cbid: 19091013-0020-0000-0000-0000036A843A
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19091013-0021-0000-0000-000021C00BA0
Message-Id: <156812303847.1865227.3495698285729698782.stgit@bahia.tls.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-09-10_09:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=2 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1034 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=999 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1906280000 definitions=main-1909100135
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Cédric Le Goater <clg@kaod.org>

Do not assign the device private pointer before making sure the XIVE
VPs are allocated in OPAL and test pointer validity when releasing
the device.

Fixes: 5422e95103cf ("KVM: PPC: Book3S HV: XIVE: Replace the 'destroy' method by a 'release' method")
Signed-off-by: Cédric Le Goater <clg@kaod.org>
Signed-off-by: Greg Kurz <groug@kaod.org>
---
 arch/powerpc/kvm/book3s_xive.c        |   13 +++++++++++--
 arch/powerpc/kvm/book3s_xive_native.c |   13 +++++++++++--
 2 files changed, 22 insertions(+), 4 deletions(-)

```
#### [PATCH 1/2] KVM: CPUID: Check limit first when emulating CPUID instruction
##### From: Xiaoyao Li <xiaoyao.li@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xiaoyao Li <xiaoyao.li@intel.com>
X-Patchwork-Id: 11138939
Return-Path: <SRS0=WlTH=XF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C82DB76
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Sep 2019 08:39:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B0ACA21019
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Sep 2019 08:39:27 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728027AbfIJIj1 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 10 Sep 2019 04:39:27 -0400
Received: from mga04.intel.com ([192.55.52.120]:55164 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726099AbfIJIj0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 10 Sep 2019 04:39:26 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga002.jf.intel.com ([10.7.209.21])
  by fmsmga104.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 10 Sep 2019 01:39:26 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.64,489,1559545200";
   d="scan'208";a="196468187"
Received: from lxy-clx-4s.sh.intel.com ([10.239.43.44])
  by orsmga002.jf.intel.com with ESMTP; 10 Sep 2019 01:39:24 -0700
From: Xiaoyao Li <xiaoyao.li@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>
Cc: Xiaoyao Li <xiaoyao.li@intel.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org
Subject: [PATCH 1/2] KVM: CPUID: Check limit first when emulating CPUID
 instruction
Date: Tue, 10 Sep 2019 16:24:41 +0800
Message-Id: <20190910082442.142702-2-xiaoyao.li@intel.com>
X-Mailer: git-send-email 2.19.1
In-Reply-To: <20190910082442.142702-1-xiaoyao.li@intel.com>
References: <20190910082442.142702-1-xiaoyao.li@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When limit checking is required, it should be executed first, which is
consistent with the CPUID specification.

Signed-off-by: Xiaoyao Li <xiaoyao.li@intel.com>
---
 arch/x86/kvm/cpuid.c | 50 +++++++++++++++++++++++++-------------------
 1 file changed, 28 insertions(+), 22 deletions(-)

```
#### [PATCH v2 1/2] KVM: CPUID: Check limit first when emulating CPUID instruction
##### From: Xiaoyao Li <xiaoyao.li@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xiaoyao Li <xiaoyao.li@intel.com>
X-Patchwork-Id: 11139223
Return-Path: <SRS0=WlTH=XF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BB85C1395
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Sep 2019 10:42:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A2B1E208E4
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Sep 2019 10:42:25 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729049AbfIJKmY (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 10 Sep 2019 06:42:24 -0400
Received: from mga04.intel.com ([192.55.52.120]:64085 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725797AbfIJKmY (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 10 Sep 2019 06:42:24 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga002.jf.intel.com ([10.7.209.21])
  by fmsmga104.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 10 Sep 2019 03:42:24 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.64,489,1559545200";
   d="scan'208";a="196512145"
Received: from lxy-clx-4s.sh.intel.com ([10.239.43.44])
  by orsmga002.jf.intel.com with ESMTP; 10 Sep 2019 03:42:22 -0700
From: Xiaoyao Li <xiaoyao.li@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>
Cc: Xiaoyao Li <xiaoyao.li@intel.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org
Subject: [PATCH v2 1/2] KVM: CPUID: Check limit first when emulating CPUID
 instruction
Date: Tue, 10 Sep 2019 18:27:41 +0800
Message-Id: <20190910102742.47729-2-xiaoyao.li@intel.com>
X-Mailer: git-send-email 2.19.1
In-Reply-To: <20190910102742.47729-1-xiaoyao.li@intel.com>
References: <20190910102742.47729-1-xiaoyao.li@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When limit checking is required, it should be executed first, which is
consistent with the CPUID specification.

Signed-off-by: Xiaoyao Li <xiaoyao.li@intel.com>
---
v2:
  - correctly set entry_found in no limit checking case.

---
 arch/x86/kvm/cpuid.c | 51 ++++++++++++++++++++++++++------------------
 1 file changed, 30 insertions(+), 21 deletions(-)

```
#### [PATCH] KVM: PPC: Book3S HV: Tunable to configure maximum # of vCPUs per VM
##### From: Greg Kurz <groug@kaod.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Greg Kurz <groug@kaod.org>
X-Patchwork-Id: 11139907
Return-Path: <SRS0=WlTH=XF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4122514DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Sep 2019 16:49:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1DE5F2082C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Sep 2019 16:49:43 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2436815AbfIJQtm (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 10 Sep 2019 12:49:42 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:27230 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S2436760AbfIJQtm (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 10 Sep 2019 12:49:42 -0400
Received: from pps.filterd (m0098420.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 x8AGmswl125259
        for <kvm@vger.kernel.org>; Tue, 10 Sep 2019 12:49:40 -0400
Received: from e06smtp01.uk.ibm.com (e06smtp01.uk.ibm.com [195.75.94.97])
        by mx0b-001b2d01.pphosted.com with ESMTP id 2uxcj37qh3-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Tue, 10 Sep 2019 12:49:40 -0400
Received: from localhost
        by e06smtp01.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <groug@kaod.org>;
        Tue, 10 Sep 2019 17:49:38 +0100
Received: from b06avi18878370.portsmouth.uk.ibm.com (9.149.26.194)
        by e06smtp01.uk.ibm.com (192.168.101.131) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Tue, 10 Sep 2019 17:49:35 +0100
Received: from d06av24.portsmouth.uk.ibm.com (d06av24.portsmouth.uk.ibm.com
 [9.149.105.60])
        by b06avi18878370.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id x8AGnYPm31261136
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 10 Sep 2019 16:49:34 GMT
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 80C704203F;
        Tue, 10 Sep 2019 16:49:34 +0000 (GMT)
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 3565042049;
        Tue, 10 Sep 2019 16:49:34 +0000 (GMT)
Received: from bahia.tls.ibm.com (unknown [9.101.4.41])
        by d06av24.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue, 10 Sep 2019 16:49:34 +0000 (GMT)
Subject: [PATCH] KVM: PPC: Book3S HV: Tunable to configure maximum # of
 vCPUs per VM
From: Greg Kurz <groug@kaod.org>
To: Paul Mackerras <paulus@ozlabs.org>
Cc: Michael Ellerman <mpe@ellerman.id.au>,
 David Gibson <david@gibson.dropbear.id.au>,
 =?utf-8?q?C=C3=A9dric?= Le Goater <clg@kaod.org>, kvm-ppc@vger.kernel.org,
 kvm@vger.kernel.org, linuxppc-dev@lists.ozlabs.org
Date: Tue, 10 Sep 2019 18:49:34 +0200
User-Agent: StGit/unknown-version
MIME-Version: 1.0
Content-Type: text/plain; charset="utf-8"
X-TM-AS-GCONF: 00
x-cbid: 19091016-4275-0000-0000-000003640AE4
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19091016-4276-0000-0000-000038766001
Message-Id: <156813417397.1880979.6162333671088177553.stgit@bahia.tls.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-09-10_11:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=0 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1034 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=999 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1906280000 definitions=main-1909100161
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Each vCPU of a VM allocates a XIVE VP in OPAL which is associated with
8 event queue (EQ) descriptors, one for each priority. A POWER9 socket
can handle a maximum of 1M event queues.

The powernv platform allocates NR_CPUS (== 2048) VPs for the hypervisor,
and each XIVE KVM device allocates KVM_MAX_VCPUS (== 2048) VPs. This means
that on a bi-socket system, we can create at most:

(2 * 1M) / (8 * 2048) - 1 == 127 XIVE or XICS-on-XIVE KVM devices

ie, start at most 127 VMs benefiting from an in-kernel interrupt controller.
Subsequent VMs need to rely on much slower userspace emulated XIVE device in
QEMU.

This is problematic as one can legitimately expect to start the same
number of mono-CPU VMs as the number of HW threads available on the
system (eg, 144 on Witherspoon).

I'm not aware of any userspace supporting more that 1024 vCPUs. It thus
seem overkill to consume that many VPs per VM. Ideally we would even
want userspace to be able to tell KVM about the maximum number of vCPUs
when creating the VM.

For now, provide a module parameter to configure the maximum number of
vCPUs per VM. While here, reduce the default value to 1024 to match the
current limit in QEMU. This number is only used by the XIVE KVM devices,
but some more users of KVM_MAX_VCPUS could possibly be converted.

With this change, I could successfully run 230 mono-CPU VMs on a
Witherspoon system using the official skiboot-6.3.

I could even run more VMs by using upstream skiboot containing this
fix, that allows to better spread interrupts between sockets:

e97391ae2bb5 ("xive: fix return value of opal_xive_allocate_irq()")

MAX VPCUS | MAX VMS
----------+---------
     1024 |     255
      512 |     511
      256 |    1023 (*)

(*) the system was barely usable because of the extreme load and
    memory exhaustion but the VMs did start.

Signed-off-by: Greg Kurz <groug@kaod.org>
---
 arch/powerpc/include/asm/kvm_host.h   |    1 +
 arch/powerpc/kvm/book3s_hv.c          |   32 ++++++++++++++++++++++++++++++++
 arch/powerpc/kvm/book3s_xive.c        |    2 +-
 arch/powerpc/kvm/book3s_xive_native.c |    2 +-
 4 files changed, 35 insertions(+), 2 deletions(-)

```
#### [PATCH] KVM: s390: kvm_s390_vm_start_migration: check dirty_bitmap before using it as target for memset()
##### From: Igor Mammedov <imammedo@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Igor Mammedov <imammedo@redhat.com>
X-Patchwork-Id: 11139493
Return-Path: <SRS0=WlTH=XF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2A9D476
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Sep 2019 13:02:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1346021479
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Sep 2019 13:02:33 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2392914AbfIJNCa (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 10 Sep 2019 09:02:30 -0400
Received: from mx1.redhat.com ([209.132.183.28]:55264 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726192AbfIJNC3 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 10 Sep 2019 09:02:29 -0400
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 58E75309BF21;
        Tue, 10 Sep 2019 13:02:29 +0000 (UTC)
Received: from dell-r430-03.lab.eng.brq.redhat.com
 (dell-r430-03.lab.eng.brq.redhat.com [10.37.153.18])
        by smtp.corp.redhat.com (Postfix) with ESMTP id DF245196B2;
        Tue, 10 Sep 2019 13:02:18 +0000 (UTC)
From: Igor Mammedov <imammedo@redhat.com>
To: linux-kernel@vger.kernel.org
Cc: borntraeger@de.ibm.com, david@redhat.com, cohuck@redhat.com,
        frankja@linux.ibm.com, heiko.carstens@de.ibm.com,
        gor@linux.ibm.com, imbrenda@linux.ibm.com,
        linux-s390@vger.kernel.org, kvm@vger.kernel.org,
        stable@vger.kernel.org
Subject: [PATCH] KVM: s390: kvm_s390_vm_start_migration: check dirty_bitmap
 before using it as target for memset()
Date: Tue, 10 Sep 2019 09:02:15 -0400
Message-Id: <20190910130215.23647-1-imammedo@redhat.com>
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.5.16 (mx1.redhat.com [10.5.110.45]);
 Tue, 10 Sep 2019 13:02:29 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If userspace doesn't set KVM_MEM_LOG_DIRTY_PAGES on memslot before calling
kvm_s390_vm_start_migration(), kernel will oops with:

  Unable to handle kernel pointer dereference in virtual kernel address space
  Failing address: 0000000000000000 TEID: 0000000000000483
  Fault in home space mode while using kernel ASCE.
  AS:0000000002a2000b R2:00000001bff8c00b R3:00000001bff88007 S:00000001bff91000 P:000000000000003d
  Oops: 0004 ilc:2 [#1] SMP
  ...
  Call Trace:
  ([<001fffff804ec552>] kvm_s390_vm_set_attr+0x347a/0x3828 [kvm])
   [<001fffff804ecfc0>] kvm_arch_vm_ioctl+0x6c0/0x1998 [kvm]
   [<001fffff804b67e4>] kvm_vm_ioctl+0x51c/0x11a8 [kvm]
   [<00000000008ba572>] do_vfs_ioctl+0x1d2/0xe58
   [<00000000008bb284>] ksys_ioctl+0x8c/0xb8
   [<00000000008bb2e2>] sys_ioctl+0x32/0x40
   [<000000000175552c>] system_call+0x2b8/0x2d8
  INFO: lockdep is turned off.
  Last Breaking-Event-Address:
   [<0000000000dbaf60>] __memset+0xc/0xa0

due to ms->dirty_bitmap being NULL, which might crash the host.

Make sure that ms->dirty_bitmap is set before using it or
print a warning and return -ENIVAL otherwise.

Fixes: afdad61615cc ("KVM: s390: Fix storage attributes migration with memory slots")
Signed-off-by: Igor Mammedov <imammedo@redhat.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Christian Borntraeger <borntraeger@de.ibm.com>
Reviewed-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---
Cc: stable@vger.kernel.org # v4.19+

v2:
   - drop WARN()

 arch/s390/kvm/kvm-s390.c | 2 ++
 1 file changed, 2 insertions(+)

```
#### [kvm-unit-tests PATCH] x86: Skip APIC-access address tests beyond mapped RAM
##### From: Jim Mattson <jmattson@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jim Mattson <jmattson@google.com>
X-Patchwork-Id: 11139989
Return-Path: <SRS0=WlTH=XF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7A6591599
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Sep 2019 18:49:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 25F702171F
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Sep 2019 18:49:27 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="HLdv739i"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728609AbfIJSt0 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 10 Sep 2019 14:49:26 -0400
Received: from mail-pf1-f201.google.com ([209.85.210.201]:43711 "EHLO
        mail-pf1-f201.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725770AbfIJStZ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 10 Sep 2019 14:49:25 -0400
Received: by mail-pf1-f201.google.com with SMTP id i187so13740884pfc.10
        for <kvm@vger.kernel.org>; Tue, 10 Sep 2019 11:49:24 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=Dr8xkXNDT/zhoODue2+DxNalzbXghdJqV9hoE9dV0dQ=;
        b=HLdv739iJi72Bbw4VZjEbb6HN0lGBKBsYMHrm5uNyp92uGIxc+L4nA7WZDX9+A9GoA
         EwZJ/KdPxhh9GIVBAS/PEexxuJ0Td3BTGjrEbPhjzlPnB6SsWi0/3rqTtOcYxxYO7Wwj
         CPHJbHwTtgv9nY1kdEMs5hTBg5Am5BtJZciv535rJSUlMRnMvBvJa7vN4I8HhkoQQQla
         hTdvwf7ul0MfyE8Bv41Gj59ADN/JVq65lbQl05h2Fdc1Gg0A7zp/m0+pMYuHBUvQ5ns6
         RsJklb0NJz5uQ+LQLL4GRHLJwNt/MRmwMAZOFvtH/OvA0H+4EvBjOutkLqg84TZHX8LB
         GHRw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=Dr8xkXNDT/zhoODue2+DxNalzbXghdJqV9hoE9dV0dQ=;
        b=dmh3raXbElwgP0HrxIICAnCsJ5NVbAU551CMNPfGl39BpBTa92E5Wgdh5G6V7116q3
         mppKFG7WldEGSenY1g2fnsh4wMP39R2RjIYr1UV/uBDikuf3SlNPzMy2mS5C755IJvD1
         Y9jPKzbxlwLuiIzC2D04PMYqe9oD7DA74cDzEzeZhr4kY8J6TlBgEtvhiqd/vQBWC7Z2
         Fvjs3Vf1geX7TiG69QllNhw5dpnmoS1yo4l6OVK31VqL8rqANdo2/U0ZxcczTTrLbA2o
         UJL2Jc7PcmvBL7CqtZ5ZvOE/RLuiGH4fNUqgdID8lG9Q1oFQyHcgluFI/uW6DKMs7dPH
         dYrg==
X-Gm-Message-State: APjAAAVnNJFcf+T/vlECaaGqzDU0xNRraM5e3MlnTwAK13Sq7+WBSwoz
        5C5IXpgoZu4d07GxcNJa2/9ELay/Oii6stgs5gDJWo1xRZZ+Hyqp90ZIlpjBkLaDqW/2hqsqi8R
        xbyVnq7qnnuO20pQYKapq9sP+PkAnvhgabWteXcIPjz4zVX5nt4NKnqhIOapK2SU=
X-Google-Smtp-Source: 
 APXvYqzZy7aTHOKdremR4+DykF0jAQqVDQZKx7PZTLTXhw70bqJHzhk5ssMirNgG/cDsI+K7Neyr6BTaiG/yFQ==
X-Received: by 2002:a63:7b16:: with SMTP id w22mr2977941pgc.328.1568141363775;
 Tue, 10 Sep 2019 11:49:23 -0700 (PDT)
Date: Tue, 10 Sep 2019 11:49:16 -0700
Message-Id: <20190910184916.50282-1-jmattson@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.23.0.162.g0b9fbb3734-goog
Subject: [kvm-unit-tests PATCH] x86: Skip APIC-access address tests beyond
 mapped RAM
From: Jim Mattson <jmattson@google.com>
To: kvm@vger.kernel.org
Cc: Jim Mattson <jmattson@google.com>
Content-Type: text/plain; charset="UTF-8"
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We no longer have any tests in vmx_tests.c that use
xfail_beyond_mapped_ram. However, an upcoming change to kvm will exit
to userspace with a kvm internal error whenever launching a nested VM
with the vmcs12 APIC-access address set to a non-cacheable address in
L1. Reuse the xfail_beyond_mapped_ram plumbing to support
skip_beyond_mapped_ram, and skip any APIC-access address tests that
use addresses beyond mapped RAM, so that the test won't induce a kvm
internal error.

Signed-off-by: Jim Mattson <jmattson@google.com>
---
 x86/vmx_tests.c | 289 +++++++++++++++++++++++-------------------------
 1 file changed, 139 insertions(+), 150 deletions(-)

```
#### [RFC PATCH 1/4] vringh: fix copy direction of vringh_iov_push_kern()
##### From: Jason Wang <jasowang@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 11138909
Return-Path: <SRS0=WlTH=XF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 710911395
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Sep 2019 08:20:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 57CE321D6C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Sep 2019 08:20:23 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2406787AbfIJIUO (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 10 Sep 2019 04:20:14 -0400
Received: from mx1.redhat.com ([209.132.183.28]:33244 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2406759AbfIJIUL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 10 Sep 2019 04:20:11 -0400
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 5ED43800DEB;
        Tue, 10 Sep 2019 08:20:11 +0000 (UTC)
Received: from jason-ThinkPad-X1-Carbon-6th.redhat.com
 (ovpn-12-188.pek2.redhat.com [10.72.12.188])
        by smtp.corp.redhat.com (Postfix) with ESMTP id D0E7360623;
        Tue, 10 Sep 2019 08:20:03 +0000 (UTC)
From: Jason Wang <jasowang@redhat.com>
To: mst@redhat.com, jasowang@redhat.com, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, kwankhede@nvidia.com,
        alex.williamson@redhat.com, cohuck@redhat.com, tiwei.bie@intel.com,
        maxime.coquelin@redhat.com, cunming.liang@intel.com,
        zhihong.wang@intel.com, rob.miller@broadcom.com, idos@mellanox.com,
        xiao.w.wang@intel.com, haotian.wang@sifive.com
Subject: [RFC PATCH 1/4] vringh: fix copy direction of vringh_iov_push_kern()
Date: Tue, 10 Sep 2019 16:19:32 +0800
Message-Id: <20190910081935.30516-2-jasowang@redhat.com>
In-Reply-To: <20190910081935.30516-1-jasowang@redhat.com>
References: <20190910081935.30516-1-jasowang@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.6.2 (mx1.redhat.com [10.5.110.67]);
 Tue, 10 Sep 2019 08:20:11 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We want to copy from iov to buf, so the direction was wrong.

Signed-off-by: Jason Wang <jasowang@redhat.com>
---
 drivers/vhost/vringh.c | 8 +++++++-
 1 file changed, 7 insertions(+), 1 deletion(-)

```
