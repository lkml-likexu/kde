

#### [PATCH v4 0/3] ppc: Enable 2nd DAWR support on Power10
##### From: Ravi Bangoria <ravi.bangoria@linux.ibm.com>

```c
From patchwork Tue Apr  6 05:38:30 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ravi Bangoria <ravi.bangoria@linux.ibm.com>
X-Patchwork-Id: 12184177
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 8CF03C433ED
	for <kvm@archiver.kernel.org>; Tue,  6 Apr 2021 05:39:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 484A9611CC
	for <kvm@archiver.kernel.org>; Tue,  6 Apr 2021 05:39:43 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232967AbhDFFjt (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 6 Apr 2021 01:39:49 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:3646 "EHLO
        mx0b-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S231752AbhDFFjr (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 6 Apr 2021 01:39:47 -0400
Received: from pps.filterd (m0127361.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 1365X7nq109971;
        Tue, 6 Apr 2021 01:39:13 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : content-transfer-encoding : mime-version; s=pp1;
 bh=mLB47dibA3OSwGBj27SutkMchCWc8CvO8NZtioNOQnE=;
 b=No7jtEsfkiaD3kOpBYQVaRY9bsgpCo/UkTALth7izH0EtHs39yzBnL4TzF4Js9v0kJys
 9z/qVVevlUPeIY0TYfUoRCj8PXlQ4+bb3edx6+gvqEftImNhIrJpSBafon7AAmhmByxU
 Gnt139m8ICEZtwKxhJObCjFwxgj3wy/1o6IaYNxmL/oFLQI34knsSIFsyqSK9yQd5rCm
 ISCrF2z1Spr3SG1mkzNWjqU7rtAerK7e5vvQ2AgY82Kz4Wg2WBJ3KpuGYOsNGp07PbuL
 fQFtC1B49e4XZ78bwZURtAfMhCxNe7/9rE7086cu1Kt7sZHwQAJ4VeZcaAiDNQq69Q2/ Ew==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 37q5kxfs9x-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 06 Apr 2021 01:39:13 -0400
Received: from m0127361.ppops.net (m0127361.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 1365XcdS110950;
        Tue, 6 Apr 2021 01:39:12 -0400
Received: from ppma03ams.nl.ibm.com (62.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.98])
        by mx0a-001b2d01.pphosted.com with ESMTP id 37q5kxfs94-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 06 Apr 2021 01:39:12 -0400
Received: from pps.filterd (ppma03ams.nl.ibm.com [127.0.0.1])
        by ppma03ams.nl.ibm.com (8.16.0.43/8.16.0.43) with SMTP id
 1365amMl028874;
        Tue, 6 Apr 2021 05:39:10 GMT
Received: from b06cxnps3075.portsmouth.uk.ibm.com
 (d06relay10.portsmouth.uk.ibm.com [9.149.109.195])
        by ppma03ams.nl.ibm.com with ESMTP id 37q2y9hu2x-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 06 Apr 2021 05:39:10 +0000
Received: from d06av21.portsmouth.uk.ibm.com (d06av21.portsmouth.uk.ibm.com
 [9.149.105.232])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 1365d8OS30671212
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 6 Apr 2021 05:39:08 GMT
Received: from d06av21.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 4F18052052;
        Tue,  6 Apr 2021 05:39:08 +0000 (GMT)
Received: from bangoria.ibmuc.com (unknown [9.199.40.1])
        by d06av21.portsmouth.uk.ibm.com (Postfix) with ESMTP id C9E5E5204E;
        Tue,  6 Apr 2021 05:39:04 +0000 (GMT)
From: Ravi Bangoria <ravi.bangoria@linux.ibm.com>
To: paulus@samba.org, david@gibson.dropbear.id.au
Cc: ravi.bangoria@linux.ibm.com, mpe@ellerman.id.au, mikey@neuling.org,
        pbonzini@redhat.com, mst@redhat.com, clg@kaod.org,
        qemu-ppc@nongnu.org, qemu-devel@nongnu.org, kvm@vger.kernel.org,
        cohuck@redhat.com, groug@kaod.org
Subject: [PATCH v4 0/3] ppc: Enable 2nd DAWR support on Power10
Date: Tue,  6 Apr 2021 11:08:30 +0530
Message-Id: <20210406053833.282907-1-ravi.bangoria@linux.ibm.com>
X-Mailer: git-send-email 2.30.2
X-TM-AS-GCONF: 00
X-Proofpoint-ORIG-GUID: MCYFSoaxnKv4EDLXyT9u0_WvNJiHeose
X-Proofpoint-GUID: dKqAIj6i_Wb8ivCLaz-8NPPIr987M65k
X-Proofpoint-UnRewURL: 0 URL was un-rewritten
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.761
 definitions=2021-04-06_01:2021-04-01,2021-04-06 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 impostorscore=0
 mlxlogscore=999 suspectscore=0 phishscore=0 lowpriorityscore=0
 malwarescore=0 mlxscore=0 priorityscore=1501 spamscore=0 clxscore=1015
 bulkscore=0 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2104030000 definitions=main-2104060037
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series enables 2nd DAWR support on p10 qemu guest. 2nd
DAWR is new watchpoint added in Power10 processor. Kernel/kvm
patches are already in[1]. Watchpoint on powerpc TCG guest is
not supported and thus 2nd DAWR is not enabled for TCG mode.

Patches apply fine on qemu/master branch (11577d85b1a6).

v3: https://lore.kernel.org/r/20210330095350.36309-1-ravi.bangoria@linux.ibm.com
v3->v4:
  - spapr_dt_pa_features(): POWER10 processor is compatible with 3.0
    (PCR_COMPAT_3_00). No need to ppc_check_compat(3_10) for now as
    ppc_check_compati(3_00) will also be true. ppc_check_compat(3_10)
    can be added while introducing pa_features_310 in future.
  - Use error_append_hint() for hints. Also add ERRP_GUARD().
  - Add kvmppc_set_cap_dawr1() stub function for CONFIG_KVM=n.

v2: https://lore.kernel.org/r/20210329041906.213991-1-ravi.bangoria@linux.ibm.com
v2->v3:
  - Don't introduce pa_features_310[], instead, reuse pa_features_300[]
    for 3.1 guests, as there is no difference between initial values of
    them atm.
  - Call gen_spr_book3s_310_dbg() from init_proc_POWER10() instead of
    init_proc_POWER8(). Also, Don't call gen_spr_book3s_207_dbg() from
    gen_spr_book3s_310_dbg() as init_proc_POWER10() already calls it.

v1: https://lore.kernel.org/r/20200723104220.314671-1-ravi.bangoria@linux.ibm.com
[Apologies for long gap]
v1->v2:
  - Introduce machine capability cap-dawr1 to enable/disable
    the feature. By default, 2nd DAWR is OFF for guests even
    when host kvm supports it. User has to manually enable it
    with -machine cap-dawr1=on if he wishes to use it.
  - Split the header file changes into separate patch. (Sync
    headers from v5.12-rc3)

[1] https://git.kernel.org/torvalds/c/bd1de1a0e6eff

Ravi Bangoria (3):
  Linux headers: update from 5.12-rc3
  ppc: Rename current DAWR macros and variables
  ppc: Enable 2nd DAWR support on p10

 hw/ppc/spapr.c                                |  7 +-
 hw/ppc/spapr_caps.c                           | 32 +++++++
 include/hw/ppc/spapr.h                        |  8 +-
 include/standard-headers/drm/drm_fourcc.h     | 23 ++++-
 include/standard-headers/linux/input.h        |  2 +-
 .../standard-headers/rdma/vmw_pvrdma-abi.h    |  7 ++
 linux-headers/asm-generic/unistd.h            |  4 +-
 linux-headers/asm-mips/unistd_n32.h           |  1 +
 linux-headers/asm-mips/unistd_n64.h           |  1 +
 linux-headers/asm-mips/unistd_o32.h           |  1 +
 linux-headers/asm-powerpc/kvm.h               |  2 +
 linux-headers/asm-powerpc/unistd_32.h         |  1 +
 linux-headers/asm-powerpc/unistd_64.h         |  1 +
 linux-headers/asm-s390/unistd_32.h            |  1 +
 linux-headers/asm-s390/unistd_64.h            |  1 +
 linux-headers/asm-x86/kvm.h                   |  1 +
 linux-headers/asm-x86/unistd_32.h             |  1 +
 linux-headers/asm-x86/unistd_64.h             |  1 +
 linux-headers/asm-x86/unistd_x32.h            |  1 +
 linux-headers/linux/kvm.h                     | 89 +++++++++++++++++++
 linux-headers/linux/vfio.h                    | 27 ++++++
 target/ppc/cpu.h                              |  6 +-
 target/ppc/kvm.c                              | 12 +++
 target/ppc/kvm_ppc.h                          | 12 +++
 target/ppc/translate_init.c.inc               | 19 +++-
 25 files changed, 250 insertions(+), 11 deletions(-)
```
#### [kvm-unit-tests PATCH v3 00/16] s390x: Testing SSCH,
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
From patchwork Tue Apr  6 07:40:37 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 12184393
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 67454C433B4
	for <kvm@archiver.kernel.org>; Tue,  6 Apr 2021 07:41:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3861F613B8
	for <kvm@archiver.kernel.org>; Tue,  6 Apr 2021 07:41:03 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S235458AbhDFHlJ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 6 Apr 2021 03:41:09 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:21052 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S232661AbhDFHlH (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 6 Apr 2021 03:41:07 -0400
Received: from pps.filterd (m0098419.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 1367YBFb028858
        for <kvm@vger.kernel.org>; Tue, 6 Apr 2021 03:41:00 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id; s=pp1;
 bh=ORSeLVk4Dk5V5xnEUjoRNmgfUYEaJiDykhMSCJhQPOw=;
 b=Eaei06gi3mrZv5spDsMhXQA6u9ZVTgNBqzun8WAt520xAitFGY2YDWTmoKkkGG6IXW9R
 M1P5UsyyFikpN348Z3meFFVKdPyZRUvkHA88HYap2aZ9V7Y6OtdG+bVJKWRMkfxUcNPq
 1IUE7TtHGc9i0/kybT+fqTac4+4iR5esW9Nipn8pT4+CCNz/78CBlwf9H4gwaUX+Fri5
 9TZ3RAd8hTJnI9w1Jxqrh4YHachLDEbwx620P86fLF4QQXJoqYUdu0fnSWvGFB5kgR8d
 fNubrSh3SYSsR3Iia5RvSo8T2ISrO8OYFoCgWax96m+rRQCepNMPxZF1nTPOazxBVEIb gg==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 37q5tyk6hw-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT)
        for <kvm@vger.kernel.org>; Tue, 06 Apr 2021 03:41:00 -0400
Received: from m0098419.ppops.net (m0098419.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 1367aW3A035682
        for <kvm@vger.kernel.org>; Tue, 6 Apr 2021 03:40:59 -0400
Received: from ppma04ams.nl.ibm.com (63.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.99])
        by mx0b-001b2d01.pphosted.com with ESMTP id 37q5tyk6ha-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 06 Apr 2021 03:40:59 -0400
Received: from pps.filterd (ppma04ams.nl.ibm.com [127.0.0.1])
        by ppma04ams.nl.ibm.com (8.16.0.43/8.16.0.43) with SMTP id
 1367Wktx015585;
        Tue, 6 Apr 2021 07:40:57 GMT
Received: from b06cxnps3074.portsmouth.uk.ibm.com
 (d06relay09.portsmouth.uk.ibm.com [9.149.109.194])
        by ppma04ams.nl.ibm.com with ESMTP id 37q2n2sx7y-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 06 Apr 2021 07:40:57 +0000
Received: from d06av22.portsmouth.uk.ibm.com (d06av22.portsmouth.uk.ibm.com
 [9.149.105.58])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 1367etRP30212482
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 6 Apr 2021 07:40:55 GMT
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id F20334C040;
        Tue,  6 Apr 2021 07:40:54 +0000 (GMT)
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id A4F904C046;
        Tue,  6 Apr 2021 07:40:54 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.42.152])
        by d06av22.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue,  6 Apr 2021 07:40:54 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: frankja@linux.ibm.com, david@redhat.com, thuth@redhat.com,
        cohuck@redhat.com, imbrenda@linux.ibm.com
