

#### [PATCH RFC 0/6] KVM: x86: Interrupt-based mechanism for async_pf
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
From patchwork Wed Apr 29 09:36:28 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11516465
Return-Path: <SRS0=yWZj=6N=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9B53813B2
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 29 Apr 2020 09:36:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7A2C820775
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 29 Apr 2020 09:36:46 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="aygvl/kr"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726546AbgD2Jgp (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 29 Apr 2020 05:36:45 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:41450 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726423AbgD2Jgp (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 29 Apr 2020 05:36:45 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1588153003;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=YqX8OZzl6x7aX0kjunMJb9gmMH7onlmLMnzmB4yGxPk=;
        b=aygvl/kroBBB0RwENTEq7jl463YT7Iy81hVIeMijVrbQGM6DK25rjiNBppmmXZeG4ANyeA
        UM7RiDNSwzek4Dy+t/5lJpSshc7F2oHtf6N6QaiPYe3ACNRULfIe4vHN5wpFyCz9pCxR30
        LGEwW04nTr/NjRTj/nQW7zG5fTIy66M=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-314-cP-seqnhMPWc9DjOrXQJKg-1; Wed, 29 Apr 2020 05:36:42 -0400
X-MC-Unique: cP-seqnhMPWc9DjOrXQJKg-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 5B728835B41;
        Wed, 29 Apr 2020 09:36:40 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.193.242])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 54E4F5D9C9;
        Wed, 29 Apr 2020 09:36:36 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: x86@kernel.org, kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>,
        Andy Lutomirski <luto@kernel.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        "H. Peter Anvin" <hpa@zytor.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>
Subject: [PATCH RFC 0/6] KVM: x86: Interrupt-based mechanism for async_pf
 'page present' notifications
Date: Wed, 29 Apr 2020 11:36:28 +0200
Message-Id: <20200429093634.1514902-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Concerns were expressed around (ab)using #PF for KVM's async_pf mechanism,
it seems that re-using #PF exception for a PV mechanism wasn't a great
idea after all. The Grand Plan is to switch to using e.g. #VE for 'page
not present' events and normal APIC interrupts for 'page present' events.
This RFC does the later.

Please let me know what you think about the idea in general and the
selected approach in particular.

Vitaly Kuznetsov (6):
  Revert "KVM: async_pf: Fix #DF due to inject "Page not Present" and
    "Page Ready" exceptions simultaneously"
  KVM: x86: extend struct kvm_vcpu_pv_apf_data with token info
  KVM: x86: interrupt based APF page-ready event delivery
  KVM: x86: acknowledgment mechanism for async pf page ready
    notifications
  KVM: x86: announce KVM_FEATURE_ASYNC_PF_INT
  KVM: x86: Switch KVM guest to using interrupts for page ready APF
    delivery

 Documentation/virt/kvm/cpuid.rst     |   6 ++
 Documentation/virt/kvm/msr.rst       |  52 +++++++++++--
 arch/x86/entry/entry_32.S            |   5 ++
 arch/x86/entry/entry_64.S            |   5 ++
 arch/x86/include/asm/hardirq.h       |   3 +
 arch/x86/include/asm/irq_vectors.h   |   6 +-
 arch/x86/include/asm/kvm_host.h      |   5 +-
 arch/x86/include/asm/kvm_para.h      |   6 ++
 arch/x86/include/uapi/asm/kvm_para.h |  11 ++-
 arch/x86/kernel/irq.c                |   9 +++
 arch/x86/kernel/kvm.c                |  42 +++++++++++
 arch/x86/kvm/cpuid.c                 |   3 +-
 arch/x86/kvm/x86.c                   | 107 +++++++++++++++++++++------
 include/uapi/linux/kvm.h             |   1 +
 14 files changed, 228 insertions(+), 33 deletions(-)
