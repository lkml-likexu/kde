

#### [PATCH v4 0/5] Refactor handling flow of KVM_SET_CPUID*
##### From: Xiaoyao Li <xiaoyao.li@intel.com>

```c
From patchwork Thu Jul  9 04:34:21 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xiaoyao Li <xiaoyao.li@intel.com>
X-Patchwork-Id: 11653315
Return-Path: <SRS0=D4j5=AU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3AA3814DD
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Jul 2020 04:34:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2A2BF2070E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Jul 2020 04:34:35 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726251AbgGIEeb (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 9 Jul 2020 00:34:31 -0400
Received: from mga14.intel.com ([192.55.52.115]:10037 "EHLO mga14.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726064AbgGIEeb (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 9 Jul 2020 00:34:31 -0400
IronPort-SDR: 
 Gj3ggboWHNZSWnv8pg+XXRCNCpFh4iQeOuD3sxXAzoiJonQoyML6bsyAN46uWl6QIVKD52MVIL
 ynmX0WHudFUw==
X-IronPort-AV: E=McAfee;i="6000,8403,9676"; a="147011556"
X-IronPort-AV: E=Sophos;i="5.75,330,1589266800";
   d="scan'208";a="147011556"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga002.jf.intel.com ([10.7.209.21])
  by fmsmga103.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 08 Jul 2020 21:34:30 -0700
IronPort-SDR: 
 ekUZALqdUvV1jJuznU5aco34cHuYOTYFD60rr7O6jG2ufY3GB3FktmuLqvaODwL00QGujbarF2
 HYPmkHnL+xDg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,330,1589266800";
   d="scan'208";a="297942856"
Received: from lxy-dell.sh.intel.com ([10.239.159.21])
  by orsmga002.jf.intel.com with ESMTP; 08 Jul 2020 21:34:27 -0700
From: Xiaoyao Li <xiaoyao.li@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Xiaoyao Li <xiaoyao.li@intel.com>
Subject: [PATCH v4 0/5] Refactor handling flow of KVM_SET_CPUID*
Date: Thu,  9 Jul 2020 12:34:21 +0800
Message-Id: <20200709043426.92712-1-xiaoyao.li@intel.com>
X-Mailer: git-send-email 2.18.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

4 Patches of v3 has been queued into kvm/queue branch. This v4 contains
the rest to refactor the flow of KVM_SET_CPUID* as:

1. cpuid check: check if userspace provides legal CPUID settings;

2. cpuid update: Update userspace provided CPUID settings. It currently
   only contains kvm_update_cpuid_runtime, which updates special CPUID
   bits based on the vcpu state, e.g., OSXSAVE, OSPKE. In the future, we
   can re-introduce kvm_update_cpuid() if KVM needs to force on/off some
   bits.

3. update vcpu states: Update vcpu states/settings based on the final updated
   CPUID settings. 

v4:
 - remove 4 queued patches
 - rebased to kvm/queue: c16ced9cc67a "x86/kvm/vmx: Use native read/write_cr2()"
 - fix one bug in v3 to call kvfree(cpuid_entries) in kvm_vcpu_ioctl_set_cpuid()
 - rename "update_vcpu_model" to "vcpu_after_set_cpuid" [Paolo]	
 - Add a new patch to extrace kvm_update_cpuid_runtime()

v3:
https://lkml.kernel.org/r/20200708065054.19713-1-xiaoyao.li@intel.com
 - Add a note in KVM api doc to state the previous CPUID configuration
   is not reliable if current KVM_SET_CPUID* fails [Jim]
 - Adjust Patch 2 to reduce code churn [Sean]
 - Commit message refine to add more justification [Sean]
 - Add a new patch 7

v2:
https://lkml.kernel.org/r/20200623115816.24132-1-xiaoyao.li@intel.com
 - rebase to kvm/queue: a037ff353ba6 ("Merge branch 'kvm-master' into HEAD")
 - change the name of kvm_update_state_based_on_cpuid() to
   kvm_update_vcpu_model() [Sean]
 - Add patch 5 to rename kvm_x86_ops.cpuid_date() to
   kvm_x86_ops.update_vcpu_model()

v1:
https://lkml.kernel.org/r/20200529085545.29242-1-xiaoyao.li@intel.com

Xiaoyao Li (5):
  KVM: x86: Introduce kvm_check_cpuid()
  KVM: x86: Extract kvm_update_cpuid_runtime() from kvm_update_cpuid()
  KVM: x86: Rename kvm_update_cpuid() to kvm_vcpu_after_set_cpuid()
  KVM: x86: Rename cpuid_update() callback to vcpu_after_set_cpuid()
  KVM: x86: Move kvm_x86_ops.vcpu_after_set_cpuid() into
    kvm_vcpu_after_set_cpuid()

 arch/x86/include/asm/kvm_host.h |  2 +-
 arch/x86/kvm/cpuid.c            | 99 +++++++++++++++++++++------------
 arch/x86/kvm/cpuid.h            |  2 +-
 arch/x86/kvm/lapic.c            |  2 +-
 arch/x86/kvm/svm/svm.c          |  4 +-
 arch/x86/kvm/vmx/nested.c       |  3 +-
 arch/x86/kvm/vmx/vmx.c          |  4 +-
 arch/x86/kvm/x86.c              | 10 ++--
 8 files changed, 76 insertions(+), 50 deletions(-)
```
#### [kvm-unit-tests PATCH v11 0/9] s390x: Testing the Channel Subsystem
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
From patchwork Thu Jul  9 08:07:39 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 11653709
Return-Path: <SRS0=D4j5=AU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4876960D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Jul 2020 08:07:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3A5D92070E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Jul 2020 08:07:58 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726502AbgGIIH5 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 9 Jul 2020 04:07:57 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:23764 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726124AbgGIIH4 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 9 Jul 2020 04:07:56 -0400
Received: from pps.filterd (m0098409.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 069834iB121001;
        Thu, 9 Jul 2020 04:07:55 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 325s241bmu-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 09 Jul 2020 04:07:55 -0400
Received: from m0098409.ppops.net (m0098409.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 06983ENV121675;
        Thu, 9 Jul 2020 04:07:54 -0400
Received: from ppma06ams.nl.ibm.com (66.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.102])
        by mx0a-001b2d01.pphosted.com with ESMTP id 325s241bkp-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 09 Jul 2020 04:07:54 -0400
Received: from pps.filterd (ppma06ams.nl.ibm.com [127.0.0.1])
        by ppma06ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 0698707K025598;
        Thu, 9 Jul 2020 08:07:52 GMT
Received: from b06cxnps4076.portsmouth.uk.ibm.com
 (d06relay13.portsmouth.uk.ibm.com [9.149.109.198])
        by ppma06ams.nl.ibm.com with ESMTP id 325k0crkct-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 09 Jul 2020 08:07:52 +0000
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06cxnps4076.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 06987oFb58327262
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 9 Jul 2020 08:07:50 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 1A1EEA405B;
        Thu,  9 Jul 2020 08:07:50 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 98F9EA4054;
        Thu,  9 Jul 2020 08:07:49 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.34.67])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Thu,  9 Jul 2020 08:07:49 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, frankja@linux.ibm.com,
        david@redhat.com, thuth@redhat.com, cohuck@redhat.com,
        drjones@redhat.com
