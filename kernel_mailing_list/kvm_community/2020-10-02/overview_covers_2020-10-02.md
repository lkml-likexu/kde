

#### [PATCH 0/6] Fix new html build warnings from next-20201001
##### From: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>

```c
From patchwork Fri Oct  2 05:49:44 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
X-Patchwork-Id: 11812875
Return-Path: <SRS0=ns5b=DJ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5649E6CB
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  2 Oct 2020 05:50:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3DB592145D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  2 Oct 2020 05:50:17 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1601617817;
	bh=FBPwZnSsMqIWKQkD2zCJOP8xtefKz0VFKlRBsQSz4YE=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=AwFIJVJGgiW6Wx0x791bsFhBU8TbTbGyqNIJEP6+PhWhk1LrTO4jffgwE6lydbys4
	 AJJPeVJ30AdHXRxDp3V3MYxuctFK0Pc9Y+yBjidXbzW4NdAwulNpksjSjUnYB3Ou6f
	 IW2xyqTFEQqSxVedMPZYukj4EH68TwTO2Al1XfE0=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726113AbgJBFuG (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 2 Oct 2020 01:50:06 -0400
Received: from mail.kernel.org ([198.145.29.99]:59822 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725971AbgJBFt7 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 2 Oct 2020 01:49:59 -0400
Received: from mail.kernel.org (ip5f5ad59f.dynamic.kabel-deutschland.de
 [95.90.213.159])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 85847208C7;
        Fri,  2 Oct 2020 05:49:58 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1601617798;
        bh=FBPwZnSsMqIWKQkD2zCJOP8xtefKz0VFKlRBsQSz4YE=;
        h=From:To:Cc:Subject:Date:From;
        b=ejgMZ/l6FXxzU+YdRTwMxdT0f1Q+4gbrj+84EBxH2JN9yIe9vDe8W07jPvUyVE/UW
         pwqbFJ9yYWMl5Ms1dxYbPS7KEwa6ATt81MqjfNpvhhwgtMSJSrT18+F2izm1Y7rpLF
         3mFQ7DT+0UPX36PDklpu0eXa1Raxyyql02Wb8Kf4=
Received: from mchehab by mail.kernel.org with local (Exim 4.94)
        (envelope-from <mchehab@kernel.org>)
        id 1kODx6-006hij-79; Fri, 02 Oct 2020 07:49:56 +0200
From: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
To: Linux Doc Mailing List <linux-doc@vger.kernel.org>
Cc: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>,
        linux-kernel@vger.kernel.org, Jonathan Corbet <corbet@lwn.net>,
        "David S. Miller" <davem@davemloft.net>,
        Alexandru Elisei <alexandru.elisei@arm.com>,
        Andrew Jones <drjones@redhat.com>,
        Andrew Lunn <andrew@lunn.ch>,
        Anton Ivanov <anton.ivanov@cambridgegreys.com>,
        Balbir Singh <sblbir@amazon.com>,
        Bartosz Golaszewski <bgolaszewski@baylibre.com>,
        Eugeniu Rosca <erosca@de.adit-jv.com>,
        Geert Uytterhoeven <geert+renesas@glider.be>,
        Jakub Kicinski <kuba@kernel.org>,
        Jeff Dike <jdike@addtoit.com>,
        Linus Walleij <linus.walleij@linaro.org>,
        Marc Zyngier <maz@kernel.org>,
        Mathieu Poirier <mathieu.poirier@linaro.org>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Richard Weinberger <richard@nod.at>,
        Taehee Yoo <ap420073@gmail.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ulrich Hecht <uli+renesas@fpond.eu>,
        Wolfram Sang <wsa@kernel.org>, kvm@vger.kernel.org,
        linux-gpio@vger.kernel.org, linux-i2c@vger.kernel.org,
        linux-um@lists.infradead.org, netdev@vger.kernel.org
Subject: [PATCH 0/6] Fix new html build warnings from next-20201001
Date: Fri,  2 Oct 2020 07:49:44 +0200
Message-Id: <cover.1601616399.git.mchehab+huawei@kernel.org>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Sender: Mauro Carvalho Chehab <mchehab@kernel.org>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

There are some new warnings when building the documentation from
yesterday's linux next. This small series fix them.

- patch 1 documents two new kernel-doc parameters on a net core file.
  I used the commit log in order to help documenting them;
- patch 2 fixes some tags at UMLv2 howto;
- patches 3 and 5 add some new documents at the corresponding
  index file.
- patch 4 changes kernel-doc script for it to recognize typedef enums.

Patch 4 should probably be merged via docs tree, but the others
are against stuff recently added at linux-next. So, the better is to
merge them directly at the trees which introduced the issue.

-

As a reference, the patches fixing all html build warnings are at:

	https://git.linuxtv.org/mchehab/experimental.git/log/?h=sphinx3-fixes-v3

Such series also adds support for Sphinx versions 3.1 and above.

It should be noticed that, with Sphinx version 3 and above, there
are a few new warnings, because currently Sphinx assumes a
that names are unique for all C symbols. There are a few cases
where we have the same name for a function and for a struct at
the Kernel. Upstream is already working on a solution for that.

So, for now, I recomend doing html builds with version < 3.


Mauro Carvalho Chehab (6):
  net: core: document two new elements of struct net_device
  docs: vcpu.rst: fix some build warnings
  docs: virt: user_mode_linux_howto_v2.rst: fix a literal block markup
  docs: i2c: index.rst: add slave-testunit-backend.rst
  scripts: kernel-doc: add support for typedef enum
  docs: gpio: add a new document to its index.rst

 Documentation/admin-guide/gpio/index.rst      |  1 +
 .../admin-guide/hw-vuln/l1d_flush.rst         |  3 +--
 Documentation/i2c/index.rst                   |  1 +
 Documentation/virt/kvm/devices/vcpu.rst       | 26 +++++++++----------
 .../virt/uml/user_mode_linux_howto_v2.rst     |  1 +
 include/linux/netdevice.h                     |  5 ++++
 scripts/kernel-doc                            | 15 ++++++++---
 7 files changed, 33 insertions(+), 19 deletions(-)
```
#### [kvm-unit-tests PATCH v2 0/7] Rewrite the allocators
##### From: Claudio Imbrenda <imbrenda@linux.ibm.com>

