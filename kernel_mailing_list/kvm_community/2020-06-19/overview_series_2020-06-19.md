#### [kvm-unit-test PATCH 1/2] Revert "access: disable phys-bits=36 for now"
##### From: Mohammed Gamal <mgamal@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Mohammed Gamal <mgamal@redhat.com>
X-Patchwork-Id: 11614435
Return-Path: <SRS0=UAw1=AA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DE85813A0
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 19 Jun 2020 15:44:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C648C2158C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 19 Jun 2020 15:44:35 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="apCpC7bd"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2405011AbgFSPoe (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 19 Jun 2020 11:44:34 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:29821 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S2404502AbgFSPod (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 19 Jun 2020 11:44:33 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1592581472;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=vjSxq7yztb/JRLpgt28mDLuXnBEGCZxUJIt/QDoQYsc=;
        b=apCpC7bd9zqYqGBqRAoZxbpqPyUIZ+Z73t6nbP8MlQgGY9+TdyWmpAxo0y84Ct3TOzCh4+
        laZhCY8B3j1rJexdWmKEEy81h/AgqXbqOoeMGDLue444b/j43oAPTGthRDrE2DRVIi1xK9
        gWeMB3zILCVbCymVVSbcABFu4Qt28SQ=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-157-u_WJo5xBO-eDPwwAQHJopw-1; Fri, 19 Jun 2020 11:44:30 -0400
X-MC-Unique: u_WJo5xBO-eDPwwAQHJopw-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 396E581EDDB;
        Fri, 19 Jun 2020 15:43:11 +0000 (UTC)
Received: from localhost.localdomain.com (ovpn-112-254.ams2.redhat.com
 [10.36.112.254])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 4CFB160BF4;
        Fri, 19 Jun 2020 15:43:09 +0000 (UTC)
From: Mohammed Gamal <mgamal@redhat.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com
Cc: vkuznets@redhat.com, sean.j.christopherson@intel.com,
        wanpengli@tencent.com, jmattson@google.com, joro@8bytes.org,
        Mohammed Gamal <mgamal@redhat.com>
Subject: [kvm-unit-test PATCH 1/2] Revert "access: disable phys-bits=36 for
 now"
Date: Fri, 19 Jun 2020 17:42:55 +0200
Message-Id: <20200619154256.79216-2-mgamal@redhat.com>
In-Reply-To: <20200619154256.79216-1-mgamal@redhat.com>
References: <20200619154256.79216-1-mgamal@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This reverts commit 71de9c93fbdb15978ffa2f290dd120d3005a9292.

Now that guest_maxphyaddr < host_maxphyaddr patches are sent.
Revert this change in kvm-unit-test

Signed-off-by: Mohammed Gamal <mgamal@redhat.com>
---
 x86/unittests.cfg | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH 1/4] KVM: Documentation minor fixups
##### From: Andrew Jones <drjones@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11614931
Return-Path: <SRS0=UAw1=AA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 91B4C14DD
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 19 Jun 2020 18:46:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6EFC721531
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 19 Jun 2020 18:46:40 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="NnsZGKvw"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388231AbgFSSqj (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 19 Jun 2020 14:46:39 -0400
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:57475 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1731358AbgFSSqi (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 19 Jun 2020 14:46:38 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1592592397;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=uQl6Bsxc7SVXJaJ585YknvsUaymV8f0R9mIn/btW8+M=;
        b=NnsZGKvwvemaBqKGZYiuap1v1vX7gn8Gj4t77RLikrYRscERjtmHRIxKhGK/PVDksSLGNc
        hlHZkPWXi7iNd1BqM+SQ9cjCauf+MlHanEPZUTLB4DAmkDQM7/6UAHiRfWmyDP+/YZu53O
        aXQqECWnUIEpCyocatLjng77yHOwRg0=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-505-O1iWbGyQNDmjbjjmCAYc-Q-1; Fri, 19 Jun 2020 14:46:35 -0400
X-MC-Unique: O1iWbGyQNDmjbjjmCAYc-Q-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id AC3951052508;
        Fri, 19 Jun 2020 18:46:34 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.40.194.110])
        by smtp.corp.redhat.com (Postfix) with ESMTP id E601960BF4;
        Fri, 19 Jun 2020 18:46:32 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu
Cc: pbonzini@redhat.com, maz@kernel.org, steven.price@arm.com
Subject: [PATCH 1/4] KVM: Documentation minor fixups
Date: Fri, 19 Jun 2020 20:46:26 +0200
Message-Id: <20200619184629.58653-2-drjones@redhat.com>
In-Reply-To: <20200619184629.58653-1-drjones@redhat.com>
References: <20200619184629.58653-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Signed-off-by: Andrew Jones <drjones@redhat.com>
---
 Documentation/virt/kvm/api.rst | 9 +++++----
 1 file changed, 5 insertions(+), 4 deletions(-)

```
#### [RFC PATCH v13 1/9] arm64: Probe for the presence of KVM hypervisor services during boot
##### From: Jianyong Wu <jianyong.wu@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jianyong Wu <jianyong.wu@arm.com>
X-Patchwork-Id: 11613571
Return-Path: <SRS0=UAw1=AA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6B8F414DD
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 19 Jun 2020 09:31:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 58B902073E
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 19 Jun 2020 09:31:10 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731398AbgFSJbA (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 19 Jun 2020 05:31:00 -0400
Received: from foss.arm.com ([217.140.110.172]:49116 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1731364AbgFSJa4 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 19 Jun 2020 05:30:56 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 6C2B8101E;
        Fri, 19 Jun 2020 02:30:55 -0700 (PDT)
Received: from entos-d05.shanghai.arm.com (entos-d05.shanghai.arm.com
 [10.169.40.35])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPA id
 3F26F3F71F;
        Fri, 19 Jun 2020 02:30:49 -0700 (PDT)
From: Jianyong Wu <jianyong.wu@arm.com>
To: netdev@vger.kernel.org, yangbo.lu@nxp.com, john.stultz@linaro.org,
        tglx@linutronix.de, pbonzini@redhat.com,
        sean.j.christopherson@intel.com, maz@kernel.org,
        richardcochran@gmail.com, Mark.Rutland@arm.com, will@kernel.org,
        suzuki.poulose@arm.com, steven.price@arm.com
Cc: linux-kernel@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        Steve.Capper@arm.com, Kaly.Xin@arm.com, justin.he@arm.com,
        Wei.Chen@arm.com, jianyong.wu@arm.com, nd@arm.com
Subject: [RFC PATCH v13 1/9] arm64: Probe for the presence of KVM hypervisor
 services during boot
Date: Fri, 19 Jun 2020 17:30:25 +0800
Message-Id: <20200619093033.58344-2-jianyong.wu@arm.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200619093033.58344-1-jianyong.wu@arm.com>
References: <20200619093033.58344-1-jianyong.wu@arm.com>
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
#### [PATCH v13 1/9] arm64: Probe for the presence of KVM hypervisor services during boot
##### From: Jianyong Wu <jianyong.wu@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jianyong Wu <jianyong.wu@arm.com>
X-Patchwork-Id: 11614149
Return-Path: <SRS0=UAw1=AA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E9CD114B7
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 19 Jun 2020 13:02:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DBEA921527
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 19 Jun 2020 13:02:06 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732720AbgFSNBu (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 19 Jun 2020 09:01:50 -0400
Received: from foss.arm.com ([217.140.110.172]:57376 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728606AbgFSNBr (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 19 Jun 2020 09:01:47 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 6896E11B3;
        Fri, 19 Jun 2020 06:01:46 -0700 (PDT)
Received: from entos-d05.shanghai.arm.com (entos-d05.shanghai.arm.com
 [10.169.40.35])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPA id
 39AF33F6CF;
        Fri, 19 Jun 2020 06:01:39 -0700 (PDT)
From: Jianyong Wu <jianyong.wu@arm.com>
To: netdev@vger.kernel.org, yangbo.lu@nxp.com, john.stultz@linaro.org,
        tglx@linutronix.de, pbonzini@redhat.com,
        sean.j.christopherson@intel.com, maz@kernel.org,
        richardcochran@gmail.com, Mark.Rutland@arm.com, will@kernel.org,
        suzuki.poulose@arm.com, steven.price@arm.com
Cc: linux-kernel@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        Steve.Capper@arm.com, Kaly.Xin@arm.com, justin.he@arm.com,
        Wei.Chen@arm.com, jianyong.wu@arm.com, nd@arm.com
Subject: [PATCH v13 1/9] arm64: Probe for the presence of KVM hypervisor
 services during boot
Date: Fri, 19 Jun 2020 21:01:12 +0800
Message-Id: <20200619130120.40556-2-jianyong.wu@arm.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200619130120.40556-1-jianyong.wu@arm.com>
References: <20200619130120.40556-1-jianyong.wu@arm.com>
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
#### [PATCH v3 1/9] host trust limitation: Introduce new host trust limitation interface
##### From: David Gibson <david@gibson.dropbear.id.au>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Gibson <david@gibson.dropbear.id.au>
X-Patchwork-Id: 11613109
Return-Path: <SRS0=UAw1=AA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0F3CB13A0
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 19 Jun 2020 02:06:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id EB53F20773
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 19 Jun 2020 02:06:13 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=gibson.dropbear.id.au
 header.i=@gibson.dropbear.id.au header.b="nJSanPg8"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727915AbgFSCGM (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 18 Jun 2020 22:06:12 -0400
Received: from bilbo.ozlabs.org ([203.11.71.1]:36545 "EHLO ozlabs.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727911AbgFSCGK (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 18 Jun 2020 22:06:10 -0400
Received: by ozlabs.org (Postfix, from userid 1007)
        id 49p2GS1dYgz9sNR; Fri, 19 Jun 2020 12:06:08 +1000 (AEST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple;
        d=gibson.dropbear.id.au; s=201602; t=1592532368;
        bh=gLWD9Joj8IIB/tTWGt6QwLtKruFK1pcFHrhx6E7+hAA=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=nJSanPg8NeKsUcm7P+zX/JVyECFc0xANus0zN7ZXcMfswdMa7g4E9Y+wA81Bpfj3y
         +KrsONmNKbqxLTMakO/mYVlUf+9y/pUO96TnOtTv140aKrE7ioEdjqWS8fUOPnj4rj
         AAWfHyWIaUknWsxeYZWj/0V9n9jwPbvL5JTJx9BI=
From: David Gibson <david@gibson.dropbear.id.au>
To: qemu-devel@nongnu.org, brijesh.singh@amd.com, pair@us.ibm.com,
        pbonzini@redhat.com, dgilbert@redhat.com, frankja@linux.ibm.com
Cc: Marcel Apfelbaum <marcel.apfelbaum@gmail.com>, kvm@vger.kernel.org,
        qemu-ppc@nongnu.org, mst@redhat.com, mdroth@linux.vnet.ibm.com,
        Richard Henderson <rth@twiddle.net>, cohuck@redhat.com,
        pasic@linux.ibm.com, Eduardo Habkost <ehabkost@redhat.com>,
        David Gibson <david@gibson.dropbear.id.au>,
        qemu-s390x@nongnu.org, david@redhat.com
Subject: [PATCH v3 1/9] host trust limitation: Introduce new host trust
 limitation interface
Date: Fri, 19 Jun 2020 12:05:54 +1000
Message-Id: <20200619020602.118306-2-david@gibson.dropbear.id.au>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20200619020602.118306-1-david@gibson.dropbear.id.au>
References: <20200619020602.118306-1-david@gibson.dropbear.id.au>
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
---
 backends/Makefile.objs               |  2 ++
 backends/host-trust-limitation.c     | 29 ++++++++++++++++++++++++
 include/exec/host-trust-limitation.h | 33 ++++++++++++++++++++++++++++
 include/qemu/typedefs.h              |  1 +
 4 files changed, 65 insertions(+)
 create mode 100644 backends/host-trust-limitation.c
 create mode 100644 include/exec/host-trust-limitation.h

```
#### [PATCH v2 01/11] KVM: x86: Add helper functions for illegal GPA checking and page fault injection
##### From: Mohammed Gamal <mgamal@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Mohammed Gamal <mgamal@redhat.com>
X-Patchwork-Id: 11614401
Return-Path: <SRS0=UAw1=AA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1E6A013A0
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 19 Jun 2020 15:39:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0698120786
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 19 Jun 2020 15:39:54 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="XOl8h9lp"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2393768AbgFSPjx (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 19 Jun 2020 11:39:53 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:47234 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S2393602AbgFSPjv (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 19 Jun 2020 11:39:51 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1592581190;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=b5JoAyE8A6/raa81T7z4O+0wQ9DFK5kTLDmKpjBV3xE=;
        b=XOl8h9lpiWRrHgT16qsUPBUoF2DKUEERxYdCuPlZCf40vAd4CvKXMypxHamj+UXp4mY1/i
        29keKr5nfIHQKOTViVIPR3Xi6EgTfGO010yCiQ2M4A+9cGssbGxSJ9O+I0Xyt3oUXtQLlv
        Iu/X/0ZoFjgUVRpJ8Tx+3Qoijctw21w=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-287-486lxakvOICJrW_7MYVevQ-1; Fri, 19 Jun 2020 11:39:46 -0400
X-MC-Unique: 486lxakvOICJrW_7MYVevQ-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 274F31054FB3;
        Fri, 19 Jun 2020 15:39:37 +0000 (UTC)
Received: from localhost.localdomain.com (ovpn-112-254.ams2.redhat.com
 [10.36.112.254])
        by smtp.corp.redhat.com (Postfix) with ESMTP id C6E5B60BF4;
        Fri, 19 Jun 2020 15:39:34 +0000 (UTC)
From: Mohammed Gamal <mgamal@redhat.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com
Cc: linux-kernel@vger.kernel.org, vkuznets@redhat.com,
        sean.j.christopherson@intel.com, wanpengli@tencent.com,
        jmattson@google.com, joro@8bytes.org, thomas.lendacky@amd.com,
        babu.moger@amd.com, Mohammed Gamal <mgamal@redhat.com>
Subject: [PATCH v2 01/11] KVM: x86: Add helper functions for illegal GPA
 checking and page fault injection
Date: Fri, 19 Jun 2020 17:39:15 +0200
Message-Id: <20200619153925.79106-2-mgamal@redhat.com>
In-Reply-To: <20200619153925.79106-1-mgamal@redhat.com>
References: <20200619153925.79106-1-mgamal@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch adds two helper functions that will be used to support virtualizing
MAXPHYADDR in both kvm-intel.ko and kvm.ko.

kvm_fixup_and_inject_pf_error() injects a page fault for a user-specified GVA,
while kvm_mmu_is_illegal_gpa() checks whether a GPA exceeds vCPU address limits.

Signed-off-by: Mohammed Gamal <mgamal@redhat.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/mmu.h |  6 ++++++
 arch/x86/kvm/x86.c | 21 +++++++++++++++++++++
 arch/x86/kvm/x86.h |  1 +
 3 files changed, 28 insertions(+)

```
#### [kvm-unit-tests PATCH] x86: pmu: fix failures on 32-bit due to wrong masks
##### From: Nadav Amit <namit@vmware.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Nadav Amit <namit@vmware.com>
X-Patchwork-Id: 11614965
Return-Path: <SRS0=UAw1=AA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B11FC618
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 19 Jun 2020 19:41:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A3FA1206C3
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 19 Jun 2020 19:41:27 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2389877AbgFSTl0 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 19 Jun 2020 15:41:26 -0400
Received: from ex13-edg-ou-001.vmware.com ([208.91.0.189]:5542 "EHLO
        EX13-EDG-OU-001.vmware.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S2389853AbgFSTl0 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 19 Jun 2020 15:41:26 -0400
Received: from sc9-mailhost2.vmware.com (10.113.161.72) by
 EX13-EDG-OU-001.vmware.com (10.113.208.155) with Microsoft SMTP Server id
 15.0.1156.6; Fri, 19 Jun 2020 12:41:24 -0700
Received: from sc2-haas01-esx0118.eng.vmware.com
 (sc2-haas01-esx0118.eng.vmware.com [10.172.44.118])
        by sc9-mailhost2.vmware.com (Postfix) with ESMTP id 87C56B29F4;
        Fri, 19 Jun 2020 15:41:25 -0400 (EDT)
From: Nadav Amit <namit@vmware.com>
To: Paolo Bonzini <pbonzini@redhat.com>
CC: <kvm@vger.kernel.org>, Nadav Amit <namit@vmware.com>
Subject: [kvm-unit-tests PATCH] x86: pmu: fix failures on 32-bit due to wrong
 masks
Date: Fri, 19 Jun 2020 12:39:09 -0700
Message-ID: <20200619193909.18949-1-namit@vmware.com>
X-Mailer: git-send-email 2.17.1
MIME-Version: 1.0
Received-SPF: None (EX13-EDG-OU-001.vmware.com: namit@vmware.com does not
 designate permitted sender hosts)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Some mask computation are using long constants instead of long long
constants, which causes test failures on x86-32.

Signed-off-by: Nadav Amit <namit@vmware.com>
---
 x86/pmu.c | 8 ++++----
 1 file changed, 4 insertions(+), 4 deletions(-)

```
#### [PATCH 1/2] kvm: Add support for KVM_CAP_HAS_SMALLER_MAXPHYADDR
##### From: Mohammed Gamal <mgamal@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Mohammed Gamal <mgamal@redhat.com>
X-Patchwork-Id: 11614455
Return-Path: <SRS0=UAw1=AA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9AF71912
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 19 Jun 2020 15:54:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 82E5421532
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 19 Jun 2020 15:54:22 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="cwVR6aAS"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2392907AbgFSPyV (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 19 Jun 2020 11:54:21 -0400
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:48818 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S2392500AbgFSPyI (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 19 Jun 2020 11:54:08 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1592582047;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=ONVIMPFVgNlQCWartogeNcXUxw3XoJkJEtWznEeVhjk=;
        b=cwVR6aAS83hOC250xFLAk6Ur1omjydrJLzAGSKkQwnmJDgC5uYEjfubVJ7RuJUmJ2qiStM
        m30VuD+JnNKXTxhJleNTsclSnz0SVY7a0aslzWTA7rWratdvB952DvXhT6Dh+tIEvXm5lg
        Ndi4ETgvVY8o0GmAq7B8YICYUZyTFyY=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-232-an-RjqUnOU2a1z51WD2Ghw-1; Fri, 19 Jun 2020 11:54:03 -0400
X-MC-Unique: an-RjqUnOU2a1z51WD2Ghw-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 79C6C18C6EEA;
        Fri, 19 Jun 2020 15:53:54 +0000 (UTC)
Received: from localhost.localdomain.com (ovpn-112-254.ams2.redhat.com
 [10.36.112.254])
        by smtp.corp.redhat.com (Postfix) with ESMTP id A1DD95BAD3;
        Fri, 19 Jun 2020 15:53:52 +0000 (UTC)
From: Mohammed Gamal <mgamal@redhat.com>
To: qemu-devel@nongnu.org, pbonzini@redhat.com
Cc: ehabkost@redhat.com, mtosatti@redhat.com, rth@twiddle.net,
        kvm@vger.kernel.org, Mohammed Gamal <mgamal@redhat.com>
Subject: [PATCH 1/2] kvm: Add support for KVM_CAP_HAS_SMALLER_MAXPHYADDR
Date: Fri, 19 Jun 2020 17:53:43 +0200
Message-Id: <20200619155344.79579-2-mgamal@redhat.com>
In-Reply-To: <20200619155344.79579-1-mgamal@redhat.com>
References: <20200619155344.79579-1-mgamal@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This adds the KVM_CAP_HAS_SMALLER_MAXPHYADDR capability
and a helper function to check for this capability.
This will allow QEMU to decide to what to do if the host
CPU can't handle GUEST_MAXPHYADDR < HOST_MAXPHYADDR properly.

Signed-off-by: Mohammed Gamal <mgamal@redhat.com>
---
 linux-headers/linux/kvm.h | 1 +
 target/i386/kvm.c         | 5 +++++
 target/i386/kvm_i386.h    | 1 +
 3 files changed, 7 insertions(+)

```
#### [PATCH v7 34/36] samples: vfio-mdev/mbochs: fix common struct sg_table related issues
##### From: Marek Szyprowski <m.szyprowski@samsung.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marek Szyprowski <m.szyprowski@samsung.com>
X-Patchwork-Id: 11613845
Return-Path: <SRS0=UAw1=AA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 19CFD138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 19 Jun 2020 10:41:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id F178721548
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 19 Jun 2020 10:41:44 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=samsung.com header.i=@samsung.com
 header.b="atfLKskR"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732635AbgFSKl0 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 19 Jun 2020 06:41:26 -0400
Received: from mailout2.w1.samsung.com ([210.118.77.12]:52401 "EHLO
        mailout2.w1.samsung.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1732644AbgFSKjU (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 19 Jun 2020 06:39:20 -0400
Received: from eucas1p2.samsung.com (unknown [182.198.249.207])
        by mailout2.w1.samsung.com (KnoxPortal) with ESMTP id
 20200619103717euoutp02710797021ff2de461f5882aca23e15d3~Z66Udwt-p2372823728euoutp02q
        for <kvm@vger.kernel.org>; Fri, 19 Jun 2020 10:37:17 +0000 (GMT)
DKIM-Filter: OpenDKIM Filter v2.11.0 mailout2.w1.samsung.com
 20200619103717euoutp02710797021ff2de461f5882aca23e15d3~Z66Udwt-p2372823728euoutp02q
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=samsung.com;
        s=mail20170921; t=1592563037;
        bh=i9tfBl9XK1ZIcmVNmOj760Z4Av4MmZkmEeWSykU107Y=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=atfLKskRDXY9/BVWa8nrWCkqrLlOqNmWkrUN380u7/G1/IYRQ2SquJHlNGdC3pF5u
         yEE7x9K8spZAsjX9UIpMCJy6Mi6EkPN8oqx9oitCGUc7+PXCSenvehDRwWZUpHo+yd
         X4xLDQONvYxHAvDN2Gej1UHl060j28cVKHpr90eU=
Received: from eusmges2new.samsung.com (unknown [203.254.199.244]) by
        eucas1p1.samsung.com (KnoxPortal) with ESMTP id
        20200619103717eucas1p1eea0e1812066354b4495c584c9e55e05~Z66UJdHfh0708007080eucas1p1G;
        Fri, 19 Jun 2020 10:37:17 +0000 (GMT)
Received: from eucas1p2.samsung.com ( [182.198.249.207]) by
        eusmges2new.samsung.com (EUCPMTA) with SMTP id 01.AD.05997.D559CEE5;
 Fri, 19
        Jun 2020 11:37:17 +0100 (BST)
Received: from eusmtrp1.samsung.com (unknown [182.198.249.138]) by
        eucas1p2.samsung.com (KnoxPortal) with ESMTPA id
        20200619103716eucas1p28d6da172346acf044d3c1f213d9543ef~Z66TruWMo3081930819eucas1p2x;
        Fri, 19 Jun 2020 10:37:16 +0000 (GMT)
Received: from eusmgms2.samsung.com (unknown [182.198.249.180]) by
        eusmtrp1.samsung.com (KnoxPortal) with ESMTP id
        20200619103716eusmtrp15280a537011684db0a31a468099f5dbe~Z66TrF-eS1007310073eusmtrp1J;
        Fri, 19 Jun 2020 10:37:16 +0000 (GMT)
X-AuditID: cbfec7f4-677ff7000000176d-14-5eec955dc01a
Received: from eusmtip2.samsung.com ( [203.254.199.222]) by
        eusmgms2.samsung.com (EUCPMTA) with SMTP id AA.1B.06017.C559CEE5;
 Fri, 19
        Jun 2020 11:37:16 +0100 (BST)
Received: from AMDC2765.digital.local (unknown [106.120.51.73]) by
        eusmtip2.samsung.com (KnoxPortal) with ESMTPA id
        20200619103716eusmtip29553eb2a23be38cf52b095dd61d865f0~Z66TEv0qL0229502295eusmtip2n;
        Fri, 19 Jun 2020 10:37:16 +0000 (GMT)
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
Subject: [PATCH v7 34/36] samples: vfio-mdev/mbochs: fix common struct
 sg_table related issues
Date: Fri, 19 Jun 2020 12:36:34 +0200
Message-Id: <20200619103636.11974-35-m.szyprowski@samsung.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200619103636.11974-1-m.szyprowski@samsung.com>
X-Brightmail-Tracker: 
 H4sIAAAAAAAAA0WSWUwTURiFvZ3OdFhqhoLhCiimCgaTsqjRSVAE9GFI1PjAiyYgBSZAhAIt
        qw+KgCC7yNYgAhoMS9klhZQIdMQWbKhGluAWIRBFsIiCREDAlgF8O//3nz/n3OTiiKADtcMj
        JHG0VCKOFGLmXKVm5bUooOR7oHt/NULm6Qc5ZJu8BSU3lYUIOfL7B0bWK15yyOpeT7KiJJbs
        0D0C5NLIJIdsnxpDyWFVBUY29X/ikeqFadSbTzVWNgLq+XI1l+pcnkCpzzlaDvWs5jb1YWMK
        oYrGawHV/S4Fo/LS5jEqv6MBUIvtB69YXDM/E0pHRiTQUjevIPPwNWU7L6bGKul9V3QKaNub
        DcxwSJyEAy8YNBuY4wKiDsD83pHtYQnA0o387WERQE13PW/nxJA6DdhFLYCpD19huycFWVnA
        5MIID5htyMZM2oa4C+BAnqXJhBBjHGhYn0dNC2siCNZkVm6ZuIQTXFFkICbNJ7wgs/mYy8Y5
        QkVr3xY3M/K5dDXKcoYHdX/2s/oClHcNI6y2hrPaju2qDlBXlMs1BUMiDcBJfROPHXIBHE6V
        A9blCT/qV40tcGM9F9iicmOxD1zRjHFMGBJ74bjByoQRo3ygLENYzIf3MgSs2xmWa5t3Y9Vv
        3m7XoeB6afrWEwVEIYDF+Xb3gWP5/6xqABqALR0viwqjZccldKKrTBwli5eEuYZER7UD41/S
        bWiXuoDqbzADCBwILfkz/nOBAlScIEuOYgDEEaEN33dIFyjgh4qTb9LS6OvS+EhaxgB7nCu0
        5Z948i1AQISJ4+gbNB1DS3e2HNzMLgUUfznVo5rpylmqUlxyX4/1qx8VHejzyZ2/eGs1qbnT
        /vSQH1oUkXnW2V90xJu5A/McDpk1BU+MqbudRxd6NurOJw7PyvVrSOtXrGCSCblaYTUkIiZm
        5quIRrlvkf4wfa6sX5J11Cld6+L51OEys+8X8XOwyb+NBzUWij2TnFwhVxYu9jiGSGXif6kI
        LLtHAwAA
X-Brightmail-Tracker: 
 H4sIAAAAAAAAA+NgFprGIsWRmVeSWpSXmKPExsVy+t/xe7oxU9/EGWxco2/Re+4kk8XGGetZ
        Lf5vm8hsceXrezaLlauPMlks2G9tMWdqocWW03MZLb5cechksenxNVaLy7vmsFmsPXKX3eLg
        hyesDrwea+atYfTY+20Bi8f2bw9YPe53H2fy2Lyk3uP2v8fMHpNvLGf02H2zgc2jt/kdm0ff
        llWMHp83yQVwR+nZFOWXlqQqZOQXl9gqRRtaGOkZWlroGZlY6hkam8daGZkq6dvZpKTmZJal
        FunbJehl/N62ib1giWDFrR35DYwb+boYOTkkBEwk3jY9Yexi5OIQEljKKPHx1VU2iISMxMlp
        DawQtrDEn2tdbBBFnxgl7s9dywySYBMwlOh6C5EQEehklJjW/ZEdJMEscI9JYu86PxBbWCBO
        ovvjXxYQm0VAVeLn6jawZl4BO4lD/xeyQGyQl1i94QBYnBMo/rrlINhmIQFbieUL3jNPYORb
        wMiwilEktbQ4Nz232EivODG3uDQvXS85P3cTIzBOth37uWUHY9e74EOMAhyMSjy8L0Jexwmx
        JpYVV+YeYpTgYFYS4XU6ezpOiDclsbIqtSg/vqg0J7X4EKMp0FETmaVEk/OBMZxXEm9oamhu
        YWlobmxubGahJM7bIXAwRkggPbEkNTs1tSC1CKaPiYNTqoFxTmLo16xbv99UpNy47P79hMR2
        th4ro2yrMJ1/17ety4lbaKehOM3mUVDIs5qaglOv68K8NzuFPMn+0CnnMl3+p0WUgePSf/+O
        f3lXdoxfIOXhibch3nsNrbo/P29st7k/TT6Hp/N7yl725N7zi9W4mp9M/nfms+Isbua7Cfrl
        8y+djNiXmymqxFKckWioxVxUnAgAn5sRn6kCAAA=
X-CMS-MailID: 20200619103716eucas1p28d6da172346acf044d3c1f213d9543ef
X-Msg-Generator: CA
X-RootMTR: 20200619103716eucas1p28d6da172346acf044d3c1f213d9543ef
X-EPHeader: CA
CMS-TYPE: 201P
X-CMS-RootMailID: 20200619103716eucas1p28d6da172346acf044d3c1f213d9543ef
References: <20200619103636.11974-1-m.szyprowski@samsung.com>
        <CGME20200619103716eucas1p28d6da172346acf044d3c1f213d9543ef@eucas1p2.samsung.com>
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
---
 samples/vfio-mdev/mbochs.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [PATCH RFC] Revert "KVM: VMX: Micro-optimize vmexit time when not exposing PMU"
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11613637
Return-Path: <SRS0=UAw1=AA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4F68C92A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 19 Jun 2020 09:42:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3A0FE214DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 19 Jun 2020 09:42:11 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="ESGagB1D"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732147AbgFSJmG (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 19 Jun 2020 05:42:06 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:54226 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1732121AbgFSJmD (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 19 Jun 2020 05:42:03 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1592559722;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=zPadoQCK/Zr9dBTIUqiEQCreoi9mBoOI8SaL3yX0d6k=;
        b=ESGagB1D/3k7fc6ZFBIVwjKWWqdft1VkmlO8D62YMQAj3aKYt2NZPZoxPFLF92zDnoKdJl
        pOn9LsvRuPm2dLGExbcuvijphCBAnpEjHcf059qaTzptU0rB5WxQEHtTXoFIDPRi4z8cK7
        ipRR8jh2llRSBUi223vJOYCNMo0uyAA=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-214-Sjz3vM05PgSz-fHbhIqSIQ-1; Fri, 19 Jun 2020 05:40:57 -0400
X-MC-Unique: Sjz3vM05PgSz-fHbhIqSIQ-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 272688035D7;
        Fri, 19 Jun 2020 09:40:56 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.194.248])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 726A971688;
        Fri, 19 Jun 2020 09:40:47 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>
Cc: Jim Mattson <jmattson@google.com>,
        Maxime Coquelin <maxime.coquelin@redhat.com>,
        linux-kernel@vger.kernel.org
Subject: [PATCH RFC] Revert "KVM: VMX: Micro-optimize vmexit time when not
 exposing PMU"
Date: Fri, 19 Jun 2020 11:40:46 +0200
Message-Id: <20200619094046.654019-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Guest crashes are observed on a Cascade Lake system when 'perf top' is
launched on the host, e.g.

 BUG: unable to handle kernel paging request at fffffe0000073038
 PGD 7ffa7067 P4D 7ffa7067 PUD 7ffa6067 PMD 7ffa5067 PTE ffffffffff120
 Oops: 0000 [#1] SMP PTI
 CPU: 1 PID: 1 Comm: systemd Not tainted 4.18.0+ #380
...
 Call Trace:
  serial8250_console_write+0xfe/0x1f0
  call_console_drivers.constprop.0+0x9d/0x120
  console_unlock+0x1ea/0x460

Call traces are different but the crash is imminent. The problem was
blindly bisected to the commit 041bc42ce2d0 ("KVM: VMX: Micro-optimize
vmexit time when not exposing PMU"). It was also confirmed that the
issue goes away if PMU is exposed to the guest.

With some instrumentation of the guest we can see what is being switched
(when we do atomic_switch_perf_msrs()):

 vmx_vcpu_run: switching 2 msrs
 vmx_vcpu_run: switching MSR38f guest: 70000000d host: 70000000f
 vmx_vcpu_run: switching MSR3f1 guest: 0 host: 2

The current guess is that PEBS (MSR_IA32_PEBS_ENABLE, 0x3f1) is to blame.
Regardless of whether PMU is exposed to the guest or not, PEBS needs to
be disabled upon switch.

This reverts commit 041bc42ce2d0efac3b85bbb81dea8c74b81f4ef9.

Reported-by: Maxime Coquelin <maxime.coquelin@redhat.com>
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
- Perf/KVM interractions are a mystery to me, thus RFC.
---
 arch/x86/kvm/vmx/vmx.c | 3 +--
 1 file changed, 1 insertion(+), 2 deletions(-)

```
#### [PATCH v2] target/arm: Check supported KVM features globally (not per vCPU)
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
 <philmd@redhat.com>
X-Patchwork-Id: 11613645
Return-Path: <SRS0=UAw1=AA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0A4DB618
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 19 Jun 2020 09:55:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E0572208DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 19 Jun 2020 09:55:55 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="d2upQC0x"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731636AbgFSJzy (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 19 Jun 2020 05:55:54 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:44930 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1729195AbgFSJzu (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 19 Jun 2020 05:55:50 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1592560548;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
  content-type:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=XfPfFaCxaa/T1kqInXIsZ3mZZB5WY2/ynXcN7FcGNnk=;
        b=d2upQC0xagk91yNR+clpcL3/EEUeWGj8Ym3ZAWsq6jVKo6e0TFKYyabQaRF9qOPMH5thT1
        GTFWLtc+VvXRFLCKl/yFtY4oP+K0b6PKWYfx/dB2efj87F7H8E1hEDsqzmSpo4L9reXbJy
        0v7QvibJfEnL+kOBkUvnkrT9rDQYLAI=
Received: from mail-wm1-f72.google.com (mail-wm1-f72.google.com
 [209.85.128.72]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-73-qbl4mRCxMeaGVW2KBofcDg-1; Fri, 19 Jun 2020 05:55:46 -0400
X-MC-Unique: qbl4mRCxMeaGVW2KBofcDg-1
Received: by mail-wm1-f72.google.com with SMTP id b63so3936031wme.1
        for <kvm@vger.kernel.org>; Fri, 19 Jun 2020 02:55:46 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=XfPfFaCxaa/T1kqInXIsZ3mZZB5WY2/ynXcN7FcGNnk=;
        b=nRArqMBEzyAfDGsRUV19Uq4vU+vdPO/PHmLpDs+Zw5QT6TlLu36swu7AqOxKG/TJlA
         i2wf/RCgKAjCQPz26NIntaVwQgaP2Ux1Bx7urNulfCmjGFC//HyY67W5M0QuI9NP7+IL
         mlDb22AiEF2nYvL7C1iV3wcCdO0GSnlFUouAiST5RhHKILZmohwLxRh6XpGR7j5QXv4I
         gv/D9gWQC5zNkWZIZz6VcRcjSuptTJP879mHMBSiRy3EhkfskpCUBgHOivxk8qu7x+tH
         lwZGVftGALQWONBLrNhRS5jRgCUQV0WKCEW3uBRhenY0PJuAkSOqEytgceC/uzwE/Lii
         TP0w==
X-Gm-Message-State: AOAM533YRBYjz+7ivpgQNbzvy7us0YdjtPyX9Ef6AUg2MaphKzJzVWhE
        hotD2vX9kMQfjYTzvnHbCulGehaDswMzTFHWYWX4RLt8+r2OQJOxZwEx1tO6bAYqMuOsqgrsGwO
        VQlOrELRoLhUY
X-Received: by 2002:a1c:9d09:: with SMTP id g9mr2805106wme.31.1592560545269;
        Fri, 19 Jun 2020 02:55:45 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJzato/vJMecQoKyx5I8aGz7ePiNZCR3cTLm0WhI5JTnkyfD6EkApXh8z9T03JUmFi+wLOSLsA==
X-Received: by 2002:a1c:9d09:: with SMTP id g9mr2805075wme.31.1592560544865;
        Fri, 19 Jun 2020 02:55:44 -0700 (PDT)
Received: from localhost.localdomain (93.red-83-59-160.dynamicip.rima-tde.net.
 [83.59.160.93])
        by smtp.gmail.com with ESMTPSA id
 h18sm6585676wru.7.2020.06.19.02.55.43
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 19 Jun 2020 02:55:44 -0700 (PDT)
From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>
To: qemu-devel@nongnu.org
Cc: kvm@vger.kernel.org, Peter Maydell <peter.maydell@linaro.org>,
 qemu-arm@nongnu.org, Andrew Jones <drjones@redhat.com>, =?utf-8?q?Philippe_?=
	=?utf-8?q?Mathieu-Daud=C3=A9?= <philmd@redhat.com>,
 Haibo Xu <haibo.xu@linaro.org>, Paolo Bonzini <pbonzini@redhat.com>,
 "Dr . David Alan Gilbert" <dgilbert@redhat.com>
Subject: [PATCH v2] target/arm: Check supported KVM features globally (not per
 vCPU)
Date: Fri, 19 Jun 2020 11:55:42 +0200
Message-Id: <20200619095542.2095-1-philmd@redhat.com>
X-Mailer: git-send-email 2.21.3
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Since commit d70c996df23f, when enabling the PMU we get:

  $ qemu-system-aarch64 -cpu host,pmu=on -M virt,accel=kvm,gic-version=3
  Segmentation fault (core dumped)

  Thread 1 "qemu-system-aar" received signal SIGSEGV, Segmentation fault.
  0x0000aaaaaae356d0 in kvm_ioctl (s=0x0, type=44547) at accel/kvm/kvm-all.c:2588
  2588        ret = ioctl(s->fd, type, arg);
  (gdb) bt
  #0  0x0000aaaaaae356d0 in kvm_ioctl (s=0x0, type=44547) at accel/kvm/kvm-all.c:2588
  #1  0x0000aaaaaae31568 in kvm_check_extension (s=0x0, extension=126) at accel/kvm/kvm-all.c:916
  #2  0x0000aaaaaafce254 in kvm_arm_pmu_supported (cpu=0xaaaaac214ab0) at target/arm/kvm.c:213
  #3  0x0000aaaaaafc0f94 in arm_set_pmu (obj=0xaaaaac214ab0, value=true, errp=0xffffffffe438) at target/arm/cpu.c:1111
  #4  0x0000aaaaab5533ac in property_set_bool (obj=0xaaaaac214ab0, v=0xaaaaac223a80, name=0xaaaaac11a970 "pmu", opaque=0xaaaaac222730, errp=0xffffffffe438) at qom/object.c:2170
  #5  0x0000aaaaab5512f0 in object_property_set (obj=0xaaaaac214ab0, v=0xaaaaac223a80, name=0xaaaaac11a970 "pmu", errp=0xffffffffe438) at qom/object.c:1328
  #6  0x0000aaaaab551e10 in object_property_parse (obj=0xaaaaac214ab0, string=0xaaaaac11b4c0 "on", name=0xaaaaac11a970 "pmu", errp=0xffffffffe438) at qom/object.c:1561
  #7  0x0000aaaaab54ee8c in object_apply_global_props (obj=0xaaaaac214ab0, props=0xaaaaac018e20, errp=0xaaaaabd6fd88 <error_fatal>) at qom/object.c:407
  #8  0x0000aaaaab1dd5a4 in qdev_prop_set_globals (dev=0xaaaaac214ab0) at hw/core/qdev-properties.c:1218
  #9  0x0000aaaaab1d9fac in device_post_init (obj=0xaaaaac214ab0) at hw/core/qdev.c:1050
  ...
  #15 0x0000aaaaab54f310 in object_initialize_with_type (obj=0xaaaaac214ab0, size=52208, type=0xaaaaabe237f0) at qom/object.c:512
  #16 0x0000aaaaab54fa24 in object_new_with_type (type=0xaaaaabe237f0) at qom/object.c:687
  #17 0x0000aaaaab54fa80 in object_new (typename=0xaaaaabe23970 "host-arm-cpu") at qom/object.c:702
  #18 0x0000aaaaaaf04a74 in machvirt_init (machine=0xaaaaac0a8550) at hw/arm/virt.c:1770
  #19 0x0000aaaaab1e8720 in machine_run_board_init (machine=0xaaaaac0a8550) at hw/core/machine.c:1138
  #20 0x0000aaaaaaf95394 in qemu_init (argc=5, argv=0xffffffffea58, envp=0xffffffffea88) at softmmu/vl.c:4348
  #21 0x0000aaaaaada3f74 in main (argc=<optimized out>, argv=<optimized out>, envp=<optimized out>) at softmmu/main.c:48

This is because in frame #2, cpu->kvm_state is still NULL
(the vCPU is not yet realized).

KVM has a hard requirement of all cores supporting the same
feature set. We only need to check if the accelerator supports
a feature, not each vCPU individually.

Fix by kvm_arm_<FEATURE>_supported() functions take a AccelState
argument (already realized/valid at this point) instead of a
CPUState argument.

Reported-by: Haibo Xu <haibo.xu@linaro.org>
Suggested-by: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Philippe Mathieu-Daudé <philmd@redhat.com>
Reviewed-by: Andrew Jones <drjones@redhat.com>
Signed-off-by: Andrew Jones <drjones@redhat.com>
---
v2: Use global kvm_state (bonzini)

Paolo, does this break migration of encrypted memory assumptions?

Cc: Dr. David Alan Gilbert <dgilbert@redhat.com>
Supersedes: <20200617130800.26355-1-philmd@redhat.com>
---
 target/arm/kvm_arm.h | 21 +++++++++------------
 target/arm/cpu.c     |  2 +-
 target/arm/cpu64.c   | 10 +++++-----
 target/arm/kvm.c     |  4 ++--
 target/arm/kvm64.c   | 14 +++++---------
 5 files changed, 22 insertions(+), 29 deletions(-)

```
#### [PATCH v2] vfio: Cleanup allowed driver namingFrom: Alex Williamson <alex.williamson@redhat.com>
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alex Williamson <alex.williamson@redhat.com>
X-Patchwork-Id: 11614575
Return-Path: <SRS0=UAw1=AA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 81DD890
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 19 Jun 2020 16:21:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 67763217BA
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 19 Jun 2020 16:21:28 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="f1BTs/NP"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2404741AbgFSQV0 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 19 Jun 2020 12:21:26 -0400
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:29133 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S2390662AbgFSPAu (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 19 Jun 2020 11:00:50 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1592578846;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=ZKQQ3TSN3kM3Cb8dTgCKmUaoa0Mo3XfrlHvCQ5ywFhw=;
        b=f1BTs/NPzetpirbEi3J7FSXEXl0YMZQxalxi79y8DuBQA6iaQ6euChvam0dEHSj0Q5wJZG
        Wt/dJqFNFsVL/iERWBIN8siBcNJpiWL+rRGbvVuJQxoqJe5Ii174ZWEVsZXNj31YDwrqVY
        NoXXWKkEaiPCoK2Rxs6Iu9/wurtU9zY=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-396-tYa_nW_TODO6rlo-ACXqqw-1; Fri, 19 Jun 2020 11:00:43 -0400
X-MC-Unique: tYa_nW_TODO6rlo-ACXqqw-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id A757F107ACF4;
        Fri, 19 Jun 2020 15:00:42 +0000 (UTC)
Received: from gimli.home (ovpn-112-195.phx2.redhat.com [10.3.112.195])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 63A695C1D0;
        Fri, 19 Jun 2020 15:00:39 +0000 (UTC)
Subject: [PATCH v2] vfio: Cleanup allowed driver naming
From: Alex Williamson <alex.williamson@redhat.com>
To: alex.williamson@redhat.com
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        cohuck@redhat.com
Date: Fri, 19 Jun 2020 09:00:39 -0600
Message-ID: <159257872055.20595.16949396190256140801.stgit@gimli.home>
User-Agent: StGit/0.19-dirty
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

No functional change, avoid non-inclusive naming schemes.

Signed-off-by: Alex Williamson <alex.williamson@redhat.com>
---

v2: Wrap vfio_dev_driver_allowed to 80 column for consistency,
    checkpatch no longer warns about this.

 drivers/vfio/vfio.c |   13 +++++++------
 1 file changed, 7 insertions(+), 6 deletions(-)

```
#### [RFC v9 01/11] vhost: option to fetch descriptors through an independent struct
##### From: =?utf-8?q?Eugenio_P=C3=A9rez?= <eperezma@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Eugenio Perez Martin <eperezma@redhat.com>
X-Patchwork-Id: 11614893
Return-Path: <SRS0=UAw1=AA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6AA55913
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 19 Jun 2020 18:23:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4721321531
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 19 Jun 2020 18:23:25 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="iWhOdqFy"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2392847AbgFSSXY (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 19 Jun 2020 14:23:24 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:57019 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1731031AbgFSSXU (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 19 Jun 2020 14:23:20 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1592590998;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=+CtPUIMGWcoYx3GArUVC0wAi/+1VQx1I1wXsVmTNvLE=;
        b=iWhOdqFy0h0HjqGpgEbRaGQlyghDmOxLWs4118QZJ8qPIR4jmyuFFeZ95Z37wevrVisJnh
        WkJOz111aNV50lZ5zd3qO+ENwlIvGkmL9iAbWSGNvf2LVpf2kGhCdxnEE2B3WgcsDCSV/y
        t/oQHIw5q8dcXni+kDOqZQMDX/kxJs8=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-425-U4G3TYIWMoqQwdFgwQ0Ivw-1; Fri, 19 Jun 2020 14:23:16 -0400
X-MC-Unique: U4G3TYIWMoqQwdFgwQ0Ivw-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 3AB27107ACCA;
        Fri, 19 Jun 2020 18:23:15 +0000 (UTC)
Received: from eperezma.remote.csb (ovpn-113-14.ams2.redhat.com
 [10.36.113.14])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 190487C1E2;
        Fri, 19 Jun 2020 18:23:12 +0000 (UTC)
From: =?utf-8?q?Eugenio_P=C3=A9rez?= <eperezma@redhat.com>
To: mst@redhat.com
Cc: kvm list <kvm@vger.kernel.org>,
        Stefano Garzarella <sgarzare@redhat.com>,
        virtualization@lists.linux-foundation.org,
        linux-kernel@vger.kernel.org, netdev@vger.kernel.org,
        Stefan Hajnoczi <stefanha@redhat.com>,
        Jason Wang <jasowang@redhat.com>
Subject: [RFC v9 01/11] vhost: option to fetch descriptors through an
 independent struct
Date: Fri, 19 Jun 2020 20:22:52 +0200
Message-Id: <20200619182302.850-2-eperezma@redhat.com>
In-Reply-To: <20200619182302.850-1-eperezma@redhat.com>
References: <20200619182302.850-1-eperezma@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: "Michael S. Tsirkin" <mst@redhat.com>

The idea is to support multiple ring formats by converting
to a format-independent array of descriptors.

This costs extra cycles, but we gain in ability
to fetch a batch of descriptors in one go, which
is good for code cache locality.

When used, this causes a minor performance degradation,
it's been kept as simple as possible for ease of review.
A follow-up patch gets us back the performance by adding batching.

To simplify benchmarking, I kept the old code around so one can switch
back and forth between old and new code. This will go away in the final
submission.

Signed-off-by: Michael S. Tsirkin <mst@redhat.com>
Signed-off-by: Eugenio Pérez <eperezma@redhat.com>
Link: https://lore.kernel.org/r/20200401183118.8334-2-eperezma@redhat.com
Signed-off-by: Michael S. Tsirkin <mst@redhat.com>
Signed-off-by: Eugenio Pérez <eperezma@redhat.com>
---
 drivers/vhost/vhost.c | 305 +++++++++++++++++++++++++++++++++++++++++-
 drivers/vhost/vhost.h |  16 +++
 2 files changed, 320 insertions(+), 1 deletion(-)

```
