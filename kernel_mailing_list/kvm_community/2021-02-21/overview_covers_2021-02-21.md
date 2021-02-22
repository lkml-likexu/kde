

#### [RFC v3 0/5] Introduce MMIO/PIO dispatch file descriptors
##### From: Elena Afanasova <eafanasova@gmail.com>

```c
From patchwork Sun Feb 21 12:04:36 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Elena Afanasova <eafanasova@gmail.com>
X-Patchwork-Id: 12097293
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-10.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id CEE14C433E0
	for <kvm@archiver.kernel.org>; Sun, 21 Feb 2021 12:12:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9498264EF6
	for <kvm@archiver.kernel.org>; Sun, 21 Feb 2021 12:12:04 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229905AbhBUMLI (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sun, 21 Feb 2021 07:11:08 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:33084 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229663AbhBUMLF (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 21 Feb 2021 07:11:05 -0500
Received: from mail-lj1-x22e.google.com (mail-lj1-x22e.google.com
 [IPv6:2a00:1450:4864:20::22e])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 842B9C061574
        for <kvm@vger.kernel.org>; Sun, 21 Feb 2021 04:10:24 -0800 (PST)
Received: by mail-lj1-x22e.google.com with SMTP id o16so42561088ljj.11
        for <kvm@vger.kernel.org>; Sun, 21 Feb 2021 04:10:24 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=7xxmMhkUo5vLIF/NBtVw/E/xvIVKVyolllZIrIime28=;
        b=osx8x7kIhWknKNnacyZqW6cyzKespTfKTo/RcC4I1N6runUj3gNs03wTA/5euI5ofC
         ynkU3iMnOMwF66LRVUrI6qBOXr3jEklOsXTD1uaaLt67mtvCz0t4+po81hq+K4Dai+i+
         /+E0zz68dQIlYHcRBAQInAuZAfj4XSKi81F2xBoKPg/BG9pqk31TplCaF/uNUCteH1p4
         A2HRHbGVPPkvod8kW78mXhlYN7hXP5Mkj5lW1dj9qifomUcMhiSGDsfQzZTTr7mTxERc
         XYqHh9xmTX9fSZqgPC2HdgPtZXndquJ6orgE+Sc7WLgGX/s+AJhd9Xx/9aNVNO4hc+GL
         Kggw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=7xxmMhkUo5vLIF/NBtVw/E/xvIVKVyolllZIrIime28=;
        b=EFavIoDQd5AwafRZ6BoVx0zJCd+Az/IqZiQ9box6n3qi5yZesrQmNiH2EEI1MHnJ2J
         pEJzLHTgrY8T0xmxDYrZigppBPOlB6O1Z4eCXHarFJicXuM+FFleYJ84Ki2409tJXuvJ
         h+W+YWY1Rp0JdjTMnafadHaIS10q2980Hyd05eb1wGPRonk0YWvMlae4+TfdI2PCMTg3
         JycgXVoFMYXCvjbFoO8iVTw5fmmtJXC3O/3R6tmDT3hkUanbBfWTSNCgyfDtnjku861c
         0EdpvQh4g+h0w5qWE+SYGj8uq2LJ9Yx06jtL0g1UeDgq+CqyofzF/rudZlq591stok1g
         rt5w==
X-Gm-Message-State: AOAM531/wle+nAqM4U6eOajhvWJnR8ENRWhiQCcGB7SHUC5skE56jZaC
        YNpFCI3sOhi7y5fijnmkPnrRQYp0Yw0FVzvv
X-Google-Smtp-Source: 
 ABdhPJyTkA2jty3/SVI8WLUgj6hgh/m5YiVuVoTaSgDAmcAxvKllWbQsTCUvjTFjvcJDeuN7317Jnw==
X-Received: by 2002:a05:6512:558:: with SMTP id
 h24mr10697921lfl.531.1613909422707;
        Sun, 21 Feb 2021 04:10:22 -0800 (PST)
Received: from localhost.localdomain (37-145-186-126.broadband.corbina.ru.
 [37.145.186.126])
        by smtp.gmail.com with ESMTPSA id
 q6sm1547715lfn.23.2021.02.21.04.10.21
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Sun, 21 Feb 2021 04:10:22 -0800 (PST)
From: Elena Afanasova <eafanasova@gmail.com>
To: kvm@vger.kernel.org
Cc: stefanha@redhat.com, jag.raman@oracle.com,
        elena.ufimtseva@oracle.com, pbonzini@redhat.com,
        jasowang@redhat.com, mst@redhat.com, cohuck@redhat.com,
        john.levon@nutanix.com, Elena Afanasova <eafanasova@gmail.com>
Subject: [RFC v3 0/5] Introduce MMIO/PIO dispatch file descriptors
 (ioregionfd)
Date: Sun, 21 Feb 2021 15:04:36 +0300
Message-Id: <cover.1613828726.git.eafanasova@gmail.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patchset introduces a KVM dispatch mechanism which can be used 
for handling MMIO/PIO accesses over file descriptors without returning 
from ioctl(KVM_RUN). This allows device emulation to run in another task 
separate from the vCPU task.

This is achieved through KVM vm ioctl for registering MMIO/PIO regions and 
a wire protocol that KVM uses to communicate with a task handling an 
MMIO/PIO access.

TODOs:
* Implement KVM_EXIT_IOREGIONFD_FAILURE
* Add non-x86 arch support
* Add kvm-unittests
* Flush waiters if ioregion is deleted

v3:
 - add FAST_MMIO bus support
 - add KVM_IOREGION_DEASSIGN flag
 - rename kvm_ioregion read/write file descriptors
 - split ioregionfd signal handling support into two patches
 - move ioregion_interrupted flag to ioregion_ctx
 - reorder ioregion_ctx fields
 - rework complete_ioregion operations 
 - add signal handling support for crossing a page boundary case
 - change wire protocol license
 - fix ioregionfd state machine
 - remove ioregionfd_cmd info and drop appropriate macros
 - add comment on ioregionfd cmds/replies serialization
 - drop kvm_io_bus_finish/prepare()

Elena Afanasova (5):
  KVM: add initial support for KVM_SET_IOREGION
  KVM: x86: add support for ioregionfd signal handling
  KVM: implement wire protocol
  KVM: add ioregionfd context
  KVM: enforce NR_IOBUS_DEVS limit if kmemcg is disabled

 arch/x86/kvm/Kconfig          |   1 +
 arch/x86/kvm/Makefile         |   1 +
 arch/x86/kvm/vmx/vmx.c        |  40 ++-
 arch/x86/kvm/x86.c            | 273 +++++++++++++++++-
 include/linux/kvm_host.h      |  28 ++
 include/uapi/linux/ioregion.h |  30 ++
 include/uapi/linux/kvm.h      |  25 ++
 virt/kvm/Kconfig              |   3 +
 virt/kvm/eventfd.c            |  25 ++
 virt/kvm/eventfd.h            |  14 +
 virt/kvm/ioregion.c           | 529 ++++++++++++++++++++++++++++++++++
 virt/kvm/ioregion.h           |  15 +
 virt/kvm/kvm_main.c           |  36 ++-
 13 files changed, 996 insertions(+), 24 deletions(-)
 create mode 100644 include/uapi/linux/ioregion.h
 create mode 100644 virt/kvm/eventfd.h
 create mode 100644 virt/kvm/ioregion.c
 create mode 100644 virt/kvm/ioregion.h
```
