#### [RESEND v4 1/2] KVM: VMX: Convert vcpu_vmx.exit_reason to a union
##### From: Chenyi Qiang <chenyi.qiang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Chenyi Qiang <chenyi.qiang@intel.com>
X-Patchwork-Id: 11831533
Return-Path: <SRS0=greB=DT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DFF66139F
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 12 Oct 2020 03:33:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C54552078A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 12 Oct 2020 03:33:42 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727425AbgJLDdg (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 11 Oct 2020 23:33:36 -0400
Received: from mga04.intel.com ([192.55.52.120]:62772 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727389AbgJLDdf (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 11 Oct 2020 23:33:35 -0400
IronPort-SDR: 
 v9BuqfNdPFahqocL+rGbptVzmvmlEb6bxHGQocDQMRtx1arQo50UNDHbvLuueTeGEoKhN8D/qX
 WX+9cYWlLblQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9771"; a="163046220"
X-IronPort-AV: E=Sophos;i="5.77,365,1596524400";
   d="scan'208";a="163046220"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga005.jf.intel.com ([10.7.209.41])
  by fmsmga104.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 11 Oct 2020 20:33:33 -0700
IronPort-SDR: 
 7B/9Mh9zjeMcimBH/zjg0HGAG6y6/WoGUxBEazgAjGguP5SDE98IdDvdmPfGZ0hcbBsuSzf3zZ
 TL02JvEJZ3YA==
X-IronPort-AV: E=Sophos;i="5.77,365,1596524400";
   d="scan'208";a="529780086"
Received: from chenyi-pc.sh.intel.com ([10.239.159.72])
  by orsmga005-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 11 Oct 2020 20:33:30 -0700
From: Chenyi Qiang <chenyi.qiang@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Xiaoyao Li <xiaoyao.li@intel.com>
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [RESEND v4 1/2] KVM: VMX: Convert vcpu_vmx.exit_reason to a union
Date: Mon, 12 Oct 2020 11:35:41 +0800
Message-Id: <20201012033542.4696-2-chenyi.qiang@intel.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20201012033542.4696-1-chenyi.qiang@intel.com>
References: <20201012033542.4696-1-chenyi.qiang@intel.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Sean Christopherson <sean.j.christopherson@intel.com>

Convert vcpu_vmx.exit_reason from a u32 to a union (of size u32).  The
full VM_EXIT_REASON field is comprised of a 16-bit basic exit reason in
bits 15:0, and single-bit modifiers in bits 31:16.

Historically, KVM has only had to worry about handling the "failed
VM-Entry" modifier, which could only be set in very specific flows and
required dedicated handling.  I.e. manually stripping the FAILED_VMENTRY
bit was a somewhat viable approach.  But even with only a single bit to
worry about, KVM has had several bugs related to comparing a basic exit
reason against the full exit reason store in vcpu_vmx.

Upcoming Intel features, e.g. SGX, will add new modifier bits that can
be set on more or less any VM-Exit, as opposed to the significantly more
restricted FAILED_VMENTRY, i.e. correctly handling everything in one-off
flows isn't scalable.  Tracking exit reason in a union forces code to
explicitly choose between consuming the full exit reason and the basic
exit, and is a convenient way to document and access the modifiers.

No functional change intended.

Cc: Xiaoyao Li <xiaoyao.li@intel.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/vmx/nested.c | 42 ++++++++++++++++---------
 arch/x86/kvm/vmx/vmx.c    | 66 ++++++++++++++++++++-------------------
 arch/x86/kvm/vmx/vmx.h    | 25 ++++++++++++++-
 3 files changed, 85 insertions(+), 48 deletions(-)

```
#### [PATCH v3 1/4] selftests: kvm: Fix the segment descriptor layout to match the actual layout
##### From: Aaron Lewis <aaronlewis@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Aaron Lewis <aaronlewis@google.com>
X-Patchwork-Id: 11833653
Return-Path: <SRS0=greB=DT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E4B00139F
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 12 Oct 2020 19:47:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BFE6520797
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 12 Oct 2020 19:47:41 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="VbYCilhz"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2391468AbgJLTrj (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 12 Oct 2020 15:47:39 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:59900 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2391283AbgJLTrj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 12 Oct 2020 15:47:39 -0400
Received: from mail-pl1-x64a.google.com (mail-pl1-x64a.google.com
 [IPv6:2607:f8b0:4864:20::64a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id AE2E5C0613D1
        for <kvm@vger.kernel.org>; Mon, 12 Oct 2020 12:47:37 -0700 (PDT)
Received: by mail-pl1-x64a.google.com with SMTP id v6so12593891plo.3
        for <kvm@vger.kernel.org>; Mon, 12 Oct 2020 12:47:37 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:in-reply-to:message-id:mime-version:references:subject
         :from:to:cc;
        bh=kRLElTJYruy9BhLgGAtIqt00VI4hnTdleImYdQGJD0s=;
        b=VbYCilhzAh5d75jt1/Rw6IKq31I6bNJFp6cHs1XQNsyBaYBqeeBxEkKtocNPrtcP0Z
         +w7CfXSo3bcsAPsj6fGJtysBZpZBhE1f+xBDx5ZP+qcXiSXJQhZrSDI1uebrNrnataKz
         +7XWoXogA9gFu4cCIsoTjymFVLzL/yG60NvjsSyEjDrDgMLIyPrYjr+L4pt7cK0Rf6Ye
         DdxXp1zx+hfzd9YgD17pETaYiKjBLCFVDV6QfKIFzEHZH8jnQRclkXo2kaw9zJP6kIk4
         iV7UPrHJpUJ3PdXCrR4rhkFGeOJk2AGgeESptIG6mujHn0YcaEchg+d1mOLDHOYi0sNs
         8cvw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=kRLElTJYruy9BhLgGAtIqt00VI4hnTdleImYdQGJD0s=;
        b=nhiW3/2JnYtDALW5gdTqOJtRF9Ppv8q+etmFovCn6GMNg3qQP+uE+N1t1o0TwW0ICV
         3Z3+uyuvl/0b337duT4bcVxMU30XagX5QGTjzml4PHTa4tHqjr99RR3EP7QIUTq9kNE4
         Y09axxjerRGypEigSziVcVa6sGLnXUkdSuMpTZrauXnseYrbxEgal03Z4lKS8/iUD4o6
         V4RIN5g6p2ESBTvTI6aMWwnmUeTsvi0N2x1C9BP9x0qCyZLnkiIrWjinAH76es39jrXP
         CUoexvs8HeX0ArfXtfUX0v/ebycp/kZdSAQvN9ypMaTAnfq76Mu2bzsIZxX+PDPg3Ze0
         LbKw==
X-Gm-Message-State: AOAM533Go0Qcm37y7VdUeQwGgs5pu0tAA6TkmJbI0q400Tqy481OE+dd
        eMtkxVTXEPHlIjwVllWhtZPysxDNdcDuZ/Ji
X-Google-Smtp-Source: 
 ABdhPJw8LETdjBiV9xMt/ibGjAUwIHaHuLJo2byCuH/Tr//Hlh5fn1CGAP0/0JWCDMwrxSK+PfRE/sRRTkY+XkcU
Sender: "aaronlewis via sendgmr" <aaronlewis@aaronlewis1.sea.corp.google.com>
X-Received: from aaronlewis1.sea.corp.google.com
 ([2620:15c:100:202:a28c:fdff:fed8:8d46])
 (user=aaronlewis job=sendgmr) by 2002:a17:90b:4b8a:: with SMTP id
 lr10mr11547252pjb.217.1602532057197; Mon, 12 Oct 2020 12:47:37 -0700 (PDT)
Date: Mon, 12 Oct 2020 12:47:13 -0700
In-Reply-To: <20201012194716.3950330-1-aaronlewis@google.com>
Message-Id: <20201012194716.3950330-2-aaronlewis@google.com>
Mime-Version: 1.0
References: <20201012194716.3950330-1-aaronlewis@google.com>
X-Mailer: git-send-email 2.28.0.1011.ga647a8990f-goog
Subject: [PATCH v3 1/4] selftests: kvm: Fix the segment descriptor layout to
 match the actual layout
From: Aaron Lewis <aaronlewis@google.com>
To: graf@amazon.com
Cc: pshier@google.com, jmattson@google.com, kvm@vger.kernel.org,
        Aaron Lewis <aaronlewis@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Fix the layout of 'struct desc64' to match the layout described in the
SDM Vol 3, Chapter 3 "Protected-Mode Memory Management", section 3.4.5
"Segment Descriptors", Figure 3-8 "Segment Descriptor".  The test added
later in this series relies on this and crashes if this layout is not
correct.

Signed-off-by: Aaron Lewis <aaronlewis@google.com>
Reviewed-by: Alexander Graf <graf@amazon.com>
---
 tools/testing/selftests/kvm/include/x86_64/processor.h | 2 +-
 tools/testing/selftests/kvm/lib/x86_64/processor.c     | 3 ++-
 2 files changed, 3 insertions(+), 2 deletions(-)

```
