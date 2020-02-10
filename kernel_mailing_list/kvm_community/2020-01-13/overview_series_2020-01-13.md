#### [PATCH kvm-unit-tests 1/3] arm/arm64: Improve memory region management
##### From: Andrew Jones <drjones@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11330115
Return-Path: <SRS0=ekPD=3C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 51602930
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 13 Jan 2020 13:00:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 264F32080D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 13 Jan 2020 13:00:54 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="YfC0BPab"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728665AbgAMNAx (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 13 Jan 2020 08:00:53 -0500
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:55472 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726567AbgAMNAx (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 13 Jan 2020 08:00:53 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1578920451;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=OwXlzBEQhwCa8wParpIDpsxijVGaBsk9N2BIUCVw5x0=;
        b=YfC0BPabh7j76b72CpbGLqkOt/dPvBXn2KqCX0xXoWejMi7/djQdKJ2qiX8T40jBOafqwU
        aQMCk7JptWcPicA71/uo+4cmx3pPwlhUqzmIsXiLRsPDVETSGiaoAv5XWifAzbncFqBRn8
        qd8DrEHH7ysDKwSeLifvDmtK7mw5ZzU=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-113-SUHtmpXOOaWK3twCgs47zQ-1; Mon, 13 Jan 2020 08:00:48 -0500
X-MC-Unique: SUHtmpXOOaWK3twCgs47zQ-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 4271218A6EC9;
        Mon, 13 Jan 2020 13:00:47 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.43.2.160])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 0D30C6A846;
        Mon, 13 Jan 2020 13:00:45 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu
Cc: pbonzini@redhat.com, alexandru.elisei@arm.com
Subject: [PATCH kvm-unit-tests 1/3] arm/arm64: Improve memory region
 management
Date: Mon, 13 Jan 2020 14:00:41 +0100
Message-Id: <20200113130043.30851-2-drjones@redhat.com>
In-Reply-To: <20200113130043.30851-1-drjones@redhat.com>
References: <20200113130043.30851-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add expected I/O regions and provide a way to check memory region
properties of a physical address. We also bump the initial number
of regions and even prepare for a unit test to reallocate for
growth if necessary.

Signed-off-by: Andrew Jones <drjones@redhat.com>
---
 lib/arm/asm/setup.h |  8 +++++--
 lib/arm/mmu.c       | 24 ++++++-------------
 lib/arm/setup.c     | 56 +++++++++++++++++++++++++++++++++------------
 3 files changed, 55 insertions(+), 33 deletions(-)

