

#### [PATCH v7 0/2] System Generation ID driver and VMGENID backend
##### From: Adrian Catangiu <acatan@amazon.com>

```c
From patchwork Wed Feb 24 08:47:30 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Adrian Catangiu <acatan@amazon.com>
X-Patchwork-Id: 12101531
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7D1EFC4332D
	for <kvm@archiver.kernel.org>; Wed, 24 Feb 2021 08:50:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3332264D74
	for <kvm@archiver.kernel.org>; Wed, 24 Feb 2021 08:50:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234567AbhBXIuN (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 24 Feb 2021 03:50:13 -0500
Received: from smtp-fw-6001.amazon.com ([52.95.48.154]:61481 "EHLO
        smtp-fw-6001.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S234392AbhBXIs7 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 24 Feb 2021 03:48:59 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.com; i=@amazon.com; q=dns/txt; s=amazon201209;
  t=1614156537; x=1645692537;
  h=from:to:cc:subject:date:message-id:mime-version:
   content-transfer-encoding;
  bh=/R8Bcf3qXRH0sz3GRvHFXvpgzilNaYT4N1/kR6A7D8E=;
  b=c38IPhQVfy9Jv2JFvtptN4FMyurlwQqG1buNxFfYbyN+ywNkXqlTdjrv
   OJsu2GG6HvDEnn8wip4SN7DJE5pr2q7QCHi1mvhQcarA98otWGUTliy33
   YqyZwvwdwlGGfTbtURMBe0+7ypt2Lgwxh18ZZubF8fwo9aHpVxyQeqwFc
   c=;
X-IronPort-AV: E=Sophos;i="5.81,202,1610409600";
   d="scan'208";a="91601605"
Received: from iad12-co-svc-p1-lb1-vlan2.amazon.com (HELO
 email-inbound-relay-1a-715bee71.us-east-1.amazon.com) ([10.43.8.2])
  by smtp-border-fw-out-6001.iad6.amazon.com with ESMTP;
 24 Feb 2021 08:48:09 +0000
Received: from EX13D08EUB004.ant.amazon.com
 (iad12-ws-svc-p26-lb9-vlan2.iad.amazon.com [10.40.163.34])
        by email-inbound-relay-1a-715bee71.us-east-1.amazon.com (Postfix) with
 ESMTPS id B296FA20A1;
        Wed, 24 Feb 2021 08:47:57 +0000 (UTC)
Received: from uf6ed9c851f4556.ant.amazon.com (10.43.160.157) by
 EX13D08EUB004.ant.amazon.com (10.43.166.158) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Wed, 24 Feb 2021 08:47:42 +0000
From: Adrian Catangiu <acatan@amazon.com>
To: <linux-doc@vger.kernel.org>, <linux-kernel@vger.kernel.org>,
        <qemu-devel@nongnu.org>, <kvm@vger.kernel.org>,
        <linux-s390@vger.kernel.org>
CC: <gregkh@linuxfoundation.org>, <graf@amazon.com>,
        <rdunlap@infradead.org>, <arnd@arndb.de>, <ebiederm@xmission.com>,
        <rppt@kernel.org>, <0x7f454c46@gmail.com>,
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
Subject: [PATCH v7 0/2] System Generation ID driver and VMGENID backend
Date: Wed, 24 Feb 2021 10:47:30 +0200
Message-ID: <1614156452-17311-1-git-send-email-acatan@amazon.com>
X-Mailer: git-send-email 2.7.4
MIME-Version: 1.0
X-Originating-IP: [10.43.160.157]
X-ClientProxiedBy: EX13D38UWC002.ant.amazon.com (10.43.162.46) To
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
the /dev/sysgenid char device to userspace. Its associated filesystem
operations operations can be used to build a system level safe workflow
that guest software can follow to protect itself from negative system
snapshot effects.

The second patch in the set adds a VmGenId driver which makes use of
the ACPI vmgenid device to drive SysGenId and to reseed kernel entropy
following VM snapshots.

**Please note**, SysGenID alone does not guarantee complete snapshot
safety to applications using it. A certain workflow needs to be
followed at the system level, in order to make the system
snapshot-resilient. Please see the "Snapshot Safety Prerequisites"
section in the included SysGenID documentation.
---

v6 -> v7:
  - remove sysgenid uevent

v5 -> v6:

  - sysgenid: watcher tracking disabled by default
  - sysgenid: add SYSGENID_SET_WATCHER_TRACKING ioctl to allow each
    file descriptor to set whether they should be tracked as watchers
  - rename SYSGENID_FORCE_GEN_UPDATE -> SYSGENID_TRIGGER_GEN_UPDATE
  - rework all documentation to clearly capture all prerequisites for
    achieving snapshot safety when using the provided mechanism
  - sysgenid documentation: replace individual filesystem operations
    examples with a higher level example showcasing system-level
    snapshot-safe workflow

v4 -> v5:

  - sysgenid: generation changes are also exported through uevents
  - remove SYSGENID_GET_OUTDATED_WATCHERS ioctl
  - document sysgenid ioctl major/minor numbers

v3 -> v4:

  - split functionality in two separate kernel modules: 
    1. drivers/misc/sysgenid.c which provides the generic userspace
       interface and mechanisms
    2. drivers/virt/vmgenid.c as VMGENID acpi device driver that seeds
       kernel entropy and acts as a driving backend for the generic
       sysgenid
  - rename /dev/vmgenid -> /dev/sysgenid
  - rename uapi header file vmgenid.h -> sysgenid.h
  - rename ioctls VMGENID_* -> SYSGENID_*
  - add ‘min_gen’ parameter to SYSGENID_FORCE_GEN_UPDATE ioctl
  - fix races in documentation examples

v2 -> v3:

  - separate the core driver logic and interface, from the ACPI device.
    The ACPI vmgenid device is now one possible backend
  - fix issue when timeout=0 in VMGENID_WAIT_WATCHERS
  - add locking to avoid races between fs ops handlers and hw irq
    driven generation updates
  - change VMGENID_WAIT_WATCHERS ioctl so if the current caller is
    outdated or a generation change happens while waiting (thus making
    current caller outdated), the ioctl returns -EINTR to signal the
    user to handle event and retry. Fixes blocking on oneself
  - add VMGENID_FORCE_GEN_UPDATE ioctl conditioned by
    CAP_CHECKPOINT_RESTORE capability, through which software can force
    generation bump

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

Adrian Catangiu (2):
  drivers/misc: sysgenid: add system generation id driver
  drivers/virt: vmgenid: add vm generation id driver

 Documentation/misc-devices/sysgenid.rst            | 229 +++++++++++++++
 Documentation/userspace-api/ioctl/ioctl-number.rst |   1 +
 Documentation/virt/vmgenid.rst                     |  36 +++
 MAINTAINERS                                        |  15 +
 drivers/misc/Kconfig                               |  15 +
 drivers/misc/Makefile                              |   1 +
 drivers/misc/sysgenid.c                            | 322 +++++++++++++++++++++
 drivers/virt/Kconfig                               |  13 +
 drivers/virt/Makefile                              |   1 +
 drivers/virt/vmgenid.c                             | 153 ++++++++++
 include/uapi/linux/sysgenid.h                      |  18 ++
 11 files changed, 804 insertions(+)
 create mode 100644 Documentation/misc-devices/sysgenid.rst
 create mode 100644 Documentation/virt/vmgenid.rst
 create mode 100644 drivers/misc/sysgenid.c
 create mode 100644 drivers/virt/vmgenid.c
 create mode 100644 include/uapi/linux/sysgenid.h
```
#### [PATCH v3 0/5] KVM: x86: dump_vmcs: don't assume GUEST_IA32_EFER,
##### From: David Edmondson <david.edmondson@oracle.com>

