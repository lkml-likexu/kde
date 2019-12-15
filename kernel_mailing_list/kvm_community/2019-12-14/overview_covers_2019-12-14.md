

#### [PATCH 0/8] Simplify memory_region_add_subregion_overlap(...,
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>

```c
From patchwork Sat Dec 14 15:56:06 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
 <philmd@redhat.com>
X-Patchwork-Id: 11292309
Return-Path: <SRS0=Vqht=2E=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6DCA5175D
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 14 Dec 2019 15:56:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4BACD2073D
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 14 Dec 2019 15:56:38 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="czsEzxAk"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726820AbfLNP4h (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 14 Dec 2019 10:56:37 -0500
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:52291 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1725943AbfLNP4h (ORCPT
        <rfc822;kvm@vger.kernel.org>); Sat, 14 Dec 2019 10:56:37 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1576338995;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=DU+v1+qSXxMwHczsoakDiicLnkfOmtj3Euf4AZRmwFY=;
        b=czsEzxAkBaZZtRWijzCurYB08NJgkBYaUM4SgbPUYmZ9SnxolkXKKOuFu3BnjmTttmCql2
        fIMtntFJjEEW3VluP34x9C9+v+/Ms0yGfNU4yRmEWBz2JNcjSocj5z2/Gq36QuyVs5FFuW
        AMhPaDnne4gFE4WKkn+ejc0wnNOHyEA=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-200-9iIaSgdkNYWGuH4yNdMIvw-1; Sat, 14 Dec 2019 10:56:33 -0500
X-MC-Unique: 9iIaSgdkNYWGuH4yNdMIvw-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id B08321005502;
        Sat, 14 Dec 2019 15:56:31 +0000 (UTC)
Received: from x1w.redhat.com (ovpn-205-147.brq.redhat.com [10.40.205.147])
        by smtp.corp.redhat.com (Postfix) with ESMTPS id 234905D6A7;
        Sat, 14 Dec 2019 15:56:16 +0000 (UTC)
From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>
To: qemu-devel@nongnu.org
Cc: Peter Maydell <peter.maydell@linaro.org>,
 Andrew Baumann <Andrew.Baumann@microsoft.com>,
 Aurelien Jarno <aurelien@aurel32.net>, kvm@vger.kernel.org,
 Alex Williamson <alex.williamson@redhat.com>,
 Aleksandar Markovic <amarkovic@wavecomp.com>, Joel Stanley <joel@jms.id.au>,
 qemu-arm@nongnu.org, Marcelo Tosatti <mtosatti@redhat.com>,
 Alistair Francis <alistair@alistair23.me>,
 "Michael S. Tsirkin" <mst@redhat.com>, Eduardo Habkost <ehabkost@redhat.com>,
 Richard Henderson <rth@twiddle.net>,
 Aleksandar Rikalo <aleksandar.rikalo@rt-rk.com>, =?utf-8?q?Philippe_Mathieu?=
	=?utf-8?q?-Daud=C3=A9?= <philmd@redhat.com>,
 Paul Burton <pburton@wavecomp.com>,
 Marcel Apfelbaum <marcel.apfelbaum@gmail.com>,
 "Edgar E. Iglesias" <edgar.iglesias@gmail.com>,
 Paolo Bonzini <pbonzini@redhat.com>
Subject: [PATCH 0/8] Simplify memory_region_add_subregion_overlap(...,
 priority=0)
Date: Sat, 14 Dec 2019 16:56:06 +0100
Message-Id: <20191214155614.19004-1-philmd@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

In this series we use coccinelle to replace:
- memory_region_add_subregion_overlap(..., priority=0)
+ memory_region_add_subregion(...)

Rationale is the code is easier to read, and reviewers don't
have to worry about overlapping because it isn't used.

Last patch is a minor cleanup in variable names.

I expect each subsystem maintainer to take the subsystem patches.

Regards,

Phil.

Philippe Mathieu-Daudé (8):
  hw/arm/nrf51_soc: Use memory_region_add_subregion() when priority is 0
  hw/arm/raspi: Use memory_region_add_subregion() when priority is 0
  hw/arm/xlnx-versal: Use memory_region_add_subregion() when priority is
    0
  hw/i386/intel_iommu: Use memory_region_add_subregion when priority is
    0
  hw/mips/boston: Use memory_region_add_subregion() when priority is 0
  hw/vfio/pci: Use memory_region_add_subregion() when priority is 0
  target/i386: Use memory_region_add_subregion() when priority is 0
  target/i386/cpu: Use 'mr' for MemoryRegion variables

 target/i386/cpu.h            |  2 +-
 hw/arm/bcm2835_peripherals.c |  4 ++--
 hw/arm/nrf51_soc.c           | 14 +++++++-------
 hw/arm/raspi.c               |  2 +-
 hw/arm/xlnx-versal-virt.c    |  3 +--
 hw/arm/xlnx-versal.c         |  4 ++--
 hw/i386/intel_iommu.c        | 11 ++++-------
 hw/mips/boston.c             | 14 +++++++-------
 hw/vfio/pci.c                |  3 +--
 target/i386/cpu.c            | 18 +++++++++---------
 target/i386/kvm.c            |  2 +-
 11 files changed, 36 insertions(+), 41 deletions(-)
```