```
#### [PATCH 1/3] KVM: x86: Add vendor-specific #DB payload deliveryFrom: Oliver Upton <oupton@google.com>
##### From: Oliver Upton <oupton@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Oliver Upton <oupton@google.com>
X-Patchwork-Id: 11331009
Return-Path: <SRS0=ekPD=3C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4D3B36C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 13 Jan 2020 22:11:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 2175D2084D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 13 Jan 2020 22:11:01 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="cIhcoFTd"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728872AbgAMWLA (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 13 Jan 2020 17:11:00 -0500
Received: from mail-pj1-f74.google.com ([209.85.216.74]:44194 "EHLO
        mail-pj1-f74.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727382AbgAMWK7 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 13 Jan 2020 17:10:59 -0500
Received: by mail-pj1-f74.google.com with SMTP id c31so7550322pje.9
        for <kvm@vger.kernel.org>; Mon, 13 Jan 2020 14:10:58 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=m/qOsq+wdtuQutrd4owz9XAVpuoAS5ct18Ghp0jkcFg=;
        b=cIhcoFTduW7s3DvTZHusTuz8xxLfFLk/Olb5FJxQOUrbd3nb2CYZrB/IhHQFlPSqKW
         FE06w0x6T4R/9stBfD09QDSgAIIJA7el+2Q0mhrjdZO9//IQi//Ye8TiDKXeCc4tfvNP
         gdUtv0LHa0itmn9QZjr5MogldoqqyaOEhMAHJ25hIBpK1/T5mT95zKfMVDQiPanjzbDV
         ee7XSByDxZsgoh/67ZCkC3Xr68Y5sNVJHK//uDhs57/y5yRAEzgwiw8k12YrCO+yAgns
         Fc/AaddyQbYl2vVcJwpGuoKHzD6GoB2P1qJs6pDdmWp+P26ozUF+uO17Ha8yZCO0rvGy
         Csiw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=m/qOsq+wdtuQutrd4owz9XAVpuoAS5ct18Ghp0jkcFg=;
        b=txV2x8DKZxNFrMsDmYj51PDlDMh9Z6cxyZZsWUH+nuYR3CYYyuBRyVsfajwS6bLRal
         ACr0LVclVgtIDr8OOGgw3OoJKfL/Kg960giJMpLJQXX7DluFo9Pl3lBNgJklCrJgTE2f
         x8GiqHXwGqNp8xEnzKa//NXe+66FV8dt8phLQc0xuNC6BX/WCSBrrYBvXpwrnBfqGB+R
         YFI74I+fWaRLRHNeKT83L21yPO/pMQasDJVxEkgc0/vM64m9k9hgr53LrWuQGgqBZKGj
         qPZqXFX4/oMxV0BJNcZ5FW7X/qcP51FFhI/gYftmHlpQJEXAEXDtiI+BeoO326cYkFlR
         3OnA==
X-Gm-Message-State: APjAAAWdd2gj7z82HhLZBgJe/B+HWfnB38XsCGVdUife+QWdDi81kk4D
        ptRcAh9lU+stBV7g/YZhQVqkFDcjexHQj9UZXoqFbafyfTGBP2HjlhpRijg3cmNX1QBcgWDcyot
        itPt8jHLbTkFafiBKmzXni0zWfWtGR1dVzhHyqmw+dj9Zu9cKs4HpfEZnuw==
X-Google-Smtp-Source: 
 APXvYqyJITlnAOKB0VRr6bEvGfITZUgjTa7u1NdRTLHuDGLsl3FrgSiC04j3UHkZcmm1Q8ZVS/TnsSgPF8k=
X-Received: by 2002:a63:de4a:: with SMTP id
 y10mr23244878pgi.367.1578953458112;
 Mon, 13 Jan 2020 14:10:58 -0800 (PST)
Date: Mon, 13 Jan 2020 14:10:51 -0800
In-Reply-To: <20200113221053.22053-1-oupton@google.com>
Message-Id: <20200113221053.22053-2-oupton@google.com>
Mime-Version: 1.0
References: <20200113221053.22053-1-oupton@google.com>
X-Mailer: git-send-email 2.25.0.rc1.283.g88dfdc4193-goog
Subject: [PATCH 1/3] KVM: x86: Add vendor-specific #DB payload delivery
From: Oliver Upton <oupton@google.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Oliver Upton <oupton@google.com>,
        Peter Shier <pshier@google.com>,
        Jim Mattson <jmattson@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

VMX and SVM differ slightly in the handling of #DB debug-trap exceptions
upon VM-entry. VMX defines the 'pending debug exceptions' field in the
VMCS for hardware to inject the event and update debug register state
upon VM-entry.

SVM provides no such mechanism for maintaining the state of a pending
debug exception, as the debug register state is updated before delivery
of #VMEXIT.

Lastly, while KVM defines the exception payload for debug-trap
exceptions as compatible with the 'pending debug exceptions' VMCS field,
it is not compatible with the DR6 register across both vendors.

Split the #DB payload delivery between SVM and VMX to capture the
nuanced differences in instruction emulation. Utilize the 'pending debug
exceptions' field on VMX to deliver the payload. On SVM, directly update
register state with the appropriate requested bits from the exception
payload.

Fixes: f10c729ff965 ("kvm: vmx: Defer setting of DR6 until #DB delivery")

Signed-off-by: Oliver Upton <oupton@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 arch/x86/include/asm/kvm_host.h |  1 +
 arch/x86/kvm/svm.c              | 20 ++++++++++++++++++++
 arch/x86/kvm/vmx/vmx.c          | 20 +++++++++++++++++++-
 arch/x86/kvm/x86.c              | 21 +--------------------
 4 files changed, 41 insertions(+), 21 deletions(-)

```
#### [kvm-unit-tests] travis.yml: Prevent 'script' section from premature exit
##### From: Wainer dos Santos Moschetta <wainersm@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wainer dos Santos Moschetta <wainersm@redhat.com>
X-Patchwork-Id: 11330785
Return-Path: <SRS0=ekPD=3C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 28D86109A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 13 Jan 2020 19:51:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E567D21556
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 13 Jan 2020 19:51:10 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="XhZA5WDZ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728512AbgAMTvK (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 13 Jan 2020 14:51:10 -0500
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:35081 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726202AbgAMTvJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 13 Jan 2020 14:51:09 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1578945069;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=0mFyRlYXkeza/c8rVf5F+jfb7DpuuePFUt7750qH+2s=;
        b=XhZA5WDZ5xORjUlJDJ0H/cwKhPUA1Leuu93b58R3ZpCRp5Rm9pAyjaDULrZqQs8nwuzkiI
        uw3EtORTDM7v+R1ODXwLsUUKsZd0Qm/xNpd+W9KXhtoqorRX4VEkU17gL8+AVen1Y7D4oc
        Lj+njorTDJJqrdSr96eHEItD0vtQLOs=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-367-Bf4kQpwhM--bwaFdHgFyww-1; Mon, 13 Jan 2020 14:51:07 -0500
