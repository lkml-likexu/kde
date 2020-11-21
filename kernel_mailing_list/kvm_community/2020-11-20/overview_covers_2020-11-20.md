

#### [PATCH v2 00/12] x86: major paravirt cleanup
##### From: Juergen Gross <jgross@suse.com>

```c
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=suse.com; s=susede1;
        t=1605872794;
 h=from:from:reply-to:date:date:message-id:message-id:to:to:cc:cc:
         mime-version:mime-version:
  content-transfer-encoding:content-transfer-encoding;
        bh=fjHe3+rmjY5cASW1XAPrcDHWzGbizvpE61ZYWB4j3cw=;
        b=rHmTXjwVBmFJKyhCEqOmhgg9FGZswY8WJdm/UueRf8DddoT49obCKWkkpulXZkEmbMyr53
        +tF6wEHiJQUjLKUN11yRtxzw2OPKHPWiM+6wvnAdRmBLFldnpbyUuBKOY+QFrHkVnZVwFO
        BIZuxt25L9jBmyI/EuK0mKwTZgHx17c=
Received: from relay2.suse.de (unknown [195.135.221.27])
        by mx2.suse.de (Postfix) with ESMTP id C23BCAD57;
        Fri, 20 Nov 2020 11:46:33 +0000 (UTC)
From: Juergen Gross <jgross@suse.com>
To: xen-devel@lists.xenproject.org, x86@kernel.org,
        linux-kernel@vger.kernel.org,
        virtualization@lists.linux-foundation.org,
        linux-hyperv@vger.kernel.org, kvm@vger.kernel.org
Cc: peterz@infradead.org, luto@kernel.org,
        Juergen Gross <jgross@suse.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        "H. Peter Anvin" <hpa@zytor.com>,
        Boris Ostrovsky <boris.ostrovsky@oracle.com>,
        Stefano Stabellini <sstabellini@kernel.org>,
        Deep Shah <sdeep@vmware.com>,
        "VMware, Inc." <pv-drivers@vmware.com>,
        "K. Y. Srinivasan" <kys@microsoft.com>,
        Haiyang Zhang <haiyangz@microsoft.com>,
        Stephen Hemminger <sthemmin@microsoft.com>,
        Wei Liu <wei.liu@kernel.org>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Daniel Lezcano <daniel.lezcano@linaro.org>,
        Juri Lelli <juri.lelli@redhat.com>,
        Vincent Guittot <vincent.guittot@linaro.org>,
        Dietmar Eggemann <dietmar.eggemann@arm.com>,
        Steven Rostedt <rostedt@goodmis.org>,
        Ben Segall <bsegall@google.com>, Mel Gorman <mgorman@suse.de>,
        Daniel Bristot de Oliveira <bristot@redhat.com>
Subject: [PATCH v2 00/12] x86: major paravirt cleanup
Date: Fri, 20 Nov 2020 12:46:18 +0100
Message-Id: <20201120114630.13552-1-jgross@suse.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is a major cleanup of the paravirt infrastructure aiming at
eliminating all custom code patching via paravirt patching.

This is achieved by using ALTERNATIVE instead, leading to the ability
to give objtool access to the patched in instructions.

In order to remove most of the 32-bit special handling from pvops the
time related operations are switched to use static_call() instead.

At the end of this series all paravirt patching has to do is to
replace indirect calls with direct ones. In a further step this could
be switched to static_call(), too, but that would require a major
header file disentangling.

Note that an updated objtool is needed for this series, as otherwise
lots of warnings due to alternative instructions modifying the stack
will be issued during the build.

Changes in V2:
- added patches 5-12

Juergen Gross (12):
  x86/xen: use specific Xen pv interrupt entry for MCE
  x86/xen: use specific Xen pv interrupt entry for DF
  x86/pv: switch SWAPGS to ALTERNATIVE
  x86/xen: drop USERGS_SYSRET64 paravirt call
  x86: rework arch_local_irq_restore() to not use popf
  x86/paravirt: switch time pvops functions to use static_call()
  x86: add new features for paravirt patching
  x86/paravirt: remove no longer needed 32-bit pvops cruft
  x86/paravirt: switch iret pvops to ALTERNATIVE
  x86/paravirt: add new macros PVOP_ALT* supporting pvops in
    ALTERNATIVEs
  x86/paravirt: switch functions with custom code to ALTERNATIVE
  x86/paravirt: have only one paravirt patch function

 arch/x86/Kconfig                      |   1 +
 arch/x86/entry/entry_32.S             |   4 +-
 arch/x86/entry/entry_64.S             |  32 ++--
 arch/x86/include/asm/cpufeatures.h    |   3 +
 arch/x86/include/asm/idtentry.h       |   6 +
 arch/x86/include/asm/irqflags.h       |  51 ++----
 arch/x86/include/asm/mshyperv.h       |  11 --
 arch/x86/include/asm/paravirt.h       | 170 ++++++--------------
 arch/x86/include/asm/paravirt_time.h  |  38 +++++
 arch/x86/include/asm/paravirt_types.h | 222 ++++++++++++--------------
 arch/x86/kernel/Makefile              |   3 +-
 arch/x86/kernel/alternative.c         |  30 +++-
 arch/x86/kernel/asm-offsets.c         |   8 -
 arch/x86/kernel/asm-offsets_64.c      |   3 -
 arch/x86/kernel/cpu/vmware.c          |   5 +-
 arch/x86/kernel/head_64.S             |   2 -
 arch/x86/kernel/irqflags.S            |  11 --
 arch/x86/kernel/kvm.c                 |   3 +-
 arch/x86/kernel/kvmclock.c            |   3 +-
 arch/x86/kernel/paravirt.c            |  70 +++-----
 arch/x86/kernel/paravirt_patch.c      | 109 -------------
 arch/x86/kernel/tsc.c                 |   3 +-
 arch/x86/xen/enlighten_pv.c           |  36 +++--
 arch/x86/xen/irq.c                    |  23 ---
 arch/x86/xen/time.c                   |  12 +-
 arch/x86/xen/xen-asm.S                |  52 +-----
 arch/x86/xen/xen-ops.h                |   3 -
 drivers/clocksource/hyperv_timer.c    |   5 +-
 drivers/xen/time.c                    |   3 +-
 kernel/sched/sched.h                  |   1 +
 30 files changed, 325 insertions(+), 598 deletions(-)
 create mode 100644 arch/x86/include/asm/paravirt_time.h
 delete mode 100644 arch/x86/kernel/paravirt_patch.c
```
#### [PATCH 0/3] Introduce new vcpu ioctls KVM_(GET|SET)_MANY_REGS
##### From: <darkhan@amazon.com>
From: Darkhan Mukashov <darkhan@amazon.com>

