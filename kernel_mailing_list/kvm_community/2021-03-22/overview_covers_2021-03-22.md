

#### [PATCH v5 0/6] KVM: arm64: Add VLPI migration support on GICv4.1
##### From: Shenming Lu <lushenming@huawei.com>

```c
From patchwork Mon Mar 22 06:01:52 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Shenming Lu <lushenming@huawei.com>
X-Patchwork-Id: 12153803
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 3A17FC433DB
	for <kvm@archiver.kernel.org>; Mon, 22 Mar 2021 06:03:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id F168C61966
	for <kvm@archiver.kernel.org>; Mon, 22 Mar 2021 06:03:36 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229614AbhCVGDE (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 22 Mar 2021 02:03:04 -0400
Received: from szxga06-in.huawei.com ([45.249.212.32]:14421 "EHLO
        szxga06-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S230035AbhCVGCa (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 22 Mar 2021 02:02:30 -0400
Received: from DGGEMS412-HUB.china.huawei.com (unknown [172.30.72.59])
        by szxga06-in.huawei.com (SkyGuard) with ESMTP id 4F3kPv4k4tzkdDV;
        Mon, 22 Mar 2021 14:00:51 +0800 (CST)
Received: from DESKTOP-7FEPK9S.china.huawei.com (10.174.184.135) by
 DGGEMS412-HUB.china.huawei.com (10.3.19.212) with Microsoft SMTP Server id
 14.3.498.0; Mon, 22 Mar 2021 14:02:18 +0800
From: Shenming Lu <lushenming@huawei.com>
To: Marc Zyngier <maz@kernel.org>, Eric Auger <eric.auger@redhat.com>,
        "Will Deacon" <will@kernel.org>,
        <linux-arm-kernel@lists.infradead.org>,
        <kvmarm@lists.cs.columbia.edu>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>
CC: Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Lorenzo Pieralisi <lorenzo.pieralisi@arm.com>,
        <wanghaibin.wang@huawei.com>, <yuzenghui@huawei.com>,
        <lushenming@huawei.com>
Subject: [PATCH v5 0/6] KVM: arm64: Add VLPI migration support on GICv4.1
Date: Mon, 22 Mar 2021 14:01:52 +0800
Message-ID: <20210322060158.1584-1-lushenming@huawei.com>
X-Mailer: git-send-email 2.27.0.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.184.135]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

In GICv4.1, migration has been supported except for (directly-injected)
VLPI. And GICv4.1 Spec explicitly gives a way to get the VLPI's pending
state (which was crucially missing in GICv4.0). So we make VLPI migration
capable on GICv4.1 in this series.

In order to support VLPI migration, we need to save and restore all
required configuration information and pending states of VLPIs. But
in fact, the configuration information of VLPIs has already been saved
(or will be reallocated on the dst host...) in vgic(kvm) migration.
So we only have to migrate the pending states of VLPIs specially.

Below is the related workflow in migration.

On the save path:
	In migration completion:
		pause all vCPUs
				|
		call each VM state change handler:
			pause other devices (just keep from sending interrupts, and
			such as VFIO migration protocol has already realized it [1])
					|
			flush ITS tables into guest RAM
					|
			flush RDIST pending tables (also flush VLPI pending states here)
				|
		...
On the resume path:
	load each device's state:
		restore ITS tables (include pending tables) from guest RAM
				|
		for other (PCI) devices (paused), if configured to have VLPIs,
		establish the forwarding paths of their VLPIs (and transfer
		the pending states from kvm's vgic to VPT here)

We have tested this series in VFIO migration, and found some related
issues in QEMU [2].

Links:
[1] vfio: UAPI for migration interface for device state:
    https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/commit/?id=a8a24f3f6e38103b77cf399c38eb54e1219d00d6
[2] vfio: Some fixes and optimizations for VFIO migration:
    https://patchwork.ozlabs.org/project/qemu-devel/cover/20210310030233.1133-1-lushenming@huawei.com/

History:

v4 -> v5
 - Lock the whole pending state read/write sequence. (in Patch 5, from Marc)

v3 -> v4
 - Nit fixes.
 - Add a CPU cache invalidation right after unmapping the vPE. (Patch 1)
 - Drop the setting of PTZ altogether. (Patch 2)
 - Bail out if spot !vgic_initialized(). (in Patch 4)
 - Communicate the state change (clear pending_latch) via
   vgic_queue_irq_unlock. (in Patch 5)

Thanks a lot for the suggestions from Marc!

v2 -> v3
 - Add the vgic initialized check to ensure that the allocation and enabling
   of the doorbells have already been done before unmapping the vPEs.
 - Check all get_vlpi_state related conditions in save_pending_tables in one place.
 - Nit fixes.

v1 -> v2:
 - Get the VLPI state from the KVM side.
 - Nit fixes.

Thanks,
Shenming


Marc Zyngier (1):
  irqchip/gic-v3-its: Add a cache invalidation right after vPE unmapping

Shenming Lu (4):
  irqchip/gic-v3-its: Drop the setting of PTZ altogether
  KVM: arm64: GICv4.1: Add function to get VLPI state
  KVM: arm64: GICv4.1: Try to save VLPI state in save_pending_tables
  KVM: arm64: GICv4.1: Give a chance to save VLPI state

Zenghui Yu (1):
  KVM: arm64: GICv4.1: Restore VLPI pending state to physical side

 .../virt/kvm/devices/arm-vgic-its.rst         |  2 +-
 arch/arm64/kvm/vgic/vgic-its.c                |  6 +-
 arch/arm64/kvm/vgic/vgic-v3.c                 | 66 +++++++++++++++++--
 arch/arm64/kvm/vgic/vgic-v4.c                 | 38 +++++++++++
 arch/arm64/kvm/vgic/vgic.h                    |  1 +
 drivers/irqchip/irq-gic-v3-its.c              | 21 +++++-
 6 files changed, 122 insertions(+), 12 deletions(-)
```
#### [PATCH v2 0/2] s390/kvm: VSIE: fix prefixing and MSO for MVPG
##### From: Claudio Imbrenda <imbrenda@linux.ibm.com>

