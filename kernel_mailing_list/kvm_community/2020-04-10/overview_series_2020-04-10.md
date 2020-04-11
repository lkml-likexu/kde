#### [PATCH v25 01/10] acpi: nvdimm: change NVDIMM_UUID_LE to a common macro
##### From: Dongjiu Geng <gengdongjiu@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Dongjiu Geng <gengdongjiu@huawei.com>
X-Patchwork-Id: 11483163
Return-Path: <SRS0=vRYM=52=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CD5621744
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Apr 2020 11:45:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B88D52084D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Apr 2020 11:45:33 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726626AbgDJLpc (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 10 Apr 2020 07:45:32 -0400
Received: from szxga06-in.huawei.com ([45.249.212.32]:52028 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726111AbgDJLpb (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 10 Apr 2020 07:45:31 -0400
Received: from DGGEMS401-HUB.china.huawei.com (unknown [172.30.72.58])
        by Forcepoint Email with ESMTP id 51EEFEFCBB7CCB18A091;
        Fri, 10 Apr 2020 19:45:27 +0800 (CST)
Received: from huawei.com (10.151.151.243) by DGGEMS401-HUB.china.huawei.com
 (10.3.19.201) with Microsoft SMTP Server id 14.3.487.0; Fri, 10 Apr 2020
 19:45:17 +0800
From: Dongjiu Geng <gengdongjiu@huawei.com>
To: <imammedo@redhat.com>, <mst@redhat.com>,
        <xiaoguangrong.eric@gmail.com>, <peter.maydell@linaro.org>,
        <shannon.zhaosl@gmail.com>, <fam@euphon.net>, <rth@twiddle.net>,
        <ehabkost@redhat.com>, <mtosatti@redhat.com>,
        <qemu-devel@nongnu.org>, <kvm@vger.kernel.org>,
        <qemu-arm@nongnu.org>, <pbonzini@redhat.com>
CC: <gengdongjiu@huawei.com>, <zhengxiang9@huawei.com>,
        <Jonathan.Cameron@huawei.com>, <linuxarm@huawei.com>
Subject: [PATCH v25 01/10] acpi: nvdimm: change NVDIMM_UUID_LE to a common
 macro
Date: Fri, 10 Apr 2020 19:46:30 +0800
Message-ID: <20200410114639.32844-2-gengdongjiu@huawei.com>
X-Mailer: git-send-email 2.18.0.huawei.25
In-Reply-To: <20200410114639.32844-1-gengdongjiu@huawei.com>
References: <20200410114639.32844-1-gengdongjiu@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.151.151.243]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The little end UUID is used in many places, so make
NVDIMM_UUID_LE to a common macro to convert the UUID
to a little end array.

Reviewed-by: Xiang Zheng <zhengxiang9@huawei.com>
Signed-off-by: Dongjiu Geng <gengdongjiu@huawei.com>
---
 hw/acpi/nvdimm.c    | 10 +++-------
 include/qemu/uuid.h |  9 +++++++++
 2 files changed, 12 insertions(+), 7 deletions(-)

```
#### [PATCH] KVM: remove redundant assignment to variable r
##### From: Colin King <colin.king@canonical.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Colin King <colin.king@canonical.com>
X-Patchwork-Id: 11483155
Return-Path: <SRS0=vRYM=52=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F105F17D4
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Apr 2020 11:35:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id DA1E920787
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Apr 2020 11:35:43 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726648AbgDJLf2 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 10 Apr 2020 07:35:28 -0400
Received: from youngberry.canonical.com ([91.189.89.112]:33812 "EHLO
        youngberry.canonical.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725913AbgDJLf2 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 10 Apr 2020 07:35:28 -0400
Received: from 1.general.cking.uk.vpn ([10.172.193.212] helo=localhost)
        by youngberry.canonical.com with esmtpsa
 (TLS1.2:ECDHE_RSA_AES_128_GCM_SHA256:128)
        (Exim 4.86_2)
        (envelope-from <colin.king@canonical.com>)
        id 1jMrwU-0008VB-On; Fri, 10 Apr 2020 11:35:26 +0000
From: Colin King <colin.king@canonical.com>
To: Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org
Cc: kernel-janitors@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: remove redundant assignment to variable r
Date: Fri, 10 Apr 2020 12:35:26 +0100
Message-Id: <20200410113526.13822-1-colin.king@canonical.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Colin Ian King <colin.king@canonical.com>

The variable r is being assigned  with a value that is never read
and it is being updated later with a new value.  The initialization is
redundant and can be removed.

Addresses-Coverity: ("Unused value")
Signed-off-by: Colin Ian King <colin.king@canonical.com>
---
 virt/kvm/kvm_main.c | 1 -
 1 file changed, 1 deletion(-)

```
#### [PATCH v2] KVM: X86: Ultra fast single target IPI fastpath
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11482653
Return-Path: <SRS0=vRYM=52=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B740B913
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Apr 2020 01:03:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 8F18C2074F
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Apr 2020 01:03:50 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="NR3LliSb"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726620AbgDJBDq (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 9 Apr 2020 21:03:46 -0400
Received: from mail-pj1-f67.google.com ([209.85.216.67]:50892 "EHLO
        mail-pj1-f67.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725970AbgDJBDq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 9 Apr 2020 21:03:46 -0400
Received: by mail-pj1-f67.google.com with SMTP id b7so214809pju.0;
        Thu, 09 Apr 2020 18:03:44 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=EeQYxbvTeKI2BVQRT2aOOtI1jSNcFNNz19lVdiuGtjo=;
        b=NR3LliSb0NmRvkwkX6K7wUezSIjOzKfP7gJGADD/PBV/nI5KDnJYcAIAn2XL1yimeg
         DJaM77X2BS0toCZ8slmx4/orYPp4iS0+CIIRJnYw6FA/ZtkoV1GSPKYTJCximgbVfhTf
         y8Uf1kpG5VfxMTWRIm/tnHlP7y4wGmapdGxA+WhlksBEaDQ6Db2NBG7pAXkiOPi/zP3q
         vp2tHa3wBKrWwdFNN+24kJfUsjEMdweQSzH29Ran940zdyuWlGzOzfoSDQPm3i2RFPp6
         H0kVBCb6acocj11RZuyWNvRzZMoLvYo3vh7QatbSEFV98mha1e3TKMQnUtnSPwtQxYx1
         xDWw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=EeQYxbvTeKI2BVQRT2aOOtI1jSNcFNNz19lVdiuGtjo=;
        b=GEp2Sma4LqiGuDUNz3FqzE8CtpT+18SHbrUdO1xi82CCQ3QVFHiwBjyD8yMlVXsH4t
         bvF1n9agkBQ+9uisCFVXnt1oWt0yaKsABDNguqUDjfeq3/ZXeTOiWo9DoUvmsFafOQhq
         LTnOeAoIoLiBYsILnllwxNs5aAev2uMOpo1YPdP0VCIkKXMlbweXb+DlcXfi4JvQr3AA
         pRyXbo5jYkHJcybZC4Pql0KNQKZKHp0dz68i6al+0XM6CwpcZQchOnIoHTp4NzWGTrJc
         B2H7Ps/cBMrs/Cc8sv5qEXtxepw6tvFizoJJG3j4dPDZMW8AX7C2iVQ4Y4rnNxK+r6OB
         Tg4A==
X-Gm-Message-State: AGi0PuZ5yptaxeMu67/8yIqe0C4JmLrDPdktrGwAJ9YhIIQaYA+i270X
        QYlD2athGdEaS3MIiGAYW/y8rW+7
X-Google-Smtp-Source: 
 APiQypKyQITZWkM0GCWB3H4MhFYc7wViYWzg3JhzUfyPnV03ktUpOCaa3XqWUdNpP9cVbSVU9INOaw==
X-Received: by 2002:a17:902:968a:: with SMTP id
 n10mr2292044plp.74.1586480623007;
        Thu, 09 Apr 2020 18:03:43 -0700 (PDT)
Received: from localhost.localdomain ([103.7.29.6])
        by smtp.googlemail.com with ESMTPSA id
 y3sm311180pfy.6.2020.04.09.18.03.40
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Thu, 09 Apr 2020 18:03:42 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Haiwei Li <lihaiwei@tencent.com>
Subject: [PATCH v2] KVM: X86: Ultra fast single target IPI fastpath
Date: Fri, 10 Apr 2020 09:03:27 +0800
Message-Id: <1586480607-5408-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

IPI and Timer cause the main MSRs write vmexits in cloud environment 
observation, let's optimize virtual IPI latency more aggressively to 
inject target IPI as soon as possible.

Running kvm-unit-tests/vmexit.flat IPI testing on SKX server, disable 
adaptive advance lapic timer and adaptive halt-polling to avoid the 
interference, this patch can give another 7% improvement.

w/o fastpath -> fastpath            4238 -> 3543  16.4%
fastpath     -> ultra fastpath      3543 -> 3293     7%
w/o fastpath -> ultra fastpath      4238 -> 3293  22.3% 

This also revises the performance data in commit 1e9e2622a1 (KVM: VMX: 
FIXED+PHYSICAL mode single target IPI fastpath), that testing adds
--overcommit cpu-pm=on to kvm-unit-tests guest which is unnecessary.

Tested-by: Haiwei Li <lihaiwei@tencent.com>
Cc: Haiwei Li <lihaiwei@tencent.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
v1 -> v2:
 * rebase on latest kvm/queue
 * update patch description

 arch/x86/include/asm/kvm_host.h |  6 +++---
 arch/x86/kvm/svm/svm.c          | 21 ++++++++++++++-------
 arch/x86/kvm/vmx/vmx.c          | 19 +++++++++++++------
 arch/x86/kvm/x86.c              |  4 ++--
 4 files changed, 32 insertions(+), 18 deletions(-)

```
#### [PATCH v3 1/2] KVM: VMX: Optimize handling of VM-Entry failures in vmx_vcpu_run()
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11483513
Return-Path: <SRS0=vRYM=52=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2D56E14B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Apr 2020 17:47:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 184B820936
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Apr 2020 17:47:15 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726715AbgDJRrH (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 10 Apr 2020 13:47:07 -0400
Received: from mga17.intel.com ([192.55.52.151]:60983 "EHLO mga17.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726203AbgDJRrG (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 10 Apr 2020 13:47:06 -0400
IronPort-SDR: 
 U1WklG+yOS6NE+jMI7UvZ5MHCiD4wcFsOQSSj3OX7lHw3fBIBviNV9W5CR44k09eOfHNbWZWbl
 NeS2TXrA1Mow==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga003.fm.intel.com ([10.253.24.29])
  by fmsmga107.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 10 Apr 2020 10:47:06 -0700
IronPort-SDR: 
 jFSvR6kxcUcRaXKCntyWUbd41j54+6KAo3c4Sif0MehZ4fYwrJ6RvZeiOuiJcXYCxs5zCbLLet
 78CM6ujhyVwA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.72,367,1580803200";
   d="scan'208";a="297857979"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by FMSMGA003.fm.intel.com with ESMTP; 10 Apr 2020 10:47:06 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Haiwei Li <lihaiwei@tencent.com>
Subject: [PATCH v3 1/2] KVM: VMX: Optimize handling of VM-Entry failures in
 vmx_vcpu_run()
Date: Fri, 10 Apr 2020 10:47:02 -0700
Message-Id: <20200410174703.1138-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
In-Reply-To: <20200410174703.1138-1-sean.j.christopherson@intel.com>
References: <f51251cc-885e-2f7a-b18d-faa76db15b87@redhat.com>
 <20200410174703.1138-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Mark the VM-Fail, VM-Exit on VM-Enter, and #MC on VM-Enter paths as
'unlikely' so as to improve code generation so that it favors successful
VM-Enter.  The performance of successful VM-Enter is for more important,
irrespective of whether or not success is actually likely.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/vmx/vmx.c | 11 ++++++++---
 1 file changed, 8 insertions(+), 3 deletions(-)

```
