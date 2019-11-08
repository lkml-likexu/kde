

#### [kvm-unit-tests PATCH 0/2] Use "-Werror" for checking flags
##### From: Bill Wendling <morbo@google.com>

```c
From patchwork Thu Nov  7 01:08:42 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Bill Wendling <morbo@google.com>
X-Patchwork-Id: 11231473
Return-Path: <SRS0=VFBJ=Y7=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BBE9214E5
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  7 Nov 2019 01:08:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 96F682187F
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  7 Nov 2019 01:08:58 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="rDxFdZSp"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728218AbfKGBI5 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 6 Nov 2019 20:08:57 -0500
Received: from mail-pg1-f202.google.com ([209.85.215.202]:38402 "EHLO
        mail-pg1-f202.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727308AbfKGBI5 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 6 Nov 2019 20:08:57 -0500
Received: by mail-pg1-f202.google.com with SMTP id b24so433810pgi.5
        for <kvm@vger.kernel.org>; Wed, 06 Nov 2019 17:08:57 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=KHrUwtrqwpkVOQz+PpboVYfO9iAvo1mgLyQ5TxBkfZY=;
        b=rDxFdZSpD+T5li3HmBi2HJvPwl35hw0uJwTFF707Qc92BX5Ky/SRdgirkgXDkkpZZn
         cJChkb4aYhl2edAEvw7JIduyZazNNMZFTIV+AJrpsrieKi4KGxD5Lf9dyBklbBJEpEkM
         cPmb+hsXlCnRQELtnSFNZm/OS/ruHeK77qQOO0iDSMfx26eexj19thTT26eED+p7IlSb
         9suN80rREjKfFSTNLCkaVTK1gG2SW9bnLTF0aqHGICqcMVZXIwYBQfP2VXQTN8+EHZFr
         GcZPjQ+Gj+e2P+0EuodLL/vpSmdom+tOmZEmcrRDFExlOVVNrX9QC10GI8TMQvfYeS3T
         4gHg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=KHrUwtrqwpkVOQz+PpboVYfO9iAvo1mgLyQ5TxBkfZY=;
        b=sIABMQ/6K8dfZyZIY8FALwYM9DB50LrmEVFJKBM48O+EmC0lvdXWdYsWmXiNCOIy7g
         eQG+7z8/pzUmQCudEWRAHUAGdp9sRgRQX8PWt0v8e4Tv9eW/C9Br5tjKvbLyUV4jU4XW
         JEjT9iBd9CQsV/NG7VwJm28XOjm22HVxWrTs0ArSne0zscRGimexIBsV/f38MtgdfMHG
         G5cd9+EsIRgxG/VclePfrjhN7Le1H3DBB4ISypj396X7TJk/WMdYnf9f4qnrpdUtNuek
         XJb50+iBUL4I0tYEukZNJOfgonoddtK8mhFgt31m2Si2fdT0rnTd/9NdddDLuhnhkrwl
         8/+g==
X-Gm-Message-State: APjAAAVAfvlA+a7CP/p4HaYLs9pDoCze1EJkWZulEFDDyB0nkpF7l7xa
        6KrlsBtH1uIWHAeEv4JPufEEg1RUeY7pc2PqSts9v/1j/3deprEX0TtzAD5igpv85eqPerPPH1o
        R8unyR5nOiIbs/3cSCLtt9NskCM2MZGIpQEUR5hxaUVIiDu09o7DJgw==
X-Google-Smtp-Source: 
 APXvYqzZIdtG9ngqDg/sk4UWl4qPAuNbOzWfeUCZ+X+9TRy/TQf7rz+SFPH58KkiecHCA9H5IHcYTykOvQ==
X-Received: by 2002:a63:fc09:: with SMTP id j9mr1032825pgi.272.1573088936358;
 Wed, 06 Nov 2019 17:08:56 -0800 (PST)
Date: Wed,  6 Nov 2019 17:08:42 -0800
Message-Id: <20191107010844.101059-1-morbo@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.24.0.rc1.363.gb1bccd3e3d-goog
Subject: [kvm-unit-tests PATCH 0/2] Use "-Werror" for checking flags
From: Bill Wendling <morbo@google.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com
Cc: jmattson@google.com, Bill Wendling <morbo@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If "-Werror" isn't used then Clang doesn't fail if an unrecognized flag
is used. This causes "cc-option" to pass when it shouldn't. Also add
"cxx-option" for flags that aren't supported by the C++ compiler.

Bill Wendling (2):
  Makefile: use "-Werror" in cc-option
  Makefile: add "cxx-option" for C++ builds

 Makefile | 30 +++++++++++++++++++++++-------
 1 file changed, 23 insertions(+), 7 deletions(-)
```
#### [PATCH v2 0/2] KVM: deliver IOAPIC scan request only to the target
##### From: Nitesh Narayan Lal <nitesh@redhat.com>

