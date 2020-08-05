

#### [PATCH 0/6] Allow userspace to manage MSRs
##### From: Aaron Lewis <aaronlewis@google.com>

```c
From patchwork Tue Aug  4 04:20:37 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Aaron Lewis <aaronlewis@google.com>
X-Patchwork-Id: 11699705
Return-Path: <SRS0=wIAV=BO=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7599813B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  4 Aug 2020 04:21:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8F3DF2070A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  4 Aug 2020 04:21:02 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="SRPje/kN"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728287AbgHDEUy (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 4 Aug 2020 00:20:54 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:48264 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725807AbgHDEUy (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 4 Aug 2020 00:20:54 -0400
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id D446AC06174A
        for <kvm@vger.kernel.org>; Mon,  3 Aug 2020 21:20:53 -0700 (PDT)
Received: by mail-yb1-xb49.google.com with SMTP id l67so13173328ybb.7
        for <kvm@vger.kernel.org>; Mon, 03 Aug 2020 21:20:53 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=UAH7GGDxpw0Jk/D++xQ0t+lcW0UcVRC2qykxqWivZiM=;
        b=SRPje/kNJFU7MFZoYvFTbxK52Da+79MbhvNtVCBuEXfYWQjvgGBV93+pbpGsqIOzGE
         W3QfMtwZrfMQWjc7IKqZvn502x38fvzu6bDPywlTAIAZYxwCD3UR/rSgIotM5JgVI5lP
         YbcfND8Jud3NSGMrfZ9llxh3z0M5hS955BWkjCSe8Ay67F5ZCOLu2eaDOnyFqapf+1XS
         pXjktlITU6fSCcwQyYSxfo0x2OEJDDj69kMiC8a7lLrkbprpSVycpY9lhFdlocW0Cowf
         plEDFLlgdI/kP/5HeRZkg+cA01am/t37xMlFq31Gpz+Q+oNKmfwOof7p/86im+vfO59R
         MbEQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=UAH7GGDxpw0Jk/D++xQ0t+lcW0UcVRC2qykxqWivZiM=;
        b=C6AfNvBeR1z+OPELBLHQgNu2Q3Zaw8ZFWOjpEJFFLoXGa/vnUjh8WT33TQEQqANHwv
         QOFjFsao4u1h95fxFrJtEoXGoTx0pTr0Vqjxl9y1hUz22Ds6UCux8L/XUcPlhA0StNmv
         iNvllT+PSZShs0v5HdmRFBeFNlDF83qphtfFiEQe+bSGDZ3XtCwm6AeL3GPS76sGbqkA
         kmpHSnHN5k8jkewEiZlj9iJNgJti1ABqoufDFtE0Um7S+KYWqgRzO9xMkrw/AWSB25Vj
         HR1Jy5gC4zU0Zu3N7I253tpxmXkcAAxJBX9TMdXZftmLLHCcey0eE+GYX/fRmwgj+ryH
         x0dQ==
X-Gm-Message-State: AOAM530CKEpyTi4b+RnWp+/R5x/Tq2sq5A4ldERjyCx90tmWByq8IHiY
        bCI1rofTJkBJF5gb9+dscW5poaNiHxln98Hk
X-Google-Smtp-Source: 
 ABdhPJwLH2zd00jjwKbPMH781SkgiXbKWtsMsMfu9kHcdzFtIWiY5PYRl8PzAg3eF2SFh5vhh+jPp0nkmLe2coxD
X-Received: by 2002:a25:ae59:: with SMTP id
 g25mr29619447ybe.135.1596514852934;
 Mon, 03 Aug 2020 21:20:52 -0700 (PDT)
Date: Mon,  3 Aug 2020 21:20:37 -0700
Message-Id: <20200804042043.3592620-1-aaronlewis@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.28.0.163.g6104cc2f0b6-goog
Subject: [PATCH 0/6] Allow userspace to manage MSRs
From: Aaron Lewis <aaronlewis@google.com>
To: jmattson@google.com, graf@amazon.com
Cc: pshier@google.com, oupton@google.com, kvm@vger.kernel.org,
        Aaron Lewis <aaronlewis@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series makes it possible for userspace to manage MSRs by having KVM
forward select MSRs to it when rdmsr and wrmsr are executed in the guest.
Userspace can set this up by calling the ioctl KVM_SET_EXIT_MSRS with a
list of MSRs it wants to manage.  When KVM encounters any of these MSRs
they are forwarded to userspace for processing.  Userspace can then read
from or write to the MSR, or it can also throw a #GP if needed.

This series includes the kernel changes needed to implement this feature
and a test that exercises this behavior.  Also, included is an
implementation of expection handling in selftests, which allows the test
to excercise throwing a #GP.

Aaron Lewis (6):
  KVM: x86: Add ioctl for accepting a userspace provided MSR list
  KVM: x86: Add support for exiting to userspace on rdmsr or wrmsr
  KVM: x86: Prepare MSR bitmaps for userspace tracked MSRs
  KVM: x86: Ensure the MSR bitmap never clears userspace tracked MSRs
  selftests: kvm: Fix the segment descriptor layout to match the actual
    layout
  selftests: kvm: Add test to exercise userspace MSR list

 Documentation/virt/kvm/api.rst                |  53 +++-
 arch/x86/include/asm/kvm_host.h               |   5 +
 arch/x86/kvm/svm/svm.c                        |  93 ++++--
 arch/x86/kvm/trace.h                          |  24 ++
 arch/x86/kvm/vmx/nested.c                     |   2 +-
 arch/x86/kvm/vmx/vmx.c                        |  94 +++---
 arch/x86/kvm/vmx/vmx.h                        |   2 +-
 arch/x86/kvm/x86.c                            | 140 +++++++++
 include/trace/events/kvm.h                    |   2 +-
 include/uapi/linux/kvm.h                      |  12 +
 tools/testing/selftests/kvm/.gitignore        |   1 +
 tools/testing/selftests/kvm/Makefile          |  20 +-
 .../selftests/kvm/include/x86_64/processor.h  |  29 +-
 tools/testing/selftests/kvm/lib/kvm_util.c    |  17 ++
 .../selftests/kvm/lib/kvm_util_internal.h     |   2 +
 .../selftests/kvm/lib/x86_64/handlers.S       |  83 ++++++
 .../selftests/kvm/lib/x86_64/processor.c      | 168 ++++++++++-
 .../testing/selftests/kvm/lib/x86_64/ucall.c  |   3 +
 .../selftests/kvm/x86_64/userspace_msr_exit.c | 271 ++++++++++++++++++
 19 files changed, 931 insertions(+), 90 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/lib/x86_64/handlers.S
 create mode 100644 tools/testing/selftests/kvm/x86_64/userspace_msr_exit.c
```
#### [RFC PATCH v1 0/3] put arm64 kvm_config on a diet
##### From: =?utf-8?q?Alex_Benn=C3=A9e?= <alex.bennee@linaro.org>

