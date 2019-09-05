#### [PATCH] KVM: s390: Disallow invalid bits in kvm_valid_regs and kvm_dirty_regs
##### From: Thomas Huth <thuth@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Huth <thuth@redhat.com>
X-Patchwork-Id: 11129493
Return-Path: <SRS0=1IPj=W7=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 498A613B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  4 Sep 2019 07:13:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 2B1602087E
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  4 Sep 2019 07:13:19 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728796AbfIDHNP (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 4 Sep 2019 03:13:15 -0400
Received: from mx1.redhat.com ([209.132.183.28]:37176 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725938AbfIDHNP (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 4 Sep 2019 03:13:15 -0400
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id D88157CBB1;
        Wed,  4 Sep 2019 07:13:14 +0000 (UTC)
Received: from thuth.com (ovpn-116-69.ams2.redhat.com [10.36.116.69])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 0339D1001B1A;
        Wed,  4 Sep 2019 07:13:12 +0000 (UTC)
From: Thomas Huth <thuth@redhat.com>
To: kvm@vger.kernel.org,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Janosch Frank <frankja@linux.ibm.com>
Cc: David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>, linux-s390@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: s390: Disallow invalid bits in kvm_valid_regs and
 kvm_dirty_regs
Date: Wed,  4 Sep 2019 09:13:08 +0200
Message-Id: <20190904071308.25683-1-thuth@redhat.com>
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.5.16 (mx1.redhat.com [10.5.110.26]);
 Wed, 04 Sep 2019 07:13:14 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If unknown bits are set in kvm_valid_regs or kvm_dirty_regs, this
clearly indicates that something went wrong in the KVM userspace
application. The x86 variant of KVM already contains a check for
bad bits (and the corresponding kselftest checks this), so let's
do the same on s390x now, too.

Signed-off-by: Thomas Huth <thuth@redhat.com>
Reviewed-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Christian Borntraeger <borntraeger@de.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---
 arch/s390/include/uapi/asm/kvm.h              |  6 ++++
 arch/s390/kvm/kvm-s390.c                      |  4 +++
 .../selftests/kvm/s390x/sync_regs_test.c      | 30 +++++++++++++++++++
 3 files changed, 40 insertions(+)

```
#### [Patch] KVM: SVM: Fix svm_xsaves_supportedFrom: Aaron Lewis <aaronlewis@google.com>
##### From: Aaron Lewis <aaronlewis@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Aaron Lewis <aaronlewis@google.com>
X-Patchwork-Id: 11129079
Return-Path: <SRS0=1IPj=W7=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5F7E814E5
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  4 Sep 2019 00:15:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 31B6F22CED
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  4 Sep 2019 00:15:05 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="mQmP8yLi"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727423AbfIDAOy (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 3 Sep 2019 20:14:54 -0400
Received: from mail-ua1-f73.google.com ([209.85.222.73]:46023 "EHLO
        mail-ua1-f73.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726105AbfIDAOy (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 3 Sep 2019 20:14:54 -0400
Received: by mail-ua1-f73.google.com with SMTP id 34so2185152uak.12
        for <kvm@vger.kernel.org>; Tue, 03 Sep 2019 17:14:53 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc
         :content-transfer-encoding;
        bh=gddY9rXfy1o/BJAVc6NV/dzZ1eIgz23K6mAhrOnns6o=;
        b=mQmP8yLidRKsOA6YGterIhvm71km1533ZKZH5XuU0t2XnmLxal0PYJXgij40loF5xa
         lURGeeKQe0Sc2V3aYWXwYWjnbrtnLOSFm79r8ZzIqdUgLYU7vvpIrj8FokAz4LInIgjX
         vn0x77A+Z0+czO6/ScPkTAZYs2sE+/bjOryLAGurBQrWgBxYhUf772Unla2XNINnNosQ
         KrXRQLpEhmZa6zFV27mSQH0QPJdKT756iEfBb7TAlg0XOdvaFciWDGclwqWrNENB5Lrj
         S4N8w+Krs9+WorvRzstVvq+jIBsOVWFpmzwvRnbNWqMa7c+78m+h+T7G5mPdMfUHodQP
         ++Lw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc
         :content-transfer-encoding;
        bh=gddY9rXfy1o/BJAVc6NV/dzZ1eIgz23K6mAhrOnns6o=;
        b=DwcV1urIAAGGnipoQE5QGVK+ooV/KkbbLYLE+tQAq3nvKlXSja7EIry607Yi7qb+g+
         n6hbtmpVbgJHdcNnKPmwzxd52fRRWVFR0+lHgP7MZwzSmqr2Pb+NKz8nl1fDTP07xP3M
         gdCRhqykyjsxvUFMrGQIUoers3mSixI1eJFOBPsH03gvuDZZEQm9XA8XJAXCXolc75bC
         Z0LxBT6FLzgoK/9KLRQiGFOYezo1FA59oGDXxF6a7RBQOWW269ohBTlngF+OupTkRe9s
         mF/kapbcdEJyrseeHpjE5kcgudZG6a3w8ssbjdcBZAi93cCPIpVMbzUIrkbRA1xLFiGv
         Cu4w==
X-Gm-Message-State: APjAAAWWHFts11X/t61DtgolvwGLZqseOTd3VQthWQhQQT6OTLDxOScY
        3vvh8HizkH642B/s1DmY5wpMCmJrloFjSNityUh0zLyq5CvbgBptX3I9otAqyR7a/dAUxcYwLoC
        VaXooXXFbC3JBp+EdH/kqhuyu8aqiqN7ZmNTZwDco38cpcif/LyEdHJOKQ/5P0JcfOfMJ
X-Google-Smtp-Source: 
 APXvYqxzziA5JgqUEnZXByq+rnJeFb6VsrtjTq1mmKSs5vX1/rGddkQjZJz+Gw9WO48+GE7WS/t9Udary57+I1V9
X-Received: by 2002:ab0:1c0b:: with SMTP id a11mr7245696uaj.65.1567556093218;
 Tue, 03 Sep 2019 17:14:53 -0700 (PDT)
Date: Tue,  3 Sep 2019 17:14:22 -0700
Message-Id: <20190904001422.11809-1-aaronlewis@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.23.0.187.g17f5b7556c-goog
Subject: [Patch] KVM: SVM: Fix svm_xsaves_supported
From: Aaron Lewis <aaronlewis@google.com>
To: kvm@vger.kernel.org
Cc: Janakarajan.Natarajan@amd.com, jmattson@google.com,
        Aaron Lewis <aaronlewis@google.com>
Content-Type: text/plain; charset="UTF-8"
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

AMD allows guests to execute XSAVES/XRSTORS if supported by the host.  This is different than Intel as they have an additional control bit that determines if XSAVES/XRSTORS can be used by the guest. Intel also has intercept bits that might prevent the guest from intercepting the instruction as well. AMD has none of that, not even an Intercept mechanism.  AMD simply allows XSAVES/XRSTORS to be executed by the guest if also supported by the host.

Signed-off-by: Aaron Lewis <aaronlewis@google.com>
---
 arch/x86/kvm/svm.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v2] doc: kvm: Fix return description of KVM_SET_MSRS
##### From: Xiaoyao Li <xiaoyao.li@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xiaoyao Li <xiaoyao.li@intel.com>
X-Patchwork-Id: 11129381
Return-Path: <SRS0=1IPj=W7=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4C3531398
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  4 Sep 2019 06:15:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 35F8F2341D
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  4 Sep 2019 06:15:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728849AbfIDGP4 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 4 Sep 2019 02:15:56 -0400
Received: from mga05.intel.com ([192.55.52.43]:60359 "EHLO mga05.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725938AbfIDGP4 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 4 Sep 2019 02:15:56 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga007.jf.intel.com ([10.7.209.58])
  by fmsmga105.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 03 Sep 2019 23:15:55 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.64,465,1559545200";
   d="scan'208";a="173462883"
Received: from lxy-clx-4s.sh.intel.com ([10.239.43.44])
  by orsmga007.jf.intel.com with ESMTP; 03 Sep 2019 23:15:53 -0700
From: Xiaoyao Li <xiaoyao.li@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>
Cc: Xiaoyao Li <xiaoyao.li@intel.com>,
        Jonathan Corbet <corbet@lwn.net>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        kvm@vger.kernel.org, linux-doc@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v2] doc: kvm: Fix return description of KVM_SET_MSRS
Date: Wed,  4 Sep 2019 14:01:18 +0800
Message-Id: <20190904060118.43851-1-xiaoyao.li@intel.com>
X-Mailer: git-send-email 2.19.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Userspace can use ioctl KVM_SET_MSRS to update a set of MSRs of guest.
This ioctl sets specified MSRs one by one. Once it fails to set an MSR
due to setting reserved bits, the MSR is not supported/emulated by kvm,
or violating other restrictions, it stops further processing and returns
the number of MSRs have been set successfully.

Signed-off-by: Xiaoyao Li <xiaoyao.li@intel.com>
---
v2:
  elaborate the changelog and description of ioctl KVM_SET_MSRS based on
  Sean's comments.

---
 Documentation/virt/kvm/api.txt | 7 ++++++-
 1 file changed, 6 insertions(+), 1 deletion(-)

```
