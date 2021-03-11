

#### [RFC PATCH 0/4] KVM: stats: Retrieve statistics data in binary format
##### From: Jing Zhang <jingzhangos@google.com>

```c
From patchwork Wed Mar 10 00:30:20 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jing Zhang <jingzhangos@google.com>
X-Patchwork-Id: 12126741
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B9B18C4332D
	for <kvm@archiver.kernel.org>; Wed, 10 Mar 2021 00:31:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A477D64FF7
	for <kvm@archiver.kernel.org>; Wed, 10 Mar 2021 00:31:46 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231341AbhCJAbP (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 9 Mar 2021 19:31:15 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:47990 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S231335AbhCJAam (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 9 Mar 2021 19:30:42 -0500
Received: from mail-io1-xd49.google.com (mail-io1-xd49.google.com
 [IPv6:2607:f8b0:4864:20::d49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id B311CC061762
        for <kvm@vger.kernel.org>; Tue,  9 Mar 2021 16:30:42 -0800 (PST)
Received: by mail-io1-xd49.google.com with SMTP id x26so11677654ior.7
        for <kvm@vger.kernel.org>; Tue, 09 Mar 2021 16:30:42 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=1BcHrgVIevscHGOPbP9Sxwife20LoA3ZZqd9CRbz5Bw=;
        b=DKv71NfHgZl9K+3WTTgnMIMFhTJhw0KdiZ+0DsSSoWMbruSU8JYpotmsteHcMpFnKP
         p3oJl9d7poG/uNqx9QVjZxRsDg84eU0xeqR/z3zNbVYX8v/8Pqaq2D2o6XtuLtoQIAWn
         XZIko6RjucQT9l8eCAbgMb2o84jv4v0MYqAUW+gbWQ/6DAdn7cgT09hkIvc7uvV40U3/
         OXNI1psrB1fZwZO3xGQK35hCSkEnWUaO1l3/peXbxmeOQdZwn1Qj3XsVRuxh8uptWwNf
         ZpoGFHSOUGyGujS8e+ldyI4tL/z2BcdRYhlTSsMqOPaw7n36OXxIcUJIiplu0hMkQaNX
         IFPw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=1BcHrgVIevscHGOPbP9Sxwife20LoA3ZZqd9CRbz5Bw=;
        b=OzL4j5+3NWUcMoxiVkt+3Yt5PkC1RwrwcLkZeLO80de7jMYeyBrGIBh5BJ4SlZIsgG
         Imj1lNW804Mb0Qn/dQbOcB2Z72zG4vef2fjgunG62f+QSFL81bdoVnoGMwh2KPkg+99Z
         0DsnWQvleMBaVqWRNryvfOpB1el7Aejg/bSNMIb7+L0329dglBJpPO+Y7D9kYPLRYqZY
         zKAH1hvVqoahehGIZKX3YoQYlNALB7/h4UFARkPRaT3IgsKxaJ6ZOqi1iaT6eJS6iw2a
         leEvcZnLq8Vn4EkTnu4NormGhHSvUgf4GmjmILkzT+GNcHhZo1klvV1ztrORonrZCtIF
         zFtg==
X-Gm-Message-State: AOAM5338U71GYQjPUYhNT1fvXr0VdrNnAxNdDdC6KJaMf4d/4zvRHulz
        l9zif+8mPtIDiz20WPs8JJYHWlYcEUeY0h+2X0CZ8RaA1nsbehL/v1FGovasKut0bP/V1WL7G0B
        DOXCKlGAFIeUwuP8wvRQKDOFnzoIPBHYGPKPJt+9LYdFxnDDeRstIhq/FRfFLW5Vr7jPa9/c=
X-Google-Smtp-Source: 
 ABdhPJzu6oYBav/oVxbZg4DkYFlYy8mfxqu7QjB5WE/gplPDgic3NrLr6r8qLWmnqz7/bt/7iNP/OuQ+NB4k0O9fnQ==
X-Received: from jingzhangos.c.googlers.com
 ([fda3:e722:ac3:10:2b:ff92:c0a8:513])
 (user=jingzhangos job=sendgmr) by 2002:a92:b00d:: with SMTP id
 x13mr708430ilh.128.1615336242003; Tue, 09 Mar 2021 16:30:42 -0800 (PST)
Date: Wed, 10 Mar 2021 00:30:20 +0000
Message-Id: <20210310003024.2026253-1-jingzhangos@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.30.1.766.gb4fecdf3b7-goog
Subject: [RFC PATCH 0/4] KVM: stats: Retrieve statistics data in binary format
From: Jing Zhang <jingzhangos@google.com>
To: KVM <kvm@vger.kernel.org>, KVM ARM <kvmarm@lists.cs.columbia.edu>,
        Linux MIPS <linux-mips@vger.kernel.org>,
        KVM PPC <kvm-ppc@vger.kernel.org>,
        Linux S390 <linux-s390@vger.kernel.org>,
        Linux kselftest <linux-kselftest@vger.kernel.org>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Marc Zyngier <maz@kernel.org>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Will Deacon <will@kernel.org>,
        Huacai Chen <chenhuacai@kernel.org>,
        Aleksandar Markovic <aleksandar.qemu.devel@gmail.com>,
        Thomas Bogendoerfer <tsbogend@alpha.franken.de>,
        Paul Mackerras <paulus@ozlabs.org>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Janosch Frank <frankja@linux.ibm.com>,
        David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Claudio Imbrenda <imbrenda@linux.ibm.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Peter Shier <pshier@google.com>,
        Oliver Upton <oupton@google.com>,
        David Rientjes <rientjes@google.com>,
        Emanuele Giuseppe Esposito <eesposit@redhat.com>
Cc: Jing Zhang <jingzhangos@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patchset extends IOCTL interface to retrieve KVM statistics data
in aggregated binary format.
It is meant to provide a lightweight, flexible, scalable and efficient 
lock-free solution for userspace telemetry applications to pull the
statistics data periodically for large scale systems.
The capability is indicated by KVM_CAP_STATS_BINARY_FORM.
Ioctl KVM_STATS_GET_INFO is used to get the information about VM or
vCPU statistics data (The number of supported statistics data which is
used for buffer allocation).
Ioctl KVM_STATS_GET_NAMES is used to get the list of name strings of
all supported statistics data.
Ioctl KVM_STATS_GET_DATA is used to get the aggregated statistics data
per VM or vCPU in the same order as the list of name strings. This is
the ioctl which would be called periodically to retrieve statistics
data per VM or vCPU.

Jing Zhang (4):
  KVM: stats: Separate statistics name strings from debugfs code
  KVM: stats: Define APIs for aggregated stats retrieval in binary
    format
  KVM: stats: Add ioctl commands to pull statistics in binary format
  KVM: selftests: Add selftest for KVM binary form statistics interface

 Documentation/virt/kvm/api.rst                |  79 +++++
 arch/arm64/kvm/guest.c                        |  47 ++-
 arch/mips/kvm/mips.c                          | 114 +++++--
 arch/powerpc/kvm/book3s.c                     | 107 ++++--
 arch/powerpc/kvm/booke.c                      |  84 +++--
 arch/s390/kvm/kvm-s390.c                      | 320 ++++++++++++------
 arch/x86/kvm/x86.c                            | 127 ++++---
 include/linux/kvm_host.h                      |  30 +-
 include/uapi/linux/kvm.h                      |  60 ++++
 tools/testing/selftests/kvm/.gitignore        |   1 +
 tools/testing/selftests/kvm/Makefile          |   3 +
 .../selftests/kvm/kvm_bin_form_stats.c        |  89 +++++
 virt/kvm/kvm_main.c                           | 115 +++++++
 13 files changed, 935 insertions(+), 241 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/kvm_bin_form_stats.c


base-commit: 357ad203d45c0f9d76a8feadbd5a1c5d460c638b
```
#### [PATCH v2 0/7] x86/seves: Support 32-bit boot path and other updates
##### From: Joerg Roedel <joro@8bytes.org>
From: Joerg Roedel <jroedel@suse.de>