```c
From patchwork Fri Oct  2 15:44:13 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Claudio Imbrenda <imbrenda@linux.ibm.com>
X-Patchwork-Id: 11813891
Return-Path: <SRS0=ns5b=DJ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 86845112E
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  2 Oct 2020 15:44:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6760420795
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  2 Oct 2020 15:44:38 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="nCiv1hGB"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388091AbgJBPoh (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 2 Oct 2020 11:44:37 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:62586 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S2387688AbgJBPo1 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 2 Oct 2020 11:44:27 -0400
Received: from pps.filterd (m0098396.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 092Fgtfs170844
        for <kvm@vger.kernel.org>; Fri, 2 Oct 2020 11:44:26 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=OBFmEtstBDrixjho+AObz9IFTju2w8vuHTINydbaTtY=;
 b=nCiv1hGBKTD+VmUq5V/XUQWX/FF62Qme6WSwf3O6euwt+eqFUvnBh44bvl1niiTsD2Ru
 A97adqQVrNgpPCipksB6Z5HQR5npl3VuyD9BmA/nUNfsNCHQuWKFAHEeX6TO1cYIPKYq
 uWgDBrOQjEv19kz1cgapB3f+qhV4540hk8EMe4idsOKMoc+wtedRBO99hjey24UzQ+SG
 XEcUz6xkG2RgGL2O/B+uA8CGaQiWs4T+ZNbWjU3vE+nML075BHoZAFrr9DXH9u3P0Dys
 gsn5h4M3t+sH7XvmJbxY6Z77VhsesZ+ghcAn4jQ2nCOXfSghokNNv3HSJivwh+7MrBQt KA==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 33x73900xr-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT)
        for <kvm@vger.kernel.org>; Fri, 02 Oct 2020 11:44:26 -0400
Received: from m0098396.ppops.net (m0098396.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 092FiQFS174521
        for <kvm@vger.kernel.org>; Fri, 2 Oct 2020 11:44:26 -0400
Received: from ppma04ams.nl.ibm.com (63.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.99])
        by mx0a-001b2d01.pphosted.com with ESMTP id 33x73900wv-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 02 Oct 2020 11:44:25 -0400
Received: from pps.filterd (ppma04ams.nl.ibm.com [127.0.0.1])
        by ppma04ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 092FhJkH031116;
        Fri, 2 Oct 2020 15:44:23 GMT
Received: from b06cxnps4076.portsmouth.uk.ibm.com
 (d06relay13.portsmouth.uk.ibm.com [9.149.109.198])
        by ppma04ams.nl.ibm.com with ESMTP id 33sw97xqj3-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 02 Oct 2020 15:44:23 +0000
Received: from d06av24.portsmouth.uk.ibm.com (mk.ibm.com [9.149.105.60])
        by b06cxnps4076.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 092FiLi927525380
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 2 Oct 2020 15:44:21 GMT
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 69A654203F;
        Fri,  2 Oct 2020 15:44:21 +0000 (GMT)
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 05DBB42042;
        Fri,  2 Oct 2020 15:44:21 +0000 (GMT)
Received: from ibm-vm.ibmuc.com (unknown [9.145.14.90])
        by d06av24.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Fri,  2 Oct 2020 15:44:20 +0000 (GMT)
From: Claudio Imbrenda <imbrenda@linux.ibm.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com
Cc: frankja@linux.ibm.com, david@redhat.com, thuth@redhat.com,
        cohuck@redhat.com, lvivier@redhat.com
Subject: [kvm-unit-tests PATCH v2 0/7] Rewrite the allocators
Date: Fri,  2 Oct 2020 17:44:13 +0200
Message-Id: <20201002154420.292134-1-imbrenda@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-10-02_10:2020-10-02,2020-10-02 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 lowpriorityscore=0
 priorityscore=1501 impostorscore=0 malwarescore=0 mlxscore=0 bulkscore=0
 phishscore=0 clxscore=1011 adultscore=0 mlxlogscore=999 spamscore=0
 suspectscore=2 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2010020119
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The KVM unit tests are increasingly being used to test more than just
KVM. They are being used to test TCG, qemu I/O device emulation, other
hypervisors, and even actual hardware.

The existing memory allocators are becoming more and more inadequate to
the needs of the upcoming unit tests (but also some existing ones, see
below).

Some important features that are lacking:
* ability to perform a small physical page allocation with a big
  alignment withtout wasting huge amounts of memory
* ability to allocate physical pages from specific pools/areaas (e.g.
  below 16M, or 4G, etc)
* ability to reserve arbitrary pages (if free), removing them from the
  free pool

Some other features that are nice, but not so fundamental:
* no need for the generic allocator to keep track of metadata
  (i.e. allocation size), this is now handled by the lower level
  allocators
* coalescing small blocks into bigger ones, to allow contiguous memory
  freed in small blocks in a random order to be used for large
  allocations again

This is achieved in the following ways:

For the virtual allocator:
* only the virtul allocator needs one extra page of metadata, but only
  for allocations that wouldn't fit in one page

For the page allocator:
* page allocator has up to 6 memory pools, each pool has a metadata
  area; the metadata has a byte for each page in the area, describing
  the order of the block it belongs to, and whether it is free
* if there are no free blocks of the desired size, a bigger block is
  split until we reach the required size; the unused parts of the block
  are put back in the free lists
* if an allocation needs ablock with a larger alignment than its size, a
  larger block of (at least) the required order is split; the unused parts
  put back in the appropriate free lists
* if the allocation could not be satisfied, the next allowed area is
  searched; the allocation fails only when all allowed areas have been
  tried
* new functions to perform allocations from specific areas; the areas
  are arch-dependent and should be set up by the arch code
* for now x86 has a memory area for "lowest" memory under 16MB, one for
  "low" memory under 4GB and one for the rest, while s390x has one for under
  2GB and one for the rest; suggestions for more fine grained areas or for
  the other architectures are welcome
* upon freeing a block, an attempt is made to coalesce it into the
  appropriate neighbour (if it is free), and so on for the resulting
  larger block thus obtained

For the physical allocator:
* the minimum alignment is now handled manually, since it has been
  removed from the common struct


This patchset addresses some current but otherwise unsolvable issues on
s390x, such as the need to allocate a block under 2GB for each SMP CPU
upon CPU activation.

This patchset has been tested on s390x, amd64 and i386. It has also been
compiled on aarch64.

V1->V2:
* Renamed some functions, as per review comments
* Improved commit messages
* Split the list handling functions into an independent header
* Addded arch-specific headers to define the memory areas
* Fixed some minor issues
* The magic value for small allocations in the virtual allocator is now
  put right before the returned pointer, like for large allocations
* Added comments to make the code more readable
* Many minor fixes

Claudio Imbrenda (7):
  lib/list: Add double linked list management functions
  lib/vmalloc: vmalloc support for handling allocation metadata
  lib/asm: Add definitions of memory areas
  lib/alloc_page: complete rewrite of the page allocator
  lib/alloc: simplify free and malloc
  lib/alloc.h: remove align_min from struct alloc_ops
  lib/alloc_page: allow reserving arbitrary memory ranges

 lib/asm-generic/memory_areas.h |  11 +
 lib/arm/asm/memory_areas.h     |  11 +
 lib/arm64/asm/memory_areas.h   |  11 +
 lib/powerpc/asm/memory_areas.h |  11 +
 lib/ppc64/asm/memory_areas.h   |  11 +
 lib/s390x/asm/memory_areas.h   |  17 ++
 lib/x86/asm/memory_areas.h     |  22 ++
 lib/alloc.h                    |   3 +-
 lib/alloc_page.h               |  80 ++++-
 lib/list.h                     |  53 ++++
 lib/alloc.c                    |  42 +--
 lib/alloc_page.c               | 541 +++++++++++++++++++++++++++------
 lib/alloc_phys.c               |   9 +-
 lib/arm/setup.c                |   2 +-
 lib/s390x/sclp.c               |   6 +-
 lib/s390x/smp.c                |   6 +-
 lib/vmalloc.c                  | 121 ++++++--
 s390x/smp.c                    |   4 +-
 18 files changed, 789 insertions(+), 172 deletions(-)
 create mode 100644 lib/asm-generic/memory_areas.h
 create mode 100644 lib/arm/asm/memory_areas.h
 create mode 100644 lib/arm64/asm/memory_areas.h
 create mode 100644 lib/powerpc/asm/memory_areas.h
 create mode 100644 lib/ppc64/asm/memory_areas.h
 create mode 100644 lib/s390x/asm/memory_areas.h
 create mode 100644 lib/x86/asm/memory_areas.h
 create mode 100644 lib/list.h
```
#### [RFC PATCH v2 00/33] SEV-ES hypervisor support
##### From: Tom Lendacky <thomas.lendacky@amd.com>
From: Tom Lendacky <thomas.lendacky@amd.com>

