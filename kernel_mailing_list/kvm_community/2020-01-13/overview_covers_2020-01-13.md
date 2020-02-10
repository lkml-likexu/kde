

#### [PATCH kvm-unit-tests 0/3] arm/arm64: selftest for pabt
##### From: Andrew Jones <drjones@redhat.com>

```c
From patchwork Mon Jan 13 13:00:40 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11330113
Return-Path: <SRS0=ekPD=3C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D842F930
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 13 Jan 2020 13:00:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B6A2B2081E
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 13 Jan 2020 13:00:50 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Z0iYB/jK"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727014AbgAMNAt (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 13 Jan 2020 08:00:49 -0500
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:39248 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726277AbgAMNAt (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 13 Jan 2020 08:00:49 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1578920448;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=EkS+XB1Ns/9Hyh+RmqcN6uCGCO0+4bXjZaEm/l9P19A=;
        b=Z0iYB/jKHh+aUGcvIRTjfwoAY1yFDF6tuD0V/72GkV5YCbbx3s6oxF0VuVhWsecF6NpXhT
        Jlpe3xOXJRy2Sn8KJcm+Q28LM+kwHYHD1zZMAgA3lwdBISxcB/vj9NgJeLTvKhSCwP5JOl
        K/T7UAfLtU3UkVUkVqKqbAtwzanHZwo=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-206-VZ-fsZIIMe-6upmb9trs7Q-1; Mon, 13 Jan 2020 08:00:46 -0500
X-MC-Unique: VZ-fsZIIMe-6upmb9trs7Q-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id BBE2918A6ED1;
        Mon, 13 Jan 2020 13:00:45 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.43.2.160])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 7BAA480F6C;
        Mon, 13 Jan 2020 13:00:44 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu
Cc: pbonzini@redhat.com, alexandru.elisei@arm.com
Subject: [PATCH kvm-unit-tests 0/3] arm/arm64: selftest for pabt
Date: Mon, 13 Jan 2020 14:00:40 +0100
Message-Id: <20200113130043.30851-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Patch 3/3 is a rework of Alexandru's pabt test on top of a couple of
framework changes allowing it to be more simply and robustly implemented.

Andrew Jones (3):
  arm/arm64: Improve memory region management
  arm/arm64: selftest: Allow test_exception clobber list to be extended
  arm/arm64: selftest: Add prefetch abort test

 arm/selftest.c      | 199 ++++++++++++++++++++++++++++++++------------
 lib/arm/asm/setup.h |   8 +-
 lib/arm/mmu.c       |  24 ++----
 lib/arm/setup.c     |  56 +++++++++----
 lib/arm64/asm/esr.h |   3 +
 5 files changed, 203 insertions(+), 87 deletions(-)
```
#### [PATCH 0/3] Handle monitor trap flag during instruction emulation
##### From: Oliver Upton <oupton@google.com>

