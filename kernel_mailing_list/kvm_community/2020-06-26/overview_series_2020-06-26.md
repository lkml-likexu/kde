#### [PATCH kvm-unit-tests] x86: map bottom 2G 1:1 into page tables
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11626631
Return-Path: <SRS0=HaOM=AH=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6CE1192A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 26 Jun 2020 07:19:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 496EC20768
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 26 Jun 2020 07:19:08 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="cP8wQtSa"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728277AbgFZHTH (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 26 Jun 2020 03:19:07 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:40113 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1725884AbgFZHTG (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 26 Jun 2020 03:19:06 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1593155945;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=Kd8no0/JYBBJaey3wsd+KD3bY5C0EF+almWIUr0Z1a8=;
        b=cP8wQtSaOKjTab5sd8KrT775qfRVi+zp5yMsg+2AhbL63nVuw50cXjC1CdCa5PlcBZC2oH
        OXWbdhcknLmsRWsL8TsFdwomQ+jFRH+/Jd1DTxf3wVqE660fhjL10vwSoqmrkVfe0ljHl6
        qVXwWI1O3LVLyBT6Puq7U/XYBGtpkDA=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-1-D9phEzF5PuykqpQkHWiDSg-1; Fri, 26 Jun 2020 03:19:00 -0400
X-MC-Unique: D9phEzF5PuykqpQkHWiDSg-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id CB2AEEC1B3
        for <kvm@vger.kernel.org>; Fri, 26 Jun 2020 07:18:59 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 8CE405F9DB
        for <kvm@vger.kernel.org>; Fri, 26 Jun 2020 07:18:59 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: kvm@vger.kernel.org
Subject: [PATCH kvm-unit-tests] x86: map bottom 2G 1:1 into page tables
Date: Fri, 26 Jun 2020 03:18:59 -0400
Message-Id: <20200626071859.6827-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Right now only addresses up to the highest RAM memory address are
are mapped 1:1 into the 32-bit page tables, but this also excludes
ACPI-reserved areas that are higher than the highest RAM memory
address.  Depending on the memory layout, this may prevent the
tests from accessing the ACPI tables after setup_vm.  Unconditionally
including the bottom 2G of memory fixes that.  We do rely on the
ACPI tables being in the first 2GB of memory, which is not necessarily
true on bare metal; fixing that requires adding calls to something like
Linux's kmap/kunmap.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 lib/x86/vm.c | 3 +--
 1 file changed, 1 insertion(+), 2 deletions(-)

```
#### [PATCH v5 01/21] pc: Support coldplugging of virtio-pmem-pci devices on all buses
##### From: David Hildenbrand <david@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Hildenbrand <david@redhat.com>
X-Patchwork-Id: 11626635
Return-Path: <SRS0=HaOM=AH=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5CA7992A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 26 Jun 2020 07:23:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 440B72080C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 26 Jun 2020 07:23:25 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="GP57/3T6"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726504AbgFZHXY (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 26 Jun 2020 03:23:24 -0400
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:24872 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1725855AbgFZHXY (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 26 Jun 2020 03:23:24 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1593156202;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=k5gcxusQzyzo3jSltVar2tBWqpPktP5b6qDTjVFvjTk=;
        b=GP57/3T6Wr5Yb9FgtTzT5wfjcBhEluOXLRdItJT9cu5iLcZjXemcgIphc9optQiMzkrGO3
        bG0FL7ZkMvUw8uh1N58tnVe/LGDgvfQWHHY3QKag4qime9qEmA8PHdV9sUnn+5ouHLZ/B7
        hkxXWt6/3U0NOxmWVbuDMYw47ChjwZ4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-263-V9G5qmFIM82M1WqWRFUFRA-1; Fri, 26 Jun 2020 03:23:19 -0400
X-MC-Unique: V9G5qmFIM82M1WqWRFUFRA-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 0BE368015FB;
        Fri, 26 Jun 2020 07:23:18 +0000 (UTC)
Received: from t480s.redhat.com (ovpn-113-35.ams2.redhat.com [10.36.113.35])
        by smtp.corp.redhat.com (Postfix) with ESMTP id CEDF360C1D;
        Fri, 26 Jun 2020 07:23:08 +0000 (UTC)
From: David Hildenbrand <david@redhat.com>
To: qemu-devel@nongnu.org
Cc: kvm@vger.kernel.org, qemu-s390x@nongnu.org,
        Richard Henderson <rth@twiddle.net>,
        Paolo Bonzini <pbonzini@redhat.com>,
        "Dr . David Alan Gilbert" <dgilbert@redhat.com>,
        Eduardo Habkost <ehabkost@redhat.com>,
        "Michael S . Tsirkin" <mst@redhat.com>,
        David Hildenbrand <david@redhat.com>,
        Vivek Goyal <vgoyal@redhat.com>,
        Pankaj Gupta <pankaj.gupta.linux@gmail.com>,
        Igor Mammedov <imammedo@redhat.com>,
        Marcel Apfelbaum <marcel.apfelbaum@gmail.com>
Subject: [PATCH v5 01/21] pc: Support coldplugging of virtio-pmem-pci devices
 on all buses
Date: Fri, 26 Jun 2020 09:22:28 +0200
Message-Id: <20200626072248.78761-2-david@redhat.com>
In-Reply-To: <20200626072248.78761-1-david@redhat.com>
References: <20200626072248.78761-1-david@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

E.g., with "pc-q35-4.2", trying to coldplug a virtio-pmem-pci devices
results in
    "virtio-pmem-pci not supported on this bus"

Reasons is, that the bus does not support hotplug and, therefore, does
not have a hotplug handler. Let's allow coldplugging virtio-pmem devices
on such buses. The hotplug order is only relevant for virtio-pmem-pci
when the guest is already alive and the device is visible before
memory_device_plug() wired up the memory device bits.

Hotplug attempts will still fail with:
    "Error: Bus 'pcie.0' does not support hotplugging"

Hotunplug attempts will still fail with:
    "Error: Bus 'pcie.0' does not support hotplugging"

Reported-by: Vivek Goyal <vgoyal@redhat.com>
Reviewed-by: Pankaj Gupta <pankaj.gupta.linux@gmail.com>
Cc: Pankaj Gupta <pankaj.gupta.linux@gmail.com>
Cc: Igor Mammedov <imammedo@redhat.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Richard Henderson <rth@twiddle.net>
Cc: Eduardo Habkost <ehabkost@redhat.com>
Cc: "Michael S. Tsirkin" <mst@redhat.com>
Cc: Marcel Apfelbaum <marcel.apfelbaum@gmail.com>
Signed-off-by: David Hildenbrand <david@redhat.com>
---
 hw/i386/pc.c | 18 ++++++++++--------
 1 file changed, 10 insertions(+), 8 deletions(-)

```
#### [kvm-unit-tests PATCH 1/3] x86: realmode: initialize idtr
##### From: Nadav Amit <namit@vmware.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Nadav Amit <namit@vmware.com>
X-Patchwork-Id: 11626907
Return-Path: <SRS0=HaOM=AH=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0A00E912
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 26 Jun 2020 09:26:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id ED1EA21527
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 26 Jun 2020 09:26:05 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726548AbgFZJ0C (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 26 Jun 2020 05:26:02 -0400
Received: from ex13-edg-ou-002.vmware.com ([208.91.0.190]:59908 "EHLO
        EX13-EDG-OU-002.vmware.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1725983AbgFZJ0B (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 26 Jun 2020 05:26:01 -0400
Received: from sc9-mailhost2.vmware.com (10.113.161.72) by
 EX13-EDG-OU-002.vmware.com (10.113.208.156) with Microsoft SMTP Server id
 15.0.1156.6; Fri, 26 Jun 2020 02:25:55 -0700
Received: from sc2-haas01-esx0118.eng.vmware.com
 (sc2-haas01-esx0118.eng.vmware.com [10.172.44.118])
        by sc9-mailhost2.vmware.com (Postfix) with ESMTP id EE476B1605;
        Fri, 26 Jun 2020 05:25:59 -0400 (EDT)
From: Nadav Amit <namit@vmware.com>
To: Paolo Bonzini <pbonzini@redhat.com>
CC: <kvm@vger.kernel.org>, Nadav Amit <namit@vmware.com>
Subject: [kvm-unit-tests PATCH 1/3] x86: realmode: initialize idtr
Date: Fri, 26 Jun 2020 02:23:31 -0700
Message-ID: <20200626092333.2830-2-namit@vmware.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200626092333.2830-1-namit@vmware.com>
References: <20200626092333.2830-1-namit@vmware.com>
MIME-Version: 1.0
Received-SPF: None (EX13-EDG-OU-002.vmware.com: namit@vmware.com does not
 designate permitted sender hosts)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The realmode test does not initialize the IDTR, assuming that its base
is zero and its limit 0x3ff. Initialize it, as the BIOS might not set it
as such.

Signed-off-by: Nadav Amit <namit@vmware.com>
---
 x86/realmode.c | 2 ++
 1 file changed, 2 insertions(+)

```
