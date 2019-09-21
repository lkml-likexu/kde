

#### [RFC 0/2] kvm: Use host timekeeping in guest.
##### From: Suleiman Souhlal <suleiman@google.com>

```c
From patchwork Fri Sep 20 06:27:11 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Suleiman Souhlal <suleiman@google.com>
X-Patchwork-Id: 11153785
Return-Path: <SRS0=H7Z2=XP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 147FD76
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Sep 2019 06:27:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id DC8922173E
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Sep 2019 06:27:27 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="JYz0tgkq"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2394847AbfITG1Y (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 20 Sep 2019 02:27:24 -0400
Received: from mail-qk1-f201.google.com ([209.85.222.201]:55901 "EHLO
        mail-qk1-f201.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2393028AbfITG1Y (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 20 Sep 2019 02:27:24 -0400
Received: by mail-qk1-f201.google.com with SMTP id q80so6834417qke.22
        for <kvm@vger.kernel.org>; Thu, 19 Sep 2019 23:27:23 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=kndoGPsK6TO6IAqiWJAGc1exJ1qKbB/qTmt7yhIgp2A=;
        b=JYz0tgkqcjHYeFXGs5Jkl7ZHNM2Ki+xRUUbhi+Co1pWIqK2Rqoy5TkDvvpJ1jQ9eZS
         ZM93FmdRSdYmq/dqNzmeE//LcDslAmNWchBeD0VLVf5H+I/KUQevLfWnJu6s73dMnS5s
         OGUXUFXe8NM3iA4gIqi6vYO6gcWHC+zeZWytQi71ABPyMIUNz3pPkAM3FbR3OuNKybJe
         ia7FUXADvdzznFyTB3tU+qEMGiyyPfayVYvyZ2SRo9++8xPKE5dZovma8zsSJZCWWRKS
         B2/Jq0rfBSS4w1k087d0vW0FqPCn+dcwRkRwKVPoGQ3lFhU9+LK8rXGWEXLNpOhoJp5T
         aM1w==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=kndoGPsK6TO6IAqiWJAGc1exJ1qKbB/qTmt7yhIgp2A=;
        b=Bvr7Hty2hhaZhKaVgEyR93NONgmNWsa/6LH9pXlFGRy4tXQMB18Y0gpW50+kRk6CUM
         PuLJmGCsMVi/Z/H008sSNUt09baakjj8fK/zntZBK8N2gCiFAUn0epTR+u1S9FNcHcap
         koe8kC0ykCFGJUoy066X3HBNA0b7ULUTaT8VgM/kBX8dYGXTSgnntcrjfnQxquOM/A9T
         Qkpw/QroJB49MHHOb/kdj85z1nk/0DgYM1pCbc0tOgFPPu3q2rLkbyVFyEu7FZyG7xBd
         l6hA7uHbJM0an+Cz7wUynJU80g4yD7Sd75LR6ZNeBOPjmlubflvdvOpjGCLg2aLbR7FX
         cesw==
X-Gm-Message-State: APjAAAXs50fMxkXH/MKQLtXRpHFankEgf7dvCRk2wFPnhpeY6gGKWImU
        HvwEs/vlN6+RUs5B5IyLBNSD9haIBb8/Sg==
X-Google-Smtp-Source: 
 APXvYqw1JYvp88OxeYK0ycIQ0fMgenrGiZsTYURvNN1tTjKkuC+71gJsg7hD8TQ7bpIVzkxB3yhufPymfAFwQg==
X-Received: by 2002:aed:22cc:: with SMTP id q12mr1653867qtc.232.1568960842694;
 Thu, 19 Sep 2019 23:27:22 -0700 (PDT)
Date: Fri, 20 Sep 2019 15:27:11 +0900
Message-Id: <20190920062713.78503-1-suleiman@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.23.0.351.gc4317032e6-goog
Subject: [RFC 0/2] kvm: Use host timekeeping in guest.
From: Suleiman Souhlal <suleiman@google.com>
To: pbonzini@redhat.com, rkrcmar@redhat.com, tglx@linutronix.de
Cc: john.stultz@linaro.org, sboyd@kernel.org,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        Suleiman Souhlal <suleiman@google.com>
Content-Type: text/plain; charset="UTF-8"
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This RFC is to try to solve the following problem:

We have some applications that are currently running in their
own namespace, that still talk to other processes on the
machine, using IPC, and expect to run on the same machine.

We want to move them into a virtual machine, for the usual
benefits of virtualization.

However, some of these programs use CLOCK_MONOTONIC and 
CLOCK_BOOTTIME timestamps, as part of their protocol, when talking
to the host.

Generally speaking, we have multiple event sources, for example
sensors, input devices, display controller vsync, etc and we would
like to rely on them in the guest for various scenarios.

As a specific example, we are trying to run some wayland clients
(in the guest) who talk to the server (in the host), and the server
gives input events based on host time. Additionally, there are also
vsync events that the clients use for timing their rendering.

Another use case we have are timestamps from IIO sensors and cameras.
There are applications that need to determine how the timestamps
relate to the current time and the only way to get current time is
clock_gettime(), which would return a value from a different time
domain than the timestamps.

In this case, it is not feasible to change these programs, due to
the number of the places we would have to change.

We spent some time thinking about this, and the best solution we
could come up with was the following:

Make the guest kernel return the same CLOCK_MONOTONIC and
CLOCK_GETTIME timestamps as the host.

To do that, I am changing kvmclock to request to the host to copy
its timekeeping parameters (mult, base, cycle_last, etc), so that
the guest timekeeper can use the same values, so that time can
be synchronized between the guest and the host.

Any suggestions or feedback would be highly appreciated.

Suleiman Souhlal (2):
  kvm: Mechanism to copy host timekeeping parameters into guest.
  x86/kvmclock: Use host timekeeping.

 arch/x86/Kconfig                     |   9 ++
 arch/x86/include/asm/kvm_host.h      |   3 +
 arch/x86/include/asm/kvmclock.h      |   2 +
 arch/x86/include/asm/pvclock-abi.h   |  27 ++++++
 arch/x86/include/uapi/asm/kvm_para.h |   1 +
 arch/x86/kernel/kvmclock.c           | 127 ++++++++++++++++++++++++++-
 arch/x86/kvm/x86.c                   | 121 +++++++++++++++++++++++++
 kernel/time/timekeeping.c            |  21 +++++
 8 files changed, 307 insertions(+), 4 deletions(-)
```
#### [kvm-unit-tests PATCH v3 0/6] s390x: Add multiboot and smp
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
From patchwork Fri Sep 20 08:03:50 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11153971
Return-Path: <SRS0=H7Z2=XP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1C9471747
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Sep 2019 08:04:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 059BB21D6C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Sep 2019 08:04:18 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2437721AbfITIER (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 20 Sep 2019 04:04:17 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:8492 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S2437716AbfITIEQ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 20 Sep 2019 04:04:16 -0400
Received: from pps.filterd (m0098417.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 x8K7cHOV122253
        for <kvm@vger.kernel.org>; Fri, 20 Sep 2019 04:04:15 -0400
Received: from e06smtp04.uk.ibm.com (e06smtp04.uk.ibm.com [195.75.94.100])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2v4st1addx-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Fri, 20 Sep 2019 04:04:14 -0400
Received: from localhost
        by e06smtp04.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Fri, 20 Sep 2019 09:04:13 +0100
Received: from b06avi18626390.portsmouth.uk.ibm.com (9.149.26.192)
        by e06smtp04.uk.ibm.com (192.168.101.134) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Fri, 20 Sep 2019 09:04:11 +0100
Received: from d06av24.portsmouth.uk.ibm.com (d06av24.portsmouth.uk.ibm.com
 [9.149.105.60])
        by b06avi18626390.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id x8K83hCL25952520
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 20 Sep 2019 08:03:44 GMT
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 330E94204C;
        Fri, 20 Sep 2019 08:04:10 +0000 (GMT)
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id EF74342041;
        Fri, 20 Sep 2019 08:04:08 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.145.165.207])
        by d06av24.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Fri, 20 Sep 2019 08:04:08 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, david@redhat.com, thuth@redhat.com