```c
From patchwork Wed Mar 10 08:43:18 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Joerg Roedel <joro@8bytes.org>
X-Patchwork-Id: 12127311
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 31454C432C3
	for <kvm@archiver.kernel.org>; Wed, 10 Mar 2021 08:45:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E8A9664FF1
	for <kvm@archiver.kernel.org>; Wed, 10 Mar 2021 08:45:02 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232461AbhCJIof (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 10 Mar 2021 03:44:35 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:40950 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S231492AbhCJIn6 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 10 Mar 2021 03:43:58 -0500
Received: from theia.8bytes.org (8bytes.org
 [IPv6:2a01:238:4383:600:38bc:a715:4b6d:a889])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 3C54FC061760;
        Wed, 10 Mar 2021 00:43:54 -0800 (PST)
Received: from cap.home.8bytes.org (p549adcf6.dip0.t-ipconnect.de
 [84.154.220.246])
        (using TLSv1.3 with cipher TLS_AES_256_GCM_SHA384 (256/256 bits))
        (No client certificate requested)
        by theia.8bytes.org (Postfix) with ESMTPSA id F0A60261;
        Wed, 10 Mar 2021 09:43:50 +0100 (CET)
From: Joerg Roedel <joro@8bytes.org>
To: x86@kernel.org
Cc: Joerg Roedel <joro@8bytes.org>, Joerg Roedel <jroedel@suse.de>,
        hpa@zytor.com, Andy Lutomirski <luto@kernel.org>,
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
        Sean Christopherson <seanjc@google.com>,
        Martin Radev <martin.b.radev@gmail.com>,
        Arvind Sankar <nivedita@alum.mit.edu>,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org
Subject: [PATCH v2 0/7] x86/seves: Support 32-bit boot path and other updates
Date: Wed, 10 Mar 2021 09:43:18 +0100
Message-Id: <20210310084325.12966-1-joro@8bytes.org>
X-Mailer: git-send-email 2.30.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Joerg Roedel <jroedel@suse.de>

Hi,

these patches add support for the 32-bit boot in the decompressor
code. This is needed to boot an SEV-ES guest on some firmware and grub
versions. The patches also add the necessary CPUID sanity checks and a
32-bit version of the C-bit check.

Other updates included here:

        1. Add code to shut down exception handling in the
           decompressor code before jumping to the real kernel.
           Once in the real kernel it is not safe anymore to jump
           back to the decompressor code via exceptions.

        2. Replace open-coded hlt loops with proper calls to
           sev_es_terminate().

Please review.

Thanks,

	Joerg

Changes to v1:

	- Addressed Boris' review comments.
	- Fixed a bug which caused the cbit-check to never be
	  executed even in an SEV guest.

Joerg Roedel (7):
  x86/boot/compressed/64: Cleanup exception handling before booting
    kernel
  x86/boot/compressed/64: Reload CS in startup_32
  x86/boot/compressed/64: Setup IDT in startup_32 boot path
  x86/boot/compressed/64: Add 32-bit boot #VC handler
  x86/boot/compressed/64: Add CPUID sanity check to 32-bit boot-path
  x86/boot/compressed/64: Check SEV encryption in 32-bit boot-path
  x86/sev-es: Replace open-coded hlt-loops with sev_es_terminate()

 arch/x86/boot/compressed/head_64.S     | 170 ++++++++++++++++++++++++-
 arch/x86/boot/compressed/idt_64.c      |  14 ++
 arch/x86/boot/compressed/mem_encrypt.S | 132 ++++++++++++++++++-
 arch/x86/boot/compressed/misc.c        |   7 +-
 arch/x86/boot/compressed/misc.h        |   6 +
 arch/x86/boot/compressed/sev-es.c      |  12 +-
 arch/x86/kernel/sev-es-shared.c        |  10 +-
 7 files changed, 328 insertions(+), 23 deletions(-)
```
#### [PATCH V3 0/6] vDPA/ifcvf: enables Intel C5000X-PL virtio-net
##### From: Zhu Lingshan <lingshan.zhu@intel.com>

