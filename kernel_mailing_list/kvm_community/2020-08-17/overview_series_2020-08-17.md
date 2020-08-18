#### [PATCH 1/2] Add new flush_iotlb_range and handle freelists when using iommu_unmap_fast
##### From: Tom Murphy <murphyt7@tcd.ie>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tom Murphy <murphyt7@tcd.ie>
X-Patchwork-Id: 11719195
Return-Path: <SRS0=mOyg=B3=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 176C9618
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Aug 2020 21:20:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DA0112072E
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Aug 2020 21:20:09 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=tcd-ie.20150623.gappssmtp.com
 header.i=@tcd-ie.20150623.gappssmtp.com header.b="seHBtxOq"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728197AbgHQVUG (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 17 Aug 2020 17:20:06 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:60348 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728169AbgHQVT7 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 17 Aug 2020 17:19:59 -0400
Received: from mail-pf1-x444.google.com (mail-pf1-x444.google.com
 [IPv6:2607:f8b0:4864:20::444])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 0DDEAC061345
        for <kvm@vger.kernel.org>; Mon, 17 Aug 2020 14:19:59 -0700 (PDT)
Received: by mail-pf1-x444.google.com with SMTP id m71so8874140pfd.1
        for <kvm@vger.kernel.org>; Mon, 17 Aug 2020 14:19:59 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=tcd-ie.20150623.gappssmtp.com; s=20150623;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=lzbssZSqWsDNjNzFL+N6OlLzKZWUkpB6XZ73g9026HE=;
        b=seHBtxOq0Hta3K2MkirUnvlZcptzkwbCxZ63S5NIzjY267CJ+pbWwr6wWdNxaPuTAd
         snfmmSEMSsEbs6rYWICwJ4gsFjWvaAoly/Szwaq2OrQIN6Df9FJSXNRlGoA9Nseesym0
         kzB/5xQJG3xLBRyGaAdkjrCDr64yQdhzgAOIimrSa8CLqIcjL2tRSCPa5YsM40jQrIB1
         PbC65LOyRllKXCL/f2DSNxf6SVPcFNawf5ptdZtUu429Wlcajhgl2dbkPoPoYb7c912t
         ivV2GS7rfc4739T4DEG1CB4kOsUtVX+thpcQX8SQ0CmOBq3iUkQuCupjJu7iOADLRfr+
         2Qjw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=lzbssZSqWsDNjNzFL+N6OlLzKZWUkpB6XZ73g9026HE=;
        b=ZwGTS7H4C0Ajn9lpGXDSORcnmByJZISDgEWO+V/lxs3xAE+MOJJy0FSFxJxYNyNkNc
         ohNFs6nBrtdl7Y97XLrwwAU+EvPQUkOW7UTURwIxV/Qkvx+XFHKkWrUlGauw/8aDNQPC
         eaJ5IOcK3WUgMhLexGEHfO/sWwFcrkCEExacd2dpzN+/KcVzMRQ6qsVOig0G9oce+Pmi
         /TLdiyYNry/AB8KC0eT9XcByP/dssqmhpxsa51mjF8LnX75axOUurGfTkr3C5GL/wy/5
         gFXGa6QMwqDYdlS4R/jAT5DcfIwo6IOGjqZSkBozeyZN8c4nxZRmk+9ZHgZQ9YWO65WP
         97+A==
X-Gm-Message-State: AOAM531jnUX1l+TFCa1XipC60MpzYA459wLbYVkfgu8Dp8KfwLGq0GKv
        UAY5cSzhvRjYGf4T8yTWL+ixSA==
X-Google-Smtp-Source: 
 ABdhPJy45z2aeZf1aCXcrEaUNgkOwdCtNG7KGYJi9PRq9pB353rv5iukS0xromsVTg0AyiekM1EDAA==
X-Received: by 2002:a62:8881:: with SMTP id
 l123mr12296930pfd.186.1597699198052;
        Mon, 17 Aug 2020 14:19:58 -0700 (PDT)
Received: from localhost.localdomain (S0106ac17c8c0ce82.vc.shawcable.net.
 [24.87.214.6])
        by smtp.googlemail.com with ESMTPSA id
 q10sm20733468pfs.75.2020.08.17.14.19.56
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 17 Aug 2020 14:19:57 -0700 (PDT)
From: Tom Murphy <murphyt7@tcd.ie>
To: iommu@lists.linux-foundation.org
Cc: Tom Murphy <murphyt7@tcd.ie>, Joerg Roedel <joro@8bytes.org>,
        Will Deacon <will@kernel.org>,
        Robin Murphy <robin.murphy@arm.com>,
        Marek Szyprowski <m.szyprowski@samsung.com>,
        Kukjin Kim <kgene@kernel.org>,
        Krzysztof Kozlowski <krzk@kernel.org>,
        David Woodhouse <dwmw2@infradead.org>,
        Lu Baolu <baolu.lu@linux.intel.com>,
        Andy Gross <agross@kernel.org>,
        Bjorn Andersson <bjorn.andersson@linaro.org>,
        Matthias Brugger <matthias.bgg@gmail.com>,
        Rob Clark <robdclark@gmail.com>,
        Heiko Stuebner <heiko@sntech.de>,
        Matthew Rosato <mjrosato@linux.ibm.com>,
        Gerald Schaefer <gerald.schaefer@linux.ibm.com>,
        Maxime Ripard <mripard@kernel.org>,
        Chen-Yu Tsai <wens@csie.org>,
        Thierry Reding <thierry.reding@gmail.com>,
        Jonathan Hunter <jonathanh@nvidia.com>,
        Jean-Philippe Brucker <jean-philippe@linaro.org>,
        Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        linux-kernel@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
        linux-samsung-soc@vger.kernel.org, linux-arm-msm@vger.kernel.org,
        linux-mediatek@lists.infradead.org,
        linux-rockchip@lists.infradead.org, linux-s390@vger.kernel.org,
        linux-tegra@vger.kernel.org,
        virtualization@lists.linux-foundation.org, kvm@vger.kernel.org
Subject: [PATCH 1/2] Add new flush_iotlb_range and handle freelists when using
 iommu_unmap_fast
Date: Mon, 17 Aug 2020 22:19:49 +0100
Message-Id: <20200817211951.14794-1-murphyt7@tcd.ie>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add a flush_iotlb_range to allow flushing of an iova range instead of a
full flush in the dma-iommu path.

Allow the iommu_unmap_fast to return newly freed page table pages and
pass the freelist to queue_iova in the dma-iommu ops path.

This patch is useful for iommu drivers (in this case the intel iommu
driver) which need to wait for the ioTLB to be flushed before newly
free/unmapped page table pages can be freed. This way we can still batch
ioTLB free operations and handle the freelists.

Signed-off-by: Tom Murphy <murphyt7@tcd.ie>
---
 drivers/iommu/amd/iommu.c       | 14 ++++++++-
 drivers/iommu/arm-smmu-v3.c     |  3 +-
 drivers/iommu/arm-smmu.c        |  3 +-
 drivers/iommu/dma-iommu.c       | 45 ++++++++++++++++++++-------
 drivers/iommu/exynos-iommu.c    |  3 +-
 drivers/iommu/intel/iommu.c     | 54 +++++++++++++++++++++------------
 drivers/iommu/iommu.c           | 25 +++++++++++----
 drivers/iommu/ipmmu-vmsa.c      |  3 +-
 drivers/iommu/msm_iommu.c       |  3 +-
 drivers/iommu/mtk_iommu.c       |  3 +-
 drivers/iommu/omap-iommu.c      |  3 +-
 drivers/iommu/qcom_iommu.c      |  3 +-
 drivers/iommu/rockchip-iommu.c  |  3 +-
 drivers/iommu/s390-iommu.c      |  3 +-
 drivers/iommu/sun50i-iommu.c    |  3 +-
 drivers/iommu/tegra-gart.c      |  3 +-
 drivers/iommu/tegra-smmu.c      |  3 +-
 drivers/iommu/virtio-iommu.c    |  3 +-
 drivers/vfio/vfio_iommu_type1.c |  2 +-
 include/linux/iommu.h           | 21 +++++++++++--
 20 files changed, 148 insertions(+), 55 deletions(-)

```
#### [PATCH 1/2] kvm: x86: Toggling CR4.PKE does not load PDPTEs in PAE mode
##### From: Jim Mattson <jmattson@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jim Mattson <jmattson@google.com>
X-Patchwork-Id: 11719053
Return-Path: <SRS0=mOyg=B3=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 98B65722
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Aug 2020 18:18:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7C44820738
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Aug 2020 18:18:38 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="r+Qpffn8"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2390418AbgHQSSc (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 17 Aug 2020 14:18:32 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:59944 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2390534AbgHQSRP (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 17 Aug 2020 14:17:15 -0400
Received: from mail-pf1-x44a.google.com (mail-pf1-x44a.google.com
 [IPv6:2607:f8b0:4864:20::44a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id E7697C061342
        for <kvm@vger.kernel.org>; Mon, 17 Aug 2020 11:17:14 -0700 (PDT)
Received: by mail-pf1-x44a.google.com with SMTP id z16so11237792pfq.7
        for <kvm@vger.kernel.org>; Mon, 17 Aug 2020 11:17:14 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=Q9Urp5Zg/ojVwCnBfwbevPtDZNDnY8XuunFzOx8DVIs=;
        b=r+Qpffn8N6PCB7loSsHOq1dt9znqP2KrseMok4tDGoPV+RB5L+0w6PlHpMv3qML/xG
         As3v2+PiRsirgzzoNjqseL1mrNEw6NzXKwZYcdO2lNI1Nm7qiyj3MzVpm8kxoDdOW4iJ
         Jt/DdUcJptkoQIjPTfxyE4/dnwIEv8iHE8z5uPrplXvcHEGbha89ZVpQHcjk0HdeDBZa
         0PMGK6vVUh+j+kaXkAEYEvVIkWiquHtuzM1PF32v5u+9t+MQ5sZ1jMZ/fog6moM5/dFd
         692B9nm9Y8+W12oHss00gfZZLAwTQOjG3SQGV1paCuxDrb1UH+YzLQvlie4rXSXK8vmm
         w+xw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=Q9Urp5Zg/ojVwCnBfwbevPtDZNDnY8XuunFzOx8DVIs=;
        b=fJ2kBqMfNMgP1gtWQq3J/y++nJFHevNY4JvPianydACQ9Pq6W8+GMPyae0kNfpC/JG
         3zawUXAKHy460vilqNqvvt9nkKIPRg4KzYKd0cDzDFMqyWJBootKlvxNPmtiwjEdpyLN
         njDD2btLQRbmatk5czldfmcdJo+hgh+SlApuOIDp2BuJACQpyZEkNAr54MlksDaTP5gd
         il4wa/fY7ml3+Tz3ISPdQruLz7Ph/6QJjER5Dh81f1Zo3ce3Nd74rdC6zi5ZlUo7o7oE
         a9ED4nwcHGKcmPaI6RSnO5qhlHloYZtgbaMpKcN70AoIi57ASbCaFr5nIDSVW1hZ73zz
         dw1A==
X-Gm-Message-State: AOAM532QU1wIjj8QkF+LJfAlS/b0lxdIFEPCBWBPba4yUIm5zGWF0eg4
        CGiEdYXgCccT4IUhpu1BiLZYQ0QgcZ8ZEhUNhy1MBWEWEEGOIG+Cbn902+CI201C1JOi8n5/FD5
        QIBM3SDpng+f0jG5GuQtlo5XfbipZJJZrdqW6gSMZL12Ctoq0XWMmQ4YtRL06734=
X-Google-Smtp-Source: 
 ABdhPJyqyBGxKNmVszoTSjP/mYizC+F5KdT0j7N/lvFmDir7y7UR79jV73CUsaUbYmrCwGaLpxknId+QZi4Exg==
X-Received: by 2002:aa7:8608:: with SMTP id p8mr11898432pfn.62.1597688233247;
 Mon, 17 Aug 2020 11:17:13 -0700 (PDT)
Date: Mon, 17 Aug 2020 11:16:54 -0700
Message-Id: <20200817181655.3716509-1-jmattson@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.28.0.220.ged08abb693-goog
Subject: [PATCH 1/2] kvm: x86: Toggling CR4.PKE does not load PDPTEs in PAE
 mode
From: Jim Mattson <jmattson@google.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Jim Mattson <jmattson@google.com>,
        Huaitong Han <huaitong.han@intel.com>,
        Peter Shier <pshier@google.com>,
        Oliver Upton <oupton@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

See the SDM, volume 3, section 4.4.1:

If PAE paging would be in use following an execution of MOV to CR0 or
MOV to CR4 (see Section 4.1.1) and the instruction is modifying any of
CR0.CD, CR0.NW, CR0.PG, CR4.PAE, CR4.PGE, CR4.PSE, or CR4.SMEP; then
the PDPTEs are loaded from the address in CR3.

Fixes: b9baba8614890 ("KVM, pkeys: expose CPUID/CR4 to guest")
Cc: Huaitong Han <huaitong.han@intel.com>
Signed-off-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
Reviewed-by: Oliver Upton <oupton@google.com>
---
 arch/x86/kvm/x86.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [RFC v2 1/2] KVM: VMX: Convert vcpu_vmx.exit_reason to a union
##### From: Chenyi Qiang <chenyi.qiang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Chenyi Qiang <chenyi.qiang@intel.com>
X-Patchwork-Id: 11716273
Return-Path: <SRS0=mOyg=B3=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 24202109B
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Aug 2020 01:43:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0B4432075D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Aug 2020 01:43:28 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726728AbgHQBnV (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 16 Aug 2020 21:43:21 -0400
Received: from mga11.intel.com ([192.55.52.93]:61654 "EHLO mga11.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726371AbgHQBnG (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 16 Aug 2020 21:43:06 -0400
IronPort-SDR: 
 Du6QqfsqWKRLP4bpGx4xyZPLjKQde65rsMGa9gXOPOSic//wgkdL35jjg+pXM22XSLbxSbMxOr
 lfGoJWtHmzBg==
X-IronPort-AV: E=McAfee;i="6000,8403,9715"; a="152267102"
X-IronPort-AV: E=Sophos;i="5.76,322,1592895600";
   d="scan'208";a="152267102"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga005.jf.intel.com ([10.7.209.41])
  by fmsmga102.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 16 Aug 2020 18:43:02 -0700
IronPort-SDR: 
 3uU5G+dZfvwT27kB3xNn2RmfasC5J8dMThnKx9av1xpoiYihCj2M4JpAWHLruQCQzPCURcndG1
 XoZCPRULshtw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.76,322,1592895600";
   d="scan'208";a="471258542"
Received: from chenyi-pc.sh.intel.com ([10.239.159.72])
  by orsmga005.jf.intel.com with ESMTP; 16 Aug 2020 18:42:58 -0700
From: Chenyi Qiang <chenyi.qiang@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Xiaoyao Li <xiaoyao.li@intel.com>
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [RFC v2 1/2] KVM: VMX: Convert vcpu_vmx.exit_reason to a union
Date: Mon, 17 Aug 2020 09:44:58 +0800
Message-Id: <20200817014459.28782-2-chenyi.qiang@intel.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200817014459.28782-1-chenyi.qiang@intel.com>
References: <20200817014459.28782-1-chenyi.qiang@intel.com>
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
#### [RESEND RFC v2 1/2] KVM: VMX: Convert vcpu_vmx.exit_reason to a union
##### From: Chenyi Qiang <chenyi.qiang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Chenyi Qiang <chenyi.qiang@intel.com>
X-Patchwork-Id: 11716377
Return-Path: <SRS0=mOyg=B3=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7CF8E109B
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Aug 2020 03:34:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 65D4F205CB
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Aug 2020 03:34:15 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727084AbgHQDeI (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 16 Aug 2020 23:34:08 -0400
Received: from mga04.intel.com ([192.55.52.120]:53823 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726385AbgHQDeG (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 16 Aug 2020 23:34:06 -0400
IronPort-SDR: 
 Egp6Pv4jqcArFm1yKEY3h8RnzbNhhK1lVB4m+G2pf1PLxj3UjwELFD2ftFB78JmCE759LNWvvi
 ytapLR/m4ZAA==
X-IronPort-AV: E=McAfee;i="6000,8403,9715"; a="152033207"
X-IronPort-AV: E=Sophos;i="5.76,322,1592895600";
   d="scan'208";a="152033207"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by fmsmga104.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 16 Aug 2020 20:34:05 -0700
IronPort-SDR: 
 C8zKo8TiMbHeszBHzsG1KItZkvhUJMa+cF+jmRAzwhDQamx7/P7GZ7Rp672JbSsyKIcKx3nr3z
 eTCEU36oyJiw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.76,322,1592895600";
   d="scan'208";a="400075242"
Received: from chenyi-pc.sh.intel.com ([10.239.159.72])
  by fmsmga001.fm.intel.com with ESMTP; 16 Aug 2020 20:34:03 -0700
From: Chenyi Qiang <chenyi.qiang@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Xiaoyao Li <xiaoyao.li@intel.com>
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [RESEND RFC v2 1/2] KVM: VMX: Convert vcpu_vmx.exit_reason to a union
Date: Mon, 17 Aug 2020 11:36:03 +0800
Message-Id: <20200817033604.5836-2-chenyi.qiang@intel.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200817033604.5836-1-chenyi.qiang@intel.com>
References: <20200817033604.5836-1-chenyi.qiang@intel.com>
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
#### [PATCH v7 01/18] nitro_enclaves: Add ioctl interface definition
##### From: Andra Paraschiv <andraprs@amazon.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andra Paraschiv <andraprs@amazon.com>
X-Patchwork-Id: 11718207
Return-Path: <SRS0=mOyg=B3=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BFF3B618
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Aug 2020 13:11:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9D2E72076E
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Aug 2020 13:11:00 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amazon.com header.i=@amazon.com
 header.b="h27dticx"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728530AbgHQNKz (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 17 Aug 2020 09:10:55 -0400
Received: from smtp-fw-9102.amazon.com ([207.171.184.29]:64672 "EHLO
        smtp-fw-9102.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728460AbgHQNKl (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 17 Aug 2020 09:10:41 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.com; i=@amazon.com; q=dns/txt; s=amazon201209;
  t=1597669839; x=1629205839;
  h=from:to:cc:subject:date:message-id:in-reply-to:
   references:mime-version:content-transfer-encoding;
  bh=V+LUw3hibO5Ygdlgwj4ZkmCdL6KQpUj7f8YNRNSNDaw=;
  b=h27dticxrcOlQ4wiXwo3WYYqh/xkE+vkLaVCFMfQOUw29MTeKEuFWWQD
   c4TpSLSWzkjxaeBB5S71nbPWxYKCMZe3D4zmxs3fCEkN9OX9f3SR0AZ0J
   y5YgRqwTpNSvbHEsaW+hP9Wf8ACCE9O3sZ/m7LO2e1ozN+z5/WT2L4mHA
   o=;
X-IronPort-AV: E=Sophos;i="5.76,322,1592870400";
   d="scan'208";a="68512624"
Received: from sea32-co-svc-lb4-vlan3.sea.corp.amazon.com (HELO
 email-inbound-relay-1d-2c665b5d.us-east-1.amazon.com) ([10.47.23.38])
  by smtp-border-fw-out-9102.sea19.amazon.com with ESMTP;
 17 Aug 2020 13:10:36 +0000
Received: from EX13MTAUEA002.ant.amazon.com
 (iad55-ws-svc-p15-lb9-vlan2.iad.amazon.com [10.40.159.162])
        by email-inbound-relay-1d-2c665b5d.us-east-1.amazon.com (Postfix) with
 ESMTPS id 8D04EA17EC;
        Mon, 17 Aug 2020 13:10:34 +0000 (UTC)
Received: from EX13D16EUB001.ant.amazon.com (10.43.166.28) by
 EX13MTAUEA002.ant.amazon.com (10.43.61.77) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Mon, 17 Aug 2020 13:10:33 +0000
Received: from 38f9d34ed3b1.ant.amazon.com (10.43.162.140) by
 EX13D16EUB001.ant.amazon.com (10.43.166.28) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Mon, 17 Aug 2020 13:10:23 +0000
From: Andra Paraschiv <andraprs@amazon.com>
To: linux-kernel <linux-kernel@vger.kernel.org>
CC: Anthony Liguori <aliguori@amazon.com>,
        Benjamin Herrenschmidt <benh@kernel.crashing.org>,
        Colm MacCarthaigh <colmmacc@amazon.com>,
        "David Duncan" <davdunc@amazon.com>,
        Bjoern Doebel <doebel@amazon.de>,
        "David Woodhouse" <dwmw@amazon.co.uk>,
        Frank van der Linden <fllinden@amazon.com>,
        Alexander Graf <graf@amazon.de>,
        Greg KH <gregkh@linuxfoundation.org>,
        "Karen Noel" <knoel@redhat.com>,
        Martin Pohlack <mpohlack@amazon.de>,
        Matt Wilson <msw@amazon.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Balbir Singh <sblbir@amazon.com>,
        Stefano Garzarella <sgarzare@redhat.com>,
        "Stefan Hajnoczi" <stefanha@redhat.com>,
        Stewart Smith <trawets@amazon.com>,
        "Uwe Dannowski" <uwed@amazon.de>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        kvm <kvm@vger.kernel.org>,
        ne-devel-upstream <ne-devel-upstream@amazon.com>,
        Andra Paraschiv <andraprs@amazon.com>
Subject: [PATCH v7 01/18] nitro_enclaves: Add ioctl interface definition
Date: Mon, 17 Aug 2020 16:09:46 +0300
Message-ID: <20200817131003.56650-2-andraprs@amazon.com>
X-Mailer: git-send-email 2.20.1 (Apple Git-117)
In-Reply-To: <20200817131003.56650-1-andraprs@amazon.com>
References: <20200817131003.56650-1-andraprs@amazon.com>
MIME-Version: 1.0
X-Originating-IP: [10.43.162.140]
X-ClientProxiedBy: EX13D16UWC003.ant.amazon.com (10.43.162.15) To
 EX13D16EUB001.ant.amazon.com (10.43.166.28)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The Nitro Enclaves driver handles the enclave lifetime management. This
includes enclave creation, termination and setting up its resources such
as memory and CPU.

An enclave runs alongside the VM that spawned it. It is abstracted as a
process running in the VM that launched it. The process interacts with
the NE driver, that exposes an ioctl interface for creating an enclave
and setting up its resources.

Signed-off-by: Alexandru Vasile <lexnv@amazon.com>
Signed-off-by: Andra Paraschiv <andraprs@amazon.com>
Reviewed-by: Alexander Graf <graf@amazon.com>
Reviewed-by: Stefan Hajnoczi <stefanha@redhat.com>
---
Changelog

v6 -> v7

* Clarify in the ioctls documentation that the return value is -1 and
  errno is set on failure.
* Update the error code value for NE_ERR_INVALID_MEM_REGION_SIZE as it
  gets in user space as value 25 (ENOTTY) instead of 515. Update the
  NE custom error codes values range to not be the same as the ones
  defined in include/linux/errno.h, although these are not propagated
  to user space.

v5 -> v6

* Fix typo in the description about the NE CPU pool.
* Update documentation to kernel-doc format.
* Remove the ioctl to query API version.

v4 -> v5

* Add more details about the ioctl calls usage e.g. error codes, file
  descriptors used.
* Update the ioctl to set an enclave vCPU to not return a file
  descriptor.
* Add specific NE error codes.

v3 -> v4

* Decouple NE ioctl interface from KVM API.
* Add NE API version and the corresponding ioctl call.
* Add enclave / image load flags options.

v2 -> v3

* Remove the GPL additional wording as SPDX-License-Identifier is
  already in place.

v1 -> v2

* Add ioctl for getting enclave image load metadata.
* Update NE_ENCLAVE_START ioctl name to NE_START_ENCLAVE.
* Add entry in Documentation/userspace-api/ioctl/ioctl-number.rst for NE
  ioctls.
* Update NE ioctls definition based on the updated ioctl range for major
  and minor.
---
 .../userspace-api/ioctl/ioctl-number.rst      |   5 +-
 include/linux/nitro_enclaves.h                |  11 +
 include/uapi/linux/nitro_enclaves.h           | 337 ++++++++++++++++++
 3 files changed, 352 insertions(+), 1 deletion(-)
 create mode 100644 include/linux/nitro_enclaves.h
 create mode 100644 include/uapi/linux/nitro_enclaves.h

```
#### [PATCH 1/2] clocksource: arm_arch_timer: Simplify and fix count reader code logic
##### From: Keqian Zhu <zhukeqian1@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Keqian Zhu <zhukeqian1@huawei.com>
X-Patchwork-Id: 11718129
Return-Path: <SRS0=mOyg=B3=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 603BF138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Aug 2020 12:24:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4CC802075B
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Aug 2020 12:24:36 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727863AbgHQMYb (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 17 Aug 2020 08:24:31 -0400
Received: from szxga07-in.huawei.com ([45.249.212.35]:49960 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726151AbgHQMYa (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 17 Aug 2020 08:24:30 -0400
Received: from DGGEMS401-HUB.china.huawei.com (unknown [172.30.72.59])
        by Forcepoint Email with ESMTP id 6AFAA26378CE36048E93;
        Mon, 17 Aug 2020 20:24:25 +0800 (CST)
Received: from DESKTOP-5IS4806.china.huawei.com (10.174.187.22) by
 DGGEMS401-HUB.china.huawei.com (10.3.19.201) with Microsoft SMTP Server id
 14.3.487.0; Mon, 17 Aug 2020 20:24:19 +0800
From: Keqian Zhu <zhukeqian1@huawei.com>
To: <linux-kernel@vger.kernel.org>,
        <linux-arm-kernel@lists.infradead.org>,
        <kvmarm@lists.cs.columbia.edu>, <kvm@vger.kernel.org>
CC: Marc Zyngier <maz@kernel.org>, Steven Price <steven.price@arm.com>,
        "Andrew Jones" <drjones@redhat.com>,
        Catalin Marinas <catalin.marinas@arm.com>,
        "Will Deacon" <will@kernel.org>, James Morse <james.morse@arm.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        <wanghaibin.wang@huawei.com>, Keqian Zhu <zhukeqian1@huawei.com>
Subject: [PATCH 1/2] clocksource: arm_arch_timer: Simplify and fix count
 reader code logic
Date: Mon, 17 Aug 2020 20:24:14 +0800
Message-ID: <20200817122415.6568-2-zhukeqian1@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
In-Reply-To: <20200817122415.6568-1-zhukeqian1@huawei.com>
References: <20200817122415.6568-1-zhukeqian1@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.174.187.22]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In commit 0ea415390cd3 (clocksource/arm_arch_timer: Use arch_timer_read_counter
to access stable counters), we separate stable and normal count reader. Actually
the stable reader can correctly lead us to normal reader if we has no workaround.

Besides, in erratum_set_next_event_tval_generic(), we use normal reader, it is
obviously wrong, so just revert this commit to solve this problem by the way.

Signed-off-by: Keqian Zhu <zhukeqian1@huawei.com>
---
 arch/arm/include/asm/arch_timer.h    | 14 ++----------
 arch/arm64/include/asm/arch_timer.h  | 24 ++------------------
 drivers/clocksource/arm_arch_timer.c | 43 ++----------------------------------
 3 files changed, 6 insertions(+), 75 deletions(-)

```
#### [RFC PATCH 1/5] KVM: arm64: Document pvtime LPT interface
##### From: Keqian Zhu <zhukeqian1@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Keqian Zhu <zhukeqian1@huawei.com>
X-Patchwork-Id: 11717065
Return-Path: <SRS0=mOyg=B3=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1F3C4109B
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Aug 2020 08:41:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0CA4120855
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Aug 2020 08:41:30 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726897AbgHQIl3 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 17 Aug 2020 04:41:29 -0400
Received: from szxga05-in.huawei.com ([45.249.212.191]:9745 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726685AbgHQIl1 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 17 Aug 2020 04:41:27 -0400
Received: from DGGEMS411-HUB.china.huawei.com (unknown [172.30.72.58])
        by Forcepoint Email with ESMTP id 8E9C953B776B2C53A1D1;
        Mon, 17 Aug 2020 16:41:22 +0800 (CST)
Received: from DESKTOP-5IS4806.china.huawei.com (10.174.187.22) by
 DGGEMS411-HUB.china.huawei.com (10.3.19.211) with Microsoft SMTP Server id
 14.3.487.0; Mon, 17 Aug 2020 16:41:12 +0800
From: Keqian Zhu <zhukeqian1@huawei.com>
To: <linux-kernel@vger.kernel.org>,
        <linux-arm-kernel@lists.infradead.org>,
        <kvmarm@lists.cs.columbia.edu>, <kvm@vger.kernel.org>
CC: Marc Zyngier <maz@kernel.org>, Steven Price <steven.price@arm.com>,
        Catalin Marinas <catalin.marinas@arm.com>,
        Will Deacon <will@kernel.org>,
        James Morse <james.morse@arm.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        <wanghaibin.wang@huawei.com>, Keqian Zhu <zhukeqian1@huawei.com>
Subject: [RFC PATCH 1/5] KVM: arm64: Document pvtime LPT interface
Date: Mon, 17 Aug 2020 16:41:06 +0800
Message-ID: <20200817084110.2672-2-zhukeqian1@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
In-Reply-To: <20200817084110.2672-1-zhukeqian1@huawei.com>
References: <20200817084110.2672-1-zhukeqian1@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.174.187.22]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The "Arm Paravirtualized Time for Arm-Base Systems" specification
DEN 0057A just contains "Stolen Time" now, as the details of "Live
Physical Time" have not been fully agreed.

This introduces a new LPT structure with more understandable fields,
as scale_mult and rscale_mult are symmetrical.

Signed-off-by: Steven Price <steven.price@arm.com>
Signed-off-by: Keqian Zhu <zhukeqian1@huawei.com>
---
 Documentation/virt/kvm/arm/pvtime.rst | 78 ++++++++++++++++++++++++++++++-----
 Documentation/virt/kvm/devices/vm.rst | 30 ++++++++++++++
 2 files changed, 97 insertions(+), 11 deletions(-)

```
#### [PATCH 1/3] KVM: arm64: Some fixes of PV-time interface document
##### From: Keqian Zhu <zhukeqian1@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Keqian Zhu <zhukeqian1@huawei.com>
X-Patchwork-Id: 11716385
Return-Path: <SRS0=mOyg=B3=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 824C2618
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Aug 2020 03:38:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 756D520658
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Aug 2020 03:38:32 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727016AbgHQDiS (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 16 Aug 2020 23:38:18 -0400
Received: from szxga05-in.huawei.com ([45.249.212.191]:9742 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726973AbgHQDiQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 16 Aug 2020 23:38:16 -0400
Received: from DGGEMS413-HUB.china.huawei.com (unknown [172.30.72.58])
        by Forcepoint Email with ESMTP id 3E6E47DEA0381D2AEE45;
        Mon, 17 Aug 2020 11:38:13 +0800 (CST)
Received: from DESKTOP-5IS4806.china.huawei.com (10.174.187.22) by
 DGGEMS413-HUB.china.huawei.com (10.3.19.213) with Microsoft SMTP Server id
 14.3.487.0; Mon, 17 Aug 2020 11:38:05 +0800
From: Keqian Zhu <zhukeqian1@huawei.com>
To: <linux-kernel@vger.kernel.org>,
        <linux-arm-kernel@lists.infradead.org>,
        <kvmarm@lists.cs.columbia.edu>, <kvm@vger.kernel.org>
CC: Marc Zyngier <maz@kernel.org>,
        Catalin Marinas <catalin.marinas@arm.com>,
        Will Deacon <will@kernel.org>,
        James Morse <james.morse@arm.com>,
        "Suzuki K Poulose" <suzuki.poulose@arm.com>,
        Steven Price <steven.price@arm.com>,
        <wanghaibin.wang@huawei.com>, Keqian Zhu <zhukeqian1@huawei.com>
Subject: [PATCH 1/3] KVM: arm64: Some fixes of PV-time interface document
Date: Mon, 17 Aug 2020 11:37:27 +0800
Message-ID: <20200817033729.10848-2-zhukeqian1@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
In-Reply-To: <20200817033729.10848-1-zhukeqian1@huawei.com>
References: <20200817033729.10848-1-zhukeqian1@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.174.187.22]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Rename PV_FEATURES tp PV_TIME_FEATURES

Signed-off-by: Keqian Zhu <zhukeqian1@huawei.com>
Reviewed-by: Andrew Jones <drjones@redhat.com>
Reviewed-by: Steven Price <steven.price@arm.com>
---
 Documentation/virt/kvm/arm/pvtime.rst | 6 +++---
 1 file changed, 3 insertions(+), 3 deletions(-)

```
#### [PATCH v2 1/2] KVM: arm64: Some fixes of PV-time interface document
##### From: Keqian Zhu <zhukeqian1@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Keqian Zhu <zhukeqian1@huawei.com>
X-Patchwork-Id: 11718021
Return-Path: <SRS0=mOyg=B3=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 998BF138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Aug 2020 11:08:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 890342072D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Aug 2020 11:08:10 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727021AbgHQLIH (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 17 Aug 2020 07:08:07 -0400
Received: from szxga05-in.huawei.com ([45.249.212.191]:9746 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726612AbgHQLIF (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 17 Aug 2020 07:08:05 -0400
Received: from DGGEMS411-HUB.china.huawei.com (unknown [172.30.72.58])
        by Forcepoint Email with ESMTP id DFFEC183E6E7D710B54F;
        Mon, 17 Aug 2020 19:08:00 +0800 (CST)
Received: from DESKTOP-5IS4806.china.huawei.com (10.174.187.22) by
 DGGEMS411-HUB.china.huawei.com (10.3.19.211) with Microsoft SMTP Server id
 14.3.487.0; Mon, 17 Aug 2020 19:07:51 +0800
From: Keqian Zhu <zhukeqian1@huawei.com>
To: <linux-kernel@vger.kernel.org>,
        <linux-arm-kernel@lists.infradead.org>,
        <kvmarm@lists.cs.columbia.edu>, <kvm@vger.kernel.org>
CC: Marc Zyngier <maz@kernel.org>, Steven Price <steven.price@arm.com>,
        "Andrew Jones" <drjones@redhat.com>,
        Catalin Marinas <catalin.marinas@arm.com>,
        "Will Deacon" <will@kernel.org>, James Morse <james.morse@arm.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        <wanghaibin.wang@huawei.com>, Keqian Zhu <zhukeqian1@huawei.com>
Subject: [PATCH v2 1/2] KVM: arm64: Some fixes of PV-time interface document
Date: Mon, 17 Aug 2020 19:07:27 +0800
Message-ID: <20200817110728.12196-2-zhukeqian1@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
In-Reply-To: <20200817110728.12196-1-zhukeqian1@huawei.com>
References: <20200817110728.12196-1-zhukeqian1@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.174.187.22]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Rename PV_FEATURES to PV_TIME_FEATURES.

Signed-off-by: Keqian Zhu <zhukeqian1@huawei.com>
Reviewed-by: Andrew Jones <drjones@redhat.com>
Reviewed-by: Steven Price <steven.price@arm.com>
---
 Documentation/virt/kvm/arm/pvtime.rst | 6 +++---
 1 file changed, 3 insertions(+), 3 deletions(-)

```
#### [PATCH] KVM: x86: fix access code passed to gva_to_gpa
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11719001
Return-Path: <SRS0=mOyg=B3=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9B35D13A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Aug 2020 18:02:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 824DD2072E
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Aug 2020 18:02:14 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Gs6qf9vF"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2390195AbgHQSB1 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 17 Aug 2020 14:01:27 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:54526 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S2388631AbgHQSAu (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 17 Aug 2020 14:00:50 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1597687246;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=M7O0Zd6WuXF1RKsXDTV/oWCgHc9hBiiy2FXt3YXOKsQ=;
        b=Gs6qf9vFRjVNzyyo5Jdgb4vaA3lTrAplhhEDEIHEdSDYVBKnmgVf1h5jHorJsXWwLAI3nP
        ZIrAqtD/Of92M9upmi7pLl/8Fz0ztz2zUTyN8xVv2DZMR7xLaSMDIk7/PMPuXj+EYIFmHS
        hP1wOKndvSlV7on+j2bTxscd4YJ0RtQ=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-423-qQDItl9mNwqrS87_GLAxJQ-1; Mon, 17 Aug 2020 14:00:44 -0400
X-MC-Unique: qQDItl9mNwqrS87_GLAxJQ-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 54F4E1008549;
        Mon, 17 Aug 2020 18:00:43 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 01BBA7A3B4;
        Mon, 17 Aug 2020 18:00:42 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Subject: [PATCH] KVM: x86: fix access code passed to gva_to_gpa
Date: Mon, 17 Aug 2020 14:00:42 -0400
Message-Id: <20200817180042.32264-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The PK bit of the error code is computed dynamically in permission_fault
and therefore need not be passed to gva_to_gpa: only the access bits
(fetch, user, write) need to be passed down.

Not doing so causes a splat in the pku test:

   WARNING: CPU: 25 PID: 5465 at arch/x86/kvm/mmu.h:197 paging64_walk_addr_generic+0x594/0x750 [kvm]
   Hardware name: Intel Corporation WilsonCity/WilsonCity, BIOS WLYDCRB1.SYS.0014.D62.2001092233 01/09/2020
   RIP: 0010:paging64_walk_addr_generic+0x594/0x750 [kvm]
   Code: <0f> 0b e9 db fe ff ff 44 8b 43 04 4c 89 6c 24 30 8b 13 41 39 d0 89
   RSP: 0018:ff53778fc623fb60 EFLAGS: 00010202
   RAX: 0000000000000001 RBX: ff53778fc623fbf0 RCX: 0000000000000007
   RDX: 0000000000000001 RSI: 0000000000000002 RDI: ff4501efba818000
   RBP: 0000000000000020 R08: 0000000000000005 R09: 00000000004000e7
   R10: 0000000000000001 R11: 0000000000000000 R12: 0000000000000007
   R13: ff4501efba818388 R14: 10000000004000e7 R15: 0000000000000000
   FS:  00007f2dcf31a700(0000) GS:ff4501f1c8040000(0000) knlGS:0000000000000000
   CS:  0010 DS: 0000 ES: 0000 CR0: 0000000080050033
   CR2: 0000000000000000 CR3: 0000001dea475005 CR4: 0000000000763ee0
   DR0: 0000000000000000 DR1: 0000000000000000 DR2: 0000000000000000
   DR3: 0000000000000000 DR6: 00000000fffe0ff0 DR7: 0000000000000400
   PKRU: 55555554
   Call Trace:
    paging64_gva_to_gpa+0x3f/0xb0 [kvm]
    kvm_fixup_and_inject_pf_error+0x48/0xa0 [kvm]
    handle_exception_nmi+0x4fc/0x5b0 [kvm_intel]
    kvm_arch_vcpu_ioctl_run+0x911/0x1c10 [kvm]
    kvm_vcpu_ioctl+0x23e/0x5d0 [kvm]
    ksys_ioctl+0x92/0xb0
    __x64_sys_ioctl+0x16/0x20
    do_syscall_64+0x3e/0xb0
    entry_SYSCALL_64_after_hwframe+0x44/0xa9
   ---[ end trace d17eb998aee991da ]---

Reported-by: Sean Christopherson <sean.j.christopherson@intel.com>
Fixes: 897861479c064 ("KVM: x86: Add helper functions for illegal GPA checking and page fault injection")
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/x86.c | 6 +++++-
 1 file changed, 5 insertions(+), 1 deletion(-)

```
#### [PATCH] KVM: x86: kvmclock_init_mem() should be called any way
##### From: Zelin Deng <zelin.deng@linux.alibaba.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zelin Deng <zelin.deng@linux.alibaba.com>
X-Patchwork-Id: 11716477
Return-Path: <SRS0=mOyg=B3=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 63A20739
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Aug 2020 05:57:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5049E206DA
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Aug 2020 05:57:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726417AbgHQF5z (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 17 Aug 2020 01:57:55 -0400
Received: from out30-130.freemail.mail.aliyun.com ([115.124.30.130]:37592
 "EHLO
        out30-130.freemail.mail.aliyun.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726235AbgHQF5y (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 17 Aug 2020 01:57:54 -0400
X-Alimail-AntiSpam: 
 AC=PASS;BC=-1|-1;BR=01201311R171e4;CH=green;DM=||false|;DS=||;FP=0|-1|-1|-1|0|-1|-1|-1;HT=e01f04397;MF=zelin.deng@linux.alibaba.com;NM=1;PH=DS;RN=8;SR=0;TI=SMTPD_---0U5z1wNG_1597643859;
Received: from localhost(mailfrom:zelin.deng@linux.alibaba.com
 fp:SMTPD_---0U5z1wNG_1597643859)
          by smtp.aliyun-inc.com(127.0.0.1);
          Mon, 17 Aug 2020 13:57:39 +0800
From: Zelin Deng <zelin.deng@linux.alibaba.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Thomas Gleixner <tglx@linutronix.de>
Cc: Brijesh Singh <brijesh.singh@amd.com>,
        Artie Ding <artie.ding@linux.alibaba.com>,
        Caspar Zhang <caspar@linux.alibaba.com>,
        Zelin Deng <zelin.deng@linux.alibaba.com>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: x86: kvmclock_init_mem() should be called any way
Date: Mon, 17 Aug 2020 13:57:39 +0800
Message-Id: <20200817055739.9994-1-zelin.deng@linux.alibaba.com>
X-Mailer: git-send-email 2.20.1.2432.ga663e714
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

pvclock data pointers of vCPUs >= HVC_BOOT_ARRAY_SIZE (64) are stored in
hvclock_mem wihch is initialized in kvmclock_init_mem().
Here're 3 scenarios in current implementation:
    - no-kvmclock is set in cmdline. kvm pv clock driver is disabled,
      no impact.
    - no-kvmclock-vsyscall is set in cmdline. kvmclock_init_mem() won't
      be called. No memory for storing pvclock data of vCPUs >= 64, vCPUs
      >= 64 can not be online or hotpluged.
    - tsc unstable. kvmclock_init_mem() won't be called. vCPUs >= 64 can
      not be online or hotpluged.
It's not reasonable that vCPUs hotplug have been impacted by last 2
scenarios. Hence move kvmclock_init_mem() to front, in case hvclock_mem
can not be initialized unexpectedly.

Fixes: 6a1cac56f41f9 (x86/kvm: Use __bss_decrypted attribute in shared variables)
Signed-off-by: Zelin Deng <zelin.deng@linux.alibaba.com>
---
 arch/x86/kernel/kvmclock.c | 9 +++++++--
 1 file changed, 7 insertions(+), 2 deletions(-)

```
#### [PATCH 1/7] MIPS: sync-r4k: Rework to be many cores firendly
##### From: Jiaxun Yang <jiaxun.yang@flygoat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jiaxun Yang <jiaxun.yang@flygoat.com>
X-Patchwork-Id: 11716405
Return-Path: <SRS0=mOyg=B3=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7D461739
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Aug 2020 03:48:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 60A9520826
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Aug 2020 03:48:00 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=flygoat.com header.i=@flygoat.com header.b="ZozkZjop"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727043AbgHQDr7 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 16 Aug 2020 23:47:59 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:38106 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726977AbgHQDr5 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 16 Aug 2020 23:47:57 -0400
Received: from vultr.net.flygoat.com (vultr.net.flygoat.com
 [IPv6:2001:19f0:6001:3633:5400:2ff:fe8c:553])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id AC65CC061388
        for <kvm@vger.kernel.org>; Sun, 16 Aug 2020 20:47:57 -0700 (PDT)
Received: from localhost.localdomain (unknown
 [IPv6:2001:da8:20f:4430:250:56ff:fe9a:7470])
        by vultr.net.flygoat.com (Postfix) with ESMTPSA id 25FAA1FEF5;
        Mon, 17 Aug 2020 03:47:51 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=simple/simple; d=flygoat.com; s=vultr;
        t=1597636076; bh=akb+og0HnO3wboY8Fq8f9zbqdX3Uoz+REcSJDdeCfZI=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=ZozkZjopFHz84hwKNShWN4hgcNl9ecwl+KkYe0OnQNX1Kf0Q+K2KcFp7BOk+T8yvQ
         K9fg8Sxnc6uhT4IedQyJc+DKDODsvAQA5C2/K/gMKXz0aYfQ7I82+nWl7VED/EFfE1
         EhDoldaLtmmcOd87ZTxyWWRvGvVT0B7rfFv9pDs8wFIKNRWN60d6+owsr3HkYdO0jC
         akEG5f/6xyvBCX3d+j+VO+qWTLqGIoUg0Ko2xMminrNt4rE4hPvgMz4ic7QDSQDSb8
         tF9dd1Qy0C/LrAiIG2EiALP1/QlK7Dvr56E27V1bNfeMJK/gYIWAE5JmT4lfzZZ2aF
         rT9UJ7CU9rWOw==
From: Jiaxun Yang <jiaxun.yang@flygoat.com>
To: linux-mips@vger.kernel.org
Cc: Jiaxun Yang <jiaxun.yang@flygoat.com>,
 Thomas Bogendoerfer <tsbogend@alpha.franken.de>,
 Huacai Chen <chenhc@lemote.com>,
 Aleksandar Markovic <aleksandar.qemu.devel@gmail.com>,
 Paul Burton <paulburton@kernel.org>,
 Serge Semin <Sergey.Semin@baikalelectronics.ru>,
 WANG Xuerui <git@xen0n.name>,
 =?utf-8?b?5ZGo55Cw5p2wIChaaG91IFlhbmppZSk=?=  <zhouyanjie@wanyeetech.com>,
 Liangliang Huang <huanglllzu@gmail.com>,
 afzal mohammed <afzal.mohd.ma@gmail.com>, Ingo Molnar <mingo@kernel.org>,
 Peter Xu <peterx@redhat.com>,
 "Peter Zijlstra (Intel)" <peterz@infradead.org>,
 Sergey Korolev <s.korolev@ndmsystems.com>,
 Alexey Malahov <Alexey.Malahov@baikalelectronics.ru>,
 Marc Zyngier <maz@kernel.org>, Anup Patel <anup.patel@wdc.com>,
 Palmer Dabbelt <palmer@dabbelt.com>, Atish Patra <atish.patra@wdc.com>,
 Michael Kelley <mikelley@microsoft.com>, Steven Price <steven.price@arm.com>,
 Daniel Jordan <daniel.m.jordan@oracle.com>, Ming Lei <ming.lei@redhat.com>,
 Ulf Hansson <ulf.hansson@linaro.org>, Mike Leach <mike.leach@linaro.org>,
 linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [PATCH 1/7] MIPS: sync-r4k: Rework to be many cores firendly
Date: Mon, 17 Aug 2020 11:46:40 +0800
Message-Id: <20200817034701.3515721-2-jiaxun.yang@flygoat.com>
X-Mailer: git-send-email 2.28.0.rc1
In-Reply-To: <20200817034701.3515721-1-jiaxun.yang@flygoat.com>
References: <20200817034701.3515721-1-jiaxun.yang@flygoat.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The original sync-r4k did a good job on reducing jitter by determine
the "next time value", but it has a limitation that when we have lots
of cores, the timewrap on CPU0 will become unaccpetable. That will also
happen when CPU Hotplug is enabled and the counter needs to be synchronised
at every plug event.

Here we reworked the whole procdure. Now the synchronise event on CPU0
is triggered by smp call function, and we won't touch the count on CPU0
at all.

Signed-off-by: Jiaxun Yang <jiaxun.yang@flygoat.com>
---
 arch/mips/include/asm/r4k-timer.h |   5 --
 arch/mips/kernel/smp.c            |   2 -
 arch/mips/kernel/sync-r4k.c       | 143 +++++++++++++-----------------
 3 files changed, 61 insertions(+), 89 deletions(-)

```
#### Rename iommu_tlb_* functions to iommu_iotlb_*
##### From: Tom Murphy <murphyt7@tcd.ie>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tom Murphy <murphyt7@tcd.ie>
X-Patchwork-Id: 11719189
Return-Path: <SRS0=mOyg=B3=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5AA6E13A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Aug 2020 21:01:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3C47E2072D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Aug 2020 21:01:07 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=tcd-ie.20150623.gappssmtp.com
 header.i=@tcd-ie.20150623.gappssmtp.com header.b="X1ehmlg/"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727073AbgHQVBE (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 17 Aug 2020 17:01:04 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:57416 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726203AbgHQVA6 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 17 Aug 2020 17:00:58 -0400
Received: from mail-pg1-x543.google.com (mail-pg1-x543.google.com
 [IPv6:2607:f8b0:4864:20::543])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 2E31BC061342
        for <kvm@vger.kernel.org>; Mon, 17 Aug 2020 14:00:57 -0700 (PDT)
Received: by mail-pg1-x543.google.com with SMTP id m34so8685020pgl.11
        for <kvm@vger.kernel.org>; Mon, 17 Aug 2020 14:00:57 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=tcd-ie.20150623.gappssmtp.com; s=20150623;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=g3b17tpQsxeSrpEJMNS65bCpVzCghTE72IhZ2F4sGm8=;
        b=X1ehmlg/aGEGwU8TlqB+7kJoeA7pGAjwOZUvoxZgjsb9cYUBO53eVjUbxfMC95XFPL
         Q8KTcz9XTCWFgfS2tP8/KtjBKQPS068kT06iwABH7hw+JoPmc92WjyUnCMMIOG3y3dVW
         8Q/jbqfphqosT0z/JKfeFL8aItaLAym4bVWP7q0TSCm4m0ToVhuJ35Ap7r2ZPap6h069
         bBTcdGkCwAwiKRLgIDJ19J8Tm4ve5mEQYQSNx8/ncgRMWb+p/t2HqFZdgrG5YRevMlXg
         JWZl6E+oOmLw2z+QC7yOGH/x/ODm219KdBiBikoMblD5i0+ahzg7NSv3BQ7zeySsdG5t
         oYPQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=g3b17tpQsxeSrpEJMNS65bCpVzCghTE72IhZ2F4sGm8=;
        b=K7g054qM2Zlr6M3qylGZSosLRDXUe28ZNBR9uTg8ca+dDPazj3Dn6XCYcYJ98G87Rm
         /KcFtBSwEE6wOD3nOVcMRFQNdz1qIfFl82DcdL/cfH3x1smZMNtJFALc13XNSLHUIGAT
         T9VWttx2hiUw6gTRQpL8kua7rNne5SoKMOoxL08+c9C5HjYz7NwhNUaniaweGPTxgfA4
         SpAl3wjGEC+4I9pMZRZ6tAe+FvnnhVV6Y4TNZ+A02190jWBTUgEz3LG8YIQ494xEWZyt
         uX1jCZNmJz2EteQVV4UmRhbKBe/Ex9y4968GLpESNwZEJBJwovC/mQW16p5lQnbE/t0Z
         jaJQ==
X-Gm-Message-State: AOAM531wd8yfS1UEugi8v9Fq9IQ++Cqm7sA940zzgVUR+SKluFZEYC/O
        mAQ3jvv4bp/4ejDuOMncaep9dQ==
X-Google-Smtp-Source: 
 ABdhPJxZlziJHTCHPvQS4XhFGDrR51ylltOsuD3KwPoc2QE6wRzaZSRbXWvH7K1WQcYlUvdGvfnT7w==
X-Received: by 2002:aa7:9468:: with SMTP id t8mr12312380pfq.182.1597698056896;
        Mon, 17 Aug 2020 14:00:56 -0700 (PDT)
Received: from localhost.localdomain (S0106ac17c8c0ce82.vc.shawcable.net.
 [24.87.214.6])
        by smtp.googlemail.com with ESMTPSA id
 b20sm21158263pfo.88.2020.08.17.14.00.56
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 17 Aug 2020 14:00:56 -0700 (PDT)
From: Tom Murphy <murphyt7@tcd.ie>
To: iommu@lists.linux-foundation.org
Cc: person@a.com, Tom Murphy <murphyt7@tcd.ie>,
        Joerg Roedel <joro@8bytes.org>,
        Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Will Deacon <will@kernel.org>,
        Robin Murphy <robin.murphy@arm.com>,
        Yong Wu <yong.wu@mediatek.com>, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org
Subject: Rename iommu_tlb_* functions to iommu_iotlb_*
Date: Mon, 17 Aug 2020 22:00:49 +0100
Message-Id: <20200817210051.13546-1-murphyt7@tcd.ie>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

To keep naming consistent we should stick with *iotlb*. This patch
renames a few remaining functions.

Signed-off-by: Tom Murphy <murphyt7@tcd.ie>
---
 drivers/iommu/dma-iommu.c       |  2 +-
 drivers/iommu/iommu.c           |  4 ++--
 drivers/vfio/vfio_iommu_type1.c |  2 +-
 include/linux/io-pgtable.h      |  2 +-
 include/linux/iommu.h           | 10 +++++-----
 5 files changed, 10 insertions(+), 10 deletions(-)

```
#### [PATCH] selftests: kvm: Use a shorter encoding to clear RAX
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11718905
Return-Path: <SRS0=mOyg=B3=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E0DFF13A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Aug 2020 17:20:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C7768206FA
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Aug 2020 17:20:54 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="XBz6GJYE"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2389626AbgHQRUw (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 17 Aug 2020 13:20:52 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:55122 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1731460AbgHQRUp (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 17 Aug 2020 13:20:45 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1597684844;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=2KOxcTzA4HjXLrbc8Kis3OZr0Jk9r2f94fOWh6B2JtI=;
        b=XBz6GJYEGBFwPmHH9FcPApxgQWy607NhqWJ50zudkV1ZW2b/WPsK+2jZLbLmWVJrV0i49W
        8FO62cvmZMJ9tYkxyX5utEcPgosJ68WGLMpAh5erkbnnf0PhQbFt86/p/JyD/RVowVZ5Gp
        71ICP6jY2xG4l341S1wXKOE6FjTYnnI=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-322-VJjp-ljEPnex_p-WPMyJ0g-1; Mon, 17 Aug 2020 13:20:39 -0400
X-MC-Unique: VJjp-ljEPnex_p-WPMyJ0g-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 223CF81F001;
        Mon, 17 Aug 2020 17:20:38 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id B33FD5D9D2;
        Mon, 17 Aug 2020 17:20:34 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        peterx@redhat.com, Yang Weijiang <weijiang.yang@intel.com>,
        stable@vger.kernel.org
Subject: [PATCH] selftests: kvm: Use a shorter encoding to clear RAX
Date: Mon, 17 Aug 2020 13:20:34 -0400
Message-Id: <20200817172034.26673-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Yang Weijiang <weijiang.yang@intel.com>

If debug_regs.c is built with newer binutils, the resulting binary is "optimized"
by the assembler:

asm volatile("ss_start: "
             "xor %%rax,%%rax\n\t"
             "cpuid\n\t"
             "movl $0x1a0,%%ecx\n\t"
             "rdmsr\n\t"
             : : : "rax", "ecx");

is translated to :

  000000000040194e <ss_start>:
  40194e:       31 c0                   xor    %eax,%eax     <----- rax->eax?
  401950:       0f a2                   cpuid
  401952:       b9 a0 01 00 00          mov    $0x1a0,%ecx
  401957:       0f 32                   rdmsr

As you can see rax is replaced with eax in target binary code.
This causes a difference is the length of xor instruction (2 Byte vs 3 Byte),
and makes the hard-coded instruction length check fail:

        /* Instruction lengths starting at ss_start */
        int ss_size[4] = {
                3,              /* xor */   <-------- 2 or 3?
                2,              /* cpuid */
                5,              /* mov */
                2,              /* rdmsr */
        };

Encode the shorter version directly and, while at it, fix the "clobbers"
of the asm.

Reported-by: Yang Weijiang <weijiang.yang@intel.com>
Cc: stable@vger.kernel.org
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 tools/testing/selftests/kvm/x86_64/debug_regs.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
