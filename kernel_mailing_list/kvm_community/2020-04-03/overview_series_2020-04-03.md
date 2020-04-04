#### [GIT PULL] VFIO updates for v5.7-rc1
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alex Williamson <alex.williamson@redhat.com>
X-Patchwork-Id: 11473855
Return-Path: <SRS0=Xk8+=5T=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8520E92C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Apr 2020 22:22:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 56B7920659
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Apr 2020 22:22:49 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="PZepwGBx"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728375AbgDCWWs (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 3 Apr 2020 18:22:48 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:39031 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1727879AbgDCWWs (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 3 Apr 2020 18:22:48 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1585952566;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=s4frkIsjfdUlJtqzclZG3qUK/GnNSIuQZIcCJzVIQcI=;
        b=PZepwGBxGiVZO2EmgMLywISLJeyfENQ3E2dvJr0eLrJOrVLF714JihNAc0kmxNfh27pRcS
        AKr6PSCuf3INKQXwfpGAiph8rCynXGd3guX4Vw+JdcMniwwV1KpXZ9LwQYfAdRxIhkHM40
        sL3JDQm2xyDadVQWSAUMEGY7q9Ez6PU=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-30-i3sFbb7LNTGRZIWfJgx-SQ-1; Fri, 03 Apr 2020 18:22:44 -0400
X-MC-Unique: i3sFbb7LNTGRZIWfJgx-SQ-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id BA63E18CA240;
        Fri,  3 Apr 2020 22:22:43 +0000 (UTC)
Received: from w520.home (ovpn-112-162.phx2.redhat.com [10.3.112.162])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 7BB37114810;
        Fri,  3 Apr 2020 22:22:43 +0000 (UTC)
Date: Fri, 3 Apr 2020 16:22:42 -0600
From: Alex Williamson <alex.williamson@redhat.com>
To: Linus Torvalds <torvalds@linux-foundation.org>
Cc: <linux-kernel@vger.kernel.org>,
        "kvm@vger.kernel.org" <kvm@vger.kernel.org>
Subject: [GIT PULL] VFIO updates for v5.7-rc1
Message-ID: <20200403162242.5e4f9afa@w520.home>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Linus,

The following changes since commit 16fbf79b0f83bc752cee8589279f1ebfe57b3b6e:

  Linux 5.6-rc7 (2020-03-22 18:31:56 -0700)

are available in the Git repository at:

  git://github.com/awilliam/linux-vfio.git tags/vfio-v5.7-rc1

for you to fetch changes up to f44efca0493ddc1e8731047c234ec8e475943077:

  vfio: Ignore -ENODEV when getting MSI cookie (2020-04-01 13:51:51 -0600)

----------------------------------------------------------------
VFIO updates for v5.7-rc1

 - vfio-pci SR-IOV support (Alex Williamson)

 - vfio DMA read/write interface (Yan Zhao)

 - Fix vfio-platform erroneous IRQ error log (Eric Auger)

 - Fix shared ATSD support for NVLink on POWER (Sam Bobroff)

 - Fix init error without CONFIG_IOMMU_DMA (Andre Przywara)

----------------------------------------------------------------
Alex Williamson (8):
      vfio: Include optional device match in vfio_device_ops callbacks
      vfio/pci: Implement match ops
      vfio/pci: Introduce VF token
      vfio: Introduce VFIO_DEVICE_FEATURE ioctl and first user
      vfio/pci: Add sriov_configure support
      vfio/pci: Remove dev_fmt definition
      vfio/pci: Cleanup .probe() exit paths
      Merge branches 'v5.7/vfio/alex-sriov-v3' and 'v5.7/vfio/yan-dma-rw-v4' into v5.7/vfio/next

Andre Przywara (1):
      vfio: Ignore -ENODEV when getting MSI cookie

Eric Auger (1):
      vfio: platform: Switch to platform_get_irq_optional()

Sam Bobroff (1):
      vfio-pci/nvlink2: Allow fallback to ibm,mmio-atsd[0]

Yan Zhao (3):
      vfio: allow external user to get vfio group from device
      vfio: introduce vfio_dma_rw to read/write a range of IOVAs
      vfio: avoid inefficient operations on VFIO group in vfio_pin/unpin_pages

 drivers/vfio/pci/vfio_pci.c           | 390 +++++++++++++++++++++++++++++++---
 drivers/vfio/pci/vfio_pci_nvlink2.c   |  10 +-
 drivers/vfio/pci/vfio_pci_private.h   |  10 +
 drivers/vfio/platform/vfio_platform.c |   2 +-
 drivers/vfio/vfio.c                   | 198 ++++++++++++++++-
 drivers/vfio/vfio_iommu_type1.c       |  78 ++++++-
 include/linux/vfio.h                  |  17 ++
 include/uapi/linux/vfio.h             |  37 ++++
 8 files changed, 710 insertions(+), 32 deletions(-)
```
#### [kvm-unit-tests PATCH v4 01/12] arm64: Provide read/write_sysreg_s
##### From: Eric Auger <eric.auger@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Auger Eric <eric.auger@redhat.com>
X-Patchwork-Id: 11471939
Return-Path: <SRS0=Xk8+=5T=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5FD2B92A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Apr 2020 07:13:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 3352920CC7
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Apr 2020 07:13:45 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="AmaEZl22"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2389104AbgDCHNo (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 3 Apr 2020 03:13:44 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:24733 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S2388959AbgDCHNn (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 3 Apr 2020 03:13:43 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1585898022;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=5QgGQR5lmCzHdU2tw8u26Dp0LVz138MaKuXfv7AyzLc=;
        b=AmaEZl22Q6IctKMMzB+rgc+I1AJAJjjmCPvgwSxYbp1F/7g70ROC+W/WgheZZZrnrpsD0w
        HJn3BGdNJ6XD6i09ZsLqX/OtUMQi7+MlinhASqRimz9VP1UZJhENS/jSWEkmmxfjHB/SX3
        jhSyQK9eZihjj2v+7n0051UbQpd95Rc=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-246-6uK3z0ZZOhS9hY4FytW9qg-1; Fri, 03 Apr 2020 03:13:40 -0400
X-MC-Unique: 6uK3z0ZZOhS9hY4FytW9qg-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id D63AF107ACC4;
        Fri,  3 Apr 2020 07:13:38 +0000 (UTC)
Received: from laptop.redhat.com (ovpn-112-58.ams2.redhat.com [10.36.112.58])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 1D68C5C1C6;
        Fri,  3 Apr 2020 07:13:35 +0000 (UTC)
From: Eric Auger <eric.auger@redhat.com>
To: eric.auger.pro@gmail.com, eric.auger@redhat.com, maz@kernel.org,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        qemu-devel@nongnu.org, qemu-arm@nongnu.org
Cc: drjones@redhat.com, andrew.murray@arm.com, andre.przywara@arm.com,
        peter.maydell@linaro.org, alexandru.elisei@arm.com
Subject: [kvm-unit-tests PATCH v4 01/12] arm64: Provide read/write_sysreg_s
Date: Fri,  3 Apr 2020 09:13:15 +0200
Message-Id: <20200403071326.29932-2-eric.auger@redhat.com>
In-Reply-To: <20200403071326.29932-1-eric.auger@redhat.com>
References: <20200403071326.29932-1-eric.auger@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Andrew Jones <drjones@redhat.com>

Sometimes we need to test access to system registers which are
missing assembler mnemonics.

Signed-off-by: Andrew Jones <drjones@redhat.com>
Reviewed-by: Alexandru Elisei <alexandru.elisei@arm.com>
---
 lib/arm64/asm/sysreg.h | 11 +++++++++++
 1 file changed, 11 insertions(+)

```
#### [PATCH v2 1/5] KVM: s390: vsie: Fix region 1 ASCE sanity shadow address checks
##### From: David Hildenbrand <david@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Hildenbrand <david@redhat.com>
X-Patchwork-Id: 11473003
Return-Path: <SRS0=Xk8+=5T=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8489414DD
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Apr 2020 15:31:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 623FB20CC7
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Apr 2020 15:31:34 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="WE5TVmWF"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2404280AbgDCPbG (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 3 Apr 2020 11:31:06 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:55703 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S2404270AbgDCPbF (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 3 Apr 2020 11:31:05 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1585927865;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=KOB528RQaBcIIxwNxgwnDzZl9thgTK4yeE9O3dHXbMk=;
        b=WE5TVmWFEVinsif276lRNhAR6Yw3MkR1+AlW+l85t0gDkJzwR87b1NZs9KwVrPN2nHqyKX
        SYexVrF/k3tlojmj5XdIR0YEVR42Gw1IsQ5KRuMNGTpKZA5kFNcDWHJ2nDP5V/emCpbAeh
        JISZtdr8AZVOXNo9GXFiT6hgt3pPHog=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-350-PkOhlhWAOjGlSOe86hgh-A-1; Fri, 03 Apr 2020 11:31:01 -0400
X-MC-Unique: PkOhlhWAOjGlSOe86hgh-A-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id B2F351005513;
        Fri,  3 Apr 2020 15:30:59 +0000 (UTC)
Received: from t480s.redhat.com (ovpn-112-213.ams2.redhat.com [10.36.112.213])
        by smtp.corp.redhat.com (Postfix) with ESMTP id A79C326DC4;
        Fri,  3 Apr 2020 15:30:57 +0000 (UTC)
From: David Hildenbrand <david@redhat.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, linux-kernel@vger.kernel.org,
        Vasily Gorbik <gor@linux.ibm.com>,
        Heiko Carstens <heiko.carstens@de.ibm.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Janosch Frank <frankja@linux.ibm.com>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        David Hildenbrand <david@redhat.com>, stable@vger.kernel.org
Subject: [PATCH v2 1/5] KVM: s390: vsie: Fix region 1 ASCE sanity shadow
 address checks
Date: Fri,  3 Apr 2020 17:30:46 +0200
Message-Id: <20200403153050.20569-2-david@redhat.com>
In-Reply-To: <20200403153050.20569-1-david@redhat.com>
References: <20200403153050.20569-1-david@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In case we have a region 1 ASCE, our shadow/g3 address can have any value.
Unfortunately, (-1UL << 64) is undefined and triggers sometimes,
rejecting valid shadow addresses when trying to walk our shadow table
hierarchy.

The result is that the prefix cannot get mapped and will loop basically
forever trying to map it (-EAGAIN loop).

After all, the broken check is only a sanity check, our table shadowing
code in kvm_s390_shadow_tables() already checks these conditions, injecting
proper translation exceptions. Turn it into a WARN_ON_ONCE().

Fixes: 4be130a08420 ("s390/mm: add shadow gmap support")
Tested-by: Janosch Frank <frankja@linux.ibm.com>
Reported-by: Janosch Frank <frankja@linux.ibm.com>
Cc: <stable@vger.kernel.org> # v4.8+
Signed-off-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 arch/s390/mm/gmap.c | 6 +++++-
 1 file changed, 5 insertions(+), 1 deletion(-)

```
#### [PATCH kvm-unit-tests v2] s390x: unittests: Use smp parameter
##### From: Andrew Jones <drjones@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11472321
Return-Path: <SRS0=Xk8+=5T=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 85272912
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Apr 2020 09:40:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 539BF208E4
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Apr 2020 09:40:27 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="I6HLiI+5"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2390651AbgDCJk0 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 3 Apr 2020 05:40:26 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:21927 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S2390228AbgDCJk0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 3 Apr 2020 05:40:26 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1585906825;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=52QYJyYJv2m/SL+tJcSL8iQkShlKqG1bBL9lBOP0aCU=;
        b=I6HLiI+5kPnAKiVS2ba9JXJa1AdE4Yk8qffARbaj124KlBLRLygYSSzjaFYTcc63QTJrZK
        rB0snoW7/27HVapZhZGVE2xwf+4iDPTAcAKKGezi7vUJy+UTFrqjvEKkK6K6HyzPFZmJHB
        2IITveBUg2CyiiDbu90TsnkTDlVkv7o=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-260-DYiiXnBuNCCYu1zovg25MQ-1; Fri, 03 Apr 2020 05:40:23 -0400
X-MC-Unique: DYiiXnBuNCCYu1zovg25MQ-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id C5C95190B2A6;
        Fri,  3 Apr 2020 09:40:22 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.40.193.142])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 5AC3B60BF3;
        Fri,  3 Apr 2020 09:40:18 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org
Cc: thuth@redhat.com, david@redhat.com, frankja@linux.ibm.com
Subject: [PATCH kvm-unit-tests v2] s390x: unittests: Use smp parameter
Date: Fri,  3 Apr 2020 11:40:15 +0200
Message-Id: <20200403094015.506838-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Signed-off-by: Andrew Jones <drjones@redhat.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Janosch Frank <frankja@linux.ibm.com>
---

v2: Really just a repost, but also picked up the tags.

 s390x/unittests.cfg | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v2 1/2] selftests: kvm: Add vm_get_fd() in kvm_util
##### From: Wainer dos Santos Moschetta <wainersm@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wainer dos Santos Moschetta <wainersm@redhat.com>
X-Patchwork-Id: 11473201
Return-Path: <SRS0=Xk8+=5T=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1AEDA912
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Apr 2020 17:24:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id EE075207FF
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Apr 2020 17:24:57 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="O+/sK1lD"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2391154AbgDCRYu (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 3 Apr 2020 13:24:50 -0400
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:22837 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S2391126AbgDCRYt (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 3 Apr 2020 13:24:49 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1585934688;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:in-reply-to:in-reply-to:references:references;
        bh=T9VXyQCNLGacVac6lDzMJmSSKgM4vqx/WPWQSRZzIiE=;
        b=O+/sK1lDFqwzR0X2pkeFHwdt2VRplefq63JsLtf1IlFUACwJCKy6ctEl2WoKuE6/5F6JeW
        ws5vjZ23rnvwXKMRyVrD32jBYmpLDCvkjlj5pHo4C0i0s5KznzzdqBOFjM3735OunTJOts
        EOM4PD2tEItWLP6PrrC1g+UYnSUpsrw=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-185-aN-TBCs_Nr6dT7TtaTa2_A-1; Fri, 03 Apr 2020 13:24:43 -0400
X-MC-Unique: aN-TBCs_Nr6dT7TtaTa2_A-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 187DB107ACCC;
        Fri,  3 Apr 2020 17:24:42 +0000 (UTC)
Received: from localhost.localdomain (ovpn-116-15.gru2.redhat.com
 [10.97.116.15])
        by smtp.corp.redhat.com (Postfix) with ESMTP id E0D7A5C1BE;
        Fri,  3 Apr 2020 17:24:38 +0000 (UTC)
From: Wainer dos Santos Moschetta <wainersm@redhat.com>
To: pbonzini@redhat.com, kvm@vger.kernel.org
Cc: drjones@redhat.com, david@redhat.com, linux-kernel@vger.kernel.org,
        linux-kselftest@vger.kernel.org
Subject: [PATCH v2 1/2] selftests: kvm: Add vm_get_fd() in kvm_util
Date: Fri,  3 Apr 2020 14:24:27 -0300
Message-Id: <20200403172428.15574-2-wainersm@redhat.com>
In-Reply-To: <20200403172428.15574-1-wainersm@redhat.com>
References: <20200403172428.15574-1-wainersm@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Introduces the vm_get_fd() function in kvm_util which returns
the VM file descriptor.

Signed-off-by: Wainer dos Santos Moschetta <wainersm@redhat.com>
---
 tools/testing/selftests/kvm/include/kvm_util.h | 1 +
 tools/testing/selftests/kvm/lib/kvm_util.c     | 5 +++++
 2 files changed, 6 insertions(+)

```
#### [PATCH 1/8] tools/virtio: fix virtio_test.c indentation
##### From: =?utf-8?q?Eugenio_P=C3=A9rez?= <eperezma@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: =?utf-8?q?Eugenio_P=C3=A9rez?= <eperezma@redhat.com>
X-Patchwork-Id: 11473165
Return-Path: <SRS0=Xk8+=5T=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EC1B0159A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Apr 2020 16:51:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id C9AD12073B
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Apr 2020 16:51:39 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="ds4VvLH3"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2404079AbgDCQvh (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 3 Apr 2020 12:51:37 -0400
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:29905 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1728095AbgDCQvg (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 3 Apr 2020 12:51:36 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1585932695;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:in-reply-to:in-reply-to:references:references;
        bh=8Hv0uUrFnNOWfNc5i6u80voUI6IiFg7M4Etc0ppl07Y=;
        b=ds4VvLH3+Sh9Hk19DflQBHvy2Gdi90rDBdVMyLk0v/YaYifgHng8AZRaf6iblvCFg/C9+f
        8P0LXm/jNCpGrHtoRPWSFr9g99C/o0TKDllI+KudYXIYhH4mDez0+EN5Rmr/+XmaUApCXu
        /9hJQyDjbU1ec8b17j/jg+EaFWNhI78=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-369-z1n5TK3VMjumBR5MSHdrIQ-1; Fri, 03 Apr 2020 12:51:33 -0400
X-MC-Unique: z1n5TK3VMjumBR5MSHdrIQ-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 7EDF7DBA6;
        Fri,  3 Apr 2020 16:51:31 +0000 (UTC)
Received: from eperezma.remote.csb (ovpn-113-28.ams2.redhat.com
 [10.36.113.28])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 0F7CC18A85;
        Fri,  3 Apr 2020 16:51:28 +0000 (UTC)
From: =?utf-8?q?Eugenio_P=C3=A9rez?= <eperezma@redhat.com>
To: "Michael S. Tsirkin" <mst@redhat.com>
Cc: kvm list <kvm@vger.kernel.org>,
 "virtualization@lists.linux-foundation.org"
  <virtualization@lists.linux-foundation.org>,
 Linux Next Mailing List <linux-next@vger.kernel.org>, =?utf-8?q?Eugenio_P?=
	=?utf-8?q?=C3=A9rez?= <eperezma@redhat.com>,
 Stephen Rothwell <sfr@canb.auug.org.au>, Cornelia Huck <cohuck@redhat.com>,
 Halil Pasic <pasic@linux.ibm.com>,
 "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>,
 Christian Borntraeger <borntraeger@de.ibm.com>
Subject: [PATCH 1/8] tools/virtio: fix virtio_test.c indentation
Date: Fri,  3 Apr 2020 18:51:12 +0200
Message-Id: <20200403165119.5030-2-eperezma@redhat.com>
In-Reply-To: <20200403165119.5030-1-eperezma@redhat.com>
References: <20200403165119.5030-1-eperezma@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

---
 tools/virtio/virtio_test.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v3 1/2] virtio/test: fix up after IOTLB changes
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 11473067
Return-Path: <SRS0=Xk8+=5T=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 80F431392
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Apr 2020 16:10:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5425D208FE
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Apr 2020 16:10:36 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Z7e1NsU6"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2404133AbgDCQKf (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 3 Apr 2020 12:10:35 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:35645 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1728351AbgDCQKf (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 3 Apr 2020 12:10:35 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1585930233;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=HxGDx8xMWngtG+W7aIWS1cH1WkrfSib7IwRlpCopMt0=;
        b=Z7e1NsU6nw7FIGYfeznkl9r0ITcHEJGk/G460nxwlhjJbwrUs+/bJNEwny0FlLhkV5lQQA
        PtBUOqYW7TXSdAs0GmaHJcrn59Ay1qc4tioPuOjii19Ov/VVD6UupyTwO25fDdmJIypugX
        D/LXpmlxPdcykMTzoFuR4pKlJs207Bg=
Received: from mail-wr1-f72.google.com (mail-wr1-f72.google.com
 [209.85.221.72]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-46-lZX97i_BNIO43clW2hQRrA-1; Fri, 03 Apr 2020 12:10:32 -0400
X-MC-Unique: lZX97i_BNIO43clW2hQRrA-1
Received: by mail-wr1-f72.google.com with SMTP id m15so3338875wrb.0
        for <kvm@vger.kernel.org>; Fri, 03 Apr 2020 09:10:31 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:references
         :mime-version:content-disposition:content-transfer-encoding
         :in-reply-to;
        bh=HxGDx8xMWngtG+W7aIWS1cH1WkrfSib7IwRlpCopMt0=;
        b=pLFbhpklCORUeu7gYkIX2XlkZI6HjTUbZNqvrOOOLy5FJyhgfhDoJCUpeoXr3tJBBN
         cyYsJRkpl1nQIK7mPj2a/IEoi7nKIK+ePDA2bevZjCFATvOjCL74UvCdMz7QNrOwKeaj
         aN246mFqt3EKt5g8NFqe3Xko+6V7noF6vRqmb/LnP2zbk+voX6ZVV+OxGMIiCB/stsjs
         nDADyoBltWHFt27FMIEGo1nWvjscVxrGi03bMrSC1ZoxtUslL3HymrRVur8NU3ZEAPMo
         3NyZ8P/Czx8HF2VQR2lUv3qG7tmv7f5zvhff2CwmezZr9ulK5XZhphAVF7CFjJIzAudJ
         wkvw==
X-Gm-Message-State: AGi0PuaUeFbADRFAuicLd6vtTRu80qQopTEVHKeyVve72k50w5HCyBaB
        Y5sDrJL7wW2TXYklxAtP4oPZTmRhDYqds/t7uPhJ4uFZTZqwYjW2uY91sGQc/2mvvrHZiDq4E54
        qXBx9hOU2i07C
X-Received: by 2002:adf:92a3:: with SMTP id 32mr1691695wrn.254.1585930230641;
        Fri, 03 Apr 2020 09:10:30 -0700 (PDT)
X-Google-Smtp-Source: 
 APiQypLmrG+TV47aCCJhBBP60hCAWxJr4RwtTXo78EGqzfC86StxChKcxJSpL+guDENdVCsWHZ1/gQ==
X-Received: by 2002:adf:92a3:: with SMTP id 32mr1691673wrn.254.1585930230347;
        Fri, 03 Apr 2020 09:10:30 -0700 (PDT)
Received: from redhat.com (bzq-79-176-51-222.red.bezeqint.net.
 [79.176.51.222])
        by smtp.gmail.com with ESMTPSA id
 f141sm12222545wmf.3.2020.04.03.09.10.29
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 03 Apr 2020 09:10:29 -0700 (PDT)
Date: Fri, 3 Apr 2020 12:10:28 -0400
From: "Michael S. Tsirkin" <mst@redhat.com>
To: linux-kernel@vger.kernel.org
Cc: Jason Wang <jasowang@redhat.com>,
 Eugenio =?utf-8?b?UMOpcmV6?= <eperezma@redhat.com>, kvm@vger.kernel.org,
 virtualization@lists.linux-foundation.org, netdev@vger.kernel.org
Subject: [PATCH v3 1/2] virtio/test: fix up after IOTLB changes
Message-ID: <20200403161011.13046-2-mst@redhat.com>
References: <20200403161011.13046-1-mst@redhat.com>
MIME-Version: 1.0
Content-Disposition: inline
In-Reply-To: <20200403161011.13046-1-mst@redhat.com>
X-Mailer: git-send-email 2.24.1.751.gd10ce2899c
X-Mutt-Fcc: =sent
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Allow building vringh without IOTLB (that's the case for userspace
builds, will be useful for CAIF/VOD down the road too).
Update for API tweaks.
Don't include vringh with userspace builds.

Cc: Jason Wang <jasowang@redhat.com>
Cc: Eugenio Pérez <eperezma@redhat.com>
Signed-off-by: Michael S. Tsirkin <mst@redhat.com>
Acked-by: Jason Wang <jasowang@redhat.com>
---
 drivers/vhost/Kconfig             | 2 ++
 drivers/vhost/test.c              | 4 ++--
 drivers/vhost/vringh.c            | 5 +++++
 include/linux/vringh.h            | 6 ++++++
 tools/virtio/Makefile             | 5 +++--
 tools/virtio/generated/autoconf.h | 0
 6 files changed, 18 insertions(+), 4 deletions(-)
 create mode 100644 tools/virtio/generated/autoconf.h

```