```c
From patchwork Thu Nov  7 12:53:41 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Nitesh Narayan Lal <nitesh@redhat.com>
X-Patchwork-Id: 11232753
Return-Path: <SRS0=VFBJ=Y7=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2DB0C1850
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  7 Nov 2019 12:54:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 037FA2178F
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  7 Nov 2019 12:54:14 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="UfGwsjO+"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388392AbfKGMyA (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 7 Nov 2019 07:54:00 -0500
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:20179 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726810AbfKGMyA (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 7 Nov 2019 07:54:00 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1573131238;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=6FLN7O1yAviKDZlM0e9S3vB8E0dXgIqkr70PMj8kw/c=;
        b=UfGwsjO+m3moK8Who9WIUbV38IooVt5T8NOuctXvXW2wKMJDQR8Bd1qiQturOuh9NRm9BY
        8tNzBGIet34WrzgagWzsB/pnbojCWNFxJml8BcAlzh0MB2BiCSHGovPCFGVOePCuPKAAl9
        HkoYSoH+oX7ENEF9BIcLHJiwO1mlrm0=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-36-JfVVaFmIPxSrfm964BNNTg-1; Thu, 07 Nov 2019 07:53:55 -0500
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 7B6071005500;
        Thu,  7 Nov 2019 12:53:53 +0000 (UTC)
Received: from virtlab512.virt.lab.eng.bos.redhat.com
 (virtlab512.virt.lab.eng.bos.redhat.com [10.19.152.206])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 51DCC1001B34;
        Thu,  7 Nov 2019 12:53:48 +0000 (UTC)
From: Nitesh Narayan Lal <nitesh@redhat.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        pbonzini@redhat.com, mtosatti@redhat.com, rkrcmar@redhat.com,
        vkuznets@redhat.com, sean.j.christopherson@intel.com,
        wanpengli@tencent.com, jmattson@google.com, joro@8bytes.org
Subject: [PATCH v2 0/2] KVM: deliver IOAPIC scan request only to the target
 vCPUs
Date: Thu,  7 Nov 2019 07:53:41 -0500
Message-Id: <1573131223-5685-1-git-send-email-nitesh@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
X-MC-Unique: JfVVaFmIPxSrfm964BNNTg-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

IOAPIC scan requests with fixed delivery mode should only be delivered to the
vCPUs specified by the destination ID.
The second patch in this patch-set introduces an additional
kvm_get_dest_vcpus_mask() API which retrieves a bitmap with bits set for each
target vCPUs. This bitmap is later passed on to the
kvm_make_vcpus_request_mask().

I have re-used the patch sent by Radim Krčmář, which adds the support to
remember the position of each vCPUs in kvm->vcpus array.
As I needed to find out the vCPUs index in kvm->vcpus array for setting the
bits in the bitmap corresponding to the target vCPUs.

This support will enable us to reduce the latency overhead on isolated
vCPUs caused by the IPI to process due to KVM_REQ_IOAPIC_SCAN. With the current
implementation, the KVM_REQ_IOAPIC_SCAN is flushed on to all the vCPUs even
if it is meant for just one of them.

Testing:
I have added the support for testing IOAPIC logical and physical destination
mode under Fixed Delivery mode to kvm-unit-test and used it to test this patch.
https://patchwork.kernel.org/cover/11230215/
Tested the scenario where kvm_apic_map_get_dest_lapic() returns false in
kvm_get_dest_vcpus_mask() using the same patch-set mentioned above.

Changes from v1:
https://lkml.org/lkml/2019/11/6/535
- Renamed vcpus_idx to vcpu_idx.
- Fixed a bug in kvm_get_dest_vcpus_mask(), which would have triggered when
  kvm_apic_map_get_dest_lapic() returned false.
- Removed kvm_make_cpus_request_mask() from kvm_main.c. Now, I am directly
  calling kvm_make_vcpus_request_mask() from
  kvm_make_scan_ioapic_request_mask().

Nitesh Narayan Lal (1):
  KVM: x86: deliver KVM IOAPIC scan request to target vCPUs

Radim Krčmář (1):
  KVM: remember position in kvm->vcpus array

 arch/x86/include/asm/kvm_host.h |  2 ++
 arch/x86/kvm/ioapic.c           | 33 +++++++++++++++++++++++++++++--
 arch/x86/kvm/lapic.c            | 44 +++++++++++++++++++++++++++++++++++++++++
 arch/x86/kvm/lapic.h            |  3 +++
 arch/x86/kvm/x86.c              | 14 +++++++++++++
 include/linux/kvm_host.h        | 13 +++++-------
 virt/kvm/kvm_main.c             |  5 +++--
 7 files changed, 102 insertions(+), 12 deletions(-)
```
#### [PATCH V11 0/6] mdev based hardware virtio offloading support
##### From: Jason Wang <jasowang@redhat.com>

