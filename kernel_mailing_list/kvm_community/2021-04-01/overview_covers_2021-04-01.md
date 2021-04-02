

#### [PATCH v4 0/8] KVM/ARM: Some vgic fixes and init sequence KVM
##### From: Eric Auger <eric.auger@redhat.com>

```c
From patchwork Thu Apr  1 08:52:30 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Auger Eric <eric.auger@redhat.com>
X-Patchwork-Id: 12177537
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id DFC45C43460
	for <kvm@archiver.kernel.org>; Thu,  1 Apr 2021 08:53:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A07A061055
	for <kvm@archiver.kernel.org>; Thu,  1 Apr 2021 08:53:46 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233662AbhDAIxN (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 1 Apr 2021 04:53:13 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:25253 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S229459AbhDAIwr (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 1 Apr 2021 04:52:47 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1617267166;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=BP9WZNqxIzPCA5LtPAzAvwf0rm1qTrzO8RqIvNWUBDg=;
        b=Rg3rDWb/f1dPfILyOdVRc42JL0x2MHNDK3Zm9JA4nkvrjIEauCN/5yTMDg/R3pobRk8uDv
        X2NtO3ITHi6S6ZCkzfmXpTgYEcaFGO5unNzUSGOk+0pjxqo57K1VHywUE+Xeu803xRndOE
        HWA1Ox8D+brqc541ksGRVPtomg5qdfE=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-265-37QGPauRPAqjbxf-145CTA-1; Thu, 01 Apr 2021 04:52:44 -0400
X-MC-Unique: 37QGPauRPAqjbxf-145CTA-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id ED606802B7F;
        Thu,  1 Apr 2021 08:52:42 +0000 (UTC)
Received: from laptop.redhat.com (ovpn-112-13.ams2.redhat.com [10.36.112.13])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 0924E5D9DE;
        Thu,  1 Apr 2021 08:52:39 +0000 (UTC)
From: Eric Auger <eric.auger@redhat.com>
To: eric.auger.pro@gmail.com, eric.auger@redhat.com,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        kvmarm@lists.cs.columbia.edu, maz@kernel.org, drjones@redhat.com,
        alexandru.elisei@arm.com
Cc: james.morse@arm.com, suzuki.poulose@arm.com, shuah@kernel.org,
        pbonzini@redhat.com
Subject: [PATCH v4 0/8] KVM/ARM: Some vgic fixes and init sequence KVM
 selftests
Date: Thu,  1 Apr 2021 10:52:30 +0200
Message-Id: <20210401085238.477270-1-eric.auger@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

While writting vgic v3 init sequence KVM selftests I noticed some
relatively minor issues. This was also the opportunity to try to
fix the issue laterly reported by Zenghui, related to the RDIST_TYPER
last bit emulation. The final patch is a first batch of VGIC init
sequence selftests. Of course they can be augmented with a lot more
register access tests, but let's try to move forward incrementally ...

Best Regards

Eric

This series can be found at:
https://github.com/eauger/linux/tree/vgic_kvmselftests_v4

History:
v3 -> v4:
- take into account Drew's comment on the kvm selftests. No
  change to the KVM related patches compared to v3
v2 ->v3:
- reworked last bit read accessor to handle contiguous redist
  regions and rdist not registered in ascending order
- removed [PATCH 5/9] KVM: arm: move has_run_once after the
  map_resources
v1 -> v2:
- Took into account all comments from Marc and Alexandru's except
  the has_run_once still after the map_resources (this would oblige
  me to revisit in depth the selftests)


Eric Auger (8):
  KVM: arm64: vgic-v3: Fix some error codes when setting RDIST base
  KVM: arm64: Fix KVM_VGIC_V3_ADDR_TYPE_REDIST_REGION read
  KVM: arm64: vgic-v3: Fix error handling in vgic_v3_set_redist_base()
  KVM: arm/arm64: vgic: Reset base address on kvm_vgic_dist_destroy()
  docs: kvm: devices/arm-vgic-v3: enhance KVM_DEV_ARM_VGIC_CTRL_INIT doc
  KVM: arm64: Simplify argument passing to vgic_uaccess_[read|write]
  KVM: arm64: vgic-v3: Expose GICR_TYPER.Last for userspace
  KVM: selftests: aarch64/vgic-v3 init sequence tests

 .../virt/kvm/devices/arm-vgic-v3.rst          |   2 +-
 arch/arm64/kvm/vgic/vgic-init.c               |  13 +-
 arch/arm64/kvm/vgic/vgic-kvm-device.c         |   3 +
 arch/arm64/kvm/vgic/vgic-mmio-v3.c            | 116 +++-
 arch/arm64/kvm/vgic/vgic-mmio.c               |  10 +-
 arch/arm64/kvm/vgic/vgic.h                    |   1 +
 include/kvm/arm_vgic.h                        |   3 +
 tools/testing/selftests/kvm/.gitignore        |   1 +
 tools/testing/selftests/kvm/Makefile          |   1 +
 .../testing/selftests/kvm/aarch64/vgic_init.c | 652 ++++++++++++++++++
 .../testing/selftests/kvm/include/kvm_util.h  |   9 +
 tools/testing/selftests/kvm/lib/kvm_util.c    |  77 +++
 12 files changed, 838 insertions(+), 50 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/aarch64/vgic_init.c
```
#### [PATCH 0/4] KVM: nSVM/nVMX: fix nested virtualization treatment of
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
From patchwork Thu Apr  1 14:38:13 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 12178609
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-10.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_NONE autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 6BF31C433B4
	for <kvm@archiver.kernel.org>; Thu,  1 Apr 2021 17:46:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2B7EA61286
	for <kvm@archiver.kernel.org>; Thu,  1 Apr 2021 17:46:55 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S235564AbhDARqp (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 1 Apr 2021 13:46:45 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:57948 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S234910AbhDARlR (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 1 Apr 2021 13:41:17 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1617298876;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=vPQ/nf2q8LAkQ8OcVv2K8+oWAe1O0DGRxava7ECuAkg=;
        b=fKjyL/mQYGT6FOrLp9bmGBK+1k2MjmUvAWdi8sRjj65GMaCs6Yz9bh5ghX4avItdZ8j2F0
        7Kp/mr8j6enRgmvh3TznNcoUBmuQK2+l08GLDU5bHyjVE173TVF5p9fl1sL0lArr2xitlV
        K98XG5jD+oOSPoNYv0o5v/O8pjLIbx4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-227-WkrSyo2-PJ2wmI7lp45zfw-1; Thu, 01 Apr 2021 10:39:29 -0400
X-MC-Unique: WkrSyo2-PJ2wmI7lp45zfw-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 27CA783DEA6;
        Thu,  1 Apr 2021 14:38:22 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.206.58])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 351CD5D9CA;
        Thu,  1 Apr 2021 14:38:18 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: Thomas Gleixner <tglx@linutronix.de>,
        Wanpeng Li <wanpengli@tencent.com>,
        Borislav Petkov <bp@alien8.de>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        linux-kernel@vger.kernel.org (open list:X86 ARCHITECTURE (32-BIT AND
        64-BIT)), Vitaly Kuznetsov <vkuznets@redhat.com>,
        "H. Peter Anvin" <hpa@zytor.com>, Joerg Roedel <joro@8bytes.org>,
        Ingo Molnar <mingo@redhat.com>,
        x86@kernel.org (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT)),
        Sean Christopherson <seanjc@google.com>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH 0/4] KVM: nSVM/nVMX: fix nested virtualization treatment of
 nested exceptions
Date: Thu,  1 Apr 2021 17:38:13 +0300
Message-Id: <20210401143817.1030695-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

clone of "kernel-starship-5.12.unstable"

Maxim Levitsky (4):
  KVM: x86: pending exceptions must not be blocked by an injected event
  KVM: x86: separate pending and injected exception
  KVM: x86: correctly merge pending and injected exception
  KVM: x86: remove tweaking of inject_page_fault

 arch/x86/include/asm/kvm_host.h |  34 +++-
 arch/x86/kvm/svm/nested.c       |  65 +++----
 arch/x86/kvm/svm/svm.c          |   8 +-
 arch/x86/kvm/vmx/nested.c       | 107 +++++------
 arch/x86/kvm/vmx/vmx.c          |  14 +-
 arch/x86/kvm/x86.c              | 302 ++++++++++++++++++--------------
 arch/x86/kvm/x86.h              |   6 +-
 7 files changed, 283 insertions(+), 253 deletions(-)
```
#### [PATCH 0/2] KVM: x86: nSVM: fixes for SYSENTER emulation
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
From patchwork Thu Apr  1 11:16:12 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 12178611
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-10.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_NONE autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 6CC4DC43616
	for <kvm@archiver.kernel.org>; Thu,  1 Apr 2021 17:47:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2FACC61139
	for <kvm@archiver.kernel.org>; Thu,  1 Apr 2021 17:47:06 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S235025AbhDARrA (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 1 Apr 2021 13:47:00 -0400
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:32337 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S235169AbhDARmW (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 1 Apr 2021 13:42:22 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1617298942;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=6tYRJ1YPm2YiHZpNplHwmZcadjvns9Uy/SktMSxJfhw=;
        b=O74nDNps+K7mgMbGeV8pKAA0J3x+6+oZAaK2igZ1xpuRiBfASpZ2NjcUxRzym9Dw01od/c
        r9Thw/Y3JwTRFRtlpz8RHqfikUYv1n8v6M/Ap+VfX6PQ8LUisz6RbkF1SM6dmmSKwJoeS/
        ZSRP2aCDEPu5qiVG09eSVmesfHoCyxk=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-361-c_-25MNsOuaopDL9pXv0Sw-1; Thu, 01 Apr 2021 07:16:23 -0400
X-MC-Unique: c_-25MNsOuaopDL9pXv0Sw-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id D713480063;
        Thu,  1 Apr 2021 11:16:19 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.206.58])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 06D8A73A69;
        Thu,  1 Apr 2021 11:16:15 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, Jim Mattson <jmattson@google.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Ingo Molnar <mingo@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Joerg Roedel <joro@8bytes.org>,
        x86@kernel.org (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT)),
        Thomas Gleixner <tglx@linutronix.de>,
        "H. Peter Anvin" <hpa@zytor.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Borislav Petkov <bp@alien8.de>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH 0/2] KVM: x86: nSVM: fixes for SYSENTER emulation
Date: Thu,  1 Apr 2021 14:16:12 +0300
Message-Id: <20210401111614.996018-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is a result of a deep rabbit hole dive in regard to why
currently the nested migration of 32 bit guests
is totally broken on AMD.

It turns out that due to slight differences between the original AMD64
implementation and the Intel's remake, SYSENTER instruction behaves a
bit differently on Intel, and to support migration from Intel to AMD we
try to emulate those differences away.

Sadly that collides with virtual vmload/vmsave feature that is used in nesting.
The problem was that when it is enabled,
on migration (and otherwise when userspace reads MSR_IA32_SYSENTER_{EIP|ESP},
wrong value were returned, which leads to #DF in the
nested guest when the wrong value is loaded back.

The patch I prepared carefully fixes this, by mostly disabling that
SYSCALL emulation when we don't spoof the Intel's vendor ID, and if we do,
and yet somehow SVM is enabled (this is a very rare edge case), then
virtual vmload/save is force disabled.

V2: incorporated review feedback from Paulo.

Best regards,
        Maxim Levitsky

Maxim Levitsky (2):
  KVM: x86: add guest_cpuid_is_intel
  KVM: nSVM: improve SYSENTER emulation on AMD

 arch/x86/kvm/cpuid.h   |  8 ++++
 arch/x86/kvm/svm/svm.c | 99 +++++++++++++++++++++++++++---------------
 arch/x86/kvm/svm/svm.h |  6 +--
 3 files changed, 76 insertions(+), 37 deletions(-)
```
#### [PATCH 0/2] gdbstub: implement support for blocking interrupts on
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
From patchwork Thu Apr  1 14:41:50 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 12178619
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-10.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_NONE
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 4270DC43461
	for <kvm@archiver.kernel.org>; Thu,  1 Apr 2021 17:47:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 239D961139
	for <kvm@archiver.kernel.org>; Thu,  1 Apr 2021 17:47:21 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234479AbhDARrT (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 1 Apr 2021 13:47:19 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:37415 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S235916AbhDARnW (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 1 Apr 2021 13:43:22 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1617299002;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=Wqovkryd67AAu1yEb9Qoyk/Fi5dhTRWrAiv6mvYiJ+M=;
        b=EeyjlJRhBlWFDtA3MMfQhDiGm4IAKcJqSAXL8AJlrkFCeosDZvE96rOi+Xn4EsdleTSATD
        pF6YRJJcJOvIlzV6xaZRHisaJFtUt05sVlD4I+1/5ofSMnmk/OiYqQ3tBi28MobxMlU5A7
        HHAblSwWStrwJUsdn4kTJ5oNQ/YuYVg=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-174-cYAo7J9-MaOgWw0At0kROw-1; Thu, 01 Apr 2021 10:42:06 -0400
X-MC-Unique: cYAo7J9-MaOgWw0At0kROw-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 5E1961927813;
        Thu,  1 Apr 2021 14:41:55 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.206.58])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 4C3DD5D6B1;
        Thu,  1 Apr 2021 14:41:53 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: qemu-devel@nongnu.org
