#### [PATCH 4/5] vfio/type1: optimize dma_list tree iterations
##### From: Davidlohr Bueso <dave@stgolabs.net>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Davidlohr Bueso <dave@stgolabs.net>
X-Patchwork-Id: 11370885
Return-Path: <SRS0=xIo7=33=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 246E5921
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Feb 2020 18:14:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 03203227BF
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Feb 2020 18:14:22 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727457AbgBGSOP (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 7 Feb 2020 13:14:15 -0500
Received: from mx2.suse.de ([195.135.220.15]:39500 "EHLO mx2.suse.de"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727392AbgBGSOO (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 7 Feb 2020 13:14:14 -0500
X-Virus-Scanned: by amavisd-new at test-mx.suse.de
Received: from relay2.suse.de (unknown [195.135.220.254])
        by mx2.suse.de (Postfix) with ESMTP id 540E4AD3F;
        Fri,  7 Feb 2020 18:14:12 +0000 (UTC)
From: Davidlohr Bueso <dave@stgolabs.net>
To: akpm@linux-foundation.org
Cc: dave@stgolabs.net, linux-kernel@vger.kernel.org, mcgrof@kernel.org,
        broonie@kernel.org, alex.williamson@redhat.com, cohuck@redhat.com,
        kvm@vger.kernel.org, Davidlohr Bueso <dbueso@suse.de>
Subject: [PATCH 4/5] vfio/type1: optimize dma_list tree iterations
Date: Fri,  7 Feb 2020 10:03:04 -0800
Message-Id: <20200207180305.11092-5-dave@stgolabs.net>
X-Mailer: git-send-email 2.16.4
In-Reply-To: <20200207180305.11092-1-dave@stgolabs.net>
References: <20200207180305.11092-1-dave@stgolabs.net>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Both ->release() and ->attach_group() vfio_iommu driver
callbacks can incur in full in-order iommu->dma_list traversals,
which can be suboptimal under regular rbtree interators. This
patch proposes using the optimized llrbtree interface such that
we always have a branchless O(1) next node available. The cost
is higher memory footprint, mainly enlarging struct vfio_dma
by two pointers. This allows for minimal runtime overhead
when doing tree modifications.

Cc: alex.williamson@redhat.com
Cc: cohuck@redhat.com
Cc: kvm@vger.kernel.org
Signed-off-by: Davidlohr Bueso <dbueso@suse.de>
---
 drivers/vfio/vfio_iommu_type1.c | 50 +++++++++++++++++++++++------------------
 1 file changed, 28 insertions(+), 22 deletions(-)

```
#### [PATCH] docs/virt/kvm: Document running nested guests
##### From: Kashyap Chamarthy <kchamart@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Kashyap Chamarthy <kchamart@redhat.com>
X-Patchwork-Id: 11370707
Return-Path: <SRS0=xIo7=33=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 433E6109A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Feb 2020 15:30:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 17A0622522
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Feb 2020 15:30:17 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="L6fqpXUL"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726936AbgBGPaQ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 7 Feb 2020 10:30:16 -0500
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:51924 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726674AbgBGPaQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 7 Feb 2020 10:30:16 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1581089413;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=kzWDSvBw3VE0LQexdqxKLxFwvOaZNkpkVRmLXLOnsBk=;
        b=L6fqpXULUL2fVANkrYXLheZbbYp29ybG7+KPttvj44HzQhMZsEQEZTJKkNy9Ef+7m4Gef4
        CuP30aPhXSRotdErKbO0arafd+9iulTnin/QcNQ/SI2yzdYb9vEXRET/rM5HIlfZlCPHLc
        U4jdKrBKaBPJv30I67LZv+WC0uxZpnE=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-14-LjFylj3BMU6NoqA-Cqke4Q-1; Fri, 07 Feb 2020 10:30:09 -0500
X-MC-Unique: LjFylj3BMU6NoqA-Cqke4Q-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 56B941085933
        for <kvm@vger.kernel.org>; Fri,  7 Feb 2020 15:30:08 +0000 (UTC)
Received: from paraplu.localdomain (ovpn-116-47.ams2.redhat.com
 [10.36.116.47])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 2ED547794F;
        Fri,  7 Feb 2020 15:30:07 +0000 (UTC)
From: Kashyap Chamarthy <kchamart@redhat.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, dgilbert@redhat.com, vkuznets@redhat.com,
        Kashyap Chamarthy <kchamart@redhat.com>
Subject: [PATCH] docs/virt/kvm: Document running nested guests
Date: Fri,  7 Feb 2020 16:30:02 +0100
Message-Id: <20200207153002.16081-1-kchamart@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is a rewrite of the Wiki page:

    https://www.linux-kvm.org/page/Nested_Guests

Signed-off-by: Kashyap Chamarthy <kchamart@redhat.com>
---
Question: is the live migration of L1-with-L2-running-in-it fixed for
*all* architectures, including s390x?
---
 .../virt/kvm/running-nested-guests.rst        | 171 ++++++++++++++++++
 1 file changed, 171 insertions(+)
 create mode 100644 Documentation/virt/kvm/running-nested-guests.rst

diff --git a/Documentation/virt/kvm/running-nested-guests.rst b/Documentation/virt/kvm/running-nested-guests.rst
new file mode 100644
index 0000000000000000000000000000000000000000..e94ab665c71a36b7718aebae902af16b792f6dd3
--- /dev/null
+++ b/Documentation/virt/kvm/running-nested-guests.rst
@@ -0,0 +1,171 @@
+Running nested guests with KVM
+==============================
+
+A nested guest is a KVM guest that in turn runs on a KVM guest::
+
+              .----------------.  .----------------.
+              |                |  |                |
+              |      L2        |  |      L2        |
+              | (Nested Guest) |  | (Nested Guest) |
+              |                |  |                |
+              |----------------'--'----------------|
+              |                                    |
+              |       L1 (Guest Hypervisor)        |
+              |          KVM (/dev/kvm)            |
+              |                                    |
+      .------------------------------------------------------.
+      |                 L0 (Host Hypervisor)                 |
+      |                    KVM (/dev/kvm)                    |
+      |------------------------------------------------------|
+      |                  x86 Hardware (VMX)                  |
+      '------------------------------------------------------'
+
+
+Terminology:
+
+  - L0 – level-0; the bare metal host, running KVM
+
+  - L1 – level-1 guest; a VM running on L0; also called the "guest
+    hypervisor", as it itself is capable of running KVM.
+
+  - L2 – level-2 guest; a VM running on L1, this is the "nested guest"
+
+
+Use Cases
+---------
+
+An additional layer of virtualization sometimes can .  You
+might have access to a large virtual machine in a cloud environment that
+you want to compartmentalize into multiple workloads.  You might be
+running a lab environment in a training session.
+
+There are several scenarios where nested KVM can be Useful:
+
+  - As a developer, you want to test your software on different OSes.
+    Instead of renting multiple VMs from a Cloud Provider, using nested
+    KVM lets you rent a large enough "guest hypervisor" (level-1 guest).
+    This in turn allows you to create multiple nested guests (level-2
+    guests), running different OSes, on which you can develop and test
+    your software.
+
+  - Live migration of "guest hypervisors" and their nested guests, for
+    load balancing, disaster recovery, etc.
+
+  - Using VMs for isolation (as in Kata Containers, and before it Clear
+    Containers https://lwn.net/Articles/644675/) if you're running on a
+    cloud provider that is already using virtual machines
+
+
+Procedure to enable nesting on the bare metal host
+--------------------------------------------------
+
+The KVM kernel modules do not enable nesting by default (though your
+distribution may override this default).  To enable nesting, set the
+``nested`` module parameter to ``Y`` or ``1``. You may set this
+parameter persistently in a file in ``/etc/modprobe.d`` in the L0 host:
+
+1. On the bare metal host (L0), list the kernel modules, and ensure that
+   the KVM modules::
+
+    $ lsmod | grep -i kvm
+    kvm_intel             133627  0
+    kvm                   435079  1 kvm_intel
+
+2. Show information for ``kvm_intel`` module::
+
+    $ modinfo kvm_intel | grep -i nested
+    parm:           nested:boolkvm                   435079  1 kvm_intel
+
+3. To make nested KVM configuration persistent across reboots, place the
+   below entry in a config attribute::
+
+    $ cat /etc/modprobe.d/kvm_intel.conf
+    options kvm-intel nested=y
+
+4. Unload and re-load the KVM Intel module::
+
+    $ sudo rmmod kvm-intel
+    $ sudo modprobe kvm-intel
+
+5. Verify if the ``nested`` parameter for KVM is enabled::
+
+    $ cat /sys/module/kvm_intel/parameters/nested
+    Y
+
+For AMD hosts, the process is the same as above, except that the module
+name is ``kvm-amd``.
+
+Once your bare metal host (L0) is configured for nesting, you should be
+able to start an L1 guest with ``qemu-kvm -cpu host`` (which passes
+through the host CPU's capabilities as-is to the guest); or for better
+live migration compatibility, use a named CPU model supported by QEMU,
+e.g.: ``-cpu Haswell-noTSX-IBRS,vmx=on`` and the guest will subsequently
+be capable of running an L2 guest with accelerated KVM.
+
+Additional nested-related kernel parameters
+-------------------------------------------
+
+If your hardware is sufficiently advanced (Intel Haswell processor or
+above which has newer hardware virt extensions), you might want to
+enable additional features: "Shadow VMCS (Virtual Machine Control
+Structure)", APIC Virtualization on your bare metal host (L0).
+Parameters for Intel hosts::
+
+    $ cat /sys/module/kvm_intel/parameters/enable_shadow_vmcs
+    Y
+
+    $ cat /sys/module/kvm_intel/parameters/enable_apicv
+    N
+
+    $ cat /sys/module/kvm_intel/parameters/ept
+    Y
+
+Again, to persist the above values across reboot, append them to
+``/etc/modprobe.d/kvm_intel.conf``::
+
+    options kvm-intel nested=y
+    options kvm-intel enable_shadow_vmcs=y
+    options kvm-intel enable_apivc=y
+    options kvm-intel ept=y
+
+
+Live migration with nested KVM
+------------------------------
+
+The below live migration scenarios should work as of Linux kernel 5.3
+and QEMU 4.2.0.  In all the below cases, L1 exposes ``/dev/kvm`` in
+it, i.e. the L2 guest is a "KVM-accelerated guest", not a "plain
+emulated guest" (as done by QEMU's TCG).
+
+- Migrating a nested guest (L2) to another L1 guest on the *same* bare
+  metal host.
+
+- Migrating a nested guest (L2) to another L1 guest on a *different*
+  bare metal host.
+
+- Migrating an L1 guest, with an *offline* nested guest in it, to
+  another bare metal host.
+
+- Migrating an L1 guest, with a  *live* nested guest in it, to another
+  bare metal host.
+
+
+Limitations on Linux kernel versions older than 5.3
+---------------------------------------------------
+
+On Linux kernel versions older than 5.3, once an L1 guest has started an
+L2 guest, the L1 guest would no longer capable of being migrated, saved,
+or loaded (refer to QEMU documentation on "save"/"load") until the L2
+guest shuts down.  [FIXME: Is this limitation fixed for *all*
+architectures, including s390x?]
+
+Attempting to migrate or save & load an L1 guest while an L2 guest is
+running will result in undefined behavior.  You might see a ``kernel
+BUG!`` entry in ``dmesg``, a kernel 'oops', or an outright kernel panic.
+Such a migrated or loaded L1 guest can no longer be considered stable or
+secure, and must be restarted.
+
+Migrating an L1 guest merely configured to support nesting, while not
+actually running L2 guests, is expected to function normally.
+Live-migrating an L2 guest from one L1 guest to another is also expected
+to succeed.
```
#### [PATCH v3 1/5] KVM: x86: Mask off reserved bit from #DB exception payload
##### From: Oliver Upton <oupton@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Oliver Upton <oupton@google.com>
X-Patchwork-Id: 11370213
Return-Path: <SRS0=xIo7=33=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9F90A1398
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Feb 2020 10:36:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7E0C72082E
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Feb 2020 10:36:34 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="HH+16w6b"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727254AbgBGKgd (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 7 Feb 2020 05:36:33 -0500
Received: from mail-pl1-f202.google.com ([209.85.214.202]:36379 "EHLO
        mail-pl1-f202.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726899AbgBGKgc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 7 Feb 2020 05:36:32 -0500
Received: by mail-pl1-f202.google.com with SMTP id bg1so1075310plb.3
        for <kvm@vger.kernel.org>; Fri, 07 Feb 2020 02:36:31 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=7R/dzs2gX8j/iAzEk3ko1uOJm0nEa/ipr/WpACBTbQQ=;
        b=HH+16w6bSh9kJgwLw/eGP3tT64ip677kQ/rI6KBT1ztBNMY2LuPcn2EtSKmypceuLl
         XHENXp7zLTq1c9REd5bT4rau+b2DJ4Yds7NZUL9N5w4fnzwGEhWweqg8ZPhU+u6/jEXh
         0+qlLVbepZGF4vKYOHbjOkVmB/bYMCCTMcPX7pgn9F1OZWeuoqq7KcAVsI6DkZ0fUW78
         cIWFlEPvnCilWFzZY/idDIrIm/63njmUVxk563HSJ/1KR6b2DTunGb3XPtQDaSdZPObi
         5XWiB5WvTCdP9M0BafRbFWWoDrlYsvvN0/4tiqU76L2mSj//P5tkk5iunbk3glXQnIOA
         m4WQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=7R/dzs2gX8j/iAzEk3ko1uOJm0nEa/ipr/WpACBTbQQ=;
        b=KF1k9W/X/JtBB9slzq+rziYgYi+QdAsI4ZT86la8ie0KEJKfFY2nWyZOALEdZZ6wgY
         dPgKAmkrj5r2TqdImJJ6MQoARlNFrOYI9Qj/plZb3mrqrLpPhJuFtS653PD9RIvB+Lwg
         oacdFgooJ8ULM8QodEKRkPdrjuU9m7rMchOIKXJ5FCVDnE9YoM1MBbTO36UEsEcOEZPf
         7XDNAwpNC/XKiXVWJo0BRyGKU4OQjOs0XM0e6ngmrVSfBxS2UErB6Xrk5H+zdclVbdMu
         iL/UuvwjfxSDHB6Be2JBGUMQLZ+mfJp0gQpOly9cGq3FGosrU+KKjQoL7JZYGqN4gI/f
         iqpw==
X-Gm-Message-State: APjAAAWZFamgacBGTTr2BGleFO1VlRyGYskfLC4SPD+XaJwGATpiHn9x
        RG+T5b57/lt1KdvTQLaRZeTKghcyGmrov3KBmH495SWOur6HTKjKmaMfPQkAQiFhV/8Gc8kIcaS
        9w1ws3OAE6XA0tSyoSjttHF2F/Cj62X5JiLglF/BDbo4/QDwElI+HRhCdxw==
X-Google-Smtp-Source: 
 APXvYqxrN9GobmXw/X8Yt4hU6wKnPvXV97gls1jHqsBkjRGKq2QvqKN6fJ7klMWLTemuQP9hEwwiZNI+oHM=
X-Received: by 2002:a63:7454:: with SMTP id e20mr8820602pgn.192.1581071790694;
 Fri, 07 Feb 2020 02:36:30 -0800 (PST)
Date: Fri,  7 Feb 2020 02:36:04 -0800
In-Reply-To: <20200207103608.110305-1-oupton@google.com>
Message-Id: <20200207103608.110305-2-oupton@google.com>
Mime-Version: 1.0
References: <20200207103608.110305-1-oupton@google.com>
X-Mailer: git-send-email 2.25.0.341.g760bfbb309-goog
Subject: [PATCH v3 1/5] KVM: x86: Mask off reserved bit from #DB exception
 payload
From: Oliver Upton <oupton@google.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Peter Shier <pshier@google.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Oliver Upton <oupton@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

KVM defines the #DB payload as compatible with the 'pending debug
exceptions' field under VMX, not DR6. Mask off bit 12 when applying the
payload to DR6, as it is reserved on DR6 but not the 'pending debug
exceptions' field.

Fixes: f10c729ff965 ("kvm: vmx: Defer setting of DR6 until #DB delivery")
Signed-off-by: Oliver Upton <oupton@google.com>
---
 arch/x86/kvm/x86.c | 8 ++++++++
 1 file changed, 8 insertions(+)

```
#### [PATCH v12 Kernel 1/7] vfio: KABI for migration interface for device state
##### From: Kirti Wankhede <kwankhede@nvidia.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kirti Wankhede <kwankhede@nvidia.com>
X-Patchwork-Id: 11371103
Return-Path: <SRS0=xIo7=33=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 71795924
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Feb 2020 20:16:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 3CAE520715
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Feb 2020 20:16:30 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=nvidia.com header.i=@nvidia.com
 header.b="ESZpDxNI"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727144AbgBGUQ0 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 7 Feb 2020 15:16:26 -0500
Received: from hqnvemgate24.nvidia.com ([216.228.121.143]:16211 "EHLO
        hqnvemgate24.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727130AbgBGUQ0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 7 Feb 2020 15:16:26 -0500
Received: from hqpgpgate101.nvidia.com (Not Verified[216.228.121.13]) by
 hqnvemgate24.nvidia.com (using TLS: TLSv1.2, DES-CBC3-SHA)
        id <B5e3dc55c0001>; Fri, 07 Feb 2020 12:15:25 -0800
Received: from hqmail.nvidia.com ([172.20.161.6])
  by hqpgpgate101.nvidia.com (PGP Universal service);
  Fri, 07 Feb 2020 12:16:24 -0800
X-PGP-Universal: processed;
        by hqpgpgate101.nvidia.com on Fri, 07 Feb 2020 12:16:24 -0800
Received: from HQMAIL101.nvidia.com (172.20.187.10) by HQMAIL111.nvidia.com
 (172.20.187.18) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Fri, 7 Feb
 2020 20:16:24 +0000
Received: from kwankhede-dev.nvidia.com (10.124.1.5) by HQMAIL101.nvidia.com
 (172.20.187.10) with Microsoft SMTP Server (TLS) id 15.0.1473.3 via Frontend
 Transport; Fri, 7 Feb 2020 20:16:17 +0000
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
Subject: [PATCH v12 Kernel 1/7] vfio: KABI for migration interface for device
 state
Date: Sat, 8 Feb 2020 01:12:28 +0530
Message-ID: <1581104554-10704-2-git-send-email-kwankhede@nvidia.com>
X-Mailer: git-send-email 2.7.0
In-Reply-To: <1581104554-10704-1-git-send-email-kwankhede@nvidia.com>
References: <1581104554-10704-1-git-send-email-kwankhede@nvidia.com>
X-NVConfidentiality: public
MIME-Version: 1.0
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1581106525; bh=Wk/4vlleosW0ARxawGyH3dUipo434bU6vZVMB6qpW1Y=;
        h=X-PGP-Universal:From:To:CC:Subject:Date:Message-ID:X-Mailer:
         In-Reply-To:References:X-NVConfidentiality:MIME-Version:
         Content-Type;
        b=ESZpDxNI6FyuI9/di6HP09hWINSc4fqZKC/ppLb0GYCnjl9gNKyzOZAayjZ4DWPLM
         hdT2ZQo+ezYwU3VOI5vESbYJFZJURs60dq/lzSb5pFhB7p6DvUIMeiffOSh60gvfA/
         qGZPZYLXfCI0DZ5qkqcomEDndYUz0eZwelHoZBVu56DPbUGGeuUp14skB2NCtf7X5W
         oF74rgH1kkMTU10PAZdT4rGMVbEjNkegAaxzYK+w3Ur40ACP0rlQf8+DAzzOql2lCg
         t7mN6HZYK8dCpe3FvYtU6lSIYM2ASOvd/wIZrDmQYH4CnriQFDU/txEpjpxaoLtsaI
         MjGIj9UtsY5zg==
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

- Defined MIGRATION region type and sub-type.

- Defined vfio_device_migration_info structure which will be placed at 0th
  offset of migration region to get/set VFIO device related information.
  Defined members of structure and usage on read/write access.

- Defined device states and state transition details.

- Defined sequence to be followed while saving and resuming VFIO device.

Signed-off-by: Kirti Wankhede <kwankhede@nvidia.com>
Reviewed-by: Neo Jia <cjia@nvidia.com>
---
 include/uapi/linux/vfio.h | 208 ++++++++++++++++++++++++++++++++++++++++++++++
 1 file changed, 208 insertions(+)

```
#### [PATCH] KVM: Disable preemption in kvm_get_running_vcpu()
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11370761
Return-Path: <SRS0=xIo7=33=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 68F75138D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Feb 2020 16:34:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 48310217BA
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Feb 2020 16:34:27 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1581093267;
	bh=GN1tdZxHd8F0WGBBeyp6PW/4IYqx0usfkvEwY2P3jF4=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=m33nHd03vr0QZxPoTFipNAMim6yKwSnFRiPwOoW4VS7HwHmAmWOO+uNkwqYq1T342
	 faFJar5095RKRSVS+Cl7ElCUjostRMZa117EItsnhSpAaSyIJ008KBDgQhLn4fsfxh
	 Wyn1fFR+zjUOHAuVuKRFtMSpL1nqd1b0HGqaD+6c=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727012AbgBGQe0 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 7 Feb 2020 11:34:26 -0500
Received: from mail.kernel.org ([198.145.29.99]:43854 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726936AbgBGQe0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 7 Feb 2020 11:34:26 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 2BB9C22314;
        Fri,  7 Feb 2020 16:34:25 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1581093265;
        bh=GN1tdZxHd8F0WGBBeyp6PW/4IYqx0usfkvEwY2P3jF4=;
        h=From:To:Cc:Subject:Date:From;
        b=gQsHJwOFLrBtOGkqDs0dTVfyUCCd4XMI1BZPMd42SCm46NR5s0ZuwKEzZsQf4uV7w
         hXFxsWknPm9x6aQNT9YCAEr2yTPGAB1asqO22dYqMOBS+rXVpFQKyrvezanCO9OA2q
         q9ku9GPjvY1iAFObNpqTMRnn4fbwgJ6S2fOhRT7w=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1j06aF-003Zb1-Gi; Fri, 07 Feb 2020 16:34:23 +0000
From: Marc Zyngier <maz@kernel.org>
To: kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org
Cc: Peter Xu <peterx@redhat.com>, Paolo Bonzini <pbonzini@redhat.com>,
        Zenghui Yu <yuzenghui@huawei.com>
Subject: [PATCH] KVM: Disable preemption in kvm_get_running_vcpu()
Date: Fri,  7 Feb 2020 16:34:10 +0000
Message-Id: <20200207163410.31276-1-maz@kernel.org>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
 peterx@redhat.com, pbonzini@redhat.com, yuzenghui@huawei.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Accessing a per-cpu variable only makes sense when preemption is
disabled (and the kernel does check this when the right debug options
are switched on).

For kvm_get_running_vcpu(), it is fine to return the value after
re-enabling preemption, as the preempt notifiers will make sure that
this is kept consistent across task migration (the comment above the
function hints at it, but lacks the crucial preemption management).

While we're at it, move the comment from the ARM code, which explains
why the whole thing works.

Fixes: 7495e22bb165 ("KVM: Move running VCPU from ARM to common code").
Cc: Peter Xu <peterx@redhat.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Reported-by: Zenghui Yu <yuzenghui@huawei.com>
Signed-off-by: Marc Zyngier <maz@kernel.org>
Link: https://lore.kernel.org/r/318984f6-bc36-33a3-abc6-bf2295974b06@huawei.com
Reviewed-by: Peter Xu <peterx@redhat.com>
---
 virt/kvm/arm/vgic/vgic-mmio.c | 12 ------------
 virt/kvm/kvm_main.c           | 16 +++++++++++++---
 2 files changed, 13 insertions(+), 15 deletions(-)

```
#### [PATCH RFC 1/4] KVM: Provide kvm_flush_remote_tlbs_common()
##### From: Peter Xu <peterx@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11371339
Return-Path: <SRS0=xIo7=33=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 628311398
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Feb 2020 22:35:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 406BA222D9
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Feb 2020 22:35:31 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="TqgeDWsV"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727465AbgBGWfa (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 7 Feb 2020 17:35:30 -0500
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:20554 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727379AbgBGWfa (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 7 Feb 2020 17:35:30 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1581114928;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=8BwOjosBD3aan9vZqA1/XtTiViONk3Y9UUF8NI7mgRo=;
        b=TqgeDWsVl6jBUndQDpLwvSh19aWpr8HKcV3F+Sn5DF/18m/fbM1e8u7PR/0Z9U5CwOlEzn
        AzQCxtFJTyYB7DTa3+UmYkhrtwlU4zn3QiTXnDxidZxhOcVhEMiXDCDYa7Mymzm2UHRCCT
        RVC4ary7WfhAqsUIX5OkvCICezOS8Wo=
Received: from mail-qv1-f70.google.com (mail-qv1-f70.google.com
 [209.85.219.70]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-321-jJu1sl6qPiOuGnj6dnw_PA-1; Fri, 07 Feb 2020 17:35:25 -0500
X-MC-Unique: jJu1sl6qPiOuGnj6dnw_PA-1
Received: by mail-qv1-f70.google.com with SMTP id l1so485508qvu.13
        for <kvm@vger.kernel.org>; Fri, 07 Feb 2020 14:35:25 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=8BwOjosBD3aan9vZqA1/XtTiViONk3Y9UUF8NI7mgRo=;
        b=eCopripMFszuJcljTne+EoyIOjHfiYemh9T7mJ7Z4zTSdvtGtNeCe039K1sfJXiVSP
         o7Qn/L0m+wQWAChwdYpsaCwbGbr9JI4ji7YOWxa8dM0I3dWya3JwVCV6fkcI71gXP3yt
         F6d0TjHnlxvF4eK7WoY3iyaIfK244qwY/l/PGkOvszj4l51irG6fic+K4taqYvX967uD
         0CXqarHWIbssEY0It4zIqaQKgcNv7FqkDAOpiMop29NDud7gns6pwC38Cvz66u+bnfde
         JpT6ugceC92FL48GkHsxy+FyGdD4LP52IWjShvDpJ2RDOrUauOPFDYZ6wK1FM8zreatt
         6h8Q==
X-Gm-Message-State: APjAAAXrCsY3ausQOqxnwfeKpZuTxS9kBYs1brSmTdGBlOBCtRie/Hsm
        hscfhqbOvkPXt8PSOFpHq+v/A4kmkCTPDwwhL8sKkGB1Co9m6irlokRbswTx6sfQ9o89iIhBPvg
        9c/MOpEy3+412
X-Received: by 2002:aed:3e13:: with SMTP id l19mr560576qtf.103.1581114925266;
        Fri, 07 Feb 2020 14:35:25 -0800 (PST)
X-Google-Smtp-Source: 
 APXvYqyVTvI4slEe315nMe8hBROEAYdieeZun635Z6BLpraphf59wQM9cy4oqH/UIWzzvIngWXEG9g==
X-Received: by 2002:aed:3e13:: with SMTP id l19mr560554qtf.103.1581114925041;
        Fri, 07 Feb 2020 14:35:25 -0800 (PST)
Received: from xz-x1.redhat.com ([2607:9880:19c8:32::2])
        by smtp.gmail.com with ESMTPSA id
 u12sm2178736qtj.84.2020.02.07.14.35.23
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 07 Feb 2020 14:35:24 -0800 (PST)
From: Peter Xu <peterx@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        linux-mips@vger.kernel.org, peterx@redhat.com,
        Vitaly Kuznetsov <vkuznets@redhat.com>
Subject: [PATCH RFC 1/4] KVM: Provide kvm_flush_remote_tlbs_common()
Date: Fri,  7 Feb 2020 17:35:17 -0500
Message-Id: <20200207223520.735523-2-peterx@redhat.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20200207223520.735523-1-peterx@redhat.com>
References: <20200207223520.735523-1-peterx@redhat.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

It's exactly kvm_flush_remote_tlbs() now but a internal wrapper of the
common code path.  With this, an arch can then optionally select
CONFIG_HAVE_KVM_ARCH_TLB_FLUSH_ALL=y and will be able to use the
common flushing code.

Signed-off-by: Peter Xu <peterx@redhat.com>
---
 include/linux/kvm_host.h |  1 +
 virt/kvm/kvm_main.c      | 10 ++++++++--
 2 files changed, 9 insertions(+), 2 deletions(-)

```
#### [PATCH 01/35] mm:gup/writeback: add callbacks for inaccessible pages
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11370341
Return-Path: <SRS0=xIo7=33=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1F831921
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Feb 2020 11:40:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 094E320838
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Feb 2020 11:40:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727571AbgBGLk6 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 7 Feb 2020 06:40:58 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:10848 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726897AbgBGLkG (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 7 Feb 2020 06:40:06 -0500
Received: from pps.filterd (m0098417.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 017BaQuc077910;
        Fri, 7 Feb 2020 06:40:03 -0500
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2y0p79nsq2-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 07 Feb 2020 06:40:03 -0500
Received: from m0098417.ppops.net (m0098417.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 017BactT078735;
        Fri, 7 Feb 2020 06:40:02 -0500
Received: from ppma02wdc.us.ibm.com (aa.5b.37a9.ip4.static.sl-reverse.com
 [169.55.91.170])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2y0p79nsph-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 07 Feb 2020 06:40:02 -0500
Received: from pps.filterd (ppma02wdc.us.ibm.com [127.0.0.1])
        by ppma02wdc.us.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 017BcjoO029235;
        Fri, 7 Feb 2020 11:40:02 GMT
Received: from b01cxnp23034.gho.pok.ibm.com (b01cxnp23034.gho.pok.ibm.com
 [9.57.198.29])
        by ppma02wdc.us.ibm.com with ESMTP id 2xykc9vtvs-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 07 Feb 2020 11:40:02 +0000
Received: from b01ledav006.gho.pok.ibm.com (b01ledav006.gho.pok.ibm.com
 [9.57.199.111])
        by b01cxnp23034.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id 017Be0wR50069946
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 7 Feb 2020 11:40:00 GMT
Received: from b01ledav006.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 4C295AC059;
        Fri,  7 Feb 2020 11:40:00 +0000 (GMT)
Received: from b01ledav006.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 3CAACAC05F;
        Fri,  7 Feb 2020 11:40:00 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.114.17.106])
        by b01ledav006.gho.pok.ibm.com (Postfix) with ESMTP;
        Fri,  7 Feb 2020 11:40:00 +0000 (GMT)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: Christian Borntraeger <borntraeger@de.ibm.com>,
        Janosch Frank <frankja@linux.vnet.ibm.com>
Cc: KVM <kvm@vger.kernel.org>, Cornelia Huck <cohuck@redhat.com>,
        David Hildenbrand <david@redhat.com>,
        Thomas Huth <thuth@redhat.com>,
        Ulrich Weigand <Ulrich.Weigand@de.ibm.com>,
        Claudio Imbrenda <imbrenda@linux.ibm.com>,
        Andrea Arcangeli <aarcange@redhat.com>,
        linux-s390 <linux-s390@vger.kernel.org>,
        Michael Mueller <mimu@linux.ibm.com>,
        Vasily Gorbik <gor@linux.ibm.com>, linux-mm@kvack.org,
        Andrew Morton <akpm@linux-foundation.org>
Subject: [PATCH 01/35] mm:gup/writeback: add callbacks for inaccessible pages
Date: Fri,  7 Feb 2020 06:39:24 -0500
Message-Id: <20200207113958.7320-2-borntraeger@de.ibm.com>
X-Mailer: git-send-email 2.24.0
In-Reply-To: <20200207113958.7320-1-borntraeger@de.ibm.com>
References: <20200207113958.7320-1-borntraeger@de.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-02-07_01:2020-02-07,2020-02-06 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 bulkscore=0 phishscore=0
 impostorscore=0 malwarescore=0 suspectscore=2 mlxlogscore=986
 priorityscore=1501 adultscore=0 lowpriorityscore=0 spamscore=0
 clxscore=1015 mlxscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2001150001 definitions=main-2002070089
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Claudio Imbrenda <imbrenda@linux.ibm.com>

With the introduction of protected KVM guests on s390 there is now a
concept of inaccessible pages. These pages need to be made accessible
before the host can access them.

While cpu accesses will trigger a fault that can be resolved, I/O
accesses will just fail.  We need to add a callback into architecture
code for places that will do I/O, namely when writeback is started or
when a page reference is taken.

Signed-off-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 include/linux/gfp.h | 6 ++++++
 mm/gup.c            | 2 ++
 mm/page-writeback.c | 1 +
 3 files changed, 9 insertions(+)

```
#### [PATCH v2 1/7] KVM: nVMX: Use correct root level for nested EPT shadow page tables
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11370843
Return-Path: <SRS0=xIo7=33=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0B2EB1395
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Feb 2020 17:38:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id DF04621927
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Feb 2020 17:38:17 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727113AbgBGRhv (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 7 Feb 2020 12:37:51 -0500
Received: from mga06.intel.com ([134.134.136.31]:53093 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726900AbgBGRhu (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 7 Feb 2020 12:37:50 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by orsmga104.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 07 Feb 2020 09:37:49 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,414,1574150400";
   d="scan'208";a="346067528"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by fmsmga001.fm.intel.com with ESMTP; 07 Feb 2020 09:37:49 -0800
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v2 1/7] KVM: nVMX: Use correct root level for nested EPT
 shadow page tables
Date: Fri,  7 Feb 2020 09:37:41 -0800
Message-Id: <20200207173747.6243-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20200207173747.6243-1-sean.j.christopherson@intel.com>
References: <20200207173747.6243-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hardcode the EPT page-walk level for L2 to be 4 levels, as KVM's MMU
currently also hardcodes the page walk level for nested EPT to be 4
levels.  The L2 guest is all but guaranteed to soft hang on its first
instruction when L1 is using EPT, as KVM will construct 4-level page
tables and then tell hardware to use 5-level page tables.

Fixes: 855feb673640 ("KVM: MMU: Add 5 level EPT & Shadow page table support.")
Cc: stable@vger.kernel.org
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/vmx/vmx.c | 3 +++
 1 file changed, 3 insertions(+)

```
#### [kvm-unit-tests PATCH 1/4] nVMX: Extend EPTP test to allow 5-level EPT
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11370851
Return-Path: <SRS0=xIo7=33=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B81A514B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Feb 2020 17:42:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A10A621741
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Feb 2020 17:42:48 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727195AbgBGRmr (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 7 Feb 2020 12:42:47 -0500
Received: from mga11.intel.com ([192.55.52.93]:13003 "EHLO mga11.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726988AbgBGRmr (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 7 Feb 2020 12:42:47 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga001.jf.intel.com ([10.7.209.18])
  by fmsmga102.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 07 Feb 2020 09:42:47 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,414,1574150400";
   d="scan'208";a="312095673"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by orsmga001.jf.intel.com with ESMTP; 07 Feb 2020 09:42:46 -0800
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org
Subject: [kvm-unit-tests PATCH 1/4] nVMX: Extend EPTP test to allow 5-level
 EPT
Date: Fri,  7 Feb 2020 09:42:41 -0800
Message-Id: <20200207174244.6590-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20200207174244.6590-1-sean.j.christopherson@intel.com>
References: <20200207174244.6590-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Modify the EPTP test to expect success when the EPTP is configured for
5-level page walks and 5-level walks are enumerated as supported by the
EPT capabilities MSR.  KVM is in the process of gaining support for
5-level nested EPT[*].

[*] https://lkml.kernel.org/r/20200206220836.22743-1-sean.j.christopherson@intel.com

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 x86/vmx.h       |  1 +
 x86/vmx_tests.c | 12 ++++++++----
 2 files changed, 9 insertions(+), 4 deletions(-)

```
#### [PATCH v5 1/4] selftests: KVM: Replace get_[gdt | idt]_base() by get_[gdt | idt]()
##### From: Eric Auger <eric.auger@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Auger <eric.auger@redhat.com>
X-Patchwork-Id: 11370507
Return-Path: <SRS0=xIo7=33=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8AAAC13A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Feb 2020 14:27:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 69D6721775
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Feb 2020 14:27:34 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="fXDpAPAk"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727309AbgBGO1d (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 7 Feb 2020 09:27:33 -0500
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:59171 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726954AbgBGO1d (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 7 Feb 2020 09:27:33 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1581085652;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=5mRwgw7mfJynWHZCW67IzcNW7w5lOAlL2kD3NH8ZwE8=;
        b=fXDpAPAkh1uBrttBCBMn5f7Zc6ia0TBtZSh+ESLhpRvV7X4CthDkMYRojjKA2AfY724k2S
        lS0DNd0QDnMVDGsFV/UZgUltnZ6lZgLyDCnp4mtK8PLvPX+hhV6j3d6tZl4OqvDHt/BSrH
        spyEkmvjxxYkVzNLZft6aO2f8tziA2Q=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-11-XSmolhbBNQWyupTzYTe-hA-1; Fri, 07 Feb 2020 09:27:30 -0500
X-MC-Unique: XSmolhbBNQWyupTzYTe-hA-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id AFF501081FA7;
        Fri,  7 Feb 2020 14:27:28 +0000 (UTC)
Received: from laptop.redhat.com (ovpn-116-37.ams2.redhat.com [10.36.116.37])
        by smtp.corp.redhat.com (Postfix) with ESMTP id EE08360BEC;
        Fri,  7 Feb 2020 14:27:24 +0000 (UTC)
From: Eric Auger <eric.auger@redhat.com>
To: eric.auger.pro@gmail.com, eric.auger@redhat.com,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        pbonzini@redhat.com, vkuznets@redhat.com
Cc: thuth@redhat.com, drjones@redhat.com, wei.huang2@amd.com,
        krish.sadhukhan@oracle.com
Subject: [PATCH v5 1/4] selftests: KVM: Replace get_[gdt | idt]_base() by
 get_[gdt | idt]()
Date: Fri,  7 Feb 2020 15:27:12 +0100
Message-Id: <20200207142715.6166-2-eric.auger@redhat.com>
In-Reply-To: <20200207142715.6166-1-eric.auger@redhat.com>
References: <20200207142715.6166-1-eric.auger@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

get_gdt_base() and get_idt_base() only return the base address
of the descriptor tables. Soon we will need to get the size as well.
Change the prototype of those functions so that they return
the whole desc_ptr struct instead of the address field.

Signed-off-by: Eric Auger <eric.auger@redhat.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Reviewed-by: Miaohe Lin <linmiaohe@huawei.com>
Reviewed-by: Wei Huang <wei.huang2@amd.com>
Reviewed-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---

v4 -> v5:
- updated the commit title according to Krish suggestion

v3 -> v4:
- Collected R-b's
---
 tools/testing/selftests/kvm/include/x86_64/processor.h | 8 ++++----
 tools/testing/selftests/kvm/lib/x86_64/vmx.c           | 6 +++---
 2 files changed, 7 insertions(+), 7 deletions(-)

```
#### [PATCH v2] KVM: apic: reuse smp_wmb() in kvm_make_request()
##### From: linmiaohe <linmiaohe@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: linmiaohe <linmiaohe@huawei.com>
X-Patchwork-Id: 11370685
Return-Path: <SRS0=xIo7=33=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CA5481398
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Feb 2020 15:20:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B1FC3246E0
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Feb 2020 15:20:37 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727009AbgBGPUe (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 7 Feb 2020 10:20:34 -0500
Received: from szxga05-in.huawei.com ([45.249.212.191]:9710 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726874AbgBGPUe (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 7 Feb 2020 10:20:34 -0500
Received: from DGGEMS403-HUB.china.huawei.com (unknown [172.30.72.59])
        by Forcepoint Email with ESMTP id D74921C7151530B987DE;
        Fri,  7 Feb 2020 23:20:28 +0800 (CST)
Received: from huawei.com (10.175.105.18) by DGGEMS403-HUB.china.huawei.com
 (10.3.19.203) with Microsoft SMTP Server id 14.3.439.0; Fri, 7 Feb 2020
 23:20:21 +0800
From: linmiaohe <linmiaohe@huawei.com>
To: <pbonzini@redhat.com>, <rkrcmar@redhat.com>,
        <sean.j.christopherson@intel.com>, <vkuznets@redhat.com>,
        <wanpengli@tencent.com>, <jmattson@google.com>, <joro@8bytes.org>,
        <tglx@linutronix.de>, <mingo@redhat.com>, <bp@alien8.de>,
        <hpa@zytor.com>
CC: <linmiaohe@huawei.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <x86@kernel.org>
Subject: [PATCH v2] KVM: apic: reuse smp_wmb() in kvm_make_request()
Date: Fri, 7 Feb 2020 23:22:07 +0800
Message-ID: <1581088927-3269-1-git-send-email-linmiaohe@huawei.com>
X-Mailer: git-send-email 1.8.3.1
MIME-Version: 1.0
X-Originating-IP: [10.175.105.18]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Miaohe Lin <linmiaohe@huawei.com>

kvm_make_request() provides smp_wmb() so pending_events changes are
guaranteed to be visible.

Signed-off-by: Miaohe Lin <linmiaohe@huawei.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
v1->v2:
Collected Vitaly's R-b
Use Vitaly's alternative wording
Drop unnecessary comment as suggested by Sean Christopherson
---
 arch/x86/kvm/lapic.c | 3 ---
 1 file changed, 3 deletions(-)

```
#### [PATCH v2] KVM: nVMX: Fix some comment typos and coding style
##### From: linmiaohe <linmiaohe@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: linmiaohe <linmiaohe@huawei.com>
X-Patchwork-Id: 11370687
Return-Path: <SRS0=xIo7=33=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 217431395
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Feb 2020 15:21:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 0A77222464
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Feb 2020 15:21:15 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727123AbgBGPVM (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 7 Feb 2020 10:21:12 -0500
Received: from szxga07-in.huawei.com ([45.249.212.35]:33910 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726974AbgBGPVM (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 7 Feb 2020 10:21:12 -0500
Received: from DGGEMS407-HUB.china.huawei.com (unknown [172.30.72.58])
        by Forcepoint Email with ESMTP id 4BA45BAC8A096D99EEDA;
        Fri,  7 Feb 2020 23:21:07 +0800 (CST)
Received: from huawei.com (10.175.105.18) by DGGEMS407-HUB.china.huawei.com
 (10.3.19.207) with Microsoft SMTP Server id 14.3.439.0; Fri, 7 Feb 2020
 23:20:57 +0800
From: linmiaohe <linmiaohe@huawei.com>
To: <pbonzini@redhat.com>, <rkrcmar@redhat.com>,
        <sean.j.christopherson@intel.com>, <vkuznets@redhat.com>,
        <wanpengli@tencent.com>, <jmattson@google.com>, <joro@8bytes.org>,
        <tglx@linutronix.de>, <mingo@redhat.com>, <bp@alien8.de>,
        <hpa@zytor.com>
CC: <linmiaohe@huawei.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <x86@kernel.org>
Subject: [PATCH v2] KVM: nVMX: Fix some comment typos and coding style
Date: Fri, 7 Feb 2020 23:22:45 +0800
Message-ID: <1581088965-3334-1-git-send-email-linmiaohe@huawei.com>
X-Mailer: git-send-email 1.8.3.1
MIME-Version: 1.0
X-Originating-IP: [10.175.105.18]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Miaohe Lin <linmiaohe@huawei.com>

Fix some typos in the comments. Also fix coding style.
[Sean Christopherson rewrites the comment of write_fault_to_shadow_pgtable
field in struct kvm_vcpu_arch.]

Signed-off-by: Miaohe Lin <linmiaohe@huawei.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
v1->v2:
Use Sean Christopherson' comment for write_fault_to_shadow_pgtable
---
 arch/x86/include/asm/kvm_host.h | 16 +++++++++++++---
 arch/x86/kvm/vmx/nested.c       |  5 +++--
 2 files changed, 16 insertions(+), 5 deletions(-)

```
#### [PATCH v2] KVM: x86: remove duplicated KVM_REQ_EVENT request
##### From: linmiaohe <linmiaohe@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: linmiaohe <linmiaohe@huawei.com>
X-Patchwork-Id: 11370705
Return-Path: <SRS0=xIo7=33=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 07206138D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Feb 2020 15:26:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E421422314
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Feb 2020 15:26:21 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727049AbgBGP0S (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 7 Feb 2020 10:26:18 -0500
Received: from szxga07-in.huawei.com ([45.249.212.35]:37858 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726867AbgBGP0S (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 7 Feb 2020 10:26:18 -0500
Received: from DGGEMS411-HUB.china.huawei.com (unknown [172.30.72.59])
        by Forcepoint Email with ESMTP id 44562151689C27D83C1A;
        Fri,  7 Feb 2020 23:26:15 +0800 (CST)
Received: from huawei.com (10.175.105.18) by DGGEMS411-HUB.china.huawei.com
 (10.3.19.211) with Microsoft SMTP Server id 14.3.439.0; Fri, 7 Feb 2020
 23:26:05 +0800
From: linmiaohe <linmiaohe@huawei.com>
To: <pbonzini@redhat.com>, <rkrcmar@redhat.com>,
        <sean.j.christopherson@intel.com>, <vkuznets@redhat.com>,
        <wanpengli@tencent.com>, <jmattson@google.com>, <joro@8bytes.org>,
        <tglx@linutronix.de>, <mingo@redhat.com>, <bp@alien8.de>,
        <hpa@zytor.com>
CC: <linmiaohe@huawei.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <x86@kernel.org>
Subject: [PATCH v2] KVM: x86: remove duplicated KVM_REQ_EVENT request
Date: Fri, 7 Feb 2020 23:27:51 +0800
Message-ID: <1581089271-3431-1-git-send-email-linmiaohe@huawei.com>
X-Mailer: git-send-email 1.8.3.1
MIME-Version: 1.0
X-Originating-IP: [10.175.105.18]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Miaohe Lin <linmiaohe@huawei.com>

The KVM_REQ_EVENT request is already made in kvm_set_rflags(). We should
not make it again.

Signed-off-by: Miaohe Lin <linmiaohe@huawei.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
v1->v2:
Collected Vitaly's R-b
---
 arch/x86/kvm/x86.c | 1 -
 1 file changed, 1 deletion(-)

```
#### [RFC PATCH v7 01/78] sched/swait: add swait_event_killable_exclusive()
##### From: =?utf-8?q?Adalbert_Laz=C4=83r?= <alazar@bitdefender.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Adalbert_Laz=C4=83r?=
 <alazar@bitdefender.com>
X-Patchwork-Id: 11371045
Return-Path: <SRS0=xIo7=33=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 952F7921
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Feb 2020 18:18:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 8791A21775
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Feb 2020 18:18:53 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727032AbgBGSQk (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 7 Feb 2020 13:16:40 -0500
Received: from mx01.bbu.dsd.mx.bitdefender.com ([91.199.104.161]:40538 "EHLO
        mx01.bbu.dsd.mx.bitdefender.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726951AbgBGSQk (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 7 Feb 2020 13:16:40 -0500
Received: from smtp.bitdefender.com (smtp01.buh.bitdefender.com [10.17.80.75])
        by mx01.bbu.dsd.mx.bitdefender.com (Postfix) with ESMTPS id
 84183305CA1D;
        Fri,  7 Feb 2020 20:16:38 +0200 (EET)
Received: from host.bbu.bitdefender.biz (unknown [195.210.4.22])
        by smtp.bitdefender.com (Postfix) with ESMTPSA id 69D013032046;
        Fri,  7 Feb 2020 20:16:38 +0200 (EET)
From: =?utf-8?q?Adalbert_Laz=C4=83r?= <alazar@bitdefender.com>
To: kvm@vger.kernel.org
Cc: virtualization@lists.linux-foundation.org,
 Paolo Bonzini <pbonzini@redhat.com>,
 Sean Christopherson <sean.j.christopherson@intel.com>, =?utf-8?q?Adalbert_L?=
	=?utf-8?q?az=C4=83r?= <alazar@bitdefender.com>
Subject: [RFC PATCH v7 01/78] sched/swait: add
 swait_event_killable_exclusive()
Date: Fri,  7 Feb 2020 20:15:19 +0200
Message-Id: <20200207181636.1065-2-alazar@bitdefender.com>
In-Reply-To: <20200207181636.1065-1-alazar@bitdefender.com>
References: <20200207181636.1065-1-alazar@bitdefender.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When a vCPU is introspected, it waits for introspection commands or event
replies. If the introspection channel is closed, the receiving thread
will wake-up the vCPU threads. With this function the vCPU thread will
wake-up on SIGKILL too.

Signed-off-by: Adalbert Lazăr <alazar@bitdefender.com>
---
 include/linux/swait.h | 11 +++++++++++
 1 file changed, 11 insertions(+)

```
