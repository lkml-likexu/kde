#### [GIT PULL] More KVM fixes for 5.4-rc8
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11245673
Return-Path: <SRS0=Hm6W=ZH=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AA0186C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 15 Nov 2019 09:45:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 8917F20740
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 15 Nov 2019 09:45:00 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="DyoReDyy"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727180AbfKOJo5 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 15 Nov 2019 04:44:57 -0500
Received: from mail-wm1-f66.google.com ([209.85.128.66]:54287 "EHLO
        mail-wm1-f66.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726920AbfKOJo4 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 15 Nov 2019 04:44:56 -0500
Received: by mail-wm1-f66.google.com with SMTP id z26so8957775wmi.4;
        Fri, 15 Nov 2019 01:44:55 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id;
        bh=s61crLo7rMvO8Wf80iBrPDgDwSffbeyNgj2v4Ncj5Ag=;
        b=DyoReDyyhRBmrZaTauJCDmNm+/tlTd3FWW/ZoNYN05xqz6RvoflkhN+J91NI8ye6E4
         5/VSJXf/6UpCZPNIno3j6M4oUR2TN3R+xG9uV6Fc3RwJcqyasO/Lqw71+d4uNVMle4Vz
         61PGIXq+qSJkhUU3SK7GYZbuYMT0KFN7lrqURh4wg1vR0F7fedMlJ0l/3wDbguRCJI1u
         xRYQd3W09q1P5EH2j6QOz/rYwK6YBNOTwC83douYCfnHnJNypcE64rDt8sZuHrCS+hXp
         f8YZ1WVWZfn1vc1IoCQCk+9DvU+dANWjX92j41uXBeJfn4HWvfOSeikJG/402s4DNYv9
         Q03w==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id;
        bh=s61crLo7rMvO8Wf80iBrPDgDwSffbeyNgj2v4Ncj5Ag=;
        b=M2B36gHIJUp18WQ/tOtESlB8QMI9pP7JmCDxGOQ5e0+dzIJVI+GsA1/GiI+czh0Ufs
         NfREdOSBIQqT4FpzweWn/Y802YoP+RuSqGTKPLkDqKwWSN1uLZCep7tP8rMX7EB4t/+H
         XcCnGw9bjtp8ZkdQleMEO5CiaWd8itbFxDgFoSmpSjKK2263lJC4IbrWQOeCkyn4p4WU
         dPWMAEG9PFeqLiBXTr1feRCn8qIiIK/irRzOj1BOflYKEoMvWlrhr9UNFJZihD48VBbj
         APJbYB7SMvI4O5vTRE3djQuDupyaM7q8wUirrYDBd5ndzd2XmD9Rf2NuKVIRODeMrNp7
         uwqA==
X-Gm-Message-State: APjAAAXs6q29fyDURtwK1hWK0ysQXLP29iC/TOn09fWAKWGP6lv+WNJi
        NE8Ea7tblI2+VkkgRqyfJdbJuLTx
X-Google-Smtp-Source: 
 APXvYqyU+TVj8L3P31QRcrvtWrtvI3pOCkxyInBkWrRnjj5g3p+UdchNp9kkKhraOwu7Mnb6ySx4KQ==
X-Received: by 2002:a7b:cc8b:: with SMTP id p11mr13682877wma.38.1573811094469;
        Fri, 15 Nov 2019 01:44:54 -0800 (PST)
Received: from 640k.lan ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 d13sm10097783wrq.51.2019.11.15.01.44.53
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Fri, 15 Nov 2019 01:44:53 -0800 (PST)
From: Paolo Bonzini <pbonzini@redhat.com>
To: torvalds@linux-foundation.org
Cc: linux-kernel@vger.kernel.org, rkrcmar@redhat.com,
        kvm@vger.kernel.org
Subject: [GIT PULL] More KVM fixes for 5.4-rc8
Date: Fri, 15 Nov 2019 10:44:52 +0100
Message-Id: <1573811092-12834-1-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Linus,

The following changes since commit 8c5bd25bf42effd194d4b0b43895c42b374e620b:

  Merge tag 'for-linus' of git://git.kernel.org/pub/scm/virt/kvm/kvm (2019-11-12 13:19:15 -0800)

are available in the git repository at:


  https://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to 9cb09e7c1c9af2968d5186ef9085f05641ab65d9:

  KVM: Add a comment describing the /dev/kvm no_compat handling (2019-11-15 10:14:04 +0100)

----------------------------------------------------------------
* Fixes for CONFIG_KVM_COMPAT=n
* Two updates to the IFU erratum
* selftests build fix
* Brown paper bag fix

----------------------------------------------------------------
Marc Zyngier (2):
      KVM: Forbid /dev/kvm being opened by a compat task when CONFIG_KVM_COMPAT=n
      KVM: Add a comment describing the /dev/kvm no_compat handling

Paolo Bonzini (1):
      kvm: x86: disable shattered huge page recovery for PREEMPT_RT.

Sean Christopherson (1):
      KVM: x86/mmu: Take slots_lock when using kvm_mmu_zap_all_fast()

Vitaly Kuznetsov (1):
      selftests: kvm: fix build with glibc >= 2.30

Xiaoyao Li (1):
      KVM: X86: Reset the three MSR list number variables to 0 in kvm_init_msr_list()

 arch/x86/kvm/mmu.c                       | 10 +++++++---
 arch/x86/kvm/x86.c                       |  4 ++++
 tools/testing/selftests/kvm/lib/assert.c |  4 ++--
 virt/kvm/kvm_main.c                      | 15 ++++++++++++++-
 4 files changed, 27 insertions(+), 6 deletions(-)
```
#### [PATCH] KVM: nVMX: mark functions in the header as "static inline"
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11246009
Return-Path: <SRS0=Hm6W=ZH=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D93AF930
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 15 Nov 2019 10:36:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id BA28B206DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 15 Nov 2019 10:36:24 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="oAaeCX6L"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727274AbfKOKgV (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 15 Nov 2019 05:36:21 -0500
Received: from mail-wm1-f66.google.com ([209.85.128.66]:38427 "EHLO
        mail-wm1-f66.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727022AbfKOKgU (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 15 Nov 2019 05:36:20 -0500
Received: by mail-wm1-f66.google.com with SMTP id z19so9831110wmk.3;
        Fri, 15 Nov 2019 02:36:19 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:subject:date:message-id;
        bh=frWZkSD6sy+8xeYJ3Z3Dvc1ltroH4PVNYqHO9zC/gkU=;
        b=oAaeCX6Lw4vTyv0tC3MmzjWCZ0wJwGhNiup8LtPqlbMwl4Tz0ld9uF9kAdkXbv0j1m
         F/3MQx4qpNlS1NE/4ZuukATOeEbUzu+9ESR0W86lDELqojpGB7Ocsodi97F+PbTN4Ls7
         5io2PJ2RgWlEThI3Yoh/Pcxe6cEN9tSmgOSaun0R3G0Mo5jBNK+NPU4XkWu6X4LztwJO
         I4qtJYHR1ggCeMx9tUvzUXOAknQk7ogN7QcRf0yp553OqA8i8MmhHDIdK4kTokmxN0Ym
         qliw4KqyhB0i8W9dsat0p9Wlin6ravgfbVCu7ekv/uXV71d+ffavN1IBZCSpKpI3SSpp
         5BiA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:subject:date:message-id;
        bh=frWZkSD6sy+8xeYJ3Z3Dvc1ltroH4PVNYqHO9zC/gkU=;
        b=RfCsLMhR7qjgGCZDyr5ML9ZD1byy49AYIJyG241QniH4wAMH/gHHeyjZTppAwsDm/W
         2i5zMsau9wxc5k08h/0gIlMD7PBcFzEfrJcky5kvcECk9AYaFroWXrjJ+VecHAP4hvV0
         LY1pDiwmzm/dmUwttxp3LVR/IxRiZJyhRSzCBAods9McmGOel+QPc5G8/1e/dN1vQzOM
         y4FJ/sertNVQedEgyACMVWoLHr/7cbZuRGXQu4XjKZuuEm9wwF2yVIAKg2IZQ0TjBlhP
         sxailiprI+j/Kbg8DjznClGyJgpTrfqaGh5NfnsC7JlwHUGZPhRZyMRqlKQRxKAZ65g9
         Pv/Q==
X-Gm-Message-State: APjAAAURzzYOwLGKBahtFwX4l6cOk2KnlT/G7pIgImF8kdW/kQcuP03e
        y5OwjakZ2BDgPqQEA2zyIENbd6rf
X-Google-Smtp-Source: 
 APXvYqwR8q3zsqox2ep5AOsJj1majxWGrUKLw6Izp+EvrWGnzP7gzmSEyY6YmaYXu6FJDq4UwXpgnQ==
X-Received: by 2002:a1c:4e1a:: with SMTP id
 g26mr14110733wmh.138.1573814178104;
        Fri, 15 Nov 2019 02:36:18 -0800 (PST)
Received: from 640k.lan ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 b186sm8801138wmb.21.2019.11.15.02.36.17
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Fri, 15 Nov 2019 02:36:17 -0800 (PST)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [PATCH] KVM: nVMX: mark functions in the header as "static inline"
Date: Fri, 15 Nov 2019 11:36:16 +0100
Message-Id: <1573814176-28536-1-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Correct a small inaccuracy in the shattering of vmx.c, which becomes
visible now that pmu_intel.c includes nested.h.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/vmx/nested.h | 6 +++---
 1 file changed, 3 insertions(+), 3 deletions(-)

```
#### [PATCH v5 01/24] mm/gup: pass flags arg to __gup_device_* functions
##### From: John Hubbard <jhubbard@nvidia.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: John Hubbard <jhubbard@nvidia.com>
X-Patchwork-Id: 11245175
Return-Path: <SRS0=Hm6W=ZH=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3AB7E17E0
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 15 Nov 2019 05:57:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 122FB2075E
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 15 Nov 2019 05:57:44 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=nvidia.com header.i=@nvidia.com
 header.b="Vf3URXCB"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727668AbfKOF5f (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 15 Nov 2019 00:57:35 -0500
Received: from hqemgate16.nvidia.com ([216.228.121.65]:10608 "EHLO
        hqemgate16.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726308AbfKOFxv (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 15 Nov 2019 00:53:51 -0500
Received: from hqpgpgate101.nvidia.com (Not Verified[216.228.121.13]) by
 hqemgate16.nvidia.com (using TLS: TLSv1.2, DES-CBC3-SHA)
        id <B5dce3d670000>; Thu, 14 Nov 2019 21:53:44 -0800
Received: from hqmail.nvidia.com ([172.20.161.6])
  by hqpgpgate101.nvidia.com (PGP Universal service);
  Thu, 14 Nov 2019 21:53:44 -0800
X-PGP-Universal: processed;
        by hqpgpgate101.nvidia.com on Thu, 14 Nov 2019 21:53:44 -0800
Received: from HQMAIL101.nvidia.com (172.20.187.10) by HQMAIL107.nvidia.com
 (172.20.187.13) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Fri, 15 Nov
 2019 05:53:43 +0000
Received: from hqnvemgw03.nvidia.com (10.124.88.68) by HQMAIL101.nvidia.com
 (172.20.187.10) with Microsoft SMTP Server (TLS) id 15.0.1473.3 via Frontend
 Transport; Fri, 15 Nov 2019 05:53:43 +0000
Received: from blueforge.nvidia.com (Not Verified[10.110.48.28]) by
 hqnvemgw03.nvidia.com with Trustwave SEG (v7,5,8,10121)
        id <B5dce3d670001>; Thu, 14 Nov 2019 21:53:43 -0800
From: John Hubbard <jhubbard@nvidia.com>
To: Andrew Morton <akpm@linux-foundation.org>
CC: Al Viro <viro@zeniv.linux.org.uk>,
 Alex Williamson <alex.williamson@redhat.com>,
 Benjamin Herrenschmidt <benh@kernel.crashing.org>, =?utf-8?b?QmrDtnJuIFQ=?=
	=?utf-8?b?w7ZwZWw=?= <bjorn.topel@intel.com>,
 Christoph Hellwig <hch@infradead.org>,
 Dan Williams <dan.j.williams@intel.com>, Daniel Vetter <daniel@ffwll.ch>,
 Dave Chinner <david@fromorbit.com>, David Airlie <airlied@linux.ie>,
 "David S . Miller" <davem@davemloft.net>, Ira Weiny <ira.weiny@intel.com>,
 Jan Kara <jack@suse.cz>, Jason Gunthorpe <jgg@ziepe.ca>,
 Jens Axboe <axboe@kernel.dk>, Jonathan Corbet <corbet@lwn.net>,
	=?utf-8?b?SsOpcsO0bWUgR2xpc3Nl?= <jglisse@redhat.com>,
 Magnus Karlsson <magnus.karlsson@intel.com>,
 Mauro Carvalho Chehab <mchehab@kernel.org>,
 Michael Ellerman <mpe@ellerman.id.au>, Michal Hocko <mhocko@suse.com>,
 Mike Kravetz <mike.kravetz@oracle.com>, Paul Mackerras <paulus@samba.org>,
 Shuah Khan <shuah@kernel.org>, Vlastimil Babka <vbabka@suse.cz>,
 <bpf@vger.kernel.org>, <dri-devel@lists.freedesktop.org>,
 <kvm@vger.kernel.org>, <linux-block@vger.kernel.org>,
 <linux-doc@vger.kernel.org>, <linux-fsdevel@vger.kernel.org>,
 <linux-kselftest@vger.kernel.org>, <linux-media@vger.kernel.org>,
 <linux-rdma@vger.kernel.org>, <linuxppc-dev@lists.ozlabs.org>,
 <netdev@vger.kernel.org>, <linux-mm@kvack.org>,
 LKML <linux-kernel@vger.kernel.org>, John Hubbard <jhubbard@nvidia.com>,
 "Kirill A . Shutemov" <kirill.shutemov@linux.intel.com>
Subject: [PATCH v5 01/24] mm/gup: pass flags arg to __gup_device_* functions
Date: Thu, 14 Nov 2019 21:53:17 -0800
Message-ID: <20191115055340.1825745-2-jhubbard@nvidia.com>
X-Mailer: git-send-email 2.24.0
In-Reply-To: <20191115055340.1825745-1-jhubbard@nvidia.com>
References: <20191115055340.1825745-1-jhubbard@nvidia.com>
MIME-Version: 1.0
X-NVConfidentiality: public
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1573797224; bh=shQdk3aSV65MVp9nCFIR9V5hifAIbJq1aZuVoQR8zJ0=;
        h=X-PGP-Universal:From:To:CC:Subject:Date:Message-ID:X-Mailer:
         In-Reply-To:References:MIME-Version:X-NVConfidentiality:
         Content-Type:Content-Transfer-Encoding;
        b=Vf3URXCBhJ0LWwHJTcm52WVotKdwRX+fknMcBrSG9k9AJxxUhN4wPoYtvL0rv0zz0
         qbduFsMF4ZFH6miC1kaynU/PrKYo4BtWIA/ZvENIC1Gpe4IoMeJtZfOjm9/Z6JLagQ
         vn3NYUI4U5tVPDOcTeijgB4+34WSSn3+imGks6gzw6odBbR8B0oqCrtPU8HmBWVQYj
         fyyd2pwWVoWnJQw5edg9QMnK85g5O8Xa/udpjC3YJAysMnGOdUGjR9e/DDV1oBbSIE
         jOIUGGOPL35CODf13FwjukgEvzT2UWdIxS8kelzmDzlSC6jbbyG50vbWHQgHl8o9MC
         sY4Z99AL8LcOw==
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

A subsequent patch requires access to gup flags, so
pass the flags argument through to the __gup_device_*
functions.

Also placate checkpatch.pl by shortening a nearby line.

Reviewed-by: Jan Kara <jack@suse.cz>
Reviewed-by: Jérôme Glisse <jglisse@redhat.com>
Reviewed-by: Ira Weiny <ira.weiny@intel.com>
Cc: Kirill A. Shutemov <kirill.shutemov@linux.intel.com>
Signed-off-by: John Hubbard <jhubbard@nvidia.com>
---
 mm/gup.c | 28 ++++++++++++++++++----------
 1 file changed, 18 insertions(+), 10 deletions(-)

```
#### [RFC PATCH v1 01/10] vfio-ccw: Introduce new helper functions to free/destroy regions
##### From: Eric Farman <farman@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Farman <farman@linux.ibm.com>
X-Patchwork-Id: 11244803
Return-Path: <SRS0=Hm6W=ZH=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C19A96C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 15 Nov 2019 05:26:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id AAAEC20729
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 15 Nov 2019 05:26:53 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726655AbfKOF0v (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 15 Nov 2019 00:26:51 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:12314 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726017AbfKOF0v (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 15 Nov 2019 00:26:51 -0500
Received: from pps.filterd (m0098396.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 xAF5OClO111869
        for <kvm@vger.kernel.org>; Fri, 15 Nov 2019 00:26:50 -0500
Received: from e06smtp01.uk.ibm.com (e06smtp01.uk.ibm.com [195.75.94.97])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2w9jtsvs4q-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Fri, 15 Nov 2019 00:26:50 -0500
Received: from localhost
        by e06smtp01.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <farman@linux.ibm.com>;
        Fri, 15 Nov 2019 02:56:25 -0000
Received: from b06cxnps4074.portsmouth.uk.ibm.com (9.149.109.196)
        by e06smtp01.uk.ibm.com (192.168.101.131) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Fri, 15 Nov 2019 02:56:22 -0000
Received: from d06av21.portsmouth.uk.ibm.com (d06av21.portsmouth.uk.ibm.com
 [9.149.105.232])
        by b06cxnps4074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id xAF2uKBv45875442
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 15 Nov 2019 02:56:20 GMT
Received: from d06av21.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id C0FB75204E;
        Fri, 15 Nov 2019 02:56:20 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av21.portsmouth.uk.ibm.com (Postfix) with ESMTPS id AEFFA52050;
        Fri, 15 Nov 2019 02:56:20 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 4958)
        id 4E1CAE0193; Fri, 15 Nov 2019 03:56:20 +0100 (CET)
From: Eric Farman <farman@linux.ibm.com>
To: kvm@vger.kernel.org, linux-s390@vger.kernel.org
Cc: Cornelia Huck <cohuck@redhat.com>,
        Jason Herne <jjherne@linux.ibm.com>,
        Jared Rossi <jrossi@linux.ibm.com>,
        Eric Farman <farman@linux.ibm.com>
Subject: [RFC PATCH v1 01/10] vfio-ccw: Introduce new helper functions to
 free/destroy regions
Date: Fri, 15 Nov 2019 03:56:11 +0100
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20191115025620.19593-1-farman@linux.ibm.com>
References: <20191115025620.19593-1-farman@linux.ibm.com>
X-TM-AS-GCONF: 00
x-cbid: 19111502-4275-0000-0000-0000037DDAA5
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19111502-4276-0000-0000-000038914295
Message-Id: <20191115025620.19593-2-farman@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.95,18.0.572
 definitions=2019-11-14_07:2019-11-14,2019-11-14 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 adultscore=0 spamscore=0
 mlxlogscore=660 impostorscore=0 lowpriorityscore=0 phishscore=0
 bulkscore=0 mlxscore=0 clxscore=1015 suspectscore=2 malwarescore=0
 priorityscore=1501 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-1910280000 definitions=main-1911150047
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Farhan Ali <alifm@linux.ibm.com>

Consolidate some of the cleanup code for the regions, so that
as more are added we reduce code duplication.

Signed-off-by: Farhan Ali <alifm@linux.ibm.com>
Signed-off-by: Eric Farman <farman@linux.ibm.com>
---

Notes:
    v0->v1: [EF]
     - Commit message

 drivers/s390/cio/vfio_ccw_drv.c | 28 ++++++++++++++++++----------
 1 file changed, 18 insertions(+), 10 deletions(-)

```
#### [PATCH] SIDAD macro fixup
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11246229
Return-Path: <SRS0=Hm6W=ZH=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EA36113B2
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 15 Nov 2019 12:18:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D6054207FA
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 15 Nov 2019 12:18:07 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727494AbfKOMSG (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 15 Nov 2019 07:18:06 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:44586 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727557AbfKOMSG (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 15 Nov 2019 07:18:06 -0500
Received: from pps.filterd (m0098419.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 xAFCEtB4019252
        for <kvm@vger.kernel.org>; Fri, 15 Nov 2019 07:18:04 -0500
Received: from e06smtp02.uk.ibm.com (e06smtp02.uk.ibm.com [195.75.94.98])
        by mx0b-001b2d01.pphosted.com with ESMTP id 2w9jtvuncc-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Fri, 15 Nov 2019 07:18:04 -0500
Received: from localhost
        by e06smtp02.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Fri, 15 Nov 2019 12:18:03 -0000
Received: from b06cxnps4074.portsmouth.uk.ibm.com (9.149.109.196)
        by e06smtp02.uk.ibm.com (192.168.101.132) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Fri, 15 Nov 2019 12:18:00 -0000
Received: from d06av23.portsmouth.uk.ibm.com (d06av23.portsmouth.uk.ibm.com
 [9.149.105.59])
        by b06cxnps4074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id xAFCHwHb27852848
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 15 Nov 2019 12:17:58 GMT
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id B464CA4040;
        Fri, 15 Nov 2019 12:17:58 +0000 (GMT)
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 67E96A4059;
        Fri, 15 Nov 2019 12:17:57 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.152.224.131])
        by d06av23.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Fri, 15 Nov 2019 12:17:57 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, david@redhat.com, thuth@redhat.com,
        borntraeger@de.ibm.com, imbrenda@linux.ibm.com,
        mihajlov@linux.ibm.com, mimu@linux.ibm.com, cohuck@redhat.com
Subject: [PATCH] SIDAD macro fixup
Date: Fri, 15 Nov 2019 07:17:55 -0500
X-Mailer: git-send-email 2.20.1
In-Reply-To: <6f956633-d067-bde9-78dc-7833b9cd86ee@redhat.com>
References: <6f956633-d067-bde9-78dc-7833b9cd86ee@redhat.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 19111512-0008-0000-0000-0000032F445C
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19111512-0009-0000-0000-00004A4E56D8
Message-Id: <20191115121755.63197-1-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.95,18.0.572
 definitions=2019-11-15_03:2019-11-15,2019-11-15 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 malwarescore=0 suspectscore=3
 adultscore=0 clxscore=1015 impostorscore=0 bulkscore=0 spamscore=0
 mlxscore=0 lowpriorityscore=0 priorityscore=1501 mlxlogscore=895
 phishscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-1910280000 definitions=main-1911150116
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Additionally I would need to use it in the other patches...

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
---
 arch/s390/include/asm/kvm_host.h | 4 ++++
 arch/s390/kvm/kvm-s390.c         | 4 ++--
 arch/s390/kvm/pv.c               | 2 +-
 3 files changed, 7 insertions(+), 3 deletions(-)

```
