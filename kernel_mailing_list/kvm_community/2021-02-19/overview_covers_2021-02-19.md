

#### [PATCH 0/7] hw/kvm: Exit gracefully when KVM is not supported
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>

```c
From patchwork Fri Feb 19 11:44:21 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
 <philmd@redhat.com>
X-Patchwork-Id: 12095121
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 8C053C433E0
	for <kvm@archiver.kernel.org>; Fri, 19 Feb 2021 11:46:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3D18864EB3
	for <kvm@archiver.kernel.org>; Fri, 19 Feb 2021 11:46:30 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230375AbhBSLqH (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 19 Feb 2021 06:46:07 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:23637 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S230222AbhBSLqB (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 19 Feb 2021 06:46:01 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1613735074;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=aBiPAh6j0La2jswV89eyq5qlhizmmpayYHhAIblEKKQ=;
        b=C3zKWfLM5MrEwuKltoQbAerZTNU10TdB5xlVeMHOPbAwOBbCFMaGXH4AIQWpKacL10xc3n
        AXLe1gQwxvq63XAdmpVJaLA1ZtPnVLVUURz9jkQkYW/jxdFSb08dl7mCSIb9WefJF6K5/Y
        cYZE4ARBil08WZMsq7RsDWL/a7h3kQM=
Received: from mail-wr1-f69.google.com (mail-wr1-f69.google.com
 [209.85.221.69]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-252-_O25KnmQMwSLdq4cLQsL9Q-1; Fri, 19 Feb 2021 06:44:32 -0500
X-MC-Unique: _O25KnmQMwSLdq4cLQsL9Q-1
Received: by mail-wr1-f69.google.com with SMTP id f5so2346977wro.7
        for <kvm@vger.kernel.org>; Fri, 19 Feb 2021 03:44:32 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=aBiPAh6j0La2jswV89eyq5qlhizmmpayYHhAIblEKKQ=;
        b=BNGKl+cXE5+FvpH7zQFQJaZbS7QZNTer5Rf+PpbuGvADrS0cKsnxTt9oWXzuGkMYbl
         Ga1ZSg8An0itDA9DTsqtU+F59Cf+Kb4RtyvriW6NCP1R1yQAluxQRWBjd+BTVfsGmaNZ
         cMl8TdULBHJztT363LW9z81kuk0lu5HMJpaFL9Ax5s/ZHx0a6LfXVGJ2Pi9+pxC3TWxi
         N+2Vj/QsxaC9oQKv4tOLJZvsffvCjoaP5togJb4awoQE4B3lyXVeq28TWZcRuzuI0ZVh
         DScxk1vHxExJnvfnLiW62UjpW/kPJF0x2Hl7hSVC6ZV4vKVcMrRf22U9cXMlXeZ/fy8k
         fKZQ==
X-Gm-Message-State: AOAM533sn1Qg1nK+VWYU1sDCD6B83o6PI/Nb7WDHTCc+8r5ttWa4p5wY
        mnuLJWSk2FnC34qq9MTvR7b+mAnWVjJyHzgcleymK5fa579tqjK99yVuQZmhXQzFlNL/DXu1JnW
        NBeshOC05TvyK
X-Received: by 2002:a05:600c:8a2:: with SMTP id
 l34mr7983459wmp.4.1613735071626;
        Fri, 19 Feb 2021 03:44:31 -0800 (PST)
X-Google-Smtp-Source: 
 ABdhPJzCQmJUMzqBp58GRknzlFcK+50J5x/1xbRxspDX0PSKwBAjo2a1yxhfME/pP4E86Lbkjw1cYw==
X-Received: by 2002:a05:600c:8a2:: with SMTP id
 l34mr7983425wmp.4.1613735071474;
        Fri, 19 Feb 2021 03:44:31 -0800 (PST)
Received: from localhost.localdomain (68.red-83-57-175.dynamicip.rima-tde.net.
 [83.57.175.68])
        by smtp.gmail.com with ESMTPSA id
 l17sm1537098wmq.46.2021.02.19.03.44.29
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 19 Feb 2021 03:44:31 -0800 (PST)
From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>
To: qemu-devel@nongnu.org
Cc: Radoslaw Biernacki <rad@semihalf.com>,
 Paolo Bonzini <pbonzini@redhat.com>, qemu-s390x@nongnu.org,
 Greg Kurz <groug@kaod.org>, Marcel Apfelbaum <marcel.apfelbaum@gmail.com>,
 qemu-arm@nongnu.org, Cornelia Huck <cohuck@redhat.com>,
 Aleksandar Rikalo <aleksandar.rikalo@syrmia.com>, =?utf-8?q?Philippe_Mathie?=
	=?utf-8?q?u-Daud=C3=A9?= <f4bug@amsat.org>,
 BALATON Zoltan <balaton@eik.bme.hu>, Huacai Chen <chenhuacai@kernel.org>,
 Aurelien Jarno <aurelien@aurel32.net>,
 Richard Henderson <richard.henderson@linaro.org>,
 "Edgar E. Iglesias" <edgar.iglesias@gmail.com>,
 Christian Borntraeger <borntraeger@de.ibm.com>,
 Leif Lindholm <leif@nuviainc.com>, Alistair Francis <alistair@alistair23.me>,
 Thomas Huth <thuth@redhat.com>, Peter Maydell <peter.maydell@linaro.org>,
 Eduardo Habkost <ehabkost@redhat.com>, Jiaxun Yang <jiaxun.yang@flygoat.com>,
 Halil Pasic <pasic@linux.ibm.com>, David Hildenbrand <david@redhat.com>,
 qemu-ppc@nongnu.org,
 =?utf-8?q?Herv=C3=A9_Poussineau?= <hpoussin@reactos.org>,
 David Gibson <david@gibson.dropbear.id.au>,
 Mark Cave-Ayland <mark.cave-ayland@ilande.co.uk>, kvm@vger.kernel.org,
	=?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>
Subject: [PATCH 0/7] hw/kvm: Exit gracefully when KVM is not supported
Date: Fri, 19 Feb 2021 12:44:21 +0100
Message-Id: <20210219114428.1936109-1-philmd@redhat.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

This series aims to improve user experience by providing
a better error message when the user tries to enable KVM
on machines not supporting it.

Regards,

Phil.

Philippe Mathieu-Daudé (7):
  accel/kvm: Check MachineClass kvm_type() return value
  hw/boards: Introduce 'kvm_supported' field to MachineClass
  hw/arm: Set kvm_supported for KVM-compatible machines
  hw/mips: Set kvm_supported for KVM-compatible machines
  hw/ppc: Set kvm_supported for KVM-compatible machines
  hw/s390x: Set kvm_supported to s390-ccw-virtio machines
  accel/kvm: Exit gracefully when KVM is not supported

 include/hw/boards.h        |  6 +++++-
 accel/kvm/kvm-all.c        | 12 ++++++++++++
 hw/arm/sbsa-ref.c          |  1 +
 hw/arm/virt.c              |  1 +
 hw/arm/xlnx-versal-virt.c  |  1 +
 hw/mips/loongson3_virt.c   |  1 +
 hw/mips/malta.c            |  1 +
 hw/ppc/e500plat.c          |  1 +
 hw/ppc/mac_newworld.c      |  1 +
 hw/ppc/mac_oldworld.c      |  1 +
 hw/ppc/mpc8544ds.c         |  1 +
 hw/ppc/ppc440_bamboo.c     |  1 +
 hw/ppc/prep.c              |  1 +
 hw/ppc/sam460ex.c          |  1 +
 hw/ppc/spapr.c             |  1 +
 hw/s390x/s390-virtio-ccw.c |  1 +
 16 files changed, 31 insertions(+), 1 deletion(-)
```
#### [kvm-unit-tests PATCH v4 00/11] GIC fixes and improvements
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c
From patchwork Fri Feb 19 12:13:26 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexandru Elisei <alexandru.elisei@arm.com>
X-Patchwork-Id: 12095279
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A88D6C433DB
	for <kvm@archiver.kernel.org>; Fri, 19 Feb 2021 12:14:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5EA5D64EB8
	for <kvm@archiver.kernel.org>; Fri, 19 Feb 2021 12:14:26 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230348AbhBSMOY (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 19 Feb 2021 07:14:24 -0500
Received: from foss.arm.com ([217.140.110.172]:35010 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229804AbhBSMOT (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 19 Feb 2021 07:14:19 -0500
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 9BBC3ED1;
        Fri, 19 Feb 2021 04:13:33 -0800 (PST)
Received: from monolith.localdoman (unknown [172.31.20.19])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 BC28E3F73B;
        Fri, 19 Feb 2021 04:13:32 -0800 (PST)
From: Alexandru Elisei <alexandru.elisei@arm.com>
To: drjones@redhat.com, kvm@vger.kernel.org,
        kvmarm@lists.cs.columbia.edu
Cc: andre.przywara@arm.com, eric.auger@redhat.com
Subject: [kvm-unit-tests PATCH v4 00/11] GIC fixes and improvements
Date: Fri, 19 Feb 2021 12:13:26 +0000
Message-Id: <20210219121337.76533-1-alexandru.elisei@arm.com>
X-Mailer: git-send-email 2.30.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

What started this series is Andre's SPI and group interrupts tests [1],
which prompted me to attempt to rewrite check_acked() so it's more flexible
and not so complicated to review. When I was doing that I noticed that the
message passing pattern for accesses to the acked, bad_irq and bad_sender
arrays didn't look quite right, and that turned into the first 7 patches of
the series. Even though the diffs are relatively small, they are not
trivial and the reviewer can skip them for the more palatable patches that
follow. I would still appreciate someone having a look at the memory
ordering fixes.

Patch #8 ("Split check_acked() into two functions") is where check_acked()
is reworked with an eye towards supporting different timeout values or
silent reporting without adding too many arguments to check_acked().

After changing the IPI tests, I turned my attention to the LPI tests, which
followed the same memory synchronization patterns, but invented their own
interrupt handler and testing functions. Instead of redoing the work that I
did for the IPI tests, I decided to convert the LPI tests to use the same
infrastructure.

For v2, I ran tests on the following machines and didn't see any issues:

- Ampere EMAG: all arm64 tests 10,000+ times (combined) under qemu and
  kvmtool.

- rockpro64: the arm GICv2 and GICv3 tests 10,000+ times under kvmtool (I
  chose kvmtool because it's faster than qemu); the arm64 gic tests (GICv2
  and GICv3) 5000+ times with qemu (didn't realize that ./run_tests.sh -g
  gic doesn't include the its tests); the arm64 GICv2 and GICv3 and ITS
  tests under kvmtool 13,000+ times.

For v3, because the changes weren't too big, I ran ./run_tests.sh for arm
and arm64 with qemu TCG on the my x86 machine; ran ./run_tests.sh for arm64
on rockpro64; and ran all the gic tests for arm and arm64 under kvmtool on
the rockpro64.

For v4, same tests as for v3.

Changes in v4:

 * Gathered Reviewed-by and Acked-by tags, thank you for the feedback!

 * Cosmetic changes to the commit message for #4 ("arm/arm64: gic: Remove
   unnecessary synchronization with stats_reset()").

 * Dropped the unneeded wmb() before its_send_invall() in #11 ("arm64: gic:
   Use IPI test checking for the LPI tests") (the wmb is present in
   its_send_inval->its_send_single_command->its_post_commands->writeq.

Changes in v3:

* Gathered Reviewed-by tags, thank you for the feedback!

* Reworked patch #2 and renamed it to "lib: arm/arm64: gicv2: Document
  existing barriers when sending IPIs". The necessary barriers were already in
  place in writel/readl. Dropped the R-b tag.

* Removed the GICv2 smp_rmb() barrier in #4 ("arm/arm64: gic: Remove unnecessary
  synchronization with stats_reset") because of the rmb() already present in
  readl() and reworded the commit message accordingly. Dropped the R-b tag.

* Commented the extra delay in wait_for_interrupts() for patch #8
  ("arm/arm64: gic: Split check_acked() into two functions").

* Minor change to the commit message for #10 ("arm64: gic: its-trigger:
  Don't trigger the LPI while it is pending") as per Andre's suggestion.

* Dropped patch #11 ("lib: arm64: gic-v3-its: Add wmb() barrier before INT
  command") because the wmb() was already present in __its_send_int() ->
  its_send_single_command() -> its_post_commands() -> writeq().

Changes in v2:

* Gathered Reviewed-by tags, thank you for the feedback!

* Modified code comments in #1 ("lib: arm/arm64: gicv3: Add missing barrier
  when sending IPIs") as per review suggestions.

* Moved the barrier() in gicv2_ipi_send_self() from #3 ("arm/arm64: gic:
  Remove memory synchronization from ipi_clear_active_handler()") to #2
  ("lib: arm/arm64: gicv2: Add missing barrier when sending IPIs").

* Renamed #3, changed "[..] Remove memory synchronization [..]" to
  "[..] Remove SMP synchronization [..]".

* Moved the removal of smp_rmb() from check_spurious() from #5 ("arm/arm64:
  gic: Use correct memory ordering for the IPI test") to patch #7
  ("arm/arm64: gic: Wait for writes to acked or spurious to complete").

* Fixed typos in #8 ("arm/arm64: gic: Split check_acked() into two
  functions").

* Patch #10 ("arm64: gic: its-trigger: Don't trigger the LPI while it is
  pending") is new. It was added to fix an issue found in v1 [2].

* Patch #11 ("lib: arm64: gic-v3-its: Add wmb() barrier before INT
  command") is also new; it was split from #12 ("arm64: gic: Use IPI test
  checking for the LPI tests") following review comments.

* Removed the now redundant call to stats_reset() from its_prerequisites()
  in #12 ("arm64: gic: Use IPI test checking for the LPI tests").

[1] https://lists.cs.columbia.edu/pipermail/kvmarm/2019-November/037853.html
[2] https://www.spinics.net/lists/kvm-arm/msg43628.html

Alexandru Elisei (11):
  lib: arm/arm64: gicv3: Add missing barrier when sending IPIs
  lib: arm/arm64: gicv2: Document existing barriers when sending IPIs
  arm/arm64: gic: Remove SMP synchronization from
    ipi_clear_active_handler()
  arm/arm64: gic: Remove unnecessary synchronization with stats_reset()
  arm/arm64: gic: Use correct memory ordering for the IPI test
  arm/arm64: gic: Check spurious and bad_sender in the active test
  arm/arm64: gic: Wait for writes to acked or spurious to complete
  arm/arm64: gic: Split check_acked() into two functions
  arm/arm64: gic: Make check_acked() more generic
  arm64: gic: its-trigger: Don't trigger the LPI while it is pending
  arm64: gic: Use IPI test checking for the LPI tests

 lib/arm/gic-v2.c |   6 +
 lib/arm/gic-v3.c |   6 +
 arm/gic.c        | 336 +++++++++++++++++++++++++----------------------
 3 files changed, 188 insertions(+), 160 deletions(-)
```
#### [PATCH v2 0/3] KVM: x86: dump_vmcs: don't assume GUEST_IA32_EFER,
##### From: David Edmondson <david.edmondson@oracle.com>

```c
From patchwork Fri Feb 19 14:46:29 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Edmondson <david.edmondson@oracle.com>
X-Patchwork-Id: 12095525
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,
	UNPARSEABLE_RELAY,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 0E428C433DB
	for <kvm@archiver.kernel.org>; Fri, 19 Feb 2021 14:48:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B864E64EB2
	for <kvm@archiver.kernel.org>; Fri, 19 Feb 2021 14:48:44 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229571AbhBSOsn (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 19 Feb 2021 09:48:43 -0500
Received: from userp2130.oracle.com ([156.151.31.86]:39166 "EHLO
        userp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229691AbhBSOsf (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 19 Feb 2021 09:48:35 -0500
Received: from pps.filterd (userp2130.oracle.com [127.0.0.1])
        by userp2130.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 11JEjQEd029382;
        Fri, 19 Feb 2021 14:46:42 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : content-transfer-encoding : content-type :
 mime-version; s=corp-2020-01-29;
 bh=YMJqVqao4ydj1ukxOpSEj8SNvF7Jt/Ioka1r/ab2XRw=;
 b=gadFsUe9LLKdH5pH0cQJMOE9iWs9ennMJDlGQxc09zlB36s7b2ErEywUXkWaRY/ElSOQ
 JPWe8aIIoCgCFIEi8jjwqgv2+aIQ7NFi2LV+bZ5s0cvGAN8Cx3j6L0s8SYDjrjKwSbBn
 LqYp6dlVMRJIzCBSPXLHDNoLYqXGmJQpv5eicskITqqdqZ0E6SBoaeL4ISPhmNP/EU5E
 gLuer3ge81OXdxPoDrpOYL/exY3NKzayLoLmRkmdnBm63nnmBtXQW4XbrLw3JYuoegZw
 HOl/fC7plqc7lRvUVWlPNfKpIqEbibNz9Z8MdWLUvYr1aC+WmtbZqMCT4QCyl/BF19cB +g==
Received: from aserp3020.oracle.com (aserp3020.oracle.com [141.146.126.70])
        by userp2130.oracle.com with ESMTP id 36p66r9r5w-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 19 Feb 2021 14:46:41 +0000
Received: from pps.filterd (aserp3020.oracle.com [127.0.0.1])
        by aserp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 11JEkKfS112347;
        Fri, 19 Feb 2021 14:46:41 GMT
Received: from nam10-bn7-obe.outbound.protection.outlook.com
 (mail-bn7nam10lp2102.outbound.protection.outlook.com [104.47.70.102])
        by aserp3020.oracle.com with ESMTP id 36prp2yfrq-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 19 Feb 2021 14:46:40 +0000
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=nHlqz1b/qszlJ39dCbMPu+tB9MH5aPqMjxAGCdGt1lPM+o0suYMFatJG9uFIv0xCPw5FVPuGIujBsnA3P0QQPLsbob3rK9qmDVDKStZxiKYltLA2AVICvZ9bJn7nlv4RCoQ1ZnaMVSIuZdnoI7UXxX4OtaVZvxeup7dR5gKktxllRfKgxlSV321FVhjmN+MxcUZxGaYM4+bMJNBC1IpcgIXOly+f/9sv2VMp4IIB+hSxL2kPM3QBPI1WecZaAYx+XlehzzRST8IXKPd3T35UtA7h1COqDF2HrI+Fs2JW5Ofwy/m70RwFAHPRGtiJhGNXjRFiJf9R6chE21B1gWJjAg==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=YMJqVqao4ydj1ukxOpSEj8SNvF7Jt/Ioka1r/ab2XRw=;
 b=hvqnsDYSn9FGldzN54d4u52iX9W6UDGyfPHC3nieJmov7EkxUOANJLgPmh5aK7ienZ9TrX4XJnS6Y9creb42aj9kMmBarnxAIBW/YXnEoMT4lmAH1i3oXrwHp70iC7zzgVNPUCeAS6qT2YviCeWHaO0scu/55PhzpTPMI5kygID4aivvFuw/RhIXj2a2394oLgybJ/koqu/kA4yZGEzg8p6HFbblo/t3GRy1mG+FaeGjkzd1HuD8lgK9b9prAqeThrJ+W83VVrscVqigj8kv9hVE/dglqXc5zZP/m5T8908ToN9ApqmrdI6IE3hYFuqUM4KMurIxamJKScRy55ryTw==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=oracle.com; dmarc=pass action=none header.from=oracle.com;
 dkim=pass header.d=oracle.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=oracle.onmicrosoft.com; s=selector2-oracle-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=YMJqVqao4ydj1ukxOpSEj8SNvF7Jt/Ioka1r/ab2XRw=;
 b=jV3QFJ6Us4feUbWTRtqURZkJcw60veMy3muo1fQXZ6QLi3DSmfrR/cMtmhhtiAekJNKODbo27iUTQdi/+kmAMlBCbpbl+43GCeMKxdpISS4HtpHROmvGO84WM0PRcowT1lXtVZSfR19Fn/B4cN3Ls9hR5m30BXWQaiDueWsvRBk=
Authentication-Results: zytor.com; dkim=none (message not signed)
 header.d=none;zytor.com; dmarc=none action=none header.from=oracle.com;
Received: from DM6PR10MB3148.namprd10.prod.outlook.com (2603:10b6:5:1a4::21)
 by DM6PR10MB3067.namprd10.prod.outlook.com (2603:10b6:5:6e::29) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3846.29; Fri, 19 Feb
 2021 14:46:39 +0000
Received: from DM6PR10MB3148.namprd10.prod.outlook.com
 ([fe80::f871:5965:2081:3934]) by DM6PR10MB3148.namprd10.prod.outlook.com
 ([fe80::f871:5965:2081:3934%5]) with mapi id 15.20.3846.027; Fri, 19 Feb 2021
 14:46:39 +0000
From: David Edmondson <david.edmondson@oracle.com>
To: linux-kernel@vger.kernel.org
Cc: "H. Peter Anvin" <hpa@zytor.com>, Joerg Roedel <joro@8bytes.org>,
        x86@kernel.org, Thomas Gleixner <tglx@linutronix.de>,
        kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Ingo Molnar <mingo@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Jim Mattson <jmattson@google.com>,
        Borislav Petkov <bp@alien8.de>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        David Edmondson <david.edmondson@oracle.com>
Subject: [PATCH v2 0/3] KVM: x86: dump_vmcs: don't assume GUEST_IA32_EFER,
 show MSR autoloads/autosaves
Date: Fri, 19 Feb 2021 14:46:29 +0000
Message-Id: <20210219144632.2288189-1-david.edmondson@oracle.com>
X-Mailer: git-send-email 2.30.0
X-Originating-IP: [2001:8b0:bb71:7140:64::1]
X-ClientProxiedBy: LO4P123CA0496.GBRP123.PROD.OUTLOOK.COM
 (2603:10a6:600:1ab::15) To DM6PR10MB3148.namprd10.prod.outlook.com
 (2603:10b6:5:1a4::21)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from disaster-area.hh.sledj.net (2001:8b0:bb71:7140:64::1) by
 LO4P123CA0496.GBRP123.PROD.OUTLOOK.COM (2603:10a6:600:1ab::15) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3846.38 via Frontend
 Transport; Fri, 19 Feb 2021 14:46:36 +0000
Received: from localhost (disaster-area.hh.sledj.net [local])   by
 disaster-area.hh.sledj.net (OpenSMTPD) with ESMTPA id 98123fb1;
      Fri, 19 Feb 2021 14:46:32 +0000 (UTC)
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 17cd4398-b5e6-4042-435f-08d8d4e529a9
X-MS-TrafficTypeDiagnostic: DM6PR10MB3067:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM6PR10MB3067BEE0D143916AD255C81188849@DM6PR10MB3067.namprd10.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:3826;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 I+udt5Gw0z8n7Z8SdPTHzQnSu1X8HvoxFQlZfTFMby4UExILAgslWDCsp6vXhRjg89levh/Mm28kDBBU0PgRI7EjpI2j+X2OAoIrCIEIUXu0L9aPqvjimv8Oe+zDFQ7F9qi2r+Bsy5KXGMPZ/m+MLpaOyexKyX6M2lP5vsoFM7fSm3clMI63lW+Xz6oWrJ3tGo88vGUQtqSab525f+z9ozWdHnOUIcWMIWeNlLGO5hyYpewFuBlk+w04cwZjoYH5sBhyvX0n8IhERba0gxracPbNzAFj1AWwbEOCFgUoKAmAjFh1ZGMrICq5K7gwN5+gJ8HZdgYMuAlDajXDW1tGuHPCo2XXfspsTBjRH5GJHSPDo/eekAEN9FifjPzInjjQMC2TWCWFZQfqrkiS6cSBfNF+h+g03xdvNXF0YwlPEl/e+0iC6lOLkhRIsBO8LADLJAYTUexAoEJPOeR3aq5+hus3zLfJ/S4Hn8fqzuMTtHRRLyIIQEaoAqoNmKsN+lfFPm1PCWl1qH5mlo9v6tOXaQ==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM6PR10MB3148.namprd10.prod.outlook.com;PTR:;CAT:NONE;SFS:(39860400002)(396003)(136003)(346002)(366004)(376002)(2616005)(36756003)(5660300002)(316002)(6916009)(83380400001)(186003)(66946007)(44832011)(7416002)(4744005)(2906002)(8936002)(1076003)(6666004)(478600001)(86362001)(66556008)(107886003)(8676002)(54906003)(4326008)(66476007)(52116002);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 3XHmd7yD+72FgeLv6pklhbIGNzjkh5qCnj+EGuS/7Foz/hy9sY+kH3Zk/+Th+ZIuKHCG0IDCSi0sXlCoKETINwNZmLGAuP8i91ZPjHFFLzxy4mi5RUJEd9d8o0McC8iiINV9rqxyqVLYp+JVaq3b0WL3upUJkcOqKQNzkblc1l1htQyjsYB+meO9yuWas3Zc6rzD/uofEEzbMBQOL5jyfouMW3cuzKa5Sry2p669dXPduesB5IoTT38EL/JWy2k4n+DcYtTS+k1TWcmVjs9FuWzuMzK77K1YpfKRAJhUSAm97GtdzHm6YkoMm84zkpWUQA9vj7r5z43ocomZ4DO4IqkaAd/YrNwi9uhs5QWwtMaEH9kZwJAn0FzNvS0t9N8BSaJ76XKTpgla7JyAa57lafgodr7Rg/9Vl6CSFIfBZGwJmOM5Qz4R+2nVWZsAQUQJdiOdj9t01asGRAbFYETXSMyf0MRSnqjKkxrhqAKOUx9mefc7MU96Vn2tFKoLKwfv5obJCGE5hCCurOecCyRhZQld0+KEKN5PccKHaPT6ufHSZ88tHCNQJX6b+qyTe1u2V1YurG1lJZJWYLK06TLFNiLDD0QjKoNUTu1BdxhXWiELyHnKE4+zicOIPlJGVAdWZXR7/5WFr+TlUd2O4q1WboLkx6D+dKGAiY/1lsea0bWv1FaWSWCDvtEvzYr1DJ6Z+o34VrCC1XyXp1mAC53qnTzOL3jtPvKTyaP+KxT5u2szzueBIY73oOecd8sWAJBBnZOgbE6379PJZFT1W34rYDEFkSgEAPkChv4gaB27Hzj3itloGQBVMbcOPDb0Du1wDe00zvdRry2lacaxmFHeYJ62oNeSwJOKNjwlcdTflgken0QiTcCMJ8B1m0bfnNpQd1+vbZoAnGK41CsA8rysRx8r293nsjqVZdVfkCzqJTdFnL9iFRsAagD3aP+nFYQ6eqeWHtEvrfG2fTO9EewSuFlwNNUG2bO+ggPhsBDgGy+kp0dprRjfSKpFyv7+cXWSr7YKWHakZYWKqoIw7FRSljlOEu8Dy2MdIZaNMQNsNDP2qWsUEYk32UnVQSswK6OPiV89wylzE/vMTnScqKMytR1mwDPL0EBB/uOxJaVwf26BU3MIizl2WS06PYa23vHR/g+CbuDqRezKRwgypYGfyVhqNUFndHCi5tA3Tv2szPBAsww/oA1BajaCasfWMlHfwn45vd2ud4YV7kjs8zw/odt72M/bANEj5OFjw3m/1K43EzIH1VFm/VjzZFiwV2vlvac6WCaYVFZyfQLG+P2xWOUYUclYNrW/LdjXLKkl832AA9Ytu9H0chU1bxzZntACggXTk5wCeZfkMUYVc7GdZw==
X-OriginatorOrg: oracle.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 17cd4398-b5e6-4042-435f-08d8d4e529a9
X-MS-Exchange-CrossTenant-AuthSource: DM6PR10MB3148.namprd10.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 19 Feb 2021 14:46:39.2338
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 4e2c6054-71cb-48f1-bd6c-3a9705aca71b
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 X90W9Fed8ZmcbMT6ET4KVbDEI2TPgaAgPTW+0f7oh1hWhwhGirsBQwPlWKEP8zvEL3MdnKUoScrRtLEEpf4xiLWtDbC/6YiuektjD3gitjw=
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6PR10MB3067
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9899
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 phishscore=0
 mlxlogscore=778
 bulkscore=0 suspectscore=0 spamscore=0 malwarescore=0 mlxscore=0
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2102190119
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9899
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 lowpriorityscore=0 suspectscore=0
 impostorscore=0 priorityscore=1501 clxscore=1015 spamscore=0 mlxscore=0
 phishscore=0 malwarescore=0 bulkscore=0 adultscore=0 mlxlogscore=999
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2102190119
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

v2:
- Don't use vcpu->arch.efer when GUEST_IA32_EFER is not available (Paolo).
- Show EFER and PAT seperately, as appropriate.
- Dump the MSR autoload/autosave lists (Paolo).

David Edmondson (3):
  KVM: x86: dump_vmcs should not assume GUEST_IA32_EFER is valid
  KVM: x86: dump_vmcs should not conflate EFER and PAT presence in VMCS
  KVM: x86: dump_vmcs should include the autoload/autostore MSR lists

 arch/x86/kvm/vmx/vmx.c | 48 ++++++++++++++++++++++++++++--------------
 arch/x86/kvm/vmx/vmx.h |  2 +-
 2 files changed, 33 insertions(+), 17 deletions(-)
```
#### [PATCH v2 0/3] vfio/type1: Batch page pinning
##### From: Daniel Jordan <daniel.m.jordan@oracle.com>

```c
From patchwork Fri Feb 19 16:13:02 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Daniel Jordan <daniel.m.jordan@oracle.com>
X-Patchwork-Id: 12095815
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 046E4C433E0
	for <kvm@archiver.kernel.org>; Fri, 19 Feb 2021 16:14:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C015F64EDC
	for <kvm@archiver.kernel.org>; Fri, 19 Feb 2021 16:14:44 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229947AbhBSQOb (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 19 Feb 2021 11:14:31 -0500
Received: from aserp2120.oracle.com ([141.146.126.78]:46672 "EHLO
        aserp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229527AbhBSQOW (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 19 Feb 2021 11:14:22 -0500
Received: from pps.filterd (aserp2120.oracle.com [127.0.0.1])
        by aserp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 11JG9kIc047729;
        Fri, 19 Feb 2021 16:13:23 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : content-transfer-encoding : content-type :
 mime-version; s=corp-2020-01-29;
 bh=bVjF1+RjAnffvnw7iAX0KyOJrk/f9r164jRnov3l7qE=;
 b=kowaW01je9JNDxC+EjxnMRGkhRAXGEWllCR/e4JEIy4RQmdiHJ9zO8S1YkjWnSsTnaDk
 pDUzyD0b7Cmz7ni3UT2Q0B2Na39IIwCyHb3hXGEEGzZX4asbfT4ZPTWiqDWUkc5MQFI1
 uR0o9d3Ebdg+jMkk5bIlkbsRVlca5g+bC/MJBsnDVtIsJycQOhL8SEIk87Jq3S8+Tre7
 35F2fZz9+MJcgJla95fTv4R6O01is84SauvYE+KSxnJEWCD+6jq4lABT1BHFRCgh+0gZ
 T/h/obE85OsbUYrFH9uS2hnFxMzmfQf2gMVWVlxNSZ+XmWKtiumXro+oObu1JJxai96I nw==
Received: from userp3030.oracle.com (userp3030.oracle.com [156.151.31.80])
        by aserp2120.oracle.com with ESMTP id 36pd9ahj5n-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 19 Feb 2021 16:13:22 +0000
Received: from pps.filterd (userp3030.oracle.com [127.0.0.1])
        by userp3030.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 11JGAHqc113531;
        Fri, 19 Feb 2021 16:13:22 GMT
Received: from nam12-bn8-obe.outbound.protection.outlook.com
 (mail-bn8nam12lp2168.outbound.protection.outlook.com [104.47.55.168])
        by userp3030.oracle.com with ESMTP id 36prq226rn-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 19 Feb 2021 16:13:21 +0000
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=eefgWqWZoFrMvktIlGSoUsy1dpiIRHoibZewghIVgXU6R3nvdgdv3Cme+A9uovW/5HTVXw/9WuOn/JGefU4XpILmY+vfYf1S9oHI/2/iEF+mZHeSTpgQyhKgz6/AAiQf27PIGBQYZ2Pez4MtLHMZy/m7eCIfjbMnVWAyRA4GGDTdoVFtKBuDAkXGMyvvUjRK2lrDjQW4nP9s+j7apzFkcLSKGa9ljo5hY3KdI9i+0G9ZL+69G1et2yTaRYcRbn7ln0x9hKv+y9WKKMkguyDI6xwdUa0ow3pMsYecCu0/tJLBm0LwdszaUl91QKPWXaMiePQzUCOOpAjGwvFfgTsyng==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=bVjF1+RjAnffvnw7iAX0KyOJrk/f9r164jRnov3l7qE=;
 b=VhkQz3RBFMlzUu23aGim6qQ+1Qvg2+zAntWrY4gzHSKl411X8McH42CujWi1yhqa8vFGXMD7NSwonhsxf/gdRtQtZpsIK+Sy76w0wWNXUEPVZpcTfL7THNRDApbRcVxuPImFeXfgYsQFRSAkJx98qusqrjXcrfOjiwcvfVEFBRMPwJm0XDzk3aZdaOTc/oVo9tcZXBW94aYxe7I5SoVMgAgx33HwksDQ2N3OqxXQe44Vl9U8yXZBsnDCX7QIp7EdJORUEcJFN9UJEH1UQ3uVdLF8WS32D8zLK4J3ZnSLWfgDkL1b50bBdQ6KRecDv8wSR4t6R63DQXfVYWTFccSZDQ==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=oracle.com; dmarc=pass action=none header.from=oracle.com;
 dkim=pass header.d=oracle.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=oracle.onmicrosoft.com; s=selector2-oracle-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=bVjF1+RjAnffvnw7iAX0KyOJrk/f9r164jRnov3l7qE=;
 b=o/az6rCpRFncgmJU72DSMMfe3XFHQwTa1hibmy4hVlatoV3bPrgWeTWk8PahQ/h+yNAN5tDestFOXrNGJnet5Lwramgpx7VU06PcRE4blUWjG6KyZCLzJBlo78VshHnQbXYbizglrb+u4iwWErUfBLBvzHQag0q5hvvUk3TAqYE=
Authentication-Results: redhat.com; dkim=none (message not signed)
 header.d=none;redhat.com; dmarc=none action=none header.from=oracle.com;
Received: from MWHPR10MB1774.namprd10.prod.outlook.com (2603:10b6:301:9::13)
 by MWHPR1001MB2157.namprd10.prod.outlook.com (2603:10b6:301:32::24) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3825.27; Fri, 19 Feb
 2021 16:13:19 +0000
Received: from MWHPR10MB1774.namprd10.prod.outlook.com
 ([fe80::24eb:1300:dd70:4183]) by MWHPR10MB1774.namprd10.prod.outlook.com
 ([fe80::24eb:1300:dd70:4183%3]) with mapi id 15.20.3846.042; Fri, 19 Feb 2021
 16:13:19 +0000
From: Daniel Jordan <daniel.m.jordan@oracle.com>
To: Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>
Cc: Jason Gunthorpe <jgg@nvidia.com>,
        Matthew Wilcox <willy@infradead.org>,
        Pavel Tatashin <pasha.tatashin@soleen.com>,
        Steven Sistare <steven.sistare@oracle.com>,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Daniel Jordan <daniel.m.jordan@oracle.com>
Subject: [PATCH v2 0/3] vfio/type1: Batch page pinning
Date: Fri, 19 Feb 2021 11:13:02 -0500
Message-Id: <20210219161305.36522-1-daniel.m.jordan@oracle.com>
X-Mailer: git-send-email 2.30.1
X-Originating-IP: [98.229.125.203]
X-ClientProxiedBy: BL0PR0102CA0052.prod.exchangelabs.com
 (2603:10b6:208:25::29) To MWHPR10MB1774.namprd10.prod.outlook.com
 (2603:10b6:301:9::13)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from localhost.localdomain (98.229.125.203) by
 BL0PR0102CA0052.prod.exchangelabs.com (2603:10b6:208:25::29) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3868.28 via Frontend
 Transport; Fri, 19 Feb 2021 16:13:18 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: e11312b1-1146-42ea-070d-08d8d4f145a9
X-MS-TrafficTypeDiagnostic: MWHPR1001MB2157:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <MWHPR1001MB215781D75E9EE81DAD4F3041D9849@MWHPR1001MB2157.namprd10.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:3826;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 U3CttiRU4H6WM9KUzWCRZG4ljEz38tLIpavZ9WqCMjlJvL1GdLJoHBsZqNGn0OigXxkOW//wV/my4VsNuhZ8vae/gpVMwR1291tCT9C+nsOhW9crn44VY44vLQErkh/VNM32HHcCMRyL8ZTtmBnJsdxu5mf91GuE8AyAa2gJm/UPd6ruZsntvw0xkux2FUJpErVaaQoy0HzapwfpGpo57x/vG1wWVF/QLsNPO3T36nB1j9AQU1zBKOi9A4z1ZWsMi8CFuCpo2pNy8q8jIb0N1DThqwtYUBRWcvvHftXIBfZ9/jQW4S58ZDbuGqYqC7p06zVIerCdXhPvuf3yWkfkpRyyP1X3IQ9OG9DRBv2D/6q8Njt0WSZd3P+qp/EMTwaA35vV03zi/ysgWM20Fp5W0EMRBs1X46P/gWm2kDYts3nAEXq4zbvTWU6aZti06LaB7kkjPjz9aw0/dx8mFdEIoaHAmoB5+TmCUaaN0Nf1GpB8b96piFrxj57aliqEKXHPk57UQgZdFg+aRQU5bFJdtBoOXC2ejquswdB4uMOHnJ2AHKN5ERdXDh7LonqMthkR8MiTVDR210kB4FLTd+cRxg==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:MWHPR10MB1774.namprd10.prod.outlook.com;PTR:;CAT:NONE;SFS:(396003)(39860400002)(346002)(136003)(366004)(376002)(8936002)(107886003)(66946007)(1076003)(6486002)(6506007)(956004)(5660300002)(86362001)(83380400001)(8676002)(66556008)(54906003)(478600001)(103116003)(2616005)(110136005)(6666004)(69590400012)(2906002)(52116002)(26005)(186003)(36756003)(6512007)(66476007)(16526019)(316002)(4326008);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 7PrW7/G2xdlLBTUnbwTC+acsu/Dj4U4sAAu8gFE7A3Uj9s0pVj7h35H+jWrpyn/Hyl3DJ4LA3ij6RJANnqEIFfnh2fSNNzNFkayPmicMdosZ5SNgP+ZKHwBfPf93HwkvOLA+ytbbdXhc9NViZP3GrxAEszKZl1zPgDhdhmsDygjyL8wY2ScHwpqp+fZPR7U5f/PO7Yu/+Dm85Z9ejVO3AV6HrYRIm60vcjxkMt18jLvZFwg1RJI1N6pXki3N6Xm6gE+b23T6a6hK1EUvmkgVuwshYEhzPst8Ev7/XnfsnoEfBIq8LtY08cdN7nYemR5mnyt4s4bxesB0BW5LUHBpgQ6kXGXpDEFRelhK3p4+fa5yBrtixOJAPBvl4wLVoVUlEP8Ica0VkywViWM8e5/J8YEuElHHrlm2Gq5nwp+9UOEa0RisPApu2gLwhQbEKT53/fh2PJCF7mBv8Q/Ue1OuYhf7ARQ6++zlidBk7+RxYwF0DXaYRcRZ3sBHO9l7dX4pp7KRY2PyOv/aur12aonbKl+S75OLL1FhP+yf/DKZWoiW8UXdRNLhv9jcgo8gNuKucNaRR3QRtrjJyU850Dmeb5weVYrkFfn+x/QnznWOeliIjMHEoffBui+mUyGTpuwMsPirhkPgpYjBP/8yAZwekQnVikFgUW1qymi4XMLnpIrgRPFhpFW3E35wyi/3gQSAOFH2r8Qm6F/dFBuD/kV2shwiAvlDCQ8AfFOnOCzwnP+FYMhAwS1R1RxFJA092P9oEe5X7n/PIWR+csi6KJRNvuDk9kihDCkXMKNgLRi67Z4zeIEt+nQGYqyQEl7yEcTbVMuaCGxu1u2SLKITLrnC8wFq6rFDmxFe9DshCSVGbICgRU7jWfAYMgBSDpHeIdZ0iWhO0Exvtqq+WyszoN3OrhW6P1Jh+OZ27tqlUIivEOOgNxnIQwNhlyFOS+v4DCktk3Bx5se+AKIKUoNrMd4nbacCHfjDVi3LLH+toj4lezaHKW9bUdnupwlf2LZWE6rP7zekfXdMpPpj8teHDMdfGUh125Pd40gt2E73IHi/TOUbPlqBe3YTbsdCdom0iH1yRFNF4IJNoKsD42hsOAhQ3gI4PVMypgaRDlikOIM1dUIVWffL3aG9fxW1n1BhFU9G25vMBvCegWflnKgwiHY3Z3+Jxb0ucQnOYPULdkCux5hpKJNwBeTecH1fadXRlBQbnnXxtjTjJhp8LrpXMXTK9b6gtvABvIvtQktonxkBsF2a/HGOgl4+3V75OBP1XWqAU2HgCVIMWydsbUril7hfUR2JY0EtTJE+ls9l6ShSBC2dtyzOzbUuhS2Q7BqzbfML
X-OriginatorOrg: oracle.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 e11312b1-1146-42ea-070d-08d8d4f145a9
X-MS-Exchange-CrossTenant-AuthSource: MWHPR10MB1774.namprd10.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 19 Feb 2021 16:13:19.5816
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 4e2c6054-71cb-48f1-bd6c-3a9705aca71b
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 5ned8SBIbiHAp76DLCTpDA/4sQ+8JM0bVMIHUD+u8BGZCjq+ulmlqjxslql2eTECPxBQNcMc/1/Lo8HqNY0iaIxR5Se/6cho7njSsHxhX1k=
X-MS-Exchange-Transport-CrossTenantHeadersStamped: MWHPR1001MB2157
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9900
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 bulkscore=0
 mlxlogscore=999
 phishscore=0 adultscore=0 mlxscore=0 suspectscore=0 malwarescore=0
 spamscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2102190127
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9900
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 clxscore=1015
 impostorscore=0
 mlxscore=0 phishscore=0 mlxlogscore=999 spamscore=0 bulkscore=0
 priorityscore=1501 malwarescore=0 suspectscore=0 adultscore=0
 lowpriorityscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2102190127
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

v2:
 - Fixed missing error unwind in patch 3 (Alex).  After more thought,
   the ENODEV case is fine, so it stayed the same.

 - Rebased on linux-vfio.git/next (no conflicts).
---

The VFIO type1 driver is calling pin_user_pages_remote() once per 4k page, so
let's do it once per 512 4k pages to bring VFIO in line with other drivers such
as IB and vDPA.

qemu guests with at least 2G memory start about 8% faster on a Xeon server,
with more detailed results in the last changelog.

Thanks to Matthew, who first suggested the idea to me.

Daniel


Test Cases
----------

 1) qemu passthrough with IOMMU-capable PCI device

 2) standalone program to hit
        vfio_pin_map_dma() -> vfio_pin_pages_remote()

 3) standalone program to hit
        vfio_iommu_replay() -> vfio_pin_pages_remote()

Each was run...

 - with varying sizes
 - with/without disable_hugepages=1
 - with/without LOCKED_VM exceeded

I didn't test vfio_pin_page_external() because there was no readily available
hardware, but the changes there are pretty minimal.

Daniel Jordan (3):
  vfio/type1: Change success value of vaddr_get_pfn()
  vfio/type1: Prepare for batched pinning with struct vfio_batch
  vfio/type1: Batch page pinning

 drivers/vfio/vfio_iommu_type1.c | 215 +++++++++++++++++++++++---------
 1 file changed, 155 insertions(+), 60 deletions(-)

base-commit: 76adb20f924f8d27ed50d02cd29cadedb59fd88f
```
#### [PATCH v2 00/11] hw/accel: Exit gracefully when accelerator is
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>

```c
From patchwork Fri Feb 19 17:38:36 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
 <philmd@redhat.com>
X-Patchwork-Id: 12095911
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 191F1C433E0
	for <kvm@archiver.kernel.org>; Fri, 19 Feb 2021 17:40:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E366C60295
	for <kvm@archiver.kernel.org>; Fri, 19 Feb 2021 17:40:23 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229766AbhBSRkX (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 19 Feb 2021 12:40:23 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:51658 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S229658AbhBSRkW (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 19 Feb 2021 12:40:22 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1613756334;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=lykBUd6DAhrahT8nCJAC5FU9Ql8oesKH07nupx8xYdk=;
        b=LIXgwv60bbXZZIwcDQ5k5imvtugFoGSyk/vJ1Bny4rs/hfhyo1pGIW2lrWwXa1STjYL7aA
        7voQzyf/1T5wLwpLKktFTHSITkJzk6eLWwZ6sVMTYRPCeLnD5uHOnqlq9pDs3F4Kpn/Idg
        PzUyjlL8BkIi3Qry/IlDxDaeCRhXiZQ=
Received: from mail-wr1-f70.google.com (mail-wr1-f70.google.com
 [209.85.221.70]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-492-sUJmk8MLO3ShdUet-3m-4A-1; Fri, 19 Feb 2021 12:38:52 -0500
X-MC-Unique: sUJmk8MLO3ShdUet-3m-4A-1
Received: by mail-wr1-f70.google.com with SMTP id f5so2782322wro.7
        for <kvm@vger.kernel.org>; Fri, 19 Feb 2021 09:38:52 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=lykBUd6DAhrahT8nCJAC5FU9Ql8oesKH07nupx8xYdk=;
        b=SKWgju7pWDq7PyHm15YbZoNM9V1B2seiwc37sLjd/A9yAur1sPjvyB9xgLKfA0ew8y
         hpku5uJAW4dwZvexqkO3qP/MVNY5ZgHkhFRKMTj2mQy3HSwgcfJAAgk1XgNh1mzwZvA+
         zS8JnW03cRSpeO1C2mz/qz8chxnuqqNKCxyQ53BgTZKyEGA/3VtUhka/ePkCTMWgJygz
         WVW/DTFYlVMDI834/+M+UvBjiIIknQj6PgaUrNAi4TxlAT7YhBxL5arbnYb+aHNpRbVx
         TBG7EaPJinODCiYTt1TyxJVz7HpcT4nKqpkN/V3szIc+9kWqQfN9IBrAYl6vXxv7eLNv
         Cd7Q==
X-Gm-Message-State: AOAM530mmL2QZHqNp0677mmScIP5jiqyCGsR6vU2HNf9oqr10f0mIPqa
        v3+XolozllfMgR/4YZZ9NyJVgfkoZd5uIzfABATWHeNlDboUdso1IZz+SCcZT5Q0AGBiieVcump
        X33k6oRrSxB4q
X-Received: by 2002:adf:e4c3:: with SMTP id v3mr10542040wrm.210.1613756331025;
        Fri, 19 Feb 2021 09:38:51 -0800 (PST)
X-Google-Smtp-Source: 
 ABdhPJwI/byrZ/GWSkkhxlUrl1Omb6LyZ4OFFS/CSa2qXI7tP50C7ZajzgipQ5EfU9sygOtDbt6r2g==
X-Received: by 2002:adf:e4c3:: with SMTP id v3mr10542005wrm.210.1613756330876;
        Fri, 19 Feb 2021 09:38:50 -0800 (PST)
Received: from localhost.localdomain (68.red-83-57-175.dynamicip.rima-tde.net.
 [83.57.175.68])
        by smtp.gmail.com with ESMTPSA id
 l2sm13785629wrm.6.2021.02.19.09.38.48
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 19 Feb 2021 09:38:50 -0800 (PST)
From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>
To: qemu-devel@nongnu.org
Cc: Aurelien Jarno <aurelien@aurel32.net>,
 Peter Maydell <peter.maydell@linaro.org>,
 Anthony Perard <anthony.perard@citrix.com>, qemu-ppc@nongnu.org,
 qemu-s390x@nongnu.org, Halil Pasic <pasic@linux.ibm.com>,
 Huacai Chen <chenhuacai@kernel.org>, xen-devel@lists.xenproject.org,
 Marcel Apfelbaum <marcel.apfelbaum@gmail.com>,
 David Gibson <david@gibson.dropbear.id.au>, qemu-arm@nongnu.org,
 Stefano Stabellini <sstabellini@kernel.org>,
 Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org,
 BALATON Zoltan <balaton@eik.bme.hu>, Leif Lindholm <leif@nuviainc.com>,
 Richard Henderson <richard.henderson@linaro.org>,
 Radoslaw Biernacki <rad@semihalf.com>,
 Alistair Francis <alistair@alistair23.me>, Paul Durrant <paul@xen.org>,
 Eduardo Habkost <ehabkost@redhat.com>, "Michael S. Tsirkin" <mst@redhat.com>,
 Thomas Huth <thuth@redhat.com>, Jiaxun Yang <jiaxun.yang@flygoat.com>,
	=?utf-8?q?Herv=C3=A9_Poussineau?= <hpoussin@reactos.org>,
 Greg Kurz <groug@kaod.org>, Christian Borntraeger <borntraeger@de.ibm.com>,
 Cornelia Huck <cohuck@redhat.com>,
 "Edgar E. Iglesias" <edgar.iglesias@gmail.com>,
 David Hildenbrand <david@redhat.com>,
 Mark Cave-Ayland <mark.cave-ayland@ilande.co.uk>,
 Aleksandar Rikalo <aleksandar.rikalo@syrmia.com>, =?utf-8?q?Philippe_Mathie?=
	=?utf-8?q?u-Daud=C3=A9?= <f4bug@amsat.org>, =?utf-8?q?Philippe_Mathieu-Daud?=
	=?utf-8?q?=C3=A9?= <philmd@redhat.com>
Subject: [PATCH v2 00/11] hw/accel: Exit gracefully when accelerator is
 invalid
Date: Fri, 19 Feb 2021 18:38:36 +0100
Message-Id: <20210219173847.2054123-1-philmd@redhat.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

This series aims to improve user experience by providing
a better error message when the user tries to enable KVM
on machines not supporting it.

Since v1:
- added missing x86 arch (Peter)
- consider all accelerators (Daniel and Peter)
- do not enable KVM on sbsa-ref (Leif)
- updated 'query-machines' (Daniel)
- new patch for XenPV

Supersedes: <20210219114428.1936109-1-philmd@redhat.com>

Philippe Mathieu-Daudé (11):
  accel/kvm: Check MachineClass kvm_type() return value
  hw/boards: Introduce machine_class_valid_for_accelerator()
  hw/core: Restrict 'query-machines' to those supported by current accel
  hw/arm: Restrit KVM to the virt & versal machines
  hw/mips: Restrict KVM to the malta & virt machines
  hw/ppc: Restrict KVM to various PPC machines
  hw/s390x: Explicit the s390-ccw-virtio machines support TCG and KVM
  hw/i386: Explicit x86 machines support all current accelerators
  hw/xenpv: Restrict Xen Para-virtualized machine to Xen accelerator
  hw/board: Only allow TCG accelerator by default
  softmmu/vl: Exit gracefully when accelerator is not supported

 include/hw/boards.h        | 27 ++++++++++++++++++++++++++-
 accel/kvm/kvm-all.c        |  6 ++++++
 hw/arm/virt.c              |  5 +++++
 hw/arm/xlnx-versal-virt.c  |  5 +++++
 hw/core/machine-qmp-cmds.c |  4 ++++
 hw/core/machine.c          | 26 ++++++++++++++++++++++++++
 hw/i386/x86.c              |  5 +++++
 hw/mips/loongson3_virt.c   |  5 +++++
 hw/mips/malta.c            |  5 +++++
 hw/ppc/e500plat.c          |  5 +++++
 hw/ppc/mac_newworld.c      |  6 ++++++
 hw/ppc/mac_oldworld.c      |  5 +++++
 hw/ppc/mpc8544ds.c         |  5 +++++
 hw/ppc/ppc440_bamboo.c     |  5 +++++
 hw/ppc/prep.c              |  5 +++++
 hw/ppc/sam460ex.c          |  5 +++++
 hw/ppc/spapr.c             |  5 +++++
 hw/s390x/s390-virtio-ccw.c |  5 +++++
 hw/xenpv/xen_machine_pv.c  |  5 +++++
 softmmu/vl.c               |  7 +++++++
 20 files changed, 145 insertions(+), 1 deletion(-)
```
