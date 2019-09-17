

#### [PATCH 0/3] KVM: x86: hyper-v: make L2 Hyper-V 2019 on KVM guests see
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
From patchwork Mon Sep 16 16:22:55 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11147563
Return-Path: <SRS0=87xZ=XL=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E2AC51745
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 16 Sep 2019 16:23:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id CA74E2184D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 16 Sep 2019 16:23:05 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729670AbfIPQXE (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 16 Sep 2019 12:23:04 -0400
Received: from mx1.redhat.com ([209.132.183.28]:39968 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729110AbfIPQXD (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 16 Sep 2019 12:23:03 -0400
Received: from mail-wr1-f71.google.com (mail-wr1-f71.google.com
 [209.85.221.71])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-GCM-SHA256 (128/128 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id CD061C054907
        for <kvm@vger.kernel.org>; Mon, 16 Sep 2019 16:23:02 +0000 (UTC)
Received: by mail-wr1-f71.google.com with SMTP id o16so117532wru.10
        for <kvm@vger.kernel.org>; Mon, 16 Sep 2019 09:23:02 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=FDgjsWSDn6xBrhx6U+9m9Eu+qyYKBG2MdOtlO9XcnZA=;
        b=FLOspzaHvSOQa+gMkpzisxSWdG+ohzaru9T05QyF6QEjG3ui7fQR/ku9M1R0wkIDzO
         g0mIt7NpnfdpiKXHldS4AIwLzoOyUyXrjvPHvG34EhJeQoYzoj69SF455m2O3QGU763h
         nbIVZinIQvcjyGCheTrbg7blA1ZeREJYdz7ovyk93qs0+ilykpXXWWIqm1I1kAqBU/zY
         c6dSfRCQdr+bYdJuvHsAh/oSDFOzfxmArOvNRb3D1hilhKA5jUS2rAaYNqG4jTOYFrs+
         wl+FlYQuynAMhv03C+FJUrZxGHrPpav7g+o8vy6gY1ag/RxEzx2bBMHUzb01Y6PqzskK
         005g==
X-Gm-Message-State: APjAAAWIaggFb0J0MVpjjcNtVOsb2x1thZzpUW2vlaZ+mchqjmT04VQX
        b2nlcDE+zo6ggpB9q6L/SJRM6n/BGdUM/589Q96ObElqLv481tmAiIGbMEBo162VAaEGEH4djOW
        BWKlsHMdNdFo5
X-Received: by 2002:a05:600c:295d:: with SMTP id
 n29mr42845wmd.36.1568650981046;
        Mon, 16 Sep 2019 09:23:01 -0700 (PDT)
X-Google-Smtp-Source: 
 APXvYqxHalXeJGi+RCuzUK9rmpW00UqDDt5f6sreleDyRFkD/UPh7GhVb0E++elsWy8IafgPDqQgOA==
X-Received: by 2002:a05:600c:295d:: with SMTP id
 n29mr42826wmd.36.1568650980794;
        Mon, 16 Sep 2019 09:23:00 -0700 (PDT)
Received: from vitty.brq.redhat.com (nat-pool-brq-t.redhat.com.
 [213.175.37.10])
        by smtp.gmail.com with ESMTPSA id
 q10sm78370575wrd.39.2019.09.16.09.22.59
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 16 Sep 2019 09:22:59 -0700 (PDT)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, linux-hyperv@vger.kernel.org,
 x86@kernel.org, Paolo Bonzini <pbonzini@redhat.com>, =?utf-8?b?UmFkaW0gS3I=?=
	=?utf-8?b?xI1tw6HFmQ==?= <rkrcmar@redhat.com>,
 Sean Christopherson <sean.j.christopherson@intel.com>,
 Jim Mattson <jmattson@google.com>, Thomas Gleixner <tglx@linutronix.de>,
 Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
 "H. Peter Anvin" <hpa@zytor.com>,
 "Peter Zijlstra (Intel)" <peterz@infradead.org>,
 Michael Kelley <mikelley@microsoft.com>, Roman Kagan <rkagan@virtuozzo.com>
Subject: [PATCH 0/3] KVM: x86: hyper-v: make L2 Hyper-V 2019 on KVM guests see
 MD_CLEAR
Date: Mon, 16 Sep 2019 18:22:55 +0200
Message-Id: <20190916162258.6528-1-vkuznets@redhat.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

[The series is KVM specific but the first patch of the series likely requires
 someone else's ACK. hyperv-tlfs.h gets a small addition too.]

It was discovered that L2 guests on Hyper-V 2019 on KVM don't see MD_CLEAR
bit (and thus think they're MDS vulnerable) even when it is present on the
host. Turns out, Hyper-V is filtering it out because it is not sure the
topology L0 is exposing is trustworthy and generally it is not. In some
specific cases (e.g. when SMT is unsupported or forcesully disabled) it is
and we can tell this to userspace hoping that it'll pass this info to L1.
See PATCH2 of the series for additional details.

The series can be tested with QEMU-4.1+ and 'hv-passthrough' CPU flag.

Vitaly Kuznetsov (3):
  cpu/SMT: create and export cpu_smt_possible()
  KVM: x86: hyper-v: set NoNonArchitecturalCoreSharing CPUID bit when
    SMT is impossible
  KVM: selftests: hyperv_cpuid: add check for
    NoNonArchitecturalCoreSharing bit

 arch/x86/include/asm/hyperv-tlfs.h            |  7 +++++
 arch/x86/kvm/hyperv.c                         |  4 ++-
 include/linux/cpu.h                           |  2 ++
 kernel/cpu.c                                  | 11 ++++++--
 .../selftests/kvm/x86_64/hyperv_cpuid.c       | 27 +++++++++++++++++++
 5 files changed, 48 insertions(+), 3 deletions(-)
```
