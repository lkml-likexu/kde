#### [PATCH v3 1/5] vhost: convert VHOST_VSOCK_SET_RUNNING to a generic ioctl
##### From: Guennadi Liakhovetski <guennadi.liakhovetski@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Guennadi Liakhovetski
 <guennadi.liakhovetski@linux.intel.com>
X-Patchwork-Id: 11573715
Return-Path: <SRS0=eyEw=7J=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7984A60D
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 27 May 2020 18:05:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6BB3420899
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 27 May 2020 18:05:49 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2389027AbgE0SFs (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 27 May 2020 14:05:48 -0400
Received: from mga09.intel.com ([134.134.136.24]:57368 "EHLO mga09.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2387706AbgE0SFs (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 27 May 2020 14:05:48 -0400
IronPort-SDR: 
 6JdRG1+QdRjfK24fQqZobAFbuZG3u0DrsctchT0/+ZaNPFzV3kNbSrdz/YV4WnGPh/5raKUq1P
 LmuJO9iVAXLg==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga006.jf.intel.com ([10.7.209.51])
  by orsmga102.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 27 May 2020 11:05:48 -0700
IronPort-SDR: 
 4UsyZtFFCxi4B9q9Mkk3x08+aT/JYRBr7ju1ejj11/RmcPfyoVUItqp2IjQ2aW/2E4hOlqG/Ni
 z67gX2OVkpXQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,442,1583222400";
   d="scan'208";a="270553297"
Received: from gliakhov-mobl2.ger.corp.intel.com (HELO
 ubuntu.ger.corp.intel.com) ([10.252.42.249])
  by orsmga006.jf.intel.com with ESMTP; 27 May 2020 11:05:45 -0700
From: Guennadi Liakhovetski <guennadi.liakhovetski@linux.intel.com>
To: kvm@vger.kernel.org
Cc: linux-remoteproc@vger.kernel.org,
        virtualization@lists.linux-foundation.org,
        sound-open-firmware@alsa-project.org,
        Pierre-Louis Bossart <pierre-louis.bossart@linux.intel.com>,
        Liam Girdwood <liam.r.girdwood@linux.intel.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Jason Wang <jasowang@redhat.com>,
        Ohad Ben-Cohen <ohad@wizery.com>,
        Bjorn Andersson <bjorn.andersson@linaro.org>,
        Mathieu Poirier <mathieu.poirier@linaro.org>
Subject: [PATCH v3 1/5] vhost: convert VHOST_VSOCK_SET_RUNNING to a generic
 ioctl
Date: Wed, 27 May 2020 20:05:37 +0200
Message-Id: <20200527180541.5570-2-guennadi.liakhovetski@linux.intel.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20200527180541.5570-1-guennadi.liakhovetski@linux.intel.com>
References: <20200527180541.5570-1-guennadi.liakhovetski@linux.intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

VHOST_VSOCK_SET_RUNNING is used by the vhost vsock driver to perform
crucial VirtQueue initialisation, like assigning .private fields and
calling vhost_vq_init_access(), and clean up. However, this ioctl is
actually extremely useful for any vhost driver, that doesn't have a
side channel to inform it of a status change, e.g. upon a guest
reboot. This patch makes that ioctl generic, while preserving its
numeric value and also keeping the original alias.

Signed-off-by: Guennadi Liakhovetski <guennadi.liakhovetski@linux.intel.com>
---
 include/uapi/linux/vhost.h | 4 +++-
 1 file changed, 3 insertions(+), 1 deletion(-)

```
#### [PATCH v3 1/2] KVM: VMX: enable X86_FEATURE_WAITPKG in KVM capabilities
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 11573073
Return-Path: <SRS0=eyEw=7J=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4253A90
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 27 May 2020 14:04:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2B24D20EDD
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 27 May 2020 14:04:42 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="TlyRv+7f"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730363AbgE0OEl (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 27 May 2020 10:04:41 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:58036 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1730258AbgE0OEk (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 27 May 2020 10:04:40 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1590588280;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=LoMxv8kbrQ7HIAUcS1Qgahod+d8JOwkdyw5s7rWVktc=;
        b=TlyRv+7fD16zpHxZezzCBJowxVL0lQuNe2jKaQE7Uk+fLt5NE1T2FAb1ofcuXZ5FT77IbI
        2cvNBO4LKpCYz3GyRrejUciRCwsYYK0ZkWUBIKczf5QlVAADSyqOhGkto4rDAytiPZdyn/
        V03kJM2nnwCX8PPmRS3iT5I0k+7lNZk=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-76-G9Dv8E5LO6mDJTCtZeQgzQ-1; Wed, 27 May 2020 10:04:38 -0400
X-MC-Unique: G9Dv8E5LO6mDJTCtZeQgzQ-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id E203519057A1;
        Wed, 27 May 2020 14:04:36 +0000 (UTC)
Received: from starship.f32vm (unknown [10.35.206.172])
        by smtp.corp.redhat.com (Postfix) with ESMTP id D21471C946;
        Wed, 27 May 2020 14:04:32 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, Ingo Molnar <mingo@redhat.com>,
        Borislav Petkov <bp@alien8.de>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Jingqi Liu <jingqi.liu@intel.com>, Tao Xu <tao3.xu@intel.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        "H. Peter Anvin" <hpa@zytor.com>, Joerg Roedel <joro@8bytes.org>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        x86@kernel.org (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT)),
        Maxim Levitsky <mlevitsk@redhat.com>,
        Krish Sadhukhan <krish.sadhukhan@oracle.com>
Subject: [PATCH v3 1/2] KVM: VMX: enable X86_FEATURE_WAITPKG in KVM
 capabilities
Date: Wed, 27 May 2020 17:04:24 +0300
Message-Id: <20200527140425.3484-2-mlevitsk@redhat.com>
In-Reply-To: <20200527140425.3484-1-mlevitsk@redhat.com>
References: <20200527140425.3484-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Even though we might not allow the guest to use WAITPKG's new instructions,
we should tell KVM that the feature is supported by the host CPU.

Note that vmx_waitpkg_supported checks that WAITPKG _can_ be set in the
secondary execution controls as specified by VMX capability MSR,
rather that indicate that we actually enable it for a guest.

Fixes: e69e72faa3a07 (KVM: x86: Add support for user wait instructions)

Suggested-by: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Maxim Levitsky <mlevitsk@redhat.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
Reviewed-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 arch/x86/kvm/vmx/vmx.c | 3 +++
 1 file changed, 3 insertions(+)

```
#### [PATCH] KVM: nVMX: Preserve registers modifications done before nested_svm_vmexit()
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11572259
Return-Path: <SRS0=eyEw=7J=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2A39460D
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 27 May 2020 08:29:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 125252084C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 27 May 2020 08:29:33 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Bxgki3Zp"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729578AbgE0I3c (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 27 May 2020 04:29:32 -0400
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:59101 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729497AbgE0I3b (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 27 May 2020 04:29:31 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1590568170;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=8QOC8GoFKK5IDy7Fbg6T/1YhJRpFsrglY/dRIt6Yu28=;
        b=Bxgki3ZpQ/qu8l1d7ix3l1JYyNPZ5hruJFsuUzKpiNLcFbARQ7hH8+/Abi2gsNOdatQNVM
        huEIhJVtL9mEBQuJJJ4RK3Ux+hYGc/E9Wx6MckiN79FXMYBMg2EBMVT88+0wD7BaiHmpNQ
        SpWxMTrWaHt4galD9Zqih1y3O7TYEgU=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-3-5UPbVJK1OQ2nacCcycmRZQ-1; Wed, 27 May 2020 04:29:27 -0400
X-MC-Unique: 5UPbVJK1OQ2nacCcycmRZQ-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 0133A1005512;
        Wed, 27 May 2020 08:29:26 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.192.209])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 7FA8C5D9E5;
        Wed, 27 May 2020 08:29:23 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Cathy Avery <cavery@redhat.com>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH] KVM: nVMX: Preserve registers modifications done before
 nested_svm_vmexit()
