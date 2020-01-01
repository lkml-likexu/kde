#### [kvm-unit-tests PATCH v3 01/18] lib: arm/arm64: Remove unnecessary dcache maintenance operations
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexandru Elisei <alexandru.elisei@arm.com>
X-Patchwork-Id: 11314285
Return-Path: <SRS0=Z6yu=2V=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 213666C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 31 Dec 2019 16:10:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 07610206EE
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 31 Dec 2019 16:10:13 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727107AbfLaQKM (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 31 Dec 2019 11:10:12 -0500
Received: from foss.arm.com ([217.140.110.172]:35450 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727081AbfLaQKL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 31 Dec 2019 11:10:11 -0500
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 7067F1007;
        Tue, 31 Dec 2019 08:10:11 -0800 (PST)
Received: from e121566-lin.arm.com,emea.arm.com,asiapac.arm.com,usa.arm.com
 (unknown [10.37.8.41])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPA id
 472E13F68F;
        Tue, 31 Dec 2019 08:10:09 -0800 (PST)
From: Alexandru Elisei <alexandru.elisei@arm.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, drjones@redhat.com, maz@kernel.org,
        andre.przywara@arm.com, vladimir.murzin@arm.com,
        mark.rutland@arm.com
Subject: [kvm-unit-tests PATCH v3 01/18] lib: arm/arm64: Remove unnecessary
 dcache maintenance operations
Date: Tue, 31 Dec 2019 16:09:32 +0000
Message-Id: <1577808589-31892-2-git-send-email-alexandru.elisei@arm.com>
X-Mailer: git-send-email 2.7.4
In-Reply-To: <1577808589-31892-1-git-send-email-alexandru.elisei@arm.com>
References: <1577808589-31892-1-git-send-email-alexandru.elisei@arm.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

On ARMv7 with multiprocessing extensions (which are mandated by the
virtualization extensions [1]), and on ARMv8, translation table walks are
coherent [2, 3], which means that no dcache maintenance operations are
required when changing the tables. Remove the maintenance operations so
that we do only the minimum required to ensure correctness.

Translation table walks are coherent if the memory where the tables
themselves reside have the same shareability and cacheability attributes
as the translation table walks. For ARMv8, this is already the case, and
it is only a matter of removing the cache operations.

However, for ARMv7, translation table walks were being configured as
Non-shareable (TTBCR.SH0 = 0b00) and Non-cacheable
(TTBCR.{I,O}RGN0 = 0b00). Fix that by marking them as Inner Shareable,
Normal memory, Inner and Outer Write-Back Write-Allocate Cacheable.

Because translation table walks are now coherent on arm, replace the
TLBIMVAA operation with TLBIMVAAIS in flush_tlb_page, which acts on the
Inner Shareable domain instead of being private to the PE.

The functions that update the translation table are called when the MMU
is off, or to modify permissions, in the case of the cache test, so
break-before-make is not necessary.

[1] ARM DDI 0406C.d, section B1.7
[2] ARM DDI 0406C.d, section B3.3.1
[3] ARM DDI 0487E.a, section D13.2.72
[4] ARM DDI 0487E.a, section K11.5.3

Reported-by: Mark Rutland <mark.rutland@arm.com>
Signed-off-by: Alexandru Elisei <alexandru.elisei@arm.com>
---
 lib/arm/asm/mmu.h           |  4 ++--
 lib/arm/asm/pgtable-hwdef.h |  8 ++++++++
 lib/arm/mmu.c               | 14 +-------------
 arm/cstart.S                |  7 +++++--
 4 files changed, 16 insertions(+), 17 deletions(-)

```
#### [PATCH v10 01/10] Documentation: Add EPT based Subpage Protection and related APIs
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Weijiang <weijiang.yang@intel.com>
X-Patchwork-Id: 11313781
Return-Path: <SRS0=Z6yu=2V=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7B9A11398
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 31 Dec 2019 06:47:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 55FCF206E6
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 31 Dec 2019 06:47:32 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726386AbfLaGqp (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 31 Dec 2019 01:46:45 -0500
Received: from mga04.intel.com ([192.55.52.120]:16543 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725497AbfLaGqo (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 31 Dec 2019 01:46:44 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by fmsmga104.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 30 Dec 2019 22:46:44 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.69,378,1571727600";
   d="scan'208";a="224368474"
Received: from unknown (HELO local-michael-cet-test.sh.intel.com)
 ([10.239.159.128])
  by fmsmga001.fm.intel.com with ESMTP; 30 Dec 2019 22:46:42 -0800
From: Yang Weijiang <weijiang.yang@intel.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        pbonzini@redhat.com, jmattson@google.com,
        sean.j.christopherson@intel.com
Cc: yu.c.zhang@linux.intel.com, alazar@bitdefender.com,
        edwin.zhai@intel.com, Yang Weijiang <weijiang.yang@intel.com>
Subject: [PATCH v10 01/10] Documentation: Add EPT based Subpage Protection and
 related APIs
Date: Tue, 31 Dec 2019 14:50:34 +0800
Message-Id: <20191231065043.2209-2-weijiang.yang@intel.com>
X-Mailer: git-send-email 2.17.2
In-Reply-To: <20191231065043.2209-1-weijiang.yang@intel.com>
References: <20191231065043.2209-1-weijiang.yang@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Co-developed-by: yi.z.zhang@linux.intel.com
Signed-off-by: yi.z.zhang@linux.intel.com
Signed-off-by: Yang Weijiang <weijiang.yang@intel.com>
---
 Documentation/virt/kvm/api.txt        |  39 ++++++
 Documentation/virtual/kvm/spp_kvm.txt | 179 ++++++++++++++++++++++++++
 2 files changed, 218 insertions(+)
 create mode 100644 Documentation/virtual/kvm/spp_kvm.txt

```
