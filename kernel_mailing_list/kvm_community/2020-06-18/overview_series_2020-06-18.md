#### [PATCH] arm64: kvm: Annotate hyp NMI-related functions as __always_inline
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexandru Elisei <alexandru.elisei@arm.com>
X-Patchwork-Id: 11612855
Return-Path: <SRS0=ZHPl=77=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AFF6B1392
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 18 Jun 2020 17:12:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9FD73208C7
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 18 Jun 2020 17:12:18 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731995AbgFRRMR (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 18 Jun 2020 13:12:17 -0400
Received: from foss.arm.com ([217.140.110.172]:55466 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727822AbgFRRMP (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 18 Jun 2020 13:12:15 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 8CB5931B;
        Thu, 18 Jun 2020 10:12:15 -0700 (PDT)
Received: from monolith.arm.com (unknown [10.37.8.10])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 DE59A3F6CF;
        Thu, 18 Jun 2020 10:12:13 -0700 (PDT)
From: Alexandru Elisei <alexandru.elisei@arm.com>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: maz@kernel.org, james.morse@arm.com, julien.thierry.kdev@gmail.com,
        suzuki.poulose@arm.com, will@kernel.org, catalin.marinas@arm.com
Subject: [PATCH] arm64: kvm: Annotate hyp NMI-related functions as
 __always_inline
Date: Thu, 18 Jun 2020 18:12:54 +0100
Message-Id: <20200618171254.1596055-1-alexandru.elisei@arm.com>
X-Mailer: git-send-email 2.27.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The "inline" keyword is a hint for the compiler to inline a function.  The
functions system_uses_irq_prio_masking() and gic_write_pmr() are used by
the code running at EL2 on a non-VHE system, so mark them as
__always_inline to make sure they'll always be part of the .hyp.text
section.

This fixes the following splat when trying to run a VM:

[   47.625273] Kernel panic - not syncing: HYP panic:
[   47.625273] PS:a00003c9 PC:0000ca0b42049fc4 ESR:86000006
[   47.625273] FAR:0000ca0b42049fc4 HPFAR:0000000010001000 PAR:0000000000000000
[   47.625273] VCPU:0000000000000000
[   47.647261] CPU: 1 PID: 217 Comm: kvm-vcpu-0 Not tainted 5.8.0-rc1-ARCH+ #61
[   47.654508] Hardware name: Globalscale Marvell ESPRESSOBin Board (DT)
[   47.661139] Call trace:
[   47.663659]  dump_backtrace+0x0/0x1cc
[   47.667413]  show_stack+0x18/0x24
[   47.670822]  dump_stack+0xb8/0x108
[   47.674312]  panic+0x124/0x2f4
[   47.677446]  panic+0x0/0x2f4
[   47.680407] SMP: stopping secondary CPUs
[   47.684439] Kernel Offset: disabled
[   47.688018] CPU features: 0x240402,20002008
[   47.692318] Memory Limit: none
[   47.695465] ---[ end Kernel panic - not syncing: HYP panic:
[   47.695465] PS:a00003c9 PC:0000ca0b42049fc4 ESR:86000006
[   47.695465] FAR:0000ca0b42049fc4 HPFAR:0000000010001000 PAR:0000000000000000
[   47.695465] VCPU:0000000000000000 ]---

The instruction abort was caused by the code running at EL2 trying to fetch
an instruction which wasn't mapped in the EL2 translation tables. Using
objdump showed the two functions as separate symbols in the .text section.

Fixes: 85738e05dc38 ("arm64: kvm: Unmask PMR before entering guest")
Signed-off-by: Alexandru Elisei <alexandru.elisei@arm.com>
---
 arch/arm64/include/asm/arch_gicv3.h | 2 +-
 arch/arm64/include/asm/cpufeature.h | 2 +-
 2 files changed, 2 insertions(+), 2 deletions(-)

```
#### [kvm-unit-tests PATCH v2] x86: Add control register pinning tests
##### From: John Andersen <john.s.andersen@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Andersen, John" <john.s.andersen@intel.com>
X-Patchwork-Id: 11612257
Return-Path: <SRS0=ZHPl=77=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 40B4E1392
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 18 Jun 2020 14:03:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 243AB2082F
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 18 Jun 2020 14:03:40 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727801AbgFRODj (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 18 Jun 2020 10:03:39 -0400
Received: from mga09.intel.com ([134.134.136.24]:40025 "EHLO mga09.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725987AbgFRODh (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 18 Jun 2020 10:03:37 -0400
IronPort-SDR: 
 988lPZ4RanmIhGHZ/tFfYy6gdTmGP/rQSUsCKk5UxFtJj45ygFlLRYT62dRFquBKgqZISx+V9w
 zor1+UBcpuUg==
X-IronPort-AV: E=McAfee;i="6000,8403,9655"; a="144094722"
X-IronPort-AV: E=Sophos;i="5.73,526,1583222400";
   d="scan'208";a="144094722"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga005.fm.intel.com ([10.253.24.32])
  by orsmga102.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 18 Jun 2020 07:03:32 -0700
IronPort-SDR: 
 imGXRQKCZKXB03PP+i/S3Hmk2U4QSsVtM/0i5VZ2hU3Sy4FTF+ubpddOPWNP3pyk/y3mNQonN6
 QsM61x7TCFIg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,526,1583222400";
   d="scan'208";a="477248114"
Received: from gza.jf.intel.com ([10.54.75.28])
  by fmsmga005.fm.intel.com with ESMTP; 18 Jun 2020 07:03:31 -0700
From: John Andersen <john.s.andersen@intel.com>
To: nadav.amit@gmail.com, corbet@lwn.net, pbonzini@redhat.com,
        tglx@linutronix.de, mingo@redhat.com, bp@alien8.de, hpa@zytor.com,
        shuah@kernel.org, sean.j.christopherson@intel.com,
        rick.p.edgecombe@intel.com, kvm@vger.kernel.org
Cc: john.s.andersen@intel.com, kernel-hardening@lists.openwall.com
Subject: [kvm-unit-tests PATCH v2] x86: Add control register pinning tests
Date: Thu, 18 Jun 2020 07:06:41 -0700
Message-Id: <20200618140641.9762-1-john.s.andersen@intel.com>
X-Mailer: git-send-email 2.21.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Paravirutalized control register pinning adds MSRs guests can use to
discover which bits in CR0/4 they may pin, and MSRs for activating
pinning for any of those bits.

We check that the bits allowed to be pinned for CR4 are UMIP, SMEP, and
SMAP. Only WP should be allowed to be pinned in CR0.

We turn on all of the allowed bits, pin them, then attempt to disable
them. We verify that the attempt to disable was unsuccessful, and that
it generated a general protection fault.

For nested, we check that for when pinning enabled in L1, changing
HOST_CR0/4 will not result in the un-setting of pinned bits. The VMX CR
pinning tests is it's own test so that the pinning doesn't potentially
affect other tests within the same .flat testing VM.

Signed-off-by: John Andersen <john.s.andersen@intel.com>
---
 x86/Makefile.common |   3 +-
 lib/x86/desc.h      |   1 +
 lib/x86/msr.h       |   8 ++
 lib/x86/processor.h |   6 ++
 lib/x86/desc.c      |   8 ++
 x86/cr_pin_high.c   | 213 ++++++++++++++++++++++++++++++++++++++++++++
 x86/cr_pin_low.c    |  65 ++++++++++++++
 x86/pcid.c          |   8 --
 x86/vmx_tests.c     | 144 ++++++++++++++++++++++++++++++
 x86/unittests.cfg   |  16 +++-
 10 files changed, 462 insertions(+), 10 deletions(-)
 create mode 100644 x86/cr_pin_high.c
 create mode 100644 x86/cr_pin_low.c

```
#### [PATCH v6 33/36] samples: vfio-mdev/mbochs: fix common struct sg_table related issues
##### From: Marek Szyprowski <m.szyprowski@samsung.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marek Szyprowski <m.szyprowski@samsung.com>
X-Patchwork-Id: 11612597
Return-Path: <SRS0=ZHPl=77=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 24BB4912
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 18 Jun 2020 15:41:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 07F8D2075E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 18 Jun 2020 15:41:38 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=samsung.com header.i=@samsung.com
 header.b="KZMr6zGK"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731820AbgFRPlg (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 18 Jun 2020 11:41:36 -0400
Received: from mailout1.w1.samsung.com ([210.118.77.11]:54962 "EHLO
        mailout1.w1.samsung.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1731713AbgFRPkn (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 18 Jun 2020 11:40:43 -0400
Received: from eucas1p1.samsung.com (unknown [182.198.249.206])
        by mailout1.w1.samsung.com (KnoxPortal) with ESMTP id
 20200618154038euoutp010e1948411e76854c49c7ba236cdc4602~ZrZ4pHgIR1844818448euoutp01P
        for <kvm@vger.kernel.org>; Thu, 18 Jun 2020 15:40:38 +0000 (GMT)
DKIM-Filter: OpenDKIM Filter v2.11.0 mailout1.w1.samsung.com
 20200618154038euoutp010e1948411e76854c49c7ba236cdc4602~ZrZ4pHgIR1844818448euoutp01P
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=samsung.com;
        s=mail20170921; t=1592494838;
        bh=i9tfBl9XK1ZIcmVNmOj760Z4Av4MmZkmEeWSykU107Y=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=KZMr6zGKccCjIXwLvtaZvINM5cvedqSKjLsMAlbFaqa/2uidxZv4eJwZw6UlCvaeF
         9YebsQk0pCSOf0hZVeGz5jyKC7bIKsyTqcxutg8SECaAxAFjSsElGDvinxdLb+wtUU
         aDzTWa6ipwlVAyqCaRl33uC2xz3NXA3enEo71oO0=
Received: from eusmges1new.samsung.com (unknown [203.254.199.242]) by
        eucas1p1.samsung.com (KnoxPortal) with ESMTP id
        20200618154037eucas1p162bd4bce5ff25284dc35a3b750373f07~ZrZ4YCBn21545815458eucas1p1m;
        Thu, 18 Jun 2020 15:40:37 +0000 (GMT)
Received: from eucas1p2.samsung.com ( [182.198.249.207]) by
        eusmges1new.samsung.com (EUCPMTA) with SMTP id FB.1F.61286.5FA8BEE5;
 Thu, 18
        Jun 2020 16:40:37 +0100 (BST)
Received: from eusmtrp2.samsung.com (unknown [182.198.249.139]) by
        eucas1p1.samsung.com (KnoxPortal) with ESMTPA id
        20200618154037eucas1p19a60af169ef9c272b9d1eecf589f6627~ZrZ4Bn1_B1545815458eucas1p1l;
        Thu, 18 Jun 2020 15:40:37 +0000 (GMT)
Received: from eusmgms1.samsung.com (unknown [182.198.249.179]) by
        eusmtrp2.samsung.com (KnoxPortal) with ESMTP id
        20200618154037eusmtrp2e1d1f0ddf5441e208cc3e8e1afc41c0b~ZrZ4A_iTP0370403704eusmtrp2w;
        Thu, 18 Jun 2020 15:40:37 +0000 (GMT)
X-AuditID: cbfec7f2-ef1ff7000001ef66-f2-5eeb8af57b24
Received: from eusmtip1.samsung.com ( [203.254.199.221]) by
        eusmgms1.samsung.com (EUCPMTA) with SMTP id 78.FE.08375.5FA8BEE5;
 Thu, 18
        Jun 2020 16:40:37 +0100 (BST)
Received: from AMDC2765.digital.local (unknown [106.120.51.73]) by
        eusmtip1.samsung.com (KnoxPortal) with ESMTPA id
        20200618154036eusmtip1fb60c40ddcb27db26c518640dc3aacde~ZrZ3a9J5Z0742307423eusmtip1Y;
        Thu, 18 Jun 2020 15:40:36 +0000 (GMT)
From: Marek Szyprowski <m.szyprowski@samsung.com>
To: dri-devel@lists.freedesktop.org, iommu@lists.linux-foundation.org,
        linaro-mm-sig@lists.linaro.org, linux-kernel@vger.kernel.org
Cc: Marek Szyprowski <m.szyprowski@samsung.com>,
        Christoph Hellwig <hch@lst.de>,
        Robin Murphy <robin.murphy@arm.com>,
        Bartlomiej Zolnierkiewicz <b.zolnierkie@samsung.com>,
        linux-arm-kernel@lists.infradead.org,
        David Airlie <airlied@linux.ie>,
        Daniel Vetter <daniel@ffwll.ch>,
        Kirti Wankhede <kwankhede@nvidia.com>, kvm@vger.kernel.org
Subject: [PATCH v6 33/36] samples: vfio-mdev/mbochs: fix common struct
 sg_table related issues
Date: Thu, 18 Jun 2020 17:39:54 +0200
Message-Id: <20200618153956.29558-34-m.szyprowski@samsung.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200618153956.29558-1-m.szyprowski@samsung.com>
X-Brightmail-Tracker: 
 H4sIAAAAAAAAA0VSa0hTYRjuO2fn7GjOjpvgh0nGIsnAGxUeUMTMH4cKuv0oBC8zDypuuja1
        FCRTFzK1NDNNLC0E865zzktKOdQlmpcpy0umov7QoYY6sUma2yn79zzP+7zP873wESi/BXMm
        YuMTGVm8SCzEbTma/l8jHialMcy79J07lTc8gFDNJY0YdaApQKkJ0wZOVdf2IVTFJz+qrOgB
        pR58A6jtiQWEUi0aMGq8swyn6ntnuVTPzyUskEfXva0DdPdOBYdu25nH6LkcHUK3VD6mZ/YX
        UbpwsgrQH6fScTovcx2nn6lrAL2lOnXzeIitfxQjjk1mZF4BEbYxexoVV1rp8Gi6PSEdNNsr
        AUFA8iKcrwpUAluCT34AcKm8msOSbQDzVrU4S7YAVGv6MCWwsW4MVOpRdlAF4N5GNnq0krE8
        iltcOOkDlWtKK3YkFQB+ybOzmFDSgMC13+vWKAEZAfWmSivmkGfhXFkNYsE8MgAOPM/B2TpX
        WNv0GbVgm0N9UKfALEGQ1HJhxVAZwl4RDL+1oqxfAFd1ai6LXeBBRznC+jMBXBiu57IkF8Dx
        jBLAuvzg92EzbglCSXfY2OnFypfhzKtpLptvDyfXHCwyeghfaIpRVubB7Kd81u0GS3UNR7U9
        o/q/z6Hham+R9RQ+WQDgSAueD1xL/3dVAFADnJgkuSSakfvEMw895SKJPCk+2vN+gkQFDr/S
        4L5usx2Y9JFaQBJAaMcLvGsM42OiZHmKRAsggQodeUFfB8P4vChRSiojSwiXJYkZuRacJDhC
        J96F9yuhfDJalMjEMYyUkf2bIoSNczroNt+OG+1o8hGPFRnRW/5TY0OOBwvBsy6hpzPPtc0c
        w38sh6f2GnyvKN2WpVncrq6NEKwYO9mflTtuZphLuVpkZa/1xtVrL8ndFLP0db1CIvCG+Y2+
        Z5bvnNj0bfDfuFeoSDMJnlCl3rtBxm6P/fWt4rTIIUNzd6ZICJ0414UceYzI5zwqk4v+ALRX
        GcFGAwAA
X-Brightmail-Tracker: 
 H4sIAAAAAAAAA+NgFprKIsWRmVeSWpSXmKPExsVy+t/xu7pfu17HGZxYLWbRe+4kk8XGGetZ
        Lf5vm8hsceXrezaLlauPMlks2G9tMWdqocWW03MZLb5cechksenxNVaLy7vmsFmsPXKX3eLg
        hyesDrwea+atYfTY+20Bi8f2bw9YPe53H2fy2Lyk3uP2v8fMHpNvLGf02H2zgc2jt/kdm0ff
        llWMHp83yQVwR+nZFOWXlqQqZOQXl9gqRRtaGOkZWlroGZlY6hkam8daGZkq6dvZpKTmZJal
        FunbJehl/N62ib1giWDFrR35DYwb+boYOTkkBEwkTi65xNzFyMUhJLCUUeLC9H3MEAkZiZPT
        GlghbGGJP9e62CCKPjFKPLo3mw0kwSZgKNH1FiIhItDJKDGt+yM7SIJZ4B6TxN51fl2MHBzC
        AnEST0+BhVkEVCXuz1nFBGLzCthJnOzvZoNYIC+xesMBsMWcQPHTx1vBFgsJ2Eo8/9DGNoGR
        bwEjwypGkdTS4tz03GJDveLE3OLSvHS95PzcTYzAKNl27OfmHYyXNgYfYhTgYFTi4X0R8jpO
        iDWxrLgy9xCjBAezkgiv09nTcUK8KYmVValF+fFFpTmpxYcYTYGOmsgsJZqcD4zgvJJ4Q1ND
        cwtLQ3Njc2MzCyVx3g6BgzFCAumJJanZqakFqUUwfUwcnFINjDNCV88xOhK1dtqtd3p1c/RW
        1HUGTYi8FZc783pN96+0qub/YddXfs0JeHXlfvnWqjZ2Xo66CbeuzfAq6LoicuVD5/ZMF5+r
        ZxoKZNjVfuwxXpiTKCivzDx9JVf0tFnRDyXXfPjzNOKHRXR17fqjHuvXO2iGtN9vO1deKc4+
        4ZWu398liUarGJVYijMSDbWYi4oTAZpEzByoAgAA
X-CMS-MailID: 20200618154037eucas1p19a60af169ef9c272b9d1eecf589f6627
X-Msg-Generator: CA
X-RootMTR: 20200618154037eucas1p19a60af169ef9c272b9d1eecf589f6627
X-EPHeader: CA
CMS-TYPE: 201P
X-CMS-RootMailID: 20200618154037eucas1p19a60af169ef9c272b9d1eecf589f6627
References: <20200618153956.29558-1-m.szyprowski@samsung.com>
        <CGME20200618154037eucas1p19a60af169ef9c272b9d1eecf589f6627@eucas1p1.samsung.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The Documentation/DMA-API-HOWTO.txt states that the dma_map_sg() function
returns the number of the created entries in the DMA address space.
However the subsequent calls to the dma_sync_sg_for_{device,cpu}() and
dma_unmap_sg must be called with the original number of the entries
passed to the dma_map_sg().

struct sg_table is a common structure used for describing a non-contiguous
memory buffer, used commonly in the DRM and graphics subsystems. It
consists of a scatterlist with memory pages and DMA addresses (sgl entry),
as well as the number of scatterlist entries: CPU pages (orig_nents entry)
and DMA mapped pages (nents entry).

It turned out that it was a common mistake to misuse nents and orig_nents
entries, calling DMA-mapping functions with a wrong number of entries or
ignoring the number of mapped entries returned by the dma_map_sg()
function.

To avoid such issues, lets use a common dma-mapping wrappers operating
directly on the struct sg_table objects and use scatterlist page
iterators where possible. This, almost always, hides references to the
nents and orig_nents entries, making the code robust, easier to follow
and copy/paste safe.

While touching this code, also add missing call to dma_unmap_sgtable.

Signed-off-by: Marek Szyprowski <m.szyprowski@samsung.com>
---
 samples/vfio-mdev/mbochs.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [PATCH][next] vfio/type1: Use struct_size() helper
##### From: "Gustavo A. R. Silva" <gustavoars@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Gustavo A. R. Silva" <gustavoars@kernel.org>
X-Patchwork-Id: 11612933
Return-Path: <SRS0=ZHPl=77=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8745614E3
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 18 Jun 2020 19:16:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6F064208C3
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 18 Jun 2020 19:16:17 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1592507777;
	bh=GKvyYGsgx2yaXPftx75dKRpr9bN/B2GO4AJDXtGC5gg=;
	h=Date:From:To:Cc:Subject:List-ID:From;
	b=1Itt3KLxzgYRtU1lFrjgF/N1ripVVMIEQY3yOYXat5YM4awl1Y1tJhB6iEIDULzqH
	 hvCH0PaGGI4r/Q/DNdbRqUJ6gmEIAiD/WgKe4L6nyaDGkwHD0+TsZhfWC8ZV83JYzo
	 +S4sJyyKsIVbVWAGWLqQoPbR4C8ArfgmeLm7Plfs=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728254AbgFRTQM (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 18 Jun 2020 15:16:12 -0400
Received: from mail.kernel.org ([198.145.29.99]:40148 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728199AbgFRTQM (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 18 Jun 2020 15:16:12 -0400
Received: from embeddedor (unknown [189.207.59.248])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 477BE207E8;
        Thu, 18 Jun 2020 19:16:11 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1592507771;
        bh=GKvyYGsgx2yaXPftx75dKRpr9bN/B2GO4AJDXtGC5gg=;
        h=Date:From:To:Cc:Subject:From;
        b=uI3teB5B/fXNlwUMuCmt7oZL7V2rKZwgv11rCamXcgA0gCjDvXhESWovaTch6TRyT
         0SDa+oC2QyKAEFlS1klmR2RJsRA8hPrZ5TCWMyseoGh7+u3pnZgi6CMRypr2/Yx33V
         w64cO+I4FyeMU2oMFEzN1g46KH21YejZhgC/Zm3A=
Date: Thu, 18 Jun 2020 14:21:34 -0500
From: "Gustavo A. R. Silva" <gustavoars@kernel.org>
To: Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        "Gustavo A. R. Silva" <gustavo@embeddedor.com>
Subject: [PATCH][next] vfio/type1: Use struct_size() helper
Message-ID: <20200618192134.GA30734@embeddedor>
MIME-Version: 1.0
Content-Disposition: inline
User-Agent: Mutt/1.9.4 (2018-02-28)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Make use of the struct_size() helper instead of an open-coded version
in order to avoid any potential type mistakes.

This code was detected with the help of Coccinelle and, audited and
fixed manually.

Signed-off-by: Gustavo A. R. Silva <gustavoars@kernel.org>
---
 drivers/vfio/vfio_iommu_type1.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v8 1/2] s390/setup: diag 318: refactor struct
##### From: Collin Walling <walling@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Collin Walling <walling@linux.ibm.com>
X-Patchwork-Id: 11612999
Return-Path: <SRS0=ZHPl=77=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AB4A0618
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 18 Jun 2020 22:22:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9DE1B20885
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 18 Jun 2020 22:22:50 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732035AbgFRWWs (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 18 Jun 2020 18:22:48 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:44638 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1732004AbgFRWWq (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 18 Jun 2020 18:22:46 -0400
Received: from pps.filterd (m0098410.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 05IM27Ob022477;
        Thu, 18 Jun 2020 18:22:45 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 31rerm3ttw-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 18 Jun 2020 18:22:44 -0400
Received: from m0098410.ppops.net (m0098410.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 05IMI3QE070797;
        Thu, 18 Jun 2020 18:22:44 -0400
Received: from ppma03dal.us.ibm.com (b.bd.3ea9.ip4.static.sl-reverse.com
 [169.62.189.11])
        by mx0a-001b2d01.pphosted.com with ESMTP id 31rerm3ttj-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 18 Jun 2020 18:22:44 -0400
Received: from pps.filterd (ppma03dal.us.ibm.com [127.0.0.1])
        by ppma03dal.us.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 05IML5BY028730;
        Thu, 18 Jun 2020 22:22:43 GMT
Received: from b03cxnp08025.gho.boulder.ibm.com
 (b03cxnp08025.gho.boulder.ibm.com [9.17.130.17])
        by ppma03dal.us.ibm.com with ESMTP id 31q6c64wc8-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 18 Jun 2020 22:22:43 +0000
Received: from b03ledav001.gho.boulder.ibm.com
 (b03ledav001.gho.boulder.ibm.com [9.17.130.232])
        by b03cxnp08025.gho.boulder.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 05IMMdpw30736782
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 18 Jun 2020 22:22:39 GMT
Received: from b03ledav001.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 4C13B6E052;
        Thu, 18 Jun 2020 22:22:40 +0000 (GMT)
Received: from b03ledav001.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 61AB26E04C;
        Thu, 18 Jun 2020 22:22:39 +0000 (GMT)
Received: from localhost.localdomain.com (unknown [9.85.159.16])
        by b03ledav001.gho.boulder.ibm.com (Postfix) with ESMTP;
        Thu, 18 Jun 2020 22:22:39 +0000 (GMT)
From: Collin Walling <walling@linux.ibm.com>
To: kvm@vger.kernel.org, linux-s390@vger.kernel.org
Cc: pbonzini@redhat.com, borntraeger@de.ibm.com, frankja@linux.ibm.com,
        david@redhat.com, cohuck@redhat.com, imbrenda@linux.ibm.com,
        heiko.carstens@de.ibm.com, gor@linux.ibm.com, thuth@redhat.com
Subject: [PATCH v8 1/2] s390/setup: diag 318: refactor struct
Date: Thu, 18 Jun 2020 18:22:21 -0400
Message-Id: <20200618222222.23175-2-walling@linux.ibm.com>
X-Mailer: git-send-email 2.21.3
In-Reply-To: <20200618222222.23175-1-walling@linux.ibm.com>
References: <20200618222222.23175-1-walling@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.216,18.0.687
 definitions=2020-06-18_21:2020-06-18,2020-06-18 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 phishscore=0 mlxlogscore=999
 impostorscore=0 lowpriorityscore=0 spamscore=0 priorityscore=1501
 suspectscore=0 malwarescore=0 clxscore=1015 bulkscore=0 adultscore=0
 cotscore=-2147483648 mlxscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-2004280000 definitions=main-2006180164
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The diag 318 struct introduced in include/asm/diag.h can be
reused in KVM, so let's condense the version code fields in the
diag318_info struct for easier usage and simplify it until we
can determine how the data should be formatted.

Signed-off-by: Collin Walling <walling@linux.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
Reviewed-by: Janosch Frank <frankja@linux.ibm.com>
---
 arch/s390/include/asm/diag.h | 6 ++----
 arch/s390/kernel/setup.c     | 3 +--
 2 files changed, 3 insertions(+), 6 deletions(-)

```
#### [PATCH v2] KVM: SVM: emulate MSR_IA32_PERF_CAPABILITIES
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11611825
Return-Path: <SRS0=ZHPl=77=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0DCAF912
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 18 Jun 2020 11:13:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E929B208D5
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 18 Jun 2020 11:13:50 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="HiYSsdPr"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729454AbgFRLNs (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 18 Jun 2020 07:13:48 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:26074 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1728262AbgFRLNg (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 18 Jun 2020 07:13:36 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1592478814;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=dAjSN5aDL+hVRsYsF7/VthZ3MY7xiAzNFu4+vdSACNM=;
        b=HiYSsdPrQ4WA5YRuQB2k54tYe5BIYF6NX2SHReOPGjYShxC4VHW3pmDf1M7xQGOouq2l4s
        BYbV39c14Hn4UAUrF6XBdds9ELsZCIXHMYp1+1OkZzFYbjvYUrClwAQBKmfe43A8EITMy6
        GcqMftPU7i3p97W2LAd8Ww5DrY3PJ9w=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-219-aqOfGQKUNQKHtDcjW29_eg-1; Thu, 18 Jun 2020 07:13:33 -0400
X-MC-Unique: aqOfGQKUNQKHtDcjW29_eg-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id D907E801504;
        Thu, 18 Jun 2020 11:13:31 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.194.81])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 8FAE910013D6;
        Thu, 18 Jun 2020 11:13:29 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Like Xu <like.xu@linux.intel.com>, linux-kernel@vger.kernel.org
Subject: [PATCH v2] KVM: SVM: emulate MSR_IA32_PERF_CAPABILITIES
Date: Thu, 18 Jun 2020 13:13:28 +0200
Message-Id: <20200618111328.429931-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

state_test/smm_test selftests are failing on AMD with:
"Unexpected result from KVM_GET_MSRS, r: 51 (failed MSR was 0x345)"

MSR_IA32_PERF_CAPABILITIES is an emulated MSR on Intel but it is not
known to AMD code, emulate it there too (by returning 0 and allowing
userspace to write 0). This way the code is better prepared to the
eventual appearance of the feature in AMD hardware.

Fixes: 27461da31089 ("KVM: x86/pmu: Support full width counting")
Suggested-by: Jim Mattson <jmattson@google.com>
Suggested-by: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/svm/pmu.c | 29 ++++++++++++++++++++++++++++-
 1 file changed, 28 insertions(+), 1 deletion(-)

```
#### [PATCH] vfio: Cleanup allowed driver namingFrom: Alex Williamson <alex.williamson@redhat.com>
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alex Williamson <alex.williamson@redhat.com>
X-Patchwork-Id: 11612941
Return-Path: <SRS0=ZHPl=77=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EE46F618
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 18 Jun 2020 19:57:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D5CF8208C3
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 18 Jun 2020 19:57:30 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="fkY3wk1C"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730523AbgFRT50 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 18 Jun 2020 15:57:26 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:44767 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1727909AbgFRT50 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 18 Jun 2020 15:57:26 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1592510245;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=6uhU1vYx1jeJPqDKTT2tgprjXa1p0qoF4btUD8t6CkI=;
        b=fkY3wk1C319/JiTTjkBF9M9AF+YWMQ+/XsJrOj0IGm6iRB7h63z9zjolpB++osbvzWa5bH
        +dM7qciDR13Uk9m8H3He5SYi7/ezgVGsEjpLDJRyHe+7fcQYreSGeQS/t7ynkDECOpp6VV
        Cyj2FjLyS2785IsALfF5zXNsrb13S3g=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-339-FqpFi6npO-ygI0rj1Xk_6A-1; Thu, 18 Jun 2020 15:57:22 -0400
X-MC-Unique: FqpFi6npO-ygI0rj1Xk_6A-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 05F57107ACCD;
        Thu, 18 Jun 2020 19:57:22 +0000 (UTC)
Received: from gimli.home (ovpn-112-195.phx2.redhat.com [10.3.112.195])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 838AB5BAC2;
        Thu, 18 Jun 2020 19:57:18 +0000 (UTC)
Subject: [PATCH] vfio: Cleanup allowed driver naming
From: Alex Williamson <alex.williamson@redhat.com>
To: alex.williamson@redhat.com
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        cohuck@redhat.com
Date: Thu, 18 Jun 2020 13:57:18 -0600
Message-ID: <159251018108.23973.14170848139642305203.stgit@gimli.home>
User-Agent: StGit/0.19-dirty
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

No functional change, avoid non-inclusive naming schemes.

Signed-off-by: Alex Williamson <alex.williamson@redhat.com>
---
 drivers/vfio/vfio.c |   12 ++++++------
 1 file changed, 6 insertions(+), 6 deletions(-)

```
#### [PATCH] vfio/type1: Fix migration info capability IDFrom: Alex Williamson <alex.williamson@redhat.com>
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alex Williamson <alex.williamson@redhat.com>
X-Patchwork-Id: 11612931
Return-Path: <SRS0=ZHPl=77=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CD3B213A0
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 18 Jun 2020 19:12:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B440B20B1F
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 18 Jun 2020 19:12:23 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="f9v17/vY"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728615AbgFRTMU (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 18 Jun 2020 15:12:20 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:50215 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726879AbgFRTMT (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 18 Jun 2020 15:12:19 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1592507538;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=K3Y9Ku4t7g7FpHAGcPWhhFdBH9tIdcnitGnwvpTD3+Y=;
        b=f9v17/vY0WJUFJvsahcIZIz3EsEGqT9Th9+IKKuzlfGW/8/KyYw5ehblgWtX4H9kPPEUZB
        L4BMp22ttLabGgcfETvOYdGah3aUhs8lv8fq7bvlBCkaoK8f1D58rmtlaEeVLJU44MmmkT
        ujSm39nJulPRWqaXIqmjQvZk6sHN6z8=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-35-fL7y4JKLMpCryjmxrydDfw-1; Thu, 18 Jun 2020 15:12:17 -0400
X-MC-Unique: fL7y4JKLMpCryjmxrydDfw-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id CB07B464;
        Thu, 18 Jun 2020 19:12:15 +0000 (UTC)
Received: from gimli.home (ovpn-112-195.phx2.redhat.com [10.3.112.195])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 6996419C4F;
        Thu, 18 Jun 2020 19:12:12 +0000 (UTC)
Subject: [PATCH] vfio/type1: Fix migration info capability ID
From: Alex Williamson <alex.williamson@redhat.com>
To: alex.williamson@redhat.com
Cc: Liu Yi L <yi.l.liu@intel.com>,
        Kirti Wankhede <kwankhede@nvidia.com>,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Date: Thu, 18 Jun 2020 13:12:12 -0600
Message-ID: <159250751478.22544.8607332732745502185.stgit@gimli.home>
User-Agent: StGit/0.19-dirty
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

ID 1 is already used by the IOVA range capability, use ID 2.

Reported-by: Liu Yi L <yi.l.liu@intel.com>
Cc: Kirti Wankhede <kwankhede@nvidia.com>
Fixes: ad721705d09c ("vfio iommu: Add migration capability to report supported features")
Signed-off-by: Alex Williamson <alex.williamson@redhat.com>
---
 include/uapi/linux/vfio.h |    2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
