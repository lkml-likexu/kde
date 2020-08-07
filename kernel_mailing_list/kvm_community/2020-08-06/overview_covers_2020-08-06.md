

#### [RFC PATCH 0/7] metricfs metric file system and examples
##### From: Jonathan Adams <jwadams@google.com>

```c
From patchwork Thu Aug  6 00:14:24 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jonathan Adams <jwadams@google.com>
X-Patchwork-Id: 11702607
Return-Path: <SRS0=LWg4=BQ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2025A1731
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  6 Aug 2020 00:14:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0C6B722CAE
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  6 Aug 2020 00:14:59 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="oGOu/f1T"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726490AbgHFAOm (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 5 Aug 2020 20:14:42 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:59740 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725779AbgHFAOj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 5 Aug 2020 20:14:39 -0400
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 2E5CDC061574
        for <kvm@vger.kernel.org>; Wed,  5 Aug 2020 17:14:38 -0700 (PDT)
Received: by mail-yb1-xb4a.google.com with SMTP id d26so26401163yba.20
        for <kvm@vger.kernel.org>; Wed, 05 Aug 2020 17:14:38 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=ukHjjWs5WkFtiIo1+uIoaJAHaeV1zsDQLFHCLViDx9A=;
        b=oGOu/f1TAJ6j3p+WWvzitUIbdLGn8Duqb+dycILCf+u/HF87ubz84dGBN4tweHZLK4
         u/azbVeHevh0sZ2wvJIpoDUl/qrx1n/IIVR/aq/ZlkleDhpHq+2TlAD1oaDS/XCiwPdw
         mD5Ep+zfU/1V/JtWSuHyz6kyo1/PLM/D0Hg5nVGQMe9w7ooe/FVBa5bWyWF4EIHusdt1
         ru01c0Yjlkv9p7b29FLi872xUBhf7Ee67Lks1XzQk7qpNBeyUKhv8W/OKZhKdtNHijut
         vpqf7Pxm266TabuQLpw+zirpX3jIUfrWH5do9jKQKAqdILOUSvFPmP5Ta5WC1kjLhpea
         1Meg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=ukHjjWs5WkFtiIo1+uIoaJAHaeV1zsDQLFHCLViDx9A=;
        b=IdRf50jPS1QhlbP6RSXnZUfuxdpy7AkbH5sq+WqsDvWDddxZ9rWCtlZSPxJHStS2ZB
         lvabfcErR2JyZWdnH5EKzx6klRyy2zEV/56WKmym4wNS1xcH3qLR8vLHq1N3EuwsU16k
         GXxy9HN5ZJQ6JWkQk/Av4NhnnlMLA6TGaY54YqN+Y2OntXuRSxAiLjXEP9u7JMKq/7A7
         zdFq3am8nqZti8M3rHawBECs1eawzIVAQR/5hnkbwAy0RywX+n50cY2KHQwmIlvGCkY4
         ipFiq+BDHm3o0GUcmPUvggVywdDZYuOYqgzvED9Bjmv3APNfLLv/jmAZO462HnlYDKBv
         +h9w==
X-Gm-Message-State: AOAM533gDrAwCm5iEZL8D8y13ZuN6YWUmEKHnl1x0MAy4hdgSlwkz5E5
        piVIS8BdMtpP8xjpYvkdOt3r09eU1EY=
X-Google-Smtp-Source: 
 ABdhPJx+cPe/ZfGxzR9zdfhIWm8DUg/eVg2ptgtOtQPOFUmRpLc+elP5rUSmOj2N95q5WLDf+3HcontyW5cD
X-Received: by 2002:a25:cf95:: with SMTP id
 f143mr7894705ybg.126.1596672877936;
 Wed, 05 Aug 2020 17:14:37 -0700 (PDT)
Date: Wed,  5 Aug 2020 17:14:24 -0700
Message-Id: <20200806001431.2072150-1-jwadams@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.28.0.236.gb10cc79966-goog
Subject: [RFC PATCH 0/7] metricfs metric file system and examples
From: Jonathan Adams <jwadams@google.com>
To: linux-kernel@vger.kernel.org
Cc: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        David Rientjes <rientjes@google.com>,
        Jonathan Adams <jwadams@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

To try to restart the discussion of kernel statistics started by the
statsfs patchsets (https://lkml.org/lkml/2020/5/26/332), I wanted
to share the following set of patches which are Google's 'metricfs'
implementation and some example uses.  Google has been using metricfs
internally since 2012 as a way to export various statistics to our
telemetry systems (similar to OpenTelemetry), and we have over 200
statistics exported on a typical machine.

These patches have been cleaned up and modernized v.s. the versions
in production; I've included notes under the fold in the patches.
They're based on v5.8-rc6.

The statistics live under debugfs, in a tree rooted at:

	/sys/kernel/debug/metricfs

Each metric is a directory, with four files in it.  For example, the '
core/metricfs: Create metricfs, standardized files under debugfs.' patch
includes a simple 'metricfs_presence' metric, whose files look like:
/sys/kernel/debug/metricfs:
 metricfs_presence/annotations
  DESCRIPTION A\ basic\ presence\ metric.
 metricfs_presence/fields
  value
  int
 metricfs_presence/values
  1
 metricfs_presence/version
  1

(The "version" field always says '1', and is kind of vestigial)

An example of a more complicated stat is the networking stats.
For example, the tx_bytes stat looks like:

net/dev/stats/tx_bytes/annotations
  DESCRIPTION net\ device\ transmited\ bytes\ count
  CUMULATIVE
net/dev/stats/tx_bytes/fields
  interface value
  str int
net/dev/stats/tx_bytes/values
  lo 4394430608
  eth0 33353183843
  eth1 16228847091
net/dev/stats/tx_bytes/version
  1

The per-cpu statistics show up in the schedulat stat info and x86
IRQ counts.  For example:

stat/user/annotations
  DESCRIPTION time\ in\ user\ mode\ (nsec)
  CUMULATIVE
stat/user/fields
  cpu value
  int int
stat/user/values
  0 1183486517734
  1 1038284237228
  ...
stat/user/version
  1

The full set of example metrics I've included are:

core/metricfs: Create metricfs, standardized files under debugfs.
  metricfs_presence
core/metricfs: metric for kernel warnings
  warnings/values
core/metricfs: expose scheduler stat information through metricfs
  stat/*
net-metricfs: Export /proc/net/dev via metricfs.
  net/dev/stats/[tr]x_*
core/metricfs: expose x86-specific irq information through metricfs
  irq_x86/*

The general approach is called out in kernel/metricfs.c:

The kernel provides:
  - A description of the metric
  - The subsystem for the metric (NULL is ok)
  - Type information about the metric, and
  - A callback function which supplies metric values.

Limitations:
  - "values" files are at MOST 64K. We truncate the file at that point.
  - The list of fields and types is at most 1K.
  - Metrics may have at most 2 fields.

Best Practices:
  - Emit the most important data first! Once the 64K per-metric buffer
    is full, the emit* functions won't do anything.
  - In userspace, open(), read(), and close() the file quickly! The kernel
    allocation for the metric is alive as long as the file is open. This
    permits users to seek around the contents of the file, while
    permitting an atomic view of the data.

Note that since the callbacks are called and the data is generated at
file open() time, the relative consistency is only between members of
a given metric; the rx_bytes stat for every network interface will
be read at almost the same time, but if you want to get rx_bytes
and rx_packets, there could be a bunch of slew between the two file
opens.  (So this doesn't entirely address Andrew Lunn's comments in
https://lkml.org/lkml/2020/5/26/490)

This also doesn't address one of the basic parts of the statsfs work:
moving the statistics out of debugfs to avoid lockdown interactions.

Google has found a lot of value in having a generic interface for adding
these kinds of statistics with reasonably low overhead (reading them
is O(number of statistics), not number of objects in each statistic).
There are definitely warts in the interface, but does the basic approach
make sense to folks?

Thanks,
- Jonathan

Jonathan Adams (5):
  core/metricfs: add support for percpu metricfs files
  core/metricfs: metric for kernel warnings
  core/metricfs: expose softirq information through metricfs
  core/metricfs: expose scheduler stat information through metricfs
  core/metricfs: expose x86-specific irq information through metricfs

Justin TerAvest (1):
  core/metricfs: Create metricfs, standardized files under debugfs.

Laurent Chavey (1):
  net-metricfs: Export /proc/net/dev via metricfs.

 arch/x86/kernel/irq.c      |  80 ++++
 fs/proc/stat.c             |  57 +++
 include/linux/metricfs.h   | 131 +++++++
 kernel/Makefile            |   2 +
 kernel/metricfs.c          | 775 +++++++++++++++++++++++++++++++++++++
 kernel/metricfs_examples.c | 151 ++++++++
 kernel/panic.c             | 131 +++++++
 kernel/softirq.c           |  45 +++
 lib/Kconfig.debug          |  18 +
 net/core/Makefile          |   1 +
 net/core/net_metricfs.c    | 194 ++++++++++
 11 files changed, 1585 insertions(+)
 create mode 100644 include/linux/metricfs.h
 create mode 100644 kernel/metricfs.c
 create mode 100644 kernel/metricfs_examples.c
 create mode 100644 net/core/net_metricfs.c
```
#### [PATCH v3 0/4] Restrict PV features to only enabled guests
##### From: Oliver Upton <oupton@google.com>

