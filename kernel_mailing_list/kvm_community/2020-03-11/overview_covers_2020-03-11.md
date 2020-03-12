

#### [PATCH 0/2] format string fixups for selftests
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
From patchwork Wed Mar 11 13:10:54 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11431705
Return-Path: <SRS0=PMbP=44=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6348817D5
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Mar 2020 13:11:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4CCE12253D
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Mar 2020 13:11:06 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729447AbgCKNLF (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 11 Mar 2020 09:11:05 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:10634 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1729232AbgCKNLF (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 11 Mar 2020 09:11:05 -0400
Received: from pps.filterd (m0098417.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 02BD1Iv9111135
        for <kvm@vger.kernel.org>; Wed, 11 Mar 2020 09:11:03 -0400
Received: from e06smtp02.uk.ibm.com (e06smtp02.uk.ibm.com [195.75.94.98])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2ypyu1k31n-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Wed, 11 Mar 2020 09:11:03 -0400
Received: from localhost
        by e06smtp02.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <borntraeger@de.ibm.com>;
        Wed, 11 Mar 2020 13:11:01 -0000
Received: from b06cxnps4074.portsmouth.uk.ibm.com (9.149.109.196)
        by e06smtp02.uk.ibm.com (192.168.101.132) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Wed, 11 Mar 2020 13:10:58 -0000
Received: from d06av26.portsmouth.uk.ibm.com (d06av26.portsmouth.uk.ibm.com
 [9.149.105.62])
        by b06cxnps4074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 02BDAvPf53346402
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 11 Mar 2020 13:10:57 GMT
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 4A4F1AE058;
        Wed, 11 Mar 2020 13:10:57 +0000 (GMT)
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 39011AE056;
        Wed, 11 Mar 2020 13:10:57 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av26.portsmouth.uk.ibm.com (Postfix) with ESMTPS;
        Wed, 11 Mar 2020 13:10:57 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 25651)
        id EED45E024B; Wed, 11 Mar 2020 14:10:56 +0100 (CET)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: Janosch Frank <frankja@linux.vnet.ibm.com>
Cc: KVM <kvm@vger.kernel.org>, Cornelia Huck <cohuck@redhat.com>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        David Hildenbrand <david@redhat.com>,
        linux-s390 <linux-s390@vger.kernel.org>,
        Thomas Huth <thuth@redhat.com>,
        Andrew Jones <drjones@redhat.com>
Subject: [PATCH 0/2] format string fixups for selftests
Date: Wed, 11 Mar 2020 14:10:54 +0100
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 20031113-0008-0000-0000-0000035B90A2
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 20031113-0009-0000-0000-00004A7CD746
Message-Id: <20200311131056.140016-1-borntraeger@de.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-03-11_05:2020-03-11,2020-03-11 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxlogscore=860
 lowpriorityscore=0 spamscore=0 mlxscore=0 adultscore=0 priorityscore=1501
 phishscore=0 suspectscore=0 impostorscore=0 clxscore=1015 bulkscore=0
 malwarescore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2001150001 definitions=main-2003110083
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

found by Andrews recent changes so I attributed him as Reported by.

Christian Borntraeger (2):
  selftests: KVM: s390: fixup fprintf format error in reset.c
  selftests: KVM: s390: fix format strings for access reg test

 tools/testing/selftests/kvm/s390x/resets.c         |  2 +-
 tools/testing/selftests/kvm/s390x/sync_regs_test.c | 11 +++++++++--
 2 files changed, 10 insertions(+), 3 deletions(-)
```
#### [kvm-unit-tests PATCH v6 00/13] arm/arm64: Add ITS tests
##### From: Eric Auger <eric.auger@redhat.com>

```c
From patchwork Wed Mar 11 13:51:04 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Auger Eric <eric.auger@redhat.com>
X-Patchwork-Id: 11431797
Return-Path: <SRS0=PMbP=44=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AE630921
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Mar 2020 13:51:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 8B80421D56
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Mar 2020 13:51:35 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="cI991D0m"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729584AbgCKNve (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 11 Mar 2020 09:51:34 -0400
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:51559 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1729473AbgCKNve (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 11 Mar 2020 09:51:34 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1583934693;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=83Q3TmDO8jStqyv9dZqc6/YGFhze/CwItPNxto5n22I=;
        b=cI991D0mNr2iSkOZTQq5aN8KzXxgHYjPkQWABPjgESFhZetfGCLIZb34CzpRk3v+4l7Kk8
        4FPdtxfZofvlvNvU+z6h9xSP9xjRCYLeLtVbCMx403lXZ7QFxME74YeKUnCZ+2oBUtAFFy
        JDz4PhM9WejVMJf0YwolSNDAPUL0DO0=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-415-qw9_DzRtOgStNf1O5sk2wA-1; Wed, 11 Mar 2020 09:51:29 -0400
X-MC-Unique: qw9_DzRtOgStNf1O5sk2wA-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 2D1B88017CC;
        Wed, 11 Mar 2020 13:51:27 +0000 (UTC)
Received: from laptop.redhat.com (unknown [10.36.118.12])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 3E1E592983;
        Wed, 11 Mar 2020 13:51:20 +0000 (UTC)
From: Eric Auger <eric.auger@redhat.com>
To: eric.auger.pro@gmail.com, eric.auger@redhat.com, maz@kernel.org,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        qemu-devel@nongnu.org, qemu-arm@nongnu.org
Cc: drjones@redhat.com, andre.przywara@arm.com,
        peter.maydell@linaro.org, yuzenghui@huawei.com,
        alexandru.elisei@arm.com, thuth@redhat.com
Subject: [kvm-unit-tests PATCH v6 00/13] arm/arm64: Add ITS tests
Date: Wed, 11 Mar 2020 14:51:04 +0100
Message-Id: <20200311135117.9366-1-eric.auger@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
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

The series can be fount at:
https://github.com/eauger/kut/tree/its-v6

Applies on top of arm/queue.

Best Regards

Eric

History:
v5 -> v6:
- Took into account Zenghui's comments, mostly functional: see invidual
  history logs
- fix wrong assert!

v4 -> v5:
- 32b stubs moved back to arm/gic.c
- some changes reordering
- minor style issues

v3 -> v4:
- addressed comments from Drew and Zenghui
- added "page_alloc: Introduce get_order()"
- removed "arm: gic: Provide per-IRQ helper functions"
- ITS files moved to lib64
- and many more, see individual logs

v2 -> v3:
- fix 32b compilation
- take into account Drew's comments (see individual diff logs)

v1 -> v2:
- took into account Zenghui's comments
- collect R-b's from Thomas

References:
[1] [kvm-unit-tests RFC 00/15] arm/arm64: add ITS framework
    https://lists.gnu.org/archive/html/qemu-devel/2016-12/msg00575.html

Execution:
x For other ITS tests:
  ./run_tests.sh -g its

x non migration tests can be launched invidually. For instance:
  ./arm-run arm/gic.flat -smp 8 -append 'its-trigger'

Eric Auger (13):
  libcflat: Add other size defines
  page_alloc: Introduce get_order()
  arm/arm64: gic: Introduce setup_irq() helper
  arm/arm64: gicv3: Add some re-distributor defines
  arm/arm64: gicv3: Set the LPI config and pending tables
  arm/arm64: ITS: Introspection tests
  arm/arm64: ITS: its_enable_defaults
  arm/arm64: ITS: Device and collection Initialization
  arm/arm64: ITS: Commands
  arm/arm64: ITS: INT functional tests
  arm/run: Allow Migration tests
  arm/arm64: ITS: migration tests
  arm/arm64: ITS: pending table migration test

 arm/Makefile.arm64         |   1 +
 arm/Makefile.common        |   2 +-
 arm/gic.c                  | 460 ++++++++++++++++++++++++++++++++++--
 arm/run                    |   2 +-
 arm/unittests.cfg          |  38 +++
 lib/alloc_page.c           |   7 +-
 lib/alloc_page.h           |   1 +
 lib/arm/asm/gic-v3-its.h   |  22 ++
 lib/arm/asm/gic-v3.h       |  29 +++
 lib/arm/asm/processor.h    |   2 +
 lib/arm/gic-v3.c           |  78 +++++++
 lib/arm/gic.c              |  34 ++-
 lib/arm/io.c               |  28 +++
 lib/arm64/asm/gic-v3-its.h | 170 ++++++++++++++
 lib/arm64/gic-v3-its-cmd.c | 464 +++++++++++++++++++++++++++++++++++++
 lib/arm64/gic-v3-its.c     | 172 ++++++++++++++
 lib/libcflat.h             |   3 +
 17 files changed, 1484 insertions(+), 29 deletions(-)
 create mode 100644 lib/arm/asm/gic-v3-its.h
 create mode 100644 lib/arm64/asm/gic-v3-its.h
 create mode 100644 lib/arm64/gic-v3-its-cmd.c
 create mode 100644 lib/arm64/gic-v3-its.c
```
#### [PATCH v2 00/10] virtio-mem: paravirtualized memory
##### From: David Hildenbrand <david@redhat.com>

```c
From patchwork Wed Mar 11 17:14:12 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Hildenbrand <david@redhat.com>
X-Patchwork-Id: 11432299
Return-Path: <SRS0=PMbP=44=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F1CA214B7
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Mar 2020 17:15:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 8292220739
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Mar 2020 17:15:15 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="CWk/ETIG"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730422AbgCKRPM (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 11 Mar 2020 13:15:12 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:42386 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1730351AbgCKRPM (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 11 Mar 2020 13:15:12 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1583946909;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=tltugljWB03t3t9efVxWUD7LJ38gUskpvS9AulZYy0c=;
        b=CWk/ETIGj9QbR5cguM7gQ7IHD/8LZyuStYEAePj61WOsHO1I1iikLn8FaEmRTNDZJlKrIX
        /ZIu9/KiFgduZ6N9J9A9aDu/fmNc+tXdTs0FsK3U9401U+E1MnBnbS2iMq1qwCjratMDGK
        G8d/CqkljJMuJMNzONeqc7ePQsz2QWc=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-411-oK5My588PXuQV5ihCTPzpQ-1; Wed, 11 Mar 2020 13:15:01 -0400
X-MC-Unique: oK5My588PXuQV5ihCTPzpQ-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id B95B98017CC;
        Wed, 11 Mar 2020 17:14:55 +0000 (UTC)
Received: from t480s.redhat.com (ovpn-116-132.ams2.redhat.com [10.36.116.132])
        by smtp.corp.redhat.com (Postfix) with ESMTP id C47CE92F84;
        Wed, 11 Mar 2020 17:14:33 +0000 (UTC)
From: David Hildenbrand <david@redhat.com>
To: linux-kernel@vger.kernel.org
Cc: linux-mm@kvack.org, virtio-dev@lists.oasis-open.org,
        virtualization@lists.linux-foundation.org, kvm@vger.kernel.org,
        Michal Hocko <mhocko@kernel.org>,
        Andrew Morton <akpm@linux-foundation.org>,
        "Michael S . Tsirkin" <mst@redhat.com>,
        David Hildenbrand <david@redhat.com>,
        Sebastien Boeuf <sebastien.boeuf@intel.com>,
        Samuel Ortiz <samuel.ortiz@intel.com>,
        Robert Bradford <robert.bradford@intel.com>,
        Luiz Capitulino <lcapitulino@redhat.com>,
        Pankaj Gupta <pankaj.gupta.linux@gmail.com>,
        teawater <teawaterz@linux.alibaba.com>,
        Igor Mammedov <imammedo@redhat.com>,
        "Dr . David Alan Gilbert" <dgilbert@redhat.com>,
        Alexander Duyck <alexander.h.duyck@linux.intel.com>,
        Alexander Potapenko <glider@google.com>,
        Anshuman Khandual <anshuman.khandual@arm.com>,
        Anthony Yznaga <anthony.yznaga@oracle.com>,
        Dan Williams <dan.j.williams@intel.com>,
        Dave Young <dyoung@redhat.com>,
        Jason Wang <jasowang@redhat.com>,
        Johannes Weiner <hannes@cmpxchg.org>,
        Juergen Gross <jgross@suse.com>,
        Konrad Rzeszutek Wilk <konrad.wilk@oracle.com>,
        Len Brown <lenb@kernel.org>,
        Mel Gorman <mgorman@techsingularity.net>,
        Michal Hocko <mhocko@suse.com>,
        Mike Rapoport <rppt@linux.ibm.com>,
        Oscar Salvador <osalvador@suse.com>,
        Oscar Salvador <osalvador@suse.de>,
        Pavel Tatashin <pasha.tatashin@soleen.com>,
        Pavel Tatashin <pavel.tatashin@microsoft.com>,
        Pingfan Liu <kernelfans@gmail.com>, Qian Cai <cai@lca.pw>,
        "Rafael J. Wysocki" <rafael@kernel.org>,
        "Rafael J. Wysocki" <rjw@rjwysocki.net>,
        Stefan Hajnoczi <stefanha@redhat.com>,
        Vlastimil Babka <vbabka@suse.cz>,
        Wei Yang <richard.weiyang@gmail.com>
Subject: [PATCH v2 00/10] virtio-mem: paravirtualized memory
Date: Wed, 11 Mar 2020 18:14:12 +0100
Message-Id: <20200311171422.10484-1-david@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series is based on latest linux-next. The patches are located at:
    https://github.com/davidhildenbrand/linux.git virtio-mem-v2

I now have acks for all !virtio-mem changes. I'll be happy to get review
feedback, testing reports, etc. for the virtio-mem changes. If there are
no further comments, I guess this is good to go as a v1 soon.

The basic idea of virtio-mem is to provide a flexible,
cross-architecture memory hot(un)plug solution that avoids many limitations
imposed by existing technologies, architectures, and interfaces. More
details can be found below and in linked material.

It's currently only enabled for x86-64, however, should theoretically work
on any architecture that supports virtio and implements memory hot(un)plug
under Linux - like s390x, powerpc64, and arm64. On x86-64, it is currently
possible to add/remove memory to the system in >= 4MB granularity.
Memory hotplug works very reliably. For memory unplug, there are no
guarantees how much memory can actually get unplugged, it depends on the
setup (especially: fragmentation of physical memory).

I am currently getting the QEMU side into shape (which will be posted as
RFC soon, see below for a link to the current state). Experimental Kata
support is in the works [4]. Also, a cloud-hypervisor implementation is
under discussion [5].

--------------------------------------------------------------------------
1. virtio-mem
--------------------------------------------------------------------------

The basic idea behind virtio-mem was presented at KVM Forum 2018. The
slides can be found at [1]. The previous RFC can be found at [2]. The
first RFC can be found at [3]. However, the concept evolved over time. The
KVM Forum slides roughly match the current design.

Patch #2 ("virtio-mem: Paravirtualized memory hotplug") contains quite some
information, especially in "include/uapi/linux/virtio_mem.h":

    Each virtio-mem device manages a dedicated region in physical address
    space. Each device can belong to a single NUMA node, multiple devices
    for a single NUMA node are possible. A virtio-mem device is like a
    "resizable DIMM" consisting of small memory blocks that can be plugged
    or unplugged. The device driver is responsible for (un)plugging memory
    blocks on demand.

    Virtio-mem devices can only operate on their assigned memory region in
    order to (un)plug memory. A device cannot (un)plug memory belonging to
    other devices.

    The "region_size" corresponds to the maximum amount of memory that can
    be provided by a device. The "size" corresponds to the amount of memory
    that is currently plugged. "requested_size" corresponds to a request
    from the device to the device driver to (un)plug blocks. The
    device driver should try to (un)plug blocks in order to reach the
    "requested_size". It is impossible to plug more memory than requested.

    The "usable_region_size" represents the memory region that can actually
    be used to (un)plug memory. It is always at least as big as the
    "requested_size" and will grow dynamically. It will only shrink when
    explicitly triggered (VIRTIO_MEM_REQ_UNPLUG).

    There are no guarantees what will happen if unplugged memory is
    read/written. Such memory should, in general, not be touched. E.g.,
    even writing might succeed, but the values will simply be discarded at
    random points in time.

    It can happen that the device cannot process a request, because it is
    busy. The device driver has to retry later.

    Usually, during system resets all memory will get unplugged, so the
    device driver can start with a clean state. However, in specific
    scenarios (if the device is busy) it can happen that the device still
    has memory plugged. The device driver can request to unplug all memory
    (VIRTIO_MEM_REQ_UNPLUG) - which might take a while to succeed if the
    device is busy.

--------------------------------------------------------------------------
2. Linux Implementation
--------------------------------------------------------------------------

Memory blocks (e.g., 128MB) are added/removed on demand. Within these
memory blocks, subblocks (e.g., 4MB) are plugged/unplugged. The sizes
depend on the target architecture, MAX_ORDER, pageblock_order, and
the block size of a virtio-mem device.

add_memory()/try_remove_memory() is used to add/remove memory blocks.
virtio-mem will not online memory blocks itself. This has to be done by
user space, or configured into the kernel
(CONFIG_MEMORY_HOTPLUG_DEFAULT_ONLINE). virtio-mem will only unplug memory
that was online to the ZONE_NORMAL. Memory is suggested to be onlined to
the ZONE_NORMAL for now.

The memory hotplug notifier is used to properly synchronize against
onlining/offlining of memory blocks and to track the states of memory
blocks (including the zone memory blocks are onlined to).

The set_online_page() callback is used to keep unplugged subblocks
of a memory block fake-offline when onlining the memory block.
generic_online_page() is used to fake-online plugged subblocks. This
handling is similar to the Hyper-V balloon driver.

PG_offline is used to mark unplugged subblocks as offline, so e.g.,
dumping tools (makedumpfile) will skip these pages. This is similar to
other balloon drivers like virtio-balloon and Hyper-V.

Memory offlining code is extended to allow drivers to drop their reference
to PG_offline pages when MEM_GOING_OFFLINE, so these pages can be skipped
when offlining memory blocks. This allows to offline memory blocks that
have partially unplugged (allocated e.g., via alloc_contig_range())
subblocks - or are completely unplugged.

alloc_contig_range()/free_contig_range() [now exposed] is used to
unplug/plug subblocks of memory blocks the are already exposed to Linux.

offline_and_remove_memory() [new] is used to offline a fully unplugged
memory block and remove it from Linux.

--------------------------------------------------------------------------
3. Changes v1 -> v2
--------------------------------------------------------------------------

- "virtio-mem: Paravirtualized memory hotplug"
-- Use "__u64" and friends in uapi header
-- Split out ACPI PXM handling
- "virtio-mem: Allow to specify an ACPI PXM as nid"
-- Squash of the ACPI PXM handling and previous "ACPI: NUMA: export
   pxm_to_node"
- "virtio-mem: Paravirtualized memory hotunplug part 2"
-- Squashed previous "mm: Export alloc_contig_range() /
   free_contig_range()"
- "virtio-mem: Allow to offline partially unplugged memory blocks"
-- WARN and dump_page() in case somebody has a reference to an unplugged
   page
- "virtio-mem: Better retry handling"
-- Use retry interval of 5s -> 5m
- Tweaked some patch descriptions

--------------------------------------------------------------------------
4. Future work
--------------------------------------------------------------------------

One of the next TODO things besides the QEMU part is writing a virtio-mem
spec - however, that might still take some time.

virtio-mem extensions (via new feature flags):
- Indicate the guest status (e.g., initialized, working, all memory is
  busy when unplugging, too many memory blocks are offline when plugging,
  etc.)
- Guest-triggered shrinking of the usable region (e.g., whenever the
  highest memory block is removed).
- Exchange of plugged<->unplugged block for defragmentation.

Memory hotplug:
- Reduce the amount of memory resources if that tunes out to be an
  issue. Or try to speed up relevant code paths to deal with many
  resources.
- Allocate vmemmap from added memory.

Memory hotunplug:
- Performance improvements:
-- Sense (lockless) if it make sense to try alloc_contig_range() at all
   before directly trying to isolate and taking locks.
-- Try to unplug bigger chunks within a memory block first.
- Make unplug more likely to succeed:
-- There are various idea to limit fragmentation on memory block
   granularity. (e.g., ZONE_PREFER_MOVABLE and smart balancing)
-- Allocate vmemmap from added memory.
- OOM handling, e.g., via an OOM handler/shrinker.
- Defragmentation
- Support for < MAX_ORDER - 1 blocks (esp. pageblock_order)

--------------------------------------------------------------------------
5. Example Usage
--------------------------------------------------------------------------

A QEMU implementation (without protection of unplugged memory, but with
resizable memory regions and optimized migration) is available at (kept
updated):
    https://github.com/davidhildenbrand/qemu.git virtio-mem

Start QEMU with two virtio-mem devices (one per NUMA node):
 $ qemu-system-x86_64 -m 4G,maxmem=204G \
  -smp sockets=2,cores=2 \
  -numa node,nodeid=0,cpus=0-1 -numa node,nodeid=1,cpus=2-3 \
  [...]
  -object memory-backend-ram,id=mem0,size=100G,managed-size=on \
  -device virtio-mem-pci,id=vm0,memdev=mem0,node=0,requested-size=0M \
  -object memory-backend-ram,id=mem1,size=100G,managed-size=on \
  -device virtio-mem-pci,id=vm1,memdev=mem1,node=1,requested-size=1G

Query the configuration:
 QEMU 4.2.50 monitor - type 'help' for more information
 (qemu) info memory-devices
 Memory device [virtio-mem]: "vm0"
   memaddr: 0x140000000
   node: 0
   requested-size: 0
   size: 0
   max-size: 107374182400
   block-size: 2097152
   memdev: /objects/mem0
 Memory device [virtio-mem]: "vm1"
   memaddr: 0x1a40000000
   node: 1
   requested-size: 1073741824
   size: 1073741824
   max-size: 107374182400
   block-size: 2097152
   memdev: /objects/mem1

Add some memory to node 0:
 QEMU 4.2.50 monitor - type 'help' for more information
 (qemu) qom-set vm0 requested-size 1G

Remove some memory from node 1:
 QEMU 4.2.50 monitor - type 'help' for more information
 (qemu) qom-set vm1 requested-size 64M

Query the configuration again:
 QEMU 4.2.50 monitor - type 'help' for more information
 (qemu) info memory-devices
 Memory device [virtio-mem]: "vm0"
   memaddr: 0x140000000
   node: 0
   requested-size: 1073741824
   size: 1073741824
   max-size: 107374182400
   block-size: 2097152
   memdev: /objects/mem0
 Memory device [virtio-mem]: "vm1"
   memaddr: 0x1a40000000
   node: 1
   requested-size: 67108864
   size: 67108864
   max-size: 107374182400
   block-size: 2097152
   memdev: /objects/mem1

--------------------------------------------------------------------------
6. Q/A
--------------------------------------------------------------------------

Q: Why add/remove parts ("subblocks") of memory blocks/sections?
A: Flexibility (section size depends on the architecture) - e.g., some
   architectures have a section size of 2GB. Also, the memory block size
   is variable (e.g., on x86-64). I want to avoid any such restrictions.
   Some use cases want to add/remove memory in smaller granularity to a
   VM (e.g., the Hyper-V balloon also implements this) - especially smaller
   VMs like used for kata containers. Also, on memory unplug, it is more
   reliable to free-up and unplug multiple small chunks instead
   of one big chunk. E.g., if one page of a DIMM is either unmovable or
   pinned, the DIMM can't get unplugged. This approach is basically a
   compromise between DIMM-based memory hot(un)plug and balloon
   inflation/deflation, which works mostly on page granularity.

Q: Why care about memory blocks?
A: They are the way to tell user space about new memory. This way,
   memory can get onlined/offlined by user space. Also, e.g., kdump
   relies on udev events to reload kexec when memory blocks are
   onlined/offlined. Memory blocks are the "real" memory hot(un)plug
   granularity. Everything that's smaller has to be emulated "on top".

Q: Won't memory unplug of subblocks fragment memory?
A: Yes and no. Unplugging e.g., >=4MB subblocks on x86-64 will not really
   fragment memory like unplugging random pages like a balloon driver does.
   Buddy merging will not be limited. However, any allocation that requires
   bigger consecutive memory chunks (e.g., gigantic pages) might observe
   the fragmentation. Possible solutions: Allocate gigantic huge pages
   before unplugging memory, don't unplug memory, combine virtio-mem with
   DIMM based memory or bigger initial memory. Remember, a virtio-mem
   device will only unplug on the memory range it manages, not on other
   DIMMs. Unplug of single memory blocks will result in similar
   fragmentation in respect to gigantic huge pages.

Q: How reliable is memory unplug?
A: There are no guarantees on how much memory can get unplugged
   again. However, it is more likely to find 4MB chunks to unplug than
   e.g., 128MB chunks. If memory is terribly fragmented, there is nothing
   we can do - for now. I consider memory hotplug the first primary use
   of virtio-mem. Memory unplug might usually work, but we want to improve
   the performance and the amount of memory we can actually unplug later.

Q: Why not unplug from the ZONE_MOVABLE?
A: Unplugged memory chunks are unmovable. Unmovable data must not end up
   on the ZONE_MOVABLE - similar to gigantic pages - they will never be
   allocated from ZONE_MOVABLE. virtio-mem added memory can be onlined
   to the ZONE_MOVABLE, but subblocks will not get unplugged from it.

Q: How big should the initial (!virtio-mem) memory of a VM be?
A: virtio-mem memory will not go to the DMA zones. So to avoid running out
   of DMA memory, I suggest something like 2-3GB on x86-64. But many
   VMs can most probably deal with less DMA memory - depends on the use
   case.

[1] https://events.linuxfoundation.org/wp-content/uploads/2017/12/virtio-mem-Paravirtualized-Memory-David-Hildenbrand-Red-Hat-1.pdf
[2] https://lkml.kernel.org/r/20190919142228.5483-1-david@redhat.com
[3] https://lkml.kernel.org/r/547865a9-d6c2-7140-47e2-5af01e7d761d@redhat.com
[4] https://github.com/kata-containers/documentation/pull/592
[5] https://github.com/cloud-hypervisor/cloud-hypervisor/pull/837

Cc: Sebastien Boeuf <sebastien.boeuf@intel.com>
Cc: Samuel Ortiz <samuel.ortiz@intel.com>
Cc: Robert Bradford <robert.bradford@intel.com>
Cc: Luiz Capitulino <lcapitulino@redhat.com>
Cc: Pankaj Gupta <pankaj.gupta.linux@gmail.com>
Cc: teawater <teawaterz@linux.alibaba.com>
Cc: Igor Mammedov <imammedo@redhat.com>
Cc: Dr. David Alan Gilbert <dgilbert@redhat.com>

David Hildenbrand (10):
  virtio-mem: Paravirtualized memory hotplug
  virtio-mem: Allow to specify an ACPI PXM as nid
  virtio-mem: Paravirtualized memory hotunplug part 1
  virtio-mem: Paravirtualized memory hotunplug part 2
  mm: Allow to offline unmovable PageOffline() pages via
    MEM_GOING_OFFLINE
  virtio-mem: Allow to offline partially unplugged memory blocks
  mm/memory_hotplug: Introduce offline_and_remove_memory()
  virtio-mem: Offline and remove completely unplugged memory blocks
  virtio-mem: Better retry handling
  MAINTAINERS: Add myself as virtio-mem maintainer

 MAINTAINERS                     |    7 +
 drivers/acpi/numa/srat.c        |    1 +
 drivers/virtio/Kconfig          |   18 +
 drivers/virtio/Makefile         |    1 +
 drivers/virtio/virtio_mem.c     | 1910 +++++++++++++++++++++++++++++++
 include/linux/memory_hotplug.h  |    1 +
 include/linux/page-flags.h      |   10 +
 include/uapi/linux/virtio_ids.h |    1 +
 include/uapi/linux/virtio_mem.h |  208 ++++
 mm/memory_hotplug.c             |   81 +-
 mm/page_alloc.c                 |   26 +
 mm/page_isolation.c             |    9 +
 12 files changed, 2263 insertions(+), 10 deletions(-)
 create mode 100644 drivers/virtio/virtio_mem.c
 create mode 100644 include/uapi/linux/virtio_mem.h
```
#### [PATCH v3 0/7] vfio/pci: SR-IOV support
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
From patchwork Wed Mar 11 21:58:25 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alex Williamson <alex.williamson@redhat.com>
X-Patchwork-Id: 11432863
Return-Path: <SRS0=PMbP=44=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 30F8C92C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Mar 2020 21:58:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 27CE720746
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Mar 2020 21:58:38 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Lzm5PtcS"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729513AbgCKV6h (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 11 Mar 2020 17:58:37 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:56011 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1729328AbgCKV6g (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 11 Mar 2020 17:58:36 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1583963915;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=obrvwIi1FyEjS5wRGrKPnSPLdfDGorfe7sIIaJexKBU=;
        b=Lzm5PtcSSxWyhK0h+R+EqlC0B5TW/zK+mG98cCmQxxHLFeJmGN80c5mIFiWNLhfuC4LD+b
        xLJwhewUz2Hl6TmqfzCLX1huOl4znamyZpCO59OU5Vz4eK0tfEC5jqg4OKvBKdUE+ZbkPv
        PfWgcdxQ35BB/9kgptzli2G/VpQgcV0=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-140-9hZTx998MT6e-uolMq_oRA-1; Wed, 11 Mar 2020 17:58:31 -0400
X-MC-Unique: 9hZTx998MT6e-uolMq_oRA-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 68D4418A5500;
        Wed, 11 Mar 2020 21:58:29 +0000 (UTC)
Received: from gimli.home (ovpn-116-28.phx2.redhat.com [10.3.116.28])
        by smtp.corp.redhat.com (Postfix) with ESMTP id E887991D74;
        Wed, 11 Mar 2020 21:58:25 +0000 (UTC)
Subject: [PATCH v3 0/7] vfio/pci: SR-IOV support
From: Alex Williamson <alex.williamson@redhat.com>
To: kvm@vger.kernel.org
Cc: linux-pci@vger.kernel.org, linux-kernel@vger.kernel.org,
        dev@dpdk.org, mtosatti@redhat.com, thomas@monjalon.net,
        bluca@debian.org, jerinjacobk@gmail.com,
        bruce.richardson@intel.com, cohuck@redhat.com, kevin.tian@intel.com
Date: Wed, 11 Mar 2020 15:58:25 -0600
Message-ID: <158396044753.5601.14804870681174789709.stgit@gimli.home>
User-Agent: StGit/0.19-dirty
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Only minor tweaks since v2, GET and SET on VFIO_DEVICE_FEATURE are
enforced mutually exclusive except with the PROBE option as suggested
by Connie, the modinfo text has been expanded for the opt-in to enable
SR-IOV support in the vfio-pci driver per discussion with Kevin.

I have not incorporated runtime warnings attempting to detect misuse
of SR-IOV or imposed a session lifetime of a VF token, both of which
were significant portions of the discussion of the v2 series.  Both of
these also seem to impose a usage model or make assumptions about VF
resource usage or configuration requirements that don't seem necessary
except for the sake of generating a warning or requiring an otherwise
unnecessary and implicit token reinitialization.  If there are new
thoughts around these or other discussion points, please raise them.

Series overview (same as provided with v1):

The synopsis of this series is that we have an ongoing desire to drive
PCIe SR-IOV PFs from userspace with VFIO.  There's an immediate need
for this with DPDK drivers and potentially interesting future use
cases in virtualization.  We've been reluctant to add this support
previously due to the dependency and trust relationship between the
VF device and PF driver.  Minimally the PF driver can induce a denial
of service to the VF, but depending on the specific implementation,
the PF driver might also be responsible for moving data between VFs
or have direct access to the state of the VF, including data or state
otherwise private to the VF or VF driver.

To help resolve these concerns, we introduce a VF token into the VFIO
PCI ABI, which acts as a shared secret key between drivers.  The
userspace PF driver is required to set the VF token to a known value
and userspace VF drivers are required to provide the token to access
the VF device.  If a PF driver is restarted with VF drivers in use, it
must also provide the current token in order to prevent a rogue
untrusted PF driver from replacing a known driver.  The degree to
which this new token is considered secret is left to the userspace
drivers, the kernel intentionally provides no means to retrieve the
current token.

Note that the above token is only required for this new model where
both the PF and VF devices are usable through vfio-pci.  Existing
models of VFIO drivers where the PF is used without SR-IOV enabled
or the VF is bound to a userspace driver with an in-kernel, host PF
driver are unaffected.

The latter configuration above also highlights a new inverted scenario
that is now possible, a userspace PF driver with in-kernel VF drivers.
I believe this is a scenario that should be allowed, but should not be
enabled by default.  This series includes code to set a default
driver_override for VFs sourced from a vfio-pci user owned PF, such
that the VFs are also bound to vfio-pci.  This model is compatible
with tools like driverctl and allows the system administrator to
decide if other bindings should be enabled.  The VF token interface
above exists only between vfio-pci PF and VF drivers, once a VF is
bound to another driver, the administrator has effectively pronounced
the device as trusted.  The vfio-pci driver will note alternate
binding in dmesg for logging and debugging purposes.

Please review, comment, and test.  The example QEMU implementation
provided with the RFC is still current for this version.  Thanks,

Alex

RFC: https://lore.kernel.org/lkml/158085337582.9445.17682266437583505502.stgit@gimli.home/
v1: https://lore.kernel.org/lkml/158145472604.16827.15751375540102298130.stgit@gimli.home/
v2: https://lore.kernel.org/lkml/158213716959.17090.8399427017403507114.stgit@gimli.home/
---

Alex Williamson (7):
      vfio: Include optional device match in vfio_device_ops callbacks
      vfio/pci: Implement match ops
      vfio/pci: Introduce VF token
      vfio: Introduce VFIO_DEVICE_FEATURE ioctl and first user
      vfio/pci: Add sriov_configure support
      vfio/pci: Remove dev_fmt definition
      vfio/pci: Cleanup .probe() exit paths


 drivers/vfio/pci/vfio_pci.c         |  390 +++++++++++++++++++++++++++++++++--
 drivers/vfio/pci/vfio_pci_private.h |   10 +
 drivers/vfio/vfio.c                 |   20 +-
 include/linux/vfio.h                |    4 
 include/uapi/linux/vfio.h           |   37 +++
 5 files changed, 433 insertions(+), 28 deletions(-)
```
