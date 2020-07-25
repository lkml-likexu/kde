#### [RFC 1/2] RISC-V: KVM: enable ioeventfd capability and compile for risc-v
##### From: Yifei Jiang <jiangyifei@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yifei Jiang <jiangyifei@huawei.com>
X-Patchwork-Id: 11682739
Return-Path: <SRS0=BqhU=BD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 99D0C913
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Jul 2020 08:55:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8978820748
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Jul 2020 08:55:52 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727847AbgGXIzt (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 24 Jul 2020 04:55:49 -0400
Received: from szxga06-in.huawei.com ([45.249.212.32]:55940 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1727112AbgGXIzt (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 24 Jul 2020 04:55:49 -0400
Received: from DGGEMS401-HUB.china.huawei.com (unknown [172.30.72.60])
        by Forcepoint Email with ESMTP id DDC697F4DEC214F115C6;
        Fri, 24 Jul 2020 16:55:38 +0800 (CST)
Received: from huawei.com (10.174.187.31) by DGGEMS401-HUB.china.huawei.com
 (10.3.19.201) with Microsoft SMTP Server id 14.3.487.0; Fri, 24 Jul 2020
 16:55:28 +0800
From: Yifei Jiang <jiangyifei@huawei.com>
To: <pbonzini@redhat.com>, <paul.walmsley@sifive.com>,
        <palmer@dabbelt.com>, <aou@eecs.berkeley.edu>
CC: <anup.patel@wdc.com>, <atish.patra@wdc.com>, <kvm@vger.kernel.org>,
        <kvm-riscv@lists.infradead.org>, <linux-riscv@lists.infradead.org>,
        <linux-kernel@vger.kernel.org>, <victor.zhangxiaofeng@huawei.com>,
        <wu.wubin@huawei.com>, <zhang.zhanghailiang@huawei.com>,
        <dengkai1@huawei.com>, <limingwang@huawei.com>,
        Yifei Jiang <jiangyifei@huawei.com>
Subject: [RFC 1/2] RISC-V: KVM: enable ioeventfd capability and compile for
 risc-v
Date: Fri, 24 Jul 2020 16:54:40 +0800
Message-ID: <20200724085441.1514-2-jiangyifei@huawei.com>
X-Mailer: git-send-email 2.26.2.windows.1
In-Reply-To: <20200724085441.1514-1-jiangyifei@huawei.com>
References: <20200724085441.1514-1-jiangyifei@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.174.187.31]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Signed-off-by: Yifei Jiang <jiangyifei@huawei.com>
Signed-off-by: Mingwang Li <limingwang@huawei.com>
---
 arch/riscv/kvm/Kconfig  | 2 ++
 arch/riscv/kvm/Makefile | 2 +-
 arch/riscv/kvm/vm.c     | 1 +
 3 files changed, 4 insertions(+), 1 deletion(-)

```
#### [for-5.2 v4 01/10] host trust limitation: Introduce new host trust limitation interface
##### From: David Gibson <david@gibson.dropbear.id.au>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Gibson <david@gibson.dropbear.id.au>
X-Patchwork-Id: 11681927
Return-Path: <SRS0=BqhU=BD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BAE46722
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Jul 2020 02:58:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A1887207FC
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Jul 2020 02:58:03 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=gibson.dropbear.id.au
 header.i=@gibson.dropbear.id.au header.b="I8R/r6K0"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726783AbgGXC5u (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 23 Jul 2020 22:57:50 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:52370 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726381AbgGXC5t (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 23 Jul 2020 22:57:49 -0400
Received: from ozlabs.org (bilbo.ozlabs.org [IPv6:2401:3900:2:1::2])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id BB05AC0619D3
        for <kvm@vger.kernel.org>; Thu, 23 Jul 2020 19:57:49 -0700 (PDT)
Received: by ozlabs.org (Postfix, from userid 1007)
        id 4BCYlv33w0z9sSt; Fri, 24 Jul 2020 12:57:47 +1000 (AEST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple;
        d=gibson.dropbear.id.au; s=201602; t=1595559467;
        bh=aXMwhPSEkPHTpzErQPz4f4zNkJ2AVJxzRI0h3KgdOaE=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=I8R/r6K0P/IZg9wSKSjVg8EjaXlXMJmGktM9HhxalYdYd1gB7LXXgFxkcmHIyQHqn
         yxPqtlhIW670eVcVZpL3C3m1uB0rstBiBaYembN8TPTdsKUsNqvjo+wNjHOe5V8GXt
         lrZfMdVdBphNf6F/mciBlXPWMn31lLx5pZr4iUis=
From: David Gibson <david@gibson.dropbear.id.au>
To: dgilbert@redhat.com, frankja@linux.ibm.com, pair@us.ibm.com,
        qemu-devel@nongnu.org, pbonzini@redhat.com, brijesh.singh@amd.com
Cc: ehabkost@redhat.com, marcel.apfelbaum@gmail.com,
 "Michael S. Tsirkin" <mst@redhat.com>, qemu-ppc@nongnu.org,
 kvm@vger.kernel.org, pasic@linux.ibm.com, qemu-s390x@nongnu.org,
 David Gibson <david@gibson.dropbear.id.au>,
 David Hildenbrand <david@redhat.com>,
 Christian Borntraeger <borntraeger@de.ibm.com>,
 Richard Henderson <rth@twiddle.net>,
 =?utf-8?q?Daniel_P=2E_Berrang=C3=A9?= <berrange@redhat.com>,
 mdroth@linux.vnet.ibm.com, Thomas Huth <thuth@redhat.com>,
 Cornelia Huck <cohuck@redhat.com>,
 Richard Henderson <richard.henderson@linaro.org>
Subject: [for-5.2 v4 01/10] host trust limitation: Introduce new host trust
 limitation interface
Date: Fri, 24 Jul 2020 12:57:35 +1000
Message-Id: <20200724025744.69644-2-david@gibson.dropbear.id.au>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20200724025744.69644-1-david@gibson.dropbear.id.au>
References: <20200724025744.69644-1-david@gibson.dropbear.id.au>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Several architectures have mechanisms which are designed to protect guest
memory from interference or eavesdropping by a compromised hypervisor.  AMD
SEV does this with in-chip memory encryption and Intel has a similar
mechanism.  POWER's Protected Execution Framework (PEF) accomplishes a
similar goal using an ultravisor and new memory protection features,
instead of encryption.

To (partially) unify handling for these, this introduces a new
HostTrustLimitation QOM interface.

Signed-off-by: David Gibson <david@gibson.dropbear.id.au>
Acked-by: Dr. David Alan Gilbert <dgilbert@redhat.com>
Reviewed-by: Richard Henderson <richard.henderson@linaro.org>
---
 backends/Makefile.objs               |  2 ++
 backends/host-trust-limitation.c     | 29 ++++++++++++++++++++++++
 include/exec/host-trust-limitation.h | 33 ++++++++++++++++++++++++++++
 include/qemu/typedefs.h              |  1 +
 4 files changed, 65 insertions(+)
 create mode 100644 backends/host-trust-limitation.c
 create mode 100644 include/exec/host-trust-limitation.h

```
#### [PATCH] kvm: x86: fix reversed timespec values in PV wall clockFrom: Oliver Upton <oupton@google.com>
##### From: Oliver Upton <oupton@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Oliver Upton <oupton@google.com>
X-Patchwork-Id: 11683913
Return-Path: <SRS0=BqhU=BD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 027C81709
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Jul 2020 17:35:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DE1FE2067D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Jul 2020 17:35:49 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="fN4sZq/T"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726899AbgGXRfr (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 24 Jul 2020 13:35:47 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:48080 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726397AbgGXRfq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 24 Jul 2020 13:35:46 -0400
Received: from mail-pf1-x449.google.com (mail-pf1-x449.google.com
 [IPv6:2607:f8b0:4864:20::449])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 98A55C0619E5
        for <kvm@vger.kernel.org>; Fri, 24 Jul 2020 10:35:46 -0700 (PDT)
Received: by mail-pf1-x449.google.com with SMTP id u11so105557pfm.23
        for <kvm@vger.kernel.org>; Fri, 24 Jul 2020 10:35:46 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=9z4C5r79ACInbjfze4NId6Y2btX0M3fh8nl4dn9b26s=;
        b=fN4sZq/TP83yFzy+siEXLP4SrgOpx7NBN6ZiJVHwc3DsYjLS6vFtBeOspp2/PMgVYc
         BRp6JmUw/hMfGePHy/NJFvFDe4LzBFq+JJE/NvACrw8LLgRTmINP+mnqpWisEEkunNQo
         Fws/zekrL0GiMxgAUAMLgsE/13aJfgnxXFtzWBra/K5uSTlmzpjtzQ+184Qw3Ap7Dpx4
         UXtMdoJtToto60EenvqQcfQmcQXzbcG0KMU7+EsrPUzi9282GIyW5upCwSSvvhDFy5XM
         n6lc9UKvVwwk5SFEm6220t9AwlKp07h/YEo0IuB+ak1ke9ySE/DZhqPkzRHcs1peQsMn
         0L9Q==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=9z4C5r79ACInbjfze4NId6Y2btX0M3fh8nl4dn9b26s=;
        b=Qv7TX6gvkWa0EhPmB0zaskaQ9XljS9EU8pYdks3H05OnE8QJbpEbqzS5dHR3mG7BkB
         S/6edJHEoVLzsh37Ppy9iLRqydQJXZaZN2mdVb7x7WYh+rCS5l3Jsqzhf93+mm/Sx8k+
         uSpfHVrRdyX54Ufgi/Vzkq7Iy/g3MfECTuj+JPSBzT08X5z4ckZqkt/6iu3Bx6wQ7syn
         Fja3gaEitPf028SYEKWwwh+vdc7Jr5XZ1u0GWojtyF/7ttb/Bil5iyGuVwBV7V5fDyTg
         UtezkaB9QaIrgb1kxRhznun0dE7KcqTw1RvCk8XvcqflP/9XxTTNfbbUh5gG0xeJBNuK
         56wQ==
X-Gm-Message-State: AOAM532A1RC//YDIP56VOL731kI6iiRhM4IJHi8hjmuTpcgof+RoUDiD
        2krhNpeoA5kbVlH2iEeLlmYtD7fLCzKzqb2Rnf9BpMjvwKpgFsr0syqtcwkaxjPvy8YUFnv+Tf/
        QnhUaIwtwjNQd2qepgokB10zlCv8qMQm/+Xi4Q2Y2Wzc42cfGeFVUxHIDwg==
X-Google-Smtp-Source: 
 ABdhPJzodcJYbtUzygaRALh5D65g0it/h4cc6rUSeS1ixMjdWjcC2aH+Frr78yzdpW4AwxEmwHhFlf6YfCg=
X-Received: by 2002:a17:90b:1b08:: with SMTP id
 nu8mr2292293pjb.190.1595612145895;
 Fri, 24 Jul 2020 10:35:45 -0700 (PDT)
Date: Fri, 24 Jul 2020 17:35:36 +0000
Message-Id: <20200724173536.789982-1-oupton@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.28.0.rc0.142.g3c755180ce-goog
Subject: [PATCH] kvm: x86: fix reversed timespec values in PV wall clock
From: Oliver Upton <oupton@google.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        linux-kernel@vger.kernel.org, Oliver Upton <oupton@google.com>,
        stable@vger.kernel.org, Jim Mattson <jmattson@google.com>,
        Peter Shier <pshier@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

commit 8171cd68806b ("KVM: x86: use raw clock values consistently")
causes KVM to accidentally write seconds to the nanoseconds field (and
vice versa) in the KVM wall clock. Fix it by reversing this accidental
switch. Modulo the written nanoseconds value by NSEC_PER_SEC to correct
for the amount of time represented as seconds.

Fixes: 8171cd68806b ("KVM: x86: use raw clock values consistently")
Cc: stable@vger.kernel.org
Reviewed-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
Signed-off-by: Oliver Upton <oupton@google.com>
---
 Parent commit: c34b26b98cac ("KVM: MIPS: clean up redundant 'kvm_run' parameters")

 arch/x86/kvm/x86.c | 5 +++--
 1 file changed, 3 insertions(+), 2 deletions(-)

```
#### [PATCH] pseries: fix kvmppc_set_fwnmi()
##### From: Laurent Vivier <lvivier@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Laurent Vivier <lvivier@redhat.com>
X-Patchwork-Id: 11682633
Return-Path: <SRS0=BqhU=BD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 90C9D1709
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Jul 2020 08:35:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 775272068F
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Jul 2020 08:35:42 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="VtOVNcKL"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727016AbgGXIfl (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 24 Jul 2020 04:35:41 -0400
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:38759 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726753AbgGXIfl (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 24 Jul 2020 04:35:41 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1595579739;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=InBwq/6ekQfs5RfXLsv/seuvSyx3UpGVDS5FZpmQ+jQ=;
        b=VtOVNcKLyCdazojxp5oR2wS21+QRB95KPoQJeKK39Fn31YwCqMkyX54rU88Gsr5/X8FAC0
        GTJ320j1zoNPIRS6Es93C8XOQ9hfqyh/a0wf6CWE52Q6pzwZnsWN3asVYA0VHTKsdFMAoc
        v2Pk9xsZ3nIR2dEWXwcHK8sd4W51Sr4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-336-fQzOSTIOOkiInjhslgAVeA-1; Fri, 24 Jul 2020 04:35:37 -0400
X-MC-Unique: fQzOSTIOOkiInjhslgAVeA-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 8644D80183C;
        Fri, 24 Jul 2020 08:35:36 +0000 (UTC)
Received: from thinkpad.redhat.com (ovpn-112-21.ams2.redhat.com
 [10.36.112.21])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 9D9162DE73;
        Fri, 24 Jul 2020 08:35:34 +0000 (UTC)
From: Laurent Vivier <lvivier@redhat.com>
To: qemu-devel@nongnu.org
Cc: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>,
        David Gibson <david@gibson.dropbear.id.au>,
        qemu-ppc@nongnu.org, Laurent Vivier <lvivier@redhat.com>,
        npiggin@gmail.com
Subject: [PATCH] pseries: fix kvmppc_set_fwnmi()
Date: Fri, 24 Jul 2020 10:35:33 +0200
Message-Id: <20200724083533.281700-1-lvivier@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

QEMU issues the ioctl(KVM_CAP_PPC_FWNMI) on the first vCPU.

If the first vCPU is currently running, the vCPU mutex is held
and the ioctl() cannot be done and waits until the mutex is released.
This never happens and the VM is stuck.

To avoid this deadlock, issue the ioctl on the same vCPU doing the
RTAS call.

The problem can be reproduced by booting a guest with several vCPUs
(the probability to have the problem is (n - 1) / n,  n = # of CPUs),
and then by triggering a kernel crash with "echo c >/proc/sysrq-trigger".

On the reboot, the kernel hangs after:

...
[    0.000000] -----------------------------------------------------
[    0.000000] ppc64_pft_size    = 0x0
[    0.000000] phys_mem_size     = 0x48000000
[    0.000000] dcache_bsize      = 0x80
[    0.000000] icache_bsize      = 0x80
[    0.000000] cpu_features      = 0x0001c06f8f4f91a7
[    0.000000]   possible        = 0x0003fbffcf5fb1a7
[    0.000000]   always          = 0x00000003800081a1
[    0.000000] cpu_user_features = 0xdc0065c2 0xaee00000
[    0.000000] mmu_features      = 0x3c006041
[    0.000000] firmware_features = 0x00000085455a445f
[    0.000000] physical_start    = 0x8000000
[    0.000000] -----------------------------------------------------
[    0.000000] numa:   NODE_DATA [mem 0x47f33c80-0x47f3ffff]

Fixes: ec010c00665b ("ppc/spapr: KVM FWNMI should not be enabled until guest requests it")
Cc: npiggin@gmail.com
Signed-off-by: Laurent Vivier <lvivier@redhat.com>
Reviewed-by: Philippe Mathieu-Daudé <philmd@redhat.com>
---
 hw/ppc/spapr_rtas.c  | 2 +-
 target/ppc/kvm.c     | 3 +--
 target/ppc/kvm_ppc.h | 4 ++--
 3 files changed, 4 insertions(+), 5 deletions(-)

```
#### [RESEND RFC PATCH v1] arm64: kvm: flush tlbs by range in unmap_stage2_range function
##### From: Zhenyu Ye <yezhenyu2@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhenyu Ye <yezhenyu2@huawei.com>
X-Patchwork-Id: 11683357
Return-Path: <SRS0=BqhU=BD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1EAE81392
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Jul 2020 13:43:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0F90C2074A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Jul 2020 13:43:42 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726639AbgGXNnk (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 24 Jul 2020 09:43:40 -0400
Received: from szxga06-in.huawei.com ([45.249.212.32]:58292 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726326AbgGXNnj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 24 Jul 2020 09:43:39 -0400
Received: from DGGEMS413-HUB.china.huawei.com (unknown [172.30.72.58])
        by Forcepoint Email with ESMTP id 6B9BB6B6301DDE2BC00E;
        Fri, 24 Jul 2020 21:43:29 +0800 (CST)
Received: from DESKTOP-KKJBAGG.china.huawei.com (10.174.186.173) by
 DGGEMS413-HUB.china.huawei.com (10.3.19.213) with Microsoft SMTP Server id
 14.3.487.0; Fri, 24 Jul 2020 21:43:20 +0800
From: Zhenyu Ye <yezhenyu2@huawei.com>
To: <maz@kernel.org>, <james.morse@arm.com>,
        <julien.thierry.kdev@gmail.com>, <suzuki.poulose@arm.com>,
        <catalin.marinas@arm.com>, <will@kernel.org>,
        <steven.price@arm.com>, <mark.rutland@arm.com>, <ascull@google.com>
CC: <kvm@vger.kernel.org>, <kvmarm@lists.cs.columbia.edu>,
        <linux-arm-kernel@lists.infradead.org>,
        <linux-kernel@vger.kernel.org>, <linux-arch@vger.kernel.org>,
        <linux-mm@kvack.org>, <arm@kernel.org>, <xiexiangyou@huawei.com>,
        <yezhenyu2@huawei.com>
Subject: [RESEND RFC PATCH v1] arm64: kvm: flush tlbs by range in
 unmap_stage2_range function
Date: Fri, 24 Jul 2020 21:43:15 +0800
Message-ID: <20200724134315.805-1-yezhenyu2@huawei.com>
X-Mailer: git-send-email 2.22.0.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.186.173]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Now in unmap_stage2_range(), we flush tlbs one by one just after the
corresponding pages cleared.  However, this may cause some performance
problems when the unmap range is very large (such as when the vm
migration rollback, this may cause vm downtime too loog).

This patch moves the kvm_tlb_flush_vmid_ipa() out of loop, and
flush tlbs by range after other operations completed.  Because we
do not make new mapping for the pages here, so this doesn't violate
the Break-Before-Make rules.

Signed-off-by: Zhenyu Ye <yezhenyu2@huawei.com>
---
 arch/arm64/include/asm/kvm_asm.h |  2 ++
 arch/arm64/kvm/hyp/tlb.c         | 36 ++++++++++++++++++++++++++++++++
 arch/arm64/kvm/mmu.c             | 11 +++++++---
 3 files changed, 46 insertions(+), 3 deletions(-)

```
#### [PATCH v4 1/5] PCI: Add Intel QuickAssist device IDs
##### From: Giovanni Cabiddu <giovanni.cabiddu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Giovanni Cabiddu <giovanni.cabiddu@intel.com>
X-Patchwork-Id: 11682701
Return-Path: <SRS0=BqhU=BD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A0F75138A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Jul 2020 08:48:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 925332070B
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Jul 2020 08:48:38 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726984AbgGXIsN (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 24 Jul 2020 04:48:13 -0400
Received: from mga02.intel.com ([134.134.136.20]:45604 "EHLO mga02.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726554AbgGXIsN (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 24 Jul 2020 04:48:13 -0400
IronPort-SDR: 
 Y1C/99zzEjbNXPGuNNHyjTHJZndvEwuG1SSV84A6E/a3ctGPpJnK7TEcHDIqB5u3TzEyiyE1+N
 /SV8Dmcc3MXQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9691"; a="138742739"
X-IronPort-AV: E=Sophos;i="5.75,390,1589266800";
   d="scan'208";a="138742739"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga004.fm.intel.com ([10.253.24.48])
  by orsmga101.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 24 Jul 2020 01:48:12 -0700
IronPort-SDR: 
 XGLvuQ0Qav2ohwLVK2nttsOrS9rmfF9DHR/pGa5JlPvRB6opUdBezYHZ5jt0CeT0zEOCQT8ehm
 nL1Kjcv4hXHw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,390,1589266800";
   d="scan'208";a="311335271"
Received: from silpixa00400314.ir.intel.com (HELO
 silpixa00400314.ger.corp.intel.com) ([10.237.222.51])
  by fmsmga004.fm.intel.com with ESMTP; 24 Jul 2020 01:48:09 -0700
From: Giovanni Cabiddu <giovanni.cabiddu@intel.com>
To: alex.williamson@redhat.com, herbert@gondor.apana.org.au
Cc: cohuck@redhat.com, nhorman@redhat.com, vdronov@redhat.com,
        bhelgaas@google.com, mark.a.chambers@intel.com,
        gordon.mcfadden@intel.com, ahsan.atta@intel.com,
        fiona.trahe@intel.com, qat-linux@intel.com, kvm@vger.kernel.org,
        linux-crypto@vger.kernel.org, linux-pci@vger.kernel.org,
        linux-kernel@vger.kernel.org,
        Giovanni Cabiddu <giovanni.cabiddu@intel.com>
Subject: [PATCH v4 1/5] PCI: Add Intel QuickAssist device IDs
Date: Fri, 24 Jul 2020 09:47:56 +0100
Message-Id: <20200724084800.6136-2-giovanni.cabiddu@intel.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20200724084800.6136-1-giovanni.cabiddu@intel.com>
References: <20200724084800.6136-1-giovanni.cabiddu@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add device IDs for the following Intel QuickAssist devices: DH895XCC,
C3XXX and C62X.

The defines in this patch are going to be referenced in two independent
drivers, qat and vfio-pci.

Signed-off-by: Giovanni Cabiddu <giovanni.cabiddu@intel.com>
Acked-by: Bjorn Helgaas <bhelgaas@google.com>
---
 include/linux/pci_ids.h | 6 ++++++
 1 file changed, 6 insertions(+)

```
#### [PATCH v5 1/5] PCI: Add Intel QuickAssist device IDs
##### From: Giovanni Cabiddu <giovanni.cabiddu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Giovanni Cabiddu <giovanni.cabiddu@intel.com>
X-Patchwork-Id: 11682997
Return-Path: <SRS0=BqhU=BD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 685D5138A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Jul 2020 10:56:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4FECF20771
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Jul 2020 10:56:15 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726992AbgGXK4O (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 24 Jul 2020 06:56:14 -0400
Received: from mga03.intel.com ([134.134.136.65]:6908 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726258AbgGXK4N (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 24 Jul 2020 06:56:13 -0400
IronPort-SDR: 
 e/8eBRYezjBh+0lktMOhjPfBVoq6ciPmzD0+mwgKHbzMoxGwaOM6uw/GOp0NN4cGorjsMyFLh9
 xIRgdjy1IiKg==
X-IronPort-AV: E=McAfee;i="6000,8403,9691"; a="150675014"
X-IronPort-AV: E=Sophos;i="5.75,390,1589266800";
   d="scan'208";a="150675014"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga003.jf.intel.com ([10.7.209.27])
  by orsmga103.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 24 Jul 2020 03:56:13 -0700
IronPort-SDR: 
 p/ePnwyeQJlPOPOiNEifMstkJkp29RfObeMal3Y9DDC/ZvxkKARaOYCK0PMiI4Lp9eOKKR0asg
 h7Jv0QUiNQ5A==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,390,1589266800";
   d="scan'208";a="284901521"
Received: from silpixa00400314.ir.intel.com (HELO
 silpixa00400314.ger.corp.intel.com) ([10.237.222.51])
  by orsmga003.jf.intel.com with ESMTP; 24 Jul 2020 03:56:10 -0700
From: Giovanni Cabiddu <giovanni.cabiddu@intel.com>
To: alex.williamson@redhat.com, herbert@gondor.apana.org.au
Cc: cohuck@redhat.com, nhorman@redhat.com, vdronov@redhat.com,
        bhelgaas@google.com, mark.a.chambers@intel.com,
        gordon.mcfadden@intel.com, ahsan.atta@intel.com,
        fiona.trahe@intel.com, qat-linux@intel.com, kvm@vger.kernel.org,
        linux-crypto@vger.kernel.org, linux-pci@vger.kernel.org,
        linux-kernel@vger.kernel.org,
        Giovanni Cabiddu <giovanni.cabiddu@intel.com>
Subject: [PATCH v5 1/5] PCI: Add Intel QuickAssist device IDs
Date: Fri, 24 Jul 2020 11:55:56 +0100
Message-Id: <20200724105600.10814-2-giovanni.cabiddu@intel.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20200724105600.10814-1-giovanni.cabiddu@intel.com>
References: <20200724105600.10814-1-giovanni.cabiddu@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add device IDs for the following Intel QuickAssist devices: DH895XCC,
C3XXX and C62X.

The defines in this patch are going to be referenced in two independent
drivers, qat and vfio-pci.

Signed-off-by: Giovanni Cabiddu <giovanni.cabiddu@intel.com>
Acked-by: Bjorn Helgaas <bhelgaas@google.com>
Reviewed-by: Fiona Trahe <fiona.trahe@intel.com>
---
 include/linux/pci_ids.h | 6 ++++++
 1 file changed, 6 insertions(+)

```
#### [PATCH v5 01/75] KVM: SVM: Add GHCB definitions
##### From: Joerg Roedel <joro@8bytes.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Joerg Roedel <joro@8bytes.org>
X-Patchwork-Id: 11683719
Return-Path: <SRS0=BqhU=BD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 98554618
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Jul 2020 16:11:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 85E0A206EB
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Jul 2020 16:11:28 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728021AbgGXQL2 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 24 Jul 2020 12:11:28 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:33410 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726754AbgGXQD7 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 24 Jul 2020 12:03:59 -0400
Received: from theia.8bytes.org (8bytes.org
 [IPv6:2a01:238:4383:600:38bc:a715:4b6d:a889])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 9A4ADC0619D3;
        Fri, 24 Jul 2020 09:03:59 -0700 (PDT)
Received: from cap.home.8bytes.org (p5b006776.dip0.t-ipconnect.de
 [91.0.103.118])
        (using TLSv1.3 with cipher TLS_AES_256_GCM_SHA384 (256/256 bits))
        (No client certificate requested)
        by theia.8bytes.org (Postfix) with ESMTPSA id 9412F6FA;
        Fri, 24 Jul 2020 18:03:56 +0200 (CEST)
From: Joerg Roedel <joro@8bytes.org>
To: x86@kernel.org
Cc: Joerg Roedel <joro@8bytes.org>, Joerg Roedel <jroedel@suse.de>,
        Tom Lendacky <thomas.lendacky@amd.com>, hpa@zytor.com,
        Andy Lutomirski <luto@kernel.org>,
        Dave Hansen <dave.hansen@linux.intel.com>,
        Peter Zijlstra <peterz@infradead.org>,
        Jiri Slaby <jslaby@suse.cz>,
        Dan Williams <dan.j.williams@intel.com>,
        Juergen Gross <jgross@suse.com>,
        Kees Cook <keescook@chromium.org>,
        David Rientjes <rientjes@google.com>,
        Cfir Cohen <cfir@google.com>,
        Erdem Aktas <erdemaktas@google.com>,
        Masami Hiramatsu <mhiramat@kernel.org>,
        Mike Stunes <mstunes@vmware.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Martin Radev <martin.b.radev@gmail.com>,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org
Subject: [PATCH v5 01/75] KVM: SVM: Add GHCB definitions
Date: Fri, 24 Jul 2020 18:02:22 +0200
Message-Id: <20200724160336.5435-2-joro@8bytes.org>
X-Mailer: git-send-email 2.27.0
In-Reply-To: <20200724160336.5435-1-joro@8bytes.org>
References: <20200724160336.5435-1-joro@8bytes.org>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Tom Lendacky <thomas.lendacky@amd.com>

Extend the vmcb_safe_area with SEV-ES fields and add a new
'struct ghcb' which will be used for guest-hypervisor communication.

Signed-off-by: Tom Lendacky <thomas.lendacky@amd.com>
Signed-off-by: Joerg Roedel <jroedel@suse.de>
---
 arch/x86/include/asm/svm.h | 45 +++++++++++++++++++++++++++++++++++++-
 arch/x86/kvm/svm/svm.c     |  2 ++
 2 files changed, 46 insertions(+), 1 deletion(-)

```