```c
From patchwork Thu Aug  6 15:14:29 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Oliver Upton <oupton@google.com>
X-Patchwork-Id: 11703493
Return-Path: <SRS0=LWg4=BQ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2A7C41392
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  6 Aug 2020 16:32:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7C494204FD
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  6 Aug 2020 16:32:08 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="W05t8l8x"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727103AbgHFQcE (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 6 Aug 2020 12:32:04 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:40150 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728271AbgHFQbD (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 6 Aug 2020 12:31:03 -0400
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id A3559C0086D4
        for <kvm@vger.kernel.org>; Thu,  6 Aug 2020 08:14:37 -0700 (PDT)
Received: by mail-yb1-xb49.google.com with SMTP id n21so41918646ybf.18
        for <kvm@vger.kernel.org>; Thu, 06 Aug 2020 08:14:37 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=tlp9q0ruYxUy6K1Wv14LOld0/f3sQOHJP7F2snACgNU=;
        b=W05t8l8xySwHgO0u+OSgCEVI3iDQiF56QlWJqJaodjlhjBda9AFua7Tx5Dj44UGd5v
         PuJkTUdNO+OhFKmcFWbAT/+ysNG7J+JT+BAnUQqr4mlC9LWyBNlDOeEMFVGl5v6SOcCt
         ZKvqgS6U+Hp/laLUDEezpru2ftsJ/GW/kaMdAJjgxYpk1rIM/c1azH5Wf/ey/phx6tI4
         mlv+sMXvawAP4v9rzpyMgKCyF1pUTJlZqXzjyQ0fAov/jSZoW1vDhTeVychMw9vT9esU
         v2R8ARKFqvLr0nyWXlCBoK9HHiCfivAoB+/LzQHa19Zemfs1A3B4pYuF8p5BYRhGzi39
         9A4w==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=tlp9q0ruYxUy6K1Wv14LOld0/f3sQOHJP7F2snACgNU=;
        b=j7NLAL+bwBrvoadTfBVKCuGDdHN+HRbcMp40QSmEs69cReCDQ8x73DniLx2Fucugui
         YCmDZYF4ioiNdexH0I5InPW+sEKx4i7wZvn5KMtojMuRVqwoqzaKsxPbgFaWbDTJ0cdU
         EdCyLSMQ1K1gE4mO8pnbj7krHG7S9fJOAE70HCdG6OFOG9JJnvv5+FwbhxycFfp9+LSO
         73HnFGawCqFVM46YnVNpIczambTp0K6MdYZDkvzpJXsFYdINXCvR1s42e4k3eORE5tjJ
         luTYoifQZEPxHwiRD1qnQvN/p+r7slAMLpTjgXb4+m7/pDsNy2/RvdmWRq09ZrGy8JKi
         kyXA==
X-Gm-Message-State: AOAM530wh1n3UTKIbjDTrifyG7aBWDgEGmpRuIX1lLNOLH11fNXphG9H
        y7dTMQVlCHZnBq79w8ytyWatrDxH2gTnbVnYpKqURjP0rRqYjyN+lAzG4R2sdqKpvbpOuevDTzF
        hM7goZHkYL+hxnbn/g3Ekc1IqQrq5DkjDYwjC6icLRbXv6RQpn3dehtseVQ==
X-Google-Smtp-Source: 
 ABdhPJyTK2QJ9GYTipDG3/WDK2rWv1Dn7ftTBrUYTRW1u8l701qwRaDHfnsbB/BPZHhU0nxZVFxPBpDrpSY=
X-Received: by 2002:a25:2314:: with SMTP id
 j20mr13312806ybj.508.1596726876527;
 Thu, 06 Aug 2020 08:14:36 -0700 (PDT)
Date: Thu,  6 Aug 2020 15:14:29 +0000
Message-Id: <20200806151433.2747952-1-oupton@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.28.0.236.gb10cc79966-goog
Subject: [PATCH v3 0/4] Restrict PV features to only enabled guests
From: Oliver Upton <oupton@google.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Oliver Upton <oupton@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

To date, KVM has allowed guests to use paravirtual interfaces regardless
of the configured CPUID. While almost any guest will consult the
KVM_CPUID_FEATURES leaf _before_ using PV features, it is still
undesirable to have such interfaces silently present.

This series aims to address the issue by adding explicit checks against
the guest's CPUID when servicing any paravirtual feature. Since this
effectively changes the guest/hypervisor ABI, a KVM_CAP is warranted to
guard the new behavior.

Patches 1-2 refactor some of the PV code in anticipation of the change.
Patch 3 introduces the checks + KVM_CAP. Finally, patch 4 fixes some doc
typos that were noticed when working on this series.

v1 => v2:
 - Strip Change-Id footers (checkpatch is your friend!)

v2 => v3:
 - Mark kvm_write_system_time() as static

Parent commit: f3633c268354 ("Merge tag 'kvm-s390-next-5.9-1' of git://git.kernel.org/pub/scm/linux/kernel/git/kvms390/linux into kvm-next-5.6")

Oliver Upton (4):
  kvm: x86: encapsulate wrmsr(MSR_KVM_SYSTEM_TIME) emulation in helper
    fn
  kvm: x86: set wall_clock in kvm_write_wall_clock()
  kvm: x86: only provide PV features if enabled in guest's CPUID
  Documentation: kvm: fix some typos in cpuid.rst

 Documentation/virt/kvm/api.rst   |  11 +++
 Documentation/virt/kvm/cpuid.rst |  88 +++++++++++-----------
 arch/x86/include/asm/kvm_host.h  |   6 ++
 arch/x86/kvm/cpuid.h             |  16 ++++
 arch/x86/kvm/x86.c               | 122 +++++++++++++++++++++++--------
 include/uapi/linux/kvm.h         |   1 +
 6 files changed, 171 insertions(+), 73 deletions(-)
```
#### [kvm-unit-tests PATCH 0/3] x86: Add guest physical bits tests
##### From: Mohammed Gamal <mgamal@redhat.com>