Subject: [kvm-unit-tests PATCH v3 0/6] s390x: Add multiboot and smp
Date: Fri, 20 Sep 2019 10:03:50 +0200
X-Mailer: git-send-email 2.17.2
X-TM-AS-GCONF: 00
x-cbid: 19092008-0016-0000-0000-000002AE7409
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19092008-0017-0000-0000-0000330F272C
Message-Id: <20190920080356.1948-1-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-09-20_02:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=826 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1908290000 definitions=main-1909200077
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Cross testing emulated instructions has in the past brought up some
issues on all available IBM Z hypervisors. So let's upstream the last
part of multiboot: sclp interrupts and line mode console.

SMP tests are a great way to excercise external interruptions, cpu
resets and sigp. The smp library is always initialized and provides
very rudimentary CPU management for now.

v3:
 * Simplified linemode buffering
 * Removed error constant use
 * Smaller fixes

Janosch Frank (6):
  s390x: Use interrupts in SCLP and add locking
  s390x: Add linemode console
  s390x: Add linemode buffer to fix newline on every print
  s390x: Add initial smp code
  s390x: Prepare for external calls
  s390x: SMP test

 lib/s390x/asm/arch_def.h  |  13 ++
 lib/s390x/asm/interrupt.h |   5 +
 lib/s390x/asm/sigp.h      |  28 +++-
 lib/s390x/interrupt.c     |  27 +++-
 lib/s390x/io.c            |   5 +-
 lib/s390x/sclp-console.c  | 218 ++++++++++++++++++++++++++++---
 lib/s390x/sclp.c          |  55 +++++++-
 lib/s390x/sclp.h          |  59 ++++++++-
 lib/s390x/smp.c           | 263 ++++++++++++++++++++++++++++++++++++++
 lib/s390x/smp.h           |  51 ++++++++
 s390x/Makefile            |   2 +
 s390x/cstart64.S          |   7 +
 s390x/smp.c               | 242 +++++++++++++++++++++++++++++++++++
 s390x/unittests.cfg       |   4 +
 14 files changed, 952 insertions(+), 27 deletions(-)
 create mode 100644 lib/s390x/smp.c
 create mode 100644 lib/s390x/smp.h
 create mode 100644 s390x/smp.c
