

#### [PATCH v5 00/21] virtio-mem: Paravirtualized memory hot(un)plug
##### From: David Hildenbrand <david@redhat.com>

```c
From patchwork Fri Jun 26 07:22:27 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Hildenbrand <david@redhat.com>
X-Patchwork-Id: 11626633
Return-Path: <SRS0=HaOM=AH=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BB5446C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 26 Jun 2020 07:23:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9BEC12080C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 26 Jun 2020 07:23:17 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="ZxCUnmJJ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726422AbgFZHXQ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 26 Jun 2020 03:23:16 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:30886 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1725855AbgFZHXQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 26 Jun 2020 03:23:16 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1593156194;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=qhGaneoHx5il05o01jW1hDOadm2bPogSKu/DKrsEmAc=;
        b=ZxCUnmJJXgQGtfivfxp8avEOxzRpa8gh7BXpiqPM7iImYajxXT6VDoZ+gmtQgNRtkZFGuz
        kkkYk7F8pNAuFnbcqnAjIeGzE2qSonfU1NvID5yBwR6pm0sFWVgRu4EzH/GEh9dG1XhHAX
        3+Py6FJrR0fCRyPViuvs4bn4dhPuP3Q=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-168-rL45roI1OLesF9PxZX_jrQ-1; Fri, 26 Jun 2020 03:23:11 -0400
X-MC-Unique: rL45roI1OLesF9PxZX_jrQ-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 81D1E1009441;
        Fri, 26 Jun 2020 07:23:08 +0000 (UTC)
Received: from t480s.redhat.com (ovpn-113-35.ams2.redhat.com [10.36.113.35])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 7C6C560C1D;
        Fri, 26 Jun 2020 07:22:49 +0000 (UTC)
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
        Tony Krowiak <akrowiak@linux.ibm.com>,
        Vivek Goyal <vgoyal@redhat.com>
Subject: [PATCH v5 00/21] virtio-mem: Paravirtualized memory hot(un)plug
Date: Fri, 26 Jun 2020 09:22:27 +0200
Message-Id: <20200626072248.78761-1-david@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is the very basic, initial version of virtio-mem. More info on
virtio-mem in general can be found in the Linux kernel driver v2 posting
[1] and in patch #10. The Linux driver is now upstream.

This series now contains a resend of [3]:
    "[PATCH v1] pc: Support coldplugging of virtio-pmem-pci devices on all
     buses"

The patches can be found at:
    https://github.com/davidhildenbrand/qemu.git virtio-mem-v5

"The basic idea of virtio-mem is to provide a flexible,
cross-architecture memory hot(un)plug solution that avoids many limitations
imposed by existing technologies, architectures, and interfaces."

There are a lot of addons in the works (esp. protection of unplugged
memory, better hugepage support (esp. when reading unplugged memory),
resizeable memory backends, support for more architectures, ...), this is
the very basic version to get the ball rolling.

The first patch is a resend. Patches #2-#9 make sure we don't have any
sudden surprises e.g., if somebody tries to pin all memory in RAM blocks,
resulting in a higher memory consumption than desired. The remaining
patches add basic virtio-mem along with support for x86-64. The last patch
indicates to the guest OS the maximum possible PFN using ACPI SRAT, such
that Linux can properly enable the swiotlb when booting only with DMA
memory.

[1] https://lkml.kernel.org/r/20200311171422.10484-1-david@redhat.com
[2] https://lkml.kernel.org/r/20200507140139.17083-1-david@redhat.com
[3] https://lkml.kernel.org/r/20200525084511.51379-1-david@redhat.com
[3] https://lkml.kernel.org/r/20200610075153.33892-1-david@redhat.com

Cc: teawater <teawaterz@linux.alibaba.com>
Cc: Pankaj Gupta <pankaj.gupta.linux@gmail.com>

v4 -> v5:
- Rebased, added acks/rb's
- "pc: Support coldplugging of virtio-pmem-pci devices on all buses"
-- Included it now, for simplicity
- "linux-headers: update to contain virtio-mem"
-- Dropped, because header changes are already upstream now
- "MAINTAINERS: Add myself as virtio-mem maintainer"
-- Reference status page

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
  pc: Support coldplugging of virtio-pmem-pci devices on all buses
  exec: Introduce ram_block_discard_(disable|require)()
  vfio: Convert to ram_block_discard_disable()
  accel/kvm: Convert to ram_block_discard_disable()
  s390x/pv: Convert to ram_block_discard_disable()
  virtio-balloon: Rip out qemu_balloon_inhibit()
  target/i386: sev: Use ram_block_discard_disable()
  migration/rdma: Use ram_block_discard_disable()
  migration/colo: Use ram_block_discard_disable()
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

 MAINTAINERS                    |   9 +
 accel/kvm/kvm-all.c            |   4 +-
 balloon.c                      |  17 -
 exec.c                         |  52 ++
 hw/arm/virt.c                  |   2 +
 hw/core/numa.c                 |  17 +-
 hw/i386/Kconfig                |   1 +
 hw/i386/microvm.c              |   1 +
 hw/i386/pc.c                   |  66 +--
 hw/i386/pc_piix.c              |   1 +
 hw/i386/pc_q35.c               |   1 +
 hw/s390x/s390-virtio-ccw.c     |  22 +-
 hw/vfio/ap.c                   |   8 +-
 hw/vfio/ccw.c                  |  11 +-
 hw/vfio/common.c               |  53 +-
 hw/vfio/pci.c                  |   6 +-
 hw/virtio/Kconfig              |  11 +
 hw/virtio/Makefile.objs        |   2 +
 hw/virtio/trace-events         |  10 +
 hw/virtio/virtio-balloon.c     |  10 +-
 hw/virtio/virtio-mem-pci.c     | 157 ++++++
 hw/virtio/virtio-mem-pci.h     |  34 ++
 hw/virtio/virtio-mem.c         | 873 +++++++++++++++++++++++++++++++++
 include/exec/memory.h          |  41 ++
 include/hw/boards.h            |   1 +
 include/hw/pci/pci.h           |   1 +
 include/hw/vfio/vfio-common.h  |   4 +-
 include/hw/virtio/virtio-mem.h |  86 ++++
 include/migration/colo.h       |   2 +-
 include/migration/misc.h       |   2 +
 include/sysemu/balloon.h       |   2 -
 migration/migration.c          |  15 +-
 migration/postcopy-ram.c       |  23 -
 migration/rdma.c               |  18 +-
 migration/savevm.c             |  11 +-
 monitor/hmp-cmds.c             |  16 +
 monitor/monitor.c              |   1 +
 qapi/misc.json                 |  64 ++-
 target/i386/sev.c              |   7 +
 39 files changed, 1529 insertions(+), 133 deletions(-)
 create mode 100644 hw/virtio/virtio-mem-pci.c
 create mode 100644 hw/virtio/virtio-mem-pci.h
 create mode 100644 hw/virtio/virtio-mem.c
 create mode 100644 include/hw/virtio/virtio-mem.h
```
#### [kvm-unit-tests PATCH 0/3] x86: realmode: fixes
##### From: Nadav Amit <namit@vmware.com>