```c
From patchwork Tue Aug  4 12:44:14 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Alex_Benn=C3=A9e?= <alex.bennee@linaro.org>
X-Patchwork-Id: 11700373
Return-Path: <SRS0=wIAV=BO=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 64F04138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  4 Aug 2020 12:47:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5F19121744
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  4 Aug 2020 12:47:24 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=linaro.org header.i=@linaro.org
 header.b="xmDdxPVB"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728349AbgHDMql (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 4 Aug 2020 08:46:41 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:41172 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728258AbgHDMoX (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 4 Aug 2020 08:44:23 -0400
Received: from mail-wm1-x341.google.com (mail-wm1-x341.google.com
 [IPv6:2a00:1450:4864:20::341])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id EA839C06179E
        for <kvm@vger.kernel.org>; Tue,  4 Aug 2020 05:44:22 -0700 (PDT)
Received: by mail-wm1-x341.google.com with SMTP id k8so2787831wma.2
        for <kvm@vger.kernel.org>; Tue, 04 Aug 2020 05:44:22 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=linaro.org; s=google;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=pXFf5i+ccqczXVXTg/nZ29LHnMvff9vMvvoJKipTK/k=;
        b=xmDdxPVBebllwYSXr8MTF5/0WVgZGKSZUMcEmtg1Yb6lXQo90+6kVdw3cQCf4XLw2a
         M7kb5BeEfu2MZRYypdtYVL7FuPiQ9THnz2WAl4CNEiw92SXD1Gp2UD3XZwg82u3Ec4mv
         t3ZWzvYQJ2a0G4okutZQe+5ypiJzpjGTq3/5YMxxkhi1n/QDZTKpGr0WFAPJg4NFSYxF
         rzXEuRDF0jzSKq3FW5Wgttxs2iCjBLDtl0PSrYbT2lfK2UrFozrTRxtfl4VFYOEwim7v
         WZZ0lo3eI2JwOsiFmXAMwp3UwPLdLcwIVZCe4upmuSA1YTH3p9bYdrrABYOA4zvUNdI1
         7UHA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=pXFf5i+ccqczXVXTg/nZ29LHnMvff9vMvvoJKipTK/k=;
        b=VmFAMbaM1A59FACfRN1fTzea9TTkRlK48QJEDmxcZ6fq6LXF9Pql2Cn1txMckF4O6X
         ipbd+pz5JTXdF/Smk8emSGfGjUAsouxIokW+WgSN/oejIVFoULLDCv5X14M3aUDmQWk6
         lW/V4K/nuuiHYouFGyCmuyTeqK6rtJn0ck0GinTxWogEF2iAHYfxczkJ2lRjK+8ufNIf
         YHmgdHnYavKbjeeRgPnFWdN4LBao/zli2H66BeGlDymKp+GoCnJNhDHgh0lGc8qHmVV/
         neff5JGUszxfwUrRE6SwiNcck4EHusFRh+511RlsPXPyfsle/74JRIfg0fiOlCYIdjOV
         ySZw==
X-Gm-Message-State: AOAM532bUhzkdpPjnNKUO/9hRhncutQVkLyCEoOeeFffPTzNrxmkhyhK
        /BNL2IM0GlESTDqIKTq4Zu731g==
X-Google-Smtp-Source: 
 ABdhPJxSYL3nLFynYC8/0kcrhha40SMBrbJj4GceYNd50xdCxUrISm9qcztn279uGdoJsV28A5ASGg==
X-Received: by 2002:a1c:1bc4:: with SMTP id
 b187mr3879098wmb.175.1596545061671;
        Tue, 04 Aug 2020 05:44:21 -0700 (PDT)
Received: from zen.linaroharston ([51.148.130.216])
        by smtp.gmail.com with ESMTPSA id
 15sm4107897wmo.33.2020.08.04.05.44.18
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 04 Aug 2020 05:44:18 -0700 (PDT)
Received: from zen.lan (localhost [127.0.0.1])
        by zen.linaroharston (Postfix) with ESMTP id 77F6D1FF7E;
        Tue,  4 Aug 2020 13:44:17 +0100 (BST)
From: =?utf-8?q?Alex_Benn=C3=A9e?= <alex.bennee@linaro.org>
To: kvm@vger.kernel.org, linux-arm-kernel@lists.infradead.org
Cc: linux-kernel@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
 christoffer.dall@arm.com, maz@kernel.org,
 =?utf-8?q?Alex_Benn=C3=A9e?= <alex.bennee@linaro.org>
Subject: [RFC PATCH v1 0/3] put arm64 kvm_config on a diet
Date: Tue,  4 Aug 2020 13:44:14 +0100
Message-Id: <20200804124417.27102-1-alex.bennee@linaro.org>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

When building guest kernels for virtualisation we were bringing in a
bunch of stuff from physical hardware which we don't need for our
idealised fixable virtual PCI devices. This series makes some Kconfig
changes to allow the ThunderX and XGene PCI drivers to be compiled
out. It also drops PCI_QUIRKS from the KVM guest build as a virtual
PCI device should be quirk free.

This is my first time hacking around Kconfig so I hope I've got the
balance between depends and selects right but please let be know if it
could be specified in a cleaner way.

Alex Bennée (3):
  arm64: allow de-selection of ThunderX PCI controllers
  arm64: gate the whole of pci-xgene on CONFIG_PCI_XGENE
  kernel/configs: don't include PCI_QUIRKS in KVM guest configs

 arch/arm64/Kconfig.platforms    | 2 ++
 arch/arm64/configs/defconfig    | 1 +
 drivers/pci/controller/Kconfig  | 7 +++++++
 drivers/pci/controller/Makefile | 8 +++-----
 kernel/configs/kvm_guest.config | 1 +
 5 files changed, 14 insertions(+), 5 deletions(-)
```
#### [PATCH v2 0/6] KVM: arm64: pvtime: Fixes and a new cap
##### From: Andrew Jones <drjones@redhat.com>

