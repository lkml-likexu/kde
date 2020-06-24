#### [PATCH 1/7] accel/kvm: Let kvm_check_extension use global KVM state
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
 <philmd@redhat.com>
X-Patchwork-Id: 11620299
Return-Path: <SRS0=VBfj=AE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AD71790
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 23 Jun 2020 10:51:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9392220771
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 23 Jun 2020 10:51:08 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="XrCKsBD+"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732280AbgFWKvH (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 23 Jun 2020 06:51:07 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:32571 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1732254AbgFWKvF (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 23 Jun 2020 06:51:05 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1592909464;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
  content-type:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=1BS0abpdiPuVnJZzNFn28vzuVgg/Ij6oTCIsBYhyt1Y=;
        b=XrCKsBD+LoDsTLJRbqvQuZYl1EYwHPPLce51hEAIXLLa+mXwATtJvVq1naf5yfGu9PItPe
        yp3a4C8EQ9NwVQrCrJ3Nc8FldUhjj770YueN44AjuE+6iIMkyoSqV+LZPG0mkCJw/eHKn2
        jxHznudgGUZGfaVpxyPDrr2NUyr5S0E=
Received: from mail-wr1-f70.google.com (mail-wr1-f70.google.com
 [209.85.221.70]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-43-zzMZoXWTPB-iakWkIFsJrw-1; Tue, 23 Jun 2020 06:51:02 -0400
X-MC-Unique: zzMZoXWTPB-iakWkIFsJrw-1
Received: by mail-wr1-f70.google.com with SMTP id o12so12890972wrj.23
        for <kvm@vger.kernel.org>; Tue, 23 Jun 2020 03:51:02 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=1BS0abpdiPuVnJZzNFn28vzuVgg/Ij6oTCIsBYhyt1Y=;
        b=DInpBgyoL2TMelunCIzlM/VyEM+5TMGz24NYkIKudpi6uUGc05Thek+qm0qppi99z6
         wZpxj+rzg5YQ67tolhgs8y7fwWNyd6MoSlG+lorxc4Q5G3vRK5v/96Q1Cys35EGYmrio
         U2Vhyujp2J3x6WyDdOkwh67iL2rTa83NdU1DvVsxZrAW/kMMKGtGxqIjGMK3FTjHW4gN
         x8X6f5Ts4mqe5eZExc0yl5QQpMdV3k/5+5crY+3JnxC70ZXKL3GQlpUyoHSKVVJd5i1O
         JDg98i5jeft08zjciCuAUhN4VmK2dFntVkoBMq3Dvs/iNkkBIuuw8Y7Lsbt/oDrMCTBr
         k+Cw==
X-Gm-Message-State: AOAM533v2gzxyvdcMtzMUzDIMHqbsMFs+bT5ZoCOmNleejIsc6cMIFuI
        yqNGyVMbMK/woUDdjDFVbCz256fKDnqtfoPH/1Is2W8XUT3uiJ13thiofPHJ8tQlwlwjJJscBr8
        B70dLPXKhPBXm
X-Received: by 2002:adf:9205:: with SMTP id 5mr23264884wrj.232.1592909461398;
        Tue, 23 Jun 2020 03:51:01 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJxjdMOkGSgtWFKbLjB8FzK+2Ae35wW4M/EhzLYOTVgI1sklv0ksqtYAGkGa8RRoxTc2DMk/SA==
X-Received: by 2002:adf:9205:: with SMTP id 5mr23264860wrj.232.1592909461243;
        Tue, 23 Jun 2020 03:51:01 -0700 (PDT)
Received: from localhost.localdomain (1.red-83-51-162.dynamicip.rima-tde.net.
 [83.51.162.1])
        by smtp.gmail.com with ESMTPSA id
 104sm22641857wrl.25.2020.06.23.03.50.59
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 23 Jun 2020 03:51:00 -0700 (PDT)
From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>
To: qemu-devel@nongnu.org
Cc: Aleksandar Markovic <aleksandar.qemu.devel@gmail.com>,
 Aurelien Jarno <aurelien@aurel32.net>, David Hildenbrand <david@redhat.com>,
 Christian Borntraeger <borntraeger@de.ibm.com>,
 Aleksandar Rikalo <aleksandar.rikalo@syrmia.com>,
 Richard Henderson <rth@twiddle.net>, qemu-s390x@nongnu.org,
 David Gibson <david@gibson.dropbear.id.au>,
 Peter Maydell <peter.maydell@linaro.org>,
 Eduardo Habkost <ehabkost@redhat.com>, kvm@vger.kernel.org,
 "Michael S. Tsirkin" <mst@redhat.com>, Halil Pasic <pasic@linux.ibm.com>,
 qemu-arm@nongnu.org, Cornelia Huck <cohuck@redhat.com>, qemu-ppc@nongnu.org,
 Marcel Apfelbaum <marcel.apfelbaum@gmail.com>,
 Paolo Bonzini <pbonzini@redhat.com>, Marcelo Tosatti <mtosatti@redhat.com>,
 Thomas Huth <thuth@redhat.com>,
 =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>
Subject: [PATCH 1/7] accel/kvm: Let kvm_check_extension use global KVM state
Date: Tue, 23 Jun 2020 12:50:46 +0200
Message-Id: <20200623105052.1700-2-philmd@redhat.com>
X-Mailer: git-send-email 2.21.3
In-Reply-To: <20200623105052.1700-1-philmd@redhat.com>
References: <20200623105052.1700-1-philmd@redhat.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

As KVM supported extentions those should be the same for
all VMs, it is safe to directly use the global kvm_state
in kvm_check_extension().

Suggested-by: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Philippe Mathieu-Daudé <philmd@redhat.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---
 accel/kvm/kvm-all.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v6 1/5] KVM: s390: clean up redundant 'kvm_run' parameters
##### From: Tianjia Zhang <tianjia.zhang@linux.alibaba.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tianjia Zhang <tianjia.zhang@linux.alibaba.com>
X-Patchwork-Id: 11620683
Return-Path: <SRS0=VBfj=AE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 40FA2161F
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 23 Jun 2020 13:14:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 336CC20781
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 23 Jun 2020 13:14:36 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725955AbgFWNOb (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 23 Jun 2020 09:14:31 -0400
Received: from out30-133.freemail.mail.aliyun.com ([115.124.30.133]:51323
 "EHLO
        out30-133.freemail.mail.aliyun.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1732624AbgFWNO2 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 23 Jun 2020 09:14:28 -0400
X-Alimail-AntiSpam: 
 AC=PASS;BC=-1|-1;BR=01201311R131e4;CH=green;DM=||false|;DS=||;FP=0|-1|-1|-1|0|-1|-1|-1;HT=e01e01358;MF=tianjia.zhang@linux.alibaba.com;NM=1;PH=DS;RN=38;SR=0;TI=SMTPD_---0U0WDqnG_1592918059;
Received: from localhost(mailfrom:tianjia.zhang@linux.alibaba.com
 fp:SMTPD_---0U0WDqnG_1592918059)
          by smtp.aliyun-inc.com(127.0.0.1);
          Tue, 23 Jun 2020 21:14:19 +0800
From: Tianjia Zhang <tianjia.zhang@linux.alibaba.com>
To: pbonzini@redhat.com, tsbogend@alpha.franken.de, paulus@ozlabs.org,
        mpe@ellerman.id.au, benh@kernel.crashing.org,
        borntraeger@de.ibm.com, frankja@linux.ibm.com, david@redhat.com,
        cohuck@redhat.com, heiko.carstens@de.ibm.com, gor@linux.ibm.com,
        sean.j.christopherson@intel.com, vkuznets@redhat.com,
        wanpengli@tencent.com, jmattson@google.com, joro@8bytes.org,
        tglx@linutronix.de, mingo@redhat.com, bp@alien8.de, x86@kernel.org,
        hpa@zytor.com, maz@kernel.org, james.morse@arm.com,
        julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
        christoffer.dall@arm.com, peterx@redhat.com, thuth@redhat.com,
        chenhuacai@gmail.com
Cc: kvm@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
        kvmarm@lists.cs.columbia.edu, linux-mips@vger.kernel.org,
        kvm-ppc@vger.kernel.org, linuxppc-dev@lists.ozlabs.org,
        linux-s390@vger.kernel.org, linux-kernel@vger.kernel.org,
        tianjia.zhang@linux.alibaba.com
Subject: [PATCH v6 1/5] KVM: s390: clean up redundant 'kvm_run' parameters
Date: Tue, 23 Jun 2020 21:14:14 +0800
Message-Id: <20200623131418.31473-2-tianjia.zhang@linux.alibaba.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200623131418.31473-1-tianjia.zhang@linux.alibaba.com>
References: <20200623131418.31473-1-tianjia.zhang@linux.alibaba.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In the current kvm version, 'kvm_run' has been included in the 'kvm_vcpu'
structure. For historical reasons, many kvm-related function parameters
retain the 'kvm_run' and 'kvm_vcpu' parameters at the same time. This
patch does a unified cleanup of these remaining redundant parameters.

Signed-off-by: Tianjia Zhang <tianjia.zhang@linux.alibaba.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/s390/kvm/kvm-s390.c | 23 +++++++++++++++--------
 1 file changed, 15 insertions(+), 8 deletions(-)

```
#### [GIT PULL 1/1] KVM: s390: reduce number of IO pins to 1
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11620173
Return-Path: <SRS0=VBfj=AE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C0B6B90
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 23 Jun 2020 09:24:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AC74820724
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 23 Jun 2020 09:24:30 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731952AbgFWJYa (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 23 Jun 2020 05:24:30 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:40424 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1731887AbgFWJY3 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 23 Jun 2020 05:24:29 -0400
Received: from pps.filterd (m0098416.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 05N914cK042258;
        Tue, 23 Jun 2020 05:24:28 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 31tyry2378-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 23 Jun 2020 05:24:28 -0400
Received: from m0098416.ppops.net (m0098416.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 05N916rE042447;
        Tue, 23 Jun 2020 05:24:28 -0400
Received: from ppma01fra.de.ibm.com (46.49.7a9f.ip4.static.sl-reverse.com
 [159.122.73.70])
        by mx0b-001b2d01.pphosted.com with ESMTP id 31tyry236q-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 23 Jun 2020 05:24:27 -0400
Received: from pps.filterd (ppma01fra.de.ibm.com [127.0.0.1])
        by ppma01fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 05N9KN0W028871;
        Tue, 23 Jun 2020 09:24:26 GMT
Received: from b06cxnps3074.portsmouth.uk.ibm.com
 (d06relay09.portsmouth.uk.ibm.com [9.149.109.194])
        by ppma01fra.de.ibm.com with ESMTP id 31sa3823fy-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 23 Jun 2020 09:24:25 +0000
Received: from d06av21.portsmouth.uk.ibm.com (d06av21.portsmouth.uk.ibm.com
 [9.149.105.232])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 05N9ONwY4063568
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 23 Jun 2020 09:24:23 GMT
Received: from d06av21.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 1B84F52051;
        Tue, 23 Jun 2020 09:24:23 +0000 (GMT)
Received: from localhost.localdomain.com (unknown [9.145.62.182])
        by d06av21.portsmouth.uk.ibm.com (Postfix) with ESMTP id 9EF9352052;
        Tue, 23 Jun 2020 09:24:22 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: pbonzini@redhat.com
Cc: kvm@vger.kernel.org, frankja@linux.vnet.ibm.com, david@redhat.com,
        borntraeger@de.ibm.com, cohuck@redhat.com,
        linux-s390@vger.kernel.org, imbrenda@linux.ibm.com
Subject: [GIT PULL 1/1] KVM: s390: reduce number of IO pins to 1
Date: Tue, 23 Jun 2020 11:23:41 +0200
Message-Id: <20200623092341.10348-2-frankja@linux.ibm.com>
X-Mailer: git-send-email 2.25.4
In-Reply-To: <20200623092341.10348-1-frankja@linux.ibm.com>
References: <20200623092341.10348-1-frankja@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.216,18.0.687
 definitions=2020-06-23_04:2020-06-22,2020-06-23 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 lowpriorityscore=0
 adultscore=0 phishscore=0 spamscore=0 mlxscore=0 impostorscore=0
 cotscore=-2147483648 suspectscore=0 mlxlogscore=999 clxscore=1015
 priorityscore=1501 bulkscore=0 malwarescore=0 classifier=spam adjust=0
 reason=mlx scancount=1 engine=8.12.0-2004280000
 definitions=main-2006230068
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Christian Borntraeger <borntraeger@de.ibm.com>

The current number of KVM_IRQCHIP_NUM_PINS results in an order 3
allocation (32kb) for each guest start/restart. This can result in OOM
killer activity even with free swap when the memory is fragmented
enough:

kernel: qemu-system-s39 invoked oom-killer: gfp_mask=0x440dc0(GFP_KERNEL_ACCOUNT|__GFP_COMP|__GFP_ZERO), order=3, oom_score_adj=0
kernel: CPU: 1 PID: 357274 Comm: qemu-system-s39 Kdump: loaded Not tainted 5.4.0-29-generic #33-Ubuntu
kernel: Hardware name: IBM 8562 T02 Z06 (LPAR)
kernel: Call Trace:
kernel: ([<00000001f848fe2a>] show_stack+0x7a/0xc0)
kernel:  [<00000001f8d3437a>] dump_stack+0x8a/0xc0
kernel:  [<00000001f8687032>] dump_header+0x62/0x258
kernel:  [<00000001f8686122>] oom_kill_process+0x172/0x180
kernel:  [<00000001f8686abe>] out_of_memory+0xee/0x580
kernel:  [<00000001f86e66b8>] __alloc_pages_slowpath+0xd18/0xe90
kernel:  [<00000001f86e6ad4>] __alloc_pages_nodemask+0x2a4/0x320
kernel:  [<00000001f86b1ab4>] kmalloc_order+0x34/0xb0
kernel:  [<00000001f86b1b62>] kmalloc_order_trace+0x32/0xe0
kernel:  [<00000001f84bb806>] kvm_set_irq_routing+0xa6/0x2e0
kernel:  [<00000001f84c99a4>] kvm_arch_vm_ioctl+0x544/0x9e0
kernel:  [<00000001f84b8936>] kvm_vm_ioctl+0x396/0x760
kernel:  [<00000001f875df66>] do_vfs_ioctl+0x376/0x690
kernel:  [<00000001f875e304>] ksys_ioctl+0x84/0xb0
kernel:  [<00000001f875e39a>] __s390x_sys_ioctl+0x2a/0x40
kernel:  [<00000001f8d55424>] system_call+0xd8/0x2c8

As far as I can tell s390x does not use the iopins as we bail our for
anything other than KVM_IRQ_ROUTING_S390_ADAPTER and the chip/pin is
only used for KVM_IRQ_ROUTING_IRQCHIP. So let us use a small number to
reduce the memory footprint.

Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Link: https://lore.kernel.org/r/20200617083620.5409-1-borntraeger@de.ibm.com
---
 arch/s390/include/asm/kvm_host.h | 8 ++++----
 1 file changed, 4 insertions(+), 4 deletions(-)

```
#### [GIT PULL] KVM fixes for Linux 5.8-rc3
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11621171
Return-Path: <SRS0=VBfj=AE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1C5CA60D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 23 Jun 2020 17:11:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 02A1820781
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 23 Jun 2020 17:11:28 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="AZk02rCA"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732979AbgFWRLX (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 23 Jun 2020 13:11:23 -0400
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:29048 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1728916AbgFWRLX (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 23 Jun 2020 13:11:23 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1592932281;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=tgpqv+Z4YzvIf/4SqnrwWUNPhSAJzQTNmQO1fWEnu4g=;
        b=AZk02rCAYz9FmShJrHLK/213qOgbmJRA0fQvN4CAdiR9hbgHLY6qLIlp57p+qsjV72qm7d
        FZGHL+J5Hj22VmoFLPZLXzIeFkydt7/HL/gfzgGP2sl1kw6JvXThUxbfRmUeXIYqNQouc5
        zT452za7dMG39a39mwssx7e0IGOONn8=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-372-fa8R2lz4PIqGlC1xadbvrQ-1; Tue, 23 Jun 2020 13:11:19 -0400
X-MC-Unique: fa8R2lz4PIqGlC1xadbvrQ-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 9E71B8C4BA1;
        Tue, 23 Jun 2020 17:11:18 +0000 (UTC)
Received: from virtlab511.virt.lab.eng.bos.redhat.com
 (virtlab511.virt.lab.eng.bos.redhat.com [10.19.152.198])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 2F2AF5D9D3;
        Tue, 23 Jun 2020 17:11:18 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: torvalds@linux-foundation.org
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [GIT PULL] KVM fixes for Linux 5.8-rc3
Date: Tue, 23 Jun 2020 13:11:17 -0400
Message-Id: <20200623171117.326222-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Linus,

The following changes since commit b3a9e3b9622ae10064826dccb4f7a52bd88c7407:

  Linux 5.8-rc1 (2020-06-14 12:45:04 -0700)

are available in the Git repository at:

  https://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to e4553b4976d1178c13da295cb5c7b21f55baf8f9:

  KVM: VMX: Remove vcpu_vmx's defunct copy of host_pkru (2020-06-23 06:01:29 -0400)

----------------------------------------------------------------
All bugfixes except for a couple cleanup patches.

----------------------------------------------------------------
Huacai Chen (1):
      KVM: MIPS: Fix a build error for !CPU_LOONGSON64

Igor Mammedov (1):
      kvm: lapic: fix broken vcpu hotplug

Marcelo Tosatti (1):
      KVM: x86: allow TSC to differ by NTP correction bounds without TSC scaling

Paolo Bonzini (1):
      KVM: LAPIC: ensure APIC map is up to date on concurrent update requests

Qian Cai (1):
      kvm/svm: disable KCSAN for svm_vcpu_run()

Sean Christopherson (4):
      KVM: VMX: Add helpers to identify interrupt type from intr_info
      KVM: nVMX: Plumb L2 GPA through to PML emulation
      KVM: VMX: Stop context switching MSR_IA32_UMWAIT_CONTROL
      KVM: VMX: Remove vcpu_vmx's defunct copy of host_pkru

Vitaly Kuznetsov (2):
      Revert "KVM: VMX: Micro-optimize vmexit time when not exposing PMU"
      KVM: x86/mmu: Avoid mixing gpa_t with gfn_t in walk_addr_generic()

Xiaoyao Li (1):
      KVM: X86: Fix MSR range of APIC registers in X2APIC mode

 arch/mips/kvm/mips.c            |  2 ++
 arch/x86/include/asm/kvm_host.h |  4 ++--
 arch/x86/include/asm/mwait.h    |  2 --
 arch/x86/kernel/cpu/umwait.c    |  6 -----
 arch/x86/kvm/lapic.c            | 50 +++++++++++++++++++++++++----------------
 arch/x86/kvm/mmu.h              |  2 +-
 arch/x86/kvm/mmu/mmu.c          |  4 ++--
 arch/x86/kvm/mmu/paging_tmpl.h  | 16 ++++++-------
 arch/x86/kvm/svm/svm.c          |  2 +-
 arch/x86/kvm/vmx/vmcs.h         | 32 ++++++++++++++++----------
 arch/x86/kvm/vmx/vmx.c          | 27 ++++------------------
 arch/x86/kvm/vmx/vmx.h          |  2 --
 arch/x86/kvm/x86.c              |  7 +++---
 13 files changed, 74 insertions(+), 82 deletions(-)
```
#### [PATCH] KVM: arm64: vgic-v4: Plug race between non-residency and v4.1 doorbell
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11620599
Return-Path: <SRS0=VBfj=AE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A62C56C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 23 Jun 2020 12:12:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8F2082072E
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 23 Jun 2020 12:12:24 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1592914344;
	bh=82FEL/lqihaAkT9TFcf9PCxFsGrapDUAVvxVatgi5Vo=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=lL74xNhXd6Lz4X1ToNnqBECY6Rf1P81nMrebF0drkAmBUnnmoh5p48mDxgDsH3xgf
	 dZZHrDAyoU3YWyqMgLm7wIsp+x0UeEvOBiQt1NpQmfc5kJXakBZcVRdf/gE00RYsjb
	 UTV2/5Cj02nrKzPSXCy9xKuZ6+IAfoex1yQLiy5Q=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732514AbgFWMMX (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 23 Jun 2020 08:12:23 -0400
Received: from mail.kernel.org ([198.145.29.99]:52846 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1732436AbgFWMMX (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 23 Jun 2020 08:12:23 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 745B420707;
        Tue, 23 Jun 2020 12:12:22 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1592914342;
        bh=82FEL/lqihaAkT9TFcf9PCxFsGrapDUAVvxVatgi5Vo=;
        h=From:To:Cc:Subject:Date:From;
        b=pD87Q8rJB6cjNx4jAe7RfbqAjaHX3486yTR/IyiwU9rVik33STPz3KTZf1mEdrJMm
         MkYRT1QLW4gAG6Coup+KXL+blU0reYnw21TSoS6DYNEIXFu/NM1J+y44m6J6DkXhxG
         QbxgCa5SjpPW/IVpnkfMwAytwNhpiO+WxlwCPa5Q=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1jnhmm-005gBg-Rs; Tue, 23 Jun 2020 13:12:21 +0100
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        kernel-team@android.com, Zenghui Yu <yuzenghui@huawei.com>
Subject: [PATCH] KVM: arm64: vgic-v4: Plug race between non-residency and v4.1
 doorbell
Date: Tue, 23 Jun 2020 13:12:01 +0100
Message-Id: <20200623121201.362532-1-maz@kernel.org>
X-Mailer: git-send-email 2.27.0
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 kernel-team@android.com, yuzenghui@huawei.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When making a vPE non-resident because it has hit a blocking WFI,
the doorbell can fire at any time after the write to the RD.
Crucially, it can fire right between the write to GICR_VPENDBASER
and the write to the pending_last field in the its_vpe structure.

This means that we would overwrite pending_last with stale data,
and potentially not wakeup until some unrelated event (such as
a timer interrupt) puts the vPE back on the CPU.

GICv4 isn't affected by this as we actively mask the doorbell on
entering the guest, while GICv4.1 automatically manages doorbell
delivery without any hypervisor-driven masking.

Use the vpe_lock to synchronize such update, which solves the
problem altogether.

Fixes: ae699ad348cdc ("irqchip/gic-v4.1: Move doorbell management to the GICv4 abstraction layer")
Reported-by: Zenghui Yu <yuzenghui@huawei.com>
Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 arch/arm64/kvm/vgic/vgic-v4.c    | 8 ++++++++
 drivers/irqchip/irq-gic-v3-its.c | 8 ++++++++
 2 files changed, 16 insertions(+)

```
#### [PATCH] KVM: PPC: Book3S HV: Use feature flag CPU_FTR_P9_TIDR when accessing TIDR
##### From: =?utf-8?q?C=C3=A9dric_Le_Goater?= <clg@kaod.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?C=C3=A9dric_Le_Goater?= <clg@kaod.org>
X-Patchwork-Id: 11621325
Return-Path: <SRS0=VBfj=AE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5E6A014E3
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 23 Jun 2020 18:06:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4E3D92078B
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 23 Jun 2020 18:06:50 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1733201AbgFWSGt (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 23 Jun 2020 14:06:49 -0400
Received: from 9.mo6.mail-out.ovh.net ([87.98.171.146]:54655 "EHLO
        9.mo6.mail-out.ovh.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1733085AbgFWSGt (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 23 Jun 2020 14:06:49 -0400
X-Greylist: delayed 3598 seconds by postgrey-1.27 at vger.kernel.org;
 Tue, 23 Jun 2020 14:06:48 EDT
Received: from player693.ha.ovh.net (unknown [10.110.208.89])
        by mo6.mail-out.ovh.net (Postfix) with ESMTP id 6C60A21AD9C
        for <kvm@vger.kernel.org>; Tue, 23 Jun 2020 18:50:36 +0200 (CEST)
Received: from kaod.org (lfbn-tou-1-921-245.w86-210.abo.wanadoo.fr
 [86.210.152.245])
        (Authenticated sender: clg@kaod.org)
        by player693.ha.ovh.net (Postfix) with ESMTPSA id D386013A38801;
        Tue, 23 Jun 2020 16:50:28 +0000 (UTC)
Authentication-Results: garm.ovh;
 auth=pass
 (GARM-101G0046a9a02d6-4de9-4819-8928-acddee862ae7,EED1DA90FC9B795DFFB5AB62ED4F19E3D36D96F8)
 smtp.auth=clg@kaod.org
From: =?utf-8?q?C=C3=A9dric_Le_Goater?= <clg@kaod.org>
To: Michael Ellerman <mpe@ellerman.id.au>
Cc: Paul Mackerras <paulus@samba.org>, linuxppc-dev@lists.ozlabs.org,
 kvm-ppc@vger.kernel.org, kvm@vger.kernel.org, =?utf-8?q?C=C3=A9dric_Le_Goat?=
	=?utf-8?q?er?= <clg@kaod.org>
Subject: [PATCH] KVM: PPC: Book3S HV: Use feature flag CPU_FTR_P9_TIDR when
 accessing TIDR
Date: Tue, 23 Jun 2020 18:50:27 +0200
Message-Id: <20200623165027.271215-1-clg@kaod.org>
X-Mailer: git-send-email 2.25.4
MIME-Version: 1.0
X-Ovh-Tracer-Id: 3664804199253838769
X-VR-SPAMSTATE: OK
X-VR-SPAMSCORE: 0
X-VR-SPAMCAUSE: 
 gggruggvucftvghtrhhoucdtuddrgeduhedrudekhedgjeelucetufdoteggodetrfdotffvucfrrhhofhhilhgvmecuqfggjfdpvefjgfevmfevgfenuceurghilhhouhhtmecuhedttdenucenucfjughrpefhvffufffkofggtgfgsehtkeertdertdejnecuhfhrohhmpeevrogurhhitgcunfgvucfiohgrthgvrhcuoegtlhhgsehkrghougdrohhrgheqnecuggftrfgrthhtvghrnhephfdvfeeguedthedvleffgeekveeiiedvveegvefhudfhffdtieekueelfeeiheeunecuffhomhgrihhnpehrmhhhrghnughlvghrshdrshgsnecukfhppedtrddtrddtrddtpdekiedrvddutddrudehvddrvdegheenucevlhhushhtvghrufhiiigvpedtnecurfgrrhgrmhepmhhouggvpehsmhhtphdqohhuthdphhgvlhhopehplhgrhigvrheileefrdhhrgdrohhvhhdrnhgvthdpihhnvghtpedtrddtrddtrddtpdhmrghilhhfrhhomheptghlgheskhgrohgurdhorhhgpdhrtghpthhtohepkhhvmhesvhhgvghrrdhkvghrnhgvlhdrohhrgh
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The TIDR register is only available on POWER9 systems and code
accessing this register is not always protected by the CPU_FTR_P9_TIDR
flag. Fix that to make sure POWER10 systems won't use it as TIDR has
been removed.

Signed-off-by: Cédric Le Goater <clg@kaod.org>
---
 arch/powerpc/kvm/book3s_hv.c            | 23 +++++++++++++++++------
 arch/powerpc/kvm/book3s_hv_rmhandlers.S | 16 ++++++++++++----
 2 files changed, 29 insertions(+), 10 deletions(-)

```
#### [PATCH kvm-unit-tests] lib/alloc.c: fix missing include
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11619917
Return-Path: <SRS0=VBfj=AE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0C2096C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 23 Jun 2020 07:28:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E97B620774
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 23 Jun 2020 07:28:56 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="UeuuIx/X"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731505AbgFWH24 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 23 Jun 2020 03:28:56 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:26932 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1731057AbgFWH2z (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 23 Jun 2020 03:28:55 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1592897335;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=KOoSXZOmbiUr1rlTG1Dr2upX/xU5gp149xe2zR0H7ME=;
        b=UeuuIx/XMCRxn4A5gt9CcY40DMzsh9FuYtwsxWlQtRURcj8RIJTkxRFRXjqwVCL8Dpq1F6
        4JL653LCutGLT2o2w7LaLtWthNokdN3utUmSkqiFhA0ridLPqn2I/wyclBRCmwMBDSOftF
        hX4LlOEtwHI6V4JzDtShpbrL0aKVos0=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-314-1Uup3uu5NKKfl9DPjjzKFA-1; Tue, 23 Jun 2020 03:28:52 -0400
X-MC-Unique: 1Uup3uu5NKKfl9DPjjzKFA-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 29A50805EE4
        for <kvm@vger.kernel.org>; Tue, 23 Jun 2020 07:28:52 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id E86E25C1D4
        for <kvm@vger.kernel.org>; Tue, 23 Jun 2020 07:28:51 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: kvm@vger.kernel.org
Subject: [PATCH kvm-unit-tests] lib/alloc.c: fix missing include
Date: Tue, 23 Jun 2020 03:28:51 -0400
Message-Id: <20200623072851.30972-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Include bitops.h to get BITS_PER_LONG and avoid errors such as

lib/alloc.c: In function mult_overflow:
lib/alloc.c:24:9: error: right shift count >= width of type
[-Werror=shift-count-overflow]
   24 |  if ((a >> 32) && (b >> 32))
      |         ^~

Fixes: cde8415e1 ("lib/alloc.c: add overflow check for calloc")
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 lib/alloc.c | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH kvm-unit-tests RFC] Revert "SVM: move guest past HLT"
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11620037
Return-Path: <SRS0=VBfj=AE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D226360D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 23 Jun 2020 08:27:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BB2E320767
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 23 Jun 2020 08:27:19 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="K4+8qw0b"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731885AbgFWI1S (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 23 Jun 2020 04:27:18 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:54409 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1731718AbgFWI1S (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 23 Jun 2020 04:27:18 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1592900837;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=d9HjsnlPG7d2lI7SP6pinbDLKBTZckBRqaBaiNwA4Is=;
        b=K4+8qw0bnMOcXn3eV2Xcj7xfKjUTTpRv5euXV5I9dAe/b0IGcYtdXgmJCepW9cQJB4ERgC
        NUoJfzTNKUhwwXoH3dCwvp3H65HLCJFuoSBrMqVBU2SrF2uYD3hvFxdQTKkKng+D15BZN9
        sB8g8RFxxXBrnHJl/5YyGtxnNJ6v1N8=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-237-3w0UAWawMh-7EOKBLPfsXQ-1; Tue, 23 Jun 2020 04:27:15 -0400
X-MC-Unique: 3w0UAWawMh-7EOKBLPfsXQ-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 708A6800597
        for <kvm@vger.kernel.org>; Tue, 23 Jun 2020 08:27:14 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.193.16])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 4D93519D82;
        Tue, 23 Jun 2020 08:27:13 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org
Subject: [PATCH kvm-unit-tests RFC] Revert "SVM: move guest past HLT"
Date: Tue, 23 Jun 2020 10:27:11 +0200
Message-Id: <20200623082711.803916-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

'nmi_hlt' test returns somewhat weird result:

...
PASS: direct NMI + hlt
PASS: NMI intercept while running guest
PASS: intercepted NMI + hlt
PASS: nmi_hlt
SUMMARY: 4 tests, 1 unexpected failures

Trying to investigate where the failure is coming from I was tweaking
the code around and with tiny meaningless changes I was able to observe
 #PF, #GP, #UD and other 'interesting' results. Compiler optimization
flags also change the outcome so there's obviously a corruption somewhere.
Adding a meaningless 'nop' to the second 'asm volatile ("hlt");' in
nmi_hlt_test() saves the day so it seems we erroneously advance RIP
twice, the advancement in nmi_hlt_finished() is not needed.

The outcome, however, contradicts with the commit message in 7e7aa86f74
("SVM: move guest past HLT"). With that commit reverted, all tests seem
to pass but I'm not sure what issue the commit was trying to fix, thus
RFC.

This reverts commit 7e7aa86f7418a8343de46583977f631e55fd02ed.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 x86/svm_tests.c | 8 --------
 1 file changed, 8 deletions(-)

```
#### [PATCH kvm-unit-tests] vmx: remove unnecessary #ifdef __x86_64__
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11620159
Return-Path: <SRS0=VBfj=AE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BB8F014F6
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 23 Jun 2020 09:20:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A3D5920738
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 23 Jun 2020 09:20:51 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="IO+i6TN6"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732066AbgFWJUu (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 23 Jun 2020 05:20:50 -0400
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:35044 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1731938AbgFWJUu (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 23 Jun 2020 05:20:50 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1592904048;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=s16NwfI3JixQk4P13nqbgQj1Gxhu5uAf3M2pBFtoqOo=;
        b=IO+i6TN6uOM8fn+dG7k5JBvSTtw/vACm31sBK3SJuwW5DWaY6gpPoWLrN0B04wYjqsw8tF
        FLvlqJiD1tKCRcJL3cBMHM4wCYhL+MoEOqUYB6yVzhJOjH3i67dUY5IiLF9RNwt0IePLEK
        tjxBjK4a8v8SR1ml8ItrvmxgWig/8ww=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-191-yRmnP8n9OHmejooAZeBd9A-1; Tue, 23 Jun 2020 05:20:47 -0400
X-MC-Unique: yRmnP8n9OHmejooAZeBd9A-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 37EF0464;
        Tue, 23 Jun 2020 09:20:46 +0000 (UTC)
Received: from virtlab511.virt.lab.eng.bos.redhat.com
 (virtlab511.virt.lab.eng.bos.redhat.com [10.19.152.198])
        by smtp.corp.redhat.com (Postfix) with ESMTP id BF6CA5C541;
        Tue, 23 Jun 2020 09:20:45 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: kvm@vger.kernel.org
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Subject: [PATCH kvm-unit-tests] vmx: remove unnecessary #ifdef __x86_64__
Date: Tue, 23 Jun 2020 05:20:45 -0400
Message-Id: <20200623092045.271835-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The VMX tests are 64-bit only, so checking the architecture is
unnecessary.  Also, if the tests supported 32-bits environments
the #ifdef would probably go in test_canonical.

Reported-by: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 x86/vmx_tests.c | 12 ------------
 1 file changed, 12 deletions(-)

```
#### [kvm-unit-tests PATCH] x86: Initialize segment selectors
##### From: Nadav Amit <namit@vmware.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Nadav Amit <namit@vmware.com>
X-Patchwork-Id: 11620045
Return-Path: <SRS0=VBfj=AE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 167AE1392
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 23 Jun 2020 08:44:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0718C20720
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 23 Jun 2020 08:44:03 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731780AbgFWIoC (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 23 Jun 2020 04:44:02 -0400
Received: from ex13-edg-ou-001.vmware.com ([208.91.0.189]:2019 "EHLO
        EX13-EDG-OU-001.vmware.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1731158AbgFWIoB (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 23 Jun 2020 04:44:01 -0400
Received: from sc9-mailhost3.vmware.com (10.113.161.73) by
 EX13-EDG-OU-001.vmware.com (10.113.208.155) with Microsoft SMTP Server id
 15.0.1156.6; Tue, 23 Jun 2020 01:43:59 -0700
Received: from sc2-haas01-esx0118.eng.vmware.com
 (sc2-haas01-esx0118.eng.vmware.com [10.172.44.118])
        by sc9-mailhost3.vmware.com (Postfix) with ESMTP id 7E399407C6;
        Tue, 23 Jun 2020 01:44:01 -0700 (PDT)
From: Nadav Amit <namit@vmware.com>
To: Paolo Bonzini <pbonzini@redhat.com>
CC: <kvm@vger.kernel.org>, Nadav Amit <namit@vmware.com>
Subject: [kvm-unit-tests PATCH] x86: Initialize segment selectors
Date: Tue, 23 Jun 2020 01:41:32 -0700
Message-ID: <20200623084132.36213-1-namit@vmware.com>
X-Mailer: git-send-email 2.17.1
MIME-Version: 1.0
Received-SPF: None (EX13-EDG-OU-001.vmware.com: namit@vmware.com does not
 designate permitted sender hosts)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Currently, the BSP's segment selectors are not initialized in 32-bit
(cstart.S). As a result the tests implicitly rely on the segment
selector values that are set by the BIOS. If this assumption is not
kept, the task-switch test fails.

Fix it by initializing them.

Signed-off-by: Nadav Amit <namit@vmware.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 x86/cstart.S | 17 +++++++++++------
 1 file changed, 11 insertions(+), 6 deletions(-)

```
#### [PATCH] KVM: VMX: Stop context switching MSR_IA32_UMWAIT_CONTROL
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11619515
Return-Path: <SRS0=VBfj=AE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 665FF13A0
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 23 Jun 2020 00:51:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 58A4220738
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 23 Jun 2020 00:51:43 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732327AbgFWAvj (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 22 Jun 2020 20:51:39 -0400
Received: from mga04.intel.com ([192.55.52.120]:10120 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1731750AbgFWAvi (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 22 Jun 2020 20:51:38 -0400
IronPort-SDR: 
 TwQ4rW+XOK1NTshp9+G8eOvNKtr7K6kZc9Jgu7nL6YJd29tV6PkLEhMe2ILDec54za4ctRdczw
 fiS5pBGfqjpg==
X-IronPort-AV: E=McAfee;i="6000,8403,9660"; a="141422602"
X-IronPort-AV: E=Sophos;i="5.75,268,1589266800";
   d="scan'208";a="141422602"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga003.fm.intel.com ([10.253.24.29])
  by fmsmga104.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 22 Jun 2020 17:51:37 -0700
IronPort-SDR: 
 RXTycZaOvOOv96UEW80afRXTHI74G+J3g0EXw6R3mRJBzFpBV01mjP80zcCQbuOfjoMwPes/u+
 jAi8gMV7Q+sQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,268,1589266800";
   d="scan'208";a="319007683"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.152])
  by FMSMGA003.fm.intel.com with ESMTP; 22 Jun 2020 17:51:36 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Jingqi Liu <jingqi.liu@intel.com>,
        Tao Xu <tao3.xu@intel.com>
Subject: [PATCH] KVM: VMX: Stop context switching MSR_IA32_UMWAIT_CONTROL
Date: Mon, 22 Jun 2020 17:51:35 -0700
Message-Id: <20200623005135.10414-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Remove support for context switching between the guest's and host's
desired UMWAIT_CONTROL.  Propagating the guest's value to hardware isn't
required for correct functionality, e.g. KVM intercepts reads and writes
to the MSR, and the latency effects of the settings controlled by the
MSR are not architecturally visible.

As a general rule, KVM should not allow the guest to control power
management settings unless explicitly enabled by userspace, e.g. see
KVM_CAP_X86_DISABLE_EXITS.  E.g. Intel's SDM explicitly states that C0.2
can improve the performance of SMT siblings.  A devious guest could
disable C0.2 so as to improve the performance of their workloads at the
detriment to workloads running in the host or on other VMs.

Wholesale removal of UMWAIT_CONTROL context switching also fixes a race
condition where updates from the host may cause KVM to enter the guest
with the incorrect value.  Because updates are are propagated to all
CPUs via IPI (SMP function callback), the value in hardware may be
stale with respect to the cached value and KVM could enter the guest
with the wrong value in hardware.  As above, the guest can't observe the
bad value, but it's a weird and confusing wart in the implementation.

Removal also fixes the unnecessary usage of VMX's atomic load/store MSR
lists.  Using the lists is only necessary for MSRs that are required for
correct functionality immediately upon VM-Enter/VM-Exit, e.g. EFER on
old hardware, or for MSRs that need to-the-uop precision, e.g. perf
related MSRs.  For UMWAIT_CONTROL, the effects are only visible in the
kernel via TPAUSE/delay(), and KVM doesn't do any form of delay in
vcpu_vmx_run().  Using the atomic lists is undesirable as they are more
expensive than direct RDMSR/WRMSR.

Furthermore, even if giving the guest control of the MSR is legitimate,
e.g. in pass-through scenarios, it's not clear that the benefits would
outweigh the overhead.  E.g. saving and restoring an MSR across a VMX
roundtrip costs ~250 cycles, and if the guest diverged from the host
that cost would be paid on every run of the guest.  In other words, if
there is a legitimate use case then it should be enabled by a new
per-VM capability.

Note, KVM still needs to emulate MSR_IA32_UMWAIT_CONTROL so that it can
correctly expose other WAITPKG features to the guest, e.g. TPAUSE,
UMWAIT and UMONITOR.

Fixes: 6e3ba4abcea56 ("KVM: vmx: Emulate MSR IA32_UMWAIT_CONTROL")
Cc: stable@vger.kernel.org
Cc: Jingqi Liu <jingqi.liu@intel.com>
Cc: Tao Xu <tao3.xu@intel.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/include/asm/mwait.h |  2 --
 arch/x86/kernel/cpu/umwait.c |  6 ------
 arch/x86/kvm/vmx/vmx.c       | 18 ------------------
 3 files changed, 26 deletions(-)

```
#### [PATCH] KVM: X86: Emulate APERF/MPERF to report actual VCPU frequency
##### From: Like Xu <like.xu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Like Xu <like.xu@linux.intel.com>
X-Patchwork-Id: 11619863
Return-Path: <SRS0=VBfj=AE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0CE2E6C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 23 Jun 2020 06:36:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id EC4A62072E
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 23 Jun 2020 06:36:50 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730793AbgFWGgr (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 23 Jun 2020 02:36:47 -0400
Received: from mga14.intel.com ([192.55.52.115]:5416 "EHLO mga14.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1730540AbgFWGgr (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 23 Jun 2020 02:36:47 -0400
IronPort-SDR: 
 nsmTi8ocRiUWvXLoPH8IMlCJmhc1CUCkBdAz69f7SSeVRvbX312vZC0lpgb7DocI0FC7GYQh3N
 PZK0a168hk9g==
X-IronPort-AV: E=McAfee;i="6000,8403,9660"; a="143043212"
X-IronPort-AV: E=Sophos;i="5.75,270,1589266800";
   d="scan'208";a="143043212"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga005.fm.intel.com ([10.253.24.32])
  by fmsmga103.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 22 Jun 2020 23:36:42 -0700
IronPort-SDR: 
 tX/2AxVwRB59zBI8qq+V05rF3uOKO4vT9Qt+z5oG4lsarvbMhj1J34QrUC3Nhu+0UsMxtUsklG
 Rbcl5daCwLQg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,270,1589266800";
   d="scan'208";a="478750232"
Received: from sqa-gate.sh.intel.com (HELO clx-ap-likexu.tsp.org)
 ([10.239.48.212])
  by fmsmga005.fm.intel.com with ESMTP; 22 Jun 2020 23:36:38 -0700
From: Like Xu <like.xu@linux.intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, wei.huang2@amd.com,
        Peter Zijlstra <peterz@infradead.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        linux-kernel@vger.kernel.org, Like Xu <like.xu@linux.intel.com>,
        Li RongQing <lirongqing@baidu.com>,
        Chai Wen <chaiwen@baidu.com>, Jia Lina <jialina01@baidu.com>
Subject: [PATCH] KVM: X86: Emulate APERF/MPERF to report actual VCPU frequency
Date: Tue, 23 Jun 2020 14:35:30 +0800
Message-Id: <20200623063530.81917-1-like.xu@linux.intel.com>
X-Mailer: git-send-email 2.21.3
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The aperf/mperf are used to report current CPU frequency after 7d5905dc14a
"x86 / CPU: Always show current CPU frequency in /proc/cpuinfo". But guest
kernel always reports a fixed VCPU frequency in the /proc/cpuinfo, which
may confuse users especially when turbo is enabled on the host.

Emulate guest APERF/MPERF capability based their values on the host.

Co-developed-by: Li RongQing <lirongqing@baidu.com>
Signed-off-by: Li RongQing <lirongqing@baidu.com>
Reviewed-by: Chai Wen <chaiwen@baidu.com>
Reviewed-by: Jia Lina <jialina01@baidu.com>
Signed-off-by: Like Xu <like.xu@linux.intel.com>
---
 arch/x86/include/asm/kvm_host.h | 12 ++++++
 arch/x86/kvm/cpuid.c            |  8 +++-
 arch/x86/kvm/x86.c              | 76 ++++++++++++++++++++++++++++++++-
 3 files changed, 94 insertions(+), 2 deletions(-)

```
#### [PATCH 1/2] KVM: x86/mmu: Avoid multiple hash lookups in kvm_get_mmu_page()
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11621603
Return-Path: <SRS0=VBfj=AE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D5BE9618
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 23 Jun 2020 19:40:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C7B5220EDD
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 23 Jun 2020 19:40:46 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2387607AbgFWTkm (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 23 Jun 2020 15:40:42 -0400
Received: from mga06.intel.com ([134.134.136.31]:64955 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2387442AbgFWTk3 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 23 Jun 2020 15:40:29 -0400
IronPort-SDR: 
 TH3lobsh+GvUDkEROc0lXs4Fq2FespYfmuwIo7dCgZirFAAjTZJh4MVsqlmFSMwgJWR8V7XwTd
 M++HcgeRIgQA==
X-IronPort-AV: E=McAfee;i="6000,8403,9661"; a="205705217"
X-IronPort-AV: E=Sophos;i="5.75,272,1589266800";
   d="scan'208";a="205705217"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga003.fm.intel.com ([10.253.24.29])
  by orsmga104.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 23 Jun 2020 12:40:29 -0700
IronPort-SDR: 
 05tE0GLhuyI3F46Oq3sOoMHZmyc2D5d7erJVwrsYJ7Kd25vOwzaSSq73I+4JcjGsSHVmBV3BPy
 PcejMBCW+zAg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,272,1589266800";
   d="scan'208";a="319249367"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.152])
  by FMSMGA003.fm.intel.com with ESMTP; 23 Jun 2020 12:40:28 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Peter Feiner <pfeiner@google.com>,
        Jon Cargille <jcargill@google.com>
Subject: [PATCH 1/2] KVM: x86/mmu: Avoid multiple hash lookups in
 kvm_get_mmu_page()
Date: Tue, 23 Jun 2020 12:40:26 -0700
Message-Id: <20200623194027.23135-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
In-Reply-To: <20200623194027.23135-1-sean.j.christopherson@intel.com>
References: <20200623194027.23135-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Refactor for_each_valid_sp() to take the list of shadow pages instead of
retrieving it from a gfn to avoid doing the gfn->list hash and lookup
multiple times during kvm_get_mmu_page().

Cc: Peter Feiner <pfeiner@google.com>
Cc: Jon Cargille <jcargill@google.com>
Cc: Jim Mattson <jmattson@google.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Reviewed-By: Jon Cargille <jcargill@google.com>
---
 arch/x86/kvm/mmu/mmu.c | 17 +++++++++--------
 1 file changed, 9 insertions(+), 8 deletions(-)

```
#### [PATCH v2 1/4] KVM: x86/mmu: Don't put invalid SPs back on the list of active pages
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11621577
Return-Path: <SRS0=VBfj=AE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6F6D9161F
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 23 Jun 2020 19:35:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5EDAF20C09
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 23 Jun 2020 19:35:47 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2387513AbgFWTfq (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 23 Jun 2020 15:35:46 -0400
Received: from mga11.intel.com ([192.55.52.93]:11007 "EHLO mga11.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2387430AbgFWTfo (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 23 Jun 2020 15:35:44 -0400
IronPort-SDR: 
 sJ9sRrvxb1h5Okc9pcBYB6agzuUxgWFnBl5k//utyzCFXv1OdBKibJm+1+i3gUy5SWrC7W9i6J
 im2bQ1BqbqXg==
X-IronPort-AV: E=McAfee;i="6000,8403,9661"; a="142430969"
X-IronPort-AV: E=Sophos;i="5.75,272,1589266800";
   d="scan'208";a="142430969"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga007.fm.intel.com ([10.253.24.52])
  by fmsmga102.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 23 Jun 2020 12:35:44 -0700
IronPort-SDR: 
 f/IL09ce9Xl12I9sC84qWOGB+ALwlnlDkcqdbVGwKzExiEQfaqkLOU6xbOyYA/jWnWsc4Xx629
 B2L/gsVdejgQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,272,1589266800";
   d="scan'208";a="263428289"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.152])
  by fmsmga007.fm.intel.com with ESMTP; 23 Jun 2020 12:35:43 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v2 1/4] KVM: x86/mmu: Don't put invalid SPs back on the list
 of active pages
Date: Tue, 23 Jun 2020 12:35:39 -0700
Message-Id: <20200623193542.7554-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
In-Reply-To: <20200623193542.7554-1-sean.j.christopherson@intel.com>
References: <20200623193542.7554-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Delete a shadow page from the invalidation list instead of throwing it
back on the list of active pages when it's a root shadow page with
active users.  Invalid active root pages will be explicitly freed by
mmu_free_root_page() when the root_count hits zero, i.e. they don't need
to be put on the active list to avoid leakage.

Use sp->role.invalid to detect that a shadow page has already been
zapped, i.e. is not on a list.

WARN if an invalid page is encountered when zapping pages, as it should
now be impossible.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/mmu/mmu.c | 28 ++++++++++++++++++++--------
 1 file changed, 20 insertions(+), 8 deletions(-)

```
#### [PATCH] KVM: x86: report sev_pin_memory errors with PTR_ERR
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11620149
Return-Path: <SRS0=VBfj=AE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9857514F6
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 23 Jun 2020 09:17:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7A11C20738
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 23 Jun 2020 09:17:42 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="F0tg31Kl"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731944AbgFWJRb (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 23 Jun 2020 05:17:31 -0400
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:57682 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1731887AbgFWJRb (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 23 Jun 2020 05:17:31 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1592903849;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=yiRnWHa9VVB1e8yxG1o2k5x8axs0i04jT/k6YjjG0Ms=;
        b=F0tg31KlJEWsT8ByuvUPbpq2SI4IVldwNOxJHQzEkJmrhfgNly8KMPgFFUMCouaENj2Jz/
        ylQAOyIt1lpSvyVR+rdOXFusNbnwWnlURHsJxW5URc/3onmtCYhy/bSkktmKIuDk2b7ln1
        cxPW0kpfmw4JQ5fUltMeE90Ha6OrtFA=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-15-BsDaQ65hNNuuXgpF2hlGSw-1; Tue, 23 Jun 2020 05:17:27 -0400
X-MC-Unique: BsDaQ65hNNuuXgpF2hlGSw-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 68A0619057A0;
        Tue, 23 Jun 2020 09:17:26 +0000 (UTC)
Received: from virtlab511.virt.lab.eng.bos.redhat.com
 (virtlab511.virt.lab.eng.bos.redhat.com [10.19.152.198])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 12D887166D;
        Tue, 23 Jun 2020 09:17:26 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>
Subject: [PATCH] KVM: x86: report sev_pin_memory errors with PTR_ERR
Date: Tue, 23 Jun 2020 05:17:25 -0400
Message-Id: <20200623091725.271605-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Callers of sev_pin_memory() treat
NULL differently:

sev_launch_secret()/svm_register_enc_region() return -ENOMEM
sev_dbg_crypt() returns -EFAULT.

Switching to ERR_PTR() preserves the error and enables cleaner reporting of
different kinds of failures.

Suggested-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/svm/sev.c | 22 ++++++++++++----------
 1 file changed, 12 insertions(+), 10 deletions(-)

```
#### [PATCH] KVM: x86: Use VMCALL and VMMCALL mnemonics in kvm_para.h
##### From: Uros Bizjak <ubizjak@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Uros Bizjak <ubizjak@gmail.com>
X-Patchwork-Id: 11621467
Return-Path: <SRS0=VBfj=AE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 08AC792A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 23 Jun 2020 18:34:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E193C2083B
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 23 Jun 2020 18:34:53 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="Tz4wtzJy"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1733223AbgFWSeu (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 23 Jun 2020 14:34:50 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:36022 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1733149AbgFWSet (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 23 Jun 2020 14:34:49 -0400
Received: from mail-ed1-x541.google.com (mail-ed1-x541.google.com
 [IPv6:2a00:1450:4864:20::541])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 4C7A8C061573;
        Tue, 23 Jun 2020 11:34:49 -0700 (PDT)
Received: by mail-ed1-x541.google.com with SMTP id g1so17127771edv.6;
        Tue, 23 Jun 2020 11:34:49 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=n1T35J+HW/tfUciSMhCodCWFYqAaiFCQ5lEz9exQc/o=;
        b=Tz4wtzJyPad5gy/IG2huil3XWoC4trTDH3+djIUF3u7v/4p/SjuUx+r/eYHwG9y8jd
         nk5i/IcG6i09Svx0gslTFU6+uZleU99hIi5QCVx+oSEqkoxfnNJbMcK0xZue9Vo3T6a1
         gxxXhLBXgoXWe23MRaAKzJTnsQKT/IAGiH0lmQZ1O9igePrxYt/j6p17WLpPYMiOfcDY
         NOJGpdKZ9TYjFy8tzG3HPottQ3/h1xyLws2qMfEcLEvfXFnWOTLivm7isJ0zKvhUG+G4
         cLVxTeiheNchYJcjJc5JnHmeJ3IGnuP3bB66TNZutt2n2pnGlcsVEucag+efFl5jFEZB
         oHjA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=n1T35J+HW/tfUciSMhCodCWFYqAaiFCQ5lEz9exQc/o=;
        b=EB6hDhyEfTiOsw4IbzKENf63EQq1tRE3BR7WGB5AhLad4y1eP3CaBuRrAQUX7Bavim
         aGGCM05Ztdo1WkDPeUoDCoj6Ws/fSV+XAxjmxIkf2Brw6Ark0uGnGbg4Hb259lkImUYJ
         WU4zVupQlkDW1XqtAqe4/bGenz2HCS7M6KWDZdOcCrjL1hkOFsU5r4WAhFP8ZN2Di1Sd
         w30nrPIdKL57NFKwgKsR4nM+GO4soZfONlpcovVB6erFS+YZyvznS4K+oJHDw0CuzVu/
         pCPs6M3a3dMsUkK+82YRPUQHJKj0bfwcIClOIaa+H5DcAdSwCbsnL9c6I/1HMYRGpTMj
         d0HA==
X-Gm-Message-State: AOAM533DepYh5o/vja5dvNgWRv2oft2GhTYX4Q3qiQtslYvojTyCn+7w
        xe4PEGYwV/LaETnsehVpCrytpyv8OOs=
X-Google-Smtp-Source: 
 ABdhPJz4BjlhlNpvHxHxx5ypE7pv9WMsb5v1cQUv3j3XfPneaGq69WI+XsdYygOC7WX+OlWM9d/kEw==
X-Received: by 2002:aa7:c41a:: with SMTP id j26mr23493827edq.13.1592937287680;
        Tue, 23 Jun 2020 11:34:47 -0700 (PDT)
Received: from localhost.localdomain (93-103-18-160.static.t-2.net.
 [93.103.18.160])
        by smtp.gmail.com with ESMTPSA id
 y26sm15341379edv.91.2020.06.23.11.34.46
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 23 Jun 2020 11:34:47 -0700 (PDT)
From: Uros Bizjak <ubizjak@gmail.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: Uros Bizjak <ubizjak@gmail.com>,
        Paolo Bonzini <pbonzini@redhat.com>
Subject: [PATCH] KVM: x86: Use VMCALL and VMMCALL mnemonics in kvm_para.h
Date: Tue, 23 Jun 2020 20:34:39 +0200
Message-Id: <20200623183439.5526-1-ubizjak@gmail.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Current minimum required version of binutils is 2.23,
which supports VMCALL and VMMCALL instruction mnemonics.

Replace the byte-wise specification of VMCALL and
VMMCALL with these proper mnemonics.

Signed-off-by: Uros Bizjak <ubizjak@gmail.com>
CC: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/include/asm/kvm_para.h | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v2 1/7] KVM: X86: Reset vcpu->arch.cpuid_nent to 0 if SET_CPUID fails
##### From: Xiaoyao Li <xiaoyao.li@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xiaoyao Li <xiaoyao.li@intel.com>
X-Patchwork-Id: 11620529
Return-Path: <SRS0=VBfj=AE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AA59B92A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 23 Jun 2020 11:58:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9AC7E20738
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 23 Jun 2020 11:58:27 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732533AbgFWL6Y (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 23 Jun 2020 07:58:24 -0400
Received: from mga05.intel.com ([192.55.52.43]:58474 "EHLO mga05.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1732364AbgFWL6Y (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 23 Jun 2020 07:58:24 -0400
IronPort-SDR: 
 bnkQ12CZuUHAwuve9KzbHcNOCrE0T56NUMctU2PkB5y7Rn4HM6xU6O5sllJZATmIgvALOO3xq7
 NhdrHmW6HaFg==
X-IronPort-AV: E=McAfee;i="6000,8403,9660"; a="228710034"
X-IronPort-AV: E=Sophos;i="5.75,271,1589266800";
   d="scan'208";a="228710034"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga007.jf.intel.com ([10.7.209.58])
  by fmsmga105.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 23 Jun 2020 04:58:23 -0700
IronPort-SDR: 
 qptkiFY9mzn1oJIiSEjbe6MsnPiPaMjdFMI/J/dgVDyy8cDOsUAdDbzlZbKr8yFOdewfLcubsE
 y68dUnbyL6zQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,271,1589266800";
   d="scan'208";a="285745184"
Received: from lxy-dell.sh.intel.com ([10.239.159.21])
  by orsmga007.jf.intel.com with ESMTP; 23 Jun 2020 04:58:20 -0700
From: Xiaoyao Li <xiaoyao.li@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>
Cc: Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Xiaoyao Li <xiaoyao.li@intel.com>
Subject: [PATCH v2 1/7] KVM: X86: Reset vcpu->arch.cpuid_nent to 0 if
 SET_CPUID fails
Date: Tue, 23 Jun 2020 19:58:10 +0800
Message-Id: <20200623115816.24132-2-xiaoyao.li@intel.com>
X-Mailer: git-send-email 2.18.2
In-Reply-To: <20200623115816.24132-1-xiaoyao.li@intel.com>
References: <20200623115816.24132-1-xiaoyao.li@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

It needs to invalidate CPUID configruations if usersapce provides
illegal input.

Signed-off-by: Xiaoyao Li <xiaoyao.li@intel.com>
---
 arch/x86/kvm/cpuid.c | 4 ++++
 1 file changed, 4 insertions(+)

```
#### [PATCH v3 1/2] tests/qtest/arm-cpu-features: Add feature setting tests
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
 <philmd@redhat.com>
X-Patchwork-Id: 11620119
Return-Path: <SRS0=VBfj=AE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F3271161F
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 23 Jun 2020 09:06:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D65EC20776
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 23 Jun 2020 09:06:36 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="cqVXgBlg"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731965AbgFWJGf (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 23 Jun 2020 05:06:35 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:31046 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1731921AbgFWJGf (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 23 Jun 2020 05:06:35 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1592903194;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
  content-type:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=NFodWqskMtC/5PQ2GwuPpH+2hReee1VihIY8eKIqRQU=;
        b=cqVXgBlgosFUCtjYcJNO5iyObAlRtXeyepTiZ7e+r3aKU1WIpsJ87weP+aWr9vRh5nHqQx
        SAa3n+y0y7c3a8kWz7LMHCSJ27Fxg9qRH3iTo5BMPDuOMpgRyATciL2YoTRebuZLxQXWp+
        S36Nrdy+tHoyLGQO9OqfeNYgjxaEUuo=
Received: from mail-wr1-f69.google.com (mail-wr1-f69.google.com
 [209.85.221.69]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-433-uwLtroUHPGSPCrBybJSE9Q-1; Tue, 23 Jun 2020 05:06:32 -0400
X-MC-Unique: uwLtroUHPGSPCrBybJSE9Q-1
Received: by mail-wr1-f69.google.com with SMTP id y13so1388965wrp.13
        for <kvm@vger.kernel.org>; Tue, 23 Jun 2020 02:06:32 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=NFodWqskMtC/5PQ2GwuPpH+2hReee1VihIY8eKIqRQU=;
        b=KPHQNYwY3414r041f7FJ52VjJv6yf1qk46UYyc9csGrVebrnBTmFg1xP9Lcl0zUSAW
         E0ti8zL5Z5NXa1SNYZoIgD9zAG25fMvc8bVkrVJQ+V0WdnfMTd75fTFORNrpCFSj3luv
         NsPiqC0/dpuWXnHxtKMGRjFfPLgkfWdfdJ7K7gngky61j8malhtBOr/Oy0chqlRizncf
         zh2dTOY+gFQ5T1peAe49UodShgFoHBGmfug3Nx3MD1b2YLUhNUdHIaDygYjyyUukZOc7
         zdhwssm9ES1MtwppEigiJWfndWEz1hL4YXuuBysR9r93Mh8opvOCZjwjvAvkhZKUDwGH
         9WkA==
X-Gm-Message-State: AOAM530MvtYddu/r1mXnZD57Wp6WN+v3uzm0S57cQ+k8XIn54+/JOIni
        PSyD6f7Ce9pFrGTQqRun8u4KcQFhyq7SCumRcDsHsBEnBrDlcghuAQOeRIUsdLrmLJYoAurpsrm
        hkZAoqXfB5dLv
X-Received: by 2002:adf:fa81:: with SMTP id h1mr13967365wrr.266.1592903190739;
        Tue, 23 Jun 2020 02:06:30 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJxYp7EOW24aIihuYBSTeyCt0a8qu7PFtl2vjpx6/D5IDweqkFR4nJCyT8X1HMCfow4T+lhWtA==
X-Received: by 2002:adf:fa81:: with SMTP id h1mr13967350wrr.266.1592903190490;
        Tue, 23 Jun 2020 02:06:30 -0700 (PDT)
Received: from localhost.localdomain (1.red-83-51-162.dynamicip.rima-tde.net.
 [83.51.162.1])
        by smtp.gmail.com with ESMTPSA id
 g195sm2896048wme.38.2020.06.23.02.06.29
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 23 Jun 2020 02:06:30 -0700 (PDT)
From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>
To: qemu-devel@nongnu.org
Cc: qemu-arm@nongnu.org, Thomas Huth <thuth@redhat.com>,
 Paolo Bonzini <pbonzini@redhat.com>,
 Peter Maydell <peter.maydell@linaro.org>, kvm@vger.kernel.org,
 Andrew Jones <drjones@redhat.com>, Laurent Vivier <lvivier@redhat.com>,
	=?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>
Subject: [PATCH v3 1/2] tests/qtest/arm-cpu-features: Add feature setting
 tests
Date: Tue, 23 Jun 2020 11:06:21 +0200
Message-Id: <20200623090622.30365-2-philmd@redhat.com>
X-Mailer: git-send-email 2.21.3
In-Reply-To: <20200623090622.30365-1-philmd@redhat.com>
References: <20200623090622.30365-1-philmd@redhat.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Andrew Jones <drjones@redhat.com>

Some cpu features may be enabled and disabled for all configurations
that support the feature. Let's test that.

A recent regression[*] inspired adding these tests.

[*] '-cpu host,pmu=on' caused a segfault

Signed-off-by: Andrew Jones <drjones@redhat.com>
Message-Id: <20200623082310.17577-1-drjones@redhat.com>
Signed-off-by: Philippe Mathieu-Daudé <philmd@redhat.com>
---
 tests/qtest/arm-cpu-features.c | 38 ++++++++++++++++++++++++++++++----
 1 file changed, 34 insertions(+), 4 deletions(-)

```
#### [PATCH v2] SVM: add test for nested guest RIP corruption
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 11620317
Return-Path: <SRS0=VBfj=AE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6FFF390
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 23 Jun 2020 10:52:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5785720768
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 23 Jun 2020 10:52:16 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="RIE/Tnsi"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732413AbgFWKwP (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 23 Jun 2020 06:52:15 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:41150 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1732375AbgFWKwO (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 23 Jun 2020 06:52:14 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1592909532;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=MtuBBuxFtTIbU5iSzkSfmj8H1qBI68ds9qLJJkYV0+c=;
        b=RIE/Tnsie/lAzW+H9lO9jYiqJksROONiaVQRhyo8JY+0N3u4pKqw2BFmjDpFMMtIuoy+eK
        DhPKMh56iIMiazKCj88DKqtuDppo1lYRUcxj0usDdv+wS3eiIKIZzykyfeWw7ZIumQq5Oc
        V/+ZYV7Wmtiql/xNJ73iE8fJIhDe3bc=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-438-15iMkhFWNiKhCE6nMtiIiw-1; Tue, 23 Jun 2020 06:52:10 -0400
X-MC-Unique: 15iMkhFWNiKhCE6nMtiIiw-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id D325418FF660
        for <kvm@vger.kernel.org>; Tue, 23 Jun 2020 10:52:09 +0000 (UTC)
Received: from starship.redhat.com (unknown [10.35.206.216])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 8869619934;
        Tue, 23 Jun 2020 10:52:08 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH v2] SVM: add test for nested guest RIP corruption
Date: Tue, 23 Jun 2020 13:52:07 +0300
Message-Id: <20200623105207.149798-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This adds a unit test for SVM nested register corruption that happened when
L0 was emulating an instruction, but then injecting an interrupt intercept to L1, which
lead it to give L1 vmexit handler stale (pre emulation) values of RAX,RIP and RSP.

This test detects the RIP corruption (situation when RIP is at the start of
the emulated instruction but the instruction, was already executed.

The upstream commit that fixed this bug is b6162e82aef19fee9c32cb3fe9ac30d9116a8c73
  KVM: nSVM: Preserve registers modifications done before nested_svm_vmexit()

Signed-off-by: Maxim Levitsky <mlevitsk@redhat.com>
---
 x86/svm_tests.c | 102 ++++++++++++++++++++++++++++++++++++++++++++++++
 1 file changed, 102 insertions(+)

```
