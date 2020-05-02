

#### [PATCH RFC 0/1] Hypercall UCALL for guest/userspace communication
##### From: Forrest Yuan Yu <yuanyu@google.com>

```c
From patchwork Fri May  1 18:51:46 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Forrest Yuan Yu <yuanyu@google.com>
X-Patchwork-Id: 11523143
Return-Path: <SRS0=uSm/=6P=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2E0F41575
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  1 May 2020 18:52:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 12ABE20787
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  1 May 2020 18:52:21 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="imuA6/8z"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730381AbgEASwU (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 1 May 2020 14:52:20 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:45098 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-FAIL-OK-FAIL)
        by vger.kernel.org with ESMTP id S1729767AbgEASwT (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 1 May 2020 14:52:19 -0400
Received: from mail-qv1-xf4a.google.com (mail-qv1-xf4a.google.com
 [IPv6:2607:f8b0:4864:20::f4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 302B8C061A0C
        for <kvm@vger.kernel.org>; Fri,  1 May 2020 11:52:19 -0700 (PDT)
Received: by mail-qv1-xf4a.google.com with SMTP id bm3so10995036qvb.0
        for <kvm@vger.kernel.org>; Fri, 01 May 2020 11:52:19 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=dqyWkacoDk0SlzRjFvS5NPN8XWNRiCuxkwSEq7I48cE=;
        b=imuA6/8z7ACHxfkEWthb7/P9i0FIbUx1TzWmMDuksLp8MQLEZ+UyF6Dd/gVb/8HNO3
         FRTAiCh7aI6pBwt1fpQnw31soJT4j7jt14Af6kXssmRqkZMTX+V/7l5exOFE/oPvQaPj
         cUGXJljn1hLOse4sXdKVODzRkvMb7pf94EODSWF6gdpbo/4WjKVJo4mpBuyHRZRooFz9
         Jd8Q81eju937SW4h6De+ySrY87gjkxTzVAssbU6UYhyPqPoiExLSonj9mpXyFBq5vUXX
         YM9WBh/IQB9GxTD4fUXwpmwjcToZ66KYsQditCuN0hXCoKOfOa6Ahp7VGO1LKTlMYDCt
         1p8A==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=dqyWkacoDk0SlzRjFvS5NPN8XWNRiCuxkwSEq7I48cE=;
        b=cHNXlHJ3yWPHwWVpRiRDwlzPLBPn8iuInfBkf1h5ScDViV9rM8H/zWp1PnY002FMbX
         lJkhCWOv68jsZsguwSjUTx6H4On9JZXckWfiCAwE6/zVC5t4CfCrhTJcvurdhEs5+UgG
         7ojN2G6HlMMsesuqZ/LYlO+5wXzalNsdOcRRla/EtsUBNo1pRS5m3p0jzWnvvaFGsh3l
         YsYkHJTrF5bkbcsrDzwp4/xwjTo6dPoe8t2tYZs2zK7Levkch1iHohAnx7udmP2OfKZ+
         SGtZksTlqraV2Zv9ZkRHt7gO2KYn1pQ/HJDrfnAusyHIK/MToPA3N6fsJ1/vvsOmYudt
         3/Jw==
X-Gm-Message-State: AGi0PuZcmVQ3N/rEWK7DxIq6KyEs/UPmeRv1kxB3xjDLAusH+ftXur28
        w+frKyzzofcxyj4r2sZrnGvQHvYN78/rH2HyXgJRZkgrNYS7ij0AmsjPpkAoU98F/+wCTjifa16
        peRZ1duAb5LuN+6BlFL2pw7v6N/Cz8/w3TSX+afmIxpDqx8i294KMX1QM0w==
X-Google-Smtp-Source: 
 APiQypKhmBQD1Dcf+8aZNFzRU9wdT3IgF3rDC+ZBO5nnqqXi+E8aGtYFDJY58/KzvnbQLQkV7H55XYmVrQA=
X-Received: by 2002:a0c:efc8:: with SMTP id a8mr5133922qvt.153.1588359137619;
 Fri, 01 May 2020 11:52:17 -0700 (PDT)
Date: Fri,  1 May 2020 11:51:46 -0700
Message-Id: <20200501185147.208192-1-yuanyu@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.26.2.526.g744177e7f7-goog
Subject: [PATCH RFC 0/1] Hypercall UCALL for guest/userspace communication
From: Forrest Yuan Yu <yuanyu@google.com>
To: kvm@vger.kernel.org
Cc: Forrest Yuan Yu <yuanyu@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This RFC is to add a hypercall UCALL so that guest can communicate with
the userspace hypervisor. A guest may want to do this in different
scenarios. For example, a guest can ask the userspace hypervisor to
harden security by setting restricted access permissions on guest SLAT
entries.

Please note this hypercall provides the infrastructure for this type of
communication but does not enforce the protocol. A proposal for the
guest/userspace communication protocol will follow if this RFC is
accepted.

Forrest Yuan Yu (1):
  KVM: x86: add KVM_HC_UCALL hypercall

 Documentation/virt/kvm/api.rst                |  15 +-
 Documentation/virt/kvm/cpuid.rst              |   3 +
 Documentation/virt/kvm/hypercalls.rst         |  14 ++
 arch/x86/include/asm/kvm_host.h               |   1 +
 arch/x86/include/uapi/asm/kvm_para.h          |   1 +
 arch/x86/kvm/x86.c                            |  39 +++-
 include/uapi/linux/kvm.h                      |   1 +
 include/uapi/linux/kvm_para.h                 |   1 +
 tools/testing/selftests/kvm/.gitignore        |   1 +
 tools/testing/selftests/kvm/Makefile          |   1 +
 .../selftests/kvm/x86_64/hypercall_ucall.c    | 195 ++++++++++++++++++
 11 files changed, 264 insertions(+), 8 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/x86_64/hypercall_ucall.c
```
#### [PATCH 0/3] vfio-pci: Block user access to disabled device MMIO
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
From patchwork Fri May  1 21:38:56 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alex Williamson <alex.williamson@redhat.com>
X-Patchwork-Id: 11523297
Return-Path: <SRS0=uSm/=6P=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BF2D8139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  1 May 2020 21:39:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A77B1208DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  1 May 2020 21:39:09 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Lz1Aeq9u"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726973AbgEAVjH (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 1 May 2020 17:39:07 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:53972 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726366AbgEAVjG (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 1 May 2020 17:39:06 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1588369145;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=GIT31CsSTgsaQoUzYR0DvSWUFhNop6BqpZn0iiLF29Q=;
        b=Lz1Aeq9uDyiYuDCRX4GkhSvOyw4ZtKv5Y0yNZ08fEVKPsAPOFx1pHu9JwH5ZnnHrP0GB/0
        jwXmUaQUhvu7xkKvsCyV5X55JmQMgwKOKyB4nwyt76+55r2fJg2qH6X6vhDeSY18jkdDIA
        Lb9M8VUtURDUpBJPWhmrhRw6p/6BXes=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-74-SLwr3-LZONqihU56HCeGHA-1; Fri, 01 May 2020 17:39:03 -0400
