#### [PATCH v6 QEMU 2/3] virtio-balloon: Add bit to notify guest of unused page reporting
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Duyck <alexander.duyck@gmail.com>
X-Patchwork-Id: 11107257
Return-Path: <SRS0=nXzg=WR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A536D13A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 21 Aug 2019 15:00:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 836B020870
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 21 Aug 2019 15:00:43 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="k2a5K2EC"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729558AbfHUPAk (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 21 Aug 2019 11:00:40 -0400
Received: from mail-pl1-f193.google.com ([209.85.214.193]:39112 "EHLO
        mail-pl1-f193.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727725AbfHUPAj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 21 Aug 2019 11:00:39 -0400
Received: by mail-pl1-f193.google.com with SMTP id z3so1477461pln.6;
        Wed, 21 Aug 2019 08:00:39 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=subject:from:to:cc:date:message-id:in-reply-to:references
         :user-agent:mime-version:content-transfer-encoding;
        bh=VitjQQFQG7H0A5JYqbYhHy/YWDiYO6QESupJyX3H62U=;
        b=k2a5K2ECmdb6swy6bHd/xAA0MDd7K9ym8QEcuo2Yh8MrxSUDRJfnZxqnDcQyv0BZeB
         WUSY/nSZQqI+F6Y/vkkK+HYEaKGvN6UXSdDpJESF2TUJx/ITqTLIqvlc80XeABcTTJZ5
         znjbFUnyuBjiqOSg/b3a1bnhG+vBZjuk9oOKuKENGYfrcjcnIQZInnQ7woSmsbs2qXb1
         OuXaFOUvpnHlRCm7vwjNeRwd0ycNjxnBwMDZ4igLcN6CZPKg44vCqE2Sf+PcHG3jgFQ0
         hrqzlA5atInMjmpkGw0fz7iDvXvYYVgPB7mnEj9E37BHfHaHAvoDAQSkB9iryiY88Xlj
         Eyyg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:subject:from:to:cc:date:message-id:in-reply-to
         :references:user-agent:mime-version:content-transfer-encoding;
        bh=VitjQQFQG7H0A5JYqbYhHy/YWDiYO6QESupJyX3H62U=;
        b=Gap/iX6IGC2Go6Ahh+63P4e9YCj+2pFp8FOb9cHDjU3IAvbsHHhM/JC/26X64nFyol
         GL4HmyeNEkO3fFKb1sNmyrnj2v2o5s2VrtX6NvL1j9LwDBo/YbXWbGDLWTXaV9y/bhPf
         Y73JcElrp+/CcV0T0k20YTQM5dSPga8nqkopdIlU7JX+dkUe7hODuKdMvqPQ8+DLAzmw
         DJl8d2qqC2SZnmZi/oWWxoLmQAJGDcFHZmTdki+VGzg080T7BIS/r/Yq69tbqJViK9fs
         Bs1H7L4/e7X83Pe24fC4Su2E6kdv51UfT5qgsZepAPzicGS+BeDw0YdXRXfgHKpZPaRK
         4clA==
X-Gm-Message-State: APjAAAW1apht04/SqwTQSX3LIzg14YTA+78SXbkbVzH+FFsgkiTfgvk5
        Anjr24JlS1qCNDj0sJjW7g4=
X-Google-Smtp-Source: 
 APXvYqzoQn+RfX4vjD+nR26xkBjnL4PsFBTP+0Ha9xmMLH5TQ58gGkHGrSHmBFrhAWplNCl7l58xYQ==
X-Received: by 2002:a17:902:343:: with SMTP id
 61mr35450878pld.215.1566399638758;
        Wed, 21 Aug 2019 08:00:38 -0700 (PDT)
Received: from localhost.localdomain ([2001:470:b:9c3:9e5c:8eff:fe4f:f2d0])
        by smtp.gmail.com with ESMTPSA id
 e13sm29412309pfl.130.2019.08.21.08.00.37
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Wed, 21 Aug 2019 08:00:38 -0700 (PDT)
Subject: [PATCH v6 QEMU 2/3] virtio-balloon: Add bit to notify guest of
 unused page reporting
From: Alexander Duyck <alexander.duyck@gmail.com>
To: nitesh@redhat.com, kvm@vger.kernel.org, mst@redhat.com,
        david@redhat.com, dave.hansen@intel.com,
        linux-kernel@vger.kernel.org, linux-mm@kvack.org,
        akpm@linux-foundation.org, virtio-dev@lists.oasis-open.org
Cc: yang.zhang.wz@gmail.com, pagupta@redhat.com, riel@surriel.com,
        konrad.wilk@oracle.com, willy@infradead.org,
        lcapitulino@redhat.com, wei.w.wang@intel.com, aarcange@redhat.com,
        pbonzini@redhat.com, dan.j.williams@intel.com, mhocko@kernel.org,
        alexander.h.duyck@linux.intel.com, osalvador@suse.de
Date: Wed, 21 Aug 2019 08:00:37 -0700
Message-ID: <20190821150037.21485.3191.stgit@localhost.localdomain>
In-Reply-To: <20190821145806.20926.22448.stgit@localhost.localdomain>
References: <20190821145806.20926.22448.stgit@localhost.localdomain>
User-Agent: StGit/0.17.1-dirty
MIME-Version: 1.0
Content-Type: text/plain; charset="utf-8"
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Alexander Duyck <alexander.h.duyck@linux.intel.com>

Add a bit for the page reporting feature provided by virtio-balloon.

This patch should be replaced once the feature is added to the Linux kernel
and the bit is backported into this exported kernel header.

Signed-off-by: Alexander Duyck <alexander.h.duyck@linux.intel.com>
---
 include/standard-headers/linux/virtio_balloon.h |    1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH v6 QEMU 3/3] virtio-balloon: Provide a interface for unused page reporting
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Duyck <alexander.duyck@gmail.com>
X-Patchwork-Id: 11107261
Return-Path: <SRS0=nXzg=WR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1BDEF1399
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 21 Aug 2019 15:00:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E475322DD3
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 21 Aug 2019 15:00:49 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="tkfoMKNl"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729696AbfHUPAq (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 21 Aug 2019 11:00:46 -0400
Received: from mail-pl1-f195.google.com ([209.85.214.195]:33271 "EHLO
        mail-pl1-f195.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728437AbfHUPAp (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 21 Aug 2019 11:00:45 -0400
Received: by mail-pl1-f195.google.com with SMTP id go14so1483077plb.0;
        Wed, 21 Aug 2019 08:00:45 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=subject:from:to:cc:date:message-id:in-reply-to:references
         :user-agent:mime-version:content-transfer-encoding;
        bh=R9EIePxtKgh7rutMNGBvqWvR/nyIQIv1yBQVlI6lc80=;
        b=tkfoMKNl6R00u1CGr4goVFrz53AHxoV7hFxDcGeUp0tOZUCo+74t/zt8j+2QopIgxI
         EZ3M3c24Jl9SrsJM+dTZwK8SGp7tO2O/0yx89/oESAn4+Y33U06VmjCAJUF8WYGRwZeO
         eKjbkMOiSUf3GOoqrhSS+vgoRMpgqZeesnV5hVjONU4VcpdOzOxTu/6+rYJJelofQ2l3
         KrIWCI8aXlUCizR5/hSFEMJ0SFD0wRsscqpCzcEa6q+HWASFrKQeuvC0VTIT8+HbR6/e
         kIbuzlNFr7cnr7aQG0JZ89EPMqXTXef7jzZr4LRARx074pduHcDo0oZ2TTBh+XMIA1it
         tJhw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:subject:from:to:cc:date:message-id:in-reply-to
         :references:user-agent:mime-version:content-transfer-encoding;
        bh=R9EIePxtKgh7rutMNGBvqWvR/nyIQIv1yBQVlI6lc80=;
        b=N8uG4VLyAj2C8zZPu4NrH8iGwhXcdjEiiN5HJmGYr+sm3PFBf/Pyzwt7HlAussmJX5
         uuh2KCr/NVRpy/FCOi4MwQd/OjeyaG2OR1Prv6rNAAk3VCQa6B55H+LD3STNIPCi1otN
         ykB7gkK/YLqjz7ob2TZDlZU7vWNgQR9d+qUHujcnJSQdsgcvcGVQE5NLZ6+8G+Hka4+R
         NgWg86abCUhMb7jJ8pmBCKhxdY64hKNz8X7+E7iSTRQOeM4rCZ5ba3X0eyJNxES/XU/R
         +KrTvGKM/ZyRferwN3DMFc7JTQDKpqGCiY8HFxFU1wHvGGA1xuJUvu+W0FfDi0C/UOfc
         68hA==
X-Gm-Message-State: APjAAAXVraNnOmuk8yYcq4qFXu8idC4wI7b7ymwx4ZYuxqXc9CKUqeu1
        1PajkZFJpfKCBbJiJUsRzaHgqvXN
X-Google-Smtp-Source: 
 APXvYqzGZGBxE2Kux8cFfIoXPTej4Y3Rq0bhdauQWIpL/YOuwEUcP9xBJA0wE9MgWkUpeYVOa9xJ2g==
X-Received: by 2002:a17:902:6843:: with SMTP id
 f3mr31726895pln.97.1566399645002;
        Wed, 21 Aug 2019 08:00:45 -0700 (PDT)
Received: from localhost.localdomain ([2001:470:b:9c3:9e5c:8eff:fe4f:f2d0])
        by smtp.gmail.com with ESMTPSA id
 b19sm14248033pgs.10.2019.08.21.08.00.44
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Wed, 21 Aug 2019 08:00:44 -0700 (PDT)
Subject: [PATCH v6 QEMU 3/3] virtio-balloon: Provide a interface for unused
 page reporting
From: Alexander Duyck <alexander.duyck@gmail.com>
To: nitesh@redhat.com, kvm@vger.kernel.org, mst@redhat.com,
        david@redhat.com, dave.hansen@intel.com,
        linux-kernel@vger.kernel.org, linux-mm@kvack.org,
        akpm@linux-foundation.org, virtio-dev@lists.oasis-open.org
Cc: yang.zhang.wz@gmail.com, pagupta@redhat.com, riel@surriel.com,
        konrad.wilk@oracle.com, willy@infradead.org,
        lcapitulino@redhat.com, wei.w.wang@intel.com, aarcange@redhat.com,
        pbonzini@redhat.com, dan.j.williams@intel.com, mhocko@kernel.org,
        alexander.h.duyck@linux.intel.com, osalvador@suse.de
Date: Wed, 21 Aug 2019 08:00:43 -0700
Message-ID: <20190821150043.21485.84756.stgit@localhost.localdomain>
In-Reply-To: <20190821145806.20926.22448.stgit@localhost.localdomain>
References: <20190821145806.20926.22448.stgit@localhost.localdomain>
User-Agent: StGit/0.17.1-dirty
MIME-Version: 1.0
Content-Type: text/plain; charset="utf-8"
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Alexander Duyck <alexander.h.duyck@linux.intel.com>

Add support for what I am referring to as "unused page reporting".
Basically the idea is to function very similar to how the balloon works
in that we basically end up madvising the page as not being used. However
we don't really need to bother with any deflate type logic since the page
will be faulted back into the guest when it is read or written to.

This is meant to be a simplification of the existing balloon interface
to use for providing hints to what memory needs to be freed. I am assuming
this is safe to do as the deflate logic does not actually appear to do very
much other than tracking what subpages have been released and which ones
haven't.

Signed-off-by: Alexander Duyck <alexander.h.duyck@linux.intel.com>
---
 hw/virtio/virtio-balloon.c         |   46 ++++++++++++++++++++++++++++++++++--
 include/hw/virtio/virtio-balloon.h |    2 +-
 2 files changed, 45 insertions(+), 3 deletions(-)

```
#### [PATCH] arm64: KVM: Only skip MMIO insn once
##### From: Andrew Jones <drjones@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11108073
Return-Path: <SRS0=nXzg=WR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9D546112C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 21 Aug 2019 19:50:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 83C9322DD3
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 21 Aug 2019 19:50:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730081AbfHUTud (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 21 Aug 2019 15:50:33 -0400
Received: from mx1.redhat.com ([209.132.183.28]:55040 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729608AbfHUTud (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 21 Aug 2019 15:50:33 -0400
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 12DD6300183D;
        Wed, 21 Aug 2019 19:50:33 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.43.2.160])
        by smtp.corp.redhat.com (Postfix) with ESMTP id D03FC17D69;
        Wed, 21 Aug 2019 19:50:31 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org
Cc: maz@kernel.org, mark.rutland@arm.com
Subject: [PATCH] arm64: KVM: Only skip MMIO insn once
Date: Wed, 21 Aug 2019 21:50:30 +0200
Message-Id: <20190821195030.2569-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.5.16 (mx1.redhat.com [10.5.110.40]);
 Wed, 21 Aug 2019 19:50:33 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If after an MMIO exit to userspace a VCPU is immediately run with an
immediate_exit request, such as when a signal is delivered or an MMIO
emulation completion is needed, then the VCPU completes the MMIO
emulation and immediately returns to userspace. As the exit_reason
does not get changed from KVM_EXIT_MMIO in these cases we have to
be careful not to complete the MMIO emulation again, when the VCPU is
eventually run again, because the emulation does an instruction skip
(and doing too many skips would be a waste of guest code :-) We need
to use additional VCPU state to track if the emulation is complete.
As luck would have it, we already have 'mmio_needed', which even
appears to be used in this way by other architectures already.

Fixes: 0d640732dbeb ("arm64: KVM: Skip MMIO insn after emulation")
Signed-off-by: Andrew Jones <drjones@redhat.com>
---
 virt/kvm/arm/arm.c  | 3 ++-
 virt/kvm/arm/mmio.c | 1 +
 2 files changed, 3 insertions(+), 1 deletion(-)

```
#### [PATCH v3 01/10] KVM: arm64: Document PV-time interface
##### From: Steven Price <steven.price@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Steven Price <Steven.Price@arm.com>
X-Patchwork-Id: 11107385
Return-Path: <SRS0=nXzg=WR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0CDE41399
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 21 Aug 2019 15:38:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E8E702339E
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 21 Aug 2019 15:38:12 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730091AbfHUPhR (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 21 Aug 2019 11:37:17 -0400
Received: from foss.arm.com ([217.140.110.172]:60340 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728848AbfHUPhQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 21 Aug 2019 11:37:16 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 9B225360;
        Wed, 21 Aug 2019 08:37:15 -0700 (PDT)
Received: from e112269-lin.arm.com (e112269-lin.cambridge.arm.com
 [10.1.196.133])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 995FD3F718;
        Wed, 21 Aug 2019 08:37:13 -0700 (PDT)
From: Steven Price <steven.price@arm.com>
To: Marc Zyngier <maz@kernel.org>, Will Deacon <will@kernel.org>,
        linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu
Cc: Steven Price <steven.price@arm.com>,
 Catalin Marinas <catalin.marinas@arm.com>,
 Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Russell King <linux@armlinux.org.uk>, James Morse <james.morse@arm.com>,
 Julien Thierry <julien.thierry.kdev@gmail.com>,
 Suzuki K Pouloze <suzuki.poulose@arm.com>,
 Mark Rutland <mark.rutland@arm.com>, kvm@vger.kernel.org,
 linux-doc@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH v3 01/10] KVM: arm64: Document PV-time interface
Date: Wed, 21 Aug 2019 16:36:47 +0100
Message-Id: <20190821153656.33429-2-steven.price@arm.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20190821153656.33429-1-steven.price@arm.com>
References: <20190821153656.33429-1-steven.price@arm.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Introduce a paravirtualization interface for KVM/arm64 based on the
"Arm Paravirtualized Time for Arm-Base Systems" specification DEN 0057A.

This only adds the details about "Stolen Time" as the details of "Live
Physical Time" have not been fully agreed.

User space can specify a reserved area of memory for the guest and
inform KVM to populate the memory with information on time that the host
kernel has stolen from the guest.

A hypercall interface is provided for the guest to interrogate the
hypervisor's support for this interface and the location of the shared
memory structures.

Signed-off-by: Steven Price <steven.price@arm.com>
---
 Documentation/virt/kvm/arm/pvtime.txt | 100 ++++++++++++++++++++++++++
 1 file changed, 100 insertions(+)
 create mode 100644 Documentation/virt/kvm/arm/pvtime.txt

diff --git a/Documentation/virt/kvm/arm/pvtime.txt b/Documentation/virt/kvm/arm/pvtime.txt
new file mode 100644
index 000000000000..1ceb118694e7
--- /dev/null
+++ b/Documentation/virt/kvm/arm/pvtime.txt
@@ -0,0 +1,100 @@
+Paravirtualized time support for arm64
+======================================
+
+Arm specification DEN0057/A defined a standard for paravirtualised time
+support for AArch64 guests:
+
+https://developer.arm.com/docs/den0057/a
+
+KVM/arm64 implements the stolen time part of this specification by providing
+some hypervisor service calls to support a paravirtualized guest obtaining a
+view of the amount of time stolen from its execution.
+
+Two new SMCCC compatible hypercalls are defined:
+
+PV_FEATURES 0xC5000020
+PV_TIME_ST  0xC5000022
+
+These are only available in the SMC64/HVC64 calling convention as
+paravirtualized time is not available to 32 bit Arm guests. The existence of
+the PV_FEATURES hypercall should be probed using the SMCCC 1.1 ARCH_FEATURES
+mechanism before calling it.
+
+PV_FEATURES
+    Function ID:  (uint32)  : 0xC5000020
+    PV_func_id:   (uint32)  : Either PV_TIME_LPT or PV_TIME_ST
+    Return value: (int32)   : NOT_SUPPORTED (-1) or SUCCESS (0) if the relevant
+                              PV-time feature is supported by the hypervisor.
+
+PV_TIME_ST
+    Function ID:  (uint32)  : 0xC5000022
+    Return value: (int64)   : IPA of the stolen time data structure for this
+                              (V)CPU. On failure:
+                              NOT_SUPPORTED (-1)
+
+The IPA returned by PV_TIME_ST should be mapped by the guest as normal memory
+with inner and outer write back caching attributes, in the inner shareable
+domain. A total of 16 bytes from the IPA returned are guaranteed to be
+meaningfully filled by the hypervisor (see structure below).
+
+PV_TIME_ST returns the structure for the calling VCPU.
+
+Stolen Time
+-----------
+
+The structure pointed to by the PV_TIME_ST hypercall is as follows:
+
+  Field       | Byte Length | Byte Offset | Description
+  ----------- | ----------- | ----------- | --------------------------
+  Revision    |      4      |      0      | Must be 0 for version 0.1
+  Attributes  |      4      |      4      | Must be 0
+  Stolen time |      8      |      8      | Stolen time in unsigned
+              |             |             | nanoseconds indicating how
+              |             |             | much time this VCPU thread
+              |             |             | was involuntarily not
+              |             |             | running on a physical CPU.
+
+The structure will be updated by the hypervisor prior to scheduling a VCPU. It
+will be present within a reserved region of the normal memory given to the
+guest. The guest should not attempt to write into this memory. There is a
+structure per VCPU of the guest.
+
+User space interface
+====================
+
+User space can request that KVM provide the paravirtualized time interface to
+a guest by creating a KVM_DEV_TYPE_ARM_PV_TIME device, for example:
+
+    struct kvm_create_device pvtime_device = {
+            .type = KVM_DEV_TYPE_ARM_PV_TIME,
+            .attr = 0,
+            .flags = 0,
+    };
+
+    pvtime_fd = ioctl(vm_fd, KVM_CREATE_DEVICE, &pvtime_device);
+
+Creation of the device should be done after creating the vCPUs of the virtual
+machine.
+
+The IPA of the structures must be given to KVM. This is the base address
+of an array of stolen time structures (one for each VCPU). The base address
+must be page aligned. The size must be at least 64 * number of VCPUs and be a
+multiple of PAGE_SIZE.
+
+The memory for these structures should be added to the guest in the usual
+manner (e.g. using KVM_SET_USER_MEMORY_REGION).
+
+For example:
+
+    struct kvm_dev_arm_st_region region = {
+            .gpa = <IPA of guest base address>,
+            .size = <size in bytes>
+    };
+
+    struct kvm_device_attr st_base = {
+            .group = KVM_DEV_ARM_PV_TIME_PADDR,
+            .attr = KVM_DEV_ARM_PV_TIME_ST,
+            .addr = (u64)&region
+    };
+
+    ioctl(pvtime_fd, KVM_SET_DEVICE_ATTR, &st_base);

From patchwork Wed Aug 21 15:36:48 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Steven Price <Steven.Price@arm.com>
X-Patchwork-Id: 11107383
Return-Path: <SRS0=nXzg=WR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 397D61399
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 21 Aug 2019 15:38:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 0E40622DD3
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 21 Aug 2019 15:38:11 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730109AbfHUPhT (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 21 Aug 2019 11:37:19 -0400
Received: from foss.arm.com ([217.140.110.172]:60354 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728848AbfHUPhT (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 21 Aug 2019 11:37:19 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 15760337;
        Wed, 21 Aug 2019 08:37:18 -0700 (PDT)
Received: from e112269-lin.arm.com (e112269-lin.cambridge.arm.com
 [10.1.196.133])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 D17963F718;
        Wed, 21 Aug 2019 08:37:15 -0700 (PDT)
From: Steven Price <steven.price@arm.com>
To: Marc Zyngier <maz@kernel.org>, Will Deacon <will@kernel.org>,
        linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu
Cc: Steven Price <steven.price@arm.com>,
 Catalin Marinas <catalin.marinas@arm.com>,
 Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Russell King <linux@armlinux.org.uk>, James Morse <james.morse@arm.com>,
 Julien Thierry <julien.thierry.kdev@gmail.com>,
 Suzuki K Pouloze <suzuki.poulose@arm.com>,
 Mark Rutland <mark.rutland@arm.com>, kvm@vger.kernel.org,
 linux-doc@vger.kernel.org, linux-kernel@vger.kernel.org,
 Christoffer Dall <christoffer.dall@arm.com>
Subject: [PATCH v3 02/10] KVM: arm/arm64: Factor out hypercall handling from
 PSCI code
Date: Wed, 21 Aug 2019 16:36:48 +0100
Message-Id: <20190821153656.33429-3-steven.price@arm.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20190821153656.33429-1-steven.price@arm.com>
References: <20190821153656.33429-1-steven.price@arm.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Christoffer Dall <christoffer.dall@arm.com>

We currently intertwine the KVM PSCI implementation with the general
dispatch of hypercall handling, which makes perfect sense because PSCI
is the only category of hypercalls we support.

However, as we are about to support additional hypercalls, factor out
this functionality into a separate hypercall handler file.

Signed-off-by: Christoffer Dall <christoffer.dall@arm.com>
[steven.price@arm.com: rebased]
Signed-off-by: Steven Price <steven.price@arm.com>
---
 arch/arm/kvm/Makefile        |  2 +-
 arch/arm/kvm/handle_exit.c   |  2 +-
 arch/arm64/kvm/Makefile      |  1 +
 arch/arm64/kvm/handle_exit.c |  4 +-
 include/kvm/arm_hypercalls.h | 43 ++++++++++++++++++
 include/kvm/arm_psci.h       |  2 +-
 virt/kvm/arm/hypercalls.c    | 59 +++++++++++++++++++++++++
 virt/kvm/arm/psci.c          | 84 +-----------------------------------
 8 files changed, 110 insertions(+), 87 deletions(-)
 create mode 100644 include/kvm/arm_hypercalls.h
 create mode 100644 virt/kvm/arm/hypercalls.c

```
#### [GIT PULL] KVM fixes for Linux 5.3-rc6
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11107607
Return-Path: <SRS0=nXzg=WR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0E29E1395
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 21 Aug 2019 17:37:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E14E2233FC
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 21 Aug 2019 17:37:00 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="Z7SZLu+1"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729977AbfHURg5 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 21 Aug 2019 13:36:57 -0400
Received: from mail-wm1-f65.google.com ([209.85.128.65]:40612 "EHLO
        mail-wm1-f65.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728535AbfHURg5 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 21 Aug 2019 13:36:57 -0400
Received: by mail-wm1-f65.google.com with SMTP id c5so2777632wmb.5;
        Wed, 21 Aug 2019 10:36:55 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id;
        bh=smhXu1L5t6GuvxXpM02oEkcG3qy/NF91cs0u42tWNQM=;
        b=Z7SZLu+1OWPt/QYrEf3gyDmxq2SiRh/WlDoNoD9cXWQW8PfO6Bg2S6A72046Wbb69b
         fuqPMdlWe2O0FipE/J1iPyhMAOp7BTcYSDB51HiqDqy9fDCeQ/seS7z0aTYhrcPhDsEd
         iK52/paX6q2MJNbM35hzjgnq3X6nebfa9TLxD+KLpSlw+bWeXUQnGfF8nI6xKw+ELGbs
         wWr5BIRKIPEdW/826poZAbTrS7mUqW9Oh5ixr04Z8t8TXEy3WsIAnUYcBh0THUSdoWWw
         jwyempdtrYCOpPNfUUkuw4gNXiuA5KV11Ej5F9qL4lZ6DMhAsM7pEZM2igDG2A4aGTO7
         NdpA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id;
        bh=smhXu1L5t6GuvxXpM02oEkcG3qy/NF91cs0u42tWNQM=;
        b=DKy0LCB2LVqwtAyd4Op0oZW0/X/7GJQ3MPANVt50XikgDRX86eQF8gW5U4i5WZPRoP
         CXx/kQE7Ae2HkCuputTDqs/y0DKW0tbTa37e22c1nZ70Ly8S7NooJBuCJatfW1fr3SR7
         aqtXXidLqgBiCVEvo7cpo3Iloxtn9LNwQGocJin1QgB3kTma1VnXi2vssTfDeP+RNUyb
         YRxVdpb2DT139v/omDBjlB3HE6i7R8vE7lThB+kLw6IvpX2NgnU4sMqgg1An/kgCMEb0
         DMXniCZM0cBJ9JlAbSUIpIjXAioi1208zHGRMuz5pS3l7oiQwIDW7WA4g8vsGp4vueAh
         rUWQ==
X-Gm-Message-State: APjAAAXym44ZtrQwMsbSRPR1pIYK0eOWlpbFv0tIJaKdf+/ZNMHCxrIM
        19zBqjvHYD4HUwEzkumYua0=
X-Google-Smtp-Source: 
 APXvYqyXNaXwSC85caOVq0J3S9SmTrgdefplsopEPHCiE6o/zPmn3cLlBkTYVCg6pWayt8sHC4PbyA==
X-Received: by 2002:a1c:9ad8:: with SMTP id
 c207mr1246531wme.145.1566409014779;
        Wed, 21 Aug 2019 10:36:54 -0700 (PDT)
Received: from 640k.localdomain.com ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id 2sm1109217wmz.16.2019.08.21.10.36.52
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Wed, 21 Aug 2019 10:36:53 -0700 (PDT)
From: Paolo Bonzini <pbonzini@redhat.com>
To: torvalds@linux-foundation.org
Cc: linux-kernel@vger.kernel.org, rkrcmar@redhat.com,
        kvm@vger.kernel.org
Subject: [GIT PULL] KVM fixes for Linux 5.3-rc6
Date: Wed, 21 Aug 2019 19:36:50 +0200
Message-Id: <1566409010-50104-1-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Linus,

The following changes since commit a738b5e75b4c13be3485c82eb62c30047aa9f164:

  Merge tag 'kvmarm-fixes-for-5.3-2' of git://git.kernel.org/pub/scm/linux/kernel/git/kvmarm/kvmarm into HEAD (2019-08-09 16:53:50 +0200)

are available in the git repository at:


  https://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to e4427372398c31f57450565de277f861a4db5b3b:

  selftests/kvm: make platform_info_test pass on AMD (2019-08-21 19:08:18 +0200)

----------------------------------------------------------------
* A couple bugfixes, and mostly selftests changes.

----------------------------------------------------------------
Miaohe Lin (1):
      KVM: x86: svm: remove redundant assignment of var new_entry

Paolo Bonzini (7):
      MAINTAINERS: change list for KVM/s390
      MAINTAINERS: add KVM x86 reviewers
      selftests: kvm: do not try running the VM in vmx_set_nested_state_test
      selftests: kvm: provide common function to enable eVMCS
      selftests: kvm: fix vmx_set_nested_state_test
      selftests: kvm: fix state save/load on processors without XSAVE
      Revert "KVM: x86/mmu: Zap only the relevant pages when removing a memslot"

Radim Krcmar (1):
      kvm: x86: skip populating logical dest map if apic is not sw enabled

Vitaly Kuznetsov (1):
      selftests/kvm: make platform_info_test pass on AMD

 MAINTAINERS                                        | 19 +++++++------
 arch/x86/kvm/lapic.c                               |  5 ++++
 arch/x86/kvm/mmu.c                                 | 33 +---------------------
 arch/x86/kvm/svm.c                                 |  1 -
 tools/testing/selftests/kvm/include/evmcs.h        |  2 ++
 tools/testing/selftests/kvm/lib/x86_64/processor.c | 16 +++++++----
 tools/testing/selftests/kvm/lib/x86_64/vmx.c       | 20 +++++++++++++
 tools/testing/selftests/kvm/x86_64/evmcs_test.c    | 15 ++--------
 tools/testing/selftests/kvm/x86_64/hyperv_cpuid.c  | 12 +++-----
 .../selftests/kvm/x86_64/platform_info_test.c      |  2 +-
 .../kvm/x86_64/vmx_set_nested_state_test.c         | 32 +++++++++------------
 11 files changed, 69 insertions(+), 88 deletions(-)
```
#### [PATCH] kvm: x86: Add Intel PMU MSRs to msrs_to_save[]From: Jim Mattson <jmattson@google.com>
##### From: Jim Mattson <jmattson@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jim Mattson <jmattson@google.com>
X-Patchwork-Id: 11107853
Return-Path: <SRS0=nXzg=WR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8897614DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 21 Aug 2019 18:20:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 675D12339E
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 21 Aug 2019 18:20:17 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="PL4GW/z+"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728639AbfHUSUQ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 21 Aug 2019 14:20:16 -0400
Received: from mail-vs1-f74.google.com ([209.85.217.74]:40743 "EHLO
        mail-vs1-f74.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727099AbfHUSUQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 21 Aug 2019 14:20:16 -0400
Received: by mail-vs1-f74.google.com with SMTP id y7so1060220vsq.7
        for <kvm@vger.kernel.org>; Wed, 21 Aug 2019 11:20:15 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=XOWLAgp0P8npFc8OAOfS4Qa4ZgriqhnGg7/Zma2VF2Y=;
        b=PL4GW/z+KdvWg8PgiliXgFESGa1f8UQXyd+7ri//f/7ac44KtIJPu57pb7RcP4x5CE
         YsVSa2XFokfd36Rh9twwQxbLrS3Ean1MUAjsfUqJRtTQhoN3RPycoBF8PZgs00WnpeJq
         HMqlX5qxJEavzolTIgMKI2L7kfV0sQCfJUngnemvBtwrMDcIgKFkHOt+hgglaLop/d04
         HOGhzWi6d9qVF+OGKQ4YrGSlX4M79EdWNs3OFWB140ZR6AXTlqvb+tUv9K/YCtB9Q59E
         HG0qmpwWMcVa4av4G8PBrMgwLS/JzGvZtAXgQD2+soMohQ/y2xXx1jMo4+2s8TmpHGP0
         piyA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=XOWLAgp0P8npFc8OAOfS4Qa4ZgriqhnGg7/Zma2VF2Y=;
        b=sS8HJPrEeBzUN3YmV9jI22HVEiRS80a65/J/EcK7uRmwM+wDG/BQhenDEm3MhZtQ8a
         pkUiqejMrPhEkwm16WuH/x9hZuzxqxiskTSF+0VvF9gMl5kyB1fNVKjcdxkvuES83WJl
         qc571oi4aZvMRBOtofWtt2pRaAweWyiDoOQnHml/cG0/dUrsPYZlp6iGGIWG2jPnZ1TI
         BD2POrLVUHhX3uKY5y2V8yvoavoXwYVC6HoARHjyvU5g6EtENq9q/h4bPJokE7oDAwpE
         tKQJNhUuReVC3IQfCBXTbUbJdOjz5M6ceG6BCCgFUor0MGc/IgIC8WXNfh0kaEWyRO3b
         F4zg==
X-Gm-Message-State: APjAAAVx4qVHwHvNLFS8ZBTtT+bVob0yETlcCp/Z359UM1AKF99h1dZ5
        x1ws3q63OLPGrUGJ/waLn6zejJJlXmmWNIX1KV3x41Iu1kM+aP6uvV+zNGCbkkQVseDE39kK/+w
        jIYUB6Kz2YIViHSRUV+BBXGBtpIwbpGhLPXvXeeZwYWtIR2oMw3aqO3eRy0kgxnI=
X-Google-Smtp-Source: 
 APXvYqyOtN6QsibogCg7LnU0B3aINk4w+2zic8k4fpKIkx0+JNYB93greEYNIPRkpmXkkZ7gyDjNpsDP9SKReg==
X-Received: by 2002:ab0:240e:: with SMTP id f14mr3249017uan.26.1566411614472;
 Wed, 21 Aug 2019 11:20:14 -0700 (PDT)
Date: Wed, 21 Aug 2019 11:20:04 -0700
Message-Id: <20190821182004.102768-1-jmattson@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.23.0.187.g17f5b7556c-goog
Subject: [PATCH] kvm: x86: Add Intel PMU MSRs to msrs_to_save[]
From: Jim Mattson <jmattson@google.com>
To: kvm@vger.kernel.org
Cc: Jim Mattson <jmattson@google.com>,
        Eric Hankland <ehankland@google.com>,
        Peter Shier <pshier@google.com>
Content-Type: text/plain; charset="UTF-8"
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

These MSRs should be enumerated by KVM_GET_MSR_INDEX_LIST, so that
userspace knows that these MSRs may be part of the vCPU state.

Signed-off-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Eric Hankland <ehankland@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
---
 arch/x86/kvm/x86.c | 41 +++++++++++++++++++++++++++++++++++++++++
 1 file changed, 41 insertions(+)

```
#### [PATCH 1/3] KVM: x86: fix reporting of AMD speculation bug CPUID leaf
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11106097
Return-Path: <SRS0=nXzg=WR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3AE311395
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 21 Aug 2019 08:26:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 181C92339E
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 21 Aug 2019 08:26:56 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="ZULk9xeI"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727455AbfHUI0s (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 21 Aug 2019 04:26:48 -0400
Received: from mail-wm1-f65.google.com ([209.85.128.65]:39166 "EHLO
        mail-wm1-f65.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727107AbfHUI0s (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 21 Aug 2019 04:26:48 -0400
Received: by mail-wm1-f65.google.com with SMTP id i63so1195955wmg.4;
        Wed, 21 Aug 2019 01:26:46 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id:in-reply-to:references;
        bh=nwX/48Ia7d2dRgMHoMgDxjTtTXX3pmd4YgGY1f3Mcbg=;
        b=ZULk9xeIJuv1XoFXog3/KZs2+L80kTNWp4MkFqWfibqPuHiMoIYJ1EHN5CXMu87HKk
         TXsZ3YK9TdmFxEhnPy2G2nhjyaglkv+pyMaDM0djtXs7FNeHSjHxXdkscuKKwhCz6bHo
         Ysw7c0sulOGiQWZwa3lZ8eWk2FLi9/DHJ7oshYYNrA707T5EUQyRTme2ErNeYs7hkvrr
         hO44+hOKaXEd6U4opIUnBjIyFRS2nU5l+WdZDPKJaB7khl3fut4+9uavVOw/H5kWfLv+
         dqfcHBBfM0E+84nNhPh8OC5yBQjNW8iry7YMaHHiYL5ldaLSoQj/p5FkyOW2XL3IBsdD
         h4Pg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id
         :in-reply-to:references;
        bh=nwX/48Ia7d2dRgMHoMgDxjTtTXX3pmd4YgGY1f3Mcbg=;
        b=PygTowU/BVJGwiye0FWZ1z7AMm1VXyLjqf4IPK4cI+VzkzwHhZMosMjQS6ad7yEkde
         5eK5FIGN8UZsDsm50Gn76M8E4BQ3MFQHQvNcXDRUt3+6IXGX+XIuQibZvilKWkm8SJbO
         5/CcApTY4YsV8GREdDKe6HDL409kqpoyodYosnnpDBzuh+0lg9CtZ+ZiWa5pvNIadXGZ
         Fw9zJULfpT1May8HeFGO1cntyRbVJ9J8Wes8EFr77NJQkKlfAGijsW41fYgY8OsovSvK
         Cpq91E05pFG1/9rX0qHk1iuJWBrOFtAmiyPbIf2kuBFevIlzhLi4hEg9nqd3oWFEuKXc
         hNng==
X-Gm-Message-State: APjAAAXHAAO+6Y1XrlmOVH/QJEGsOUgByd/0BnC/yYESo4uw/cv3QhFg
        jka3VFlQRV4xMR9NWRk54LuWxf4udHI=
X-Google-Smtp-Source: 
 APXvYqynhnmicUQQOOG75MVstq+5H1fNWaUgK9qQiE62egUfeFJKxzkXHxu7i6FLV/9QLM/pzsl6Sw==
X-Received: by 2002:a7b:c5c2:: with SMTP id n2mr4835665wmk.9.1566376005834;
        Wed, 21 Aug 2019 01:26:45 -0700 (PDT)
Received: from 640k.localdomain.com ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 w5sm2931892wmm.43.2019.08.21.01.26.44
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Wed, 21 Aug 2019 01:26:45 -0700 (PDT)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: jmattson@redhat.com, ehabkost@redhat.com, konrad.wilk@oracle.com
Subject: [PATCH 1/3] KVM: x86: fix reporting of AMD speculation bug CPUID leaf
Date: Wed, 21 Aug 2019 10:26:40 +0200
Message-Id: <1566376002-17121-2-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1566376002-17121-1-git-send-email-pbonzini@redhat.com>
References: <1566376002-17121-1-git-send-email-pbonzini@redhat.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The AMD_* bits have to be set from the vendor-independent
feature and bug flags, because KVM_GET_SUPPORTED_CPUID does not care
about the vendor and they should be set on Intel processors as well.
On top of this, SSBD, STIBP and AMD_SSB_NO bit were not set, and
VIRT_SSBD does not have to be added manually because it is a
cpufeature that comes directly from the host's CPUID bit.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 arch/x86/kvm/cpuid.c | 21 +++++++++++++--------
 1 file changed, 13 insertions(+), 8 deletions(-)

```
#### [PATCH v6 1/6] mm: Adjust shuffle code to allow for future coalescing
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Duyck <alexander.duyck@gmail.com>
X-Patchwork-Id: 11107229
Return-Path: <SRS0=nXzg=WR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 880611399
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 21 Aug 2019 14:59:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 530E3233A0
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 21 Aug 2019 14:59:38 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="Ou5ImC3G"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729302AbfHUO7e (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 21 Aug 2019 10:59:34 -0400
Received: from mail-pl1-f195.google.com ([209.85.214.195]:36307 "EHLO
        mail-pl1-f195.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729275AbfHUO7e (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 21 Aug 2019 10:59:34 -0400
Received: by mail-pl1-f195.google.com with SMTP id f19so1476081plr.3;
        Wed, 21 Aug 2019 07:59:33 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=subject:from:to:cc:date:message-id:in-reply-to:references
         :user-agent:mime-version:content-transfer-encoding;
        bh=Yi6WYldnJwTaPPOKzplfbrsRDAV4yzenPtD5HnKNjwo=;
        b=Ou5ImC3GBWLUA3lNlDGYzW9zKH8bQG7N1Zr3BtiSZJohqsohONH6X8mExc+KJ/Wbue
         JryEZFiOIykwXbFlgvve2CenotVcXC5co1SiZwHIGlY6VYCP8LFv1zsgoukWazWwKNBx
         DvmoP8VqsS6bis4uhMzRkKePCNfq3OM/fKWUqd64uXIagRBnrmhwc6FzZ4dCCf2TQNXp
         4XlVqehLeqJ1un7OQRGKikDZ9SUXcWtBw4ihdq7lQRuKkGnW7x6KsoSWFhon5u5ceish
         uBtE9Q5g7RDqh+NJjEXtBmIB0Pez4RdMSb0Ek25uxyFFLRnu8xOdonioV6KQUC4ug/eS
         Stjw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:subject:from:to:cc:date:message-id:in-reply-to
         :references:user-agent:mime-version:content-transfer-encoding;
        bh=Yi6WYldnJwTaPPOKzplfbrsRDAV4yzenPtD5HnKNjwo=;
        b=n3II+GqK9ol/U8WP7ZkxF6jr7WKeLOwVXwEXdehWBuhICg7XqYSfCSmQCCFWvJh396
         EJz8SFeBQ1+EJ5Toze8Yvk4XU4Juz1pa140p7EDZD4Q/puaRL/FUoZ/eI/uQUyGSwYhh
         Qi0kaCizqH/Ge3PRLMl8VCzQgesgd3xsTUtwt9JdiKNKPZitWEq8hdRmJZgpncx5Qbai
         P4T8orB0rqG+roGuG3x5YX6yAjSHTjkP2jUKEGMmjvM8gz98tZNKFVVszJNZ13q+uBiC
         1HwF0FIzOhtLPLfYHBIe+q+vHD19xrSiVgW9YeH03tMxitMsATOlz/yPMaPrCukHow8V
         /MwA==
X-Gm-Message-State: APjAAAXFucs0g8GPA/+CZjK+GvJEDcTAbAkNFWP6o5Bb9nLFpYu6EOz+
        YSp1G5vQXwaiasUsLthHkOg=
X-Google-Smtp-Source: 
 APXvYqz5V42dlogvFa4VorG9G5jfX3kPnSUuUtoaDltscBozsmGw0roKd7pCjPB8WcWJHylzLnxqAg==
X-Received: by 2002:a17:902:6a88:: with SMTP id
 n8mr34233623plk.70.1566399572654;
        Wed, 21 Aug 2019 07:59:32 -0700 (PDT)
Received: from localhost.localdomain ([2001:470:b:9c3:9e5c:8eff:fe4f:f2d0])
        by smtp.gmail.com with ESMTPSA id
 n10sm21949644pgv.67.2019.08.21.07.59.31
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Wed, 21 Aug 2019 07:59:32 -0700 (PDT)
Subject: [PATCH v6 1/6] mm: Adjust shuffle code to allow for future
 coalescing
From: Alexander Duyck <alexander.duyck@gmail.com>
To: nitesh@redhat.com, kvm@vger.kernel.org, mst@redhat.com,
        david@redhat.com, dave.hansen@intel.com,
        linux-kernel@vger.kernel.org, willy@infradead.org,
        mhocko@kernel.org, linux-mm@kvack.org, akpm@linux-foundation.org,
        virtio-dev@lists.oasis-open.org, osalvador@suse.de
Cc: yang.zhang.wz@gmail.com, pagupta@redhat.com, riel@surriel.com,
        konrad.wilk@oracle.com, lcapitulino@redhat.com,
        wei.w.wang@intel.com, aarcange@redhat.com, pbonzini@redhat.com,
        dan.j.williams@intel.com, alexander.h.duyck@linux.intel.com
Date: Wed, 21 Aug 2019 07:59:31 -0700
Message-ID: <20190821145931.20926.97386.stgit@localhost.localdomain>
In-Reply-To: <20190821145806.20926.22448.stgit@localhost.localdomain>
References: <20190821145806.20926.22448.stgit@localhost.localdomain>
User-Agent: StGit/0.17.1-dirty
MIME-Version: 1.0
Content-Type: text/plain; charset="utf-8"
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Alexander Duyck <alexander.h.duyck@linux.intel.com>

Move the head/tail adding logic out of the shuffle code and into the
__free_one_page function since ultimately that is where it is really
needed anyway. By doing this we should be able to reduce the overhead
and can consolidate all of the list addition bits in one spot.

While changing out the code I also opted to go for a bit more thread safe
approach to getting the boolean value. This way we can avoid possible cache
line bouncing of the batched entropy between CPUs.

Signed-off-by: Alexander Duyck <alexander.h.duyck@linux.intel.com>
---
 include/linux/mmzone.h |   12 --------
 mm/page_alloc.c        |   70 +++++++++++++++++++++++++++---------------------
 mm/shuffle.c           |   40 ++++++++++++++++-----------
 mm/shuffle.h           |   12 ++++++++
 4 files changed, 75 insertions(+), 59 deletions(-)

```
#### [kvm-unit-tests PATCH v2 1/4] s390x: Support PSW restart boot
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11106341
Return-Path: <SRS0=nXzg=WR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3BFF7174A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 21 Aug 2019 10:48:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 21A88233A1
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 21 Aug 2019 10:48:41 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727123AbfHUKsk (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 21 Aug 2019 06:48:40 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:26642 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727063AbfHUKsk (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 21 Aug 2019 06:48:40 -0400
Received: from pps.filterd (m0098399.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 x7LAmRq9127711
        for <kvm@vger.kernel.org>; Wed, 21 Aug 2019 06:48:39 -0400
Received: from e06smtp01.uk.ibm.com (e06smtp01.uk.ibm.com [195.75.94.97])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2uh2nu50b2-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Wed, 21 Aug 2019 06:48:39 -0400
Received: from localhost
        by e06smtp01.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Wed, 21 Aug 2019 11:48:17 +0100
Received: from b06avi18878370.portsmouth.uk.ibm.com (9.149.26.194)
        by e06smtp01.uk.ibm.com (192.168.101.131) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Wed, 21 Aug 2019 11:48:14 +0100
Received: from d06av26.portsmouth.uk.ibm.com (d06av26.portsmouth.uk.ibm.com
 [9.149.105.62])
        by b06avi18878370.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id x7LAmE8S30802248
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 21 Aug 2019 10:48:14 GMT
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 06727AE04D;
        Wed, 21 Aug 2019 10:48:14 +0000 (GMT)
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id D6E21AE045;
        Wed, 21 Aug 2019 10:48:12 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.145.3.179])
        by d06av26.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Wed, 21 Aug 2019 10:48:12 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, david@redhat.com, thuth@redhat.com
Subject: [kvm-unit-tests PATCH v2 1/4] s390x: Support PSW restart boot
Date: Wed, 21 Aug 2019 12:47:33 +0200
X-Mailer: git-send-email 2.17.0
In-Reply-To: <20190821104736.1470-1-frankja@linux.ibm.com>
References: <20190821104736.1470-1-frankja@linux.ibm.com>
X-TM-AS-GCONF: 00
x-cbid: 19082110-4275-0000-0000-0000035B7609
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19082110-4276-0000-0000-0000386D98C9
Message-Id: <20190821104736.1470-2-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-08-21_04:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=999 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1906280000 definitions=main-1908210116
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add a boot PSW to PSW restart new, so we can also boot via a PSW
restart.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
---
 s390x/flat.lds | 14 +++++++++-----
 1 file changed, 9 insertions(+), 5 deletions(-)

```
#### [PATCH v6 QEMU 1/3] virtio-ballon: Implement support for page poison tracking feature
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Duyck <alexander.duyck@gmail.com>
X-Patchwork-Id: 11107253
Return-Path: <SRS0=nXzg=WR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DC7F413A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 21 Aug 2019 15:00:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B00F922CE3
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 21 Aug 2019 15:00:37 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="KGKJ9Fg/"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728642AbfHUPAd (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 21 Aug 2019 11:00:33 -0400
Received: from mail-pg1-f196.google.com ([209.85.215.196]:40305 "EHLO
        mail-pg1-f196.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727725AbfHUPAd (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 21 Aug 2019 11:00:33 -0400
Received: by mail-pg1-f196.google.com with SMTP id w10so1461899pgj.7;
        Wed, 21 Aug 2019 08:00:32 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=subject:from:to:cc:date:message-id:in-reply-to:references
         :user-agent:mime-version:content-transfer-encoding;
        bh=a/jqoVnZMS4gCQHlsNMs0Wm0i9/bhDBfzuCMndLKGiI=;
        b=KGKJ9Fg/Tjl9RCPStqmfC8QMnNGz4KlH0MwV2qwztLBaDu4nFZvHUBPYKrnPyejHgD
         ffYxgNs5g51syS55ejem0oZY7ve37imwAMXfd6dwyyHKpghg7q+PO3Uknov6aWBb43WM
         b7LsLdg++VqSRc9YHQFICeWZZvwA0NF8Suj/H423jy333XvYvBK6Er6XwErxQ9aqfRiQ
         pTUYTQYbTTr/IuvYlxA/Wg16do6GJTw1Jwp/Voi7LZheh+KR53FTGJsok059kLVVOOh3
         llCTKDZVWYLLmzs6cSZPe/c1w4xsYjskruzbYaRQLs4GTeiTu7jQMD3y2fU4RVmS6rqq
         ljlg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:subject:from:to:cc:date:message-id:in-reply-to
         :references:user-agent:mime-version:content-transfer-encoding;
        bh=a/jqoVnZMS4gCQHlsNMs0Wm0i9/bhDBfzuCMndLKGiI=;
        b=qqjFYt/Nmm6yov0MKrmvJSMb112BMHCKPLLF0vfnyh5QRW1EA5GL+K1eT1+goKao7/
         Ht6+dFXfRyFo3Gk3p93xyJIe73U+FP4rY8QLl1DJN9IOuv7zbC032RkA/t958oU2DSL3
         FZiNKHEiT4b1GWVlbjBBExPR3wHosUT65nfwrqBRLxnBvFbpaegJxT87cL58HhgUsg9h
         7MANXjrjosJymbNQXg2SwJ2IA3vbarsKXyFH086evflU9XZUuAhzEQiZBUT/7qIKlAKJ
         DaIQEcDGz2zACSlILFGodHbKkH2+6uy8NsjPnTfBQb11mmoaBKls7+QOn+F6OuArN/08
         B10w==
X-Gm-Message-State: APjAAAX+8DUAZbKqAm4JuUKO7RRVBIHsIvMclNweeP9naUo7YznBvN+G
        tpBy/p0EJD5/37ywX1W90i8=
X-Google-Smtp-Source: 
 APXvYqwMk27APT6WG6ZRnG6RyPnBsymvYah2tOLN8zJk1JMxpbtXEpg4GLebgz5M+Kef6+R8Tlaksg==
X-Received: by 2002:a62:86cf:: with SMTP id
 x198mr27374776pfd.195.1566399632349;
        Wed, 21 Aug 2019 08:00:32 -0700 (PDT)
Received: from localhost.localdomain ([2001:470:b:9c3:9e5c:8eff:fe4f:f2d0])
        by smtp.gmail.com with ESMTPSA id
 x17sm23350311pff.62.2019.08.21.08.00.31
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Wed, 21 Aug 2019 08:00:31 -0700 (PDT)
Subject: [PATCH v6 QEMU 1/3] virtio-ballon: Implement support for page
 poison tracking feature
From: Alexander Duyck <alexander.duyck@gmail.com>
To: nitesh@redhat.com, kvm@vger.kernel.org, mst@redhat.com,
        david@redhat.com, dave.hansen@intel.com,
        linux-kernel@vger.kernel.org, linux-mm@kvack.org,
        akpm@linux-foundation.org, virtio-dev@lists.oasis-open.org
Cc: yang.zhang.wz@gmail.com, pagupta@redhat.com, riel@surriel.com,
        konrad.wilk@oracle.com, willy@infradead.org,
        lcapitulino@redhat.com, wei.w.wang@intel.com, aarcange@redhat.com,
        pbonzini@redhat.com, dan.j.williams@intel.com, mhocko@kernel.org,
        alexander.h.duyck@linux.intel.com, osalvador@suse.de
Date: Wed, 21 Aug 2019 08:00:31 -0700
Message-ID: <20190821150031.21485.7505.stgit@localhost.localdomain>
In-Reply-To: <20190821145806.20926.22448.stgit@localhost.localdomain>
References: <20190821145806.20926.22448.stgit@localhost.localdomain>
User-Agent: StGit/0.17.1-dirty
MIME-Version: 1.0
Content-Type: text/plain; charset="utf-8"
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Alexander Duyck <alexander.h.duyck@linux.intel.com>

We need to make certain to advertise support for page poison tracking if
we want to actually get data on if the guest will be poisoning pages. So
if free page hinting is active we should add page poisoning support and
let the guest disable it if it isn't using it.

Page poisoning will result in a page being dirtied on free. As such we
cannot really avoid having to copy the page at least one more time since
we will need to write the poison value to the destination. As such we can
just ignore free page hinting if page poisoning is enabled as it will
actually reduce the work we have to do.

Signed-off-by: Alexander Duyck <alexander.h.duyck@linux.intel.com>
---
 hw/virtio/virtio-balloon.c         |   25 +++++++++++++++++++++----
 include/hw/virtio/virtio-balloon.h |    1 +
 2 files changed, 22 insertions(+), 4 deletions(-)

```
#### [PATCH 04/19] virtio: Implement get_shm_region for PCI transport
##### From: Vivek Goyal <vgoyal@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vivek Goyal <vgoyal@redhat.com>
X-Patchwork-Id: 11107723
Return-Path: <SRS0=nXzg=WR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6FDAC1399
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 21 Aug 2019 17:57:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4F948233A0
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 21 Aug 2019 17:57:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730376AbfHUR5t (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 21 Aug 2019 13:57:49 -0400
Received: from mx1.redhat.com ([209.132.183.28]:34270 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1730356AbfHUR5r (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 21 Aug 2019 13:57:47 -0400
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id F156918C426E;
        Wed, 21 Aug 2019 17:57:46 +0000 (UTC)
Received: from horse.redhat.com (unknown [10.18.25.158])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 00FC860E1C;
        Wed, 21 Aug 2019 17:57:33 +0000 (UTC)
Received: by horse.redhat.com (Postfix, from userid 10451)
        id 8CD1A223D00; Wed, 21 Aug 2019 13:57:32 -0400 (EDT)
From: Vivek Goyal <vgoyal@redhat.com>
To: linux-fsdevel@vger.kernel.org, linux-kernel@vger.kernel.org,
        linux-nvdimm@lists.01.org
Cc: virtio-fs@redhat.com, vgoyal@redhat.com, miklos@szeredi.hu,
        stefanha@redhat.com, dgilbert@redhat.com,
        Sebastien Boeuf <sebastien.boeuf@intel.com>,
        kvm@vger.kernel.org, kbuild test robot <lkp@intel.com>
Subject: [PATCH 04/19] virtio: Implement get_shm_region for PCI transport
Date: Wed, 21 Aug 2019 13:57:05 -0400
Message-Id: <20190821175720.25901-5-vgoyal@redhat.com>
In-Reply-To: <20190821175720.25901-1-vgoyal@redhat.com>
References: <20190821175720.25901-1-vgoyal@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.6.2 (mx1.redhat.com [10.5.110.62]);
 Wed, 21 Aug 2019 17:57:47 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Sebastien Boeuf <sebastien.boeuf@intel.com>

On PCI the shm regions are found using capability entries;
find a region by searching for the capability.

Cc: kvm@vger.kernel.org
Signed-off-by: Sebastien Boeuf <sebastien.boeuf@intel.com>
Signed-off-by: Dr. David Alan Gilbert <dgilbert@redhat.com>
Signed-off-by: kbuild test robot <lkp@intel.com>
---
 drivers/virtio/virtio_pci_modern.c | 108 +++++++++++++++++++++++++++++
 include/uapi/linux/virtio_pci.h    |  11 ++-
 2 files changed, 118 insertions(+), 1 deletion(-)

```
