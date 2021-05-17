

#### [PATCH v3 00/16] Replace some bad characters on documents
##### From: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>

```c
From patchwork Sun May 16 10:18:17 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
X-Patchwork-Id: 12260215
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-14.3 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id EF3DCC43462
	for <kvm@archiver.kernel.org>; Sun, 16 May 2021 10:18:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D7695611AD
	for <kvm@archiver.kernel.org>; Sun, 16 May 2021 10:18:58 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S235113AbhEPKUH (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sun, 16 May 2021 06:20:07 -0400
Received: from mail.kernel.org ([198.145.29.99]:37682 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S231386AbhEPKTx (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 16 May 2021 06:19:53 -0400
Received: by mail.kernel.org (Postfix) with ESMTPSA id 768AD611CA;
        Sun, 16 May 2021 10:18:37 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=k20201202; t=1621160317;
        bh=uz12JEUkFl1zk0MKhwqoy7Swq0yIqwlg559U5vqLb64=;
        h=From:To:Cc:Subject:Date:From;
        b=NZoYuL4T8pZP0XVsuqpo1xaXga3djUflecwXx5LGut8qbhlW3Y9NzBmiQJpti66iQ
         XEctA9a/tkYn6eIfMFOD23iU2NVyAWENwzAu5GTKImts+lpuYv0eNqgw/CUZ2ZkWss
         fllyfJ2EOkHcmxftZ1iXvAx83SROwJwSmenZXooYhJTuiuJxIyQ+zDnL2KcckWJO3l
         HXjHP9OcKsGcnNSkEPNKSqumMlW9xOUSyWQbW7rfHCgaVLEVCKAvIaHdwvFlEJ1a7n
         T0Jc41mYwmUESpLNWcMxWdQoD+Yw7News+EAAT/i+fb8vmW0PjoNLGp13h2ptdOtyU
         rkJ7P+/53g9gg==
Received: by mail.kernel.org with local (Exim 4.94.2)
        (envelope-from <mchehab@kernel.org>)
        id 1liDr1-003o89-5Z; Sun, 16 May 2021 12:18:35 +0200
From: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
To: Linux Doc Mailing List <linux-doc@vger.kernel.org>
Cc: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>,
        linux-kernel@vger.kernel.org, Jonathan Corbet <corbet@lwn.net>,
        "David S. Miller" <davem@davemloft.net>,
        "Theodore Ts'o" <tytso@mit.edu>,
        Alan Stern <stern@rowland.harvard.edu>,
        Andreas Dilger <adilger.kernel@dilger.ca>,
        Corentin Labbe <clabbe@baylibre.com>,
        Guenter Roeck <linux@roeck-us.net>,
        Jakub Kicinski <kuba@kernel.org>,
        Jaroslav Kysela <perex@perex.cz>,
        Jean Delvare <jdelvare@suse.com>,
        Joel Fernandes <joel@joelfernandes.org>,
        Lai Jiangshan <jiangshanlai@gmail.com>,
        Leo Yan <leo.yan@linaro.org>,
        Mathieu Desnoyers <mathieu.desnoyers@efficios.com>,
        Mathieu Poirier <mathieu.poirier@linaro.org>,
        Mauro Carvalho Chehab <mchehab@kernel.org>,
        Mike Leach <mike.leach@linaro.org>,
        Steven Rostedt <rostedt@goodmis.org>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Thorsten Leemhuis <linux@leemhuis.info>,
        alsa-devel@alsa-project.org, coresight@lists.linaro.org,
        intel-wired-lan@lists.osuosl.org, kvm@vger.kernel.org,
        linux-acpi@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
        linux-ext4@vger.kernel.org, linux-hwmon@vger.kernel.org,
        linux-media@vger.kernel.org, linux-pci@vger.kernel.org,
        linux-usb@vger.kernel.org, mjpeg-users@lists.sourceforge.net,
        netdev@vger.kernel.org, rcu@vger.kernel.org
Subject: [PATCH v3 00/16] Replace some bad characters on documents
Date: Sun, 16 May 2021 12:18:17 +0200
Message-Id: <cover.1621159997.git.mchehab+huawei@kernel.org>
X-Mailer: git-send-email 2.31.1
MIME-Version: 1.0
Sender: Mauro Carvalho Chehab <mchehab@kernel.org>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The conversion tools used during DocBook/LaTeX/html/Markdown->ReST 
conversion and some cut-and-pasted text contain some characters that
aren't easily reachable on standard keyboards and/or could cause 
troubles when parsed by the documentation build system.

Replace the occurences of the following characters:

            - U+00a0 (' '): NO-BREAK SPACE
            - U+00ad ('­'): SOFT HYPHEN
            - U+2010 ('‐'): HYPHEN
            - U+2217 ('∗'): ASTERISK OPERATOR
            - U+feff ('﻿'): BOM

I'll submit in separate another series to address other character occurrences.

v3:
  - removed curly commas and changed the patch descriptions.
v2:
  - removed EM/EN dashes and changed the patch descriptions.


Mauro Carvalho Chehab (16):
  docs: hwmon: ir36021.rst: replace some characters
  docs: admin-guide: reporting-issues.rst: replace some characters
  docs: trace: coresight: coresight-etm4x-reference.rst: replace some
    characters
  docs: driver-api: ioctl.rst: replace some characters
  docs: driver-api: media: drivers: zoran.rst: replace some characters
  docs: usb: replace some characters
  docs: userspace-api: media: v4l: dev-decoder.rst: replace some
    characters
  docs: userspace-api: media: dvb: intro.rst: replace some characters
  docs: vm: zswap.rst: replace some characters
  docs: filesystems: ext4: blockgroup.rst: replace some characters
  docs: networking: device_drivers: replace some characters
  docs: PCI: acpi-info.rst: replace some characters
  docs: sound: kernel-api: writing-an-alsa-driver.rst: replace some
    characters
  docs: firmware-guide: acpi: dsd: graph.rst: replace some characters
  docs: virt: kvm: api.rst: replace some characters
  docs: RCU: replace some characters

 Documentation/PCI/acpi-info.rst               | 18 ++---
 .../Data-Structures/Data-Structures.rst       | 46 ++++++------
 .../Expedited-Grace-Periods.rst               | 36 +++++-----
 .../Tree-RCU-Memory-Ordering.rst              |  2 +-
 .../RCU/Design/Requirements/Requirements.rst  | 70 +++++++++----------
 .../admin-guide/reporting-issues.rst          |  2 +-
 Documentation/driver-api/ioctl.rst            |  8 +--
 .../driver-api/media/drivers/zoran.rst        |  2 +-
 Documentation/filesystems/ext4/blockgroup.rst |  2 +-
 .../firmware-guide/acpi/dsd/graph.rst         |  2 +-
 Documentation/hwmon/ir36021.rst               |  2 +-
 .../device_drivers/ethernet/intel/i40e.rst    |  6 +-
 .../device_drivers/ethernet/intel/iavf.rst    |  2 +-
 .../kernel-api/writing-an-alsa-driver.rst     |  2 +-
 .../coresight/coresight-etm4x-reference.rst   |  2 +-
 Documentation/usb/ehci.rst                    |  2 +-
 Documentation/usb/gadget_printer.rst          |  2 +-
 .../userspace-api/media/dvb/intro.rst         |  4 +-
 .../userspace-api/media/v4l/dev-decoder.rst   |  2 +-
 Documentation/virt/kvm/api.rst                | 28 ++++----
 Documentation/vm/zswap.rst                    |  4 +-
 21 files changed, 122 insertions(+), 122 deletions(-)
```
#### [PATCH v3 0/8] KVM: Scalable memslots implementation
##### From: "Maciej S. Szmigiero" <mail@maciej.szmigiero.name>
From: "Maciej S. Szmigiero" <maciej.szmigiero@oracle.com>

