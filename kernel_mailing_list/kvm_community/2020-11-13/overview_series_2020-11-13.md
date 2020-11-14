#### [PATCH kernel] vfio_pci_nvlink2: Do not attempt NPU2 setup on old P8's NPU
##### From: Alexey Kardashevskiy <aik@ozlabs.ru>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexey Kardashevskiy <aik@ozlabs.ru>
X-Patchwork-Id: 11902523
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id BEDBDC388F9
	for <kvm@archiver.kernel.org>; Fri, 13 Nov 2020 05:16:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7DA17206CA
	for <kvm@archiver.kernel.org>; Fri, 13 Nov 2020 05:16:19 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726104AbgKMFQS (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 13 Nov 2020 00:16:18 -0500
Received: from ozlabs.ru ([107.174.27.60]:54926 "EHLO ozlabs.ru"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726054AbgKMFQS (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 13 Nov 2020 00:16:18 -0500
X-Greylist: delayed 579 seconds by postgrey-1.27 at vger.kernel.org;
 Fri, 13 Nov 2020 00:16:18 EST
Received: from fstn1-p1.ozlabs.ibm.com (localhost [IPv6:::1])
        by ozlabs.ru (Postfix) with ESMTP id 67D7DAE80053;
        Fri, 13 Nov 2020 00:06:34 -0500 (EST)
From: Alexey Kardashevskiy <aik@ozlabs.ru>
To: linuxppc-dev@lists.ozlabs.org
Cc: Alexey Kardashevskiy <aik@ozlabs.ru>,
        David Gibson <david@gibson.dropbear.id.au>,
        kvm@vger.kernel.org, Alex Williamson <alex.williamson@redhat.com>
Subject: [PATCH kernel] vfio_pci_nvlink2: Do not attempt NPU2 setup on old
 P8's NPU
Date: Fri, 13 Nov 2020 16:06:32 +1100
Message-Id: <20201113050632.74124-1-aik@ozlabs.ru>
X-Mailer: git-send-email 2.17.1
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We execute certain NPU2 setup code (such as mapping an LPID to a device
in NPU2) unconditionally if an Nvlink bridge is detected. However this
cannot succeed on P8+ machines as the init helpers return an error other
than ENODEV which means the device is there is and setup failed so
vfio_pci_enable() fails and pass through is not possible.

This changes the two NPU2 related init helpers to return -ENODEV if
there is no "memory-region" device tree property as this is
the distinction between NPU and NPU2.

Fixes: 7f92891778df ("vfio_pci: Add NVIDIA GV100GL [Tesla V100 SXM2] subdriver")
Signed-off-by: Alexey Kardashevskiy <aik@ozlabs.ru>
---
 drivers/vfio/pci/vfio_pci_nvlink2.c | 7 +++++--
 1 file changed, 5 insertions(+), 2 deletions(-)

```
#### [PATCH 1/8] KVM: arm64: Add kvm_vcpu_has_pmu() helper
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11904449
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id EAE46C61DD8
	for <kvm@archiver.kernel.org>; Fri, 13 Nov 2020 18:26:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8C18E20759
	for <kvm@archiver.kernel.org>; Fri, 13 Nov 2020 18:26:19 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=kernel.org header.i=@kernel.org
 header.b="x9i4kYUk"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726291AbgKMS0S (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 13 Nov 2020 13:26:18 -0500
Received: from mail.kernel.org ([198.145.29.99]:59728 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726202AbgKMS0S (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 13 Nov 2020 13:26:18 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id BFB9D206F9;
        Fri, 13 Nov 2020 18:26:17 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1605291977;
        bh=9em7zCAFy/zAPxoJ9DJ79psVVW688qygNNSSZqu5SPE=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=x9i4kYUkJo2L9Aa+G1xFE/2x1IQcKTmHpOuzrQv1JHLPjXoOs3zl3tQkz/gvpsg4K
         DdTYOK4aFva0nA/L9jHOoEEBrBJCuJCt++FxmAVs2ftQOp+pUSvP8bzcArq4qPok8J
         ++4KLthb3M7HggB25v7ygKXaWm9KTuuCeFp8CFNg=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1kddm3-00APrY-Vo; Fri, 13 Nov 2020 18:26:16 +0000
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Eric Auger <eric.auger@redhat.com>, kernel-team@android.com
Subject: [PATCH 1/8] KVM: arm64: Add kvm_vcpu_has_pmu() helper
Date: Fri, 13 Nov 2020 18:25:55 +0000
Message-Id: <20201113182602.471776-2-maz@kernel.org>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20201113182602.471776-1-maz@kernel.org>
References: <20201113182602.471776-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com, eric.auger@redhat.com,
 kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

There are a number of places where we check for the KVM_ARM_VCPU_PMU_V3
feature. Wrap this check into a new kvm_vcpu_has_pmu(), and use
it at the existing locations.

No functional change.

Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 arch/arm64/include/asm/kvm_host.h | 3 +++
 arch/arm64/kvm/pmu-emul.c         | 8 +++-----
 2 files changed, 6 insertions(+), 5 deletions(-)

```
#### [PATCH kvm-unit-tests] x86: svm: clean up CR3 tests
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11903697
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-9.9 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A7DE1C388F7
	for <kvm@archiver.kernel.org>; Fri, 13 Nov 2020 14:39:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 63F1C20659
	for <kvm@archiver.kernel.org>; Fri, 13 Nov 2020 14:39:46 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="MRkGO6+o"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726587AbgKMOjp (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 13 Nov 2020 09:39:45 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:33837 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726324AbgKMOjp (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 13 Nov 2020 09:39:45 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1605278383;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=2hSIc4NCwTfXqPZCANFvroqBUVVU/829trViCkGb+q8=;
        b=MRkGO6+oPuzfqyTelONQmMPs8VLRcxOgxK8jIECifnWZ2r/PRWFYmj/GAqWgt7NLJ+iODd
        wxdZpiqH0F3/DTD5iBrmJu7pvZwHTFpYwnB3qmyIIQ/KnvtYycpXWuiObmMHaCks/UGg+z
        Q+JVxX5qIM3hr5GH9fda3WudZNCWG8I=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-81-5k4SgpMwM1mmUUke_j-e8w-1; Fri, 13 Nov 2020 09:39:41 -0500
X-MC-Unique: 5k4SgpMwM1mmUUke_j-e8w-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 759FB1030988
        for <kvm@vger.kernel.org>; Fri, 13 Nov 2020 14:39:39 +0000 (UTC)
Received: from virtlab511.virt.lab.eng.bos.redhat.com
 (virtlab511.virt.lab.eng.bos.redhat.com [10.19.152.198])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 3643460C11
        for <kvm@vger.kernel.org>; Fri, 13 Nov 2020 14:39:39 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: kvm@vger.kernel.org
Subject: [PATCH kvm-unit-tests] x86: svm: clean up CR3 tests
Date: Fri, 13 Nov 2020 09:39:38 -0500
Message-Id: <20201113143938.1050040-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Do not execute the same test repeatedly, and run PCIDE=0 test
even if the PCID bit is set in CPUID.  Note which CR4 configuration
is in use for each test.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 x86/svm_tests.c | 41 +++++++++++++++++------------------------
 1 file changed, 17 insertions(+), 24 deletions(-)

```
#### [PATCH 2/8] KVM: arm64: Set ID_AA64DFR0_EL1.PMUVer to 0 when no PMU support
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11904455
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 84B00C63699
	for <kvm@archiver.kernel.org>; Fri, 13 Nov 2020 18:26:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3926E206FB
	for <kvm@archiver.kernel.org>; Fri, 13 Nov 2020 18:26:20 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=kernel.org header.i=@kernel.org
 header.b="riZ/QyU+"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726203AbgKMS0T (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 13 Nov 2020 13:26:19 -0500
Received: from mail.kernel.org ([198.145.29.99]:59756 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726233AbgKMS0S (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 13 Nov 2020 13:26:18 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 4A10D2074B;
        Fri, 13 Nov 2020 18:26:18 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1605291978;
        bh=yeLt3nqD1e41ZnMR7XCTopnao0wO6yUaD1zjpERGPFg=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=riZ/QyU++0GCZfImskdEDD1g5xZEAsgyBKPpbHX8INDflaVbu4TWHBkJGT8wFQrcS
         OKHFi1pIO+TS1YAlfDlPmVV6Cxqs4ZMX4xaSrjHcODLaBMBwr5E33vjp10Py2Aachn
         lUId5tI+2N6O8se/g9z90oT0DVT+48ALpzd+MIDM=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1kddm4-00APrY-Gt; Fri, 13 Nov 2020 18:26:16 +0000
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Eric Auger <eric.auger@redhat.com>, kernel-team@android.com
Subject: [PATCH 2/8] KVM: arm64: Set ID_AA64DFR0_EL1.PMUVer to 0 when no PMU
 support
Date: Fri, 13 Nov 2020 18:25:56 +0000
Message-Id: <20201113182602.471776-3-maz@kernel.org>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20201113182602.471776-1-maz@kernel.org>
References: <20201113182602.471776-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com, eric.auger@redhat.com,
 kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We always expose the HW view of PMU in ID_AA64FDR0_EL1.PMUver,
even when the PMU feature is disabled, while the architecture
says that FEAT_PMUv3 not being implemented should result in this
field being zero.

Let's follow the architecture's guidance.

Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 arch/arm64/kvm/sys_regs.c | 7 ++++++-
 1 file changed, 6 insertions(+), 1 deletion(-)

```
#### [PATCH 7/8] KVM: arm64: Gate kvm_pmu_update_state() on the PMU feature
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11904457
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 2023BC63798
	for <kvm@archiver.kernel.org>; Fri, 13 Nov 2020 18:26:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BE2AA2074B
	for <kvm@archiver.kernel.org>; Fri, 13 Nov 2020 18:26:26 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=kernel.org header.i=@kernel.org
 header.b="qyKSf+mo"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726525AbgKMS0Y (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 13 Nov 2020 13:26:24 -0500
Received: from mail.kernel.org ([198.145.29.99]:59954 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726544AbgKMS0V (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 13 Nov 2020 13:26:21 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id B273B20759;
        Fri, 13 Nov 2020 18:26:20 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1605291980;
        bh=gY/VRsiPzRuoQjrUpaFkSuVWs50kFr+mHGg8iLcn3xs=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=qyKSf+moAYGtWWDjfKeEo01OP2lMgRMqd2zIk6o456bvQfCX/WSbUERqz+SMN47/D
         RlSSOh0yn1eghW3QeAKqezJufFDz3k8jBmmkRUBJHLj5hMi1Binku54KLIXI+P4mmB
         2Fp56zja5vdZ7cduoj88ICsT8ignDc3S1F//WnEM=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1kddm6-00APrY-Uk; Fri, 13 Nov 2020 18:26:19 +0000
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Eric Auger <eric.auger@redhat.com>, kernel-team@android.com
Subject: [PATCH 7/8] KVM: arm64: Gate kvm_pmu_update_state() on the PMU
 feature
Date: Fri, 13 Nov 2020 18:26:01 +0000
Message-Id: <20201113182602.471776-8-maz@kernel.org>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20201113182602.471776-1-maz@kernel.org>
References: <20201113182602.471776-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com, eric.auger@redhat.com,
 kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We currently gate the update of the PMU state on the PMU being "ready".
The "ready" state is only set to true when the first vcpu run is
successful, and if it isn't, we never reach the update code.

So the "ready" state is never the right thing to check for, and it
should instead be the presence of the PMU feature, which makes
a bit more sense.

Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 arch/arm64/kvm/pmu-emul.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH 2/4] MIPS: kvm: Use vm_get_page_prot to get protection bits
##### From: Thomas Bogendoerfer <tsbogend@alpha.franken.de>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Bogendoerfer <tsbogend@alpha.franken.de>
X-Patchwork-Id: 11903063
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 09A09C56202
	for <kvm@archiver.kernel.org>; Fri, 13 Nov 2020 11:13:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BB8F0207DE
	for <kvm@archiver.kernel.org>; Fri, 13 Nov 2020 11:13:56 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726569AbgKMLNe (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 13 Nov 2020 06:13:34 -0500
Received: from mx2.suse.de ([195.135.220.15]:33016 "EHLO mx2.suse.de"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726597AbgKMLKO (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 13 Nov 2020 06:10:14 -0500
X-Virus-Scanned: by amavisd-new at test-mx.suse.de
Received: from relay2.suse.de (unknown [195.135.221.27])
        by mx2.suse.de (Postfix) with ESMTP id ECA9EAEFB;
        Fri, 13 Nov 2020 11:10:11 +0000 (UTC)
From: Thomas Bogendoerfer <tsbogend@alpha.franken.de>
To: Huacai Chen <chenhc@lemote.com>,
        Aleksandar Markovic <aleksandar.qemu.devel@gmail.com>,
        linux-mips@vger.kernel.org, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH 2/4] MIPS: kvm: Use vm_get_page_prot to get protection bits
Date: Fri, 13 Nov 2020 12:09:50 +0100
Message-Id: <20201113110952.68086-2-tsbogend@alpha.franken.de>
X-Mailer: git-send-email 2.16.4
In-Reply-To: <20201113110952.68086-1-tsbogend@alpha.franken.de>
References: <20201113110952.68086-1-tsbogend@alpha.franken.de>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

MIPS protection bits are setup during runtime so using defines like
PAGE_SHARED ignores this runtime changes. Using vm_get_page_prot
to get correct page protection fixes this.

Signed-off-by: Thomas Bogendoerfer <tsbogend@alpha.franken.de>
---
 arch/mips/kvm/mmu.c | 4 +++-
 1 file changed, 3 insertions(+), 1 deletion(-)

```
