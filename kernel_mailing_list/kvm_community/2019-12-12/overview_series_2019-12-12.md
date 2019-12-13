#### [PATCH 1/1] drivers/vhost : Removes unnecessary 'else' in vhost_copy_from_user
##### From: Leonardo Bras <leonardo@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Leonardo Bras <leonardo@linux.ibm.com>
X-Patchwork-Id: 11289411
Return-Path: <SRS0=BLLP=2C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2543C14DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Dec 2019 21:15:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 0D3992173E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Dec 2019 21:15:55 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731052AbfLLVPw (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 12 Dec 2019 16:15:52 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:60706 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1730971AbfLLVPv (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 12 Dec 2019 16:15:51 -0500
Received: from pps.filterd (m0098417.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 xBCL7Eno051267;
        Thu, 12 Dec 2019 16:15:49 -0500
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2wujxrppd5-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 12 Dec 2019 16:15:48 -0500
Received: from m0098417.ppops.net (m0098417.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id xBCL7YiG052047;
        Thu, 12 Dec 2019 16:15:48 -0500
Received: from ppma04dal.us.ibm.com (7a.29.35a9.ip4.static.sl-reverse.com
 [169.53.41.122])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2wujxrppcv-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 12 Dec 2019 16:15:48 -0500
Received: from pps.filterd (ppma04dal.us.ibm.com [127.0.0.1])
        by ppma04dal.us.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 xBCL9xOL012765;
        Thu, 12 Dec 2019 21:15:47 GMT
Received: from b03cxnp08027.gho.boulder.ibm.com
 (b03cxnp08027.gho.boulder.ibm.com [9.17.130.19])
        by ppma04dal.us.ibm.com with ESMTP id 2wr3q7dhy4-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 12 Dec 2019 21:15:47 +0000
Received: from b03ledav004.gho.boulder.ibm.com
 (b03ledav004.gho.boulder.ibm.com [9.17.130.235])
        by b03cxnp08027.gho.boulder.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id xBCLFka655836952
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 12 Dec 2019 21:15:46 GMT
Received: from b03ledav004.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 48A8678060;
        Thu, 12 Dec 2019 21:15:46 +0000 (GMT)
Received: from b03ledav004.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id C55197805E;
        Thu, 12 Dec 2019 21:15:44 +0000 (GMT)
Received: from LeoBras.aus.stglabs.ibm.com (unknown [9.18.235.137])
        by b03ledav004.gho.boulder.ibm.com (Postfix) with ESMTP;
        Thu, 12 Dec 2019 21:15:44 +0000 (GMT)
From: Leonardo Bras <leonardo@linux.ibm.com>
To: "Michael S. Tsirkin" <mst@redhat.com>,
        Jason Wang <jasowang@redhat.com>
Cc: Leonardo Bras <leonardo@linux.ibm.com>, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH 1/1] drivers/vhost : Removes unnecessary 'else' in
 vhost_copy_from_user
Date: Thu, 12 Dec 2019 18:15:39 -0300
Message-Id: <20191212211539.34578-1-leonardo@linux.ibm.com>
X-Mailer: git-send-email 2.23.0
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.95,18.0.572
 definitions=2019-12-12_07:2019-12-12,2019-12-12 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxscore=0 lowpriorityscore=0
 malwarescore=0 mlxlogscore=999 impostorscore=0 priorityscore=1501
 clxscore=1011 suspectscore=0 bulkscore=0 spamscore=0 adultscore=0
 phishscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-1910280000 definitions=main-1912120164
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

There is no need for this else statement, given that if block will return.
This change is not supposed to change the output binary.

It reduces identation level on most lines in this function, and also
fixes an split string on vq_err().

Signed-off-by: Leonardo Bras <leonardo@linux.ibm.com>
---
 drivers/vhost/vhost.c | 50 +++++++++++++++++++++----------------------
 1 file changed, 24 insertions(+), 26 deletions(-)

```
#### [PATCH 1/8] KVM: arm/arm64: Get rid of unused arg in cpu_init_hyp_mode()
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11288835
Return-Path: <SRS0=BLLP=2C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E5268930
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Dec 2019 17:28:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id BAF9E2173E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Dec 2019 17:28:52 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1576171732;
	bh=kmg0rQSL7xJ64epto9hwDxRrxjylqkolXY8MvpGANsg=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=VcJbgP9h6awFuryvj4C4QqvmNXaaY8qr/3bzd6CY6pvvnSO2/p7wmYChXOTVV7cyF
	 fbTtb6fJo/FlLGv6b7Gwa064RoKxOeuuPXioOes65WxrAKmuFgWTBiw4fl3/FrSQG9
	 9QpYziy0l4NbogsdTk+KFf07SZjR5hvRF9R51tVM=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730135AbfLLR2r (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 12 Dec 2019 12:28:47 -0500
Received: from inca-roads.misterjones.org ([213.251.177.50]:47938 "EHLO
        inca-roads.misterjones.org" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1730027AbfLLR2r (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 12 Dec 2019 12:28:47 -0500
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by cheepnis.misterjones.org with esmtpsa
 (TLSv1.2:DHE-RSA-AES128-GCM-SHA256:128)
        (Exim 4.80)
        (envelope-from <maz@kernel.org>)
        id 1ifSGV-00069s-HK; Thu, 12 Dec 2019 18:28:39 +0100
From: Marc Zyngier <maz@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>
Cc: Alexandru Elisei <alexandru.elisei@arm.com>,
        Ard Biesheuvel <ard.biesheuvel@linaro.org>,
        Christoffer Dall <christoffer.dall@arm.com>,
        Eric Auger <eric.auger@redhat.com>,
        James Morse <james.morse@arm.com>, Jia He <justin.he@arm.com>,
        Mark Rutland <mark.rutland@arm.com>,
        Miaohe Lin <linmiaohe@huawei.com>,
        Steven Price <steven.price@arm.com>,
        Will Deacon <will@kernel.org>, kvm@vger.kernel.org,
        kvmarm@lists.cs.columbia.edu, linux-arm-kernel@lists.infradead.org,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>
Subject: [PATCH 1/8] KVM: arm/arm64: Get rid of unused arg in
 cpu_init_hyp_mode()
Date: Thu, 12 Dec 2019 17:28:17 +0000
Message-Id: <20191212172824.11523-2-maz@kernel.org>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20191212172824.11523-1-maz@kernel.org>
References: <20191212172824.11523-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: pbonzini@redhat.com, rkrcmar@redhat.com,
 alexandru.elisei@arm.com, ard.biesheuvel@linaro.org,
 christoffer.dall@arm.com, eric.auger@redhat.com, james.morse@arm.com,
 justin.he@arm.com, mark.rutland@arm.com, linmiaohe@huawei.com,
 steven.price@arm.com, will@kernel.org, kvm@vger.kernel.org,
 kvmarm@lists.cs.columbia.edu, linux-arm-kernel@lists.infradead.org,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on cheepnis.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Miaohe Lin <linmiaohe@huawei.com>

As arg dummy is not really needed, there's no need to pass
NULL when calling cpu_init_hyp_mode(). So clean it up.

Fixes: 67f691976662 ("arm64: kvm: allows kvm cpu hotplug")
Reviewed-by: Steven Price <steven.price@arm.com>
Signed-off-by: Miaohe Lin <linmiaohe@huawei.com>
Signed-off-by: Marc Zyngier <maz@kernel.org>
Link: https://lore.kernel.org/r/1574320559-5662-1-git-send-email-linmiaohe@huawei.com
---
 virt/kvm/arm/arm.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH v2 1/4] KVM: VMX: Fix some typos and out-dated function names in comments
##### From: linmiaohe <linmiaohe@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: linmiaohe <linmiaohe@huawei.com>
X-Patchwork-Id: 11287167
Return-Path: <SRS0=BLLP=2C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C181E14B7
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Dec 2019 08:19:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A7BB322527
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Dec 2019 08:19:15 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728207AbfLLITO (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 12 Dec 2019 03:19:14 -0500
Received: from szxga05-in.huawei.com ([45.249.212.191]:7222 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1728201AbfLLITO (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 12 Dec 2019 03:19:14 -0500
Received: from DGGEMS407-HUB.china.huawei.com (unknown [172.30.72.59])
        by Forcepoint Email with ESMTP id 077BD20775CFDA10E796;
        Thu, 12 Dec 2019 16:19:12 +0800 (CST)
Received: from huawei.com (10.175.105.18) by DGGEMS407-HUB.china.huawei.com
 (10.3.19.207) with Microsoft SMTP Server id 14.3.439.0; Thu, 12 Dec 2019
 16:19:03 +0800
From: linmiaohe <linmiaohe@huawei.com>
To: <pbonzini@redhat.com>, <rkrcmar@redhat.com>,
        <sean.j.christopherson@intel.com>, <vkuznets@redhat.com>,
        <wanpengli@tencent.com>, <jmattson@google.com>, <joro@8bytes.org>,
        <tglx@linutronix.de>, <mingo@redhat.com>, <bp@alien8.de>,
        <hpa@zytor.com>
CC: <linmiaohe@huawei.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <x86@kernel.org>
Subject: [PATCH v2 1/4] KVM: VMX: Fix some typos and out-dated function names
 in comments
Date: Thu, 12 Dec 2019 16:18:35 +0800
Message-ID: <1576138718-32728-2-git-send-email-linmiaohe@huawei.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1576138718-32728-1-git-send-email-linmiaohe@huawei.com>
References: <1576138718-32728-1-git-send-email-linmiaohe@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.175.105.18]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Miaohe Lin <linmiaohe@huawei.com>

Fix some comment typos and out-dated function names in comments. Since
commit b1346ab2afbe ("KVM: nVMX: Rename prepare_vmcs02_*_full to
prepare_vmcs02_*_rare"), prepare_vmcs02_full has been renamed to
prepare_vmcs02_rare.
nested_vmx_merge_msr_bitmap is renamed to nested_vmx_prepare_msr_bitmap
since commit c992384bde84 ("KVM: vmx: speed up MSR bitmap merge").

Signed-off-by: Miaohe Lin <linmiaohe@huawei.com>
---
 arch/x86/kvm/vmx/nested.c             | 2 +-
 arch/x86/kvm/vmx/vmcs_shadow_fields.h | 4 ++--
 arch/x86/kvm/vmx/vmx.c                | 8 ++++----
 3 files changed, 7 insertions(+), 7 deletions(-)

```
#### [GIT PULL] KVM/arm updates for 5.5-rc2
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11288825
Return-Path: <SRS0=BLLP=2C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 01267930
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Dec 2019 17:28:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D3C6A21655
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Dec 2019 17:28:46 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1576171726;
	bh=0roBPlynw4jnuonJ/JquYdPLTDJvfgme7qmhIJPnfZ0=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=xlaXBcvP9gHXDLhKukEWZZ1ctxXe5lTdOQOY9FF2pCyag53JdNuEViGXyYftag6V8
	 pZF3lv+DBPe5qdurEEN29qYAzjMe7G2Kn0xwpWpa406aPdWi01zXoygvMNa8l8GqPO
	 gJ6Q28FLw5rHuTjh19fR/mokAtB7PqZYG84d/BMY=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730096AbfLLR2p (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 12 Dec 2019 12:28:45 -0500
Received: from inca-roads.misterjones.org ([213.251.177.50]:53578 "EHLO
        inca-roads.misterjones.org" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1730023AbfLLR2p (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 12 Dec 2019 12:28:45 -0500
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by cheepnis.misterjones.org with esmtpsa
 (TLSv1.2:DHE-RSA-AES128-GCM-SHA256:128)
        (Exim 4.80)
        (envelope-from <maz@kernel.org>)
        id 1ifSGU-00069s-N1; Thu, 12 Dec 2019 18:28:38 +0100
From: Marc Zyngier <maz@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>
Cc: Alexandru Elisei <alexandru.elisei@arm.com>,
        Ard Biesheuvel <ard.biesheuvel@linaro.org>,
        Christoffer Dall <christoffer.dall@arm.com>,
        Eric Auger <eric.auger@redhat.com>,
        James Morse <james.morse@arm.com>, Jia He <justin.he@arm.com>,
        Mark Rutland <mark.rutland@arm.com>,
        Miaohe Lin <linmiaohe@huawei.com>,
        Steven Price <steven.price@arm.com>,
        Will Deacon <will@kernel.org>, kvm@vger.kernel.org,
        kvmarm@lists.cs.columbia.edu, linux-arm-kernel@lists.infradead.org,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>
Subject: [GIT PULL] KVM/arm updates for 5.5-rc2
Date: Thu, 12 Dec 2019 17:28:16 +0000
Message-Id: <20191212172824.11523-1-maz@kernel.org>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: pbonzini@redhat.com, rkrcmar@redhat.com,
 alexandru.elisei@arm.com, ard.biesheuvel@linaro.org,
 christoffer.dall@arm.com, eric.auger@redhat.com, james.morse@arm.com,
 justin.he@arm.com, mark.rutland@arm.com, linmiaohe@huawei.com,
 steven.price@arm.com, will@kernel.org, kvm@vger.kernel.org,
 kvmarm@lists.cs.columbia.edu, linux-arm-kernel@lists.infradead.org,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on cheepnis.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Paolo, Radim,

This is the first set of fixes for 5.5-rc2. This time around,
a couple of MM fixes, a ONE_REG fix for an issue detected by
GCC-10, and a handful of cleanups.

Please pull,

	M.

The following changes since commit cd7056ae34af0e9424da97bbc7d2b38246ba8a2c:

  Merge remote-tracking branch 'kvmarm/misc-5.5' into kvmarm/next (2019-11-08 11:27:29 +0000)

are available in the Git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/kvmarm/kvmarm.git tags/kvmarm-fixes-5.5-1

for you to fetch changes up to 6d674e28f642e3ff676fbae2d8d1b872814d32b6:

  KVM: arm/arm64: Properly handle faulting of device mappings (2019-12-12 16:22:40 +0000)

----------------------------------------------------------------
KVM/arm fixes for .5.5, take #1

- Fix uninitialised sysreg accessor
- Fix handling of demand-paged device mappings
- Stop spamming the console on IMPDEF sysregs
- Relax mappings of writable memslots
- Assorted cleanups

----------------------------------------------------------------
Jia He (1):
      KVM: arm/arm64: Remove excessive permission check in kvm_arch_prepare_memory_region

Marc Zyngier (1):
      KVM: arm/arm64: Properly handle faulting of device mappings

Mark Rutland (2):
      KVM: arm64: Sanely ratelimit sysreg messages
      KVM: arm64: Don't log IMP DEF sysreg traps

Miaohe Lin (3):
      KVM: arm/arm64: Get rid of unused arg in cpu_init_hyp_mode()
      KVM: arm/arm64: vgic: Fix potential double free dist->spis in __kvm_vgic_destroy()
      KVM: arm/arm64: vgic: Use wrapper function to lock/unlock all vcpus in kvm_vgic_create()

Will Deacon (1):
      KVM: arm64: Ensure 'params' is initialised when looking up sys register

 arch/arm64/kvm/sys_regs.c     | 25 ++++++++++++++++++-------
 arch/arm64/kvm/sys_regs.h     | 17 +++++++++++++++--
 virt/kvm/arm/arm.c            |  4 ++--
 virt/kvm/arm/mmu.c            | 30 +++++++++++++++++-------------
 virt/kvm/arm/vgic/vgic-init.c | 20 +++++---------------
 5 files changed, 57 insertions(+), 39 deletions(-)

From patchwork Thu Dec 12 17:28:18 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11288829
Return-Path: <SRS0=BLLP=2C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B155614DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Dec 2019 17:28:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 867B622527
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Dec 2019 17:28:48 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1576171728;
	bh=WeO50GO26ahSqAUrie6ZZrDKCP53iPgbXi9HLO/HVYA=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=yvAV7M4A3V7cY7o3/Diq0kNhjfNv06NX4FtUDyZIZHQor9oZAvxw7GAzOE0A7W24A
	 cEuCd8Mw4TOCtyDvJxHxqVYCJj+ecXyK79rRjJU/9iTN9rFn3CAYHvV1zjcXtEO79o
	 e4wANz8NwdbVrkSpS40m2kbWWzddRAQGc3xY0dzc=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730148AbfLLR2s (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 12 Dec 2019 12:28:48 -0500
Received: from inca-roads.misterjones.org ([213.251.177.50]:59844 "EHLO
        inca-roads.misterjones.org" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1730100AbfLLR2r (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 12 Dec 2019 12:28:47 -0500
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by cheepnis.misterjones.org with esmtpsa
 (TLSv1.2:DHE-RSA-AES128-GCM-SHA256:128)
        (Exim 4.80)
        (envelope-from <maz@kernel.org>)
        id 1ifSGW-00069s-Cp; Thu, 12 Dec 2019 18:28:40 +0100
From: Marc Zyngier <maz@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>
Cc: Alexandru Elisei <alexandru.elisei@arm.com>,
        Ard Biesheuvel <ard.biesheuvel@linaro.org>,
        Christoffer Dall <christoffer.dall@arm.com>,
        Eric Auger <eric.auger@redhat.com>,
        James Morse <james.morse@arm.com>, Jia He <justin.he@arm.com>,
        Mark Rutland <mark.rutland@arm.com>,
        Miaohe Lin <linmiaohe@huawei.com>,
        Steven Price <steven.price@arm.com>,
        Will Deacon <will@kernel.org>, kvm@vger.kernel.org,
        kvmarm@lists.cs.columbia.edu, linux-arm-kernel@lists.infradead.org,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>
Subject: [PATCH 2/8] KVM: arm/arm64: vgic: Fix potential double free
 dist->spis in __kvm_vgic_destroy()
Date: Thu, 12 Dec 2019 17:28:18 +0000
Message-Id: <20191212172824.11523-3-maz@kernel.org>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20191212172824.11523-1-maz@kernel.org>
References: <20191212172824.11523-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: pbonzini@redhat.com, rkrcmar@redhat.com,
 alexandru.elisei@arm.com, ard.biesheuvel@linaro.org,
 christoffer.dall@arm.com, eric.auger@redhat.com, james.morse@arm.com,
 justin.he@arm.com, mark.rutland@arm.com, linmiaohe@huawei.com,
 steven.price@arm.com, will@kernel.org, kvm@vger.kernel.org,
 kvmarm@lists.cs.columbia.edu, linux-arm-kernel@lists.infradead.org,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on cheepnis.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Miaohe Lin <linmiaohe@huawei.com>

In kvm_vgic_dist_init() called from kvm_vgic_map_resources(), if
dist->vgic_model is invalid, dist->spis will be freed without set
dist->spis = NULL. And in vgicv2 resources clean up path,
__kvm_vgic_destroy() will be called to free allocated resources.
And dist->spis will be freed again in clean up chain because we
forget to set dist->spis = NULL in kvm_vgic_dist_init() failed
path. So double free would happen.

Signed-off-by: Miaohe Lin <linmiaohe@huawei.com>
Signed-off-by: Marc Zyngier <maz@kernel.org>
Reviewed-by: Eric Auger <eric.auger@redhat.com>
Link: https://lore.kernel.org/r/1574923128-19956-1-git-send-email-linmiaohe@huawei.com
---
 virt/kvm/arm/vgic/vgic-init.c | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH v5 1/2] mm: make dev_pagemap_mapping_shift() externally visible
##### From: Barret Rhoden <brho@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Barret Rhoden <brho@google.com>
X-Patchwork-Id: 11289013
Return-Path: <SRS0=BLLP=2C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 74F2C112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Dec 2019 18:23:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 538AC2253D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Dec 2019 18:23:07 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="MAdkof8C"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730375AbfLLSW6 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 12 Dec 2019 13:22:58 -0500
Received: from mail-pj1-f73.google.com ([209.85.216.73]:55779 "EHLO
        mail-pj1-f73.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1730357AbfLLSW6 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 12 Dec 2019 13:22:58 -0500
Received: by mail-pj1-f73.google.com with SMTP id e7so1569542pjt.22
        for <kvm@vger.kernel.org>; Thu, 12 Dec 2019 10:22:57 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=IvHeRx1oBCh9J6TLvVWdv2Gb1z0rpMzGcWyY+BXVgxo=;
        b=MAdkof8C2KW30AALfnNJO3vr9VoF0vmBXanMXL/vR51qGyvIZkGihOmBNe+C0or/8I
         NpO/KCC3oEKNcwp7NIyw7WnD6H+rCsDvTI30S8NWdXPxMl0MDaFljsm9JXiaxGx8tZCO
         d4KLSyqgiZeCGiJqkepl0hPb47CUKa9ToIY3jibKjBu4kZUmg7uhITO9RyP7k+b0KyoU
         zEcEs3lkMbzHsbNJ2xA4Mv3lS6SzC0mJbsHZ2qOxVL621b4e0Gt/qvA+mGVTzX9rJKB5
         /8rQMuMbnVTaGER/Xvhr4PwqP6nQELiDlJ6qv20w9iVMpmIsQeJffxIkfXKhEXwrX/ah
         Gvjg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=IvHeRx1oBCh9J6TLvVWdv2Gb1z0rpMzGcWyY+BXVgxo=;
        b=CRlcwjzyuxnYTKBv8V5C5V/Dm50ScEglei+cW1LSsvvpDu4602Xuj9V+JiyEnMRMCT
         x74OQK20tsd0iEpMiIpZxkL4ki1V3ae71+COeXav9XzLKR49XwpdDHrVbzmy+C9YsrjL
         +rjGMEd7J5nU+mSmLIV2E3qH384Gt1E3V2uYI4bWoo32lwWk/wyvSB0/OHTbcgTkmfvr
         rpDfiXG/Aii4sUp4UGTrknCRH5vzmIOi1LpGMm1080Fjo6KHuEb3yaJdkBCTu+uKfhHe
         XWrbfEGpeGtM9VVNjQ37M++gq7YYEL/RmCVsBBjzyb91VayI99vLARRWu4vc68L3SMV8
         rvqw==
X-Gm-Message-State: APjAAAWluXfFFUI2C8d8d0imH+XlZ5IEzxjECwTds0aJ/Yzqudgvw35R
        v6cVWmDkcHkMq+IdPpBR7G4b6orY
X-Google-Smtp-Source: 
 APXvYqwVXoFFdqVc4oFKrnkNNIY1YlbI3lRBL8mXjnVcsOoBTjQ2NnV0mup2jeDoJ+6bSYWUQLoZOkJ/
X-Received: by 2002:a63:a508:: with SMTP id n8mr11683668pgf.278.1576174977297;
 Thu, 12 Dec 2019 10:22:57 -0800 (PST)
Date: Thu, 12 Dec 2019 13:22:37 -0500
In-Reply-To: <20191212182238.46535-1-brho@google.com>
Message-Id: <20191212182238.46535-2-brho@google.com>
Mime-Version: 1.0
References: <20191212182238.46535-1-brho@google.com>
X-Mailer: git-send-email 2.24.1.735.g03f4e72817-goog
Subject: [PATCH v5 1/2] mm: make dev_pagemap_mapping_shift() externally
 visible
From: Barret Rhoden <brho@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Dan Williams <dan.j.williams@intel.com>,
        David Hildenbrand <david@redhat.com>,
        Dave Jiang <dave.jiang@intel.com>,
        Alexander Duyck <alexander.h.duyck@linux.intel.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>
Cc: linux-nvdimm@lists.01.org, x86@kernel.org, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, jason.zeng@intel.com
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

KVM has a use case for determining the size of a dax mapping.

The KVM code has easy access to the address and the mm, and
dev_pagemap_mapping_shift() needs only those parameters.  It was
deriving them from page and vma.  This commit changes those parameters
from (page, vma) to (address, mm).

Signed-off-by: Barret Rhoden <brho@google.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Acked-by: Dan Williams <dan.j.williams@intel.com>
---
 include/linux/mm.h  |  3 +++
 mm/memory-failure.c | 38 +++-----------------------------------
 mm/util.c           | 34 ++++++++++++++++++++++++++++++++++
 3 files changed, 40 insertions(+), 35 deletions(-)

```
#### [PATCH v10 01/25] mm/gup: factor out duplicate code from four routines
##### From: John Hubbard <jhubbard@nvidia.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: John Hubbard <jhubbard@nvidia.com>
X-Patchwork-Id: 11287529
Return-Path: <SRS0=BLLP=2C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 70CB114BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Dec 2019 08:23:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 439D922B48
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Dec 2019 08:23:11 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=nvidia.com header.i=@nvidia.com
 header.b="eFoJLZ09"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728317AbfLLITX (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 12 Dec 2019 03:19:23 -0500
Received: from hqnvemgate25.nvidia.com ([216.228.121.64]:8506 "EHLO
        hqnvemgate25.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728304AbfLLITW (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 12 Dec 2019 03:19:22 -0500
Received: from hqpgpgate101.nvidia.com (Not Verified[216.228.121.13]) by
 hqnvemgate25.nvidia.com (using TLS: TLSv1.2, DES-CBC3-SHA)
        id <B5df1f8000000>; Thu, 12 Dec 2019 00:19:14 -0800
Received: from hqmail.nvidia.com ([172.20.161.6])
  by hqpgpgate101.nvidia.com (PGP Universal service);
  Thu, 12 Dec 2019 00:19:21 -0800
X-PGP-Universal: processed;
        by hqpgpgate101.nvidia.com on Thu, 12 Dec 2019 00:19:21 -0800
Received: from HQMAIL107.nvidia.com (172.20.187.13) by HQMAIL105.nvidia.com
 (172.20.187.12) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Thu, 12 Dec
 2019 08:19:18 +0000
Received: from hqnvemgw03.nvidia.com (10.124.88.68) by HQMAIL107.nvidia.com
 (172.20.187.13) with Microsoft SMTP Server (TLS) id 15.0.1473.3 via Frontend
 Transport; Thu, 12 Dec 2019 08:19:18 +0000
Received: from blueforge.nvidia.com (Not Verified[10.110.48.28]) by
 hqnvemgw03.nvidia.com with Trustwave SEG (v7,5,8,10121)
        id <B5df1f8060002>; Thu, 12 Dec 2019 00:19:18 -0800
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
 Christoph Hellwig <hch@lst.de>,
 "Aneesh Kumar K . V" <aneesh.kumar@linux.ibm.com>
Subject: [PATCH v10 01/25] mm/gup: factor out duplicate code from four
 routines
Date: Thu, 12 Dec 2019 00:18:53 -0800
Message-ID: <20191212081917.1264184-2-jhubbard@nvidia.com>
X-Mailer: git-send-email 2.24.0
In-Reply-To: <20191212081917.1264184-1-jhubbard@nvidia.com>
References: <20191212081917.1264184-1-jhubbard@nvidia.com>
MIME-Version: 1.0
X-NVConfidentiality: public
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1576138754; bh=NjEUDVUY50BsRhke7z2S9TxhDwSe8KFPL35zO7aJjtI=;
        h=X-PGP-Universal:From:To:CC:Subject:Date:Message-ID:X-Mailer:
         In-Reply-To:References:MIME-Version:X-NVConfidentiality:
         Content-Type:Content-Transfer-Encoding;
        b=eFoJLZ094H96VEw0VZgoT9vY9t8XJ6NaXBjIsxip9K649lfdEn/ehXVDoLK9SlQkD
         RyOdKG0XsitgjGVAO+jZJ6f5YATGR6f+qRZQ5RNBPxs9uD5H0Yqv3a1TPRx3nck2AY
         +LcFM2Cp9I3lHAX62B2OT04NIfdIhzEMy7EuFgIzMfLv71VoZZzbeWiefw0OnELqhp
         zdeHTzZe1ZQtecRfLfhH+fXQP2LTjs52RlYm9LVOwnED6782E4fHDqhVmIRKUTpDTR
         8WXsicsI67F2F6YDOcQfqMJxTAOSyrNidx2obEbqCZpcY7FuguL2uHwUoJyDzaKobz
         1qlwE2jYi0Ryw==
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

There are four locations in gup.c that have a fair amount of code
duplication. This means that changing one requires making the same
changes in four places, not to mention reading the same code four
times, and wondering if there are subtle differences.

Factor out the common code into static functions, thus reducing the
overall line count and the code's complexity.

Also, take the opportunity to slightly improve the efficiency of the
error cases, by doing a mass subtraction of the refcount, surrounded
by get_page()/put_page().

Also, further simplify (slightly), by waiting until the the successful
end of each routine, to increment *nr.

Reviewed-by: Christoph Hellwig <hch@lst.de>
Reviewed-by: Jérôme Glisse <jglisse@redhat.com>
Reviewed-by: Jan Kara <jack@suse.cz>
Cc: Ira Weiny <ira.weiny@intel.com>
Cc: Christoph Hellwig <hch@lst.de>
Cc: Aneesh Kumar K.V <aneesh.kumar@linux.ibm.com>
Signed-off-by: John Hubbard <jhubbard@nvidia.com>
---
 mm/gup.c | 91 ++++++++++++++++++++++----------------------------------
 1 file changed, 36 insertions(+), 55 deletions(-)

```
#### [PATCH 1/3] kvm/mips: Standardize kvm exit reason field
##### From: Gavin Shan <gshan@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Gavin Shan <gshan@redhat.com>
X-Patchwork-Id: 11286801
Return-Path: <SRS0=BLLP=2C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 02F466C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Dec 2019 02:45:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id CBEF521655
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Dec 2019 02:45:31 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="KDRzkLEh"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727882AbfLLCpb (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 11 Dec 2019 21:45:31 -0500
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:60788 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727879AbfLLCpa (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 11 Dec 2019 21:45:30 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1576118729;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=vVBnTdpElxP7oPw8MW4U3TzLCcSf5UiwUt7vzIeW4ps=;
        b=KDRzkLEhJj0gaQt9UdggpFq4eXkoZaPWQl/rrfiphS+g6gBsXpC/Jhx7GagDAyFzxit9CW
        FG1HWoMgbCTsmTd2UkwRvwPGy9qCGkoQFF5QpB4tpr9FTVGWpbe+Ts2l+lH5ImeLBBzwQQ
        MFYNS/SV9zMPqL3tNssOUMA6hLC6PEc=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-282-G0VUWj9PM5qw6TyRw48vBw-1; Wed, 11 Dec 2019 21:45:28 -0500
X-MC-Unique: G0VUWj9PM5qw6TyRw48vBw-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 8142F800D4C;
        Thu, 12 Dec 2019 02:45:27 +0000 (UTC)
Received: from localhost.localdomain.com (vpn2-54-40.bne.redhat.com
 [10.64.54.40])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 699A46609A;
        Thu, 12 Dec 2019 02:45:24 +0000 (UTC)
From: Gavin Shan <gshan@redhat.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, rkrcmar@redhat.com, paulus@ozlabs.org,
        maz@kernel.org, jhogan@kernel.org, drjones@redhat.com,
        vkuznets@redhat.com, gshan@redhat.com
Subject: [PATCH 1/3] kvm/mips: Standardize kvm exit reason field
Date: Thu, 12 Dec 2019 13:45:10 +1100
Message-Id: <20191212024512.39930-2-gshan@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This standardizes kvm exit reason field name by replacing "reason"
with "exit_reason".

Signed-off-by: Gavin Shan <gshan@redhat.com>
---
 arch/mips/kvm/trace.h | 10 +++++-----
 1 file changed, 5 insertions(+), 5 deletions(-)

```
#### [PATCH v2] kvm: Refactor handling of VM debugfs files
##### From: Milan Pandurov <milanpa@amazon.de>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Milan Pandurov <milanpa@amazon.de>
X-Patchwork-Id: 11287673
Return-Path: <SRS0=BLLP=2C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 285A5930
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Dec 2019 09:22:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E34612173E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Dec 2019 09:22:36 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amazon.de header.i=@amazon.de
 header.b="VvTbL0jz"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728292AbfLLJWg (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 12 Dec 2019 04:22:36 -0500
Received: from smtp-fw-9101.amazon.com ([207.171.184.25]:41292 "EHLO
        smtp-fw-9101.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728198AbfLLJWf (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 12 Dec 2019 04:22:35 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.de; i=@amazon.de; q=dns/txt; s=amazon201209;
  t=1576142553; x=1607678553;
  h=from:to:cc:subject:date:message-id:mime-version;
  bh=fru1UTtKpWklPq7GP/CN+tcnqTg8cl3eG/v+tI/5mx0=;
  b=VvTbL0jzF1xXVK2m2C3zwg7FQkVpOFhAYJFJ3rM/6FgjALOJkQyzi0Za
   IdjtcZ1lYdzLOYREgAvycxAfAP4rJjn9dD36c7uA8/j61izFwponOhaA+
   K15Njg2BWkUYiaTYPCqqO8QuH/Xm9NOtZhEs0mlANJcVui/Yt6BQh7Z2v
   0=;
IronPort-SDR: 
 hpLlQrMHQIBekeF9SJIAiqTu72m09Mwci+nNWzTr48UTn6rYMaMTOL/I4OdkTjFJ6W/B6kSbut
 ig6OEQdmuqTQ==
X-IronPort-AV: E=Sophos;i="5.69,305,1571702400";
   d="scan'208";a="4695259"
Received: from sea32-co-svc-lb4-vlan3.sea.corp.amazon.com (HELO
 email-inbound-relay-1a-7d76a15f.us-east-1.amazon.com) ([10.47.23.38])
  by smtp-border-fw-out-9101.sea19.amazon.com with ESMTP;
 12 Dec 2019 09:22:22 +0000
Received: from EX13MTAUEA001.ant.amazon.com
 (iad55-ws-svc-p15-lb9-vlan2.iad.amazon.com [10.40.159.162])
        by email-inbound-relay-1a-7d76a15f.us-east-1.amazon.com (Postfix) with
 ESMTPS id 915AEA36DD;
        Thu, 12 Dec 2019 09:22:20 +0000 (UTC)
Received: from EX13D27EUB004.ant.amazon.com (10.43.166.152) by
 EX13MTAUEA001.ant.amazon.com (10.43.61.243) with Microsoft SMTP Server (TLS)
 id 15.0.1367.3; Thu, 12 Dec 2019 09:22:20 +0000
Received: from uc3ce012741425f.ant.amazon.com (10.43.160.109) by
 EX13D27EUB004.ant.amazon.com (10.43.166.152) with Microsoft SMTP Server (TLS)
 id 15.0.1367.3; Thu, 12 Dec 2019 09:22:16 +0000
From: Milan Pandurov <milanpa@amazon.de>
To: <kvm@vger.kernel.org>
CC: <pbonzini@redhat.com>, <rkrcmar@redhat.com>, <graf@amazon.de>,
        <borntraeger@de.ibm.com>
Subject: [PATCH v2] kvm: Refactor handling of VM debugfs files
Date: Thu, 12 Dec 2019 10:22:06 +0100
Message-ID: <20191212092206.7732-1-milanpa@amazon.de>
X-Mailer: git-send-email 2.17.1
MIME-Version: 1.0
X-Originating-IP: [10.43.160.109]
X-ClientProxiedBy: EX13D17UWB001.ant.amazon.com (10.43.161.252) To
 EX13D27EUB004.ant.amazon.com (10.43.166.152)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We can store reference to kvm_stats_debugfs_item instead of copying
its values to kvm_stat_data.
This allows us to remove duplicated code and usage of temporary
kvm_stat_data inside vm_stat_get et al.

Signed-off-by: Milan Pandurov <milanpa@amazon.de>
---
v1 -> v2:
 - fix compile issues
 - address comments
---
 include/linux/kvm_host.h |   7 +-
 virt/kvm/kvm_main.c      | 154 +++++++++++++++++++++------------------
 2 files changed, 90 insertions(+), 71 deletions(-)

```
#### [PATCH v3] kvm: Refactor handling of VM debugfs files
##### From: Milan Pandurov <milanpa@amazon.de>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Milan Pandurov <milanpa@amazon.de>
X-Patchwork-Id: 11287807
Return-Path: <SRS0=BLLP=2C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0FCDA6C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Dec 2019 10:14:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D4BBB206A5
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Dec 2019 10:14:14 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amazon.de header.i=@amazon.de
 header.b="Fq8AD3IT"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728479AbfLLKON (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 12 Dec 2019 05:14:13 -0500
Received: from smtp-fw-6001.amazon.com ([52.95.48.154]:53555 "EHLO
        smtp-fw-6001.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726382AbfLLKON (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 12 Dec 2019 05:14:13 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.de; i=@amazon.de; q=dns/txt; s=amazon201209;
  t=1576145651; x=1607681651;
  h=from:to:cc:subject:date:message-id:mime-version;
  bh=3CdN7B3OL+RgefY+UyCMKfOdrs7aVA3TRckY7HsudyI=;
  b=Fq8AD3ITxuShXkLh8GTep7QrEc33gffNjGI8kq1CD8Wp9x1gOR5t/gG4
   M+toIBA9n5/chR5QcLbDnrBmCghqFbXhM6uB1giKa/z9ep8OqIriFR/9/
   FJR8xmRC0e9G2OSrUUW71qgfPySKUcUAPcF7sRhxd5MvWMw/qIGB0Rju7
   Q=;
IronPort-SDR: 
 VW7ktYHVcz1FJgA2L5nAEx5PKDUousErMkwKCDt8zYtnYwt90hE2glim80/yHLDFLr9oOuGtLY
 WXUSNb1sSaLQ==
X-IronPort-AV: E=Sophos;i="5.69,305,1571702400";
   d="scan'208";a="8766919"
Received: from iad6-co-svc-p1-lb1-vlan3.amazon.com (HELO
 email-inbound-relay-1e-57e1d233.us-east-1.amazon.com) ([10.124.125.6])
  by smtp-border-fw-out-6001.iad6.amazon.com with ESMTP;
 12 Dec 2019 10:14:10 +0000
Received: from EX13MTAUEA001.ant.amazon.com
 (iad55-ws-svc-p15-lb9-vlan3.iad.amazon.com [10.40.159.166])
        by email-inbound-relay-1e-57e1d233.us-east-1.amazon.com (Postfix) with
 ESMTPS id 276EB14180D;
        Thu, 12 Dec 2019 10:14:08 +0000 (UTC)
Received: from EX13D27EUB004.ant.amazon.com (10.43.166.152) by
 EX13MTAUEA001.ant.amazon.com (10.43.61.243) with Microsoft SMTP Server (TLS)
 id 15.0.1367.3; Thu, 12 Dec 2019 10:14:07 +0000
Received: from uc3ce012741425f.ant.amazon.com (10.43.161.179) by
 EX13D27EUB004.ant.amazon.com (10.43.166.152) with Microsoft SMTP Server (TLS)
 id 15.0.1367.3; Thu, 12 Dec 2019 10:14:04 +0000
From: Milan Pandurov <milanpa@amazon.de>
To: <kvm@vger.kernel.org>
CC: <pbonzini@redhat.com>, <rkrcmar@redhat.com>, <graf@amazon.de>,
        <borntraeger@de.ibm.com>
Subject: [PATCH v3] kvm: Refactor handling of VM debugfs files
Date: Thu, 12 Dec 2019 11:13:54 +0100
Message-ID: <20191212101354.22614-1-milanpa@amazon.de>
X-Mailer: git-send-email 2.17.1
MIME-Version: 1.0
X-Originating-IP: [10.43.161.179]
X-ClientProxiedBy: EX13D33UWC001.ant.amazon.com (10.43.162.185) To
 EX13D27EUB004.ant.amazon.com (10.43.166.152)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We can store reference to kvm_stats_debugfs_item instead of copying
its values to kvm_stat_data.
This allows us to remove duplicated code and usage of temporary
kvm_stat_data inside vm_stat_get et al.

Signed-off-by: Milan Pandurov <milanpa@amazon.de>
---
v1 -> v2:
 - fix compile issues
 - address comments

v2 -> v3:
 - address comments
---
 include/linux/kvm_host.h |   7 +-
 virt/kvm/kvm_main.c      | 142 +++++++++++++++++++--------------------
 2 files changed, 76 insertions(+), 73 deletions(-)

```
#### [PATCH v4] kvm: Refactor handling of VM debugfs files
##### From: Milan Pandurov <milanpa@amazon.de>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Milan Pandurov <milanpa@amazon.de>
X-Patchwork-Id: 11288457
Return-Path: <SRS0=BLLP=2C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 204E26C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Dec 2019 14:13:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id DCE43214AF
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Dec 2019 14:13:07 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amazon.de header.i=@amazon.de
 header.b="pqHAih/2"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729568AbfLLONG (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 12 Dec 2019 09:13:06 -0500
Received: from smtp-fw-9102.amazon.com ([207.171.184.29]:30583 "EHLO
        smtp-fw-9102.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729392AbfLLONG (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 12 Dec 2019 09:13:06 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.de; i=@amazon.de; q=dns/txt; s=amazon201209;
  t=1576159984; x=1607695984;
  h=from:to:cc:subject:date:message-id:mime-version;
  bh=VnXQ/si/PddmaiLs9SIOVqc3GYuruP9Nne1F7PseBys=;
  b=pqHAih/214RSYut+ToaZTj70YmmhEyiEdAmsA961SDi23Nyl2HU1uMrV
   +E0lmhPVViSMc4FaS/KXw1huENuIijunGpEvLGze6WsL7B8p84EBvT9Sv
   aOaTXGry6Eq65TH4z+7q3WLVqCHDsDpWXdFCFOoDMjyIHLGMiRa2Obio3
   k=;
IronPort-SDR: 
 sVSq0e3UkGRwoYoS2r1ozjmorsPv47o8gnqqR7aV+1Pl1H19rEemIZhxr8ay/Qb27gv0X5NbFq
 wsmN/3gbmeyA==
X-IronPort-AV: E=Sophos;i="5.69,306,1571702400";
   d="scan'208";a="13143525"
Received: from sea32-co-svc-lb4-vlan3.sea.corp.amazon.com (HELO
 email-inbound-relay-1a-7d76a15f.us-east-1.amazon.com) ([10.47.23.38])
  by smtp-border-fw-out-9102.sea19.amazon.com with ESMTP;
 12 Dec 2019 14:12:52 +0000
Received: from EX13MTAUEA001.ant.amazon.com
 (iad55-ws-svc-p15-lb9-vlan2.iad.amazon.com [10.40.159.162])
        by email-inbound-relay-1a-7d76a15f.us-east-1.amazon.com (Postfix) with
 ESMTPS id D831DA1919;
        Thu, 12 Dec 2019 14:12:50 +0000 (UTC)
Received: from EX13D27EUB004.ant.amazon.com (10.43.166.152) by
 EX13MTAUEA001.ant.amazon.com (10.43.61.82) with Microsoft SMTP Server (TLS)
 id 15.0.1367.3; Thu, 12 Dec 2019 14:12:50 +0000
Received: from uc3ce012741425f.ant.amazon.com (10.43.161.179) by
 EX13D27EUB004.ant.amazon.com (10.43.166.152) with Microsoft SMTP Server (TLS)
 id 15.0.1367.3; Thu, 12 Dec 2019 14:12:47 +0000
From: Milan Pandurov <milanpa@amazon.de>
To: <kvm@vger.kernel.org>
CC: <pbonzini@redhat.com>, <rkrcmar@redhat.com>, <graf@amazon.de>,
        <borntraeger@de.ibm.com>
Subject: [PATCH v4] kvm: Refactor handling of VM debugfs files
Date: Thu, 12 Dec 2019 15:12:36 +0100
Message-ID: <20191212141236.21832-1-milanpa@amazon.de>
X-Mailer: git-send-email 2.17.1
MIME-Version: 1.0
X-Originating-IP: [10.43.161.179]
X-ClientProxiedBy: EX13D10UWA004.ant.amazon.com (10.43.160.64) To
 EX13D27EUB004.ant.amazon.com (10.43.166.152)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We can store reference to kvm_stats_debugfs_item instead of copying
its values to kvm_stat_data.
This allows us to remove duplicated code and usage of temporary
kvm_stat_data inside vm_stat_get et al.

Signed-off-by: Milan Pandurov <milanpa@amazon.de>
---
v1 -> v2:
 - fix compile issues
 - add reference to kvm_stats_debugfs_item in kvm_stat_data
 - return -EINVAL when writing !0
 - use explicit switch case instead of ops indirection
 - fix checkpatch warning: Change S_IWUGO to 0222

v2 -> v3:
 - remove unused kvm_stat_ops
 - fix style issues

v3 -> v4:
 - revert: Change S_IWUGO to 0222
---
 include/linux/kvm_host.h |   7 +-
 virt/kvm/kvm_main.c      | 142 +++++++++++++++++++--------------------
 2 files changed, 76 insertions(+), 73 deletions(-)

```
#### [PATCH RFC v4 01/13] ACPI: NUMA: export pxm_to_node
##### From: David Hildenbrand <david@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Hildenbrand <david@redhat.com>
X-Patchwork-Id: 11288699
Return-Path: <SRS0=BLLP=2C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C2368109A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Dec 2019 17:12:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 98029227BF
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Dec 2019 17:12:22 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="bqmm4JR1"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730099AbfLLRMO (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 12 Dec 2019 12:12:14 -0500
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:39718 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1730093AbfLLRMO (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 12 Dec 2019 12:12:14 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1576170733;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=QmqYn0neP7Ig3ATfsZz5/1LWePBeC7WoQLfsRAoMt5Y=;
        b=bqmm4JR1EAUnjFySmLAwcvqAonI2OKzMSWChmyRqUnmo5HSErvA1wlGH3sODoltGgjzT/T
        e70sS9Yo263jSaQ1lX7NUQV7cGo68zK7dONpVmBjKKa0YTgESBUIoEFwfNOi/9bZJK5bBm
        GDL+ro2ul9HcXOLgUI7jMzOovCNZJa0=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-424-nHjKpbVVOHCedEn6dfr4Uw-1; Thu, 12 Dec 2019 12:12:08 -0500
X-MC-Unique: nHjKpbVVOHCedEn6dfr4Uw-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id C792718A6EC0;
        Thu, 12 Dec 2019 17:12:06 +0000 (UTC)
Received: from t480s.redhat.com (ovpn-117-65.ams2.redhat.com [10.36.117.65])
        by smtp.corp.redhat.com (Postfix) with ESMTP id AC3725C21B;
        Thu, 12 Dec 2019 17:11:59 +0000 (UTC)
From: David Hildenbrand <david@redhat.com>
To: linux-kernel@vger.kernel.org
Cc: linux-mm@kvack.org, virtio-dev@lists.oasis-open.org,
        virtualization@lists.linux-foundation.org, kvm@vger.kernel.org,
        Michal Hocko <mhocko@kernel.org>,
        Andrew Morton <akpm@linux-foundation.org>,
        "Michael S . Tsirkin" <mst@redhat.com>,
        David Hildenbrand <david@redhat.com>,
        "Rafael J. Wysocki" <rjw@rjwysocki.net>,
        Len Brown <lenb@kernel.org>, linux-acpi@vger.kernel.org
Subject: [PATCH RFC v4 01/13] ACPI: NUMA: export pxm_to_node
Date: Thu, 12 Dec 2019 18:11:25 +0100
Message-Id: <20191212171137.13872-2-david@redhat.com>
In-Reply-To: <20191212171137.13872-1-david@redhat.com>
References: <20191212171137.13872-1-david@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Will be needed by virtio-mem to identify the node from a pxm.

Cc: "Rafael J. Wysocki" <rjw@rjwysocki.net>
Cc: Len Brown <lenb@kernel.org>
Cc: linux-acpi@vger.kernel.org
Signed-off-by: David Hildenbrand <david@redhat.com>
---
 drivers/acpi/numa/srat.c | 1 +
 1 file changed, 1 insertion(+)

```