```c
From patchwork Fri Nov 20 12:56:13 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: darkhan@amazon.com
X-Patchwork-Id: 11920217
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 1F768C56202
	for <kvm@archiver.kernel.org>; Fri, 20 Nov 2020 12:56:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A847D22255
	for <kvm@archiver.kernel.org>; Fri, 20 Nov 2020 12:56:57 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amazon.com header.i=@amazon.com
 header.b="kemxds01"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727933AbgKTM44 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 20 Nov 2020 07:56:56 -0500
Received: from smtp-fw-4101.amazon.com ([72.21.198.25]:50174 "EHLO
        smtp-fw-4101.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726560AbgKTM44 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 20 Nov 2020 07:56:56 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.com; i=@amazon.com; q=dns/txt; s=amazon201209;
  t=1605877016; x=1637413016;
  h=from:to:cc:subject:date:message-id:mime-version;
  bh=Tu3ky8QtpoG4/ntezhBA0uUewx/dtdgS9ou84KSbXl8=;
  b=kemxds01Hy9ZOiA/cyOlZsjA2fDKKF7z08zVtylrUMQJ8NWoZkPkWnlt
   I8La4by+AA5nfQb+nQKwlvhSYY+LIttlBvFBSESfGmzpg6whV0R1LA7jU
   bf5ioDaWQ2bEdSMiViuRG+kKSK1JFA/B1lJ2Lo32zPLyiTzmD9yba1itl
   k=;
X-IronPort-AV: E=Sophos;i="5.78,356,1599523200";
   d="scan'208";a="65112994"
Received: from iad12-co-svc-p1-lb1-vlan2.amazon.com (HELO
 email-inbound-relay-1a-7d76a15f.us-east-1.amazon.com) ([10.43.8.2])
  by smtp-border-fw-out-4101.iad4.amazon.com with ESMTP;
 20 Nov 2020 12:56:48 +0000
Received: from EX13D01EUA002.ant.amazon.com
 (iad12-ws-svc-p26-lb9-vlan3.iad.amazon.com [10.40.163.38])
        by email-inbound-relay-1a-7d76a15f.us-east-1.amazon.com (Postfix) with
 ESMTPS id 930ACA18CE;
        Fri, 20 Nov 2020 12:56:43 +0000 (UTC)
Received: from EX13D52EUA002.ant.amazon.com (10.43.165.139) by
 EX13D01EUA002.ant.amazon.com (10.43.165.199) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Fri, 20 Nov 2020 12:56:42 +0000
Received: from uc995cb558fb65a.ant.amazon.com (10.43.162.50) by
 EX13D52EUA002.ant.amazon.com (10.43.165.139) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Fri, 20 Nov 2020 12:56:37 +0000
From: <darkhan@amazon.com>
To: <pbonzini@redhat.com>
CC: <kvm@vger.kernel.org>, <corbet@lwn.net>, <maz@kernel.org>,
        <james.morse@arm.com>, <catalin.marinas@arm.com>,
        <chenhc@lemote.com>, <paulus@ozlabs.org>, <frankja@linux.ibm.com>,
        <mingo@redhat.com>, <acme@redhat.com>, <graf@amazon.de>,
        <darkhan@amazon.de>, Darkhan Mukashov <darkhan@amazon.com>
Subject: [PATCH 0/3] Introduce new vcpu ioctls KVM_(GET|SET)_MANY_REGS
Date: Fri, 20 Nov 2020 13:56:13 +0100
Message-ID: <20201120125616.14436-1-darkhan@amazon.com>
X-Mailer: git-send-email 2.17.1
MIME-Version: 1.0
X-Originating-IP: [10.43.162.50]
X-ClientProxiedBy: EX13D32UWB001.ant.amazon.com (10.43.161.248) To
 EX13D52EUA002.ant.amazon.com (10.43.165.139)
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Darkhan Mukashov <darkhan@amazon.com>

The ultimate goal is to introduce new vcpu ioctls KVM_(GET|SET)_MANY_REGS.
To introduce these ioctls, implementations of KVM_(GET|SET)_ONE_REG have
to be refactored. Specifically, KVM_(GET|SET)_ONE_REG should be handled in
a generic kvm_vcpu_ioctl function.

New KVM APIs KVM_(GET|SET)_MANY_REGS make it possible to bulk read/write
vCPU registers at one ioctl call. These ioctls can be very useful when
vCPU state serialization/deserialization is required (e.g. live update of
kvm, live migration of guests), hence all registers have to be
saved/restored. KVM_(GET|SET)_MANY_REGS will help avoid performance
overhead associated with syscall (ioctl in our case) handling. Tests
conducted on AWS Graviton2 Processors (64-bit ARM Neoverse cores) show
that average save/restore time of all vCPU registers can be optimized
~3.5 times per vCPU with new ioctls. Test results can be found in Table 1.
+---------+-------------+---------------+
|         | kvm_one_reg | kvm_many_regs |
+---------+-------------+---------------+
| get all |   123 usec  |    33 usec    |
+---------+-------------+---------------+
| set all |   120 usec  |    36 usec    |
+---------+-------------+---------------+
	Table 1. Test results

The patches are based out of kvm/queue.

Darkhan Mukashov (3):
  Documentation: KVM: change description of vcpu ioctls
    KVM_(GET|SET)_ONE_REG
  KVM: handle vcpu ioctls KVM_(GET|SET)_ONE_REG in a generic function
  KVM: introduce new vcpu ioctls KVM_GET_MANY_REGS and KVM_SET_MANY_REGS

 Documentation/virt/kvm/api.rst     | 80 ++++++++++++++++++++++++++++--
 arch/arm64/include/asm/kvm_host.h  |  5 +-
 arch/arm64/kvm/arm.c               | 25 +++-------
 arch/arm64/kvm/guest.c             |  6 ++-
 arch/mips/include/asm/kvm_host.h   |  6 +++
 arch/mips/kvm/mips.c               | 32 ++++++------
 arch/powerpc/include/asm/kvm_ppc.h |  2 -
 arch/powerpc/kvm/powerpc.c         | 20 ++------
 arch/s390/include/asm/kvm_host.h   |  6 +++
 arch/s390/kvm/kvm-s390.c           | 38 +++++++-------
 arch/x86/kvm/x86.c                 | 12 +++++
 include/linux/kvm_host.h           | 18 +++++++
 include/uapi/linux/kvm.h           | 11 ++++
 virt/kvm/kvm_main.c                | 62 +++++++++++++++++++++++
 14 files changed, 244 insertions(+), 79 deletions(-)
```
#### [PATCH v2 0/2] Connect request callback to mdev and vfio-ccw
##### From: Eric Farman <farman@linux.ibm.com>

