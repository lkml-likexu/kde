#### [kvm-unit-tests PATCH v3] x86: Add RDTSC testFrom: Aaron Lewis <aaronlewis@google.com>
##### From: Aaron Lewis <aaronlewis@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Aaron Lewis <aaronlewis@google.com>
X-Patchwork-Id: 11269921
Return-Path: <SRS0=t74V=ZY=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 343DB6C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  2 Dec 2019 20:45:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 094A420848
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  2 Dec 2019 20:45:19 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="qMSQaNdV"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725838AbfLBUpS (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 2 Dec 2019 15:45:18 -0500
Received: from mail-pg1-f201.google.com ([209.85.215.201]:46198 "EHLO
        mail-pg1-f201.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725775AbfLBUpR (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 2 Dec 2019 15:45:17 -0500
Received: by mail-pg1-f201.google.com with SMTP id p21so383872pgh.13
        for <kvm@vger.kernel.org>; Mon, 02 Dec 2019 12:45:17 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc
         :content-transfer-encoding;
        bh=QYhac3r55bAEwLqoDrUzbjmy450chfvsZZ2g9rcvJrc=;
        b=qMSQaNdVGB8yVApYDZlGuMkFVrepNOumH+MCFMV1tmWZ2GhNJxnx5olgGuUkdxXPlP
         EoGxDgd8d9L6nyDWDoHD/dfkmrzdIoY88kKhZJQpjijJjQwNxxQDAs7KxskNCYJH7yOF
         +ujb0Y3TBlCRnM7qqIEQwYrGx6o0CIOUHbw7CBl9BH5hvKYFDx4oK1CmZDDo6YHqHuop
         Ox304NyiydYFATEH8VUOFxh/4qQjVdUDHwZTfPNRmP0SDZNtdmb6tC0vyX5E0BN3rGlW
         0QhsbD08zze8EpuKd6xEycGZixH9n8P2NFyOpTJ0ESuyobIW/WF2YNW3l9Rmx6Bm2dVH
         hadQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc
         :content-transfer-encoding;
        bh=QYhac3r55bAEwLqoDrUzbjmy450chfvsZZ2g9rcvJrc=;
        b=IyJxDkcddWOXYgNU00A6O316YMUi8bPWVFjx1hRIK4qfKgwmtnKpR3qbUpMWebz5rd
         rLqQDAHo96ljhWs1+qX3dXhrmalgiGJ2dBPiUk3WuqAtDuAEfqfgquCKKnOXFKKUgSEF
         fen58Hn2ijyVE1OzcF1jyGjaiH4rRdZwGloN7tD4mUBK40DYpOCd7GE5+MMy6wIWvOsG
         1geEUrWnGKmijL0Nj1SnbuWJdsXgTDWZNdlA65jH28eSHO2s0QIsgT7LtfSV/2GjoJB7
         WOMQsvqVHLIqhjtW5meBVIDemEQA315yfliBQcNGxvqygNMCwaD615vZq5UJk289zhGG
         NZow==
X-Gm-Message-State: APjAAAULlKk3yP17YS8olZQIIZ4fLD50BQcWehZEBhfXvyPiBRwM9Awl
        JV2nOzQB4/xCZrOiky21cPmrQgB2Cmn3Ay6UYFLzbxEtdhA3z9zGH89mUnYMGVd8r8z4H/EKhCE
        iuyFvQ+S7RXi6IInDGfulrPFUPBdZmEW5AL/78shMGt1PRjQ34hfvOyBPi8TWHKC6NXcr
X-Google-Smtp-Source: 
 APXvYqwW55eUIQmXY1HOXBdQ+5wSfD+IYy5lIFvfsLgfmdvLs/5xkHMzMy5melgrhbVDCM/aybzuprdL2aSvLyiH
X-Received: by 2002:a63:f006:: with SMTP id k6mr1090977pgh.380.1575319516240;
 Mon, 02 Dec 2019 12:45:16 -0800 (PST)
Date: Mon,  2 Dec 2019 12:43:57 -0800
Message-Id: <20191202204356.250357-1-aaronlewis@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.24.0.393.g34dc348eaf-goog
Subject: [kvm-unit-tests PATCH v3] x86: Add RDTSC test
From: Aaron Lewis <aaronlewis@google.com>
To: kvm@vger.kernel.org
Cc: Jim Mattson <jmattson@google.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Liran Alon <liran.alon@oracle.com>,
        Aaron Lewis <aaronlewis@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Verify that the difference between a guest RDTSC instruction and the
IA32_TIME_STAMP_COUNTER MSR value stored in the VMCS12's VM-exit
MSR-store list is less than 750 cycles, 99.9% of the time.

662f1d1d1931 ("KVM: nVMX: Add support for capturing highest observable L2 TSC”)

Signed-off-by: Aaron Lewis <aaronlewis@google.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 x86/vmx.h       |  1 +
 x86/vmx_tests.c | 93 +++++++++++++++++++++++++++++++++++++++++++++++++
 2 files changed, 94 insertions(+)

```
#### [PATCH v3 1/5] KVM: X86: Fix kvm_bitmap_or_dest_vcpus() to use irq shorthand
##### From: Peter Xu <peterx@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11269887
Return-Path: <SRS0=t74V=ZY=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E6276109A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  2 Dec 2019 20:13:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id C4A0021835
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  2 Dec 2019 20:13:51 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="TqtI2P+F"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728143AbfLBUN0 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 2 Dec 2019 15:13:26 -0500
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:20166 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1728099AbfLBUNV (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 2 Dec 2019 15:13:21 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1575317600;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=1fy9n7dcmvJgMCcJNV0TpfIBPUc+H1bj0IMdTlJT67Y=;
        b=TqtI2P+Fa1oxnOT/+wionTMWgXLs0df7qaJX9auauAp+SZ2jtrOMRpUixWEiVv5Jjm1PW4
        oNKGgd0m2nyYMTu65/hXtw0zpIIZrLMlZNI4oH9q4zEStCy7Epmy9gWdKJM2AAKDWOUwbL
        +imrhyakofO/2vUyxzCTCOtzvOPYui4=
Received: from mail-qt1-f200.google.com (mail-qt1-f200.google.com
 [209.85.160.200]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-274-LNhikmsIO3yBFeFmnZLXVw-1; Mon, 02 Dec 2019 15:13:18 -0500
Received: by mail-qt1-f200.google.com with SMTP id k27so689414qtu.12
        for <kvm@vger.kernel.org>; Mon, 02 Dec 2019 12:13:18 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=G46phdLsdELb62aYURKq9FYQ6hJlvcecU9Mkr0WukfA=;
        b=IUzhoBEwQm9Hh27iedzaGWxAt/e2DpfMmelFj3xpzz078YWZyXLjPP03NSsVocMZ+V
         j4ofBMEZ88ZH5FeG5mSXKsJThafooLnfqtWVUSyI2Q+Pk62pl5iv3f73xjuSxgRBlFhH
         qVDnxRv0hx45TMJUBKMkdJ9qCkZ2/G5KFMPfODp+6IQmuPuNvfgo9TDt0qJTvPPZciNB
         /VTpmT//8KZQYTSrTnNMGnSb2aqoYstX5yB+RYXcK37LNv+CMZzZtT0cJ6tuWfP5nXMi
         XLJci5QlygeimEov5wt/sU/KYtXoPkJps+QwgPt4Jiq5jw9CHJaef7gpbMxP/ktliQZY
         /3lg==
X-Gm-Message-State: APjAAAW8EnIeuW60sWoCHka4wZx+OQhVwfk/rJHV8orcimxPr9+hbk0l
        emUIymv4Aj7ZYftiTaj9MfM7myEj3mln536thiod3Qm7t+u8hK89NsoIZ901ipVR6sZ2UJpzTTt
        NYD4m7FKe529x
X-Received: by 2002:a37:8fc7:: with SMTP id r190mr802090qkd.57.1575317598022;
        Mon, 02 Dec 2019 12:13:18 -0800 (PST)
X-Google-Smtp-Source: 
 APXvYqyyXV9FRZwo488kcpWWx8NKtpTc+Mn5z7ZJGiXXUVERX6ZlH3itwmcb06sFXIkKThyWsyuWdw==
X-Received: by 2002:a37:8fc7:: with SMTP id r190mr802057qkd.57.1575317597756;
        Mon, 02 Dec 2019 12:13:17 -0800 (PST)
Received: from xz-x1.yyz.redhat.com ([104.156.64.74])
        by smtp.gmail.com with ESMTPSA id b6sm342410qtp.5.2019.12.02.12.13.16
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 02 Dec 2019 12:13:16 -0800 (PST)
From: Peter Xu <peterx@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Nitesh Narayan Lal <nitesh@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        peterx@redhat.com, Vitaly Kuznetsov <vkuznets@redhat.com>
Subject: [PATCH v3 1/5] KVM: X86: Fix kvm_bitmap_or_dest_vcpus() to use irq
 shorthand
Date: Mon,  2 Dec 2019 15:13:10 -0500
Message-Id: <20191202201314.543-2-peterx@redhat.com>
X-Mailer: git-send-email 2.21.0
In-Reply-To: <20191202201314.543-1-peterx@redhat.com>
References: <20191202201314.543-1-peterx@redhat.com>
MIME-Version: 1.0
X-MC-Unique: LNhikmsIO3yBFeFmnZLXVw-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The 3rd parameter of kvm_apic_match_dest() is the irq shorthand,
rather than the irq delivery mode.

Fixes: 7ee30bc132c683d06a6d9e360e39e483e3990708
Signed-off-by: Peter Xu <peterx@redhat.com>
---
 arch/x86/kvm/lapic.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH kernel RFC 1/4] powerpc/powernv/ioda: Rework for huge DMA window at 4GB
##### From: Alexey Kardashevskiy <aik@ozlabs.ru>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexey Kardashevskiy <aik@ozlabs.ru>
X-Patchwork-Id: 11268669
Return-Path: <SRS0=t74V=ZY=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 00D1B17F0
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  2 Dec 2019 02:09:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id DDB23215F1
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  2 Dec 2019 02:09:39 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727416AbfLBCJi (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 1 Dec 2019 21:09:38 -0500
Received: from 107-174-27-60-host.colocrossing.com ([107.174.27.60]:38176
 "EHLO
        ozlabs.ru" rhost-flags-OK-FAIL-OK-OK) by vger.kernel.org with ESMTP
        id S1727350AbfLBCJi (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 1 Dec 2019 21:09:38 -0500
Received: from fstn1-p1.ozlabs.ibm.com (localhost [IPv6:::1])
        by ozlabs.ru (Postfix) with ESMTP id 9504AAE8010F;
        Sun,  1 Dec 2019 20:58:56 -0500 (EST)
From: Alexey Kardashevskiy <aik@ozlabs.ru>
To: linuxppc-dev@lists.ozlabs.org
Cc: David Gibson <david@gibson.dropbear.id.au>, kvm@vger.kernel.org,
        Alistair Popple <alistair@popple.id.au>,
        Alex Williamson <alex.williamson@redhat.com>,
        Oliver O'Halloran <oohall@gmail.com>,
        Alexey Kardashevskiy <aik@ozlabs.ru>
Subject: [PATCH kernel RFC 1/4] powerpc/powernv/ioda: Rework for huge DMA
 window at 4GB
Date: Mon,  2 Dec 2019 12:59:50 +1100
Message-Id: <20191202015953.127902-2-aik@ozlabs.ru>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20191202015953.127902-1-aik@ozlabs.ru>
References: <20191202015953.127902-1-aik@ozlabs.ru>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This moves code to make the next patches look simpler. In particular:

1. Separate locals declaration as we will be allocating a smaller DMA
window if a TVE1_4GB option (allows a huge DMA windows at 4GB) is enabled;

2. Pass the bypass offset directly to pnv_pci_ioda2_create_table()
as it is the only information needed from @pe;

3. Use PAGE_SHIFT for it_map allocation estimate and @tceshift for
the IOMMU page size; this makes the distinction clear and allows
easy switching between different IOMMU page size.

These changes should not cause behavioral change.

Signed-off-by: Alexey Kardashevskiy <aik@ozlabs.ru>
---

I really need 1), 2) makes the code less dependent on the PE struct member
value (==easier to follow), 3) is to enable 2MB quickly for the default
DMA window for debugging/performance testing.
---
 arch/powerpc/platforms/powernv/pci-ioda.c | 38 ++++++++++++-----------
 1 file changed, 20 insertions(+), 18 deletions(-)

```
