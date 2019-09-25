

#### [PATCH v6 0/6] Deliver vGPU display refresh event to userspace
##### From: Tina Zhang <tina.zhang@intel.com>

```c
From patchwork Tue Sep 24 06:41:37 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tina Zhang <tina.zhang@intel.com>
X-Patchwork-Id: 11157989
Return-Path: <SRS0=xKXW=XT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BAB9C14E5
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 24 Sep 2019 06:43:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A3E63214DA
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 24 Sep 2019 06:43:51 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2440556AbfIXGnG (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 24 Sep 2019 02:43:06 -0400
Received: from mga02.intel.com ([134.134.136.20]:25186 "EHLO mga02.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2394281AbfIXGnG (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 24 Sep 2019 02:43:06 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by orsmga101.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 23 Sep 2019 23:43:05 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.64,543,1559545200";
   d="scan'208";a="203306293"
Received: from gvt.bj.intel.com ([10.238.158.180])
  by fmsmga001.fm.intel.com with ESMTP; 23 Sep 2019 23:43:02 -0700
From: Tina Zhang <tina.zhang@intel.com>
To: intel-gvt-dev@lists.freedesktop.org, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Cc: Tina Zhang <tina.zhang@intel.com>, kraxel@redhat.com,
        zhenyuw@linux.intel.com, zhiyuan.lv@intel.com,
        zhi.a.wang@intel.com, kevin.tian@intel.com, hang.yuan@intel.com,
        alex.williamson@redhat.com, yi.l.liu@intel.com
Subject: [PATCH v6 0/6] Deliver vGPU display refresh event to userspace
Date: Tue, 24 Sep 2019 14:41:37 +0800
Message-Id: <20190924064143.9282-1-tina.zhang@intel.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series sends the vGPU display refresh events to user land. A vGPU
display IRQ is proposed to notify user space with all the display
updates events.  With this IRQ supported by vendor driver, user space
can stop the display update timer and fully depend on getting the
notification if an update is needed.

How does gvt-g provide the vGPU display refresh IRQ covering all the
display update events?

Instead of delivering page flip events only or vblank events only, we
choose to combine two of them, i.e. post display refresh event at
vblanks and skip some of them when no page flip happens. Vblanks as
upper bound are safe and skipping no-page-flip vblanks guarantees both
trivial performance impacts and good user experience without screen
tearing. Plus, we have the mask/unmask mechansim providing user space
flexibility to switch between event-notified refresh and classic
timer-based refresh.

In addition, there are some cases that guest app only uses one
framebuffer for both drawing and display. In such case, guest OS won't
do the plane page flip when the framebuffer is updated, thus the user
land won't be notified about the updated framebuffer. Hence, in single
framebuffer case, we apply a heuristic to determine whether it is the
case or not. If it is, notify user land when each vblank event
triggers.

v6:
- Add more description to VFIO_IRQ_SUBTYPE_GFX_DISPLAY_IRQ and
  VFIO_IRQ_INFO_CAP_DISPLAY. (Alex & Gerd)
- Irq capability index starts from 1
v5:
- Introduce a vGPU display irq cap which can notify user space with
  both primary and cursor plane update events through one eventfd. (Gerd & Alex)
v4:
- Deliver page flip event and single framebuffer refresh event bounded 
by display vblanks. (Kechen)
v3:
- Deliver display vblank event instead of page flip event. (Zhenyu)
v2:
- Use VFIO irq chain to get eventfds from userspace instead of adding
a new ABI. (Alex)
v1:
- https://patchwork.kernel.org/cover/10962341/

Kechen Lu (2):
  drm/i915/gvt: Deliver async primary plane page flip events at vblank
  drm/i915/gvt: Add cursor plane reg update trap emulation handler

Tina Zhang (4):
  vfio: Define device specific irq type capability
  vfio: Introduce vGPU display irq type
  drm/i915/gvt: Register vGPU display event irq
  drm/i915/gvt: Deliver vGPU refresh event to userspace

 drivers/gpu/drm/i915/gvt/cmd_parser.c |   6 +-
 drivers/gpu/drm/i915/gvt/display.c    |  47 +++++-
 drivers/gpu/drm/i915/gvt/display.h    |   3 +
 drivers/gpu/drm/i915/gvt/gvt.h        |   7 +
 drivers/gpu/drm/i915/gvt/handlers.c   |  32 +++-
 drivers/gpu/drm/i915/gvt/hypercall.h  |   1 +
 drivers/gpu/drm/i915/gvt/interrupt.c  |   7 +
 drivers/gpu/drm/i915/gvt/interrupt.h  |   3 +
 drivers/gpu/drm/i915/gvt/kvmgt.c      | 230 +++++++++++++++++++++++++-
 drivers/gpu/drm/i915/gvt/mpt.h        |  17 ++
 include/uapi/linux/vfio.h             |  57 ++++++-
 11 files changed, 391 insertions(+), 19 deletions(-)
```
#### [PATCH v4 0/8] Introduce the microvm machine type
##### From: Sergio Lopez <slp@redhat.com>

