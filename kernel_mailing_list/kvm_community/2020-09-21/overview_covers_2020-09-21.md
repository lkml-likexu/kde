

#### [PATCH 0/3 v3] kvm-unit-test: nVMX: Test Selector and Base Address
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
From patchwork Mon Sep 21 08:10:24 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11788891
Return-Path: <SRS0=AHPx=C6=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1CA22618
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 21 Sep 2020 08:10:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id EABB120BED
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 21 Sep 2020 08:10:44 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="XCXY2Vfx"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726641AbgIUIKo (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 21 Sep 2020 04:10:44 -0400
Received: from aserp2120.oracle.com ([141.146.126.78]:45058 "EHLO
        aserp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726551AbgIUIKn (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 21 Sep 2020 04:10:43 -0400
Received: from pps.filterd (aserp2120.oracle.com [127.0.0.1])
        by aserp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 08L8961A163592;
        Mon, 21 Sep 2020 08:10:38 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id; s=corp-2020-01-29;
 bh=5vYeTsR3FXtTok9hIWQTwXvWr0ueKem5fAmGgOOBPyU=;
 b=XCXY2VfxFPGc1R5MIuVwJmuOlLi7LOcWkhOCTupN517ETL53vJxbkyrgYx3FPOB0CbVJ
 ITUNo97DJ3yrsI2cQz1wJxlPREM8vVaPMD1UtuQLqFyQSrKsoOOg5JcIYKsKB5dupD1t
 NE+m4P8jS08Dt1txjL2kVJeK7pjfqrw+lXhhu1Q1js1zV/kyfudbso7a7i0msrpsb5E7
 r0KcxpoYhMEuGuOO+UTlAHBKigagmO6cxuvFBBM3P3RCdngTlG8ba1IrvHGLZvX6pZ9R
 KmnjTTtnoI5o7KIl8007FjD1DEFNB+oxWNAxxM1z1X1tcefD5/83UndGc3qha5xUKXPQ tQ==
Received: from aserp3020.oracle.com (aserp3020.oracle.com [141.146.126.70])
        by aserp2120.oracle.com with ESMTP id 33n9xkm31u-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=FAIL);
        Mon, 21 Sep 2020 08:10:38 +0000
Received: from pps.filterd (aserp3020.oracle.com [127.0.0.1])
        by aserp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 08L85mm6188353;
        Mon, 21 Sep 2020 08:10:38 GMT
Received: from userv0122.oracle.com (userv0122.oracle.com [156.151.31.75])
        by aserp3020.oracle.com with ESMTP id 33nuw04r7v-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 21 Sep 2020 08:10:38 +0000
Received: from abhmp0016.oracle.com (abhmp0016.oracle.com [141.146.116.22])
        by userv0122.oracle.com (8.14.4/8.14.4) with ESMTP id 08L8AaxK022449;
        Mon, 21 Sep 2020 08:10:37 GMT
Received: from sadhukhan-nvmx.osdevelopmeniad.oraclevcn.com (/100.100.230.226)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Mon, 21 Sep 2020 01:10:36 -0700
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com,
        sean.j.christopherson@intel.com
Subject: [PATCH 0/3 v3] kvm-unit-test: nVMX: Test Selector and Base Address
 fields of Guest Segment registers
Date: Mon, 21 Sep 2020 08:10:24 +0000
Message-Id: <20200921081027.23047-1-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.18.4
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9750
 signatures=668679
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 spamscore=0
 phishscore=0 malwarescore=0
 mlxscore=0 suspectscore=13 adultscore=0 mlxlogscore=767 bulkscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2006250000
 definitions=main-2009210059
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9750
 signatures=668679
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 lowpriorityscore=0 malwarescore=0
 suspectscore=13 priorityscore=1501 adultscore=0 spamscore=0 clxscore=1015
 mlxlogscore=791 bulkscore=0 mlxscore=0 phishscore=0 impostorscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2006250000
 definitions=main-2009210059
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

It's been a while since I sent out v2. This patch-series tests the Selector
and Base Address fields of the Guest Segement register according to section
"Checks on Guest Segment Registers" in SDM vol 3C. "Unrestricted guest"
VM-execution control is a condition in testing some parts of the Guest
Segement registers.

v2 -> v3
	1. Patch# 1 has been enhanced to check the "unrestricted VM-execution
	   control" of the nested VMCS, along with the
	   "enabled_unrestricted_guest" global variable, in some of the code
	   paths where the VM-execution control from both vmcs01 and vmcs02
	   needs to be considered.
	2. Patch# 3 is new. It adds a test for VMENTRY of an unrestricted guest
	   in unpaged protected mode.


[PATCH 1/3 v3] KVM: nVMX: KVM needs to unset "unrestricted guest"
[PATCH 2/3 v3] nVMX: Test Selector and Base Address fields of Guest Segment
[PATCH 3/3 v3] nVMX: Test vmentry of unrestricted (unpaged protected) nested

 arch/x86/kvm/vmx/nested.c |  3 +++
 arch/x86/kvm/vmx/vmx.c    | 17 +++++++++--------
 arch/x86/kvm/vmx/vmx.h    |  7 +++++++
 3 files changed, 19 insertions(+), 8 deletions(-)

Krish Sadhukhan (1):
      KVM: nVMX: KVM needs to unset "unrestricted guest" VM-execution control in vmcs02 if vmcs12 doesn't set it

 lib/x86/processor.h |   1 +
 x86/vmx_tests.c     | 200 ++++++++++++++++++++++++++++++++++++++++++++++++++++
 2 files changed, 201 insertions(+)

Krish Sadhukhan (1):
      nVMX: Test Selector and Base Address fields of Guest Segment Registers on vmentry of nested guests

 x86/vmx.c       |  2 +-
 x86/vmx.h       |  1 +
 x86/vmx_tests.c | 48 ++++++++++++++++++++++++++++++++++++++++++++++++
 3 files changed, 50 insertions(+), 1 deletion(-)

Krish Sadhukhan (1):
      nVMX: Test vmentry of unrestricted (unpaged protected) nested guest
```
#### [PATCH v2 0/1] KVM: correctly restore the TSC value on nested
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
From patchwork Mon Sep 21 10:38:04 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 11789243
Return-Path: <SRS0=AHPx=C6=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A57EA139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 21 Sep 2020 10:38:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 892F0216C4
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 21 Sep 2020 10:38:19 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="AueoSnjJ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726513AbgIUKiS (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 21 Sep 2020 06:38:18 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:24161 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726436AbgIUKiS (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 21 Sep 2020 06:38:18 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1600684697;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=k37fRmP6IslqoM8RNLxcb8OzcjtWZpkq3yLymvakBU4=;
        b=AueoSnjJkfxW7RSb0Z5Hyb1MxvQTgtSHZt5IAWWE7T4OJHOeWVa5CjQTaRFTOhg6DNYqXz
        gI/N6uzv0ZRG7C/brcvbJBNvm5ZnfHWIPWE0NR48mqCvhMROgiRvNMTXmmg8koV/lSR5I1
        rA5JCKVdjyJ+/TE7YOGistZ19H8pJkE=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-395-YFqMEzMEPRqvidZyzhPt7g-1; Mon, 21 Sep 2020 06:38:15 -0400
X-MC-Unique: YFqMEzMEPRqvidZyzhPt7g-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 40029801AC3;
        Mon, 21 Sep 2020 10:38:13 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.206.238])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 7513E68D64;
        Mon, 21 Sep 2020 10:38:06 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, Jim Mattson <jmattson@google.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Ingo Molnar <mingo@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Borislav Petkov <bp@alien8.de>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        x86@kernel.org (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT)),
        Joerg Roedel <joro@8bytes.org>,
        "H. Peter Anvin" <hpa@zytor.com>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH v2 0/1] KVM: correctly restore the TSC value on nested
 migration
Date: Mon, 21 Sep 2020 13:38:04 +0300
Message-Id: <20200921103805.9102-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch is a result of a long investigation I made to understand
why the nested migration more often than not makes the nested guest hang.
Sometimes the nested guest recovers and sometimes it hangs forever.

The root cause of this is that reading MSR_IA32_TSC while nested guest is
running returns its TSC value, that is (assuming no tsc scaling)
host tsc + L1 tsc offset + L2 tsc offset.

This is correct but it is a result of a nice curiosity of X86 VMX
(and apparently SVM too, according to my tests) implementation:

As a rule MSR reads done by the guest should either trap to host, or just
return host value, and therefore kvm_get_msr and friends, should basically
always return the L1 value of any msr.

Well, MSR_IA32_TSC is an exception. Intel's PRM states that when you disable
its interception, then in guest mode the host adds the TSC offset to
the read value.

I haven't found anything like that in AMD's PRM but according to the few
tests I made, it behaves the same.

However, there is no such exception when writing MSR_IA32_TSC, and this
poses a problem for nested migration.

When MSR_IA32_TSC is read, we read L2 value (smaller since L2 is started
after L1), and when we restore it after migration, the value is interpreted
as L1 value, thus resulting in huge TSC jump backward which the guest usually
really doesn't like, especially on AMD with APIC deadline timer, which
usually just doesn't fire afterward sending the guest into endless wait for it.

The proposed patch fixes this by making read of MSR_IA32_TSC depend on
'msr_info->host_initiated'

If guest reads the MSR, we add the TSC offset, but when host's qemu reads
the msr we skip that silly emulation of TSC offset, and return the real value
for the L1 guest which is host tsc + L1 offset.

This patch was tested on both SVM and VMX, and on both it fixes hangs.
On VMX since it uses VMX preemption timer for APIC deadline, the guest seems
to recover after a while without that patch.

To make sure that the nested migration happens I usually used
-overcommit cpu_pm=on but I reproduced this with just running an endless loop
in L2.

This is tested both with and without -invtsc,tsc-frequency=...

The migration was done by saving the migration stream to a file, and then
loading the qemu with '-incoming'

V2: incorporated feedback from Sean Christopherson (thanks!)

Maxim Levitsky (1):
  KVM: x86: fix MSR_IA32_TSC read for nested migration

 arch/x86/kvm/x86.c | 16 ++++++++++++++--
 1 file changed, 14 insertions(+), 2 deletions(-)
```
#### [PATCH v10 00/18] Add support for Nitro Enclaves
##### From: Andra Paraschiv <andraprs@amazon.com>

```c
From patchwork Mon Sep 21 12:17:14 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andra Paraschiv <andraprs@amazon.com>
X-Patchwork-Id: 11789631
Return-Path: <SRS0=AHPx=C6=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CFA666CB
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 21 Sep 2020 12:18:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A180D20EDD
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 21 Sep 2020 12:18:12 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amazon.com header.i=@amazon.com
 header.b="mZRdvGqf"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726854AbgIUMSJ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 21 Sep 2020 08:18:09 -0400
Received: from smtp-fw-9101.amazon.com ([207.171.184.25]:62967 "EHLO
        smtp-fw-9101.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726821AbgIUMSJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 21 Sep 2020 08:18:09 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.com; i=@amazon.com; q=dns/txt; s=amazon201209;
  t=1600690687; x=1632226687;
  h=from:to:cc:subject:date:message-id:mime-version:
   content-transfer-encoding;
  bh=px05utS3lQfM7kY6IubO/5Myaky8rjCI+WDX9rB1rjE=;
  b=mZRdvGqfjOZYENIC8drKTV83om+qQsu+hNCqvH8xc4E3sGpfok4ZL/QJ
   8re5gxlUbZCBqHHzgDn9Hd9RguocXVYsarCvHtYWFqpbHVy5jVbRxuOjt
   nwuPdjmc5ydtvt4xfWuT8zT+FWWW5iA86N58j65AB++yk+dD+cbEASnmE
   U=;
X-IronPort-AV: E=Sophos;i="5.77,286,1596499200";
   d="scan'208";a="69767479"
Received: from sea32-co-svc-lb4-vlan3.sea.corp.amazon.com (HELO
 email-inbound-relay-1a-af6a10df.us-east-1.amazon.com) ([10.47.23.38])
  by smtp-border-fw-out-9101.sea19.amazon.com with ESMTP;
 21 Sep 2020 12:18:00 +0000
Received: from EX13D16EUB001.ant.amazon.com
 (iad12-ws-svc-p26-lb9-vlan2.iad.amazon.com [10.40.163.34])
        by email-inbound-relay-1a-af6a10df.us-east-1.amazon.com (Postfix) with
 ESMTPS id 2045DA20E0;
        Mon, 21 Sep 2020 12:17:57 +0000 (UTC)
Received: from 38f9d34ed3b1.ant.amazon.com (10.43.160.229) by
 EX13D16EUB001.ant.amazon.com (10.43.166.28) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Mon, 21 Sep 2020 12:17:47 +0000
From: Andra Paraschiv <andraprs@amazon.com>
To: linux-kernel <linux-kernel@vger.kernel.org>
CC: Anthony Liguori <aliguori@amazon.com>,
        Benjamin Herrenschmidt <benh@kernel.crashing.org>,
        Colm MacCarthaigh <colmmacc@amazon.com>,
        "David Duncan" <davdunc@amazon.com>,
        Bjoern Doebel <doebel@amazon.de>,
        "David Woodhouse" <dwmw@amazon.co.uk>,
        Frank van der Linden <fllinden@amazon.com>,
        Alexander Graf <graf@amazon.de>,
        Greg KH <gregkh@linuxfoundation.org>,
        "Karen Noel" <knoel@redhat.com>,
        Martin Pohlack <mpohlack@amazon.de>,
        Matt Wilson <msw@amazon.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Stefano Garzarella <sgarzare@redhat.com>,
        Stefan Hajnoczi <stefanha@redhat.com>,
        Stewart Smith <trawets@amazon.com>,
        Uwe Dannowski <uwed@amazon.de>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        kvm <kvm@vger.kernel.org>,
        ne-devel-upstream <ne-devel-upstream@amazon.com>,
        Andra Paraschiv <andraprs@amazon.com>
Subject: [PATCH v10 00/18] Add support for Nitro Enclaves
Date: Mon, 21 Sep 2020 15:17:14 +0300
Message-ID: <20200921121732.44291-1-andraprs@amazon.com>
X-Mailer: git-send-email 2.20.1 (Apple Git-117)
MIME-Version: 1.0
X-Originating-IP: [10.43.160.229]
X-ClientProxiedBy: EX13D36UWB001.ant.amazon.com (10.43.161.84) To
 EX13D16EUB001.ant.amazon.com (10.43.166.28)
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Nitro Enclaves (NE) is a new Amazon Elastic Compute Cloud (EC2) capability
that allows customers to carve out isolated compute environments within EC2
instances [1].

For example, an application that processes sensitive data and runs in a VM,
can be separated from other applications running in the same VM. This
application then runs in a separate VM than the primary VM, namely an enclave.

An enclave runs alongside the VM that spawned it. This setup matches low latency
applications needs. The resources that are allocated for the enclave, such as
memory and CPUs, are carved out of the primary VM. Each enclave is mapped to a
process running in the primary VM, that communicates with the NE driver via an
ioctl interface.

In this sense, there are two components:

1. An enclave abstraction process - a user space process running in the primary
VM guest that uses the provided ioctl interface of the NE driver to spawn an
enclave VM (that's 2 below).

There is a NE emulated PCI device exposed to the primary VM. The driver for this
new PCI device is included in the NE driver.

The ioctl logic is mapped to PCI device commands e.g. the NE_START_ENCLAVE ioctl
maps to an enclave start PCI command. The PCI device commands are then
translated into  actions taken on the hypervisor side; that's the Nitro
hypervisor running on the host where the primary VM is running. The Nitro
hypervisor is based on core KVM technology.

2. The enclave itself - a VM running on the same host as the primary VM that
spawned it. Memory and CPUs are carved out of the primary VM and are dedicated
for the enclave VM. An enclave does not have persistent storage attached.

The memory regions carved out of the primary VM and given to an enclave need to
be aligned 2 MiB / 1 GiB physically contiguous memory regions (or multiple of
this size e.g. 8 MiB). The memory can be allocated e.g. by using hugetlbfs from
user space [2][3]. The memory size for an enclave needs to be at least 64 MiB.
The enclave memory and CPUs need to be from the same NUMA node.

An enclave runs on dedicated cores. CPU 0 and its CPU siblings need to remain
available for the primary VM. A CPU pool has to be set for NE purposes by an
user with admin capability. See the cpu list section from the kernel
documentation [4] for how a CPU pool format looks.

An enclave communicates with the primary VM via a local communication channel,
using virtio-vsock [5]. The primary VM has virtio-pci vsock emulated device,
while the enclave VM has a virtio-mmio vsock emulated device. The vsock device
uses eventfd for signaling. The enclave VM sees the usual interfaces - local
APIC and IOAPIC - to get interrupts from virtio-vsock device. The virtio-mmio
device is placed in memory below the typical 4 GiB.

The application that runs in the enclave needs to be packaged in an enclave
image together with the OS ( e.g. kernel, ramdisk, init ) that will run in the
enclave VM. The enclave VM has its own kernel and follows the standard Linux
boot protocol [6].

The kernel bzImage, the kernel command line, the ramdisk(s) are part of the
Enclave Image Format (EIF); plus an EIF header including metadata such as magic
number, eif version, image size and CRC.

Hash values are computed for the entire enclave image (EIF), the kernel and
ramdisk(s). That's used, for example, to check that the enclave image that is
loaded in the enclave VM is the one that was intended to be run.

These crypto measurements are included in a signed attestation document
generated by the Nitro Hypervisor and further used to prove the identity of the
enclave; KMS is an example of service that NE is integrated with and that checks
the attestation doc.

The enclave image (EIF) is loaded in the enclave memory at offset 8 MiB. The
init process in the enclave connects to the vsock CID of the primary VM and a
predefined port - 9000 - to send a heartbeat value - 0xb7. This mechanism is
used to check in the primary VM that the enclave has booted. The CID of the
primary VM is 3.

If the enclave VM crashes or gracefully exits, an interrupt event is received by
the NE driver. This event is sent further to the user space enclave process
running in the primary VM via a poll notification mechanism. Then the user space
enclave process can exit.

Thank you.

Andra

[1] https://aws.amazon.com/ec2/nitro/nitro-enclaves/
[2] https://www.kernel.org/doc/html/latest/admin-guide/mm/hugetlbpage.html
[3] https://lwn.net/Articles/807108/
[4] https://www.kernel.org/doc/html/latest/admin-guide/kernel-parameters.html
[5] https://man7.org/linux/man-pages/man7/vsock.7.html
[6] https://www.kernel.org/doc/html/latest/x86/boot.html
---

Patch Series Changelog

The patch series is built on top of v5.9-rc6.

GitHub repo branch for the latest version of the patch series:

* https://github.com/andraprs/linux/tree/ne-driver-upstream-v10

* v9 -> v10

* Rebase on top of v5.9-rc6.
* Update commit messages to include the changelog before the SoB tag(s).
* v9: https://github.com/andraprs/linux/tree/ne-driver-upstream-v9
  (it seems there have been several issues with the mail delivery to
  the mailing list itself, that's why GitHub refs, instead of lore)

v8 -> v9

* Rebase on top of v5.9-rc4.
* Add data structure to keep references to both Nitro Enclaves misc and PCI
  devices. These refs are used in the NE PCI device driver probe / remove /
  shutdow flow, in the ioctl logic for the enclave VM creation and during the
  NE CPU pool setup.
* Update the location of the NE documentation to the "virt" directory and
  include it in the corresponding index file.
* Remove -Wall flags from the NE driver Makefile, could use W=1 as an option.
* v8: https://lore.kernel.org/lkml/20200904173718.64857-1-andraprs@amazon.com/ 

v7 -> v8

* Rebase on top of v5.9-rc3.
* Add NE customer error codes for invalid flags and enclave CID provided to the
  ioctl calls, and memory regions not backed by pages multiple of 2 MiB.
* Add NE PCI driver shutdown logic.
* Add check for invalid provided enclave CID to the start enclave ioctl.
* Update documentation to include info about the primary / parent VM CID for its
  vsock device. Update reference link for huge pages and include refs for the
  x86 boot protocol.
* Update sample to track the newly added NE custom error codes and match the
  latest logic for the heartbeat enclave boot check.
* v7: https://lore.kernel.org/lkml/20200817131003.56650-1-andraprs@amazon.com/

v6 -> v7

* Rebase on top of v5.9-rc1.
* Use the NE misc device parent field to get the NE PCI device.
* Update the naming and add more comments to make more clear the logic of
  handling full CPU cores and dedicating them to the enclave.
* Remove, for now, the dependency on ARM64 arch in Kconfig. x86 is currently
  supported, with Arm to come afterwards. The NE kernel driver can be currently
  built for aarch64 arch.
* Clarify in the ioctls documentation that the return value is -1 and errno is
  set on failure.
* Update the error code value for NE_ERR_INVALID_MEM_REGION_SIZE as it gets in
  user space as value 25 (ENOTTY) instead of 515. Update the NE custom error
  codes values range to not be the same as the ones defined in
  include/linux/errno.h, although these are not propagated to user space.
* Update the documentation to include references to the NE PCI device id and
  MMIO bar.
* Update check for duplicate user space memory regions to cover additional
  possible scenarios.
* Calculate the number of threads per core and not use smp_num_siblings that is
  x86 specific.
* v6: https://lore.kernel.org/lkml/20200805091017.86203-1-andraprs@amazon.com/

v5 -> v6

* Rebase on top of v5.8.
* Update documentation to kernel-doc format.
* Update sample to include the enclave image loading logic.
* Remove the ioctl to query API version.
* Check for invalid provided flags field via ioctl calls args.
* Check for duplicate provided user space memory regions.
* Check for aligned memory regions.
* Include, in the sample, usage info for NUMA-aware hugetlb config.
* v5: https://lore.kernel.org/lkml/20200715194540.45532-1-andraprs@amazon.com/

v4 -> v5

* Rebase on top of v5.8-rc5.
* Add more details about the ioctl calls usage e.g. error codes.
* Update the ioctl to set an enclave vCPU to not return a fd.
* Add specific NE error codes.
* Split the NE CPU pool in CPU cores cpumasks.
* Remove log on copy_from_user() / copy_to_user() failure.
* Release the reference to the NE PCI device on failure paths.
* Close enclave fd on copy_to_user() failure.
* Set empty string in case of invalid NE CPU pool sysfs value.
* Early exit on NE CPU pool setup if enclave(s) already running.
* Add more sanity checks for provided vCPUs e.g. maximum possible value.
* Split logic for checking if a vCPU is in pool / getting a vCPU from pool.
* Exit without unpinning the pages on NE PCI dev request failure.
* Add check for the memory region user space address alignment.
* Update the logic to set memory region to not have a hardcoded check for 2 MiB.
* Add arch dependency for Arm / x86.
* v4: https://lore.kernel.org/lkml/20200622200329.52996-1-andraprs@amazon.com/

v3 -> v4

* Rebase on top of v5.8-rc2.
* Add NE API version and the corresponding ioctl call.
* Add enclave / image load flags options.
* Decouple NE ioctl interface from KVM API.
* Remove the "packed" attribute and include padding in the NE data structures.
* Update documentation based on the changes from v4.
* Update sample to match the updates in v4.
* Remove the NE CPU pool init during NE kernel module loading.
* Setup the NE CPU pool at runtime via a sysfs file for the kernel parameter.
* Check if the enclave memory and CPUs are from the same NUMA node.
* Add minimum enclave memory size definition.
* v3: https://lore.kernel.org/lkml/20200525221334.62966-1-andraprs@amazon.com/ 

v2 -> v3

* Rebase on top of v5.7-rc7.
* Add changelog to each patch in the series.
* Remove "ratelimited" from the logs that are not in the ioctl call paths.
* Update static calls sanity checks.
* Remove file ops that do nothing for now.
* Remove GPL additional wording as SPDX-License-Identifier is already in place.
* v2: https://lore.kernel.org/lkml/20200522062946.28973-1-andraprs@amazon.com/

v1 -> v2

* Rebase on top of v5.7-rc6.
* Adapt codebase based on feedback from v1.
* Update ioctl number definition - major and minor.
* Add sample / documentation for the ioctl interface basic flow usage.
* Update cover letter to include more context on the NE overall.
* Add fix for the enclave / vcpu fd creation error cleanup path.
* Add fix reported by kbuild test robot <lkp@intel.com>.
* v1: https://lore.kernel.org/lkml/20200421184150.68011-1-andraprs@amazon.com/

---

Andra Paraschiv (18):
  nitro_enclaves: Add ioctl interface definition
  nitro_enclaves: Define the PCI device interface
  nitro_enclaves: Define enclave info for internal bookkeeping
  nitro_enclaves: Init PCI device driver
  nitro_enclaves: Handle PCI device command requests
  nitro_enclaves: Handle out-of-band PCI device events
  nitro_enclaves: Init misc device providing the ioctl interface
  nitro_enclaves: Add logic for creating an enclave VM
  nitro_enclaves: Add logic for setting an enclave vCPU
  nitro_enclaves: Add logic for getting the enclave image load info
  nitro_enclaves: Add logic for setting an enclave memory region
  nitro_enclaves: Add logic for starting an enclave
  nitro_enclaves: Add logic for terminating an enclave
  nitro_enclaves: Add Kconfig for the Nitro Enclaves driver
  nitro_enclaves: Add Makefile for the Nitro Enclaves driver
  nitro_enclaves: Add sample for ioctl interface usage
  nitro_enclaves: Add overview documentation
  MAINTAINERS: Add entry for the Nitro Enclaves driver

 .../userspace-api/ioctl/ioctl-number.rst      |    5 +-
 Documentation/virt/index.rst                  |    1 +
 Documentation/virt/ne_overview.rst            |   95 +
 MAINTAINERS                                   |   13 +
 drivers/virt/Kconfig                          |    2 +
 drivers/virt/Makefile                         |    2 +
 drivers/virt/nitro_enclaves/Kconfig           |   20 +
 drivers/virt/nitro_enclaves/Makefile          |    9 +
 drivers/virt/nitro_enclaves/ne_misc_dev.c     | 1733 +++++++++++++++++
 drivers/virt/nitro_enclaves/ne_misc_dev.h     |  109 ++
 drivers/virt/nitro_enclaves/ne_pci_dev.c      |  625 ++++++
 drivers/virt/nitro_enclaves/ne_pci_dev.h      |  327 ++++
 include/linux/nitro_enclaves.h                |   11 +
 include/uapi/linux/nitro_enclaves.h           |  359 ++++
 samples/nitro_enclaves/.gitignore             |    2 +
 samples/nitro_enclaves/Makefile               |   16 +
 samples/nitro_enclaves/ne_ioctl_sample.c      |  883 +++++++++
 17 files changed, 4211 insertions(+), 1 deletion(-)
 create mode 100644 Documentation/virt/ne_overview.rst
 create mode 100644 drivers/virt/nitro_enclaves/Kconfig
 create mode 100644 drivers/virt/nitro_enclaves/Makefile
 create mode 100644 drivers/virt/nitro_enclaves/ne_misc_dev.c
 create mode 100644 drivers/virt/nitro_enclaves/ne_misc_dev.h
 create mode 100644 drivers/virt/nitro_enclaves/ne_pci_dev.c
 create mode 100644 drivers/virt/nitro_enclaves/ne_pci_dev.h
 create mode 100644 include/linux/nitro_enclaves.h
 create mode 100644 include/uapi/linux/nitro_enclaves.h
 create mode 100644 samples/nitro_enclaves/.gitignore
 create mode 100644 samples/nitro_enclaves/Makefile
 create mode 100644 samples/nitro_enclaves/ne_ioctl_sample.c
```
#### [PATCH v5 0/4] KVM: nSVM: ondemand nested state allocation
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
From patchwork Mon Sep 21 13:19:19 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 11789833
Return-Path: <SRS0=AHPx=C6=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 59B11112C
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 21 Sep 2020 13:19:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3BA3121D43
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 21 Sep 2020 13:19:39 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="bPct19gy"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727045AbgIUNTf (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 21 Sep 2020 09:19:35 -0400
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:30752 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726876AbgIUNTf (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 21 Sep 2020 09:19:35 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1600694374;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=2li71nHKDdeIHk4pBYNK/fNmoEg3vB9ERzI+dLskZvo=;
        b=bPct19gyY+B6+dw+al61BDgFX6fTfSongPZczHIxyTdPdkfPaKY0cQwlso8qkU7JZX7bzT
        8YryzdWBBKep9nDCg/6FA77TFor3HK1mcvg5KGcfXCIa0CgOHSroLHyrBg0GxCpsz0j1+r
        urFJCEHkx5tD/ctcG7Q9Zg9LOqm8l8c=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-332-_ZZloquDNz6-Zlg1Un68nQ-1; Mon, 21 Sep 2020 09:19:32 -0400
X-MC-Unique: _ZZloquDNz6-Zlg1Un68nQ-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id A19F018C89C1;
        Mon, 21 Sep 2020 13:19:30 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.206.238])
        by smtp.corp.redhat.com (Postfix) with ESMTP id DBD133782;
        Mon, 21 Sep 2020 13:19:25 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>,
        "H. Peter Anvin" <hpa@zytor.com>, Joerg Roedel <joro@8bytes.org>,
        Ingo Molnar <mingo@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        x86@kernel.org (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT)),
        Wanpeng Li <wanpengli@tencent.com>,
        Borislav Petkov <bp@alien8.de>,
        Jim Mattson <jmattson@google.com>,
        linux-kernel@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH v5 0/4] KVM: nSVM: ondemand nested state allocation
