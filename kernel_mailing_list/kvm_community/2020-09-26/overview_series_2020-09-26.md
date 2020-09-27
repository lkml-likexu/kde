#### [PATCH] x86/hyperv: Remove aliases with X64 in their name
##### From: Joseph Salisbury <jsalisbury@linux.microsoft.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Joseph Salisbury <jsalisbury@linux.microsoft.com>
X-Patchwork-Id: 11801503
Return-Path: <SRS0=bF+2=DD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 14E196CA
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 26 Sep 2020 14:26:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DD5EA20BED
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 26 Sep 2020 14:26:45 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=linux.microsoft.com
 header.i=@linux.microsoft.com header.b="kri/E4EY"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729093AbgIZO0e (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 26 Sep 2020 10:26:34 -0400
Received: from linux.microsoft.com ([13.77.154.182]:43092 "EHLO
        linux.microsoft.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725208AbgIZO0e (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 26 Sep 2020 10:26:34 -0400
Received: from
 linuxonhyperv3.guj3yctzbm1etfxqx2vob5hsef.xx.internal.cloudapp.net
 (linux.microsoft.com [13.77.154.182])
        by linux.microsoft.com (Postfix) with ESMTPSA id 347CC20B7178;
        Sat, 26 Sep 2020 07:26:32 -0700 (PDT)
DKIM-Filter: OpenDKIM Filter v2.11.0 linux.microsoft.com 347CC20B7178
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=linux.microsoft.com;
        s=default; t=1601130392;
        bh=/Ho0fecMukZFT9gjtpJSysWsHe+ug17qsYo3c7Eyiho=;
        h=From:To:Cc:Subject:Date:Reply-To:From;
        b=kri/E4EYtmmQeK++SIJoElmKjdhVpEg30Ru+vHH+1Vj8hs6CbemJUzh+vXFcDBrIB
         XHD48wses7C0B6RzWtDDwn2zad6PK4KBBppvGZpXeNd0/bc7m/Nwjy+iQt8UmY+C80
         c+9cQvdueVV9xF/Qghn+vDN11lp2g2HRlQMB4yjo=
From: Joseph Salisbury <jsalisbury@linux.microsoft.com>
To: kys@microsoft.com, haiyangz@microsoft.com, sthemmin@microsoft.com,
        wei.liu@kernel.org, tglx@linutronix.de, mingo@redhat.com,
        bp@alien8.de, hpa@zytor.com, mikelley@microsoft.com,
        pbonzini@redhat.com, sean.j.christopherson@intel.com,
        vkuznets@redhat.com, wanpengli@tencent.com, jmattson@google.com,
        joro@8bytes.org
Cc: x86@kernel.org, linux-hyperv@vger.kernel.org,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [PATCH] x86/hyperv: Remove aliases with X64 in their name
Date: Sat, 26 Sep 2020 07:26:26 -0700
Message-Id: <1601130386-11111-1-git-send-email-jsalisbury@linux.microsoft.com>
X-Mailer: git-send-email 1.8.3.1
Reply-To: joseph.salisbury@microsoft.com
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Joseph Salisbury <joseph.salisbury@microsoft.com>

In the architecture independent version of hyperv-tlfs.h, commit c55a844f46f958b
removed the "X64" in the symbol names so they would make sense for both x86 and
ARM64.  That commit added aliases with the "X64" in the x86 version of hyperv-tlfs.h 
so that existing x86 code would continue to compile.

As a cleanup, update the x86 code to use the symbols without the "X64", then remove 
the aliases.  There's no functional change.

Signed-off-by: Joseph Salisbury <joseph.salisbury@microsoft.com>
---
 arch/x86/hyperv/hv_init.c          |  8 ++++----
 arch/x86/hyperv/hv_spinlock.c      |  2 +-
 arch/x86/include/asm/hyperv-tlfs.h | 33 ------------------------------
 arch/x86/kernel/cpu/mshyperv.c     |  8 ++++----
 arch/x86/kvm/hyperv.c              | 20 +++++++++---------
 5 files changed, 19 insertions(+), 52 deletions(-)

```
