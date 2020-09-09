#### [PATCH 1/3] fpga: dfl: add driver_override support
##### From: Xu Yilun <yilun.xu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xu Yilun <yilun.xu@intel.com>
X-Patchwork-Id: 11762659
Return-Path: <SRS0=SnLg=CR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6C08359D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  8 Sep 2020 07:18:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5773D218AC
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  8 Sep 2020 07:18:07 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729278AbgIHHSE (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 8 Sep 2020 03:18:04 -0400
Received: from mga09.intel.com ([134.134.136.24]:30573 "EHLO mga09.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729246AbgIHHSC (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 8 Sep 2020 03:18:02 -0400
IronPort-SDR: 
 RV9utV7ksloTlCOhj9ft8L0rDC/J2HXyziceEBZM6Jkxsu3HNdTJRoTXIrOi4SemC2O/cYYhzm
 xaQgmZxtwasA==
X-IronPort-AV: E=McAfee;i="6000,8403,9737"; a="159058737"
X-IronPort-AV: E=Sophos;i="5.76,404,1592895600";
   d="scan'208";a="159058737"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga004.jf.intel.com ([10.7.209.38])
  by orsmga102.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 08 Sep 2020 00:18:01 -0700
IronPort-SDR: 
 16kxSz8FcibQjPAMjNL4fMfj/Uu0qMWU1yqlgh+aBu3zVs17c5oJ3mqCj+w2OBdwPmPu9UnxmK
 aM6CJrdBkFIw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.76,404,1592895600";
   d="scan'208";a="448677709"
Received: from yilunxu-optiplex-7050.sh.intel.com ([10.239.159.141])
  by orsmga004.jf.intel.com with ESMTP; 08 Sep 2020 00:17:59 -0700
From: Xu Yilun <yilun.xu@intel.com>
To: mdf@kernel.org, alex.williamson@redhat.com, kwankhede@nvidia.com,
        linux-fpga@vger.kernel.org, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Cc: trix@redhat.com, lgoncalv@redhat.com, yilun.xu@intel.com
Subject: [PATCH 1/3] fpga: dfl: add driver_override support
Date: Tue,  8 Sep 2020 15:13:30 +0800
Message-Id: <1599549212-24253-2-git-send-email-yilun.xu@intel.com>
X-Mailer: git-send-email 2.7.4
In-Reply-To: <1599549212-24253-1-git-send-email-yilun.xu@intel.com>
References: <1599549212-24253-1-git-send-email-yilun.xu@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add support for overriding the default matching of a dfl device to a dfl
driver. It follows the same way that can be used for PCI and platform
devices. This patch adds the 'driver_override' sysfs file. It can be
used by VFIO to bind dfl devices for user accessing.

Signed-off-by: Xu Yilun <yilun.xu@intel.com>
---
 Documentation/ABI/testing/sysfs-bus-dfl | 20 ++++++++++++
 drivers/fpga/dfl.c                      | 54 ++++++++++++++++++++++++++++++++-
 include/linux/fpga/dfl-bus.h            |  2 ++
 3 files changed, 75 insertions(+), 1 deletion(-)

```
#### [PATCH v7.1 39/72] x86/sev-es: Setup early #VC handler
##### From: Joerg Roedel <joro@8bytes.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Joerg Roedel <joro@8bytes.org>
X-Patchwork-Id: 11763133
Return-Path: <SRS0=SnLg=CR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D2A47746
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  8 Sep 2020 10:22:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C525A206A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  8 Sep 2020 10:22:44 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729200AbgIHKWn (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 8 Sep 2020 06:22:43 -0400
Received: from 8bytes.org ([81.169.241.247]:43782 "EHLO theia.8bytes.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726801AbgIHKWl (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 8 Sep 2020 06:22:41 -0400
Received: by theia.8bytes.org (Postfix, from userid 1000)
        id A2E93344; Tue,  8 Sep 2020 12:22:39 +0200 (CEST)
Date: Tue, 8 Sep 2020 12:22:37 +0200
From: Joerg Roedel <joro@8bytes.org>
To: x86@kernel.org
Cc: Joerg Roedel <jroedel@suse.de>, hpa@zytor.com,
        Andy Lutomirski <luto@kernel.org>,
        Dave Hansen <dave.hansen@linux.intel.com>,
        Peter Zijlstra <peterz@infradead.org>,
        Jiri Slaby <jslaby@suse.cz>,
        Dan Williams <dan.j.williams@intel.com>,
        Tom Lendacky <thomas.lendacky@amd.com>,
        Juergen Gross <jgross@suse.com>,
        Kees Cook <keescook@chromium.org>,
        David Rientjes <rientjes@google.com>,
        Cfir Cohen <cfir@google.com>,
        Erdem Aktas <erdemaktas@google.com>,
        Masami Hiramatsu <mhiramat@kernel.org>,
        Mike Stunes <mstunes@vmware.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Martin Radev <martin.b.radev@gmail.com>,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org
Subject: [PATCH v7.1 39/72] x86/sev-es: Setup early #VC handler
Message-ID: <20200908102237.GA12638@8bytes.org>
References: <20200907131613.12703-1-joro@8bytes.org>
 <20200907131613.12703-40-joro@8bytes.org>
MIME-Version: 1.0
Content-Disposition: inline
In-Reply-To: <20200907131613.12703-40-joro@8bytes.org>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Joerg Roedel <jroedel@suse.de>

Setup an early handler for #VC exceptions. There is no GHCB mapped
yet, so just re-use the vc_no_ghcb_handler. It can only handle CPUID
exit-codes, but that should be enough to get the kernel through
verify_cpu() and __startup_64() until it runs on virtual addresses.

Signed-off-by: Joerg Roedel <jroedel@suse.de>
---
 arch/x86/include/asm/sev-es.h |  3 +++
 arch/x86/kernel/head64.c      | 21 +++++++++++++++++++++
 arch/x86/kernel/head_64.S     | 30 ++++++++++++++++++++++++++++++
 3 files changed, 54 insertions(+)

```
#### [PATCH v7.1 40/72] x86/sev-es: Setup GHCB based boot #VC handler
##### From: Joerg Roedel <joro@8bytes.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Joerg Roedel <joro@8bytes.org>
X-Patchwork-Id: 11763135
Return-Path: <SRS0=SnLg=CR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C2F44746
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  8 Sep 2020 10:24:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id ADC262078B
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  8 Sep 2020 10:24:31 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729037AbgIHKY3 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 8 Sep 2020 06:24:29 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:58866 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728876AbgIHKY0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 8 Sep 2020 06:24:26 -0400
Received: from theia.8bytes.org (8bytes.org
 [IPv6:2a01:238:4383:600:38bc:a715:4b6d:a889])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 38433C061573;
        Tue,  8 Sep 2020 03:24:24 -0700 (PDT)
Received: by theia.8bytes.org (Postfix, from userid 1000)
        id 328E0344; Tue,  8 Sep 2020 12:24:18 +0200 (CEST)
Date: Tue, 8 Sep 2020 12:24:16 +0200
From: Joerg Roedel <joro@8bytes.org>
To: x86@kernel.org
Cc: Joerg Roedel <jroedel@suse.de>, hpa@zytor.com,
        Andy Lutomirski <luto@kernel.org>,
        Dave Hansen <dave.hansen@linux.intel.com>,
        Peter Zijlstra <peterz@infradead.org>,
        Jiri Slaby <jslaby@suse.cz>,
        Dan Williams <dan.j.williams@intel.com>,
        Tom Lendacky <thomas.lendacky@amd.com>,
        Juergen Gross <jgross@suse.com>,
        Kees Cook <keescook@chromium.org>,
        David Rientjes <rientjes@google.com>,
        Cfir Cohen <cfir@google.com>,
        Erdem Aktas <erdemaktas@google.com>,
        Masami Hiramatsu <mhiramat@kernel.org>,
        Mike Stunes <mstunes@vmware.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Martin Radev <martin.b.radev@gmail.com>,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org
Subject: [PATCH v7.1 40/72] x86/sev-es: Setup GHCB based boot #VC handler
Message-ID: <20200908102416.GB12638@8bytes.org>
References: <20200907131613.12703-1-joro@8bytes.org>
 <20200907131613.12703-41-joro@8bytes.org>
MIME-Version: 1.0
Content-Disposition: inline
In-Reply-To: <20200907131613.12703-41-joro@8bytes.org>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Joerg Roedel <jroedel@suse.de>

Add the infrastructure to handle #VC exceptions when the kernel runs
on virtual addresses and has a GHCB mapped. This handler will be used
until the runtime #VC handler takes over.

Since the handler runs very early, disable instrumentation for sev-es.c.

Signed-off-by: Joerg Roedel <jroedel@suse.de>
---
 arch/x86/include/asm/realmode.h |   3 +
 arch/x86/include/asm/segment.h  |   2 +-
 arch/x86/include/asm/sev-es.h   |   2 +
 arch/x86/kernel/Makefile        |   2 +
 arch/x86/kernel/head64.c        |   8 +++
 arch/x86/kernel/head_64.S       |  36 ++++++++++
 arch/x86/kernel/sev-es-shared.c |  14 ++--
 arch/x86/kernel/sev-es.c        | 116 ++++++++++++++++++++++++++++++++
 arch/x86/mm/extable.c           |   1 +
 9 files changed, 176 insertions(+), 8 deletions(-)

```
#### [PATCH v7.2 39/74] x86/sev-es: Setup early #VC handler
##### From: Joerg Roedel <joro@8bytes.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Joerg Roedel <joro@8bytes.org>
X-Patchwork-Id: 11763605
Return-Path: <SRS0=SnLg=CR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 48496618
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  8 Sep 2020 16:42:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 39937207DE
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  8 Sep 2020 16:42:36 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732122AbgIHQmY (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 8 Sep 2020 12:42:24 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:33158 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1731514AbgIHQmS (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 8 Sep 2020 12:42:18 -0400
Received: from theia.8bytes.org (8bytes.org
 [IPv6:2a01:238:4383:600:38bc:a715:4b6d:a889])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 77677C061371;
        Tue,  8 Sep 2020 05:44:39 -0700 (PDT)
Received: by theia.8bytes.org (Postfix, from userid 1000)
        id 86023344; Tue,  8 Sep 2020 14:35:18 +0200 (CEST)
Date: Tue, 8 Sep 2020 14:35:17 +0200
From: Joerg Roedel <joro@8bytes.org>
To: x86@kernel.org
Cc: Joerg Roedel <jroedel@suse.de>, hpa@zytor.com,
        Andy Lutomirski <luto@kernel.org>,
        Dave Hansen <dave.hansen@linux.intel.com>,
        Peter Zijlstra <peterz@infradead.org>,
        Jiri Slaby <jslaby@suse.cz>,
        Dan Williams <dan.j.williams@intel.com>,
        Tom Lendacky <thomas.lendacky@amd.com>,
        Juergen Gross <jgross@suse.com>,
        Kees Cook <keescook@chromium.org>,
        David Rientjes <rientjes@google.com>,
        Cfir Cohen <cfir@google.com>,
        Erdem Aktas <erdemaktas@google.com>,
        Masami Hiramatsu <mhiramat@kernel.org>,
        Mike Stunes <mstunes@vmware.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Martin Radev <martin.b.radev@gmail.com>,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org
Subject: [PATCH v7.2 39/74] x86/sev-es: Setup early #VC handler
Message-ID: <20200908123517.GA3764@8bytes.org>
References: <20200907131613.12703-1-joro@8bytes.org>
 <20200907131613.12703-40-joro@8bytes.org>
MIME-Version: 1.0
Content-Disposition: inline
In-Reply-To: <20200907131613.12703-40-joro@8bytes.org>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Joerg Roedel <jroedel@suse.de>

Setup an early handler for #VC exceptions. There is no GHCB mapped
yet, so just re-use the vc_no_ghcb_handler. It can only handle CPUID
exit-codes, but that should be enough to get the kernel through
verify_cpu() and __startup_64() until it runs on virtual addresses.

Signed-off-by: Joerg Roedel <jroedel@suse.de>
---
 arch/x86/include/asm/sev-es.h |  3 +++
 arch/x86/kernel/head64.c      | 25 ++++++++++++++++++++++++-
 arch/x86/kernel/head_64.S     | 30 ++++++++++++++++++++++++++++++
 3 files changed, 57 insertions(+), 1 deletion(-)

```
#### [PATCH v7.2 40/74] x86/sev-es: Setup GHCB based boot #VC handler
##### From: Joerg Roedel <joro@8bytes.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Joerg Roedel <joro@8bytes.org>
X-Patchwork-Id: 11763611
Return-Path: <SRS0=SnLg=CR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 11DE7112E
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  8 Sep 2020 16:42:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E8A36206DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  8 Sep 2020 16:42:47 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732023AbgIHQmq (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 8 Sep 2020 12:42:46 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:33138 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1731979AbgIHQmO (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 8 Sep 2020 12:42:14 -0400
Received: from theia.8bytes.org (8bytes.org
 [IPv6:2a01:238:4383:600:38bc:a715:4b6d:a889])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 69DE2C06136F;
        Tue,  8 Sep 2020 05:43:21 -0700 (PDT)
Received: by theia.8bytes.org (Postfix, from userid 1000)
        id A7309455; Tue,  8 Sep 2020 14:38:17 +0200 (CEST)
Date: Tue, 8 Sep 2020 14:38:16 +0200
From: Joerg Roedel <joro@8bytes.org>
To: x86@kernel.org
Cc: Joerg Roedel <jroedel@suse.de>, hpa@zytor.com,
        Andy Lutomirski <luto@kernel.org>,
        Dave Hansen <dave.hansen@linux.intel.com>,
        Peter Zijlstra <peterz@infradead.org>,
        Jiri Slaby <jslaby@suse.cz>,
        Dan Williams <dan.j.williams@intel.com>,
        Tom Lendacky <thomas.lendacky@amd.com>,
        Juergen Gross <jgross@suse.com>,
        Kees Cook <keescook@chromium.org>,
        David Rientjes <rientjes@google.com>,
        Cfir Cohen <cfir@google.com>,
        Erdem Aktas <erdemaktas@google.com>,
        Masami Hiramatsu <mhiramat@kernel.org>,
        Mike Stunes <mstunes@vmware.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Martin Radev <martin.b.radev@gmail.com>,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org
Subject: [PATCH v7.2 40/74] x86/sev-es: Setup GHCB based boot #VC handler
Message-ID: <20200908123816.GB3764@8bytes.org>
References: <20200907131613.12703-1-joro@8bytes.org>
 <20200907131613.12703-41-joro@8bytes.org>
MIME-Version: 1.0
Content-Disposition: inline
In-Reply-To: <20200907131613.12703-41-joro@8bytes.org>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Joerg Roedel <jroedel@suse.de>

Add the infrastructure to handle #VC exceptions when the kernel runs
on virtual addresses and has a GHCB mapped. This handler will be used
until the runtime #VC handler takes over.

Since the handler runs very early, disable instrumentation for sev-es.c.

Signed-off-by: Joerg Roedel <jroedel@suse.de>
---
 arch/x86/include/asm/realmode.h |   3 +
 arch/x86/include/asm/segment.h  |   2 +-
 arch/x86/include/asm/sev-es.h   |   2 +
 arch/x86/kernel/Makefile        |   2 +
 arch/x86/kernel/head64.c        |   8 +++
 arch/x86/kernel/head_64.S       |  36 ++++++++++
 arch/x86/kernel/sev-es-shared.c |  14 ++--
 arch/x86/kernel/sev-es.c        | 116 ++++++++++++++++++++++++++++++++
 arch/x86/mm/extable.c           |   1 +
 9 files changed, 176 insertions(+), 8 deletions(-)

```
#### [PATCH] KVM: arm64: Allow to limit number of PMU counters
##### From: Alexander Graf <graf@amazon.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Graf <graf@amazon.com>
X-Patchwork-Id: 11763949
Return-Path: <SRS0=SnLg=CR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6C84C1599
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  8 Sep 2020 18:56:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 50AAE208FE
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  8 Sep 2020 18:56:33 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amazon.com header.i=@amazon.com
 header.b="L64aNTEH"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731124AbgIHSz3 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 8 Sep 2020 14:55:29 -0400
Received: from smtp-fw-9101.amazon.com ([207.171.184.25]:62984 "EHLO
        smtp-fw-9101.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726272AbgIHSzH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 8 Sep 2020 14:55:07 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.com; i=@amazon.com; q=dns/txt; s=amazon201209;
  t=1599591308; x=1631127308;
  h=from:to:cc:subject:date:message-id:mime-version:
   content-transfer-encoding;
  bh=x5jEF96sYCAIy62XD2CkEvqSoI0X9CvEDr0LQID4QSM=;
  b=L64aNTEHBgFKOJoGKPJUAnl5WaPuqSpKksJS+9eRL9vbyjF31LnY4KLt
   g8WQtDm+l7c3t5T6SEBCr1PKda7VCp/7bVDdXm+aObMsAyH6ZnNEDueZ+
   S3nbX6VZ5gkwtMbmp2v+3tXyveZbO58ns4B8eFX3mt/s0RAasvnLNWdCH
   Q=;
X-IronPort-AV: E=Sophos;i="5.76,406,1592870400";
   d="scan'208";a="66374160"
Received: from sea32-co-svc-lb4-vlan3.sea.corp.amazon.com (HELO
 email-inbound-relay-2b-c7131dcf.us-west-2.amazon.com) ([10.47.23.38])
  by smtp-border-fw-out-9101.sea19.amazon.com with ESMTP;
 08 Sep 2020 18:55:00 +0000
Received: from EX13MTAUWC001.ant.amazon.com
 (pdx4-ws-svc-p6-lb7-vlan2.pdx.amazon.com [10.170.41.162])
        by email-inbound-relay-2b-c7131dcf.us-west-2.amazon.com (Postfix) with
 ESMTPS id 8E7E7A2582;
        Tue,  8 Sep 2020 18:54:58 +0000 (UTC)
Received: from EX13D20UWC001.ant.amazon.com (10.43.162.244) by
 EX13MTAUWC001.ant.amazon.com (10.43.162.135) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Tue, 8 Sep 2020 18:54:56 +0000
Received: from u79c5a0a55de558.ant.amazon.com (10.43.161.85) by
 EX13D20UWC001.ant.amazon.com (10.43.162.244) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Tue, 8 Sep 2020 18:54:53 +0000
From: Alexander Graf <graf@amazon.com>
To: <kvmarm@lists.cs.columbia.edu>
CC: Marc Zyngier <maz@kernel.org>,
        <linux-arm-kernel@lists.infradead.org>, <kvm@vger.kernel.org>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Robin Murphy <robin.murphy@arm.com>,
        Mark Rutland <mark.rutland@arm.com>,
        Eric Auger <eric.auger@redhat.com>
Subject: [PATCH] KVM: arm64: Allow to limit number of PMU counters
Date: Tue, 8 Sep 2020 20:54:45 +0200
Message-ID: <20200908185445.22561-1-graf@amazon.com>
X-Mailer: git-send-email 2.28.0.394.ge197136389
MIME-Version: 1.0
X-Originating-IP: [10.43.161.85]
X-ClientProxiedBy: EX13D12UWC004.ant.amazon.com (10.43.162.182) To
 EX13D20UWC001.ant.amazon.com (10.43.162.244)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We currently pass through the number of PMU counters that we have available
in hardware to guests. So if my host supports 10 concurrently active PMU
counters, my guest will be able to spawn 10 counters as well.

This is undesireable if we also want to use the PMU on the host for
monitoring. In that case, we want to split the PMU between guest and
host.

To help that case, let's add a PMU attr that allows us to limit the number
of PMU counters that we expose. With this patch in place, user space can
keep some counters free for host use.

Signed-off-by: Alexander Graf <graf@amazon.com>
---

Because this patch touches the same code paths as the vPMU filtering one
and the vPMU filtering generalized a few conditions in the attr path,
I've based it on top. Please let me know if you want it independent instead.
---
 arch/arm64/include/uapi/asm/kvm.h |  7 ++++---
 arch/arm64/kvm/pmu-emul.c         | 22 ++++++++++++++++++++++
 arch/arm64/kvm/sys_regs.c         |  5 +++++
 include/kvm/arm_pmu.h             |  1 +
 4 files changed, 32 insertions(+), 3 deletions(-)

```
#### [PATCH v3 1/5] KVM: arm64: Refactor PMU attribute error handling
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11762843
Return-Path: <SRS0=SnLg=CR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EC036159A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  8 Sep 2020 07:59:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CFE9821D20
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  8 Sep 2020 07:59:04 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1599551944;
	bh=GKYC3lnr2B5+Pi4HQdR597nzMM3piNOBy6vkNYjbNZI=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=yS5noP8mlCP2ZI3T6fmrijS8gqI/G9x9I18lZsmsMuk4Oy/8rfzNekzCfAZ3Ne4KN
	 e0vH4St2mXEXLWDMjMXzjyE0WCOmdHG15/teFSAr/9SIb3v62/FH3jVY1FnlKKaF6E
	 jzZovOwB2OLDutlIpk5/Ox8NNWtCSO066/Q7F7W4=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730045AbgIHH7B (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 8 Sep 2020 03:59:01 -0400
Received: from mail.kernel.org ([198.145.29.99]:38822 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729789AbgIHH6r (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 8 Sep 2020 03:58:47 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id B9D2621D20;
        Tue,  8 Sep 2020 07:58:46 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1599551926;
        bh=GKYC3lnr2B5+Pi4HQdR597nzMM3piNOBy6vkNYjbNZI=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=C/wbdKwWHILxtSRcdpsLzQbagirznr6+MU/yeYC9mWUovnKXXBpcT/np2wX5uEb6p
         C9JW0dDQsOUW9ca0Yay/22VuXhjX1jhx1V77+HCy1eHaDTIERnaXTkSr+MeOBmU4kM
         qyj4u8jvAM0d/92Ywa/CEqusZ9Mw1AojqFsli8sU=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1kFYWb-009zhy-6b; Tue, 08 Sep 2020 08:58:45 +0100
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Robin Murphy <robin.murphy@arm.com>,
        Mark Rutland <mark.rutland@arm.com>,
        Eric Auger <eric.auger@redhat.com>, graf@amazon.com,
        kernel-team@android.com
Subject: [PATCH v3 1/5] KVM: arm64: Refactor PMU attribute error handling
Date: Tue,  8 Sep 2020 08:58:26 +0100
Message-Id: <20200908075830.1161921-2-maz@kernel.org>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20200908075830.1161921-1-maz@kernel.org>
References: <20200908075830.1161921-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com, robin.murphy@arm.com,
 mark.rutland@arm.com, eric.auger@redhat.com, graf@amazon.com,
 kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The PMU emulation error handling is pretty messy when dealing with
attributes. Let's refactor it so that we have less duplication,
and that it is easy to extend later on.

A functional change is that kvm_arm_pmu_v3_init() used to return
-ENXIO when the PMU feature wasn't set. The error is now reported
as -ENODEV, matching the documentation. -ENXIO is still returned
when the interrupt isn't properly configured.

Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 arch/arm64/kvm/pmu-emul.c | 21 +++++++++------------
 1 file changed, 9 insertions(+), 12 deletions(-)

```
#### [PATCH v2] KVM: arm64: Allow to limit number of PMU counters
##### From: Alexander Graf <graf@amazon.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Graf <graf@amazon.com>
X-Patchwork-Id: 11764531
Return-Path: <SRS0=SnLg=CR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D72A559D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  8 Sep 2020 20:57:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B6A6B208FE
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  8 Sep 2020 20:57:53 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amazon.com header.i=@amazon.com
 header.b="VNO1LHvd"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728507AbgIHU5v (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 8 Sep 2020 16:57:51 -0400
Received: from smtp-fw-4101.amazon.com ([72.21.198.25]:40548 "EHLO
        smtp-fw-4101.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726340AbgIHU5s (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 8 Sep 2020 16:57:48 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.com; i=@amazon.com; q=dns/txt; s=amazon201209;
  t=1599598666; x=1631134666;
  h=from:to:cc:subject:date:message-id:mime-version:
   content-transfer-encoding;
  bh=w+WDjUguH6wxTf/jOmY/ulveNsmF3SzEEfvwqGmwBIE=;
  b=VNO1LHvd6X8/8/clAbF7T0MTcXjFwa6z5F7LcL+TBAWhtwjxd0gFl9C7
   7NrHnF503i/rCS3SHTzU5G+bBR5GH2fT1tw9817gawOt7t37uDUTYuhpv
   4DU9DMyE3wpRPrzCpSX/9uHzr3/znz+p9AWdzSTZfs51ABN2CX8qqaPDc
   A=;
X-IronPort-AV: E=Sophos;i="5.76,407,1592870400";
   d="scan'208";a="52844612"
Received: from iad12-co-svc-p1-lb1-vlan3.amazon.com (HELO
 email-inbound-relay-1a-67b371d8.us-east-1.amazon.com) ([10.43.8.6])
  by smtp-border-fw-out-4101.iad4.amazon.com with ESMTP;
 08 Sep 2020 20:57:45 +0000
Received: from EX13MTAUWC002.ant.amazon.com
 (iad12-ws-svc-p26-lb9-vlan2.iad.amazon.com [10.40.163.34])
        by email-inbound-relay-1a-67b371d8.us-east-1.amazon.com (Postfix) with
 ESMTPS id E8903A1716;
        Tue,  8 Sep 2020 20:57:41 +0000 (UTC)
Received: from EX13D20UWC001.ant.amazon.com (10.43.162.244) by
 EX13MTAUWC002.ant.amazon.com (10.43.162.240) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Tue, 8 Sep 2020 20:57:41 +0000
Received: from u79c5a0a55de558.ant.amazon.com (10.43.160.215) by
 EX13D20UWC001.ant.amazon.com (10.43.162.244) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Tue, 8 Sep 2020 20:57:38 +0000
From: Alexander Graf <graf@amazon.com>
To: <kvmarm@lists.cs.columbia.edu>
CC: Marc Zyngier <maz@kernel.org>,
        <linux-arm-kernel@lists.infradead.org>, <kvm@vger.kernel.org>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Robin Murphy <robin.murphy@arm.com>,
        Mark Rutland <mark.rutland@arm.com>,
        Eric Auger <eric.auger@redhat.com>
Subject: [PATCH v2] KVM: arm64: Allow to limit number of PMU counters
Date: Tue, 8 Sep 2020 22:57:30 +0200
Message-ID: <20200908205730.23898-1-graf@amazon.com>
X-Mailer: git-send-email 2.28.0.394.ge197136389
MIME-Version: 1.0
X-Originating-IP: [10.43.160.215]
X-ClientProxiedBy: EX13D03UWA002.ant.amazon.com (10.43.160.144) To
 EX13D20UWC001.ant.amazon.com (10.43.162.244)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We currently pass through the number of PMU counters that we have available
in hardware to guests. So if my host supports 10 concurrently active PMU
counters, my guest will be able to spawn 10 counters as well.

This is undesireable if we also want to use the PMU on the host for
monitoring. In that case, we want to split the PMU between guest and
host.

To help that case, let's add a PMU attr that allows us to limit the number
of PMU counters that we expose. With this patch in place, user space can
keep some counters free for host use.

Signed-off-by: Alexander Graf <graf@amazon.com>
---

Because this patch touches the same code paths as the vPMU filtering one
and the vPMU filtering generalized a few conditions in the attr path,
I've based it on top. Please let me know if you want it independent instead.

v1 -> v2:

  - Add documentation
  - Add read support
---
 Documentation/virt/kvm/devices/vcpu.rst | 25 +++++++++++++++++++++++++
 arch/arm64/include/uapi/asm/kvm.h       |  7 ++++---
 arch/arm64/kvm/pmu-emul.c               | 32 ++++++++++++++++++++++++++++++++
 arch/arm64/kvm/sys_regs.c               |  5 +++++
 include/kvm/arm_pmu.h                   |  1 +
 5 files changed, 67 insertions(+), 3 deletions(-)

```
#### [PATCH v2] KVM: LAPIC: Reduce world switch latency caused by timer_advance_ns
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11762673
Return-Path: <SRS0=SnLg=CR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 893F8746
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  8 Sep 2020 07:19:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6EA0421D1A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  8 Sep 2020 07:19:09 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="BeN69dOd"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729347AbgIHHSY (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 8 Sep 2020 03:18:24 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:58480 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729231AbgIHHSP (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 8 Sep 2020 03:18:15 -0400
Received: from mail-pg1-x541.google.com (mail-pg1-x541.google.com
 [IPv6:2607:f8b0:4864:20::541])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 56ADEC061756;
        Tue,  8 Sep 2020 00:18:13 -0700 (PDT)
Received: by mail-pg1-x541.google.com with SMTP id 7so9399432pgm.11;
        Tue, 08 Sep 2020 00:18:13 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=nu11smmO1MLPBr0YyFlQ7QMaiS4dHSCwCtOQC6QvghQ=;
        b=BeN69dOd73In3yvux1bQOAJFhMWC1wLnRHaJvcHqUsJ+Q63UGjkBTdGZeqfu9OGxay
         FNj8ecK/niHBS6Nnru8IExabjT20+zTvmH9KsgnL0n7FN9R86a45qN4Cb76Yfv4bJFXM
         Quj3T9q+qOX+3vLEkVGOXUh70rXFCIDeKE2lhW0JN7hoshxbe66OecvCZ1BpipR0MtcS
         EPJxBxSH1WCcmU/uMU5zP8WLFN4CFcFMAabSzZRhO/5kfoHwfAmlYTWWrBXNKA3LZKjc
         xc7mJEm01rN6q1Y7COCC1W29ebbIMiRiEdEa4MU4OxhjQRVj2Wzg5RbiBr95GwcS9Mut
         8YWA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=nu11smmO1MLPBr0YyFlQ7QMaiS4dHSCwCtOQC6QvghQ=;
        b=iiDbcE4lzcklQmiqDbsxujv2Y5Q8Bt3qjQQTtVdSruqJK5H+e7ueLbRHFbMgzAH605
         qBn9vIl+GZX2J54cEusvcxIedh3QNeYG4zFq1ujij6A0NPrfb06z6MxFX0XQAv5zLkKV
         ev+R9sTWXDVcAhvCfHgD4EzV8ym3Kys39wUuir4ffWstoEtdl3U6dPlLcq0IK3XxQOx+
         eKv2Yxtat97o+/LrUCqTl4rghRMvAtSQL6wlSHb6pCVVyw+NcuupxPiwgsy6Gf4xVszw
         7rPqemPpdKU0kxEoUSV9PN+Kid/RSDbutNqL/SumJgcbYmQa2NAFZ9LHlzPQvwy9VJQM
         3BHg==
X-Gm-Message-State: AOAM533o0e6ava7FzYcLbqalJCsIf23CmmBjnBpjmNbFWpuz7l+U3AHe
        LGT6B9iZz2UHkOYAWMqFa9wEpjCUrIU=
X-Google-Smtp-Source: 
 ABdhPJyKWwWgF5Vgs/ibNYf3Ni3RsyjIpiAKFC6RiuRkTQz3Mvi0yRcD1cg9VmpKa34bPVoWn+pQpw==
X-Received: by 2002:a62:33c1:: with SMTP id
 z184mr23333624pfz.248.1599549492531;
        Tue, 08 Sep 2020 00:18:12 -0700 (PDT)
Received: from localhost.localdomain ([103.7.29.6])
        by smtp.googlemail.com with ESMTPSA id
 gt11sm6437801pjb.48.2020.09.08.00.18.09
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Tue, 08 Sep 2020 00:18:11 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>
Subject: [PATCH v2] KVM: LAPIC: Reduce world switch latency caused by
 timer_advance_ns
Date: Tue,  8 Sep 2020 15:17:52 +0800
Message-Id: <1599549472-26052-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

All the checks in lapic_timer_int_injected(), __kvm_wait_lapic_expire(), and 
these function calls waste cpu cycles when the timer mode is not tscdeadline. 
We can observe ~1.3% world switch time overhead by kvm-unit-tests/vmexit.flat 
vmcall testing on AMD server. This patch reduces the world switch latency 
caused by timer_advance_ns feature when the timer mode is not tscdeadline by 
simpling move the check against apic->lapic_timer.expired_tscdeadline much 
earlier.

Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
v1 -> v2:
 * move the check against apic->lapic_timer.expired_tscdeadline much earlier 
   instead of reset timer_advance_ns

 arch/x86/kvm/lapic.c   | 11 +++++------
 arch/x86/kvm/svm/svm.c |  4 +---
 arch/x86/kvm/vmx/vmx.c |  4 +---
 3 files changed, 7 insertions(+), 12 deletions(-)

```
#### [PATCH v2 v4.14.y 1/3] vfio/type1: Support faulting PFNMAP vmas
##### From: Ajay Kaher <akaher@vmware.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ajay Kaher <akaher@vmware.com>
X-Patchwork-Id: 11763967
Return-Path: <SRS0=SnLg=CR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A648F59D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  8 Sep 2020 19:00:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 973722068D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  8 Sep 2020 19:00:11 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731440AbgIHTAH (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 8 Sep 2020 15:00:07 -0400
Received: from ex13-edg-ou-001.vmware.com ([208.91.0.189]:51727 "EHLO
        EX13-EDG-OU-001.vmware.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728585AbgIHS63 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 8 Sep 2020 14:58:29 -0400
Received: from sc9-mailhost3.vmware.com (10.113.161.73) by
 EX13-EDG-OU-001.vmware.com (10.113.208.155) with Microsoft SMTP Server id
 15.0.1156.6; Tue, 8 Sep 2020 11:58:24 -0700
Received: from akaher-virtual-machine.eng.vmware.com (unknown
 [10.197.103.239])
        by sc9-mailhost3.vmware.com (Postfix) with ESMTP id 0EBA140B4E;
        Tue,  8 Sep 2020 11:58:26 -0700 (PDT)
From: Ajay Kaher <akaher@vmware.com>
To: <gregkh@linuxfoundation.org>, <sashal@kernel.org>
CC: <alex.williamson@redhat.com>, <cohuck@redhat.com>,
        <peterx@redhat.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <stable@vger.kernel.org>,
        <srivatsab@vmware.com>, <srivatsa@csail.mit.edu>,
        <vsirnapalli@vmware.com>, <akaher@vmware.com>
Subject: [PATCH v2 v4.14.y 1/3] vfio/type1: Support faulting PFNMAP vmas
Date: Wed, 9 Sep 2020 00:24:20 +0530
Message-ID: <1599591263-46520-1-git-send-email-akaher@vmware.com>
X-Mailer: git-send-email 2.7.4
MIME-Version: 1.0
Received-SPF: None (EX13-EDG-OU-001.vmware.com: akaher@vmware.com does not
 designate permitted sender hosts)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Alex Williamson <alex.williamson@redhat.com>

commit 41311242221e3482b20bfed10fa4d9db98d87016 upstream.

With conversion to follow_pfn(), DMA mapping a PFNMAP range depends on
the range being faulted into the vma.  Add support to manually provide
that, in the same way as done on KVM with hva_to_pfn_remapped().

Reviewed-by: Peter Xu <peterx@redhat.com>
Signed-off-by: Alex Williamson <alex.williamson@redhat.com>
[Ajay: Regenerated the patch for v4.14]
Signed-off-by: Ajay Kaher <akaher@vmware.com>
---
 drivers/vfio/vfio_iommu_type1.c | 36 +++++++++++++++++++++++++++++++++---
 1 file changed, 33 insertions(+), 3 deletions(-)

```
#### [PATCH v3] KVM: s390: Introduce storage key removal facility
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11763093
Return-Path: <SRS0=SnLg=CR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A4D28618
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  8 Sep 2020 10:03:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 665C621D47
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  8 Sep 2020 10:03:18 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="EqyzS4OJ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729269AbgIHKDR (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 8 Sep 2020 06:03:17 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:59726 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1729248AbgIHKDQ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 8 Sep 2020 06:03:16 -0400
Received: from pps.filterd (m0098416.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 088A14LH135907;
        Tue, 8 Sep 2020 06:03:14 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=VWNPJ8nrQ3kyrPXv3ORfc0g5VmVXuAU5MlsyPmYGm0k=;
 b=EqyzS4OJcJ6aOvTgxl8KrcSQF7WumTTNF7Gjn52OEfVGgjfNPT7jKJ0uoW9O3wh/lsy2
 2f+iI8NenE5jtksdp7ViF5Yf3dzzjxF3dNf4gImXzrdynCvPXrSMIPUssJGDnQhyRd63
 NxSK0w/shlbKD/VdwqQNBUpDH1VeiZTCPTcAmvtf7UuWf3o+BtRwei9ynPi5emh+V6Pr
 S3iVvkufTAn1DmC6aou21Fp+2YputH0C0qlaFotiDYyP+hCuZNBd8CPfy6HQmSopaYG/
 njxUq8gLE86i2OaBzkRm1giyVElABViegj3eNPspUeIHKa0qCyoVLuDuHMlf9LXxzZzb Zw==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 33e5yec118-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 08 Sep 2020 06:03:14 -0400
Received: from m0098416.ppops.net (m0098416.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 088A1ok8138956;
        Tue, 8 Sep 2020 06:03:13 -0400
Received: from ppma04ams.nl.ibm.com (63.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.99])
        by mx0b-001b2d01.pphosted.com with ESMTP id 33e5yec10e-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 08 Sep 2020 06:03:13 -0400
Received: from pps.filterd (ppma04ams.nl.ibm.com [127.0.0.1])
        by ppma04ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 088A28LW019729;
        Tue, 8 Sep 2020 10:03:12 GMT
Received: from b06cxnps4076.portsmouth.uk.ibm.com
 (d06relay13.portsmouth.uk.ibm.com [9.149.109.198])
        by ppma04ams.nl.ibm.com with ESMTP id 33c2a8ba62-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 08 Sep 2020 10:03:11 +0000
Received: from d06av23.portsmouth.uk.ibm.com (d06av23.portsmouth.uk.ibm.com
 [9.149.105.59])
        by b06cxnps4076.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 088A39TV35455368
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 8 Sep 2020 10:03:09 GMT
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 0662CA4051;
        Tue,  8 Sep 2020 10:03:09 +0000 (GMT)
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 5B963A404D;
        Tue,  8 Sep 2020 10:03:08 +0000 (GMT)
Received: from linux01.pok.stglabs.ibm.com (unknown [9.114.17.81])
        by d06av23.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue,  8 Sep 2020 10:03:08 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: borntraeger@de.ibm.com, imbrenda@linux.ibm.com, david@redhat.com,
        linux-s390@vger.kernel.org
Subject: [PATCH v3] KVM: s390: Introduce storage key removal facility
Date: Tue,  8 Sep 2020 06:02:49 -0400
Message-Id: <20200908100249.23150-1-frankja@linux.ibm.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-09-08_04:2020-09-08,2020-09-08 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 bulkscore=0
 priorityscore=1501 clxscore=1015 mlxscore=0 phishscore=0 mlxlogscore=999
 malwarescore=0 suspectscore=1 impostorscore=0 lowpriorityscore=0
 spamscore=0 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2009080089
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The storage key removal facility makes skey related instructions
result in special operation program exceptions. It is based on the
Keyless Subset Facility.

The usual suspects are iske, sske, rrbe and their respective
variants. lpsw(e), pfmf and tprot can also specify a key and essa with
an ORC of 4 will consult the change bit, hence they all result in
exceptions.

Unfortunately storage keys were so essential to the architecture, that
there is no facility bit that we could deactivate. That's why the
removal facility (bit 169) was introduced which makes it necessary,
that, if active, the skey related facilities 10, 14, 66, 145 and 149
are zero. Managing this requirement and migratability has to be done
in userspace, as KVM does not check the facilities it receives to be
able to easily implement userspace emulation.

Removing storage key support allows us to circumvent complicated
emulation code and makes huge page support tremendously easier.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
---

v3:
	* Put kss handling into own function
	* Removed some unneeded catch statements and converted others to ifs

v2:
	* Removed the likely
	* Updated and re-shuffeled the comments which had the wrong information

---
 arch/s390/kvm/intercept.c | 34 +++++++++++++++++++++++++++++++++-
 arch/s390/kvm/kvm-s390.c  |  5 +++++
 arch/s390/kvm/priv.c      | 26 +++++++++++++++++++++++---
 3 files changed, 61 insertions(+), 4 deletions(-)

```
#### [PATCH v3] s390x: Add 3f program exception handler
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11763391
Return-Path: <SRS0=SnLg=CR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B23AE746
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  8 Sep 2020 14:17:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 98B8A21D90
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  8 Sep 2020 14:17:55 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="IOP7gFXW"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730083AbgIHORe (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 8 Sep 2020 10:17:34 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:10952 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728975AbgIHOQu (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 8 Sep 2020 10:16:50 -0400
Received: from pps.filterd (m0098393.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 088D3Olg133343;
        Tue, 8 Sep 2020 09:05:13 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=rdyzONfAjlQKywvb8PXpfSL9Mb1tE/stNvI+MMrDpDE=;
 b=IOP7gFXWoXksOBcYP2rJa1AZF3ddyycLv23cdx1zvHGrylPNgEz3s188ugQIW4eBEho2
 IXVNm5VaIgTbk3m9vBZLg9qzUoCQzPZaRSat891QIyZbw5hkI0aocNb3XiEoVnfeMf53
 +wVPWW21tIu/79xnAxoPu+85eXCRZKCd6KKZflsBoeuSjIzRB5/NWoHKRu0DDS+5CYn8
 /3Rea0fH6qOEKRZVUbaqkyshpo5ylfF/OtE72cd+y46tKmveaNPhs/35I6NJxEZmbSnM
 cJFD/DRniiws2jXLWzTFUQYb1tEKlLoiNPfZ4zH7v+332UxaHXGWSX0cPcShmLvpeueq 1A==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 33ea0c96st-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 08 Sep 2020 09:05:12 -0400
Received: from m0098393.ppops.net (m0098393.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 088D4dP2139018;
        Tue, 8 Sep 2020 09:05:12 -0400
Received: from ppma03fra.de.ibm.com (6b.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.107])
        by mx0a-001b2d01.pphosted.com with ESMTP id 33ea0c96rb-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 08 Sep 2020 09:05:12 -0400
Received: from pps.filterd (ppma03fra.de.ibm.com [127.0.0.1])
        by ppma03fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 088Cw9al030320;
        Tue, 8 Sep 2020 13:05:10 GMT
Received: from b06avi18878370.portsmouth.uk.ibm.com
 (b06avi18878370.portsmouth.uk.ibm.com [9.149.26.194])
        by ppma03fra.de.ibm.com with ESMTP id 33c2a8a468-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 08 Sep 2020 13:05:09 +0000
Received: from d06av25.portsmouth.uk.ibm.com (d06av25.portsmouth.uk.ibm.com
 [9.149.105.61])
        by b06avi18878370.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 088D57EI62521774
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 8 Sep 2020 13:05:07 GMT
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 2283F11C04C;
        Tue,  8 Sep 2020 13:05:07 +0000 (GMT)
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 3F9C911C052;
        Tue,  8 Sep 2020 13:05:06 +0000 (GMT)
Received: from linux01.pok.stglabs.ibm.com (unknown [9.114.17.81])
        by d06av25.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue,  8 Sep 2020 13:05:06 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: linux-s390@vger.kernel.org
Cc: borntraeger@de.ibm.com, gor@linux.ibm.com, imbrenda@linux.ibm.com,
        kvm@vger.kernel.org, david@redhat.com, hca@linux.ibm.com,
        cohuck@redhat.com, thuth@redhat.com
Subject: [PATCH v3] s390x: Add 3f program exception handler
Date: Tue,  8 Sep 2020 09:05:04 -0400
Message-Id: <20200908130504.24641-1-frankja@linux.ibm.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20200908075337.GA9170@osiris>
References: <20200908075337.GA9170@osiris>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-09-08_06:2020-09-08,2020-09-08 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 adultscore=0 spamscore=0
 bulkscore=0 lowpriorityscore=0 malwarescore=0 priorityscore=1501
 suspectscore=1 phishscore=0 impostorscore=0 mlxscore=0 mlxlogscore=999
 clxscore=1015 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2009080123
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Program exception 3f (secure storage violation) can only be detected
when the CPU is running in SIE with a format 4 state description,
e.g. running a protected guest. Because of this and because user
space partly controls the guest memory mapping and can trigger this
exception, we want to send a SIGSEGV to the process running the guest
and not panic the kernel.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
CC: <stable@vger.kernel.org> # 5.7+
Fixes: 084ea4d611a3 ("s390/mm: add (non)secure page access exceptions handlers")
Reviewed-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Acked-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 arch/s390/kernel/entry.h     |  1 +
 arch/s390/kernel/pgm_check.S |  2 +-
 arch/s390/mm/fault.c         | 20 ++++++++++++++++++++
 3 files changed, 22 insertions(+), 1 deletion(-)

```
#### 
##### 

```c
```
#### [PATCH V4 1/2] vfio dma_map/unmap: optimized for hugetlbfs pages
##### From: Ming Mao <maoming.maoming@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ming Mao <maoming.maoming@huawei.com>
X-Patchwork-Id: 11763751
Return-Path: <SRS0=SnLg=CR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C269E15E4
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  8 Sep 2020 17:35:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AA95D20738
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  8 Sep 2020 17:35:50 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731762AbgIHRfr (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 8 Sep 2020 13:35:47 -0400
Received: from szxga06-in.huawei.com ([45.249.212.32]:34990 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1731737AbgIHRfm (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 8 Sep 2020 13:35:42 -0400
Received: from DGGEMS412-HUB.china.huawei.com (unknown [172.30.72.59])
        by Forcepoint Email with ESMTP id 7CFC6D9380F9D3DCB5E4;
        Tue,  8 Sep 2020 21:32:24 +0800 (CST)
Received: from localhost (10.174.151.129) by DGGEMS412-HUB.china.huawei.com
 (10.3.19.212) with Microsoft SMTP Server id 14.3.487.0; Tue, 8 Sep 2020
 21:32:14 +0800
From: Ming Mao <maoming.maoming@huawei.com>
To: <linux-kernel@vger.kernel.org>, <kvm@vger.kernel.org>,
        <linux-mm@kvack.org>, <alex.williamson@redhat.com>,
        <akpm@linux-foundation.org>
CC: <cohuck@redhat.com>, <jianjay.zhou@huawei.com>,
        <weidong.huang@huawei.com>, <peterx@redhat.com>,
        <aarcange@redhat.com>, <wangyunjian@huawei.com>,
        Ming Mao <maoming.maoming@huawei.com>
Subject: [PATCH V4 1/2] vfio dma_map/unmap: optimized for hugetlbfs pages
Date: Tue, 8 Sep 2020 21:32:03 +0800
Message-ID: <20200908133204.1338-2-maoming.maoming@huawei.com>
X-Mailer: git-send-email 2.26.2.windows.1
In-Reply-To: <20200908133204.1338-1-maoming.maoming@huawei.com>
References: <20200908133204.1338-1-maoming.maoming@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.174.151.129]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In the original process of dma_map/unmap pages for VFIO-devices,
to make sure the pages are contiguous, we have to check them one by one.
As a result, dma_map/unmap could spend a long time.
Using the hugetlb pages, we can avoid this problem.
All pages in hugetlb pages are contiguous.And the hugetlb
page should not be split.So we can delete the for loops.

According to the suggestions of Peter Xu,
we should use the API unpin_user_pages_dirty_lock() to unpin hugetlb pages.
And the pages are unpinned one by one in this API.
So it is better to optimize the API.
In this patch, we do not optimize the process of unpinning.
We will do this in another patch.

Signed-off-by: Ming Mao <maoming.maoming@huawei.com>
---
 drivers/vfio/vfio_iommu_type1.c | 289 +++++++++++++++++++++++++++++++-
 1 file changed, 281 insertions(+), 8 deletions(-)

```
#### [PATCH 1/2] x86/kvm: properly use DEFINE_IDTENTRY_SYSVEC() macro
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11763375
Return-Path: <SRS0=SnLg=CR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 719B2746
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  8 Sep 2020 14:09:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 55FAD221F0
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  8 Sep 2020 14:09:50 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="OMQSjk72"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729635AbgIHOJn (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 8 Sep 2020 10:09:43 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:41827 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1729954AbgIHN6e (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 8 Sep 2020 09:58:34 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1599573442;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=V8gJHVVzl/wwJZfOQGNWW8wLM+ZCeRs5gKT/LuNGCcw=;
        b=OMQSjk72eXgSD5FvYmLtjRHRyXF82GEjzOE6oLSjDI4RIfFn3mwQlnrq/4SJeiacqXOI2N
        yuuztMu03Ckf16Lv87/tfLHaaByKxZ0Zp0OLCV/E/9XWRKFIwKByCZBoP1JifXK5HpPeDZ
        cu5NgegDxSQqSZX3HkOebZqkXjOzwAM=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-329-iMmetHogMoyHJc6VOO_2HA-1; Tue, 08 Sep 2020 09:53:57 -0400
X-MC-Unique: iMmetHogMoyHJc6VOO_2HA-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 6827A1017DC1;
        Tue,  8 Sep 2020 13:53:56 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.194.93])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 3E4D87D8AC;
        Tue,  8 Sep 2020 13:53:54 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, x86@kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        Andy Lutomirski <luto@kernel.org>
Subject: [PATCH 1/2] x86/kvm: properly use DEFINE_IDTENTRY_SYSVEC() macro
Date: Tue,  8 Sep 2020 15:53:49 +0200
Message-Id: <20200908135350.355053-2-vkuznets@redhat.com>
In-Reply-To: <20200908135350.355053-1-vkuznets@redhat.com>
References: <20200908135350.355053-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

DEFINE_IDTENTRY_SYSVEC() already contains irqentry_enter()/
irqentry_exit().

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kernel/kvm.c | 4 ----
 1 file changed, 4 deletions(-)

```