```c
From patchwork Wed Mar 10 09:00:46 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhu Lingshan <lingshan.zhu@intel.com>
X-Patchwork-Id: 12127355
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=unavailable autolearn_force=no
 version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 4CC2FC4332B
	for <kvm@archiver.kernel.org>; Wed, 10 Mar 2021 09:06:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id F028664FC4
	for <kvm@archiver.kernel.org>; Wed, 10 Mar 2021 09:06:38 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231572AbhCJJGD (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 10 Mar 2021 04:06:03 -0500
Received: from mga03.intel.com ([134.134.136.65]:64352 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229544AbhCJJGB (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 10 Mar 2021 04:06:01 -0500
IronPort-SDR: 
 4FZetOKMarS+UDH+t9lRD4sFMo4/L+MG1dHGfrO//N36U/cyeExmK7AGLFzB2VeiELLq52ZDh9
 SDPxiwGeTjig==
X-IronPort-AV: E=McAfee;i="6000,8403,9917"; a="188461249"
X-IronPort-AV: E=Sophos;i="5.81,237,1610438400";
   d="scan'208";a="188461249"
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by orsmga103.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 10 Mar 2021 01:06:00 -0800
IronPort-SDR: 
 C2P/5eS9Tn3+Kw5cuTpUQ8fg1w7HszNPfkveY4eJNXMT88dS+k/pQRnSuoUYUZZKQ5BSIMWm+N
 iUQdVbP4tQvg==
X-IronPort-AV: E=Sophos;i="5.81,237,1610438400";
   d="scan'208";a="410110225"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.240.193.73])
  by orsmga008-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 10 Mar 2021 01:05:57 -0800
From: Zhu Lingshan <lingshan.zhu@intel.com>
To: jasowang@redhat.com, mst@redhat.com, lulu@redhat.com,
        leonro@nvidia.com
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Zhu Lingshan <lingshan.zhu@intel.com>
Subject: [PATCH V3 0/6] vDPA/ifcvf: enables Intel C5000X-PL virtio-net
Date: Wed, 10 Mar 2021 17:00:46 +0800
Message-Id: <20210310090052.4762-1-lingshan.zhu@intel.com>
X-Mailer: git-send-email 2.27.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series enabled Intel FGPA SmartNIC C5000X-PL
virtio-net for vDPA.
vDPA requires VIRTIO_F_ACCESS_PLATFORM as a must, this series
verify this feature bit when set features.

Changes from V2:
verify VIRTIO_F_ACCESS_PLATFORM when set features(Jason)

Changes from V1:
remove version number string(Leon)
add new device ids and remove original device ids in
separate patches(Jason)

Zhu Lingshan (6):
  vDPA/ifcvf: get_vendor_id returns a device specific vendor id
  vDPA/ifcvf: enable Intel C5000X-PL virtio-net for vDPA
  vDPA/ifcvf: rename original IFCVF dev ids to N3000 ids
  vDPA/ifcvf: remove the version number string
  vDPA/ifcvf: fetch device feature bits when probe
  vDPA/ifcvf: verify mandatory feature bits for vDPA

 drivers/vdpa/ifcvf/ifcvf_base.c | 20 ++++++++++++++++++--
 drivers/vdpa/ifcvf/ifcvf_base.h | 16 ++++++++++++----
 drivers/vdpa/ifcvf/ifcvf_main.c | 27 ++++++++++++++++++++-------
 3 files changed, 50 insertions(+), 13 deletions(-)
```
#### [RFC PATCH v2 0/3] KVM: arm64: Improve efficiency of stage2 page
##### From: Yanan Wang <wangyanan55@huawei.com>

