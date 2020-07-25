

#### [for-5.2 v4 00/10] Generalize memory encryption models
##### From: David Gibson <david@gibson.dropbear.id.au>

```c
From patchwork Fri Jul 24 02:57:34 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Gibson <david@gibson.dropbear.id.au>
X-Patchwork-Id: 11681929
Return-Path: <SRS0=BqhU=BD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E4214722
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Jul 2020 02:58:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CD256207FC
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Jul 2020 02:58:04 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=gibson.dropbear.id.au
 header.i=@gibson.dropbear.id.au header.b="C5PGevUJ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726957AbgGXC6D (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 23 Jul 2020 22:58:03 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:52374 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726784AbgGXC5u (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 23 Jul 2020 22:57:50 -0400
Received: from ozlabs.org (ozlabs.org [IPv6:2401:3900:2:1::2])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 78C3EC0619D3
        for <kvm@vger.kernel.org>; Thu, 23 Jul 2020 19:57:50 -0700 (PDT)
Received: by ozlabs.org (Postfix, from userid 1007)
        id 4BCYlv1BKjz9sRN; Fri, 24 Jul 2020 12:57:47 +1000 (AEST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple;
        d=gibson.dropbear.id.au; s=201602; t=1595559467;
        bh=g66FwVz1r6nGsK6XJ5UcsyTZuDIgWFh7d1+V/6AC+0I=;
        h=From:To:Cc:Subject:Date:From;
        b=C5PGevUJgzVOgAIu9G1YJhVIdy5YZzXT+TIXBMNYd8rze8zDPZv1/8gf29OGzcCak
         ATvVaZzSVokHz9AhNsJE1rtRAYtsBidm6G0Lzm0Tm4MbDJ8y+aiBC7OIzzEzqzEBN8
         qbj5gC930eEbwMu5xJee3GuQS/SvIHYplFgh53EY=
From: David Gibson <david@gibson.dropbear.id.au>
To: dgilbert@redhat.com, frankja@linux.ibm.com, pair@us.ibm.com,
        qemu-devel@nongnu.org, pbonzini@redhat.com, brijesh.singh@amd.com
Cc: ehabkost@redhat.com, marcel.apfelbaum@gmail.com,
 "Michael S. Tsirkin" <mst@redhat.com>, qemu-ppc@nongnu.org,
 kvm@vger.kernel.org, pasic@linux.ibm.com, qemu-s390x@nongnu.org,
 David Gibson <david@gibson.dropbear.id.au>,
 David Hildenbrand <david@redhat.com>,
 Christian Borntraeger <borntraeger@de.ibm.com>,
 Richard Henderson <rth@twiddle.net>,
 =?utf-8?q?Daniel_P=2E_Berrang=C3=A9?= <berrange@redhat.com>,
 mdroth@linux.vnet.ibm.com, Thomas Huth <thuth@redhat.com>,
 Cornelia Huck <cohuck@redhat.com>
Subject: [for-5.2 v4 00/10] Generalize memory encryption models
Date: Fri, 24 Jul 2020 12:57:34 +1000
Message-Id: <20200724025744.69644-1-david@gibson.dropbear.id.au>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

A number of hardware platforms are implementing mechanisms whereby the
hypervisor does not have unfettered access to guest memory, in order
to mitigate the security impact of a compromised hypervisor.

AMD's SEV implements this with in-cpu memory encryption, and Intel has
its own memory encryption mechanism.  POWER has an upcoming mechanism
to accomplish this in a different way, using a new memory protection
level plus a small trusted ultravisor.  s390 also has a protected
execution environment.

The current code (committed or draft) for these features has each
platform's version configured entirely differently.  That doesn't seem
ideal for users, or particularly for management layers.

AMD SEV introduces a notionally generic machine option
"machine-encryption", but it doesn't actually cover any cases other
than SEV.

This series is a proposal to at least partially unify configuration
for these mechanisms, by renaming and generalizing AMD's
"memory-encryption" property.  It is replaced by a
"host-trust-limitation" property pointing to a platform specific
object which configures and manages the specific details.

Please apply.

Changes since v3:
 * Rebased
 * Added first cut at handling of s390 protected virtualization
Changes since RFCv2:
 * Rebased
 * Removed preliminary SEV cleanups (they've been merged)
 * Changed name to "host trust limitation"
 * Added migration blocker to the PEF code (based on SEV's version)
Changes since RFCv1:
 * Rebased
 * Fixed some errors pointed out by Dave Gilbert

David Gibson (10):
  host trust limitation: Introduce new host trust limitation interface
  host trust limitation: Handle memory encryption via interface
  host trust limitation: Move side effect out of
    machine_set_memory_encryption()
  host trust limitation: Rework the "memory-encryption" property
  host trust limitation: Decouple kvm_memcrypt_*() helpers from KVM
  host trust limitation: Add Error ** to HostTrustLimitation::kvm_init
  spapr: Add PEF based host trust limitation
  spapr: PEF: block migration
  host trust limitation: Alter virtio default properties for protected
    guests
  s390: Recognize host-trust-limitation option

 accel/kvm/kvm-all.c                  |  40 ++------
 accel/kvm/sev-stub.c                 |   7 +-
 accel/stubs/kvm-stub.c               |  10 --
 backends/Makefile.objs               |   2 +
 backends/host-trust-limitation.c     |  29 ++++++
 hw/core/machine.c                    |  61 +++++++++--
 hw/i386/pc_sysfw.c                   |   6 +-
 hw/s390x/pv.c                        |  61 +++++++++++
 include/exec/host-trust-limitation.h |  72 +++++++++++++
 include/hw/boards.h                  |   2 +-
 include/qemu/typedefs.h              |   1 +
 include/sysemu/kvm.h                 |  17 ---
 include/sysemu/sev.h                 |   4 +-
 target/i386/sev.c                    | 148 ++++++++++++---------------
 target/ppc/Makefile.objs             |   2 +-
 target/ppc/pef.c                     |  89 ++++++++++++++++
 16 files changed, 387 insertions(+), 164 deletions(-)
 create mode 100644 backends/host-trust-limitation.c
 create mode 100644 include/exec/host-trust-limitation.h
 create mode 100644 target/ppc/pef.c
```
#### [PATCH v4 0/5] vfio/pci: add denylist and disable qat
##### From: Giovanni Cabiddu <giovanni.cabiddu@intel.com>

