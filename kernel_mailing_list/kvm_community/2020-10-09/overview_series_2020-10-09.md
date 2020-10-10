#### [PATCH v2 1/8] x86/apic: Fix x2apic enablement without interrupt remapping
##### From: David Woodhouse <dwmw2@infradead.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Woodhouse <dwmw2@infradead.org>
X-Patchwork-Id: 11825569
Return-Path: <SRS0=Illt=DQ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D745A6CA
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  9 Oct 2020 10:46:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AD6F6222C8
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  9 Oct 2020 10:46:29 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=infradead.org header.i=@infradead.org
 header.b="cQC3Sh+2"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2387815AbgJIKq3 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 9 Oct 2020 06:46:29 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:47014 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2387787AbgJIKq0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 9 Oct 2020 06:46:26 -0400
Received: from merlin.infradead.org (merlin.infradead.org
 [IPv6:2001:8b0:10b:1231::1])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 31665C0613D9;
        Fri,  9 Oct 2020 03:46:26 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; q=dns/txt; c=relaxed/relaxed;
        d=infradead.org; s=merlin.20170209;
 h=Sender:Content-Transfer-Encoding:
        MIME-Version:References:In-Reply-To:Message-Id:Date:Subject:Cc:To:From:
        Reply-To:Content-Type:Content-ID:Content-Description;
        bh=CsaHshU52iFBF6irbPkHUNEv7y5J4Xj0UjALSbLyJyI=;
 b=cQC3Sh+2XWLLTkMC7OJJgsl7li
        a7twtM3yjvC6QruFzDuG8X9D3e7DM7Gh0+f+yZP1s8OyQSarZBHxk7zG6701WCYZD47DIWAgbz1uG
        mU+5OAWNyLTlJDbQeL+ub5H6IMVa42pFWho2raiy5M1idEC9HTyDzkD34kSz4/klBGQW1p/GzKimz
        jKykXI4gBhxC/Zxn7ChRnz/d913FTfIMg8s29h/1Ii5ZcM8yrQsttQNsb3OVS4dXWIr9zmHQqXp4p
        NfrdWPVmvMW1zG9TRqBYgu4cGNHgUJzpTDDwPo3wOR4mKRutuKYHDW8zUXbcoF/+4aJU4xkLcbJx7
        ZBOeMUGQ==;
Received: from i7.infradead.org ([2001:8b0:10b:1:21e:67ff:fecb:7a92])
        by merlin.infradead.org with esmtpsa (Exim 4.92.3 #3 (Red Hat Linux))
        id 1kQpuq-00050T-1Y; Fri, 09 Oct 2020 10:46:24 +0000
Received: from dwoodhou by i7.infradead.org with local (Exim 4.93 #3 (Red Hat
 Linux))
        id 1kQpup-005W3u-17; Fri, 09 Oct 2020 11:46:23 +0100
From: David Woodhouse <dwmw2@infradead.org>
To: x86@kernel.org
Cc: kvm <kvm@vger.kernel.org>, Thomas Gleixner <tglx@linutronix.de>,
        Paolo Bonzini <pbonzini@redhat.com>,
        linux-kernel <linux-kernel@vger.kernel.org>,
        linux-hyperv@vger.kernel.org
Subject: [PATCH v2 1/8] x86/apic: Fix x2apic enablement without interrupt
 remapping
Date: Fri,  9 Oct 2020 11:46:09 +0100
Message-Id: <20201009104616.1314746-2-dwmw2@infradead.org>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20201009104616.1314746-1-dwmw2@infradead.org>
References: <803bb6b2212e65c568c84ff6882c2aa8a0ee03d5.camel@infradead.org>
 <20201009104616.1314746-1-dwmw2@infradead.org>
MIME-Version: 1.0
Sender: David Woodhouse <dwmw2@infradead.org>
X-SRS-Rewrite: SMTP reverse-path rewritten from <dwmw2@infradead.org> by
 merlin.infradead.org. See http://www.infradead.org/rpr.html
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: David Woodhouse <dwmw@amazon.co.uk>

Currently, Linux as a hypervisor guest will enable x2apic only if there
are no CPUs present at boot time with an APIC ID above 255.

Hotplugging a CPU later with a higher APIC ID would result in a CPU
which cannot be targeted by external interrupts.

Add a filter in x2apic_apic_id_valid() which can be used to prevent
such CPUs from coming online, and allow x2apic to be enabled even if
they are present at boot time.

