

#### [PATCH V5 00/15] KVM: MIPS: Add Loongson-3 support (Host Side)
##### From: Huacai Chen <chenhc@lemote.com>

```c
From patchwork Wed May 13 08:42:31 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Huacai Chen <chenhc@lemote.com>
X-Patchwork-Id: 11545353
Return-Path: <SRS0=Sfx5=63=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 28EE114C0
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 13 May 2020 08:42:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1207720769
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 13 May 2020 08:42:41 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="BPe0yXCW"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732330AbgEMImk (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 13 May 2020 04:42:40 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:38696 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726092AbgEMImk (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 13 May 2020 04:42:40 -0400
Received: from mail-pg1-x541.google.com (mail-pg1-x541.google.com
 [IPv6:2607:f8b0:4864:20::541])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 1499CC061A0C;
        Wed, 13 May 2020 01:42:40 -0700 (PDT)
Received: by mail-pg1-x541.google.com with SMTP id n11so7474931pgl.9;
        Wed, 13 May 2020 01:42:40 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id;
        bh=fVefEu093xh7eZgov8vcbtYrPYBZHyOWLgcytUR5N6w=;
        b=BPe0yXCWZdQh00SOsRIYzYvEnqSGMWBKRRh42Sx4ThYuVO2bL3Ncpy20sIEKFeiKci
         nq2ljWW1fu7btXEDv1vJ0ojL4oBRK+3TU/JsdxQa7UlbUommg5l0wjE6F1B0Iwjt4iJe
         Lubz0EbH5qbBz/WgMef3Yjob8F9KA102D4Pmr4hetRG2jKAgXhGGTp9arGQAaKlv9iRt
         seE1+3OQjFs4KcWIVeF0c6daN0a3068XWFbfPrWXvAgLxc1hm0D4PBQWBt6WCecpFObw
         6AAbA6ujX/Zcqa4+3ccLk19kpmqrA2krGVPGL9EBt4NJYTmkVlQMiF+/syDofIas9pIc
         tuWg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id;
        bh=fVefEu093xh7eZgov8vcbtYrPYBZHyOWLgcytUR5N6w=;
        b=ImkDkvRkqg5EOl5FoBJ+nxtHWofUlef+mmXQ20KcMCHSPQac+kHd0SGExudtBVYEk6
         R7NyZIicXdekpfzXg2FA+tyeO3Zs9OVkZy9MCijxQ+nZDKOD3Yvp3kY1F5PhgIJiD6sc
         DPGSGM87HJpqthGymShVK9PR0tf5XaeZCoMWz4Ng4y7TDZMZDOSAe0YzkR98K4vi/JVy
         PM7dFm+uGiFWz+VwG3xgdzW8AQywsEWQtUTHXFHiv1Q02D+87RZ4wTr1WHhlqfuhoSy0
         gF3+JwZTeQgGjraHGM8cOmc8x+QkVsZlOcLUKydqNiGwkrOX2a+zanFEYqLVztxsE12G
         wE+Q==
X-Gm-Message-State: AGi0PuZKC3XgLx1LtU+dJV0diagSKyKhMSktQfXAnfJEIrfLF/EHYaAf
        Yw23ukYe+XPcTLFVgMrUdp4=
X-Google-Smtp-Source: 
 APiQypJh7/gq6dGqLnTOpjc3yLkAoDsgAd3blvRoL1dAV2zBjuqp8ZGq7OTY+AF+t2C0KkPWXqgmDQ==
X-Received: by 2002:aa7:957c:: with SMTP id x28mr25165250pfq.31.1589359359627;
        Wed, 13 May 2020 01:42:39 -0700 (PDT)
Received: from software.domain.org (28.144.92.34.bc.googleusercontent.com.
 [34.92.144.28])
        by smtp.gmail.com with ESMTPSA id
 o21sm14645570pjr.37.2020.05.13.01.42.36
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Wed, 13 May 2020 01:42:39 -0700 (PDT)
From: Huacai Chen <chenhc@lemote.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Thomas Bogendoerfer <tsbogend@alpha.franken.de>,
        Aleksandar Markovic <aleksandar.qemu.devel@gmail.com>
Cc: kvm@vger.kernel.org, linux-mips@vger.kernel.org,
        Fuxin Zhang <zhangfx@lemote.com>,
        Huacai Chen <chenhuacai@gmail.com>,
        Jiaxun Yang <jiaxun.yang@flygoat.com>,
        Huacai Chen <chenhc@lemote.com>
Subject: [PATCH V5 00/15] KVM: MIPS: Add Loongson-3 support (Host Side)
Date: Wed, 13 May 2020 16:42:31 +0800
Message-Id: <1589359366-1669-1-git-send-email-chenhc@lemote.com>
X-Mailer: git-send-email 2.7.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We are preparing to add KVM support for Loongson-3. VZ extension is
fully supported in Loongson-3A R4+, and we will not care about old CPUs
(at least now). We already have a full functional Linux kernel (based
on Linux-5.4.x LTS) and QEMU (based on 5.0.0) and their git repositories
are here:

QEMU: https://github.com/chenhuacai/qemu
Kernel: https://github.com/chenhuacai/linux

Of course these two repositories need to be rework and not suitable for
upstream (especially the commits need to be splitted). We show them here
is just to tell others what we have done, and how KVM/Loongson will look
like.

Our plan is make the KVM host side be upstream first, and after that,
we will make the KVM guest side and QEMU emulator be upstream.

V1 -> V2:
1, Remove "mips: define pud_index() regardless of page table folding"
   because it has been applied.
2, Make Loongson-specific code be guarded by CONFIG_CPU_LOONGSON64.

V2 -> V3:
1, Emulate a reduced feature list of CPUCFG.
2, Fix all possible checkpatch.pl errors and warnings.

V3 -> V4:
1, Emulate LOONGSON_CFG0/LOONGSON_CFG3 in CPUCFG correctly.
2, Update commit messages to explain Loongson-3 Virtual IPI.
3, Add Reviewed-by: Aleksandar Markovic <aleksandar.qemu.devel@gmail.com>.

V4 -> V5:
1, Fix a typo.
2, Update MAINTAINERS.

Xing Li(2):
 KVM: MIPS: Define KVM_ENTRYHI_ASID to cpu_asid_mask(&boot_cpu_data)
 KVM: MIPS: Fix VPN2_MASK definition for variable cpu_vmbits

Huacai Chen(13):
 KVM: MIPS: Increase KVM_MAX_VCPUS and KVM_USER_MEM_SLOTS to 16
 KVM: MIPS: Add EVENTFD support which is needed by VHOST
 KVM: MIPS: Use lddir/ldpte instructions to lookup gpa_mm.pgd
 KVM: MIPS: Introduce and use cpu_guest_has_ldpte
 KVM: MIPS: Use root tlb to control guest's CCA for Loongson-3
 KVM: MIPS: Let indexed cacheops cause guest exit on Loongson-3
 KVM: MIPS: Add more types of virtual interrupts
 KVM: MIPS: Add Loongson-3 Virtual IPI interrupt support
 KVM: MIPS: Add CPUCFG emulation for Loongson-3
 KVM: MIPS: Add CONFIG6 and DIAG registers emulation
 KVM: MIPS: Add more MMIO load/store instructions emulation
 KVM: MIPS: Enable KVM support for Loongson-3
 MAINTAINERS: Update KVM/MIPS maintainers

Signed-off-by: Huacai Chen <chenhc@lemote.com>
---
 MAINTAINERS                          |   4 +-
 arch/mips/Kconfig                    |   1 +
 arch/mips/include/asm/cpu-features.h |   3 +
 arch/mips/include/asm/kvm_host.h     |  52 +++-
 arch/mips/include/asm/mipsregs.h     |   7 +
 arch/mips/include/uapi/asm/inst.h    |  11 +
 arch/mips/kernel/cpu-probe.c         |   2 +
 arch/mips/kvm/Kconfig                |   1 +
 arch/mips/kvm/Makefile               |   5 +-
 arch/mips/kvm/emulate.c              | 503 ++++++++++++++++++++++++++++++++++-
 arch/mips/kvm/entry.c                |  19 +-
 arch/mips/kvm/interrupt.c            |  93 +------
 arch/mips/kvm/interrupt.h            |  14 +-
 arch/mips/kvm/loongson_ipi.c         | 214 +++++++++++++++
 arch/mips/kvm/mips.c                 |  49 +++-
 arch/mips/kvm/tlb.c                  |  41 +++
 arch/mips/kvm/trap_emul.c            |   3 +
 arch/mips/kvm/vz.c                   | 237 ++++++++++++-----
 18 files changed, 1092 insertions(+), 167 deletions(-)
 create mode 100644 arch/mips/kvm/loongson_ipi.c
--
2.7.0
```
#### [RFC PATCH v2 0/4] vfio-ccw: Fix interrupt handling for HALT/CLEAR
##### From: Eric Farman <farman@linux.ibm.com>

