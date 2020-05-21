#### [PATCH 01/24] KVM: nSVM: fix condition for filtering async PF
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11560873
Return-Path: <SRS0=QMHo=7C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 59C2C912
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 20 May 2020 17:21:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 41BC92075F
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 20 May 2020 17:21:57 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Nt1GIeMw"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726836AbgETRVw (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 20 May 2020 13:21:52 -0400
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:51966 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726439AbgETRVv (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 20 May 2020 13:21:51 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1589995311;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:in-reply-to:in-reply-to:references:references;
        bh=WrBR4w78uBBs4VQ3VrdJAzQ/9ZZhP1UKmnG9BOpHw14=;
        b=Nt1GIeMwWsE/Gy86bi6nYa7LBGB/H8I58kZH6Nns5IXWAfOVi9ihX0m9V6nVYSCzHSWFyT
        Xj80PwQ5LoFAMkw9eEYA+1zA+cc/XqpUEatfHSXR7RcnEASZKc/lQWrvwWy9AyfZynI3wC
        yR46IusMGZWy/Rot9PDxaLX05djDsKs=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-78-Z5e_C_Z6Obud2Kubqpe_6Q-1; Wed, 20 May 2020 13:21:48 -0400
X-MC-Unique: Z5e_C_Z6Obud2Kubqpe_6Q-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 80443A0BE6;
        Wed, 20 May 2020 17:21:47 +0000 (UTC)
Received: from virtlab511.virt.lab.eng.bos.redhat.com
 (virtlab511.virt.lab.eng.bos.redhat.com [10.19.152.198])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 0434E60610;
        Wed, 20 May 2020 17:21:46 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: vkuznets@redhat.com, Joerg Roedel <jroedel@suse.de>,
        stable@vger.kernel.org
Subject: [PATCH 01/24] KVM: nSVM: fix condition for filtering async PF
Date: Wed, 20 May 2020 13:21:22 -0400
Message-Id: <20200520172145.23284-2-pbonzini@redhat.com>
In-Reply-To: <20200520172145.23284-1-pbonzini@redhat.com>
References: <20200520172145.23284-1-pbonzini@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Async page faults have to be trapped in the host (L1 in this case),
since the APF reason was passed from L0 to L1 and stored in the L1 APF
data page.  This was completely reversed: the page faults were passed
to the guest, a L2 hypervisor.

Cc: stable@vger.kernel.org
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/svm/nested.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH Kernel v23 1/8] vfio: UAPI for migration interface for device state
##### From: Kirti Wankhede <kwankhede@nvidia.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kirti Wankhede <kwankhede@nvidia.com>
X-Patchwork-Id: 11561027
Return-Path: <SRS0=QMHo=7C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0882114C0
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 20 May 2020 18:41:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DA6EC207D4
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 20 May 2020 18:41:32 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=nvidia.com header.i=@nvidia.com
 header.b="cuGtN4Ql"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726905AbgETSlb (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 20 May 2020 14:41:31 -0400
Received: from hqnvemgate24.nvidia.com ([216.228.121.143]:7178 "EHLO
        hqnvemgate24.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726548AbgETSl3 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 20 May 2020 14:41:29 -0400
Received: from hqpgpgate102.nvidia.com (Not Verified[216.228.121.13]) by
 hqnvemgate24.nvidia.com (using TLS: TLSv1.2, DES-CBC3-SHA)
        id <B5ec579470000>; Wed, 20 May 2020 11:39:03 -0700
Received: from hqmail.nvidia.com ([172.20.161.6])
  by hqpgpgate102.nvidia.com (PGP Universal service);
  Wed, 20 May 2020 11:41:27 -0700
X-PGP-Universal: processed;
        by hqpgpgate102.nvidia.com on Wed, 20 May 2020 11:41:27 -0700
Received: from HQMAIL105.nvidia.com (172.20.187.12) by HQMAIL111.nvidia.com
 (172.20.187.18) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Wed, 20 May
 2020 18:41:26 +0000
Received: from kwankhede-dev.nvidia.com (10.124.1.5) by HQMAIL105.nvidia.com
 (172.20.187.12) with Microsoft SMTP Server (TLS) id 15.0.1473.3 via Frontend
 Transport; Wed, 20 May 2020 18:41:19 +0000
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
        "Kirti Wankhede" <kwankhede@nvidia.com>
Subject: [PATCH Kernel v23 1/8] vfio: UAPI for migration interface for device
 state
Date: Wed, 20 May 2020 23:38:01 +0530
Message-ID: <1589998088-3250-2-git-send-email-kwankhede@nvidia.com>
X-Mailer: git-send-email 2.7.0
In-Reply-To: <1589998088-3250-1-git-send-email-kwankhede@nvidia.com>
References: <1589998088-3250-1-git-send-email-kwankhede@nvidia.com>
X-NVConfidentiality: public
MIME-Version: 1.0
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1589999943; bh=s4Iv0GJDj+1bhl4jbE8YcxRvsfl81dyjXBeOzB1RdI0=;
        h=X-PGP-Universal:From:To:CC:Subject:Date:Message-ID:X-Mailer:
         In-Reply-To:References:X-NVConfidentiality:MIME-Version:
         Content-Type;
        b=cuGtN4Ql9q8Jt2XSzwZsUrlpDvQkaPQoZT4KGDYPcVqbzd71q6UVgkOFD0hoHYp2r
         vSOOGtOreMvqBodEPWTcwWGWzHOVZjXIKB1YSzkr9qV/k6jtmod14SWoiL36ffIDhp
         nn/4lB6TZ8HSSSZ888EAKavvXsia9Pt+KVy01BOBZ2ZoGksMC38Vq7XWBFdLqsGUQ9
         LORmOFPZWRhotIfhbHOQaDtLDrOaTZBLb2CwLAWEAzL3faxPy8BxMD9TKAwapzz80n
         43pZtOt+LOcYoIziI0HTUNmJF+6z7jUaQroaGeTMbX8w8hDOZKuEtiY2Ui3bitsUQz
         oXkSd9nZXr5sQ==
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

- Defined MIGRATION region type and sub-type.

- Defined vfio_device_migration_info structure which will be placed at the
  0th offset of migration region to get/set VFIO device related
  information. Defined members of structure and usage on read/write access.

- Defined device states and state transition details.

- Defined sequence to be followed while saving and resuming VFIO device.

Signed-off-by: Kirti Wankhede <kwankhede@nvidia.com>
Reviewed-by: Neo Jia <cjia@nvidia.com>
---
 include/uapi/linux/vfio.h | 228 ++++++++++++++++++++++++++++++++++++++++++++++
 1 file changed, 228 insertions(+)

```
#### [PATCH 1/2] kvm: cosmetic: remove wrong braces in kvm_init_msr_list switch
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 11560655
Return-Path: <SRS0=QMHo=7C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 05BAC14C0
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 20 May 2020 16:08:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E2860207D8
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 20 May 2020 16:08:06 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="SsVN176h"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726844AbgETQH7 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 20 May 2020 12:07:59 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:35179 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726747AbgETQHu (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 20 May 2020 12:07:50 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1589990869;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=E7vWrkA41Lbp4gQucfyzJ2NA68KZJVdfSkrpXlefoOA=;
        b=SsVN176hbxT4S7Eu8lAkUfhoZkpsdOmo8rLSHLi/ii1DJ4FOmlJMGkWGodArQwT3JxM+u3
        QvZDfRPFCW1TV1StbfgfegQIUhKYJYJ1PmxKO3s2ELv+HV+8u8ltpR2XuyE+W/wVvw6iOc
        Fct69C4WApqybDAawEErl6M/48uswtQ=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-418-vgoOO36qM3CobbxcYUw79g-1; Wed, 20 May 2020 12:07:46 -0400
X-MC-Unique: vgoOO36qM3CobbxcYUw79g-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id CFD198015D2;
        Wed, 20 May 2020 16:07:45 +0000 (UTC)
Received: from starship.fedora32vm (unknown [10.35.207.28])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 9168D341FD;
        Wed, 20 May 2020 16:07:44 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH 1/2] kvm: cosmetic: remove wrong braces in kvm_init_msr_list
 switch
Date: Wed, 20 May 2020 19:07:39 +0300
Message-Id: <20200520160740.6144-2-mlevitsk@redhat.com>
In-Reply-To: <20200520160740.6144-1-mlevitsk@redhat.com>
References: <20200520160740.6144-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

I think these were added accidentally.

Signed-off-by: Maxim Levitsky <mlevitsk@redhat.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/x86.c | 3 +--
 1 file changed, 1 insertion(+), 2 deletions(-)

```
#### [PATCH 03/24] KVM: nSVM: inject exceptions via svm_check_nested_events
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11560875
Return-Path: <SRS0=QMHo=7C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 766E214C0
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 20 May 2020 17:21:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5F50D207FB
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 20 May 2020 17:21:57 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="W4NlzYjS"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727847AbgETRV4 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 20 May 2020 13:21:56 -0400
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:54928 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726436AbgETRVz (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 20 May 2020 13:21:55 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1589995312;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:in-reply-to:in-reply-to:references:references;
        bh=b1e72ai5xr6VO89iRvvb4B58/x2QU6V3gbbwzULbvm0=;
        b=W4NlzYjSrfol9r8VkKOU2w058S4Tt1CidaC1U7Voz/6Me1vQzhrfKV1mwQvALIo0aC6VGg
        0POkhmNJfsmWvoMWyhypq5UnMW/KLeKLqMdc1xUNPd3Db74D/UFNVz/rh65VmX9qlB67Cz
        nHpat+qtlxyTmQoVLTaPGrhKcT+9mco=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-501-RxVMZLUwO7mYFn4Ydjt2MA-1; Wed, 20 May 2020 13:21:50 -0400
X-MC-Unique: RxVMZLUwO7mYFn4Ydjt2MA-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 75004A0C00;
        Wed, 20 May 2020 17:21:49 +0000 (UTC)
Received: from virtlab511.virt.lab.eng.bos.redhat.com
 (virtlab511.virt.lab.eng.bos.redhat.com [10.19.152.198])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 3D7B582A33;
        Wed, 20 May 2020 17:21:48 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: vkuznets@redhat.com, Joerg Roedel <jroedel@suse.de>
Subject: [PATCH 03/24] KVM: nSVM: inject exceptions via
 svm_check_nested_events
Date: Wed, 20 May 2020 13:21:24 -0400
Message-Id: <20200520172145.23284-4-pbonzini@redhat.com>
In-Reply-To: <20200520172145.23284-1-pbonzini@redhat.com>
References: <20200520172145.23284-1-pbonzini@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This allows exceptions injected by the emulator to be properly delivered
as vmexits.  The code also becomes simpler, because we can just let all
L0-intercepted exceptions go through the usual path.  In particular, our
emulation of the VMX #DB exit qualification is very much simplified,
because the vmexit injection path can use kvm_deliver_exception_payload
to update DR6.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/svm/nested.c | 129 ++++++++++++++------------------------
 arch/x86/kvm/svm/svm.c    |   9 ---
 arch/x86/kvm/svm/svm.h    |   1 +
 3 files changed, 47 insertions(+), 92 deletions(-)

```
#### [PATCH 1/1] thunderbolt: add trivial .shutdown
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 11560981
Return-Path: <SRS0=QMHo=7C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DD30C912
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 20 May 2020 18:12:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C523B207D3
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 20 May 2020 18:12:59 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="hwDPHFVs"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726977AbgETSMz (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 20 May 2020 14:12:55 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:60170 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726933AbgETSMw (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 20 May 2020 14:12:52 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1589998371;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=xN2W+VHPdONngIsn/cmQXo9hulCtlz3Fu6VwpKF5hZ0=;
        b=hwDPHFVsb/7m6yYkBBXEUxdCTHgi37tQVC/O4Yhm/KpBdYqebLRR0Q+LcEuFw9jqRRGqlD
        U71azVvHf8p5QcfH+50e2LQgkn9+AjtuJVe7FJx8y/xUj9OkNAWLk/Dv92HRMMYmVUS1BV
        TFlEXah/GgOVgkl1jdzkmhGasjqXymg=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-314-AYBkFoVVNAixcRnr5zIGOA-1; Wed, 20 May 2020 14:12:48 -0400
X-MC-Unique: AYBkFoVVNAixcRnr5zIGOA-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id B9C56184C5C0;
        Wed, 20 May 2020 18:12:46 +0000 (UTC)
Received: from starship.redhat.com (unknown [10.35.207.28])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 652A510640E1;
        Wed, 20 May 2020 18:12:44 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: Michael Jamet <michael.jamet@intel.com>,
        Mika Westerberg <mika.westerberg@linux.intel.com>,
        Andreas Noever <andreas.noever@gmail.com>,
        linux-usb@vger.kernel.org (open list:THUNDERBOLT DRIVER),
        Yehezkel Bernat <YehezkelShB@gmail.com>,
        linux-kernel@vger.kernel.org (open list),
        Jiri Kosina <trivial@kernel.org>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH 1/1] thunderbolt: add trivial .shutdown
Date: Wed, 20 May 2020 21:12:40 +0300
Message-Id: <20200520181240.118559-2-mlevitsk@redhat.com>
In-Reply-To: <20200520181240.118559-1-mlevitsk@redhat.com>
References: <20200520181240.118559-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

On my machine, a kexec with this driver loaded in the old kernel
causes a very long delay on boot in the kexec'ed kernel,
most likely due to unclean shutdown prior to that.

Unloading thunderbolt driver prior to kexec allows kexec to work as fast
as regular kernel boot, as well as adding this .shutdown pointer.

Shutting a device prior to the shutdown completely is always
a good idea IMHO to help with kexec,
and this one-liner patch implements it.

Signed-off-by: Maxim Levitsky <mlevitsk@redhat.com>
---
 drivers/thunderbolt/nhi.c | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH v2 01/19] exec: Introduce ram_block_discard_(disable|require)()
##### From: David Hildenbrand <david@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Hildenbrand <david@redhat.com>
X-Patchwork-Id: 11560119
Return-Path: <SRS0=QMHo=7C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DD430159A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 20 May 2020 12:32:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C44A8207C4
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 20 May 2020 12:32:19 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="KhCGfFa5"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726720AbgETMcS (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 20 May 2020 08:32:18 -0400
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:49516 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726443AbgETMcR (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 20 May 2020 08:32:17 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1589977935;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=csTCzjprRmlnuhs1t5G0bRckObBhYBDq2SaPlfd5uBA=;
        b=KhCGfFa5V09nuYCWKfF5wJYFJmFwOABQ5wMUe6IQ7ai3EiQfm14C57yARXQcCKnpEdKI+W
        szqM530emPLjKiPQ29HwbDUhyXS1MrGOLZ8L9crqfKEwJb/8hcPl21bAvPiGj7NoRlBCid
        rM8bpCNSLPIxop+6pGYUGB9tBUThdms=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-404-RxSYxRzzPT-tNfKEDBm5TQ-1; Wed, 20 May 2020 08:32:11 -0400
X-MC-Unique: RxSYxRzzPT-tNfKEDBm5TQ-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 2E62A464;
        Wed, 20 May 2020 12:32:10 +0000 (UTC)
Received: from t480s.redhat.com (ovpn-113-76.ams2.redhat.com [10.36.113.76])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 4F1146EA21;
        Wed, 20 May 2020 12:32:08 +0000 (UTC)
From: David Hildenbrand <david@redhat.com>
To: qemu-devel@nongnu.org
Cc: kvm@vger.kernel.org, qemu-s390x@nongnu.org,
        Richard Henderson <rth@twiddle.net>,
        Paolo Bonzini <pbonzini@redhat.com>,
        "Dr . David Alan Gilbert" <dgilbert@redhat.com>,
        Eduardo Habkost <ehabkost@redhat.com>,
        "Michael S . Tsirkin" <mst@redhat.com>,
        David Hildenbrand <david@redhat.com>
Subject: [PATCH v2 01/19] exec: Introduce
 ram_block_discard_(disable|require)()
Date: Wed, 20 May 2020 14:31:34 +0200
Message-Id: <20200520123152.60527-2-david@redhat.com>
In-Reply-To: <20200520123152.60527-1-david@redhat.com>
References: <20200520123152.60527-1-david@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We want to replace qemu_balloon_inhibit() by something more generic.
Especially, we want to make sure that technologies that really rely on
RAM block discards to work reliably to run mutual exclusive with
technologies that effectively break it.

E.g., vfio will usually pin all guest memory, turning the virtio-balloon
basically useless and make the VM consume more memory than reported via
the balloon. While the balloon is special already (=> no guarantees, same
behavior possible afer reboots and with huge pages), this will be
different, especially, with virtio-mem.

Let's implement a way such that we can make both types of technology run
mutually exclusive. We'll convert existing balloon inhibitors in successive
patches and add some new ones. Add the check to
qemu_balloon_is_inhibited() for now. We might want to make
virtio-balloon an acutal inhibitor in the future - however, that
requires more thought to not break existing setups.

Reviewed-by: Dr. David Alan Gilbert <dgilbert@redhat.com>
Cc: "Michael S. Tsirkin" <mst@redhat.com>
Cc: Richard Henderson <rth@twiddle.net>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: David Hildenbrand <david@redhat.com>
---
 balloon.c             |  3 ++-
 exec.c                | 52 +++++++++++++++++++++++++++++++++++++++++++
 include/exec/memory.h | 41 ++++++++++++++++++++++++++++++++++
 3 files changed, 95 insertions(+), 1 deletion(-)

```
