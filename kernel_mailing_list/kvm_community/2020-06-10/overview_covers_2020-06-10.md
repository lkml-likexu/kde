

#### [PATCH v2 0/4] kvm: arm64: Pointer Authentication handling fixes
##### From: Marc Zyngier <maz@kernel.org>
X-SA-Exim-Mail-From: maz@kernel.org

```c
From patchwork Wed Jun 10 11:34:02 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11597521
Return-Path: <SRS0=Uci1=7X=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D1178739
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 10 Jun 2020 11:34:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B8B9E2078D
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 10 Jun 2020 11:34:17 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1591788857;
	bh=9N6nffWe0REroh98cZzvRnmfrffUIT7lJJ7yMkeQ6uI=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=zD/S8qvQlPtR0/uDSL8lDgrz2XaFg8/lZPhr3NVsdagE5r3p3Hthe29MJRC4V6+Si
	 2/MdVN1MScOcP3XvWkyD9uaZPAM7F6qGDUhPD1WgLcXNBX9mpPwrutRb8oEql6khk7
	 hOMmehfmEjHvQ1TkNwrYLadIe8jb6aJDeODRHa1g=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728527AbgFJLeQ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 10 Jun 2020 07:34:16 -0400
Received: from mail.kernel.org ([198.145.29.99]:42712 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728491AbgFJLeQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 10 Jun 2020 07:34:16 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id B0BCA20734;
        Wed, 10 Jun 2020 11:34:15 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1591788855;
        bh=9N6nffWe0REroh98cZzvRnmfrffUIT7lJJ7yMkeQ6uI=;
        h=From:To:Cc:Subject:Date:From;
        b=Ksvks8e29KLnHD9le872+c+3SUvatPHr3scAMz190kRFvyApeml9YWHh8o+yITFcD
         Mj8bsnfTJ1Vtcu0R5MHp396KaIIEEQ11lRB+vXVJj0rIdF/qd77dIO2NIfDLl5PFao
         YoBbsMa+nMUOr7bfYEkscw/tyWNN//u47xzi+XXM=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1jiyzm-001lrp-8M; Wed, 10 Jun 2020 12:34:14 +0100
From: Marc Zyngier <maz@kernel.org>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
        linux-arm-kernel@lists.infradead.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Will Deacon <will@kernel.org>,
        Catalin Marinas <catalin.marinas@arm.com>,
        Mark Rutland <mark.rutland@arm.com>,
        Andrew Scull <ascull@google.com>, kernel-team@android.com
Subject: [PATCH v2 0/4] kvm: arm64: Pointer Authentication handling fixes
Date: Wed, 10 Jun 2020 12:34:02 +0100
Message-Id: <20200610113406.1493170-1-maz@kernel.org>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
 linux-arm-kernel@lists.infradead.org, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com, will@kernel.org,
 catalin.marinas@arm.com, mark.rutland@arm.com, ascull@google.com,
 kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

I recently discovered that the Pointer Authentication (PtrAuth)
handling code in KVM is busted, and has been for a while. The main
issue is that the we save the host's keys from a preemptible
context. Things will go wrong at some point.

In order to address this, the first patch move the saving of the
host's keys to vcpu_load(). It is done eagerly, which is a bore, but
is at least safe. This is definitely stable material.

The following patch is adding an optimisatioe: we handle key saving
and HCR massaging as a fixup, much like the FPSIMD code.

Subsequent patch cleans up our HYP per-CPU accessor and make it sparse
friendly, asthe last patch makes heavy use of it by killing the
per-vcpu backpointer to the physical CPU context, avoiding the first
bug altogether.

This has been very lightly tested on a model. Unless someone shouts, I
plan to send this as part of the pending set of fixes.

* From v1:
  - Dropped the misbehaving guest handling patch
  - Added the two cleanup patches to the series (previously posted separately)

Marc Zyngier (4):
  KVM: arm64: Save the host's PtrAuth keys in non-preemptible context
  KVM: arm64: Handle PtrAuth traps early
  KVM: arm64: Stop sparse from moaning at __hyp_this_cpu_ptr
  KVM: arm64: Remove host_cpu_context member from vcpu structure

 arch/arm64/include/asm/kvm_asm.h     | 13 ++++--
 arch/arm64/include/asm/kvm_emulate.h |  6 ---
 arch/arm64/include/asm/kvm_host.h    |  3 --
 arch/arm64/kvm/arm.c                 |  6 +--
 arch/arm64/kvm/handle_exit.c         | 32 ++------------
 arch/arm64/kvm/hyp/debug-sr.c        |  4 +-
 arch/arm64/kvm/hyp/switch.c          | 65 +++++++++++++++++++++++++++-
 arch/arm64/kvm/hyp/sysreg-sr.c       |  6 ++-
 arch/arm64/kvm/pmu.c                 |  8 +---
 arch/arm64/kvm/sys_regs.c            | 13 +++---
 10 files changed, 91 insertions(+), 65 deletions(-)
```
#### [PATCH RFC v7 00/14] vhost: ring format independence
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
From patchwork Wed Jun 10 11:35:44 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 11597541
Return-Path: <SRS0=Uci1=7X=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 703FD13B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 10 Jun 2020 11:35:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 57FC92074B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 10 Jun 2020 11:35:56 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="QF2OTnz9"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728560AbgFJLfw (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 10 Jun 2020 07:35:52 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:41238 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1728471AbgFJLfw (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 10 Jun 2020 07:35:52 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1591788950;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type;
        bh=K8pYKea34n4xAOJeaGLf5FVVIvqFNqD4hPeT2vvgXYw=;
        b=QF2OTnz9kxuNasah4u4+KL7oDpaLE1I/forXxt8yF2+vBNNpKWBHG80j0tpIXY1sZpqptQ
        S5i5fLcweNfEER4kl5D0DL8ts+UN+0HWJLc+zsR5TfFnLo33R9HIQdyZ4PMsoaomRfIyTP
        Z640UA6RqpCOJbBxRhC8R3RpymGfVmo=
Received: from mail-wm1-f69.google.com (mail-wm1-f69.google.com
 [209.85.128.69]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-334-tW4BO7umNFa-hHurk8rvWQ-1; Wed, 10 Jun 2020 07:35:49 -0400
X-MC-Unique: tW4BO7umNFa-hHurk8rvWQ-1
Received: by mail-wm1-f69.google.com with SMTP id g84so400295wmf.4
        for <kvm@vger.kernel.org>; Wed, 10 Jun 2020 04:35:48 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:mime-version
         :content-disposition;
        bh=K8pYKea34n4xAOJeaGLf5FVVIvqFNqD4hPeT2vvgXYw=;
        b=MiyK6LNjARTlLIVYy4PmWAEVPCIEJsDRTxRCE/YI9fKwLhOB1x4LJ69a13BhMwNEqN
         kp2EGmv9aW9fP8dnSYg7SwXZMHkuvkU/XHwwj1X8eA6eq56zshJ3gk+ghWT2XCFnG8qW
         97j08IXSK8PyUpARVGCdaEV+2KuIRt4ikwv0iEg/Ce1OMi4hnH7DjY/+VUcNcdk4zsoV
         yrAYNupfZc2Pu4ZZggVrCRgZS/l5cFSeUwSSQ/gj4rHaj5MXGmfePVNApUa2j0Nv9z1F
         0vpN8yOauvf10iGtmFcCyzwvO26UWyWKYrMWXuQKAMUH0aojtur5T4JtqZgBaMLQM6Tx
         FlPg==
X-Gm-Message-State: AOAM532zxWco2hRfo4odhgG3NJyvMcHn2fc+no25Yx0isGUSOG4ckVdr
        q7YO+8OT7KwNvt/VtNfoEZBXKcEvZSbcy1K+mnusvnsyDmZoVa+MHICJ9hjHyyk2pr5BSptUMKG
        9Ji488XTrgeIm
X-Received: by 2002:adf:f251:: with SMTP id b17mr3051843wrp.289.1591788947565;
        Wed, 10 Jun 2020 04:35:47 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJyWnKuMQXjtn3IeBKm108U4YQm44aJFvUiXB9xS8f3b+y8TTFsSksejlRPFLR+mhd/ngiqchQ==
X-Received: by 2002:adf:f251:: with SMTP id b17mr3051819wrp.289.1591788947339;
        Wed, 10 Jun 2020 04:35:47 -0700 (PDT)
Received: from redhat.com ([212.92.121.57])
        by smtp.gmail.com with ESMTPSA id
 e15sm6864302wme.9.2020.06.10.04.35.45
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 10 Jun 2020 04:35:46 -0700 (PDT)
Date: Wed, 10 Jun 2020 07:35:44 -0400
From: "Michael S. Tsirkin" <mst@redhat.com>
To: linux-kernel@vger.kernel.org
Cc: kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org, Jason Wang <jasowang@redhat.com>,
        eperezma@redhat.com
Subject: [PATCH RFC v7 00/14] vhost: ring format independence
Message-ID: <20200610113515.1497099-1-mst@redhat.com>
MIME-Version: 1.0
Content-Disposition: inline
X-Mailer: git-send-email 2.27.0.106.g8ac3dc51b1
X-Mutt-Fcc: =sent
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This intentionally leaves "fixup" changes separate - hopefully
that is enough to fix vhost-net crashes reported here,
but it helps me keep track of what changed.
I will naturally squash them later when we are done.


This adds infrastructure required for supporting
multiple ring formats.

The idea is as follows: we convert descriptors to an
independent format first, and process that converting to
iov later.

Used ring is similar: we fetch into an independent struct first,
convert that to IOV later.

The point is that we have a tight loop that fetches
descriptors, which is good for cache utilization.
This will also allow all kind of batching tricks -
e.g. it seems possible to keep SMAP disabled while
we are fetching multiple descriptors.

For used descriptors, this allows keeping track of the buffer length
without need to rescan IOV.

This seems to perform exactly the same as the original
code based on a microbenchmark.
Lightly tested.
More testing would be very much appreciated.

changes from v6:
	- fixes some bugs introduced in v6 and v5

changes from v5:
	- addressed comments by Jason: squashed API changes, fixed up discard

changes from v4:
	- added used descriptor format independence
	- addressed comments by jason
	- fixed a crash detected by the lkp robot.

changes from v3:
        - fixed error handling in case of indirect descriptors
        - add BUG_ON to detect buffer overflow in case of bugs
                in response to comment by Jason Wang
        - minor code tweaks

Changes from v2:
	- fixed indirect descriptor batching
                reported by Jason Wang

Changes from v1:
	- typo fixes


Michael S. Tsirkin (14):
  vhost: option to fetch descriptors through an independent struct
  fixup! vhost: option to fetch descriptors through an independent
    struct
  vhost: use batched get_vq_desc version
  vhost/net: pass net specific struct pointer
  vhost: reorder functions
  vhost: format-independent API for used buffers
  fixup! vhost: format-independent API for used buffers
  fixup! vhost: use batched get_vq_desc version
  vhost/net: convert to new API: heads->bufs
  vhost/net: avoid iov length math
  vhost/test: convert to the buf API
  vhost/scsi: switch to buf APIs
  vhost/vsock: switch to the buf API
  vhost: drop head based APIs

 drivers/vhost/net.c   | 174 +++++++++----------
 drivers/vhost/scsi.c  |  73 ++++----
 drivers/vhost/test.c  |  22 +--
 drivers/vhost/vhost.c | 378 +++++++++++++++++++++++++++---------------
 drivers/vhost/vhost.h |  44 +++--
 drivers/vhost/vsock.c |  30 ++--
 6 files changed, 439 insertions(+), 282 deletions(-)
```
#### [PATCH v4 00/21] virtio-mem: Paravirtualized memory hot(un)plug
##### From: David Hildenbrand <david@redhat.com>

```c
From patchwork Wed Jun 10 11:53:58 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Hildenbrand <david@redhat.com>
X-Patchwork-Id: 11597599
Return-Path: <SRS0=Uci1=7X=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F0BDC14B7
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 10 Jun 2020 11:54:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D207A2074B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 10 Jun 2020 11:54:47 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="bK4ZZmHJ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728718AbgFJLyq (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 10 Jun 2020 07:54:46 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:26777 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1728497AbgFJLyq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 10 Jun 2020 07:54:46 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1591790083;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=5GKw6maa7B1hSULtMqvkZqZPAWdNHZFJSoWS3golo7w=;
        b=bK4ZZmHJ3Ngbplf506BdrAIJVRYXRb+zBpAlN81JSNmkC1cqriuYjd4wgpPTu0/mfXVLdu
        HU3sApGx44QHKaDc6ltv+ffa3P4KgRYPUmRNNq4Pp2WHfvQ3/OwJqvPwdKAK5Qg//e4rkp
        VZN27/c8m5SWJIkaISxvWzXsaB3i+x8=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-5-2gkK6RQTM4eSzxW0-G2CwQ-1; Wed, 10 Jun 2020 07:54:40 -0400
X-MC-Unique: 2gkK6RQTM4eSzxW0-G2CwQ-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 6C6D2800053;
        Wed, 10 Jun 2020 11:54:37 +0000 (UTC)
Received: from t480s.redhat.com (ovpn-114-42.ams2.redhat.com [10.36.114.42])
        by smtp.corp.redhat.com (Postfix) with ESMTP id A38615D9D3;
        Wed, 10 Jun 2020 11:54:20 +0000 (UTC)
From: David Hildenbrand <david@redhat.com>
To: qemu-devel@nongnu.org
Cc: kvm@vger.kernel.org, qemu-s390x@nongnu.org,
        Richard Henderson <rth@twiddle.net>,
        Paolo Bonzini <pbonzini@redhat.com>,
        "Dr . David Alan Gilbert" <dgilbert@redhat.com>,
        Eduardo Habkost <ehabkost@redhat.com>,
        "Michael S . Tsirkin" <mst@redhat.com>,
        David Hildenbrand <david@redhat.com>,
        teawater <teawaterz@linux.alibaba.com>,
        Pankaj Gupta <pankaj.gupta.linux@gmail.com>,
        Alex Shi <alex.shi@linux.alibaba.com>,
        Alex Williamson <alex.williamson@redhat.com>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Eric Blake <eblake@redhat.com>,
        Eric Farman <farman@linux.ibm.com>,
        Hailiang Zhang <zhang.zhanghailiang@huawei.com>,
        Halil Pasic <pasic@linux.ibm.com>,
        Igor Mammedov <imammedo@redhat.com>,
        Janosch Frank <frankja@linux.ibm.com>,
        Juan Quintela <quintela@redhat.com>,
        Keith Busch <kbusch@kernel.org>,
        Lukas Straub <lukasstraub2@web.de>,
        Marcel Apfelbaum <marcel.apfelbaum@gmail.com>,
        Markus Armbruster <armbru@redhat.com>,
        Peter Maydell <peter.maydell@linaro.org>,
        Pierre Morel <pmorel@linux.ibm.com>,
        "qemu-arm@nongnu.org" <qemu-arm@nongnu.org>,
        Sergio Lopez <slp@redhat.com>,
        Tony Krowiak <akrowiak@linux.ibm.com>
Subject: [PATCH v4 00/21] virtio-mem: Paravirtualized memory hot(un)plug
Date: Wed, 10 Jun 2020 13:53:58 +0200
Message-Id: <20200610115419.51688-1-david@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is the very basic, initial version of virtio-mem. More info on
virtio-mem in general can be found in the Linux kernel driver v2 posting
[1] and in patch #10. The Linux driver is currently on its way upstream.

This series is based on [3]:
    "[PATCH v1] pc: Support coldplugging of virtio-pmem-pci devices on all
     buses"
And [4]:
    "[PATCH v2] hmp: Make json format optional for qom-set"

The patches can be found at:
    https://github.com/davidhildenbrand/qemu.git virtio-mem-v4

"The basic idea of virtio-mem is to provide a flexible,
cross-architecture memory hot(un)plug solution that avoids many limitations
imposed by existing technologies, architectures, and interfaces."

There are a lot of addons in the works (esp. protection of unplugged
memory, better hugepage support (esp. when reading unplugged memory),
resizeable memory backends, support for more architectures, ...), this is
the very basic version to get the ball rolling.

The first 8 patches make sure we don't have any sudden surprises e.g., if
somebody tries to pin all memory in RAM blocks, resulting in a higher
memory consumption than desired. The remaining patches add basic virtio-mem
along with support for x86-64. The last patch indicates to the guest OS
the maximum possible PFN using ACPI SRAT, such that Linux can properly
enable the swiotlb when booting only with DMA memory.

[1] https://lkml.kernel.org/r/20200311171422.10484-1-david@redhat.com
[2] https://lkml.kernel.org/r/20200507140139.17083-1-david@redhat.com
[3] https://lkml.kernel.org/r/20200525084511.51379-1-david@redhat.com
[3] https://lkml.kernel.org/r/20200610075153.33892-1-david@redhat.com

Based-on: <20200525084511.51379-1-david@redhat.com>
Based-on: <20200610075153.33892-1-david@redhat.com>
Cc: teawater <teawaterz@linux.alibaba.com>
Cc: Pankaj Gupta <pankaj.gupta.linux@gmail.com>

v3 -> v4
- Adapt to virtio-mem config layout change (block size now is 64bit)
- Added "numa: Auto-enable NUMA when any memory devices are possible"

v2 -> v3:
- Rebased on upstream/[3]
- "virtio-mem: Exclude unplugged memory during migration"
-- Added
- "virtio-mem: Paravirtualized memory hot(un)plug"
-- Simplify bitmap operations, find consecutive areas
-- Tweak error messages
-- Reshuffle some checks
-- Minor cleanups
- "accel/kvm: Convert to ram_block_discard_disable()"
- "target/i386: sev: Use ram_block_discard_disable()"
-- Keep asserts clean of functional things

v1 -> v2:
- Rebased to object_property_*() changes
- "exec: Introduce ram_block_discard_(disable|require)()"
-- Change the function names and rephrase/add comments
- "virtio-balloon: Rip out qemu_balloon_inhibit()"
-- Add and use "migration_in_incoming_postcopy()"
- "migration/rdma: Use ram_block_discard_disable()"
-- Add a comment regarding pin_all vs. !pin_all
- "virtio-mem: Paravirtualized memory hot(un)plug"
-- Replace virtio_mem_discard_inhibited() by
   migration_in_incoming_postcopy()
-- Drop some asserts
-- Drop virtio_mem_bad_request(), use virtio_error() directly, printing
   more information
-- Replace "Note: Discarding should never fail ..." comments by
   error_report()
-- Replace virtio_stw_p() by cpu_to_le16()
-- Drop migration_addr and migration_block_size
-- Minor cleanups
- "linux-headers: update to contain virtio-mem"
-- Updated to latest v4 in Linux
- General changes
-- Fixup the users of the renamed ram_block_discard_(disable|require)
-- Use "X: cannot disable RAM discard"-styled error messages
- Added
-- "virtio-mem: Migration sanity checks"
-- "virtio-mem: Add trace events"

David Hildenbrand (21):
  exec: Introduce ram_block_discard_(disable|require)()
  vfio: Convert to ram_block_discard_disable()
  accel/kvm: Convert to ram_block_discard_disable()
  s390x/pv: Convert to ram_block_discard_disable()
  virtio-balloon: Rip out qemu_balloon_inhibit()
  target/i386: sev: Use ram_block_discard_disable()
  migration/rdma: Use ram_block_discard_disable()
  migration/colo: Use ram_block_discard_disable()
  linux-headers: update to contain virtio-mem
  virtio-mem: Paravirtualized memory hot(un)plug
  virtio-pci: Proxy for virtio-mem
  MAINTAINERS: Add myself as virtio-mem maintainer
  hmp: Handle virtio-mem when printing memory device info
  numa: Handle virtio-mem in NUMA stats
  pc: Support for virtio-mem-pci
  virtio-mem: Allow notifiers for size changes
  virtio-pci: Send qapi events when the virtio-mem size changes
  virtio-mem: Migration sanity checks
  virtio-mem: Add trace events
  virtio-mem: Exclude unplugged memory during migration
  numa: Auto-enable NUMA when any memory devices are possible

 MAINTAINERS                                 |   8 +
 accel/kvm/kvm-all.c                         |   4 +-
 balloon.c                                   |  17 -
 exec.c                                      |  52 ++
 hw/arm/virt.c                               |   2 +
 hw/core/numa.c                              |  17 +-
 hw/i386/Kconfig                             |   1 +
 hw/i386/microvm.c                           |   1 +
 hw/i386/pc.c                                |  50 +-
 hw/i386/pc_piix.c                           |   1 +
 hw/i386/pc_q35.c                            |   1 +
 hw/s390x/s390-virtio-ccw.c                  |  22 +-
 hw/vfio/ap.c                                |  10 +-
 hw/vfio/ccw.c                               |  11 +-
 hw/vfio/common.c                            |  53 +-
 hw/vfio/pci.c                               |   6 +-
 hw/virtio/Kconfig                           |  11 +
 hw/virtio/Makefile.objs                     |   2 +
 hw/virtio/trace-events                      |  10 +
 hw/virtio/virtio-balloon.c                  |   8 +-
 hw/virtio/virtio-mem-pci.c                  | 157 ++++
 hw/virtio/virtio-mem-pci.h                  |  34 +
 hw/virtio/virtio-mem.c                      | 872 ++++++++++++++++++++
 include/exec/memory.h                       |  41 +
 include/hw/boards.h                         |   1 +
 include/hw/pci/pci.h                        |   1 +
 include/hw/vfio/vfio-common.h               |   4 +-
 include/hw/virtio/virtio-mem.h              |  86 ++
 include/migration/colo.h                    |   2 +-
 include/migration/misc.h                    |   2 +
 include/standard-headers/linux/virtio_ids.h |   1 +
 include/standard-headers/linux/virtio_mem.h | 211 +++++
 include/sysemu/balloon.h                    |   2 -
 migration/migration.c                       |  15 +-
 migration/postcopy-ram.c                    |  23 -
 migration/rdma.c                            |  18 +-
 migration/savevm.c                          |  11 +-
 monitor/hmp-cmds.c                          |  16 +
 monitor/monitor.c                           |   1 +
 qapi/misc.json                              |  64 +-
 target/i386/sev.c                           |   7 +
 41 files changed, 1730 insertions(+), 126 deletions(-)
 create mode 100644 hw/virtio/virtio-mem-pci.c
 create mode 100644 hw/virtio/virtio-mem-pci.h
 create mode 100644 hw/virtio/virtio-mem.c
 create mode 100644 include/hw/virtio/virtio-mem.h
 create mode 100644 include/standard-headers/linux/virtio_mem.h
```
#### [PATCH 0/2] KVM: selftests: avoid test failures with 'nested=0'
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
From patchwork Wed Jun 10 13:58:45 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11597983
Return-Path: <SRS0=Uci1=7X=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5B3BA913
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 10 Jun 2020 13:59:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 415E2206F7
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 10 Jun 2020 13:59:02 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="A0ewlUM4"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729597AbgFJN7B (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 10 Jun 2020 09:59:01 -0400
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:33098 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726316AbgFJN67 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 10 Jun 2020 09:58:59 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1591797538;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=+xK1FKusim+ilFQ1Wb/m7cl9km13yzEUJrwXMyQvZtM=;
        b=A0ewlUM4IgzNdN79RWh2br9hjH4eOUeFl6S8FsOMMhG5RuPIU9v1bWcumrn228YgSnDQ6J
        yHEUtnqLJkhqqyppxC0kC4L2J3UWW4r+WeVb8k/rLdJ/Hp+J954kLTo6KbS2UZejP/D7jY
        MAPopu1T7w//ZgjcbEAE+pZpFMZnxcg=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-320-ZyrC7x46PaucaFZt8eaF4A-1; Wed, 10 Jun 2020 09:58:55 -0400
X-MC-Unique: ZyrC7x46PaucaFZt8eaF4A-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 01680100A614;
        Wed, 10 Jun 2020 13:58:53 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.192.78])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 1AE3D5C1BD;
        Wed, 10 Jun 2020 13:58:48 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>, linux-kernel@vger.kernel.org
Subject: [PATCH 0/2] KVM: selftests: avoid test failures with 'nested=0'
Date: Wed, 10 Jun 2020 15:58:45 +0200
Message-Id: <20200610135847.754289-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Commit 33b22172452f ("KVM: x86: move nested-related kvm_x86_ops to a
separate struct") made nested hooks (e.g. ->get_state(), ->enable_evmcs())
always available, even when kvm module is loaded with 'nested=0'. Assuming
the change was intentional, update selftests to not fail in this situation.

Vitaly Kuznetsov (2):
  KVM: selftests: do not substitute SVM/VMX check with
    KVM_CAP_NESTED_STATE check
  KVM: selftests: Don't probe KVM_CAP_HYPERV_ENLIGHTENED_VMCS when
    nested VMX is unsupported

 .../testing/selftests/kvm/include/x86_64/svm_util.h |  1 +
 tools/testing/selftests/kvm/include/x86_64/vmx.h    |  1 +
 tools/testing/selftests/kvm/lib/x86_64/svm.c        | 10 +++++++---
 tools/testing/selftests/kvm/lib/x86_64/vmx.c        |  9 +++++++--
 tools/testing/selftests/kvm/x86_64/evmcs_test.c     |  5 +++--
 tools/testing/selftests/kvm/x86_64/hyperv_cpuid.c   |  3 ++-
 tools/testing/selftests/kvm/x86_64/smm_test.c       | 13 +++++++------
 tools/testing/selftests/kvm/x86_64/state_test.c     | 13 +++++++------
 8 files changed, 35 insertions(+), 20 deletions(-)
```
