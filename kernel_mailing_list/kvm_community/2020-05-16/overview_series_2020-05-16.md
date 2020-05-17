#### [PATCH 1/6] vhost: convert VHOST_VSOCK_SET_RUNNING to a generic ioctl
##### From: Guennadi Liakhovetski <guennadi.liakhovetski@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Guennadi Liakhovetski
 <guennadi.liakhovetski@linux.intel.com>
X-Patchwork-Id: 11553427
Return-Path: <SRS0=97JA=66=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B244F1391
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 16 May 2020 10:11:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9A78B2076A
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 16 May 2020 10:11:16 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726283AbgEPKLO (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 16 May 2020 06:11:14 -0400
Received: from mga12.intel.com ([192.55.52.136]:36845 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726276AbgEPKLN (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 16 May 2020 06:11:13 -0400
IronPort-SDR: 
 ijLohQcy76h90/96vro/5K7UltXZOf6CuqxGelRpxAQMX8SkRji5NdQy2ZRuaD9wJw4pU+Uqub
 Fo7Kyxb0TWWA==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga002.jf.intel.com ([10.7.209.21])
  by fmsmga106.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 16 May 2020 03:11:13 -0700
IronPort-SDR: 
 JHGSgJksp0L392q1NgvYECyuFKRrE2ipyredBrMTXLZIHNdzO8oVHATveIkLExH3X2lT3iRk4H
 7XuMY5Dd4sng==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,398,1583222400";
   d="scan'208";a="281484330"
Received: from gliakhov-mobl2.ger.corp.intel.com (HELO
 ubuntu.ger.corp.intel.com) ([10.249.40.45])
  by orsmga002.jf.intel.com with ESMTP; 16 May 2020 03:11:11 -0700
From: Guennadi Liakhovetski <guennadi.liakhovetski@linux.intel.com>
To: kvm@vger.kernel.org
Cc: linux-remoteproc@vger.kernel.org,
        virtualization@lists.linux-foundation.org,
        sound-open-firmware@alsa-project.org,
        Pierre-Louis Bossart <pierre-louis.bossart@linux.intel.com>,
        Liam Girdwood <liam.r.girdwood@linux.intel.com>
Subject: [PATCH 1/6] vhost: convert VHOST_VSOCK_SET_RUNNING to a generic ioctl
Date: Sat, 16 May 2020 12:11:04 +0200
Message-Id: <20200516101109.2624-2-guennadi.liakhovetski@linux.intel.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20200516101109.2624-1-guennadi.liakhovetski@linux.intel.com>
References: <20200516101109.2624-1-guennadi.liakhovetski@linux.intel.com>
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
#### [PATCH v12 01/11] Documentation: Add EPT based Subpage Protection and related APIs
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Weijiang <weijiang.yang@intel.com>
X-Patchwork-Id: 11553497
Return-Path: <SRS0=97JA=66=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DDB6959D
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 16 May 2020 12:53:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C6C79206D8
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 16 May 2020 12:53:55 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726532AbgEPMxw (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 16 May 2020 08:53:52 -0400
Received: from mga07.intel.com ([134.134.136.100]:47556 "EHLO mga07.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726237AbgEPMxu (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 16 May 2020 08:53:50 -0400
IronPort-SDR: 
 caTWrWCNXYE/EUAbvs8zPnL8wWt2ocucYQqKsl6+InhH3zId/9+sc+RpCOanatEtl1R9pUVThG
 Ts0169seKDpw==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga004.fm.intel.com ([10.253.24.48])
  by orsmga105.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 16 May 2020 05:53:49 -0700
IronPort-SDR: 
 kv861OnMzM+uz102VH7q5QsV/n1eQsqas7vSE5qFvm9fALyGHbKGdX6bzhx0xEiw3P1wTCj9xu
 ymrvx5tWWLHQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,398,1583222400";
   d="scan'208";a="288076562"
Received: from local-michael-cet-test.sh.intel.com ([10.239.159.128])
  by fmsmga004.fm.intel.com with ESMTP; 16 May 2020 05:53:47 -0700
From: Yang Weijiang <weijiang.yang@intel.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        pbonzini@redhat.com, jmattson@google.com,
        sean.j.christopherson@intel.com
Cc: yu.c.zhang@linux.intel.com, alazar@bitdefender.com,
        edwin.zhai@intel.com, ssicleru@bitdefender.com,
        Yang Weijiang <weijiang.yang@intel.com>
Subject: [PATCH v12 01/11] Documentation: Add EPT based Subpage Protection and
 related APIs
Date: Sat, 16 May 2020 20:54:57 +0800
Message-Id: <20200516125507.5277-2-weijiang.yang@intel.com>
X-Mailer: git-send-email 2.17.2
In-Reply-To: <20200516125507.5277-1-weijiang.yang@intel.com>
References: <20200516125507.5277-1-weijiang.yang@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Co-developed-by: yi.z.zhang@linux.intel.com
Signed-off-by: yi.z.zhang@linux.intel.com
Signed-off-by: Yang Weijiang <weijiang.yang@intel.com>
---
 Documentation/virt/kvm/api.rst        |  38 ++++++
 Documentation/virtual/kvm/spp_kvm.txt | 179 ++++++++++++++++++++++++++
 2 files changed, 217 insertions(+)
 create mode 100644 Documentation/virtual/kvm/spp_kvm.txt

```
#### [GIT PULL] KVM changes for Linux 5.7-rc6
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11553475
Return-Path: <SRS0=97JA=66=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 108C059D
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 16 May 2020 12:24:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DE84D206D8
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 16 May 2020 12:24:19 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Y6cEPyGb"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726228AbgEPMYS (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 16 May 2020 08:24:18 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:38880 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726219AbgEPMYS (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 16 May 2020 08:24:18 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1589631857;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc; bh=8mmEst/G2NAr0kipPJrp+ihzAeJTb8tA3U7VWWeYgP4=;
        b=Y6cEPyGbuao4T5tPmyiQU//Naac6HK79TMFp1jgKjqY5jxXFtHyEB64j2g1v42UpsQ34Wk
        XBs3WKeiDtEc1H/p+RkHopSCKheGYM5F1BmQOf/9j0qreG5YVWh+N1pMJe47G9wNuvXPRl
        uYUbfRW5qumSm2F3ayomQX0LHNV2XvY=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-222-5Sf6BMQYMyelcSRVZ_uPWg-1; Sat, 16 May 2020 08:24:15 -0400
X-MC-Unique: 5Sf6BMQYMyelcSRVZ_uPWg-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 6BE5F1005510;
        Sat, 16 May 2020 12:24:14 +0000 (UTC)
Received: from virtlab511.virt.lab.eng.bos.redhat.com
 (virtlab511.virt.lab.eng.bos.redhat.com [10.19.152.198])
        by smtp.corp.redhat.com (Postfix) with ESMTP id F02032657D;
        Sat, 16 May 2020 12:24:13 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: torvalds@linux-foundation.org
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [GIT PULL] KVM changes for Linux 5.7-rc6
Date: Sat, 16 May 2020 08:24:13 -0400
Message-Id: <20200516122413.693424-1-pbonzini@redhat.com>
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Linus,

The following changes since commit 2673cb6849722a4ffd74c27a9200a9ec43f64be3:

  Merge tag 'kvm-s390-master-5.7-3' of git://git.kernel.org/pub/scm/linux/kernel/git/kvms390/linux into HEAD (2020-05-06 08:09:17 -0400)

are available in the Git repository at:

  https://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to c4e0e4ab4cf3ec2b3f0b628ead108d677644ebd9:

  KVM: x86: Fix off-by-one error in kvm_vcpu_ioctl_x86_setup_mce (2020-05-15 13:48:56 -0400)

----------------------------------------------------------------
A new testcase for guest debugging (gdbstub) that exposed a bunch of
bugs, mostly for AMD processors.  And a few other x86 fixes.

----------------------------------------------------------------
Babu Moger (1):
      KVM: x86: Fix pkru save/restore when guest CR4.PKE=0, move it to x86.c

Jim Mattson (1):
      KVM: x86: Fix off-by-one error in kvm_vcpu_ioctl_x86_setup_mce

Paolo Bonzini (6):
      KVM: x86: fix DR6 delivery for various cases of #DB injection
      KVM: nSVM: trap #DB and #BP to userspace if guest debugging is on
      KVM: SVM: keep DR6 synchronized with vcpu->arch.dr6
      KVM: x86, SVM: isolate vcpu->arch.dr6 from vmcb->save.dr6
      KVM: VMX: pass correct DR6 for GD userspace exit
      Merge branch 'kvm-amd-fixes' into HEAD

Peter Xu (4):
      KVM: X86: Declare KVM_CAP_SET_GUEST_DEBUG properly
      KVM: X86: Set RTM for DB_VECTOR too for KVM_EXIT_DEBUG
      KVM: X86: Fix single-step with KVM_SET_GUEST_DEBUG
      KVM: selftests: Add KVM_SET_GUEST_DEBUG test

Suravee Suthikulpanit (2):
      KVM: Introduce kvm_make_all_cpus_request_except()
      KVM: SVM: Disable AVIC before setting V_IRQ

 arch/x86/include/asm/kvm_host.h                 |   4 +-
 arch/x86/kvm/hyperv.c                           |   2 +-
 arch/x86/kvm/svm/nested.c                       |  39 ++++-
 arch/x86/kvm/svm/svm.c                          |  36 +++--
 arch/x86/kvm/vmx/vmx.c                          |  41 +----
 arch/x86/kvm/x86.c                              |  60 ++++---
 include/linux/kvm_host.h                        |   3 +
 tools/testing/selftests/kvm/Makefile            |   1 +
 tools/testing/selftests/kvm/include/kvm_util.h  |   2 +
 tools/testing/selftests/kvm/lib/kvm_util.c      |   9 ++
 tools/testing/selftests/kvm/x86_64/debug_regs.c | 202 ++++++++++++++++++++++++
 virt/kvm/kvm_main.c                             |  14 +-
 12 files changed, 325 insertions(+), 88 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/x86_64/debug_regs.c
```
#### [PATCH 1/4] KVM: nSVM: fix condition for filtering async PF
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11553537
Return-Path: <SRS0=97JA=66=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 83E3F59D
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 16 May 2020 13:53:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6852C206F4
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 16 May 2020 13:53:32 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="EBjpjrb2"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726700AbgEPNxU (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 16 May 2020 09:53:20 -0400
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:33592 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726374AbgEPNxT (ORCPT
        <rfc822;kvm@vger.kernel.org>); Sat, 16 May 2020 09:53:19 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1589637198;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:in-reply-to:in-reply-to:references:references;
        bh=FF/ooaDDfU4o/ecS6s5UdO9199Vv4g2oaCID5N2AiVg=;
        b=EBjpjrb2DMMUUXub+YBWeZhd4uv+QMBZy+5T+3tnTvlwixEecWpt17W2j5Lu4VYdJ3LyFR
        P023xjkqtZB8QzZUIyHc/pEwQaTlTM6qRtmiyLe7WKrhRBT5QNNusqJG7EguIULaj9dGQQ
        JPCyy6tnq3/Pq2QV4EjCun8d6vl/d1g=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-387-MBor5CpnOA-WkrEwIEn2Rg-1; Sat, 16 May 2020 09:53:16 -0400
X-MC-Unique: MBor5CpnOA-WkrEwIEn2Rg-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id CE81E80183C;
        Sat, 16 May 2020 13:53:15 +0000 (UTC)
Received: from virtlab511.virt.lab.eng.bos.redhat.com
 (virtlab511.virt.lab.eng.bos.redhat.com [10.19.152.198])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 5FFEB5D9D3;
        Sat, 16 May 2020 13:53:15 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: peterx@redhat.com
Subject: [PATCH 1/4] KVM: nSVM: fix condition for filtering async PF
Date: Sat, 16 May 2020 09:53:08 -0400
Message-Id: <20200516135311.704878-2-pbonzini@redhat.com>
In-Reply-To: <20200516135311.704878-1-pbonzini@redhat.com>
References: <20200516135311.704878-1-pbonzini@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Async page faults have to be trapped in the host (L1 in this
case), since the APC reason was passed from L0 to L1 and stored
in the L1 APF data page.  This was completely reversed, as the
page faults were passed to the guest (a L2 hypervisor).

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/svm/nested.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH 3/4] KVM: nSVM: remove exit_required
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11553539
Return-Path: <SRS0=97JA=66=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9FBA71391
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 16 May 2020 13:53:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 88172206F4
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 16 May 2020 13:53:32 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Gyxbc8x/"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726803AbgEPNxX (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 16 May 2020 09:53:23 -0400
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:52040 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726715AbgEPNxW (ORCPT
        <rfc822;kvm@vger.kernel.org>); Sat, 16 May 2020 09:53:22 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1589637201;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:in-reply-to:in-reply-to:references:references;
        bh=PcB0rlTVKf82QCXQYfq37/1aCuUnjuKh5Ln3iuABjVM=;
        b=Gyxbc8x/TCJglSaITphwhTGZia25V0E8rv239QxfDv/+eRLft9KcJjSxHeiAyKxOPtyXMI
        DkoBJfIS35OjMjv85JP8xB4uwq3k6A1+DBg4Ub7m5ivLMPL5ksxmhl4tVvWTEKR/ly/r1w
        tWRYFBgtUNpLvTM5Qbw0UQjdID05iJ4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-433-na5FWGkNMYe39A-NEuAWGw-1; Sat, 16 May 2020 09:53:18 -0400
X-MC-Unique: na5FWGkNMYe39A-NEuAWGw-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 25787100A68D;
        Sat, 16 May 2020 13:53:17 +0000 (UTC)
Received: from virtlab511.virt.lab.eng.bos.redhat.com
 (virtlab511.virt.lab.eng.bos.redhat.com [10.19.152.198])
        by smtp.corp.redhat.com (Postfix) with ESMTP id AB4AE5D9D3;
        Sat, 16 May 2020 13:53:16 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: peterx@redhat.com
Subject: [PATCH 3/4] KVM: nSVM: remove exit_required
Date: Sat, 16 May 2020 09:53:10 -0400
Message-Id: <20200516135311.704878-4-pbonzini@redhat.com>
In-Reply-To: <20200516135311.704878-1-pbonzini@redhat.com>
References: <20200516135311.704878-1-pbonzini@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

All events now inject vmexits before vmentry rather than after vmexit.  Therefore,
exit_required is not set anymore and we can remove it.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/svm/nested.c |  3 +--
 arch/x86/kvm/svm/svm.c    | 14 --------------
 arch/x86/kvm/svm/svm.h    |  3 ---
 3 files changed, 1 insertion(+), 19 deletions(-)

```
#### [PATCH RFC] vhost: add an SOF Audio DSP driver
##### From: Guennadi Liakhovetski <guennadi.liakhovetski@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Guennadi Liakhovetski
 <guennadi.liakhovetski@linux.intel.com>
X-Patchwork-Id: 11553453
Return-Path: <SRS0=97JA=66=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4E65190
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 16 May 2020 10:16:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2C0E62076A
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 16 May 2020 10:16:16 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726237AbgEPKQP (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 16 May 2020 06:16:15 -0400
Received: from mga12.intel.com ([192.55.52.136]:37165 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725792AbgEPKQN (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 16 May 2020 06:16:13 -0400
IronPort-SDR: 
 i+262E0LkHnpBm4VMX8kyunPQIuqPzMIOr4ry+PWW7Wq4FU2BZZ6CcPkukx/tkbA16AfbTU5ye
 8GmsR7q2CTnQ==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga007.jf.intel.com ([10.7.209.58])
  by fmsmga106.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 16 May 2020 03:16:12 -0700
IronPort-SDR: 
 E8NjAMPFQKWjtoqyfArlrqD9tn/bYi0ZDSQbC9qS2Zuma7opB/dZMxV7q0MJfSmBS39u84u+9m
 2qG9OG/tx+dA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,398,1583222400";
   d="scan'208";a="252322439"
Received: from gliakhov-mobl2.ger.corp.intel.com (HELO
 ubuntu.ger.corp.intel.com) ([10.249.40.45])
  by orsmga007.jf.intel.com with ESMTP; 16 May 2020 03:16:10 -0700
From: Guennadi Liakhovetski <guennadi.liakhovetski@linux.intel.com>
To: kvm@vger.kernel.org
Cc: linux-remoteproc@vger.kernel.org,
        virtualization@lists.linux-foundation.org,
        sound-open-firmware@alsa-project.org,
        Pierre-Louis Bossart <pierre-louis.bossart@linux.intel.com>,
        Liam Girdwood <liam.r.girdwood@linux.intel.com>
Subject: [PATCH RFC] vhost: add an SOF Audio DSP driver
Date: Sat, 16 May 2020 12:16:09 +0200
Message-Id: <20200516101609.2845-1-guennadi.liakhovetski@linux.intel.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The SOF ADSP vhost driver consists of two parts: a sound and a vhost
part. This patch implements the vhost part of the driver. It handles
QEMU communication with the vhost misc device and virtual queues to
any VirtIO RPMsg guests.

Signed-off-by: Guennadi Liakhovetski <guennadi.liakhovetski@linux.intel.com>
---

This is marked as an RFC / request for review, since it depends on other
patches, that haven't been merged yet. It uses the vhost RPMsg API, submitted
minutes ago to the lists
https://lists.linuxfoundation.org/pipermail/virtualization/2020-May/047669.html
and is a part of the SOF virtualisation project
https://github.com/thesofproject/linux/pull/1501/commits

Thanks
Guennadi

 drivers/vhost/Kconfig  |  10 +
 drivers/vhost/Makefile |   3 +
 drivers/vhost/adsp.c   | 618 +++++++++++++++++++++++++++++++++++++++++++++++++
 3 files changed, 631 insertions(+)
 create mode 100644 drivers/vhost/adsp.c

```
#### [PATCH v2] kvm: Fix false positive RCU usage warning
##### From: madhuparnabhowmik10@gmail.com

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Madhuparna Bhowmik <madhuparnabhowmik10@gmail.com>
X-Patchwork-Id: 11553385
Return-Path: <SRS0=97JA=66=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C5FCD90
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 16 May 2020 08:22:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AD3E7207D4
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 16 May 2020 08:22:43 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="kSHTwd5e"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726399AbgEPIWk (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 16 May 2020 04:22:40 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:34386 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725934AbgEPIWj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 16 May 2020 04:22:39 -0400
Received: from mail-pj1-x1044.google.com (mail-pj1-x1044.google.com
 [IPv6:2607:f8b0:4864:20::1044])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id B1F44C061A0C;
        Sat, 16 May 2020 01:22:39 -0700 (PDT)
Received: by mail-pj1-x1044.google.com with SMTP id fu13so2110384pjb.5;
        Sat, 16 May 2020 01:22:39 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=n8zeuSyWYmnUTCcGG4KcbVscwA04lg+t/YXhdGOdoRk=;
        b=kSHTwd5eDGUl/K2MsusgZkFTMR3AophuUBe1kXDJlVfE5ua9O9OGjGOTYBUA3y5LCn
         8hfYpuOH9CiRvEIBKKz0DdncM80p7x2LCzSJsHtx9GOPiVNuYor8fBKkYpooLG+K18tI
         8c2l3vKaAQh3GcMZwwMvWipE1/aFXrVcw2aOz/ihBV690LmRmrcCqn4JXXF9u7tpAnRQ
         ymfsLBjAXaAY2/IYj7vPtMnKY5CNAK5wHgJ846IwYx/qZmLwhq4NKXE0mqvPU0LgGQxw
         YgOazcAPN8DRZkJWwS5Ds8FcdLH04a4/lCqZhFVRLctKTXmMN+hM+6Jb5xlsWjDkNWYd
         sudg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=n8zeuSyWYmnUTCcGG4KcbVscwA04lg+t/YXhdGOdoRk=;
        b=ZB79viSLq4sH6E9R2OfAZX+sXv20vMHAhBRN1KEcHy0lqX61n3eaDaT2e8PlP586ic
         /RQV/Y/P6UShlsgQlFN+Ia2LH05DCTt7pvhorEZEDY+dVljlq0OIni6DLi98G3l6wSFq
         T70fLxlpnXt9R3EKU3jW0UwZ4X2gqGsMEHbcoZdFOiG9oHOab43Qc+AzlEmNzJhvbyZW
         GtxEqU1HTEFfDPTA8AXwDK7h1wQe74FtLoJ03UwQDpFwtmeiAOihfXY26VrsX+osLhYB
         /GgrCy2m3lWMBfdmsEr8A8+SBRGYixP2f4MhfhWqq9Daa05C1CRUezVfS9W3FY6WcbD8
         itug==
X-Gm-Message-State: AOAM531pT426NTHMwnz7c8aDkkVlqKw35TmUUt/HwKVZtK2KLtzLy2j3
        7612Q/Qxo2YMMJ0h+8Vujg==
X-Google-Smtp-Source: 
 ABdhPJy0lauqLn17lbGE3w8KJHGHD9NuhDV2LLqXRRaRQTMDJP5PCGFyuaHLhQCh2EmHugUqCHILZg==
X-Received: by 2002:a17:90b:1492:: with SMTP id
 js18mr1459691pjb.212.1589617359233;
        Sat, 16 May 2020 01:22:39 -0700 (PDT)
Received: from localhost.localdomain
 ([2402:3a80:13a5:a61b:b5d4:b438:1bc1:57f3])
        by smtp.gmail.com with ESMTPSA id
 j7sm3695288pfi.160.2020.05.16.01.22.33
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Sat, 16 May 2020 01:22:38 -0700 (PDT)
From: madhuparnabhowmik10@gmail.com
To: pbonzini@redhat.com, sean.j.christopherson@intel.com,
        vkuznets@redhat.com, wanpengli@tencent.com, jmattson@google.com,
        tglx@linutronix.de, bp@alien8.de
Cc: x86@kernel.org, kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        joel@joelfernandes.org, paulmck@kernel.org, frextrite@gmail.com,
        linux-kernel-mentees@lists.linuxfoundation.org,
        Madhuparna Bhowmik <madhuparnabhowmik10@gmail.com>
Subject: [PATCH v2] kvm: Fix false positive RCU usage warning
Date: Sat, 16 May 2020 13:52:27 +0530
Message-Id: <20200516082227.22194-1-madhuparnabhowmik10@gmail.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Madhuparna Bhowmik <madhuparnabhowmik10@gmail.com>

Fix the following false positive warnings:

[ 9403.765413][T61744] =============================
[ 9403.786541][T61744] WARNING: suspicious RCU usage
[ 9403.807865][T61744] 5.7.0-rc1-next-20200417 #4 Tainted: G             L
[ 9403.838945][T61744] -----------------------------
[ 9403.860099][T61744] arch/x86/kvm/mmu/page_track.c:257 RCU-list traversed in non-reader section!!

and

[ 9405.859252][T61751] =============================
[ 9405.859258][T61751] WARNING: suspicious RCU usage
[ 9405.880867][T61755] -----------------------------
[ 9405.911936][T61751] 5.7.0-rc1-next-20200417 #4 Tainted: G             L
[ 9405.911942][T61751] -----------------------------
[ 9405.911950][T61751] arch/x86/kvm/mmu/page_track.c:232 RCU-list traversed in non-reader section!!

Since srcu read lock is held, these are false positive warnings.
Therefore, pass condition srcu_read_lock_held() to
list_for_each_entry_rcu().

Reported-by: kernel test robot <lkp@intel.com>
Signed-off-by: Madhuparna Bhowmik <madhuparnabhowmik10@gmail.com>
---
v2:
-Rebase v5.7-rc5

 arch/x86/kvm/mmu/page_track.c | 6 ++++--
 1 file changed, 4 insertions(+), 2 deletions(-)

```
