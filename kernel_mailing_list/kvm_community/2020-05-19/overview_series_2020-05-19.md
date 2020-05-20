#### [PATCH 1/3] selftests: kvm: add a SVM version of state-test
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11558413
Return-Path: <SRS0=rCNo=7B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 38D8F90
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 19 May 2020 18:07:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 218932075F
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 19 May 2020 18:07:58 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Gsi/xEGq"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729210AbgESSH5 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 19 May 2020 14:07:57 -0400
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:32321 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1729185AbgESSH4 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 19 May 2020 14:07:56 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1589911675;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc; bh=jSkbMzL80RhyCrT3ZnovTmqJc4ZMDL+dVOZ04nO1iEs=;
        b=Gsi/xEGqH/abMdni/AhgX2Z1O0999l7VvRQe05gK4B/qzyM63cIt3VPuRezvsliwN0RhMZ
        K8qWGTszjo2mjiOVTH8vlcgoUKKfUvNFxWMlss7gs8NH55N5JZy/xNbMXQXk6U10QMy7wZ
        QpQ2g2jCJ2JolclLl5UXnOV4qMjY1Fk=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-439-UqvQheSgO6CDN0qpYEYNHQ-1; Tue, 19 May 2020 14:07:42 -0400
X-MC-Unique: UqvQheSgO6CDN0qpYEYNHQ-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 72E90800D24;
        Tue, 19 May 2020 18:07:41 +0000 (UTC)
Received: from virtlab511.virt.lab.eng.bos.redhat.com
 (virtlab511.virt.lab.eng.bos.redhat.com [10.19.152.198])
        by smtp.corp.redhat.com (Postfix) with ESMTP id DBDF55D9DD;
        Tue, 19 May 2020 18:07:40 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: oupton@google.com
Subject: [PATCH 1/3] selftests: kvm: add a SVM version of state-test
Date: Tue, 19 May 2020 14:07:38 -0400
Message-Id: <20200519180740.89884-1-pbonzini@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 .../testing/selftests/kvm/x86_64/state_test.c | 65 ++++++++++++++++---
 1 file changed, 55 insertions(+), 10 deletions(-)