X-MC-Unique: Bf4kQpwhM--bwaFdHgFyww-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id ABDDB108C2AD
        for <kvm@vger.kernel.org>; Mon, 13 Jan 2020 19:51:06 +0000 (UTC)
Received: from localhost.localdomain (ovpn-116-74.gru2.redhat.com
 [10.97.116.74])
        by smtp.corp.redhat.com (Postfix) with ESMTP id E674260BF1;
        Mon, 13 Jan 2020 19:51:04 +0000 (UTC)
From: Wainer dos Santos Moschetta <wainersm@redhat.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, thuth@redhat.com
Subject: [kvm-unit-tests] travis.yml: Prevent 'script' section from premature
 exit
Date: Mon, 13 Jan 2020 16:51:02 -0300
Message-Id: <20200113195102.44756-1-wainersm@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The 'script' section finishes its execution prematurely whenever
a shell's exit is called. If the intention is to force
Travis to flag a build/test failure then the correct approach
is erroring any build command. In this change, it executes a
sub-shell process and exit 1, so that Travis capture the return
code and interpret it as a build error.

Signed-off-by: Wainer dos Santos Moschetta <wainersm@redhat.com>
---
 .travis.yml | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH] KVM: VMX: Rename define to CPU_BASED_USE_TSC_OFFSETTING
##### From: Borislav Petkov <bp@alien8.de>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Borislav Petkov <bp@alien8.de>
X-Patchwork-Id: 11330745
Return-Path: <SRS0=ekPD=3C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 72D1813A0
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 13 Jan 2020 18:52:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 507C1207E0
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 13 Jan 2020 18:52:30 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=alien8.de header.i=@alien8.de
 header.b="CHuOHTdN"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728680AbgAMSw0 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 13 Jan 2020 13:52:26 -0500