```c
From patchwork Wed May 13 14:29:30 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Farman <farman@linux.ibm.com>
X-Patchwork-Id: 11546551
Return-Path: <SRS0=Sfx5=63=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DE43F60D
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 13 May 2020 14:29:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 761152065C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 13 May 2020 14:29:45 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388997AbgEMO3o (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 13 May 2020 10:29:44 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:53252 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S2388790AbgEMO3m (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 13 May 2020 10:29:42 -0400
Received: from pps.filterd (m0098421.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 04DEAo62156622;
        Wed, 13 May 2020 10:29:41 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 3101knnxk6-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 13 May 2020 10:29:41 -0400
Received: from m0098421.ppops.net (m0098421.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 04DEBLQ4158639;
        Wed, 13 May 2020 10:29:40 -0400
Received: from ppma03ams.nl.ibm.com (62.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.98])
        by mx0a-001b2d01.pphosted.com with ESMTP id 3101knnxje-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 13 May 2020 10:29:40 -0400
Received: from pps.filterd (ppma03ams.nl.ibm.com [127.0.0.1])
        by ppma03ams.nl.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 04DEL5fd015403;
        Wed, 13 May 2020 14:29:39 GMT
Received: from b06avi18626390.portsmouth.uk.ibm.com
 (b06avi18626390.portsmouth.uk.ibm.com [9.149.26.192])
        by ppma03ams.nl.ibm.com with ESMTP id 3100ub9rgv-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 13 May 2020 14:29:38 +0000
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06avi18626390.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 04DESPjt25035040
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 13 May 2020 14:28:25 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 14DD2A4066;
        Wed, 13 May 2020 14:29:36 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id EC722A405F;
        Wed, 13 May 2020 14:29:35 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTPS;
        Wed, 13 May 2020 14:29:35 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 4958)
        id A4F0BE02B1; Wed, 13 May 2020 16:29:35 +0200 (CEST)
From: Eric Farman <farman@linux.ibm.com>
To: Cornelia Huck <cohuck@redhat.com>
Cc: Jared Rossi <jrossi@linux.ibm.com>,
        Halil Pasic <pasic@linux.ibm.com>, linux-s390@vger.kernel.org,
        kvm@vger.kernel.org, Eric Farman <farman@linux.ibm.com>
Subject: [RFC PATCH v2 0/4] vfio-ccw: Fix interrupt handling for HALT/CLEAR
Date: Wed, 13 May 2020 16:29:30 +0200
Message-Id: <20200513142934.28788-1-farman@linux.ibm.com>
X-Mailer: git-send-email 2.17.1
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.216,18.0.676
 definitions=2020-05-13_06:2020-05-13,2020-05-13 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 malwarescore=0
 impostorscore=0 lowpriorityscore=0 mlxscore=0 bulkscore=0
 cotscore=-2147483648 mlxlogscore=999 adultscore=0 clxscore=1015
 suspectscore=0 spamscore=0 phishscore=0 priorityscore=1501 classifier=spam
 adjust=0 reason=mlx scancount=1 engine=8.12.0-2004280000
 definitions=main-2005130121
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Conny,

Back in January, I suggested a small patch [1] to try to clean up
the handling of HSCH/CSCH interrupts, especially as it relates to
concurrent SSCH interrupts. Here is a new attempt to address this.

There was some suggestion earlier about locking the FSM, but I'm not
seeing any problems with that. Rather, what I'm noticing is that the
flow between a synchronous START and asynchronous HALT/CLEAR have
different impacts on the FSM state. Consider:

    CPU 1                           CPU 2

    SSCH (set state=CP_PENDING)
    INTERRUPT (set state=IDLE)
    CSCH (no change in state)
                                    SSCH (set state=CP_PENDING)
    INTERRUPT (set state=IDLE)
                                    INTERRUPT (set state=IDLE)

The second interrupt on CPU 1 will call cp_free() for the START
created by CPU 2, and our results will be, um, messy. This
suggests that three things must be true:

 A) cp_free() must be called for either a final interrupt,
or a failure issuing a SSCH
 B) The FSM state must only be set to IDLE once cp_free()
has been called
 C) A SSCH cannot be issued while an interrupt is outstanding

It's not great that items B and C are separated in the interrupt
path by a mutex boundary where the copy into io_region occurs.
We could (and perhaps should) move them together, which would
improve things somewhat, but still doesn't address the scenario
laid out above. Even putting that work within the mutex window
during interrupt processing doesn't address things totally.

So, the patches here do two things. One to handle unsolicited
interrupts [2], which I think is pretty straightforward. Though,
it does make me want to do a more drastic rearranging of the
affected function. :)

The other warrants some discussion, since it's sort of weird.
Basically, recognize what commands we've issued, expect interrupts
for each, and prevent new SSCH's while asynchronous commands are
pending. It doesn't address interrupts from the HSCH/CSCH that
could be generated by the Channel Path Handling code [3] for an
offline CHPID yet, and it needs some TLC to make checkpatch happy.
But it's the best possibility I've seen thus far.

I used private->scsw for this because it's barely used for anything
else; at one point I had been considering removing it outright because
we have entirely too many SCSW's in this code. :) I could implement
this as three small flags in private, to simplify the code and avoid
confusion with the different fctl/actl flags in private vs schib.

It does make me wonder whether the CP_PENDING check before cp_free()
is still necessary, but that's a query for a later date.

Also, perhaps this could be accomplished with two new FSM states,
one for a HALT and one for a CLEAR. I put it aside because the
interrupt handler got a little hairy with that, but I'm still looking
at it in parallel to this discussion.

I look forward to hearing your thoughts...

[1] https://lore.kernel.org/kvm/20200124145455.51181-1-farman@linux.ibm.com/
[2] https://lore.kernel.org/kvm/9635c45f-4652-c837-d256-46f426737a5e@linux.ibm.com/
[3] https://lore.kernel.org/kvm/20200505122745.53208-1-farman@linux.ibm.com/

Eric Farman (4):
  vfio-ccw: Do not reset FSM state for unsolicited interrupts
  vfio-ccw: Utilize scsw actl to serialize start operations
  vfio-ccw: Expand SCSW usage to HALT and CLEAR
  vfio-ccw: Clean up how to react to a failed START

 drivers/s390/cio/vfio_ccw_drv.c | 10 +++++++++-
 drivers/s390/cio/vfio_ccw_fsm.c | 26 ++++++++++++++++++++++++++
 drivers/s390/cio/vfio_ccw_ops.c |  3 +--
 3 files changed, 36 insertions(+), 3 deletions(-)
```
#### [PATCH Kernel v19 0/8] Add UAPIs to support migration for VFIO
##### From: Kirti Wankhede <kwankhede@nvidia.com>

