#### [PATCH v2 1/2] KVM: SVM: Move asid to vcpu_svm
##### From: Cathy Avery <cavery@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Cathy Avery <cavery@redhat.com>
X-Patchwork-Id: 11831033
Return-Path: <SRS0=URuE=DS=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B415C16BC
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 11 Oct 2020 18:48:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 897EB215A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 11 Oct 2020 18:48:39 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="iTfIDWSO"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728421AbgJKSs1 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 11 Oct 2020 14:48:27 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:52253 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728336AbgJKSs0 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Sun, 11 Oct 2020 14:48:26 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1602442105;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=fsF90lczTHK2vP6/mcyjhD+7u2tKEKelJzv9co4ZOe0=;
        b=iTfIDWSOlZitPm7+s9iAkWpk9K/179kJrbN3CTOfI7rhcXBA1o56a0Pk/vVLLvltybLf7U
        Qkml7gbVL85VIGB8sqJHqR0dmlAxn1IoKmDns7mLB43Q8Sc50Ut4c1WwsexI4bahtBPWcr
        g9kVuM1DiWFrlB3uDXvZDINglIbscLM=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-465-yCkWrjjbM1S0wrIHsOI76g-1; Sun, 11 Oct 2020 14:48:21 -0400
X-MC-Unique: yCkWrjjbM1S0wrIHsOI76g-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 77F96804004;
        Sun, 11 Oct 2020 18:48:20 +0000 (UTC)
Received: from virtlab710.virt.lab.eng.bos.redhat.com
 (virtlab710.virt.lab.eng.bos.redhat.com [10.19.152.252])
        by smtp.corp.redhat.com (Postfix) with ESMTP id C14565C1DC;
        Sun, 11 Oct 2020 18:48:19 +0000 (UTC)
From: Cathy Avery <cavery@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        pbonzini@redhat.com
Cc: vkuznets@redhat.com, wei.huang2@amd.com, mlevitsk@redhat.com
Subject: [PATCH v2 1/2] KVM: SVM: Move asid to vcpu_svm
Date: Sun, 11 Oct 2020 14:48:17 -0400
Message-Id: <20201011184818.3609-2-cavery@redhat.com>
In-Reply-To: <20201011184818.3609-1-cavery@redhat.com>
References: <20201011184818.3609-1-cavery@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Move asid to svm->asid to allow for vmcb assignment
during svm_vcpu_run without regard to which level
guest is running.

Signed-off-by: Cathy Avery <cavery@redhat.com>
---
 arch/x86/kvm/svm/svm.c | 4 +++-
 arch/x86/kvm/svm/svm.h | 1 +
 2 files changed, 4 insertions(+), 1 deletion(-)

```
