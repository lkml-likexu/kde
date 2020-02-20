

#### [PATCH 0/1] Paravirtualized control register pinning test
##### From: John Andersen <john.s.andersen@intel.com>

```c
From patchwork Wed Feb 19 18:04:35 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: John Andersen <john.s.andersen@intel.com>
X-Patchwork-Id: 11392267
Return-Path: <SRS0=TgUu=4H=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D276F138D
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 19 Feb 2020 18:03:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B76A8206DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 19 Feb 2020 18:03:52 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726610AbgBSSDv (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 19 Feb 2020 13:03:51 -0500
Received: from mga18.intel.com ([134.134.136.126]:17830 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726514AbgBSSDv (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 19 Feb 2020 13:03:51 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga006.fm.intel.com ([10.253.24.20])
  by orsmga106.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 19 Feb 2020 10:03:50 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,461,1574150400";
   d="scan'208";a="436312510"
Received: from gza.jf.intel.com ([10.54.75.28])
  by fmsmga006.fm.intel.com with ESMTP; 19 Feb 2020 10:03:50 -0800
From: John Andersen <john.s.andersen@intel.com>
To: pbonzini@redhat.com, kvm@vger.kernel.org
Cc: John Andersen <john.s.andersen@intel.com>
Subject: [PATCH 0/1] Paravirtualized control register pinning test
Date: Wed, 19 Feb 2020 10:04:35 -0800
Message-Id: <20200219180436.6580-1-john.s.andersen@intel.com>
X-Mailer: git-send-email 2.21.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is the corresponding test for
https://lore.kernel.org/kvm/20200218215902.5655-1-john.s.andersen@intel.com/T/#t

Thank you!

John Andersen (1):
  x86: Add control register pinning test

 x86/Makefile.common |   3 +-
 lib/x86/desc.h      |   1 +
 lib/x86/processor.h |   1 +
 lib/x86/desc.c      |   8 +++
 x86/cr_pin.c        | 163 ++++++++++++++++++++++++++++++++++++++++++++
 x86/pcid.c          |   8 ---
 x86/unittests.cfg   |   4 ++
 7 files changed, 179 insertions(+), 9 deletions(-)
 create mode 100644 x86/cr_pin.c
```
#### [PATCH v2 0/7] vfio/pci: SR-IOV support
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
From patchwork Wed Feb 19 18:53:46 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alex Williamson <alex.williamson@redhat.com>
X-Patchwork-Id: 11392293
Return-Path: <SRS0=TgUu=4H=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1E376159A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 19 Feb 2020 18:54:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E8B7724677
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 19 Feb 2020 18:54:04 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Rg0ZKshp"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726648AbgBSSyD (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 19 Feb 2020 13:54:03 -0500
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:32977 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726710AbgBSSyD (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 19 Feb 2020 13:54:03 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1582138441;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=ooAVZmPqmpejcE1lho8HJzD9Jr6TIc1QTP2vQodr9hU=;
        b=Rg0ZKshp8M0pAWk5gZuBEelgHbs2ORrC0rE/Rqtr5/rnNszDExFMOODikKlfYvoRoCnk9D
        EOZkoXkMU6Ufghls0w8C3+1YkkFpteX5ek0aSwpmZPQIosDuuaboy6j6JgPCcTxyJmKA41
        3H6gfoUC7wUDnSDz0CHMvarukTOpyhM=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-56-JYUDF0GWNu6vXN8CwF6baQ-1; Wed, 19 Feb 2020 13:53:51 -0500
X-MC-Unique: JYUDF0GWNu6vXN8CwF6baQ-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 1F401107ACC5;
        Wed, 19 Feb 2020 18:53:50 +0000 (UTC)
Received: from gimli.home (ovpn-116-28.phx2.redhat.com [10.3.116.28])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 80B505C1B0;
        Wed, 19 Feb 2020 18:53:46 +0000 (UTC)
Subject: [PATCH v2 0/7] vfio/pci: SR-IOV support
From: Alex Williamson <alex.williamson@redhat.com>
To: kvm@vger.kernel.org
Cc: linux-pci@vger.kernel.org, linux-kernel@vger.kernel.org,
        dev@dpdk.org, mtosatti@redhat.com, thomas@monjalon.net,
        bluca@debian.org, jerinjacobk@gmail.com,
        bruce.richardson@intel.com, cohuck@redhat.com
Date: Wed, 19 Feb 2020 11:53:46 -0700
Message-ID: <158213716959.17090.8399427017403507114.stgit@gimli.home>
User-Agent: StGit/0.19-dirty
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Changes since v1 are primarily to patch 3/7 where the commit log is
rewritten, along with option parsing and failure logging based on
upstream discussions.  The primary user visible difference is that
option parsing is now much more strict.  If a vf_token option is
provided that cannot be used, we generate an error.  As a result of
this, opening a PF with a vf_token option will serve as a mechanism of
setting the vf_token.  This seems like a more user friendly API than
the alternative of sometimes requiring the option (VFs in use) and
sometimes rejecting it, and upholds our desire that the option is
always either used or rejected.

This also means that the VFIO_DEVICE_FEATURE ioctl is not the only
means of setting the VF token, which might call into question whether
we absolutely need this new ioctl.  Currently I'm keeping it because I
can imagine use cases, for example if a hypervisor were to support
SR-IOV, the PF device might be opened without consideration for a VF
token and we'd require the hypservisor to close and re-open the PF in
order to set a known VF token, which is impractical.

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
---

Alex Williamson (7):
      vfio: Include optional device match in vfio_device_ops callbacks
      vfio/pci: Implement match ops
      vfio/pci: Introduce VF token
      vfio: Introduce VFIO_DEVICE_FEATURE ioctl and first user
      vfio/pci: Add sriov_configure support
      vfio/pci: Remove dev_fmt definition
      vfio/pci: Cleanup .probe() exit paths


 drivers/vfio/pci/vfio_pci.c         |  383 +++++++++++++++++++++++++++++++++--
 drivers/vfio/pci/vfio_pci_private.h |   10 +
 drivers/vfio/vfio.c                 |   20 +-
 include/linux/vfio.h                |    4 
 include/uapi/linux/vfio.h           |   37 +++
 5 files changed, 426 insertions(+), 28 deletions(-)
```
