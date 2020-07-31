#### [GIT PULL 1/2] s390/setup: diag 318: refactor struct
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11692673
Return-Path: <SRS0=wP1B=BJ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 075A713B6
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Jul 2020 09:49:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id ED55420838
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Jul 2020 09:49:11 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729544AbgG3JtK (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 30 Jul 2020 05:49:10 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:47508 "EHLO
        mx0b-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1729532AbgG3JtJ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 30 Jul 2020 05:49:09 -0400
Received: from pps.filterd (m0127361.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 06U9Wfuw167655;
        Thu, 30 Jul 2020 05:49:08 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 32krgdwyss-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 30 Jul 2020 05:49:08 -0400
Received: from m0127361.ppops.net (m0127361.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 06U9WokB168418;
        Thu, 30 Jul 2020 05:49:08 -0400
Received: from ppma04fra.de.ibm.com (6a.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.106])
        by mx0a-001b2d01.pphosted.com with ESMTP id 32krgdwyqg-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 30 Jul 2020 05:49:08 -0400
Received: from pps.filterd (ppma04fra.de.ibm.com [127.0.0.1])
        by ppma04fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 06U9k5uJ015524;
        Thu, 30 Jul 2020 09:49:01 GMT
Received: from b06avi18878370.portsmouth.uk.ibm.com
 (b06avi18878370.portsmouth.uk.ibm.com [9.149.26.194])
        by ppma04fra.de.ibm.com with ESMTP id 32gcpwbpjc-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 30 Jul 2020 09:49:01 +0000
Received: from d06av23.portsmouth.uk.ibm.com (d06av23.portsmouth.uk.ibm.com
 [9.149.105.59])
        by b06avi18878370.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 06U9mwXv59048374
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 30 Jul 2020 09:48:58 GMT
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 8132DA404D;
        Thu, 30 Jul 2020 09:48:58 +0000 (GMT)
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 6BEF6A4040;
        Thu, 30 Jul 2020 09:48:58 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av23.portsmouth.uk.ibm.com (Postfix) with ESMTPS;
        Thu, 30 Jul 2020 09:48:58 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 25651)
        id 2E9CCE0661; Thu, 30 Jul 2020 11:48:58 +0200 (CEST)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: KVM <kvm@vger.kernel.org>, Janosch Frank <frankja@linux.ibm.com>,
        David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        linux-s390 <linux-s390@vger.kernel.org>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Claudio Imbrenda <imbrenda@linux.ibm.com>,
        Collin Walling <walling@linux.ibm.com>,
        Heiko Carstens <hca@linux.ibm.com>,
        Thomas Huth <thuth@redhat.com>
Subject: [GIT PULL 1/2] s390/setup: diag 318: refactor struct
Date: Thu, 30 Jul 2020 11:48:56 +0200
Message-Id: <20200730094857.175501-2-borntraeger@de.ibm.com>
X-Mailer: git-send-email 2.25.4
In-Reply-To: <20200730094857.175501-1-borntraeger@de.ibm.com>
References: <20200730094857.175501-1-borntraeger@de.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-UnRewURL: 0 URL was un-rewritten
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-07-30_05:2020-07-30,2020-07-30 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 clxscore=1015
 priorityscore=1501 mlxlogscore=999 mlxscore=0 adultscore=0 bulkscore=0
 suspectscore=0 impostorscore=0 phishscore=0 malwarescore=0 spamscore=0
 lowpriorityscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2007300069
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Collin Walling <walling@linux.ibm.com>

The diag 318 struct introduced in include/asm/diag.h can be
reused in KVM, so let's condense the version code fields in the
diag318_info struct for easier usage and simplify it until we
can determine how the data should be formatted.

Signed-off-by: Collin Walling <walling@linux.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
Reviewed-by: Janosch Frank <frankja@linux.ibm.com>
Link: https://lore.kernel.org/r/20200622154636.5499-2-walling@linux.ibm.com
Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 arch/s390/include/asm/diag.h | 6 ++----
 arch/s390/kernel/setup.c     | 3 +--
 2 files changed, 3 insertions(+), 6 deletions(-)

```
#### [GIT PULL] virtio, qemu_fw: bugfixes
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 11693581
Return-Path: <SRS0=wP1B=BJ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BC347722
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Jul 2020 19:30:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A3C2B21883
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Jul 2020 19:30:12 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="TK4/Arut"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730486AbgG3TaH (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 30 Jul 2020 15:30:07 -0400
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:43272 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726853AbgG3TaH (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 30 Jul 2020 15:30:07 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1596137406;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type;
        bh=Zo62zBr05G4i/w6uOCrF5bcIwehfjUuSBLT3HlEcuYQ=;
        b=TK4/ArutFiX30RTVSeQP72Z2Gg3T069qDEa8QhEdpHXY4H9Wb9h/Q4PtRO7epGbvlxFCR6
        b7xh+gPHuedTwoEnaJewZS1w/y+Nxl6KOj3YtkbirOPQVc/+g6xkdBIucTEE8VtXApf05t
        HdtsZRI1T2jnHEfDUECFPrFB3Ys83mA=
Received: from mail-wr1-f70.google.com (mail-wr1-f70.google.com
 [209.85.221.70]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-54-QKL0iWxkNVC7_REwZ5NrHw-1; Thu, 30 Jul 2020 15:30:04 -0400
X-MC-Unique: QKL0iWxkNVC7_REwZ5NrHw-1
Received: by mail-wr1-f70.google.com with SMTP id j16so8341336wrw.3
        for <kvm@vger.kernel.org>; Thu, 30 Jul 2020 12:30:04 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:mime-version
         :content-disposition;
        bh=Zo62zBr05G4i/w6uOCrF5bcIwehfjUuSBLT3HlEcuYQ=;
        b=pMu+rGIQOXWiASM29rI/HxGXPUEgciNPy0lROlNtLHP4uqCp10+U9XWvx0UipMdQ2n
         Ton8/3kk17w9LoLST9vwCTgeZ9LQLHeAfpn6nOPB8lNyTSTG/6a5YSfwA4h2F22VEAyn
         Fgp8GcklsoXmhhP3pyyI24zN4GCWwDuNaNi9RuUVDGfoWQSFKyOtceGytR3SN+Dqy9Fx
         0xey4aJ9cF70mD2Ym5U0lF7aYwtSpHvoRS945l2nTSwr0egN7XlDcvYeInh/FJ4KO4Fg
         JImMMh9UndBEemGKp/2J1DVNFiJWqoO2CFnZ2vla20dFTPs9mY0Tf+qSAM0s5juK2bEl
         wp8A==
X-Gm-Message-State: AOAM53315x3EZhZovYgluwcWc5EXfQPVIX0qizDHNSDa6YrhorVLgQmQ
        R2g3WflLfwXP8OY4itBpFJXLu+vaFZjOrzwGAzWJ18Cw9J6meaSAYN3ko7sB9+COn3PECzgLdT6
        ZMAsuMMCJJUNP
X-Received: by 2002:a5d:538a:: with SMTP id d10mr267393wrv.280.1596137403065;
        Thu, 30 Jul 2020 12:30:03 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJxM38R/gaJ4B9lHJnwY7CoXgiuKGr1JOva2N2K51sHps4St8QHQsZSys7gU+zLzyFwcYWboVQ==
X-Received: by 2002:a5d:538a:: with SMTP id d10mr267372wrv.280.1596137402764;
        Thu, 30 Jul 2020 12:30:02 -0700 (PDT)
Received: from redhat.com (bzq-79-179-105-63.red.bezeqint.net.
 [79.179.105.63])
        by smtp.gmail.com with ESMTPSA id
 w64sm9081104wmb.26.2020.07.30.12.29.59
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 30 Jul 2020 12:30:01 -0700 (PDT)
Date: Thu, 30 Jul 2020 15:29:58 -0400
From: "Michael S. Tsirkin" <mst@redhat.com>
To: Linus Torvalds <torvalds@linux-foundation.org>
Cc: kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org, linux-kernel@vger.kernel.org,
        alexander.h.duyck@linux.intel.com, chenweilong@huawei.com,
        david@redhat.com, jasowang@redhat.com, mst@redhat.com,
        rdunlap@infradead.org, stable@vger.kernel.org, wu000273@umn.edu
Subject: [GIT PULL] virtio, qemu_fw: bugfixes
Message-ID: <20200730152958-mutt-send-email-mst@kernel.org>
MIME-Version: 1.0
Content-Disposition: inline
X-Mutt-Fcc: =sent
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The following changes since commit 92ed301919932f777713b9172e525674157e983d:

  Linux 5.8-rc7 (2020-07-26 14:14:06 -0700)

are available in the Git repository at:

  https://git.kernel.org/pub/scm/linux/kernel/git/mst/vhost.git tags/for_linus

for you to fetch changes up to a96b0d061d476093cf86ca1c2de06fc57163588d:

  virtio-mem: Fix build error due to improper use 'select' (2020-07-30 11:28:17 -0400)

----------------------------------------------------------------
virtio, qemu_fw: bugfixes

A couple of last minute bugfixes.

Signed-off-by: Michael S. Tsirkin <mst@redhat.com>

----------------------------------------------------------------
Alexander Duyck (1):
      virtio-balloon: Document byte ordering of poison_val

Michael S. Tsirkin (2):
      vhost/scsi: fix up req type endian-ness
      virtio_balloon: fix up endian-ness for free cmd id

Qiushi Wu (1):
      firmware: Fix a reference count leak.

Weilong Chen (1):
      virtio-mem: Fix build error due to improper use 'select'

 drivers/firmware/qemu_fw_cfg.c  |  7 ++++---
 drivers/vhost/scsi.c            |  2 +-
 drivers/virtio/Kconfig          |  2 +-
 drivers/virtio/virtio_balloon.c | 11 ++++++++++-
 4 files changed, 16 insertions(+), 6 deletions(-)
```
#### [PATCH 4.4 15/54] x86/fpu: Disable bottom halves while loading FPU registers
##### From: Greg Kroah-Hartman <gregkh@linuxfoundation.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Greg KH <gregkh@linuxfoundation.org>
X-Patchwork-Id: 11692471
Return-Path: <SRS0=wP1B=BJ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EC87B14E3
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Jul 2020 08:16:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D37682083B
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Jul 2020 08:16:20 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1596096980;
	bh=4PIK3txsItU6RK1rxjj0QPH/Qr9nof33HTpuGYpGiww=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=a/Pzj5Wk5lohD6B9BQ1CpCSZYlKNeTO6wgziveEi5G2Y8M5YgwfNrIBpGlwFB21q5
	 hF3Zy5iQPFVT1sVkiiN8kGBJhhT+18QtvilpHgxWG6YSVXL+DlYm6zKbamOyXX3ZzW
	 PgUGd/gGVm28VmmBTBkmZwG3geHwAs92E2wivsmw=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729938AbgG3ILP (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 30 Jul 2020 04:11:15 -0400
Received: from mail.kernel.org ([198.145.29.99]:50332 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729927AbgG3ILJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 30 Jul 2020 04:11:09 -0400
Received: from localhost (83-86-89-107.cable.dynamic.v4.ziggo.nl
 [83.86.89.107])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id B62532075F;
        Thu, 30 Jul 2020 08:11:07 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1596096668;
        bh=4PIK3txsItU6RK1rxjj0QPH/Qr9nof33HTpuGYpGiww=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=f4qL2SeVrrQjgqrobKIx2L6PkMDNXFHn1nejXdAy2JlGWMFUhyvPvOdb9loS6/Bh1
         nyZRHGEQMza2G21/o47R0VrQQJJ7fjxo+gOMb1E9JeT2syu2FfOwZrzFaWl9UGTodO
         Dj89ZBrHOJMiEANmXA6dmxN5iHRy5sYZgmVljLzU=
From: Greg Kroah-Hartman <gregkh@linuxfoundation.org>
To: linux-kernel@vger.kernel.org
Cc: Greg Kroah-Hartman <gregkh@linuxfoundation.org>, stable@vger.kernel.org,
 Sebastian Andrzej Siewior <bigeasy@linutronix.de>,
 Borislav Petkov <bp@suse.de>, Ingo Molnar <mingo@kernel.org>,
 Thomas Gleixner <tglx@linutronix.de>, Andy Lutomirski <luto@kernel.org>,
 Dave Hansen <dave.hansen@linux.intel.com>, "H. Peter Anvin" <hpa@zytor.com>,
 "Jason A. Donenfeld" <Jason@zx2c4.com>, kvm ML <kvm@vger.kernel.org>,
 Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Rik van Riel <riel@surriel.com>, x86-ml <x86@kernel.org>,
 Sasha Levin <sashal@kernel.org>
Subject: [PATCH 4.4 15/54] x86/fpu: Disable bottom halves while loading FPU
 registers
Date: Thu, 30 Jul 2020 10:04:54 +0200
Message-Id: <20200730074421.942105266@linuxfoundation.org>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20200730074421.203879987@linuxfoundation.org>
References: <20200730074421.203879987@linuxfoundation.org>
User-Agent: quilt/0.66
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Sebastian Andrzej Siewior <bigeasy@linutronix.de>

[ Upstream commit 68239654acafe6aad5a3c1dc7237e60accfebc03 ]

The sequence

  fpu->initialized = 1;		/* step A */
  preempt_disable();		/* step B */
  fpu__restore(fpu);
  preempt_enable();

in __fpu__restore_sig() is racy in regard to a context switch.

For 32bit frames, __fpu__restore_sig() prepares the FPU state within
fpu->state. To ensure that a context switch (switch_fpu_prepare() in
particular) does not modify fpu->state it uses fpu__drop() which sets
fpu->initialized to 0.

After fpu->initialized is cleared, the CPU's FPU state is not saved
to fpu->state during a context switch. The new state is loaded via
fpu__restore(). It gets loaded into fpu->state from userland and
ensured it is sane. fpu->initialized is then set to 1 in order to avoid
fpu__initialize() doing anything (overwrite the new state) which is part
of fpu__restore().

A context switch between step A and B above would save CPU's current FPU
registers to fpu->state and overwrite the newly prepared state. This
looks like a tiny race window but the Kernel Test Robot reported this
back in 2016 while we had lazy FPU support. Borislav Petkov made the
link between that report and another patch that has been posted. Since
the removal of the lazy FPU support, this race goes unnoticed because
the warning has been removed.

Disable bottom halves around the restore sequence to avoid the race. BH
need to be disabled because BH is allowed to run (even with preemption
disabled) and might invoke kernel_fpu_begin() by doing IPsec.

 [ bp: massage commit message a bit. ]

Signed-off-by: Sebastian Andrzej Siewior <bigeasy@linutronix.de>
Signed-off-by: Borislav Petkov <bp@suse.de>
Acked-by: Ingo Molnar <mingo@kernel.org>
Acked-by: Thomas Gleixner <tglx@linutronix.de>
Cc: Andy Lutomirski <luto@kernel.org>
Cc: Dave Hansen <dave.hansen@linux.intel.com>
Cc: "H. Peter Anvin" <hpa@zytor.com>
Cc: "Jason A. Donenfeld" <Jason@zx2c4.com>
Cc: kvm ML <kvm@vger.kernel.org>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Rik van Riel <riel@surriel.com>
Cc: stable@vger.kernel.org
Cc: x86-ml <x86@kernel.org>
Link: http://lkml.kernel.org/r/20181120102635.ddv3fvavxajjlfqk@linutronix.de
Link: https://lkml.kernel.org/r/20160226074940.GA28911@pd.tnic
Signed-off-by: Sasha Levin <sashal@kernel.org>
---
 arch/x86/kernel/fpu/signal.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH] KVM: arm: Add trace name for ARM_NISV
##### From: Alexander Graf <graf@amazon.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Graf <graf@amazon.com>
X-Patchwork-Id: 11692667
Return-Path: <SRS0=wP1B=BJ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1437D912
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Jul 2020 09:45:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E64812075F
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Jul 2020 09:44:59 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amazon.com header.i=@amazon.com
 header.b="qMGyJ0vM"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726846AbgG3Jo4 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 30 Jul 2020 05:44:56 -0400
Received: from smtp-fw-4101.amazon.com ([72.21.198.25]:5555 "EHLO
        smtp-fw-4101.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725892AbgG3Jo4 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 30 Jul 2020 05:44:56 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.com; i=@amazon.com; q=dns/txt; s=amazon201209;
  t=1596102296; x=1627638296;
  h=from:to:cc:subject:date:message-id:mime-version;
  bh=yS8mB8k1qRFT2l/VsyZ2ew82E3uftJGYIBk/EhMUB+U=;
  b=qMGyJ0vMT1pMpR4Aus87w65xlILIcKOgwm/4CZzPsjafTFk0HkGcAVGb
   7lTP/JHssJAKD8/Y0mQ33c6dpjSgUgwD6zIm1y0UGCgk6vIjUCCiFnDEn
   Kxh3mutWD2TNLLOFAO59FLTxTcmaajlwW0ScF132SQEgk54VRD8ENvXRH
   k=;
IronPort-SDR: 
 CNk0xcG7ruz5shy5cGY4vfa2ZvAScrDvqnMExmPxQqHBcsX6Cy4H74gs+egxCgIkZa0eG1uVKb
 JMObEUP2Y+fA==
X-IronPort-AV: E=Sophos;i="5.75,414,1589241600";
   d="scan'208";a="45130693"
Received: from iad12-co-svc-p1-lb1-vlan3.amazon.com (HELO
 email-inbound-relay-1e-62350142.us-east-1.amazon.com) ([10.43.8.6])
  by smtp-border-fw-out-4101.iad4.amazon.com with ESMTP;
 30 Jul 2020 09:44:54 +0000
Received: from EX13MTAUWC001.ant.amazon.com
 (iad55-ws-svc-p15-lb9-vlan2.iad.amazon.com [10.40.159.162])
        by email-inbound-relay-1e-62350142.us-east-1.amazon.com (Postfix) with
 ESMTPS id D50C8A25A6;
        Thu, 30 Jul 2020 09:44:51 +0000 (UTC)
Received: from EX13D20UWC002.ant.amazon.com (10.43.162.163) by
 EX13MTAUWC001.ant.amazon.com (10.43.162.135) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Thu, 30 Jul 2020 09:44:51 +0000
Received: from u79c5a0a55de558.ant.amazon.com (10.43.162.85) by
 EX13D20UWC002.ant.amazon.com (10.43.162.163) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Thu, 30 Jul 2020 09:44:49 +0000
From: Alexander Graf <graf@amazon.com>
To: <kvm@vger.kernel.org>
CC: Paolo Bonzini <pbonzini@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Heinrich Schuchardt <xypron.glpk@gmx.de>,
        "Christoffer Dall" <christoffer.dall@arm.com>,
        Marc Zyngier <maz@kernel.org>, <kvmarm@lists.cs.columbia.edu>,
        <linux-kernel@vger.kernel.org>
Subject: [PATCH] KVM: arm: Add trace name for ARM_NISV
Date: Thu, 30 Jul 2020 11:44:41 +0200
Message-ID: <20200730094441.18231-1-graf@amazon.com>
X-Mailer: git-send-email 2.17.1
MIME-Version: 1.0
X-Originating-IP: [10.43.162.85]
X-ClientProxiedBy: EX13D22UWB004.ant.amazon.com (10.43.161.165) To
 EX13D20UWC002.ant.amazon.com (10.43.162.163)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Commit c726200dd106d ("KVM: arm/arm64: Allow reporting non-ISV data aborts
to userspace") introduced a mechanism to deflect MMIO traffic the kernel
can not handle to user space. For that, it introduced a new exit reason.

However, it did not update the trace point array that gives human readable
names to these exit reasons inside the trace log.

Let's fix that up after the fact, so that trace logs are pretty even when
we get user space MMIO traps on ARM.

Fixes: c726200dd106d ("KVM: arm/arm64: Allow reporting non-ISV data aborts to userspace")
Signed-off-by: Alexander Graf <graf@amazon.com>
---
 include/trace/events/kvm.h | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v2 1/4] KVM: SVM: nested: Don't allocate VMCB structures on stack
##### From: Joerg Roedel <joro@8bytes.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Joerg Roedel <joro@8bytes.org>
X-Patchwork-Id: 11693329
Return-Path: <SRS0=wP1B=BJ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6290D1392
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Jul 2020 15:44:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5473E21D95
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Jul 2020 15:44:00 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729854AbgG3Pnw (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 30 Jul 2020 11:43:52 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:38432 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729823AbgG3Pns (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 30 Jul 2020 11:43:48 -0400
Received: from theia.8bytes.org (8bytes.org
 [IPv6:2a01:238:4383:600:38bc:a715:4b6d:a889])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 27F1FC061574;
        Thu, 30 Jul 2020 08:43:48 -0700 (PDT)
Received: by theia.8bytes.org (Postfix, from userid 1000)
        id 811ED2E3; Thu, 30 Jul 2020 17:43:44 +0200 (CEST)
From: Joerg Roedel <joro@8bytes.org>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Tom Lendacky <thomas.lendacky@amd.com>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Joerg Roedel <jroedel@suse.de>
Subject: [PATCH v2 1/4] KVM: SVM: nested: Don't allocate VMCB structures on
 stack
Date: Thu, 30 Jul 2020 17:43:37 +0200
Message-Id: <20200730154340.14021-2-joro@8bytes.org>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200730154340.14021-1-joro@8bytes.org>
References: <20200730154340.14021-1-joro@8bytes.org>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Joerg Roedel <jroedel@suse.de>

Do not allocate a vmcb_control_area and a vmcb_save_area on the stack,
as these structures will become larger with future extenstions of
SVM and thus the svm_set_nested_state() function will become a too large
stack frame.

Signed-off-by: Joerg Roedel <jroedel@suse.de>
---
 arch/x86/kvm/svm/nested.c | 47 +++++++++++++++++++++++++++------------
 1 file changed, 33 insertions(+), 14 deletions(-)

```
#### [PATCH kvm-unit-tests] fw_cfg: avoid index out of bounds
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11693695
Return-Path: <SRS0=wP1B=BJ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E5E46138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Jul 2020 21:58:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CC87821883
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Jul 2020 21:58:29 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="QJRhiUGR"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730651AbgG3V62 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 30 Jul 2020 17:58:28 -0400
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:21136 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1730635AbgG3V62 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 30 Jul 2020 17:58:28 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1596146307;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=+1f/uSLSGKmf8jEEPF1yVvJi+XRpXH6xSbKl2HyV+QQ=;
        b=QJRhiUGR8rbqoBHU25qB9Vvr2W1RXtIf/IHEXwARyvLokVr0xrogVZILJEv9GnmcLpc7sP
        UnEy4MT9wN4jAqXhqktXSWHYsTpBEy6+rjrmgr5BJA5rHHN0tbahejyHe5Inj/ya5zXvdO
        9Njnz3ZoB168fQhI5X+nVkUtwn3lP0o=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-63-xh4orQasNqKZzJK2iyoAaw-1; Thu, 30 Jul 2020 17:58:11 -0400
X-MC-Unique: xh4orQasNqKZzJK2iyoAaw-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 8D77F800685
        for <kvm@vger.kernel.org>; Thu, 30 Jul 2020 21:58:10 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 5A40569335
        for <kvm@vger.kernel.org>; Thu, 30 Jul 2020 21:58:10 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: kvm@vger.kernel.org
Subject: [PATCH kvm-unit-tests] fw_cfg: avoid index out of bounds
Date: Thu, 30 Jul 2020 17:58:09 -0400
Message-Id: <20200730215809.1970-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

clang compilation fails with

lib/x86/fwcfg.c:32:3: error: array index 17 is past the end of the array (which contains 16 elements) [-Werror,-Warray-bounds]
                fw_override[FW_CFG_MAX_RAM] = atol(str) * 1024 * 1024;

The reason is that FW_CFG_MAX_RAM does not exist in the fw-cfg spec and was
added for bare metal support.  Fix the size of the array and rename FW_CFG_MAX_ENTRY
to FW_CFG_NUM_ENTRIES, so that it is clear that it must be one plus the
highest valid entry.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 lib/x86/fwcfg.c | 6 +++---
 lib/x86/fwcfg.h | 5 ++++-
 2 files changed, 7 insertions(+), 4 deletions(-)

```
#### [PATCH] KVM: x86: Use MMCONFIG for all PCI config space accesses
##### From: Julia Suvorova <jusual@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Julia Suvorova <jusual@redhat.com>
X-Patchwork-Id: 11693583
Return-Path: <SRS0=wP1B=BJ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2D82F1392
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Jul 2020 19:37:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1503B20809
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Jul 2020 19:37:13 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="cJ5Ex6mu"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727972AbgG3ThM (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 30 Jul 2020 15:37:12 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:41436 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726650AbgG3ThL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 30 Jul 2020 15:37:11 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1596137830;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=evGWKkVwKQbCUf877DPL3WNOIsuP9Jsv7c2BA2D1qwo=;
        b=cJ5Ex6muHurYQD1DoKzGQr/Vdh7V42t/Vj9qJUr/8nUiG7+2cby5WJJDEUElqi0DoXSaNC
        cJaDUQ7IqpUkJRvpcM/kXHKqvJr8pXDeTnznYJEhKjptyTrGLTZOSOMvpsATVM4fACglib
        Jkja/9l/xKbu9HDhbP4LfNEL3HJx570=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-476-PkkDqE-UMYi3wYkWz6A3QQ-1; Thu, 30 Jul 2020 15:37:07 -0400
X-MC-Unique: PkkDqE-UMYi3wYkWz6A3QQ-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id DFC11102C7EE;
        Thu, 30 Jul 2020 19:37:05 +0000 (UTC)
Received: from localhost.localdomain.com (unknown [10.40.192.46])
        by smtp.corp.redhat.com (Postfix) with ESMTPS id 735A51002393;
        Thu, 30 Jul 2020 19:36:45 +0000 (UTC)
From: Julia Suvorova <jusual@redhat.com>
To: kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, Bjorn Helgaas <helgaas@kernel.org>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Matthew Wilcox <willy@infradead.org>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Andy Shevchenko <andy.shevchenko@gmail.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Julia Suvorova <jusual@redhat.com>
Subject: [PATCH] KVM: x86: Use MMCONFIG for all PCI config space accesses
Date: Thu, 30 Jul 2020 21:35:10 +0200
Message-Id: <20200730193510.578309-1-jusual@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Using MMCONFIG instead of I/O ports cuts the number of config space
accesses in half, which is faster on KVM and opens the door for
additional optimizations such as Vitaly's "[PATCH 0/3] KVM: x86: KVM
MEM_PCI_HOLE memory":
https://lore.kernel.org/kvm/20200728143741.2718593-1-vkuznets@redhat.com

However, this change will not bring significant performance improvement
unless it is running on x86 within a hypervisor. Moreover, allowing
MMCONFIG access for addresses < 256 can be dangerous for some devices:
see commit a0ca99096094 ("PCI x86: always use conf1 to access config
space below 256 bytes"). That is why a special feature flag is needed.

Introduce KVM_FEATURE_PCI_GO_MMCONFIG, which can be enabled when the
configuration is known to be safe (e.g. in QEMU).

Signed-off-by: Julia Suvorova <jusual@redhat.com>
---
 Documentation/virt/kvm/cpuid.rst     |  4 ++++
 arch/x86/include/uapi/asm/kvm_para.h |  1 +
 arch/x86/kernel/kvm.c                | 14 ++++++++++++++
 3 files changed, 19 insertions(+)

```
#### [PATCH-for-5.1?] util/pagesize: Make qemu_real_host_page_size of type size_t
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
 <philmd@redhat.com>
X-Patchwork-Id: 11693105
Return-Path: <SRS0=wP1B=BJ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F3B9213B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Jul 2020 13:59:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D72A320838
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Jul 2020 13:59:46 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="YdYLuZT6"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729090AbgG3N7q (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 30 Jul 2020 09:59:46 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:28700 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1728462AbgG3N7o (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 30 Jul 2020 09:59:44 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1596117581;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
  content-type:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=QVsnilQZ1vhpy0OO9SwSmJY9XUdq3f2mYSRQhQYQpd0=;
        b=YdYLuZT6wlqDhaAorL1Aq2nTfmIhFddkSBZ0OTTRA6tJ6oAxJ09IQtT6xbbP5tvzRqtAij
        Lxveh6O2SbQrbcoIIhWm4kTopSDaWbRbWB03Yn188IBfZGH2NKsmxhcte0aWQoPByfoGrh
        +NANnXR9k9BEVEgwiW/ThjDLeAtuzjY=
Received: from mail-wm1-f72.google.com (mail-wm1-f72.google.com
 [209.85.128.72]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-254-1Mc-v9YmPR-LOu4Co5zOLA-1; Thu, 30 Jul 2020 09:59:39 -0400
X-MC-Unique: 1Mc-v9YmPR-LOu4Co5zOLA-1
Received: by mail-wm1-f72.google.com with SMTP id a5so2266663wmj.5
        for <kvm@vger.kernel.org>; Thu, 30 Jul 2020 06:59:39 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=QVsnilQZ1vhpy0OO9SwSmJY9XUdq3f2mYSRQhQYQpd0=;
        b=ab2Rlvc7EPsEfXOdG7h6mZxi8pUdtW0LZ+7s4LV1uW/0tZ/RhyfcVzngVZsRzfRNrr
         xhOBtbW6ZPTUT31KeubfYLaeIo2laXwTtp3D0SGAPPtLSW8mSHacgE5V2oexdMCo0aVi
         lNxam0eNkIWmmbAhQ0i85oKhgscVcsiTbphivTIj0EWVtaRvFbGH5tsuhzut7G2elRzl
         pwBEpy1Gks6e8ivsi0PHhnvUcjQBKU3kJ6/n0aXoMuCjkFRYI9lnfiec0Bk0eBnlqwk7
         WiQSu2FlhOoP5BwbBu2q/wmK+nkqT0dFeVz2B8xk+k+adhPCqAezQjeyI3KgW63RULL6
         UfcQ==
X-Gm-Message-State: AOAM5338uqyyCzijDF2uP/lzvVYY9xd+T5N0xUT+7AP1ZTGarpEtIU2a
        PnAmUb3j1Ksw0o3U/ZxoIgAF8dfFnXuQcTBcoshABjFCnkSkZMMLPA1iwHWBgwiXHUurr8jYA4W
        wKsvaI0DSK6NF
X-Received: by 2002:adf:f7c3:: with SMTP id a3mr2889844wrq.162.1596117578422;
        Thu, 30 Jul 2020 06:59:38 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJwTXtEmmLwOZCBchzadGbKx9FHz1Av/y+TsvELbV7aOdz4Ua8L9CsS4+c2FcuHNw7nHHW9XBQ==
X-Received: by 2002:adf:f7c3:: with SMTP id a3mr2889823wrq.162.1596117578170;
        Thu, 30 Jul 2020 06:59:38 -0700 (PDT)
Received: from localhost.localdomain (214.red-88-21-68.staticip.rima-tde.net.
 [88.21.68.214])
        by smtp.gmail.com with ESMTPSA id
 y11sm10120598wrs.80.2020.07.30.06.59.36
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 30 Jul 2020 06:59:37 -0700 (PDT)
From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>
To: qemu-devel@nongnu.org
Cc: Richard Henderson <rth@twiddle.net>,
 David Gibson <david@gibson.dropbear.id.au>,
 "Michael S. Tsirkin" <mst@redhat.com>, Kaige Li <likaige@loongson.cn>,
 qemu-block@nongnu.org, Paolo Bonzini <pbonzini@redhat.com>,
 Juan Quintela <quintela@redhat.com>, Kevin Wolf <kwolf@redhat.com>,
 Markus Armbruster <armbru@redhat.com>,
 "Dr. David Alan Gilbert" <dgilbert@redhat.com>,
 Max Reitz <mreitz@redhat.com>, Stefano Garzarella <sgarzare@redhat.com>,
 kvm@vger.kernel.org, David Hildenbrand <david@redhat.com>,
 qemu-ppc@nongnu.org,
 =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>,
 Bruce Rogers <brogers@suse.com>
Subject: [PATCH-for-5.1?] util/pagesize: Make qemu_real_host_page_size of type
 size_t
Date: Thu, 30 Jul 2020 15:59:35 +0200
Message-Id: <20200730135935.23968-1-philmd@redhat.com>
X-Mailer: git-send-email 2.21.3
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We use different types to hold 'qemu_real_host_page_size'.
Unify picking 'size_t' which seems the best candidate.

Doing so fix a format string issue in hw/virtio/virtio-mem.c
reported when building with GCC 4.9.4:

  hw/virtio/virtio-mem.c: In function ‘virtio_mem_set_block_size’:
  hw/virtio/virtio-mem.c:756:9: error: format ‘%x’ expects argument of type ‘unsigned int’, but argument 7 has type ‘uintptr_t’ [-Werror=format=]
         error_setg(errp, "'%s' property has to be at least 0x%" PRIx32, name,
         ^

Fixes: 910b25766b ("virtio-mem: Paravirtualized memory hot(un)plug")
Reported-by: Bruce Rogers <brogers@suse.com>
Signed-off-by: Philippe Mathieu-Daudé <philmd@redhat.com>
---
 include/exec/ram_addr.h  | 4 ++--
 include/qemu/osdep.h     | 2 +-
 accel/kvm/kvm-all.c      | 3 ++-
 block/qcow2-cache.c      | 2 +-
 exec.c                   | 8 ++++----
 hw/ppc/spapr_pci.c       | 2 +-
 hw/virtio/virtio-mem.c   | 2 +-
 migration/migration.c    | 2 +-
 migration/postcopy-ram.c | 2 +-
 monitor/misc.c           | 2 +-
 util/pagesize.c          | 2 +-
 11 files changed, 16 insertions(+), 15 deletions(-)

```
#### [PATCH-for-5.1? v2 1/2] qemu/osdep: Make QEMU_VMALLOC_ALIGN unsigned long
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
 <philmd@redhat.com>
X-Patchwork-Id: 11693151
Return-Path: <SRS0=wP1B=BJ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A251F913
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Jul 2020 14:12:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8AF892070B
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Jul 2020 14:12:59 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="JFjXR7g7"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729356AbgG3OM6 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 30 Jul 2020 10:12:58 -0400
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:49141 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726581AbgG3OM5 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 30 Jul 2020 10:12:57 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1596118376;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
  content-type:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=wzBIF3mB2xmF46OsHhJUcCq/p+2yfCrRkyersC8FDx0=;
        b=JFjXR7g75YRihgYWG6ACIWyE2NmJ/GYkNm4sNx9tajSJZmvf4xyXzbpXvmm7c2gx/OSs+E
        /T/VfZCoNoRPgy3gQEUQftyxkROXiH6KdzYlgLJuRM6v4UF2uxYIdrL1fzs12VFE3wyMaG
        fTzHfruOpPf80K34ssbiCktNlDGTVPU=
Received: from mail-wr1-f71.google.com (mail-wr1-f71.google.com
 [209.85.221.71]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-12-H3E0btiIOxSTz67bx2X-Qw-1; Thu, 30 Jul 2020 10:12:54 -0400
X-MC-Unique: H3E0btiIOxSTz67bx2X-Qw-1
Received: by mail-wr1-f71.google.com with SMTP id 89so7982256wrr.15
        for <kvm@vger.kernel.org>; Thu, 30 Jul 2020 07:12:54 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=wzBIF3mB2xmF46OsHhJUcCq/p+2yfCrRkyersC8FDx0=;
        b=TDRbQJVSRKJ+WCNFULFWjtN1hvLDtDH2+5k95ANUXvXEf078aB1o4EXe95fg63DSKO
         PDEyDpCQKsI2LwoUE2AUumK2eh/ERHXOZo4KfIH2H4OHAnhGK5ME20vUm4d6nAoTHl+Z
         +ViHWMw/BoS8vFl3SLnizrTn8R1Wvs3i+2+TqiXoK3OXOuHgK7sINkMCBanLWdiuL36I
         /LFPR/qQL8U3S+r2E3S57mTfm2sgiX46feotMTw209b0BNMavNmgYGAl/Ls9pYwZA+yD
         1VyJ1rp2hiuD5uB5PnuWEaTi0F9BPtEShwIgPlYXhibCmUnnz/EGPKRYplMpQL2rD40k
         01Eg==
X-Gm-Message-State: AOAM531EVGg0qCYVy+t65Ur8DryrIbCUuRsaJaNsiLmpGwaiz1QnShx3
        b+UPAPnCrbwwMAKhABEbqQJADzH86TtKImzrcxrPVeC/45t1PKqlDvwDSpB5sODvEXirp2uGLei
        cjn8/rFwBV6DU
X-Received: by 2002:a05:6000:12c1:: with SMTP id
 l1mr2874739wrx.270.1596118373526;
        Thu, 30 Jul 2020 07:12:53 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJwT6wwK4v6vGZ6RN86OQz0/t9EYwC/x3YdgMMj4ZYne65BxsiQuJlNPry4tJPmuVKaL5qu6/w==
X-Received: by 2002:a05:6000:12c1:: with SMTP id
 l1mr2874704wrx.270.1596118373300;
        Thu, 30 Jul 2020 07:12:53 -0700 (PDT)
Received: from localhost.localdomain (214.red-88-21-68.staticip.rima-tde.net.
 [88.21.68.214])
        by smtp.gmail.com with ESMTPSA id
 o10sm9536174wrw.79.2020.07.30.07.12.51
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 30 Jul 2020 07:12:52 -0700 (PDT)
From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>
To: qemu-devel@nongnu.org
Cc: Stefano Garzarella <sgarzare@redhat.com>,
 Juan Quintela <quintela@redhat.com>, David Hildenbrand <david@redhat.com>,
 Max Reitz <mreitz@redhat.com>, "Michael S. Tsirkin" <mst@redhat.com>,
 Richard Henderson <rth@twiddle.net>,
 "Dr. David Alan Gilbert" <dgilbert@redhat.com>, qemu-block@nongnu.org,
 qemu-ppc@nongnu.org, Kaige Li <likaige@loongson.cn>,
 David Gibson <david@gibson.dropbear.id.au>, Kevin Wolf <kwolf@redhat.com>,
 kvm@vger.kernel.org, Markus Armbruster <armbru@redhat.com>,
 Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>
Subject: [PATCH-for-5.1? v2 1/2] qemu/osdep: Make QEMU_VMALLOC_ALIGN unsigned
 long
Date: Thu, 30 Jul 2020 16:12:44 +0200
Message-Id: <20200730141245.21739-2-philmd@redhat.com>
X-Mailer: git-send-email 2.21.3
In-Reply-To: <20200730141245.21739-1-philmd@redhat.com>
References: <20200730141245.21739-1-philmd@redhat.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

QEMU_VMALLOC_ALIGN is sometimes expanded to signed type,
other times to unsigned. Unify using unsigned.

Signed-off-by: Philippe Mathieu-Daudé <philmd@redhat.com>
---
 include/qemu/osdep.h | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