```c
From patchwork Mon Jan 13 22:10:50 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Oliver Upton <oupton@google.com>
X-Patchwork-Id: 11331007
Return-Path: <SRS0=ekPD=3C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 58BFE138D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 13 Jan 2020 22:10:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 367032072B
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 13 Jan 2020 22:10:58 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="nMOkTXEu"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728819AbgAMWK5 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 13 Jan 2020 17:10:57 -0500
Received: from mail-pf1-f202.google.com ([209.85.210.202]:52786 "EHLO
        mail-pf1-f202.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727382AbgAMWK5 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 13 Jan 2020 17:10:57 -0500
Received: by mail-pf1-f202.google.com with SMTP id 145so7471900pfx.19
        for <kvm@vger.kernel.org>; Mon, 13 Jan 2020 14:10:56 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=tgXHdBhTxnbggm48PWjGbR468zkVyYGw0KccqoL7rpE=;
        b=nMOkTXEuejp7ltUHNH5PwzsoaA8hAe+3a/zcrS0wD8S2/J5Umx5O9KFmaYDfxeKiik
         Ux9uUEvVKwo29Kvaxp/OARzzgcyr9F3EBK2dLNuKxxifrtu17aKlMZcmYOU9QLwlPolH
         Bgr1dV2ZalUSIQ1DjUyQ1Q3uhc8/Fd1rxoNGwQm/QviERBptioRJtBbDT04+naXxgkJv
         ePXuR757YoKbkB4VG0B+H1Jol3Jy6MWGsr34Zr9e4lZwgAltPBgo3e114UEON9Guicj7
         t03g8Vs2Oz8k2AHzBnnG+QycgVG2S+OvvQi8X00fD/hX2f7dGNxos4EyzdQMFAFKj8z6
         bpFQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=tgXHdBhTxnbggm48PWjGbR468zkVyYGw0KccqoL7rpE=;
        b=KEWI1ZkUn1yiLSiGsuoTBx8L6dccXTmZLV4Ncv7e04gy5cur+CdEuYcvtjOMmif+Bk
         ufC/CogXcyPJSQ0b2Yve5U+rohwmyXqSLjOVT2eW44CH1KjgcNqr7v5U8P3PESWb9ZHL
         TjCQOQgymz2CcANZfpV/VS459phuDOMgfX5G7Q0JVZo5j9Oz2ws/Z6mnhp5R/nCObZq/
         UO9APYf896jzm2SKKBr8e0/omK8AOWXMy0/SMSQs+qAupE6KSto2mHfS468ooV7qXSp2
         aoFwr5psAzslus+uYjdFxkFtrA7VC6bLw4JLAoPjfQpPMFsgN8WM16AjG5OWbM2B8bW/
         R5qQ==
X-Gm-Message-State: APjAAAXehvBb3pXkEGWQyoVrc0tVikGjvRlPizclSSFO/8b4/cn5rQnk
        Z5BDn1Iq9II+RAyifzciwKhhKQMUw+bRQJpyoY/+aTyBdiSeo2p5D23zWi0qgFGo9EMelNvbgt8
        j2EXpNhNSDJbKTLGypkK2qTeuE1iIK4Eg2UBa+QHCQ2tkYdjuQjF2sHf/og==
X-Google-Smtp-Source: 
 APXvYqz09qNCQFN5bt1F8eq7/D6JLu/oaru0DGVcMGilzCKvI5HYi8omESd5WpXJNj/CErdAQJKLEGA61as=
X-Received: by 2002:a63:7944:: with SMTP id
 u65mr21442503pgc.298.1578953455971;
 Mon, 13 Jan 2020 14:10:55 -0800 (PST)
Date: Mon, 13 Jan 2020 14:10:50 -0800
Message-Id: <20200113221053.22053-1-oupton@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.25.0.rc1.283.g88dfdc4193-goog
Subject: [PATCH 0/3] Handle monitor trap flag during instruction emulation
From: Oliver Upton <oupton@google.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Oliver Upton <oupton@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

KVM already provides guests the ability to use the 'monitor trap flag'
VM-execution control. Support for this flag is provided by the fact that
KVM unconditionally forwards MTF VM-exits to the guest (if requested),
as KVM doesn't utilize MTF. While this provides support during hardware
instruction execution, it is insufficient for instruction emulation.

Should L0 emulate an instruction on the behalf of L2, L0 should also
synthesize an MTF VM-exit into L1, should control be set.

The first patch fixes the handling of #DB payloads for both Intel and
AMD. To support MTF, KVM must also populate the 'pending debug
exceptions' field, rather than directly manipulating the debug register
state. Additionally, the exception payload associated with #DB is said
to be compatible with the 'pending debug exceptions' field in VMX. This
does not map cleanly into an AMD DR6 register, requiring bit 12 (enabled
breakpoint on Intel, reserved MBZ on AMD) to be masked off.

The second patch implements MTF under instruction emulation by adding
vendor-specific hooks to kvm_skip_emulated_instruction(). Should any
non-debug exception be pending before this call, MTF will follow event
delivery. Otherwise, an MTF VM-exit may be synthesized directly into L1.

Third patch introduces tests to kvm-unit-tests. These tests path both
under virtualization and on bare-metal.

Oliver Upton (2):
  KVM: x86: Add vendor-specific #DB payload delivery
  KVM: x86: Emulate MTF when performing instruction emulation

 arch/x86/include/asm/kvm_host.h |  2 ++
 arch/x86/kvm/svm.c              | 25 +++++++++++++++++++++
 arch/x86/kvm/vmx/nested.c       |  2 +-
 arch/x86/kvm/vmx/nested.h       |  5 +++++
 arch/x86/kvm/vmx/vmx.c          | 39 ++++++++++++++++++++++++++++++++-
 arch/x86/kvm/x86.c              | 27 ++++++-----------------
 6 files changed, 78 insertions(+), 22 deletions(-)
```
