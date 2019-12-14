#### [PATCH] hw/i386: De-duplicate gsi_handler() to remove kvm_pc_gsi_handler()
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
 <philmd@redhat.com>
X-Patchwork-Id: 11290449
Return-Path: <SRS0=Db9H=2D=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2E566109A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 13 Dec 2019 20:36:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id CA4B1246A2
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 13 Dec 2019 20:36:31 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="AC1y87w2"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726687AbfLMLHv (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 13 Dec 2019 06:07:51 -0500
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:24996 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1725948AbfLMLHu (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 13 Dec 2019 06:07:50 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1576235269;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=9YVwxsrA7bHU0ZxobUQ7B9E7z5AaZfc5ooyfIz7vtGg=;
        b=AC1y87w2JjQDb94mQxvye37nJ6TRi02WuodYhTxpIxKpwbo4SzdeIxuU8hkVC4S10eGhKl
        5W9Tc05ICP57ICFvaelUqAYHtm6QPkpfVKa6KnKs5iltUmw/qxfc5kELdN5Y/7iMurfujf
        yiYzkhKcrSjaSe4Lt4VMPaR5HjrxDxo=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-297-S5e_EUE5MiSWKFOHK0hUeA-1; Fri, 13 Dec 2019 06:07:48 -0500
X-MC-Unique: S5e_EUE5MiSWKFOHK0hUeA-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 52FA6107ACC7;
        Fri, 13 Dec 2019 11:07:47 +0000 (UTC)
Received: from x1w.redhat.com (ovpn-204-134.brq.redhat.com [10.40.204.134])
        by smtp.corp.redhat.com (Postfix) with ESMTPS id 814145D6BE;
        Fri, 13 Dec 2019 11:07:39 +0000 (UTC)
From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>
To: qemu-devel@nongnu.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
 Marcel Apfelbaum <marcel.apfelbaum@gmail.com>, kvm@vger.kernel.org,
 Eduardo Habkost <ehabkost@redhat.com>, Richard Henderson <rth@twiddle.net>,
 "Michael S. Tsirkin" <mst@redhat.com>, =?utf-8?q?Philippe_Mathieu-Daud?=
	=?utf-8?q?=C3=A9?= <philmd@redhat.com>
Subject: [PATCH] hw/i386: De-duplicate gsi_handler() to remove
 kvm_pc_gsi_handler()
Date: Fri, 13 Dec 2019 12:07:36 +0100
Message-Id: <20191213110736.10767-1-philmd@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Both gsi_handler() and kvm_pc_gsi_handler() have the same content,
except one comment. Move the comment, and de-duplicate the code.

Signed-off-by: Philippe Mathieu-Daudé <philmd@redhat.com>
---
 include/sysemu/kvm.h |  1 -
 hw/i386/kvm/ioapic.c | 12 ------------
 hw/i386/pc.c         |  5 ++---
 3 files changed, 2 insertions(+), 16 deletions(-)

```
#### [PATCH 01/12] hw/i386/pc: Convert DPRINTF() to trace events
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
 <philmd@redhat.com>
X-Patchwork-Id: 11290827
Return-Path: <SRS0=Db9H=2D=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D19B8109A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 13 Dec 2019 20:37:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 826C124712
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 13 Dec 2019 20:37:52 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="eThTNBIj"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728076AbfLMQSY (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 13 Dec 2019 11:18:24 -0500
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:26592 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1728057AbfLMQSY (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 13 Dec 2019 11:18:24 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1576253903;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=zCZ3/HzJt6UebSooqSPs4MgLhNuCHweYJBKUsTXMBXw=;
        b=eThTNBIj1LpDkDq5CCRCKqh+fTh87XpfdBoRJx4Ua0Cnn5wVsZsqDvI45VF3FHikhHRsmz
        0k6nC7gXlg+1jaIRLd+AGXlbFIEFq6RVMTcDJQvis44avpk/SgJWOReOHw+A3c8uIrKyTR
        NTDBAlnIcJSWq1zcb9vxnBhwPlu4ToQ=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-312-3ZUD0pJMOhuSY8G0PHLj2g-1; Fri, 13 Dec 2019 11:18:21 -0500
X-MC-Unique: 3ZUD0pJMOhuSY8G0PHLj2g-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 3B5BB107ACC4;
        Fri, 13 Dec 2019 16:18:20 +0000 (UTC)
Received: from x1w.redhat.com (ovpn-205-147.brq.redhat.com [10.40.205.147])
        by smtp.corp.redhat.com (Postfix) with ESMTPS id CB3BD19C4F;
        Fri, 13 Dec 2019 16:18:12 +0000 (UTC)
From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>
To: qemu-devel@nongnu.org
Cc: John Snow <jsnow@redhat.com>, "Michael S. Tsirkin" <mst@redhat.com>,
 Eduardo Habkost <ehabkost@redhat.com>, Paul Durrant <paul@xen.org>,
 Marcel Apfelbaum <marcel.apfelbaum@gmail.com>, kvm@vger.kernel.org,
 Stefano Stabellini <sstabellini@kernel.org>,
 Igor Mammedov <imammedo@redhat.com>,
 Anthony Perard <anthony.perard@citrix.com>, qemu-block@nongnu.org,
 Richard Henderson <rth@twiddle.net>, xen-devel@lists.xenproject.org,
 Paolo Bonzini <pbonzini@redhat.com>, Sergio Lopez <slp@redhat.com>,
	=?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>
Subject: [PATCH 01/12] hw/i386/pc: Convert DPRINTF() to trace events
Date: Fri, 13 Dec 2019 17:17:42 +0100
Message-Id: <20191213161753.8051-2-philmd@redhat.com>
In-Reply-To: <20191213161753.8051-1-philmd@redhat.com>
References: <20191213161753.8051-1-philmd@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Convert the deprecated DPRINTF() macro to trace events.

Signed-off-by: Philippe Mathieu-Daudé <philmd@redhat.com>
---
v2: rename pc_pic -> x86_pic
---
 hw/i386/pc.c         | 19 +++++--------------
 hw/i386/trace-events |  6 ++++++
 2 files changed, 11 insertions(+), 14 deletions(-)

```
#### [PATCH 1/7] KVM: Pass mmu_notifier_range down to kvm_unmap_hva_range()
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11290971
Return-Path: <SRS0=Db9H=2D=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 35ADF6C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 13 Dec 2019 20:38:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id DE6642473C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 13 Dec 2019 20:38:28 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1576269509;
	bh=fpvvJyJEt6VW9FDMCI8TKXi+3y4rOFaZJsJHq5X3VK4=;
	h=From:Cc:Subject:Date:In-Reply-To:References:To:List-ID:From;
	b=MSftiYHU7jy3gswS72szVhmWC/5Vy7Y4NMCY3FDy9gSIwdrl99FFPBKyPU9lsmNpm
	 uYrZII7leiWUhi0ssjI1JnHa4+sjFH17iV0GxJ7rfgVO+UUbGvYEb8RSEoULenhnmb
	 AVeKtueXzoadwn1dvLpFibDx3zpyes2Wn55iiWks=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728816AbfLMS2D (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 13 Dec 2019 13:28:03 -0500
Received: from inca-roads.misterjones.org ([213.251.177.50]:40815 "EHLO
        inca-roads.misterjones.org" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728704AbfLMS1w (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 13 Dec 2019 13:27:52 -0500
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by cheepnis.misterjones.org with esmtpsa
 (TLSv1.2:DHE-RSA-AES128-GCM-SHA256:128)
        (Exim 4.80)
        (envelope-from <maz@kernel.org>)
        id 1ifpdE-0001O7-PY; Fri, 13 Dec 2019 19:25:41 +0100
From: Marc Zyngier <maz@kernel.org>
Cc: James Morse <james.morse@arm.com>,
 Julien Thierry <julien.thierry.kdev@gmail.com>,
 Suzuki K Poulose <suzuki.poulose@arm.com>, James Hogan <jhogan@kernel.org>,
 Paul Mackerras <paulus@ozlabs.org>, Paolo Bonzini <pbonzini@redhat.com>,
	=?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Sean Christopherson <sean.j.christopherson@intel.com>,
 Vitaly Kuznetsov <vkuznets@redhat.com>, Wanpeng Li <wanpengli@tencent.com>,
 Jim Mattson <jmattson@google.com>, Joerg Roedel <joro@8bytes.org>,
 linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
 linux-mips@vger.kernel.org, kvm-ppc@vger.kernel.org, kvm@vger.kernel.org
Subject: [PATCH 1/7] KVM: Pass mmu_notifier_range down to
 kvm_unmap_hva_range()
Date: Fri, 13 Dec 2019 18:24:57 +0000
Message-Id: <20191213182503.14460-2-maz@kernel.org>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20191213182503.14460-1-maz@kernel.org>
References: <20191213182503.14460-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: james.morse@arm.com, julien.thierry.kdev@gmail.com,
 suzuki.poulose@arm.com, jhogan@kernel.org, paulus@ozlabs.org,
 pbonzini@redhat.com, rkrcmar@redhat.com, sean.j.christopherson@intel.com,
 vkuznets@redhat.com, wanpengli@tencent.com, jmattson@google.com,
 joro@8bytes.org, linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, linux-mips@vger.kernel.org,
 kvm-ppc@vger.kernel.org, kvm@vger.kernel.org
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on cheepnis.misterjones.org);
 SAEximRunCond expanded to false
To: unlisted-recipients:; (no To-header on input)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

kvm_unmap_hva_range() is currently passed both start and end
fields from the mmu_notifier_range structure. As this struct
now contains important information about the reason of the
unmap (the event field), replace the start/end parameters
with the range struct, and update all architectures.

No functionnal change.

Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 arch/arm/include/asm/kvm_host.h     | 2 +-
 arch/arm64/include/asm/kvm_host.h   | 2 +-
 arch/mips/include/asm/kvm_host.h    | 2 +-
 arch/mips/kvm/mmu.c                 | 6 ++++--
 arch/powerpc/include/asm/kvm_host.h | 2 +-
 arch/powerpc/kvm/book3s.c           | 5 +++--
 arch/powerpc/kvm/e500_mmu_host.c    | 4 ++--
 arch/x86/include/asm/kvm_host.h     | 3 ++-
 arch/x86/kvm/mmu/mmu.c              | 5 +++--
 arch/x86/kvm/x86.c                  | 4 ++--
 include/linux/kvm_host.h            | 2 +-
 virt/kvm/arm/mmu.c                  | 8 ++++----
 virt/kvm/kvm_main.c                 | 7 +++----
 13 files changed, 28 insertions(+), 24 deletions(-)

```
#### [PULL] virtio: cleanups and fixes
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 11290657
Return-Path: <SRS0=Db9H=2D=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6E780175D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 13 Dec 2019 20:37:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 218B724747
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 13 Dec 2019 20:37:20 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="VnMg/nbS"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727790AbfLMOfa (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 13 Dec 2019 09:35:30 -0500
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:37093 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1727779AbfLMOfa (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 13 Dec 2019 09:35:30 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1576247729;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type;
        bh=K16O3uoMoq1X7RVCymy3uF4s1barxs0V/Dkj4PdUFYc=;
        b=VnMg/nbS4WLIfz9pzROj7NhtJ+T8bS4q7p43VNINsfGcthTJ0gzHuKdNvUujFeABQmT07v
        /sBKFDEymBQCaHrCXwiTGfqcU3nXhm3L0gph82GjC5NLz2O5LtoBk9ZlCTxqNwACUO+bmd
        7ALyVfVI4h2L5Zis0Iu8IWP4KqhB0NM=
Received: from mail-qv1-f69.google.com (mail-qv1-f69.google.com
 [209.85.219.69]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-167-C1CU97dMPmGLXrfEVGRKyA-1; Fri, 13 Dec 2019 09:35:26 -0500
X-MC-Unique: C1CU97dMPmGLXrfEVGRKyA-1
Received: by mail-qv1-f69.google.com with SMTP id a4so1805576qvn.14
        for <kvm@vger.kernel.org>; Fri, 13 Dec 2019 06:35:25 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:mime-version
         :content-disposition;
        bh=K16O3uoMoq1X7RVCymy3uF4s1barxs0V/Dkj4PdUFYc=;
        b=YpUVMYFK2FS9EN4w3sTsyNp8xr9R4DilGjg1U+AUnZJ5aZ0zeyT8YMn59M6rbrFp6J
         h5KA/A4EYcWdORTUMtxHbW5iFE58XZ853TB2iRAMy0z/kU2uaruCmuPT3M44C9hOPRrK
         TpHmP0vg8ID8iHy3rxPUr68LLeUIUTQeOEwMVUjBkYiN8aAhm3Vsc8ntr4Jrw9YfsCt/
         ZktCTkOHD/8c77WqSZzfTrixtpUbaW3VD72hdJai4HcAM8MRZnWPMOYwIh+DeQ1HjGTX
         TPma/M5TvnFB0bz+fy1KWuF9Gus+SW1fpIZfhyeNi43G6wNymQuQsdKLINeFIsYWNiWd
         Rg3g==
X-Gm-Message-State: APjAAAV2wq7J91mh9wgW06rVeAZjFe0wwMQUex50NH1QHULjJz15Xuhw
        HNbfXumfiaf+/Q1DUWfAOyMyuQqwVJsSot4liJ3HqDXufUyuViMZP3/lTkmD0YyknKQGGR2KjKH
        t3tiVqWikdw9l
X-Received: by 2002:a37:5d1:: with SMTP id 200mr13575576qkf.492.1576247725619;
        Fri, 13 Dec 2019 06:35:25 -0800 (PST)
X-Google-Smtp-Source: 
 APXvYqxgq1bbRToA9P95foPk8oGS2OI8ibHY6a72vmEjljgya2qgJqTa4/Xh04URKGN+H8Bz4Y3K4g==
X-Received: by 2002:a37:5d1:: with SMTP id 200mr13575555qkf.492.1576247725393;
        Fri, 13 Dec 2019 06:35:25 -0800 (PST)
Received: from redhat.com (bzq-79-181-48-215.red.bezeqint.net.
 [79.181.48.215])
        by smtp.gmail.com with ESMTPSA id
 l62sm2885132qke.12.2019.12.13.06.35.21
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 13 Dec 2019 06:35:24 -0800 (PST)
Date: Fri, 13 Dec 2019 09:35:19 -0500
From: "Michael S. Tsirkin" <mst@redhat.com>
To: Linus Torvalds <torvalds@linux-foundation.org>
Cc: kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org, linux-kernel@vger.kernel.org,
        akpm@linux-foundation.org, david@redhat.com, imammedo@redhat.com,
        jasowang@redhat.com, liuj97@gmail.com, mst@redhat.com,
        stable@vger.kernel.org, yuhuang@redhat.com
Subject: [PULL] virtio: cleanups and fixes
Message-ID: <20191213093519-mutt-send-email-mst@kernel.org>
MIME-Version: 1.0
Content-Disposition: inline
X-Mutt-Fcc: =sent
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The following changes since commit e42617b825f8073569da76dc4510bfa019b1c35a:

  Linux 5.5-rc1 (2019-12-08 14:57:55 -0800)

are available in the Git repository at:

  https://git.kernel.org/pub/scm/linux/kernel/git/mst/vhost.git tags/for_linus

for you to fetch changes up to 63b9b80e9f5b2c463d98d6e550e0d0e3ace66033:

  virtio_balloon: divide/multiply instead of shifts (2019-12-11 08:14:07 -0500)

----------------------------------------------------------------
virtio: fixes, cleanups

Some fixes and cleanup patches.

Signed-off-by: Michael S. Tsirkin <mst@redhat.com>

----------------------------------------------------------------
David Hildenbrand (1):
      virtio-balloon: fix managed page counts when migrating pages between zones

Michael S. Tsirkin (2):
      virtio_balloon: name cleanups
      virtio_balloon: divide/multiply instead of shifts

 drivers/virtio/virtio_balloon.c | 36 ++++++++++++++++++++++++------------
 1 file changed, 24 insertions(+), 12 deletions(-)
```
#### [PATCH v5] kvm: Refactor handling of VM debugfs files
##### From: Milan Pandurov <milanpa@amazon.de>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Milan Pandurov <milanpa@amazon.de>
X-Patchwork-Id: 11290581
Return-Path: <SRS0=Db9H=2D=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AF221175D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 13 Dec 2019 20:37:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 6257324715
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 13 Dec 2019 20:37:00 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amazon.de header.i=@amazon.de
 header.b="ua3Y2KtV"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727328AbfLMNHl (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 13 Dec 2019 08:07:41 -0500
Received: from smtp-fw-4101.amazon.com ([72.21.198.25]:49205 "EHLO
        smtp-fw-4101.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727306AbfLMNHl (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 13 Dec 2019 08:07:41 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.de; i=@amazon.de; q=dns/txt; s=amazon201209;
  t=1576242458; x=1607778458;
  h=from:to:cc:subject:date:message-id:mime-version;
  bh=4fQBD4rRlXQRRamEzH1tOwObi2stteZWOKar33c3SOw=;
  b=ua3Y2KtVebY6x4Sl1ldwwNt3IPl/3Brumcg4QjXk2OI6jMFLKG6OKR10
   qWClspJSWdbHjmUIf9YKi/0ohPCEijFk/3/M4qnLeYzQosDjXzmIa2LOO
   s+aToBPRCnbNeBY8Ui1KPPe5RNYLl+BivrzN2/FGVSWj0YpAN5Q7UYllO
   Y=;
IronPort-SDR: 
 7uwDc3ozL1jchQhLsYIQc6pKAlvqbZN3cNdeNTTXbDVvU7T5YxI7UCtMZMu49EXlgFxXwC7Ogz
 9Y1C/wOi5eWw==
X-IronPort-AV: E=Sophos;i="5.69,309,1571702400";
   d="scan'208";a="8355052"
Received: from iad6-co-svc-p1-lb1-vlan3.amazon.com (HELO
 email-inbound-relay-2c-397e131e.us-west-2.amazon.com) ([10.124.125.6])
  by smtp-border-fw-out-4101.iad4.amazon.com with ESMTP;
 13 Dec 2019 13:07:36 +0000
Received: from EX13MTAUEA001.ant.amazon.com
 (pdx4-ws-svc-p6-lb7-vlan3.pdx.amazon.com [10.170.41.166])
        by email-inbound-relay-2c-397e131e.us-west-2.amazon.com (Postfix) with
 ESMTPS id C5A62A2158;
        Fri, 13 Dec 2019 13:07:35 +0000 (UTC)
Received: from EX13D27EUB004.ant.amazon.com (10.43.166.152) by
 EX13MTAUEA001.ant.amazon.com (10.43.61.243) with Microsoft SMTP Server (TLS)
 id 15.0.1367.3; Fri, 13 Dec 2019 13:07:35 +0000
Received: from uc3ce012741425f.ant.amazon.com (10.43.161.179) by
 EX13D27EUB004.ant.amazon.com (10.43.166.152) with Microsoft SMTP Server (TLS)
 id 15.0.1367.3; Fri, 13 Dec 2019 13:07:31 +0000
From: Milan Pandurov <milanpa@amazon.de>
To: <kvm@vger.kernel.org>
CC: <pbonzini@redhat.com>, <rkrcmar@redhat.com>, <graf@amazon.de>,
        <borntraeger@de.ibm.com>
Subject: [PATCH v5] kvm: Refactor handling of VM debugfs files
Date: Fri, 13 Dec 2019 14:07:21 +0100
Message-ID: <20191213130721.7942-1-milanpa@amazon.de>
X-Mailer: git-send-email 2.17.1
MIME-Version: 1.0
X-Originating-IP: [10.43.161.179]
X-ClientProxiedBy: EX13D02UWB004.ant.amazon.com (10.43.161.11) To
 EX13D27EUB004.ant.amazon.com (10.43.166.152)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We can store reference to kvm_stats_debugfs_item instead of copying
its values to kvm_stat_data.
This allows us to remove duplicated code and usage of temporary
kvm_stat_data inside vm_stat_get et al.

Signed-off-by: Milan Pandurov <milanpa@amazon.de>
Reviewed-by: Alexander Graf <graf@anazon.com>
---
v1 -> v2:
 - fix compile issues
 - add reference to kvm_stats_debugfs_item in kvm_stat_data
 - return -EINVAL when writing !0
 - use explicit switch case instead of ops indirection
 - fix checkpatch warning: Change S_IWUGO to 0222

v2 -> v3:
 - remove unused kvm_stat_ops
 - fix style issues

v3 -> v4:
 - revert: Change S_IWUGO to 0222

v4 -> v5:
 - fix checkpatch warning: Change S_IWUGO to 0222
---
 include/linux/kvm_host.h |   7 +-
 virt/kvm/kvm_main.c      | 142 +++++++++++++++++++--------------------
 2 files changed, 76 insertions(+), 73 deletions(-)

```
#### [PATCH net 1/2] vsock/virtio: fix null-pointer dereference in virtio_transport_recv_listen()
##### From: Stefano Garzarella <sgarzare@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stefano Garzarella <sgarzare@redhat.com>
X-Patchwork-Id: 11290999
Return-Path: <SRS0=Db9H=2D=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 33300188B
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 13 Dec 2019 20:38:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id DD087246C0
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 13 Dec 2019 20:38:34 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="BWSrxPB3"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728649AbfLMSsP (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 13 Dec 2019 13:48:15 -0500
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:38674 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1728696AbfLMSsN (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 13 Dec 2019 13:48:13 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1576262892;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=5A2LeRnUqA/oVUAeoB9Y1zyaCpFbrJsfRAN46NsJ6og=;
        b=BWSrxPB3sx/Vle2dnpPMbnN5XXhVCMHDe60fLhX85MxyCMsdeM1xYd9Ef2VGiV+x1fRM4o
        OWfElaiytoGnnhQlDZ4nnpsfbnaU8QdJFbxfZ39B6qifmHD0q3y3M+ZOyFm+F+Q34EESAv
        u8q9ZJ2DBLA2Lx84qulFbylbcIK09Vs=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-385-znf3gbb5PCy5O_eL0tSkOA-1; Fri, 13 Dec 2019 13:48:10 -0500
X-MC-Unique: znf3gbb5PCy5O_eL0tSkOA-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 7F649477;
        Fri, 13 Dec 2019 18:48:09 +0000 (UTC)
Received: from steredhat.redhat.com (ovpn-117-123.ams2.redhat.com
 [10.36.117.123])
        by smtp.corp.redhat.com (Postfix) with ESMTP id C21DD60474;
        Fri, 13 Dec 2019 18:48:07 +0000 (UTC)
From: Stefano Garzarella <sgarzare@redhat.com>
To: davem@davemloft.net
Cc: Stefano Garzarella <sgarzare@redhat.com>,
        linux-kernel@vger.kernel.org, netdev@vger.kernel.org,
        kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        Stefan Hajnoczi <stefanha@redhat.com>
Subject: [PATCH net 1/2] vsock/virtio: fix null-pointer dereference in
 virtio_transport_recv_listen()
Date: Fri, 13 Dec 2019 19:48:00 +0100
Message-Id: <20191213184801.486675-2-sgarzare@redhat.com>
In-Reply-To: <20191213184801.486675-1-sgarzare@redhat.com>
References: <20191213184801.486675-1-sgarzare@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

With multi-transport support, listener sockets are not bound to any
transport. So, calling virtio_transport_reset(), when an error
occurs, on a listener socket produces the following null-pointer
dereference:

  BUG: kernel NULL pointer dereference, address: 00000000000000e8
  #PF: supervisor read access in kernel mode
  #PF: error_code(0x0000) - not-present page
  PGD 0 P4D 0
  Oops: 0000 [#1] SMP PTI
  CPU: 0 PID: 20 Comm: kworker/0:1 Not tainted 5.5.0-rc1-ste-00003-gb4be21f316ac-dirty #56
  Hardware name: QEMU Standard PC (Q35 + ICH9, 2009), BIOS ?-20190727_073836-buildvm-ppc64le-16.ppc.fedoraproject.org-3.fc31 04/01/2014
  Workqueue: virtio_vsock virtio_transport_rx_work [vmw_vsock_virtio_transport]
  RIP: 0010:virtio_transport_send_pkt_info+0x20/0x130 [vmw_vsock_virtio_transport_common]
  Code: 1f 84 00 00 00 00 00 0f 1f 00 55 48 89 e5 41 57 41 56 41 55 49 89 f5 41 54 49 89 fc 53 48 83 ec 10 44 8b 76 20 e8 c0 ba fe ff <48> 8b 80 e8 00 00 00 e8 64 e3 7d c1 45 8b 45 00 41 8b 8c 24 d4 02
  RSP: 0018:ffffc900000b7d08 EFLAGS: 00010282
  RAX: 0000000000000000 RBX: ffff88807bf12728 RCX: 0000000000000000
  RDX: ffff88807bf12700 RSI: ffffc900000b7d50 RDI: ffff888035c84000
  RBP: ffffc900000b7d40 R08: ffff888035c84000 R09: ffffc900000b7d08
  R10: ffff8880781de800 R11: 0000000000000018 R12: ffff888035c84000
  R13: ffffc900000b7d50 R14: 0000000000000000 R15: ffff88807bf12724
  FS:  0000000000000000(0000) GS:ffff88807dc00000(0000) knlGS:0000000000000000
  CS:  0010 DS: 0000 ES: 0000 CR0: 0000000080050033
  CR2: 00000000000000e8 CR3: 00000000790f4004 CR4: 0000000000160ef0
  DR0: 0000000000000000 DR1: 0000000000000000 DR2: 0000000000000000
  DR3: 0000000000000000 DR6: 00000000fffe0ff0 DR7: 0000000000000400
  Call Trace:
   virtio_transport_reset+0x59/0x70 [vmw_vsock_virtio_transport_common]
   virtio_transport_recv_pkt+0x5bb/0xe50 [vmw_vsock_virtio_transport_common]
   ? detach_buf_split+0xf1/0x130
   virtio_transport_rx_work+0xba/0x130 [vmw_vsock_virtio_transport]
   process_one_work+0x1c0/0x300
   worker_thread+0x45/0x3c0
   kthread+0xfc/0x130
   ? current_work+0x40/0x40
   ? kthread_park+0x90/0x90
   ret_from_fork+0x35/0x40
  Modules linked in: sunrpc kvm_intel kvm vmw_vsock_virtio_transport vmw_vsock_virtio_transport_common irqbypass vsock virtio_rng rng_core
  CR2: 00000000000000e8
  ---[ end trace e75400e2ea2fa824 ]---

This happens because virtio_transport_reset() calls
virtio_transport_send_pkt_info() that can be used only on
connecting/connected sockets.

This patch fixes the issue, using virtio_transport_reset_no_sock()
instead of virtio_transport_reset() when we are handling a listener
socket.

Fixes: c0cfa2d8a788 ("vsock: add multi-transports support")
Signed-off-by: Stefano Garzarella <sgarzare@redhat.com>
---
 net/vmw_vsock/virtio_transport_common.c | 8 ++++----
 1 file changed, 4 insertions(+), 4 deletions(-)

```
