#### [PATCH] Allow RDTSC and RDTSCP from userspace
##### From: Mike Stunes <mstunes@vmware.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Mike Stunes <mstunes@vmware.com>
X-Patchwork-Id: 11509491
Return-Path: <SRS0=ezuo=6I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 14F4814DD
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Apr 2020 21:19:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id F2BB92098B
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Apr 2020 21:19:09 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726053AbgDXVSk (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 24 Apr 2020 17:18:40 -0400
Received: from ex13-edg-ou-002.vmware.com ([208.91.0.190]:9377 "EHLO
        EX13-EDG-OU-002.vmware.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726027AbgDXVSk (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 24 Apr 2020 17:18:40 -0400
X-Greylist: delayed 904 seconds by postgrey-1.27 at vger.kernel.org;
 Fri, 24 Apr 2020 17:18:40 EDT
Received: from sc9-mailhost3.vmware.com (10.113.161.73) by
 EX13-EDG-OU-002.vmware.com (10.113.208.156) with Microsoft SMTP Server id
 15.0.1156.6; Fri, 24 Apr 2020 14:03:32 -0700
Received: from mstunes-sid.eng.vmware.com (mstunes-sid.eng.vmware.com
 [10.118.100.24])
        by sc9-mailhost3.vmware.com (Postfix) with ESMTP id CBB63405C8;
        Fri, 24 Apr 2020 14:03:35 -0700 (PDT)
From: Mike Stunes <mstunes@vmware.com>
To: <joro@8bytes.org>
CC: <dan.j.williams@intel.com>, <dave.hansen@linux.intel.com>,
        <hpa@zytor.com>, <jgross@suse.com>, <jroedel@suse.de>,
        <jslaby@suse.cz>, <keescook@chromium.org>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <luto@kernel.org>,
        <peterz@infradead.org>, <thellstrom@vmware.com>,
        <thomas.lendacky@amd.com>,
        <virtualization@lists.linux-foundation.org>, <x86@kernel.org>,
        Mike Stunes <mstunes@vmware.com>
Subject: [PATCH] Allow RDTSC and RDTSCP from userspace
Date: Fri, 24 Apr 2020 14:03:16 -0700
Message-ID: <20200424210316.848878-1-mstunes@vmware.com>
X-Mailer: git-send-email 2.26.1
In-Reply-To: <20200319091407.1481-56-joro@8bytes.org>
References: <20200319091407.1481-56-joro@8bytes.org>
MIME-Version: 1.0
Received-SPF: None (EX13-EDG-OU-002.vmware.com: mstunes@vmware.com does not
 designate permitted sender hosts)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Joerg,

I needed to allow RDTSC(P) from userspace and in early boot in order to
get userspace started properly. Patch below.
---
SEV-ES guests will need to execute rdtsc and rdtscp from userspace and
during early boot. Move the rdtsc(p) #VC handler into common code and
extend the #VC handlers.

Signed-off-by: Mike Stunes <mstunes@vmware.com>
---
 arch/x86/boot/compressed/sev-es.c |  4 ++++
 arch/x86/kernel/sev-es-shared.c   | 23 +++++++++++++++++++++++
 arch/x86/kernel/sev-es.c          | 25 ++-----------------------
 3 files changed, 29 insertions(+), 23 deletions(-)

```
#### [PATCH kvmtool v4 6/5] pci: Move legacy IRQ assignment into devices
##### From: Andre Przywara <andre.przywara@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andre Przywara <andre.przywara@arm.com>
X-Patchwork-Id: 11508155
Return-Path: <SRS0=ezuo=6I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E753E92C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Apr 2020 15:17:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D96DC206D7
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Apr 2020 15:17:17 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726698AbgDXPRQ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 24 Apr 2020 11:17:16 -0400
Received: from foss.arm.com ([217.140.110.172]:36830 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727017AbgDXPRQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 24 Apr 2020 11:17:16 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 79CA931B;
        Fri, 24 Apr 2020 08:17:15 -0700 (PDT)
Received: from localhost.localdomain (unknown [172.31.20.19])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 8258C3F68F;
        Fri, 24 Apr 2020 08:17:14 -0700 (PDT)
From: Andre Przywara <andre.przywara@arm.com>
To: Will Deacon <will@kernel.org>,
        Julien Thierry <julien.thierry.kdev@gmail.com>
Cc: Alexandru Elisei <alexandru.elisei@arm.com>, kvm@vger.kernel.org,
        kvmarm@lists.cs.columbia.edu
Subject: [PATCH kvmtool v4 6/5] pci: Move legacy IRQ assignment into devices
Date: Fri, 24 Apr 2020 16:17:02 +0100
Message-Id: <20200424151702.4750-1-andre.przywara@arm.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

So far the (legacy) IRQ line for a PCI device is allocated in devices.c,
which should actually not take care of that. Since we allocate all other
device specific resources in the actual device emulation code, the IRQ
should not be something special.

Remove the PCI specific code from devices.c, and move the IRQ line
allocation to the PCI code.
This drops the IRQ line from the VESA device, since it does not use one.

Signed-off-by: Andre Przywara <andre.przywara@arm.com>
---
Hi Will,

this is the patch I mentioned earlier today. Briefly tested on x86 with
the VESA device and on a Juno.

Cheers,
Andre

 devices.c         | 9 ---------
 include/kvm/pci.h | 2 +-
 pci.c             | 6 +++---
 vfio/pci.c        | 2 ++
 virtio/pci.c      | 5 ++---
 5 files changed, 8 insertions(+), 16 deletions(-)

```
#### [PATCH 1/2] vdpa: Support config interrupt in vhost_vdpa
##### From: Zhu Lingshan <lingshan.zhu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhu Lingshan <lingshan.zhu@intel.com>
X-Patchwork-Id: 11507421
Return-Path: <SRS0=ezuo=6I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CFCEF1575
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Apr 2020 10:07:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B8D2A2087E
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Apr 2020 10:07:53 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726876AbgDXKHj (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 24 Apr 2020 06:07:39 -0400
Received: from mga03.intel.com ([134.134.136.65]:53054 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726820AbgDXKHi (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 24 Apr 2020 06:07:38 -0400
IronPort-SDR: 
 3QRZn8TxDp9DC5PVJ2C/qmUf99k0VN7+bG99WQ/7gtLo+6EEoR+K3E3q70LBhJ9Hg/lOrXNNCm
 Jqyk32fPdC/Q==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga004.fm.intel.com ([10.253.24.48])
  by orsmga103.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 24 Apr 2020 03:07:37 -0700
IronPort-SDR: 
 ZUC3A8b3zI0M/td+Xxx0JTIdbdiYd9Jibxh6unfcbZhZLr1F2OykoIohhNPg0q5Zccu27FFXkx
 VWKaScT2L59w==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,311,1583222400";
   d="scan'208";a="280755918"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.240.193.79])
  by fmsmga004.fm.intel.com with ESMTP; 24 Apr 2020 03:07:35 -0700
From: Zhu Lingshan <lingshan.zhu@intel.com>
To: mst@redhat.com, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org,
        linux-kernel@vger.kernel.org, netdev@vger.kernel.org,
        jasowang@redhat.com
Cc: lulu@redhat.com, dan.daly@intel.com, cunming.liang@intel.com,
        Zhu Lingshan <lingshan.zhu@intel.com>
Subject: [PATCH 1/2] vdpa: Support config interrupt in vhost_vdpa
Date: Fri, 24 Apr 2020 18:04:18 +0800
Message-Id: <1587722659-1300-2-git-send-email-lingshan.zhu@intel.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1587722659-1300-1-git-send-email-lingshan.zhu@intel.com>
References: <1587722659-1300-1-git-send-email-lingshan.zhu@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This commit implements config interrupt support in
vhost_vdpa layer.

Signed-off-by: Zhu Lingshan <lingshan.zhu@intel.com>

Signed-off-by: Zhu Lingshan <lingshan.zhu@intel.com>
---
 drivers/vhost/vdpa.c             | 53 ++++++++++++++++++++++++++++++++++++++++
 include/uapi/linux/vhost.h       |  2 ++
 include/uapi/linux/vhost_types.h |  2 ++
 3 files changed, 57 insertions(+)

```
#### [PATCH] docs: virt/kvm: close inline string literal
##### From: Stephen Kitt <steve@sk2.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stephen Kitt <steve@sk2.org>
X-Patchwork-Id: 11508483
Return-Path: <SRS0=ezuo=6I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0FADF81
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Apr 2020 16:03:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 01B6F2075A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Apr 2020 16:03:00 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727088AbgDXQC7 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 24 Apr 2020 12:02:59 -0400
Received: from 10.mo3.mail-out.ovh.net ([87.98.165.232]:33755 "EHLO
        10.mo3.mail-out.ovh.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726698AbgDXQC6 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 24 Apr 2020 12:02:58 -0400
X-Greylist: delayed 1800 seconds by postgrey-1.27 at vger.kernel.org;
 Fri, 24 Apr 2020 12:02:58 EDT
Received: from player694.ha.ovh.net (unknown [10.110.208.89])
        by mo3.mail-out.ovh.net (Postfix) with ESMTP id ACACC24D8D7
        for <kvm@vger.kernel.org>; Fri, 24 Apr 2020 17:27:06 +0200 (CEST)
Received: from sk2.org (82-65-25-201.subs.proxad.net [82.65.25.201])
        (Authenticated sender: steve@sk2.org)
        by player694.ha.ovh.net (Postfix) with ESMTPSA id B3E1C11A58320;
        Fri, 24 Apr 2020 15:26:59 +0000 (UTC)
From: Stephen Kitt <steve@sk2.org>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Jonathan Corbet <corbet@lwn.net>, kvm@vger.kernel.org,
        linux-doc@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, Stephen Kitt <steve@sk2.org>
Subject: [PATCH] docs: virt/kvm: close inline string literal
Date: Fri, 24 Apr 2020 17:26:37 +0200
Message-Id: <20200424152637.120876-1-steve@sk2.org>
X-Mailer: git-send-email 2.25.3
MIME-Version: 1.0
X-Ovh-Tracer-Id: 381117119294557646
X-VR-SPAMSTATE: OK
X-VR-SPAMSCORE: -100
X-VR-SPAMCAUSE: 
 gggruggvucftvghtrhhoucdtuddrgeduhedrhedugdekgecutefuodetggdotefrodftvfcurfhrohhfihhlvgemucfqggfjpdevjffgvefmvefgnecuuegrihhlohhuthemucehtddtnecusecvtfgvtghiphhivghnthhsucdlqddutddtmdenucfjughrpefhvffufffkofgggfestdekredtredttdenucfhrhhomhepufhtvghphhgvnhcumfhithhtuceoshhtvghvvgesshhkvddrohhrgheqnecukfhppedtrddtrddtrddtpdekvddrieehrddvhedrvddtudenucevlhhushhtvghrufhiiigvpedtnecurfgrrhgrmhepmhhouggvpehsmhhtphdqohhuthdphhgvlhhopehplhgrhigvrheileegrdhhrgdrohhvhhdrnhgvthdpihhnvghtpedtrddtrddtrddtpdhmrghilhhfrhhomhepshhtvghvvgesshhkvddrohhrghdprhgtphhtthhopehkvhhmsehvghgvrhdrkhgvrhhnvghlrdhorhhg
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This fixes

	Documentation/virt/kvm/amd-memory-encryption.rst:76: WARNING: Inline literal start-string without end-string.

Fixes: 2da1ed62d55c ("KVM: SVM: document KVM_MEM_ENCRYPT_OP, let userspace detect if SEV is available")
Signed-off-by: Stephen Kitt <steve@sk2.org>
---
 Documentation/virt/kvm/amd-memory-encryption.rst | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v2 01/22] KVM: SVM: introduce nested_run_pending
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11508681
Return-Path: <SRS0=ezuo=6I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E052481
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Apr 2020 17:24:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C69EA20857
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Apr 2020 17:24:38 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="h334Ucv4"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728708AbgDXRYg (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 24 Apr 2020 13:24:36 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:37106 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726849AbgDXRYf (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 24 Apr 2020 13:24:35 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1587749074;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:in-reply-to:in-reply-to:references:references;
        bh=urUA8szmOjF8TY/rJiBW3e0Wg6p5Hv2oHLXiGg8Oq0o=;
        b=h334Ucv46X/K2z4bc0zmZfOJ6U7TUFMM2SuRLQ/HdHo+BrlAvqj4UMesELGwewP0CaoQrW
        dCY/A+p0XZNdqlumU7i1LixhGGYsRM/Mf8wEhYT1iBrZ8zvKtub0BubzFGO573a4bWMYkq
        9xAAbS4HsdEe8GJGU73fzUECvzw3hNM=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-300-0mgY1dxVNxO22Tior9hslg-1; Fri, 24 Apr 2020 13:24:33 -0400
X-MC-Unique: 0mgY1dxVNxO22Tior9hslg-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id AA8371800D42;
        Fri, 24 Apr 2020 17:24:19 +0000 (UTC)
Received: from virtlab511.virt.lab.eng.bos.redhat.com
 (virtlab511.virt.lab.eng.bos.redhat.com [10.19.152.198])
        by smtp.corp.redhat.com (Postfix) with ESMTP id C1E651FDE1;
        Fri, 24 Apr 2020 17:24:18 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: wei.huang2@amd.com, cavery@redhat.com, vkuznets@redhat.com,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Oliver Upton <oupton@google.com>,
        Jim Mattson <jmattson@google.com>
Subject: [PATCH v2 01/22] KVM: SVM: introduce nested_run_pending
Date: Fri, 24 Apr 2020 13:23:55 -0400
Message-Id: <20200424172416.243870-2-pbonzini@redhat.com>
In-Reply-To: <20200424172416.243870-1-pbonzini@redhat.com>
References: <20200424172416.243870-1-pbonzini@redhat.com>
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We want to inject vmexits immediately from svm_check_nested_events,
so that the interrupt/NMI window requests happen in inject_pending_event
right after it returns.

This however has the same issue as in vmx_check_nested_events, so
introduce a nested_run_pending flag with the exact same purpose
of delaying vmexit injection after the vmentry.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/svm/nested.c | 3 ++-
 arch/x86/kvm/svm/svm.c    | 1 +
 arch/x86/kvm/svm/svm.h    | 4 ++++
 3 files changed, 7 insertions(+), 1 deletion(-)

```
#### [PATCH] kvm: ioapic: Introduce arch-specific check for lazy update EOI mechanism
##### From: Suravee Suthikulpanit <suravee.suthikulpanit@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Suravee Suthikulpanit <Suravee.Suthikulpanit@amd.com>
X-Patchwork-Id: 11507111
Return-Path: <SRS0=ezuo=6I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F0773912
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Apr 2020 05:08:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CB0052084D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Apr 2020 05:08:54 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="lFy/OICp"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726051AbgDXFIv (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 24 Apr 2020 01:08:51 -0400
Received: from mail-co1nam11on2073.outbound.protection.outlook.com
 ([40.107.220.73]:15676
        "EHLO NAM11-CO1-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1725554AbgDXFIv (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 24 Apr 2020 01:08:51 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=RqzRonsEAzTAqQ7hmAvA4i4lhTKmBedvrC8AwVYZWLHwYmBw0qJzTY7vMYKfVLmrcwwyxg53cbgeBZkjgjGD6OwUUlgYk9invoiXM6CYm10E5UB33eIxNTCE5OPGjeb1VwcxvdQd7RnzvKukfiofN20BaUF+S6WJwNC22cydxa0Ja+0nQNuixb+K5PQMNPodMkf0Bt7iqLSBDZNOtZQK6GD1ppvzIDKkiPXk+fOufxj7LOK4cgg0S4VNQn4Hmok+FuQ867D2WuVwoizugAHbNKvqeZcMTeEleMjH/QnOb8UFbQpl5wcNCEfkAUC8PkcK9t95PcUj2HZl8D0lLQM7FA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=IP2CZ7pzXxK0RMTbJf8T6eEjCMMjTv9AVYwT14Rf+/I=;
 b=acPuUYllbZ/zONZN9M6FMWGA2W2Upb3S/T9vMls3g803GoSn+7McWQpcgSR0Hp55V9CY7bBoA37epL7a0fWOoK1WNaycqA/0RfacpqH+R/WPk2U93NcZ3u4ufw1aIEPhBovHrD5aeWfvxTAGtiz4/uBixCEfsA4v40++4f3hd3CJhsxKNsYBDUBfsj1lv/Fro83hTEuJQlK0oS1ScgtJMjc6M6gqdJFtWHXkM+xhBbxjPng3fwr0+KiHc4P8Kc8jvfSDZ/4h9/9zBZoa0KDrZA57k1g996qPulAGVrctNW8tT7QbS9A+GgoKVTL0EnFe87ZH3k/r3aDQGqKyoGPuyw==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=IP2CZ7pzXxK0RMTbJf8T6eEjCMMjTv9AVYwT14Rf+/I=;
 b=lFy/OICpliSgG8ldYAyuC8//sxxOeScu/EzYtzBkyHw8NmCy/XpitxfO+UI+OAw1OBfSBBXzg66XN7a2KaT0hktOADuRmVihvULykAKxFU5THfkBdQ4nSlDEddQ2g5teUAH1chRZcCWylWjw4E0ZQ2Mtf6DRSWoY3XejIr81cpQ=
Authentication-Results: spf=none (sender IP is )
 smtp.mailfrom=Suravee.Suthikulpanit@amd.com;
Received: from DM5PR12MB1163.namprd12.prod.outlook.com (2603:10b6:3:7a::18) by
 DM5PR12MB2423.namprd12.prod.outlook.com (2603:10b6:4:b3::30) with Microsoft
 SMTP Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.2937.13; Fri, 24 Apr 2020 05:08:47 +0000
Received: from DM5PR12MB1163.namprd12.prod.outlook.com
 ([fe80::d061:4c5:954e:4744]) by DM5PR12MB1163.namprd12.prod.outlook.com
 ([fe80::d061:4c5:954e:4744%4]) with mapi id 15.20.2921.035; Fri, 24 Apr 2020
 05:08:47 +0000
From: Suravee Suthikulpanit <suravee.suthikulpanit@amd.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: pbonzini@redhat.com, rkrcmar@redhat.com, joro@8bytes.org,
        jon.grimm@amd.com, borisvk@bstnet.org,
        Suravee Suthikulpanit <suravee.suthikulpanit@amd.com>
Subject: [PATCH] kvm: ioapic: Introduce arch-specific check for lazy update
 EOI mechanism
Date: Fri, 24 Apr 2020 00:08:30 -0500
Message-Id: <1587704910-78437-1-git-send-email-suravee.suthikulpanit@amd.com>
X-Mailer: git-send-email 1.8.3.1
X-ClientProxiedBy: DM5PR07CA0104.namprd07.prod.outlook.com
 (2603:10b6:4:ae::33) To DM5PR12MB1163.namprd12.prod.outlook.com
 (2603:10b6:3:7a::18)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from ssuthiku-rhel7-ssp.amd.com (165.204.78.2) by
 DM5PR07CA0104.namprd07.prod.outlook.com (2603:10b6:4:ae::33) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.2937.13 via Frontend
 Transport; Fri, 24 Apr 2020 05:08:46 +0000
X-Mailer: git-send-email 1.8.3.1
X-Originating-IP: [165.204.78.2]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 18122522-78fb-4538-0981-08d7e80d9195
X-MS-TrafficTypeDiagnostic: DM5PR12MB2423:|DM5PR12MB2423:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM5PR12MB24238EB315CD373C607495B6F3D00@DM5PR12MB2423.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:2958;
X-Forefront-PRVS: 03838E948C
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM5PR12MB1163.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFTY:;SFS:(4636009)(136003)(376002)(346002)(39860400002)(366004)(396003)(966005)(6486002)(8936002)(8676002)(26005)(81156014)(52116002)(478600001)(7696005)(2906002)(86362001)(186003)(16526019)(6666004)(316002)(5660300002)(44832011)(2616005)(36756003)(956004)(4326008)(66556008)(66946007)(15650500001)(66476007);DIR:OUT;SFP:1101;
Received-SPF: None (protection.outlook.com: amd.com does not designate
 permitted sender hosts)
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 BUUxStpv4e7ynDEbCwaNKQ/b1qEylmx20p8uU5c7BeVi3yR4Wt12KwtlGYcuIYR+cQqXlUSCxQ+zVT47Obwr8xQDnz2MhSFfAAIXEq9i2zHXg5LRJtqubr7P2t314NNKt3XJqhbZK4zxlfD5lkxhDg5ob2Zb/Vg+9HSsDri6qQpjQ+aqtpj+xL2j87Dnc90tnhwjthSqat9mN1+KM4LQa0SaKbHCZXxQulJRhiHfMaeaL9ZlSjK10U5rg/hSBhviBl5RZhaKR5Zqsewi4J/F5N7w0gdXIxxAdnF+tPZvOdVbm8hlItznR65lgqu9F5KiuXj93MW9M8qHugnmcmFkA3lMrOmFvxWll/5fo8CWFXMHwVYBRG/l8ClLq4hgE7hEMiCwNDy7HIYl4af+SUJbkuCWRgnYtxLRINM498087y4D8n9MRtomO9nvbkdQGqHBnCSXuRRS8itfeeVX6NaZSCenF/lC/BzNIWyimGZhzVAjgqIUbiNzb/uy4+BgKQWLw4fgmz5hvWuu9RTGPIy//g==
X-MS-Exchange-AntiSpam-MessageData: 
 ZMty4Tj2xP/AN0m7zveIV2BBdz0F3Y/oljBtyTvi2j6V3mQ6fLH3mc1fJq7qPMbIjCFoAxO70LPPoIC+zK+VnQbZe4kX7ae/bVcgP9NxMGJxIecn9SGsV/dVcrLKTISbYr+J8WmSBrpLJKlxSIrG7A==
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 18122522-78fb-4538-0981-08d7e80d9195
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 24 Apr 2020 05:08:47.3595
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 3nFjPUZ7oiUcwl+oj8iZkAXW7neVtul+gKCLnjBOD2/ee7dREPBl//ubwKQpwcZQZ5q310NJpkpqVepsSgm7hw==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM5PR12MB2423
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

commit f458d039db7e ("kvm: ioapic: Lazy update IOAPIC EOI") introduces
the following regression on Intel VMX APICv.

BUG: stack guard page was hit at 000000008f595917 \
(stack is 00000000bdefe5a4..00000000ae2b06f5)
kernel stack overflow (double-fault): 0000 [#1] SMP NOPTI
RIP: 0010:kvm_set_irq+0x51/0x160 [kvm]
Call Trace:
 irqfd_resampler_ack+0x32/0x90 [kvm]
 kvm_notify_acked_irq+0x62/0xd0 [kvm]
 kvm_ioapic_update_eoi_one.isra.0+0x30/0x120 [kvm]
 ioapic_set_irq+0x20e/0x240 [kvm]
 kvm_ioapic_set_irq+0x5c/0x80 [kvm]
 kvm_set_irq+0xbb/0x160 [kvm]
 ? kvm_hv_set_sint+0x20/0x20 [kvm]
 irqfd_resampler_ack+0x32/0x90 [kvm]
 kvm_notify_acked_irq+0x62/0xd0 [kvm]
 kvm_ioapic_update_eoi_one.isra.0+0x30/0x120 [kvm]
 ioapic_set_irq+0x20e/0x240 [kvm]
 kvm_ioapic_set_irq+0x5c/0x80 [kvm]
 kvm_set_irq+0xbb/0x160 [kvm]
 ? kvm_hv_set_sint+0x20/0x20 [kvm]
....

This is due to the logic always force IOAPIC lazy update EOI mechanism
when APICv is activated, which is only needed by AMD SVM AVIC.

Fixes by introducing struct kvm_arch.use_lazy_eoi variable to specify
whether the architecture needs lazy update EOI support.

Reported-by: borisvk@bstnet.org
Link: https://www.spinics.net/lists/kvm/msg213512.html
Fixes: f458d039db7e ("kvm: ioapic: Lazy update IOAPIC EOI")
Signed-off-by: Suravee Suthikulpanit <suravee.suthikulpanit@amd.com>
---
 arch/x86/include/asm/kvm_host.h | 2 ++
 arch/x86/kvm/ioapic.c           | 5 +++--
 arch/x86/kvm/svm/svm.c          | 8 ++++++++
 3 files changed, 13 insertions(+), 2 deletions(-)

```
#### [PATCH V2 01/14] KVM: MIPS: Define KVM_ENTRYHI_ASID to cpu_asid_mask(&boot_cpu_data)
##### From: Huacai Chen <chenhc@lemote.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Huacai Chen <chenhc@lemote.com>
X-Patchwork-Id: 11507549
Return-Path: <SRS0=ezuo=6I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F39C917EA
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Apr 2020 11:06:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DA7F520736
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Apr 2020 11:06:48 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="tI7YDPXr"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726872AbgDXLGs (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 24 Apr 2020 07:06:48 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:38980 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726289AbgDXLGs (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 24 Apr 2020 07:06:48 -0400
Received: from mail-pl1-x642.google.com (mail-pl1-x642.google.com
 [IPv6:2607:f8b0:4864:20::642])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id E6866C09B045;
        Fri, 24 Apr 2020 04:06:47 -0700 (PDT)
Received: by mail-pl1-x642.google.com with SMTP id v2so3606079plp.9;
        Fri, 24 Apr 2020 04:06:47 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id:in-reply-to:references;
        bh=PbRSEAf2iP4s0AdgPIwTBI8UU6TRpGo2RmWTv12T7ho=;
        b=tI7YDPXrk0NS/QGz2+TanWURFuX4q+QSV6t/XrOp2ZC2U9/QeUh/S37qIZB5rnRPjb
         EDOUQrMldyMGZmpEvRZAtRdBcfXkuWvFwQaQ47ZhC38vly6rGgU24tXvUxcwVBL3fVhD
         jgKoM5yKiK7AxXYfhCynTlqMrReVId3Hd3CkLTudAJnsqkHi123QRU41/P8Og1OYVRZP
         DOq0wVZs+qN1GhkAf8wsZKztwnFz/nZdHg17OoVFAnOi3e5a7v6ZuFl6v82WEMy+7edE
         symx6Qj6IBlV00vGtJ/1sfFIVZH2BxpW4NRYQ0IRFWcny7bNXEq/piEmVY9rqhtAh7dc
         r7ng==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id
         :in-reply-to:references;
        bh=PbRSEAf2iP4s0AdgPIwTBI8UU6TRpGo2RmWTv12T7ho=;
        b=joM7wF+gab8IyuzMD069Vp/wBCGqdCZPc0buVp8JeLJf8+H5gdwISRd5GAPhrdC4WP
         AqmhBzLlN7Qqhdd5T06lVtg/i5lD+PSGl6nl6JHlXJEEboKYZpeb0akstE0LqwUymMKV
         o/uKzdyTwGH7d4LrFp2MqqpqOhztzzjX1LapFxJUH+8WW8ySKg92QRNP7AmM0pzrInrS
         MiFAXEytjbYDhjzK8rhgH7kiYvR3w/NdKviGsFcBh7Ggvt9Q0o0bDzQ9lej1DdgHPQuA
         XET+ufZLIoh4QwjU0x548nEhAbUVOk320jlJpoieX5XRtpvw+CKEdZ+5FC6TliVMRJeN
         v2FQ==
X-Gm-Message-State: AGi0PuZQ+eFik7zn+z157J55BxXHVRDXUuhy8yMfHVUNnqUdZj9fmPj/
        Svbus/1PIBEIfWe4oPlD2hUrncuzmAo=
X-Google-Smtp-Source: 
 APiQypIeKfPUIaMdSUZT4R8efpeU1guWS/zOvrO3qTYIBnTd+jwlffLhauGQ3JW+CjQgTc5B1I6nSQ==
X-Received: by 2002:a17:90a:270d:: with SMTP id
 o13mr5612686pje.34.1587726407471;
        Fri, 24 Apr 2020 04:06:47 -0700 (PDT)
Received: from software.domain.org (28.144.92.34.bc.googleusercontent.com.
 [34.92.144.28])
        by smtp.gmail.com with ESMTPSA id
 y10sm5470110pfb.53.2020.04.24.04.06.44
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Fri, 24 Apr 2020 04:06:46 -0700 (PDT)
From: Huacai Chen <chenhc@lemote.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Thomas Bogendoerfer <tsbogend@alpha.franken.de>
Cc: kvm@vger.kernel.org, linux-mips@vger.kernel.org,
        Fuxin Zhang <zhangfx@lemote.com>,
        Huacai Chen <chenhuacai@gmail.com>,
        Jiaxun Yang <jiaxun.yang@flygoat.com>,
        Xing Li <lixing@loongson.cn>, stable@vger.kernel.org,
        Huacai Chen <chenhc@lemote.com>
Subject: [PATCH V2 01/14] KVM: MIPS: Define KVM_ENTRYHI_ASID to
 cpu_asid_mask(&boot_cpu_data)
Date: Fri, 24 Apr 2020 19:15:20 +0800
Message-Id: <1587726933-31757-2-git-send-email-chenhc@lemote.com>
X-Mailer: git-send-email 2.7.0
In-Reply-To: <1587726933-31757-1-git-send-email-chenhc@lemote.com>
References: <1587726933-31757-1-git-send-email-chenhc@lemote.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Xing Li <lixing@loongson.cn>

The code in decode_config4() of arch/mips/kernel/cpu-probe.c

        asid_mask = MIPS_ENTRYHI_ASID;
        if (config4 & MIPS_CONF4_AE)
                asid_mask |= MIPS_ENTRYHI_ASIDX;
        set_cpu_asid_mask(c, asid_mask);

set asid_mask to cpuinfo->asid_mask.

So in order to support variable ASID_MASK, KVM_ENTRYHI_ASID should also
be changed to cpu_asid_mask(&boot_cpu_data).

Cc: stable@vger.kernel.org
Signed-off-by: Xing Li <lixing@loongson.cn>
[Huacai: Change current_cpu_data to boot_cpu_data for optimization]
Signed-off-by: Huacai Chen <chenhc@lemote.com>
---
 arch/mips/include/asm/kvm_host.h | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] KVM: nVMX: Tweak handling of failure code for nested VM-Enter failure
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11508677
Return-Path: <SRS0=ezuo=6I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 87ACB81
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Apr 2020 17:19:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 698FE2075A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Apr 2020 17:19:31 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727091AbgDXRT2 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 24 Apr 2020 13:19:28 -0400
Received: from mga03.intel.com ([134.134.136.65]:14632 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726813AbgDXRT2 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 24 Apr 2020 13:19:28 -0400
IronPort-SDR: 
 8oDrBcXIfUv4rkGplRme9Xi2fs8fGKbrVaolAZ8Z/gHfiPMC4Z/oOihwMrROPi1lzB3IMhABVj
 +e5aAvNn6J0g==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga006.jf.intel.com ([10.7.209.51])
  by orsmga103.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 24 Apr 2020 10:19:27 -0700
IronPort-SDR: 
 YquaYbCpzuPcEbkFG18XrwTE0QbEwlzOzr7LCqlIXar3KpDE/jHZ7en8cKwOcvDVdUUCM3J6ee
 pXoftvnPaVZw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,311,1583222400";
   d="scan'208";a="259894358"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by orsmga006.jf.intel.com with ESMTP; 24 Apr 2020 10:19:26 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: nVMX: Tweak handling of failure code for nested VM-Enter
 failure
Date: Fri, 24 Apr 2020 10:19:25 -0700
Message-Id: <20200424171925.1178-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Use an enum for passing around the failure code for a failed VM-Enter
that results in VM-Exit to provide a level of indirection from the final
resting place of the failure code, vmcs.EXIT_QUALIFICATION.  The exit
qualification field is an unsigned long, e.g. passing around
'u32 exit_qual' throws up red flags as it suggests KVM may be dropping
bits when reporting errors to L1.  This is a red herring because the
only defined failure codes are 0, 2, 3, and 4, i.e. don't come remotely
close to overflowing a u32.

Setting vmcs.EXIT_QUALIFICATION on entry failure is further complicated
by the MSR load list, which returns the (1-based) entry that failed, and
the number of MSRs to load is a 32-bit VMCS field.  At first blush, it
would appear that overflowing a u32 is possible, but the number of MSRs
that can be loaded is hardcapped at 4096 (limited by MSR_IA32_VMX_MISC).

In other words, there are two completely disparate types of data that
eventually get stuffed into vmcs.EXIT_QUALIFICATION, neither of which is
an 'unsigned long' in nature.  This was presumably the reasoning for
switching to 'u32' when the related code was refactored in commit
ca0bde28f2ed6 ("kvm: nVMX: Split VMCS checks from nested_vmx_run()").

Using an enum for the failure code addresses the technically-possible-
but-will-never-happen scenario where Intel defines a failure code that
doesn't fit in a 32-bit integer.  The enum variables and values will
either be automatically sized (gcc 5.4 behavior) or be subjected to some
combination of truncation.  The former case will simply work, while the
latter will trigger a compile-time warning unless the compiler is being
particularly unhelpful.

Separating the failure code from the failed MSR entry allows for
disassociating both from vmcs.EXIT_QUALIFICATION, which avoids the
conundrum where KVM has to choose between 'u32 exit_qual' and tracking
values as 'unsigned long' that have no business being tracked as such.

Opportunistically rename the variables in load_vmcs12_host_state() and
vmx_set_nested_state() to call out that they're ignored, and add a
comment in nested_vmx_load_msr() to call out that returning 'i + 1'
can't wrap.

No functional change intended.

Reported-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/include/asm/vmx.h | 10 ++++++----
 arch/x86/kvm/vmx/nested.c  | 38 +++++++++++++++++++++-----------------
 2 files changed, 27 insertions(+), 21 deletions(-)

```
#### [PATCH kvmtool v2] vfio: fix multi-MSI vector handling
##### From: Lorenzo Pieralisi <lorenzo.pieralisi@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Lorenzo Pieralisi <lorenzo.pieralisi@arm.com>
X-Patchwork-Id: 11508193
Return-Path: <SRS0=ezuo=6I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CF63613B2
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Apr 2020 15:31:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C1BC220706
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Apr 2020 15:31:29 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726849AbgDXPb2 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 24 Apr 2020 11:31:28 -0400
Received: from foss.arm.com ([217.140.110.172]:37134 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726791AbgDXPb2 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 24 Apr 2020 11:31:28 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 38EE431B;
        Fri, 24 Apr 2020 08:31:28 -0700 (PDT)
Received: from red-moon.arm.com (unknown [10.57.30.150])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 3E6283F68F;
        Fri, 24 Apr 2020 08:31:26 -0700 (PDT)
From: Lorenzo Pieralisi <lorenzo.pieralisi@arm.com>
To: kvm@vger.kernel.org
Cc: Lorenzo Pieralisi <lorenzo.pieralisi@arm.com>,
        Marc Zyngier <maz@kernel.org>, Will Deacon <will@kernel.org>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Jean-Philippe Brucker <jean-philippe@linaro.org>,
        Andre Przywara <andre.przywara@arm.com>,
        Alexandru Elisei <alexandru.elisei@arm.com>
Subject: [PATCH kvmtool v2] vfio: fix multi-MSI vector handling
Date: Fri, 24 Apr 2020 16:31:19 +0100
Message-Id: <20200424153119.16913-1-lorenzo.pieralisi@arm.com>
X-Mailer: git-send-email 2.26.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

A PCI device with a MSI capability enabling Multiple MSI messages
(through the Multiple Message Enable field in the Message Control
register[6:4]) is expected to drive the Message Data lower bits (number
determined by the number of selected vectors) to generate the
corresponding MSI messages writes on the PCI bus.

Therefore, KVM expects the MSI data lower bits (a number of
bits that depend on bits [6:4] of the Message Control
register - which in turn control the number of vectors
allocated) to be set-up by kvmtool while programming the
MSI IRQ routing entries to make sure the MSI entries can
actually be demultiplexed by KVM and IRQ routes set-up
accordingly so that when an actual HW fires KVM can
route it to the correct entry in the interrupt controller
(and set-up a correct passthrough route for directly
injected interrupt).

Current kvmtool code does not set-up Message data entries
correctly for multi-MSI vectors - the data field is left
as programmed in the MSI capability by the guest for all
vector entries, triggering IRQs misrouting.

Fix it.

Signed-off-by: Lorenzo Pieralisi <lorenzo.pieralisi@arm.com>
Acked-by: Marc Zyngier <maz@kernel.org>
Cc: Will Deacon <will@kernel.org>
Cc: Julien Thierry <julien.thierry.kdev@gmail.com>
---
v1 -> v2:
	- Removed superfluous nr_vectors check
	- Added MarcZ ACK
	- Added comment

 vfio/pci.c | 8 ++++++++
 1 file changed, 8 insertions(+)

```
#### [PATCH kvmtool] vfio: fix multi-MSI vector handling
##### From: Lorenzo Pieralisi <lorenzo.pieralisi@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Lorenzo Pieralisi <lorenzo.pieralisi@arm.com>
X-Patchwork-Id: 11507883
Return-Path: <SRS0=ezuo=6I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A294592A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Apr 2020 13:40:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8A2A720767
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Apr 2020 13:40:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726717AbgDXNkd (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 24 Apr 2020 09:40:33 -0400
Received: from foss.arm.com ([217.140.110.172]:34660 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726301AbgDXNkd (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 24 Apr 2020 09:40:33 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id E7F4F31B;
        Fri, 24 Apr 2020 06:40:30 -0700 (PDT)
Received: from red-moon.arm.com (unknown [10.57.30.150])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 B77403F68F;
        Fri, 24 Apr 2020 06:40:29 -0700 (PDT)
From: Lorenzo Pieralisi <lorenzo.pieralisi@arm.com>
To: kvm@vger.kernel.org
Cc: Lorenzo Pieralisi <lorenzo.pieralisi@arm.com>,
        Will Deacon <will@kernel.org>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Marc Zyngier <maz@kernel.org>,
        Jean-Philippe Brucker <jean-philippe@linaro.org>,
        Andre Przywara <andre.przywara@arm.com>,
        Alexandru Elisei <alexandru.elisei@arm.com>
Subject: [PATCH kvmtool] vfio: fix multi-MSI vector handling
Date: Fri, 24 Apr 2020 14:40:24 +0100
Message-Id: <20200424134024.12543-1-lorenzo.pieralisi@arm.com>
X-Mailer: git-send-email 2.26.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

A PCI device with a MSI capability enabling Multiple MSI messages
(through the Multiple Message Enable field in the Message Control
register[6:4]) is expected to drive the Message Data lower bits (number
determined by the number of selected vectors) to generate the
corresponding MSI messages writes on the PCI bus.

Therefore, KVM expects the MSI data lower bits (a number of
bits that depend on bits [6:4] of the Message Control
register - which in turn control the number of vectors
allocated) to be set-up by kvmtool while programming the
MSI IRQ routing entries to make sure the MSI entries can
actually be demultiplexed by KVM and IRQ routes set-up
accordingly so that when an actual HW fires KVM can
route it to the correct entry in the interrupt controller
(and set-up a correct passthrough route for directly
injected interrupt).

Current kvmtool code does not set-up Message data entries
correctly for multi-MSI vectors - the data field is left
as programmed in the MSI capability by the guest for all
vector entries, triggering IRQs misrouting.

Fix it.

Signed-off-by: Lorenzo Pieralisi <lorenzo.pieralisi@arm.com>
Cc: Will Deacon <will@kernel.org>
Cc: Julien Thierry <julien.thierry.kdev@gmail.com>
Acked-by: Marc Zyngier <maz@kernel.org>
---
 vfio/pci.c | 6 ++++++
 1 file changed, 6 insertions(+)

```
#### [kvm-unit-tests PATCH] nVMX: Check EXIT_QUALIFICATION on VM-Enter failures due to bad guest state
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11508735
Return-Path: <SRS0=ezuo=6I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BA93814B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Apr 2020 17:40:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A432420736
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Apr 2020 17:40:28 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728568AbgDXRk1 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 24 Apr 2020 13:40:27 -0400
Received: from mga04.intel.com ([192.55.52.120]:23370 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726813AbgDXRk1 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 24 Apr 2020 13:40:27 -0400
IronPort-SDR: 
 xD0q9w9DnjUbofb9vRRGt4tQJ7nAMiFiCbRYb1fkLBfBYqirpDHjs9rr3TBIhp8cD1PkOguJ4a
 kQJ+aN3l320w==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga002.fm.intel.com ([10.253.24.26])
  by fmsmga104.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 24 Apr 2020 10:40:27 -0700
IronPort-SDR: 
 GOeV/tdjEBx6hImgR2esH83Sn2tQx8ViXHQflHKpyHcrspy0GE57b+/qwdbsN1L2YDmiC9GDFz
 nXduDFMiNTnw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,311,1583222400";
   d="scan'208";a="291651846"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by fmsmga002.fm.intel.com with ESMTP; 24 Apr 2020 10:40:26 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org,
        Sean Christopherson <sean.j.christopherson@intel.com>
Subject: [kvm-unit-tests PATCH] nVMX: Check EXIT_QUALIFICATION on VM-Enter
 failures due to bad guest state
Date: Fri, 24 Apr 2020 10:40:25 -0700
Message-Id: <20200424174025.1379-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Assert that vmcs.EXIT_QUALIFICATION contains the correct failure code on
failed VM-Enter due to invalid guest state.  Hardcode the expected code
to the default code, '0', rather than passing in the expected code to
minimize churn and boilerplate code, which works for all existing tests.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 x86/vmx.h       | 7 +++++++
 x86/vmx_tests.c | 3 ++-
 2 files changed, 9 insertions(+), 1 deletion(-)

```
#### [PATCH 1/5] rcuwait: Fix stale wake call name in comment
##### From: Davidlohr Bueso <dave@stgolabs.net>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Davidlohr Bueso <dave@stgolabs.net>
X-Patchwork-Id: 11507145
Return-Path: <SRS0=ezuo=6I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EF82914B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Apr 2020 05:52:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E1B362098B
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Apr 2020 05:52:44 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726554AbgDXFwY (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 24 Apr 2020 01:52:24 -0400
Received: from mx2.suse.de ([195.135.220.15]:37006 "EHLO mx2.suse.de"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726442AbgDXFwV (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 24 Apr 2020 01:52:21 -0400
X-Virus-Scanned: by amavisd-new at test-mx.suse.de
Received: from relay2.suse.de (unknown [195.135.220.254])
        by mx2.suse.de (Postfix) with ESMTP id F2A62AD9A;
        Fri, 24 Apr 2020 05:52:17 +0000 (UTC)
From: Davidlohr Bueso <dave@stgolabs.net>
To: tglx@linutronix.de, pbonzini@redhat.com
Cc: peterz@infradead.org, maz@kernel.org, bigeasy@linutronix.de,
        rostedt@goodmis.org, torvalds@linux-foundation.org,
        will@kernel.org, joel@joelfernandes.org,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        dave@stgolabs.net, Davidlohr Bueso <dbueso@suse.de>
Subject: [PATCH 1/5] rcuwait: Fix stale wake call name in comment
Date: Thu, 23 Apr 2020 22:48:33 -0700
Message-Id: <20200424054837.5138-2-dave@stgolabs.net>
X-Mailer: git-send-email 2.16.4
In-Reply-To: <20200424054837.5138-1-dave@stgolabs.net>
References: <20200424054837.5138-1-dave@stgolabs.net>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The 'trywake' name was renamed to simply 'wake', update the comment.

Acked-by: Peter Zijlstra (Intel) <peterz@infradead.org>
Signed-off-by: Davidlohr Bueso <dbueso@suse.de>
---
 kernel/exit.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v3 1/5] KVM: VMX: Introduce generic fastpath handler
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11507173
Return-Path: <SRS0=ezuo=6I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B465592A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Apr 2020 06:23:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9C76520704
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Apr 2020 06:23:03 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="r9EXwphq"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726593AbgDXGXA (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 24 Apr 2020 02:23:00 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:51262 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-FAIL-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726008AbgDXGW7 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 24 Apr 2020 02:22:59 -0400
Received: from mail-pf1-x442.google.com (mail-pf1-x442.google.com
 [IPv6:2607:f8b0:4864:20::442])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id A5FB5C09B045;
        Thu, 23 Apr 2020 23:22:59 -0700 (PDT)
Received: by mail-pf1-x442.google.com with SMTP id x2so612902pfx.7;
        Thu, 23 Apr 2020 23:22:59 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:in-reply-to:references;
        bh=UFT0hKfL7iS8UZisqhI7Q6xNbcamwNw/NX1yQQKe78k=;
        b=r9EXwphqugPnCRsU9hun3rEjYYMPFF5n3SJRgkB06t8M1LLomn2v/KHS7FYZ8QsaTF
         OZhrIsF24j2K9W3BvcBzWpkJtNptx2ECz0VvKoqPNqW571yWQ2gxidDiGKd90GltpbT3
         I/EZLu/35Vf74VFUQ3hWOw2BggmuQXaNuV7nNg+7nghNldbyuqGqm3JkFx93pMoOBnRG
         kVg3X6koFKGnLYCClKcFJFLoSBpP78pbnKyeOLI+MrkWrs1NCcaQekDcQM35UBP89ncS
         Zn7IO01wHLBh3q46+r/kwkxK56XEoejS7l+C5IEM6p5L8LqZ2dUOwcii/oAsRVwv0dvS
         s3Kw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references;
        bh=UFT0hKfL7iS8UZisqhI7Q6xNbcamwNw/NX1yQQKe78k=;
        b=hzrja8lhh1APcRERjiMLdVltbQ1waWo8pxW+YeKNvPBJqKXnwvzqut8EIrcukj4sFJ
         EIgIeJx4h4VKXdk/BTwWl6YqVl6zNpPhFNLqZS8X2TFuJY5iFCJ/61KQwdrM+gtdKbQ8
         sa2iIwcUqAAJlhTvPbdYolBdJbQJjM4Svol7O9uYakisblVZDQm6YPQoT05uNdvIYezj
         QKk+OzFEE0/VY9/Lil88D7WCJ5UjA5Ozs/tpUUWHL2K7Z7QjVX3j2OEJSwVW0q1Bww/K
         d44UNgz8l1aUq90rENueYbWmEHIs9G2T3lOO5jpOrzlDtOonqGD8VM6a5BbVjwLi4Li8
         SPSg==
X-Gm-Message-State: AGi0PubhdLFATJwf6eZo7uXZwkn2cFM9ztB1bAD5f7q7Vo5TnCplzDCF
        y2LfON2OTRX8dUy71YnXF88DqRrH
X-Google-Smtp-Source: 
 APiQypJxuwuvFp5xaaFdP2nRbicoYJCzqR9KIgDJ6O55/vXmZ012YMWjjUMzMCASJnAKzYj6mBRriw==
X-Received: by 2002:a62:7656:: with SMTP id r83mr7763612pfc.71.1587709378973;
        Thu, 23 Apr 2020 23:22:58 -0700 (PDT)
Received: from localhost.localdomain ([103.7.29.6])
        by smtp.googlemail.com with ESMTPSA id
 l30sm3920674pgu.29.2020.04.23.23.22.56
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Thu, 23 Apr 2020 23:22:58 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Haiwei Li <lihaiwei@tencent.com>
Subject: [PATCH v3 1/5] KVM: VMX: Introduce generic fastpath handler
Date: Fri, 24 Apr 2020 14:22:40 +0800
Message-Id: <1587709364-19090-2-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
In-Reply-To: <1587709364-19090-1-git-send-email-wanpengli@tencent.com>
References: <1587709364-19090-1-git-send-email-wanpengli@tencent.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

Introduce generic fastpath handler to handle MSR fastpath, VMX-preemption 
timer fastpath etc. In addition, we can't observe benefit from single 
target IPI fastpath when APICv is disabled, let's just enable IPI and 
Timer fastpath when APICv is enabled for now.

Tested-by: Haiwei Li <lihaiwei@tencent.com>
Cc: Haiwei Li <lihaiwei@tencent.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/include/asm/kvm_host.h |  1 +
 arch/x86/kvm/vmx/vmx.c          | 25 ++++++++++++++++++++-----
 2 files changed, 21 insertions(+), 5 deletions(-)

```
#### [PATCH] [RFC] kvm: x86: emulate APERF/MPERF registers
##### From: Li RongQing <lirongqing@baidu.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Li RongQing <lirongqing@baidu.com>
X-Patchwork-Id: 11507123
Return-Path: <SRS0=ezuo=6I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 947221392
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Apr 2020 05:18:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 85DD020776
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Apr 2020 05:18:53 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726642AbgDXFSw (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 24 Apr 2020 01:18:52 -0400
Received: from mx59.baidu.com ([61.135.168.59]:31099 "EHLO
        tc-sys-mailedm02.tc.baidu.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1725919AbgDXFSu (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 24 Apr 2020 01:18:50 -0400
X-Greylist: delayed 580 seconds by postgrey-1.27 at vger.kernel.org;
 Fri, 24 Apr 2020 01:18:49 EDT
Received: from localhost (cp01-cos-dev01.cp01.baidu.com [10.92.119.46])
        by tc-sys-mailedm02.tc.baidu.com (Postfix) with ESMTP id 4E31611C0049;
        Fri, 24 Apr 2020 13:08:55 +0800 (CST)
From: Li RongQing <lirongqing@baidu.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org, x86@kernel.org,
        hpa@zytor.com, bp@alien8.de, mingo@redhat.com, tglx@linutronix.de,
        joro@8bytes.org, jmattson@google.com, wanpengli@tencent.com,
        vkuznets@redhat.com, sean.j.christopherson@intel.com,
        pbonzini@redhat.com
Subject: [PATCH] [RFC] kvm: x86: emulate APERF/MPERF registers
Date: Fri, 24 Apr 2020 13:08:55 +0800
Message-Id: <1587704935-30960-1-git-send-email-lirongqing@baidu.com>
X-Mailer: git-send-email 1.7.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Guest kernel reports a fixed cpu frequency in /proc/cpuinfo,
this is confused to user when turbo is enable, and aperf/mperf
can be used to show current cpu frequency after 7d5905dc14a
"(x86 / CPU: Always show current CPU frequency in /proc/cpuinfo)"
so we should emulate aperf mperf to achieve it

the period of aperf/mperf in guest mode are accumulated
as emulated value

Signed-off-by: Li RongQing <lirongqing@baidu.com>
---
 arch/x86/include/asm/kvm_host.h |  5 +++++
 arch/x86/kvm/cpuid.c            |  5 ++++-
 arch/x86/kvm/vmx/vmx.c          | 20 ++++++++++++++++++++
 3 files changed, 29 insertions(+), 1 deletion(-)

```
#### [PATCH 1/3] RISC-V: Export riscv_cpuid_to_hartid_mask() API
##### From: Anup Patel <anup.patel@wdc.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Anup Patel <Anup.Patel@wdc.com>
X-Patchwork-Id: 11507097
Return-Path: <SRS0=ezuo=6I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EA2DF912
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Apr 2020 05:00:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CD2B92076C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Apr 2020 05:00:25 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=wdc.com header.i=@wdc.com header.b="O7U6IFxq";
	dkim=pass (1024-bit key) header.d=sharedspace.onmicrosoft.com
 header.i=@sharedspace.onmicrosoft.com header.b="jLUaibd8"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726458AbgDXFAW (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 24 Apr 2020 01:00:22 -0400
Received: from esa4.hgst.iphmx.com ([216.71.154.42]:57967 "EHLO
        esa4.hgst.iphmx.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726524AbgDXFAV (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 24 Apr 2020 01:00:21 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=simple/simple;
  d=wdc.com; i=@wdc.com; q=dns/txt; s=dkim.wdc.com;
  t=1587704420; x=1619240420;
  h=from:to:cc:subject:date:message-id:in-reply-to:
   references:content-transfer-encoding:mime-version;
  bh=9TZKFN70WqKudIvHylul3i6+8Yt2GNTWaHlG3fnfXc0=;
  b=O7U6IFxqdct0jbj9hLVJzEHYkfiVZ3oeZp+/PDRgR0rfUJrfUzGwgHLa
   H5dbFX4g1tQNdBK0NDmYb97OcAP/zNXZF54iZ1/VWF9iOKbVUpaglfpvf
   k+NpCC0OPOzxOLwFDiAzLM6QjgY179JdSsLMgeA9mJjpegwCcOvFPHCpj
   MS7R1QR5c/FB8xu1Fj18VnZxTs4Vkg7Wxrg0oJA40KkzD87BJbsPaEOZK
   1qptCveu3R5Dkmsoh5zejpT+54l1JOhdNR7u5iD2o+hJ+XlKEtkTdKuvU
   UyO3CDPOzkzqV8Vnfft3qtqKXEXOggOrsnrSngXR7p7BfsTe+t/xJXHXm
   A==;
IronPort-SDR: 
 pVzrA5NqSJNBO8rvBgVn+hBIzHL3duMAjOuHp0XVDcwylpvY76U2ZoHQ8yGWi/nntNtAvJEcVc
 5m6gL6fWXAK95Mq4N+HqmOQTtND2F/1l9Er3e6EapKNN/eAQLdokAlx9zGhVimkVg2DdS5c7uw
 FD8TxZVpW6OyUVUdiSCuPLojfG0MVgFoJKjO9iWHQMNM5ku0mnqrtir8W90SOU1otABANzxtT0
 o0t0HYa6w0v10sZqxdi1958NS53GdK5WxYb8wkPI5T7B0pXoug/E+/BbdiVEQCFytEsGQb1ct3
 JHk=
X-IronPort-AV: E=Sophos;i="5.73,310,1583164800";
   d="scan'208";a="136050477"
Received: from mail-co1nam11lp2174.outbound.protection.outlook.com (HELO
 NAM11-CO1-obe.outbound.protection.outlook.com) ([104.47.56.174])
  by ob1.hgst.iphmx.com with ESMTP; 24 Apr 2020 13:00:18 +0800
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=cDn4YRN6y8wnq16UkMbsjUdamxXezpAs+DB8Fw3YXUg6m8jjmo5t65Pq7/pv7XI6QQcfeu4uMYWoX6p2hvHu8SkO5tx7H15vWDfCzr4MzvY0d82tYuqiRqHha04CaT7TnnPEBxhmS914dkOzIE6BhOziKQ9L0tyCONMy6CFnk/CAst30Jhf+toe76Y2hTiK0qvBj+bo+CZU//c5jtGFh9VngODJbgjGo78iec70Cuj2g8KL5mgNMzm1GIvHypypmrcNfTxL8yAFjb+OBwvQQJSFYR2v+GnaQJbmD30uZGYQNltmcJaHa3AwvuFAnyK88zO3/ZFQ8sek3WmUbTTNQPQ==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=xl6Gy1sZP6WITFuw1lylVY/qGiEL4U21EOf9JQzzjX0=;
 b=LoR0NhPeJ9/njmxiMQlYfliZvIiIMe1JXRWQeowbQxzZ7Ieplg1hD+/kig9CsTLb+gAuM/tVfR7hJrIAgYxWGKItyXvd8ORQdKnQPz/Vdp6YCywxy/l6rbMFcb6yzNi4Bzy5SiNB7xZ15yHp77yT0T7oW6Kpz23OPIbZE03MkNU3RT8Xf9U6+FD1mC+cHBBlM9lOmmFiK54/NdW7iE2rRYs78p2hXtJSZzQ74eW2zbeoZd5ToFTBlkKE/JJ8taZ87REMZAWKA7F0E7lx0QoX4ZNtTIcEqRiCGe62z2B43L7qCEfzIRY+jDMDokS8s34WlnWrQIJNiuaGT4YI/+6aMQ==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=wdc.com; dmarc=pass action=none header.from=wdc.com; dkim=pass
 header.d=wdc.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=sharedspace.onmicrosoft.com; s=selector2-sharedspace-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=xl6Gy1sZP6WITFuw1lylVY/qGiEL4U21EOf9JQzzjX0=;
 b=jLUaibd8fdUX6JN+gy2VneIC+wqx2OeV2sJ/VrosPT0+QSlbo+CSIyY+D2hK/4tnfao1osgrRBTuAabp7WQLTpuDqmMyP0O8xrbEQp4d2614jcMxA6Bx8nWzjqOV9MMNgDipnq95UFgrnTOLOQFu5iT/vJRLR9TuGB3CBFyRCtc=
Authentication-Results: spf=none (sender IP is )
 smtp.mailfrom=Anup.Patel@wdc.com;
Received: from DM6PR04MB6201.namprd04.prod.outlook.com (20.178.225.224) by
 DM6PR04MB5467.namprd04.prod.outlook.com (20.178.25.10) with Microsoft SMTP
 Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.2937.13; Fri, 24 Apr 2020 05:00:17 +0000
Received: from DM6PR04MB6201.namprd04.prod.outlook.com
 ([fe80::f8b3:c124:482b:52e0]) by DM6PR04MB6201.namprd04.prod.outlook.com
 ([fe80::f8b3:c124:482b:52e0%5]) with mapi id 15.20.2921.030; Fri, 24 Apr 2020
 05:00:17 +0000
From: Anup Patel <anup.patel@wdc.com>
To: Palmer Dabbelt <palmer@dabbelt.com>,
        Palmer Dabbelt <palmerdabbelt@google.com>,
        Paul Walmsley <paul.walmsley@sifive.com>,
        Albert Ou <aou@eecs.berkeley.edu>,
        Paolo Bonzini <pbonzini@redhat.com>
Cc: Atish Patra <atish.patra@wdc.com>,
        Alistair Francis <Alistair.Francis@wdc.com>,
        Anup Patel <anup@brainfault.org>, kvm@vger.kernel.org,
        kvm-riscv@lists.infradead.org, linux-riscv@lists.infradead.org,
        linux-kernel@vger.kernel.org, Anup Patel <anup.patel@wdc.com>
Subject: [PATCH 1/3] RISC-V: Export riscv_cpuid_to_hartid_mask() API
Date: Fri, 24 Apr 2020 10:29:26 +0530
Message-Id: <20200424045928.79324-2-anup.patel@wdc.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20200424045928.79324-1-anup.patel@wdc.com>
References: <20200424045928.79324-1-anup.patel@wdc.com>
X-ClientProxiedBy: MA1PR01CA0130.INDPRD01.PROD.OUTLOOK.COM
 (2603:1096:a00:35::24) To DM6PR04MB6201.namprd04.prod.outlook.com
 (2603:10b6:5:127::32)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from wdc.com (49.207.59.136) by
 MA1PR01CA0130.INDPRD01.PROD.OUTLOOK.COM (2603:1096:a00:35::24) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.2937.13 via Frontend
 Transport; Fri, 24 Apr 2020 05:00:12 +0000
X-Mailer: git-send-email 2.25.1
X-Originating-IP: [49.207.59.136]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: bb9e8edd-9bd5-4f69-5c1e-08d7e80c61d2
X-MS-TrafficTypeDiagnostic: DM6PR04MB5467:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM6PR04MB54675AAED1D26AEE033028B18DD00@DM6PR04MB5467.namprd04.prod.outlook.com>
WDCIPOUTBOUND: EOP-TRUE
X-MS-Oob-TLC-OOBClassifiers: OLM:3968;
X-Forefront-PRVS: 03838E948C
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM6PR04MB6201.namprd04.prod.outlook.com;PTR:;CAT:NONE;SFTY:;SFS:(4636009)(396003)(366004)(39860400002)(136003)(346002)(376002)(54906003)(110136005)(55016002)(52116002)(7696005)(16526019)(8936002)(5660300002)(7416002)(4326008)(2906002)(8886007)(6666004)(81156014)(478600001)(1006002)(186003)(316002)(1076003)(55236004)(36756003)(4744005)(44832011)(8676002)(2616005)(26005)(956004)(66556008)(66476007)(86362001)(66946007);DIR:OUT;SFP:1102;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 nxPUh7wZf1+YzdpJpoPs4/9RHtfvzaJkdFx5Sdbn7cggFx9NEImW14JY4rfh5WPSUVy85itGk49NnXALQVNcbWpzCX7KpBMjYnIlVJTK4w5wKl507/gayKmbtnH/dlKytaon1eclWu2iQti1sdQfXAnihdgNndVMtHtraRyeFU8RREgzTcm7V4eV7OnGt4yYZQe+Ob98Ro/exGGAHWjXZ0jHgYEAM/r1iWs+DWOXLuT6igGupxpQEs7kEaTg23oHaF7/73U46iExvglyXpDsQu2Zh1Cvv4LqyE2HVS+b82yDPQj8QFPWP6SvSdsfSmB+Hz/JP4C+z2T6UrYMqYh0VbPitQpdCbUWd0ZDU1f59hsr7S2lQFkljikucN8nnCZZ/kF8X/JOcwHQXx8iWjU6/54jSzzHvfAeMQVOBfMeots5neo56CtNMfKk3o9Dx2o0
X-MS-Exchange-AntiSpam-MessageData: 
 ljx1o1u/BhLMjjjV7/mDOYhRWbxo5QhnkqfkknT2hqOP1uvxc6iBLvog0NN4STqZsns+xt4Nh9TR42nGCyKcOIgfArOav1S1jVCc/953CoJ9dodBhWoHCLc3VCNjlb39e9266EXMIAObyREhdvBZUQ==
X-OriginatorOrg: wdc.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 bb9e8edd-9bd5-4f69-5c1e-08d7e80c61d2
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 24 Apr 2020 05:00:17.8370
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: b61c8803-16f3-4c35-9b17-6f65f441df86
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 p5xDU0W9arBlfOxdtJlYMl8E4TpLQ4X4LGZ48VA3VkR14udShIsPLqCHakJfDT/4+VNoYuXtU0LfeMdqnMvODA==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6PR04MB5467
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The riscv_cpuid_to_hartid_mask() API should be exported to allow
building KVM RISC-V as loadable module.

Signed-off-by: Anup Patel <anup.patel@wdc.com>
Reviewed-by: Palmer Dabbelt <palmerdabbelt@google.com>
---
 arch/riscv/kernel/smp.c | 2 ++
 1 file changed, 2 insertions(+)

```
#### [kvm-unit-tests PATCH v6 01/10] s390x: saving regs for interrupts
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 11507509
Return-Path: <SRS0=ezuo=6I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2485D1575
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Apr 2020 10:46:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 15FA32064A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Apr 2020 10:46:01 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726746AbgDXKqA (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 24 Apr 2020 06:46:00 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:10104 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726489AbgDXKqA (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 24 Apr 2020 06:46:00 -0400
Received: from pps.filterd (m0098417.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 03OAXdCF038456;
        Fri, 24 Apr 2020 06:45:59 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 30kpq45x80-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 24 Apr 2020 06:45:58 -0400
Received: from m0098417.ppops.net (m0098417.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 03OAZP4c046995;
        Fri, 24 Apr 2020 06:45:58 -0400
Received: from ppma03ams.nl.ibm.com (62.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.98])
        by mx0a-001b2d01.pphosted.com with ESMTP id 30kpq45x78-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 24 Apr 2020 06:45:58 -0400
Received: from pps.filterd (ppma03ams.nl.ibm.com [127.0.0.1])
        by ppma03ams.nl.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 03OAjTqe022195;
        Fri, 24 Apr 2020 10:45:56 GMT
Received: from b06cxnps4075.portsmouth.uk.ibm.com
 (d06relay12.portsmouth.uk.ibm.com [9.149.109.197])
        by ppma03ams.nl.ibm.com with ESMTP id 30fs65921v-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 24 Apr 2020 10:45:56 +0000
Received: from d06av23.portsmouth.uk.ibm.com (d06av23.portsmouth.uk.ibm.com
 [9.149.105.59])
        by b06cxnps4075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 03OAjsrW1179926
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 24 Apr 2020 10:45:54 GMT
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 9764FA4040;
        Fri, 24 Apr 2020 10:45:54 +0000 (GMT)
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 4560DA4053;
        Fri, 24 Apr 2020 10:45:54 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.79.138])
        by d06av23.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Fri, 24 Apr 2020 10:45:54 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, frankja@linux.ibm.com,
        david@redhat.com, thuth@redhat.com, cohuck@redhat.com
Subject: [kvm-unit-tests PATCH v6 01/10] s390x: saving regs for interrupts
Date: Fri, 24 Apr 2020 12:45:43 +0200
Message-Id: <1587725152-25569-2-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1587725152-25569-1-git-send-email-pmorel@linux.ibm.com>
References: <1587725152-25569-1-git-send-email-pmorel@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.676
 definitions=2020-04-24_04:2020-04-23,2020-04-24 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 bulkscore=0 malwarescore=0
 adultscore=0 clxscore=1015 suspectscore=1 mlxscore=0 priorityscore=1501
 phishscore=0 spamscore=0 impostorscore=0 mlxlogscore=950
 lowpriorityscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2003020000 definitions=main-2004240082
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If we use multiple source of interrupts, for example, using SCLP
console to print information while using I/O interrupts, we need
to have a re-entrant register saving interruption handling.

Instead of saving at a static memory address, let's save the base
registers and the floating point registers on the stack.

Note that we keep the static register saving to recover from the
RESET tests.

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
---
 s390x/cstart64.S | 34 ++++++++++++++++++++++++++++++++--
 1 file changed, 32 insertions(+), 2 deletions(-)

```
#### [PATCH v3] s390x: smp: Test all CRs on initial reset
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11507395
Return-Path: <SRS0=ezuo=6I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D073B81
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Apr 2020 09:34:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C16322074F
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Apr 2020 09:34:08 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726796AbgDXJeH (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 24 Apr 2020 05:34:07 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:14012 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726770AbgDXJeH (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 24 Apr 2020 05:34:07 -0400
Received: from pps.filterd (m0098394.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 03O9Xm7S025353;
        Fri, 24 Apr 2020 05:34:06 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 30k7rd0dqf-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 24 Apr 2020 05:34:06 -0400
Received: from m0098394.ppops.net (m0098394.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 03O9Y6aL028083;
        Fri, 24 Apr 2020 05:34:06 -0400
Received: from ppma03ams.nl.ibm.com (62.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.98])
        by mx0a-001b2d01.pphosted.com with ESMTP id 30k7rd0dpt-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 24 Apr 2020 05:34:06 -0400
Received: from pps.filterd (ppma03ams.nl.ibm.com [127.0.0.1])
        by ppma03ams.nl.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 03O9PxKP001321;
        Fri, 24 Apr 2020 09:34:03 GMT
Received: from b06cxnps4074.portsmouth.uk.ibm.com
 (d06relay11.portsmouth.uk.ibm.com [9.149.109.196])
        by ppma03ams.nl.ibm.com with ESMTP id 30fs658ypv-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 24 Apr 2020 09:34:03 +0000
Received: from d06av24.portsmouth.uk.ibm.com (mk.ibm.com [9.149.105.60])
        by b06cxnps4074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 03O9Y1wa57278508
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 24 Apr 2020 09:34:01 GMT
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id E38C142042;
        Fri, 24 Apr 2020 09:34:00 +0000 (GMT)
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 3E68D42045;
        Fri, 24 Apr 2020 09:34:00 +0000 (GMT)
Received: from linux01.pok.stglabs.ibm.com (unknown [9.114.17.81])
        by d06av24.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Fri, 24 Apr 2020 09:34:00 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: thuth@redhat.com, linux-s390@vger.kernel.org, david@redhat.com,
        borntraeger@de.ibm.com, cohuck@redhat.com
Subject: [PATCH v3] s390x: smp: Test all CRs on initial reset
Date: Fri, 24 Apr 2020 05:33:56 -0400
Message-Id: <20200424093356.11931-1-frankja@linux.ibm.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <2ebdf5d6-74ac-d9e5-d329-29611a5f87cd@redhat.com>
References: <2ebdf5d6-74ac-d9e5-d329-29611a5f87cd@redhat.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.676
 definitions=2020-04-24_03:2020-04-23,2020-04-24 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 malwarescore=0 spamscore=0
 clxscore=1015 priorityscore=1501 mlxlogscore=999 impostorscore=0
 mlxscore=0 phishscore=0 lowpriorityscore=0 adultscore=0 suspectscore=1
 bulkscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2003020000 definitions=main-2004240072
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

All CRs are set to 0 and CRs 0 and 14 are set to pre-defined values,
so we also need to test 1-13 and 15 for 0.

And while we're at it, let's also set some values to cr 1, 7 and 13, so
we can actually be sure that they will be zeroed.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: Christian Borntraeger <borntraeger@de.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
---
 s390x/smp.c | 18 +++++++++++++++++-
 1 file changed, 17 insertions(+), 1 deletion(-)

```
#### [PATCH net v2 1/2] vhost/vsock: fix packet delivery order to monitoring devices
##### From: Stefano Garzarella <sgarzare@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stefano Garzarella <sgarzare@redhat.com>
X-Patchwork-Id: 11508065
Return-Path: <SRS0=ezuo=6I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AF8A0112C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Apr 2020 15:08:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 974AB20776
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Apr 2020 15:08:58 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="H7fa5u3k"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727903AbgDXPI5 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 24 Apr 2020 11:08:57 -0400
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:23576 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727804AbgDXPI4 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 24 Apr 2020 11:08:56 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1587740935;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=9R6yjveOElwyTut93FZB4NDQJHLkZZ8HkoqOG3/TEPw=;
        b=H7fa5u3kq0iFqt+1pKZuspjKSk54jXe5JXcnYGxX/Rhxx+ehHdRj2Lf4nGqLnfw40lD6ZS
        Smvkc6VB0nnnalAclJXEXvFHlGiE1IUqCJ6H0ElI98ZF1AYJYEx6s1jmv9i87I0xJMQ9Ec
        JUQoqsfZnnbcNI8m98wTAhxQc3ve/do=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-495-iTW-gitIMiyiT6Du8TpJbg-1; Fri, 24 Apr 2020 11:08:51 -0400
X-MC-Unique: iTW-gitIMiyiT6Du8TpJbg-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id CBD7E1005510;
        Fri, 24 Apr 2020 15:08:36 +0000 (UTC)
Received: from steredhat.redhat.com (ovpn-114-43.ams2.redhat.com
 [10.36.114.43])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 71AC55D70C;
        Fri, 24 Apr 2020 15:08:34 +0000 (UTC)
From: Stefano Garzarella <sgarzare@redhat.com>
To: davem@davemloft.net
Cc: Jason Wang <jasowang@redhat.com>, Jakub Kicinski <kuba@kernel.org>,
        linux-kernel@vger.kernel.org,
        Stefano Garzarella <sgarzare@redhat.com>, kvm@vger.kernel.org,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Stefan Hajnoczi <stefanha@redhat.com>,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org
Subject: [PATCH net v2 1/2] vhost/vsock: fix packet delivery order to
 monitoring devices
Date: Fri, 24 Apr 2020 17:08:29 +0200
Message-Id: <20200424150830.183113-2-sgarzare@redhat.com>
In-Reply-To: <20200424150830.183113-1-sgarzare@redhat.com>
References: <20200424150830.183113-1-sgarzare@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We want to deliver packets to monitoring devices before it is
put in the virtqueue, to avoid that replies can appear in the
packet capture before the transmitted packet.

Signed-off-by: Stefano Garzarella <sgarzare@redhat.com>
---
 drivers/vhost/vsock.c | 10 +++++-----
 1 file changed, 5 insertions(+), 5 deletions(-)

```
#### [PATCH v11 1/7] x86/kvm/hyper-v: Explicitly align hcall param for kvm_hyperv_exit
##### From: Jon Doron <arilou@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jon Doron <arilou@gmail.com>
X-Patchwork-Id: 11507663
Return-Path: <SRS0=ezuo=6I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D476914B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Apr 2020 11:38:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BC57C2084D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Apr 2020 11:38:07 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="iI1PGy8n"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727018AbgDXLiH (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 24 Apr 2020 07:38:07 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:43864 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726888AbgDXLiG (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 24 Apr 2020 07:38:06 -0400
Received: from mail-wm1-x341.google.com (mail-wm1-x341.google.com
 [IPv6:2a00:1450:4864:20::341])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id DDF78C09B046;
        Fri, 24 Apr 2020 04:38:04 -0700 (PDT)
Received: by mail-wm1-x341.google.com with SMTP id g12so10305660wmh.3;
        Fri, 24 Apr 2020 04:38:04 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=hjT03eHhQ1dE3AJ2qMjxfwTNnQchau8BzAjB0MfMplY=;
        b=iI1PGy8nES6hDeRdsF06GvtCVXNHa+2QyXXjpyPiG1P5m4oC6prwJFmvdtE/PleiWm
         Da1h5SiXK/kFe8QaTEd/CEIJCM2eyiXGkRGeRnnJrxmtzrx9gHv61+gSPiRgrjSse1OZ
         0+Uh/rJDDZrkeFrvSjeOnDc4I9O12LJnBDvU3245VktJ2vYprdD4/kObgf/YkfpvuWGf
         ME63Ldi6EMtBW/sbsGGJFc7syeoxDiaN9MM5raf3hOVkL5DQtc2nxx8jDT7kW7uq7Tgn
         JarzBz0obteBNH3nRefLstZ3topmgoJD0Ge9OTGsCN1u1vFFpSORRA+82CosLl5qvNTK
         pCYg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=hjT03eHhQ1dE3AJ2qMjxfwTNnQchau8BzAjB0MfMplY=;
        b=ixkFAuR2yJ6p9FAa7C/qwnAeceZPqQzmcy22L68Diub2SWbMIFL+clJfmnjqv89bBM
         +Be9eSWhS1QsCRTvQb2+u3RX+FPkCk7A5lvXF7nZqSMWDEXX4Tf03x/Lie6y4coVWYkA
         /xDPK7xUT/nujryGY2mVTlhzwvGZW7NdayXVGY+TRz6fBBlSPGXyDrPVx5MOFSHPtWMQ
         ete1WEQZKmFvd+nwvK6yAFsVET8R3Aonq12jeB0AyP+uuccKNqqs9kwRo35x8y0gwXqY
         SxzJL4vCKIxMsFkyXp6nPIExTINT4MDFrqr+9uurMJNT04r5bYQ7MvTIFA0aFeJj5hOv
         Kw5Q==
X-Gm-Message-State: AGi0PuYIhLfDGbp2eHssUukynDow/URyDQllUPTFAkUtY6Cx6buJ39yn
        oCKftNvasc183fTi2cwXH1lQTlyW5EI=
X-Google-Smtp-Source: 
 APiQypL/XYfWJE9aLnvUn5aWZDuAFV9fmnIFisczBW37nZ9lgKGN/1rGxyjDg3A5aw0GetlEYObSzw==
X-Received: by 2002:a05:600c:2645:: with SMTP id
 5mr9498220wmy.168.1587728283298;
        Fri, 24 Apr 2020 04:38:03 -0700 (PDT)
Received: from jondnuc.lan (IGLD-84-229-154-20.inter.net.il. [84.229.154.20])
        by smtp.gmail.com with ESMTPSA id
 w83sm2451007wmb.37.2020.04.24.04.38.02
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 24 Apr 2020 04:38:02 -0700 (PDT)
From: Jon Doron <arilou@gmail.com>
To: kvm@vger.kernel.org, linux-hyperv@vger.kernel.org
Cc: vkuznets@redhat.com, Jon Doron <arilou@gmail.com>
Subject: [PATCH v11 1/7] x86/kvm/hyper-v: Explicitly align hcall param for
 kvm_hyperv_exit
Date: Fri, 24 Apr 2020 14:37:40 +0300
Message-Id: <20200424113746.3473563-2-arilou@gmail.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20200424113746.3473563-1-arilou@gmail.com>
References: <20200424113746.3473563-1-arilou@gmail.com>
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

Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Signed-off-by: Jon Doron <arilou@gmail.com>
---
 Documentation/virt/kvm/api.rst | 2 ++
 include/uapi/linux/kvm.h       | 2 ++
 2 files changed, 4 insertions(+)

```