```c
From patchwork Thu Aug  6 12:43:55 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Mohammed Gamal <mgamal@redhat.com>
X-Patchwork-Id: 11703671
Return-Path: <SRS0=LWg4=BQ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8AB9C138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  6 Aug 2020 17:22:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E69102312E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  6 Aug 2020 17:22:44 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="BWcz/RKu"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729896AbgHFRP3 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 6 Aug 2020 13:15:29 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:36429 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1730259AbgHFRPZ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 6 Aug 2020 13:15:25 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1596734119;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=qmd9lA9V2WmAck1ZMV5IDD4q2AP3yXBJ6bMUOiVD5uI=;
        b=BWcz/RKuFOJf/sXrHyD8waAr/wpfp+449wNTo1OU8LC7Q5ju+sJnPvooeLXBO994LBXtkR
        LpRLZPi38RHBP2Gdy2gzMeDwx+a/fdvnPS7j+sdK9GcEaeywrHj0PKclT9m/t8z4aJDxoC
        pmkU2RQpcZ48dC2Lz1jDEl0DqKTux20=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-291-v-66GkEwOIScLzrzmawPAw-1; Thu, 06 Aug 2020 08:44:18 -0400
X-MC-Unique: v-66GkEwOIScLzrzmawPAw-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 1764E52AB7
        for <kvm@vger.kernel.org>; Thu,  6 Aug 2020 12:44:08 +0000 (UTC)
Received: from localhost.localdomain.com (ovpn-114-17.ams2.redhat.com
 [10.36.114.17])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 429F65C1BD;
        Thu,  6 Aug 2020 12:44:03 +0000 (UTC)
From: Mohammed Gamal <mgamal@redhat.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com
Cc: Mohammed Gamal <mgamal@redhat.com>
Subject: [kvm-unit-tests PATCH 0/3] x86: Add guest physical bits tests
Date: Thu,  6 Aug 2020 14:43:55 +0200
Message-Id: <20200806124358.4928-1-mgamal@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch series re-enables the guest physical bits tests, in addition
timeouts are also tweaked for AMD without NPT enabled, and the tests are
also disabled on AMD with NPT enabled, since we aren't able to support them
properly due to the way CPUs set PTE bits on NPT VM exits

Mohammed Gamal (3):
  unittests.cfg: Increase timeout for access test
  x86/access: Skip running guest physical bits tests on AMD with NPT
    enabled
  Revert "access: disable phys-bits=36 for now"

 x86/access.c      | 8 ++++++++
 x86/unittests.cfg | 3 ++-
 2 files changed, 10 insertions(+), 1 deletion(-)
```
#### [PATCH v1 0/1] s390: virtio-ccw: PV needs VIRTIO I/O device
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
From patchwork Thu Aug  6 14:23:01 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 11703675
Return-Path: <SRS0=LWg4=BQ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A6099138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  6 Aug 2020 17:24:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 17E1323120
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  6 Aug 2020 17:24:02 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="XogXsXMR"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727971AbgHFRXc (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 6 Aug 2020 13:23:32 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:26028 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1729955AbgHFRE5 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 6 Aug 2020 13:04:57 -0400
Received: from pps.filterd (m0098399.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 076E4BLq037516;
        Thu, 6 Aug 2020 10:23:10 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id; s=pp1;
 bh=kmhmWCdm048zOKwXHN42FLNuOm7WrXWJMfUPgkm2BNs=;
 b=XogXsXMRXlfm/JAY1LPooBLT63IRYCp8ojV2ctAf3lkvx5Vw9iebfbHieezthAQNC8c0
 /b1g87Yz1d4zB3k1WmuW66G9PU53U8W4EKMQAt7AIgCI/psb/OtVEE/vgSFef0buG0Z7
 JYYwr4i98hQQjP4LOaXvML4fgtZAkymKXVkOEnyDvVVF2gFiGNfUIeZK/XEjsOlO4vj2
 JabFvOzanHZCzsGRQ9PzVHJrSjmUeuJaEAN0xISsn+fffwArKOrYc5vb2gWSAF6EBLid
 tAJK30i6TKzf/UYtYNXDr7tiutyamSPYWlkM7VKb4hqRKBliSIvFSDVr+n1qfByVXcpS JA==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 32rgnf5y0j-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 06 Aug 2020 10:23:10 -0400
Received: from m0098399.ppops.net (m0098399.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 076E4iXH040969;
        Thu, 6 Aug 2020 10:23:10 -0400
Received: from ppma03ams.nl.ibm.com (62.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.98])
        by mx0a-001b2d01.pphosted.com with ESMTP id 32rgnf5xyj-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 06 Aug 2020 10:23:10 -0400
Received: from pps.filterd (ppma03ams.nl.ibm.com [127.0.0.1])
        by ppma03ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 076EF6Jl029907;
        Thu, 6 Aug 2020 14:23:07 GMT
Received: from b06cxnps4074.portsmouth.uk.ibm.com
 (d06relay11.portsmouth.uk.ibm.com [9.149.109.196])
        by ppma03ams.nl.ibm.com with ESMTP id 32n0185j5x-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 06 Aug 2020 14:23:07 +0000
Received: from d06av26.portsmouth.uk.ibm.com (d06av26.portsmouth.uk.ibm.com
 [9.149.105.62])
        by b06cxnps4074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 076EN48J16253204
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 6 Aug 2020 14:23:05 GMT
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id CAB55AE059;
        Thu,  6 Aug 2020 14:23:04 +0000 (GMT)
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 541CFAE04D;
        Thu,  6 Aug 2020 14:23:04 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.149.70])
        by d06av26.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Thu,  6 Aug 2020 14:23:04 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: linux-kernel@vger.kernel.org
