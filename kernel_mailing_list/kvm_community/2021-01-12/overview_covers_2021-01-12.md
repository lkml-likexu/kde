

#### [PATCH v6 00/13] Generalize memory encryption models
##### From: David Gibson <david@gibson.dropbear.id.au>

```c
From patchwork Tue Jan 12 04:44:55 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Gibson <david@gibson.dropbear.id.au>
X-Patchwork-Id: 12012359
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 41A1CC433E0
	for <kvm@archiver.kernel.org>; Tue, 12 Jan 2021 04:45:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0C46A221FE
	for <kvm@archiver.kernel.org>; Tue, 12 Jan 2021 04:45:55 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731708AbhALEpy (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 11 Jan 2021 23:45:54 -0500
Received: from bilbo.ozlabs.org ([203.11.71.1]:41799 "EHLO ozlabs.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1731369AbhALEpx (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 11 Jan 2021 23:45:53 -0500
Received: by ozlabs.org (Postfix, from userid 1007)
        id 4DFJ0R0784z9sWC; Tue, 12 Jan 2021 15:45:10 +1100 (AEDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple;
        d=gibson.dropbear.id.au; s=201602; t=1610426711;
        bh=7hHllMpehAyZjZNsuKhkyTJVPh53/m3oZinqtAXXwig=;
        h=From:To:Cc:Subject:Date:From;
        b=jIoVRrqF9kp65OoqeHl3I+JcrR8Aao8xY6IDnC3P5tSNvuft/QMx4yw1G3taZ8Zrl
         tpSYa9cPixT/DRMOeibFsRXkGWHOmTHvfmwRXhV9kh4Uvwhc/ZXbcO1JiSGMb61ESf
         p6cYcCBEeSoVNl+l4Wg4GoOIANmq+61iwwMJYv6g=
From: David Gibson <david@gibson.dropbear.id.au>
To: pasic@linux.ibm.com, brijesh.singh@amd.com, pair@us.ibm.com,
        dgilbert@redhat.com, qemu-devel@nongnu.org
Cc: andi.kleen@intel.com, qemu-ppc@nongnu.org,
 Paolo Bonzini <pbonzini@redhat.com>, Marcelo Tosatti <mtosatti@redhat.com>,
 David Gibson <david@gibson.dropbear.id.au>, Greg Kurz <groug@kaod.org>,
 frankja@linux.ibm.com, thuth@redhat.com,
 Christian Borntraeger <borntraeger@de.ibm.com>, mdroth@linux.vnet.ibm.com,
 richard.henderson@linaro.org, kvm@vger.kernel.org, =?utf-8?q?Daniel_P=2E_Be?=
	=?utf-8?q?rrang=C3=A9?= <berrange@redhat.com>,
 Marcel Apfelbaum <marcel.apfelbaum@gmail.com>,
 Eduardo Habkost <ehabkost@redhat.com>, david@redhat.com,
 Cornelia Huck <cohuck@redhat.com>, mst@redhat.com, qemu-s390x@nongnu.org,
 pragyansri.pathi@intel.com, jun.nakajima@intel.com
Subject: [PATCH v6 00/13] Generalize memory encryption models
Date: Tue, 12 Jan 2021 15:44:55 +1100
Message-Id: <20210112044508.427338-1-david@gibson.dropbear.id.au>
X-Mailer: git-send-email 2.29.2
MIME-Version: 1.0
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
"confidential-guest-support" property pointing to a platform specific
object which configures and manages the specific details.

Note to Ram Pai: the documentation I've included for PEF is very
minimal.  If you could send a patch expanding on that, it would be
very helpful.

Changes since v5:
 * Renamed from "securable guest memory" to "confidential guest
   support"
 * Simpler reworking of x86 boot time flash encryption
 * Added a bunch of documentation
 * Fixed some compile errors on POWER
Changes since v4:
 * Renamed from "host trust limitation" to "securable guest memory",
   which I think is marginally more descriptive
 * Re-organized initialization, because the previous model called at
   kvm_init didn't work for s390
 * Assorted fixes to the s390 implementation; rudimentary testing
   (gitlab CI) only
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

David Gibson (12):
  confidential guest support: Introduce new confidential guest support
    class
  sev: Remove false abstraction of flash encryption
  confidential guest support: Move side effect out of
    machine_set_memory_encryption()
  confidential guest support: Rework the "memory-encryption" property
  sev: Add Error ** to sev_kvm_init()
  confidential guest support: Introduce cgs "ready" flag
  confidential guest support: Move SEV initialization into arch specific
    code
  confidential guest support: Update documentation
  spapr: Add PEF based confidential guest support
  spapr: PEF: prevent migration
  confidential guest support: Alter virtio default properties for
    protected guests
  s390: Recognize confidential-guest-support option

Greg Kurz (1):
  qom: Allow optional sugar props

 accel/kvm/kvm-all.c                       |  38 -------
 accel/kvm/sev-stub.c                      |  10 +-
 accel/stubs/kvm-stub.c                    |  10 --
 backends/confidential-guest-support.c     |  30 ++++++
 backends/meson.build                      |   1 +
 docs/amd-memory-encryption.txt            |   2 +-
 docs/confidential-guest-support.txt       |  48 +++++++++
 docs/papr-pef.txt                         |  30 ++++++
 docs/system/s390x/protvirt.rst            |  19 ++--
 hw/core/machine.c                         |  71 +++++++++++--
 hw/i386/pc_sysfw.c                        |  17 ++-
 hw/ppc/meson.build                        |   1 +
 hw/ppc/pef.c                              | 122 ++++++++++++++++++++++
 hw/ppc/spapr.c                            |  10 ++
 hw/s390x/pv.c                             |  58 ++++++++++
 include/exec/confidential-guest-support.h |  48 +++++++++
 include/hw/boards.h                       |   2 +-
 include/hw/ppc/pef.h                      |  26 +++++
 include/hw/s390x/pv.h                     |   1 +
 include/qemu/typedefs.h                   |   1 +
 include/qom/object.h                      |   3 +-
 include/sysemu/kvm.h                      |  16 ---
 include/sysemu/sev.h                      |   4 +-
 qom/object.c                              |   4 +-
 softmmu/rtc.c                             |   3 +-
 softmmu/vl.c                              |  17 +--
 target/i386/kvm/kvm.c                     |  12 +++
 target/i386/sev-stub.c                    |   5 +
 target/i386/sev.c                         |  93 +++++++----------
 target/ppc/kvm.c                          |  18 ----
 target/ppc/kvm_ppc.h                      |   6 --
 target/s390x/kvm.c                        |   3 +
 32 files changed, 540 insertions(+), 189 deletions(-)
 create mode 100644 backends/confidential-guest-support.c
 create mode 100644 docs/confidential-guest-support.txt
 create mode 100644 docs/papr-pef.txt
 create mode 100644 hw/ppc/pef.c
 create mode 100644 include/exec/confidential-guest-support.h
 create mode 100644 include/hw/ppc/pef.h
```
#### [PATCH v4 0/2] System Generation ID driver and VMGENID backend
##### From: Adrian Catangiu <acatan@amazon.com>