```c
From patchwork Thu Nov  7 15:11:03 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 11233103
Return-Path: <SRS0=VFBJ=Y7=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E90A31599
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  7 Nov 2019 15:11:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B56E221D79
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  7 Nov 2019 15:11:51 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="YcS14Fee"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2389452AbfKGPLt (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 7 Nov 2019 10:11:49 -0500
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:32826 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S2388519AbfKGPLt (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 7 Nov 2019 10:11:49 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1573139507;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=FrBgMaUl+cnUHfuZj6Cms+/UBTPhWI76SfAU6TTRzaU=;
        b=YcS14Fee3afaGxDGDnM9ZR+5aA8cEpCsVnKaQ43/DZYowgNj31hphwReNmDlNF8ldeqaxP
        pmwBPFyeyrCgPXu7V5aSCu1jMC0lfhce1B1f9eKJKgaXeAL/O1VN+pn7ENTwuPcm55l4rl
        V5amn/Y022HIWjXwJbqjx59FTAqzIJs=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-179-cC6C2CnIObebYy1VhuzwIg-1; Thu, 07 Nov 2019 10:11:41 -0500
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 5061D800C61;
        Thu,  7 Nov 2019 15:11:37 +0000 (UTC)
Received: from jason-ThinkPad-X1-Carbon-6th.redhat.com
 (ovpn-12-21.pek2.redhat.com [10.72.12.21])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 019B2600D1;
        Thu,  7 Nov 2019 15:11:11 +0000 (UTC)
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
        freude@linux.ibm.com, lingshan.zhu@intel.com, eperezma@redhat.com,
        lulu@redhat.com, parav@mellanox.com,
        christophe.de.dinechin@gmail.com, kevin.tian@intel.com,
        stefanha@redhat.com, rdunlap@infradead.org,
        Jason Wang <jasowang@redhat.com>
Subject: [PATCH V11 0/6] mdev based hardware virtio offloading support
Date: Thu,  7 Nov 2019 23:11:03 +0800
Message-Id: <20191107151109.23261-1-jasowang@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
X-MC-Unique: cC6C2CnIObebYy1VhuzwIg-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all:

There are hardwares that can do virtio datapath offloading while
having its own control path. This path tries to implement a mdev based
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

Also a real IFC VF driver was also posted here[2] which is a good
reference for vendors who is interested in their own virtio datapath
offloading product.

Consider mdev framework only support VFIO device and driver right now,
this series also extend it to support other types. This is done
through introducing class id to the device and pairing it with
id_talbe claimed by the driver. On top, this seris also decouple
device specific ops out of the common ones for implementing class
specific operations over mdev bus.

Pktgen test was done with virito-net + mvnet loop back device.

Please review.

[1] https://lkml.org/lkml/2019/11/5/424
[2] https://lkml.org/lkml/2019/11/5/227

Changes from V10:
- rename mvnet to mvnet_loopback
- fix typo in the help text for sample Kconfig

Changes from V9:
- Tweak the help text for virito-mdev kconfig

Changes from V8:
- try silent checkpatch, some are still there becuase they were inherited
  from virtio_config_ops which needs to be resolved in an independent series
- tweak on the comment and doc
- remove VIRTIO_MDEV_F_VERSION_1 completely
- rename CONFIG_VIRTIO_MDEV_DEVICE to CONFIG_VIRTIO_MDEV

Changes from V7:
- drop {set|get}_mdev_features for virtio
- typo and comment style fixes

Changes from V6:
- rename ops files and compile guard

Changes from V5:
- use dev_warn() instead of WARN(1) when class id is not set
- validate id_table before trying to do matching between device and
  driver
- add wildcard for modpost script
- use unique name for id_table
- move get_mdev_features() to be the first member of virtio_device_ops
  and more comments for it
- typo fixes for the comments above virtio_mdev_ops

Changes from V4:
- keep mdev_set_class() for the device that doesn't use device ops
- use union for device ops pointer in mdev_device
- introduce class specific helper for getting is device ops
- use WARN_ON instead of BUG_ON in mdev_set_virtio_ops
- explain details of get_mdev_features() and get_vendor_id()
- distinguish the optional virito device ops from mandatory ones and
  make get_generation() optional
- rename vfio_mdev.h to vfio_mdev_ops.h, rename virito_mdev.h to
  virtio_mdev_ops.h
- don't abuse version fileds in virtio_mdev structure, use features
  instead
- fix warning during device remove
- style & docs tweaks and typo fixes

Changes from V3:
- document that class id (device ops) must be specified in create()
- add WARN() when trying to set class_id when it has already set
- add WARN() when class_id is not specified in create() and correctly
  return an error in this case
- correct the prototype of mdev_set_class() in the doc
- add documention of mdev_set_class()
- remove the unnecessary "class_id_fail" label when class id is not
  specified in create()
- convert id_table in vfio_mdev to const
- move mdev_set_class and its friends after mdev_uuid()
- suqash the patch of bus uevent into patch of introducing class id
- tweak the words in the docs per Cornelia suggestion
- tie class_id and device ops through class specific initialization
  routine like mdev_set_vfio_ops()
- typos fixes in the docs of virtio-mdev callbacks
- document the usage of virtqueues in struct virtio_mdev_device
- remove the useless vqs array in struct virtio_mdev_device
- rename MDEV_ID_XXX to MDEV_CLASS_ID_XXX

Changes from V2:
- fail when class_id is not specified
- drop the vringh patch
- match the doc to the code
- tweak the commit log
- move device_ops from parent to mdev device
- remove the unused MDEV_ID_VHOST

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

Jason Wang (6):
  mdev: class id support
  modpost: add support for mdev class id
  mdev: introduce device specific ops
  mdev: introduce virtio device and its device ops
  virtio: introduce a mdev based transport
  docs: sample driver to demonstrate how to implement virtio-mdev
    framework

 .../driver-api/vfio-mediated-device.rst       |  38 +-
 MAINTAINERS                                   |   3 +
 drivers/gpu/drm/i915/gvt/kvmgt.c              |  17 +-
 drivers/s390/cio/vfio_ccw_ops.c               |  17 +-
 drivers/s390/crypto/vfio_ap_ops.c             |  13 +-
 drivers/vfio/mdev/mdev_core.c                 |  60 ++
 drivers/vfio/mdev/mdev_driver.c               |  25 +
 drivers/vfio/mdev/mdev_private.h              |   8 +
 drivers/vfio/mdev/vfio_mdev.c                 |  45 +-
 drivers/virtio/Kconfig                        |  13 +
 drivers/virtio/Makefile                       |   1 +
 drivers/virtio/virtio_mdev.c                  | 406 +++++++++++
 include/linux/mdev.h                          |  57 +-
 include/linux/mdev_vfio_ops.h                 |  52 ++
 include/linux/mdev_virtio_ops.h               | 147 ++++
 include/linux/mod_devicetable.h               |   8 +
 samples/Kconfig                               |  10 +
 samples/vfio-mdev/Makefile                    |   1 +
 samples/vfio-mdev/mbochs.c                    |  19 +-
 samples/vfio-mdev/mdpy.c                      |  19 +-
 samples/vfio-mdev/mtty.c                      |  17 +-
 samples/vfio-mdev/mvnet_loopback.c            | 687 ++++++++++++++++++
 scripts/mod/devicetable-offsets.c             |   3 +
 scripts/mod/file2alias.c                      |  11 +
 24 files changed, 1586 insertions(+), 91 deletions(-)
 create mode 100644 drivers/virtio/virtio_mdev.c
 create mode 100644 include/linux/mdev_vfio_ops.h
 create mode 100644 include/linux/mdev_virtio_ops.h
 create mode 100644 samples/vfio-mdev/mvnet_loopback.c
Acked-by: Michael S. Tsirkin <mst@redhat.com>
```
#### [PATCH 0/2] KVM: arm64: Reduce occurence of GICv4 doorbells on
##### From: Marc Zyngier <maz@kernel.org>
X-SA-Exim-Mail-From: maz@kernel.org

