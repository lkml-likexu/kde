

#### [PATCH 0/2] KVM: SVM: convert get_user_pages() --> pin_user_pages(),
##### From: John Hubbard <jhubbard@nvidia.com>

```c
From patchwork Tue May 26 06:22:05 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: John Hubbard <jhubbard@nvidia.com>
X-Patchwork-Id: 11569945
Return-Path: <SRS0=g4lY=7I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DC639913
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 26 May 2020 06:22:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C3EB5207D8
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 26 May 2020 06:22:20 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=nvidia.com header.i=@nvidia.com
 header.b="ey7+nu0R"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729605AbgEZGWO (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 26 May 2020 02:22:14 -0400
Received: from hqnvemgate24.nvidia.com ([216.228.121.143]:13895 "EHLO
        hqnvemgate24.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728138AbgEZGWN (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 26 May 2020 02:22:13 -0400
Received: from hqpgpgate101.nvidia.com (Not Verified[216.228.121.13]) by
 hqnvemgate24.nvidia.com (using TLS: TLSv1.2, DES-CBC3-SHA)
        id <B5eccb53a0000>; Mon, 25 May 2020 23:20:42 -0700
Received: from hqmail.nvidia.com ([172.20.161.6])
  by hqpgpgate101.nvidia.com (PGP Universal service);
  Mon, 25 May 2020 23:22:10 -0700
X-PGP-Universal: processed;
        by hqpgpgate101.nvidia.com on Mon, 25 May 2020 23:22:10 -0700
Received: from HQMAIL105.nvidia.com (172.20.187.12) by HQMAIL101.nvidia.com
 (172.20.187.10) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Tue, 26 May
 2020 06:22:10 +0000
Received: from hqnvemgw03.nvidia.com (10.124.88.68) by HQMAIL105.nvidia.com
 (172.20.187.12) with Microsoft SMTP Server (TLS) id 15.0.1473.3 via Frontend
 Transport; Tue, 26 May 2020 06:22:10 +0000
Received: from sandstorm.nvidia.com (Not Verified[10.2.58.199]) by
 hqnvemgw03.nvidia.com with Trustwave SEG (v7,5,8,10121)
        id <B5eccb5920000>; Mon, 25 May 2020 23:22:10 -0700
From: John Hubbard <jhubbard@nvidia.com>
To: LKML <linux-kernel@vger.kernel.org>
CC: Souptick Joarder <jrdr.linux@gmail.com>,
        John Hubbard <jhubbard@nvidia.com>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        Thomas Gleixner <tglx@linutronix.de>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        "H . Peter Anvin" <hpa@zytor.com>, <x86@kernel.org>,
        <kvm@vger.kernel.org>
Subject: [PATCH 0/2] KVM: SVM: convert get_user_pages() --> pin_user_pages(),
 bug fixes
Date: Mon, 25 May 2020 23:22:05 -0700
Message-ID: <20200526062207.1360225-1-jhubbard@nvidia.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
X-NVConfidentiality: public
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1590474042; bh=xyHCUTas3F16ZK+n98+gQf/X3rsWdl0q0EXVHn6zcqQ=;
        h=X-PGP-Universal:From:To:CC:Subject:Date:Message-ID:X-Mailer:
         MIME-Version:X-NVConfidentiality:Content-Transfer-Encoding:
         Content-Type;
        b=ey7+nu0R2FPsgmiBmHjb7F5Y0ADHbPJ0yum97UBILsXbjXAtn3kOVKjSj1QKjVnQm
         iQXdYCvx0qaJZMEFGKZahaThMMdnDvoi6FGdpvhkLJCRheWBG1apBurFlPNiNnCKLM
         wz8F5ThCruyg7jUyt+7loyRsDSmanTCg3FWFjg/nebLBDK7jP6oIIkBJAFm8czFw8R
         IEbOP4U79X767fLsRqt1lJ3/9zlzV7i1G7spOHS9QkTfDsfkEjuouu35pZxYx03obh
         u3YgPJ1iyu2URs8jIBpx57ojeauDJfPbINW/655wqs/ISdDx1fkppwOom9ADXqy5J3
         UKwU1YIayHCOA==
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

This is just for the SEV (Secure Encrypted Virtualization) part of KVM.
It converts the get_user_pages_fast() call, after fixing a couple of
small bugs in the vicinity.

Note that I have only compile-tested these two patches, so any run-time
testing coverage would be greatly appreciated.

Cc: Ingo Molnar <mingo@redhat.com>
Cc: Borislav Petkov <bp@alien8.de>
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>
Cc: Wanpeng Li <wanpengli@tencent.com>
Cc: Jim Mattson <jmattson@google.com>
Cc: Joerg Roedel <joro@8bytes.org>
Cc: H. Peter Anvin <hpa@zytor.com>
Cc: x86@kernel.org
Cc: kvm@vger.kernel.org


John Hubbard (2):
  KVM: SVM: fix svn_pin_memory()'s use of get_user_pages_fast()
  KVM: SVM: convert get_user_pages() --> pin_user_pages()

 arch/x86/kvm/svm/sev.c | 12 ++++++++----
 1 file changed, 8 insertions(+), 4 deletions(-)


base-commit: 9cb1fd0efd195590b828b9b865421ad345a4a145
```
#### [PATCH v3 0/7] Statsfs: a new ram-based file system for Linux kernel
##### From: Emanuele Giuseppe Esposito <eesposit@redhat.com>

