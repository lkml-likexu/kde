

#### [PATCH 00/12] hw/i386/pc: Move PC-machine specific declarations to
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>

```c
From patchwork Fri Dec 13 16:17:41 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
 <philmd@redhat.com>
X-Patchwork-Id: 11290825
Return-Path: <SRS0=Db9H=2D=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 965906C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 13 Dec 2019 20:37:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4AE7B24735
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 13 Dec 2019 20:37:52 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="W7FtgtZy"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728023AbfLMQST (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 13 Dec 2019 11:18:19 -0500
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:56002 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726404AbfLMQST (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 13 Dec 2019 11:18:19 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1576253898;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=eictPqqvfDWdLCnWulB6nvsiJMgILd7otDTiwQaZME4=;
        b=W7FtgtZy02cgeowTjxtRgkyZ4xFT2qSVGM77Q+xQmb5rJO9AOgBIT2ez5KWeNhvYZQ0aZq
        we01nH6WoRkLxRGiSg3khpteMc7lhCzlZolJJkWc1gcfDC76VlR8wDehbqlrGVloctr7pt
        KAUKgVhiPknzDQ6XqFhbXdrD55H72cs=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-82-termAq3FMgGFGnyF0OlLXA-1; Fri, 13 Dec 2019 11:18:14 -0500
X-MC-Unique: termAq3FMgGFGnyF0OlLXA-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 3E942800D41;
        Fri, 13 Dec 2019 16:18:12 +0000 (UTC)
Received: from x1w.redhat.com (ovpn-205-147.brq.redhat.com [10.40.205.147])
        by smtp.corp.redhat.com (Postfix) with ESMTPS id 5F91219C4F;
        Fri, 13 Dec 2019 16:17:57 +0000 (UTC)
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
Subject: [PATCH 00/12] hw/i386/pc: Move PC-machine specific declarations to
 'pc_internal.h'
Date: Fri, 13 Dec 2019 17:17:41 +0100
Message-Id: <20191213161753.8051-1-philmd@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Paolo,

Since you posted your "x86: allow building without PC machine
types" series [1], I looked at my past work on this topic
(restrict "hw/i386/pc.h" to the X86 architecture).
I'm glad to see in [2] you remove most (all) of the last uses.
Since I haven't looked at this for some time, my WiP branch was
quite diverged from QEMU master. I guess I could salvage most of
the easy patches. The rest is QOMification of GSI/IOAPIC which
require various changes with the i8259, so I'll keep that for
later.

[1] https://www.mail-archive.com/qemu-devel@nongnu.org/msg664760.html
[2] https://www.mail-archive.com/qemu-devel@nongnu.org/msg664765.html

Philippe Mathieu-Daudé (12):
  hw/i386/pc: Convert DPRINTF() to trace events
  hw/i386/pc: Move kvm_i8259_init() declaration to sysemu/kvm.h
  hw/i386/pc: Remove obsolete pc_pci_device_init() declaration
  hw/i386/pc: Remove obsolete cpu_set_smm_t typedef
  hw/i386/ich9: Remove unused include
  hw/i386/ich9: Move unnecessary "pci_bridge.h" include
  hw/ide/piix: Remove superfluous DEVICE() cast
  hw/ide/piix: Use ARRAY_SIZE() instead of magic numbers
  hw/intc/ioapic: Make ioapic_print_redtbl() static
  hw/i386/pc: Rename allocate_cpu_irq from 'pc' to 'x86_machine'
  hw/i386/pc: Move x86_machine_allocate_cpu_irq() to 'hw/i386/x86.c'
  hw/i386/pc: Move PC-machine specific declarations to 'pc_internal.h'

 hw/i386/pc_internal.h             | 144 ++++++++++++++++++++++++++++++
 include/hw/i386/ich9.h            |   2 -
 include/hw/i386/ioapic_internal.h |   1 -
 include/hw/i386/pc.h              | 133 ---------------------------
 include/hw/i386/x86.h             |   2 +
 include/sysemu/kvm.h              |   1 +
 hw/i386/acpi-build.c              |   2 +
 hw/i386/microvm.c                 |   2 +-
 hw/i386/pc.c                      |  47 ++--------
 hw/i386/pc_piix.c                 |   1 +
 hw/i386/pc_q35.c                  |   1 +
 hw/i386/pc_sysfw.c                |   1 +
 hw/i386/x86.c                     |  30 +++++++
 hw/i386/xen/xen-hvm.c             |   1 +
 hw/ide/piix.c                     |  29 +++---
 hw/intc/ioapic_common.c           |   2 +-
 hw/pci-bridge/i82801b11.c         |   1 +
 hw/i386/trace-events              |   6 ++
 18 files changed, 211 insertions(+), 195 deletions(-)
 create mode 100644 hw/i386/pc_internal.h
```
#### [PATCH 0/7] KVM: arm/arm64: Help VMs dying quicker
##### From: Marc Zyngier <maz@kernel.org>
X-SA-Exim-Mail-From: maz@kernel.org

