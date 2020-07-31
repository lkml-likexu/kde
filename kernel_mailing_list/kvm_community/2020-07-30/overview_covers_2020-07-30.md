

#### [PATCH-for-5.1? v2 0/2] util/pagesize: Make qemu_real_host_page_size
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>

```c
From patchwork Thu Jul 30 14:12:43 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
 <philmd@redhat.com>
X-Patchwork-Id: 11693149
Return-Path: <SRS0=wP1B=BJ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5139B913
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Jul 2020 14:12:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 38B652070B
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Jul 2020 14:12:56 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="JbzXGU4v"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728352AbgG3OMz (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 30 Jul 2020 10:12:55 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:51420 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726581AbgG3OMy (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 30 Jul 2020 10:12:54 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1596118373;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
  content-type:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=1nCUmzxGIbC0kn3/ng/Xf3mTqDwzdByUhgD6JCrp3Ls=;
        b=JbzXGU4vjSmDVhhQcsHwxfd8z7x9be9eVHkjjkTigXhvID2YkGFzSYaZx8yOUsfWGA2i7P
        RzzGaVLAA7mS1ZeYiFQqxj7KgZHZbTj8wldJV1nnHfPbUjEd4EDk0Oz65AID/l8B+ivZwk
        8U2TNnXh4S+3CSpctprEfHgRMnIN4YM=
Received: from mail-wm1-f72.google.com (mail-wm1-f72.google.com
 [209.85.128.72]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-109--tIGMiFcMqeUHaCdNEecng-1; Thu, 30 Jul 2020 10:12:52 -0400
X-MC-Unique: -tIGMiFcMqeUHaCdNEecng-1
Received: by mail-wm1-f72.google.com with SMTP id v8so1422378wma.6
        for <kvm@vger.kernel.org>; Thu, 30 Jul 2020 07:12:51 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=1nCUmzxGIbC0kn3/ng/Xf3mTqDwzdByUhgD6JCrp3Ls=;
        b=SOUV9pmbHRUFxPRxLdzQDODg5rSlTE9PAdPJFz3TcmwxCufUGME45kPQG5pNt2nFG+
         Se5UbQNlEvmQV/QtDms8z8aHLcarylCRgHxRilLUBCrFhJhivoNYy6nxr6Qb5QC6ELlY
         QtsIhEWiG7ghF7KPkGW+XIl5SKUars9XQrzi9dj+xsmEsvs990Z5AMGDG0Jx75Y+8DPF
         3+K+HuKPWC0XHWRJ3Y4rQg9/YbYimF2LOkxulhbxJdBb7B3HagP5RQmhfVx9aYt5t4Yy
         QZw+aeurqeOhkvH2qbxrdI8pIm/vd+i/LGtATRWHUoXWfG5vp5zDBds9yUfivJSWot0o
         F9lw==
X-Gm-Message-State: AOAM531AOkkssmYeC6mM3kOAeliN9YO1KGkcoWe16gKXNJcgn3YkYuDG
        yeDfzSfW18hxHnc3uvcg494iCueWakCNoeGGq55MTbLGpGwqe7pvv6oPLIXY7r54lPXY+OZKrIC
        0un5s6+0bDwr+
X-Received: by 2002:adf:e9cd:: with SMTP id l13mr3326758wrn.340.1596118368099;
        Thu, 30 Jul 2020 07:12:48 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJyAWJCTyc1yX9F+GsslaNXx+FdufjDrNeO7osI5iibj6rASK8Lnwmt5G0LLkaV/o05prpzKBQ==
X-Received: by 2002:adf:e9cd:: with SMTP id l13mr3326725wrn.340.1596118367870;
        Thu, 30 Jul 2020 07:12:47 -0700 (PDT)
Received: from localhost.localdomain (214.red-88-21-68.staticip.rima-tde.net.
 [88.21.68.214])
        by smtp.gmail.com with ESMTPSA id
 x11sm9644402wrl.28.2020.07.30.07.12.46
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 30 Jul 2020 07:12:47 -0700 (PDT)
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
Subject: [PATCH-for-5.1? v2 0/2] util/pagesize: Make qemu_real_host_page_size
 of type size_t
Date: Thu, 30 Jul 2020 16:12:43 +0200
Message-Id: <20200730141245.21739-1-philmd@redhat.com>
X-Mailer: git-send-email 2.21.3
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Since v1:
Make QEMU_VMALLOC_ALIGN unsigned in a previous patch

Philippe Mathieu-Daudé (2):
  qemu/osdep: Make QEMU_VMALLOC_ALIGN unsigned long
  util/pagesize: Make qemu_real_host_page_size of type size_t

 include/exec/ram_addr.h  | 4 ++--
 include/qemu/osdep.h     | 6 +++---
 accel/kvm/kvm-all.c      | 3 ++-
 block/qcow2-cache.c      | 2 +-
 exec.c                   | 8 ++++----
 hw/ppc/spapr_pci.c       | 2 +-
 hw/virtio/virtio-mem.c   | 2 +-
 migration/migration.c    | 2 +-
 migration/postcopy-ram.c | 2 +-
 monitor/misc.c           | 2 +-
 util/pagesize.c          | 2 +-
 11 files changed, 18 insertions(+), 17 deletions(-)
```
#### [PATCH v2 0/4] KVM: SVM: SEV-ES groundwork
##### From: Joerg Roedel <joro@8bytes.org>

```c
From patchwork Thu Jul 30 15:43:36 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Joerg Roedel <joro@8bytes.org>
X-Patchwork-Id: 11693335
Return-Path: <SRS0=wP1B=BJ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 60C3D1392
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Jul 2020 15:44:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5342C21D95
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Jul 2020 15:44:13 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729778AbgG3Pnq (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 30 Jul 2020 11:43:46 -0400
Received: from 8bytes.org ([81.169.241.247]:34072 "EHLO theia.8bytes.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726275AbgG3Pnq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 30 Jul 2020 11:43:46 -0400
Received: by theia.8bytes.org (Postfix, from userid 1000)
        id 7771697F; Thu, 30 Jul 2020 17:43:44 +0200 (CEST)
From: Joerg Roedel <joro@8bytes.org>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Tom Lendacky <thomas.lendacky@amd.com>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v2 0/4] KVM: SVM: SEV-ES groundwork
Date: Thu, 30 Jul 2020 17:43:36 +0200
Message-Id: <20200730154340.14021-1-joro@8bytes.org>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Paolo,

here is v2 of the  groundwork patches for the upcoming SEV-ES support in
the Linux kernel. They are part of both the client patch-set and of the
KVM hypervisor patches (under development).

Patch 1 necesary to fix a compile warning about a stack-frame getting
too large. The other 3 patches are currently posted as part of the
SEV-ES client patch-set.

This version addresses the review comments from Sean.

It would be great if you could consider them for v5.9, so that the
client and the hypervisor patch-sets can be developed more independently
of each other.

Please let me know what you think.

Regards,

	Joerg
Borislav Petkov (1):
  KVM: SVM: Use __packed shorthand

Joerg Roedel (2):
  KVM: SVM: nested: Don't allocate VMCB structures on stack
  KVM: SVM: Add GHCB Accessor functions

Tom Lendacky (1):
  KVM: SVM: Add GHCB definitions

 arch/x86/include/asm/svm.h | 103 ++++++++++++++++++++++++++++++++++---
 arch/x86/kvm/svm/nested.c  |  47 ++++++++++++-----
 arch/x86/kvm/svm/svm.c     |   2 +
 3 files changed, 131 insertions(+), 21 deletions(-)
```