```c
From patchwork Wed Feb 24 13:29:14 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Edmondson <david.edmondson@oracle.com>
X-Patchwork-Id: 12101903
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,
	UNPARSEABLE_RELAY,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E50FBC433DB
	for <kvm@archiver.kernel.org>; Wed, 24 Feb 2021 14:16:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9749064EDD
	for <kvm@archiver.kernel.org>; Wed, 24 Feb 2021 14:16:49 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S235091AbhBXOL6 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 24 Feb 2021 09:11:58 -0500
Received: from aserp2130.oracle.com ([141.146.126.79]:37966 "EHLO
        aserp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S232673AbhBXNcH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 24 Feb 2021 08:32:07 -0500
Received: from pps.filterd (aserp2130.oracle.com [127.0.0.1])
        by aserp2130.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 11ODTMUv160548;
        Wed, 24 Feb 2021 13:29:28 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : content-transfer-encoding : content-type :
 mime-version; s=corp-2020-01-29;
 bh=iys3HEbXDXRkK+VKVQuM+F8FtraW1Rp6yixwV/lQN4k=;
 b=d1wmejH0Locuner3Kxga+Zmv67k8Oseez1Or0BFaNSYa2r8x3iDCGl53NqSfP6eihq/g
 aG7OdOWraWGhigBlTWU+fMkmT+eCNVGsUlXqXymCjEKumM26dq6HZXL0KgIudYtJCALh
 moxy2+Qu8Vn+h0FAHXf2F0FnOdyJTHGXIVivsUjS39YqA+vYBGIcq5rjWys25DCU1/A1
 k3XnPglvfdWQwsisuTTdOp75qtz4FyGmLWuuZh7EDVg4knFVKg64Ew0sdl7ip8aSN8y4
 RFfZv0JL7ceVPHmFEuZHjdF9iwiBkr5RRUn86pPoBCbZWyWMEhyRi5DXR6dIcvXSYmIB Lw==
Received: from aserp3020.oracle.com (aserp3020.oracle.com [141.146.126.70])
        by aserp2130.oracle.com with ESMTP id 36vr6258dr-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 24 Feb 2021 13:29:28 +0000
Received: from pps.filterd (aserp3020.oracle.com [127.0.0.1])
        by aserp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 11ODOabE081658;
        Wed, 24 Feb 2021 13:29:27 GMT
Received: from nam11-dm6-obe.outbound.protection.outlook.com
 (mail-dm6nam11lp2171.outbound.protection.outlook.com [104.47.57.171])
        by aserp3020.oracle.com with ESMTP id 36ucb0r5ts-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 24 Feb 2021 13:29:27 +0000
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=CW108FDxX1Kf3WRRXFUn87qDUqKHHB5AggVXaK72r4HQ+YY8wntHbVXLtUk9OLGF7pky+Hw0znTuFI5mgoJnWzD0Axj7+gQsUPQqXbTsnQiSpB49h4CG1BdN/ow8ovvx92mr7jI5as8Ap65sJ1QQ551xXRWASAru+7RLFSETUsfSpC1yIZM0fQEUVJtKZlvEaShYvyRIG9FYaC0UwztX0PR75z2qSNEe5XrJCblgMOqxkPh6HgFuc7ltH8VvLn1GitjbY0c4eBzGhFMrQkFfXI4M6F0W5OoaHU8uSWXkhF3JCMAJK2eXGMmecD5iu0VMRQJUwA4ZtfBuRBU8R2OTSA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=iys3HEbXDXRkK+VKVQuM+F8FtraW1Rp6yixwV/lQN4k=;
 b=gKdfc1GP6yvxWWyG9KDiPPeD191QSSLEjihXq4yZWfKWByslYfwpTt07l9LfORwN8o+VB7hwvBK+uiKcHI/3aszQenxxHtsEsEiKz2pcvfXufL/admCl5nIJzAGgTEt5tBBFRMm9G1lEu8DGA8KDi0Y925XrCyvI47Qdr7irjCwmmnyhw0yLKPgNH2QRnhRQY0yVoBS/hBzcfSWWc9hvzWCf1Rr5nHkxVDAtFPi9+wQHvwYSV/JSJTvIoRfTqNDvbtxf8NG6nRWzdmwz4sHr3ATVhWU8mE4wIJACXancab+r1SV6/cnm6nV8zG32U+hXX+UmIczQhECTH9zsZXNy2A==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=oracle.com; dmarc=pass action=none header.from=oracle.com;
 dkim=pass header.d=oracle.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=oracle.onmicrosoft.com; s=selector2-oracle-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=iys3HEbXDXRkK+VKVQuM+F8FtraW1Rp6yixwV/lQN4k=;
 b=qGROGt9jouzWTLFlho+2pgL/3KgVNLm0+a6yGrNWm6PwnXSsTKIfjiwEBgKfN/ZjbqJeIxJpVEK3l+kQ/WMnr65C/Jq8cHo/Ih5gS5poQaGRaj8r7h38JNmc+dllXKjMfjQ+t11GQSxt5GkDyRr9k+kkvuvtQgijQ89n0n11D68=
Authentication-Results: redhat.com; dkim=none (message not signed)
 header.d=none;redhat.com; dmarc=none action=none header.from=oracle.com;
Received: from DM6PR10MB3148.namprd10.prod.outlook.com (2603:10b6:5:1a4::21)
 by DM5PR1001MB2265.namprd10.prod.outlook.com (2603:10b6:4:30::12) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3868.33; Wed, 24 Feb
 2021 13:29:26 +0000
Received: from DM6PR10MB3148.namprd10.prod.outlook.com
 ([fe80::f871:5965:2081:3934]) by DM6PR10MB3148.namprd10.prod.outlook.com
 ([fe80::f871:5965:2081:3934%5]) with mapi id 15.20.3868.033; Wed, 24 Feb 2021
 13:29:26 +0000
From: David Edmondson <david.edmondson@oracle.com>
To: linux-kernel@vger.kernel.org
Cc: Borislav Petkov <bp@alien8.de>, x86@kernel.org,
        Jim Mattson <jmattson@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Sean Christopherson <seanjc@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        "H. Peter Anvin" <hpa@zytor.com>, kvm@vger.kernel.org,
        Paolo Bonzini <pbonzini@redhat.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>,
        David Edmondson <david.edmondson@oracle.com>
Subject: [PATCH v3 0/5] KVM: x86: dump_vmcs: don't assume GUEST_IA32_EFER,
 show MSR autoloads/autosaves
Date: Wed, 24 Feb 2021 13:29:14 +0000
Message-Id: <20210224132919.2467444-1-david.edmondson@oracle.com>
X-Mailer: git-send-email 2.30.0
X-Originating-IP: [2001:8b0:bb71:7140:64::1]
X-ClientProxiedBy: LO2P265CA0155.GBRP265.PROD.OUTLOOK.COM
 (2603:10a6:600:9::23) To DM6PR10MB3148.namprd10.prod.outlook.com
 (2603:10b6:5:1a4::21)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from disaster-area.hh.sledj.net (2001:8b0:bb71:7140:64::1) by
 LO2P265CA0155.GBRP265.PROD.OUTLOOK.COM (2603:10a6:600:9::23) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3890.19 via Frontend
 Transport; Wed, 24 Feb 2021 13:29:23 +0000
Received: from localhost (disaster-area.hh.sledj.net [local])   by
 disaster-area.hh.sledj.net (OpenSMTPD) with ESMTPA id 0a7b5d02;
      Wed, 24 Feb 2021 13:29:19 +0000 (UTC)
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 7ed5ce97-13aa-4200-34cd-08d8d8c83436
X-MS-TrafficTypeDiagnostic: DM5PR1001MB2265:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM5PR1001MB2265536FE139D1353C8ECAD8889F9@DM5PR1001MB2265.namprd10.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:7691;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 +xl2N8wZ7A9gXo8KqeQEGluagqHVxcsZ0t7Yls660GPckvDriQ8cVBc6S5SDzbouPcwCznJG+gkTmW5XdnKqa1cvosAQkDepuVKYN3a7NxsNmaiHfF9zKGGxX1Ka3q59wz6V8MjX9wBs2I4FUvqyAQvwmoviklt/fpRy/GywYDArGPvgDVRfkCTAoZtSNByyZw3wvBaV36kEoH94XU9fLXfZlOf3ru+OhCyn6AdCCVdGUAmqnMYJEhOAJJXmSvAILAHcs2nbSWFk6KSSMEtUa/CcCOjMC9/mYhR7ndSAe6jj7g8GSu6lSLDrpt9rNAOdwEW526weKjAg40Als2SU7XQ79rJh5g9Gs7nBmdvaXAKn8vFF4f8atzme9/QPaYfM/C3cCswSRiDwe13GB/kWbL53EuDU0KvTraVqiuCiyMLxAiv0GfN5F/g/N9YQPm0CaoxagTcYBjReAZlFlx3++Se5SGjKHfDxvGPFd8MQn6zW4l0G856vi+1ZH5mkBvllKsUedN0uiiMBjL7FM+Imhg==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM6PR10MB3148.namprd10.prod.outlook.com;PTR:;CAT:NONE;SFS:(136003)(346002)(366004)(376002)(39860400002)(396003)(4744005)(86362001)(4326008)(54906003)(66946007)(44832011)(6916009)(2616005)(36756003)(8936002)(7416002)(2906002)(66556008)(52116002)(5660300002)(66476007)(186003)(1076003)(6666004)(8676002)(478600001)(316002)(83380400001)(107886003);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 0pmjoQPFFcYRcp9W7sxTsKpZgW4j0WZqeQeQNqdH8HGeP/GtoDO6L3E1Kwk/wMFo5GcHhP1o0ug8t9nGTtu0vKY2dVei1yuBpW/XFXz+Q3Lt0sHCY2szPWEyuNdncQvIIcSStmzXtOuyKuFvfRyqmavbR21n3kWTTkmRV/4iNIFmsWvivs3v9aoVKWNDC/AkizI9Q5lGDJowhrS9fCOe28BjFVq8XwtuuxoLa5z1H+eMF1ykiKm9D6W1AzGfeqXyk/R6SMdfupzAAnuoJLKBG51qiwfwjZnIXrBbAFLo6VkGN91gGbAvUP551U/RgahTzQzSEqUv0rfM88hRXPucOSqJtOmzlL2JG/IPcoAJ4JRcY55QMc4pkqs3NcFJ6/q0Gv2Tss32YWFR8u7BgudbCqEnN8nJ+RjcGyi3pvgSypY8oH2YSs2bpvRXA36w9R8QLSxn5MqzjyWlWR1wVJNhaayyLrbhO7UGY26rKe/TlxPm9ep5OSnDYZi/lzOFr8IoNKaF62/gAt7QDvUho1k4MMWF9oumbG3bVRtxo4c6k5Bq3S4dTPiXWsjp8knwRez7BnNOQYJJNS872ySzMBQY3QCzZDGcAZYRyQ/YMKImQAqWn/nbF+SClyyFmGIWa/OKmzLZf/WH+8uvZjBricpjATD33x9oz/2EkHb5KtXta6zf/hJLLA5Jwo34rmt66Q8EKMhlGTsDVruRdcefOVi36AfDVj7bz3DRKTQCyCsGQM9xYEo5vG1bH1bEGJLfzp/Dw+PmTReMVs2/n2qga5KcC37QspV46Bq+SJWl2WUJ7l81OZXXHoTzvkOfnmIb6GEDQTYLSYPbAPdlWwQZf5sZXoYhQuTbKiIXSk7AV7DCCKkhNqylXRJ7X9murfckxNzejoi7p1G9735gwsePoaU/uiEDBdB2W4uRyqx3vphsSNsQwHBFbSl/co5as9UkbgWKoJJC1vW/hlKN1c9hXhxilewkvqtuT8s8k3Q9r4h1ZNWAVpMq4s/YIJXMQ6vIOI3PsBu6y5fqDIcr3C5fn0E+/ZhngazMaFBMwsoEmosBYl9/Z/wOpmF+YLMm5pzaLCb+hKHaCTEyU6tAAFTZf98/qBeQ+oQhzxD3CB8sosLeuw0gH2CuM/OiMOzVBTNliq2ui/WIzC7xGizeiyIUG3M/2bFrTNtfW88eIhtuwl30UFZDYf20bl5PbnqDrSINHUwazHx/r+2qRzyNk6PEBUHc76i9VpiRTQgQ15KhddEI6a5XmQXMwWww0p+A/HZArwDQS0s2V193RKte01/VWj0ZG0aouAb5rcoKwf4rUemE8QlY+ard5iOF+/8866Xh8P/jPF9WNLzE6dIH7dXg8/HHrg==
X-OriginatorOrg: oracle.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 7ed5ce97-13aa-4200-34cd-08d8d8c83436
X-MS-Exchange-CrossTenant-AuthSource: DM6PR10MB3148.namprd10.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 24 Feb 2021 13:29:26.0058
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 4e2c6054-71cb-48f1-bd6c-3a9705aca71b
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 UUcDlsaF+Ums4X2LKNp5F3q50dRh0lBYVLbjJZnj9gfiwZdJGUxl6M0f3H0Y11CK60UxrbXfY3ab+nbEAKQUPWayHsUhZQkMpI/OY7hU3C8=
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM5PR1001MB2265
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9904
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 spamscore=0
 suspectscore=0
 malwarescore=0 mlxlogscore=728 adultscore=0 bulkscore=0 mlxscore=0
 phishscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2102240104
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9904
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=0
 bulkscore=0
 clxscore=1015 mlxlogscore=975 lowpriorityscore=0 phishscore=0
 impostorscore=0 adultscore=0 mlxscore=0 priorityscore=1501 malwarescore=0
 spamscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2102240105
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

v2:
- Don't use vcpu->arch.efer when GUEST_IA32_EFER is not available (Paolo).
- Dump the MSR autoload/autosave lists (Paolo).

v3:
- Rebase to master.
- Check only the load controls (Sean).
- Always show the PTPRs from the VMCS if they exist (Jim/Sean).
- Dig EFER out of the MSR autoload list if it's there (Paulo).
- Calculate and show the effective EFER if it is not coming from
  either the VMCS or the MSR autoload list (Sean).

David Edmondson (5):
  KVM: x86: dump_vmcs should not assume GUEST_IA32_EFER is valid
  KVM: x86: dump_vmcs should not conflate EFER and PAT presence in VMCS
  KVM: x86: dump_vmcs should consider only the load controls of EFER/PAT
  KVM: x86: dump_vmcs should show the effective EFER
  KVM: x86: dump_vmcs should include the autoload/autostore MSR lists

 arch/x86/kvm/vmx/vmx.c | 58 +++++++++++++++++++++++++++++-------------
 arch/x86/kvm/vmx/vmx.h |  2 +-
 2 files changed, 42 insertions(+), 18 deletions(-)
```
#### [PATCH v4 0/5] KVM: x86: dump_vmcs: don't assume GUEST_IA32_EFER,
##### From: David Edmondson <david.edmondson@oracle.com>