```c
From patchwork Tue Sep 24 12:44:25 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sergio Lopez <slp@redhat.com>
X-Patchwork-Id: 11158635
Return-Path: <SRS0=xKXW=XT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 270981599
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 24 Sep 2019 12:45:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 0674B21655
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 24 Sep 2019 12:45:06 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729513AbfIXMpF (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 24 Sep 2019 08:45:05 -0400
Received: from mx1.redhat.com ([209.132.183.28]:47588 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729455AbfIXMpE (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 24 Sep 2019 08:45:04 -0400
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 29B7518C37B;
        Tue, 24 Sep 2019 12:45:04 +0000 (UTC)
Received: from dritchie.redhat.com (unknown [10.33.36.128])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 87B0D60852;
        Tue, 24 Sep 2019 12:44:50 +0000 (UTC)
From: Sergio Lopez <slp@redhat.com>
To: qemu-devel@nongnu.org
Cc: mst@redhat.com, imammedo@redhat.com, marcel.apfelbaum@gmail.com,
        pbonzini@redhat.com, rth@twiddle.net, ehabkost@redhat.com,
        philmd@redhat.com, lersek@redhat.com, kraxel@redhat.com,
        mtosatti@redhat.com, kvm@vger.kernel.org,
        Sergio Lopez <slp@redhat.com>
Subject: [PATCH v4 0/8] Introduce the microvm machine type
Date: Tue, 24 Sep 2019 14:44:25 +0200
Message-Id: <20190924124433.96810-1-slp@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.5.16 (mx1.redhat.com [10.5.110.29]);
 Tue, 24 Sep 2019 12:45:04 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Microvm is a machine type inspired by both NEMU and Firecracker, and
constructed after the machine model implemented by the latter.

It's main purpose is providing users a minimalist machine type free
from the burden of legacy compatibility, serving as a stepping stone
for future projects aiming at improving boot times, reducing the
attack surface and slimming down QEMU's footprint.

The microvm machine type supports the following devices:

 - ISA bus
 - i8259 PIC
 - LAPIC (implicit if using KVM)
 - IOAPIC (defaults to kernel_irqchip_split = true)
 - i8254 PIT
 - MC146818 RTC (optional)
 - kvmclock (if using KVM)
 - fw_cfg
 - One ISA serial port (optional)
 - Up to eight virtio-mmio devices (configured by the user)

It supports the following machine-specific options:

microvm.option-roms=bool (Set off to disable loading option ROMs)
microvm.isa-serial=bool (Set off to disable the instantiation an ISA serial port)
microvm.rtc=bool (Set off to disable the instantiation of an MC146818 RTC)
microvm.kernel-cmdline=bool (Set off to disable adding virtio-mmio devices to the kernel cmdline)

By default, microvm uses qboot as its BIOS, to obtain better boot
times, but it's also compatible with SeaBIOS.

As no current FW is able to boot from a block device using virtio-mmio
as its transport, a microvm-based VM needs to be run using a host-side
kernel and, optionally, an initrd image.

This is an example of instantiating a microvm VM with a virtio-mmio
based console:

qemu-system-x86_64 -M microvm
 -enable-kvm -cpu host -m 512m -smp 2 \
 -kernel vmlinux -append "console=hvc0 root=/dev/vda" \
 -nodefaults -no-user-config -nographic \
 -chardev stdio,id=virtiocon0,server \
 -device virtio-serial-device \
 -device virtconsole,chardev=virtiocon0 \
 -drive id=test,file=test.img,format=raw,if=none \
 -device virtio-blk-device,drive=test \
 -netdev tap,id=tap0,script=no,downscript=no \
 -device virtio-net-device,netdev=tap0

This is another example, this time using an ISA serial port, useful
for debugging purposes:

qemu-system-x86_64 -M microvm \
 -enable-kvm -cpu host -m 512m -smp 2 \
 -kernel vmlinux -append "earlyprintk=ttyS0 console=ttyS0 root=/dev/vda" \
 -nodefaults -no-user-config -nographic \
 -serial stdio \
 -drive id=test,file=test.img,format=raw,if=none \
 -device virtio-blk-device,drive=test \
 -netdev tap,id=tap0,script=no,downscript=no \
 -device virtio-net-device,netdev=tap0

Finally, in this example a microvm VM is instantiated without RTC,
without an ISA serial port and without loading the option ROMs,
obtaining the smallest configuration:

qemu-system-x86_64 -M microvm,rtc=off,isa-serial=off,option-roms=off \
 -enable-kvm -cpu host -m 512m -smp 2 \
 -kernel vmlinux -append "console=hvc0 root=/dev/vda" \
 -nodefaults -no-user-config -nographic \
 -chardev stdio,id=virtiocon0,server \
 -device virtio-serial-device \
 -device virtconsole,chardev=virtiocon0 \
 -drive id=test,file=test.img,format=raw,if=none \
 -device virtio-blk-device,drive=test \
 -netdev tap,id=tap0,script=no,downscript=no \
 -device virtio-net-device,netdev=tap0
---

Changelog
v4:
 - This is a complete rewrite of the whole patchset, with a focus on
   reusing as much existing code as possible to ease the maintenance burden
   and making the machine type as compatible as possible by default. As
   a result, the number of lines dedicated specifically to microvm is
   383 (code lines measured by "cloc") and, with the default
   configuration, it's now able to boot both PVH ELF images and
   bzImages with either SeaBIOS or qboot.

v3:
  - Add initrd support (thanks Stefano).

v2:
  - Drop "[PATCH 1/4] hw/i386: Factorize CPU routine".
  - Simplify machine definition (thanks Eduardo).
  - Remove use of unneeded NUMA-related callbacks (thanks Eduardo).
  - Add a patch to factorize PVH-related functions.
  - Replace use of Linux's Zero Page with PVH (thanks Maran and Paolo).
  
---
Sergio Lopez (8):
  hw/i386: Factorize PVH related functions
  hw/i386: Factorize e820 related functions
  hw/virtio: Factorize virtio-mmio headers
  hw/i386: split PCMachineState deriving X86MachineState from it
  fw_cfg: add "modify" functions for all types
  roms: add microvm-bios (qboot) as binary and git submodule
  docs/microvm.txt: document the new microvm machine type
  hw/i386: Introduce the microvm machine type

 .gitmodules                      |   3 +
 default-configs/i386-softmmu.mak |   1 +
 docs/microvm.txt                 |  78 +++
 hw/acpi/cpu_hotplug.c            |  10 +-
 hw/i386/Kconfig                  |   4 +
 hw/i386/Makefile.objs            |   4 +
 hw/i386/acpi-build.c             |  31 +-
 hw/i386/amd_iommu.c              |   4 +-
 hw/i386/e820.c                   |  99 ++++
 hw/i386/e820.h                   |  11 +
 hw/i386/intel_iommu.c            |   4 +-
 hw/i386/microvm.c                | 512 +++++++++++++++++
 hw/i386/pc.c                     | 960 +++----------------------------
 hw/i386/pc_piix.c                |  48 +-
 hw/i386/pc_q35.c                 |  38 +-
 hw/i386/pc_sysfw.c               |  60 +-
 hw/i386/pvh.c                    | 113 ++++
 hw/i386/pvh.h                    |  10 +
 hw/i386/x86.c                    | 788 +++++++++++++++++++++++++
 hw/intc/ioapic.c                 |   3 +-
 hw/nvram/fw_cfg.c                |  29 +
 hw/virtio/virtio-mmio.c          |  35 +-
 include/hw/i386/microvm.h        |  80 +++
 include/hw/i386/pc.h             |  40 +-
 include/hw/i386/x86.h            |  97 ++++
 include/hw/nvram/fw_cfg.h        |  42 ++
 include/hw/virtio/virtio-mmio.h  |  60 ++
 pc-bios/bios-microvm.bin         | Bin 0 -> 65536 bytes
 roms/Makefile                    |   6 +
 roms/qboot                       |   1 +
 target/i386/kvm.c                |   1 +
 31 files changed, 2102 insertions(+), 1070 deletions(-)
 create mode 100644 docs/microvm.txt
 create mode 100644 hw/i386/e820.c
 create mode 100644 hw/i386/e820.h
 create mode 100644 hw/i386/microvm.c
 create mode 100644 hw/i386/pvh.c
 create mode 100644 hw/i386/pvh.h
 create mode 100644 hw/i386/x86.c
 create mode 100644 include/hw/i386/microvm.h
 create mode 100644 include/hw/i386/x86.h
 create mode 100644 include/hw/virtio/virtio-mmio.h
 create mode 100755 pc-bios/bios-microvm.bin
 create mode 160000 roms/qboot
```
#### [PATCH V2 0/8] mdev based hardware virtio offloading support
##### From: Jason Wang <jasowang@redhat.com>

