#### [PATCH 1/2] kvm: x86: Host feature SSBD doesn't imply guest feature SPEC_CTRL_SSBD
##### From: Jim Mattson <jmattson@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jim Mattson <jmattson@google.com>
X-Patchwork-Id: 11292003
Return-Path: <SRS0=Vqht=2E=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E7729930
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 14 Dec 2019 00:15:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id C5F7421655
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 14 Dec 2019 00:15:27 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="a4YYoxiE"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726690AbfLNAP0 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 13 Dec 2019 19:15:26 -0500
Received: from mail-pf1-f202.google.com ([209.85.210.202]:52540 "EHLO
        mail-pf1-f202.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726638AbfLNAP0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 13 Dec 2019 19:15:26 -0500
Received: by mail-pf1-f202.google.com with SMTP id j7so2530065pfa.19
        for <kvm@vger.kernel.org>; Fri, 13 Dec 2019 16:15:24 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=j3GWZOfDYJMyQxFqgM/P1MdaTU3tmLK8r2EVWlOwQg0=;
        b=a4YYoxiEQkOxlxpOaZQptugyg1b1VgiCniRH/OCNEjUZ1tWbiPuJCViJ407/9eD44D
         a9xBX3klgf/oj+GW6VONsYC6i6IHH0cBjJDcaKeS9PYi5pOgAk6gtTWUO4QYHUTCLXHc
         fMsC/gurdr8oAGhsn3pf1CcNlD3kcH+V2bG87zBEr3Kume0n4gaZWYWzZgBV6x/G92j8
         g4mOX5Z/d7jJfH4A0wVkYh/EgihPRNI/j3SccyiY7zvdKspd5jsJAS3pNM+tB+VOD3E2
         VQhjvXZ1MX5extxhMiPrU2k+Hdhk4dv8TjduB5bLe8b1nTK5H1Gn9hkOSIDkBUyBpOsR
         P7eA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=j3GWZOfDYJMyQxFqgM/P1MdaTU3tmLK8r2EVWlOwQg0=;
        b=K4a8Q+hqNTQPUMqor8+C7XJLbBg3zG6MX5i50UokHO0iYHT8o0G+vDI8cZKrYWYOMJ
         bTz3m1qTVmeDa4Kr5mIaJgM2RntJOksAmtHcWDrKeWoNT7++VHuGl5n2T333TxC0NBd6
         0ASfcH5TzPt56X/fzI5YKxGjc1nZXb7cCp3zNuUD5qOGL/BFONK4HYgNoxVRorfMdyIj
         qDAxH5LjfDgdqaSN5jsZXm1cEmCD7BRdci1qJqeldKlxxrWa7xeLRXl1iPqgdC15ZxOY
         pXhwxTzEr9UVHuzAmzqqpC9IuZ5WBhZorZZulexzTi1Zyh+R+lIbEeHR6yrgWrroE2+E
         3DHg==
X-Gm-Message-State: APjAAAWcmHPVbFzedSjkoPglrrgEBULL/BtiyTC3ksG3WIIsOZBQCLhi
        P/8OnmhBshC0/yBSrWjFXrMi5J/3bdNPtVlBH3NVjnUlOfT7ILpr4oT5CqcN86P2n/m93166aYD
        sjnIjjp1cI98EcsEVs1qWCd5Hsx1KRBjLG8jlvgzNpbovisYp+YfO/eBQm8aPoDE=
X-Google-Smtp-Source: 
 APXvYqz0PMBepM8X4lTtxtrURgx5ZRr8C0AwB73mfLoQPee57ZWzlBOegixTy14QNyXYBcMX1CoH/iIgknYm6g==
X-Received: by 2002:a63:4708:: with SMTP id u8mr2500295pga.391.1576282524350;
 Fri, 13 Dec 2019 16:15:24 -0800 (PST)
Date: Fri, 13 Dec 2019 16:15:15 -0800
Message-Id: <20191214001516.137526-1-jmattson@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.24.1.735.g03f4e72817-goog
Subject: [PATCH 1/2] kvm: x86: Host feature SSBD doesn't imply guest feature
 SPEC_CTRL_SSBD
From: Jim Mattson <jmattson@google.com>
To: kvm@vger.kernel.org
Cc: Jim Mattson <jmattson@google.com>, Jacob Xu <jacobhxu@google.com>,
        Peter Shier <pshier@google.com>,
        Paolo Bonzini <pbonzini@redhat.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The host reports support for the synthetic feature X86_FEATURE_SSBD
when any of the three following hardware features are set:
  CPUID.(EAX=7,ECX=0):EDX.SSBD[bit 31]
  CPUID.80000008H:EBX.AMD_SSBD[bit 24]
  CPUID.80000008H:EBX.VIRT_SSBD[bit 25]

Either of the first two hardware features implies the existence of the
IA32_SPEC_CTRL MSR, but CPUID.80000008H:EBX.VIRT_SSBD[bit 25] does
not. Therefore, CPUID.(EAX=7,ECX=0):EDX.SSBD[bit 31] should only be
set in the guest if CPUID.(EAX=7,ECX=0):EDX.SSBD[bit 31] or
CPUID.80000008H:EBX.AMD_SSBD[bit 24] is set on the host.

Fixes: 0c54914d0c52a ("KVM: x86: use Intel speculation bugs and features as derived in generic x86 code")
Signed-off-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Jacob Xu <jacobhxu@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/cpuid.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [PATCH v11 23/25] mm/gup: track FOLL_PIN pages
##### From: John Hubbard <jhubbard@nvidia.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: John Hubbard <jhubbard@nvidia.com>
X-Patchwork-Id: 11292107
Return-Path: <SRS0=Vqht=2E=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7E27C18B6
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 14 Dec 2019 03:26:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4CE5D206EE
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 14 Dec 2019 03:26:45 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=nvidia.com header.i=@nvidia.com
 header.b="WG0j9MlZ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726777AbfLND0c (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 13 Dec 2019 22:26:32 -0500
Received: from hqnvemgate26.nvidia.com ([216.228.121.65]:4644 "EHLO
        hqnvemgate26.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726757AbfLND0c (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 13 Dec 2019 22:26:32 -0500
Received: from hqpgpgate101.nvidia.com (Not Verified[216.228.121.13]) by
 hqnvemgate26.nvidia.com (using TLS: TLSv1.2, DES-CBC3-SHA)
        id <B5df456580000>; Fri, 13 Dec 2019 19:26:16 -0800
Received: from hqmail.nvidia.com ([172.20.161.6])
  by hqpgpgate101.nvidia.com (PGP Universal service);
  Fri, 13 Dec 2019 19:26:24 -0800
X-PGP-Universal: processed;
        by hqpgpgate101.nvidia.com on Fri, 13 Dec 2019 19:26:24 -0800
Received: from HQMAIL109.nvidia.com (172.20.187.15) by HQMAIL107.nvidia.com
 (172.20.187.13) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Sat, 14 Dec
 2019 03:26:23 +0000
Received: from hqnvemgw03.nvidia.com (10.124.88.68) by HQMAIL109.nvidia.com
 (172.20.187.15) with Microsoft SMTP Server (TLS) id 15.0.1473.3 via Frontend
 Transport; Sat, 14 Dec 2019 03:26:23 +0000
Received: from blueforge.nvidia.com (Not Verified[10.110.48.28]) by
 hqnvemgw03.nvidia.com with Trustwave SEG (v7,5,8,10121)
        id <B5df4565f0000>; Fri, 13 Dec 2019 19:26:23 -0800
From: John Hubbard <jhubbard@nvidia.com>
To: Andrew Morton <akpm@linux-foundation.org>
CC: Al Viro <viro@zeniv.linux.org.uk>,
 Alex Williamson <alex.williamson@redhat.com>,
 Benjamin Herrenschmidt <benh@kernel.crashing.org>, =?utf-8?b?QmrDtnJuIFQ=?=
	=?utf-8?b?w7ZwZWw=?= <bjorn.topel@intel.com>,
 Christoph Hellwig <hch@infradead.org>,
 Dan Williams <dan.j.williams@intel.com>, Daniel Vetter <daniel@ffwll.ch>,
 Dave Chinner <david@fromorbit.com>, David Airlie <airlied@linux.ie>,
 "David S . Miller" <davem@davemloft.net>, Ira Weiny <ira.weiny@intel.com>,
 Jan Kara <jack@suse.cz>, Jason Gunthorpe <jgg@ziepe.ca>,
 Jens Axboe <axboe@kernel.dk>, Jonathan Corbet <corbet@lwn.net>,
	=?utf-8?b?SsOpcsO0bWUgR2xpc3Nl?= <jglisse@redhat.com>,
 Magnus Karlsson <magnus.karlsson@intel.com>,
 Mauro Carvalho Chehab <mchehab@kernel.org>,
 Michael Ellerman <mpe@ellerman.id.au>, Michal Hocko <mhocko@suse.com>,
 Mike Kravetz <mike.kravetz@oracle.com>, Paul Mackerras <paulus@samba.org>,
 Shuah Khan <shuah@kernel.org>, Vlastimil Babka <vbabka@suse.cz>,
 <bpf@vger.kernel.org>, <dri-devel@lists.freedesktop.org>,
 <kvm@vger.kernel.org>, <linux-block@vger.kernel.org>,
 <linux-doc@vger.kernel.org>, <linux-fsdevel@vger.kernel.org>,
 <linux-kselftest@vger.kernel.org>, <linux-media@vger.kernel.org>,
 <linux-rdma@vger.kernel.org>, <linuxppc-dev@lists.ozlabs.org>,
 <netdev@vger.kernel.org>, <linux-mm@kvack.org>,
 LKML <linux-kernel@vger.kernel.org>, John Hubbard <jhubbard@nvidia.com>,
 "Kirill A . Shutemov" <kirill.shutemov@linux.intel.com>
Subject: [PATCH v11 23/25] mm/gup: track FOLL_PIN pages
Date: Fri, 13 Dec 2019 19:26:17 -0800
Message-ID: <20191214032617.1670759-1-jhubbard@nvidia.com>
X-Mailer: git-send-email 2.24.0
In-Reply-To: <20191212101741.GD10065@quack2.suse.cz>
References: <20191212101741.GD10065@quack2.suse.cz>
MIME-Version: 1.0
X-NVConfidentiality: public
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1576293976; bh=FWLx+gxsfuOtztyFqCn2BrgEGx3+6Ho7wvF61tReGAs=;
        h=X-PGP-Universal:From:To:CC:Subject:Date:Message-ID:X-Mailer:
         In-Reply-To:References:MIME-Version:X-NVConfidentiality:
         Content-Type:Content-Transfer-Encoding;
        b=WG0j9MlZSjr9ZI+XBaDA8nUAtPylsXvCcYofxMFrJJsgB++b+lsbqUzxLXBB3olN3
         9Ft1jS1einleJz21GidQ1VYOX8BFmNBFS+Z9FE1W3El3mCZk0hHUrEGc7RdCaEZ9mp
         B53HALTuEmfRkkyolY1GPi4P+8b8WNYdqMDD9u3sIiODg5xDBhMPGsZk6oTHmgbj5/
         SHkDdS9hUEkn36q/WHbt2SmG6ABpe2RCIePZjYy4UZeOjtFcBivYWbFy35Hrv1yydD
         7wOzfuBEla2W09p/nJQxjYimQRqlFFloQVzp4oxaHYNIK3L9KqH/OL5FGF0hwrK5Qd
         9ywVBlFQkUCKA==
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add tracking of pages that were pinned via FOLL_PIN.

As mentioned in the FOLL_PIN documentation, callers who effectively set
FOLL_PIN are required to ultimately free such pages via unpin_user_page().
The effect is similar to FOLL_GET, and may be thought of as "FOLL_GET
for DIO and/or RDMA use".

Pages that have been pinned via FOLL_PIN are identifiable via a
new function call:

   bool page_dma_pinned(struct page *page);

What to do in response to encountering such a page, is left to later
patchsets. There is discussion about this in [1], [2], and [3].

This also changes a BUG_ON(), to a WARN_ON(), in follow_page_mask().

[1] Some slow progress on get_user_pages() (Apr 2, 2019):
    https://lwn.net/Articles/784574/
[2] DMA and get_user_pages() (LPC: Dec 12, 2018):
    https://lwn.net/Articles/774411/
[3] The trouble with get_user_pages() (Apr 30, 2018):
    https://lwn.net/Articles/753027/

Suggested-by: Jan Kara <jack@suse.cz>
Suggested-by: Jérôme Glisse <jglisse@redhat.com>
Cc: Kirill A. Shutemov <kirill.shutemov@linux.intel.com>
Signed-off-by: John Hubbard <jhubbard@nvidia.com>
---

Hi Jan,

This should address all of your comments for patch 23!

thanks,
John Hubbard
NVIDIA

 Documentation/core-api/pin_user_pages.rst |   2 +-
 include/linux/mm.h                        |  83 ++++-
 include/linux/mmzone.h                    |   2 +
 include/linux/page_ref.h                  |  10 +
 mm/gup.c                                  | 409 +++++++++++++++++-----
 mm/huge_memory.c                          |  28 +-
 mm/hugetlb.c                              |  38 +-
 mm/vmstat.c                               |   2 +
 8 files changed, 438 insertions(+), 136 deletions(-)

```
#### [PATCH] KVM: nVMX: WARN on failure to set IA32_PERF_GLOBAL_CTRLFrom: Oliver Upton <oupton@google.com>
##### From: Oliver Upton <oupton@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Oliver Upton <oupton@google.com>
X-Patchwork-Id: 11292055
Return-Path: <SRS0=Vqht=2E=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9F4D614B7
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 14 Dec 2019 00:34:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7C4AE21655
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 14 Dec 2019 00:34:12 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="dGlbP5YJ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726735AbfLNAeL (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 13 Dec 2019 19:34:11 -0500
Received: from mail-pj1-f73.google.com ([209.85.216.73]:45892 "EHLO
        mail-pj1-f73.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726590AbfLNAeL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 13 Dec 2019 19:34:11 -0500
Received: by mail-pj1-f73.google.com with SMTP id f62so640368pjg.12
        for <kvm@vger.kernel.org>; Fri, 13 Dec 2019 16:34:09 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=zK9Y4nx0Rj/ARKOrR+GneC6HR8RpVxfAwxr1k/suMxQ=;
        b=dGlbP5YJCTlQwkz63/EM/Xh64ZL03NpqjvX4hLy0TyEAL1uzjNi0qhjL9/ZAzpYuSW
         uvs2j5rmZetl8F7/qNmL62ho2BCQKbUjK68bbhcomU7u/4gfypDF1Mo/mIYGu71weaLJ
         8nmWzaJUnt5TdKncGrefEoNuAGR3ezD1EeOc9ofzmSAlnXNvWQIXaTxRHnyADkoxsCPv
         plVvl/9/7RURTAZrxkSQrEHPKtJP8qBc06MCOatg5CNdEyWC3v3k0eckOkErOlO0Zhpy
         kTwxlNrqugvyjkXglZ4ZOlWeURaIcRjvMvxqhPDD9i95ZaqQ9IJ/kLIVan4OhvKjzVWh
         cjDQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=zK9Y4nx0Rj/ARKOrR+GneC6HR8RpVxfAwxr1k/suMxQ=;
        b=laqk1lCTrP+gRv7uz0iSfno+0cLqaK4pDeTdyWF/rjtZPATS5qbroWbvttHkN++JmD
         Qs0y4jFNeRfcTg1NigYf9s99Dj1QSSAoIJQQinIoFsdQ9rQtIo31D+Vd1oAeLuNxYyhk
         M4pqmuDU0NwuV/9NiP17LtKhrsWwHx5AdVlRJr4FZA4mcNBdeixmfGLuCeZD+0SMiJvB
         azfHQKtxl+hY7+ohEPuuVIoNhFb2AUAK/SAYY2ploCLwX2PNVdg7RZpVSLzlQe4v/jRe
         9BQrGunXp2aIXi3dXspOlByOEyzuPQ6OsJfEnyGUl3ZV7TEU0jZGInEyqHMjZQ9abWvN
         dTTQ==
X-Gm-Message-State: APjAAAW9aq2Zutu93c33ndsB8qqnNXdKLMqRf/Jg3N5HY8o19aiA0cvb
        wJZxtaImtezPaqJcWPNRnw9ooomcrCqG9ao+jtLVUgFQIvRUyVSSSx857FXHEBy5RjOfmTbfrnp
        2daHdY2ROB/kz+qkKyhoB0+KPy+q9q099BStjjqUaoweB0Q1lKbpyqKgK2Q==
X-Google-Smtp-Source: 
 APXvYqwvK+qjeL33M1SlGRaGvZbj7HIQN/w09HixIxWeFsSObMPL1SVMYciHFve4t597E/WLHS9zdvPPvrE=
X-Received: by 2002:a65:6842:: with SMTP id q2mr2676955pgt.345.1576283649114;
 Fri, 13 Dec 2019 16:34:09 -0800 (PST)
Date: Fri, 13 Dec 2019 16:33:58 -0800
Message-Id: <20191214003358.169496-1-oupton@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.24.1.735.g03f4e72817-goog
Subject: [PATCH] KVM: nVMX: WARN on failure to set IA32_PERF_GLOBAL_CTRL
From: Oliver Upton <oupton@google.com>
To: kvm@vger.kernel.org
Cc: Oliver Upton <oupton@google.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Paolo Bonzini <pbonzini@redhat.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Writes to MSR_CORE_PERF_GLOBAL_CONTROL should never fail if the VM-exit
and VM-entry controls are exposed to L1. Promote the checks to perform a
full WARN if kvm_set_msr() fails and remove the now unused macro
SET_MSR_OR_WARN().

Suggested-by: Sean Christopherson <sean.j.christopherson@intel.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Oliver Upton <oupton@google.com>
---
 arch/x86/kvm/vmx/nested.c | 18 ++++--------------
 1 file changed, 4 insertions(+), 14 deletions(-)

```
#### [PATCH] KVM: vmx: delete meaningless nested_vmx_prepare_msr_bitmap() declaration
##### From: linmiaohe <linmiaohe@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: linmiaohe <linmiaohe@huawei.com>
X-Patchwork-Id: 11292121
Return-Path: <SRS0=Vqht=2E=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 41F1814B7
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 14 Dec 2019 06:49:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1B481206DA
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 14 Dec 2019 06:49:45 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725871AbfLNGtL (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 14 Dec 2019 01:49:11 -0500
Received: from szxga04-in.huawei.com ([45.249.212.190]:7688 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1725372AbfLNGtK (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 14 Dec 2019 01:49:10 -0500
Received: from DGGEMS402-HUB.china.huawei.com (unknown [172.30.72.59])
        by Forcepoint Email with ESMTP id DC6962319C750067A1EF;
        Sat, 14 Dec 2019 14:49:07 +0800 (CST)
Received: from huawei.com (10.175.105.18) by DGGEMS402-HUB.china.huawei.com
 (10.3.19.202) with Microsoft SMTP Server id 14.3.439.0; Sat, 14 Dec 2019
 14:48:58 +0800
From: linmiaohe <linmiaohe@huawei.com>
To: <pbonzini@redhat.com>, <rkrcmar@redhat.com>,
        <sean.j.christopherson@intel.com>, <vkuznets@redhat.com>,
        <wanpengli@tencent.com>, <jmattson@google.com>, <joro@8bytes.org>,
        <tglx@linutronix.de>, <mingo@redhat.com>, <bp@alien8.de>,
        <hpa@zytor.com>
CC: <linmiaohe@huawei.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <x86@kernel.org>
Subject: [PATCH] KVM: vmx: delete meaningless nested_vmx_prepare_msr_bitmap()
 declaration
Date: Sat, 14 Dec 2019 14:48:45 +0800
Message-ID: <1576306125-18843-1-git-send-email-linmiaohe@huawei.com>
X-Mailer: git-send-email 1.8.3.1
MIME-Version: 1.0
X-Originating-IP: [10.175.105.18]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Miaohe Lin <linmiaohe@huawei.com>

The function nested_vmx_prepare_msr_bitmap() declaration is below its
implementation. So this is meaningless and should be removed.

Signed-off-by: Miaohe Lin <linmiaohe@huawei.com>
---
 arch/x86/kvm/vmx/nested.c | 3 ---
 1 file changed, 3 deletions(-)

```
#### [PATCH 1/8] hw/arm/nrf51_soc: Use memory_region_add_subregion() when priority is 0
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
 <philmd@redhat.com>
X-Patchwork-Id: 11292311
Return-Path: <SRS0=Vqht=2E=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 108A6112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 14 Dec 2019 15:56:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E18D82465B
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 14 Dec 2019 15:56:52 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="MsdGxiOA"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726960AbfLNP4w (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 14 Dec 2019 10:56:52 -0500
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:31246 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726944AbfLNP4v (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 14 Dec 2019 10:56:51 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1576339011;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=IiMSoFUEZseoMxLw1sAmT/IUeieWX2EUqAxBTC+j+po=;
        b=MsdGxiOAuI3TpMWumBs3S87MFcocJUweZ9R89UjHZCvMI47GTrDoCLMf1QPRN3LpvJ+vqw
        FFErJNSfKPB3l1murZou81w55rHq/LhiuLf1BnoI+cQyOzyvd9dtlOyU9CCXydN1VF+ZOB
        q5YYejji8Fez7sb5GT3LpJl10HlvCjE=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-5-8GfcR2qbM7asPJU8NqZDDA-1; Sat, 14 Dec 2019 10:56:49 -0500
X-MC-Unique: 8GfcR2qbM7asPJU8NqZDDA-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 62B71107ACC4;
        Sat, 14 Dec 2019 15:56:47 +0000 (UTC)
Received: from x1w.redhat.com (ovpn-205-147.brq.redhat.com [10.40.205.147])
        by smtp.corp.redhat.com (Postfix) with ESMTPS id 4C0F166A1A;
        Sat, 14 Dec 2019 15:56:32 +0000 (UTC)
From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>
To: qemu-devel@nongnu.org
Cc: Peter Maydell <peter.maydell@linaro.org>,
 Andrew Baumann <Andrew.Baumann@microsoft.com>,
 Aurelien Jarno <aurelien@aurel32.net>, kvm@vger.kernel.org,
 Alex Williamson <alex.williamson@redhat.com>,
 Aleksandar Markovic <amarkovic@wavecomp.com>, Joel Stanley <joel@jms.id.au>,
 qemu-arm@nongnu.org, Marcelo Tosatti <mtosatti@redhat.com>,
 Alistair Francis <alistair@alistair23.me>,
 "Michael S. Tsirkin" <mst@redhat.com>, Eduardo Habkost <ehabkost@redhat.com>,
 Richard Henderson <rth@twiddle.net>,
 Aleksandar Rikalo <aleksandar.rikalo@rt-rk.com>, =?utf-8?q?Philippe_Mathieu?=
	=?utf-8?q?-Daud=C3=A9?= <philmd@redhat.com>,
 Paul Burton <pburton@wavecomp.com>,
 Marcel Apfelbaum <marcel.apfelbaum@gmail.com>,
 "Edgar E. Iglesias" <edgar.iglesias@gmail.com>,
 Paolo Bonzini <pbonzini@redhat.com>
Subject: [PATCH 1/8] hw/arm/nrf51_soc: Use memory_region_add_subregion() when
 priority is 0
Date: Sat, 14 Dec 2019 16:56:07 +0100
Message-Id: <20191214155614.19004-2-philmd@redhat.com>
In-Reply-To: <20191214155614.19004-1-philmd@redhat.com>
References: <20191214155614.19004-1-philmd@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

It is pointless to overlap a memory subregion with priority 0.
Use the simpler memory_region_add_subregion() function.

This patch was produced with the following spatch script:

    @@
    expression region;
    expression offset;
    expression subregion;
    @@
    -memory_region_add_subregion_overlap(region, offset, subregion, 0)
    +memory_region_add_subregion(region, offset, subregion)

Signed-off-by: Philippe Mathieu-Daudé <philmd@redhat.com>
---
 hw/arm/nrf51_soc.c | 14 +++++++-------
 1 file changed, 7 insertions(+), 7 deletions(-)

```
#### [PATCH v2] kvm: x86: Add logical CPU to KVM_EXIT_FAIL_ENTRY infoFrom: Jim Mattson <jmattson@google.com>
##### From: Jim Mattson <jmattson@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jim Mattson <jmattson@google.com>
X-Patchwork-Id: 11292007
Return-Path: <SRS0=Vqht=2E=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1E3D56C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 14 Dec 2019 00:20:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E71612253D
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 14 Dec 2019 00:20:19 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="BKk1ZzWN"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726678AbfLNAUT (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 13 Dec 2019 19:20:19 -0500
Received: from mail-pl1-f202.google.com ([209.85.214.202]:42496 "EHLO
        mail-pl1-f202.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726590AbfLNAUS (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 13 Dec 2019 19:20:18 -0500
Received: by mail-pl1-f202.google.com with SMTP id b3so2140878plr.9
        for <kvm@vger.kernel.org>; Fri, 13 Dec 2019 16:20:18 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=iYjRSLM/149x9A6g7cj2JAFrBIGaPeMK4MkKkb0OcHo=;
        b=BKk1ZzWN7AJEO0OwzObETGLBBPvFRcZkvdQAgsOlQF6/6vj87G9B+NA0fDDKcPBTqp
         Ui8YwSbvJcTl05rToJ2R2ulHd3xgTv7qPkVoXlFf7BA0e8bLDfibF253t7VZHZuUrWO+
         cWYhVt6MoaAhu+kOZd+A+eBGHHtDXvJ8hBIjJ6wATiMoSZTQ9RDd6DRQ6aiRwfSZszw3
         9eZsJCKm5TDZbX5H3ZbWRB/jd0s9j6MBqm/H6RMEyh5wCPfINNX4of+7CUdrnDooBu9j
         /Ibncbm1Jd74xU3DAZohldT1S5dvChKWKCQPmXA91qk8Z4oorfCxcoLKYevJJe250+M6
         59dA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=iYjRSLM/149x9A6g7cj2JAFrBIGaPeMK4MkKkb0OcHo=;
        b=LHKvZifpjrYy+L4CphLu8GcO+WDkTVWZbT1KamgKy9Qu5rq6pXwj99o5CAlDH2UBY3
         u57kHb1KjCG9RirvA++RzrI5ZN68oxHshCqV5AWiQBGIiP82la7FXOrtVlpPkHAWaS8T
         tj/gYRy5w9/gnBrfSN+qBZ8AJa6FAwl9KqDtAAyMTKTb7+/SLpegDy3RpsyBkdwVYmrl
         W/2euc/ikZ2z7KVOXNymz2k6y69wW/Db+0nGUXrh6DvO9125TwxISWGkfRhvCGqlhfb5
         UmurtRGJhA33AOaM7+ZHc61Y1DiknVW+UZ1V3Vf2AcnJBuJTZDKDPD8U7+vGB9UdJF+D
         We9Q==
X-Gm-Message-State: APjAAAU2X8SH9/BwtwcGkEYx4cjajJ+G7EexPW/yQEK6Dffl5cg1Y2mp
        HDSAa5oQ5VYTmoFIQy7QypoZtq3OThY7CokBw7VsO+lxnF6rmloyzSTOnhIMf8ilut3f0nRFUXd
        +/jw9Yms8YI7PsQ9FjH0er5wjgHW7xnK42Pr6Jr8HySShEQc04RCX6vExstCxTTU=
X-Google-Smtp-Source: 
 APXvYqxmR2lJ2RJ6lXNZWujx4zLl7bYEr5vocTMscxqqRqxNopWUxCdH3bm5nZQekevV0yC/N7d6+F8GjcoXUQ==
X-Received: by 2002:a63:28c7:: with SMTP id
 o190mr2503762pgo.394.1576282817946;
 Fri, 13 Dec 2019 16:20:17 -0800 (PST)
Date: Fri, 13 Dec 2019 16:20:14 -0800
Message-Id: <20191214002014.144430-1-jmattson@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.24.1.735.g03f4e72817-goog
Subject: [PATCH v2] kvm: x86: Add logical CPU to KVM_EXIT_FAIL_ENTRY info
From: Jim Mattson <jmattson@google.com>
To: kvm@vger.kernel.org
Cc: Jim Mattson <jmattson@google.com>,
        Oliver Upton <oupton@google.com>,
        Liran Alon <liran.alon@oracle.com>,
        Paolo Bonzini <pbonzini@redhat.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

More often than not, a failed VM-entry in a production environment is
the result of a defective CPU (at least, insofar as Intel x86 is
concerned). To aid in identifying the bad hardware, add the logical
CPU to the information provided to userspace on a KVM exit with reason
KVM_EXIT_FAIL_ENTRY. The presence of this additional information is
indicated by a new capability, KVM_CAP_FAILED_ENTRY_CPU.

Signed-off-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Oliver Upton <oupton@google.com>
Cc: Liran Alon <liran.alon@oracle.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Liran Alon <liran.alon@oracle.com>
---
 Documentation/virt/kvm/api.txt | 1 +
 arch/x86/kvm/svm.c             | 1 +
 arch/x86/kvm/vmx/vmx.c         | 2 ++
 arch/x86/kvm/x86.c             | 1 +
 include/uapi/linux/kvm.h       | 2 ++
 5 files changed, 7 insertions(+)

```