```c
From patchwork Thu Nov  7 16:04:10 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11233267
Return-Path: <SRS0=VFBJ=Y7=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 813961864
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  7 Nov 2019 16:04:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 55E2D21D7E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  7 Nov 2019 16:04:26 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1573142666;
	bh=H6Ign5lSBgOVZuqj31XgX9GVSaik4GG3m+HjKK4n1eU=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=rmZ+vhI62SEHjawGC+mTn9guQx2gddpkNoK41EUdqQa2TMSAD7KvNXAxI7kTRL7Yl
	 08Q1WUwCmAjuxsm/FJtG+nJwZUu7zgOoCqygWdTPphIeVouXgI1bazRI6qQglW5JWA
	 OO4E7eF6f6d6SIqF2i5XiUq7Z/IRBKXJ4sICqd5A=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388564AbfKGQEZ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 7 Nov 2019 11:04:25 -0500
Received: from inca-roads.misterjones.org ([213.251.177.50]:56966 "EHLO
        inca-roads.misterjones.org" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S2387459AbfKGQEY (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 7 Nov 2019 11:04:24 -0500
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by cheepnis.misterjones.org with esmtpsa
 (TLSv1.2:DHE-RSA-AES128-GCM-SHA256:128)
        (Exim 4.80)
        (envelope-from <maz@kernel.org>)
        id 1iSkGk-0008Bm-6O; Thu, 07 Nov 2019 17:04:22 +0100
From: Marc Zyngier <maz@kernel.org>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
        linux-arm-kernel@lists.infradead.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>
Subject: [PATCH 0/2] KVM: arm64: Reduce occurence of GICv4 doorbells on
 non-oversubscribed systems
Date: Thu,  7 Nov 2019 16:04:10 +0000
Message-Id: <20191107160412.30301-1-maz@kernel.org>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
 linux-arm-kernel@lists.infradead.org, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on cheepnis.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

As I was cleaning up some of the GICv4 code to make way for GICv4.1 it
occured to me that we could drastically reduce the impact of the GICv4
doorbells on systems that are not oversubscribed (each vcpu "owns" a
physical CPU).

The technique borrows its logic from the way we disable WFE trapping
when a vcpu is the only process on the CPU run-queue. If this vcpu is
the target of VLPIs, it is then beneficial not to trap blocking WFIs
and to leave the vcpu waiting for interrupts in guest state.

All we need to do here is to track whether VLPIs are associated to a
vcpu (which is easily done by using a counter that we update on MAPI,
DISCARD and MOVI).

It has been *very lightly* tested on a D05, and behaved pretty well in
my limited test cases (I get almost no doorbell at all in the non
oversubscribed case, and the usual hailstorm as soon as there is
oversubscription). I'd welcome some testing on more current HW.

Marc Zyngier (2):
  KVM: vgic-v4: Track the number of VLPIs per vcpu
  KVM: arm64: Opportunistically turn off WFI trapping when using direct
    LPI injection

 arch/arm/include/asm/kvm_emulate.h   | 4 ++--
 arch/arm64/include/asm/kvm_emulate.h | 9 +++++++--
 include/linux/irqchip/arm-gic-v4.h   | 2 ++
 virt/kvm/arm/arm.c                   | 4 ++--
 virt/kvm/arm/vgic/vgic-init.c        | 1 +
 virt/kvm/arm/vgic/vgic-its.c         | 3 +++
 virt/kvm/arm/vgic/vgic-v4.c          | 2 ++
 7 files changed, 19 insertions(+), 6 deletions(-)
Reviewed-by: Christoffer Dall <christoffer.dall@arm.com>
```
#### [PATCH net-next 00/19] Mellanox, mlx5 sub function support
##### From: Parav Pandit <parav@mellanox.com>