```c
From patchwork Tue Jan 12 12:15:58 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Adrian Catangiu <acatan@amazon.com>
X-Patchwork-Id: 12013337
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-14.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 88839C433E6
	for <kvm@archiver.kernel.org>; Tue, 12 Jan 2021 12:17:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 44F3B23107
	for <kvm@archiver.kernel.org>; Tue, 12 Jan 2021 12:17:47 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732675AbhALMRa (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 12 Jan 2021 07:17:30 -0500
Received: from smtp-fw-6002.amazon.com ([52.95.49.90]:21019 "EHLO
        smtp-fw-6002.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1732299AbhALMRa (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 12 Jan 2021 07:17:30 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.com; i=@amazon.com; q=dns/txt; s=amazon201209;
  t=1610453847; x=1641989847;
  h=from:to:cc:subject:date:message-id:mime-version:
   content-transfer-encoding;
  bh=tF+5LWSipsSfv/MpNTU2XOkSQBgOPGBmsF5sLnQRVvI=;
  b=A1FvrYH7NKrhzLt0kkpD9RYxfl9Kqi8AjptzODDcmyd4npmojVXPTz7f
   /bqegMuf1w7twUocRHBoDVOOzzR0JC0zwbr3caiA7J4D2N2QQELs8FKHz
   8Arr1ecsIGLGBLNA0b9rb388vbOQH0gnrwIbj7/+80zrDcMhDQ/IIS3x5
   o=;
X-IronPort-AV: E=Sophos;i="5.79,341,1602547200";
   d="scan'208";a="77011747"
Received: from iad12-co-svc-p1-lb1-vlan2.amazon.com (HELO
 email-inbound-relay-1d-16425a8d.us-east-1.amazon.com) ([10.43.8.2])
  by smtp-border-fw-out-6002.iad6.amazon.com with ESMTP;
 12 Jan 2021 12:16:39 +0000
Received: from EX13D08EUB004.ant.amazon.com
 (iad12-ws-svc-p26-lb9-vlan3.iad.amazon.com [10.40.163.38])
        by email-inbound-relay-1d-16425a8d.us-east-1.amazon.com (Postfix) with
 ESMTPS id 1E6F6100F90;
        Tue, 12 Jan 2021 12:16:29 +0000 (UTC)
Received: from uf6ed9c851f4556.ant.amazon.com (10.43.161.68) by
 EX13D08EUB004.ant.amazon.com (10.43.166.158) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Tue, 12 Jan 2021 12:16:15 +0000
From: Adrian Catangiu <acatan@amazon.com>
To: <linux-doc@vger.kernel.org>, <linux-kernel@vger.kernel.org>,
        <qemu-devel@nongnu.org>, <kvm@vger.kernel.org>,
        <linux-s390@vger.kernel.org>
CC: <gregkh@linuxfoundation.org>, <graf@amazon.com>, <arnd@arndb.de>,
        <ebiederm@xmission.com>, <rppt@kernel.org>, <0x7f454c46@gmail.com>,
        <borntraeger@de.ibm.com>, <Jason@zx2c4.com>, <jannh@google.com>,
        <w@1wt.eu>, <colmmacc@amazon.com>, <luto@kernel.org>,
        <tytso@mit.edu>, <ebiggers@kernel.org>, <dwmw@amazon.co.uk>,
        <bonzini@gnu.org>, <sblbir@amazon.com>, <raduweis@amazon.com>,
        <corbet@lwn.net>, <mst@redhat.com>, <mhocko@kernel.org>,
        <rafael@kernel.org>, <pavel@ucw.cz>, <mpe@ellerman.id.au>,
        <areber@redhat.com>, <ovzxemul@gmail.com>, <avagin@gmail.com>,
        <ptikhomirov@virtuozzo.com>, <gil@azul.com>, <asmehra@redhat.com>,
        <dgunigun@redhat.com>, <vijaysun@ca.ibm.com>, <oridgar@gmail.com>,
        <ghammer@redhat.com>, Adrian Catangiu <acatan@amazon.com>
Subject: [PATCH v4 0/2] System Generation ID driver and VMGENID backend
Date: Tue, 12 Jan 2021 14:15:58 +0200
Message-ID: <1610453760-13812-1-git-send-email-acatan@amazon.com>
X-Mailer: git-send-email 2.7.4
MIME-Version: 1.0
X-Originating-IP: [10.43.161.68]
X-ClientProxiedBy: EX13D50UWC001.ant.amazon.com (10.43.162.96) To
 EX13D08EUB004.ant.amazon.com (10.43.166.158)
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This feature is aimed at virtualized or containerized environments
where VM or container snapshotting duplicates memory state, which is a
challenge for applications that want to generate unique data such as
request IDs, UUIDs, and cryptographic nonces.

The patch set introduces a mechanism that provides a userspace
interface for applications and libraries to be made aware of uniqueness
breaking events such as VM or container snapshotting, and allow them to
react and adapt to such events.

Solving the uniqueness problem strongly enough for cryptographic
purposes requires a mechanism which can deterministically reseed
userspace PRNGs with new entropy at restore time. This mechanism must
also support the high-throughput and low-latency use-cases that led
programmers to pick a userspace PRNG in the first place; be usable by
both application code and libraries; allow transparent retrofitting
behind existing popular PRNG interfaces without changing application
code; it must be efficient, especially on snapshot restore; and be
simple enough for wide adoption.

The first patch in the set implements a device driver which exposes a
read-only device /dev/sysgenid to userspace, which contains a
monotonically increasing u32 generation counter. Libraries and
applications are expected to open() the device, and then call read()
which blocks until the SysGenId changes. Following an update, read()
calls no longer block until the application acknowledges the new
SysGenId by write()ing it back to the device. Non-blocking read() calls
return EAGAIN when there is no new SysGenId available. Alternatively,
libraries can mmap() the device to get a single shared page which
contains the latest SysGenId at offset 0.

SysGenId also supports a notification mechanism exposed as two IOCTLs
on the device. SYSGENID_GET_OUTDATED_WATCHERS immediately returns the
number of file descriptors to the device that were open during the last
SysGenId change but have not yet acknowledged the new id.
SYSGENID_WAIT_WATCHERS blocks until there are no open file handles on
the device which haven’t acknowledged the new id. These two interfaces
are intended for serverless and container control planes, which want to
confirm that all application code has detected and reacted to the new
SysGenId before sending an invoke to the newly-restored sandbox.

The second patch in the set adds a VmGenId driver which makes use of
the ACPI vmgenid device to drive SysGenId and to reseed kernel entropy
on VM snapshots.
---

v3 -> v4:

  - split functionality in two separate kernel modules: 
    1. drivers/misc/sysgenid.c which provides the generic userspace
       interface and mechanisms
    2. drivers/virt/vmgenid.c as VMGENID acpi device driver that seeds
       kernel entropy and acts as a driving backend for the generic
       sysgenid
  - renamed /dev/vmgenid -> /dev/sysgenid
  - renamed uapi header file vmgenid.h -> sysgenid.h
  - renamed ioctls VMGENID_* -> SYSGENID_*
  - added ‘min_gen’ parameter to SYSGENID_FORCE_GEN_UPDATE ioctl
  - fixed races in documentation examples
  - various style nits
  - rebased on top of linus latest

v2 -> v3:

  - separate the core driver logic and interface, from the ACPI device.
    The ACPI vmgenid device is now one possible backend.
  - fix issue when timeout=0 in VMGENID_WAIT_WATCHERS
  - add locking to avoid races between fs ops handlers and hw irq
    driven generation updates
  - change VMGENID_WAIT_WATCHERS ioctl so if the current caller is
    outdated or a generation change happens while waiting (thus making
    current caller outdated), the ioctl returns -EINTR to signal the
    user to handle event and retry. Fixes blocking on oneself.
  - add VMGENID_FORCE_GEN_UPDATE ioctl conditioned by
    CAP_CHECKPOINT_RESTORE capability, through which software can force
    generation bump.

v1 -> v2:

  - expose to userspace a monotonically increasing u32 Vm Gen Counter
    instead of the hw VmGen UUID
  - since the hw/hypervisor-provided 128-bit UUID is not public
    anymore, add it to the kernel RNG as device randomness
  - insert driver page containing Vm Gen Counter in the user vma in
    the driver's mmap handler instead of using a fault handler
  - turn driver into a misc device driver to auto-create /dev/vmgenid
  - change ioctl arg to avoid leaking kernel structs to userspace
  - update documentation
  - various nits
  - rebase on top of linus latest

Adrian Catangiu (2):
  drivers/misc: sysgenid: add system generation id driver
  drivers/virt: vmgenid: add vm generation id driver

 Documentation/misc-devices/sysgenid.rst | 240 +++++++++++++++++++++++++
 Documentation/virt/vmgenid.rst          |  34 ++++
 drivers/misc/Kconfig                    |  16 ++
 drivers/misc/Makefile                   |   1 +
 drivers/misc/sysgenid.c                 | 298 ++++++++++++++++++++++++++++++++
 drivers/virt/Kconfig                    |  14 ++
 drivers/virt/Makefile                   |   1 +
 drivers/virt/vmgenid.c                  | 153 ++++++++++++++++
 include/uapi/linux/sysgenid.h           |  18 ++
 9 files changed, 775 insertions(+)
 create mode 100644 Documentation/misc-devices/sysgenid.rst
 create mode 100644 Documentation/virt/vmgenid.rst
 create mode 100644 drivers/misc/sysgenid.c
 create mode 100644 drivers/virt/vmgenid.c
 create mode 100644 include/uapi/linux/sysgenid.h
```
#### [kvm-unit-tests PATCH v4 0/9] s390x: Add SIE library and simple tests
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
From patchwork Tue Jan 12 13:20:45 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 12013471
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 77929C433E0
	for <kvm@archiver.kernel.org>; Tue, 12 Jan 2021 13:22:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1F37422571
	for <kvm@archiver.kernel.org>; Tue, 12 Jan 2021 13:22:32 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732358AbhALNV4 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 12 Jan 2021 08:21:56 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:51368 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1729303AbhALNV4 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 12 Jan 2021 08:21:56 -0500
