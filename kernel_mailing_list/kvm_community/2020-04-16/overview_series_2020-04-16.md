#### [PATCH 1/5] KVM: X86: Force ASYNC_PF_PER_VCPU to be power of two
##### From: Peter Xu <peterx@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11493293
Return-Path: <SRS0=ZIlC=6A=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F2DF2186E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Apr 2020 15:53:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D8D4922242
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Apr 2020 15:53:33 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="EmBTdn7I"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2896666AbgDPPxc (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 16 Apr 2020 11:53:32 -0400
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:59442 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S2896636AbgDPPx2 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 16 Apr 2020 11:53:28 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1587052407;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=EN/H+dURYVmdO4EXHtSzJA+fcODs32+NBiRjW8BRIZw=;
        b=EmBTdn7IVbQYFhdvaK/2Lv8m3DLb18LNhjgbq8X4DF+IhLK338wnQnEy+T9/iCqI3BJZ00
        5pG3CJfuxM7pqb3Fu4gOAL4ljT52pYB7UsVbfiTvVX34v/oWRyn1KhvmJJfgmJP5PCfMpC
        +kF8inTxpzxKZgBO7+CSszyMfqF/Srk=
Received: from mail-qt1-f200.google.com (mail-qt1-f200.google.com
 [209.85.160.200]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-62-uDWLXXCBP6yrAfyK2WVB9A-1; Thu, 16 Apr 2020 11:53:25 -0400
X-MC-Unique: uDWLXXCBP6yrAfyK2WVB9A-1
Received: by mail-qt1-f200.google.com with SMTP id g23so19038668qto.0
        for <kvm@vger.kernel.org>; Thu, 16 Apr 2020 08:53:25 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=EN/H+dURYVmdO4EXHtSzJA+fcODs32+NBiRjW8BRIZw=;
        b=lV3QqdZzawXUa0H02rk1tGaLnl1BSvEglJ0fU9afEaszGUmYeyewGZfFmM2Lj4gjAX
         ODi1LsOGnH7Zkxsy4p73pF5YYoJR70QSEBH9uFrPPWGLQiW0FSV6WBdMZ5RUmGhWnA5K
         crvfPadBV/0kzmumaflu1py9cypB6D+DFYFTwwLMcsIG7MArJqum0VYJDEEHCpi33Drs
         Ypprsd60dME/L2vl4u/z5Rjo/hCSguhbyonlTiJ2dfmRGC0HL0dHjMfgYkrc4Uy83DNm
         bMAaimXtYTjUCJOomgVpVwsqpGNtP7luGeMVU8sQDYfMnkJYYVv7dVV670PnAWbqmrRr
         hHyg==
X-Gm-Message-State: AGi0PuaBTjLCQXClo+el2QF549xwlWAyxFpbt0idB8yTlS2ccZl1RqXj
        VKZ6LhiFevrTxfsu2EPdw/+Jp//pJvTZ37vsj6z4JgOS4BaZ1Gy3/fMiotPsjcXhDqSwQ4yiAYZ
        9GT9NO3SydFai
X-Received: by 2002:a05:620a:5f1:: with SMTP id
 z17mr27807341qkg.21.1587052404965;
        Thu, 16 Apr 2020 08:53:24 -0700 (PDT)
X-Google-Smtp-Source: 
 APiQypJm5c/jIx1xNo1oON6lK6lrZ3qH3lLjFF0849VMtJ79LLl88AVumVItnDw+zIip+iHJEbsSeg==
X-Received: by 2002:a05:620a:5f1:: with SMTP id
 z17mr27807317qkg.21.1587052404735;
        Thu, 16 Apr 2020 08:53:24 -0700 (PDT)
Received: from xz-x1.redhat.com ([2607:9880:19c0:32::2])
        by smtp.gmail.com with ESMTPSA id
 j2sm11449124qtp.5.2020.04.16.08.53.23
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 16 Apr 2020 08:53:24 -0700 (PDT)
From: Peter Xu <peterx@redhat.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>, peterx@redhat.com
Subject: [PATCH 1/5] KVM: X86: Force ASYNC_PF_PER_VCPU to be power of two
Date: Thu, 16 Apr 2020 11:53:22 -0400
Message-Id: <20200416155322.266709-1-peterx@redhat.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Forcing the ASYNC_PF_PER_VCPU to be power of two is much easier to be
used rather than calling roundup_pow_of_two() from time to time.  Do
this by adding a BUILD_BUG_ON() inside the hash function.

Another point is that generally async pf does not allow concurrency
over ASYNC_PF_PER_VCPU after all (see kvm_setup_async_pf()), so it
does not make much sense either to have it not a power of two or some
of the entries will definitely be wasted.

Signed-off-by: Peter Xu <peterx@redhat.com>
---
 arch/x86/include/asm/kvm_host.h | 2 +-
 arch/x86/kvm/x86.c              | 8 +++++---
 2 files changed, 6 insertions(+), 4 deletions(-)

```
#### [PATCH] KVM: Documentation: Fix up cpuid page
##### From: Peter Xu <peterx@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11493325
Return-Path: <SRS0=ZIlC=6A=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7C42A81
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Apr 2020 15:59:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 63D3E217D8
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Apr 2020 15:59:27 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="LCyd/RWn"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2409097AbgDPP7Z (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 16 Apr 2020 11:59:25 -0400
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:35812 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S2897266AbgDPP7S (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 16 Apr 2020 11:59:18 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1587052757;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=JPDoCdd6Mz59gLMUCJpo/feFNXBVnhyS3Hu+/K7Ll1U=;
        b=LCyd/RWndwnvee4TIChxTMW99flEu5b1sPnTViC8n2VP4gKIx/fyB2t/0w7KqR/jE9jKUA
        ccoZW3AoHviIvmX+rMPpslHb3mDNXbFrmuKCpc8fylMO/vK+PzpveP216CzIHc2k4judb0
        g4Bv30LtbORuLaG6kIiuWOhRUPyaSeQ=
Received: from mail-qk1-f197.google.com (mail-qk1-f197.google.com
 [209.85.222.197]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-251-yWAsYfmxMnGf3UJc5L98BA-1; Thu, 16 Apr 2020 11:59:16 -0400
X-MC-Unique: yWAsYfmxMnGf3UJc5L98BA-1
Received: by mail-qk1-f197.google.com with SMTP id k13so2563285qkg.2
        for <kvm@vger.kernel.org>; Thu, 16 Apr 2020 08:59:16 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=JPDoCdd6Mz59gLMUCJpo/feFNXBVnhyS3Hu+/K7Ll1U=;
        b=Pq/eTLXVx77P0EPa0ta4W8vW6DKhVOAjeByvtWwjIPdH9zfwzIq9V4heEo0Wgw03R9
         dxQjatwyFCkU98ENt4/pJQQdjIT6qSfSTaOXZyWk5i3DDYEM9HTWVGYftyCFYdEaOcul
         AYkDTwdLJ0G3K/ZDKCr7+Q1fFWpSV99sbTDBPmP1Xw83mtkpxEsDQwsR0vy+g+Oc2I9H
         LC8oVxIegVTXwK65XvnMu4TV6j8KrAZ+cDgZAgAcMKEIjOzpRg+439T+dt416bMfcjo/
         gpZOjH69nbccP/YgMEBy45svNg7LZIkn8U24Nu/zahGBfmf4gnjcCmJgU+qzTtfqdyyf
         JRGA==
X-Gm-Message-State: AGi0PuYFXaWS/zif96uTmIoc0sizWE6ZXK8krMbCpjYfbTdWED2xPhZJ
        61AdyaBIRN5xFFCVE/VSkGrq9081o8NhQPiK+3/0dhosuuOcMX1aIks5eneT5zH4jVMF5PAfQlQ
        V2lSzuOn0KPjw
X-Received: by 2002:a0c:9e2f:: with SMTP id p47mr9997820qve.211.1587052755355;
        Thu, 16 Apr 2020 08:59:15 -0700 (PDT)
X-Google-Smtp-Source: 
 APiQypK+7QOzQNp7II51CKMz7W9yt//0mr5pcpNxTmnKALRjFnlpuLVkr+q9GhnPW+9sTClwrKTJRw==
X-Received: by 2002:a0c:9e2f:: with SMTP id p47mr9997807qve.211.1587052755176;
        Thu, 16 Apr 2020 08:59:15 -0700 (PDT)
Received: from xz-x1.redhat.com ([2607:9880:19c0:32::2])
        by smtp.gmail.com with ESMTPSA id
 c41sm12164124qta.96.2020.04.16.08.59.14
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 16 Apr 2020 08:59:14 -0700 (PDT)
From: Peter Xu <peterx@redhat.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>, peterx@redhat.com
Subject: [PATCH] KVM: Documentation: Fix up cpuid page
Date: Thu, 16 Apr 2020 11:59:13 -0400
Message-Id: <20200416155913.267562-1-peterx@redhat.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

0x4b564d00 and 0x4b564d01 belong to KVM_FEATURE_CLOCKSOURCE2.

Signed-off-by: Peter Xu <peterx@redhat.com>
---
 Documentation/virt/kvm/cpuid.rst | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] kvm: Handle reads of SandyBridge RAPL PMU MSRs rather than injecting #GP
##### From: Jon Cargille <jcargill@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jon Cargille <jcargill@google.com>
X-Patchwork-Id: 11493667
Return-Path: <SRS0=ZIlC=6A=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D8D371392
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Apr 2020 18:43:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C040F221E8
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Apr 2020 18:43:20 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="CFPLLGPX"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1733198AbgDPSnT (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 16 Apr 2020 14:43:19 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:48614 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728815AbgDPSnS (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 16 Apr 2020 14:43:18 -0400
Received: from mail-pf1-x449.google.com (mail-pf1-x449.google.com
 [IPv6:2607:f8b0:4864:20::449])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id C9D3FC061A0C
        for <kvm@vger.kernel.org>; Thu, 16 Apr 2020 11:43:16 -0700 (PDT)
Received: by mail-pf1-x449.google.com with SMTP id 20so3870292pfw.10
        for <kvm@vger.kernel.org>; Thu, 16 Apr 2020 11:43:16 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=mC/qr0j7HUgGt77fxIftKjS5qqz0qPQen02hUmh1Dh8=;
        b=CFPLLGPX4ctg78piDhgn3JbQBZ4NUQ5XOGuQiN/7vBRQR685triRRUALfmerg6W9xb
         j17+dKXQTA3N2V71skyu4zTFuVB/4OZSOXSyyskfOa5GZcQt4xpXMOQ5n5GE5MlQPCkQ
         1ZT3ut6wPZWf8D1dz63sAtr4+ZZSe1wtluo7mS5hgEVFNheTwFlMBnRW1WwxEpYbZ7ua
         XDKaJoHGbdm/AHYIKimMrLcSP6KvyLTT43OvDxyfMe60DGjgycAsTONaibnbQmuRB/82
         56FsiaOolzNptFQmMpl3CS8QBl6GBmGxjoAOyseLH1OgPbkueAOjEA0utBJPCWW3wD5F
         nYEw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=mC/qr0j7HUgGt77fxIftKjS5qqz0qPQen02hUmh1Dh8=;
        b=UgWlByuBwbj7qz7zElj+GPe+mi+GylCoYSqB+Nio+Y4PIpXs7MWFnj4fUHQVHFI6Sc
         EuOSjkhgKKxkjbvyjniDwXGfahbRAc0Kuy00FX5hpGDRCeE+QgLaDedzO3B/KcdPgDcL
         reHQG606DDtLO7ywfT5C85X3njy9RPFjxJWVjM212yiqsWzcYSUpcAFqWTzdGojVMKR+
         ifQceFkCn0qIDAiRXeieQIjhHAmus8WLq2kWEUT9Gvuyuy3qkNvQm0jomlK0aiDWZ/s6
         l42Alf2a+zMa0skrf83Lzo8FdQfi4RAErCAnNyeVJmfNKyT4V/bnKTHH3GfVd/An8fpL
         WHuQ==
X-Gm-Message-State: AGi0PuapXyMpQMIvN8KharD5Q33/HUakUihXS7s6xS7BEp0JvDPge8B0
        M9MGcRgo1w+yTqDL7AfMeazwBqrldT3n+A==
X-Google-Smtp-Source: 
 APiQypKhTjvNBou9iWL+ZmFqhZSk6QlvKSXplfrNIv5dwwZO5la9jHmS99O/mXPKRy/qIQIJHfkgNvE17bDG8Q==
X-Received: by 2002:a17:90a:65c8:: with SMTP id
 i8mr6679174pjs.156.1587062596155;
 Thu, 16 Apr 2020 11:43:16 -0700 (PDT)
Date: Thu, 16 Apr 2020 11:42:54 -0700
Message-Id: <20200416184254.248374-1-jcargill@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.26.1.301.g55bc3eb7cb9-goog
Subject: [PATCH] kvm: Handle reads of SandyBridge RAPL PMU MSRs rather than
 injecting #GP
From: Jon Cargille <jcargill@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        "H. Peter Anvin" <hpa@zytor.com>, x86@kernel.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: Venkatesh Srinivas <venkateshs@google.com>,
        Jon Cargille <jcargill@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Venkatesh Srinivas <venkateshs@google.com>

Linux 3.14 unconditionally reads the RAPL PMU MSRs on boot, without handling
General Protection Faults on reading those MSRs. Rather than injecting a #GP,
which prevents boot, handle the MSRs by returning 0 for their data. Zero was
checked to be safe by code review of the RAPL PMU driver and in discussion
with the original driver author (eranian@google.com).

Signed-off-by: Venkatesh Srinivas <venkateshs@google.com>
Signed-off-by: Jon Cargille <jcargill@google.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 arch/x86/kvm/x86.c | 11 +++++++++++
 1 file changed, 11 insertions(+)

```
#### [PATCH] KVM: No need to retry for hva_to_pfn_remapped()
##### From: Peter Xu <peterx@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11493327
Return-Path: <SRS0=ZIlC=6A=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4EBDF81
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Apr 2020 15:59:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 36C8321924
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Apr 2020 15:59:28 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="OeXEN1TV"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2406733AbgDPP71 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 16 Apr 2020 11:59:27 -0400
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:23679 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S2897213AbgDPP7N (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 16 Apr 2020 11:59:13 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1587052752;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=toq7sOeh3Oxre7YgXmyZ7yZ/oSgoiV55xEipFX9W/e8=;
        b=OeXEN1TVB2gqjwV47bMW3I7tbfhsDT5KORnwTppfZajqlXqlGU1RHhB5oZsDVoj0QaiUUT
        jkfcKARjNsfVspB13/kizegYJX8nIELEcZyJbE0xquJf2MaBka6x2OAcqEdLRv17pHK4WD
        RnomzhuyNHdqgjXrBXW+TcFMoB0e5/E=
Received: from mail-qk1-f200.google.com (mail-qk1-f200.google.com
 [209.85.222.200]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-36-y9Rb8g2tOSmEN8P-n19jDg-1; Thu, 16 Apr 2020 11:59:10 -0400
X-MC-Unique: y9Rb8g2tOSmEN8P-n19jDg-1
Received: by mail-qk1-f200.google.com with SMTP id r129so12931547qkd.19
        for <kvm@vger.kernel.org>; Thu, 16 Apr 2020 08:59:09 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=toq7sOeh3Oxre7YgXmyZ7yZ/oSgoiV55xEipFX9W/e8=;
        b=hzjHNA02gKy3Z3B65bOI6zT0vem6wjqo5EK0R3pzDjijvn5wLTBqpBSCgE/tTECR2a
         7OTJsmDgOeIZkxp7mLBUHK72MqDv5tpgvzlNXsnwbBx35iEWXQq6YlFNyGrHhnTLoUBC
         QwNZyxoW2MlVe4xwG7Ll+CXVViePLSVVi5yC2wOskySrCDH0dV+K+IzXdJcAVZ0F+77D
         0A2LcrErttyVcHD4zhvM8XJy5rpow8I1+g/Ui1Uy+Jva0XbDM/1OOgH800QT31WEEoou
         nGVKUpNHtkzifV3l2Yq+Dr5qRAUiszpmndddOa7PkJEY7Z/R9/+HkHmFbhYUjpLV3VjZ
         QNjA==
X-Gm-Message-State: AGi0PuYoUKeI65XneH4O5Fy8+S7Hr1rDf4h3OlCoHfMz37s+putRXan1
        1wId+dQ71KxpoNNNRIo+2ElCwT7rNLbTev3bLNzmivDQcw8+mnLzvcQ6Gynth3Klk3sVdyhDxWu
        FlbLdYfenSW/r
X-Received: by 2002:a37:6754:: with SMTP id
 b81mr11643863qkc.129.1587052748954;
        Thu, 16 Apr 2020 08:59:08 -0700 (PDT)
X-Google-Smtp-Source: 
 APiQypIp14On5d+FqJCkdeoD2L1ux2G7lAjoz3TzLNQDBoXBLDbiX6e/+Ywl75dqRmGHTVCB1srDGQ==
X-Received: by 2002:a37:6754:: with SMTP id
 b81mr11643846qkc.129.1587052748695;
        Thu, 16 Apr 2020 08:59:08 -0700 (PDT)
Received: from xz-x1.redhat.com ([2607:9880:19c0:32::2])
        by smtp.gmail.com with ESMTPSA id
 l7sm15398153qkb.47.2020.04.16.08.59.07
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 16 Apr 2020 08:59:08 -0700 (PDT)
From: Peter Xu <peterx@redhat.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>, peterx@redhat.com
Subject: [PATCH] KVM: No need to retry for hva_to_pfn_remapped()
Date: Thu, 16 Apr 2020 11:59:06 -0400
Message-Id: <20200416155906.267462-1-peterx@redhat.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

hva_to_pfn_remapped() calls fixup_user_fault(), which has already
handled the retry gracefully.  Even if "unlocked" is set to true, it
means that we've got a VM_FAULT_RETRY inside fixup_user_fault(),
however the page fault has already retried and we should have the pfn
set correctly.  No need to do that again.

Signed-off-by: Peter Xu <peterx@redhat.com>
---
 virt/kvm/kvm_main.c | 5 -----
 1 file changed, 5 deletions(-)

```
#### [PATCH] KVM: nVMX: Remove non-functional "support" for CR3 target values
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11492119
Return-Path: <SRS0=ZIlC=6A=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B59B992C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Apr 2020 00:07:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 96E1D2078B
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Apr 2020 00:07:56 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2391278AbgDPAHy (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 15 Apr 2020 20:07:54 -0400
Received: from mga07.intel.com ([134.134.136.100]:22230 "EHLO mga07.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729647AbgDPAHp (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 15 Apr 2020 20:07:45 -0400
IronPort-SDR: 
 PQfhgqXv5v/vASIwhZjiOITSEAQnm9/yFD81t+rylvvIW2R9cjlWfGnRV9/YK9arJOLhwVhjGp
 vEPrhGiMqbGA==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by orsmga105.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 15 Apr 2020 17:07:41 -0700
IronPort-SDR: 
 UxXcPxc0sQa68f6ATqUQ5Ng7RkwoejAfrLXEJFY8YRx3wxDutdu5sbWCzywxg1LT1y/WVbb+cv
 r9l1SGupJFwA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.72,388,1580803200";
   d="scan'208";a="363818564"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by fmsmga001.fm.intel.com with ESMTP; 15 Apr 2020 17:07:41 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: nVMX: Remove non-functional "support" for CR3 target
 values
Date: Wed, 15 Apr 2020 17:07:39 -0700
Message-Id: <20200416000739.9012-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Remove all references to cr3_target_value[0-3] and replace the fields
in vmcs12 with "dead_space" to preserve the vmcs12 layout.  KVM doesn't
support emulating CR3-target values, despite a variety of code that
implies otherwise, as KVM unconditionally reports '0' for the number of
supported CR3-target values.

This technically fixes a bug where KVM would incorrectly allow VMREAD
and VMWRITE to nonexistent fields, i.e. cr3_target_value[0-3].  Per
Intel's SDM, the number of supported CR3-target values reported in
VMX_MISC also enumerates the existence of the associated VMCS fields:

  If a future implementation supports more than 4 CR3-target values, they
  will be encoded consecutively following the 4 encodings given here.

Alternatively, the "bug" could be fixed by actually advertisting support
for 4 CR3-target values, but that'd likely just enable kvm-unit-tests
given that no one has complained about lack of support for going on ten
years, e.g. KVM, Xen and HyperV don't use CR3-target values.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---

Krish's patch to allow L1 to disable unrestricted guest got me poking
around the related code.  That led me into nested_vmx_exit_handled_cr()
and handle_cr().  handle_cr() does WARN_ON_ONCE(enable_unrestricted_guest)
in the MOV-to-CR3 path, as KVM should never enable CR3-exiting for L1.
But the CR3-target matching nested_vmx_exit_handled_cr() meant that it
would be possible to trigger the warn by enabling CR3-exiting in L1 with
a valid list of CR3-targets.  I got so far as to write a patch and a unit
test, and then I checked MSR_IA32_VMX_MISC under KVM...

AFAICT, properly emulating CR3-targets would be a trivial patch.  But, I
don't think there would be any meaningful users, e.g. Xen is the one
hypervisor (that I am aware of) that runs with EPT disabled for certain
use cases, and even Xen doesn't bother with CR3-targets.  On the other
hand, the odds of introducing a bug of one form or another seem high.

Amusing side note, Xen's only reference to vmcs.CR3_TARGET_VALUE* is in
its vmcs_dump_vcpu(), which explains why KVM's dump_vmcs() bothers to spit
out the unused CR3-target fields :-).

 Documentation/virt/kvm/nested-vmx.rst |  5 +----
 arch/x86/kvm/vmx/evmcs.c              |  8 --------
 arch/x86/kvm/vmx/nested.c             | 17 -----------------
 arch/x86/kvm/vmx/vmcs12.c             |  4 ----
 arch/x86/kvm/vmx/vmcs12.h             | 10 ++--------
 arch/x86/kvm/vmx/vmx.c                |  9 ---------
 6 files changed, 3 insertions(+), 50 deletions(-)

```
#### [PATCH] KVM: PPC: Book3S HV: Handle non-present PTEs in page fault functions
##### From: Paul Mackerras <paulus@ozlabs.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Paul Mackerras <paulus@ozlabs.org>
X-Patchwork-Id: 11492263
Return-Path: <SRS0=ZIlC=6A=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2383B92C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Apr 2020 05:03:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0AAF020771
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Apr 2020 05:03:48 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ozlabs.org header.i=@ozlabs.org
 header.b="CMjVIBuA"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2405166AbgDPFDm (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 16 Apr 2020 01:03:42 -0400
Received: from bilbo.ozlabs.org ([203.11.71.1]:59787 "EHLO ozlabs.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2404633AbgDPFDk (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 16 Apr 2020 01:03:40 -0400
Received: by ozlabs.org (Postfix, from userid 1003)
        id 492nDp3Rfhz9sSG; Thu, 16 Apr 2020 15:03:38 +1000 (AEST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=ozlabs.org; s=201707;
        t=1587013418; bh=ezMMwkByK2qZyRKxM4BFNkkLAWHC+jA69OSNgaQhgbc=;
        h=Date:From:To:Cc:Subject:From;
        b=CMjVIBuASwAcDOMMj7oJiM3jwgXLZge7hHE1uCcAlkF9v6v2mv20mbE8W5cKSaZV9
         ouc+wKbBOOZuAtIhol8gUN6iROYWWiNFtkAILfyEXCJclcYVJ26fyUQMeSz8/8bzjF
         HsrwEbMFAZTjuCI3urNFQTUaWIqBm0t9YZZTWP6LaN4/eAMrstp0pbEU7K9YhCjLez
         nnSAJRdiX5njMqBAvkSHmr/Df3u7eFKEjDwsb3T1AW41iVgiCn9STeyQCdDb1gXT03
         OxLpDiwb8mJPTxc6fMbZnmDuwaa96fKPA2DnLDq4uCINbQiIhP33idhnnwhaq+viwD
         y7KRNUKE4cFXQ==
Date: Thu, 16 Apr 2020 15:03:35 +1000
From: Paul Mackerras <paulus@ozlabs.org>
To: kvm@vger.kernel.org, kvm-ppc@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, linuxppc-dev@lists.ozlabs.org,
        groug@kaod.org, clg@kaod.org,
        David Gibson <david@gibson.dropbear.id.au>
Subject: [PATCH] KVM: PPC: Book3S HV: Handle non-present PTEs in page fault
 functions
Message-ID: <20200416050335.GB10545@blackberry>
MIME-Version: 1.0
Content-Disposition: inline
User-Agent: Mutt/1.5.24 (2015-08-30)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Since cd758a9b57ee "KVM: PPC: Book3S HV: Use __gfn_to_pfn_memslot in HPT
page fault handler", it's been possible in fairly rare circumstances to
load a non-present PTE in kvmppc_book3s_hv_page_fault() when running a
guest on a POWER8 host.

Because that case wasn't checked for, we could misinterpret the non-present
PTE as being a cache-inhibited PTE.  That could mismatch with the
corresponding hash PTE, which would cause the function to fail with -EFAULT
a little further down.  That would propagate up to the KVM_RUN ioctl()
generally causing the KVM userspace (usually qemu) to fall over.

This addresses the problem by catching that case and returning to the guest
instead, letting it fault again, and retrying the whole page fault from
the beginning.

For completeness, this fixes the radix page fault handler in the same
way.  For radix this didn't cause any obvious misbehaviour, because we
ended up putting the non-present PTE into the guest's partition-scoped
page tables, leading immediately to another hypervisor data/instruction
storage interrupt, which would go through the page fault path again
and fix things up.

Fixes: cd758a9b57ee "KVM: PPC: Book3S HV: Use __gfn_to_pfn_memslot in HPT page fault handler"
Bugzilla: https://bugzilla.redhat.com/show_bug.cgi?id=1820402
Reported-by: David Gibson <david@gibson.dropbear.id.au>
Signed-off-by: Paul Mackerras <paulus@ozlabs.org>
Tested-by: Cédric Le Goater <clg@kaod.org>
Reviewed-by: Cédric Le Goater <clg@kaod.org>
---
This is a reworked version of the patch David Gibson sent recently,
with the fix applied to the radix case as well. The commit message
is mostly stolen from David's patch.

 arch/powerpc/kvm/book3s_64_mmu_hv.c    | 9 +++++----
 arch/powerpc/kvm/book3s_64_mmu_radix.c | 9 +++++----
 2 files changed, 10 insertions(+), 8 deletions(-)

```
#### [PATCH] KVM: Remove async parameter for hva_to_pfn_remapped()
##### From: Peter Xu <peterx@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11493323
Return-Path: <SRS0=ZIlC=6A=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4AB631392
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Apr 2020 15:59:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3428F22244
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Apr 2020 15:59:21 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="hI/gKD13"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2633078AbgDPP7T (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 16 Apr 2020 11:59:19 -0400
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:36678 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S2896590AbgDPP7J (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 16 Apr 2020 11:59:09 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1587052747;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=NILe1+M954ythiYZr78tAgB+rwYmZAWGI0SxXGC7+zU=;
        b=hI/gKD13+e9aColeHbuN+YIDrKo3gqodSJLC7SCsMqhpqPHilrtR4GiCrmbkDLu0KzuwQS
        umoAu0/vK56i0OZhCNPjHMWwtnFMIy4nNluvDBSxUtrL/383YZsXTLw/0gDJUhOwchbDem
        5sd0hA/F9WGONg7QvVZmKUkxEaWRqYo=
Received: from mail-qt1-f200.google.com (mail-qt1-f200.google.com
 [209.85.160.200]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-105-gX9jz6bYPcmIrb7U7qG1Ng-1; Thu, 16 Apr 2020 11:59:06 -0400
X-MC-Unique: gX9jz6bYPcmIrb7U7qG1Ng-1
Received: by mail-qt1-f200.google.com with SMTP id y31so7657662qta.16
        for <kvm@vger.kernel.org>; Thu, 16 Apr 2020 08:59:06 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=NILe1+M954ythiYZr78tAgB+rwYmZAWGI0SxXGC7+zU=;
        b=O6yhNdr1HL6Ad82wstn6/h/sNAKKCm3hTSm64yenUq1yVx4BqVd63WtsVooujrtvsB
         pu95KtipGS++7Q/4c+2xzvT8ZqH3RgUFHwLG/HNk0qs8EUYZUgNUQ7yJ8tKXgenO8TZ6
         P96Iy4qFneYBM5ioT+kLDa3W07CaKjCodPoIKxeKJgoAYFX45mPJ+UO7dxy+W7Wd1Fuy
         Bi0BqasMxzLw8kLKuKoF7FpfT/LbbcDhNzK1ZGfTrKY4LIzHsoLy9gWlMkYe/YEp/BKW
         Cxn5QbFtExj1oUuj/dpP4FyaO9W6eEo2xV5rpPuqxfEJyzIpw6xYwK42Hvu1P6Lq0hRN
         bmVA==
X-Gm-Message-State: AGi0PuYLng91IzotHll2+oiA5pCIya1/OUB0r+dOHMyuwhkcJjEUfB2E
        SOVDOrs+QWylpc98Uve/b2fXQ+E3ZMJSBfLzABmVYf5+PN3vCVrWiFc0IlgNSyjfwmEo7jr5RWL
        SEP2Ir1SvlJqG
X-Received: by 2002:a37:9544:: with SMTP id x65mr29717672qkd.48.1587052745489;
        Thu, 16 Apr 2020 08:59:05 -0700 (PDT)
X-Google-Smtp-Source: 
 APiQypJJ5SMoPDB1NgVBB/ZGS0WTscaGWTPbULSlx+L7FEDpFfiyYIzZe1vfM7SfBLlF0N9gw8P3gw==
X-Received: by 2002:a37:9544:: with SMTP id x65mr29717649qkd.48.1587052745214;
        Thu, 16 Apr 2020 08:59:05 -0700 (PDT)
Received: from xz-x1.redhat.com ([2607:9880:19c0:32::2])
        by smtp.gmail.com with ESMTPSA id
 v27sm6636870qtb.35.2020.04.16.08.59.03
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 16 Apr 2020 08:59:04 -0700 (PDT)
From: Peter Xu <peterx@redhat.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>, peterx@redhat.com
Subject: [PATCH] KVM: Remove async parameter for hva_to_pfn_remapped()
Date: Thu, 16 Apr 2020 11:59:03 -0400
Message-Id: <20200416155903.267414-1-peterx@redhat.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We always do synchronous fault in for those pages.

Signed-off-by: Peter Xu <peterx@redhat.com>
---

Or, does it make sense to allow async pf for PFNMAP|IO too?  I just
didn't figure out why not...
---
 virt/kvm/kvm_main.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH] KVM: Remove CREATE_IRQCHIP/SET_PIT2 raceFrom: Jon Cargille <jcargill@google.com>
##### From: Jon Cargille <jcargill@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jon Cargille <jcargill@google.com>
X-Patchwork-Id: 11493689
Return-Path: <SRS0=ZIlC=6A=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 010E081
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Apr 2020 19:12:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DC9A620786
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Apr 2020 19:12:31 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="do1iupJT"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730199AbgDPTMW (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 16 Apr 2020 15:12:22 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:53112 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727926AbgDPTMS (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 16 Apr 2020 15:12:18 -0400
Received: from mail-qt1-x84a.google.com (mail-qt1-x84a.google.com
 [IPv6:2607:f8b0:4864:20::84a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id CAD74C061A0C
        for <kvm@vger.kernel.org>; Thu, 16 Apr 2020 12:12:18 -0700 (PDT)
Received: by mail-qt1-x84a.google.com with SMTP id g55so20184328qtk.14
        for <kvm@vger.kernel.org>; Thu, 16 Apr 2020 12:12:18 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=akfUqnFcHbR4ypUK0waDS6vSsDmt70xk58DkBEhixQg=;
        b=do1iupJTFmsxaH3hlHdr4r/sVdtkohH+o2zKk5OnjDlNtdtq3IgMnNQa8oe9bE9tZk
         T7mxam+uL1lKWTS8eclSdD7tNmxvzRuDzLNZvuzmBY2aoNC1RfGeZKXD/EBeuzFzfWIr
         WJZHHWVuGV/SQF4RzrES/bJXAM4lLssSGx4Ijqqa7pY431PrVSte603yTzBazwmOOy53
         Dg9NPpvOUyl+7bSOHXZSLJKN9qN0YpEVLIZrVCuHHAipr+4tm5tVqHqFuiUbpTofL1cE
         +92D4EfDi2Egn+PC7ABAi7lUqTDDkEKceV3jg+kju8Mw+tV08GZ10XV89Fi9XWU7/tHb
         prQA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=akfUqnFcHbR4ypUK0waDS6vSsDmt70xk58DkBEhixQg=;
        b=Jz1TZ8yf/kCRlxDDsAFQe4PaaWWTCiS87U+NeIMk2T/l/bI1I5zahrtxMtOkouOQ26
         WcQbi4+nrhla+NkoXEZDrIY8NESN5v0Kv4LPAjrspkvb3UzyX7xB9GVg+b02pjo1d3+A
         lgXnTF3dAD6Ds9Ond6Mhp7yWNomiQVW+i8X4esjIx5wVbBJuKKnGllMmeqsm7BUan4YT
         wC/iOF8PI5n38yIngTEUwMUtAgNQj5r5yTi/IkgRBgscaAbNCUTkL6LxumVgEQqf832q
         2lwkimSKkDtGtoJsJ4Q5j8elFH8xYeSZkZaUGRrnr62YuEWztJHp4mIDt+h5q8OanrLD
         nsNQ==
X-Gm-Message-State: AGi0Pub3aJ0JEtaBsbAU9TGDpGx33FWogaDfG7tF3k0AF31+JTp97qZB
        te6Y4QciXzZCVFlPwzY9J8HiFrz9xqMTVQ==
X-Google-Smtp-Source: 
 APiQypLttKT3SWY83gbGGp6Kj1Y4LsKg53UpN8WjCnn4NxYVGBQ/lOGRM1gn8dXlfLwC/TTmCRtAPeP7DJHcuw==
X-Received: by 2002:ad4:5546:: with SMTP id v6mr12063970qvy.11.1587064337976;
 Thu, 16 Apr 2020 12:12:17 -0700 (PDT)
Date: Thu, 16 Apr 2020 12:11:52 -0700
Message-Id: <20200416191152.259434-1-jcargill@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.26.1.301.g55bc3eb7cb9-goog
Subject: [PATCH] KVM: Remove CREATE_IRQCHIP/SET_PIT2 race
From: Jon Cargille <jcargill@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        "H. Peter Anvin" <hpa@zytor.com>, x86@kernel.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: Steve Rutherford <srutherford@google.com>,
        Jon Cargille <jcargill@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Steve Rutherford <srutherford@google.com>

Fixes a NULL pointer dereference, caused by the PIT firing an interrupt
before the interrupt table has been initialized.

SET_PIT2 can race with the creation of the IRQchip. In particular,
if SET_PIT2 is called with a low PIT timer period (after the creation of
the IOAPIC, but before the instantiation of the irq routes), the PIT can
fire an interrupt at an uninitialized table.

Signed-off-by: Steve Rutherford <srutherford@google.com>
Signed-off-by: Jon Cargille <jcargill@google.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 arch/x86/kvm/x86.c | 10 ++++++++--
 1 file changed, 8 insertions(+), 2 deletions(-)

```
#### [kvm-unit-tests PATCH] nVMX: Add testcase to cover VMWRITE to nonexistent CR3-target values
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11493477
Return-Path: <SRS0=ZIlC=6A=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1FA036CA
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Apr 2020 16:28:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 11D9F2223E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Apr 2020 16:28:22 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731680AbgDPQ2U (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 16 Apr 2020 12:28:20 -0400
Received: from mga06.intel.com ([134.134.136.31]:13693 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729269AbgDPQ2T (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 16 Apr 2020 12:28:19 -0400
IronPort-SDR: 
 RaiMmUB6D5BwhO9aXefhzyOYjhsV6zkZDQjG1Ewc/L7PjnuDOuuyO3ITfLCq+qjTiOqrsCqOk/
 JLKEvM3LIZuQ==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga004.jf.intel.com ([10.7.209.38])
  by orsmga104.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 16 Apr 2020 09:28:18 -0700
IronPort-SDR: 
 FKixKdxKXu495bulbZxjUOLEUSkbNuXKvvVfa9hed7D0h2appRHAB8ZOMq32vF45sNwUXRMyFj
 tLLCUdRnuNUA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.72,391,1580803200";
   d="scan'208";a="400727226"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by orsmga004.jf.intel.com with ESMTP; 16 Apr 2020 09:28:18 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org,
        Sean Christopherson <sean.j.christopherson@intel.com>
Subject: [kvm-unit-tests PATCH] nVMX: Add testcase to cover VMWRITE to
 nonexistent CR3-target values
Date: Thu, 16 Apr 2020 09:28:14 -0700
Message-Id: <20200416162814.32065-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Enhance test_cr3_targets() to verify that attempting to write CR3-target
value fields beyond the reported number of supported targets fails.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 x86/vmx_tests.c | 4 ++++
 1 file changed, 4 insertions(+)

```
#### [RFC PATCH 1/3] kvm: x86: Rename KVM_DEBUGREG_RELOAD to KVM_DEBUGREG_NEED_RELOAD
##### From: Xiaoyao Li <xiaoyao.li@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xiaoyao Li <xiaoyao.li@intel.com>
X-Patchwork-Id: 11492835
Return-Path: <SRS0=ZIlC=6A=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EC4BC112C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Apr 2020 11:45:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DE07A21D7F
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Apr 2020 11:45:57 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2505206AbgDPLpy (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 16 Apr 2020 07:45:54 -0400
Received: from mga01.intel.com ([192.55.52.88]:46619 "EHLO mga01.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2504914AbgDPKdi (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 16 Apr 2020 06:33:38 -0400
IronPort-SDR: 
 CBFc0+RD/rxjCamx/CRPEvlO6bTrJVUX4OIwq8jHiIvt3Rvp6XRL3YygupM8qsk+0JJ4zR+pQB
 qT1GHhZyJ7JA==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga004.fm.intel.com ([10.253.24.48])
  by fmsmga101.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 16 Apr 2020 03:33:27 -0700
IronPort-SDR: 
 GM7QgTRxLZxNtY5oDGeuldEujPWqCiRNQBU2Z1aqO/DnlR2z2n87sj4SRohvLHQLhs+KMo2hax
 VASDiE9UKVsA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.72,390,1580803200";
   d="scan'208";a="277947896"
Received: from lxy-clx-4s.sh.intel.com ([10.239.43.132])
  by fmsmga004.fm.intel.com with ESMTP; 16 Apr 2020 03:33:26 -0700
From: Xiaoyao Li <xiaoyao.li@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        kvm@vger.kernel.org
Cc: Nadav Amit <namit@cs.technion.ac.il>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        linux-kernel@vger.kernel.org, Xiaoyao Li <xiaoyao.li@intel.com>
Subject: [RFC PATCH 1/3] kvm: x86: Rename KVM_DEBUGREG_RELOAD to
 KVM_DEBUGREG_NEED_RELOAD
Date: Thu, 16 Apr 2020 18:15:07 +0800
Message-Id: <20200416101509.73526-2-xiaoyao.li@intel.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20200416101509.73526-1-xiaoyao.li@intel.com>
References: <20200416101509.73526-1-xiaoyao.li@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

To make it more clear that the flag means DRn (except DR7) need to be
reloaded before vm entry.

Signed-off-by: Xiaoyao Li <xiaoyao.li@intel.com>
---
 arch/x86/include/asm/kvm_host.h | 2 +-
 arch/x86/kvm/x86.c              | 6 +++---
 2 files changed, 4 insertions(+), 4 deletions(-)

```
#### [PATCH] KVM: X86: Force ASYNC_PF_PER_VCPU to be power of two
##### From: Peter Xu <peterx@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11493321
Return-Path: <SRS0=ZIlC=6A=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E8F4E1392
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Apr 2020 15:59:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CD4A822244
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Apr 2020 15:59:17 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Zlr45w+C"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2897248AbgDPP7P (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 16 Apr 2020 11:59:15 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:44261 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S2896263AbgDPP7G (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 16 Apr 2020 11:59:06 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1587052744;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=EN/H+dURYVmdO4EXHtSzJA+fcODs32+NBiRjW8BRIZw=;
        b=Zlr45w+CuG4go0NRRvN4Vf9xqmZh55ctTuS0egCxmfVFU8k7iYt+is5QOyf6ls0QDsSMSN
        oncKAAMPrBCWjZf/KUCkyq22Huemi/wmQxzNJw/TSq34K/G3GNBIAPu8S0ETN5ZAzwgDOe
        bBYrdypxtGOyN31VLZINn/rJwx0YAuQ=
Received: from mail-qt1-f200.google.com (mail-qt1-f200.google.com
 [209.85.160.200]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-500-mUZs85VYM9a1XAM7kBrTKQ-1; Thu, 16 Apr 2020 11:59:02 -0400
X-MC-Unique: mUZs85VYM9a1XAM7kBrTKQ-1
Received: by mail-qt1-f200.google.com with SMTP id x56so19556925qtc.10
        for <kvm@vger.kernel.org>; Thu, 16 Apr 2020 08:59:02 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=EN/H+dURYVmdO4EXHtSzJA+fcODs32+NBiRjW8BRIZw=;
        b=SVg4qT5KW8EWZmUn488J0tRs3jXypJsfFKxfKEpEcCXhb5bDkLGyGjk3u63134xTH8
         GEAsg9rKgEnyFezyPWa81YVHHNOWE+8tqCamERnb+/g3QDYm90/W1w6TXYxxRq9aFVFv
         dKEPIGQd9YnZ1ybBvtjfC4/43VCnewbyCx8kz3+AnUIdh5vQB6jn+2wVznjPADnjChK1
         OBWKHi/qDfZugsw9QZyot3UA1DLuoJ0hawxPBX2+HkDjavUi9/4UQ1U/3P39InV4da4d
         hRO/ada2/H3P+dhqmJH6upy6eIAsQlzOrTg9tVpBfXPlf23v2a5xLZ0ZvvdtFvrpMNNS
         fwzg==
X-Gm-Message-State: AGi0PuZ9/xhO6LxvyKP3EJxfG6oSuIzYDAlhkoUGp4m0UFAr1PPsFybN
        UomCwrOP4PPdSKnMOhlpBRsm35QLcHOb6c6NVEQ4a8cZ0xcXhr3SjwBXYs+NWkhHmYU2ZyP0bzy
        56FkM0mcqbAak
X-Received: by 2002:ad4:54c3:: with SMTP id j3mr10822714qvx.241.1587052741879;
        Thu, 16 Apr 2020 08:59:01 -0700 (PDT)
X-Google-Smtp-Source: 
 APiQypLDBUNGHmlOG11XrkWQ/pjAZwIDGioryxCRlW/eA5eQmopOir38iknIpUxnuvqlVuyvruM8dw==
X-Received: by 2002:ad4:54c3:: with SMTP id j3mr10822694qvx.241.1587052741558;
        Thu, 16 Apr 2020 08:59:01 -0700 (PDT)
Received: from xz-x1.redhat.com ([2607:9880:19c0:32::2])
        by smtp.gmail.com with ESMTPSA id
 h13sm14752239qkj.21.2020.04.16.08.58.59
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 16 Apr 2020 08:59:00 -0700 (PDT)
From: Peter Xu <peterx@redhat.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>, peterx@redhat.com
Subject: [PATCH] KVM: X86: Force ASYNC_PF_PER_VCPU to be power of two
Date: Thu, 16 Apr 2020 11:58:59 -0400
Message-Id: <20200416155859.267366-1-peterx@redhat.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Forcing the ASYNC_PF_PER_VCPU to be power of two is much easier to be
used rather than calling roundup_pow_of_two() from time to time.  Do
this by adding a BUILD_BUG_ON() inside the hash function.

Another point is that generally async pf does not allow concurrency
over ASYNC_PF_PER_VCPU after all (see kvm_setup_async_pf()), so it
does not make much sense either to have it not a power of two or some
of the entries will definitely be wasted.

Signed-off-by: Peter Xu <peterx@redhat.com>
---
 arch/x86/include/asm/kvm_host.h | 2 +-
 arch/x86/kvm/x86.c              | 8 +++++---
 2 files changed, 6 insertions(+), 4 deletions(-)

```
#### [PATCH] KVM: X86: Sanity check on gfn before removal
##### From: Peter Xu <peterx@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11493329
Return-Path: <SRS0=ZIlC=6A=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6C75F1392
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Apr 2020 15:59:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 53A2E21924
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Apr 2020 15:59:35 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="J6YNm5CZ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2410680AbgDPP73 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 16 Apr 2020 11:59:29 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:49111 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S2897252AbgDPP7Q (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 16 Apr 2020 11:59:16 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1587052755;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=fzOnR5A7GlmS9rHeBs6Acef4J3y9D9TufivnERunTyU=;
        b=J6YNm5CZZE4QvAiJhztq1EOGG85t2BoWfbKKRTJLoKXGdeIXfim4TEnHoUGwGTcAdm16X4
        AHIxf1jlAWES304Z3eETC/b+h8k32A1zE5JByssWXk151NsAX+4pTQNSsFsit0Y17n/G6P
        AnMDq4MvetXYau0rUOQ29rF5ZeaUZwc=
Received: from mail-qk1-f198.google.com (mail-qk1-f198.google.com
 [209.85.222.198]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-471-gMI0G1RdOGeuv90seyGMGA-1; Thu, 16 Apr 2020 11:59:12 -0400
X-MC-Unique: gMI0G1RdOGeuv90seyGMGA-1
Received: by mail-qk1-f198.google.com with SMTP id k13so2563124qkg.2
        for <kvm@vger.kernel.org>; Thu, 16 Apr 2020 08:59:12 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=fzOnR5A7GlmS9rHeBs6Acef4J3y9D9TufivnERunTyU=;
        b=mTfdvmNN3PLhrlqfrYI5Nxl0zdhvHswIRBCp3yYDqev3ty/yY6YZ9xAWFDBdbU0ihm
         L6jexn7Bo1TMJ3oqtaeXzq7eWEyF0nD2wLBlh9AK6XXJgbP9eMOd9unT0Ct4aTIOHHvw
         kzt/ygyjQZ1NH1GVS4rpMAmNvDIoZtdesjSamX5KPYHEQp1HdttnTO2of0Dc6yQXROe/
         NRY2p5lhRPOoFoIRfR6W+N5ipyCmPmYcWudJ5Q2SI520TiIne2g9H+w597nTBzk2W+M1
         3YhTI6jLyNwIUSN7RDp1WTI/KD79/alWF/4Sc02MtABaK1BVlQ449+DEKXhXbxupxZ7y
         EG7A==
X-Gm-Message-State: AGi0PubDKhD3BGr3FuTE+ZKQPQU5kqmsgi1ZO+7ucoLqfZi+DLix0IJy
        m3uAIysf50crtMEKjDHYqjjiKwe/nEC05z3rl9rS2Z1+dDlI4LrkziKkPka/LVGSSwd3FIDjVCD
        wAe4Y7vMv9vnH
X-Received: by 2002:a37:809:: with SMTP id 9mr17014804qki.93.1587052752008;
        Thu, 16 Apr 2020 08:59:12 -0700 (PDT)
X-Google-Smtp-Source: 
 APiQypJCVUrdFy7/i8pvfn8GY7IMxV4JE5dnih9EcFzFPzSJsgH6IoFoXLnlQV0a2ClVWLh0S21nfw==
X-Received: by 2002:a37:809:: with SMTP id 9mr17014792qki.93.1587052751792;
        Thu, 16 Apr 2020 08:59:11 -0700 (PDT)
Received: from xz-x1.redhat.com ([2607:9880:19c0:32::2])
        by smtp.gmail.com with ESMTPSA id
 d1sm15426699qto.66.2020.04.16.08.59.10
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 16 Apr 2020 08:59:11 -0700 (PDT)
From: Peter Xu <peterx@redhat.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>, peterx@redhat.com
Subject: [PATCH] KVM: X86: Sanity check on gfn before removal
Date: Thu, 16 Apr 2020 11:59:10 -0400
Message-Id: <20200416155910.267514-1-peterx@redhat.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The index returned by kvm_async_pf_gfn_slot() will be removed when an
async pf gfn is going to be removed.  However kvm_async_pf_gfn_slot()
is not reliable in that it can return the last key it loops over even
if the gfn is not found in the async gfn array.  It should never
happen, but it's still better to sanity check against that to make
sure no unexpected gfn will be removed.

Signed-off-by: Peter Xu <peterx@redhat.com>
---
 arch/x86/kvm/x86.c | 4 ++++
 1 file changed, 4 insertions(+)

```
#### [PATCH v2 1/8] tools/virtio: fix virtio_test.c indentation
##### From: =?utf-8?q?Eugenio_P=C3=A9rez?= <eperezma@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Eugenio_P=C3=A9rez?= <eperezma@redhat.com>
X-Patchwork-Id: 11492455
Return-Path: <SRS0=ZIlC=6A=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6F488112C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Apr 2020 07:58:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5731620784
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Apr 2020 07:58:52 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="KpIxz8Ur"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2441094AbgDPH6t (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 16 Apr 2020 03:58:49 -0400
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:54360 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S2440767AbgDPH5B (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 16 Apr 2020 03:57:01 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1587023820;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=e1k01JD5xORhS1YT1xVO0vHDHL2WrkMx7ODikVyTREQ=;
        b=KpIxz8Ur6wlKffHi1mxzcHWFyPBHQ4Zz100qbTAhWgxdfoIm7RCW6v4Ry2/qKlwGz/kqUF
        58FEjBhJHv8CTtOux1tO0XwZU/t9G1Uo0vCQvifrgh4VopAN6DXQjwJSQKVmBAF25L3Z2u
        kqwWFlJZIkw1qY6Z04Hal1tUURnKm/g=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-114-YBSDWHJlMbyoAM-xemqa1A-1; Thu, 16 Apr 2020 03:56:56 -0400
X-MC-Unique: YBSDWHJlMbyoAM-xemqa1A-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 58F71107ACC9;
        Thu, 16 Apr 2020 07:56:55 +0000 (UTC)
Received: from eperezma.remote.csb (ovpn-112-194.ams2.redhat.com
 [10.36.112.194])
        by smtp.corp.redhat.com (Postfix) with ESMTP id F0B7C7E7C0;
        Thu, 16 Apr 2020 07:56:52 +0000 (UTC)
From: =?utf-8?q?Eugenio_P=C3=A9rez?= <eperezma@redhat.com>
To: "Michael S. Tsirkin" <mst@redhat.com>
Cc: Stephen Rothwell <sfr@canb.auug.org.au>,
 "virtualization@lists.linux-foundation.org"
  <virtualization@lists.linux-foundation.org>,
 Christian Borntraeger <borntraeger@de.ibm.com>, =?utf-8?q?Eugenio_P=C3=A9re?=
	=?utf-8?q?z?= <eperezma@redhat.com>,
 Linux Next Mailing List <linux-next@vger.kernel.org>,
 kvm list <kvm@vger.kernel.org>, Cornelia Huck <cohuck@redhat.com>,
 Halil Pasic <pasic@linux.ibm.com>,
 "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>
Subject: [PATCH v2 1/8] tools/virtio: fix virtio_test.c indentation
Date: Thu, 16 Apr 2020 09:56:36 +0200
Message-Id: <20200416075643.27330-2-eperezma@redhat.com>
In-Reply-To: <20200416075643.27330-1-eperezma@redhat.com>
References: <20200416075643.27330-1-eperezma@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Just removing extra whitespace.

Signed-off-by: Eugenio Pérez <eperezma@redhat.com>
---
 tools/virtio/virtio_test.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v2] KVM: Optimize kvm_arch_vcpu_ioctl_run function
##### From: Tianjia Zhang <tianjia.zhang@linux.alibaba.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tianjia Zhang <tianjia.zhang@linux.alibaba.com>
X-Patchwork-Id: 11492265
Return-Path: <SRS0=ZIlC=6A=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D139214DD
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Apr 2020 05:11:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B3C072137B
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Apr 2020 05:11:14 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2405895AbgDPFLM (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 16 Apr 2020 01:11:12 -0400
Received: from out30-54.freemail.mail.aliyun.com ([115.124.30.54]:56110 "EHLO
        out30-54.freemail.mail.aliyun.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S2404971AbgDPFLJ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 16 Apr 2020 01:11:09 -0400
X-Alimail-AntiSpam: 
 AC=PASS;BC=-1|-1;BR=01201311R141e4;CH=green;DM=||false|;DS=||;FP=0|-1|-1|-1|0|-1|-1|-1;HT=e01f04428;MF=tianjia.zhang@linux.alibaba.com;NM=1;PH=DS;RN=37;SR=0;TI=SMTPD_---0Tvg4OPB_1587013858;
Received: from localhost(mailfrom:tianjia.zhang@linux.alibaba.com
 fp:SMTPD_---0Tvg4OPB_1587013858)
          by smtp.aliyun-inc.com(127.0.0.1);
          Thu, 16 Apr 2020 13:10:58 +0800
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
        christoffer.dall@arm.com, peterx@redhat.com, thuth@redhat.com
Cc: kvm@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
        kvmarm@lists.cs.columbia.edu, linux-mips@vger.kernel.org,
        kvm-ppc@vger.kernel.org, linuxppc-dev@lists.ozlabs.org,
        linux-s390@vger.kernel.org, linux-kernel@vger.kernel.org,
        tianjia.zhang@linux.alibaba.com
Subject: [PATCH v2] KVM: Optimize kvm_arch_vcpu_ioctl_run function
Date: Thu, 16 Apr 2020 13:10:57 +0800
Message-Id: <20200416051057.26526-1-tianjia.zhang@linux.alibaba.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In earlier versions of kvm, 'kvm_run' is an independent structure
and is not included in the vcpu structure. At present, 'kvm_run'
is already included in the vcpu structure, so the parameter
'kvm_run' is redundant.

This patch simplify the function definition, removes the extra
'kvm_run' parameter, and extract it from the 'kvm_vcpu' structure
if necessary.

Signed-off-by: Tianjia Zhang <tianjia.zhang@linux.alibaba.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---

v2 change:
  remove 'kvm_run' parameter and extract it from 'kvm_vcpu'

 arch/mips/kvm/mips.c       |  3 ++-
 arch/powerpc/kvm/powerpc.c |  3 ++-
 arch/s390/kvm/kvm-s390.c   |  3 ++-
 arch/x86/kvm/x86.c         | 11 ++++++-----
 include/linux/kvm_host.h   |  2 +-
 virt/kvm/arm/arm.c         |  6 +++---
 virt/kvm/kvm_main.c        |  2 +-
 7 files changed, 17 insertions(+), 13 deletions(-)

```
#### [PATCH v3] vhost: disable for OABI
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 11493921
Return-Path: <SRS0=ZIlC=6A=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C1C7F174A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Apr 2020 22:20:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A5877218AC
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Apr 2020 22:20:42 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="RgeU1BKY"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729044AbgDPWUi (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 16 Apr 2020 18:20:38 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:35729 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1728817AbgDPWUh (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 16 Apr 2020 18:20:37 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1587075636;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type;
        bh=LKcXo+p/uaeU/hsHRyKbdRNMgG4/p28XvmGbqiu1vto=;
        b=RgeU1BKY/zuiMPVHB2Z5lLwz3iphXI6PQXbCfYUHzm/F2sUxh+kmK3RFbxHsrlbWD+XBte
        mHCWrXsu1mAstv2Cik200wiTwC5c9hwyE8trqL4uUptXnaOTMv7LoLJ5rzWa2bmS7z6541
        9lMxjYYLp+UOWYQvJsw/E+Itv0ccjgY=
Received: from mail-wr1-f71.google.com (mail-wr1-f71.google.com
 [209.85.221.71]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-364-VMzsqttjMWq6OdaiSCkvTA-1; Thu, 16 Apr 2020 18:20:24 -0400
X-MC-Unique: VMzsqttjMWq6OdaiSCkvTA-1
Received: by mail-wr1-f71.google.com with SMTP id s11so2478954wru.6
        for <kvm@vger.kernel.org>; Thu, 16 Apr 2020 15:20:24 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:mime-version
         :content-disposition;
        bh=LKcXo+p/uaeU/hsHRyKbdRNMgG4/p28XvmGbqiu1vto=;
        b=XoWf/E0UGvDo/yqVuniYxdlx67/UFeSOo9QY90QbzyPVbkZOv6YORDYy5VZBcjqUpU
         Xrv4nG4cx5iC2XvMm6PCvfqC8YxTAa35Ma+XoKf6XsjdnMn9Z4INxTU4Q2zNiX/xQ7O8
         EbxcNuDjfoIdrscaKq06W4JUC3lX3DrmBU9V1rB/MRFQJUFR6LiCTA7htHtc/NObJoE1
         ded72e8dlo3zwx5nMiK+/HN8k1Ser9fQ3gajV4AoB6AFfRqrkKcxyyukLryidlpJPsI3
         ZXL968nrZ5lDZpRgT97TgFTiLM26kzpwZHZfCt+rErJsrCAzwFo2ifjrS2kyszcUGp5m
         XRWA==
X-Gm-Message-State: AGi0PuYThYtuStsbMRac545JT7/qtTVlVxMQ+DAxdmUEs4e//yfJzntY
        9GIQk/prrber/5Kd99GcI26zMEgN1N2qefHxf3yssw6fArUyKJYKElbSgV3sc8AUCBrMlcZ63Hi
        SKGBqB3k/3bYP
X-Received: by 2002:a7b:c955:: with SMTP id i21mr43720wml.25.1587075622982;
        Thu, 16 Apr 2020 15:20:22 -0700 (PDT)
X-Google-Smtp-Source: 
 APiQypLTMzBiCaoZdbA9StOEic7q7PuNDUniFaAXDS0fu05xLaJzs2UfTHwtFzY0cbIA235H0bagiw==
X-Received: by 2002:a7b:c955:: with SMTP id i21mr43692wml.25.1587075622724;
        Thu, 16 Apr 2020 15:20:22 -0700 (PDT)
Received: from redhat.com (bzq-79-183-51-3.red.bezeqint.net. [79.183.51.3])
        by smtp.gmail.com with ESMTPSA id
 g186sm5712499wmg.36.2020.04.16.15.20.21
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 16 Apr 2020 15:20:22 -0700 (PDT)
Date: Thu, 16 Apr 2020 18:20:20 -0400
From: "Michael S. Tsirkin" <mst@redhat.com>
To: linux-kernel@vger.kernel.org
Cc: Ard Biesheuvel <ardb@kernel.org>,
        Richard Earnshaw <Richard.Earnshaw@arm.com>,
        Sudeep Dutt <sudeep.dutt@intel.com>,
        Ashutosh Dixit <ashutosh.dixit@intel.com>,
        Arnd Bergmann <arnd@arndb.de>,
        Greg Kroah-Hartman <gregkh@linuxfoundation.org>,
        "David S. Miller" <davem@davemloft.net>,
        Jason Wang <jasowang@redhat.com>, netdev@vger.kernel.org,
        virtualization@lists.linux-foundation.org, kvm@vger.kernel.org
Subject: [PATCH v3] vhost: disable for OABI
Message-ID: <20200416221902.5801-1-mst@redhat.com>
MIME-Version: 1.0
Content-Disposition: inline
X-Mailer: git-send-email 2.24.1.751.gd10ce2899c
X-Mutt-Fcc: =sent
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

vhost is currently broken on the some ARM configs.

The reason is that that uses apcs-gnu which is the ancient OABI that is been
deprecated for a long time.

Given that virtio support on such ancient systems is not needed in the
first place, let's just add something along the lines of

	depends on !ARM || AEABI

to the virtio Kconfig declaration, and add a comment that it has to do
with struct member alignment.

Note: we can't make VHOST and VHOST_RING themselves have
a dependency since these are selected. Add a new symbol for that.

Link: https://lore.kernel.org/r/20200406121233.109889-3-mst@redhat.com
Suggested-by: Ard Biesheuvel <ardb@kernel.org>
Suggested-by: Richard Earnshaw <Richard.Earnshaw@arm.com>
Signed-off-by: Michael S. Tsirkin <mst@redhat.com>
---

Changes from v2:
	- drop prompt from VHOST_DPN
	- typo fix in commit log
	- OABI is a possible ARM config but not the default one

 drivers/misc/mic/Kconfig |  2 +-
 drivers/net/caif/Kconfig |  2 +-
 drivers/vdpa/Kconfig     |  2 +-
 drivers/vhost/Kconfig    | 17 +++++++++++++----
 4 files changed, 16 insertions(+), 7 deletions(-)

```
#### [PATCH] vfio/type1: Fix VA->PA translation for PFNMAP VMAs in vaddr_get_pfn()
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11493923
Return-Path: <SRS0=ZIlC=6A=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 403B815AB
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Apr 2020 22:51:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 31FC8221F7
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Apr 2020 22:51:09 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729078AbgDPWvB (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 16 Apr 2020 18:51:01 -0400
Received: from mga17.intel.com ([192.55.52.151]:49373 "EHLO mga17.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726441AbgDPWvB (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 16 Apr 2020 18:51:01 -0400
IronPort-SDR: 
 aRe8YSExJc6b+NOKf+/LcTTbrawLHr5zB4eJ1UT3n4uakgnSmWH0Rl48V/SyO4ibo4xEvhapRO
 rolR3tuBKltg==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by fmsmga107.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 16 Apr 2020 15:51:00 -0700
IronPort-SDR: 
 3SWrEXltK0cnP2E2h1Fyod1t7tbH4FXYJ+dEFSp2J6FRqQBb7wyTtq7UxRHsZy1fHUWpLWiP3N
 HAuEvO4RzINA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.72,392,1580803200";
   d="scan'208";a="278029698"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by orsmga008.jf.intel.com with ESMTP; 16 Apr 2020 15:50:59 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Alex Williamson <alex.williamson@redhat.com>
Cc: Cornelia Huck <cohuck@redhat.com>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org,
        Sean Christopherson <sean.j.christopherson@intel.com>
Subject: [PATCH] vfio/type1: Fix VA->PA translation for PFNMAP VMAs in
 vaddr_get_pfn()
Date: Thu, 16 Apr 2020 15:50:57 -0700
Message-Id: <20200416225057.8449-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Use follow_pfn() to get the PFN of a PFNMAP VMA instead of assuming that
vma->vm_pgoff holds the base PFN of the VMA.  This fixes a bug where
attempting to do VFIO_IOMMU_MAP_DMA on an arbitrary PFNMAP'd region of
memory calculates garbage for the PFN.

Hilariously, this only got detected because the first "PFN" calculated
by vaddr_get_pfn() is PFN 0 (vma->vm_pgoff==0), and iommu_iova_to_phys()
uses PA==0 as an error, which triggers a WARN in vfio_unmap_unpin()
because the translation "failed".  PFN 0 is now unconditionally reserved
on x86 in order to mitigate L1TF, which causes is_invalid_reserved_pfn()
to return true and in turns results in vaddr_get_pfn() returning success
for PFN 0.  Eventually the bogus calculation runs into PFNs that aren't
reserved and leads to failure in vfio_pin_map_dma().  The subsequent
call to vfio_remove_dma() attempts to unmap PFN 0 and WARNs.

  WARNING: CPU: 8 PID: 5130 at drivers/vfio/vfio_iommu_type1.c:750 vfio_unmap_unpin+0x2e1/0x310 [vfio_iommu_type1]
  Modules linked in: vfio_pci vfio_virqfd vfio_iommu_type1 vfio ...
  CPU: 8 PID: 5130 Comm: sgx Tainted: G        W         5.6.0-rc5-705d787c7fee-vfio+ #3
  Hardware name: Intel Corporation Mehlow UP Server Platform/Moss Beach Server, BIOS CNLSE2R1.D00.X119.B49.1803010910 03/01/2018
  RIP: 0010:vfio_unmap_unpin+0x2e1/0x310 [vfio_iommu_type1]
  Code: <0f> 0b 49 81 c5 00 10 00 00 e9 c5 fe ff ff bb 00 10 00 00 e9 3d fe
  RSP: 0018:ffffbeb5039ebda8 EFLAGS: 00010246
  RAX: 0000000000000000 RBX: ffff9a55cbf8d480 RCX: 0000000000000000
  RDX: 0000000000000000 RSI: 0000000000000001 RDI: ffff9a52b771c200
  RBP: 0000000000000000 R08: 0000000000000040 R09: 00000000fffffff2
  R10: 0000000000000001 R11: ffff9a51fa896000 R12: 0000000184010000
  R13: 0000000184000000 R14: 0000000000010000 R15: ffff9a55cb66ea08
  FS:  00007f15d3830b40(0000) GS:ffff9a55d5600000(0000) knlGS:0000000000000000
  CS:  0010 DS: 0000 ES: 0000 CR0: 0000000080050033
  CR2: 0000561cf39429e0 CR3: 000000084f75f005 CR4: 00000000003626e0
  DR0: 0000000000000000 DR1: 0000000000000000 DR2: 0000000000000000
  DR3: 0000000000000000 DR6: 00000000fffe0ff0 DR7: 0000000000000400
  Call Trace:
   vfio_remove_dma+0x17/0x70 [vfio_iommu_type1]
   vfio_iommu_type1_ioctl+0x9e3/0xa7b [vfio_iommu_type1]
   ksys_ioctl+0x92/0xb0
   __x64_sys_ioctl+0x16/0x20
   do_syscall_64+0x4c/0x180
   entry_SYSCALL_64_after_hwframe+0x44/0xa9
  RIP: 0033:0x7f15d04c75d7
  Code: <48> 3d 01 f0 ff ff 73 01 c3 48 8b 0d 81 48 2d 00 f7 d8 64 89 01 48

Fixes: 73fa0d10d077 ("vfio: Type1 IOMMU implementation")
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---

I'm mostly confident this is correct from the standpoint that it generates
the correct VA->PA.  I'm far less confident the end result is what VFIO
wants, there appears to be a fair bit of magic going on that I don't fully
understand, e.g. I'm a bit mystified as to how this ever worked in any
capacity.

Mapping PFNMAP VMAs into the IOMMU without using a mmu_notifier also seems
dangerous, e.g. if the subsystem associated with the VMA unmaps/remaps the
VMA then the IOMMU will end up with stale translations.

Last thought, using PA==0 for the error seems unnecessarily risky, e.g.
why not use something similar to KVM_PFN_ERR_* or an explicit return code?

 drivers/vfio/vfio_iommu_type1.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH v2 1/1] x86/kvm/hyper-v: Add support to SYNIC exit on EOM
##### From: Jon Doron <arilou@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jon Doron <arilou@gmail.com>
X-Patchwork-Id: 11492561
Return-Path: <SRS0=ZIlC=6A=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D43FE81
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Apr 2020 09:11:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AA73720787
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Apr 2020 09:11:21 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="Us5R3I5n"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2441259AbgDPIjP (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 16 Apr 2020 04:39:15 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:38820 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2502682AbgDPIjF (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 16 Apr 2020 04:39:05 -0400
Received: from mail-wr1-x442.google.com (mail-wr1-x442.google.com
 [IPv6:2a00:1450:4864:20::442])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 98DF4C061A10;
        Thu, 16 Apr 2020 01:39:04 -0700 (PDT)
Received: by mail-wr1-x442.google.com with SMTP id k11so3820502wrp.5;
        Thu, 16 Apr 2020 01:39:04 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=PkvJMl1gqjbqsZHs+qV+I97naXMp6apsvSAWhtAhZ1U=;
        b=Us5R3I5nXYZ/qD4V87LVi5rjfklLkNZJPGc1m/boLL6nmQoSwEmWJXz/ZYIinnCMsp
         C8wqvCQxkRXFrgmYGkZdIPTO1UCOIHnTuV97OWUzSWVl7ll0CvjQ6IN+kPq76sXXUUpj
         Vbi5Q3iVbVYYpeHqC7EDerGtiu7vmtsxq1KmVQhRAmzE1YPPyEfdpFIREvUfXbB84jg1
         73+0U50AS/wVu4qR089bG+eVc/ptnAys70Rt56hZy5i/Sv/1UL3gYIoquJllqaPyP+kJ
         +9gxelePEjcgFxDHgqHMw2t7hwo6zCCgtM5X9wA3CHzwvRHZRjwPBWjkibg1k+5YGw0Y
         CqNA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=PkvJMl1gqjbqsZHs+qV+I97naXMp6apsvSAWhtAhZ1U=;
        b=fa1nu7odWMFnINTfF80ERmeHqNnUmdC1/XW7YmstkZD4H+vvX7DzDw9eK3aDu0mfm/
         hNh5UdwV/6AeFpLsbnxB0Um2qfTJ+QprzZJJVYPodzOggQ3nNHW3XumA54S4MC2zd/y1
         Hj0AiId5fltsyeYfdMSzYJwGQrQb6e6w2Zs8M2rJsN1tuY/d7UtqCSxl/nfpcX0mgulc
         YpQwsWZP4mqFhqj9k6REaV2XAmr1SX8xIq9x4J2A0b6VtpHGcGhJjU1gqs0BkurZqndm
         q2nBi2n69xx/uTdJqjswP5YFxeLEZ+i9SIaeFbfcJkDt/+IhcaXvKV/keeZP9xndUxzu
         rASQ==
X-Gm-Message-State: AGi0PubwGoVrNle46nf1/zwy8bI+8Dtos5CdGGNt7spAPOQEX3Vbq7Nr
        u/nBK+j4zFvM5LvsENVmufbwsIX2NW986w==
X-Google-Smtp-Source: 
 APiQypJKsd9oyZg3ySBMjY8FH2RQyTioVfnAsmkgeOFQTYRHKx0dtq8hnwkidMNNEulteSXbN3wzRA==
X-Received: by 2002:a5d:49c7:: with SMTP id t7mr32017503wrs.22.1587026342989;
        Thu, 16 Apr 2020 01:39:02 -0700 (PDT)
Received: from jondnuc.lan (IGLD-84-229-155-55.inter.net.il. [84.229.155.55])
        by smtp.gmail.com with ESMTPSA id
 s12sm1256358wmc.7.2020.04.16.01.39.01
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 16 Apr 2020 01:39:02 -0700 (PDT)
From: Jon Doron <arilou@gmail.com>
To: kvm@vger.kernel.org, linux-hyperv@vger.kernel.org
Cc: vkuznets@redhat.com, rvkagan@yandex-team.ru,
        Jon Doron <arilou@gmail.com>
Subject: [PATCH v2 1/1] x86/kvm/hyper-v: Add support to SYNIC exit on EOM
Date: Thu, 16 Apr 2020 11:38:47 +0300
Message-Id: <20200416083847.1776387-2-arilou@gmail.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20200416083847.1776387-1-arilou@gmail.com>
References: <20200416083847.1776387-1-arilou@gmail.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

According to the TLFS a write to the EOM register by the guest
causes the hypervisor to scan for any pending messages and if there
are any it will try to deliver them.

To do this we must exit so any pending messages can be written.

Signed-off-by: Jon Doron <arilou@gmail.com>
---
 arch/x86/include/asm/kvm_host.h |  1 +
 arch/x86/kvm/hyperv.c           | 67 +++++++++++++++++++++++++++++----
 arch/x86/kvm/hyperv.h           |  1 +
 arch/x86/kvm/x86.c              |  5 +++
 include/uapi/linux/kvm.h        |  1 +
 5 files changed, 67 insertions(+), 8 deletions(-)

```