```c
From patchwork Wed May 13 20:04:31 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kirti Wankhede <kwankhede@nvidia.com>
X-Patchwork-Id: 11547215
Return-Path: <SRS0=Sfx5=63=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9AC1C739
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 13 May 2020 20:37:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B558720675
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 13 May 2020 20:37:54 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=nvidia.com header.i=@nvidia.com
 header.b="nUT49zw2"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728053AbgEMUhx (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 13 May 2020 16:37:53 -0400
Received: from hqnvemgate24.nvidia.com ([216.228.121.143]:15816 "EHLO
        hqnvemgate24.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727118AbgEMUhw (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 13 May 2020 16:37:52 -0400
Received: from hqpgpgate101.nvidia.com (Not Verified[216.228.121.13]) by
 hqnvemgate24.nvidia.com (using TLS: TLSv1.2, DES-CBC3-SHA)
        id <B5ebc5a170000>; Wed, 13 May 2020 13:35:35 -0700
Received: from hqmail.nvidia.com ([172.20.161.6])
  by hqpgpgate101.nvidia.com (PGP Universal service);
  Wed, 13 May 2020 13:37:52 -0700
X-PGP-Universal: processed;
        by hqpgpgate101.nvidia.com on Wed, 13 May 2020 13:37:52 -0700
Received: from HQMAIL107.nvidia.com (172.20.187.13) by HQMAIL109.nvidia.com
 (172.20.187.15) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Wed, 13 May
 2020 20:37:51 +0000
Received: from kwankhede-dev.nvidia.com (172.20.13.39) by HQMAIL107.nvidia.com
 (172.20.187.13) with Microsoft SMTP Server (TLS) id 15.0.1473.3 via Frontend
 Transport; Wed, 13 May 2020 20:37:45 +0000
From: Kirti Wankhede <kwankhede@nvidia.com>
To: <alex.williamson@redhat.com>, <cjia@nvidia.com>
CC: <kevin.tian@intel.com>, <ziye.yang@intel.com>,
        <changpeng.liu@intel.com>, <yi.l.liu@intel.com>,
        <mlevitsk@redhat.com>, <eskultet@redhat.com>, <cohuck@redhat.com>,
        <dgilbert@redhat.com>, <jonathan.davies@nutanix.com>,
        <eauger@redhat.com>, <aik@ozlabs.ru>, <pasic@linux.ibm.com>,
        <felipe@nutanix.com>, <Zhengxiao.zx@Alibaba-inc.com>,
        <shuangtai.tst@alibaba-inc.com>, <Ken.Xue@amd.com>,
        <zhi.a.wang@intel.com>, <yan.y.zhao@intel.com>,
        <qemu-devel@nongnu.org>, <kvm@vger.kernel.org>,
        Kirti Wankhede <kwankhede@nvidia.com>
Subject: [PATCH Kernel v19 0/8] Add UAPIs to support migration for VFIO
 devices
Date: Thu, 14 May 2020 01:34:31 +0530
Message-ID: <1589400279-28522-1-git-send-email-kwankhede@nvidia.com>
X-Mailer: git-send-email 2.7.0
X-NVConfidentiality: public
MIME-Version: 1.0
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1589402135; bh=R0qhKuak5cLSlgSFd5CJC4ZHNh6o1/by9wgg+Kh6gQY=;
        h=X-PGP-Universal:From:To:CC:Subject:Date:Message-ID:X-Mailer:
         X-NVConfidentiality:MIME-Version:Content-Type;
        b=nUT49zw2bPZZw6bdi6JdX2TD3lv0mP+p64xaIa0ngGoRvp5Hcqnp2Q09d8dPhHsgw
         RBeH86wv55JNBbLYyodz0c6D1vD2bkbHy3zP0ntuxa0wnaSvYWkdU4aOJ8zKFiMRTR
         mklUSw2PQmqB85RPCSIBU0omfdQ8+WeiqPnm8BrjzvlkjyrM/XJAyeUqovlErXqklI
         PeBsgKbXm9NERGaK9nI7yKr92o/Cm3IZ50uUiOwKtNO+uuKAyUSl4UXX+Ofvjcfhie
         2pZ4SJoTsI3mmheJUVh2mGSnQ1CAgVrc6cwaY3NUbB7av3WMd+0oOcP5B29WqlDH8y
         Ko6Lak1Wzc9Ag==
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

This patch set adds:
* IOCTL VFIO_IOMMU_DIRTY_PAGES to get dirty pages bitmap with
  respect to IOMMU container rather than per device. All pages pinned by
  vendor driver through vfio_pin_pages external API has to be marked as
  dirty during  migration. When IOMMU capable device is present in the
  container and all pages are pinned and mapped, then all pages are marked
  dirty.
  When there are CPU writes, CPU dirty page tracking can identify dirtied
  pages, but any page pinned by vendor driver can also be written by
  device. As of now there is no device which has hardware support for
  dirty page tracking. So all pages which are pinned should be considered
  as dirty.
  This ioctl is also used to start/stop dirty pages tracking for pinned and
  unpinned pages while migration is active.

* Updated IOCTL VFIO_IOMMU_UNMAP_DMA to get dirty pages bitmap before
  unmapping IO virtual address range.
  With vIOMMU, during pre-copy phase of migration, while CPUs are still
  running, IO virtual address unmap can happen while device still keeping
  reference of guest pfns. Those pages should be reported as dirty before
  unmap, so that VFIO user space application can copy content of those
  pages from source to destination.

* Patch 8 detect if IOMMU capable device driver is smart to report pages
  to be marked dirty by pinning pages using vfio_pin_pages() API.


Yet TODO:
Since there is no device which has hardware support for system memmory
dirty bitmap tracking, right now there is no other API from vendor driver
to VFIO IOMMU module to report dirty pages. In future, when such hardware
support will be implemented, an API will be required such that vendor
driver could report dirty pages to VFIO module during migration phases.

Adding revision history from previous QEMU patch set to understand KABI
changes done till now

v18 -> v19
- Updated migration capability with supported page sizes bitmap for dirty
  page tracking and  maximum bitmap size supported by kernel module.
- Added patch to calculate and cache pgsize_bitmap when iommu->domain_list
  is updated.
- Removed extra buffers added in previous version for bitmap manipulation
  and optimised the code.

v17 -> v18
- Add migration capability to the capability chain for VFIO_IOMMU_GET_INFO
  ioctl
- Updated UMAP_DMA ioctl to return bitmap of multiple vfio_dma

v16 -> v17
- Fixed errors reported by kbuild test robot <lkp@intel.com> on i386

v15 -> v16
- Minor edits and nit picks (Auger Eric)
- On copying bitmap to user, re-populated bitmap only for pinned pages,
  excluding unmapped pages and CPU dirtied pages.
- Patches are on tag: next-20200318 and 1-3 patches from Yan's series
  https://lkml.org/lkml/2020/3/12/1255

v14 -> v15
- Minor edits and nit picks.
- In the verification of user allocated bitmap memory, added check of
   maximum size.
- Patches are on tag: next-20200318 and 1-3 patches from Yan's series
  https://lkml.org/lkml/2020/3/12/1255

v13 -> v14
- Added struct vfio_bitmap to kabi. updated structure
  vfio_iommu_type1_dirty_bitmap_get and vfio_iommu_type1_dma_unmap.
- All small changes suggested by Alex.
- Patches are on tag: next-20200318 and 1-3 patches from Yan's series
  https://lkml.org/lkml/2020/3/12/1255

v12 -> v13
- Changed bitmap allocation in vfio_iommu_type1 to per vfio_dma
- Changed VFIO_IOMMU_DIRTY_PAGES ioctl behaviour to be per vfio_dma range.
- Changed vfio_iommu_type1_dirty_bitmap structure to have separate data
  field.

v11 -> v12
- Changed bitmap allocation in vfio_iommu_type1.
- Remove atomicity of ref_count.
- Updated comments for migration device state structure about error
  reporting.
- Nit picks from v11 reviews

v10 -> v11
- Fix pin pages API to free vpfn if it is marked as unpinned tracking page.
- Added proposal to detect if IOMMU capable device calls external pin pages
  API to mark pages dirty.
- Nit picks from v10 reviews

v9 -> v10:
- Updated existing VFIO_IOMMU_UNMAP_DMA ioctl to get dirty pages bitmap
  during unmap while migration is active
- Added flag in VFIO_IOMMU_GET_INFO to indicate driver support dirty page
  tracking.
- If iommu_mapped, mark all pages dirty.
- Added unpinned pages tracking while migration is active.
- Updated comments for migration device state structure with bit
  combination table and state transition details.

v8 -> v9:
- Split patch set in 2 sets, Kernel and QEMU.
- Dirty pages bitmap is queried from IOMMU container rather than from
  vendor driver for per device. Added 2 ioctls to achieve this.

v7 -> v8:
- Updated comments for KABI
- Added BAR address validation check during PCI device's config space load
  as suggested by Dr. David Alan Gilbert.
- Changed vfio_migration_set_state() to set or clear device state flags.
- Some nit fixes.

v6 -> v7:
- Fix build failures.

v5 -> v6:
- Fix build failure.

v4 -> v5:
- Added decriptive comment about the sequence of access of members of
  structure vfio_device_migration_info to be followed based on Alex's
  suggestion
- Updated get dirty pages sequence.
- As per Cornelia Huck's suggestion, added callbacks to VFIODeviceOps to
  get_object, save_config and load_config.
- Fixed multiple nit picks.
- Tested live migration with multiple vfio device assigned to a VM.

v3 -> v4:
- Added one more bit for _RESUMING flag to be set explicitly.
- data_offset field is read-only for user space application.
- data_size is read for every iteration before reading data from migration,
  that is removed assumption that data will be till end of migration
  region.
- If vendor driver supports mappable sparsed region, map those region
  during setup state of save/load, similarly unmap those from cleanup
  routines.
- Handles race condition that causes data corruption in migration region
  during save device state by adding mutex and serialiaing save_buffer and
  get_dirty_pages routines.
- Skip called get_dirty_pages routine for mapped MMIO region of device.
- Added trace events.
- Split into multiple functional patches.

v2 -> v3:
- Removed enum of VFIO device states. Defined VFIO device state with 2
  bits.
- Re-structured vfio_device_migration_info to keep it minimal and defined
  action on read and write access on its members.

v1 -> v2:
- Defined MIGRATION region type and sub-type which should be used with
  region type capability.
- Re-structured vfio_device_migration_info. This structure will be placed
  at 0th offset of migration region.
- Replaced ioctl with read/write for trapped part of migration region.
- Added both type of access support, trapped or mmapped, for data section
  of the region.
- Moved PCI device functions to pci file.
- Added iteration to get dirty page bitmap until bitmap for all requested
  pages are copied.

Thanks,
Kirti



Kirti Wankhede (8):
  vfio: UAPI for migration interface for device state
  vfio iommu: Remove atomicity of ref_count of pinned pages
  vfio iommu: Cache pgsize_bitmap in struct vfio_iommu
  vfio iommu: Add ioctl definition for dirty pages tracking.
  vfio iommu: Implementation of ioctl for dirty pages tracking
  vfio iommu: Update UNMAP_DMA ioctl to get dirty bitmap before unmap
  vfio iommu: Add migration capability to report supported features
  vfio: Selective dirty page tracking if IOMMU backed device pins pages

 drivers/vfio/vfio.c             |  13 +-
 drivers/vfio/vfio_iommu_type1.c | 570 ++++++++++++++++++++++++++++++++++++----
 include/linux/vfio.h            |   4 +-
 include/uapi/linux/vfio.h       | 315 ++++++++++++++++++++++
 4 files changed, 842 insertions(+), 60 deletions(-)
```
#### [PATCH v6 0/2] Use DIAG318 to set Control Program Name & Version
##### From: Collin Walling <walling@linux.ibm.com>

