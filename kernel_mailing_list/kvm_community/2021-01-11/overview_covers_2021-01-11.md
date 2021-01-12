

#### [PATCH 0/2] sysemu: Let VMChangeStateHandler take boolean 'running'
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>

```c
From patchwork Mon Jan 11 15:20:18 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
 <philmd@redhat.com>
X-Patchwork-Id: 12010987
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-19.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 2F46BC433E6
	for <kvm@archiver.kernel.org>; Mon, 11 Jan 2021 15:22:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id EDAC8229C4
	for <kvm@archiver.kernel.org>; Mon, 11 Jan 2021 15:22:03 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731169AbhAKPVy (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 11 Jan 2021 10:21:54 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:43157 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1730627AbhAKPVx (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 11 Jan 2021 10:21:53 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1610378427;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=Ucd06r2eJPcCIqt9QCTk/uw4j4Vi5AVfWPojlXh2MWo=;
        b=in1dkHa8UBwH1v4cwuMmfdnOJYCHq5c16Xl2flaViqNK3WrpC17bVR9fZLfdlo1fsu1rCq
        bx3WfGy1663PHc/rnpwRyiFwiX5izWeCbL6jk7uWxrxnBPWPxxbiQcRUlxzuURFVucy04c
        AQ0uPcp9tx2YPiqgTvg3ygwAaFkxDp8=
Received: from mail-ej1-f70.google.com (mail-ej1-f70.google.com
 [209.85.218.70]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-319-6wIwBHTENWyPWPeJWLFAFQ-1; Mon, 11 Jan 2021 10:20:25 -0500
X-MC-Unique: 6wIwBHTENWyPWPeJWLFAFQ-1
Received: by mail-ej1-f70.google.com with SMTP id r26so41459ejx.6
        for <kvm@vger.kernel.org>; Mon, 11 Jan 2021 07:20:25 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=Ucd06r2eJPcCIqt9QCTk/uw4j4Vi5AVfWPojlXh2MWo=;
        b=CDBAEf7HUJ4iN4Ra88+VAvh0F111YGppYkLaU0Ls2zZ0+10ETSmyJBi88tpg0EjSWC
         eqd1NcKrg7TZf1RguhharBVlxxAZZv4RQ6wD3DcwNT8eAJepzImz3Jo/qggNv4yloD7u
         JLkBr+LcAH8Ap6DX0Ky6K593IQao8ef5X3HeiO51EqdQZG2p6mNvCgy26zGncE8rhnd6
         IRZqA31bqpURoAizyhegK2oYtFBqpKrbct41sFPq19K2T5BhEUjr2KcOYZb49WY8JkjU
         V0upGYjDPgtuH/eqOyAJJ4Z8gvNJQ1YO8oUnDuDI4G6/vuuR+AX+3/RWDISxShg52ZZf
         2/Bg==
X-Gm-Message-State: AOAM532kUkS4vsqeJaw2oWPnSDacY73wDjtKDDZjQYFJ3R5UqoMDI1Cl
        KPbIi6eDRuxucP4YK2CrDqXgg01i8tZXlAeAzBYLutKoxaDa0pqicl9qboMMgss98K/K+FU/GOR
        qmbVu6VPvVJhI
X-Received: by 2002:a17:907:e9e:: with SMTP id
 ho30mr11282826ejc.529.1610378424338;
        Mon, 11 Jan 2021 07:20:24 -0800 (PST)
X-Google-Smtp-Source: 
 ABdhPJywxJElqigN/5jUO+VSUtxZXH9MfGPzYtOFdIcNPFnX2mDokjoLqsfHorN2m3Haq800FJrUjA==
X-Received: by 2002:a17:907:e9e:: with SMTP id
 ho30mr11282789ejc.529.1610378424080;
        Mon, 11 Jan 2021 07:20:24 -0800 (PST)
Received: from x1w.redhat.com (129.red-88-21-205.staticip.rima-tde.net.
 [88.21.205.129])
        by smtp.gmail.com with ESMTPSA id
 y17sm7157263ejj.84.2021.01.11.07.20.21
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 11 Jan 2021 07:20:23 -0800 (PST)
From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>
To: qemu-devel@nongnu.org
Cc: Huacai Chen <chenhuacai@kernel.org>, Greg Kurz <groug@kaod.org>,
 "Michael S. Tsirkin" <mst@redhat.com>, qemu-trivial@nongnu.org,
 Amit Shah <amit@kernel.org>, Dmitry Fleytman <dmitry.fleytman@gmail.com>,
 qemu-arm@nongnu.org, John Snow <jsnow@redhat.com>, qemu-s390x@nongnu.org,
 Paul Durrant <paul@xen.org>, Anthony Perard <anthony.perard@citrix.com>,
 Eduardo Habkost <ehabkost@redhat.com>, =?utf-8?q?Philippe_Mathieu-Daud?=
	=?utf-8?q?=C3=A9?= <philmd@redhat.com>, Gerd Hoffmann <kraxel@redhat.com>,
 Kevin Wolf <kwolf@redhat.com>, Marcelo Tosatti <mtosatti@redhat.com>,
 Max Reitz <mreitz@redhat.com>, Alex Williamson <alex.williamson@redhat.com>,
 Aurelien Jarno <aurelien@aurel32.net>,
 Aleksandar Rikalo <aleksandar.rikalo@syrmia.com>,
 Marcel Apfelbaum <marcel.apfelbaum@gmail.com>,
 Jason Wang <jasowang@redhat.com>, Peter Maydell <peter.maydell@linaro.org>,
	=?utf-8?q?C=C3=A9dric_Le_Goater?= <clg@kaod.org>,
 Halil Pasic <pasic@linux.ibm.com>, Fam Zheng <fam@euphon.net>,
 qemu-ppc@nongnu.org, Paolo Bonzini <pbonzini@redhat.com>,
 kvm@vger.kernel.org, Stefano Stabellini <sstabellini@kernel.org>,
 xen-devel@lists.xenproject.org, Cornelia Huck <cohuck@redhat.com>,
 David Hildenbrand <david@redhat.com>, qemu-block@nongnu.org,
 Christian Borntraeger <borntraeger@de.ibm.com>,
 Sunil Muthuswamy <sunilmut@microsoft.com>,
 David Gibson <david@gibson.dropbear.id.au>,
 Richard Henderson <richard.henderson@linaro.org>, =?utf-8?q?Alex_Benn=C3=A9?=
	=?utf-8?q?e?= <alex.bennee@linaro.org>, Laurent Vivier <laurent@vivier.eu>,
 Thomas Huth <thuth@redhat.com>, Stefan Hajnoczi <stefanha@redhat.com>,
 Jiaxun Yang <jiaxun.yang@flygoat.com>
Subject: [PATCH 0/2] sysemu: Let VMChangeStateHandler take boolean 'running'
 argument
Date: Mon, 11 Jan 2021 16:20:18 +0100
Message-Id: <20210111152020.1422021-1-philmd@redhat.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Trivial prototype change to clarify the use of the 'running'
argument of VMChangeStateHandler.

Green CI:
https://gitlab.com/philmd/qemu/-/pipelines/239497352

Philippe Mathieu-Daudé (2):
  sysemu/runstate: Let runstate_is_running() return bool
  sysemu: Let VMChangeStateHandler take boolean 'running' argument

 include/sysemu/runstate.h   | 12 +++++++++---
 target/arm/kvm_arm.h        |  2 +-
 target/ppc/cpu-qom.h        |  2 +-
 accel/xen/xen-all.c         |  2 +-
 audio/audio.c               |  2 +-
 block/block-backend.c       |  2 +-
 gdbstub.c                   |  2 +-
 hw/block/pflash_cfi01.c     |  2 +-
 hw/block/virtio-blk.c       |  2 +-
 hw/display/qxl.c            |  2 +-
 hw/i386/kvm/clock.c         |  2 +-
 hw/i386/kvm/i8254.c         |  2 +-
 hw/i386/kvmvapic.c          |  2 +-
 hw/i386/xen/xen-hvm.c       |  2 +-
 hw/ide/core.c               |  2 +-
 hw/intc/arm_gicv3_its_kvm.c |  2 +-
 hw/intc/arm_gicv3_kvm.c     |  2 +-
 hw/intc/spapr_xive_kvm.c    |  2 +-
 hw/misc/mac_via.c           |  2 +-
 hw/net/e1000e_core.c        |  2 +-
 hw/nvram/spapr_nvram.c      |  2 +-
 hw/ppc/ppc.c                |  2 +-
 hw/ppc/ppc_booke.c          |  2 +-
 hw/s390x/tod-kvm.c          |  2 +-
 hw/scsi/scsi-bus.c          |  2 +-
 hw/usb/hcd-ehci.c           |  2 +-
 hw/usb/host-libusb.c        |  2 +-
 hw/usb/redirect.c           |  2 +-
 hw/vfio/migration.c         |  2 +-
 hw/virtio/virtio-rng.c      |  2 +-
 hw/virtio/virtio.c          |  2 +-
 net/net.c                   |  2 +-
 softmmu/memory.c            |  2 +-
 softmmu/runstate.c          |  4 ++--
 target/arm/kvm.c            |  2 +-
 target/i386/kvm/kvm.c       |  2 +-
 target/i386/sev.c           |  2 +-
 target/i386/whpx/whpx-all.c |  2 +-
 target/mips/kvm.c           |  4 ++--
 ui/gtk.c                    |  2 +-
 ui/spice-core.c             |  2 +-
 41 files changed, 51 insertions(+), 45 deletions(-)
```
#### [PATCH 0/2] Use static_call for kvm_x86_ops
##### From: Jason Baron <jbaron@akamai.com>

