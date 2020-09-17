#### [PATCH v7 1/7] KVM: x86: Deflect unknown MSR accesses to user space
##### From: Alexander Graf <graf@amazon.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Graf <graf@amazon.com>
X-Patchwork-Id: 11780831
Return-Path: <SRS0=aKWm=CZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CB8B8618
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 16 Sep 2020 20:33:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8BB8B2220B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 16 Sep 2020 20:33:25 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amazon.com header.i=@amazon.com
 header.b="udjnzadm"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727356AbgIPUcj (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 16 Sep 2020 16:32:39 -0400
Received: from smtp-fw-9102.amazon.com ([207.171.184.29]:49984 "EHLO
        smtp-fw-9102.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727094AbgIPUaP (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 16 Sep 2020 16:30:15 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.com; i=@amazon.com; q=dns/txt; s=amazon201209;
  t=1600288212; x=1631824212;
  h=from:to:cc:subject:date:message-id:in-reply-to:
   references:mime-version:content-transfer-encoding;
  bh=ND9e1PrYvLU9INALSpxF6Ou/4aOmJHHlmr9WGOCGddI=;
  b=udjnzadmGdYy2seBwKFm9URgF/VqMe6AfW7q90GYuU5sGQ5YCFCwWNaJ
   avSh7eRAS+vpmS14RLY/Hx/KCH/1S9Aq3ECPxvH9Q4ml9jBUNd0R8nUxO
   y8cOgMQzFWfDL7yBeEnjh07mv5EW5G4MAgC7BdAs5hQEpoPt2/2qlk20j
   s=;
X-IronPort-AV: E=Sophos;i="5.76,434,1592870400";
   d="scan'208";a="76817925"
Received: from sea32-co-svc-lb4-vlan3.sea.corp.amazon.com (HELO
 email-inbound-relay-2a-53356bf6.us-west-2.amazon.com) ([10.47.23.38])
  by smtp-border-fw-out-9102.sea19.amazon.com with ESMTP;
 16 Sep 2020 20:30:07 +0000
Received: from EX13MTAUWC001.ant.amazon.com
 (pdx4-ws-svc-p6-lb7-vlan2.pdx.amazon.com [10.170.41.162])
        by email-inbound-relay-2a-53356bf6.us-west-2.amazon.com (Postfix) with
 ESMTPS id 90302A17D0;
        Wed, 16 Sep 2020 20:30:06 +0000 (UTC)
Received: from EX13D20UWC001.ant.amazon.com (10.43.162.244) by
 EX13MTAUWC001.ant.amazon.com (10.43.162.135) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Wed, 16 Sep 2020 20:30:06 +0000
Received: from u79c5a0a55de558.ant.amazon.com (10.43.162.35) by
 EX13D20UWC001.ant.amazon.com (10.43.162.244) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Wed, 16 Sep 2020 20:30:02 +0000
From: Alexander Graf <graf@amazon.com>
To: kvm list <kvm@vger.kernel.org>
CC: Sean Christopherson <sean.j.christopherson@intel.com>,
        Aaron Lewis <aaronlewis@google.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Jonathan Corbet <corbet@lwn.net>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        KarimAllah Raslan <karahmed@amazon.de>,
        Dan Carpenter <dan.carpenter@oracle.com>,
        <linux-doc@vger.kernel.org>, <linux-kernel@vger.kernel.org>
Subject: [PATCH v7 1/7] KVM: x86: Deflect unknown MSR accesses to user space
Date: Wed, 16 Sep 2020 22:29:45 +0200
Message-ID: <20200916202951.23760-2-graf@amazon.com>
X-Mailer: git-send-email 2.28.0.394.ge197136389
In-Reply-To: <20200916202951.23760-1-graf@amazon.com>
References: <20200916202951.23760-1-graf@amazon.com>
MIME-Version: 1.0
X-Originating-IP: [10.43.162.35]
X-ClientProxiedBy: EX13D42UWA002.ant.amazon.com (10.43.160.16) To
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

v6 -> v7:

  - Fire #GP without skipping the MSR instruction
  - Fix padding
---
 Documentation/virt/kvm/api.rst  |  73 +++++++++++++++++++-
 arch/x86/include/asm/kvm_host.h |   3 +
 arch/x86/kvm/emulate.c          |  18 ++++-
 arch/x86/kvm/x86.c              | 118 ++++++++++++++++++++++++++++++--
 include/trace/events/kvm.h      |   2 +-
 include/uapi/linux/kvm.h        |  12 ++++
 6 files changed, 217 insertions(+), 9 deletions(-)

```
#### [PATCH] KVM: SVM: use __GFP_ZERO instead of clear_page()
##### From: lihaiwei.kernel@gmail.com

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Haiwei Li <lihaiwei.kernel@gmail.com>
X-Patchwork-Id: 11779319
Return-Path: <SRS0=aKWm=CZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2CF4359D
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 16 Sep 2020 08:36:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 096172087D
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 16 Sep 2020 08:36:31 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="I/nL8EJJ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726507AbgIPIga (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 16 Sep 2020 04:36:30 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:33836 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725840AbgIPIg3 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 16 Sep 2020 04:36:29 -0400
Received: from mail-pf1-x443.google.com (mail-pf1-x443.google.com
 [IPv6:2607:f8b0:4864:20::443])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 9191CC06174A;
        Wed, 16 Sep 2020 01:36:29 -0700 (PDT)
Received: by mail-pf1-x443.google.com with SMTP id x123so3547026pfc.7;
        Wed, 16 Sep 2020 01:36:29 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=KT47zfJmk0l7JghqVT5ZA5rEy8OCXlg/IWMuynysqoI=;
        b=I/nL8EJJEdwYLLDbfZjvs/cqVdyYo5txPiN1xZ7rkpBRmJIrn4u3/Hxb/wjG0rehZ4
         go8mNOFsVCgqGnSnLZmn/UzVoh2xfNa+X3CCDeB3LHXqFStfNJGGepQWWqzMC2fr2SBX
         jFO7fNse+b7YDJPRBTLT5WU5LurvCTxoxZrUBETu8viXtFAGMS2s+tx1ar7I865v/9OA
         UgSE00xU6hImInbi57hnzYOEXHz/pljPeYAgf7t3xjpOnOLjdeuTSo09aMewwx40FzQZ
         kXUm/+RR29oDy8NYBYVxRGgILZWO1Z4grhJrMqZ7/Zkh/+yrNSowDNAPtj/FkJahh6z6
         9fMg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=KT47zfJmk0l7JghqVT5ZA5rEy8OCXlg/IWMuynysqoI=;
        b=B71yEVDtW3O/UK5BI54ukkkUoAJ+1LUvnn/qWc0cVLx5p2pCEOnZr3iWBIvhWgpURI
         Od9HrDkDCH0t5Vt8VPm1IZXxgTl4Xk1lK/0EbsYjxs1wEUA8oaSKSLlPivhqCX+ZoIAM
         2Fl6vLdHeccVveCRxARZoqjR5QbRjr7QPLqJYfoJsSw0/t2MEhyydswNIIodsIv5aYXP
         BoaNeZ4KDEgDe4meLSC0UiN+4ZUDjmz78+4I9TPYUuGIr+5NKuaeLaG8WC6sitTv7e9/
         VOcssN1p4hRwnbA46pkkDSwagSvj7O/8CcacCmyddD7juGFVoU8AgO21/D2NNq1mLg+3
         xEAg==
X-Gm-Message-State: AOAM532Zq4caHrn/qcoWk/eq6xc7fRkbFBfp7vWiKvTsIoXdbTo5HdDh
        0fEEDqWHdZNyLUhnhA2VL3o5/Bvs0ngo
X-Google-Smtp-Source: 
 ABdhPJxniQ3ds4YHSA2Ue2nrlmMmPPLMCqvXrVwKt7jYep+pX01hfC0BD9DPul4ueTvSoZH0p7Z6ng==
X-Received: by 2002:a63:8ac8:: with SMTP id
 y191mr17492646pgd.159.1600245388877;
        Wed, 16 Sep 2020 01:36:28 -0700 (PDT)
Received: from LiHaiwei.tencent.com ([203.205.141.64])
        by smtp.gmail.com with ESMTPSA id
 w6sm14523417pgf.72.2020.09.16.01.36.24
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Wed, 16 Sep 2020 01:36:28 -0700 (PDT)
From: lihaiwei.kernel@gmail.com
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org, x86@kernel.org
Cc: pbonzini@redhat.com, sean.j.christopherson@intel.com,
        vkuznets@redhat.com, wanpengli@tencent.com, jmattson@google.com,
        joro@8bytes.org, tglx@linutronix.de, mingo@redhat.com,
        bp@alien8.de, hpa@zytor.com, Haiwei Li <lihaiwei@tencent.com>
Subject: [PATCH] KVM: SVM: use __GFP_ZERO instead of clear_page()
Date: Wed, 16 Sep 2020 16:36:21 +0800
Message-Id: <20200916083621.5512-1-lihaiwei.kernel@gmail.com>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Haiwei Li <lihaiwei@tencent.com>

Use __GFP_ZERO while alloc_page().

Signed-off-by: Haiwei Li <lihaiwei@tencent.com>
---
 arch/x86/kvm/svm/avic.c | 6 ++----
 1 file changed, 2 insertions(+), 4 deletions(-)

```
#### [PATCH] Revert "KVM: Check the allocation of pv cpu mask"
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11779395
Return-Path: <SRS0=aKWm=CZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3A2766CA
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 16 Sep 2020 09:03:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1E60C20738
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 16 Sep 2020 09:03:57 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="d8zM/AUu"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726563AbgIPJDz (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 16 Sep 2020 05:03:55 -0400
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:43665 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726452AbgIPJDx (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 16 Sep 2020 05:03:53 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1600247031;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=k1t3aEF1OX+VjrQN9WEWMI8c1AvBflhlomB9um5hxKk=;
        b=d8zM/AUuOyKv7qVnrbYYYB3kZIK/9uOgThZi5ns86Fy4DnSE3A5doSP4zBSNj48LMV/sGG
        4O6q2IwP+2hH/VdORDwyAPSBrbx5mjCgYWFj6fneiVn0M9iwgRpfyQcuBt6WI/tVKwTymu
        BmhuKCNQ1siag6BUR1ayos2zW1VfxyI=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-355-8tOYClDzM0itUWfAY2fe4A-1; Wed, 16 Sep 2020 05:03:48 -0400
X-MC-Unique: 8tOYClDzM0itUWfAY2fe4A-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 5981A1005E72;
        Wed, 16 Sep 2020 09:03:46 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.192.19])
        by smtp.corp.redhat.com (Postfix) with ESMTP id E040278808;
        Wed, 16 Sep 2020 09:03:43 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Haiwei Li <lihaiwei@tencent.com>, linux-kernel@vger.kernel.org,
        x86@kernel.org
Subject: [PATCH] Revert "KVM: Check the allocation of pv cpu mask"
Date: Wed, 16 Sep 2020 11:03:42 +0200
Message-Id: <20200916090342.748452-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The commit 0f990222108d ("KVM: Check the allocation of pv cpu mask") we
have in 5.9-rc5 has two issue:
1) Compilation fails for !CONFIG_SMP, see:
   https://bugzilla.kernel.org/show_bug.cgi?id=209285

2) This commit completely disables PV TLB flush, see
   https://lore.kernel.org/kvm/87y2lrnnyf.fsf@vitty.brq.redhat.com/

The allocation problem is likely a theoretical one, if we don't
have memory that early in boot process we're likely doomed anyway.
Let's solve it properly later.

This reverts commit 0f990222108d214a0924d920e6095b58107d7b59.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kernel/kvm.c | 22 +++-------------------
 1 file changed, 3 insertions(+), 19 deletions(-)

```
#### [PATCH v2] vfio: add a singleton check for vfio_group_pin_pages
##### From: Yan Zhao <yan.y.zhao@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yan Zhao <yan.y.zhao@intel.com>
X-Patchwork-Id: 11778735
Return-Path: <SRS0=aKWm=CZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D5D97618
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 16 Sep 2020 02:41:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C6CBE21D94
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 16 Sep 2020 02:41:48 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726302AbgIPClp (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 15 Sep 2020 22:41:45 -0400
Received: from mga14.intel.com ([192.55.52.115]:17839 "EHLO mga14.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726079AbgIPClp (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 15 Sep 2020 22:41:45 -0400
IronPort-SDR: 
 cYuKMYz4px8i0wZ/lRCMk7uQndwo7kdffUlX9VByWknnLA5niweuc/C0piifeUJJhqd84hcW0d
 ff2NfzQftp4Q==
X-IronPort-AV: E=McAfee;i="6000,8403,9745"; a="158667533"
X-IronPort-AV: E=Sophos;i="5.76,430,1592895600";
   d="scan'208";a="158667533"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by fmsmga103.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 15 Sep 2020 19:41:43 -0700
IronPort-SDR: 
 WvYV8c7liVIQ9zCjn3jIyAHwjA96a9TXWHx0PHavH7nGVbLaikka5HSnwL6bBZCVJ81GKPdzE8
 54weBgBOa3sQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.76,430,1592895600";
   d="scan'208";a="335875192"
Received: from joy-optiplex-7040.sh.intel.com ([10.239.13.16])
  by orsmga008.jf.intel.com with ESMTP; 15 Sep 2020 19:41:41 -0700
From: Yan Zhao <yan.y.zhao@intel.com>
To: alex.williamson@redhat.com, cohuck@redhat.com
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Yan Zhao <yan.y.zhao@intel.com>
Subject: [PATCH v2] vfio: add a singleton check for vfio_group_pin_pages
Date: Wed, 16 Sep 2020 10:28:33 +0800
Message-Id: <20200916022833.26304-1-yan.y.zhao@intel.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Page pinning is used both to translate and pin device mappings for DMA
purpose, as well as to indicate to the IOMMU backend to limit the dirty
page scope to those pages that have been pinned, in the case of an IOMMU
backed device.
To support this, the vfio_pin_pages() interface limits itself to only
singleton groups such that the IOMMU backend can consider dirty page
scope only at the group level.  Implement the same requirement for the
vfio_group_pin_pages() interface.

Fixes: 95fc87b44104 ("vfio: Selective dirty page tracking if IOMMU backed device pins pages")

Signed-off-by: Yan Zhao <yan.y.zhao@intel.com>
---
v2:
1. updated the commit message to declare the issue clearly. (Alex)
2. updated the format of the Fixes: line.
---
 drivers/vfio/vfio.c | 3 +++
 1 file changed, 3 insertions(+)

```
#### [PATCH v2] vfio: fix a missed vfio group put in vfio_pin_pages
##### From: Yan Zhao <yan.y.zhao@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yan Zhao <yan.y.zhao@intel.com>
X-Patchwork-Id: 11778737
Return-Path: <SRS0=aKWm=CZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7678C746
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 16 Sep 2020 02:48:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6389621D1B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 16 Sep 2020 02:48:42 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726281AbgIPCsf (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 15 Sep 2020 22:48:35 -0400
Received: from mga02.intel.com ([134.134.136.20]:2896 "EHLO mga02.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726210AbgIPCsd (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 15 Sep 2020 22:48:33 -0400
IronPort-SDR: 
 zWFSai//FLqwvbK4zcnyHX3bMikozgDLxaYtsl3t//4c1GGnYs+MslK7Daqh7kUaawx4KPX1zU
 O+sv2HVTU/ew==
X-IronPort-AV: E=McAfee;i="6000,8403,9745"; a="147080375"
X-IronPort-AV: E=Sophos;i="5.76,431,1592895600";
   d="scan'208";a="147080375"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by orsmga101.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 15 Sep 2020 19:48:32 -0700
IronPort-SDR: 
 uBOb0byliZpJTD2s+egSk+nmACoZs5vHfD96uvAiu9R+FRNjVUSvmt8O5+ceRifFEPlcapu0Wt
 k7Cb3pRXwM4A==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.76,431,1592895600";
   d="scan'208";a="335876270"
Received: from joy-optiplex-7040.sh.intel.com ([10.239.13.16])
  by orsmga008.jf.intel.com with ESMTP; 15 Sep 2020 19:48:31 -0700
From: Yan Zhao <yan.y.zhao@intel.com>
To: alex.williamson@redhat.com, cohuck@redhat.com
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Yan Zhao <yan.y.zhao@intel.com>
Subject: [PATCH v2] vfio: fix a missed vfio group put in vfio_pin_pages
Date: Wed, 16 Sep 2020 10:29:27 +0800
Message-Id: <20200916022927.26359-1-yan.y.zhao@intel.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

when error occurs, need to put vfio group after a successful get.

Fixes: 95fc87b44104 ("vfio: Selective dirty page tracking if IOMMU backed device pins pages")

Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Signed-off-by: Yan Zhao <yan.y.zhao@intel.com>
---
v2: updated the format of the Fixes: line. (Cornelia)
---
 drivers/vfio/vfio.c | 6 ++++--
 1 file changed, 4 insertions(+), 2 deletions(-)

```
#### [PATCH v2] vfio/type1: fix dirty bitmap calculation in vfio_dma_rw
##### From: Yan Zhao <yan.y.zhao@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yan Zhao <yan.y.zhao@intel.com>
X-Patchwork-Id: 11778739
Return-Path: <SRS0=aKWm=CZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 42096746
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 16 Sep 2020 02:49:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3292A21D1B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 16 Sep 2020 02:49:27 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726336AbgIPCtO (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 15 Sep 2020 22:49:14 -0400
Received: from mga01.intel.com ([192.55.52.88]:28355 "EHLO mga01.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726303AbgIPCtM (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 15 Sep 2020 22:49:12 -0400
IronPort-SDR: 
 xgG/nhkpj4Jmxi+OZzRFOPeTW5MeAvR6Oi/phP27sGMj8/mn+dXq7gq4ZzUWGKfoVVfLudyldv
 u7T+l2fGEinw==
X-IronPort-AV: E=McAfee;i="6000,8403,9745"; a="177461390"
X-IronPort-AV: E=Sophos;i="5.76,431,1592895600";
   d="scan'208";a="177461390"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by fmsmga101.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 15 Sep 2020 19:49:10 -0700
IronPort-SDR: 
 w0sYBVSvEv+bHfmTysoiFCFjCw7rmZLj8JPZJQOXsGKDwg4yEwl/JOldE3hth9Eoho6npBSSXT
 PgVlZpLRRqug==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.76,431,1592895600";
   d="scan'208";a="335876367"
Received: from joy-optiplex-7040.sh.intel.com ([10.239.13.16])
  by orsmga008.jf.intel.com with ESMTP; 15 Sep 2020 19:49:09 -0700
From: Yan Zhao <yan.y.zhao@intel.com>
To: alex.williamson@redhat.com, cohuck@redhat.com
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Yan Zhao <yan.y.zhao@intel.com>
Subject: [PATCH v2] vfio/type1: fix dirty bitmap calculation in vfio_dma_rw
Date: Wed, 16 Sep 2020 10:30:05 +0800
Message-Id: <20200916023005.26414-1-yan.y.zhao@intel.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

the count of dirtied pages is not only determined by count of copied
pages, but also by the start offset.

e.g. if offset = PAGE_SIZE - 1, and *copied=2, the dirty pages count is
2, instead of 1 or 0.

Fixes: d6a4c185660c ("vfio iommu: Implementation of ioctl for dirty pages tracking")

Signed-off-by: Yan Zhao <yan.y.zhao@intel.com>
---
v2: updated the format of the Fixes: line.
---
 drivers/vfio/vfio_iommu_type1.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