```c
From patchwork Mon Mar 22 14:05:57 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Claudio Imbrenda <imbrenda@linux.ibm.com>
X-Patchwork-Id: 12154879
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 2E568C433E8
	for <kvm@archiver.kernel.org>; Mon, 22 Mar 2021 14:07:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 073BB61992
	for <kvm@archiver.kernel.org>; Mon, 22 Mar 2021 14:06:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230281AbhCVOGd (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 22 Mar 2021 10:06:33 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:38830 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S230497AbhCVOGM (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 22 Mar 2021 10:06:12 -0400
Received: from pps.filterd (m0098394.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 12ME3J3i036725;
        Mon, 22 Mar 2021 10:06:12 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=pnANhrdarCwpxEDW4R3cclyoLFe42MpHeORvJNjndw4=;
 b=b2brCyiOCVgd9E4AVSWlcHV793fsQ5cbC3cZfXLRUihclpW2p44ylChmVxm6aiizUnhR
 QPFXynML482QmRw+eZ3nMbD6vHmYkfH03xmeOGsThDWn3pZKT8C/lvHwcMkcYejg6gO1
 1mgAgWM01Ot3z9VUTI0zx17m6vTrwCXEwPFOTkuP0mNCu2bBbBZfKP+2HRjACIFccRt1
 NZ8S85BpYjfzF1Fs/vl85Y9td4Bm76SYsZf4TYnpyZ+60eSrQfoJYs39SplS/Jn7+bK3
 qqv1PHjweXLuWDao72VVBOz6ZPdrrDuKHfUXamlMz+lNkGsEaXVWv5zqBMv/IWNCn/1h Rw==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 37e03f0jbn-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 22 Mar 2021 10:06:12 -0400
Received: from m0098394.ppops.net (m0098394.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 12ME3cwT038627;
        Mon, 22 Mar 2021 10:06:12 -0400
Received: from ppma04fra.de.ibm.com (6a.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.106])
        by mx0a-001b2d01.pphosted.com with ESMTP id 37e03f0j81-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 22 Mar 2021 10:06:11 -0400
Received: from pps.filterd (ppma04fra.de.ibm.com [127.0.0.1])
        by ppma04fra.de.ibm.com (8.16.0.43/8.16.0.43) with SMTP id
 12ME2V0b004761;
        Mon, 22 Mar 2021 14:06:03 GMT
Received: from b06cxnps3075.portsmouth.uk.ibm.com
 (d06relay10.portsmouth.uk.ibm.com [9.149.109.195])
        by ppma04fra.de.ibm.com with ESMTP id 37d9by987f-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 22 Mar 2021 14:06:03 +0000
Received: from d06av22.portsmouth.uk.ibm.com (d06av22.portsmouth.uk.ibm.com
 [9.149.105.58])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 12ME60q641419176
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 22 Mar 2021 14:06:00 GMT
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 489CB4C04A;
        Mon, 22 Mar 2021 14:06:00 +0000 (GMT)
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id D7F6D4C050;
        Mon, 22 Mar 2021 14:05:59 +0000 (GMT)
Received: from ibm-vm.ibmuc.com (unknown [9.145.2.56])
        by d06av22.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Mon, 22 Mar 2021 14:05:59 +0000 (GMT)
From: Claudio Imbrenda <imbrenda@linux.ibm.com>
To: linux-kernel@vger.kernel.org
Cc: borntraeger@de.ibm.com, frankja@linux.ibm.com, david@redhat.com,
        cohuck@redhat.com, kvm@vger.kernel.org, linux-s390@vger.kernel.org
Subject: [PATCH v2 0/2] s390/kvm: VSIE: fix prefixing and MSO for MVPG
Date: Mon, 22 Mar 2021 15:05:57 +0100
Message-Id: <20210322140559.500716-1-imbrenda@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.761
 definitions=2021-03-22_07:2021-03-22,2021-03-22 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 clxscore=1015
 priorityscore=1501 lowpriorityscore=0 adultscore=0 phishscore=0
 impostorscore=0 bulkscore=0 mlxscore=0 mlxlogscore=999 malwarescore=0
 spamscore=0 suspectscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2103220103
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The guest real address needs to pass through prefixing in order to yield
the absolute address.

The absolute address needs to be offset by the MSO in order to get the
host virtual address.

v1->v2
* use the MSO from the shadow SIE page instead of the original one
* reuse src and dest variabled to improve readability

Claudio Imbrenda (2):
  s390/kvm: split kvm_s390_real_to_abs
  s390/kvm: VSIE: fix MVPG handling for prefixing and MSO

 arch/s390/kvm/gaccess.h | 23 +++++++++++++++++------
 arch/s390/kvm/vsie.c    |  6 +++++-
 2 files changed, 22 insertions(+), 7 deletions(-)
```
#### [kvm-unit-tests PATCH v2 0/6] Misc assembly fixes and cleanups
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c
From patchwork Mon Mar 22 15:06:35 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexandru Elisei <alexandru.elisei@arm.com>
X-Patchwork-Id: 12155107
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A9A61C433DB
	for <kvm@archiver.kernel.org>; Mon, 22 Mar 2021 15:07:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5F3FA619BA
	for <kvm@archiver.kernel.org>; Mon, 22 Mar 2021 15:07:23 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231607AbhCVPGy (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 22 Mar 2021 11:06:54 -0400
Received: from foss.arm.com ([217.140.110.172]:33478 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S231621AbhCVPGU (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 22 Mar 2021 11:06:20 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id A97F91042;
        Mon, 22 Mar 2021 08:06:19 -0700 (PDT)
Received: from monolith.localdoman (unknown [172.31.20.19])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 E73293F719;
        Mon, 22 Mar 2021 08:06:18 -0700 (PDT)
From: Alexandru Elisei <alexandru.elisei@arm.com>
To: drjones@redhat.com, kvm@vger.kernel.org,
        kvmarm@lists.cs.columbia.edu
Cc: andre.przywara@arm.com
Subject: [kvm-unit-tests PATCH v2 0/6] Misc assembly fixes and cleanups
Date: Mon, 22 Mar 2021 15:06:35 +0000
Message-Id: <20210322150641.58878-1-alexandru.elisei@arm.com>
X-Mailer: git-send-email 2.31.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series is mostly fixes and cleanups for things I found when playing
with EFI support. Most of them I hope are fairly self-explanatory.

What is clearly aimed at running on baremetal is patch #2 ("arm/arm64:
Remove dcache_line_size global variable"), which is needed because the
startup environment is different for EFI apps and we're going to need to do
cache maintenance before setup() is run.

Patch #4 ("lib: arm64: Consolidate register definitions to sysreg.h") is
there to make importing register definitions and other header files from
Linux (like el2_setup.h) easier by switching to the same layout. And arm
is already using sysreg.h for SCTLR fields.

Changes in v2:
* Gathered Reviewed-by tags, thank you!
* For patch #2 ("arm/arm64: Remove dcache_line_size global variable"), I've
  modified the commit message to mention the change in parameters for
  dcache_by_line_op, I've added the proper header guards to
  lib/arm/asm/assembler.h and I've changed raw_dcache_line_size to use ubfx
  instead of ubfm.

Alexandru Elisei (6):
  arm64: Remove unnecessary ISB when writing to SPSel
  arm/arm64: Remove dcache_line_size global variable
  arm/arm64: Remove unnecessary ISB when doing dcache maintenance
  lib: arm64: Consolidate register definitions to sysreg.h
  arm64: Configure SCTLR_EL1 at boot
  arm64: Disable TTBR1_EL1 translation table walks

 lib/arm/asm/assembler.h       | 53 ++++++++++++++++++++++++++++++++++
 lib/arm/asm/processor.h       |  7 -----
 lib/arm64/asm/arch_gicv3.h    |  6 ----
 lib/arm64/asm/assembler.h     | 54 +++++++++++++++++++++++++++++++++++
 lib/arm64/asm/pgtable-hwdef.h |  1 +
 lib/arm64/asm/processor.h     | 17 -----------
 lib/arm64/asm/sysreg.h        | 24 ++++++++++++++++
 lib/arm/setup.c               |  7 -----
 arm/cstart.S                  | 19 ++----------
 arm/cstart64.S                | 28 +++++++-----------
 10 files changed, 145 insertions(+), 71 deletions(-)
 create mode 100644 lib/arm/asm/assembler.h
 create mode 100644 lib/arm64/asm/assembler.h
```
#### [PATCH 0/4 v4] nSVM: Test host RFLAGS.TF on VMRUN
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
From patchwork Mon Mar 22 18:10:03 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 12155955
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id F0F18C433C1
	for <kvm@archiver.kernel.org>; Mon, 22 Mar 2021 18:59:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C149F619A2
	for <kvm@archiver.kernel.org>; Mon, 22 Mar 2021 18:59:26 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232230AbhCVS65 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 22 Mar 2021 14:58:57 -0400
Received: from aserp2120.oracle.com ([141.146.126.78]:56976 "EHLO
        aserp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S231674AbhCVS6s (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 22 Mar 2021 14:58:48 -0400
Received: from pps.filterd (aserp2120.oracle.com [127.0.0.1])
        by aserp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 12MInRxd020336;
        Mon, 22 Mar 2021 18:58:43 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : content-transfer-encoding : content-type :
 mime-version; s=corp-2020-01-29;
 bh=xJx38k7Yfwxuwb8DcYyX9exNs9Z2W5O7BFVCGJFGOcA=;
 b=FfXQes+Okdexgc21ZgkiwymHs3/QQbGgGPAtr5zc4FoSKKalmojxcbICPkolnFTNLf9B
 ow6+fhxS71CGpC72yQi1EkKsRdGLzPqQSETwHtpKdVov6WRtTCCmOqB+y+C8GdQr/ttE
 TW3lXMvImI6wfeuAq9IbqUTVuauXtOp6yRynw0F/Dpwm6E5XwbhvxMXmJjXUjqlFdsWv
 p15hVzHzA+jh6g18r9k6gFAE2M8T8YEERryuOLTFz/NJdpJbIYI6xEMdjIwiAPV3kZwH
 czDrdfm18sj0w+rEbjFs69Ubn2qjouuimuyS4aEne9rcdCUMxvOwlypch2O7Imo8h8US yQ==
Received: from userp3020.oracle.com (userp3020.oracle.com [156.151.31.79])
        by aserp2120.oracle.com with ESMTP id 37d90mch49-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 22 Mar 2021 18:58:42 +0000
Received: from pps.filterd (userp3020.oracle.com [127.0.0.1])
        by userp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 12MIo8Iq135034;
        Mon, 22 Mar 2021 18:58:42 GMT
Received: from nam12-mw2-obe.outbound.protection.outlook.com
 (mail-mw2nam12lp2042.outbound.protection.outlook.com [104.47.66.42])
        by userp3020.oracle.com with ESMTP id 37dttqxyc5-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 22 Mar 2021 18:58:41 +0000
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=nqW99gLdEDqH6cDpWteuzPDB5W2CW5J13IjXMDHxlwq7m2YMmsB6sZpUDcJ94HifkuwmVhvbaVApkEuM7lIoqqfMTog/gbxkvF+RkjcHODVHpuMGMV17hx8BgFEi0HtDC8RnKYsTAZJgUhlGrmiOy3YoZ/W19sgh2omlz5zGJb+54YkGwCL4H1Sb5kLP3lvwH1Obn4Gmg34tXFCvxatYQFa+mzA8pYWaYgvlBKQhoLnKNvfj6fUiCItQwGQ4FffJtTtYtBDxMX+xEwxX8eghrvuRg/39qLknjECIjduyEWaITvoMlbzskzJBM+1ooHF9L5uRt63xiUKh5CdmopQ5Jw==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=xJx38k7Yfwxuwb8DcYyX9exNs9Z2W5O7BFVCGJFGOcA=;
 b=G38I/kiD/PExcpIX9+pQkT1LefxQgq62m8qhnkEJAmPBh4+AMOEdFwF6MphAPVpKzQcUi6Xt/6Ma3vT0056BF1LzA3BQL55uU6HuNVbNVyx0JrHVT04QPb9Yl+uOOkmWb0m0lTYAkz6edxRm1MK0mdTCI/YTG4g0ENHHGAzlLly7rNwh/XeBvAdNSgmWASwBA55pV14DuRvLH6RFtKGh0OB+nojUiaV+LUvZxTpqH3ikeINEkf0Y8tyLX9HszXr6GlFGKGPiLGFiKFSrPKAogDgAeK+t+aLRA+UTqVZZnOd6VCHDSUtMo+vM2dSm9FPw8IF3k+drBX6kxh6yE9vNOg==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=oracle.com; dmarc=pass action=none header.from=oracle.com;
 dkim=pass header.d=oracle.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=oracle.onmicrosoft.com; s=selector2-oracle-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=xJx38k7Yfwxuwb8DcYyX9exNs9Z2W5O7BFVCGJFGOcA=;
 b=rSJLjdkHgipbO8geaYOc32v2iB5Vol19VPndGjS4ZxgurLyR7xgBB7P5JWJnVlYtTdVRlquB3n2bRIUix0fSG24NGITUC1jqS9ZwNArk6etqKI9Z+oTIWmz80BtSGkD2mzpmqlW/scE+pUxd4Tg9pmTxRYsXUWhHsc/L76UPmvs=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=oracle.com;
Received: from SN6PR10MB3021.namprd10.prod.outlook.com (2603:10b6:805:cc::19)
 by SA2PR10MB4795.namprd10.prod.outlook.com (2603:10b6:806:11d::14) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3955.18; Mon, 22 Mar
 2021 18:58:40 +0000
Received: from SN6PR10MB3021.namprd10.prod.outlook.com
 ([fe80::1871:3741:cc17:bcf7]) by SN6PR10MB3021.namprd10.prod.outlook.com
 ([fe80::1871:3741:cc17:bcf7%7]) with mapi id 15.20.3955.025; Mon, 22 Mar 2021
 18:58:40 +0000
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com, seanjc@google.com
Subject: [PATCH 0/4 v4] nSVM: Test host RFLAGS.TF on VMRUN
Date: Mon, 22 Mar 2021 14:10:03 -0400
Message-Id: <20210322181007.71519-1-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.25.4
X-Originating-IP: [138.3.201.29]
X-ClientProxiedBy: CH2PR14CA0021.namprd14.prod.outlook.com
 (2603:10b6:610:60::31) To SN6PR10MB3021.namprd10.prod.outlook.com
 (2603:10b6:805:cc::19)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from ban25x6uut29.us.oracle.com (138.3.201.29) by
 CH2PR14CA0021.namprd14.prod.outlook.com (2603:10b6:610:60::31) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3955.18 via Frontend
 Transport; Mon, 22 Mar 2021 18:58:39 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: f6a3fede-6b26-4dc2-dcf8-08d8ed6481ac
X-MS-TrafficTypeDiagnostic: SA2PR10MB4795:
X-Microsoft-Antispam-PRVS: 
 <SA2PR10MB4795040A03C95BD7A65ED60581659@SA2PR10MB4795.namprd10.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:8273;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 WIKlRFJFcrcgFhptEEJlEiv/Ki+oWVlFEcS+frAER2PU3UaZSYtWhogmcl2OSdWs7tKmebEXeCY7WYe8XWz9+ALgW+dSno5aGh4zYYKbSO+91Z1UPckpFT1hsCKHyQo6Z2NEDz6yq2GhzTX4Jat29WHrreoILlcHlQW+7QViAGHf9dNE9c7RbnBTuImT8BCPkWBbl/M9cnxw1sjM0YEJlY278aRdoIXaIBrbOEkN8DBeKJ0rdlKJKLTYYjfn0aBT4T5aWQDmrZFs3AXNBHnRnkCymLZMjEYVYOYAHWpxtZB1PfTmk+kiQW/nY1/duc5eD9g537KYzeGOlyDXnKa13zQ6p0uV2KQ4LLwyyqhgNhuFlCg7VVEIs3dw1MXcpc6pNsDsRki0qDEzB0ADVDBLj7qnmAEH6rQ/dOt07UvMad2brCCuR8iRrjxthnh9DKlGeRMoZU0TUK+aAZphDfbqNv3G7g/gEisMyuVmnm7s7O9P2+/Dr4AYVEmvb0NTmFBQ1vPTZgUHho7HPPrwDGOXxbHlgiDuUm88m8nW+zDG59Lj4L+uj8VhC5OUThRaordTfz3HkNtCK7KFSWwxCDGHr+nhLGEV22Wrm+koUCKc+jBdOJQVV5NMEtqzDWNdpRBMJ1HYB1XZsh/GIhMXa44e5w==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN6PR10MB3021.namprd10.prod.outlook.com;PTR:;CAT:NONE;SFS:(346002)(366004)(136003)(396003)(376002)(39860400002)(6486002)(2906002)(16526019)(186003)(6666004)(26005)(44832011)(5660300002)(66556008)(86362001)(52116002)(4326008)(2616005)(316002)(8936002)(1076003)(7696005)(38100700001)(36756003)(478600001)(66946007)(8676002)(956004)(66476007)(83380400001)(6916009);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 5E+TQhxYEpIoaqKB+PEPJzVujRTk2nen8kCNfLAwSGF5RrwDUC9bPF22gg2tnG1LychOx59ZcdTGpA+IKmbnmQpdHzcDcau4re/vHhEHvO0xQFqUME1oswS3C2TZBcIzwtaWP70MuTSDR3stNsyzk2SAx8Dt3WJcun/LSr0ftM1Wt2/T/2/fUSG/Ldhf+Smp51UFWVbruaPwxT5IEHvYHFB9Jdw3/vLjYQT7YEAsqwVrbHBFoqgtF7a+9Sor0T90qFfex70CNbizOgopZvXHmgNOCtMHvju5C/YJ1bGXVKRH4EaEYH/1058aNlUnGaNFgzlEmv1qGEDPHWmLVo0A2jxS11Yfex7rtsliZI0AOM4lbvASdWK9EVOhA4J5igOmJpfgd9p/OP1r+89L7zfLb0fIHYFdGhgyj8w0ERMXEObMMNq71Ecltvhqs9ygFpM/nD6vzkfQYoxlQeD7n+H0wWZP3DxYuqLPWUnKKW83FY//4pip2toRHb+Jgmhqnt0lR2V5qeufJAIEZupuD2nCCQ86ixZeEjfqEBhUakAaaqJU86YR/K46BpA739nOzx7uGMbUHvM5WWy0omJrsmGC4U0POiisG+yJ7IVeNLVlHAs77pp8n320piFI8XOUe78zSbgCKbA4R7nFjdxrOWbeh9rFqHthPlmwZ6Gm3UNqX4YOel9kmnD+0Yk1FQJxooUfDz7PrWpREtYQBtnOto1b5xpkrNSnX7dYibAUEUOITrjkLwf1YCfdmX8qejHIxsvBJZOPgURK0Dg5q/QEZzMeauxJjHAvLZrLR+PmOA7eRzJ+LW5zRMVANfmbtgSIBC/Ig3/Nv8Vnl7ODojJV1Gu5dazyLj8ghv4RMFYcxq5KYjYTbYCnUKfDICyxeoqVTM/LsoLibqXjUt9l924yjhStrbMgGBR+eBsvW4+8U52qi0yKHqeY9qXZYuxi1LeO9imdZGLWAdmOmur6DraYG1q52vEETbEGUZJus7S7QiXBBwtt8bN57rWQZMXQP80rOFKQF1YR2LmygCZT/Yp8ymyoI72BoJPZX36ONT4Y9ZI62jpjuTMKVuP+osflbEgosqAWC57rP18bxZaaxcTD0eHN7eiQoV2Tqs65zSYgH7ru7NC5aSCTqfEtT4bRT4wolJ9JlBnlYH8mLQb/CgsMkxduP6qx4FNAFpVx5XC7KwlYs6d494fRZ/hzeI/fd4fYqsTHX6NKIIp4hdJOp4KkfU86luVYKtrKs9sQDU4+spfqYWvSqkR7GIQo5unTjUq4hk83pgpSsLL6MELcWQ2hgl7fP8OAm/3sAU+Xe33Qvsdyupc/uLR5a84am39pVnwWyVnf
X-OriginatorOrg: oracle.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 f6a3fede-6b26-4dc2-dcf8-08d8ed6481ac
X-MS-Exchange-CrossTenant-AuthSource: SN6PR10MB3021.namprd10.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 22 Mar 2021 18:58:40.3116
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 4e2c6054-71cb-48f1-bd6c-3a9705aca71b
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 u71ULm71LEDdQk1DJ8+HXF+6JSNC1QZeyUSpvP62vzNcDjZbdPAHO8zL1X4/oTY/4qAOA7O4evDYQl49x1EcHw3MdYJFa/3+pGzQ2ilOG0E=
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SA2PR10MB4795
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9931
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 adultscore=0
 malwarescore=0 spamscore=0
 mlxscore=0 phishscore=0 suspectscore=0 mlxlogscore=791 bulkscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2103220136
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9931
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 adultscore=0
 malwarescore=0 mlxscore=0
 priorityscore=1501 bulkscore=0 impostorscore=0 lowpriorityscore=0
 phishscore=0 mlxlogscore=988 suspectscore=0 clxscore=1015 spamscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2103220136
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

v3 -> v4:
        1. Patch# 1 fixes the problem differently from what v3 did. In the new
           fix, svm_vcpu_run() for L1 first checks if the previous #VMEXIT from
           L2 was a VMRUN #VMEXIT and if that VMRUN is being single-stepped. If
           both of these conditions are satisfied, it synthesizes a #DB 
           intercept to account for the pending RFLAGS.TF. This prevents the
           instruction next to VMRUN from being executed before taking care of
           the pending RFLAGS.TF.
        2. in Patch# 4, in host_rflags_test(), the call to vmmcall() has been
           moved down. 

[PATCH 1/4 v4] KVM: nSVM: Trigger synthetic #DB intercept following completion of single-stepped VMRUN instruction
[PATCH 2/4 v4] KVM: X86: Add a utility function to read current RIP
[PATCH 3/4 v4] nSVM: Add assembly label to VMRUN instruction
[PATCH 4/4 v4] nSVM: Test effect of host RFLAGS.TF on VMRUN

 arch/x86/kvm/svm/svm.c | 15 +++++++++++++++
 1 file changed, 15 insertions(+)

Krish Sadhukhan (1):
      KVM: Trigger synthetic #DB intercept following completion of single-stepped VMRUN instruction

 lib/x86/processor.h |   7 ++++
 x86/svm.c           |  16 ++++++--
 x86/svm_tests.c     | 115 ++++++++++++++++++++++++++++++++++++++++++++++++++++
 3 files changed, 134 insertions(+), 4 deletions(-)

Krish Sadhukhan (3):
      KVM: X86: Add a utility function to read current RIP
      KVM: nSVM: Add assembly label to VMRUN instruction
      nSVM: Test effect of host RFLAGS.TF on VMRUN
```
