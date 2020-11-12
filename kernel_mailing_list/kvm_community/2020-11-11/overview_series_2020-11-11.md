#### [PATCH v15 1/9] arm64: Probe for the presence of KVM hypervisor
##### From: Jianyong Wu <jianyong.wu@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jianyong Wu <jianyong.wu@arm.com>
X-Patchwork-Id: 11896337
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 971C3C56201
	for <kvm@archiver.kernel.org>; Wed, 11 Nov 2020 06:22:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4FDB420786
	for <kvm@archiver.kernel.org>; Wed, 11 Nov 2020 06:22:55 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726054AbgKKGWx (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 11 Nov 2020 01:22:53 -0500
Received: from foss.arm.com ([217.140.110.172]:41698 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726015AbgKKGWo (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 11 Nov 2020 01:22:44 -0500
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 9FA0B1063;
        Tue, 10 Nov 2020 22:22:42 -0800 (PST)
Received: from localhost.localdomain (entos-thunderx2-desktop.shanghai.arm.com
 [10.169.212.215])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPA id
 5179C3F6CF;
        Tue, 10 Nov 2020 22:22:36 -0800 (PST)
From: Jianyong Wu <jianyong.wu@arm.com>
To: netdev@vger.kernel.org, yangbo.lu@nxp.com, john.stultz@linaro.org,
        tglx@linutronix.de, pbonzini@redhat.com,
        sean.j.christopherson@intel.com, maz@kernel.org,
        richardcochran@gmail.com, Mark.Rutland@arm.com, will@kernel.org,
        suzuki.poulose@arm.com, Andre.Przywara@arm.com,
        steven.price@arm.com
Cc: linux-kernel@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        Steve.Capper@arm.com, justin.he@arm.com, jianyong.wu@arm.com,
        nd@arm.com
Subject: [PATCH v15 1/9] arm64: Probe for the presence of KVM hypervisor
Date: Wed, 11 Nov 2020 14:22:03 +0800
Message-Id: <20201111062211.33144-2-jianyong.wu@arm.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20201111062211.33144-1-jianyong.wu@arm.com>
References: <20201111062211.33144-1-jianyong.wu@arm.com>
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

Change from Jianyong Wu:
mv kvm_arm_hyp_service_available to common place to let both arm/arm64 touch it.
add kvm_init_hyp_services also under arm arch to let arm kvm guest use this service.

Cc: Marc Zyngier <maz@kernel.org>
Signed-off-by: Will Deacon <will@kernel.org>
Signed-off-by: Jianyong Wu <jianyong.wu@arm.com>
---
 arch/arm/kernel/setup.c        |  1 +
 arch/arm64/kernel/setup.c      |  1 +
 drivers/firmware/smccc/smccc.c | 37 +++++++++++++++++++++++++++++
 include/linux/arm-smccc.h      | 43 ++++++++++++++++++++++++++++++++++
 4 files changed, 82 insertions(+)

```
#### [RFC PATCH 1/3] KVM: x86: Add helpers for {set|clear} bits in supported_xss
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Weijiang <weijiang.yang@intel.com>
X-Patchwork-Id: 11896405
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 3A1CCC4742C
	for <kvm@archiver.kernel.org>; Wed, 11 Nov 2020 06:32:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E7B0C2078E
	for <kvm@archiver.kernel.org>; Wed, 11 Nov 2020 06:32:02 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726020AbgKKGcA (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 11 Nov 2020 01:32:00 -0500
Received: from mga17.intel.com ([192.55.52.151]:43536 "EHLO mga17.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725904AbgKKGb1 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 11 Nov 2020 01:31:27 -0500
IronPort-SDR: 
 xe+hrv6e53TVuBTM1sicPH3CEfpBAQC1qcBUnBukwrLu130C17wwacd3tJsJRNGIlLsqqJ0XHR
 jjRyaU7D+MUA==
X-IronPort-AV: E=McAfee;i="6000,8403,9801"; a="149951497"
X-IronPort-AV: E=Sophos;i="5.77,468,1596524400";
   d="scan'208";a="149951497"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga003.jf.intel.com ([10.7.209.27])
  by fmsmga107.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 10 Nov 2020 22:31:27 -0800
IronPort-SDR: 
 U4NXlMMBhq7IhaqRgIfN55Z/duQ4Ym0W9MUxJNcVFRlcjoP0Zdb/l5tOu5qYSxGYrYyBbd+r1l
 ofg/v19g4N2Q==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,468,1596524400";
   d="scan'208";a="323167579"
Received: from local-michael-cet-test.sh.intel.com ([10.239.159.156])
  by orsmga003.jf.intel.com with ESMTP; 10 Nov 2020 22:31:25 -0800
From: Yang Weijiang <weijiang.yang@intel.com>
To: pbonzini@redhat.com, sean.j.christopherson@intel.com,
        jmattson@google.com, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org
Cc: Yang Weijiang <weijiang.yang@intel.com>
Subject: [RFC PATCH 1/3] KVM: x86: Add helpers for {set|clear} bits in
 supported_xss
Date: Wed, 11 Nov 2020 14:41:49 +0800
Message-Id: <20201111064151.1090-2-weijiang.yang@intel.com>
X-Mailer: git-send-email 2.17.2
In-Reply-To: <20201111064151.1090-1-weijiang.yang@intel.com>
References: <20201111064151.1090-1-weijiang.yang@intel.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Sean Christopherson <sean.j.christopherson@intel.com>

KVM supported XSS feature bits are designated in supported_xss, bits
could be set/cleared dynamically, add helpers to facilitate the operation.
Also add MSR_IA32_XSS to the list of MSRs reported to userspace if
supported_xss is non-zero, i.e. KVM supports at least one XSS based
feature.

Co-developed-by: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Yang Weijiang <weijiang.yang@intel.com>
---
 arch/x86/kvm/x86.c | 20 ++++++++++++++++++++
 1 file changed, 20 insertions(+)

```
#### [PATCH v2 01/11] KVM: selftests: Update .gitignore
##### From: Andrew Jones <drjones@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11897501
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-9.9 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 433D9C5517A
	for <kvm@archiver.kernel.org>; Wed, 11 Nov 2020 12:26:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CA0B120795
	for <kvm@archiver.kernel.org>; Wed, 11 Nov 2020 12:26:49 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Niycp4vE"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726465AbgKKM0s (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 11 Nov 2020 07:26:48 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:23655 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1725979AbgKKM0r (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 11 Nov 2020 07:26:47 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1605097607;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=cY9Dc3o8oHhG/6CVI6xeevBtNQB290eszc83VzqGshk=;
        b=Niycp4vEEBi1VAfMYprGjEn4THOQ3H0gP8Lut482uL7RwGd6r1ZCks154KSAocRmdBFD6O
        0qMDTuiy4i76VNp5Q4DTaGrCQjgMSGv9HZhxlObpitLosUVAMkQn7knY+HKShHU74SXE3M
        835nEr3y/qQMbd48My/sLxHzkO2pgNI=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-580-lmXgXWwSMkagX9QfkxpqJg-1; Wed, 11 Nov 2020 07:26:45 -0500
X-MC-Unique: lmXgXWwSMkagX9QfkxpqJg-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 9EA2A186DD41;
        Wed, 11 Nov 2020 12:26:44 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.40.193.216])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 018F610013BD;
        Wed, 11 Nov 2020 12:26:42 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, borntraeger@de.ibm.com, frankja@linux.ibm.com,
        bgardon@google.com, peterx@redhat.com
Subject: [PATCH v2 01/11] KVM: selftests: Update .gitignore
Date: Wed, 11 Nov 2020 13:26:26 +0100
Message-Id: <20201111122636.73346-2-drjones@redhat.com>
In-Reply-To: <20201111122636.73346-1-drjones@redhat.com>
References: <20201111122636.73346-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add x86_64/tsc_msrs_test and remove clear_dirty_log_test.

Reviewed-by: Ben Gardon <bgardon@google.com>
Signed-off-by: Andrew Jones <drjones@redhat.com>
---
 tools/testing/selftests/kvm/.gitignore | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] kvm: x86/mmu: Fix is_tdp_mmu_check when using PAEFrom: Ben Gardon <bgardon@google.com>