```c
From patchwork Thu Nov  7 16:04:48 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Parav Pandit <parav@mellanox.com>
X-Patchwork-Id: 11233279
Return-Path: <SRS0=VFBJ=Y7=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1195416B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  7 Nov 2019 16:05:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id DC575218AE
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  7 Nov 2019 16:05:24 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2387939AbfKGQFX (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 7 Nov 2019 11:05:23 -0500
Received: from mail-il-dmz.mellanox.com ([193.47.165.129]:53065 "EHLO
        mellanox.co.il" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1729953AbfKGQFW (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 7 Nov 2019 11:05:22 -0500
Received: from Internal Mail-Server by MTLPINE1 (envelope-from
 parav@mellanox.com)
        with ESMTPS (AES256-SHA encrypted); 7 Nov 2019 18:05:14 +0200
Received: from sw-mtx-036.mtx.labs.mlnx (sw-mtx-036.mtx.labs.mlnx
 [10.9.150.149])
        by labmailer.mlnx (8.13.8/8.13.8) with ESMTP id xA7G5BGo016782;
        Thu, 7 Nov 2019 18:05:12 +0200
From: Parav Pandit <parav@mellanox.com>
To: alex.williamson@redhat.com, davem@davemloft.net,
        kvm@vger.kernel.org, netdev@vger.kernel.org
Cc: saeedm@mellanox.com, kwankhede@nvidia.com, leon@kernel.org,
        cohuck@redhat.com, jiri@mellanox.com, linux-rdma@vger.kernel.org,
        Parav Pandit <parav@mellanox.com>
Subject: [PATCH net-next 00/19] Mellanox, mlx5 sub function support
Date: Thu,  7 Nov 2019 10:04:48 -0600
Message-Id: <20191107160448.20962-1-parav@mellanox.com>
X-Mailer: git-send-email 2.19.2
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Dave, Jiri, Alex,

This series adds the support for mlx5 sub function devices using
mediated device with eswitch switchdev mode.

This series is currently on top of [1], but once [1] is merged to
net-next tree, this series should be resend through usual Saeed's
net-next tree or to netdev net-next.

Mdev alias support patches are already reviewed at vfio/kvm's mailing
list in past. Since mlx5_core driver is first user of the
mdev alias API, those patches are part of this series to merge via
net-next tree.

[1] https://git.kernel.org/pub/scm/linux/kernel/git/saeed/linux.git/log/?h=net-next-mlx5

Also, once Jason Wang's series [9] is merged, mlx5_core driver will be enhanced to
use class id based matching support for mdev devices.

Abstract:
---------

Mellanox ConnectX device supports dynamic creation of sub function which
are equivalent to a PCI function handled by mlx5_core and mlx5_ib drivers.
It has few few differences to PCI function. They are described below in
overview section.

Mellanox sub function capability allows users to create several hundreds
of networking and/or rdma devices without depending on PCI SR-IOV support.

Motivation:
-----------
User wants to use multiple netdevices and rdma devices in a system
without enabling SR-IOV, possibly more number of devices than what
mellanox ConnectX device supports using SR-IOV.

Such devices will have most if not all of the acceleration and offload
capabilities of mlx5, while they are still light weight and don't demand
any dedicated physical resources such as (pci function, MSIX vectors).

Provision such netdevice and/or rdma device to use in bare-metal
server or provision to a container.

In future, map such sub function device to a VM once ConnectX device
supports it. In such case, it should be able to reuse existing
mediated device (mdev) [2] framework of kernel.

Regardless of how a sub function is used, it is desired to lifecycle
such device in unified way, such as using mdev [2].

User wants to have same level of control, visibility, offloads support
as that of current SR-IOV VFs using eswitch switchdev mode for
Ethernet devices.

Overview:
---------
Mellanox ConnectX sub functions are exposed to user as a mediated
device (mdev) [2] as discussed in RFC [3] and further during
netdevconf0x13 at [4].

mlx5 mediated device (mdev) enables users to create multiple netdevices
and/or RDMA devices from single PCI function.

Each mdev maps to a mlx5 sub function.
mlx5 sub function is similar to PCI VF. However it doesn't have its own
PCI function and MSI-X vectors.

mlx5 mdevs share common PCI resources such as PCI BAR region,
MSI-X interrupts.

Each mdev has its own window in the PCI BAR region, which is
accessible only to that mdev and applications using it.

Each mlx5 sub function has its own resource namespace for RDMA resources.

mdevs are supported when eswitch mode of the devlink instance
is in switchdev mode described in devlink documentation [5].

mdev is identified using a UUID defined by RFC 4122.

Each created mdev has unique 12 letters alias. This alias is used to
derive phys_port_name attribute of the corresponding representor
netdevice. This establishes clear link between mdev device, eswitch
port and eswitch representor netdevice.

systemd udev [6] will be enhanced post this work to have predictable
netdevice names based on the unique and predicable mdev alias of the
mdev device.

For example, an Ethernet netdevice of an mdev device having alias
'aliasfoo123' will be persistently named as enmaliasfoo123, where:
<en> for Ethernet
m = mediated device bus
<alias> = unique mdev alias

Design decisions:
-----------------
1. mdev device (and bus) instead of any new subdevice bus is used
after concluding discussion at [7]. This simplifies and eliminates the
need of new bus, also eliminates any vendor specific bus.

2. mdev device is also chosen to not create multiple tools for creating
netdevice, rdma device, devlink port, its representor netdevice and
representor rdma port.

3. mdev device support in eswitch switchdev mode, gives rich isolation
and reuses existing offload infrastructure of iproute2/tc.

4. mdev device also enjoys existing devlink health reporting infrastructure
uniformely for PF, VF and mdev.

5. Persistent naming of mdev's netdevice scheme is discussed and concluded
at [8] using systemwide unique, predicable mdev alias.

6. Unique eswitch port phys_port_name derivation from the mdev alias usage
is concluded at [8].

User commands examples:
-----------------------

- Set eswitch mode as switchdev mode
    $ devlink dev eswitch set pci/0000:06:00.0 mode switchdev

- Create a mdev
    Generate a UUID
    $ UUID=$(uuidgen)
    Create the mdev using UUID
    $ echo $UUID > /sys/class/net/ens2f0_p0/device/mdev_supported_types/mlx5_core-local/create

- Unbind a mdev from vfio_mdev driver
    $ echo $UUID > /sys/bus/mdev/drivers/vfio_mdev/unbind

- Bind a mdev to mlx5_core driver
    $ echo $UUID > /sys/bus/mdev/drivers/mlx5_core/bind

- View netdevice and (optionally) RDMA device in sysfs tree
    $ ls -l /sys/bus/mdev/devices/$UUID/net/
    $ ls -l /sys/bus/mdev/devices/$UUID/infiniband/

- View netdevice and (optionally) RDMA device using iproute2 tools
    $ ip link show
    $ rdma dev show

- Query maximum number of mdevs that can be created
    $ cat /sys/class/net/ens2f0_p0/device/mdev_supported_types/mlx5_core-local/max_mdevs

- Query remaining number of mdevs that can be created
    $ cat /sys/class/net/ens2f0_p0/device/mdev_supported_types/mlx5_core-local/available_instances

- Query an alias of the mdev
    $ cat /sys/bus/mdev/devices/$UUID/alias

Security model:
--------------
This section covers security aspects of mlx5 mediated devices at
host level and at network level.

Host side:
- At present mlx5 mdev is meant to be used only in a host.
It is not meant to be mapped to a VM or access by userspace application
using VFIO framework.
Hence, mlx5_core driver doesn't implement any of the VFIO device specific
callback routines.
Hence, mlx5 mediated device cannot be mapped to a VM or to a userspace
application via VFIO framework.

- At present an mlx5 mdev can be accessed by an application through
its netdevice and/or RDMA device.

- mlx5 mdev does not share PCI BAR with its parent PCI function.

- All mlx5 mdevs of a given parent device share a single PCI BAR.
However each mdev device has a small dedicated window of the PCI BAR.
Hence, one mdev device cannot access PCI BAR or any of the resources
of another mdev device.

- Each mlx5 mdev has its own dedicated event queue through which interrupt
notifications are delivered. Hence, one mlx5 mdev cannot enable/disable
interrupts of other mlx5 mdev. mlx5 mdev cannot enable/disable interrupts
of the parent PCI function.

Network side:
- By default the netdevice and the rdma device of mlx5 mdev cannot send or
receive any packets over the network or to any other mlx5 mdev.

- mlx5 mdev follows devlink eswitch and vport model of PCI SR-IOV PF and VFs.
All traffic is dropped by default in this eswitch model.

- Each mlx5 mdev has one eswitch vport representor netdevice and rdma port.
The user must do necessary configuration through such representor to enable
mlx5 mdev to send and/or receive packets.

Patchset summary:
-----------------
Patch 1 to 6 prepare mlx5 core driver to create mdev.

Patch-1 Moves mlx5 devlink port close to eswitch port
Patch-2 implements sub function vport representor handling
Patch-3,4 Introduces mlx5 sub function lifecycle routines
Patch-5 Extended mlx5 eswitch to enable/disable sub function vports
Patch-6 Registers mlx5 driver with mdev subsystem for mdev lifecycle

Patch-7 to 10 enhances mdev subsystem for unique alias generation

Patch-7 introduces sha1 based mdev alias
Patch-8 Ensures mdev alias is unique amlong all mdev devices
Patch-9 Exposes mdev alias in sysfs file for systemd/udev usage
Patch-10 Introduces mdev alias API to be used by vendor driver
Patch-11 Improves mdev to avoid nested locking with mlx5_core driver
and devlink subsystem

Patch-12 Introduces new devlink mdev port flavour
Patch-13 Registers devlink eswitch port for a sub function

Patch-14 to 17 implements mdev driver by reusing most of the mlx5_core
driver
Patch-14 implements sharing IRQ between sub function and parent PCI device
Patch-15 implements load, unload routine for sub function
Patch-16 implements dma ops for mediated device
Patch-17 implements mdev driver to bind to mdev device

Patch-18 Adds documentation for mdev overview, example and security model
Patch-19 extends sample mtty driver for mdev alias generation

[1] https://git.kernel.org/pub/scm/linux/kernel/git/saeed/linux.git/log/?h=net-next-mlx5
[2] https://www.kernel.org/doc/Documentation/vfio-mediated-device.txt
[3] https://lkml.org/lkml/2019/3/8/819
[4] https://netdevconf.org/0x13/session.html?workshop-hardware-offload
[5] http://man7.org/linux/man-pages/man8/devlink-dev.8.html.
[6] https://github.com/systemd/systemd/blob/master/src/udev/udev-builtin-net_id.c
[7] https://lkml.org/lkml/2019/3/7/696
[8] https://lkml.org/lkml/2019/8/23/146
[9] https://patchwork.ozlabs.org/patch/1190425


Parav Pandit (14):
  net/mlx5: E-switch, Move devlink port close to eswitch port
  net/mlx5: Introduce SF life cycle APIs to allocate/free
  vfio/mdev: Introduce sha1 based mdev alias
  vfio/mdev: Make mdev alias unique among all mdevs
  vfio/mdev: Expose mdev alias in sysfs tree
  vfio/mdev: Introduce an API mdev_alias
  vfio/mdev: Improvise mdev life cycle and parent removal scheme
  devlink: Introduce mdev port flavour
  net/mlx5: Register SF devlink port
  net/mlx5: Add load/unload routines for SF driver binding
  net/mlx5: Implement dma ops and params for mediated device
  net/mlx5: Add mdev driver to bind to mdev devices
  Documentation: net: mlx5: Add mdev usage documentation
  mtty: Optionally support mtty alias

Vu Pham (4):
  net/mlx5: E-Switch, Add SF vport, vport-rep support
  net/mlx5: Introduce SF table framework
  net/mlx5: E-Switch, Enable/disable SF's vport during SF life cycle
  net/mlx5: Add support for mediated devices in switchdev mode

Yuval Avnery (1):
  net/mlx5: Share irqs between SFs and parent PCI device

 .../driver-api/vfio-mediated-device.rst       |   9 +
 .../device_drivers/mellanox/mlx5.rst          | 122 +++++
 .../net/ethernet/mellanox/mlx5/core/Kconfig   |  11 +
 .../net/ethernet/mellanox/mlx5/core/Makefile  |   4 +
 drivers/net/ethernet/mellanox/mlx5/core/cmd.c |   6 +
 drivers/net/ethernet/mellanox/mlx5/core/dev.c |  17 +
 .../net/ethernet/mellanox/mlx5/core/devlink.c |  69 +++
 .../net/ethernet/mellanox/mlx5/core/devlink.h |   8 +
 .../net/ethernet/mellanox/mlx5/core/en_rep.c  |  94 +---
 .../net/ethernet/mellanox/mlx5/core/en_rep.h  |   2 +-
 drivers/net/ethernet/mellanox/mlx5/core/eq.c  |   6 +-
 .../net/ethernet/mellanox/mlx5/core/eswitch.c |  24 +-
 .../net/ethernet/mellanox/mlx5/core/eswitch.h |  85 ++++
 .../mellanox/mlx5/core/eswitch_offloads.c     | 147 +++++-
 .../net/ethernet/mellanox/mlx5/core/lib/eq.h  |   3 +-
 .../net/ethernet/mellanox/mlx5/core/main.c    |  80 +++-
 .../ethernet/mellanox/mlx5/core/meddev/mdev.c | 212 +++++++++
 .../mellanox/mlx5/core/meddev/mdev_driver.c   |  50 +++
 .../ethernet/mellanox/mlx5/core/meddev/sf.c   | 425 ++++++++++++++++++
 .../ethernet/mellanox/mlx5/core/meddev/sf.h   |  73 +++
 .../ethernet/mellanox/mlx5/core/mlx5_core.h   |  54 +++
 .../net/ethernet/mellanox/mlx5/core/pci_irq.c |  12 +
 .../net/ethernet/mellanox/mlx5/core/vport.c   |   4 +-
 drivers/vfio/mdev/mdev_core.c                 | 198 +++++++-
 drivers/vfio/mdev/mdev_private.h              |   8 +-
 drivers/vfio/mdev/mdev_sysfs.c                |  26 +-
 include/linux/mdev.h                          |   5 +
 include/linux/mlx5/driver.h                   |   8 +-
 include/net/devlink.h                         |   9 +
 include/uapi/linux/devlink.h                  |   5 +
 net/core/devlink.c                            |  32 ++
 samples/vfio-mdev/mtty.c                      |  13 +
 32 files changed, 1678 insertions(+), 143 deletions(-)
 create mode 100644 drivers/net/ethernet/mellanox/mlx5/core/meddev/mdev.c
 create mode 100644 drivers/net/ethernet/mellanox/mlx5/core/meddev/mdev_driver.c
 create mode 100644 drivers/net/ethernet/mellanox/mlx5/core/meddev/sf.c
 create mode 100644 drivers/net/ethernet/mellanox/mlx5/core/meddev/sf.h
```
#### [PATCH v3 0/5] Add support for capturing the highest observable L2
##### From: Aaron Lewis <aaronlewis@google.com>