```c
From patchwork Fri Jul 24 08:47:55 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Giovanni Cabiddu <giovanni.cabiddu@intel.com>
X-Patchwork-Id: 11682673
Return-Path: <SRS0=BqhU=BD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0335913A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Jul 2020 08:48:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E8695206EB
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Jul 2020 08:48:13 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726863AbgGXIsK (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 24 Jul 2020 04:48:10 -0400
Received: from mga02.intel.com ([134.134.136.20]:45604 "EHLO mga02.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726554AbgGXIsJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 24 Jul 2020 04:48:09 -0400
IronPort-SDR: 
 sH6rwSAxZ1rS5Gvp09MhgJ+hBfsY/Jiulsyzzv04BQ+5NStcQtKtHTx+XR1EIUZHnP3Q+Uxas6
 F5B8HltMKMvw==
X-IronPort-AV: E=McAfee;i="6000,8403,9691"; a="138742736"
X-IronPort-AV: E=Sophos;i="5.75,390,1589266800";
   d="scan'208";a="138742736"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga004.fm.intel.com ([10.253.24.48])
  by orsmga101.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 24 Jul 2020 01:48:09 -0700
IronPort-SDR: 
 +Un+cSduj96ujc+RzGWhAE9vgnycKNK++XQWrcgHivKYO1MueFnzcalUZFyGf87nATYpUZltb8
 r1MhhKa+Uuyg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,390,1589266800";
   d="scan'208";a="311335253"
Received: from silpixa00400314.ir.intel.com (HELO
 silpixa00400314.ger.corp.intel.com) ([10.237.222.51])
  by fmsmga004.fm.intel.com with ESMTP; 24 Jul 2020 01:48:05 -0700
From: Giovanni Cabiddu <giovanni.cabiddu@intel.com>
To: alex.williamson@redhat.com, herbert@gondor.apana.org.au
Cc: cohuck@redhat.com, nhorman@redhat.com, vdronov@redhat.com,
        bhelgaas@google.com, mark.a.chambers@intel.com,
        gordon.mcfadden@intel.com, ahsan.atta@intel.com,
        fiona.trahe@intel.com, qat-linux@intel.com, kvm@vger.kernel.org,
        linux-crypto@vger.kernel.org, linux-pci@vger.kernel.org,
        linux-kernel@vger.kernel.org,
        Giovanni Cabiddu <giovanni.cabiddu@intel.com>
Subject: [PATCH v4 0/5] vfio/pci: add denylist and disable qat
Date: Fri, 24 Jul 2020 09:47:55 +0100
Message-Id: <20200724084800.6136-1-giovanni.cabiddu@intel.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patchset defines a denylist of devices in the vfio-pci module and adds
the current generation of Intel(R) QuickAssist devices to it as they are
not designed to run in an untrusted environment.

By default, if a device is in the denylist, the probe of vfio-pci fails.
If a user wants to use a device in the denylist, he needs to disable the
full denylist providing the option disable_denylist=1 at the load of
vfio-pci or specifying that parameter in a config file in /etc/modprobe.d.

This series also moves the device ids definitions present in the qat driver
to linux/pci_ids.h since they will be shared between the vfio-pci and the qat
drivers and replaces the custom ADF_SYSTEM_DEVICE macro with PCI_VDEVICE.

The series is applicable to Herbert's tree. Patches 1 to 3 apply also to
Alex's tree (next). Patches 4 and 5 are optional and can be applied at a later
stage.

Changes from v3:
 - Patch #1: included Acked-by tag, after ack from Bjorn Helgaas
 - Patch #2: s/prevents/allows/ in module parameter description

Changes from v2:
 - Renamed blocklist in denylist
 - Patch #2: reworded module parameter description to clarify why a device is
   in the denylist
 - Patch #2: reworded warning that occurs when denylist is enabled and device
   is present in that list

Changes from v1:
 - Reworked commit messages:
   Patches #1, #2 and #3: capitalized first character after column to comply to
   subject line convention
   Patch #3: Capitalized QAT acronym and added link and doc number for document
   "Intel® QuickAssist Technology (Intel® QAT) Software for Linux"

Giovanni Cabiddu (5):
  PCI: Add Intel QuickAssist device IDs
  vfio/pci: Add device denylist
  vfio/pci: Add QAT devices to denylist
  crypto: qat - replace device ids defines
  crypto: qat - use PCI_VDEVICE

 drivers/crypto/qat/qat_c3xxx/adf_drv.c        | 11 ++---
 drivers/crypto/qat/qat_c3xxxvf/adf_drv.c      | 11 ++---
 drivers/crypto/qat/qat_c62x/adf_drv.c         | 11 ++---
 drivers/crypto/qat/qat_c62xvf/adf_drv.c       | 11 ++---
 .../crypto/qat/qat_common/adf_accel_devices.h |  6 ---
 drivers/crypto/qat/qat_common/qat_hal.c       |  7 +--
 drivers/crypto/qat/qat_common/qat_uclo.c      |  9 ++--
 drivers/crypto/qat/qat_dh895xcc/adf_drv.c     | 11 ++---
 drivers/crypto/qat/qat_dh895xccvf/adf_drv.c   | 11 ++---
 drivers/vfio/pci/vfio_pci.c                   | 48 +++++++++++++++++++
 include/linux/pci_ids.h                       |  6 +++
 11 files changed, 87 insertions(+), 55 deletions(-)
Reviewed-by: Fiona Trahe <fiona.trahe@intel.com>
```
#### [RFC 0/2] Add risc-v vhost-net support
##### From: Yifei Jiang <jiangyifei@huawei.com>