##### From: Ben Gardon <bgardon@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ben Gardon <bgardon@google.com>
X-Patchwork-Id: 11898335
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-20.4 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=unavailable autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id CAAB9C388F9
	for <kvm@archiver.kernel.org>; Wed, 11 Nov 2020 18:53:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 627E0206FB
	for <kvm@archiver.kernel.org>; Wed, 11 Nov 2020 18:53:47 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="kK51WkYo"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727635AbgKKSxn (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 11 Nov 2020 13:53:43 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:47316 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725949AbgKKSxm (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 11 Nov 2020 13:53:42 -0500
Received: from mail-pj1-x104a.google.com (mail-pj1-x104a.google.com
 [IPv6:2607:f8b0:4864:20::104a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 80A6FC0613D1
        for <kvm@vger.kernel.org>; Wed, 11 Nov 2020 10:53:42 -0800 (PST)
Received: by mail-pj1-x104a.google.com with SMTP id t15so1260096pja.7
        for <kvm@vger.kernel.org>; Wed, 11 Nov 2020 10:53:42 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:message-id:mime-version:subject:from:to:cc;
        bh=93R4ztQrLrDF9Ja7P3toIKUvpq9Mkw15Zf+bh5c6Tqo=;
        b=kK51WkYoFHiSWND2/+N+C4Ova1zafjAVM+MPR0hpWwVY8W6VovOfLNmIiMynognenH
         lbj/HnGi8LUypoLkUvvq6ifdmaKSM7Qs5KY8OLvuNSHqi93xn9P6OKqDth56mfLf7TmS
         eTy6XVOeyZYgAtmx4jHnLmdF44tZnyR7Y37vDyXD8JbUe+YWpWxdIFOY2Nm8WnVKjlrZ
         mxOlGUs7o2Q964Dlth1cEweUi0t1TPbzd6pUE+KsV14NikSdbNfPu+/9c1+67WbwQh0t
         up5tbY5R9KY1/3ZqfWU+oDjfpEZZf3nt8OrukS3kW8t8SAHkHMKBe8JkEeeJE8heHb7y
         6zVQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:message-id:mime-version:subject:from
         :to:cc;
        bh=93R4ztQrLrDF9Ja7P3toIKUvpq9Mkw15Zf+bh5c6Tqo=;
        b=eFh7sMLcpSfXgMWWZ+nxA2n85HEoh2RYfmx/19TENlVneVZ404eC0QMqp6ZkrU/I5C
         HVTeQCUQ0M+hQ8/of+IX2GcpPLNC3AZGVKu3LyJg/y04WQSkq3akz8dUXomRfaQSQhyN
         stQ57MhpiJbijYyPnB8yUNv/tUamw+sFqr7t70IZsSdb5GnpiBdfMMb3vifhwAf5nKKa
         TtjLhQKz+adt5rGMPaNpVgi376qZaoCLr3IG+AmQn/kowIU61dTB4HcSiBfI5sjntwJn
         z5EoU2FPp7AS7Dl0GE1vrKCOOGWzJpLFmkNkG/0qn1FHg2KLSaW4oLCXolEbb8VXQvrv
         vOmg==
X-Gm-Message-State: AOAM532tyXEJs0sIuKlEcjxpKFPTARk2fqWGqV76q9x/4a1KtCx1oh6T
        nOMOaf53wDzKskvTbLHWkTqW9ePc5v9t
X-Google-Smtp-Source: 
 ABdhPJyl7J/4ZMYI6a1D98WFOkbXOBJ8G/8pul2PYv3oklRs7dNvgDUFi0coDy0Z5skyieCqVo68nE6HtM2h
Sender: "bgardon via sendgmr" <bgardon@bgardon.sea.corp.google.com>
X-Received: from bgardon.sea.corp.google.com
 ([2620:15c:100:202:f693:9fff:fef4:a293])
 (user=bgardon job=sendgmr) by 2002:a17:902:bc46:b029:d6:d98a:1a68 with SMTP
 id t6-20020a170902bc46b02900d6d98a1a68mr10718919plz.63.1605120821929; Wed, 11
 Nov 2020 10:53:41 -0800 (PST)
Date: Wed, 11 Nov 2020 10:53:37 -0800
Message-Id: <20201111185337.1237383-1-bgardon@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.29.2.222.g5d2a92d10f8-goog
Subject: [PATCH] kvm: x86/mmu: Fix is_tdp_mmu_check when using PAE
From: Ben Gardon <bgardon@google.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Peter Shier <pshier@google.com>,
        Jim Mattson <jmattson@google.com>,
        Zdenek Kaspar <zkaspar82@gmail.com>,
        Ben Gardon <bgardon@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When PAE is in use, the root_hpa will not have a shadow page assoicated
with it. In this case the kernel will crash with a NULL pointer
dereference. Add checks to ensure is_tdp_mmu_root works as intended even
when using PAE.

Tested: compiles

Fixes: 02c00b3a2f7e ("kvm: x86/mmu: Allocate and free TDP MMU roots")
Reported-by: Zdenek Kaspar <zkaspar82@gmail.com>
Signed-off-by: Ben Gardon <bgardon@google.com>
---
 arch/x86/kvm/mmu/tdp_mmu.c | 10 ++++++++++
 1 file changed, 10 insertions(+)

```
#### [PATCH v2] x86/mce: Use "safe" MSR functions when enabling additional error logging
##### From: "Luck, Tony" <tony.luck@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Luck, Tony" <tony.luck@intel.com>
X-Patchwork-Id: 11895921
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-9.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED autolearn=unavailable autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C4077C5517A
	for <kvm@archiver.kernel.org>; Wed, 11 Nov 2020 00:40:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 89F7820679
	for <kvm@archiver.kernel.org>; Wed, 11 Nov 2020 00:40:02 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732090AbgKKAj7 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 10 Nov 2020 19:39:59 -0500
Received: from mga04.intel.com ([192.55.52.120]:12588 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727275AbgKKAj7 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 10 Nov 2020 19:39:59 -0500
IronPort-SDR: 
 pfxbqvZBzCS9LxdlzFXr1gnXMzqCfGtrBmiAOeht8KeiN2C9HYOYsWwJEmv0pesSolnRdvnbeD
 dSmxwayl4qFQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9801"; a="167489223"
X-IronPort-AV: E=Sophos;i="5.77,468,1596524400";
   d="scan'208";a="167489223"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga004.fm.intel.com ([10.253.24.48])
  by fmsmga104.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 10 Nov 2020 16:39:57 -0800
IronPort-SDR: 
 yxsyaDteDfcShgJDHe25SY8PLDJkrEfTHmRI7swP+/uvKoOvYh33CH3Zx0r8pzvBKXTdO1wOly
 JUW3MbeEmqxw==
X-IronPort-AV: E=Sophos;i="5.77,468,1596524400";
   d="scan'208";a="356389564"
Received: from agluck-desk2.sc.intel.com (HELO
 agluck-desk2.amr.corp.intel.com) ([10.3.52.68])
  by fmsmga004-auth.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 10 Nov 2020 16:39:56 -0800
Date: Tue, 10 Nov 2020 16:39:54 -0800
From: "Luck, Tony" <tony.luck@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Borislav Petkov <bp@alien8.de>, Jim Mattson <jmattson@google.com>,
        Qian Cai <cai@redhat.com>,
        "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>,
        "linux-tip-commits@vger.kernel.org"
        <linux-tip-commits@vger.kernel.org>, x86 <x86@kernel.org>,
        "kvm@vger.kernel.org" <kvm@vger.kernel.org>
Subject: [PATCH v2] x86/mce: Use "safe" MSR functions when enabling
 additional error logging
Message-ID: <20201111003954.GA11878@agluck-desk2.amr.corp.intel.com>
References: <a22b5468e1c94906b72c4d8bc83c0f64@intel.com>
 <20201109232402.GA25492@agluck-desk2.amr.corp.intel.com>
 <20201110063151.GB7290@nazgul.tnic>
 <094c2395-b1b3-d908-657c-9bd4144e40ac@redhat.com>
 <20201110095615.GB9450@nazgul.tnic>
 <b8de7f7b-7aa1-d98b-74be-62d7c055542b@redhat.com>
 <20201110155013.GE9857@nazgul.tnic>
 <1b587b45-a5a8-2147-ae53-06d1b284ea11@redhat.com>
 <cacd1cd272e94213a0c82c9871086cf5@intel.com>
 <7bd98718-f800-02ef-037a-4dfc5a7d1a54@redhat.com>
MIME-Version: 1.0
Content-Disposition: inline
In-Reply-To: <7bd98718-f800-02ef-037a-4dfc5a7d1a54@redhat.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Booting as a guest under KVM results in error messages about
unchecked MSR access:

[    6.814328][    T0] unchecked MSR access error: RDMSR from 0x17f at rIP: 0xffffffff84483f16 (mce_intel_feature_init+0x156/0x270)

because KVM doesn't provide emulation for random model specific registers.

Switch to using rdmsrl_safe()/wrmsrl_safe() to avoid the message.

Reported-by: Qian Cai <cai@redhat.com>
Fixes: 68299a42f842 ("x86/mce: Enable additional error logging on certain Intel CPUs")
Signed-off-by: Tony Luck <tony.luck@intel.com>
---
 arch/x86/kernel/cpu/mce/intel.c | 5 +++--
 1 file changed, 3 insertions(+), 2 deletions(-)

```
#### [PATCH] vhost_vdpa: switch to vmemdup_user()
##### From: Tian Tao <tiantao6@hisilicon.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tian Tao <tiantao6@hisilicon.com>
X-Patchwork-Id: 11896023
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 5F108C388F7
	for <kvm@archiver.kernel.org>; Wed, 11 Nov 2020 01:14:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1D3E5221E9
	for <kvm@archiver.kernel.org>; Wed, 11 Nov 2020 01:14:31 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732570AbgKKBO0 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 10 Nov 2020 20:14:26 -0500
Received: from szxga05-in.huawei.com ([45.249.212.191]:7627 "EHLO
        szxga05-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1731746AbgKKBOW (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 10 Nov 2020 20:14:22 -0500
Received: from DGGEMS409-HUB.china.huawei.com (unknown [172.30.72.58])
        by szxga05-in.huawei.com (SkyGuard) with ESMTP id 4CW6FW4x09zLx6D;
        Wed, 11 Nov 2020 09:14:07 +0800 (CST)
Received: from localhost.localdomain (10.69.192.56) by
 DGGEMS409-HUB.china.huawei.com (10.3.19.209) with Microsoft SMTP Server id
 14.3.487.0; Wed, 11 Nov 2020 09:14:17 +0800
From: Tian Tao <tiantao6@hisilicon.com>
To: <mst@redhat.com>, <jasowang@redhat.com>, <kvm@vger.kernel.org>,
        <virtualization@lists.linux-foundation.org>,
        <netdev@vger.kernel.org>, <linux-kernel@vger.kernel.org>
Subject: [PATCH] vhost_vdpa: switch to vmemdup_user()
Date: Wed, 11 Nov 2020 09:14:48 +0800
Message-ID: <1605057288-60400-1-git-send-email-tiantao6@hisilicon.com>
X-Mailer: git-send-email 2.7.4
MIME-Version: 1.0
X-Originating-IP: [10.69.192.56]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Replace opencoded alloc and copy with vmemdup_user()

Signed-off-by: Tian Tao <tiantao6@hisilicon.com>
Reviewed-by: Stefano Garzarella <sgarzare@redhat.com>
---
 drivers/vhost/vdpa.c | 10 +++-------
 1 file changed, 3 insertions(+), 7 deletions(-)

```