```c
From patchwork Tue Sep 24 13:53:24 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 11158861
Return-Path: <SRS0=xKXW=XT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A706014ED
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 24 Sep 2019 13:54:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 8575D20872
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 24 Sep 2019 13:54:14 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2441157AbfIXNyN (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 24 Sep 2019 09:54:13 -0400
Received: from mx1.redhat.com ([209.132.183.28]:35932 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2441133AbfIXNyN (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 24 Sep 2019 09:54:13 -0400
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 7AC747FDCA;
        Tue, 24 Sep 2019 13:54:09 +0000 (UTC)
Received: from jason-ThinkPad-X1-Carbon-6th.redhat.com
 (ovpn-12-44.pek2.redhat.com [10.72.12.44])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 5087C5B69A;
        Tue, 24 Sep 2019 13:53:48 +0000 (UTC)
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
        freude@linux.ibm.com, lingshan.zhu@intel.com, idos@mellanox.com,
        eperezma@redhat.com, lulu@redhat.com, parav@mellanox.com,
        christophe.de.dinechin@gmail.com, kevin.tian@intel.com,
        Jason Wang <jasowang@redhat.com>
Subject: [PATCH V2 0/8] mdev based hardware virtio offloading support
Date: Tue, 24 Sep 2019 21:53:24 +0800
Message-Id: <20190924135332.14160-1-jasowang@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.5.16 (mx1.redhat.com [10.5.110.27]);
 Tue, 24 Sep 2019 13:54:13 +0000 (UTC)
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

Though the series only contains kernel driver support, the goal is to
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

[1] https://lkml.org/lkml/2019/9/16/869

Changes from V1:

- move virtio_mdev.c to drivers/virtio
- store class_id in mdev_device instead of mdev_parent
- store device_ops in mdev_device instead of mdev_parent
- reorder the patch, vringh fix comes first
- really silent compiling warnings
- really switch to use u16 for class_id
- uevent and modpost support for mdev class_id
- vraious tweaks per comments from Parav

Changes from RFC-V2:

- silent compile warnings on some specific configuration
- use u16 instead u8 for class id
- reseve MDEV_ID_VHOST for future vhost-mdev work
- introduce "virtio" type for mvnet and make "vhost" type for future
  work
- add entries in MAINTAINER
- tweak and typos fixes in commit log

Changes from RFC-V1:

- rename device id to class id
- add docs for class id and device specific ops (device_ops)
- split device_ops into seperate headers
- drop the mdev_set_dma_ops()
- use device_ops to implement the transport API, then it's not a part
  of UAPI any more
- use GFP_ATOMIC in mvnet sample device and other tweaks
- set_vring_base/get_vring_base support for mvnet device

Jason Wang (8):
  vringh: fix copy direction of vringh_iov_push_kern()
  mdev: class id support
  mdev: bus uevent support
  modpost: add support for mdev class id
  mdev: introduce device specific ops
  mdev: introduce virtio device and its device ops
  virtio: introduce a mdev based transport
  docs: sample driver to demonstrate how to implement virtio-mdev
    framework

 .../driver-api/vfio-mediated-device.rst       |   7 +-
 MAINTAINERS                                   |   2 +
 drivers/gpu/drm/i915/gvt/kvmgt.c              |  18 +-
 drivers/s390/cio/vfio_ccw_ops.c               |  18 +-
 drivers/s390/crypto/vfio_ap_ops.c             |  14 +-
 drivers/vfio/mdev/mdev_core.c                 |  19 +
 drivers/vfio/mdev/mdev_driver.c               |  22 +
 drivers/vfio/mdev/mdev_private.h              |   2 +
 drivers/vfio/mdev/vfio_mdev.c                 |  45 +-
 drivers/vhost/vringh.c                        |   8 +-
 drivers/virtio/Kconfig                        |   7 +
 drivers/virtio/Makefile                       |   1 +
 drivers/virtio/virtio_mdev.c                  | 417 +++++++++++
 include/linux/mdev.h                          |  52 +-
 include/linux/mod_devicetable.h               |   8 +
 include/linux/vfio_mdev.h                     |  52 ++
 include/linux/virtio_mdev.h                   | 145 ++++
 samples/Kconfig                               |   7 +
 samples/vfio-mdev/Makefile                    |   1 +
 samples/vfio-mdev/mbochs.c                    |  20 +-
 samples/vfio-mdev/mdpy.c                      |  20 +-
 samples/vfio-mdev/mtty.c                      |  18 +-
 samples/vfio-mdev/mvnet.c                     | 692 ++++++++++++++++++
 scripts/mod/devicetable-offsets.c             |   3 +
 scripts/mod/file2alias.c                      |  10 +
 25 files changed, 1524 insertions(+), 84 deletions(-)
 create mode 100644 drivers/virtio/virtio_mdev.c
 create mode 100644 include/linux/vfio_mdev.h
 create mode 100644 include/linux/virtio_mdev.h
 create mode 100644 samples/vfio-mdev/mvnet.c
```
#### [RFC PATCH 0/2] Add virtual SDEI support for arm64
##### From: Heyi Guo <guoheyi@huawei.com>