```c
From patchwork Tue May 26 11:03:10 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Emanuele Giuseppe Esposito <eesposit@redhat.com>
X-Patchwork-Id: 11570329
Return-Path: <SRS0=g4lY=7I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0BE4160D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 26 May 2020 11:03:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E79E32084C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 26 May 2020 11:03:55 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="DMuOOaAG"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388900AbgEZLDx (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 26 May 2020 07:03:53 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:37952 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S2388858AbgEZLDv (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 26 May 2020 07:03:51 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1590491028;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=YiHC1jSZ9odIhljl+OEk0Z9XTPo94KqwVQ3mMvdqhCY=;
        b=DMuOOaAGXfOSIGzwiBAhU/ngZOWPAm28LwZHUJBTTHp2/PmFirNu1HwY1qwSeqXq03JUgb
        KSp3s0ILTCj+GqK+w9BvokbQWcqNcsv8pm/B74K1SFvmJNfvq+2GBLlGiYvjy8in00lbJh
        efZvBRBACdyknTjn9H1pZMSpeSrqAAQ=
Received: from mail-wm1-f71.google.com (mail-wm1-f71.google.com
 [209.85.128.71]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-148-aIFaE5HrNhelrupQ-S6L-A-1; Tue, 26 May 2020 07:03:44 -0400
X-MC-Unique: aIFaE5HrNhelrupQ-S6L-A-1
Received: by mail-wm1-f71.google.com with SMTP id t62so951659wmt.7
        for <kvm@vger.kernel.org>; Tue, 26 May 2020 04:03:44 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=YiHC1jSZ9odIhljl+OEk0Z9XTPo94KqwVQ3mMvdqhCY=;
        b=EdgZbg1SsBev1A0yiFbhxd6x1COlfxM0oSi1A2ME2JEx2i1L/4bUCke//U+fJTJnrU
         v9CNTCae3dGwdaZK31MmsevOWk08mKsQPrxC7As0mNCEd3BD4Pq4mkWd5a4GKCd7zHY0
         BWPHNLDjUCgNppkMEAG5ODba7wTGLFL++Zn6krm4CPN8CXB9vURmQbCWAA1HPfa+ivr8
         qscITY+55al9krWLHfQ2eycOP//CJPBG6V6R9JwTz+uG6jXQgYUQ7PbfmA0l+Nn7zuhS
         MWffpdC3MA/5YRZjF5oD0U2myrulo0glVj0lD56kxL8IEtKp9NxwcJLKQ5V47nUU1mnL
         YcKg==
X-Gm-Message-State: AOAM5322vx7NCNyLjW2qkGalLchQ/sL76RhLFUsewTAaQuOe569pPPy5
        qKLPQHkNHCzL+5bAQKbXiF6DY1gJBbYF0EgxFvrTTUX8areuWB/1LzOseXeGlIfbeDz6Kbiw9Ke
        t2fPuj0u2Rwi2
X-Received: by 2002:a7b:c8d6:: with SMTP id f22mr867254wml.108.1590491022779;
        Tue, 26 May 2020 04:03:42 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJy+r1rjVk/6TMhaP3IgReV3uZsywmdIrm1MH7nDDpPZhbJkQGL0WqDauUTDI+FV3ViYCaqhZA==
X-Received: by 2002:a7b:c8d6:: with SMTP id f22mr867213wml.108.1590491022381;
        Tue, 26 May 2020 04:03:42 -0700 (PDT)
Received: from localhost.localdomain.com ([194.230.155.118])
        by smtp.gmail.com with ESMTPSA id
 d6sm22928240wrj.90.2020.05.26.04.03.25
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 26 May 2020 04:03:31 -0700 (PDT)
From: Emanuele Giuseppe Esposito <eesposit@redhat.com>
To: kvm@vger.kernel.org
Cc: Christian Borntraeger <borntraeger@de.ibm.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Alexander Viro <viro@zeniv.linux.org.uk>,
        Emanuele Giuseppe Esposito <e.emanuelegiuseppe@gmail.com>,
        David Rientjes <rientjes@google.com>,
        Jonathan Adams <jwadams@google.com>, linux-doc@vger.kernel.org,
        linux-kernel@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
        linux-mips@vger.kernel.org, kvm-ppc@vger.kernel.org,
        linuxppc-dev@lists.ozlabs.org, linux-s390@vger.kernel.org,
        linux-fsdevel@vger.kernel.org, netdev@vger.kernel.org,
        Emanuele Giuseppe Esposito <eesposit@redhat.com>
Subject: [PATCH v3 0/7] Statsfs: a new ram-based file system for Linux kernel
 statistics
Date: Tue, 26 May 2020 13:03:10 +0200
Message-Id: <20200526110318.69006-1-eesposit@redhat.com>
X-Mailer: git-send-email 2.25.4
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

There is currently no common way for Linux kernel subsystems to expose
statistics to userspace shared throughout the Linux kernel; subsystems have
to take care of gathering and displaying statistics by themselves, for
example in the form of files in debugfs. For example KVM has its own code
section that takes care of this in virt/kvm/kvm_main.c, where it sets up
debugfs handlers for displaying values and aggregating them from various
subfolders to obtain information about the system state (i.e. displaying
the total number of exits, calculated by summing all exits of all cpus of
all running virtual machines).

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
(boolean, unsigned/signed and custom types). The implementation, which is
a generalization of KVM’s debugfs statistics code, takes care of gathering
and displaying information at run time; users only need to specify the
values to be included in each source.

Statsfs would also be a different mountpoint from debugfs, and would not
suffer from limited access due to the security lock down patches. Its main
function is to display each statistics as a file in the desired folder
hierarchy defined through the API. Statsfs files can be read, and possibly
cleared if their file mode allows it.

Statsfs has two main components: the public API defined by
include/linux/statsfs.h, and the virtual file system which should end up in
/sys/kernel/stats.

The API has two main elements, values and sources. Kernel subsystems like
KVM can use the API to create a source, add child sources/values/aggregates
and register it to the root source (that on the virtual fs would be
/sys/kernel/statsfs).

Sources are created via statsfs_source_create(), and each source becomes a
directory in the file system. Sources form a parent-child relationship;
root sources are added to the file system via statsfs_source_register().
Every other source is added to or removed from a parent through the
statsfs_source_add_subordinate and statsfs_source_remote_subordinate APIs.
Once a source is created and added to the tree (via add_subordinate), it
will be used to compute aggregate values in the parent source.
A source can optionally be hidden from the filesystem
but still considered in the aggregation operations if the corresponding
flag is set during initialization.

Values represent quantites that are gathered by the statsfs user. Examples
of values include the number of vm exits of a given kind, the amount of
memory used by some data structure, the length of the longest hash table
chain, or anything like that. Values are defined with the
statsfs_source_add_values function. Each value is defined by a struct
statsfs_value; the same statsfs_value can be added to many different
sources. A value can be considered "simple" if it fetches data from a
user-provided location, or "aggregate" if it groups all values in the
subordinates sources that include the same statsfs_value.
Each value has a stats_fs_type pointer in order to allow the user to
provide custom get and clear functions. The library, however, also
exports default stats_fs_type structs for the standard types
(all unsigned and signed types plus boolean).
A value can also provide a show function, that takes care
of displaying the value in a custom string format. This can be especially
useful when displaying enums.

For more information, please consult the kerneldoc documentation in patch 2
and the sample uses in the kunit tests, KVM and networking.

This series of patches is based on my previous series "libfs: group and
simplify linux fs code" and the single patch sent to kvm "kvm_host: unify
VM_STAT and VCPU_STAT definitions in a single place". The former simplifies
code duplicated in debugfs and tracefs (from which statsfs is based on),
the latter groups all macros definition for statistics in kvm in a single
common file shared by all architectures.

Patch 1 adds a new refcount and kref destructor wrappers that take a
semaphore, as those are used later by statsfs. Patch 2 introduces the
statsfs API, patch 3 provides extensive tests that can also be used as
example on how to use the API and patch 4 adds the file system support.
Finally, patch 5 provides a real-life example of statsfs usage in KVM,
with patch 6 providing a concrete example of the show function and
patch 7 another real-life example in the networking subsystem.

[1] https://lore.kernel.org/kvm/5d6cdcb1-d8ad-7ae6-7351-3544e2fa366d@redhat.com/?fbclid=IwAR18LHJ0PBcXcDaLzILFhHsl3qpT3z2vlG60RnqgbpGYhDv7L43n0ZXJY8M

Signed-off-by: Emanuele Giuseppe Esposito <eesposit@redhat.com>

v2 -> v3 move kconfig entry in the pseudo filesystem menu, add
documentation, get/clear function for value types, show function,
floating/cumulative and hidden flags. Also added the netstat
example

Emanuele Giuseppe Esposito (7):
  stats_fs API: create, add and remove stats_fs sources and values
  documentation for stats_fs
  kunit: tests for stats_fs API
  stats_fs fs: virtual fs to show stats to the end-user
  kvm_main: replace debugfs with stats_fs
  [not for merge] kvm: example of stats_fs_value show function
  [not for merge] netstats: example use of stats_fs API

 Documentation/filesystems/index.rst    |    1 +
 Documentation/filesystems/stats_fs.rst |  222 +++++
 MAINTAINERS                            |    7 +
 arch/arm64/kvm/Kconfig                 |    1 +
 arch/arm64/kvm/guest.c                 |    2 +-
 arch/mips/kvm/Kconfig                  |    1 +
 arch/mips/kvm/mips.c                   |    2 +-
 arch/powerpc/kvm/Kconfig               |    1 +
 arch/powerpc/kvm/book3s.c              |   12 +-
 arch/powerpc/kvm/booke.c               |    8 +-
 arch/s390/kvm/Kconfig                  |    1 +
 arch/s390/kvm/kvm-s390.c               |   16 +-
 arch/x86/include/asm/kvm_host.h        |    2 +-
 arch/x86/kvm/Kconfig                   |    1 +
 arch/x86/kvm/Makefile                  |    2 +-
 arch/x86/kvm/debugfs.c                 |   64 --
 arch/x86/kvm/stats_fs.c                |  114 +++
 arch/x86/kvm/x86.c                     |   11 +-
 fs/Kconfig                             |   20 +
 fs/Makefile                            |    1 +
 fs/stats_fs/Makefile                   |    7 +
 fs/stats_fs/inode.c                    |  461 ++++++++++
 fs/stats_fs/internal.h                 |   34 +
 fs/stats_fs/stats_fs-tests.c           | 1097 ++++++++++++++++++++++++
 fs/stats_fs/stats_fs.c                 |  642 ++++++++++++++
 fs/stats_fs/stub.c                     |   13 +
 include/linux/kvm_host.h               |   45 +-
 include/linux/netdevice.h              |    2 +
 include/linux/stats_fs.h               |  381 ++++++++
 include/uapi/linux/magic.h             |    1 +
 net/Kconfig                            |    1 +
 net/core/dev.c                         |   68 ++
 tools/lib/api/fs/fs.c                  |   21 +
 virt/kvm/arm/arm.c                     |    2 +-
 virt/kvm/kvm_main.c                    |  317 +------
 35 files changed, 3193 insertions(+), 388 deletions(-)
 create mode 100644 Documentation/filesystems/stats_fs.rst
 delete mode 100644 arch/x86/kvm/debugfs.c
 create mode 100644 arch/x86/kvm/stats_fs.c
 create mode 100644 fs/stats_fs/Makefile
 create mode 100644 fs/stats_fs/inode.c
 create mode 100644 fs/stats_fs/internal.h
 create mode 100644 fs/stats_fs/stats_fs-tests.c
 create mode 100644 fs/stats_fs/stats_fs.c
 create mode 100644 fs/stats_fs/stub.c
 create mode 100644 include/linux/stats_fs.h
```
#### [PATCH v2 00/28] KVM: nSVM: event fixes and migration support
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
From patchwork Tue May 26 17:22:40 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11570899
Return-Path: <SRS0=g4lY=7I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 43AAB60D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 26 May 2020 17:23:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2823720823
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 26 May 2020 17:23:17 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="UtbtMzCf"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388896AbgEZRXO (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 26 May 2020 13:23:14 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:34437 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S2388740AbgEZRXO (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 26 May 2020 13:23:14 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1590513792;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=PT+9sIc45kDpdRXOEm8Xg9MAFO/U8LI2utirVVEKJpA=;
        b=UtbtMzCf/GlpWZvKAeIx2YBa/y6AOO88GH/AsSKC6al5qgINlkBYl2HhyU+YEv/eF3FUqN
        d0kNPD+SbfEwDTn4q3GYdUwoPpPhixNtPnYmCscgm5+rrbuc4vjj2psxUOaqhQW1FlaYKR
        NFEZBmM592Bpow2omBRwYgoJlrMY44A=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-235-lZL-I7WRM1i5yn5yU8gw6w-1; Tue, 26 May 2020 13:23:11 -0400
X-MC-Unique: lZL-I7WRM1i5yn5yU8gw6w-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 82845108BD0B;
        Tue, 26 May 2020 17:23:09 +0000 (UTC)
Received: from virtlab511.virt.lab.eng.bos.redhat.com
 (virtlab511.virt.lab.eng.bos.redhat.com [10.19.152.198])
        by smtp.corp.redhat.com (Postfix) with ESMTP id E5C321001B07;
        Tue, 26 May 2020 17:23:08 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: vkuznets@redhat.com, mlevitsk@redhat.com,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Jim Mattson <jmattson@google.com>
Subject: [PATCH v2 00/28] KVM: nSVM: event fixes and migration support
Date: Tue, 26 May 2020 13:22:40 -0400
Message-Id: <20200526172308.111575-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Compared to v1, this fixes some incorrect injections of VINTR that happen
on kvm/queue while running nested guests, and it clarifies the code
that handles INT_CTL.  The most important part here is the first three
patches, which further cleanup event injection and remove another race
between inject_pending_event and kvm_cpu_has_injectable_intr.

Two other important patches are "KVM: nSVM: restore clobbered INT_CTL
fields after clearing VINTR" and "KVM: nSVM: synthesize correct EXITINTINFO
on vmexit", which fix various hangs that were happening with v1.

Nested Hyper-V is still broken with these patches; the bug is only
marginally related to event injection and the fix is simple, so it can
go into 5.7.  And it's Vitaly who heroically debugged it, so I'll leave
it to him to post it.

Paolo

Paolo Bonzini (28):
  KVM: x86: track manually whether an event has been injected
  KVM: x86: enable event window in inject_pending_event
  KVM: nSVM: inject exceptions via svm_check_nested_events
  KVM: nSVM: remove exit_required
  KVM: nSVM: correctly inject INIT vmexits
  KVM: SVM: always update CR3 in VMCB
  KVM: nVMX: always update CR3 in VMCS
  KVM: nSVM: move map argument out of enter_svm_guest_mode
  KVM: nSVM: extract load_nested_vmcb_control
  KVM: nSVM: extract preparation of VMCB for nested run
  KVM: nSVM: move MMU setup to nested_prepare_vmcb_control
  KVM: nSVM: clean up tsc_offset update
  KVM: nSVM: pass vmcb_control_area to copy_vmcb_control_area
  KVM: nSVM: remove trailing padding for struct vmcb_control_area
  KVM: nSVM: save all control fields in svm->nested
  KVM: nSVM: restore clobbered INT_CTL fields after clearing VINTR
  KVM: nSVM: synchronize VMCB controls updated by the processor on every
    vmexit
  KVM: nSVM: remove unnecessary if
  KVM: nSVM: extract svm_set_gif
  KVM: SVM: preserve VGIF across VMCB switch
  KVM: nSVM: synthesize correct EXITINTINFO on vmexit
  KVM: nSVM: remove HF_VINTR_MASK
  KVM: nSVM: remove HF_HIF_MASK
  KVM: nSVM: split nested_vmcb_check_controls
  KVM: nSVM: leave guest mode when clearing EFER.SVME
  KVM: MMU: pass arbitrary CR0/CR4/EFER to kvm_init_shadow_mmu
  selftests: kvm: add a SVM version of state-test
  KVM: nSVM: implement KVM_GET_NESTED_STATE and KVM_SET_NESTED_STATE

 arch/x86/include/asm/kvm_host.h               |  12 +-
 arch/x86/include/asm/svm.h                    |   9 +-
 arch/x86/include/uapi/asm/kvm.h               |  17 +-
 arch/x86/kvm/cpuid.h                          |   5 +
 arch/x86/kvm/irq.c                            |   1 +
 arch/x86/kvm/mmu.h                            |   2 +-
 arch/x86/kvm/mmu/mmu.c                        |  14 +-
 arch/x86/kvm/svm/nested.c                     | 624 ++++++++++++------
 arch/x86/kvm/svm/svm.c                        | 154 ++---
 arch/x86/kvm/svm/svm.h                        |  33 +-
 arch/x86/kvm/vmx/nested.c                     |   5 -
 arch/x86/kvm/vmx/vmx.c                        |  25 +-
 arch/x86/kvm/x86.c                            | 141 ++--
 .../testing/selftests/kvm/x86_64/state_test.c |  69 +-
 14 files changed, 687 insertions(+), 424 deletions(-)
```
#### [PATCH  0/2 v5] Fix VMX preemption timer migration
##### From: Makarand Sonare <makarandsonare@google.com>

```c
From patchwork Tue May 26 21:51:05 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Makarand Sonare <makarandsonare@google.com>
X-Patchwork-Id: 11571411
Return-Path: <SRS0=g4lY=7I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9717A92A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 26 May 2020 21:51:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7542020888
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 26 May 2020 21:51:17 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="rxbbGFmW"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2389134AbgEZVvQ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 26 May 2020 17:51:16 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:59468 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726858AbgEZVvQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 26 May 2020 17:51:16 -0400
Received: from mail-qt1-x84a.google.com (mail-qt1-x84a.google.com
 [IPv6:2607:f8b0:4864:20::84a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id B2E56C061A0F
        for <kvm@vger.kernel.org>; Tue, 26 May 2020 14:51:14 -0700 (PDT)
Received: by mail-qt1-x84a.google.com with SMTP id v17so23791042qtp.15
        for <kvm@vger.kernel.org>; Tue, 26 May 2020 14:51:14 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=JsFe+N5Crx7S9HTSKTOSQGE2yny3voXAyrEiokfM1es=;
        b=rxbbGFmWtMHoEZjKVc6p7rFGdNaP84+QznsSghpEjm2PqUxGPsTMMLY1d8tlFu/3nO
         C5LDMn8Pe+ytAIqrRl/SIEc7ZOXFQGTtuAaybM8hiwlwRHD9A7bvDIJBU0m9EloJzDxh
         Qxu+l9a/UzvoEvHcddUZcWIG5ea3oSfKD2ikZn72T2+dSw9pToFOmD/dzk0ROHRyQ55/
         8cNgAJjElYIsqMyynpofx7BiiznwXfRTBYDlu2GP427HNFb48mKkwHP2SP2lFsU0Hth3
         3uhjjMsZU/fk02SU4YHJu5nYgBPCvWttLvCew90fCUJmlf8VOOtKaCeTmNjcQEhqO79r
         TlYQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=JsFe+N5Crx7S9HTSKTOSQGE2yny3voXAyrEiokfM1es=;
        b=CksIy+fFI2JLkb0mPUGpZ5dN+MNTNDnBt641lw7SYooMD5KIaQZAknNAUYMb3Jd3SF
         bwMI8feONgrGW//gyWNRwgrddiywlO5C4KhoagZ/VskAeQ/j+Oz0XE+4yJ6jv+eeyv9+
         nFYnhOywxuD+n56u2RabJHovPGt24p3vuCh/t4VxZ1wVKboU1q0j4OhrBVaAZl61yzn5
         waWaiQqb+QS8usCY+KJcNrKPU5XSQ/EOzvqHgnnY0u1QzxRGuOT5UIaQO3sMKt3X2/FC
         DBH6TIJRmkCEd5L7St0goTY8n+HjaROYumBALAVeWDHV0uAwDoOk0De1e3VYQ3B0v/aP
         JYDg==
X-Gm-Message-State: AOAM531GMiRT3v/96XoWMMe+i52wo291Nk9Y/vbiMjNLbuWt0EkHDe0q
        aativkLHdkw4VapaAPfW4fbnjn1Y2XxfxXiMUs6Hfj0JZY7SsvWwzFljAO7CK1VjfWTuRn+/t98
        qhVPHBAXoGtAC/6ZjU1/qDTPSLoXiB9JOu45FtpPJw9oQoOPRSCHYyn+/ewf9oBFnqVYgIt7zja
        B9aVE=
X-Google-Smtp-Source: 
 ABdhPJw3F8D4hE0oOF5Ut/M9pHPdbBMl7IcEA5edpRf+JFo1cn9T6X+oRXja4Ve42BOWl6cQCMpBxOmKlB9yg2qQVjUw2g==
X-Received: by 2002:a0c:8482:: with SMTP id m2mr12650359qva.65.1590529873579;
 Tue, 26 May 2020 14:51:13 -0700 (PDT)
Date: Tue, 26 May 2020 14:51:05 -0700
Message-Id: <20200526215107.205814-1-makarandsonare@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.27.0.rc0.183.gde8f92d652-goog
Subject: [PATCH  0/2 v5] Fix VMX preemption timer migration
From: Makarand Sonare <makarandsonare@google.com>
To: kvm@vger.kernel.org, pshier@google.com, jmattson@google.com
Cc: Makarand Sonare <makarandsonare@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

v4: Renamed flag to KVM_STATE_VMX_PREEMPTION_TIMER_DEADLINE
    and removed the KVM_CAP_NESTED_STATE_PREEMPTION_TIMER check [Paolo]

Makarand Sonare (1):
  KVM: selftests: VMX preemption timer migration test

Peter Shier (1):
  KVM: nVMX: Fix VMX preemption timer migration

 Documentation/virt/kvm/api.rst                |   4 +
 arch/x86/include/uapi/asm/kvm.h               |   4 +
 arch/x86/kvm/vmx/nested.c                     |  55 +++-
 arch/x86/kvm/vmx/vmx.h                        |   2 +
 tools/arch/x86/include/uapi/asm/kvm.h         |   1 +
 tools/testing/selftests/kvm/.gitignore        |   1 +
 tools/testing/selftests/kvm/Makefile          |   1 +
 .../testing/selftests/kvm/include/kvm_util.h  |   2 +
 .../selftests/kvm/include/x86_64/processor.h  |  11 +-
 .../selftests/kvm/include/x86_64/vmx.h        |  27 ++
 .../kvm/x86_64/vmx_preemption_timer_test.c    | 255 ++++++++++++++++++
 11 files changed, 351 insertions(+), 12 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/x86_64/vmx_preemption_timer_test.c
---
2.27.0.rc0.183.gde8f92d652-goog
```