```c
From patchwork Wed Mar 10 09:43:16 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yanan Wang <wangyanan55@huawei.com>
X-Patchwork-Id: 12127447
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=unavailable autolearn_force=no
 version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B943CC433DB
	for <kvm@archiver.kernel.org>; Wed, 10 Mar 2021 09:44:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 776FB64FBF
	for <kvm@archiver.kernel.org>; Wed, 10 Mar 2021 09:44:40 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231161AbhCJJoJ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 10 Mar 2021 04:44:09 -0500
Received: from szxga06-in.huawei.com ([45.249.212.32]:13902 "EHLO
        szxga06-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S232261AbhCJJnh (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 10 Mar 2021 04:43:37 -0500
Received: from DGGEMS412-HUB.china.huawei.com (unknown [172.30.72.59])
        by szxga06-in.huawei.com (SkyGuard) with ESMTP id 4DwRtg075xzkX1n;
        Wed, 10 Mar 2021 17:42:03 +0800 (CST)
Received: from DESKTOP-TMVL5KK.china.huawei.com (10.174.187.128) by
 DGGEMS412-HUB.china.huawei.com (10.3.19.212) with Microsoft SMTP Server id
 14.3.498.0; Wed, 10 Mar 2021 17:43:21 +0800
From: Yanan Wang <wangyanan55@huawei.com>
To: Marc Zyngier <maz@kernel.org>, Will Deacon <will@kernel.org>,
        "Catalin Marinas" <catalin.marinas@arm.com>,
        James Morse <james.morse@arm.com>,
        "Julien Thierry" <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Gavin Shan <gshan@redhat.com>,
        Quentin Perret <qperret@google.com>,
        <kvmarm@lists.cs.columbia.edu>,
        <linux-arm-kernel@lists.infradead.org>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>
CC: <wanghaibin.wang@huawei.com>, <zhukeqian1@huawei.com>,
        <yuzenghui@huawei.com>, Yanan Wang <wangyanan55@huawei.com>
Subject: [RFC PATCH v2 0/3] KVM: arm64: Improve efficiency of stage2 page
 table
Date: Wed, 10 Mar 2021 17:43:16 +0800
Message-ID: <20210310094319.18760-1-wangyanan55@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.187.128]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,
This v2 series makes some efficiency improvement of stage2 page table code,
and there are some test results to quantify the benefit of each patch.

Changelogs:
v1->v2:
- rebased on top of mainline v5.12-rc2
- also move CMOs of I-cache to the fault handlers
- merge patch 2 and patch 3 together
- retest this v2 series based on v5.12-rc2
- v1: https://lore.kernel.org/lkml/20210208112250.163568-1-wangyanan55@huawei.com/

About patch 1:
We currently uniformly perform CMOs of D-cache and I-cache in user_mem_abort()
before calling the fault handlers. If we get concurrent translation faults on
the same IPA (page or block), CMOs for the first time is necessary while the
others later are not.

By moving CMOs to the fault handlers, we can easily identify conditions where
they are really needed and avoid the unnecessary ones. As it's a time consuming
process to perform CMOs especially when flushing a block range, so this solution
reduces much load of kvm and improve efficiency of the stage2 page table code.

So let's move both clean of D-cache and invalidation of I-cache to the map path
and move only invalidation of I-cache to the permission path. Since the original
APIs for CMOs in mmu.c are only called in function user_mem_abort(), we now also
move them to pgtable.c.

The following results represent the benefit of patch 1 alone, and they were
tested by [1](kvm/selftest) that I have posted recently.
[1] https://lore.kernel.org/lkml/20210302125751.19080-1-wangyanan55@huawei.com/

When there are muitiple vcpus concurrently accessing the same memory region,
we can test the execution time of KVM creating new mappings, updating the
permissions of old mappings from RO to RW, and rebuilding the blocks after
they have been split.

hardware platform: HiSilicon Kunpeng920 Server
host kernel: Linux mainline v5.12-rc2

cmdline: ./kvm_page_table_test -m 4 -s anonymous -b 1G -v 80
           (80 vcpus, 1G memory, page mappings(normal 4K))
KVM_CREATE_MAPPINGS: before 104.63s -> after  97.30s  +7.00%
KVM_UPDATE_MAPPINGS: before  78.47s -> after  77.18s  +1.64%

cmdline: ./kvm_page_table_test -m 4 -s anonymous_thp -b 20G -v 40
	   (40 vcpus, 20G memory, block mappings(THP 2M))
KVM_CREATE_MAPPINGS: before  15.70s -> after   7.36s  +53.12%
KVM_UPDATE_MAPPINGS: before 161.00s -> after 135.03s  +16.13%
KVM_REBUILD_BLOCKS:  before 170.49s -> after 145.46s  +14.68%

cmdline: ./kvm_page_table_test -m 4 -s anonymous_hugetlb_1gb -b 20G -v 40
	   (40 vcpus, 20G memory, block mappings(HUGETLB 1G))
KVM_CREATE_MAPPINGS: before 104.55s -> after   3.69s  +96.47%
KVM_UPDATE_MAPPINGS: before 160.67s -> after 130.65s  +18.68%
KVM_REBUILD_BLOCKS:  before 103.95s -> after   2.96s  +97.15%

About patch 2:
If KVM needs to coalesce the existing normal page mappings into a block mapping,
we currently follow the following steps successively:
1) invalidate the table entry in the PMD/PUD table
2) flush TLB by VMID
3) unmap the old sub-level tables
4) install the new block entry to the PMD/PUD table

It will cost a long time to unmap the numerous old page mappings in step 3,
which means there will be a long period when the PMD/PUD table entry could be
found invalid (step 1, 2, 3). So the other vcpus have a really big chance to
trigger unnecessary translations if they access any page within the block and
find the table entry invalid.

So let's quickly install the block entry at first to ensure uninterrupted memory
access of the other vcpus, and then unmap the page mappings after installation.
This will reduce most of the time when the table entry is invalid, and avoid most
of the unnecessary translation faults.

After this patch the steps can be like:
1) invalidate the table entry in the PMD/PUD table
2) flush TLB by VMID
3) install the new block entry to the PMD/PUD table
4) unmap the old sub-level tables

As this patch only affects the rebuilding of block mappings, so we can test the
execution time of KVM rebuilding the blocks after they have been split.

hardware platform: HiSilicon Kunpeng920 Server
host kernel: Linux mainline v5.12-rc2

cmdline: ./kvm_page_table_test -m 4 -s anonymous_thp -b 20G -v 20
	   (20 vcpus, 20G memory, block mappings(THP 2M))
KVM_REBUILD_BLOCKS: before 73.64s -> after 57.75s  +21.58%

cmdline: ./kvm_page_table_test -m 4 -s anonymous_thp -b 20G -v 40
           (40 vcpus, 20G memory, block mappings(THP 2M))
KVM_REBUILD_BLOCKS: before 145.4s -> after 130.8s  +10.62%

cmdline: ./kvm_page_table_test -m 4 -s anonymous_hugetlb_1gb -b 1G -v 80
           (80 vcpus, 1G memory, block mappings(HUGETLB 1G))
KVM_REBUILD_BLOCKS: before 0.166s -> after 0.035s  +78.92%

cmdline: ./kvm_page_table_test -m 4 -s anonymous_hugetlb_1gb -b 20G -v 20
	   (20 vcpus, 20G memory, block mappings(HUGETLB 1G))
KVM_REBUILD_BLOCKS: before 2.875s -> after 0.282s  +90.20%

cmdline: ./kvm_page_table_test -m 4 -s anonymous_hugetlb_1gb -b 20G -v 40
	   (40 vcpus, 20G memory, block mappings(HUGETLB 1G))
KVM_REBUILD_BLOCKS: before 2.965s -> after 0.359s  +87.55%

About patch 3:
A new method to distinguish cases of memcache allocations is introduced.
By comparing fault_granule and vma_pagesize, cases that require allocations
from memcache and cases that don't can be distinguished completely.
---

Yanan Wang (3):
  KVM: arm64: Move CMOs from user_mem_abort to the fault handlers
  KVM: arm64: Install the block entry before unmapping the page mappings
  KVM: arm64: Distinguish cases of memcache allocations completely

 arch/arm64/include/asm/kvm_mmu.h |  31 ---------
 arch/arm64/kvm/hyp/pgtable.c     | 112 +++++++++++++++++++++++--------
 arch/arm64/kvm/mmu.c             |  48 +++++--------
 3 files changed, 99 insertions(+), 92 deletions(-)
```
#### [PATCH v2 0/2] KVM: arm64: Assorted IPA size fixes
##### From: Marc Zyngier <maz@kernel.org>
X-SA-Exim-Mail-From: maz@kernel.org