Date: Mon, 21 Sep 2020 16:19:19 +0300
Message-Id: <20200921131923.120833-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is yet another version of ondemand nested state allocation.

In this version I adoped the suggestion of Sean Christopherson
to return make EFER write return a negative error which then should
propogate to the userspace.

So I fixed the WRMSR code to actually obey this (#GP on positive
return value, exit to userspace when negative error value,
and success on 0 error value, and fixed one user (xen)
that returned negative error code on failures.

The XEN patch is only compile tested. The rest were tested
by always returning -ENOMEM from svm_allocate_nested.

Best regards,
	Maxim Levitsky

Maxim Levitsky (4):
  KVM: x86: xen_hvm_config cleanup return values
  KVM: x86: report negative values from wrmsr to userspace
  KVM: x86: allow kvm_x86_ops.set_efer to return a value
  KVM: nSVM: implement ondemand allocation of the nested state

 arch/x86/include/asm/kvm_host.h |  2 +-
 arch/x86/kvm/emulate.c          |  7 ++--
 arch/x86/kvm/svm/nested.c       | 42 ++++++++++++++++++++++++
 arch/x86/kvm/svm/svm.c          | 58 +++++++++++++++++++--------------
 arch/x86/kvm/svm/svm.h          |  8 ++++-
 arch/x86/kvm/vmx/vmx.c          |  9 +++--
 arch/x86/kvm/x86.c              | 36 ++++++++++----------
 7 files changed, 113 insertions(+), 49 deletions(-)
```