Date: Wed, 27 May 2020 10:29:21 +0200
Message-Id: <20200527082921.218601-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

L2 guest hang is observed after 'exit_required' was dropped and nSVM
switched to check_nested_events() completely. The hang is a busy loop when
e.g. KVM is emulating an instruction (e.g. L2 is accessing MMIO space and
we drop to userspace). After nested_svm_vmexit() and when L1 is doing VMRUN
nested guest's RIP is not advanced so KVM goes into emulating the same
instruction which cased nested_svm_vmexit() and the loop continues.

nested_svm_vmexit() is not new, however, with check_nested_events() we're
now calling it later than before. In case by that time KVM has modified
register state we may pick stale values from VMCS when trying to save
nested guest state to nested VMCB.

VMX code handles this case correctly: sync_vmcs02_to_vmcs12() called from
nested_vmx_vmexit() does 'vmcs12->guest_rip = kvm_rip_read(vcpu)' and this
ensures KVM-made modifications are preserved. Do the same for nVMX.

Generally, nested_vmx_vmexit()/nested_svm_vmexit() need to pick up all
nested guest state modifications done by KVM after vmexit. It would be
great to find a way to express this in a way which would not require to
manually track these changes, e.g. nested_{vmcb,vmcs}_get_field().

Co-debugged-with: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
- To certain extent we're fixing currently-pending 'KVM: SVM: immediately
 inject INTR vmexit' commit but I'm not certain about that. We had so many
 problems with nested events before switching to check_nested_events() that
 what worked before could just be treated as a miracle. Miracles tend to
 appear and disappear all of a sudden.