Received: from pps.filterd (m0098413.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 10CDG8Fk184721;
        Tue, 12 Jan 2021 08:21:14 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=IWj/54VTi75ZD4lwJOBWscmuML0OT0LXJ6DNcd/ZqsM=;
 b=FzImBZUN09lLDxXxyIkFXscplrMb0lDDc2fm15sTV7N6l5BMhlCLRu1Z9VZqtS5BjEA+
 sv+/hIsEp9y35A4SpEBYKh0ycJTqWp0Bm1zRVwVTNDAdBUUTIMv/4ymgrkHfBEMd1JYY
 5SNdoEGseP0BhTAb1bgVNXetlZDg22vfI/Weyl9CwnyF6bCzlRP3iGHsbXcHoaaLuzmx
 mzUA+V8D5ZEyZiUeAdmnpEkDuiYy4v7VNmtMadk6eQUTzSlpmkVhRy4UrOXStpGFz5pe
 DWMematlZHCUqUuZ6uHjhCCMuYEyd5LE3a3qRP32y6yFLDZDhoF1pEknOyIauQl1f3fE eg==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 361cgmr397-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 12 Jan 2021 08:21:14 -0500
Received: from m0098413.ppops.net (m0098413.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 10CDI26q192592;
        Tue, 12 Jan 2021 08:21:14 -0500
Received: from ppma03ams.nl.ibm.com (62.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.98])
        by mx0b-001b2d01.pphosted.com with ESMTP id 361cgmr38c-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 12 Jan 2021 08:21:14 -0500
Received: from pps.filterd (ppma03ams.nl.ibm.com [127.0.0.1])
        by ppma03ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 10CDHSGi015940;
        Tue, 12 Jan 2021 13:21:12 GMT
Received: from b06cxnps3074.portsmouth.uk.ibm.com
 (d06relay09.portsmouth.uk.ibm.com [9.149.109.194])
        by ppma03ams.nl.ibm.com with ESMTP id 35y447unt1-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 12 Jan 2021 13:21:12 +0000
Received: from d06av22.portsmouth.uk.ibm.com (d06av22.portsmouth.uk.ibm.com
 [9.149.105.58])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 10CDL91k27394492
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 12 Jan 2021 13:21:09 GMT
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 472704C044;
        Tue, 12 Jan 2021 13:21:09 +0000 (GMT)
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 7E9954C059;
        Tue, 12 Jan 2021 13:21:08 +0000 (GMT)
Received: from linux01.pok.stglabs.ibm.com (unknown [9.114.17.81])
        by d06av22.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue, 12 Jan 2021 13:21:08 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: thuth@redhat.com, david@redhat.com, borntraeger@de.ibm.com,
        imbrenda@linux.ibm.com, cohuck@redhat.com,
        linux-s390@vger.kernel.org
Subject: [kvm-unit-tests PATCH v4 0/9] s390x: Add SIE library and simple tests
Date: Tue, 12 Jan 2021 08:20:45 -0500
Message-Id: <20210112132054.49756-1-frankja@linux.ibm.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.343,18.0.737
 definitions=2021-01-12_07:2021-01-12,2021-01-12 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 adultscore=0 spamscore=0
 impostorscore=0 suspectscore=0 priorityscore=1501 lowpriorityscore=0
 clxscore=1015 mlxlogscore=999 mlxscore=0 bulkscore=0 phishscore=0
 malwarescore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2101120071
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is the absolute minimum needed to run VMs inside the KVM Unit
Tests. It's more of a base for other tests that I can't (yet) publish
than an addition of tests that check KVM functionality. However, I
wanted to decrease the number of WIP patches in my private
branch. Once the library is available maybe others will come and
extend the SIE test itself.

Yes, I have added VM management functionality like VM create/destroy,
etc but as it is not needed right now, I'd like to exclude it from
this patch set for now.

v4:
	* Removed asm directory and moved all asm files into s390x/ (I changed my view)
	* Review fixes
	* Removed a stray newline in the asm offsets file

v3:
	* Rebased on re-license patches
	* Split assembly
	* Now using ICPT_* constants
	* Added read_info asserts
	* Fixed missing spin_lock() in smp.c lib
	* Replaced duplicated code in sie test with generic intercept test
	* Replaced uv-guest.x bit testing with test_bit_inv()
	* Some other minor cleanups

Gitlab:
https://gitlab.com/frankja/kvm-unit-tests/-/tree/sie

CI:
https://gitlab.com/frankja/kvm-unit-tests/-/pipelines/240506525


Janosch Frank (9):
  s390x: Add test_bit to library
  s390x: Consolidate sclp read info
  s390x: SCLP feature checking
  s390x: Split assembly into multiple files
  s390x: sie: Add SIE to lib
  s390x: sie: Add first SIE test
  s390x: Add diag318 intercept test
  s390x: Fix sclp.h style issues
  s390x: sclp: Add CPU entry offset comment

 lib/s390x/asm-offsets.c  |  11 +++
 lib/s390x/asm/arch_def.h |   9 ++
 lib/s390x/asm/bitops.h   |  26 ++++++
 lib/s390x/asm/facility.h |   3 +-
 lib/s390x/interrupt.c    |   7 ++
 lib/s390x/io.c           |   2 +
 lib/s390x/sclp.c         |  57 +++++++++--
 lib/s390x/sclp.h         | 181 +++++++++++++++++++----------------
 lib/s390x/sie.h          | 197 +++++++++++++++++++++++++++++++++++++++
 lib/s390x/smp.c          |  27 +++---
 s390x/Makefile           |   7 +-
 s390x/cstart64.S         | 119 +----------------------
 s390x/intercept.c        |  19 ++++
 s390x/lib.S              | 121 ++++++++++++++++++++++++
 s390x/macros.S           |  77 +++++++++++++++
 s390x/sie.c              | 113 ++++++++++++++++++++++
 s390x/unittests.cfg      |   3 +
 s390x/uv-guest.c         |   6 +-
 18 files changed, 761 insertions(+), 224 deletions(-)
 create mode 100644 lib/s390x/sie.h
 create mode 100644 s390x/lib.S
 create mode 100644 s390x/macros.S
 create mode 100644 s390x/sie.c
```
#### [PATCH 0/2] KVM: SVM: Track physical cpu and asid_generation via the
##### From: Cathy Avery <cavery@redhat.com>

```c
From patchwork Tue Jan 12 16:43:11 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Cathy Avery <cavery@redhat.com>
X-Patchwork-Id: 12014061
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 92144C433E9
	for <kvm@archiver.kernel.org>; Tue, 12 Jan 2021 16:44:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 49CDE23107
	for <kvm@archiver.kernel.org>; Tue, 12 Jan 2021 16:44:53 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2404872AbhALQoo (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 12 Jan 2021 11:44:44 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:28931 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S2404683AbhALQoo (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 12 Jan 2021 11:44:44 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1610469798;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=RUslB6q7RxjLtV6kH7HKHwCBZnZvPnq5E+zwqql6G8Y=;
        b=Fhax8wXJ/mrrJrjwApexltD/hWx9PNVfaPdANoKmH4Gfw8ObSVvHvW9p+36v5Frcl22Yfe
        9rqm1fzhVabJUwLn0l5rZpHnjV5QcnzESB5g/6M8UbE21hjvVrp1kkXx+UiuCvFhZSpCk+
        zpGgwef09ZSgHGdn2nlVkHorEpJoYrk=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-565-mwIeKspGNryfQOsFEelNyw-1; Tue, 12 Jan 2021 11:43:15 -0500
X-MC-Unique: mwIeKspGNryfQOsFEelNyw-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 5A72B51F7;
        Tue, 12 Jan 2021 16:43:14 +0000 (UTC)
Received: from virtlab710.virt.lab.eng.bos.redhat.com
 (virtlab710.virt.lab.eng.bos.redhat.com [10.19.152.252])
        by smtp.corp.redhat.com (Postfix) with ESMTP id BC9435C1B4;
        Tue, 12 Jan 2021 16:43:13 +0000 (UTC)
From: Cathy Avery <cavery@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        pbonzini@redhat.com
Cc: vkuznets@redhat.com, wei.huang2@amd.com,
        sean.j.christopherson@intel.com
Subject: [PATCH 0/2] KVM: SVM: Track physical cpu and asid_generation via the
 vmcb
Date: Tue, 12 Jan 2021 11:43:11 -0500
Message-Id: <20210112164313.4204-1-cavery@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In the cases where vmcbs change processors from one vmrun to another updated
information in the vmcb from a prior run can potentially be lost. By tracking
the physical cpu and asid_generation per vmcb instead of svm->vcpu the following
scenario illustrated by Paolo can be avoided.

     ---------------------          ---------------------
     pCPU 1                         pCPU 2
     ---------------------          ---------------------
     run VMCB02
                                    run VMCB02 (*)
                                    run VMCB01
     run VMCB01 (**)
     run VMCB02 (***)
     ---------------------          ---------------------

     After the point marked (*), while L2 runs, some fields change in VMCB02.
     When the processor vmexits back to L0, VMCB02 is marked clean.

     At the point marked (**), svm->vcpu.cpu becomes 1 again.

     Therefore, at the point marked (***) you will get svm->vcpu.cpu == cpu
     and the VMCB02 will not be marked dirty.  The processor can then incorrectly
     use some data that is cached from before point (*).

Theses patches are intended for the kvm nested-svm branch.

The patches have been tested on nested fedora VMs, kvm self tests, and kvm-unit-tests.
They have not been tested on SEV.

Cathy Avery (2):
  KVM: nSVM: Track the physical cpu of the vmcb vmrun through the vmcb
  KVM: nSVM: Track the ASID generation of the vmcb vmrun through the
    vmcb

 arch/x86/kvm/svm/svm.c | 45 +++++++++++++++++++++++-------------------
 arch/x86/kvm/svm/svm.h |  3 ++-
 2 files changed, 27 insertions(+), 21 deletions(-)
```
#### [PATCH 00/24] Allow parallel page faults with TDP MMU
##### From: Ben Gardon <bgardon@google.com>

```c
From patchwork Tue Jan 12 18:10:17 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ben Gardon <bgardon@google.com>
X-Patchwork-Id: 12014295
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 56AA4C433E0
	for <kvm@archiver.kernel.org>; Tue, 12 Jan 2021 18:11:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 240C42311D
	for <kvm@archiver.kernel.org>; Tue, 12 Jan 2021 18:11:55 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388490AbhALSL3 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 12 Jan 2021 13:11:29 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:56648 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726091AbhALSL0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 12 Jan 2021 13:11:26 -0500
Received: from mail-pg1-x549.google.com (mail-pg1-x549.google.com
 [IPv6:2607:f8b0:4864:20::549])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 15FCDC061786
        for <kvm@vger.kernel.org>; Tue, 12 Jan 2021 10:10:46 -0800 (PST)
Received: by mail-pg1-x549.google.com with SMTP id 1so2138419pgu.17
        for <kvm@vger.kernel.org>; Tue, 12 Jan 2021 10:10:46 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:message-id:mime-version:subject:from:to:cc;
        bh=fnzL0jDAo9xIfWQHPhjTRvzsU8/hpdoL+ymw2yPPaR8=;
        b=bqh/tCOplimzhw8TJ/Fx5s21Ja85FXBo8arh+ndM+lpHS+EJqewnynGxBMBabsKe6Y
         4EkJd/rR++NPUXHuDM8q6sVB7GoNERQ4XLPc90D/kLMCnqKPa6UNr5QFVPg8xMBDg/lt
         ncSAj9qRn4ANhmZ9y2LyOcqxg1KY6Lg3ec3whFr9zuYwlOF7PgFcBkgcyF9Lh1qmi7Ph
         dKcMrkVm5EdCA8oGV3WsDCaEgZ/SpUlH3We7Hc+/5qhQYpccgdkxuT42jInXXyaHLM5F
         BWpHN1LQ4Fkbv63GwcnRzTMd1DBHTvIpoKUmZRu+NZIdLw7HDvghPTTkc6wSZh0EFEbp
         yJxg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:message-id:mime-version:subject:from
         :to:cc;
        bh=fnzL0jDAo9xIfWQHPhjTRvzsU8/hpdoL+ymw2yPPaR8=;
        b=J8tcScoM/dBYzjXK+LifG9XKOc3xi/hSQOSliyhK4LGgpEEU17AqcYWQiPNHvXEG61
         +C5WS3LFkA/vycYM8EPAMBahodhht0COd0PW+q1sogRNvO04OiIiFto1ZZzGCCgdvFjV
         hB0Oi/2F7aWW9cvMa/BdlqGWNozH9ey15aN2mUcY0SG639VJAPZrQNnt5JxChP91cbtI
         l7JS+cxiZr0GrL/aFrY6/7vHjqWO91t/l4KqfuGh3C13lYK2NbGacpVmQ4R7zQWxaX9m
         R2XTP1yIqGxtERPZ4ce8SobGr5Uqnyr5+tzPa4QXibUZqDBvukuV/N3wGmeTZNCBdIk0
         ouqA==
X-Gm-Message-State: AOAM532WjR7cpQlkfu9+AAuPvLRiRkhHRJDKjw0zGpjJlqfWOJvrX/Tf
        l4zsw73LjF+2rrAj7aWEqY1g8AtCHnhE
X-Google-Smtp-Source: 
 ABdhPJwEwgh4q6rWDhbMv93t+vDodjDTTzM72nf4MGU5I/ay3h4PAvJKiXoGPcBhiCK05TLEdRtqvwbl4qkv
Sender: "bgardon via sendgmr" <bgardon@bgardon.sea.corp.google.com>
X-Received: from bgardon.sea.corp.google.com
 ([2620:15c:100:202:f693:9fff:fef4:a293])
 (user=bgardon job=sendgmr) by 2002:a17:902:ab97:b029:de:30a:5234 with SMTP id
 f23-20020a170902ab97b02900de030a5234mr301190plr.55.1610475045535; Tue, 12 Jan
 2021 10:10:45 -0800 (PST)
Date: Tue, 12 Jan 2021 10:10:17 -0800
Message-Id: <20210112181041.356734-1-bgardon@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.30.0.284.gd98b1dd5eaa7-goog
Subject: [PATCH 00/24] Allow parallel page faults with TDP MMU
From: Ben Gardon <bgardon@google.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>, Peter Xu <peterx@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Peter Shier <pshier@google.com>,
        Peter Feiner <pfeiner@google.com>,
        Junaid Shahid <junaids@google.com>,
        Jim Mattson <jmattson@google.com>,
        Yulei Zhang <yulei.kernel@gmail.com>,
        Wanpeng Li <kernellwp@gmail.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Xiao Guangrong <xiaoguangrong.eric@gmail.com>,
        Ben Gardon <bgardon@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The TDP MMU was implemented to simplify and improve the performance of
KVM's memory management on modern hardware with TDP (EPT / NPT). To build
on the existing performance improvements of the TDP MMU, add the ability
to handle vCPU page faults in parallel. In the current implementation,
vCPU page faults (actually EPT/NPT violations/misconfigurations) are the
largest source of MMU lock contention on VMs with many vCPUs. This
contention, and the resulting page fault latency, can soft-lock guests
and degrade performance. Handling page faults in parallel is especially
useful when booting VMs, enabling dirty logging, and handling demand
paging. In all these cases vCPUs are constantly incurring  page faults on
each new page accessed.

Broadly, the following changes were required to allow parallel page
faults:
-- Contention detection and yielding added to rwlocks to bring them up to
   feature parity with spin locks, at least as far as the use of the MMU
   lock is concerned.
-- TDP MMU page table memory is protected with RCU and freed in RCU
   callbacks to allow multiple threads to operate on that memory
   concurrently.
-- When the TDP MMU is enabled, a rwlock is used instead of a spin lock on
   x86. This allows the page fault handlers to acquire the MMU lock in read
   mode and handle page faults in parallel while other operations maintain
   exclusive use of the lock by acquiring it in write mode.
-- An additional lock is added to protect some data structures needed by
   the page fault handlers, for relatively infrequent operations.
-- The page fault handler is modified to use atomic cmpxchgs to set SPTEs
   and some page fault handler operations are modified slightly to work
   concurrently with other threads.

This series also contains a few bug fixes and optimizations, related to
the above, but not strictly part of enabling parallel page fault handling.

Performance testing:
The KVM selftests dirty_log_perf_test demonstrates the performance
improvements associated with this patch series. The dirty_log_perf test
was run on a two socket Indus Skylake, with a VM with 96 vCPUs.
5 get-dirty-log iterations were run. Each test was run 3 times and the
results averaged. The test was conducted with 3 different variables:
Overlapping versus partitioned memory
With overlapping memory vCPUs are more likely to incur retries handling
parallel page faults, so the TDP MMU with parallel page faults is expected
to fare the worst in this situation.
Partitioned memory between vCPUs is a best case for parallel page faults
with the TDP MMU as it should minimize contention and retries.
When running with partitioned memory, 3G was allocated for each vCPU's
data region. When running with overlapping memory accesses, a total of 6G
was allocated for the VM's data region. This meant that the VM was much
smaller overall, but each vCPU had more memory to access. Since the VMs
were very different in size, the results cannot be reliably compared. The
VM sizes were chosen to balance test runtime and repeatability of results.
The option to overlap memory accesses will be added to dirty_log_perf_test
in a (near-)future series.
With this patch set applied versus without
In these tests the series was applied on commit:
9f1abbe97c08 Merge tag 'for_linus' of git://git.kernel.org/pub/scm/linux/kernel/git/mst/vhost
That commit was also used as the baseline.
TDP MMU enabled versus disabled
This is primarily included to ensure that this series does not regress
performance with the TDP MMU disabled.

Does this series improve performance with the TDP MMU enabled?

Baseline, TDP MMU enabled, partitioned accesses:
Populate memory time (s)		110.193
Enabling dirty logging time (s)		4.829
Dirty memory time (s)			3.949
Get dirty log time (s)			0.822
Disabling dirty logging time (s)	2.995
Parallel PFs series, TDP MMU enabled, partitioned accesses:
Populate memory time (s)		16.112
Enabling dirty logging time (s)		7.057
Dirty memory time (s)			0.275
Get dirty log time (s)			5.468
Disabling dirty logging time (s)	3.088

This scenario demonstrates the big win in this series: an 85% reduction in
the time taken to populate memory! Note that the time taken to dirty memory
is much shorter and the time to get the dirty log higher with this series.

Baseline, TDP MMU enabled, overlapping accesses:
Populate memory time (s)		117.31
Enabling dirty logging time (s)		0.191
Dirty memory time (s)			0.193
Get dirty log time (s)			2.33
Disabling dirty logging time (s)	0.059
Parallel PFs series, TDP MMU enabled, overlapping accesses:
Populate memory time (s)		141.155
Enabling dirty logging time (s)		0.245
Dirty memory time (s)			0.236
Get dirty log time (s)			2.35
Disabling dirty logging time (s)	0.075

With overlapping accesses, we can see that this parallel page faults
series actually reduces performance when populating memory. In profiling,
it appeared that most of the time was spent in get_user_pages, so it's
possible the extra concurrency hit the main MM subsystem harder, creating
contention there.

Does this series degrade performance with the TDP MMU disabled?

Baseline, TDP MMU disabled, partitioned accesses:
Populate memory time (s)		110.193
Enabling dirty logging time (s)		4.829
Dirty memory time (s)			3.949
Get dirty log time (s)			0.822
Disabling dirty logging time (s)	2.995
Parallel PFs series, TDP MMU disabled, partitioned accesses:
Populate memory time (s)		110.917
Enabling dirty logging time (s)		5.196
Dirty memory time (s)			4.559
Get dirty log time (s)			0.879
Disabling dirty logging time (s)	3.278

Here we can see that the parallel PFs series appears to have made enabling
and disabling dirty logging, and dirtying memory slightly slower. It's
possible that this is a result of additional checks around MMU lock
acquisition.

Baseline, TDP MMU disabled, overlapping accesses:
Populate memory time (s)		103.115
Enabling dirty logging time (s)		0.222
Dirty memory time (s)			0.189
Get dirty log time (s)			2.341
Disabling dirty logging time (s)	0.126
Parallel PFs series, TDP MMU disabled, overlapping accesses:
Populate memory time (s)		85.392
Enabling dirty logging time (s)		0.224
Dirty memory time (s)			0.201
Get dirty log time (s)			2.363
Disabling dirty logging time (s)	0.131

From the above results we can see that the parallel PF series only had a
significant effect on the population time, with overlapping accesses and
the TDP MMU disabled. It is not currently known what in this series caused
the improvement.

Correctness testing:
The following tests were performed with an SMP kernel and DBX kernel on an
Intel Skylake machine. The tests were run both with and without the TDP
MMU enabled.
-- This series introduces no new failures in kvm-unit-tests
SMP + no TDP MMU no new failures
SMP + TDP MMU no new failures
DBX + no TDP MMU no new failures
DBX + TDP MMU no new failures
-- All KVM selftests behave as expected
SMP + no TDP MMU all pass except ./x86_64/vmx_preemption_timer_test
SMP + TDP MMU all pass except ./x86_64/vmx_preemption_timer_test
(./x86_64/vmx_preemption_timer_test also fails without this patch set,
both with the TDP MMU on and off.)
DBX + no TDP MMU all pass
DBX + TDP MMU all pass
-- A VM can be booted running a Debian 9 and all memory accessed
SMP + no TDP MMU works
SMP + TDP MMU works
DBX + no TDP MMU works
DBX + TDP MMU works
Cross-compilation was also checked for PowerPC and ARM64.

This series can be viewed in Gerrit at:
https://linux-review.googlesource.com/c/linux/kernel/git/torvalds/linux/+/7172

Ben Gardon (24):
  locking/rwlocks: Add contention detection for rwlocks
  sched: Add needbreak for rwlocks
  sched: Add cond_resched_rwlock
  kvm: x86/mmu: change TDP MMU yield function returns to match
    cond_resched
  kvm: x86/mmu: Fix yielding in TDP MMU
  kvm: x86/mmu: Skip no-op changes in TDP MMU functions
  kvm: x86/mmu: Add comment on __tdp_mmu_set_spte
  kvm: x86/mmu: Add lockdep when setting a TDP MMU SPTE
  kvm: x86/mmu: Don't redundantly clear TDP MMU pt memory
  kvm: x86/mmu: Factor out handle disconnected pt
  kvm: x86/mmu: Put TDP MMU PT walks in RCU read-critical section
  kvm: x86/kvm: RCU dereference tdp mmu page table links
  kvm: x86/mmu: Only free tdp_mmu pages after a grace period
  kvm: mmu: Wrap mmu_lock lock / unlock in a function
  kvm: mmu: Wrap mmu_lock cond_resched and needbreak
  kvm: mmu: Wrap mmu_lock assertions
  kvm: mmu: Move mmu_lock to struct kvm_arch
  kvm: x86/mmu: Use an rwlock for the x86 TDP MMU
  kvm: x86/mmu: Protect tdp_mmu_pages with a lock
  kvm: x86/mmu: Add atomic option for setting SPTEs
  kvm: x86/mmu: Use atomic ops to set SPTEs in TDP MMU map
  kvm: x86/mmu: Flush TLBs after zap in TDP MMU PF handler
  kvm: x86/mmu: Freeze SPTEs in disconnected pages
  kvm: x86/mmu: Allow parallel page faults for the TDP MMU

 Documentation/virt/kvm/locking.rst       |   2 +-
 arch/arm64/include/asm/kvm_host.h        |   2 +
 arch/arm64/kvm/arm.c                     |   2 +
 arch/arm64/kvm/mmu.c                     |  40 +-
 arch/mips/include/asm/kvm_host.h         |   2 +
 arch/mips/kvm/mips.c                     |  10 +-
 arch/mips/kvm/mmu.c                      |  20 +-
 arch/powerpc/include/asm/kvm_book3s_64.h |   7 +-
 arch/powerpc/include/asm/kvm_host.h      |   2 +
 arch/powerpc/kvm/book3s_64_mmu_host.c    |   4 +-
 arch/powerpc/kvm/book3s_64_mmu_hv.c      |  12 +-
 arch/powerpc/kvm/book3s_64_mmu_radix.c   |  32 +-
 arch/powerpc/kvm/book3s_64_vio_hv.c      |   4 +-
 arch/powerpc/kvm/book3s_hv.c             |   8 +-
 arch/powerpc/kvm/book3s_hv_nested.c      |  59 ++-
 arch/powerpc/kvm/book3s_hv_rm_mmu.c      |  14 +-
 arch/powerpc/kvm/book3s_mmu_hpte.c       |  10 +-
 arch/powerpc/kvm/e500_mmu_host.c         |   6 +-
 arch/powerpc/kvm/powerpc.c               |   2 +
 arch/s390/include/asm/kvm_host.h         |   2 +
 arch/s390/kvm/kvm-s390.c                 |   2 +
 arch/x86/include/asm/kvm_host.h          |  23 +
 arch/x86/kvm/mmu/mmu.c                   | 189 ++++++--
 arch/x86/kvm/mmu/mmu_internal.h          |  16 +-
 arch/x86/kvm/mmu/page_track.c            |   8 +-
 arch/x86/kvm/mmu/paging_tmpl.h           |   8 +-
 arch/x86/kvm/mmu/spte.h                  |  16 +-
 arch/x86/kvm/mmu/tdp_iter.c              |   6 +-
 arch/x86/kvm/mmu/tdp_mmu.c               | 540 +++++++++++++++++++----
 arch/x86/kvm/x86.c                       |   4 +-
 drivers/gpu/drm/i915/gvt/kvmgt.c         |  12 +-
 include/asm-generic/qrwlock.h            |  24 +-
 include/linux/kvm_host.h                 |   7 +-
 include/linux/rwlock.h                   |   7 +
 include/linux/sched.h                    |  29 ++
 kernel/sched/core.c                      |  40 ++
 virt/kvm/dirty_ring.c                    |   4 +-
 virt/kvm/kvm_main.c                      |  58 ++-
 38 files changed, 938 insertions(+), 295 deletions(-)
```
#### [RFC PATCH 0/7] Support for virtio-net hash reporting
##### From: Yuri Benditovich <yuri.benditovich@daynix.com>

```c
From patchwork Tue Jan 12 19:41:36 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yuri Benditovich <yuri.benditovich@daynix.com>
X-Patchwork-Id: 12014743
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 0A340C4332E
	for <kvm@archiver.kernel.org>; Tue, 12 Jan 2021 19:43:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E4EBD2310E
	for <kvm@archiver.kernel.org>; Tue, 12 Jan 2021 19:43:11 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2406787AbhALTnA (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 12 Jan 2021 14:43:00 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:48366 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2406619AbhALTnA (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 12 Jan 2021 14:43:00 -0500
Received: from mail-wm1-x336.google.com (mail-wm1-x336.google.com
 [IPv6:2a00:1450:4864:20::336])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 582D8C0617A2
        for <kvm@vger.kernel.org>; Tue, 12 Jan 2021 11:41:56 -0800 (PST)
Received: by mail-wm1-x336.google.com with SMTP id y23so3237084wmi.1
        for <kvm@vger.kernel.org>; Tue, 12 Jan 2021 11:41:56 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=daynix-com.20150623.gappssmtp.com; s=20150623;
        h=from:to:cc:subject:date:message-id;
        bh=9oioH7fTimHXbwiOIluI6SOkD883+857JncYScStEP4=;
        b=JmO6IQKgjQY+7ho4ih3Bdmj0eRPnup/UlujCGZhO4AJhanp3QH0J71/SQjiI8RlftE
         LxVkn1U86G3tkyTL1V1ekzv7AG4aQUuBC1r0RvRBoERwudQRkTXIem4aavnr56WrANo8
         gOtBpR9pRxwKu1xDJhfk/82GSYbgzv2ibgNt5w0f4THTbGm6h2zSgqNsqz15NEjpA55j
         jhso19OBmu3jzIh6d8tb1TXJSzru4eS/fD3T3nWv1umUB8RNCOvvnnPdOKeCNLkCN3mh
         BIGrXTEThybGX1OaJSNIbNpsSW/dNQUVwxByoyviBmYkIkBVcUXJ03lrcjitMvDn4T//
         igkw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=9oioH7fTimHXbwiOIluI6SOkD883+857JncYScStEP4=;
        b=rLxWvbhmCW6fzosECY/I3yKCnfPVHF7XdpPlMR/7I7Q5Z8zWUeEZcGjkRsTY+X3Zc9
         a06QrTb3DAE6viIcu+jtYdkC00RMayqpsvICoKwv2kc7cFWN1aFa5oPqeumyJ0iqEpp5
         ONYMiR30/jmaWXQ7DWMlYw/4q1/8eqdLNzwDTYoQp7JmROKF95fxn4sqQ3Scd2WobP4c
         BpP3gmTtgKj1bOnJ0Yu4zJOIhx1QWnGw2OCb/YnggraHBOeiMwlU4ynaTfud4trxbhBs
         PHQaXocJtweqYYrEXu0vrVnk00I6j/KO/De/catdnXKg1W8hiLyQUspJUsbAFX6cvqQe
         7GLA==
X-Gm-Message-State: AOAM533/NEvsQjeJZ82Ln6CzozEwrFCtLuLutmNw6fAlkvmDbSHiOkSg
        Ov4sjMfF1ALndslgQUaumFpMIg==
X-Google-Smtp-Source: 
 ABdhPJxLSdWWpfIxaQGNHeFfQoIuyfHcKNbVYBL99mebz4m6+1+6/6514Is75EyggDSS6XrPJMXKGw==
X-Received: by 2002:a1c:b742:: with SMTP id h63mr780567wmf.122.1610480514861;
        Tue, 12 Jan 2021 11:41:54 -0800 (PST)
Received: from f2.redhat.com (bzq-79-183-72-147.red.bezeqint.net.
 [79.183.72.147])
        by smtp.gmail.com with ESMTPSA id
 z63sm4885315wme.8.2021.01.12.11.41.51
        (version=TLS1_2 cipher=ECDHE-ECDSA-CHACHA20-POLY1305 bits=256/256);
        Tue, 12 Jan 2021 11:41:54 -0800 (PST)
From: Yuri Benditovich <yuri.benditovich@daynix.com>
To: davem@davemloft.net, kuba@kernel.org, mst@redhat.com,
        jasowang@redhat.com, ast@kernel.org, daniel@iogearbox.net,
        andrii@kernel.org, kafai@fb.com, songliubraving@fb.com, yhs@fb.com,
        john.fastabend@gmail.com, kpsingh@kernel.org,
        rdunlap@infradead.org, willemb@google.com, gustavoars@kernel.org,
        herbert@gondor.apana.org.au, steffen.klassert@secunet.com,
        nogikh@google.com, pablo@netfilter.org, decui@microsoft.com,
        cai@lca.pw, jakub@cloudflare.com, elver@google.com,
        pabeni@redhat.com, netdev@vger.kernel.org,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org, bpf@vger.kernel.org
Cc: yan@daynix.com
Subject: [RFC PATCH 0/7] Support for virtio-net hash reporting
Date: Tue, 12 Jan 2021 21:41:36 +0200
Message-Id: <20210112194143.1494-1-yuri.benditovich@daynix.com>
X-Mailer: git-send-email 2.17.1
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Existing TUN module is able to use provided "steering eBPF" to
calculate per-packet hash and derive the destination queue to
place the packet to. The eBPF uses mapped configuration data
containing a key for hash calculation and indirection table
with array of queues' indices.

This series of patches adds support for virtio-net hash reporting
feature as defined in virtio specification. It extends the TUN module
and the "steering eBPF" as follows:

Extended steering eBPF calculates the hash value and hash type, keeps
hash value in the skb->hash and returns index of destination virtqueue
and the type of the hash. TUN module keeps returned hash type in
(currently unused) field of the skb. 
skb->__unused renamed to 'hash_report_type'.

When TUN module is called later to allocate and fill the virtio-net
header and push it to destination virtqueue it populates the hash
and the hash type into virtio-net header.

VHOST driver is made aware of respective virtio-net feature that
extends the virtio-net header to report the hash value and hash report
type.

Yuri Benditovich (7):
  skbuff: define field for hash report type
  vhost: support for hash report virtio-net feature
  tun: allow use of BPF_PROG_TYPE_SCHED_CLS program type
  tun: free bpf_program by bpf_prog_put instead of bpf_prog_destroy
  tun: add ioctl code TUNSETHASHPOPULATION
  tun: populate hash in virtio-net header when needed
  tun: report new tun feature IFF_HASH

 drivers/net/tun.c           | 43 +++++++++++++++++++++++++++++++------
 drivers/vhost/net.c         | 37 ++++++++++++++++++++++++-------
 include/linux/skbuff.h      |  7 +++++-
 include/uapi/linux/if_tun.h |  2 ++
 4 files changed, 74 insertions(+), 15 deletions(-)
```
#### [PATCH 0/6] KVM: selftests: Perf test cleanups and memslot
##### From: Ben Gardon <bgardon@google.com>

```c
From patchwork Tue Jan 12 21:42:47 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ben Gardon <bgardon@google.com>
X-Patchwork-Id: 12014905
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=unavailable autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B3A51C07542
	for <kvm@archiver.kernel.org>; Tue, 12 Jan 2021 21:46:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8C16323122
	for <kvm@archiver.kernel.org>; Tue, 12 Jan 2021 21:46:09 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732066AbhALVqB (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 12 Jan 2021 16:46:01 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:46406 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1731990AbhALVn6 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 12 Jan 2021 16:43:58 -0500
Received: from mail-qv1-xf4a.google.com (mail-qv1-xf4a.google.com
 [IPv6:2607:f8b0:4864:20::f4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 5A48EC0617A9
        for <kvm@vger.kernel.org>; Tue, 12 Jan 2021 13:42:58 -0800 (PST)
Received: by mail-qv1-xf4a.google.com with SMTP id t17so51581qvv.17
        for <kvm@vger.kernel.org>; Tue, 12 Jan 2021 13:42:58 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:message-id:mime-version:subject:from:to:cc;
        bh=U+CbYhEX3bk6CbEgkAzVDMsXIsxbjmYTO8NB12RiUfg=;
        b=ZYv6sEPqBHAArWWsUp2QL2JuEOAXcxNJ/TbleUpNix3Zom4HvsFXD6eBgs0/JiuL8S
         RcC1e//0CvYuIWl8eVu13IUXE/CsevnVnke/u6pKoUh8iiHXOER4VvVQafnlPnmlAft8
         IPP4Z4TjBYoZLIA6As9ZWQ3/6zwgdW1r/QykaNd0NxkuFhTYSFysEDk58A8TKx8oCI+4
         niiR71NrYJaivrHtLYhDIPWFeH4AHZhSo8YIrSKNB19Oq8kd94F/lH+OGNbCfTSoPYIe
         fJ8FVeeiInuJ3Tlo0Ydy1IEQ4MNRWlX3hErJuv9pGKd75FQd+Htl2xNJa6mB45RXHbDK
         5RGQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:message-id:mime-version:subject:from
         :to:cc;
        bh=U+CbYhEX3bk6CbEgkAzVDMsXIsxbjmYTO8NB12RiUfg=;
        b=F13pz6H6g1R1vI0RaGR1ZWwMqcc6VZr79ygJ5Wi7hFjbgq8LcArOwfQoVUod3u3WKR
         X+Bp8v4pxPsPeuQoprQ9oYXi8Io4DCTI9q9nP/nWjHG6nUmSuAu4s9cH7lXj+Buw3Z1F
         8ltVFaXotdvlAGMOWRwlGyi7AIo6Bbh0QwDOxFVa8fYHkd1fUx5KfQc9WcSc3mw3a/Sk
         wDqzkIf8kg9Zjn11X8VG++sRS3yIPdPZhsH7T/oVLUf9a+9f/d18/N9UzSEX4AEKEEB5
         j6pNPz3sHHZdlHTV1vjYrCQihto7qmx+AlDElLeqSX9Ru1/pH8viI4zc62aZ0ZDGaKby
         cyFw==
X-Gm-Message-State: AOAM531p0sC1mFsMHhivVpZCx4pYUty9wAkh5xRrp6r4l2y0bE9NNyT5
        3OE5hDeEfJm4BpuTkEckfI9NmtudFrin
X-Google-Smtp-Source: 
 ABdhPJwcwZH2KZ2pN7t1zlwuuRyYOL6A378R4xORgoSVJhlmFt3unwT0CSROZTnrTQpMBKu6C2QJNlR2YppO
Sender: "bgardon via sendgmr" <bgardon@bgardon.sea.corp.google.com>
X-Received: from bgardon.sea.corp.google.com
 ([2620:15c:100:202:f693:9fff:fef4:a293])
 (user=bgardon job=sendgmr) by 2002:a0c:da87:: with SMTP id
 z7mr1679434qvj.41.1610487777488; Tue, 12 Jan 2021 13:42:57 -0800 (PST)
Date: Tue, 12 Jan 2021 13:42:47 -0800
Message-Id: <20210112214253.463999-1-bgardon@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.30.0.284.gd98b1dd5eaa7-goog
Subject: [PATCH 0/6] KVM: selftests: Perf test cleanups and memslot
 modification test
From: Ben Gardon <bgardon@google.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        linux-kselftest@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>, Peter Xu <peterx@redhat.com>,
        Andrew Jones <drjones@redhat.com>,
        Peter Shier <pshier@google.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Thomas Huth <thuth@redhat.com>, Jacob Xu <jacobhxu@google.com>,
        Makarand Sonare <makarandsonare@google.com>,
        Ben Gardon <bgardon@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series contains a few cleanups that didn't make it into previous
series, including some cosmetic changes and small bug fixes. The series
also lays the groundwork for a memslot modification test which stresses
the memslot update and page fault code paths in an attempt to expose races.

Tested: dirty_log_perf_test, memslot_modification_stress_test, and
	demand_paging_test were run, with all the patches in this series
	applied, on an Intel Skylake machine.

	echo Y > /sys/module/kvm/parameters/tdp_mmu; \
	./memslot_modification_stress_test -i 1000 -v 64 -b 1G; \
	./memslot_modification_stress_test -i 1000 -v 64 -b 64M -o; \
	./dirty_log_perf_test -v 64 -b 1G; \
	./dirty_log_perf_test -v 64 -b 64M -o; \
	./demand_paging_test -v 64 -b 1G; \
	./demand_paging_test -v 64 -b 64M -o; \
	echo N > /sys/module/kvm/parameters/tdp_mmu; \
	./memslot_modification_stress_test -i 1000 -v 64 -b 1G; \
	./memslot_modification_stress_test -i 1000 -v 64 -b 64M -o; \
	./dirty_log_perf_test -v 64 -b 1G; \
	./dirty_log_perf_test -v 64 -b 64M -o; \
	./demand_paging_test -v 64 -b 1G; \
	./demand_paging_test -v 64 -b 64M -o

	The tests behaved as expected, and fixed the problem of the
	population stage being skipped in dirty_log_perf_test. This can be
	seen in the output, with the population stage taking about the time
	dirty pass 1 took and dirty pass 1 falling closer to the times for
	the other passes.

Note that when running these tests, the -o option causes the test to take
much longer as the work each vCPU must do increases proportional to the
number of vCPUs.

You can view this series in Gerrit at:
https://linux-review.googlesource.com/c/linux/kernel/git/torvalds/linux/+/7216

Ben Gardon (6):
  KVM: selftests: Rename timespec_diff_now to timespec_elapsed
  KVM: selftests: Avoid flooding debug log while populating memory
  KVM: selftests: Convert iterations to int in dirty_log_perf_test
  KVM: selftests: Fix population stage in dirty_log_perf_test
  KVM: selftests: Add option to overlap vCPU memory access
  KVM: selftests: Add memslot modification stress test

 tools/testing/selftests/kvm/.gitignore        |   1 +
 tools/testing/selftests/kvm/Makefile          |   1 +
 .../selftests/kvm/demand_paging_test.c        |  40 +++-
 .../selftests/kvm/dirty_log_perf_test.c       |  72 +++---
 .../selftests/kvm/include/perf_test_util.h    |   4 +-
 .../testing/selftests/kvm/include/test_util.h |   2 +-
 .../selftests/kvm/lib/perf_test_util.c        |  25 ++-
 tools/testing/selftests/kvm/lib/test_util.c   |   2 +-
 .../kvm/memslot_modification_stress_test.c    | 211 ++++++++++++++++++
 9 files changed, 307 insertions(+), 51 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/memslot_modification_stress_test.c
```
