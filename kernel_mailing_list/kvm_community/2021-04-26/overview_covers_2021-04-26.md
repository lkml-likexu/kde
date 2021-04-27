

#### [RFC PATCH 0/6] x86/kvm: Virtual suspend time injection support
##### From: Hikaru Nishida <hikalium@chromium.org>

```c
From patchwork Mon Apr 26 09:06:39 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Hikaru Nishida <hikalium@chromium.org>
X-Patchwork-Id: 12224001
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-14.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E48E8C433B4
	for <kvm@archiver.kernel.org>; Mon, 26 Apr 2021 09:09:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9B54E60FEF
	for <kvm@archiver.kernel.org>; Mon, 26 Apr 2021 09:09:06 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232756AbhDZJJl (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 26 Apr 2021 05:09:41 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:59904 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S232710AbhDZJJG (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 26 Apr 2021 05:09:06 -0400
Received: from mail-pg1-x52e.google.com (mail-pg1-x52e.google.com
 [IPv6:2607:f8b0:4864:20::52e])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 3B73CC061756
        for <kvm@vger.kernel.org>; Mon, 26 Apr 2021 02:08:24 -0700 (PDT)
Received: by mail-pg1-x52e.google.com with SMTP id j7so30238155pgi.3
        for <kvm@vger.kernel.org>; Mon, 26 Apr 2021 02:08:24 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=chromium.org; s=google;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=HNdzFDdOgeWXGKXmnjDGLCV9ZQhV0CgleaBxzMVsBew=;
        b=Zu3BggN8BFpvKZGn6qHGXUPTHBTV4x1GkM1zsI4Okx7UF40oT4oF5Pmw6uYulawjjb
         0KlLYFgLhZvaknAJ+/IQfINmmgk96eMHEw89RwtnWU85lDW76coUguECJmDwWTADV7mo
         i8DhqIGQCCJNYmZWbVFxUAd6UsCPsRA4APklA=
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=HNdzFDdOgeWXGKXmnjDGLCV9ZQhV0CgleaBxzMVsBew=;
        b=J9yl47Ugn7SoifenbUTo3AVysjCLY3R7TDq8tZoz9pFPK5F4VOEJ+QkuI5THol0O5U
         UcfyW7uPLEWkgbsGcg8lKcndCGMfsJ7eVGIzPe+BapwE2ZldMTHci8i8wly+Tnoe1oWQ
         CdOBtsh6Fs12qu1ZwGniMdztE/9/EdHjV0goYPiNRK95vmYTxEwl0ZvqZZk2t01vTzJO
         EZyRbMcgoh0o805vByMojbzdBDN+ax2w+c1UXoM1aUGKltDdVwQjhcaaTkzisRipVYk9
         3zBGfLDqIj0ljuRfOjFteY2W9/jCQw32OTp00FN4AoOUr0DAI8aQN2BnQPRnx8gvMiPY
         wF/Q==
X-Gm-Message-State: AOAM533kGrWR4jOT66Si1i5kYoOFWwVMU+Cc5WunfthIjSeXEsiXYe7k
        wuMxsWF5NI5J2sEsGQzc0CYWFbSYFDgsBA==
X-Google-Smtp-Source: 
 ABdhPJxCIKL4jdEbT9jB4QA6Zvprni9bDSdgXrCbWLLsGOXVPQwykN6qzWsE4gCtmVAhCaRxtGLepA==
X-Received: by 2002:aa7:9046:0:b029:272:3729:e10a with SMTP id
 n6-20020aa790460000b02902723729e10amr9940066pfo.49.1619428103205;
        Mon, 26 Apr 2021 02:08:23 -0700 (PDT)
Received: from localhost (160.131.236.35.bc.googleusercontent.com.
 [35.236.131.160])
        by smtp.gmail.com with UTF8SMTPSA id
 kk9sm12011641pjb.23.2021.04.26.02.08.20
        (version=TLS1_3 cipher=TLS_AES_128_GCM_SHA256 bits=128/128);
        Mon, 26 Apr 2021 02:08:22 -0700 (PDT)
From: Hikaru Nishida <hikalium@chromium.org>
To: kvm@vger.kernel.org
Cc: suleiman@google.com, Hikaru Nishida <hikalium@chromium.org>,
        Borislav Petkov <bp@alien8.de>,
        "H. Peter Anvin" <hpa@zytor.com>, Ingo Molnar <mingo@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        John Stultz <john.stultz@linaro.org>,
        Jonathan Corbet <corbet@lwn.net>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Stephen Boyd <sboyd@kernel.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>, linux-doc@vger.kernel.org,
        linux-kernel@vger.kernel.org, x86@kernel.org
Subject: [RFC PATCH 0/6] x86/kvm: Virtual suspend time injection support
Date: Mon, 26 Apr 2021 18:06:39 +0900
Message-Id: <20210426090644.2218834-1-hikalium@chromium.org>
X-Mailer: git-send-email 2.31.1.498.g6c1eba8ee3d-goog
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

This patch series adds virtual suspend time injection support to KVM.

Before this change, if the host goes into suspended state while the
guest is running, the guest will experience a time jump after the host's
resume. This can confuse some services in the guest since they can't
detect if the system went into suspend or not by comparing
CLOCK_BOOTTIME and CLOCK_MONOTONIC.

To solve this problem, we wanted to add a way to adjust the guest clocks
without actually suspending the guests. However, there was no way to
modify a gap between CLOCK_BOOTTIME and CLOCK_MONOTONIC without actually
suspending the guests. Therefore, this series introduce a new struct
called kvm_host_suspend_time to share the suspend time between host and
guest and a mechanism to inject a suspend time to the guest while
keeping
monotonicity of the clocks.

Could you take a look and let me know how we can improve the patches if
they are doing something wrong?

Thanks,

Hikaru Nishida



Hikaru Nishida (6):
  x86/kvm: Reserve KVM_FEATURE_HOST_SUSPEND_TIME and
    MSR_KVM_HOST_SUSPEND_TIME
  x86/kvm: Add a struct and constants for virtual suspend time injection
  x86/kvm: Add CONFIG_KVM_VIRT_SUSPEND_TIMING
  x86/kvm: Add a host side support for virtual suspend time injection
  x86/kvm: Add CONFIG_KVM_VIRT_SUSPEND_TIMING_GUEST
  x86/kvm: Add a guest side support for virtual suspend time injection

 Documentation/virt/kvm/cpuid.rst     |  3 +
 Documentation/virt/kvm/msr.rst       | 29 +++++++++
 arch/x86/Kconfig                     | 13 ++++
 arch/x86/include/asm/kvm_host.h      |  5 ++
 arch/x86/include/asm/kvm_para.h      |  9 +++
 arch/x86/include/uapi/asm/kvm_para.h |  6 ++
 arch/x86/kernel/kvmclock.c           | 25 ++++++++
 arch/x86/kvm/Kconfig                 | 13 ++++
 arch/x86/kvm/cpuid.c                 |  4 ++
 arch/x86/kvm/x86.c                   | 89 +++++++++++++++++++++++++++-
 include/linux/kvm_host.h             |  7 +++
 include/linux/timekeeper_internal.h  |  4 ++
 kernel/time/timekeeping.c            | 31 ++++++++++
 13 files changed, 237 insertions(+), 1 deletion(-)
```
#### [PATCH v2 0/6] Introduce KVM_{GET|SET}_SREGS2 and fix PDPTR migration
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
From patchwork Mon Apr 26 11:13:27 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 12224165
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E2891C433B4
	for <kvm@archiver.kernel.org>; Mon, 26 Apr 2021 11:14:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AA7BA61359
	for <kvm@archiver.kernel.org>; Mon, 26 Apr 2021 11:14:19 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233034AbhDZLO7 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 26 Apr 2021 07:14:59 -0400
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:41637 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S232492AbhDZLO4 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 26 Apr 2021 07:14:56 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1619435655;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=4EGSofxQx4brtBrsah9Z+zPRC9nWkVvSS5E/pnfMZn0=;
        b=E0S6t5qc1zssvPJR2i03GN7FsBl/xfOKirD79+vlmyeJMSCiGLYE6eNjkqYydjfnVzq4Ov
        JLrw0Dn3DpThH/RdoWS073q/3ZFrjlz3g74zeEJAPpLgyPrzoUk/wAfOrm0FupFIbsvcXo
        LJ+YxwtkrqTzH7h8x/txfEct/a2A99k=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-442-78yYM6mCOhS2wonT2h580w-1; Mon, 26 Apr 2021 07:14:11 -0400