---
 arch/x86/kvm/svm/nested.c | 6 +++---
 1 file changed, 3 insertions(+), 3 deletions(-)

```
#### [PATCH] KVM: x86: Initialize tdp_level during vCPU creation
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11572311
Return-Path: <SRS0=eyEw=7J=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 78015912
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 27 May 2020 08:54:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6A3562078B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 27 May 2020 08:54:05 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388192AbgE0IyC (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 27 May 2020 04:54:02 -0400
Received: from mga17.intel.com ([192.55.52.151]:18477 "EHLO mga17.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2388019AbgE0IyC (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 27 May 2020 04:54:02 -0400
IronPort-SDR: 
 NzUkZnxz/Kv4fBGO/iVWpVBiC27CNeS8BjFK3dXnmjVLc0VXMqVkw7qv228EKzHaCx6078gWKn
 U57p+20liE3w==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga002.jf.intel.com ([10.7.209.21])
  by fmsmga107.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 27 May 2020 01:54:01 -0700
IronPort-SDR: 
 X4MCtpRkLljsgR7+EkaTcY9qggKkR+7funFrhV7OCKkBeiyURWXENxtDHbdrLfTArkU5NtAPnL
 /hvq1Txw7Frg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,440,1583222400";
   d="scan'208";a="284736246"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.152])
  by orsmga002.jf.intel.com with ESMTP; 27 May 2020 01:54:01 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org,
        syzbot+904752567107eefb728c@syzkaller.appspotmail.com
Subject: [PATCH] KVM: x86: Initialize tdp_level during vCPU creation
Date: Wed, 27 May 2020 01:54:00 -0700
Message-Id: <20200527085400.23759-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Initialize vcpu->arch.tdp_level during vCPU creation to avoid consuming
garbage if userspace calls KVM_RUN without first calling KVM_SET_CPUID.

Fixes: e93fd3b3e89e9 ("KVM: x86/mmu: Capture TDP level when updating CPUID")
Reported-by: syzbot+904752567107eefb728c@syzkaller.appspotmail.com
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/x86.c | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH] KVM: x86/mmu: Set mmio_value to '0' if reserved #PF can't be generated
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11572301
Return-Path: <SRS0=eyEw=7J=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DD98C60D
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 27 May 2020 08:49:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CD95D2078C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 27 May 2020 08:49:15 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388268AbgE0ItM (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 27 May 2020 04:49:12 -0400
Received: from mga06.intel.com ([134.134.136.31]:18700 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2388173AbgE0ItM (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 27 May 2020 04:49:12 -0400
IronPort-SDR: 
 ppc5c+AhmTRp5NuQ514pzNnoKc2bNMN2mGH5pee3UTsOzxXYJ5ksHTLJbcnJrdVHOJ6ke7LlEM
 EyBMDOJfImuA==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga007.fm.intel.com ([10.253.24.52])
  by orsmga104.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 27 May 2020 01:49:11 -0700
IronPort-SDR: 
 OPrgdhhPN+h5HL5PvgzCH//opLERqRbC79bQCFH6zzeXmEejHv6+cdk4yzhFg2TqPI7Fz7UJ2B
 QAJM/FhgrYmA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,440,1583222400";
   d="scan'208";a="255414431"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.152])
  by fmsmga007.fm.intel.com with ESMTP; 27 May 2020 01:49:10 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: x86/mmu: Set mmio_value to '0' if reserved #PF can't be
 generated
Date: Wed, 27 May 2020 01:49:09 -0700
Message-Id: <20200527084909.23492-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Set the mmio_value to '0' instead of simply clearing the present bit to
squash a benign warning in kvm_mmu_set_mmio_spte_mask() that complains
about the mmio_value overlapping the lower GFN mask on systems with 52
bits of PA space.

Opportunistically clean up the code and comments.

Fixes: 608831174100 ("KVM: x86: only do L1TF workaround on affected processors")
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---

Thanks for the excuse to clean up kvm_set_mmio_spte_mask(), been wanting a
reason to fix that mess for a few months now :-).

 arch/x86/kvm/mmu/mmu.c | 27 +++++++++------------------
 1 file changed, 9 insertions(+), 18 deletions(-)

```
#### [PATCH] KVM: x86: simplify is_mmio_spte
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11573613
Return-Path: <SRS0=eyEw=7J=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3DF43159A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 27 May 2020 17:12:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 263FE20890
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 27 May 2020 17:12:31 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="godB6zxk"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731215AbgE0RM2 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 27 May 2020 13:12:28 -0400
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:25791 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1730006AbgE0RM2 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 27 May 2020 13:12:28 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1590599546;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=0Ma+strw5r3/zerzC9gCl0y+XwFVc4Xo+zlOUjNhXTY=;
        b=godB6zxkcscSCeZrHJ90Xwrk3hc0Ya/Wo6upCywZZjsYetU4EF2pH3DI9XaAbNBvQCxvM3
        J8KO9raB7tLJfc2fTRmhVfj8Gvl4oXH3HFR6EJhOVobQs7lbjnr8HihRkaek0hjv8y88ij
        9YNkGtk51zAwPxxFCYM2dAQapR8zjwI=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-373-3CpxfOFBMOmIMhUA1TfO8A-1; Wed, 27 May 2020 13:12:21 -0400
