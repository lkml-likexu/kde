#### [PATCH v6 1/4] vhost: convert VHOST_VSOCK_SET_RUNNING to a generic ioctl
##### From: Guennadi Liakhovetski <guennadi.liakhovetski@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Guennadi Liakhovetski
 <guennadi.liakhovetski@linux.intel.com>
X-Patchwork-Id: 11749291
Return-Path: <SRS0=IPmA=CK=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AB1AE109B
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  1 Sep 2020 17:23:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9E1F820BED
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  1 Sep 2020 17:23:31 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732592AbgIARXV (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 1 Sep 2020 13:23:21 -0400
Received: from mga07.intel.com ([134.134.136.100]:55893 "EHLO mga07.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727112AbgIAPL7 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 1 Sep 2020 11:11:59 -0400
IronPort-SDR: 
 7m7f6xU7N+UzjPxmzEoY+7C5UQHr7sBI1Dp/RUxBYiWZv/spVNe6t+FB+wXwEX1NYzCvgTVn5i
 qlWR4SNoE7AA==
X-IronPort-AV: E=McAfee;i="6000,8403,9730"; a="221408208"
X-IronPort-AV: E=Sophos;i="5.76,379,1592895600";
   d="scan'208";a="221408208"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga006.fm.intel.com ([10.253.24.20])
  by orsmga105.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 01 Sep 2020 08:11:59 -0700
IronPort-SDR: 
 /wgnN22BFee6yJ3dN/boURLM6bcZdYWN5tJ46cG829uTIa4Uit3+gy/yMn0VDIFFh0A3ftGTJz
 cpLlK+qcSsTg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.76,379,1592895600";
   d="scan'208";a="501776247"
Received: from gliakhov-mobl2.ger.corp.intel.com (HELO
 ubuntu.ger.corp.intel.com) ([10.252.56.69])
  by fmsmga006.fm.intel.com with ESMTP; 01 Sep 2020 08:11:56 -0700
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
Subject: [PATCH v6 1/4] vhost: convert VHOST_VSOCK_SET_RUNNING to a generic
 ioctl
Date: Tue,  1 Sep 2020 17:11:50 +0200
Message-Id: <20200901151153.28111-2-guennadi.liakhovetski@linux.intel.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20200901151153.28111-1-guennadi.liakhovetski@linux.intel.com>
References: <20200901151153.28111-1-guennadi.liakhovetski@linux.intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

VHOST_VSOCK_SET_RUNNING is used by the vhost vsock driver to perform
crucial VirtQueue initialisation, like assigning .private fields and
calling vhost_vq_init_access(), and clean up. However, this ioctl is
actually extremely useful for any vhost driver, that doesn't have a
side channel to inform it of a status change, e.g. upon a guest
reboot. This patch makes that ioctl generic, while preserving its
numeric value and also keeping the original alias.

Signed-off-by: Guennadi Liakhovetski <guennadi.liakhovetski@linux.intel.com>
---
 include/uapi/linux/vhost.h | 4 +++-
 1 file changed, 3 insertions(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH v2 01/10] x86: Makefile: Allow division on x86_64-elf binutils
##### From: Roman Bolshakov <r.bolshakov@yadro.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Roman Bolshakov <r.bolshakov@yadro.com>
X-Patchwork-Id: 11747673
Return-Path: <SRS0=IPmA=CK=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BF71D1575
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  1 Sep 2020 08:51:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A3686205CB
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  1 Sep 2020 08:51:10 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=yadro.com header.i=@yadro.com
 header.b="cU+7RcpN"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727935AbgIAIvK (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 1 Sep 2020 04:51:10 -0400
Received: from mta-02.yadro.com ([89.207.88.252]:55006 "EHLO mta-01.yadro.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1727089AbgIAIvI (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 1 Sep 2020 04:51:08 -0400
Received: from localhost (unknown [127.0.0.1])
        by mta-01.yadro.com (Postfix) with ESMTP id 0399C5732F;
        Tue,  1 Sep 2020 08:51:06 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=yadro.com; h=
        content-type:content-type:content-transfer-encoding:mime-version
        :references:in-reply-to:x-mailer:message-id:date:date:subject
        :subject:from:from:received:received:received; s=mta-01; t=
        1598950264; x=1600764665; bh=+2lWsZX/gRrm4AzavLRxhHDoo/GY5h4wfKb
        /Xw6NKbk=; b=cU+7RcpNN+qY1FvsZYK6AxU1pJZG0ppxa/L4u5lD87zb5H+Hizu
        4oddiUyMThGy149T9C23A767BeBOga41zmjt54tHSOaGh0b6lpm9yv6FvjtrFUhf
        Vxc+4TWW/I/TMFs7OPEWrRgAkQIDICl8cCTtDNQ2lXPV345l0xNRTuSI=
X-Virus-Scanned: amavisd-new at yadro.com
Received: from mta-01.yadro.com ([127.0.0.1])
        by localhost (mta-01.yadro.com [127.0.0.1]) (amavisd-new, port 10024)
        with ESMTP id x2t1_GzJ4rV9; Tue,  1 Sep 2020 11:51:04 +0300 (MSK)
Received: from T-EXCH-02.corp.yadro.com (t-exch-02.corp.yadro.com
 [172.17.10.102])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-SHA384 (256/256 bits))
        (No client certificate requested)
        by mta-01.yadro.com (Postfix) with ESMTPS id 7ED2252215;
        Tue,  1 Sep 2020 11:51:04 +0300 (MSK)
Received: from localhost (172.17.204.212) by T-EXCH-02.corp.yadro.com
 (172.17.10.102) with Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA384_P384) id 15.1.669.32; Tue, 1 Sep
 2020 11:51:04 +0300
From: Roman Bolshakov <r.bolshakov@yadro.com>
To: <kvm@vger.kernel.org>
CC: Thomas Huth <thuth@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Roman Bolshakov <r.bolshakov@yadro.com>,
        Cameron Esfahani <dirty@apple.com>
Subject: [kvm-unit-tests PATCH v2 01/10] x86: Makefile: Allow division on
 x86_64-elf binutils
Date: Tue, 1 Sep 2020 11:50:47 +0300
Message-ID: <20200901085056.33391-2-r.bolshakov@yadro.com>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20200901085056.33391-1-r.bolshakov@yadro.com>
References: <20200901085056.33391-1-r.bolshakov@yadro.com>
MIME-Version: 1.0
X-Originating-IP: [172.17.204.212]
X-ClientProxiedBy: T-EXCH-01.corp.yadro.com (172.17.10.101) To
 T-EXCH-02.corp.yadro.com (172.17.10.102)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

For compatibility with other SVR4 assemblers, '/' starts a comment on
*-elf binutils target and thus division operator is not allowed [1][2].
That breaks cstart64.S build:

  x86/cstart64.S: Assembler messages:
  x86/cstart64.S:294: Error: unbalanced parenthesis in operand 1.

configure should detect if --divide needs to be passed to assembler by
compiling a small snippet where division is used inside parentheses.

1. https://sourceware.org/binutils/docs/as/i386_002dChars.html
2. https://sourceware.org/binutils/docs/as/i386_002dOptions.html#index-_002d_002ddivide-option_002c-i386

Cc: Cameron Esfahani <dirty@apple.com>
Signed-off-by: Roman Bolshakov <r.bolshakov@yadro.com>
---
 configure           | 12 ++++++++++++
 x86/Makefile.common |  3 +++
 2 files changed, 15 insertions(+)

```
#### [PATCH v6 1/7] KVM: x86: Deflect unknown MSR accesses to user space
##### From: Alexander Graf <graf@amazon.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Graf <graf@amazon.com>
X-Patchwork-Id: 11749427
Return-Path: <SRS0=IPmA=CK=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 99125618
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  1 Sep 2020 20:15:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 777872078B
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  1 Sep 2020 20:15:51 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amazon.com header.i=@amazon.com
 header.b="mYlLow/2"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728827AbgIAUPn (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 1 Sep 2020 16:15:43 -0400
Received: from smtp-fw-2101.amazon.com ([72.21.196.25]:23808 "EHLO
        smtp-fw-2101.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729386AbgIAUPi (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 1 Sep 2020 16:15:38 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.com; i=@amazon.com; q=dns/txt; s=amazon201209;
  t=1598991337; x=1630527337;
  h=from:to:cc:subject:date:message-id:in-reply-to:
   references:mime-version;
  bh=sVr8f22MaDe/QCgG5Z/gJcf5Swrutmw8uwmX7xhUdug=;
  b=mYlLow/24dIEHk/lGL/N8PJBMhQA3pQuJ/7ULqh3kql8YcTrGhcV2jS1
   mGDVLxbVMLzlTeQyXS4WEsiTf6ylpn0ZFbkc5QwOn/4dO4xtDpYdjTlOX
   qyUuEOASpbX0exXUxbCrv2A/dFVdh/2MI6Lu6nZsiq61mawtvfWUnl7FQ
   w=;
X-IronPort-AV: E=Sophos;i="5.76,380,1592870400";
   d="scan'208";a="51310836"
Received: from iad12-co-svc-p1-lb1-vlan2.amazon.com (HELO
 email-inbound-relay-1e-27fb8269.us-east-1.amazon.com) ([10.43.8.2])
  by smtp-border-fw-out-2101.iad2.amazon.com with ESMTP;
 01 Sep 2020 20:15:37 +0000
Received: from EX13MTAUWC001.ant.amazon.com
 (iad55-ws-svc-p15-lb9-vlan2.iad.amazon.com [10.40.159.162])
        by email-inbound-relay-1e-27fb8269.us-east-1.amazon.com (Postfix) with
 ESMTPS id AB866A07CE;
        Tue,  1 Sep 2020 20:15:32 +0000 (UTC)
Received: from EX13D20UWC001.ant.amazon.com (10.43.162.244) by
 EX13MTAUWC001.ant.amazon.com (10.43.162.135) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Tue, 1 Sep 2020 20:15:31 +0000
Received: from u79c5a0a55de558.ant.amazon.com (10.43.160.229) by
 EX13D20UWC001.ant.amazon.com (10.43.162.244) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Tue, 1 Sep 2020 20:15:28 +0000
From: Alexander Graf <graf@amazon.com>
To: Paolo Bonzini <pbonzini@redhat.com>
CC: Jonathan Corbet <corbet@lwn.net>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        "Joerg Roedel" <joro@8bytes.org>,
        KarimAllah Raslan <karahmed@amazon.de>,
        Aaron Lewis <aaronlewis@google.com>,
        Dan Carpenter <dan.carpenter@oracle.com>,
        <kvm@vger.kernel.org>, <linux-doc@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>
Subject: [PATCH v6 1/7] KVM: x86: Deflect unknown MSR accesses to user space
Date: Tue, 1 Sep 2020 22:15:11 +0200
Message-ID: <20200901201517.29086-2-graf@amazon.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200901201517.29086-1-graf@amazon.com>
References: <20200901201517.29086-1-graf@amazon.com>
MIME-Version: 1.0
X-Originating-IP: [10.43.160.229]
X-ClientProxiedBy: EX13D18UWC001.ant.amazon.com (10.43.162.105) To
 EX13D20UWC001.ant.amazon.com (10.43.162.244)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

MSRs are weird. Some of them are normal control registers, such as EFER.
Some however are registers that really are model specific, not very
interesting to virtualization workloads, and not performance critical.
Others again are really just windows into package configuration.

Out of these MSRs, only the first category is necessary to implement in
kernel space. Rarely accessed MSRs, MSRs that should be fine tunes against
certain CPU models and MSRs that contain information on the package level
are much better suited for user space to process. However, over time we have
accumulated a lot of MSRs that are not the first category, but still handled
by in-kernel KVM code.

This patch adds a generic interface to handle WRMSR and RDMSR from user
space. With this, any future MSR that is part of the latter categories can
be handled in user space.

Furthermore, it allows us to replace the existing "ignore_msrs" logic with
something that applies per-VM rather than on the full system. That way you
can run productive VMs in parallel to experimental ones where you don't care
about proper MSR handling.

Signed-off-by: Alexander Graf <graf@amazon.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---

v1 -> v2:

  - s/ETRAP_TO_USER_SPACE/ENOENT/g
  - deflect all #GP injection events to user space, not just unknown MSRs.
    That was we can also deflect allowlist errors later
  - fix emulator case

v2 -> v3:

  - return r if r == X86EMUL_IO_NEEDED
  - s/KVM_EXIT_RDMSR/KVM_EXIT_X86_RDMSR/g
  - s/KVM_EXIT_WRMSR/KVM_EXIT_X86_WRMSR/g
  - Use complete_userspace_io logic instead of reply field
  - Simplify trapping code

v3 -> v4:

  - Mention exit reasons in re-inter mandatory section of API documentation
  - Clear padding bytes
  - Generalize get/set deflect functions
  - Remove redundant pending_user_msr field

v5 -> v6:

  - Introduce exit reason mask to allow for future expansion and filtering
  - s/emul_to_vcpu(ctxt)/vcpu/
---
 Documentation/virt/kvm/api.rst  |  73 +++++++++++++++++++-
 arch/x86/include/asm/kvm_host.h |   3 +
 arch/x86/kvm/emulate.c          |  18 ++++-
 arch/x86/kvm/x86.c              | 119 ++++++++++++++++++++++++++++++--
 include/trace/events/kvm.h      |   2 +-
 include/uapi/linux/kvm.h        |  12 ++++
 6 files changed, 218 insertions(+), 9 deletions(-)

```
#### [PATCH v4 1/5] iommu: Add optional subdev in aux_at(de)tach ops
##### From: Lu Baolu <baolu.lu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Lu Baolu <baolu.lu@linux.intel.com>
X-Patchwork-Id: 11747311
Return-Path: <SRS0=IPmA=CK=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 164541667
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  1 Sep 2020 03:40:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 045942083B
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  1 Sep 2020 03:40:18 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726559AbgIADkO (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 31 Aug 2020 23:40:14 -0400
Received: from mga12.intel.com ([192.55.52.136]:62487 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725987AbgIADkN (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 31 Aug 2020 23:40:13 -0400
IronPort-SDR: 
 Ouwm8mi3EjYZswVXAjDRuIzqQZfYUsAzlZ2PzM3ElSKQhDhZGSpqgWRu6y2L313TyG8o+i9nkm
 gLRa1dKg73SA==
X-IronPort-AV: E=McAfee;i="6000,8403,9730"; a="136620920"
X-IronPort-AV: E=Sophos;i="5.76,377,1592895600";
   d="scan'208";a="136620920"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga004.fm.intel.com ([10.253.24.48])
  by fmsmga106.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 31 Aug 2020 20:40:12 -0700
IronPort-SDR: 
 1kfNDpxVZ6PjA9CK/YbklI2otaiSCxb5Hzrt0nE6YVckEQ9BAy5kwhn0hOaSxj3FTWfku0VgS4
 ccCggZH6ZUZw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.76,377,1592895600";
   d="scan'208";a="325180863"
Received: from allen-box.sh.intel.com ([10.239.159.139])
  by fmsmga004.fm.intel.com with ESMTP; 31 Aug 2020 20:40:09 -0700
From: Lu Baolu <baolu.lu@linux.intel.com>
To: Joerg Roedel <joro@8bytes.org>,
        Alex Williamson <alex.williamson@redhat.com>
Cc: Robin Murphy <robin.murphy@arm.com>,
        Jean-Philippe Brucker <jean-philippe@linaro.org>,
        Cornelia Huck <cohuck@redhat.com>,
        Kevin Tian <kevin.tian@intel.com>,
        Ashok Raj <ashok.raj@intel.com>,
        Dave Jiang <dave.jiang@intel.com>,
        Liu Yi L <yi.l.liu@intel.com>, Zeng Xin <xin.zeng@intel.com>,
        iommu@lists.linux-foundation.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, Lu Baolu <baolu.lu@linux.intel.com>
Subject: [PATCH v4 1/5] iommu: Add optional subdev in aux_at(de)tach ops
Date: Tue,  1 Sep 2020 11:34:18 +0800
Message-Id: <20200901033422.22249-2-baolu.lu@linux.intel.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200901033422.22249-1-baolu.lu@linux.intel.com>
References: <20200901033422.22249-1-baolu.lu@linux.intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In the vfio/mdev use case of aux-domain, the subdevices are created from
the physical devices with IOMMU_DEV_FEAT_AUX enabled and the aux-domains
are attached to the subdevices through the iommu_ops.aux_attach_dev()
interface.

Current iommu_ops.aux_at(de)tach_dev() design only takes the aux-domain
and the physical device as the parameters, this is insufficient if we
want the vendor iommu drivers to learn the knowledge about relationships
between the aux-domains and the subdevices. Add a @subdev parameter to
iommu_ops.aux_at(de)tach_dev() interfaces so that a subdevice could be
opt-in.

Signed-off-by: Lu Baolu <baolu.lu@linux.intel.com>
---
 drivers/iommu/intel/iommu.c | 10 ++++++----
 drivers/iommu/iommu.c       |  4 ++--
 include/linux/iommu.h       |  6 ++++--
 3 files changed, 12 insertions(+), 8 deletions(-)

```
#### [PATCH] KVM: Check the allocation of pv cpu maskTo: "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>,
##### From: Haiwei Li <lihaiwei.kernel@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Haiwei Li <lihaiwei.kernel@gmail.com>
X-Patchwork-Id: 11747985
Return-Path: <SRS0=IPmA=CK=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 85402138A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  1 Sep 2020 11:47:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6C32220707
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  1 Sep 2020 11:47:17 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="WTXFwaaO"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727116AbgIALq3 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 1 Sep 2020 07:46:29 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:47086 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726144AbgIALlz (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 1 Sep 2020 07:41:55 -0400
Received: from mail-pl1-x642.google.com (mail-pl1-x642.google.com
 [IPv6:2607:f8b0:4864:20::642])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 4E8D7C061245;
        Tue,  1 Sep 2020 04:41:48 -0700 (PDT)
Received: by mail-pl1-x642.google.com with SMTP id y6so396465plk.10;
        Tue, 01 Sep 2020 04:41:48 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:subject:to:cc:message-id:date:user-agent:mime-version
         :content-language:content-transfer-encoding;
        bh=vL68VqqvBOJpmK0bclLXd33KppmDO85K8QP95o8vC+4=;
        b=WTXFwaaOARSwB1lRXSnt3qJua0sM84oKQHSk1MVVav7KFevKHkgOdVWkOgVmbGz2HQ
         rOSCUGNLXUF2a8hQ0U/7QnO8Ut6haIUxfAkW5QbrydpqnMTrL8ChApB111FHedpghk8M
         qL9gl2Ulk1g7MaEOr5xX2SyOZw1fR0QrhePKuJPUmk3yXIlrBwk10NRgah5ptx0EJxo6
         6o/Lre/7Qwt0vZzwavPXFv5c5Cj/9n3WZI4zh9PQWuTw/TX4z4mIt+8u2qonXS8i8BLt
         q5gNIiVOa2LIDasdDEjPtxZloIkYI3TBp/TlgO+Myw8AincTMRjubtIaOiNIW3fiiVE9
         J3EQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:subject:to:cc:message-id:date:user-agent
         :mime-version:content-language:content-transfer-encoding;
        bh=vL68VqqvBOJpmK0bclLXd33KppmDO85K8QP95o8vC+4=;
        b=FBroC7xRngotSnK1Dg5LhfFeH3+sIwPHAk7ag9A7RZsGzazI0AmCNv4VzE4eA62QGn
         LS0q++/BpxXJmAueBLaW5jkP1+GM8ZKrCHGtUl2K2NwX6SiZw7dKEpS26PRvylclTyiD
         L11Xl4qWveGko/vqZGUMuf4smMTTHm1VHU1OnbepJvVjwM7BSM5yyf3GTfrwX+ezuJkw
         WVMPQVSbGpUtl2rxpMo062OJpyhqkw9vVhS0slMXIhpMVzGUz6g3F5kmYitqOfIim57/
         b69HjScrmCRsURgTzB5C5E5WUkNvQQhzJev0PFE4hhdWv+8fW5Kt+VTO2V1oaIFquL3+
         81Mg==
X-Gm-Message-State: AOAM531ytOHDJV7zyxw/ipVL+zjrTqP0MT2tABq3gyER5BYVALd7HB2n
        NB4e/RyhckTv1/xL8LbtLQ==
X-Google-Smtp-Source: 
 ABdhPJw7j2QWldkxD7fX4qizVyKuseP3QD5Bv0/o1MGNiCfFzJZRsol9XRm13ns3zWHLLlrlzysLUw==
X-Received: by 2002:a17:90a:8909:: with SMTP id
 u9mr1207128pjn.119.1598960507698;
        Tue, 01 Sep 2020 04:41:47 -0700 (PDT)
Received: from [127.0.0.1] ([103.7.29.7])
        by smtp.gmail.com with ESMTPSA id
 142sm1799131pgf.68.2020.09.01.04.41.43
        (version=TLS1_3 cipher=TLS_AES_128_GCM_SHA256 bits=128/128);
        Tue, 01 Sep 2020 04:41:46 -0700 (PDT)
From: Haiwei Li <lihaiwei.kernel@gmail.com>
Subject: [PATCH] KVM: Check the allocation of pv cpu mask
To: "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>,
        "kvm@vger.kernel.org" <kvm@vger.kernel.org>,
        "x86@kernel.org" <x86@kernel.org>
Cc: "hpa@zytor.com" <hpa@zytor.com>, "bp@alien8.de" <bp@alien8.de>,
        "mingo@redhat.com" <mingo@redhat.com>, tglx@linutronix.de,
        joro@8bytes.org, jmattson@google.com,
        "wanpengli@tencent.com" <wanpengli@tencent.com>,
        vkuznets@redhat.com,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        "pbonzini@redhat.com" <pbonzini@redhat.com>
Message-ID: <d59f05df-e6d3-3d31-a036-cc25a2b2f33f@gmail.com>
Date: Tue, 1 Sep 2020 19:41:37 +0800
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:68.0)
 Gecko/20100101 Thunderbird/68.11.0
MIME-Version: 1.0
Content-Language: en-US
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Haiwei Li <lihaiwei@tencent.com>

check the allocation of per-cpu __pv_cpu_mask. Initialize ops only when
successful.

Signed-off-by: Haiwei Li <lihaiwei@tencent.com>
Reported-by: kernel test robot <lkp@intel.com>
---
  arch/x86/kernel/kvm.c | 23 +++++++++++++++++++----
  1 file changed, 19 insertions(+), 4 deletions(-)


@@ -654,7 +653,6 @@ static void __init kvm_guest_init(void)
  	}

  	if (pv_tlb_flush_supported()) {
-		pv_ops.mmu.flush_tlb_others = kvm_flush_tlb_others;
  		pv_ops.mmu.tlb_remove_table = tlb_remove_table;
  		pr_info("KVM setup pv remote TLB flush\n");
  	}
@@ -767,6 +765,14 @@ static __init int activate_jump_labels(void)
  }
  arch_initcall(activate_jump_labels);

+static void kvm_free_pv_cpu_mask(void)
+{
+	unsigned int cpu;
+
+	for_each_possible_cpu(cpu)
+		free_cpumask_var(per_cpu(__pv_cpu_mask, cpu));
+}
+
  static __init int kvm_alloc_cpumask(void)
  {
  	int cpu;
@@ -785,11 +791,20 @@ static __init int kvm_alloc_cpumask(void)

  	if (alloc)
  		for_each_possible_cpu(cpu) {
-			zalloc_cpumask_var_node(per_cpu_ptr(&__pv_cpu_mask, cpu),
-				GFP_KERNEL, cpu_to_node(cpu));
+			if (!zalloc_cpumask_var_node(
+				per_cpu_ptr(&__pv_cpu_mask, cpu),
+				GFP_KERNEL, cpu_to_node(cpu))) {
+				goto zalloc_cpumask_fail;
+			}
  		}

+	apic->send_IPI_mask_allbutself = kvm_send_ipi_mask_allbutself;
+	pv_ops.mmu.flush_tlb_others = kvm_flush_tlb_others;
  	return 0;
+
+zalloc_cpumask_fail:
+	kvm_free_pv_cpu_mask();
+	return -ENOMEM;
  }
  arch_initcall(kvm_alloc_cpumask);

--
2.18.4

```
#### [kvm-unit-tests GIT PULL 1/3] s390x: Add custom pgm cleanup function
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11747743
Return-Path: <SRS0=IPmA=CK=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 54B30166C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  1 Sep 2020 09:18:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3B0502098B
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  1 Sep 2020 09:18:54 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="OQiNGzoF"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726244AbgIAJSu (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 1 Sep 2020 05:18:50 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:34822 "EHLO
        mx0b-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1725848AbgIAJSo (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 1 Sep 2020 05:18:44 -0400
Received: from pps.filterd (m0098417.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 08191juC161425;
        Tue, 1 Sep 2020 05:18:43 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=Mo8KmB6saTrJHYx8XJzHO0sD/ITp9wiOPYwvnymwVUk=;
 b=OQiNGzoFXulsu9r1A+OVa8oRe2JCWPvucU2EpaahoM/OJP7iev9ippfniiGJ31MAe55y
 zjAppTkZIFUwbKogsnKzTepuvrmUe9O/+OEueDLg64v5pPIfWRIfjeiaytGRrFW/aT5i
 GZ+Vf+o1xs1oeQbbDoJISIqT6kMdPZTiYCLr5FZD1OYPcLxREU1digEsAZJcrlzOhDPM
 I3K4sRZzd78VQSrK76EX+PXrAS/Mov6zNFNo99IqzRqvuCdyDJ373oLwqRjSbwyioxi0
 0WE4nsnAQ/Sqa+G1nFYXQWWYyblma7hkImFjvCbtZi/gCHcK51W4yfWucdrJxJZgzspr lQ==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 339k4g8v36-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 01 Sep 2020 05:18:43 -0400
Received: from m0098417.ppops.net (m0098417.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 0819HFch034128;
        Tue, 1 Sep 2020 05:18:42 -0400
Received: from ppma05fra.de.ibm.com (6c.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.108])
        by mx0a-001b2d01.pphosted.com with ESMTP id 339k4g8v22-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 01 Sep 2020 05:18:42 -0400
Received: from pps.filterd (ppma05fra.de.ibm.com [127.0.0.1])
        by ppma05fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 0819DB9p007935;
        Tue, 1 Sep 2020 09:18:41 GMT
Received: from b06avi18878370.portsmouth.uk.ibm.com
 (b06avi18878370.portsmouth.uk.ibm.com [9.149.26.194])
        by ppma05fra.de.ibm.com with ESMTP id 337en81yb0-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 01 Sep 2020 09:18:40 +0000
Received: from d06av22.portsmouth.uk.ibm.com (d06av22.portsmouth.uk.ibm.com
 [9.149.105.58])
        by b06avi18878370.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 0819IcWv60686776
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 1 Sep 2020 09:18:38 GMT
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id F314C4C044;
        Tue,  1 Sep 2020 09:18:37 +0000 (GMT)
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 910AF4C04E;
        Tue,  1 Sep 2020 09:18:37 +0000 (GMT)
Received: from localhost.localdomain.com (unknown [9.145.37.233])
        by d06av22.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue,  1 Sep 2020 09:18:37 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: pbonzini@redhat.com
Cc: kvm@vger.kernel.org, frankja@linux.vnet.ibm.com, david@redhat.com,
        borntraeger@de.ibm.com, cohuck@redhat.com,
        linux-s390@vger.kernel.org, imbrenda@linux.ibm.com
Subject: [kvm-unit-tests GIT PULL 1/3] s390x: Add custom pgm cleanup function
Date: Tue,  1 Sep 2020 11:18:21 +0200
Message-Id: <20200901091823.14477-2-frankja@linux.ibm.com>
X-Mailer: git-send-email 2.25.4
In-Reply-To: <20200901091823.14477-1-frankja@linux.ibm.com>
References: <20200901091823.14477-1-frankja@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-09-01_04:2020-09-01,2020-09-01 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 malwarescore=0
 impostorscore=0 adultscore=0 spamscore=0 priorityscore=1501 clxscore=1015
 bulkscore=0 lowpriorityscore=0 phishscore=0 mlxlogscore=999 suspectscore=1
 mlxscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2009010075
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Sometimes we need to do cleanup which we don't necessarily want to add
to interrupt.c, so let's add a way to register a cleanup function.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Message-Id: <20200807111555.11169-2-frankja@linux.ibm.com>
Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
---
 lib/s390x/asm/interrupt.h |  1 +
 lib/s390x/interrupt.c     | 12 +++++++++++-
 2 files changed, 12 insertions(+), 1 deletion(-)

```
#### [PATCH] KVM: x86/mmu: fix counting of rmap entries in pte_list_add
##### From: Li RongQing <lirongqing@baidu.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Li RongQing <lirongqing@baidu.com>
X-Patchwork-Id: 11747781
Return-Path: <SRS0=IPmA=CK=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 62B69138A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  1 Sep 2020 09:27:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 552F520866
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  1 Sep 2020 09:27:11 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726255AbgIAJ1K (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 1 Sep 2020 05:27:10 -0400
Received: from mx132-tc.baidu.com ([61.135.168.132]:38193 "EHLO
        tc-sys-mailedm02.tc.baidu.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1725989AbgIAJ1J (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 1 Sep 2020 05:27:09 -0400
Received: from localhost (cp01-cos-dev01.cp01.baidu.com [10.92.119.46])
        by tc-sys-mailedm02.tc.baidu.com (Postfix) with ESMTP id 72DE011C0053;
        Tue,  1 Sep 2020 17:26:55 +0800 (CST)
From: Li RongQing <lirongqing@baidu.com>
To: x86@kernel.org, kvm@vger.kernel.org
Subject: [PATCH] KVM: x86/mmu: fix counting of rmap entries in pte_list_add
Date: Tue,  1 Sep 2020 17:26:55 +0800
Message-Id: <1598952415-19706-1-git-send-email-lirongqing@baidu.com>
X-Mailer: git-send-email 1.7.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

counting of rmap entries was missed when desc->sptes is full
and desc->more is false

Cc: <stable@vger.kernel.org>
Signed-off-by: Li RongQing <lirongqing@baidu.com>
---
 arch/x86/kvm/mmu/mmu.c | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH net-next] vhost: fix typo in error message
##### From: Yunsheng Lin <linyunsheng@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yunsheng Lin <linyunsheng@huawei.com>
X-Patchwork-Id: 11747251
Return-Path: <SRS0=IPmA=CK=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3DA0714E5
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  1 Sep 2020 02:43:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2F2A82078B
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  1 Sep 2020 02:43:23 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726771AbgIACmw (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 31 Aug 2020 22:42:52 -0400
Received: from szxga05-in.huawei.com ([45.249.212.191]:10741 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1725901AbgIACmw (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 31 Aug 2020 22:42:52 -0400
Received: from DGGEMS405-HUB.china.huawei.com (unknown [172.30.72.60])
        by Forcepoint Email with ESMTP id D19B6F84F83104F950EF;
        Tue,  1 Sep 2020 10:42:49 +0800 (CST)
Received: from localhost.localdomain (10.69.192.58) by
 DGGEMS405-HUB.china.huawei.com (10.3.19.205) with Microsoft SMTP Server id
 14.3.487.0; Tue, 1 Sep 2020 10:42:42 +0800
From: Yunsheng Lin <linyunsheng@huawei.com>
To: <mst@redhat.com>, <jasowang@redhat.com>
CC: <kvm@vger.kernel.org>, <virtualization@lists.linux-foundation.org>,
        <netdev@vger.kernel.org>, <linux-kernel@vger.kernel.org>,
        <linuxarm@huawei.com>
Subject: [PATCH net-next] vhost: fix typo in error message
Date: Tue, 1 Sep 2020 10:39:09 +0800
Message-ID: <1598927949-201997-1-git-send-email-linyunsheng@huawei.com>
X-Mailer: git-send-email 2.8.1
MIME-Version: 1.0
X-Originating-IP: [10.69.192.58]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

"enable" should be "disable" when the function name is
vhost_disable_notify(), which does the disabling work.

Signed-off-by: Yunsheng Lin <linyunsheng@huawei.com>
Acked-by: Jason Wang <jasowang@redhat.com>
Acked-by: Michael S. Tsirkin <mst@redhat.com>
---
 drivers/vhost/vhost.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [RFC V2 1/9] Introduce new fields in kvm_arch/vcpu_arch struct for direct build EPT support
##### From: yulei.kernel@gmail.com

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: yulei zhang <yulei.kernel@gmail.com>
X-Patchwork-Id: 11748231
Return-Path: <SRS0=IPmA=CK=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 09F4F722
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  1 Sep 2020 14:13:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DDDBF20FC3
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  1 Sep 2020 14:13:02 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="XGknnUl5"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727819AbgIALy4 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 1 Sep 2020 07:54:56 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:48988 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726419AbgIALxu (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 1 Sep 2020 07:53:50 -0400
Received: from mail-pl1-x644.google.com (mail-pl1-x644.google.com
 [IPv6:2607:f8b0:4864:20::644])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 5F381C061244;
        Tue,  1 Sep 2020 04:53:50 -0700 (PDT)
Received: by mail-pl1-x644.google.com with SMTP id y6so423060plt.3;
        Tue, 01 Sep 2020 04:53:50 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:in-reply-to:references;
        bh=deukqrTnR0cMzsDKDaqxmBI2QdBNNOMXdjj1IqkXDBo=;
        b=XGknnUl5Ax4ZlofOqiThlZt8dgwF/9fDJdmA9cH5irula3kLI7CPRZdtZKjoWcQvDn
         6B04V4QhFIMLMKg+Mhd8b086sl9AYx3mAjclN+TgDMQ319a+bG4Y//xrZ/QFSp6FwN1g
         0lO8uOwRIXqEUW1RzJNAIdBx8rj4eO8oOR4/GGJc1uusHoco4LjMvs4Lqe9ia/CEUqNX
         1ZwV0v1yg34L7gtWDlMPlZf3muPjnnssrC/R5Z6knCMEzWj+6mrPtfrQVSwZofUoNI3X
         6Nb51M0GQZmfzS89waYtM2Ee4I8ImR2PxPSgF1+3LvQlDDB2z2NYs2t7R/RzGLy1A5cz
         n0Sg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references;
        bh=deukqrTnR0cMzsDKDaqxmBI2QdBNNOMXdjj1IqkXDBo=;
        b=uRgLdV3zy/Pe9lAaLZkpssfjnQaDfv3lfwfWQ0yy+HjoiyaYh+PgGfUwxRHI7x2Lvd
         hfzaFFCoI0I6u0GZaWuKlKIWGPECPV2tdKF/4zTDBZdjyb1rZKr3KpjRlp1qSs93wCYK
         vpWbllGo/5Rwq7ohwe1V3KX+EvI7vCgCKSN+oiiIplYAhrmsw3IC8FEKNpYESOJtSyZY
         bdjqgNYjXVqkz36s1mK8dIwT9Ubh0w8vztLaANgVV91lvtdYUFmcEc/gzXw9Ri9DbFsd
         mxydgBoJOCU/H/ImIaVuXhKswoEUbA57I8GKse9TPEjrU/jo9BhsHG7fPiHKxMzJau6R
         ifFw==
X-Gm-Message-State: AOAM533bQZGfWWR0JzSs6n+NyI3rYXCAdwTJz/T6wx2OvnTqvR2/dMQd
        CCRFFiTaPJ17x2mQIT2uIA4=
X-Google-Smtp-Source: 
 ABdhPJwNjXvlt61ssgWgPZnZKqp427rrJB0T8ROpLi2YxiDjwxc1bBuVnFWLhkztKoKUIcxnj0fhnA==
X-Received: by 2002:a17:902:b111:: with SMTP id
 q17mr1066230plr.202.1598961229988;
        Tue, 01 Sep 2020 04:53:49 -0700 (PDT)
Received: from localhost.localdomain ([203.205.141.53])
        by smtp.gmail.com with ESMTPSA id
 fs24sm1365344pjb.8.2020.09.01.04.53.46
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 01 Sep 2020 04:53:49 -0700 (PDT)
From: yulei.kernel@gmail.com
X-Google-Original-From: yuleixzhang@tencent.com
To: pbonzini@redhat.com
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        sean.j.christopherson@intel.com, jmattson@google.com,
        junaids@google.com, bgardon@google.com, vkuznets@redhat.com,
        xiaoguangrong.eric@gmail.com, kernellwp@gmail.com,
        lihaiwei.kernel@gmail.com, Yulei Zhang <yuleixzhang@tencent.com>
Subject: [RFC V2 1/9] Introduce new fields in kvm_arch/vcpu_arch struct for
 direct build EPT support
Date: Tue,  1 Sep 2020 19:54:43 +0800
Message-Id: 
 <d7684439e1aa1c213c3a29219afda55b9b70b662.1598868204.git.yulei.kernel@gmail.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <cover.1598868203.git.yulei.kernel@gmail.com>
References: <cover.1598868203.git.yulei.kernel@gmail.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Yulei Zhang <yuleixzhang@tencent.com>

Add parameter global_root_hpa for saving direct build global EPT root point,
and add per-vcpu flag direct_build_tdp to indicate using global EPT root
point.

Signed-off-by: Yulei Zhang <yuleixzhang@tencent.com>
---
 arch/x86/include/asm/kvm_host.h | 5 +++++
 1 file changed, 5 insertions(+)

```
