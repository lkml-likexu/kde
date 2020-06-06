#### [PATCH] KVM: arm64: Remove host_cpu_context member from vcpu structure
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11589969
Return-Path: <SRS0=rHMY=7S=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 62A48618
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  5 Jun 2020 16:19:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3CBB6207D3
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  5 Jun 2020 16:19:00 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1591373940;
	bh=paJXf48AWQH6tw11YLkNIpuHunscwji3xlYKrNSY0oo=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=D29rxFjRu2VnMthbcC20rXaaVQutUKOeXkMGXtg6b80umqW5GW9JlJrud0BGv0yaA
	 EP6XgCW5qZOaYfIjPSn25SGIiyKYdGVp69U/bT+xpbsEUDFxTvf+jD7gJBm3k2kXkm
	 wJfIZFc3rlK5fg5zGoKwB0mY3dYNFrBrqHhrae5w=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726090AbgFEQS7 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 5 Jun 2020 12:18:59 -0400
Received: from mail.kernel.org ([198.145.29.99]:56160 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726024AbgFEQS6 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 5 Jun 2020 12:18:58 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 985CB206DB;
        Fri,  5 Jun 2020 16:18:57 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1591373937;
        bh=paJXf48AWQH6tw11YLkNIpuHunscwji3xlYKrNSY0oo=;
        h=From:To:Cc:Subject:Date:From;
        b=Qw60EwTzazbCTcePt+nm7ifIpHUNoIxiUj2mmFBkwGDmtc3RNXQuLeGnFhtfSD6H/
         KGeyiVDYs0Cmx/cIVyQ8nzbE4iWSn/EkqeGk3ePL3mTYMXlHdOzuFkkHX9+a8I1X7L
         WuIwLjVGJPwOvsP4HtcuxWjk8wBt3x9iZCO3h6ug=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1jhF3Y-000YzD-2R; Fri, 05 Jun 2020 17:18:56 +0100
From: Marc Zyngier <maz@kernel.org>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
        linux-arm-kernel@lists.infradead.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Mark Rutland <mark.rutland@arm.com>, kernel-team@android.com,
        Andrew Scull <ascull@google.com>
Subject: [PATCH] KVM: arm64: Remove host_cpu_context member from vcpu
 structure
Date: Fri,  5 Jun 2020 17:18:47 +0100
Message-Id: <20200605161847.1316354-1-maz@kernel.org>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
 linux-arm-kernel@lists.infradead.org, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com, mark.rutland@arm.com,
 kernel-team@android.com, ascull@google.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

For very long, we have kept this pointer back to the per-cpu
host state, despite having working per-cpu accessors at EL2
for some time now.

Recent investigations have shown that this pointer is easy
to abuse in preemptible context, which is a sure sign that
it would better be gone. Not to mention that a per-cpu
pointer is faster to access at all times.

Reported-by: Andrew Scull <ascull@google.com>
Signed-off-by: Marc Zyngier <maz@kernel.org>
---
This patch goes on top of the PtrAuth rework that I have previously
posted, and make sures it is harder to fall into the same trap.

 arch/arm64/include/asm/kvm_host.h | 3 ---
 arch/arm64/kvm/arm.c              | 3 ---
 arch/arm64/kvm/hyp/debug-sr.c     | 4 ++--
 arch/arm64/kvm/hyp/switch.c       | 6 +++---
 arch/arm64/kvm/hyp/sysreg-sr.c    | 6 ++++--
 arch/arm64/kvm/pmu.c              | 8 ++------
 6 files changed, 11 insertions(+), 19 deletions(-)

```
#### [PATCH 01/21] KVM: x86/mmu: Track the associated kmem_cache in the MMU caches
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11590729
Return-Path: <SRS0=rHMY=7S=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6B455138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  5 Jun 2020 21:44:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5CC35206E6
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  5 Jun 2020 21:44:28 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728314AbgFEVjJ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 5 Jun 2020 17:39:09 -0400
Received: from mga17.intel.com ([192.55.52.151]:49307 "EHLO mga17.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728227AbgFEVjI (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 5 Jun 2020 17:39:08 -0400
IronPort-SDR: 
 QJudosyraLoQ2pgoGD3dtsMijyFPia44foxIrkje7YWrIsaCB1QDfK44F0TVo0lLJCX7xqORB2
 mB4vtKXFJCng==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga002.jf.intel.com ([10.7.209.21])
  by fmsmga107.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 05 Jun 2020 14:39:07 -0700
IronPort-SDR: 
 kUB4EaD9pBY+TwwSYxybFG3rI29fqgwbISoJ3DAUxWFW4zz+0j67lNNk6bsc8yImoZHZt5pcsT
 yNUu2OllTXSw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,477,1583222400";
   d="scan'208";a="287860868"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.152])
  by orsmga002.jf.intel.com with ESMTP; 05 Jun 2020 14:39:07 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Marc Zyngier <maz@kernel.org>, Paul Mackerras <paulus@ozlabs.org>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Janosch Frank <frankja@linux.ibm.com>,
        Paolo Bonzini <pbonzini@redhat.com>
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Claudio Imbrenda <imbrenda@linux.ibm.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        linux-mips@vger.kernel.org, kvm@vger.kernel.org,
        kvm-ppc@vger.kernel.org, linux-kernel@vger.kernel.org,
        Peter Feiner <pfeiner@google.com>,
        Peter Shier <pshier@google.com>,
        Junaid Shahid <junaids@google.com>,
        Ben Gardon <bgardon@google.com>,
        Christoffer Dall <christoffer.dall@arm.com>
Subject: [PATCH 01/21] KVM: x86/mmu: Track the associated kmem_cache in the
 MMU caches
Date: Fri,  5 Jun 2020 14:38:33 -0700
Message-Id: <20200605213853.14959-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
In-Reply-To: <20200605213853.14959-1-sean.j.christopherson@intel.com>
References: <20200605213853.14959-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Track the kmem_cache used for non-page KVM MMU memory caches instead of
passing in the associated kmem_cache when filling the cache.  This will
allow consolidating code and other cleanups.

No functional change intended.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/include/asm/kvm_host.h |  1 +
 arch/x86/kvm/mmu/mmu.c          | 24 +++++++++++-------------
 2 files changed, 12 insertions(+), 13 deletions(-)

```
#### [PATCH] KVM: let kvm_destroy_vm_debugfs clean up vCPU debugfs directories
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11589869
Return-Path: <SRS0=rHMY=7S=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E3B7A618
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  5 Jun 2020 15:15:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C844A206A2
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  5 Jun 2020 15:15:28 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="NCNF/gBa"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728005AbgFEPP1 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 5 Jun 2020 11:15:27 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:37478 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726675AbgFEPP1 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 5 Jun 2020 11:15:27 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1591370125;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=fn51+xgx98oZsB/D59Na1SLBQWdWeTshRNoFGM9XJVg=;
        b=NCNF/gBa0hTVuD4M9eZhbBAnsqZjNTW39qpArPoC25sQPn3H9ly87Y39rT9rqqCWaeSEwH
        5iZ/ZoVfIqtYBeYy/PhNpCyVTDbvg6NCnMqP5O7nY/FsRi4W2wCibggfaFnuvsaUcpzeaL
        fHYyuOCy0e221FT6qGjiaKDP9tPtFXo=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-292-xdjEkaHJNYuWM2jaGqNynA-1; Fri, 05 Jun 2020 11:15:22 -0400
X-MC-Unique: xdjEkaHJNYuWM2jaGqNynA-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 65E658C7C82;
        Fri,  5 Jun 2020 15:15:07 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id CF1DA9CA0;
        Fri,  5 Jun 2020 15:15:06 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: vkuznets@redhat.com,
        syzbot+705f4401d5a93a59b87d@syzkaller.appspotmail.com
Subject: [PATCH] KVM: let kvm_destroy_vm_debugfs clean up vCPU debugfs
 directories
Date: Fri,  5 Jun 2020 11:15:06 -0400
Message-Id: <20200605151506.18064-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

After commit 63d0434 ("KVM: x86: move kvm_create_vcpu_debugfs after
last failure point") we are creating the pre-vCPU debugfs files
after the creation of the vCPU file descriptor.  This makes it
possible for userspace to reach kvm_vcpu_release before
kvm_create_vcpu_debugfs has finished.  The vcpu->debugfs_dentry
then does not have any associated inode anymore, and this causes
a NULL-pointer dereference in debugfs_create_file.

The solution is simply to avoid removing the files; they are
cleaned up when the VM file descriptor is closed (and that must be
after KVM_CREATE_VCPU returns).  We can stop storing the dentry
in struct kvm_vcpu too, because it is not needed anywhere after
kvm_create_vcpu_debugfs returns.

Reported-by: syzbot+705f4401d5a93a59b87d@syzkaller.appspotmail.com
Fixes: 63d04348371b ("KVM: x86: move kvm_create_vcpu_debugfs after last failure point")
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/arm64/kvm/arm.c     |  5 -----
 arch/x86/kvm/debugfs.c   | 10 +++++-----
 include/linux/kvm_host.h |  3 +--
 virt/kvm/kvm_main.c      |  8 ++++----
 4 files changed, 10 insertions(+), 16 deletions(-)

```
#### [PATCH] KVM: let kvm_destroy_vm_debugfs clean up vCPU debugfs directories
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11590129
Return-Path: <SRS0=rHMY=7S=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5DC04739
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  5 Jun 2020 17:06:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3778A207D3
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  5 Jun 2020 17:06:49 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="FhIg8aK5"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726977AbgFERGr (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 5 Jun 2020 13:06:47 -0400
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:30282 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726252AbgFERGp (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 5 Jun 2020 13:06:45 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1591376803;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=fn51+xgx98oZsB/D59Na1SLBQWdWeTshRNoFGM9XJVg=;
        b=FhIg8aK56SkWujMQEK4whbCDaJv8+sxO+NEfmxd731g4gbcn72SBl9D2cpsK/gDnS9fj4E
        2gyDWOaLue9JO31OkapiBcTUV3F9COhHqBP4mi2PuPO1nUtK33c/XbtruZq5ND4jJf6zu1
        pohJdYFF4SHWuJP0fqHYBLtlUCf5S/g=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-331-NfHEDjfTMZS_9-9DlOrH2w-1; Fri, 05 Jun 2020 13:06:42 -0400
X-MC-Unique: NfHEDjfTMZS_9-9DlOrH2w-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 2514E106B208;
        Fri,  5 Jun 2020 17:06:35 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 3EEAE707C7;
        Fri,  5 Jun 2020 17:06:34 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: vkuznets@redhat.com,
        syzbot+705f4401d5a93a59b87d@syzkaller.appspotmail.com
Subject: [PATCH] KVM: let kvm_destroy_vm_debugfs clean up vCPU debugfs
 directories
Date: Fri,  5 Jun 2020 13:06:33 -0400
Message-Id: <20200605170633.16766-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

After commit 63d0434 ("KVM: x86: move kvm_create_vcpu_debugfs after
last failure point") we are creating the pre-vCPU debugfs files
after the creation of the vCPU file descriptor.  This makes it
possible for userspace to reach kvm_vcpu_release before
kvm_create_vcpu_debugfs has finished.  The vcpu->debugfs_dentry
then does not have any associated inode anymore, and this causes
a NULL-pointer dereference in debugfs_create_file.

The solution is simply to avoid removing the files; they are
cleaned up when the VM file descriptor is closed (and that must be
after KVM_CREATE_VCPU returns).  We can stop storing the dentry
in struct kvm_vcpu too, because it is not needed anywhere after
kvm_create_vcpu_debugfs returns.

Reported-by: syzbot+705f4401d5a93a59b87d@syzkaller.appspotmail.com
Fixes: 63d04348371b ("KVM: x86: move kvm_create_vcpu_debugfs after last failure point")
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/arm64/kvm/arm.c     |  5 -----
 arch/x86/kvm/debugfs.c   | 10 +++++-----
 include/linux/kvm_host.h |  3 +--
 virt/kvm/kvm_main.c      |  8 ++++----
 4 files changed, 10 insertions(+), 16 deletions(-)

```
#### [PATCH] KVM: selftests: delete some dead code
##### From: Dan Carpenter <dan.carpenter@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Dan Carpenter <dan.carpenter@oracle.com>
X-Patchwork-Id: 11589461
Return-Path: <SRS0=rHMY=7S=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 944CB912
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  5 Jun 2020 11:01:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7B7F2206E6
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  5 Jun 2020 11:01:05 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="yieOJsHO"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726964AbgFELBF (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 5 Jun 2020 07:01:05 -0400
Received: from userp2120.oracle.com ([156.151.31.85]:54398 "EHLO
        userp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726954AbgFELBE (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 5 Jun 2020 07:01:04 -0400
Received: from pps.filterd (userp2120.oracle.com [127.0.0.1])
        by userp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 055AwGRb161927;
        Fri, 5 Jun 2020 11:00:58 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=date : from : to : cc
 : subject : message-id : mime-version : content-type; s=corp-2020-01-29;
 bh=dmqsTnpEMgvgWaF01TZp1obHH5FHCkwtMSTp+ECkeJw=;
 b=yieOJsHOmtFiDu5GpR2Lc6WmKnrXM/Hn0FVOBlUrZxeYaHy0vWGL4J0wZCgosqE9PfZc
 kiRxN75Lsw/hxUhoFYP7FHJ64RQQwD4a8Is23ZFFrEFDrxUQP17Ir80vdbozi0VYUl1j
 uvJ4JUAab7IGGBWIfRnKSRhBEU7dIDoD7sTDoPjfH3gZ1+E0A631qlh7S2o0c1qvGy3V
 EJWizOidaSMoU7pK4jl+To0yFij8NYVnhEBx8hVWDiKG+h5l3NuEDHzYIsCIJeEyFle+
 xBhOcSsGXxXkhnQsw6iakcRQYZ5eLam+fzolK7+T8Nn5IMQbhhf/iUa6DD0HTGEL7cLu KQ==
Received: from userp3030.oracle.com (userp3030.oracle.com [156.151.31.80])
        by userp2120.oracle.com with ESMTP id 31f92629uv-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=FAIL);
        Fri, 05 Jun 2020 11:00:58 +0000
Received: from pps.filterd (userp3030.oracle.com [127.0.0.1])
        by userp3030.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 055AxRiC016464;
        Fri, 5 Jun 2020 11:00:58 GMT
Received: from userv0122.oracle.com (userv0122.oracle.com [156.151.31.75])
        by userp3030.oracle.com with ESMTP id 31f92skt9v-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 05 Jun 2020 11:00:58 +0000
Received: from abhmp0007.oracle.com (abhmp0007.oracle.com [141.146.116.13])
        by userv0122.oracle.com (8.14.4/8.14.4) with ESMTP id 055B0tAu029723;
        Fri, 5 Jun 2020 11:00:55 GMT
Received: from mwanda (/41.57.98.10)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Fri, 05 Jun 2020 04:00:55 -0700
Date: Fri, 5 Jun 2020 14:00:48 +0300
From: Dan Carpenter <dan.carpenter@oracle.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Ben Gardon <bgardon@google.com>
Cc: Shuah Khan <shuah@kernel.org>, Peter Xu <peterx@redhat.com>,
        kvm@vger.kernel.org, linux-kselftest@vger.kernel.org,
        kernel-janitors@vger.kernel.org
Subject: [PATCH] KVM: selftests: delete some dead code
Message-ID: <20200605110048.GB978434@mwanda>
MIME-Version: 1.0
Content-Disposition: inline
X-Mailer: git-send-email haha only kidding
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9642
 signatures=668680
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 adultscore=0
 bulkscore=0 mlxscore=0
 malwarescore=0 spamscore=0 suspectscore=0 mlxlogscore=999 phishscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2004280000
 definitions=main-2006050084
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9642
 signatures=668680
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 phishscore=0
 adultscore=0
 suspectscore=0 cotscore=-2147483648 bulkscore=0 clxscore=1011
 impostorscore=0 priorityscore=1501 malwarescore=0 mlxlogscore=999
 spamscore=0 lowpriorityscore=0 mlxscore=0 classifier=spam adjust=0
 reason=mlx scancount=1 engine=8.12.0-2004280000
 definitions=main-2006050084
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The "uffd_delay" variable is unsigned so it's always going to be >= 0.

Fixes: 0119cb365c93 ("KVM: selftests: Add configurable demand paging delay")
Signed-off-by: Dan Carpenter <dan.carpenter@oracle.com>
---
 tools/testing/selftests/kvm/demand_paging_test.c | 2 --
 1 file changed, 2 deletions(-)

```
#### [PATCH] KVM: selftests: Fix "make ARCH=x86_64" build with
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11589789
Return-Path: <SRS0=rHMY=7S=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A882E912
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  5 Jun 2020 14:21:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8FDFE2074B
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  5 Jun 2020 14:21:09 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="ZcD+SvbY"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728533AbgFEOVI (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 5 Jun 2020 10:21:08 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:20110 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1728970AbgFEOUk (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 5 Jun 2020 10:20:40 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1591366838;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=tYrH+EqixLCGC0o9Vgv8h3T7kXXMELTRVth7woAonUk=;
        b=ZcD+SvbYI+xwFHK8R/lo6oC7BSQikOCWkpYy/QFUOWXxYHTg8+/nauHUVwaBBNv05/3RTz
        jqN98n6Nfa9shlAVK0l/ICC5otmSqnuceWVUyOaS5df9LG8J0QdnSEMaHoKtAJ12IK2VDz
        sth0q32TpNIE15OAoZxFx4+FCuxrOFM=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-480-Dy9Io7yKN9-dp3U52YM0uA-1; Fri, 05 Jun 2020 10:20:37 -0400
X-MC-Unique: Dy9Io7yKN9-dp3U52YM0uA-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 91AEB1005510;
        Fri,  5 Jun 2020 14:20:35 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.195.93])
        by smtp.corp.redhat.com (Postfix) with ESMTP id E6B2E6292E;
        Fri,  5 Jun 2020 14:20:29 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Marcelo Bandeira Condotta <mcondotta@redhat.com>,
        Shuah Khan <skhan@linuxfoundation.org>,
        linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: selftests: Fix "make ARCH=x86_64" build with
Date: Fri,  5 Jun 2020 16:20:28 +0200
Message-Id: <20200605142028.550068-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Marcelo reports that kvm selftests fail to build with
"make ARCH=x86_64":

gcc -Wall -Wstrict-prototypes -Wuninitialized -O2 -g -std=gnu99
 -fno-stack-protector -fno-PIE -I../../../../tools/include
 -I../../../../tools/arch/x86_64/include  -I../../../../usr/include/
 -Iinclude -Ilib -Iinclude/x86_64 -I.. -c lib/kvm_util.c
 -o /var/tmp/20200604202744-bin/lib/kvm_util.o

In file included from lib/kvm_util.c:11:
include/x86_64/processor.h:14:10: fatal error: asm/msr-index.h: No such
 file or directory

 #include <asm/msr-index.h>
          ^~~~~~~~~~~~~~~~~
compilation terminated.

"make ARCH=x86", however, works. The problem is that arch specific headers
for x86_64 live in 'tools/arch/x86/include', not in
'tools/arch/x86_64/include'.

Fixes: 66d69e081b52 ("selftests: fix kvm relocatable native/cross builds and installs")
Reported-by: Marcelo Bandeira Condotta <mcondotta@redhat.com>
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 tools/testing/selftests/kvm/Makefile | 4 ++++
 1 file changed, 4 insertions(+)

```
#### [PATCH 1/3 v2] kvm-unit-tests: nVMX: Test GUEST_BASE_GDTR and GUEST_BASE_IDTR on vmentry of nested guests
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11590435
Return-Path: <SRS0=rHMY=7S=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2C1AE90
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  5 Jun 2020 19:22:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 065AA207D8
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  5 Jun 2020 19:22:42 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="RplfaFNh"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727877AbgFETWk (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 5 Jun 2020 15:22:40 -0400
Received: from aserp2120.oracle.com ([141.146.126.78]:40752 "EHLO
        aserp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727064AbgFETWk (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 5 Jun 2020 15:22:40 -0400
Received: from pps.filterd (aserp2120.oracle.com [127.0.0.1])
        by aserp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 055JGabZ071725;
        Fri, 5 Jun 2020 19:22:34 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references; s=corp-2020-01-29;
 bh=6lwhDaRXiHcUzHZH2+C9hBV3CaBzPiRBMGi/fm0qcSE=;
 b=RplfaFNhAvHspqK8Z1NZUy8fJRaXZq7qRHPIaCD6jyk3pZcaGSk0rPdmTM75PTwPgJjZ
 yEnDn/DbiCo40h5sGnmsmUe+iRAJ4s1idxh4W5pXqSnkYu5uRAZ+707pZmtd+hT1Ayl/
 zEwRnaFT9vDnCPSz+UBoIiNVWZ6A2HmiwXufHu8O775gsRrXHEb/XKqdWF+zitFrbVoP
 hHVhty807Ai7zgaYRyHLtJ2DFfoSHqLK8vhORylTNs074sFU4pAZ5WhFDtbbvPp2XNyW
 GucBrkBXyHNDt599IyuJde/kJcgu6gmE4kdvkZ1tT+1jj5Gp0Gmm6G9yan9XrEq4JweZ kQ==
Received: from aserp3030.oracle.com (aserp3030.oracle.com [141.146.126.71])
        by aserp2120.oracle.com with ESMTP id 31f91dvdxg-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=FAIL);
        Fri, 05 Jun 2020 19:22:34 +0000
Received: from pps.filterd (aserp3030.oracle.com [127.0.0.1])
        by aserp3030.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 055JHdNh185819;
        Fri, 5 Jun 2020 19:20:34 GMT
Received: from aserv0122.oracle.com (aserv0122.oracle.com [141.146.126.236])
        by aserp3030.oracle.com with ESMTP id 31f925ujnf-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 05 Jun 2020 19:20:34 +0000
Received: from abhmp0009.oracle.com (abhmp0009.oracle.com [141.146.116.15])
        by aserv0122.oracle.com (8.14.4/8.14.4) with ESMTP id 055JKXET017168;
        Fri, 5 Jun 2020 19:20:33 GMT
Received: from sadhukhan-nvmx.osdevelopmeniad.oraclevcn.com (/100.100.231.182)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Fri, 05 Jun 2020 19:20:33 +0000
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com,
        sean.j.christopherson@intel.com
Subject: [PATCH 1/3 v2] kvm-unit-tests: nVMX: Test GUEST_BASE_GDTR and
 GUEST_BASE_IDTR on vmentry of nested guests
Date: Fri,  5 Jun 2020 19:20:20 +0000
Message-Id: <1591384822-71784-2-git-send-email-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1591384822-71784-1-git-send-email-krish.sadhukhan@oracle.com>
References: <1591384822-71784-1-git-send-email-krish.sadhukhan@oracle.com>
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9643
 signatures=668680
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 phishscore=0
 mlxlogscore=999
 malwarescore=0 bulkscore=0 mlxscore=0 spamscore=0 suspectscore=13
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2004280000 definitions=main-2006050141
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9643
 signatures=668680
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 lowpriorityscore=0 bulkscore=0
 clxscore=1015 cotscore=-2147483648 malwarescore=0 adultscore=0
 priorityscore=1501 suspectscore=13 phishscore=0 spamscore=0 mlxscore=0
 impostorscore=0 mlxlogscore=999 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-2004280000 definitions=main-2006050141
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

According to section "Checks on Guest Descriptor-Table Registers" in Intel
SDM vol 3C, the following check is performed on the Guest Descriptor-Table
Registers on vmentry of nested guests:

    - On processors that support Intel 64 architecture, the base-address
      fields must contain canonical addresses.

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 x86/vmx_tests.c | 3 +++
 1 file changed, 3 insertions(+)

```
#### [kvm-unit-tests PATCH] x86: realmode: Relax smsw test
##### From: Roman Bolshakov <r.bolshakov@yadro.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Roman Bolshakov <r.bolshakov@yadro.com>
X-Patchwork-Id: 11590445
Return-Path: <SRS0=rHMY=7S=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5981614E3
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  5 Jun 2020 19:54:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 40B462074B
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  5 Jun 2020 19:54:56 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=yadro.com header.i=@yadro.com
 header.b="R50Bb1VT"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728067AbgFETy4 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 5 Jun 2020 15:54:56 -0400
Received: from mta-02.yadro.com ([89.207.88.252]:46810 "EHLO mta-01.yadro.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1727868AbgFETyz (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 5 Jun 2020 15:54:55 -0400
Received: from localhost (unknown [127.0.0.1])
        by mta-01.yadro.com (Postfix) with ESMTP id 7871D4C850;
        Fri,  5 Jun 2020 19:54:53 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=yadro.com; h=
        content-type:content-type:content-transfer-encoding:mime-version
        :x-mailer:message-id:date:date:subject:subject:from:from
        :received:received:received; s=mta-01; t=1591386892; x=
        1593201293; bh=BT7V5OPoBcBnhfBrfhmq0i+EDq9gDtiAbV9QTbz/h8U=; b=R
        50Bb1VTZzycUjukTARC54JTmCSTL5oH8Q45PWrI2Wb/FSUmt8rEdMfs9D+5NW1b5
        SjiPkzgw7C9qu6XSItai0oxK7dtl1jgNkVwHFHjHybfjIsvDSP4TgPB564Wgg7dA
        qnZLxrXbUtNpIWtZf306zdWSdKOs26vrDTu/2XdKwA=
X-Virus-Scanned: amavisd-new at yadro.com
Received: from mta-01.yadro.com ([127.0.0.1])
        by localhost (mta-01.yadro.com [127.0.0.1]) (amavisd-new, port 10024)
        with ESMTP id xHMBA-P1y4mm; Fri,  5 Jun 2020 22:54:52 +0300 (MSK)
Received: from T-EXCH-02.corp.yadro.com (t-exch-02.corp.yadro.com
 [172.17.10.102])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-SHA384 (256/256 bits))
        (No client certificate requested)
        by mta-01.yadro.com (Postfix) with ESMTPS id 0C0424B169;
        Fri,  5 Jun 2020 22:54:52 +0300 (MSK)
Received: from localhost (172.17.204.212) by T-EXCH-02.corp.yadro.com
 (172.17.10.102) with Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA384_P384) id 15.1.669.32; Fri, 5 Jun
 2020 22:54:51 +0300
From: Roman Bolshakov <r.bolshakov@yadro.com>
To: <kvm@vger.kernel.org>
CC: Roman Bolshakov <r.bolshakov@yadro.com>,
        Nadav Amit <namit@vmware.com>,
        Richard Henderson <rth@twiddle.net>
Subject: [kvm-unit-tests PATCH] x86: realmode: Relax smsw test
Date: Fri, 5 Jun 2020 22:49:18 +0300
Message-ID: <20200605194915.37330-1-r.bolshakov@yadro.com>
X-Mailer: git-send-email 2.26.1
MIME-Version: 1.0
X-Originating-IP: [172.17.204.212]
X-ClientProxiedBy: T-EXCH-01.corp.yadro.com (172.17.10.101) To
 T-EXCH-02.corp.yadro.com (172.17.10.102)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The test currently asserts a kind of undefined behaviour in SMSW per
Intel SDM:

  In non-64-bit modes, when the destination operand is a 32-bit register,
  the low-order 16 bits of register CR0 are copied into the low-order 16
  bits of the register and the high-order 16 bits are undefined.

TCG doesn't write high-order 16 bits and the test fails for it. Instead
of CR0.CD, set CR0.PE and check only if low-order bits match to avoid
ambiguity with the undefined behaviour.

Cc: Nadav Amit <namit@vmware.com>
Cc: Richard Henderson <rth@twiddle.net>
Signed-off-by: Roman Bolshakov <r.bolshakov@yadro.com>
---
 x86/realmode.c | 6 ++++--
 1 file changed, 4 insertions(+), 2 deletions(-)

An alternative would be to change the undefined behaviour of TCG itself:
https://github.com/roolebo/qemu/commit/a5e5ee3a41c52031dfda3b1b903100bcb5639742

```
#### [PATCH v8 01/16] s390/ap: introduce new ap function ap_get_qdev()
##### From: Tony Krowiak <akrowiak@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tony Krowiak <akrowiak@linux.ibm.com>
X-Patchwork-Id: 11590607
Return-Path: <SRS0=rHMY=7S=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D2B0092A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  5 Jun 2020 21:40:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B47452074B
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  5 Jun 2020 21:40:17 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728836AbgFEVkR (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 5 Jun 2020 17:40:17 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:53854 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728278AbgFEVkP (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 5 Jun 2020 17:40:15 -0400
Received: from pps.filterd (m0098410.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 055LWu8Z094844;
        Fri, 5 Jun 2020 17:40:13 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 31fsnk7b3u-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 05 Jun 2020 17:40:12 -0400
Received: from m0098410.ppops.net (m0098410.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 055Le3X6119018;
        Fri, 5 Jun 2020 17:40:12 -0400
Received: from ppma04wdc.us.ibm.com (1a.90.2fa9.ip4.static.sl-reverse.com
 [169.47.144.26])
        by mx0a-001b2d01.pphosted.com with ESMTP id 31fsnk7b3g-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 05 Jun 2020 17:40:12 -0400
Received: from pps.filterd (ppma04wdc.us.ibm.com [127.0.0.1])
        by ppma04wdc.us.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 055La02q012409;
        Fri, 5 Jun 2020 21:40:11 GMT
Received: from b01cxnp22033.gho.pok.ibm.com (b01cxnp22033.gho.pok.ibm.com
 [9.57.198.23])
        by ppma04wdc.us.ibm.com with ESMTP id 31bf49dgb8-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 05 Jun 2020 21:40:11 +0000
Received: from b01ledav006.gho.pok.ibm.com (b01ledav006.gho.pok.ibm.com
 [9.57.199.111])
        by b01cxnp22033.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id 055Le9FL43188512
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 5 Jun 2020 21:40:09 GMT
Received: from b01ledav006.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id CA144AC05B;
        Fri,  5 Jun 2020 21:40:09 +0000 (GMT)
Received: from b01ledav006.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 55FB2AC05E;
        Fri,  5 Jun 2020 21:40:09 +0000 (GMT)
Received: from cpe-172-100-175-116.stny.res.rr.com.com (unknown
 [9.85.146.208])
        by b01ledav006.gho.pok.ibm.com (Postfix) with ESMTP;
        Fri,  5 Jun 2020 21:40:09 +0000 (GMT)
From: Tony Krowiak <akrowiak@linux.ibm.com>
To: linux-s390@vger.kernel.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org
Cc: freude@linux.ibm.com, borntraeger@de.ibm.com, cohuck@redhat.com,
        mjrosato@linux.ibm.com, pasic@linux.ibm.com,
        alex.williamson@redhat.com, kwankhede@nvidia.com,
        fiuczy@linux.ibm.com, Tony Krowiak <akrowiak@linux.ibm.com>
Subject: [PATCH v8 01/16] s390/ap: introduce new ap function ap_get_qdev()
Date: Fri,  5 Jun 2020 17:39:49 -0400
Message-Id: <20200605214004.14270-2-akrowiak@linux.ibm.com>
X-Mailer: git-send-email 2.21.1
In-Reply-To: <20200605214004.14270-1-akrowiak@linux.ibm.com>
References: <20200605214004.14270-1-akrowiak@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.216,18.0.687
 definitions=2020-06-05_07:2020-06-04,2020-06-05 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 spamscore=0
 cotscore=-2147483648 phishscore=0 impostorscore=0 lowpriorityscore=0
 malwarescore=0 priorityscore=1501 bulkscore=0 clxscore=1011 suspectscore=3
 mlxlogscore=999 adultscore=0 mlxscore=0 classifier=spam adjust=0
 reason=mlx scancount=1 engine=8.12.0-2004280000
 definitions=main-2006050159
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Harald Freudenberger <freude@linux.ibm.com>

Provide a new interface function to be used by the ap drivers:
  struct ap_queue *ap_get_qdev(ap_qid_t qid);
Returns ptr to the struct ap_queue device or NULL if there
was no ap_queue device with this qid found. When something is
found, the reference count of the embedded device is increased.
So the caller has to decrease the reference count after use
with a call to put_device(&aq->ap_dev.device).

With this patch also the ap_card_list is removed from the
ap core code and a new hashtable is introduced which stores
hnodes of all the ap queues known to the ap bus.

The hashtable approach and a first implementation of this
interface comes from a previous patch from
Anthony Krowiak and an idea from Halil Pasic.

Signed-off-by: Harald Freudenberger <freude@linux.ibm.com>
Suggested-by: Tony Krowiak <akrowiak@linux.ibm.com>
Suggested-by: Halil Pasic <pasic@linux.ibm.com>
Reviewed-by: Tony Krowiak <akrowiak@linux.ibm.com>
Signed-off-by: Tony Krowiak <akrowiak@linux.ibm.com>
---
 drivers/s390/crypto/ap_bus.c   | 94 +++++++++++++++++++---------------
 drivers/s390/crypto/ap_bus.h   | 25 +++++----
 drivers/s390/crypto/ap_card.c  | 47 +++++++++--------
 drivers/s390/crypto/ap_queue.c | 10 ++--
 4 files changed, 95 insertions(+), 81 deletions(-)

```
#### [PATCH v2 1/2] KVM: nVMX: Properly handle kvm_read/write_guest_virt*() result
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11589553
Return-Path: <SRS0=rHMY=7S=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7750F618
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  5 Jun 2020 11:59:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4EE50206E6
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  5 Jun 2020 11:59:23 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="h8wJ57xq"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726499AbgFEL7V (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 5 Jun 2020 07:59:21 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:44900 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726324AbgFEL7R (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 5 Jun 2020 07:59:17 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1591358355;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=mxwh1xC29UBQwrK34p7n7N+1k3tNOzXKm1hVG0/SjCw=;
        b=h8wJ57xqCs5bEqD9odQsTzWsdKaPOHGIWdzTlA/jw9qtMx4qAHXgjO8bB5aUacIzL90Tgl
        s/BmODxjausiiW/nQENYFWCaS5biIKTV6Cn+c2o6u8/IkcAY7SOd9xTthn3LV+E4Vb0HSt
        iR2HQR2NjlrZ3TOrXqEc70pqfGAb1Qc=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-455-kdWgtLIDPkmc42XH3ejItg-1; Fri, 05 Jun 2020 07:59:11 -0400
X-MC-Unique: kdWgtLIDPkmc42XH3ejItg-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 4C5C88018A7;
        Fri,  5 Jun 2020 11:59:10 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.195.93])
        by smtp.corp.redhat.com (Postfix) with ESMTP id B45915D9DA;
        Fri,  5 Jun 2020 11:59:07 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>, linux-kernel@vger.kernel.org
Subject: [PATCH v2 1/2] KVM: nVMX: Properly handle
 kvm_read/write_guest_virt*() result
Date: Fri,  5 Jun 2020 13:59:05 +0200
Message-Id: <20200605115906.532682-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Syzbot reports the following issue:

WARNING: CPU: 0 PID: 6819 at arch/x86/kvm/x86.c:618
 kvm_inject_emulated_page_fault+0x210/0x290 arch/x86/kvm/x86.c:618
...
Call Trace:
...
RIP: 0010:kvm_inject_emulated_page_fault+0x210/0x290 arch/x86/kvm/x86.c:618
...
 nested_vmx_get_vmptr+0x1f9/0x2a0 arch/x86/kvm/vmx/nested.c:4638
 handle_vmon arch/x86/kvm/vmx/nested.c:4767 [inline]
 handle_vmon+0x168/0x3a0 arch/x86/kvm/vmx/nested.c:4728
 vmx_handle_exit+0x29c/0x1260 arch/x86/kvm/vmx/vmx.c:6067

'exception' we're trying to inject with kvm_inject_emulated_page_fault()
comes from:

  nested_vmx_get_vmptr()
   kvm_read_guest_virt()
     kvm_read_guest_virt_helper()
       vcpu->arch.walk_mmu->gva_to_gpa()

but it is only set when GVA to GPA conversion fails. In case it doesn't but
we still fail kvm_vcpu_read_guest_page(), X86EMUL_IO_NEEDED is returned and
nested_vmx_get_vmptr() calls kvm_inject_emulated_page_fault() with zeroed
'exception'. This happen when the argument is MMIO.

Paolo also noticed that nested_vmx_get_vmptr() is not the only place in
KVM code where kvm_read/write_guest_virt*() return result is mishandled.
All VMX instructions along with INVPCID/INVVPID/INVEPT have the same
issue. This was already noticed before, e.g. see commit 541ab2aeb282 ("KVM:
x86: work around leak of uninitialized stack contents") but was never fully
fixed.

KVM could've handled the request correctly by going to userspace and
performing I/O but there doesn't seem to be a good need for such requests
in the first place.

Introduce vmx_handle_memory_failure() as an interim solution.

Note, nested_vmx_get_vmptr() now has three possible outcomes: OK, PF,
KVM_EXIT_INTERNAL_ERROR and callers need to know if userspace exit is
needed (for KVM_EXIT_INTERNAL_ERROR) in case of failure. We don't seem
to have a good enum describing this tristate, just add "int *ret" to
nested_vmx_get_vmptr() interface to pass the information.

Reported-by: syzbot+2a7156e11dc199bdbd8a@syzkaller.appspotmail.com
Suggested-by: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/vmx/nested.c | 78 +++++++++++++++++++++------------------
 arch/x86/kvm/vmx/vmx.c    | 34 +++++++++++++++--
 arch/x86/kvm/vmx/vmx.h    |  2 +
 3 files changed, 74 insertions(+), 40 deletions(-)

```
#### [PATCH][v6] KVM: X86: support APERF/MPERF registers
##### From: Li RongQing <lirongqing@baidu.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Li,Rongqing" <lirongqing@baidu.com>
X-Patchwork-Id: 11588877
Return-Path: <SRS0=rHMY=7S=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 740371392
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  5 Jun 2020 01:44:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5330B20814
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  5 Jun 2020 01:44:52 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726026AbgFEBos (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 4 Jun 2020 21:44:48 -0400
Received: from mx134-tc.baidu.com ([61.135.168.134]:11537 "EHLO
        tc-sys-mailedm01.tc.baidu.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1725863AbgFEBos (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 4 Jun 2020 21:44:48 -0400
Received: from localhost (cp01-cos-dev01.cp01.baidu.com [10.92.119.46])
        by tc-sys-mailedm01.tc.baidu.com (Postfix) with ESMTP id F3B09204005A;
        Fri,  5 Jun 2020 09:44:26 +0800 (CST)
From: Li RongQing <lirongqing@baidu.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org, x86@kernel.org,
        hpa@zytor.com, bp@alien8.de, mingo@redhat.com, tglx@linutronix.de,
        jmattson@google.com, wanpengli@tencent.com, vkuznets@redhat.com,
        sean.j.christopherson@intel.com, pbonzini@redhat.com,
        xiaoyao.li@intel.com, lirongqing@baidu.com, wei.huang2@amd.com
Subject: [PATCH][v6] KVM: X86: support APERF/MPERF registers
Date: Fri,  5 Jun 2020 09:44:26 +0800
Message-Id: <1591321466-2046-1-git-send-email-lirongqing@baidu.com>
X-Mailer: git-send-email 1.7.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Guest kernel reports a fixed cpu frequency in /proc/cpuinfo,
this is confused to user when turbo is enable, and aperf/mperf
can be used to show current cpu frequency after 7d5905dc14a
"(x86 / CPU: Always show current CPU frequency in /proc/cpuinfo)"
so guest should support aperf/mperf capability

This patch implements aperf/mperf by three mode: none, software
emulation, and pass-through

None: default mode, guest does not support aperf/mperf

Software emulation: the period of aperf/mperf in guest mode are
accumulated as emulated value

Pass-though: it is only suitable for KVM_HINTS_REALTIME, Because
that hint guarantees we have a 1:1 vCPU:CPU binding and guaranteed
no over-commit.

And a per-VM capability is added to configure aperfmperf mode

Signed-off-by: Li RongQing <lirongqing@baidu.com>
Signed-off-by: Chai Wen <chaiwen@baidu.com>
Signed-off-by: Jia Lina <jialina01@baidu.com>

diff v5:
return error if guest is configured with mperf/aperf, but host cpu has not

diff v4:
fix maybe-uninitialized warning

diff v3:
fix interception of MSR_IA32_MPERF/APERF in svm

diff v2:
support aperfmperf pass though
move common codes to kvm_get_msr_common

diff v1:
1. support AMD, but not test
2. support per-vm capability to enable


 Documentation/virt/kvm/api.rst  | 10 ++++++++++
 arch/x86/include/asm/kvm_host.h | 11 +++++++++++
 arch/x86/kvm/cpuid.c            | 15 ++++++++++++++-
 arch/x86/kvm/svm/svm.c          |  8 ++++++++
 arch/x86/kvm/vmx/vmx.c          |  6 ++++++
 arch/x86/kvm/x86.c              | 42 +++++++++++++++++++++++++++++++++++++++++
 arch/x86/kvm/x86.h              | 15 +++++++++++++++
 include/uapi/linux/kvm.h        |  1 +
 8 files changed, 107 insertions(+), 1 deletion(-)

```
#### [PATCH RESEND 1/5] ifcvf: move IRQ request/free to status change handlers
##### From: Zhu Lingshan <lingshan.zhu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhu Lingshan <lingshan.zhu@intel.com>
X-Patchwork-Id: 11589419
Return-Path: <SRS0=rHMY=7S=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 98591618
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  5 Jun 2020 10:31:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 812502074B
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  5 Jun 2020 10:31:49 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726624AbgFEKbC (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 5 Jun 2020 06:31:02 -0400
Received: from mga18.intel.com ([134.134.136.126]:57119 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726592AbgFEKbB (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 5 Jun 2020 06:31:01 -0400
IronPort-SDR: 
 f6bPQv6nPW1E5QxE2pJxvyxnYBDKL4yw/8YI5b9dS/NrVzZDvmYLBUpnbod1OpnUUo9E/Kjyme
 PzX2X1Cfj/1g==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga002.fm.intel.com ([10.253.24.26])
  by orsmga106.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 05 Jun 2020 03:31:00 -0700
IronPort-SDR: 
 x5l/2qq2NG7AduJUCR//ecPM5gplqMOOPSBppxuPDxBjtehRJNt7jFb213Ks4AKv1K2AqNNpG1
 QftXd9Rhv5cw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,476,1583222400";
   d="scan'208";a="305024853"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.240.192.131])
  by fmsmga002.fm.intel.com with ESMTP; 05 Jun 2020 03:30:57 -0700
From: Zhu Lingshan <lingshan.zhu@intel.com>
To: mst@redhat.com, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org,
        linux-kernel@vger.kernel.org, netdev@vger.kernel.org,
        jasowang@redhat.com
Cc: lulu@redhat.com, dan.daly@intel.com, cunming.liang@intel.com,
        Zhu Lingshan <lingshan.zhu@intel.com>
Subject: [PATCH RESEND 1/5] ifcvf: move IRQ request/free to status change
 handlers
Date: Fri,  5 Jun 2020 18:27:11 +0800
Message-Id: <1591352835-22441-2-git-send-email-lingshan.zhu@intel.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1591352835-22441-1-git-send-email-lingshan.zhu@intel.com>
References: <1591352835-22441-1-git-send-email-lingshan.zhu@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

To comply with VIRTIO spec, this commit intends to move IRQ request
and free operations from probe() to device status changing handler,
would handle datapath start/stop in the handler as well.

VIRTIO spec 1.1, section 2.1.2 Device Requirements: Device Status Field
The device MUST NOT consume buffers or send any used buffer
notifications to the driver before DRIVER_OK.

Signed-off-by: Zhu Lingshan <lingshan.zhu@intel.com>
Acked-by: Jason Wang <jasowang@redhat.com>
---
 drivers/vdpa/ifcvf/ifcvf_main.c | 120 ++++++++++++++++++++++++----------------
 1 file changed, 73 insertions(+), 47 deletions(-)

```
#### [PATCH] x86/cpu: Reinitialize IA32_FEAT_CTL MSR on BSP during wakeup
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11590457
Return-Path: <SRS0=rHMY=7S=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 988D8912
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  5 Jun 2020 20:07:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8879B20820
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  5 Jun 2020 20:07:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728206AbgFEUHb (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 5 Jun 2020 16:07:31 -0400
Received: from mga06.intel.com ([134.134.136.31]:29603 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727863AbgFEUHb (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 5 Jun 2020 16:07:31 -0400
IronPort-SDR: 
 9+/foVPL4zKWpLFPjcMZ5jOulC2NGrrkaSmrW0fmrRkxCSZDxFduUa77/GlPCsfV9GwjecvihX
 ZFVqsJkSugug==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga002.fm.intel.com ([10.253.24.26])
  by orsmga104.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 05 Jun 2020 13:07:30 -0700
IronPort-SDR: 
 isHsEJJwy5bDEQA3VzN4WLRvdBKo8wguUddVPlTivtJSK5oLw205TZHHBA1nmxfFh3FXYe6Yxy
 6rJTfRuXs+0g==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,477,1583222400";
   d="scan'208";a="305171032"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.152])
  by fmsmga002.fm.intel.com with ESMTP; 05 Jun 2020 13:07:29 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        x86@kernel.org, "Rafael J. Wysocki" <rjw@rjwysocki.net>,
        Pavel Machek <pavel@ucw.cz>
Cc: "H. Peter Anvin" <hpa@zytor.com>, linux-kernel@vger.kernel.org,
        linux-pm@vger.kernel.org,
        Brad Campbell <lists2009@fnarfbargle.com>,
        Maxim Levitsky <mlevitsk@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org,
        Sean Christopherson <sean.j.christopherson@intel.com>
Subject: [PATCH] x86/cpu: Reinitialize IA32_FEAT_CTL MSR on BSP during wakeup
Date: Fri,  5 Jun 2020 13:07:28 -0700
Message-Id: <20200605200728.10145-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Reinitialize IA32_FEAT_CTL on the BSP during wakeup to handle the case
where firmware doesn't initialize or save/restore across S3.  This fixes
a bug where IA32_FEAT_CTL is left uninitialized and results in VMXON
taking a #GP due to VMX not being fully enabled, i.e. breaks KVM.

Use init_ia32_feat_ctl() to "restore" IA32_FEAT_CTL as it already deals
with the case where the MSR is locked, and because APs already redo
init_ia32_feat_ctl() during suspend by virtue of the SMP boot flow being
used to reinitialize APs upon wakeup.  Do the call in the early wakeup
flow to avoid dependencies in the syscore_ops chain, e.g. simply adding
a resume hook is not guaranteed to work, as KVM does VMXON in its own
resume hook, kvm_resume(), when KVM has active guests.

Reported-by: Brad Campbell <lists2009@fnarfbargle.com>
Cc: Maxim Levitsky <mlevitsk@redhat.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org
Fixes: 21bd3467a58e ("KVM: VMX: Drop initialization of IA32_FEAT_CTL MSR")
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/include/asm/cpu.h | 5 +++++
 arch/x86/kernel/cpu/cpu.h  | 4 ----
 arch/x86/power/cpu.c       | 6 ++++++
 3 files changed, 11 insertions(+), 4 deletions(-)

```
#### [PATCH] x86/split_lock: Don't write MSR_TEST_CTRL on CPUs that aren't whitelisted
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11590441
Return-Path: <SRS0=rHMY=7S=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4AC7C90
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  5 Jun 2020 19:26:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 32FA920810
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  5 Jun 2020 19:26:13 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727960AbgFET0J (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 5 Jun 2020 15:26:09 -0400
Received: from mga03.intel.com ([134.134.136.65]:18768 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726963AbgFET0I (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 5 Jun 2020 15:26:08 -0400
IronPort-SDR: 
 n3I0NnNI4r1LG2DD5PeoMLoXXrZssg+o73LbOn/XqoUXeGqMbpiFaT5j6DCGPPiy3UsCLAZErb
 9vob7FAtucSg==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga003.fm.intel.com ([10.253.24.29])
  by orsmga103.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 05 Jun 2020 12:26:07 -0700
IronPort-SDR: 
 N8mvhEuF9Yca0EaUBhaf8fWySQ/j2CY/8kTmbLZhcDGBSiIsoZYSuPht8u0/Gm0igCQOpET3+p
 L2ywfryHylKg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,477,1583222400";
   d="scan'208";a="313279638"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.152])
  by FMSMGA003.fm.intel.com with ESMTP; 05 Jun 2020 12:26:07 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        x86@kernel.org
Cc: "H. Peter Anvin" <hpa@zytor.com>, linux-kernel@vger.kernel.org,
        Xiaoyao Li <xiaoyao.li@intel.com>,
        Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org,
        Sean Christopherson <sean.j.christopherson@intel.com>
Subject: [PATCH] x86/split_lock: Don't write MSR_TEST_CTRL on CPUs that aren't
 whitelisted
Date: Fri,  5 Jun 2020 12:26:05 -0700
Message-Id: <20200605192605.7439-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Choo! Choo!  All aboard the Split Lock Express, with direct service to
Wreckage!

Skip split_lock_verify_msr() if the CPU isn't whitelisted as a possible
SLD-enabled CPU model to avoid writing MSR_TEST_CTRL.  MSR_TEST_CTRL
exists, and is writable, on many generations of CPUs.  Writing the MSR,
even with '0', can result in bizarre, undocumented behavior.

This fixes a crash on Haswell when resuming from suspend with a live KVM
guest.  Because APs use the standard SMP boot flow for resume, they will
go through split_lock_init() and the subsequent RDMSR/WRMSR sequence,
which runs even when sld_state==sld_off to ensure SLD is disabled.  On
Haswell (at least, my Haswell), writing MSR_TEST_CTRL with '0' will
succeed and _may_ take the SMT _sibling_ out of VMX root mode.

When KVM has an active guest, KVM performs VMXON as part of CPU onlining
(see kvm_starting_cpu()).  Because SMP boot is serialized, the resulting
flow is effectively:

  on_each_ap_cpu() {
     WRMSR(MSR_TEST_CTRL, 0)
     VMXON
  }

As a result, the WRMSR can disable VMX on a different CPU that has
already done VMXON.  This ultimately results in a #UD on VMPTRLD when
KVM regains control and attempt run its vCPUs.

The above voodoo was confirmed by reworking KVM's VMXON flow to write
MSR_TEST_CTRL prior to VMXON, and to serialize the sequence as above.
Further verification of the insanity was done by redoing VMXON on all
APs after the initial WRMSR->VMXON sequence.  The additional VMXON,
which should VM-Fail, occasionally succeeded, and also eliminated the
unexpected #UD on VMPTRLD.

The damage done by writing MSR_TEST_CTRL doesn't appear to be limited
to VMX, e.g. after suspend with an active KVM guest, subsequent reboots
almost always hang (even when fudging VMXON), a #UD on a random Jcc was
observed, suspend/resume stability is qualitatively poor, and so on and
so forth.

  kernel BUG at arch/x86/kvm/x86.c:386!
  invalid opcode: 0000 [#7] SMP
  CPU: 1 PID: 2592 Comm: CPU 6/KVM Tainted: G      D
  Hardware name: ASUS Q87M-E/Q87M-E, BIOS 1102 03/03/2014
  RIP: 0010:kvm_spurious_fault+0xf/0x20
  Code: <0f> 0b 0f 1f 44 00 00 66 2e 0f 1f 84 00 00 00 00 00 0f 1f 44 00 00
  RSP: 0018:ffffc0bcc1677b78 EFLAGS: 00010246
  RAX: 0000617640000000 RBX: ffff9e8d01d80000 RCX: ffff9e8d4fa40000
  RDX: ffff9e8d03360000 RSI: 00000003c3360000 RDI: ffff9e8d03360000
  RBP: 0000000000000001 R08: ffff9e8d046d9d40 R09: 0000000000000018
  R10: ffffc0bcc1677b80 R11: 0000000000000008 R12: 0000000000000006
  R13: 0000000000000000 R14: 0000000000000000 R15: 0000000000000000
  FS:  00007fe16c9f9700(0000) GS:ffff9e8d4fa40000(0000) knlGS:0000000000000000
  CS:  0010 DS: 0000 ES: 0000 CR0: 0000000080050033
  CR2: 0000000000d7a418 CR3: 00000003c47b1006 CR4: 00000000001626e0
  Call Trace:
   vmx_vcpu_load_vmcs+0x1fb/0x2b0
   vmx_vcpu_load+0x3e/0x160
   kvm_arch_vcpu_load+0x48/0x260
   finish_task_switch+0x140/0x260
   __schedule+0x460/0x720
   _cond_resched+0x2d/0x40
   kvm_arch_vcpu_ioctl_run+0x82e/0x1ca0
   kvm_vcpu_ioctl+0x363/0x5c0
   ksys_ioctl+0x88/0xa0
   __x64_sys_ioctl+0x16/0x20
   do_syscall_64+0x4c/0x170
   entry_SYSCALL_64_after_hwframe+0x44/0xa9

Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Xiaoyao Li <xiaoyao.li@intel.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org
Fixes: dbaba47085b0c ("x86/split_lock: Rework the initialization flow of split lock detection")
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kernel/cpu/intel.c | 11 ++++++++++-
 1 file changed, 10 insertions(+), 1 deletion(-)

```
