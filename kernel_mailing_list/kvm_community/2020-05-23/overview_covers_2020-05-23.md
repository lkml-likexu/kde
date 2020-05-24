

#### [PATCH 0/3] kvm-unit-tests: nVMX: Test base and limit fields of guest
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
From patchwork Sat May 23 00:26:00 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11566463
Return-Path: <SRS0=+Aw4=7F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8C35260D
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 23 May 2020 01:07:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 74E81206B6
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 23 May 2020 01:07:19 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="PxmMRfDo"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2387533AbgEWBHT (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 22 May 2020 21:07:19 -0400
Received: from userp2120.oracle.com ([156.151.31.85]:40938 "EHLO
        userp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2387531AbgEWBHS (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 22 May 2020 21:07:18 -0400
Received: from pps.filterd (userp2120.oracle.com [127.0.0.1])
        by userp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 04N11WLh086549;
        Sat, 23 May 2020 01:07:05 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : mime-version : content-transfer-encoding;
 s=corp-2020-01-29; bh=xvJpkd0McCUwHK7qpMaBTPqSG76xUVmhav7yoJ2Qv7A=;
 b=PxmMRfDot+eXp5xyLu0rnQKo4UGvzPUJpec46aoeXM/DFed0rdLJ5zF6yWu3QC32az2t
 4yDBdbuXIc++XnZSEtn+Ab+PUJjqDcSMb72mf9vi3smPVOetz5mMB4pn4rKPjDA2C644
 SFml8v5DJzzAsIRce3sdOFzgPcYOtVETUeR2U1lC5J40P+hBSKFW8m1spncMZdDE2YCX
 u4URk3itdYwmOV/FJP8J+6+39/5nimagm9lWZUmVN5HnlLYuwJubBBGEskWozQvazVKY
 mgqktV0Att7OUvm6P/94skPcTwOIRdV/cPKD1FIyxvvue4r8Wt7OwN8rFjezOXvdvhME Pg==
Received: from userp3030.oracle.com (userp3030.oracle.com [156.151.31.80])
        by userp2120.oracle.com with ESMTP id 316qrvr7bp-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=FAIL);
        Sat, 23 May 2020 01:07:05 +0000
Received: from pps.filterd (userp3030.oracle.com [127.0.0.1])
        by userp3030.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 04N12ZKr148105;
        Sat, 23 May 2020 01:07:04 GMT
Received: from aserv0122.oracle.com (aserv0122.oracle.com [141.146.126.236])
        by userp3030.oracle.com with ESMTP id 316rxqspe5-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Sat, 23 May 2020 01:07:04 +0000
Received: from abhmp0006.oracle.com (abhmp0006.oracle.com [141.146.116.12])
        by aserv0122.oracle.com (8.14.4/8.14.4) with ESMTP id 04N173oi006845;
        Sat, 23 May 2020 01:07:03 GMT
Received: from ban25x6uut29.us.oracle.com (/10.153.73.29)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Fri, 22 May 2020 18:07:03 -0700
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com,
        sean.j.christopherson@intel.com
Subject: [PATCH 0/3] kvm-unit-tests: nVMX: Test base and limit fields of guest
 GDTR and IDTR
Date: Fri, 22 May 2020 20:26:00 -0400
Message-Id: <20200523002603.32450-1-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9629
 signatures=668686
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=13
 mlxlogscore=746
 phishscore=0 spamscore=0 adultscore=0 bulkscore=0 malwarescore=0
 mlxscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2004280000 definitions=main-2005230005
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9629
 signatures=668686
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 mlxscore=0
 impostorscore=0
 malwarescore=0 cotscore=-2147483648 suspectscore=13 adultscore=0
 phishscore=0 clxscore=1015 priorityscore=1501 lowpriorityscore=0
 mlxlogscore=779 spamscore=0 bulkscore=0 classifier=spam adjust=0
 reason=mlx scancount=1 engine=8.12.0-2004280000
 definitions=main-2005230005
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Patch# 1: Adds the kvm-unit-tests for the base field of GUEST_BASE_GDTR and
	  GUEST_BASE_IDTR
Patch# 2: Factors out the loops from test_guest_dr7() to a macro
Patch# 3: Adds the kvm-unit-tests for the limit fields of GUEST_BASE_GDTR and
	  GUEST_BASE_IDTR


[PATCH 1/3] kvm-unit-tests: nVMX: Test GUEST_BASE_GDTR and
[PATCH 2/3] kvm-unit-tests: nVMX: Optimize test_guest_dr7() by
[PATCH 3/3] kvm-unit-tests: nVMX: Test GUEST_LIMIT_GDTR and

 x86/vmx_tests.c | 52 ++++++++++++++++++++++++++++++++++++----------------
 1 file changed, 36 insertions(+), 16 deletions(-)

Krish Sadhukhan (3):
      kvm-unit-tests: nVMX: Test GUEST_BASE_GDTR and GUEST_BASE_IDTR on vmentry 
      kvm-unit-tests: nVMX: Optimize test_guest_dr7() by factoring out the loops
      kvm-unit-tests: nVMX: Test GUEST_LIMIT_GDTR and GUEST_LIMIT_IDTR on vmentr
```
#### [PATCH V7 00/15] KVM: MIPS: Add Loongson-3 support (Host Side)
##### From: Huacai Chen <chenhc@lemote.com>

```c
From patchwork Sat May 23 07:56:27 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Huacai Chen <chenhc@lemote.com>
X-Patchwork-Id: 11566637
Return-Path: <SRS0=+Aw4=7F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5B252138A
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 23 May 2020 07:56:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 440E9206C3
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 23 May 2020 07:56:17 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="Vm6wmNZh"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2387535AbgEWH4N (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 23 May 2020 03:56:13 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:46512 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2387489AbgEWH4M (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 23 May 2020 03:56:12 -0400
Received: from mail-pj1-x1044.google.com (mail-pj1-x1044.google.com
 [IPv6:2607:f8b0:4864:20::1044])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 0F563C061A0E;
        Sat, 23 May 2020 00:56:12 -0700 (PDT)
Received: by mail-pj1-x1044.google.com with SMTP id s69so5990639pjb.4;
        Sat, 23 May 2020 00:56:11 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id;
        bh=0roxkuOLFvs3XP03ejCnMAL4pHcaibNzZ6qxSZTCf50=;
        b=Vm6wmNZhRPhoZj/g4YSCwqAu+CkLu9VAT6W42wFWfxUlc08KDk92Olkt07olfA3ebz
         g15IEJ4ZND1gCfLwQJvPLNRyCtMENFE9dhlenekK2rt46kwFdcCntSUgoENKhvl3xegq
         2fkL4ZiPfIu1m0G/k4eG8IPHHK4flVq6wGdIOvJxyqJHyE/OCpBQmDyDLm07kWa3Z0Fr
         7Yyndozzh6qlM2mVSnq+DhMmmoXEucv4T/1adIOq3kwbzFL0vQKmcUs2phPOmY6ofq9+
         Cfzcg8p46XGsLsnr7jW8KkW+gZrKeTWsuHt59I19LWuoTyGAzayGmhicBRWAcAk76Ufc
         rWrw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id;
        bh=0roxkuOLFvs3XP03ejCnMAL4pHcaibNzZ6qxSZTCf50=;
        b=cJ5jmvXkPb/XhKiZFKGBCIymMEW6E6cfHZMseel/OM23zkb9ZXPk7GpPnGNd/wKWmf
         xhuowmg11sMs6J9R9Eof8B32J0Yh4doVmOlYxnCiiuZ/tMtbJOukCGH4xMf3nq5j6AE8
         CKkOYsfcTsPbN5r4PLshQF0xojV3b0/hJ3dZP+GiIwWnc9xiTvM9k5yy61CcYJzUCKkP
         +qfbTRtVy4SMo2bJ0YwP+cB1Mz7j8ADcvwX8LeLrYv2f5Oj0cBoM6QHlj4JPZO4b0TTd
         eweCehGC9tf0zliSN48ubCIMdU8JCkdXuBU4Y+y+6bKcFOnC5TRGKfqnizEbInjjN9qI
         RLGA==
X-Gm-Message-State: AOAM531/UN84l+FLrTBvOpLEcYY+rdwx3F6B0uUXvpuJfNe4ZOmWrnSZ
        dRE5Z7xNF1K/E8tFhtYfJ+I=
X-Google-Smtp-Source: 
 ABdhPJwMuVAm7C30eqGSsS7Ge/poym48K0RP9Fev40gIcsMb6RcotlD8ywWnyMIxlfqanCHHGqxTTQ==
X-Received: by 2002:a17:902:6b07:: with SMTP id
 o7mr17968039plk.74.1590220571413;
        Sat, 23 May 2020 00:56:11 -0700 (PDT)
Received: from software.domain.org (28.144.92.34.bc.googleusercontent.com.
 [34.92.144.28])
        by smtp.gmail.com with ESMTPSA id
 w7sm678491pfu.117.2020.05.23.00.56.08
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Sat, 23 May 2020 00:56:10 -0700 (PDT)
From: Huacai Chen <chenhc@lemote.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Thomas Bogendoerfer <tsbogend@alpha.franken.de>,
        Aleksandar Markovic <aleksandar.qemu.devel@gmail.com>
Cc: kvm@vger.kernel.org, linux-mips@vger.kernel.org,
        Fuxin Zhang <zhangfx@lemote.com>,
        Huacai Chen <chenhuacai@gmail.com>,
        Jiaxun Yang <jiaxun.yang@flygoat.com>,
        Huacai Chen <chenhc@lemote.com>
Subject: [PATCH V7 00/15] KVM: MIPS: Add Loongson-3 support (Host Side)
Date: Sat, 23 May 2020 15:56:27 +0800
Message-Id: <1590220602-3547-1-git-send-email-chenhc@lemote.com>
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

V5 -> V6:
1, Fix a mismatch during rebasing.
2, Add Acked-by: Thomas Bogendoerfer <tsbogend@alpha.franken.de>.

V6 -> V7:
1, Rebase on latest mips-next (Config6 feature bits definition updated).

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
#### [PATCH 0/2] Fix issue with not starting nesting guests on my system
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
From patchwork Sat May 23 16:14:53 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 11566839
Return-Path: <SRS0=+Aw4=7F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EF448913
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 23 May 2020 16:15:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CE64620878
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 23 May 2020 16:15:08 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="F2sZjVZi"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727063AbgEWQPH (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 23 May 2020 12:15:07 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:51487 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726338AbgEWQPG (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 23 May 2020 12:15:06 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1590250505;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=L8j7T0o/S5OaFe2c9p53BQS8VJwyJfs8YmL4K/O2KYU=;
        b=F2sZjVZiCp7J+ruyAvDDd34owqxa5j/L1vk+2aAOwS/+QTO0bSuqn+RX/GZNt1IjzZ3JxR
        eFU16FVv0R5LKHl9fd2eVWRWKSlNbWfQxKsCGPu+V8DqsR57+sOxMiYV+4sZUvPmmIUyck
        SAA0dC9i/Z3DGi+dymvI+18vLcffOHk=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-280-WRTp-SYzNFCw-fza1ty5uA-1; Sat, 23 May 2020 12:15:03 -0400
X-MC-Unique: WRTp-SYzNFCw-fza1ty5uA-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 7AFFB107ACCD;
        Sat, 23 May 2020 16:15:01 +0000 (UTC)
Received: from starship.f32vm (unknown [10.35.206.21])
        by smtp.corp.redhat.com (Postfix) with ESMTP id DC61F6E716;
        Sat, 23 May 2020 16:14:56 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        "H. Peter Anvin" <hpa@zytor.com>, Tao Xu <tao3.xu@intel.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Jim Mattson <jmattson@google.com>,
        linux-kernel@vger.kernel.org, Joerg Roedel <joro@8bytes.org>,
        x86@kernel.org (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT)),
        Wanpeng Li <wanpengli@tencent.com>,
        Ingo Molnar <mingo@redhat.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Borislav Petkov <bp@alien8.de>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Jingqi Liu <jingqi.liu@intel.com>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH 0/2] Fix issue with not starting nesting guests on my system
Date: Sat, 23 May 2020 19:14:53 +0300
Message-Id: <20200523161455.3940-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

On my AMD machine I noticed that I can't start any nested guests,
because nested KVM (everything from master git branches) complains
that it can't find msr MSR_IA32_UMWAIT_CONTROL which my system doesn't support
at all anyway.

I traced it to the recently added UMWAIT support to qemu and kvm.
The kvm portion exposed the new MSR in KVM_GET_MSR_INDEX_LIST without
checking that it the underlying feature is supported in CPUID.
It happened to work when non nested because as a precation kvm,
tries to read each MSR on host before adding it to that list,
and when read gets a #GP it ignores it.

When running nested, the L1 hypervisor can be set to ignore unknown
msr read/writes (I need this for some other guests), thus this safety
check doesn't work anymore.

V2: * added a patch to setup correctly the X86_FEATURE_WAITPKG kvm capability
    * dropped the cosmetic fix patch as it is now fixed in kvm/queue

Best regards,
	Maxim Levitsky

Maxim Levitsky (2):
  kvm/x86/vmx: enable X86_FEATURE_WAITPKG in KVM capabilities
  kvm/x86: don't expose MSR_IA32_UMWAIT_CONTROL unconditionally

 arch/x86/kvm/vmx/vmx.c | 3 +++
 arch/x86/kvm/x86.c     | 4 ++++
 2 files changed, 7 insertions(+)
```
#### [PATCH v9 00/14] KVM: Dirty ring interface
##### From: Peter Xu <peterx@redhat.com>

```c
From patchwork Sat May 23 22:56:45 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11567017
Return-Path: <SRS0=+Aw4=7F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 78C401391
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 23 May 2020 22:57:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 53E0F207CB
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 23 May 2020 22:57:35 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="cfCALY+H"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388117AbgEWW5L (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 23 May 2020 18:57:11 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:46220 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S2388042AbgEWW5K (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 23 May 2020 18:57:10 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1590274628;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=ak8gK7GNAl4EoeqUzd3T8XVnCS3M/ZLmkhVunIHgMSg=;
        b=cfCALY+HdzKL1POtlaWb2bR2NDS0cJd1oW8cwknJNDZMUpKM4SX/Uzdkb2AN5/AAvAiJ3x
        C1Ua1gea8O1QvKfjfjahshoI1UUpOMRIYRac+1Y8xrQ/9uW25+e4yMsuuv4ZP6oF6YvwOS
        CYPrXUTVRGEv41ooGuM/l22ONU/jnEE=
Received: from mail-qv1-f72.google.com (mail-qv1-f72.google.com
 [209.85.219.72]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-150-ve7OhXjaPH6_4msYS62HEg-1; Sat, 23 May 2020 18:57:04 -0400
X-MC-Unique: ve7OhXjaPH6_4msYS62HEg-1
Received: by mail-qv1-f72.google.com with SMTP id dt19so14181388qvb.5
        for <kvm@vger.kernel.org>; Sat, 23 May 2020 15:57:04 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=ak8gK7GNAl4EoeqUzd3T8XVnCS3M/ZLmkhVunIHgMSg=;
        b=pptujs9oKU7oEgwaqohbiduIZUiqmMarsb4Mbn6c9hQOYLMuYkP7BfNqLEWkC5sKuF
         FATz5M17qEvt2AIaiTQc/rT/WYsmF3OiDoVkIZu2IEySwVmv503gb/l+2cVbG5dW7X4K
         1H9mIc3XrGGrbYMx35bfFB4xJu8aYXDRowT9p6oI9xDGIFzn7rK0kAWUPiORQTFQguUy
         BC0m1jgzIu5V+wVMLs3wJ+WloNQu0IPkh5v/lEMHmkdyjLlmlGtFYbXYbDatZKey0G0Z
         PyFJZa5Z8b4iC0gxkgMSTrS/FyAiaG/vQyez7Y69V4XmYNEeJ3pc6P2ScIWVYDB+UVTk
         K/hg==
X-Gm-Message-State: AOAM530kFtDg3VVhYQZ5Vcywn+RJWIoldYvGwKzeaNz9IEkMR15gMVd+
        xc7UW7RDhOBnyz5UxsRY2r2LIMYnohT38Uab3pUeKR9x4y2zVjiaJy2uTtH9SeNukuWz+I6X9d4
        +LnbZivKlUFdT
X-Received: by 2002:ac8:6cf:: with SMTP id j15mr22239407qth.143.1590274623903;
        Sat, 23 May 2020 15:57:03 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJylCK/o2NNseX4bI35qrHG6Z9sjKhapnRw7cBT3s7JjrXpw/jL1gk7SLlunETsB099ebjxu0w==
X-Received: by 2002:ac8:6cf:: with SMTP id j15mr22239397qth.143.1590274623525;
        Sat, 23 May 2020 15:57:03 -0700 (PDT)
Received: from xz-x1.hitronhub.home
 (CPEf81d0fb19163-CMf81d0fb19160.cpe.net.fido.ca. [72.137.123.47])
        by smtp.gmail.com with ESMTPSA id
 w14sm11630979qtt.82.2020.05.23.15.57.01
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Sat, 23 May 2020 15:57:02 -0700 (PDT)
From: Peter Xu <peterx@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>,
        Alex Williamson <alex.williamson@redhat.com>,
        "Michael S . Tsirkin" <mst@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        "Dr . David Alan Gilbert" <dgilbert@redhat.com>,
        Christophe de Dinechin <dinechin@redhat.com>,
        Jason Wang <jasowang@redhat.com>,
        Kevin Tian <kevin.tian@intel.com>, peterx@redhat.com,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Yan Zhao <yan.y.zhao@intel.com>
Subject: [PATCH v9 00/14] KVM: Dirty ring interface
Date: Sat, 23 May 2020 18:56:45 -0400
Message-Id: <20200523225659.1027044-1-peterx@redhat.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

KVM branch:
  https://github.com/xzpeter/linux/tree/kvm-dirty-ring

QEMU branch for testing:
  https://github.com/xzpeter/qemu/tree/kvm-dirty-ring

v9:
- patch 3: __x86_set_memory_region: squash another trivial change to return
  (0xdeadull << 48) always for slot removal [Sean]
- pick r-bs for Drew

v8:
- rebase to kvm/next
- fix test bisection issues [Drew]
- reword comment for __x86_set_memory_region [Sean]
- document fixup on "mutual exclusive", etc. [Sean]

For previous versions, please refer to:

V1: https://lore.kernel.org/kvm/20191129213505.18472-1-peterx@redhat.com
V2: https://lore.kernel.org/kvm/20191221014938.58831-1-peterx@redhat.com
V3: https://lore.kernel.org/kvm/20200109145729.32898-1-peterx@redhat.com
V4: https://lore.kernel.org/kvm/20200205025105.367213-1-peterx@redhat.com
V5: https://lore.kernel.org/kvm/20200304174947.69595-1-peterx@redhat.com
V6: https://lore.kernel.org/kvm/20200309214424.330363-1-peterx@redhat.com
V7: https://lore.kernel.org/kvm/20200318163720.93929-1-peterx@redhat.com
V8: https://lore.kernel.org/kvm/20200331190000.659614-1-peterx@redhat.com

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
 arch/x86/kvm/mmu/mmu.c                        |  12 +-
 arch/x86/kvm/mmutrace.h                       |   9 +-
 arch/x86/kvm/svm/avic.c                       |  11 +-
 arch/x86/kvm/vmx/vmx.c                        |  90 ++--
 arch/x86/kvm/x86.c                            |  53 +-
 include/linux/kvm_dirty_ring.h                | 103 ++++
 include/linux/kvm_host.h                      |  19 +
 include/trace/events/kvm.h                    |  78 +++
 include/uapi/linux/kvm.h                      |  53 ++
 tools/include/uapi/linux/kvm.h                |  53 ++
 tools/testing/selftests/kvm/Makefile          |   2 -
 .../selftests/kvm/clear_dirty_log_test.c      |   6 -
 tools/testing/selftests/kvm/dirty_log_test.c  | 505 ++++++++++++++++--
 .../testing/selftests/kvm/include/kvm_util.h  |   4 +
 tools/testing/selftests/kvm/lib/kvm_util.c    |  68 +++
 .../selftests/kvm/lib/kvm_util_internal.h     |   4 +
 virt/kvm/dirty_ring.c                         | 197 +++++++
 virt/kvm/kvm_main.c                           | 162 +++++-
 22 files changed, 1423 insertions(+), 139 deletions(-)
 create mode 100644 include/linux/kvm_dirty_ring.h
 delete mode 100644 tools/testing/selftests/kvm/clear_dirty_log_test.c
 create mode 100644 virt/kvm/dirty_ring.c
```