```c
From patchwork Fri Oct  2 17:02:24 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tom Lendacky <thomas.lendacky@amd.com>
X-Patchwork-Id: 11814079
Return-Path: <SRS0=ns5b=DJ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6264A139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  2 Oct 2020 17:03:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3C79820758
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  2 Oct 2020 17:03:22 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="sBtVvUUH"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388208AbgJBRDT (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 2 Oct 2020 13:03:19 -0400
Received: from mail-mw2nam10on2070.outbound.protection.outlook.com
 ([40.107.94.70]:47009
        "EHLO NAM10-MW2-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1725995AbgJBRDS (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 2 Oct 2020 13:03:18 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=jEOlKOpI2NaaFolVRzp1BD+M56dZfXySoABh4UVD7hFf2Fstf6GVGVuaIrQdPFnTbmc0VBRzG/hfRTBh9PkXcuSo7rUEt5FtQ8asPjPIgO1nF2NzHKkVMVOc4fCAhy22yLcFVlY0yU6jq66FbhkYRPmfEHfL6eQ3UFGbXdjjOlgohGJd1W6uUD0yAvjaq84ZO8QFfzPeXapQB0UIHxaKZF3rKo/S2/nGH6lP6eon4QdyK6AGAehDTJPNt9I4Ywc/0XfXydQQNkd19yJSVylIklgzl1/8tkjrGbX44SJuHAmFHu2j5zeeIW6KAylgeYMNwN5eMa/Ji+i2SeXkT64JkQ==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=A/hFUML1z4GtZgMMRdtKLHjxDcERlIOilWMysLeE7nc=;
 b=US69HKu0gvCSzzQcYVHBzDxxNUbUdcv9oDwnOOc5yLOGPSiX6SX88zrZpOF8iqMzlC3dSif5p6nbJi+xU/0wKe+aFC672bCjHgvZJv+qH/QbZkbrXbXhXxsgdFZfX4YZnxQMwkYg9naENLaWKOsOuq7NrtntTJTeE5SPdDjyv6WppOnk9M4jpKoRX5NjYSUvcGSHOk0FdCq0LJGz8Iv8WcgqKzSMA3D2/fSiU11KazBd1KuNm10zA1y5n2vd6mtCUsRVMiZ+ehehiEk/+LjKxmI7fw60dKo8A3n85x+VXHnoxbUjB5QUp22taOlbTLMmy0ahcE51Uinpgc9Bg4Qu8Q==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=A/hFUML1z4GtZgMMRdtKLHjxDcERlIOilWMysLeE7nc=;
 b=sBtVvUUHapHPYvIkTLovNWIXoRA5eIexyOdYLp1FPXfPjvhJMGBAF+yPYZBLYbYBMUdHrvkZMvGbQoN6CcIUju2Igrtt7s1UxNx7xOMsIanBWJXL2Q7uNY0UK6fuIekor6AWgEFjy2f2lT8OcfjyWgGSDdAjl11Pz1lD9FNABtE=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=amd.com;
Received: from DM5PR12MB1355.namprd12.prod.outlook.com (2603:10b6:3:6e::7) by
 DM6PR12MB4218.namprd12.prod.outlook.com (2603:10b6:5:21b::16) with Microsoft
 SMTP Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.3433.35; Fri, 2 Oct 2020 17:03:14 +0000
Received: from DM5PR12MB1355.namprd12.prod.outlook.com
 ([fe80::4d88:9239:2419:7348]) by DM5PR12MB1355.namprd12.prod.outlook.com
 ([fe80::4d88:9239:2419:7348%2]) with mapi id 15.20.3433.039; Fri, 2 Oct 2020
 17:03:14 +0000
From: Tom Lendacky <thomas.lendacky@amd.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org, x86@kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Borislav Petkov <bp@alien8.de>, Ingo Molnar <mingo@redhat.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Brijesh Singh <brijesh.singh@amd.com>
Subject: [RFC PATCH v2 00/33] SEV-ES hypervisor support
Date: Fri,  2 Oct 2020 12:02:24 -0500
Message-Id: <cover.1601658176.git.thomas.lendacky@amd.com>
X-Mailer: git-send-email 2.28.0
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: SN4PR0401CA0020.namprd04.prod.outlook.com
 (2603:10b6:803:21::30) To DM5PR12MB1355.namprd12.prod.outlook.com
 (2603:10b6:3:6e::7)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from tlendack-t1.amd.com (165.204.77.1) by
 SN4PR0401CA0020.namprd04.prod.outlook.com (2603:10b6:803:21::30) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3433.37 via Frontend
 Transport; Fri, 2 Oct 2020 17:03:13 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 754e4b59-a84e-4f9e-8145-08d866f50cea
X-MS-TrafficTypeDiagnostic: DM6PR12MB4218:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM6PR12MB4218CF1C83B27A6A822752FBEC310@DM6PR12MB4218.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:1850;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 lIn7bRdN67EaOQuTGtx4kzoWGCgZm3t5idNHyUM+irXGokRu2NJHUW/IF2OKaUfNBNejAB3EedZ3lIqxUjbWgnJiGwtkH7YL/imk67eSs7lDNpz7mVmEwxmapW4auREv0ku+pnucuRHV0isu7rPA+nabF0eXa5GhrA6cqJ4O89B72qzUrUNmMurJ3pInUxUdeHexm1+P3mVHCKXfs6JXNIMPbYvYIWsdA1WTjSAA7YNikYZm8Wf0naLSRSRlga43eaYrkRhoQt1Y4o3xZKkV3izW/WvCkYesdKGTcQszeOkN/rXcjyUZkDHoEfsuqrPwDmPu61ywPKAjIotO61WNg31NVhPBUowMhggbT70IsDbX57MljjvF9uB70L09vJG0fPuqombqawIaQt/KOhk4mw==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM5PR12MB1355.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(396003)(346002)(39860400002)(366004)(136003)(376002)(6666004)(8676002)(83380400001)(83080400001)(6486002)(2616005)(66556008)(956004)(66476007)(66946007)(52116002)(7696005)(4326008)(36756003)(5660300002)(8936002)(16526019)(186003)(2906002)(54906003)(316002)(26005)(966005)(7416002)(478600001)(86362001);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 61hu1bcywvcmlcA+Ve9dUGmb/0qQ+bOyFJilV/C1iGhVj7WQCZ4WHy9F2LgpeNsyxEkWK1rzGPOa1mbU2enTH8Tq47zyfCPWmvQoHN2jNcc3C0E/nVqxO/qsNII8rOnHjgWUMnOTA2Z5kpZK2Pxe5xZE6SStjqfHGcEOcKhRzhCe5OcvEz5nhD+3cmrm+MOiXYUJy0p3I9A+2DPL3AeyWMd5t3+yYLcSN3CFx9w+Hmn6dGKNqtyG4RoU6PJ4upxWq1D6j1cDcw8cGI4x0NkdZUZxoMvxrWh2yc1jBF9JnxZDc5yiFSAUAyxWSn6iSznwKeNOsz/NzWZ4RxMN0dNjwRJC/So752/IMqO51LkXdrASb3YPrzgQ1eQb8aZvSZVHQm8K3amSGe8jnW81F+r5lXUbn7rmh9Kh8uneVKUmAtNz3nRHQ1uDOpoqmvDEUVgzbT3yHJSuBSkKD4HWSOSXL1WNNBf1eKCUnbQ5MMo0CNGY8JgCJ0uLAKPJfhivC/c0aGhxVUT+HIZD1DZpm7HxUKxhDTGZEv/dYtYgyGWy7BwO+3bRdE1GABWcPFDzVf1wS5qIl82vTd/HXCme+sznA4CVOc/8DQx/EBkBLc20m/uVnh/kvpEWW1bRXEl0MUQktTtPol6gLHon6FCovimgMw==
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 754e4b59-a84e-4f9e-8145-08d866f50cea
X-MS-Exchange-CrossTenant-AuthSource: DM5PR12MB1355.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 02 Oct 2020 17:03:14.4320
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 uq0S5xEJSaFs99+/MlmURlUWTR9h+SHiY4dG9Wo5bduNfGSFffK8mWw1WclTHGsXwq7OgRp8rUKPZc8s3MhsDw==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6PR12MB4218
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Tom Lendacky <thomas.lendacky@amd.com>

This patch series provides support for running SEV-ES guests under KVM.

Secure Encrypted Virtualization - Encrypted State (SEV-ES) expands on the
SEV support to protect the guest register state from the hypervisor. See
"AMD64 Architecture Programmer's Manual Volume 2: System Programming",
section "15.35 Encrypted State (SEV-ES)" [1].

In order to allow a hypervisor to perform functions on behalf of a guest,
there is architectural support for notifying a guest's operating system
when certain types of VMEXITs are about to occur. This allows the guest to
selectively share information with the hypervisor to satisfy the requested
function. The notification is performed using a new exception, the VMM
Communication exception (#VC). The information is shared through the
Guest-Hypervisor Communication Block (GHCB) using the VMGEXIT instruction.
The GHCB format and the protocol for using it is documented in "SEV-ES
Guest-Hypervisor Communication Block Standardization" [2].

Under SEV-ES, a vCPU save area (VMSA) must be encrypted. SVM is updated to
build the initial VMSA and then encrypt it before running the guest. Once
encrypted, it must not be modified by the hypervisor. Modification of the
VMSA will result in the VMRUN instruction failing with a SHUTDOWN exit
code. KVM must support the VMGEXIT exit code in order to perform the
necessary functions required of the guest. The GHCB is used to exchange
the information needed by both the hypervisor and the guest.

To simplify access to the VMSA and the GHCB, SVM uses an accessor function
to obtain the address of the either the VMSA or the GHCB, depending on the
stage of execution of the guest.

There are changes to some of the intercepts that are needed under SEV-ES.
For example, CR0 writes cannot be intercepted, so the code needs to ensure
that the intercept is not enabled during execution or that the hypervisor
does not try to read the register as part of exit processing. Another
example is shutdown processing, where the vCPU cannot be directly reset.

Support is added to handle VMGEXIT events and implement the GHCB protocol.
This includes supporting standard exit events, like a CPUID instruction
intercept, to new support, for things like AP processor booting. Much of
the existing SVM intercept support can be re-used by setting the exit
code information from the VMGEXIT and calling the appropriate intercept
handlers.

Finally, to launch and run an SEV-ES guest requires changes to the vCPU
initialization, loading and execution.

[1] https://www.amd.com/system/files/TechDocs/24593.pdf
[2] https://developer.amd.com/wp-content/resources/56421.pdf
---

These patches are based on a commit of the KVM next branch. However, I had
to backport recent SEV-ES guest patches (a previous series to the actual
patches that are now in the tip tree) into my development branch, since
there are prereq patches needed by this series. As a result, this patch
series will not successfully build or apply to the KVM next branch as is.

A version of the tree can be found at:
https://github.com/AMDESE/linux/tree/sev-es-5.9-v1

Changes from v1:
- Removed the VMSA indirection support:
  - On LAUNCH_UPDATE_VMSA, sync traditional VMSA over to the new SEV-ES
    VMSA area to be encrypted.
  - On VMGEXIT VMEXIT, directly copy valid registers into vCPU arch
    register array from GHCB. On VMRUN (following a VMGEXIT), directly
    copy dirty vCPU arch registers to GHCB.
  - Removed reg_read_override()/reg_write_override() KVM ops.
- Added VMGEXIT exit-reason validation.
- Changed kvm_vcpu_arch variable vmsa_encrypted to guest_state_protected
- Updated the tracking support for EFER/CR0/CR4/CR8 to minimize changes
  to the x86.c code
- Updated __set_sregs to not set any register values (previously supported
  setting the tracked values of EFER/CR0/CR4/CR8)
- Added support for reporting SMM capability at the VM-level. This allows
  an SEV-ES guest to indicate SMM is not supported
- Updated FPU support to check for a guest FPU save area before using it.
  Updated SVM to free guest FPU for an SEV-ES guest during KVM create_vcpu
  op.
- Removed changes to the kvm_skip_emulated_instruction()
- Added VMSA validity checks before invoking LAUNCH_UPDATE_VMSA
- Minor code restructuring in areas for better readability

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Jim Mattson <jmattson@google.com>
Cc: Joerg Roedel <joro@8bytes.org>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>
Cc: Wanpeng Li <wanpengli@tencent.com>
Cc: Borislav Petkov <bp@alien8.de>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Brijesh Singh <brijesh.singh@amd.com>

Tom Lendacky (33):
  KVM: SVM: Remove the call to sev_platform_status() during setup
  KVM: SVM: Add support for SEV-ES capability in KVM
  KVM: SVM: Add GHCB accessor functions for retrieving fields
  KVM: SVM: Add support for the SEV-ES VMSA
  KVM: x86: Mark GPRs dirty when written
  KVM: SVM: Add required changes to support intercepts under SEV-ES
  KVM: SVM: Prevent debugging under SEV-ES
  KVM: SVM: Do not allow instruction emulation under SEV-ES
  KVM: SVM: Cannot re-initialize the VMCB after shutdown with SEV-ES
  KVM: SVM: Prepare for SEV-ES exit handling in the sev.c file
  KVM: SVM: Add initial support for a VMGEXIT VMEXIT
  KVM: SVM: Create trace events for VMGEXIT processing
  KVM: SVM: Add support for SEV-ES GHCB MSR protocol function 0x002
  KVM: SVM: Add support for SEV-ES GHCB MSR protocol function 0x004
  KVM: SVM: Add support for SEV-ES GHCB MSR protocol function 0x100
  KVM: SVM: Create trace events for VMGEXIT MSR protocol processing
  KVM: SVM: Support MMIO for an SEV-ES guest
  KVM: SVM: Support port IO operations for an SEV-ES guest
  KVM: SVM: Add support for EFER write traps for an SEV-ES guest
  KVM: SVM: Add support for CR0 write traps for an SEV-ES guest
  KVM: SVM: Add support for CR4 write traps for an SEV-ES guest
  KVM: SVM: Add support for CR8 write traps for an SEV-ES guest
  KVM: x86: Update __get_sregs() / __set_sregs() to support SEV-ES
  KVM: SVM: Do not report support for SMM for an SEV-ES guest
  KVM: SVM: Guest FPU state save/restore not needed for SEV-ES guest
  KVM: SVM: Add support for booting APs for an SEV-ES guest
  KVM: SVM: Add NMI support for an SEV-ES guest
  KVM: SVM: Set the encryption mask for the SVM host save area
  KVM: SVM: Update ASID allocation to support SEV-ES guests
  KVM: SVM: Provide support for SEV-ES vCPU creation/loading
  KVM: SVM: Provide support for SEV-ES vCPU loading
  KVM: SVM: Provide an updated VMRUN invocation for SEV-ES guests
  KVM: SVM: Provide support to launch and run an SEV-ES guest

 arch/x86/include/asm/kvm_host.h  |  12 +-
 arch/x86/include/asm/msr-index.h |   1 +
 arch/x86/include/asm/svm.h       |  40 +-
 arch/x86/include/uapi/asm/svm.h  |  28 ++
 arch/x86/kernel/cpu/vmware.c     |  12 +-
 arch/x86/kvm/Kconfig             |   3 +-
 arch/x86/kvm/cpuid.c             |   1 +
 arch/x86/kvm/kvm_cache_regs.h    |  51 +-
 arch/x86/kvm/svm/sev.c           | 837 +++++++++++++++++++++++++++++--
 arch/x86/kvm/svm/svm.c           | 465 +++++++++++++----
 arch/x86/kvm/svm/svm.h           | 165 ++++--
 arch/x86/kvm/svm/vmenter.S       |  50 ++
 arch/x86/kvm/trace.h             |  97 ++++
 arch/x86/kvm/vmx/vmx.c           |   6 +-
 arch/x86/kvm/x86.c               | 364 ++++++++++++--
 arch/x86/kvm/x86.h               |   9 +
 16 files changed, 1892 insertions(+), 249 deletions(-)
```
#### [PATCH v2 0/5] Pass zPCI hardware information via VFIO
##### From: Matthew Rosato <mjrosato@linux.ibm.com>

