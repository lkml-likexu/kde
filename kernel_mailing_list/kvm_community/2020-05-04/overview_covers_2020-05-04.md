

#### [PATCH v2 0/5] Statsfs: a new ram-based file sytem for Linux kernel
##### From: Emanuele Giuseppe Esposito <eesposit@redhat.com>

```c
From patchwork Mon May  4 11:03:39 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Emanuele Giuseppe Esposito <eesposit@redhat.com>
X-Patchwork-Id: 11525493
Return-Path: <SRS0=Q5Yu=6S=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0BBCA14B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  4 May 2020 11:04:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E29742073E
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  4 May 2020 11:04:44 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="gTOxcaUE"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727970AbgEDLEo (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 4 May 2020 07:04:44 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:38992 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1728601AbgEDLED (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 4 May 2020 07:04:03 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1588590240;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=ICTWiD14DGnWtt5uuvQA1CMZKfEw+J2p/55HnpIvnTw=;
        b=gTOxcaUEj/L42jZq9vlr7br2A9pcR012PvyYQOsPhSQGbvvRZoGePveEtis3MiqhZ8g9L1
        EfygQYBvxjSWQOo+bMdWC9S7DAkDeCB3sEQLTUcXLY9xGeKTFoN1Tm6q/9i9UpK44ZIoPQ
        5dpFK0ZiJdXLsw5qWMskdlUxvubMruw=
Received: from mail-wr1-f70.google.com (mail-wr1-f70.google.com
 [209.85.221.70]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-109-Ofmeqs5HMDOE03eiLIA6FQ-1; Mon, 04 May 2020 07:03:52 -0400
X-MC-Unique: Ofmeqs5HMDOE03eiLIA6FQ-1
Received: by mail-wr1-f70.google.com with SMTP id x8so1800075wrl.16
        for <kvm@vger.kernel.org>; Mon, 04 May 2020 04:03:52 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=ICTWiD14DGnWtt5uuvQA1CMZKfEw+J2p/55HnpIvnTw=;
        b=X4CrWDOSA/tvredqXAmsSd8NWWPfOL1KYz136zR617H0DUWZ2oEcqAwQGx2Vr9/UKO
         CTYhI5WDSowBYXgJrVrxnNt3pQOmyWUVbLwtPNaQpOOIMdWQc7nuC2RSetnCLSikwOIh
         NApJ17pxsL6QilNthzXDsZQhy0/woiBK3DlUJhY6DgUQE/vF32GZdlZh5n9iYi1J9LvF
         8TJbci34qi6uqNsJ5bD1paAybtGDyuRxW3L4Ei0ZT3KQwQd/rJRkAJ3beLGm23h68qM9
         1ecNSVhjBF21GFffLEok5PQ+bpeTF8X8IGtLARacwzfxPrrAEhy/Qdn3guBOhBNS3MXV
         n/ow==
X-Gm-Message-State: AGi0Pub1fu7Rlip+r7uSXsKy2ZY9F7SKcg1EA409YRTRGK+YCIInUsQI
        RA1mVKXxoEwppCsjSzJZVDgq4DQZrLv8c/QrG/XImCpPeuuq02TE4kG4I+Opm/KVMCqQ4JVeGWh
        w3sFDDqtypHDn
X-Received: by 2002:adf:a2d7:: with SMTP id t23mr4327210wra.402.1588590231215;
        Mon, 04 May 2020 04:03:51 -0700 (PDT)
X-Google-Smtp-Source: 
 APiQypIx2aIz7stykmwXWJf7C80Kf95sM7YNOTZKj0BHeE5ekaM3LQpRAivT6MmqN7PrZv1JcZDMtA==
X-Received: by 2002:adf:a2d7:: with SMTP id t23mr4327156wra.402.1588590230858;
        Mon, 04 May 2020 04:03:50 -0700 (PDT)
Received: from localhost.localdomain.com ([194.230.155.213])
        by smtp.gmail.com with ESMTPSA id
 a13sm10885750wrv.67.2020.05.04.04.03.48
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 04 May 2020 04:03:50 -0700 (PDT)
From: Emanuele Giuseppe Esposito <eesposit@redhat.com>
To: kvm@vger.kernel.org
Cc: Christian Borntraeger <borntraeger@de.ibm.com>,
        David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Alexander Viro <viro@zeniv.linux.org.uk>,
        Emanuele Giuseppe Esposito <e.emanuelegiuseppe@gmail.com>,
        linux-kernel@vger.kernel.org, linux-mips@vger.kernel.org,
        kvm-ppc@vger.kernel.org, linuxppc-dev@lists.ozlabs.org,
        linux-s390@vger.kernel.org, linux-fsdevel@vger.kernel.org,
        Emanuele Giuseppe Esposito <eesposit@redhat.com>
Subject: [PATCH v2 0/5] Statsfs: a new ram-based file sytem for Linux kernel
 statistics
Date: Mon,  4 May 2020 13:03:39 +0200
Message-Id: <20200504110344.17560-1-eesposit@redhat.com>
X-Mailer: git-send-email 2.25.2
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

There is currently no common way for Linux kernel subsystems to expose
statistics to userspace shared throughout the Linux kernel; subsystems
have to take care of gathering and displaying statistics by themselves,
for example in the form of files in debugfs. For example KVM has its own
code section that takes care of this in virt/kvm/kvm_main.c, where it sets
up debugfs handlers for displaying values and aggregating them from
various subfolders to obtain information about the system state (i.e.
displaying the total number of exits, calculated by summing all exits of
all cpus of all running virtual machines).

Allowing each section of the kernel to do so has two disadvantages. First,
it will introduce redundant code. Second, debugfs is anyway not the right
place for statistics (for example it is affected by lockdown)

In this patch series I introduce statsfs, a synthetic ram-based virtual
filesystem that takes care of gathering and displaying statistics for the
Linux kernel subsystems.

The file system is mounted on /sys/kernel/stats and would be already used
by kvm. Statsfs was initially introduced by Paolo Bonzini [1].

Statsfs offers a generic and stable API, allowing any kind of
directory/file organization and supporting multiple kind of aggregations
(not only sum, but also average, max, min and count_zero) and data types
(all unsigned and signed types plus boolean). The implementation, which is
a generalization of KVM’s debugfs statistics code, takes care of gathering
and displaying information at run time; users only need to specify the
values to be included in each source.

Statsfs would also be a different mountpoint from debugfs, and would not
suffer from limited access due to the security lock down patches. Its main
function is to display each statistics as a file in the desired folder
hierarchy defined through the API. Statsfs files can be read, and possibly
cleared if their file mode allows it.

Statsfs has two main components: the public API defined by
include/linux/statsfs.h, and the virtual file system which should end up
in /sys/kernel/stats.

The API has two main elements, values and sources. Kernel subsystems like
KVM can use the API to create a source, add child
sources/values/aggregates and register it to the root source (that on the
virtual fs would be /sys/kernel/statsfs).

Sources are created via statsfs_source_create(), and each source becomes a
directory in the file system. Sources form a parent-child relationship;
root sources are added to the file system via statsfs_source_register().
Every other source is added to or removed from a parent through the
statsfs_source_add_subordinate and statsfs_source_remote_subordinate APIs.
Once a source is created and added to the tree (via add_subordinate), it
will be used to compute aggregate values in the parent source.

Values represent quantites that are gathered by the statsfs user. Examples
of values include the number of vm exits of a given kind, the amount of
memory used by some data structure, the length of the longest hash table
chain, or anything like that. Values are defined with the
statsfs_source_add_values function. Each value is defined by a struct
statsfs_value; the same statsfs_value can be added to many different
sources. A value can be considered "simple" if it fetches data from a
user-provided location, or "aggregate" if it groups all values in the
subordinates sources that include the same statsfs_value.

For more information, please consult the kerneldoc documentation in patch
2 and the sample uses in the kunit tests and in KVM.

This series of patches is based on my previous series "libfs: group and
simplify linux fs code" and the single patch sent to kvm "kvm_host: unify
VM_STAT and VCPU_STAT definitions in a single place". The former
simplifies code duplicated in debugfs and tracefs (from which statsfs is
based on), the latter groups all macros definition for statistics in kvm
in a single common file shared by all architectures.

Patch 1 adds a new refcount and kref destructor wrappers that take a
semaphore, as those are used later by statsfs. Patch 2 introduces the
statsfs API, patch 3 provides extensive tests that can also be used as
example on how to use the API and patch 4 adds the file system support.
Finally, patch 5 provides a real-life example of statsfs usage in KVM.

[1] https://lore.kernel.org/kvm/5d6cdcb1-d8ad-7ae6-7351-3544e2fa366d@redhat.com/?fbclid=IwAR18LHJ0PBcXcDaLzILFhHsl3qpT3z2vlG60RnqgbpGYhDv7L43n0ZXJY8M

Signed-off-by: Emanuele Giuseppe Esposito <eesposit@redhat.com>

v1->v2 remove unnecessary list_foreach_safe loops, fix wrong indentation,
change statsfs in stats_fs

Emanuele Giuseppe Esposito (5):
  refcount, kref: add dec-and-test wrappers for rw_semaphores
  stats_fs API: create, add and remove stats_fs sources and values
  kunit: tests for stats_fs API
  stats_fs fs: virtual fs to show stats to the end-user
  kvm_main: replace debugfs with stats_fs

 MAINTAINERS                     |    7 +
 arch/arm64/kvm/Kconfig          |    1 +
 arch/arm64/kvm/guest.c          |    2 +-
 arch/mips/kvm/Kconfig           |    1 +
 arch/mips/kvm/mips.c            |    2 +-
 arch/powerpc/kvm/Kconfig        |    1 +
 arch/powerpc/kvm/book3s.c       |    6 +-
 arch/powerpc/kvm/booke.c        |    8 +-
 arch/s390/kvm/Kconfig           |    1 +
 arch/s390/kvm/kvm-s390.c        |   16 +-
 arch/x86/include/asm/kvm_host.h |    2 +-
 arch/x86/kvm/Kconfig            |    1 +
 arch/x86/kvm/Makefile           |    2 +-
 arch/x86/kvm/debugfs.c          |   64 --
 arch/x86/kvm/stats_fs.c         |   56 ++
 arch/x86/kvm/x86.c              |    6 +-
 fs/Kconfig                      |   12 +
 fs/Makefile                     |    1 +
 fs/stats_fs/Makefile            |    6 +
 fs/stats_fs/inode.c             |  337 ++++++++++
 fs/stats_fs/internal.h          |   35 +
 fs/stats_fs/stats_fs-tests.c    | 1088 +++++++++++++++++++++++++++++++
 fs/stats_fs/stats_fs.c          |  773 ++++++++++++++++++++++
 include/linux/kref.h            |   11 +
 include/linux/kvm_host.h        |   39 +-
 include/linux/refcount.h        |    2 +
 include/linux/stats_fs.h        |  304 +++++++++
 include/uapi/linux/magic.h      |    1 +
 lib/refcount.c                  |   32 +
 tools/lib/api/fs/fs.c           |   21 +
 virt/kvm/arm/arm.c              |    2 +-
 virt/kvm/kvm_main.c             |  314 ++-------
 32 files changed, 2772 insertions(+), 382 deletions(-)
 delete mode 100644 arch/x86/kvm/debugfs.c
 create mode 100644 arch/x86/kvm/stats_fs.c
 create mode 100644 fs/stats_fs/Makefile
 create mode 100644 fs/stats_fs/inode.c
 create mode 100644 fs/stats_fs/internal.h
 create mode 100644 fs/stats_fs/stats_fs-tests.c
 create mode 100644 fs/stats_fs/stats_fs.c
 create mode 100644 include/linux/stats_fs.h
```
#### [PATCH 0/3] KVM: x86: cleanup and fixes for debug register accesses
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
From patchwork Mon May  4 15:55:55 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11526607
Return-Path: <SRS0=Q5Yu=6S=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 17BF91392
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  4 May 2020 15:56:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E6A4E20705
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  4 May 2020 15:56:03 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="TwOpXRKl"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729141AbgEDP4D (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 4 May 2020 11:56:03 -0400
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:24212 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1728873AbgEDP4C (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 4 May 2020 11:56:02 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1588607761;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc; bh=eX+GzNLLoLRdY/7Oo9fQjZpifFeDPG106etXnTI+oh4=;
        b=TwOpXRKlFECLn2zOTFdPSRmiT5taJq0LbU3farurr03Tan3CaJMDYe+xz+NBr+k0+SPQ4+
        vX/8SOk5Ke+cOu0hOjix31bbsF3SOhjCPwqUfz4ot3wA5CJlcH6M9DUrP8fJHgEtc/ua9j
        QVZ+HtWhcVTogDHEqr1JA+3KNjntpg0=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-221-Hn7cpswBOnSw0swXlGpKDw-1; Mon, 04 May 2020 11:56:00 -0400
X-MC-Unique: Hn7cpswBOnSw0swXlGpKDw-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 06585107AFD4;
        Mon,  4 May 2020 15:55:59 +0000 (UTC)
Received: from virtlab511.virt.lab.eng.bos.redhat.com
 (virtlab511.virt.lab.eng.bos.redhat.com [10.19.152.198])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 8C1D96FF1A;
        Mon,  4 May 2020 15:55:58 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Subject: [PATCH 0/3] KVM: x86: cleanup and fixes for debug register accesses
Date: Mon,  4 May 2020 11:55:55 -0400
Message-Id: <20200504155558.401468-1-pbonzini@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The purpose of this series is to get rid of the get_dr6 accessor
and, on Intel, of set_dr6 as well.  This is done mostly in patch 2,
since patch 3 is only the resulting cleanup.  Patch 1 is a related
bug fix that I found while inspecting the code.

A guest debugging selftest is sorely needed if anyone wants to take
a look!

Paolo

Paolo Bonzini (3):
  KVM: SVM: fill in kvm_run->debug.arch.dr[67]
  KVM: SVM: keep DR6 synchronized with vcpu->arch.dr6
  KVM: x86: simplify dr6 accessors in kvm_x86_ops

 arch/x86/include/asm/kvm_host.h |  1 -
 arch/x86/kvm/svm/svm.c          | 11 ++++-------
 arch/x86/kvm/vmx/vmx.c          | 11 -----------
 arch/x86/kvm/x86.c              |  8 +++-----
 4 files changed, 7 insertions(+), 24 deletions(-)
Reviewed-by: Peter Xu <peterx@redhat.com>
```
#### [PATCH Kernel v18 0/7] KABIs to support migration for VFIO devices
##### From: Kirti Wankhede <kwankhede@nvidia.com>

```c
From patchwork Mon May  4 15:58:52 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kirti Wankhede <kwankhede@nvidia.com>
X-Patchwork-Id: 11526681
Return-Path: <SRS0=Q5Yu=6S=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4567215AB
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  4 May 2020 16:32:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 21BCB20705
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  4 May 2020 16:32:17 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=nvidia.com header.i=@nvidia.com
 header.b="sCX816iJ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729665AbgEDQcQ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 4 May 2020 12:32:16 -0400
Received: from hqnvemgate25.nvidia.com ([216.228.121.64]:10644 "EHLO
        hqnvemgate25.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729604AbgEDQcP (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 4 May 2020 12:32:15 -0400
Received: from hqpgpgate101.nvidia.com (Not Verified[216.228.121.13]) by
 hqnvemgate25.nvidia.com (using TLS: TLSv1.2, DES-CBC3-SHA)
        id <B5eb043490000>; Mon, 04 May 2020 09:31:06 -0700
Received: from hqmail.nvidia.com ([172.20.161.6])
  by hqpgpgate101.nvidia.com (PGP Universal service);
  Mon, 04 May 2020 09:32:15 -0700
X-PGP-Universal: processed;
        by hqpgpgate101.nvidia.com on Mon, 04 May 2020 09:32:15 -0700
Received: from HQMAIL101.nvidia.com (172.20.187.10) by HQMAIL111.nvidia.com
 (172.20.187.18) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Mon, 4 May
 2020 16:32:15 +0000
Received: from kwankhede-dev.nvidia.com (10.124.1.5) by HQMAIL101.nvidia.com
 (172.20.187.10) with Microsoft SMTP Server (TLS) id 15.0.1473.3 via Frontend
 Transport; Mon, 4 May 2020 16:32:08 +0000
From: Kirti Wankhede <kwankhede@nvidia.com>
To: <alex.williamson@redhat.com>, <cjia@nvidia.com>
CC: <kevin.tian@intel.com>, <ziye.yang@intel.com>,
        <changpeng.liu@intel.com>, <yi.l.liu@intel.com>,
        <mlevitsk@redhat.com>, <eskultet@redhat.com>, <cohuck@redhat.com>,
        <dgilbert@redhat.com>, <jonathan.davies@nutanix.com>,
        <eauger@redhat.com>, <aik@ozlabs.ru>, <pasic@linux.ibm.com>,
        <felipe@nutanix.com>, <Zhengxiao.zx@Alibaba-inc.com>,
        <shuangtai.tst@alibaba-inc.com>, <Ken.Xue@amd.com>,
        <zhi.a.wang@intel.com>, <yan.y.zhao@intel.com>,
        <qemu-devel@nongnu.org>, <kvm@vger.kernel.org>,
        "Kirti Wankhede" <kwankhede@nvidia.com>
Subject: [PATCH Kernel v18 0/7] KABIs to support migration for VFIO devices
Date: Mon, 4 May 2020 21:28:52 +0530
Message-ID: <1588607939-26441-1-git-send-email-kwankhede@nvidia.com>
X-Mailer: git-send-email 2.7.0
X-NVConfidentiality: public
MIME-Version: 1.0
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1588609866; bh=ZbX+QQV922iYQMwb1v9icsD1X5ueLZ4WbJNPZqSyR0U=;
        h=X-PGP-Universal:From:To:CC:Subject:Date:Message-ID:X-Mailer:
         X-NVConfidentiality:MIME-Version:Content-Type;
        b=sCX816iJof9Djm8+Y6ddYHXpQl+LZcb/sliaqCkD5mgoLoMmjalDaxvOWie05F4jz
         18Ao99gEKyEQ3d4gGL8Bra+7BEQFp4z2wvI2/fOjaDptzl+HZ9G8djKioIpZr1S5Qg
         /DKz1gWf1KUU6VBgDIjwd9+xY/IgfZI4uX2pNBsIFV6jIeqgG9PdEHAV1nP+55X73P
         TyTsbcKIvZLU+WlodTneOphCtqtdA2c77fGfpBWVJP/tN7omC2WVeqyru0YFK5qO2O
         zO3JGQvHsfph9dsJgpf1HelxLji1hIRqQrr+r3R6pGvHDkgBH5Tyx4JhKpAkTiqrEa
         YjGPBcPAGJmNA==
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

This patch set adds:
* IOCTL VFIO_IOMMU_DIRTY_PAGES to get dirty pages bitmap with
  respect to IOMMU container rather than per device. All pages pinned by
  vendor driver through vfio_pin_pages external API has to be marked as
  dirty during  migration. When IOMMU capable device is present in the
  container and all pages are pinned and mapped, then all pages are marked
  dirty.
  When there are CPU writes, CPU dirty page tracking can identify dirtied
  pages, but any page pinned by vendor driver can also be written by
  device. As of now there is no device which has hardware support for
  dirty page tracking. So all pages which are pinned should be considered
  as dirty.
  This ioctl is also used to start/stop dirty pages tracking for pinned and
  unpinned pages while migration is active.

* Updated IOCTL VFIO_IOMMU_UNMAP_DMA to get dirty pages bitmap before
  unmapping IO virtual address range.
  With vIOMMU, during pre-copy phase of migration, while CPUs are still
  running, IO virtual address unmap can happen while device still keeping
  reference of guest pfns. Those pages should be reported as dirty before
  unmap, so that VFIO user space application can copy content of those
  pages from source to destination.

* Patch 7 detect if IOMMU capable device driver is smart to report pages
  to be marked dirty by pinning pages using vfio_pin_pages() API.


Yet TODO:
Since there is no device which has hardware support for system memmory
dirty bitmap tracking, right now there is no other API from vendor driver
to VFIO IOMMU module to report dirty pages. In future, when such hardware
support will be implemented, an API will be required such that vendor
driver could report dirty pages to VFIO module during migration phases.

Adding revision history from previous QEMU patch set to understand KABI
changes done till now

v17 -> v18
- Add migration capability to the capability chain for VFIO_IOMMU_GET_INFO
  ioctl
- Updated UMAP_DMA ioctl to return bitmap of multiple vfio_dma

v16 -> v17
- Fixed errors reported by kbuild test robot <lkp@intel.com> on i386

v15 -> v16
- Minor edits and nit picks (Auger Eric)
- On copying bitmap to user, re-populated bitmap only for pinned pages,
  excluding unmapped pages and CPU dirtied pages.
- Patches are on tag: next-20200318 and 1-3 patches from Yan's series
  https://lkml.org/lkml/2020/3/12/1255

v14 -> v15
- Minor edits and nit picks.
- In the verification of user allocated bitmap memory, added check of
   maximum size.
- Patches are on tag: next-20200318 and 1-3 patches from Yan's series
  https://lkml.org/lkml/2020/3/12/1255

v13 -> v14
- Added struct vfio_bitmap to kabi. updated structure
  vfio_iommu_type1_dirty_bitmap_get and vfio_iommu_type1_dma_unmap.
- All small changes suggested by Alex.
- Patches are on tag: next-20200318 and 1-3 patches from Yan's series
  https://lkml.org/lkml/2020/3/12/1255

v12 -> v13
- Changed bitmap allocation in vfio_iommu_type1 to per vfio_dma
- Changed VFIO_IOMMU_DIRTY_PAGES ioctl behaviour to be per vfio_dma range.
- Changed vfio_iommu_type1_dirty_bitmap structure to have separate data
  field.

v11 -> v12
- Changed bitmap allocation in vfio_iommu_type1.
- Remove atomicity of ref_count.
- Updated comments for migration device state structure about error
  reporting.
- Nit picks from v11 reviews

v10 -> v11
- Fix pin pages API to free vpfn if it is marked as unpinned tracking page.
- Added proposal to detect if IOMMU capable device calls external pin pages
  API to mark pages dirty.
- Nit picks from v10 reviews

v9 -> v10:
- Updated existing VFIO_IOMMU_UNMAP_DMA ioctl to get dirty pages bitmap
  during unmap while migration is active
- Added flag in VFIO_IOMMU_GET_INFO to indicate driver support dirty page
  tracking.
- If iommu_mapped, mark all pages dirty.
- Added unpinned pages tracking while migration is active.
- Updated comments for migration device state structure with bit
  combination table and state transition details.

v8 -> v9:
- Split patch set in 2 sets, Kernel and QEMU.
- Dirty pages bitmap is queried from IOMMU container rather than from
  vendor driver for per device. Added 2 ioctls to achieve this.

v7 -> v8:
- Updated comments for KABI
- Added BAR address validation check during PCI device's config space load
  as suggested by Dr. David Alan Gilbert.
- Changed vfio_migration_set_state() to set or clear device state flags.
- Some nit fixes.

v6 -> v7:
- Fix build failures.

v5 -> v6:
- Fix build failure.

v4 -> v5:
- Added decriptive comment about the sequence of access of members of
  structure vfio_device_migration_info to be followed based on Alex's
  suggestion
- Updated get dirty pages sequence.
- As per Cornelia Huck's suggestion, added callbacks to VFIODeviceOps to
  get_object, save_config and load_config.
- Fixed multiple nit picks.
- Tested live migration with multiple vfio device assigned to a VM.

v3 -> v4:
- Added one more bit for _RESUMING flag to be set explicitly.
- data_offset field is read-only for user space application.
- data_size is read for every iteration before reading data from migration,
  that is removed assumption that data will be till end of migration
  region.
- If vendor driver supports mappable sparsed region, map those region
  during setup state of save/load, similarly unmap those from cleanup
  routines.
- Handles race condition that causes data corruption in migration region
  during save device state by adding mutex and serialiaing save_buffer and
  get_dirty_pages routines.
- Skip called get_dirty_pages routine for mapped MMIO region of device.
- Added trace events.
- Split into multiple functional patches.

v2 -> v3:
- Removed enum of VFIO device states. Defined VFIO device state with 2
  bits.
- Re-structured vfio_device_migration_info to keep it minimal and defined
  action on read and write access on its members.

v1 -> v2:
- Defined MIGRATION region type and sub-type which should be used with
  region type capability.
- Re-structured vfio_device_migration_info. This structure will be placed
  at 0th offset of migration region.
- Replaced ioctl with read/write for trapped part of migration region.
- Added both type of access support, trapped or mmapped, for data section
  of the region.
- Moved PCI device functions to pci file.
- Added iteration to get dirty page bitmap until bitmap for all requested
  pages are copied.

Thanks,
Kirti




Kirti Wankhede (7):
  vfio: UAPI for migration interface for device state
  vfio iommu: Remove atomicity of ref_count of pinned pages
  vfio iommu: Add ioctl definition for dirty pages tracking.
  vfio iommu: Implementation of ioctl for dirty pages tracking.
  vfio iommu: Update UNMAP_DMA ioctl to get dirty bitmap before unmap
  vfio iommu: Add migration capability to report supported features
  vfio: Selective dirty page tracking if IOMMU backed device pins pages

 drivers/vfio/vfio.c             |  13 +-
 drivers/vfio/vfio_iommu_type1.c | 464 ++++++++++++++++++++++++++++++++++++++--
 include/linux/vfio.h            |   4 +-
 include/uapi/linux/vfio.h       | 308 ++++++++++++++++++++++++++
 4 files changed, 770 insertions(+), 19 deletions(-)
```
#### [PATCH v1 0/2] Sample mtty: Add migration support
##### From: Kirti Wankhede <kwankhede@nvidia.com>

```c
From patchwork Mon May  4 17:54:18 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kirti Wankhede <kwankhede@nvidia.com>
X-Patchwork-Id: 11527393
Return-Path: <SRS0=Q5Yu=6S=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 574AD15AB
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  4 May 2020 18:27:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 32D6724960
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  4 May 2020 18:27:38 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=nvidia.com header.i=@nvidia.com
 header.b="XIkUIBsG"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730811AbgEDS1h (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 4 May 2020 14:27:37 -0400
Received: from hqnvemgate24.nvidia.com ([216.228.121.143]:6434 "EHLO
        hqnvemgate24.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1730700AbgEDS1h (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 4 May 2020 14:27:37 -0400
Received: from hqpgpgate102.nvidia.com (Not Verified[216.228.121.13]) by
 hqnvemgate24.nvidia.com (using TLS: TLSv1.2, DES-CBC3-SHA)
        id <B5eb05e180000>; Mon, 04 May 2020 11:25:28 -0700
Received: from hqmail.nvidia.com ([172.20.161.6])
  by hqpgpgate102.nvidia.com (PGP Universal service);
  Mon, 04 May 2020 11:27:36 -0700
X-PGP-Universal: processed;
        by hqpgpgate102.nvidia.com on Mon, 04 May 2020 11:27:36 -0700
Received: from HQMAIL105.nvidia.com (172.20.187.12) by HQMAIL105.nvidia.com
 (172.20.187.12) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Mon, 4 May
 2020 18:27:36 +0000
Received: from kwankhede-dev.nvidia.com (10.124.1.5) by HQMAIL105.nvidia.com
 (172.20.187.12) with Microsoft SMTP Server (TLS) id 15.0.1473.3 via Frontend
 Transport; Mon, 4 May 2020 18:27:29 +0000
From: Kirti Wankhede <kwankhede@nvidia.com>
To: <alex.williamson@redhat.com>, <cjia@nvidia.com>
CC: <kevin.tian@intel.com>, <ziye.yang@intel.com>,
        <changpeng.liu@intel.com>, <yi.l.liu@intel.com>,
        <mlevitsk@redhat.com>, <eskultet@redhat.com>, <cohuck@redhat.com>,
        <dgilbert@redhat.com>, <jonathan.davies@nutanix.com>,
        <eauger@redhat.com>, <aik@ozlabs.ru>, <pasic@linux.ibm.com>,
        <felipe@nutanix.com>, <Zhengxiao.zx@Alibaba-inc.com>,
        <shuangtai.tst@alibaba-inc.com>, <Ken.Xue@amd.com>,
        <zhi.a.wang@intel.com>, <yan.y.zhao@intel.com>,
        <qemu-devel@nongnu.org>, <kvm@vger.kernel.org>,
        Kirti Wankhede <kwankhede@nvidia.com>
Subject: [PATCH v1 0/2] Sample mtty: Add migration support
Date: Mon, 4 May 2020 23:24:18 +0530
Message-ID: <1588614860-16330-1-git-send-email-kwankhede@nvidia.com>
X-Mailer: git-send-email 2.7.0
X-NVConfidentiality: public
MIME-Version: 1.0
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1588616728; bh=Pb04Iu62xKvSrOf93txxsuT7GSxKY/A1qJ9hHxmcZuw=;
        h=X-PGP-Universal:From:To:CC:Subject:Date:Message-ID:X-Mailer:
         X-NVConfidentiality:MIME-Version:Content-Type;
        b=XIkUIBsG/2E3lUv77T7YmZp3/8PEYGrkbFAMksY3qDhYXCtfGyogTciOwsAsMc9l8
         fPkc0fv01NfPurK2cnjLdu6Nnq4hqfTzcgwCmIsfi/GKjbZ9DoKDqT7yqqDKqNYfhS
         72q/9cmZTpr1Ha925S7Z+5lz59DCcD5hhzt/k2cpyOe/BiypOtPpbXlwN75n7gnWa+
         5kApbA6kXPIVuPuS35kL0tcNuktGWFHG56BSv6XPvDd7QGoPOWUBD1ZRwYQhxZlld0
         zjLVpvK6OkNsILm5PSOU46cId8j6PuN/gGX4T4eS6P3NvqAsyp2kNBGV2hBZtwWNPj
         DRKKmwZaRZ8cw==
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

These patches add migration support to mtty module.

mtty module doesn't pin pages, but to test migration interface which
queries dirty pages, first patch adds sysfs file to pin pages. Input to
this file is guest pfn. Each write to sysfs file pins one page.

Second patch add migration interface to mtty module.

Only stop-and-copy phase is implemented.
Postcopy migration is not supported.
This series is for testing purpose only.

Signed-off-by: Kirti Wankhede <kwankhede@nvidia.com>

Kirti Wankhede (2):
  Sample mtty: Add sysfs interface to pin pages
  Sample mtty: Add migration capability to mtty module

 samples/vfio-mdev/mtty.c | 778 +++++++++++++++++++++++++++++++++++++++++++++--
 1 file changed, 749 insertions(+), 29 deletions(-)
```