X-MC-Unique: 3CpxfOFBMOmIMhUA1TfO8A-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 2AB3253;
        Wed, 27 May 2020 17:12:20 +0000 (UTC)
Received: from virtlab511.virt.lab.eng.bos.redhat.com
 (virtlab511.virt.lab.eng.bos.redhat.com [10.19.152.198])
        by smtp.corp.redhat.com (Postfix) with ESMTP id D9F4F5D9E5;
        Wed, 27 May 2020 17:12:19 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [PATCH] KVM: x86: simplify is_mmio_spte
Date: Wed, 27 May 2020 13:12:19 -0400
Message-Id: <20200527171219.130319-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We can simply look at bits 52-53 to identify MMIO entries in KVM's page
tables.  Therefore, there is no need to pass a mask to kvm_mmu_set_mmio_spte_mask.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/mmu.h     |  2 +-
 arch/x86/kvm/mmu/mmu.c | 10 +++-------
 arch/x86/kvm/svm/svm.c |  2 +-
 arch/x86/kvm/vmx/vmx.c |  3 +--
 4 files changed, 6 insertions(+), 11 deletions(-)

```
#### [PATCH v2] KVM: nSVM: Preserve registers modifications done before nested_svm_vmexit()
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11572331
Return-Path: <SRS0=eyEw=7J=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C126B60D
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 27 May 2020 09:01:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A91B7207E8
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 27 May 2020 09:01:15 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Wx+0RN9K"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388323AbgE0JBO (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 27 May 2020 05:01:14 -0400
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:46344 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S2388213AbgE0JBO (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 27 May 2020 05:01:14 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1590570072;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=H3stnU91LhnxpV8eTnwJlnlF2JcqMMwBmM20JYfVSKI=;
        b=Wx+0RN9KF2oESFyp8/XuIs0T/rJWihBM5xuxUuvn3zQnlQu2KXHNSCICmE/0MoIsuJ4br7
        3VcM9RsOskltg2SCXJqrUjjCk4zimJwEvZpr/Eo8nqU2bLVxaJWIPZKc9Rmu6pT6lKuSqg
        8Tn4NH1Z5nwalHaYd3ET8To2djkdyYc=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-164-3BAWVqMbMdCBGWSrTSe0cA-1; Wed, 27 May 2020 05:01:07 -0400
X-MC-Unique: 3BAWVqMbMdCBGWSrTSe0cA-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id A01CD107B26F;
        Wed, 27 May 2020 09:01:06 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.192.209])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 2B1F25D9E5;
        Wed, 27 May 2020 09:01:03 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Cathy Avery <cavery@redhat.com>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH v2] KVM: nSVM: Preserve registers modifications done before
 nested_svm_vmexit()
Date: Wed, 27 May 2020 11:01:02 +0200
Message-Id: <20200527090102.220647-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

L2 guest hang is observed after 'exit_required' was dropped and nSVM
switched to check_nested_events() completely. The hang is a busy loop when
e.g. KVM is emulating an instruction (e.g. L2 is accessing MMIO space and
we drop to userspace). After nested_svm_vmexit() and when L1 is doing VMRUN
nested guest's RIP is not advanced so KVM goes into emulating the same
instruction which caused nested_svm_vmexit() and the loop continues.

nested_svm_vmexit() is not new, however, with check_nested_events() we're
now calling it later than before. In case by that time KVM has modified
register state we may pick stale values from VMCB when trying to save
nested guest state to nested VMCB.

nVMX code handles this case correctly: sync_vmcs02_to_vmcs12() called from
nested_vmx_vmexit() does e.g 'vmcs12->guest_rip = kvm_rip_read(vcpu)' and
this ensures KVM-made modifications are preserved. Do the same for nSVM.

Generally, nested_vmx_vmexit()/nested_svm_vmexit() need to pick up all
nested guest state modifications done by KVM after vmexit. It would be
great to find a way to express this in a way which would not require to
manually track these changes, e.g. nested_{vmcb,vmcs}_get_field().

Co-debugged-with: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
- Changes from v1:
 s,nVMX,nSVM,g + typos [Sean Christopherson]

- To certain extent we're fixing currently-pending 'KVM: SVM: immediately
 inject INTR vmexit' commit but I'm not certain about that. We had so many
 problems with nested events before switching to check_nested_events() that
 what worked before could just be treated as a miracle. Miracles tend to
 appear and disappear all of a sudden.
---
 arch/x86/kvm/svm/nested.c | 6 +++---
 1 file changed, 3 insertions(+), 3 deletions(-)

```