```c
From patchwork Fri Dec 13 18:24:56 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11290941
Return-Path: <SRS0=Db9H=2D=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AC98E109A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 13 Dec 2019 20:38:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5EECC246D0
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 13 Dec 2019 20:38:25 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1576269505;
	bh=6dvjtHi2y01wFE5sRxcphtKCC9JrCAlvp9j31wPAeSU=;
	h=From:Cc:Subject:Date:To:List-ID:From;
	b=sWQekOfjg/2zJMAyIj7k4krqwfpxX5F3AFKhbCqEHl+Z8hRpxUNjmgzFp6krGPOyn
	 BlLyliXxJdd+PIJFVmTnpJ/a3/awUxgCYgHQMti65r2Kx6bXQnB0/y2a2n0nh42C5L
	 QMbBTDxxKgkUZT2Bc8GjAWgZReHYXJV3CUqQvwjY=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728762AbfLMS1w (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 13 Dec 2019 13:27:52 -0500
Received: from inca-roads.misterjones.org ([213.251.177.50]:34659 "EHLO
        inca-roads.misterjones.org" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726404AbfLMS1w (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 13 Dec 2019 13:27:52 -0500
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by cheepnis.misterjones.org with esmtpsa
 (TLSv1.2:DHE-RSA-AES128-GCM-SHA256:128)
        (Exim 4.80)
        (envelope-from <maz@kernel.org>)
        id 1ifpdD-0001O7-Ur; Fri, 13 Dec 2019 19:25:40 +0100
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
Subject: [PATCH 0/7] KVM: arm/arm64: Help VMs dying quicker
Date: Fri, 13 Dec 2019 18:24:56 +0000
Message-Id: <20191213182503.14460-1-maz@kernel.org>
X-Mailer: git-send-email 2.20.1
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

[Yes, the subject is deliberately provocative!]

Having recently played with large, memory intensive, and very short lived
VMs, I have realised that we spend a substantial amount of time cleaning up
when a VM has terminated.

It turns out that 99% of the overhead is due to the unnecessary cache
cleaning that we perform when pages get unmapped from Stage-2, which
only serves a single purpose: to make the page visible to a non-coherent
IO subsystem when the page is being swapped out.

It would make sense to drop these cache maintenance operations when
userspace is either unmapping a VMA or simply exiting. Detecting the
latter is easy, as KVM calls kvm_arch_flush_shadow_all(). The unmap
case is harder, or at least it was until 5.2 gained the MMU notifier
event, which allows subsystems to find out about the reason of an
change in the page tables.

And it turns out we can do even better: We can also avoid invalidating
individual page mappings if we're tearing down the VM altogether, and
replace it with a single TLBI VMALL, which will be much lighter on the
whole system (specially if your interconnect is a bit flimsy).

With the above, terminating a 64GB VM that has most of its memory
mapped at S2 goes from several seconds (I've seen up to 12s) to less
than a second on my D05. In general, multi-socket systems seem to
benefit from this more than single socket machines (based on a
non-representative sample of 4 random machines I have access to).

The first patch affects most architectures, as it changes one of the
core architecture hooks (in a fairly mechanical way). The rest is
definitely ARM-specific.

Marc Zyngier (7):
  KVM: Pass mmu_notifier_range down to kvm_unmap_hva_range()
  KVM: arm/arm64: Pass flags along Stage-2 unmapping functions
  KVM: arm/arm64: Condition cache maintenance on unmap with a flag
  KVM: arm/arm64: Condition TLB maintenance on unmap with a flag
  KVM: arm/arm64: Elide both CMOs and TBLIs on freeing the whole Stage-2
  KVM: arm/arm64: Elide CMOs when retrying a block mapping
  KVM: arm/arm64: Elide CMOs when unmapping a range

 arch/arm/include/asm/kvm_host.h     |  2 +-
 arch/arm64/include/asm/kvm_host.h   |  2 +-
 arch/mips/include/asm/kvm_host.h    |  2 +-
 arch/mips/kvm/mmu.c                 |  6 +-
 arch/powerpc/include/asm/kvm_host.h |  2 +-
 arch/powerpc/kvm/book3s.c           |  5 +-
 arch/powerpc/kvm/e500_mmu_host.c    |  4 +-
 arch/x86/include/asm/kvm_host.h     |  3 +-
 arch/x86/kvm/mmu/mmu.c              |  5 +-
 arch/x86/kvm/x86.c                  |  4 +-
 include/linux/kvm_host.h            |  2 +-
 virt/kvm/arm/mmu.c                  | 97 +++++++++++++++++++----------
 virt/kvm/kvm_main.c                 |  7 +--
 13 files changed, 88 insertions(+), 53 deletions(-)
```
#### [PATCH net 0/2] vsock/virtio: fix null-pointer dereference and
##### From: Stefano Garzarella <sgarzare@redhat.com>

