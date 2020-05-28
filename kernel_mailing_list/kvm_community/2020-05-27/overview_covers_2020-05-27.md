

#### [PATCH v3 0/2] Fix issue with not starting nesting guests on my
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
From patchwork Wed May 27 14:04:23 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 11573075
Return-Path: <SRS0=eyEw=7J=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 08378913
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 27 May 2020 14:04:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E533721475
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 27 May 2020 14:04:43 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="GHijKu1P"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730352AbgE0OEk (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 27 May 2020 10:04:40 -0400
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:48510 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1730258AbgE0OEj (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 27 May 2020 10:04:39 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1590588278;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=NcFdxBDv4qTLkO36Cyhthea6RiBA+xci3OrDd7Ic3kg=;
        b=GHijKu1PxOxkpFiW5jWHJfhu2P3L7pWFYvChtporDWqNFGA8CV33GeSEUWW0HxNDlAOYR4
        6C6TZzhUH0GeMfQ6xZlU9DNO0q0gYZyExUGau6gDl0UR9F7PYienQBCFBVUt05xdEZ4wGH
        mRRYB+kNnWn+9Chs0HYtPeH4YFbk1sU=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-237-9wuW275oOzawgKXdjjUfsA-1; Wed, 27 May 2020 10:04:34 -0400
X-MC-Unique: 9wuW275oOzawgKXdjjUfsA-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 71CE4460;
        Wed, 27 May 2020 14:04:32 +0000 (UTC)
Received: from starship.f32vm (unknown [10.35.206.172])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 293642DE69;
        Wed, 27 May 2020 14:04:27 +0000 (UTC)
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
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH v3 0/2] Fix issue with not starting nesting guests on my
 system
Date: Wed, 27 May 2020 17:04:23 +0300
Message-Id: <20200527140425.3484-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

On my AMD machine I noticed that I can't start any nested guests,
because nested KVM (everything from master git branches) complains
that it can't find msr MSR_IA32_UMWAIT_CONTROL which my system doesn't support
at all anyway.

I traced it to the recently added UMWAIT support to qemu and kvm.
The kvm portion exposed the new MSR in KVM_GET_MSR_INDEX_LIST without
checking that it the underlying feature is supported in CPUID.
It happened to work when non nested because as a precation kvm,
tries to read each MSR on host before adding it to that list,
and when read gets a #GP it ignores it.

When running nested, the L1 hypervisor can be set to ignore unknown
msr read/writes (I need this for some other guests), thus this safety
check doesn't work anymore.

V2: * added a patch to setup correctly the X86_FEATURE_WAITPKG kvm capability
    * dropped the cosmetic fix patch as it is now fixed in kvm/queue

V3: addressed the review feedback and possibly made the commit messages a bit better
    Thanks!

Best regards,
        Maxim Levitsky

Maxim Levitsky (2):
  KVM: VMX: enable X86_FEATURE_WAITPKG in KVM capabilities
  KVM: x86: don't expose MSR_IA32_UMWAIT_CONTROL unconditionally

 arch/x86/kvm/vmx/vmx.c | 3 +++
 arch/x86/kvm/x86.c     | 4 ++++
 2 files changed, 7 insertions(+)
```
#### [PATCH v3 0/5] Add a vhost RPMsg API
##### From: Guennadi Liakhovetski <guennadi.liakhovetski@linux.intel.com>

```c
From patchwork Wed May 27 18:05:36 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Guennadi Liakhovetski
 <guennadi.liakhovetski@linux.intel.com>
X-Patchwork-Id: 11573711
Return-Path: <SRS0=eyEw=7J=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6802E1752
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 27 May 2020 18:05:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5947B2075A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 27 May 2020 18:05:47 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2389015AbgE0SFq (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 27 May 2020 14:05:46 -0400
Received: from mga09.intel.com ([134.134.136.24]:57368 "EHLO mga09.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2387706AbgE0SFq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 27 May 2020 14:05:46 -0400
IronPort-SDR: 
 RPhUTSsqebZ1L4XkCgpjxQctvFiN73IAOUmYLO6Gjc2haGE4oDcEwIPHUIA+Y2OVLjfLfbQRCh
 bdz81QWetVXA==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga006.jf.intel.com ([10.7.209.51])
  by orsmga102.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 27 May 2020 11:05:45 -0700
IronPort-SDR: 
 O7FuUcKroBLlWWsUlkd/MVwiNKX8h3WpRYkx6DXWzxpnS5MQdkbT+mkutDL7BeUtQpGRQ3mjnI
 gxITuBGQzgdw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,442,1583222400";
   d="scan'208";a="270553286"
Received: from gliakhov-mobl2.ger.corp.intel.com (HELO
 ubuntu.ger.corp.intel.com) ([10.252.42.249])
  by orsmga006.jf.intel.com with ESMTP; 27 May 2020 11:05:42 -0700
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
Subject: [PATCH v3 0/5] Add a vhost RPMsg API
Date: Wed, 27 May 2020 20:05:36 +0200
Message-Id: <20200527180541.5570-1-guennadi.liakhovetski@linux.intel.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

v3:
- address several checkpatch warnings
- address comments from Mathieu Poirier

v2:
- update patch #5 with a correct vhost_dev_init() prototype
- drop patch #6 - it depends on a different patch, that is currently
  an RFC
- address comments from Pierre-Louis Bossart:
  * remove "default n" from Kconfig

Linux supports RPMsg over VirtIO for "remote processor" /AMP use
cases. It can however also be used for virtualisation scenarios,
e.g. when using KVM to run Linux on both the host and the guests.
This patch set adds a wrapper API to facilitate writing vhost
drivers for such RPMsg-based solutions. The first use case is an
audio DSP virtualisation project, currently under development, ready
for review and submission, available at
https://github.com/thesofproject/linux/pull/1501/commits
A further patch for the ADSP vhost RPMsg driver will be sent
separately for review only since it cannot be merged without audio
patches being upstreamed first.

Thanks
Guennadi

Guennadi Liakhovetski (5):
  vhost: convert VHOST_VSOCK_SET_RUNNING to a generic ioctl
  vhost: (cosmetic) remove a superfluous variable initialisation
  rpmsg: move common structures and defines to headers
  rpmsg: update documentation
  vhost: add an RPMsg API

 Documentation/rpmsg.txt          |   6 +-
 drivers/rpmsg/virtio_rpmsg_bus.c |  78 +-------
 drivers/vhost/Kconfig            |   7 +
 drivers/vhost/Makefile           |   3 +
 drivers/vhost/rpmsg.c            | 382 +++++++++++++++++++++++++++++++++++++++
 drivers/vhost/vhost.c            |   2 +-
 drivers/vhost/vhost_rpmsg.h      |  74 ++++++++
 include/linux/virtio_rpmsg.h     |  81 +++++++++
 include/uapi/linux/rpmsg.h       |   3 +
 include/uapi/linux/vhost.h       |   4 +-
 10 files changed, 559 insertions(+), 81 deletions(-)
 create mode 100644 drivers/vhost/rpmsg.c
 create mode 100644 drivers/vhost/vhost_rpmsg.h
 create mode 100644 include/linux/virtio_rpmsg.h
```
