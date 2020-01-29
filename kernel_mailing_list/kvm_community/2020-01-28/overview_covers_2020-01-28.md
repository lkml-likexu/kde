

#### [PATCH v2 0/5] Handle monitor trap flag during instruction emulation
##### From: Oliver Upton <oupton@google.com>

```c
From patchwork Tue Jan 28 09:27:10 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Oliver Upton <oupton@google.com>
X-Patchwork-Id: 11353859
Return-Path: <SRS0=gQxY=3R=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3C5FD138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Jan 2020 09:27:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1A33F24686
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Jan 2020 09:27:30 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="JDNWLBhB"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725919AbgA1J13 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 28 Jan 2020 04:27:29 -0500
Received: from mail-yb1-f202.google.com ([209.85.219.202]:43644 "EHLO
        mail-yb1-f202.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725271AbgA1J12 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 28 Jan 2020 04:27:28 -0500
Received: by mail-yb1-f202.google.com with SMTP id g11so9672739ybc.10
        for <kvm@vger.kernel.org>; Tue, 28 Jan 2020 01:27:28 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=1D2HqKC9xNZbgrwgnAL8n/SPKL7jL4ZkZkoq8tmp9b8=;
        b=JDNWLBhBFWoJl6jiprEuB62OWWTC69IaEjDtsRF8/NeuXZ/Dxss6EZoBeC+L+C9U+x
         lMczqXsg7XLlbPdDCme2pDMFv1UcsJiZ92eW4tJa/hdpX1PPTNzYb97GJBgelqVvv2f3
         BN5uxg+st9AQplCR3XccdgVx7ZW0ysjAk5fFE1JWwNzOcwF3a3OtIW23enJckYoqrbo8
         81/PfFHh0mM6+wTbXyCRnvE9jK5Ds0OYTm/XeK3Pdn+grDR7RXOlEzLwqD02ByER2jWV
         JqGZp1GwBueV51DUjB3NAK2d2xUfaUcFSxAZNedRWWn5RSBRzkT+pSbUWlNCy/LmF6s5
         HbsQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=1D2HqKC9xNZbgrwgnAL8n/SPKL7jL4ZkZkoq8tmp9b8=;
        b=W56dUtJ62FA/PYv0fqwcZe/1tkfTSKULFxTCJqrGKGBchvIWRzMJefL8ItkqjXQm8E
         GWy2Raa0SSK7b95S6iLzZbFkiq+TPSzYjZpH259IqCn9FqjQ3M28bOJR/Go6KOOuYZba
         CVva0bFrdgtgsHEB08nGEPOdSdSbDdWQfDj4rsrFudmuKQWggAkHnDg5lAXg1tx0Rp7i
         7P3YrA3MCMzbC74bBiLm5zQ9ieKdXE5YhiTdxd882rjg981XxjpzqlDw1rvMGN5OhcNl
         rg4e7f8YVCrvnlUTpqL0+ZkqLC1ZOC7c8HqDYjD53S0CKZqJfBNU+yKFuYUrP/nat6xR
         TtMQ==
X-Gm-Message-State: APjAAAVbRTpBrkPchUaXisDPkUZdCOx/132HyvBQ/K4YndLGINGp4NXO
        Rsad73ZZQZyWyu/hydJOo1jis4Dl9e/D2r3+9jASOZeG/96hjHBBak/XCEApaUSkWX3ydi29PL6
        29epXePZ4tcLTwHB/iwOZlbQbSBOeeysz0ZODKDM4TBzOtmbof62N1Cgs4g==
X-Google-Smtp-Source: 
 APXvYqwRqeqGcIzZ8xLebgJnllx3kBwi/LiQU8PzrVDYXD1fiD8XhLCPgXdFIcmN3K+Y75RUgYm5+YDOFn8=
X-Received: by 2002:a81:6d17:: with SMTP id i23mr16153448ywc.58.1580203647427;
 Tue, 28 Jan 2020 01:27:27 -0800 (PST)
Date: Tue, 28 Jan 2020 01:27:10 -0800
Message-Id: <20200128092715.69429-1-oupton@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.25.0.341.g760bfbb309-goog
Subject: [PATCH v2 0/5] Handle monitor trap flag during instruction emulation
From: Oliver Upton <oupton@google.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Peter Shier <pshier@google.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Oliver Upton <oupton@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

v1: http://lore.kernel.org/r/20200113221053.22053-1-oupton@google.com

v1 => v2:
 - Don't split the #DB delivery by vendors. Unconditionally injecting
   #DB payloads into the 'pending debug exceptions' field will cause KVM
   to get stuck in a loop. Per the SDM, when hardware injects an event
   resulting from this field's value, it is checked against the
   exception interception bitmap.
 - Address Sean's comments by injecting the VM-exit into L1 from
   vmx_check_nested_events().
 - Added fix for nested INIT VM-exits + 'pending debug exceptions' field
   as it was noticed in implementing v2.
 - Drop Peter + Jim's Reviewed-by tags, as the patch set has changed
   since v1.

KVM already provides guests the ability to use the 'monitor trap flag'
VM-execution control. Support for this flag is provided by the fact that
KVM unconditionally forwards MTF VM-exits to the guest (if requested),
as KVM doesn't utilize MTF. While this provides support during hardware
instruction execution, it is insufficient for instruction emulation.

Should L0 emulate an instruction on the behalf of L2, L0 should also
synthesize an MTF VM-exit into L1, should control be set.

The first patch corrects a nuanced difference between the definition of
a #DB exception payload field and DR6 register. Mask off bit 12 which is
defined in the 'pending debug exceptions' field when applying to DR6,
since the payload field is said to be compatible with the aforementioned
VMCS field.

The second patch sets the 'pending debug exceptions' VMCS field when
delivering an INIT signal VM-exit to L1, as described in the SDM. This
patch also introduces helpers for setting the 'pending debug exceptions'
VMCS field.

The third patch massages KVM's handling of exception payloads with
regard to API compatibility. Rather than immediately injecting the
payload w/o opt-in, instead defer the payload + immediately inject
before completing a KVM_GET_VCPU_EVENTS. This maintains API
compatibility whilst correcting #DB behavior with regard to higher
priority VM-exit events.

Fourth patch introduces MTF implementation for emulated instructions.
Identify if an MTF is due on an instruction boundary from
kvm_vcpu_do_singlestep(), however only deliver this VM-exit from
vmx_check_nested_events() to respect the relative prioritization to
other VM-exits. Since this augments the nested state, introduce a new
flag for (de)serialization.

Last patch adds tests to kvm-unit-tests to assert the correctness of MTF
under several conditions (concurrent #DB trap, #DB fault, etc). These
tests pass under virtualization with this series as well as on
bare-metal.

Oliver Upton (4):
  KVM: x86: Mask off reserved bit from #DB exception payload
  KVM: nVMX: Handle pending #DB when injecting INIT VM-exit
  KVM: x86: Deliver exception payload on KVM_GET_VCPU_EVENTS
  KVM: nVMX: Emulate MTF when performing instruction emulation

 arch/x86/include/asm/kvm_host.h |  1 +
 arch/x86/include/uapi/asm/kvm.h |  1 +
 arch/x86/kvm/svm.c              |  1 +
 arch/x86/kvm/vmx/nested.c       | 60 ++++++++++++++++++++++++++++++++-
 arch/x86/kvm/vmx/nested.h       |  5 +++
 arch/x86/kvm/vmx/vmx.c          | 22 ++++++++++++
 arch/x86/kvm/vmx/vmx.h          |  3 ++
 arch/x86/kvm/x86.c              | 52 +++++++++++++++++-----------
 8 files changed, 125 insertions(+), 20 deletions(-)
```
#### [kvm-unit-tests PATCH v3 00/14] arm/arm64: Add ITS tests
##### From: Eric Auger <eric.auger@redhat.com>

