#### [PATCH 1/2] KVM: X86: Single target IPI fastpath
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11235811
Return-Path: <SRS0=r51r=ZB=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 39DC61747
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat,  9 Nov 2019 07:06:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 0647121848
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat,  9 Nov 2019 07:06:02 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="eNKAefhx"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726194AbfKIHFm (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 9 Nov 2019 02:05:42 -0500
Received: from mail-pg1-f193.google.com ([209.85.215.193]:34428 "EHLO
        mail-pg1-f193.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725861AbfKIHFm (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 9 Nov 2019 02:05:42 -0500
Received: by mail-pg1-f193.google.com with SMTP id c9so966711pgc.1;
        Fri, 08 Nov 2019 23:05:41 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=ZCWySZwIFzo2R68xigCV0RDhtUpT4rtgzjsd95CcpwQ=;
        b=eNKAefhxCaa3zY6JByKGRa8WBVBBnoI0ZkPv9LLZz9qO3eYRoWbg5y6KdfqF9g+GLn
         9RGGyjCbTguezobMDVYXOKVD0JI8ABdKhSH1J1G0dTt6ULRGAWs+cRBLimdYjjhcAQun
         P+0tpsXw5sbWtnQgEb41Owm+8ehVY2p+KDcK7jpepDmNlfxoW2k+XPJfWdDtbtGMQIon
         fB9iiJMcHa/V97mEbISMdqcCIfokDoXrGd1FFlXKlriKrZeBgiBEigv4pGzPrk1Nt/4c
         g/IRf6I50Pf0yt/7jQ8anvaaQTaj3ZkCkyPnh6aY7r/Ugqq0Lb0X0B+6g9Tanrjbaq/5
         c1Dg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=ZCWySZwIFzo2R68xigCV0RDhtUpT4rtgzjsd95CcpwQ=;
        b=CC0KAcYTGhhEfZi3CSYcOonrC+F9ubmRk5sfrAjdBIDLsHsmF/zswp1v6AeJZug8V2
         YUk1QK2YBbETor2PzVqoJRKmtoNu0XuGdnXIsRQFSoLf/RixuH0eel+M0AkdM+FvKLfO
         F5oo9mqAEK6aTWRoHI8yXxsFf6jSLJ8LZT+EF01nbFF0HeLy8wPcRq80DH6QGPM8wJoY
         CB09Q7kaWknNDrhhuiy44Ow2iXobC1UErO7OItGemPzdrTyFCyI1bssMB3aWB8feaF/+
         tpUsOx/w3tB0pjYnCyjMKMSR9kHredpdwAlmMLdtks+JdePAhg1/QuJ10dYeb/8xFSEe
         /Yzg==
X-Gm-Message-State: APjAAAWEP0Esf6uorwIj6ukoqNQqK8WdgqM1ymzixIprSkLZlkFonRAv
        y9HpHFVjjL3M2kpWyiMsVc/9sJ/N
X-Google-Smtp-Source: 
 APXvYqzrHyFC3iNi9gdl0/Mi61B9vgmW5ATsn68KqWw+xYueR5oDvgvcOpJax3cgw4PCUgZt27Dxzg==
X-Received: by 2002:a63:1b41:: with SMTP id b1mr16833656pgm.335.1573283140988;
        Fri, 08 Nov 2019 23:05:40 -0800 (PST)
Received: from localhost.localdomain ([203.205.141.123])
        by smtp.googlemail.com with ESMTPSA id
 b200sm8337991pfb.86.2019.11.08.23.05.38
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-SHA bits=128/128);
        Fri, 08 Nov 2019 23:05:40 -0800 (PST)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Sean Christopherson <sean.j.christopherson@intel.com>,
 Vitaly Kuznetsov <vkuznets@redhat.com>, Wanpeng Li <wanpengli@tencent.com>,
 Jim Mattson <jmattson@google.com>, Joerg Roedel <joro@8bytes.org>
Subject: [PATCH 1/2] KVM: X86: Single target IPI fastpath
Date: Sat,  9 Nov 2019 15:05:34 +0800
Message-Id: <1573283135-5502-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

This patch tries to optimize x2apic physical destination mode, fixed delivery
mode single target IPI by delivering IPI to receiver immediately after sender
writes ICR vmexit to avoid various checks when possible.

Testing on Xeon Skylake server:

The virtual IPI latency from sender send to receiver receive reduces more than
330+ cpu cycles.

Running hackbench(reschedule ipi) in the guest, the avg handle time of MSR_WRITE
caused vmexit reduces more than 1000+ cpu cycles:

Before patch:

  VM-EXIT    Samples  Samples%     Time%    Min Time    Max Time   Avg time
MSR_WRITE    5417390    90.01%    16.31%      0.69us    159.60us    1.08us

After patch:

  VM-EXIT    Samples  Samples%     Time%    Min Time    Max Time   Avg time
MSR_WRITE    6726109    90.73%    62.18%      0.48us    191.27us    0.58us

Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kvm/vmx/vmx.c   | 39 +++++++++++++++++++++++++++++++++++++--
 include/linux/kvm_host.h |  1 +
 2 files changed, 38 insertions(+), 2 deletions(-)

```
