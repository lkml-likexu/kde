

#### [kvm-unit-tests PATCH v4 00/13] arm/arm64: Add ITS tests
##### From: Eric Auger <eric.auger@redhat.com>

```c
From patchwork Mon Mar  9 10:24:07 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Auger Eric <eric.auger@redhat.com>
X-Patchwork-Id: 11426603
Return-Path: <SRS0=BDOO=42=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6ADED92A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  9 Mar 2020 10:24:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4BFFB208C3
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  9 Mar 2020 10:24:39 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="HktzG3ng"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726635AbgCIKYi (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 9 Mar 2020 06:24:38 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:40759 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1725956AbgCIKYi (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 9 Mar 2020 06:24:38 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1583749476;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=xsESJb0v2tbgzsnXysDr2pQil6qkLSgz3wrtXC2dgwQ=;
        b=HktzG3ng2If5BrpV5UGpR7vuo5H2HqOo7vcrreQUqrrxGBEU8gxIrdYFsKmPUnq2S5CIyi
        hiTB9l56uvP7T3NP/bu92ONrqkRzk856piSwsme3dFJ5kVP4b5ozGM5keW3gYOFmDnTcuK
        eVTUWvjKmrEyPn2sP0eu2ljb+khLHXc=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-286-QjWGG_wBNjinhNMo74aRwQ-1; Mon, 09 Mar 2020 06:24:35 -0400
X-MC-Unique: QjWGG_wBNjinhNMo74aRwQ-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 59858477;
        Mon,  9 Mar 2020 10:24:33 +0000 (UTC)
Received: from laptop.redhat.com (ovpn-116-59.ams2.redhat.com [10.36.116.59])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 9FD8987B08;
        Mon,  9 Mar 2020 10:24:27 +0000 (UTC)
From: Eric Auger <eric.auger@redhat.com>
To: eric.auger.pro@gmail.com, eric.auger@redhat.com, maz@kernel.org,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        qemu-devel@nongnu.org, qemu-arm@nongnu.org
Cc: drjones@redhat.com, andre.przywara@arm.com,
        peter.maydell@linaro.org, yuzenghui@huawei.com,
        alexandru.elisei@arm.com, thuth@redhat.com
Subject: [kvm-unit-tests PATCH v4 00/13] arm/arm64: Add ITS tests
Date: Mon,  9 Mar 2020 11:24:07 +0100
Message-Id: <20200309102420.24498-1-eric.auger@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series is a revival of an RFC series sent in Dec 2016 [1].
Given the amount of code and the lack of traction at that time,
I haven't respinned until now. However a recent bug found related
to the ITS migration convinced me that this work may deserve to be
respinned and enhanced.

Tests exercise main ITS commands and also test migration.
With the migration framework, we are able to trigger the
migration from guest and that is very practical actually.

What is particular with the ITS programming is that most of
the commands are passed through queues and there is real error
handling. Invalid commands are just ignored and that is not
really tester friendly.

The series can be fount at:
https://github.com/eauger/kut/tree/its-v4

Best Regards

Eric

History:
v3 -> v4:
- addressed comments from Drew and Zenghui
- added "page_alloc: Introduce get_order()"
- removed "arm: gic: Provide per-IRQ helper functions"
- ITS files moved to lib64
- and many more, see individual logs

v2 -> v3:
- fix 32b compilation
- take into account Drew's comments (see individual diff logs)

v1 -> v2:
- took into account Zenghui's comments
- collect R-b's from Thomas

References:
[1] [kvm-unit-tests RFC 00/15] arm/arm64: add ITS framework
    https://lists.gnu.org/archive/html/qemu-devel/2016-12/msg00575.html

Execution:
x For other ITS tests:
  ./run_tests.sh -g its

x non migration tests can be launched invidually. For instance:
  ./arm-run arm/gic.flat -smp 8 -append 'its-trigger'

Eric Auger (13):
  libcflat: Add other size defines
  page_alloc: Introduce get_order()
  arm/arm64: gic: Introduce setup_irq() helper
  arm/arm64: gicv3: Add some re-distributor defines
  arm/arm64: gicv3: Set the LPI config and pending tables
  arm/arm64: ITS: Introspection tests
  arm/arm64: ITS: its_enable_defaults
  arm/arm64: ITS: Device and collection Initialization
  arm/arm64: ITS: Commands
  arm/arm64: ITS: INT functional tests
  arm/run: Allow Migration tests
  arm/arm64: ITS: migration tests
  arm/arm64: ITS: pending table migration test

 arm/Makefile.arm64         |   1 +
 arm/Makefile.common        |   2 +-
 arm/gic.c                  | 469 +++++++++++++++++++++++++++++++++++--
 arm/run                    |   2 +-
 arm/unittests.cfg          |  38 +++
 lib/alloc_page.c           |   7 +-
 lib/alloc_page.h           |   1 +
 lib/arm/asm/gic-v3-its.h   |  39 +++
 lib/arm/asm/gic-v3.h       |  32 +++
 lib/arm/gic-v3.c           |  76 ++++++
 lib/arm/gic.c              |  34 ++-
 lib/arm/io.c               |  28 +++
 lib/arm64/asm/gic-v3-its.h | 172 ++++++++++++++
 lib/arm64/gic-v3-its-cmd.c | 463 ++++++++++++++++++++++++++++++++++++
 lib/arm64/gic-v3-its.c     | 172 ++++++++++++++
 lib/libcflat.h             |   3 +
 16 files changed, 1510 insertions(+), 29 deletions(-)
 create mode 100644 lib/arm/asm/gic-v3-its.h
 create mode 100644 lib/arm64/asm/gic-v3-its.h
 create mode 100644 lib/arm64/gic-v3-its-cmd.c
 create mode 100644 lib/arm64/gic-v3-its.c
```
#### [PATCH v2 0/2] KVM: arm64: Filtering PMU events
##### From: Marc Zyngier <maz@kernel.org>
X-SA-Exim-Mail-From: maz@kernel.org