Fixes: ce69a784504 ("x86/apic: Enable x2APIC without interrupt remapping under KVM")
Signed-off-by: David Woodhouse <dwmw@amazon.co.uk>
---
 arch/x86/include/asm/apic.h        |  1 +
 arch/x86/kernel/apic/apic.c        | 14 ++++++++------
 arch/x86/kernel/apic/x2apic_phys.c |  9 +++++++++
 3 files changed, 18 insertions(+), 6 deletions(-)

```
#### [PATCH v2 01/17] drm/exynos: Stop using frame_vector helpers
##### From: Daniel Vetter <daniel.vetter@ffwll.ch>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Daniel Vetter <daniel.vetter@ffwll.ch>
X-Patchwork-Id: 11825343
Return-Path: <SRS0=Illt=DQ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D2D8F109B
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  9 Oct 2020 08:02:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AC43922227
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  9 Oct 2020 08:02:32 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=ffwll.ch header.i=@ffwll.ch
 header.b="SWhf00Td"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732951AbgJIICb (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 9 Oct 2020 04:02:31 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:49464 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1732657AbgJIH7z (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 9 Oct 2020 03:59:55 -0400
Received: from mail-wm1-x341.google.com (mail-wm1-x341.google.com
 [IPv6:2a00:1450:4864:20::341])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 9290BC0613D9
        for <kvm@vger.kernel.org>; Fri,  9 Oct 2020 00:59:54 -0700 (PDT)
Received: by mail-wm1-x341.google.com with SMTP id z22so8390346wmi.0
        for <kvm@vger.kernel.org>; Fri, 09 Oct 2020 00:59:54 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=ffwll.ch; s=google;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=HSRfALuX/IouQZitVihZxXHTCU7Rm5wzYoVT9RXb0bQ=;
        b=SWhf00TdPqOP8156zohQQyTtmDuNxJfK0W9fnCMqmPLciyxtuo7vcgbtxhhN5oO6gi
         /6m4diCL1wJuHJBYEV+zQ5FwryH8vdV7pMGhKi+N5RvkmTH/Ih3JSyB/yzMFawpej0G/
         CJPIqXdiS0DRGKulzrlj/AGXS9SyLuM2tSsog=
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=HSRfALuX/IouQZitVihZxXHTCU7Rm5wzYoVT9RXb0bQ=;
        b=n75ZbBR/GZOS6bol/DJMEH1uO0M32/zcgdC69uCnXK0WWTA6Xz0hDgTxTz0jwsUQ4I
         GyZs72edCzHAjFdrSHdndmtcLyvxctjF2UMTPPBcExwK9a/2/q3RuKV49opm91mgFe7T
         /rGBclSIL+YHCQZAfsu8uXsWWTyAqM6aYDgrXAOwFn3s4BPTtN5yq3X9vmk63PV52MrI
         4qx0U7EOBst0yKokgLm9S8lb86fchpwj9PmB7PxsO73oXb+keVwFqDpzchbAO5m9nOI/
         /RF4MEsH/PWf4E5+e1+EQDGoAM2j8s+oaH1PGrnq/LEsVMpbzgFTykQcc/VbfahzThTy
         jDWw==
X-Gm-Message-State: AOAM530Ge4tRRzXPRHEc1OiHpcscn02HvruO/OdZ6ov7sNmRK5x5zx7B
        3MNpdZcUd9D39XDPJNH9ODzbTQ==
X-Google-Smtp-Source: 
 ABdhPJwUS14aPNDu6Fdjhifpy3cbOOhq8GIbHY08/ZuG5GVGU/mBRM7HMVv9afMyQGpP+uPyZkh2Vg==
X-Received: by 2002:a1c:791a:: with SMTP id l26mr267265wme.163.1602230393288;
        Fri, 09 Oct 2020 00:59:53 -0700 (PDT)
Received: from phenom.ffwll.local ([2a02:168:57f4:0:efd0:b9e5:5ae6:c2fa])
        by smtp.gmail.com with ESMTPSA id
 u17sm11634118wri.45.2020.10.09.00.59.51
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 09 Oct 2020 00:59:52 -0700 (PDT)
From: Daniel Vetter <daniel.vetter@ffwll.ch>
To: DRI Development <dri-devel@lists.freedesktop.org>,
        LKML <linux-kernel@vger.kernel.org>
Cc: kvm@vger.kernel.org, linux-mm@kvack.org,
 linux-arm-kernel@lists.infradead.org, linux-samsung-soc@vger.kernel.org,
 linux-media@vger.kernel.org, linux-s390@vger.kernel.org,
 Daniel Vetter <daniel.vetter@ffwll.ch>,
 Daniel Vetter <daniel.vetter@intel.com>, Jason Gunthorpe <jgg@ziepe.ca>,
 Inki Dae <inki.dae@samsung.com>, Joonyoung Shim <jy0922.shim@samsung.com>,
 Seung-Woo Kim <sw0312.kim@samsung.com>,
 Kyungmin Park <kyungmin.park@samsung.com>, Kukjin Kim <kgene@kernel.org>,
 Krzysztof Kozlowski <krzk@kernel.org>,
 Andrew Morton <akpm@linux-foundation.org>,
 John Hubbard <jhubbard@nvidia.com>,
 =?utf-8?b?SsOpcsO0bWUgR2xpc3Nl?= <jglisse@redhat.com>,
 Jan Kara <jack@suse.cz>, Dan Williams <dan.j.williams@intel.com>
Subject: [PATCH v2 01/17] drm/exynos: Stop using frame_vector helpers
Date: Fri,  9 Oct 2020 09:59:18 +0200
Message-Id: <20201009075934.3509076-2-daniel.vetter@ffwll.ch>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20201009075934.3509076-1-daniel.vetter@ffwll.ch>
References: <20201009075934.3509076-1-daniel.vetter@ffwll.ch>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

All we need are a pages array, pin_user_pages_fast can give us that
directly. Plus this avoids the entire raw pfn side of get_vaddr_frames.

Signed-off-by: Daniel Vetter <daniel.vetter@intel.com>
Cc: Jason Gunthorpe <jgg@ziepe.ca>
Cc: Inki Dae <inki.dae@samsung.com>
Cc: Joonyoung Shim <jy0922.shim@samsung.com>
Cc: Seung-Woo Kim <sw0312.kim@samsung.com>
Cc: Kyungmin Park <kyungmin.park@samsung.com>
Cc: Kukjin Kim <kgene@kernel.org>
Cc: Krzysztof Kozlowski <krzk@kernel.org>
Cc: Andrew Morton <akpm@linux-foundation.org>
Cc: John Hubbard <jhubbard@nvidia.com>
Cc: Jérôme Glisse <jglisse@redhat.com>
Cc: Jan Kara <jack@suse.cz>
Cc: Dan Williams <dan.j.williams@intel.com>
Cc: linux-mm@kvack.org
Cc: linux-arm-kernel@lists.infradead.org
Cc: linux-samsung-soc@vger.kernel.org
Cc: linux-media@vger.kernel.org
---
v2: Use unpin_user_pages_dirty_lock (John)
---
 drivers/gpu/drm/exynos/Kconfig          |  1 -
 drivers/gpu/drm/exynos/exynos_drm_g2d.c | 47 +++++++++++--------------
 2 files changed, 20 insertions(+), 28 deletions(-)

```
#### [PATCH RFC PKS/PMEM 01/58] x86/pks: Add a global pkrs option
##### From: ira.weiny@intel.com

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ira Weiny <ira.weiny@intel.com>
X-Patchwork-Id: 11829515
Return-Path: <SRS0=Illt=DQ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 76E44109B
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  9 Oct 2020 20:10:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5118C20659
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  9 Oct 2020 20:10:35 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2403828AbgJITvF (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 9 Oct 2020 15:51:05 -0400
Received: from mga05.intel.com ([192.55.52.43]:56235 "EHLO mga05.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2390840AbgJITuu (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 9 Oct 2020 15:50:50 -0400
IronPort-SDR: 
 w1qCiG3AJrbHpSZTfimcXSJzO/yJWuRyVF4QWgalq7actQXgPvgRXk29wA5KGD6UbigUjAM3yo
 dw4QNiCtCnjg==
X-IronPort-AV: E=McAfee;i="6000,8403,9769"; a="250225864"
X-IronPort-AV: E=Sophos;i="5.77,355,1596524400";
   d="scan'208";a="250225864"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by fmsmga105.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 09 Oct 2020 12:50:46 -0700
IronPort-SDR: 
 qnBWOjzlCrAn0iz4juA1IxPDmIdlUS8zYMFKRiVxpP3UruuZtN+Up+nA/7WPjpw84o9yPhVhmH
 jUXVTF6t7/+g==
X-IronPort-AV: E=Sophos;i="5.77,355,1596524400";
   d="scan'208";a="298530884"
Received: from iweiny-desk2.sc.intel.com (HELO localhost) ([10.3.52.147])
  by fmsmga008-auth.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 09 Oct 2020 12:50:46 -0700
From: ira.weiny@intel.com
To: Andrew Morton <akpm@linux-foundation.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        Andy Lutomirski <luto@kernel.org>,
        Peter Zijlstra <peterz@infradead.org>
Cc: Ira Weiny <ira.weiny@intel.com>, x86@kernel.org,
        Dave Hansen <dave.hansen@linux.intel.com>,
        Dan Williams <dan.j.williams@intel.com>,
        Fenghua Yu <fenghua.yu@intel.com>, linux-doc@vger.kernel.org,
        linux-kernel@vger.kernel.org, linux-nvdimm@lists.01.org,
        linux-fsdevel@vger.kernel.org, linux-mm@kvack.org,
        linux-kselftest@vger.kernel.org, linuxppc-dev@lists.ozlabs.org,
        kvm@vger.kernel.org, netdev@vger.kernel.org, bpf@vger.kernel.org,
        kexec@lists.infradead.org, linux-bcache@vger.kernel.org,
        linux-mtd@lists.infradead.org, devel@driverdev.osuosl.org,
        linux-efi@vger.kernel.org, linux-mmc@vger.kernel.org,
        linux-scsi@vger.kernel.org, target-devel@vger.kernel.org,
        linux-nfs@vger.kernel.org, ceph-devel@vger.kernel.org,
        linux-ext4@vger.kernel.org, linux-aio@kvack.org,
        io-uring@vger.kernel.org, linux-erofs@lists.ozlabs.org,
        linux-um@lists.infradead.org, linux-ntfs-dev@lists.sourceforge.net,
        reiserfs-devel@vger.kernel.org,
        linux-f2fs-devel@lists.sourceforge.net,
        linux-nilfs@vger.kernel.org, cluster-devel@redhat.com,
        ecryptfs@vger.kernel.org, linux-cifs@vger.kernel.org,
        linux-btrfs@vger.kernel.org, linux-afs@lists.infradead.org,
        linux-rdma@vger.kernel.org, amd-gfx@lists.freedesktop.org,
        dri-devel@lists.freedesktop.org, intel-gfx@lists.freedesktop.org,
        drbd-dev@lists.linbit.com, linux-block@vger.kernel.org,
        xen-devel@lists.xenproject.org, linux-cachefs@redhat.com,
        samba-technical@lists.samba.org, intel-wired-lan@lists.osuosl.org
Subject: [PATCH RFC PKS/PMEM 01/58] x86/pks: Add a global pkrs option
Date: Fri,  9 Oct 2020 12:49:36 -0700
Message-Id: <20201009195033.3208459-2-ira.weiny@intel.com>
X-Mailer: git-send-email 2.28.0.rc0.12.gb6a658bd00c9
In-Reply-To: <20201009195033.3208459-1-ira.weiny@intel.com>
References: <20201009195033.3208459-1-ira.weiny@intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Ira Weiny <ira.weiny@intel.com>

Some users, such as kmap(), sometimes requires PKS to be global.
However, updating all CPUs, and worse yet all threads is expensive.

Introduce a global PKRS state which is checked at critical times to
allow the state to enable access when global PKS is required.  To
accomplish this with minimal locking; the code is carefully designed
with the following key concepts.

1) Borrow the idea of lazy TLB invalidations from the fault handler
   code.  When enabling PKS access we anticipate that other threads are
   not yet running.  However, if they are we catch the fault and clean
   up the MSR value.

2) When disabling PKS access we force all MSR values across all CPU's.
   This is required to block access as soon as possible.[1]  However, it
   is key that we never attempt to update the per-task PKS values
   directly.  See next point.