```c
From patchwork Fri Jun 26 09:23:30 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Nadav Amit <namit@vmware.com>
X-Patchwork-Id: 11626905
Return-Path: <SRS0=HaOM=AH=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E4E78912
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 26 Jun 2020 09:26:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D760D21527
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 26 Jun 2020 09:26:04 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726561AbgFZJ0D (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 26 Jun 2020 05:26:03 -0400
Received: from ex13-edg-ou-002.vmware.com ([208.91.0.190]:59908 "EHLO
        EX13-EDG-OU-002.vmware.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726530AbgFZJ0C (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 26 Jun 2020 05:26:02 -0400
Received: from sc9-mailhost2.vmware.com (10.113.161.72) by
 EX13-EDG-OU-002.vmware.com (10.113.208.156) with Microsoft SMTP Server id
 15.0.1156.6; Fri, 26 Jun 2020 02:25:55 -0700
Received: from sc2-haas01-esx0118.eng.vmware.com
 (sc2-haas01-esx0118.eng.vmware.com [10.172.44.118])
        by sc9-mailhost2.vmware.com (Postfix) with ESMTP id E1F92B2723;
        Fri, 26 Jun 2020 05:25:59 -0400 (EDT)
From: Nadav Amit <namit@vmware.com>
To: Paolo Bonzini <pbonzini@redhat.com>
CC: <kvm@vger.kernel.org>, Nadav Amit <namit@vmware.com>
Subject: [kvm-unit-tests PATCH 0/3] x86: realmode: fixes
Date: Fri, 26 Jun 2020 02:23:30 -0700
Message-ID: <20200626092333.2830-1-namit@vmware.com>
X-Mailer: git-send-email 2.17.1
MIME-Version: 1.0
Received-SPF: None (EX13-EDG-OU-002.vmware.com: namit@vmware.com does not
 designate permitted sender hosts)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Some fixes for realmode tests.

Nadav Amit (3):
  x86: realmode: initialize idtr
  x86: realmode: hlt loop as fallback on exit
  x86: realmode: fix lss test

 x86/realmode.c | 10 ++++++++--
 1 file changed, 8 insertions(+), 2 deletions(-)
```