```c
From patchwork Sun May 16 21:44:26 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Maciej S. Szmigiero" <mail@maciej.szmigiero.name>
X-Patchwork-Id: 12260645
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 661D4C433B4
	for <kvm@archiver.kernel.org>; Sun, 16 May 2021 21:45:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2C21461151
	for <kvm@archiver.kernel.org>; Sun, 16 May 2021 21:45:11 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234175AbhEPVqY (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sun, 16 May 2021 17:46:24 -0400
Received: from vps-vb.mhejs.net ([37.28.154.113]:54354 "EHLO vps-vb.mhejs.net"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S234128AbhEPVqX (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 16 May 2021 17:46:23 -0400
Received: from MUA
        by vps-vb.mhejs.net with esmtps  (TLS1.2) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94.2)
        (envelope-from <mail@maciej.szmigiero.name>)
        id 1liOYy-0007yi-Al; Sun, 16 May 2021 23:44:40 +0200
From: "Maciej S. Szmigiero" <mail@maciej.szmigiero.name>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Igor Mammedov <imammedo@redhat.com>,
        Marc Zyngier <maz@kernel.org>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Huacai Chen <chenhuacai@kernel.org>,
        Aleksandar Markovic <aleksandar.qemu.devel@gmail.com>,
        Paul Mackerras <paulus@ozlabs.org>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Janosch Frank <frankja@linux.ibm.com>,
        David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Claudio Imbrenda <imbrenda@linux.ibm.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v3 0/8] KVM: Scalable memslots implementation
Date: Sun, 16 May 2021 23:44:26 +0200
Message-Id: <cover.1621191549.git.maciej.szmigiero@oracle.com>
X-Mailer: git-send-email 2.31.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: "Maciej S. Szmigiero" <maciej.szmigiero@oracle.com>

The current memslot code uses a (reverse) gfn-ordered memslot array
for keeping track of them.
This only allows quick binary search by gfn, quick lookup by hva is
not possible (the implementation has to do a linear scan of the whole
memslot array).

Because the memslot array that is currently in use cannot be modified
every memslot management operation (create, delete, move, change
flags) has to make a copy of the whole array so it has a scratch copy
to work on.

Strictly speaking, however, it is only necessary to make copy of the
memslot that is being modified, copying all the memslots currently
present is just a limitation of the array-based memslot implementation.

Two memslot sets, however, are still needed so the VM continues to run
on the currently active set while the requested operation is being
performed on the second, currently inactive one.

In order to have two memslot sets, but only one copy of the actual
memslots it is necessary to split out the memslot data from the
memslot sets.

The memslots themselves should be also kept independent of each other
so they can be individually added or deleted.

These two memslot sets should normally point to the same set of memslots.
They can, however, be desynchronized when performing a memslot management
operation by replacing the memslot to be modified by its copy.
After the operation is complete, both memslot sets once again point to
the same, common set of memslot data.

This series implements the aforementioned idea.

The new implementation uses two trees to perform quick lookups:
For tracking of gfn an ordinary rbtree is used since memslots cannot
overlap in the guest address space and so this data structure is
sufficient for ensuring that lookups are done quickly.

For tracking of hva, however, an interval tree is needed since they
can overlap between memslots.

ID to memslot mappings are kept in a hash table instead of using a
statically allocated "id_to_index" array.

The "lru slot" mini-cache, that keeps track of the last found-by-gfn
memslot, is still present in the new code.

There was also a desire to make the new structure operate on "pay as
you go" basis, that is, that the user only pays the price of the
memslot count that is actually used, not of the maximum count allowed.

The operation semantics were carefully matched to the original
implementation, the outside-visible behavior should not change.
Only the timing will be different.

Making lookup and memslot management operations O(log(n)) brings some
performance benefits (tested on a Xeon 8167M machine):
509 slots in use:
Test            Before          After           Improvement
Map             0.0232s         0.0223s          4%
Unmap           0.0724s         0.0315s         56%
Unmap 2M        0.00155s        0.000869s       44%
Move active     0.000101s       0.0000792s      22%
Move inactive   0.000108s       0.0000847s      21%
Slot setup      0.0135s         0.00803s        41%

100 slots in use:
Test            Before          After           Improvement
Map             0.0195s         0.0191s         None
Unmap           0.0374s         0.0312s         17%
Unmap 2M        0.000470s       0.000447s        5%
Move active     0.0000956s      0.0000800s      16%
Move inactive   0.000101s       0.0000840s      17%
Slot setup      0.00260s        0.00174s        33%

50 slots in use:
Test            Before          After           Improvement
Map             0.0192s         0.0190s         None
Unmap           0.0339s         0.0311s          8%
Unmap 2M        0.000399s       0.000395s       None
Move active     0.0000999s      0.0000854s      15%
Move inactive   0.0000992s      0.0000826s      17%
Slot setup      0.00141s        0.000990s       30%

30 slots in use:
Test            Before          After           Improvement
Map             0.0192s         0.0190s         None
Unmap           0.0325s         0.0310s          5%
Unmap 2M        0.000373s       0.000373s       None
Move active     0.000100s       0.0000865s      14%
Move inactive   0.000106s       0.0000918s      13%
Slot setup      0.000989s       0.000775s       22%

10 slots in use:
Test            Before          After           Improvement
Map             0.0192s         0.0186s          3%
Unmap           0.0313s         0.0310s         None
Unmap 2M        0.000348s       0.000351s       None
Move active     0.000110s       0.0000948s      14%
Move inactive   0.000111s       0.0000933s      16%
Slot setup      0.000342s       0.000283s       17%

32k slots in use:
Test            Before          After           Improvement
Map (8194)       0.200s         0.0541s         73%
Unmap            3.88s          0.0351s         99%
Unmap 2M         3.88s          0.0348s         99%
Move active      0.00142s       0.0000786s      94%
Move inactive    0.00148s       0.0000880s      94%
Slot setup      16.1s           0.59s           96%

Since the map test can be done with up to 8194 slots, the result above
for this test was obtained running it with that maximum number of
slots.

In both the old and new memslot code case the measurements were done
against the new KVM selftest framework, with TDP MMU disabled
(that is, with the default setting).

On x86-64 the code was well tested, passed KVM unit tests and KVM
selftests with KASAN on.
And, of course, booted various guests successfully (including nested
ones with TDP MMU enabled).
On other KVM platforms the code was compile-tested only.

Changes since v1:
* Drop the already merged HVA handler retpoline-friendliness patch,

* Split the scalable memslots patch into 8 smaller ones,

* Rebase onto the current kvm/queue,

* Make sure that ranges at both memslot's hva_nodes are always
initialized,

* Remove kvm_mmu_calculate_default_mmu_pages() prototype, too,
when removing this function,

* Redo benchmarks, measure 32k memslots on the old implementation, too.

Changes since v2:
* Rebase onto the current kvm/queue, taking into account the now-merged
MMU notifiers rewrite.
This reduces the diffstat by ~50 lines.

 arch/arm64/kvm/Kconfig              |   1 +
 arch/arm64/kvm/mmu.c                |   8 +-
 arch/mips/kvm/Kconfig               |   1 +
 arch/powerpc/kvm/Kconfig            |   1 +
 arch/powerpc/kvm/book3s_64_mmu_hv.c |   4 +-
 arch/powerpc/kvm/book3s_64_vio.c    |   2 +-
 arch/powerpc/kvm/book3s_64_vio_hv.c |   2 +-
 arch/powerpc/kvm/book3s_hv.c        |   3 +-
 arch/powerpc/kvm/book3s_hv_nested.c |   4 +-
 arch/powerpc/kvm/book3s_hv_uvmem.c  |  14 +-
 arch/s390/kvm/Kconfig               |   1 +
 arch/s390/kvm/kvm-s390.c            |  66 +--
 arch/s390/kvm/kvm-s390.h            |  15 +
 arch/s390/kvm/pv.c                  |   4 +-
 arch/x86/include/asm/kvm_host.h     |   2 +-
 arch/x86/kvm/Kconfig                |   1 +
 arch/x86/kvm/mmu/mmu.c              |  65 +--
 arch/x86/kvm/x86.c                  |  18 +-
 include/linux/kvm_host.h            | 139 ++++---
 virt/kvm/kvm_main.c                 | 604 ++++++++++++++++------------
 20 files changed, 555 insertions(+), 400 deletions(-)
```