```
#### [PATCH v3 00/10] s390x: smp: Improve smp code part 2
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
From patchwork Wed Apr 29 14:35:08 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11517685
Return-Path: <SRS0=yWZj=6N=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 17D6092C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 29 Apr 2020 14:35:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 08E6E2074A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 29 Apr 2020 14:35:33 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726898AbgD2Ofc (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 29 Apr 2020 10:35:32 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:22372 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726348AbgD2Ofb (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 29 Apr 2020 10:35:31 -0400
Received: from pps.filterd (m0098393.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 03TEWDYR047130;
        Wed, 29 Apr 2020 10:35:31 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 30me46av8r-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 29 Apr 2020 10:35:30 -0400
Received: from m0098393.ppops.net (m0098393.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 03TEXKSk051293;
        Wed, 29 Apr 2020 10:35:30 -0400
Received: from ppma04ams.nl.ibm.com (63.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.99])
        by mx0a-001b2d01.pphosted.com with ESMTP id 30me46av72-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 29 Apr 2020 10:35:30 -0400
Received: from pps.filterd (ppma04ams.nl.ibm.com [127.0.0.1])
        by ppma04ams.nl.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 03TEUZp5019028;
        Wed, 29 Apr 2020 14:35:27 GMT
Received: from b06cxnps3074.portsmouth.uk.ibm.com
 (d06relay09.portsmouth.uk.ibm.com [9.149.109.194])
        by ppma04ams.nl.ibm.com with ESMTP id 30mcu70n48-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 29 Apr 2020 14:35:27 +0000
Received: from d06av22.portsmouth.uk.ibm.com (d06av22.portsmouth.uk.ibm.com
 [9.149.105.58])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 03TEZPCX7733510
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 29 Apr 2020 14:35:25 GMT
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 4708F4C040;
        Wed, 29 Apr 2020 14:35:25 +0000 (GMT)
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 94ED54C044;
        Wed, 29 Apr 2020 14:35:24 +0000 (GMT)
Received: from linux01.pok.stglabs.ibm.com (unknown [9.114.17.81])
        by d06av22.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Wed, 29 Apr 2020 14:35:24 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: thuth@redhat.com, linux-s390@vger.kernel.org, david@redhat.com,
        borntraeger@de.ibm.com, cohuck@redhat.com
Subject: [PATCH v3 00/10] s390x: smp: Improve smp code part 2
Date: Wed, 29 Apr 2020 10:35:08 -0400
Message-Id: <20200429143518.1360468-1-frankja@linux.ibm.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.676
 definitions=2020-04-29_05:2020-04-29,2020-04-29 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 adultscore=0 bulkscore=0
 lowpriorityscore=0 priorityscore=1501 mlxscore=0 impostorscore=0
 spamscore=0 malwarescore=0 mlxlogscore=760 clxscore=1015 phishscore=0
 suspectscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2003020000 definitions=main-2004290117
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Let's continue cleaning up the smp test and smp related functions.

We add:
   * Test for external/emergency calls after reset
   * Test SIGP restart while running
   * SIGP stop and store status while running
   * CR testing on reset

We fix:
   * Proper check for sigp completion
   * smp_cpu_setup_state() loop and return address in r14

v3:
	* Added some rev-bys and acks
	* Add a workaround for stop and store status
	* Beautified cr checking with loop

v2:
	* Added some rev-bys and acks
	* Explicitly stop and start cpu before hot restart test

GIT: https://github.com/frankjaa/kvm-unit-tests/tree/smp_cleanup2

Janosch Frank (10):
  s390x: smp: Test all CRs on initial reset
  s390x: smp: Dirty fpc before initial reset test
  s390x: smp: Test stop and store status on a running and stopped cpu
  s390x: smp: Test local interrupts after cpu reset
  s390x: smp: Loop if secondary cpu returns into cpu setup again
  s390x: smp: Remove unneeded cpu loops
  s390x: smp: Use full PSW to bringup new cpu
  s390x: smp: Wait for sigp completion
  s390x: smp: Add restart when running test
  s390x: Fix library constant definitions

 lib/s390x/asm/arch_def.h |   8 ++--
 lib/s390x/smp.c          |  11 +++++
 lib/s390x/smp.h          |   1 +
 s390x/cstart64.S         |   5 +-
 s390x/smp.c              | 101 +++++++++++++++++++++++++++++++++++----
 5 files changed, 112 insertions(+), 14 deletions(-)
```
