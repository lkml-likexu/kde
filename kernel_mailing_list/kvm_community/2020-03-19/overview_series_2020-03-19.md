#### [PATCH v15 Kernel 1/7] vfio: KABI for migration interface for device state
##### From: Kirti Wankhede <kwankhede@nvidia.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kirti Wankhede <kwankhede@nvidia.com>
X-Patchwork-Id: 11448045
Return-Path: <SRS0=MMtT=5E=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 99DBD1668
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 19 Mar 2020 20:50:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 670F220787
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 19 Mar 2020 20:50:40 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=nvidia.com header.i=@nvidia.com
 header.b="NrUZxtBO"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727401AbgCSUuj (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 19 Mar 2020 16:50:39 -0400
Received: from hqnvemgate25.nvidia.com ([216.228.121.64]:15216 "EHLO
        hqnvemgate25.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727257AbgCSUuW (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 19 Mar 2020 16:50:22 -0400
Received: from hqpgpgate102.nvidia.com (Not Verified[216.228.121.13]) by
 hqnvemgate25.nvidia.com (using TLS: TLSv1.2, DES-CBC3-SHA)
        id <B5e73dadb0000>; Thu, 19 Mar 2020 13:49:31 -0700
Received: from hqmail.nvidia.com ([172.20.161.6])
  by hqpgpgate102.nvidia.com (PGP Universal service);
  Thu, 19 Mar 2020 13:50:21 -0700
X-PGP-Universal: processed;
        by hqpgpgate102.nvidia.com on Thu, 19 Mar 2020 13:50:21 -0700
Received: from HQMAIL105.nvidia.com (172.20.187.12) by HQMAIL109.nvidia.com
 (172.20.187.15) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Thu, 19 Mar
 2020 20:50:20 +0000
Received: from kwankhede-dev.nvidia.com (10.124.1.5) by HQMAIL105.nvidia.com
 (172.20.187.12) with Microsoft SMTP Server (TLS) id 15.0.1473.3 via Frontend
 Transport; Thu, 19 Mar 2020 20:50:14 +0000
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
Subject: [PATCH v15 Kernel 1/7] vfio: KABI for migration interface for device
 state
Date: Fri, 20 Mar 2020 01:46:38 +0530
Message-ID: <1584649004-8285-2-git-send-email-kwankhede@nvidia.com>
X-Mailer: git-send-email 2.7.0
In-Reply-To: <1584649004-8285-1-git-send-email-kwankhede@nvidia.com>
References: <1584649004-8285-1-git-send-email-kwankhede@nvidia.com>
X-NVConfidentiality: public
MIME-Version: 1.0
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1584650971; bh=0ZjfEcEiUXBdRywKyc/OSpDD6GbPXaTampjnU8oIFR4=;
        h=X-PGP-Universal:From:To:CC:Subject:Date:Message-ID:X-Mailer:
         In-Reply-To:References:X-NVConfidentiality:MIME-Version:
         Content-Type;
        b=NrUZxtBOsOotXYc6nxKq6Hm//ewQ8P0QQ+uhZbziuAglUEfqcnCiVm8C2MtYvI/Oi
         iLlVimo81F08oYph0rzzO+M0IqwPOlvmhJA3uKNa5kK7lv/VMYjQUjYQhIc6pyAiv6
         vc6Bvji7pJT425YOD/+RS8zlHaF7yw/xKTgut4ZpbgmDMG3i/gWDWnieU7JUZ1rSRU
         t9eLubPPjdLwZUN2Ex3dISdi9PiTP6Ler1rYQGd2zn2qMFRGrlcS3Qt7aiTNdWIujK
         ZHNpLbqEoibu04ni4v9zA/mkX6nPM0rxK1MZU+YQy3jOpdWhkw+rlG/jd889P2mcWP
         6591WNMr4294w==
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
 include/uapi/linux/vfio.h | 227 ++++++++++++++++++++++++++++++++++++++++++++++
 1 file changed, 227 insertions(+)

```
#### [PATCH] KVM: PPC: Book3S HV: Add a capability for enabling secure guests
##### From: Paul Mackerras <paulus@ozlabs.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Paul Mackerras <paulus@ozlabs.org>
X-Patchwork-Id: 11446465
Return-Path: <SRS0=MMtT=5E=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D087417E6
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 19 Mar 2020 04:33:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A09262072D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 19 Mar 2020 04:33:11 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ozlabs.org header.i=@ozlabs.org
 header.b="q3+vPPVH"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725874AbgCSEdK (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 19 Mar 2020 00:33:10 -0400
Received: from bilbo.ozlabs.org ([203.11.71.1]:36817 "EHLO ozlabs.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725768AbgCSEdK (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 19 Mar 2020 00:33:10 -0400
Received: by ozlabs.org (Postfix, from userid 1003)
        id 48jYtV5Ly0z9sSM; Thu, 19 Mar 2020 15:33:06 +1100 (AEDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=ozlabs.org; s=201707;
        t=1584592386; bh=QAywpI3JOjIIEUTy46Gfhm93J1pIzZ8maKY0VqoIB8k=;
        h=Date:From:To:Cc:Subject:From;
        b=q3+vPPVHAr7M76upYnV+slNMg4FMb0q3It1nUOv0AXZln4DYvSJLAEfoCkkzo+6kQ
         984QRjlUMIAfhAAcI+tnYupptPT5aEMY2TLgI9qh9xgyhARFfkUwXlhElphX8UHgeC
         aCTyDbyQYzf3OJT4bosANZmvKI9jdxSvmmFKlJ6ycT4jbJcjijAUzCqlv122ahbxPw
         UMpzcNwvx2HNw7wPjkXgavG7E7Rk0MtxO6wJVNLA07i7L5Gix7J/wAKOZpFB6J9Clv
         SW2gtCB2aQwJAfOfRkO6lF5DwJhjgaiwmXVDMGeZQdJdA00OabsWCrq2ctVaOpHINu
         V7o5tb8rHCpxg==
Date: Thu, 19 Mar 2020 15:33:01 +1100
From: Paul Mackerras <paulus@ozlabs.org>
To: kvm@vger.kernel.org
Cc: kvm-ppc@vger.kernel.org,
        David Gibson <david@gibson.dropbear.id.au>,
        Ram Pai <linuxram@us.ibm.com>
Subject: [PATCH] KVM: PPC: Book3S HV: Add a capability for enabling secure
 guests
Message-ID: <20200319043301.GA13052@blackberry>
MIME-Version: 1.0
Content-Disposition: inline
User-Agent: Mutt/1.5.24 (2015-08-30)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

At present, on Power systems with Protected Execution Facility
hardware and an ultravisor, a KVM guest can transition to being a
secure guest at will.  Userspace (QEMU) has no way of knowing
whether a host system is capable of running secure guests.  This
will present a problem in future when the ultravisor is capable of
migrating secure guests from one host to another, because
virtualization management software will have no way to ensure that
secure guests only run in domains where all of the hosts can
support secure guests.

This adds a VM capability which has two functions: (a) userspace
can query it to find out whether the host can support secure guests,
and (b) userspace can enable it for a guest, which allows that
guest to become a secure guest.  If userspace does not enable it,
KVM will return an error when the ultravisor does the hypercall
that indicates that the guest is starting to transition to a
secure guest.  The ultravisor will then abort the transition and
the guest will terminate.

Signed-off-by: Paul Mackerras <paulus@ozlabs.org>
Reviewed-by: Greg Kurz <groug@kaod.org>
Reviewed-by: Cédric Le Goater <clg@kaod.org>
---
Note, only compile-tested.  Ram, please test.

 Documentation/virt/kvm/api.rst      | 17 +++++++++++++++++
 arch/powerpc/include/asm/kvm_host.h |  1 +
 arch/powerpc/include/asm/kvm_ppc.h  |  1 +
 arch/powerpc/kvm/book3s_hv.c        | 13 +++++++++++++
 arch/powerpc/kvm/book3s_hv_uvmem.c  |  4 ++++
 arch/powerpc/kvm/powerpc.c          | 13 +++++++++++++
 include/uapi/linux/kvm.h            |  1 +
 7 files changed, 50 insertions(+)

```
#### [PATCH] KVM: x86: remove bogus user-triggerable WARN_ON
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11447797
Return-Path: <SRS0=MMtT=5E=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 852A46CA
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 19 Mar 2020 17:43:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5FBBE20836
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 19 Mar 2020 17:43:25 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="bENnoaQT"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728739AbgCSRnY (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 19 Mar 2020 13:43:24 -0400
Received: from us-smtp-delivery-74.mimecast.com ([63.128.21.74]:26000 "EHLO
        us-smtp-delivery-74.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727561AbgCSRnX (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 19 Mar 2020 13:43:23 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1584639802;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc; bh=arXREge8xmNm33ojJlI2/DsuKy1gZAPWYFzbLrZKzuE=;
        b=bENnoaQTkZoyMJKtHZVTdrbLhmxIiQVbEqjn7oOU1ld//j7z7+jtfZfftxIQgsVayqGS9t
        25LaGLT87SRTCqB+C0VToT7jziDQoIzU9HiKIltPwKpQJvYsl3LVE90wiXDwVSWGN3P+YF
        NsFjscnha8mUKK9LMEvtKfDvxCm0b+U=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-400-xNA2rQfpPRacroWjr_yhsA-1; Thu, 19 Mar 2020 13:43:20 -0400
X-MC-Unique: xNA2rQfpPRacroWjr_yhsA-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id B7DB18024EA;
        Thu, 19 Mar 2020 17:43:19 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 02C055C545;
        Thu, 19 Mar 2020 17:43:18 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: syzbot+00be5da1d75f1cc95f6b@syzkaller.appspotmail.com,
        Sean Christopherson <sean.j.christopherson@intel.com>
Subject: [PATCH] KVM: x86: remove bogus user-triggerable WARN_ON
Date: Thu, 19 Mar 2020 13:43:18 -0400
Message-Id: <20200319174318.20752-1-pbonzini@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The WARN_ON is essentially comparing a user-provided value with 0.  It is
trivial to trigger it just by passing garbage to KVM_SET_CLOCK.  Guests
can break if you do so, but if it hurts when you do like this just do not
do it.

Reported-by: syzbot+00be5da1d75f1cc95f6b@syzkaller.appspotmail.com
Fixes: 9446e6fce0ab ("KVM: x86: fix WARN_ON check of an unsigned less than zero")
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/x86.c | 1 -
 1 file changed, 1 deletion(-)

```
#### [PATCH v2 1/5] KVM: x86/pmu: Add base address parameter for get_fixed_pmc function
##### From: Luwei Kang <luwei.kang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Luwei Kang <luwei.kang@intel.com>
X-Patchwork-Id: 11446545
Return-Path: <SRS0=MMtT=5E=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EB2A81668
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 19 Mar 2020 06:35:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D4E3520409
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 19 Mar 2020 06:35:43 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727154AbgCSGfk (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 19 Mar 2020 02:35:40 -0400
Received: from mga18.intel.com ([134.134.136.126]:53786 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727083AbgCSGfk (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 19 Mar 2020 02:35:40 -0400
IronPort-SDR: 
 uN70BF67evq3fYIOzWXYrvPcgwYfO6elXpxF4mw3jyNrYXI6j3GParuuDhjplExTyO8VcCgoBh
 ICM546pLLQcA==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga006.jf.intel.com ([10.7.209.51])
  by orsmga106.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 18 Mar 2020 23:35:39 -0700
IronPort-SDR: 
 mO6BQX3Nubr+1jnwsgXjApcFxUDYoktBvcVK/l5I75yXI3q9hhvDsIoE62AI6hXhjSQ8r+nluz
 bZOVt17vDFQA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,570,1574150400";
   d="scan'208";a="248439100"
Received: from snr.bj.intel.com ([10.240.193.90])
  by orsmga006.jf.intel.com with ESMTP; 18 Mar 2020 23:35:33 -0700
From: Luwei Kang <luwei.kang@intel.com>
To: x86@kernel.org, linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: peterz@infradead.org, mingo@redhat.com, acme@kernel.org,
        mark.rutland@arm.com, alexander.shishkin@linux.intel.com,
        jolsa@redhat.com, namhyung@kernel.org, tglx@linutronix.de,
        bp@alien8.de, hpa@zytor.com, pbonzini@redhat.com,
        sean.j.christopherson@intel.com, vkuznets@redhat.com,
        wanpengli@tencent.com, jmattson@google.com, joro@8bytes.org,
        pawan.kumar.gupta@linux.intel.com, ak@linux.intel.com,
        thomas.lendacky@amd.com, fenghua.yu@intel.com,
        kan.liang@linux.intel.com, Luwei Kang <luwei.kang@intel.com>
Subject: [PATCH v2 1/5] KVM: x86/pmu: Add base address parameter for
 get_fixed_pmc function
Date: Thu, 19 Mar 2020 22:33:46 +0800
Message-Id: <1584628430-23220-2-git-send-email-luwei.kang@intel.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1584628430-23220-1-git-send-email-luwei.kang@intel.com>
References: <1584628430-23220-1-git-send-email-luwei.kang@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

PEBS output to Inte PT feature introduces some new
MSRs(MSR_RELOAD_FIXED_CTRx) for fixed function counters that using for
autoload the present value after writing out a PEBS event.

Introduce a base MSRs address parameter to make this function can get
kvm performance monitor counter structure by MSR_RELOAD_FIXED_CTRx
registers.

Signed-off-by: Luwei Kang <luwei.kang@intel.com>
---
 arch/x86/kvm/pmu.h           |  5 ++---
 arch/x86/kvm/vmx/pmu_intel.c | 16 ++++++++++------
 2 files changed, 12 insertions(+), 9 deletions(-)

```
#### [PATCH v7 1/5] x86/kvm/hyper-v: Explicitly align hcall param for kvm_hyperv_exit
##### From: Jon Doron <arilou@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jon Doron <arilou@gmail.com>
X-Patchwork-Id: 11446519
Return-Path: <SRS0=MMtT=5E=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EC0961392
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 19 Mar 2020 05:59:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id CBF8B20740
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 19 Mar 2020 05:59:00 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="nOOB05Ht"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727089AbgCSF7A (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 19 Mar 2020 01:59:00 -0400
Received: from mail-wr1-f66.google.com ([209.85.221.66]:38976 "EHLO
        mail-wr1-f66.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725767AbgCSF7A (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 19 Mar 2020 01:59:00 -0400
Received: by mail-wr1-f66.google.com with SMTP id h6so1166997wrs.6;
        Wed, 18 Mar 2020 22:58:58 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=qORovMW4qFXFXcdoIljFzjQs+83nq3xI2+7AeVXu0Jo=;
        b=nOOB05HtYbAQ6YRUSNddR9ZQ+6/ctli+nnZkioh6T3HYsfY4+Zuew9FggRhG2speTc
         awFaRyQYwhZPzl12+wYCReZL2030hIO/t4NouiMRtPF2zVcZ8XOqe8M6B2oGWHYi43Uq
         k7Jgw3umWgtcSc8NQJpK4vWdBA+96kHOokL8iwldpbE2epRj57ltRRD5ez8V28OsEg9w
         bdqAHn2hnj7r90T655m3EWVAPQhKFyfR253k33N86mNty69Ep3JmA42p2dVJXsTQSOO+
         k5qeQ3ZMMMZYBlbSzvlz10Qrmpj3h6UcsMLgsScaafKKU9JVA8IhWVvprq4XajLNyLTF
         h6xg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=qORovMW4qFXFXcdoIljFzjQs+83nq3xI2+7AeVXu0Jo=;
        b=bPTPCRGWw9VKfivv3TTQtMWWS6TRe3QkUbefDLY+D4/n/RVQVbNagCcA7TC/jJjN9o
         xGQupVshIM7sGxL+K/CH/luQijswAQ6ROEbyhY97ciZoN0ChFcnKcKxONLyvE1n3SGaK
         4+MZIm5IHl7SAKSq6JqzWdnei+Anza7eI9qpnPveiT86oqwAcXq82/yaOFFJXA27rurR
         qkiY/m3fLfWyGw/8C7Z7xa6PQqQcubkEOKyGj0cxmK5EeZcUdfTmqLncZo/F8J+SNBEg
         ZzCoCFlVwAMZnvZPx6cCiau63HIjF2PNt2jvr5JvVbuq34VeR98Lvu/1lk6YLZ1IdkGp
         1Y1g==
X-Gm-Message-State: ANhLgQ34dM//TqMO9pnKpOG/V1OmXJ2CT1ZwlNF7l/ZOz2ej3ofRFV1y
        wbFIA6ETDwW9dfZwqRKtzJU+Jv+cQX8=
X-Google-Smtp-Source: 
 ADFU+vtnopswMiu3EvNFMbvxn803dFChQpCfrbFVo1x6X+PQHxVbVqXJ4Sybbk9f2hJDEY835gKyoQ==
X-Received: by 2002:a5d:69cb:: with SMTP id s11mr1832766wrw.47.1584597537739;
        Wed, 18 Mar 2020 22:58:57 -0700 (PDT)
Received: from jondnuc.lan (IGLD-84-229-155-229.inter.net.il.
 [84.229.155.229])
        by smtp.gmail.com with ESMTPSA id
 n2sm1884174wro.25.2020.03.18.22.58.56
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 18 Mar 2020 22:58:57 -0700 (PDT)
From: Jon Doron <arilou@gmail.com>
To: kvm@vger.kernel.org, linux-hyperv@vger.kernel.org
Cc: vkuznets@redhat.com, Jon Doron <arilou@gmail.com>
Subject: [PATCH v7 1/5] x86/kvm/hyper-v: Explicitly align hcall param for
 kvm_hyperv_exit
Date: Thu, 19 Mar 2020 07:58:38 +0200
Message-Id: <20200319055842.673513-2-arilou@gmail.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20200319055842.673513-1-arilou@gmail.com>
References: <20200319055842.673513-1-arilou@gmail.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The problem the patch is trying to address is the fact that 'struct
kvm_hyperv_exit' has different layout on when compiling in 32 and 64 bit
modes.

In 64-bit mode the default alignment boundary is 64 bits thus
forcing extra gaps after 'type' and 'msr' but in 32-bit mode the
boundary is at 32 bits thus no extra gaps.

This is an issue as even when the kernel is 64 bit, the userspace using
the interface can be both 32 and 64 bit but the same 32 bit userspace has
to work with 32 bit kernel.

The issue is fixed by forcing the 64 bit layout, this leads to ABI
change for 32 bit builds and while we are obviously breaking '32 bit
userspace with 32 bit kernel' case, we're fixing the '32 bit userspace
with 64 bit kernel' one.

As the interface has no (known) users and 32 bit KVM is rather baroque
nowadays, this seems like a reasonable decision.

Signed-off-by: Jon Doron <arilou@gmail.com>
---
 Documentation/virt/kvm/api.rst | 2 ++
 include/uapi/linux/kvm.h       | 2 ++
 2 files changed, 4 insertions(+)

```
#### [PATCH v8 1/5] x86/kvm/hyper-v: Explicitly align hcall param for kvm_hyperv_exit
##### From: Jon Doron <arilou@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jon Doron <arilou@gmail.com>
X-Patchwork-Id: 11446555
Return-Path: <SRS0=MMtT=5E=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 27FC113B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 19 Mar 2020 06:38:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 04CB320757
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 19 Mar 2020 06:38:52 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="XHgPjea2"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727163AbgCSGiw (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 19 Mar 2020 02:38:52 -0400
Received: from mail-wm1-f67.google.com ([209.85.128.67]:35721 "EHLO
        mail-wm1-f67.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726714AbgCSGiv (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 19 Mar 2020 02:38:51 -0400
Received: by mail-wm1-f67.google.com with SMTP id m3so717026wmi.0;
        Wed, 18 Mar 2020 23:38:50 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=qORovMW4qFXFXcdoIljFzjQs+83nq3xI2+7AeVXu0Jo=;
        b=XHgPjea2n+g2SEmEbwyrkXs34T5r0cG6XzKB2M0ynsZeDtSYiUlk+Bp2zTTafyoZdH
         P5g4lj1ImzTMGDW+7Atct6VEBlJbr91iB282aTbVXgr5YmnJubVskQ4yJRoq+D7wTbfV
         O1KeFtRSp7tlRXt0Z61oEwkX9r3rLRf7t0l7iC8V7KAEq8jP3DeOJ5hCYeD0hM12Pkxa
         /MeW5V9zgNPgEgNiRd9Sng2rqvB0414rjJWXWF9eh/CQ9tKxes386kqRTiYlkafwnaxE
         z4vP1rEdpatH19NOPykNj3OVCRo6Y9cqjzQa3u78GmMhDEKsg9zNXl0l70eCrbhr5lVH
         ZQiw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=qORovMW4qFXFXcdoIljFzjQs+83nq3xI2+7AeVXu0Jo=;
        b=bSAbhf7FkdZTUOBGROyQbQ5GH4tAVLbidqTrvmpr9W537L4EsU6CUvU0RwV8xS8jPs
         cRvsIsjW/+/HTruYRhmAkE8G4bH84hfbz6BcNKNIZ7eUYsndhNCcGICWYd6mx8/sF/SU
         JIDykZltrTjMH2hkh4YTVXL2FozronLcCwTVBJcqYYmWm7a+rOW5uxjcCpz5qkCo7zFT
         FAjwMCCDjBA94UVL6bZBhZ7DJzNp71ow0RCiYIL9dbEwQCdy9TTJa4cIoaS7ckoLSNBA
         wgJjbNnqqsdl7Vb3e/2sBU9lsA06DQNIt3skNK1C1DX/RcJmQWnUgsvlSxvBMmSiBiPK
         JGJQ==
X-Gm-Message-State: ANhLgQ2Gj38l/vml8jMzvuoxBabV4zDDJ3ogssnwEdSRiLd8NJ+wmW1W
        QbIYaDDA5A75yCFy6jHpCKZxevsepZI=
X-Google-Smtp-Source: 
 ADFU+vv2umC2Fn4i78nQiQtIaZeOwfGtR6/eYcbt62L8GKOZ7Lk5sF0RJJLR5pkcx4EbYffDB3IWDQ==
X-Received: by 2002:a1c:5506:: with SMTP id j6mr1781381wmb.127.1584599930042;
        Wed, 18 Mar 2020 23:38:50 -0700 (PDT)
Received: from jondnuc.lan (IGLD-84-229-155-229.inter.net.il.
 [84.229.155.229])
        by smtp.gmail.com with ESMTPSA id
 l13sm1945665wrm.57.2020.03.18.23.38.49
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 18 Mar 2020 23:38:49 -0700 (PDT)
From: Jon Doron <arilou@gmail.com>
To: kvm@vger.kernel.org, linux-hyperv@vger.kernel.org
Cc: vkuznets@redhat.com, Jon Doron <arilou@gmail.com>
Subject: [PATCH v8 1/5] x86/kvm/hyper-v: Explicitly align hcall param for
 kvm_hyperv_exit
Date: Thu, 19 Mar 2020 08:38:32 +0200
Message-Id: <20200319063836.678562-2-arilou@gmail.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20200319063836.678562-1-arilou@gmail.com>
References: <20200319063836.678562-1-arilou@gmail.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The problem the patch is trying to address is the fact that 'struct
kvm_hyperv_exit' has different layout on when compiling in 32 and 64 bit
modes.

In 64-bit mode the default alignment boundary is 64 bits thus
forcing extra gaps after 'type' and 'msr' but in 32-bit mode the
boundary is at 32 bits thus no extra gaps.

This is an issue as even when the kernel is 64 bit, the userspace using
the interface can be both 32 and 64 bit but the same 32 bit userspace has
to work with 32 bit kernel.

The issue is fixed by forcing the 64 bit layout, this leads to ABI
change for 32 bit builds and while we are obviously breaking '32 bit
userspace with 32 bit kernel' case, we're fixing the '32 bit userspace
with 64 bit kernel' one.

As the interface has no (known) users and 32 bit KVM is rather baroque
nowadays, this seems like a reasonable decision.

Signed-off-by: Jon Doron <arilou@gmail.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 Documentation/virt/kvm/api.rst | 2 ++
 include/uapi/linux/kvm.h       | 2 ++
 2 files changed, 4 insertions(+)

```
#### [PATCH 01/70] KVM: SVM: Add GHCB definitions
##### From: Joerg Roedel <joro@8bytes.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Joerg Roedel <joro@8bytes.org>
X-Patchwork-Id: 11446897
Return-Path: <SRS0=MMtT=5E=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6220D14B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 19 Mar 2020 09:21:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 3DC4D20722
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 19 Mar 2020 09:21:01 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727032AbgCSJOT (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 19 Mar 2020 05:14:19 -0400
Received: from 8bytes.org ([81.169.241.247]:51868 "EHLO theia.8bytes.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727091AbgCSJOS (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 19 Mar 2020 05:14:18 -0400
Received: by theia.8bytes.org (Postfix, from userid 1000)
        id D3105B0; Thu, 19 Mar 2020 10:14:15 +0100 (CET)
From: Joerg Roedel <joro@8bytes.org>
To: x86@kernel.org
Cc: hpa@zytor.com, Andy Lutomirski <luto@kernel.org>,
        Dave Hansen <dave.hansen@linux.intel.com>,
        Peter Zijlstra <peterz@infradead.org>,
        Thomas Hellstrom <thellstrom@vmware.com>,
        Jiri Slaby <jslaby@suse.cz>,
        Dan Williams <dan.j.williams@intel.com>,
        Tom Lendacky <thomas.lendacky@amd.com>,
        Juergen Gross <jgross@suse.com>,
        Kees Cook <keescook@chromium.org>,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org,
        Joerg Roedel <joro@8bytes.org>, Joerg Roedel <jroedel@suse.de>
Subject: [PATCH 01/70] KVM: SVM: Add GHCB definitions
Date: Thu, 19 Mar 2020 10:12:58 +0100
Message-Id: <20200319091407.1481-2-joro@8bytes.org>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200319091407.1481-1-joro@8bytes.org>
References: <20200319091407.1481-1-joro@8bytes.org>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Tom Lendacky <thomas.lendacky@amd.com>

Extend the vmcb_safe_area with SEV-ES fields and add a new
'struct ghcb' which will be used for guest-hypervisor communication.

Signed-off-by: Tom Lendacky <thomas.lendacky@amd.com>
Signed-off-by: Joerg Roedel <jroedel@suse.de>
---
 arch/x86/include/asm/svm.h | 42 ++++++++++++++++++++++++++++++++++++++
 1 file changed, 42 insertions(+)

```