Received: from mail.skyhub.de ([5.9.137.197]:58730 "EHLO mail.skyhub.de"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726435AbgAMSw0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 13 Jan 2020 13:52:26 -0500
Received: from zn.tnic (p200300EC2F05D30049A87F91DFBF49F4.dip0.t-ipconnect.de
 [IPv6:2003:ec:2f05:d300:49a8:7f91:dfbf:49f4])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.skyhub.de (SuperMail on ZX Spectrum 128k) with ESMTPSA id
 264231EC0CBF;
        Mon, 13 Jan 2020 19:52:24 +0100 (CET)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=alien8.de; s=dkim;
        t=1578941544;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:in-reply-to:in-reply-to:
  references:references;
        bh=nroBP1M9a+oDLvFHSrWrc/9Pg86AU7wcX7yapLqPoeI=;
        b=CHuOHTdNpZGOYG47VGt6oBtE5RAxe7d8TvFCYjsAjjFB8fSqH+3OwPexCnHeVJYgCxrKU5
        IHJd/aI68UOL0L5Xxri11CE+Z3Pd/sEcYcACZ/aanHHJVcI9MnRWqznCzy7OzLpZcSTqE7
        gfib7yhDI3gdZFNlUJjJvYXaBq+E0UQ=
Date: Mon, 13 Jan 2020 19:52:16 +0100
From: Borislav Petkov <bp@alien8.de>
To: Sean Christopherson <sean.j.christopherson@intel.com>
Cc: Thomas Gleixner <tglx@linutronix.de>, Ingo Molnar <mingo@redhat.com>,
 x86@kernel.org, "H. Peter Anvin" <hpa@zytor.com>,
 Peter Zijlstra <peterz@infradead.org>,
 Arnaldo Carvalho de Melo <acme@kernel.org>,
 Mark Rutland <mark.rutland@arm.com>,
 Alexander Shishkin <alexander.shishkin@linux.intel.com>,
 Jiri Olsa <jolsa@redhat.com>, Namhyung Kim <namhyung@kernel.org>,
 Paolo Bonzini <pbonzini@redhat.com>,
 Radim =?utf-8?b?S3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Vitaly Kuznetsov <vkuznets@redhat.com>, Wanpeng Li <wanpengli@tencent.com>,
 Jim Mattson <jmattson@google.com>, Joerg Roedel <joro@8bytes.org>,
 Tony Luck <tony.luck@intel.com>, Tony W Wang-oc <TonyWWang-oc@zhaoxin.com>,
 Jacob Pan <jacob.jun.pan@linux.intel.com>, Len Brown <lenb@kernel.org>,
 Shuah Khan <shuah@kernel.org>, linux-kernel@vger.kernel.org,
 kvm@vger.kernel.org, linux-edac@vger.kernel.org, linux-pm@vger.kernel.org,
 linux-kselftest@vger.kernel.org,
 Jarkko Sakkinen <jarkko.sakkinen@linux.intel.com>
Subject: [PATCH] KVM: VMX: Rename define to CPU_BASED_USE_TSC_OFFSETTING
Message-ID: <20200113185216.GQ13310@zn.tnic>
References: <20191221044513.21680-1-sean.j.christopherson@intel.com>
 <20191221044513.21680-18-sean.j.christopherson@intel.com>
 <20200113183228.GO13310@zn.tnic>
 <20200113183705.GL1175@linux.intel.com>
 <20200113183823.GP13310@zn.tnic>
 <20200113184217.GA2216@linux.intel.com>
MIME-Version: 1.0
Content-Disposition: inline
In-Reply-To: <20200113184217.GA2216@linux.intel.com>
User-Agent: Mutt/1.10.1 (2018-07-13)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

On Mon, Jan 13, 2020 at 10:42:17AM -0800, Sean Christopherson wrote:
> > Doesn't bother me, I could do it in a patch ontop. But your call.
> 
> No objection here.

Something like this:
---
From: Borislav Petkov <bp@suse.de>

... so that "offsetting" is spelled the same as the respective VMX feature
bit VMX_FEATURE_TSC_OFFSETTING.

No functional changes.

Signed-off-by: Borislav Petkov <bp@suse.de>
---
 arch/x86/include/asm/vmx.h                               | 2 +-
 arch/x86/kvm/vmx/nested.c                                | 8 ++++----
 arch/x86/kvm/vmx/vmx.c                                   | 6 +++---
 tools/testing/selftests/kvm/include/x86_64/vmx.h         | 2 +-
 tools/testing/selftests/kvm/x86_64/vmx_tsc_adjust_test.c | 2 +-
 5 files changed, 10 insertions(+), 10 deletions(-)

```