```c
From patchwork Wed Feb 24 14:04:51 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Edmondson <david.edmondson@oracle.com>
X-Patchwork-Id: 12101919
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,
	UNPARSEABLE_RELAY,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A4669C43331
	for <kvm@archiver.kernel.org>; Wed, 24 Feb 2021 14:17:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 83A3864EEC
	for <kvm@archiver.kernel.org>; Wed, 24 Feb 2021 14:17:51 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S235872AbhBXOO2 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 24 Feb 2021 09:14:28 -0500
Received: from aserp2130.oracle.com ([141.146.126.79]:59048 "EHLO
        aserp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S232372AbhBXOHm (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 24 Feb 2021 09:07:42 -0500
Received: from pps.filterd (aserp2130.oracle.com [127.0.0.1])
        by aserp2130.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 11OE4sWt017955;
        Wed, 24 Feb 2021 14:05:06 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : content-transfer-encoding : content-type :
 mime-version; s=corp-2020-01-29;
 bh=H+wP1GcZxZfeErzlXnCcR7gdg6vlVEoZwfoi3So9ghs=;
 b=jFIHLaNNdwUWEBA9z5qEHOXpbYvMNsNso/9b8hQze5S9/r9HLyjjuy+iFy9QKAzAXrTC
 Zn1l5IQ9izrvV2tuOufqERIIuzc7AMYnF5rXsMUXv2cbpqtKeGKbD9IdHUOUC0n85mbl
 xEIKwURhsvgirsuK0Lnoo+aRoemz41YLzgJaZPg/rFNw6hXoDxv7/3QQj8ATLWriMai1
 ZxFlKExVr6/SxuV/Oj238X/cOZAlIFVVHzMHWCchaq4bY62jyEx/6BTxRmCFp7ZbbMZF
 RKWS+p694jF5umSuWbjx+N5XHZpsrz3CGeGIbPy/mSdpmeHwe79tXNp9V/7eZMMnYbqM 4Q==
Received: from userp3020.oracle.com (userp3020.oracle.com [156.151.31.79])
        by aserp2130.oracle.com with ESMTP id 36vr625bwq-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 24 Feb 2021 14:05:05 +0000
Received: from pps.filterd (userp3020.oracle.com [127.0.0.1])
        by userp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 11ODuBpj117099;
        Wed, 24 Feb 2021 14:05:05 GMT
Received: from nam11-co1-obe.outbound.protection.outlook.com
 (mail-co1nam11lp2177.outbound.protection.outlook.com [104.47.56.177])
        by userp3020.oracle.com with ESMTP id 36uc6t5ytk-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 24 Feb 2021 14:05:04 +0000
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=Ih3q5yqHQlDncS3ci3oVhN9dngQpd3nO/KGenKlFcyCEqgsXggBVnByWoajJsd0Yu1/cal14+HuIjjB6zf9qvUAzEzzDb2cvt8XTS+XcOeoAnHpQ0k0R9GWd1cyHSuOZyV12y/0nhsF+XDTlbzjrNfaz2lPHr8idBCUS+v3Vx2k8ri5T5kED4wRvplZGRTyLBLgTkpohexIQNXBb5f0c2nNgIXaDQWgRN371kvqNuOBABpritx0P3Dl5IFF30INrgpy8ZER4+w5us7X6kCCG6zUxC/oW7jesmtv2NObuHNjphlfaC/dhmLe6fqqzgGVXZAboeHFNDOSUJ+fjidzyHQ==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=H+wP1GcZxZfeErzlXnCcR7gdg6vlVEoZwfoi3So9ghs=;
 b=ALnpM0dESpaAfbZ9d2P8tvDu63QgEihuc++EtuRZerBW+2hn/tPdEqH/aVB2U+xCs9cZgIbKyY3DzDZ3CkH4MzcszKA9o/yGwmWBdX6XNLSIJIgMvJb8jEOkzUin/XV8yf/ipmD6+iUhX++WsHYAWA/DrT2rKeNltYuM/YQluCu4mFs8p3MHF+JKeqN35mh1bqY74sD82CZEWqXkPodZ7cJ0OY8ecuuGD3CykebbhQXqiVCB4MpJTVTRd8XTByRP5MjWJuTN+USOV8TiqE6JCSLbDJkO14JyO6GfTnIgkf4hUZKS9jBJ+ctoi2CkqwY34uzasqJhhotGbGdD0aSTlg==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=oracle.com; dmarc=pass action=none header.from=oracle.com;
 dkim=pass header.d=oracle.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=oracle.onmicrosoft.com; s=selector2-oracle-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=H+wP1GcZxZfeErzlXnCcR7gdg6vlVEoZwfoi3So9ghs=;
 b=RuvhYBHyrCfsSnmAZa2mGayfNZwJIpeABXXKvLBt7tSIE30GZJIwG5guWwAHUgncaSp77zVDR6L9DP7j/Oe6MpNsZdbOW9X1B2H9IznNzBvL8RdcaZXJIzz9ywmyJVBV1t9TXTj8vp5Z3TyqR0AZcov2I5pae8X0KwdWjf/33H0=
Authentication-Results: redhat.com; dkim=none (message not signed)
 header.d=none;redhat.com; dmarc=none action=none header.from=oracle.com;
Received: from DM6PR10MB3148.namprd10.prod.outlook.com (2603:10b6:5:1a4::21)
 by DM5PR1001MB2153.namprd10.prod.outlook.com (2603:10b6:4:2c::27) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3868.33; Wed, 24 Feb
 2021 14:05:02 +0000
Received: from DM6PR10MB3148.namprd10.prod.outlook.com
 ([fe80::f871:5965:2081:3934]) by DM6PR10MB3148.namprd10.prod.outlook.com
 ([fe80::f871:5965:2081:3934%5]) with mapi id 15.20.3868.033; Wed, 24 Feb 2021
 14:05:02 +0000
From: David Edmondson <david.edmondson@oracle.com>
To: linux-kernel@vger.kernel.org
Cc: Jim Mattson <jmattson@google.com>, Borislav Petkov <bp@alien8.de>,
        Joerg Roedel <joro@8bytes.org>,
        Vitaly Kuznetsov <vkuznets@redhat.com>, kvm@vger.kernel.org,
        Wanpeng Li <wanpengli@tencent.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Sean Christopherson <seanjc@google.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        "H. Peter Anvin" <hpa@zytor.com>, Ingo Molnar <mingo@redhat.com>,
        x86@kernel.org, David Edmondson <david.edmondson@oracle.com>
Subject: [PATCH v4 0/5] KVM: x86: dump_vmcs: don't assume GUEST_IA32_EFER,
 show MSR autoloads/autosaves
Date: Wed, 24 Feb 2021 14:04:51 +0000
Message-Id: <20210224140456.2558033-1-david.edmondson@oracle.com>
X-Mailer: git-send-email 2.30.0
X-Originating-IP: [2001:8b0:bb71:7140:64::1]
X-ClientProxiedBy: LO4P123CA0411.GBRP123.PROD.OUTLOOK.COM
 (2603:10a6:600:189::20) To DM6PR10MB3148.namprd10.prod.outlook.com
 (2603:10b6:5:1a4::21)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from disaster-area.hh.sledj.net (2001:8b0:bb71:7140:64::1) by
 LO4P123CA0411.GBRP123.PROD.OUTLOOK.COM (2603:10a6:600:189::20) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3868.30 via Frontend
 Transport; Wed, 24 Feb 2021 14:05:00 +0000
Received: from localhost (disaster-area.hh.sledj.net [local])   by
 disaster-area.hh.sledj.net (OpenSMTPD) with ESMTPA id e3609277;
      Wed, 24 Feb 2021 14:04:56 +0000 (UTC)
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: d34080c8-e91f-40f2-6596-08d8d8cd2e09
X-MS-TrafficTypeDiagnostic: DM5PR1001MB2153:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM5PR1001MB21534C830BF0CBFA58729158889F9@DM5PR1001MB2153.namprd10.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:7691;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 CCkuAwlORRP/1wpSCw3aN2wlr3MpCzjwpJKPVQaHfPShJEBIn4GLhyDlGYnBDsGx4wZVlnEnSfjALge/J9qLjOH1HIzfvO6pVKUPfHSGoEz84x4wtst6F+wwdj3Ua1aCrq/pQVNFOcim8t5tQ2QV4rQzA2YQbOaoGf0XdKG4/u6+FnyVWCVbGkaKdVvl6pd1LvWuAHS2exbjn8/K4ypkSK4rsJP1216e78bREYB5Z4ZLdomjp97aa2oi4rj6dGssgiL2lvJvjiY0IOXSSAb86rw3FBMImkrZ98FlUDdZu7awzpQSPQ3cjC+Qjr5bbDdK/64QZZDyVIlZwteIShKyg+Be9Lkk2tHlLxhT/Q2dX2415CRClJIg7g6JvxKvFLf3/rvv0haNG2N7wFFn2XevFyjJj79BJHP1xFVavhgC2GCJfrKddxbzcNze2zVZfE3pYCLQMdiDxPRu9YplHvKZctFOC/CsnUgJmiQ4DXBEoU9ylYQ0E2KfNZH3Wpqlq3iA8v2SsyQ/I/RQTChDJJSPaA==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM6PR10MB3148.namprd10.prod.outlook.com;PTR:;CAT:NONE;SFS:(136003)(39860400002)(346002)(396003)(366004)(376002)(83380400001)(316002)(66476007)(44832011)(8936002)(186003)(2906002)(86362001)(7416002)(8676002)(66556008)(52116002)(36756003)(5660300002)(6916009)(54906003)(1076003)(2616005)(4326008)(6666004)(478600001)(66946007)(107886003);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 98zKLZQW7khdLvopnbGhHlVQZhVm80AacmzaG8gxNVmdlgkeid2boINELnBaoKrk2Em4gkZhm++CkH4c3zpUUIHKmolwqNQHsMmRAZvxQtEk0VPs+F80ZA+6EEKVZpxAsurjMWzWwUUtdlBaKcrr1SE3ycNX6pn/RBvXvkWm3fTJlTrhsZMT+km+sI2LVyf54SGGKCJihk2NaM40ZAigs505w66MoXVZpN4LVTZlo6NN4LPhNqHckLowin8h5C0rlmtXPKiRGj9Pdwk9w2jbGz0X+36humSkJViYdkiNBcklR+t12bp1FSW4m9lr1nuWVJwlEXDt++J2hDFuSJFBgQP9Z+aMG7LMtXdRya25mGEfISsIfavwEryk8hxX9o/av9tOeG+Ttb8XKUGgnhoxbdFQnTqU/qG6tTXOcfWxNWE7WgO46G/5aW8xa5fweO/g1Bhsf8t2X0kgRfT4QEuWKPBdaXISGzxpIkLF9/MIQuVQijxqd2hUeNRLpO58UPgezLv3jgUXC6gQvfogtTDeAXLrIfJ/P0fSoWWAoX64hSGe8Lpm5svPhve3y8H5UXDaR3gR+LnLwwozcwtcw0TkyEOM2WJqRZnoY0qNCMnPN0GFM0UZDNv4Ysv7lVJUH9xOXPl3rufCYKDC3PGMOXgXzZEYi2nVC1yzTClGTabQ8ZZBliOb1ek7uVRUeAlBZ7cSeK+EAvsB3UuV0ZASyJj8fSCCp4hI+GAiCNjaf1jjNMtQ6QaDK60oC5EbkVopRLHtzPMeGQX1hGOXI+O91XdRtO68kkErRGrAFtinuNpF2mAf7zAi+flc+a9grJSrcwT916KNlCiEC8dqrpEkBr0UtpkRT3XU0Jk5r6CXGlUWSZvFE3XJg4caG1NzJD8gsf+uEdMP76oE6hh1HPsGGwjdtrfWrz1ivcd62l2TEIfrDczsO6Wp2FNin3twZDCljtbq5PkSV7WXXHvNGGniTvrLH4n3aARnwiz/dwXwkWbMwYHqugeaLWh8BolFTt0S4/nmcvOqlMaFj5ZiS+ZBM7SUq20Km2atO4n3P/ySEXLgJTytcBmyfO+VRQfUJ6A3c5rT78Z/qvbDFyq0B9MfWSNCj0ArJ8k/UaMmXYGi0iZrG1yR4JqVa3Fxv1FwwvIvta5cCGS4ZmyPUsTtRRYuSCHq2pqkjKy/26WAujQIMzshpORRYED6aOipqHOzpSiHgnGbNZqqzyBZxwgagljsvZ0uWMshwOGZKUUN3jkFaGrmA9cYlC1ztoi7P4PowhqWZUT+4LxfvTTwMb+t5TOvc/VWxor24ThHJZH5Xu9+ZyxlYepFFVrjBfVzQjk8jVn8EiStqcNrhzbdH8XknP8glE2qeQ==
X-OriginatorOrg: oracle.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 d34080c8-e91f-40f2-6596-08d8d8cd2e09
X-MS-Exchange-CrossTenant-AuthSource: DM6PR10MB3148.namprd10.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 24 Feb 2021 14:05:02.7187
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 4e2c6054-71cb-48f1-bd6c-3a9705aca71b
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 w9G0H19pBGh9gYrZTwztgUYKXQhNvmLuM35fQ0o9ck3BO/N7iOVxqsa+Crol5dDq84Yg0+3cX1cmgsFftDgxCLpbw5ASWMWlu3SaYe7UA0M=
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM5PR1001MB2153
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9904
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=0
 mlxscore=0 spamscore=0
 mlxlogscore=730 adultscore=0 bulkscore=0 malwarescore=0 phishscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2102240108
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9904
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=0
 bulkscore=0
 clxscore=1015 mlxlogscore=965 lowpriorityscore=0 phishscore=0
 impostorscore=0 adultscore=0 mlxscore=0 priorityscore=1501 malwarescore=0
 spamscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2102240109
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

v2:
- Don't use vcpu->arch.efer when GUEST_IA32_EFER is not available (Paolo).
- Dump the MSR autoload/autosave lists (Paolo).

v3:
- Rebase to master.
- Check only the load controls (Sean).
- Always show the PTPRs from the VMCS if they exist (Jim/Sean).
- Dig EFER out of the MSR autoload list if it's there (Paulo).
- Calculate and show the effective EFER if it is not coming from
  either the VMCS or the MSR autoload list (Sean).

v4:
- Ensure that each changeset builds with just the previous set.

David Edmondson (5):
  KVM: x86: dump_vmcs should not assume GUEST_IA32_EFER is valid
  KVM: x86: dump_vmcs should not conflate EFER and PAT presence in VMCS
  KVM: x86: dump_vmcs should consider only the load controls of EFER/PAT
  KVM: x86: dump_vmcs should show the effective EFER
  KVM: x86: dump_vmcs should include the autoload/autostore MSR lists

 arch/x86/kvm/vmx/vmx.c | 58 +++++++++++++++++++++++++++++-------------
 arch/x86/kvm/vmx/vmx.h |  2 +-
 2 files changed, 42 insertions(+), 18 deletions(-)
```
#### [PATCH kvm-unit-tests v2 0/4] x86: hyperv_stimer: test direct mode
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
From patchwork Wed Feb 24 16:35:43 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 12102133
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-10.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 2A702C433E0
	for <kvm@archiver.kernel.org>; Wed, 24 Feb 2021 16:38:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E00AE64EF1
	for <kvm@archiver.kernel.org>; Wed, 24 Feb 2021 16:38:57 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S235289AbhBXQih (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 24 Feb 2021 11:38:37 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:37437 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S232616AbhBXQhT (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 24 Feb 2021 11:37:19 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1614184552;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=vqM3jBqcK0WlcpFWakq278CLcazYhvJjJtccE6zbFGE=;
        b=eTa1tw7s27oyYecTUr//18yLGuyKUhwy51qjWb3mfyRaG550GTpVLlBq4xI5HZ8IbUYUfN
        KxBGnvrGxJq5YFDGxL05yhwmtTir9UWxawz6IB20JSFkbTRIGZBeXP5522KcRLj6gN9ukH
        R2rPb9KDWQ3FRrtMdVtyq9JZXYmBzy4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-437-fh_DROU6OziVRTRzKkZcwA-1; Wed, 24 Feb 2021 11:35:50 -0500
X-MC-Unique: fh_DROU6OziVRTRzKkZcwA-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id BF4451008312
        for <kvm@vger.kernel.org>; Wed, 24 Feb 2021 16:35:49 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.195.221])
        by smtp.corp.redhat.com (Postfix) with ESMTP id A10A819C46;
        Wed, 24 Feb 2021 16:35:48 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Subject: [PATCH kvm-unit-tests v2 0/4] x86: hyperv_stimer: test direct mode
Date: Wed, 24 Feb 2021 17:35:43 +0100
Message-Id: <20210224163547.197100-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Changes since v1:
- Minor cosmetic changes. v1 was sent in October, 2019 and I completely
 forgot about it. Time to dust it off!

Original description:

Testing 'direct' mode requires us to add 'hv_stimer_direct' CPU flag to
QEMU, create a new entry in unittests.cfg to not lose the ability to test
stimers in 'VMbus message' mode.

Vitaly Kuznetsov (4):
  x86: hyperv_stimer: keep SINT number parameter in 'struct stimer'
  x86: hyperv_stimer: define union hv_stimer_config
  x86: hyperv_stimer: don't require hyperv-testdev
  x86: hyperv_stimer: add direct mode tests

 x86/hyperv.h        |  29 ++++++--
 x86/hyperv_stimer.c | 159 +++++++++++++++++++++++++++++++++++---------
 x86/unittests.cfg   |   8 ++-
 3 files changed, 157 insertions(+), 39 deletions(-)
```