```c
From patchwork Wed Mar 10 10:42:06 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 12127701
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.0 required=3.0 tests=BAYES_00,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 9BB2DC433E6
	for <kvm@archiver.kernel.org>; Wed, 10 Mar 2021 10:43:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6380564FE5
	for <kvm@archiver.kernel.org>; Wed, 10 Mar 2021 10:43:26 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232633AbhCJKm4 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 10 Mar 2021 05:42:56 -0500
Received: from mail.kernel.org ([198.145.29.99]:42862 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S232566AbhCJKmY (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 10 Mar 2021 05:42:24 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 3B73564F51;
        Wed, 10 Mar 2021 10:42:24 +0000 (UTC)
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1lJwII-000jdD-1H; Wed, 10 Mar 2021 10:42:22 +0000
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Will Deacon <will@kernel.org>,
        Andrew Jones <drjones@redhat.com>,
        Eric Auger <eric.auger@redhat.com>,
        Alexandru Elisei <alexandru.elisei@arm.com>,
        kernel-team@android.com
Subject: [PATCH v2 0/2] KVM: arm64: Assorted IPA size fixes
Date: Wed, 10 Mar 2021 10:42:06 +0000
Message-Id: <20210310104208.3819061-1-maz@kernel.org>
X-Mailer: git-send-email 2.29.2
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com, will@kernel.org,
 drjones@redhat.com, eric.auger@redhat.com, alexandru.elisei@arm.com,
 kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is a rework of an initial patch posted a couple of days back[1]

While working on enabling KVM on "reduced IPA size" systems, I realise
we have a couple of issues, some of while do impact userspace.

The first issue is that we accept the creation of a "default IPA size"
VM (40 bits) even when the HW doesn't support it. Not good.

The second one is that we disallow a memslot to end right where the
IPA limit is. One page less and you're good, but that's not quite what
it should be.

I intend for both patches to be backported to -stable.

Thanks,

	M.

* From v1:
  - Don't try to cap the default IPA size. If userspace uses 0 with an
    expectation that it will get 40bits, we should abide by it and
    return an error immediately (noticed by Andrew)
  - Added a new patch to fix the exclusive nature of the IPA limit
  
[1] https://lore.kernel.org/r/20210308174643.761100-1-maz@kernel.org

Marc Zyngier (2):
  KVM: arm64: Reject VM creation when the default IPA size is
    unsupported
  KVM: arm64: Fix exclusive limit for IPA size

 Documentation/virt/kvm/api.rst |  3 +++
 arch/arm64/kvm/mmu.c           |  3 +--
 arch/arm64/kvm/reset.c         | 12 ++++++++----
 3 files changed, 12 insertions(+), 6 deletions(-)
```
#### [PATCH v4 0/1] s390/vfio-ap: fix circular lockdep when starting
##### From: Tony Krowiak <akrowiak@linux.ibm.com>