Subject: [kvm-unit-tests PATCH v3 00/16] s390x: Testing SSCH,
 CSCH and HSCH for errors
Date: Tue,  6 Apr 2021 09:40:37 +0200
Message-Id: <1617694853-6881-1-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
X-TM-AS-GCONF: 00
X-Proofpoint-ORIG-GUID: n0fYmORlGM2hDnBA3-YBgyuatmzCX7KC
X-Proofpoint-GUID: UUKfQ57iZ0YTNjS7yMq4bzasOQNmyVHv
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.761
 definitions=2021-04-06_01:2021-04-01,2021-04-06 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 malwarescore=0 clxscore=1015
 impostorscore=0 mlxscore=0 mlxlogscore=999 priorityscore=1501 adultscore=0
 phishscore=0 bulkscore=0 lowpriorityscore=0 spamscore=0 suspectscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2104030000
 definitions=main-2104060050
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The goal of this series is to test some of the I/O instructions,
SSCH, CSCH and HSCH for errors like invalid parameters, addressing,
timing etc.
We can not test the sending of an instruction before the last instruction
has been proceeded by QEMU due to the QEMU serialization but we can 
check the behavior of an instruction if it is started before the status
of the last instruction is read.

To do this we first separate the waiting for the interruption and the
checking of the IRB and enable the subchannel without an I/O ISC to
avoid interruptions at this subchannel and second, we add an argument
to the routine in charge to check the IRB representing the expected
SCSW control field of the IRB.

We also need several other enhancements to the testing environment:

- definitions for the SCSW control bits
- a new function to disable a subchannel
- a macro to simplify skiping tests when no device is present
  (I know the warning about return in macro, can we accept it?)

In the new tests we assume that all the test preparation is working and
use asserts for all function for which we do not expect a failure.

regards,
Pierre

PS: Sorry, I needed to modify patches 4 and 5 for which I already had RB or AB.
    I removed them even I hope you will agree with my modifications.


Pierre Morel (16):
  s390x: lib: css: disabling a subchannel
  s390x: lib: css: SCSW bit definitions
  s390x: css: simplify skipping tests on no device
  s390x: lib: css: separate wait for IRQ and check I/O completion
  s390x: lib: css: add SCSW ctrl expectations to check I/O completion
  s390x: lib: css: checking I/O errors
  s390x: css: testing ssch errors
  s390x: css: ssch check for cpa zero
  s390x: css: ssch with mis aligned ORB
  s390x: css: ssch checking addressing errors
  s390x: css: No support for MIDAW
  s390x: css: Check ORB reserved bits
  s390x: css: checking for CSS extensions
  s390x: css: issuing SSCH when the channel is status pending
  s390x: css: testing halt subchannel
  s390x: css: testing clear subchannel

 lib/s390x/css.h     |  42 ++++-
 lib/s390x/css_lib.c | 138 ++++++++++++--
 s390x/css.c         | 425 +++++++++++++++++++++++++++++++++++++++++---
 s390x/unittests.cfg |   8 +-
 4 files changed, 565 insertions(+), 48 deletions(-)
