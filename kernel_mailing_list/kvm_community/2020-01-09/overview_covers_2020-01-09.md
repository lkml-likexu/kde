

#### [PATCH v3 00/21] KVM: Dirty ring interface
##### From: Peter Xu <peterx@redhat.com>

```c
From patchwork Thu Jan  9 14:57:08 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11325927
Return-Path: <SRS0=hq+s=26=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 35ADC92A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Jan 2020 14:59:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 09A192072E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Jan 2020 14:59:35 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="LmG0qflD"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731850AbgAIO5h (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 9 Jan 2020 09:57:37 -0500
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:23351 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1729136AbgAIO5h (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 9 Jan 2020 09:57:37 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1578581856;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=dTjYPWrRS50vXb+awZBlOczchH8zUZfJ4o80FlJt42o=;
        b=LmG0qflDS9+mBFF78IGeryXTToe5g3DYUFgajGm/nOdssoPk8ZDH8Dgn0fQA0dqMYsVVgP
        yrbF8ENkYMkFDvb9ZoqVG7RmXuBTn/pg9rBmqcFEW72wtKQ0JrUrxQMHYXdF+1oznqMmDX
        f8xBVe46Ody5u20J9Fdm9tTDoe42u5E=
Received: from mail-qt1-f200.google.com (mail-qt1-f200.google.com
 [209.85.160.200]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-325-azuK9gvbPPyN0B6Tn0RgAA-1; Thu, 09 Jan 2020 09:57:34 -0500
X-MC-Unique: azuK9gvbPPyN0B6Tn0RgAA-1
Received: by mail-qt1-f200.google.com with SMTP id d18so4352372qtp.16
        for <kvm@vger.kernel.org>; Thu, 09 Jan 2020 06:57:34 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=dTjYPWrRS50vXb+awZBlOczchH8zUZfJ4o80FlJt42o=;
        b=N5aZlGEIxRSzHDl4msPObiG7COIeZOSCTGgDIlxuLWCGt3NAPIwm8UeqzoDs/wF7OA
         3ohSf20bR6Z0rAbiP3s9GfRfl94pLpPV/LGQIwr1GPTYBJ6CIPA33Hod+eyP4Sij0JXf
         DguuzSnje5aCzAxB955fJnkfgw1AiOALAMcz1zB+Vd//eoQbH0ZcIIfeRT/r5CEGmvdd
         Jy1feDSWNbNQhNJmrvE1zvxk8pLuO9/ii8tddMv1LeGQQCxFwTOtU7DMPO7Bt4X0eD9Y
         EGAMdVKFaXic/oyDuE3q3js/QCFCe/ze6FDvICslTB68SHOJ0nQWNu0wX59Pf3OhG/Wi
         gg/A==
X-Gm-Message-State: APjAAAW4oHiVJYZ9Ck4aUEfuSZJCPtJAQr7bOgGosCSrtpWkGU1LCh0f
        r39dg8D0bDRmlTpDOmed42MKnPDD6V9I8jzPMqYhxftp2pdYP01uPJu6Vhg9QORpJ6xGuGs0NQa
        Yk/it4bLo3cZQ
X-Received: by 2002:ae9:f442:: with SMTP id z2mr10147929qkl.130.1578581852981;
        Thu, 09 Jan 2020 06:57:32 -0800 (PST)
X-Google-Smtp-Source: 
 APXvYqwvlKadDyijtWYeJ2Wd9k4rTi/vdyU+ZnfMwnSTOg0LZPt/qEGbYJRt3o/7E1ao7PmCs8P0Ng==
X-Received: by 2002:ae9:f442:: with SMTP id z2mr10147895qkl.130.1578581852605;
        Thu, 09 Jan 2020 06:57:32 -0800 (PST)
Received: from xz-x1.yyz.redhat.com ([104.156.64.74])
        by smtp.gmail.com with ESMTPSA id q2sm3124179qkm.5.2020.01.09.06.57.30
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 09 Jan 2020 06:57:31 -0800 (PST)
From: Peter Xu <peterx@redhat.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: Christophe de Dinechin <dinechin@redhat.com>,
        "Michael S . Tsirkin" <mst@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Yan Zhao <yan.y.zhao@intel.com>,
        Alex Williamson <alex.williamson@redhat.com>,
        Jason Wang <jasowang@redhat.com>,
        Kevin Kevin <kevin.tian@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>, peterx@redhat.com,
        "Dr . David Alan Gilbert" <dgilbert@redhat.com>
Subject: [PATCH v3 00/21] KVM: Dirty ring interface
Date: Thu,  9 Jan 2020 09:57:08 -0500
Message-Id: <20200109145729.32898-1-peterx@redhat.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Branch is here: https://github.com/xzpeter/linux/tree/kvm-dirty-ring
(based on kvm/queue)

Please refer to either the previous cover letters, or documentation
update in patch 12 for the big picture.  Previous posts:

V1: https://lore.kernel.org/kvm/20191129213505.18472-1-peterx@redhat.com
V2: https://lore.kernel.org/kvm/20191221014938.58831-1-peterx@redhat.com

The major change in V3 is that we dropped the whole waitqueue and the
global lock. With that, we have clean per-vcpu ring and no default
ring any more.  The two kvmgt refactoring patches were also included
to show the dependency of the works.

Patchset layout:

Patch 1-2:         Picked up from kvmgt refactoring
Patch 3-6:         Small patches that are not directly related,
                   (So can be acked/nacked/picked as standalone)
Patch 7-11:        Prepares for the dirty ring interface
Patch 12:          Major implementation
Patch 13-14:       Quick follow-ups for patch 8
Patch 15-21:       Test cases

V3 changelog:

- fail userspace writable maps on dirty ring ranges [Jason]
- commit message fixups [Paolo]
- change __x86_set_memory_region to return hva [Paolo]
- cacheline align for indices [Paolo, Jason]
- drop waitqueue, global lock, etc., include kvmgt rework patchset
- take lock for __x86_set_memory_region() (otherwise it triggers a
  lockdep in latest kvm/queue) [Paolo]
- check KVM_DIRTY_LOG_PAGE_OFFSET in kvm_vm_ioctl_enable_dirty_log_ring
- one more patch to drop x86_set_memory_region [Paolo]
- one more patch to remove extra srcu usage in init_rmode_identity_map()
- add some r-bs for Paolo

Please review, thanks.

Paolo Bonzini (1):
  KVM: Move running VCPU from ARM to common code

Peter Xu (18):
  KVM: Remove kvm_read_guest_atomic()
  KVM: Add build-time error check on kvm_run size
  KVM: X86: Change parameter for fast_page_fault tracepoint
  KVM: X86: Don't take srcu lock in init_rmode_identity_map()
  KVM: Cache as_id in kvm_memory_slot
  KVM: X86: Drop x86_set_memory_region()
  KVM: X86: Don't track dirty for KVM_SET_[TSS_ADDR|IDENTITY_MAP_ADDR]
  KVM: Pass in kvm pointer into mark_page_dirty_in_slot()
  KVM: X86: Implement ring-based dirty memory tracking
  KVM: Make dirty ring exclusive to dirty bitmap log
  KVM: Don't allocate dirty bitmap if dirty ring is enabled
  KVM: selftests: Always clear dirty bitmap after iteration
  KVM: selftests: Sync uapi/linux/kvm.h to tools/
  KVM: selftests: Use a single binary for dirty/clear log test
  KVM: selftests: Introduce after_vcpu_run hook for dirty log test
  KVM: selftests: Add dirty ring buffer test
  KVM: selftests: Let dirty_log_test async for dirty ring test
  KVM: selftests: Add "-c" parameter to dirty log test

Yan Zhao (2):
  vfio: introduce vfio_iova_rw to read/write a range of IOVAs
  drm/i915/gvt: subsitute kvm_read/write_guest with vfio_iova_rw

 Documentation/virt/kvm/api.txt                |  96 ++++
 arch/arm/include/asm/kvm_host.h               |   2 -
 arch/arm64/include/asm/kvm_host.h             |   2 -
 arch/x86/include/asm/kvm_host.h               |   7 +-
 arch/x86/include/uapi/asm/kvm.h               |   1 +
 arch/x86/kvm/Makefile                         |   3 +-
 arch/x86/kvm/mmu/mmu.c                        |   6 +
 arch/x86/kvm/mmutrace.h                       |   9 +-
 arch/x86/kvm/svm.c                            |   3 +-
 arch/x86/kvm/vmx/vmx.c                        |  86 ++--
 arch/x86/kvm/x86.c                            |  43 +-
 drivers/gpu/drm/i915/gvt/kvmgt.c              |  25 +-
 drivers/vfio/vfio.c                           |  45 ++
 drivers/vfio/vfio_iommu_type1.c               |  81 ++++
 include/linux/kvm_dirty_ring.h                |  55 +++
 include/linux/kvm_host.h                      |  37 +-
 include/linux/vfio.h                          |   5 +
 include/trace/events/kvm.h                    |  78 ++++
 include/uapi/linux/kvm.h                      |  33 ++
 tools/include/uapi/linux/kvm.h                |  38 ++
 tools/testing/selftests/kvm/Makefile          |   2 -
 .../selftests/kvm/clear_dirty_log_test.c      |   2 -
 tools/testing/selftests/kvm/dirty_log_test.c  | 420 ++++++++++++++++--
 .../testing/selftests/kvm/include/kvm_util.h  |   4 +
 tools/testing/selftests/kvm/lib/kvm_util.c    |  72 +++
 .../selftests/kvm/lib/kvm_util_internal.h     |   3 +
 virt/kvm/arm/arch_timer.c                     |   2 +-
 virt/kvm/arm/arm.c                            |  29 --
 virt/kvm/arm/perf.c                           |   6 +-
 virt/kvm/arm/vgic/vgic-mmio.c                 |  15 +-
 virt/kvm/dirty_ring.c                         | 162 +++++++
 virt/kvm/kvm_main.c                           | 215 +++++++--
 32 files changed, 1379 insertions(+), 208 deletions(-)
 create mode 100644 include/linux/kvm_dirty_ring.h
 delete mode 100644 tools/testing/selftests/kvm/clear_dirty_log_test.c
 create mode 100644 virt/kvm/dirty_ring.c
```
#### [PATCH 00/15] Replace current_machine by qdev_get_machine()
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>

