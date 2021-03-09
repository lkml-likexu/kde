#### [PATCH v3 10/12] memory: introduce RAM_NORESERVE and wire it up in qemu_ram_mmap()
##### From: David Hildenbrand <david@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Hildenbrand <david@redhat.com>
X-Patchwork-Id: 12122649
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 77519C433E6
	for <kvm@archiver.kernel.org>; Mon,  8 Mar 2021 15:09:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4D0A0651D1
	for <kvm@archiver.kernel.org>; Mon,  8 Mar 2021 15:09:18 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231512AbhCHPIq (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 8 Mar 2021 10:08:46 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:31073 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S231684AbhCHPIQ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 8 Mar 2021 10:08:16 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1615216096;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=jVrOZFTnsT3zj2UiCAsG7eDoDu76mO5ChVhYgbKeU/E=;
        b=Tn1LNjhRMd4uIKkmsZS0u2Vw7vdGKTymiatYfg+M1gRMgsOQvN5K4X/SSiQbmO1WlhGBjn
        9pTdCmYrGYcdLq0s/4r8D4WgroVStdySC7KLfwzqIcTmSdCnHfe4JaLtZ1b1v7Z35th2/O
        AdMKOF8EmW1sqfKO84wYW5e5vIdX9WA=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-242-oe6MMNRePruFEJn_dl7W9w-1; Mon, 08 Mar 2021 10:08:12 -0500
X-MC-Unique: oe6MMNRePruFEJn_dl7W9w-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 96BF3760C1;
        Mon,  8 Mar 2021 15:08:10 +0000 (UTC)
Received: from t480s.redhat.com (ovpn-113-123.ams2.redhat.com [10.36.113.123])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 3CC905D9CD;
        Mon,  8 Mar 2021 15:08:05 +0000 (UTC)
From: David Hildenbrand <david@redhat.com>
To: qemu-devel@nongnu.org
Cc: David Hildenbrand <david@redhat.com>, Peter Xu <peterx@redhat.com>,
 "Michael S. Tsirkin" <mst@redhat.com>, Eduardo Habkost <ehabkost@redhat.com>,
 "Dr. David Alan Gilbert" <dgilbert@redhat.com>,
 Richard Henderson <richard.henderson@linaro.org>,
 Paolo Bonzini <pbonzini@redhat.com>, Igor Mammedov <imammedo@redhat.com>,
	=?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>,
 Stefan Hajnoczi <stefanha@redhat.com>,
 Murilo Opsfelder Araujo <muriloo@linux.ibm.com>, Greg Kurz <groug@kaod.org>,
 Liam Merwick <liam.merwick@oracle.com>,
 Marcel Apfelbaum <mapfelba@redhat.com>,
 Christian Borntraeger <borntraeger@de.ibm.com>,
 Cornelia Huck <cohuck@redhat.com>, Halil Pasic <pasic@linux.ibm.com>,
 Igor Kotrasinski <i.kotrasinsk@partner.samsung.com>,
 Juan Quintela <quintela@redhat.com>, Stefan Weil <sw@weilnetz.de>,
 Thomas Huth <thuth@redhat.com>, kvm@vger.kernel.org, qemu-s390x@nongnu.org
Subject: [PATCH v3 10/12] memory: introduce RAM_NORESERVE and wire it up in
 qemu_ram_mmap()
Date: Mon,  8 Mar 2021 16:05:58 +0100
Message-Id: <20210308150600.14440-11-david@redhat.com>
In-Reply-To: <20210308150600.14440-1-david@redhat.com>
References: <20210308150600.14440-1-david@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Let's introduce RAM_NORESERVE, allowing mmap'ing with MAP_NORESERVE. The
new flag has the following semantics:

  RAM is mmap-ed with MAP_NORESERVE. When set, reserving swap space (or
  huge pages on Linux) is skipped: will bail out if not supported. When not
  set, the OS might reserve swap space (or huge pages on Linux), depending
  on OS support.

Allow passing it into:
- memory_region_init_ram_nomigrate()
- memory_region_init_resizeable_ram()
- memory_region_init_ram_from_file()

... and teach qemu_ram_mmap() and qemu_anon_ram_alloc() about the flag.
Bail out if the flag is not supported, which is the case right now for
both, POSIX and win32. We will add the POSIX mmap implementation next and
allow specifying RAM_NORESERVE via memory backends.

The target use case is virtio-mem, which dynamically exposes memory
inside a large, sparse memory area to the VM.

Cc: Juan Quintela <quintela@redhat.com>
Cc: Halil Pasic <pasic@linux.ibm.com>
Cc: Cornelia Huck <cohuck@redhat.com>
Cc: Christian Borntraeger <borntraeger@de.ibm.com>
Cc: Thomas Huth <thuth@redhat.com>
Cc: Stefan Weil <sw@weilnetz.de>
Cc: kvm@vger.kernel.org
Cc: qemu-s390x@nongnu.org
Signed-off-by: David Hildenbrand <david@redhat.com>
---
 include/exec/cpu-common.h |  1 +
 include/exec/memory.h     | 16 +++++++++++++---
 include/exec/ram_addr.h   |  3 ++-
 include/qemu/mmap-alloc.h |  3 +++
 include/qemu/osdep.h      |  3 ++-
 migration/ram.c           |  3 +--
 softmmu/physmem.c         | 15 +++++++++++----
 util/mmap-alloc.c         |  6 ++++++
 util/oslib-posix.c        |  6 ++++--
 util/oslib-win32.c        | 13 ++++++++++++-
 10 files changed, 55 insertions(+), 14 deletions(-)

```
#### [PATCH] KVM: arm64: Cap default IPA size to the host's own size
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 12123109
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No,
 score=-17.0 required=3.0 tests=BAYES_00,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id AE500C433E0
	for <kvm@archiver.kernel.org>; Mon,  8 Mar 2021 17:47:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 856D9652A7
	for <kvm@archiver.kernel.org>; Mon,  8 Mar 2021 17:47:42 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230116AbhCHRrJ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 8 Mar 2021 12:47:09 -0500
Received: from mail.kernel.org ([198.145.29.99]:44548 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S230184AbhCHRq4 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 8 Mar 2021 12:46:56 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 2450165296;
        Mon,  8 Mar 2021 17:46:52 +0000 (UTC)
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=hot-poop.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1lJJxy-000OD8-8a; Mon, 08 Mar 2021 17:46:50 +0000
From: Marc Zyngier <maz@kernel.org>
To: kvmarm@lists.cs.columbia.edu, linux-arm-kernel@lists.infradead.org,
        kvm@vger.kernel.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Alexandru Elisei <alexandru.elisei@arm.com>,
        kernel-team@android.com
Subject: [PATCH] KVM: arm64: Cap default IPA size to the host's own size
Date: Mon,  8 Mar 2021 17:46:43 +0000
Message-Id: <20210308174643.761100-1-maz@kernel.org>
X-Mailer: git-send-email 2.30.0
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: kvmarm@lists.cs.columbia.edu,
 linux-arm-kernel@lists.infradead.org, kvm@vger.kernel.org,
 james.morse@arm.com, julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 alexandru.elisei@arm.com, kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

KVM/arm64 has forever used a 40bit default IPA space, partially
due to its 32bit heritage (where the only choice is 40bit).

However, there are implementations in the wild that have a *cough*
much smaller *cough* IPA space, which leads to a misprogramming of
VTCR_EL2, and a guest that is stuck on its first memory access
if userspace dares to ask for the default IPA setting (which most
VMMs do).

Instead, cap the default IPA size to what the host can actually
do, and spit out a one-off message on the console. The boot warning
is turned into a more meaningfull message, and the new behaviour
is also documented.

Although this is a userspace ABI change, it doesn't really change
much for userspace:

- the guest couldn't run before this change, while it now has
  a chance to if the memory range fits the reduced IPA space

- a memory slot that was accepted because it did fit the default
  IPA space but didn't fit the HW constraints is now properly
  rejected

The other thing that's left doing is to convince userspace to
actually use the IPA space setting instead of relying on the
antiquated default.

Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 Documentation/virt/kvm/api.rst | 13 +++++++------
 arch/arm64/kvm/reset.c         | 12 ++++++++----
 2 files changed, 15 insertions(+), 10 deletions(-)

```
#### [kvm-unit-tests GIT PULL 01/16] lib/s390x/sclp: Clarify that the CPUEntry array could be at a different spot
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 12122499
Return-Path: <SRS0=plzI=IG=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B1DC9C43333
	for <kvm@archiver.kernel.org>; Mon,  8 Mar 2021 14:34:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9B84265201
	for <kvm@archiver.kernel.org>; Mon,  8 Mar 2021 14:34:25 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230125AbhCHOdy (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 8 Mar 2021 09:33:54 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:6048 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S229697AbhCHOdn (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 8 Mar 2021 09:33:43 -0500
Received: from pps.filterd (m0098419.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 128EWm8m160963;
        Mon, 8 Mar 2021 09:33:42 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=ZbIWr2J5ANlQOhmjQRW2nFD7roJ7b7up328UAGygTxM=;
 b=EG779/VFjSWtn9KspTAxo1BnFRuyVYT32+3OgUgqnkKETFW/41VRQOmT4M0HbzWgg5io
 njqyXC+CpurpVAOeWBjxOrymYGgypGxMR2vlwtxb+WsMwKj4Gdq3SSSUPDKoBQfSLevZ
 /3Z7Kq9KWopC8e27Wc/DRTCURyTPjtVv/hxab7K8M8Bk34NIzo+iVI1P0sXM9FJYifI7
 u9lUvxqxNCD52lnqHFdEXSDc4VC62johVpg73Q3AHLiSd0JwB8EAlWAs2yGgPZJuGAMP
 ev7hPxGKi9aU3e0S006T9X8ZbUsiZPnk5Y7+vN4gTlTWu497V6cIunfTFPT44SDT6YVb ZQ==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 375nsk80rh-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 08 Mar 2021 09:33:42 -0500
Received: from m0098419.ppops.net (m0098419.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 128EXgqY167220;
        Mon, 8 Mar 2021 09:33:42 -0500
Received: from ppma02fra.de.ibm.com (47.49.7a9f.ip4.static.sl-reverse.com
 [159.122.73.71])
        by mx0b-001b2d01.pphosted.com with ESMTP id 375nsk80qs-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 08 Mar 2021 09:33:42 -0500
Received: from pps.filterd (ppma02fra.de.ibm.com [127.0.0.1])
        by ppma02fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 128EX56U012033;
        Mon, 8 Mar 2021 14:33:40 GMT
Received: from b06cxnps4076.portsmouth.uk.ibm.com
 (d06relay13.portsmouth.uk.ibm.com [9.149.109.198])
        by ppma02fra.de.ibm.com with ESMTP id 3741c8901x-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 08 Mar 2021 14:33:40 +0000
Received: from d06av23.portsmouth.uk.ibm.com (d06av23.portsmouth.uk.ibm.com
 [9.149.105.59])
        by b06cxnps4076.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 128EXbWT41419044
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 8 Mar 2021 14:33:37 GMT
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 64CB3A404D;
        Mon,  8 Mar 2021 14:33:37 +0000 (GMT)
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 0319CA4040;
        Mon,  8 Mar 2021 14:33:37 +0000 (GMT)
Received: from fedora.fritz.box (unknown [9.145.7.187])
        by d06av23.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Mon,  8 Mar 2021 14:33:36 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: pbonzini@redhat.com
Cc: kvm@vger.kernel.org, frankja@linux.ibm.com, david@redhat.com,
        borntraeger@de.ibm.com, cohuck@redhat.com,
        linux-s390@vger.kernel.org, imbrenda@linux.ibm.com
Subject: [kvm-unit-tests GIT PULL 01/16] lib/s390x/sclp: Clarify that the
 CPUEntry array could be at a different spot
Date: Mon,  8 Mar 2021 15:31:32 +0100
Message-Id: <20210308143147.64755-2-frankja@linux.ibm.com>
X-Mailer: git-send-email 2.29.2
In-Reply-To: <20210308143147.64755-1-frankja@linux.ibm.com>
References: <20210308143147.64755-1-frankja@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.761
 definitions=2021-03-08_08:2021-03-08,2021-03-08 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 adultscore=0 clxscore=1015
 bulkscore=0 spamscore=0 mlxscore=0 mlxlogscore=999 phishscore=0
 impostorscore=0 malwarescore=0 priorityscore=1501 suspectscore=0
 lowpriorityscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2103080080
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Thomas Huth <thuth@redhat.com>

The "struct CPUEntry entries[0]" in the ReadInfo structure is misleading
since the entries could be at a completely different spot. Replace it
by a proper comment instead.

Signed-off-by: Thomas Huth <thuth@redhat.com>
Message-Id: <20210121065703.561444-1-thuth@redhat.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
---
 lib/s390x/sclp.h | 9 +++++++--
 1 file changed, 7 insertions(+), 2 deletions(-)

```
#### [PATCH v8] drivers/misc: sysgenid: add system generation id driver
##### From: Adrian Catangiu <acatan@amazon.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Adrian Catangiu <acatan@amazon.com>
X-Patchwork-Id: 12122469
Return-Path: <SRS0=plzI=IG=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-19.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B6E33C433E6
	for <kvm@archiver.kernel.org>; Mon,  8 Mar 2021 14:19:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6F970651E8
	for <kvm@archiver.kernel.org>; Mon,  8 Mar 2021 14:19:58 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229904AbhCHOT0 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 8 Mar 2021 09:19:26 -0500
Received: from smtp-fw-6002.amazon.com ([52.95.49.90]:8315 "EHLO
        smtp-fw-6002.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229757AbhCHOTB (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 8 Mar 2021 09:19:01 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.com; i=@amazon.com; q=dns/txt; s=amazon201209;
  t=1615213141; x=1646749141;
  h=from:to:cc:subject:date:message-id:mime-version:
   content-transfer-encoding;
  bh=Ljkjbuxz8H4S73rRWSpzlkKHdgWrkOkkYi5xVAvvF5g=;
  b=Ox/i1rypmSsv/FU8T+zWBKWIZDTUzQZwiHfKjsfW28HJbsNFix/PwjJK
   BsmGIIjnEpATCfhaXSaFl1M6B4phgQPz/kNCiBWU6Ws1cqmPg6vbgnwPQ
   PKPnbsWzoJkxeT+d0aFZwuVBQGNBPWw9Liw0KqD/62ovBAc4MXCQysTig
   Y=;
X-IronPort-AV: E=Sophos;i="5.81,232,1610409600";
   d="scan'208";a="95288656"
Received: from iad12-co-svc-p1-lb1-vlan2.amazon.com (HELO
 email-inbound-relay-1d-98acfc19.us-east-1.amazon.com) ([10.43.8.2])
  by smtp-border-fw-out-6002.iad6.amazon.com with ESMTP;
 08 Mar 2021 14:18:53 +0000
Received: from EX13D08EUB004.ant.amazon.com
 (iad12-ws-svc-p26-lb9-vlan3.iad.amazon.com [10.40.163.38])
        by email-inbound-relay-1d-98acfc19.us-east-1.amazon.com (Postfix) with
 ESMTPS id C11EFA1F1F;
        Mon,  8 Mar 2021 14:18:42 +0000 (UTC)
Received: from uf6ed9c851f4556.ant.amazon.com (10.43.162.131) by
 EX13D08EUB004.ant.amazon.com (10.43.166.158) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Mon, 8 Mar 2021 14:18:27 +0000
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
Subject: [PATCH v8] drivers/misc: sysgenid: add system generation id driver
Date: Mon, 8 Mar 2021 16:18:03 +0200
Message-ID: <1615213083-29869-1-git-send-email-acatan@amazon.com>
X-Mailer: git-send-email 2.7.4
MIME-Version: 1.0
X-Originating-IP: [10.43.162.131]
X-ClientProxiedBy: EX13D47UWA003.ant.amazon.com (10.43.163.9) To
 EX13D08EUB004.ant.amazon.com (10.43.166.158)
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

- Background and problem

The System Generation ID feature is required in virtualized or
containerized environments by applications that work with local copies
or caches of world-unique data such as random values, uuids,
monotonically increasing counters, cryptographic nonces, etc.
Such applications can be negatively affected by VM or container
snapshotting when the VM or container is either cloned or returned to
an earlier point in time.

Solving the uniqueness problem strongly enough for cryptographic
purposes requires a mechanism which can deterministically reseed
userspace PRNGs with new entropy at restore time. This mechanism must
also support the high-throughput and low-latency use-cases that led
programmers to pick a userspace PRNG in the first place; be usable by
both application code and libraries; allow transparent retrofitting
behind existing popular PRNG interfaces without changing application
code; it must be efficient, especially on snapshot restore; and be
simple enough for wide adoption.

- Solution

This commit introduces a mechanism that standardizes an API for
applications and libraries to be made aware of uniqueness breaking
events such as VM or container snapshotting, and allow them to react
and adapt to such events.

The System Generation ID is meant to help in these scenarios by
providing a monotonically increasing u32 counter that changes each time
the VM or container is restored from a snapshot.

The `sysgenid` driver exposes a monotonic incremental System Generation
u32 counter via a char-dev filesystem interface accessible
through `/dev/sysgenid`. It provides synchronous and asynchronous SysGen
counter update notifications, as well as counter retrieval and
confirmation mechanisms.
The counter starts from zero when the driver is initialized and
monotonically increments every time the system generation changes.

Userspace applications or libraries can (a)synchronously consume the
system generation counter through the provided filesystem interface, to
make any necessary internal adjustments following a system generation
update.

The provided filesystem interface operations can be used to build a
system level safe workflow that guest software can follow to protect
itself from negative system snapshot effects.

System generation changes are driven by userspace software through a
dedicated driver ioctl.

**Please note**, SysGenID alone does not guarantee complete snapshot
safety to applications using it. A certain workflow needs to be
followed at the system level, in order to make the system
snapshot-resilient. Please see the "Snapshot Safety Prerequisites"
section in the included documentation.

Signed-off-by: Adrian Catangiu <acatan@amazon.com>
---
v7 -> v8:
  - remove vmgenid driver
  - sysgenid: remove support for HW backends, SysGenID is now driven
    by software through a safe, consistent interface
  - without HW backend there is no IRQ to race with mmap() interface
  - update documentation

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
---
 Documentation/misc-devices/sysgenid.rst            | 228 +++++++++++++++
 Documentation/userspace-api/ioctl/ioctl-number.rst |   1 +
 MAINTAINERS                                        |   8 +
 drivers/misc/Kconfig                               |  15 +
 drivers/misc/Makefile                              |   1 +
 drivers/misc/sysgenid.c                            | 316 +++++++++++++++++++++
 include/uapi/linux/sysgenid.h                      |  14 +
 7 files changed, 583 insertions(+)
 create mode 100644 Documentation/misc-devices/sysgenid.rst
 create mode 100644 drivers/misc/sysgenid.c
 create mode 100644 include/uapi/linux/sysgenid.h

diff --git a/Documentation/misc-devices/sysgenid.rst b/Documentation/misc-devices/sysgenid.rst
new file mode 100644
index 0000000..21f748d
--- /dev/null
+++ b/Documentation/misc-devices/sysgenid.rst
@@ -0,0 +1,228 @@
+.. SPDX-License-Identifier: GPL-2.0
+
+========
+SYSGENID
+========
+
+The System Generation ID feature is required in virtualized or
+containerized environments by applications that work with local copies
+or caches of world-unique data such as random values, UUIDs,
+monotonically increasing counters, etc.
+Such applications can be negatively affected by VM or container
+snapshotting when the VM or container is either cloned or returned to
+an earlier point in time.
+
+The System Generation ID device is meant to help in these scenarios by
+providing a system level interface for applications and libraries to
+consume and synchronize against the System Generation ID.
+The SysGenID is a monotonically increasing counter that is meant to
+changes eachtime the system generation changes, for example after a VM
+or container is restored from a snapshot. The driver for it lives at
+``drivers/misc/sysgenid.c``.
+
+The ``sysgenid`` driver exposes a monotonic incremental System
+Generation u32 counter via a char-dev filesystem interface accessible
+through ``/dev/sysgenid`` that provides sync and async SysGen counter
+update notifications. It also provides SysGen counter retrieval and
+confirmation mechanisms.
+
+The counter starts from zero when the driver is initialized and
+monotonically increments every time the system generation changes.
+
+System generation changes are driven by userspace software through a
+dedicated driver ioctl.
+
+Userspace applications or libraries can (a)synchronously consume the
+system generation counter through the provided filesystem interface, to
+make any necessary internal adjustments following a system generation
+update.
+
+**Please note**, SysGenID alone does not guarantee complete snapshot
+safety to applications using it. A certain workflow needs to be
+followed at the system level, in order to make the system
+snapshot-resilient. Please see the "Snapshot Safety Prerequisites"
+section below.
+
+Driver filesystem interface
+===========================
+
+``open()``:
+  When the device is opened, a copy of the current SysGenID (counter)
+  is associated with the open file descriptor. Every open file
+  descriptor will have readable data available (EPOLLIN) while its
+  current copy of the SysGenID is outdated. Reading from the fd will
+  provide the latest SysGenID, while writing to the fd will update the
+  fd-local copy of the SysGenID and is used as a confirmation
+  mechanism.
+
+``read()``:
+  Read is meant to provide the *new* system generation counter when a
+  generation change takes place. The read operation blocks until the
+  associated counter is no longer up to date, at which point the new
+  counter is provided/returned.  Nonblocking ``read()`` returns
+  ``EAGAIN`` to signal that there is no *new* counter value available.
+  The generation counter is considered *new* for each open file
+  descriptor that hasn't confirmed the new value following a generation
+  change. Therefore, once a generation change takes place, all
+  ``read()`` calls will immediately return the new generation counter
+  and will continue to do so until the new value is confirmed back to
+  the driver through ``write()``.
+  Partial reads are not allowed - read buffer needs to be at least
+  32 bits in size.
+
+``write()``:
+  Write is used to confirm the up-to-date SysGenID counter back to the
+  driver.
+  Following a VM generation change, all existing watchers are marked
+  as *outdated*. Each file descriptor will maintain the *outdated*
+  status until a ``write()`` containing the new up-to-date generation
+  counter is used as an update confirmation mechanism.
+  Partial writes are not allowed - write buffer should be exactly
+  32 bits in size.
+
+``poll()``:
+  Poll is implemented to allow polling for generation counter updates.
+  Such updates result in ``EPOLLIN`` polling status until the new
+  up-to-date counter is confirmed back to the driver through a
+  ``write()``.
+
+``ioctl()``:
+  The driver also adds support for waiting on open file descriptors
+  that haven't acknowledged a generation counter update, as well as a
+  mechanism for userspace to *trigger* a generation update:
+
+  - SYSGENID_SET_WATCHER_TRACKING: takes a bool argument to set tracking
+    status for current file descriptor. When watcher tracking is
+    enabled, the driver tracks this file descriptor as an independent
+    *watcher*. The driver keeps accounting of how many watchers have
+    confirmed the latest Sys-Gen-Id counter and how many of them are
+    *outdated*; an outdated watcher is a *tracked* open file descriptor
+    that has lived through a Sys-Gen-Id change but has not yet confirmed
+    the new generation counter.
+    Software that wants to be waited on by the system while it adjusts
+    to generation changes, should turn tracking on. The sysgenid driver
+    then keeps track of it and can block system-level adjustment process
+    until the software has finished adjusting and confirmed it through a
+    ``write()``.
+    Tracking is disabled by default and file descriptors need to
+    explicitly opt-in using this IOCTL.
+  - SYSGENID_WAIT_WATCHERS: blocks until there are no more *outdated*
+    tracked watchers or, if a ``timeout`` argument is provided, until
+    the timeout expires.
+    If the current caller is *outdated* or a generation change happens
+    while waiting (thus making current caller *outdated*), the ioctl
+    returns ``-EINTR`` to signal the user to handle event and retry.
+  - SYSGENID_TRIGGER_GEN_UPDATE: triggers a generation counter increment.
+    It takes a ``minimum-generation`` argument which represents the
+    minimum value the generation counter will be set to. For example if
+    current generation is ``x`` and ``SYSGENID_TRIGGER_GEN_UPDATE(y)``
+    is called, the generation counter will increment to ``MAX(y,x+1)``.
+    This IOCTL can only be used by processes with CAP_CHECKPOINT_RESTORE
+    or CAP_SYS_ADMIN capabilities.
+
+``mmap()``:
+  The driver supports ``PROT_READ, MAP_SHARED`` mmaps of a single page
+  in size. The first 4 bytes of the mapped page will contain an
+  up-to-date u32 copy of the system generation counter.
+  The mapped memory can be used as a low-latency generation counter
+  probe mechanism in critical sections.
+  The mmap() interface is targeted at libraries or code that needs to
+  check for generation changes in-line, where an event loop is not
+  available or read()/write() syscalls are too expensive.
+  In such cases, logic can be added in-line with the sensitive code to
+  check and trigger on-demand/just-in-time readjustments when changes
+  are detected on the memory mapped generation counter.
+  Users of this interface that plan to lazily adjust should not enable
+  watcher tracking, since waiting on them doesn't make sense.
+
+``close()``:
+  Removes the file descriptor as a system generation counter *watcher*.
+
+Snapshot Safety Prerequisites
+=============================
+
+If VM, container or other system-level snapshots happen asynchronously,
+at arbitrary times during an active workload there is no practical way
+to ensure that in-flight local copies or caches of world-unique data
+such as random values, secrets, UUIDs, etc are properly scrubbed and
+regenerated.
+The challenge stems from the fact that the categorization of data as
+snapshot-sensitive is only known to the software working with it, and
+this software has no logical control over the moment in time when an
+external system snapshot occurs.
+
+Let's take an OpenSSL session token for example. Even if the library
+code is made 100% snapshot-safe, meaning the library guarantees that
+the session token is unique (any snapshot that happened during the
+library call did not duplicate or leak the token), the token is still
+vulnerable to snapshot events while it transits the various layers of
+the library caller, then the various layers of the OS before leaving
+the system.
+
+To catch a secret while it's in-flight, we'd have to validate system
+generation at every layer, every step of the way. Even if that would
+be deemed the right solution, it would be a long road and a whole
+universe to patch before we get there.
+
+Bottom line is we don't have a way to track all of these in-flight
+secrets and dynamically scrub them from existence with snapshot
+events happening arbitrarily.
+
+Simplifyng assumption - safety prerequisite
+-------------------------------------------
+
+**Control the snapshot flow**, disallow snapshots coming at arbitrary
+moments in the workload lifetime.
+
+Use a system-level overseer entity that quiesces the system before
+snapshot, and post-snapshot-resume oversees that software components
+have readjusted to new environment, to the new generation. Only after,
+will the overseer un-quiesce the system and allow active workloads.
+
+Software components can choose whether they want to be tracked and
+waited on by the overseer by using the ``SYSGENID_SET_WATCHER_TRACKING``
+IOCTL.
+
+The sysgenid framework standardizes the API for system software to
+find out about needing to readjust and at the same time provides a
+mechanism for the overseer entity to wait for everyone to be done, the
+system to have readjusted, so it can un-quiesce.
+
+Example snapshot-safe workflow
+------------------------------
+
+1) Before taking a snapshot, quiesce the VM/container/system. Exactly
+   how this is achieved is very workload-specific, but the general
+   description is to get all software to an expected state where their
+   event loops dry up and they are effectively quiesced.
+2) Take snapshot.
+3) Resume the VM/container/system from said snapshot.
+4) Overseer will trigger generation bump using
+   ``SYSGENID_TRIGGER_GEN_UPDATE`` IOCLT.
+5) Software components which have ``/dev/sysgenid`` in their event
+   loops (either using ``poll()`` or ``read()``) are notified of the
+   generation change.
+   They do their specific internal adjustments. Some may have requested
+   to be tracked and waited on by the overseer, others might choose to
+   do their adjustments out of band and not block the overseer.
+   Tracked ones *must* signal when they are done/ready with a ``write()``
+   while the rest *should* also do so for cleanliness, but it's not
+   mandatory.
+6) Overseer will block and wait for all tracked watchers by using the
+   ``SYSGENID_WAIT_WATCHERS`` IOCTL. Once all tracked watchers are done
+   in step 5, this overseer will return from this blocking ioctl knowing
+   that the system has readjusted and is ready for active workload.
+7) Overseer un-quiesces system.
+8) There is a class of software, usually libraries, most notably PRNGs
+   or SSLs, that don't fit the event-loop model and also have strict
+   latency requirements. These can take advantage of the ``mmap()``
+   interface and lazily adjust on-demand whenever they are called after
+   un-quiesce.
+   For a well-designed service stack, these libraries should not be
+   called while system is quiesced. When workload is resumed by the
+   overseer, on the first call into these libs, they will safely JIT
+   readjust.
+   Users of this lazy on-demand readjustment model should not enable
+   watcher tracking since doing so would introduce a logical deadlock:
+   lazy adjustments happen only after un-quiesce, but un-quiesce is
+   blocked until all tracked watchers are up-to-date.
```
#### [PATCH V2 1/4] vDPA/ifcvf: get_vendor_id returns a device specific vendor id
##### From: Zhu Lingshan <lingshan.zhu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhu Lingshan <lingshan.zhu@intel.com>
X-Patchwork-Id: 12121771
Return-Path: <SRS0=plzI=IG=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 54F3AC433E6
	for <kvm@archiver.kernel.org>; Mon,  8 Mar 2021 08:41:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2D12B651C3
	for <kvm@archiver.kernel.org>; Mon,  8 Mar 2021 08:41:30 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231629AbhCHIlA (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 8 Mar 2021 03:41:00 -0500
Received: from mga03.intel.com ([134.134.136.65]:40492 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S231793AbhCHIk4 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 8 Mar 2021 03:40:56 -0500
IronPort-SDR: 
 Fh1rKVVCjRwayOg+CIcXzjakuhmSsS+CRYrlMv+dprL4YOeyBHbUJmA0+uTdZdWw32BYSxBuI4
 A9hECJXwBwYQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9916"; a="188041992"
X-IronPort-AV: E=Sophos;i="5.81,232,1610438400";
   d="scan'208";a="188041992"
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by orsmga103.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 08 Mar 2021 00:40:53 -0800
IronPort-SDR: 
 fbjU80Wk7p4LMwQS/SuXMdGxXRYRoiNL0xim2NGxWGi9raFKzzit0u0/RXJ+llK6R4torCfREr
 9jsW/BosW2PA==
X-IronPort-AV: E=Sophos;i="5.81,232,1610438400";
   d="scan'208";a="508855638"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.240.193.73])
  by fmsmga001-auth.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 08 Mar 2021 00:40:51 -0800
From: Zhu Lingshan <lingshan.zhu@intel.com>
To: jasowang@redhat.com, mst@redhat.com, lulu@redhat.com
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Zhu Lingshan <lingshan.zhu@intel.com>
Subject: [PATCH V2 1/4] vDPA/ifcvf: get_vendor_id returns a device specific
 vendor id
Date: Mon,  8 Mar 2021 16:35:22 +0800
Message-Id: <20210308083525.382514-2-lingshan.zhu@intel.com>
X-Mailer: git-send-email 2.27.0
In-Reply-To: <20210308083525.382514-1-lingshan.zhu@intel.com>
References: <20210308083525.382514-1-lingshan.zhu@intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In this commit, ifcvf_get_vendor_id() will return
a device specific vendor id of the probed pci device
than a hard code.

Signed-off-by: Zhu Lingshan <lingshan.zhu@intel.com>
---
 drivers/vdpa/ifcvf/ifcvf_main.c | 5 ++++-
 1 file changed, 4 insertions(+), 1 deletion(-)

```
#### [PATCH v1 01/14] vfio: Create vfio_fs_type with inode per deviceFrom: Alex Williamson <alex.williamson@redhat.com>
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alex Williamson <alex.williamson@redhat.com>
X-Patchwork-Id: 12123431
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 72934C433DB
	for <kvm@archiver.kernel.org>; Mon,  8 Mar 2021 21:48:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 449C8651B7
	for <kvm@archiver.kernel.org>; Mon,  8 Mar 2021 21:48:16 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229978AbhCHVrn (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 8 Mar 2021 16:47:43 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:32870 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S230047AbhCHVri (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 8 Mar 2021 16:47:38 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1615240058;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=5qWQV30xEvYhKMl4+qKvr7XLbSB144DLEcjcsYdfp1w=;
        b=aKL/06AqfWoo7gZz3xgFB1TlWfKyjccm94N1u9nu6aXOrA8Kn4BT9cwUegMJBOuuTrmBMO
        pDbXYW466Ex7BCXNff5sNFC0V69Ymun6ko8yD6PQaArpBkMyNtkhvDlf22I3Ap7PvkbJDe
        fDw/UMjAh+8j9ahLf3Gxjtm17K9ST/g=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-47-HSiE92j2N1GDfXZoE6nETg-1; Mon, 08 Mar 2021 16:47:36 -0500
X-MC-Unique: HSiE92j2N1GDfXZoE6nETg-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 7958B1005D4A;
        Mon,  8 Mar 2021 21:47:35 +0000 (UTC)
Received: from gimli.home (ovpn-112-255.phx2.redhat.com [10.3.112.255])
        by smtp.corp.redhat.com (Postfix) with ESMTP id A06941A878;
        Mon,  8 Mar 2021 21:47:28 +0000 (UTC)
Subject: [PATCH v1 01/14] vfio: Create vfio_fs_type with inode per device
From: Alex Williamson <alex.williamson@redhat.com>
To: alex.williamson@redhat.com
Cc: cohuck@redhat.com, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, jgg@nvidia.com, peterx@redhat.com
Date: Mon, 08 Mar 2021 14:47:28 -0700
Message-ID: <161524004828.3480.1817334832614722574.stgit@gimli.home>
In-Reply-To: <161523878883.3480.12103845207889888280.stgit@gimli.home>
References: <161523878883.3480.12103845207889888280.stgit@gimli.home>
User-Agent: StGit/0.21-2-g8ef5
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

By linking all the device fds we provide to userspace to an
address space through a new pseudo fs, we can use tools like
unmap_mapping_range() to zap all vmas associated with a device.

Suggested-by: Jason Gunthorpe <jgg@nvidia.com>
Signed-off-by: Alex Williamson <alex.williamson@redhat.com>
---
 drivers/vfio/vfio.c |   54 +++++++++++++++++++++++++++++++++++++++++++++++++++
 1 file changed, 54 insertions(+)

```
#### [PATCH] vfio/pci: make the vfio_pci_mmap_fault reentrant
##### From: Zeng Tao <prime.zeng@hisilicon.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zeng Tao <prime.zeng@hisilicon.com>
X-Patchwork-Id: 12122007
Return-Path: <SRS0=plzI=IG=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id EE340C433E0
	for <kvm@archiver.kernel.org>; Mon,  8 Mar 2021 11:17:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 89A47650F2
	for <kvm@archiver.kernel.org>; Mon,  8 Mar 2021 11:17:58 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231657AbhCHLRZ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 8 Mar 2021 06:17:25 -0500
Received: from szxga05-in.huawei.com ([45.249.212.191]:13071 "EHLO
        szxga05-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S231633AbhCHLRT (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 8 Mar 2021 06:17:19 -0500
Received: from DGGEMS406-HUB.china.huawei.com (unknown [172.30.72.58])
        by szxga05-in.huawei.com (SkyGuard) with ESMTP id 4DvG2t2cX8zMkKk;
        Mon,  8 Mar 2021 19:15:02 +0800 (CST)
Received: from localhost.localdomain (10.67.165.24) by
 DGGEMS406-HUB.china.huawei.com (10.3.19.206) with Microsoft SMTP Server id
 14.3.498.0; Mon, 8 Mar 2021 19:17:10 +0800
From: Zeng Tao <prime.zeng@hisilicon.com>
To: <alex.williamson@redhat.com>
CC: <linuxarm@huawei.com>, Zeng Tao <prime.zeng@hisilicon.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Kevin Tian <kevin.tian@intel.com>,
        Andrew Morton <akpm@linux-foundation.org>,
        Peter Xu <peterx@redhat.com>,
        Giovanni Cabiddu <giovanni.cabiddu@intel.com>,
        Michel Lespinasse <walken@google.com>,
        "Jann Horn" <jannh@google.com>,
        Max Gurtovoy <mgurtovoy@nvidia.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>
Subject: [PATCH] vfio/pci: make the vfio_pci_mmap_fault reentrant
Date: Mon, 8 Mar 2021 19:11:26 +0800
Message-ID: <1615201890-887-1-git-send-email-prime.zeng@hisilicon.com>
X-Mailer: git-send-email 2.8.1
MIME-Version: 1.0
X-Originating-IP: [10.67.165.24]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We have met the following error when test with DPDK testpmd:
[ 1591.733256] kernel BUG at mm/memory.c:2177!
[ 1591.739515] Internal error: Oops - BUG: 0 [#1] PREEMPT SMP
[ 1591.747381] Modules linked in: vfio_iommu_type1 vfio_pci vfio_virqfd vfio pv680_mii(O)
[ 1591.760536] CPU: 2 PID: 227 Comm: lcore-worker-2 Tainted: G O 5.11.0-rc3+ #1
[ 1591.770735] Hardware name:  , BIOS HixxxxFPGA 1P B600 V121-1
[ 1591.778872] pstate: 40400009 (nZcv daif +PAN -UAO -TCO BTYPE=--)
[ 1591.786134] pc : remap_pfn_range+0x214/0x340
[ 1591.793564] lr : remap_pfn_range+0x1b8/0x340
[ 1591.799117] sp : ffff80001068bbd0
[ 1591.803476] x29: ffff80001068bbd0 x28: 0000042eff6f0000
[ 1591.810404] x27: 0000001100910000 x26: 0000001300910000
[ 1591.817457] x25: 0068000000000fd3 x24: ffffa92f1338e358
[ 1591.825144] x23: 0000001140000000 x22: 0000000000000041
[ 1591.832506] x21: 0000001300910000 x20: ffffa92f141a4000
[ 1591.839520] x19: 0000001100a00000 x18: 0000000000000000
[ 1591.846108] x17: 0000000000000000 x16: ffffa92f11844540
[ 1591.853570] x15: 0000000000000000 x14: 0000000000000000
[ 1591.860768] x13: fffffc0000000000 x12: 0000000000000880
[ 1591.868053] x11: ffff0821bf3d01d0 x10: ffff5ef2abd89000
[ 1591.875932] x9 : ffffa92f12ab0064 x8 : ffffa92f136471c0
[ 1591.883208] x7 : 0000001140910000 x6 : 0000000200000000
[ 1591.890177] x5 : 0000000000000001 x4 : 0000000000000001
[ 1591.896656] x3 : 0000000000000000 x2 : 0168044000000fd3
[ 1591.903215] x1 : ffff082126261880 x0 : fffffc2084989868
[ 1591.910234] Call trace:
[ 1591.914837]  remap_pfn_range+0x214/0x340
[ 1591.921765]  vfio_pci_mmap_fault+0xac/0x130 [vfio_pci]
[ 1591.931200]  __do_fault+0x44/0x12c
[ 1591.937031]  handle_mm_fault+0xcc8/0x1230
[ 1591.942475]  do_page_fault+0x16c/0x484
[ 1591.948635]  do_translation_fault+0xbc/0xd8
[ 1591.954171]  do_mem_abort+0x4c/0xc0
[ 1591.960316]  el0_da+0x40/0x80
[ 1591.965585]  el0_sync_handler+0x168/0x1b0
[ 1591.971608]  el0_sync+0x174/0x180
[ 1591.978312] Code: eb1b027f 540000c0 f9400022 b4fffe02 (d4210000)

The cause is that the vfio_pci_mmap_fault function is not reentrant, if
multiple threads access the same address which will lead to a page fault
at the same time, we will have the above error.

Fix the issue by making the vfio_pci_mmap_fault reentrant, and there is
another issue that when the io_remap_pfn_range fails, we need to undo
the __vfio_pci_add_vma, fix it by moving the __vfio_pci_add_vma down
after the io_remap_pfn_range.

Fixes: 11c4cd07ba11 ("vfio-pci: Fault mmaps to enable vma tracking")
Signed-off-by: Zeng Tao <prime.zeng@hisilicon.com>
---
 drivers/vfio/pci/vfio_pci.c | 14 ++++++++++----
 1 file changed, 10 insertions(+), 4 deletions(-)

```
#### [PATCH] vfio/type1: fix vaddr_get_pfns() return in vfio_pin_page_external()
##### From: Daniel Jordan <daniel.m.jordan@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Daniel Jordan <daniel.m.jordan@oracle.com>
X-Patchwork-Id: 12123067
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 46794C433E9
	for <kvm@archiver.kernel.org>; Mon,  8 Mar 2021 17:26:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 106386528B
	for <kvm@archiver.kernel.org>; Mon,  8 Mar 2021 17:26:05 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230373AbhCHRZd (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 8 Mar 2021 12:25:33 -0500
Received: from userp2120.oracle.com ([156.151.31.85]:39670 "EHLO
        userp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S230512AbhCHRZL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 8 Mar 2021 12:25:11 -0500
Received: from pps.filterd (userp2120.oracle.com [127.0.0.1])
        by userp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 128HJAvF040345;
        Mon, 8 Mar 2021 17:25:08 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : content-transfer-encoding : content-type :
 mime-version; s=corp-2020-01-29;
 bh=63QGh+BrI11sMRz5cCZ1Avt7DW6pw/kd4kO2jw1o/cI=;
 b=UWX5f3/wusKPsvvDcGzAOuj+bcHacrWnBACbMUtc+fJprvth3SGLDLZTxgCBivRJk9uP
 xE2shCw+YIO1um7xOOaauDT+sx4ZZg1GC88eOR6kVGQ/iwas5pCGDJwMsCIEpYqMl1m/
 7+nnjJm9Ts/vy45z3r6HNue4rcpWSZywAODWhmtZuGq6Okd2gjygpOtDcg5WtQv77nvU
 7txyNoA7+dzTJd7252jLtkSadIyXxu/aRqas/QHYtOfjcVg8ATidmVqI9p3pEipdla6B
 42WQW7gj8FRrnIUFPM65kBdoo2VFij3p01DzCdtcjwxtTa7WBDLXZFB7bKEjpOs7e/zR zg==
Received: from aserp3030.oracle.com (aserp3030.oracle.com [141.146.126.71])
        by userp2120.oracle.com with ESMTP id 3742cn4cps-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 08 Mar 2021 17:25:08 +0000
Received: from pps.filterd (aserp3030.oracle.com [127.0.0.1])
        by aserp3030.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 128HLOnc138608;
        Mon, 8 Mar 2021 17:25:07 GMT
Received: from nam12-bn8-obe.outbound.protection.outlook.com
 (mail-bn8nam12lp2173.outbound.protection.outlook.com [104.47.55.173])
        by aserp3030.oracle.com with ESMTP id 374kamh1vs-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 08 Mar 2021 17:25:07 +0000
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=hKCLU+6//r5+BzbKk/vbdsrlsHBx25HUIsgzlvwMXoCDxa7Dz4JM/TF9rHCw5K7TDrL5s8hZynCFBEjq7WzBAwgRJwp/ZO4RXIeSAOQ+RSv4Rd2yEIN4NYxt2zWRH5KXWBc/mm+8pAblLGl4TguAHe4OzIHa5m5ADbg9+9LvCHf+JdZskp4GiSdgwMnX/PBP6KhnIVj166aSi9+saPeTcXS28uzkTqyI4WRDrf35Mj8vMzl/QHJN1OM1v9ssE+A18wxUZwSORye6Hcimlxy+on66BXsSSXtt31e4QMqSdiTjHtKVbM2rZ+kPNDFe//51SnCHpDAnqzPS1BuPKepiUw==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=63QGh+BrI11sMRz5cCZ1Avt7DW6pw/kd4kO2jw1o/cI=;
 b=TirXu4ZjcKQRGHKj/p8bA7gUYz77sinHzZLX1s6OZHuf8wriv3UWz1SDKT6lD9q3Ai3HB/bZEMu32lK+nsCqKwSSYSR54hh15eWYupcO1xcInYVI0tdappd7ksDB56oLdL4DQAmtyHtXcE8a8qOVRdfncE/cD7FDVZjvm0EOEcJWwf/C35fjtvj2tdEZbc3+mpz2R+4vtDzbS5O5fJ6E4vLRuFAaZceYtPwlNbp8aIutWcWXw/lEg/b4LdbmY7j2BEmnT8Rr499iEwHFUTpaXgoT0wgQS+zw+xsctHVCFc2KlH11ucZOmmYVS4A9YVtZ40IywVTg5gBQiwzTJoNYIA==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=oracle.com; dmarc=pass action=none header.from=oracle.com;
 dkim=pass header.d=oracle.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=oracle.onmicrosoft.com; s=selector2-oracle-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=63QGh+BrI11sMRz5cCZ1Avt7DW6pw/kd4kO2jw1o/cI=;
 b=u19gccwyTXH5XUysSiYXzxr2JbBwp83ShZM0Y9fuH+aHItiPzJuh3fAzHrS+JW1ygz1UoFWqEr61yNE7OseNaQUu4h1mhgbweI790r4k1tdQ1rc5iKRs38JW8GGVcmjIqBDHoYX0VdiwYMeGOpHHR3TtzXTPL8Ju3nlRCwZILi0=
Authentication-Results: redhat.com; dkim=none (message not signed)
 header.d=none;redhat.com; dmarc=none action=none header.from=oracle.com;
Received: from MWHPR10MB1774.namprd10.prod.outlook.com (2603:10b6:301:9::13)
 by MWHPR10MB1663.namprd10.prod.outlook.com (2603:10b6:301:7::18) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3912.17; Mon, 8 Mar
 2021 17:25:04 +0000
Received: from MWHPR10MB1774.namprd10.prod.outlook.com
 ([fe80::24eb:1300:dd70:4183]) by MWHPR10MB1774.namprd10.prod.outlook.com
 ([fe80::24eb:1300:dd70:4183%3]) with mapi id 15.20.3890.038; Mon, 8 Mar 2021
 17:25:04 +0000
From: Daniel Jordan <daniel.m.jordan@oracle.com>
To: Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Daniel Jordan <daniel.m.jordan@oracle.com>
Subject: [PATCH] vfio/type1: fix vaddr_get_pfns() return in
 vfio_pin_page_external()
Date: Mon,  8 Mar 2021 12:24:52 -0500
Message-Id: <20210308172452.38864-1-daniel.m.jordan@oracle.com>
X-Mailer: git-send-email 2.30.1
X-Originating-IP: [98.229.125.203]
X-ClientProxiedBy: MN2PR02CA0010.namprd02.prod.outlook.com
 (2603:10b6:208:fc::23) To MWHPR10MB1774.namprd10.prod.outlook.com
 (2603:10b6:301:9::13)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from localhost.localdomain (98.229.125.203) by
 MN2PR02CA0010.namprd02.prod.outlook.com (2603:10b6:208:fc::23) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3912.17 via Frontend
 Transport; Mon, 8 Mar 2021 17:25:03 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 223c7d56-ce17-44ab-6be3-08d8e2571ca2
X-MS-TrafficTypeDiagnostic: MWHPR10MB1663:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <MWHPR10MB166310CDC4C0754EFCEA74ADD9939@MWHPR10MB1663.namprd10.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:935;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 7dIKuLrfeShtBGfKpeJ6cXhLfM7VRqHNV18vgkW84M/aZfFFvVn4q+/lRyoMoyoOEEMhOMsXccNhelx9ksoJzKadaG5NzrzIAJjhWzkyhh7R435/sU1c/DjjDn0PPTAub6LM47Ji5w4G8/XJwDcxvtUSep9F+Nb6bfQCYwYHR5Ci2SfvS7wGPRd8s2LkdlrT1dwpVedN8ISvl9PyFS/D6ysX24H+U8tmtaQPs0ZN3l6U8Si1cUgaxwHzsPGED953Bb+ZteuSUGYwDAPHPCfcOEf8ruQ3PxypxIALpIiilR8Ck6smdCSCqI1vhuPTel5iQsmR12Q9c98mo0Rxl/2xzD/A0V2avDDwYTYx1tV+eJ/b9+sr8OvbNqwiSgaAQ8l7epaj8ieVJTm4ve8F1GwRu54I5T6Vshtr3fH73T8folCcMk0ewTYJtLRqSpGdbM+70Gqzk7iHqHYKfilxNCag3BJsTOFpY+eGpLeWnL3JwuIogCJb3H0YIe8h4kw+WSIYLN3uu4KviIqsjNp/A+15Vi6wfxwTjBEU59Xdnh9n9a3QBvaqVQsHaQS0+LZJKj6kPszaLP0d5e0RU7OfFUo1eA==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:MWHPR10MB1774.namprd10.prod.outlook.com;PTR:;CAT:NONE;SFS:(346002)(136003)(39860400002)(376002)(366004)(396003)(103116003)(956004)(2616005)(478600001)(5660300002)(6512007)(26005)(4326008)(69590400012)(52116002)(1076003)(66946007)(186003)(83380400001)(316002)(6486002)(16526019)(6666004)(66476007)(107886003)(8936002)(36756003)(8676002)(110136005)(2906002)(6506007)(66556008)(86362001);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 ErWwq4rz8/A/y1jnRNy/Ay0ijHnH11f2osdRc30k59UQPFstRYgvorUrYZIz8Ckzb3/13JDm5RYwJNikK7rQ/OolYkZFeWW1t/4YZoRAaDYTwrTd8Ouz+RS1lB2VtQQ4UaOX9Ghxxlx5D56eKYselzy4Mvn99N0NTJqonx1TeJx9gk6GJLeRPM8CVuDFuuO8fp5NzmZH5M5OoUlzGvYCGv8G8Oc8CXe9aOvXy9uw9ee2GBR+RTe9VUO673gi5Sm2A0BSNvugd5fdhhSQuM7ydPFHT4N8fBHwSr0UwWOuR1ZytBSg88Dv++i5AmESIP4iA7uIISJ2DFvU7pt7/qo6g/AVuNGwF0R0lPLdNxEYfSRJR9bRLwD5+QkYs1jrs9vp6dGDnYaJAzMe8NDmNWVb02fime1YfT0SZUJPsQKvLYBF2nSXkRpoN+GlkNh2RQt9t6SUdOHgobC7yz5hZy2QXcshIw0NVta7I0VWn/j+aK8OPosI5wFK9Qy9Xi01GblYAhnw17J02rUelEsqdBpjgBJnAENYQPh3zyd1FFtJjze7enycsWxQhjrxapJwbCy6D+s/e9ypM2UDH5FB9fT0W2ipTblawYj1yzDLNmj92NJ0at86cXBAg6etBrgpFQ/F2E58a4iWqoRG3LVFpQGCSZHS3RNGHnO6vZBCiG5luXbp8uBH688hPByWfVdyi8b2h/Fux9r82jsLUyYC8zEdIzMZbHPBfH7ApNJZUJdvaN/A0lchqgcTOApJubdGa8B4roUNAqG3A9X94kDag62nEHClJcvx7KD+/y/j2E+xeuYtQBAWNepoU+mJmdXRzWRklbWFhNEV/gK6Yb4ODoVNsCcW3WxxaQeX1Ke2q5eMHE08zJR7wvv2X4NrYQkoaB4QEc82OrcPyYqKvgpesZ8CnqJL5Zb7DrBhMnw3pGeJbAEsILs65aEoKXcDyqeJevDMIbPxZJobKm/dTMRYFVT1sptHoHQgebYVpSUv/cJaqTLVsLPb5+hp+JYU1FsOYG7iGxNNBV6xdc4GHEtGc5Wdt+MoYmefEsRh/1OLMwYSwSBibd1XZObJ7EG3rKrD8yZN3QzKnLczCW/JVrzobW4WLrAMHv9+ZcFefvesjP0eaaWrLvTw+/L+aahTSEE94+u0Cqx9B6sAVf7vBM+Rng6HkVSS6JnhoHB2Q/zyIq3le/9vZEYaUoa8s3Fvg8gouYYXQ2kuIjN6utXfNe1jO/YRUVKJ44TC/8kxeP3uN1CJD8azvzOp9B+J2XBlX2RB+HgqV82bjfoQXqOvb0sbxUzJuPHqSxPulGdH01Py04xZc2JO5WuIUya2Lg6qKJl/q8ci
X-OriginatorOrg: oracle.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 223c7d56-ce17-44ab-6be3-08d8e2571ca2
X-MS-Exchange-CrossTenant-AuthSource: MWHPR10MB1774.namprd10.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 08 Mar 2021 17:25:04.5332
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 4e2c6054-71cb-48f1-bd6c-3a9705aca71b
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 A3chzYMhkPWyTWOKxsZWa/KKnpNJcu2nytW3g5BKZWIfEgx4ONS/SGZldpCEQlxtdr0B3Ye9+qXXatNm94/5CNY8sa4ZmXaH9OR9+6tSVT8=
X-MS-Exchange-Transport-CrossTenantHeadersStamped: MWHPR10MB1663
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9917
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 mlxlogscore=999
 suspectscore=0
 spamscore=0 phishscore=0 bulkscore=0 malwarescore=0 adultscore=0
 mlxscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2103080092
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9917
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 spamscore=0
 suspectscore=0
 clxscore=1015 phishscore=0 adultscore=0 mlxlogscore=999 priorityscore=1501
 lowpriorityscore=0 bulkscore=0 mlxscore=0 impostorscore=0 malwarescore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2103080092
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

vaddr_get_pfns() now returns the positive number of pfns successfully
gotten instead of zero.  vfio_pin_page_external() might return 1 to
vfio_iommu_type1_pin_pages(), which will treat it as an error, if
vaddr_get_pfns() is successful but vfio_pin_page_external() doesn't
reach vfio_lock_acct().

Fix it up in vfio_pin_page_external().  Found by inspection.

Fixes: be16c1fd99f4 ("vfio/type1: Change success value of vaddr_get_pfn()")
Signed-off-by: Daniel Jordan <daniel.m.jordan@oracle.com>
---

I couldn't test this due to lack of hardware.

 drivers/vfio/vfio_iommu_type1.c | 8 +++++++-
 1 file changed, 7 insertions(+), 1 deletion(-)


base-commit: 144c79ef33536b4ecb4951e07dbc1f2b7fa99d32

```
#### [PATCH v5 02/12] x86/paravirt: switch time pvops functions to use static_call()
##### From: Juergen Gross <jgross@suse.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Juergen Gross <jgross@suse.com>
X-Patchwork-Id: 12122169
Return-Path: <SRS0=plzI=IG=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 5C30EC433E6
	for <kvm@archiver.kernel.org>; Mon,  8 Mar 2021 12:29:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 25836651D1
	for <kvm@archiver.kernel.org>; Mon,  8 Mar 2021 12:29:57 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230327AbhCHM3Y (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 8 Mar 2021 07:29:24 -0500
Received: from mx2.suse.de ([195.135.220.15]:40308 "EHLO mx2.suse.de"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229757AbhCHM2w (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 8 Mar 2021 07:28:52 -0500
X-Virus-Scanned: by amavisd-new at test-mx.suse.de
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=suse.com; s=susede1;
        t=1615206530;
 h=from:from:reply-to:date:date:message-id:message-id:to:to:cc:cc:
         mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=J66CWuwKwfzFPvCq/m8D63U++K/o7dDSv22aN/eKP7M=;
        b=cIXiUqxf03980MHxBeIJz7vODEC6tQtd6/lUgwJufF8vAwaGi1A80YufivneEt5GZP/2E8
        v70lIPnIEGXuQi2CqELG40DuUwx+olazP2WTKu8piVPTmYHrvFbzH5GBP7rz87skFklWM4
        RZyo17tov8ZR5dCZ9W3sgwYURK9c2HU=
Received: from relay2.suse.de (unknown [195.135.221.27])
        by mx2.suse.de (Postfix) with ESMTP id 9F935AD74;
        Mon,  8 Mar 2021 12:28:50 +0000 (UTC)
From: Juergen Gross <jgross@suse.com>
To: xen-devel@lists.xenproject.org, x86@kernel.org,
        virtualization@lists.linux-foundation.org,
        linux-arm-kernel@lists.infradead.org, linux-kernel@vger.kernel.org,
        linux-hyperv@vger.kernel.org, kvm@vger.kernel.org
Cc: Juergen Gross <jgross@suse.com>, Deep Shah <sdeep@vmware.com>,
        "VMware, Inc." <pv-drivers@vmware.com>,
        Russell King <linux@armlinux.org.uk>,
        Catalin Marinas <catalin.marinas@arm.com>,
        Will Deacon <will@kernel.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        "H. Peter Anvin" <hpa@zytor.com>,
        "K. Y. Srinivasan" <kys@microsoft.com>,
        Haiyang Zhang <haiyangz@microsoft.com>,
        Stephen Hemminger <sthemmin@microsoft.com>,
        Wei Liu <wei.liu@kernel.org>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Boris Ostrovsky <boris.ostrovsky@oracle.com>,
        Stefano Stabellini <sstabellini@kernel.org>
Subject: [PATCH v5 02/12] x86/paravirt: switch time pvops functions to use
 static_call()
Date: Mon,  8 Mar 2021 13:28:34 +0100
Message-Id: <20210308122844.30488-3-jgross@suse.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20210308122844.30488-1-jgross@suse.com>
References: <20210308122844.30488-1-jgross@suse.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The time pvops functions are the only ones left which might be
used in 32-bit mode and which return a 64-bit value.

Switch them to use the static_call() mechanism instead of pvops, as
this allows quite some simplification of the pvops implementation.

Signed-off-by: Juergen Gross <jgross@suse.com>
---
V4:
- drop paravirt_time.h again
- don't move Hyper-V code (Michael Kelley)
V5:
- drop no longer needed Hyper-V modification (Michael Kelley)
- switch Arm and Arm64 to static_call(), too (kernel test robot)
---
 arch/arm/include/asm/paravirt.h       | 14 +++++---------
 arch/arm/kernel/paravirt.c            |  9 +++++++--
 arch/arm64/include/asm/paravirt.h     | 14 +++++---------
 arch/arm64/kernel/paravirt.c          | 13 +++++++++----
 arch/x86/Kconfig                      |  1 +
 arch/x86/include/asm/mshyperv.h       |  2 +-
 arch/x86/include/asm/paravirt.h       | 17 ++++++++++++++---
 arch/x86/include/asm/paravirt_types.h |  6 ------
 arch/x86/kernel/cpu/vmware.c          |  5 +++--
 arch/x86/kernel/kvm.c                 |  2 +-
 arch/x86/kernel/kvmclock.c            |  2 +-
 arch/x86/kernel/paravirt.c            | 16 ++++++++++++----
 arch/x86/kernel/tsc.c                 |  2 +-
 arch/x86/xen/time.c                   | 11 ++++-------
 drivers/xen/time.c                    |  3 ++-
 15 files changed, 66 insertions(+), 51 deletions(-)

```
