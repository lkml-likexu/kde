

#### [PATCH v3 0/1] vfio-ccw: Enable transparent CCW IPL from DASD
##### From: Jared Rossi <jrossi@linux.ibm.com>

```c
From patchwork Wed May  6 00:15:43 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jared Rossi <jrossi@linux.ibm.com>
X-Patchwork-Id: 11530093
Return-Path: <SRS0=qN9b=6U=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 920741392
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 May 2020 00:13:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 83CDF2075E
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 May 2020 00:13:24 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729533AbgEFANR (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 5 May 2020 20:13:17 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:57184 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727989AbgEFANQ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 5 May 2020 20:13:16 -0400
Received: from pps.filterd (m0098420.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 046035xK012562;
        Tue, 5 May 2020 20:13:15 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 30ugugaba0-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 05 May 2020 20:13:15 -0400
Received: from m0098420.ppops.net (m0098420.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 04603Xqn014153;
        Tue, 5 May 2020 20:13:15 -0400
Received: from ppma03dal.us.ibm.com (b.bd.3ea9.ip4.static.sl-reverse.com
 [169.62.189.11])
        by mx0b-001b2d01.pphosted.com with ESMTP id 30ugugab9n-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 05 May 2020 20:13:15 -0400
Received: from pps.filterd (ppma03dal.us.ibm.com [127.0.0.1])
        by ppma03dal.us.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 0460AL6Y006022;
        Wed, 6 May 2020 00:13:14 GMT
Received: from b03cxnp07028.gho.boulder.ibm.com
 (b03cxnp07028.gho.boulder.ibm.com [9.17.130.15])
        by ppma03dal.us.ibm.com with ESMTP id 30s0g7c4dd-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 06 May 2020 00:13:14 +0000
Received: from b03ledav004.gho.boulder.ibm.com
 (b03ledav004.gho.boulder.ibm.com [9.17.130.235])
        by b03cxnp07028.gho.boulder.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 0460DC7637093636
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 6 May 2020 00:13:12 GMT
Received: from b03ledav004.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 5F39E7805F;
        Wed,  6 May 2020 00:13:12 +0000 (GMT)
Received: from b03ledav004.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 8E8BC7805C;
        Wed,  6 May 2020 00:13:11 +0000 (GMT)
Received: from localhost.localdomain.com (unknown [9.85.145.129])
        by b03ledav004.gho.boulder.ibm.com (Postfix) with ESMTP;
        Wed,  6 May 2020 00:13:11 +0000 (GMT)
From: Jared Rossi <jrossi@linux.ibm.com>
To: Eric Farman <farman@linux.ibm.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Halil Pasic <pasic@linux.ibm.com>
Cc: linux-s390@vger.kernel.org, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v3 0/1] vfio-ccw: Enable transparent CCW IPL from DASD
Date: Tue,  5 May 2020 20:15:43 -0400
Message-Id: <20200506001544.16213-1-jrossi@linux.ibm.com>
X-Mailer: git-send-email 2.21.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.676
 definitions=2020-05-05_11:2020-05-04,2020-05-05 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 clxscore=1015 mlxscore=0
 phishscore=0 impostorscore=0 lowpriorityscore=0 suspectscore=0 bulkscore=0
 spamscore=0 adultscore=0 malwarescore=0 priorityscore=1501 mlxlogscore=999
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2003020000
 definitions=main-2005050178
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Remove the explicit prefetch check when using vfio-ccw devices.
This check does not trigger in practice as all Linux channel programs
are intended to use prefetch.

Version 3 improves logging by including the UUID of the vfio device
that triggers the warning.  A custom rate limit is used because
the generic rate limit of 10 per 5 seconds will still result in
multiple warnings during IPL. The warning message has been clarfied
to reflect that a channel program will be executed using prefetch
even though prefetch was not specified.

The text of warning itself does not explicitly refer to non-prefetching
channel programs as unsupported because it will trigger during IPL,
which is a normal and expected sequence.  Likewise, because we expect
the message to appear during IPL, the warning also does not explicitly
alert to the potential of an error, rather it simply notes that a
channel program is being executed in a way other than specified.

Verson 3 also makes some word choice changes to the documentation.

Jared Rossi (1):
  vfio-ccw: Enable transparent CCW IPL from DASD

 Documentation/s390/vfio-ccw.rst |  6 ++++++
 drivers/s390/cio/vfio_ccw_cp.c  | 19 ++++++++++++-------
 2 files changed, 18 insertions(+), 7 deletions(-)
```
#### [PATCH v12 00/10] Introduce support for guest CET feature
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
From patchwork Wed May  6 08:20:59 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Weijiang <weijiang.yang@intel.com>
X-Patchwork-Id: 11530693
Return-Path: <SRS0=qN9b=6U=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1144A14B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 May 2020 08:20:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 01FEC20714
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 May 2020 08:20:41 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728492AbgEFITd (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 6 May 2020 04:19:33 -0400
Received: from mga12.intel.com ([192.55.52.136]:35417 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727956AbgEFITc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 6 May 2020 04:19:32 -0400
IronPort-SDR: 
 wh/LuNdsM6dh97y4DoXDqvxQtWgCLksPxFzBcdWtG4RVWm8tQa+gIf1MbIv9gjVciVrNXrUHlh
 5HexSBCW3i+Q==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga003.jf.intel.com ([10.7.209.27])
  by fmsmga106.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 06 May 2020 01:19:31 -0700
IronPort-SDR: 
 0sJdlU5Eqrq/1EZ0PUrt4wZ7aBHhsOBfYytUeHSPfQgqCv7xnT7xVOh38Hy/9rkq5nGniSlo57
 YYQQwDm42Vyw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,358,1583222400";
   d="scan'208";a="260030045"
Received: from unknown (HELO local-michael-cet-test.sh.intel.com)
 ([10.239.159.128])
  by orsmga003.jf.intel.com with ESMTP; 06 May 2020 01:19:29 -0700
From: Yang Weijiang <weijiang.yang@intel.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        pbonzini@redhat.com, sean.j.christopherson@intel.com,
        jmattson@google.com
Cc: yu.c.zhang@linux.intel.com, Yang Weijiang <weijiang.yang@intel.com>
Subject: [PATCH v12 00/10] Introduce support for guest CET feature
Date: Wed,  6 May 2020 16:20:59 +0800
Message-Id: <20200506082110.25441-1-weijiang.yang@intel.com>
X-Mailer: git-send-email 2.17.2
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Control-flow Enforcement Technology (CET) provides protection against
Return/Jump-Oriented Programming (ROP/JOP) attack. There're two CET
sub-features: Shadow Stack (SHSTK) and Indirect Branch Tracking (IBT).
SHSTK is to prevent ROP programming and IBT is to prevent JOP programming.

Several parts in KVM have been updated to provide VM CET support, including:
CPUID/XSAVES config, MSR pass-through, user space MSR access interface, 
vmentry/vmexit config, nested VM etc. These patches have dependency on CET
kernel patches for xsaves support and CET definitions, e.g., MSR and related
feature flags.

CET kernel patches are here:
https://lkml.kernel.org/r/20200429220732.31602-1-yu-cheng.yu@intel.com

v12:
- Fixed a few issues per Sean and Paolo's review feeback.
- Refactored patches to make them properly arranged.
- Removed unnecessary hard-coded CET states for host/guest.
- Added compile-time assertions for vmcs_field_to_offset_table to detect
  mismatch of the field type and field encoding number.
- Added a custom MSR MSR_KVM_GUEST_SSP for guest active SSP save/restore.
- Rebased patches to 5.7-rc3.

v11:
- Fixed a guest vmentry failure issue when guest reboots.
- Used vm_xxx_control_{set, clear}bit() to avoid side effect, it'll
  clear cached data instead of pure VMCS field bits.
- Added vcpu->arch.guest_supported_xss dedidated for guest runtime mask,
  this avoids supported_xss overwritten issue caused by an old qemu.
- Separated vmentry/vmexit state setting with CR0/CR4 dependency check
  to make the patch more clear.
- Added CET VMCS states in dump_vmcs() for debugging purpose.
- Other refactor based on testing.
- This patch serial is built on top of below branch and CET kernel patches
  for seeking xsaves support:
  https://git.kernel.org/pub/scm/virt/kvm/kvm.git/log/?h=cpu-caps

v10:
- Refactored code per Sean's review feedback.
- Added CET support for nested VM.
- Removed fix-patch for CPUID(0xd,N) enumeration as this part is done
  by Paolo and Sean.
- This new patchset is based on Paolo's queued cpu_caps branch.
- Modified patch per XSAVES related change.
- Consolidated KVM unit-test patch with KVM patches.

v9:
- Refactored msr-check functions per Sean's feedback.
- Fixed a few issues per Sean's suggestion.
- Rebased patch to kernel-v5.4.
- Moved CET CPUID feature bits and CR4.CET to last patch.

v8:
- Addressed Jim and Sean's feedback on: 1) CPUID(0xD,i) enumeration. 2)
  sanity check when configure guest CET. 3) function improvement.
- Added more sanity check functions.
- Set host vmexit default status so that guest won't leak CET status to
  host when vmexit.
- Added CR0.WP vs. CR4.CET mutual constrains.

v7:
- Rebased patch to kernel v5.3
- Sean suggested to change CPUID(0xd, n) enumeration code as alined with
  existing one, and I think it's better to make the fix as an independent patch 
  since XSS MSR are being used widely on X86 platforms.
- Check more host and guest status before configure guest CET
  per Sean's feedback.
- Add error-check before guest accesses CET MSRs per Sean's feedback.
- Other minor fixes suggested by Sean.

v6:
- Rebase patch to kernel v5.2.
- Move CPUID(0xD, n>=1) helper to a seperate patch.
- Merge xsave size fix with other patch.
- Other minor fixes per community feedback.

v5:
- Rebase patch to kernel v5.1.
- Wrap CPUID(0xD, n>=1) code to a helper function.
- Pass through MSR_IA32_PL1_SSP and MSR_IA32_PL2_SSP to Guest.
- Add Co-developed-by expression in patch description.
- Refine patch description.

v4:
- Add Sean's patch for loading Guest fpu state before access XSAVES
  managed CET MSRs.
- Melt down CET bits setting into CPUID configuration patch.
- Add VMX interface to query Host XSS.
- Check Host and Guest XSS support bits before set Guest XSS.
- Make Guest SHSTK and IBT feature enabling independent.
- Do not report CET support to Guest when Host CET feature is Disabled.

v3:
- Modified patches to make Guest CET independent to Host enabling.
- Added patch 8 to add user space access for Guest CET MSR access.
- Modified code comments and patch description to reflect changes.

v2:
- Re-ordered patch sequence, combined one patch.
- Added more description for CET related VMCS fields.
- Added Host CET capability check while enabling Guest CET loading bit.
- Added Host CET capability check while reporting Guest CPUID(EAX=7, EXC=0).
- Modified code in reporting Guest CPUID(EAX=D,ECX>=1), make it clearer.
- Added Host and Guest XSS mask check while setting bits for Guest XSS.



Sean Christopherson (1):
  KVM: x86: Load guest fpu state when access MSRs managed by XSAVES

Yang Weijiang (9):
  KVM: VMX: Introduce CET VMCS fields and flags
  KVM: VMX: Set guest CET MSRs per KVM and host configuration
  KVM: VMX: Configure CET settings upon guest CR0/4 changing
  KVM: x86: Refresh CPUID once guest changes XSS bits
  KVM: x86: Add userspace access interface for CET MSRs
  KVM: VMX: Enable CET support for nested VM
  KVM: VMX: Add VMCS dump and sanity check for CET states
  KVM: x86: Add #CP support in guest exception dispatch
  KVM: x86: Enable CET virtualization and advertise CET to userspace

 arch/x86/include/asm/kvm_host.h      |   4 +-
 arch/x86/include/asm/vmx.h           |   8 +
 arch/x86/include/uapi/asm/kvm.h      |   1 +
 arch/x86/include/uapi/asm/kvm_para.h |   7 +-
 arch/x86/kvm/cpuid.c                 |  28 ++-
 arch/x86/kvm/vmx/capabilities.h      |   5 +
 arch/x86/kvm/vmx/nested.c            |  34 ++++
 arch/x86/kvm/vmx/vmcs12.c            | 275 ++++++++++++++++-----------
 arch/x86/kvm/vmx/vmcs12.h            |  14 +-
 arch/x86/kvm/vmx/vmx.c               | 257 ++++++++++++++++++++++++-
 arch/x86/kvm/x86.c                   |  42 +++-
 arch/x86/kvm/x86.h                   |   2 +-
 12 files changed, 546 insertions(+), 131 deletions(-)
```
#### [PATCH v1 00/17] virtio-mem: Paravirtualized memory hot(un)plug
##### From: David Hildenbrand <david@redhat.com>

```c
From patchwork Wed May  6 09:49:31 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Hildenbrand <david@redhat.com>
X-Patchwork-Id: 11530893
Return-Path: <SRS0=qN9b=6U=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 23447139F
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 May 2020 09:50:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0CF8120714
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 May 2020 09:50:12 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="CA5ccXrV"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729081AbgEFJuL (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 6 May 2020 05:50:11 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:40793 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1728640AbgEFJuK (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 6 May 2020 05:50:10 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1588758609;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=uwx25ggXFYcraw8wlJgMYjAcAt7rECdGCBo2VgZbClU=;
        b=CA5ccXrVNkYoY0Bp4iVBcpvXyLejplaps907+56/3EkzKjl0aINm19SJVdF4iOTgx2vveh
        IEmwcUZR9f5fk1rK5Yc7HCb/ogu22W2D7GAm8AV/xcjsziTvS/vq7hTt1LbZ57hbEbnv9C
        7vlTI70+jozI8IzeI+LdCf1oiZS8WHQ=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-256-GBwgf7kXNXKT49c3ZENCcw-1; Wed, 06 May 2020 05:50:04 -0400
X-MC-Unique: GBwgf7kXNXKT49c3ZENCcw-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 89710835B44;
        Wed,  6 May 2020 09:50:01 +0000 (UTC)
Received: from t480s.redhat.com (ovpn-113-17.ams2.redhat.com [10.36.113.17])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 27BF65C1BD;
        Wed,  6 May 2020 09:49:48 +0000 (UTC)
From: David Hildenbrand <david@redhat.com>
To: qemu-devel@nongnu.org
Cc: kvm@vger.kernel.org, qemu-s390x@nongnu.org,
        Richard Henderson <rth@twiddle.net>,
        Paolo Bonzini <pbonzini@redhat.com>,
        "Dr . David Alan Gilbert" <dgilbert@redhat.com>,
        Eduardo Habkost <ehabkost@redhat.com>,
        "Michael S . Tsirkin" <mst@redhat.com>,
        David Hildenbrand <david@redhat.com>,
        Alex Williamson <alex.williamson@redhat.com>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Eric Blake <eblake@redhat.com>,
        Eric Farman <farman@linux.ibm.com>,
        Hailiang Zhang <zhang.zhanghailiang@huawei.com>,
        Halil Pasic <pasic@linux.ibm.com>,
        Igor Mammedov <imammedo@redhat.com>,
        Janosch Frank <frankja@linux.ibm.com>,
        Juan Quintela <quintela@redhat.com>,
        Keith Busch <kbusch@kernel.org>,
        Marcel Apfelbaum <marcel.apfelbaum@gmail.com>,
        Markus Armbruster <armbru@redhat.com>,
        Peter Maydell <peter.maydell@linaro.org>,
        Pierre Morel <pmorel@linux.ibm.com>,
        Tony Krowiak <akrowiak@linux.ibm.com>
Subject: [PATCH v1 00/17] virtio-mem: Paravirtualized memory hot(un)plug
Date: Wed,  6 May 2020 11:49:31 +0200
Message-Id: <20200506094948.76388-1-david@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is the very basic, initial version of virtio-mem. More info on
virtio-mem in general can be found in the Linux kernel driver posting [1]
and in patch #10.

"The basic idea of virtio-mem is to provide a flexible,
cross-architecture memory hot(un)plug solution that avoids many limitations
imposed by existing technologies, architectures, and interfaces."

There are a lot of addons in the works (esp. protection of unplugged
memory, better hugepage support (esp. when reading unplugged memory),
resizeable memory backends, migration optimizations, support for more
architectures, ...), this is the very basic version to get the ball
rolling.

The first 8 patches make sure we don't have any sudden surprises e.g., if
somebody tries to pin all memory in RAM blocks, resulting in a higher
memory consumption than desired. The remaining patches add basic virtio-mem
along with support for x86-64.

[1] https://lkml.kernel.org/r/20200311171422.10484-1-david@redhat.com

David Hildenbrand (17):
  exec: Introduce ram_block_discard_set_(unreliable|required)()
  vfio: Convert to ram_block_discard_set_broken()
  accel/kvm: Convert to ram_block_discard_set_broken()
  s390x/pv: Convert to ram_block_discard_set_broken()
  virtio-balloon: Rip out qemu_balloon_inhibit()
  target/i386: sev: Use ram_block_discard_set_broken()
  migration/rdma: Use ram_block_discard_set_broken()
  migration/colo: Use ram_block_discard_set_broken()
  linux-headers: update to contain virtio-mem
  virtio-mem: Paravirtualized memory hot(un)plug
  virtio-pci: Proxy for virtio-mem
  MAINTAINERS: Add myself as virtio-mem maintainer
  hmp: Handle virtio-mem when printing memory device info
  numa: Handle virtio-mem in NUMA stats
  pc: Support for virtio-mem-pci
  virtio-mem: Allow notifiers for size changes
  virtio-pci: Send qapi events when the virtio-mem size changes

 MAINTAINERS                                 |   8 +
 accel/kvm/kvm-all.c                         |   3 +-
 balloon.c                                   |  17 -
 exec.c                                      |  48 ++
 hw/core/numa.c                              |   6 +
 hw/i386/Kconfig                             |   1 +
 hw/i386/pc.c                                |  49 +-
 hw/s390x/s390-virtio-ccw.c                  |  22 +-
 hw/vfio/ap.c                                |  10 +-
 hw/vfio/ccw.c                               |  11 +-
 hw/vfio/common.c                            |  53 +-
 hw/vfio/pci.c                               |   6 +-
 hw/virtio/Kconfig                           |  11 +
 hw/virtio/Makefile.objs                     |   2 +
 hw/virtio/virtio-balloon.c                  |  12 +-
 hw/virtio/virtio-mem-pci.c                  | 159 ++++
 hw/virtio/virtio-mem-pci.h                  |  34 +
 hw/virtio/virtio-mem.c                      | 781 ++++++++++++++++++++
 include/exec/memory.h                       |  41 +
 include/hw/pci/pci.h                        |   1 +
 include/hw/vfio/vfio-common.h               |   4 +-
 include/hw/virtio/virtio-mem.h              |  85 +++
 include/migration/colo.h                    |   2 +-
 include/standard-headers/linux/virtio_ids.h |   1 +
 include/standard-headers/linux/virtio_mem.h | 208 ++++++
 include/sysemu/balloon.h                    |   2 -
 migration/migration.c                       |   8 +-
 migration/postcopy-ram.c                    |  23 -
 migration/rdma.c                            |  18 +-
 migration/savevm.c                          |  11 +-
 monitor/hmp-cmds.c                          |  16 +
 monitor/monitor.c                           |   1 +
 qapi/misc.json                              |  64 +-
 target/i386/sev.c                           |   1 +
 34 files changed, 1598 insertions(+), 121 deletions(-)
 create mode 100644 hw/virtio/virtio-mem-pci.c
 create mode 100644 hw/virtio/virtio-mem-pci.h
 create mode 100644 hw/virtio/virtio-mem.c
 create mode 100644 include/hw/virtio/virtio-mem.h
 create mode 100644 include/standard-headers/linux/virtio_mem.h
```
#### [PATCH 0/9] KVM_SET_GUEST_DEBUG tests and fixes,
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
From patchwork Wed May  6 11:10:25 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11531031
Return-Path: <SRS0=qN9b=6U=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D47D5913
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 May 2020 11:10:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BB6D120714
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 May 2020 11:10:45 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="boGLhLOj"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728162AbgEFLKo (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 6 May 2020 07:10:44 -0400
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:24267 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727917AbgEFLKn (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 6 May 2020 07:10:43 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1588763442;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc; bh=8lay/dHAY+Hj4ui8V65Mg/+aXrRPwt7ABhu7lPQIaEk=;
        b=boGLhLOjEWylyGfJMzqL6mKomaRTic6DhiZM+Bkve21cVVx2DmBGfMIpMezKRuGQ/gddNc
        Ctph8AQJWVzbulHkuOsxVe4ijjvTZRRErOg5mdGTAWTl1a8LH5rkvK3Le8AS+B61GKO98l
        zToiSBGVMxX8XPKI8Fe6gq+/RkuMX/w=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-232-HffpQwpoMsGJtGIwkE-JxQ-1; Wed, 06 May 2020 07:10:38 -0400
X-MC-Unique: HffpQwpoMsGJtGIwkE-JxQ-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id BB4101899520;
        Wed,  6 May 2020 11:10:37 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 9732C5C1D4;
        Wed,  6 May 2020 11:10:34 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: peterx@redhat.com,
        Sean Christopherson <sean.j.christopherson@intel.com>
Subject: [PATCH 0/9] KVM_SET_GUEST_DEBUG tests and fixes,
 DR accessors cleanups
Date: Wed,  6 May 2020 07:10:25 -0400
Message-Id: <20200506111034.11756-1-pbonzini@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

I am posting all the pending patches as a full series because I found
another issue on AMD, which is easily fixed with the last patch but has
dependencies on the patches to keep DR6 synchronized with vcpu->arch.dr6.

Paolo Bonzini (5):
  KVM: x86: fix DR6 delivery for various cases of #DB injection
  KVM: SVM: keep DR6 synchronized with vcpu->arch.dr6
  KVM: x86: simplify dr6 accessors in kvm_x86_ops
  KVM: x86, SVM: do not clobber guest DR6 on KVM_EXIT_DEBUG
  KVM: VMX: pass correct DR6 for GD userspace exit

Peter Xu (4):
  KVM: X86: Declare KVM_CAP_SET_GUEST_DEBUG properly
  KVM: X86: Set RTM for DB_VECTOR too for KVM_EXIT_DEBUG
  KVM: X86: Fix single-step with KVM_SET_GUEST_DEBUG
  KVM: selftests: Add KVM_SET_GUEST_DEBUG test

 arch/powerpc/kvm/powerpc.c                    |   1 +
 arch/s390/kvm/kvm-s390.c                      |   1 +
 arch/x86/include/asm/kvm_host.h               |   2 +-
 arch/x86/kvm/svm/svm.c                        |  11 +-
 arch/x86/kvm/vmx/vmx.c                        |  23 +-
 arch/x86/kvm/x86.c                            |  28 +--
 arch/x86/kvm/x86.h                            |   2 +
 tools/testing/selftests/kvm/Makefile          |   1 +
 .../testing/selftests/kvm/include/kvm_util.h  |   2 +
 tools/testing/selftests/kvm/lib/kvm_util.c    |   9 +
 .../testing/selftests/kvm/x86_64/debug_regs.c | 202 ++++++++++++++++++
 11 files changed, 243 insertions(+), 39 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/x86_64/debug_regs.c
```
#### [PATCH 0/4] KVM: SVM: Fix AVIC warning when enable irq window
##### From: Suravee Suthikulpanit <suravee.suthikulpanit@amd.com>

```c
From patchwork Wed May  6 13:17:52 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Suravee Suthikulpanit <Suravee.Suthikulpanit@amd.com>
X-Patchwork-Id: 11531205
Return-Path: <SRS0=qN9b=6U=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 64B2C15AB
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 May 2020 13:18:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 465CC206D5
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 May 2020 13:18:42 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="XjGQZSOD"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728701AbgEFNSi (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 6 May 2020 09:18:38 -0400
Received: from mail-eopbgr760078.outbound.protection.outlook.com
 ([40.107.76.78]:6525
        "EHLO NAM02-CY1-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1728082AbgEFNSU (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 6 May 2020 09:18:20 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=Z0Byoi1YFrZlLtiOOhTxuToVEhHBu4DV/dHx24R+M6UfVXe508JZu+ReJYGwNduLD6H9WWaQJCmv0iI894QGn7QOj0ViDbujKHwy1SVjpNVMipqNwFtlO55rODEqQQ8d+Ct5ppaGha/nGzzZQOjCgBuz0P7ozDFSNgpdZTzSmmr8x6jNCwO6o5o4AOzXyGNN0w5D/XeLoaXLcFe2U5mK/TVGG3bgwKTKYEm9h7KeDhSpXpjtWM1OX+IRwlLCZE9fvpE5svo8O9+oPR/Rluh8CoT7eqQXvhBTtPh7KaOXbcYRvs8Z/RjX+1L7IkrOf2v/kabSnhQcSml7kNU0qjx8hg==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=EHKuqxcnGfkscwD9jFe/Y0HVKRgyHsMiTITckECT99Q=;
 b=gGX5al10LX4uP5x5zMWjuss06tWldtaJ6/MngMwYXxTMzXbi5ALZn6Xi9hrGKKAIspvC+N2ibTF5a1pO/Bu18JvVzu1HZ8rjCt4F/b42eO83BH5Ba9IYoBb+rfgxlAwe+LDXb/VbLZ8mFvORXszz0k6ToZC+xvSVPVmPtS8bzTs8F1fRFeWsqijR8UlszaA6ESjf825zlrhgdKALD1QoK85oJgx8SzEP/7EHntQ+39CmiXJOuWU397T9s7o3LJxojuXjOoUZoXesaSq8dQbDE8pZRCzOuN3AkpWovpJf7zefYaQoAKxVJvS+mfaiT+88hZa0/GK8lYFoGlrjJ2qqbA==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=EHKuqxcnGfkscwD9jFe/Y0HVKRgyHsMiTITckECT99Q=;
 b=XjGQZSODJ1WdJxhibH3gE706GWR5aJ3UcMmYssPCwnYBeCNM95fcoIy6tPoxQ0S/lzZH46jMFQI/YlRf/angONk8Vdxppa+vWpk6AQ2cE8QnMCr/XzfwJffhIspyCKHqRRCr3pYeFK0gO33Ww4vkzExhxeenjC1Qs4ub79x1N1U=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=amd.com;
Received: from DM5PR12MB1163.namprd12.prod.outlook.com (2603:10b6:3:7a::18) by
 DM5PR12MB1258.namprd12.prod.outlook.com (2603:10b6:3:79::14) with Microsoft
 SMTP Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.2958.29; Wed, 6 May 2020 13:18:13 +0000
Received: from DM5PR12MB1163.namprd12.prod.outlook.com
 ([fe80::d061:4c5:954e:4744]) by DM5PR12MB1163.namprd12.prod.outlook.com
 ([fe80::d061:4c5:954e:4744%4]) with mapi id 15.20.2958.030; Wed, 6 May 2020
 13:18:13 +0000
From: Suravee Suthikulpanit <suravee.suthikulpanit@amd.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: pbonzini@redhat.com, joro@8bytes.org, jon.grimm@amd.com,
        mlevitsk@redhat.com,
        Suravee Suthikulpanit <suravee.suthikulpanit@amd.com>
Subject: [PATCH 0/4] KVM: SVM: Fix AVIC warning when enable irq window
Date: Wed,  6 May 2020 08:17:52 -0500
Message-Id: <1588771076-73790-1-git-send-email-suravee.suthikulpanit@amd.com>
X-Mailer: git-send-email 1.8.3.1
X-ClientProxiedBy: DM5PR12CA0071.namprd12.prod.outlook.com
 (2603:10b6:3:103::33) To DM5PR12MB1163.namprd12.prod.outlook.com
 (2603:10b6:3:7a::18)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from ssuthiku-rhel7-ssp.amd.com (165.204.78.2) by
 DM5PR12CA0071.namprd12.prod.outlook.com (2603:10b6:3:103::33) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.2979.28 via Frontend
 Transport; Wed, 6 May 2020 13:18:13 +0000
X-Mailer: git-send-email 1.8.3.1
X-Originating-IP: [165.204.78.2]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: aa30d1ed-7187-432f-1d25-08d7f1bfee41
X-MS-TrafficTypeDiagnostic: DM5PR12MB1258:|DM5PR12MB1258:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM5PR12MB1258C7AB76E7CD2F1627CBBAF3A40@DM5PR12MB1258.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:5797;
X-Forefront-PRVS: 03950F25EC
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 woCpf5rMpKquxVwBPccdASWdqALHeDcrZV469u/YUg16pPmZDHl+XbT7P/qxsGixC2PL9rVxyM+G9MMjl/8RsqapDyiYaiZ+UziM710FS5bGuILSHrrhwhAIz3WXHLad2LVjC9bDENIYQYYpWjA+usRGIp6NRUIg7NZpdQcw/FTagg+U1VWRM4X7ZYGedddaxZ+WCynqiDf8sesQsXrOjjybK7g6FxccjHHQ6fumVs3cGhoXPM/IE2p2hjpR1Wss2mJlwvK3aASKHXXkyBU1QJ8G78JI3XHdBtw1FkMD+lSduicSX8pVJeJ23cZ4SBnrNiZkU0JUp98d//4mi/tySwtSVVyID0vUvLXz1EPBhI1xBLlwHzpt8FBVWVUay+v5xn871HWjMJ80xkFi+ENagmh7J7kdmRwNbaVCTw3aC2g2HWAFSfyMShmaUCsXAUG0chu/lkGS0OJg6WD3QJiEpMArQOg/V5XlHpTPAheBY1TEndYO8g47fKAvBXrX1JDsehQ16osm1chnaLJpcAtvhg==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM5PR12MB1163.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFTY:;SFS:(4636009)(366004)(39860400002)(376002)(136003)(396003)(346002)(33430700001)(4744005)(5660300002)(66556008)(66476007)(66946007)(7696005)(52116002)(8676002)(478600001)(8936002)(44832011)(6666004)(2906002)(2616005)(956004)(6486002)(86362001)(316002)(33440700001)(26005)(16526019)(186003)(36756003)(4326008);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 FmCoi+XAtpKOKCUgBSPYUkKicDaDzGU6ybCYrb7303KCho29MsVEE/EmG6CDNlt09fJOM5sTY1HR5YxDMOhXmgfpxpj0B7KyU1slO00lZmeu1upHf1oLyvuDR8TqXukbblI9VrJALNt3R4YZDu3VZNTxPn51G9OgsnvVezZwSDl8KKLR1GuGr979Img1DI4B52+okNLF3OYvFqOJK1wMxRg8O8h1uPQTTl6+APBEPzBRr4DYQU8AD2440Iv7bPnktwoHV/CPzLXT7W5/KCfVpzHYDrChF8ro9E9BqrfS7zAT0woON99K5bkazcYAWeQttRdXTRzV5X6q6HGC1ZIMFEPYSa0uHV1P0tVd6g46pZ+uGUCvTZFBcbybrVn0PyylWzUer88fLlCo7UMpslYjk35T+yUAcVwLJvADiqa4dy3t5/rCTnoVYjktB84QGIV8cCW5V5u7ueIgvg0fnuihVsPXE7UeXQ34XU9ibHUuOjBXTtPoo4ryIpPehki8zVqAscuHNMmrmL0GFVwuhr+AXAWSdADFnOU4bblXM+bLQZGludkpyTlZPWS3Zs/VJvlctGVsXbk00IuvjxtAZ/9PD56/My1MKWqmryoFeD/sCwygi1jzm3Xnly53mJBRbQwLsJKLCILAEs+hzDhnLWdfduY8B7XeT5J4O6rgFa+SHBSSbElWQolB9RHv2JPMyVGwtu5LPCyHUpMwHmARD45rgcqX0suy/CkumxGMnXm/zlbQc0GDznpL1Tu9Bk7nly5EaipW+YfHVr27slw30UhGds6gsR9NYMONV6GeGa7pZfo=
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 aa30d1ed-7187-432f-1d25-08d7f1bfee41
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 06 May 2020 13:18:13.7765
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 FqR3QiAgo2gfaI9LfQg3YpL4VPjArgrBaWYKDYwF5jn8ToWytaR4p0U2BiYnSuRs23a8owCAf4LZjFUn44JmVg==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM5PR12MB1258
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Introduce kvm_make_all_cpus_request_except(), which is used
in the subsequent patch 2 to fix AVIC warning.

Also include miscelleneous clean ups.

Thanks,
Suravee

Suravee Suthikulpanit (4):
  KVM: Introduce kvm_make_all_cpus_request_except()
  KVM: SVM: Fixes setting V_IRQ while AVIC is still enabled
  KVM: SVM: Merge svm_enable_vintr into svm_set_vintr
  KVM: SVM: Remove unnecessary V_IRQ unsetting

 arch/x86/include/asm/kvm_host.h |  2 +-
 arch/x86/kvm/hyperv.c           |  6 ++++--
 arch/x86/kvm/i8254.c            |  4 ++--
 arch/x86/kvm/svm/avic.c         |  2 +-
 arch/x86/kvm/svm/svm.c          | 18 ++++++------------
 arch/x86/kvm/x86.c              | 16 +++++++++++++---
 include/linux/kvm_host.h        |  3 +++
 virt/kvm/kvm_main.c             | 14 +++++++++++---
 8 files changed, 41 insertions(+), 24 deletions(-)
```
#### [PATCH v5 0/7] KVM: VMX: Tscdeadline timer emulation fastpath
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
From patchwork Wed May  6 16:10:41 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11531473
Return-Path: <SRS0=qN9b=6U=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4DAC21392
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 May 2020 16:10:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 35EA2208DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 May 2020 16:10:58 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="KZSIRiTf"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729966AbgEFQKy (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 6 May 2020 12:10:54 -0400
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:56751 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1729505AbgEFQKy (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 6 May 2020 12:10:54 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1588781453;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=pK8XLGVgtLQ7Wuz0EniH4HZPeCKMh3d83lQPtPWl3h4=;
        b=KZSIRiTfeG5+JQd21pzLmD5rvJSkgKExANGQGD6F7BeL+UpNWzMUxlkxV6X7owbyRBDgD0
        iSPOMheFXJeYKgEih73qDoxVK/YWM+mkkPgGrt+xsPFpZI3FYi7zJwFYexubvGex5UHGIa
        ijh/Dp2L43ZcRix3Xi4MmlIHrOGj6qI=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-411-fmYHDPn_MOGx2iku1zuVsg-1; Wed, 06 May 2020 12:10:51 -0400
X-MC-Unique: fmYHDPn_MOGx2iku1zuVsg-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 522021842D22;
        Wed,  6 May 2020 16:10:50 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 04949165F6;
        Wed,  6 May 2020 16:10:48 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: wanpengli@tencent.com, linxl3@wangsu.com
Subject: [PATCH v5 0/7] KVM: VMX: Tscdeadline timer emulation fastpath
Date: Wed,  6 May 2020 12:10:41 -0400
Message-Id: <20200506161048.28840-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is my cleaned up version of Wanpeng's TSC deadline timer
optimizations.  The main change is a reorganization of the fast
path enums, removing EXIT_FASTPATH_SKIP_EMUL_INS (following the
suggestion of 林鑫龙) and renaming EXIT_FASTPATH_NOP to
EXIT_FASTPATH_EXIT_HANDLED.

Paolo Bonzini (1):
  KVM: x86: introduce kvm_can_use_hv_timer

Wanpeng Li (6):
  KVM: VMX: Introduce generic fastpath handler
  KVM: X86: Introduce kvm_vcpu_exit_request() helper
  KVM: X86: Introduce more exit_fastpath_completion enum values
  KVM: VMX: Optimize posted-interrupt delivery for timer fastpath
  KVM: X86: TSCDEADLINE MSR emulation fastpath
  KVM: VMX: Handle preemption timer fastpath

 arch/x86/include/asm/kvm_host.h |  4 +-
 arch/x86/kvm/lapic.c            | 31 ++++++++++-----
 arch/x86/kvm/lapic.h            |  2 +-
 arch/x86/kvm/svm/svm.c          | 15 ++++---
 arch/x86/kvm/vmx/vmx.c          | 69 +++++++++++++++++++++++----------
 arch/x86/kvm/x86.c              | 45 +++++++++++++++------
 arch/x86/kvm/x86.h              |  3 +-
 virt/kvm/kvm_main.c             |  1 +
 8 files changed, 118 insertions(+), 52 deletions(-)
```
#### [PATCH v4 0/1] vfio-ccw: Enable transparent CCW IPL from DASD
##### From: Jared Rossi <jrossi@linux.ibm.com>

```c
From patchwork Wed May  6 21:24:39 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jared Rossi <jrossi@linux.ibm.com>
X-Patchwork-Id: 11531901
Return-Path: <SRS0=qN9b=6U=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2C11815E6
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 May 2020 21:22:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1E0112076D
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 May 2020 21:22:13 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729596AbgEFVWM (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 6 May 2020 17:22:12 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:62404 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1729261AbgEFVWM (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 6 May 2020 17:22:12 -0400
Received: from pps.filterd (m0098399.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 046L2enM143800;
        Wed, 6 May 2020 17:22:11 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 30u8srveeu-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 06 May 2020 17:22:11 -0400
Received: from m0098399.ppops.net (m0098399.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 046L3rlX148174;
        Wed, 6 May 2020 17:22:11 -0400
Received: from ppma04dal.us.ibm.com (7a.29.35a9.ip4.static.sl-reverse.com
 [169.53.41.122])
        by mx0a-001b2d01.pphosted.com with ESMTP id 30u8srveef-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 06 May 2020 17:22:11 -0400
Received: from pps.filterd (ppma04dal.us.ibm.com [127.0.0.1])
        by ppma04dal.us.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 046LKkBO004196;
        Wed, 6 May 2020 21:22:10 GMT
Received: from b03cxnp07028.gho.boulder.ibm.com
 (b03cxnp07028.gho.boulder.ibm.com [9.17.130.15])
        by ppma04dal.us.ibm.com with ESMTP id 30s0g75hm5-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 06 May 2020 21:22:10 +0000
Received: from b03ledav005.gho.boulder.ibm.com
 (b03ledav005.gho.boulder.ibm.com [9.17.130.236])
        by b03cxnp07028.gho.boulder.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 046LM8kP51052986
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 6 May 2020 21:22:08 GMT
Received: from b03ledav005.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 958A1BE051;
        Wed,  6 May 2020 21:22:08 +0000 (GMT)
Received: from b03ledav005.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 8C6A9BE053;
        Wed,  6 May 2020 21:22:07 +0000 (GMT)
Received: from localhost.localdomain.com (unknown [9.85.180.129])
        by b03ledav005.gho.boulder.ibm.com (Postfix) with ESMTP;
        Wed,  6 May 2020 21:22:07 +0000 (GMT)
From: Jared Rossi <jrossi@linux.ibm.com>
To: Eric Farman <farman@linux.ibm.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Halil Pasic <pasic@linux.ibm.com>
Cc: linux-s390@vger.kernel.org, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v4 0/1] vfio-ccw: Enable transparent CCW IPL from DASD
Date: Wed,  6 May 2020 17:24:39 -0400
Message-Id: <20200506212440.31323-1-jrossi@linux.ibm.com>
X-Mailer: git-send-email 2.21.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.216,18.0.676
 definitions=2020-05-06_09:2020-05-05,2020-05-06 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 bulkscore=0 spamscore=0 lowpriorityscore=0 clxscore=1015 mlxscore=0
 mlxlogscore=857 impostorscore=0 adultscore=0 suspectscore=0 phishscore=0
 malwarescore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2003020000 definitions=main-2005060170
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Remove the explicit prefetch check when using vfio-ccw devices.
This check does not trigger in practice as all Linux channel programs
are intended to use prefetch.

Version 4 makes only stylistic and word choice changes to comments
and/or documentation.

Jared Rossi (1):
  vfio-ccw: Enable transparent CCW IPL from DASD

 Documentation/s390/vfio-ccw.rst |  6 ++++++
 drivers/s390/cio/vfio_ccw_cp.c  | 19 ++++++++++++-------
 2 files changed, 18 insertions(+), 7 deletions(-)
```
#### [PATCH 0/2] arch/x86: Enable MPK feature on AMD
##### From: Babu Moger <babu.moger@amd.com>

```c
From patchwork Wed May  6 22:02:05 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Babu Moger <babu.moger@amd.com>
X-Patchwork-Id: 11531955
Return-Path: <SRS0=qN9b=6U=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3FCBC1392
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 May 2020 22:02:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1D3FA2082E
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 May 2020 22:02:18 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="kXoLUz3I"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729956AbgEFWCR (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 6 May 2020 18:02:17 -0400
Received: from mail-dm6nam10on2082.outbound.protection.outlook.com
 ([40.107.93.82]:62529
        "EHLO NAM10-DM6-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1728621AbgEFWCP (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 6 May 2020 18:02:15 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=eg2M+zlp9ix77kwB/sp1kgkxtPp5vNUtwen/FWRs3nk+Fqbxh4waIRkVC2+nSH1Fu7t4/75pUnpTfmzIi+GvH/Xzvw6/OW8gYBV5FMYUAMv9/k1FG06g2vptBZcjtUKaZnXPCWSBM2E+iqsYWX46LPwOHNqljEmPB9lk6xM5v2GR9RrXZwVO6AHLe6PzIvlYjqqfvWRT9F5oi48obJ4H0xLq216/s7Tq2pTkZ5wrCwUpi0LRWbnj8t3SwpSkG9pejgfr0pXT8aE+oQ3tQcOZWU6axR50C023ViBGayVYzF12KaiUZYfNH4qOvH3pjOYE7mS6SrgEBVDj3p1QNP3y5A==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=n0B0d4zYiuLCdvai489BpPWKD9qYym4cwE9fIj18bmo=;
 b=KMPnDei8nPe9PXVAQrFjyQY+Wqhxknkp3fuBemtLDV3TWuNroXaHj5cGo6VcslwlfChYzxHpthe1Q6aJgTHz2OYZApnryYgRRLFwsGzEi3hZZ8iiskj2unvHB5TQv6L2MRH6bDvtGETKxscq5nM3uz6uCfEspHiGTeKpA4+Tsn2Nd4OGh5T4PEbBSAcmlTNxPayaEP94NAevQFlOUMRipl8FXi1SvGqJrkj6lVLU9kUjoRXZV5W06fUh+Zxeq7ZDZTqVbx8/P4ednEijIS0mAnycgUwxiP6Qq5q06Jfj0rC/HxDxxeOrAuCaoem4eQzpL+iKzaUPTMIipPJW6xEhFg==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=n0B0d4zYiuLCdvai489BpPWKD9qYym4cwE9fIj18bmo=;
 b=kXoLUz3ItNmKa627DKuZkdRO8zBjUJI9+FqLCTQq2nItbQGxpzGvOBsKo+28xdndcreZNOALlolpc4sfzgfkl+RkS8X8ykJ1sc8du9dcRla/gCNdkPpE3tUbqyykPYqBVKx2WvB4+OOPxkqTWHfcVhwLbwtqofIV4qDoLPyEFLM=
Authentication-Results: tencent.com; dkim=none (message not signed)
 header.d=none;tencent.com; dmarc=none action=none header.from=amd.com;
Received: from SN1PR12MB2560.namprd12.prod.outlook.com (2603:10b6:802:26::19)
 by SN1PR12MB2512.namprd12.prod.outlook.com (2603:10b6:802:31::14) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.2979.26; Wed, 6 May
 2020 22:02:08 +0000
Received: from SN1PR12MB2560.namprd12.prod.outlook.com
 ([fe80::c0f:2938:784f:ed8d]) by SN1PR12MB2560.namprd12.prod.outlook.com
 ([fe80::c0f:2938:784f:ed8d%7]) with mapi id 15.20.2979.028; Wed, 6 May 2020
 22:02:08 +0000
Subject: [PATCH 0/2] arch/x86: Enable MPK feature on AMD
From: Babu Moger <babu.moger@amd.com>
To: corbet@lwn.net, tglx@linutronix.de, mingo@redhat.com, bp@alien8.de,
        hpa@zytor.com, pbonzini@redhat.com, sean.j.christopherson@intel.com
Cc: x86@kernel.org, vkuznets@redhat.com, wanpengli@tencent.com,
        jmattson@google.com, joro@8bytes.org, dave.hansen@linux.intel.com,
        luto@kernel.org, peterz@infradead.org, mchehab+samsung@kernel.org,
        babu.moger@amd.com, changbin.du@intel.com, namit@vmware.com,
        bigeasy@linutronix.de, yang.shi@linux.alibaba.com,
        asteinhauser@google.com, anshuman.khandual@arm.com,
        jan.kiszka@siemens.com, akpm@linux-foundation.org,
        steven.price@arm.com, rppt@linux.vnet.ibm.com, peterx@redhat.com,
        dan.j.williams@intel.com, arjunroy@google.com, logang@deltatee.com,
        thellstrom@vmware.com, aarcange@redhat.com, justin.he@arm.com,
        robin.murphy@arm.com, ira.weiny@intel.com, keescook@chromium.org,
        jgross@suse.com, andrew.cooper3@citrix.com,
        pawan.kumar.gupta@linux.intel.com, fenghua.yu@intel.com,
        vineela.tummalapalli@intel.com, yamada.masahiro@socionext.com,
        sam@ravnborg.org, acme@redhat.com, linux-doc@vger.kernel.org,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Date: Wed, 06 May 2020 17:02:05 -0500
Message-ID: <158880240546.11615.2219410169137148044.stgit@naples-babu.amd.com>
User-Agent: StGit/unknown-version
X-ClientProxiedBy: SN4PR0501CA0049.namprd05.prod.outlook.com
 (2603:10b6:803:41::26) To SN1PR12MB2560.namprd12.prod.outlook.com
 (2603:10b6:802:26::19)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from naples-babu.amd.com (165.204.78.2) by
 SN4PR0501CA0049.namprd05.prod.outlook.com (2603:10b6:803:41::26) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.2979.16 via Frontend
 Transport; Wed, 6 May 2020 22:02:06 +0000
X-Originating-IP: [165.204.78.2]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 0d58689f-ab94-4574-d1d4-08d7f2091e9c
X-MS-TrafficTypeDiagnostic: SN1PR12MB2512:|SN1PR12MB2512:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SN1PR12MB251213DBF887E0BCC0D386FF95A40@SN1PR12MB2512.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:8273;
X-Forefront-PRVS: 03950F25EC
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 FgTxiOq1gkmanrhkn5E3a6lNsx5TyOmSlRBgs15HXd++JNtfea/IRHoCAKt7Iy+DQG+Bhj1dXeQk3pktRU29eAiomH13THHsqkSL6rGR2IL862c4mQTAUytHNJUyzxHCIlvuboaCL4LO5iomKhqfTp7iukobiGdSisMZK3f8Fvku+/XgKQ8NRFJQzyqcxh5lruypiTKuvKpcLpM687bU7FhwO7URG45OAm0Sv2v7gwHS8pJUY7PCe/FTJ580c7UagZ5w4WN4M5x2gbLWwTg7/wQAU3jC6l2IO1bm+lBQCSodSdsIk6+mQhJ7Ijn+6ypM89oljFfYJLjq8/USjxOyQJSblE2SxXkVkdJNv/ChOQY+kyTaFseRJqv1Yb34OD0WqnzQ05UeFauZBO1xNB6r+5eMHif3ahOjf/MGB7fxGdpMEWQDhWyw/C1REeaoy+O6/pyha1n64NPEBqb+Q9QYiHuNbp0efZMAbC5UIlgNf7Y3kb3OOplK2xF3usNkIzToA2a5oaLarKH4WhcYYTKdPpzWKxJI4xVuw16AWQRVm/r/fbg2EDSySksWJxfD20cdfInBAeTHKGTfbvYSHtdVcwZjq+e2UJLM3RA8o/s/SNQ=
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN1PR12MB2560.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFTY:;SFS:(4636009)(346002)(376002)(136003)(39860400002)(396003)(366004)(33430700001)(26005)(52116002)(7696005)(4326008)(2906002)(8936002)(33440700001)(66476007)(66556008)(8676002)(16526019)(478600001)(55016002)(186003)(103116003)(966005)(316002)(86362001)(956004)(66946007)(7416002)(7406005)(5660300002)(44832011);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 ef5KWZ+BtRCMXIB2ah/x7gGLXVgnvCRYH3/8lzFygbrzy6twyzyjCZeOgVwvRRPQcoFV3rreu2XiUhU0knjWlRg3ejq1xoi/iL3oKMBWJayfUwXhLGXItRYNXBHTbgcZsZwUsm77Q/wsFgAnvUPZX8mRVvKeDzmKuQOz6skqXUB1KuV/RKsF3UuvsVjhN1BheXkEDWQfanUT3SuXpg2Xwyc5yoEe+jM4aTmhxxV5AasDbAeuwVVYpG9MI9WYmKQbe0pyoX9XmJFBiqs2Ze87WCAr3gncV9vmvf9WpOUk7bfzFIJZuEhQTS58rPspwoPgajWGNoqz0GMC/HqKDFXEZ1KaQh73m6pGeMqVnuc2v5DA/ELXjSyow0sQFrTcpN4LCsbJ4GcAZZ1vjZQFvhkfPzXnj9lPnr+vWKbnFyBy5srcu0JnGf0a9aRTPYO1gX578vySo1SHQI72UhBjCntrl31yvl3+WjwipuyaxeI5cAiKAS9UqJR6tjOdD8BCkKZR0UKycqVl9HwPKJEnFPwTtfPFXyhZa8QpRRbPRx3tUuM6WgWHF7iKLyHC+1tyQl69/pDTXJZz2FfM1Cxn4xhS0irEhXqIsBVVHZR9QmkLSQsNsP0UdXO84SHO0OPd3VCsas7604RG2jG5BJWnXB6kxlT0yTg6f8V3IQlzPAsjbXkU/mxfQwJ9aMrioP9o8qKfsqxfHUQCLWwLAJaVKj4vZYlgFe+A93qsbFKQcMl0+1oiQPlDBWDRtqpBIiYtt40rcBLv4JN/wflw2nYImo4WE+GmkCyYgRqcbfeYRxNoZ5E=
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 0d58689f-ab94-4574-d1d4-08d7f2091e9c
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 06 May 2020 22:02:08.2083
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 aEBHNVI3o71Ue51uDAAzU3zx3lqyqJqdb04/JrzgU9EmSsSLTcB6tqEUHYNpT6Fy
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SN1PR12MB2512
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

AMD's next generation of EPYC processors support the MPK (Memory
Protection Keys) feature.

AMD documentation for MPK feature is available at "AMD64 Architecture
Programmer’s Manual Volume 2: System Programming, Pub. 24593 Rev. 3.34,
Section 5.6.6 Memory Protection Keys (MPK) Bit".

The documentation can be obtained at the link below:
https://bugzilla.kernel.org/show_bug.cgi?id=206537

This series enables the feature on AMD and updates config parameters
to reflect the MPK support on generic x86 platforms.
---

Babu Moger (2):
      arch/x86: Rename config X86_INTEL_MEMORY_PROTECTION_KEYS to generic x86
      KVM: SVM: Add support for MPK feature on AMD


 Documentation/core-api/protection-keys.rst     |    3 ++-
 arch/x86/Kconfig                               |    6 +++---
 arch/x86/include/asm/disabled-features.h       |    4 ++--
 arch/x86/include/asm/mmu.h                     |    2 +-
 arch/x86/include/asm/mmu_context.h             |    4 ++--
 arch/x86/include/asm/pgtable.h                 |    4 ++--
 arch/x86/include/asm/pgtable_types.h           |    2 +-
 arch/x86/include/asm/special_insns.h           |    2 +-
 arch/x86/include/uapi/asm/mman.h               |    2 +-
 arch/x86/kernel/cpu/common.c                   |    2 +-
 arch/x86/kvm/svm/svm.c                         |   20 ++++++++++++++++++++
 arch/x86/kvm/svm/svm.h                         |    2 ++
 arch/x86/mm/Makefile                           |    2 +-
 arch/x86/mm/pkeys.c                            |    2 +-
 scripts/headers_install.sh                     |    2 +-
 tools/arch/x86/include/asm/disabled-features.h |    4 ++--
 16 files changed, 43 insertions(+), 20 deletions(-)

--
```