Cc: "Michael S. Tsirkin" <mst@redhat.com>,
 Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?q?Alex_Benn=C3=A9e?= <alex.bennee@linaro.org>, kvm@vger.kernel.org,
 Cornelia Huck <cohuck@redhat.com>,
 =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>,
 Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH 0/2] gdbstub: implement support for blocking interrupts on
 single stepping
Date: Thu,  1 Apr 2021 17:41:50 +0300
Message-Id: <20210401144152.1031282-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

clone of "starship_unstable"

Maxim Levitsky (2):
  kvm: update kernel headers for KVM_GUESTDBG_BLOCKEVENTS
  gdbstub: implement NOIRQ support for single step on KVM, when kvm's
    KVM_GUESTDBG_BLOCKIRQ debug flag is supported.

 accel/kvm/kvm-all.c         | 25 ++++++++++++++++
 gdbstub.c                   | 59 ++++++++++++++++++++++++++++++-------
 include/sysemu/kvm.h        | 13 ++++++++
 linux-headers/asm-x86/kvm.h |  2 ++
 linux-headers/linux/kvm.h   |  1 +
 5 files changed, 90 insertions(+), 10 deletions(-)
```
#### [PATCH 0/2] kvm: use KVM_{GET|SET}_SREGS2 when available
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
From patchwork Thu Apr  1 14:45:43 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 12178689
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-10.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E66EAC433ED
	for <kvm@archiver.kernel.org>; Thu,  1 Apr 2021 17:53:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C400E60FF3
	for <kvm@archiver.kernel.org>; Thu,  1 Apr 2021 17:53:36 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234544AbhDARx0 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 1 Apr 2021 13:53:26 -0400
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:23451 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S236442AbhDARrI (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 1 Apr 2021 13:47:08 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1617299228;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=caF8NNgeAw+4v4t8bg5Tp1fnSjzea1gBUcStxuTikxY=;
        b=RjD7QMpDc6SEJrBeuAYo4e41On/2ZZ4eooGnDMPKpci3p5YaZ7iNejW5PIxEfesTCLGB9q
        Fp+jauqDqXDevZDtbjrlmTJp0tOTOgRv2FNhojFE+yuwEdG4siabrLmOgyECq8QZjZ/DuU
        2EYtIBfNLC9HTjSsLz8Ggim5nkbK+lQ=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-207-h6n7w6QxOSCSux_680o51w-1; Thu, 01 Apr 2021 10:46:04 -0400
X-MC-Unique: h6n7w6QxOSCSux_680o51w-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 40D2D1087C67;
        Thu,  1 Apr 2021 14:45:49 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.206.58])
        by smtp.corp.redhat.com (Postfix) with ESMTP id EE51E5C233;
        Thu,  1 Apr 2021 14:45:46 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: qemu-devel@nongnu.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Eduardo Habkost <ehabkost@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Marcelo Tosatti <mtosatti@redhat.com>, kvm@vger.kernel.org,
        Richard Henderson <richard.henderson@linaro.org>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH 0/2] kvm: use KVM_{GET|SET}_SREGS2 when available
Date: Thu,  1 Apr 2021 17:45:43 +0300
Message-Id: <20210401144545.1031704-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

clone of "starship_unstable"

Maxim Levitsky (2):
  kvm: update kernel headers for KVM_{GET|SET}_SREGS2
  KVM: use KVM_{GET|SET}_SREGS2 when supported by kvm.

 accel/kvm/kvm-all.c         |   4 ++
 include/sysemu/kvm.h        |   4 ++
 linux-headers/asm-x86/kvm.h |  13 +++++
 linux-headers/linux/kvm.h   |   5 ++
 target/i386/cpu.h           |   1 +
 target/i386/kvm/kvm.c       | 101 +++++++++++++++++++++++++++++++++++-
 target/i386/machine.c       |  33 ++++++++++++
 7 files changed, 159 insertions(+), 2 deletions(-)
```
#### [PATCH v2 0/2] KVM: x86: nSVM: fixes for SYSENTER emulation
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
From patchwork Thu Apr  1 11:19:26 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 12178789
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-10.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 848A3C43470
	for <kvm@archiver.kernel.org>; Thu,  1 Apr 2021 17:54:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5BEE46112E
	for <kvm@archiver.kernel.org>; Thu,  1 Apr 2021 17:54:04 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S236227AbhDARyB (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 1 Apr 2021 13:54:01 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:36056 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S237209AbhDARvI (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 1 Apr 2021 13:51:08 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1617299467;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=6tYRJ1YPm2YiHZpNplHwmZcadjvns9Uy/SktMSxJfhw=;
        b=WxS2TTytlIBoG5DR2QhGt2KZHSbA6ucBbL4q2wX5+P135xeP3o/TRABYEdF1JwfwCR6LOR
        wEEnxAbqKtAvjZ2Zn0/L7Qw9dhAyZgfXVHhiIQmqgng3277H9AucfsLUy3PNnk5zrCo6kI
        KtzE1uRAkF51c3Gty0XRKeV02iIXxN0=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-14-A4WTr3KoPZWJDliuqV2sJA-1; Thu, 01 Apr 2021 07:19:34 -0400
X-MC-Unique: A4WTr3KoPZWJDliuqV2sJA-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 9ADAE108BD06;
        Thu,  1 Apr 2021 11:19:32 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.206.58])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 368C117B15;
        Thu,  1 Apr 2021 11:19:29 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Ingo Molnar <mingo@redhat.com>,
        linux-kernel@vger.kernel.org (open list:X86 ARCHITECTURE (32-BIT AND
        64-BIT)), "H. Peter Anvin" <hpa@zytor.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        x86@kernel.org (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT)),
        Thomas Gleixner <tglx@linutronix.de>,
        Borislav Petkov <bp@alien8.de>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH v2 0/2] KVM: x86: nSVM: fixes for SYSENTER emulation
Date: Thu,  1 Apr 2021 14:19:26 +0300
Message-Id: <20210401111928.996871-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is a result of a deep rabbit hole dive in regard to why
currently the nested migration of 32 bit guests
is totally broken on AMD.

It turns out that due to slight differences between the original AMD64
implementation and the Intel's remake, SYSENTER instruction behaves a
bit differently on Intel, and to support migration from Intel to AMD we
try to emulate those differences away.