```
#### [RFC PATCH V2 0/6] mdev based hardware virtio offloading support
##### From: Jason Wang <jasowang@redhat.com>

```c
From patchwork Fri Sep 20 08:20:44 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 11153995
Return-Path: <SRS0=H7Z2=XP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9B83D14E5
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Sep 2019 08:22:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 847072190F
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Sep 2019 08:22:15 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2395214AbfITIWO (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 20 Sep 2019 04:22:14 -0400
Received: from mx1.redhat.com ([209.132.183.28]:42100 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2395207AbfITIWM (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 20 Sep 2019 04:22:12 -0400
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 9CC0410DCC9D;
        Fri, 20 Sep 2019 08:22:11 +0000 (UTC)
Received: from jason-ThinkPad-X1-Carbon-6th.redhat.com
 (ovpn-12-88.pek2.redhat.com [10.72.12.88])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 43D14101E67D;
        Fri, 20 Sep 2019 08:21:03 +0000 (UTC)
From: Jason Wang <jasowang@redhat.com>
To: kvm@vger.kernel.org, linux-s390@vger.kernel.org,
        linux-kernel@vger.kernel.org, dri-devel@lists.freedesktop.org,
        intel-gfx@lists.freedesktop.org,
        intel-gvt-dev@lists.freedesktop.org, kwankhede@nvidia.com,
        alex.williamson@redhat.com, mst@redhat.com, tiwei.bie@intel.com
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        cohuck@redhat.com, maxime.coquelin@redhat.com,
        cunming.liang@intel.com, zhihong.wang@intel.com,
        rob.miller@broadcom.com, xiao.w.wang@intel.com,
        haotian.wang@sifive.com, zhenyuw@linux.intel.com,
        zhi.a.wang@intel.com, jani.nikula@linux.intel.com,
        joonas.lahtinen@linux.intel.com, rodrigo.vivi@intel.com,
        airlied@linux.ie, daniel@ffwll.ch, farman@linux.ibm.com,
        pasic@linux.ibm.com, sebott@linux.ibm.com, oberpar@linux.ibm.com,
        heiko.carstens@de.ibm.com, gor@linux.ibm.com,
        borntraeger@de.ibm.com, akrowiak@linux.ibm.com,
        pmorel@linux.ibm.com, freude@linux.ibm.com, lingshan.zhu@intel.com,
        idos@mellanox.com, eperezma@redhat.com, lulu@redhat.com,
        Jason Wang <jasowang@redhat.com>
Subject: [RFC PATCH V2 0/6] mdev based hardware virtio offloading support
Date: Fri, 20 Sep 2019 16:20:44 +0800
Message-Id: <20190920082050.19352-1-jasowang@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.6.2 (mx1.redhat.com [10.5.110.64]);
 Fri, 20 Sep 2019 08:22:12 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all:

There are hardware that can do virtio datapath offloading while having
its own control path. This path tries to implement a mdev based
unified API to support using kernel virtio driver to drive those
devices. This is done by introducing a new mdev transport for virtio
(virtio_mdev) and register itself as a new kind of mdev driver. Then
it provides a unified way for kernel virtio driver to talk with mdev
device implementation.

Though the series only contain kernel driver support, the goal is to
make the transport generic enough to support userspace drivers. This
means vhost-mdev[1] could be built on top as well by resuing the
transport.

A sample driver is also implemented which simulate a virito-net
loopback ethernet device on top of vringh + workqueue. This could be
used as a reference implementation for real hardware driver.

Consider mdev framework only support VFIO device and driver right now,
this series also extend it to support other types. This is done
through introducing class id to the device and pairing it with
id_talbe claimed by the driver. On top, this seris also decouple
device specific parents ops out of the common ones.

Pktgen test was done with virito-net + mvnet loop back device.

Please review.

Changes from V1:

- rename device id to class id
- add docs for class id and device specific ops (device_ops)
- split device_ops into seperate headers
- drop the mdev_set_dma_ops()
- use device_ops to implement the transport API, then it's not a part
  of UAPI any more
- use GFP_ATOMIC in mvnet sample device and other tweaks
- set_vring_base/get_vring_base support for mvnet device

Jason Wang (6):
  mdev: class id support
  mdev: introduce device specific ops
  mdev: introduce virtio device and its device ops
  virtio: introudce a mdev based transport
  vringh: fix copy direction of vringh_iov_push_kern()
  docs: Sample driver to demonstrate how to implement virtio-mdev
    framework

 .../driver-api/vfio-mediated-device.rst       |  11 +-
 drivers/gpu/drm/i915/gvt/kvmgt.c              |  17 +-
 drivers/s390/cio/vfio_ccw_ops.c               |  17 +-
 drivers/s390/crypto/vfio_ap_ops.c             |  14 +-
 drivers/vfio/mdev/Kconfig                     |   7 +
 drivers/vfio/mdev/Makefile                    |   1 +
 drivers/vfio/mdev/mdev_core.c                 |  21 +-
 drivers/vfio/mdev/mdev_driver.c               |  14 +
 drivers/vfio/mdev/mdev_private.h              |   1 +
 drivers/vfio/mdev/vfio_mdev.c                 |  37 +-
 drivers/vfio/mdev/virtio_mdev.c               | 418 +++++++++++
 drivers/vhost/vringh.c                        |   8 +-
 include/linux/mdev.h                          |  46 +-
 include/linux/mod_devicetable.h               |   8 +
 include/linux/vfio_mdev.h                     |  50 ++
 include/linux/virtio_mdev.h                   | 141 ++++
 samples/Kconfig                               |   7 +
 samples/vfio-mdev/Makefile                    |   1 +
 samples/vfio-mdev/mbochs.c                    |  19 +-
 samples/vfio-mdev/mdpy.c                      |  19 +-
 samples/vfio-mdev/mtty.c                      |  17 +-
 samples/vfio-mdev/mvnet.c                     | 688 ++++++++++++++++++
 22 files changed, 1473 insertions(+), 89 deletions(-)
 create mode 100644 drivers/vfio/mdev/virtio_mdev.c
 create mode 100644 include/linux/vfio_mdev.h
 create mode 100644 include/linux/virtio_mdev.h
 create mode 100644 samples/vfio-mdev/mvnet.c
```
#### [PATCH 00/17] KVM monolithic v1
##### From: Andrea Arcangeli <aarcange@redhat.com>

```c
From patchwork Fri Sep 20 21:24:52 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrea Arcangeli <aarcange@redhat.com>
X-Patchwork-Id: 11154885
Return-Path: <SRS0=H7Z2=XP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DC0721599
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Sep 2019 21:26:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id C2F242173E
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Sep 2019 21:26:38 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2405358AbfITV0e (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 20 Sep 2019 17:26:34 -0400
Received: from mx1.redhat.com ([209.132.183.28]:59066 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1730152AbfITVZN (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 20 Sep 2019 17:25:13 -0400
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id B194E6412E;
        Fri, 20 Sep 2019 21:25:12 +0000 (UTC)
Received: from mail (ovpn-120-159.rdu2.redhat.com [10.10.120.159])
        by smtp.corp.redhat.com (Postfix) with ESMTPS id 1C10A5D9CD;
        Fri, 20 Sep 2019 21:25:10 +0000 (UTC)
From: Andrea Arcangeli <aarcange@redhat.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>,
        "Dr. David Alan Gilbert" <dgilbert@redhat.com>,
        Marcelo Tosatti <mtosatti@redhat.com>,
        Peter Xu <peterx@redhat.com>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH 00/17] KVM monolithic v1
Date: Fri, 20 Sep 2019 17:24:52 -0400
Message-Id: <20190920212509.2578-1-aarcange@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.5.16 (mx1.redhat.com [10.5.110.39]);
 Fri, 20 Sep 2019 21:25:12 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hello,

This patchset micro optimizes the vmexit to increase performance by
dropping the kvm.ko kernel module.

All common KVM code gets linked twice into kvm-intel and kvm-amd with
the only cons of using more disk space, but the pros of CPU (and RAM)
runtime benefits.

This improves the vmexit performance by two digits percent on
microbenchmarks with the spectre_v2 default mitigation on both VMX and
SVM. With spectre_v2=off or with CPUs with IBRS_ALL in
ARCH_CAPABILITIES this still improve performance but it's more of the
order of 1%.

We'll still have to deal with CPUs without IBRS_ALL for a decade and
reducing the vmexit latency is important to pass certain benchmarks
with workloads that happen to trigger frequent vmexits without having
to set spectre_v2=off in the host (which at least in theory would make
the host kernel vulnerable from a spectre v2 attack from the guest,
even through hyperthreading).

The first patch 1/17 should be splitted off from this series and it's
intended to be merged separately, it's included here only to avoid any
possible erroneous measurement if using kexec for testing, in turn if
using kexec it's recommended to include it in the baseline
measurements too.

A git clonable branch for quick testing is available here:

  https://git.kernel.org/pub/scm/linux/kernel/git/andrea/aa.git/log/?h=kvm-mono1

Thanks,
Andrea

Andrea Arcangeli (17):
  x86: spec_ctrl: fix SPEC_CTRL initialization after kexec
  KVM: monolithic: x86: convert the kvm_x86_ops methods to external
    functions
  KVM: monolithic: x86: handle the request_immediate_exit variation
  KVM: monolithic: x86: convert the kvm_pmu_ops methods to external
    functions
  KVM: monolithic: x86: enable the kvm_x86_ops external functions
  KVM: monolithic: x86: enable the kvm_pmu_ops external functions
  KVM: monolithic: x86: adjust the section prefixes
  KVM: monolithic: adjust the section prefixes in the KVM common code
  KVM: monolithic: x86: remove kvm.ko
  KVM: monolithic: x86: use the external functions instead of
    kvm_x86_ops
  KVM: monolithic: x86: remove exports
  KVM: monolithic: remove exports from KVM common code
  KVM: monolithic: x86: drop the kvm_pmu_ops structure
  KVM: monolithic: x86: inline more exit handlers in vmx.c
  KVM: retpolines: x86: eliminate retpoline from vmx.c exit handlers
  KVM: retpolines: x86: eliminate retpoline from svm.c exit handlers
  x86: retpolines: eliminate retpoline from msr event handlers

 arch/x86/events/intel/core.c     |  11 +
 arch/x86/include/asm/kvm_host.h  |  15 +-
 arch/x86/include/asm/kvm_ops.h   | 166 ++++++++
 arch/x86/include/asm/msr-index.h |   2 +
 arch/x86/kernel/cpu/bugs.c       |  20 +-
 arch/x86/kvm/Makefile            |   5 +-
 arch/x86/kvm/cpuid.c             |  27 +-
 arch/x86/kvm/hyperv.c            |   8 +-
 arch/x86/kvm/irq.c               |   4 -
 arch/x86/kvm/irq_comm.c          |   2 -
 arch/x86/kvm/kvm_cache_regs.h    |  10 +-
 arch/x86/kvm/lapic.c             |  44 +-
 arch/x86/kvm/mmu.c               |  50 +--
 arch/x86/kvm/mmu.h               |   4 +-
 arch/x86/kvm/mtrr.c              |   2 -
 arch/x86/kvm/pmu.c               |  27 +-
 arch/x86/kvm/pmu.h               |  21 +-
 arch/x86/kvm/pmu_amd.c           |  15 +-
 arch/x86/kvm/pmu_amd_ops.c       |  68 ++++
 arch/x86/kvm/pmu_ops.h           |  22 +
 arch/x86/kvm/svm.c               |  19 +-
 arch/x86/kvm/svm_ops.c           | 672 ++++++++++++++++++++++++++++++
 arch/x86/kvm/trace.h             |   4 +-
 arch/x86/kvm/vmx/pmu_intel.c     |  17 +-
 arch/x86/kvm/vmx/pmu_intel_ops.c |  68 ++++
 arch/x86/kvm/vmx/vmx.c           |  36 +-
 arch/x86/kvm/vmx/vmx_ops.c       | 675 +++++++++++++++++++++++++++++++
 arch/x86/kvm/x86.c               | 409 +++++++------------
 arch/x86/kvm/x86.h               |   2 +-
 virt/kvm/eventfd.c               |   1 -
 virt/kvm/kvm_main.c              |  71 +---
 31 files changed, 1982 insertions(+), 515 deletions(-)
 create mode 100644 arch/x86/include/asm/kvm_ops.h
 create mode 100644 arch/x86/kvm/pmu_amd_ops.c
 create mode 100644 arch/x86/kvm/pmu_ops.h
 create mode 100644 arch/x86/kvm/svm_ops.c
 create mode 100644 arch/x86/kvm/vmx/pmu_intel_ops.c
 create mode 100644 arch/x86/kvm/vmx/vmx_ops.c
```