```c
From patchwork Mon Jan 11 16:57:26 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Baron <jbaron@akamai.com>
X-Patchwork-Id: 12011171
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-14.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 49976C43381
	for <kvm@archiver.kernel.org>; Mon, 11 Jan 2021 17:20:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1D07122AAD
	for <kvm@archiver.kernel.org>; Mon, 11 Jan 2021 17:20:41 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2389173AbhAKRU0 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 11 Jan 2021 12:20:26 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:46156 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729496AbhAKRU0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 11 Jan 2021 12:20:26 -0500
X-Greylist: delayed 1133 seconds by postgrey-1.37 at
 lindbergh.monkeyblade.net; Mon, 11 Jan 2021 09:19:41 PST
Received: from mx0b-00190b01.pphosted.com (mx0b-00190b01.pphosted.com
 [IPv6:2620:100:9005:57f::1])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 15281C0617A4;
        Mon, 11 Jan 2021 09:19:40 -0800 (PST)
Received: from pps.filterd (m0050096.ppops.net [127.0.0.1])
        by m0050096.ppops.net-00190b01. (8.16.0.43/8.16.0.43) with SMTP id
 10BGwxLv017013;
        Mon, 11 Jan 2021 17:00:18 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=akamai.com;
 h=from : to : cc :
 subject : date : message-id; s=jan2016.eng;
 bh=7+uzNxtC4FyCIlNoqbVSn/Wrjh14z/hSraiASi7Xzh0=;
 b=CZ7Ngs/q3Gkqw5ZzS/0Uc8g6xQIZbJS4/ugbj1mOhBqOoabjx6A8FZBCwECGKkEiue/b
 Wxtk504NlIpBzgXVSmJsKqQ4zYkxR6XM6JJzhadSU/rQ1T1VY50JR4Nwf2s4u+ESjP9B
 G+Ekb0en6f0XfkYzJjS66yUlglhiLyjY3A7qkXPIfHKBBByUDyhe9LdfYcQm5v32LcCo
 Vl2I2RAay+NqbR3/a/eUUho5AdIzu6Bt90luziQoItz3m7ehjL1QEfYhwmXEll5okkro
 rS0j34w/+XoVtlbpsD+G5kkcC1DJk2E0Pa9Xk+PKUZrIryvbFQGEhZXDPTCW84glZeRE jQ==
Received: from prod-mail-ppoint4
 (a72-247-45-32.deploy.static.akamaitechnologies.com [72.247.45.32] (may be
 forged))
        by m0050096.ppops.net-00190b01. with ESMTP id 35y5sde7e5-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 11 Jan 2021 17:00:18 +0000
Received: from pps.filterd (prod-mail-ppoint4.akamai.com [127.0.0.1])
        by prod-mail-ppoint4.akamai.com (8.16.0.43/8.16.0.43) with SMTP id
 10BGn2N2017988;
        Mon, 11 Jan 2021 12:00:04 -0500
Received: from prod-mail-relay18.dfw02.corp.akamai.com ([172.27.165.172])
        by prod-mail-ppoint4.akamai.com with ESMTP id 35y8q31qwx-1;
        Mon, 11 Jan 2021 12:00:04 -0500
Received: from bos-lpjec.145bw.corp.akamai.com (unknown [172.28.3.71])
        by prod-mail-relay18.dfw02.corp.akamai.com (Postfix) with ESMTP id
 15614400;
        Mon, 11 Jan 2021 17:00:04 +0000 (GMT)
From: Jason Baron <jbaron@akamai.com>
To: pbonzini@redhat.com, kvm@vger.kernel.org
Cc: tglx@linutronix.de, mingo@redhat.com, bp@alien8.de,
        peterz@infradead.org, aarcange@redhat.com, x86@kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH 0/2] Use static_call for kvm_x86_ops
Date: Mon, 11 Jan 2021 11:57:26 -0500
Message-Id: <cover.1610379877.git.jbaron@akamai.com>
X-Mailer: git-send-email 2.7.4
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.343,18.0.737
 definitions=2021-01-11_28:2021-01-11,2021-01-11 signatures=0
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 adultscore=0
 mlxscore=0 malwarescore=0
 spamscore=0 bulkscore=0 suspectscore=0 phishscore=0 mlxlogscore=540
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2101110098
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.343,18.0.737
 definitions=2021-01-11_28:2021-01-11,2021-01-11 signatures=0
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 mlxscore=0
 malwarescore=0 phishscore=0
 spamscore=0 mlxlogscore=454 suspectscore=0 impostorscore=0 bulkscore=0
 clxscore=1015 priorityscore=1501 adultscore=0 lowpriorityscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2101110099
X-Agari-Authentication-Results: mx.akamai.com;
 spf=${SPFResult} (sender IP is 72.247.45.32)
 smtp.mailfrom=jbaron@akamai.com smtp.helo=prod-mail-ppoint4
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

Convert kvm_x86_ops to use static_call. Shows good performance
gains for cpuid loop micro-benchmark (resulsts included in patch 2).

Thanks,

-Jason

Jason Baron (2):
  KVM: x86: introduce definitions to support static calls for kvm_x86_ops
  KVM: x86: use static calls to reduce kvm_x86_ops overhead

 arch/x86/include/asm/kvm_host.h |  71 +++++++++-
 arch/x86/kvm/cpuid.c            |   2 +-
 arch/x86/kvm/hyperv.c           |   4 +-
 arch/x86/kvm/irq.c              |   2 +-
 arch/x86/kvm/kvm_cache_regs.h   |  10 +-
 arch/x86/kvm/lapic.c            |  28 ++--
 arch/x86/kvm/mmu.h              |   6 +-
 arch/x86/kvm/mmu/mmu.c          |  12 +-
 arch/x86/kvm/mmu/spte.c         |   2 +-
 arch/x86/kvm/pmu.c              |   2 +-
 arch/x86/kvm/trace.h            |   4 +-
 arch/x86/kvm/x86.c              | 299 ++++++++++++++++++++--------------------
 arch/x86/kvm/x86.h              |   6 +-
 13 files changed, 259 insertions(+), 189 deletions(-)
```
#### [PATCH v5 00/16] KVM: Add minimal support for Xen HVM guests
##### From: David Woodhouse <dwmw2@infradead.org>