Sadly that collides with virtual vmload/vmsave feature that is used in nesting.
The problem was that when it is enabled,
on migration (and otherwise when userspace reads MSR_IA32_SYSENTER_{EIP|ESP},
wrong value were returned, which leads to #DF in the
nested guest when the wrong value is loaded back.

The patch I prepared carefully fixes this, by mostly disabling that
SYSCALL emulation when we don't spoof the Intel's vendor ID, and if we do,
and yet somehow SVM is enabled (this is a very rare edge case), then
virtual vmload/save is force disabled.

V2: incorporated review feedback from Paulo.

Best regards,
        Maxim Levitsky

Maxim Levitsky (2):
  KVM: x86: add guest_cpuid_is_intel
  KVM: nSVM: improve SYSENTER emulation on AMD

 arch/x86/kvm/cpuid.h   |  8 ++++
 arch/x86/kvm/svm/svm.c | 99 +++++++++++++++++++++++++++---------------
 arch/x86/kvm/svm/svm.h |  6 +--
 3 files changed, 76 insertions(+), 37 deletions(-)
```
#### [PATCH v2 0/9] KVM: my debug patch queue
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
From patchwork Thu Apr  1 13:54:42 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 12178793
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-10.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 6422CC43470
	for <kvm@archiver.kernel.org>; Thu,  1 Apr 2021 17:58:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4647461261
	for <kvm@archiver.kernel.org>; Thu,  1 Apr 2021 17:58:49 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S236833AbhDAR6r (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 1 Apr 2021 13:58:47 -0400
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:38937 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S236960AbhDAR4I (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 1 Apr 2021 13:56:08 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1617299768;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=CqTbGA2nnEQCoezWyE1Fpgf0IZLhERcQWs6PZNwBkg4=;
        b=jFiEEP1ySKt+P33XvxoDDxTYKWJSCcrP6KcaK1ncFumMvSJSIyDlhkiDVVQ+YJJCh0b6B3
        oW/crAi4Jc+xaGNTetGQrHI8f65REIM8SsY9AC5DQlEzKNenm8Y+DD4sjJrCOkJio4y0pa
        DDAXlb8AGKCzQbZfOc2xwboeHxiSUaA=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-450-PwIa3jVQOJCoHvlqWy6ukQ-1; Thu, 01 Apr 2021 09:55:06 -0400
X-MC-Unique: PwIa3jVQOJCoHvlqWy6ukQ-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id A55FC107B789;
        Thu,  1 Apr 2021 13:55:02 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.206.58])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 8D0E15D6B1;
        Thu,  1 Apr 2021 13:54:52 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: x86@kernel.org (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT)),
        Ingo Molnar <mingo@redhat.com>,
        Andrew Morton <akpm@linux-foundation.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Sean Christopherson <seanjc@google.com>,
        Marc Zyngier <maz@kernel.org>,
        Catalin Marinas <catalin.marinas@arm.com>,
        linux-kernel@vger.kernel.org (open list),
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Stefano Garzarella <sgarzare@redhat.com>,
        Borislav Petkov <bp@alien8.de>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Jonathan Corbet <corbet@lwn.net>, Jessica Yu <jeyu@kernel.org>,
        "H. Peter Anvin" <hpa@zytor.com>,
        Jan Kiszka <jan.kiszka@siemens.com>,
        Will Deacon <will@kernel.org>,
        kvmarm@lists.cs.columbia.edu (open list:KERNEL VIRTUAL MACHINE FOR
        ARM64 (KVM/arm64)), Paolo Bonzini <pbonzini@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Vasily Gorbik <gor@linux.ibm.com>,
        Joerg Roedel <joro@8bytes.org>,
        Claudio Imbrenda <imbrenda@linux.ibm.com>,
        Jim Mattson <jmattson@google.com>,
        Cornelia Huck <cohuck@redhat.com>,
        David Hildenbrand <david@redhat.com>,
        Maxim Levitsky <mlevitsk@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Janosch Frank <frankja@linux.ibm.com>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        linux-s390@vger.kernel.org (open list:S390),
        Heiko Carstens <hca@linux.ibm.com>,
        Kieran Bingham <kbingham@kernel.org>,
        linux-doc@vger.kernel.org (open list:DOCUMENTATION),
        linux-arm-kernel@lists.infradead.org (moderated list:KERNEL VIRTUAL
        MACHINE FOR ARM64 (KVM/arm64)), James Morse <james.morse@arm.com>
Subject: [PATCH v2 0/9] KVM: my debug patch queue
Date: Thu,  1 Apr 2021 16:54:42 +0300
Message-Id: <20210401135451.1004564-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi!

I would like to publish two debug features which were needed for other stuff
I work on.

One is the reworked lx-symbols script which now actually works on at least
gdb 9.1 (gdb 9.2 was reported to fail to load the debug symbols from the kernel
for some reason, not related to this patch) and upstream qemu.

The other feature is the ability to trap all guest exceptions (on SVM for now)
and see them in kvmtrace prior to potential merge to double/triple fault.

This can be very useful and I already had to manually patch KVM a few
times for this.
I will, once time permits, implement this feature on Intel as well.

V2:

 * Some more refactoring and workarounds for lx-symbols script

 * added KVM_GUESTDBG_BLOCKEVENTS flag to enable 'block interrupts on
   single step' together with KVM_CAP_SET_GUEST_DEBUG2 capability
   to indicate which guest debug flags are supported.

   This is a replacement for unconditional block of interrupts on single
   step that was done in previous version of this patch set.
   Patches to qemu to use that feature will be sent soon.

 * Reworked the the 'intercept all exceptions for debug' feature according
   to the review feedback:

   - renamed the parameter that enables the feature and
     moved it to common kvm module.
     (only SVM part is currently implemented though)

   - disable the feature for SEV guests as was suggested during the review
   - made the vmexit table const again, as was suggested in the review as well.

Best regards,
	Maxim Levitsky

Maxim Levitsky (9):
  scripts/gdb: rework lx-symbols gdb script
  KVM: introduce KVM_CAP_SET_GUEST_DEBUG2
  KVM: x86: implement KVM_CAP_SET_GUEST_DEBUG2
  KVM: aarch64: implement KVM_CAP_SET_GUEST_DEBUG2
  KVM: s390x: implement KVM_CAP_SET_GUEST_DEBUG2
  KVM: x86: implement KVM_GUESTDBG_BLOCKEVENTS
  KVM: SVM: split svm_handle_invalid_exit
  KVM: x86: add force_intercept_exceptions_mask
  KVM: SVM: implement force_intercept_exceptions_mask

 Documentation/virt/kvm/api.rst    |   4 +
 arch/arm64/include/asm/kvm_host.h |   4 +
 arch/arm64/kvm/arm.c              |   2 +
 arch/arm64/kvm/guest.c            |   5 -
 arch/s390/include/asm/kvm_host.h  |   4 +
 arch/s390/kvm/kvm-s390.c          |   3 +
 arch/x86/include/asm/kvm_host.h   |  12 ++
 arch/x86/include/uapi/asm/kvm.h   |   1 +
 arch/x86/kvm/svm/svm.c            |  87 +++++++++++--
 arch/x86/kvm/svm/svm.h            |   6 +-
 arch/x86/kvm/x86.c                |  14 ++-
 arch/x86/kvm/x86.h                |   2 +
 include/uapi/linux/kvm.h          |   1 +
 kernel/module.c                   |   8 +-
 scripts/gdb/linux/symbols.py      | 203 ++++++++++++++++++++----------
 15 files changed, 272 insertions(+), 84 deletions(-)
```
#### [PATCH v17 00/17] KVM RISC-V Support
##### From: Anup Patel <anup.patel@wdc.com>

```c
From patchwork Thu Apr  1 13:34:18 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Anup Patel <Anup.Patel@wdc.com>
X-Patchwork-Id: 12178867
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E99FCC433B4
	for <kvm@archiver.kernel.org>; Thu,  1 Apr 2021 18:02:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C022261159
	for <kvm@archiver.kernel.org>; Thu,  1 Apr 2021 18:02:11 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S236138AbhDASCJ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 1 Apr 2021 14:02:09 -0400
Received: from esa4.hgst.iphmx.com ([216.71.154.42]:59599 "EHLO
        esa4.hgst.iphmx.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S236548AbhDAR6A (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 1 Apr 2021 13:58:00 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=simple/simple;
  d=wdc.com; i=@wdc.com; q=dns/txt; s=dkim.wdc.com;
  t=1617299881; x=1648835881;
  h=from:to:cc:subject:date:message-id:
   content-transfer-encoding:mime-version;
  bh=73/GetQxONBnna3naBTBIVnHoPDXomMO14Fw9GZFHVU=;
  b=NaQs8pAfIq2dATvhwf1M6qKvVaTV/BYeglFATbkr9+h6lAkFe8f0+0V/
   Sf6C5WpmVgtuFaA+iJI5kePKcJnHaWJ6072/yWOlvvzq/3UtbCbtCzFC6
   kQfm+JKXp/rWQtqPPLDmXtRXQ+P40zpfHLZUvb+h2r3Vp8tazyrfzF2Gn
   x7DfErwepjJo0zWnhAnpD6a+izp6Bq6sRU29+5c8j5KFG/CaGeSbtcH7A
   c514r+s9u0HBLymGa1FyuToK2rYx/djF1uxym1tpULo+ivokKGkazPVXw
   jwGHmc558u/af4NWkrxQbptg2PC79zhSFAgRW4ve4KGxYrkLckiJygrCh
   A==;
IronPort-SDR: 
 nu3IYh6FcUDvv5raiwmlEhAoHy3Wa5u0DHPPNZj/t4qZZHXyrGa6RXRiUi0sMlxKxMMwGo3qtZ
 0asZFSjbpRH3tIUve0sCrPM9EsCXTzJ72X+Sa+wKMckSo+qJr9WYxVD4qxyJb6cDSm0GqEv3Vx
 OidGnY7aTaq8IFkcGS6SgWwrExH0u3TPrVo8tq0UcKDMLdKnVAKb0vcab9cc2lu96cO0GFBfq0
 nmLMTr4m3iQxLZ/auKkDLSDurdUAZMvwewuZk21WntThyMBmR/mUg/2vtVWYAyUsFepKcWj+J2
 tEU=
X-IronPort-AV: E=Sophos;i="5.81,296,1610380800";
   d="scan'208";a="163447192"
Received: from mail-dm3nam07lp2045.outbound.protection.outlook.com (HELO
 NAM02-DM3-obe.outbound.protection.outlook.com) ([104.47.56.45])
  by ob1.hgst.iphmx.com with ESMTP; 01 Apr 2021 21:35:20 +0800
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=gnMX0jBSgmP+7QL0oW7nDdrVkrattvWc4EmhRgN10tXNTFSSexKfPTDzwiA015Y9JM4DXy2vUOSD9DPxOaOuUv4v4mm5c1J3WctCp8jze4feWodNLzpX6MFk3NjkyFWhtpxeWpinIBm2+FhhrTM6Kcf4uHMrUncXNowQMucmvfrPa+dz3SWSfDb4sj5hHVQFGbXX+WNDS7LWi//Wz0Dlgm4UxiSiKyKYKa/km6sfAvhl0xMDV1R3RP4UHq91HX88IGgnQhGkK5lKfmvTE55MSekX4LMryn0nhBoiCYkzoKaDus9sH+yD2/tYSfnEehKpTdReAKHJLYRelie08XdrKQ==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=3SKoMUbW2eLvAheKEAnL7+DHjQ1AoYVvj7LHQZKt4io=;
 b=jOEGiUtOY/3+t4y0Qm9JVhsLi4xHXfWRt1EJdT4A/+DtB4tg0BcANPYiuTXpmvpsGRFcetZypyE28uqSnFxAcfX9+npN3vJEfjw2U/+HQUpbCEB8Cfa+IGlHxJIEr6FlgXYK6Vn8aPXMVK7ORTzgV+BaDfYxyrCeP7p0gnvGDHSbM2ih/wIgIQt9SOi4z4TBzxZqx6n4C2T+vJf6tom6bV2g1O+1LLV6+yLCNKDj7PoMyT30NvHJqyos7HLthLEGo0kz/FMiW6LaPUesUgbLPKOb5yraQ+UldTFQnha1WJ/Fj2Jk9qatrCejkVNHHluIDvfB1NsuNHcfZ0Gh3MjfjA==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=wdc.com; dmarc=pass action=none header.from=wdc.com; dkim=pass
 header.d=wdc.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=sharedspace.onmicrosoft.com; s=selector2-sharedspace-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=3SKoMUbW2eLvAheKEAnL7+DHjQ1AoYVvj7LHQZKt4io=;
 b=Y22+W2/lnpTaEwKHo4yWwP4bQBu2CjAFPA0xRayKnP/LqG08Sg7K/3zWorhXr+6QvNJYI2hBCPYoXeyPhTZo8oLmcKH35S7BjX135YSn2d40OrtIFPU4ZgbBnUt0yw1uWHdH4T+zMlDeA3TQwyARmUhUdKTt3oJ0pGP3VwwHu0k=
Authentication-Results: dabbelt.com; dkim=none (message not signed)
 header.d=none;dabbelt.com; dmarc=none action=none header.from=wdc.com;
Received: from DM6PR04MB6201.namprd04.prod.outlook.com (2603:10b6:5:127::32)
 by DM6PR04MB3865.namprd04.prod.outlook.com (2603:10b6:5:ac::21) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3999.28; Thu, 1 Apr
 2021 13:35:17 +0000
Received: from DM6PR04MB6201.namprd04.prod.outlook.com
 ([fe80::38c0:cc46:192b:1868]) by DM6PR04MB6201.namprd04.prod.outlook.com
 ([fe80::38c0:cc46:192b:1868%7]) with mapi id 15.20.3977.033; Thu, 1 Apr 2021
 13:35:17 +0000
From: Anup Patel <anup.patel@wdc.com>
To: Palmer Dabbelt <palmer@dabbelt.com>,
        Palmer Dabbelt <palmerdabbelt@google.com>,
        Paul Walmsley <paul.walmsley@sifive.com>,
        Albert Ou <aou@eecs.berkeley.edu>,
        Paolo Bonzini <pbonzini@redhat.com>
Cc: Alexander Graf <graf@amazon.com>,
        Atish Patra <atish.patra@wdc.com>,
        Alistair Francis <Alistair.Francis@wdc.com>,
        Damien Le Moal <damien.lemoal@wdc.com>,
        Anup Patel <anup@brainfault.org>, kvm@vger.kernel.org,
        kvm-riscv@lists.infradead.org, linux-riscv@lists.infradead.org,
        linux-kernel@vger.kernel.org, Anup Patel <anup.patel@wdc.com>
Subject: [PATCH v17 00/17] KVM RISC-V Support
Date: Thu,  1 Apr 2021 19:04:18 +0530
Message-Id: <20210401133435.383959-1-anup.patel@wdc.com>
X-Mailer: git-send-email 2.25.1
X-Originating-IP: [122.179.112.210]
X-ClientProxiedBy: MA1PR01CA0104.INDPRD01.PROD.OUTLOOK.COM
 (2603:1096:a00:1::20) To DM6PR04MB6201.namprd04.prod.outlook.com
 (2603:10b6:5:127::32)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from wdc.com (122.179.112.210) by
 MA1PR01CA0104.INDPRD01.PROD.OUTLOOK.COM (2603:1096:a00:1::20) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3999.28 via Frontend
 Transport; Thu, 1 Apr 2021 13:35:01 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: b6a41bcf-24ac-46f8-a477-08d8f512fcd4
X-MS-TrafficTypeDiagnostic: DM6PR04MB3865:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM6PR04MB3865269520B5442895B077108D7B9@DM6PR04MB3865.namprd04.prod.outlook.com>
WDCIPOUTBOUND: EOP-TRUE
X-MS-Oob-TLC-OOBClassifiers: OLM:79;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 y8KUloPqvd76dcFuZKBZoPw9H8ICb5mZp8zTDMPwN7M57SE+02D3kdB6o+KAPFv0Bi0A2/+aInMTL2FQK0eYRWdjy93VZlB241cd36Ly3I8noANSWa73UMig6boWGAibC1px5cRust4bsVxZNBsgPRgI1+OfA8nh1r+cWmjS6fL9eXv8VsBglF9bp+kpoHFSARtybyQqyOj0miroofUrX26JS2gOtm0a4FuyqyzPrDlkkQgOoKnP3gIQ3my1BNr80ndkScG+1AcO3NM/pq4fsfKrn+6A0VZLQTcQ6VmK7m/sdq2NJ5vRsvZT3xJAm+Vz/0RyhQaF6WM2NCQI8peze4xNgc/z/VULL7JmwF0a1/ZcOrVh0lIhzHo4cSZeLGfSbvPkFuQBc4pk9rluBD4/Ix87htrs+Es/gFUF5ylBLTD1K0fCVOv8pfYMs/x9X9HlKJ+Mqa8D1WgMTGE2xpBqO2PnELguXlIF0aM/VAkBv4CdISVd8mxhgL7FJQDZgzNEyZcITTwmWUZ1+Wx6VZa0liyYl+bnI0yE4OOdSwl3CvT7RVJ50KGCYsbigGMjs08njSc0TVNtB1HnmApvV71cocwCumCR3MdSKfVeJ6/Xy/pgALmWoqPTupZfEUAj5CFKXASL37D6mqaDit/Jik9YfL79TW1aagV0n1j4FmbJ3crYGGuJ3CoYAffZDQCT83ep5xNoIyW9iO3eyAPf3i1TbctjaS/Gzjk9bwg7ED2HZLqlaKKuJ80OpDxg0YvCLsuPs4eUhCLrMddJmvf+aZCYeQ==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM6PR04MB6201.namprd04.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(346002)(396003)(136003)(376002)(366004)(39860400002)(6666004)(36756003)(55016002)(26005)(2906002)(30864003)(83380400001)(966005)(66556008)(66476007)(5660300002)(66946007)(7416002)(186003)(16526019)(7696005)(956004)(2616005)(8886007)(38100700001)(8936002)(52116002)(44832011)(54906003)(110136005)(8676002)(316002)(86362001)(4326008)(1076003)(478600001)(42580500001);DIR:OUT;SFP:1102;
X-MS-Exchange-AntiSpam-MessageData: 
 CjochSdHlIpFtoqpFPCuQpY4wHKzW6I4TrAz9EYaXXcdfEltT5pNbdBcPZIp4JtOpeTGGPJa9lDSzmykNwbJAJohR8STx9xTrR7nBW9OuLd4h9eF5+tWmz5vpOHEmTLLMXJ4ZFHoI4VlyER1VWbt1eH+hgdXxYNlwv+L/S8uJoNKaRMeRdXrUUlbUGFuUMzHkkI8c+PJMy/hEEpdJpoEby2HmdabPESApABnCjoN0mtnnNlg9chxLkxerXu88c0gMG4BTZNN+WvHYfCN3D92SwksRD7JrDSS0DPI6CVW+KTHvNBFQHqIgDPJKiP6NKHGcyCP4FYeHCfNxtym5q8cHA7eYmpjukbUchIFpN+V+R0uRr+kSlCMVFgR4odK7CDVj9PHZXf3QoOueTpqfG7DUoaNyY6phIAwwryIppZPPf8126HigqCJHYWxSS1pm6nHU4tsM1YSBOMQELfg0f1QukCGxIW54DjImBhNAAv/KJVlwN+Lg53a1f0vTafHX03FEpK6GT8i2utD7j/Hei3Kmim2X0lGLDnKK2HiaMhq5L89ouQgG/qobrkuw+EwgaM+gvNrXHEtFiRjyIdiPx/Leys/n7a+f1hNzGXdxN23svy77m+e5A2HoP8gA8IokCwiz0b55pAfQP1Xg2zDTjZ+B9coI4CmdF6EkYMeuG6QE9TPfKB10YiUZGpQxa5vOczkf+FEqrTjWmR0k2gGudxT5SERFJGJKBTm+Su4YHP4YFZfHfnr2qJe7CC8Pn/tS7tFi+4+RzrDbL4zbUMXKEuh3CA/2OScWXCi6MBYtiokVpVHkzPhKIYIsEHuTQpI3IvEitUdFmX4NlmrMAprpVUlizu5cMfIk/O3eJT4BjYT549t0Sp8PeMiGc82cGxD6AnvuVZwQLJ1sNr762IXDC6hr79I5zmtNFXp7hP2Q3xliec3kLS6IzB2LkyNk1eiCbWT7dusvP+K/tDT6mY8jq1PiTx1cNv4f1UYWfs1/seHK8+BWq0kgX1shL77MXNC5tNs0sae+6I98t8+5vtp3m4r0tfbFt/0lcvmj30MVVvFMUR/YTZBHA++TxklgoWqoAjgbxKs6ALEMHKgHFNKo1YHRNJiFMoTEnyBaOUR2o2ZDNyGCP3RbSoLvZKUIQr7cKAC+2ON0KhBn4xnGlHk1TP0fYN+Se3gq0DsgHA+hZRui7b42Tm9rD7wM1Ycak972lUzwVNTHQmumkl81s9mhT2lV/2I/t4apKVXfHjqm0rjpgfwxo26v6ljpi6Iw3XiHmhTgWgNHA32GVxY2pA3x/4eU52n2xHavNqknXMR/FQZSWXdiJnCIjfxj6/DLiHyKPwF
X-OriginatorOrg: wdc.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 b6a41bcf-24ac-46f8-a477-08d8f512fcd4
X-MS-Exchange-CrossTenant-AuthSource: DM6PR04MB6201.namprd04.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 01 Apr 2021 13:35:17.5873
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: b61c8803-16f3-4c35-9b17-6f65f441df86
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 XdMrA52+3+nnhc1911yPSlcmgit75E4F6Lz78qEFlxHWpJJkwLAsnHxLka8yvanJSzNAE4pk8s47Zlw+WEVH3A==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6PR04MB3865
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series adds initial KVM RISC-V support. Currently, we are able to boot
Linux on RV64/RV32 Guest with multiple VCPUs.

Key aspects of KVM RISC-V added by this series are:
1. No RISC-V specific KVM IOCTL
2. Minimal possible KVM world-switch which touches only GPRs and few CSRs
3. Both RV64 and RV32 host supported
4. Full Guest/VM switch is done via vcpu_get/vcpu_put infrastructure
5. KVM ONE_REG interface for VCPU register access from user-space
6. PLIC emulation is done in user-space
7. Timer and IPI emuation is done in-kernel
8. Both Sv39x4 and Sv48x4 supported for RV64 host
9. MMU notifiers supported
10. Generic dirtylog supported
11. FP lazy save/restore supported
12. SBI v0.1 emulation for KVM Guest available
13. Forward unhandled SBI calls to KVM userspace
14. Hugepage support for Guest/VM
15. IOEVENTFD support for Vhost

Here's a brief TODO list which we will work upon after this series:
1. SBI v0.2 emulation in-kernel
2. SBI v0.2 hart state management emulation in-kernel
3. In-kernel PLIC emulation
4. ..... and more .....

This series can be found in riscv_kvm_v17 branch at:
https//github.com/avpatel/linux.git

Our work-in-progress KVMTOOL RISC-V port can be found in riscv_v7 branch
at: https//github.com/avpatel/kvmtool.git

The QEMU RISC-V hypervisor emulation is done by Alistair and is available
in master branch at: https://git.qemu.org/git/qemu.git

To play around with KVM RISC-V, refer KVM RISC-V wiki at:
https://github.com/kvm-riscv/howto/wiki
https://github.com/kvm-riscv/howto/wiki/KVM-RISCV64-on-QEMU
https://github.com/kvm-riscv/howto/wiki/KVM-RISCV64-on-Spike

Changes since v16:
 - Rebased on Linux-5.12-rc5
 - Remove redundant kvm_arch_create_memslot(), kvm_arch_vcpu_setup(),
   kvm_arch_vcpu_init(), kvm_arch_has_vcpu_debugfs(), and
   kvm_arch_create_vcpu_debugfs() from PATCH5
 - Make stage2_wp_memory_region() and stage2_ioremap() as static
   in PATCH13

Changes since v15:
 - Rebased on Linux-5.11-rc3
 - Fixed kvm_stage2_map() to use gfn_to_pfn_prot() for determing
   writeability of a host pfn.
 - Use "__u64" in-place of "u64" and "__u32" in-place of "u32" for
   uapi/asm/kvm.h

Changes since v14:
 - Rebased on Linux-5.10-rc3
 - Fixed Stage2 (G-stage) PDG allocation to ensure it is 16KB aligned

Changes since v13:
 - Rebased on Linux-5.9-rc3
 - Fixed kvm_riscv_vcpu_set_reg_csr() for SIP updation in PATCH5
 - Fixed instruction length computation in PATCH7
 - Added ioeventfd support in PATCH7
 - Ensure HSTATUS.SPVP is set to correct value before using HLV/HSV
   intructions in PATCH7
 - Fixed stage2_map_page() to set PTE 'A' and 'D' bits correctly
   in PATCH10
 - Added stage2 dirty page logging in PATCH10
 - Allow KVM user-space to SET/GET SCOUNTER CSR in PATCH5
 - Save/restore SCOUNTEREN in PATCH6
 - Reduced quite a few instructions for __kvm_riscv_switch_to() by
   using CSR swap instruction in PATCH6
 - Detect and use Sv48x4 when available in PATCH10

Changes since v12:
 - Rebased patches on Linux-5.8-rc4
 - By default enable all counters in HCOUNTEREN
 - RISC-V H-Extension v0.6.1 spec support

Changes since v11:
 - Rebased patches on Linux-5.7-rc3
 - Fixed typo in typecast of stage2_map_size define
 - Introduced struct kvm_cpu_trap to represent trap details and
   use it as function parameter wherever applicable
 - Pass memslot to kvm_riscv_stage2_map() for supporing dirty page
   logging in future
 - RISC-V H-Extension v0.6 spec support
 - Send-out first three patches as separate series so that it can
   be taken by Palmer for Linux RISC-V

Changes since v10:
 - Rebased patches on Linux-5.6-rc5
 - Reduce RISCV_ISA_EXT_MAX from 256 to 64
 - Separate PATCH for removing N-extension related defines
 - Added comments as requested by Palmer
 - Fixed HIDELEG CSR programming

Changes since v9:
 - Rebased patches on Linux-5.5-rc3
 - Squash PATCH19 and PATCH20 into PATCH5
 - Squash PATCH18 into PATCH11
 - Squash PATCH17 into PATCH16
 - Added ONE_REG interface for VCPU timer in PATCH13
 - Use HTIMEDELTA for VCPU timer in PATCH13
 - Updated KVM RISC-V mailing list in MAINTAINERS entry
 - Update KVM kconfig option to depend on RISCV_SBI and MMU
 - Check for SBI v0.2 and SBI v0.2 RFENCE extension at boot-time
 - Use SBI v0.2 RFENCE extension in VMID implementation
 - Use SBI v0.2 RFENCE extension in Stage2 MMU implementation
 - Use SBI v0.2 RFENCE extension in SBI implementation
 - Moved to RISC-V Hypervisor v0.5 draft spec
 - Updated Documentation/virt/kvm/api.txt for timer ONE_REG interface

Changes since v8:
 - Rebased series on Linux-5.4-rc3 and Atish's SBI v0.2 patches
 - Use HRTIMER_MODE_REL instead of HRTIMER_MODE_ABS in timer emulation
 - Fixed kvm_riscv_stage2_map() to handle hugepages
 - Added patch to forward unhandled SBI calls to user-space
 - Added patch for iterative/recursive stage2 page table programming
 - Added patch to remove per-CPU vsip_shadow variable
 - Added patch to fix race-condition in kvm_riscv_vcpu_sync_interrupts()

Changes since v7:
 - Rebased series on Linux-5.4-rc1 and Atish's SBI v0.2 patches
 - Removed PATCH1, PATCH3, and PATCH20 because these already merged
 - Use kernel doc style comments for ISA bitmap functions
 - Don't parse X, Y, and Z extension in riscv_fill_hwcap() because it will
   be added in-future
 - Mark KVM RISC-V kconfig option as EXPERIMENTAL
 - Typo fix in commit description of PATCH6 of v7 series
 - Use separate structs for CORE and CSR registers of ONE_REG interface
 - Explicitly include asm/sbi.h in kvm/vcpu_sbi.c
 - Removed implicit switch-case fall-through in kvm_riscv_vcpu_exit()
 - No need to set VSSTATUS.MXR bit in kvm_riscv_vcpu_unpriv_read()
 - Removed register for instruction length in kvm_riscv_vcpu_unpriv_read()
 - Added defines for checking/decoding instruction length
 - Added separate patch to forward unhandled SBI calls to userspace tool

Changes since v6:
 - Rebased patches on Linux-5.3-rc7
 - Added "return_handled" in struct kvm_mmio_decode to ensure that
   kvm_riscv_vcpu_mmio_return() updates SEPC only once
 - Removed trap_stval parameter from kvm_riscv_vcpu_unpriv_read()
 - Updated git repo URL in MAINTAINERS entry

Changes since v5:
 - Renamed KVM_REG_RISCV_CONFIG_TIMEBASE register to
   KVM_REG_RISCV_CONFIG_TBFREQ register in ONE_REG interface
 - Update SPEC in kvm_riscv_vcpu_mmio_return() for MMIO exits
 - Use switch case instead of illegal instruction opcode table for simplicity
 - Improve comments in stage2_remote_tlb_flush() for a potential remote TLB
  flush optimization
 - Handle all unsupported SBI calls in default case of
   kvm_riscv_vcpu_sbi_ecall() function
 - Fixed kvm_riscv_vcpu_sync_interrupts() for software interrupts
 - Improved unprivilege reads to handle traps due to Guest stage1 page table
 - Added separate patch to document RISC-V specific things in
   Documentation/virt/kvm/api.txt

Changes since v4:
 - Rebased patches on Linux-5.3-rc5
 - Added Paolo's Acked-by and Reviewed-by
 - Updated mailing list in MAINTAINERS entry

Changes since v3:
 - Moved patch for ISA bitmap from KVM prep series to this series
 - Make vsip_shadow as run-time percpu variable instead of compile-time
 - Flush Guest TLBs on all Host CPUs whenever we run-out of VMIDs

Changes since v2:
 - Removed references of KVM_REQ_IRQ_PENDING from all patches
 - Use kvm->srcu within in-kernel KVM run loop
 - Added percpu vsip_shadow to track last value programmed in VSIP CSR
 - Added comments about irqs_pending and irqs_pending_mask
 - Used kvm_arch_vcpu_runnable() in-place-of kvm_riscv_vcpu_has_interrupt()
   in system_opcode_insn()
 - Removed unwanted smp_wmb() in kvm_riscv_stage2_vmid_update()
 - Use kvm_flush_remote_tlbs() in kvm_riscv_stage2_vmid_update()
 - Use READ_ONCE() in kvm_riscv_stage2_update_hgatp() for vmid

Changes since v1:
 - Fixed compile errors in building KVM RISC-V as module
 - Removed unused kvm_riscv_halt_guest() and kvm_riscv_resume_guest()
 - Set KVM_CAP_SYNC_MMU capability only after MMU notifiers are implemented
 - Made vmid_version as unsigned long instead of atomic
 - Renamed KVM_REQ_UPDATE_PGTBL to KVM_REQ_UPDATE_HGATP
 - Renamed kvm_riscv_stage2_update_pgtbl() to kvm_riscv_stage2_update_hgatp()
 - Configure HIDELEG and HEDELEG in kvm_arch_hardware_enable()
 - Updated ONE_REG interface for CSR access to user-space
 - Removed irqs_pending_lock and use atomic bitops instead
 - Added separate patch for FP ONE_REG interface
 - Added separate patch for updating MAINTAINERS file

Anup Patel (13):
  RISC-V: Add hypervisor extension related CSR defines
  RISC-V: Add initial skeletal KVM support
  RISC-V: KVM: Implement VCPU create, init and destroy functions
  RISC-V: KVM: Implement VCPU interrupts and requests handling
  RISC-V: KVM: Implement KVM_GET_ONE_REG/KVM_SET_ONE_REG ioctls
  RISC-V: KVM: Implement VCPU world-switch
  RISC-V: KVM: Handle MMIO exits for VCPU
  RISC-V: KVM: Handle WFI exits for VCPU
  RISC-V: KVM: Implement VMID allocator
  RISC-V: KVM: Implement stage2 page table programming
  RISC-V: KVM: Implement MMU notifiers
  RISC-V: KVM: Document RISC-V specific parts of KVM API
  RISC-V: KVM: Add MAINTAINERS entry

Atish Patra (4):
  RISC-V: KVM: Add timer functionality
  RISC-V: KVM: FP lazy save/restore
  RISC-V: KVM: Implement ONE REG interface for FP registers
  RISC-V: KVM: Add SBI v0.1 support

 Documentation/virt/kvm/api.rst          | 193 ++++-
 MAINTAINERS                             |  11 +
 arch/riscv/Kconfig                      |   1 +
 arch/riscv/Makefile                     |   2 +
 arch/riscv/include/asm/csr.h            |  89 +++
 arch/riscv/include/asm/kvm_host.h       | 277 +++++++
 arch/riscv/include/asm/kvm_types.h      |   7 +
 arch/riscv/include/asm/kvm_vcpu_timer.h |  44 ++
 arch/riscv/include/asm/pgtable-bits.h   |   1 +
 arch/riscv/include/uapi/asm/kvm.h       | 128 +++
 arch/riscv/kernel/asm-offsets.c         | 156 ++++
 arch/riscv/kvm/Kconfig                  |  36 +
 arch/riscv/kvm/Makefile                 |  15 +
 arch/riscv/kvm/main.c                   | 118 +++
 arch/riscv/kvm/mmu.c                    | 854 ++++++++++++++++++++
 arch/riscv/kvm/tlb.S                    |  74 ++
 arch/riscv/kvm/vcpu.c                   | 997 ++++++++++++++++++++++++
 arch/riscv/kvm/vcpu_exit.c              | 701 +++++++++++++++++
 arch/riscv/kvm/vcpu_sbi.c               | 173 ++++
 arch/riscv/kvm/vcpu_switch.S            | 400 ++++++++++
 arch/riscv/kvm/vcpu_timer.c             | 225 ++++++
 arch/riscv/kvm/vm.c                     |  81 ++
 arch/riscv/kvm/vmid.c                   | 120 +++
 drivers/clocksource/timer-riscv.c       |   8 +
 include/clocksource/timer-riscv.h       |  16 +
 include/uapi/linux/kvm.h                |   8 +
 26 files changed, 4726 insertions(+), 9 deletions(-)
 create mode 100644 arch/riscv/include/asm/kvm_host.h
 create mode 100644 arch/riscv/include/asm/kvm_types.h
 create mode 100644 arch/riscv/include/asm/kvm_vcpu_timer.h
 create mode 100644 arch/riscv/include/uapi/asm/kvm.h
 create mode 100644 arch/riscv/kvm/Kconfig
 create mode 100644 arch/riscv/kvm/Makefile
 create mode 100644 arch/riscv/kvm/main.c
 create mode 100644 arch/riscv/kvm/mmu.c
 create mode 100644 arch/riscv/kvm/tlb.S
 create mode 100644 arch/riscv/kvm/vcpu.c
 create mode 100644 arch/riscv/kvm/vcpu_exit.c
 create mode 100644 arch/riscv/kvm/vcpu_sbi.c
 create mode 100644 arch/riscv/kvm/vcpu_switch.S
 create mode 100644 arch/riscv/kvm/vcpu_timer.c
 create mode 100644 arch/riscv/kvm/vm.c
 create mode 100644 arch/riscv/kvm/vmid.c
 create mode 100644 include/clocksource/timer-riscv.h
```
#### [PATCH v7 0/8] KVMTOOL RISC-V Support
##### From: Anup Patel <anup.patel@wdc.com>

```c
From patchwork Thu Apr  1 13:40:48 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Anup Patel <Anup.Patel@wdc.com>
X-Patchwork-Id: 12178961
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 284FCC43619
	for <kvm@archiver.kernel.org>; Thu,  1 Apr 2021 18:06:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 087C261001
	for <kvm@archiver.kernel.org>; Thu,  1 Apr 2021 18:06:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234629AbhDASGx (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 1 Apr 2021 14:06:53 -0400
Received: from esa5.hgst.iphmx.com ([216.71.153.144]:55859 "EHLO
        esa5.hgst.iphmx.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S235005AbhDASBa (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 1 Apr 2021 14:01:30 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=simple/simple;
  d=wdc.com; i=@wdc.com; q=dns/txt; s=dkim.wdc.com;
  t=1617300091; x=1648836091;
  h=from:to:cc:subject:date:message-id:
   content-transfer-encoding:mime-version;
  bh=lt/QKwJXcapmTqSI3EiGaC1bAYetQ+QNn0vvxI4oqIw=;
  b=hOC1QGQk2o7DOl8Q1Dv6QzVBDZtO3cF09xvgQoQqxCRPZuYXMnnhNRzK
   E5pFkTjXrZVBQHg8TqM+AApGz5YDovXEMQDizNYEPk7MqsDeDlKtwRJSo
   9FRj+oBg0go+IEjnrso/aifjF9Bwdiqk0YcfOAl13Tbhu8qZQtsr92eqb
   RkUw6lfxdckpBAJUG0HeVQPmKkLsHKaB8Bp1BDZJHvkhqXllGo+6rXdIY
   EXdx+mpqI9Ef8zpLXWfsKkWKxkdWNGKI8lsN78Y4/b7uh9ii297HDhYyS
   xijXcn+iid3g0F8VGAmR9+LhR/1Akhd4L/C9ZdMBc6T3z6lDvLKp+amOy
   g==;
IronPort-SDR: 
 CaevHoNgyVTILvEs8uUmlqPKP+daE+VNMN4+IwbpbnTN1vnP+5cWoG/gbLSqaFmsoC0fZfZfmz
 8rZ9H8uij5aGbSEUa8u+2N1jNHnmHYfWnDDDh3E7gsfaA+TeiYZu7XZ63RKZWONiD8V89LsUj2
 euWV5ZzE8JDc8NH/wtcFhl7UDh9BGZMkxZzuqdWmOYypDyFgaeRp+FIqIjUQ1/HsCNo1DoQwPi
 daNf2h2Gy/35SlLNmWnfw4xZDtZjNQjxtsfIWPmcBGajqWinR4DWzwsVaZXQ00vquW0inT6mmR
 izY=
X-IronPort-AV: E=Sophos;i="5.81,296,1610380800";
   d="scan'208";a="163561419"
Received: from mail-bn8nam11lp2174.outbound.protection.outlook.com (HELO
 NAM11-BN8-obe.outbound.protection.outlook.com) ([104.47.58.174])
  by ob1.hgst.iphmx.com with ESMTP; 01 Apr 2021 21:41:41 +0800
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=VvxljKXgwRa4upl6RYZNPP6CmDYnZluKiLonzdknJbBO6H2AbY/rUOvInveoQjm+yIxAR9IzLNsoM/5OyvKHQ2UbYLHSzN4MZyZt5ZgditMwnWudLzBAsBoqS+OaBtlt39qwJL8G3T6+rymjwL4LGquspePlllK3u7XaT/uz2+926cVVHFq1yGa4aWxAEhc3Y+qv2xVDKlqZoXkNHxqwcT5abPwq1cS14mScIg4090JhDATsZUgYXIma6Ka2l1L2Q33rzl5f9uiCQeBcWd9Owe6FGFk/I/2C6SC4ALo/5fN3iKYt69jJzfTNXE3WCslCquQep3XyQ8coc+RJ3dUxwg==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=JVONtn7CY6bJufBTlSVyRiQgxQc9dDvTi0cfyuI8f+o=;
 b=Yx3L4ASrU+9I+CuOkZXwbG0RGfH7+u+ctzhgSaaDKe5Eu8y89ZoO/iYpyHtQVJqhrTak2h8/pv9HKFxvymVD4PHfgAYcsES/t5M7k1GpvCwbE1k/cDzrWdgi3KQ2rVDvMcI4fj8Z74XsuIZ46xekLV7kmJcmeafbciTCBrLDZdtwGmU1DHv2uTG83ezGDBvOmWchNuoKJgVBTYYe5OCay2qgsZnG7tf5fHB27bnQIgiiKSxSiCqF1ruyQD0EV3FFXgFyH3IxEua0qk+2yvW9wps+qunPWdS1mN5vAyLGMinjPaWzzw3CI+Lhdja2M3+Gho9+p/nO7qjQf4ulOS7wFw==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=wdc.com; dmarc=pass action=none header.from=wdc.com; dkim=pass
 header.d=wdc.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=sharedspace.onmicrosoft.com; s=selector2-sharedspace-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=JVONtn7CY6bJufBTlSVyRiQgxQc9dDvTi0cfyuI8f+o=;
 b=y4N4OHk7ojSS/lRf+lCd3/ngxttZyuD5qR4GXd1R7uRlN8AxwyrXOJajZ/jNhqqIU2byCFj8D5m4/3CaY+codZJYPrfVTyADL6B+ctM+2EaSNYM2BwlRsZaxHl2DkkkilHHaT5l4w/V/94qZs7GTxcQMM07humIJehT0bJn5+vw=
Authentication-Results: kernel.org; dkim=none (message not signed)
 header.d=none;kernel.org; dmarc=none action=none header.from=wdc.com;
Received: from DM6PR04MB6201.namprd04.prod.outlook.com (2603:10b6:5:127::32)
 by DM5PR04MB0218.namprd04.prod.outlook.com (2603:10b6:3:77::8) with Microsoft
 SMTP Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.3999.27; Thu, 1 Apr 2021 13:41:40 +0000
Received: from DM6PR04MB6201.namprd04.prod.outlook.com
 ([fe80::38c0:cc46:192b:1868]) by DM6PR04MB6201.namprd04.prod.outlook.com
 ([fe80::38c0:cc46:192b:1868%7]) with mapi id 15.20.3977.033; Thu, 1 Apr 2021
 13:41:40 +0000
From: Anup Patel <anup.patel@wdc.com>
To: Will Deacon <will@kernel.org>
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Atish Patra <atish.patra@wdc.com>,
        Alistair Francis <Alistair.Francis@wdc.com>,
        Anup Patel <anup@brainfault.org>, kvm@vger.kernel.org,
        kvm-riscv@lists.infradead.org, Anup Patel <anup.patel@wdc.com>
Subject: [PATCH v7 0/8] KVMTOOL RISC-V Support
Date: Thu,  1 Apr 2021 19:10:48 +0530
Message-Id: <20210401134056.384038-1-anup.patel@wdc.com>
X-Mailer: git-send-email 2.25.1
X-Originating-IP: [122.179.112.210]
X-ClientProxiedBy: MAXPR0101CA0019.INDPRD01.PROD.OUTLOOK.COM
 (2603:1096:a00:c::29) To DM6PR04MB6201.namprd04.prod.outlook.com
 (2603:10b6:5:127::32)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from wdc.com (122.179.112.210) by
 MAXPR0101CA0019.INDPRD01.PROD.OUTLOOK.COM (2603:1096:a00:c::29) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3999.26 via Frontend
 Transport; Thu, 1 Apr 2021 13:41:24 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 05d75563-e549-4db8-82ef-08d8f513e142
X-MS-TrafficTypeDiagnostic: DM5PR04MB0218:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM5PR04MB021841C2EA105114E705EC448D7B9@DM5PR04MB0218.namprd04.prod.outlook.com>
WDCIPOUTBOUND: EOP-TRUE
X-MS-Oob-TLC-OOBClassifiers: OLM:1923;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 0gsPDX3/XDyPrD5SZZvZ/7ggDeD7m7KPwfli7dGNjRnkumvzcGych+H/UKilrA6vb1rPTU0uMtFid1kbyFQnrHVyQ0j4bVy+H9S4gO1WRH/XO5kSalYjpAi30Nx3N81cNiyBBr39ZyMY9tcMjzUPDs283hZRsuDPdp/Rtdziycfz8L4qPBWkpfTZ7r/voRberLNpLrHbgo0ounhQJCl9jU2cjyhmFi2CCR9993LBMSvwoZc6IgmwTytY0k81pf/2xcTtB/IAcDR62CMLF4GEn9xrLRBRi8PoDM9BXUnnXrS2PewodRtveICvTWLnL1CH5v3nfOW1bJTQ1chS0bHPyugcr7z+oB9klg3mRY5BXb64tZCwkrM8CTbUje5h46Wi1opebTcv34QWMMyiofsDPjgg0s9kx0gpjORuN2DjF44eq6rdwS/23DjHofXGzE8fkrPydLY0DRUCjKHp6/sUlTNh6/cqaJlqx7GH6KNxNwGOdmo5MLgML4Eaw+mNhlCfzy7M/QphFN5HIlN3jPP6VGbL2Sd+6bFtlzGaKZv5LskswMCNeIpayFBQH97+6yrXFTYVwIWeGndxsYMciL1XyFCp91GSMqG7fS4Cywh9DyDUIZPZaV3NPIvOoxa6WcV42tHCAb0tA3GyxBA/yib4+K47T3665ie3tmcWI84fAo+fo9Q5yYls3K6Dyz5mVjQqyhHYi2IGqypcBKB6S2ODeWZ2C59VDl9pOTcNKWqJLgqx0NFuIcsOID8D5tay1PfeQeSEj3+Kwo7XlQKrPT+R9Q==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM6PR04MB6201.namprd04.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(376002)(366004)(39860400002)(396003)(136003)(346002)(38100700001)(966005)(8676002)(6666004)(316002)(36756003)(8886007)(86362001)(66946007)(2906002)(186003)(16526019)(44832011)(1076003)(54906003)(2616005)(956004)(83380400001)(478600001)(66556008)(66476007)(7696005)(26005)(8936002)(5660300002)(4326008)(52116002)(55016002)(6916009)(42580500001);DIR:OUT;SFP:1102;
X-MS-Exchange-AntiSpam-MessageData: 
 QdT74QQK110ZEyNAJlksJXOpUWtPYaK2ZXLboTChKueDUa1B1/BqNiDOTvWhjrueDXzxNi14/3f4cJl3kdWbrhrYWewLFsxyt9/AOT7+l41JCw1qte0dyjP/hIrIjauYU0abY1r/QgVFvTni/nomgHB9yKFR0Z0hReR1d8TjRpUcttEdEC2t2lDzd4z2+iVVqXrNjQg6ucFUGGP0ciW4uEgJ5Hp4B/7eUcJVSFoIsn24w5JPzZkk9f+VWanx3HnMuHQHjuCseqMG3FkDBseddmLDAvVI6IEfxpVBdN3b01QvrT3oe/SDFDEN9PztR+3BR+Lupm/izyJP0h8pMD54pITPeKM90eR526Fn+6+j1GoaYozK3POabek55OBe6ogr8ASC5Ti3j4FgGoKHv2JHwftwN5ZSkhLNU11es/tV3jq3eFdcnEj4FXfQrdNB8+MOyH5OklR2jPcboPt+zg0RkjYcjX55PDN9ifX7fKi2C4wEGAkg/xu5vXyt2/+tieGcCwumfMCJibmgshNfgyLMYAPA7snN1i+LnqJxEW9HSxFnmJ1q9laX53F7Og8bw8HjG3r4NQArteDkE7RlOIYkzssmDUmzsaGFJ/Zcqth4XCmV19aIFNNtRKozp5uFBMm44t1o2wJypFdhT0vBTp2NCIZoQPR7AaGMWwmAkiQC5sEoXApVXINpW5e9KDVDtrTT6ECbl045J5AKe6za6+Ikybd+nnuQr+ZoBJx2JamoDip9rsIucIwEdMOCCIQL+6M8YrBPzv0ejG0C5JLbjkYaWXWB6z1BvQiwv/9L0aljUZytkZ4Fbvs2bYGMdgVOuCHm2E8e8/TX8FcvoYCTTOoWGMSvjMXdgpBzws/c8DRt4Orx8sgGfbDGphLd1H6JYomwsYWOJ1XiWh4jt1nlaSFMwCEdUpFGALV9ZBWvVvQnphna59TrXty+jKwaYmUQdpTGzWkfsuyII3+fsUdLRAYeQ8pJM6odSG9aEJHhov4DHFdUQ8gwnp536fl4WGMErD1YI3gvx/fd7yhNq7LMDQbEtl62gEjN+mxSrOgPpoAq5ekezzQXu58jwwpM2rAe/vAEY0vsmt5ij2CmMF5Ndem7nCu1Hk2UscbageH4BCDq7f259c8zywLi6nka8E4OqAtiID6SCfOfWW/3/QALmJHgtnlfjecp3aKscIun9TsWwTWw8LD33sRfID3sW/0mKb9eoArORn+KM0vjCXLmxOlBn2t8RVvwCSGmO5kFB0PMa84jwzmKL/VmGG29d/2l+De1QEaDLdVX2YTJFbOjzPnPOzGfuACr/4tEqtpYNL7tBgeXMxe6bCSkPJcQxrxyvtAk
X-OriginatorOrg: wdc.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 05d75563-e549-4db8-82ef-08d8f513e142
X-MS-Exchange-CrossTenant-AuthSource: DM6PR04MB6201.namprd04.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 01 Apr 2021 13:41:40.7010
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: b61c8803-16f3-4c35-9b17-6f65f441df86
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 3cSgdaRM7DogpeXOyTcyB7c1MVe+K6807vra0w/ZJvP4YLQMdQd3J54AYsqwaa52tbjGbfrdQhgRxeNOIt2Zsw==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM5PR04MB0218
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series adds RISC-V support for KVMTOOL and it is based on
the v10 of KVM RISC-V series. The KVM RISC-V patches are not yet
merged in Linux kernel but it will be good to get early review
for KVMTOOL RISC-V support.

The KVMTOOL RISC-V patches can be found in riscv_master branch at:
https//github.com/kvm-riscv/kvmtool.git

The KVM RISC-V patches can be found in riscv_kvm_master branch at:
https//github.com/kvm-riscv/linux.git

The QEMU RISC-V hypervisor emulation is done by Alistair and is
available in master branch at: https://git.qemu.org/git/qemu.git

Changes since v6:
 - Rebased on recent commit 117d64953228afa90b52f6e1b4873770643ffdc9
 - Sync-up headers with latest KVM RISC-V v17 series which is based
   on Linux-5.12-rc5

Changes since v5:
 - Sync-up headers with latest KVM RISC-V v16 series which is based
   on Linux-5.11-rc3

Changes since v4:
 - Rebased on recent commit 90b2d3adadf218dfc6bdfdfcefe269843360223c
 - Sync-up headers with latest KVM RISC-V v15 series which is based
   on Linux-5.10-rc3

Changes since v3:
 - Rebased on recent commit 351d931f496aeb2e97b8daa44c943d8b59351d07
 - Improved kvm_cpu__show_registers() implementation

Changes since v2:
 - Support compiling KVMTOOL for both RV32 and RV64 systems using
   a multilib toolchain
 - Fix kvm_cpu__arch_init() for RV32 system

Changes since v1:
 - Use linux/sizes.h in kvm/kvm-arch.h
 - Added comment in kvm/kvm-arch.h about why PCI config space is 256M
 - Remove forward declaration of "struct kvm" from kvm/kvm-cpu-arch.h
 - Fixed placement of DTB and INITRD in guest RAM
 - Use __riscv_xlen instead of sizeof(unsigned long) in __kvm_reg_id()

Anup Patel (8):
  update_headers: Sync-up ABI headers with Linux-5.12-rc5
  riscv: Initial skeletal support
  riscv: Implement Guest/VM arch functions
  riscv: Implement Guest/VM VCPU arch functions
  riscv: Add PLIC device emulation
  riscv: Generate FDT at runtime for Guest/VM
  riscv: Handle SBI calls forwarded to user space
  riscv: Generate PCI host DT node

 INSTALL                             |   7 +-
 Makefile                            |  24 +-
 arm/aarch64/include/asm/kvm.h       |  45 ++-
 include/linux/kvm.h                 | 269 ++++++++++++-
 powerpc/include/asm/kvm.h           |  10 +
 riscv/fdt.c                         | 195 ++++++++++
 riscv/include/asm/kvm.h             | 128 +++++++
 riscv/include/kvm/barrier.h         |  14 +
 riscv/include/kvm/fdt-arch.h        |   8 +
 riscv/include/kvm/kvm-arch.h        |  85 +++++
 riscv/include/kvm/kvm-config-arch.h |  15 +
 riscv/include/kvm/kvm-cpu-arch.h    |  51 +++
 riscv/include/kvm/sbi.h             |  48 +++
 riscv/ioport.c                      |   7 +
 riscv/irq.c                         |  13 +
 riscv/kvm-cpu.c                     | 490 ++++++++++++++++++++++++
 riscv/kvm.c                         | 174 +++++++++
 riscv/pci.c                         | 109 ++++++
 riscv/plic.c                        | 563 ++++++++++++++++++++++++++++
 util/update_headers.sh              |   2 +-
 x86/include/asm/kvm.h               |  44 ++-
 21 files changed, 2283 insertions(+), 18 deletions(-)
 create mode 100644 riscv/fdt.c
 create mode 100644 riscv/include/asm/kvm.h
 create mode 100644 riscv/include/kvm/barrier.h
 create mode 100644 riscv/include/kvm/fdt-arch.h
 create mode 100644 riscv/include/kvm/kvm-arch.h
 create mode 100644 riscv/include/kvm/kvm-config-arch.h
 create mode 100644 riscv/include/kvm/kvm-cpu-arch.h
 create mode 100644 riscv/include/kvm/sbi.h
 create mode 100644 riscv/ioport.c
 create mode 100644 riscv/irq.c
 create mode 100644 riscv/kvm-cpu.c
 create mode 100644 riscv/kvm.c
 create mode 100644 riscv/pci.c
 create mode 100644 riscv/plic.c
```
#### [PATCH 0/6] Introduce KVM_{GET|SET}_SREGS2 and fix PDPTR migration
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
From patchwork Thu Apr  1 14:18:08 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 12179193
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-10.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 44724C43461
	for <kvm@archiver.kernel.org>; Thu,  1 Apr 2021 18:23:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1CAA4601FC
	for <kvm@archiver.kernel.org>; Thu,  1 Apr 2021 18:23:46 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234915AbhDASXl (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 1 Apr 2021 14:23:41 -0400
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:37281 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S235296AbhDASVD (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 1 Apr 2021 14:21:03 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1617301262;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=Gy/ng5zCwEi0kvaEHLz2eineziKHWcaMJpVr9bUxhnU=;
        b=eVbfKshU0rpWhdVZISL+3gKcPPe2dx13MEssTleOKUce4PvALxlsUje8ppFQOOpgjg6QPq
        uWgTHCR2w9j/BP28yGgsrQjqRHFePTQ0gcE+BsWyrDXNd2dnY+JiWb4PkxVGfUfrMQ13x+
        lFe5teYzKZrUOMTpY9KPqIW9txVZX4Q=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-390-o6gNyiRcMtqFtV05SKEVdg-1; Thu, 01 Apr 2021 10:19:01 -0400
X-MC-Unique: o6gNyiRcMtqFtV05SKEVdg-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 17C831853032;
        Thu,  1 Apr 2021 14:18:20 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.206.58])
        by smtp.corp.redhat.com (Postfix) with ESMTP id EC2AA6F7EA;
        Thu,  1 Apr 2021 14:18:15 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: x86@kernel.org (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT)),
        Jim Mattson <jmattson@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Sean Christopherson <seanjc@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        "H. Peter Anvin" <hpa@zytor.com>,
        linux-kernel@vger.kernel.org (open list:X86 ARCHITECTURE (32-BIT AND
        64-BIT)), Paolo Bonzini <pbonzini@redhat.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Jonathan Corbet <corbet@lwn.net>,
        Borislav Petkov <bp@alien8.de>, Ingo Molnar <mingo@redhat.com>,
        linux-doc@vger.kernel.org (open list:DOCUMENTATION),
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH 0/6] Introduce KVM_{GET|SET}_SREGS2 and fix PDPTR migration
Date: Thu,  1 Apr 2021 17:18:08 +0300
Message-Id: <20210401141814.1029036-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch set aims to fix few flaws that were discovered
in KVM_{GET|SET}_SREGS on x86:

* There is no support for reading/writing PDPTRs although
  these are considered to be part of the guest state.

* There is useless interrupt bitmap which isn't needed

* No support for future extensions (via flags and such)

Final two patches in this patch series allow to
correctly migrate PDPTRs when new API is used.

This patch series was tested by doing nested migration test
of 32 bit PAE L1 + 32 bit PAE L2 on AMD and Intel and by
nested migration test of 64 bit L1 + 32 bit PAE L2 on AMD.
The later test currently fails on Intel (regardless of my patches).

Finally patch 2 in this patch series fixes a rare L0 kernel oops,
which I can trigger by migrating a hyper-v machine.

Best regards,
	Maxim Levitskky

Maxim Levitsky (6):
  KVM: nVMX: delay loading of PDPTRs to KVM_REQ_GET_NESTED_STATE_PAGES
  KVM: nSVM: call nested_svm_load_cr3 on nested state load
  KVM: x86: introduce kvm_register_clear_available
  KVM: x86: Introduce KVM_GET_SREGS2 / KVM_SET_SREGS2
  KVM: nSVM: avoid loading PDPTRs after migration when possible
  KVM: nVMX: avoid loading PDPTRs after migration when possible

 Documentation/virt/kvm/api.rst  |  43 ++++++++++
 arch/x86/include/asm/kvm_host.h |   7 ++
 arch/x86/include/uapi/asm/kvm.h |  13 +++
 arch/x86/kvm/kvm_cache_regs.h   |  12 +++
 arch/x86/kvm/svm/nested.c       |  55 ++++++++-----
 arch/x86/kvm/svm/svm.c          |   6 +-
 arch/x86/kvm/vmx/nested.c       |  26 ++++--
 arch/x86/kvm/x86.c              | 136 ++++++++++++++++++++++++++------
 include/uapi/linux/kvm.h        |   5 ++
 9 files changed, 249 insertions(+), 54 deletions(-)