```c
From patchwork Fri Nov 20 18:07:38 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Farman <farman@linux.ibm.com>
X-Patchwork-Id: 11921511
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B4E1BC56201
	for <kvm@archiver.kernel.org>; Fri, 20 Nov 2020 18:08:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1350722464
	for <kvm@archiver.kernel.org>; Fri, 20 Nov 2020 18:08:07 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="LkseijrR"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729679AbgKTSHu (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 20 Nov 2020 13:07:50 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:25568 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1729284AbgKTSHu (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 20 Nov 2020 13:07:50 -0500
Received: from pps.filterd (m0098399.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 0AKI1seg136543;
        Fri, 20 Nov 2020 13:07:49 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id; s=pp1;
 bh=hZJYjGbJ7SSpHfEryz4NfRrrOXGkbrELDzJma1AXbIQ=;
 b=LkseijrRHGNCQfU+0KXt2mw27pIboWpP4daQ7V/MaCgloJ/Nph3y7eg27D0nR3XMTtBy
 o3geZgLMc6owPnRaPvENQgygN2eY+6z6ig72VsqlOlS+vAGZsxq/vHbDwaGxsBYgL85z
 AczaHTzejhhY9zVzBwzIKF7uFpq6VDsKENDpQLoTO5kZAlUBRb/tziYk4TQ7zsc1Pwwp
 t2DeCQpLM2NuDPFuao+8O2OWskDK9+6WpdxUB/oXIrs9xenunGXg+O0CODGK6m+QDbN/
 0tRWsSnOmJou7nwZXU3nx+TkVdP7BmvuzNVGhIihvntDHnK6gp4mNu3LTG2xGxuTmUMq /Q==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 34xdrw3kng-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 20 Nov 2020 13:07:49 -0500
Received: from m0098399.ppops.net (m0098399.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 0AKI5Ibe155441;
        Fri, 20 Nov 2020 13:07:49 -0500
Received: from ppma06fra.de.ibm.com (48.49.7a9f.ip4.static.sl-reverse.com
 [159.122.73.72])
        by mx0a-001b2d01.pphosted.com with ESMTP id 34xdrw3km3-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 20 Nov 2020 13:07:49 -0500
Received: from pps.filterd (ppma06fra.de.ibm.com [127.0.0.1])
        by ppma06fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 0AKI3XJa006091;
        Fri, 20 Nov 2020 18:07:46 GMT
Received: from b06cxnps4074.portsmouth.uk.ibm.com
 (d06relay11.portsmouth.uk.ibm.com [9.149.109.196])
        by ppma06fra.de.ibm.com with ESMTP id 34t6ghbcth-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 20 Nov 2020 18:07:46 +0000
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06cxnps4074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 0AKI7hBL60752252
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 20 Nov 2020 18:07:43 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 75B8FA4060;
        Fri, 20 Nov 2020 18:07:43 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 64280A4064;
        Fri, 20 Nov 2020 18:07:43 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTPS;
        Fri, 20 Nov 2020 18:07:43 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 4958)
        id 0E732E23B0; Fri, 20 Nov 2020 19:07:43 +0100 (CET)
From: Eric Farman <farman@linux.ibm.com>
To: Cornelia Huck <cohuck@redhat.com>,
        Kirti Wankhede <kwankhede@nvidia.com>,
        Alex Williamson <alex.williamson@redhat.com>
Cc: Halil Pasic <pasic@linux.ibm.com>,
        Matthew Rosato <mjrosato@linux.ibm.com>,
        linux-s390@vger.kernel.org, kvm@vger.kernel.org,
        Eric Farman <farman@linux.ibm.com>
Subject: [PATCH v2 0/2] Connect request callback to mdev and vfio-ccw
Date: Fri, 20 Nov 2020 19:07:38 +0100
Message-Id: <20201120180740.87837-1-farman@linux.ibm.com>
X-Mailer: git-send-email 2.17.1
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.312,18.0.737
 definitions=2020-11-20_09:2020-11-20,2020-11-20 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxscore=0 adultscore=0
 malwarescore=0 bulkscore=0 lowpriorityscore=0 spamscore=0 impostorscore=0
 phishscore=0 mlxlogscore=999 clxscore=1015 priorityscore=1501
 suspectscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2011200120
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

There is a situation where removing all the paths from a device
connected via mdev and vfio-ccw can cause some difficulty.
Using the "chchp -c 0 xx" command to all paths will cause the
device to be removed from the configuration, and any guest
filesystem that is relying on that device will encounter errors.
Interestingly, the last chchp command will actually fail to
return to a shell prompt, and subsequent commands (another
chchp to bring the paths back online, chzdev, etc.) will also
hang because of the outstanding chchp.

The last chchp command drives to vfio_ccw_sch_remove() for every
affected mediated device, and ultimately enters an infinite loop
in vfio_del_group_dev(). This loop is broken when the guest goes
away, which in this case doesn't occur until the guest is shutdown.
This drives vfio_ccw_mdev_release() and thus vfio_device_release()
to wake up the vfio_del_group_dev() thread.

There is also a callback mechanism called "request" to ask a
driver (and perhaps user) to release the device, but this is not
implemented for mdev. So this adds one to that point, and then
wire it to vfio-ccw to pass it along to userspace. This will
gracefully drive the unplug code, and everything behaves nicely.

Despite the testing that was occurring, this doesn't appear related
to the vfio-ccw channel path handling code. I can reproduce this with
an older kernel/QEMU, which makes sense because the above behavior is
driven from the subchannel event codepaths and not the chpid events.
Because of that, I didn't flag anything with a Fixes tag, since it's
seemingly been this way forever.

RFC->V2:
 - Patch 1
   - Added a message when registering a device without a request callback
   - Changed the "if(!callback) return" to "if(callback) do" layout
   - Removed "unlikely" from "if(callback)" logic
   - Clarified some wording in the device ops struct commentary
 - Patch 2
   - Added Conny's r-b

Eric Farman (2):
  vfio-mdev: Wire in a request handler for mdev parent
  vfio-ccw: Wire in the request callback

 drivers/s390/cio/vfio_ccw_ops.c     | 26 ++++++++++++++++++++++++++
 drivers/s390/cio/vfio_ccw_private.h |  4 ++++
 drivers/vfio/mdev/mdev_core.c       |  4 ++++
 drivers/vfio/mdev/vfio_mdev.c       | 10 ++++++++++
 include/linux/mdev.h                |  4 ++++
 include/uapi/linux/vfio.h           |  1 +
 6 files changed, 49 insertions(+)
```
#### [RFC PATCH 00/27] vDPA software assisted live migration
##### From: =?utf-8?q?Eugenio_P=C3=A9rez?= <eperezma@redhat.com>