```c
From patchwork Mon Jan 11 19:57:09 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: David Woodhouse <dwmw2@infradead.org>
X-Patchwork-Id: 12011619
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 27628C433DB
	for <kvm@archiver.kernel.org>; Mon, 11 Jan 2021 19:58:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D941A22CE3
	for <kvm@archiver.kernel.org>; Mon, 11 Jan 2021 19:58:56 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2391422AbhAKT6z (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 11 Jan 2021 14:58:55 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:52204 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2391405AbhAKT6x (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 11 Jan 2021 14:58:53 -0500
Received: from casper.infradead.org (casper.infradead.org
 [IPv6:2001:8b0:10b:1236::1])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id D991EC0617A7
        for <kvm@vger.kernel.org>; Mon, 11 Jan 2021 11:57:56 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; q=dns/txt; c=relaxed/relaxed;
        d=infradead.org; s=casper.20170209;
 h=Sender:Content-Transfer-Encoding:
        Content-Type:MIME-Version:Message-Id:Date:Subject:Cc:To:From:Reply-To:
        Content-ID:Content-Description:In-Reply-To:References;
        bh=MPnGeTXXSDHQnncDdsvtf1rAofte1AgKCB/siFe7Psk=;
 b=nxLj2JUfAcGxDLnsgEU2dLCnmJ
        OY/3K5D0Jp6b8hKhHSsg2mtNG2RxWut55D6Dch1LFJC/KobKMwWhGEsFFOtb1Z/9BOqDelMDo8p3u
        tVQ3AVLzlDgyr29djAZZXDx2GuA+DwD0F6rC3rnEDwJy5M+EJ5Tllai+vp/Fk5OaE2IBYzhRRmLmE
        iY1iJbjTWczinEAsb+vAL/x9WaFiuZYSjKDuzURy4B8O9Xdyxixrr9PrkIYKQmn9XPtkozbhKpfSj
        1u9+YA90d9aUCQSSkRxujuKeGMUQBWr9HjjVQp9aLsgwPU/uHgLMy4OZX3OB1A/g/qjfX+Dxz5s1E
        qk8WTvkg==;
Received: from i7.infradead.org ([2001:8b0:10b:1:21e:67ff:fecb:7a92])
        by casper.infradead.org with esmtpsa (Exim 4.94 #2 (Red Hat Linux))
        id 1kz3Jf-003kSV-SH; Mon, 11 Jan 2021 19:57:37 +0000
Received: from dwoodhou by i7.infradead.org with local (Exim 4.94 #2 (Red Hat
 Linux))
        id 1kz3Jf-0001HM-Ca; Mon, 11 Jan 2021 19:57:27 +0000
From: David Woodhouse <dwmw2@infradead.org>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Ankur Arora <ankur.a.arora@oracle.com>,
        Joao Martins <joao.m.martins@oracle.com>,
        Boris Ostrovsky <boris.ostrovsky@oracle.com>,
        Sean Christopherson <seanjc@google.com>, graf@amazon.com,
        iaslan@amazon.de, pdurrant@amazon.com, aagch@amazon.com,
        fandree@amazon.com, hch@infradead.org
Subject: [PATCH v5 00/16] KVM: Add minimal support for Xen HVM guests
Date: Mon, 11 Jan 2021 19:57:09 +0000
Message-Id: <20210111195725.4601-1-dwmw2@infradead.org>
X-Mailer: git-send-email 2.29.2
MIME-Version: 1.0
Sender: David Woodhouse <dwmw2@infradead.org>
X-SRS-Rewrite: SMTP reverse-path rewritten from <dwmw2@infradead.org> by
 casper.infradead.org. See http://www.infradead.org/rpr.html
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch set provides enough kernel support to allow hosting Xen HVM 
guests in KVM. It allows hypercalls to be trapped to userspace for 
handling, uses the existing KVM functions for writing system clock and 
pvclock information to Xen shared pages, and adds Xen runstate info and 
event channel upcall vector delivery.

It's based on the first section of a patch set that Joao posted as 
RFC last year^W^W in 2019:

https://lore.kernel.org/kvm/20190220201609.28290-1-joao.m.martins@oracle.com/

I've updated and reworked the original a bit, including (in my v1):
 • Support for 32-bit guests
 • 64-bit second support in wallclock
 • Time counters for runnable/blocked states in runstate support
 • Self-tests
 • Fixed Viridian coexistence
 • No new KVM_CAP_XEN_xxx, just more bits returned by KVM_CAP_XEN_HVM

v2: 
 • Remember the RCU read-critical sections on using the shared info pages
 • Fix 32-bit build of compat structures (which we use there too)
 • Use RUNSTATE_blocked as initial state not RUNSTATE_runnable
 • Include documentation, add cosmetic KVM_XEN_HVM_CONFIG_HYPERCALL_MSR

v3:
 • Stop mapping the shared pages; use kvm_guest_write_cached() instead.
 • Use kvm_setup_pvclock_page() for Xen pvclock writes too.
 • Fix CPU numbering confusion and update documentation accordingly.
 • Support HVMIRQ_callback_vector delivery based on evtchn_upcall_pending.

v4:
 • Rebase on top of the KVM changes merged into 5.11-rc1.
 • Drop the kvm_{un,}map_gfn() cleanup as it isn't used since v2 anyway.
 • Trivial cosmetic cleanup (superfluous parens, remove declaration of a
   function removed in v3, etc.)

v5:
 • Rebased onto kvm/next as of 2021-01-08 (commit 872f36eb0b0f4).
 • Fix error handling for XEN_HVM_GET_ATTR.
 • Stop moving struct kvm_host_map definition; it's not used any more.
 • Add explicit padding to struct kvm_xen_hvm_attr to make it have
   identical layout on 32-bit vs. 64-bit machines.

With the addition in v3 of the callback vector support, we can now 
successfully boot Linux guests. Other callback types can be handled 
entirely from userspace, but the vector injection needs kernel support 
because it doesn't quite work to inject it as ExtINT.

We will work on a little bit more event channel offload in future patches,
as discussed, but those are purely optimisations. There's a bunch of work
for us to do in userspace before those get to the top of our list, and
this patch set should be functionally complete as it is.

We're working on pushing out rust-vmm support to make use of this, and
Joao's qemu patches from last year should still also work with minor
tweaks where I've "improved" the KVM←→userspace ABI.
David Woodhouse (7):
      KVM: x86/xen: Fix coexistence of Xen and Hyper-V hypercalls
      KVM: x86/xen: latch long_mode when hypercall page is set up
      KVM: x86/xen: add definitions of compat_shared_info, compat_vcpu_info
      xen: add wc_sec_hi to struct shared_info
      KVM: x86: declare Xen HVM shared info capability and add test case
      KVM: Add documentation for Xen hypercall and shared_info updates
      KVM: x86/xen: Add event channel interrupt vector upcall

Joao Martins (9):
      KVM: x86/xen: fix Xen hypercall page msr handling
      KVM: x86/xen: intercept xen hypercalls if enabled
      KVM: x86/xen: add KVM_XEN_HVM_SET_ATTR/KVM_XEN_HVM_GET_ATTR
      KVM: x86/xen: register shared_info page
      KVM: x86/xen: update wallclock region
      KVM: x86/xen: register vcpu info
      KVM: x86/xen: setup pvclock updates
      KVM: x86/xen: register vcpu time info region
      KVM: x86/xen: register runstate info

 Documentation/virt/kvm/api.rst                     | 124 +++++-
 arch/x86/include/asm/kvm_host.h                    |  24 +
 arch/x86/include/asm/xen/interface.h               |   3 +
 arch/x86/kvm/Makefile                              |   2 +-
 arch/x86/kvm/hyperv.c                              |  40 +-
 arch/x86/kvm/irq.c                                 |   7 +
 arch/x86/kvm/trace.h                               |  36 ++
 arch/x86/kvm/x86.c                                 | 134 ++++--
 arch/x86/kvm/x86.h                                 |   1 +
 arch/x86/kvm/xen.c                                 | 495 +++++++++++++++++++++
 arch/x86/kvm/xen.h                                 |  68 +++
 include/uapi/linux/kvm.h                           |  50 +++
 include/xen/interface/xen.h                        |   4 +-
 tools/testing/selftests/kvm/Makefile               |   3 +
 tools/testing/selftests/kvm/lib/kvm_util.c         |   1 +
 .../testing/selftests/kvm/x86_64/xen_shinfo_test.c | 194 ++++++++
 .../testing/selftests/kvm/x86_64/xen_vmcall_test.c | 150 +++++++
 17 files changed, 1273 insertions(+), 63 deletions(-)
```