X-MC-Unique: 78yYM6mCOhS2wonT2h580w-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id ABF3F84B9A7;
        Mon, 26 Apr 2021 11:13:40 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.40.192.73])
        by smtp.corp.redhat.com (Postfix) with ESMTP id BAE505D9F0;
        Mon, 26 Apr 2021 11:13:35 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: linux-doc@vger.kernel.org (open list:DOCUMENTATION),
        Thomas Gleixner <tglx@linutronix.de>,
        Jonathan Corbet <corbet@lwn.net>,
        Paolo Bonzini <pbonzini@redhat.com>,
        x86@kernel.org (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT)),
        linux-kernel@vger.kernel.org (open list:X86 ARCHITECTURE (32-BIT AND
        64-BIT)), "H. Peter Anvin" <hpa@zytor.com>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        Wanpeng Li <wanpengli@tencent.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Sean Christopherson <seanjc@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH v2 0/6] Introduce KVM_{GET|SET}_SREGS2 and fix PDPTR migration
Date: Mon, 26 Apr 2021 14:13:27 +0300
Message-Id: <20210426111333.967729-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch set aims to fix few flaws that were discovered
in KVM_{GET|SET}_SREGS on x86:

* There is no support for reading/writing PDPTRs although
  these are considered to be part of the guest state.