```
#### [PATCH v1 24/25] kvm/eventfd: Use sequence counter with associated spinlock
##### From: "Ahmed S. Darwish" <a.darwish@linutronix.de>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Ahmed S. Darwish" <a.darwish@linutronix.de>
X-Patchwork-Id: 11558883
Return-Path: <SRS0=rCNo=7B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5D9D313B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 19 May 2020 21:48:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4B5662072C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 19 May 2020 21:48:06 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726064AbgESVsF (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 19 May 2020 17:48:05 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:41062 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728593AbgESVsB (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 19 May 2020 17:48:01 -0400
Received: from Galois.linutronix.de (Galois.linutronix.de
 [IPv6:2a0a:51c0:0:12e:550::1])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 546CAC08C5C2;
        Tue, 19 May 2020 14:48:01 -0700 (PDT)
Received: from [5.158.153.53] (helo=debian-buster-darwi.lab.linutronix.de.)
        by Galois.linutronix.de with esmtpsa
 (TLS1.2:DHE_RSA_AES_256_CBC_SHA1:256)
        (Exim 4.80)
        (envelope-from <a.darwish@linutronix.de>)
        id 1jbA5W-0002yb-3S; Tue, 19 May 2020 23:47:50 +0200
From: "Ahmed S. Darwish" <a.darwish@linutronix.de>
To: Peter Zijlstra <peterz@infradead.org>,
        Ingo Molnar <mingo@redhat.com>, Will Deacon <will@kernel.org>
Cc: Thomas Gleixner <tglx@linutronix.de>,
        "Paul E. McKenney" <paulmck@kernel.org>,
        "Sebastian A. Siewior" <bigeasy@linutronix.de>,
        Steven Rostedt <rostedt@goodmis.org>,
        LKML <linux-kernel@vger.kernel.org>,
        "Ahmed S. Darwish" <a.darwish@linutronix.de>,
        Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org
Subject: [PATCH v1 24/25] kvm/eventfd: Use sequence counter with associated
 spinlock
Date: Tue, 19 May 2020 23:45:46 +0200
Message-Id: <20200519214547.352050-25-a.darwish@linutronix.de>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20200519214547.352050-1-a.darwish@linutronix.de>
References: <20200519214547.352050-1-a.darwish@linutronix.de>
MIME-Version: 1.0
X-Linutronix-Spam-Score: -1.0
X-Linutronix-Spam-Level: -
X-Linutronix-Spam-Status: No , -1.0 points, 5.0 required,
  ALL_TRUSTED=-1,SHORTCIRCUIT=-0.0001
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

A sequence counter write side critical section must be protected by some
form of locking to serialize writers. A plain seqcount_t does not
contain the information of which lock must be held when entering a write
side critical section.

Use the new seqcount_spinlock_t data type, which allows to associate a
spinlock with the sequence counter. This enables lockdep to verify that
the spinlock used for writer serialization is held when the write side
critical section is entered.

If lockdep is disabled this lock association is compiled out and has
neither storage size nor runtime overhead.

Signed-off-by: Ahmed S. Darwish <a.darwish@linutronix.de>
---
 include/linux/kvm_irqfd.h | 2 +-
 virt/kvm/eventfd.c        | 2 +-
 2 files changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH  v2 1/2] KVM: nVMX: Fix VMX preemption timer migrationFrom: Makarand Sonare <makarandsonare@google.com>
##### From: Makarand Sonare <makarandsonare@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Makarand Sonare <makarandsonare@google.com>
X-Patchwork-Id: 11558911
Return-Path: <SRS0=rCNo=7B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E533D618
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 19 May 2020 22:22:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C78EF206C3
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 19 May 2020 22:22:56 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="mwUbPEj0"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725998AbgESWWz (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 19 May 2020 18:22:55 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:46484 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726432AbgESWWz (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 19 May 2020 18:22:55 -0400
Received: from mail-qt1-x849.google.com (mail-qt1-x849.google.com
 [IPv6:2607:f8b0:4864:20::849])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 332CFC061A0F
        for <kvm@vger.kernel.org>; Tue, 19 May 2020 15:22:54 -0700 (PDT)
Received: by mail-qt1-x849.google.com with SMTP id z29so1434935qtj.5
        for <kvm@vger.kernel.org>; Tue, 19 May 2020 15:22:54 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=bCJWmHbze1pLLih718jeliFNM3BKqGb8v3takoCjUgM=;
        b=mwUbPEj0O8gsWGPPjwy7WK6wbWiPEhZ/9djjleiE9hbD+JPX0QGsTKsEZYLLpnkGEB
         AxPnpEMRpH8DH0gvXv56X5nOU4a1ix0jJQSz2X7YaEs5vM8cjza1YgUAGhl+2RGCRC/8
         P11rFvKwtfjGL7j5e+mb5Z82hMepwcwhK6ua83ItPxy1GqkSLb3HPzY5EL5xQjl4uviG
         DOU3dyEbG2dbBCL4CXIcBzhSMhp1mK+4v91yhKSCSI8i9i3hyIuU8Psng52943m8ZiZE
         8dZZWbJn71Mjah4mf13ifBUaOa9xmoY4qNZCJGwsKKotu5BYiXqqNiUg1unqvOsRMjzU
         s4hg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=bCJWmHbze1pLLih718jeliFNM3BKqGb8v3takoCjUgM=;
        b=cgFu+8c7YOOfBZKnEIVNbH+JHmz1cwT/ZanaO9OFNxgjteHeC9Ygk7XurtiuKxcFD9
         Rc1qU/ePKu0Cz+Y5AgF0Yw6FrU+cUMWhw3FPxNN+17ynKZ+dG2XuQwz3PBXpYBC543fP
         9kqimtumW7R8lP02QkT1SsWtZlyXHozgmOcFU4pZHmaUHIymN5bWTOwMzocMZq1avkGe
         AelXLVf4ecwhSd3DSjqwB+jU0cTdCo1S36vSTiGP/SznVyb9ZXC80gRvr5nf4pt1NpUu
         n4ptGjPGF62YjGhUAqKEIKwsABcLW9CPQsLNKGjYPPETnLXuTfQjDAMUOJiavGEpy18k
         M/PQ==
X-Gm-Message-State: AOAM530/tuYl8GfvB4cI3OnZfayH7Wl+1Ui3jZZnBXkB76w1Z7lknXND
        ZQek84Y69wGHrki2xlNTzaOidfZzoiUDRoErFmESKjex+8YjWk06Wk7W5wc8aCEtgR0j9IdmTBx
        sLp/QGxlz4TkKC606j1/MCzRY2y4KvE6Z8kQgXXe20VPLYpCVoyJoJXhbCJJMmw807016LsTO8n
        qgc6A=
X-Google-Smtp-Source: 
 ABdhPJwAWec4iG4MOqtZLYCA8D2mJSqbmHHmeAiZuuGdc/at+/qqP8n3ZIXg7wkCHQwDNrmRiqpB4tBMkDBt36buWC/hug==
X-Received: by 2002:a05:6214:1427:: with SMTP id
 o7mr2015675qvx.104.1589926973326;
 Tue, 19 May 2020 15:22:53 -0700 (PDT)
Date: Tue, 19 May 2020 15:22:37 -0700
In-Reply-To: <20200519222238.213574-1-makarandsonare@google.com>
Message-Id: <20200519222238.213574-2-makarandsonare@google.com>
Mime-Version: 1.0
References: <20200519222238.213574-1-makarandsonare@google.com>
X-Mailer: git-send-email 2.26.2.761.g0e0b3e54be-goog
Subject: [PATCH  v2 1/2] KVM: nVMX: Fix VMX preemption timer migration
From: Makarand Sonare <makarandsonare@google.com>
To: kvm@vger.kernel.org, pshier@google.com, jmattson@google.com
Cc: Makarand Sonare <makarandsonare@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Peter Shier <pshier@google.com>

Add new field to hold preemption timer expiration deadline
appended to struct kvm_vmx_nested_state_data. This is to prevent
the first VM-Enter after migration from incorrectly restarting the timer
with the full timer value instead of partially decayed timer value.
KVM_SET_NESTED_STATE restarts timer using migrated state regardless
of whether L1 sets VM_EXIT_SAVE_VMX_PREEMPTION_TIMER.

Fixes: cf8b84f48a593 ("kvm: nVMX: Prepare for checkpointing L2 state")

Signed-off-by: Peter Shier <pshier@google.com>
Signed-off-by: Makarand Sonare <makarandsonare@google.com>
Change-Id: I6446aba5a547afa667f0ef4620b1b76115bf3753
---
 Documentation/virt/kvm/api.rst  |  4 +++
 arch/x86/include/uapi/asm/kvm.h |  3 ++
 arch/x86/kvm/vmx/nested.c       | 56 +++++++++++++++++++++++++++++----
 arch/x86/kvm/vmx/vmx.h          |  1 +
 arch/x86/kvm/x86.c              |  3 +-
 include/uapi/linux/kvm.h        |  1 +
 6 files changed, 61 insertions(+), 7 deletions(-)

--
2.26.2.761.g0e0b3e54be-goog

```
#### [PATCH Kernel v22 5/8] vfio iommu: Implementation of ioctl for dirty pages tracking
##### From: Kirti Wankhede <kwankhede@nvidia.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kirti Wankhede <kwankhede@nvidia.com>
X-Patchwork-Id: 11557111
Return-Path: <SRS0=rCNo=7B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 47D911391
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 19 May 2020 07:26:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1AB072075F
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 19 May 2020 07:26:14 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=nvidia.com header.i=@nvidia.com
 header.b="UqxelBSu"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728159AbgESH0N (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 19 May 2020 03:26:13 -0400
Received: from hqnvemgate26.nvidia.com ([216.228.121.65]:7814 "EHLO
        hqnvemgate26.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726881AbgESH0M (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 19 May 2020 03:26:12 -0400
Received: from hqpgpgate101.nvidia.com (Not Verified[216.228.121.13]) by
 hqnvemgate26.nvidia.com (using TLS: TLSv1.2, DES-CBC3-SHA)
        id <B5ec38a050000>; Tue, 19 May 2020 00:25:57 -0700
Received: from hqmail.nvidia.com ([172.20.161.6])
  by hqpgpgate101.nvidia.com (PGP Universal service);
  Tue, 19 May 2020 00:26:09 -0700
X-PGP-Universal: processed;
        by hqpgpgate101.nvidia.com on Tue, 19 May 2020 00:26:09 -0700
Received: from HQMAIL105.nvidia.com (172.20.187.12) by HQMAIL105.nvidia.com
 (172.20.187.12) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Tue, 19 May
 2020 07:26:09 +0000
Received: from kwankhede-dev.nvidia.com (10.124.1.5) by HQMAIL105.nvidia.com
 (172.20.187.12) with Microsoft SMTP Server (TLS) id 15.0.1473.3 via Frontend
 Transport; Tue, 19 May 2020 07:26:02 +0000
From: Kirti Wankhede <kwankhede@nvidia.com>
To: <alex.williamson@redhat.com>, <cjia@nvidia.com>
CC: <kevin.tian@intel.com>, <ziye.yang@intel.com>,
        <changpeng.liu@intel.com>, <yi.l.liu@intel.com>,
        <mlevitsk@redhat.com>, <eskultet@redhat.com>, <cohuck@redhat.com>,
        <dgilbert@redhat.com>, <jonathan.davies@nutanix.com>,
        <eauger@redhat.com>, <aik@ozlabs.ru>, <pasic@linux.ibm.com>,
        <felipe@nutanix.com>, <Zhengxiao.zx@Alibaba-inc.com>,
        <shuangtai.tst@alibaba-inc.com>, <Ken.Xue@amd.com>,
        <zhi.a.wang@intel.com>, <yan.y.zhao@intel.com>,
        <qemu-devel@nongnu.org>, <kvm@vger.kernel.org>,
        Kirti Wankhede <kwankhede@nvidia.com>
Subject: [PATCH Kernel v22 5/8] vfio iommu: Implementation of ioctl for dirty
 pages tracking
Date: Tue, 19 May 2020 12:22:58 +0530
Message-ID: <1589871178-8282-1-git-send-email-kwankhede@nvidia.com>
X-Mailer: git-send-email 2.7.0
In-Reply-To: <17511c50-dc59-d9e9-10b6-54b16dec01c4@nvidia.com>
References: <17511c50-dc59-d9e9-10b6-54b16dec01c4@nvidia.com>
X-NVConfidentiality: public
MIME-Version: 1.0
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1589873157; bh=OTPdTfD3q2pZ56e0XbOLl0CElgEI4wot2JIWkdS4xYw=;
        h=X-PGP-Universal:From:To:CC:Subject:Date:Message-ID:X-Mailer:
         In-Reply-To:References:X-NVConfidentiality:MIME-Version:
         Content-Type;
        b=UqxelBSu4YQ+isYv1v/dTWH2DWdvcrntP5O6FzxZrjaelxSHZqBhr3udI7MFaNANt
         ohdRyXGndeTri/FaiixSs8PbLxygHhtJLigDJZXrUJXVqUuNhnDD3omnauCi/tEqAi
         WhRqISQm2qKmV8t4t/fjLnRLOkpXsPFBHOZI8FvRy920ww5zDB181cy+LLoFNvH2LI
         uTSCV6l5L5BAjxA11hMDHr3x+xmGB/thkPwByS6cOntsOxI/nB17bJ8mOrQjAUdK9I
         NtxQx9mrzSTV7TOfvXviBqd2Z1WoTqnru3ahSsKY3Vwf/jmHU/3gBjAddsrB/5qHN7
         ZXXeRZGrEGEQQ==
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

VFIO_IOMMU_DIRTY_PAGES ioctl performs three operations:
- Start dirty pages tracking while migration is active
- Stop dirty pages tracking.
- Get dirty pages bitmap. Its user space application's responsibility to
  copy content of dirty pages from source to destination during migration.

To prevent DoS attack, memory for bitmap is allocated per vfio_dma
structure. Bitmap size is calculated considering smallest supported page
size. Bitmap is allocated for all vfio_dmas when dirty logging is enabled

Bitmap is populated for already pinned pages when bitmap is allocated for
a vfio_dma with the smallest supported page size. Update bitmap from
pinning functions when tracking is enabled. When user application queries
bitmap, check if requested page size is same as page size used to
populated bitmap. If it is equal, copy bitmap, but if not equal, return
error.

Signed-off-by: Kirti Wankhede <kwankhede@nvidia.com>
Reviewed-by: Neo Jia <cjia@nvidia.com>

Fixed error reported by build bot by changing pgsize type from uint64_t
to size_t.
Reported-by: kbuild test robot <lkp@intel.com>
---
 drivers/vfio/vfio_iommu_type1.c | 313 +++++++++++++++++++++++++++++++++++++++-
 1 file changed, 307 insertions(+), 6 deletions(-)

```
#### [PATCH] KVM: x86: allow KVM_STATE_NESTED_MTF_PENDING in kvm_state flags
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11558411
Return-Path: <SRS0=rCNo=7B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 01AA490
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 19 May 2020 18:07:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DFA7020823
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 19 May 2020 18:07:52 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="KKsOPnyV"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729053AbgESSHv (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 19 May 2020 14:07:51 -0400
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:41556 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726447AbgESSHu (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 19 May 2020 14:07:50 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1589911669;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc; bh=megtxqWXyglz/CqjKs2x/itHX3lBYfTYHJlMu70hZuI=;
        b=KKsOPnyVaFxxXSdKBSyWtJRexuqmoI2RSQxtuJNaJ1V1aV18Bh9XxopsIGb9jM7MQJve0j
        n0HijRCfVCmd1BCvs6vfAI0KwZirku57BE4l9IW9xhM34wCbwk1J8TfgTK6j1aqMrzkJPJ
        osuewFLKItj97gssKItA4dh4ThP/1JI=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-426-8zS8eI4HPqOnJYwKbtq5eQ-1; Tue, 19 May 2020 14:07:46 -0400
X-MC-Unique: 8zS8eI4HPqOnJYwKbtq5eQ-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id ECE9A107ACCA;
        Tue, 19 May 2020 18:07:44 +0000 (UTC)
Received: from virtlab511.virt.lab.eng.bos.redhat.com
 (virtlab511.virt.lab.eng.bos.redhat.com [10.19.152.198])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 6367410016EB;
        Tue, 19 May 2020 18:07:44 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: oupton@google.com, stable@vger.kernel.org
Subject: [PATCH] KVM: x86: allow KVM_STATE_NESTED_MTF_PENDING in kvm_state
 flags
Date: Tue, 19 May 2020 14:07:43 -0400
Message-Id: <20200519180743.89974-1-pbonzini@redhat.com>
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The migration functionality was left incomplete in commit 5ef8acbdd687
("KVM: nVMX: Emulate MTF when performing instruction emulation", 2020-02-23),
fix it.

Fixes: 5ef8acbdd687 ("KVM: nVMX: Emulate MTF when performing instruction emulation")
Cc: stable@vger.kernel.org
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Oliver Upton <oupton@google.com>
---
 arch/x86/kvm/x86.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] KVM: x86: only do L1TF workaround on affected processors
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11557371
Return-Path: <SRS0=rCNo=7B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CE1E2912
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 19 May 2020 09:50:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B22D7207D8
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 19 May 2020 09:50:18 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="jAsSi/J6"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728432AbgESJuR (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 19 May 2020 05:50:17 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:44969 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726880AbgESJuQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 19 May 2020 05:50:16 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1589881815;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc; bh=SIVLP0DRrlKxQ6SwkqhvlChjQm02/QELWNEmHf7Q4zw=;
        b=jAsSi/J64TVF9eNiiWu29MxFTeIptlj5yspD+8+J36ugs+Y2OS5/ljqwzSQKIesRR3mGeJ
        l7nbUcEf2Eb9wX3j0H+oKFLVXZwPOpKFcZgLh40eE7Dzm46jnnrwFv+p1VzpJcIJev7loA
        /ON5sQddP/ZSY6Ej4szv6moWaksmjCs=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-471-CihpbDhtN7SvRQGJ7bl_JA-1; Tue, 19 May 2020 05:50:11 -0400
X-MC-Unique: CihpbDhtN7SvRQGJ7bl_JA-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id E966B1800D42;
        Tue, 19 May 2020 09:50:09 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 1775710013D9;
        Tue, 19 May 2020 09:50:08 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Tom Lendacky <thomas.lendacky@amd.com>,
        Maxim Levitsky <mlevitsk@redhat.com>, stable@vger.kernel.org
Subject: [PATCH] KVM: x86: only do L1TF workaround on affected processors
Date: Tue, 19 May 2020 05:50:08 -0400
Message-Id: <20200519095008.1212-1-pbonzini@redhat.com>
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

KVM stores the gfn in MMIO SPTEs as a caching optimization.  These are split
in two parts, as in "[high 11111 low]", to thwart any attempt to use these bits
in an L1TF attack.  This works as long as there are 5 free bits between
MAXPHYADDR and bit 50 (inclusive), leaving bit 51 free so that the MMIO
access triggers a reserved-bit-set page fault.

The bit positions however were computed wrongly for AMD processors that have
encryption support.  In this case, x86_phys_bits is reduced (for example
from 48 to 43, to account for the C bit at position 47 and four bits used
internally to store the SEV ASID and other stuff) while x86_cache_bits in
would remain set to 48, and _all_ bits between the reduced MAXPHYADDR
and bit 51 are set.  Then low_phys_bits would also cover some of the
bits that are set in the shadow_mmio_value, terribly confusing the gfn
caching mechanism.

To fix this, avoid splitting gfns as long as the processor does not have
the L1TF bug (which includes all AMD processors).  When there is no
splitting, low_phys_bits can be set to the reduced MAXPHYADDR removing
the overlap.  This fixes "npt=0" operation on EPYC processors.

Thanks to Maxim Levitsky for bisecting this bug.

Cc: stable@vger.kernel.org
Fixes: 52918ed5fcf0 ("KVM: SVM: Override default MMIO mask if memory encryption is enabled")
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Tested-by: Maxim Levitsky <mlevitsk@redhat.com>
Tested-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/mmu/mmu.c | 19 ++++++++++---------
 1 file changed, 10 insertions(+), 9 deletions(-)

```
#### [PATCH v2] KVM: x86: respect singlestep when emulating instruction
##### From: Felipe Franciosi <felipe@nutanix.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Felipe Franciosi <felipe@nutanix.com>
X-Patchwork-Id: 11557219
Return-Path: <SRS0=rCNo=7B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B723D13B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 19 May 2020 08:11:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9DD8620809
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 19 May 2020 08:11:24 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=sendgrid.net header.i=@sendgrid.net
 header.b="jV9LilP4"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726860AbgESILX (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 19 May 2020 04:11:23 -0400
Received: from o1.dev.nutanix.com ([198.21.4.205]:48131 "EHLO
        o1.dev.nutanix.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726595AbgESILX (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 19 May 2020 04:11:23 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=sendgrid.net;
        h=from:subject:mime-version:to:cc:content-transfer-encoding:
        content-type;
        s=smtpapi; bh=FyetZpafM/v6XIJbkIYr2RB7YlhXywPDsBHNjztNYEU=;
        b=jV9LilP4hIzcawYH20i8HqWNol8X/nZtdQwfcS/oscSi3owPPnqwiKr49kkuzPaKCyAl
        Qt7tHLBnVADXBEpCwTdw6+jr8o3pU0IaUDhw1IYxojxhwivOl/vA2yAjZQL81tDKzs9/Fk
        4CBYBxId495E61VR5bR7TsK71zYELPfAA=
Received: by filterdrecv-p3iad2-8ddf98858-lwgxm with SMTP id
 filterdrecv-p3iad2-8ddf98858-lwgxm-19-5EC394AA-1D
        2020-05-19 08:11:22.408630125 +0000 UTC m=+4691031.646325677
Received: from debian.localdomain (unknown)
        by ismtpd0008p1lon1.sendgrid.net (SG) with ESMTP
        id 6UUgXTmQRF-ABD9SVFhCQg
        Tue, 19 May 2020 08:11:22.067 +0000 (UTC)
From: Felipe Franciosi <felipe@nutanix.com>
Subject: [PATCH v2] KVM: x86: respect singlestep when emulating instruction
Date: Tue, 19 May 2020 08:11:22 +0000 (UTC)
Message-Id: <20200519081048.8204-1-felipe@nutanix.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-SG-EID: 
 W9goRmNI2M6BaZDnSanVWLdj2DuGbkuGfTWZsqFIAk59ONbkkaLXMDCghpkcaIPehS/Luf7/3t083SnZbMEjV/hVoVQYNCU8if+b2hfP+MkdnLaAkF5irJPrTFAwszS9YEc5FrwmrAteU06//ITgah6myXAmbMmxM6C+3EkrrrNN8umvDrKpUsgqrf8itVNQP48k41wcQgCHneucsOgbtgR/lp13n8xCFrqBMpg2A28H/G9RnojSy4A3oHkSdx8eYCYCivB+U4YHqkLLebiBWg==
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org, stable@vger.kernel.org,
        Felipe Franciosi <felipe@nutanix.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When userspace configures KVM_GUESTDBG_SINGLESTEP, KVM will manage the
presence of X86_EFLAGS_TF via kvm_set/get_rflags on vcpus. The actual
rflag bit is therefore hidden from callers.

That includes init_emulate_ctxt() which uses the value returned from
kvm_get_flags() to set ctxt->tf. As a result, x86_emulate_instruction()
will skip a single step, leaving singlestep_rip stale and not returning
to userspace.

This resolves the issue by observing the vcpu guest_debug configuration
alongside ctxt->tf in x86_emulate_instruction(), performing the single
step if set.

Signed-off-by: Felipe Franciosi <felipe@nutanix.com>
---
 arch/x86/kvm/x86.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [patch 1/7] x86/kvm: Move context tracking where it belongsReferences: <20200519203128.773151484@linutronix.de>
##### From: Thomas Gleixner <tglx@linutronix.de>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Gleixner <tglx@linutronix.de>
X-Patchwork-Id: 11558793
Return-Path: <SRS0=rCNo=7B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D4BF790
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 19 May 2020 21:13:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C636D2075F
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 19 May 2020 21:13:32 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727867AbgESVNa (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 19 May 2020 17:13:30 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:35564 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727803AbgESVNa (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 19 May 2020 17:13:30 -0400
Received: from Galois.linutronix.de (Galois.linutronix.de
 [IPv6:2a0a:51c0:0:12e:550::1])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id CCF26C08C5C0;
        Tue, 19 May 2020 14:13:29 -0700 (PDT)
Received: from p5de0bf0b.dip0.t-ipconnect.de ([93.224.191.11]
 helo=nanos.tec.linutronix.de)
        by Galois.linutronix.de with esmtpsa
 (TLS1.2:DHE_RSA_AES_256_CBC_SHA256:256)
        (Exim 4.80)
        (envelope-from <tglx@linutronix.de>)
        id 1jb9Y4-0001wu-6B; Tue, 19 May 2020 23:13:16 +0200
Received: from nanos.tec.linutronix.de (localhost [IPv6:::1])
        by nanos.tec.linutronix.de (Postfix) with ESMTP id B14A2100D00;
        Tue, 19 May 2020 23:13:15 +0200 (CEST)
Message-Id: <20200519211224.286191418@linutronix.de>
User-Agent: quilt/0.65
Date: Tue, 19 May 2020 22:31:29 +0200
From: Thomas Gleixner <tglx@linutronix.de>
To: LKML <linux-kernel@vger.kernel.org>
Cc: x86@kernel.org, Paolo Bonzini <pbonzini@redhat.com>,
        kvm@vger.kernel.org,
        Alexandre Chartre <alexandre.chartre@oracle.com>,
        Peter Zijlstra <peterz@infradead.org>,
        Juergen Gross <jgross@suse.com>,
        Tom Lendacky <thomas.lendacky@amd.com>
Subject: [patch 1/7] x86/kvm: Move context tracking where it belongs
References: <20200519203128.773151484@linutronix.de>
MIME-Version: 1.0
Content-transfer-encoding: 8-bit
X-Linutronix-Spam-Score: -1.0
X-Linutronix-Spam-Level: -
X-Linutronix-Spam-Status: No , -1.0 points, 5.0 required,
  ALL_TRUSTED=-1,SHORTCIRCUIT=-0.0001
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Context tracking for KVM happens way too early in the vcpu_run()
code. Anything after guest_enter_irqoff() and before guest_exit_irqoff()
cannot use RCU and should also be not instrumented.

The current way of doing this covers way too much code. Move it closer to
the actual vmenter/exit code.

Signed-off-by: Thomas Gleixner <tglx@linutronix.de>
Reviewed-by: Alexandre Chartre <alexandre.chartre@oracle.com>
Acked-by: Peter Zijlstra <peterz@infradead.org>
Acked-by: Paolo Bonzini <pbonzini@redhat.com>
Link: https://lkml.kernel.org/r/20200505134341.379326289@linutronix.de

```