```c
From patchwork Fri Jul 24 08:54:39 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yifei Jiang <jiangyifei@huawei.com>
X-Patchwork-Id: 11682733
Return-Path: <SRS0=BqhU=BD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 09C45913
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Jul 2020 08:55:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id EE20A2065C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Jul 2020 08:55:38 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726979AbgGXIzf (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 24 Jul 2020 04:55:35 -0400
Received: from szxga07-in.huawei.com ([45.249.212.35]:54784 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726554AbgGXIzf (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 24 Jul 2020 04:55:35 -0400
Received: from DGGEMS401-HUB.china.huawei.com (unknown [172.30.72.59])
        by Forcepoint Email with ESMTP id D3DA38FE8846B0F92B8C;
        Fri, 24 Jul 2020 16:55:33 +0800 (CST)
Received: from huawei.com (10.174.187.31) by DGGEMS401-HUB.china.huawei.com
 (10.3.19.201) with Microsoft SMTP Server id 14.3.487.0; Fri, 24 Jul 2020
 16:55:27 +0800
From: Yifei Jiang <jiangyifei@huawei.com>
To: <pbonzini@redhat.com>, <paul.walmsley@sifive.com>,
        <palmer@dabbelt.com>, <aou@eecs.berkeley.edu>
CC: <anup.patel@wdc.com>, <atish.patra@wdc.com>, <kvm@vger.kernel.org>,
        <kvm-riscv@lists.infradead.org>, <linux-riscv@lists.infradead.org>,
        <linux-kernel@vger.kernel.org>, <victor.zhangxiaofeng@huawei.com>,
        <wu.wubin@huawei.com>, <zhang.zhanghailiang@huawei.com>,
        <dengkai1@huawei.com>, <limingwang@huawei.com>,
        Yifei Jiang <jiangyifei@huawei.com>
Subject: [RFC 0/2] Add risc-v vhost-net support
Date: Fri, 24 Jul 2020 16:54:39 +0800
Message-ID: <20200724085441.1514-1-jiangyifei@huawei.com>
X-Mailer: git-send-email 2.26.2.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.187.31]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

These two patches enable support for vhost-net on RISC-V architecture. They are developed
based on the Linux source in this repo: https://github.com/avpatel/linux,
the branch is riscv_kvm_v13. 

The accompanying QEMU is from the repo: https://github.com/alistair23/qemu, the branch is
hyp-ext-v0.6.next. In order for the QEMU to work with KVM, the patch found here is necessary:
https://patchwork.kernel.org/cover/11435965/

Several steps to use this:

1. create virbr0 on riscv64 emulation
$ brctl addbr virbr0
$ brctl stp virbr0 on
$ ifconfig virbr0 up
$ ifconfig virbr0 <virbr0_ip> netmask <virbr0_netmask>

2. boot riscv64 guestOS on riscv64 emulation
$ ./qemu-system-riscv64 -M virt,accel=kvm -m 1024M -cpu host -nographic \
	-name guest=riscv-guest \
	-smp 2 \
	-kernel ./Image \
	-drive file=./guest.img,format=raw,id=hd0 \
	-device virtio-blk,drive=hd0 \
	-netdev type=tap,vhost=on,script=./ifup.sh,downscript=./ifdown.sh,id=net0 \
	-append "root=/dev/vda rw console=ttyS0 earlycon=sbi"

$ cat ifup.sh
#!/bin/sh
brctl addif virbr0 $1
ifconfig $1 up

$ cat ifdown.sh
#!/bin/sh
ifconfig $1 down
brctl delif virbr0 $1

This brenchmark is vhost-net compare with virtio:

$ ./netperf -H <virbr0_ip> -l 100 -t TCP_STREAM

vhost-net:
Recv   Send    Send                          
Socket Socket  Message  Elapsed              
Size   Size    Size     Time     Throughput  
bytes  bytes   bytes    secs.    10^6bits/sec  

131072  16384  16384    100.07    457.55

virtio:
Recv   Send    Send                          
Socket Socket  Message  Elapsed              
Size   Size    Size     Time     Throughput  
bytes  bytes   bytes    secs.    10^6bits/sec  

131072  16384  16384    100.07    227.02


The next step is to support irqfd on RISC-V architecture.

Yifei Jiang (2):
  RISC-V: KVM: enable ioeventfd capability and compile for risc-v
  RISC-V: KVM: read\write kernel mmio device support

 arch/riscv/kvm/Kconfig     |  2 ++
 arch/riscv/kvm/Makefile    |  2 +-
 arch/riscv/kvm/vcpu_exit.c | 38 ++++++++++++++++++++++++++++++++------
 arch/riscv/kvm/vm.c        |  1 +
 4 files changed, 36 insertions(+), 7 deletions(-)
```
#### [PATCH v5 0/5] vfio/pci: add denylist and disable qat
##### From: Giovanni Cabiddu <giovanni.cabiddu@intel.com>