```c
From patchwork Wed Mar 10 15:05:58 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tony Krowiak <akrowiak@linux.ibm.com>
X-Patchwork-Id: 12128187
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A2960C43381
	for <kvm@archiver.kernel.org>; Wed, 10 Mar 2021 15:07:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 878B564FBF
	for <kvm@archiver.kernel.org>; Wed, 10 Mar 2021 15:07:14 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233085AbhCJPGm (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 10 Mar 2021 10:06:42 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:33894 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S230270AbhCJPGK (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 10 Mar 2021 10:06:10 -0500
Received: from pps.filterd (m0098393.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 12AF43Yh050263;
        Wed, 10 Mar 2021 10:06:06 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=53H1LLl3qRqfe3nJ8hxU7IBg/TBXctguygeNieZskCk=;
 b=SNK8U9lDAk6kTkgm1N3MR17znDbI8Qk0e3nxQO+x99vuzwTBCbkKAMvqmABdHzhWBXzu
 uQ2fIs58/4V6aOs3tqGWvjhACLSSuofyQlWYdu7zWb722NJj9C3+5S9N4MZsHP79Rbnp
 Sw846sgjI7+nsQ6jx38+dJafmJISC9GQVIFxwJU62r6vYf5NkjWrNyd/WOz1dlkj0Vcp
 TRqrOuVoQy445yz8WxKv+wXNt1k2RLede/BRNnYOk4gl+3DNTioWaMbM5coSplQCoRyZ
 mbNE3AO4yBuD5Tn+ShOim+r/9NoIcVjJE8VHmBFgSTS5tOLsiSJnUCNv1Ph6PQqqqpFU 3w==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 376hwdy29r-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 10 Mar 2021 10:06:06 -0500
Received: from m0098393.ppops.net (m0098393.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 12AF45hi050487;
        Wed, 10 Mar 2021 10:06:06 -0500
Received: from ppma02dal.us.ibm.com (a.bd.3ea9.ip4.static.sl-reverse.com
 [169.62.189.10])
        by mx0a-001b2d01.pphosted.com with ESMTP id 376hwdy28c-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 10 Mar 2021 10:06:05 -0500
Received: from pps.filterd (ppma02dal.us.ibm.com [127.0.0.1])
        by ppma02dal.us.ibm.com (8.16.0.43/8.16.0.43) with SMTP id
 12AF3bFM016572;
        Wed, 10 Mar 2021 15:06:04 GMT
Received: from b01cxnp22036.gho.pok.ibm.com (b01cxnp22036.gho.pok.ibm.com
 [9.57.198.26])
        by ppma02dal.us.ibm.com with ESMTP id 3768rbjt42-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 10 Mar 2021 15:06:04 +0000
Received: from b01ledav001.gho.pok.ibm.com (b01ledav001.gho.pok.ibm.com
 [9.57.199.106])
        by b01cxnp22036.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id 12AF646s11338076
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 10 Mar 2021 15:06:04 GMT
Received: from b01ledav001.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 135D12805A;
        Wed, 10 Mar 2021 15:06:04 +0000 (GMT)
Received: from b01ledav001.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 8DE2E2805C;
        Wed, 10 Mar 2021 15:06:03 +0000 (GMT)
Received: from cpe-66-24-58-13.stny.res.rr.com.com (unknown [9.85.150.254])
        by b01ledav001.gho.pok.ibm.com (Postfix) with ESMTP;
        Wed, 10 Mar 2021 15:06:03 +0000 (GMT)
From: Tony Krowiak <akrowiak@linux.ibm.com>
To: linux-s390@vger.kernel.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org
Cc: stable@vger.kernel.org, borntraeger@de.ibm.com, cohuck@redhat.com,
        kwankhede@nvidia.com, pbonzini@redhat.com,
        alex.williamson@redhat.com, pasic@linux.vnet.ibm.com
Subject: [PATCH v4 0/1] s390/vfio-ap: fix circular lockdep when starting
Date: Wed, 10 Mar 2021 10:05:58 -0500
Message-Id: <20210310150559.8956-1-akrowiak@linux.ibm.com>
X-Mailer: git-send-email 2.21.3
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.761
 definitions=2021-03-10_09:2021-03-10,2021-03-10 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 lowpriorityscore=0 mlxscore=0
 malwarescore=0 spamscore=0 suspectscore=0 impostorscore=0 phishscore=0
 mlxlogscore=999 clxscore=1015 priorityscore=1501 adultscore=0 bulkscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2103100076
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

*Commit f21916ec4826 ("s390/vfio-ap: clean up vfio_ap resources when KVM
pointer invalidated") introduced a change that results in a circular
lockdep when a Secure Execution guest that is configured with
crypto devices is started. The problem resulted due to the fact that the
patch moved the setting of the guest's AP masks within the protection of
the matrix_dev->lock when the vfio_ap driver is notified that the KVM 
pointer has been set. Since it is not critical that setting/clearing of
the guest's AP masks be done under the matrix_dev->lock when the driver
is notified, the masks will not be updated under the matrix_dev->lock.
The lock is necessary for the setting/unsetting of the KVM pointer,
however, so that will remain in place. 

The dependency chain for the circular lockdep resolved by this patch 
is (in reverse order):

2:	vfio_ap_mdev_group_notifier:	kvm->lock
					matrix_dev->lock

1:	handle_pqap:			matrix_dev->lock
	kvm_vcpu_ioctl:			vcpu->mutex

0:	kvm_s390_cpus_to_pv:		vcpu->mutex
	kvm_vm_ioctl:  			kvm->lock

Please note:
-----------
* If checkpatch is run against this patch series, you may
  get a "WARNING: Unknown commit id 'f21916ec4826', maybe rebased or not 
  pulled?" message. The commit 'f21916ec4826', however, is definitely
  in the master branch on top of which this patch series was built, so
  I'm not sure why this message is being output by checkpatch.
* All acks granted from previous review of this patch have been removed
  due to the fact that this patch introduces non-trivial changes (see
  change log below).

Change log v3=> v4:
------------------
* In vfio_ap_mdev_set_kvm() function, moved the setting of 
  matrix_mdev->kvm_busy just prior to unlocking matrix_dev->lock.

* Reset queues regardless of regardless of the value of matrix_mdev->kvm
  in response to the VFIO_DEVICE_RESET ioctl.

Change log v2=> v3:
------------------ 
* Added two fields - 'bool kvm_busy' and 'wait_queue_head_t wait_for_kvm'
  to struct ap_matrix_mdev. The former indicates that the KVM
  pointer is in the process of being updated and the second allows a
  function that needs access to the KVM pointer to wait until it is
  no longer being updated. Resolves problem of synchronization between
  the functions that change the KVM pointer value and the functions that
  required access to it.

Change log v1=> v2:
------------------
* No longer holding the matrix_dev->lock prior to setting/clearing the
  masks supplying the AP configuration to a KVM guest.
* Make all updates to the data in the matrix mdev that is used to manage
  AP resources used by the KVM guest in the vfio_ap_mdev_set_kvm()
  function instead of the group notifier callback.
* Check for the matrix mdev's KVM pointer in the vfio_ap_mdev_unset_kvm()
  function instead of the vfio_ap_mdev_release() function.

Tony Krowiak (1):
  s390/vfio-ap: fix circular lockdep when setting/clearing crypto masks

 drivers/s390/crypto/vfio_ap_ops.c     | 309 ++++++++++++++++++--------
 drivers/s390/crypto/vfio_ap_private.h |   2 +
 2 files changed, 215 insertions(+), 96 deletions(-)
```
#### [PATCH 0/4] KVM: arm64: Running the EL2 nVHE code with WXN
##### From: Marc Zyngier <maz@kernel.org>
X-SA-Exim-Mail-From: maz@kernel.org