```
#### [PATCH v3 0/4] KVM: cpuid: fix KVM_GET_EMULATED_CPUID implementation
##### From: Emanuele Giuseppe Esposito <eesposit@redhat.com>

```c
From patchwork Tue Apr  6 08:26:38 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Emanuele Giuseppe Esposito <eesposit@redhat.com>
X-Patchwork-Id: 12184503
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 83B5CC43461
	for <kvm@archiver.kernel.org>; Tue,  6 Apr 2021 08:26:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 52241613BE
	for <kvm@archiver.kernel.org>; Tue,  6 Apr 2021 08:26:55 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S240123AbhDFI1B (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 6 Apr 2021 04:27:01 -0400
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:36507 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S240119AbhDFI1A (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 6 Apr 2021 04:27:00 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1617697612;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=70z9esMo2B49i245lsCrvtnfLxOMXAVc5hPbm8uKJwE=;
        b=DYV1A+dzrLPLwJktCfKlyZ52LcycmX9f/m/nJBFZVfreVGyHcY8Wvc916wC4YqRc4TT7MW
        1PtHcLbxrW3TplaaNc9bJgQf9vLVQ3JYXIyHLw+98Z6KxuKxZdlsvovj6Yts6sngRMyEq4
        Ui5uGK3t2T6LZG0vTMniXe8BEsy/Xkw=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-376-35f28TuHNUqwLkCHV8l62Q-1; Tue, 06 Apr 2021 04:26:51 -0400
X-MC-Unique: 35f28TuHNUqwLkCHV8l62Q-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 7723C81425A;
        Tue,  6 Apr 2021 08:26:49 +0000 (UTC)
Received: from localhost.localdomain.com (ovpn-114-253.ams2.redhat.com
 [10.36.114.253])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 3531C5D9E3;
        Tue,  6 Apr 2021 08:26:43 +0000 (UTC)
From: Emanuele Giuseppe Esposito <eesposit@redhat.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Jonathan Corbet <corbet@lwn.net>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Emanuele Giuseppe Esposito <eesposit@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        "H. Peter Anvin" <hpa@zytor.com>, Shuah Khan <shuah@kernel.org>,
        Alexander Graf <graf@amazon.com>,
        Andrew Jones <drjones@redhat.com>, linux-doc@vger.kernel.org,
        linux-kernel@vger.kernel.org, linux-kselftest@vger.kernel.org
Subject: [PATCH v3 0/4] KVM: cpuid: fix KVM_GET_EMULATED_CPUID implementation
Date: Tue,  6 Apr 2021 10:26:38 +0200
Message-Id: <20210406082642.20115-1-eesposit@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series aims to clarify the behavior of the KVM_GET_EMULATED_CPUID
ioctl, and fix a corner case where -E2BIG is returned when
the nent field of struct kvm_cpuid2 is matching the amount of
emulated entries that kvm returns.

Patch 1 proposes the nent field fix to cpuid.c,
patch 2 updates the ioctl documentation accordingly and
patches 3 and 4 extend the x86_64/get_cpuid_test.c selftest to check
the intended behavior of KVM_GET_EMULATED_CPUID.

Signed-off-by: Emanuele Giuseppe Esposito <eesposit@redhat.com>
---
v3:
- clearer commit message and problem explanation 
- pre-initialize the stack variable 'entry' in __do_cpuid_func_emulated
so that the various eax/ebx/ecx are initialized if not set by func.


Emanuele Giuseppe Esposito (4):
  KVM: x86: Fix a spurious -E2BIG in KVM_GET_EMULATED_CPUID
  Documentation: KVM: update KVM_GET_EMULATED_CPUID ioctl description
  selftests: add kvm_get_emulated_cpuid to processor.h
  selftests: KVM: extend get_cpuid_test to include
    KVM_GET_EMULATED_CPUID

 Documentation/virt/kvm/api.rst                | 10 +--
 arch/x86/kvm/cpuid.c                          | 33 ++++---
 .../selftests/kvm/include/x86_64/processor.h  |  1 +
 .../selftests/kvm/lib/x86_64/processor.c      | 33 +++++++
 .../selftests/kvm/x86_64/get_cpuid_test.c     | 90 ++++++++++++++++++-
 5 files changed, 142 insertions(+), 25 deletions(-)
```
#### [PATCH v15 00/13] s390/vfio-ap: dynamic configuration support
##### From: Tony Krowiak <akrowiak@linux.ibm.com>

```c
From patchwork Tue Apr  6 15:31:09 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tony Krowiak <akrowiak@linux.ibm.com>
X-Patchwork-Id: 12185475
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 5D392C43460
	for <kvm@archiver.kernel.org>; Tue,  6 Apr 2021 15:31:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2E7D261222
	for <kvm@archiver.kernel.org>; Tue,  6 Apr 2021 15:31:41 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1345682AbhDFPbs (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 6 Apr 2021 11:31:48 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:40796 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S229741AbhDFPbr (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 6 Apr 2021 11:31:47 -0400
Received: from pps.filterd (m0187473.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 136FDdVg121788;
        Tue, 6 Apr 2021 11:31:37 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=6hNEY2Tr2fdxqG7vpmIgzG83En6mrVB2bLFV7rxkzXg=;
 b=rs8bNWCkQjYhAw69Fvc2dRtgPJ2pj/uGGu1krAHo0S08Y7QfM3qPcNTT5UbQ8tYcv0cb
 ESQ2NVfHOAm4rgwjLp2lUWMkb/oILQxfFDd5JPI0Y3j0G++oIPnkOS8TB2s7tdR2ZfPq
 3iZl2lTzhUqNVzIwH5uDCbLmuWFUHMbirbnkilxzd0vK6PnZofhewj6m0nhyZeQxVMpO
 jDWEpbdiFz3u9X3ycKMA2Cnyn1XgAJPxyI/3W7ZZQOctBrngrKYJLQDtEefF5I84LfSa
 AtK1X9UJQqPB/PihdEUDb6I+igAZFDPdddZ9tPJX349S5fhp86F4/fAGLGVZ8HBLPz/r Ug==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 37q5exs1qb-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 06 Apr 2021 11:31:37 -0400
Received: from m0187473.ppops.net (m0187473.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 136FDtd6122881;
        Tue, 6 Apr 2021 11:31:37 -0400
Received: from ppma01wdc.us.ibm.com (fd.55.37a9.ip4.static.sl-reverse.com
 [169.55.85.253])
        by mx0a-001b2d01.pphosted.com with ESMTP id 37q5exs1ph-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 06 Apr 2021 11:31:37 -0400
Received: from pps.filterd (ppma01wdc.us.ibm.com [127.0.0.1])
        by ppma01wdc.us.ibm.com (8.16.0.43/8.16.0.43) with SMTP id
 136FM2eD002554;
        Tue, 6 Apr 2021 15:31:35 GMT
Received: from b03cxnp08028.gho.boulder.ibm.com
 (b03cxnp08028.gho.boulder.ibm.com [9.17.130.20])
        by ppma01wdc.us.ibm.com with ESMTP id 37q2q90r3c-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 06 Apr 2021 15:31:35 +0000
Received: from b03ledav005.gho.boulder.ibm.com
 (b03ledav005.gho.boulder.ibm.com [9.17.130.236])
        by b03cxnp08028.gho.boulder.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 136FVW6v18219382
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 6 Apr 2021 15:31:32 GMT
Received: from b03ledav005.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 7B720BE056;
        Tue,  6 Apr 2021 15:31:32 +0000 (GMT)
Received: from b03ledav005.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id C57CBBE04F;
        Tue,  6 Apr 2021 15:31:30 +0000 (GMT)
Received: from cpe-172-100-182-241.stny.res.rr.com.com (unknown
 [9.85.175.110])
        by b03ledav005.gho.boulder.ibm.com (Postfix) with ESMTP;
        Tue,  6 Apr 2021 15:31:30 +0000 (GMT)
From: Tony Krowiak <akrowiak@linux.ibm.com>
To: linux-s390@vger.kernel.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org
Cc: jjherne@linux.ibm.com, freude@linux.ibm.com,
        borntraeger@de.ibm.com, cohuck@redhat.com, mjrosato@linux.ibm.com,
        pasic@linux.ibm.com, alex.williamson@redhat.com,
        kwankhede@nvidia.com, fiuczy@linux.ibm.com, frankja@linux.ibm.com,
        david@redhat.com, hca@linux.ibm.com, gor@linux.ibm.com,
        Tony Krowiak <akrowiak@linux.ibm.com>
Subject: [PATCH v15 00/13] s390/vfio-ap: dynamic configuration support
Date: Tue,  6 Apr 2021 11:31:09 -0400
Message-Id: <20210406153122.22874-1-akrowiak@linux.ibm.com>
X-Mailer: git-send-email 2.21.3
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-GUID: yZrWpi2DZhNehvQ34WDV8kK0sw-zXEwT
X-Proofpoint-ORIG-GUID: QViAz2-yfuXs7NJd5smzikqhR9rkd2Fk
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.761
 definitions=2021-04-06_04:2021-04-01,2021-04-06 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 bulkscore=0 impostorscore=0
 mlxlogscore=999 priorityscore=1501 phishscore=0 spamscore=0 adultscore=0
 clxscore=1015 suspectscore=0 malwarescore=0 mlxscore=0 lowpriorityscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2104030000
 definitions=main-2104060104
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Note: Patch 1, "s390/vfio-ap: fix circular lockdep when setting/clearing
      crypto masks" does not belong to this series. It is currently
      being merged and is included here because it is a pre-req for
      this series.

      Ignore checkpatch warnings regarding unknown commit IDs, those
      appears to be made in error.

The current design for AP pass-through does not support making dynamic
changes to the AP matrix of a running guest resulting in a few
deficiencies this patch series is intended to mitigate:

1. Adapters, domains and control domains can not be added to or removed
   from a running guest. In order to modify a guest's AP configuration,
   the guest must be terminated; only then can AP resources be assigned
   to or unassigned from the guest's matrix mdev. The new AP
   configuration becomes available to the guest when it is subsequently
   restarted.

2. The AP bus's /sys/bus/ap/apmask and /sys/bus/ap/aqmask interfaces can
   be modified by a root user without any restrictions. A change to
   either mask can result in AP queue devices being unbound from the
   vfio_ap device driver and bound to a zcrypt device driver even if a
   guest is using the queues, thus giving the host access to the guest's
   private crypto data and vice versa.

3. The APQNs derived from the Cartesian product of the APIDs of the
   adapters and APQIs of the domains assigned to a matrix mdev must
   reference an AP queue device bound to the vfio_ap device driver. The
   AP architecture allows assignment of AP resources that are not
   available to the system, so this artificial restriction is not
   compliant with the architecture.

4. The AP configuration profile can be dynamically changed for the linux
   host after a KVM guest is started. For example, a new domain can be
   dynamically added to the configuration profile via the SE or an HMC
   connected to a DPM enabled lpar. Likewise, AP adapters can be
   dynamically configured (online state) and deconfigured (standby state)
   using the SE, an SCLP command or an HMC connected to a DPM enabled
   lpar. This can result in inadvertent sharing of AP queues between the
   guest and host.

5. A root user can manually unbind an AP queue device representing a
   queue in use by a KVM guest via the vfio_ap device driver's sysfs
   unbind attribute. In this case, the guest will be using a queue that
   is not bound to the driver which violates the device model.

This patch series introduces the following changes to the current design
to alleviate the shortcomings described above as well as to implement
more of the AP architecture:

1. A root user will be prevented from making edits to the AP bus's
   /sys/bus/ap/apmask or /sys/bus/ap/aqmask if the change would transfer
   ownership of an APQN from the vfio_ap device driver to a zcrypt driver
   while the APQN is assigned to a matrix mdev.

2. Allow a root user to hot plug/unplug AP adapters, domains and control
   domains for a KVM guest using the matrix mdev via its sysfs
   assign/unassign attributes.

4. Allow assignment of an AP adapter or domain to a matrix mdev even if
   it results in assignment of an APQN that does not reference an AP
   queue device bound to the vfio_ap device driver, as long as the APQN
   is not reserved for use by the default zcrypt drivers (also known as
   over-provisioning of AP resources). Allowing over-provisioning of AP
   resources better models the architecture which does not preclude
   assigning AP resources that are not yet available in the system. Such
   APQNs, however, will not be assigned to the guest using the matrix
   mdev; only APQNs referencing AP queue devices bound to the vfio_ap
   device driver will actually get assigned to the guest.

5. Handle dynamic changes to the AP device model.

1. Rationale for changes to AP bus's apmask/aqmask interfaces:
----------------------------------------------------------
Due to the extremely sensitive nature of cryptographic data, it is
imperative that great care be taken to ensure that such data is secured.
Allowing a root user, either inadvertently or maliciously, to configure
these masks such that a queue is shared between the host and a guest is
not only avoidable, it is advisable. It was suggested that this scenario
is better handled in user space with management software, but that does
not preclude a malicious administrator from using the sysfs interfaces
to gain access to a guest's crypto data. It was also suggested that this
scenario could be avoided by taking access to the adapter away from the
guest and zeroing out the queues prior to the vfio_ap driver releasing the
device; however, stealing an adapter in use from a guest as a by-product
of an operation is bad and will likely cause problems for the guest
unnecessarily. It was decided that the most effective solution with the
least number of negative side effects is to prevent the situation at the
source.

2. Rationale for hot plug/unplug using matrix mdev sysfs interfaces:
----------------------------------------------------------------
Allowing a user to hot plug/unplug AP resources using the matrix mdev
sysfs interfaces circumvents the need to terminate the guest in order to
modify its AP configuration. Allowing dynamic configuration makes
reconfiguring a guest's AP matrix much less disruptive.

3. Rationale for allowing over-provisioning of AP resources:
-----------------------------------------------------------
Allowing assignment of AP resources to a matrix mdev and ultimately to a
guest better models the AP architecture. The architecture does not
preclude assignment of unavailable AP resources. If a queue subsequently
becomes available while a guest using the matrix mdev to which its APQN
is assigned, the guest will be given access to it. If an APQN
is dynamically unassigned from the underlying host system, it will
automatically become unavailable to the guest.


Change log v14-v15:
------------------
* Fixed bug: Unlink mdev from all queues when the mdev is removed.

Change log v13-v14:
------------------
* Removed patch "s390/vfio-ap: clean up vfio_ap resources when KVM pointer
  invalidated". The patch is not necessary because that is handled
  with patch 1 of this series (currently being merged) and
  commit f21916ec4826 ("s390/vfio-ap: clean up vfio_ap resources when KVM pointer invalidated")

* Removed patch "s390/vfio-ap: No need to disable IRQ after queue reset",
  that has already been merged with
  commit 6c12a6384e0c ("s390/vfio-ap: No need to disable IRQ after queue reset").

* Initialize the vfio_ap_queue object before setting the drvdata in
  the probe callback

* Change return code from mdev assignment interfaces to -EAGAIN when
  mutex_trylock fails for the mdev lock.

* Restored missing hunk from v12 in the group notifier callback, but
  had to restore it to the vfio_ap_mdev_set_kvm() function due to
  changes made via merged commits noted above.

* Reordered patch "s390/vfio-ap: sysfs attribute to display the
  guest's matrix" to follow the patches that modify the shadow
  APCB.

* Remove queue from APCB before resetting it in the remove
  callback.

* Split the vfio_ap_mdev_unlink_queue() function into two
  functions: one to remove the link from the matrix mdev to
  the queue; and, one to remove the link from the queue to the matrix
  mdev.

* Removed the QCI call and the shadow_apcb memcpy from the
  vfio_ap_mdev_filter_apcb() function.

* Do not clear shadow_apcb when there are not adapters or domains
  assigned.

* Moved filtering code from "s390/vfio-ap: allow hot plug/unplug of
  AP resources using mdev device" into its own patch.

* Squashed the two patches comprising the handling of changes to
  the AP configuration into one patch.

* Added code to delay hot plug during probe until the AP bus scan
  is complete if the APID of the queue is in the bitmap of adapters
  currently being added to the AP configuration.

Change log v12-v13:
------------------
* Combined patches 12/13 from previous series into one patch

* Moved all changes for linking queues and mdevs into a single patch

* Re-ordered some patches to aid in review

* Using mutex_trylock() function in adapter/domain assignment functions
  to avoid potential deadlock condition with in_use callback

* Using filtering function for refreshing the guest's APCB for all events
  that change the APCB: assign/unassign adapters, domains, control domains;
  bind/unbind of queue devices; and, changes to the host AP configuration.

Change log v11-v12:
------------------
* Moved matrix device lock to protect group notifier callback

* Split the 'No need to disable IRQ after queue reset' patch into
  multiple patches for easier review (move probe/remove callback
  functions and remove disable IRQ after queue reset)

* Added code to decrement reference count for KVM in group notifier
  callback

* Using mutex_trylock() in functions implementing the sysfs assign_adapter
  and assign_domain as well as the in_use callback to avoid deadlock
  between the AP bus's ap_perms mutex and the matrix device lock used by
  vfio_ap driver.

* The sysfs guest_matrix attribute of the vfio_ap mdev will now display
  the shadow APCB regardless of whether a guest is using the mdev or not

* Replaced vfio_ap mdev filtering function with a function that initializes
  the guest's APCB by filtering the vfio_ap mdev by APID.

* No longer using filtering function during adapter/domain assignment
  to/from the vfio_ap mdev; replaced with new hot plug/unplug
  adapter/domain functions.

* No longer using filtering function during bind/unbind; replaced with
  hot plug/unplug queue functions.

* No longer using filtering function for bulk assignment of new adapters
  and domains in on_scan_complete callback; replaced with new hot plug
  functions.


Change log v10-v11:
------------------
* The matrix mdev's configuration is not filtered by APID so that if any
  APQN assigned to the mdev is not bound to the vfio_ap device driver,
  the adapter will not get plugged into the KVM guest on startup, or when
  a new adapter is assigned to the mdev.

* Replaced patch 8 by squashing patches 8 (filtering patch) and 15 (handle
  probe/remove).

* Added a patch 1 to remove disable IRQ after a reset because the reset
  already disables a queue.

* Now using filtering code to update the KVM guest's matrix when
  notified that AP bus scan has completed.

* Fixed issue with probe/remove not inititiated by a configuration change
  occurring within a config change.


Change log v9-v10:
-----------------
* Updated the documentation in vfio-ap.rst to include information about the
  AP dynamic configuration support

Change log v8-v9:
----------------
* Fixed errors flagged by the kernel test robot

* Fixed issue with guest losing queues when a new queue is probed due to
  manual bind operation.

Change log v7-v8:
----------------
* Now logging a message when an attempt to reserve APQNs for the zcrypt
  drivers will result in taking a queue away from a KVM guest to provide
  the sysadmin a way to ascertain why the sysfs operation failed.

* Created locked and unlocked versions of the ap_parse_mask_str() function.

* Now using new interface provided by an AP bus patch -
  s390/ap: introduce new ap function ap_get_qdev() - to retrieve
  struct ap_queue representing an AP queue device. This patch is not a
  part of this series but is a prerequisite for this series.

Change log v6-v7:
----------------
* Added callbacks to AP bus:
  - on_config_changed: Notifies implementing drivers that
    the AP configuration has changed since last AP device scan.
  - on_scan_complete: Notifies implementing drivers that the device scan
    has completed.
  - implemented on_config_changed and on_scan_complete callbacks for
    vfio_ap device driver.
  - updated vfio_ap device driver's probe and remove callbacks to handle
    dynamic changes to the AP device model.
* Added code to filter APQNs when assigning AP resources to a KVM guest's
  CRYCB

Change log v5-v6:
----------------
* Fixed a bug in ap_bus.c introduced with patch 2/7 of the v5
  series. Harald Freudenberer pointed out that the mutex lock
  for ap_perms_mutex in the apmask_store and aqmask_store functions
  was not being freed.

* Removed patch 6/7 which added logging to the vfio_ap driver
  to expedite acceptance of this series. The logging will be introduced
  with a separate patch series to allow more time to explore options
  such as DBF logging vs. tracepoints.

* Added 3 patches related to ensuring that APQNs that do not reference
  AP queue devices bound to the vfio_ap device driver are not assigned
  to the guest CRYCB:

  Patch 4: Filter CRYCB bits for unavailable queue devices
  Patch 5: sysfs attribute to display the guest CRYCB
  Patch 6: update guest CRYCB in vfio_ap probe and remove callbacks

* Added a patch (Patch 9) to version the vfio_ap module.

* Reshuffled patches to allow the in_use callback implementation to
  invoke the vfio_ap_mdev_verify_no_sharing() function introduced in
  patch 2.

Change log v4-v5:
----------------
* Added a patch to provide kernel s390dbf debug logs for VFIO AP

Change log v3->v4:
-----------------
* Restored patches preventing root user from changing ownership of
  APQNs from zcrypt drivers to the vfio_ap driver if the APQN is
  assigned to an mdev.

* No longer enforcing requirement restricting guest access to
  queues represented by a queue device bound to the vfio_ap
  device driver.

* Removed shadow CRYCB and now directly updating the guest CRYCB
  from the matrix mdev's matrix.

* Rebased the patch series on top of 'vfio: ap: AP Queue Interrupt
  Control' patches.

* Disabled bind/unbind sysfs interfaces for vfio_ap driver

Change log v2->v3:
-----------------
* Allow guest access to an AP queue only if the queue is bound to
  the vfio_ap device driver.

* Removed the patch to test CRYCB masks before taking the vCPUs
  out of SIE. Now checking the shadow CRYCB in the vfio_ap driver.

Change log v1->v2:
-----------------
* Removed patches preventing root user from unbinding AP queues from
  the vfio_ap device driver
* Introduced a shadow CRYCB in the vfio_ap driver to manage dynamic
  changes to the AP guest configuration due to root user interventions
  or hardware anomalies.

Tony Krowiak (13):
  s390/vfio-ap: fix circular lockdep when setting/clearing crypto masks
  s390/vfio-ap: use new AP bus interface to search for queue devices
  s390/vfio-ap: move probe and remove callbacks to vfio_ap_ops.c
  s390/vfio-ap: manage link between queue struct and matrix mdev
  s390/vfio-ap: introduce shadow APCB
  s390/vfio-ap: refresh guest's APCB by filtering APQNs assigned to mdev
  s390/vfio-ap: allow assignment of unavailable AP queues to mdev device
  s390/vfio-ap: allow hot plug/unplug of AP resources using mdev device
  s390/zcrypt: driver callback to indicate resource in use
  s390/vfio-ap: implement in-use callback for vfio_ap driver
  s390/vfio-ap: sysfs attribute to display the guest's matrix
  s390/zcrypt: notify drivers on config changed and scan complete
    callbacks
  s390/vfio-ap: update docs to include dynamic config support

 Documentation/s390/vfio-ap.rst        |  383 ++++++---
 drivers/s390/crypto/ap_bus.c          |  249 +++++-
 drivers/s390/crypto/ap_bus.h          |   16 +
 drivers/s390/crypto/vfio_ap_drv.c     |   46 +-
 drivers/s390/crypto/vfio_ap_ops.c     | 1107 ++++++++++++++++++-------
 drivers/s390/crypto/vfio_ap_private.h |   29 +-
 6 files changed, 1364 insertions(+), 466 deletions(-)
---
2.21.3
```
#### [PATCH 0/4] KVM: SVM: A fix and cleanups for vmcb tracking
##### From: Sean Christopherson <seanjc@google.com>

```c
From patchwork Tue Apr  6 17:18:07 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12185591
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 16C26C433B4
	for <kvm@archiver.kernel.org>; Tue,  6 Apr 2021 17:18:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CC7636113E
	for <kvm@archiver.kernel.org>; Tue,  6 Apr 2021 17:18:16 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S244375AbhDFRSX (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 6 Apr 2021 13:18:23 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:52444 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S235380AbhDFRSW (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 6 Apr 2021 13:18:22 -0400
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id CEE09C06174A
        for <kvm@vger.kernel.org>; Tue,  6 Apr 2021 10:18:14 -0700 (PDT)
Received: by mail-yb1-xb4a.google.com with SMTP id n67so5872942ybf.11
        for <kvm@vger.kernel.org>; Tue, 06 Apr 2021 10:18:14 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=2QVarXwWjfAQ6D128GVf+WS0ZBaSudzPxzhf4vjW9Pc=;
        b=RzlDtRxBkXkLYNyInRsipPHgQI+EUlsswpmhz7RqwzjyAtRO5C9CPPWpjLTorw4/ag
         QpOPm5hG55P2oRNMWitz44qrKmz5bBmdnZcjjhOiCu0faVVLgZHbOgEJrPbqxWsMEbMb
         QqSythYmiBIiBAZFEAGg/yAmaus7Ei0C2t6lzEEMJaJ7iHVCuSARwIMkHma3v9FNSodX
         BwPrZHyrtwxeiQtWy4EsDaZUrWgW9IuU6Nu6vFaV89xfak/0Cw2wmVsntgf1DBMUogHO
         Jpd7y2sjb5Wo8FWjMKWzkp9YKCbPtgrZgodM4ie2JdCgVJN+PwTjgxaKdVquyvBD8aWN
         x0Eg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:reply-to:date:message-id:mime-version:subject
         :from:to:cc;
        bh=2QVarXwWjfAQ6D128GVf+WS0ZBaSudzPxzhf4vjW9Pc=;
        b=ZRdTm8SBaMYlpthf982/GR10tphxzQs2lydxGw9qWaUZe+Ca6uSPI46ucv+dbRAUAD
         R1qxAGnXvN7hC5SZn6yW44D3HVODF6gsd9mJKKKEfbYKlB+cfoksA/n2TFVt6UTJonfl
         q/tQmYDoQJgA5DXB8Q3dX5a7pvl4QTCF9q0k5UbTJlSUPGxH9RGNSOG8RQxVd+oSwe7Q
         sdHUcfuFnXUBI3Ws30vlmYvXE9833iDGAo5OeCzKnZh+ymesfejhf+OVpR4Atpw1SINJ
         vFg5hwIRh4HqBjkr0+t9P70V9o75m2q1DcCc3KiB/0mrGL/ZClTBOvYpNHhQuVxss0HK
         iOKw==
X-Gm-Message-State: AOAM5325bwkPBEfz0seXkPDHUtc6AuM4fQUCRV7AzoW2KEO6qjeICsF0
        sMgbzpUiG+K1oc25uuIEdve104zffLk=
X-Google-Smtp-Source: 
 ABdhPJx0P56RiIuz/a4w5YDahtfmvb66qqZAu2XOJs8zEcjT81edWLuMZVNWSJPcP+l7dOYSkfOiIIvC5DU=
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:24a1:90fb:182b:777c])
 (user=seanjc job=sendgmr) by 2002:a25:1186:: with SMTP id
 128mr43976001ybr.59.1617729494045;
 Tue, 06 Apr 2021 10:18:14 -0700 (PDT)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Tue,  6 Apr 2021 10:18:07 -0700
Message-Id: <20210406171811.4043363-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.0.208.g409f899ff0-goog
Subject: [PATCH 0/4] KVM: SVM: A fix and cleanups for vmcb tracking
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Cathy Avery <cavery@redhat.com>,
        Maxim Levitsky <mlevitsk@redhat.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Belated code review for the vmcb changes that are queued for 5.13.

Sean Christopherson (4):
  KVM: SVM: Don't set current_vmcb->cpu when switching vmcb
  KVM: SVM: Drop vcpu_svm.vmcb_pa
  KVM: SVM: Add a comment to clarify what vcpu_svm.vmcb points at
  KVM: SVM: Enhance and clean up the vmcb tracking comment in
    pre_svm_run()

 arch/x86/kvm/svm/svm.c | 29 +++++++++++++----------------
 arch/x86/kvm/svm/svm.h |  2 +-
 2 files changed, 14 insertions(+), 17 deletions(-)
```
#### [PATCH v2 00/18] Make vfio_mdev type safe
##### From: Jason Gunthorpe <jgg@nvidia.com>

```c
From patchwork Tue Apr  6 19:40:23 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Gunthorpe <jgg@nvidia.com>
X-Patchwork-Id: 12185797
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-10.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,
	SPF_PASS autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 0A2D4C43603
	for <kvm@archiver.kernel.org>; Tue,  6 Apr 2021 19:40:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C913E613D8
	for <kvm@archiver.kernel.org>; Tue,  6 Apr 2021 19:40:51 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S239005AbhDFTk7 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 6 Apr 2021 15:40:59 -0400
Received: from mail-bn7nam10on2075.outbound.protection.outlook.com
 ([40.107.92.75]:17062
        "EHLO NAM10-BN7-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S233580AbhDFTk5 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 6 Apr 2021 15:40:57 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=UsJ+7OkDUhjgj4zWy3Euz8+sSyikrBHHbe+WVYst+FHYL+4/Zdm3Aqe7bDbYlgPrpv4Xi5GwVkZuLTxtI81GRgzC1DHOSi9MPe4iddyrL4V4Cxt+Dpo1/wxpy3ALsJPaUQQCqM/Xj4prsS6Sfr2bdqW9kQthyAPSfym1r0JSMZmmE3DVABz6az3EbXsSilPmr/5LumNHVDQzuOoQh8Rl6zvCSRcaUg0pPVITes9g2amGI5WdD6FPA37LRbDZpMsVgZ7gPMw0VK3u+oZWrlySSHAc6yCwHYwdBZJ691iTChQH0OvSbT4MFO49oej0wwT8p4/p/aOP+2RDNZXtP1ke7Q==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=L5QJOx/zrVYe49XoE9tKWpVTR7qDZ8I9IAiVsr/SsDw=;
 b=fLxSD83i9XH20DAejEPqjXw9bzQD4yPGavPYjrimfhWdsEpQezVclPBmPX+w/odr7xd0/JJiKMkDvPJtQuzhVmtf+DijexWEEO6NL7qAhw9FfwMDDvfBqewek5iWfYaXIoA9+oNbX+9BCtxNOFcgiipk07RsB4uSQO4sunXJjKD27P1HTn7kA5DJgWUuT13g0YBHDo8YuOCmS1LR9dBfp6S3K3RqoKuCTNJW212EUDA25DcYrD61MGQro8JboFO0djF95Du89X3C2V5QOXuCVwKlKVICt3oXRFnfg7CcWvjp1hlR1Zm7nozrdcAUtJjHPMaHcLLcv03tPDRjcjPn3A==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=nvidia.com; dmarc=pass action=none header.from=nvidia.com;
 dkim=pass header.d=nvidia.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=Nvidia.com;
 s=selector2;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=L5QJOx/zrVYe49XoE9tKWpVTR7qDZ8I9IAiVsr/SsDw=;
 b=QBPxdhjld7XNQEyNvUKAIIoYgOXNctI5jQm3sSpAx9RdmuAmvO3U6oSnv3Snerbqga8aiz6iw7O0bDthX7UlkxJMupHG/P2zMCO6GS6deKotmTNiCaS0k3ki8/AvLJuJDZD1y2kIB9mjLM3quw7h9kFfhWbEJmtjDiNGrTozXMSc2W44gei+05bJ8NT/I19vc/ImjwHnw0KkODdH8r4s2cFwQLMhZQWV8IBtmQhvdC/tnBU8pPxHVeQsUZtzQbz70ozbufpRN1SHqlZje98x2amCCxC3BYJQK7McoQkCbM8Tr3EYpLzMqv1egd1mvm3H39QQgmM3ef6di6XnUICPfg==
Authentication-Results: linux.ie; dkim=none (message not signed)
 header.d=none;linux.ie; dmarc=none action=none header.from=nvidia.com;
Received: from DM6PR12MB3834.namprd12.prod.outlook.com (2603:10b6:5:14a::12)
 by DM6PR12MB2859.namprd12.prod.outlook.com (2603:10b6:5:15d::29) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3999.27; Tue, 6 Apr
 2021 19:40:43 +0000
Received: from DM6PR12MB3834.namprd12.prod.outlook.com
 ([fe80::1c62:7fa3:617b:ab87]) by DM6PR12MB3834.namprd12.prod.outlook.com
 ([fe80::1c62:7fa3:617b:ab87%6]) with mapi id 15.20.3999.032; Tue, 6 Apr 2021
 19:40:43 +0000
From: Jason Gunthorpe <jgg@nvidia.com>
To: David Airlie <airlied@linux.ie>,
        Tony Krowiak <akrowiak@linux.ibm.com>,
        Alex Williamson <alex.williamson@redhat.com>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Jonathan Corbet <corbet@lwn.net>,
        Daniel Vetter <daniel@ffwll.ch>,
        dri-devel@lists.freedesktop.org,
        Eric Farman <farman@linux.ibm.com>,
        Harald Freudenberger <freude@linux.ibm.com>,
        Vasily Gorbik <gor@linux.ibm.com>,
        Heiko Carstens <hca@linux.ibm.com>,
        intel-gfx@lists.freedesktop.org,
        intel-gvt-dev@lists.freedesktop.org,
        Jani Nikula <jani.nikula@linux.intel.com>,
        Joonas Lahtinen <joonas.lahtinen@linux.intel.com>,
        kvm@vger.kernel.org, Kirti Wankhede <kwankhede@nvidia.com>,
        linux-doc@vger.kernel.org, linux-s390@vger.kernel.org,
        Peter Oberparleiter <oberpar@linux.ibm.com>,
        Halil Pasic <pasic@linux.ibm.com>,
        Pierre Morel <pmorel@linux.ibm.com>,
        Rodrigo Vivi <rodrigo.vivi@intel.com>,
        Vineeth Vijayan <vneethv@linux.ibm.com>,
        Zhenyu Wang <zhenyuw@linux.intel.com>,
        Zhi Wang <zhi.a.wang@intel.com>
Cc: "Raj, Ashok" <ashok.raj@intel.com>,
        Dong Jia Shi <bjsdjshi@linux.vnet.ibm.com>,
        Neo Jia <cjia@nvidia.com>, Cornelia Huck <cohuck@redhat.com>,
        Dan Williams <dan.j.williams@intel.com>,
        Christoph Hellwig <hch@lst.de>,
        Jike Song <jike.song@intel.com>,
        Kevin Tian <kevin.tian@intel.com>,
        Gerd Hoffmann <kraxel@redhat.com>,
        Leon Romanovsky <leonro@nvidia.com>,
        Max Gurtovoy <mgurtovoy@nvidia.com>,
        Tarun Gupta <targupta@nvidia.com>
Subject: [PATCH v2 00/18] Make vfio_mdev type safe
Date: Tue,  6 Apr 2021 16:40:23 -0300
Message-Id: <0-v2-d36939638fc6+d54-vfio2_jgg@nvidia.com>
X-Originating-IP: [142.162.115.133]
X-ClientProxiedBy: BL1PR13CA0140.namprd13.prod.outlook.com
 (2603:10b6:208:2bb::25) To DM6PR12MB3834.namprd12.prod.outlook.com
 (2603:10b6:5:14a::12)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from mlx.ziepe.ca (142.162.115.133) by
 BL1PR13CA0140.namprd13.prod.outlook.com (2603:10b6:208:2bb::25) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4020.9 via Frontend
 Transport; Tue, 6 Apr 2021 19:40:42 +0000
Received: from jgg by mlx with local (Exim 4.94)        (envelope-from
 <jgg@nvidia.com>)        id 1lTrZ3-001mWo-Qr; Tue, 06 Apr 2021 16:40:41 -0300
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: bec7c2a0-e204-451c-e1fb-08d8f933dd8b
X-MS-TrafficTypeDiagnostic: DM6PR12MB2859:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM6PR12MB2859F6715AA9EF832DBF7099C2769@DM6PR12MB2859.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:8882;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 +J8XcL0jLBVBZcI7QoBk6WfISVOpBInknxAWm4K2zSbekhMqrvF6HBrzhmBp1WizhtqZq+RlHMRp7tcRNqhWl3I1wSITQK58LUiJVxqOgTfVAc371BhICGiHFUZyMzShyFVmaxX5UzH+EdDjtDH4jbmRZfDI8KDJZtrc74ZVuIhU+aeIB/fm8jbgHzk6Mt1Xa9caKl3UtHZYkPO6LycMHCZJoxQsxb4T73fJIfdLx6gdTl/7AgTjMBmwCUv+iJSB293W7yIi+u1udy1os8Y/8r4pokyh9K+ti0r6+GgEWKZrIkn7KGD4pX5w6RxtR9d6KEzLlvTNdk+LHFYg1e85xQ3xssp8mOiKRnb3f4NtNaFaCVx2svj54SMKTO+t0z0qM6hoNKp29a2gG3uwFKfPZXQp37EfSG0OnOVZcJ6PQGmc1w3N7H5KONAR2Biplf3TAc0uVgwLch7XbbL587Tiss879odAt3+XqS0Phtl6UIT51llK0NboNEHQqo+FflkSa7/qPazjFGvn0BycQfWNwOn0jZUia/+KfL4maa9ToGa8Y9vVXrpd42J0VIAdj3h+feJqBVdxyEDhIvvfGBr8Gdo+fb4xQvsfuh8pK+rhm7kXDAx3hEZv5nojF8A84cmJOjeoIGQJmC1zoOaF6b6+Yu5JTmPS/8W0ZFbOnA3mZcnip03tMZ9emA12MmQnQ/qZEKm2uwyZ6HkwXD/gQahXRtCLSDaceFrvypcZ6U54nzzs4xwgHRYaCRtpQ9G5kXwh6tNMdBBpqfuII7/Un/l+Mg==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM6PR12MB3834.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(39860400002)(376002)(346002)(366004)(136003)(396003)(54906003)(86362001)(2616005)(26005)(8936002)(38100700001)(66476007)(426003)(7416002)(66946007)(5660300002)(316002)(36756003)(66556008)(2906002)(7406005)(6666004)(107886003)(83380400001)(186003)(921005)(478600001)(966005)(110136005)(4326008)(8676002)(9746002)(9786002)(4216001);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 XoyGl2ea3PznBZNPO3Y92GRSphjz8+E3Uo0qRGpiHGE+K5p3AieRH/PxvIYnDoMD1EXwonLSsBnXLOrFJk4IxwNVRMoPmHefijo+LcuFr4yFZWK4arLxyi/LgJYUh7iMBy14SObA3U0hVp1gVKi4ZJvXoeOkTeGZGQ01wUeqN5OIcwbEPFY8UnEU1uD4FIjRUkZbVlLG0XfqJIMN6sohFukKUr0YZnxFsDDJWZ9Z+nmfYsOszvApWbbtFfaOUcn6peeQtCVdJyllTz3yhqWOl9btWo7ERFhvycOq+Xb8v5GZS04PimH45b2U+APtrZMHneCmGCta/5jTtjRemjuk6DCxOHHyOf1+MhfOUk6AYokX5gcFRvjStQPHciuKAi5r9ZIVWB01LiZaKC8IwoyZ3iBDShQuX4I9eiZncLdO2qDPSNFPTFdD7E0dojiVM1qrf21CmPv00EXkt5YVl1vsBjK9hxe1kHnPxc5WqDUuhCKTLCWjWBYxK1edNQkc1mufi841ThJsxYdPEUowQ1Hp6oLitvI6w6TWLiz1TLSR5zfCS5QQ7gOMuXY0+4EpXaA81DUMOMCkJMFRlpwhC3QJx9bJtSM1zHevDBmYKHSsWng91kgP326MskoylJ14pxseTHOqVmWegDDs4dbxK5Jk3m+T755yLEWU9PKH2RKLSNwo703kOSLxHo1cCEtWVmf86n50eOs5NDvSE2nqEWXydDCv5h0T0mqbRZCcvni/om4lWuJA4hyxc5nWiHfxnJ+Qz60z5Rz7Exu7scTIkOKpSE+MNotgVNWkZZdlopvRYWa3v0q7DNsSU6hpRpdY3Jb9DRXh8pGkNPR4z9j1+QgxDaiFw3WOit52J++cjrcG7/pDmgt8ItruQsAAb0ZSGFP75+UrjAY9pfbQQaEGX14WvJGxf3tjxJUSxjNsDtZOuO6vDWtjii6MXttZHW4UbPUdo6g7hrfqs81io8k9Deas33E4icucG2QOC9X0PzrU6HBhI7efQghywa5c2D433iYddPop8BHn2I0KFsziRWUdddQhHSWj6IbhZgWVBPUGPbEKECXXT/4pANQvm/N/IplCE5JwQNKV2EqBkxTzv5ghVR3CuWYUouiwo7c2qEl5YypDVvlDONieude0wNagWyr41jyNdrUw5xoL70a6kK4gvjkIag2hvgaS2H4y0BkSLXNb6tXB6BaW9XCkSUWM6vRiqjtWU73LDvQlws2733VQTjk41LNBo/V8UBQ5ABKZIA795HO1GtEED5DdgByKQ+ZtFS6MLKPbtsrhz3gOfZDNpaXM5aXmkiEedaqmJSgFXNxXQ0czhedQNpzY7VNDGG5v0uONVLuzvedCd/U9iFCzOQ==
X-OriginatorOrg: Nvidia.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 bec7c2a0-e204-451c-e1fb-08d8f933dd8b
X-MS-Exchange-CrossTenant-AuthSource: DM6PR12MB3834.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 06 Apr 2021 19:40:43.1773
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 43083d15-7273-40c1-b7db-39efd9ccc17a
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 YjbYr5x6r4o68CxcCnAs7KaI1Hm1Q4qFG7A+i9fvl4MLOBGnGLeO38GECsrOR0bs
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6PR12MB2859
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

vfio_mdev has a number of different objects: mdev_parent, mdev_type and
mdev_device.

Unfortunately the types of these have been erased in various places
throughout the API, and this makes it very hard to understand this code or
maintain it by the time it reaches all of the drivers.

This series puts in all the types and aligns some of the design with the
driver core standard for a driver core bus driver:

 - Replace 'struct device *' with 'struct mdev_device *
 - Replace 'struct device *' with 'struct mdev_type *' and
   mtype_get_parent_dev()
 - Replace 'struct kobject *' with 'struct mdev_type *'

Now that types are clear it is easy to spot a few places that have
duplicated information.

More significantly we can now understand how to directly fix the
obfuscated 'kobj->name' matching by realizing the the kobj is a mdev_type,
which is linked to the supported_types_list provided by the driver, and
thus the core code can directly return the array indexes all the drivers
actually want.

v2:
 - Use a mdev_type local in mdev_create_sysfs_files
 - Rename the goto unwind labels in mdev_device_free()
 - Reorder patches, annotate reviewed-by's thanks all
v1: https://lore.kernel.org/r/0-v1-7dedf20b2b75+4f785-vfio2_jgg@nvidia.com

Jason Gunthorpe (18):
  vfio/mdev: Fix missing static's on MDEV_TYPE_ATTR's
  vfio/mdev: Do not allow a mdev_type to have a NULL parent pointer
  vfio/mdev: Add missing typesafety around mdev_device
  vfio/mdev: Simplify driver registration
  vfio/mdev: Use struct mdev_type in struct mdev_device
  vfio/mdev: Expose mdev_get/put_parent to mdev_private.h
  vfio/mdev: Add missing reference counting to mdev_type
  vfio/mdev: Reorganize mdev_device_create()
  vfio/mdev: Add missing error handling to dev_set_name()
  vfio/mdev: Remove duplicate storage of parent in mdev_device
  vfio/mdev: Add mdev/mtype_get_type_group_id()
  vfio/mtty: Use mdev_get_type_group_id()
  vfio/mdpy: Use mdev_get_type_group_id()
  vfio/mbochs: Use mdev_get_type_group_id()
  vfio/gvt: Make DRM_I915_GVT depend on VFIO_MDEV
  vfio/gvt: Use mdev_get_type_group_id()
  vfio/mdev: Remove kobj from mdev_parent_ops->create()
  vfio/mdev: Correct the function signatures for the
    mdev_type_attributes

 .../driver-api/vfio-mediated-device.rst       |   9 +-
 drivers/gpu/drm/i915/Kconfig                  |   1 +
 drivers/gpu/drm/i915/gvt/gvt.c                |  41 ++---
 drivers/gpu/drm/i915/gvt/gvt.h                |   4 +-
 drivers/gpu/drm/i915/gvt/kvmgt.c              |   7 +-
 drivers/s390/cio/vfio_ccw_ops.c               |  17 +-
 drivers/s390/crypto/vfio_ap_ops.c             |  14 +-
 drivers/vfio/mdev/mdev_core.c                 | 174 +++++++-----------
 drivers/vfio/mdev/mdev_driver.c               |  19 +-
 drivers/vfio/mdev/mdev_private.h              |  40 ++--
 drivers/vfio/mdev/mdev_sysfs.c                |  59 +++---
 drivers/vfio/mdev/vfio_mdev.c                 |  29 +--
 drivers/vfio/vfio_iommu_type1.c               |  25 +--
 include/linux/mdev.h                          |  80 +++++---
 samples/vfio-mdev/mbochs.c                    |  55 +++---
 samples/vfio-mdev/mdpy.c                      |  56 +++---
 samples/vfio-mdev/mtty.c                      |  66 ++-----
 17 files changed, 313 insertions(+), 383 deletions(-)
```
#### [PATCH v2 0/8] ccp: KVM: SVM: Use stack for SEV command buffers
##### From: Sean Christopherson <seanjc@google.com>

```c
From patchwork Tue Apr  6 22:49:44 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12186191
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 03BDAC433ED
	for <kvm@archiver.kernel.org>; Tue,  6 Apr 2021 22:50:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B5CBE613D5
	for <kvm@archiver.kernel.org>; Tue,  6 Apr 2021 22:50:08 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1344128AbhDFWuP (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 6 Apr 2021 18:50:15 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:40042 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S230160AbhDFWuO (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 6 Apr 2021 18:50:14 -0400
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 12B33C06174A
        for <kvm@vger.kernel.org>; Tue,  6 Apr 2021 15:50:06 -0700 (PDT)
Received: by mail-yb1-xb4a.google.com with SMTP id g7so15226599ybm.13
        for <kvm@vger.kernel.org>; Tue, 06 Apr 2021 15:50:06 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=29qkvQNMyHwLCHP8pXWRgWswaf/k2g0dTyIZhsX4Pvk=;
        b=mUCDW8goB/BkfT+GMgye4Lbl4vbr0CWjFY7SeZiXn3jP2soqTvTb9NToTJe9mZv29V
         697bWQTz0SxGedUF1HwLD0JFxJvs20ZajAvN5qgCNhk+5Wkyc1TqJZjxJ4O+0Y2u+937
         wy4sxbq50hDa62jBWPsHBBDxUDYKJapcfE2lO37hms0Sm0NsKUBuf+St+Gb5/f42Ezml
         eAe2CumEX7m0PTiQSq7OEXrbZ0w8TP2hSA9KfCv+DP0hI4IDeeFuVplbD7HFe4QuL2Y9
         7l5yJmN9dl/lx9CQDk5TGNWLKUv3ZvNrHWqkDon/XSBNVfX4Lz4zdf5HoQgI2n3ZLhVr
         /9ug==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:reply-to:date:message-id:mime-version:subject
         :from:to:cc;
        bh=29qkvQNMyHwLCHP8pXWRgWswaf/k2g0dTyIZhsX4Pvk=;
        b=QidA05UtArD26FcLJCRdqMPnRbrA4TWp77B1qk/4QkkjOGPZlGFUa6lR+fM5Uvpq5N
         wglNUOnxTP30GOJCjY0H6quZR+MYICOLsMhGO2ss10PQ7MAn1h3ltiUcDZpzfwbBJAB9
         qe5/3Rvu+YTaHP3tFA4T/q+/TyyWjqtTpiiJrk4VQ+pZgNDL+F/Gkb7Jgatf+agubFri
         i/Ul/wYgQO+QEn7nx7HPjp48ucne4WyisvclRxyVypMcCD91GvEL9XeraGkhmHrbtZb2
         FWRV6dpoLS2z4bL8btT5i7XFAFviGdiiWFWlz89zLcZz4i9pL4OlIKMo109MRAOpE9Uq
         YZBg==
X-Gm-Message-State: AOAM532OeLE2iCqpgNeQJEMqW6/m33h/AKhvw3xYR3RnfZuszhQDugu+
        HN+wXCxbl8DSU4smpnQOxFPWjWolWNg=
X-Google-Smtp-Source: 
 ABdhPJzRouXKIhQs8EfMqHUio8a2b3cN1QJZ0wcW2fPXd72cKuXtNJvbuk4wCZqugfRujJJGfODyK2fcLA0=
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:24a1:90fb:182b:777c])
 (user=seanjc job=sendgmr) by 2002:a25:2351:: with SMTP id
 j78mr536179ybj.102.1617749405370;
 Tue, 06 Apr 2021 15:50:05 -0700 (PDT)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Tue,  6 Apr 2021 15:49:44 -0700
Message-Id: <20210406224952.4177376-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.0.208.g409f899ff0-goog
Subject: [PATCH v2 0/8] ccp: KVM: SVM: Use stack for SEV command buffers
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Brijesh Singh <brijesh.singh@amd.com>,
        Tom Lendacky <thomas.lendacky@amd.com>,
        John Allen <john.allen@amd.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-crypto@vger.kernel.org, linux-kernel@vger.kernel.org,
        Borislav Petkov <bp@suse.de>,
        Christophe Leroy <christophe.leroy@csgroup.eu>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series teaches __sev_do_cmd_locked() to gracefully handle vmalloc'd
command buffers by copying _all_ incoming data pointers to an internal
buffer before sending the command to the PSP.  The SEV driver and KVM are
then converted to use the stack for all command buffers.

Tested everything except sev_ioctl_do_pek_import(), I don't know anywhere
near enough about the PSP to give it the right input.

v2:
  - Rebase to kvm/queue, commit f96be2deac9b ("KVM: x86: Support KVM VMs
    sharing SEV context").
  - Unconditionally copy @data to the internal buffer. [Christophe, Brijesh]
  - Allocate a full page for the buffer. [Brijesh]
  - Drop one set of the "!"s. [Christophe]
  - Use virt_addr_valid() instead of is_vmalloc_addr() for the temporary
    patch (definitely feel free to drop the patch if it's not worth
    backporting). [Christophe]
  - s/intput/input/. [Tom]
  - Add a patch to free "sev" if init fails.  This is not strictly
    necessary (I think; I suck horribly when it comes to the driver
    framework).   But it felt wrong to not free cmd_buf on failure, and
    even more wrong to free cmd_buf but not sev.

v1:
  - https://lkml.kernel.org/r/20210402233702.3291792-1-seanjc@google.com

Sean Christopherson (8):
  crypto: ccp: Free SEV device if SEV init fails
  crypto: ccp: Detect and reject "invalid" addresses destined for PSP
  crypto: ccp: Reject SEV commands with mismatching command buffer
  crypto: ccp: Play nice with vmalloc'd memory for SEV command structs
  crypto: ccp: Use the stack for small SEV command buffers
  crypto: ccp: Use the stack and common buffer for status commands
  crypto: ccp: Use the stack and common buffer for INIT command
  KVM: SVM: Allocate SEV command structures on local stack

 arch/x86/kvm/svm/sev.c       | 262 +++++++++++++----------------------
 drivers/crypto/ccp/sev-dev.c | 197 +++++++++++++-------------
 drivers/crypto/ccp/sev-dev.h |   4 +-
 3 files changed, 196 insertions(+), 267 deletions(-)
```