```c
From patchwork Tue Jan 28 10:34:45 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Auger Eric <eric.auger@redhat.com>
X-Patchwork-Id: 11353999
Return-Path: <SRS0=gQxY=3R=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AC00D92A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Jan 2020 10:35:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 890B224688
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Jan 2020 10:35:23 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="HQ8JFqMV"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725997AbgA1KfW (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 28 Jan 2020 05:35:22 -0500
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:32232 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1725948AbgA1KfW (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 28 Jan 2020 05:35:22 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1580207720;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=fkt49j2omiFhxKeCwkMFncGz7jKFhFRQ1Z0P3fqpgS4=;
        b=HQ8JFqMVz/ns9fq4gWHhXcFohEr8xe/M7Oc0Cvrk/AsEjkztK0r7RBoKi28blx7v2MVIPx
        5LDLYIqWe6DEqz1E0oM0yj97VtAPietFzGtQTJwL47GXFG/wVjMWGTpavgQt16+/sF0K9C
        IFfPap4htUFlWAuCEFcvKqk2RuKiv2E=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-171-iOkdwkQ5PaOa_EbpL-qEKQ-1; Tue, 28 Jan 2020 05:35:12 -0500
X-MC-Unique: iOkdwkQ5PaOa_EbpL-qEKQ-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 357E618C43C0;
        Tue, 28 Jan 2020 10:35:10 +0000 (UTC)
Received: from laptop.redhat.com (ovpn-116-37.ams2.redhat.com [10.36.116.37])
        by smtp.corp.redhat.com (Postfix) with ESMTP id AD6381001B08;
        Tue, 28 Jan 2020 10:35:01 +0000 (UTC)
From: Eric Auger <eric.auger@redhat.com>
To: eric.auger.pro@gmail.com, eric.auger@redhat.com, maz@kernel.org,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        qemu-devel@nongnu.org, qemu-arm@nongnu.org
Cc: drjones@redhat.com, andre.przywara@arm.com,
        peter.maydell@linaro.org, yuzenghui@huawei.com,
        alexandru.elisei@arm.com, thuth@redhat.com
Subject: [kvm-unit-tests PATCH v3 00/14] arm/arm64: Add ITS tests
Date: Tue, 28 Jan 2020 11:34:45 +0100
Message-Id: <20200128103459.19413-1-eric.auger@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series is a revival of an RFC series sent in Dec 2016 [1].
Given the amount of code and the lack of traction at that time,
I haven't respinned until now. However a recent bug found related
to the ITS migration convinced me that this work may deserve to be
respinned and enhanced.

Tests exercise main ITS commands and also test migration.
With the migration framework, we are able to trigger the
migration from guest and that is very practical actually.

What is particular with the ITS programming is that most of
the commands are passed through queues and there is real error
handling. Invalid commands are just ignored and that is not
really tester friendly.

This series includes Andre's patch: "arm: gic: Provide
per-IRQ helper functions" [2]

test_migrate_unmapped_collection is currently failing with
upstream kernel. See [3].

The series can be fount at:
https://github.com/eauger/kut/tree/its-v3

Best Regards

Eric

History:
v2 -> v3:
- fix 32b compilation
- take into account Drew's comments (see individual diff logs)

v1 -> v2:
- took into account Zenghui's comments
- collect R-b's from Thomas

References:
[1] [kvm-unit-tests RFC 00/15] arm/arm64: add ITS framework
    https://lists.gnu.org/archive/html/qemu-devel/2016-12/msg00575.html

[2] [kvm-unit-tests PATCH 00/17] arm: gic: Test SPIs and interrupt groups
    https://patchwork.kernel.org/cover/11234975/

[3] [PATCH] KVM: arm/arm64: vgic-its: Fix restoration of unmapped
    collections (https://lkml.org/lkml/2019/12/13/205)

Execution:
x For ITS migration testing use:
  ./run_tests.sh -g migration (block on TCG)

x For other ITS tests:
  ./run_tests.sh -g its

x non migration tests can be launched invidually. For instance:
  ./arm-run arm/gic.flat -smp 8 -append 'its-trigger'


Andre Przywara (1):
  arm: gic: Provide per-IRQ helper functions

Eric Auger (13):
  libcflat: Add other size defines
  arm/arm64: gic: Introduce setup_irq() helper
  arm/arm64: gicv3: Add some re-distributor defines
  arm/arm64: ITS: Introspection tests
  arm/arm64: gicv3: Set the LPI config and pending tables
  arm/arm64: gicv3: Enable/Disable LPIs at re-distributor level
  arm/arm64: ITS: its_enable_defaults
  arm/arm64: ITS: Device and collection Initialization
  arm/arm64: ITS: commands
  arm/arm64: ITS: INT functional tests
  arm/run: Allow Migration tests
  arm/arm64: ITS: migration tests
  arm/arm64: ITS: pending table migration test

 arm/Makefile.arm64         |   1 +
 arm/Makefile.common        |   2 +-
 arm/gic.c                  | 488 +++++++++++++++++++++++++++++++++++--
 arm/run                    |   2 +-
 arm/unittests.cfg          |  38 +++
 lib/arm/asm/gic-v3-its.h   | 167 +++++++++++++
 lib/arm/asm/gic-v3.h       |  25 ++
 lib/arm/asm/gic.h          |   8 +
 lib/arm/gic-v3-its-cmd.c   | 454 ++++++++++++++++++++++++++++++++++
 lib/arm/gic-v3-its.c       | 243 ++++++++++++++++++
 lib/arm/gic-v3.c           |  81 ++++++
 lib/arm/gic.c              | 120 ++++++++-
 lib/arm/io.c               |  28 +++
 lib/arm64/asm/gic-v3-its.h |   1 +
 lib/libcflat.h             |   3 +
 15 files changed, 1633 insertions(+), 28 deletions(-)
 create mode 100644 lib/arm/asm/gic-v3-its.h
 create mode 100644 lib/arm/gic-v3-its-cmd.c
 create mode 100644 lib/arm/gic-v3-its.c
 create mode 100644 lib/arm64/asm/gic-v3-its.h
```
#### [PATCH 00/27] docs: virt: convert text documents to ReST format
##### From: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>

