#### [PATCH] accel: kvm: clarify that extra exit data is hexadecimal
##### From: David Edmondson <david.edmondson@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: David Edmondson <david.edmondson@oracle.com>
X-Patchwork-Id: 12228965
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,UNPARSEABLE_RELAY,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 047E5C433B4
	for <kvm@archiver.kernel.org>; Wed, 28 Apr 2021 14:24:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C802D61434
	for <kvm@archiver.kernel.org>; Wed, 28 Apr 2021 14:24:38 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231585AbhD1OZW (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 28 Apr 2021 10:25:22 -0400
Received: from wforward1-smtp.messagingengine.com ([64.147.123.30]:32831 "EHLO
        wforward1-smtp.messagingengine.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S229520AbhD1OZV (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 28 Apr 2021 10:25:21 -0400
Received: from compute2.internal (compute2.nyi.internal [10.202.2.42])
        by mailforward.west.internal (Postfix) with ESMTP id C9809B64;
        Wed, 28 Apr 2021 10:24:35 -0400 (EDT)
Received: from mailfrontend1 ([10.202.2.162])
  by compute2.internal (MEProxy); Wed, 28 Apr 2021 10:24:36 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=
        messagingengine.com; h=cc:content-transfer-encoding:date:from
        :message-id:mime-version:subject:to:x-me-proxy:x-me-proxy
        :x-me-sender:x-me-sender:x-sasl-enc; s=fm2; bh=HQQ7SpOqqpIwy1otx
        y1mWGf90mk55isIJKpzIEWUu1w=; b=O+5/nHzHlRhTl3zn3jPZx5Ni81cln3oao
        vlOjqg6LWgvXJrqOv8obs4fRaPxz2cPnvQXpHhSsJht3lZcjlUf1MSaK0iclkiUF
        PrAhdUPFdQczW7hfLE2ifucktETeVqwE23oVIkfz7W6teKVNkMwWExUxj9oFiizs
        d3+tuqhNAptxyeK+MXLL+5XAJsPSYGcoBYGaK4TmsT1P2Png2jja/qV+W2X3dNdM
        ENpqomCe0HBJrOeyYZ5IwPlTzKlKKFfPCqaU16ZBlu59t1ScQZK0rFUEv/vVrDCx
        lXMhsv6CEQjEk6n2ku+J/28OujVljr2mMVXFEQi3QXe5rtl4Wrv8g==
X-ME-Sender: <xms:InCJYDrxundC7WYciFjOmv2ygrpJ74plT-1tgE3QNiT86yqRcU3wgw>
    <xme:InCJYNrtwORwdx_yk2wjh8CKyGszyCTLjkQ12WUX8kL-biEnYSlvX9qngaQbTxwA2
    yOC0iKheOpqdbgNaME>
X-ME-Proxy-Cause: 
 gggruggvucftvghtrhhoucdtuddrgeduledrvddvvddgheduucetufdoteggodetrfdotf
    fvucfrrhhofhhilhgvmecuhfgrshhtofgrihhlpdfqfgfvpdfurfetoffkrfgpnffqhgen
    uceurghilhhouhhtmecufedttdenucesvcftvggtihhpihgvnhhtshculddquddttddmne
    cujfgurhephffvufffkffoggfgsedtkeertdertddtnecuhfhrohhmpeffrghvihguucfg
    ughmohhnughsohhnuceouggrvhhiugdrvggumhhonhgushhonhesohhrrggtlhgvrdgtoh
    hmqeenucggtffrrghtthgvrhhnpeduhfetvdfhgfeltddtgeelheetveeufeegteevtddu
    iedvgeejhfdukeegteehheenucfkphepkedurddukeejrddviedrvdefkeenucevlhhush
    htvghrufhiiigvpedtnecurfgrrhgrmhepmhgrihhlfhhrohhmpegurghvihgurdgvughm
    ohhnughsohhnsehorhgrtghlvgdrtghomh
X-ME-Proxy: <xmx:InCJYAN6LwT4F_kI-ZrSJDsYSOal9EHWCwOLABuSbw5efip584eLXA>
    <xmx:InCJYG4Rfck2DvMzNI4VuZbwFJTvMLIMgIkQOv9owGXXOV6tFyRLNw>
    <xmx:InCJYC4EldmNbbTlIWMexAUYRyxGTgAazj-35dUTwHF2DNTm86TwQQ>
    <xmx:I3CJYPz9HB7OH-lak-hCi56L6NnX36Ww0D5UBexpmEW3ItPFvTAyRZq_yO0>
Received: from disaster-area.hh.sledj.net (disaster-area.hh.sledj.net
 [81.187.26.238])
        by mail.messagingengine.com (Postfix) with ESMTPA;
        Wed, 28 Apr 2021 10:24:33 -0400 (EDT)
Received: from localhost (disaster-area.hh.sledj.net [local])
        by disaster-area.hh.sledj.net (OpenSMTPD) with ESMTPA id b1bbd0bf;
        Wed, 28 Apr 2021 14:24:31 +0000 (UTC)
From: David Edmondson <david.edmondson@oracle.com>
To: qemu-devel@nongnu.org
Cc: qemu-trivial@nongnu.org, Paolo Bonzini <pbonzini@redhat.com>,
        kvm@vger.kernel.org, David Edmondson <david.edmondson@oracle.com>
Subject: [PATCH] accel: kvm: clarify that extra exit data is hexadecimal
Date: Wed, 28 Apr 2021 15:24:31 +0100
Message-Id: <20210428142431.266879-1-david.edmondson@oracle.com>
X-Mailer: git-send-email 2.30.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When dumping the extra exit data provided by KVM, make it clear that
the data is hexadecimal.

At the same time, zero-pad the output.

Signed-off-by: David Edmondson <david.edmondson@oracle.com>
Reviewed-by: Philippe Mathieu-Daudé <philmd@redhat.com>
---
 accel/kvm/kvm-all.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH v1 1/4] arm64: split its-trigger test into KVM and TCG variants
##### From: =?utf-8?q?Alex_Benn=C3=A9e?= <alex.bennee@linaro.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Alex_Benn=C3=A9e?= <alex.bennee@linaro.org>
X-Patchwork-Id: 12228503
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D9086C433B4
	for <kvm@archiver.kernel.org>; Wed, 28 Apr 2021 10:18:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A894F61431
	for <kvm@archiver.kernel.org>; Wed, 28 Apr 2021 10:18:52 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S239185AbhD1KTg (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 28 Apr 2021 06:19:36 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:34522 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S236343AbhD1KTf (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 28 Apr 2021 06:19:35 -0400
Received: from mail-wm1-x32f.google.com (mail-wm1-x32f.google.com
 [IPv6:2a00:1450:4864:20::32f])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 84333C06138B
        for <kvm@vger.kernel.org>; Wed, 28 Apr 2021 03:18:50 -0700 (PDT)
Received: by mail-wm1-x32f.google.com with SMTP id g65so4306726wmg.2
        for <kvm@vger.kernel.org>; Wed, 28 Apr 2021 03:18:50 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=linaro.org; s=google;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=W/65gl/q8IPHxxfmkIEqzGwlIffS1aBvU9xDbEnZyHM=;
        b=SSrrTtwZJ02Zr0JA6NRj0GmP0uyFPOUSFabhokoV6Sy5GNCyllTC4VWQMLE81igmUe
         Wh0Vi6utYveAA/fpekiI7G8ty768Nqo3K2LOp81FzggyzgrXoRp1v5KCSAMdAMjCuyuX
         r9IM1GiXmva9cV/s22qi9+5GmGGbvx5LX8EDykKoW42J+NlR2k9rKWnZXSzadxTkzeUd
         8J/bswhnJIBlc10SW99J5bPaBrR8JUigyAKh1GY1S03X1swxtLM4p+pB0ZXIwfxYh19v
         CSzoeIhOjW5U/V0rLWA1tjAH0VlGLBK6V5mrPM0R1DcsKn2suEmABcoaH6S5DiU8qNgM
         REDA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=W/65gl/q8IPHxxfmkIEqzGwlIffS1aBvU9xDbEnZyHM=;
        b=EyXLYwaApc/BnKMcdUWfNG7cEoLTuikEDK4l8CkIS5S91eH8/0nmGX1q/WMGEXmagR
         V6nhu6neKm66JKU8OTuFMFOH/E0MC6pf3qvsN8q521hz7Ya0A2YaC10J72yhVvjU8aIX
         m4t5VWCAKn7B8iLAGLXVfp0HNjanFoY82fVHAndBVe1i/QdSxuKAOkjA7Zmmvf97SxFB
         zZgQ59f5PY4CvBgJXKI980wfRhmMCWs0nwQqzMbk3wYI6vvfku6CJ1vHX8shwzoX6IhI
         9RCArz06WaakPnYdVm8lzD8kZoGw1/HghkKVBkBgD6IBOSqGCZOdX+e5yf8ZhJsqy/H9
         39Zg==
X-Gm-Message-State: AOAM530nmbKpqhr30SMa18rGysyfcDLlPf22vNTcN84SqjrCtPkAYrxV
        gPQxEFKTUr+a6Bff3UXfxQ2f6g==
X-Google-Smtp-Source: 
 ABdhPJxRO3MjPBAuuf7/5yeRHIOMTjCLbzPgeFWy3MG9Ge5F6gbUkBS3K7ic1Vpc5z70bIjpSShKyA==
X-Received: by 2002:a7b:cd85:: with SMTP id y5mr3586309wmj.93.1619605129193;
        Wed, 28 Apr 2021 03:18:49 -0700 (PDT)
Received: from zen.linaroharston ([51.148.130.216])
        by smtp.gmail.com with ESMTPSA id
 b14sm7950544wrf.75.2021.04.28.03.18.44
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 28 Apr 2021 03:18:44 -0700 (PDT)
Received: from zen.lan (localhost [127.0.0.1])
        by zen.linaroharston (Postfix) with ESMTP id 27D401FF87;
        Wed, 28 Apr 2021 11:18:44 +0100 (BST)
From: =?utf-8?q?Alex_Benn=C3=A9e?= <alex.bennee@linaro.org>
To: kvm@vger.kernel.org
Cc: shashi.mallela@linaro.org, alexandru.elisei@arm.com,
 eric.auger@redhat.com, qemu-arm@nongnu.org,
 linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
 christoffer.dall@arm.com, maz@kernel.org,
 =?utf-8?q?Alex_Benn=C3=A9e?= <alex.bennee@linaro.org>
Subject: [kvm-unit-tests PATCH v1 1/4] arm64: split its-trigger test into KVM
 and TCG variants
Date: Wed, 28 Apr 2021 11:18:41 +0100
Message-Id: <20210428101844.22656-2-alex.bennee@linaro.org>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20210428101844.22656-1-alex.bennee@linaro.org>
References: <20210428101844.22656-1-alex.bennee@linaro.org>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

A few of the its-trigger tests rely on IMPDEF behaviour where caches
aren't flushed before invall events. However TCG emulation doesn't
model any invall behaviour and as we can't probe for it we need to be
told. Split the test into a KVM and TCG variant and skip the invall
tests when under TCG.

Signed-off-by: Alex Bennée <alex.bennee@linaro.org>
Cc: Shashi Mallela <shashi.mallela@linaro.org>
---
 arm/gic.c         | 60 +++++++++++++++++++++++++++--------------------
 arm/unittests.cfg | 11 ++++++++-
 2 files changed, 45 insertions(+), 26 deletions(-)

```
#### [GIT PULL] KVM, AMD PSP and ARM CoreSight changes for 5.13 merge window
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 12230215
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,INCLUDES_PULL_REQUEST,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,
	SPF_HELO_NONE,SPF_PASS autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 2F7A9C433B4
	for <kvm@archiver.kernel.org>; Wed, 28 Apr 2021 23:05:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id F05EC6144A
	for <kvm@archiver.kernel.org>; Wed, 28 Apr 2021 23:05:36 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230122AbhD1XGV (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 28 Apr 2021 19:06:21 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:32572 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S230056AbhD1XGU (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 28 Apr 2021 19:06:20 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1619651133;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=hGwasNCNhnHl4l91Dy18SMDiEbF+EtHDi2uduzYhTyo=;
        b=QKgn3laqcgn/lhTuDP0HahaFj89gLcs5t8LNcTMfV4Qe3UyE0lFMYtGPym0Es9AWdZOQfb
        Xf3LtF6rvwAesQtrpvEVQGdl0HvQuWW+2YsuA02Jw9BH8+9zZzmutR8ZL6YTcvvJULPGj5
        xcT5khkhJm+st0Tmz2I+xuHBEtsEpEw=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-145-X5nI_K2MNGS59HhVH5CR4w-1; Wed, 28 Apr 2021 19:05:31 -0400
X-MC-Unique: X5nI_K2MNGS59HhVH5CR4w-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 748BF18B9ECA;
        Wed, 28 Apr 2021 23:05:29 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 9701962467;
        Wed, 28 Apr 2021 23:05:28 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: torvalds@linux-foundation.org
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        Mathieu Poirier <mathieu.poirier@linaro.org>,
        Marc Zyngier <maz@kernel.org>,
        Herbert Xu <herbert@gondor.apana.org.au>
Subject: [GIT PULL] KVM,
 AMD PSP and ARM CoreSight changes for 5.13 merge window
Date: Wed, 28 Apr 2021 19:05:28 -0400
Message-Id: <20210428230528.189146-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Linus,

The following changes since commit 523caed9efbb049339706b124185c9358c1b6477:

  x86/sgx: Mark sgx_vepc_vm_ops static (2021-04-12 19:48:32 +0200)

are available in the Git repository at:

  https://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to 3bf0fcd754345d7ea63e1446015ba65ece6788ca:

  KVM: selftests: Speed up set_memory_region_test (2021-04-26 12:21:27 -0400)


It's a fairly large pull request for KVM standards.  There were quite
a few common topic branches and crossover series with other trees,
especially within KVM ARM, which I need to mention explicitly.
In particular:

- the coresight/next-ETE-TRBE branch from the KVM ARM tree hasn't yet
reached you, so I am CCing the maintainer.  Since he sent the patches
as a pull request to Marc Zyngier (the KVM ARM maintainer) at
https://lore.kernel.org/kvmarm/20210406224437.330939-1-mathieu.poirier@linaro.org/T/#u,
I actually suspect that from his point of view he's done.

- Herbert Xu and Tom Lendacky asked to include AMD PSP driver changes
in this pull request

- the KVM ARM tree also brought in a handful of "Get rid of oprofile
leftovers" patches for other architectures, but they all have maintainer
acks and are just cleanups, so I am a bit less worried there.

I hope all this is okay.


Despite the juggling of topic branches, a couple conflicts escaped:

- the worst is with the tip rework of x86 TLB flushes.  Basically, tip
renamed kvm_flush_tlb_others to kvm_flush_tlb_multi, added a comment and
moved it to a different position.  KVM moved it somewhere else, so after
merging you'll have both kvm_flush_tlb_multi and kvm_flush_tlb_others.
You need to take kvm_flush_tlb_multi and paste it in place of
kvm_flush_tlb_others.  For everything else the KVM code is the correct
one, again except for s/kvm_flush_tlb_others/kvm_flush_tlb_multi/.
I have placed the relevant hunks of the "diff --combined" output at the
end of this message.

- arch/mips/kvm/trap_emul.c has been deleted in the MIPS tree, which
will cause a modify/delete conflict either now or when merging the
MIPS tree.  The conflict is of course solved just by deleting the file.
For the future, Thomas Bogendorfer will either not take KVM patches or
ensure that we have a common topic branch.


Thanks,

Paolo

----------------------------------------------------------------
ARM:

- Stage-2 isolation for the host kernel when running in protected mode

- Guest SVE support when running in nVHE mode

- Force W^X hypervisor mappings in nVHE mode

- ITS save/restore for guests using direct injection with GICv4.1

- nVHE panics now produce readable backtraces

- Guest support for PTP using the ptp_kvm driver

- Performance improvements in the S2 fault handler

x86:

- Optimizations and cleanup of nested SVM code

- AMD: Support for virtual SPEC_CTRL

- Optimizations of the new MMU code: fast invalidation,
  zap under read lock, enable/disably dirty page logging under
  read lock

- /dev/kvm API for AMD SEV live migration (guest API coming soon)

- support SEV virtual machines sharing the same encryption context

- support SGX in virtual machines

- add a few more statistics

- improved directed yield heuristics

- Lots and lots of cleanups

Generic:

- Rework of MMU notifier interface, simplifying and optimizing
the architecture-specific code

- Some selftests improvements

----------------------------------------------------------------
Alexandru Elisei (4):
      Documentation: KVM: Document KVM_GUESTDBG_USE_HW control flag for arm64
      KVM: arm64: Initialize VCPU mdcr_el2 before loading it
      KVM: arm64: Don't print warning when trapping SPE registers
      KVM: arm64: Don't advertise FEAT_SPE to guests

Andrew Scull (5):
      bug: Remove redundant condition check in report_bug
      bug: Factor out a getter for a bug's file line
      bug: Assign values once in bug_get_file_line()
      KVM: arm64: Use BUG and BUG_ON in nVHE hyp
      KVM: arm64: Log source when panicking from nVHE hyp

Anshuman Khandual (5):
      arm64: Add TRBE definitions
      coresight: core: Add support for dedicated percpu sinks
      coresight: sink: Add TRBE driver
      Documentation: coresight: trbe: Sysfs ABI description
      Documentation: trace: Add documentation for TRBE

Babu Moger (2):
      x86/cpufeatures: Add the Virtual SPEC_CTRL feature
      KVM: SVM: Add support for Virtual SPEC_CTRL

Ben Gardon (13):
      KVM: x86/mmu: Re-add const qualifier in kvm_tdp_mmu_zap_collapsible_sptes
      KVM: x86/mmu: Move kvm_mmu_(get|put)_root to TDP MMU
      KVM: x86/mmu: use tdp_mmu_free_sp to free roots
      KVM: x86/mmu: Merge TDP MMU put and free root
      KVM: x86/mmu: Refactor yield safe root iterator
      KVM: x86/mmu: Make TDP MMU root refcount atomic
      KVM: x86/mmu: handle cmpxchg failure in kvm_tdp_mmu_get_root
      KVM: x86/mmu: Protect the tdp_mmu_roots list with RCU
      KVM: x86/mmu: Allow zap gfn range to operate under the mmu read lock
      KVM: x86/mmu: Allow zapping collapsible SPTEs to use MMU read lock
      KVM: x86/mmu: Allow enabling/disabling dirty logging under MMU read lock
      KVM: x86/mmu: Fast invalidation for TDP MMU
      KVM: x86/mmu: Tear down roots before kvm_mmu_zap_all_fast returns

Bhaskar Chowdhury (1):
      KVM: s390: Fix comment spelling in kvm_s390_vcpu_start()

Brijesh Singh (6):
      KVM: SVM: Add KVM_SEV SEND_START command
      KVM: SVM: Add KVM_SEND_UPDATE_DATA command
      KVM: SVM: Add KVM_SEV_SEND_FINISH command
      KVM: SVM: Add support for KVM_SEV_RECEIVE_START command
      KVM: SVM: Add KVM_SEV_RECEIVE_UPDATE_DATA command
      KVM: SVM: Add KVM_SEV_RECEIVE_FINISH command

Cathy Avery (4):
      KVM: SVM: Use a separate vmcb for the nested L2 guest
      KVM: nSVM: Track the physical cpu of the vmcb vmrun through the vmcb
      KVM: nSVM: Track the ASID generation of the vmcb vmrun through the vmcb
      KVM: nSVM: Optimize vmcb12 to vmcb02 save area copies

Claudio Imbrenda (5):
      KVM: s390: split kvm_s390_logical_to_effective
      KVM: s390: extend kvm_s390_shadow_fault to return entry pointer
      KVM: s390: VSIE: correctly handle MVPG when in VSIE
      KVM: s390: split kvm_s390_real_to_abs
      KVM: s390: VSIE: fix MVPG handling for prefixing and MSO

Daniel Kiss (1):
      KVM: arm64: Enable SVE support for nVHE

David Brazdil (1):
      KVM: arm64: Support PREL/PLT relocs in EL2 code

David Edmondson (5):
      KVM: x86: dump_vmcs should not assume GUEST_IA32_EFER is valid
      KVM: x86: dump_vmcs should not conflate EFER and PAT presence in VMCS
      KVM: x86: dump_vmcs should consider only the load controls of EFER/PAT
      KVM: x86: dump_vmcs should show the effective EFER
      KVM: x86: dump_vmcs should include the autoload/autostore MSR lists

Dongli Zhang (1):
      KVM: x86: to track if L1 is running L2 VM

Emanuele Giuseppe Esposito (1):
      doc/virt/kvm: move KVM_CAP_PPC_MULTITCE in section 8

Eric Auger (11):
      KVM: arm64: vgic-v3: Fix some error codes when setting RDIST base
      KVM: arm64: Fix KVM_VGIC_V3_ADDR_TYPE_REDIST_REGION read
      KVM: arm64: vgic-v3: Fix error handling in vgic_v3_set_redist_base()
      KVM: arm/arm64: vgic: Reset base address on kvm_vgic_dist_destroy()
      docs: kvm: devices/arm-vgic-v3: enhance KVM_DEV_ARM_VGIC_CTRL_INIT doc
      KVM: arm64: Simplify argument passing to vgic_uaccess_[read|write]
      kvm: arm64: vgic-v3: Introduce vgic_v3_free_redist_region()
      KVM: arm64: vgic-v3: Expose GICR_TYPER.Last for userspace
      KVM: selftests: aarch64/vgic-v3 init sequence tests
      KVM: selftests: vgic_init kvm selftests fixup
      KVM: arm/arm64: Fix KVM_VGIC_V3_ADDR_TYPE_REDIST read

Gavin Shan (3):
      KVM: arm64: Hide kvm_mmu_wp_memory_region()
      KVM: arm64: Use find_vma_intersection()
      KVM: arm64: Don't retrieve memory slot again in page fault handler

Haiwei Li (2):
      KVM: vmx: add mismatched size assertions in vmcs_check32()
      KVM: x86: Take advantage of kvm_arch_dy_has_pending_interrupt()

Heiko Carstens (1):
      KVM: s390: fix guarded storage control register handling

Isaku Yamahata (1):
      KVM: VMX: use EPT_VIOLATION_GVA_TRANSLATED instead of 0x100

Jianyong Wu (4):
      ptp: Reorganize ptp_kvm.c to make it arch-independent
      clocksource: Add clocksource id for arm arch counter
      KVM: arm64: Add support for the KVM PTP service
      ptp: arm/arm64: Enable ptp_kvm for arm/arm64

Jon Hunter (1):
      ptp: Don't print an error if ptp_kvm is not supported

Keqian Zhu (1):
      KVM: x86: Remove unused function declaration

Krish Sadhukhan (4):
      KVM: nSVM: Add missing checks for reserved bits to svm_set_nested_state()
      KVM: nSVM: If VMRUN is single-stepped, queue the #DB intercept in nested_svm_vmexit()
      KVM: SVM: Define actual size of IOPM and MSRPM tables
      nSVM: Check addresses of MSR and IO permission maps

Marc Zyngier (47):
      KVM: arm64: Provide KVM's own save/restore SVE primitives
      KVM: arm64: Use {read,write}_sysreg_el1 to access ZCR_EL1
      KVM: arm64: Let vcpu_sve_pffr() handle HYP VAs
      KVM: arm64: Introduce vcpu_sve_vq() helper
      arm64: sve: Provide a conditional update accessor for ZCR_ELx
      KVM: arm64: Rework SVE host-save/guest-restore
      KVM: arm64: Map SVE context at EL2 when available
      KVM: arm64: Save guest's ZCR_EL1 before saving the FPSIMD state
      KVM: arm64: Trap host SVE accesses when the FPSIMD state is dirty
      KVM: arm64: Save/restore SVE state for nVHE
      arm64: Use INIT_SCTLR_EL1_MMU_OFF to disable the MMU on CPU restart
      KVM: arm64: Use INIT_SCTLR_EL2_MMU_OFF to disable the MMU on KVM teardown
      KVM: arm64: Turn SCTLR_ELx_FLAGS into INIT_SCTLR_EL2_MMU_ON
      KVM: arm64: Force SCTLR_EL2.WXN when running nVHE
      KVM: arm64: Fix host's ZCR_EL2 restore on nVHE
      Merge tag 'v5.12-rc3' into kvm-arm64/host-stage2
      irqchip/gic-v3-its: Add a cache invalidation right after vPE unmapping
      KVM: arm64: Generate final CTR_EL0 value when running in Protected mode
      KVM: arm64: Drop the CPU_FTR_REG_HYP_COPY infrastructure
      KVM: arm64: Elect Alexandru as a replacement for Julien as a reviewer
      KVM: arm64: Mark the kvmarm ML as moderated for non-subscribers
      KVM: arm64: Fix table format for PTP documentation
      Merge remote-tracking branch 'coresight/next-ETE-TRBE' into kvmarm-master/next
      KVM: arm64: Clarify vcpu reset behaviour
      KVM: arm64: Fully zero the vcpu state on reset
      Merge branch 'kvm-arm64/debug-5.13' into kvmarm-master/next
      Merge branch 'kvm-arm64/host-stage2' into kvmarm-master/next
      Merge branch 'kvm-arm64/memslot-fixes' into kvmarm-master/next
      Merge branch 'kvm-arm64/misc-5.13' into kvmarm-master/next
      Merge branch 'kvm-arm64/nvhe-panic-info' into kvmarm-master/next
      Merge branch 'kvm-arm64/nvhe-sve' into kvmarm-master/next
      Merge branch 'kvm-arm64/nvhe-wxn' into kvmarm-master/next
      Merge branch 'kvm-arm64/ptp' into kvmarm-master/next
      Merge branch 'kvm-arm64/vgic-5.13' into kvmarm-master/next
      Merge branch 'kvm-arm64/vlpi-save-restore' into kvmarm-master/next
      Merge remote-tracking branch 'arm64/for-next/vhe-only' into kvmarm-master/next
      Merge remote-tracking branch 'arm64/for-next/neon-softirqs-disabled' into kvmarm-master/next
      Merge remote-tracking branch 'coresight/next-ETE-TRBE' into kvmarm-master/next
      bug: Provide dummy version of bug_get_file_line() when !GENERIC_BUG
      Merge branch 'kvm-arm64/nvhe-panic-info' into kvmarm-master/next
      Merge branch 'kvm-arm64/ptp' into kvmarm-master/next
      KVM: arm64: Divorce the perf code from oprofile helpers
      arm64: Get rid of oprofile leftovers
      s390: Get rid of oprofile leftovers
      sh: Get rid of oprofile leftovers
      perf: Get rid of oprofile leftovers
      Merge branch 'kvm-arm64/kill_oprofile_dependency' into kvmarm-master/next

Maxim Levitsky (10):
      KVM: nSVM: always use vmcb01 to for vmsave/vmload of guest state
      KVM: x86: determine if an exception has an error code only when injecting it.
      KVM: x86: mmu: initialize fault.async_page_fault in walk_addr_generic
      KVM: x86: add guest_cpuid_is_intel
      KVM: nSVM: improve SYSENTER emulation on AMD
      KVM: nSVM: call nested_svm_load_cr3 on nested state load
      KVM: x86: pending exceptions must not be blocked by an injected event
      KVM: x86: implement KVM_CAP_SET_GUEST_DEBUG2
      KVM: aarch64: implement KVM_CAP_SET_GUEST_DEBUG2
      KVM: s390x: implement KVM_CAP_SET_GUEST_DEBUG2

Nathan Tempelman (1):
      KVM: x86: Support KVM VMs sharing SEV context

Paolo Bonzini (27):
      KVM: nSVM: rename functions and variables according to vmcbXY nomenclature
      KVM: nSVM: do not copy vmcb01->control blindly to vmcb02->control
      KVM: nSVM: do not mark all VMCB01 fields dirty on nested vmexit
      KVM: nSVM: do not mark all VMCB02 fields dirty on nested vmexit
      KVM: nSVM: only copy L1 non-VMLOAD/VMSAVE data in svm_set_nested_state()
      KVM: SVM: merge update_cr0_intercept into svm_set_cr0
      KVM: SVM: Pass struct kvm_vcpu to exit handlers (and many, many other places)
      KVM: SVM: move VMLOAD/VMSAVE to C code
      Merge branch 'kvm-fix-svm-races' into HEAD
      Merge branch 'kvm-tdp-fix-flushes' into HEAD
      Merge branch 'kvm-tdp-fix-rcu' into HEAD
      Merge tag 'kvm-s390-next-5.13-1' of git://git.kernel.org/pub/scm/linux/kernel/git/kvms390/linux into HEAD
      Merge tag 'kvm-s390-next-5.13-2' of git://git.kernel.org/pub/scm/linux/kernel/git/kvms390/linux into HEAD
      Merge remote-tracking branch 'tip/x86/sgx' into kvm-next
      KVM: MMU: load PDPTRs outside mmu_lock
      KVM: introduce KVM_CAP_SET_GUEST_DEBUG2
      KVM: MMU: protect TDP MMU pages only down to required level
      KVM: constify kvm_arch_flush_remote_tlbs_memslot
      KVM: MIPS: rework flush_shadow_* callbacks into one that prepares the flush
      KVM: MIPS: let generic code call prepare_flush_shadow
      KVM: MIPS: defer flush to generic MMU notifier code
      KVM: selftests: Always run vCPU thread with blocked SIG_IPI
      KVM: x86: document behavior of measurement ioctls with len==0
      Merge branch 'kvm-sev-cgroup' into HEAD
      Merge tag 'kvmarm-5.13' of git://git.kernel.org/pub/scm/linux/kernel/git/kvmarm/kvmarm into HEAD
      KVM: documentation: fix sphinx warnings
      KVM: SEV: Mask CPUID[0x8000001F].eax according to supported features

Peter Xu (1):
      KVM: selftests: Sync data verify of dirty logging with guest sync

Pierre Morel (1):
      KVM: s390: diag9c (directed yield) forwarding

Quentin Perret (35):
      KVM: arm64: Initialize kvm_nvhe_init_params early
      KVM: arm64: Avoid free_page() in page-table allocator
      KVM: arm64: Factor memory allocation out of pgtable.c
      KVM: arm64: Introduce a BSS section for use at Hyp
      KVM: arm64: Make kvm_call_hyp() a function call at Hyp
      KVM: arm64: Allow using kvm_nvhe_sym() in hyp code
      KVM: arm64: Introduce an early Hyp page allocator
      KVM: arm64: Stub CONFIG_DEBUG_LIST at Hyp
      KVM: arm64: Introduce a Hyp buddy page allocator
      KVM: arm64: Enable access to sanitized CPU features at EL2
      KVM: arm64: Provide __flush_dcache_area at EL2
      KVM: arm64: Factor out vector address calculation
      arm64: asm: Provide set_sctlr_el2 macro
      KVM: arm64: Prepare the creation of s1 mappings at EL2
      KVM: arm64: Elevate hypervisor mappings creation at EL2
      KVM: arm64: Use kvm_arch for stage 2 pgtable
      KVM: arm64: Use kvm_arch in kvm_s2_mmu
      KVM: arm64: Set host stage 2 using kvm_nvhe_init_params
      KVM: arm64: Refactor kvm_arm_setup_stage2()
      KVM: arm64: Refactor __load_guest_stage2()
      KVM: arm64: Refactor __populate_fault_info()
      KVM: arm64: Make memcache anonymous in pgtable allocator
      KVM: arm64: Reserve memory for host stage 2
      KVM: arm64: Sort the hypervisor memblocks
      KVM: arm64: Always zero invalid PTEs
      KVM: arm64: Use page-table to track page ownership
      KVM: arm64: Refactor the *_map_set_prot_attr() helpers
      KVM: arm64: Add kvm_pgtable_stage2_find_range()
      KVM: arm64: Introduce KVM_PGTABLE_S2_NOFWB stage 2 flag
      KVM: arm64: Introduce KVM_PGTABLE_S2_IDMAP stage 2 flag
      KVM: arm64: Provide sanitized mmfr* registers at EL2
      KVM: arm64: Wrap the host with a stage 2
      KVM: arm64: Page-align the .hyp sections
      KVM: arm64: Disable PMU support in protected mode
      KVM: arm64: Protect the .hyp sections from the host

Ricardo Koller (1):
      KVM: x86: Move reverse CPUID helpers to separate header file

Sean Christopherson (147):
      KVM: x86/mmu: Alloc page for PDPTEs when shadowing 32-bit NPT with 64-bit
      KVM: x86/mmu: Capture 'mmu' in a local variable when allocating roots
      KVM: x86/mmu: Allocate the lm_root before allocating PAE roots
      KVM: x86/mmu: Allocate pae_root and lm_root pages in dedicated helper
      KVM: x86/mmu: Ensure MMU pages are available when allocating roots
      KVM: x86/mmu: Check PDPTRs before allocating PAE roots
      KVM: x86/mmu: Fix and unconditionally enable WARNs to detect PAE leaks
      KVM: x86/mmu: Set the C-bit in the PDPTRs and LM pseudo-PDPTRs
      KVM: nVMX: Defer the MMU reload to the normal path on an EPTP switch
      KVM: x86: Defer the MMU unload to the normal path on an global INVPCID
      KVM: x86/mmu: Unexport MMU load/unload functions
      KVM: x86/mmu: Sync roots after MMU load iff load as successful
      KVM: x86/mmu: WARN on NULL pae_root or lm_root, or bad shadow root level
      KVM: SVM: Don't strip the C-bit from CR2 on #PF interception
      KVM: nSVM: Set the shadow root level to the TDP level for nested NPT
      KVM: x86: Move nVMX's consistency check macro to common code
      KVM: nSVM: Trace VM-Enter consistency check failures
      KVM: x86: Handle triple fault in L2 without killing L1
      KVM: nSVM: Add helper to synthesize nested VM-Exit without collateral
      KVM: nSVM: Add VMLOAD/VMSAVE helper to deduplicate code
      KVM: x86: Move XSETBV emulation to common code
      KVM: x86: Move trivial instruction-based exit handlers to common code
      KVM: x86: Move RDPMC emulation to common code
      KVM: SVM: Don't manually emulate RDPMC if nrips=0
      KVM: SVM: Skip intercepted PAUSE instructions after emulation
      KVM: x86/mmu: Remove spurious TLB flush from TDP MMU's change_pte() hook
      KVM: x86/mmu: WARN if TDP MMU's set_tdp_spte() sees multiple GFNs
      KVM: x86/mmu: Use 'end' param in TDP MMU's test_age_gfn()
      KVM: x86/mmu: Add typedefs for rmap/iter handlers
      KVM: x86/mmu: Add convenience wrapper for acting on single hva in TDP MMU
      KVM: x86/mmu: Check for shadow-present SPTE before querying A/D status
      KVM: x86/mmu: Bail from fast_page_fault() if SPTE is not shadow-present
      KVM: x86/mmu: Disable MMIO caching if MMIO value collides with L1TF
      KVM: x86/mmu: Retry page faults that hit an invalid memslot
      KVM: x86/mmu: Don't install bogus MMIO SPTEs if MMIO caching is disabled
      KVM: x86/mmu: Handle MMIO SPTEs directly in mmu_set_spte()
      KVM: x86/mmu: Drop redundant trace_kvm_mmu_set_spte() in the TDP MMU
      KVM: x86/mmu: Rename 'mask' to 'spte' in MMIO SPTE helpers
      KVM: x86/mmu: Stop using software available bits to denote MMIO SPTEs
      KVM: x86/mmu: Add module param to disable MMIO caching (for testing)
      KVM: x86/mmu: Rename and document A/D scheme for TDP SPTEs
      KVM: x86/mmu: Use MMIO SPTE bits 53 and 52 for the MMIO generation
      KVM: x86/mmu: Document dependency bewteen TDP A/D type and saved bits
      KVM: x86/mmu: Move initial kvm_mmu_set_mask_ptes() call into MMU proper
      KVM: x86/mmu: Co-locate code for setting various SPTE masks
      KVM: x86/mmu: Move logic for setting SPTE masks for EPT into the MMU proper
      KVM: x86/mmu: Make Host-writable and MMU-writable bit locations dynamic
      KVM: x86/mmu: Use high bits for host/mmu writable masks for EPT SPTEs
      KVM: x86/mmu: Use a dedicated bit to track shadow/MMU-present SPTEs
      KVM: x86/mmu: Tweak auditing WARN for A/D bits to !PRESENT (was MMIO)
      KVM: x86/mmu: Use is_removed_spte() instead of open coded equivalents
      KVM: x86/mmu: Use low available bits for removed SPTEs
      KVM: x86/mmu: Dump reserved bits if they're detected on non-MMIO SPTE
      KVM: x86: Get active PCID only when writing a CR3 value
      KVM: VMX: Track common EPTP for Hyper-V's paravirt TLB flush
      KVM: VMX: Stash kvm_vmx in a local variable for Hyper-V paravirt TLB flush
      KVM: VMX: Fold Hyper-V EPTP checking into it's only caller
      KVM: VMX: Do Hyper-V TLB flush iff vCPU's EPTP hasn't been flushed
      KVM: VMX: Invalidate hv_tlb_eptp to denote an EPTP mismatch
      KVM: VMX: Don't invalidate hv_tlb_eptp if the new EPTP matches
      KVM: VMX: Explicitly check for hv_remote_flush_tlb when loading pgd
      KVM: VMX: Define Hyper-V paravirt TLB flush fields iff Hyper-V is enabled
      KVM: VMX: Skip additional Hyper-V TLB EPTP flushes if one fails
      KVM: VMX: Track root HPA instead of EPTP for paravirt Hyper-V TLB flush
      KVM: x86/mmu: Use '0' as the one and only value for an invalid PAE root
      KVM: x86/mmu: Mark the PAE roots as decrypted for shadow paging
      KVM: x86/mmu: Coalesce TDP MMU TLB flushes when zapping collapsible SPTEs
      KVM: x86/mmu: Move flushing for "slot" handlers to caller for legacy MMU
      KVM: x86/mmu: Coalesce TLB flushes when zapping collapsible SPTEs
      KVM: x86/mmu: Coalesce TLB flushes across address spaces for gfn range zap
      KVM: x86/mmu: Pass address space ID to __kvm_tdp_mmu_zap_gfn_range()
      KVM: x86/mmu: Pass address space ID to TDP MMU root walkers
      KVM: x86/mmu: Use leaf-only loop for walking TDP SPTEs when changing SPTE
      KVM: Move prototypes for MMU notifier callbacks to generic code
      KVM: Move arm64's MMU notifier trace events to generic code
      KVM: x86/mmu: Drop trace_kvm_age_page() tracepoint
      KVM: x86/mmu: Remove spurious clearing of dirty bit from TDP MMU SPTE
      KVM: x86/mmu: Simplify code for aging SPTEs in TDP MMU
      KVM: SVM: Use online_vcpus, not created_vcpus, to iterate over vCPUs
      KVM: SVM: Do not set sev->es_active until KVM_SEV_ES_INIT completes
      KVM: SVM: Do not allow SEV/SEV-ES initialization after vCPUs are created
      KVM: x86: Account a variety of miscellaneous allocations
      KVM: Explicitly use GFP_KERNEL_ACCOUNT for 'struct kvm_vcpu' allocations
      KVM: Assert that notifier count is elevated in .change_pte()
      KVM: Move x86's MMU notifier memslot walkers to generic code
      KVM: arm64: Convert to the gfn-based MMU notifier callbacks
      KVM: MIPS/MMU: Convert to the gfn-based MMU notifier callbacks
      KVM: PPC: Convert to the gfn-based MMU notifier callbacks
      KVM: Kill off the old hva-based MMU notifier callbacks
      KVM: Move MMU notifier's mmu_lock acquisition into common helper
      KVM: Take mmu_lock when handling MMU notifier iff the hva hits a memslot
      KVM: x86/mmu: Allow yielding during MMU notifier unmap/zap, if possible
      KVM: SVM: Don't set current_vmcb->cpu when switching vmcb
      KVM: SVM: Drop vcpu_svm.vmcb_pa
      KVM: SVM: Add a comment to clarify what vcpu_svm.vmcb points at
      KVM: SVM: Enhance and clean up the vmcb tracking comment in pre_svm_run()
      KVM: Destroy I/O bus devices on unregister failure _after_ sync'ing SRCU
      KVM: Stop looking for coalesced MMIO zones if the bus is destroyed
      KVM: Add proper lockdep assertion in I/O bus unregister
      KVM: x86: Export kvm_mmu_gva_to_gpa_{read,write}() for SGX (VMX)
      KVM: x86: Define new #PF SGX error code bit
      KVM: x86: Add support for reverse CPUID lookup of scattered features
      KVM: x86: Add reverse-CPUID lookup support for scattered SGX features
      KVM: VMX: Add basic handling of VM-Exit from SGX enclave
      KVM: VMX: Frame in ENCLS handler for SGX virtualization
      KVM: VMX: Add SGX ENCLS[ECREATE] handler to enforce CPUID restrictions
      KVM: VMX: Add emulation of SGX Launch Control LE hash MSRs
      KVM: VMX: Add ENCLS[EINIT] handler to support SGX Launch Control (LC)
      KVM: VMX: Enable SGX virtualization for SGX1, SGX2 and LC
      KVM: x86: Add capability to grant VM access to privileged SGX attribute
      crypto: ccp: Free SEV device if SEV init fails
      crypto: ccp: Detect and reject "invalid" addresses destined for PSP
      crypto: ccp: Reject SEV commands with mismatching command buffer
      crypto: ccp: Play nice with vmalloc'd memory for SEV command structs
      crypto: ccp: Use the stack for small SEV command buffers
      crypto: ccp: Use the stack and common buffer for status commands
      crypto: ccp: Use the stack and common buffer for INIT command
      KVM: SVM: Allocate SEV command structures on local stack
      KVM: x86: Fix implicit enum conversion goof in scattered reverse CPUID code
      KVM: VMX: Invert the inlining of MSR interception helpers
      KVM: SVM: Inject #GP on guest MSR_TSC_AUX accesses if RDTSCP unsupported
      KVM: SVM: Clear MSR_TSC_AUX[63:32] on write
      KVM: SVM: Delay restoration of host MSR_TSC_AUX until return to userspace
      KVM: VMX: Intercept FS/GS_BASE MSR accesses for 32-bit KVM
      KVM: x86: Remove emulator's broken checks on CR0/CR3/CR4 loads
      KVM: x86: Check CR3 GPA for validity regardless of vCPU mode
      KVM: SVM: Truncate GPR value for DR and CR accesses in !64-bit mode
      KVM: VMX: Truncate GPR value for DR and CR reads in !64-bit mode
      KVM: nVMX: Truncate bits 63:32 of VMCS field on nested check in !64-bit
      KVM: nVMX: Truncate base/index GPR value on address calc in !64-bit
      KVM: x86/xen: Drop RAX[63:32] when processing hypercall
      KVM: SVM: Use default rAX size for INVLPGA emulation
      KVM: x86: Rename GPR accessors to make mode-aware variants the defaults
      x86/sev: Drop redundant and potentially misleading 'sev_enabled'
      KVM: SVM: Zero out the VMCB array used to track SEV ASID association
      KVM: SVM: Free sev_asid_bitmap during init if SEV setup fails
      KVM: SVM: Disable SEV/SEV-ES if NPT is disabled
      KVM: SVM: Move SEV module params/variables to sev.c
      KVM: SVM: Append "_enabled" to module-scoped SEV/SEV-ES control variables
      KVM: SVM: Condition sev_enabled and sev_es_enabled on CONFIG_KVM_AMD_SEV=y
      KVM: SVM: Enable SEV/SEV-ES functionality by default (when supported)
      KVM: SVM: Unconditionally invoke sev_hardware_teardown()
      KVM: SVM: Explicitly check max SEV ASID during sev_hardware_setup()
      KVM: SVM: Move SEV VMCB tracking allocation to sev.c
      KVM: SVM: Drop redundant svm_sev_enabled() helper
      KVM: SVM: Remove an unnecessary prototype declaration of sev_flush_asids()
      KVM: SVM: Skip SEV cache flush if no ASIDs have been used

Shenming Lu (4):
      irqchip/gic-v3-its: Drop the setting of PTZ altogether
      KVM: arm64: GICv4.1: Add function to get VLPI state
      KVM: arm64: GICv4.1: Try to save VLPI state in save_pending_tables
      KVM: arm64: GICv4.1: Give a chance to save VLPI state

Steve Rutherford (1):
      KVM: SVM: Add support for KVM_SEV_SEND_CANCEL command

Suzuki K Poulose (15):
      perf: aux: Add flags for the buffer format
      perf: aux: Add CoreSight PMU buffer formats
      arm64: Add support for trace synchronization barrier
      KVM: arm64: Handle access to TRFCR_EL1
      KVM: arm64: Move SPE availability check to VCPU load
      arm64: KVM: Enable access to TRBE support for host
      coresight: etm4x: Move ETM to prohibited region for disable
      coresight: etm-perf: Allow an event to use different sinks
      coresight: Do not scan for graph if none is present
      coresight: etm4x: Add support for PE OS lock
      coresight: ete: Add support for ETE sysreg access
      coresight: ete: Add support for ETE tracing
      dts: bindings: Document device tree bindings for ETE
      coresight: etm-perf: Handle stale output handles
      dts: bindings: Document device tree bindings for Arm TRBE

Thomas Gleixner (1):
      time: Add mechanism to recognize clocksource in time_get_snapshot

Tom Lendacky (1):
      KVM: SVM: Make sure GHCB is mapped before updating

Uros Bizjak (1):
      KVM/SVM: Move vmenter.S exception fixups out of line

Vitaly Kuznetsov (3):
      KVM: x86/vPMU: Forbid reading from MSR_F15H_PERF MSRs when guest doesn't have X86_FEATURE_PERFCTR_CORE
      KVM: x86: Properly handle APF vs disabled LAPIC situation
      KVM: selftests: Speed up set_memory_region_test

Wang Wensheng (1):
      KVM: arm64: Fix error return code in init_hyp_mode()

Wanpeng Li (5):
      x86/kvm: Don't bother __pv_cpu_mask when !CONFIG_SMP
      KVM: X86: Count attempted/successful directed yield
      KVM: X86: Do not yield to self
      KVM: Boost vCPU candidate in user mode which is delivering interrupt
      KVM: X86: Fix failure to boost kernel lock holder candidate in SEV-ES guests

Wei Yongjun (2):
      coresight: core: Make symbol 'csdev_sink' static
      coresight: trbe: Fix return value check in arm_trbe_register_coresight_cpu()

Will Deacon (5):
      arm64: lib: Annotate {clear, copy}_page() as position-independent
      KVM: arm64: Link position-independent string routines into .hyp.text
      arm64: kvm: Add standalone ticket spinlock implementation for use at hyp
      arm/arm64: Probe for the presence of KVM hypervisor
      KVM: arm64: Advertise KVM UID to guests via SMCCC

Xiaofei Tan (1):
      arm64: sve: Provide sve_cond_update_zcr_vq fallback when !ARM64_SVE

Xu Jia (1):
      KVM: arm64: Make symbol '_kvm_host_prot_finalize' static

Yanan Wang (8):
      tools/headers: sync headers of asm-generic/hugetlb_encode.h
      KVM: selftests: Print the errno besides error-string in TEST_ASSERT
      KVM: selftests: Make a generic helper to get vm guest mode strings
      KVM: selftests: Add a helper to get system configured THP page size
      KVM: selftests: Add a helper to get system default hugetlb page size
      KVM: selftests: List all hugetlb src types specified with page sizes
      KVM: selftests: Adapt vm_userspace_mem_region_add to new helpers
      KVM: selftests: Add a test for kvm page table code

Yang Yingliang (1):
      KVM: selftests: remove redundant semi-colon

Zenghui Yu (2):
      KVM: arm64: GICv4.1: Restore VLPI pending state to physical side
      KVM: arm64: Fix Function ID typo for PTP_KVM service

Zhenzhong Duan (1):
      selftests: kvm: Fix the check of return value

 .../ABI/testing/sysfs-bus-coresight-devices-trbe   |   14 +
 Documentation/devicetree/bindings/arm/ete.yaml     |   75 ++
 Documentation/devicetree/bindings/arm/trbe.yaml    |   49 +
 Documentation/trace/coresight/coresight-trbe.rst   |   38 +
 Documentation/virt/kvm/amd-memory-encryption.rst   |  143 +++
 Documentation/virt/kvm/api.rst                     |  214 +++-
 Documentation/virt/kvm/arm/index.rst               |    1 +
 Documentation/virt/kvm/arm/ptp_kvm.rst             |   25 +
 Documentation/virt/kvm/devices/arm-vgic-its.rst    |    2 +-
 Documentation/virt/kvm/devices/arm-vgic-v3.rst     |    2 +-
 Documentation/virt/kvm/locking.rst                 |   49 +-
 Documentation/virt/kvm/s390-diag.rst               |   33 +
 MAINTAINERS                                        |    6 +-
 arch/arm/include/asm/hypervisor.h                  |    3 +
 arch/arm64/include/asm/assembler.h                 |   27 +-
 arch/arm64/include/asm/barrier.h                   |    1 +
 arch/arm64/include/asm/el2_setup.h                 |   13 +
 arch/arm64/include/asm/fpsimd.h                    |   11 +
 arch/arm64/include/asm/fpsimdmacros.h              |   10 +-
 arch/arm64/include/asm/hyp_image.h                 |    7 +
 arch/arm64/include/asm/hypervisor.h                |    3 +
 arch/arm64/include/asm/kvm_arm.h                   |    2 +
 arch/arm64/include/asm/kvm_asm.h                   |    9 +
 arch/arm64/include/asm/kvm_host.h                  |   55 +-
 arch/arm64/include/asm/kvm_hyp.h                   |   14 +-
 arch/arm64/include/asm/kvm_mmu.h                   |   25 +-
 arch/arm64/include/asm/kvm_pgtable.h               |  164 ++-
 arch/arm64/include/asm/pgtable-prot.h              |    4 +-
 arch/arm64/include/asm/sections.h                  |    1 +
 arch/arm64/include/asm/sysreg.h                    |   59 +-
 arch/arm64/kernel/asm-offsets.c                    |    3 +
 arch/arm64/kernel/cpu-reset.S                      |    5 +-
 arch/arm64/kernel/hyp-stub.S                       |    3 +-
 arch/arm64/kernel/image-vars.h                     |   34 +-
 arch/arm64/kernel/vmlinux.lds.S                    |   74 +-
 arch/arm64/kvm/arm.c                               |  220 +++-
 arch/arm64/kvm/debug.c                             |  118 +-
 arch/arm64/kvm/fpsimd.c                            |   26 +-
 arch/arm64/kvm/guest.c                             |   11 +-
 arch/arm64/kvm/handle_exit.c                       |   45 +
 arch/arm64/kvm/hyp/Makefile                        |    2 +-
 arch/arm64/kvm/hyp/fpsimd.S                        |   10 +
 arch/arm64/kvm/hyp/include/hyp/switch.h            |  107 +-
 arch/arm64/kvm/hyp/include/nvhe/early_alloc.h      |   14 +
 arch/arm64/kvm/hyp/include/nvhe/gfp.h              |   68 ++
 arch/arm64/kvm/hyp/include/nvhe/mem_protect.h      |   36 +
 arch/arm64/kvm/hyp/include/nvhe/memory.h           |   51 +
 arch/arm64/kvm/hyp/include/nvhe/mm.h               |   96 ++
 arch/arm64/kvm/hyp/include/nvhe/spinlock.h         |   92 ++
 arch/arm64/kvm/hyp/nvhe/Makefile                   |    9 +-
 arch/arm64/kvm/hyp/nvhe/cache.S                    |   13 +
 arch/arm64/kvm/hyp/nvhe/debug-sr.c                 |   56 +-
 arch/arm64/kvm/hyp/nvhe/early_alloc.c              |   54 +
 arch/arm64/kvm/hyp/nvhe/gen-hyprel.c               |   18 +
 arch/arm64/kvm/hyp/nvhe/host.S                     |   18 +-
 arch/arm64/kvm/hyp/nvhe/hyp-init.S                 |   54 +-
 arch/arm64/kvm/hyp/nvhe/hyp-main.c                 |   75 +-
 arch/arm64/kvm/hyp/nvhe/hyp-smp.c                  |    6 +-
 arch/arm64/kvm/hyp/nvhe/hyp.lds.S                  |    1 +
 arch/arm64/kvm/hyp/nvhe/mem_protect.c              |  279 +++++
 arch/arm64/kvm/hyp/nvhe/mm.c                       |  173 +++
 arch/arm64/kvm/hyp/nvhe/page_alloc.c               |  195 ++++
 arch/arm64/kvm/hyp/nvhe/psci-relay.c               |    4 +-
 arch/arm64/kvm/hyp/nvhe/setup.c                    |  214 ++++
 arch/arm64/kvm/hyp/nvhe/stub.c                     |   22 +
 arch/arm64/kvm/hyp/nvhe/switch.c                   |   26 +-
 arch/arm64/kvm/hyp/nvhe/tlb.c                      |    4 +-
 arch/arm64/kvm/hyp/pgtable.c                       |  410 +++++--
 arch/arm64/kvm/hyp/reserved_mem.c                  |  113 ++
 arch/arm64/kvm/hyp/vhe/switch.c                    |    4 +-
 arch/arm64/kvm/hypercalls.c                        |   80 +-
 arch/arm64/kvm/mmu.c                               |  254 +++--
 arch/arm64/kvm/perf.c                              |    7 +-
 arch/arm64/kvm/pmu-emul.c                          |    2 +-
 arch/arm64/kvm/pmu.c                               |    8 +-
 arch/arm64/kvm/reset.c                             |   51 +-
 arch/arm64/kvm/sys_regs.c                          |   16 +
 arch/arm64/kvm/trace_arm.h                         |   66 --
 arch/arm64/kvm/va_layout.c                         |    7 +
 arch/arm64/kvm/vgic/vgic-init.c                    |   12 +-
 arch/arm64/kvm/vgic/vgic-its.c                     |    6 +-
 arch/arm64/kvm/vgic/vgic-kvm-device.c              |    7 +-
 arch/arm64/kvm/vgic/vgic-mmio-v3.c                 |   81 +-
 arch/arm64/kvm/vgic/vgic-mmio.c                    |   10 +-
 arch/arm64/kvm/vgic/vgic-v3.c                      |   66 +-
 arch/arm64/kvm/vgic/vgic-v4.c                      |   38 +
 arch/arm64/kvm/vgic/vgic.h                         |    2 +
 arch/arm64/lib/clear_page.S                        |    4 +-
 arch/arm64/lib/copy_page.S                         |    4 +-
 arch/arm64/mm/init.c                               |    3 +
 arch/mips/include/asm/kvm_host.h                   |   17 +-
 arch/mips/kvm/mips.c                               |   21 +-
 arch/mips/kvm/mmu.c                                |  100 +-
 arch/mips/kvm/trap_emul.c                          |   13 +-
 arch/mips/kvm/vz.c                                 |   19 +-
 arch/powerpc/include/asm/kvm_book3s.h              |   12 +-
 arch/powerpc/include/asm/kvm_host.h                |    7 -
 arch/powerpc/include/asm/kvm_ppc.h                 |    9 +-
 arch/powerpc/kvm/book3s.c                          |   18 +-
 arch/powerpc/kvm/book3s.h                          |   10 +-
 arch/powerpc/kvm/book3s_64_mmu_hv.c                |   98 +-
 arch/powerpc/kvm/book3s_64_mmu_radix.c             |   25 +-
 arch/powerpc/kvm/book3s_hv.c                       |   12 +-
 arch/powerpc/kvm/book3s_pr.c                       |   56 +-
 arch/powerpc/kvm/e500_mmu_host.c                   |   29 +-
 arch/powerpc/kvm/trace_booke.h                     |   15 -
 arch/s390/include/asm/kvm_host.h                   |    5 +
 arch/s390/include/asm/smp.h                        |    1 +
 arch/s390/kernel/smp.c                             |    1 +
 arch/s390/kvm/diag.c                               |   31 +-
 arch/s390/kvm/gaccess.c                            |   30 +-
 arch/s390/kvm/gaccess.h                            |   60 +-
 arch/s390/kvm/kvm-s390.c                           |   15 +-
 arch/s390/kvm/kvm-s390.h                           |    8 +
 arch/s390/kvm/vsie.c                               |  109 +-
 arch/sh/kernel/perf_event.c                        |   18 -
 arch/x86/include/asm/cpufeatures.h                 |    1 +
 arch/x86/include/asm/kvm_host.h                    |   67 +-
 arch/x86/include/asm/mem_encrypt.h                 |    1 -
 arch/x86/include/asm/svm.h                         |    4 +-
 arch/x86/include/asm/vmx.h                         |    1 +
 arch/x86/include/uapi/asm/vmx.h                    |    1 +
 arch/x86/kernel/kvm.c                              |  118 +-
 arch/x86/kvm/Makefile                              |    2 +
 arch/x86/kvm/cpuid.c                               |   98 +-
 arch/x86/kvm/cpuid.h                               |  155 +--
 arch/x86/kvm/emulate.c                             |   80 +-
 arch/x86/kvm/kvm_cache_regs.h                      |   19 +-
 arch/x86/kvm/lapic.c                               |    8 +-
 arch/x86/kvm/mmu.h                                 |   23 +-
 arch/x86/kvm/mmu/mmu.c                             |  637 ++++++-----
 arch/x86/kvm/mmu/mmu_audit.c                       |    2 +-
 arch/x86/kvm/mmu/mmu_internal.h                    |   44 +-
 arch/x86/kvm/mmu/paging_tmpl.h                     |    3 +-
 arch/x86/kvm/mmu/spte.c                            |  159 ++-
 arch/x86/kvm/mmu/spte.h                            |  141 ++-
 arch/x86/kvm/mmu/tdp_mmu.c                         |  740 +++++++------
 arch/x86/kvm/mmu/tdp_mmu.h                         |   51 +-
 arch/x86/kvm/reverse_cpuid.h                       |  186 ++++
 arch/x86/kvm/svm/avic.c                            |   24 +-
 arch/x86/kvm/svm/nested.c                          |  573 ++++++----
 arch/x86/kvm/svm/sev.c                             |  922 ++++++++++++----
 arch/x86/kvm/svm/svm.c                             | 1107 +++++++++----------
 arch/x86/kvm/svm/svm.h                             |   91 +-
 arch/x86/kvm/svm/vmenter.S                         |   47 +-
 arch/x86/kvm/vmx/nested.c                          |   83 +-
 arch/x86/kvm/vmx/nested.h                          |    5 +
 arch/x86/kvm/vmx/sgx.c                             |  502 +++++++++
 arch/x86/kvm/vmx/sgx.h                             |   34 +
 arch/x86/kvm/vmx/vmcs12.c                          |    1 +
 arch/x86/kvm/vmx/vmcs12.h                          |    4 +-
 arch/x86/kvm/vmx/vmx.c                             |  432 ++++----
 arch/x86/kvm/vmx/vmx.h                             |   39 +-
 arch/x86/kvm/vmx/vmx_ops.h                         |    4 +
 arch/x86/kvm/x86.c                                 |  214 +++-
 arch/x86/kvm/x86.h                                 |   18 +-
 arch/x86/mm/mem_encrypt.c                          |   10 +-
 arch/x86/mm/mem_encrypt_identity.c                 |    1 -
 drivers/clocksource/arm_arch_timer.c               |   36 +
 drivers/crypto/ccp/sev-dev.c                       |  193 ++--
 drivers/crypto/ccp/sev-dev.h                       |    4 +-
 drivers/firmware/psci/psci.c                       |    2 +
 drivers/firmware/smccc/Makefile                    |    2 +-
 drivers/firmware/smccc/kvm_guest.c                 |   50 +
 drivers/firmware/smccc/smccc.c                     |    1 +
 drivers/hwtracing/coresight/Kconfig                |   24 +-
 drivers/hwtracing/coresight/Makefile               |    1 +
 drivers/hwtracing/coresight/coresight-core.c       |   29 +-
 drivers/hwtracing/coresight/coresight-etm-perf.c   |  119 +-
 drivers/hwtracing/coresight/coresight-etm4x-core.c |  161 ++-
 .../hwtracing/coresight/coresight-etm4x-sysfs.c    |   19 +-
 drivers/hwtracing/coresight/coresight-etm4x.h      |   83 +-
 drivers/hwtracing/coresight/coresight-platform.c   |    6 +
 drivers/hwtracing/coresight/coresight-priv.h       |    3 +
 drivers/hwtracing/coresight/coresight-trbe.c       | 1157 ++++++++++++++++++++
 drivers/hwtracing/coresight/coresight-trbe.h       |  152 +++
 drivers/irqchip/irq-gic-v3-its.c                   |   18 +-
 drivers/perf/arm_pmu.c                             |   30 -
 drivers/ptp/Kconfig                                |    2 +-
 drivers/ptp/Makefile                               |    2 +
 drivers/ptp/ptp_kvm_arm.c                          |   28 +
 drivers/ptp/{ptp_kvm.c => ptp_kvm_common.c}        |   85 +-
 drivers/ptp/ptp_kvm_x86.c                          |   97 ++
 include/kvm/arm_pmu.h                              |    4 +
 include/kvm/arm_vgic.h                             |    1 +
 include/linux/arm-smccc.h                          |   41 +
 include/linux/bug.h                                |   10 +
 include/linux/clocksource.h                        |    6 +
 include/linux/clocksource_ids.h                    |   12 +
 include/linux/coresight.h                          |   13 +
 include/linux/kvm_host.h                           |   24 +-
 include/linux/perf_event.h                         |    2 -
 include/linux/psp-sev.h                            |   18 +-
 include/linux/ptp_kvm.h                            |   19 +
 include/linux/timekeeping.h                        |   12 +-
 include/trace/events/kvm.h                         |   90 +-
 include/uapi/linux/kvm.h                           |   45 +
 include/uapi/linux/perf_event.h                    |   13 +-
 kernel/events/core.c                               |    5 -
 kernel/time/clocksource.c                          |    2 +
 kernel/time/timekeeping.c                          |    1 +
 lib/bug.c                                          |   54 +-
 tools/include/asm-generic/hugetlb_encode.h         |    3 +
 tools/testing/selftests/kvm/.gitignore             |    2 +
 tools/testing/selftests/kvm/Makefile               |    4 +
 tools/testing/selftests/kvm/aarch64/vgic_init.c    |  551 ++++++++++
 tools/testing/selftests/kvm/dirty_log_test.c       |   69 +-
 tools/testing/selftests/kvm/include/kvm_util.h     |   13 +-
 tools/testing/selftests/kvm/include/test_util.h    |   21 +-
 tools/testing/selftests/kvm/kvm_page_table_test.c  |  506 +++++++++
 tools/testing/selftests/kvm/lib/assert.c           |    4 +-
 tools/testing/selftests/kvm/lib/kvm_util.c         |  138 ++-
 tools/testing/selftests/kvm/lib/test_util.c        |  163 ++-
 .../testing/selftests/kvm/set_memory_region_test.c |   61 +-
 .../testing/selftests/kvm/x86_64/xen_shinfo_test.c |    2 +-
 virt/kvm/coalesced_mmio.c                          |   19 +-
 virt/kvm/kvm_main.c                                |  303 +++--
 217 files changed, 12444 insertions(+), 4028 deletions(-)


+++ b/arch/x86/kernel/kvm.c
@@@ -574,6 -574,49 +574,54 @@@ static void kvm_smp_send_call_func_ipi(
  	}
  }
  
 -static void kvm_flush_tlb_others(const struct cpumask *cpumask,
++static void kvm_flush_tlb_multi(const struct cpumask *cpumask,
+ 			const struct flush_tlb_info *info)
+ {
+ 	u8 state;
+ 	int cpu;
+ 	struct kvm_steal_time *src;
+ 	struct cpumask *flushmask = this_cpu_cpumask_var_ptr(__pv_cpu_mask);
+ 
+ 	cpumask_copy(flushmask, cpumask);
+ 	/*
+ 	 * We have to call flush only on online vCPUs. And
+ 	 * queue flush_on_enter for pre-empted vCPUs
+ 	 */
+ 	for_each_cpu(cpu, flushmask) {
++		/*
++		 * The local vCPU is never preempted, so we do not explicitly
++		 * skip check for local vCPU - it will never be cleared from
++		 * flushmask.
++		 */
+ 		src = &per_cpu(steal_time, cpu);
+ 		state = READ_ONCE(src->preempted);
+ 		if ((state & KVM_VCPU_PREEMPTED)) {
+ 			if (try_cmpxchg(&src->preempted, &state,
+ 					state | KVM_VCPU_FLUSH_TLB))
+ 				__cpumask_clear_cpu(cpu, flushmask);
+ 		}
+ 	}
+ 
 -	native_flush_tlb_others(flushmask, info);
++	native_flush_tlb_multi(flushmask, info);
+ }
+ 
+ static __init int kvm_alloc_cpumask(void)
+ {
+ 	int cpu;
+ 
+ 	if (!kvm_para_available() || nopv)
+ 		return 0;
+ 
+ 	if (pv_tlb_flush_supported() || pv_ipi_supported())
+ 		for_each_possible_cpu(cpu) {
+ 			zalloc_cpumask_var_node(per_cpu_ptr(&__pv_cpu_mask, cpu),
+ 				GFP_KERNEL, cpu_to_node(cpu));
+ 		}
+ 
+ 	return 0;
+ }
+ arch_initcall(kvm_alloc_cpumask);
+ 
  static void __init kvm_smp_prepare_boot_cpu(void)
  {
  	/*
@@@ -611,38 -654,8 +659,8 @@@ static int kvm_cpu_down_prepare(unsigne
  	local_irq_enable();
  	return 0;
  }
- #endif
- 
- static void kvm_flush_tlb_multi(const struct cpumask *cpumask,
- 			const struct flush_tlb_info *info)
- {
- 	u8 state;
- 	int cpu;
- 	struct kvm_steal_time *src;
- 	struct cpumask *flushmask = this_cpu_cpumask_var_ptr(__pv_cpu_mask);
- 
- 	cpumask_copy(flushmask, cpumask);
- 	/*
- 	 * We have to call flush only on online vCPUs. And
- 	 * queue flush_on_enter for pre-empted vCPUs
- 	 */
- 	for_each_cpu(cpu, flushmask) {
- 		/*
- 		 * The local vCPU is never preempted, so we do not explicitly
- 		 * skip check for local vCPU - it will never be cleared from
- 		 * flushmask.
- 		 */
- 		src = &per_cpu(steal_time, cpu);
- 		state = READ_ONCE(src->preempted);
- 		if ((state & KVM_VCPU_PREEMPTED)) {
- 			if (try_cmpxchg(&src->preempted, &state,
- 					state | KVM_VCPU_FLUSH_TLB))
- 				__cpumask_clear_cpu(cpu, flushmask);
- 		}
- 	}
  
- 	native_flush_tlb_multi(flushmask, info);
- }
+ #endif
  
  static void __init kvm_guest_init(void)
  {
@@@ -655,15 -668,9 +673,9 @@@
  
  	if (kvm_para_has_feature(KVM_FEATURE_STEAL_TIME)) {
  		has_steal_clock = 1;
 -		pv_ops.time.steal_clock = kvm_steal_clock;
 +		static_call_update(pv_steal_clock, kvm_steal_clock);
  	}
  
- 	if (pv_tlb_flush_supported()) {
- 		pv_ops.mmu.flush_tlb_multi = kvm_flush_tlb_multi;
- 		pv_ops.mmu.tlb_remove_table = tlb_remove_table;
- 		pr_info("KVM setup pv remote TLB flush\n");
- 	}
- 
  	if (kvm_para_has_feature(KVM_FEATURE_PV_EOI))
  		apic_set_eoi_write(kvm_guest_apic_eoi_write);
  
@@@ -673,6 -680,12 +685,12 @@@
  	}
  
  #ifdef CONFIG_SMP
+ 	if (pv_tlb_flush_supported()) {
 -		pv_ops.mmu.flush_tlb_others = kvm_flush_tlb_others;
++		pv_ops.mmu.flush_tlb_multi = kvm_flush_tlb_multi;
+ 		pv_ops.mmu.tlb_remove_table = tlb_remove_table;
+ 		pr_info("KVM setup pv remote TLB flush\n");
+ 	}
+ 
  	smp_ops.smp_prepare_boot_cpu = kvm_smp_prepare_boot_cpu;
  	if (pv_sched_yield_supported()) {
  		smp_ops.send_call_func_ipi = kvm_smp_send_call_func_ipi;

```
#### [GIT PULL] VFIO updates for v5.13-rc1
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alex Williamson <alex.williamson@redhat.com>
X-Patchwork-Id: 12229991
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,INCLUDES_PULL_REQUEST,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,
	SPF_HELO_NONE,SPF_PASS autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 25F14C433ED
	for <kvm@archiver.kernel.org>; Wed, 28 Apr 2021 19:40:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E51CE613B4
	for <kvm@archiver.kernel.org>; Wed, 28 Apr 2021 19:40:24 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S236700AbhD1TlG (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 28 Apr 2021 15:41:06 -0400
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:30257 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S231312AbhD1TlA (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 28 Apr 2021 15:41:00 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1619638814;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=aNKxH/tYvIoxwT8T/p02EbXbtq/qDBC33gmsPEeKMqA=;
        b=IpGUzQ3soxsIDSyIuzwh2nybiobJYr2+Sdtvn7wSLnkpXmh8hzR9td/D/DRdYWFNT8cy+J
        07iOwSAeDH73NMXeMVYLf6ZBE3zUFmPUioZ2ubEzAEUwu/ZZuaONHPM8KHvti0510jxiM/
        UpnoonR/jvXNg+V7Mk9axK0wCfzoPSY=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-374-ToNQa1A6Pf2g_QfUKgHEQw-1; Wed, 28 Apr 2021 15:40:10 -0400
X-MC-Unique: ToNQa1A6Pf2g_QfUKgHEQw-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 84FAF107F97F;
        Wed, 28 Apr 2021 19:39:19 +0000 (UTC)
Received: from redhat.com (ovpn-113-225.phx2.redhat.com [10.3.113.225])
        by smtp.corp.redhat.com (Postfix) with ESMTP id EAA2410A33C4;
        Wed, 28 Apr 2021 19:39:17 +0000 (UTC)
Date: Wed, 28 Apr 2021 13:39:17 -0600
From: Alex Williamson <alex.williamson@redhat.com>
To: Linus Torvalds <torvalds@linux-foundation.org>
Cc: <linux-kernel@vger.kernel.org>,
        "kvm@vger.kernel.org" <kvm@vger.kernel.org>
Subject: [GIT PULL] VFIO updates for v5.13-rc1
Message-ID: <20210428133917.1c039eac@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Linus,

There's a conflict versus Dave's drm tree that was just merged in this
one.  Stephen noted the resolution vs linux-next here[1], essentially
dropping the function contents from HEAD and using the new body.  Thanks,

Alex

[1] https://lore.kernel.org/lkml/20210415164734.1143f20d@canb.auug.org.au/

The following changes since commit e49d033bddf5b565044e2abe4241353959bc9120:

  Linux 5.12-rc6 (2021-04-04 14:15:36 -0700)

are available in the Git repository at:

  git://github.com/awilliam/linux-vfio.git tags/vfio-v5.13-rc1

for you to fetch changes up to adaeb718d46f6b42a3fc1dffd4f946f26b33779a:

  vfio/gvt: fix DRM_I915_GVT dependency on VFIO_MDEV (2021-04-27 13:36:54 -0600)

----------------------------------------------------------------
VFIO updates for v5.13-rc1

 - Embed struct vfio_device into vfio driver structures (Jason Gunthorpe)

 - Make vfio_mdev type safe (Jason Gunthorpe)

 - Remove vfio-pci NVLink2 extensions for POWER9 (Christoph Hellwig)

 - Update vfio-pci IGD extensions for OpRegion 2.1+ (Fred Gao)

 - Various spelling/blank line fixes (Zhen Lei, Zhou Wang, Bhaskar Chowdhury)

 - Simplify unpin_pages error handling (Shenming Lu)

 - Fix i915 mdev Kconfig dependency (Arnd Bergmann)

 - Remove unused structure member (Keqian Zhu)

----------------------------------------------------------------
Alex Williamson (1):
      Merge branches 'v5.13/vfio/embed-vfio_device', 'v5.13/vfio/misc' and 'v5.13/vfio/nvlink' into v5.13/vfio/next

Arnd Bergmann (1):
      vfio/gvt: fix DRM_I915_GVT dependency on VFIO_MDEV

Bhaskar Chowdhury (1):
      vfio: pci: Spello fix in the file vfio_pci.c

Christoph Hellwig (1):
      vfio/pci: remove vfio_pci_nvlink2

Fred Gao (1):
      vfio/pci: Add support for opregion v2.1+

Jason Gunthorpe (32):
      vfio: Remove extra put/gets around vfio_device->group
      vfio: Simplify the lifetime logic for vfio_device
      vfio: Split creation of a vfio_device into init and register ops
      vfio/platform: Use vfio_init/register/unregister_group_dev
      vfio/fsl-mc: Re-order vfio_fsl_mc_probe()
      vfio/fsl-mc: Use vfio_init/register/unregister_group_dev
      vfio/pci: Move VGA and VF initialization to functions
      vfio/pci: Re-order vfio_pci_probe()
      vfio/pci: Use vfio_init/register/unregister_group_dev
      vfio/mdev: Use vfio_init/register/unregister_group_dev
      vfio/mdev: Make to_mdev_device() into a static inline
      vfio: Make vfio_device_ops pass a 'struct vfio_device *' instead of 'void *'
      vfio/pci: Replace uses of vfio_device_data() with container_of
      vfio: Remove device_data from the vfio bus driver API
      vfio/mdev: Fix missing static's on MDEV_TYPE_ATTR's
      vfio/mdev: Do not allow a mdev_type to have a NULL parent pointer
      vfio/mdev: Add missing typesafety around mdev_device
      vfio/mdev: Simplify driver registration
      vfio/mdev: Use struct mdev_type in struct mdev_device
      vfio/mdev: Expose mdev_get/put_parent to mdev_private.h
      vfio/mdev: Add missing reference counting to mdev_type
      vfio/mdev: Reorganize mdev_device_create()
      vfio/mdev: Add missing error handling to dev_set_name()
      vfio/mdev: Remove duplicate storage of parent in mdev_device
      vfio/mdev: Add mdev/mtype_get_type_group_id()
      vfio/mtty: Use mdev_get_type_group_id()
      vfio/mdpy: Use mdev_get_type_group_id()
      vfio/mbochs: Use mdev_get_type_group_id()
      vfio/gvt: Make DRM_I915_GVT depend on VFIO_MDEV
      vfio/gvt: Use mdev_get_type_group_id()
      vfio/mdev: Remove kobj from mdev_parent_ops->create()
      vfio/mdev: Correct the function signatures for the mdev_type_attributes

Keqian Zhu (1):
      vfio/iommu_type1: Remove unused pinned_page_dirty_scope in vfio_iommu

Shenming Lu (1):
      vfio/type1: Remove the almost unused check in vfio_iommu_type1_unpin_pages

Zhen Lei (4):
      vfio/type1: fix a couple of spelling mistakes
      vfio/mdev: Fix spelling mistake "interal" -> "internal"
      vfio/pci: fix a couple of spelling mistakes
      vfio/platform: Fix spelling mistake "registe" -> "register"

Zhou Wang (1):
      vfio/pci: Remove an unnecessary blank line in vfio_pci_enable

 Documentation/driver-api/vfio-mediated-device.rst  |   9 +-
 Documentation/driver-api/vfio.rst                  |  48 +-
 drivers/gpu/drm/i915/Kconfig                       |   1 +
 drivers/gpu/drm/i915/gvt/gvt.c                     |  41 +-
 drivers/gpu/drm/i915/gvt/gvt.h                     |   4 +-
 drivers/gpu/drm/i915/gvt/kvmgt.c                   |   7 +-
 drivers/s390/cio/vfio_ccw_ops.c                    |  17 +-
 drivers/s390/crypto/vfio_ap_ops.c                  |  14 +-
 drivers/vfio/fsl-mc/vfio_fsl_mc.c                  | 127 ++++--
 drivers/vfio/fsl-mc/vfio_fsl_mc_private.h          |   1 +
 drivers/vfio/mdev/mdev_core.c                      | 174 +++-----
 drivers/vfio/mdev/mdev_driver.c                    |  19 +-
 drivers/vfio/mdev/mdev_private.h                   |  39 +-
 drivers/vfio/mdev/mdev_sysfs.c                     |  59 ++-
 drivers/vfio/mdev/vfio_mdev.c                      |  80 ++--
 drivers/vfio/pci/Kconfig                           |   6 -
 drivers/vfio/pci/Makefile                          |   1 -
 drivers/vfio/pci/vfio_pci.c                        | 274 ++++++------
 drivers/vfio/pci/vfio_pci_config.c                 |   2 +-
 drivers/vfio/pci/vfio_pci_igd.c                    |  53 +++
 drivers/vfio/pci/vfio_pci_nvlink2.c                | 490 ---------------------
 drivers/vfio/pci/vfio_pci_private.h                |  15 +-
 .../platform/reset/vfio_platform_calxedaxgmac.c    |   2 +-
 drivers/vfio/platform/vfio_amba.c                  |   8 +-
 drivers/vfio/platform/vfio_platform.c              |  20 +-
 drivers/vfio/platform/vfio_platform_common.c       |  56 +--
 drivers/vfio/platform/vfio_platform_private.h      |   5 +-
 drivers/vfio/vfio.c                                | 210 +++------
 drivers/vfio/vfio_iommu_type1.c                    |  40 +-
 include/linux/mdev.h                               |  80 +++-
 include/linux/vfio.h                               |  37 +-
 include/uapi/linux/vfio.h                          |  38 +-
 samples/vfio-mdev/mbochs.c                         |  55 ++-
 samples/vfio-mdev/mdpy.c                           |  56 ++-
 samples/vfio-mdev/mtty.c                           |  66 +--
 35 files changed, 793 insertions(+), 1361 deletions(-)
 delete mode 100644 drivers/vfio/pci/vfio_pci_nvlink2.c
```
#### [PATCH] KVM: LAPIC: Accurately guarantee busy wait for timer to expire when using hv_timer
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 12228539
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id BAE07C433B4
	for <kvm@archiver.kernel.org>; Wed, 28 Apr 2021 11:08:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 869B561429
	for <kvm@archiver.kernel.org>; Wed, 28 Apr 2021 11:08:16 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S238305AbhD1LI7 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 28 Apr 2021 07:08:59 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:45320 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S239648AbhD1LIz (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 28 Apr 2021 07:08:55 -0400
Received: from mail-pf1-x42a.google.com (mail-pf1-x42a.google.com
 [IPv6:2607:f8b0:4864:20::42a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 7ED36C061574;
        Wed, 28 Apr 2021 04:08:10 -0700 (PDT)
Received: by mail-pf1-x42a.google.com with SMTP id c3so24720259pfo.3;
        Wed, 28 Apr 2021 04:08:10 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=sLpoIH+yhyALQFTgQocCci8bsTG3D7jmg/76ZkWjRcY=;
        b=dpwXpyq3mY3XQ/cbopkDD6jheZvyXHH6oeT2KuE8ukVbHVlj940j0PSiy+9xFf9xsh
         +NNRap1mP+dfKzOY1wZpB+MXHl14qTGu29zkTdUjG/9YHWH28q50wsevtiSHsRjZorkp
         TBidwdOjaxRWuGrrBR2WMAHr/hYZRMm4OVYcfrWZfYnhK6qdSLLniHMS7UoT6f1IU1WC
         EzEFS8iidL21YpS0nUD+WLjHvuXCCQFbUuYtw0PctqOWcZndxuKU604QfncYs5H+ik17
         F0z3l2U+DwwnQKsqNKCYHe1ZCgd2WqzmA04SkOUAYz7xZR5HkaDsfztOhENb2tbqAoGm
         9b8g==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=sLpoIH+yhyALQFTgQocCci8bsTG3D7jmg/76ZkWjRcY=;
        b=J9V1vGPHVbYRmUi+52GFCxgGznh7ZnI/kPaHDwgaL3ARZvrO+aDhDbXUaKMwkFFKN9
         t5L+0gnrhVBwmk1hrWAfJlFuysKQ9tsnE+Pnx6c3rR75oDSTY82TN6251ZfQnBMfUXw6
         0Qbuv64S/kkc8Bn75M5vwWqeRJifFZgrPat7UKjVI8+r0IaX3yMKMUouVwwitlvcBAIJ
         /C95Id1DZ6CbQNF2lrln3xC1NyQgz68KJS8DiDWNcFM3X6L8t4PSy0s722quJT0tnphz
         mY+jsNRc4Rgz8D2CznqU7zN0i1aBbGBv7WmShvt82V9jQ9JDJIfRG0gAg7fkenCN3dnJ
         BweQ==
X-Gm-Message-State: AOAM530TzsiLtGc0L+wXj80u5QErXaoQVj6H4CLel1rVVi0kFAY8mUFs
        aMpLBLnQ0HJHYLjB+oUcQRVZCIuP300=
X-Google-Smtp-Source: 
 ABdhPJzgUYS5opVQrXuZN/v6IrlJrCS4wl7W8ENluYVVshJoupHTYPqxcKawOAAerM7DT8BRVj3gKg==
X-Received: by 2002:a63:d942:: with SMTP id e2mr26479270pgj.117.1619608089738;
        Wed, 28 Apr 2021 04:08:09 -0700 (PDT)
Received: from localhost.localdomain ([103.7.29.6])
        by smtp.googlemail.com with ESMTPSA id
 z17sm4738423pfe.181.2021.04.28.04.08.07
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Wed, 28 Apr 2021 04:08:09 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>
Subject: [PATCH] KVM: LAPIC: Accurately guarantee busy wait for timer to
 expire when using hv_timer
Date: Wed, 28 Apr 2021 19:08:02 +0800
Message-Id: <1619608082-4187-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

Commit ee66e453db13d (KVM: lapic: Busy wait for timer to expire when 
using hv_timer) tries to set ktime->expired_tscdeadline by checking 
ktime->hv_timer_in_use since lapic timer oneshot/periodic modes which 
are emulated by vmx preemption timer also get advanced, they leverage 
the same vmx preemption timer logic with tsc-deadline mode. However, 
ktime->hv_timer_in_use is cleared before apic_timer_expired() handling, 
let's delay this clearing in preemption-disabled region.

Fixes: ee66e453db13d (KVM: lapic: Busy wait for timer to expire when using hv_timer)
Cc: Sean Christopherson <seanjc@google.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
Reviewed-by: Sean Christopherson <seanjc@google.com>
---
 arch/x86/kvm/lapic.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] KVM: x86: Fix KVM_GET_CPUID2 ioctl to return cpuid entries count
##### From: Valeriy Vdovin <valeriy.vdovin@virtuozzo.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Valeriy Vdovin <valeriy.vdovin@virtuozzo.com>
X-Patchwork-Id: 12228605
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=unavailable autolearn_force=no
 version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 60A8AC433B4
	for <kvm@archiver.kernel.org>; Wed, 28 Apr 2021 11:37:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2430B613E7
	for <kvm@archiver.kernel.org>; Wed, 28 Apr 2021 11:37:14 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S239209AbhD1Lh5 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 28 Apr 2021 07:37:57 -0400
Received: from mail-eopbgr60102.outbound.protection.outlook.com
 ([40.107.6.102]:25651
        "EHLO EUR04-DB3-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S234158AbhD1Lh5 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 28 Apr 2021 07:37:57 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=Y3PgaT8MU+bJOFltItTfOEXQlnq1loGT2L6dz2QWNGqq1ki0makfqjOG8w1hjbJ2lRaRud3hIWOFQs23sUCFwXpATrWCnI9g6Ma/qvW3fckrY+fy2NhCbgXDe1bYL79O9Ob2n7cQR4lcQ9faWg/pjjhO6ngLxLIRFUUqqUcje/Peur/KVrffZAErSUpIDXAowks+Ni6eUaTsw/N47pvgCtElkXAFJIDJqR91z33RZMyKlpSXlXIAkPzaunbrfjdNsJ++yBmZ7S0hiJW1pW3ysqpNxOB1OAtSvC720PQbDwsaJ1n0W+ygi894EJhXEg5HyXDdZBAboWgDlrhR9egQnw==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=w0db4OClljsDs15qUYvQR9/uVd9LLVF0JZzUbGI9oD4=;
 b=h6bR2EPIiqmJE0vjdhBSEJOvEYWUGLYGkC4Wpy6pEHkBEigv8rnDGw8iK3vvVB9bJf+nMVXtmn2eADXbI/tSC7OmZAW2Jxidbw5/u8p+LwR4WHBhx5rVoUDDvJ5b+uNAOzsKdmgaIzfB1SCnfg9IZWSJcs/z2MPSA/RP2L3OF4b2kmragLz/qkCb2lBnWunmK0GDudKeLohgKpqpe0qK2miva2HYFPaqSyhIWIi1oWB93dzFqfLlacElLfo2oPOEVO+Vm2XPShyzmyo8RsEImaYlnd40GbhIptmJ9VgnNfMtWvLGWMRPE1zpudU633NWOP7TMrIvzXnvRj+xfcx9Ww==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=virtuozzo.com; dmarc=pass action=none
 header.from=virtuozzo.com; dkim=pass header.d=virtuozzo.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=virtuozzo.com;
 s=selector2;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=w0db4OClljsDs15qUYvQR9/uVd9LLVF0JZzUbGI9oD4=;
 b=UzEVulf4KKv3wdfZvJh9S19ruh3PXIM0ErW1sM8BLc3XxVFzVKxVB9Xedcpkp9KEEdvKQXIeztPwSHGbZLlHvHI21ycpceHuXtpOqpxYHs4BLzMDbylPFoHdTGHEYLm9gqH7CrCi6Pq1BTsHhohymbjdMGdB1fMiogAE+uYgQoU=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none
 header.from=virtuozzo.com;
Received: from AM9PR08MB5988.eurprd08.prod.outlook.com (2603:10a6:20b:283::19)
 by AM0PR08MB5539.eurprd08.prod.outlook.com (2603:10a6:208:13d::12) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4065.21; Wed, 28 Apr
 2021 11:37:10 +0000
Received: from AM9PR08MB5988.eurprd08.prod.outlook.com
 ([fe80::7d3f:e291:9411:c50f]) by AM9PR08MB5988.eurprd08.prod.outlook.com
 ([fe80::7d3f:e291:9411:c50f%7]) with mapi id 15.20.4065.028; Wed, 28 Apr 2021
 11:37:10 +0000
From: Valeriy Vdovin <valeriy.vdovin@virtuozzo.com>
To: linux-kernel@vger.kernel.org
Cc: Valeriy Vdovin <valeriy.vdovin@virtuozzo.com>,
        Denis Lunev <den@openvz.org>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        x86@kernel.org, "H. Peter Anvin" <hpa@zytor.com>,
        Shuah Khan <shuah@kernel.org>,
        Aaron Lewis <aaronlewis@google.com>,
        Alexander Graf <graf@amazon.com>,
        Like Xu <like.xu@linux.intel.com>,
        Oliver Upton <oupton@google.com>,
        Andrew Jones <drjones@redhat.com>, kvm@vger.kernel.org,
        linux-kselftest@vger.kernel.org
Subject: [PATCH] KVM: x86: Fix KVM_GET_CPUID2 ioctl to return cpuid entries
 count
Date: Wed, 28 Apr 2021 14:36:52 +0300
Message-Id: <20210428113655.26282-1-valeriy.vdovin@virtuozzo.com>
X-Mailer: git-send-email 2.17.1
X-Originating-IP: [176.106.247.78]
X-ClientProxiedBy: AM0PR10CA0104.EURPRD10.PROD.OUTLOOK.COM
 (2603:10a6:208:e6::21) To AM9PR08MB5988.eurprd08.prod.outlook.com
 (2603:10a6:20b:283::19)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from localhost.localdomain (176.106.247.78) by
 AM0PR10CA0104.EURPRD10.PROD.OUTLOOK.COM (2603:10a6:208:e6::21) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4087.27 via Frontend
 Transport; Wed, 28 Apr 2021 11:37:08 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: b5b60e6f-7204-4d1d-f717-08d90a39f58d
X-MS-TrafficTypeDiagnostic: AM0PR08MB5539:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <AM0PR08MB55399D01439102B8FA6DBCB487409@AM0PR08MB5539.eurprd08.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:7691;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 3oiYFwACeI/L9kz90AKbQJbmN2GOb7tA7sp3dwI8hBiCKjCRrqIeTvBBkvE4aFGqgT70ZQ7dfJFIuM7dfi3y25nLm+rL1+1XtGuXvuOLGiImhe6DfdVMpTmVBN1To4i7itXnHZgsJSTuSE4Xxlsgyu64ccDEFOLUYN7mpYW2I32gsmqCz5nByV2Xcv8XtfJIz7ThlRT8rRsMzgk9oO96fXhuDk2z6byDKpvdOd/Y/HuIPjsPzqe8HGVM34vnxlgX+MMM9VMnJOFt1Rfqmxe1tUc7Mnmn6Jean/EgKkZQgSvp6J1mGDM5oyjLRWho2aUObaGNP7jOVdaP3CPy0Pb2Aabvxz1h7wVT8wj6+9q9n2uPoXq7EUVqrfjpP8PTNYKt+yoHZP1Sf3vPzUTfT4B1j0ZVrwyc0+HPS1tJXzqbBMJEuOljf/mhOVPGg63u8A/Xk2CBOonZhx66Wjl59pIWpiizPqI2rjTe9YBptmFTCM8C55OrhpsaEW+xV7x1OI9ofBzR6+sbW0saSrxKxc+xpp4+mABy09lguFVy9iZGZBioU+K1evXEj6HNq9dY3CR5WzU4ByH+k33EOk0MO1KSCv8P48bE2Rf6nrrYDrSvTdaKXMt0mSLlx+ExS9Q1eZ1Zl94iMGsFoKZyAUAl6mEv/Zy0aH0OEL0JRKWAwCqXhbGfc8SOe6MOGV9EIgIqGCqZ
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:AM9PR08MB5988.eurprd08.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(136003)(396003)(376002)(366004)(346002)(39840400004)(8676002)(6486002)(38350700002)(66476007)(38100700002)(4326008)(36756003)(54906003)(2616005)(6666004)(16526019)(478600001)(186003)(5660300002)(8936002)(86362001)(7416002)(44832011)(2906002)(316002)(26005)(956004)(6506007)(66556008)(1076003)(52116002)(6916009)(66946007)(83380400001)(6512007)(69590400013);DIR:OUT;SFP:1102;
X-MS-Exchange-AntiSpam-MessageData: 
 B52IVhnHobvkWeHQdmAI5jsb/ja6X4D0NsM1TnI1ylLn5ASdK4rdTuaCTdO8xx391enXO8p0QR9Fx/XJSEMVLwmYtcQs/r9UDPphgg2NwBzMUxf2GBD+4iGdO/QLEcudUcrBWukLYMEEtzpu4/cQLy50QovQ/V/XWDtf5Fk0hnGDDY1Yq5d4RLcyHL2RijB9++iUkbF7gV5tFqG8txshGrR0zvUKuAEYcnlJOyZlAfMNtpasWGR1+n3jeFlyGCcMJIUQreR2UIeEEsEH9VVgy5fWhoDrF7X7fVwNIzuMFBqpgxTT77CZ92fpseooensdUy3Zixa+fJwShFod/rLtE0YSurOR9lDVZb7/UKfmAlnex8QsyGyRDEf1Z88CCim85jqQZurntCfWi2PvlvyOfvNu/2484j8cyfF1GuXP9Bypmq74NX95rYn82I4gME7/b+LNc1VXpOIXHKHf+Fr3U8UGqzOWwI0It8BbW+Rh4iYbyeTpDmnn2Xx62Z9NFdENU1wxcyrJzsOqyrardye39pSp6+NW2+rojYWjoGVBE6Yj4rGLZKsJAnBn7O7R3k0FtkdvQpPsJUfWPoFY0bH9OfoEkKZMPLPWTjiOH/dEZJ6q4g96bhPoUCpGsJWjv4TNCOlw7QvEToDWGWwpMVqqRCzLFqHHiHn6xrV5mj7kGl+BpzKHZG4gPIy2eZgvM6dZJC2gj89V9Gbc5Nxejc/mXZPoXEomd9EjI61PVY0A/kVy98OoODklLYg/V4RygS1ZsjExJ5o0u8FTKMrkeo/W9B8OpXhQ8rogM3vopOc0S25QrbqO4lzu9UdWiil47K02oyW9vJhMxvbN4rQYMOEuJ8DZaFgBtjpUrzLLMy2py0TURPy1orvFiq/hGPfW7pjUq/XOiaixN1LPbAWP9eEp4UQyXHZjb8mrL17nGprL1fg3YfoI/QkPjvzVBXm0AMamsPzZYBxPLrd9Z+JwGFB41h4fomlqFB55XBhPJbxedEdrw36FKyKQTHWGmlzNO/sqU4PXQAOLhUNSYAegJqGnvOEDym0M1JEJVuCQLzcsDjUmK3cJi4INcEnUnAxNdbJ7AxbsNTJQyT/CAVZj3OFGhnwplAEPZq6Xt3HBQLwBxb6EBKIYTDOTL862E0/+8XvwqoG9CfSisovnGIy1FyMyJKAP5XSMSwDMTc90yf2T1OgA95hrRoHDlR4/9OPfXmhYx46h6LTl3m+1PTZZG7kgWSTqYyuzZ/9Q4hjyJnInl1s6MAYXs7AOD0OWgGOUICbsPeZmHGnuAUxTizy0zriwu5eXNomPywUTR01gjN5ym8vVgflt3CBFIpoWZ8FFu3Bu
X-OriginatorOrg: virtuozzo.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 b5b60e6f-7204-4d1d-f717-08d90a39f58d
X-MS-Exchange-CrossTenant-AuthSource: AM9PR08MB5988.eurprd08.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 28 Apr 2021 11:37:10.2345
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 0bc7f26d-0264-416e-a6fc-8352af79c58f
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 6+xV6dZzeUeeOhjLcvZ8CKFz0zVAha2PSh6Ta3ahuwL6bSuOVZaQr8G+K5MwV8yW03RNABpAAVT9vvCYmvPziIKbEhGBk7pZU8UUjeodNFs=
X-MS-Exchange-Transport-CrossTenantHeadersStamped: AM0PR08MB5539
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

KVM_GET_CPUID2 kvm ioctl is not very well documented, but the way it is
implemented in function kvm_vcpu_ioctl_get_cpuid2 suggests that even at
error path it will try to return number of entries to the caller. But
The dispatcher kvm vcpu ioctl dispatcher code in kvm_arch_vcpu_ioctl
ignores any output from this function if it sees the error return code.

It's very explicit by the code that it was designed to receive some
small number of entries to return E2BIG along with the corrected number.

This lost logic in the dispatcher code has been restored by removing the
lines that check for function return code and skip if error is found.
Without it, the ioctl caller will see both the number of entries and the
correct error.

In selftests relevant function vcpu_get_cpuid has also been modified to
utilize the number of cpuid entries returned along with errno E2BIG.

Signed-off-by: Valeriy Vdovin <valeriy.vdovin@virtuozzo.com>
---
 arch/x86/kvm/x86.c                            | 10 +++++-----
 .../selftests/kvm/lib/x86_64/processor.c      | 20 +++++++++++--------
 2 files changed, 17 insertions(+), 13 deletions(-)

```
#### [PATCH] kvm: x86: move srcu lock out of kvm_vcpu_check_block
##### From: Jon Kohler <jon@nutanix.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jon Kohler <jon@nutanix.com>
X-Patchwork-Id: 12229867
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.5 required=3.0 tests=BAYES_00,DKIM_INVALID,
	DKIM_SIGNED,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 44578C433ED
	for <kvm@archiver.kernel.org>; Wed, 28 Apr 2021 17:40:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 115616143F
	for <kvm@archiver.kernel.org>; Wed, 28 Apr 2021 17:40:37 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S242756AbhD1RlU (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 28 Apr 2021 13:41:20 -0400
Received: from mx0a-002c1b01.pphosted.com ([148.163.151.68]:40304 "EHLO
        mx0a-002c1b01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S242705AbhD1RlI (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 28 Apr 2021 13:41:08 -0400
Received: from pps.filterd (m0127840.ppops.net [127.0.0.1])
        by mx0a-002c1b01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 13SHUJgB020655;
        Wed, 28 Apr 2021 10:39:17 -0700
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nutanix.com;
 h=from : to : cc :
 subject : date : message-id : content-transfer-encoding : content-type :
 mime-version; s=proofpoint20171006;
 bh=5FdrwWxs92QDTjrlGBRdAVvKaRrOt1nkH4EwHDh6O68=;
 b=F6y1OTDxzs6yEqWqN97M+dLN8t4yCbBZmRv0JVLuxuEubsl2XuDnWW9ycvg4EqKFfuDc
 D0DItpkQY0H9F+jNf2dWKKv4BK7joWIxujppqD9JtSgv0EpIXAicM2aoVsxmB/SqAjlR
 YiakblKjSMJtC95arPP4grhlbJZetFSc+LjHmRYgjQo7vTn1enInY41rRK6ZGi0y2XJf
 xPPvU9smfWnHCYiCv3tBaM7CleszwLUS6O9KDA9bIMcslaHdVhhO+dTknHqs70tRZeJ2
 Y0eAjd0kGJ5z+OKoqI4mi5sYS9LG6YltQ+yoXzaUbQ8Lf50SCWH7if1jJiFwKxOD5vJ6 yQ==
Received: from nam12-dm6-obe.outbound.protection.outlook.com
 (mail-dm6nam12lp2169.outbound.protection.outlook.com [104.47.59.169])
        by mx0a-002c1b01.pphosted.com with ESMTP id 386gy93f0v-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 28 Apr 2021 10:39:17 -0700
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=EldOCsIFU4tOn6B3A/4T+nF2r1AxFNNbesb1ZDUoUyBnAtnItbwp0DMFi+J+q4gtokRRZvsVK5CnjiW80EtFZVkMOKEIny1RlQpf6nreqgexaIV04VOukeVE/JJFlQNdzdUHbCSgm6VCyt10lWbh/tHtIRgMBuULWFiawPPJ13JNnMpSjGbuOOMKTQBWd+LeuhEYqowQCQogtKEtPX66VjE34za5BWxF3hyE3tqdamHSJiaRZ1MkgIPmsL6uPkSY2OQYU7PK+MpYRAId42FDBjVbpQ/hLQGQfrvvpVeUKTUkUmUPpobmjYJVn2b7bUUxf0C6+Yr8FEC11eoXTl8ubQ==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=5FdrwWxs92QDTjrlGBRdAVvKaRrOt1nkH4EwHDh6O68=;
 b=I5cPHQByhjg+qwn8JNvMjvPJ+gdgjkKtyJ91hIPRJ0P/b0T6HmARCCmsqkiUMIAb4CBfCfbgkmYY9IAhHuFK5Uhtjhir94w7pj+7fb20mjjV5zgNnWpdMMnBMFpTVJRAARmZEBJo5VlbkIod4DdyDQ8hMklyZVqiIbuHctSx4VlQJAxFIMVp6UbwsSKDraaT3S1lpXkInatkQfJfOlK/EtGR1piHuvRKi+DMlsnqlY+TQPowyg6reARCeSjopAgaP+/AJIaYk2fN1HeG9am7iKbzC+YhFrUZqPYFu3+ypnEsP7d4Wv6Q4xlp6fFWELIKQfcyLecAxkcV1fWtMliULQ==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=nutanix.com; dmarc=pass action=none header.from=nutanix.com;
 dkim=pass header.d=nutanix.com; arc=none
Authentication-Results: nutanix.com; dkim=none (message not signed)
 header.d=none;nutanix.com; dmarc=none action=none header.from=nutanix.com;
Received: from BL0PR02MB4579.namprd02.prod.outlook.com (2603:10b6:208:4b::10)
 by BL0PR02MB4882.namprd02.prod.outlook.com (2603:10b6:208:5d::18) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4065.20; Wed, 28 Apr
 2021 17:39:15 +0000
Received: from BL0PR02MB4579.namprd02.prod.outlook.com
 ([fe80::75cf:5b99:f963:cc07]) by BL0PR02MB4579.namprd02.prod.outlook.com
 ([fe80::75cf:5b99:f963:cc07%5]) with mapi id 15.20.4065.027; Wed, 28 Apr 2021
 17:39:15 +0000
From: Jon Kohler <jon@nutanix.com>
Cc: Jon Kohler <jon@nutanix.com>,
        Bijan Mottahedeh <bijan.mottahedeh@nutanix.com>,
        Raphael Norwitz <raphael.norwitz@nutanix.com>,
        Junaid Shahid <junaids@google.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        x86@kernel.org, "H. Peter Anvin" <hpa@zytor.com>,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH] kvm: x86: move srcu lock out of kvm_vcpu_check_block
Date: Wed, 28 Apr 2021 13:38:19 -0400
Message-Id: <20210428173820.13051-1-jon@nutanix.com>
X-Mailer: git-send-email 2.24.3 (Apple Git-128)
X-Originating-IP: [2601:19b:c501:64d0:f5f6:aad4:1b61:d025]
X-ClientProxiedBy: BYAPR08CA0062.namprd08.prod.outlook.com
 (2603:10b6:a03:117::39) To BL0PR02MB4579.namprd02.prod.outlook.com
 (2603:10b6:208:4b::10)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from C02F13YVQ05N.corp.nutanix.com
 (2601:19b:c501:64d0:f5f6:aad4:1b61:d025) by
 BYAPR08CA0062.namprd08.prod.outlook.com (2603:10b6:a03:117::39) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4087.27 via Frontend
 Transport; Wed, 28 Apr 2021 17:39:10 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: be679128-6c58-4275-731e-08d90a6c8a86
X-MS-TrafficTypeDiagnostic: BL0PR02MB4882:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <BL0PR02MB4882D67F5E3F7EA6D980CF2DAF409@BL0PR02MB4882.namprd02.prod.outlook.com>
x-proofpoint-crosstenant: true
X-MS-Oob-TLC-OOBClassifiers: OLM:10000;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 mMFZuCTTZe21jSo39j9PFvokiG5r+7Gyo8YXNeoJKUky3tx9QdFz/HqzP+nN2Vu3cG31oTQ/hAPwFhuzBfTw4b6x6eRSYXKZKLvcIL4eQ9aYXPHMm21KUZCZKp0pq55Nr4KasZ85wqOv0VJm+ysvHjGq+6zHVpQdFD7fD57YvnyDrmLCXqWuMhcsN/sAOPBuRwYyAR92+0j9kAIvVB4cAWrCr3zNGDYDFGcYtCPL9TGbW5qSgQ8pfViCZoyv1U4vpNhVuUL7yLeEB51kSxZfe3Tcxie8q1jo7kME9GMe3Uio9rn3KE9kCnwh37JEOPBG3asQsZKi7HX52u+dPSH/NikOicajzpPQGSaijm9p9CoN/RxKmEITmwzhckH8oHs3JGAnWUljC7R6iR9LtDZlqJL1amlz/j8JG1Be7HeZlgnTh/BKk0Sd8Rh4ED4jKZfnwDqnRg6JTsRzF2UAT9xjiIFoBtvWa1Rg849gUh3YJ4fv0bKJS+VbMyfDCEQWYKdpJw3wHt54WTQMcU8/37I0IpKpLqP7lt0Y/7Wl1kMQvxx7qz3sK/abbiz2Sog0LD1aS0a16BZWuLaKJhRkNcWmRE2cZsMYpLuPaQa7JdBQtyn5O++ctQpd50q9u37/ZaVINpeWqtNRsvSx607HLUu6+Q66Kz1POrUF9EV7ode4R5YSmY98v7elfokKq5246l8IeJeP1bvm/26ih4reOqBw5zWKZ0scy7L4vIn0mfVDG+SbRrPy7ypZxXXkP25RqcWL
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:BL0PR02MB4579.namprd02.prod.outlook.com;PTR:;CAT:NONE;SFS:(366004)(136003)(376002)(396003)(39860400002)(346002)(4326008)(8936002)(7416002)(2906002)(8676002)(109986005)(66476007)(966005)(2616005)(5660300002)(6486002)(66946007)(66556008)(316002)(16526019)(186003)(38100700002)(7696005)(36756003)(478600001)(1076003)(54906003)(86362001)(83380400001)(52116002)(266003)(46800400005);DIR:OUT;SFP:1102;
X-MS-Exchange-AntiSpam-MessageData: 
 u8FAdnGq6pl6sn6hPgufCNkI6ABtNH2f4mKiJNZ3P/nkBlvMvnrdpJlz1YLPEsfhYKhyjejVEPaYMgHTbnp19j1Isdg07x1pQ8X3MsLzLpTannfgE/Q+YYLAvcUzz9/l1bmjsZgJTZl6ld8NOhngQNoZNmjPdd9d+V5ioyf5b8Cc7tkxJY3PK7pS7T4tNOC63i3BAfNH65mosDnLCz5ZxhKj+e/7NhpxwlL0VBT88GBGlF2kQjuaojMxEvI+GzAZDHZJoNIX0xAH4QGuJM1fDa08Aq/0KnJfn/K1bQIA1eN/c4B7Rg4dpFbM/PidiNcsfZLMH0TgXdZuaUwN2FHOmJnewOhBMH9X25CiTKgGSihwnIr9X9hLjvFpXz+CqiVp5Ag2IBeSUE24f47GQOgZeoAWkl9LVn4uynbKKt3xduYoTYKfwuJF0Pga34PsHgg30gVBcfhZQBXR7UlnSBKHs54kn2x3GFU6VTAal0GLx6TE2bZcJRrAMXbBbRI7PW9bnh1DSx2WcWij8JNt7UeR4Q6j7ajS09RnAk5ry70iYtqBl2szmMpyOj17DTpfT1NWb1aemzwygLSCL/1Klwj7bW/+pg1jv5Wl8+XbFcRZNxL/IG62CmMjufZpOMwtnY2Lew37V68nlqdSJTfj+Ug1uukTzxxSy4WKyj2jeanw4qqpPRco1Wz9/wysWW+3JKPOMq7mf78nkjSXdjAEa6c67wUSE1ldxg88ZxE5iLV3DgbSDrNXC951koD5d7TOalwlw/EzFxniiz8gcHWrliTl7j4IZQ9yPaTHXkaho8gqzd7kSzIKtkRXcxbAIGAXxoKLHHz7nPNUafnEvEYkvXqyOYYKOp5TNw+PxfSFHFNpR/9SJu4Eo9VElBbq96q2+FIqm2Y9z2+EszaOE07+DdePyu0Qt5dwfLxedoNrXrNtDoLpfawtUF9Ldi1SZi3tyMh/GLAafp9cngmWo+h12CcZf/bIWLEyZW+tVZrJKo8SIlQky0IdpqTK8QxmloVY1M75gBJMyY9TI05CG6cDRKBoswK4TB1zuHGzPCDfeVgNOwjX6SaxTUver+Vjrs/dABKniI1OqT4iohdTV1iGgviWwlzDeyDSLWBFdd/hwyL+cE40NqJzCew4KOj6Vp4TN3BQQg2PKZhdvHDdBu+GPKh8JiDh86kGtJgsihK1x4b9U2tfrWYWWJopP/53CzRm6l+d2p6JkkU1Ce6v+b2x448pHLfSP+oj9WSlR45/ONyVutZiMqfQ7axj5W9iKewPRgQigvjD3J2BuLw2/KgAzjlZJA076y9ayCJiM4uO/t0hQCTurDKwFwMPukUbor5iT3HO5gcHNdIH8yALM+G/WbBUdbxwAZdujtbuHxQ6c2EJFoDkUEz3RopQUz8/PRhP1kO6
X-OriginatorOrg: nutanix.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 be679128-6c58-4275-731e-08d90a6c8a86
X-MS-Exchange-CrossTenant-AuthSource: BL0PR02MB4579.namprd02.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 28 Apr 2021 17:39:15.1835
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: bb047546-786f-4de1-bd75-24e5b6f79043
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 QGtjWrfluWDiUQL+VvqZQr5oU4GOkekmBRjRwymYtdYg6aWlmE9Yv4zl+VXzvFZ4ONA0RDtfbddvxrNvJ42LAR2KlyHocEEra2G/YVBWhB8=
X-MS-Exchange-Transport-CrossTenantHeadersStamped: BL0PR02MB4882
X-Proofpoint-ORIG-GUID: YUwRs1ugoCbkzxrpZmJJb3OJNX-uJYvP
X-Proofpoint-GUID: YUwRs1ugoCbkzxrpZmJJb3OJNX-uJYvP
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.391,18.0.761
 definitions=2021-04-28_10:2021-04-28,2021-04-28 signatures=0
X-Proofpoint-Spam-Reason: safe
To: unlisted-recipients:; (no To-header on input)
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When using halt polling on x86, srcu_read_lock + unlock overhead [1] is
high in a bursty workload, showing as ~8% of samples in a 60-sec flame
graph.

kvm_vcpu_block calls kvm_vcpu_check_block for both halt polling and
normal blocking. kvm_vcpu_check_block takes srcu_read on kvm->srcu.
This was added in 50c28f21d0 to support fast CR3 and was questioned [2]
at the time but made it in such that we take the lock even for
non-nested. This only appears to be valid for nested situations, where
we will eventually call kvm_vcpu_running and vmx_check_nested_events.
This check is hidden behind is_guest_mode() and therefore does not
seem to apply to non-nested workloads.

To improve performance, this moves kvm->srcu lock logic from
kvm_vcpu_check_block to kvm_vcpu_running and wraps directly around
check_events. Also adds a hint for callers to tell
kvm_vcpu_running whether or not to acquire srcu, which is useful in
situations where the lock may already be held. With this in place, we
see roughly 5% improvement in an internal benchmark [3] and no more
impact from this lock on non-nested workloads.

[1] perf top output in heavy workload
Overhead  Shared Object  Symbol
   9.24%  [kernel]       [k] __srcu_read_lock
   7.48%  [kernel]       [k] __srcu_read_unlock

[2] Locking originally discussed here
https://patchwork.kernel.org/project/kvm/patch/20180612225244.71856-9-junaids@google.com/

[3] Internal benchmark details
Fixed-rate 100 GBytes/second 1MB random read IO ran against the
internal in-memory read cache of Nutanix AOS, 16 threads on a 22
vCPU CentOS 7.9 VM. Before: ~120us avg latency, After: ~113us.

Fixes: 50c28f21d0 ("kvm: x86: Use fast CR3 switch for nested VMX")
Signed-off-by: Jon Kohler <jon@nutanix.com>
Reviewed-by: Bijan Mottahedeh <bijan.mottahedeh@nutanix.com>
Reviewed-by: Raphael Norwitz <raphael.norwitz@nutanix.com>
Cc: Junaid Shahid <junaids@google.com>
---
 arch/x86/kvm/x86.c  | 24 +++++++++++++++++++-----
 virt/kvm/kvm_main.c | 21 +++++++--------------
 2 files changed, 26 insertions(+), 19 deletions(-)

--
2.24.3 (Apple Git-128)

```
#### [PATCH] KVM: x86: Update vCPU's hv_clock before back to guest when tsc_offset is adjusted
##### From: Zelin Deng <zelin.deng@linux.alibaba.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zelin Deng <zelin.deng@linux.alibaba.com>
X-Patchwork-Id: 12227881
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,UNPARSEABLE_RELAY,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B732AC43460
	for <kvm@archiver.kernel.org>; Wed, 28 Apr 2021 02:22:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 858BB6140B
	for <kvm@archiver.kernel.org>; Wed, 28 Apr 2021 02:22:07 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S239585AbhD1CWt (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 27 Apr 2021 22:22:49 -0400
Received: from out30-133.freemail.mail.aliyun.com ([115.124.30.133]:34802
 "EHLO
        out30-133.freemail.mail.aliyun.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S239572AbhD1CWt (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 27 Apr 2021 22:22:49 -0400
X-Alimail-AntiSpam: 
 AC=PASS;BC=-1|-1;BR=01201311R191e4;CH=green;DM=||false|;DS=||;FP=0|-1|-1|-1|0|-1|-1|-1;HT=e01e04400;MF=zelin.deng@linux.alibaba.com;NM=1;PH=DS;RN=6;SR=0;TI=SMTPD_---0UX0thWn_1619576521;
Received: from localhost(mailfrom:zelin.deng@linux.alibaba.com
 fp:SMTPD_---0UX0thWn_1619576521)
          by smtp.aliyun-inc.com(127.0.0.1);
          Wed, 28 Apr 2021 10:22:01 +0800
From: Zelin Deng <zelin.deng@linux.alibaba.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Wanpeng Li <wanpengli@tencent.com>
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org, x86@kernel.org
Subject: [PATCH] KVM: x86: Update vCPU's hv_clock before back to guest when
 tsc_offset is adjusted
Date: Wed, 28 Apr 2021 10:22:01 +0800
Message-Id: <1619576521-81399-2-git-send-email-zelin.deng@linux.alibaba.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1619576521-81399-1-git-send-email-zelin.deng@linux.alibaba.com>
References: <1619576521-81399-1-git-send-email-zelin.deng@linux.alibaba.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When MSR_IA32_TSC_ADJUST is written by guest due to TSC ADJUST feature
especially there's a big tsc warp (like a new vCPU is hot-added into VM
which has been up for a long time), tsc_offset is added by a large value
then go back to guest. This causes system time jump as tsc_timestamp is
not adjusted in the meantime and pvclock monotonic character.
To fix this, just notify kvm to update vCPU's guest time before back to
guest.

Cc: stable@vger.kernel.org
Signed-off-by: Zelin Deng <zelin.deng@linux.alibaba.com>
---
 arch/x86/kvm/x86.c | 4 ++++
 1 file changed, 4 insertions(+)

```
#### [PATCH v2 1/6] KVM: selftests: Add kernel headers sync checkFrom: Ricardo Koller <ricarkol@google.com>
##### From: Ricardo Koller <ricarkol@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ricardo Koller <ricarkol@google.com>
X-Patchwork-Id: 12229981
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 369CDC433ED
	for <kvm@archiver.kernel.org>; Wed, 28 Apr 2021 19:38:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id EF79E613B4
	for <kvm@archiver.kernel.org>; Wed, 28 Apr 2021 19:38:29 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S240086AbhD1TjJ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 28 Apr 2021 15:39:09 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:46068 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S241726AbhD1Ti4 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 28 Apr 2021 15:38:56 -0400
Received: from mail-pf1-x44a.google.com (mail-pf1-x44a.google.com
 [IPv6:2607:f8b0:4864:20::44a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id D08F8C0613ED
        for <kvm@vger.kernel.org>; Wed, 28 Apr 2021 12:38:04 -0700 (PDT)
Received: by mail-pf1-x44a.google.com with SMTP id
 k11-20020a62840b0000b029024135614a60so23914087pfd.18
        for <kvm@vger.kernel.org>; Wed, 28 Apr 2021 12:38:04 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=3EmL6xt5jVjqc/fFRGG9Bp/HY5j+2f9o1zD7J8DnnPw=;
        b=qojwyUnMOEKFrRAcoKNQv8n9HI0z+aYcwAplArllOvARz6euC5nXNvMP3+XTjqrcuq
         27iyRNgjq7qlyk8BgfqzP+q/bPr4jr7bPbIFOboYm2DK2DViCz9IgZO02YQcBAjmgel7
         LfkZytiSEZgfQZE2lG/0d3YqOKenqkidls0+i+KeEhqqrAkiHzY1FGQib/wb6bMGhpLC
         ggG0+bb0D3uy/d/sAGEhmuM6kW/F/n5phGtR6VG9kFmXv+RTV8Z/lXrev6QZXNEaeuuF
         FSyn+4mmB/ug/UJXVXOt2t+AUXRjC8OQmqDiBEC30XkjkcsO+gdvbaD1+CHgH+8vqOGS
         vn2g==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=3EmL6xt5jVjqc/fFRGG9Bp/HY5j+2f9o1zD7J8DnnPw=;
        b=UnEB2WoJIRGSVaGlKFk37j1R3ZlJ6BP3GrlCOPtd0xjtG+I1GrqZRZhiiNwkEX2vVP
         pa9S0yXueMbj4h4hq8Kuf60ywjJNIErzXoU9bbLS9bIBHGOn1y4F9qwPWV4MGw0wNkn3
         oIzyAuR5IfKt0FK9ACYbaTXk7kj3BtUj4Rt7NkqNjmPIEnscCpauKAQWerdfI3zetB5Z
         HiR5nhvnn57IIzYWVELzUFaSV1pIVEy3dTQC6mhKHtnJNEL0QJtcEwRY0+R8lM68n/JF
         zWk/WSNlOy37maeIfHXN0NVuikFaKv1oo/WomEgVoWpyX55lTNSAtHv2li7OZUrYBcNw
         yMXQ==
X-Gm-Message-State: AOAM533/YYCYMZqy56Ee4BNd8am/jCNXJSdPbxyYEqxFWRjpe2HcPCY1
        7zXT7J/osSYnp7iowMZYcUpapd/idVZpaw==
X-Google-Smtp-Source: 
 ABdhPJwxcktVdD/XvgMx0K4EkvWN9+2vn0sfN6x1/yc8vpWGv23+caxbU3DuBq9wNvwPZ95Khs2Y0ysoEKh68w==
X-Received: from ricarkol2.c.googlers.com
 ([fda3:e722:ac3:10:24:72f4:c0a8:62fe])
 (user=ricarkol job=sendgmr) by 2002:a17:902:8d8b:b029:ed:64bb:db81 with SMTP
 id v11-20020a1709028d8bb02900ed64bbdb81mr8252681plo.53.1619638684396; Wed, 28
 Apr 2021 12:38:04 -0700 (PDT)
Date: Wed, 28 Apr 2021 12:37:51 -0700
In-Reply-To: <20210428193756.2110517-1-ricarkol@google.com>
Message-Id: <20210428193756.2110517-2-ricarkol@google.com>
Mime-Version: 1.0
References: <20210428193756.2110517-1-ricarkol@google.com>
X-Mailer: git-send-email 2.31.1.498.g6c1eba8ee3d-goog
Subject: [PATCH v2 1/6] KVM: selftests: Add kernel headers sync check
From: Ricardo Koller <ricarkol@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org, Peter Zijlstra <peterz@infradead.org>,
        Ingo Molnar <mingo@redhat.com>,
        Arnaldo Carvalho de Melo <acme@kernel.org>,
        Mark Rutland <mark.rutland@arm.com>,
        Alexander Shishkin <alexander.shishkin@linux.intel.com>,
        Jiri Olsa <jolsa@redhat.com>,
        Namhyung Kim <namhyung@kernel.org>,
        "H. Peter Anvin" <hpa@zytor.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Nathan Chancellor <nathan@kernel.org>,
        Nick Desaulniers <ndesaulniers@google.com>,
        linux-kernel@vger.kernel.org, clang-built-linux@googlegroups.com,
        Ricardo Koller <ricarkol@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add a script that checks if header files under /tools match their
original version in the kernel. Perform the check at the end of the
make, so warnings are shown after all tests are built.  Note that
the build is _not_ aborted if any diff check fails.

The list of header files to check was obtained from the union of the
output of these (at tools/testing/selftests/kvm):

  CFLAGS="-H" make ARCH=x86_64 2>&1 | grep '.h$' | grep 'tools'
  CFLAGS="-H" make ARCH=arm64 CC=aarch64-linux-gnu-gcc-10 2>&1 | grep '.h$' | grep 'tools'

and then by manually removing the header files that were updated on the
tools/ side but not on the kernel side. There is no point in checking
for these as their changes will not be synced back to the kernel. Here
are the removed headers and the first commit that made them drift apart
from their original copies:

  tools/include/linux/kernel.h
  d0761e37fe3 perf tools: Uninline scnprintf() and vscnprint()

  tools/include/linux/list.h
  5602ea09c19 tools include: Add compiler.h to list.h

  tools/include/linux/poison.h
  6ae8eefc6c8 tools include: Do not use poison with C++

  tools/include/linux/types.h
  70ba6b8f975 tools include: add __aligned_u64 to types.h

  tools/include/asm-generic/bitsperlong.h
  2a00f026a15 tools: Fix up BITS_PER_LONG setting

Based on tools/perf/check-headers.sh.

Signed-off-by: Ricardo Koller <ricarkol@google.com>
---
 tools/testing/selftests/kvm/Makefile         |  2 +
 tools/testing/selftests/kvm/check-headers.sh | 55 ++++++++++++++++++++
 2 files changed, 57 insertions(+)
 create mode 100755 tools/testing/selftests/kvm/check-headers.sh

```
#### [PATCH v2] KVM: x86: Fix KVM_GET_CPUID2 ioctl to return cpuid entries count
##### From: Valeriy Vdovin <valeriy.vdovin@virtuozzo.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Valeriy Vdovin <valeriy.vdovin@virtuozzo.com>
X-Patchwork-Id: 12229661
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=unavailable autolearn_force=no
 version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 46339C43461
	for <kvm@archiver.kernel.org>; Wed, 28 Apr 2021 16:34:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 10A226141F
	for <kvm@archiver.kernel.org>; Wed, 28 Apr 2021 16:34:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S241089AbhD1QfR (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 28 Apr 2021 12:35:17 -0400
Received: from mail-eopbgr00120.outbound.protection.outlook.com
 ([40.107.0.120]:64900
        "EHLO EUR02-AM5-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S241085AbhD1QfQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 28 Apr 2021 12:35:16 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=nZLWMORLgty753KMH5SObPxXZNvND9s2ebTqeH1dCjSKaOR4cpUGPY/Si5/Mw/aLoxQos6n/UywOPGzcKvLUwSLBcFltf6qALlpMES1uGWiRUDXCpQw5ha4+jFc7Ry0j8XRik+1vS9MnUqYv8vtt4qCX2x8NQ8O3hzkVTYBPauVwd4dmZyuFEAy8Ogwr8dLy9u0OcePCnlfJaAZ+AM6MVqizZHgpInJL27E2nhjcMMKHEVylQ7mFxSjrwZkmup5VlOKCZpE0MpNEEze1pRq1a0QiYllgR+e0bWSdl/OfCSKTMj93n/qninNO6idgf5SfkszEvhZ85ebrH+R3MjnGOA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=LG8b5T/7bC0ajHUAn/zHuE8JnYQTZrQtyB9HkERNm0o=;
 b=k7q9XIBJGltyn5R13wtmxPGYZtiViC+JJvf/B0xZjpuVmdfbQgxULXRpcwWZPxowMk00B8rDlhH37PEGJKZtSfRJgyr2FIX04PPJT9dBiPd95YzFLoKGkuX4i0Sz7YATGYcujlEKexwdOSZh3+ZVz6UQfiOn7Mf51nWrLisn2a5hcGbXo7YfvCUWEDfOCFVe0iooGKwbrV0cnmfi5GF6RwLnFj7GEo1M1Sc7yEWz2NTjMBlYY/zCogpkct9zuJwkHAVSgmaT8gIBc64XDLyvtoWayaIOWTCCCJ8RrOURn9Etjw5JYi3un8OIvIvO3oYNwy1zSWXaH23uGzGO/sS6xg==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=virtuozzo.com; dmarc=pass action=none
 header.from=virtuozzo.com; dkim=pass header.d=virtuozzo.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=virtuozzo.com;
 s=selector2;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=LG8b5T/7bC0ajHUAn/zHuE8JnYQTZrQtyB9HkERNm0o=;
 b=kOtPwjDyyje8Qm917sToNjMU8YM429tEt1czCjzENi9oHCsl5G6YbCE9JN1uy3j1bv9SlbVz3oaeXxkD6p1ACKr2qL2ZMSN8peV/IV9gxKNCURIl+NfxzaOLTX2NlavocW5oThtBHZsERJnsfC61Q1br9kShscHAQoctj6FYtOY=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none
 header.from=virtuozzo.com;
Received: from AM9PR08MB5988.eurprd08.prod.outlook.com (2603:10a6:20b:283::19)
 by AM8PR08MB5714.eurprd08.prod.outlook.com (2603:10a6:20b:1dd::22) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4065.21; Wed, 28 Apr
 2021 16:34:29 +0000
Received: from AM9PR08MB5988.eurprd08.prod.outlook.com
 ([fe80::7d3f:e291:9411:c50f]) by AM9PR08MB5988.eurprd08.prod.outlook.com
 ([fe80::7d3f:e291:9411:c50f%7]) with mapi id 15.20.4065.028; Wed, 28 Apr 2021
 16:34:29 +0000
From: Valeriy Vdovin <valeriy.vdovin@virtuozzo.com>
To: linux-kernel@vger.kernel.org
Cc: Valeriy Vdovin <valeriy.vdovin@virtuozzo.com>,
        Denis Lunev <den@openvz.org>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Jonathan Corbet <corbet@lwn.net>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        x86@kernel.org, "H. Peter Anvin" <hpa@zytor.com>,
        Shuah Khan <shuah@kernel.org>,
        Aaron Lewis <aaronlewis@google.com>,
        Alexander Graf <graf@amazon.com>, Peter Xu <peterx@redhat.com>,
        Oliver Upton <oupton@google.com>,
        Andrew Jones <drjones@redhat.com>,
        Like Xu <like.xu@linux.intel.com>, kvm@vger.kernel.org,
        linux-doc@vger.kernel.org, linux-kselftest@vger.kernel.org
Subject: [PATCH v2] KVM: x86: Fix KVM_GET_CPUID2 ioctl to return cpuid entries
 count
Date: Wed, 28 Apr 2021 19:34:05 +0300
Message-Id: <20210428163408.20388-1-valeriy.vdovin@virtuozzo.com>
X-Mailer: git-send-email 2.17.1
X-Originating-IP: [176.106.247.78]
X-ClientProxiedBy: AM0PR08CA0034.eurprd08.prod.outlook.com
 (2603:10a6:208:d2::47) To AM9PR08MB5988.eurprd08.prod.outlook.com
 (2603:10a6:20b:283::19)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from localhost.localdomain (176.106.247.78) by
 AM0PR08CA0034.eurprd08.prod.outlook.com (2603:10a6:208:d2::47) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4087.27 via Frontend
 Transport; Wed, 28 Apr 2021 16:34:27 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 9a616f68-4c19-4384-d26b-08d90a637e8c
X-MS-TrafficTypeDiagnostic: AM8PR08MB5714:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <AM8PR08MB5714FA0D46D1353E21F2474187409@AM8PR08MB5714.eurprd08.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:10000;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 uES2wpZekReorgObGKArQfCrFUXckDLxJZqzZ9SEoUmBplb7axNqG/zYAP66XJNROF84i4Oqq0GmQxyuWZRtnCEVsdOADEd0AaWsuu1qztiFcWpYAQ5MsrCSdpM89LrVMrCbT4QJE0YCLBH1g79AiWyfsH95zeDBgloOmykwkq6eeBee5qy6tVNfSxVdGnMztAEvXsWK2dS0T44rg5pAQ9iPx5f3XyNAdQL8iWQAUTuUYYD10UfrPMdOYH/Phs1bv/KSqxldRXR8nm9inLJhetHkto4yTGGyhg+DCLZbhFVNETyez700z6oOIWzYOpjhPXsUQ1h4aDrsEVgKCkHdbq+X/+UuFkUs4prHrMpKZNwR2r8L+ghyL54np0zIiiW1jry+GA2rVS3Utz36BOSUm7rGVVQeHuMVF0KTpTfre8kYVXJubiDBHBd6vn3/+ms7ItKPZxdyW+kEbFgWkc4oeexak02jMKBXUvXyeC3nFdBtBgaaX8sMikjt3EbN15tJ4uL93y6tJLOCeDosb1+5t5JWkmm3EC81e8ZCnYKOBP9MpTYYdseqBdK73rn+neTK4LXnskGQkpjsUJaQARHga9MFCGkgcgXosqdI7RuVLfFumf6aDTlO7VuhBnaKZx8g1lKHeohsZl2ElS6yqTgPmUaK7CA50Zpn4II79nhmyrW8uU715l62Uo6WfFm8JMZy
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:AM9PR08MB5988.eurprd08.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(136003)(346002)(366004)(376002)(396003)(39830400003)(186003)(16526019)(4326008)(6916009)(26005)(8676002)(1076003)(6666004)(52116002)(5660300002)(6512007)(66556008)(54906003)(66946007)(66476007)(86362001)(36756003)(38350700002)(44832011)(2616005)(478600001)(2906002)(316002)(956004)(7416002)(8936002)(38100700002)(6486002)(83380400001)(6506007)(69590400013);DIR:OUT;SFP:1102;
X-MS-Exchange-AntiSpam-MessageData: 
 NCf8nsG+pu2ATYyc9JGuQwxOT5mqZHUMi8+UlidbXJdeyD5/FWsexkaIlzxONHFJUVv019NHNy+80ffW5UsZ5V8jtBGabLmSXOSq5hSTMde8VMrhKhGzN3700CZythoPEUe50+nYzRUNwaRWjdkUHppETWmFp77S+rK489H9aClM0e7Pypucqg7LjQDMn6tl2QU+Y/VJZZri96540UTMGG+F0cLgfOMIdFrUQfvIQQyZonTsj04wGzMOx9+FDz1f2GvdvLceNHVVQxcn6Kjy+OtavghsOmKo6H+34pUJZX6KqTPt720qlnV2TdsY3jl46Jxoxvl8UTSSHTqUvkGmLfRpbDfJiB/iMPt8UDmR7tde2rzBJfzFN20xFnCraO5CBknnjZieOmO/6UhZ54wan/zNFGmF3zLQUzNO25xAiuV5qQbTCr+NQtpavjzpIXhOL8TWE8yTOA/fQL5N2QaCQ0LlT0Sb/bGBOu12657W/iygJm9UyYmWsDfQgJj8gK9q9y+rFG3OwNTnH5qmNTYI3Zm+TIKiSMbrtr5mnDWzhBgzMdtzGs24LqxFEm+PKTN6DaLSvIXoU8RkswZQ2AfTQyLiOGSvN/Gkyqzf6WZ8GxExW290oLTBlB09yVAwK/GrJF4pNZOKQOzVFx7P8yPU/3lwXFkdr3PaIKMZZ+nhQf/D7RsIvP25u04/foT0TMrJIGcfIf1NGMh1YXKP1KUEYrMPSYGGtq7uuzNowpZGHDIiQFKqPyOO2mzgYSHefYpO
X-OriginatorOrg: virtuozzo.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 9a616f68-4c19-4384-d26b-08d90a637e8c
X-MS-Exchange-CrossTenant-AuthSource: AM9PR08MB5988.eurprd08.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 28 Apr 2021 16:34:29.3243
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 0bc7f26d-0264-416e-a6fc-8352af79c58f
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 z+QNq1hQ9CFwNA0a1CMBStkQ9y5A2bRsnTYps/1XZh4aFi3ur/vnbeesQW0rIoknFVYbLhwupzac/keBA5qK+IOD4x9J1ZDobuTGk+Z4hPs=
X-MS-Exchange-Transport-CrossTenantHeadersStamped: AM8PR08MB5714
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

KVM_GET_CPUID2 kvm ioctl is not very well documented, but the way it is
implemented in function kvm_vcpu_ioctl_get_cpuid2 suggests that even at
error path it will try to return number of entries to the caller. But
The dispatcher kvm vcpu ioctl dispatcher code in kvm_arch_vcpu_ioctl
ignores any output from this function if it sees the error return code.

It's very explicit by the code that it was designed to receive some
small number of entries to return E2BIG along with the corrected number.

This lost logic in the dispatcher code has been restored by removing the
lines that check for function return code and skip if error is found.
Without it, the ioctl caller will see both the number of entries and the
correct error.

In selftests relevant function vcpu_get_cpuid has also been modified to
utilize the number of cpuid entries returned along with errno E2BIG.

Signed-off-by: Valeriy Vdovin <valeriy.vdovin@virtuozzo.com>
---
v2: 
  - Added description to documentation of KVM_GET_CPUID2.
  - Copy back nent only if E2BIG is returned.

 Documentation/virt/kvm/api.rst                | 81 ++++++++++++-------
 arch/x86/kvm/x86.c                            | 11 ++-
 .../selftests/kvm/lib/x86_64/processor.c      | 20 +++--
 3 files changed, 73 insertions(+), 39 deletions(-)

```
#### [PATCH v3] KVM: x86: Fix KVM_GET_CPUID2 ioctl to return cpuid entries count
##### From: Valeriy Vdovin <valeriy.vdovin@virtuozzo.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Valeriy Vdovin <valeriy.vdovin@virtuozzo.com>
X-Patchwork-Id: 12229831
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=unavailable autolearn_force=no
 version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 0EDBBC433ED
	for <kvm@archiver.kernel.org>; Wed, 28 Apr 2021 17:21:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CD24D6143D
	for <kvm@archiver.kernel.org>; Wed, 28 Apr 2021 17:21:31 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S239248AbhD1RWM (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 28 Apr 2021 13:22:12 -0400
Received: from mail-db8eur05on2097.outbound.protection.outlook.com
 ([40.107.20.97]:14048
        "EHLO EUR05-DB8-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S229931AbhD1RWH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 28 Apr 2021 13:22:07 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=Kx5/TxnzHeu0zOsD+DitZxofzPt5Th+NY5TLtJcPM92MS8BLlUbHn+922uy7iceZk7PH0HU0YVFyhoy7o7QV85QZX/rf6j2qgSryzPv6PTkJohz4SBDCwPoQfJNHV3IRdETYRFLspvs0WH5er39fhSLpMSXuKDFJzN02hbEkTp+XugHIBt8TmUCW2fci84Eh6IYBKMgSgCRctwdOrUM3/9KfBzu0guxehUxF7prFeLPoQ5F9uD6S4nYE0n9tQTeINqlrqHJlIizVpr/N8eLORX+RYa28AiGwg+AHB9IS4TJMyIccN0XtFOB+TpMSW8ht5yudQoQ43EPn84dP9zVidg==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=PUsOmLQns1Jh8tj/9v4ddUPkij8uQ5cVgynwE8coHFc=;
 b=HugwTxAge+Pc6XaEE9MoRgOBYsDq8nUysi/c5oCxEuwuZHiUzN8x1imN8iKfI3Zj9mHt35w5B+9H+I4l2PLCarL5GgboPh7EYK65wIRAMj/O81F1GWUWusGM/6BqVjk0dPgOY8uC30LcI2xGsI7OQliSQO9CiyQdR/Z4AJCpVkJL9GxMb/A0p5dCrxezqsKEkqBtViIRAwEd9yunX6xFVhQRJO/HGziwcJ4JluMMnKs4KqCT/zHVjbURkl1ohybzfdqQEj0tcGWDABLvzVSWgKQA+ezZJNizsiDqU9g1H5byxyDtH3F2VSO1sHbuwdC9Vk7p4VO1x9Ql+PErNLikNQ==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=virtuozzo.com; dmarc=pass action=none
 header.from=virtuozzo.com; dkim=pass header.d=virtuozzo.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=virtuozzo.com;
 s=selector2;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=PUsOmLQns1Jh8tj/9v4ddUPkij8uQ5cVgynwE8coHFc=;
 b=X5LZNL1SggDTQnE651Ggb1pQTQnlYHbSdpS3N8it65lQqJH27GIzGTLdFIda6AVh8U+m2a2ntAZfq0idS1j2kZmh0a+MQ2XzEAA4lrqndfGs7ng/PYjQ23Uyl1X04NERgkacPEnx8FrZ3zGVmd5/QTUf+Hp5eQ0bTZwHZKuWkiY=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none
 header.from=virtuozzo.com;
Received: from AM9PR08MB5988.eurprd08.prod.outlook.com (2603:10a6:20b:283::19)
 by AM4PR0802MB2193.eurprd08.prod.outlook.com (2603:10a6:200:5b::9) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4065.24; Wed, 28 Apr
 2021 17:21:19 +0000
Received: from AM9PR08MB5988.eurprd08.prod.outlook.com
 ([fe80::7d3f:e291:9411:c50f]) by AM9PR08MB5988.eurprd08.prod.outlook.com
 ([fe80::7d3f:e291:9411:c50f%7]) with mapi id 15.20.4065.028; Wed, 28 Apr 2021
 17:21:19 +0000
From: Valeriy Vdovin <valeriy.vdovin@virtuozzo.com>
To: linux-kernel@vger.kernel.org
Cc: Valeriy Vdovin <valeriy.vdovin@virtuozzo.com>,
        Denis Lunev <den@openvz.org>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Jonathan Corbet <corbet@lwn.net>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        x86@kernel.org, "H. Peter Anvin" <hpa@zytor.com>,
        Shuah Khan <shuah@kernel.org>,
        Aaron Lewis <aaronlewis@google.com>,
        Alexander Graf <graf@amazon.com>,
        Like Xu <like.xu@linux.intel.com>,
        Andrew Jones <drjones@redhat.com>,
        Oliver Upton <oupton@google.com>, kvm@vger.kernel.org,
        linux-doc@vger.kernel.org, linux-kselftest@vger.kernel.org
Subject: [PATCH v3] KVM: x86: Fix KVM_GET_CPUID2 ioctl to return cpuid entries
 count
Date: Wed, 28 Apr 2021 20:20:26 +0300
Message-Id: <20210428172028.3339-1-valeriy.vdovin@virtuozzo.com>
X-Mailer: git-send-email 2.17.1
X-Originating-IP: [176.106.247.78]
X-ClientProxiedBy: AM4PR0202CA0014.eurprd02.prod.outlook.com
 (2603:10a6:200:89::24) To AM9PR08MB5988.eurprd08.prod.outlook.com
 (2603:10a6:20b:283::19)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from localhost.localdomain (176.106.247.78) by
 AM4PR0202CA0014.eurprd02.prod.outlook.com (2603:10a6:200:89::24) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4087.25 via Frontend
 Transport; Wed, 28 Apr 2021 17:21:18 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: acb01369-2e0e-4e6b-2fc8-08d90a6a09b3
X-MS-TrafficTypeDiagnostic: AM4PR0802MB2193:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <AM4PR0802MB21933DF2E652459B49E8F32787409@AM4PR0802MB2193.eurprd08.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:10000;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 Ov8LYXyE4eM5ICoHWhlPBdVDJYayzybW4+TOnFJuRPAVVt0YoZjPRFljQEu7qXgm4xBxTb/9ZM+7JubuL/umFHNVLAu3C5pasijy/hp0BM1zADaWslbWR8AgsBzGySW82K6v6ge/1aJMH4cUvrbVFBmHbz9uJ7lJmEMu5wUKy4viKkByHJ9YLzNBMZZLMlUDM9tMFVh4i/5N2KXMJZoU3v/KD1KjrHbrTU7Y4Nk35b2EeD5VBrZ8+uYnWscEPmyd83GbxD2BNwiCcfagK9R7oHa7jA74P4nN4lbxZwc+0KA8kUMdcSZwgoJ9rFjQGMOR/cCeeCrQeE5ZHxGEtXu+RENaFgeVgrIcUcqHP+xxGaL0IFc0LjtRSwsWIaNmOFlQA4tfpkm+lmUwKReb+7kOZXtQ8pWAJvasSUGGbZmQCpYlNfJYhZXmP6fzDnvrLVI3B5CF8sVrZaRTtXCHd09ePcdXM7+Kb+MopjQi3vyLGMa8FhhuXHKfMZFdjJKezPNz+26pE5dS+xWyd0I+2aiBQwaBGtAC7+tc5Mjb7Oi1vsIA/i9O1iHY6BcgLpHBsazlGLHQSJgQPIJFkvgEav8oPY+/kldduIm6Wo6ov3/ZmRTZlLE6hlRKYAQWoB7POUUtnlQi+RL/tfZZ3g7cEqb0bxNBJKwXXT5OZ0Vy2RwZwZ857yvy4avi7adLpXRmJzOH
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:AM9PR08MB5988.eurprd08.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(39830400003)(346002)(396003)(376002)(366004)(136003)(6506007)(2616005)(6486002)(66556008)(6512007)(1076003)(956004)(5660300002)(36756003)(66946007)(86362001)(2906002)(8676002)(8936002)(6916009)(44832011)(83380400001)(186003)(6666004)(16526019)(26005)(38350700002)(54906003)(52116002)(38100700002)(316002)(4326008)(478600001)(66476007)(7416002)(69590400013);DIR:OUT;SFP:1102;
X-MS-Exchange-AntiSpam-MessageData: 
 KGzQUabDtWV35YzNymhXifc+zPo8tn5+AkpjlpeBofxssE1HBksU+ainvN9/fM2uh0Zb2nnB9RBwVNNttngk8Ps0NJcrCHSOzzmqaAHXiniPrOojtefJ+7cEQDpYU8qoxPrHPhEE9fz44gzW147eoSTMktANa+MLHQvYze4Oerls5mYN4N9yySvWm7FFu59iWJVgEe+NOrUbhONetJojnnoYbPTMz/EduOruFBbEWlTbtTPbB3Zs5pDRMDuFeqOdfloIQdfzGFkGr5GAbNJiPEDaZ/+ob5qLa9eIXIe8rdGfBBzRBqQCbzejLEuhY0nJk34din0sRWaCwZXyiawC7vByia+2SfK7Sx42YgY473SpXdave4aE3ATNe7nrlYTZJil8GL+BRqryry6ENBhhhr93cNm6ic0KChyKXCii8DnMOiTw1GS/M/QcX5Xe5Q7G9o3CgIT4SdkX/Rn3h5Iqbl0vM1XeUce/xGH4rb23vlEU6q7wx8JBco5krabt4+YPwtcXp1YnMvz41cSHOVoxoc15U38VcNY0xIXfNzVVTrBT1HkanJtE3S0Nu7jN7UsOyY1ksYvAm+Ioy3iTTPFEJBMgGWbtzL5hkmM6eq6Ch8i/jdOjs4WWPpXDQCpvmQWnPyXmKwEf2XzVMCG00cgVPjF0KMjezEaFVe9in2YNSjU8yfMXYHPF3SLQsM4WG2nNc3TT3ZevLNAXkltGUNzt1BCRz45dzBDqhdtd5DAsAxs6IdB8GE+WKdcdD8Z4KbpGN5tDoymBijKdHBY/yH4pDXWj2Rko+o5PvNkfH8uWLtlfsY+klCbGLVZklQOc1Wr/Mje4rGABcNLTrPIwA0iin/w8UIKBA6rQ+iN6pVg9JFQFbkIlVO65vnNiOEUx991uYH7OVaxIrdb2bkdMDA3XueFTeX/SicVsupAEWC3BoN2W/Q4Hut20AzddLJCdMA2OSY28oKko+xlklhgb33ExfJznLYqNs4I9lMlXxZZGmL6DN/zOL5vNt2r/BFG53CMnRPKh9ur8wEN/oPdyRttaI7i98w5M7IKC2ljroSkcXjCE1XqVJeFR7zpiC3uA5o9CckXkSLbRSw+/WIQMC5DIDxIElX1LzLfhAWGP5J6PmL+hSJD2U+ceB82+NAC7a1WUjNqjF5potpaBHfZUYuXzHnqaVuNcffRTsj4rieSSU1/emAZA8LeqMiwDPVHA1lqP5NAP2PS0y4eYn/zf1TQ1Z79RQV8cBaKNeG0zA/Bg19eHYO6s1WQBo6jjfg+Yll6OG/opVQrhDTlYONU4CviXBu9pP1TZIMuN5CALvFOc+fl4oDNzXzcXJcaVnZ7STOMl
X-OriginatorOrg: virtuozzo.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 acb01369-2e0e-4e6b-2fc8-08d90a6a09b3
X-MS-Exchange-CrossTenant-AuthSource: AM9PR08MB5988.eurprd08.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 28 Apr 2021 17:21:19.7365
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 0bc7f26d-0264-416e-a6fc-8352af79c58f
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 LANXsNw4gxRe4ORUAGiLLqWcmAzjwJJ8u7hOaZBP4lwNrAJJw91iQn0GoH9/wezerNXrwwjPRfi9uAtPxj16FGmZucvcVcY3wyYZKkalbic=
X-MS-Exchange-Transport-CrossTenantHeadersStamped: AM4PR0802MB2193
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

KVM_GET_CPUID2 kvm ioctl is not very well documented, but the way it is
implemented in function kvm_vcpu_ioctl_get_cpuid2 suggests that even at
error path it will try to return number of entries to the caller. But
The dispatcher kvm vcpu ioctl dispatcher code in kvm_arch_vcpu_ioctl
ignores any output from this function if it sees the error return code.

It's very explicit by the code that it was designed to receive some
small number of entries to return E2BIG along with the corrected number.

This lost logic in the dispatcher code has been restored by removing the
lines that check for function return code and skip if error is found.
Without it, the ioctl caller will see both the number of entries and the
correct error.

In selftests relevant function vcpu_get_cpuid has also been modified to
utilize the number of cpuid entries returned along with errno E2BIG.

Signed-off-by: Valeriy Vdovin <valeriy.vdovin@virtuozzo.com>
---
v2:
  - Added description to documentation of KVM_GET_CPUID2.
  - Copy back nent only if E2BIG is returned.
	- Fixed error code sign. 

 Documentation/virt/kvm/api.rst                | 81 ++++++++++++-------
 arch/x86/kvm/x86.c                            | 11 ++-
 .../selftests/kvm/lib/x86_64/processor.c      | 20 +++--
 3 files changed, 73 insertions(+), 39 deletions(-)

```
#### [PATCH v4] KVM: x86: Fix KVM_GET_CPUID2 ioctl to return cpuid entries count
##### From: Valeriy Vdovin <valeriy.vdovin@virtuozzo.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Valeriy Vdovin <valeriy.vdovin@virtuozzo.com>
X-Patchwork-Id: 12229853
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=unavailable autolearn_force=no
 version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 89CA5C43460
	for <kvm@archiver.kernel.org>; Wed, 28 Apr 2021 17:27:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 54D2061431
	for <kvm@archiver.kernel.org>; Wed, 28 Apr 2021 17:27:48 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S241617AbhD1R2c (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 28 Apr 2021 13:28:32 -0400
Received: from mail-db8eur05on2105.outbound.protection.outlook.com
 ([40.107.20.105]:27009
        "EHLO EUR05-DB8-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S239542AbhD1R2a (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 28 Apr 2021 13:28:30 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=FAjk/UTmV2P7QAJbbV1INKU/gh/5isidjr8xQ185EM76MxcxNBQVRcPca1bAtYdlCOquxrGP+SNiePJ45k8H/NPqcvD0MtvXheQZVGifl1QPC3Qbhqa6zB+dVGukyNKTtbcjQow7WasOkNB3nnDUmu3epNOJMz3s+Hx1MzP0w11BYZgKdQkKmZSWEdjmTHrOTBW+wR3lXO2lPNB2+J8XuJKmj4Dwxux7MvcA15W1RGizOke3uBnQi56YHRJvFUhhADy6Fsm0Pef4jC+aQiYXDdukExGLsPbPQ4kAbOpcwg5M+UGnM2Rwm+oe0LIAzOMX4/a4Q9eHjDj5f1y1dAO7Ug==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=UBAM+oCKw/wuVHiDDW8O+AEHuIABJVQaq+DedHMME9I=;
 b=BEdv9KUHkK2JBpYSmjeTMGVnK6nkG32WMTNACDqHbE1grA3gE9pnVZKNJR4tfv51rqbk4DiDgSDEPdkjcXbRcHYAWTVzyFSy84xApyuJg3ZV8kY4HkpzVfINxbnVwsKJAoWLzuH8cZvq3f2UszdTaZAg+4DhXE0ym41+N13kD0Qz3n08r66lyvwqwg4QmwGJixfNDfpFufRO1k4SbUJmYdIV+a/whXz4uJbZ5ptc4kljxfY/CkI31XkgW0X+nBRnT11C5HTFKUwLSenoNXACSeiUU10jP0QwKI/PzAH9pGCO6eLxdAuGOGgbnwHVSuc0bCth8ES92dilKDtxF6eX5Q==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=virtuozzo.com; dmarc=pass action=none
 header.from=virtuozzo.com; dkim=pass header.d=virtuozzo.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=virtuozzo.com;
 s=selector2;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=UBAM+oCKw/wuVHiDDW8O+AEHuIABJVQaq+DedHMME9I=;
 b=NZgnuovdr5fMBNLkLSiaLsXpiZGAFVHGmE7zOMqAvVyviTrWJJvddDKGQnhRvY0csGDfxN8wkknPCmewLT3X4JYHV71Kt3/XrkOmPGvXN8cgslr2+m/rxnL1S+uE3N+gqcxKrNlo3097B9EZSGYAPEw+BsDftPd4Cr0VAyc8nIA=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none
 header.from=virtuozzo.com;
Received: from AM9PR08MB5988.eurprd08.prod.outlook.com (2603:10a6:20b:283::19)
 by AM9PR08MB6753.eurprd08.prod.outlook.com (2603:10a6:20b:309::14) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4065.21; Wed, 28 Apr
 2021 17:27:42 +0000
Received: from AM9PR08MB5988.eurprd08.prod.outlook.com
 ([fe80::7d3f:e291:9411:c50f]) by AM9PR08MB5988.eurprd08.prod.outlook.com
 ([fe80::7d3f:e291:9411:c50f%7]) with mapi id 15.20.4065.028; Wed, 28 Apr 2021
 17:27:42 +0000
From: Valeriy Vdovin <valeriy.vdovin@virtuozzo.com>
To: linux-kernel@vger.kernel.org
Cc: Valeriy Vdovin <valeriy.vdovin@virtuozzo.com>,
        Denis Lunev <den@openvz.org>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Jonathan Corbet <corbet@lwn.net>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        x86@kernel.org, "H. Peter Anvin" <hpa@zytor.com>,
        Shuah Khan <shuah@kernel.org>,
        Aaron Lewis <aaronlewis@google.com>,
        Alexander Graf <graf@amazon.com>,
        Andrew Jones <drjones@redhat.com>,
        Oliver Upton <oupton@google.com>,
        Like Xu <like.xu@linux.intel.com>, kvm@vger.kernel.org,
        linux-doc@vger.kernel.org, linux-kselftest@vger.kernel.org
Subject: [PATCH v4] KVM: x86: Fix KVM_GET_CPUID2 ioctl to return cpuid entries
 count
Date: Wed, 28 Apr 2021 20:27:26 +0300
Message-Id: <20210428172729.3551-1-valeriy.vdovin@virtuozzo.com>
X-Mailer: git-send-email 2.17.1
X-Originating-IP: [176.106.247.78]
X-ClientProxiedBy: AM0PR07CA0006.eurprd07.prod.outlook.com
 (2603:10a6:208:ac::19) To AM9PR08MB5988.eurprd08.prod.outlook.com
 (2603:10a6:20b:283::19)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from localhost.localdomain (176.106.247.78) by
 AM0PR07CA0006.eurprd07.prod.outlook.com (2603:10a6:208:ac::19) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4108.8 via Frontend
 Transport; Wed, 28 Apr 2021 17:27:40 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 6a65aef8-1d41-45cb-50b8-08d90a6aedc1
X-MS-TrafficTypeDiagnostic: AM9PR08MB6753:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <AM9PR08MB675317A85C5ECCD3418346AE87409@AM9PR08MB6753.eurprd08.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:10000;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 wravgZJiDH8noZn0wqCWGm1qbnsKeAQ0mB+VVRKmhLnVyazw5wPDn27f+rhhfPNnYpabyAk48xcsb9o2KyWDgfYLY6bDKY+elufH3LJKWPdt1DYdFnK6j0fTT5SJMfIOW/jDsz7bF7jRxysik/ISdiswVjZUtdMc8VfATFWQ5Euhu1rUZJhmJx+jjoCAtqBlouiELfkkEANzLhUvEmRY8sOV/qLw1zO09WsbnvHtvet43+AZGbIeyQLBF297UiNmcj9C7oyATPF3i7JmI5NX78pw+FjPMqx0N0gvOKBhSWJkhLWuWWXXl3dwDUIl7f7nubo7v3G4F8hXjBJNFKtEA7N1plXhAnWFIm6vOo8N3jNq9IagPtuMupIGqtAu/Yha+cbrA5FuaeZACquhMaJ8cMhKMNDWI7OK15dzMPgNTOFxHt0GCj8ZHoZlxswStLUKOHboCJG+3gJcsFaCCf8PhA1//nPF6gNjZ4KvEVi5PiqBQ/0viDRkNwdNAuQwmeJq/UdMWki3oDvVXaW1Gegqu0sjaNbKM9I0idTSIyzfYFkuFAypTMMKty23QqrvVIjwuRVYXlbeZiExhO63rKWBsKvYYRO/ww9gAnxvati9779ve8vyfq6RMGTXLl5o72hYOl1C2bNhP9lhk8SK3KYkzEB1sEpp7nJBLdA8DTt70i9mNs5Sxwa0tMnvC70fjrWj
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:AM9PR08MB5988.eurprd08.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(366004)(39840400004)(396003)(346002)(136003)(376002)(44832011)(54906003)(4326008)(16526019)(52116002)(186003)(38350700002)(38100700002)(2616005)(6666004)(956004)(316002)(6916009)(1076003)(36756003)(2906002)(6512007)(7416002)(6506007)(26005)(86362001)(8936002)(30864003)(66476007)(66946007)(8676002)(6486002)(66556008)(478600001)(5660300002)(83380400001)(69590400013);DIR:OUT;SFP:1102;
X-MS-Exchange-AntiSpam-MessageData: 
 RfL51SEtYHPB9wegSQ2If+N4bmZkSlYIj6FLlTnLsK5OB+u+9dlaQ+ewH491XBuDAx1JhFhIDIFFCbTa4td+ZUX1454QxscdIq8LinV7W7gVOoZpB+5ZGmAeGx+i3UX8zxVvCUSlgKWtmic3ZwHzqpk0ZGwKmhhCGNlhec7A65L0dmh+yoZXLCu32A7FQcP0gbbdZVp5OHtmNPcsZ/Jz9BkSMuaIxfO8vG+OFtqQv2Oz2/GYA0aS2OOrlgT2wplp/LVPL8MP2LnCJUf2+srO7B/6C/W4Syn9oF5alZbmCHA0nWmG/p2+r2KPwQfhFxpESWJ2pq+FQZ9aRK1f8lUQSHoqcH9lSSM8QDZsz03hWZrI5pqlSE90mSFCFnX3cb4FWrfloiyLiIuV/NIinXNsRJNcMbargwVeq01ABtPKONeQFEglGlPL4FvBtuepAdRUINkICgO6eHWHSLKYmsPQmGle1LNWWDczC0kb1oc9k2KS+f5Ms7nmos9zB6W/b6W9yd93H9KiCb2d095ERUCK/ZgaDhewwLZul3sa6WTBfaf5jojW8C9dn2E9itnpXMLiCTNzey8IafU9ymXKXkzpQlo06vsCJlbVJh19A+Cma2KuVbO2lkDQNgchoVi2oe8WpL9hAihlmjocmCEgHJ9R8u6XLDTChV4rTmTpp5wCAgX6mQTrTmdXm1R5AbmCixFp81dgkyzLU9sd9sVNcBthFHGTgdltlqXzR5FX/4iL4wkdaE+c7oIpnkJCAHmhr2hswqxWCI0JDnE3S3aTGsReL3debwKtojEm+RkRcPSplK5PYeN9yOys5UjDHmRGkhdXMkzATK3cZJIqBeP/FSgliYsUsiu0TEX+jSakmjUOik3t4ij0COWBsSez+7r/jN4JeMD7qFTEmYIAM8Qr1iUwfVILDm+jsLH4v49JJwKctuqVfOMRddbngecqTkqevgezPQ0GE9hsJaUxbbIjF1sZ68+XtX7MnRHrA5MA69TbGvka1NghGbERmNDGZXO1YOKvpinjMUT37nGAT6wGby65qTptSQvdPktqWHO2+WvI7oK5U80ImzGdhfl3e85qpe1/xqa5yo1ApUeb5SjflZ1UBL+eKAYWQuc6M6Q8ybsMqS0mBtayFm4QwBlvEmgnrMtzu/Ob7sHA66xdUIFYl0tbWndDEuwWfMAN7ECqTMaS+5R8s8zX7SXRDEd322URes9nAN81p0kTv18R38StKKJH0snD2yeMbq4G91CQjJ8CvzKbUfCLvxoDxq3XfYeAaxNIU/8xX5LD1ac7slllfKX3lBNpJ4nvTeelZk4T1Cy2fJAG7mNnbkGXUju5xT0p0hhG
X-OriginatorOrg: virtuozzo.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 6a65aef8-1d41-45cb-50b8-08d90a6aedc1
X-MS-Exchange-CrossTenant-AuthSource: AM9PR08MB5988.eurprd08.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 28 Apr 2021 17:27:42.2909
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 0bc7f26d-0264-416e-a6fc-8352af79c58f
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 T5H2pRoLqG7lRComFt96ZnvZPNS2SQfu0qYqSRpb3kZgs79kG2XCV0GJGcG8rYT5vYZv1qweNnrhNajS8JhtskYtVNg7NDRAGD0j6lpsdHY=
X-MS-Exchange-Transport-CrossTenantHeadersStamped: AM9PR08MB6753
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

KVM_GET_CPUID2 kvm ioctl is not very well documented, but the way it is
implemented in function kvm_vcpu_ioctl_get_cpuid2 suggests that even at
error path it will try to return number of entries to the caller. But
The dispatcher kvm vcpu ioctl dispatcher code in kvm_arch_vcpu_ioctl
ignores any output from this function if it sees the error return code.

It's very explicit by the code that it was designed to receive some
small number of entries to return E2BIG along with the corrected number.

This lost logic in the dispatcher code has been restored by removing the
lines that check for function return code and skip if error is found.
Without it, the ioctl caller will see both the number of entries and the
correct error.

In selftests relevant function vcpu_get_cpuid has also been modified to
utilize the number of cpuid entries returned along with errno E2BIG.

Signed-off-by: Valeriy Vdovin <valeriy.vdovin@virtuozzo.com>
---
v4:
  - Added description to documentation of KVM_GET_CPUID2.
  - Copy back nent only if E2BIG is returned.
  - Fixed error code sign. 
  - Corrected version message

 Documentation/virt/kvm/api.rst                | 81 ++++++++++++-------
 arch/x86/kvm/x86.c                            | 11 ++-
 .../selftests/kvm/lib/x86_64/processor.c      | 20 +++--
 3 files changed, 73 insertions(+), 39 deletions(-)

```
#### [PATCH 1/2] vDPA/ifcvf: record virtio notify base
##### From: Zhu Lingshan <lingshan.zhu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Zhu, Lingshan" <lingshan.zhu@intel.com>
X-Patchwork-Id: 12228343
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 86A96C433B4
	for <kvm@archiver.kernel.org>; Wed, 28 Apr 2021 08:27:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 54D3F61424
	for <kvm@archiver.kernel.org>; Wed, 28 Apr 2021 08:27:02 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S237528AbhD1I1p (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 28 Apr 2021 04:27:45 -0400
Received: from mga04.intel.com ([192.55.52.120]:7991 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S231635AbhD1I1o (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 28 Apr 2021 04:27:44 -0400
IronPort-SDR: 
 2zKtKa8S+oFbtnM2IwuXLgHv9V3XXQn3pNz3czSLjsEU69JDM1PljUhMfJd7yeZh0Z0A4jdY3j
 6GtUKV3tZaIw==
X-IronPort-AV: E=McAfee;i="6200,9189,9967"; a="194573424"
X-IronPort-AV: E=Sophos;i="5.82,257,1613462400";
   d="scan'208";a="194573424"
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by fmsmga104.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 28 Apr 2021 01:26:59 -0700
IronPort-SDR: 
 qF1yCpea3G+3k0EktqFIR0vwPr4mAoOu/4FPz7HSdbKMJoN2jdxgk3Hi++L/vcBgvGia0r+Isb
 D9KQ0yksG7rw==
X-IronPort-AV: E=Sophos;i="5.82,257,1613462400";
   d="scan'208";a="430192243"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.240.193.73])
  by orsmga008-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 28 Apr 2021 01:26:57 -0700
From: Zhu Lingshan <lingshan.zhu@intel.com>
To: jasowang@redhat.com, mst@redhat.com
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Zhu Lingshan <lingshan.zhu@intel.com>
Subject: [PATCH 1/2] vDPA/ifcvf: record virtio notify base
Date: Wed, 28 Apr 2021 16:21:32 +0800
Message-Id: <20210428082133.6766-2-lingshan.zhu@intel.com>
X-Mailer: git-send-email 2.27.0
In-Reply-To: <20210428082133.6766-1-lingshan.zhu@intel.com>
References: <20210428082133.6766-1-lingshan.zhu@intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This commit records virtio notify base addr to implemente
doorbell mapping feature

Signed-off-by: Zhu Lingshan <lingshan.zhu@intel.com>
Reported-by: kernel test robot <lkp@intel.com>
---
 drivers/vdpa/ifcvf/ifcvf_base.c | 1 +
 drivers/vdpa/ifcvf/ifcvf_base.h | 1 +
 2 files changed, 2 insertions(+)

```
#### [PATCH] x86/kvm: Use 'hlist_for_each_entry' to simplify code
##### From: Christophe JAILLET <christophe.jaillet@wanadoo.fr>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christophe JAILLET <christophe.jaillet@wanadoo.fr>
X-Patchwork-Id: 12228397
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 80599C433ED
	for <kvm@archiver.kernel.org>; Wed, 28 Apr 2021 09:08:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3F2006109E
	for <kvm@archiver.kernel.org>; Wed, 28 Apr 2021 09:08:51 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S237919AbhD1JJe (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 28 Apr 2021 05:09:34 -0400
Received: from smtp12.smtpout.orange.fr ([80.12.242.134]:53378 "EHLO
        smtp.smtpout.orange.fr" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S232153AbhD1JJe (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 28 Apr 2021 05:09:34 -0400
Received: from localhost.localdomain ([86.243.172.93])
        by mwinf5d23 with ME
        id y98k2400a21Fzsu0398lpr; Wed, 28 Apr 2021 11:08:48 +0200
X-ME-Helo: localhost.localdomain
X-ME-Auth: Y2hyaXN0b3BoZS5qYWlsbGV0QHdhbmFkb28uZnI=
X-ME-Date: Wed, 28 Apr 2021 11:08:48 +0200
X-ME-IP: 86.243.172.93
From: Christophe JAILLET <christophe.jaillet@wanadoo.fr>
To: pbonzini@redhat.com, seanjc@google.com, vkuznets@redhat.com,
        wanpengli@tencent.com, jmattson@google.com, joro@8bytes.org,
        tglx@linutronix.de, mingo@redhat.com, bp@alien8.de, x86@kernel.org,
        hpa@zytor.com
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        kernel-janitors@vger.kernel.org,
        Christophe JAILLET <christophe.jaillet@wanadoo.fr>
Subject: [PATCH] x86/kvm: Use 'hlist_for_each_entry' to simplify code
Date: Wed, 28 Apr 2021 11:08:43 +0200
Message-Id: 
 <29796ca9a5d4255c2a0260c2f5c829539a6e7d88.1619600757.git.christophe.jaillet@wanadoo.fr>
X-Mailer: git-send-email 2.30.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Use 'hlist_for_each_entry' instead of hand writing it.
This saves a few lines of code.

Signed-off-by: Christophe JAILLET <christophe.jaillet@wanadoo.fr>
---
Compile tested only
---
 arch/x86/kernel/kvm.c | 13 ++++---------
 1 file changed, 4 insertions(+), 9 deletions(-)

```