Cc: pasic@linux.ibm.com, borntraeger@de.ibm.com, frankja@linux.ibm.com,
        mst@redhat.com, jasowang@redhat.com, cohuck@redhat.com,
        kvm@vger.kernel.org, linux-s390@vger.kernel.org,
        virtualization@lists.linux-foundation.org
Subject: [PATCH v1 0/1] s390: virtio-ccw: PV needs VIRTIO I/O device
 protection
Date: Thu,  6 Aug 2020 16:23:01 +0200
Message-Id: <1596723782-12798-1-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-08-06_09:2020-08-06,2020-08-06 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 spamscore=0
 priorityscore=1501 mlxlogscore=999 malwarescore=0 adultscore=0 mlxscore=0
 phishscore=0 suspectscore=1 clxscore=1015 impostorscore=0 bulkscore=0
 lowpriorityscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2008060099
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all,

In another series I proposed to add an architecture specific
callback to fail feature negociation on architecture need.

In VIRTIO, we already have an entry to reject the features on the
transport basis.

Transport is not architecture so I send a separate series in which
we fail the feature negociation inside virtio_ccw_finalize_features,
the virtio_config_ops.finalize_features for S390 CCW transport,
when the device do not propose the VIRTIO_F_IOMMU_PLATFORM.

This solves the problem of crashing QEMU when this one is not using
a CCW device with iommu_platform=on in S390.

Regards,
Pierre

Regards,
Pierre

Pierre Morel (1):
  s390: virtio-ccw: PV needs VIRTIO I/O device protection

 drivers/s390/virtio/virtio_ccw.c | 24 +++++++++++++++++++-----
 1 file changed, 19 insertions(+), 5 deletions(-)
```