* There is useless interrupt bitmap which isn't needed

* No support for future extensions (via flags and such)

Also if the user doesn't use the new SREG2 api, the PDPTR
load after migration is now done on KVM_REQ_GET_NESTED_STATE_PAGES
to at least read them correctly in cases when guest memory
map is not up to date when nested state is loaded.

This patch series was tested by doing nested migration test
of 32 bit PAE L1 + 32 bit PAE L2 on AMD and Intel and by
nested migration test of 64 bit L1 + 32 bit PAE L2 on AMD.
The later test currently fails on Intel (regardless of my patches).

Changes from V1:
  - move only PDPTRS load to KVM_REQ_GET_NESTED_STATE_PAGES on VMX
  - rebase on top of kvm/queue
  - improve the KVM_GET_SREGS2 to have flag for PDPTRS
    and remove padding

Patches to qemu will be send soon as well.

Best regards,
        Maxim Levitskky

Maxim Levitsky (6):
  KVM: nSVM: refactor the CR3 reload on migration
  KVM: nVMX: delay loading of PDPTRs to KVM_REQ_GET_NESTED_STATE_PAGES
  KVM: x86: introduce kvm_register_clear_available
  KVM: x86: Introduce KVM_GET_SREGS2 / KVM_SET_SREGS2
  KVM: nSVM: avoid loading PDPTRs after migration when possible
  KVM: nVMX: avoid loading PDPTRs after migration when possible

 Documentation/virt/kvm/api.rst  |  48 +++++++++++
 arch/x86/include/asm/kvm_host.h |   7 ++
 arch/x86/include/uapi/asm/kvm.h |  13 +++
 arch/x86/kvm/kvm_cache_regs.h   |  12 +++
 arch/x86/kvm/svm/nested.c       |  33 ++++++--
 arch/x86/kvm/svm/svm.c          |   6 +-
 arch/x86/kvm/vmx/nested.c       |  24 ++++--
 arch/x86/kvm/x86.c              | 139 ++++++++++++++++++++++++++------
 include/uapi/linux/kvm.h        |   4 +
 9 files changed, 246 insertions(+), 40 deletions(-)
```
#### [PATCH v2 0/2] kvm: use KVM_{GET|SET}_SREGS2 when available
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
From patchwork Mon Apr 26 11:58:48 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 12224199
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 0EF4EC433ED
	for <kvm@archiver.kernel.org>; Mon, 26 Apr 2021 11:59:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C9D2561185
	for <kvm@archiver.kernel.org>; Mon, 26 Apr 2021 11:59:02 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233191AbhDZL7n (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 26 Apr 2021 07:59:43 -0400
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:46329 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S231970AbhDZL7m (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 26 Apr 2021 07:59:42 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1619438340;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=+nCk6Ve+TN+8pnIdsqGxzK6u1TVgQuTIbmRV1IvBlv8=;
        b=irSODoH+Ei1INot5TAB5pViGN2zp/YiKReOe9djiwMex/NXvmqK5pODMIncMbQ3ITdI/A0
        TUVf1Jm1VAisqt4o8ZmxZYeRg/XQOBHZfx2o1o77Ed3pwrMaxU+5KX+V/HmCD7Oeb3Ts5K
        qbHgldYAvDwn4uxBkiIKnZdWvusabKk=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-352-wMXs2KOMPeWxPCW9ha64fQ-1; Mon, 26 Apr 2021 07:58:58 -0400
X-MC-Unique: wMXs2KOMPeWxPCW9ha64fQ-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 170135F9FF;
        Mon, 26 Apr 2021 11:58:58 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.40.192.73])
        by smtp.corp.redhat.com (Postfix) with ESMTP id E85F960855;
        Mon, 26 Apr 2021 11:58:51 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: qemu-devel@nongnu.org
Cc: Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org,
        Marcelo Tosatti <mtosatti@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Eduardo Habkost <ehabkost@redhat.com>,
        Richard Henderson <richard.henderson@linaro.org>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH v2 0/2] kvm: use KVM_{GET|SET}_SREGS2 when available
Date: Mon, 26 Apr 2021 14:58:48 +0300
Message-Id: <20210426115850.1003501-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This implements support for using these new
IOCTLS to migrate PDPTRS.

Best regards,
	Maxim Levitsky

Maxim Levitsky (2):
  kvm: update kernel headers for KVM_{GET|SET}_SREGS2
  KVM: use KVM_{GET|SET}_SREGS2 when supported.

 accel/kvm/kvm-all.c         |   5 ++
 include/sysemu/kvm.h        |   4 ++
 linux-headers/asm-x86/kvm.h |  13 +++++
 linux-headers/linux/kvm.h   |   5 ++
 target/i386/cpu.h           |   3 +
 target/i386/kvm/kvm.c       | 107 +++++++++++++++++++++++++++++++++++-
 target/i386/machine.c       |  30 ++++++++++
 7 files changed, 165 insertions(+), 2 deletions(-)
```
#### [for-6.1 v2 0/2] virtiofsd: Add support for FUSE_SYNCFS request
##### From: Greg Kurz <groug@kaod.org>

