#### [PATCH v9 01/10] Documentation: Add EPT based Subpage Protection and related APIs
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Weijiang <weijiang.yang@intel.com>
X-Patchwork-Id: 11275779
Return-Path: <SRS0=PSGZ=Z4=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9DFA1138D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Dec 2019 08:25:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7267124677
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Dec 2019 08:25:13 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726831AbfLFIZJ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 6 Dec 2019 03:25:09 -0500
Received: from mga06.intel.com ([134.134.136.31]:25868 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726278AbfLFIZJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 6 Dec 2019 03:25:09 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga001.jf.intel.com ([10.7.209.18])
  by orsmga104.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 06 Dec 2019 00:25:08 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.69,283,1571727600";
   d="scan'208";a="294797911"
Received: from local-michael-cet-test.sh.intel.com ([10.239.159.128])
  by orsmga001.jf.intel.com with ESMTP; 06 Dec 2019 00:25:06 -0800
From: Yang Weijiang <weijiang.yang@intel.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        pbonzini@redhat.com, jmattson@google.com,
        sean.j.christopherson@intel.com
Cc: yu.c.zhang@linux.intel.com, alazar@bitdefender.com,
        edwin.zhai@intel.com, Yang Weijiang <weijiang.yang@intel.com>
Subject: [PATCH v9 01/10] Documentation: Add EPT based Subpage Protection and
 related APIs
Date: Fri,  6 Dec 2019 16:26:25 +0800
Message-Id: <20191206082634.21042-2-weijiang.yang@intel.com>
X-Mailer: git-send-email 2.17.2
In-Reply-To: <20191206082634.21042-1-weijiang.yang@intel.com>
References: <20191206082634.21042-1-weijiang.yang@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Co-developed-by: yi.z.zhang@linux.intel.com
Signed-off-by: yi.z.zhang@linux.intel.com
Signed-off-by: Yang Weijiang <weijiang.yang@intel.com>
---
 Documentation/virt/kvm/api.txt        |  38 ++++++
 Documentation/virtual/kvm/spp_kvm.txt | 179 ++++++++++++++++++++++++++
 2 files changed, 217 insertions(+)
 create mode 100644 Documentation/virtual/kvm/spp_kvm.txt

```
#### [GIT PULL] VFIO updates for v5.5-rc1
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alex Williamson <alex.williamson@redhat.com>
X-Patchwork-Id: 11276931
Return-Path: <SRS0=PSGZ=Z4=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B0B82112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Dec 2019 18:22:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 8F21324677
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Dec 2019 18:22:33 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Cr93jeQW"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726350AbfLFSWc (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 6 Dec 2019 13:22:32 -0500
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:25747 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726298AbfLFSWc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 6 Dec 2019 13:22:32 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1575656551;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=pkO2zZFmgQehl/A8nk21THxwcIqs5vjrYyeZ+q3C/Nk=;
        b=Cr93jeQWMdg5kBFM60+z+DPcRbgSN0FTk6PDmNRt5GOonNKi4fxcmpkXPK6b8BBCTGjqzU
        Ru/o9Vt8yZFNt33a/pD4EvWP1+LFApQo+OxP1iE5o5a+rsKqaX7MVy0ZYYLaFYz4Jg58xT
        87DqN2CqjzsT9QCT1GOGS5HIESVP1+4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-333-S58x6o8wPNCLHbUrxi5mBA-1; Fri, 06 Dec 2019 13:22:30 -0500
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 0D070800D4C;
        Fri,  6 Dec 2019 18:22:29 +0000 (UTC)
Received: from x1.home (ovpn-116-56.phx2.redhat.com [10.3.116.56])
        by smtp.corp.redhat.com (Postfix) with ESMTP id AD5D6608A5;
        Fri,  6 Dec 2019 18:22:28 +0000 (UTC)
Date: Fri, 6 Dec 2019 11:22:27 -0700
From: Alex Williamson <alex.williamson@redhat.com>
To: Linus Torvalds <torvalds@linux-foundation.org>
Cc: "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>,
        "kvm@vger.kernel.org" <kvm@vger.kernel.org>
Subject: [GIT PULL] VFIO updates for v5.5-rc1
Message-ID: <20191206112227.53e15607@x1.home>
Organization: Red Hat
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
X-MC-Unique: S58x6o8wPNCLHbUrxi5mBA-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Linus,

The following changes since commit 4f5cafb5cb8471e54afdc9054d973535614f7675:

  Linux 5.4-rc3 (2019-10-13 16:37:36 -0700)

are available in the Git repository at:

  git://github.com/awilliam/linux-vfio.git tags/vfio-v5.5-rc1

for you to fetch changes up to 9917b54aded12dff9beb9e709981617b788e44b0:

  Merge branch 'v5.5/vfio/jiang-yi-irq-bypass-unregister-v1' into v5.5/vfio/next (2019-12-04 10:15:56 -0700)

----------------------------------------------------------------
VFIO updates for v5.5-rc1

 - Remove hugepage checks for reserved pfns (Ben Luo)

 - Fix irq-bypass unregister ordering (Jiang Yi)

----------------------------------------------------------------
Alex Williamson (1):
      Merge branch 'v5.5/vfio/jiang-yi-irq-bypass-unregister-v1' into v5.5/vfio/next

Ben Luo (1):
      vfio/type1: remove hugepage checks in is_invalid_reserved_pfn()

Jiang Yi (1):
      vfio/pci: call irq_bypass_unregister_producer() before freeing irq

 drivers/vfio/pci/vfio_pci_intrs.c |  2 +-
 drivers/vfio/vfio_iommu_type1.c   | 26 ++++----------------------
 2 files changed, 5 insertions(+), 23 deletions(-)
```
#### [kvm-unit-tests RFC 01/10] arm64: Provide read/write_sysreg_s
##### From: Eric Auger <eric.auger@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Auger <eric.auger@redhat.com>
X-Patchwork-Id: 11276875
Return-Path: <SRS0=PSGZ=Z4=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 61BDE13B6
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Dec 2019 17:27:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 35B0924659
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Dec 2019 17:27:44 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="GqWKDFaN"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726388AbfLFR1n (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 6 Dec 2019 12:27:43 -0500
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:52824 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726287AbfLFR1n (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 6 Dec 2019 12:27:43 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1575653262;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=82q1ODmkZ7c1oPzZoGIi16jb3fC0s7ZgyAm8HyUNG/k=;
        b=GqWKDFaN1Wm9fSEJbCykqP9EPZCrn/NTMaKlhErAReFctSzaePjnd1kyiNftswvAukaybB
        kX0s8W6I391/vTmlXTeMx6Bb06EyfGP5X7c5b6PMNru1hGfiEoXWwEVnk50+nC/SATJx82
        iJLGUYnxO2W0RFEoaDbi2dQZdX92jGI=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-139-am3fbLFtNLK_jb0VJtV8MA-1; Fri, 06 Dec 2019 12:27:40 -0500
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 1CBB3800580;
        Fri,  6 Dec 2019 17:27:39 +0000 (UTC)
Received: from laptop.redhat.com (ovpn-116-117.ams2.redhat.com
 [10.36.116.117])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 3E9436CE40;
        Fri,  6 Dec 2019 17:27:34 +0000 (UTC)
From: Eric Auger <eric.auger@redhat.com>
To: eric.auger.pro@gmail.com, eric.auger@redhat.com, maz@kernel.org,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        qemu-devel@nongnu.org, qemu-arm@nongnu.org
Cc: drjones@redhat.com, andrew.murray@arm.com, andre.przywara@arm.com,
        peter.maydell@linaro.org
Subject: [kvm-unit-tests RFC 01/10] arm64: Provide read/write_sysreg_s
Date: Fri,  6 Dec 2019 18:27:15 +0100
Message-Id: <20191206172724.947-2-eric.auger@redhat.com>
In-Reply-To: <20191206172724.947-1-eric.auger@redhat.com>
References: <20191206172724.947-1-eric.auger@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
X-MC-Unique: am3fbLFtNLK_jb0VJtV8MA-1
X-Mimecast-Spam-Score: 0
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
#### [PATCH] KVM: Radim is no longer available as KVM maintainer
##### From: Thomas Huth <thuth@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Thomas Huth <thuth@redhat.com>
X-Patchwork-Id: 11276169
Return-Path: <SRS0=PSGZ=Z4=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F307E13B6
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Dec 2019 13:45:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D1D0C24675
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Dec 2019 13:45:33 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="K724XoU7"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726332AbfLFNpa (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 6 Dec 2019 08:45:30 -0500
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:34723 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726312AbfLFNpa (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 6 Dec 2019 08:45:30 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1575639929;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=AxChkYm0yBQdYCSo9K5fS2Y6ct4oJJSVzt3QR9uwmtY=;
        b=K724XoU700/1AIR8XOWIU1DAPma+R3a5w5B3WLgIBP+bhJqYTa2/s1u01foINIwS6EkoHL
        DmJqTgUPcTt07Zp91ozuZftEyApAuKFpl4SJXsrhhkmLHdABhKbOjEQ/bzW6tabQ4uRo2U
        gAn2GZdrSJpJV4OoxzBXmBa5Fl3BqLk=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-312-I2YEdcGCO4uHrjah08uYYg-1; Fri, 06 Dec 2019 08:45:23 -0500
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id A78F78017DF;
        Fri,  6 Dec 2019 13:45:21 +0000 (UTC)
Received: from thuth.com (ovpn-116-205.ams2.redhat.com [10.36.116.205])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 5E2006B8F0;
        Fri,  6 Dec 2019 13:45:14 +0000 (UTC)
From: Thomas Huth <thuth@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>,
        linux-kernel@vger.kernel.org
Cc: rkrcmar@redhat.com, radimkrcmar@gmail.com, drjones@redhat.com,
        stable@vger.kernel.org, sean.j.christopherson@intel.com,
        vkuznets@redhat.com, wanpengli@tencent.com, jmattson@google.com,
        joro@8bytes.org
Subject: [PATCH] KVM: Radim is no longer available as KVM maintainer
Date: Fri,  6 Dec 2019 14:45:11 +0100
Message-Id: <20191206134511.20036-1-thuth@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
X-MC-Unique: I2YEdcGCO4uHrjah08uYYg-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Radim's mail address @redhat.com is not valid anymore, so we should
remove this line from the MAINTAINERS file to avoid that people send
mails to this address in vain.

Thank you very much for all your work on KVM during the past years,
Radim!

Signed-off-by: Thomas Huth <thuth@redhat.com>
---
 MAINTAINERS | 2 --
 1 file changed, 2 deletions(-)

```
#### [kvm-unit-tests PATCH] MAINTAINERS: Radim is no longer available as kvm-unit-tests maintainer
##### From: Thomas Huth <thuth@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Thomas Huth <thuth@redhat.com>
X-Patchwork-Id: 11276123
Return-Path: <SRS0=PSGZ=Z4=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 15E17930
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Dec 2019 13:15:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id DC21E2464E
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Dec 2019 13:15:46 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="ZC/KaW7I"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726244AbfLFNPp (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 6 Dec 2019 08:15:45 -0500
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:47405 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726128AbfLFNPp (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 6 Dec 2019 08:15:45 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1575638144;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=MLDnBsWA2sFSFtoTw/NU467cHCiZwmFim8KHvfPZ3+E=;
        b=ZC/KaW7Ik22wtHI+WJXm9q9PTNK+WSN7FzUZ/bEBs3uvn2MHpi/yy7e19v1g2cTJfGpEbG
        DDGyhKVjFBtP+PCTwWhahpyRYdLGEX6Vy/01cEHa0gmY1SjxtMTQE6F7Ce84j2xhkuD9GU
        eyLPrXlwXsbJt22w+bgBCPYbtnJlRYI=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-48--0ksnmB9PiW1ROw1eCvRsw-1; Fri, 06 Dec 2019 08:15:43 -0500
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id A8A3518036B3;
        Fri,  6 Dec 2019 13:15:42 +0000 (UTC)
Received: from thuth.com (ovpn-116-205.ams2.redhat.com [10.36.116.205])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 85EC25DA32;
        Fri,  6 Dec 2019 13:15:38 +0000 (UTC)
From: Thomas Huth <thuth@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: rkrcmar@redhat.com, radimkrcmar@gmail.com, drjones@redhat.com
Subject: [kvm-unit-tests PATCH] MAINTAINERS: Radim is no longer available as
 kvm-unit-tests maintainer
Date: Fri,  6 Dec 2019 14:15:34 +0100
Message-Id: <20191206131534.18509-1-thuth@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
X-MC-Unique: -0ksnmB9PiW1ROw1eCvRsw-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Radim's mail address @redhat.com is not valid anymore, so we should
remove this line from the MAINTAINERS file.

Thanks for all your work on kvm-unit-tests during the past years, Radim!

Signed-off-by: Thomas Huth <thuth@redhat.com>
---
 MAINTAINERS | 2 --
 1 file changed, 2 deletions(-)

```
#### [PATCH] KVM: x86: Fix some comment typos
##### From: linmiaohe <linmiaohe@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: linmiaohe <linmiaohe@huawei.com>
X-Patchwork-Id: 11275765
Return-Path: <SRS0=PSGZ=Z4=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3964814BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Dec 2019 08:21:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 20D142467A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Dec 2019 08:21:06 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726444AbfLFIVC (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 6 Dec 2019 03:21:02 -0500
Received: from szxga05-in.huawei.com ([45.249.212.191]:7195 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726088AbfLFIVB (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 6 Dec 2019 03:21:01 -0500
Received: from DGGEMS405-HUB.china.huawei.com (unknown [172.30.72.60])
        by Forcepoint Email with ESMTP id 86107F4CE85D0C8DBBF5;
        Fri,  6 Dec 2019 16:20:59 +0800 (CST)
Received: from huawei.com (10.175.105.18) by DGGEMS405-HUB.china.huawei.com
 (10.3.19.205) with Microsoft SMTP Server id 14.3.439.0; Fri, 6 Dec 2019
 16:20:24 +0800
From: linmiaohe <linmiaohe@huawei.com>
To: <pbonzini@redhat.com>, <rkrcmar@redhat.com>,
        <sean.j.christopherson@intel.com>, <vkuznets@redhat.com>,
        <wanpengli@tencent.com>, <jmattson@google.com>, <joro@8bytes.org>,
        <tglx@linutronix.de>, <mingo@redhat.com>, <bp@alien8.de>,
        <hpa@zytor.com>
CC: <linmiaohe@huawei.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <x86@kernel.org>
Subject: [PATCH] KVM: x86: Fix some comment typos
Date: Fri, 6 Dec 2019 16:20:18 +0800
Message-ID: <1575620418-19011-1-git-send-email-linmiaohe@huawei.com>
X-Mailer: git-send-email 1.8.3.1
MIME-Version: 1.0
X-Originating-IP: [10.175.105.18]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Miaohe Lin <linmiaohe@huawei.com>

Fix some typos in comment.

Signed-off-by: Miaohe Lin <linmiaohe@huawei.com>
---
 arch/x86/kvm/mmu/mmu.c | 2 +-
 arch/x86/kvm/vmx/vmx.c | 2 +-
 arch/x86/kvm/x86.c     | 2 +-
 3 files changed, 3 insertions(+), 3 deletions(-)

```
#### [PATCH 1/3] KVM: VMX: Rename INTERRUPT_PENDING to INTERRUPT_WINDOW
##### From: Xiaoyao Li <xiaoyao.li@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xiaoyao Li <xiaoyao.li@intel.com>
X-Patchwork-Id: 11275831
Return-Path: <SRS0=PSGZ=Z4=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9E55B14B7
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Dec 2019 09:01:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7EEF720659
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Dec 2019 09:01:54 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726416AbfLFJBm (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 6 Dec 2019 04:01:42 -0500
Received: from mga09.intel.com ([134.134.136.24]:50484 "EHLO mga09.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726065AbfLFJBj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 6 Dec 2019 04:01:39 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by orsmga102.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 06 Dec 2019 01:01:39 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.69,283,1571727600";
   d="scan'208";a="219395090"
Received: from lxy-clx-4s.sh.intel.com ([10.239.43.57])
  by fmsmga001.fm.intel.com with ESMTP; 06 Dec 2019 01:01:37 -0800
From: Xiaoyao Li <xiaoyao.li@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Shuah Khan <shuah@kernel.org>
Cc: Xiaoyao Li <xiaoyao.li@intel.com>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, linux-kselftest@vger.kernel.org
Subject: [PATCH 1/3] KVM: VMX: Rename INTERRUPT_PENDING to INTERRUPT_WINDOW
Date: Fri,  6 Dec 2019 16:45:24 +0800
Message-Id: <20191206084526.131861-2-xiaoyao.li@intel.com>
X-Mailer: git-send-email 2.19.1
In-Reply-To: <20191206084526.131861-1-xiaoyao.li@intel.com>
References: <20191206084526.131861-1-xiaoyao.li@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Rename interrupt-windown exiting related definitions to match the
latest Intel SDM. No functional changes.

Signed-off-by: Xiaoyao Li <xiaoyao.li@intel.com>
---
 arch/x86/include/asm/vmx.h                       |  2 +-
 arch/x86/include/uapi/asm/vmx.h                  |  4 ++--
 arch/x86/kvm/vmx/nested.c                        | 12 ++++++------
 arch/x86/kvm/vmx/vmx.c                           | 10 +++++-----
 tools/arch/x86/include/uapi/asm/vmx.h            |  4 ++--
 tools/testing/selftests/kvm/include/x86_64/vmx.h |  4 ++--
 6 files changed, 18 insertions(+), 18 deletions(-)

```
#### [kvm-unit-tests PATCH v3 1/9] s390x: saving regs for interrupts
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 11276777
Return-Path: <SRS0=PSGZ=Z4=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C29FE17EF
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Dec 2019 16:26:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A9D8C20659
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Dec 2019 16:26:38 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726395AbfLFQ0h (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 6 Dec 2019 11:26:37 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:37850 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726315AbfLFQ0g (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 6 Dec 2019 11:26:36 -0500
Received: from pps.filterd (m0098410.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 xB6GEoLl068873
        for <kvm@vger.kernel.org>; Fri, 6 Dec 2019 11:26:35 -0500
Received: from e06smtp05.uk.ibm.com (e06smtp05.uk.ibm.com [195.75.94.101])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2wq9g6c90b-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Fri, 06 Dec 2019 11:26:35 -0500
Received: from localhost
        by e06smtp05.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <pmorel@linux.ibm.com>;
        Fri, 6 Dec 2019 16:26:33 -0000
Received: from b06cxnps4074.portsmouth.uk.ibm.com (9.149.109.196)
        by e06smtp05.uk.ibm.com (192.168.101.135) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Fri, 6 Dec 2019 16:26:31 -0000
Received: from d06av21.portsmouth.uk.ibm.com (d06av21.portsmouth.uk.ibm.com
 [9.149.105.232])
        by b06cxnps4074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id xB6GQUi352232390
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 6 Dec 2019 16:26:30 GMT
Received: from d06av21.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 23AD452052;
        Fri,  6 Dec 2019 16:26:30 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.175.63])
        by d06av21.portsmouth.uk.ibm.com (Postfix) with ESMTP id BE02D52054;
        Fri,  6 Dec 2019 16:26:29 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, frankja@linux.ibm.com,
        david@redhat.com, thuth@redhat.com, cohuck@redhat.com
Subject: [kvm-unit-tests PATCH v3 1/9] s390x: saving regs for interrupts
Date: Fri,  6 Dec 2019 17:26:20 +0100
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1575649588-6127-1-git-send-email-pmorel@linux.ibm.com>
References: <1575649588-6127-1-git-send-email-pmorel@linux.ibm.com>
X-TM-AS-GCONF: 00
x-cbid: 19120616-0020-0000-0000-0000039509A5
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19120616-0021-0000-0000-000021EC3DE7
Message-Id: <1575649588-6127-2-git-send-email-pmorel@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.95,18.0.572
 definitions=2019-12-06_05:2019-12-05,2019-12-06 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 malwarescore=0
 priorityscore=1501 clxscore=1015 mlxscore=0 impostorscore=0 bulkscore=0
 mlxlogscore=696 suspectscore=1 adultscore=0 phishscore=0 spamscore=0
 lowpriorityscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-1910280000 definitions=main-1912060136
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If we use multiple source of interrupts, for exemple, using SCLP
console to print information while using I/O interrupts, we need
to have a re-entrant register saving interruption handling.

Instead of saving at a static memory address, let's save the base
registers and the floating point registers on the stack.

Note that we keep the static register saving to recover from the
RESET tests.

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
---
 s390x/cstart64.S | 25 +++++++++++++++++++++++--
 1 file changed, 23 insertions(+), 2 deletions(-)

```
#### [PATCH] target/i386: skip kvm_msr_entry_add when kvm_vmx_basic is 0
##### From: Catherine Ho <catherine.hecx@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Catherine Ho <catherine.hecx@gmail.com>
X-Patchwork-Id: 11275945
Return-Path: <SRS0=PSGZ=Z4=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 12E58930
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Dec 2019 10:25:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D8D0E2245C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Dec 2019 10:25:35 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="OfA4h5x4"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726201AbfLFKZe (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 6 Dec 2019 05:25:34 -0500
Received: from mail-qk1-f193.google.com ([209.85.222.193]:44105 "EHLO
        mail-qk1-f193.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726070AbfLFKZe (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 6 Dec 2019 05:25:34 -0500
Received: by mail-qk1-f193.google.com with SMTP id i18so6020386qkl.11
        for <kvm@vger.kernel.org>; Fri, 06 Dec 2019 02:25:34 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:in-reply-to:references;
        bh=poU4coC1wpEnGRHnApg5z8cKyUslXoAMtkEQeEix3YE=;
        b=OfA4h5x466F13+EJ6RAM3rEK2XQXeqRQWVoYD9x7iKGEqTUVkJVKX2xdBb0uK7Wiy8
         +K3lV6Ttr9mWyHEWzqLfsOXpVaoyIgO0Z7sucDUc5ml8tWFEQx/VSTgDfzKC/7ts+9tw
         Uo0K8cEOVQCNU+30QTyVLUHJ2glanPx6QqbpFY+xVb6A3XF0oMul+CpcqSe8Z35w2dZo
         ewoSVe3v+Tq8NBBaubsauIIlFA/zUxnBp8Pw/r37SJwO+aI5dxmsVQ7EzGHFv/9Bo/ks
         M4iMFTRX1g39U7AWBmfcXeI9aiBakRBcEVi2x8Bs2FWOfBsJCaLVK7xPUmK3LcBKuPUg
         94Jg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references;
        bh=poU4coC1wpEnGRHnApg5z8cKyUslXoAMtkEQeEix3YE=;
        b=i4iYGRggECSdrAteE2tNY9x1bEAb1L5rrxOscGrgNaP4c3xzxheMgi7s3TF3BWksoG
         bPe0/mgLAg7tVWL7TRKze/BnZ+8ZRWxoINXNMlAIPZmoZj9/ZXyWqGX0EA8Jjog5RVHF
         FsKlsczb4v6fg+npwEv7Qov0xiEwdm86wdqxTWe3b78FW/zk+MVsRS41syj4D/h+2KMd
         W9ptlPjwb59SXXonxNfL3g9idY8E5b+O1E77jr6BwxTafG+VtgCtr/RG09plUslNZZeQ
         B/6+AcVTK25Rr8/gPTDfr4PzKrD/txjj0R4Ur0QXn62/CkRLx7R1wXwyK3u/dh8q3Nmo
         Et5A==
X-Gm-Message-State: APjAAAXb76/pB10kV/INuU9kD+5+HfzBMrGR7V4IV/xevCzKfVs1tCMJ
        pZTsBIJnE9LabDKaPo0oIlI=
X-Google-Smtp-Source: 
 APXvYqyHAGUvqCWHS5evYFAogikSLDtFd1xrmclCYnoYpwWw+dIWtypuzUWGf2XoUfxoQEICD0mGNQ==
X-Received: by 2002:a37:a257:: with SMTP id l84mr13084095qke.22.1575627933529;
        Fri, 06 Dec 2019 02:25:33 -0800 (PST)
Received: from host.localdomain (104.129.187.94.16clouds.com.
 [104.129.187.94])
        by smtp.gmail.com with ESMTPSA id
 o7sm2117654qkd.119.2019.12.06.02.25.31
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Fri, 06 Dec 2019 02:25:32 -0800 (PST)
From: Catherine Ho <catherine.hecx@gmail.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Marcelo Tosatti <mtosatti@redhat.com>, qemu-devel@nongnu.org
Cc: Richard Henderson <rth@twiddle.net>,
        Eduardo Habkost <ehabkost@redhat.com>, kvm@vger.kernel.org,
        Catherine Ho <catherine.hecx@gmail.com>,
        Paolo Bonzini <pbonzini@redhat.com>
Subject: [PATCH] target/i386: skip kvm_msr_entry_add when kvm_vmx_basic is 0
Date: Fri,  6 Dec 2019 05:23:37 -0500
Message-Id: <1575627817-24625-1-git-send-email-catherine.hecx@gmail.com>
X-Mailer: git-send-email 1.7.1
In-Reply-To: <3a1c97b2-789f-dd21-59ba-f780cf3bad92@redhat.com>
References: <3a1c97b2-789f-dd21-59ba-f780cf3bad92@redhat.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Commit 1389309c811b ("KVM: nVMX: expose VMX capabilities for nested
hypervisors to userspace") expands the msr_based_features with
MSR_IA32_VMX_BASIC and others. Then together with an old kernel before
1389309c811b, the qemu call KVM_GET_MSR_FEATURE_INDEX_LIST and got the
smaller kvm_feature_msrs. Then in kvm_arch_get_supported_msr_feature(),
searching VMX_BASIC will be failed and return 0. At last kvm_vmx_basic
will be assigned to 0.

Without this patch, it will cause a qemu crash (host kernel 4.15
ubuntu 18.04+qemu 4.1):
qemu-system-x86_64: error: failed to set MSR 0x480 to 0x0
target/i386/kvm.c:2932: kvm_put_msrs: Assertion `ret ==
cpu->kvm_msr_buf->nmsrs' failed.

This fixes it by skipping kvm_msr_entry_add when kvm_vmx_basic is 0

Cc: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Catherine Ho <catherine.hecx@gmail.com>
---
 target/i386/kvm.c |    7 ++++++-
 1 files changed, 6 insertions(+), 1 deletions(-)

```
#### [PATCH 1/2] KVM: lib: use jump label to handle resource release in irq_bypass_register_consumer()
##### From: linmiaohe <linmiaohe@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: linmiaohe <linmiaohe@huawei.com>
X-Patchwork-Id: 11275605
Return-Path: <SRS0=PSGZ=Z4=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BBD29112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Dec 2019 02:54:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A47CF21823
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Dec 2019 02:54:27 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726278AbfLFCyJ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 5 Dec 2019 21:54:09 -0500
Received: from szxga05-in.huawei.com ([45.249.212.191]:6759 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726076AbfLFCyJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 5 Dec 2019 21:54:09 -0500
Received: from DGGEMS407-HUB.china.huawei.com (unknown [172.30.72.58])
        by Forcepoint Email with ESMTP id B083F64EF77D563497E7;
        Fri,  6 Dec 2019 10:54:07 +0800 (CST)
Received: from huawei.com (10.175.105.18) by DGGEMS407-HUB.china.huawei.com
 (10.3.19.207) with Microsoft SMTP Server id 14.3.439.0; Fri, 6 Dec 2019
 10:53:59 +0800
From: linmiaohe <linmiaohe@huawei.com>
To: <pbonzini@redhat.com>, <alex.williamson@redhat.com>
CC: <linmiaohe@huawei.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>
Subject: [PATCH 1/2] KVM: lib: use jump label to handle resource release in
 irq_bypass_register_consumer()
Date: Fri, 6 Dec 2019 10:53:52 +0800
Message-ID: <1575600833-12839-2-git-send-email-linmiaohe@huawei.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1575600833-12839-1-git-send-email-linmiaohe@huawei.com>
References: <1575600833-12839-1-git-send-email-linmiaohe@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.175.105.18]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Miaohe Lin <linmiaohe@huawei.com>

Use out_err jump label to handle resource release. It's a
good practice to release resource in one place and help
eliminate some duplicated code.

Signed-off-by: Miaohe Lin <linmiaohe@huawei.com>
---
 virt/lib/irqbypass.c | 19 ++++++++++---------
 1 file changed, 10 insertions(+), 9 deletions(-)

```
#### [PATCH v2 1/3] kvm: nVMX: VMWRITE checks VMCS-link pointer before VMCS field
##### From: Jim Mattson <jmattson@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jim Mattson <jmattson@google.com>
X-Patchwork-Id: 11276997
Return-Path: <SRS0=PSGZ=Z4=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2F03E112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Dec 2019 19:32:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id F2A15206DF
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Dec 2019 19:32:08 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="RRvSp2mJ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726371AbfLFTcI (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 6 Dec 2019 14:32:08 -0500
Received: from mail-pj1-f73.google.com ([209.85.216.73]:35998 "EHLO
        mail-pj1-f73.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726321AbfLFTcH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 6 Dec 2019 14:32:07 -0500
Received: by mail-pj1-f73.google.com with SMTP id h6so788176pju.3
        for <kvm@vger.kernel.org>; Fri, 06 Dec 2019 11:32:06 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=j4XRHZCw0G2Q9oTbXX5ca2bK+8yfDz21ed70QhN9JTs=;
        b=RRvSp2mJGwiPRXJINZ0d820tblpaR+vgxnDgRXYJ37hlvL+LDcNMD3idv+oMM5CeYW
         9ftVgLfbCH5tXV/lu5zWDBFDlQlYG4oi5gNNEmBzMy/CjTgiuGG8ZEZy3yWR9JAPn5g5
         CCPkN4FJ1B16fE2+aNjtImSXc/qUouGnn9Nkp8fDyGEDMBlGkHnlWRMCz5zO13ejE5vm
         8lKZaowfg1W4gq6bbabcGihDfGrMff3v62RDM1IYS42rfk3PIAk1/i79xipFIDy9OWtg
         mosBge7FW6dkeoMS/pHwo0YcVVam4Z1QSH8+UWiipb7HKaGc2v5gZ+7TUn5UgFjuKOVK
         Xx+w==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=j4XRHZCw0G2Q9oTbXX5ca2bK+8yfDz21ed70QhN9JTs=;
        b=Wz9XodCmUG7zzglCSDj5ioDtCyVvyee+fcrp1xWQf1dtGr7YjSd/Bf7xQCSSVBJfe1
         NzWsUhhgO6Tu7Nd1HU/UT0PO5zHBVCGLVlaQD5yaqzedrP9AHTrD6JoLKxwpnLQSGHX4
         3ps67vbOsqYwVJMXoDmK4boHMXdTdzxFOiOdkhcRpLtu5X79jivDkExKNeJkAh0TPPi2
         k6rdHHaw8cJwKn/yghOlSP+UzHkHZxmOOG14bFvV5c3bY7kyhUy3YCcnjwhHweBTLiUI
         yxSAlAa8SUAwVzZnpmJhoD8pZ7tTmQ2bBYAo7rzR3B/BREeF3Vh9FQl61RQV+nzfqr+f
         /W/w==
X-Gm-Message-State: APjAAAWVjVSDrZJJ/yE7IBSJvVeAcVE6ZNhGab+x8JbRM1e9SWJf8zgh
        jreiayYUmLSjRev0A2sOmHZC7Kbm1MCRbGbjktEyaAQYJjgwfejEPnrvy1O5xQKHJZuMCEWV0pD
        6jLB7Z3D7GrSZ2d/OnrOEVWgc8GqQVjUrf2s8JpCnoOrcVegUc5PGBaz59UGvdPw=
X-Google-Smtp-Source: 
 APXvYqxdez10mu0I4p1MtnMG/cWtZiGAnGVGCCJ1MOJqdhnLTC4izjs6+s8F/hnISExGQip6H+TRsw5ABwG7Iw==
X-Received: by 2002:a65:6451:: with SMTP id s17mr5345865pgv.188.1575660726256;
 Fri, 06 Dec 2019 11:32:06 -0800 (PST)
Date: Fri,  6 Dec 2019 11:31:42 -0800
Message-Id: <20191206193144.33209-1-jmattson@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.24.0.393.g34dc348eaf-goog
Subject: [PATCH v2 1/3] kvm: nVMX: VMWRITE checks VMCS-link pointer before
 VMCS field
From: Jim Mattson <jmattson@google.com>
To: kvm@vger.kernel.org
Cc: Jim Mattson <jmattson@google.com>, Peter Shier <pshier@google.com>,
        Oliver Upton <oupton@google.com>,
        Jon Cargille <jcargill@google.com>,
        Liran Alon <liran.alon@oracle.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

According to the SDM, a VMWRITE in VMX non-root operation with an
invalid VMCS-link pointer results in VMfailInvalid before the validity
of the VMCS field in the secondary source operand is checked.

For consistency, modify both handle_vmwrite and handle_vmread, even
though there was no problem with the latter.

Fixes: 6d894f498f5d1 ("KVM: nVMX: vmread/vmwrite: Use shadow vmcs12 if running L2")
Signed-off-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
Reviewed-by: Oliver Upton <oupton@google.com>
Reviewed-by: Jon Cargille <jcargill@google.com>
Cc: Liran Alon <liran.alon@oracle.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>
---
v1 -> v2:
 * Split the invalid VMCS-link pointer check from the conditional call to
   copy_vmcs02_to_vmcs12_rare.
 * Hoisted the assignment of vmcs12 to its declaration.
 * Modified handle_vmread to maintain consistency with handle_vmwrite.

 arch/x86/kvm/vmx/nested.c | 59 +++++++++++++++++----------------------
 1 file changed, 25 insertions(+), 34 deletions(-)

```
#### [PATCH v2] KVM: Remove duplicated declaration of kvm_vcpu_kick
##### From: Zenghui Yu <yuzenghui@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zenghui Yu <yuzenghui@huawei.com>
X-Patchwork-Id: 11275953
Return-Path: <SRS0=PSGZ=Z4=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9E1C0109A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Dec 2019 10:46:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7A89B24659
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Dec 2019 10:46:26 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726206AbfLFKqW (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 6 Dec 2019 05:46:22 -0500
Received: from szxga04-in.huawei.com ([45.249.212.190]:7646 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726102AbfLFKqW (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 6 Dec 2019 05:46:22 -0500
Received: from DGGEMS404-HUB.china.huawei.com (unknown [172.30.72.58])
        by Forcepoint Email with ESMTP id 85D5C69AC500BA8716F1;
        Fri,  6 Dec 2019 18:46:19 +0800 (CST)
Received: from DESKTOP-8RFUVS3.china.huawei.com (10.173.222.27) by
 DGGEMS404-HUB.china.huawei.com (10.3.19.204) with Microsoft SMTP Server id
 14.3.439.0; Fri, 6 Dec 2019 18:46:12 +0800
From: Zenghui Yu <yuzenghui@huawei.com>
To: <pbonzini@redhat.com>, <rkrcmar@redhat.com>
CC: <cohuck@redhat.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <wanghaibin.wang@huawei.com>,
        Zenghui Yu <yuzenghui@huawei.com>
Subject: [PATCH v2] KVM: Remove duplicated declaration of kvm_vcpu_kick
Date: Fri, 6 Dec 2019 18:45:52 +0800
Message-ID: <20191206104552.464-1-yuzenghui@huawei.com>
X-Mailer: git-send-email 2.23.0.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.173.222.27]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

There are two declarations of kvm_vcpu_kick() in kvm_host.h where
one of them is redundant. Remove to keep the git grep a bit cleaner.

Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Signed-off-by: Zenghui Yu <yuzenghui@huawei.com>
---

v1 -> v2:
	Collect Cornelia's tag

 include/linux/kvm_host.h | 1 -
 1 file changed, 1 deletion(-)

```
#### [PATCH] vhost/vsock: accept only packets with the right dst_cid
##### From: Stefano Garzarella <sgarzare@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stefano Garzarella <sgarzare@redhat.com>
X-Patchwork-Id: 11276573
Return-Path: <SRS0=PSGZ=Z4=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 76EEA14BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Dec 2019 14:39:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 55C7C20706
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Dec 2019 14:39:29 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="A8u6dFx7"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726461AbfLFOjZ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 6 Dec 2019 09:39:25 -0500
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:31225 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726250AbfLFOjZ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 6 Dec 2019 09:39:25 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1575643163;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=t9EmvdK1AgBEeVtyIdQhFEC+nCx5dAL/M6REGeRF2KI=;
        b=A8u6dFx7I3AQ9vPjpD4oHMpe5QOUPE3N36xPugfLKDuaA98+bb1h7mDn/rQXjtk0m8xxt7
        I3Ug+bSW+15uBh2M0pUS4zhx+U12Klw/EVJOJn/Dnyy4AdnzqDZ8/L2ePuR/T35v4b3UFz
        kceOEZ5bil4v/g+AhHRp6U7jQlu49nA=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-111-vn1BWFynNbyWxKfbUzJhhg-1; Fri, 06 Dec 2019 09:39:20 -0500
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 7F30F64A9B;
        Fri,  6 Dec 2019 14:39:19 +0000 (UTC)
Received: from steredhat.redhat.com (ovpn-117-106.ams2.redhat.com
 [10.36.117.106])
        by smtp.corp.redhat.com (Postfix) with ESMTP id ECF4D5C1C3;
        Fri,  6 Dec 2019 14:39:12 +0000 (UTC)
From: Stefano Garzarella <sgarzare@redhat.com>
To: virtualization@lists.linux-foundation.org
Cc: Stefano Garzarella <sgarzare@redhat.com>,
        Stefan Hajnoczi <stefanha@redhat.com>,
        Jason Wang <jasowang@redhat.com>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, netdev@vger.kernel.org,
        "Michael S. Tsirkin" <mst@redhat.com>
Subject: [PATCH] vhost/vsock: accept only packets with the right dst_cid
Date: Fri,  6 Dec 2019 15:39:12 +0100
Message-Id: <20191206143912.153583-1-sgarzare@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
X-MC-Unique: vn1BWFynNbyWxKfbUzJhhg-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When we receive a new packet from the guest, we check if the
src_cid is correct, but we forgot to check the dst_cid.

The host should accept only packets where dst_cid is
equal to the host CID.

Signed-off-by: Stefano Garzarella <sgarzare@redhat.com>
---
 drivers/vhost/vsock.c | 4 +++-
 1 file changed, 3 insertions(+), 1 deletion(-)

```