```c
From patchwork Wed Mar 10 15:26:12 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 12128219
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.0 required=3.0 tests=BAYES_00,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 019DBC4332B
	for <kvm@archiver.kernel.org>; Wed, 10 Mar 2021 15:27:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C7C6064F51
	for <kvm@archiver.kernel.org>; Wed, 10 Mar 2021 15:27:19 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232370AbhCJP0s (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 10 Mar 2021 10:26:48 -0500
Received: from mail.kernel.org ([198.145.29.99]:49048 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S231244AbhCJP02 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 10 Mar 2021 10:26:28 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 019CE64F6A;
        Wed, 10 Mar 2021 15:26:28 +0000 (UTC)
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1lK0jB-000n2m-Ot; Wed, 10 Mar 2021 15:26:26 +0000
From: Marc Zyngier <maz@kernel.org>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
        linux-arm-kernel@lists.infradead.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Mark Rutland <mark.rutland@arm.com>,
        Will Deacon <will@kernel.org>, qperret@google.com,
        kernel-team@android.com
Subject: [PATCH 0/4] KVM: arm64: Running the EL2 nVHE code with WXN
Date: Wed, 10 Mar 2021 15:26:12 +0000
Message-Id: <20210310152612.3821182-1-maz@kernel.org>
X-Mailer: git-send-email 2.29.2
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
 linux-arm-kernel@lists.infradead.org, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com, mark.rutland@arm.com,
 will@kernel.org, qperret@google.com, kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Since we use distinct permissions when mapping things at EL2 depending
on whether they are text or data, we are already using a W^X setup
with nVHE.

This trivial series aims to enforce it by setting SCTLR_EL2.WXN at all
times. It just cleans up a couple of code paths so that
SCTLR_ELx_FLAGS is only used by the KVM setup code, and finally sets
the WXN flag permanently.

Lightly tested on an A53 system with 4KB and 64KB pages.

Thanks,

	M.

Marc Zyngier (4):
  arm64: Use INIT_SCTLR_EL1_MMU_OFF to disable the MMU on CPU restart
  KVM: arm64: Use INIT_SCTLR_EL2_MMU_OFF to disable the MMU on KVM
    teardown
  KVM: arm64: Rename SCTLR_ELx_FLAGS to SCTLR_EL2_FLAGS
  KVM: arm64: Force SCTLR_EL2.WXN when running nVHE

 arch/arm64/include/asm/sysreg.h    | 5 +++--
 arch/arm64/kernel/cpu-reset.S      | 5 +----
 arch/arm64/kvm/hyp/nvhe/hyp-init.S | 6 ++----
 3 files changed, 6 insertions(+), 10 deletions(-)
```
#### [PATCH 0/4] KVM: arm64: Running the EL2 nVHE code with WXN
##### From: Marc Zyngier <maz@kernel.org>
X-SA-Exim-Mail-From: maz@kernel.org