```c
From patchwork Fri Nov 20 18:50:38 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Eugenio Perez Martin <eperezma@redhat.com>
X-Patchwork-Id: 11921937
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-10.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A0FF8C56201
	for <kvm@archiver.kernel.org>; Fri, 20 Nov 2020 18:52:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 519D022464
	for <kvm@archiver.kernel.org>; Fri, 20 Nov 2020 18:52:00 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="cdswnbE9"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731994AbgKTSvi (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 20 Nov 2020 13:51:38 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:35244 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1731937AbgKTSvi (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 20 Nov 2020 13:51:38 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1605898296;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=/Sb8SkhHSx+YyTW1MXsUsqQRkW1t3AvbZ30ip8xfmcY=;
        b=cdswnbE9DhbYFCNDaG1rHdLz9ODZymz6QE97f2ynL105y4WtHjS23CSX/Y9ycL4MevJ088
        jAHUNXuOB/jIf4CytYD6KR2GCcKXeyyxbZPgl4k9LuSwzcbRLit50uCGYGNjRTMi1a6lb2
        1YUXMW9ndCBH9DjrHRigWTiqUVB+nXk=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-401-vIcMi6b8OYG6iQ1GEt0oHw-1; Fri, 20 Nov 2020 13:51:32 -0500
X-MC-Unique: vIcMi6b8OYG6iQ1GEt0oHw-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id DF47263CC8;
        Fri, 20 Nov 2020 18:51:22 +0000 (UTC)
Received: from eperezma.remote.csb (ovpn-112-88.ams2.redhat.com
 [10.36.112.88])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 38DB65C1D5;
        Fri, 20 Nov 2020 18:51:07 +0000 (UTC)
From: =?utf-8?q?Eugenio_P=C3=A9rez?= <eperezma@redhat.com>
To: qemu-devel@nongnu.org
Cc: Lars Ganrot <lars.ganrot@gmail.com>,
        virtualization@lists.linux-foundation.org,
        Salil Mehta <mehta.salil.lnk@gmail.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Liran Alon <liralon@gmail.com>,
        Rob Miller <rob.miller@broadcom.com>,
        Max Gurtovoy <maxgu14@gmail.com>,
        Alex Barba <alex.barba@broadcom.com>,
        Stefan Hajnoczi <stefanha@redhat.com>,
        Jim Harford <jim.harford@broadcom.com>,
        Jason Wang <jasowang@redhat.com>,
        Harpreet Singh Anand <hanand@xilinx.com>,
        Christophe Fontaine <cfontain@redhat.com>,
        vm <vmireyno@marvell.com>, Daniel Daly <dandaly0@gmail.com>,
        Michael Lilja <ml@napatech.com>,
        Stefano Garzarella <sgarzare@redhat.com>,
        Nitin Shrivastav <nitin.shrivastav@broadcom.com>,
        Lee Ballard <ballle98@gmail.com>,
        Dmytro Kazantsev <dmytro.kazantsev@gmail.com>,
        Juan Quintela <quintela@redhat.com>, kvm@vger.kernel.org,
        Howard Cai <howard.cai@gmail.com>,
        Xiao W Wang <xiao.w.wang@intel.com>,
        Sean Mooney <smooney@redhat.com>,
        Parav Pandit <parav@mellanox.com>,
        Eli Cohen <eli@mellanox.com>, Siwei Liu <loseweigh@gmail.com>,
        Stephen Finucane <stephenfin@redhat.com>
Subject: [RFC PATCH 00/27] vDPA software assisted live migration
Date: Fri, 20 Nov 2020 19:50:38 +0100
Message-Id: <20201120185105.279030-1-eperezma@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series enable vDPA software assisted live migration for vhost-net
devices. This is a new method of vhost devices migration: Instead of
relay on vDPA device's dirty logging capability, SW assisted LM
intercepts dataplane, forwarding the descriptors between VM and device.

In this migration mode, qemu offers a new vring to the device to
read and write into, and disable vhost notifiers, processing guest and
vhost notifications in qemu. On used buffer relay, qemu will mark the
dirty memory as with plain virtio-net devices. This way, devices does
not need to have dirty page logging capability.

This series is a POC doing SW LM for vhost-net devices, which already
have dirty page logging capabilities. None of the changes have actual
effect with current devices until last two patches (26 and 27) are
applied, but they can be rebased on top of any other. These checks the
device to meet all requirements, and disable vhost-net devices logging
so migration goes through SW LM. This last patch is not meant to be
applied in the final revision, it is in the series just for testing
purposes.

For use SW assisted LM these vhost-net devices need to be instantiated:
* With IOMMU (iommu_platform=on,ats=on)
* Without event_idx (event_idx=off)

Just the notification forwarding (with no descriptor relay) can be
achieved with patches 7 and 9, and starting migration. Partial applies
between 13 and 24 will not work while migrating on source, and patch
25 is needed for the destination to resume network activity.

It is based on the ideas of DPDK SW assisted LM, in the series of
DPDK's https://patchwork.dpdk.org/cover/48370/ .

Comments are welcome.

Thanks!

Eugenio Pérez (27):
  vhost: Add vhost_dev_can_log
  vhost: Add device callback in vhost_migration_log
  vhost: Move log resize/put to vhost_dev_set_log
  vhost: add vhost_kernel_set_vring_enable
  vhost: Add hdev->dev.sw_lm_vq_handler
  virtio: Add virtio_queue_get_used_notify_split
  vhost: Route guest->host notification through qemu
  vhost: Add a flag for software assisted Live Migration
  vhost: Route host->guest notification through qemu
  vhost: Allocate shadow vring
  virtio: const-ify all virtio_tswap* functions
  virtio: Add virtio_queue_full
  vhost: Send buffers to device
  virtio: Remove virtio_queue_get_used_notify_split
  vhost: Do not invalidate signalled used
  virtio: Expose virtqueue_alloc_element
  vhost: add vhost_vring_set_notification_rcu
  vhost: add vhost_vring_poll_rcu
  vhost: add vhost_vring_get_buf_rcu
  vhost: Return used buffers
  vhost: Add vhost_virtqueue_memory_unmap
  vhost: Add vhost_virtqueue_memory_map
  vhost: unmap qemu's shadow virtqueues on sw live migration
  vhost: iommu changes
  vhost: Do not commit vhost used idx on vhost_virtqueue_stop
  vhost: Add vhost_hdev_can_sw_lm
  vhost: forbid vhost devices logging

 hw/virtio/vhost-sw-lm-ring.h      |  39 +++
 include/hw/virtio/vhost.h         |   5 +
 include/hw/virtio/virtio-access.h |   8 +-
 include/hw/virtio/virtio.h        |   4 +
 hw/net/virtio-net.c               |  39 ++-
 hw/virtio/vhost-backend.c         |  29 ++
 hw/virtio/vhost-sw-lm-ring.c      | 268 +++++++++++++++++++
 hw/virtio/vhost.c                 | 431 +++++++++++++++++++++++++-----
 hw/virtio/virtio.c                |  18 +-
 hw/virtio/meson.build             |   2 +-
 10 files changed, 758 insertions(+), 85 deletions(-)
 create mode 100644 hw/virtio/vhost-sw-lm-ring.h
 create mode 100644 hw/virtio/vhost-sw-lm-ring.c
```