```c
From patchwork Fri Jul 24 10:55:55 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Giovanni Cabiddu <giovanni.cabiddu@intel.com>
X-Patchwork-Id: 11682995
Return-Path: <SRS0=BqhU=BD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A0DA0138A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Jul 2020 10:56:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9099520768
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Jul 2020 10:56:14 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726812AbgGXK4L (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 24 Jul 2020 06:56:11 -0400
Received: from mga03.intel.com ([134.134.136.65]:6908 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726258AbgGXK4L (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 24 Jul 2020 06:56:11 -0400
IronPort-SDR: 
 9L1TGkqDiJZDjwESrL5beZ8CA2jFxy40TSiiqXXNI6abRbYmgN/nraxvPNslXYsYlvEEw0+ivb
 Kuw34WTHJL2g==
X-IronPort-AV: E=McAfee;i="6000,8403,9691"; a="150675010"
X-IronPort-AV: E=Sophos;i="5.75,390,1589266800";
   d="scan'208";a="150675010"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga003.jf.intel.com ([10.7.209.27])
  by orsmga103.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 24 Jul 2020 03:56:10 -0700
IronPort-SDR: 
 2tisJ6WPrHiElX4vifb4Xa+qD7K0tawdKTHfz5RL1+5+CZdqOn4YpC7SW6EmyCm1/+1fJj5g/6
 5DLjkbgOcpaw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,390,1589266800";
   d="scan'208";a="284901497"
Received: from silpixa00400314.ir.intel.com (HELO
 silpixa00400314.ger.corp.intel.com) ([10.237.222.51])
  by orsmga003.jf.intel.com with ESMTP; 24 Jul 2020 03:56:07 -0700
From: Giovanni Cabiddu <giovanni.cabiddu@intel.com>
To: alex.williamson@redhat.com, herbert@gondor.apana.org.au
Cc: cohuck@redhat.com, nhorman@redhat.com, vdronov@redhat.com,
        bhelgaas@google.com, mark.a.chambers@intel.com,
        gordon.mcfadden@intel.com, ahsan.atta@intel.com,
        fiona.trahe@intel.com, qat-linux@intel.com, kvm@vger.kernel.org,
        linux-crypto@vger.kernel.org, linux-pci@vger.kernel.org,
        linux-kernel@vger.kernel.org,
        Giovanni Cabiddu <giovanni.cabiddu@intel.com>
Subject: [PATCH v5 0/5] vfio/pci: add denylist and disable qat
Date: Fri, 24 Jul 2020 11:55:55 +0100
Message-Id: <20200724105600.10814-1-giovanni.cabiddu@intel.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patchset defines a denylist of devices in the vfio-pci module and adds
the current generation of Intel(R) QuickAssist devices to it as they are
not designed to run in an untrusted environment.

By default, if a device is in the denylist, the probe of vfio-pci fails.
If a user wants to use a device in the denylist, he needs to disable the
full denylist providing the option disable_denylist=1 at the load of
vfio-pci or specifying that parameter in a config file in /etc/modprobe.d.

This series also moves the device ids definitions present in the qat driver
to linux/pci_ids.h since they will be shared between the vfio-pci and the qat
drivers and replaces the custom ADF_SYSTEM_DEVICE macro with PCI_VDEVICE.

The series is applicable to Herbert's tree. Patches 1 to 3 apply also to
Alex's tree (next). Patches 4 and 5 are optional and can be applied at a later
stage.

Changes from v4:
 - Patch #2: added Reviewed-by tag from Cornelia Huck
 - Patch #5: added Suggested-by tag as this change was suggested internally
   by Andy Shevchenko
 - Patches 1-5: added Reviewed-by tag from Fiona Trahe

Changes from v3:
 - Patch #1: included Acked-by tag, after ack from Bjorn Helgaas
 - Patch #2: s/prevents/allows/ in module parameter description

Changes from v2:
 - Renamed blocklist in denylist
 - Patch #2: reworded module parameter description to clarify why a device is
   in the denylist
 - Patch #2: reworded warning that occurs when denylist is enabled and device
   is present in that list

Changes from v1:
 - Reworked commit messages:
   Patches #1, #2 and #3: capitalized first character after column to comply to
   subject line convention
   Patch #3: Capitalized QAT acronym and added link and doc number for document
   "Intel® QuickAssist Technology (Intel® QAT) Software for Linux"


Giovanni Cabiddu (5):
  PCI: Add Intel QuickAssist device IDs
  vfio/pci: Add device denylist
  vfio/pci: Add QAT devices to denylist
  crypto: qat - replace device ids defines
  crypto: qat - use PCI_VDEVICE

 drivers/crypto/qat/qat_c3xxx/adf_drv.c        | 11 ++---
 drivers/crypto/qat/qat_c3xxxvf/adf_drv.c      | 11 ++---
 drivers/crypto/qat/qat_c62x/adf_drv.c         | 11 ++---
 drivers/crypto/qat/qat_c62xvf/adf_drv.c       | 11 ++---
 .../crypto/qat/qat_common/adf_accel_devices.h |  6 ---
 drivers/crypto/qat/qat_common/qat_hal.c       |  7 +--
 drivers/crypto/qat/qat_common/qat_uclo.c      |  9 ++--
 drivers/crypto/qat/qat_dh895xcc/adf_drv.c     | 11 ++---
 drivers/crypto/qat/qat_dh895xccvf/adf_drv.c   | 11 ++---
 drivers/vfio/pci/vfio_pci.c                   | 48 +++++++++++++++++++
 include/linux/pci_ids.h                       |  6 +++
 11 files changed, 87 insertions(+), 55 deletions(-)
Reviewed-by: Andy Shevchenko <andy.shevchenko@gmail.com>
```
#### [PATCH v5 00/75] x86: SEV-ES Guest Support
##### From: Joerg Roedel <joro@8bytes.org>
From: Joerg Roedel <jroedel@suse.de>

