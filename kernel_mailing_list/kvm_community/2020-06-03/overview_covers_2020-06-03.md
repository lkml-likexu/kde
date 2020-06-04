

#### [PATCH v3 00/20] virtio-mem: Paravirtualized memory hot(un)plug
##### From: David Hildenbrand <david@redhat.com>

```c
From patchwork Wed Jun  3 14:48:54 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Hildenbrand <david@redhat.com>
X-Patchwork-Id: 11585765
Return-Path: <SRS0=c+SP=7Q=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8915392A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  3 Jun 2020 14:49:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6C39F207D8
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  3 Jun 2020 14:49:46 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="HcHUrex4"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726112AbgFCOto (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 3 Jun 2020 10:49:44 -0400
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:28063 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1725834AbgFCOtn (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 3 Jun 2020 10:49:43 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1591195781;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=zKFP0QF9he822WRSSHDvVJN3nyZoiZ5PaNm66UxKUK4=;
        b=HcHUrex4ime1hdo62//2wHvBW01VtyHtEdnVQIPK6/EDTcj5FZcPf5tq2DCXrUJKHE0DmG
        vpgqy3lxYweW16fOP2E8PcbjKZFs1uopj8b8CchS/sOeu/qWttRWagURvjqixk5rIb4OvE
        fvBb2pljtSYHVQJs+Vf1SQ++hWp45ec=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-420-RxClTtjJO8Cg9vN_LIHmcg-1; Wed, 03 Jun 2020 10:49:32 -0400
X-MC-Unique: RxClTtjJO8Cg9vN_LIHmcg-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 25AB71005510;
        Wed,  3 Jun 2020 14:49:30 +0000 (UTC)
Received: from t480s.redhat.com (ovpn-113-192.ams2.redhat.com [10.36.113.192])
        by smtp.corp.redhat.com (Postfix) with ESMTP id B81795D9CD;
        Wed,  3 Jun 2020 14:49:15 +0000 (UTC)
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
        Marcel Apfelbaum <marcel.apfelbaum@gmail.com>,
        Markus Armbruster <armbru@redhat.com>,
        Peter Maydell <peter.maydell@linaro.org>,
        Pierre Morel <pmorel@linux.ibm.com>,
        Tony Krowiak <akrowiak@linux.ibm.com>
Subject: [PATCH v3 00/20] virtio-mem: Paravirtualized memory hot(un)plug
Date: Wed,  3 Jun 2020 16:48:54 +0200
Message-Id: <20200603144914.41645-1-david@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is the very basic, initial version of virtio-mem. More info on
virtio-mem in general can be found in the Linux kernel driver v2 posting
[1] and in patch #10. The latest Linux driver v4 can be found at [2].

This series is based on [3]:
    "[PATCH v1] pc: Support coldplugging of virtio-pmem-pci devices on all
     buses"

The patches can be found at:
    https://github.com/davidhildenbrand/qemu.git virtio-mem-v3

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
along with support for x86-64.


Note: Since commit 7d2ef6dcc1cf ("hmp: Simplify qom-set"), the behavior of
qom-set changed and we can no longer pass proper sizes (e.g., 300M). The
description in patch #10 is outdated - but I hope that we'll bring back the
old behaviour, so I kept it for now :)

[1] https://lkml.kernel.org/r/20200311171422.10484-1-david@redhat.com
[2] https://lkml.kernel.org/r/20200507140139.17083-1-david@redhat.com
[3] https://lkml.kernel.org/r/20200525084511.51379-1-david@redhat.com

Cc: teawater <teawaterz@linux.alibaba.com>
Cc: Pankaj Gupta <pankaj.gupta.linux@gmail.com>

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

David Hildenbrand (20):
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

 MAINTAINERS                                 |   8 +
 accel/kvm/kvm-all.c                         |   4 +-
 balloon.c                                   |  17 -
 exec.c                                      |  52 ++
 hw/core/numa.c                              |   6 +
 hw/i386/Kconfig                             |   1 +
 hw/i386/pc.c                                |  49 +-
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
 hw/virtio/virtio-mem.c                      | 876 ++++++++++++++++++++
 include/exec/memory.h                       |  41 +
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
 36 files changed, 1721 insertions(+), 121 deletions(-)
 create mode 100644 hw/virtio/virtio-mem-pci.c
 create mode 100644 hw/virtio/virtio-mem-pci.h
 create mode 100644 hw/virtio/virtio-mem.c
 create mode 100644 include/hw/virtio/virtio-mem.h
 create mode 100644 include/standard-headers/linux/virtio_mem.h
```
