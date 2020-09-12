#### [PATCH] kvm/eventfd:do wildcard calculation before list_for_each_entry_safe
##### From: Yi Li <yili@winhong.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yi Li <yili@winhong.com>
X-Patchwork-Id: 11769833
Return-Path: <SRS0=Lkah=CU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D927D59D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 11 Sep 2020 06:04:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C6AAF221E5
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 11 Sep 2020 06:04:06 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725766AbgIKGEE (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 11 Sep 2020 02:04:04 -0400
Received: from regular1.263xmail.com ([211.150.70.206]:45482 "EHLO
        regular1.263xmail.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725497AbgIKGED (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 11 Sep 2020 02:04:03 -0400
X-Greylist: delayed 385 seconds by postgrey-1.27 at vger.kernel.org;
 Fri, 11 Sep 2020 02:04:02 EDT
Received: from localhost (unknown [192.168.167.69])
        by regular1.263xmail.com (Postfix) with ESMTP id 0FD7049A;
        Fri, 11 Sep 2020 13:57:13 +0800 (CST)
X-MAIL-GRAY: 0
X-MAIL-DELIVERY: 1
X-ADDR-CHECKED4: 1
X-ANTISPAM-LEVEL: 2
X-SKE-CHECKED: 1
X-ABS-CHECKED: 1
Received: from localhost.localdomain (unknown [125.88.171.115])
        by smtp.263.net (postfix) whith ESMTP id
 P25136T140525459982080S1599803826185079_;
        Fri, 11 Sep 2020 13:57:12 +0800 (CST)
X-IP-DOMAINF: 1
X-UNIQUE-TAG: <6aaa4e79d86ee4d5edf8d473087f072a>
X-RL-SENDER: yili@winhong.com
X-SENDER: yili@winhong.com
X-LOGIN-NAME: yili@winhong.com
X-FST-TO: pbonzini@redhat.com
X-SENDER-IP: 125.88.171.115
X-ATTACHMENT-NUM: 0
X-DNS-TYPE: 0
X-System-Flag: 0
From: Yi Li <yili@winhong.com>
To: pbonzini@redhat.com
Cc: yilikernel@gmail.com, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, Yi Li <yili@winhong.com>
Subject: [PATCH] kvm/eventfd:do wildcard calculation before
 list_for_each_entry_safe
Date: Fri, 11 Sep 2020 13:56:52 +0800
Message-Id: <20200911055652.3041762-1-yili@winhong.com>
X-Mailer: git-send-email 2.25.3
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

There is no need to calculate wildcard in each loop
since wildcard is not changed.

Signed-off-by: Yi Li <yili@winhong.com>
---
 virt/kvm/eventfd.c | 4 +++-
 1 file changed, 3 insertions(+), 1 deletion(-)

```
#### [PATCH] KVM: PPC: Book3S HV: Do not allocate HPT for a nested guest
##### From: Fabiano Rosas <farosas@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Fabiano Rosas <farosas@linux.ibm.com>
X-Patchwork-Id: 11769761
Return-Path: <SRS0=Lkah=CU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 77118618
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 11 Sep 2020 04:16:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4C6A3221E8
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 11 Sep 2020 04:16:42 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="OHKrWCfd"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725766AbgIKEQl (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 11 Sep 2020 00:16:41 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:64108 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1725283AbgIKEQj (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 11 Sep 2020 00:16:39 -0400
Received: from pps.filterd (m0098419.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 08B40kG2091940;
        Fri, 11 Sep 2020 00:16:22 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=LHOkpPN83ZtmAlscrJcPGRdOy5V9rMnM7fXtdJV7PO0=;
 b=OHKrWCfdhWSqTX97Id1N22I4UWO35mrfuXSb9ECeuzJXrrNZKWNWCCCjz4KxT6RDZk0z
 BgmzCrwHx92EQJGk1fDHbLnkh9THpGyCVLWzsoRixOFSkrUesTdNb0+OPi60V6XUJghj
 uk4GWBD1N4XfeDTPG7l/Olhuj1dMDo5H+FRTMwYGV+i+7IN4p6Tjh+XkoM/Sjg5CCpLp
 qAraYZJoV46GiK22alsozGA5GmKkLt5Nxw/zS0k+6U0Qc3Q+arDBefAp5KNK2L2UExw2
 W1FRKZ+bwrF1qyW1lwRQLiPRPoHmZSuANvRi0JVk378fTYoCEgvlzSKKLJrlHLPxFFIN aA==
Received: from ppma05wdc.us.ibm.com (1b.90.2fa9.ip4.static.sl-reverse.com
 [169.47.144.27])
        by mx0b-001b2d01.pphosted.com with ESMTP id 33g1rp8fv7-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 11 Sep 2020 00:16:22 -0400
Received: from pps.filterd (ppma05wdc.us.ibm.com [127.0.0.1])
        by ppma05wdc.us.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 08B4BYji016703;
        Fri, 11 Sep 2020 04:16:21 GMT
Received: from b03cxnp08028.gho.boulder.ibm.com
 (b03cxnp08028.gho.boulder.ibm.com [9.17.130.20])
        by ppma05wdc.us.ibm.com with ESMTP id 33c2a9n55p-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 11 Sep 2020 04:16:21 +0000
Received: from b03ledav006.gho.boulder.ibm.com
 (b03ledav006.gho.boulder.ibm.com [9.17.130.237])
        by b03cxnp08028.gho.boulder.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 08B4GK4r15729130
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 11 Sep 2020 04:16:21 GMT
Received: from b03ledav006.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id E09B6C6061;
        Fri, 11 Sep 2020 04:16:20 +0000 (GMT)
Received: from b03ledav006.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 3FBFFC6057;
        Fri, 11 Sep 2020 04:16:19 +0000 (GMT)
Received: from farosas.linux.ibm.com.com (unknown [9.80.219.36])
        by b03ledav006.gho.boulder.ibm.com (Postfix) with ESMTP;
        Fri, 11 Sep 2020 04:16:18 +0000 (GMT)
From: Fabiano Rosas <farosas@linux.ibm.com>
To: kvm-ppc@vger.kernel.org
Cc: linuxppc-dev@lists.ozlabs.org, kvm@vger.kernel.org,
        paulus@ozlabs.org, mpe@ellerman.id.au, david@gibson.dropbear.id.au
Subject: [PATCH] KVM: PPC: Book3S HV: Do not allocate HPT for a nested guest
Date: Fri, 11 Sep 2020 01:16:07 -0300
Message-Id: <20200911041607.198092-1-farosas@linux.ibm.com>
X-Mailer: git-send-email 2.25.4
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-09-11_01:2020-09-10,2020-09-11 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 malwarescore=0
 mlxlogscore=999 clxscore=1011 adultscore=0 suspectscore=1 impostorscore=0
 phishscore=0 lowpriorityscore=0 mlxscore=0 bulkscore=0 priorityscore=1501
 spamscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2009110026
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The current nested KVM code does not support HPT guests. This is
informed/enforced in some ways:

- Hosts < P9 will not be able to enable the nested HV feature;

- The nested hypervisor MMU capabilities will not contain
  KVM_CAP_PPC_MMU_HASH_V3;

- QEMU reflects the MMU capabilities in the
  'ibm,arch-vec-5-platform-support' device-tree property;

- The nested guest, at 'prom_parse_mmu_model' ignores the
  'disable_radix' kernel command line option if HPT is not supported;

- The KVM_PPC_CONFIGURE_V3_MMU ioctl will fail if trying to use HPT.

There is, however, still a way to start a HPT guest by using
max-compat-cpu=power8 at the QEMU machine options. This leads to the
guest being set to use hash after QEMU calls the KVM_PPC_ALLOCATE_HTAB
ioctl.

With the guest set to hash, the nested hypervisor goes through the
entry path that has no knowledge of nesting (kvmppc_run_vcpu) and
crashes when it tries to execute an hypervisor-privileged (mtspr
HDEC) instruction at __kvmppc_vcore_entry:

root@L1:~ $ qemu-system-ppc64 -machine pseries,max-cpu-compat=power8 ...

<snip>
[  538.543303] CPU: 83 PID: 25185 Comm: CPU 0/KVM Not tainted 5.9.0-rc4 #1
[  538.543355] NIP:  c00800000753f388 LR: c00800000753f368 CTR: c0000000001e5ec0
[  538.543417] REGS: c0000013e91e33b0 TRAP: 0700   Not tainted  (5.9.0-rc4)
[  538.543470] MSR:  8000000002843033 <SF,VEC,VSX,FP,ME,IR,DR,RI,LE>  CR: 22422882  XER: 20040000
[  538.543546] CFAR: c00800000753f4b0 IRQMASK: 3
               GPR00: c0080000075397a0 c0000013e91e3640 c00800000755e600 0000000080000000
               GPR04: 0000000000000000 c0000013eab19800 c000001394de0000 00000043a054db72
               GPR08: 00000000003b1652 0000000000000000 0000000000000000 c0080000075502e0
               GPR12: c0000000001e5ec0 c0000007ffa74200 c0000013eab19800 0000000000000008
               GPR16: 0000000000000000 c00000139676c6c0 c000000001d23948 c0000013e91e38b8
               GPR20: 0000000000000053 0000000000000000 0000000000000001 0000000000000000
               GPR24: 0000000000000001 0000000000000001 0000000000000000 0000000000000001
               GPR28: 0000000000000001 0000000000000053 c0000013eab19800 0000000000000001
[  538.544067] NIP [c00800000753f388] __kvmppc_vcore_entry+0x90/0x104 [kvm_hv]
[  538.544121] LR [c00800000753f368] __kvmppc_vcore_entry+0x70/0x104 [kvm_hv]
[  538.544173] Call Trace:
[  538.544196] [c0000013e91e3640] [c0000013e91e3680] 0xc0000013e91e3680 (unreliable)
[  538.544260] [c0000013e91e3820] [c0080000075397a0] kvmppc_run_core+0xbc8/0x19d0 [kvm_hv]
[  538.544325] [c0000013e91e39e0] [c00800000753d99c] kvmppc_vcpu_run_hv+0x404/0xc00 [kvm_hv]
[  538.544394] [c0000013e91e3ad0] [c0080000072da4fc] kvmppc_vcpu_run+0x34/0x48 [kvm]
[  538.544472] [c0000013e91e3af0] [c0080000072d61b8] kvm_arch_vcpu_ioctl_run+0x310/0x420 [kvm]
[  538.544539] [c0000013e91e3b80] [c0080000072c7450] kvm_vcpu_ioctl+0x298/0x778 [kvm]
[  538.544605] [c0000013e91e3ce0] [c0000000004b8c2c] sys_ioctl+0x1dc/0xc90
[  538.544662] [c0000013e91e3dc0] [c00000000002f9a4] system_call_exception+0xe4/0x1c0
[  538.544726] [c0000013e91e3e20] [c00000000000d140] system_call_common+0xf0/0x27c
[  538.544787] Instruction dump:
[  538.544821] f86d1098 60000000 60000000 48000099 e8ad0fe8 e8c500a0 e9264140 75290002
[  538.544886] 7d1602a6 7cec42a6 40820008 7d0807b4 <7d164ba6> 7d083a14 f90d10a0 480104fd
[  538.544953] ---[ end trace 74423e2b948c2e0c ]---

This patch makes the KVM_PPC_ALLOCATE_HTAB ioctl fail when running in
the nested hypervisor, causing QEMU to abort.

Reported-by: Satheesh Rajendran <sathnaga@linux.vnet.ibm.com>
Signed-off-by: Fabiano Rosas <farosas@linux.ibm.com>
Reviewed-by: Greg Kurz <groug@kaod.org>
---
 arch/powerpc/kvm/book3s_hv.c | 6 ++++++
 1 file changed, 6 insertions(+)

```
#### [PATCH] KVM: x86: always allow writing '0' to MSR_KVM_ASYNC_PF_EN
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11770057
Return-Path: <SRS0=Lkah=CU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8311359D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 11 Sep 2020 09:32:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 62E3820855
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 11 Sep 2020 09:32:06 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="EYfN7uYR"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725820AbgIKJcC (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 11 Sep 2020 05:32:02 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:24566 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1725554AbgIKJcA (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 11 Sep 2020 05:32:00 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1599816717;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=K4DFyJXY8m+V25NE+T5vQS6MN0ZdnFjFO0L25fv/fME=;
        b=EYfN7uYRaluIVseqYa+ObOLd0QwCztGQJt8293fz0QMQrFvCH8gZKlF6nkhNqYYZnSHWFt
        hlwUzUPkgPRMIV5idFXq9ts2iMMMelBKwMP70NAHM8pcZuzu3iBSR4FjTnfYY7U9SjE7zV
        /cL1Lzs8dX3q5544CamOA+UIFp8tKjQ=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-472-5qZrdsEbNLaKlaFb9QaiCw-1; Fri, 11 Sep 2020 05:31:53 -0400
X-MC-Unique: 5qZrdsEbNLaKlaFb9QaiCw-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id A2C1B18B9F01;
        Fri, 11 Sep 2020 09:31:51 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.193.114])
        by smtp.corp.redhat.com (Postfix) with ESMTP id A4A8427BCC;
        Fri, 11 Sep 2020 09:31:48 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        "Dr . David Alan Gilbert" <dgilbert@redhat.com>,
        linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: x86: always allow writing '0' to MSR_KVM_ASYNC_PF_EN
Date: Fri, 11 Sep 2020 11:31:47 +0200
Message-Id: <20200911093147.484565-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Even without in-kernel LAPIC we should allow writing '0' to
MSR_KVM_ASYNC_PF_EN as we're not enabling the mechanism. In
particular, QEMU with 'kernel-irqchip=off' fails to start
a guest with

qemu-system-x86_64: error: failed to set MSR 0x4b564d02 to 0x0

Fixes: 9d3c447c72fb2 ("KVM: X86: Fix async pf caused null-ptr-deref")
Reported-by: Dr. David Alan Gilbert <dgilbert@redhat.com>
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/x86.c | 6 +++---
 1 file changed, 3 insertions(+), 3 deletions(-)

```
#### [PATCH][next] KVM: SVM: nested: fix free of uninitialized pointers save and ctl
##### From: Colin King <colin.king@canonical.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Colin King <colin.king@canonical.com>
X-Patchwork-Id: 11770343
Return-Path: <SRS0=Lkah=CU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EE165698
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 11 Sep 2020 11:07:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DBC0921D92
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 11 Sep 2020 11:07:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725785AbgIKLHz (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 11 Sep 2020 07:07:55 -0400
Received: from youngberry.canonical.com ([91.189.89.112]:37556 "EHLO
        youngberry.canonical.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725710AbgIKLHy (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 11 Sep 2020 07:07:54 -0400
Received: from 1.general.cking.uk.vpn ([10.172.193.212] helo=localhost)
        by youngberry.canonical.com with esmtpsa
 (TLS1.2:ECDHE_RSA_AES_128_GCM_SHA256:128)
        (Exim 4.86_2)
        (envelope-from <colin.king@canonical.com>)
        id 1kGgtu-0006tV-Hl; Fri, 11 Sep 2020 11:07:30 +0000
From: Colin King <colin.king@canonical.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        x86@kernel.org (maintainer:X86 ARCHITECTURE),
        "H . Peter Anvin" <hpa@zytor.com>, kvm@vger.kernel.org
Cc: kernel-janitors@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH][next] KVM: SVM: nested: fix free of uninitialized pointers
 save and ctl
Date: Fri, 11 Sep 2020 12:07:30 +0100
Message-Id: <20200911110730.24238-1-colin.king@canonical.com>
X-Mailer: git-send-email 2.27.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Colin Ian King <colin.king@canonical.com>

Currently the error exit path to outt_set_gif will kfree on uninitialized
pointers save and ctl.  Fix this by ensuring these pointers are
inintialized to NULL to avoid garbage pointer freeing.

Addresses-Coverity: ("Uninitialized pointer read")
Fixes: 6ccbd29ade0d ("KVM: SVM: nested: Don't allocate VMCB structures on stack")
Signed-off-by: Colin Ian King <colin.king@canonical.com>
---
 arch/x86/kvm/svm/nested.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH v6 01/12] KVM: SVM: Introduce vmcb_(set_intercept/clr_intercept/_is_intercept)
##### From: Babu Moger <babu.moger@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Babu Moger <babu.moger@amd.com>
X-Patchwork-Id: 11771433
Return-Path: <SRS0=Lkah=CU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0E8FD618
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 11 Sep 2020 19:35:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E2FED22208
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 11 Sep 2020 19:34:59 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="ZSIqcAu9"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725796AbgIKTew (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 11 Sep 2020 15:34:52 -0400
Received: from mail-dm6nam10on2075.outbound.protection.outlook.com
 ([40.107.93.75]:49377
        "EHLO NAM10-DM6-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1725835AbgIKT2K (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 11 Sep 2020 15:28:10 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=lyi/i5NGGL/Rvpld8rudFDBOXQAoQ6EmJYNoTQf6T87GTa18MAeIcPRl7DkqBzaKZ7J5xKAH4s2/SYPsyziLzys2/6i4oYHwxJjH/keDQ22ioMCOtcRt0yfACZq5E6/yRqxJ0nRiGwQ5kRlsbIxUYpD9zFBBDwOjZ3pu00WkSKogH+CFNwmncJ5BWRM1tDcDXf3ADQxXd8y7aKJPBz/SLg9FC6PO+Of1Aa+mw0BFs5qhAF+0eclnLnL5bXNHkYcBZ2ksGcBBt2GyAQLOndLfY3LQlQZoRhlkOVtuz+FpCnGub5eI4bMQ0cWIwXn6mhe5i0BOLXwIZn8CUPlysLa0gQ==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=VsEd+IONZz7nfctO26GqncX8mvyIk9ArYkf/jcTkvFc=;
 b=ah55lTjUgyAfEzMyoB/+bmeVmU7lDljyB9MmchYKzAJLJOD5PTZxbTTxmzw23o/G0WIudzO1h4+ithnyyU4hCfoKKCcVLE8ckOhwuBVckU+IpMGk/m7XF9tuF4PNsozu3IWbz7s3hUunyQJ3+VQPMqHCOyTTFR5KPaY8uXtfXQBVrT2OONbIn8B3L6HCiJ2xVZQhM5sCwMhQkjaAmNosLCweVew7J0ADrF6XLhhfI6EEQ43WHgvsJX45Bvjsumn0uRYcdV6riX/W2DNKK6p7RQlO/ZF+Ne/AK3g7ea0Gy7YCCkoyCrKgg+HG9m+8ZTUcZ3+tbPpgCtbTzWIq9fgtVw==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=VsEd+IONZz7nfctO26GqncX8mvyIk9ArYkf/jcTkvFc=;
 b=ZSIqcAu9yl+jFb9f5uCa8bVNysyKKqSIkJdqgJxCXbSNiRdW9QrDRz42Gk23leVR1XB7oLUf3mIZFW3t1aLvUbRu/oKru3ccdhw8LSxGX8+XqBchPIXkw+iYE+WwVBVU/jbCFWa+ziOh9EtD1DcQrXNv/OVV3BtcXqMcLbf4jTA=
Authentication-Results: tencent.com; dkim=none (message not signed)
 header.d=none;tencent.com; dmarc=none action=none header.from=amd.com;
Received: from SN1PR12MB2560.namprd12.prod.outlook.com (2603:10b6:802:26::19)
 by SA0PR12MB4543.namprd12.prod.outlook.com (2603:10b6:806:9d::12) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3370.16; Fri, 11 Sep
 2020 19:27:59 +0000
Received: from SN1PR12MB2560.namprd12.prod.outlook.com
 ([fe80::ccd9:728:9577:200d]) by SN1PR12MB2560.namprd12.prod.outlook.com
 ([fe80::ccd9:728:9577:200d%4]) with mapi id 15.20.3370.017; Fri, 11 Sep 2020
 19:27:59 +0000
Subject: [PATCH v6 01/12] KVM: SVM: Introduce
 vmcb_(set_intercept/clr_intercept/_is_intercept)
From: Babu Moger <babu.moger@amd.com>
To: pbonzini@redhat.com, vkuznets@redhat.com,
        sean.j.christopherson@intel.com, jmattson@google.com
Cc: wanpengli@tencent.com, kvm@vger.kernel.org, joro@8bytes.org,
        x86@kernel.org, linux-kernel@vger.kernel.org, babu.moger@amd.com,
        mingo@redhat.com, bp@alien8.de, hpa@zytor.com, tglx@linutronix.de
Date: Fri, 11 Sep 2020 14:27:58 -0500
Message-ID: <159985247876.11252.16039238014239824460.stgit@bmoger-ubuntu>
In-Reply-To: <159985237526.11252.1516487214307300610.stgit@bmoger-ubuntu>
References: <159985237526.11252.1516487214307300610.stgit@bmoger-ubuntu>
User-Agent: StGit/0.17.1-dirty
X-ClientProxiedBy: SN4PR0501CA0024.namprd05.prod.outlook.com
 (2603:10b6:803:40::37) To SN1PR12MB2560.namprd12.prod.outlook.com
 (2603:10b6:802:26::19)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from [127.0.1.1] (165.204.77.1) by
 SN4PR0501CA0024.namprd05.prod.outlook.com (2603:10b6:803:40::37) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3391.5 via Frontend
 Transport; Fri, 11 Sep 2020 19:27:59 +0000
X-Originating-IP: [165.204.77.1]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 9a6adda3-6338-44b3-632a-08d85688cb29
X-MS-TrafficTypeDiagnostic: SA0PR12MB4543:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SA0PR12MB45435A49D1B2E66976FBB78695240@SA0PR12MB4543.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:2449;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 a9qzhktaRsluvhbmJeJFRn5DaeGO4OL2y54em7ojLe0W7t/J6E2SMQERQakKhbi2DtBRUiPIjMJGoBYNLmYurlp7rfr88ppH3eA1fYVcjB6R+9wnWvwDT3YtyL4nK9jDv2THNRAgCi5rE7O0pfMXSMA9fVCbme7A/FgWZPD6Gq5IGN+tWB9BEUpV5oM36mwwv9sLn8/3Ba+ypMO3wyK7fNBx1BsRj6QDfCN5mOBmQo0yg5J6xbEDhSbzjMdhHZ00vF1hjP0gdnwZM+i76ZE7csFyGo67i9Hx5ArBOyN48XQVoFZhCPPTvRcsUN6xN9O3OYv67U8/ljE96/2x/8EtNQ==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN1PR12MB2560.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(7916004)(4636009)(376002)(136003)(346002)(366004)(39860400002)(396003)(2906002)(956004)(66946007)(66476007)(103116003)(8676002)(66556008)(52116002)(5660300002)(7416002)(9686003)(4326008)(8936002)(44832011)(186003)(16526019)(86362001)(33716001)(16576012)(6486002)(316002)(478600001)(26005);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 9WapRrfjuvClAjC/klkuCCrpya3FMC6Mw7ZfWjaNY02hXHFoLFMPo7WGKFEaYfy2PP0Kk/WiSZz/tcLGlqyAZwlI164e2TF2kOjbpoXcvqUNaGyXpbnYD8aakKniJh7SWZyihBYUVgOCAhNg9lJx1l/bsGhVsuq9keEgrdJXITjNQ8GghHowcP8hpEmNGuJrXhv9bhZIR5HSJIlcIa4Xo4ikU5sRLedLenNJjyC5S+bNPK4BnGtfutGPh2mW7kThEk1M6IB6fkqQuf6q0Xhl14treha6raITcjdJtlyCn/+Hvl405ql8TMbeOKAAKEUdevecLfFavHSeyXrVWlSCT40XEy9P3js3Y7gfJTPppWVtFGc3fC80EfX25JOl2KjHncbOqys1Aqpi5EBf8PBeR44LRTSWSaMPjIB+rP40+pWqnO/YVqYzTOpAIhF/GS3l1NAeNNrq9MpmopF4dd/FWjIbDzY5UjgxyC8T/LnADS0bF+TlDyWaQmeAjXOWd8nZLwZuToMHQvCeSTQ4nHJbVvpHSEX7O+Np1HHtwAdBZbJkG9ulWN03WJutbsw+VdUrB50gLLMSRZh5gE2w9Hp+imwbeQhcZeJ5H2ju3/1CRx6JQBK+LgTvpKi7L6JK4DdraC50j6LiN8siGJMD7qC05w==
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 9a6adda3-6338-44b3-632a-08d85688cb29
X-MS-Exchange-CrossTenant-AuthSource: SN1PR12MB2560.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 11 Sep 2020 19:27:59.8182
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 XTcBLrJJTxGiO9p1X9IR1N4kZHBdQuMxK06yI7AYY9uXOmI4ku+eF8cYzoJrvALQ
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SA0PR12MB4543
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is in preparation for the future intercept vector additions.

Add new functions vmcb_set_intercept, vmcb_clr_intercept and vmcb_is_intercept
using kernel APIs __set_bit, __clear_bit and test_bit espectively.

Signed-off-by: Babu Moger <babu.moger@amd.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 arch/x86/kvm/svm/svm.h |   15 +++++++++++++++
 1 file changed, 15 insertions(+)

```
#### [PATCH] vfio iommu: Add dma limit capability
##### From: Matthew Rosato <mjrosato@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Matthew Rosato <mjrosato@linux.ibm.com>
X-Patchwork-Id: 11770961
Return-Path: <SRS0=Lkah=CU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 002A6698
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 11 Sep 2020 16:44:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C41B6221ED
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 11 Sep 2020 16:44:37 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="cDk7oIWt"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726242AbgIKQof (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 11 Sep 2020 12:44:35 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:13128 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726392AbgIKQoT (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 11 Sep 2020 12:44:19 -0400
Received: from pps.filterd (m0098394.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 08BGYkvk024226;
        Fri, 11 Sep 2020 12:44:13 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references; s=pp1;
 bh=jaxEgQC6wdaz4q4DPBtqSbQcompo/vEQ4h4vw9qyZ58=;
 b=cDk7oIWtwX2DxKkZwQcb581iwmL4GVmZSOpFkK5XUYF/hKTA/pnYztMgC6k/BrmXOfFA
 PZt6w5k7rTjO9SWHS/VVqc8DQv+628stSHRrAPpSCsPTHGN4DkWBsrLlbIh7EnIf0PbM
 5AQhPjyoBRMobOZ/63lp+rBJUO2RsdktlMuMkZAbOZbNSocv12UznaJPfN6CKVEnpiuj
 6EoSYAr4KmSi+U/ZGNgpffuuUec2pulTVaCd2ouRIiAyMMHN/DtUK0vJk9gn2suhpGvh
 P3xUfqLCVCFR5WDp66shLW75Fx5GQ4Ms7Obdzs+wgKRnV/Ej1ii6LpbDVt6M9vcxhpDP fA==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 33gcdy8y2h-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 11 Sep 2020 12:44:13 -0400
Received: from m0098394.ppops.net (m0098394.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 08BGZ82e025595;
        Fri, 11 Sep 2020 12:44:13 -0400
Received: from ppma02dal.us.ibm.com (a.bd.3ea9.ip4.static.sl-reverse.com
 [169.62.189.10])
        by mx0a-001b2d01.pphosted.com with ESMTP id 33gcdy8y2a-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 11 Sep 2020 12:44:13 -0400
Received: from pps.filterd (ppma02dal.us.ibm.com [127.0.0.1])
        by ppma02dal.us.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 08BGgVux018955;
        Fri, 11 Sep 2020 16:44:12 GMT
Received: from b01cxnp22034.gho.pok.ibm.com (b01cxnp22034.gho.pok.ibm.com
 [9.57.198.24])
        by ppma02dal.us.ibm.com with ESMTP id 33c2aa5f8a-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 11 Sep 2020 16:44:12 +0000
Received: from b01ledav003.gho.pok.ibm.com (b01ledav003.gho.pok.ibm.com
 [9.57.199.108])
        by b01cxnp22034.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id 08BGiBQr38928760
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 11 Sep 2020 16:44:11 GMT
Received: from b01ledav003.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 6FC48B205F;
        Fri, 11 Sep 2020 16:44:11 +0000 (GMT)
Received: from b01ledav003.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id EBDE8B2064;
        Fri, 11 Sep 2020 16:44:09 +0000 (GMT)
Received: from oc4221205838.ibm.com (unknown [9.211.91.207])
        by b01ledav003.gho.pok.ibm.com (Postfix) with ESMTP;
        Fri, 11 Sep 2020 16:44:09 +0000 (GMT)
From: Matthew Rosato <mjrosato@linux.ibm.com>
To: alex.williamson@redhat.com, cohuck@redhat.com
Cc: pmorel@linux.ibm.com, schnelle@linux.ibm.com, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH] vfio iommu: Add dma limit capability
Date: Fri, 11 Sep 2020 12:44:03 -0400
Message-Id: <1599842643-2553-2-git-send-email-mjrosato@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1599842643-2553-1-git-send-email-mjrosato@linux.ibm.com>
References: <1599842643-2553-1-git-send-email-mjrosato@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-09-11_08:2020-09-10,2020-09-11 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 adultscore=0 spamscore=0 suspectscore=0 mlxlogscore=887 impostorscore=0
 mlxscore=0 phishscore=0 bulkscore=0 lowpriorityscore=0 malwarescore=0
 clxscore=1015 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2009110131
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Commit 492855939bdb ("vfio/type1: Limit DMA mappings per container")
added the ability to limit the number of memory backed DMA mappings.
However on s390x, when lazy mapping is in use, we use a very large
number of concurrent mappings.  Let's provide the limitation to
userspace via the IOMMU info chain so that userspace can take
appropriate mitigation.

Signed-off-by: Matthew Rosato <mjrosato@linux.ibm.com>
---
 drivers/vfio/vfio_iommu_type1.c | 17 +++++++++++++++++
 include/uapi/linux/vfio.h       | 16 ++++++++++++++++
 2 files changed, 33 insertions(+)

```
#### [PATCH] vhost: reduce stack usage in log_used
##### From: Li Wang <li.wang@windriver.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Li Wang <li.wang@windriver.com>
X-Patchwork-Id: 11770795
Return-Path: <SRS0=Lkah=CU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B8963746
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 11 Sep 2020 15:15:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AACFB207FB
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 11 Sep 2020 15:15:37 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726401AbgIKPPX (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 11 Sep 2020 11:15:23 -0400
Received: from mail1.windriver.com ([147.11.146.13]:59212 "EHLO
        mail1.windriver.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726074AbgIKPNX (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 11 Sep 2020 11:13:23 -0400
Received: from ALA-HCA.corp.ad.wrs.com (ala-hca.corp.ad.wrs.com
 [147.11.189.40])
        by mail1.windriver.com (8.15.2/8.15.2) with ESMTPS id 08BFCplq011659
        (version=TLSv1 cipher=DHE-RSA-AES256-SHA bits=256 verify=FAIL);
        Fri, 11 Sep 2020 08:12:51 -0700 (PDT)
Received: from pek-lwang1-u1404.wrs.com (128.224.162.178) by
 ALA-HCA.corp.ad.wrs.com (147.11.189.40) with Microsoft SMTP Server id
 14.3.487.0; Fri, 11 Sep 2020 08:12:50 -0700
From: Li Wang <li.wang@windriver.com>
To: <mst@redhat.com>, <jasowang@redhat.com>
CC: <kvm@vger.kernel.org>, <virtualization@lists.linux-foundation.org>,
        <netdev@vger.kernel.org>, <linux-kernel@vger.kernel.org>
Subject: [PATCH] vhost: reduce stack usage in log_used
Date: Fri, 11 Sep 2020 23:09:39 +0800
Message-ID: <1599836979-4950-1-git-send-email-li.wang@windriver.com>
X-Mailer: git-send-email 2.7.4
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Fix the warning: [-Werror=-Wframe-larger-than=]

drivers/vhost/vhost.c: In function log_used:
drivers/vhost/vhost.c:1906:1:
warning: the frame size of 1040 bytes is larger than 1024 bytes

Signed-off-by: Li Wang <li.wang@windriver.com>
---
 drivers/vhost/vhost.c | 14 ++++++++++----
 1 file changed, 10 insertions(+), 4 deletions(-)

```
#### [PATCH 1/4 v3] x86: AMD: Replace numeric value for SME CPUID leaf with a #define
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11771399
Return-Path: <SRS0=Lkah=CU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D5EE9139F
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 11 Sep 2020 19:28:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AEF782220F
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 11 Sep 2020 19:28:41 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="PxaToik1"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725892AbgIKT2g (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 11 Sep 2020 15:28:36 -0400
Received: from aserp2120.oracle.com ([141.146.126.78]:49598 "EHLO
        aserp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725776AbgIKT14 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 11 Sep 2020 15:27:56 -0400
Received: from pps.filterd (aserp2120.oracle.com [127.0.0.1])
        by aserp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 08BJObPC175106;
        Fri, 11 Sep 2020 19:26:32 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references; s=corp-2020-01-29;
 bh=9Yu0+hVjg349shgtmGEHPIIhGF87WXKFZaup59ONGuE=;
 b=PxaToik1sSRid0lUYOQlHI5sZyx5JbdMRjbQIZZJGphKCd5YUvxnC5NA3U1UY4HPuTYj
 crld18ZhN/JEJrYqIMAjpzyVzQ3HD1e1Qznkfvhu4D+5EGv6o46QN3JLs3uOpd95iaqb
 5hbK0mIdLPKn9Fnv5m5qpovquPdntqNBu04JTRob4lg442m62GHcsddxHXuHJYylvyL+
 s43Ozh0Q9eIBFqHEFdreEDE3hMRrl17SZsrOl7D0N4YsfvZtgPWzgy18a1hRcxHm/AAi
 mdbFa7+ap0KzRiRxk0oE3xkm2SinDRyLR6rd1uY7nJsUj1I2MFosNQJPheyD9capjvfK Iw==
Received: from aserp3020.oracle.com (aserp3020.oracle.com [141.146.126.70])
        by aserp2120.oracle.com with ESMTP id 33c2mmg2vn-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=FAIL);
        Fri, 11 Sep 2020 19:26:32 +0000
Received: from pps.filterd (aserp3020.oracle.com [127.0.0.1])
        by aserp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 08BJPDuf019612;
        Fri, 11 Sep 2020 19:26:32 GMT
Received: from userv0122.oracle.com (userv0122.oracle.com [156.151.31.75])
        by aserp3020.oracle.com with ESMTP id 33cmkdu77n-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 11 Sep 2020 19:26:31 +0000
Received: from abhmp0002.oracle.com (abhmp0002.oracle.com [141.146.116.8])
        by userv0122.oracle.com (8.14.4/8.14.4) with ESMTP id 08BJQPJi009907;
        Fri, 11 Sep 2020 19:26:26 GMT
Received: from nsvm-sadhukhan-1.osdevelopmeniad.oraclevcn.com
 (/100.100.230.216)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Fri, 11 Sep 2020 12:26:24 -0700
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com, tglx@linutronix.de,
        mingo@redhat.com, bp@alien8.de, x86@kernel.org,
        sean.j.christopherson@intel.com, vkuznets@redhat.com,
        wanpengli@tencent.com, joro@8bytes.org,
        dave.hansen@linux.intel.com, luto@kernel.org, peterz@infradead.org,
        linux-kernel@vger.kernel.org, hpa@zytor.com
Subject: [PATCH 1/4 v3] x86: AMD: Replace numeric value for SME CPUID leaf
 with a #define
Date: Fri, 11 Sep 2020 19:25:58 +0000
Message-Id: <20200911192601.9591-2-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.18.4
In-Reply-To: <20200911192601.9591-1-krish.sadhukhan@oracle.com>
References: <20200911192601.9591-1-krish.sadhukhan@oracle.com>
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9741
 signatures=668679
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 spamscore=0
 malwarescore=0 phishscore=0
 mlxlogscore=999 bulkscore=0 adultscore=0 mlxscore=0 suspectscore=1
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2006250000
 definitions=main-2009110155
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9741
 signatures=668679
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 mlxscore=0
 priorityscore=1501
 phishscore=0 adultscore=0 bulkscore=0 clxscore=1015 mlxlogscore=999
 malwarescore=0 suspectscore=1 lowpriorityscore=0 spamscore=0
 impostorscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2009110155
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 arch/x86/boot/compressed/mem_encrypt.S | 5 +++--
 arch/x86/include/asm/cpufeatures.h     | 5 +++++
 arch/x86/kernel/cpu/amd.c              | 2 +-
 arch/x86/kernel/cpu/scattered.c        | 4 ++--
 arch/x86/kvm/cpuid.c                   | 2 +-
 arch/x86/kvm/svm/svm.c                 | 4 ++--
 arch/x86/mm/mem_encrypt_identity.c     | 4 ++--
 7 files changed, 16 insertions(+), 10 deletions(-)

```
