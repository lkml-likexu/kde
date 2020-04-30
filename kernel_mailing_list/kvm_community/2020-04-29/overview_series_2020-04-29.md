#### [RFC PATCH 2/5] statsfs API: create, add and remove statsfs
##### From: Emanuele Giuseppe Esposito <eesposit@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Emanuele Giuseppe Esposito <eesposit@redhat.com>
X-Patchwork-Id: 11516557
Return-Path: <SRS0=yWZj=6N=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9A85D13B2
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 29 Apr 2020 09:49:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7D7152087E
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 29 Apr 2020 09:49:36 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="S72lMrJD"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726745AbgD2Jtf (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 29 Apr 2020 05:49:35 -0400
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:57974 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726739AbgD2Jtf (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 29 Apr 2020 05:49:35 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1588153772;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=bbs27IXMBaJcsgy3STOZVEUhkP5D7KawKdkHQuyWL3c=;
        b=S72lMrJDjgGGrdhQN9VtoUpcb62qHMfpnwlxBgg9ftY07ZeGLPRmmewCcw6cweF/Og0mmB
        1odbHVmjS38DkY020JQkyVdiRJjjr/BN5m3++0woW0oka5M2xmtlpqXSabhB5qwdgtikPD
        yhWV8NCVj9NB1DXaduqGuuZlOD6wtsM=
Received: from mail-wr1-f72.google.com (mail-wr1-f72.google.com
 [209.85.221.72]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-109-_9eugQG7Oqm4DToMXmR-yA-1; Wed, 29 Apr 2020 05:49:31 -0400
X-MC-Unique: _9eugQG7Oqm4DToMXmR-yA-1
Received: by mail-wr1-f72.google.com with SMTP id r11so1437977wrx.21
        for <kvm@vger.kernel.org>; Wed, 29 Apr 2020 02:49:30 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=bbs27IXMBaJcsgy3STOZVEUhkP5D7KawKdkHQuyWL3c=;
        b=m2q7I3dPApvcE1nFGesgiNxclbXv1mHq1FIEQl30H5RKMn96iyrW+rZy131RDMDTPa
         qghuPYI6n7YVd0Z+l2FtRiuLLK0geiYTyRtGTbbyoFvey6chFQGMZwE93DwskrFy7eX9
         S45AE1mMLAvJ5y4Iz6WSN26TbHsP90ODtSq0qWmHWpKkztYQUtvs+Idwbt9Dn6D8P5QP
         1L1QS6LxZd/NoQDaQrJt/O/qEE4WmwFuwJQntVdZFl/rFEtJ7zo6GlBkWW5VxafBTcNO
         mS4qz8ywc2l7upObbgYgGo6FCI07Ft2YV5zMAXV9TuksaiAVEyIqHW+uEl3p9/Yu6bRk
         Skcw==
X-Gm-Message-State: AGi0PuZTXKpu6DbD0xZti3nmEZe7E+sDVOvz0/DbBIvEQp4o7x8BG6Sv
        SX1QHBl+59deUyM4ZDbRJX+6KnYiici7C52Ty8ykYaOMrlQwr+Pr7MLuuTvtca+37VWIgWd9NSX
        KEBpWe5apEDle
X-Received: by 2002:adf:fe87:: with SMTP id l7mr40790316wrr.360.1588153770038;
        Wed, 29 Apr 2020 02:49:30 -0700 (PDT)
X-Google-Smtp-Source: 
 APiQypL3lOosPELSXYfi/Ql2ON5M3P/FRdYdFKW7FpT8yKLlLalIpi9flCq1OR+1XzHDC86bYLP/TQ==
X-Received: by 2002:adf:fe87:: with SMTP id l7mr40790296wrr.360.1588153769812;
        Wed, 29 Apr 2020 02:49:29 -0700 (PDT)
Received: from localhost.localdomain.com ([194.230.155.226])
        by smtp.gmail.com with ESMTPSA id
 y18sm7506030wmc.45.2020.04.29.02.49.28
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 29 Apr 2020 02:49:29 -0700 (PDT)
From: Emanuele Giuseppe Esposito <eesposit@redhat.com>
To: Matthew Wilcox <willy@infradead.org>
Cc: kvm@vger.kernel.org, linux-fsdevel@vger.kernel.org, mst@redhat.com,
        borntraeger@de.ibm.com, Paolo Bonzini <pbonzini@redhat.com>,
        Emanuele Giuseppe Esposito <eesposit@redhat.com>
Subject: [RFC PATCH 2/5] statsfs API: create, add and remove statsfs
Date: Wed, 29 Apr 2020 11:49:22 +0200
Message-Id: <20200429094922.55032-1-eesposit@redhat.com>
X-Mailer: git-send-email 2.25.2
In-Reply-To: <20200427154727.GH29705@bombadil.infradead.org>
References: <20200427154727.GH29705@bombadil.infradead.org>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Mattew,
I am trying to apply your Xarrays suggestion, but I don't
understand how to make them properly work. In particular, the __xa_alloc
function always returns -EINVAL.

I tried to follow the Xarrays kernel doc and the example you provided to
replace the subordinates linked list, but alloc always returns that error.

Below you can find the changes I intended to do.
Can you help me?

Thank you,
Emanuele

------ 8< -----------
From ad5d20b6ce7995b2d1164104cf958f7bc3e692fa Mon Sep 17 00:00:00 2001
From: Emanuele Giuseppe Esposito <eesposit@redhat.com>
Date: Tue, 28 Apr 2020 12:21:00 +0200
Subject: [PATCH] statsfs: switch subordinate sources to xarray
---
 fs/statsfs/statsfs.c    | 45 +++++++++++++++++++++++++++--------------
 include/linux/statsfs.h |  5 ++---
 2 files changed, 32 insertions(+), 18 deletions(-)

```
#### [PATCH] KVM: MIPS: use true,false for bool variable
##### From: Jason Yan <yanaijie@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Yan <yanaijie@huawei.com>
X-Patchwork-Id: 11517569
Return-Path: <SRS0=yWZj=6N=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1B64392A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 29 Apr 2020 14:10:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0A7EB218AC
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 29 Apr 2020 14:10:25 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728139AbgD2OKW (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 29 Apr 2020 10:10:22 -0400
Received: from szxga06-in.huawei.com ([45.249.212.32]:36840 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726691AbgD2OKV (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 29 Apr 2020 10:10:21 -0400
Received: from DGGEMS404-HUB.china.huawei.com (unknown [172.30.72.60])
        by Forcepoint Email with ESMTP id 4038964235C1C3E36776;
        Wed, 29 Apr 2020 22:10:18 +0800 (CST)
Received: from huawei.com (10.175.124.28) by DGGEMS404-HUB.china.huawei.com
 (10.3.19.204) with Microsoft SMTP Server id 14.3.487.0; Wed, 29 Apr 2020
 22:10:09 +0800
From: Jason Yan <yanaijie@huawei.com>
To: <tsbogend@alpha.franken.de>, <pbonzini@redhat.com>,
        <sean.j.christopherson@intel.com>, <linux-mips@vger.kernel.org>,
        <kvm@vger.kernel.org>, <linux-kernel@vger.kernel.org>
CC: Jason Yan <yanaijie@huawei.com>
Subject: [PATCH] KVM: MIPS: use true,false for bool variable
Date: Wed, 29 Apr 2020 22:09:35 +0800
Message-ID: <20200429140935.7993-1-yanaijie@huawei.com>
X-Mailer: git-send-email 2.21.1
MIME-Version: 1.0
X-Originating-IP: [10.175.124.28]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Fix the following coccicheck warning:

arch/mips/kvm/mips.c:82:1-28: WARNING: Assignment of 0/1 to bool
variable
arch/mips/kvm/mips.c:88:1-28: WARNING: Assignment of 0/1 to bool
variable

Signed-off-by: Jason Yan <yanaijie@huawei.com>
---
 arch/mips/kvm/mips.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH] kvm: x86: Cleanup vcpu->arch.guest_xstate_size
##### From: Xiaoyao Li <xiaoyao.li@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xiaoyao Li <xiaoyao.li@intel.com>
X-Patchwork-Id: 11516299
Return-Path: <SRS0=yWZj=6N=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 490F581
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 29 Apr 2020 07:41:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 38CB2208E0
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 29 Apr 2020 07:41:27 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726611AbgD2HlY (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 29 Apr 2020 03:41:24 -0400
Received: from mga02.intel.com ([134.134.136.20]:43114 "EHLO mga02.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726355AbgD2HlY (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 29 Apr 2020 03:41:24 -0400
IronPort-SDR: 
 3PqwIIFQKMmXCLuypnL7o3Tfliz+Knx1gIw6ZRqe0LNsU2t3MGY13m02hqqejTzN1/2Zk1NM3I
 tQEdmded6nOw==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga003.fm.intel.com ([10.253.24.29])
  by orsmga101.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 29 Apr 2020 00:41:23 -0700
IronPort-SDR: 
 phi0KJ//BVVxyKik5SX4LXIfbNkAfgUfknW+m75A2qkdVTQLjC1+fOjB60anFyH3w/m175ypCW
 NKGwCtOaEyMg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,330,1583222400";
   d="scan'208";a="302931421"
Received: from lxy-dell.sh.intel.com ([10.239.159.21])
  by FMSMGA003.fm.intel.com with ESMTP; 29 Apr 2020 00:41:21 -0700
From: Xiaoyao Li <xiaoyao.li@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH] kvm: x86: Cleanup vcpu->arch.guest_xstate_size
Date: Wed, 29 Apr 2020 23:43:12 +0800
Message-Id: <20200429154312.1411-1-xiaoyao.li@intel.com>
X-Mailer: git-send-email 2.18.2
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

vcpu->arch.guest_xstate_size lost its only user since commit df1daba7d1cb
("KVM: x86: support XSAVES usage in the host"), so clean it up.

Signed-off-by: Xiaoyao Li <xiaoyao.li@intel.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/include/asm/kvm_host.h | 1 -
 arch/x86/kvm/cpuid.c            | 8 ++------
 arch/x86/kvm/x86.c              | 2 --
 3 files changed, 2 insertions(+), 9 deletions(-)

```
#### [PATCH RFC 1/6] Revert "KVM: async_pf: Fix #DF due to inject "Page not Present" and "Page Ready" exceptions simultaneously"
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11516477
Return-Path: <SRS0=yWZj=6N=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 150E013B2
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 29 Apr 2020 09:37:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id EE73A2074A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 29 Apr 2020 09:37:22 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="dj/fOCZD"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726699AbgD2Jgw (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 29 Apr 2020 05:36:52 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:40558 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726678AbgD2Jgv (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 29 Apr 2020 05:36:51 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1588153011;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=qrU45IjYpsSPhee98a71DO7PSXKEWlgj/Cgaykvb5Xg=;
        b=dj/fOCZDm7sNGXBmmk4Tc05OqP0XQgluyD7BwVnJbq2x3VAhjIsKxlGRQfDJ2i2tyBXlBm
        +pC4vlwr7oMNYVDxsaTI/N+T6NVkq1Waonf0FnVp+9s2g7nArv04bcjxM4Of3tTvSF9A5C
        hMiYNy699/4BD9v7EHiktW1ktrmphhM=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-150-SW8I2XbHNheSFWLDCaJulg-1; Wed, 29 Apr 2020 05:36:46 -0400
X-MC-Unique: SW8I2XbHNheSFWLDCaJulg-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 7088E800C78;
        Wed, 29 Apr 2020 09:36:44 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.193.242])
        by smtp.corp.redhat.com (Postfix) with ESMTP id B86C05D9C9;
        Wed, 29 Apr 2020 09:36:40 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: x86@kernel.org, kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>,
        Andy Lutomirski <luto@kernel.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        "H. Peter Anvin" <hpa@zytor.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>
Subject: [PATCH RFC 1/6] Revert "KVM: async_pf: Fix #DF due to inject "Page
 not Present" and "Page Ready" exceptions simultaneously"
Date: Wed, 29 Apr 2020 11:36:29 +0200
Message-Id: <20200429093634.1514902-2-vkuznets@redhat.com>
In-Reply-To: <20200429093634.1514902-1-vkuznets@redhat.com>
References: <20200429093634.1514902-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Commit 9a6e7c39810e (""KVM: async_pf: Fix #DF due to inject "Page not
Present" and "Page Ready" exceptions simultaneously") added a protection
against 'page ready' notification coming before 'page not ready' is
delivered. This situation seems to be impossible since commit 2a266f23550b
("KVM MMU: check pending exception before injecting APF) which added
'vcpu->arch.exception.pending' check to kvm_can_do_async_pf.

On x86, kvm_arch_async_page_present() has only one call site:
kvm_check_async_pf_completion() loop and we only enter the loop when
kvm_arch_can_inject_async_page_present(vcpu) which when async pf msr
is enabled, translates into kvm_can_do_async_pf().

There is also one problem with the cancellation mechanism. We don't seem
to check that the 'page not ready' notification we're cancelling matches
the 'page ready' notification so in theory, we may erroneously drop two
valid events.

Revert the commit. apf_get_user() stays as we will need it for the new
'page ready notifications via interrupt' mechanism.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/x86.c | 16 +---------------
 1 file changed, 1 insertion(+), 15 deletions(-)

```
#### [PATCH v3 01/10] s390x: smp: Test all CRs on initial reset
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11517687
Return-Path: <SRS0=yWZj=6N=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D936413B2
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 29 Apr 2020 14:35:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C90332074A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 29 Apr 2020 14:35:33 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727107AbgD2Ofd (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 29 Apr 2020 10:35:33 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:25772 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726355AbgD2Ofc (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 29 Apr 2020 10:35:32 -0400
Received: from pps.filterd (m0098399.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 03TEXD9i133135;
        Wed, 29 Apr 2020 10:35:31 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 30mhc2frg4-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 29 Apr 2020 10:35:31 -0400
Received: from m0098399.ppops.net (m0098399.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 03TEXOhH134034;
        Wed, 29 Apr 2020 10:35:31 -0400
Received: from ppma03ams.nl.ibm.com (62.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.98])
        by mx0a-001b2d01.pphosted.com with ESMTP id 30mhc2frf0-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 29 Apr 2020 10:35:30 -0400
Received: from pps.filterd (ppma03ams.nl.ibm.com [127.0.0.1])
        by ppma03ams.nl.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 03TEUWY6009583;
        Wed, 29 Apr 2020 14:35:28 GMT
Received: from b06avi18626390.portsmouth.uk.ibm.com
 (b06avi18626390.portsmouth.uk.ibm.com [9.149.26.192])
        by ppma03ams.nl.ibm.com with ESMTP id 30mcu5rkry-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 29 Apr 2020 14:35:28 +0000
Received: from d06av22.portsmouth.uk.ibm.com (d06av22.portsmouth.uk.ibm.com
 [9.149.105.58])
        by b06avi18626390.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 03TEYHWd52035966
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 29 Apr 2020 14:34:17 GMT
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 1EC284C046;
        Wed, 29 Apr 2020 14:35:26 +0000 (GMT)
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 6D2A84C040;
        Wed, 29 Apr 2020 14:35:25 +0000 (GMT)
Received: from linux01.pok.stglabs.ibm.com (unknown [9.114.17.81])
        by d06av22.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Wed, 29 Apr 2020 14:35:25 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: thuth@redhat.com, linux-s390@vger.kernel.org, david@redhat.com,
        borntraeger@de.ibm.com, cohuck@redhat.com
Subject: [PATCH v3 01/10] s390x: smp: Test all CRs on initial reset
Date: Wed, 29 Apr 2020 10:35:09 -0400
Message-Id: <20200429143518.1360468-2-frankja@linux.ibm.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20200429143518.1360468-1-frankja@linux.ibm.com>
References: <20200429143518.1360468-1-frankja@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.676
 definitions=2020-04-29_07:2020-04-29,2020-04-29 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 suspectscore=1
 impostorscore=0 priorityscore=1501 adultscore=0 lowpriorityscore=0
 spamscore=0 bulkscore=0 mlxlogscore=999 phishscore=0 mlxscore=0
 malwarescore=0 clxscore=1015 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-2003020000 definitions=main-2004290117
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

All CRs are set to 0 and CRs 0 and 14 are set to pre-defined values,
so we also need to test 1-13 and 15 for 0.

And while we're at it, let's also set some values to cr 1, 7 and 13, so
we can actually be sure that they will be zeroed.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: Christian Borntraeger <borntraeger@de.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
---
 s390x/smp.c | 18 +++++++++++++++++-
 1 file changed, 17 insertions(+), 1 deletion(-)

```
#### [PATCH][v2] kvm: x86: emulate APERF/MPERF registers
##### From: Li RongQing <lirongqing@baidu.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Li,Rongqing" <lirongqing@baidu.com>
X-Patchwork-Id: 11516041
Return-Path: <SRS0=yWZj=6N=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 94F5A14B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 29 Apr 2020 05:47:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7E6BE20757
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 29 Apr 2020 05:47:00 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726515AbgD2Fq5 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 29 Apr 2020 01:46:57 -0400
Received: from mx137-tc.baidu.com ([61.135.168.137]:43907 "EHLO
        tc-sys-mailedm02.tc.baidu.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1725798AbgD2Fq5 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 29 Apr 2020 01:46:57 -0400
Received: from localhost (cp01-cos-dev01.cp01.baidu.com [10.92.119.46])
        by tc-sys-mailedm02.tc.baidu.com (Postfix) with ESMTP id 044A211C0069;
        Wed, 29 Apr 2020 13:46:37 +0800 (CST)
From: Li RongQing <lirongqing@baidu.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org, x86@kernel.org,
        hpa@zytor.com, bp@alien8.de, mingo@redhat.com, tglx@linutronix.de,
        joro@8bytes.org, jmattson@google.com, wanpengli@tencent.com,
        vkuznets@redhat.com, sean.j.christopherson@intel.com,
        pbonzini@redhat.com
Subject: [PATCH][v2] kvm: x86: emulate APERF/MPERF registers
Date: Wed, 29 Apr 2020 13:46:36 +0800
Message-Id: <1588139196-23802-1-git-send-email-lirongqing@baidu.com>
X-Mailer: git-send-email 1.7.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Guest kernel reports a fixed cpu frequency in /proc/cpuinfo,
this is confused to user when turbo is enable, and aperf/mperf
can be used to show current cpu frequency after 7d5905dc14a
"(x86 / CPU: Always show current CPU frequency in /proc/cpuinfo)"
so we should emulate aperf mperf to achieve it

the period of aperf/mperf in guest mode are accumulated as
emulated value, and add per-VM knod to enable emulate mperfaperf

diff v1:
1. support AMD
2. support per-vm capability to enable

Signed-off-by: Li RongQing <lirongqing@baidu.com>
Signed-off-by: Chai Wen <chaiwen@baidu.com>
Signed-off-by: Jia Lina <jialina01@baidu.com>
---
 Documentation/virt/kvm/api.rst  |  7 +++++++
 arch/x86/include/asm/kvm_host.h |  4 ++++
 arch/x86/kvm/cpuid.c            | 13 ++++++++++++-
 arch/x86/kvm/svm.c              |  6 ++++++
 arch/x86/kvm/vmx/vmx.c          |  6 ++++++
 arch/x86/kvm/x86.c              | 37 +++++++++++++++++++++++++++++++++++++
 arch/x86/kvm/x86.h              |  6 ++++++
 include/uapi/linux/kvm.h        |  1 +
 8 files changed, 79 insertions(+), 1 deletion(-)

```
#### [PATCH] vhost: fix default for vhost_iotlb
##### From: Arnd Bergmann <arnd@arndb.de>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Arnd Bergmann <arnd@arndb.de>
X-Patchwork-Id: 11517611
Return-Path: <SRS0=yWZj=6N=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DD70681
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 29 Apr 2020 14:23:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D04EA20B80
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 29 Apr 2020 14:23:31 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728006AbgD2OX1 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 29 Apr 2020 10:23:27 -0400
Received: from mout.kundenserver.de ([212.227.126.130]:59573 "EHLO
        mout.kundenserver.de" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726661AbgD2OX0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 29 Apr 2020 10:23:26 -0400
Received: from threadripper.lan ([149.172.19.189]) by mrelayeu.kundenserver.de
 (mreue010 [212.227.15.129]) with ESMTPA (Nemesis) id
 1N7iOw-1j8KpB09eU-014iMZ; Wed, 29 Apr 2020 16:23:19 +0200
From: Arnd Bergmann <arnd@arndb.de>
To: "Michael S. Tsirkin" <mst@redhat.com>,
        Jason Wang <jasowang@redhat.com>
Cc: Arnd Bergmann <arnd@arndb.de>, Tiwei Bie <tiwei.bie@intel.com>,
        kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH] vhost: fix default for vhost_iotlb
Date: Wed, 29 Apr 2020 16:23:04 +0200
Message-Id: <20200429142317.1847441-1-arnd@arndb.de>
X-Mailer: git-send-email 2.26.0
MIME-Version: 1.0
X-Provags-ID: V03:K1:b3pbp/XZSd+qFAXvZ9I7UjuleCw3GTy1vtyionbvaNjSrD6kYrH
 y/IBPt43A5XriZwjpg/iVL+DG+MEIGNcDlWlMfkFbLwqZGn3pMma6Xx0viUdy8bDJdYLpx4
 Lt9B3isKWwO+iGzLngj6QapH5GuypPJSDv//HUUaylj17ZdCqAsqXaqYgEDbLhcGG+xHkJk
 FAgf2eV+mFETYygqDSJbA==
X-Spam-Flag: NO
X-UI-Out-Filterresults: notjunk:1;V03:K0:cHnxtw5s88I=:liybKe0ZyJzauaYbhV1tR4
 v+detTxqBVhe77qXrhR+LJDZDMNMOV9mkaPORuAXHIO5xefWpUdkz7/jiaLp1rVYj2t2+IZXW
 gshFy77aTRiWP9IpwdC7VXhAMHccPlBSLN3hOlCaY8AuVBKJbH4zlgAI6RriDPkTOroUsBhQu
 Bub16qn/gv6uBFl5q8Mv6yfgOGbDoMBT+Iy59/H9BOg6yCTIBNZNaR0kKt55xjXZRFY9nCeIz
 fprxjDfT8ScG5bD0YZXz8EpefMvdPdPekIcs/ntCx4f5Brr9ND7oq8cpkWPdCpSrI0gLsnpdi
 oTc1r8Xe87uRzZXf8hQ6sjtoBmS7kj8RaIEsyERkpCXyoES858LWCSlfQHpSxkNVZ6XSAP7OY
 Ir3zR49Q5LlOIx5i6GpH5DLsCrOpenvCyZ4SeKcBvwrZCMeXvJaMLqfCYo8MsTRSwKbPokI01
 1mNrqwi3kWN45VD/6TFDZ5fbTjlzmzwIz2/8aZhVjtSITAgicPam99N3mDGx0k6Vs8TFnhhcp
 rO1P5mJi5QQhgvmGKXLkBJAIH7DfNPKIuzBL0GWXOQFAzMfM4W0BJbTQcSAhh8cShtglo/RsN
 lAOvUduj4mF3d/+TzX8M/wA0ciSJd/K37cwbwyrSOXHTHwe9f/cwweHkCPwYBl4snwOFa7lKF
 S+dQUFMv9GoCpx4RCmGtGm3hnL/EUd+moTge+fJmVdqv79d7rIx+kiZXeTay19bhIB4NWeB4K
 HSJJK8hYrPtPyRvsAAH4oJnDSlMvq9s2gDZ8OGRC37fKsYgkiDOthoi3KmKJbELyTstVJ0w5c
 tS93kyVDjAmyLIv1AtkY5kjjiIpVAnOkIKdLzwZcK39cVbgrKg=
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

During randconfig build testing, I ran into a configuration that has
CONFIG_VHOST=m, CONFIG_VHOST_IOTLB=m and CONFIG_VHOST_RING=y, which
makes the iotlb implementation left out from vhost_ring, and in turn
leads to a link failure of the vdpa_sim module:

ERROR: modpost: "vringh_set_iotlb" [drivers/vdpa/vdpa_sim/vdpa_sim.ko] undefined!
ERROR: modpost: "vringh_init_iotlb" [drivers/vdpa/vdpa_sim/vdpa_sim.ko] undefined!
ERROR: modpost: "vringh_iov_push_iotlb" [drivers/vdpa/vdpa_sim/vdpa_sim.ko] undefined!
ERROR: modpost: "vringh_iov_pull_iotlb" [drivers/vdpa/vdpa_sim/vdpa_sim.ko] undefined!
ERROR: modpost: "vringh_complete_iotlb" [drivers/vdpa/vdpa_sim/vdpa_sim.ko] undefined!
ERROR: modpost: "vringh_getdesc_iotlb" [drivers/vdpa/vdpa_sim/vdpa_sim.ko] undefined!

Work around it by setting the default for VHOST_IOTLB to avoid this
configuration.

Fixes: e6faeaa12841 ("vhost: drop vring dependency on iotlb")
Signed-off-by: Arnd Bergmann <arnd@arndb.de>
---
I fixed this a while ago locally but never got around to sending the
fix. If the problem has been addressed differently in the meantime,
please ignore this one.
---
 drivers/vhost/Kconfig | 1 +
 1 file changed, 1 insertion(+)

```