```c
From patchwork Fri Oct  2 20:00:39 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Matthew Rosato <mjrosato@linux.ibm.com>
X-Patchwork-Id: 11814547
Return-Path: <SRS0=ns5b=DJ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 19B9D139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  2 Oct 2020 20:00:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E5FC920758
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  2 Oct 2020 20:00:57 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="Dq0iIiG6"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725767AbgJBUAy (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 2 Oct 2020 16:00:54 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:28148 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1725300AbgJBUAy (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 2 Oct 2020 16:00:54 -0400
Received: from pps.filterd (m0098420.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 092JWLQu071707;
        Fri, 2 Oct 2020 16:00:53 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id; s=pp1;
 bh=lIbcftX8dHVCw3Fd7UfxzvrLwo6H9wOwsR6Kl/OP0eM=;
 b=Dq0iIiG6vxrT8Kb8QHGIyKtxiuCwmCH5WOQCdjWrcM+7MlLj+m4gYvhSE3VyXIqOaSam
 gGYce7EQro+A7owOJaf4uzHxVvQdpQmQqAIf2EHrtdzPH/LfNqwDtnJ1PqqEmvBeTVGF
 csQpwCJvP0lWFw3qK/TMu7eAfAUmk5VTDJX1KdIov3lRIvqr9QQItkXdyLt+kRUKg5dR
 510Vi7nlpTJYoPyGozlSpYtfKUEYFHC/MFtGmPkQr4ZcjEMB43HaCPHeoENcSvrlwrMT
 EjGMRB6GTrU+mwRm12b0C2IhB+BkMg461egfCT8GCXLO5ctA3C6e4pCUKpcSyglauA0C 8w==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 33xa0xs6xh-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 02 Oct 2020 16:00:53 -0400
Received: from m0098420.ppops.net (m0098420.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 092K0ZXJ164510;
        Fri, 2 Oct 2020 16:00:52 -0400
Received: from ppma03dal.us.ibm.com (b.bd.3ea9.ip4.static.sl-reverse.com
 [169.62.189.11])
        by mx0b-001b2d01.pphosted.com with ESMTP id 33xa0xs6x6-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 02 Oct 2020 16:00:52 -0400
Received: from pps.filterd (ppma03dal.us.ibm.com [127.0.0.1])
        by ppma03dal.us.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 092JlIgb026874;
        Fri, 2 Oct 2020 20:00:52 GMT
Received: from b03cxnp07028.gho.boulder.ibm.com
 (b03cxnp07028.gho.boulder.ibm.com [9.17.130.15])
        by ppma03dal.us.ibm.com with ESMTP id 33sw9ae9vk-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 02 Oct 2020 20:00:52 +0000
Received: from b03ledav001.gho.boulder.ibm.com
 (b03ledav001.gho.boulder.ibm.com [9.17.130.232])
        by b03cxnp07028.gho.boulder.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 092K0mZE54985076
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 2 Oct 2020 20:00:48 GMT
Received: from b03ledav001.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 8DB7F6E054;
        Fri,  2 Oct 2020 20:00:48 +0000 (GMT)
Received: from b03ledav001.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 71B716E050;
        Fri,  2 Oct 2020 20:00:47 +0000 (GMT)
Received: from oc4221205838.ibm.com (unknown [9.163.4.25])
        by b03ledav001.gho.boulder.ibm.com (Postfix) with ESMTP;
        Fri,  2 Oct 2020 20:00:47 +0000 (GMT)
From: Matthew Rosato <mjrosato@linux.ibm.com>
To: alex.williamson@redhat.com, cohuck@redhat.com,
        schnelle@linux.ibm.com
Cc: pmorel@linux.ibm.com, borntraeger@de.ibm.com, hca@linux.ibm.com,
        gor@linux.ibm.com, gerald.schaefer@linux.ibm.com,
        linux-s390@vger.kernel.org, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v2 0/5] Pass zPCI hardware information via VFIO
Date: Fri,  2 Oct 2020 16:00:39 -0400
Message-Id: <1601668844-5798-1-git-send-email-mjrosato@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-10-02_14:2020-10-02,2020-10-02 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 suspectscore=0 bulkscore=0
 malwarescore=0 adultscore=0 spamscore=0 mlxscore=0 clxscore=1015
 phishscore=0 impostorscore=0 priorityscore=1501 lowpriorityscore=0
 mlxlogscore=999 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2010020137
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patchset provides a means by which hardware information about the
underlying PCI device can be passed up to userspace (ie, QEMU) so that
this hardware information can be used rather than previously hard-coded
assumptions. A new VFIO region type is defined which holds this
information. 

A form of these patches saw some rounds last year but has been back-
tabled for a while.  The original work for this feature was done by Pierre
Morel. I'd like to refresh the discussion on this and get this finished up
so that we can move forward with better-supporting additional types of
PCI-attached devices.  The proposal here presents a completely different
region mapping vs the prior approach, taking inspiration from vfio info
capability chains to provide device CLP information in a way that allows 
for future expansion (new CLP features).

This feature is toggled via the CONFIG_VFIO_PCI_ZDEV configuration entry. 

Changes from v1:
- Added ACKs (thanks!)
- Patch 2: Minor change:s/util_avail/util_str_avail/ per Niklas
- Patch 3: removed __packed
- Patch 3: rework various descriptions / comment blocks
- New patch: MAINTAINERS hit to cover new files.

Matthew Rosato (5):
  s390/pci: stash version in the zpci_dev
  s390/pci: track whether util_str is valid in the zpci_dev
  vfio-pci/zdev: define the vfio_zdev header
  vfio-pci/zdev: use a device region to retrieve zPCI information
  MAINTAINERS: Add entry for s390 vfio-pci

 MAINTAINERS                         |   8 ++
 arch/s390/include/asm/pci.h         |   4 +-
 arch/s390/pci/pci_clp.c             |   2 +
 drivers/vfio/pci/Kconfig            |  13 ++
 drivers/vfio/pci/Makefile           |   1 +
 drivers/vfio/pci/vfio_pci.c         |   8 ++
 drivers/vfio/pci/vfio_pci_private.h |  10 ++
 drivers/vfio/pci/vfio_pci_zdev.c    | 242 ++++++++++++++++++++++++++++++++++++
 include/uapi/linux/vfio.h           |   5 +
 include/uapi/linux/vfio_zdev.h      | 118 ++++++++++++++++++
 10 files changed, 410 insertions(+), 1 deletion(-)
 create mode 100644 drivers/vfio/pci/vfio_pci_zdev.c
 create mode 100644 include/uapi/linux/vfio_zdev.h
```
#### [PATCH v2 0/9] Retrieve zPCI hardware information from VFIO
##### From: Matthew Rosato <mjrosato@linux.ibm.com>