Subject: [kvm-unit-tests PATCH v11 0/9] s390x: Testing the Channel Subsystem
 I/O
Date: Thu,  9 Jul 2020 10:07:39 +0200
Message-Id: <1594282068-11054-1-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-07-09_04:2020-07-08,2020-07-09 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 clxscore=1015 mlxlogscore=999
 bulkscore=0 impostorscore=0 phishscore=0 lowpriorityscore=0 mlxscore=0
 spamscore=0 suspectscore=1 adultscore=0 priorityscore=1501 malwarescore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2006250000
 definitions=main-2007090059
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi All,

This new respin of the series add modifications to
- patches 8: s390x: css: msch, enable test
- and mostly to patch 9: s390x: css: ssch/tsch with sense and interrupt
Other patches did not change.

Recall:

Goal of the series is to have a framework to test Channel-Subsystem I/O with
QEMU/KVM.
  
To be able to support interrupt for CSS I/O and for SCLP we need to modify
the interrupt framework to allow re-entrant interruptions.
  
We add a registration for IRQ callbacks to the test program to define its own
interrupt handler. We need to do special work under interrupt like acknowledging
the interrupt.
  
This series presents three tests:
- Enumeration:
        The CSS is enumerated using the STSCH instruction recursively on all
        potentially existing channels.
        Keeping the first channel found as a reference for future use.
        Checks STSCH
 
- Enable:
        If the enumeration succeeded the tests enables the reference
        channel with MSCH and verifies with STSCH that the channel is
        effectively enabled, retrying a predefined count on failure
	to enable the channel
        Checks MSCH       
 
- Sense:
        If the channel is enabled this test sends a SENSE_ID command
        to the reference channel, analyzing the answer and expecting
        the Control unit type being 0x3832, a.k.a. virtio-ccw.
        Checks SSCH(READ) and IO-IRQ

Note:
- The following 5 patches are general usage and may be pulled first:
  s390x: saving regs for interrupts
  s390x: I/O interrupt registration
  s390x: export the clock get_clock_ms() utility
  s390x: clock and delays calculations
  s390x: define function to wait for interrupt