```c
From patchwork Wed May 13 22:15:55 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Collin Walling <walling@linux.ibm.com>
X-Patchwork-Id: 11547395
Return-Path: <SRS0=Sfx5=63=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6FE6A90
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 13 May 2020 22:17:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2E938205ED
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 13 May 2020 22:17:22 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731016AbgEMWRU (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 13 May 2020 18:17:20 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:25416 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1730276AbgEMWRU (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 13 May 2020 18:17:20 -0400
Received: from pps.filterd (m0098404.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 04DM2tHW020466;
        Wed, 13 May 2020 18:17:19 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 31016mafm5-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 13 May 2020 18:17:19 -0400
Received: from m0098404.ppops.net (m0098404.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 04DM3r0n026330;
        Wed, 13 May 2020 18:17:19 -0400
Received: from ppma02dal.us.ibm.com (a.bd.3ea9.ip4.static.sl-reverse.com
 [169.62.189.10])
        by mx0a-001b2d01.pphosted.com with ESMTP id 31016mafkw-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 13 May 2020 18:17:19 -0400
Received: from pps.filterd (ppma02dal.us.ibm.com [127.0.0.1])
        by ppma02dal.us.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 04DMEtqP002407;
        Wed, 13 May 2020 22:17:18 GMT
Received: from b01cxnp23034.gho.pok.ibm.com (b01cxnp23034.gho.pok.ibm.com
 [9.57.198.29])
        by ppma02dal.us.ibm.com with ESMTP id 3100uc4fjn-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 13 May 2020 22:17:18 +0000
Received: from b01ledav006.gho.pok.ibm.com (b01ledav006.gho.pok.ibm.com
 [9.57.199.111])
        by b01cxnp23034.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id 04DMHFlZ40239508
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 13 May 2020 22:17:15 GMT
Received: from b01ledav006.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 9FA59AC059;
        Wed, 13 May 2020 22:17:15 +0000 (GMT)
Received: from b01ledav006.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 76974AC05B;
        Wed, 13 May 2020 22:17:15 +0000 (GMT)
Received: from localhost.localdomain.com (unknown [9.85.196.213])
        by b01ledav006.gho.pok.ibm.com (Postfix) with ESMTP;
        Wed, 13 May 2020 22:17:15 +0000 (GMT)
From: Collin Walling <walling@linux.ibm.com>
To: kvm@vger.kernel.org, linux-s390@vger.kernel.org
Cc: pbonzini@redhat.com, borntraeger@de.ibm.com, frankja@linux.ibm.com,
        david@redhat.com, cohuck@redhat.com, imbrenda@linux.ibm.com,
        heiko.carstens@de.ibm.com, gor@linux.ibm.com
Subject: [PATCH v6 0/2] Use DIAG318 to set Control Program Name & Version
 Codes
Date: Wed, 13 May 2020 18:15:55 -0400
Message-Id: <20200513221557.14366-1-walling@linux.ibm.com>
X-Mailer: git-send-email 2.21.3
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.216,18.0.676
 definitions=2020-05-13_09:2020-05-13,2020-05-13 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 phishscore=0 lowpriorityscore=0 mlxscore=0 mlxlogscore=999 bulkscore=0
 malwarescore=0 adultscore=0 spamscore=0 clxscore=1011 impostorscore=0
 cotscore=-2147483648 suspectscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-2004280000 definitions=main-2005130188
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Changelog:

    v6
	- KVM disables diag318 get/set by default
	- added new IOCTL to tell KVM to enable diag318
	- removed VCPU event message in favor of VM_EVENT only

    v5
        - s/cpc/diag318_info in order to make the relevant data more clear
        - removed mutex locks for diag318_info get/set

    v4
        - removed setup.c changes introduced in bullet 1 of v3
        - kept diag318_info struct cleanup
        - analogous QEMU patches:
            https://lists.gnu.org/archive/html/qemu-devel/2019-05/msg00164.html

    v3
        - kernel patch for diag 0x318 instruction call fixup [removed in v4]
        - removed CPU model code
        - cleaned up diag318_info struct
        - cpnc is no longer unshadowed as it was not needed
        - rebased on 5.1.0-rc3

This instruction call is executed once-and-only-once during Kernel setup.
The availability of this instruction depends on Read Info byte 134, bit 0.

DIAG 318's functionality is also emulated by KVM, which means we can enable 
this feature for a guest even if the host kernel cannot support it. This
feature is made available starting with the zEC12-full model (see analogous
QEMU patches).

The diag318_info is composed of a Control Program Name Code (CPNC) and a
Control Program Version Code (CPVC). These values are used for problem 
diagnosis and allows IBM to identify control program information by answering 
the following question:

    "What environment is this guest running in?" (CPNC)
    "What are more details regarding the OS?" (CPVC)

In the future, we will implement the CPVC to convey more information about the 
OS. For now, we set this field to 0 until we come up with a solid plan.

Collin Walling (2):
  s390/setup: diag318: refactor struct
  s390/kvm: diagnose 318 handling

 Documentation/virt/kvm/devices/vm.rst | 29 +++++++++
 arch/s390/include/asm/diag.h          |  6 +-
 arch/s390/include/asm/kvm_host.h      |  6 +-
 arch/s390/include/uapi/asm/kvm.h      |  5 ++
 arch/s390/kernel/setup.c              |  3 +-
 arch/s390/kvm/diag.c                  | 20 ++++++
 arch/s390/kvm/kvm-s390.c              | 89 +++++++++++++++++++++++++++
 arch/s390/kvm/kvm-s390.h              |  1 +
 arch/s390/kvm/vsie.c                  |  2 +
 9 files changed, 154 insertions(+), 7 deletions(-)
```
