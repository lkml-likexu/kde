#### [PATCH 1/9] KVM: arm64: pvtime: steal-time is only supported when configured
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11756655
Return-Path: <SRS0=EfB3=CN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B3FF0618
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  4 Sep 2020 10:48:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 91A6C208B3
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  4 Sep 2020 10:48:55 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1599216535;
	bh=hwGXasGI3vXuxzwR0fHBe/7NmPWta8DzMPNFt/WIVgM=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=l7a7pcZe7HOHUNNkzl3KkxvbPAfKc/y8xJaiDeYXIxg+bE00NRVZ3+FCaB/qw1HR2
	 gjjd2uB1xdU//ZLlMLUK6byVheIcu/e7aGS0HmT2ZUjMUmvHG7C6y8vyt324hxtoEz
	 l9w0+CL7wZBEUKYA5VK2NFskjCZR9pURVcxcZm7Q=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730100AbgIDKsw (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 4 Sep 2020 06:48:52 -0400
Received: from mail.kernel.org ([198.145.29.99]:58792 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728636AbgIDKqC (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 4 Sep 2020 06:46:02 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 25CF82084D;
        Fri,  4 Sep 2020 10:46:02 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1599216362;
        bh=hwGXasGI3vXuxzwR0fHBe/7NmPWta8DzMPNFt/WIVgM=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=q0FfVPp/FmurwSKrvSZ9N7lthPNpqqJd63RIhw6bd5GelQ0tHuTSdCClt/qF5V6z3
         4dd+PH2xU0Dw6X7d468qEWIi54HKZXY6srQ5KJmIHXvF5koaSFsjWdcl6EsoRV6mks
         1Pq7it2Urg/hKH+ZJK+AwolS7Bak52XjNquyEBII=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1kE9EG-0098oH-Ja; Fri, 04 Sep 2020 11:46:00 +0100
From: Marc Zyngier <maz@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Alexandru Elisei <alexandru.elisei@arm.com>,
        Andrew Jones <drjones@redhat.com>,
        Eric Auger <eric.auger@redhat.com>,
        Gavin Shan <gshan@redhat.com>,
        Steven Price <steven.price@arm.com>, kernel-team@android.com,
        linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Subject: [PATCH 1/9] KVM: arm64: pvtime: steal-time is only supported when
 configured
Date: Fri,  4 Sep 2020 11:45:22 +0100
Message-Id: <20200904104530.1082676-2-maz@kernel.org>
X-Mailer: git-send-email 2.27.0
In-Reply-To: <20200904104530.1082676-1-maz@kernel.org>
References: <20200904104530.1082676-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: pbonzini@redhat.com, alexandru.elisei@arm.com,
 drjones@redhat.com, eric.auger@redhat.com, gshan@redhat.com,
 steven.price@arm.com, kernel-team@android.com,
 linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
 kvm@vger.kernel.org
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Andrew Jones <drjones@redhat.com>

Don't confuse the guest by saying steal-time is supported when
it hasn't been configured by userspace and won't work.

Signed-off-by: Andrew Jones <drjones@redhat.com>
Signed-off-by: Marc Zyngier <maz@kernel.org>
Link: https://lore.kernel.org/r/20200804170604.42662-2-drjones@redhat.com
---
 arch/arm64/kvm/pvtime.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [PATCH v8 01/18] nitro_enclaves: Add ioctl interface definition
##### From: Andra Paraschiv <andraprs@amazon.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Paraschiv, Andra-Irina" <andraprs@amazon.com>
X-Patchwork-Id: 11758303
Return-Path: <SRS0=EfB3=CN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8C263138E
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  4 Sep 2020 18:02:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5AF5423D58
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  4 Sep 2020 18:02:02 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amazon.com header.i=@amazon.com
 header.b="REyWZldh"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728045AbgIDRhv (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 4 Sep 2020 13:37:51 -0400
Received: from smtp-fw-4101.amazon.com ([72.21.198.25]:49812 "EHLO
        smtp-fw-4101.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726800AbgIDRhu (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 4 Sep 2020 13:37:50 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.com; i=@amazon.com; q=dns/txt; s=amazon201209;
  t=1599241068; x=1630777068;
  h=from:to:cc:subject:date:message-id:in-reply-to:
   references:mime-version:content-transfer-encoding;
  bh=rZmxzJa++9MgO5sbtwcclbk5uyV6IgYtmIUjDOWHdJQ=;
  b=REyWZldhnq1t1h6iA91O5bZq2JMp3/BpqhHAHMkAk5Rzbpii72N+KjsG
   Ww1AAzpq7+8ceDs0kcQM0F5TeRRHC+1J0hu2ZNiPEGr3q1QIAasHE7ILS
   NMWhuBreQeCMXhslbyhqqSl4Z6lHa6pu3gmGHy65EfNZX5mxbAgz5gZUU
   0=;
X-IronPort-AV: E=Sophos;i="5.76,390,1592870400";
   d="scan'208";a="52178755"
Received: from iad12-co-svc-p1-lb1-vlan3.amazon.com (HELO
 email-inbound-relay-1d-5dd976cd.us-east-1.amazon.com) ([10.43.8.6])
  by smtp-border-fw-out-4101.iad4.amazon.com with ESMTP;
 04 Sep 2020 17:37:46 +0000
Received: from EX13D16EUB001.ant.amazon.com
 (iad55-ws-svc-p15-lb9-vlan2.iad.amazon.com [10.40.159.162])
        by email-inbound-relay-1d-5dd976cd.us-east-1.amazon.com (Postfix) with
 ESMTPS id C8ED8A20F8;
        Fri,  4 Sep 2020 17:37:45 +0000 (UTC)
Received: from 38f9d34ed3b1.ant.amazon.com (10.43.161.85) by
 EX13D16EUB001.ant.amazon.com (10.43.166.28) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Fri, 4 Sep 2020 17:37:35 +0000
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
Subject: [PATCH v8 01/18] nitro_enclaves: Add ioctl interface definition
Date: Fri, 4 Sep 2020 20:37:01 +0300
Message-ID: <20200904173718.64857-2-andraprs@amazon.com>
X-Mailer: git-send-email 2.20.1 (Apple Git-117)
In-Reply-To: <20200904173718.64857-1-andraprs@amazon.com>
References: <20200904173718.64857-1-andraprs@amazon.com>
MIME-Version: 1.0
X-Originating-IP: [10.43.161.85]
X-ClientProxiedBy: EX13D13UWB001.ant.amazon.com (10.43.161.156) To
 EX13D16EUB001.ant.amazon.com (10.43.166.28)
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
---
 .../userspace-api/ioctl/ioctl-number.rst      |   5 +-
 include/linux/nitro_enclaves.h                |  11 +
 include/uapi/linux/nitro_enclaves.h           | 359 ++++++++++++++++++
 3 files changed, 374 insertions(+), 1 deletion(-)
 create mode 100644 include/linux/nitro_enclaves.h
 create mode 100644 include/uapi/linux/nitro_enclaves.h

```
#### [PATCH v14 01/10] arm64: Probe for the presence of KVM hypervisor services during boot
##### From: Jianyong Wu <jianyong.wu@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jianyong Wu <jianyong.wu@arm.com>
X-Patchwork-Id: 11756457
Return-Path: <SRS0=EfB3=CN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7247B109A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  4 Sep 2020 09:32:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 62C74207EA
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  4 Sep 2020 09:32:15 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730105AbgIDJ3H (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 4 Sep 2020 05:29:07 -0400
Received: from foss.arm.com ([217.140.110.172]:46732 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729584AbgIDJ3F (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 4 Sep 2020 05:29:05 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 655601063;
        Fri,  4 Sep 2020 02:29:04 -0700 (PDT)
Received: from localhost.localdomain (entos-thunderx2-desktop.shanghai.arm.com
 [10.169.212.215])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPA id
 B06813F66F;
        Fri,  4 Sep 2020 02:28:58 -0700 (PDT)
From: Jianyong Wu <jianyong.wu@arm.com>
To: netdev@vger.kernel.org, yangbo.lu@nxp.com, john.stultz@linaro.org,
        tglx@linutronix.de, pbonzini@redhat.com,
        sean.j.christopherson@intel.com, maz@kernel.org,
        richardcochran@gmail.com, Mark.Rutland@arm.com, will@kernel.org,
        suzuki.poulose@arm.com, steven.price@arm.com
Cc: linux-kernel@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        Steve.Capper@arm.com, justin.he@arm.com, jianyong.wu@arm.com,
        nd@arm.com
Subject: [PATCH v14 01/10] arm64: Probe for the presence of KVM hypervisor
 services during boot
Date: Fri,  4 Sep 2020 17:27:35 +0800
Message-Id: <20200904092744.167655-2-jianyong.wu@arm.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200904092744.167655-1-jianyong.wu@arm.com>
References: <20200904092744.167655-1-jianyong.wu@arm.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Will Deacon <will@kernel.org>

Although the SMCCC specification provides some limited functionality for
describing the presence of hypervisor and firmware services, this is
generally applicable only to functions designated as "Arm Architecture
Service Functions" and no portable discovery mechanism is provided for
standard hypervisor services, despite having a designated range of
function identifiers reserved by the specification.

In an attempt to avoid the need for additional firmware changes every
time a new function is added, introduce a UID to identify the service
provider as being compatible with KVM. Once this has been established,
additional services can be discovered via a feature bitmap.

Cc: Marc Zyngier <maz@kernel.org>
Signed-off-by: Will Deacon <will@kernel.org>
Signed-off-by: Jianyong Wu <jianyong.wu@arm.com>
---
 arch/arm64/include/asm/hypervisor.h | 11 +++++++++
 arch/arm64/kernel/setup.c           | 36 +++++++++++++++++++++++++++++
 include/linux/arm-smccc.h           | 26 +++++++++++++++++++++
 3 files changed, 73 insertions(+)

```
#### [GIT PULL] KVM/arm64 fixes for 5.9
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11756627
Return-Path: <SRS0=EfB3=CN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 58173618
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  4 Sep 2020 10:46:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3D8052084D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  4 Sep 2020 10:46:41 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1599216401;
	bh=emfYI5A6yt/uyLK8UfzYiitooNVKksAc8FkL2+qvA7c=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=fu8Nwp/zaLeujrzA4qY1vXzaKkIJuc2tGWpjL+M972wV+QDolY422xylb7dJ9jrga
	 mFiWYXyQm7tzsjYCjfBQo7q16YQy/oVVBhFX4CPGzHsej99iI1SQ0d2TxCobmRR24E
	 BDoQT8j4c32uVxpNY7v6CzXyXp1GJqau/qW14u28=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729741AbgIDKqh (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 4 Sep 2020 06:46:37 -0400
Received: from mail.kernel.org ([198.145.29.99]:58750 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726171AbgIDKqC (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 4 Sep 2020 06:46:02 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 8925320770;
        Fri,  4 Sep 2020 10:46:01 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1599216361;
        bh=emfYI5A6yt/uyLK8UfzYiitooNVKksAc8FkL2+qvA7c=;
        h=From:To:Cc:Subject:Date:From;
        b=SUl1fEUncq5ywbwQWlGS/ZWBgkfbdJEAjcRUbgtxQSI7GWWZfG/Kk5YwcUYYM7rU1
         ll/ao5a925iM+qCX2vT6IIXVqcTs+GxWI/Rd8XiJLVob1aGeV96ggS923pKuClssM0
         bkQSHTFQ2ySdZw7AO8uK7DHTxLKZTZKxP/m15g5g=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1kE9EG-0098oH-0a; Fri, 04 Sep 2020 11:46:00 +0100
From: Marc Zyngier <maz@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Alexandru Elisei <alexandru.elisei@arm.com>,
        Andrew Jones <drjones@redhat.com>,
        Eric Auger <eric.auger@redhat.com>,
        Gavin Shan <gshan@redhat.com>,
        Steven Price <steven.price@arm.com>, kernel-team@android.com,
        linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Subject: [GIT PULL] KVM/arm64 fixes for 5.9
Date: Fri,  4 Sep 2020 11:45:21 +0100
Message-Id: <20200904104530.1082676-1-maz@kernel.org>
X-Mailer: git-send-email 2.27.0
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: pbonzini@redhat.com, alexandru.elisei@arm.com,
 drjones@redhat.com, eric.auger@redhat.com, gshan@redhat.com,
 steven.price@arm.com, kernel-team@android.com,
 linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
 kvm@vger.kernel.org
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Paolo,

Here's a bunch of fixes for 5.9. The gist of it is the stolen time
rework from Andrew, but we also have a couple of MM fixes that have
surfaced as people have started to use hugetlbfs in anger.

Please pull,

	M.

The following changes since commit 9123e3a74ec7b934a4a099e98af6a61c2f80bbf5:

  Linux 5.9-rc1 (2020-08-16 13:04:57 -0700)

are available in the Git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/kvmarm/kvmarm.git tags/kvmarm-fixes-5.9-1

for you to fetch changes up to 7b75cd5128421c673153efb1236705696a1a9812:

  KVM: arm64: Update page shift if stage 2 block mapping not supported (2020-09-04 10:53:48 +0100)

----------------------------------------------------------------
KVM/arm64 fixes for Linux 5.9, take #1

- Multiple stolen time fixes, with a new capability to match x86
- Fix for hugetlbfs mappings when PUD and PMD are the same level
- Fix for hugetlbfs mappings when PTE mappings are enforced
  (dirty logging, for example)
- Fix tracing output of 64bit values

----------------------------------------------------------------
Alexandru Elisei (1):
      KVM: arm64: Update page shift if stage 2 block mapping not supported

Andrew Jones (6):
      KVM: arm64: pvtime: steal-time is only supported when configured
      KVM: arm64: pvtime: Fix potential loss of stolen time
      KVM: arm64: Drop type input from kvm_put_guest
      KVM: arm64: pvtime: Fix stolen time accounting across migration
      KVM: Documentation: Minor fixups
      arm64/x86: KVM: Introduce steal-time cap

Marc Zyngier (2):
      KVM: arm64: Do not try to map PUDs when they are folded into PMD
      KVM: arm64: Fix address truncation in traces

 Documentation/virt/kvm/api.rst     | 22 ++++++++++++++++++----
 arch/arm64/include/asm/kvm_host.h  |  2 +-
 arch/arm64/kvm/arm.c               |  3 +++
 arch/arm64/kvm/mmu.c               |  8 +++++++-
 arch/arm64/kvm/pvtime.c            | 29 +++++++++++++----------------
 arch/arm64/kvm/trace_arm.h         | 16 ++++++++--------
 arch/arm64/kvm/trace_handle_exit.h |  6 +++---
 arch/x86/kvm/x86.c                 |  3 +++
 include/linux/kvm_host.h           | 31 ++++++++++++++++++++++++++-----
 include/uapi/linux/kvm.h           |  1 +
 10 files changed, 83 insertions(+), 38 deletions(-)

From patchwork Fri Sep  4 10:45:23 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11756631
Return-Path: <SRS0=EfB3=CN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C5120618
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  4 Sep 2020 10:46:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A3DCD2087C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  4 Sep 2020 10:46:47 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1599216407;
	bh=mIOES2oHYEYo5N/ys71QEEfVp16YdoOph7z6Wrougfk=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=hBM/92+CrEyvzCfHpl2e9FUj+sEcrb8sxgwlxHTkfJdzvwu9p2xh9UMeOkPEt/eos
	 7FzSYgvH7aGEYzZkq8oEVWNI2lIBm1GOZ/SZLZr7T4FQZ5a7lslKUu+e9PuKmsKzq5
	 Lix7uVS1hSYGtr7ZNNOTGQ8ZIYtyWn++SgVnXXl8=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730066AbgIDKqm (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 4 Sep 2020 06:46:42 -0400
Received: from mail.kernel.org ([198.145.29.99]:58820 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729582AbgIDKqD (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 4 Sep 2020 06:46:03 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id A4D882087C;
        Fri,  4 Sep 2020 10:46:02 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1599216362;
        bh=mIOES2oHYEYo5N/ys71QEEfVp16YdoOph7z6Wrougfk=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=PDUxXl55pS8P0i2mXv8eXiPFRnDlSsjvAB+5QhghbY4LOy55VUh4gNHr+qKYIqp2C
         ZQ0aCYrmuGeToF3qJsRxuR0V4jHl+tYvra5QyGZkSMc84716glwQPrjmrWNUEZ56ZU
         zccPHA1SUcz94hNN9twx6JN82PZz34Y5Twp2LR7c=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1kE9EH-0098oH-4r; Fri, 04 Sep 2020 11:46:01 +0100
From: Marc Zyngier <maz@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Alexandru Elisei <alexandru.elisei@arm.com>,
        Andrew Jones <drjones@redhat.com>,
        Eric Auger <eric.auger@redhat.com>,
        Gavin Shan <gshan@redhat.com>,
        Steven Price <steven.price@arm.com>, kernel-team@android.com,
        linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Subject: [PATCH 2/9] KVM: arm64: pvtime: Fix potential loss of stolen time
Date: Fri,  4 Sep 2020 11:45:23 +0100
Message-Id: <20200904104530.1082676-3-maz@kernel.org>
X-Mailer: git-send-email 2.27.0
In-Reply-To: <20200904104530.1082676-1-maz@kernel.org>
References: <20200904104530.1082676-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: pbonzini@redhat.com, alexandru.elisei@arm.com,
 drjones@redhat.com, eric.auger@redhat.com, gshan@redhat.com,
 steven.price@arm.com, kernel-team@android.com,
 linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
 kvm@vger.kernel.org
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Andrew Jones <drjones@redhat.com>

We should only check current->sched_info.run_delay once when
updating stolen time. Otherwise there's a chance there could
be a change between checks that we miss (preemption disabling
comes after vcpu request checks).

Signed-off-by: Andrew Jones <drjones@redhat.com>
Signed-off-by: Marc Zyngier <maz@kernel.org>
Link: https://lore.kernel.org/r/20200804170604.42662-3-drjones@redhat.com
---
 arch/arm64/kvm/pvtime.c | 5 +++--
 1 file changed, 3 insertions(+), 2 deletions(-)

```
#### [PATCH] KVM: SVM: Add tracepoint for cr_interception
##### From: Haiwei Li <lihaiwei.kernel@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Haiwei Li <lihaiwei.kernel@gmail.com>
X-Patchwork-Id: 11756741
Return-Path: <SRS0=EfB3=CN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8DD2A138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  4 Sep 2020 11:27:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 75937206B7
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  4 Sep 2020 11:27:23 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="rmly/Hi2"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730163AbgIDL1T (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 4 Sep 2020 07:27:19 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:59624 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1730185AbgIDL1I (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 4 Sep 2020 07:27:08 -0400
Received: from mail-pj1-x1042.google.com (mail-pj1-x1042.google.com
 [IPv6:2607:f8b0:4864:20::1042])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id A19C7C06123F;
        Fri,  4 Sep 2020 04:25:42 -0700 (PDT)
Received: by mail-pj1-x1042.google.com with SMTP id kk9so540923pjb.2;
        Fri, 04 Sep 2020 04:25:42 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=to:cc:from:subject:message-id:date:user-agent:mime-version
         :content-language:content-transfer-encoding;
        bh=4iF/KxJRf6RUN8ireZqNsFjdJniXRQCA0m2V2VdM7aY=;
        b=rmly/Hi26HxZ+lf1DtFGWTwggsOa+IuyWuUP6RCnfw6k7QWod4onfRB1eQGLonapfA
         mp48rqLbdh4MERxOKwp7yA5dvcmxZHdG0sLRkO9GHO2eH09WBeQJCj+oXN680YkMT/Vy
         5BriiWyC1iIlLFf38pw5AlucY1drz+Zn207Z7ywoQrJqIEG4OMwUIVx7VPTWJxxHWUwT
         TXFldnzkaBvcItl2YAsxsTBs02qrayxmEAil7cGau2+XbuOcPsoNNDUrRBUABJbxoq3j
         jvzm0OEXspY6rVCxSOvHkOIehW8NR0Jjd9g+bLyPbwTylxLj2rxXnfJ7eM08Oxih6Zi2
         2X2A==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:to:cc:from:subject:message-id:date:user-agent
         :mime-version:content-language:content-transfer-encoding;
        bh=4iF/KxJRf6RUN8ireZqNsFjdJniXRQCA0m2V2VdM7aY=;
        b=TDqo1WvdwwYIH8hK/QbDwfpb5225Mv/mKxO2+KlHieFBZpvO5nx5stcYc/YYfwGSH1
         K3kVoMVF/ZHDNIlT6Lh1fykBRyrzDcyPMDW0AwbgjlYrb2vgwztS4SAIy0wPIZVfq+7G
         qVyhplPtk8yZheWz9Xm6ZcCQ0NRaV2lUGPs0BHjpqzMtNgg70he/ZREFig+uFnqHuXoG
         ZWlMh7gXbo8jsICMK6/B6l6rWPyxyr4j5k3UYXodslSa0+WRnramsNnCw+eSSCfb+BYs
         yStGYBUFwmTuiWSxvqVuoqL7v84nFtqi8c5RXwydiOGhFfwzCAFnsTjZrGwq7mNXgc4p
         glOA==
X-Gm-Message-State: AOAM533iaKG1WmrqCU0KlmE8S44PhSWHIWDA8/JteKXdbv8dwhwBkVKC
        BsLNEVgH8HKdbFFBPZ8xWw==
X-Google-Smtp-Source: 
 ABdhPJwA6BUd2QTxpgWoADDjuuNYMmhS0f6lh9N/5x3Gvo3/JYPUwvc7iWOFYYyvAimk0pavjAATMw==
X-Received: by 2002:a17:90a:9382:: with SMTP id
 q2mr7622795pjo.118.1599218742271;
        Fri, 04 Sep 2020 04:25:42 -0700 (PDT)
Received: from [127.0.0.1] ([103.7.29.7])
        by smtp.gmail.com with ESMTPSA id
 72sm6298793pfx.79.2020.09.04.04.25.36
        (version=TLS1_3 cipher=TLS_AES_128_GCM_SHA256 bits=128/128);
        Fri, 04 Sep 2020 04:25:41 -0700 (PDT)
To: "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>,
        "kvm@vger.kernel.org" <kvm@vger.kernel.org>,
        "x86@kernel.org" <x86@kernel.org>
Cc: "hpa@zytor.com" <hpa@zytor.com>, "bp@alien8.de" <bp@alien8.de>,
        "mingo@redhat.com" <mingo@redhat.com>,
        "tglx@linutronix.de" <tglx@linutronix.de>, joro@8bytes.org,
        "jmattson@google.com" <jmattson@google.com>,
        "wanpengli@tencent.com" <wanpengli@tencent.com>,
        vkuznets@redhat.com, sean.j.christopherson@intel.com,
        "pbonzini@redhat.com" <pbonzini@redhat.com>
From: Haiwei Li <lihaiwei.kernel@gmail.com>
Subject: [PATCH] KVM: SVM: Add tracepoint for cr_interception
Message-ID: <f3031602-db3b-c4fe-b719-d402663b0a2b@gmail.com>
Date: Fri, 4 Sep 2020 19:25:29 +0800
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:68.0)
 Gecko/20100101 Thunderbird/68.12.0
MIME-Version: 1.0
Content-Language: en-US
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Haiwei Li <lihaiwei@tencent.com>

Add trace_kvm_cr_write and trace_kvm_cr_read for svm.

Signed-off-by: Haiwei Li <lihaiwei@tencent.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
  arch/x86/kvm/svm/svm.c | 2 ++
  1 file changed, 2 insertions(+)

--
2.18.4

```
#### [PATCH v10 28/30] samples: vfio-mdev/mbochs: fix common struct sg_table related issues
##### From: Marek Szyprowski <m.szyprowski@samsung.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marek Szyprowski <m.szyprowski@samsung.com>
X-Patchwork-Id: 11757379
Return-Path: <SRS0=EfB3=CN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id ECFED91F
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  4 Sep 2020 14:12:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CB0362074A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  4 Sep 2020 14:12:39 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=samsung.com header.i=@samsung.com
 header.b="VTlKnAw+"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730751AbgIDOM3 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 4 Sep 2020 10:12:29 -0400
Received: from mailout1.w1.samsung.com ([210.118.77.11]:44694 "EHLO
        mailout1.w1.samsung.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1730588AbgIDNpX (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 4 Sep 2020 09:45:23 -0400
Received: from eucas1p1.samsung.com (unknown [182.198.249.206])
        by mailout1.w1.samsung.com (KnoxPortal) with ESMTP id
 20200904133511euoutp0164563fcc7c300abedc449f32d94126ad~xmAoWy3GJ0721507215euoutp01x
        for <kvm@vger.kernel.org>; Fri,  4 Sep 2020 13:35:11 +0000 (GMT)
DKIM-Filter: OpenDKIM Filter v2.11.0 mailout1.w1.samsung.com
 20200904133511euoutp0164563fcc7c300abedc449f32d94126ad~xmAoWy3GJ0721507215euoutp01x
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=samsung.com;
        s=mail20170921; t=1599226511;
        bh=58WfIsMQtyJl7jKA0xKnsRe1U/pxzIhIdCQa1t7BJpo=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=VTlKnAw+fxk26VLKXWeIA0uc5DQDWeVgEKv/ZJljyw6UhyPT5IkjxwvU6gYZMqcJ6
         qM9QUnVWYEdNfs/jl7Tu8DxuJpJHp7IdKtaMsa1vbRnLYUA9p7lq9UmQ2eA+ywu6d/
         n+OgC5UwunH8UE/iPoSP/dS8K/9xRhuwvSYN47l4=
Received: from eusmges2new.samsung.com (unknown [203.254.199.244]) by
        eucas1p1.samsung.com (KnoxPortal) with ESMTP id
        20200904133511eucas1p1db8cd5f80eec531ed3f17eff8e18b6c3~xmAoEqN5-0114101141eucas1p1B;
        Fri,  4 Sep 2020 13:35:11 +0000 (GMT)
Received: from eucas1p1.samsung.com ( [182.198.249.206]) by
        eusmges2new.samsung.com (EUCPMTA) with SMTP id C2.76.05997.F82425F5;
 Fri,  4
        Sep 2020 14:35:11 +0100 (BST)
Received: from eusmtrp2.samsung.com (unknown [182.198.249.139]) by
        eucas1p2.samsung.com (KnoxPortal) with ESMTPA id
        20200904133511eucas1p2f7241258a90f27b0aa67e62e74c48727~xmAnuPz-g1447714477eucas1p2f;
        Fri,  4 Sep 2020 13:35:11 +0000 (GMT)
Received: from eusmgms2.samsung.com (unknown [182.198.249.180]) by
        eusmtrp2.samsung.com (KnoxPortal) with ESMTP id
        20200904133511eusmtrp2fb28d0c94602321d95e9c106fbea7422~xmAnthj880977109771eusmtrp2P;
        Fri,  4 Sep 2020 13:35:11 +0000 (GMT)
X-AuditID: cbfec7f4-65dff7000000176d-7f-5f52428f5f85
Received: from eusmtip1.samsung.com ( [203.254.199.221]) by
        eusmgms2.samsung.com (EUCPMTA) with SMTP id 84.B0.06017.E82425F5;
 Fri,  4
        Sep 2020 14:35:11 +0100 (BST)
Received: from AMDC2765.digital.local (unknown [106.120.51.73]) by
        eusmtip1.samsung.com (KnoxPortal) with ESMTPA id
        20200904133510eusmtip15068735ab97c561d115ca561029ac0cb~xmAnIuEoi2113421134eusmtip15;
        Fri,  4 Sep 2020 13:35:10 +0000 (GMT)
From: Marek Szyprowski <m.szyprowski@samsung.com>
To: dri-devel@lists.freedesktop.org, iommu@lists.linux-foundation.org,
        linaro-mm-sig@lists.linaro.org, linux-kernel@vger.kernel.org
Cc: Marek Szyprowski <m.szyprowski@samsung.com>,
        Christoph Hellwig <hch@lst.de>,
        Robin Murphy <robin.murphy@arm.com>,
        Bartlomiej Zolnierkiewicz <b.zolnierkie@samsung.com>,
        linux-arm-kernel@lists.infradead.org,
        David Airlie <airlied@linux.ie>,
        Daniel Vetter <daniel@ffwll.ch>,
        Kirti Wankhede <kwankhede@nvidia.com>, kvm@vger.kernel.org
Subject: [PATCH v10 28/30] samples: vfio-mdev/mbochs: fix common struct
 sg_table related issues
Date: Fri,  4 Sep 2020 15:17:09 +0200
Message-Id: <20200904131711.12950-29-m.szyprowski@samsung.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200904131711.12950-1-m.szyprowski@samsung.com>
X-Brightmail-Tracker: 
 H4sIAAAAAAAAA+NgFtrCKsWRmVeSWpSXmKPExsWy7djPc7r9TkHxBg2LpCx6z51kstg4Yz2r
        xf9tE5ktrnx9z2axcvVRJosF+60t5kwttNhyei6jxZcrD5ksNj2+xmpxedccNou1R+6yWxz8
        8ITVgddjzbw1jB57vy1g8dj+7QGrx/3u40wem5fUe9z+95jZY/KN5Yweu282sHn0Nr9j8+jb
        sorR4/MmuQDuKC6blNSczLLUIn27BK6Maes3sxdcE6xY+fkSewPjPb4uRg4OCQETicNbg7oY
        uTiEBFYwSixZ2MUO4XxhlHjduhfK+cwo0bDgHxNMR+v+MIj4ckaJNZfXMcJ1rDp0Csjh5GAT
        MJToetvFBmKLCLQySpzo5QEpYha4xiTx9u87VpCEsECixL59p8FsFgFVia2H/oLZvAJ2Ejva
        X4ANkhCQl1i94QAziM0JFN864wkryCAJgUPsEm+/bmeBOMlFYtUjd4h6YYlXx7ewQ9gyEv93
        zmeCqG9mlHh4bi07hNPDKHG5aQbUBmuJO+d+sYEMYhbQlFi/Sx8i7CjxdMJTqJf5JG68FQQJ
        MwOZk7ZNZ4YI80p0tAlBVKtJzDq+Dm7twQuXmCFsD4n5/59AQ3Eio8ShP+/ZJjDKz0JYtoCR
        cRWjeGppcW56arFRXmq5XnFibnFpXrpecn7uJkZgWjr97/iXHYy7/iQdYhTgYFTi4WWwD4oX
        Yk0sK67MPcQowcGsJMLrdPZ0nBBvSmJlVWpRfnxRaU5q8SFGaQ4WJXFe40UvY4UE0hNLUrNT
        UwtSi2CyTBycUg2MdZuvJnStZ8h5XjTdtCFu3WqLoEcbtpgyLnn05bUu61XmvuBw3fsfTyye
        0Kn5PHhVEL/ZlwkfmesmOEmVrvO3ikw7vOCwMjvj7elh/7S/iVtNX/Y8LNnu+qaqPWZdMwqn
        17We3V3erj5rsYFvp8SbH0vnG8f+f1cTWDU31OPvZ33xZv1U/csVSizFGYmGWsxFxYkAlWSI
        NEcDAAA=
X-Brightmail-Tracker: 
 H4sIAAAAAAAAA+NgFprKIsWRmVeSWpSXmKPExsVy+t/xu7r9TkHxBltXMVn0njvJZLFxxnpW
        i//bJjJbXPn6ns1i5eqjTBYL9ltbzJlaaLHl9FxGiy9XHjJZbHp8jdXi8q45bBZrj9xltzj4
        4QmrA6/HmnlrGD32flvA4rH92wNWj/vdx5k8Ni+p97j97zGzx+Qbyxk9dt9sYPPobX7H5tG3
        ZRWjx+dNcgHcUXo2RfmlJakKGfnFJbZK0YYWRnqGlhZ6RiaWeobG5rFWRqZK+nY2Kak5mWWp
        Rfp2CXoZ09ZvZi+4Jlix8vMl9gbGe3xdjBwcEgImEq37w7oYOTmEBJYySry/lwViSwjISJyc
        1sAKYQtL/LnWxdbFyAVU84lRYuLj5+wgCTYBQ4mutxAJEYFORolp3R/BEswC95gk9q7zA7GF
        BeIl/qzcDxZnEVCV2HroL9hUXgE7iR3tLxghNshLrN5wgBnE5gSKb53xhBXiIluJD3MWs0xg
        5FvAyLCKUSS1tDg3PbfYSK84Mbe4NC9dLzk/dxMjMEq2Hfu5ZQdj17vgQ4wCHIxKPLwM9kHx
        QqyJZcWVuYcYJTiYlUR4nc6ejhPiTUmsrEotyo8vKs1JLT7EaAp01ERmKdHkfGAE55XEG5oa
        mltYGpobmxubWSiJ83YIHIwREkhPLEnNTk0tSC2C6WPi4JRqYOzk0Tqp8LQymyPoWpVVwPOP
        kZNeMQTvPW+2bK6JKfvTQqXNDW2ZZyLOib85WNdev/Xw1jd7LH5Fflz6ojTOa1b5SwerxMl1
        m3z/iE20rhHexSp9/pb+t8W2mcobnUTKEwzs/b5f5+Zjqc6fFT2r0JZd8KVzcf/dnu6tDVZX
        IjUj5B/ukT7vqcRSnJFoqMVcVJwIAH5KQUqoAgAA
X-CMS-MailID: 20200904133511eucas1p2f7241258a90f27b0aa67e62e74c48727
X-Msg-Generator: CA
X-RootMTR: 20200904133511eucas1p2f7241258a90f27b0aa67e62e74c48727
X-EPHeader: CA
CMS-TYPE: 201P
X-CMS-RootMailID: 20200904133511eucas1p2f7241258a90f27b0aa67e62e74c48727
References: <20200904131711.12950-1-m.szyprowski@samsung.com>
        <CGME20200904133511eucas1p2f7241258a90f27b0aa67e62e74c48727@eucas1p2.samsung.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The Documentation/DMA-API-HOWTO.txt states that the dma_map_sg() function
returns the number of the created entries in the DMA address space.
However the subsequent calls to the dma_sync_sg_for_{device,cpu}() and
dma_unmap_sg must be called with the original number of the entries
passed to the dma_map_sg().

struct sg_table is a common structure used for describing a non-contiguous
memory buffer, used commonly in the DRM and graphics subsystems. It
consists of a scatterlist with memory pages and DMA addresses (sgl entry),
as well as the number of scatterlist entries: CPU pages (orig_nents entry)
and DMA mapped pages (nents entry).

It turned out that it was a common mistake to misuse nents and orig_nents
entries, calling DMA-mapping functions with a wrong number of entries or
ignoring the number of mapped entries returned by the dma_map_sg()
function.

To avoid such issues, lets use a common dma-mapping wrappers operating
directly on the struct sg_table objects and use scatterlist page
iterators where possible. This, almost always, hides references to the
nents and orig_nents entries, making the code robust, easier to follow
and copy/paste safe.

While touching this code, also add missing call to dma_unmap_sgtable.

Signed-off-by: Marek Szyprowski <m.szyprowski@samsung.com>
Reviewed-by: Robin Murphy <robin.murphy@arm.com>
---
 samples/vfio-mdev/mbochs.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [RFC] KVM: X86: implement Passthrough IPI Message-Id: <0109A01C-59D0-4C72-8B05-14959AD26AD2@bytedance.com>
##### From: =?utf-8?b?6YKT5qGl?= <dengqiao.joey@bytedance.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?b?6YKT5qGl?= <dengqiao.joey@bytedance.com>
X-Patchwork-Id: 11756775
Return-Path: <SRS0=EfB3=CN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EC8D71599
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  4 Sep 2020 11:33:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C412A208C7
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  4 Sep 2020 11:33:09 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=bytedance-com.20150623.gappssmtp.com
 header.i=@bytedance-com.20150623.gappssmtp.com header.b="lcamAIZF"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730021AbgIDLdI (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 4 Sep 2020 07:33:08 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:32898 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729954AbgIDLc1 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 4 Sep 2020 07:32:27 -0400
Received: from mail-pj1-x1043.google.com (mail-pj1-x1043.google.com
 [IPv6:2607:f8b0:4864:20::1043])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 6F2C6C061244
        for <kvm@vger.kernel.org>; Fri,  4 Sep 2020 04:32:27 -0700 (PDT)
Received: by mail-pj1-x1043.google.com with SMTP id g6so2928271pjl.0
        for <kvm@vger.kernel.org>; Fri, 04 Sep 2020 04:32:27 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=bytedance-com.20150623.gappssmtp.com; s=20150623;
        h=from:content-transfer-encoding:mime-version:subject:message-id:date
         :cc:to;
        bh=BBVb3FSWiPJHFK9MBBhv4J63/7k1Ou4B0fnv9L/nxTI=;
        b=lcamAIZFPcvWQVNO5/253V4+ERhvPT2Q5LAlBZHLHAyI6ui4mBPLCWu1ktvzgI70dj
         +K9tEsapN/kBrnvF7D+AjKssXopLMmAAJ76A7hRmxK1w5CxMIWpP9B5gL7Iwx+G62Cbw
         nuocnkj31/ZzzaRPtO+wQvYsgIOgDzd6tBLNUUCXPwVGgqfOwxnu1p58oYyqusosnmPA
         9KLrh9YWuyV9Kgn6Kz1VieYKEK6WGlSs1/vW8GQQtVvmEgObFu3YVIkfFTcK1QMeU3ru
         yksXYcFgjVRXM3fvLEx4+9tVsnONXSOekPk0t1RQyF2ML/oTIvdSiAIijQA+tAtkbAJl
         5+6w==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:content-transfer-encoding:mime-version
         :subject:message-id:date:cc:to;
        bh=BBVb3FSWiPJHFK9MBBhv4J63/7k1Ou4B0fnv9L/nxTI=;
        b=hUIvxKbIdywzqtpUygWBUuRZZkGpk1NfwpCMrEROTOtVApj9L0iPgg9LIkPdziam+p
         llXI2An5orLdZlQynEu+LI9BadFCJGmdNdd7kN0orCKrsLqVqvNzQD9Bg0ogJbd+ZyV7
         aWfGyMigx+MS9YnQ2o40isLxamxv8EfeSlLRIhA8aQNXDeFBzUXwN+gAMSbz0NKyBG7C
         36wvU93qvs8hppoxlmeoMlYWlPOivESxetEZcjr1APmbVYmHC0jDQczZsK93vF164hhf
         3dk2q5Pz6UyNwHGnHXXdNs1QRuUQ+QCDO4OHxT1XXP8TgKy+PzExKaLmThKa4SCBp373
         ryDQ==
X-Gm-Message-State: AOAM531hcBfhn2Axv0q+uzYn5+FBAPc63cI2pYZmjyRzfM7EkMfB+esG
        CSxIJ7TO6t9cQ6xMJNtplFcPdyRZd1M8JJe7
X-Google-Smtp-Source: 
 ABdhPJxEUVcK4BhucchgJRiMM4UbUM8Nz7g/4rVRSUlN7fb3qrdLfUggYiBgvLBKxuqFPXzhM4wYrQ==
X-Received: by 2002:a17:902:7d84:: with SMTP id
 a4mr8395802plm.44.1599219146168;
        Fri, 04 Sep 2020 04:32:26 -0700 (PDT)
Received: from [10.94.81.238] ([103.136.221.68])
        by smtp.gmail.com with ESMTPSA id
 h15sm5522142pjf.54.2020.09.04.04.32.23
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Fri, 04 Sep 2020 04:32:25 -0700 (PDT)
From: =?utf-8?b?6YKT5qGl?= <dengqiao.joey@bytedance.com>
Mime-Version: 1.0 (Mac OS X Mail 13.4 \(3608.80.23.2.2\))
Subject: [RFC] KVM: X86: implement Passthrough IPI 
Message-Id: <0109A01C-59D0-4C72-8B05-14959AD26AD2@bytedance.com>
Date: Fri, 4 Sep 2020 19:31:51 +0800
Cc: pbonzini@redhat.com, rkrcmar@redhat.com, yang.zhang.wz@gmail.com,
        zhouyibo@bytedance.com, zhanghaozhong@bytedance.com
To: kvm@vger.kernel.org
X-Mailer: Apple Mail (2.3608.80.23.2.2)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch paravirtualize the IPI sending process in guest by exposing
posted interrupt capability to guest directly . Since there is no VM Exit 
and VM Entry when sending IPI, the overhead is therefore reduced.

The basic idea is that:
Exposing the PI_DESC  and msr.icr to guest. When sending a IPI, set 
the PIR of destination VCPU’s PI_DESC from guest directly and write
the ICR with notification vector and destination PCPU which are got 
from hypervisor. 

This mechanism only handle the normal IPI. For SIPI/NMI/INIT, still 
goes to legacy way but which write a new msr instead msr.icr.

The cost is reduced from 7k cycles to 2k cycles, which is 1500 cycles
on the host.

However it may increase the risk in the system since the guest could
decide to send IPI to any processor.

This patch is based on Linux-5.0 and we can rebase it on latest tree if the idea
is accepted. We will introduce this idea at KVM Forum 2020.

Signed-off-by: dengqiao.joey <dengqiao.joey@bytedance.com>
Signed-off-by: Yang Zhang <yang.zhang.wz@gmail.com>
---
 arch/x86/include/asm/kvm_host.h      |  28 ++++-
 arch/x86/include/asm/kvm_para.h      |   6 ++
 arch/x86/include/asm/vmx.h           |   1 +
 arch/x86/include/uapi/asm/kvm_para.h |  25 +++++
 arch/x86/kernel/apic/apic.c          |   1 +
 arch/x86/kernel/kvm.c                | 199 ++++++++++++++++++++++++++++++++++-
 arch/x86/kvm/cpuid.c                 |  15 ++-
 arch/x86/kvm/lapic.c                 |  12 +++
 arch/x86/kvm/lapic.h                 |   9 ++
 arch/x86/kvm/svm.c                   |   6 ++
 arch/x86/kvm/vmx/vmx.c               | 132 ++++++++++++++++++++---
 arch/x86/kvm/vmx/vmx.h               |   8 +-
 arch/x86/kvm/x86.c                   |  19 ++++
 include/uapi/linux/kvm.h             |   1 +
 14 files changed, 434 insertions(+), 28 deletions(-)

--
2.11.0

```