```
#### [PATCH 0/5 v5] KVM: nSVM: Check addresses of MSR bitmap and IO bitmap
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
From patchwork Thu Apr  1 19:20:28 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 12179423
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 55693C433ED
	for <kvm@archiver.kernel.org>; Thu,  1 Apr 2021 20:09:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2EE92610E5
	for <kvm@archiver.kernel.org>; Thu,  1 Apr 2021 20:09:26 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S235431AbhDAUJZ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 1 Apr 2021 16:09:25 -0400
Received: from aserp2120.oracle.com ([141.146.126.78]:39114 "EHLO
        aserp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S235441AbhDAUJY (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 1 Apr 2021 16:09:24 -0400
Received: from pps.filterd (aserp2120.oracle.com [127.0.0.1])
        by aserp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 131K3uBO169124;
        Thu, 1 Apr 2021 20:09:21 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : content-transfer-encoding : content-type :
 mime-version; s=corp-2020-01-29;
 bh=uWERgh9ZNrR2nUt3jUJqojV2/ReFRZpkHTfavMn0fSM=;
 b=Kk9Mf988zzoTK82TbD/78PU/NUiedVZrJxIxqW1snwS4k9NQdWO2RfsF7bfmYoqjWKYm
 hiYWEbMd+oZQAAMA1lq5ip5lHbWMnDwUbLrjjKtEtK8nRGtzaitD3WGz24FkZzaqAGkX
 fFHkGwlGuM7nW3WPayKQheuD/g6tgHyWpnMu2lNG05ID+FUxvxFs01N5VLpxEjArn13v
 uXrUyKmac1wy7PEOfVHdiIFQ87je6PIq0A3/by8tduy7Ujt48Qq3q9AI9ro36Xh5G15E
 0bdqZd4t0QqsOlEVCmnQ2htWkrBxCstRm5X+3qbJYHn0/N+YssRGaad8sag7JtfIj+gC 6A==
Received: from userp3020.oracle.com (userp3020.oracle.com [156.151.31.79])
        by aserp2120.oracle.com with ESMTP id 37n2akk3bn-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 01 Apr 2021 20:09:21 +0000
Received: from pps.filterd (userp3020.oracle.com [127.0.0.1])
        by userp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 131K0kXc043054;
        Thu, 1 Apr 2021 20:09:20 GMT
Received: from nam04-co1-obe.outbound.protection.outlook.com
 (mail-co1nam04lp2057.outbound.protection.outlook.com [104.47.45.57])
        by userp3020.oracle.com with ESMTP id 37n2pb03xp-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 01 Apr 2021 20:09:20 +0000
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=nprB4sMlF8ElKqXMVmf8wqwYcwZKcq4xgXE1sax34TkY9CKwolbco12R3tRQsIUU3yYp0AGHzlLDCSbWhpm4Jf/AKTWIBPPac8UorKK1UdweqhrwfBc17fJR34swuhpsucBh/9tcAGan2Iaq73quKtvUTmzZmjNuZVomzHcB1S6pTcobgthUO3Jo5R8ltYtfMQ1o2TfsrpTL1diqv7NvkBkJGmAxoCN5auHkQLTuJy/AXISQu9Y/KTCCar1qZH4MUvCgz1+WEfjmsTo+l1d3kHBr6u0ijz9HerC+vsXDofv36Fl8gCDmMoSQKFXe5WcLxA/P8kbm7qO2uKC9T2h8ww==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=uWERgh9ZNrR2nUt3jUJqojV2/ReFRZpkHTfavMn0fSM=;
 b=MWhd1OAROeX15tue6q0TNULAiN0ntFSrtZgbpRFZlcSm1pjXSQ6+YC0hZBZoP2h2//L3nM8hfUa7BTilcfVq+8M+7k0HRgY1olFdrLI5M9l5jtqMeCl83Wn/u6eoSezGLNpf7r0uT5IOJLbBw7RmoY0IS0lnp4Idj5U527xxBYRO2UgqEgMn5mCx+cNaYftPEZWK0rO6J9M+ofarG0Cf64RpCHAf/pif64jvmrhB5f3IusVR+o6z3AtRlqDzhM4Yo9AXXpQ93tdjc6yjc/Zie7fLOet3CLp/U2/1JhTAwOMXA6KPMFOKUB22bGG9LF0L7doirfQZ7w4LgQtxSgiltQ==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=oracle.com; dmarc=pass action=none header.from=oracle.com;
 dkim=pass header.d=oracle.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=oracle.onmicrosoft.com; s=selector2-oracle-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=uWERgh9ZNrR2nUt3jUJqojV2/ReFRZpkHTfavMn0fSM=;
 b=NxZ5D4uFWpI3x0Sc3d5/A6mZvYs0qmfeg13SINoQoJVnjDGZSE6TisCDhltDN5rNmRIxuIXn5z+Jnlt8r1DODfbpWOvTniZR0uOYIaV5htHIey1rTMDhuOq5Ebl3DcksE4QrK2USMfRL8DKUXwlWlKkvbwUDLeXeFKltDDA4PdM=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=oracle.com;
Received: from DM6PR10MB3019.namprd10.prod.outlook.com (2603:10b6:5:6f::23) by
 DM5PR1001MB2091.namprd10.prod.outlook.com (2603:10b6:4:2c::21) with Microsoft
 SMTP Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.3977.33; Thu, 1 Apr 2021 20:09:19 +0000
Received: from DM6PR10MB3019.namprd10.prod.outlook.com
 ([fe80::35bb:f60f:d7e1:7b2b]) by DM6PR10MB3019.namprd10.prod.outlook.com
 ([fe80::35bb:f60f:d7e1:7b2b%3]) with mapi id 15.20.3977.033; Thu, 1 Apr 2021
 20:09:19 +0000
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com, seanjc@google.com
Subject: [PATCH 0/5 v5] KVM: nSVM: Check addresses of MSR bitmap and IO bitmap
 tables on vmrun of nested guests
Date: Thu,  1 Apr 2021 15:20:28 -0400
Message-Id: <20210401192033.91150-1-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.25.4
X-Originating-IP: [138.3.201.29]
X-ClientProxiedBy: BYAPR21CA0015.namprd21.prod.outlook.com
 (2603:10b6:a03:114::25) To DM6PR10MB3019.namprd10.prod.outlook.com
 (2603:10b6:5:6f::23)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from ban25x6uut29.us.oracle.com (138.3.201.29) by
 BYAPR21CA0015.namprd21.prod.outlook.com (2603:10b6:a03:114::25) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4020.0 via Frontend
 Transport; Thu, 1 Apr 2021 20:09:17 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 9f5fb2c8-f738-4f3d-82e1-08d8f54a082f
X-MS-TrafficTypeDiagnostic: DM5PR1001MB2091:
X-Microsoft-Antispam-PRVS: 
 <DM5PR1001MB2091CC8636882B46BE25162E817B9@DM5PR1001MB2091.namprd10.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:6790;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 SXmi+EigRlLkFSUi84dj+8oTB6yONzaxXe6O5c+wBGS3lLsdVo/i9xaDpeZA9u5rJv0406Q71WPlzIWHUXL3g1pwS22SmJmMEaVJWlcG3apJy6a2mdgITOmZFXzuGpKed4jHGSWqFniMxGpjgqbcn/5jAny3fSZkGeKJa5zcjd+AeiBSaJUEMI19Ut2cT3Tv0ekxpbAdRs8uCzgr0KL1tkTmvXP/zW6uOQ98siXoKk/sN5EWa6TqqUEHk1oUAD0PiszvUzyppmI7X1BUkB2OjcEjBYhMJ5o1I/WqjUWio5VL3I5aMSSSlZ1nTBElynkIEnnU5MRWppThOPFGcRki5Q3qYATtXgK3biHwQwP6kHiSWkAHBLeglAGQRacjaqraqIxIxy3/vWhIVFQM/MyhFNhFZh6dtDa6TF6bX9PXNyr4jt24QByGDhYHirDJlZpxXr8Xz+IyjFkNbW82qa1JDW0l7/QYlXNVTNfTkxDK14EgUHMZnWOhrfjNOjY/fB/tvTd8Y9zb17ZueTwcqX+0/9n58CpDlG1kyqy1aEWhep+WOmcwpJM1C4Wlld6m4TU4OZJdn2a/qhFo+ccdUXTrNCavCFXZCSUvuBBt2gq2Gco63N7chYGMrdPamoPgwC6JCe2SsQIo/FnnOzoHCF8goA==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM6PR10MB3019.namprd10.prod.outlook.com;PTR:;CAT:NONE;SFS:(376002)(136003)(346002)(366004)(39860400002)(396003)(66476007)(86362001)(2616005)(66946007)(4326008)(2906002)(186003)(6486002)(6666004)(36756003)(316002)(38100700001)(8936002)(7696005)(478600001)(5660300002)(8676002)(16526019)(66556008)(83380400001)(6916009)(44832011)(956004)(26005)(1076003)(52116002);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 qMi7geoCQMtIYajGiPmKYZzM+La12VJt3ZJRRoI1FXcHrO/cb6AnIa1/GWdQgTKaNCu8n2aYv+71IE9P2TJLwo/CiTyl2FxVnl8q+gcwF8hbg5pgnmLj3muMeabTzF60TaVcUoRmD2pD87uNA/WRWJpIQraVnqq9ZaltXBrszoT8N7O6rEWek1sM/q09g3KmiYF1DlXh6pJYzzzq092CMcKhjHm8aztLxlN7errwIpEDyhrfQ+ik81Awu3H1JJS+iQDeDZp/1nLveRSi/cjRZvoUnW443CDqW0jlqp2wJhuvPLqaCNbePAzbOGvIuhz2O4m6NYb3Ewf0rKZKm9NU+936JCPSN0n2KNzYuIHhz0AB9nAAh0TmiH3zRGdUxTFclPFrjBnbKGQsAJzTxtPgw+vbo+iF/5o6HQuAMGFkSwsM/Rpv0HwPolnwER9YO7t2UkMF9D+yXTxNTjnpTh0D43pxjwPvg+lnfmiiJMz+WJZvcEcODH62Mhvh6l5GafBGyGoeuyhiRbWxTj0B7B1FZv/fwdHYQoVvms0M2cOKw2iqXaBNAeGP+6Fi+iFYQLRlpZWkwQWAMFAhyKwpa3Gpu0lvfihGDyJ8Myal/MLFaKRuNZY/XiztVjOKwfe718+LXPlE1kCz/l2HWlbQ13gIxUNyn3F3Mn00YmU3nEQBw3W8qXsoZZxfISeRTvXu1G0mttEVxwVUs2lAUEODWOPjkxqalGCPOgMCZW2cKrLoB27+knEW1XRUvFAs5TtwmX8nedEerTOpbX1uljtrq6fCP6PQvbVZ43HiR0FbLo5AflxC/Vgkh9ealRy+d+HJsBweo5f+XCqmSAoUeFG4K3mIY1X6KSRXdxWUC8Yr7YBcSw0TB6DR8pMk/JyU/o8yeVYn297QJYRAoPGvbyOio77VTqyda5Fwz3vsKYgUJGUgONM37jUwJD8xLcFByy3cEcRPARm9Tq4mBS5T7/W2vednd4N+0IgqIvB6HTqBwY7yrr7LFQZmSMpvHMdMVx3YxStvkjHP3Hy4w6FeFe2KaTmfLuqMifHEHPMt/dCNwXrHUxoSqUyuTcKelWYGLZZAPSiJ+Jtb5eIrwnpxlKS2cNs23mFZqQ+W3opA1EOxQOWUVcDfiwwzsZJqAGA27yvkmob/1xoovJZ0Y8R5jq3m6ZSBhB9R+wYNjMrub6Yvv0xNFI2j/7oksC711Nmx4s6q7/jkkRJbdWT7v8aXJYUuRJ4YNBL1DDexh/zdQjqUJIT/5OuGM2527XE5RPEMn2fVYNGY+krmF2VpP6Ad80b2bfL/FJmjppBm33zBecjLfOLDNUNL+Pm6CvWlLi6CMZye88k6
X-OriginatorOrg: oracle.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 9f5fb2c8-f738-4f3d-82e1-08d8f54a082f
X-MS-Exchange-CrossTenant-AuthSource: DM6PR10MB3019.namprd10.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 01 Apr 2021 20:09:19.0099
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 4e2c6054-71cb-48f1-bd6c-3a9705aca71b
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 NRuzPIWp6PHdy4DccuBqQ75S/KCW36m/C4BK1REI10M9mls5gaJzZbKeVNKn21/I6PZKcSli3kNjwQwH5STKg7JIH34URy+g/H5ZTc2Lcl8=
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM5PR1001MB2091
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9941
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=0
 mlxlogscore=999
 adultscore=0 bulkscore=0 mlxscore=0 spamscore=0 malwarescore=0
 phishscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2103310000 definitions=main-2104010128
X-Proofpoint-ORIG-GUID: CNuQdGe6emIXG1svYnwZl9hjQRegRIVA
X-Proofpoint-GUID: CNuQdGe6emIXG1svYnwZl9hjQRegRIVA
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9941
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 mlxscore=0
 impostorscore=0 phishscore=0
 bulkscore=0 adultscore=0 clxscore=1015 malwarescore=0 priorityscore=1501
 suspectscore=0 spamscore=0 mlxlogscore=999 lowpriorityscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2103310000
 definitions=main-2104010128
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

v4 -> v5:
        1. In patch# 1, the actual size of the MSRPM and IOPM tables are now
	   defined. The initialization code for the tables has been adjusted
	   accordingly.
	2. In patch# 2, the checks have been adjusted based on the actual
	   size of the tables. The check for IOPM has also been fixed.
	3. In patch# 4, a new test case has been added. This new test uses
	   an address whose last byte touched the limit of the maximum
	   physical address.

[PATCH 1/5 v5] KVM: SVM: Define actual size of IOPM and MSRPM tables
[PATCH 2/5 v5] nSVM: Check addresses of MSR and IO permission maps
[PATCH 3/5 v5] KVM: nSVM: Cleanup in nested_svm_vmrun()
[PATCH 4/5 v5] nSVM: Test addresses of MSR and IO permissions maps
[PATCH 5/5 v5] SVM: Use ALIGN macro when aligning 'io_bitmap_area'

 arch/x86/kvm/svm/nested.c | 59 +++++++++++++++++++++++++++++------------------
 arch/x86/kvm/svm/svm.c    | 20 ++++++++--------
 arch/x86/kvm/svm/svm.h    |  3 +++
 3 files changed, 50 insertions(+), 32 deletions(-)

Krish Sadhukhan (3):
      KVM: SVM: Define actual size of IOPM and MSRPM tables
      nSVM: Check addresses of MSR and IO permission maps
      KVM: nSVM: Cleanup in nested_svm_vmrun()

 x86/svm.c       |  2 +-
 x86/svm_tests.c | 42 +++++++++++++++++++++++++++++++++++++++++-
 2 files changed, 42 insertions(+), 2 deletions(-)

Krish Sadhukhan (2):
      nSVM: Test addresses of MSR and IO permissions maps
      SVM: Use ALIGN macro when aligning 'io_bitmap_area'
```
