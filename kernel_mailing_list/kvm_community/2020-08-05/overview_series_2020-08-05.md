#### [PATCH 01/56] KVM: arm64: Enable Address Authentication at EL2 if available
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11702047
Return-Path: <SRS0=UpKl=BP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1492D1392
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  5 Aug 2020 17:58:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id EFEAD2250E
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  5 Aug 2020 17:58:44 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1596650325;
	bh=2tDp9H0m/DUHgNapuzVzhcDiDbsvksSgHwX/+FAZCOE=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=po/qk8YG1HCI3tkxJlkiU2ayDQ1LNMgkH4vZzgoq3LcMY/TMoHB533sTEtcYed0Yr
	 Qf+ndXbcNsGlWMxbyQjarb1Mun1E+gPAOoa0K0gfYGQrLJB2z1eMsmPUEdZ4IZcmaB
	 XwacjZP2qIxJZ+10pp5SjralGw0PVd+H/aIjfJa0=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728493AbgHER62 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 5 Aug 2020 13:58:28 -0400
Received: from mail.kernel.org ([198.145.29.99]:45274 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729068AbgHER5n (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 5 Aug 2020 13:57:43 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 200AB21D95;
        Wed,  5 Aug 2020 17:57:14 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1596650234;
        bh=2tDp9H0m/DUHgNapuzVzhcDiDbsvksSgHwX/+FAZCOE=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=qsX2iaGnfP/oU0mKxH9wclxYivITINyNKfnYwM4v+31djMgunV247eYKiD6Yup9bp
         6HgEMcRAGnrbRtF4Bt6Ww50H10o/K/GF/CUxf5UZLNpOmfVucMeMDPf9c8hJUlh1v0
         gsnTTamAEtz7Vs/Z3woygF2x1eUqFUAf4iu3ONzU=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1k3Nf6-0004w9-M4; Wed, 05 Aug 2020 18:57:12 +0100
From: Marc Zyngier <maz@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Alexander Graf <graf@amazon.com>,
        Alexandru Elisei <alexandru.elisei@arm.com>,
        Andrew Scull <ascull@google.com>,
        Catalin Marinas <catalin.marinas@arm.com>,
        Christoffer Dall <christoffer.dall@arm.com>,
        David Brazdil <dbrazdil@google.com>,
        Eric Auger <eric.auger@redhat.com>,
        Gavin Shan <gshan@redhat.com>,
        James Morse <james.morse@arm.com>,
        Mark Rutland <mark.rutland@arm.com>,
        Peng Hao <richard.peng@oppo.com>,
        Quentin Perret <qperret@google.com>,
        Will Deacon <will@kernel.org>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org, kernel-team@android.com
Subject: [PATCH 01/56] KVM: arm64: Enable Address Authentication at EL2 if
 available
Date: Wed,  5 Aug 2020 18:56:05 +0100
Message-Id: <20200805175700.62775-2-maz@kernel.org>
X-Mailer: git-send-email 2.27.0
In-Reply-To: <20200805175700.62775-1-maz@kernel.org>
References: <20200805175700.62775-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: pbonzini@redhat.com, graf@amazon.com,
 alexandru.elisei@arm.com, ascull@google.com, catalin.marinas@arm.com,
 christoffer.dall@arm.com, dbrazdil@google.com, eric.auger@redhat.com,
 gshan@redhat.com, james.morse@arm.com, mark.rutland@arm.com,
 richard.peng@oppo.com, qperret@google.com, will@kernel.org,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
 kvm@vger.kernel.org, kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

While initializing EL2, enable Address Authentication if detected
from EL1. We still use the EL1-provided keys though.

Acked-by: Andrew Scull <ascull@google.com>
Acked-by: Mark Rutland <mark.rutland@arm.com>
Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 arch/arm64/kvm/hyp-init.S | 5 +++++
 1 file changed, 5 insertions(+)

```
#### [PATCH 1/2] vDPA: get_vq_irq() should be optional
##### From: Zhu Lingshan <lingshan.zhu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Zhu Lingshan <lingshan.zhu@intel.com>
X-Patchwork-Id: 11702499
Return-Path: <SRS0=UpKl=BP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E3CF514DD
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  5 Aug 2020 20:09:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D899322B42
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  5 Aug 2020 20:09:04 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729681AbgHEUJD (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 5 Aug 2020 16:09:03 -0400
Received: from mga06.intel.com ([134.134.136.31]:6730 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726392AbgHEQce (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 5 Aug 2020 12:32:34 -0400
IronPort-SDR: 
 jUYgZT5wOinZiVWNnUH5zLCtcgkqC9zo5HWVa7TwAX9VjTeHOmCpgPxv5oE4ZiN6EnMPqTtoTB
 l5+hiYhLViSg==
X-IronPort-AV: E=McAfee;i="6000,8403,9703"; a="214047223"
X-IronPort-AV: E=Sophos;i="5.75,436,1589266800";
   d="scan'208";a="214047223"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga005.jf.intel.com ([10.7.209.41])
  by orsmga104.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 05 Aug 2020 04:41:48 -0700
IronPort-SDR: 
 voInwl4vfbYWzZUXFHCdXSR5TLohsgoXijCOnbprW6erlSv+R5na1gMwKuobZESQFIQPx/W9hx
 4A4Yz0c4RE9w==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,436,1589266800";
   d="scan'208";a="467437398"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.240.192.131])
  by orsmga005.jf.intel.com with ESMTP; 05 Aug 2020 04:41:45 -0700
From: Zhu Lingshan <lingshan.zhu@intel.com>
To: jasowang@redhat.com, mst@redhat.com
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        kvm@vger.kernel.org, eli@mellanox.com, shahafs@mellanox.com,
        parav@mellanox.com, Zhu Lingshan <lingshan.zhu@intel.com>
Subject: [PATCH 1/2] vDPA: get_vq_irq() should be optional
Date: Wed,  5 Aug 2020 19:37:59 +0800
Message-Id: <20200805113759.3591-1-lingshan.zhu@intel.com>
X-Mailer: git-send-email 2.18.4
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

get_vq_irq() should be optional, it's required when
we need to setup irq offloading, otherwise it‘s OK to be NULL.

Signed-off-by: Zhu Lingshan <lingshan.zhu@intel.com>
---
 include/linux/vdpa.h | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [PATCH v6 01/18] nitro_enclaves: Add ioctl interface definition
##### From: Andra Paraschiv <andraprs@amazon.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andra Paraschiv <andraprs@amazon.com>
X-Patchwork-Id: 11701571
Return-Path: <SRS0=UpKl=BP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 97908722
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  5 Aug 2020 09:11:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7B33D22CAF
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  5 Aug 2020 09:11:10 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amazon.com header.i=@amazon.com
 header.b="BsSSHT87"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728036AbgHEJLD (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 5 Aug 2020 05:11:03 -0400
Received: from smtp-fw-9101.amazon.com ([207.171.184.25]:16612 "EHLO
        smtp-fw-9101.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728198AbgHEJKs (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 5 Aug 2020 05:10:48 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.com; i=@amazon.com; q=dns/txt; s=amazon201209;
  t=1596618645; x=1628154645;
  h=from:to:cc:subject:date:message-id:in-reply-to:
   references:mime-version:content-transfer-encoding;
  bh=ri9P3cFVay0IqlN62Qx9mL647HaCAYAl6p8wRINamMI=;
  b=BsSSHT87ofAluE4WgGyN5Ahh9wirXVh8qZx34qTBM5+niA7+u9zseNKq
   IJ8ECpiTZe2ibxuxmhqtKPTAhG62m70p7EQ2Lldcadn8R9gTd9jbTZPRO
   +6D6sQJeozT+igUDXl935rkR6dWB7/HH/sDFJry+yWeljWqqfqFmb14P3
   o=;
IronPort-SDR: 
 xKXqD6u391c+OPPFLkfgFObJnH8ci8DraJaHwkHovgvDksG5hUyeDzvv0HdPX74EzjsCYIb/3t
 g+H4vbP+5hrg==
X-IronPort-AV: E=Sophos;i="5.75,436,1589241600";
   d="scan'208";a="57530549"
Received: from sea32-co-svc-lb4-vlan3.sea.corp.amazon.com (HELO
 email-inbound-relay-2c-579b7f5b.us-west-2.amazon.com) ([10.47.23.38])
  by smtp-border-fw-out-9101.sea19.amazon.com with ESMTP;
 05 Aug 2020 09:10:45 +0000
Received: from EX13MTAUEA002.ant.amazon.com
 (pdx4-ws-svc-p6-lb7-vlan3.pdx.amazon.com [10.170.41.166])
        by email-inbound-relay-2c-579b7f5b.us-west-2.amazon.com (Postfix) with
 ESMTPS id 72280A2886;
        Wed,  5 Aug 2020 09:10:44 +0000 (UTC)
Received: from EX13D16EUB003.ant.amazon.com (10.43.166.99) by
 EX13MTAUEA002.ant.amazon.com (10.43.61.77) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Wed, 5 Aug 2020 09:10:43 +0000
Received: from 38f9d34ed3b1.ant.amazon.com (10.43.160.26) by
 EX13D16EUB003.ant.amazon.com (10.43.166.99) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Wed, 5 Aug 2020 09:10:33 +0000
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
        Balbir Singh <sblbir@amazon.com>,
        Stefano Garzarella <sgarzare@redhat.com>,
        "Stefan Hajnoczi" <stefanha@redhat.com>,
        Stewart Smith <trawets@amazon.com>,
        "Uwe Dannowski" <uwed@amazon.de>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        kvm <kvm@vger.kernel.org>,
        ne-devel-upstream <ne-devel-upstream@amazon.com>,
        Andra Paraschiv <andraprs@amazon.com>
Subject: [PATCH v6 01/18] nitro_enclaves: Add ioctl interface definition
Date: Wed, 5 Aug 2020 12:10:00 +0300
Message-ID: <20200805091017.86203-2-andraprs@amazon.com>
X-Mailer: git-send-email 2.20.1 (Apple Git-117)
In-Reply-To: <20200805091017.86203-1-andraprs@amazon.com>
References: <20200805091017.86203-1-andraprs@amazon.com>
MIME-Version: 1.0
X-Originating-IP: [10.43.160.26]
X-ClientProxiedBy: EX13D03UWA003.ant.amazon.com (10.43.160.39) To
 EX13D16EUB003.ant.amazon.com (10.43.166.99)
Sender: kvm-owner@vger.kernel.org
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

Signed-off-by: Alexandru Vasile <lexnv@amazon.com>
Signed-off-by: Andra Paraschiv <andraprs@amazon.com>
Reviewed-by: Alexander Graf <graf@amazon.com>
Reviewed-by: Stefan Hajnoczi <stefanha@redhat.com>
---
Changelog

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
---
 .../userspace-api/ioctl/ioctl-number.rst      |   5 +-
 include/linux/nitro_enclaves.h                |  11 +
 include/uapi/linux/nitro_enclaves.h           | 327 ++++++++++++++++++
 3 files changed, 342 insertions(+), 1 deletion(-)
 create mode 100644 include/linux/nitro_enclaves.h
 create mode 100644 include/uapi/linux/nitro_enclaves.h

```
#### [GIT PULL] First batch of KVM changes for Linux 5.9
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11702357
Return-Path: <SRS0=UpKl=BP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 86AD914E3
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  5 Aug 2020 19:12:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 678132084D
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  5 Aug 2020 19:12:20 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="f3ouCTk0"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729024AbgHETMT (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 5 Aug 2020 15:12:19 -0400
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:31772 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1729241AbgHES1X (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 5 Aug 2020 14:27:23 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1596651982;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=NY6yDRCEkpDg5LXNyaSXdjYfolIgk3OXFlkk/eTLcfo=;
        b=f3ouCTk08IwmV2TOjtMlzOCsHmgkojNijPv3k4PQVN50fCt0B0GCxCwSE0pde1yfw/PAe4
        QifpmLo1kQP8tRPUR26QLYtjqX9dANE36djG/PlIH/087YuEuRYToR6v35OBLq647T0Bpn
        novRGLzgvZ6fWGVQYCj6QXQjgaAzJ3Y=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-39-NIBy4lHNMPuW20DwNN_t3g-1; Wed, 05 Aug 2020 14:26:09 -0400
X-MC-Unique: NIBy4lHNMPuW20DwNN_t3g-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id EA9A210059A7;
        Wed,  5 Aug 2020 18:26:07 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 794135F202;
        Wed,  5 Aug 2020 18:26:07 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: torvalds@linux-foundation.org
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [GIT PULL] First batch of KVM changes for Linux 5.9
Date: Wed,  5 Aug 2020 14:26:06 -0400
Message-Id: <20200805182606.12621-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Linus,

The following changes since commit 8038a922cf9af5266eaff29ce996a0d1b788fc0d:

  Merge tag 'kvmarm-fixes-5.8-3' of git://git.kernel.org/pub/scm/linux/kernel/git/kvmarm/kvmarm into kvm-master (2020-07-06 13:05:38 -0400)

are available in the Git repository at:

  https://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to f3633c2683545213de4a00a9b0c3fba741321fb2:

  Merge tag 'kvm-s390-next-5.9-1' of git://git.kernel.org/pub/scm/linux/kernel/git/kvms390/linux into kvm-next-5.6 (2020-08-03 14:19:13 -0400)

----------------------------------------------------------------
s390: implement diag318

x86:
* Report last CPU for debugging
* Emulate smaller MAXPHYADDR in the guest than in the host
* .noinstr and tracing fixes from Thomas
* nested SVM page table switching optimization and fixes

Generic:
* Unify shadow MMU cache data structures across architectures

----------------------------------------------------------------

There is a conflict in arch/x86/kernel/kvm.c that git will only
partially report.  idtentry_enter_cond_rcu and idtentry_exit_cond_rcu
have been renamed to idtentry_enter and idtentry_exit and their return
type went from bool to idtentry_state_t.  There are two occurrences
but git will only notice the first one (and only partly so, it misses
the function calls altogether).

The resolution is simple, but I've included it at the end of this message
anyway.

Thanks,

Paolo

Colin Ian King (1):
      KVM: MIPS: fix spelling mistake "Exteneded" -> "Extended"

Collin Walling (2):
      s390/setup: diag 318: refactor struct
      s390/kvm: diagnose 0x318 sync and reset

Dan Carpenter (1):
      KVM: SVM: Fix sev_pin_memory() error handling

Haiwei Li (1):
      KVM: Using macros instead of magic values

Huacai Chen (1):
      MIPS: KVM: Fix build error caused by 'kvm_run' cleanup

Jiaxun Yang (2):
      MIPS: KVM: Limit Trap-and-Emulate to MIPS32R2 only
      MIPS: KVM: Remove outdated README

Jim Mattson (7):
      kvm: svm: Prefer vcpu->cpu to raw_smp_processor_id()
      kvm: svm: Always set svm->last_cpu on VMRUN
      kvm: vmx: Add last_cpu to struct vcpu_vmx
      kvm: x86: Add "last CPU" to some KVM_EXIT information
      kvm: x86: Move last_cpu into kvm_vcpu_arch as last_vmentry_cpu
      kvm: x86: Set last_vmentry_cpu in vcpu_enter_guest
      kvm: x86: Read PDPTEs on CR0.CD and CR0.NW changes

Joerg Roedel (4):
      KVM: SVM: Rename struct nested_state to svm_nested_state
      KVM: SVM: Add vmcb_ prefix to mark_*() functions
      KVM: SVM: Add svm_ prefix to set/clr/is_intercept()
      KVM: SVM: Rename svm_nested_virtualize_tpr() to nested_svm_virtualize_tpr()

John Hubbard (2):
      KVM: SVM: fix svn_pin_memory()'s use of get_user_pages_fast()
      KVM: SVM: convert get_user_pages() --> pin_user_pages()

Krish Sadhukhan (4):
      KVM: x86: Move the check for upper 32 reserved bits of DR6 to separate function
      KVM: nSVM: Check that DR6[63:32] and DR7[64:32] are not set on vmrun of nested guests
      KVM: x86: Create mask for guest CR4 reserved bits in kvm_update_cpuid()
      KVM: nSVM: Check that MBZ bits in CR3 and CR4 are not set on vmrun of nested guests

Like Xu (2):
      kvm: x86: limit the maximum number of vPMU fixed counters to 3
      KVM/x86: pmu: Fix #GP condition check for RDPMC emulation

Maxim Levitsky (1):
      kvm: x86: replace kvm_spec_ctrl_test_value with runtime test on the host

Mohammed Gamal (5):
      KVM: x86: Add helper functions for illegal GPA checking and page fault injection
      KVM: x86: mmu: Move translate_gpa() to mmu.c
      KVM: x86: mmu: Add guest physical address check in translate_gpa()
      KVM: VMX: Add guest physical address check in EPT violation and misconfig
      KVM: x86: Add a capability for GUEST_MAXPHYADDR < HOST_MAXPHYADDR support

Paolo Bonzini (11):
      Merge branch 'kvm-async-pf-int' into HEAD
      Merge branch 'kvm-master' into HEAD
      KVM: x86: report sev_pin_memory errors with PTR_ERR
      KVM: x86: Make CR4.VMXE reserved for the guest
      KVM: MMU: stop dereferencing vcpu->arch.mmu to get the context for MMU init
      KVM: x86: rename update_bp_intercept to update_exception_bitmap
      KVM: x86: update exception bitmap on CPUID changes
      KVM: VMX: introduce vmx_need_pf_intercept
      KVM: VMX: optimize #PF injection when MAXPHYADDR does not match
      KVM: nSVM: remove nonsensical EXITINFO1 adjustment on nested NPF
      Merge tag 'kvm-s390-next-5.9-1' of git://git.kernel.org/.../kvms390/linux into kvm-next-5.6

Peter Xu (2):
      KVM: X86: Move ignore_msrs handling upper the stack
      KVM: X86: Do the same ignore_msrs check for feature msrs

Sean Christopherson (46):
      KVM: x86/mmu: Drop kvm_arch_write_log_dirty() wrapper
      KVM: nVMX: WARN if PML emulation helper is invoked outside of nested guest
      KVM: x86/mmu: Make .write_log_dirty a nested operation
      KVM: nVMX: Wrap VM-Fail valid path in generic VM-Fail helper
      KVM: x86/mmu: Avoid multiple hash lookups in kvm_get_mmu_page()
      KVM: x86/mmu: Optimize MMU page cache lookup for fully direct MMUs
      KVM: x86/mmu: Don't put invalid SPs back on the list of active pages
      KVM: x86/mmu: Batch zap MMU pages when recycling oldest pages
      KVM: x86/mmu: Batch zap MMU pages when shrinking the slab
      KVM: x86/mmu: Exit to userspace on make_mmu_pages_available() error
      KVM: x86/mmu: Move mmu_audit.c and mmutrace.h into the mmu/ sub-directory
      KVM: x86/mmu: Move kvm_mmu_available_pages() into mmu.c
      KVM: x86/mmu: Add MMU-internal header
      KVM: x86/mmu: Make kvm_mmu_page definition and accessor internal-only
      KVM: x86/mmu: Add sptep_to_sp() helper to wrap shadow page lookup
      KVM: x86/mmu: Rename page_header() to to_shadow_page()
      KVM: x86/mmu: Track the associated kmem_cache in the MMU caches
      KVM: x86/mmu: Consolidate "page" variant of memory cache helpers
      KVM: x86/mmu: Use consistent "mc" name for kvm_mmu_memory_cache locals
      KVM: x86/mmu: Remove superfluous gotos from mmu_topup_memory_caches()
      KVM: x86/mmu: Try to avoid crashing KVM if a MMU memory cache is empty
      KVM: x86/mmu: Move fast_page_fault() call above mmu_topup_memory_caches()
      KVM: x86/mmu: Topup memory caches after walking GVA->GPA
      KVM: x86/mmu: Clean up the gorilla math in mmu_topup_memory_caches()
      KVM: x86/mmu: Separate the memory caches for shadow pages and gfn arrays
      KVM: x86/mmu: Make __GFP_ZERO a property of the memory cache
      KVM: x86/mmu: Zero allocate shadow pages (outside of mmu_lock)
      KVM: x86/mmu: Skip filling the gfn cache for guaranteed direct MMU topups
      KVM: x86/mmu: Prepend "kvm_" to memory cache helpers that will be global
      KVM: Move x86's version of struct kvm_mmu_memory_cache to common code
      KVM: Move x86's MMU memory cache helpers to common KVM code
      KVM: arm64: Drop @max param from mmu_topup_memory_cache()
      KVM: arm64: Use common code's approach for __GFP_ZERO with memory caches
      KVM: arm64: Use common KVM implementation of MMU memory caches
      KVM: MIPS: Drop @max param from mmu_topup_memory_cache()
      KVM: MIPS: Account pages used for GPA page tables
      KVM: MIPS: Use common KVM implementation of MMU memory caches
      KVM: nSVM: Correctly set the shadow NPT root level in its MMU role
      KVM: VMX: Drop a duplicate declaration of construct_eptp()
      KVM: x86/mmu: Add separate helper for shadow NPT root page role calc
      KVM: VMX: Make vmx_load_mmu_pgd() static
      KVM: x86: Pull the PGD's level from the MMU instead of recalculating it
      KVM: VXM: Remove temporary WARN on expected vs. actual EPTP level mismatch
      KVM: x86: Dynamically calculate TDP level from max level and MAXPHYADDR
      KVM: x86/mmu: Rename max_page_level to max_huge_page_level
      KVM: x86: Specify max TDP level via kvm_configure_mmu()

Thomas Gleixner (7):
      x86/kvm: Move context tracking where it belongs
      x86/kvm/vmx: Add hardirq tracing to guest enter/exit
      x86/kvm/svm: Add hardirq tracing on guest enter/exit
      x86/kvm/vmx: Move guest enter/exit into .noinstr.text
      x86/kvm/svm: Move guest enter/exit into .noinstr.text
      x86/kvm/svm: Use uninstrumented wrmsrl() to restore GS
      x86/kvm/vmx: Use native read/write_cr2()

Tianjia Zhang (3):
      KVM: s390: clean up redundant 'kvm_run' parameters
      KVM: arm64: clean up redundant 'kvm_run' parameters
      KVM: MIPS: clean up redundant 'kvm_run' parameters

Uros Bizjak (1):
      KVM: x86: Use VMCALL and VMMCALL mnemonics in kvm_para.h

Vitaly Kuznetsov (13):
      KVM: x86: Switch KVM guest to using interrupts for page ready APF delivery
      KVM: x86: drop KVM_PV_REASON_PAGE_READY case from kvm_handle_page_fault()
      KVM: async_pf: change kvm_setup_async_pf()/kvm_arch_setup_async_pf() return type to bool
      KVM: x86: take as_id into account when checking PGD
      KVM: x86: move MSR_IA32_PERF_CAPABILITIES emulation to common x86 code
      KVM: nSVM: split kvm_init_shadow_npt_mmu() from kvm_init_shadow_mmu()
      KVM: nSVM: reset nested_run_pending upon nested_svm_vmrun_msrpm() failure
      KVM: nSVM: prepare to handle errors from enter_svm_guest_mode()
      KVM: nSVM: introduce nested_svm_load_cr3()/nested_npt_enabled()
      KVM: nSVM: move kvm_set_cr3() after nested_svm_uninit_mmu_context()
      KVM: nSVM: implement nested_svm_load_cr3() and use it for host->guest switch
      KVM: nSVM: use nested_svm_load_cr3() on guest->host switch
      KVM: x86: drop superfluous mmu_check_root() from fast_pgd_switch()

Wanpeng Li (1):
      KVM: LAPIC: Set the TDCR settable bits

Xiaoyao Li (9):
      KVM: X86: Reset vcpu->arch.cpuid_nent to 0 if SET_CPUID* fails
      KVM: X86: Go on updating other CPUID leaves when leaf 1 is absent
      KVM: lapic: Use guest_cpuid_has() in kvm_apic_set_version()
      KVM: X86: Move kvm_apic_set_version() to kvm_update_cpuid()
      KVM: x86: Introduce kvm_check_cpuid()
      KVM: x86: Extract kvm_update_cpuid_runtime() from kvm_update_cpuid()
      KVM: x86: Rename kvm_update_cpuid() to kvm_vcpu_after_set_cpuid()
      KVM: x86: Rename cpuid_update() callback to vcpu_after_set_cpuid()
      KVM: x86: Move kvm_x86_ops.vcpu_after_set_cpuid() into kvm_vcpu_after_set_cpuid()

Zhenzhong Duan (4):
      Revert "KVM: X86: Fix setup the virt_spin_lock_key before static key get initialized"
      x86/kvm: Change print code to use pr_*() format
      x86/kvm: Add "nopvspin" parameter to disable PV spinlocks
      xen: Mark "xen_nopvspin" parameter obsolete

 Documentation/admin-guide/kernel-parameters.txt |  10 +-
 Documentation/virt/kvm/api.rst                  |   5 +
 arch/arm64/include/asm/kvm_coproc.h             |  12 +-
 arch/arm64/include/asm/kvm_host.h               |  22 +-
 arch/arm64/include/asm/kvm_mmu.h                |   2 +-
 arch/arm64/include/asm/kvm_types.h              |   8 +
 arch/arm64/kvm/arm.c                            |   8 +-
 arch/arm64/kvm/handle_exit.c                    |  36 +-
 arch/arm64/kvm/mmio.c                           |  11 +-
 arch/arm64/kvm/mmu.c                            |  61 +---
 arch/arm64/kvm/sys_regs.c                       |  13 +-
 arch/mips/Kconfig                               |   1 +
 arch/mips/include/asm/kvm_host.h                |  39 +-
 arch/mips/include/asm/kvm_types.h               |   7 +
 arch/mips/kvm/00README.txt                      |  31 --
 arch/mips/kvm/Kconfig                           |   3 +-
 arch/mips/kvm/emulate.c                         |  65 ++--
 arch/mips/kvm/mips.c                            |  11 +-
 arch/mips/kvm/mmu.c                             |  44 +--
 arch/mips/kvm/trap_emul.c                       | 114 +++---
 arch/mips/kvm/vz.c                              |  26 +-
 arch/powerpc/include/asm/Kbuild                 |   1 +
 arch/s390/include/asm/Kbuild                    |   1 +
 arch/s390/include/asm/diag.h                    |   6 +-
 arch/s390/include/asm/kvm_host.h                |   4 +-
 arch/s390/include/uapi/asm/kvm.h                |   7 +-
 arch/s390/kernel/setup.c                        |   3 +-
 arch/s390/kvm/kvm-s390.c                        |  54 ++-
 arch/s390/kvm/vsie.c                            |   1 +
 arch/x86/Kconfig                                |   1 +
 arch/x86/include/asm/hardirq.h                  |   4 +-
 arch/x86/include/asm/idtentry.h                 |   4 +
 arch/x86/include/asm/kvm_host.h                 |  95 ++---
 arch/x86/include/asm/kvm_para.h                 |   3 +-
 arch/x86/include/asm/kvm_types.h                |   7 +
 arch/x86/include/asm/qspinlock.h                |   1 +
 arch/x86/kernel/kvm.c                           | 118 ++++--
 arch/x86/kvm/cpuid.c                            | 115 +++---
 arch/x86/kvm/cpuid.h                            |   2 +-
 arch/x86/kvm/lapic.c                            |  11 +-
 arch/x86/kvm/mmu.h                              |  34 +-
 arch/x86/kvm/mmu/mmu.c                          | 461 +++++++++++++-----------
 arch/x86/kvm/{ => mmu}/mmu_audit.c              |  12 +-
 arch/x86/kvm/mmu/mmu_internal.h                 |  63 ++++
 arch/x86/kvm/{ => mmu}/mmutrace.h               |   2 +-
 arch/x86/kvm/mmu/page_track.c                   |   2 +-
 arch/x86/kvm/mmu/paging_tmpl.h                  |  19 +-
 arch/x86/kvm/pmu.c                              |   5 +
 arch/x86/kvm/pmu.h                              |   2 +
 arch/x86/kvm/svm/avic.c                         |   2 +-
 arch/x86/kvm/svm/nested.c                       | 142 ++++++--
 arch/x86/kvm/svm/sev.c                          |  47 +--
 arch/x86/kvm/svm/svm.c                          | 262 +++++++++-----
 arch/x86/kvm/svm/svm.h                          |  32 +-
 arch/x86/kvm/svm/vmenter.S                      |   2 +-
 arch/x86/kvm/vmx/nested.c                       | 149 +++++---
 arch/x86/kvm/vmx/ops.h                          |   4 +
 arch/x86/kvm/vmx/pmu_intel.c                    |  17 -
 arch/x86/kvm/vmx/vmenter.S                      |   5 +-
 arch/x86/kvm/vmx/vmx.c                          | 209 ++++++-----
 arch/x86/kvm/vmx/vmx.h                          |  12 +-
 arch/x86/kvm/x86.c                              | 231 +++++++-----
 arch/x86/kvm/x86.h                              |  34 +-
 arch/x86/xen/spinlock.c                         |   4 +-
 include/asm-generic/kvm_types.h                 |   5 +
 include/linux/kvm_host.h                        |  12 +-
 include/linux/kvm_types.h                       |  19 +
 include/uapi/linux/kvm.h                        |   4 +
 kernel/locking/qspinlock.c                      |   7 +
 virt/kvm/async_pf.c                             |  16 +-
 virt/kvm/kvm_main.c                             |  63 ++++
 71 files changed, 1633 insertions(+), 1212 deletions(-)
 create mode 100644 arch/arm64/include/asm/kvm_types.h
 create mode 100644 arch/mips/include/asm/kvm_types.h
 delete mode 100644 arch/mips/kvm/00README.txt
 create mode 100644 arch/x86/include/asm/kvm_types.h
 rename arch/x86/kvm/{ => mmu}/mmu_audit.c (96%)
 create mode 100644 arch/x86/kvm/mmu/mmu_internal.h
 rename arch/x86/kvm/{ => mmu}/mmutrace.h (99%)
 create mode 100644 include/asm-generic/kvm_types.h

+++ b/arch/x86/kernel/kvm.c
@@@ -34,6 -31,6 +34,7 @@@
  #include <asm/apic.h>
  #include <asm/apicdef.h>
  #include <asm/hypervisor.h>
++#include <asm/idtentry.h>
  #include <asm/tlb.h>
  #include <asm/cpuidle_haltpoll.h>
  
@@@ -235,13 -232,18 +236,13 @@@ EXPORT_SYMBOL_GPL(kvm_read_and_reset_ap
  
  noinstr bool __kvm_handle_async_pf(struct pt_regs *regs, u32 token)
  {
 -	u32 reason = kvm_read_and_reset_apf_flags();
 +	u32 flags = kvm_read_and_reset_apf_flags();
- 	bool rcu_exit;
+ 	idtentry_state_t state;
  
 -	switch (reason) {
 -	case KVM_PV_REASON_PAGE_NOT_PRESENT:
 -	case KVM_PV_REASON_PAGE_READY:
 -		break;
 -	default:
 +	if (!flags)
  		return false;
 -	}
  
- 	rcu_exit = idtentry_enter_cond_rcu(regs);
+ 	state = idtentry_enter(regs);
  	instrumentation_begin();
  
  	/*
@@@ -266,27 -268,6 +267,27 @@@
  	return true;
  }
  
 +DEFINE_IDTENTRY_SYSVEC(sysvec_kvm_asyncpf_interrupt)
 +{
 +	struct pt_regs *old_regs = set_irq_regs(regs);
 +	u32 token;
- 	bool rcu_exit;
++	idtentry_state_t rcu_exit;
 +
- 	rcu_exit = idtentry_enter_cond_rcu(regs);
++	rcu_exit = idtentry_enter(regs);
 +
 +	inc_irq_stat(irq_hv_callback_count);
 +
 +	if (__this_cpu_read(apf_reason.enabled)) {
 +		token = __this_cpu_read(apf_reason.token);
 +		kvm_async_pf_task_wake(token);
 +		__this_cpu_write(apf_reason.token, 0);
 +		wrmsrl(MSR_KVM_ASYNC_PF_ACK, 1);
 +	}
 +
- 	idtentry_exit_cond_rcu(regs, rcu_exit);
++	idtentry_exit(regs, rcu_exit);
 +	set_irq_regs(old_regs);
 +}
 +
  static void __init paravirt_ops_setup(void)
  {
  	pv_info.name = "KVM";

```
#### [GIT PULL] KVM/arm64 updates for 5.9
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11702051
Return-Path: <SRS0=UpKl=BP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F09E614DD
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  5 Aug 2020 17:58:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CD94022CA1
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  5 Aug 2020 17:58:48 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1596650328;
	bh=juxLV+E099RYtCa22t1sG7pfJtqygQtV/DctUYidP+8=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=nhIAnJVmXVTpCdap8NqK7e7jIBaXJZDz3+eeKwHEpI/XWUdQG0noquOc7E8ftZ5fv
	 syLyzlB8P8J4+CFwBaMOKK15HIieRJJSrl0yy1cV23E1YmZYe8K24MdXuG3/hs9UH4
	 ipa36AtVjvW+3HzulTh4gXf+W/85XbIyNjBNLfpc=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729074AbgHER6r (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 5 Aug 2020 13:58:47 -0400
Received: from mail.kernel.org ([198.145.29.99]:45232 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729070AbgHER5o (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 5 Aug 2020 13:57:44 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 521BF2173E;
        Wed,  5 Aug 2020 17:57:13 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1596650233;
        bh=juxLV+E099RYtCa22t1sG7pfJtqygQtV/DctUYidP+8=;
        h=From:To:Cc:Subject:Date:From;
        b=fknGdJhK+d4oiugSSghMjrgTAQf3oBOGIkhxZU5vcURpee/7rXEI+huuFVUTisMKj
         rGTKnkZ2rvdlOxU+m28rcLEOSM9F81K05R5gaeuAOZeUPIdrO+c8WPhgH+actxu8Ny
         ildEsE/4ODjIWwfxcSi3alrx4Agvgi5NLh72wHLA=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1k3Nf5-0004w9-Pn; Wed, 05 Aug 2020 18:57:11 +0100
From: Marc Zyngier <maz@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Alexander Graf <graf@amazon.com>,
        Alexandru Elisei <alexandru.elisei@arm.com>,
        Andrew Scull <ascull@google.com>,
        Catalin Marinas <catalin.marinas@arm.com>,
        Christoffer Dall <christoffer.dall@arm.com>,
        David Brazdil <dbrazdil@google.com>,
        Eric Auger <eric.auger@redhat.com>,
        Gavin Shan <gshan@redhat.com>,
        James Morse <james.morse@arm.com>,
        Mark Rutland <mark.rutland@arm.com>,
        Peng Hao <richard.peng@oppo.com>,
        Quentin Perret <qperret@google.com>,
        Will Deacon <will@kernel.org>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org, kernel-team@android.com
Subject: [GIT PULL] KVM/arm64 updates for 5.9
Date: Wed,  5 Aug 2020 18:56:04 +0100
Message-Id: <20200805175700.62775-1-maz@kernel.org>
X-Mailer: git-send-email 2.27.0
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: pbonzini@redhat.com, graf@amazon.com,
 alexandru.elisei@arm.com, ascull@google.com, catalin.marinas@arm.com,
 christoffer.dall@arm.com, dbrazdil@google.com, eric.auger@redhat.com,
 gshan@redhat.com, james.morse@arm.com, mark.rutland@arm.com,
 richard.peng@oppo.com, qperret@google.com, will@kernel.org,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
 kvm@vger.kernel.org, kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Paolo,

This is the bulk of the 5.9 patches for KVM/arm64. It is a pretty busy
merge window for us this time, thanks to the ongoing Protected KVM
work. We have changes all over the map, but the most important piece
probably is the way we now build the EL2 code on non-VHE systems. On
top of giving us better control over what gets pulled in there, it
allowed us to enable instrumentation on VHE systems.

The rest is a mixed bag of new features (TTL TLB invalidation, Pointer
Auth on non-VHE), preliminary patches for NV, some early MMU rework
before the 5.10 onslaught, and tons of cleanups.

A few things to notice:

- We share a branch with the arm64 tree, which has gone in already.

- There are a number of known conflicts with Sean's MMU cache rework,
  as well as the late fixes that went in 5.8. The conflicts are pretty
  simple to resolve, and -next has the right resolutions already.

Please pull,

	M.

The following changes since commit 9ebcfadb0610322ac537dd7aa5d9cbc2b2894c68:

  Linux 5.8-rc3 (2020-06-28 15:00:24 -0700)

are available in the Git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/kvmarm/kvmarm.git tags/kvmarm-5.9

for you to fetch changes up to 16314874b12b451bd5a1df86bcb69745eb487502:

  Merge branch 'kvm-arm64/misc-5.9' into kvmarm-master/next (2020-07-30 16:13:04 +0100)

----------------------------------------------------------------
KVM/arm64 updates for Linux 5.9:

- Split the VHE and nVHE hypervisor code bases, build the EL2 code
  separately, allowing for the VHE code to now be built with instrumentation

- Level-based TLB invalidation support

- Restructure of the vcpu register storage to accomodate the NV code

- Pointer Authentication available for guests on nVHE hosts

- Simplification of the system register table parsing

- MMU cleanups and fixes

- A number of post-32bit cleanups and other fixes

----------------------------------------------------------------
Alexander Graf (2):
      KVM: arm64: vgic-its: Change default outer cacheability for {PEND, PROP}BASER
      KVM: arm: Add trace name for ARM_NISV

Andrew Scull (3):
      arm64: kvm: Remove kern_hyp_va from get_vcpu_ptr
      KVM: arm64: Handle calls to prefixed hyp functions
      KVM: arm64: Move hyp-init.S to nVHE

Christoffer Dall (1):
      KVM: arm64: Factor out stage 2 page table data from struct kvm

David Brazdil (16):
      KVM: arm64: Fix symbol dependency in __hyp_call_panic_nvhe
      KVM: arm64: Move __smccc_workaround_1_smc to .rodata
      KVM: arm64: Add build rules for separate VHE/nVHE object files
      KVM: arm64: Use build-time defines in has_vhe()
      KVM: arm64: Build hyp-entry.S separately for VHE/nVHE
      KVM: arm64: Duplicate hyp/tlb.c for VHE/nVHE
      KVM: arm64: Split hyp/switch.c to VHE/nVHE
      KVM: arm64: Split hyp/debug-sr.c to VHE/nVHE
      KVM: arm64: Split hyp/sysreg-sr.c to VHE/nVHE
      KVM: arm64: Duplicate hyp/timer-sr.c for VHE/nVHE
      KVM: arm64: Compile remaining hyp/ files for both VHE/nVHE
      KVM: arm64: Remove __hyp_text macro, use build rules instead
      KVM: arm64: Lift instrumentation restrictions on VHE
      KVM: arm64: Make nVHE ASLR conditional on RANDOMIZE_BASE
      KVM: arm64: Substitute RANDOMIZE_BASE for HARDEN_EL2_VECTORS
      KVM: arm64: Ensure that all nVHE hyp code is in .hyp.text

Gavin Shan (1):
      KVM: arm64: Rename HSR to ESR

James Morse (5):
      KVM: arm64: Drop the target_table[] indirection
      KVM: arm64: Tolerate an empty target_table list
      KVM: arm64: Move ACTLR_EL1 emulation to the sys_reg_descs array
      KVM: arm64: Remove target_table from exit handlers
      KVM: arm64: Remove the target table

Marc Zyngier (31):
      KVM: arm64: Enable Address Authentication at EL2 if available
      KVM: arm64: Allow ARM64_PTR_AUTH when ARM64_VHE=n
      KVM: arm64: Allow PtrAuth to be enabled from userspace on non-VHE systems
      KVM: arm64: Check HCR_EL2 instead of shadow copy to swap PtrAuth registers
      KVM: arm64: Simplify PtrAuth alternative patching
      KVM: arm64: Allow in-atomic injection of SPIs
      arm64: Detect the ARMv8.4 TTL feature
      arm64: Document SW reserved PTE/PMD bits in Stage-2 descriptors
      arm64: Add level-hinted TLB invalidation helper
      Merge branch 'kvm-arm64/ttl-for-arm64' into HEAD
      KVM: arm64: Use TTL hint in when invalidating stage-2 translations
      KVM: arm64: Introduce accessor for ctxt->sys_reg
      KVM: arm64: hyp: Use ctxt_sys_reg/__vcpu_sys_reg instead of raw sys_regs access
      KVM: arm64: sve: Use __vcpu_sys_reg() instead of raw sys_regs access
      KVM: arm64: pauth: Use ctxt_sys_reg() instead of raw sys_regs access
      KVM: arm64: debug: Drop useless vpcu parameter
      KVM: arm64: Make struct kvm_regs userspace-only
      KVM: arm64: Move ELR_EL1 to the system register array
      KVM: arm64: Move SP_EL1 to the system register array
      KVM: arm64: Disintegrate SPSR array
      KVM: arm64: Move SPSR_EL1 to the system register array
      KVM: arm64: timers: Rename kvm_timer_sync_hwstate to kvm_timer_sync_user
      KVM: arm64: timers: Move timer registers to the sys_regs file
      KVM: arm64: Don't use has_vhe() for CHOOSE_HYP_SYM()
      Merge branch 'kvm-arm64/el2-obj-v4.1' into kvmarm-master/next-WIP
      Merge branch 'kvm-arm64/pre-nv-5.9' into kvmarm-master/next-WIP
      Merge branch 'kvm-arm64/ptrauth-nvhe' into kvmarm-master/next-WIP
      Merge branch 'kvm-arm64/target-table-no-more' into kvmarm-master/next-WIP
      Merge branch 'kvm-arm64/misc-5.9' into kvmarm-master/next-WIP
      Merge branch 'kvm-arm64/el2-obj-v4.1' into kvmarm-master/next
      Merge branch 'kvm-arm64/misc-5.9' into kvmarm-master/next

Peng Hao (1):
      KVM: arm64: Drop long gone function parameter documentation

Will Deacon (4):
      KVM: arm64: Rename kvm_vcpu_dabt_isextabt()
      KVM: arm64: Handle data and instruction external aborts the same way
      KVM: arm64: Don't skip cache maintenance for read-only memslots
      KVM: arm64: Move S1PTW S2 fault logic out of io_mem_abort()

 arch/arm64/Kconfig                                 |  20 +-
 arch/arm64/include/asm/cpucaps.h                   |   3 +-
 arch/arm64/include/asm/kvm_asm.h                   |  75 +-
 arch/arm64/include/asm/kvm_coproc.h                |   8 -
 arch/arm64/include/asm/kvm_emulate.h               |  75 +-
 arch/arm64/include/asm/kvm_host.h                  |  94 ++-
 arch/arm64/include/asm/kvm_hyp.h                   |  15 +-
 arch/arm64/include/asm/kvm_mmu.h                   |  16 +-
 arch/arm64/include/asm/kvm_ptrauth.h               |  34 +-
 arch/arm64/include/asm/mmu.h                       |   7 -
 arch/arm64/include/asm/pgtable-hwdef.h             |   2 +
 arch/arm64/include/asm/stage2_pgtable.h            |   9 +
 arch/arm64/include/asm/sysreg.h                    |   1 +
 arch/arm64/include/asm/tlbflush.h                  |  45 +
 arch/arm64/include/asm/virt.h                      |  13 +-
 arch/arm64/kernel/asm-offsets.c                    |   3 +-
 arch/arm64/kernel/cpu_errata.c                     |   4 +-
 arch/arm64/kernel/cpufeature.c                     |  11 +
 arch/arm64/kernel/image-vars.h                     |  54 ++
 arch/arm64/kvm/Kconfig                             |   2 +-
 arch/arm64/kvm/Makefile                            |   4 +-
 arch/arm64/kvm/arch_timer.c                        | 157 +++-
 arch/arm64/kvm/arm.c                               |  57 +-
 arch/arm64/kvm/fpsimd.c                            |   6 +-
 arch/arm64/kvm/guest.c                             |  79 +-
 arch/arm64/kvm/handle_exit.c                       |  32 +-
 arch/arm64/kvm/hyp/Makefile                        |  24 +-
 arch/arm64/kvm/hyp/aarch32.c                       |   8 +-
 arch/arm64/kvm/hyp/entry.S                         |   4 +-
 arch/arm64/kvm/hyp/fpsimd.S                        |   1 -
 arch/arm64/kvm/hyp/hyp-entry.S                     |  21 +-
 .../kvm/hyp/{debug-sr.c => include/hyp/debug-sr.h} |  88 +-
 arch/arm64/kvm/hyp/include/hyp/switch.h            | 511 +++++++++++
 arch/arm64/kvm/hyp/include/hyp/sysreg-sr.h         | 193 +++++
 arch/arm64/kvm/hyp/nvhe/Makefile                   |  62 ++
 arch/arm64/kvm/hyp/nvhe/debug-sr.c                 |  77 ++
 arch/arm64/kvm/{ => hyp/nvhe}/hyp-init.S           |   5 +
 arch/arm64/kvm/hyp/nvhe/switch.c                   | 272 ++++++
 arch/arm64/kvm/hyp/nvhe/sysreg-sr.c                |  46 +
 arch/arm64/kvm/hyp/{ => nvhe}/timer-sr.c           |   6 +-
 arch/arm64/kvm/hyp/nvhe/tlb.c                      | 154 ++++
 arch/arm64/kvm/hyp/smccc_wa.S                      |  32 +
 arch/arm64/kvm/hyp/switch.c                        | 936 ---------------------
 arch/arm64/kvm/hyp/sysreg-sr.c                     | 333 --------
 arch/arm64/kvm/hyp/tlb.c                           | 242 ------
 arch/arm64/kvm/hyp/vgic-v2-cpuif-proxy.c           |   4 +-
 arch/arm64/kvm/hyp/vgic-v3-sr.c                    | 134 ++-
 arch/arm64/kvm/hyp/vhe/Makefile                    |  11 +
 arch/arm64/kvm/hyp/vhe/debug-sr.c                  |  26 +
 arch/arm64/kvm/hyp/vhe/switch.c                    | 219 +++++
 arch/arm64/kvm/hyp/vhe/sysreg-sr.c                 | 114 +++
 arch/arm64/kvm/hyp/vhe/timer-sr.c                  |  12 +
 arch/arm64/kvm/hyp/vhe/tlb.c                       | 162 ++++
 arch/arm64/kvm/inject_fault.c                      |   2 +-
 arch/arm64/kvm/mmio.c                              |   6 -
 arch/arm64/kvm/mmu.c                               | 311 ++++---
 arch/arm64/kvm/regmap.c                            |  37 +-
 arch/arm64/kvm/reset.c                             |  23 +-
 arch/arm64/kvm/sys_regs.c                          | 207 ++---
 arch/arm64/kvm/sys_regs_generic_v8.c               |  96 ---
 arch/arm64/kvm/trace_arm.h                         |   8 +-
 arch/arm64/kvm/va_layout.c                         |   2 +-
 arch/arm64/kvm/vgic/vgic-irqfd.c                   |  24 +-
 arch/arm64/kvm/vgic/vgic-its.c                     |   3 +-
 arch/arm64/kvm/vgic/vgic-mmio-v3.c                 |   2 +-
 include/kvm/arm_arch_timer.h                       |  13 +-
 include/trace/events/kvm.h                         |   2 +-
 scripts/kallsyms.c                                 |   1 +
 68 files changed, 2883 insertions(+), 2377 deletions(-)
 rename arch/arm64/kvm/hyp/{debug-sr.c => include/hyp/debug-sr.h} (66%)
 create mode 100644 arch/arm64/kvm/hyp/include/hyp/switch.h
 create mode 100644 arch/arm64/kvm/hyp/include/hyp/sysreg-sr.h
 create mode 100644 arch/arm64/kvm/hyp/nvhe/Makefile
 create mode 100644 arch/arm64/kvm/hyp/nvhe/debug-sr.c
 rename arch/arm64/kvm/{ => hyp/nvhe}/hyp-init.S (95%)
 create mode 100644 arch/arm64/kvm/hyp/nvhe/switch.c
 create mode 100644 arch/arm64/kvm/hyp/nvhe/sysreg-sr.c
 rename arch/arm64/kvm/hyp/{ => nvhe}/timer-sr.c (84%)
 create mode 100644 arch/arm64/kvm/hyp/nvhe/tlb.c
 create mode 100644 arch/arm64/kvm/hyp/smccc_wa.S
 delete mode 100644 arch/arm64/kvm/hyp/switch.c
 delete mode 100644 arch/arm64/kvm/hyp/sysreg-sr.c
 delete mode 100644 arch/arm64/kvm/hyp/tlb.c
 create mode 100644 arch/arm64/kvm/hyp/vhe/Makefile
 create mode 100644 arch/arm64/kvm/hyp/vhe/debug-sr.c
 create mode 100644 arch/arm64/kvm/hyp/vhe/switch.c
 create mode 100644 arch/arm64/kvm/hyp/vhe/sysreg-sr.c
 create mode 100644 arch/arm64/kvm/hyp/vhe/timer-sr.c
 create mode 100644 arch/arm64/kvm/hyp/vhe/tlb.c
 delete mode 100644 arch/arm64/kvm/sys_regs_generic_v8.c
```
#### 
##### 

```c
```
#### [PATCH v3 20/38] vhost/vdpa: switch to new helpers
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 11702403
Return-Path: <SRS0=UpKl=BP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6414E722
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  5 Aug 2020 19:26:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 444252075D
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  5 Aug 2020 19:26:49 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="dR3nXJcO"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728533AbgHET0r (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 5 Aug 2020 15:26:47 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:27620 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1728642AbgHERNE (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 5 Aug 2020 13:13:04 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1596647582;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         in-reply-to:in-reply-to:references:references;
        bh=f1A99Kan+ToYvUmOMuODkd0BFkRSjBNq3WkT2nA5570=;
        b=dR3nXJcOxXQhXr4gn6VmnbjOJP1FxOpoj2yjDm2sGOB2XQpNQ99v7U/3kvvgfu2ewkayRf
        Mn68IMjrF78i0E6dWUf6UonGQbjnuSf6zeMNP4h7bmrKiCr5kRQkOMBWv3GbNGUE/rYh6a
        XuR6rfx7M4qLvf6K9kuF8xUCy8KVRQA=
Received: from mail-wr1-f72.google.com (mail-wr1-f72.google.com
 [209.85.221.72]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-173-DRXQqQi4PgmZAWl0D5soFQ-1; Wed, 05 Aug 2020 09:44:15 -0400
X-MC-Unique: DRXQqQi4PgmZAWl0D5soFQ-1
Received: by mail-wr1-f72.google.com with SMTP id t12so13689364wrp.0
        for <kvm@vger.kernel.org>; Wed, 05 Aug 2020 06:44:14 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:references
         :mime-version:content-disposition:in-reply-to;
        bh=f1A99Kan+ToYvUmOMuODkd0BFkRSjBNq3WkT2nA5570=;
        b=nebGfeD1GEUcKPf2jo3nIHPVw2HGgAfN+87OHF9lkmKAEfj8TB6NKOjtQSgOeQbDQA
         vbbqwROV0Z9alfnc6mCUyJo4sFEXjfHlLA6uBN3plKrab6akjGa9eMku4Q9M7Lzeza2v
         ZD7H6148ZtIWj4UDxUFg4CITJJcbtYLAIayqItG+vVOHI7hM9nDk4rilb3DvaSlNGD9T
         pWbWpf5/1N9Dn+S7d+aUsZtbmWBULlew2eayKAZ7iHAlZSz/o8FdLPo6xY8C5tMAsJG9
         XCUOmcFUr8359+2V390x6j8gF/KwA8rFPW9Qk8tobFi5JRFOw8h5dV8gioL/OYcAqtxq
         iXng==
X-Gm-Message-State: AOAM5327p9Xc7p8wLefVE0Axu7tDypndtkNjn8zsUPwnepiraUxJwnyS
        Odm4Djp0gh85WVvAeqBjYp2b6wBZHgrOlxv6fCiLievNIwQOjhaW4K9KM5MkCNRKlnGTURUsyO3
        14soH8VE5TayM
X-Received: by 2002:a5d:56c9:: with SMTP id m9mr2815444wrw.311.1596635052938;
        Wed, 05 Aug 2020 06:44:12 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJz1s5cwBUNfyg52XUg786M5asAtfYsirHkxCrJWthFsY+eLaHorMKAhGdLmAYB5+K4MVfGhow==
X-Received: by 2002:a5d:56c9:: with SMTP id m9mr2815427wrw.311.1596635052770;
        Wed, 05 Aug 2020 06:44:12 -0700 (PDT)
Received: from redhat.com (bzq-79-180-0-181.red.bezeqint.net. [79.180.0.181])
        by smtp.gmail.com with ESMTPSA id
 o30sm2873971wra.67.2020.08.05.06.44.11
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 05 Aug 2020 06:44:12 -0700 (PDT)
Date: Wed, 5 Aug 2020 09:44:10 -0400
From: "Michael S. Tsirkin" <mst@redhat.com>
To: linux-kernel@vger.kernel.org
Cc: Jason Wang <jasowang@redhat.com>, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org
Subject: [PATCH v3 20/38] vhost/vdpa: switch to new helpers
Message-ID: <20200805134226.1106164-21-mst@redhat.com>
References: <20200805134226.1106164-1-mst@redhat.com>
MIME-Version: 1.0
Content-Disposition: inline
In-Reply-To: <20200805134226.1106164-1-mst@redhat.com>
X-Mailer: git-send-email 2.27.0.106.g8ac3dc51b1
X-Mutt-Fcc: =sent
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

For new helpers handling legacy features to be effective,
vhost needs to invoke them. Tie them in.

Signed-off-by: Michael S. Tsirkin <mst@redhat.com>
---
 drivers/vhost/vdpa.c | 8 +++-----
 1 file changed, 3 insertions(+), 5 deletions(-)

```
#### [PATCH 1/4] kvm: x86: encapsulate wrmsr(MSR_KVM_SYSTEM_TIME) emulation in helper fn
##### From: Oliver Upton <oupton@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Oliver Upton <oupton@google.com>
X-Patchwork-Id: 11702541
Return-Path: <SRS0=UpKl=BP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 72E3A1731
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  5 Aug 2020 21:16:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5AB6821D95
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  5 Aug 2020 21:16:24 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="bXpi2JLz"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726547AbgHEVQV (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 5 Aug 2020 17:16:21 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:60626 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726217AbgHEVQR (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 5 Aug 2020 17:16:17 -0400
Received: from mail-pj1-x1049.google.com (mail-pj1-x1049.google.com
 [IPv6:2607:f8b0:4864:20::1049])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 1F5D0C06174A
        for <kvm@vger.kernel.org>; Wed,  5 Aug 2020 14:16:17 -0700 (PDT)
Received: by mail-pj1-x1049.google.com with SMTP id hi12so5491721pjb.6
        for <kvm@vger.kernel.org>; Wed, 05 Aug 2020 14:16:17 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=la1fBNohyp9Rq0q7N/prOaEAn3Pa3Ne3Ld2u4313kWw=;
        b=bXpi2JLztAZeYO0FKrcoi/neZ2SaOju3+iUfx3+Z4jiX7mN4K6Sq7bqKw4jreYFbyJ
         GrHQszRjcrAL6sEDiyRoBr28+wvCWUMTQNYtnMJDRc/txE2wdF3WWaOwOl2k5E/fjkGi
         TLFmiwLiKWFV8In+Delusu8dHNPPmkThIn++0gAHKzco93VyIagcaeOD3YW4/IdxiAV3
         T6PBS/BgmhjUcAq3JNEdXGpMzuFTAkff7p377MvNxbnLrYqbfIb3eTRJ8s54ptjYt5qm
         aXCnJBvX0IHcRHNXAk8Jbzf+5VA44ftqstXlpiSGKVjoUzRLolqWufbwzng7huCW/6Ul
         ZDqw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=la1fBNohyp9Rq0q7N/prOaEAn3Pa3Ne3Ld2u4313kWw=;
        b=AEnsMbdTIwUjbPTwk+dYb25HC1ztCSvcJ1Jhg9Fk9Epeo0fJeCBgaf/p+pCtzmPdxH
         bIOJxdEMyivtUcTDoP3OUjMr6laFjQljhjZ4BI1tP5/bNENSeb+4IMYP0rU61rEdPvlN
         hWzOrm1oLRdcZngjk1KqyZ3R6zp4Gc8O2QBWMTD/VChQ5PdkKz/NhrvDtmJ4aKJjoTfv
         suqCRfZAgKsTILqbLRun8WW5JcrxwfQ0Nnn6WYM1GKnLuAQRzmLdZ+vLWe7I+qeOu50O
         Bu7CHMR2WIvGx35Fh69KhPu0oaveoTjitx2NnNwnZkLqGvQw6HVdKI1h17w/pbE9BCbz
         7gQA==
X-Gm-Message-State: AOAM530k6ZprHKfjvrcfEj8NPgISVsV9tLXD2jiBbwOMzlCOyfjs0Gz2
        PKXrJf1/5x0ZP+LuekThzolWlT33MuN/g4fAnFEjUAp4Q2LnQ0hkuXwIQuf7KYuLiygmchSvgpe
        TGIewRBJY16cFpJRRNTZf7SoMKS2VvlAPGzylN2vz5dGYNz6Bn37I6trr4g==
X-Google-Smtp-Source: 
 ABdhPJxm0hDF3GRIJjqfboYKhyLEgT0INlvVWxOxioqjRDAr3Dfw1NulJLURWwjZZVzBfWpTTN+xs8E6aMw=
X-Received: by 2002:a17:902:8e86:: with SMTP id
 bg6mr5029643plb.57.1596662176080;
 Wed, 05 Aug 2020 14:16:16 -0700 (PDT)
Date: Wed,  5 Aug 2020 21:16:04 +0000
In-Reply-To: <20200805211607.2048862-1-oupton@google.com>
Message-Id: <20200805211607.2048862-2-oupton@google.com>
Mime-Version: 1.0
References: <20200805211607.2048862-1-oupton@google.com>
X-Mailer: git-send-email 2.28.0.236.gb10cc79966-goog
Subject: [PATCH 1/4] kvm: x86: encapsulate wrmsr(MSR_KVM_SYSTEM_TIME)
 emulation in helper fn
From: Oliver Upton <oupton@google.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Oliver Upton <oupton@google.com>,
        Jim Mattson <jmattson@google.com>,
        Peter Shier <pshier@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

No functional change intended.

Reviewed-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
Signed-off-by: Oliver Upton <oupton@google.com>
Change-Id: I7cbe71069db98d1ded612fd2ef088b70e7618426
---
 arch/x86/kvm/x86.c | 58 +++++++++++++++++++++++++---------------------
 1 file changed, 32 insertions(+), 26 deletions(-)

```
#### [PATCH v2 1/4] kvm: x86: encapsulate wrmsr(MSR_KVM_SYSTEM_TIME) emulation in helper fn
##### From: Oliver Upton <oupton@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Oliver Upton <oupton@google.com>
X-Patchwork-Id: 11702553
Return-Path: <SRS0=UpKl=BP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B3825722
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  5 Aug 2020 21:21:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9E87222CAE
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  5 Aug 2020 21:21:47 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="t7pTWPde"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726398AbgHEVVo (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 5 Aug 2020 17:21:44 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:33252 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726233AbgHEVVl (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 5 Aug 2020 17:21:41 -0400
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 625A5C06174A
        for <kvm@vger.kernel.org>; Wed,  5 Aug 2020 14:21:41 -0700 (PDT)
Received: by mail-yb1-xb4a.google.com with SMTP id g127so14732532ybf.11
        for <kvm@vger.kernel.org>; Wed, 05 Aug 2020 14:21:41 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=yQtZaZXi+U75DJ3qF2YeU3Fjk111QGLsB9W7wdn91GA=;
        b=t7pTWPdebF0bfhcL89P7swWBkn+mBQvQA9TOHfmNvcDmFWUnYpC6tIt10M8b5uwqzy
         VJqimRCIC0QT6snmk+1D+rG2NF8O+mDPwPnxAGHRd3Uk0gQQR7RBrEWz6F7epHFX0mGP
         4tc4nd8gI/DupSg4aUgnILA7ctu2PIkIBAlyKqqX15M/hXPBXt4uuZKvROEMgxN9eN6q
         q/fUTwpara+3uNn/rEG9ER8lxqmnbD0Hfd2tY1fDZZbEJLuhzbl8u7ae9ZuTs3XTpTrR
         n5iWnS1g1XdGqvZgd/bmzDwRdGA6C473nYAVU05FAKDC4CCRTto2vgDq0gc8Se5KyQAG
         Myzw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=yQtZaZXi+U75DJ3qF2YeU3Fjk111QGLsB9W7wdn91GA=;
        b=NSY2lv94G6N2w7KCFWusgBuoy5kAsSq9pEYQc+g/9htJeUss1+uIbrP5M7AjQ5Feer
         yiylGzurFoivW1kxcgJYg9nrNR8DWEm17GHuMqA85cftc2T3xLjAEtDxe0gIUd9vanmG
         v9w8FzHOSDVGTvR5ibBx+HC4iTWBk9Eejfws2SzNCTcTqG04hc5kOxykhTyQIUch1q0+
         YV3u1Un/8BHGSTBup/b5nwiOaJEv5IEU2KNXUlUXwM15qKX/6YVtiBAkKk5juU4Z2Abn
         3bbSwWEiHH/K2eQMO5g+hS2P6I+KAnhGTkgNM9RamArK0VnoaWHYZMDqKmLcFK3slvHM
         tIbg==
X-Gm-Message-State: AOAM531mJnGZ7zv3/1wXnsVuRTAUTiSJRVh5x04Zm3nyPbzXgcbBo2CL
        gKZZZkwEJjCIbh3gpxTXcqrNF6R+XEZuLLyABbQeU1QvL0RfMszr5GsOY6HAIE/2jROiOI6kqMo
        s8AKCvoyhTEqEbsKEqaZjk+OWwQRe+TN8WJDF0J0dAD9oCxWl0j26JmtNeQ==
X-Google-Smtp-Source: 
 ABdhPJydJVXkSb37TwBwuFz9m1W1D23r2m9X9q/aeb6i5EVrtSorhWO2TZeCqIB4Q1uR7goI/xGF9B5gk8E=
X-Received: by 2002:a25:a88:: with SMTP id 130mr7575300ybk.52.1596662499619;
 Wed, 05 Aug 2020 14:21:39 -0700 (PDT)
Date: Wed,  5 Aug 2020 21:21:28 +0000
In-Reply-To: <20200805212131.2059634-1-oupton@google.com>
Message-Id: <20200805212131.2059634-2-oupton@google.com>
Mime-Version: 1.0
References: <20200805212131.2059634-1-oupton@google.com>
X-Mailer: git-send-email 2.28.0.236.gb10cc79966-goog
Subject: [PATCH v2 1/4] kvm: x86: encapsulate wrmsr(MSR_KVM_SYSTEM_TIME)
 emulation in helper fn
From: Oliver Upton <oupton@google.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Oliver Upton <oupton@google.com>,
        Jim Mattson <jmattson@google.com>,
        Peter Shier <pshier@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

No functional change intended.

Reviewed-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
Signed-off-by: Oliver Upton <oupton@google.com>
---
 arch/x86/kvm/x86.c | 58 +++++++++++++++++++++++++---------------------
 1 file changed, 32 insertions(+), 26 deletions(-)

```
#### [RFC 1/9] Introduce new fields in kvm_arch/vcpu_arch struct for direct build EPT support
##### From: Yulei Zhang <yulei.kernel@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yulei Zhang <yulei.kernel@gmail.com>
X-Patchwork-Id: 11701945
Return-Path: <SRS0=UpKl=BP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 60C856C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  5 Aug 2020 16:51:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4AA3322D00
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  5 Aug 2020 16:51:59 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="XmnFwMtn"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727030AbgHEQv4 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 5 Aug 2020 12:51:56 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:46436 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728147AbgHEQts (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 5 Aug 2020 12:49:48 -0400
Received: from mail-pl1-x644.google.com (mail-pl1-x644.google.com
 [IPv6:2607:f8b0:4864:20::644])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 7AA24C0A8939;
        Wed,  5 Aug 2020 07:11:41 -0700 (PDT)
Received: by mail-pl1-x644.google.com with SMTP id u10so15826629plr.7;
        Wed, 05 Aug 2020 07:11:41 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=t3CWCXEfy1YBGVg4SnMNF6schJfAMQg5KljYK4gfTsI=;
        b=XmnFwMtnjN75K16BQFkOpsa1h5Gm1rBb8O9whIuMSekmr/T3t27uE23AcKyg9byPcU
         dzzBGhvcFRByy1Q8+sYNxodBAWBAwD2Lp4i1aP5x+b0f/TzAD5ltXbyjS57qa5sBvhK4
         itlSPXslxBef0m0GB0yT2v85/iRjCac0hSY5FhBYy8l7+uKOMhY8+F02G+WVyx/EnprU
         Ofmp8Gkc9GZhKDjLBpV3XjErYVXpzmBVXDjmieAcvLAc888ZExmqFetlaWtf5udKQXEE
         6YFMyesazSwkr9VZwLwemb4GPyWF2WVJEabky+DzNfv257CQNCk5SbffNCoCMDGh2/Eu
         /vNQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=t3CWCXEfy1YBGVg4SnMNF6schJfAMQg5KljYK4gfTsI=;
        b=LaflvK6Rx23mNdWE9DwZoDwBvcQT8I2/nlrcfZHGyGtAvG+g90BgsKu9EXrzyc4hvO
         4p9ROI8ARhEfX2+FyL4RhTJmyI6rLGa1bzf87R5rjo+OXsmFukIja8jbqpyYwQzrQ8Po
         nxgekHzvbyFXNh8SRaG4Qk05ZsCQqJuY53bN7QtGl0V09/AUTPLdZC+KTGW1OCUazruk
         I8eVWNjl5tiO3BcilQFZObs6hiIouPxXdlrjEQZjqL9ZhbYZgxf1Ky9s+MJEhxH4EcrY
         u4ZKIcEu+f9vfltV8v7jzQvtl4nj2QNEvlPCGKJEl7ltXShqaMP1JtIHvn2NHLRa+GJE
         nfrg==
X-Gm-Message-State: AOAM530v9lfwtxw/cMPibba/zpTiCQLb4JcGg6txqhJXKXaNABpIVe7/
        j+HpASxH8Cjemk/s+jrYkcs=
X-Google-Smtp-Source: 
 ABdhPJyOFWD5B/gYZFHtHdIRmVl+RANMmDV8CWKM/a/07nb6tdMmsyGysW9wL9INF3jqqvCSc1Qwug==
X-Received: by 2002:a17:90b:1106:: with SMTP id
 gi6mr3689116pjb.2.1596636700874;
        Wed, 05 Aug 2020 07:11:40 -0700 (PDT)
Received: from localhost.localdomain ([203.205.141.62])
        by smtp.gmail.com with ESMTPSA id
 o192sm4300017pfg.81.2020.08.05.07.11.38
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 05 Aug 2020 07:11:40 -0700 (PDT)
From: Yulei Zhang <yulei.kernel@gmail.com>
To: pbonzini@redhat.com
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        sean.j.christopherson@intel.com, jmattson@google.com,
        vkuznets@redhat.com, xiaoguangrong.eric@gmail.com,
        kernellwp@gmail.com, lihaiwei.kernel@gmail.com,
        Yulei Zhang <yuleixzhang@tencent.com>
Subject: [RFC 1/9] Introduce new fields in kvm_arch/vcpu_arch struct for
 direct build EPT support
Date: Wed,  5 Aug 2020 22:12:32 +0800
Message-Id: <20200805141232.8742-1-yulei.kernel@gmail.com>
X-Mailer: git-send-email 2.17.1
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
#### [PATCH] vfio-pci: Avoid recursive read-lock usageFrom: Alex Williamson <alex.williamson@redhat.com>
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alex Williamson <alex.williamson@redhat.com>
X-Patchwork-Id: 11702077
Return-Path: <SRS0=UpKl=BP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EA1501575
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  5 Aug 2020 18:04:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D4DA822CAE
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  5 Aug 2020 18:04:14 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="NeztqPI2"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728533AbgHESEG (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 5 Aug 2020 14:04:06 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:52887 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1728488AbgHER6U (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 5 Aug 2020 13:58:20 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1596650298;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=2x3mgNdTSCpVK/PvsDtS076Na69D7EpUGAvTaGV+Rek=;
        b=NeztqPI2uItGb/UxDEd+G6pKaCRCvntgYgwWHswtfJyH8R9Yw6RHDt4zBWh3iLGD2Lo3ZV
        4+GxcgXISsi0AKhaqv2GaJsjvpjNsMZQ4dwno2rwQ/eMwitQVSFI4pO8BJQQSksYZSHi6z
        eb0j0JydXf3Jqy+wa/QvULg3jLDrpfU=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-478-EZlvipCxNui6X3CIYHErHA-1; Wed, 05 Aug 2020 13:58:16 -0400
X-MC-Unique: EZlvipCxNui6X3CIYHErHA-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 2A74F81EDB7;
        Wed,  5 Aug 2020 17:58:06 +0000 (UTC)
Received: from gimli.home (ovpn-112-71.phx2.redhat.com [10.3.112.71])
        by smtp.corp.redhat.com (Postfix) with ESMTP id CC8441755E;
        Wed,  5 Aug 2020 17:58:05 +0000 (UTC)
Subject: [PATCH] vfio-pci: Avoid recursive read-lock usage
From: Alex Williamson <alex.williamson@redhat.com>
To: alex.williamson@redhat.com
Cc: cohuck@redhat.com, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Date: Wed, 05 Aug 2020 11:58:05 -0600
Message-ID: <159665024415.30380.4401928486051321567.stgit@gimli.home>
User-Agent: StGit/0.19-dirty
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

A down_read on memory_lock is held when performing read/write accesses
to MMIO BAR space, including across the copy_to/from_user() callouts
which may fault.  If the user buffer for these copies resides in an
mmap of device MMIO space, the mmap fault handler will acquire a
recursive read-lock on memory_lock.  Avoid this by reducing the lock
granularity.  Sequential accesses requiring multiple ioread/iowrite
cycles are expected to be rare, therefore typical accesses should not
see additional overhead.

VGA MMIO accesses are expected to be non-fatal regardless of the PCI
memory enable bit to allow legacy probing, this behavior remains with
a comment added.  ioeventfds are now included in memory access testing,
with writes dropped while memory space is disabled.

Fixes: abafbc551fdd ("vfio-pci: Invalidate mmaps and block MMIO access on disabled memory")
Signed-off-by: Alex Williamson <alex.williamson@redhat.com>
---
 drivers/vfio/pci/vfio_pci_private.h |    2 +
 drivers/vfio/pci/vfio_pci_rdwr.c    |  120 ++++++++++++++++++++++++++++-------
 2 files changed, 98 insertions(+), 24 deletions(-)

```
#### [RFC 3/9] Introduce page table remove function for direct build EPT feature
##### From: Yulei Zhang <yulei.kernel@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yulei Zhang <yulei.kernel@gmail.com>
X-Patchwork-Id: 11702443
Return-Path: <SRS0=UpKl=BP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D3E4514B7
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  5 Aug 2020 19:51:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B76702076E
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  5 Aug 2020 19:51:30 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="GxS+vZ2k"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728219AbgHETv1 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 5 Aug 2020 15:51:27 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:47042 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728212AbgHEQwU (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 5 Aug 2020 12:52:20 -0400
Received: from mail-pl1-x644.google.com (mail-pl1-x644.google.com
 [IPv6:2607:f8b0:4864:20::644])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 58109C0A893B;
        Wed,  5 Aug 2020 07:12:31 -0700 (PDT)
Received: by mail-pl1-x644.google.com with SMTP id r4so14687781pls.2;
        Wed, 05 Aug 2020 07:12:31 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=ubR+1U/66cwEoUeTJMc9atQb7+ROgmCea2NvMPQs8PQ=;
        b=GxS+vZ2kVfbNjb07AZMVexUY0voxfkHVoEXsmMZImY7zdHxjqEqIk93rbwZ1Y2upMe
         iacdMzNeIUNZxaskLbQugw+oEvKagukI3WviguHLiY+BPthHNnn51BVYQtJV5+lnsmpb
         qUfHuAti9HoDFFnGk1nOlUKdSbj7KlQDPPnRh+JzvyRUgkfh5nlpXho1ilUoNrmVj87d
         X/jK5c6fFchj/PKd990jxwDPZed3+iBMy6cxPzms6XR3Jwd/NBknzE6y0Fici3z72d7a
         YYksm3vRqLGxcdeIxog9DquthiKVRs0BpfaaQh0quVFLMjqyLu4+79mfW/dtkvC/h1ny
         SGqg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=ubR+1U/66cwEoUeTJMc9atQb7+ROgmCea2NvMPQs8PQ=;
        b=hOGQ9tpfKXXOmTxIgAa9JqGe4/hM9+uXW0hOeUzeVicZdIkAMiiv0H79FqCRaUF/5P
         qkHadqLrR6RVSSlZ6QUk79c/dCJ9kDomvs0l5lZl2wTQjiGrixoEtX371VAD9ztt8gxx
         EvK72aix1ufSFNAhzl11LErgbfCKdBaqEMrZpaD6BWfoOnQV+C1pw4OWfHtP5flI8nJm
         1xqVFsK4x8mNucQY2OwDvmYEDnx+Dq+Rh3GaJbidLOh6DF0MaZ0CEMv/uOFg/jMXb7yp
         WcRY0f6nzTlvHBnaF7HvpJjUAGUavV1+sIop7O7l4zLKbfHBmH1n4KP5MUe69N29sbmM
         hPVA==
X-Gm-Message-State: AOAM530CFNlgYWN+LuQpBwX9D/YWvEkZEfNRgrsHB2GOIa+0n8O9czCj
        6RpjxEAeEIcoF0AZiRh+28I=
X-Google-Smtp-Source: 
 ABdhPJwvn3rF3guqUVD0j8h0EFW39vmETXxaXwHQFfjOtTy0pj72nVixtwJD0JIxQcE/AVhbQg8p1A==
X-Received: by 2002:a17:90a:b88b:: with SMTP id
 o11mr3527448pjr.58.1596636750850;
        Wed, 05 Aug 2020 07:12:30 -0700 (PDT)
Received: from localhost.localdomain ([203.205.141.62])
        by smtp.gmail.com with ESMTPSA id
 l17sm4156287pff.126.2020.08.05.07.12.28
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 05 Aug 2020 07:12:30 -0700 (PDT)
From: Yulei Zhang <yulei.kernel@gmail.com>
To: pbonzini@redhat.com
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        sean.j.christopherson@intel.com, jmattson@google.com,
        vkuznets@redhat.com, xiaoguangrong.eric@gmail.com,
        kernellwp@gmail.com, lihaiwei.kernel@gmail.com,
        Yulei Zhang <yuleixzhang@tencent.com>
Subject: [RFC 3/9] Introduce page table remove function for direct build EPT
 feature
Date: Wed,  5 Aug 2020 22:13:20 +0800
Message-Id: <20200805141320.8941-1-yulei.kernel@gmail.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Yulei Zhang <yuleixzhang@tencent.com>

During guest boots up it will modify the memory slots multiple times,
so add page table remove function to free pre-pinned memory according
to the the memory slot changes.

Signed-off-by: Yulei Zhang <yuleixzhang@tencent.com>
---
 arch/x86/kvm/mmu/mmu.c | 56 ++++++++++++++++++++++++++++++++++++++++++
 1 file changed, 56 insertions(+)

```
#### [RFC 2/9] Introduce page table population function for direct build EPT feature
##### From: Yulei Zhang <yulei.kernel@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yulei Zhang <yulei.kernel@gmail.com>
X-Patchwork-Id: 11702451
Return-Path: <SRS0=UpKl=BP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B199514B7
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  5 Aug 2020 19:53:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 928232076E
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  5 Aug 2020 19:53:46 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="Z9nUHyMa"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728715AbgHETxW (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 5 Aug 2020 15:53:22 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:47042 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727074AbgHEQuU (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 5 Aug 2020 12:50:20 -0400
Received: from mail-pl1-x643.google.com (mail-pl1-x643.google.com
 [IPv6:2607:f8b0:4864:20::643])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 73E84C0A893A;
        Wed,  5 Aug 2020 07:12:07 -0700 (PDT)
Received: by mail-pl1-x643.google.com with SMTP id w17so25307259ply.11;
        Wed, 05 Aug 2020 07:12:07 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=NFXipDhiZCZ3xOixjvwfPnvuyeXFxxM0MuhTheiJ4p4=;
        b=Z9nUHyMa2vU7KbGKoMXl90fqXcIhc7h6kQLrfAxucoZcHqMP5hb851GEV7+ey9jwem
         75qNus2hqMjctrwcllMNXHg6U0DoMq/KxOnto4S9gG8BIBLpdNRF6zI1LkOvT+9eKQIQ
         ER6JKEx1Nx+aL6MfNj2ge+6VQNARlDatqkwTx1a8PIsQ+A5pJ/IcqWT6gvo78+f/jD0c
         f7wVvvDHJQwbscEUYegxXjSsXent5tHvADUnFfUIITymuXsPJcKp8BhvwVy4UltoEYgJ
         DmMibDrewrWNu0LPbd9Pjlb40F5A11HD1BGVp1bwBWUpg6DpetNSb9C2qTrDKPEf/E4d
         xDig==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=NFXipDhiZCZ3xOixjvwfPnvuyeXFxxM0MuhTheiJ4p4=;
        b=H7NnHyWMOEAMvxzgYIt2W8yx99rfHfRQvTrg6sndE4EYyYXCp0wdMDUQzcSeaOCiTJ
         MsHYJR+ppkVef96w6LSZQa6a+CFb7A45DmFuYspv2Tw1Wo74hazpWjZwVpL3CjnCQVJT
         ULlvgqYrzyd7CZjy8q6/RkNVJ2i1nIErlo9fBezfwvRcauc6+k5XPQy1HW6lq7XHLi3W
         EC5IvlCDsPBvqvAT5gZiJnVQ1YW6ix1qWM+L0oFAktk/LpD5JNfwXCUXM02VTiwOkAZy
         e+5O34gfaE64eM29xtbaznW2qfCQE9IWdUjNZLvlwDTy443/adbXkoxp6A3AkmFFI32q
         fqhw==
X-Gm-Message-State: AOAM533ailxoDF8Hx0JYqttLyFdhQssd8E7//dCgHAS1jARYjMvkE6Z8
        A7Kq5Rwjpi+GcifCvkLm3mM=
X-Google-Smtp-Source: 
 ABdhPJzGSjXBd0ga8725gfRLIG9DImnG2E4CBV+/W7JuBz+av6wlo44mKw7nFMoR7TSmux5RUd6Xew==
X-Received: by 2002:a17:902:7d8b:: with SMTP id
 a11mr3049149plm.342.1596636726942;
        Wed, 05 Aug 2020 07:12:06 -0700 (PDT)
Received: from localhost.localdomain ([203.205.141.62])
        by smtp.gmail.com with ESMTPSA id
 q18sm3632943pfn.106.2020.08.05.07.12.04
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 05 Aug 2020 07:12:06 -0700 (PDT)
From: Yulei Zhang <yulei.kernel@gmail.com>
To: pbonzini@redhat.com
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        sean.j.christopherson@intel.com, jmattson@google.com,
        vkuznets@redhat.com, xiaoguangrong.eric@gmail.com,
        kernellwp@gmail.com, lihaiwei.kernel@gmail.com,
        Yulei Zhang <yuleixzhang@tencent.com>
Subject: [RFC 2/9] Introduce page table population function for direct build
 EPT feature
Date: Wed,  5 Aug 2020 22:12:57 +0800
Message-Id: <20200805141257.8841-1-yulei.kernel@gmail.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Yulei Zhang <yuleixzhang@tencent.com>

Page table population function will pin the memory and pre-construct
the EPT base on the input memory slot configuration so that it won't
relay on the page fault interrupt to setup the page table.

Signed-off-by: Yulei Zhang <yuleixzhang@tencent.com>
---
 arch/x86/include/asm/kvm_host.h |   2 +-
 arch/x86/kvm/mmu/mmu.c          | 212 +++++++++++++++++++++++++++++++-
 arch/x86/kvm/svm/svm.c          |   2 +-
 arch/x86/kvm/vmx/vmx.c          |  17 ++-
 include/linux/kvm_host.h        |   4 +-
 virt/kvm/kvm_main.c             |  30 ++++-
 6 files changed, 250 insertions(+), 17 deletions(-)

```
#### [RFC 9/9] Handle certain mmu exposed functions properly while turn on direct build EPT mode
##### From: Yulei Zhang <yulei.kernel@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yulei Zhang <yulei.kernel@gmail.com>
X-Patchwork-Id: 11702457
Return-Path: <SRS0=UpKl=BP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5D842722
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  5 Aug 2020 19:54:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 47E4A22B42
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  5 Aug 2020 19:54:58 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="ZkRT9n6q"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729612AbgHETy4 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 5 Aug 2020 15:54:56 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:46308 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728071AbgHEQsi (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 5 Aug 2020 12:48:38 -0400
Received: from mail-pl1-x641.google.com (mail-pl1-x641.google.com
 [IPv6:2607:f8b0:4864:20::641])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 3D017C0086D0;
        Wed,  5 Aug 2020 07:15:28 -0700 (PDT)
Received: by mail-pl1-x641.google.com with SMTP id z20so4577113plo.6;
        Wed, 05 Aug 2020 07:15:28 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=rEOIric6Ir5n+lOqeIUvVaHq8kkbGDlIxFcFnaIeFVQ=;
        b=ZkRT9n6qi1MmrCkM+E537KhVRT1l3vdm2/Ro4pCdDJRA6UkpwxDmS8ZAyxOdST5s62
         WBF4QZ/RCetbs01gGxXt1a02B2K+L5tE6l8UkHXoItIluhgeuw3INFKrnuvDNdTdCWHN
         s/QyMREKiE87UIIBQXZuCKez7UJ63uDhXPgUH6Xwz9mcxZMDtjvVxt4eceSv4x8PTyGA
         B5ZGKsXdPM4wZ1E+xnGW/xdPlkv0xTcfJuKeReyDLfljFHOZfQKYI59kg0aamYAy54b2
         nSbl8F62rRI6F1BGgexyInUdVE8u38O7AcmnjAEZs2NO7ET5GcxsI65CDT86tzgobmGs
         pryA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=rEOIric6Ir5n+lOqeIUvVaHq8kkbGDlIxFcFnaIeFVQ=;
        b=V3TOuKnc2p7tK3ANQdyyk48gTmy385C1LGWO/BUZP6oSTjwtl3LgibourgFR0BWzbV
         CJnY+EiURtpNzPg92sVW54dGjGdTCv6OEuuZyxVu1vlm34kc+4iKhw5xxfGZcreA39jF
         qkbkxxTfk4X0PzWIbitNWFALtV/X5dQdwyiw13lnZlwZyXTzvkdYY+lFp0pzNEcGdxUl
         bFr3oJY8hAUfeEq66QFDChKURhcx631X3X+dgLMLgO95zEWhL3wP+VvbjClZIAhC1Eh6
         SRgppINgoCkUgGIPVSVwnQtJNnq2rK25O4DXc+5VDrc92g52Q+aNkAR/gPegYES8FFei
         KrhQ==
X-Gm-Message-State: AOAM533x1XHlloGm3cEUHDCjCKDixSt+69+cTE9wNDmMXJ5a5dov0Mm0
        fAudTHotGtiJ9ASQ0vie42Q=
X-Google-Smtp-Source: 
 ABdhPJxoCHeKbtH4i8Re0QtrWCP7cYen3eIDSZ4CjAepg/EGPcmYe2gP1t4htLViL7C20uPS82QTlA==
X-Received: by 2002:a17:902:b489:: with SMTP id
 y9mr3065180plr.99.1596636927791;
        Wed, 05 Aug 2020 07:15:27 -0700 (PDT)
Received: from localhost.localdomain ([203.205.141.62])
        by smtp.gmail.com with ESMTPSA id
 q82sm4253725pfc.139.2020.08.05.07.15.25
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 05 Aug 2020 07:15:27 -0700 (PDT)
From: Yulei Zhang <yulei.kernel@gmail.com>
To: pbonzini@redhat.com
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        sean.j.christopherson@intel.com, jmattson@google.com,
        vkuznets@redhat.com, xiaoguangrong.eric@gmail.com,
        kernellwp@gmail.com, lihaiwei.kernel@gmail.com,
        Yulei Zhang <yuleixzhang@tencent.com>
Subject: [RFC 9/9] Handle certain mmu exposed functions properly while turn on
 direct build EPT mode
Date: Wed,  5 Aug 2020 22:16:19 +0800
Message-Id: <20200805141619.9529-1-yulei.kernel@gmail.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Yulei Zhang <yuleixzhang@tencent.com>

Signed-off-by: Yulei Zhang <yuleixzhang@tencent.com>
---
 arch/x86/kvm/mmu/mmu.c | 9 +++++++++
 1 file changed, 9 insertions(+)

```
#### [RFC 7/9] Add migration support when using direct build EPT
##### From: Yulei Zhang <yulei.kernel@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yulei Zhang <yulei.kernel@gmail.com>
X-Patchwork-Id: 11702467
Return-Path: <SRS0=UpKl=BP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 858B0722
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  5 Aug 2020 19:56:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 630E120842
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  5 Aug 2020 19:56:56 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="rOUemIin"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729482AbgHET4f (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 5 Aug 2020 15:56:35 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:45432 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728000AbgHEQoM (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 5 Aug 2020 12:44:12 -0400
Received: from mail-pl1-x642.google.com (mail-pl1-x642.google.com
 [IPv6:2607:f8b0:4864:20::642])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id CEA13C0086CD;
        Wed,  5 Aug 2020 07:14:44 -0700 (PDT)
Received: by mail-pl1-x642.google.com with SMTP id t11so5486145plr.5;
        Wed, 05 Aug 2020 07:14:44 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=91YW5ED4v1tRh3CUsEOp6Qs783LYngGUb2jh2KPIkMg=;
        b=rOUemIincMfQVNZ5zPioG6CdDihWgeNjJaP9GBooWAR/0Bc4A4OjuPx+GU54slJWeb
         SN4YPSSc+eQ4BIYFJLmM0+X11Ks0i5s4AVdu0HoxkqiGevWO/omd2oSOnwZ4EcB134TJ
         uhT2cLL5X3RMkiOVyIQJvusFe9Skf0DUK4SBBByKYG4fWyD4YHYmVvgQjVZj2rTfn8X8
         r33p2/O0fVEQnaWJgsE1ixjVUgLCTpLkFF1kf00LQgqkA2Obua3GVlQL7AstS0rhH5yW
         nHkqjbWg7txC49XbeCVvIM96+Vi3uJ82c1a3BCYFUkR73UqfUS1pD8nmVryWZ5SaD5fQ
         pkqg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=91YW5ED4v1tRh3CUsEOp6Qs783LYngGUb2jh2KPIkMg=;
        b=JYgt06uDmixahDPJUa6TcCxoG56MQQ5h8mDVRUhTWNeKBIX+8WU8uT0K8MWfd7bzvr
         CARBEbM+dOCyQKAdl68TEi6Ey+ItweY8Ig+CmqtXtX6CZ/ODNHCHglMI0K4eGhaU9dv4
         RhzFCHmKi4TLG8euZeflM5KQexxdRUB/Aef+JDg6sWDZ+9WlRzleFpaoTRYjHlWPk7bI
         bBZN8eQf5/1zzE+qdnJ4D5LhrS3uw8KzO2mEyl6i/vaVgrfTyzj7/0drVMEoKAsitrJn
         ixPTjIZ+tJW/WEjX0zrduCkowEptufcGbKj08Ke2nXd/kVAJBLbfbhWa49fmfIbEsdJe
         yXgA==
X-Gm-Message-State: AOAM531eBc7aGH1c3lyRQqx5mBC99TGEDiYMxNVRvd5YRTub10C7Ww3B
        gQqTrzAS7/2K5Z9Qeg/EUbo=
X-Google-Smtp-Source: 
 ABdhPJzspVzoegO673mvpxSae5jtY4cxqu7QXwuzl7RFhlB3MWenVnN4v0CzmBncHaa9Sb6SluIhPw==
X-Received: by 2002:a17:90a:a511:: with SMTP id
 a17mr3602420pjq.23.1596636884279;
        Wed, 05 Aug 2020 07:14:44 -0700 (PDT)
Received: from localhost.localdomain ([203.205.141.56])
        by smtp.gmail.com with ESMTPSA id
 y196sm3862420pfc.202.2020.08.05.07.14.41
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 05 Aug 2020 07:14:43 -0700 (PDT)
From: Yulei Zhang <yulei.kernel@gmail.com>
To: pbonzini@redhat.com
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        sean.j.christopherson@intel.com, jmattson@google.com,
        vkuznets@redhat.com, xiaoguangrong.eric@gmail.com,
        kernellwp@gmail.com, lihaiwei.kernel@gmail.com,
        Yulei Zhang <yuleixzhang@tencent.com>
Subject: [RFC 7/9] Add migration support when using direct build EPT
Date: Wed,  5 Aug 2020 22:15:33 +0800
Message-Id: <20200805141533.9333-1-yulei.kernel@gmail.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Yulei Zhang <yuleixzhang@tencent.com>

Make migration available in direct build ept mode whether
pml enabled or not.

Signed-off-by: Yulei Zhang <yuleixzhang@tencent.com>
---
 arch/x86/include/asm/kvm_host.h |   2 +
 arch/x86/kvm/mmu/mmu.c          | 153 +++++++++++++++++++++++++++++++-
 arch/x86/kvm/x86.c              |  44 +++++----
 3 files changed, 178 insertions(+), 21 deletions(-)

```
#### [RFC 4/9] Add release function for direct build ept when guest VM exit
##### From: Yulei Zhang <yulei.kernel@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yulei Zhang <yulei.kernel@gmail.com>
X-Patchwork-Id: 11702471
Return-Path: <SRS0=UpKl=BP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2360514B7
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  5 Aug 2020 19:57:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0E84620842
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  5 Aug 2020 19:57:27 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="XroRQzFh"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728680AbgHET5X (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 5 Aug 2020 15:57:23 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:45428 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727977AbgHEQny (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 5 Aug 2020 12:43:54 -0400
Received: from mail-pf1-x441.google.com (mail-pf1-x441.google.com
 [IPv6:2607:f8b0:4864:20::441])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 0D210C0A893C;
        Wed,  5 Aug 2020 07:12:56 -0700 (PDT)
Received: by mail-pf1-x441.google.com with SMTP id u185so22789067pfu.1;
        Wed, 05 Aug 2020 07:12:56 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=Z1dq08rcyRAJKP6YZL/SMfPNJkj3TPNkHN01IYY4yWs=;
        b=XroRQzFhX23GOwnvJ+TMAohKF4jLXddbL2pj4Vw71Fv6+fTlsOQL75TwEX/IfhoZXu
         MbkZ02tnwmXDdaJDdqD4378pi9AHy0egPbJGYx/AQ/Qb8zdVOVi5tJAfYkNmTmqyS3k8
         6pmcLeJx6DSR8ghJB/OopLM6Z5YioxqNN1KVrsvbvD69FeKQ7yMg1V4ifrnk4rhuG5I5
         ATi3LOotF/G5kthGiBTZOa+vWCsr97uArQGw/gBUCBzvp18H5F9IWL9fTy6LrnfGFG7u
         LxwozEMlqFzTIzquuHwh3hHdW+HKviD7rvsng85PoalKziVwuQ9ZIXskHGS1Xj5/LQYz
         /0Pg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=Z1dq08rcyRAJKP6YZL/SMfPNJkj3TPNkHN01IYY4yWs=;
        b=sBQ6KALId60/sBtnDB+n9oMqT+Cka/o3NGrCBxhNyKBV4DZre85LgMeyTASQXBxrEB
         o58TGZ2/2M1PwcaPqW0K468SB8yI+T11zdg2eJ1gcR0/1YvnKruk+pXZXB3AdR9L1rBy
         GnPw6RT3t1DT+TfrvhXazQRpU0W9YDi4pQ6QhkUnargnYiRZ2/WO8a900gM7ixjt/Q8O
         bak957wByQLI23MWUKTwHE33Ff9zEpreynf6vwDcsx3xqmSj7pHM66GZOA4G0ozDJTnx
         Yt7nRygquMci4cyTMO5vai5VVU/qTC3jLMYGMpvQ/479KUhqRYbsEDQriAmCgssG9Uiy
         XxLw==
X-Gm-Message-State: AOAM533oHVRqiytEHj6DzgYMar1wXQ9NDOR+DZHDs+f1P7yveATNE0Wp
        g/XchM9OvZ7EczcCIMg2PNg=
X-Google-Smtp-Source: 
 ABdhPJz1faKwYcoCClSYPrpjo3JT+/DAOCDHY/ELu1FrfqxIH1TxDBCpCnDmYm3YXUnuHrmTGX2ONw==
X-Received: by 2002:a65:5502:: with SMTP id f2mr3017228pgr.375.1596636775668;
        Wed, 05 Aug 2020 07:12:55 -0700 (PDT)
Received: from localhost.localdomain ([203.205.141.56])
        by smtp.gmail.com with ESMTPSA id
 b185sm3726551pfg.71.2020.08.05.07.12.53
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 05 Aug 2020 07:12:55 -0700 (PDT)
From: Yulei Zhang <yulei.kernel@gmail.com>
To: pbonzini@redhat.com
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        sean.j.christopherson@intel.com, jmattson@google.com,
        vkuznets@redhat.com, xiaoguangrong.eric@gmail.com,
        kernellwp@gmail.com, lihaiwei.kernel@gmail.com,
        Yulei Zhang <yuleixzhang@tencent.com>
Subject: [RFC 4/9] Add release function for direct build ept when guest VM
 exit
Date: Wed,  5 Aug 2020 22:13:43 +0800
Message-Id: <20200805141344.9038-1-yulei.kernel@gmail.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Yulei Zhang <yuleixzhang@tencent.com>

Release the pre-pinned memory in direct build ept when guest VM
exit.

Signed-off-by: Yulei Zhang <yuleixzhang@tencent.com>
---
 arch/x86/kvm/mmu/mmu.c | 39 ++++++++++++++++++++++++++++++---------
 1 file changed, 30 insertions(+), 9 deletions(-)

```
#### [RFC 5/9] Modify the page fault path to meet the direct build EPT requirement
##### From: Yulei Zhang <yulei.kernel@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yulei Zhang <yulei.kernel@gmail.com>
X-Patchwork-Id: 11702473
Return-Path: <SRS0=UpKl=BP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D18D0722
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  5 Aug 2020 19:59:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BBD9A22CE3
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  5 Aug 2020 19:59:24 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="avfgyGCI"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729728AbgHET6i (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 5 Aug 2020 15:58:38 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:45416 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727904AbgHEQmM (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 5 Aug 2020 12:42:12 -0400
Received: from mail-pg1-x543.google.com (mail-pg1-x543.google.com
 [IPv6:2607:f8b0:4864:20::543])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 9C490C0A893E;
        Wed,  5 Aug 2020 07:13:42 -0700 (PDT)
Received: by mail-pg1-x543.google.com with SMTP id p3so24507508pgh.3;
        Wed, 05 Aug 2020 07:13:42 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=K8w/qRSPiRGvQfAwvAEG9vaPeWJJC258oA4XZ+7V/5A=;
        b=avfgyGCIXlq9hgjbIhnPyKTrkyyn6mfx28wepMCd18SZQV5YadO4f1/77RoRfKQk/w
         7hWcQobOQlYZsmU2TThr1U1rcS3ZAskU+bXk3/esFuaDmWguaROHOw1cLPbwGvE6+A89
         1p3NirG7Bzxc9KqwFuMIfjKIyCoTMQJg5KyiOzVG8Nye336rAHCimiHnLxXpaMGXQtMB
         hPGvLgLKLBuRkqZF9u3VAhS7s9bCCoJNIYyBAtDVyMoKaBKn/xrYWoOcwJUn85+pe+bm
         4ECjc6m1GBH9UTj6EiCLRTBQ2TRgPvq9TVBlRLMoR4ger3biT7guANBuqaZw5bSsPlM2
         X8cg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=K8w/qRSPiRGvQfAwvAEG9vaPeWJJC258oA4XZ+7V/5A=;
        b=kJ9Fp0v3vBnoi2OsYraSNaAkTghC4u2689vM6s9P8NPjJI5cRlXdPE5wxnUtUhqgfS
         VPAsr2jeOJU6kChJoG8EbamKCE2Egilk+a584vgirK28wltcPkeyFxVK0SddChbrDtDc
         darTP/rrqVIujdsR0Y+LAttI8ykRznH+7iKEh3k/X/X5OUyr7DoQkZp3Yj7Lyp3/phUT
         koMW8mE5f/OMUI/IyTh1rOsPv8/Ui1VewrbfYZo7/xdC0mfdF3sDP/VOgCz8CZBrGbwr
         uBRIfLOHJLHmcRjwdJjbQ57rMVSV+ky4wCVah0eY4U3yTbvyvr7MOqoL0svknsnLMf6F
         +iyQ==
X-Gm-Message-State: AOAM533Skji63u14xl3E+l6IoIBnKwdYDEDhPR2G8dnWt9aUZhti/OIQ
        mKG8vZkR/Q04a2QxVcj5W70=
X-Google-Smtp-Source: 
 ABdhPJwp7Pld0z9vhrmzbG+AcO5ZnyP1GtoGFHh+Zphz7eH956FtbmT0Oys2jB12nUif/4/UGozEYg==
X-Received: by 2002:a63:3816:: with SMTP id f22mr3228491pga.311.1596636822205;
        Wed, 05 Aug 2020 07:13:42 -0700 (PDT)
Received: from localhost.localdomain ([203.205.141.56])
        by smtp.gmail.com with ESMTPSA id
 a129sm4069834pfd.165.2020.08.05.07.13.39
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 05 Aug 2020 07:13:41 -0700 (PDT)
From: Yulei Zhang <yulei.kernel@gmail.com>
To: pbonzini@redhat.com
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        sean.j.christopherson@intel.com, jmattson@google.com,
        vkuznets@redhat.com, xiaoguangrong.eric@gmail.com,
        kernellwp@gmail.com, lihaiwei.kernel@gmail.com,
        Yulei Zhang <yuleixzhang@tencent.com>
Subject: [RFC 5/9] Modify the page fault path to meet the direct build EPT
 requirement
Date: Wed,  5 Aug 2020 22:14:31 +0800
Message-Id: <20200805141431.9137-1-yulei.kernel@gmail.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Yulei Zhang <yuleixzhang@tencent.com>

Refine the fast page fault code so that it can be used in either
normal ept mode or direct build EPT mode.

Signed-off-by: Yulei Zhang <yuleixzhang@tencent.com>
---
 arch/x86/kvm/mmu/mmu.c | 30 +++++++++++++++++++++---------
 1 file changed, 21 insertions(+), 9 deletions(-)

```
#### [RFC 6/9] Apply the direct build EPT according to the memory slots change
##### From: Yulei Zhang <yulei.kernel@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yulei Zhang <yulei.kernel@gmail.com>
X-Patchwork-Id: 11702477
Return-Path: <SRS0=UpKl=BP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6A8C614B7
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  5 Aug 2020 19:59:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4ED5522D06
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  5 Aug 2020 19:59:42 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="YyYLES4l"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729130AbgHET71 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 5 Aug 2020 15:59:27 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:45438 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727923AbgHEQmM (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 5 Aug 2020 12:42:12 -0400
Received: from mail-pj1-x1041.google.com (mail-pj1-x1041.google.com
 [IPv6:2607:f8b0:4864:20::1041])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 2E27DC0086CC;
        Wed,  5 Aug 2020 07:14:06 -0700 (PDT)
Received: by mail-pj1-x1041.google.com with SMTP id kr4so4596050pjb.2;
        Wed, 05 Aug 2020 07:14:06 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=E6c0vghDkgEJ0a17A5+nuiHJ8D+179IgnQgcYz9dqaY=;
        b=YyYLES4lVVS0AwqF8KdFgvecU0rZ54MrgMfyenfeLVgPDjqeuE0TXmuAwbL39GI83J
         +brndbF+IwazD77a1klVuX3ccA7g93HF0Jhw/5QZqelQ5ejP+7SdCxbEgepXRveNIakf
         fWKicNGvCF+nNVi7kGy87yWOaspd6wZV4f+I0fSYIzNQ30POtG1mhkdMsTWz0ymGOJNa
         PouGZ2f5APwS3hygkDzHtxk9sZGHV9Z/3LWxkzdAkEkX+7jfsU2yKEMQhxZFcJpwKaMG
         Y2Vhxv/9VGGTXx695Mr4MizLST/MMzRNNimq54cwCS2JUY2tFJTiiCNGa9Cb7ypzWOXR
         L3lw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=E6c0vghDkgEJ0a17A5+nuiHJ8D+179IgnQgcYz9dqaY=;
        b=kG6jjb2MlMARf54JssL0VErD5V8l4e1RviW8DNLtBKN3xHNt2oVmcDj0ymdkXoZ1gS
         c/imZo/mBb87jqPoghozo1JJhjO5Lanj4tOzsfuMi3Gp3AIbQzXg6UxFsMrtPRxmKabv
         mNYKufABxbb+Z0hQrV0MYbn/jU6pT4Rz+8CA/1xjvPwSZkvl9s+3PeM0dmkTfwfyrUVN
         /Ta/UVOgPzsZFIISP/r2fisrCLKS9JuB2BLCF8E7jLbNCCRRuVVE5pCzeVZkidapI+s+
         Dn0MpugDv5lDlAkWWBdTLDbtjqfWeyUwW/JH/gJvdXDAwS+KTU6bLk0mSshti5lW4X1T
         6TbQ==
X-Gm-Message-State: AOAM530hFfA6lZYiIivb/SE96OTJTJ3bnRNekdOsN80wLQgthdhOWSBH
        9Sfn+B9uPpL25GYZfpFFFS8u7BeW
X-Google-Smtp-Source: 
 ABdhPJzGOtBj5jUOCmkzH/oXkJ+Jepgq3ah12aPXmimlVn1IaRS0eaGFAJXfoQebV2bsdecMhUPtWQ==
X-Received: by 2002:a17:90a:3d02:: with SMTP id
 h2mr3432297pjc.15.1596636845691;
        Wed, 05 Aug 2020 07:14:05 -0700 (PDT)
Received: from localhost.localdomain ([203.205.141.62])
        by smtp.gmail.com with ESMTPSA id
 p20sm3141184pjz.49.2020.08.05.07.14.02
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 05 Aug 2020 07:14:04 -0700 (PDT)
From: Yulei Zhang <yulei.kernel@gmail.com>
To: pbonzini@redhat.com
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        sean.j.christopherson@intel.com, jmattson@google.com,
        vkuznets@redhat.com, xiaoguangrong.eric@gmail.com,
        kernellwp@gmail.com, lihaiwei.kernel@gmail.com,
        Yulei Zhang <yuleixzhang@tencent.com>
Subject: [RFC 6/9] Apply the direct build EPT according to the memory slots
 change
Date: Wed,  5 Aug 2020 22:14:56 +0800
Message-Id: <20200805141456.9234-1-yulei.kernel@gmail.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Yulei Zhang <yuleixzhang@tencent.com>

Construct the direct build ept when guest memory slots have been
changed, and issue mmu_reload request to update the CR3 so that
guest could use the pre-constructed EPT without page fault.

Signed-off-by: Yulei Zhang <yuleixzhang@tencent.com>
---
 arch/mips/kvm/mips.c       | 13 +++++++++++++
 arch/powerpc/kvm/powerpc.c | 13 +++++++++++++
 arch/s390/kvm/kvm-s390.c   | 13 +++++++++++++
 arch/x86/kvm/mmu/mmu.c     | 33 ++++++++++++++++++++++++++-------
 include/linux/kvm_host.h   |  3 +++
 virt/kvm/kvm_main.c        | 13 +++++++++++++
 6 files changed, 81 insertions(+), 7 deletions(-)

```
#### [RFC 8/9] Introduce kvm module parameter global_tdp to turn on the direct build EPT mode
##### From: Yulei Zhang <yulei.kernel@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yulei Zhang <yulei.kernel@gmail.com>
X-Patchwork-Id: 11702485
Return-Path: <SRS0=UpKl=BP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0D1B114B7
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  5 Aug 2020 20:02:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E9CF720842
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  5 Aug 2020 20:01:59 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="vAw9kGgb"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727118AbgHEUB6 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 5 Aug 2020 16:01:58 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:45422 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727116AbgHEQkG (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 5 Aug 2020 12:40:06 -0400
Received: from mail-pf1-x444.google.com (mail-pf1-x444.google.com
 [IPv6:2607:f8b0:4864:20::444])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id E3B87C0086CF;
        Wed,  5 Aug 2020 07:15:10 -0700 (PDT)
Received: by mail-pf1-x444.google.com with SMTP id y206so12491410pfb.10;
        Wed, 05 Aug 2020 07:15:10 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=+xqqce3bt1Dd6YXyCPFzN+2GzEUcHoRk0/h1IH691fM=;
        b=vAw9kGgbL9KkM2+HjZkFVCiAEauRuoyizHa2DE6NIt/H/ukbr4biFl6FGaPLzqYR1m
         Y8feBgiVM4qSu50iFsGj6seA3Q+j9oLVsC7ZTIW301zQZQePILt51nINe00B/lm8asGU
         PKFIcoHfyTy1Yx46R8iwO4Rxoy5FpkzLWDtvWhOqdK9bSIiQs6/5DuDW7e0ipqsIoY0A
         08il6ksimfsPfvDVAGglj0SYwjOIfKLZxarQPN2FahhOz43Is6/czXHIMgMCOgMr4y04
         vhwJqQOnsRjbTh6jrbJbOGh7SYE4nuYoF8PVX7nrKYDnKxHNrLHLJczLHyu9B/gQ/KA7
         GRjA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=+xqqce3bt1Dd6YXyCPFzN+2GzEUcHoRk0/h1IH691fM=;
        b=bRSBgwUsoZJA+v2asKhhrB0Q6JOGDp+Ykwbvb5CrNSQaZhPP675pt3f6D8R4fqdKp+
         LAaeJPAlRVFqvwa0ysLPtO7c66We2P366giN0AR81qYVVzguwoaoZyXOvu7cHVUhlfQ9
         nUTanDYeXJb4ETE3aWDfUpZBOfdZYl5D8Tb4w0Ut5WomoXYzXqExMs2xjepXvUgi8UrV
         5gN+vh0eshD5/ehUs/kwbLjCJkFIQXVMS2yWY9R24gOg4/kYIVP6q2ZdPR1sNYU5Fyii
         jX/I9t4sQyqMRYgVNRJunhmvNkWfvMdfcxWjHudZRKYBClqFS9haijnnpWPD2tWczB6u
         /08Q==
X-Gm-Message-State: AOAM533zPAOCh9O5T70rmqZA9opE0BjCDZxblhpRgnOlqeFXeUCh1KBa
        ZYVQLt9r+8SmxpYqxPgbnmY=
X-Google-Smtp-Source: 
 ABdhPJwbuUbGXm01c54qPcEJaJWwHBAtthhYKl/qC5Dq5fmWMZtf+rrnJZ29JSqA4wwniCL3ChsA7g==
X-Received: by 2002:a62:6842:: with SMTP id d63mr3551252pfc.82.1596636907357;
        Wed, 05 Aug 2020 07:15:07 -0700 (PDT)
Received: from localhost.localdomain ([203.205.141.62])
        by smtp.gmail.com with ESMTPSA id
 g12sm3197172pjd.6.2020.08.05.07.15.04
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 05 Aug 2020 07:15:06 -0700 (PDT)
From: Yulei Zhang <yulei.kernel@gmail.com>
To: pbonzini@redhat.com
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        sean.j.christopherson@intel.com, jmattson@google.com,
        vkuznets@redhat.com, xiaoguangrong.eric@gmail.com,
        kernellwp@gmail.com, lihaiwei.kernel@gmail.com,
        Yulei Zhang <yuleixzhang@tencent.com>
Subject: [RFC 8/9] Introduce kvm module parameter global_tdp to turn on the
 direct build EPT mode
Date: Wed,  5 Aug 2020 22:15:56 +0800
Message-Id: <20200805141556.9430-1-yulei.kernel@gmail.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Yulei Zhang <yuleixzhang@tencent.com>

Currently global_tdp is only supported on intel X86 system with ept
supported, and it will turn off the smm mode when enable global_tdp.

Signed-off-by: Yulei Zhang <yuleixzhang@tencent.com>
---
 arch/x86/include/asm/kvm_host.h |  4 ++++
 arch/x86/kvm/mmu/mmu.c          |  5 ++++-
 arch/x86/kvm/x86.c              | 11 ++++++++++-
 3 files changed, 18 insertions(+), 2 deletions(-)

```