X-MC-Unique: SLwr3-LZONqihU56HCeGHA-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id E9A8B8005B7;
        Fri,  1 May 2020 21:39:02 +0000 (UTC)
Received: from gimli.home (ovpn-113-95.phx2.redhat.com [10.3.113.95])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 265A45B829;
        Fri,  1 May 2020 21:38:57 +0000 (UTC)
Subject: [PATCH 0/3] vfio-pci: Block user access to disabled device MMIO
From: Alex Williamson <alex.williamson@redhat.com>
To: kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, cohuck@redhat.com, jgg@ziepe.ca,
        peterx@redhat.com
Date: Fri, 01 May 2020 15:38:56 -0600
Message-ID: <158836742096.8433.685478071796941103.stgit@gimli.home>
User-Agent: StGit/0.19-dirty
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add tracking of the device memory enable bit and block/fault accesses
to device MMIO space while disabled.  This provides synchronous fault
handling for CPU accesses to the device and prevents the user from
triggering platform level error handling present on some systems.
Device reset and MSI-X vector table accesses are also included such
that access is blocked across reset and vector table accesses do not
depend on the user configuration of the device.

This is based on the vfio for-linus branch currently in next, making
use of follow_pfn() in vaddr_get_pfn() and therefore requiring patch
1/ to force the user fault in the case that a PFNMAP vma might be
DMA mapped before user access.  Further PFNMAP iommu invalidation
tracking is not yet included here.

As noted in the comments, I'm copying quite a bit of the logic from
rdma code for performing the zap_vma_ptes() calls and I'm also
attempting to resolve lock ordering issues in the fault handler to
lockdep's satisfaction.  I appreciate extra eyes on these sections in
particular.

I expect this to be functionally equivalent for any well behaved
userspace driver, but obviously there is a potential for the user to
get -EIO or SIGBUS on device access.  The device is provided to the
user enabled and device resets will restore the command register, so
by my evaluation a user would need to explicitly disable the memory
enable bit to trigger these faults.  We could potentially remap vmas
to a zero page rather than SIGBUS if we experience regressions, but
without known code requiring that, SIGBUS seems the appropriate
response to this condition.  Thanks,

Alex
---

Alex Williamson (3):
      vfio/type1: Support faulting PFNMAP vmas
      vfio-pci: Fault mmaps to enable vma tracking
      vfio-pci: Invalidate mmaps and block MMIO access on disabled memory


 drivers/vfio/pci/vfio_pci.c         |  268 +++++++++++++++++++++++++++++++++--
 drivers/vfio/pci/vfio_pci_config.c  |   31 ++++
 drivers/vfio/pci/vfio_pci_intrs.c   |   18 ++
 drivers/vfio/pci/vfio_pci_private.h |   11 +
 drivers/vfio/pci/vfio_pci_rdwr.c    |   12 ++
 drivers/vfio/vfio_iommu_type1.c     |   36 ++++-
 6 files changed, 356 insertions(+), 20 deletions(-)
```
