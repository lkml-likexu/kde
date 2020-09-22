#### [PATCH v10 01/18] nitro_enclaves: Add ioctl interface definition
##### From: Andra Paraschiv <andraprs@amazon.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andra Paraschiv <andraprs@amazon.com>
X-Patchwork-Id: 11789633
Return-Path: <SRS0=AHPx=C6=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2EFCD59D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 21 Sep 2020 12:18:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 064A220EDD
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 21 Sep 2020 12:18:17 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amazon.com header.i=@amazon.com
 header.b="JerHwD1c"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726890AbgIUMSP (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 21 Sep 2020 08:18:15 -0400
Received: from smtp-fw-9101.amazon.com ([207.171.184.25]:62967 "EHLO
        smtp-fw-9101.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726821AbgIUMSL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 21 Sep 2020 08:18:11 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.com; i=@amazon.com; q=dns/txt; s=amazon201209;
  t=1600690690; x=1632226690;
  h=from:to:cc:subject:date:message-id:in-reply-to:
   references:mime-version:content-transfer-encoding;
  bh=Bc9SKYxp+Cr0jfY4LMyEZnliXp3XrqjHgNt1GfIdxYk=;
  b=JerHwD1c4zaQtuFeKjPy6remlP7ApGCQpAHxp5t7T8cvC1BvQsv/EStm
   c9My/K5eTNjrl2JK9xkXQr/yKri2TtL00AmD3YBUx/CeBxp9VWV3vHRWx
   A8j2jLdAe9mWTcyG4i+ddVuz7X+4+wXh2OYMInxW3IO1y5EXOHMHnmE3V
   U=;
X-IronPort-AV: E=Sophos;i="5.77,286,1596499200";
   d="scan'208";a="69767539"
Received: from sea32-co-svc-lb4-vlan3.sea.corp.amazon.com (HELO
 email-inbound-relay-1e-303d0b0e.us-east-1.amazon.com) ([10.47.23.38])
  by smtp-border-fw-out-9101.sea19.amazon.com with ESMTP;
 21 Sep 2020 12:18:09 +0000
Received: from EX13D16EUB001.ant.amazon.com
 (iad12-ws-svc-p26-lb9-vlan2.iad.amazon.com [10.40.163.34])
        by email-inbound-relay-1e-303d0b0e.us-east-1.amazon.com (Postfix) with
 ESMTPS id A18BCA17FF;
        Mon, 21 Sep 2020 12:18:07 +0000 (UTC)
Received: from 38f9d34ed3b1.ant.amazon.com (10.43.160.229) by
 EX13D16EUB001.ant.amazon.com (10.43.166.28) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Mon, 21 Sep 2020 12:17:56 +0000
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
Subject: [PATCH v10 01/18] nitro_enclaves: Add ioctl interface definition
Date: Mon, 21 Sep 2020 15:17:15 +0300
Message-ID: <20200921121732.44291-2-andraprs@amazon.com>
X-Mailer: git-send-email 2.20.1 (Apple Git-117)
In-Reply-To: <20200921121732.44291-1-andraprs@amazon.com>
References: <20200921121732.44291-1-andraprs@amazon.com>
MIME-Version: 1.0
X-Originating-IP: [10.43.160.229]
X-ClientProxiedBy: EX13D36UWB001.ant.amazon.com (10.43.161.84) To
 EX13D16EUB001.ant.amazon.com (10.43.166.28)
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The Nitro Enclaves driver handles the enclave lifetime management. This
includes enclave creation, termination and setting up its resources such
as memory and CPU.

An enclave runs alongside the VM that spawned it. It is abstracted as a
process running in the VM that launched it. The process interacts with
the NE driver, that exposes an ioctl interface for creating an enclave
and setting up its resources.

Changelog

v9 -> v10

* Update commit message to include the changelog before the SoB tag(s).

v8 -> v9

* No changes.

v7 -> v8

* Add NE custom error codes for user space memory regions not backed by
  pages multiple of 2 MiB, invalid flags and enclave CID.
* Add max flag value for enclave image load info.

v6 -> v7

* Clarify in the ioctls documentation that the return value is -1 and
  errno is set on failure.
* Update the error code value for NE_ERR_INVALID_MEM_REGION_SIZE as it
  gets in user space as value 25 (ENOTTY) instead of 515. Update the
  NE custom error codes values range to not be the same as the ones
  defined in include/linux/errno.h, although these are not propagated
  to user space.

v5 -> v6

* Fix typo in the description about the NE CPU pool.
* Update documentation to kernel-doc format.
* Remove the ioctl to query API version.

v4 -> v5

* Add more details about the ioctl calls usage e.g. error codes, file
  descriptors used.
* Update the ioctl to set an enclave vCPU to not return a file
  descriptor.
* Add specific NE error codes.

v3 -> v4

* Decouple NE ioctl interface from KVM API.
* Add NE API version and the corresponding ioctl call.
* Add enclave / image load flags options.

v2 -> v3

* Remove the GPL additional wording as SPDX-License-Identifier is
  already in place.

v1 -> v2

* Add ioctl for getting enclave image load metadata.
* Update NE_ENCLAVE_START ioctl name to NE_START_ENCLAVE.
* Add entry in Documentation/userspace-api/ioctl/ioctl-number.rst for NE
  ioctls.
* Update NE ioctls definition based on the updated ioctl range for major
  and minor.

Signed-off-by: Alexandru Vasile <lexnv@amazon.com>
Signed-off-by: Andra Paraschiv <andraprs@amazon.com>
Reviewed-by: Alexander Graf <graf@amazon.com>
Reviewed-by: Stefan Hajnoczi <stefanha@redhat.com>
---
 .../userspace-api/ioctl/ioctl-number.rst      |   5 +-
 include/linux/nitro_enclaves.h                |  11 +
 include/uapi/linux/nitro_enclaves.h           | 359 ++++++++++++++++++
 3 files changed, 374 insertions(+), 1 deletion(-)
 create mode 100644 include/linux/nitro_enclaves.h
 create mode 100644 include/uapi/linux/nitro_enclaves.h

```
#### [GIT PULL] KVM changes for Linux 5.9-rc7
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11789693
Return-Path: <SRS0=AHPx=C6=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8168716BC
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 21 Sep 2020 12:35:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 526EB2151B
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 21 Sep 2020 12:35:28 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="E2R/MG9u"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726861AbgIUMf1 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 21 Sep 2020 08:35:27 -0400
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:26261 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726827AbgIUMf0 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 21 Sep 2020 08:35:26 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1600691724;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=3MHjQ9sOgc6BwRarKA9h7qCAMjbrE8l16YL9VPJPBJw=;
        b=E2R/MG9u8kdd34t50pwgAS3qktDyakddMQUrsNtuOnOu+LLuKOouYMJX2pkLa7RTh6qr0k
        xtYhqrk/yyjwTuB6uERDYmVjIHmEw1KlJBPpJVj8uuG5ndPxt5nJEj9hSIT5hx3jyhvO7D
        fhr3bN8tyNoHbjXxLZ4kG2FPhVbNsB8=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-276-JiOu7vgSNympMUI_0jrkFA-1; Mon, 21 Sep 2020 08:35:22 -0400
X-MC-Unique: JiOu7vgSNympMUI_0jrkFA-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id C459B10BBEC0;
        Mon, 21 Sep 2020 12:35:21 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 633FF7881A;
        Mon, 21 Sep 2020 12:35:21 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: torvalds@linux-foundation.org
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [GIT PULL] KVM changes for Linux 5.9-rc7
Date: Mon, 21 Sep 2020 08:35:20 -0400
Message-Id: <20200921123520.1255391-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Linus,

The following changes since commit 37f66bbef0920429b8cb5eddba849ec4308a9f8e:

  KVM: emulator: more strict rsm checks. (2020-09-12 12:22:55 -0400)

are available in the Git repository at:

  https://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to be6c230c3c471d32ef9d18559dc50bd5b01aa068:

  Merge tag 'kvm-s390-master-5.9-1' of git://git.kernel.org/pub/scm/linux/kernel/git/kvms390/linux into kvm-master (2020-09-20 09:14:54 -0400)

----------------------------------------------------------------
ARM:
- fix fault on page table writes during instruction fetch

s390:
- doc improvement

x86:
- The obvious patches are always the ones that turn out to be
  completely broken.  /me hangs his head in shame.

----------------------------------------------------------------
Collin Walling (1):
      docs: kvm: add documentation for KVM_CAP_S390_DIAG318

Marc Zyngier (2):
      KVM: arm64: Assume write fault on S1PTW permission fault on instruction fetch
      KVM: arm64: Remove S1PTW check from kvm_vcpu_dabt_iswrite()

Paolo Bonzini (2):
      Merge tag 'kvmarm-fixes-5.9-2' of git://git.kernel.org/.../kvmarm/kvmarm into kvm-master
      Merge tag 'kvm-s390-master-5.9-1' of git://git.kernel.org/.../kvms390/linux into kvm-master

Vitaly Kuznetsov (1):
      Revert "KVM: Check the allocation of pv cpu mask"

 Documentation/virt/kvm/api.rst          | 20 ++++++++++++++++++++
 arch/arm64/include/asm/kvm_emulate.h    | 14 +++++++++++---
 arch/arm64/kvm/hyp/include/hyp/switch.h |  2 +-
 arch/arm64/kvm/mmu.c                    |  4 ++--
 arch/x86/kernel/kvm.c                   | 22 +++-------------------
 5 files changed, 37 insertions(+), 25 deletions(-)
```
#### [PATCH v2 1/1] KVM: x86: fix MSR_IA32_TSC read for nested migration
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 11789247
Return-Path: <SRS0=AHPx=C6=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3ADC959D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 21 Sep 2020 10:38:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 20DF0214F1
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 21 Sep 2020 10:38:27 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Q+naJDf2"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726705AbgIUKiY (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 21 Sep 2020 06:38:24 -0400
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:45680 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726694AbgIUKiY (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 21 Sep 2020 06:38:24 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1600684703;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=ONnIZ3SBrEIJ/yZ6oWe7vybmIgHqvGfE9nXfpRPVygs=;
        b=Q+naJDf2MuWw2Gvrg1eIWWFUxonJN2IBiWR7iMlDS27nwwGJNLfFIe1XX5rTMD1DCGQN7u
        s8PO/tCiK4joCz/BSHeTHT82hPkbbaaiIbwArOG9rFXJKiPlO4f/PSJ6XcbmN9PgKL2ebA
        0zym/pcmd4FIG37yDbMaUiWOn8XNy40=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-586-BHYcpO1oM6mJsLJ7ZyS9Pw-1; Mon, 21 Sep 2020 06:38:21 -0400
X-MC-Unique: BHYcpO1oM6mJsLJ7ZyS9Pw-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id A94B21007461;
        Mon, 21 Sep 2020 10:38:19 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.206.238])
        by smtp.corp.redhat.com (Postfix) with ESMTP id A99A46886C;
        Mon, 21 Sep 2020 10:38:13 +0000 (UTC)
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
Subject: [PATCH v2 1/1] KVM: x86: fix MSR_IA32_TSC read for nested migration
Date: Mon, 21 Sep 2020 13:38:05 +0300
Message-Id: <20200921103805.9102-2-mlevitsk@redhat.com>
In-Reply-To: <20200921103805.9102-1-mlevitsk@redhat.com>
References: <20200921103805.9102-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

MSR reads/writes should always access the L1 state, since the (nested)
hypervisor should intercept all the msrs it wants to adjust, and these
that it doesn't should be read by the guest as if the host had read it.

However IA32_TSC is an exception. Even when not intercepted, guest still
reads the value + TSC offset.
The write however does not take any TSC offset into account.

This is documented in Intel's SDM and seems also to happen on AMD as well.

This creates a problem when userspace wants to read the IA32_TSC value and then
write it. (e.g for migration)

In this case it reads L2 value but write is interpreted as an L1 value.
To fix this make the userspace initiated reads of IA32_TSC return L1 value
as well.

Huge thanks to Dave Gilbert for helping me understand this very confusing
semantic of MSR writes.

Signed-off-by: Maxim Levitsky <mlevitsk@redhat.com>
---
 arch/x86/kvm/x86.c | 16 ++++++++++++++--
 1 file changed, 14 insertions(+), 2 deletions(-)

```
#### [PATCH v5 1/4] KVM: x86: xen_hvm_config: cleanup return values
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 11789835
Return-Path: <SRS0=AHPx=C6=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id ABC0E112C
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 21 Sep 2020 13:19:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8BC1621D43
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 21 Sep 2020 13:19:41 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="M9KDTSgP"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727137AbgIUNTk (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 21 Sep 2020 09:19:40 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:30213 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726353AbgIUNTj (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 21 Sep 2020 09:19:39 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1600694378;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=Cp4MK36U1jUXwvFeIryJqYh6pqv7rYh+phHr+1tztts=;
        b=M9KDTSgPV9ev8Ojy0gy2HpaeXaf2LlC2NKRTkzKHZj1bMGXwir88627OETzpJ+amxFkRCT
        ngyjGvt9px1Mp13UM+3PGki6r8F3aGKlDCy3kPiO2hXsfcqe1mbLahuAIn3l5ug+TLtlyJ
        Q3PeRDdh1ckcUdbQ4Hun1JM7fqQoDWs=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-383-wSnF_GshO6-Hf3MS57MiRg-1; Mon, 21 Sep 2020 09:19:36 -0400
X-MC-Unique: wSnF_GshO6-Hf3MS57MiRg-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id B8CD5802B4A;
        Mon, 21 Sep 2020 13:19:34 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.206.238])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 1790455765;
        Mon, 21 Sep 2020 13:19:30 +0000 (UTC)
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
Subject: [PATCH v5 1/4] KVM: x86: xen_hvm_config: cleanup return values
Date: Mon, 21 Sep 2020 16:19:20 +0300
Message-Id: <20200921131923.120833-2-mlevitsk@redhat.com>
In-Reply-To: <20200921131923.120833-1-mlevitsk@redhat.com>
References: <20200921131923.120833-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

MSR writes should return 1 when giving #GP to the user,
and negative value when fatal error (e.g out of memory)
happened.

Signed-off-by: Maxim Levitsky <mlevitsk@redhat.com>
---
 arch/x86/kvm/x86.c | 23 +++++++++--------------
 1 file changed, 9 insertions(+), 14 deletions(-)

```
#### [PATCH 1/3 v3] KVM: nVMX: KVM needs to unset "unrestricted guest" VM-execution control in vmcs02 if vmcs12 doesn't set it
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11788901
Return-Path: <SRS0=AHPx=C6=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6671D139F
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 21 Sep 2020 08:12:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 458C2214F1
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 21 Sep 2020 08:12:45 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="iF/4Geci"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726532AbgIUIMo (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 21 Sep 2020 04:12:44 -0400
Received: from aserp2120.oracle.com ([141.146.126.78]:46710 "EHLO
        aserp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726334AbgIUIMo (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 21 Sep 2020 04:12:44 -0400
Received: from pps.filterd (aserp2120.oracle.com [127.0.0.1])
        by aserp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 08L898vp163663;
        Mon, 21 Sep 2020 08:12:39 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references; s=corp-2020-01-29;
 bh=9P1BqW5eEbN0sm2+B7OnQjLwAserdN/C+elcGXIC7Lo=;
 b=iF/4Geci4wf7es0sEgE2g4Hcw6u9oheYE0df46kGUeKuHGrMAo0PMNT4WQNhNMFsJ9HM
 8HVO5E97oiBFuBMgF5Gb/2jay9tbEWWjGxpEUTdM0tyxPEbBuqakVtGTpipv4WSC+xqW
 bIfjTA2UI7glr9KO8+NPnDCKo0gaQAiKSz7x3Y2EWIp3FDl4SPzDSTamVxeLT37BhAQ8
 5OHjFnQ7ltkIOHpCKMLa2uYhLp623Xhkonzd8+sT83efQufSiAmt7KajgBguxyhSSPLB
 zVdvEbZcEAx2j/X5qpOq+Xgbq3lxwX9OYMa1rqrk0dleQTa0vr4/qpMZTpHd6I6bZE4h Kw==
Received: from aserp3030.oracle.com (aserp3030.oracle.com [141.146.126.71])
        by aserp2120.oracle.com with ESMTP id 33n9xkm3aa-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=FAIL);
        Mon, 21 Sep 2020 08:12:39 +0000
Received: from pps.filterd (aserp3030.oracle.com [127.0.0.1])
        by aserp3030.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 08L86GHV142937;
        Mon, 21 Sep 2020 08:10:38 GMT
Received: from userv0122.oracle.com (userv0122.oracle.com [156.151.31.75])
        by aserp3030.oracle.com with ESMTP id 33nujkb3df-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 21 Sep 2020 08:10:38 +0000
Received: from abhmp0016.oracle.com (abhmp0016.oracle.com [141.146.116.22])
        by userv0122.oracle.com (8.14.4/8.14.4) with ESMTP id 08L8AbcB022458;
        Mon, 21 Sep 2020 08:10:37 GMT
Received: from sadhukhan-nvmx.osdevelopmeniad.oraclevcn.com (/100.100.230.226)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Mon, 21 Sep 2020 01:10:37 -0700
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com,
        sean.j.christopherson@intel.com
Subject: [PATCH 1/3 v3] KVM: nVMX: KVM needs to unset "unrestricted guest"
 VM-execution control in vmcs02 if vmcs12 doesn't set it
Date: Mon, 21 Sep 2020 08:10:25 +0000
Message-Id: <20200921081027.23047-2-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.18.4
In-Reply-To: <20200921081027.23047-1-krish.sadhukhan@oracle.com>
References: <20200921081027.23047-1-krish.sadhukhan@oracle.com>
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9750
 signatures=668679
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 bulkscore=0
 malwarescore=0
 mlxlogscore=999 phishscore=0 adultscore=0 spamscore=0 suspectscore=1
 mlxscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2009210059
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9750
 signatures=668679
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 lowpriorityscore=0 malwarescore=0
 suspectscore=1 priorityscore=1501 adultscore=0 spamscore=0 clxscore=1015
 mlxlogscore=999 bulkscore=0 mlxscore=0 phishscore=0 impostorscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2006250000
 definitions=main-2009210059
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Currently, prepare_vmcs02_early() does not check if the "unrestricted guest"
VM-execution control in vmcs12 is turned off and leaves the corresponding
bit on in vmcs02. Due to this setting, vmentry checks which are supposed to
render the nested guest state as invalid when this VM-execution control is
not set, are passing in hardware.

This patch turns off the "unrestricted guest" VM-execution control in vmcs02
if vmcs12 has turned it off.

Suggested-by: Jim Mattson <jmattson@google.com>
Suggested-by: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 arch/x86/kvm/vmx/nested.c |  3 +++
 arch/x86/kvm/vmx/vmx.c    | 17 +++++++++--------
 arch/x86/kvm/vmx/vmx.h    |  7 +++++++
 3 files changed, 19 insertions(+), 8 deletions(-)

```
#### [kvm-unit-tests PATCH] scripts/arch-run: use ncat rather than nc.
##### From: Jamie Iles <jamie@nuviainc.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jamie Iles <jamie@nuviainc.com>
X-Patchwork-Id: 11789231
Return-Path: <SRS0=AHPx=C6=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C53BB6CB
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 21 Sep 2020 10:36:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9F18E218AC
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 21 Sep 2020 10:36:48 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=nuviainc-com.20150623.gappssmtp.com
 header.i=@nuviainc-com.20150623.gappssmtp.com header.b="rev57v0d"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726503AbgIUKgr (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 21 Sep 2020 06:36:47 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:33432 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726333AbgIUKgq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 21 Sep 2020 06:36:46 -0400
Received: from mail-wm1-x344.google.com (mail-wm1-x344.google.com
 [IPv6:2a00:1450:4864:20::344])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 840ABC061755
        for <kvm@vger.kernel.org>; Mon, 21 Sep 2020 03:36:46 -0700 (PDT)
Received: by mail-wm1-x344.google.com with SMTP id y15so12069069wmi.0
        for <kvm@vger.kernel.org>; Mon, 21 Sep 2020 03:36:46 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=nuviainc-com.20150623.gappssmtp.com; s=20150623;
        h=from:to:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=q2Z7oFogf9Aj/tvuJ/xWjzZlYnWlkqxbhxSK4955804=;
        b=rev57v0d0kdzPOltPtLM0GBO19LlA3oqqUoVIGXisLu6aqEKZ7eRjH1/RRU6+BIzFy
         8TJw/zAsZ4xsvDw0EzHPYOtB5IcJOGdJPQHA2xJD6xTESF5SVm8mI1LWsZ+Wo3PWxTQ3
         pSY2Qn+7Zn6YRDcWl5JVyjZNywEIzsahfS5vrLQzYjE+ceG1NefGptwqM59QgWvN4a9A
         yx1RorCx9hgjGG2ctIeTJ+K1WAo1VWaEyC8LAkkK2+l1mLf0YbPg//tOsAIDcSpclv9Z
         XQycp2+0DnfKegvF4wkMIesw92358E5qXgmNKbrHXcLcYai9H5+4gBVFgDkprQ8MQN51
         ebyg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=q2Z7oFogf9Aj/tvuJ/xWjzZlYnWlkqxbhxSK4955804=;
        b=MiQVmHcGh0+BZpJmpQZfrNY6X7w1U1zvX9c1ruJpssuwMOs35C1eLGxa7d6D78nyNf
         ZynICVRx5LoJXVokVPSC3XuOstLtWLQbxz6/LfHoGr2yiWXnwpo7om3fhVL0/Ibb84+e
         Keo0dHKcQ9i883rNKG6Npp9VoiqLV2dYg1idd/LOLpArQmqsAmz7kHoFv5fwdn4rjT2x
         CMvJsXZRrQQNE9jBTHB7UoNigoJuQnsByZ57PByZ3/FQBahyjyZvOuAdCQWPLve8Yqsi
         gzYtrBDiZztwkCftXNrqD3yL+u3K6GQI/P03zn6lP/brwg1xaaVMrdeK4l1ebLUHVGdb
         mWUw==
X-Gm-Message-State: AOAM532/Lc+hT+yohmCGh30cAwijIV0ZNSFOiXEiSZHTR9/zo/oFuw0N
        RHtG1foyTb1FYltgtXPny7RqzT1thj5rwTvbleYo5vb2uFiP+IeHa7uv42jvbhRVlKenC/fZIJl
        pkmFEQb6DDfpqFyiSooATos9H5PchULwLmourEBvOJXx3YoPv4GSLsMF29RJDCdKiXw==
X-Google-Smtp-Source: 
 ABdhPJyLe9uvm+3FnIep4Eq0zau4YH8Om9f9IcKerNbiWZ/hLf9WR+xa7cNbRUVuobpiklQ88nE2nw==
X-Received: by 2002:a1c:3588:: with SMTP id
 c130mr28744472wma.94.1600684605005;
        Mon, 21 Sep 2020 03:36:45 -0700 (PDT)
Received: from localhost ([82.44.17.50])
        by smtp.gmail.com with ESMTPSA id
 c16sm21373461wrx.31.2020.09.21.03.36.44
        for <kvm@vger.kernel.org>
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 21 Sep 2020 03:36:44 -0700 (PDT)
From: Jamie Iles <jamie@nuviainc.com>
To: kvm@vger.kernel.org
Subject: [kvm-unit-tests PATCH] scripts/arch-run: use ncat rather than nc.
Date: Mon, 21 Sep 2020 11:36:44 +0100
Message-Id: <20200921103644.1718058-1-jamie@nuviainc.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

On Red Hat 7+ and derived distributions, 'nc' is nmap-ncat, but on
Debian based distributions this is often netcat-openbsd.  Both are
mostly compatible with the important distinction that netcat-openbsd
does not shutdown the socket on stdin EOF without also passing '-N' as
an argument which is not supported on nmap-ncat.  This has the
unfortunate consequence of hanging qmp calls so tests like aarch64
its-migration never complete.

We're depending on ncat behaviour and nmap-ncat is available in all
major distributions.

Signed-off-by: Jamie Iles <jamie@nuviainc.com>
---
 scripts/arch-run.bash | 6 +++---
 1 file changed, 3 insertions(+), 3 deletions(-)

```
#### [PATCH] KVM: x86/mmu: fix counting of rmap entries in pte_list_add
##### From: Li RongQing <lirongqing@baidu.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Li RongQing <lirongqing@baidu.com>
X-Patchwork-Id: 11789233
Return-Path: <SRS0=AHPx=C6=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 35EE16CB
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 21 Sep 2020 10:37:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 26E2A216C4
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 21 Sep 2020 10:37:01 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726579AbgIUKhA (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 21 Sep 2020 06:37:00 -0400
Received: from mx59.baidu.com ([61.135.168.59]:38569 "EHLO
        tc-sys-mailedm02.tc.baidu.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726333AbgIUKhA (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 21 Sep 2020 06:37:00 -0400
X-Greylist: delayed 441 seconds by postgrey-1.27 at vger.kernel.org;
 Mon, 21 Sep 2020 06:36:59 EDT
Received: from localhost (cp01-cos-dev01.cp01.baidu.com [10.92.119.46])
        by tc-sys-mailedm02.tc.baidu.com (Postfix) with ESMTP id 3E11A11C004B;
        Mon, 21 Sep 2020 18:29:26 +0800 (CST)
From: Li RongQing <lirongqing@baidu.com>
To: lirongqing@baidu.com, kvm@vger.kernel.org, x86@kernel.org
Subject: [PATCH] KVM: x86/mmu: fix counting of rmap entries in pte_list_add
Date: Mon, 21 Sep 2020 18:29:26 +0800
Message-Id: <1600684166-32430-1-git-send-email-lirongqing@baidu.com>
X-Mailer: git-send-email 1.7.1
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

counting of rmap entries was missed when desc->sptes is full
and desc->more is NULL

Signed-off-by: Li RongQing <lirongqing@baidu.com>
---
 arch/x86/kvm/mmu/mmu.c | 1 +
 1 file changed, 1 insertion(+)

```
#### [PULL v3 01/15] linux headers: sync to 5.9-rc4
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 11789445
Return-Path: <SRS0=AHPx=C6=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 929A36CA
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 21 Sep 2020 11:29:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5EFDD20EDD
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 21 Sep 2020 11:29:51 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="M+fbcapv"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726619AbgIUL3u (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 21 Sep 2020 07:29:50 -0400
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:23542 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726689AbgIUL3u (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 21 Sep 2020 07:29:50 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1600687785;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         in-reply-to:in-reply-to:references:references;
        bh=xf2I6AVSrGRq/duV5gv6UTIln0Sg/9kyZt7swxOVAAg=;
        b=M+fbcapv1FaqMVVkTUU+zBH3H2svvEgcTMpOXVABNMMfz/SYbR0RPPcyyG7inLGu3BNggq
        PM0VF51JqZxnXl77b7R0EoWxm5Ybc9YiVn1oYHJN7UTDnlZUIMzx3X0PsTD0xx+Rvt4lCe
        D/xfjGfg/AvdtnLEnCHuwpv5ZlrYdR0=
Received: from mail-wr1-f69.google.com (mail-wr1-f69.google.com
 [209.85.221.69]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-520-7bov7whONEGp9vR_9z-xZQ-1; Mon, 21 Sep 2020 07:29:43 -0400
X-MC-Unique: 7bov7whONEGp9vR_9z-xZQ-1
Received: by mail-wr1-f69.google.com with SMTP id o6so5730837wrp.1
        for <kvm@vger.kernel.org>; Mon, 21 Sep 2020 04:29:43 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:references
         :mime-version:content-disposition:in-reply-to;
        bh=xf2I6AVSrGRq/duV5gv6UTIln0Sg/9kyZt7swxOVAAg=;
        b=N4THTfDzql/gykHLqTB5n+ZrdnwQVp1BpoWfRcdNxO6FN7SpIKIbimS6SSBj2IFJL4
         t0KBn8gSgYzWFralY5XkVq+CiZB9w6ydn3wnoG3oY13vozt2RtcZMzzAC2TEjtb4xoUX
         7ODlQh1fZ2HvapApiU92x+gDWJhJg8Ar5BB3qrQ+9EeSqEcsotuLm9Jg3L6aCC0R8q6K
         KhXsppsavDC/5AbN5oth23XFedKbdPWpl08R1S+4hECxA+HPaE0ZbFMe5VjRTadtUU+T
         knfGQvK4XLNqhWGipJmtKqEkqypTGmSWk06o7WDqO0itqLjiZM+Bz4vkEzej3Ytp1WJs
         CeSQ==
X-Gm-Message-State: AOAM531OF7fh/MK2mQEqYQUWn4GV4tE93muGhqGDdpFlZIvvMZiL9E+Y
        e5PPwdjjl/1N/VtP33bbAUnJmWOF0tdzfk2EJPOlLXbHrInc+JPJ/3gYIwcD/eO7DubWXyQbMX3
        U49ALISlGJYfk
X-Received: by 2002:a5d:5312:: with SMTP id e18mr51335446wrv.95.1600687781599;
        Mon, 21 Sep 2020 04:29:41 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJwDpevdxCTscwnclpPNKpjsG9VYREbRyhI5S3Vdidv1Nb2xnpPIfEjbTmot+1qAAS1nMbJVcw==
X-Received: by 2002:a5d:5312:: with SMTP id e18mr51335404wrv.95.1600687781132;
        Mon, 21 Sep 2020 04:29:41 -0700 (PDT)
Received: from redhat.com (bzq-109-65-116-225.red.bezeqint.net.
 [109.65.116.225])
        by smtp.gmail.com with ESMTPSA id
 d9sm12527455wmb.30.2020.09.21.04.29.39
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 21 Sep 2020 04:29:40 -0700 (PDT)
Date: Mon, 21 Sep 2020 07:29:38 -0400
From: "Michael S. Tsirkin" <mst@redhat.com>
To: qemu-devel@nongnu.org
Cc: Peter Maydell <peter.maydell@linaro.org>,
        Jason Wang <jasowang@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org
Subject: [PULL v3 01/15] linux headers: sync to 5.9-rc4
Message-ID: <20200921112913.555392-2-mst@redhat.com>
References: <20200921112913.555392-1-mst@redhat.com>
MIME-Version: 1.0
Content-Disposition: inline
In-Reply-To: <20200921112913.555392-1-mst@redhat.com>
X-Mailer: git-send-email 2.27.0.106.g8ac3dc51b1
X-Mutt-Fcc: =sent
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Jason Wang <jasowang@redhat.com>

Update against Linux 5.9-rc4.

Cc: Cornelia Huck <cohuck@redhat.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Jason Wang <jasowang@redhat.com>
Message-Id: <20200907104903.31551-2-jasowang@redhat.com>
Reviewed-by: Michael S. Tsirkin <mst@redhat.com>
Signed-off-by: Michael S. Tsirkin <mst@redhat.com>
---
 include/standard-headers/drm/drm_fourcc.h     | 140 ++++++++++++++++++
 include/standard-headers/linux/ethtool.h      |  87 +++++++++++
 .../linux/input-event-codes.h                 |   3 +-
 include/standard-headers/linux/vhost_types.h  |  11 ++
 include/standard-headers/linux/virtio_9p.h    |   4 +-
 include/standard-headers/linux/virtio_blk.h   |  26 ++--
 .../standard-headers/linux/virtio_config.h    |   8 +-
 .../standard-headers/linux/virtio_console.h   |   8 +-
 include/standard-headers/linux/virtio_net.h   |   6 +-
 include/standard-headers/linux/virtio_scsi.h  |  20 +--
 linux-headers/asm-generic/unistd.h            |   6 +-
 linux-headers/asm-mips/unistd_n32.h           |   1 +
 linux-headers/asm-mips/unistd_n64.h           |   1 +
 linux-headers/asm-mips/unistd_o32.h           |   1 +
 linux-headers/asm-powerpc/kvm.h               |   5 +
 linux-headers/asm-powerpc/unistd_32.h         |   1 +
 linux-headers/asm-powerpc/unistd_64.h         |   1 +
 linux-headers/asm-s390/kvm.h                  |   7 +-
 linux-headers/asm-s390/unistd_32.h            |   1 +
 linux-headers/asm-s390/unistd_64.h            |   1 +
 linux-headers/asm-x86/unistd_32.h             |   1 +
 linux-headers/asm-x86/unistd_64.h             |   1 +
 linux-headers/asm-x86/unistd_x32.h            |   1 +
 linux-headers/linux/kvm.h                     |   4 +
 linux-headers/linux/vfio.h                    |   2 +-
 linux-headers/linux/vhost.h                   |   2 +
 26 files changed, 308 insertions(+), 41 deletions(-)

```
#### [PATCH v2 1/2] vfio/pci: Remove redundant declaration of vfio_pci_driver
##### From: Zenghui Yu <yuzenghui@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zenghui Yu <yuzenghui@huawei.com>
X-Patchwork-Id: 11788317
Return-Path: <SRS0=AHPx=C6=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0AC7E139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 21 Sep 2020 04:51:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id F06242084C
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 21 Sep 2020 04:51:46 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726244AbgIUEvg (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 21 Sep 2020 00:51:36 -0400
Received: from szxga05-in.huawei.com ([45.249.212.191]:13735 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726011AbgIUEvg (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 21 Sep 2020 00:51:36 -0400
Received: from DGGEMS414-HUB.china.huawei.com (unknown [172.30.72.59])
        by Forcepoint Email with ESMTP id ACE0EDAEC123FCDC541F;
        Mon, 21 Sep 2020 12:51:32 +0800 (CST)
Received: from DESKTOP-8RFUVS3.china.huawei.com (10.174.185.226) by
 DGGEMS414-HUB.china.huawei.com (10.3.19.214) with Microsoft SMTP Server id
 14.3.487.0; Mon, 21 Sep 2020 12:51:26 +0800
From: Zenghui Yu <yuzenghui@huawei.com>
To: <kvm@vger.kernel.org>, <linux-kernel@vger.kernel.org>
CC: <alex.williamson@redhat.com>, <cohuck@redhat.com>,
        <wanghaibin.wang@huawei.com>, Zenghui Yu <yuzenghui@huawei.com>
Subject: [PATCH v2 1/2] vfio/pci: Remove redundant declaration of
 vfio_pci_driver
Date: Mon, 21 Sep 2020 12:51:15 +0800
Message-ID: <20200921045116.258-1-yuzenghui@huawei.com>
X-Mailer: git-send-email 2.23.0.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.185.226]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

It was added by commit 137e5531351d ("vfio/pci: Add sriov_configure
support") but duplicates a forward declaration earlier in the file.

Remove it.

Signed-off-by: Zenghui Yu <yuzenghui@huawei.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---
* From v1:
  - Clarify the commit message per Alex's suggestion.
  - Add Cornelia's R-b tag.

 drivers/vfio/pci/vfio_pci.c | 1 -
 1 file changed, 1 deletion(-)

```
#### [PATCH v2 2/2] vfio/pci: Don't regenerate vconfig for all BARs if !bardirty
##### From: Zenghui Yu <yuzenghui@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zenghui Yu <yuzenghui@huawei.com>
X-Patchwork-Id: 11788319
Return-Path: <SRS0=AHPx=C6=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2C64F618
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 21 Sep 2020 04:51:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 14FEC2084C
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 21 Sep 2020 04:51:47 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726357AbgIUEvk (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 21 Sep 2020 00:51:40 -0400
Received: from szxga05-in.huawei.com ([45.249.212.191]:13736 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726011AbgIUEvk (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 21 Sep 2020 00:51:40 -0400
Received: from DGGEMS414-HUB.china.huawei.com (unknown [172.30.72.58])
        by Forcepoint Email with ESMTP id EBD527101C9BF283D53A;
        Mon, 21 Sep 2020 12:51:37 +0800 (CST)
Received: from DESKTOP-8RFUVS3.china.huawei.com (10.174.185.226) by
 DGGEMS414-HUB.china.huawei.com (10.3.19.214) with Microsoft SMTP Server id
 14.3.487.0; Mon, 21 Sep 2020 12:51:29 +0800
From: Zenghui Yu <yuzenghui@huawei.com>
To: <kvm@vger.kernel.org>, <linux-kernel@vger.kernel.org>
CC: <alex.williamson@redhat.com>, <cohuck@redhat.com>,
        <wanghaibin.wang@huawei.com>, Zenghui Yu <yuzenghui@huawei.com>
Subject: [PATCH v2 2/2] vfio/pci: Don't regenerate vconfig for all BARs if
 !bardirty
Date: Mon, 21 Sep 2020 12:51:16 +0800
Message-ID: <20200921045116.258-2-yuzenghui@huawei.com>
X-Mailer: git-send-email 2.23.0.windows.1
In-Reply-To: <20200921045116.258-1-yuzenghui@huawei.com>
References: <20200921045116.258-1-yuzenghui@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.174.185.226]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Now we regenerate vconfig for all the BARs via vfio_bar_fixup(), every time
any offset of any of them are read. Though BARs aren't re-read regularly,
the regeneration can be avoid if no BARs had been written since they were
last read, in which case the vdev->bardirty is false.

Let's predicate the vfio_bar_fixup() on the bardirty so that it can return
immediately if !bardirty.

Suggested-by: Alex Williamson <alex.williamson@redhat.com>
Signed-off-by: Zenghui Yu <yuzenghui@huawei.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---
* From v1:
  - Per Alex's suggestion, let vfio_bar_fixup() test vdev->bardirty to
    avoid doing work if bardirty is false, instead of removing it entirely.
  - Rewrite the commit message.

 drivers/vfio/pci/vfio_pci_config.c | 3 +++
 1 file changed, 3 insertions(+)

```