```c
From patchwork Thu Nov  7 22:49:36 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Aaron Lewis <aaronlewis@google.com>
X-Patchwork-Id: 11233857
Return-Path: <SRS0=VFBJ=Y7=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CB7B713BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  7 Nov 2019 22:49:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A6DA921D82
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  7 Nov 2019 22:49:48 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="KLMYpB5j"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727984AbfKGWtr (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 7 Nov 2019 17:49:47 -0500
Received: from mail-vk1-f202.google.com ([209.85.221.202]:49481 "EHLO
        mail-vk1-f202.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725992AbfKGWtr (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 7 Nov 2019 17:49:47 -0500
Received: by mail-vk1-f202.google.com with SMTP id v71so1814916vkd.16
        for <kvm@vger.kernel.org>; Thu, 07 Nov 2019 14:49:46 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=vxOPgv/mPR6yTW95RMtFb/2LPtMh4Bc0wQxyROP1lhw=;
        b=KLMYpB5jG51x0jJ9vvJj23UOieG4GTB6YBN75FMHq5vWBjBXP6ZDoFhrdkNUkvmDGq
         zsesIQYcRu7OtqJPH8ViwRTi/3COTJujmnLba2KDnB4Gap2pY4/W7C4fgkd6kGHCZPHh
         T72Bh24kxczMzMQIMi9hu6xvNs6sOXyC9x/TXshIIc5fYM9zbcRZLyOnIp/kXrjFOjGM
         czoIA1dddmtSm+ClvzR/dF5VtMub6wNh5KJhdmV5p9cb8/a0DnG0e0eIUx++w3QJBl05
         XcrPg7TAj6Matx6Zis0Wmky4WDm4mr0mup6H7vggLBf3RR/jTXg4vBEIc2CKYByli5Ql
         2+/Q==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=vxOPgv/mPR6yTW95RMtFb/2LPtMh4Bc0wQxyROP1lhw=;
        b=VtUu+XEC0qWp46iKDwxIG3OicVu0bbkmCUJvpdptHskMMeNUdoXwUCgXPFcrhrGyVW
         m1NIrwTj4/e4TIt1fcb8FX/Ckv8Xzn6UJB+O0E+1OBNQzuLIvsDTMFQY3eTJb9Qlach0
         RB2kad5btpOyW3KNqjdHuHg6zZ4lwCk4UdwEqEOtV+nCO85LkQPiH04XqoRgDgk2zEfE
         RjFm1H/1DYVNLUMWGbcCkdkvFkO20EINceu0ds4yDKJl9IdXQLfa0ieGrRsL4nEA+NfJ
         TVk434BCmRHeuMCfHORPym/DzyvdiXSw7zBn4LH0g8iscW2lOkmrNGBLlwhrUjfq4T46
         RqQQ==
X-Gm-Message-State: APjAAAXQ2v65nD5rHSooAZJiMkaZteRcMax2ANV7nhvD+xulkOySaWOJ
        gV0tOLRL6cFqB+xLjg7xfs/rEWZE6Q4SkxhwR+XOtR5LN0LOjjKuoS8eDa3i2cZTh7o8v8Tydd7
        WVvp1tOdkf2xIXttaUDshlha7s1tvMyE3X+WSmMLig5ZHQ25vI+bd5gKH6Z1823/ELGfN
X-Google-Smtp-Source: 
 APXvYqxDqz/lc6d/2DSX03DPs9SwuXBgfiS8yVeQNLHrx65cXQvlOUZBcabVe65/YR5ZXfdUGIqkWGFe3agjgiTj
X-Received: by 2002:a05:6122:125:: with SMTP id
 a5mr4869378vko.79.1573166986093;
 Thu, 07 Nov 2019 14:49:46 -0800 (PST)
Date: Thu,  7 Nov 2019 14:49:36 -0800
Message-Id: <20191107224941.60336-1-aaronlewis@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.24.0.432.g9d3f5f5b63-goog
Subject: [PATCH v3 0/5] Add support for capturing the highest observable L2
 TSC
From: Aaron Lewis <aaronlewis@google.com>
To: kvm@vger.kernel.org
Cc: Jim Mattson <jmattson@google.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Aaron Lewis <aaronlewis@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The L1 hypervisor may include the IA32_TIME_STAMP_COUNTER MSR in the
vmcs12 MSR VM-exit MSR-store area as a way of determining the highest
TSC value that might have been observed by L2 prior to VM-exit. The
current implementation does not capture a very tight bound on this
value.  To tighten the bound, add the IA32_TIME_STAMP_COUNTER MSR to the
vmcs02 VM-exit MSR-store area whenever it appears in the vmcs12 VM-exit
MSR-store area.  When L0 processes the vmcs12 VM-exit MSR-store area
during the emulation of an L2->L1 VM-exit, special-case the
IA32_TIME_STAMP_COUNTER MSR, using the value stored in the vmcs02
VM-exit MSR-store area to derive the value to be stored in the vmcs12
VM-exit MSR-store area.

v2 -> v3:
 - Rename NR_MSR_ENTRIES to NR_LOADSAVE_MSRS
 - Pull setup code for preparing the MSR-store area out of the final commit and
   put it in it's own commit (4/5).
 - Export vmx_find_msr_index() in the final commit instead of in commit 3/5 as
   it isn't until the final commit that we actually use it.

v1 -> v2:
 - Rename function nested_vmx_get_msr_value() to
   nested_vmx_get_vmexit_msr_value().
 - Remove unneeded tag 'Change-Id' from commit messages.

Aaron Lewis (5):
  kvm: nested: Introduce read_and_check_msr_entry()
  kvm: vmx: Rename NR_AUTOLOAD_MSRS to NR_MSR_ENTRIES
  kvm: vmx: Rename function find_msr() to vmx_find_msr_index()
  KVM: nVMX: Prepare MSR-store area
  KVM: nVMX: Add support for capturing highest observable L2 TSC

 arch/x86/kvm/vmx/nested.c | 136 ++++++++++++++++++++++++++++++++------
 arch/x86/kvm/vmx/vmx.c    |  14 ++--
 arch/x86/kvm/vmx/vmx.h    |   9 ++-
 3 files changed, 131 insertions(+), 28 deletions(-)
```