```c
From patchwork Wed Mar 10 15:26:52 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 12128221
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.0 required=3.0 tests=BAYES_00,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 0A802C433DB
	for <kvm@archiver.kernel.org>; Wed, 10 Mar 2021 15:27:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C996564F6A
	for <kvm@archiver.kernel.org>; Wed, 10 Mar 2021 15:27:51 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232953AbhCJP1U (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 10 Mar 2021 10:27:20 -0500
Received: from mail.kernel.org ([198.145.29.99]:49156 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S231519AbhCJP1L (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 10 Mar 2021 10:27:11 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id E817464F6A;
        Wed, 10 Mar 2021 15:27:10 +0000 (UTC)
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1lK0js-000n3G-U9; Wed, 10 Mar 2021 15:27:09 +0000
From: Marc Zyngier <maz@kernel.org>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
        linux-arm-kernel@lists.infradead.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Mark Rutland <mark.rutland@arm.com>,
        Will Deacon <will@kernel.org>, qperret@google.com,
        kernel-team@android.com
Subject: [PATCH 0/4] KVM: arm64: Running the EL2 nVHE code with WXN
Date: Wed, 10 Mar 2021 15:26:52 +0000
Message-Id: <20210310152656.3821253-1-maz@kernel.org>
X-Mailer: git-send-email 2.29.2
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
 linux-arm-kernel@lists.infradead.org, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com, mark.rutland@arm.com,
 will@kernel.org, qperret@google.com, kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Since we use distinct permissions when mapping things at EL2 depending
on whether they are text or data, we are already using a W^X setup
with nVHE.

This trivial series aims to enforce it by setting SCTLR_EL2.WXN at all
times. It just cleans up a couple of code paths so that
SCTLR_ELx_FLAGS is only used by the KVM setup code, and finally sets
the WXN flag permanently.

Lightly tested on an A53 system with 4KB and 64KB pages.

Thanks,

	M.

Marc Zyngier (4):
  arm64: Use INIT_SCTLR_EL1_MMU_OFF to disable the MMU on CPU restart
  KVM: arm64: Use INIT_SCTLR_EL2_MMU_OFF to disable the MMU on KVM
    teardown
  KVM: arm64: Rename SCTLR_ELx_FLAGS to SCTLR_EL2_FLAGS
  KVM: arm64: Force SCTLR_EL2.WXN when running nVHE

 arch/arm64/include/asm/sysreg.h    | 5 +++--
 arch/arm64/kernel/cpu-reset.S      | 5 +----
 arch/arm64/kvm/hyp/nvhe/hyp-init.S | 6 ++----
 3 files changed, 6 insertions(+), 10 deletions(-)
```