- These 4 patches are really I/O oriented:
  s390x: Library resources for CSS tests
  s390x: css: stsch, enumeration test
  s390x: css: msch, enable test
  s390x: css: ssch/tsch with sense and interrupt

Regards,
Pierre

Pierre Morel (9):
  s390x: saving regs for interrupts
  s390x: I/O interrupt registration
  s390x: export the clock get_clock_ms() utility
  s390x: clock and delays calculations
  s390x: define function to wait for interrupt
  s390x: Library resources for CSS tests
  s390x: css: stsch, enumeration test
  s390x: css: msch, enable test
  s390x: css: ssch/tsch with sense and interrupt

 lib/s390x/asm/arch_def.h |  14 ++
 lib/s390x/asm/time.h     |  50 ++++++
 lib/s390x/css.h          | 293 +++++++++++++++++++++++++++++++++++
 lib/s390x/css_dump.c     | 152 ++++++++++++++++++
 lib/s390x/css_lib.c      | 325 +++++++++++++++++++++++++++++++++++++++
 lib/s390x/interrupt.c    |  23 ++-
 lib/s390x/interrupt.h    |   8 +
 s390x/Makefile           |   3 +
 s390x/css.c              | 150 ++++++++++++++++++
 s390x/cstart64.S         |  41 ++++-
 s390x/intercept.c        |  11 +-
 s390x/unittests.cfg      |   4 +
 12 files changed, 1061 insertions(+), 13 deletions(-)
 create mode 100644 lib/s390x/asm/time.h
 create mode 100644 lib/s390x/css.h
 create mode 100644 lib/s390x/css_dump.c
 create mode 100644 lib/s390x/css_lib.c
 create mode 100644 lib/s390x/interrupt.h
 create mode 100644 s390x/css.c
```
#### [PATCH v5 0/2] s390: virtio: let arch validate VIRTIO features
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
From patchwork Thu Jul  9 08:39:17 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 11653789
Return-Path: <SRS0=D4j5=AU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BFCA614DD
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Jul 2020 08:39:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B4130207C4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Jul 2020 08:39:52 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726289AbgGIIjv (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 9 Jul 2020 04:39:51 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:49138 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726247AbgGIIju (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 9 Jul 2020 04:39:50 -0400
Received: from pps.filterd (m0098414.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 0698ab4u111432;
        Thu, 9 Jul 2020 04:39:44 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 325r2caevj-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 09 Jul 2020 04:39:44 -0400
Received: from m0098414.ppops.net (m0098414.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 0698akDJ112286;
        Thu, 9 Jul 2020 04:39:43 -0400
Received: from ppma03ams.nl.ibm.com (62.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.98])
        by mx0b-001b2d01.pphosted.com with ESMTP id 325r2caerd-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 09 Jul 2020 04:39:42 -0400
Received: from pps.filterd (ppma03ams.nl.ibm.com [127.0.0.1])
        by ppma03ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 0698a3Dt031648;
        Thu, 9 Jul 2020 08:39:24 GMT
Received: from b06avi18878370.portsmouth.uk.ibm.com
 (b06avi18878370.portsmouth.uk.ibm.com [9.149.26.194])
        by ppma03ams.nl.ibm.com with ESMTP id 325k1vgm6b-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 09 Jul 2020 08:39:24 +0000
Received: from d06av24.portsmouth.uk.ibm.com (mk.ibm.com [9.149.105.60])
        by b06avi18878370.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 0698dLdR56164776
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 9 Jul 2020 08:39:21 GMT
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 8869D42056;
        Thu,  9 Jul 2020 08:39:21 +0000 (GMT)
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id A6F5642061;
        Thu,  9 Jul 2020 08:39:20 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.34.67])
        by d06av24.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Thu,  9 Jul 2020 08:39:20 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: linux-kernel@vger.kernel.org
Cc: pasic@linux.ibm.com, borntraeger@de.ibm.com, frankja@linux.ibm.com,
        mst@redhat.com, jasowang@redhat.com, cohuck@redhat.com,
        kvm@vger.kernel.org, linux-s390@vger.kernel.org,
        virtualization@lists.linux-foundation.org, thomas.lendacky@amd.com,
        david@gibson.dropbear.id.au, linuxram@us.ibm.com,
        heiko.carstens@de.ibm.com, gor@linux.ibm.com
Subject: [PATCH v5 0/2] s390: virtio: let arch validate VIRTIO features
Date: Thu,  9 Jul 2020 10:39:17 +0200
Message-Id: <1594283959-13742-1-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-07-09_04:2020-07-08,2020-07-09 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxscore=0 bulkscore=0
 priorityscore=1501 impostorscore=0 spamscore=0 phishscore=0 adultscore=0
 lowpriorityscore=0 malwarescore=0 clxscore=1015 mlxlogscore=975
 suspectscore=1 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2007090064
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all,

The goal of the series is to give a chance to the architecture
to validate VIRTIO device features.

in this respin:

1) I kept removed the ack from Jason as I reworked the patch
   @Jason, the nature and goal of the patch did not really changed
           please can I get back your acked-by with these changes?

2) I suppressed the unnecessary verbosity of the architecture
   specific patch

3) put back the arch specific code inside arch/s390/mm/init.c
   after offline discussion with Christian.

Regards,
Pierre

Pierre Morel (2):
  virtio: let arch validate VIRTIO features
  s390: virtio: PV needs VIRTIO I/O device protection

 arch/s390/mm/init.c           | 27 +++++++++++++++++++++++++++
 drivers/virtio/virtio.c       | 19 +++++++++++++++++++
 include/linux/virtio_config.h |  1 +
 3 files changed, 47 insertions(+)
```
#### [PATCH v3 0/9] KVM: nSVM: fixes for CR3/MMU switch upon nested guest
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
From patchwork Thu Jul  9 14:53:49 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11654529
Return-Path: <SRS0=D4j5=AU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A3150618
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Jul 2020 14:54:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 88E482077D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Jul 2020 14:54:12 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="dgbeH73g"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726923AbgGIOyJ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 9 Jul 2020 10:54:09 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:37129 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726371AbgGIOyI (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 9 Jul 2020 10:54:08 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1594306447;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=h49iUghddx6q/28Q3GpO3NfUnwfKQascXywErp2c0+8=;
        b=dgbeH73gAd1T9wAGptB5rKeU3K6M3CytHccI1PACMX9SH9tvn+obROtUp/Z5GV5W5mQH2c
        d68AnLno8tkhD4OWL/yimLXvLIJOIjk+eXdcgVTSmuUazcvIRymACPhhJyeMTOhPB5Ky/r
        1XqgXrHrtnswlvrBO/EUtJbtmwFZG9I=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-92-lKFlz2d7PPKoAmMNMXLf5w-1; Thu, 09 Jul 2020 10:54:06 -0400
X-MC-Unique: lKFlz2d7PPKoAmMNMXLf5w-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id D8EC18005B0;
        Thu,  9 Jul 2020 14:54:04 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.195.35])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 01C1E6106A;
        Thu,  9 Jul 2020 14:53:59 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Junaid Shahid <junaids@google.com>,
        linux-kernel@vger.kernel.org
