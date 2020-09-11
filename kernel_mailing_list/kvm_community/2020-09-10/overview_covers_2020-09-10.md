

#### [PATCH 0/3 v2] KVM: SVM: Don't flush cache of encrypted pages if
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
From patchwork Thu Sep 10 02:22:08 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11766385
Return-Path: <SRS0=BU+x=CT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B5A0659D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Sep 2020 02:25:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9AD8C21D7E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Sep 2020 02:25:13 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="kIlxF7Dc"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730394AbgIJCYv (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 9 Sep 2020 22:24:51 -0400
Received: from userp2120.oracle.com ([156.151.31.85]:34576 "EHLO
        userp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1730797AbgIJCWg (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 9 Sep 2020 22:22:36 -0400
Received: from pps.filterd (userp2120.oracle.com [127.0.0.1])
        by userp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 08A2KrMv121139;
        Thu, 10 Sep 2020 02:22:31 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id; s=corp-2020-01-29;
 bh=js32OklEyd2b8i8qMTH9+2LrRCdizS72A7CcGfh2l2k=;
 b=kIlxF7Dc0PYsg716lm0qgqy6JtbMmtUi+u0sCvPhCf+DxQ3H0e2jkhhzmuM9n9TjT6hX
 yFJvrPUBZyQEi9D0ERH1xelZ2KXGXjM2C20CwO9iABhm3XA1t9PJzjaSQmJWyxNotIrB
 3E0erdgSAfBnCi3OPEKie+autyMDpfkVW8tlbmVFcSWFu48ho+UnO0iY1GV+6lFGihU3
 9KWeGpeMNZZ9Vn2iUgUfHniiCK7pgQGvwyxKmpK+Q0ZYSq+XpACgzCjbgY5AksEpXe12
 VyiopxlXRu9wbnoqmWgPPdTZar9ZV4D5uGjKO3jkab9ykU+3cu/CUY8NsW12/oITu+w1 zQ==
Received: from aserp3020.oracle.com (aserp3020.oracle.com [141.146.126.70])
        by userp2120.oracle.com with ESMTP id 33c3an5513-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=FAIL);
        Thu, 10 Sep 2020 02:22:30 +0000
Received: from pps.filterd (aserp3020.oracle.com [127.0.0.1])
        by aserp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 08A2L6d9023070;
        Thu, 10 Sep 2020 02:22:30 GMT
Received: from aserv0122.oracle.com (aserv0122.oracle.com [141.146.126.236])
        by aserp3020.oracle.com with ESMTP id 33cmk88web-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 10 Sep 2020 02:22:30 +0000
Received: from abhmp0013.oracle.com (abhmp0013.oracle.com [141.146.116.19])
        by aserv0122.oracle.com (8.14.4/8.14.4) with ESMTP id 08A2MTUc012664;
        Thu, 10 Sep 2020 02:22:29 GMT
Received: from nsvm-sadhukhan-1.osdevelopmeniad.oraclevcn.com
 (/100.100.230.216)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Wed, 09 Sep 2020 19:22:29 -0700
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com, thomas.lendacky@amd.com
Subject: [PATCH 0/3 v2] KVM: SVM: Don't flush cache of encrypted pages if
 hardware enforces cache coherency
Date: Thu, 10 Sep 2020 02:22:08 +0000
Message-Id: <20200910022211.5417-1-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.18.4
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9739
 signatures=668679
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 spamscore=0
 malwarescore=0 phishscore=0
 mlxlogscore=752 bulkscore=0 adultscore=0 mlxscore=0 suspectscore=1
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2006250000
 definitions=main-2009100020
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9739
 signatures=668679
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 phishscore=0
 priorityscore=1501
 clxscore=1015 bulkscore=0 malwarescore=0 lowpriorityscore=0
 mlxlogscore=767 suspectscore=1 adultscore=0 mlxscore=0 impostorscore=0
 spamscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2009100020
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

v1 -> v2:
	1. Patch# 2 is the new addition. It adds the hardware-enforced cache
	   coherency as a CPUID feature.
	2. Patch# 3 (which was pach# 2 in v1) also adds the check to
	   __set_memory_enc_dec() so that cache/TLB is flushed only if
	   hardware doesn't enforce cache coherency.


[PATCH 1/3 v2] KVM: SVM: Replace numeric value for SME CPUID leaf with a
[PATCH 2/3 v2] KVM: SVM: Add hardware-enforced cache coherency as a
[PATCH 3/3 v2] KVM: SVM: Don't flush cache of encrypted pages if

 arch/x86/boot/compressed/mem_encrypt.S | 5 +++--
 arch/x86/include/asm/cpufeatures.h     | 6 ++++++
 arch/x86/kernel/cpu/amd.c              | 5 ++++-
 arch/x86/kernel/cpu/scattered.c        | 4 ++--
 arch/x86/kvm/cpuid.c                   | 2 +-
 arch/x86/kvm/svm/sev.c                 | 3 ++-
 arch/x86/kvm/svm/svm.c                 | 4 ++--
 arch/x86/mm/mem_encrypt_identity.c     | 4 ++--
 arch/x86/mm/pat/set_memory.c           | 6 ++++--
 9 files changed, 26 insertions(+), 13 deletions(-)

Krish Sadhukhan (3):
      KVM: SVM: Replace numeric value for SME CPUID leaf with a #define
      KVM: SVM: Add hardware-enforced cache coherency as a CPUID feature
      KVM: SVM: Don't flush cache of encrypted pages if hardware enforces cache 
coherenc
```
#### [PATCH 0/6] misc: Some inclusive terminology changes
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>

```c
From patchwork Thu Sep 10 07:01:25 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
 <philmd@redhat.com>
X-Patchwork-Id: 11766785
Return-Path: <SRS0=BU+x=CT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0C89D59D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Sep 2020 07:05:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E404A207EA
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Sep 2020 07:05:11 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="GWjYsRTr"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730400AbgIJHFE (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 10 Sep 2020 03:05:04 -0400
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:43406 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1730225AbgIJHBx (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 10 Sep 2020 03:01:53 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1599721297;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=Y1vGmD/fvsXEOWa6wkRKs3aLydzIceOGg7Tbh5f+UXQ=;
        b=GWjYsRTrA+NnxLIECRMVdbYv0rX9n/OjSIMEmuL36MAooVd+C2d5d/Mmtc20YCUQh2dHe7
        uznluxpwZIPTOi4BwtjK7RhVkJ3zwmoGwPkbZO7xGDBqfqJ0ZTZzX53Q4BH1W0hQ2kH9Uy
        //26XvyVJxHD7EUN7bpJLF09yCgSWwo=
Received: from mail-wm1-f72.google.com (mail-wm1-f72.google.com
 [209.85.128.72]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-451-2JdGbL8qNYy-AdHQrg1j7Q-1; Thu, 10 Sep 2020 03:01:35 -0400
X-MC-Unique: 2JdGbL8qNYy-AdHQrg1j7Q-1
Received: by mail-wm1-f72.google.com with SMTP id k12so551651wmj.1
        for <kvm@vger.kernel.org>; Thu, 10 Sep 2020 00:01:35 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=Y1vGmD/fvsXEOWa6wkRKs3aLydzIceOGg7Tbh5f+UXQ=;
        b=CtKLpr6IFbIVKVR8Vm1to7NuqVhqB9/S89/K0MdorF+FzlnkMoKINPjTeoCgEJ2t/7
         mFBfPZ1oIZUsYY1iMnzTuT8VtzaPsloabTubz7dImSPorluLO+IS2qojQ9SR2Rwji9rj
         j4h6FsGrpz0Fj39ClR5+s1hFXns0SC7WhFGAmwKks0dJ5PGQgq6ZTYEJxWUkxNRQXkIx
         PFz1lyPBXvhJ0DJ1wipAaf0I9wM0oH0M1OHmgg9OpgWF6FyCuBiC5MOsRzz5wMde35qg
         zkIrMnL1JqcRQQ1Ic1IRQZqykyb2tW50CkNbZJVxjmlkqN6SbU5vG0/Y/G9AnpuLDNco
         PQeg==
X-Gm-Message-State: AOAM530uspX5ELhrsm90YeIS4Z2ON99PVSb9UalEKtY8RtqtG3+/NRhZ
        gAxhCZx25nRmOJsRXpzYInaa1PqTBqo1EYMQOZrAqTMHkzlvc8QL7rArBnjfYb5i3Cm+rJd90k3
        LmP0PdwwKnixW
X-Received: by 2002:adf:f2d0:: with SMTP id d16mr7037146wrp.332.1599721294399;
        Thu, 10 Sep 2020 00:01:34 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJxOgVJywoHM/rmr+qzXsusn/6m5n3bTGfi1VzgpHQxefWx1TwErPpn8kQ+0ho5qhfDSLK+sVw==
X-Received: by 2002:adf:f2d0:: with SMTP id d16mr7037127wrp.332.1599721294215;
        Thu, 10 Sep 2020 00:01:34 -0700 (PDT)
Received: from x1w.redhat.com (65.red-83-57-170.dynamicip.rima-tde.net.
 [83.57.170.65])
        by smtp.gmail.com with ESMTPSA id
 c14sm7314726wrv.12.2020.09.10.00.01.32
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 10 Sep 2020 00:01:33 -0700 (PDT)
From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>
To: qemu-devel@nongnu.org
Cc: =?utf-8?q?Alex_Benn=C3=A9e?= <alex.bennee@linaro.org>,
 kvm@vger.kernel.org, qemu-arm@nongnu.org,
 Marcelo Tosatti <mtosatti@redhat.com>,
 "Edgar E. Iglesias" <edgar.iglesias@gmail.com>,
 "Michael S. Tsirkin" <mst@redhat.com>,
 =?utf-8?q?C=C3=A9dric_Le_Goater?= <clg@kaod.org>,
 Marcel Apfelbaum <marcel.apfelbaum@gmail.com>,
 Laurent Vivier <lvivier@redhat.com>,
 Peter Maydell <peter.maydell@linaro.org>, Andrew Jeffery <andrew@aj.id.au>,
 Jason Wang <jasowang@redhat.com>, Thomas Huth <thuth@redhat.com>,
 Alistair Francis <alistair@alistair23.me>, qemu-trivial@nongnu.org,
 Eduardo Habkost <ehabkost@redhat.com>, Richard Henderson <rth@twiddle.net>,
 Joel Stanley <joel@jms.id.au>, Paolo Bonzini <pbonzini@redhat.com>,
	=?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>
Subject: [PATCH 0/6] misc: Some inclusive terminology changes
Date: Thu, 10 Sep 2020 09:01:25 +0200
Message-Id: <20200910070131.435543-1-philmd@redhat.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We don't have (yet?) inclusive terminology guidelines,
but the PCI hole memory is not "black", the DMA sources
don't stream to "slaves", and there isn't really a TSX
"black" list, we only check for broken fields.

As this terms can be considered offensive, and changing
them is a no-brain operation, simply do it.

Philippe Mathieu-Daudé (6):
  hw/ssi/aspeed_smc: Rename max_slaves as max_devices
  hw/core/stream: Rename StreamSlave as StreamSink
  hw/dma/xilinx_axidma: Rename StreamSlave as StreamSink
  hw/net/xilinx_axienet: Rename StreamSlave as StreamSink
  hw/pci-host/q35: Rename PCI 'black hole as '(memory) hole'
  target/i386/kvm: Rename host_tsx_blacklisted() as host_tsx_broken()

 include/hw/pci-host/q35.h     |  4 +--
 include/hw/ssi/aspeed_smc.h   |  2 +-
 include/hw/ssi/xilinx_spips.h |  2 +-
 include/hw/stream.h           | 46 +++++++++++++--------------
 hw/core/stream.c              | 20 ++++++------
 hw/dma/xilinx_axidma.c        | 58 +++++++++++++++++------------------
 hw/net/xilinx_axienet.c       | 44 +++++++++++++-------------
 hw/pci-host/q35.c             | 38 +++++++++++------------
 hw/ssi/aspeed_smc.c           | 40 ++++++++++++------------
 hw/ssi/xilinx_spips.c         |  2 +-
 target/i386/kvm.c             |  4 +--
 tests/qtest/q35-test.c        |  2 +-
 12 files changed, 131 insertions(+), 131 deletions(-)
```
#### [RFC v3 0/2] add bus lock VM exit support
##### From: Chenyi Qiang <chenyi.qiang@intel.com>

```c
From patchwork Thu Sep 10 08:37:49 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Chenyi Qiang <chenyi.qiang@intel.com>
X-Patchwork-Id: 11767103
Return-Path: <SRS0=BU+x=CT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6DB48746
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Sep 2020 08:37:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5594520872
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Sep 2020 08:37:14 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730206AbgIJIgk (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 10 Sep 2020 04:36:40 -0400
Received: from mga07.intel.com ([134.134.136.100]:48998 "EHLO mga07.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1730346AbgIJIfq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 10 Sep 2020 04:35:46 -0400
IronPort-SDR: 
 oKWDyBjojvbgK3SNWUf6HyewwVHFW60J/EJcQQk4sRLzRYLO7PgvJLm0NTRnoYVm0Yk4qxqI/d
 kWVMWKsmm0Bg==
X-IronPort-AV: E=McAfee;i="6000,8403,9739"; a="222691425"
X-IronPort-AV: E=Sophos;i="5.76,412,1592895600";
   d="scan'208";a="222691425"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga004.fm.intel.com ([10.253.24.48])
  by orsmga105.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 10 Sep 2020 01:35:43 -0700
IronPort-SDR: 
 BTIMnXWE+znZbEUeoD4BA2CV+WEJFdC4OUy+ocjqMKI4jNZqnmA2BNleP0I/YjZWV8w5bD7Cg2
 vf5HoTnDUupg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.76,412,1592895600";
   d="scan'208";a="329255926"
Received: from chenyi-pc.sh.intel.com ([10.239.159.72])
  by fmsmga004.fm.intel.com with ESMTP; 10 Sep 2020 01:35:41 -0700
From: Chenyi Qiang <chenyi.qiang@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Xiaoyao Li <xiaoyao.li@intel.com>
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [RFC v3 0/2] add bus lock VM exit support
Date: Thu, 10 Sep 2020 16:37:49 +0800
Message-Id: <20200910083751.26686-1-chenyi.qiang@intel.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

v2->v3 changelogs:
- use a bitmap to get/set the capability of bus lock detection. we support
  exit and off mode currently.
- put the handle of exiting to userspace in vmx.c, thus no need to
  define a shadow to track vmx->exit_reason.bus_lock_detected.
- remove the vcpu->stats.bus_locks since every bus lock exits to userspace.
---

Add the support for bus lock VM exit in KVM. It is a sub-feature of bus
lock detection and the detailed info can be found in the patch 2/2.

In this patch series, the first patch applies Sean's refactor to
vcpu_vmx.exit_reason available at
https://patchwork.kernel.org/patch/11500659.
It is necessary as bus lock VM exit adds a new modifier bit(bit 26) in
exit_reason field in VMCS.

The second patch is the enabling work for bus lock VM exit. Add the
support to set the capability to enable bus lock vm exit. The current
implementation just exit to user space when handling the bus lock
detected in guest.

The concrete throttling policy in user space still needs to be
discussed. We can enforce ratelimit on bus lock in guest, just inject
some sleep time, or maybe other ideas.

Document for Bus Lock Detection is now available at the latest "Intel
Architecture Instruction Set Extensions Programming Reference" (see
below). Note that the section 9.1 for Bus Lock Debug Exception requires
modification due to the feedback from kernel community:
https://lore.kernel.org/lkml/87r1stmi1x.fsf@nanos.tec.linutronix.de/

Document Link:
https://software.intel.com/content/www/us/en/develop/download/intel-architecture-instruction-set-extensions-programming-reference.html

Chenyi Qiang (1):
  KVM: VMX: Enable bus lock VM exit

Sean Christopherson (1):
  KVM: VMX: Convert vcpu_vmx.exit_reason to a union

 arch/x86/include/asm/kvm_host.h    |   5 ++
 arch/x86/include/asm/vmx.h         |   1 +
 arch/x86/include/asm/vmxfeatures.h |   1 +
 arch/x86/include/uapi/asm/kvm.h    |   1 +
 arch/x86/include/uapi/asm/vmx.h    |   4 +-
 arch/x86/kvm/vmx/capabilities.h    |   6 ++
 arch/x86/kvm/vmx/nested.c          |  42 ++++++++----
 arch/x86/kvm/vmx/vmx.c             | 106 ++++++++++++++++++++---------
 arch/x86/kvm/vmx/vmx.h             |  25 ++++++-
 arch/x86/kvm/x86.c                 |  27 +++++++-
 arch/x86/kvm/x86.h                 |   5 ++
 include/uapi/linux/kvm.h           |   7 ++
 12 files changed, 179 insertions(+), 51 deletions(-)
```
#### [PATCH v12 0/2] s390: virtio: let arch validate VIRTIO features
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
From patchwork Thu Sep 10 08:53:48 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 11767143
Return-Path: <SRS0=BU+x=CT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EF209618
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Sep 2020 08:55:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CE51421941
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Sep 2020 08:55:40 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="KaavuZCI"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730315AbgIJIy0 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 10 Sep 2020 04:54:26 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:27734 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1729781AbgIJIyL (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 10 Sep 2020 04:54:11 -0400
Received: from pps.filterd (m0098420.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 08A8VI6C181275;
        Thu, 10 Sep 2020 04:53:58 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id; s=pp1;
 bh=pU4urWtsbWSPa4r0ZU3rhdfIMKoqDCYrwScAUEWZXjs=;
 b=KaavuZCIjVlnsJN3Ls5rqbo1Hu+17oC1wBEveZCYRHbgadEvSh+Y+jE6TB010Cr/AeZU
 XPf47WFBjGFsvmIv1he2228+NY4NbU/ZOjq1WTlpYvIfsUAC4iVivUB5B3EdxRZLLZxR
 oFAT2JtTXhB57M1f7PWMiELV1jS92xLsdaTwZvtxzV3NHhbO+Jsz63ThLJWTq83nHBiE
 lbLtUioXmvKIiyErnTkWEkUevP/K2I0JZRHfGXxDZ7br2GJrJDYvqX1CyJllmpfh3L8V
 oXLqqy5wGeiAs6eSMmzwqtY8UFl/rQc9nkHGYeFzi0SyfHIJBUpAq/r1ikzg3oia+79H yw==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 33fg6q1pt0-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 10 Sep 2020 04:53:57 -0400
Received: from m0098420.ppops.net (m0098420.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 08A8WnpR186593;
        Thu, 10 Sep 2020 04:53:57 -0400
Received: from ppma06ams.nl.ibm.com (66.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.102])
        by mx0b-001b2d01.pphosted.com with ESMTP id 33fg6q1psg-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 10 Sep 2020 04:53:57 -0400
Received: from pps.filterd (ppma06ams.nl.ibm.com [127.0.0.1])
        by ppma06ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 08A8rci9005421;
        Thu, 10 Sep 2020 08:53:55 GMT
Received: from b06cxnps3074.portsmouth.uk.ibm.com
 (d06relay09.portsmouth.uk.ibm.com [9.149.109.194])
        by ppma06ams.nl.ibm.com with ESMTP id 33dxdr319g-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 10 Sep 2020 08:53:55 +0000
Received: from d06av25.portsmouth.uk.ibm.com (d06av25.portsmouth.uk.ibm.com
 [9.149.105.61])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 08A8rqgW39780724
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 10 Sep 2020 08:53:52 GMT
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 9586711C052;
        Thu, 10 Sep 2020 08:53:52 +0000 (GMT)
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id CC94C11C054;
        Thu, 10 Sep 2020 08:53:51 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.28.144])
        by d06av25.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Thu, 10 Sep 2020 08:53:51 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: linux-kernel@vger.kernel.org
Cc: pasic@linux.ibm.com, borntraeger@de.ibm.com, frankja@linux.ibm.com,
        mst@redhat.com, jasowang@redhat.com, cohuck@redhat.com,
        kvm@vger.kernel.org, linux-s390@vger.kernel.org,
        virtualization@lists.linux-foundation.org, thomas.lendacky@amd.com,
        david@gibson.dropbear.id.au, linuxram@us.ibm.com,
        hca@linux.ibm.com, gor@linux.ibm.com
Subject: [PATCH v12 0/2] s390: virtio: let arch validate VIRTIO features
Date: Thu, 10 Sep 2020 10:53:48 +0200
Message-Id: <1599728030-17085-1-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-09-10_01:2020-09-10,2020-09-10 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 spamscore=0 mlxlogscore=991
 clxscore=1015 adultscore=0 priorityscore=1501 lowpriorityscore=0
 impostorscore=0 malwarescore=0 phishscore=0 mlxscore=0 bulkscore=0
 suspectscore=1 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2009100074
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all,

The goal of the series is to give a chance to the architecture
to validate VIRTIO device features.

I changed VIRTIO_F_IOMMU_PLATFORM to VIRTIO_F_ACCESS_PLATFORM
I forgot in drivers/virtio/Kconfig, and put back the inclusion
of virtio_config.h for the definition of the callback in
arch/s390/mm/init.c I wrongly removed in the last series.

Regards,
Pierre


Pierre Morel (2):
  virtio: let arch advertise guest's memory access restrictions
  s390: virtio: PV needs VIRTIO I/O device protection

 arch/s390/Kconfig             |  1 +
 arch/s390/mm/init.c           | 11 +++++++++++
 drivers/virtio/Kconfig        |  6 ++++++
 drivers/virtio/virtio.c       | 15 +++++++++++++++
 include/linux/virtio_config.h | 10 ++++++++++
 5 files changed, 43 insertions(+)
```
#### [PATCH v2 0/9] KVM: collect sporadic patches
##### From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>

```c
From patchwork Thu Sep 10 09:50:35 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11767281
Return-Path: <SRS0=BU+x=CT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 38A6392C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Sep 2020 09:51:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1046C20882
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Sep 2020 09:51:08 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="bT2deRD9"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730293AbgIJJvB (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 10 Sep 2020 05:51:01 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:40654 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729781AbgIJJu6 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 10 Sep 2020 05:50:58 -0400
Received: from mail-pf1-x443.google.com (mail-pf1-x443.google.com
 [IPv6:2607:f8b0:4864:20::443])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 30099C061573;
        Thu, 10 Sep 2020 02:50:58 -0700 (PDT)
Received: by mail-pf1-x443.google.com with SMTP id d9so4329841pfd.3;
        Thu, 10 Sep 2020 02:50:58 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=OgkTz9HeACnxw9UKomrR35bJybah4ILZigVJyKdJFAk=;
        b=bT2deRD9cdMr7UlHENM4BxShWiRI2zk5deFCpYY9GDQ/c2k6s1Ffh5MJQmx7OM+EeM
         woUytm2M5vOcJ6/T8E0PshQL7GSAIo9mE9i9slya6VfDSE5Jwb6RiTB9BZLuFd9oohZL
         FjExujdtHQbFw7MT517OEGcfF2xaeb+Tg+4hnBiddMJQgTDDKPKYHvK8lAcOkI4ds3qm
         YFDG0int/YhiYxw3WEWoqKPgh4WHDD2na+V+wGVHZ2cL+1nf9S8ftHobuFVdAXGNlZ4d
         ZYGwD3MONdsW/Pu8YK7NQ+OgmkQvOFZKw1g1hXI02M7pj9dwygSlZGAq5it4IG+30Wvr
         JAKQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=OgkTz9HeACnxw9UKomrR35bJybah4ILZigVJyKdJFAk=;
        b=ohx1u08PKJmcrGmlqvIZN2kTIsEugvrPL8lZtXY7l8AMuQJH8dkmk+uJQ2eP2VIzdG
         yVWc7g8TVnHHplB53g4jJmpBBti9xtNosb4hFuBVFSQ+QKV0um63MKaHqEcwsNwkQVhE
         hb8AY+tFBRMjk3Ed218OH+9PzZzX5Iajj/8iZetN0P+IuPQJCuvZUgrTIMZyILZ0hrrz
         RL944qQtYzbUGNa0ResQg6y4Yr1gsLF4/yg/bXffJINecz88nq9cG5AoGfrAnYHKHBfg
         e49xwLNiQTcQr0KdHXlJCXiuJ37TwLiz+65uiudBgtoljrlG9cmVD6BnDzaLNZdqao0U
         Vg8A==
X-Gm-Message-State: AOAM532ukEXyiFUWD+9Ei3uwFYYk48tGThC1msgSTHIXG66ol6Tv4ShK
        rBU2DrfYQiYas6WfRzYXkgP0pxw/cpw=
X-Google-Smtp-Source: 
 ABdhPJyYpFpYKlL5dwUrH8CJ5X/Nzsu7FTw6xwzLZxscv4LQXYoiisi3Raz6kgq1x8doMUPwZgHWFA==
X-Received: by 2002:a62:92c8:0:b029:13e:d13d:a106 with SMTP id
 o191-20020a6292c80000b029013ed13da106mr4754123pfd.34.1599731457503;
        Thu, 10 Sep 2020 02:50:57 -0700 (PDT)
Received: from localhost.localdomain ([103.7.29.6])
        by smtp.googlemail.com with ESMTPSA id
 e1sm2576534pfl.162.2020.09.10.02.50.54
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Thu, 10 Sep 2020 02:50:56 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>
Subject: [PATCH v2 0/9] KVM: collect sporadic patches
Date: Thu, 10 Sep 2020 17:50:35 +0800
Message-Id: <1599731444-3525-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Collect sporadic patches for easy apply.

Wanpeng Li (9):
  KVM: LAPIC: Return 0 when getting the tscdeadline timer if the lapic
    is hw disabled
  KVM: LAPIC: Guarantee the timer is in tsc-deadline mode when setting
  KVM: LAPIC: Fix updating DFR missing apic map recalculation
  KVM: VMX: Don't freeze guest when event delivery causes an APIC-access
    exit
  KVM: LAPIC: Narrow down the kick target vCPU
  KVM: LAPIC: Reduce world switch latency caused by timer_advance_ns
  KVM: SVM: Get rid of handle_fastpath_set_msr_irqoff()
  KVM: SVM: Move svm_complete_interrupts() into svm_vcpu_run()
  KVM: SVM: Reenable handle_fastpath_set_msr_irqoff() after
    complete_interrupts()

 arch/x86/kvm/lapic.c   | 36 ++++++++++++++++++++----------------
 arch/x86/kvm/svm/svm.c | 17 +++++++++--------
 arch/x86/kvm/vmx/vmx.c |  5 ++---
 arch/x86/kvm/x86.c     |  6 ------
 arch/x86/kvm/x86.h     |  1 -
 5 files changed, 31 insertions(+), 34 deletions(-)
```
#### [PATCH v7 00/16] vfio: expose virtual Shared Virtual Addressing to
##### From: Liu Yi L <yi.l.liu@intel.com>

```c
From patchwork Thu Sep 10 10:45:17 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Liu Yi L <yi.l.liu@intel.com>
X-Patchwork-Id: 11767473
Return-Path: <SRS0=BU+x=CT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C23DC112E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Sep 2020 10:44:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AB3E2214F1
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Sep 2020 10:44:27 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729913AbgIJKoU (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 10 Sep 2020 06:44:20 -0400
Received: from mga06.intel.com ([134.134.136.31]:21893 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727096AbgIJKnu (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 10 Sep 2020 06:43:50 -0400
IronPort-SDR: 
 9KToOdOKvraopMhKOXS9YX3gPZPCjLl3Fwzy4XSJ5tKPk4fre3lgkSezVjPZFu31lzjplQgVVR
 imHp8OHDQiCg==
X-IronPort-AV: E=McAfee;i="6000,8403,9739"; a="220066279"
X-IronPort-AV: E=Sophos;i="5.76,412,1592895600";
   d="scan'208";a="220066279"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by orsmga104.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 10 Sep 2020 03:43:34 -0700
IronPort-SDR: 
 BoBfQH2abEHYFgrr4rVF7AtQq5PSRnjpEKEpI1/cnqKP71uawlMvFzD2YiBWpxiv9UH/HlaRFF
 8s61QLfYNXPA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.76,412,1592895600";
   d="scan'208";a="334137177"
Received: from jacob-builder.jf.intel.com ([10.7.199.155])
  by orsmga008.jf.intel.com with ESMTP; 10 Sep 2020 03:43:34 -0700
From: Liu Yi L <yi.l.liu@intel.com>
To: alex.williamson@redhat.com, eric.auger@redhat.com,
        baolu.lu@linux.intel.com, joro@8bytes.org
Cc: kevin.tian@intel.com, jacob.jun.pan@linux.intel.com,
        ashok.raj@intel.com, yi.l.liu@intel.com, jun.j.tian@intel.com,
        yi.y.sun@intel.com, jean-philippe@linaro.org, peterx@redhat.com,
        jasowang@redhat.com, hao.wu@intel.com, stefanha@gmail.com,
        iommu@lists.linux-foundation.org, kvm@vger.kernel.org
Subject: [PATCH v7 00/16] vfio: expose virtual Shared Virtual Addressing to
 VMs
Date: Thu, 10 Sep 2020 03:45:17 -0700
Message-Id: <1599734733-6431-1-git-send-email-yi.l.liu@intel.com>
X-Mailer: git-send-email 2.7.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Shared Virtual Addressing (SVA), a.k.a, Shared Virtual Memory (SVM) on
Intel platforms allows address space sharing between device DMA and
applications. SVA can reduce programming complexity and enhance security.

This VFIO series is intended to expose SVA usage to VMs. i.e. Sharing
guest application address space with passthru devices. This is called
vSVA in this series. The whole vSVA enabling requires QEMU/VFIO/IOMMU
changes. For IOMMU and QEMU changes, they are in separate series (listed
in the "Related series").

The high-level architecture for SVA virtualization is as below, the key
design of vSVA support is to utilize the dual-stage IOMMU translation (
also known as IOMMU nesting translation) capability in host IOMMU.


    .-------------.  .---------------------------.
    |   vIOMMU    |  | Guest process CR3, FL only|
    |             |  '---------------------------'
    .----------------/
    | PASID Entry |--- PASID cache flush -
    '-------------'                       |
    |             |                       V
    |             |                CR3 in GPA
    '-------------'
Guest
------| Shadow |--------------------------|--------
      v        v                          v
Host
    .-------------.  .----------------------.
    |   pIOMMU    |  | Bind FL for GVA-GPA  |
    |             |  '----------------------'
    .----------------/  |
    | PASID Entry |     V (Nested xlate)
    '----------------\.------------------------------.
    |             |   |SL for GPA-HPA, default domain|
    |             |   '------------------------------'
    '-------------'
Where:
 - FL = First level/stage one page tables
 - SL = Second level/stage two page tables

Patch Overview:
 1. reports IOMMU nesting info to userspace ( patch 0001, 0002, 0003, 0015 , 0016)
 2. vfio support for PASID allocation and free for VMs (patch 0004, 0005, 0007)
 3. a fix to a revisit in intel iommu driver (patch 0006)
 4. vfio support for binding guest page table to host (patch 0008, 0009, 0010)
 5. vfio support for IOMMU cache invalidation from VMs (patch 0011)
 6. vfio support for vSVA usage on IOMMU-backed mdevs (patch 0012)
 7. expose PASID capability to VM (patch 0013)
 8. add doc for VFIO dual stage control (patch 0014)

The complete vSVA kernel upstream patches are divided into three phases:
    1. Common APIs and PCI device direct assignment
    2. IOMMU-backed Mediated Device assignment
    3. Page Request Services (PRS) support

This patchset is aiming for the phase 1 and phase 2, and based on Jacob's
below series.
*) [PATCH v8 0/7] IOMMU user API enhancement - wip
   https://lore.kernel.org/linux-iommu/1598898300-65475-1-git-send-email-jacob.jun.pan@linux.intel.com/

*) [PATCH v2 0/9] IOASID extensions for guest SVA - wip
   https://lore.kernel.org/linux-iommu/1598070918-21321-1-git-send-email-jacob.jun.pan@linux.intel.com/

Complete set for current vSVA can be found in below branch.
https://github.com/luxis1999/linux-vsva.git vsva-linux-5.9-rc2-v7

The corresponding QEMU patch series is included in below branch:
https://github.com/luxis1999/qemu.git vsva_5.9_rc2_qemu_rfcv10


Regards,
Yi Liu

Changelog:
	- Patch v6 -> Patch v7:
	  a) drop [PATCH v6 01/15] of v6 as it's merged by Alex.
	  b) rebase on Jacob's v8 IOMMU uapi enhancement and v2 IOASID extension patchset.
	  c) Address comments against v6 from Alex and Eric.
	  Patch v6: https://lore.kernel.org/kvm/1595917664-33276-1-git-send-email-yi.l.liu@intel.com/

	- Patch v5 -> Patch v6:
	  a) Address comments against v5 from Eric.
	  b) rebase on Jacob's v6 IOMMU uapi enhancement
	  Patch v5: https://lore.kernel.org/kvm/1594552870-55687-1-git-send-email-yi.l.liu@intel.com/

	- Patch v4 -> Patch v5:
	  a) Address comments against v4
	  Patch v4: https://lore.kernel.org/kvm/1593861989-35920-1-git-send-email-yi.l.liu@intel.com/

	- Patch v3 -> Patch v4:
	  a) Address comments against v3
	  b) Add rb from Stefan on patch 14/15
	  Patch v3: https://lore.kernel.org/kvm/1592988927-48009-1-git-send-email-yi.l.liu@intel.com/

	- Patch v2 -> Patch v3:
	  a) Rebase on top of Jacob's v3 iommu uapi patchset
	  b) Address comments from Kevin and Stefan Hajnoczi
	  c) Reuse DOMAIN_ATTR_NESTING to get iommu nesting info
	  d) Drop [PATCH v2 07/15] iommu/uapi: Add iommu_gpasid_unbind_data
	  Patch v2: https://lore.kernel.org/kvm/1591877734-66527-1-git-send-email-yi.l.liu@intel.com/

	- Patch v1 -> Patch v2:
	  a) Refactor vfio_iommu_type1_ioctl() per suggestion from Christoph
	     Hellwig.
	  b) Re-sequence the patch series for better bisect support.
	  c) Report IOMMU nesting cap info in detail instead of a format in
	     v1.
	  d) Enforce one group per nesting type container for vfio iommu type1
	     driver.
	  e) Build the vfio_mm related code from vfio.c to be a separate
	     vfio_pasid.ko.
	  f) Add PASID ownership check in IOMMU driver.
	  g) Adopted to latest IOMMU UAPI design. Removed IOMMU UAPI version
	     check. Added iommu_gpasid_unbind_data for unbind requests from
	     userspace.
	  h) Define a single ioctl:VFIO_IOMMU_NESTING_OP for bind/unbind_gtbl
	     and cahce_invld.
	  i) Document dual stage control in vfio.rst.
	  Patch v1: https://lore.kernel.org/kvm/1584880325-10561-1-git-send-email-yi.l.liu@intel.com/

	- RFC v3 -> Patch v1:
	  a) Address comments to the PASID request(alloc/free) path
	  b) Report PASID alloc/free availabitiy to user-space
	  c) Add a vfio_iommu_type1 parameter to support pasid quota tuning
	  d) Adjusted to latest ioasid code implementation. e.g. remove the
	     code for tracking the allocated PASIDs as latest ioasid code
	     will track it, VFIO could use ioasid_free_set() to free all
	     PASIDs.
	  RFC v3: https://lore.kernel.org/kvm/1580299912-86084-1-git-send-email-yi.l.liu@intel.com/

	- RFC v2 -> v3:
	  a) Refine the whole patchset to fit the roughly parts in this series
	  b) Adds complete vfio PASID management framework. e.g. pasid alloc,
	  free, reclaim in VM crash/down and per-VM PASID quota to prevent
	  PASID abuse.
	  c) Adds IOMMU uAPI version check and page table format check to ensure
	  version compatibility and hardware compatibility.
	  d) Adds vSVA vfio support for IOMMU-backed mdevs.
	  RFC v2: https://lore.kernel.org/kvm/1571919983-3231-1-git-send-email-yi.l.liu@intel.com/

	- RFC v1 -> v2:
	  Dropped vfio: VFIO_IOMMU_ATTACH/DETACH_PASID_TABLE.
	  RFC v1: https://lore.kernel.org/kvm/1562324772-3084-1-git-send-email-yi.l.liu@intel.com/
---
Eric Auger (1):
  vfio: Document dual stage control

Liu Yi L (14):
  iommu: Report domain nesting info
  iommu/smmu: Report empty domain nesting info
  vfio/type1: Report iommu nesting info to userspace
  vfio: Add PASID allocation/free support
  iommu/vt-d: Support setting ioasid set to domain
  iommu/vt-d: Remove get_task_mm() in bind_gpasid()
  vfio/type1: Add VFIO_IOMMU_PASID_REQUEST (alloc/free)
  iommu/vt-d: Check ownership for PASIDs from user-space
  vfio/type1: Support binding guest page tables to PASID
  vfio/type1: Allow invalidating first-level/stage IOMMU cache
  vfio/type1: Add vSVA support for IOMMU-backed mdevs
  vfio/pci: Expose PCIe PASID capability to guest
  iommu/vt-d: Only support nesting when nesting caps are consistent
    across iommu units
  iommu/vt-d: Support reporting nesting capability info

Yi Sun (1):
  iommu: Pass domain to sva_unbind_gpasid()

 Documentation/driver-api/vfio.rst           |  76 ++++++
 drivers/iommu/arm/arm-smmu-v3/arm-smmu-v3.c |  29 +-
 drivers/iommu/arm/arm-smmu/arm-smmu.c       |  29 +-
 drivers/iommu/intel/iommu.c                 | 137 +++++++++-
 drivers/iommu/intel/svm.c                   |  43 +--
 drivers/iommu/iommu.c                       |   2 +-
 drivers/vfio/Kconfig                        |   6 +
 drivers/vfio/Makefile                       |   1 +
 drivers/vfio/pci/vfio_pci_config.c          |   2 +-
 drivers/vfio/vfio_iommu_type1.c             | 395 +++++++++++++++++++++++++++-
 drivers/vfio/vfio_pasid.c                   | 283 ++++++++++++++++++++
 include/linux/intel-iommu.h                 |  25 +-
 include/linux/iommu.h                       |   4 +-
 include/linux/vfio.h                        |  54 ++++
 include/uapi/linux/iommu.h                  |  76 ++++++
 include/uapi/linux/vfio.h                   | 101 +++++++
 16 files changed, 1220 insertions(+), 43 deletions(-)
 create mode 100644 drivers/vfio/vfio_pasid.c
```
#### [PATCH v7 0/3] Add a vhost RPMsg API
##### From: Guennadi Liakhovetski <guennadi.liakhovetski@linux.intel.com>

```c
From patchwork Thu Sep 10 11:13:48 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Guennadi Liakhovetski
 <guennadi.liakhovetski@linux.intel.com>
X-Patchwork-Id: 11767667
Return-Path: <SRS0=BU+x=CT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 29A23746
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Sep 2020 11:39:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 14BA82145D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Sep 2020 11:39:01 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730316AbgIJLhq (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 10 Sep 2020 07:37:46 -0400
Received: from mga01.intel.com ([192.55.52.88]:26476 "EHLO mga01.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726847AbgIJLOk (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 10 Sep 2020 07:14:40 -0400
IronPort-SDR: 
 7KUKGb/2324GcA35o8NX9pdty2hZB4oQBpCboVdd/KGcEtRu4JXXpPmQIC/9Bwo815ZQvoQC1H
 ulsFmZqpxQaA==
X-IronPort-AV: E=McAfee;i="6000,8403,9739"; a="176571446"
X-IronPort-AV: E=Sophos;i="5.76,412,1592895600";
   d="scan'208";a="176571446"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by fmsmga101.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 10 Sep 2020 04:14:01 -0700
IronPort-SDR: 
 wVpIj/zGXtQNpFmAtAkeu91MGzSCLz/mzpLVf5KGOI2rCOahfd+o78fB05ua33jwPqEYLvwIqf
 lsXS7DYoJQ1w==
X-IronPort-AV: E=Sophos;i="5.76,412,1592895600";
   d="scan'208";a="286530910"
Received: from gliakhov-mobl2.ger.corp.intel.com (HELO
 ubuntu.ger.corp.intel.com) ([10.252.39.14])
  by fmsmga008-auth.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 10 Sep 2020 04:13:58 -0700
From: Guennadi Liakhovetski <guennadi.liakhovetski@linux.intel.com>
To: kvm@vger.kernel.org
Cc: linux-remoteproc@vger.kernel.org,
        virtualization@lists.linux-foundation.org,
        sound-open-firmware@alsa-project.org,
        Pierre-Louis Bossart <pierre-louis.bossart@linux.intel.com>,
        Liam Girdwood <liam.r.girdwood@linux.intel.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Jason Wang <jasowang@redhat.com>,
        Ohad Ben-Cohen <ohad@wizery.com>,
        Bjorn Andersson <bjorn.andersson@linaro.org>,
        Mathieu Poirier <mathieu.poirier@linaro.org>,
        Vincent Whitchurch <vincent.whitchurch@axis.com>
Subject: [PATCH v7 0/3] Add a vhost RPMsg API
Date: Thu, 10 Sep 2020 13:13:48 +0200
Message-Id: <20200910111351.20526-1-guennadi.liakhovetski@linux.intel.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

Next update:

v7:
- remove documentation update to be send separately
- address comments from Mathieu Poirier (thanks)

v6:
- rename include/linux/virtio_rpmsg.h -> include/linux/rpmsg/virtio.h

v5:
- don't hard-code message layout

v4:
- add endianness conversions to comply with the VirtIO standard

v3:
- address several checkpatch warnings
- address comments from Mathieu Poirier

v2:
- update patch #5 with a correct vhost_dev_init() prototype
- drop patch #6 - it depends on a different patch, that is currently
  an RFC
- address comments from Pierre-Louis Bossart:
  * remove "default n" from Kconfig

Linux supports RPMsg over VirtIO for "remote processor" / AMP use
cases. It can however also be used for virtualisation scenarios,
e.g. when using KVM to run Linux on both the host and the guests.
This patch set adds a wrapper API to facilitate writing vhost
drivers for such RPMsg-based solutions. The first use case is an
audio DSP virtualisation project, currently under development, ready
for review and submission, available at
https://github.com/thesofproject/linux/pull/1501/commits

Thanks
Guennadi

Guennadi Liakhovetski (3):
  vhost: convert VHOST_VSOCK_SET_RUNNING to a generic ioctl
  rpmsg: move common structures and defines to headers
  vhost: add an RPMsg API

 drivers/rpmsg/virtio_rpmsg_bus.c |  78 +------
 drivers/vhost/Kconfig            |   7 +
 drivers/vhost/Makefile           |   3 +
 drivers/vhost/rpmsg.c            | 370 +++++++++++++++++++++++++++++++
 drivers/vhost/vhost_rpmsg.h      |  74 +++++++
 include/linux/rpmsg/virtio.h     |  83 +++++++
 include/uapi/linux/rpmsg.h       |   3 +
 include/uapi/linux/vhost.h       |   4 +-
 8 files changed, 545 insertions(+), 77 deletions(-)
 create mode 100644 drivers/vhost/rpmsg.c
 create mode 100644 drivers/vhost/vhost_rpmsg.h
 create mode 100644 include/linux/rpmsg/virtio.h
```
#### [PATCH v5 0/3] vfio/pci: Restore MMIO access for s390 detached VFs
##### From: Matthew Rosato <mjrosato@linux.ibm.com>

```c
From patchwork Thu Sep 10 14:59:54 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Matthew Rosato <mjrosato@linux.ibm.com>
X-Patchwork-Id: 11769061
Return-Path: <SRS0=BU+x=CT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F1EE8698
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Sep 2020 20:10:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CCADC221E3
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Sep 2020 20:10:10 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="lJm0/tYK"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726911AbgIJUIk (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 10 Sep 2020 16:08:40 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:61852 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1730859AbgIJPAn (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 10 Sep 2020 11:00:43 -0400
Received: from pps.filterd (m0098413.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 08AEi4YI192630;
        Thu, 10 Sep 2020 11:00:07 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id; s=pp1;
 bh=5VXKsHTc2YlCV3PXBFCbmF1hTMHTSBXPxb9CKodxcuc=;
 b=lJm0/tYKVnLWLps2+W6cAz1a9vrIWBEiP+kwk1q2U+Ibr3tK9hHfmZoMaZ7sHL4AOzFG
 U8MF73hxTxtHjYbp0vBLEb92NkHzmKnOhS/u21GYrVf3OdLrsa7h7TQHZKyALnhekAjo
 nKXwusdMDgbyylGqJ1WSDugrkjpm2fcrQ+t0h8aSm/92l+ZV3JK/cliqzGPxJ4jZlzMZ
 da2I0XmeJAYCxvHw+l7r2ceDyk78W3+gRRTLx1nHTrEG94Euogl/XhE/by94e7BT5SNn
 48fbqOVVb7A3D2xgiKi3CzcaUtJ8k2udWAmivgmg0FDa3PkDt/Z/Kpfc5gNYS1a2gcgF zA==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 33fnyv0wgf-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 10 Sep 2020 11:00:07 -0400
Received: from m0098413.ppops.net (m0098413.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 08AEq17J025485;
        Thu, 10 Sep 2020 11:00:07 -0400
Received: from ppma03dal.us.ibm.com (b.bd.3ea9.ip4.static.sl-reverse.com
 [169.62.189.11])
        by mx0b-001b2d01.pphosted.com with ESMTP id 33fnyv0wew-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 10 Sep 2020 11:00:06 -0400
Received: from pps.filterd (ppma03dal.us.ibm.com [127.0.0.1])
        by ppma03dal.us.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 08AEqMb2000343;
        Thu, 10 Sep 2020 15:00:06 GMT
Received: from b03cxnp08027.gho.boulder.ibm.com
 (b03cxnp08027.gho.boulder.ibm.com [9.17.130.19])
        by ppma03dal.us.ibm.com with ESMTP id 33c2a9jbjd-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 10 Sep 2020 15:00:05 +0000
Received: from b03ledav004.gho.boulder.ibm.com
 (b03ledav004.gho.boulder.ibm.com [9.17.130.235])
        by b03cxnp08027.gho.boulder.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 08AF00At32702764
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 10 Sep 2020 15:00:00 GMT
Received: from b03ledav004.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 984DF7806E;
        Thu, 10 Sep 2020 15:00:02 +0000 (GMT)
Received: from b03ledav004.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 0909778064;
        Thu, 10 Sep 2020 15:00:00 +0000 (GMT)
Received: from oc4221205838.ibm.com (unknown [9.211.91.207])
        by b03ledav004.gho.boulder.ibm.com (Postfix) with ESMTP;
        Thu, 10 Sep 2020 15:00:00 +0000 (GMT)
From: Matthew Rosato <mjrosato@linux.ibm.com>
To: alex.williamson@redhat.com, bhelgaas@google.com
Cc: schnelle@linux.ibm.com, pmorel@linux.ibm.com, mpe@ellerman.id.au,
        oohall@gmail.com, cohuck@redhat.com, kevin.tian@intel.com,
        hca@linux.ibm.com, gor@linux.ibm.com, borntraeger@de.ibm.com,
        linux-s390@vger.kernel.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, linux-pci@vger.kernel.org
Subject: [PATCH v5 0/3] vfio/pci: Restore MMIO access for s390 detached VFs
Date: Thu, 10 Sep 2020 10:59:54 -0400
Message-Id: <1599749997-30489-1-git-send-email-mjrosato@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-09-10_03:2020-09-10,2020-09-10 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 adultscore=0
 lowpriorityscore=0 bulkscore=0 phishscore=0 impostorscore=0 clxscore=1015
 suspectscore=0 priorityscore=1501 mlxlogscore=864 spamscore=0 mlxscore=0
 malwarescore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2009100130
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Changes from v4:
- Switch from dev_flags to a bitfield
- Scrubbed improper use of MSE acronym
- Restored the fixes tag to patch 3 (but the other 2 patches are
  now pre-reqs -- cc stable 5.8?) 

Since commit abafbc551fdd ("vfio-pci: Invalidate mmaps and block MMIO
access on disabled memory") VFIO now rejects guest MMIO access when the
PCI_COMMAND_MEMORY bit is OFF.  This is however not the case for VFs
(fixed in commit ebfa440ce38b ("vfio/pci: Fix SR-IOV VF handling with
MMIO blocking")).  Furthermore, on s390 where we always run with at
least a bare-metal hypervisor (LPAR) PCI_COMMAND_MEMORY, unlike Device/
Vendor IDs and BARs, is not emulated when VFs are passed-through to the
OS independently.

Based upon Bjorn's most recent comment [1], I investigated the notion of
setting is_virtfn=1 for VFs passed-through to Linux and not linked to a
parent PF (referred to as a 'detached VF' in my prior post).  However,
we rapidly run into issues on how to treat an is_virtfn device with no
linked PF. Further complicating the issue is when you consider the guest
kernel has a passed-through VF but has CONFIG_PCI_IOV=n as in many 
locations is_virtfn checking is ifdef'd out altogether and the device is
assumed to be an independent PCI function.

The decision made by VFIO whether to require or emulate a PCI feature 
(in this case PCI_COMMAND_MEMORY) is based upon the knowledge it has 
about the device, including implicit expectations of what/is not
emulated below VFIO. (ex: is it safe to read vendor/id from config
space?) -- Our firmware layer attempts similar behavior by emulating
things such as vendor/id/BAR access - without these an unlinked VF would
not be usable. But what is or is not emulated by the layer below may be
different based upon which entity is providing the emulation (vfio,
LPAR, some other hypervisor)

So, the proposal here aims to fix the immediate issue of s390
pass-through VFs becoming suddenly unusable by vfio by using a new 
bit to identify a VF feature that we know is hardwired to 0 for any
VF (PCI_COMMAND_MEMORY) and de-coupling the need for emulating
PCI_COMMAND_MEMORY from the is_virtfn flag. The exact scope of is_virtfn
and physfn for bare-metal vs guest scenarios and identifying what
features are / are not emulated by the lower-level hypervisors is a much
bigger discussion independent of this limited proposal.

[1]: https://marc.info/?l=linux-pci&m=159856041930022&w=2



Matthew Rosato (3):
  PCI/IOV: Mark VFs as not implementing PCI_COMMAND_MEMORY
  s390/pci: Mark all VFs as not implementing PCI_COMMAND_MEMORY
  vfio/pci: Decouple PCI_COMMAND_MEMORY bit checks from is_virtfn

 arch/s390/pci/pci_bus.c            |  5 +++--
 drivers/pci/iov.c                  |  1 +
 drivers/vfio/pci/vfio_pci_config.c | 24 ++++++++++++++----------
 include/linux/pci.h                |  1 +
 4 files changed, 19 insertions(+), 12 deletions(-)
```