```c
From patchwork Thu Jan  9 15:21:18 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
 <philmd@redhat.com>
X-Patchwork-Id: 11325941
Return-Path: <SRS0=hq+s=26=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7D163109A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Jan 2020 15:21:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5BAE12072E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Jan 2020 15:21:54 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="HlRgdg4L"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730958AbgAIPVx (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 9 Jan 2020 10:21:53 -0500
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:28988 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727945AbgAIPVx (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 9 Jan 2020 10:21:53 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1578583311;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=P5RGdQrGsYtgUOKj0M4myzDzBUaBMtcy1aS0kbUYf64=;
        b=HlRgdg4L1OFxKuK1oL71gdPD2nLs5sEInQxTz/meMDlxcrBIgjIpGc5/87km2Q6QcKMaX6
        8tNR0boKB1PbNvm/vL7rZqs6Bquv9gU6Dn07jOadxA4vMJPb5hB5mO99TQrft2gxW9jXA5
        z7GY2FgOBhmKjwdp4kaglMzZYpyw1LA=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-334-Z6-I5PgHMWWbDGkeCQozUg-1; Thu, 09 Jan 2020 10:21:48 -0500
X-MC-Unique: Z6-I5PgHMWWbDGkeCQozUg-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id ACD758C2BE1;
        Thu,  9 Jan 2020 15:21:45 +0000 (UTC)
Received: from x1w.redhat.com (ovpn-204-180.brq.redhat.com [10.40.204.180])
        by smtp.corp.redhat.com (Postfix) with ESMTPS id F14D27FB5C;
        Thu,  9 Jan 2020 15:21:36 +0000 (UTC)
From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>
To: qemu-devel@nongnu.org
Cc: Marcelo Tosatti <mtosatti@redhat.com>,
 Peter Maydell <peter.maydell@linaro.org>, qemu-arm@nongnu.org,
 Eduardo Habkost <ehabkost@redhat.com>, Juan Quintela <quintela@redhat.com>,
 kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>,
 Marcel Apfelbaum <marcel.apfelbaum@gmail.com>,
 Alistair Francis <alistair.francis@wdc.com>, qemu-ppc@nongnu.org,
 "Dr. David Alan Gilbert" <dgilbert@redhat.com>,
 Richard Henderson <rth@twiddle.net>,
 David Gibson <david@gibson.dropbear.id.au>, =?utf-8?q?Philippe_Mathieu-Daud?=
	=?utf-8?q?=C3=A9?= <philmd@redhat.com>
Subject: [PATCH 00/15] Replace current_machine by qdev_get_machine()
Date: Thu,  9 Jan 2020 16:21:18 +0100
Message-Id: <20200109152133.23649-1-philmd@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Blurb from previous question [1]:

  "hw/boards.h" declare current_machine, and vl.c defines it:

    current_machine = MACHINE(object_new_with_class(OBJECT_CLASS(machine_class)));
    object_property_add_child(object_get_root(), "machine",
                              OBJECT(current_machine), &error_abort);

  The bigger user of 'current_machine' is the accel/KVM code.

  Recently in a0628599f..cc7d44c2e0 "Replace global smp variables
  with machine smp properties" we started to use MACHINE(qdev_get_machine()).
  Following a0628599f..cc7d44c2e0, a5e0b33119 use 'current_machine' again.

  qdev_get_machine() resolves the machine in the QOM composition tree.

Paolo answered [2]:

> I would always use MACHINE(qdev_get_machine()), espeecially outside
> vl.c.  Ideally, current_machine would be static within vl.c or even
> unused outside the object_property_add_child() that you quote above.

Let's remove the global current_machine.

I am still confused by this comment:

  /* qdev_get_machine() can return something that's not TYPE_MACHINE
   * if this is one of the user-only emulators; in that case there's
   * no need to check the ignore_memory_transaction_failures board flag.
   */

[1] https://www.mail-archive.com/qemu-devel@nongnu.org/msg669475.html
[2] https://www.mail-archive.com/qemu-devel@nongnu.org/msg669493.html

Philippe Mathieu-Daudé (15):
  target/arm/kvm: Use CPUState::kvm_state in kvm_arm_pmu_supported()
  hw/ppc/spapr_rtas: Use local MachineState variable
  hw/ppc/spapr_rtas: Access MachineState via SpaprMachineState argument
  hw/ppc/spapr_rtas: Restrict variables scope to single switch case
  device-hotplug: Replace current_machine by qdev_get_machine()
  migration/savevm: Replace current_machine by qdev_get_machine()
  hw/core/machine-qmp-cmds: Replace current_machine by
    qdev_get_machine()
  target/arm/monitor: Replace current_machine by qdev_get_machine()
  device_tree: Replace current_machine by qdev_get_machine()
  memory: Replace current_machine by qdev_get_machine()
  exec: Replace current_machine by qdev_get_machine()
  accel: Introduce the current_accel() method
  accel: Replace current_machine->accelerator by current_accel() method
  accel/accel: Replace current_machine by qdev_get_machine()
  vl: Make current_machine a local variable

 include/hw/boards.h        |  2 --
 include/sysemu/accel.h     |  2 ++
 accel/accel.c              |  7 +++++++
 accel/kvm/kvm-all.c        |  4 ++--
 accel/tcg/tcg-all.c        |  2 +-
 device-hotplug.c           |  2 +-
 device_tree.c              |  4 +++-
 exec.c                     | 10 ++++++----
 hw/core/machine-qmp-cmds.c |  4 ++--
 hw/ppc/spapr_rtas.c        |  6 +++---
 memory.c                   |  6 ++++--
 migration/savevm.c         | 10 +++++-----
 target/arm/kvm.c           |  4 +---
 target/arm/kvm64.c         |  4 ++--
 target/arm/monitor.c       |  3 ++-
 target/i386/kvm.c          |  2 +-
 target/ppc/kvm.c           |  2 +-
 vl.c                       |  6 +++---
 18 files changed, 46 insertions(+), 34 deletions(-)
```
#### [kvm-unit-tests PATCH v6 0/4] s390x: SCLP Unit test
##### From: Claudio Imbrenda <imbrenda@linux.ibm.com>