Subject: [PATCH v3 0/9] KVM: nSVM: fixes for CR3/MMU switch upon nested guest
 entry/exit
Date: Thu,  9 Jul 2020 16:53:49 +0200
Message-Id: <20200709145358.1560330-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is a successor of "[PATCH v2 0/3] KVM: nSVM: fix #TF from CR3 switch
when entering guest" and "[PATCH] KVM: x86: drop erroneous mmu_check_root()
from fast_pgd_switch()".

The snowball is growing fast! It all started with an intention to fix
the particular 'tripple fault' issue (now fixed by PATCH7) but now we
also get rid of unconditional kvm_mmu_reset_context() upon nested guest
entry/exit and make the code resemble nVMX. There is still a huge room
for further improvement (proper error propagation, removing unconditional
MMU sync/TLB flush,...) but at least we're making some progress.

Tested with kvm selftests/kvm-unit-tests and by running nested Hyper-V
on KVM. The series doesn't seem to introduce any new issues.

Vitaly Kuznetsov (9):
  KVM: nSVM: split kvm_init_shadow_npt_mmu() from kvm_init_shadow_mmu()
  KVM: nSVM: stop dereferencing vcpu->arch.mmu to get the context in
    kvm_init_shadow{,_npt}_mmu()
  KVM: nSVM: reset nested_run_pending upon nested_svm_vmrun_msrpm()
    failure
  KVM: nSVM: prepare to handle errors from enter_svm_guest_mode()
  KVM: nSVM: introduce nested_svm_load_cr3()
  KVM: nSVM: move kvm_set_cr3() after nested_svm_uninit_mmu_context()
  KVM: nSVM: implement nested_svm_load_cr3() and use it for host->guest
    switch
  KVM: nSVM: use nested_svm_load_cr3() on guest->host switch
  KVM: x86: drop superfluous mmu_check_root() from fast_pgd_switch()

 arch/x86/kvm/mmu.h        |   3 +-
 arch/x86/kvm/mmu/mmu.c    |  39 ++++++++++----
 arch/x86/kvm/svm/nested.c | 108 ++++++++++++++++++++++++++++----------
 arch/x86/kvm/svm/svm.c    |   6 ++-
 arch/x86/kvm/svm/svm.h    |   4 +-
 5 files changed, 116 insertions(+), 44 deletions(-)
```