```c
From patchwork Mon Apr 26 15:21:33 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Greg Kurz <groug@kaod.org>
X-Patchwork-Id: 12224405
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 68072C433B4
	for <kvm@archiver.kernel.org>; Mon, 26 Apr 2021 15:21:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 347B76135A
	for <kvm@archiver.kernel.org>; Mon, 26 Apr 2021 15:21:55 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233923AbhDZPWg convert rfc822-to-8bit (ORCPT
        <rfc822;kvm@archiver.kernel.org>); Mon, 26 Apr 2021 11:22:36 -0400
Received: from us-smtp-delivery-44.mimecast.com ([205.139.111.44]:39725 "EHLO
        us-smtp-delivery-44.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S233573AbhDZPWf (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 26 Apr 2021 11:22:35 -0400
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-44-L4NhDlQ8OHCOCv_9G1-kuA-1; Mon, 26 Apr 2021 11:21:49 -0400
X-MC-Unique: L4NhDlQ8OHCOCv_9G1-kuA-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 49A9B85EE8B;
        Mon, 26 Apr 2021 15:21:48 +0000 (UTC)
Received: from bahia.redhat.com (ovpn-113-148.ams2.redhat.com [10.36.113.148])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 40ACB60C5F;
        Mon, 26 Apr 2021 15:21:36 +0000 (UTC)
From: Greg Kurz <groug@kaod.org>
To: qemu-devel@nongnu.org
Cc: Cornelia Huck <cohuck@redhat.com>,
        "Dr. David Alan Gilbert" <dgilbert@redhat.com>,
        Stefan Hajnoczi <stefanha@redhat.com>, kvm@vger.kernel.org,
        virtio-fs@redhat.com, Miklos Szeredi <miklos@szeredi.hu>,
        Vivek Goyal <vgoyal@redhat.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>, Greg Kurz <groug@kaod.org>
Subject: [for-6.1 v2 0/2] virtiofsd: Add support for FUSE_SYNCFS request
Date: Mon, 26 Apr 2021 17:21:33 +0200
Message-Id: <20210426152135.842037-1-groug@kaod.org>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
X-Mimecast-Spam-Score: 0
X-Mimecast-Originator: kaod.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

FUSE_SYNCFS allows the client to flush the host page cache.
This isn't available in upstream linux yet, but the following
tree can be used to test:

https://gitlab.com/gkurz/linux/-/tree/virtio-fs-sync

v2: - based on new version of FUSE_SYNCFS
      https://listman.redhat.com/archives/virtio-fs/2021-April/msg00166.html
    - propagate syncfs() errors to client (Vivek)

Greg Kurz (2):
  Update linux headers to 5.12-rc8 + FUSE_SYNCFS
  virtiofsd: Add support for FUSE_SYNCFS request

 include/standard-headers/drm/drm_fourcc.h     | 23 ++++-
 include/standard-headers/linux/ethtool.h      | 54 ++++++-----
 include/standard-headers/linux/fuse.h         | 13 ++-
 include/standard-headers/linux/input.h        |  2 +-
 .../standard-headers/rdma/vmw_pvrdma-abi.h    |  7 ++
 linux-headers/asm-generic/unistd.h            |  4 +-
 linux-headers/asm-mips/unistd_n32.h           |  1 +
 linux-headers/asm-mips/unistd_n64.h           |  1 +
 linux-headers/asm-mips/unistd_o32.h           |  1 +
 linux-headers/asm-powerpc/kvm.h               |  2 +
 linux-headers/asm-powerpc/unistd_32.h         |  1 +
 linux-headers/asm-powerpc/unistd_64.h         |  1 +
 linux-headers/asm-s390/unistd_32.h            |  1 +
 linux-headers/asm-s390/unistd_64.h            |  1 +
 linux-headers/asm-x86/kvm.h                   |  1 +
 linux-headers/asm-x86/unistd_32.h             |  1 +
 linux-headers/asm-x86/unistd_64.h             |  1 +
 linux-headers/asm-x86/unistd_x32.h            |  1 +
 linux-headers/linux/kvm.h                     | 89 +++++++++++++++++++
 linux-headers/linux/vfio.h                    | 27 ++++++
 tools/virtiofsd/fuse_lowlevel.c               | 19 ++++
 tools/virtiofsd/fuse_lowlevel.h               | 13 +++
 tools/virtiofsd/passthrough_ll.c              | 29 ++++++
 tools/virtiofsd/passthrough_seccomp.c         |  1 +
 24 files changed, 267 insertions(+), 27 deletions(-)
```
#### [PATCH v2 00/13] Remove vfio_mdev.c, mdev_parent_ops and more
##### From: Jason Gunthorpe <jgg@nvidia.com>

