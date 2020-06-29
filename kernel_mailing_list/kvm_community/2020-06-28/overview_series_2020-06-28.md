#### [RFC 1/2] KVM: VMX: Convert vcpu_vmx.exit_reason to a union
##### From: Chenyi Qiang <chenyi.qiang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Chenyi Qiang <chenyi.qiang@intel.com>
X-Patchwork-Id: 11629973
Return-Path: <SRS0=5eI3=AJ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6F160913
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 28 Jun 2020 08:52:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5669220771
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 28 Jun 2020 08:52:17 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726225AbgF1IwK (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 28 Jun 2020 04:52:10 -0400
Received: from mga05.intel.com ([192.55.52.43]:43712 "EHLO mga05.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726069AbgF1IwK (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 28 Jun 2020 04:52:10 -0400
IronPort-SDR: 
 bZnYokrGsci9InTmZuN6r7mW7+i9vYK5hMqEyd2TAiuiZcRgVbKCGPPZ9vehu05kRCbTqATYBM
 /o4grOJ/xHRQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9665"; a="230601061"
X-IronPort-AV: E=Sophos;i="5.75,291,1589266800";
   d="scan'208";a="230601061"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga005.fm.intel.com ([10.253.24.32])
  by fmsmga105.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 28 Jun 2020 01:52:02 -0700
IronPort-SDR: 
 NWHtWFjP8jbhmT979AhDkD48dnFVFp4DVHmXsOuYT67QS27izzPYtkdWxpu9vIeaR7O3d4R/hV
 1H83KsjyuSkw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,291,1589266800";
   d="scan'208";a="480457292"
Received: from chenyi-pc.sh.intel.com ([10.239.159.72])
  by fmsmga005.fm.intel.com with ESMTP; 28 Jun 2020 01:51:59 -0700
From: Chenyi Qiang <chenyi.qiang@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Xiaoyao Li <xiaoyao.li@intel.com>
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [RFC 1/2] KVM: VMX: Convert vcpu_vmx.exit_reason to a union
Date: Sun, 28 Jun 2020 16:53:40 +0800
Message-Id: <20200628085341.5107-2-chenyi.qiang@intel.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200628085341.5107-1-chenyi.qiang@intel.com>
References: <20200628085341.5107-1-chenyi.qiang@intel.com>
Sender: kvm-owner@vger.kernel.org
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
 arch/x86/kvm/vmx/vmx.c    | 64 ++++++++++++++++++++-------------------
 arch/x86/kvm/vmx/vmx.h    | 25 ++++++++++++++-
 3 files changed, 84 insertions(+), 47 deletions(-)

```