```c
From patchwork Mon Mar  9 12:48:35 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11427083
Return-Path: <SRS0=BDOO=42=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E9389921
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  9 Mar 2020 12:48:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id CA14820727
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  9 Mar 2020 12:48:54 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1583758134;
	bh=CSS+5INePZvmhimi/unCx0TEoioRr+d/iqq75Std27I=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=E3Ca5hxP+jB0vlCjIMSPOMQU3iYGRhWgNO8oUziGHXeJsICBq9dD6q8yYG9yDpWzm
	 tUjmtjTYrM85iibfg2rrKhYdY4h7K0arI6FFpuS/CzPDV/ZnJsvEIH4NmQOieVrPIU
	 Icuogypo+MAuTDGOuTXO6dPm67u5ZsZI3y3sFqwM=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726415AbgCIMso (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 9 Mar 2020 08:48:44 -0400
Received: from mail.kernel.org ([198.145.29.99]:55212 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725956AbgCIMso (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 9 Mar 2020 08:48:44 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 285F620727;
        Mon,  9 Mar 2020 12:48:44 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1583758124;
        bh=CSS+5INePZvmhimi/unCx0TEoioRr+d/iqq75Std27I=;
        h=From:To:Cc:Subject:Date:From;
        b=DByraDkcHaWW6E85jLzUQ23KZZw8zgL/sHKV0sqqrojbjcSmdvjv4QpPh1LVwr1w9
         BPEixptW++IaqFflCSjCZ5E03AGMNGh4mgsm58VieYChgPjUQaR/JwiZuTXPIjHuJW
         scaLyKQSpvuvNdN/wB1L2tH32qEregObfh7UZf+M=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1jBHpq-00BHiN-C7; Mon, 09 Mar 2020 12:48:42 +0000
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Robin Murphy <robin.murphy@arm.com>,
        Mark Rutland <mark.rutland@arm.com>,
        Eric Auger <eric.auger@redhat.com>
Subject: [PATCH v2 0/2] KVM: arm64: Filtering PMU events
Date: Mon,  9 Mar 2020 12:48:35 +0000
Message-Id: <20200309124837.19908-1-maz@kernel.org>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com, robin.murphy@arm.com,
 mark.rutland@arm.com, eric.auger@redhat.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

It is at times necessary to prevent a guest from being able to sample
certain events if multiple CPUs share resources such as a cache level. In
this case, it would be interesting if the VMM could simply prevent certain
events from being counted instead of hiding the PMU.

Given that most events are not architected, there is no easy way to
designate which events shouldn't be counted other than specifying the raw
event number.

Since I have no idea whether it is better to use an event whitelist or
blacklist, the proposed API takes a cue from the x86 version and allows
either allowing or denying counting of ranges of events. The event space
being pretty large (16bits on ARMv8.1), the default policy is set by the
first filter that gets installed (default deny if we first allow, default
allow if we first deny).

The filter state is global to the guest, despite the PMU being per CPU. I'm
not sure whether it would be worth it making it CPU-private.

As an example of what can be done in userspace, I have the corresponding
kvmtool hack here[1].

* From v1:
  - Cleaned up handling of the cycle counter
  - Documented restrictions on SW_INC, CHAIN and CPU_CYCLES events

[1] https://git.kernel.org/pub/scm/linux/kernel/git/maz/kvmtool.git/commit/?h=pmu-filter

Marc Zyngier (2):
  KVM: arm64: Add PMU event filtering infrastructure
  KVM: arm64: Document PMU filtering API

 Documentation/virt/kvm/devices/vcpu.rst | 40 ++++++++++++
 arch/arm64/include/asm/kvm_host.h       |  6 ++
 arch/arm64/include/uapi/asm/kvm.h       | 16 +++++
 virt/kvm/arm/arm.c                      |  2 +
 virt/kvm/arm/pmu.c                      | 84 ++++++++++++++++++++-----
 5 files changed, 132 insertions(+), 16 deletions(-)
```
#### [PATCH 0/4] KVM: s390: reset selftest and fixes
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
From patchwork Mon Mar  9 15:00:22 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11427329
Return-Path: <SRS0=BDOO=42=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5D1D592A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  9 Mar 2020 15:00:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 46CA821655
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  9 Mar 2020 15:00:42 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726841AbgCIPAl (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 9 Mar 2020 11:00:41 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:24888 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726617AbgCIPAl (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 9 Mar 2020 11:00:41 -0400
Received: from pps.filterd (m0098404.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 029F09I9118259;
        Mon, 9 Mar 2020 11:00:40 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2ym8k7ss6v-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 09 Mar 2020 11:00:39 -0400
Received: from m0098404.ppops.net (m0098404.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 029F0dUG122814;
        Mon, 9 Mar 2020 11:00:39 -0400
Received: from ppma02wdc.us.ibm.com (aa.5b.37a9.ip4.static.sl-reverse.com
 [169.55.91.170])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2ym8k7ss2f-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 09 Mar 2020 11:00:38 -0400
Received: from pps.filterd (ppma02wdc.us.ibm.com [127.0.0.1])
        by ppma02wdc.us.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 029F0Zvw004783;
        Mon, 9 Mar 2020 15:00:35 GMT
Received: from b01cxnp23033.gho.pok.ibm.com (b01cxnp23033.gho.pok.ibm.com
 [9.57.198.28])
        by ppma02wdc.us.ibm.com with ESMTP id 2ym386b3tf-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 09 Mar 2020 15:00:35 +0000
Received: from b01ledav001.gho.pok.ibm.com (b01ledav001.gho.pok.ibm.com
 [9.57.199.106])
        by b01cxnp23033.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id 029F0YB319661106
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 9 Mar 2020 15:00:34 GMT
Received: from b01ledav001.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 9FF1A2805E;
        Mon,  9 Mar 2020 15:00:34 +0000 (GMT)
Received: from b01ledav001.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 84CA928060;
        Mon,  9 Mar 2020 15:00:34 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.114.17.106])
        by b01ledav001.gho.pok.ibm.com (Postfix) with ESMTP;
        Mon,  9 Mar 2020 15:00:34 +0000 (GMT)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: Christian Borntraeger <borntraeger@de.ibm.com>,
        Janosch Frank <frankja@linux.vnet.ibm.com>
Cc: KVM <kvm@vger.kernel.org>, Cornelia Huck <cohuck@redhat.com>,
        David Hildenbrand <david@redhat.com>,
        Thomas Huth <thuth@redhat.com>,
        linux-s390 <linux-s390@vger.kernel.org>
Subject: [PATCH 0/4] KVM: s390: reset selftest and fixes
Date: Mon,  9 Mar 2020 11:00:22 -0400
Message-Id: <20200309150026.4329-1-borntraeger@de.ibm.com>
X-Mailer: git-send-email 2.25.0
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-03-09_06:2020-03-09,2020-03-09 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 phishscore=0 mlxscore=0
 lowpriorityscore=0 malwarescore=0 clxscore=1015 impostorscore=0
 bulkscore=0 priorityscore=1501 adultscore=0 suspectscore=0 spamscore=0
 mlxlogscore=946 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2001150001 definitions=main-2003090104
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

By adding more testcases to the reset test, I even found a bug.

Christian Borntraeger (4):
  selftests: KVM: s390: fix early guest crash
  selftests: KVM: s390: test more register variants for the reset ioctl
  KVM: s390: Also reset registers in sync regs for initial cpu reset
  selftests: KVM: s390: check for registers to NOT change on reset

 arch/s390/kvm/kvm-s390.c                   |  18 ++-
 tools/testing/selftests/kvm/s390x/resets.c | 130 +++++++++++++++++----
 2 files changed, 123 insertions(+), 25 deletions(-)
```
#### [PATCH 0/6] KVM: nVMX: propperly handle enlightened vmptrld failure
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
From patchwork Mon Mar  9 15:52:10 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11427459
Return-Path: <SRS0=BDOO=42=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 87146924
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  9 Mar 2020 15:52:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 6753E208C3
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  9 Mar 2020 15:52:25 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="SEVkeIrD"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727032AbgCIPwY (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 9 Mar 2020 11:52:24 -0400
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:38255 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726436AbgCIPwY (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 9 Mar 2020 11:52:24 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1583769142;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=UB/IvUr/ugaH4om1futJLL45EG+xV5yXpIjZW59btTM=;
        b=SEVkeIrD563stOtwq2BQdj/MaInoiZYe30Ejzu2lgLBs4tglMTerTIBMiAxpML+li+dKER
        Da5hgkQDxIXC5ZcIz147M18Bu3kmBPxDr9w03tx6CL2on+hf67eDuIW+S2/bIpPLNOyr8W
        22R111slN3iyHDBsiTLAgxw5TCD1qfY=
Received: from mail-wr1-f69.google.com (mail-wr1-f69.google.com
 [209.85.221.69]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-148-GX1KOuizPSSfuup2z0bFpQ-1; Mon, 09 Mar 2020 11:52:21 -0400
X-MC-Unique: GX1KOuizPSSfuup2z0bFpQ-1
Received: by mail-wr1-f69.google.com with SMTP id v6so2981876wrg.22
        for <kvm@vger.kernel.org>; Mon, 09 Mar 2020 08:52:20 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=UB/IvUr/ugaH4om1futJLL45EG+xV5yXpIjZW59btTM=;
        b=nAat5G46tZIblIUrtDZolmxrdIxlkxd19LqB++lqg2n92icB51iZG+1wUclCPYntV2
         JuW27rKdOKmeyAQs3IPnVU5LJavFMfbOeMBEse7F1NrsyfluwfuHnsAXJ2TB1esCgi0v
         ioMf+BKYkBing7ufMVYj7PJ19ck5++/iYVHLbo8VSt/yBY30aSAKhRP/DQk+d9SN6Y7/
         sY93ZUIOsKT0A5aNndFSB5tCTNVVi1kaB9bJeSxv9van7KpOo9zMNYrgyym7v4KkVOli
         qB9SxCLQzQ4irkv+T2hhZR+mSikDnD7/rHCd+fK9KEo3Prbk3dSJD3kbAjQ2LKAZnt4A
         CF7w==
X-Gm-Message-State: ANhLgQ3h3CqQD+rEpl8wcDzs8n34m6qXnJdaaqlSJGDcJQWtcrIx2AN7
        tot4CUAHi1+0nhKkK4mFmCqDyGxOHNyJKAQfLrRZ+ypNTfmls6uYtsW8Ua9gaBKHEfyX+mWi6Dz
        xbQ+WT04A9BOh
X-Received: by 2002:a05:6000:10f:: with SMTP id
 o15mr6853054wrx.351.1583769139971;
        Mon, 09 Mar 2020 08:52:19 -0700 (PDT)
X-Google-Smtp-Source: 
 ADFU+vtw/xasyVnTCQ/tSOo6zLe/OXjzuXj8HRel7v1396vtd+EE+E43smyhMCZMQ8azfB0ke2vLQw==
X-Received: by 2002:a05:6000:10f:: with SMTP id
 o15mr6853031wrx.351.1583769139725;
        Mon, 09 Mar 2020 08:52:19 -0700 (PDT)
Received: from vitty.brq.redhat.com (nat-pool-brq-t.redhat.com.
 [213.175.37.10])
        by smtp.gmail.com with ESMTPSA id
 q4sm17294521wro.56.2020.03.09.08.52.18
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 09 Mar 2020 08:52:18 -0700 (PDT)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Jim Mattson <jmattson@google.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Liran Alon <liran.alon@oracle.com>,
        Miaohe Lin <linmiaohe@huawei.com>
Subject: [PATCH 0/6] KVM: nVMX: propperly handle enlightened vmptrld failure
 conditions
Date: Mon,  9 Mar 2020 16:52:10 +0100
Message-Id: <20200309155216.204752-1-vkuznets@redhat.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Miaohe Lin noticed that we incorrectly handle enlightened vmptrld failures
in nested_vmx_run(). Trying to handle errors correctly, I fixed
a few things:
- NULL pointer dereference with invalid eVMCS GPAs [PATCH1]
- moved eVMCS mapping after migration to nested_get_vmcs12_pages() from
  nested_sync_vmcs12_to_shadow() [PATCH2]
- added propper nested_vmx_handle_enlightened_vmptrld() error handling
  [PATCH3]
- added selftests for incorrect eVMCS revision id and GPA [PATCHes4-6]

PATCH1 fixes a DoS and thus marked for stable@.

Vitaly Kuznetsov (6):
  KVM: nVMX: avoid NULL pointer dereference with incorrect EVMCS GPAs
  KVM: nVMX: stop abusing need_vmcs12_to_shadow_sync for eVMCS mapping
  KVM: nVMX: properly handle errors in
    nested_vmx_handle_enlightened_vmptrld()
  KVM: selftests: define and use EVMCS_VERSION
  KVM: selftests: test enlightened vmenter with wrong eVMCS version
  KVM: selftests: enlightened VMPTRLD with an incorrect GPA

 arch/x86/kvm/vmx/evmcs.h                      |  7 ++
 arch/x86/kvm/vmx/nested.c                     | 64 +++++++++++++------
 tools/testing/selftests/kvm/include/evmcs.h   |  2 +
 tools/testing/selftests/kvm/lib/x86_64/vmx.c  |  2 +-
 .../testing/selftests/kvm/x86_64/evmcs_test.c | 25 ++++++--
 5 files changed, 72 insertions(+), 28 deletions(-)
```
#### [PATCH v4 0/5] x86/kvm/hyper-v: add support for synthetic debugger
##### From: Jon Doron <arilou@gmail.com>

```c
From patchwork Mon Mar  9 18:20:12 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jon Doron <arilou@gmail.com>
X-Patchwork-Id: 11427657
Return-Path: <SRS0=BDOO=42=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A325E13A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  9 Mar 2020 18:20:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 82A2920873
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  9 Mar 2020 18:20:32 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="TNfw3tiI"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727501AbgCISUb (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 9 Mar 2020 14:20:31 -0400
Received: from mail-wm1-f65.google.com ([209.85.128.65]:36694 "EHLO
        mail-wm1-f65.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727491AbgCISU3 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 9 Mar 2020 14:20:29 -0400
Received: by mail-wm1-f65.google.com with SMTP id g62so434395wme.1;
        Mon, 09 Mar 2020 11:20:28 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=CPhZKMawIEg0LF+8rUefvveQC7Pbb0atv6Urs3DG3g0=;
        b=TNfw3tiIpweI6lD4bDTky927fZqaQA/LK1U5HfECEY5Eqydk2qkzgAXkFav1YIXisY
         223HVSfNAuPQLJLGjWYKJl0kenee71inhl9QQrIY/YDyXgAx+Z42I6adHMF+uMmHCVis
         N1TX2eO+gfHuhXnGYnYL4CV9g7+hmL5TdVcdZaKp48AmgA4RlEtoSNP6YU9xTZenBcKP
         HXecdLfeWqjyCPxVDx71J9vDpEo7/cqTZvnIqDyTw2qdIBFHB0Xdyyz3meBxYsc44A59
         r36/LbFhCeuCmqPldIV5dgm9rGvrwlNiMzEHxlbjxqLNJ5Wgbb1tSsLr6LXHuPziFr+2
         vJiw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=CPhZKMawIEg0LF+8rUefvveQC7Pbb0atv6Urs3DG3g0=;
        b=MK83Ue5DnMu+0m+yTlSKZ9dScvY8JB5eBhjBnVdKaFM++xDdnNQ9LTVNh067rGjj7C
         JbFFGLdDc88Pd8vRM4WpAkIl/g26UbI0LzUD7E0KDitn5w78IeeE7VcAZQd0xJz+HJ8P
         wI7x/bZwHuGf+T62vWn34cjSfLbYW9NPUhGdjf5cVGU9bi51ru3VYG3EXE8lMDUTQB5e
         djiV3CN71j3mmq3vpldO5BKNRn2qGeZvBD3eySNLjaTOVJDzMkodSrpnYolxHUOhLEg/
         UrygVjkKbSChB8nlZkjK+RA6pOAqTjAYL2Dd6FTK/y8S965nz6EyIzU7Al+qmLiVNYH3
         f9DQ==
X-Gm-Message-State: ANhLgQ3ldJ1UpbP1B+PJvej+66qPe2DteZT/s5FkqiMyN7MWMKoAEzwV
        6kryRjuNlWVHXExW2FlNYAJeGOWqQEo=
X-Google-Smtp-Source: 
 ADFU+vtJJVp/SvpSTLWjaT/eQ+QNJuwwAQtNA4ugOEOmHSKxF8Ule/kJp4Tr/CBK/y+JuVLHgaxhPQ==
X-Received: by 2002:a1c:f707:: with SMTP id v7mr479325wmh.121.1583778026969;
        Mon, 09 Mar 2020 11:20:26 -0700 (PDT)
Received: from linux.local ([31.154.166.148])
        by smtp.gmail.com with ESMTPSA id
 t6sm8371828wrr.49.2020.03.09.11.20.25
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 09 Mar 2020 11:20:26 -0700 (PDT)
From: Jon Doron <arilou@gmail.com>
To: kvm@vger.kernel.org, linux-hyperv@vger.kernel.org
Cc: vkuznets@redhat.com, Jon Doron <arilou@gmail.com>
Subject: [PATCH v4 0/5] x86/kvm/hyper-v: add support for synthetic debugger
Date: Mon,  9 Mar 2020 20:20:12 +0200
Message-Id: <20200309182017.3559534-1-arilou@gmail.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add support for the synthetic debugger interface of hyper-v, the
synthetic debugger has 2 modes.
1. Use a set of MSRs to send/recv information
2. Use hypercalls

The first mode is based the following MSRs:
1. Control/Status MSRs which either asks for a send/recv .
2. Send/Recv MSRs each holds GPA where the send/recv buffers are.
3. Pending MSR, holds a GPA to a PAGE that simply has a boolean that
   indicates if there is data pending to issue a recv VMEXIT.

In the first patch the first mode is being implemented in the sense that
it simply exits to user-space when a control MSR is being written and
when the pending MSR is being set, then it's up-to userspace to
implement the rest of the logic of sending/recving.

In the second mode instead of using MSRs KNet will simply issue
Hypercalls with the information to send/recv, in this mode the data
being transferred is UDP encapsulated, unlike in the previous mode in
which you get just the data to send.

The new hypercalls will exit to userspace which will be incharge of
re-encapsulating if needed the UDP packets to be sent.

There is an issue though in which KDNet does not respect the hypercall
page and simply issues vmcall/vmmcall instructions depending on the cpu
type expecting them to be handled as it a real hypercall was issued.

Jon Doron (5):
  x86/kvm/hyper-v: Explicitly align hcall param for kvm_hyperv_exit
  x86/hyper-v: Add synthetic debugger definitions
  x86/kvm/hyper-v: Add support for synthetic debugger capability
  x86/kvm/hyper-v: enable hypercalls regardless of hypercall page
  x86/kvm/hyper-v: Add support for synthetic debugger via hypercalls

 arch/x86/include/asm/hyperv-tlfs.h |  26 +++++
 arch/x86/include/asm/kvm_host.h    |  13 +++
 arch/x86/kvm/hyperv.c              | 162 ++++++++++++++++++++++++++++-
 arch/x86/kvm/hyperv.h              |   5 +
 arch/x86/kvm/trace.h               |  51 +++++++++
 arch/x86/kvm/x86.c                 |   9 ++
 include/uapi/linux/kvm.h           |  11 ++
 7 files changed, 275 insertions(+), 2 deletions(-)
```
#### [PATCH v6 00/14] KVM: Dirty ring interface
##### From: Peter Xu <peterx@redhat.com>

```c
From patchwork Mon Mar  9 21:44:10 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11428125
Return-Path: <SRS0=BDOO=42=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2DC82139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  9 Mar 2020 21:44:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 0161F24655
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  9 Mar 2020 21:44:34 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="KfggPge5"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727088AbgCIVod (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 9 Mar 2020 17:44:33 -0400
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:60605 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726266AbgCIVod (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 9 Mar 2020 17:44:33 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1583790271;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=+ICtR2v0xNomH1WLkex46Nm+YSPs83aCqTW2zuVdMA4=;
        b=KfggPge5R51zEnrozMLwxsTSWUAjVuCTznd3SN1LJhpj8GOs8BtmvloEFdB4wlXOasRvCZ
        0CFcakKCEkA8Yu9xMNlfzd3o/YoyMTLlZafN53U9S9xBddwjHWNVogRt00dKC+eUrbDC0b
        jkU29E7vuTNPHqEswmktUx8X/2dsHeQ=
Received: from mail-qt1-f198.google.com (mail-qt1-f198.google.com
 [209.85.160.198]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-321-02TW3aEKNF-67w_EybCobQ-1; Mon, 09 Mar 2020 17:44:27 -0400
X-MC-Unique: 02TW3aEKNF-67w_EybCobQ-1
Received: by mail-qt1-f198.google.com with SMTP id b10so3710100qto.21
        for <kvm@vger.kernel.org>; Mon, 09 Mar 2020 14:44:27 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=+ICtR2v0xNomH1WLkex46Nm+YSPs83aCqTW2zuVdMA4=;
        b=AqGhFe7oj97K/d1UQVwpQ5PNCQcydKoc0OJkXkVEg2AFdc0qYkjzJ8j7Ti7NS38p8c
         GNlwZrXnO8VkXd4IZASPQCKU4TyIzocq238lD3jD+IbfVeizOReAea1SQpRNh9w8W5FE
         tO8oLafbFq8RK1mwqdOFaUkM2lqLws5v5zH5FuNBF51SdGm5zAqiBikrgSpc3GrZrnif
         rXJHaL7/IOihG4S/lO6dV8RbWqRQCjeBFmsRpL+yGSKKiGq6UfiFxQOd+pdHtoNDb0H+
         OiN3+jiVM7gMOe5YdAK9whbZJUsW6U7Sj650gvpfD0SCTYZNqaNXzRV/IcYhiHhP5nXi
         bOUg==
X-Gm-Message-State: ANhLgQ26Rg1LVcw7+32Lc7Nt3sjuyqdYOF7yUwbwbQ/J+qsQ56Vi5i25
        8UePRWW1omx0kMsXJ77PMifpqeBkzH8/u7+hDaUNnZuIeLYybFEAJAbNuYBcidtwEdKWUDCYKd1
        SwFM8+0yGZYSQ
X-Received: by 2002:a37:4ec1:: with SMTP id c184mr2019112qkb.0.1583790266997;
        Mon, 09 Mar 2020 14:44:26 -0700 (PDT)
X-Google-Smtp-Source: 
 ADFU+vstAS1kAHk1yzYK0Qv2/bUTpVaVnkqEMcxpVeMGOT8PFcgZlWN3qpoiuGO6oI0meC5+JHYWaw==
X-Received: by 2002:a37:4ec1:: with SMTP id c184mr2019077qkb.0.1583790266685;
        Mon, 09 Mar 2020 14:44:26 -0700 (PDT)
Received: from xz-x1.redhat.com ([2607:9880:19c0:32::2])
        by smtp.gmail.com with ESMTPSA id
 82sm10504502qko.91.2020.03.09.14.44.25
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 09 Mar 2020 14:44:25 -0700 (PDT)
From: Peter Xu <peterx@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Yan Zhao <yan.y.zhao@intel.com>, Jason Wang <jasowang@redhat.com>,
        Alex Williamson <alex.williamson@redhat.com>,
        peterx@redhat.com, Vitaly Kuznetsov <vkuznets@redhat.com>,
        "Dr . David Alan Gilbert" <dgilbert@redhat.com>,
        Christophe de Dinechin <dinechin@redhat.com>,
        "Michael S . Tsirkin" <mst@redhat.com>,
        Kevin Tian <kevin.tian@intel.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>
Subject: [PATCH v6 00/14] KVM: Dirty ring interface
Date: Mon,  9 Mar 2020 17:44:10 -0400
Message-Id: <20200309214424.330363-1-peterx@redhat.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

KVM branch:
  https://github.com/xzpeter/linux/tree/kvm-dirty-ring

QEMU branch for testing:
  https://github.com/xzpeter/qemu/tree/kvm-dirty-ring

v6:
- fix typo in test case (LOG_MODE_CLERA_LOG) [Dave]
- fix s390 build (again), by moving kvm_reset_dirty_gfn into
  kvm_dirty_ring.c, with some macro movements [syzbot]

For previous versions, please refer to:

V1: https://lore.kernel.org/kvm/20191129213505.18472-1-peterx@redhat.com
V2: https://lore.kernel.org/kvm/20191221014938.58831-1-peterx@redhat.com
V3: https://lore.kernel.org/kvm/20200109145729.32898-1-peterx@redhat.com
V4: https://lore.kernel.org/kvm/20200205025105.367213-1-peterx@redhat.com
V5: https://lore.kernel.org/kvm/20200304174947.69595-1-peterx@redhat.com

Overview
============

This is a continued work from Lei Cao <lei.cao@stratus.com> and Paolo
Bonzini on the KVM dirty ring interface.

The new dirty ring interface is another way to collect dirty pages for
the virtual machines. It is different from the existing dirty logging
interface in a few ways, majorly:

  - Data format: The dirty data was in a ring format rather than a
    bitmap format, so dirty bits to sync for dirty logging does not
    depend on the size of guest memory any more, but speed of
    dirtying.  Also, the dirty ring is per-vcpu, while the dirty
    bitmap is per-vm.

  - Data copy: The sync of dirty pages does not need data copy any more,
    but instead the ring is shared between the userspace and kernel by
    page sharings (mmap() on vcpu fd)

  - Interface: Instead of using the old KVM_GET_DIRTY_LOG,
    KVM_CLEAR_DIRTY_LOG interfaces, the new ring uses the new
    KVM_RESET_DIRTY_RINGS ioctl when we want to reset the collected
    dirty pages to protected mode again (works like
    KVM_CLEAR_DIRTY_LOG, but ring based).  To collecting dirty bits,
    we only need to read the ring data, no ioctl is needed.

Ring Layout
===========

KVM dirty ring is per-vcpu.  Each ring is an array of kvm_dirty_gfn
defined as:

struct kvm_dirty_gfn {
        __u32 flags;
        __u32 slot; /* as_id | slot_id */
        __u64 offset;
};

Each GFN is a state machine itself.  The state is embeded in the flags
field, as defined in the uapi header:

/*
 * KVM dirty GFN flags, defined as:
 *
 * |---------------+---------------+--------------|
 * | bit 1 (reset) | bit 0 (dirty) | Status       |
 * |---------------+---------------+--------------|
 * |             0 |             0 | Invalid GFN  |
 * |             0 |             1 | Dirty GFN    |
 * |             1 |             X | GFN to reset |
 * |---------------+---------------+--------------|
 *
 * Lifecycle of a dirty GFN goes like:
 *
 *      dirtied         collected        reset
 * 00 -----------> 01 -------------> 1X -------+
 *  ^                                          |
 *  |                                          |
 *  +------------------------------------------+
 *
 * The userspace program is only responsible for the 01->1X state
 * conversion (to collect dirty bits).  Also, it must not skip any
 * dirty bits so that dirty bits are always collected in sequence.
 */

Testing
=======

This series provided both the implementation of the KVM dirty ring and
the test case.  Also I've implemented the QEMU counterpart that can
run with the new KVM, link can be found at the top of the cover
letter.  However that's still a very initial version which is prone to
change and future optimizations.

I did some measurement with the new method with 24G guest running some
dirty workload, I don't see any speedup so far, even in some heavy
dirty load it'll be slower (e.g., when 800MB/s random dirty rate, kvm
dirty ring takes average of ~73s to complete migration while dirty
logging only needs average of ~55s).  However that's understandable
because 24G guest means only 1M dirty bitmap, that's still a suitable
case for dirty logging.  Meanwhile heavier workload means worst case
for dirty ring.

More tests are welcomed if there's bigger host/guest, especially on
COLO-like workload.

Please review, thanks.

Peter Xu (14):
  KVM: X86: Change parameter for fast_page_fault tracepoint
  KVM: Cache as_id in kvm_memory_slot
  KVM: X86: Don't track dirty for KVM_SET_[TSS_ADDR|IDENTITY_MAP_ADDR]
  KVM: Pass in kvm pointer into mark_page_dirty_in_slot()
  KVM: X86: Implement ring-based dirty memory tracking
  KVM: Make dirty ring exclusive to dirty bitmap log
  KVM: Don't allocate dirty bitmap if dirty ring is enabled
  KVM: selftests: Always clear dirty bitmap after iteration
  KVM: selftests: Sync uapi/linux/kvm.h to tools/
  KVM: selftests: Use a single binary for dirty/clear log test
  KVM: selftests: Introduce after_vcpu_run hook for dirty log test
  KVM: selftests: Add dirty ring buffer test
  KVM: selftests: Let dirty_log_test async for dirty ring test
  KVM: selftests: Add "-c" parameter to dirty log test

 Documentation/virt/kvm/api.rst                | 123 +++++
 arch/x86/include/asm/kvm_host.h               |   6 +-
 arch/x86/include/uapi/asm/kvm.h               |   1 +
 arch/x86/kvm/Makefile                         |   3 +-
 arch/x86/kvm/mmu/mmu.c                        |  10 +-
 arch/x86/kvm/mmutrace.h                       |   9 +-
 arch/x86/kvm/svm.c                            |   9 +-
 arch/x86/kvm/vmx/vmx.c                        |  85 +--
 arch/x86/kvm/x86.c                            |  49 +-
 include/linux/kvm_dirty_ring.h                | 103 ++++
 include/linux/kvm_host.h                      |  19 +
 include/trace/events/kvm.h                    |  78 +++
 include/uapi/linux/kvm.h                      |  53 ++
 tools/include/uapi/linux/kvm.h                |  44 ++
 tools/testing/selftests/kvm/Makefile          |   2 -
 .../selftests/kvm/clear_dirty_log_test.c      |   2 -
 tools/testing/selftests/kvm/dirty_log_test.c  | 488 ++++++++++++++++--
 .../testing/selftests/kvm/include/kvm_util.h  |   4 +
 tools/testing/selftests/kvm/lib/kvm_util.c    |  67 +++
 .../selftests/kvm/lib/kvm_util_internal.h     |   4 +
 virt/kvm/dirty_ring.c                         | 195 +++++++
 virt/kvm/kvm_main.c                           | 164 +++++-
 22 files changed, 1393 insertions(+), 125 deletions(-)
 create mode 100644 include/linux/kvm_dirty_ring.h
 delete mode 100644 tools/testing/selftests/kvm/clear_dirty_log_test.c
 create mode 100644 virt/kvm/dirty_ring.c
```