```c
From patchwork Tue Aug  4 17:05:58 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11700735
Return-Path: <SRS0=wIAV=BO=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5E84B722
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  4 Aug 2020 17:08:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 521C32086A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  4 Aug 2020 17:08:41 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="fREyw3tq"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729970AbgHDRIi (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 4 Aug 2020 13:08:38 -0400
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:29339 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1729305AbgHDRIX (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 4 Aug 2020 13:08:23 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1596560902;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=ursdoHm0tMH2wXUeTBLWm59Mni6170SDHwjwgqHwT+o=;
        b=fREyw3tqR5I+Gw55wTs3dsCson+0OGrAXZ+t4inTxO/HhAwG0HQZSrnhfsUiXqHZbDqHRi
        /4fd0AGkbuHPg8oB9Dwfa5BbtjHi6/Jxp9Qur19i7BJZ6ZDzm6FzPcfETIqjVH0/LFD1GX
        pfMWniAgjpQkDLM1inLgAu4WKDdehdQ=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-170-2ZsODA-iONy5CZ-XCCUzcA-1; Tue, 04 Aug 2020 13:06:08 -0400
X-MC-Unique: 2ZsODA-iONy5CZ-XCCUzcA-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 8115B106B242;
        Tue,  4 Aug 2020 17:06:07 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.40.192.120])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 896CC72E48;
        Tue,  4 Aug 2020 17:06:05 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu
Cc: maz@kernel.org, steven.price@arm.com, pbonzini@redhat.com
Subject: [PATCH v2 0/6] KVM: arm64: pvtime: Fixes and a new cap
Date: Tue,  4 Aug 2020 19:05:58 +0200
Message-Id: <20200804170604.42662-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

v2:
  - ARM_SMCCC_HV_PV_TIME_FEATURES now also returns SMCCC_RET_NOT_SUPPORTED
    when steal time is not supported
  - Added READ_ONCE() for the run_delay read
  - Reworked kvm_put/get_guest to not require type as a parameter
  - Added some more text to the documentation for KVM_CAP_STEAL_TIME
  - Enough changed that I didn't pick up Steven's r-b's


The first four patches in the series are fixes that come from testing
and reviewing pvtime code while writing the QEMU support[*]. The last
patch is only a convenience for userspace, and I wouldn't be heartbroken
if it wasn't deemed worth it. The QEMU patches are currently written
without the cap. However, if the cap is accepted, then I'll change the
QEMU code to use it.

Thanks,
drew

[*] https://lists.gnu.org/archive/html/qemu-devel/2020-07/msg03856.html
    (a v2 of this series will also be posted shortly)

Andrew Jones (6):
  KVM: arm64: pvtime: steal-time is only supported when configured
  KVM: arm64: pvtime: Fix potential loss of stolen time
  KVM: arm64: Drop type input from kvm_put_guest
  KVM: arm64: pvtime: Fix stolen time accounting across migration
  KVM: Documentation: Minor fixups
  arm64/x86: KVM: Introduce steal-time cap

 Documentation/virt/kvm/api.rst    | 22 ++++++++++++++++++----
 arch/arm64/include/asm/kvm_host.h |  2 +-
 arch/arm64/kvm/arm.c              |  3 +++
 arch/arm64/kvm/pvtime.c           | 29 +++++++++++++----------------
 arch/x86/kvm/x86.c                |  3 +++
 include/linux/kvm_host.h          | 31 ++++++++++++++++++++++++++-----
 include/uapi/linux/kvm.h          |  1 +
 7 files changed, 65 insertions(+), 26 deletions(-)
```