```c
From patchwork Tue Jan 28 14:00:01 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
X-Patchwork-Id: 11354337
Return-Path: <SRS0=gQxY=3R=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2686992A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Jan 2020 14:01:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 067362468A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Jan 2020 14:01:00 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1580220060;
	bh=Mv8f/pliX+ocV47UnDmPvVenRZUxEIIXDtdMqeYs8qA=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=vytwB+naDe9IkGfetVDkic4FixLCZVYQ3h+ZZCq/rM+k5TjyirmwBWjHu5YWGXEQm
	 dQMPMTgrsDGhhkboZ4JJB6CYtcnhIlatmJJUwvsaBEr1vmkItOj65qAtlfOvAK2cGd
	 HI+VGGkd3aBmvyf+XNNhRWfh19xdWohTDGaElFSU=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727321AbgA1OAs (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 28 Jan 2020 09:00:48 -0500
Received: from bombadil.infradead.org ([198.137.202.133]:59316 "EHLO
        bombadil.infradead.org" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727298AbgA1OAq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 28 Jan 2020 09:00:46 -0500
DKIM-Signature: v=1; a=rsa-sha256; q=dns/txt; c=relaxed/relaxed;
        d=infradead.org; s=bombadil.20170209;
 h=Sender:Content-Transfer-Encoding:
        MIME-Version:Message-Id:Date:Subject:Cc:To:From:Reply-To:Content-Type:
        Content-ID:Content-Description:Resent-Date:Resent-From:Resent-Sender:
        Resent-To:Resent-Cc:Resent-Message-ID:In-Reply-To:References:List-Id:
        List-Help:List-Unsubscribe:List-Subscribe:List-Post:List-Owner:List-Archive;
         bh=DXSED2YLe82h5LjexvdXkjf3Ix9TaTo2l6rYLelz1VU=;
 b=kB9R/0m6RyesZFlW3txEtEd1A
        olQ2YuBFW2vHq3owokfOnlDabx+GnkIsCH6lhxAL3Pwl5HKvRNZlEq2FWEKIq44o7uJO3+YFp7TK8
        3xIxWcqxJz2IBeqs5C13Y/h715HeTOuJpXU3JDe7Xgb5r6WGMgdC7oVTCeam7LW8jWxsgvYBMGBVX
        tFBoIefn0BUhKdMT1QDKm+0CM6Qk+OcsL0gnbM56YnRo2ZnQicscNgcDiDDJTBIJkqXFbxCEDplQO
        YZbC0C7JpXcACqrITWycMHZIH1HjQmKmAd7IcmT7LGTj0VIzX+Vyi03n8AOjnflysoG8WxNeZmt/U
        U4byvpgWA==;
Received: from [177.41.103.99] (helo=bombadil.infradead.org)
        by bombadil.infradead.org with esmtpsa (Exim 4.92.3 #3 (Red Hat
 Linux))
        id 1iwRQ5-0007ia-UW; Tue, 28 Jan 2020 14:00:45 +0000
Received: from mchehab by bombadil.infradead.org with local (Exim 4.92.3)
        (envelope-from <mchehab@bombadil.infradead.org>)
        id 1iwRPp-001BND-5V; Tue, 28 Jan 2020 15:00:29 +0100
From: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
To: Linux Media Mailing List <linux-media@vger.kernel.org>
Cc: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>,
        Mauro Carvalho Chehab <mchehab@infradead.org>,
        linux-um@lists.infradead.org, linux-doc@vger.kernel.org,
        Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org,
        Jeff Dike <jdike@addtoit.com>,
        Richard Weinberger <richard@nod.at>,
        Anton Ivanov <anton.ivanov@cambridgegreys.com>,
        Jonathan Corbet <corbet@lwn.net>
Subject: [PATCH 00/27] docs: virt: convert text documents to ReST format
Date: Tue, 28 Jan 2020 15:00:01 +0100
Message-Id: <cover.1580219586.git.mchehab+huawei@kernel.org>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Manually convert the documentation under Documentation/virt to ReST,
minimizing the usage of uneeded markups and preserving the documentation
writer's style.

PS.: Patches are against docs-next tree.

Mauro Carvalho Chehab (27):
  docs: kvm: add arm/pvtime.rst to index.rst
  docs: virt: convert UML documentation to ReST
  docs: virt: user_mode_linux.rst: update compiling instructions
  docs: virt: user_mode_linux.rst: fix URL references
  docs: virt: convert halt-polling.txt to ReST format
  docs: virt: Convert msr.txt to ReST format
  docs: kvm: devices/arm-vgic-its.txt to ReST format
  docs: kvm: devices/arm-vgit-v3.txt to ReST
  docs: kvm: convert devices/arm-vgit.txt to ReST
  docs: kvm: convert devices/mpic.txt to ReST
  docs: kvm: convert devices/s390_flic.txt to ReST
  docs: kvm: convert devices/vcpu.txt to ReST
  docs: kvm: convert devices/vcpu.txt to ReST
  docs: kvm: convert devices/vm.txt to ReST
  docs: kvm: convert devices/xics.txt to ReST
  docs: kvm: convert devices/xive.txt to ReST
  docs: kvm: Convert api.txt to ReST format
  docs: kvm: convert arm/hyp-abi.txt to ReST
  docs: kvm: arm/psci.txt: convert to ReST
  docs: kvm: Convert hypercalls.txt to ReST format
  docs: kvm: Convert locking.txt to ReST format
  docs: kvm: Convert mmu.txt to ReST format
  docs: kvm: Convert nested-vmx.txt to ReST format
  docs: kvm: Convert ppc-pv.txt to ReST format
  docs: kvm: Convert s390-diag.txt to ReST format
  docs: kvm: Convert timekeeping.txt to ReST format
  docs: kvm: review-checklist.txt: rename to ReST

 Documentation/virt/index.rst                  |    1 +
 Documentation/virt/kvm/{api.txt => api.rst}   | 3343 ++++++++++-------
 .../virt/kvm/arm/{hyp-abi.txt => hyp-abi.rst} |   26 +-
 Documentation/virt/kvm/arm/index.rst          |   12 +
 .../virt/kvm/arm/{psci.txt => psci.rst}       |   44 +-
 .../{arm-vgic-its.txt => arm-vgic-its.rst}    |  104 +-
 .../{arm-vgic-v3.txt => arm-vgic-v3.rst}      |  130 +-
 .../devices/{arm-vgic.txt => arm-vgic.rst}    |   87 +-
 Documentation/virt/kvm/devices/index.rst      |   19 +
 .../virt/kvm/devices/{mpic.txt => mpic.rst}   |    9 +-
 .../devices/{s390_flic.txt => s390_flic.rst}  |   68 +-
 Documentation/virt/kvm/devices/vcpu.rst       |  112 +
 Documentation/virt/kvm/devices/vcpu.txt       |   76 -
 .../virt/kvm/devices/{vfio.txt => vfio.rst}   |   23 +-
 .../virt/kvm/devices/{vm.txt => vm.rst}       |  204 +-
 .../virt/kvm/devices/{xics.txt => xics.rst}   |   26 +-
 .../virt/kvm/devices/{xive.txt => xive.rst}   |  146 +-
 .../{halt-polling.txt => halt-polling.rst}    |   84 +-
 .../kvm/{hypercalls.txt => hypercalls.rst}    |  127 +-
 Documentation/virt/kvm/index.rst              |   16 +
 .../virt/kvm/{locking.txt => locking.rst}     |  109 +-
 Documentation/virt/kvm/{mmu.txt => mmu.rst}   |   60 +-
 Documentation/virt/kvm/{msr.txt => msr.rst}   |  145 +-
 .../kvm/{nested-vmx.txt => nested-vmx.rst}    |   35 +-
 .../virt/kvm/{ppc-pv.txt => ppc-pv.rst}       |   24 +-
 ...iew-checklist.txt => review-checklist.rst} |    1 +
 .../virt/kvm/{s390-diag.txt => s390-diag.rst} |   11 +-
 .../kvm/{timekeeping.txt => timekeeping.rst}  |  221 +-
 ...odeLinux-HOWTO.txt => user_mode_linux.rst} | 1812 ++++-----
 29 files changed, 3954 insertions(+), 3121 deletions(-)
 rename Documentation/virt/kvm/{api.txt => api.rst} (71%)
 rename Documentation/virt/kvm/arm/{hyp-abi.txt => hyp-abi.rst} (80%)
 create mode 100644 Documentation/virt/kvm/arm/index.rst
 rename Documentation/virt/kvm/arm/{psci.txt => psci.rst} (61%)
 rename Documentation/virt/kvm/devices/{arm-vgic-its.txt => arm-vgic-its.rst} (71%)
 rename Documentation/virt/kvm/devices/{arm-vgic-v3.txt => arm-vgic-v3.rst} (77%)
 rename Documentation/virt/kvm/devices/{arm-vgic.txt => arm-vgic.rst} (66%)
 create mode 100644 Documentation/virt/kvm/devices/index.rst
 rename Documentation/virt/kvm/devices/{mpic.txt => mpic.rst} (92%)
 rename Documentation/virt/kvm/devices/{s390_flic.txt => s390_flic.rst} (88%)
 create mode 100644 Documentation/virt/kvm/devices/vcpu.rst
 delete mode 100644 Documentation/virt/kvm/devices/vcpu.txt
 rename Documentation/virt/kvm/devices/{vfio.txt => vfio.rst} (74%)
 rename Documentation/virt/kvm/devices/{vm.txt => vm.rst} (61%)
 rename Documentation/virt/kvm/devices/{xics.txt => xics.rst} (85%)
 rename Documentation/virt/kvm/devices/{xive.txt => xive.rst} (63%)
 rename Documentation/virt/kvm/{halt-polling.txt => halt-polling.rst} (64%)
 rename Documentation/virt/kvm/{hypercalls.txt => hypercalls.rst} (55%)
 rename Documentation/virt/kvm/{locking.txt => locking.rst} (79%)
 rename Documentation/virt/kvm/{mmu.txt => mmu.rst} (94%)
 rename Documentation/virt/kvm/{msr.txt => msr.rst} (75%)
 rename Documentation/virt/kvm/{nested-vmx.txt => nested-vmx.rst} (90%)
 rename Documentation/virt/kvm/{ppc-pv.txt => ppc-pv.rst} (91%)
 rename Documentation/virt/kvm/{review-checklist.txt => review-checklist.rst} (97%)
 rename Documentation/virt/kvm/{s390-diag.txt => s390-diag.rst} (91%)
 rename Documentation/virt/kvm/{timekeeping.txt => timekeeping.rst} (85%)
 rename Documentation/virt/uml/{UserModeLinux-HOWTO.txt => user_mode_linux.rst} (74%)
```
