#### [PATCH 1/8] iommu/vt-d: clean up 32bit si_domain assignment
##### From: Tom Murphy <murphyt7@tcd.ie>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tom Murphy <murphyt7@tcd.ie>
X-Patchwork-Id: 11307003
Return-Path: <SRS0=aF81=2L=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1C1FF197C
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 21 Dec 2019 15:04:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id EF57321927
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 21 Dec 2019 15:04:23 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=tcd-ie.20150623.gappssmtp.com
 header.i=@tcd-ie.20150623.gappssmtp.com header.b="OfH7P/O3"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727226AbfLUPEW (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 21 Dec 2019 10:04:22 -0500
Received: from mail-ed1-f67.google.com ([209.85.208.67]:40285 "EHLO
        mail-ed1-f67.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727166AbfLUPEV (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 21 Dec 2019 10:04:21 -0500
Received: by mail-ed1-f67.google.com with SMTP id b8so11389661edx.7
        for <kvm@vger.kernel.org>; Sat, 21 Dec 2019 07:04:20 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=tcd-ie.20150623.gappssmtp.com; s=20150623;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=yYBMxHbMND3KXJAAlRHvXU1gMqhOszki9jNdzLeiJU4=;
        b=OfH7P/O33XqVmrRHuQ/69BFU28v+MGMIwEx7w/umhnY1qNKXSsCGq1Cwaq7vbEzLMp
         1ksjMyjtAT7hWlwrLscfQ77QvEuhl13Swd9KWJGnv0QAQ12Z4EMmc0UBnDdMMC+fXDOJ
         AwGTYVg3PMuc/dPZ45WbnbZxhIn8YgFF6EoHwr+nGZQHnCr6DhBjsrSxM9L9AHr6Caov
         mXYjg4dRT2WuQhsh/0gAG0D+t+HUDuGU7Nr7pKzkderovTZvMGtj+Zix8GpyJLSUDu3F
         9RO4rb75QMNfDN91pVMg46S9XuW7CZvVU6kXu8d0DBfHs3P12+Wv2dYSOCKjy0bOS/Il
         93QQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=yYBMxHbMND3KXJAAlRHvXU1gMqhOszki9jNdzLeiJU4=;
        b=GyufEYdXS7CMD3pQbHbho9dEUxSKvHyyp4qtWqV5mRXd9gdZPT9x26LmUhmGGkJKk0
         CiiG9gtFgdKsCijY9MEfmY1j3OIBvy98QEa9IoL5ir5N6Bw8ywwDyVi6V1GNTb0u5a9A
         9P3u/z1gH2kDQL5wt0G2khYnK2NscL05kXwIKquPR1v73UoHeA8Y2JgFbgG03keBCgJf
         YuvsNwjLXUj0hXNDkyQYS6m5f4L6K4kEKbryJ6nsoeADaDu38yWWfqXZFczuuhWdOdoC
         qnT63BBwQ2/zpvjNP8UPYfGLwuNhdZaN59TAxWA/rVGOr//WOAD9EbGYJsnlbFfiE9qb
         apgQ==
X-Gm-Message-State: APjAAAWxk4buwQoojZFdBpQ0neRycJbHCowfGibiyBZAbcS0awePShH4
        hJHwS08JyQMjB9cpxBZwwmRpXw==
X-Google-Smtp-Source: 
 APXvYqxT2LSHoXL54d4LTh1o2yBuykvAD28LUC42eFWoj6JLm/GJqllZFuXkdK3UEroGowvwPF7Zpw==
X-Received: by 2002:a17:906:5448:: with SMTP id
 d8mr22606596ejp.254.1576940659410;
        Sat, 21 Dec 2019 07:04:19 -0800 (PST)
Received: from localhost.localdomain ([80.233.37.20])
        by smtp.googlemail.com with ESMTPSA id
 u13sm1517639ejz.69.2019.12.21.07.04.15
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Sat, 21 Dec 2019 07:04:18 -0800 (PST)
From: Tom Murphy <murphyt7@tcd.ie>
To: iommu@lists.linux-foundation.org
Cc: Tom Murphy <murphyt7@tcd.ie>,
        Jani Nikula <jani.nikula@linux.intel.com>,
        Joonas Lahtinen <joonas.lahtinen@linux.intel.com>,
        Rodrigo Vivi <rodrigo.vivi@intel.com>,
        David Airlie <airlied@linux.ie>,
        Daniel Vetter <daniel@ffwll.ch>,
        Joerg Roedel <joro@8bytes.org>, Will Deacon <will@kernel.org>,
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
        Gerald Schaefer <gerald.schaefer@de.ibm.com>,
        Thierry Reding <thierry.reding@gmail.com>,
        Jonathan Hunter <jonathanh@nvidia.com>,
        Jean-Philippe Brucker <jean-philippe@linaro.org>,
        Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Eric Auger <eric.auger@redhat.com>,
        Julien Grall <julien.grall@arm.com>,
        Marc Zyngier <maz@kernel.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        intel-gfx@lists.freedesktop.org, dri-devel@lists.freedesktop.org,
        linux-kernel@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
        linux-samsung-soc@vger.kernel.org, linux-arm-msm@vger.kernel.org,
        linux-mediatek@lists.infradead.org,
        linux-rockchip@lists.infradead.org, linux-s390@vger.kernel.org,
        linux-tegra@vger.kernel.org,
        virtualization@lists.linux-foundation.org, kvm@vger.kernel.org
Subject: [PATCH 1/8] iommu/vt-d: clean up 32bit si_domain assignment
Date: Sat, 21 Dec 2019 15:03:53 +0000
Message-Id: <20191221150402.13868-2-murphyt7@tcd.ie>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20191221150402.13868-1-murphyt7@tcd.ie>
References: <20191221150402.13868-1-murphyt7@tcd.ie>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In the intel iommu driver devices which only support 32bit DMA can't be
direct mapped. The implementation of this is weird. Currently we assign
it a direct mapped domain and then remove the domain later and replace
it with a domain of type IOMMU_DOMAIN_IDENTITY. We should just assign it
a domain of type IOMMU_DOMAIN_IDENTITY from the begging rather than
needlessly swapping domains.

Signed-off-by: Tom Murphy <murphyt7@tcd.ie>
---
 drivers/iommu/intel-iommu.c | 88 +++++++++++++------------------------
 1 file changed, 31 insertions(+), 57 deletions(-)

```
#### [PATCH RESEND v2 01/17] KVM: Remove kvm_read_guest_atomic()
##### From: Peter Xu <peterx@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11306593
Return-Path: <SRS0=aF81=2L=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D920D14B7
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 21 Dec 2019 01:50:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B734221655
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 21 Dec 2019 01:50:36 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="gvGicvQj"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727221AbfLUBuf (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 20 Dec 2019 20:50:35 -0500
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:28903 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726613AbfLUBts (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 20 Dec 2019 20:49:48 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1576892986;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=5u+NdTdcxJqnd4CDcK36kvrGYVN4B69rZJAB5gjRDOQ=;
        b=gvGicvQjbuqEeaL0fZ+IX0/0vUHCTKl4ikEYU34Fd2/AD6VbMEKDOUBFzk4A7ig1DUI25w
        ImIDjGDmpgNiz66JsWy3QOZGkHdv6v/m16OhPkFGhKDfPFDZir2oZJPlArl7AkdYCnp9Rq
        9MuKP+0FJMrPGWUlSgpE031syyZT3+o=
Received: from mail-qv1-f69.google.com (mail-qv1-f69.google.com
 [209.85.219.69]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-358-sEqscXwiPQONxZSpWc9tzA-1; Fri, 20 Dec 2019 20:49:45 -0500
X-MC-Unique: sEqscXwiPQONxZSpWc9tzA-1
Received: by mail-qv1-f69.google.com with SMTP id f16so7171166qvr.7
        for <kvm@vger.kernel.org>; Fri, 20 Dec 2019 17:49:45 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=5u+NdTdcxJqnd4CDcK36kvrGYVN4B69rZJAB5gjRDOQ=;
        b=WAJ+isn+iO9K4yzb6ftbeKFsAj9TcrTgtD4O17k4eKN6ZQtjysJI8wyxYtYMxPpdFx
         /RWv1hSE4e7qk+caiKqw/ns+jt+PXPQDoO+MW1mZzpdgjx+8tVs6P4TgI1NaPmIckOpu
         6iUUO/9RurA/6meXj5JLCoA3m95T2GWqmxHTlvbXkjGK7g7CYDZj3CHNkNe8ROv2wRRp
         sTo/UqdcIz4+L+R/V0xPmLF/WRn3zkCluy0J6tJEv5hoVSe2DPRyl0g9Q/WftKWMC1ws
         lu+q2cqjodzt8UQcgu1hHBL74OlAqrOU5q7LShz3sCMwVbe+hDQPATYFeyeJ12b6ZTsQ
         /nrw==
X-Gm-Message-State: APjAAAU+hpmcjAGqP/RcI3pXzrimVacMnua1UpK0cEPqwJ282odWUBDm
        WB1pSRmgX38aJuYOXmgrwSBDwDQtxsJpMyoXifHg+t/qA34Tjm93Sss5AzfChs7vHRJCdDWLmFt
        UlIhbRi91Qwp2
X-Received: by 2002:a05:620a:634:: with SMTP id
 20mr7129944qkv.269.1576892984497;
        Fri, 20 Dec 2019 17:49:44 -0800 (PST)
X-Google-Smtp-Source: 
 APXvYqzi7/gDaYgNg0pHa+V7FOPwTChgJ98Acb8wMgEHent4TmIHneaBgF7FVuz9dNugS/zXI4cUAw==
X-Received: by 2002:a05:620a:634:: with SMTP id
 20mr7129928qkv.269.1576892984288;
        Fri, 20 Dec 2019 17:49:44 -0800 (PST)
Received: from xz-x1.hitronhub.home
 (CPEf81d0fb19163-CMf81d0fb19160.cpe.net.fido.ca. [72.137.123.47])
        by smtp.gmail.com with ESMTPSA id
 e21sm3396932qkm.55.2019.12.20.17.49.42
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 20 Dec 2019 17:49:43 -0800 (PST)
From: Peter Xu <peterx@redhat.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: "Dr . David Alan Gilbert" <dgilbert@redhat.com>,
        Christophe de Dinechin <dinechin@redhat.com>,
        peterx@redhat.com,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        "Michael S . Tsirkin" <mst@redhat.com>,
        Jason Wang <jasowang@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>
Subject: [PATCH RESEND v2 01/17] KVM: Remove kvm_read_guest_atomic()
Date: Fri, 20 Dec 2019 20:49:22 -0500
Message-Id: <20191221014938.58831-2-peterx@redhat.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20191221014938.58831-1-peterx@redhat.com>
References: <20191221014938.58831-1-peterx@redhat.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Remove kvm_read_guest_atomic() because it's not used anywhere.

Signed-off-by: Peter Xu <peterx@redhat.com>
---
 include/linux/kvm_host.h |  2 --
 virt/kvm/kvm_main.c      | 11 -----------
 2 files changed, 13 deletions(-)

```
#### [PATCH] MAINTAINERS: Orphan KVM for MIPS
##### From: James Hogan <jhogan@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: James Hogan <jhogan@kernel.org>
X-Patchwork-Id: 11307107
Return-Path: <SRS0=aF81=2L=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6D68413A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 21 Dec 2019 15:50:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4206421D7E
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 21 Dec 2019 15:50:31 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1576943431;
	bh=Qpdhp38TYluaHjQoJc0KYQrsy0xlL38Nc30CTBJJEuQ=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=RwTISt2SzibDk2gr1AB4b5bUlRu9bIFk4DawlS6Hvh62vUHD65UFJFTddkmtjWyV2
	 jLtPEz7XE7kp+RbSQvrhda43lZ/Q5luaYH0X7Tk5BwwcR0ervkG6KmG6N2+LN6jSLj
	 DtEXIVCGy0nqsXIvH1a97nTugNpcgpnMEHq4XDvU=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726791AbfLUPua (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 21 Dec 2019 10:50:30 -0500
Received: from mail.kernel.org ([198.145.29.99]:59956 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726107AbfLUPua (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 21 Dec 2019 10:50:30 -0500
Received: from jamesdev.lan (jahogan.plus.com [212.159.75.221])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-GCM-SHA256 (128/128 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 8F49E2070B;
        Sat, 21 Dec 2019 15:50:28 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1576943429;
        bh=Qpdhp38TYluaHjQoJc0KYQrsy0xlL38Nc30CTBJJEuQ=;
        h=From:To:Cc:Subject:Date:From;
        b=z7r33QPFF3aXcFJ9uX4qP176TqRj0ssGenGrBFE9kdgh1btHptcSCqviiGFNLXCro
         mwjAruWCGWL/RnInHf70OTTZ3hrk2xjnqt0BYduE4Nflf2Q5CO3Wu4augkHwJ/eL1W
         D2mbHinA9O38QH1dA87ioA7li78tpBXD3LeuylV4=
From: James Hogan <jhogan@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Paul Burton <paulburton@kernel.org>
Cc: James Hogan <jhogan@kernel.org>,
        Ralf Baechle <ralf@linux-mips.org>, kvm@vger.kernel.org,
        linux-mips@vger.kernel.org
Subject: [PATCH] MAINTAINERS: Orphan KVM for MIPS
Date: Sat, 21 Dec 2019 15:50:13 +0000
Message-Id: <20191221155013.49080-1-jhogan@kernel.org>
X-Mailer: git-send-email 2.24.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

I haven't been active for 18 months, and don't have the hardware set up
to test KVM for MIPS, so mark it as orphaned and remove myself as
maintainer. Hopefully somebody from MIPS can pick this up.

Signed-off-by: James Hogan <jhogan@kernel.org>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: "Radim Krčmář" <rkrcmar@redhat.com>
Cc: Paul Burton <paulburton@kernel.org>
Cc: Ralf Baechle <ralf@linux-mips.org>
Cc: kvm@vger.kernel.org
Cc: linux-mips@vger.kernel.org
---
 MAINTAINERS | 3 +--
 1 file changed, 1 insertion(+), 2 deletions(-)

```
#### [PATCH v5 01/19] x86/msr-index: Clean up bit defines for IA32_FEATURE_CONTROL MSR
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11306629
Return-Path: <SRS0=aF81=2L=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C2A9A14B7
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 21 Dec 2019 04:46:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 9761A21927
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 21 Dec 2019 04:46:08 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726834AbfLUEpy (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 20 Dec 2019 23:45:54 -0500
Received: from mga03.intel.com ([134.134.136.65]:31824 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726705AbfLUEpx (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 20 Dec 2019 23:45:53 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by orsmga103.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 20 Dec 2019 20:45:51 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.69,338,1571727600";
   d="scan'208";a="222620049"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by fmsmga001.fm.intel.com with ESMTP; 20 Dec 2019 20:45:51 -0800
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        x86@kernel.org
Cc: "H. Peter Anvin" <hpa@zytor.com>, Peter Zijlstra <peterz@infradead.org>,
 Arnaldo Carvalho de Melo <acme@kernel.org>,
 Mark Rutland <mark.rutland@arm.com>,
 Alexander Shishkin <alexander.shishkin@linux.intel.com>,
 Jiri Olsa <jolsa@redhat.com>, Namhyung Kim <namhyung@kernel.org>,
 Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Sean Christopherson <sean.j.christopherson@intel.com>,
 Vitaly Kuznetsov <vkuznets@redhat.com>, Wanpeng Li <wanpengli@tencent.com>,
 Jim Mattson <jmattson@google.com>, Joerg Roedel <joro@8bytes.org>,
 Tony Luck <tony.luck@intel.com>, Tony W Wang-oc <TonyWWang-oc@zhaoxin.com>,
 Jacob Pan <jacob.jun.pan@linux.intel.com>, Len Brown <lenb@kernel.org>,
 Shuah Khan <shuah@kernel.org>, linux-kernel@vger.kernel.org,
 kvm@vger.kernel.org, linux-edac@vger.kernel.org, linux-pm@vger.kernel.org,
 linux-kselftest@vger.kernel.org, Borislav Petkov <bp@suse.de>,
 Jarkko Sakkinen <jarkko.sakkinen@linux.intel.com>
Subject: [PATCH v5 01/19] x86/msr-index: Clean up bit defines for
 IA32_FEATURE_CONTROL MSR
Date: Fri, 20 Dec 2019 20:44:55 -0800
Message-Id: <20191221044513.21680-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20191221044513.21680-1-sean.j.christopherson@intel.com>
References: <20191221044513.21680-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

As pointed out by Boris, the defines for bits in IA32_FEATURE_CONTROL
are quite a mouthful, especially the VMX bits which must differentiate
between enabling VMX inside and outside SMX (TXT) operation.  Rename the
MSR and its bit defines to abbreviate FEATURE_CONTROL as FEAT_CTL to
make them a little friendlier on the eyes.

Arguably the MSR itself should keep the full IA32_FEATURE_CONTROL name
to match Intel's SDM, but a future patch will add a dedicated Kconfig,
file and functions for the MSR.  Using the full name for those assets is
rather unwieldy, so bite the bullet and use IA32_FEAT_CTL so that its
nomenclature is consistent throughout the kernel.

Opportunistically fix a few other annoyances with the defines:

  - Relocate the bit defines so that they immediately follow the MSR
    define, e.g. aren't mistaken as belonging to MISC_FEATURE_CONTROL.
  - Add whitespace around the block of feature control defines to make
    it clear they're all related.
  - Use BIT() instead of manually encoding the bit shift.
  - Use "VMX" instead of "VMXON" to match the SDM.
  - Append "_ENABLED" to the LMCE (Local Machine Check Exception) bit to
    be consistent with the kernel's verbiage used for all other feature
    control bits.  Note, the SDM refers to the LMCE bit as LMCE_ON,
    likely to differentiate it from IA32_MCG_EXT_CTL.LMCE_EN.  Ignore
    the (literal) one-off usage of _ON, the SDM is simply "wrong".

Cc: Borislav Petkov <bp@alien8.de>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/include/asm/msr-index.h | 14 +++++-----
 arch/x86/kernel/cpu/mce/intel.c  | 10 +++----
 arch/x86/kvm/vmx/nested.c        |  4 +--
 arch/x86/kvm/vmx/vmx.c           | 46 ++++++++++++++++----------------
 arch/x86/kvm/vmx/vmx.h           |  2 +-
 arch/x86/kvm/x86.c               |  2 +-
 drivers/idle/intel_idle.c        |  2 +-
 7 files changed, 41 insertions(+), 39 deletions(-)

```
