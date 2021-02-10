#### [PATCH v1 7/9] memory: introduce RAM_NORESERVE and wire it up in qemu_ram_mmap()
##### From: David Hildenbrand <david@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Hildenbrand <david@redhat.com>
X-Patchwork-Id: 12078279
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.3 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 830C0C433DB
	for <kvm@archiver.kernel.org>; Tue,  9 Feb 2021 13:54:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 236ED64EE1
	for <kvm@archiver.kernel.org>; Tue,  9 Feb 2021 13:54:07 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231493AbhBINxo (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 9 Feb 2021 08:53:44 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:51405 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S231917AbhBINwn (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 9 Feb 2021 08:52:43 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1612878674;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=DSC+DaYYuNXaSIgv/N4tLqFp76dpt9unEBb9rwztZq8=;
        b=e5jjk9S0jmRTEekzk6KeFvyGFvDTSKTmsTXX6pD6bzoPeWYjjDfsF70Eijr/lz5D4PZr5V
        v7Pp9zFCatomlwGCQ9qUcy8nGKA9Avq1pVuWTeC8wbOivsqilxpXdHig75PjbZVicGbVsZ
        ldndG4oLxXhJzSSFfYYkoO7bO7mAxa0=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-551-GUswmeVLPOSPxi-k34Qmpw-1; Tue, 09 Feb 2021 08:51:12 -0500
X-MC-Unique: GUswmeVLPOSPxi-k34Qmpw-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 8C281195D571;
        Tue,  9 Feb 2021 13:51:10 +0000 (UTC)
Received: from t480s.redhat.com (ovpn-113-141.ams2.redhat.com [10.36.113.141])
        by smtp.corp.redhat.com (Postfix) with ESMTP id D31696FEED;
        Tue,  9 Feb 2021 13:50:56 +0000 (UTC)
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
 Christian Borntraeger <borntraeger@de.ibm.com>,
 Cornelia Huck <cohuck@redhat.com>, Halil Pasic <pasic@linux.ibm.com>,
 Igor Kotrasinski <i.kotrasinsk@partner.samsung.com>,
 Juan Quintela <quintela@redhat.com>, Stefan Weil <sw@weilnetz.de>,
 Thomas Huth <thuth@redhat.com>, kvm@vger.kernel.org, qemu-s390x@nongnu.org
Subject: [PATCH v1 7/9] memory: introduce RAM_NORESERVE and wire it up in
 qemu_ram_mmap()
Date: Tue,  9 Feb 2021 14:49:37 +0100
Message-Id: <20210209134939.13083-8-david@redhat.com>
In-Reply-To: <20210209134939.13083-1-david@redhat.com>
References: <20210209134939.13083-1-david@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
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
 include/qemu/mmap-alloc.h |  4 +++-
 include/qemu/osdep.h      |  3 ++-
 include/sysemu/kvm.h      |  3 ++-
 migration/ram.c           |  3 +--
 softmmu/physmem.c         | 23 ++++++++++++++++-------
 target/s390x/kvm.c        |  6 +++++-
 util/mmap-alloc.c         |  9 ++++++++-
 util/oslib-posix.c        |  5 +++--
 util/oslib-win32.c        | 13 ++++++++++++-
 12 files changed, 68 insertions(+), 21 deletions(-)

```
#### [PATCH 1/1] s390/vfio-ap: fix circular lockdep when setting/clearing crypto masks
##### From: Tony Krowiak <akrowiak@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tony Krowiak <akrowiak@linux.ibm.com>
X-Patchwork-Id: 12079153
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7A6C6C433E0
	for <kvm@archiver.kernel.org>; Tue,  9 Feb 2021 20:54:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3356264E30
	for <kvm@archiver.kernel.org>; Tue,  9 Feb 2021 20:54:58 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234100AbhBIUxB (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 9 Feb 2021 15:53:01 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:21614 "EHLO
        mx0b-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S233884AbhBIUlN (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 9 Feb 2021 15:41:13 -0500
Received: from pps.filterd (m0127361.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 119JgP6q079175;
        Tue, 9 Feb 2021 14:49:01 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=z8M8GC/vnud9WhkHtY6cAALZNKFHQBkh8OeJZYNyVZg=;
 b=IbfWBSL078+8bQhD9L+d6NIzboZExUvJJip+J5YhLwCUalsdSZnsnP744plJ41AnOkON
 F5agcLQdyMssTF4GvUcMSGEqn+MNOpCbWzDb8+6iHZEE4hroeWz9GHVw5hBJbYpVhjx3
 3XketnJPCyFQVvgpi1q5GbCud9q9QwVSWEDGvgbM6pjJF5+OYTXLulO2JUs2gUeKJbeU
 yTXdHU9Ga62bMOFlT/Cz8C9IazSxDfly333HXRNArvUw6kYmRlMlgbsSdW8vviLcrSzz
 KMnIzbJQeSyu3ZZ4aFqs0Y+zLLDcMS7FRZ+I61uZZWyBtWztXPYPxd9fEIcXPlp6Jw+c 4g==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 36m0smr4r4-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 09 Feb 2021 14:49:01 -0500
Received: from m0127361.ppops.net (m0127361.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 119JgYvt079419;
        Tue, 9 Feb 2021 14:49:01 -0500
Received: from ppma03wdc.us.ibm.com (ba.79.3fa9.ip4.static.sl-reverse.com
 [169.63.121.186])
        by mx0a-001b2d01.pphosted.com with ESMTP id 36m0smr4qy-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 09 Feb 2021 14:49:01 -0500
Received: from pps.filterd (ppma03wdc.us.ibm.com [127.0.0.1])
        by ppma03wdc.us.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 119JhFJI031990;
        Tue, 9 Feb 2021 19:49:00 GMT
Received: from b01cxnp22035.gho.pok.ibm.com (b01cxnp22035.gho.pok.ibm.com
 [9.57.198.25])
        by ppma03wdc.us.ibm.com with ESMTP id 36hjr98x2n-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 09 Feb 2021 19:49:00 +0000
Received: from b01ledav003.gho.pok.ibm.com (b01ledav003.gho.pok.ibm.com
 [9.57.199.108])
        by b01cxnp22035.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id 119Jn07A23331072
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 9 Feb 2021 19:49:00 GMT
Received: from b01ledav003.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 1DAB9B2067;
        Tue,  9 Feb 2021 19:49:00 +0000 (GMT)
Received: from b01ledav003.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 4A502B205F;
        Tue,  9 Feb 2021 19:48:59 +0000 (GMT)
Received: from cpe-66-24-58-13.stny.res.rr.com.com (unknown [9.85.203.235])
        by b01ledav003.gho.pok.ibm.com (Postfix) with ESMTP;
        Tue,  9 Feb 2021 19:48:59 +0000 (GMT)
From: Tony Krowiak <akrowiak@linux.ibm.com>
To: linux-s390@vger.kernel.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org
Cc: stable@vger.kernel.org, borntraeger@de.ibm.com, cohuck@redhat.com,
        kwankhede@nvidia.com, pbonzini@redhat.com,
        alex.williamson@redhat.com, pasic@linux.vnet.ibm.com,
        Tony Krowiak <akrowiak@linux.ibm.com>
Subject: [PATCH 1/1] s390/vfio-ap: fix circular lockdep when setting/clearing
 crypto masks
Date: Tue,  9 Feb 2021 14:48:30 -0500
Message-Id: <20210209194830.20271-2-akrowiak@linux.ibm.com>
X-Mailer: git-send-email 2.21.1
In-Reply-To: <20210209194830.20271-1-akrowiak@linux.ibm.com>
References: <20210209194830.20271-1-akrowiak@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.737
 definitions=2021-02-09_06:2021-02-09,2021-02-09 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 bulkscore=0 spamscore=0
 suspectscore=0 phishscore=0 adultscore=0 mlxscore=0 priorityscore=1501
 malwarescore=0 mlxlogscore=999 impostorscore=0 lowpriorityscore=0
 clxscore=1015 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2102090090
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch fixes a circular locking dependency in the CI introduced by
commit f21916ec4826 ("s390/vfio-ap: clean up vfio_ap resources when KVM
pointer invalidated"). The lockdep only occurs when starting a Secure
Execution guest. Crypto virtualization (vfio_ap) is not yet supported for
SE guests; however, in order to avoid CI errors, this fix is being
provided.

The circular lockdep was introduced when the masks in the guest's APCB
were taken under the matrix_dev->lock. While the lock is definitely
needed to protect the setting/unsetting of the KVM pointer, it is not
necessarily critical for setting the masks, so this will not be done under
protection of the matrix_dev->lock.

Fixes: f21916ec4826 ("s390/vfio-ap: clean up vfio_ap resources when KVM pointer invalidated")
Cc: stable@vger.kernel.org
Signed-off-by: Tony Krowiak <akrowiak@linux.ibm.com>
---
 drivers/s390/crypto/vfio_ap_ops.c | 75 ++++++++++++++++++-------------
 1 file changed, 45 insertions(+), 30 deletions(-)

```
#### [PATCH] KVM: nVMX: Sync L2 guest CET states between L1/L2
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Weijiang <weijiang.yang@intel.com>
X-Patchwork-Id: 12077389
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D4AD3C433E0
	for <kvm@archiver.kernel.org>; Tue,  9 Feb 2021 08:26:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A58C164DEC
	for <kvm@archiver.kernel.org>; Tue,  9 Feb 2021 08:26:15 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229679AbhBII0O (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 9 Feb 2021 03:26:14 -0500
Received: from mga12.intel.com ([192.55.52.136]:9711 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229544AbhBII0O (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 9 Feb 2021 03:26:14 -0500
IronPort-SDR: 
 hIZFTFkXLEx/jHQ/QXpcOvLPe4tHixvgRyGFW3H6xJmXJk63vkqvHL162TACIfPnHVb0/Yv408
 3Rf6c0QKUBgg==
X-IronPort-AV: E=McAfee;i="6000,8403,9889"; a="160999382"
X-IronPort-AV: E=Sophos;i="5.81,164,1610438400";
   d="scan'208";a="160999382"
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by fmsmga106.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 09 Feb 2021 00:25:31 -0800
IronPort-SDR: 
 3GUykSCShpgFEcHg+Ffwgwf+MBbiuf0MYD1n4gte55KB9evjW1o/NfAEXGfASI2O2cwxkgkT+E
 BHfilBx5kmrQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.81,164,1610438400";
   d="scan'208";a="378694156"
Received: from unknown (HELO local-michael-cet-test.sh.intel.com)
 ([10.239.159.166])
  by fmsmga008.fm.intel.com with ESMTP; 09 Feb 2021 00:25:30 -0800
From: Yang Weijiang <weijiang.yang@intel.com>
To: pbonzini@redhat.com, seanjc@google.com, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Cc: Yang Weijiang <weijiang.yang@intel.com>
Subject: [PATCH] KVM: nVMX: Sync L2 guest CET states between L1/L2
Date: Tue,  9 Feb 2021 16:37:08 +0800
Message-Id: <20210209083708.2680-1-weijiang.yang@intel.com>
X-Mailer: git-send-email 2.17.2
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When L2 guest status has been changed by L1 QEMU/KVM, sync the change back
to L2 guest before the later's next vm-entry. On the other hand, if it's
changed due to L2 guest, sync it back so as to let L1 guest see the change.

Signed-off-by: Yang Weijiang <weijiang.yang@intel.com>
Reported-by: kernel test robot <lkp@intel.com>
---
 arch/x86/kvm/vmx/nested.c | 12 ++++++++++++
 1 file changed, 12 insertions(+)

```
#### [kvm-unit-tests PATCH] Fix the length in the stsi check for the VM name
##### From: Thomas Huth <thuth@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Huth <thuth@redhat.com>
X-Patchwork-Id: 12078509
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.3 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C6142C433DB
	for <kvm@archiver.kernel.org>; Tue,  9 Feb 2021 15:58:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 860EC64EB8
	for <kvm@archiver.kernel.org>; Tue,  9 Feb 2021 15:58:57 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232491AbhBIP6l (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 9 Feb 2021 10:58:41 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:51306 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S231654AbhBIP6j (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 9 Feb 2021 10:58:39 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1612886231;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=6SqLbxCHV6DXwffz6T5lMoalH3C/d4xGQ0lUToQcwxQ=;
        b=Z7W/aHEEeJzC8jCJw1eua5HK2V/4xGsxE2S92sLwqwD2Badz/ajqPm8XZqV00pdUs/wBt4
        MiFDm+y8F+pwdSDjYqNOCpDjfwd5EbJbiViCxKRlq5PkQ5Teu73oTZ17Q2L+bXFsAQUjiO
        /hBBH/2e3h97g2JG9v9Tm147Gv7cG6o=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-180-wk5rEMTkO-ePRDX8jgZZ_A-1; Tue, 09 Feb 2021 10:57:10 -0500
X-MC-Unique: wk5rEMTkO-ePRDX8jgZZ_A-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 2A158427CC;
        Tue,  9 Feb 2021 15:57:09 +0000 (UTC)
Received: from thuth.com (ovpn-114-56.ams2.redhat.com [10.36.114.56])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 9330E5D736;
        Tue,  9 Feb 2021 15:57:07 +0000 (UTC)
From: Thomas Huth <thuth@redhat.com>
To: kvm@vger.kernel.org, Janosch Frank <frankja@linux.ibm.com>
Cc: linux-s390@vger.kernel.org, David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>
Subject: [kvm-unit-tests PATCH] Fix the length in the stsi check for the VM
 name
Date: Tue,  9 Feb 2021 16:57:05 +0100
Message-Id: <20210209155705.67601-1-thuth@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

sizeof(somepointer) results in the size of the pointer, i.e. 8 on a
64-bit system, so the

 memcmp(data->ext_names[0], vm_name_ext, sizeof(vm_name_ext))

only compared the first 8 characters of the VM name here. Switch
to a proper array to get the sizeof() right.

Signed-off-by: Thomas Huth <thuth@redhat.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
---
 s390x/stsi.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH] s390x: Workaround smp stop and store status race
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 12078301
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 0DFD2C433DB
	for <kvm@archiver.kernel.org>; Tue,  9 Feb 2021 14:17:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BCB3664E6C
	for <kvm@archiver.kernel.org>; Tue,  9 Feb 2021 14:17:07 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231430AbhBIOQw (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 9 Feb 2021 09:16:52 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:13650 "EHLO
        mx0b-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S231248AbhBIOQu (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 9 Feb 2021 09:16:50 -0500
Received: from pps.filterd (m0127361.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 119ECRZ8073960;
        Tue, 9 Feb 2021 09:16:08 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=1BLAQNPME1uNVq03V27AeKSvoxojAYsbwUoTYsbumY0=;
 b=L1ejIMkyZYnX+JnTtmtLfRu0+JGldv5qL7MFazSDbuJH9J8mPqsSM5FhrZtzbSoPvmGD
 lcH/dd6GBBi2UZRHTWp85leRRLSkmqL2m63DpnJAVal2KFW9wpWZoITHKvA3knY4ebUx
 vNQeyrY79h9VMWoIAzFDFNi4ntN/vKnBE+Vq6k2tzYV29YVx3xglwtBN/S395t2fPWzK
 ijzRRBUBLdlieZRKSVX4Scu1il2e+b7Ojk1FU/QWBZrbcGs1LwOO3uuT7b3XVBLdXw2u
 Jw7d2KIY9g/B5GI+DWahgj+QOXjveEeLsCFbjRcy+NvO89OwVb16jGF6xmuFpkN1s0wS hg==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 36kuxxg2u9-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 09 Feb 2021 09:16:07 -0500
Received: from m0127361.ppops.net (m0127361.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 119ED9q4075680;
        Tue, 9 Feb 2021 09:16:06 -0500
Received: from ppma04ams.nl.ibm.com (63.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.99])
        by mx0a-001b2d01.pphosted.com with ESMTP id 36kuxxg2sy-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 09 Feb 2021 09:16:06 -0500
Received: from pps.filterd (ppma04ams.nl.ibm.com [127.0.0.1])
        by ppma04ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 119E8vAQ021664;
        Tue, 9 Feb 2021 14:16:04 GMT
Received: from b06avi18878370.portsmouth.uk.ibm.com
 (b06avi18878370.portsmouth.uk.ibm.com [9.149.26.194])
        by ppma04ams.nl.ibm.com with ESMTP id 36hjr8bd7m-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 09 Feb 2021 14:16:03 +0000
Received: from d06av22.portsmouth.uk.ibm.com (d06av22.portsmouth.uk.ibm.com
 [9.149.105.58])
        by b06avi18878370.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 119EFpvQ38142286
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 9 Feb 2021 14:15:51 GMT
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id BCD464C040;
        Tue,  9 Feb 2021 14:16:01 +0000 (GMT)
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 286BE4C050;
        Tue,  9 Feb 2021 14:16:01 +0000 (GMT)
Received: from linux01.pok.stglabs.ibm.com (unknown [9.114.17.81])
        by d06av22.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue,  9 Feb 2021 14:16:01 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, david@redhat.com, thuth@redhat.com,
        imbrenda@linux.ibm.com
Subject: [kvm-unit-tests PATCH] s390x: Workaround smp stop and store status
 race
Date: Tue,  9 Feb 2021 09:15:54 -0500
Message-Id: <20210209141554.22554-1-frankja@linux.ibm.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.737
 definitions=2021-02-09_03:2021-02-09,2021-02-09 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxscore=0 clxscore=1015
 bulkscore=0 impostorscore=0 lowpriorityscore=0 mlxlogscore=999
 priorityscore=1501 malwarescore=0 suspectscore=0 phishscore=0 spamscore=0
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2102090068
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

KVM and QEMU handle a SIGP stop and store status in two steps:
1) Stop the CPU by injecting a stop request
2) Store when the CPU has left SIE because of the stop request

The problem is that the SIGP order is already considered completed by
KVM/QEMU when step 1 has been performed and not once both have
completed. In addition we currently don't implement the busy CC so a
kernel has no way of knowing that the store has finished other than
checking the location for the store.

This workaround is based on the fact that for a new SIE entry (via the
added smp restart) a stop with the store status has to be finished
first.

Correct handling of this in KVM/QEMU will need some thought and time.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Tested-by: Thomas Huth <thuth@redhat.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
---
 s390x/smp.c | 5 ++++-
 1 file changed, 4 insertions(+), 1 deletion(-)

```
#### [PATCH] KVM: x86: hyper-v: Fix erroneous 'current_vcpu' usage in kvm_hv_flush_tlb()
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 12077563
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.3 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 0484AC433E0
	for <kvm@archiver.kernel.org>; Tue,  9 Feb 2021 09:12:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BA8E664EB4
	for <kvm@archiver.kernel.org>; Tue,  9 Feb 2021 09:12:36 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230247AbhBIJMU (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 9 Feb 2021 04:12:20 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:46304 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S230469AbhBIJG1 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 9 Feb 2021 04:06:27 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1612861494;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=oAORKjLJ673EprzL/i9GHggWNiC+j4DYLlPEDjDCXoA=;
        b=bq9Ru+eGvWGmKgc957yV70rG2ha7LCPqO7vabYs039ERQF9w2euNS1CLEtAPCmxyXr+K2o
        /aGDjRHelcIsI7jcbTilAI34RgzBW5vUmj97vXGs4ALk8bIGjcKQzEftOd0NHUx96/p4ts
        BswR6zFK13V6KzNpioyxxC+gGLTsdhI=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-593-aUAASB9WNV2VnpmnMKCzVA-1; Tue, 09 Feb 2021 04:04:53 -0500
X-MC-Unique: aUAASB9WNV2VnpmnMKCzVA-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id CC98939397;
        Tue,  9 Feb 2021 09:04:51 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.195.2])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 1372160C04;
        Tue,  9 Feb 2021 09:04:49 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH] KVM: x86: hyper-v: Fix erroneous 'current_vcpu' usage in
 kvm_hv_flush_tlb()
Date: Tue,  9 Feb 2021 10:04:48 +0100
Message-Id: <20210209090448.378472-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Previously, we used to use 'current_vcpu' instead of 'vcpu' in
kvm_hv_flush_tlb() but this is no longer the case, it should clearly
be 'vcpu' here, a mistake was made during rebase.

Reported-by: Maxim Levitsky <mlevitsk@redhat.com>
Fixes: d210b1e5b685 ("KVM: x86: hyper-v: Always use to_hv_vcpu() accessor to get to 'struct kvm_vcpu_hv'"
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
The broken patch is only in kvm/queue atm, we may as well want
to squash the change.
---
 arch/x86/kvm/hyperv.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH v1 1/4] libcflat: add SZ_1M and SZ_2G
##### From: Claudio Imbrenda <imbrenda@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Claudio Imbrenda <imbrenda@linux.ibm.com>
X-Patchwork-Id: 12078369
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id EEC15C433DB
	for <kvm@archiver.kernel.org>; Tue,  9 Feb 2021 14:55:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B234E64EB8
	for <kvm@archiver.kernel.org>; Tue,  9 Feb 2021 14:55:37 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232153AbhBIOzQ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 9 Feb 2021 09:55:16 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:42346 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S232024AbhBIOzL (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 9 Feb 2021 09:55:11 -0500
Received: from pps.filterd (m0098410.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 119EWNlr143174;
        Tue, 9 Feb 2021 09:54:30 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=+FmDDaA5hoHJ6i2g8KzTG8V/MIMxanpp0BjaLySOiYw=;
 b=O+UXUY/kI5DIuDgt4DDnQOCYbtKzIR34OnYPJwypzaGwoojbID+c5TAF4yBw/eb00i6i
 06lhnhocu7aT2P7TrG1KB9qjInxBUcDpJ8qvR/DU1L16pLNKyob4S3Xs7vQbrMJb9wy3
 fB5szmKAe4kBVzRfSUoWgOgovsHUQqpg+K/clSj53O9lmqsOimKj4jm1X2PmrhEkslRn
 jVJ8oert6YZpwTIQlh1Ajx2jnuV9hjgMZeQVppesMnZvTKX/HdSBHflnBj/gEqZ0fNjO
 5NJaYK1DxTGL6yEFncSjMG/59d1nlAoryWd2Aff9VQrNIa2RAzEmkcbLKyN8hfRHmJEI uw==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 36kuh32rqp-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 09 Feb 2021 09:54:30 -0500
Received: from m0098410.ppops.net (m0098410.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 119EYp0n008708;
        Tue, 9 Feb 2021 09:54:30 -0500
Received: from ppma01fra.de.ibm.com (46.49.7a9f.ip4.static.sl-reverse.com
 [159.122.73.70])
        by mx0a-001b2d01.pphosted.com with ESMTP id 36kuh32rnf-3
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 09 Feb 2021 09:54:30 -0500
Received: from pps.filterd (ppma01fra.de.ibm.com [127.0.0.1])
        by ppma01fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 119EXhTA031396;
        Tue, 9 Feb 2021 14:38:39 GMT
Received: from b06cxnps3075.portsmouth.uk.ibm.com
 (d06relay10.portsmouth.uk.ibm.com [9.149.109.195])
        by ppma01fra.de.ibm.com with ESMTP id 36hjr81sc5-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 09 Feb 2021 14:38:39 +0000
Received: from d06av25.portsmouth.uk.ibm.com (d06av25.portsmouth.uk.ibm.com
 [9.149.105.61])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 119EcaYp22937980
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 9 Feb 2021 14:38:36 GMT
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 9DD0711C04C;
        Tue,  9 Feb 2021 14:38:36 +0000 (GMT)
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 3FDB411C05B;
        Tue,  9 Feb 2021 14:38:36 +0000 (GMT)
Received: from ibm-vm.ibmuc.com (unknown [9.145.1.216])
        by d06av25.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue,  9 Feb 2021 14:38:36 +0000 (GMT)
From: Claudio Imbrenda <imbrenda@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, david@redhat.com, thuth@redhat.com,
        frankja@linux.ibm.com, cohuck@redhat.com, pmorel@linux.ibm.com
Subject: [kvm-unit-tests PATCH v1 1/4] libcflat: add SZ_1M and SZ_2G
Date: Tue,  9 Feb 2021 15:38:32 +0100
Message-Id: <20210209143835.1031617-2-imbrenda@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20210209143835.1031617-1-imbrenda@linux.ibm.com>
References: <20210209143835.1031617-1-imbrenda@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.737
 definitions=2021-02-09_03:2021-02-09,2021-02-09 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 suspectscore=0 bulkscore=0
 priorityscore=1501 lowpriorityscore=0 mlxlogscore=974 clxscore=1015
 adultscore=0 malwarescore=0 spamscore=0 mlxscore=0 phishscore=0
 impostorscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2102090072
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add SZ_1M and SZ_2G to libcflat.h

s390x needs those for large/huge pages

Signed-off-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
---
 lib/libcflat.h | 2 ++
 1 file changed, 2 insertions(+)

```
#### [PATCH v3 1/2] s390/kvm: extend kvm_s390_shadow_fault to return entry pointer
##### From: Claudio Imbrenda <imbrenda@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Claudio Imbrenda <imbrenda@linux.ibm.com>
X-Patchwork-Id: 12078487
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 5CBD5C433DB
	for <kvm@archiver.kernel.org>; Tue,  9 Feb 2021 15:44:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 00C8564E08
	for <kvm@archiver.kernel.org>; Tue,  9 Feb 2021 15:44:14 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232512AbhBIPn5 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 9 Feb 2021 10:43:57 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:39156 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S232235AbhBIPnv (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 9 Feb 2021 10:43:51 -0500
Received: from pps.filterd (m0098419.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 119FgwSb024734;
        Tue, 9 Feb 2021 10:43:09 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=mOqYbFkzDQwH/O1c3r8AZ/mp3+k7PftizoLE+846B2Y=;
 b=K1M3eIZgYcTeKQAagu0cJ1fDE2KZaWnSgN2ZHlGKb2P2wvKPUJ3NczDN4Bj0S2ZOEzdP
 RFFWzFwkl9mXvW0FOrTb9xnK1/7PPJ1Oerey57PMDkbTZ1s5SvtmGvTlV0egaNFBoFXH
 P7tM0Z1mkzY1tcjQ+MJrUDoyLK7DoWaZWHeNjvJzAUJ0oWobC5xtaT/7RFuMYA9O3jKS
 pSHcJp3b31Klwd9OL+reYu8SMkLtN6A4mbR0+YGJ+/kGjkAqMxX38z39sXWHiZvWSxqp
 PpwJ12KVk2skSCv/9B79A8lxQxuzB1gxd2442ACp5MYAjf3PbKFYgQsQNUbBIK4A0AG9 wQ==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 36kw9c006x-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 09 Feb 2021 10:43:08 -0500
Received: from m0098419.ppops.net (m0098419.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 119Fh8vj028733;
        Tue, 9 Feb 2021 10:43:08 -0500
Received: from ppma04fra.de.ibm.com (6a.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.106])
        by mx0b-001b2d01.pphosted.com with ESMTP id 36kw9c0069-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 09 Feb 2021 10:43:08 -0500
Received: from pps.filterd (ppma04fra.de.ibm.com [127.0.0.1])
        by ppma04fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 119FbScD005071;
        Tue, 9 Feb 2021 15:43:06 GMT
Received: from b06cxnps3074.portsmouth.uk.ibm.com
 (d06relay09.portsmouth.uk.ibm.com [9.149.109.194])
        by ppma04fra.de.ibm.com with ESMTP id 36hjr89tpe-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 09 Feb 2021 15:43:06 +0000
Received: from d06av26.portsmouth.uk.ibm.com (d06av26.portsmouth.uk.ibm.com
 [9.149.105.62])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 119Fh3N437945610
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 9 Feb 2021 15:43:03 GMT
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 8E1D5AE045;
        Tue,  9 Feb 2021 15:43:03 +0000 (GMT)
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 3767FAE057;
        Tue,  9 Feb 2021 15:43:03 +0000 (GMT)
Received: from ibm-vm.ibmuc.com (unknown [9.145.1.216])
        by d06av26.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue,  9 Feb 2021 15:43:03 +0000 (GMT)
From: Claudio Imbrenda <imbrenda@linux.ibm.com>
To: linux-kernel@vger.kernel.org
Cc: borntraeger@de.ibm.com, frankja@linux.ibm.com, david@redhat.com,
        cohuck@redhat.com, kvm@vger.kernel.org, linux-s390@vger.kernel.org,
        stable@vger.kernel.org
Subject: [PATCH v3 1/2] s390/kvm: extend kvm_s390_shadow_fault to return entry
 pointer
Date: Tue,  9 Feb 2021 16:43:01 +0100
Message-Id: <20210209154302.1033165-2-imbrenda@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20210209154302.1033165-1-imbrenda@linux.ibm.com>
References: <20210209154302.1033165-1-imbrenda@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.737
 definitions=2021-02-09_03:2021-02-09,2021-02-09 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxlogscore=999
 lowpriorityscore=0 adultscore=0 spamscore=0 malwarescore=0 impostorscore=0
 bulkscore=0 suspectscore=0 mlxscore=0 clxscore=1015 phishscore=0
 priorityscore=1501 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2102090079
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Extend kvm_s390_shadow_fault to return the pointer to the valid leaf
DAT table entry, or to the invalid entry.

Also return some flags in the lower bits of the address:
DAT_PROT: indicates that DAT protection applies because of the
          protection bit in the segment (or, if EDAT, region) tables
NOT_PTE: indicates that the address of the DAT table entry returned
         does not refer to a PTE, but to a segment or region table.

Signed-off-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
Cc: stable@vger.kernel.org
---
 arch/s390/kvm/gaccess.c | 30 +++++++++++++++++++++++++-----
 arch/s390/kvm/gaccess.h |  5 ++++-
 arch/s390/kvm/vsie.c    |  8 ++++----
 3 files changed, 33 insertions(+), 10 deletions(-)

```
#### [kvm-unit-tests PATCH 1/8] s390x: Fix fpc store address in RESTORE_REGS_STACK
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 12078261
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id DA1D8C433E0
	for <kvm@archiver.kernel.org>; Tue,  9 Feb 2021 13:53:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 980CC64ED5
	for <kvm@archiver.kernel.org>; Tue,  9 Feb 2021 13:53:07 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230186AbhBINws (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 9 Feb 2021 08:52:48 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:52150 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S231825AbhBINvb (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 9 Feb 2021 08:51:31 -0500
Received: from pps.filterd (m0098419.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 119DaJVb075325;
        Tue, 9 Feb 2021 08:50:48 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=jgwAdQZx8Y11Zg7Rn/YHMxUc8hbJO/Y0dOkZhegUqxQ=;
 b=YxUeny8CezI/adGWGD/OugHDmbbz8hjbzjiw+cEoqrFmI7P23j0lClhK+p20xscbjkXF
 K99mF78XiXju8xqWYXQafPi6lemQeUOe9b24eWlsyMfVmb0M9Mow6PYscVkLJig25xbz
 iZmoooQbVQbnnGfCK+rNddsCE83eNMM8fwEyyk+5p+O1IBM+wQebt4VzwWAhXxXc/i06
 mQ8g0nYq87b2zDPkuVXEJWvxNWzyPwQT8X54J/lG0RwfonkCEPJak6e44oNeZ5mRWUuZ
 84g5DELGEFxi7dGJOM5rUa5kS0uCOHWvIeVbkXLSGkododPFsHJVCypvyEm5veuJrZOa Yw==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 36ku3211bx-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 09 Feb 2021 08:50:48 -0500
Received: from m0098419.ppops.net (m0098419.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 119DaM1X075402;
        Tue, 9 Feb 2021 08:50:46 -0500
Received: from ppma05fra.de.ibm.com (6c.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.108])
        by mx0b-001b2d01.pphosted.com with ESMTP id 36ku3211b4-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 09 Feb 2021 08:50:46 -0500
Received: from pps.filterd (ppma05fra.de.ibm.com [127.0.0.1])
        by ppma05fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 119DRB9E031294;
        Tue, 9 Feb 2021 13:50:45 GMT
Received: from b06avi18878370.portsmouth.uk.ibm.com
 (b06avi18878370.portsmouth.uk.ibm.com [9.149.26.194])
        by ppma05fra.de.ibm.com with ESMTP id 36hjr7sr4k-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 09 Feb 2021 13:50:44 +0000
Received: from d06av23.portsmouth.uk.ibm.com (d06av23.portsmouth.uk.ibm.com
 [9.149.105.59])
        by b06avi18878370.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 119DoWcR30736692
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 9 Feb 2021 13:50:32 GMT
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 13281A4040;
        Tue,  9 Feb 2021 13:50:42 +0000 (GMT)
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 558D0A4057;
        Tue,  9 Feb 2021 13:50:41 +0000 (GMT)
Received: from linux01.pok.stglabs.ibm.com (unknown [9.114.17.81])
        by d06av23.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue,  9 Feb 2021 13:50:41 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, david@redhat.com, thuth@redhat.com,
        pmorel@linux.ibm.com, imbrenda@linux.ibm.com
Subject: [kvm-unit-tests PATCH 1/8] s390x: Fix fpc store address in
 RESTORE_REGS_STACK
Date: Tue,  9 Feb 2021 08:49:18 -0500
Message-Id: <20210209134925.22248-2-frankja@linux.ibm.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20210209134925.22248-1-frankja@linux.ibm.com>
References: <20210209134925.22248-1-frankja@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.737
 definitions=2021-02-09_03:2021-02-09,2021-02-09 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 lowpriorityscore=0
 phishscore=0 suspectscore=0 spamscore=0 priorityscore=1501 mlxscore=0
 mlxlogscore=999 malwarescore=0 bulkscore=0 adultscore=0 clxscore=1015
 impostorscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2102090067
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The efpc stores in bits 32-63 of a register and we store a full 8
bytes to have the stack 8 byte aligned. This means that the fpc is
stored at offset 4 but we load it from offset 0. Lets replace efpc
with stfpc and get rid of the stg to store at offset 0.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
Reviewed-by: Pierre Morel <pmorel@linux.ibm.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
---
 s390x/macros.S | 3 +--
 1 file changed, 1 insertion(+), 2 deletions(-)

```
#### [kvm-unit-tests PATCH v1 1/3] s390x: introduce leave_pstate to leave userspace
##### From: Claudio Imbrenda <imbrenda@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Claudio Imbrenda <imbrenda@linux.ibm.com>
X-Patchwork-Id: 12079087
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 42F63C433E9
	for <kvm@archiver.kernel.org>; Tue,  9 Feb 2021 20:09:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0426F64E9D
	for <kvm@archiver.kernel.org>; Tue,  9 Feb 2021 20:09:10 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233911AbhBIUHw (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 9 Feb 2021 15:07:52 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:54898 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S233714AbhBITqE (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 9 Feb 2021 14:46:04 -0500
Received: from pps.filterd (m0098410.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 119IpQB3038065
        for <kvm@vger.kernel.org>; Tue, 9 Feb 2021 13:52:01 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=aEytD9WRlnGhVpxq85ibOkYbg29iC4fqSqmHYnlSezI=;
 b=kdR8U60bGh2DGcgbrrFDXtfnIgJ6ySfI5w4mU7Ew0vHFP0Bp+sa6PpUpgEDek/nMEjBE
 DDmRpXrrsOCaWzNWrGcqOBKiPj1aWvvKwTxCBqEw6EI/vozkuvzTZ40eQLEkNxjZ33Ia
 V3QCAMwXbnRUIoh4yqG/pD7pN6PUOWfcKEbm+tYYbyKid5OziE1P2zszk8OcFLJyOssA
 5zlHrER5t809inOFQH91LYH4Y86TtSfxPdVF2KnsAWl9E6Wdc5XiG8RfwniXS8knOnBO
 W03Lm9hn20WYTFiwTMWiLbWV8N+WlcAEIILOi7POZQPnsoiG/68/FajSJsZHaoJt9bIc vA==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 36kywqr6wc-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT)
        for <kvm@vger.kernel.org>; Tue, 09 Feb 2021 13:52:01 -0500
Received: from m0098410.ppops.net (m0098410.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 119IpW61040886
        for <kvm@vger.kernel.org>; Tue, 9 Feb 2021 13:52:00 -0500
Received: from ppma03ams.nl.ibm.com (62.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.98])
        by mx0a-001b2d01.pphosted.com with ESMTP id 36kywqr6vq-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 09 Feb 2021 13:52:00 -0500
Received: from pps.filterd (ppma03ams.nl.ibm.com [127.0.0.1])
        by ppma03ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 119IkdFN028448;
        Tue, 9 Feb 2021 18:51:58 GMT
Received: from b06avi18626390.portsmouth.uk.ibm.com
 (b06avi18626390.portsmouth.uk.ibm.com [9.149.26.192])
        by ppma03ams.nl.ibm.com with ESMTP id 36hqda3hu5-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 09 Feb 2021 18:51:58 +0000
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06avi18626390.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 119Ipjob36176150
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 9 Feb 2021 18:51:45 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 82FDDA4060;
        Tue,  9 Feb 2021 18:51:55 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 2A18BA405C;
        Tue,  9 Feb 2021 18:51:55 +0000 (GMT)
Received: from ibm-vm.ibmuc.com (unknown [9.145.1.216])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue,  9 Feb 2021 18:51:55 +0000 (GMT)
From: Claudio Imbrenda <imbrenda@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: david@redhat.com, thuth@redhat.com, frankja@linux.ibm.com,
        cohuck@redhat.com, pmorel@linux.ibm.com, borntraeger@de.ibm.com
Subject: [kvm-unit-tests PATCH v1 1/3] s390x: introduce leave_pstate to leave
 userspace
Date: Tue,  9 Feb 2021 19:51:52 +0100
Message-Id: <20210209185154.1037852-2-imbrenda@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20210209185154.1037852-1-imbrenda@linux.ibm.com>
References: <20210209185154.1037852-1-imbrenda@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.737
 definitions=2021-02-09_05:2021-02-09,2021-02-09 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 malwarescore=0 adultscore=0
 mlxlogscore=857 phishscore=0 lowpriorityscore=0 spamscore=0 bulkscore=0
 clxscore=1015 suspectscore=0 impostorscore=0 mlxscore=0 priorityscore=1501
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2102090086
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In most testcases, we enter problem state (userspace) just to test if a
privileged instruction causes a fault. In some cases, though, we need
to test if an instruction works properly in userspace. This means that
we do not expect a fault, and we need an orderly way to leave problem
state afterwards.

This patch introduces a simple system based on the SVC instruction.

Signed-off-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
---
 lib/s390x/asm/arch_def.h |  5 +++++
 lib/s390x/interrupt.c    | 12 ++++++++++--
 2 files changed, 15 insertions(+), 2 deletions(-)

```
#### [PATCH v3] KVM: x86/MMU: Do not check unsync status for root SP.
##### From: Yu Zhang <yu.c.zhang@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yu Zhang <yu.c.zhang@linux.intel.com>
X-Patchwork-Id: 12077571
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-14.8 required=3.0 tests=BAYES_00,
	DATE_IN_FUTURE_06_12,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 62958C433E0
	for <kvm@archiver.kernel.org>; Tue,  9 Feb 2021 09:26:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0BB1664EB4
	for <kvm@archiver.kernel.org>; Tue,  9 Feb 2021 09:26:46 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230181AbhBIJ0b (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 9 Feb 2021 04:26:31 -0500
Received: from mga04.intel.com ([192.55.52.120]:53959 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229839AbhBIJVq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 9 Feb 2021 04:21:46 -0500
IronPort-SDR: 
 K6Dgfz/b2BTMnL3io6eKqqwYcX64bAE1ykXj5LprFnRCpekaaMd1UWMvoxJkRZWtLtPIAmQs5r
 tGk3ub347WWQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9889"; a="179293958"
X-IronPort-AV: E=Sophos;i="5.81,164,1610438400";
   d="scan'208";a="179293958"
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by fmsmga104.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 09 Feb 2021 01:20:00 -0800
IronPort-SDR: 
 /Yng3oo8OGEW+f8mThOaJfZqvh6dvvjoINZvY8Mo6ZXCEOWGCH3ABS7tYP9xw4NKFaZp4b8rTM
 iCpo+c/tUpWw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.81,164,1610438400";
   d="scan'208";a="396042075"
Received: from zhangyu-optiplex-7040.bj.intel.com ([10.238.154.148])
  by orsmga008.jf.intel.com with ESMTP; 09 Feb 2021 01:19:57 -0800
From: Yu Zhang <yu.c.zhang@linux.intel.com>
To: pbonzini@redhat.com, seanjc@google.com
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        vkuznets@redhat.com, wanpengli@tencent.com, jmattson@google.com,
        joro@8bytes.org
Subject: [PATCH v3] KVM: x86/MMU: Do not check unsync status for root SP.
Date: Wed, 10 Feb 2021 01:01:11 +0800
Message-Id: <20210209170111.4770-1-yu.c.zhang@linux.intel.com>
X-Mailer: git-send-email 2.17.1
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In shadow page table, only leaf SPs may be marked as unsync;
instead, for non-leaf SPs, we store the number of unsynced
children in unsync_children. Therefore, in kvm_mmu_sync_root(),
sp->unsync shall always be zero for the root SP and there is
no need to check it. Remove the check, and add a warning
inside mmu_sync_children() to assert that the flags are used
properly.

While at it, move the warning from mmu_need_write_protect()
to kvm_unsync_page().

Co-developed-by: Sean Christopherson <seanjc@google.com>
Signed-off-by: Sean Christopherson <seanjc@google.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Yu Zhang <yu.c.zhang@linux.intel.com>
---
 arch/x86/kvm/mmu/mmu.c | 12 +++++++++---
 1 file changed, 9 insertions(+), 3 deletions(-)

```
#### 
##### 

```c
```