```c
From patchwork Tue Sep 24 15:20:52 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Heyi Guo <guoheyi@huawei.com>
X-Patchwork-Id: 11159069
Return-Path: <SRS0=xKXW=XT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1512314ED
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 24 Sep 2019 15:22:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id F0E9F21655
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 24 Sep 2019 15:22:24 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728680AbfIXPWV (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 24 Sep 2019 11:22:21 -0400
Received: from szxga06-in.huawei.com ([45.249.212.32]:46512 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1727382AbfIXPWV (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 24 Sep 2019 11:22:21 -0400
Received: from DGGEMS401-HUB.china.huawei.com (unknown [172.30.72.60])
        by Forcepoint Email with ESMTP id 19DE9F71006A9E2A596B;
        Tue, 24 Sep 2019 23:22:19 +0800 (CST)
Received: from linux-Bxxcye.huawei.com (10.175.104.222) by
 DGGEMS401-HUB.china.huawei.com (10.3.19.201) with Microsoft SMTP Server id
 14.3.439.0; Tue, 24 Sep 2019 23:22:09 +0800
From: Heyi Guo <guoheyi@huawei.com>
To: <linux-arm-kernel@lists.infradead.org>,
        <kvmarm@lists.cs.columbia.edu>, <linux-kernel@vger.kernel.org>,
        <kvm@vger.kernel.org>, <qemu-arm@nongnu.org>
CC: <wanghaibin.wang@huawei.com>, Heyi Guo <guoheyi@huawei.com>,
        Peter Maydell <peter.maydell@linaro.org>,
        Dave Martin <Dave.Martin@arm.com>,
        Marc Zyngier <marc.zyngier@arm.com>,
        Mark Rutland <mark.rutland@arm.com>,
        James Morse <james.morse@arm.com>
Subject: [RFC PATCH 0/2] Add virtual SDEI support for arm64
Date: Tue, 24 Sep 2019 23:20:52 +0800
Message-ID: <1569338454-26202-1-git-send-email-guoheyi@huawei.com>
X-Mailer: git-send-email 1.8.3.1
MIME-Version: 1.0
Content-Type: text/plain
X-Originating-IP: [10.175.104.222]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

As promised, this is the first RFC patch set for arm64 virtual SDEI
support.

New kvm capability KVM_CAP_FORWARD_HYPERCALL is added to probe if kvm
supports forwarding hypercalls, and the capability should be enabled
explicitly. PSCI can be set as exception for backward compatibility.

We reuse the existing term "hypercall" for SMC/HVC, as well as the
hypercall structure in kvm_run to exchange arguments and return
values. The definition on arm64 is as below:

exit_reason: KVM_EXIT_HYPERCALL

Input:
  nr: the immediate value of SMC/HVC calls; not really used today.
  args[6]: x0..x5 (This is not fully conform with SMCCC which requires
           x6 as argument as well, but use space can use GET_ONE_REG
           ioctl for such rare case).

Return:
  args[0..3]: x0..x3 as defined in SMCCC. We need to extract
              args[0..3] and write them to x0..x3 when hypercall exit
              returns.

And there is a corresponding patch set for qemu.

Please give your comments and suggestions.

Thanks,
HG

Cc: Peter Maydell <peter.maydell@linaro.org>
Cc: Dave Martin <Dave.Martin@arm.com>
Cc: Marc Zyngier <marc.zyngier@arm.com>
Cc: Mark Rutland <mark.rutland@arm.com>
Cc: James Morse <james.morse@arm.com>

Heyi Guo (2):
  kvm/arm: add capability to forward hypercall to user space
  kvm/arm64: expose hypercall_forwarding capability

 arch/arm/include/asm/kvm_host.h   |  5 +++++
 arch/arm64/include/asm/kvm_host.h |  5 +++++
 arch/arm64/kvm/reset.c            | 25 +++++++++++++++++++++++++
 include/kvm/arm_psci.h            |  1 +
 include/uapi/linux/kvm.h          |  3 +++
 virt/kvm/arm/arm.c                |  2 ++
 virt/kvm/arm/psci.c               | 30 ++++++++++++++++++++++++++++--
 7 files changed, 69 insertions(+), 2 deletions(-)
```