```c
From patchwork Fri Dec 13 18:47:59 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stefano Garzarella <sgarzare@redhat.com>
X-Patchwork-Id: 11290997
Return-Path: <SRS0=Db9H=2D=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F11526C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 13 Dec 2019 20:38:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A59DF246C0
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 13 Dec 2019 20:38:34 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="ibaVLrgh"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728756AbfLMSsK (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 13 Dec 2019 13:48:10 -0500
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:28956 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1728576AbfLMSsK (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 13 Dec 2019 13:48:10 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1576262889;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=deTmsk0BQdQEPhCCzmHgYqMaF0cfRBrvO3lqwb43CWA=;
        b=ibaVLrghPB2eFq31ccfq0+S4rrTYuYsgvzdrl1waoUZfg5yquePzktywl4d7j1mQU/0utV
        ZUVF6QJXBWcqzaIsz6zTZ5kbD5EjaA0WGT/WrHAkpXcPL0OqqIztEEID+14mmBQQhX7JHV
        Tps23HvBwJOrP6JvOcgrExhEgBKUfhs=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-4-HA1EV8o7OLOXy-TFUmvD3g-1; Fri, 13 Dec 2019 13:48:08 -0500
X-MC-Unique: HA1EV8o7OLOXy-TFUmvD3g-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 36A0D911EA;
        Fri, 13 Dec 2019 18:48:07 +0000 (UTC)
Received: from steredhat.redhat.com (ovpn-117-123.ams2.redhat.com
 [10.36.117.123])
        by smtp.corp.redhat.com (Postfix) with ESMTP id F183B60BB3;
        Fri, 13 Dec 2019 18:48:02 +0000 (UTC)
From: Stefano Garzarella <sgarzare@redhat.com>
To: davem@davemloft.net
Cc: Stefano Garzarella <sgarzare@redhat.com>,
        linux-kernel@vger.kernel.org, netdev@vger.kernel.org,
        kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        Stefan Hajnoczi <stefanha@redhat.com>
Subject: [PATCH net 0/2] vsock/virtio: fix null-pointer dereference and
 related precautions
Date: Fri, 13 Dec 2019 19:47:59 +0100
Message-Id: <20191213184801.486675-1-sgarzare@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series mainly solves a possible null-pointer dereference in
virtio_transport_recv_listen() introduced with the multi-transport
support [PATCH 1].

PATCH 2 adds a WARN_ON check for the same potential issue
and a returned error in the virtio_transport_send_pkt_info() function
to avoid crashing the kernel.

Stefano Garzarella (2):
  vsock/virtio: fix null-pointer dereference in
    virtio_transport_recv_listen()
  vsock/virtio: add WARN_ON check on virtio_transport_get_ops()

 net/vmw_vsock/virtio_transport_common.c | 25 +++++++++++++++++++------
 1 file changed, 19 insertions(+), 6 deletions(-)
```
