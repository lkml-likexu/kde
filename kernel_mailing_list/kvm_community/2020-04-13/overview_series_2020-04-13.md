#### [PATCH v5 1/4] vfio/mdev: add migration_version attribute for mdev (under mdev_type node)
##### From: Yan Zhao <yan.y.zhao@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Yan Zhao <yan.y.zhao@intel.com>
X-Patchwork-Id: 11485051
Return-Path: <SRS0=d7i1=55=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 370E1913
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 13 Apr 2020 06:03:59 +0000 (UTC)
Received: from vger.kernel.org (unknown [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 08E0D20735
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 13 Apr 2020 06:03:59 +0000 (UTC)
DMARC-Filter: OpenDMARC Filter v1.3.2 mail.kernel.org 08E0D20735
Authentication-Results: mail.kernel.org;
 dmarc=fail (p=none dis=none) header.from=intel.com
Authentication-Results: mail.kernel.org;
 spf=none smtp.mailfrom=kvm-owner@vger.kernel.org
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727530AbgDMGD4 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 13 Apr 2020 02:03:56 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.18]:46504 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726967AbgDMGDz (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 13 Apr 2020 02:03:55 -0400
Received: from mga14.intel.com (mga14.intel.com [192.55.52.115])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 10B7EC0A3BE0;
        Sun, 12 Apr 2020 23:03:55 -0700 (PDT)
IronPort-SDR: 
 sTmA9b3T4GGfb3yESswvYBcXzp20GWGINyDSv8Ijcm/ShItLfFt7SEtjcUN3SDEuFc1X8OBMiD
 QAGwc7DSkagw==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by fmsmga103.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 12 Apr 2020 23:03:54 -0700
IronPort-SDR: 
 z+0HOU69jei098SSeSutY5Rei2Llm3kZRcVPTTqJjFp4sXn0qI63LlAxr5XpUfVmCleoF6dxxX
 Quj74UvirE2g==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.72,377,1580803200";
   d="scan'208";a="245065624"
Received: from joy-optiplex-7040.sh.intel.com ([10.239.13.16])
  by fmsmga008.fm.intel.com with ESMTP; 12 Apr 2020 23:03:48 -0700
From: Yan Zhao <yan.y.zhao@intel.com>
To: intel-gvt-dev@lists.freedesktop.org
Cc: libvir-list@redhat.com, kvm@vger.kernel.org,
        linux-doc@vger.kernel.org, linux-kernel@vger.kernel.org,
        aik@ozlabs.ru, Zhengxiao.zx@alibaba-inc.com,
        shuangtai.tst@alibaba-inc.com, qemu-devel@nongnu.org,
        eauger@redhat.com, yi.l.liu@intel.com, xin.zeng@intel.com,
        ziye.yang@intel.com, mlevitsk@redhat.com, pasic@linux.ibm.com,
        felipe@nutanix.com, changpeng.liu@intel.com, Ken.Xue@amd.com,
        jonathan.davies@nutanix.com, shaopeng.he@intel.com,
        alex.williamson@redhat.com, eskultet@redhat.com,
        dgilbert@redhat.com, cohuck@redhat.com, kevin.tian@intel.com,
        zhenyuw@linux.intel.com, zhi.a.wang@intel.com, cjia@nvidia.com,
        kwankhede@nvidia.com, berrange@redhat.com, dinechin@redhat.com,
        corbet@lwn.net, Yan Zhao <yan.y.zhao@intel.com>
Subject: [PATCH v5 1/4] vfio/mdev: add migration_version attribute for mdev
 (under mdev_type node)
Date: Mon, 13 Apr 2020 01:54:03 -0400
Message-Id: <20200413055403.27203-1-yan.y.zhao@intel.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200413055201.27053-1-yan.y.zhao@intel.com>
References: <20200413055201.27053-1-yan.y.zhao@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

migration_version attribute is used to check migration compatibility
between two mdev devices of the same mdev type.
The key is that it's rw and its data is opaque to userspace.

Userspace reads migration_version of mdev device at source side and
writes the value to migration_version attribute of mdev device at target
side. It judges migration compatibility according to whether the read
and write operations succeed or fail.

Currently, it is able to read/write migration_version attribute under two
places:

(1) under mdev_type node
userspace is able to know whether two mdev devices are compatible before
a mdev device is created.

userspace also needs to check whether the two mdev devices are of the same
mdev type before checking the migration_version attribute. It also needs
to check device creation parameters if aggregation is supported in future.

(2) under mdev device node
userspace is able to know whether two mdev devices are compatible after
they are all created. But it does not need to check mdev type and device
creation parameter for aggregation as device vendor driver would have
incorporated those information into the migration_version attribute.

             __    userspace
              /\              \
             /                 \write
            / read              \
   ________/__________       ___\|/_____________
  | migration_version |     | migration_version |-->check migration
  ---------------------     ---------------------   compatibility
    mdev device A               mdev device B

This patch is for mdev documentation about the first place (under
mdev_type node)

Cc: Alex Williamson <alex.williamson@redhat.com>
Cc: Erik Skultety <eskultet@redhat.com>
Cc: "Dr. David Alan Gilbert" <dgilbert@redhat.com>
Cc: Cornelia Huck <cohuck@redhat.com>
Cc: "Tian, Kevin" <kevin.tian@intel.com>
Cc: Zhenyu Wang <zhenyuw@linux.intel.com>
Cc: "Wang, Zhi A" <zhi.a.wang@intel.com>
Cc: Neo Jia <cjia@nvidia.com>
Cc: Kirti Wankhede <kwankhede@nvidia.com>
Cc: Daniel P. Berrangé <berrange@redhat.com>
Cc: Christophe de Dinechin <dinechin@redhat.com>

Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Signed-off-by: Yan Zhao <yan.y.zhao@intel.com>
---
v5:
updated commit message a little to indicate this patch is for
migration_version attribute under mdev_type node

v4:
fixed a typo. (Cornelia Huck)

v3:
1. renamed version to migration_version
(Christophe de Dinechin, Cornelia Huck, Alex Williamson)
2. let errno to be freely defined by vendor driver
(Alex Williamson, Erik Skultety, Cornelia Huck, Dr. David Alan Gilbert)
3. let checking mdev_type be prerequisite of migration compatibility
check. (Alex Williamson)
4. reworded example usage section.
(most of this section came from Alex Williamson)
5. reworded attribute intention section (Cornelia Huck)

v2:
1. added detailed intent and usage
2. made definition of version string completely private to vendor driver
   (Alex Williamson)
3. abandoned changes to sample mdev drivers (Alex Williamson)
4. mandatory --> optional (Cornelia Huck)
5. added description for errno (Cornelia Huck)
---
 .../driver-api/vfio-mediated-device.rst       | 113 ++++++++++++++++++
 1 file changed, 113 insertions(+)

```
#### [PATCH 01/15] mips: define pud_index() regardless of page table folding
##### From: Huacai Chen <chenhc@lemote.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Huacai Chen <chenhc@lemote.com>
X-Patchwork-Id: 11485141
Return-Path: <SRS0=d7i1=55=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BD00317D4
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 13 Apr 2020 07:22:10 +0000 (UTC)
Received: from vger.kernel.org (unknown [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 9434F2076A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 13 Apr 2020 07:22:10 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="eKTR6opB"
DMARC-Filter: OpenDMARC Filter v1.3.2 mail.kernel.org 9434F2076A
Authentication-Results: mail.kernel.org;
 dmarc=none (p=none dis=none) header.from=lemote.com
Authentication-Results: mail.kernel.org;
 spf=none smtp.mailfrom=kvm-owner@vger.kernel.org
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729204AbgDMHWK (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 13 Apr 2020 03:22:10 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.18]:59442 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727654AbgDMHWJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 13 Apr 2020 03:22:09 -0400
Received: from mail-pj1-x1044.google.com (mail-pj1-x1044.google.com
 [IPv6:2607:f8b0:4864:20::1044])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id D45E4C008651;
        Mon, 13 Apr 2020 00:22:08 -0700 (PDT)
Received: by mail-pj1-x1044.google.com with SMTP id b7so3520487pju.0;
        Mon, 13 Apr 2020 00:22:08 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id:in-reply-to:references;
        bh=unWCB+7tFDxvEbrE324xq/PWVQz1J3pJxb0QQI5akQE=;
        b=eKTR6opBGDmh0WFyXbesHgyM2YLRiQFBHC5uiZl88n0oTzSeL/Tw+NnUNWcgwwMV14
         qKkmx5brwvB6qb6lT84AzMa8YjqZO8gDWvwkYx17LXozZOZwUDRvs5yxrWL2p4Ig/s3u
         X50Y/qv8M0lU4uKxUALpT/12ToTX+eSaLTsgLbN1b9tH/QQvi0RDupAzExbDtqEhZX3n
         slW9tOMpwAZENfYGaOaU6jubumcyoWCclOA95qQU9NBXVvCMZ9AOoKgbLhNYfYfW518z
         RfbMLqTBmwnA6IFH4TSOhP9Nyd0OH0d67QITUHNXc2UrZCBwdv+PcS3/U2DsWN3XhRjG
         0/Kw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id
         :in-reply-to:references;
        bh=unWCB+7tFDxvEbrE324xq/PWVQz1J3pJxb0QQI5akQE=;
        b=szivpjFuLABe+2RHDAT5CRln3/tI3IkjOiOimOX6D0UsQ7dBeN0DUFEaqtpxRnT7e9
         FYx6/fv2UyotfcswxfaNWJYkbxz/w93qXRlC95ztrfg7GI+bIUPTL3lotruj3mzIXqiw
         vt8LfjClqJvtHyx2GoJON5lgUgFfuu7TPq7UeMN56dwxvkX9Mph55G+NSmt7z8cLgMgO
         d3qwpZr7TuiqMAO+F/sKOkpoqkf/ZKHAiHACZ5qw9neNVT3liVbc9huJ7rIxYpo2EviS
         s/Rp/CNodiB04vDxbz5IihEg4EjEGvzy001ib1+kVW9XsyZeqU9B70rMxXXVY/o8Isr0
         jyUw==
X-Gm-Message-State: AGi0PuafbeZIWUZsv5zMsN3xfmFhdL39hrLABL79EAHCfBnA9sxN9Gtw
        rFnXiyTLhw0acjhGNGvXGyQ=
X-Google-Smtp-Source: 
 APiQypKG3jjD0bEk/1UaizxYUdFYFTcbzT0+h4p2hEYYr1KO3YnMiBfTuV+NpLNifY8hBLinUgTaew==
X-Received: by 2002:a17:90a:4809:: with SMTP id
 a9mr20297730pjh.73.1586762528070;
        Mon, 13 Apr 2020 00:22:08 -0700 (PDT)
Received: from software.domain.org (28.144.92.34.bc.googleusercontent.com.
 [34.92.144.28])
        by smtp.gmail.com with ESMTPSA id
 u8sm7241341pgl.19.2020.04.13.00.22.05
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Mon, 13 Apr 2020 00:22:07 -0700 (PDT)
From: Huacai Chen <chenhc@lemote.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Thomas Bogendoerfer <tsbogend@alpha.franken.de>
Cc: kvm@vger.kernel.org, qemu-devel@nongnu.org,
        linux-mips@vger.kernel.org, Fuxin Zhang <zhangfx@lemote.com>,
        Huacai Chen <chenhuacai@gmail.com>,
        Jiaxun Yang <jiaxun.yang@flygoat.com>,
        Mike Rapoport <rppt@linux.ibm.com>,
        Huacai Chen <chenhc@lemote.com>
Subject: [PATCH 01/15] mips: define pud_index() regardless of page table
 folding
Date: Mon, 13 Apr 2020 15:30:10 +0800
Message-Id: <1586763024-12197-2-git-send-email-chenhc@lemote.com>
X-Mailer: git-send-email 2.7.0
In-Reply-To: <1586763024-12197-1-git-send-email-chenhc@lemote.com>
References: <1586763024-12197-1-git-send-email-chenhc@lemote.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Mike Rapoport <rppt@linux.ibm.com>

Commit 31168f033e37 ("mips: drop __pXd_offset() macros that duplicate
pXd_index() ones") is correct that pud_index() & __pud_offset() are the
same when pud_index() is actually provided, however it does not take into
account the __PAGETABLE_PUD_FOLDED case. This has broken MIPS KVM
compilation because it relied on availability of pud_index().

Define pud_index() regardless of page table folded. It will evaluate to
actual index for 4-level pagetables and to 0 for folded PUD level.

Link: https://lore.kernel.org/lkml/20200331154749.5457-1-pbonzini@redhat.com
Tested-by: Bibo Mao <maobibo@loongson.cn>
Tested-by: Huacai Chen <chenhc@lemote.com>
Reported-by: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Mike Rapoport <rppt@linux.ibm.com>
[Huacai: Add Tested-by and take this patch into my series, because my
         series can't build an available kernel if without this patch.]
Signed-off-by: Huacai Chen <chenhc@lemote.com>
---
 arch/mips/include/asm/pgtable-64.h | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH] KVM: Optimize kvm_arch_vcpu_ioctl_run function
##### From: Tianjia Zhang <tianjia.zhang@linux.alibaba.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tianjia Zhang <tianjia.zhang@linux.alibaba.com>
X-Patchwork-Id: 11484971
Return-Path: <SRS0=d7i1=55=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4EEE01392
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 13 Apr 2020 03:45:33 +0000 (UTC)
Received: from vger.kernel.org (unknown [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 2ACE520678
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 13 Apr 2020 03:45:33 +0000 (UTC)
DMARC-Filter: OpenDMARC Filter v1.3.2 mail.kernel.org 2ACE520678
Authentication-Results: mail.kernel.org;
 dmarc=fail (p=none dis=none) header.from=linux.alibaba.com
Authentication-Results: mail.kernel.org;
 spf=none smtp.mailfrom=kvm-owner@vger.kernel.org
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728605AbgDMDp2 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 12 Apr 2020 23:45:28 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.18]:52962 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727513AbgDMDp2 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 12 Apr 2020 23:45:28 -0400
Received: from out30-130.freemail.mail.aliyun.com
 (out30-130.freemail.mail.aliyun.com [115.124.30.130])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 48FCEC0A3BE0;
        Sun, 12 Apr 2020 20:45:28 -0700 (PDT)
X-Alimail-AntiSpam: 
 AC=PASS;BC=-1|-1;BR=01201311R771e4;CH=green;DM=||false|;DS=||;FP=0|-1|-1|-1|0|-1|-1|-1;HT=e01f04397;MF=tianjia.zhang@linux.alibaba.com;NM=1;PH=DS;RN=20;SR=0;TI=SMTPD_---0TvK0H1G_1586749524;
Received: from localhost(mailfrom:tianjia.zhang@linux.alibaba.com
 fp:SMTPD_---0TvK0H1G_1586749524)
          by smtp.aliyun-inc.com(127.0.0.1);
          Mon, 13 Apr 2020 11:45:24 +0800
From: Tianjia Zhang <tianjia.zhang@linux.alibaba.com>
To: pbonzini@redhat.com, sean.j.christopherson@intel.com,
        vkuznets@redhat.com, wanpengli@tencent.com, jmattson@google.com,
        joro@8bytes.org, tglx@linutronix.de, mingo@redhat.com,
        bp@alien8.de, x86@kernel.org, hpa@zytor.com, maz@kernel.org,
        james.morse@arm.com, julien.thierry.kdev@gmail.com,
        suzuki.poulose@arm.com
Cc: kvm@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
        kvmarm@lists.cs.columbia.edu, linux-kernel@vger.kernel.org,
        tianjia.zhang@linux.alibaba.com
Subject: [PATCH] KVM: Optimize kvm_arch_vcpu_ioctl_run function
Date: Mon, 13 Apr 2020 11:45:23 +0800
Message-Id: <20200413034523.110548-1-tianjia.zhang@linux.alibaba.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

kvm_arch_vcpu_ioctl_run() is only called in the file kvm_main.c,
where vcpu->run is the kvm_run parameter, so it has been replaced.

Signed-off-by: Tianjia Zhang <tianjia.zhang@linux.alibaba.com>
---
 arch/x86/kvm/x86.c | 8 ++++----
 virt/kvm/arm/arm.c | 2 +-
 2 files changed, 5 insertions(+), 5 deletions(-)

```
#### [PATCH] KVM: SVM: fix compilation with modular PSP and non-modular KVM
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11485241
Return-Path: <SRS0=d7i1=55=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8649F6CA
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 13 Apr 2020 07:50:51 +0000 (UTC)
Received: from vger.kernel.org (unknown [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5DA0F206A1
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 13 Apr 2020 07:50:51 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="EPInsd93"
DMARC-Filter: OpenDMARC Filter v1.3.2 mail.kernel.org 5DA0F206A1
Authentication-Results: mail.kernel.org;
 dmarc=fail (p=none dis=none) header.from=redhat.com
Authentication-Results: mail.kernel.org;
 spf=none smtp.mailfrom=kvm-owner@vger.kernel.org
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729443AbgDMHui (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 13 Apr 2020 03:50:38 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.18]:36550 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729434AbgDMHui (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 13 Apr 2020 03:50:38 -0400
Received: from us-smtp-1.mimecast.com (us-smtp-delivery-1.mimecast.com
 [207.211.31.120])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 3614CC008679
        for <kvm@vger.kernel.org>; Mon, 13 Apr 2020 00:50:38 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1586764237;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc; bh=lYN6NWfIRfj/yIGOoBz/hWKpypYJrD0ZyvpeCaMLxg8=;
        b=EPInsd93r07Q1gX1zp2nPtiLbsn4epyz4d0U4z1PiJusXgoj3ombJgnPTmHghErplG18Qe
        oH5obEutHUZEhYr4DfAoE5xNrM+GlrRtTfxBIPL1bz3gt9J/CmbpuC8+X/cXKSVCbhcxmN
        AO0ahfdzQ01qxVbseLJA/66G/4NaudI=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-343-RHGsbDOdMDWecL_D8MqgFA-1; Mon, 13 Apr 2020 03:50:34 -0400
X-MC-Unique: RHGsbDOdMDWecL_D8MqgFA-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 75B491005513;
        Mon, 13 Apr 2020 07:50:33 +0000 (UTC)
Received: from virtlab511.virt.lab.eng.bos.redhat.com
 (virtlab511.virt.lab.eng.bos.redhat.com [10.19.152.198])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 0364B5C64E;
        Mon, 13 Apr 2020 07:50:32 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: ubizjak@gmail.com
Subject: [PATCH] KVM: SVM: fix compilation with modular PSP and non-modular
 KVM
Date: Mon, 13 Apr 2020 03:50:31 -0400
Message-Id: <20200413075032.5546-1-pbonzini@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Use svm_sev_enabled() in order to cull all calls to PSP code.  Otherwise,
compilation fails with undefined symbols if the PSP device driver is compiled
as a module and KVM is not.

Reported-by: Uros Bizjak <ubizjak@gmail.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/svm/sev.c | 5 ++++-
 1 file changed, 4 insertions(+), 1 deletion(-)

```
#### [PATCH] KVM: SVM: move more vmentry code to assembly
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11485243
Return-Path: <SRS0=d7i1=55=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B5D6217D4
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 13 Apr 2020 07:50:51 +0000 (UTC)
Received: from vger.kernel.org (unknown [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 8DA2E206A1
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 13 Apr 2020 07:50:51 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="YehfLY2F"
DMARC-Filter: OpenDMARC Filter v1.3.2 mail.kernel.org 8DA2E206A1
Authentication-Results: mail.kernel.org;
 dmarc=fail (p=none dis=none) header.from=redhat.com
Authentication-Results: mail.kernel.org;
 spf=none smtp.mailfrom=kvm-owner@vger.kernel.org
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729451AbgDMHuj (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 13 Apr 2020 03:50:39 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.18]:36552 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729435AbgDMHui (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 13 Apr 2020 03:50:38 -0400
Received: from us-smtp-delivery-1.mimecast.com (us-smtp-1.mimecast.com
 [207.211.31.81])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 3DA8BC008609
        for <kvm@vger.kernel.org>; Mon, 13 Apr 2020 00:50:38 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1586764237;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc; bh=zFvG+YcwjZoETKu4AwjE24+iK2LSK2xSQXF5Cz5Lw7U=;
        b=YehfLY2FaTXvsCK16gkvM5IcBjOG8nDJ7R1Vh38Fadyn0l701VLW146U6dXkFFtZsCxRW/
        NxtNEvAqcq8g/8nDgqScZFA0TNIN3hbqH/reidVJ7UHcWIkquE2LW4xxyMC6pegQgJYec6
        wYomoK3wzE060K7bXyP8+cObTRawVfE=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-489-yGxMz_h3PrSrnuhHErAqTQ-1; Mon, 13 Apr 2020 03:50:35 -0400
X-MC-Unique: yGxMz_h3PrSrnuhHErAqTQ-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 15806800D53;
        Mon, 13 Apr 2020 07:50:34 +0000 (UTC)
Received: from virtlab511.virt.lab.eng.bos.redhat.com
 (virtlab511.virt.lab.eng.bos.redhat.com [10.19.152.198])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 9927F5C296;
        Mon, 13 Apr 2020 07:50:33 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: ubizjak@gmail.com
Subject: [PATCH] KVM: SVM: move more vmentry code to assembly
Date: Mon, 13 Apr 2020 03:50:32 -0400
Message-Id: <20200413075032.5546-2-pbonzini@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Manipulate IF around vmload/vmsave to remove the confusing usage of
local_irq_enable where interrupts are actually disabled via GIF.
And stuff the RSB immediately without waiting for a RET to avoid
Spectre-v2 attacks.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/include/asm/nospec-branch.h | 21 ---------------------
 arch/x86/kvm/svm/svm.c               |  7 -------
 arch/x86/kvm/svm/vmenter.S           |  9 +++++++++
 3 files changed, 9 insertions(+), 28 deletions(-)

```