```c
From patchwork Fri Oct  2 20:06:22 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Matthew Rosato <mjrosato@linux.ibm.com>
X-Patchwork-Id: 11814559
Return-Path: <SRS0=ns5b=DJ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 24A966CB
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  2 Oct 2020 20:06:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id EE37420738
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  2 Oct 2020 20:06:47 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="CB+/aRw/"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725681AbgJBUGq (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 2 Oct 2020 16:06:46 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:2858 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1725446AbgJBUGq (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 2 Oct 2020 16:06:46 -0400
Received: from pps.filterd (m0098413.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 092K2Jav110817;
        Fri, 2 Oct 2020 16:06:37 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id; s=pp1;
 bh=+JYwpC35tUm/nlFFYqmK4F+lxWr/aRuhCz48GQWyD0k=;
 b=CB+/aRw/ks6mUxhkT5hiHsAWRzO9eYOgMLbgsTiSYg2H74wfiFGxhn+maRr+t3Z8DFcV
 JloVp3PtycRqjdhjkG8QqJjH9TM46fvAx4ZfJ5TPi/6+gdNNSaCu/lF+B688hQCH9rzb
 LezwrmnY9AGjD8Asbsv92/4W3E2k0FQVCIthrPymZSEQc5lr1K38kIHihSDESoHK3/NK
 Xi4oaPVIPg5vuCoMpCh1ySHrFdq69osTbA8AXe+sRWun/CK8dvbLUb9HNWEAUlkeCwsH
 K0kVTHxtj7ZIyN9OVuEeIBKYhLSPwsNFNPrF2rdKF6/tvtg9fZVIp+NvhUOEEDDAMD1F yw==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 33xaqmrb0e-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 02 Oct 2020 16:06:37 -0400
Received: from m0098413.ppops.net (m0098413.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 092K5HvV125763;
        Fri, 2 Oct 2020 16:06:37 -0400
Received: from ppma02wdc.us.ibm.com (aa.5b.37a9.ip4.static.sl-reverse.com
 [169.55.91.170])
        by mx0b-001b2d01.pphosted.com with ESMTP id 33xaqmrb05-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 02 Oct 2020 16:06:37 -0400
Received: from pps.filterd (ppma02wdc.us.ibm.com [127.0.0.1])
        by ppma02wdc.us.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 092Jl8D5005732;
        Fri, 2 Oct 2020 20:06:36 GMT
Received: from b03cxnp08025.gho.boulder.ibm.com
 (b03cxnp08025.gho.boulder.ibm.com [9.17.130.17])
        by ppma02wdc.us.ibm.com with ESMTP id 33sw9a09g2-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 02 Oct 2020 20:06:36 +0000
Received: from b03ledav005.gho.boulder.ibm.com
 (b03ledav005.gho.boulder.ibm.com [9.17.130.236])
        by b03cxnp08025.gho.boulder.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 092K6VsO32833974
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 2 Oct 2020 20:06:31 GMT
Received: from b03ledav005.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 46D7FBE054;
        Fri,  2 Oct 2020 20:06:35 +0000 (GMT)
Received: from b03ledav005.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id F031BBE04F;
        Fri,  2 Oct 2020 20:06:33 +0000 (GMT)
Received: from oc4221205838.ibm.com (unknown [9.163.4.25])
        by b03ledav005.gho.boulder.ibm.com (Postfix) with ESMTP;
        Fri,  2 Oct 2020 20:06:33 +0000 (GMT)
From: Matthew Rosato <mjrosato@linux.ibm.com>
To: cohuck@redhat.com, thuth@redhat.com
Cc: pmorel@linux.ibm.com, schnelle@linux.ibm.com, rth@twiddle.net,
        david@redhat.com, pasic@linux.ibm.com, borntraeger@de.ibm.com,
        mst@redhat.com, pbonzini@redhat.com, alex.williamson@redhat.com,
        qemu-s390x@nongnu.org, qemu-devel@nongnu.org, kvm@vger.kernel.org
Subject: [PATCH v2 0/9] Retrieve zPCI hardware information from VFIO
Date: Fri,  2 Oct 2020 16:06:22 -0400
Message-Id: <1601669191-6731-1-git-send-email-mjrosato@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-10-02_14:2020-10-02,2020-10-02 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 bulkscore=0 impostorscore=0
 mlxlogscore=999 mlxscore=0 lowpriorityscore=0 adultscore=0
 priorityscore=1501 phishscore=0 malwarescore=0 spamscore=0 suspectscore=0
 clxscore=1015 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2010020142
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patchset exploits the VFIO ZPCI CLP region, which provides hardware
information about passed-through s390 PCI devices that can be shared with
the guest.

The retrieval of this information is done once per function (and for a
subset of data, once per function group) and is performed at time of device
plug.  Some elements provided in the CLP region must still be forced to
default values for now to reflect what QEMU actually provides support for.

The original work for this feature was done by Pierre Morel.

Associated kernel patchset:
https://lkml.org/lkml/2020/10/2/981

Changes from v1:
- Added 2 patches to the front of this set that move the s390-pci-bus.h and
  s390-pci-inst.h files to include + associated MAINTAINERS hit.  These
  can be applied separately, but are included here for the sake of
  simplicity.
- Patch 4: header update placeholder refreshed to rc7
- Patch 5: Move new s390-pci-clp.h to include folder
- Patch 6+: s/grp/group/ and fallout from this
- Patch 9: Move new s390-pci-vfio.h to include folder


Matthew Rosato (6):
  s390x/pci: Move header files to include/hw/s390x
  MAINTAINERS: Update s390 PCI entry to include headers
  update-linux-headers: Add vfio_zdev.h
  linux-headers: update against 5.9-rc7
  s390x/pci: clean up s390 PCI groups
  s390x/pci: get zPCI function info from host

Pierre Morel (3):
  s390x/pci: create a header dedicated to PCI CLP
  s390x/pci: use a PCI Group structure
  s390x/pci: use a PCI Function structure

 MAINTAINERS                                        |   1 +
 hw/s390x/meson.build                               |   1 +
 hw/s390x/s390-pci-bus.c                            |  86 ++++-
 hw/s390x/s390-pci-bus.h                            | 372 --------------------
 hw/s390x/s390-pci-inst.c                           |  33 +-
 hw/s390x/s390-pci-inst.h                           | 312 -----------------
 hw/s390x/s390-pci-vfio.c                           | 235 +++++++++++++
 hw/s390x/s390-virtio-ccw.c                         |   2 +-
 include/hw/s390x/s390-pci-bus.h                    | 385 +++++++++++++++++++++
 include/hw/s390x/s390-pci-clp.h                    | 215 ++++++++++++
 include/hw/s390x/s390-pci-inst.h                   | 116 +++++++
 include/hw/s390x/s390-pci-vfio.h                   |  19 +
 .../drivers/infiniband/hw/vmw_pvrdma/pvrdma_ring.h |  14 +-
 linux-headers/linux/kvm.h                          |   6 +-
 linux-headers/linux/vfio.h                         |   5 +
 scripts/update-linux-headers.sh                    |   2 +-
 16 files changed, 1085 insertions(+), 719 deletions(-)
 delete mode 100644 hw/s390x/s390-pci-bus.h
 delete mode 100644 hw/s390x/s390-pci-inst.h
 create mode 100644 hw/s390x/s390-pci-vfio.c
 create mode 100644 include/hw/s390x/s390-pci-bus.h
 create mode 100644 include/hw/s390x/s390-pci-clp.h
 create mode 100644 include/hw/s390x/s390-pci-inst.h
 create mode 100644 include/hw/s390x/s390-pci-vfio.h
```
