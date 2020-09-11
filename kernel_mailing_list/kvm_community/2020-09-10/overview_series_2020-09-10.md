#### [PATCH v7 1/3] vhost: convert VHOST_VSOCK_SET_RUNNING to a generic ioctl
##### From: Guennadi Liakhovetski <guennadi.liakhovetski@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Guennadi Liakhovetski
 <guennadi.liakhovetski@linux.intel.com>
X-Patchwork-Id: 11767671
Return-Path: <SRS0=BU+x=CT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 57AF2698
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Sep 2020 11:41:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 456DA208CA
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Sep 2020 11:41:15 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730356AbgIJLks (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 10 Sep 2020 07:40:48 -0400
Received: from mga01.intel.com ([192.55.52.88]:26478 "EHLO mga01.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729779AbgIJLOk (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 10 Sep 2020 07:14:40 -0400
IronPort-SDR: 
 LGPPkhLH79C9yO2XvH+Mse9InR04ZMuiOmST0BngJ+ZjhCA1wOg/ldX9DNNLrB+rkV5Rez+Bap
 lT8xHJ0b3kjg==
X-IronPort-AV: E=McAfee;i="6000,8403,9739"; a="176571453"
X-IronPort-AV: E=Sophos;i="5.76,412,1592895600";
   d="scan'208";a="176571453"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by fmsmga101.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 10 Sep 2020 04:14:03 -0700
IronPort-SDR: 
 XtgEWbX5vEGvUv2ceRqhLfJyQwJyzCzTXVPYYvbq5WWT6UqVYbUxIYcUSgWLsPopogA1/pfSNH
 e80Jvvq1Epew==
X-IronPort-AV: E=Sophos;i="5.76,412,1592895600";
   d="scan'208";a="286530921"
Received: from gliakhov-mobl2.ger.corp.intel.com (HELO
 ubuntu.ger.corp.intel.com) ([10.252.39.14])
  by fmsmga008-auth.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 10 Sep 2020 04:14:01 -0700
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
        Mathieu Poirier <mathieu.poirier@linaro.org>,
        Vincent Whitchurch <vincent.whitchurch@axis.com>
Subject: [PATCH v7 1/3] vhost: convert VHOST_VSOCK_SET_RUNNING to a generic
 ioctl
Date: Thu, 10 Sep 2020 13:13:49 +0200
Message-Id: <20200910111351.20526-2-guennadi.liakhovetski@linux.intel.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20200910111351.20526-1-guennadi.liakhovetski@linux.intel.com>
References: <20200910111351.20526-1-guennadi.liakhovetski@linux.intel.com>
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
#### [RFC v3 1/2] KVM: VMX: Convert vcpu_vmx.exit_reason to a union
##### From: Chenyi Qiang <chenyi.qiang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Chenyi Qiang <chenyi.qiang@intel.com>
X-Patchwork-Id: 11767105
Return-Path: <SRS0=BU+x=CT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 939FC618
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Sep 2020 08:40:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7736F20872
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Sep 2020 08:40:24 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730224AbgIJIkW (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 10 Sep 2020 04:40:22 -0400
Received: from mga07.intel.com ([134.134.136.100]:49000 "EHLO mga07.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728709AbgIJIfy (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 10 Sep 2020 04:35:54 -0400
IronPort-SDR: 
 FYEqmToeGzNhIHNz+xntoAnZDx6m0qfpmS44SzmKaGaPiPTiBPIO3IBzSVwxZW5xHiF9ruCGSM
 NW1IgQf1UAFg==
X-IronPort-AV: E=McAfee;i="6000,8403,9739"; a="222691431"
X-IronPort-AV: E=Sophos;i="5.76,412,1592895600";
   d="scan'208";a="222691431"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga004.fm.intel.com ([10.253.24.48])
  by orsmga105.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 10 Sep 2020 01:35:46 -0700
IronPort-SDR: 
 85sFonMLuIAQSeMhXE15mbFMP/QFDZwo83tQaA3xbDnJtYkCvHIhPQHiqduM4nMc4e8OVx9Drn
 4ifDqyhwZ5cA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.76,412,1592895600";
   d="scan'208";a="329255937"
Received: from chenyi-pc.sh.intel.com ([10.239.159.72])
  by fmsmga004.fm.intel.com with ESMTP; 10 Sep 2020 01:35:43 -0700
From: Chenyi Qiang <chenyi.qiang@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Xiaoyao Li <xiaoyao.li@intel.com>
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [RFC v3 1/2] KVM: VMX: Convert vcpu_vmx.exit_reason to a union
Date: Thu, 10 Sep 2020 16:37:50 +0800
Message-Id: <20200910083751.26686-2-chenyi.qiang@intel.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200910083751.26686-1-chenyi.qiang@intel.com>
References: <20200910083751.26686-1-chenyi.qiang@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Sean Christopherson <sean.j.christopherson@intel.com>

Convert vcpu_vmx.exit_reason from a u32 to a union (of size u32).  The
full VM_EXIT_REASON field is comprised of a 16-bit basic exit reason in
bits 15:0, and single-bit modifiers in bits 31:16.

Historically, KVM has only had to worry about handling the "failed
VM-Entry" modifier, which could only be set in very specific flows and
required dedicated handling.  I.e. manually stripping the FAILED_VMENTRY
bit was a somewhat viable approach.  But even with only a single bit to
worry about, KVM has had several bugs related to comparing a basic exit
reason against the full exit reason store in vcpu_vmx.

Upcoming Intel features, e.g. SGX, will add new modifier bits that can
be set on more or less any VM-Exit, as opposed to the significantly more
restricted FAILED_VMENTRY, i.e. correctly handling everything in one-off
flows isn't scalable.  Tracking exit reason in a union forces code to
explicitly choose between consuming the full exit reason and the basic
exit, and is a convenient way to document and access the modifiers.

No functional change intended.

Cc: Xiaoyao Li <xiaoyao.li@intel.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/vmx/nested.c | 42 ++++++++++++++++---------
 arch/x86/kvm/vmx/vmx.c    | 64 ++++++++++++++++++++-------------------
 arch/x86/kvm/vmx/vmx.h    | 25 ++++++++++++++-
 3 files changed, 84 insertions(+), 47 deletions(-)

```
#### [Bug 209155] KVM Linux guest with more than 1 CPU panics after commit 404d5d7bff0d419fe11c7eaebca9ec8f25258f95 on old CPU (Phenom x4)
##### From: bugzilla-daemon@bugzilla.kernel.org

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: bugzilla-daemon@bugzilla.kernel.org
X-Patchwork-Id: 11767723
Return-Path: <SRS0=BU+x=CT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0A15B746
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Sep 2020 12:14:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E38B52076D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Sep 2020 12:14:45 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726989AbgIJMO1 convert rfc822-to-8bit (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 10 Sep 2020 08:14:27 -0400
Received: from mail.kernel.org ([198.145.29.99]:44092 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1730450AbgIJMNm (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 10 Sep 2020 08:13:42 -0400
From: bugzilla-daemon@bugzilla.kernel.org
To: kvm@vger.kernel.org
Subject: [Bug 209155] KVM Linux guest with more than 1 CPU panics after
 commit 404d5d7bff0d419fe11c7eaebca9ec8f25258f95 on old CPU (Phenom x4)
Date: Thu, 10 Sep 2020 12:12:58 +0000
X-Bugzilla-Reason: None
X-Bugzilla-Type: changed
X-Bugzilla-Watch-Reason: AssignedTo virtualization_kvm@kernel-bugs.osdl.org
X-Bugzilla-Product: Virtualization
X-Bugzilla-Component: kvm
X-Bugzilla-Version: unspecified
X-Bugzilla-Keywords: 
X-Bugzilla-Severity: normal
X-Bugzilla-Who: kronenpj@kronenpj.dyndns.org
X-Bugzilla-Status: NEW
X-Bugzilla-Resolution: 
X-Bugzilla-Priority: P1
X-Bugzilla-Assigned-To: virtualization_kvm@kernel-bugs.osdl.org
X-Bugzilla-Flags: 
X-Bugzilla-Changed-Fields: 
Message-ID: <bug-209155-28872-vK91HaShfP@https.bugzilla.kernel.org/>
In-Reply-To: <bug-209155-28872@https.bugzilla.kernel.org/>
References: <bug-209155-28872@https.bugzilla.kernel.org/>
X-Bugzilla-URL: https://bugzilla.kernel.org/
Auto-Submitted: auto-generated
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

https://bugzilla.kernel.org/show_bug.cgi?id=209155

--- Comment #14 from Paul K. (kronenpj@kronenpj.dyndns.org) ---
I'm having a bit of a problem applying the patches cleanly. Working with both
v5.9-rc3 and 5.9-rc4 give the same:

Patch 1/3 goes fine:
$ patch -p1 < /net/phenom/export/home2/users/kronenpj/tmp/patch1-3.txt 
patching file arch/x86/kvm/svm/svm.c

Patch 2/3 fails on hunk #3:
$ patch -p1 < /net/phenom/export/home2/users/kronenpj/tmp/patch2-3.txt 
patching file arch/x86/kvm/svm/svm.c
Hunk #1 succeeded at 3349 (offset 2 lines).
Hunk #2 succeeded at 3504 (offset 4 lines).
Hunk #3 FAILED at 3533.
1 out of 3 hunks FAILED -- saving rejects to file arch/x86/kvm/svm/svm.c.rej

$ cat svm.c.rej 
        return exit_fastpath;

Adding that line manually and continuing with the third patch:
$ patch -p1 < /net/phenom/export/home2/users/kronenpj/tmp/patch3-3.txt 
patching file arch/x86/kvm/svm/svm.c
Hunk #2 succeeded at 3536 with fuzz 2 (offset 8 lines).

```
#### [PATCH v2 1/9] KVM: LAPIC: Return 0 when getting the tscdeadline timer if the lapic is hw disabled
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11767285
Return-Path: <SRS0=BU+x=CT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D75F692C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Sep 2020 09:51:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AD92121582
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Sep 2020 09:51:49 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="YMfqaa8x"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730486AbgIJJvW (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 10 Sep 2020 05:51:22 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:40670 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729781AbgIJJvE (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 10 Sep 2020 05:51:04 -0400
Received: from mail-pg1-x544.google.com (mail-pg1-x544.google.com
 [IPv6:2607:f8b0:4864:20::544])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 1A868C061573;
        Thu, 10 Sep 2020 02:51:04 -0700 (PDT)
Received: by mail-pg1-x544.google.com with SMTP id 34so3935863pgo.13;
        Thu, 10 Sep 2020 02:51:04 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:in-reply-to:references;
        bh=cdLm++xYkcDurXtOuboxDgxpAJcdgeOErpU/g8ChEs0=;
        b=YMfqaa8x3VnmAW238O4aMYbWh8YpJvMiNexqZYyhRbQfHPkg05ZBKLaD5SMzm6EF3b
         RZV8uJMMz6SvQ8anjIMo3AcFo8Ngd+Y1ObHkrdzz9aBivexABBpCWABoUwn8SiwOzug2
         jRbyqwM6e/r2S1dFECbpseje/9r4I89d7me4hNIbTUxqgCeLeCOzM9kQLdcKhJDGgLcQ
         F2vUqSQqJIfF0VQ/3X3AwJz4QZwR24izr+rwNKTLEIWV0TORwYBGPOdBQPkY891vAvNg
         6BemgllzAGTdycAALowGnWJIFeGuKqIihs2Q50n2A/0W74emODcM/ME8ZXkfo1Ivqwhj
         AfDw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references;
        bh=cdLm++xYkcDurXtOuboxDgxpAJcdgeOErpU/g8ChEs0=;
        b=I0zo5PjAJVuM1I8+PHdeLV4rceqdEiIWjzcYdshSHlCoPcjAmoxzTWUK/daRbwieQR
         kEge//iuy+fzmGVwAymyDwkgbg+IDQwambVbIdZbadqG0Ar2Suof2k9Ref7ww4RSC+4Y
         6M5TgK4IllR/ayuqAFIwtGanQoV2/3WeAIfRVdmKCiWQCaeGFCsvTvdWfFWqurkOzdfz
         +Z8bPXIF8roOdI5H3RjW/OdDArSASm/utKBU/M4dxk5xPrTHqt5aSQrS3ImIyl4gEwSs
         G+3mbJql4Z2ht7e1uU5V+LCCPhGQbdjhlrh6mIKvoX37e6GZhIJ1ZlfoifxEzsF8xgUC
         iaBQ==
X-Gm-Message-State: AOAM530oD9tW1ZcJ8DoRTh3Sbqt11Y4vMNOxrbmLesn/1fSsvcAmvpAS
        ZKXK5zWZiXhqWvfKCChoRV9kveEPXTg=
X-Google-Smtp-Source: 
 ABdhPJxOb7Bzcz7WquKtLWovKvX25s8F05+NUPa+yNzWmnHRS8zIOvHL10P8R3RK3KCDcdhoXOwFZQ==
X-Received: by 2002:a63:1d5a:: with SMTP id d26mr3735967pgm.432.1599731460205;
        Thu, 10 Sep 2020 02:51:00 -0700 (PDT)
Received: from localhost.localdomain ([103.7.29.6])
        by smtp.googlemail.com with ESMTPSA id
 e1sm2576534pfl.162.2020.09.10.02.50.57
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Thu, 10 Sep 2020 02:50:59 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>
Subject: [PATCH v2 1/9] KVM: LAPIC: Return 0 when getting the tscdeadline
 timer if the lapic is hw disabled
Date: Thu, 10 Sep 2020 17:50:36 +0800
Message-Id: <1599731444-3525-2-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
In-Reply-To: <1599731444-3525-1-git-send-email-wanpengli@tencent.com>
References: <1599731444-3525-1-git-send-email-wanpengli@tencent.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

Return 0 when getting the tscdeadline timer if the lapic is hw disabled.

Suggested-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kvm/lapic.c | 3 +--
 1 file changed, 1 insertion(+), 2 deletions(-)

```
#### [PATCH] KVM: MIPS: Change the definition of kvm type
##### From: Huacai Chen <chenhc@lemote.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Huacai Chen <chenhc@lemote.com>
X-Patchwork-Id: 11767419
Return-Path: <SRS0=BU+x=CT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 92C4592C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Sep 2020 10:34:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 73BD3214F1
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Sep 2020 10:34:01 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="DAe9S+dX"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727090AbgIJKd7 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 10 Sep 2020 06:33:59 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:47432 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725992AbgIJKd5 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 10 Sep 2020 06:33:57 -0400
Received: from mail-pg1-x541.google.com (mail-pg1-x541.google.com
 [IPv6:2607:f8b0:4864:20::541])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 5993AC061573;
        Thu, 10 Sep 2020 03:33:57 -0700 (PDT)
Received: by mail-pg1-x541.google.com with SMTP id t14so3998213pgl.10;
        Thu, 10 Sep 2020 03:33:57 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id;
        bh=n5bejNfhnwg4ZD6VA0P2oapc248CaAsST/crmsvS6LA=;
        b=DAe9S+dXyHd8nHH/FsQQ5tioon9wlXS94y2osIBQy+LDGwwKYfSjtVxMVxLL8nYYtS
         Mh2+f1Clro6SEFmlTr9hwL/RsfzVOV2eMjMHJ9cp+//Ye8jJFfLyjZyPXPwLct8Pcben
         PIzcNbrZ6IEQ7SUJAp7gzh/5aVrK+VuQYsi2uK3AW+IdnlB4z/qL5rUF5fdjQvG+XvSo
         pogTA4s7sz8bgnclF/zdc3g0L05phrKhxZ4LyLQt1bQkEMKPCf+Aaqi2GGSStqm/PQjs
         obmtlyA0t2Km1DMYOBQKl4V2KNFDPE6RegBR8kPnucHqp8LxOO/5OiW3bQgcDLxr6O4p
         zddg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id;
        bh=n5bejNfhnwg4ZD6VA0P2oapc248CaAsST/crmsvS6LA=;
        b=sO8N9w8+JarPzG3eCQuTblDtdktlYfZ/n153pQ8t2uUhOYFo5o3dl87BJy6jwL6AZf
         Aqs5w1ivoyPi1mkgjJUmoIO0aQ8zftCezI0gdJeRK9qbAGeS3TWWr9TubynP4g52pgwP
         LhmRTZOQxb5B9qNF5eH1/dQa9Oocd9pbRZUIMig8eQm3gwekcL3dIA8N78qj4UTrOspV
         xTifdECYAhKSlySWzo1haXvqpq1tkSJMTtRgugBkEG8ZCMuqc7ukiOtdPwJN7M0f3D5D
         MJFMUWmiWLuCVTCtZzgZpIi+1yYYy3yTq+fbQYgz4H1tz9B7VNfePNX77UaQ9lxKUncD
         86Dw==
X-Gm-Message-State: AOAM531p7ZIRiysUeD4c7avmmPq9S0H2oklf7lZ6+f7rNBqF1yVJg6C1
        0UslW83dzKWEZ3B6VCwGY3Q=
X-Google-Smtp-Source: 
 ABdhPJxoQxBqPWLHTAFbLDAOl8r51m9uR9FkMGkNvHuBRPaf4/3IoDSpWshdI9Ddwk+YXWi+XZSqBw==
X-Received: by 2002:a62:7a53:: with SMTP id v80mr4680246pfc.129.1599734036685;
        Thu, 10 Sep 2020 03:33:56 -0700 (PDT)
Received: from software.domain.org ([45.77.13.216])
        by smtp.gmail.com with ESMTPSA id
 f12sm1972065pjm.5.2020.09.10.03.33.52
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Thu, 10 Sep 2020 03:33:56 -0700 (PDT)
From: Huacai Chen <chenhc@lemote.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
 Thomas Bogendoerfer <tsbogend@alpha.franken.de>,
 Aleksandar Markovic <aleksandar.qemu.devel@gmail.com>, =?utf-8?q?Philippe_M?=
	=?utf-8?q?athieu-Daud=C3=A9?= <f4bug@amsat.org>,
 Thomas Huth <thuth@redhat.com>
Cc: kvm@vger.kernel.org, linux-mips@vger.kernel.org,
        Fuxin Zhang <zhangfx@lemote.com>,
        Huacai Chen <chenhuacai@gmail.com>,
        Jiaxun Yang <jiaxun.yang@flygoat.com>,
        Huacai Chen <chenhc@lemote.com>, stable@vger.kernel.org
Subject: [PATCH] KVM: MIPS: Change the definition of kvm type
Date: Thu, 10 Sep 2020 18:33:51 +0800
Message-Id: <1599734031-28746-1-git-send-email-chenhc@lemote.com>
X-Mailer: git-send-email 2.7.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

MIPS defines two kvm types:

 #define KVM_VM_MIPS_TE          0
 #define KVM_VM_MIPS_VZ          1

In Documentation/virt/kvm/api.rst it is said that "You probably want to
use 0 as machine type", which implies that type 0 be the "automatic" or
"default" type. And, in user-space libvirt use the null-machine (with
type 0) to detect the kvm capability, which returns "KVM not supported"
on a VZ platform.

I try to fix it in QEMU but it is ugly:
https://lists.nongnu.org/archive/html/qemu-devel/2020-08/msg05629.html

And Thomas Huth suggests me to change the definition of kvm type:
https://lists.nongnu.org/archive/html/qemu-devel/2020-09/msg03281.html

So I define like this:

 #define KVM_VM_MIPS_AUTO        0
 #define KVM_VM_MIPS_VZ          1
 #define KVM_VM_MIPS_TE          2

Since VZ and TE cannot co-exists, using type 0 on a TE platform will
still return success (so old user-space tools have no problems on new
kernels); the advantage is that using type 0 on a VZ platform will not
return failure. So, the only problem is "new user-space tools use type
2 on old kernels", but if we treat this as a kernel bug, we can backport
this patch to old stable kernels.

Cc: stable@vger.kernel.org
Signed-off-by: Huacai Chen <chenhc@lemote.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
Reviewed-by: Philippe Mathieu-Daudé <f4bug@amsat.org>
---
 arch/mips/kvm/mips.c     | 2 ++
 include/uapi/linux/kvm.h | 5 +++--
 2 files changed, 5 insertions(+), 2 deletions(-)

```
#### [PATCH 1/3 v2] KVM: SVM: Replace numeric value for SME CPUID leaf with a #define
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11766383
Return-Path: <SRS0=BU+x=CT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 723A1746
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Sep 2020 02:24:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 52C5B21D7E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Sep 2020 02:24:51 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="oGy20AHZ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730878AbgIJCYr (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 9 Sep 2020 22:24:47 -0400
Received: from userp2120.oracle.com ([156.151.31.85]:34574 "EHLO
        userp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1730794AbgIJCWg (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 9 Sep 2020 22:22:36 -0400
Received: from pps.filterd (userp2120.oracle.com [127.0.0.1])
        by userp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 08A2K0o9120754;
        Thu, 10 Sep 2020 02:22:31 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references; s=corp-2020-01-29;
 bh=9Yu0+hVjg349shgtmGEHPIIhGF87WXKFZaup59ONGuE=;
 b=oGy20AHZBsiGauYoT/Jkk5Sg8YCg4T3XRcDv9haSXyhOLHMoZRT5AVnhRGgIaUEhOzq5
 ekqov6BKhPgW1iH/gLtYvOHOJrI7w2gKk2ZpV5krnXACgxZhOJghJk/cPKP4801/Rt/c
 qxx3iDw8DVOTmgm0R70Xzle6mriN/lUjCVGOGNz0UvCs4Qpn4fpzVsUQVsssCf/0utE6
 /1+M6W8FOupVycCuvGRuoXpjtF8TiHCDNDdPgHvPI44LV6iUrMr/dK8tJb/7MM5ji4jU
 PWoywfltL+Am/AwNLHECJZ6eQXznbZ1+ZCqEBfQXORZNZ9v12EMCNTBGKefjs1iWgzjs IQ==
Received: from aserp3020.oracle.com (aserp3020.oracle.com [141.146.126.70])
        by userp2120.oracle.com with ESMTP id 33c3an5514-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=FAIL);
        Thu, 10 Sep 2020 02:22:30 +0000
Received: from pps.filterd (aserp3020.oracle.com [127.0.0.1])
        by aserp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 08A2L6Pf023034;
        Thu, 10 Sep 2020 02:22:30 GMT
Received: from aserv0122.oracle.com (aserv0122.oracle.com [141.146.126.236])
        by aserp3020.oracle.com with ESMTP id 33cmk88wee-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 10 Sep 2020 02:22:30 +0000
Received: from abhmp0013.oracle.com (abhmp0013.oracle.com [141.146.116.19])
        by aserv0122.oracle.com (8.14.4/8.14.4) with ESMTP id 08A2MTDe012667;
        Thu, 10 Sep 2020 02:22:29 GMT
Received: from nsvm-sadhukhan-1.osdevelopmeniad.oraclevcn.com
 (/100.100.230.216)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Wed, 09 Sep 2020 19:22:29 -0700
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com, thomas.lendacky@amd.com
Subject: [PATCH 1/3 v2] KVM: SVM: Replace numeric value for SME CPUID leaf
 with a #define
Date: Thu, 10 Sep 2020 02:22:09 +0000
Message-Id: <20200910022211.5417-2-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.18.4
In-Reply-To: <20200910022211.5417-1-krish.sadhukhan@oracle.com>
References: <20200910022211.5417-1-krish.sadhukhan@oracle.com>
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9739
 signatures=668679
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 spamscore=0
 malwarescore=0 phishscore=0
 mlxlogscore=936 bulkscore=0 adultscore=0 mlxscore=0 suspectscore=1
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2006250000
 definitions=main-2009100020
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9739
 signatures=668679
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 phishscore=0
 priorityscore=1501
 clxscore=1015 bulkscore=0 malwarescore=0 lowpriorityscore=0
 mlxlogscore=951 suspectscore=1 adultscore=0 mlxscore=0 impostorscore=0
 spamscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2009100020
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 arch/x86/boot/compressed/mem_encrypt.S | 5 +++--
 arch/x86/include/asm/cpufeatures.h     | 5 +++++
 arch/x86/kernel/cpu/amd.c              | 2 +-
 arch/x86/kernel/cpu/scattered.c        | 4 ++--
 arch/x86/kvm/cpuid.c                   | 2 +-
 arch/x86/kvm/svm/svm.c                 | 4 ++--
 arch/x86/mm/mem_encrypt_identity.c     | 4 ++--
 7 files changed, 16 insertions(+), 10 deletions(-)

```
#### [PATCH 1/6] hw/ssi/aspeed_smc: Rename max_slaves as max_devices
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
 <philmd@redhat.com>
X-Patchwork-Id: 11766775
Return-Path: <SRS0=BU+x=CT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8FC5E92C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Sep 2020 07:04:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 62EBF20809
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Sep 2020 07:04:30 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="QL+DgfgT"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730260AbgIJHEW (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 10 Sep 2020 03:04:22 -0400
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:37803 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1730244AbgIJHCA (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 10 Sep 2020 03:02:00 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1599721305;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
  content-type:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=3LVq3GBMxvuW5ThC5No6G6me9ou9dAQJhQkLuf9vMHg=;
        b=QL+DgfgT8pjhrkQiJ2rf33LFQiiUqO8iBLjDYAs/6qiCdXV4/h7iTpdpaibkYFyOrZDDnR
        kh1k0PTc6h6l/LKd064POvEZ1btu4yHj6y0QMHLu5KxgSBP3F+TO7qiSofUh+ZkI40XzT3
        KE1DsOQgth4l6MR8iA0yPT4okknYA7A=
Received: from mail-wm1-f69.google.com (mail-wm1-f69.google.com
 [209.85.128.69]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-263-SVi5crgkPXuSVFmlbDmwWw-1; Thu, 10 Sep 2020 03:01:42 -0400
X-MC-Unique: SVi5crgkPXuSVFmlbDmwWw-1
Received: by mail-wm1-f69.google.com with SMTP id b73so1769599wmb.0
        for <kvm@vger.kernel.org>; Thu, 10 Sep 2020 00:01:42 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=3LVq3GBMxvuW5ThC5No6G6me9ou9dAQJhQkLuf9vMHg=;
        b=YWQRpz+KS5sFN+5OjnpL7MifFgDUtrw0nJ6w11FwsS1r8rL9wg4rvnxwSPdczhwq2W
         7kLTAgjeefT5XeZWQPSJXgGJoYdoyfUJnz3SgARknQE0CyJ5C3U7sTf1s/3IsH5HfnKC
         dERs80NBuIlk9kPRdKlV8YIkgT3pUquPJS9IqY7j1sSnmCTmNYir6jSVsmYGWBX3aB3N
         igGrN3l93fUpCEfl7XfuFYAfHohso3rHG1SDNUIkx7YTmhq3FYHa/IZNIqUR5kv5HYMT
         Fcr/D+epCPPcLcH1gqom+Cnc5x2vENIm7oLUI1W6TGs2HycJvghMD3iOWDZNVxyD4HYI
         B7PQ==
X-Gm-Message-State: AOAM533SAUgN/3uI1Ewkm+hrJjrgllsuitQCv0kww+Jrk59pUeutUiEm
        jF57/Gsn5pa0hwr4xoxKl4zjVfSG4GSXRtbyXzngQMj+tymlKsX4p3eS5vDtpIAlC4EPYiVpi2B
        HDuRQF44vlhwv
X-Received: by 2002:a7b:c182:: with SMTP id y2mr6733479wmi.21.1599721299988;
        Thu, 10 Sep 2020 00:01:39 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJzgp6jskt+jFoWEu9oClQRannFnMaW2ju14kuX/HT2/8P8+6b5Zro3I2ovA3LneRaIpwyvZzA==
X-Received: by 2002:a7b:c182:: with SMTP id y2mr6733445wmi.21.1599721299694;
        Thu, 10 Sep 2020 00:01:39 -0700 (PDT)
Received: from x1w.redhat.com (65.red-83-57-170.dynamicip.rima-tde.net.
 [83.57.170.65])
        by smtp.gmail.com with ESMTPSA id
 o124sm2127336wmb.2.2020.09.10.00.01.38
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 10 Sep 2020 00:01:39 -0700 (PDT)
From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>
To: qemu-devel@nongnu.org
Cc: =?utf-8?q?Alex_Benn=C3=A9e?= <alex.bennee@linaro.org>,
 kvm@vger.kernel.org, qemu-arm@nongnu.org,
 Marcelo Tosatti <mtosatti@redhat.com>,
 "Edgar E. Iglesias" <edgar.iglesias@gmail.com>,
 "Michael S. Tsirkin" <mst@redhat.com>,
 =?utf-8?q?C=C3=A9dric_Le_Goater?= <clg@kaod.org>,
 Marcel Apfelbaum <marcel.apfelbaum@gmail.com>,
 Laurent Vivier <lvivier@redhat.com>,
 Peter Maydell <peter.maydell@linaro.org>, Andrew Jeffery <andrew@aj.id.au>,
 Jason Wang <jasowang@redhat.com>, Thomas Huth <thuth@redhat.com>,
 Alistair Francis <alistair@alistair23.me>, qemu-trivial@nongnu.org,
 Eduardo Habkost <ehabkost@redhat.com>, Richard Henderson <rth@twiddle.net>,
 Joel Stanley <joel@jms.id.au>, Paolo Bonzini <pbonzini@redhat.com>,
	=?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>
Subject: [PATCH 1/6] hw/ssi/aspeed_smc: Rename max_slaves as max_devices
Date: Thu, 10 Sep 2020 09:01:26 +0200
Message-Id: <20200910070131.435543-2-philmd@redhat.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20200910070131.435543-1-philmd@redhat.com>
References: <20200910070131.435543-1-philmd@redhat.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In order to use inclusive terminology, rename max_slaves
as max_devices.

Signed-off-by: Philippe Mathieu-Daudé <philmd@redhat.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
Reviewed-by: Cédric Le Goater <clg@kaod.org>
---
 include/hw/ssi/aspeed_smc.h |  2 +-
 hw/ssi/aspeed_smc.c         | 40 ++++++++++++++++++-------------------
 2 files changed, 21 insertions(+), 21 deletions(-)

```
#### [RFC v10 01/25] scripts/update-linux-headers: Import iommu.h
##### From: Liu Yi L <yi.l.liu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Liu Yi L <yi.l.liu@intel.com>
X-Patchwork-Id: 11767601
Return-Path: <SRS0=BU+x=CT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DA1EC59D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Sep 2020 11:02:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BE4B821941
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Sep 2020 11:02:13 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730538AbgIJLB7 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 10 Sep 2020 07:01:59 -0400
Received: from mga12.intel.com ([192.55.52.136]:21743 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1730636AbgIJK7j (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 10 Sep 2020 06:59:39 -0400
IronPort-SDR: 
 XhRo6+qsk4Hzwac//UAWxyiB7v9skDl9kIIpI84Y48JQNkpwUzoodiNncdflfa1kV80/ZgXw/a
 vU6/ZxjorQOg==
X-IronPort-AV: E=McAfee;i="6000,8403,9739"; a="138025850"
X-IronPort-AV: E=Sophos;i="5.76,412,1592895600";
   d="scan'208";a="138025850"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by fmsmga106.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 10 Sep 2020 03:54:39 -0700
IronPort-SDR: 
 KYL+DBA7/CqRG61xGOcwFf2KrovP/8NEtBv7A9NJBAUou9bME+cOo+X8tBNE+nCSpQHT7S4X/h
 1/Khj93vKeuw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.76,412,1592895600";
   d="scan'208";a="334140036"
Received: from jacob-builder.jf.intel.com ([10.7.199.155])
  by orsmga008.jf.intel.com with ESMTP; 10 Sep 2020 03:54:39 -0700
From: Liu Yi L <yi.l.liu@intel.com>
To: qemu-devel@nongnu.org, alex.williamson@redhat.com,
        peterx@redhat.com, jasowang@redhat.com
Cc: mst@redhat.com, pbonzini@redhat.com, eric.auger@redhat.com,
        david@gibson.dropbear.id.au, jean-philippe@linaro.org,
        kevin.tian@intel.com, yi.l.liu@intel.com, jun.j.tian@intel.com,
        yi.y.sun@intel.com, hao.wu@intel.com, kvm@vger.kernel.org,
        Jacob Pan <jacob.jun.pan@linux.intel.com>,
        Yi Sun <yi.y.sun@linux.intel.com>,
        Cornelia Huck <cohuck@redhat.com>
Subject: [RFC v10 01/25] scripts/update-linux-headers: Import iommu.h
Date: Thu, 10 Sep 2020 03:56:14 -0700
Message-Id: <1599735398-6829-2-git-send-email-yi.l.liu@intel.com>
X-Mailer: git-send-email 2.7.4
In-Reply-To: <1599735398-6829-1-git-send-email-yi.l.liu@intel.com>
References: <1599735398-6829-1-git-send-email-yi.l.liu@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Eric Auger <eric.auger@redhat.com>

Update the script to import the new iommu.h uapi header.

Cc: Kevin Tian <kevin.tian@intel.com>
Cc: Jacob Pan <jacob.jun.pan@linux.intel.com>
Cc: Peter Xu <peterx@redhat.com>
Cc: Yi Sun <yi.y.sun@linux.intel.com>
Cc: Michael S. Tsirkin <mst@redhat.com>
Cc: Cornelia Huck <cohuck@redhat.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Acked-by: Cornelia Huck <cohuck@redhat.com>
Signed-off-by: Eric Auger <eric.auger@redhat.com>
---
 scripts/update-linux-headers.sh | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v12 1/2] virtio: let arch advertise guest's memory access restrictions
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 11767137
Return-Path: <SRS0=BU+x=CT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C457F698
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Sep 2020 08:54:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9883320872
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Sep 2020 08:54:23 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="Wx17EmnA"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730131AbgIJIyS (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 10 Sep 2020 04:54:18 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:33512 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728709AbgIJIyK (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 10 Sep 2020 04:54:10 -0400
Received: from pps.filterd (m0098399.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 08A8XGmj164198;
        Thu, 10 Sep 2020 04:53:59 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references; s=pp1;
 bh=sRPpqbahpQqemdeTO4/3zXQoLZgn4dX9e/cX2KkjQXU=;
 b=Wx17EmnASg7HC4jesWmzTo7M5hyKs/1rQu5XD9A1z6i5e/iIZkF+L7THzSnvYtyUjY7x
 iaOgtCqNpCcl6ZaKfAvuaJyiXwJ2JdecgBxjjgQdpL4LCJB75RK+n/7a+aXCJ5C6I8Ls
 WQIC2pL0qqylSUVZdljh2A2qG5IsqUIK41g2iePUCwvzcu6OXATlhamu6CTUZcP92gMa
 RibKqFvq0frW+tu9rNStrWI5Xbm9dApe7bexgGF+BdPXgrxkMVFW3YXla4TaDtdHhrL/
 ixEdAP1eLlDSLmSQ5NgMZLEtM7yryBdvlqCvRB+T3Ol/3GzXaqMdsf5e/OmG+ZtrhUvz 9Q==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 33fg431x25-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 10 Sep 2020 04:53:59 -0400
Received: from m0098399.ppops.net (m0098399.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 08A8XMQL164833;
        Thu, 10 Sep 2020 04:53:58 -0400
Received: from ppma01fra.de.ibm.com (46.49.7a9f.ip4.static.sl-reverse.com
 [159.122.73.70])
        by mx0a-001b2d01.pphosted.com with ESMTP id 33fg431x19-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 10 Sep 2020 04:53:58 -0400
Received: from pps.filterd (ppma01fra.de.ibm.com [127.0.0.1])
        by ppma01fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 08A8q1mR006833;
        Thu, 10 Sep 2020 08:53:56 GMT
Received: from b06avi18878370.portsmouth.uk.ibm.com
 (b06avi18878370.portsmouth.uk.ibm.com [9.149.26.194])
        by ppma01fra.de.ibm.com with ESMTP id 33c2a81ab2-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 10 Sep 2020 08:53:56 +0000
Received: from d06av25.portsmouth.uk.ibm.com (d06av25.portsmouth.uk.ibm.com
 [9.149.105.61])
        by b06avi18878370.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 08A8rrXG64946530
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 10 Sep 2020 08:53:53 GMT
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 6CD8711C054;
        Thu, 10 Sep 2020 08:53:53 +0000 (GMT)
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id A8A0B11C058;
        Thu, 10 Sep 2020 08:53:52 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.28.144])
        by d06av25.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Thu, 10 Sep 2020 08:53:52 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: linux-kernel@vger.kernel.org
Cc: pasic@linux.ibm.com, borntraeger@de.ibm.com, frankja@linux.ibm.com,
        mst@redhat.com, jasowang@redhat.com, cohuck@redhat.com,
        kvm@vger.kernel.org, linux-s390@vger.kernel.org,
        virtualization@lists.linux-foundation.org, thomas.lendacky@amd.com,
        david@gibson.dropbear.id.au, linuxram@us.ibm.com,
        hca@linux.ibm.com, gor@linux.ibm.com
Subject: [PATCH v12 1/2] virtio: let arch advertise guest's memory access
 restrictions
Date: Thu, 10 Sep 2020 10:53:49 +0200
Message-Id: <1599728030-17085-2-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1599728030-17085-1-git-send-email-pmorel@linux.ibm.com>
References: <1599728030-17085-1-git-send-email-pmorel@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-09-10_01:2020-09-10,2020-09-10 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 suspectscore=1 bulkscore=0
 clxscore=1015 priorityscore=1501 mlxlogscore=999 mlxscore=0 phishscore=0
 lowpriorityscore=0 spamscore=0 adultscore=0 malwarescore=0 impostorscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2006250000
 definitions=main-2009100079
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

An architecture may restrict host access to guest memory,
e.g. IBM s390 Secure Execution or AMD SEV.

Provide a new Kconfig entry the architecture can select,
CONFIG_ARCH_HAS_RESTRICTED_VIRTIO_MEMORY_ACCESS, when it provides
the arch_has_restricted_virtio_memory_access callback to advertise
to VIRTIO common code when the architecture restricts memory access
from the host.

The common code can then fail the probe for any device where
VIRTIO_F_ACCESS_PLATFORM is required, but not set.

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: Halil Pasic <pasic@linux.ibm.com>
Acked-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 drivers/virtio/Kconfig        |  6 ++++++
 drivers/virtio/virtio.c       | 15 +++++++++++++++
 include/linux/virtio_config.h | 10 ++++++++++
 3 files changed, 31 insertions(+)

```
#### [PATCH v3] KVM: arm64: Preserve PMCR immutable values across reset
##### From: Alexander Graf <graf@amazon.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Graf <graf@amazon.com>
X-Patchwork-Id: 11768193
Return-Path: <SRS0=BU+x=CT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9E22313B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Sep 2020 16:52:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7DCE62078B
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Sep 2020 16:52:01 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amazon.com header.i=@amazon.com
 header.b="YeYNSlrl"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726167AbgIJQvd (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 10 Sep 2020 12:51:33 -0400
Received: from smtp-fw-33001.amazon.com ([207.171.190.10]:31212 "EHLO
        smtp-fw-33001.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727024AbgIJQuu (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 10 Sep 2020 12:50:50 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.com; i=@amazon.com; q=dns/txt; s=amazon201209;
  t=1599756649; x=1631292649;
  h=from:to:cc:subject:date:message-id:mime-version:
   content-transfer-encoding;
  bh=9ENEb+OWsMgLP7SddzClIgFi508ntq+tzSER6yva+Q4=;
  b=YeYNSlrlJ9TU2G59HGQlzaM11FCaxRqCaohzPsW44xjMxroSCo6kD887
   1977+GdrZuXNXsFA6qvZ3nosi/Ngn9TThY5pP89GKVk91Io/RFqH6BGZu
   1OX/s6cd/L8uEI8LOtf5aKNgDEo3+3Zw+k4Pn01yG+Whj62tEaLqK82OP
   U=;
X-IronPort-AV: E=Sophos;i="5.76,413,1592870400";
   d="scan'208";a="73955160"
Received: from sea32-co-svc-lb4-vlan3.sea.corp.amazon.com (HELO
 email-inbound-relay-1d-38ae4ad2.us-east-1.amazon.com) ([10.47.23.38])
  by smtp-border-fw-out-33001.sea14.amazon.com with ESMTP;
 10 Sep 2020 16:42:59 +0000
Received: from EX13MTAUWC002.ant.amazon.com
 (iad12-ws-svc-p26-lb9-vlan2.iad.amazon.com [10.40.163.34])
        by email-inbound-relay-1d-38ae4ad2.us-east-1.amazon.com (Postfix) with
 ESMTPS id 80B89A240F;
        Thu, 10 Sep 2020 16:42:56 +0000 (UTC)
Received: from EX13D20UWC001.ant.amazon.com (10.43.162.244) by
 EX13MTAUWC002.ant.amazon.com (10.43.162.240) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Thu, 10 Sep 2020 16:42:53 +0000
Received: from u79c5a0a55de558.ant.amazon.com (10.43.161.85) by
 EX13D20UWC001.ant.amazon.com (10.43.162.244) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Thu, 10 Sep 2020 16:42:51 +0000
From: Alexander Graf <graf@amazon.com>
To: <kvmarm@lists.cs.columbia.edu>
CC: Marc Zyngier <maz@kernel.org>,
        <linux-arm-kernel@lists.infradead.org>, <kvm@vger.kernel.org>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Robin Murphy <robin.murphy@arm.com>,
        Mark Rutland <mark.rutland@arm.com>,
        Eric Auger <eric.auger@redhat.com>,
        Andrew Jones <drjones@redhat.com>
Subject: [PATCH v3] KVM: arm64: Preserve PMCR immutable values across reset
Date: Thu, 10 Sep 2020 18:42:43 +0200
Message-ID: <20200910164243.29253-1-graf@amazon.com>
X-Mailer: git-send-email 2.28.0.394.ge197136389
MIME-Version: 1.0
X-Originating-IP: [10.43.161.85]
X-ClientProxiedBy: EX13D40UWA004.ant.amazon.com (10.43.160.36) To
 EX13D20UWC001.ant.amazon.com (10.43.162.244)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We allow user space to set the PMCR register to any value. However,
when time comes for a vcpu reset (for example on PSCI online), PMCR
is reset to the hardware capabilities.

I would like to explicitly expose different PMU capabilities (number
of supported event counters) to the guest than hardware supports.
Ideally across vcpu resets.

So this patch adopts the reset path to only populate the immutable
PMCR register bits from hardware when they were not initialized
previously. This effectively means that on a normal reset, only the
guest settable fields are reset, while on vcpu creation the register
gets populated from hardware like before.

With this in place and a change in user space to invoke SET_ONE_REG
on the PMCR for every vcpu, I can reliably set the PMU event counter
number to arbitrary values.

Signed-off-by: Alexander Graf <graf@amazon.com>
---
 arch/arm64/kvm/sys_regs.c | 9 ++++++++-
 1 file changed, 8 insertions(+), 1 deletion(-)

```
#### [PATCH v7 01/16] iommu: Report domain nesting info
##### From: Liu Yi L <yi.l.liu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Liu Yi L <yi.l.liu@intel.com>
X-Patchwork-Id: 11767477
Return-Path: <SRS0=BU+x=CT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 076D259D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Sep 2020 10:44:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id EBC94206B8
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Sep 2020 10:44:50 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725855AbgIJKoq (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 10 Sep 2020 06:44:46 -0400
Received: from mga06.intel.com ([134.134.136.31]:21893 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728611AbgIJKoI (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 10 Sep 2020 06:44:08 -0400
IronPort-SDR: 
 YU/xfr0TYznu3J7oBfGfCD103UkYpP+z4pLSTdIl4ZsPLqL3AlQSjzKJ3egPGUDziNhFs8pZf6
 anff1jpLcQBw==
X-IronPort-AV: E=McAfee;i="6000,8403,9739"; a="220066280"
X-IronPort-AV: E=Sophos;i="5.76,412,1592895600";
   d="scan'208";a="220066280"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by orsmga104.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 10 Sep 2020 03:43:34 -0700
IronPort-SDR: 
 Q8ZMKACCpo2M5VtsGTtm1gIqPI663DUsQVkaDafwkJU2H00J07AmakgiRMiP1ws+Q8wCbAae6u
 09Zahmo9yacQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.76,412,1592895600";
   d="scan'208";a="334137179"
Received: from jacob-builder.jf.intel.com ([10.7.199.155])
  by orsmga008.jf.intel.com with ESMTP; 10 Sep 2020 03:43:34 -0700
From: Liu Yi L <yi.l.liu@intel.com>
To: alex.williamson@redhat.com, eric.auger@redhat.com,
        baolu.lu@linux.intel.com, joro@8bytes.org
Cc: kevin.tian@intel.com, jacob.jun.pan@linux.intel.com,
        ashok.raj@intel.com, yi.l.liu@intel.com, jun.j.tian@intel.com,
        yi.y.sun@intel.com, jean-philippe@linaro.org, peterx@redhat.com,
        jasowang@redhat.com, hao.wu@intel.com, stefanha@gmail.com,
        iommu@lists.linux-foundation.org, kvm@vger.kernel.org
Subject: [PATCH v7 01/16] iommu: Report domain nesting info
Date: Thu, 10 Sep 2020 03:45:18 -0700
Message-Id: <1599734733-6431-2-git-send-email-yi.l.liu@intel.com>
X-Mailer: git-send-email 2.7.4
In-Reply-To: <1599734733-6431-1-git-send-email-yi.l.liu@intel.com>
References: <1599734733-6431-1-git-send-email-yi.l.liu@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

IOMMUs that support nesting translation needs report the capability info
to userspace. It gives information about requirements the userspace needs
to implement plus other features characterizing the physical implementation.

This patch introduces a new IOMMU UAPI struct that gives information about
the nesting capabilities and features. This struct is supposed to be returned
by iommu_domain_get_attr() with DOMAIN_ATTR_NESTING attribute parameter, with
one domain whose type has been set to DOMAIN_ATTR_NESTING.

Cc: Kevin Tian <kevin.tian@intel.com>
CC: Jacob Pan <jacob.jun.pan@linux.intel.com>
Cc: Alex Williamson <alex.williamson@redhat.com>
Cc: Eric Auger <eric.auger@redhat.com>
Cc: Jean-Philippe Brucker <jean-philippe@linaro.org>
Cc: Joerg Roedel <joro@8bytes.org>
Cc: Lu Baolu <baolu.lu@linux.intel.com>
Signed-off-by: Liu Yi L <yi.l.liu@intel.com>
Signed-off-by: Jacob Pan <jacob.jun.pan@linux.intel.com>
---
v6 -> v7:
*) rephrase the commit message, replace the @data[] field in struct
   iommu_nesting_info with union per comments from Eric Auger.

v5 -> v6:
*) rephrase the feature notes per comments from Eric Auger.
*) rename @size of struct iommu_nesting_info to @argsz.

v4 -> v5:
*) address comments from Eric Auger.

v3 -> v4:
*) split the SMMU driver changes to be a separate patch
*) move the @addr_width and @pasid_bits from vendor specific
   part to generic part.
*) tweak the description for the @features field of struct
   iommu_nesting_info.
*) add description on the @data[] field of struct iommu_nesting_info

v2 -> v3:
*) remvoe cap/ecap_mask in iommu_nesting_info.
*) reuse DOMAIN_ATTR_NESTING to get nesting info.
*) return an empty iommu_nesting_info for SMMU drivers per Jean'
   suggestion.
---
 include/uapi/linux/iommu.h | 76 ++++++++++++++++++++++++++++++++++++++++++++++
 1 file changed, 76 insertions(+)

```
#### [PATCH] vfio: Fix typo of the device_state
##### From: Zenghui Yu <yuzenghui@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zenghui Yu <yuzenghui@huawei.com>
X-Patchwork-Id: 11769465
Return-Path: <SRS0=BU+x=CT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C55FE13B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Sep 2020 21:53:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B6B2D20732
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Sep 2020 21:53:36 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728678AbgIJVm5 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 10 Sep 2020 17:42:57 -0400
Received: from szxga05-in.huawei.com ([45.249.212.191]:11773 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1730522AbgIJMZr (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 10 Sep 2020 08:25:47 -0400
Received: from DGGEMS403-HUB.china.huawei.com (unknown [172.30.72.60])
        by Forcepoint Email with ESMTP id D4A7FAC483107EA50ED7;
        Thu, 10 Sep 2020 20:25:36 +0800 (CST)
Received: from DESKTOP-8RFUVS3.china.huawei.com (10.174.185.226) by
 DGGEMS403-HUB.china.huawei.com (10.3.19.203) with Microsoft SMTP Server id
 14.3.487.0; Thu, 10 Sep 2020 20:25:26 +0800
From: Zenghui Yu <yuzenghui@huawei.com>
To: <kvm@vger.kernel.org>, <linux-kernel@vger.kernel.org>
CC: <alex.williamson@redhat.com>, <cohuck@redhat.com>,
        <kwankhede@nvidia.com>, <wanghaibin.wang@huawei.com>,
        Zenghui Yu <yuzenghui@huawei.com>
Subject: [PATCH] vfio: Fix typo of the device_state
Date: Thu, 10 Sep 2020 20:25:08 +0800
Message-ID: <20200910122508.705-1-yuzenghui@huawei.com>
X-Mailer: git-send-email 2.23.0.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.185.226]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

A typo fix ("_RUNNNG" => "_RUNNING") in comment block of the uapi header.

Signed-off-by: Zenghui Yu <yuzenghui@huawei.com>
---
 include/uapi/linux/vfio.h | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v5 1/3] PCI/IOV: Mark VFs as not implementing PCI_COMMAND_MEMORY
##### From: Matthew Rosato <mjrosato@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Matthew Rosato <mjrosato@linux.ibm.com>
X-Patchwork-Id: 11769065
Return-Path: <SRS0=BU+x=CT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 757F859D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Sep 2020 20:10:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 511B1221E5
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Sep 2020 20:10:25 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="tAiMT4Wz"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726293AbgIJUKX (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 10 Sep 2020 16:10:23 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:50270 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1730854AbgIJPAR (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 10 Sep 2020 11:00:17 -0400
Received: from pps.filterd (m0098396.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 08AEj6vj187669;
        Thu, 10 Sep 2020 11:00:08 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references; s=pp1;
 bh=+OUmHMAzekDWnfUWHy+QvXx0etSZ8Wq/8Ekd3eDbQ+M=;
 b=tAiMT4WzrMUI13Hc4ew/XyEGMJCdvtYvfWWT1oVWREzC+2BXsqPo/bfkJktX0QngcePF
 svtBxfmofu8nZYK9KwxkHtT6jJ4KMwNdL51+aq7xsYNwJGxOtpyrA5s5YRF4pAnYyYBD
 XDa05luz0NuHFN979/r3CH1lxhGLOGolmr/P9f9NGLn7zu1J/qhTNMoKSNeCv6fELhto
 aeRCDEx70fvrmA6oTT9p+DzztoQvrXJZflkGf1/2wIfa7Leaho6nEj14VFQd7el4qeCx
 jmYHHnRFSpxyUP2ZGpUVvGGAs9o66Xh76moXSxxNH6D/7DO6yKR9CcN1/AvNYbxbnZBH yw==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 33fp698ex9-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 10 Sep 2020 11:00:08 -0400
Received: from m0098396.ppops.net (m0098396.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 08AEk6Sb190560;
        Thu, 10 Sep 2020 11:00:07 -0400
Received: from ppma02dal.us.ibm.com (a.bd.3ea9.ip4.static.sl-reverse.com
 [169.62.189.10])
        by mx0a-001b2d01.pphosted.com with ESMTP id 33fp698eve-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 10 Sep 2020 11:00:07 -0400
Received: from pps.filterd (ppma02dal.us.ibm.com [127.0.0.1])
        by ppma02dal.us.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 08AEqW13018133;
        Thu, 10 Sep 2020 15:00:06 GMT
Received: from b03cxnp07029.gho.boulder.ibm.com
 (b03cxnp07029.gho.boulder.ibm.com [9.17.130.16])
        by ppma02dal.us.ibm.com with ESMTP id 33c2a9t8g5-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 10 Sep 2020 15:00:05 +0000
Received: from b03ledav004.gho.boulder.ibm.com
 (b03ledav004.gho.boulder.ibm.com [9.17.130.235])
        by b03cxnp07029.gho.boulder.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 08AF04Rb53346702
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 10 Sep 2020 15:00:04 GMT
Received: from b03ledav004.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 362EC78069;
        Thu, 10 Sep 2020 15:00:04 +0000 (GMT)
Received: from b03ledav004.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id BC0167807B;
        Thu, 10 Sep 2020 15:00:02 +0000 (GMT)
Received: from oc4221205838.ibm.com (unknown [9.211.91.207])
        by b03ledav004.gho.boulder.ibm.com (Postfix) with ESMTP;
        Thu, 10 Sep 2020 15:00:02 +0000 (GMT)
From: Matthew Rosato <mjrosato@linux.ibm.com>
To: alex.williamson@redhat.com, bhelgaas@google.com
Cc: schnelle@linux.ibm.com, pmorel@linux.ibm.com, mpe@ellerman.id.au,
        oohall@gmail.com, cohuck@redhat.com, kevin.tian@intel.com,
        hca@linux.ibm.com, gor@linux.ibm.com, borntraeger@de.ibm.com,
        linux-s390@vger.kernel.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, linux-pci@vger.kernel.org
Subject: [PATCH v5 1/3] PCI/IOV: Mark VFs as not implementing
 PCI_COMMAND_MEMORY
Date: Thu, 10 Sep 2020 10:59:55 -0400
Message-Id: <1599749997-30489-2-git-send-email-mjrosato@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1599749997-30489-1-git-send-email-mjrosato@linux.ibm.com>
References: <1599749997-30489-1-git-send-email-mjrosato@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-09-10_03:2020-09-10,2020-09-10 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 adultscore=0
 priorityscore=1501 clxscore=1015 phishscore=0 mlxscore=0 bulkscore=0
 lowpriorityscore=0 spamscore=0 suspectscore=0 mlxlogscore=879
 impostorscore=0 malwarescore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-2006250000 definitions=main-2009100130
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

For VFs, the Memory Space Enable bit in the Command Register is
hard-wired to 0.

Add a new bit to signify devices where the Command Register Memory
Space Enable bit does not control the device's response to MMIO
accesses.

Signed-off-by: Matthew Rosato <mjrosato@linux.ibm.com>
---
 drivers/pci/iov.c   | 1 +
 include/linux/pci.h | 1 +
 2 files changed, 2 insertions(+)

```