```c
From patchwork Fri Jul 24 16:02:21 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Joerg Roedel <joro@8bytes.org>
X-Patchwork-Id: 11683723
Return-Path: <SRS0=BqhU=BD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EE444618
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Jul 2020 16:11:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DAD6C206F0
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Jul 2020 16:11:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726692AbgGXQD6 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 24 Jul 2020 12:03:58 -0400
Received: from 8bytes.org ([81.169.241.247]:59162 "EHLO theia.8bytes.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726326AbgGXQD6 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 24 Jul 2020 12:03:58 -0400
Received: from cap.home.8bytes.org (p5b006776.dip0.t-ipconnect.de
 [91.0.103.118])
        (using TLSv1.3 with cipher TLS_AES_256_GCM_SHA384 (256/256 bits))
        (No client certificate requested)
        by theia.8bytes.org (Postfix) with ESMTPSA id 1963A272;
        Fri, 24 Jul 2020 18:03:56 +0200 (CEST)
From: Joerg Roedel <joro@8bytes.org>
To: x86@kernel.org
Cc: Joerg Roedel <joro@8bytes.org>, Joerg Roedel <jroedel@suse.de>,
        hpa@zytor.com, Andy Lutomirski <luto@kernel.org>,
        Dave Hansen <dave.hansen@linux.intel.com>,
        Peter Zijlstra <peterz@infradead.org>,
        Jiri Slaby <jslaby@suse.cz>,
        Dan Williams <dan.j.williams@intel.com>,
        Tom Lendacky <thomas.lendacky@amd.com>,
        Juergen Gross <jgross@suse.com>,
        Kees Cook <keescook@chromium.org>,
        David Rientjes <rientjes@google.com>,
        Cfir Cohen <cfir@google.com>,
        Erdem Aktas <erdemaktas@google.com>,
        Masami Hiramatsu <mhiramat@kernel.org>,
        Mike Stunes <mstunes@vmware.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Martin Radev <martin.b.radev@gmail.com>,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org
Subject: [PATCH v5 00/75] x86: SEV-ES Guest Support
Date: Fri, 24 Jul 2020 18:02:21 +0200
Message-Id: <20200724160336.5435-1-joro@8bytes.org>
X-Mailer: git-send-email 2.27.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Joerg Roedel <jroedel@suse.de>

Hi,

here is a rebased version of the latest SEV-ES patches. They are now
based on latest tip/master instead of upstream Linux and include the
necessary changes.

Changes to v4 are in particular:

	- Moved early IDT setup code to idt.c, because the idt_descr
	  and the idt_table are now static

	- This required to make stack protector work early (or disable
	  it for idt.c, but I didn't go that road), so MSR_GS_BASE is
	  now set up very early too, before calling into any C code that
	  has stack protector checks.

	- As a result I decided to move the setup code which is needed
	  before the kernel switches to virtual addresses into a C
	  function as well. This should be much easier to maintain.

	- paranoid_entry/exit now uses FSGSBASE instructions, so some
	  refactoring was needed to make that work early for secondary
	  CPUs too.

	- As a result, some state of the APs is now set up on the
	  boot-cpu already, like the TSS and the CPU_NODE GDT entry,
	  so that the AP only needs to load the descriptors to handle
	  exceptions early.

The previous versions can be found as a linked-list starting here:

	https://lore.kernel.org/lkml/20200714120917.11253-1-joro@8bytes.org/

There you also find more detailed information about SEV-ES in general
and its implications.

Please review.

Thanks,

	Joerg

Borislav Petkov (1):
  KVM: SVM: Use __packed shorthand

Doug Covelli (1):
  x86/vmware: Add VMware specific handling for VMMCALL under SEV-ES

Joerg Roedel (53):
  KVM: SVM: Add GHCB Accessor functions
  x86/traps: Move pf error codes to <asm/trap_pf.h>
  x86/insn: Make inat-tables.c suitable for pre-decompression code
  x86/umip: Factor out instruction fetch
  x86/umip: Factor out instruction decoding
  x86/insn: Add insn_get_modrm_reg_off()
  x86/insn: Add insn_has_rep_prefix() helper
  x86/boot/compressed/64: Disable red-zone usage
  x86/boot/compressed/64: Add IDT Infrastructure
  x86/boot/compressed/64: Rename kaslr_64.c to ident_map_64.c
  x86/boot/compressed/64: Add page-fault handler
  x86/boot/compressed/64: Always switch to own page-table
  x86/boot/compressed/64: Don't pre-map memory in KASLR code
  x86/boot/compressed/64: Change add_identity_map() to take start and
    end
  x86/boot/compressed/64: Add stage1 #VC handler
  x86/boot/compressed/64: Call set_sev_encryption_mask earlier
  x86/boot/compressed/64: Check return value of
    kernel_ident_mapping_init()
  x86/boot/compressed/64: Add set_page_en/decrypted() helpers
  x86/boot/compressed/64: Setup GHCB Based VC Exception handler
  x86/boot/compressed/64: Unmap GHCB page before booting the kernel
  x86/fpu: Move xgetbv()/xsetbv() into separate header
  x86/idt: Move IDT to data segment
  x86/idt: Split idt_data setup out of set_intr_gate()
  x86/head/64: Install startup GDT
  x86/head/64: Setup MSR_GS_BASE before calling into C code
  x86/head/64: Load GDT after switch to virtual addresses
  x86/head/64: Load segment registers earlier
  x86/head/64: Switch to initial stack earlier
  x86/head/64: Make fixup_pointer() static inline
  x86/head/64: Load IDT earlier
  x86/head/64: Move early exception dispatch to C code
  x86/head/64: Set CR4.FSGSBASE early
  x86/sev-es: Add SEV-ES Feature Detection
  x86/sev-es: Print SEV-ES info into kernel log
  x86/sev-es: Compile early handler code into kernel image
  x86/sev-es: Setup early #VC handler
  x86/sev-es: Setup GHCB based boot #VC handler
  x86/sev-es: Allocate and Map IST stack for #VC handler
  x86/sev-es: Adjust #VC IST Stack on entering NMI handler
  x86/dumpstack/64: Add noinstr version of get_stack_info()
  x86/entry/64: Add entry code for #VC handler
  x86/sev-es: Wire up existing #VC exit-code handlers
  x86/sev-es: Handle instruction fetches from user-space
  x86/sev-es: Handle MMIO String Instructions
  x86/sev-es: Handle #AC Events
  x86/sev-es: Handle #DB Events
  x86/paravirt: Allow hypervisor specific VMMCALL handling under SEV-ES
  x86/realmode: Add SEV-ES specific trampoline entry point
  x86/smpboot: Setup TSS for starting AP
  x86/head/64: Don't call verify_cpu() on starting APs
  x86/head/64: Rename start_cpu0
  x86/sev-es: Support CPU offline/online
  x86/sev-es: Handle NMI State

Martin Radev (1):
  x86/sev-es: Check required CPU features for SEV-ES

Tom Lendacky (19):
  KVM: SVM: Add GHCB definitions
  x86/cpufeatures: Add SEV-ES CPU feature
  x86/sev-es: Add support for handling IOIO exceptions
  x86/sev-es: Add CPUID handling to #VC handler
  x86/sev-es: Setup per-cpu GHCBs for the runtime handler
  x86/sev-es: Add Runtime #VC Exception Handler
  x86/sev-es: Handle MMIO events
  x86/sev-es: Handle MSR events
  x86/sev-es: Handle DR7 read/write events
  x86/sev-es: Handle WBINVD Events
  x86/sev-es: Handle RDTSC(P) Events
  x86/sev-es: Handle RDPMC Events
  x86/sev-es: Handle INVD Events
  x86/sev-es: Handle MONITOR/MONITORX Events
  x86/sev-es: Handle MWAIT/MWAITX Events
  x86/sev-es: Handle VMMCALL Events
  x86/kvm: Add KVM specific VMMCALL handling under SEV-ES
  x86/realmode: Setup AP jump table
  x86/efi: Add GHCB mappings when SEV-ES is active

 arch/x86/Kconfig                           |    1 +
 arch/x86/boot/Makefile                     |    2 +-
 arch/x86/boot/compressed/Makefile          |    9 +-
 arch/x86/boot/compressed/cpuflags.c        |    4 -
 arch/x86/boot/compressed/head_64.S         |   32 +-
 arch/x86/boot/compressed/ident_map_64.c    |  349 +++++
 arch/x86/boot/compressed/idt_64.c          |   54 +
 arch/x86/boot/compressed/idt_handlers_64.S |   77 ++
 arch/x86/boot/compressed/kaslr.c           |   36 +-
 arch/x86/boot/compressed/kaslr_64.c        |  153 ---
 arch/x86/boot/compressed/misc.c            |    7 +
 arch/x86/boot/compressed/misc.h            |   50 +-
 arch/x86/boot/compressed/sev-es.c          |  214 +++
 arch/x86/entry/entry_64.S                  |   78 ++
 arch/x86/include/asm/cpu.h                 |    2 +-
 arch/x86/include/asm/cpu_entry_area.h      |   33 +-
 arch/x86/include/asm/cpufeatures.h         |    1 +
 arch/x86/include/asm/desc_defs.h           |    3 +
 arch/x86/include/asm/fpu/internal.h        |   33 +-
 arch/x86/include/asm/fpu/xcr.h             |   37 +
 arch/x86/include/asm/idtentry.h            |   49 +
 arch/x86/include/asm/insn-eval.h           |    6 +
 arch/x86/include/asm/mem_encrypt.h         |    5 +
 arch/x86/include/asm/msr-index.h           |    3 +
 arch/x86/include/asm/page_64_types.h       |    1 +
 arch/x86/include/asm/pgtable.h             |    2 +-
 arch/x86/include/asm/processor.h           |    7 +
 arch/x86/include/asm/proto.h               |    1 +
 arch/x86/include/asm/realmode.h            |    4 +
 arch/x86/include/asm/segment.h             |    2 +-
 arch/x86/include/asm/setup.h               |   16 +-
 arch/x86/include/asm/sev-es.h              |  113 ++
 arch/x86/include/asm/stacktrace.h          |    2 +
 arch/x86/include/asm/svm.h                 |  118 +-
 arch/x86/include/asm/trap_pf.h             |   24 +
 arch/x86/include/asm/trapnr.h              |    1 +
 arch/x86/include/asm/traps.h               |   20 +-
 arch/x86/include/asm/x86_init.h            |   16 +-
 arch/x86/include/uapi/asm/svm.h            |   11 +
 arch/x86/kernel/Makefile                   |    1 +
 arch/x86/kernel/cpu/amd.c                  |    3 +-
 arch/x86/kernel/cpu/common.c               |   37 +-
 arch/x86/kernel/cpu/scattered.c            |    1 +
 arch/x86/kernel/cpu/vmware.c               |   50 +-
 arch/x86/kernel/dumpstack.c                |    7 +-
 arch/x86/kernel/dumpstack_64.c             |   47 +-
 arch/x86/kernel/head64.c                   |   85 +-
 arch/x86/kernel/head_32.S                  |    4 +-
 arch/x86/kernel/head_64.S                  |  159 ++-
 arch/x86/kernel/idt.c                      |   94 +-
 arch/x86/kernel/kvm.c                      |   35 +-
 arch/x86/kernel/nmi.c                      |   12 +
 arch/x86/kernel/sev-es-shared.c            |  507 +++++++
 arch/x86/kernel/sev-es.c                   | 1404 ++++++++++++++++++++
 arch/x86/kernel/smpboot.c                  |   10 +-
 arch/x86/kernel/traps.c                    |   56 +
 arch/x86/kernel/umip.c                     |   49 +-
 arch/x86/kvm/svm/svm.c                     |    2 +
 arch/x86/lib/insn-eval.c                   |  130 ++
 arch/x86/mm/cpu_entry_area.c               |    3 +-
 arch/x86/mm/extable.c                      |    1 +
 arch/x86/mm/mem_encrypt.c                  |   38 +-
 arch/x86/mm/mem_encrypt_identity.c         |    3 +
 arch/x86/platform/efi/efi_64.c             |   10 +
 arch/x86/realmode/init.c                   |   24 +-
 arch/x86/realmode/rm/header.S              |    3 +
 arch/x86/realmode/rm/trampoline_64.S       |   20 +
 arch/x86/tools/gen-insn-attr-x86.awk       |   50 +-
 tools/arch/x86/tools/gen-insn-attr-x86.awk |   50 +-
 69 files changed, 4025 insertions(+), 446 deletions(-)
 create mode 100644 arch/x86/boot/compressed/ident_map_64.c
 create mode 100644 arch/x86/boot/compressed/idt_64.c
 create mode 100644 arch/x86/boot/compressed/idt_handlers_64.S
 delete mode 100644 arch/x86/boot/compressed/kaslr_64.c
 create mode 100644 arch/x86/boot/compressed/sev-es.c
 create mode 100644 arch/x86/include/asm/fpu/xcr.h
 create mode 100644 arch/x86/include/asm/sev-es.h
 create mode 100644 arch/x86/include/asm/trap_pf.h
 create mode 100644 arch/x86/kernel/sev-es-shared.c
 create mode 100644 arch/x86/kernel/sev-es.c
```
