#### [PATCH] Documentation: kvm: Fix mention to number of ioctls classes
##### From: Wainer dos Santos Moschetta <wainersm@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wainer dos Santos Moschetta <wainersm@redhat.com>
X-Patchwork-Id: 11267487
Return-Path: <SRS0=D48H=ZV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6A707921
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 Nov 2019 18:17:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 438EE2176D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 Nov 2019 18:17:44 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="C7aewtxB"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727188AbfK2SRl (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 29 Nov 2019 13:17:41 -0500
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:47078 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1727118AbfK2SRl (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 29 Nov 2019 13:17:41 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1575051459;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=0JsvcP5JjavRLN7Eg1l3dqgu/7OBAuKTZlpK2fEtMVA=;
        b=C7aewtxB3YYzazt04QJyJZwuDmDjTa5UXQZ4R83Mu9IwbFwZE/BLZtKg3ovwDfaCF7gF32
        z2ubrO2A+hQqpDvVvZg1vGIox6Dpzh/9lcN7GxvMWtFtwGtPF8izYMTVLBc8OwVSclg9qP
        1DDZdaKj0OY13qakclOMnEPZ5mC8DTw=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-206-Vn0Ttw11NB63YmMzg0Xfcw-1; Fri, 29 Nov 2019 13:17:36 -0500
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id B413118AAFA3;
        Fri, 29 Nov 2019 18:17:35 +0000 (UTC)
Received: from virtlab501.virt.lab.eng.bos.redhat.com
 (virtlab501.virt.lab.eng.bos.redhat.com [10.19.152.162])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 4B3D15C1BB;
        Fri, 29 Nov 2019 18:17:31 +0000 (UTC)
From: Wainer dos Santos Moschetta <wainersm@redhat.com>
To: pbonzini@redhat.com, rkrcmar@redhat.com
Cc: linux-doc@vger.kernel.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org
Subject: [PATCH] Documentation: kvm: Fix mention to number of ioctls classes
Date: Fri, 29 Nov 2019 13:17:30 -0500
Message-Id: <20191129181730.15037-1-wainersm@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
X-MC-Unique: Vn0Ttw11NB63YmMzg0Xfcw-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In api.txt it is said that KVM ioctls belong to three classes
but in reality it is four. Fixed this, but do not count categories
anymore to avoid such as outdated information in the future.

Signed-off-by: Wainer dos Santos Moschetta <wainersm@redhat.com>
---
 Documentation/virt/kvm/api.txt | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v8 01/10] Documentation: Introduce EPT based Subpage Protection and related APIs
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Weijiang <weijiang.yang@intel.com>
X-Patchwork-Id: 11267431
Return-Path: <SRS0=D48H=ZV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B730E112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 Nov 2019 17:26:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 8758021736
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 Nov 2019 17:26:46 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727126AbfK2RZc (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 29 Nov 2019 12:25:32 -0500
Received: from mga14.intel.com ([192.55.52.115]:64167 "EHLO mga14.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726909AbfK2RZa (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 29 Nov 2019 12:25:30 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga002.fm.intel.com ([10.253.24.26])
  by fmsmga103.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 29 Nov 2019 09:25:29 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.69,257,1571727600";
   d="scan'208";a="241108957"
Received: from unknown (HELO local-michael-cet-test.sh.intel.com)
 ([10.239.159.128])
  by fmsmga002.fm.intel.com with ESMTP; 29 Nov 2019 09:25:28 -0800
From: Yang Weijiang <weijiang.yang@intel.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        pbonzini@redhat.com, jmattson@google.com,
        sean.j.christopherson@intel.com
Cc: yu.c.zhang@linux.intel.com, alazar@bitdefender.com,
        edwin.zhai@intel.com, Yang Weijiang <weijiang.yang@intel.com>
Subject: [PATCH v8 01/10] Documentation: Introduce EPT based Subpage
 Protection and related APIs
Date: Sat, 30 Nov 2019 01:27:00 +0800
Message-Id: <20191129172709.11347-2-weijiang.yang@intel.com>
X-Mailer: git-send-email 2.17.2
In-Reply-To: <20191129172709.11347-1-weijiang.yang@intel.com>
References: <20191129172709.11347-1-weijiang.yang@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Co-developed-by: yi.z.zhang@linux.intel.com
Signed-off-by: yi.z.zhang@linux.intel.com
Signed-off-by: Yang Weijiang <weijiang.yang@intel.com>
---
 Documentation/virt/kvm/api.txt        |  38 ++++++
 Documentation/virtual/kvm/spp_kvm.txt | 180 ++++++++++++++++++++++++++
 2 files changed, 218 insertions(+)
 create mode 100644 Documentation/virtual/kvm/spp_kvm.txt

```
#### [PATCH] KVM: arm/arm64: Fix some obsolete comments
##### From: linmiaohe <linmiaohe@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: linmiaohe <linmiaohe@huawei.com>
X-Patchwork-Id: 11266673
Return-Path: <SRS0=D48H=ZV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EF19313A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 Nov 2019 03:20:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D5F0A2158A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 Nov 2019 03:20:37 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726859AbfK2DT5 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 28 Nov 2019 22:19:57 -0500
Received: from szxga05-in.huawei.com ([45.249.212.191]:6729 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726764AbfK2DT5 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 28 Nov 2019 22:19:57 -0500
Received: from DGGEMS414-HUB.china.huawei.com (unknown [172.30.72.60])
        by Forcepoint Email with ESMTP id 09800991634F43F95A93;
        Fri, 29 Nov 2019 11:19:54 +0800 (CST)
Received: from huawei.com (10.175.105.18) by DGGEMS414-HUB.china.huawei.com
 (10.3.19.214) with Microsoft SMTP Server id 14.3.439.0; Fri, 29 Nov 2019
 11:19:45 +0800
From: linmiaohe <linmiaohe@huawei.com>
To: <maz@kernel.org>, <pbonzini@redhat.com>, <rkrcmar@redhat.com>,
        <james.morse@arm.com>, <julien.thierry.kdev@gmail.com>,
        <suzuki.poulose@arm.com>, <christoffer.dall@arm.com>,
        <catalin.marinas@arm.com>, <eric.auger@redhat.com>,
        <gregkh@linuxfoundation.org>, <will@kernel.org>,
        <andre.przywara@arm.com>, <tglx@linutronix.de>
CC: <linmiaohe@huawei.com>, <linux-arm-kernel@lists.infradead.org>,
        <kvmarm@lists.cs.columbia.edu>, <linux-kernel@vger.kernel.org>,
        <kvm@vger.kernel.org>
Subject: [PATCH] KVM: arm/arm64: Fix some obsolete comments
Date: Fri, 29 Nov 2019 11:19:47 +0800
Message-ID: <1574997587-20842-1-git-send-email-linmiaohe@huawei.com>
X-Mailer: git-send-email 1.8.3.1
MIME-Version: 1.0
X-Originating-IP: [10.175.105.18]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Miaohe Lin <linmiaohe@huawei.com>

Fix various comments, including comment typo, and obsolete comments
no longer make sense.
Signed-off-by: Miaohe Lin <linmiaohe@huawei.com>
---
 virt/kvm/arm/arch_timer.c    | 5 ++---
 virt/kvm/arm/arm.c           | 1 -
 virt/kvm/arm/vgic/vgic-its.c | 2 +-
 3 files changed, 3 insertions(+), 5 deletions(-)

```
#### [PATCH RFC 01/15] KVM: Move running VCPU from ARM to common code
##### From: Peter Xu <peterx@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11267623
Return-Path: <SRS0=D48H=ZV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C9F5C17E0
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 Nov 2019 21:33:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 9C8D0206B5
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 Nov 2019 21:33:05 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="DBEgO8i4"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727193AbfK2Vcv (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 29 Nov 2019 16:32:51 -0500
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:37715 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1727073AbfK2Vcu (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 29 Nov 2019 16:32:50 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1575063169;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=eAG5Jn3OuAFdTylu6pJu+NV01EXcH/0EJLHVxQXwkPc=;
        b=DBEgO8i4uIiCm3RHtwcSWln4BC4z0BOHxbnOgOXYgI5DBnNvYKtsNGGta9qCqlxxG86yGb
        CwHVZi1bwDJAsO0wf8oQ+K3ah6XwWO9a7ARupgleNXg5nTNIAHFR/5QnoelAToNgSax+EU
        K3xdYLsaIPJG369drsIRaM1QP1Uh2iU=
Received: from mail-qt1-f200.google.com (mail-qt1-f200.google.com
 [209.85.160.200]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-405-0bE9PwbOMTuMIRgGO8ztsQ-1; Fri, 29 Nov 2019 16:32:46 -0500
Received: by mail-qt1-f200.google.com with SMTP id h15so19649089qtn.6
        for <kvm@vger.kernel.org>; Fri, 29 Nov 2019 13:32:46 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=1QV5ryCIGq2QV/eZOsMqVJWdaldoWJG8mcfxAcgQq7Q=;
        b=f0uIxiRNStWCxhME0WsiGFpBn8/AQAAR6DxbN5f+/9oJcDzo25pV8Um/MLy4896a2M
         Ij3oEWAMgqB0x9tmiJhVKXZrRcWeTzZhZ1G2159Hn5Ncqetb0l0Fa+ysEriKMx4zZnzb
         GLPZjUfHAPENhXVkgXKhxz11HvkeJtkJlK0zNupeFxy32WvajEv3gXtEUTjczCU7I7PY
         qCNgwDwQ2/H9V+t7Lg2RxXtyy+6Mr19caToehFnJI5AWI6t1BpoDmwmey3dg8DlZnxt/
         bI+2hj0ZPXyGbKQWWAK2txVNOOO6iIad2hBw+1j/+TDmfpyUZ/9MPUlMTMetK7Jks+RK
         AUDQ==
X-Gm-Message-State: APjAAAVkOQFXg4LeEVFlPORAifNpf09f1iQMcgtY4YM6Mg3eYmNZhL8H
        wl6W6MGsPtQ26j/LD/y/5XpcRRkKOL+fAkjqPz+JFBvzUfD5u/5z5vSls/2lh3I8QtpwcwBzWLI
        WhT8ODdi9Y7VM
X-Received: by 2002:ac8:163c:: with SMTP id
 p57mr34693384qtj.106.1575063165960;
        Fri, 29 Nov 2019 13:32:45 -0800 (PST)
X-Google-Smtp-Source: 
 APXvYqw+c4hSEAWhEg5Qw6P8scV1dsSyfnHKBqTlu0/32I1c4Invo+lKJ5rpxZioPxQcpCt/V/UY5Q==
X-Received: by 2002:ac8:163c:: with SMTP id
 p57mr34693345qtj.106.1575063165630;
        Fri, 29 Nov 2019 13:32:45 -0800 (PST)
Received: from xz-x1.yyz.redhat.com ([104.156.64.74])
        by smtp.gmail.com with ESMTPSA id
 n5sm10634817qkf.48.2019.11.29.13.32.44
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 29 Nov 2019 13:32:45 -0800 (PST)
From: Peter Xu <peterx@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>, Cao Lei <Lei.Cao@stratus.com>,
        peterx@redhat.com, "Dr . David Alan Gilbert" <dgilbert@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>
Subject: [PATCH RFC 01/15] KVM: Move running VCPU from ARM to common code
Date: Fri, 29 Nov 2019 16:32:28 -0500
Message-Id: <20191129213242.17144-2-peterx@redhat.com>
X-Mailer: git-send-email 2.21.0
In-Reply-To: <20191129213242.17144-1-peterx@redhat.com>
References: <20191129213242.17144-1-peterx@redhat.com>
MIME-Version: 1.0
X-MC-Unique: 0bE9PwbOMTuMIRgGO8ztsQ-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Paolo Bonzini <pbonzini@redhat.com>

For ring-based dirty log tracking, it will be more efficient to account
writes during schedule-out or schedule-in to the currently running VCPU.
We would like to do it even if the write doesn't use the current VCPU's
address space, as is the case for cached writes (see commit 4e335d9e7ddb,
"Revert "KVM: Support vCPU-based gfn->hva cache"", 2017-05-02).

Therefore, add a mechanism to track the currently-loaded kvm_vcpu struct.
There is already something similar in KVM/ARM; one important difference
is that kvm_arch_vcpu_{load,put} have two callers in virt/kvm/kvm_main.c:
we have to update both the architecture-independent vcpu_{load,put} and
the preempt notifiers.

Another change made in the process is to allow using kvm_get_running_vcpu()
in preemptible code.  This is allowed because preempt notifiers ensure
that the value does not change even after the VCPU thread is migrated.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Peter Xu <peterx@redhat.com>
---
 arch/arm/include/asm/kvm_host.h   |  2 --
 arch/arm64/include/asm/kvm_host.h |  2 --
 include/linux/kvm_host.h          |  3 +++
 virt/kvm/arm/arm.c                | 29 -----------------------------
 virt/kvm/arm/perf.c               |  6 +++---
 virt/kvm/arm/vgic/vgic-mmio.c     | 15 +++------------
 virt/kvm/kvm_main.c               | 25 ++++++++++++++++++++++++-
 7 files changed, 33 insertions(+), 49 deletions(-)

```
#### [PATCH RFC 01/15] KVM: Move running VCPU from ARM to common code
##### From: Peter Xu <peterx@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11267625
Return-Path: <SRS0=D48H=ZV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 52EC915AB
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 Nov 2019 21:33:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1B3E52424E
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 Nov 2019 21:33:36 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="cZosgmwE"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727310AbfK2Vde (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 29 Nov 2019 16:33:34 -0500
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:42193 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727261AbfK2Vda (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 29 Nov 2019 16:33:30 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1575063207;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=eAG5Jn3OuAFdTylu6pJu+NV01EXcH/0EJLHVxQXwkPc=;
        b=cZosgmwEtE/tz8Hl4AwghmXQxamCTFQu722HoU/qiW1TGR4XMrGLoDLP8DfFzLp4H8qExN
        vYf2j2FvJYGGlc46V5TwEWh6xzxAP6sbiKPG/63tUq3YyGCYmAktXBoHMav6ZnKHFgsK8g
        2OvdIg4ittuSrwOvZvCZwZtkjOPdYTk=
Received: from mail-qt1-f199.google.com (mail-qt1-f199.google.com
 [209.85.160.199]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-5-g9XFFZp2Pg6kCLPfSXAmqA-1; Fri, 29 Nov 2019 16:33:26 -0500
Received: by mail-qt1-f199.google.com with SMTP id t5so19116469qtp.5
        for <kvm@vger.kernel.org>; Fri, 29 Nov 2019 13:33:26 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=1QV5ryCIGq2QV/eZOsMqVJWdaldoWJG8mcfxAcgQq7Q=;
        b=pG+3Ld+O5M0P289sJ+JrjuzxJSCTlgZiYiOYEKaEXPXwWnDb9Ku7Lrbo8+NOrwiFyT
         NUlpP3c4aGji37SNHAbgSC/Ubc4Tl50XdAixXNOzAccTQvo1dW1RJlEKVQZ/8ts7q9VL
         7+wZexkRAHU6rJu0+IDMSB3eyJV+MDYNCfrAQswUTaSEMJJXUFfBg4pZK12Y+qIHgS+o
         tDdnYZag0T+LUHlQ5bGIQH7i/OVYZxDvk/zxt2/oPQ3COAmfbHYyFXKNn6Vt4k/Kzlu7
         c5tehaE4atFuL9tbQJQVVbX35G6WU6RRyX54MVCnwwPsyeJuhiuNof6YngaDxiHKbzZs
         Y7Mw==
X-Gm-Message-State: APjAAAXQMNqwQcN+OiAZ2jNuQ1nDcl+Bsx6I08Zo5gSG4wvE3BM3O6ht
        1e2381iFPG241C3NVV69lJ7pmq9eusDCpBhUvhuw8UorxczseVjWP9r9etSbdHQr/+sRBuBWb6g
        ulakEWip/i738
X-Received: by 2002:aed:22c1:: with SMTP id q1mr54007583qtc.337.1575063205875;
        Fri, 29 Nov 2019 13:33:25 -0800 (PST)
X-Google-Smtp-Source: 
 APXvYqzf3q4xU9le5bfUGj1s9FS5FkC907tlOwcwAdrJCp4RlCZA8IxrTXw/3cNBhJNemlPmJaCCYw==
X-Received: by 2002:aed:22c1:: with SMTP id q1mr54007545qtc.337.1575063205569;
        Fri, 29 Nov 2019 13:33:25 -0800 (PST)
Received: from xz-x1.yyz.redhat.com ([104.156.64.74])
        by smtp.gmail.com with ESMTPSA id
 g11sm10584673qkm.82.2019.11.29.13.33.24
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 29 Nov 2019 13:33:24 -0800 (PST)
From: Peter Xu <peterx@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        "Dr . David Alan Gilbert" <dgilbert@redhat.com>, peterx@redhat.com,
        Vitaly Kuznetsov <vkuznets@redhat.com>
Subject: [PATCH RFC 01/15] KVM: Move running VCPU from ARM to common code
Date: Fri, 29 Nov 2019 16:33:08 -0500
Message-Id: <20191129213322.17386-2-peterx@redhat.com>
X-Mailer: git-send-email 2.21.0
In-Reply-To: <20191129213322.17386-1-peterx@redhat.com>
References: <20191129213322.17386-1-peterx@redhat.com>
MIME-Version: 1.0
X-MC-Unique: g9XFFZp2Pg6kCLPfSXAmqA-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Paolo Bonzini <pbonzini@redhat.com>

For ring-based dirty log tracking, it will be more efficient to account
writes during schedule-out or schedule-in to the currently running VCPU.
We would like to do it even if the write doesn't use the current VCPU's
address space, as is the case for cached writes (see commit 4e335d9e7ddb,
"Revert "KVM: Support vCPU-based gfn->hva cache"", 2017-05-02).

Therefore, add a mechanism to track the currently-loaded kvm_vcpu struct.
There is already something similar in KVM/ARM; one important difference
is that kvm_arch_vcpu_{load,put} have two callers in virt/kvm/kvm_main.c:
we have to update both the architecture-independent vcpu_{load,put} and
the preempt notifiers.

Another change made in the process is to allow using kvm_get_running_vcpu()
in preemptible code.  This is allowed because preempt notifiers ensure
that the value does not change even after the VCPU thread is migrated.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Peter Xu <peterx@redhat.com>
---
 arch/arm/include/asm/kvm_host.h   |  2 --
 arch/arm64/include/asm/kvm_host.h |  2 --
 include/linux/kvm_host.h          |  3 +++
 virt/kvm/arm/arm.c                | 29 -----------------------------
 virt/kvm/arm/perf.c               |  6 +++---
 virt/kvm/arm/vgic/vgic-mmio.c     | 15 +++------------
 virt/kvm/kvm_main.c               | 25 ++++++++++++++++++++++++-
 7 files changed, 33 insertions(+), 49 deletions(-)

```
#### [PATCH RFC 01/15] KVM: Move running VCPU from ARM to common code
##### From: Peter Xu <peterx@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11267659
Return-Path: <SRS0=D48H=ZV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4E2D215AB
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 Nov 2019 21:36:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 17655206B5
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 Nov 2019 21:36:34 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="KV10N1S1"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727313AbfK2VfM (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 29 Nov 2019 16:35:12 -0500
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:25851 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1727177AbfK2VfM (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 29 Nov 2019 16:35:12 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1575063311;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=eAG5Jn3OuAFdTylu6pJu+NV01EXcH/0EJLHVxQXwkPc=;
        b=KV10N1S1cAf5OMEOtSQ/72E+Kub1jxAI227j9BKu/6l0APCBjPflHpxAfivlPzrIFv9e39
        9d6weWYrj5LH58T21PqtrLaseZHhdhbM+xwcNprl0Dib02C8Z4CbqmiX+l36rski1jrULy
        LmcXBtOEWdFLt9dRvytoSj9wyZ0+hRY=
Received: from mail-qv1-f71.google.com (mail-qv1-f71.google.com
 [209.85.219.71]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-87-_7ZoNR8aNu2IfZ6JIT30HQ-1; Fri, 29 Nov 2019 16:35:09 -0500
Received: by mail-qv1-f71.google.com with SMTP id m12so19639426qvv.8
        for <kvm@vger.kernel.org>; Fri, 29 Nov 2019 13:35:09 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=1QV5ryCIGq2QV/eZOsMqVJWdaldoWJG8mcfxAcgQq7Q=;
        b=HdzjPit+l4yOanA9Dy3RFt0wWmNVoZE1TXOrMqDoW1KrZD3SI0EwJ3TetOQjRJkHuK
         TjF6tB9CHrvm/zpecj/mlxJXXnn9HSyeaBfuyH++Hhvsm3FFXNPyzpqL2Rpe6/+EFVE+
         L6fl0NlR4nB2sYNO/gOgwz2uILKFNrZSdMgmvkP8Fmelq2m5zVTHnjFLVSp5OsAPb+c7
         baxI6AdCRUsVEiAj+JCDqZpf0jPwu8ICjbyZMTDw8Dyc91NLQFR3nfGqqNuvab6I+8+V
         sl+64pXmSI08XEzNd/hW38JZB1Tx380MUi51IcODpCeZB0lEDseluFXDOHqNDs7E8TbR
         P6sQ==
X-Gm-Message-State: APjAAAUyU2KRRRzzvsgk6Av1c+4IJYs13glnJxDuv+Znqv2aOTTDmV+H
        pbMS6z166RAnJ0TEf2FUswYrmkIFRDEMsj8Jfft7bG/JeGVsaOwQEIeqbiiUvDi6S4VggqEKXQk
        NngJReGrK6qSK
X-Received: by 2002:a0c:fecc:: with SMTP id
 z12mr19076912qvs.189.1575063309331;
        Fri, 29 Nov 2019 13:35:09 -0800 (PST)
X-Google-Smtp-Source: 
 APXvYqzrJ96EHRAhV7IUSiQFZ2LxjdO0gGveoeMOs0GpiQTvE8VMjMFlsNCKCy1hWILb3LPOZIT7+A==
X-Received: by 2002:a0c:fecc:: with SMTP id
 z12mr19076883qvs.189.1575063308934;
        Fri, 29 Nov 2019 13:35:08 -0800 (PST)
Received: from xz-x1.yyz.redhat.com ([104.156.64.74])
        by smtp.gmail.com with ESMTPSA id
 h186sm10679046qkf.64.2019.11.29.13.35.07
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 29 Nov 2019 13:35:07 -0800 (PST)
From: Peter Xu <peterx@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        "Dr . David Alan Gilbert" <dgilbert@redhat.com>, peterx@redhat.com,
        Vitaly Kuznetsov <vkuznets@redhat.com>
Subject: [PATCH RFC 01/15] KVM: Move running VCPU from ARM to common code
Date: Fri, 29 Nov 2019 16:34:51 -0500
Message-Id: <20191129213505.18472-2-peterx@redhat.com>
X-Mailer: git-send-email 2.21.0
In-Reply-To: <20191129213505.18472-1-peterx@redhat.com>
References: <20191129213505.18472-1-peterx@redhat.com>
MIME-Version: 1.0
X-MC-Unique: _7ZoNR8aNu2IfZ6JIT30HQ-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Paolo Bonzini <pbonzini@redhat.com>

For ring-based dirty log tracking, it will be more efficient to account
writes during schedule-out or schedule-in to the currently running VCPU.
We would like to do it even if the write doesn't use the current VCPU's
address space, as is the case for cached writes (see commit 4e335d9e7ddb,
"Revert "KVM: Support vCPU-based gfn->hva cache"", 2017-05-02).

Therefore, add a mechanism to track the currently-loaded kvm_vcpu struct.
There is already something similar in KVM/ARM; one important difference
is that kvm_arch_vcpu_{load,put} have two callers in virt/kvm/kvm_main.c:
we have to update both the architecture-independent vcpu_{load,put} and
the preempt notifiers.

Another change made in the process is to allow using kvm_get_running_vcpu()
in preemptible code.  This is allowed because preempt notifiers ensure
that the value does not change even after the VCPU thread is migrated.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Peter Xu <peterx@redhat.com>
---
 arch/arm/include/asm/kvm_host.h   |  2 --
 arch/arm64/include/asm/kvm_host.h |  2 --
 include/linux/kvm_host.h          |  3 +++
 virt/kvm/arm/arm.c                | 29 -----------------------------
 virt/kvm/arm/perf.c               |  6 +++---
 virt/kvm/arm/vgic/vgic-mmio.c     | 15 +++------------
 virt/kvm/kvm_main.c               | 25 ++++++++++++++++++++++++-
 7 files changed, 33 insertions(+), 49 deletions(-)

```
#### [PATCH] KVM: s390: Add new reset vcpu API
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11267203
Return-Path: <SRS0=D48H=ZV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E9B3A109A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 Nov 2019 14:21:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D23382176D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 Nov 2019 14:21:47 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727097AbfK2OVq (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 29 Nov 2019 09:21:46 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:13144 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726808AbfK2OVq (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 29 Nov 2019 09:21:46 -0500
Received: from pps.filterd (m0098414.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 xATEI1uX126354
        for <kvm@vger.kernel.org>; Fri, 29 Nov 2019 09:21:45 -0500
Received: from e06smtp01.uk.ibm.com (e06smtp01.uk.ibm.com [195.75.94.97])
        by mx0b-001b2d01.pphosted.com with ESMTP id 2wjxaye06s-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Fri, 29 Nov 2019 09:21:45 -0500
Received: from localhost
        by e06smtp01.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Fri, 29 Nov 2019 14:21:41 -0000
Received: from b06cxnps3075.portsmouth.uk.ibm.com (9.149.109.195)
        by e06smtp01.uk.ibm.com (192.168.101.131) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Fri, 29 Nov 2019 14:21:37 -0000
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id xATELaSP55705770
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 29 Nov 2019 14:21:36 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id EC228A4054;
        Fri, 29 Nov 2019 14:21:35 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 30148A405C;
        Fri, 29 Nov 2019 14:21:34 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.145.188.128])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Fri, 29 Nov 2019 14:21:33 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: thuth@redhat.com, david@redhat.com, borntraeger@de.ibm.com,
        mihajlov@linux.ibm.com, cohuck@redhat.com,
        linux-s390@vger.kernel.org
Subject: [PATCH] KVM: s390: Add new reset vcpu API
Date: Fri, 29 Nov 2019 09:21:22 -0500
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 19112914-4275-0000-0000-000003880E51
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19112914-4276-0000-0000-0000389BA3B9
Message-Id: <20191129142122.21528-1-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.95,18.0.572
 definitions=2019-11-29_04:2019-11-29,2019-11-29 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxscore=0 bulkscore=0
 phishscore=0 adultscore=0 malwarescore=0 spamscore=0 lowpriorityscore=0
 suspectscore=1 impostorscore=0 priorityscore=1501 mlxlogscore=999
 clxscore=1015 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-1910280000 definitions=main-1911290124
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The architecture states that we need to reset local IRQs for all CPU
resets. Because the old reset interface did not support the normal CPU
reset we never did that.

Now that we have a new interface, let's properly clear out local IRQs
and let this commit be a reminder.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
---
 arch/s390/kvm/kvm-s390.c | 25 ++++++++++++++++++++++++-
 include/uapi/linux/kvm.h |  7 +++++++
 2 files changed, 31 insertions(+), 1 deletion(-)

```
#### [PATCH v2 1/3] KVM: X86: Some cleanups in ioapic.h/lapic.h
##### From: Peter Xu <peterx@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11267341
Return-Path: <SRS0=D48H=ZV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7E12D14B7
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 Nov 2019 16:32:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5D6712176D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 Nov 2019 16:32:48 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="aiFTFfB9"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727110AbfK2Qcn (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 29 Nov 2019 11:32:43 -0500
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:55236 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1727076AbfK2Qcn (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 29 Nov 2019 11:32:43 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1575045162;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=C/xSejyaXzbtUL047a9u4nhEXzM8MndtKpPyPJyLXyY=;
        b=aiFTFfB93IDnCDUkPEswixX10FEAVKLviZKhBLPfg5MP0XOAQEPeTYJOSgNVe1mOnXraaX
        F+YWXahMyo0X6DfGgcEO3CeNH5A+RXYHFRtR3nvI4VuX1IDFo0owBJLoEwOzdJ1kEctJFl
        ngnOD42wrhoQZtB3eXSTSy2oeqIkclQ=
Received: from mail-qt1-f199.google.com (mail-qt1-f199.google.com
 [209.85.160.199]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-28-IecRPUdPMdW86Qnmx3jKLg-1; Fri, 29 Nov 2019 11:32:38 -0500
Received: by mail-qt1-f199.google.com with SMTP id j18so19222853qtp.15
        for <kvm@vger.kernel.org>; Fri, 29 Nov 2019 08:32:38 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=JfYuhM68fjTSb2nWUh/a1XhHzPawVsK+0KYnkYwzzyg=;
        b=oum5uABSqb+gkdxI9KvLDm9x+0QBCnPscQ+zhc78v5QnLL1NgsCAN8nxPf5bRZLylT
         GPGXmvEZGBWCoJ8/ao6TyvTXblB1UzeMgPWo9YG6iVCejmTNR54tWFtiBw4cAxQiFVyx
         t3KOA/OGQHdvAZzqFEaCdgSevxTe9odlreyKv9tjhsGrAn/48jOxd58IVdzDue6usEmU
         QXB92sH/ZaQQATAiSrDKmETMbnTra99OcGYvV2NqoFhnDheS1mQU6Jc4WeWW+qr7Xv3U
         TKJ+Nb2YDu8E8kczfl1qSHsXaXrpd5FsHROdDqhcSZT5s8OetBzUXH5Ols+npPnkc/4y
         k7Lw==
X-Gm-Message-State: APjAAAUKbTU9fz8t/1YWHlcFGsNpl7BVw0BYXr6vefrtxZiSLko+pOp3
        VmaeBhoiNaB2ZcxPYba7aZet2MAdGVL1pUXJka+n5hj1XosJPKrMigqlW6JdXqQJ39IwipX1mlH
        nBKBtDHMcZwFL
X-Received: by 2002:a0c:ee91:: with SMTP id
 u17mr16535786qvr.245.1575045158014;
        Fri, 29 Nov 2019 08:32:38 -0800 (PST)
X-Google-Smtp-Source: 
 APXvYqzmI9LDbhfjPk/kPBygYFre0p1EfkrO+8gFy85TuTM9UlPya9CAD4HYy130ni/hYFTuHHtkNw==
X-Received: by 2002:a0c:ee91:: with SMTP id
 u17mr16535759qvr.245.1575045157801;
        Fri, 29 Nov 2019 08:32:37 -0800 (PST)
Received: from xz-x1.yyz.redhat.com ([104.156.64.74])
        by smtp.gmail.com with ESMTPSA id
 d9sm4568329qtj.52.2019.11.29.08.32.36
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 29 Nov 2019 08:32:36 -0800 (PST)
From: Peter Xu <peterx@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Nitesh Narayan Lal <nitesh@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        peterx@redhat.com, Vitaly Kuznetsov <vkuznets@redhat.com>
Subject: [PATCH v2 1/3] KVM: X86: Some cleanups in ioapic.h/lapic.h
Date: Fri, 29 Nov 2019 11:32:32 -0500
Message-Id: <20191129163234.18902-2-peterx@redhat.com>
X-Mailer: git-send-email 2.21.0
In-Reply-To: <20191129163234.18902-1-peterx@redhat.com>
References: <20191129163234.18902-1-peterx@redhat.com>
MIME-Version: 1.0
X-MC-Unique: IecRPUdPMdW86Qnmx3jKLg-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Both kvm_apic_match_dest() and kvm_irq_delivery_to_apic() should
probably suite more to lapic.h comparing to ioapic.h, moving.

kvm_apic_match_dest() is defined twice, once in each of the header.
Removing the one defined in ioapic.h.

Signed-off-by: Peter Xu <peterx@redhat.com>
---
 arch/x86/kvm/ioapic.h | 6 ------
 arch/x86/kvm/lapic.h  | 5 ++++-
 2 files changed, 4 insertions(+), 7 deletions(-)

```
#### [PATCH v2 13/14] samples: vfio-mdev: constify fb ops
##### From: Jani Nikula <jani.nikula@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jani Nikula <jani.nikula@intel.com>
X-Patchwork-Id: 11266987
Return-Path: <SRS0=D48H=ZV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 41AD0175D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 Nov 2019 10:31:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 29ED5217BC
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 Nov 2019 10:31:27 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726871AbfK2KbX (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 29 Nov 2019 05:31:23 -0500
Received: from mga06.intel.com ([134.134.136.31]:59421 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726824AbfK2KbX (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 29 Nov 2019 05:31:23 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga003.fm.intel.com ([10.253.24.29])
  by orsmga104.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 29 Nov 2019 02:31:22 -0800
X-IronPort-AV: E=Sophos;i="5.69,257,1571727600";
   d="scan'208";a="261499727"
Received: from jnikula-mobl3.fi.intel.com (HELO localhost) ([10.237.66.161])
  by fmsmga003-auth.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 29 Nov 2019 02:31:19 -0800
From: Jani Nikula <jani.nikula@intel.com>
To: dri-devel@lists.freedesktop.org, linux-fbdev@vger.kernel.org
Cc: intel-gfx@lists.freedesktop.org, jani.nikula@intel.com,
        ville.syrjala@linux.intel.com,
        Kirti Wankhede <kwankhede@nvidia.com>, kvm@vger.kernel.org,
        Daniel Vetter <daniel.vetter@ffwll.ch>
Subject: [PATCH v2 13/14] samples: vfio-mdev: constify fb ops
Date: Fri, 29 Nov 2019 12:29:43 +0200
Message-Id: 
 <f8a3078ea4279a45f35ed35c9e59e45059d14b07.1575022735.git.jani.nikula@intel.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <cover.1575022735.git.jani.nikula@intel.com>
References: <cover.1575022735.git.jani.nikula@intel.com>
MIME-Version: 1.0
Organization: Intel Finland Oy - BIC 0357606-4 - Westendinkatu 7, 02160 Espoo
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Now that the fbops member of struct fb_info is const, we can start
making the ops const as well.

v2: fix	typo (Christophe de Dinechin)

Cc: Kirti Wankhede <kwankhede@nvidia.com>
Cc: kvm@vger.kernel.org
Reviewed-by: Daniel Vetter <daniel.vetter@ffwll.ch>
Signed-off-by: Jani Nikula <jani.nikula@intel.com>
---
 samples/vfio-mdev/mdpy-fb.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
