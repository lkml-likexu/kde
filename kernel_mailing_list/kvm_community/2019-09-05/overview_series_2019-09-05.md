#### [PATCH 1/2] KVM: LAPIC: Micro optimize IPI latency
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11132207
Return-Path: <SRS0=qAVt=XA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8F9AD112C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Sep 2019 06:26:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 708532184B
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Sep 2019 06:26:41 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="kRp8zzhO"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731558AbfIEG0e (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 5 Sep 2019 02:26:34 -0400
Received: from mail-pl1-f194.google.com ([209.85.214.194]:38958 "EHLO
        mail-pl1-f194.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1731359AbfIEG0e (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 5 Sep 2019 02:26:34 -0400
Received: by mail-pl1-f194.google.com with SMTP id bd8so779437plb.6;
        Wed, 04 Sep 2019 23:26:33 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=PasM8GCX7mEGAVRsf1zB0IrqtOMIBNlDj4wL+XfNBQQ=;
        b=kRp8zzhOm5SwgB5xlXbVKho0JVc6ZWWmJPaXU3biT8N/Z1tGE/7OpGVVuQ2bNJoZYU
         tx0B6NC7jaChCi/dEexhFFmcodCd/ZbF52yx+bmH8oUkuLE/IasxU2DjjMLI4XmluW9Y
         834BzA1UwGTqG/YmBHYjZJ0XtRv9rI5yshrUIdfxMgBNYu43lU84IR+3F+5AzzrZmJvH
         /RXzxHdyF9zzvPmPWFyjIqR7YbmFRhHNE32i6jqzZTCpw0CL1VyffHLBJjO6Y/hllGzn
         1ZBrJepkYMUmS7HaN6/oT/ywknBpthdrSskr7gW9zA6DVgX5WRtT90Xe4H7sgY48V8io
         Dqsg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=PasM8GCX7mEGAVRsf1zB0IrqtOMIBNlDj4wL+XfNBQQ=;
        b=Fiq/jkFkycJBAP7bzksAq1r7uxE5gPimD/DesiI+ngLMzV+9s/koeWkcBQvgJeHB3G
         3nNrj5vsFqpJPBs1LVtbm4PccfozQ/Lcs5X3lgYd0PFZGLe2MUCAc85PgqZ17oYQ24yv
         SnuMzny30XhGesi+8Nrs8u1G23qb5lTysykposJQjahBurcbI+Xpa9nI4jv4BTrxBwI5
         k1JfrWd97lsG2GnJUmd32Mlp9iHaMWXVJkTMgykNLqbmXECwo4hDjQ9YDzhm3OKQJf0d
         S9QM2ky4/tlfIkYMM+OYRmma9a9SJG8ToJTEZU8lpCujMD0PV3A8c4hq1rwhshriN5F0
         wuuQ==
X-Gm-Message-State: APjAAAVfOQyHSqJZSMGOv6ljaJL4v+DckudvR9APJefEMAJtXQiBrwsO
        LkiQQ4ChjAwSO2oDsiN3FBtd1MtO
X-Google-Smtp-Source: 
 APXvYqz4fC9DNjfuhuH7Hjj+nAevfg1kox4DNRRwCcn4H7thFDoDqy4ad16301wTifH750eAd6bD5g==
X-Received: by 2002:a17:902:a983:: with SMTP id
 bh3mr1616757plb.311.1567664793115;
        Wed, 04 Sep 2019 23:26:33 -0700 (PDT)
Received: from localhost.localdomain ([203.205.141.123])
        by smtp.googlemail.com with ESMTPSA id
 d69sm1102941pfd.175.2019.09.04.23.26.31
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-SHA bits=128/128);
        Wed, 04 Sep 2019 23:26:32 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>
Subject: [PATCH 1/2] KVM: LAPIC: Micro optimize IPI latency
Date: Thu,  5 Sep 2019 14:26:27 +0800
Message-Id: <1567664788-10249-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

This patch optimizes the virtual IPI emulation sequence:

write ICR2                     write ICR2
write ICR                      read ICR2
read ICR            ==>        send virtual IPI
read ICR2                      write ICR
send virtual IPI

It can reduce kvm-unit-tests/vmexit.flat IPI testing latency(from sender
send IPI to sender receive the ACK) from 3319 cycles to 3203 cycles on
SKylake server.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kvm/lapic.c | 9 ++++-----
 1 file changed, 4 insertions(+), 5 deletions(-)

```
#### [GIT PULL 1/8] KVM: selftests: Split ucall.c into architecture specific files
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11132451
Return-Path: <SRS0=qAVt=XA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CAFB717EF
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Sep 2019 08:40:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A095C21848
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Sep 2019 08:40:47 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732774AbfIEIkr (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 5 Sep 2019 04:40:47 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:51128 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1731641AbfIEIkl (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 5 Sep 2019 04:40:41 -0400
Received: from pps.filterd (m0187473.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 x858bbmT032807
        for <kvm@vger.kernel.org>; Thu, 5 Sep 2019 04:40:39 -0400
Received: from e06smtp04.uk.ibm.com (e06smtp04.uk.ibm.com [195.75.94.100])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2usu18k53p-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Thu, 05 Sep 2019 04:40:38 -0400
Received: from localhost
        by e06smtp04.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Thu, 5 Sep 2019 09:40:36 +0100
Received: from b06cxnps3075.portsmouth.uk.ibm.com (9.149.109.195)
        by e06smtp04.uk.ibm.com (192.168.101.134) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Thu, 5 Sep 2019 09:40:33 +0100
Received: from d06av23.portsmouth.uk.ibm.com (d06av23.portsmouth.uk.ibm.com
 [9.149.105.59])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id x858eWQh10289270
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 5 Sep 2019 08:40:32 GMT
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 752AFA405B;
        Thu,  5 Sep 2019 08:40:32 +0000 (GMT)
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 24811A406D;
        Thu,  5 Sep 2019 08:40:32 +0000 (GMT)
Received: from dyn-9-152-224-131.boeblingen.de.ibm.com (unknown
 [9.152.224.131])
        by d06av23.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Thu,  5 Sep 2019 08:40:32 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: pbonzini@redhat.com, rkrcmar@redhat.com
Cc: kvm@vger.kernel.org, cohuck@redhat.com, borntraeger@de.ibm.com,
        linux-s390@vger.kernel.org, frankja@linux.vnet.ibm.com,
        david@redhat.com, thuth@redhat.com
Subject: [GIT PULL 1/8] KVM: selftests: Split ucall.c into architecture
 specific files
Date: Thu,  5 Sep 2019 10:40:02 +0200
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20190905084009.26106-1-frankja@linux.ibm.com>
References: <20190905084009.26106-1-frankja@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 19090508-0016-0000-0000-000002A6FD90
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19090508-0017-0000-0000-000033076EFF
Message-Id: <20190905084009.26106-2-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-09-05_02:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=0 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=999 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1906280000 definitions=main-1909050089
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Thomas Huth <thuth@redhat.com>

The way we exit from a guest to userspace is very specific to the
architecture: On x86, we use PIO, on aarch64 we are using MMIO and on
s390x we're going to use an instruction instead. The possibility to
select a type via the ucall_type_t enum is currently also completely
unused, so the code in ucall.c currently looks more complex than
required. Let's split this up into architecture specific ucall.c
files instead, so we can get rid of the #ifdefs and the unnecessary
ucall_type_t handling.

Reviewed-by: Andrew Jones <drjones@redhat.com>
Signed-off-by: Thomas Huth <thuth@redhat.com>
Acked-by: Paolo Bonzini <pbonzini@redhat.com>
Link: https://lore.kernel.org/r/20190731151525.17156-2-thuth@redhat.com
Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 tools/testing/selftests/kvm/Makefile          |   6 +-
 tools/testing/selftests/kvm/dirty_log_test.c  |   2 +-
 .../testing/selftests/kvm/include/kvm_util.h  |   8 +-
 .../testing/selftests/kvm/lib/aarch64/ucall.c | 112 +++++++++++++
 tools/testing/selftests/kvm/lib/ucall.c       | 157 ------------------
 .../testing/selftests/kvm/lib/x86_64/ucall.c  |  56 +++++++
 6 files changed, 173 insertions(+), 168 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/lib/aarch64/ucall.c
 delete mode 100644 tools/testing/selftests/kvm/lib/ucall.c
 create mode 100644 tools/testing/selftests/kvm/lib/x86_64/ucall.c

```
#### [PATCH] KVM: LAPIC: Fix SynIC Timers inject timer interrupt w/o LAPIC present
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11132721
Return-Path: <SRS0=qAVt=XA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5C541112C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Sep 2019 10:44:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 3C0AF22CF5
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Sep 2019 10:44:41 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="XULESHgX"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732288AbfIEKoh (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 5 Sep 2019 06:44:37 -0400
Received: from mail-pg1-f196.google.com ([209.85.215.196]:35800 "EHLO
        mail-pg1-f196.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727900AbfIEKog (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 5 Sep 2019 06:44:36 -0400
Received: by mail-pg1-f196.google.com with SMTP id n4so1217696pgv.2;
        Thu, 05 Sep 2019 03:44:36 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=54y2QMAiCvInXUhjF/5299Z9zWajcWTy7f1EMF8YUwY=;
        b=XULESHgX8sjFoyDdlyIWLV5v5m9Tw/PeM50SJp2525wLWiamyvwmGBlQhRfaqM5Hen
         ThdcDOIqeQa2pjdEqAaYPJrhy5YaG6dSobtLjhY4y0kbeuo3MIQCc35VFmhKZlK0SpFx
         Bt7lAi0ecdtPsa0jc6pD6XOQPf4FbngItvvYmQwD608bSqgOsxaz1AZEqd5H7AjqN3gp
         xA64PQeiICbP4OhDHlAkux4FZjU1kolLsyfakLxi01NbOtPWvDUYtzK+vEg0i4xyJiF6
         Lp9qRUyTnhqdQEBzKA16appGb6w4y6t6sHmT+fwkf5p/lnv5Nkdh1tKSh9H+16nSPoYm
         sZwg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=54y2QMAiCvInXUhjF/5299Z9zWajcWTy7f1EMF8YUwY=;
        b=IHK7m2scjj9wdhJ5OcOlehkRgYIjMHNcmS6BW85DRb1eMkOeGgJSKv2BlXzJVu7ubA
         GJ6MgS9X7OWAdkcYkbhsc9aWA1uz8QTbWNwFsP7OBHGk104OU8iKPMVbl3EQfA2HwYlY
         pudeOHSQfUn/+HHHnCHJ2GCkCQOe++9SrtK/liPYloOKKrDc4m7PiSm8e2fEfY21vSFx
         LK1QDZyPEDeeyNI3pCmKYc7tM9DgXS/32QYJfMdhEHujzHkE/9oNK70ZMf9Oun9mhbof
         JizjUXjSkSLymI1IPLH/bR14Y5n0ZN9hgveXc+6frYq0bpqYy64nt600QqeKoSY122HG
         v3Kg==
X-Gm-Message-State: APjAAAUPPJbPSKPXsDvDVmZZSIutIyn5MSAOJIrBUcVvBn95XYq/Zcco
        uWPES5WYmySk9pFPHw43iBR/TxI7
X-Google-Smtp-Source: 
 APXvYqwtfT4BMVhsNb3sr+Od6dCMm4NoT3zVCcWL1nLDUGzl6n/UlJugCP6NCIDRQP8hQ35ELauoZQ==
X-Received: by 2002:a62:3887:: with SMTP id
 f129mr2986497pfa.245.1567680275873;
        Thu, 05 Sep 2019 03:44:35 -0700 (PDT)
Received: from localhost.localdomain ([203.205.141.123])
        by smtp.googlemail.com with ESMTPSA id
 dw14sm1070779pjb.2.2019.09.05.03.44.33
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-SHA bits=128/128);
        Thu, 05 Sep 2019 03:44:35 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Vitaly Kuznetsov <vkuznets@redhat.com>
Subject: [PATCH] KVM: LAPIC: Fix SynIC Timers inject timer interrupt w/o LAPIC
 present
Date: Thu,  5 Sep 2019 18:44:30 +0800
Message-Id: <1567680270-14022-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

Reported by syzkaller:

	kasan: GPF could be caused by NULL-ptr deref or user memory access
	general protection fault: 0000 [#1] PREEMPT SMP KASAN
	RIP: 0010:__apic_accept_irq+0x46/0x740 arch/x86/kvm/lapic.c:1029
	Call Trace:
	kvm_apic_set_irq+0xb4/0x140 arch/x86/kvm/lapic.c:558
	stimer_notify_direct arch/x86/kvm/hyperv.c:648 [inline]
	stimer_expiration arch/x86/kvm/hyperv.c:659 [inline]
	kvm_hv_process_stimers+0x594/0x1650 arch/x86/kvm/hyperv.c:686
	vcpu_enter_guest+0x2b2a/0x54b0 arch/x86/kvm/x86.c:7896
	vcpu_run+0x393/0xd40 arch/x86/kvm/x86.c:8152
	kvm_arch_vcpu_ioctl_run+0x636/0x900 arch/x86/kvm/x86.c:8360
	kvm_vcpu_ioctl+0x6cf/0xaf0 arch/x86/kvm/../../../virt/kvm/kvm_main.c:2765

The testcase programs HV_X64_MSR_STIMERn_CONFIG/HV_X64_MSR_STIMERn_COUNT,
in addition, there is no lapic in the kernel, the counters value are small 
enough in order that kvm_hv_process_stimers() inject this already-expired 
timer interrupt into the guest through lapic in the kernel which triggers 
the NULL deferencing. This patch fixes it by checking lapic_in_kernel, 
discarding the inject if it is 0.

Reported-by: syzbot+dff25ee91f0c7d5c1695@syzkaller.appspotmail.com
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kvm/hyperv.c | 4 +++-
 1 file changed, 3 insertions(+), 1 deletion(-)

```
#### [PATCH kvm-unit-tests] arm: gic: enable GIC MMIO tests for GICv3 as well
##### From: Andre Przywara <andre.przywara@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andre Przywara <andre.przywara@arm.com>
X-Patchwork-Id: 11133705
Return-Path: <SRS0=qAVt=XA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B8A7B112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Sep 2019 17:21:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4173520693
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Sep 2019 17:21:29 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2389581AbfIERV1 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 5 Sep 2019 13:21:27 -0400
Received: from foss.arm.com ([217.140.110.172]:47908 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2389544AbfIERV1 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 5 Sep 2019 13:21:27 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id D1EE5337;
        Thu,  5 Sep 2019 10:21:26 -0700 (PDT)
Received: from donnerap.arm.com (donnerap.cambridge.arm.com [10.1.197.44])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 100D33F718;
        Thu,  5 Sep 2019 10:21:25 -0700 (PDT)
From: Andre Przywara <andre.przywara@arm.com>
To: Andrew Jones <drjones@redhat.com>
Cc: kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        Marc Zyngier <maz@kernel.org>
Subject: [PATCH kvm-unit-tests] arm: gic: enable GIC MMIO tests for GICv3 as
 well
Date: Thu,  5 Sep 2019 18:21:14 +0100
Message-Id: <20190905172114.215380-1-andre.przywara@arm.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

So far the GIC MMIO tests were only enabled for a GICv2 guest. Modern
machines tend to have a GICv3-only GIC, so can't run those guests.
It turns out that most GIC distributor registers we test in the unit
tests are actually the same in GICv3, so we can just enable those tests
for GICv3 guests as well.
The only exception is the CPU number in the TYPER register, which we
just protect against running on a GICv3 guest.

Signed-off-by: Andre Przywara <andre.przywara@arm.com>
---
 arm/gic.c         | 13 +++++++++++--
 arm/unittests.cfg | 16 +++++++++++-----
 lib/arm/asm/gic.h |  2 ++
 3 files changed, 24 insertions(+), 7 deletions(-)

```
#### [PATCH kvm-unit-tests] arm: prevent compiler from using unaligned accesses
##### From: Andre Przywara <andre.przywara@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andre Przywara <andre.przywara@arm.com>
X-Patchwork-Id: 11133703
Return-Path: <SRS0=qAVt=XA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 11F83112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Sep 2019 17:15:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 8FE4A20828
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Sep 2019 17:15:13 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732456AbfIERPL (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 5 Sep 2019 13:15:11 -0400
Received: from foss.arm.com ([217.140.110.172]:47828 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1730864AbfIERPL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 5 Sep 2019 13:15:11 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 80B43337;
        Thu,  5 Sep 2019 10:15:10 -0700 (PDT)
Received: from donnerap.arm.com (donnerap.cambridge.arm.com [10.1.197.44])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 986843F718;
        Thu,  5 Sep 2019 10:15:09 -0700 (PDT)
From: Andre Przywara <andre.przywara@arm.com>
To: Andrew Jones <drjones@redhat.com>
Cc: kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        Alexandru Elisei <alexandru.elisei@arm.com>,
        Paolo Bonzini <pbonzini@redhat.com>
Subject: [PATCH kvm-unit-tests] arm: prevent compiler from using unaligned
 accesses
Date: Thu,  5 Sep 2019 18:15:02 +0100
Message-Id: <20190905171502.215183-1-andre.przywara@arm.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The ARM architecture requires all accesses to device memory to be
naturally aligned[1][2]. Normal memory does not have this strict
requirement, and in fact many systems do ignore unaligned accesses
(by the means of clearing the A bit in SCTLR and accessing normal
memory). So the default behaviour of GCC assumes that unaligned accesses
are fine, at least if happening on the stack.

Now kvm-unit-tests runs some C code with the MMU off, which degrades the
whole system memory to device memory. Now every unaligned access will
fault, regardless of the A bit.
In fact there is at least one place in lib/printf.c where GCC merges
two consecutive char* accesses into one "strh" instruction, writing to
a potentially unaligned address.
This can be reproduced by configuring kvm-unit-tests for kvmtool, but
running it on QEMU, which triggers an early printf that exercises this
particular code path.

Add the -mstrict-align compiler option to the arm64 CFLAGS to fix this
problem. Also add the respective -mno-unaligned-access flag for arm.

Thanks to Alexandru for helping debugging this.

Signed-off-by: Andre Przywara <andre.przywara@arm.com>

[1] ARMv8 ARM DDI 0487E.a, B2.5.2
[2] ARMv7 ARM DDI 0406C.d, A3.2.1
---
 arm/Makefile.arm   | 1 +
 arm/Makefile.arm64 | 1 +
 2 files changed, 2 insertions(+)

```
#### [PATCH 1/2] KVM: x86: Refactor up kvm_{g,s}et_msr() to simplify callers
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11133957
Return-Path: <SRS0=qAVt=XA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B7CF61398
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Sep 2019 21:23:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 8E71D206DF
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Sep 2019 21:23:06 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2391840AbfIEVXF (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 5 Sep 2019 17:23:05 -0400
Received: from mga03.intel.com ([134.134.136.65]:37535 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2389651AbfIEVW6 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 5 Sep 2019 17:22:58 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga005.fm.intel.com ([10.253.24.32])
  by orsmga103.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 05 Sep 2019 14:22:57 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.64,471,1559545200";
   d="scan'208";a="383038927"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.41])
  by fmsmga005.fm.intel.com with ESMTP; 05 Sep 2019 14:22:56 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH 1/2] KVM: x86: Refactor up kvm_{g,s}et_msr() to simplify
 callers
Date: Thu,  5 Sep 2019 14:22:54 -0700
Message-Id: <20190905212255.26549-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.22.0
In-Reply-To: <20190905212255.26549-1-sean.j.christopherson@intel.com>
References: <20190905212255.26549-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Refactor the top-level MSR accessors to take/return the index and value
directly instead of requiring the caller to dump them into a msr_data
struct.

No functional change intended.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/include/asm/kvm_host.h |   4 +-
 arch/x86/kvm/svm.c              |   7 +--
 arch/x86/kvm/vmx/nested.c       |  22 ++-----
 arch/x86/kvm/vmx/vmx.c          |   6 +-
 arch/x86/kvm/x86.c              | 103 ++++++++++++++++----------------
 5 files changed, 61 insertions(+), 81 deletions(-)

```
#### [PATCH v3 1/4] KVM: X86: Trace vcpu_id for vmexit
##### From: Peter Xu <peterx@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11132023
Return-Path: <SRS0=qAVt=XA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4AB5E1395
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Sep 2019 02:36:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 344EC20882
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Sep 2019 02:36:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730412AbfIECgd (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 4 Sep 2019 22:36:33 -0400
Received: from mx1.redhat.com ([209.132.183.28]:42248 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1730273AbfIECgd (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 4 Sep 2019 22:36:33 -0400
Received: from mail-pf1-f198.google.com (mail-pf1-f198.google.com
 [209.85.210.198])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-GCM-SHA256 (128/128 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id F0792C04BD48
        for <kvm@vger.kernel.org>; Thu,  5 Sep 2019 02:36:32 +0000 (UTC)
Received: by mail-pf1-f198.google.com with SMTP id b8so710894pfd.5
        for <kvm@vger.kernel.org>; Wed, 04 Sep 2019 19:36:32 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=D5GbwgUbqjtNcqY0SPgp2YB/jV4XMs+EgfcVdllqHe8=;
        b=GbUkndWVUU6GR0ZCgJwqpVKpzuU6LCleyvre1RRMkw3upaal4PPEEeezl4wDSh+nVL
         aA8iD+r+p3/5LpGz0XqBRX2Qa/PrU9Ce9b1ZXza6wgidUYSZ9zACKoUr46ws2gZ9Pctt
         1PZnhg8htzzFr4YxLqKq9kCalXs05szB1ad0w1yAU+mNc9P2gK6iiYTz/SO0eZL65qSh
         4s4DjYv8Y7hCd9Jhzicpz3osJdhT/db0WvhP4ReQNkyoGCGTfPOKIp+MiRXyyh3UlOhl
         jGvBxp2OF4r+aAC6k3mxUAVfFokAE74qxEApAQFO7s3t0X+WMbgcRmpd7/C7qmwFadXN
         zBKw==
X-Gm-Message-State: APjAAAUlacAnU+ebp7y3dp5n+NP1LE9q14ZTTVVLbLHmz+XKA51GsmSW
        nq3NZo2kKRHbdVLaYRUw9CLTi+zpEg/2UdUAN4336ojX0Ibyd88PivEvuoewizrKK325gm/9Tbz
        2Ouq5yNHaGvRM
X-Received: by 2002:a17:902:67:: with SMTP id 94mr941159pla.121.1567650992224;
        Wed, 04 Sep 2019 19:36:32 -0700 (PDT)
X-Google-Smtp-Source: 
 APXvYqwiGVQPTwGuGQy7rBcAzOtUEK+ZrVZNNsNgPYaIYLZwLdkLNgka3U9b7pbZcwFOLz6B/6HG2A==
X-Received: by 2002:a17:902:67:: with SMTP id 94mr941144pla.121.1567650992091;
        Wed, 04 Sep 2019 19:36:32 -0700 (PDT)
Received: from xz-x1.redhat.com ([209.132.188.80])
        by smtp.gmail.com with ESMTPSA id
 v10sm326504pjk.23.2019.09.04.19.36.28
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 04 Sep 2019 19:36:31 -0700 (PDT)
From: Peter Xu <peterx@redhat.com>
To: kvm@vger.kernel.org
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Wanpeng Li <kernellwp@gmail.com>,
        Krish Sadhukhan <krish.sadhukhan@oracle.com>, peterx@redhat.com
Subject: [PATCH v3 1/4] KVM: X86: Trace vcpu_id for vmexit
Date: Thu,  5 Sep 2019 10:36:13 +0800
Message-Id: <20190905023616.29082-2-peterx@redhat.com>
X-Mailer: git-send-email 2.21.0
In-Reply-To: <20190905023616.29082-1-peterx@redhat.com>
References: <20190905023616.29082-1-peterx@redhat.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Tracing the ID helps to pair vmenters and vmexits for guests with
multiple vCPUs.

Reviewed-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Signed-off-by: Peter Xu <peterx@redhat.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/trace.h | 5 ++++-
 1 file changed, 4 insertions(+), 1 deletion(-)

```
#### [PATCH 1/2] Revert "vhost: access vq metadata through kernel virtual address"
##### From: Jason Wang <jasowang@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 11133005
Return-Path: <SRS0=qAVt=XA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E22E41709
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Sep 2019 12:27:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B257622DBF
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Sep 2019 12:27:56 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2389376AbfIEM1v (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 5 Sep 2019 08:27:51 -0400
Received: from mx1.redhat.com ([209.132.183.28]:60302 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726453AbfIEM1u (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 5 Sep 2019 08:27:50 -0400
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 6C81B1026FFB;
        Thu,  5 Sep 2019 12:27:50 +0000 (UTC)
Received: from jason-ThinkPad-X1-Carbon-6th.redhat.com
 (ovpn-12-44.pek2.redhat.com [10.72.12.44])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 18DFC5D9E2;
        Thu,  5 Sep 2019 12:27:44 +0000 (UTC)
From: Jason Wang <jasowang@redhat.com>
To: mst@redhat.com, jasowang@redhat.com, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org
Cc: netdev@vger.kernel.org, linux-kernel@vger.kernel.org,
        jgg@mellanox.com, aarcange@redhat.com, jglisse@redhat.com,
        linux-mm@kvack.org
Subject: [PATCH 1/2] Revert "vhost: access vq metadata through kernel virtual
 address"
Date: Thu,  5 Sep 2019 20:27:35 +0800
Message-Id: <20190905122736.19768-2-jasowang@redhat.com>
In-Reply-To: <20190905122736.19768-1-jasowang@redhat.com>
References: <20190905122736.19768-1-jasowang@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.6.2 (mx1.redhat.com [10.5.110.66]);
 Thu, 05 Sep 2019 12:27:50 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

It was reported that metadata acceleration introduces several issues,
so this patch reverts commit ff466032dc9e5a61217f22ea34b2df932786bbfc,
73f628ec9e6bcc45b77c53fe6d0c0ec55eaf82af and
0b4a7092ffe568a55bf8f3cefdf79ff666586d91.

We will rework it on the next version.

Cc: Jason Gunthorpe <jgg@mellanox.com>
Signed-off-by: Jason Wang <jasowang@redhat.com>
---
 drivers/vhost/vhost.c | 515 +-----------------------------------------
 drivers/vhost/vhost.h |  41 ----
 2 files changed, 3 insertions(+), 553 deletions(-)

```
#### [kvm-unit-tests PATCH v2 1/6] s390x: Use interrupts in SCLP and add locking
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11132707
Return-Path: <SRS0=qAVt=XA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6891315E9
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Sep 2019 10:40:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 493BD22CF6
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Sep 2019 10:40:12 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2387990AbfIEKkK (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 5 Sep 2019 06:40:10 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:37652 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S2387988AbfIEKkJ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 5 Sep 2019 06:40:09 -0400
Received: from pps.filterd (m0098399.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 x85AbGfR089201
        for <kvm@vger.kernel.org>; Thu, 5 Sep 2019 06:40:09 -0400
Received: from e06smtp07.uk.ibm.com (e06smtp07.uk.ibm.com [195.75.94.103])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2utxjhp833-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Thu, 05 Sep 2019 06:40:08 -0400
Received: from localhost
        by e06smtp07.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Thu, 5 Sep 2019 11:40:06 +0100
Received: from b06cxnps3075.portsmouth.uk.ibm.com (9.149.109.195)
        by e06smtp07.uk.ibm.com (192.168.101.137) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Thu, 5 Sep 2019 11:40:03 +0100
Received: from d06av21.portsmouth.uk.ibm.com (d06av21.portsmouth.uk.ibm.com
 [9.149.105.232])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id x85Ae2Q043057182
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 5 Sep 2019 10:40:02 GMT
Received: from d06av21.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 3529A52054;
        Thu,  5 Sep 2019 10:40:02 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.152.224.131])
        by d06av21.portsmouth.uk.ibm.com (Postfix) with ESMTP id 75FC452052;
        Thu,  5 Sep 2019 10:40:01 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, david@redhat.com, thuth@redhat.com
Subject: [kvm-unit-tests PATCH v2 1/6] s390x: Use interrupts in SCLP and add
 locking
Date: Thu,  5 Sep 2019 12:39:46 +0200
X-Mailer: git-send-email 2.17.0
In-Reply-To: <20190905103951.36522-1-frankja@linux.ibm.com>
References: <20190905103951.36522-1-frankja@linux.ibm.com>
X-TM-AS-GCONF: 00
x-cbid: 19090510-0028-0000-0000-0000039800FE
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19090510-0029-0000-0000-0000245A560D
Message-Id: <20190905103951.36522-2-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-09-05_03:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=999 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1906280000 definitions=main-1909050106
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We need to properly implement interrupt handling for SCLP, because on
z/VM and LPAR SCLP calls are not synchronous!

Also with smp CPUs have to compete for sclp. Let's add some locking,
so they execute sclp calls in an orderly fashion and don't compete for
the data buffer.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
---
 lib/s390x/asm/interrupt.h |  2 ++
 lib/s390x/interrupt.c     | 12 +++++++--
 lib/s390x/sclp-console.c  |  2 ++
 lib/s390x/sclp.c          | 55 +++++++++++++++++++++++++++++++++++++--
 lib/s390x/sclp.h          |  3 +++
 5 files changed, 70 insertions(+), 4 deletions(-)

```
#### [PATCH v2] KVM: arm/arm64: vgic: Allow more than 256 vcpus for KVM_IRQ_LINE
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11133479
Return-Path: <SRS0=qAVt=XA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D1E9E13B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Sep 2019 16:02:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 2A42A206DE
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Sep 2019 16:02:57 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1567699377;
	bh=nI1mvNKqMWwh5wiQAHDwNepkBOam6tFfyDOWevf7f+M=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=cxBWRETD9hZHzgVE8/eCG5365G2MHV9nV5XWRlMxzyRQakCU2yBoYLWa0oAMRTHt1
	 Pht9I2SogxQ+yKv47pPtDqCSwBSLBQg07HqbDv6H2zKJWhKP74scpdU1288ojAM2Ph
	 I9m3Zh6o2JZpnLuM/v3lCVYMWgNT+2dQO34AHH88=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2389437AbfIEQCz (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 5 Sep 2019 12:02:55 -0400
Received: from foss.arm.com ([217.140.110.172]:47030 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1730518AbfIEQCz (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 5 Sep 2019 12:02:55 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 577AE28;
        Thu,  5 Sep 2019 09:02:54 -0700 (PDT)
Received: from filthy-habits.cambridge.arm.com
 (filthy-habits.cambridge.arm.com [10.1.197.61])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 DB2923F67D;
        Thu,  5 Sep 2019 09:02:52 -0700 (PDT)
From: Marc Zyngier <maz@kernel.org>
To: Peter Maydell <peter.maydell@linaro.org>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Zenghui Yu <yuzenghui@huawei.com>,
        Will Deacon <will@kernel.org>,
        Eric Auger <eric.auger@redhat.com>
Cc: qemu-arm@nongnu.org, kvmarm@lists.cs.columbia.edu,
        linux-arm-kernel@lists.infradead.org, kvm@vger.kernel.org
Subject: [PATCH v2] KVM: arm/arm64: vgic: Allow more than 256 vcpus for
 KVM_IRQ_LINE
Date: Thu,  5 Sep 2019 17:02:45 +0100
Message-Id: <20190905160245.20746-1-maz@kernel.org>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

While parts of the VGIC support a large number of vcpus (we
bravely allow up to 512), other parts are more limited.

One of these limits is visible in the KVM_IRQ_LINE ioctl, which
only allows 256 vcpus to be signalled when using the CPU or PPI
types. Unfortunately, we've cornered ourselves badly by allocating
all the bits in the irq field.

Since the irq_type subfield (8 bit wide) is currently only taking
the values 0, 1 and 2 (and we have been careful not to allow anything
else), let's reduce this field to only 4 bits, and allocate the
remaining 4 bits to a vcpu2_index, which acts as a multiplier:

  vcpu_id = 256 * vcpu2_index + vcpu_index

With that, and a new capability (KVM_CAP_ARM_IRQ_LINE_LAYOUT_2)
allowing this to be discovered, it becomes possible to inject
PPIs to up to 4096 vcpus. But please just don't.

Whilst we're there, add a clarification about the use of KVM_IRQ_LINE
on arm, which is not completely conditionned by KVM_CAP_IRQCHIP.

Reported-by: Zenghui Yu <yuzenghui@huawei.com>
Reviewed-by: Eric Auger <eric.auger@redhat.com>
Reviewed-by: Zenghui Yu <yuzenghui@huawei.com>
Signed-off-by: Marc Zyngier <maz@kernel.org>
---
* From v1 (https://lore.kernel.org/r/20190818140710.23920-1-maz@kernel.org)
  - Always say that we support the new layout, no matter whether
    we have an in-kernel irqchip or not
  - Clarify use of KVM_IRQ_LINE wrt KVM_CAP_IRQCHIP
  - Collected RBs

 Documentation/virt/kvm/api.txt    | 12 ++++++++++--
 arch/arm/include/uapi/asm/kvm.h   |  4 +++-
 arch/arm64/include/uapi/asm/kvm.h |  4 +++-
 include/uapi/linux/kvm.h          |  1 +
 virt/kvm/arm/arm.c                |  2 ++
 5 files changed, 19 insertions(+), 4 deletions(-)

```
#### [PATCH v3] doc: kvm: Fix return description of KVM_SET_MSRS
##### From: Xiaoyao Li <xiaoyao.li@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xiaoyao Li <xiaoyao.li@intel.com>
X-Patchwork-Id: 11131981
Return-Path: <SRS0=qAVt=XA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8E3E81398
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Sep 2019 01:12:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7953221881
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Sep 2019 01:12:15 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730177AbfIEBML (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 4 Sep 2019 21:12:11 -0400
Received: from mga18.intel.com ([134.134.136.126]:7752 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727125AbfIEBML (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 4 Sep 2019 21:12:11 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga007.fm.intel.com ([10.253.24.52])
  by orsmga106.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 04 Sep 2019 18:12:10 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.64,468,1559545200";
   d="scan'208";a="184081805"
Received: from lxy-clx-4s.sh.intel.com ([10.239.43.44])
  by fmsmga007.fm.intel.com with ESMTP; 04 Sep 2019 18:12:08 -0700
From: Xiaoyao Li <xiaoyao.li@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>
Cc: Xiaoyao Li <xiaoyao.li@intel.com>,
        Jonathan Corbet <corbet@lwn.net>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        kvm@vger.kernel.org, linux-doc@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v3] doc: kvm: Fix return description of KVM_SET_MSRS
Date: Thu,  5 Sep 2019 08:57:37 +0800
Message-Id: <20190905005737.131067-1-xiaoyao.li@intel.com>
X-Mailer: git-send-email 2.19.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Userspace can use ioctl KVM_SET_MSRS to update a set of MSRs of guest.
This ioctl set specified MSRs one by one. If it fails to set an MSR,
e.g., due to setting reserved bits, the MSR is not supported/emulated by
KVM, etc..., it stops processing the MSR list and returns the number of
MSRs have been set successfully.

Signed-off-by: Xiaoyao Li <xiaoyao.li@intel.com>
---
v3:
  refine the description based on Sean's comment.  

v2:
  elaborate the changelog and description of ioctl KVM_SET_MSRS based on
  Sean's comments.
---
 Documentation/virt/kvm/api.txt | 7 ++++++-
 1 file changed, 6 insertions(+), 1 deletion(-)

```
#### [PATCH v3] KVM: x86: Disable posted interrupts for odd IRQs
##### From: Alexander Graf <graf@amazon.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Graf <graf@amazon.com>
X-Patchwork-Id: 11133039
Return-Path: <SRS0=qAVt=XA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8945A1862
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Sep 2019 13:05:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 72C10214E0
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Sep 2019 12:58:36 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amazon.com header.i=@amazon.com
 header.b="YSuQ5o6P"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2387580AbfIEM6e (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 5 Sep 2019 08:58:34 -0400
Received: from smtp-fw-33001.amazon.com ([207.171.190.10]:13534 "EHLO
        smtp-fw-33001.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726968AbfIEM6d (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 5 Sep 2019 08:58:33 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.com; i=@amazon.com; q=dns/txt; s=amazon201209;
  t=1567688312; x=1599224312;
  h=from:to:cc:subject:date:message-id:mime-version;
  bh=ETZlDN4IdF0kxziLoR9hjkO844T65juEVcnxEPAUrBo=;
  b=YSuQ5o6P52iMHkPH4XY/9D7nyNN8jJvFLoBQdTsQ6xvrV7/9vYGjPf+A
   VAXbT3z7RE0+H3yxl9LuAM1lbjQGlqCneYsp4qgi/nU4ayJAHAriTy91X
   U1gnl/XwtCfspVut5kl/sGoSW2xjAZVrlVHTvV+rybqTIPppJAucPoSDI
   s=;
X-IronPort-AV: E=Sophos;i="5.64,470,1559520000";
   d="scan'208";a="827706210"
Received: from sea3-co-svc-lb6-vlan2.sea.amazon.com (HELO
 email-inbound-relay-2c-2225282c.us-west-2.amazon.com) ([10.47.22.34])
  by smtp-border-fw-out-33001.sea14.amazon.com with ESMTP;
 05 Sep 2019 12:58:30 +0000
Received: from EX13MTAUWC001.ant.amazon.com
 (pdx4-ws-svc-p6-lb7-vlan3.pdx.amazon.com [10.170.41.166])
        by email-inbound-relay-2c-2225282c.us-west-2.amazon.com (Postfix) with
 ESMTPS id DB0B4A2822;
        Thu,  5 Sep 2019 12:58:29 +0000 (UTC)
Received: from EX13D20UWC001.ant.amazon.com (10.43.162.244) by
 EX13MTAUWC001.ant.amazon.com (10.43.162.135) with Microsoft SMTP Server (TLS)
 id 15.0.1367.3; Thu, 5 Sep 2019 12:58:29 +0000
Received: from u79c5a0a55de558.ant.amazon.com (10.43.161.243) by
 EX13D20UWC001.ant.amazon.com (10.43.162.244) with Microsoft SMTP Server (TLS)
 id 15.0.1367.3; Thu, 5 Sep 2019 12:58:26 +0000
From: Alexander Graf <graf@amazon.com>
To: <kvm@vger.kernel.org>
CC: <linux-kernel@vger.kernel.org>, <x86@kernel.org>,
 "H. Peter Anvin" <hpa@zytor.com>, Borislav Petkov <bp@alien8.de>,
 Ingo Molnar <mingo@redhat.com>, Thomas Gleixner <tglx@linutronix.de>,
 Joerg Roedel <joro@8bytes.org>, Jim Mattson <jmattson@google.com>,
 Wanpeng Li <wanpengli@tencent.com>, Vitaly Kuznetsov <vkuznets@redhat.com>,
 "Sean Christopherson" <sean.j.christopherson@intel.com>, =?utf-8?b?UmFkaW0g?=
	=?utf-8?b?S3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Paolo Bonzini <pbonzini@redhat.com>, Liran Alon <liran.alon@oracle.com>
Subject: [PATCH v3] KVM: x86: Disable posted interrupts for odd IRQs
Date: Thu, 5 Sep 2019 14:58:18 +0200
Message-ID: <20190905125818.22395-1-graf@amazon.com>
X-Mailer: git-send-email 2.17.1
MIME-Version: 1.0
Content-Type: text/plain
X-Originating-IP: [10.43.161.243]
X-ClientProxiedBy: EX13D07UWA003.ant.amazon.com (10.43.160.35) To
 EX13D20UWC001.ant.amazon.com (10.43.162.244)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We can easily route hardware interrupts directly into VM context when
they target the "Fixed" or "LowPriority" delivery modes.

However, on modes such as "SMI" or "Init", we need to go via KVM code
to actually put the vCPU into a different mode of operation, so we can
not post the interrupt

Add code in the VMX and SVM PI logic to explicitly refuse to establish
posted mappings for advanced IRQ deliver modes. This reflects the logic
in __apic_accept_irq() which also only ever passes Fixed and LowPriority
interrupts as posted interrupts into the guest.

This fixes a bug I have with code which configures real hardware to
inject virtual SMIs into my guest.

Signed-off-by: Alexander Graf <graf@amazon.com>
Reviewed-by: Liran Alon <liran.alon@oracle.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
---

v1 -> v2:

  - Make error message more unique
  - Update commit message to point to __apic_accept_irq()

v2 -> v3:

  - Use if() rather than switch()
  - Move abort logic into existing if() branch for broadcast irqs
  -> remove the updated error message again (thus remove R-B tag from Liran)
  - Fold VMX and SVM changes into single commit
  - Combine postability check into helper function kvm_irq_is_postable()
---
 arch/x86/include/asm/kvm_host.h | 7 +++++++
 arch/x86/kvm/svm.c              | 4 +++-
 arch/x86/kvm/vmx/vmx.c          | 6 +++++-
 3 files changed, 15 insertions(+), 2 deletions(-)

```