```c
From patchwork Mon Apr 26 20:00:02 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Gunthorpe <jgg@nvidia.com>
X-Patchwork-Id: 12224997
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,
	SPF_PASS autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 5BA2BC43461
	for <kvm@archiver.kernel.org>; Mon, 26 Apr 2021 20:00:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2FFEA61359
	for <kvm@archiver.kernel.org>; Mon, 26 Apr 2021 20:00:24 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S241768AbhDZUBE (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 26 Apr 2021 16:01:04 -0400
Received: from mail-bn8nam08on2069.outbound.protection.outlook.com
 ([40.107.100.69]:56800
        "EHLO NAM04-BN8-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S241643AbhDZUBC (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 26 Apr 2021 16:01:02 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=SUPSGBHOdYVqh2TD7jnMzDyt8x0nv6JmI9gJ4FoCQgEdmi/7cj643CWrh0urbJ/iphdRzuHv0WMpg2d4+utHyCpPxZ+qVHnVH6gppy3UABpLD25HTCpXXvEP3jaoDJcN9GsHdBlyhFQIIeOCwwN29MSz+4yCy+/ZIeWUrbsqdgoK+A6Za8I5oqeYJhfaBOXyVHy/hyXB+ZkvGICnGiiQzLgdWLXC30Rr+HwSpDboot3q2VugwvVnKEDVmNDEbRkZO1wDiOv53JtcP+nphKkZWBps9mHC9zY0Cy1nSsiVDX4RKEcSr0KyOEJFLbn6cbbpjsQEfdKd232+SQaq5LopBw==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=olwDiL66vfekS16MVboSGcToyx/UXCU6SuGuTMItXbo=;
 b=kYXoTvZdalIx+8HqweIkySCb5FCd427KUDg497CuFQz/b8SIiqTDFcIMO2N7VW6oglqoXgFZCGNo8TBN4H/EYhaGR5y4+EqVzfN7RWMt01xey2L+hlHTlDLRdQ3wnfkJqC2yDlLLzxVzPPc5nA45qjm07+VKJhe3ENuBz3SNp8HD1HIbHgVONZQ3o9J0L8wJtkH0GYpGvywM5QIllBft10Y/F6H31XroOCvCfdpXowQsRjIg99KuqkSXw77n+I1MjZ516Y8wXLyyPDkSdlJZDMHhTs5xdWxQ0sQad92+emObwBflUDegGeWKTUX+UTMC/clwPNiSPUNINcHenYuilw==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=nvidia.com; dmarc=pass action=none header.from=nvidia.com;
 dkim=pass header.d=nvidia.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=Nvidia.com;
 s=selector2;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=olwDiL66vfekS16MVboSGcToyx/UXCU6SuGuTMItXbo=;
 b=E+FPbX2LhZjrnGXIPjkUembzk1m792iDQQu9vT3qd+fH6OJWr9FkphGr+iyRcYnKbJPUlQ38Lc1BL2/thnUobQlTP/hIkRJkgcDzNUI3cIiZTafOJAWYO48cPBFIsUD+7lEFnKNJ49+SOTtvBwVwr0qETQvKMPzjdkDXr8LI6gkem50cgA5LzOndVJezq8uQp+J+PVDguAqQMxL/6u10F050s2ueIH9qaAlNRnU8xH4F9xtVliLOP3eqrwbczRgM7w/cWqnvqYdTC/mnlG/FuZgvv7BewJYB66acINHaX1NpAA5YAFVIY/cl0MNm0Gi6Zl7cb0QCMp5OSWDQwHvDeA==
Authentication-Results: linux.ie; dkim=none (message not signed)
 header.d=none;linux.ie; dmarc=none action=none header.from=nvidia.com;
Received: from DM6PR12MB3834.namprd12.prod.outlook.com (2603:10b6:5:14a::12)
 by DM6PR12MB3740.namprd12.prod.outlook.com (2603:10b6:5:1c3::13) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4065.24; Mon, 26 Apr
 2021 20:00:17 +0000
Received: from DM6PR12MB3834.namprd12.prod.outlook.com
 ([fe80::1c62:7fa3:617b:ab87]) by DM6PR12MB3834.namprd12.prod.outlook.com
 ([fe80::1c62:7fa3:617b:ab87%6]) with mapi id 15.20.4065.026; Mon, 26 Apr 2021
 20:00:17 +0000
From: Jason Gunthorpe <jgg@nvidia.com>
To: David Airlie <airlied@linux.ie>,
        Tony Krowiak <akrowiak@linux.ibm.com>,
        Alex Williamson <alex.williamson@redhat.com>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Jonathan Corbet <corbet@lwn.net>,
        Daniel Vetter <daniel@ffwll.ch>,
        dri-devel@lists.freedesktop.org,
        Eric Farman <farman@linux.ibm.com>,
        Harald Freudenberger <freude@linux.ibm.com>,
        Vasily Gorbik <gor@linux.ibm.com>,
        Heiko Carstens <hca@linux.ibm.com>,
        intel-gfx@lists.freedesktop.org,
        intel-gvt-dev@lists.freedesktop.org,
        Jani Nikula <jani.nikula@linux.intel.com>,
        Joonas Lahtinen <joonas.lahtinen@linux.intel.com>,
        kvm@vger.kernel.org, Kirti Wankhede <kwankhede@nvidia.com>,
        linux-doc@vger.kernel.org, linux-s390@vger.kernel.org,
        Peter Oberparleiter <oberpar@linux.ibm.com>,
        Halil Pasic <pasic@linux.ibm.com>,
        Pierre Morel <pmorel@linux.ibm.com>,
        Rodrigo Vivi <rodrigo.vivi@intel.com>,
        Vineeth Vijayan <vneethv@linux.ibm.com>,
        Zhenyu Wang <zhenyuw@linux.intel.com>,
        Zhi Wang <zhi.a.wang@intel.com>
Cc: "Raj, Ashok" <ashok.raj@intel.com>,
        Dan Williams <dan.j.williams@intel.com>,
        Christoph Hellwig <hch@lst.de>,
        Leon Romanovsky <leonro@nvidia.com>,
        Max Gurtovoy <mgurtovoy@nvidia.com>,
        Tarun Gupta <targupta@nvidia.com>
Subject: [PATCH v2 00/13] Remove vfio_mdev.c, mdev_parent_ops and more
Date: Mon, 26 Apr 2021 17:00:02 -0300
Message-Id: <0-v2-7667f42c9bad+935-vfio3_jgg@nvidia.com>
X-Originating-IP: [47.55.113.94]
X-ClientProxiedBy: MN2PR20CA0052.namprd20.prod.outlook.com
 (2603:10b6:208:235::21) To DM6PR12MB3834.namprd12.prod.outlook.com
 (2603:10b6:5:14a::12)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from mlx.ziepe.ca (47.55.113.94) by
 MN2PR20CA0052.namprd20.prod.outlook.com (2603:10b6:208:235::21) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4065.20 via Frontend
 Transport; Mon, 26 Apr 2021 20:00:16 +0000
Received: from jgg by mlx with local (Exim 4.94)        (envelope-from
 <jgg@nvidia.com>)        id 1lb7Ox-00DFYy-MJ; Mon, 26 Apr 2021 17:00:15 -0300
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: e20688d0-e5cf-4c4e-8438-08d908ede987
X-MS-TrafficTypeDiagnostic: DM6PR12MB3740:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM6PR12MB3740A304BFC7E0F85CD45347C2429@DM6PR12MB3740.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:8882;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 8BtlUhugUCgKqMJolQ6Snv6XAQRUwcEltMTpSr7aTcjG2JxvRnLdH9qgDoJEcBWcyoxfExU68vcKJpfhavrMrQ3Hh/NC2N92BIMlZpJ2sLI/4IJqeYOw5spdZlJ4FyLypqfNraF+xZWK1bjqKwtGjPpEVjh2eD3h9HgmT9DX9skOEmdG8QOOVpQfezdqEH4NfBA0p3sNjXAfBXGqoTAZx61HTtubstFiDedXfPMRVofY8vMo12TdnNsnokU26kCcB7FgAR3mcjOQiNyKN1zYJ6QhrC4fcyZ9bdlLqD35OMeihhuesjV4AUCiiEQCVPGbjWY+Zsfk/sYNMH2Q84zZilqifGcTjl38Z4qa5eRepHcE/bSFS1VGd9FT+soDFWLJt5qLlIoFeM7HnVIZrpHx4jDYq4X8eg3k9/DbiKf51TB+RupW3LDP3TDPUfN2OBMokNW60AI54/+i54rNl0VhcQ8TdEJD6rrinfJ7gZ1vBABccm9EHkqYVgf2WutvaKePyTw2n9JKowcyqBcYdGj/3KDKvNF4Sb+4jAlyu1m7oNNl5j9QBz8TyRKXG1nS5bxNPzAZMfst1gwZEz9MqBx5S1cb7VVPMBDXBqxYK6NkAMpdTD3b4DmqkKbBShnLRyMuJ6/eNFictAgTqcpf3bPhspNtf2b5waaOLnMqTQekCa1TY7s2ZZCZAeJp8zpbdtsL5oEjK+viM4phHLsHZ4MwpABQqy8OWHyx8dxqD0ivQAhIABvDJJ8ULRouZw7OgqlH
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM6PR12MB3834.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(366004)(39860400002)(346002)(136003)(396003)(376002)(66476007)(66556008)(966005)(9746002)(54906003)(426003)(110136005)(107886003)(186003)(26005)(921005)(6666004)(36756003)(316002)(2906002)(2616005)(478600001)(9786002)(8936002)(83380400001)(38100700002)(86362001)(8676002)(5660300002)(7416002)(4326008)(66946007)(4216001);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 ZKFr44UUWfx1zrXbOHAbVR38gF6pTBagwkJEvKvsBSY3eldD4WAurqvL5oTn4XjydPH+QeANwD8TfXzIyPHYO9GXWtthRarCGumdw+DRa5HsS+lQXA81QHG3A+kClSlP75oilJi8o0yAMnBPzQtwEybAiKu2SlPhvru73r1mWMuqQxOGczct6338CVOoZDfyaxc+BXnUOcpVzTrERUlUeSvkiTCvSJUthOds4MfQq45OhCmIF75LTU55BTNa94fJTMYQFiVkXAy8mzPXDuOVr/L83h6ZqgG3pVakR8YBhpqUHXqJYhlA+LSbN/N1wIHcSbKBIUv5dCzZf11XdptQnVveZOM8xG5RYmu0K/JxDJaKk5T1oWEWtad273930FySjPc6hvTN/eui5gqeGWTzm0hAWLcMtaKOXpAB2aiZw4ed2sv+p1BoHlvtze86WsumArXJRNxJkJ8YU5W64i9WJXgFKiLRtHo2A0zi68A9+PwggnQXcy0MNQznjkfZxWZegPfTkfpUG73yO8LwBzXN2Yz0Lxo48hyKwAwcLa3Q2hc+xzPxdpiEVXyveH4X1lEDaFEdx8lTAES1BpL3j1VSAEiN5u/5elhY4tXIgJJ2kR2tloHt69ik88gXxoeoBq+N4dGdjbniWSK6aLI0P4ZouiC1AXjSaHy+4ODLwcm1SzK2zbBPYwEr/Kr7UXsj56ufOwXFG6jTBvmUFVNICJEAZV3DqZCZbwX5SNaDPS1CeBWjg24koL7Z1wSft+5XGGSOjlCb+KXESL96Bkp0E0cxndVkxUYsBX0N7WOoasRRYiqPHtGuAxgdK8o7vwHnWMZ1CKP8ZcB1M7Y51H8j2DkIsKuXTSqUUPvP9ioEZyCdkoCbdWhDEPkXnEdaGDOsOnpyRVbRMC2iDjixyyzKoqgdGA77VUjhiIrHaDj9QV80PnK1ervIH0T7NE/aGWeYjL2X9ketyz7omQEQej+UOY6X2WNqB/ORLntBSqsyKNZ6YQRpKA2hw9zsckTeu4P3jow0pcNfbBqCKpZifbh+CKrFf2KpZUO6aLRy1J4C7trWUH/mu8uS5Z3kGJ77T/0EK5hsFMGhxLTik9tHvPvBgadcMKV2LYLQbqV4F/aoqAIiu8rGYnuTIsJw6S20beASToGpKsdyG/hiX3jvvDWcT/M1MFa8MYC9ZgF0Sm6yY8JnOFE0rq6W+vMxrEDNhoAGpBQVEpZGcHECAh3e9gc+46WAAH1zkJ/hDjsDdv15JR5Ha2WVRNwHrMvHTbLw5sVWphQl16MXajMX9hWwOLyH3I4daLgmW/7LPqkCPStjvFLkk1QbuqxDa+U6ymlXqXVhDuoO
X-OriginatorOrg: Nvidia.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 e20688d0-e5cf-4c4e-8438-08d908ede987
X-MS-Exchange-CrossTenant-AuthSource: DM6PR12MB3834.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 26 Apr 2021 20:00:17.0848
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 43083d15-7273-40c1-b7db-39efd9ccc17a
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 IGoPkPY5oZXdWuJY/24/CeMjO6D9Mvs/G9bYCjRjhQTDtII0l8G6IR/oZkPfCwM7
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6PR12MB3740
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The mdev bus's core part for managing the lifecycle of devices is mostly
as one would expect for a driver core bus subsystem.

However instead of having a normal 'struct device_driver' and binding the
actual mdev drivers through the standard driver core mechanisms it open
codes this with the struct mdev_parent_ops and provides a single driver
that shims between the VFIO core and the actual device driver.

Make every one of the mdev drivers implement an actual struct mdev_driver
and directly call vfio_register_group_dev() in the probe() function for
the mdev.

Squash what is left of the mdev_parent_ops into the mdev_driver and remap
create(), remove() and mdev_attr_groups to their driver core
equivalents. Arrange to bind the created mdev_device to the mdev_driver
that is provided by the end driver.

The actual execution flow doesn't change much, eg what was
parent_ops->create is now device_driver->probe and it is called at almost
the exact same time - except under the normal control of the driver core.

This allows deleting the entire mdev_drvdata, and tidying some of the
sysfs. Many places in the drivers start using container_of()

This cleanly splits the mdev sysfs GUID lifecycle management stuff from
the vfio_device implementation part, the only VFIO special part of mdev
that remains is the mdev specific iommu intervention.

v2:
 - Keep && m in samples kconfig
 - Restore accidently squashed removeal of vfio_mdev.c
 - Remove indirections to call bus_register()/bus_unregister()
 - Reflow long doc lines
v1: https://lore.kernel.org/r/0-v1-d88406ed308e+418-vfio3_jgg@nvidia.com

Jason

Cc: Leon Romanovsky <leonro@nvidia.com>
Cc: "Raj, Ashok" <ashok.raj@intel.com>
Cc: Dan Williams <dan.j.williams@intel.com>
Cc: Max Gurtovoy <mgurtovoy@nvidia.com>
Cc: Christoph Hellwig <hch@lst.de>
Cc: Tarun Gupta <targupta@nvidia.com>
Cc: Daniel Vetter <daniel@ffwll.ch>


Jason Gunthorpe (13):
  vfio/mdev: Remove CONFIG_VFIO_MDEV_DEVICE
  vfio/mdev: Allow the mdev_parent_ops to specify the device driver to
    bind
  vfio/mtty: Convert to use vfio_register_group_dev()
  vfio/mdpy: Convert to use vfio_register_group_dev()
  vfio/mbochs: Convert to use vfio_register_group_dev()
  vfio/ap_ops: Convert to use vfio_register_group_dev()
  vfio/ccw: Convert to use vfio_register_group_dev()
  vfio/gvt: Convert to use vfio_register_group_dev()
  vfio/mdev: Remove vfio_mdev.c
  vfio/mdev: Remove mdev_parent_ops dev_attr_groups
  vfio/mdev: Remove mdev_parent_ops
  vfio/mdev: Use the driver core to create the 'remove' file
  vfio/mdev: Remove mdev drvdata

 .../driver-api/vfio-mediated-device.rst       |  56 ++---
 Documentation/s390/vfio-ap.rst                |   1 -
 arch/s390/Kconfig                             |   2 +-
 drivers/gpu/drm/i915/Kconfig                  |   2 +-
 drivers/gpu/drm/i915/gvt/kvmgt.c              | 210 +++++++++--------
 drivers/s390/cio/vfio_ccw_drv.c               |  21 +-
 drivers/s390/cio/vfio_ccw_ops.c               | 136 ++++++-----
 drivers/s390/cio/vfio_ccw_private.h           |   5 +
 drivers/s390/crypto/vfio_ap_ops.c             | 138 ++++++-----
 drivers/s390/crypto/vfio_ap_private.h         |   2 +
 drivers/vfio/mdev/Kconfig                     |   7 -
 drivers/vfio/mdev/Makefile                    |   1 -
 drivers/vfio/mdev/mdev_core.c                 |  67 ++++--
 drivers/vfio/mdev/mdev_driver.c               |  20 +-
 drivers/vfio/mdev/mdev_private.h              |   4 +-
 drivers/vfio/mdev/mdev_sysfs.c                |  37 ++-
 drivers/vfio/mdev/vfio_mdev.c                 | 180 ---------------
 drivers/vfio/vfio.c                           |   6 +-
 include/linux/mdev.h                          |  86 +------
 include/linux/vfio.h                          |   4 +
 samples/Kconfig                               |   6 +-
 samples/vfio-mdev/mbochs.c                    | 166 +++++++------
 samples/vfio-mdev/mdpy.c                      | 162 +++++++------
 samples/vfio-mdev/mtty.c                      | 218 +++++++-----------
 24 files changed, 651 insertions(+), 886 deletions(-)
 delete mode 100644 drivers/vfio/mdev/vfio_mdev.c
```