3) Per-task PKS values never get updated with global PKS values.  This
   is key to prevent locking requirements and a nearly intractable
   problem of trying to update every task in the system.  Here are a few
   key points.

   3a) The MSR value can be updated with the global PKS value if that
   global value happened to change while the task was running.

   3b) If the task was sleeping while the global PKS was updated then
   the global value is added in when task's are scheduled.

   3c) If the global PKS value restricts access the MSR is updated as
   soon as possible[1] and the thread value is not updated which ensures
   the thread does not retain the elevated privileges after a context
   switch.

4) Follow on patches must be careful to preserve the separation of the
   thread PKRS value and the MSR value.

5) Access Disable on any individual pkey is turned into (Access Disable
   | Write Disable) to facilitate faster integration of the global value
   into the thread local MSR through a simple '&' operation.  Doing
   otherwise would result in complicated individual bit manipulation for
   each pkey.

[1] There is a race condition which is ignored which is required for
performance issues.  This potentially allows access to a thread until
the end of it's time slice.  After the context switch the global value
will be restored.

Signed-off-by: Ira Weiny <ira.weiny@intel.com>
---
 Documentation/core-api/protection-keys.rst |  11 +-
 arch/x86/entry/common.c                    |   7 +
 arch/x86/include/asm/pkeys.h               |   6 +-
 arch/x86/include/asm/pkeys_common.h        |   8 +-
 arch/x86/kernel/process.c                  |  74 +++++++-
 arch/x86/mm/fault.c                        | 189 ++++++++++++++++-----
 arch/x86/mm/pkeys.c                        |  88 ++++++++--
 include/linux/pkeys.h                      |   6 +-
 lib/pks/pks_test.c                         |  16 +-
 9 files changed, 329 insertions(+), 76 deletions(-)