```c
From patchwork Thu Jan  9 16:16:21 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Claudio Imbrenda <imbrenda@linux.ibm.com>
X-Patchwork-Id: 11326127
Return-Path: <SRS0=hq+s=26=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B7AB5921
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Jan 2020 16:16:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 9E76C206ED
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Jan 2020 16:16:37 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2387541AbgAIQQg (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 9 Jan 2020 11:16:36 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:52866 "EHLO
        mx0b-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S2387527AbgAIQQe (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 9 Jan 2020 11:16:34 -0500
Received: from pps.filterd (m0127361.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 009G9mxL012399
        for <kvm@vger.kernel.org>; Thu, 9 Jan 2020 11:16:33 -0500
Received: from e06smtp04.uk.ibm.com (e06smtp04.uk.ibm.com [195.75.94.100])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2xdx6k4guj-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Thu, 09 Jan 2020 11:16:32 -0500
Received: from localhost
        by e06smtp04.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <imbrenda@linux.ibm.com>;
        Thu, 9 Jan 2020 16:16:29 -0000
Received: from b06avi18878370.portsmouth.uk.ibm.com (9.149.26.194)
        by e06smtp04.uk.ibm.com (192.168.101.134) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Thu, 9 Jan 2020 16:16:27 -0000
Received: from d06av22.portsmouth.uk.ibm.com (d06av22.portsmouth.uk.ibm.com
 [9.149.105.58])
        by b06avi18878370.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 009GGPhX38732092
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 9 Jan 2020 16:16:25 GMT
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 809494C040;
        Thu,  9 Jan 2020 16:16:25 +0000 (GMT)
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 442D84C044;
        Thu,  9 Jan 2020 16:16:25 +0000 (GMT)
Received: from p-imbrenda.boeblingen.de.ibm.com (unknown [9.152.224.108])
        by d06av22.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Thu,  9 Jan 2020 16:16:25 +0000 (GMT)
From: Claudio Imbrenda <imbrenda@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, thuth@redhat.com, david@redhat.com,
        borntraeger@de.ibm.com, frankja@linux.ibm.com
Subject: [kvm-unit-tests PATCH v6 0/4] s390x: SCLP Unit test
Date: Thu,  9 Jan 2020 17:16:21 +0100
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 20010916-0016-0000-0000-000002DBF725
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 20010916-0017-0000-0000-0000333E76DE
Message-Id: <20200109161625.154894-1-imbrenda@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-01-09_03:2020-01-09,2020-01-09 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 adultscore=0
 lowpriorityscore=0 phishscore=0 priorityscore=1501 bulkscore=0
 suspectscore=1 spamscore=0 mlxscore=0 malwarescore=0 impostorscore=0
 mlxlogscore=901 clxscore=1015 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-1910280000 definitions=main-2001090138
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patchset contains some minor cleanup, some preparatory work and
then the SCLP unit test itself.

The unit test checks the following:
    
    * Correctly ignoring instruction bits that should be ignored
    * Privileged instruction check
    * Check for addressing exceptions
    * Specification exceptions:
      - SCCB size less than 8
      - SCCB unaligned
      - SCCB overlaps prefix or lowcore
      - SCCB address higher than 2GB
    * Return codes for
      - Invalid command
      - SCCB too short (but at least 8)
      - SCCB page boundary violation

v5 -> v6
* fixed a bug in test_addressing
* improved comments in test_sccb_prefix
* replaced all inline assembly usages of spx and stpx with the wrappers
* added one more wrapper for test_one_sccb for read-only tests
v4 -> v5
* updated usage of report()
* added SPX and STPX wrappers to the library
* improved readability
* addressed some more comments
v3 -> v4
* export sclp_setup_int instead of copying it
* add more comments
* rename some more variables to improve readability
* improve the prefix test
* improved the invalid address test
* addressed further comments received during review
v2 -> v3
* generally improved the naming of variables
* added and fixed comments
* renamed test_one_run to test_one_simple
* added some const where needed
* addresed many more small comments received during review
v1 -> v2
* fix many small issues that came up during the first round of reviews
* add comments to each function
* use a static buffer for the SCCP template when used

Claudio Imbrenda (4):
  s390x: export sclp_setup_int
  s390x: sclp: add service call instruction wrapper
  s390x: lib: add SPX and STPX instruction wrapper
  s390x: SCLP unit test

 s390x/Makefile           |   1 +
 lib/s390x/asm/arch_def.h |  23 ++
 lib/s390x/sclp.h         |   1 +
 lib/s390x/sclp.c         |   9 +-
 s390x/intercept.c        |  33 ++-
 s390x/sclp.c             | 472 +++++++++++++++++++++++++++++++++++++++
 s390x/unittests.cfg      |   8 +
 7 files changed, 520 insertions(+), 27 deletions(-)
 create mode 100644 s390x/sclp.c
```
#### [PATCH v2 0/2] KVM: x86/mmu: Optimize rsvd pte checks
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Thu Jan  9 23:06:38 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11326433
Return-Path: <SRS0=hq+s=26=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CC0071398
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Jan 2020 23:06:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B3FA820656
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Jan 2020 23:06:47 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729009AbgAIXGl (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 9 Jan 2020 18:06:41 -0500
Received: from mga11.intel.com ([192.55.52.93]:54670 "EHLO mga11.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727749AbgAIXGl (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 9 Jan 2020 18:06:41 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga005.jf.intel.com ([10.7.209.41])
  by fmsmga102.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 09 Jan 2020 15:06:41 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.69,414,1571727600";
   d="scan'208";a="396242471"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by orsmga005.jf.intel.com with ESMTP; 09 Jan 2020 15:06:40 -0800
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org,
        David Laight <David.Laight@ACULAB.COM>,
        Arvind Sankar <nivedita@alum.mit.edu>
Subject: [PATCH v2 0/2] KVM: x86/mmu: Optimize rsvd pte checks
Date: Thu,  9 Jan 2020 15:06:38 -0800
Message-Id: <20200109230640.29927-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Two patches to optimize the reserved bit and illegal EPT memtype/XWR
checks, and more importantly, clean up an undocumented, subtle bitwise-OR
in the code.

v2: Rewrite everything.

v1: https://lkml.kernel.org/r/20200108001859.25254-1-sean.j.christopherson@intel.com

Sean Christopherson (2):
  KVM: x86/mmu: Reorder the reserved bit check in
    prefetch_invalid_gpte()
  KVM: x86/mmu: Micro-optimize nEPT's bad memptype/XWR checks

 arch/x86/kvm/mmu/mmu.c         | 26 ++++++++++++++------------
 arch/x86/kvm/mmu/paging_tmpl.h | 23 +++++++++++++++++++----
 2 files changed, 33 insertions(+), 16 deletions(-)
```
