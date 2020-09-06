#### [RFC] KVM: X86: implement Passthrough IPI Message-Id: <0C23CC2D-B770-43D0-8215-20CE591F2E8F@bytedance.com>
##### From: =?utf-8?b?6YKT5qGl?= <dengqiao.joey@bytedance.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?b?6YKT5qGl?= <dengqiao.joey@bytedance.com>
X-Patchwork-Id: 11759063
Return-Path: <SRS0=oq56=CO=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 077A0618
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat,  5 Sep 2020 12:21:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C39C920760
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat,  5 Sep 2020 12:21:28 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=bytedance-com.20150623.gappssmtp.com
 header.i=@bytedance-com.20150623.gappssmtp.com header.b="Sv4yNZc/"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728512AbgIEMV0 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 5 Sep 2020 08:21:26 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:35246 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726597AbgIEMVZ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 5 Sep 2020 08:21:25 -0400
Received: from mail-pf1-x435.google.com (mail-pf1-x435.google.com
 [IPv6:2607:f8b0:4864:20::435])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 8AB13C061244
        for <kvm@vger.kernel.org>; Sat,  5 Sep 2020 05:21:25 -0700 (PDT)
Received: by mail-pf1-x435.google.com with SMTP id f18so6076415pfa.10
        for <kvm@vger.kernel.org>; Sat, 05 Sep 2020 05:21:25 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=bytedance-com.20150623.gappssmtp.com; s=20150623;
        h=from:content-transfer-encoding:mime-version:subject:message-id:date
         :cc:to;
        bh=/ZLLSZsTgvLK1QUAtG3yQNe/2YpKTjjM7dljXhB5JFs=;
        b=Sv4yNZc/ksEXG/NHmPo27SqTAgmPdaqVP4iDD9sgUkcNIXx1o9WVqrp1Bqk+Hhge5z
         bjQR/Nnlaz+t3pry8/GNcrCV+TkkoA88bGPaqN6VN1D5CEyKEcUIMKtg3gJp7cTCdW/o
         KXHbfSrhA998vYvAP7cj9f2Nm2Ka4459cdVuZC7odSZvcU/TIBAO+KEXLOHhOCchzRdU
         IMcVO2I77THmxvaRZ3YNoaw28gcZ/ei9pqza9KpwZK2mBE68/uhBJ3gSYvBj6X54oT/7
         ZeTRj5OnE3p6UiW/3P4VUrHNedwO3eLcsA6/jinH4K5d5m+WWf16tJgXrcgL3YCJoV4j
         jmsQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:content-transfer-encoding:mime-version
         :subject:message-id:date:cc:to;
        bh=/ZLLSZsTgvLK1QUAtG3yQNe/2YpKTjjM7dljXhB5JFs=;
        b=l2F+SfAPVn8fj3NMYxrB7PQ5LBci5Az/wWgvcyv99cB/UCT4aYidN1Pvs0p7NohYy4
         CU9ukAwFQ6pSY6xfbiSMe/0H07vHo32XUFO6rN4fTLJY+5nGytLiiPwmZ2kwVt3jKZn/
         kkD1EUv+X9Bc7zTjgm5hVxC3PvsRMf3SnrpkupPZOZK4gjatevM0L27DsHDRRgE9Qypq
         gJTvMfTxjtyvY09wqSrDjCU9L+hpGYeMrSZ6K4zISxnKyp/Q/A8b2H0etPazpYJsuj8R
         r2EA1rvQQfhZRA+yPQ3lfdsQZMeidebCHNg7d/hKfMO12M7WYsLqCsh7Cpk/zOmyZ6Uv
         DPKQ==
X-Gm-Message-State: AOAM5315ILzH4zzcD2xHz5PIG7ZtlWIMrsgkpiIA/kTt4FtSjQvtFMdY
        O1LmMVwJ2eQckjc8XjEWHN2OKAfJQqGSCw==
X-Google-Smtp-Source: 
 ABdhPJyRHqT3/MCF8sxMghKlStAvvQuhibaD8+VrcoMz5T9hdRrjfqRj5V9i932nXQ+jLvkaRwAVsA==
X-Received: by 2002:a62:5cc4:: with SMTP id
 q187mr12874234pfb.95.1599308480699;
        Sat, 05 Sep 2020 05:21:20 -0700 (PDT)
Received: from [10.255.229.65] ([103.136.220.72])
        by smtp.gmail.com with ESMTPSA id
 x4sm9722013pfm.86.2020.09.05.05.21.17
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Sat, 05 Sep 2020 05:21:20 -0700 (PDT)
From: =?utf-8?b?6YKT5qGl?= <dengqiao.joey@bytedance.com>
Mime-Version: 1.0 (Mac OS X Mail 13.4 \(3608.80.23.2.2\))
Subject: [RFC] KVM: X86: implement Passthrough IPI 
Message-Id: <0C23CC2D-B770-43D0-8215-20CE591F2E8F@bytedance.com>
Date: Sat, 5 Sep 2020 20:21:15 +0800
Cc: pbonzini@redhat.com, rkrcmar@redhat.com, yang.zhang.wz@gmail.com,
        zhouyibo@bytedance.com, zhanghaozhong@bytedance.com
To: kvm@vger.kernel.org
X-Mailer: Apple Mail (2.3608.80.23.2.2)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch paravirtualize the IPI sending process in guest by exposing
posted interrupt capability to guest directly . Since there is no VM Exit 
and VM Entry when sending IPI, the overhead is therefore reduced.

The basic idea is that:
Exposing the PI_DESC  and msr.icr to guest. When sending a IPI, set 
the PIR of destination VCPU’s PI_DESC from guest directly and write
the ICR with notification vector and destination PCPU which are got 
from hypervisor. 

This mechanism only handle the normal IPI. For SIPI/NMI/INIT, still 
goes to legacy way but which write a new msr instead msr.icr.

The cost is reduced from 7k cycles to 2k cycles, which is 1500 cycles
on the host.

However it may increase the risk in the system since the guest could
decide to send IPI to any processor.

This patch is based on Linux-5.0 and we can rebase it on latest tree if the idea
is accepted. We will introduce this idea at KVM Forum 2020.

Signed-off-by: dengqiao.joey <dengqiao.joey@bytedance.com>
Signed-off-by: Yang Zhang <yang.zhang.wz@gmail.com>
---
arch/x86/include/asm/kvm_host.h      |  28 ++++-
arch/x86/include/asm/kvm_para.h      |   6 ++
arch/x86/include/asm/vmx.h           |   1 +
arch/x86/include/uapi/asm/kvm_para.h |  25 +++++
arch/x86/kernel/apic/apic.c          |   1 +
arch/x86/kernel/kvm.c                | 199 ++++++++++++++++++++++++++++++++++-
arch/x86/kvm/cpuid.c                 |  15 ++-
arch/x86/kvm/lapic.c                 |  12 +++
arch/x86/kvm/lapic.h                 |   9 ++
arch/x86/kvm/svm.c                   |   6 ++
arch/x86/kvm/vmx/vmx.c               | 132 ++++++++++++++++++++---
arch/x86/kvm/vmx/vmx.h               |   8 +-
arch/x86/kvm/x86.c                   |  19 ++++
include/uapi/linux/kvm.h             |   1 +
14 files changed, 434 insertions(+), 28 deletions(-)

--
2.11.0

```