```
#### [PATCH v2 1/4] selftests: kvm: Fix the segment descriptor layout to match the actual layout
##### From: Aaron Lewis <aaronlewis@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Aaron Lewis <aaronlewis@google.com>
X-Patchwork-Id: 11825625
Return-Path: <SRS0=Illt=DQ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 12CDB139F
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  9 Oct 2020 11:46:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E97E02226B
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  9 Oct 2020 11:46:24 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="du7otss2"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388155AbgJILqY (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 9 Oct 2020 07:46:24 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:56310 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1732494AbgJILqX (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 9 Oct 2020 07:46:23 -0400
Received: from mail-pf1-x449.google.com (mail-pf1-x449.google.com
 [IPv6:2607:f8b0:4864:20::449])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id A4C87C0613D2
        for <kvm@vger.kernel.org>; Fri,  9 Oct 2020 04:46:23 -0700 (PDT)
Received: by mail-pf1-x449.google.com with SMTP id a27so6390463pfl.17
        for <kvm@vger.kernel.org>; Fri, 09 Oct 2020 04:46:23 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:in-reply-to:message-id:mime-version:references:subject
         :from:to:cc;
        bh=kRLElTJYruy9BhLgGAtIqt00VI4hnTdleImYdQGJD0s=;
        b=du7otss2wXKpS/7PKEpioxcBYamyBReTtg2Op7e06jD60aZoCOGs944MtwO9JPHPjR
         J5k0e8Q0a1GMcP4vSNAgOhbtQM4mdbFYP7cXoDukMcHL84jhbiOwiaDhPlTlaiSqt2CI
         NRkQSsoh5gSzk/vqn2AJr5UhrUtznvVabo9PD6FELuyaOas35dRAmD2z7ereyeaTRGaH
         xvCnKuSHGKuHxRWXngp4JDk5Tu03yakfpkBDZdmSs3esxMnztUNcszXYcb/PpQ1tm1Yz
         kD6Xkbi2TgcAkyeqi95fWDHbglK6q2CSUPLdQbeut9MsEjLt47VHMcS65+BQOMQipiSh
         rrwA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=kRLElTJYruy9BhLgGAtIqt00VI4hnTdleImYdQGJD0s=;
        b=dB43PfdVKCYtjtzR+iJiZJKHN4f6LtC2ZRlq501+0o17zEQHy4NkKFAprCdFk4JwTO
         IYKc74/CZhFi+a9CSNCRxQsI7o9RdO9ag9+iXKHj4sBNe/Pj1XOjZEpk64klTJ+M7L9h
         /I7v/CPVzmqRiLx4duGWD3UUJw/lmr67nePVkaFcbMrMdrQGu/EpHfCi7PVmLTo2HdW1
         LmnWv7UzkiJ4i7p8wa3W1n1j3cQx+Zy1T/Pl0l5DpkVTgZahiKODc9Zd8X7RM1Wwk/Dl
         v/Hz0SADXKNQ3rZ/gyRcz6r5p+I/bk7txTN3fBMgcawXAq9KQFD2ZqR/lOT0eeXQNKXN
         At1g==
X-Gm-Message-State: AOAM532D21+yGlJ5ieKHhtHYaa5+fwV67+9AsFWa8ztCltobajx43tFy
        biNoJYjACXSj02h+5bb5RdEUix3L5WBhVXbV
X-Google-Smtp-Source: 
 ABdhPJyvDSmJ08rWSvKSiSZlSUN/Wh/9YHFKNYSXEhXVMS/pzrKVbgxIyCans2IGhVLHnbgAyVMnZI71RowkvT30
Sender: "aaronlewis via sendgmr" <aaronlewis@aaronlewis1.sea.corp.google.com>
X-Received: from aaronlewis1.sea.corp.google.com
 ([2620:15c:100:202:a28c:fdff:fed8:8d46])
 (user=aaronlewis job=sendgmr) by 2002:aa7:8d15:0:b029:142:2501:39fe with SMTP
 id j21-20020aa78d150000b0290142250139femr11821949pfe.77.1602243983040; Fri,
 09 Oct 2020 04:46:23 -0700 (PDT)
Date: Fri,  9 Oct 2020 04:46:12 -0700
In-Reply-To: <20201009114615.2187411-1-aaronlewis@google.com>
Message-Id: <20201009114615.2187411-2-aaronlewis@google.com>
Mime-Version: 1.0
References: <20201009114615.2187411-1-aaronlewis@google.com>
X-Mailer: git-send-email 2.28.0.1011.ga647a8990f-goog
Subject: [PATCH v2 1/4] selftests: kvm: Fix the segment descriptor layout to
 match the actual layout
From: Aaron Lewis <aaronlewis@google.com>
To: graf@amazon.com
Cc: pshier@google.com, jmattson@google.com, kvm@vger.kernel.org,
        Aaron Lewis <aaronlewis@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Fix the layout of 'struct desc64' to match the layout described in the
SDM Vol 3, Chapter 3 "Protected-Mode Memory Management", section 3.4.5
"Segment Descriptors", Figure 3-8 "Segment Descriptor".  The test added
later in this series relies on this and crashes if this layout is not
correct.

Signed-off-by: Aaron Lewis <aaronlewis@google.com>
Reviewed-by: Alexander Graf <graf@amazon.com>
---
 tools/testing/selftests/kvm/include/x86_64/processor.h | 2 +-
 tools/testing/selftests/kvm/lib/x86_64/processor.c     | 3 ++-
 2 files changed, 3 insertions(+), 2 deletions(-)

```
#### [tip: core/rcu] kvm: mmu: page_track: Fix RCU list API usageCc: Madhuparna Bhowmik <madhuparnabhowmik10@gmail.com>,
##### From: "tip-bot2 for Madhuparna Bhowmik" <tip-bot2@linutronix.de>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: tip-bot2 for Thomas Gleixner <tip-bot2@linutronix.de>
X-Patchwork-Id: 11824981
Return-Path: <SRS0=Illt=DQ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DC30015E6
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  9 Oct 2020 06:37:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B25A1206CA
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  9 Oct 2020 06:37:21 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=linutronix.de header.i=@linutronix.de
 header.b="G+CP1sIA";
	dkim=permerror (0-bit key) header.d=linutronix.de header.i=@linutronix.de
 header.b="vz4ghSJp"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731021AbgJIGhK (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 9 Oct 2020 02:37:10 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:36468 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1732030AbgJIGfj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 9 Oct 2020 02:35:39 -0400
Received: from galois.linutronix.de (Galois.linutronix.de
 [IPv6:2a0a:51c0:0:12e:550::1])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id D8CE8C0613D4;
        Thu,  8 Oct 2020 23:35:38 -0700 (PDT)
Date: Fri, 09 Oct 2020 06:35:36 -0000
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=linutronix.de;
        s=2020; t=1602225337;
        h=from:from:sender:sender:reply-to:reply-to:subject:subject:date:date:
         message-id:message-id:to:to:cc:cc:mime-version:mime-version:
         content-type:content-type:
  content-transfer-encoding:content-transfer-encoding;
        bh=oUDb2HwG8cuVizWUDjf89gYYGCboHOSex7ly9vGcN4A=;
        b=G+CP1sIAMbOQ0ASZ6pNjOh+NoDmz1xAT621kduUcAB0Fv4o+qHpwAAxR7jSExU5ofA7xrK
        sAmZHnI/Ui6HG07SL+3PHMy1wdbdiUDbN0v7h5Xc2E0f0q/eg6+/zHWhB8XKqY0F50tQh3
        CN5NMyF1XlclE7Ek/w2s4aEJDOTuECEl9vIqfw+CsrVYZVAJP9V8Nw0OaZHGnpzF/pj8mq
        Y51kPyAdmY2+jaOMXXUmY5Xrn95jGHRhEn3YXkAzl7cM1KFKwsAcyCWee0yku/RnQY/bac
        BDKNERaJb4itqKg0cerkoPmboArP+Tp826Rg/8CD0l7/AxFT7RLxiAUNYPxjhQ==
DKIM-Signature: v=1; a=ed25519-sha256; c=relaxed/relaxed; d=linutronix.de;
        s=2020e; t=1602225337;
        h=from:from:sender:sender:reply-to:reply-to:subject:subject:date:date:
         message-id:message-id:to:to:cc:cc:mime-version:mime-version:
         content-type:content-type:
  content-transfer-encoding:content-transfer-encoding;
        bh=oUDb2HwG8cuVizWUDjf89gYYGCboHOSex7ly9vGcN4A=;
        b=vz4ghSJps1vPvwlbaKzJQbJfeX7f7C20CAyLQ5qtnS6tasXBM4uQNigvjU2n7nz7nAyrcX
        9lUfLNOmsuDqfxDw==
From: "tip-bot2 for Madhuparna Bhowmik" <tip-bot2@linutronix.de>
Sender: tip-bot2@linutronix.de
Reply-to: linux-kernel@vger.kernel.org
To: linux-tip-commits@vger.kernel.org
Subject: [tip: core/rcu] kvm: mmu: page_track: Fix RCU list API usage
Cc: Madhuparna Bhowmik <madhuparnabhowmik10@gmail.com>,
        "Paul E. McKenney" <paulmck@kernel.org>,
        Paolo Bonzini <pbonzini@redhat.com>, <kvm@vger.kernel.org>,
        x86 <x86@kernel.org>, LKML <linux-kernel@vger.kernel.org>
MIME-Version: 1.0
Message-ID: <160222533671.7002.15652338637485531444.tip-bot2@tip-bot2>
Robot-ID: <tip-bot2.linutronix.de>
Robot-Unsubscribe: Contact <mailto:tglx@linutronix.de> to get blacklisted from
 these emails
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The following commit has been merged into the core/rcu branch of tip:

Commit-ID:     df9a30fd1f70a757df193acd7396622eee23e527
Gitweb:        https://git.kernel.org/tip/df9a30fd1f70a757df193acd7396622eee23e527
Author:        Madhuparna Bhowmik <madhuparnabhowmik10@gmail.com>
AuthorDate:    Sun, 12 Jul 2020 18:40:03 +05:30
Committer:     Paul E. McKenney <paulmck@kernel.org>
CommitterDate: Mon, 24 Aug 2020 18:36:23 -07:00

kvm: mmu: page_track: Fix RCU list API usage

Use hlist_for_each_entry_srcu() instead of hlist_for_each_entry_rcu()
as it also checkes if the right lock is held.
Using hlist_for_each_entry_rcu() with a condition argument will not
report the cases where a SRCU protected list is traversed using
rcu_read_lock(). Hence, use hlist_for_each_entry_srcu().

Signed-off-by: Madhuparna Bhowmik <madhuparnabhowmik10@gmail.com>
Signed-off-by: Paul E. McKenney <paulmck@kernel.org>
Acked-by: Paolo Bonzini <pbonzini@redhat.com>
Cc: <kvm@vger.kernel.org>
---
 arch/x86/kvm/mmu/page_track.c | 6 ++++--
 1 file changed, 4 insertions(+), 2 deletions(-)

```
#### [PATCH v2] KVM: x86: Add tracepoint for dr_write/dr_read
##### From: lihaiwei.kernel@gmail.com

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Haiwei Li <lihaiwei.kernel@gmail.com>
X-Patchwork-Id: 11824891
Return-Path: <SRS0=Illt=DQ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A0D0D109B
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  9 Oct 2020 03:21:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8330122248
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  9 Oct 2020 03:21:46 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="FmR7r7Wu"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731484AbgJIDVj (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 8 Oct 2020 23:21:39 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:34898 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729593AbgJIDVj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 8 Oct 2020 23:21:39 -0400
Received: from mail-pf1-x441.google.com (mail-pf1-x441.google.com
 [IPv6:2607:f8b0:4864:20::441])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 38603C0613D2;
        Thu,  8 Oct 2020 20:21:39 -0700 (PDT)
Received: by mail-pf1-x441.google.com with SMTP id 144so5676230pfb.4;
        Thu, 08 Oct 2020 20:21:39 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=0n2V4MNRGwK1cK7V9UjFbAKsyNZxYNY7DcB/CQ3zBuc=;
        b=FmR7r7WuUzf6gUGF6OFjv2dQL5leGw/lgwp81U2pADktuMUVBLv7fwGXphDnnbvyzB
         QyOolcHzcRu4uPTA1p6DAvn/hTv/HX3v/XDXJmX/lGzsl8Mct2hd3NSIJyBgMLyNR/Lc
         mE+X8NR4Us1Zx7B3D4mzGR4x566SJ8XB422YLPkIQYLmlrPGtv1X/fQ5f4uJGrRxm/rV
         wZ/oiDyDEiaXaXCroTtEOzCqCXm8RPJNGYMIRXRN+pKFUMFeADBn4U23UzSsgFit/LIB
         kvULcnWtjB8frMWwi/58Bsnk3GX+LToNHhM2FV4LNRiNu2+vBpQ7MboDHh77LVhmKtwg
         wFKA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=0n2V4MNRGwK1cK7V9UjFbAKsyNZxYNY7DcB/CQ3zBuc=;
        b=XynTTp8kct97y735f6bPt4ohPcJXaLGlGHIJoU6iI3qlIsZGnqLISHSdzr5Q07gVYd
         apdPybabBWfRdWB/FV/zekfd5r3pQB/edHiIH6+edgwlYSDU2m9tIwyuiFZbAO0nUVpI
         52EWfBROgA9xsiV8KZ65/G1f+k5qYaMcxKQLllHody49LOex9XKydYQxXVruyIDuPCQu
         lUUzMqi12C2Xic8AhYPjA0TtK6RZn1tcpp6X4K2tC5BP5E9qj8eYzGMGU+Q/xM+L+J8Y
         z9CLxKV8L2H/lD9B7QhMYX0ebB+1robDt9Lqo72B9IDin4BoRJ650vMc7q/y1xYRgCFB
         HGzg==
X-Gm-Message-State: AOAM531nNfo3V3TDIQuW6L17eARUKa3X7REBx8JKx3ZVlQCibRAImKjJ
        TjwPuxJ1XVLqrzTQoNciCnL2uzR8udPB
X-Google-Smtp-Source: 
 ABdhPJxzqbUV/5/fLWGXY727cgDJb+dYic2DCum+KeYwdQN1029d1bqNe6L0CaPXNlAY0CvZLda1AA==
X-Received: by 2002:a17:90a:248:: with SMTP id
 t8mr2458390pje.64.1602213698403;
        Thu, 08 Oct 2020 20:21:38 -0700 (PDT)
Received: from localhost.localdomain ([203.205.141.39])
        by smtp.gmail.com with ESMTPSA id
 gl24sm378241pjb.50.2020.10.08.20.21.35
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Thu, 08 Oct 2020 20:21:37 -0700 (PDT)
From: lihaiwei.kernel@gmail.com
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: pbonzini@redhat.com, sean.j.christopherson@intel.com,
        vkuznets@redhat.com, wanpengli@tencent.com, jmattson@google.com,
        joro@8bytes.org, Haiwei Li <lihaiwei@tencent.com>
Subject: [PATCH v2] KVM: x86: Add tracepoint for dr_write/dr_read
Date: Fri,  9 Oct 2020 11:21:30 +0800
Message-Id: <20201009032130.6774-1-lihaiwei.kernel@gmail.com>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Haiwei Li <lihaiwei@tencent.com>

When vmexit occurs caused by accessing dr, there is no tracepoint to track
this action. Add tracepoint for this on x86 kvm.

Signed-off-by: Haiwei Li <lihaiwei@tencent.com>
---
v1 -> v2:
 * Improve the changelog 

 arch/x86/kvm/svm/svm.c |  2 ++
 arch/x86/kvm/trace.h   | 27 +++++++++++++++++++++++++++
 arch/x86/kvm/vmx/vmx.c | 10 ++++++++--
 arch/x86/kvm/x86.c     |  1 +
 4 files changed, 38 insertions(+), 2 deletions(-)

```
