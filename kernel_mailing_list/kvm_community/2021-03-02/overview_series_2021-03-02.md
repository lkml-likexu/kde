#### [RFC v2 1/2] cgroup: sev: Add misc cgroup controllerFrom: Vipin Sharma <vipinsh@google.com>
##### From: Vipin Sharma <vipinsh@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vipin Sharma <vipinsh@google.com>
X-Patchwork-Id: 12111737
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=unavailable autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 3AEC7C4161F
	for <kvm@archiver.kernel.org>; Tue,  2 Mar 2021 15:57:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0CAAF61494
	for <kvm@archiver.kernel.org>; Tue,  2 Mar 2021 15:57:27 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1838902AbhCBPzN (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 2 Mar 2021 10:55:13 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:42684 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1377297AbhCBISs (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 2 Mar 2021 03:18:48 -0500
Received: from mail-pf1-x44a.google.com (mail-pf1-x44a.google.com
 [IPv6:2607:f8b0:4864:20::44a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id BCA16C0617AB
        for <kvm@vger.kernel.org>; Tue,  2 Mar 2021 00:17:13 -0800 (PST)
Received: by mail-pf1-x44a.google.com with SMTP id o2so12915113pfd.1
        for <kvm@vger.kernel.org>; Tue, 02 Mar 2021 00:17:13 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:in-reply-to:message-id:mime-version:references:subject
         :from:to:cc;
        bh=8B+Ts9aGwPaRrnVyz8Bi7Ywvo81A2m0/i9v/0T28OGw=;
        b=Lqg3uql7awJ2TJuyowfZ58WmWFYsbJVyz4oN5/VaY0vM1aV+MVRVK3ZgS51Pef9Qm5
         HfvGyPoB65k7M8NCoT1S6VIKIh6pkDCS0BkFSGL3kU1n75Zld3UWMesyUv5YFs8rT1io
         xLWpS7y9rnUvzD8bATXKoEFkOXkszavZKSFBR7QHlkN+i/W3u/bdvmv/F4/fvtSBVRku
         drdgPVOykwwri+0FxXZrftOvcPsq3uWdAzBqhVM5jaTeT85Lz/+6Fg6b1nwDGvj/I+UA
         uFIp3ka6QKz7THQl1H1fUTL6pqCd6wwWOZ7naPICQicnzbljld094O6CUMbsChSWLTEm
         fYwg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=8B+Ts9aGwPaRrnVyz8Bi7Ywvo81A2m0/i9v/0T28OGw=;
        b=VeIJLUXC8lQRde9a47LJYQANwe06GCVedHECKwDNjtKdytBsrI8pz+V7wxD0j3S83B
         09uXRTYf12Tmhvs1zECn0whnhxNRkr1ANh654bvcGyBfK+6iS/HkzBqm7ttXqX4d2GgA
         ZH4BM6LsHCfo/bqeeaJZRVkAJ3Ly1ta5bTyvMnoGYOJ4NWZ94gonb0xocaOEFbEU1h2G
         WvaWcSIjKfxeSy4EHbv7GK4UgNc8SUQV9boKCNtcM3jhWtAE/aIIcFDC0/QahINswnCW
         n8yXH9yF9drq74eZRvuJfozPCPPqhojlriHvxnQa6kN+/Frs9UvKwP5JxNebWHmed6Qo
         PaTw==
X-Gm-Message-State: AOAM532tRwYN0OCuPkCIBkjXbuM5nMhe5fLRC42/8Mk/yGBtmqdwAZ8R
        QlHjLygJh/rBZ3jvT7M/NBsBlNyuDZFP
X-Google-Smtp-Source: 
 ABdhPJzJxXAPeySsunPleMriXiknh7tXEaKBCYzXIPMV8jJgvmSTJEEIkDvO2w0QO/dCc0fNLBOBabhEJTUS
Sender: "vipinsh via sendgmr" <vipinsh@vipinsh.kir.corp.google.com>
X-Received: from vipinsh.kir.corp.google.com
 ([2620:0:1008:10:e829:dc2a:968a:1370])
 (user=vipinsh job=sendgmr) by 2002:a65:5c48:: with SMTP id
 v8mr17374764pgr.400.1614673033136; Tue, 02 Mar 2021 00:17:13 -0800 (PST)
Date: Tue,  2 Mar 2021 00:17:04 -0800
In-Reply-To: <20210302081705.1990283-1-vipinsh@google.com>
Message-Id: <20210302081705.1990283-2-vipinsh@google.com>
Mime-Version: 1.0
References: <20210302081705.1990283-1-vipinsh@google.com>
X-Mailer: git-send-email 2.30.1.766.gb4fecdf3b7-goog
Subject: [RFC v2 1/2] cgroup: sev: Add misc cgroup controller
From: Vipin Sharma <vipinsh@google.com>
To: tj@kernel.org, mkoutny@suse.com, rdunlap@infradead.org,
        thomas.lendacky@amd.com, brijesh.singh@amd.com, jon.grimm@amd.com,
        eric.vantassell@amd.com, pbonzini@redhat.com, hannes@cmpxchg.org,
        frankja@linux.ibm.com, borntraeger@de.ibm.com
Cc: corbet@lwn.net, seanjc@google.com, vkuznets@redhat.com,
        wanpengli@tencent.com, jmattson@google.com, joro@8bytes.org,
        tglx@linutronix.de, mingo@redhat.com, bp@alien8.de, hpa@zytor.com,
        gingell@google.com, rientjes@google.com, dionnaglaze@google.com,
        kvm@vger.kernel.org, x86@kernel.org, cgroups@vger.kernel.org,
        linux-doc@vger.kernel.org, linux-kernel@vger.kernel.org,
        Vipin Sharma <vipinsh@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The Miscellaneous cgroup provides the resource limiting and tracking
mechanism for the scalar resources which cannot be abstracted like the
other cgroup resources. Controller is enabled by the CONFIG_CGROUP_MISC
config option.

The first two resources added to the miscellaneous controller are Secure
Encrypted Virtualization (SEV) ASIDs and SEV - Encrypted State (SEV-ES)
ASIDs. These limited ASIDs are used for encrypting virtual machines
memory on the AMD platform

Miscellaneous controller provides 3 interface files:

misc.capacity
  A read-only flat-keyed file shown only in the root cgroup.  It shows
  miscellaneous scalar resources available on the platform along with
  their quantities::

	$ cat misc.capacity
	sev 50
	sev_es 10

misc.current
  A read-only flat-keyed file shown in the non-root cgroups.  It shows
  the current usage of the resources in the cgroup and its children::

	$ cat misc.current
	sev 3
	sev_es 0

misc.max
  A read-write flat-keyed file shown in the non root cgroups. Allowed
  maximum usage of the resources in the cgroup and its children.::

	$ cat misc.max
	sev max
	sev_es 4

  Limit can be set by::

	# echo sev 1 > misc.max

  Limit can be set to max by::

	# echo sev max > misc.max

  Limits can be set more than the capacity value in the misc.capacity
  file.

Signed-off-by: Vipin Sharma <vipinsh@google.com>
Reviewed-by: David Rientjes <rientjes@google.com>
---
 arch/x86/kvm/svm/sev.c        |  65 +++++-
 arch/x86/kvm/svm/svm.h        |   1 +
 include/linux/cgroup_subsys.h |   4 +
 include/linux/misc_cgroup.h   | 122 ++++++++++
 init/Kconfig                  |  14 ++
 kernel/cgroup/Makefile        |   1 +
 kernel/cgroup/misc.c          | 423 ++++++++++++++++++++++++++++++++++
 7 files changed, 620 insertions(+), 10 deletions(-)
 create mode 100644 include/linux/misc_cgroup.h
 create mode 100644 kernel/cgroup/misc.c

```
#### [RFC v11 01/25] scripts/update-linux-headers: Import iommu.h
##### From: Liu Yi L <yi.l.liu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Liu Yi L <yi.l.liu@intel.com>
X-Patchwork-Id: 12111773
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.7 required=3.0 tests=BAYES_00,
	DATE_IN_FUTURE_03_06,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 803B9C28CFB
	for <kvm@archiver.kernel.org>; Tue,  2 Mar 2021 16:07:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 567E564E7C
	for <kvm@archiver.kernel.org>; Tue,  2 Mar 2021 16:07:11 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1575901AbhCBQEk (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 2 Mar 2021 11:04:40 -0500
Received: from mga04.intel.com ([192.55.52.120]:29410 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1444872AbhCBMlX (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 2 Mar 2021 07:41:23 -0500
IronPort-SDR: 
 vTL+v7oI1PwQ9D5wcrZcwpN+oPzLZhercT0gdMhfilDEXOGZZ9nVdtqL6vU8KezhXuxOdyDEKo
 WAIHeVbV6Bvg==
X-IronPort-AV: E=McAfee;i="6000,8403,9910"; a="184363120"
X-IronPort-AV: E=Sophos;i="5.81,216,1610438400";
   d="scan'208";a="184363120"
Received: from fmsmga004.fm.intel.com ([10.253.24.48])
  by fmsmga104.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 02 Mar 2021 04:39:32 -0800
IronPort-SDR: 
 Nb0nayM7mT+7J4D9VH8hW0lS5n3V8W5f+0jxAEqWRE/izBvONNtONP5LsNGN46cc7Tr021AGao
 pdpqHpBxu5cA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.81,216,1610438400";
   d="scan'208";a="427472668"
Received: from yiliu-dev.bj.intel.com (HELO dual-ub.bj.intel.com)
 ([10.238.156.135])
  by fmsmga004.fm.intel.com with ESMTP; 02 Mar 2021 04:39:27 -0800
From: Liu Yi L <yi.l.liu@intel.com>
To: qemu-devel@nongnu.org, alex.williamson@redhat.com,
        peterx@redhat.com, jasowang@redhat.com
Cc: mst@redhat.com, pbonzini@redhat.com, eric.auger@redhat.com,
        david@gibson.dropbear.id.au, jean-philippe@linaro.org,
        kevin.tian@intel.com, yi.l.liu@intel.com, jun.j.tian@intel.com,
        yi.y.sun@intel.com, hao.wu@intel.com, kvm@vger.kernel.org,
        Lingshan.Zhu@intel.com, Jacob Pan <jacob.jun.pan@linux.intel.com>,
        Yi Sun <yi.y.sun@linux.intel.com>,
        Cornelia Huck <cohuck@redhat.com>
Subject: [RFC v11 01/25] scripts/update-linux-headers: Import iommu.h
Date: Wed,  3 Mar 2021 04:38:03 +0800
Message-Id: <20210302203827.437645-2-yi.l.liu@intel.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20210302203827.437645-1-yi.l.liu@intel.com>
References: <20210302203827.437645-1-yi.l.liu@intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Eric Auger <eric.auger@redhat.com>

Update the script to import the new iommu.h uapi header.

Cc: Kevin Tian <kevin.tian@intel.com>
Cc: Jacob Pan <jacob.jun.pan@linux.intel.com>
Cc: Peter Xu <peterx@redhat.com>
Cc: Yi Sun <yi.y.sun@linux.intel.com>
Cc: Michael S. Tsirkin <mst@redhat.com>
Cc: Cornelia Huck <cohuck@redhat.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Acked-by: Cornelia Huck <cohuck@redhat.com>
Signed-off-by: Eric Auger <eric.auger@redhat.com>
Signed-off-by: Liu Yi L <yi.l.liu@intel.com>
---
 scripts/update-linux-headers.sh | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] kvm: arm64: nvhe: Save the SPE context early
##### From: Suzuki K Poulose <suzuki.poulose@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Suzuki K Poulose <Suzuki.Poulose@arm.com>
X-Patchwork-Id: 12111751
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7B723C433DB
	for <kvm@archiver.kernel.org>; Tue,  2 Mar 2021 16:07:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 48AB064E7C
	for <kvm@archiver.kernel.org>; Tue,  2 Mar 2021 16:07:10 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1449062AbhCBQDw (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 2 Mar 2021 11:03:52 -0500
Received: from foss.arm.com ([217.140.110.172]:50316 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1383775AbhCBMHx (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 2 Mar 2021 07:07:53 -0500
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 9BA7911D4;
        Tue,  2 Mar 2021 04:04:03 -0800 (PST)
Received: from ewhatever.cambridge.arm.com (ewhatever.cambridge.arm.com
 [10.1.197.1])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPA id
 12A663F766;
        Tue,  2 Mar 2021 04:04:01 -0800 (PST)
From: Suzuki K Poulose <suzuki.poulose@arm.com>
To: maz@kernel.org
Cc: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org, anshuman.khandual@arm.com,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        stable@vger.kernel.org,
        Christoffer Dall <christoffer.dall@arm.com>,
        Will Deacon <will@kernel.org>,
        Catalin Marinas <catalin.marinas@arm.com>,
        Mark Rutland <mark.rutland@arm.com>,
        Alexandru Elisei <alexandru.elisei@arm.com>
Subject: [PATCH] kvm: arm64: nvhe: Save the SPE context early
Date: Tue,  2 Mar 2021 12:03:45 +0000
Message-Id: <20210302120345.3102874-1-suzuki.poulose@arm.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The nVHE KVM hyp drains and disables the SPE buffer, before
entering the guest, as the EL1&0 translation regime
is going to be loaded with that of the guest.

But this operation is performed way too late, because :
  - The owning translation regime of the SPE buffer
    is transferred to EL2. (MDCR_EL2_E2PB == 0)
  - The guest Stage1 is loaded.

Thus the flush could use the host EL1 virtual address,
but use the EL2 translations instead of host EL1, for writing
out any cached data.

Fix this by moving the SPE buffer handling early enough.
The restore path is doing the right thing.

Fixes: 014c4c77aad7 ("KVM: arm64: Improve debug register save/restore flow")
Cc: stable@vger.kernel.org
Cc: Christoffer Dall <christoffer.dall@arm.com>
Cc: Marc Zyngier <maz@kernel.org>
Cc: Will Deacon <will@kernel.org>
Cc: Catalin Marinas <catalin.marinas@arm.com>
Cc: Mark Rutland <mark.rutland@arm.com>
Cc: Alexandru Elisei <alexandru.elisei@arm.com>
Reviewed-by: Alexandru Elisei <alexandru.elisei@arm.com>
Signed-off-by: Suzuki K Poulose <suzuki.poulose@arm.com>
---
 arch/arm64/include/asm/kvm_hyp.h   |  5 +++++
 arch/arm64/kvm/hyp/nvhe/debug-sr.c | 12 ++++++++++--
 arch/arm64/kvm/hyp/nvhe/switch.c   | 11 ++++++++++-
 3 files changed, 25 insertions(+), 3 deletions(-)

```
#### [PATCH] KVM: LAPIC: Advancing the timer expiration on guest initiated write
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 12111741
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 4E56AC28CC5
	for <kvm@archiver.kernel.org>; Tue,  2 Mar 2021 15:57:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D24DB64F2D
	for <kvm@archiver.kernel.org>; Tue,  2 Mar 2021 15:57:29 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1838995AbhCBPzu (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 2 Mar 2021 10:55:50 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:32798 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1382698AbhCBJoN (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 2 Mar 2021 04:44:13 -0500
Received: from mail-pj1-x1033.google.com (mail-pj1-x1033.google.com
 [IPv6:2607:f8b0:4864:20::1033])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 73871C061756;
        Tue,  2 Mar 2021 01:43:33 -0800 (PST)
Received: by mail-pj1-x1033.google.com with SMTP id c19so1560718pjq.3;
        Tue, 02 Mar 2021 01:43:33 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=XgF5lKevrjewg9cJezIVWPcOGE+q+9kdUhmV1zB7OvE=;
        b=ODAvLqsyem96UdafeY8cYEiFXYZe+2nrl4gLaY/Bokif91LLDQ9iP7B/CBKLC4gcDR
         t02YasT2QQ25sw5Qc09GZjKKbn7uS4gC6w3dTcFmjWQvboy35cI1aq9lW5tmUPAuQHJa
         wmfR4HuNTyOyVxD2PH3UJXUrGlVt6/5+RIVjnYNMUrQQVIGwLmRKhIFyAyXgxG0ctOB4
         qS02fnfvUM9gk0JRCnAubdWi6dcNhWePu8lF3P1WardnaXdJ3zubwvjE/rPjvhu67ZDP
         XNcQPhQpevm+Qu/NCdGQK08djbvXbZJ2uNb3VsoVBsUMfiZdDICEfXMOZt8GOP7Uh3V9
         xOfA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=XgF5lKevrjewg9cJezIVWPcOGE+q+9kdUhmV1zB7OvE=;
        b=E3nl5VA5aVoRKK45IoZZ5ggZ0ihfGnNehcPkkcKNDs+px9WMogFALlkxeFLZc46qHf
         5qHuqkqpOBOT4picCECuiNWhq1qKn8bPomerTDt7UNiXkqkpEylgMJmk8CUeAlRJVDsQ
         4YGRV7eantPVndwhFo2X6TJgstXsHGuNOGJXtM36iAeOF2IDibYEpCnSZ/09k1KW/DdN
         Tz3FkN458aRIML3rkZXyeVPQT0A5L21gW4puQl8Fr2HxXKtRqZDeTpdi/Z7FN3dgRt+X
         AN3WA+MxpCC3pKEBR9zItdE0ANNL0o3kgsbmwrbPucIqNmzu+zjGKqnMixdgJtsBmUNU
         vcpw==
X-Gm-Message-State: AOAM530XkF4SzcWdJBak0pd9gk8t6AGLiOH9Ay0TFfv216hX22TxcDsv
        kXmTWqE1Rvtr8oxYzqdxQk0m8tIFY+g=
X-Google-Smtp-Source: 
 ABdhPJxIQZMzkXa9Zswjn9fQMvmAsALnBtFmaqhowII7TGPTrOOMql3V5dJTk8dRJIm25Vr3LrpO9g==
X-Received: by 2002:a17:90a:5206:: with SMTP id
 v6mr3596791pjh.22.1614678212662;
        Tue, 02 Mar 2021 01:43:32 -0800 (PST)
Received: from localhost.localdomain ([103.7.29.6])
        by smtp.googlemail.com with ESMTPSA id
 mp19sm3211907pjb.2.2021.03.02.01.43.30
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Tue, 02 Mar 2021 01:43:31 -0800 (PST)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>
Subject: [PATCH] KVM: LAPIC: Advancing the timer expiration on guest initiated
 write
Date: Tue,  2 Mar 2021 17:43:22 +0800
Message-Id: <1614678202-10808-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

Advancing the timer expiration should only be necessary on guest initiated 
writes. Now, we cancel the timer, clear .pending and clear expired_tscdeadline 
at the same time during state restore.

Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kvm/lapic.c | 1 +
 1 file changed, 1 insertion(+)

```
#### [RFC PATCH v4 1/9] tools headers: sync headers of asm-generic/hugetlb_encode.h
##### From: Yanan Wang <wangyanan55@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yanan Wang <wangyanan55@huawei.com>
X-Patchwork-Id: 12111865
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7C30BC432C3
	for <kvm@archiver.kernel.org>; Tue,  2 Mar 2021 16:23:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5D27764EE4
	for <kvm@archiver.kernel.org>; Tue,  2 Mar 2021 16:23:50 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1449124AbhCBQPx (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 2 Mar 2021 11:15:53 -0500
Received: from szxga07-in.huawei.com ([45.249.212.35]:13835 "EHLO
        szxga07-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1350923AbhCBM7Y (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 2 Mar 2021 07:59:24 -0500
Received: from DGGEMS412-HUB.china.huawei.com (unknown [172.30.72.60])
        by szxga07-in.huawei.com (SkyGuard) with ESMTP id 4DqcZd3Bsdz7sRQ;
        Tue,  2 Mar 2021 20:56:25 +0800 (CST)
Received: from DESKTOP-TMVL5KK.china.huawei.com (10.174.187.128) by
 DGGEMS412-HUB.china.huawei.com (10.3.19.212) with Microsoft SMTP Server id
 14.3.498.0; Tue, 2 Mar 2021 20:57:54 +0800
From: Yanan Wang <wangyanan55@huawei.com>
To: <kvm@vger.kernel.org>, <linux-kselftest@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>
CC: Paolo Bonzini <pbonzini@redhat.com>,
        Ben Gardon <bgardon@google.com>,
        "Sean Christopherson" <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Andrew Jones <drjones@redhat.com>,
        Peter Xu <peterx@redhat.com>, Marc Zyngier <maz@kernel.org>,
        Ingo Molnar <mingo@kernel.org>,
        Adrian Hunter <adrian.hunter@intel.com>,
        Jiri Olsa <jolsa@redhat.com>,
        "Arnaldo Carvalho de Melo" <acme@redhat.com>,
        Arnd Bergmann <arnd@arndb.de>,
        Michael Kerrisk <mtk.manpages@gmail.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        <wanghaibin.wang@huawei.com>, <yezengruan@huawei.com>,
        <yuzenghui@huawei.com>, Yanan Wang <wangyanan55@huawei.com>
Subject: [RFC PATCH v4 1/9] tools headers: sync headers of
 asm-generic/hugetlb_encode.h
Date: Tue, 2 Mar 2021 20:57:43 +0800
Message-ID: <20210302125751.19080-2-wangyanan55@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
In-Reply-To: <20210302125751.19080-1-wangyanan55@huawei.com>
References: <20210302125751.19080-1-wangyanan55@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.174.187.128]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch syncs contents of tools/include/asm-generic/hugetlb_encode.h
and include/uapi/asm-generic/hugetlb_encode.h. Arch powerpc supports 16KB
hugepages and ARM64 supports 32MB/512MB hugepages. The corresponding mmap
flags have already been added in include/uapi/asm-generic/hugetlb_encode.h,
but not tools/include/asm-generic/hugetlb_encode.h.

Cc: Ingo Molnar <mingo@kernel.org>
Cc: Adrian Hunter <adrian.hunter@intel.com>
Cc: Jiri Olsa <jolsa@redhat.com>
Cc: Arnaldo Carvalho de Melo <acme@redhat.com>
Signed-off-by: Yanan Wang <wangyanan55@huawei.com>
Reviewed-by: Ben Gardon <bgardon@google.com>
---
 tools/include/asm-generic/hugetlb_encode.h | 3 +++
 1 file changed, 3 insertions(+)

```
#### [kvm-unit-tests PATCH v4 1/3] s390x: introduce leave_pstate to leave userspace
##### From: Claudio Imbrenda <imbrenda@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Claudio Imbrenda <imbrenda@linux.ibm.com>
X-Patchwork-Id: 12111749
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 281C0C4360C
	for <kvm@archiver.kernel.org>; Tue,  2 Mar 2021 16:07:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0850664E7C
	for <kvm@archiver.kernel.org>; Tue,  2 Mar 2021 16:07:10 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1449041AbhCBQDm (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 2 Mar 2021 11:03:42 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:44122 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1383647AbhCBL5X (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 2 Mar 2021 06:57:23 -0500
Received: from pps.filterd (m0187473.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 122BXLdI036558
        for <kvm@vger.kernel.org>; Tue, 2 Mar 2021 06:41:15 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=eGLBu8j2kuIQ2X8fG8kpVJ2IHvGVtRqXnrjQara9TlM=;
 b=Gak77mjMFF0xSdt392nYQY+yQrti3UwioTAnuWyqdgGbJ6lDTuDweztVtP3MPthNF9ov
 ieALwo67N0Qe107hXD1SVLP9E4O/DSIo0HZtTp/mjlEJuQbfgQ/D/Z/30nK2PYz/BS83
 9JbbGM23pSJE+SnyuA1l0Hw18bHAD2tphmZMzcWUPJwB5h7uBQ4yFuQfqTpfeur+1gPT
 zROJmto/2VZWc4RDDsfJAhMq9lX0yMuv+HIP9bNmVGpPiElMP5P7gjQO/vAMYnlT/oSM
 Ks6t27J4jpVllmpPJJnL3qzCEPU7s+acy9ZdoY/YSs5+EAPVpSMpB4j4uOfLU/4uu0Ln dA==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 371mjp88fq-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT)
        for <kvm@vger.kernel.org>; Tue, 02 Mar 2021 06:41:14 -0500
Received: from m0187473.ppops.net (m0187473.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 122BXRKI037216
        for <kvm@vger.kernel.org>; Tue, 2 Mar 2021 06:41:14 -0500
Received: from ppma05fra.de.ibm.com (6c.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.108])
        by mx0a-001b2d01.pphosted.com with ESMTP id 371mjp88et-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 02 Mar 2021 06:41:14 -0500
Received: from pps.filterd (ppma05fra.de.ibm.com [127.0.0.1])
        by ppma05fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 122BcBEt010850;
        Tue, 2 Mar 2021 11:41:11 GMT
Received: from b06cxnps3075.portsmouth.uk.ibm.com
 (d06relay10.portsmouth.uk.ibm.com [9.149.109.195])
        by ppma05fra.de.ibm.com with ESMTP id 3712v50du2-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 02 Mar 2021 11:41:11 +0000
Received: from d06av26.portsmouth.uk.ibm.com (d06av26.portsmouth.uk.ibm.com
 [9.149.105.62])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 122Bf8OC49086884
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 2 Mar 2021 11:41:08 GMT
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 8E6ADAE056;
        Tue,  2 Mar 2021 11:41:08 +0000 (GMT)
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 38DA2AE053;
        Tue,  2 Mar 2021 11:41:08 +0000 (GMT)
Received: from ibm-vm.ibmuc.com (unknown [9.145.10.194])
        by d06av26.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue,  2 Mar 2021 11:41:08 +0000 (GMT)
From: Claudio Imbrenda <imbrenda@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: david@redhat.com, thuth@redhat.com, frankja@linux.ibm.com,
        cohuck@redhat.com, pmorel@linux.ibm.com, borntraeger@de.ibm.com
Subject: [kvm-unit-tests PATCH v4 1/3] s390x: introduce leave_pstate to leave
 userspace
Date: Tue,  2 Mar 2021 12:41:05 +0100
Message-Id: <20210302114107.501837-2-imbrenda@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20210302114107.501837-1-imbrenda@linux.ibm.com>
References: <20210302114107.501837-1-imbrenda@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.761
 definitions=2021-03-02_03:2021-03-01,2021-03-02 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 lowpriorityscore=0
 adultscore=0 suspectscore=0 mlxlogscore=999 spamscore=0 malwarescore=0
 phishscore=0 clxscore=1015 priorityscore=1501 bulkscore=0 impostorscore=0
 mlxscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2103020098
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In most testcases, we enter problem state (userspace) just to test if a
privileged instruction causes a fault. In some cases, though, we need
to test if an instruction works properly in userspace. This means that
we do not expect a fault, and we need an orderly way to leave problem
state afterwards.

This patch introduces a simple system based on the SVC instruction.

Signed-off-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
Acked-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
---
 lib/s390x/asm/arch_def.h |  7 +++++++
 lib/s390x/interrupt.c    | 12 ++++++++++--
 2 files changed, 17 insertions(+), 2 deletions(-)

```
#### [PATCH v2 1/1] irqchip/gic-v4.1: Disable vSGI upon (GIC CPUIF < v4.1) detection
##### From: Lorenzo Pieralisi <lorenzo.pieralisi@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Lorenzo Pieralisi <lorenzo.pieralisi@arm.com>
X-Patchwork-Id: 12111743
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 42627C43381
	for <kvm@archiver.kernel.org>; Tue,  2 Mar 2021 16:07:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 16B7564F17
	for <kvm@archiver.kernel.org>; Tue,  2 Mar 2021 16:07:08 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1379927AbhCBP63 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 2 Mar 2021 10:58:29 -0500
Received: from foss.arm.com ([217.140.110.172]:48810 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1380072AbhCBK2p (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 2 Mar 2021 05:28:45 -0500
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 9D5931042;
        Tue,  2 Mar 2021 02:27:50 -0800 (PST)
Received: from e121166-lin.cambridge.arm.com (e121166-lin.cambridge.arm.com
 [10.1.196.255])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 ECB993F73C;
        Tue,  2 Mar 2021 02:27:49 -0800 (PST)
From: Lorenzo Pieralisi <lorenzo.pieralisi@arm.com>
To: linux-kernel@vger.kernel.org
Cc: Marc Zyngier <maz@kernel.org>,
        LAKML <linux-arm-kernel@lists.infradead.org>,
        KVM <kvm@vger.kernel.org>
Subject: [PATCH v2 1/1] irqchip/gic-v4.1: Disable vSGI upon (GIC CPUIF < v4.1)
 detection
Date: Tue,  2 Mar 2021 10:27:44 +0000
Message-Id: <20210302102744.12692-2-lorenzo.pieralisi@arm.com>
X-Mailer: git-send-email 2.29.1
In-Reply-To: <20210302102744.12692-1-lorenzo.pieralisi@arm.com>
References: <0201111162841.3151-1-lorenzo.pieralisi@arm.com>
 <20210302102744.12692-1-lorenzo.pieralisi@arm.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

GIC CPU interfaces versions predating GIC v4.1 were not built to
accommodate vINTID within the vSGI range; as reported in the GIC
specifications (8.2 "Changes to the CPU interface"), it is
CONSTRAINED UNPREDICTABLE to deliver a vSGI to a PE with
ID_AA64PFR0_EL1.GIC < b0011.

Check the GIC CPUIF version by reading the SYS_ID_AA64_PFR0_EL1.

Disable vSGIs if a CPUIF version < 4.1 is detected to prevent using
vSGIs on systems where they may misbehave.

Signed-off-by: Lorenzo Pieralisi <lorenzo.pieralisi@arm.com>
Cc: Marc Zyngier <maz@kernel.org>
---
 arch/arm64/kvm/vgic/vgic-mmio-v3.c     |  4 ++--
 arch/arm64/kvm/vgic/vgic-v3.c          |  3 ++-
 drivers/irqchip/irq-gic-v3-its.c       |  6 +++++-
 drivers/irqchip/irq-gic-v3.c           | 22 ++++++++++++++++++++++
 include/kvm/arm_vgic.h                 |  1 +
 include/linux/irqchip/arm-gic-common.h |  2 ++
 include/linux/irqchip/arm-gic-v3.h     |  1 +
 7 files changed, 35 insertions(+), 4 deletions(-)

```
#### [PATCH V2] vhost-vdpa: honor CAP_IPC_LOCK
##### From: Jason Wang <jasowang@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 12111745
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E9977C43331
	for <kvm@archiver.kernel.org>; Tue,  2 Mar 2021 16:07:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AE77E64F14
	for <kvm@archiver.kernel.org>; Tue,  2 Mar 2021 16:07:08 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1448986AbhCBQCk (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 2 Mar 2021 11:02:40 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:57826 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1446400AbhCBKxf (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 2 Mar 2021 05:53:35 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1614682329;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc; bh=SzDKxvBAv6SXm+NUCcAJGjMwV47OKoU6w1l5j4zzOVo=;
        b=bFplR3L+WReDDuYfzMEkYBTxZ8sYubmlCXKDqQr5AudKtgRwwXZ+fo8j+ykFpWpsnC1xHk
        sFkCT4VquZ/JEidrinOtSNR2H0VFKqgFAGLjnfkpD3ABXUvv5xYyd2a8KrtK+FcvkupAnf
        evpNreVwGVJRotoJsXdc/5XlG+RytC8=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-397-3gRwmn9WOriegQZm-MSt6g-1; Tue, 02 Mar 2021 05:52:08 -0500
X-MC-Unique: 3gRwmn9WOriegQZm-MSt6g-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id E8C4B107ACF3;
        Tue,  2 Mar 2021 10:52:06 +0000 (UTC)
Received: from hp-dl380pg8-01.lab.eng.pek2.redhat.com
 (hp-dl380pg8-01.lab.eng.pek2.redhat.com [10.73.8.10])
        by smtp.corp.redhat.com (Postfix) with ESMTP id C239E6F973;
        Tue,  2 Mar 2021 10:52:00 +0000 (UTC)
From: Jason Wang <jasowang@redhat.com>
To: mst@redhat.com, jasowang@redhat.com, kvm@vger.kernel.org
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH V2] vhost-vdpa: honor CAP_IPC_LOCK
Date: Tue,  2 Mar 2021 05:51:58 -0500
Message-Id: <20210302105158.8240-1-jasowang@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When CAP_IPC_LOCK is set we should not check locked memory against
rlimit as what has been implemented in mlock() and documented in
Documentation/admin-guide/perf-security.rst:

"
RLIMIT_MEMLOCK and perf_event_mlock_kb resource constraints are ignored
for processes with the CAP_IPC_LOCK capability.
"

Fixes: 4c8cf31885f6 ("vhost: introduce vDPA-based backend")
Signed-off-by: Jason Wang <jasowang@redhat.com>
---
 drivers/vhost/vdpa.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [PATCH v4] vfio/pci: Add support for opregion v2.1+
##### From: Fred Gao <fred.gao@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Fred Gao <fred.gao@intel.com>
X-Patchwork-Id: 12111731
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 58CA7C433E0
	for <kvm@archiver.kernel.org>; Tue,  2 Mar 2021 15:57:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1CCCE61494
	for <kvm@archiver.kernel.org>; Tue,  2 Mar 2021 15:57:25 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1837110AbhCBPy1 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 2 Mar 2021 10:54:27 -0500
Received: from mga07.intel.com ([134.134.136.100]:23142 "EHLO mga07.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S240103AbhCBFPH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 2 Mar 2021 00:15:07 -0500
IronPort-SDR: 
 ZKUUQNwKjx9oUwp2EwSRPDij47HqL48mWOdhL06oMDon/ZCC/BbbE4idXFE8icux9VB39c/mHt
 gZZZkq1Siq9w==
X-IronPort-AV: E=McAfee;i="6000,8403,9910"; a="250737408"
X-IronPort-AV: E=Sophos;i="5.81,216,1610438400";
   d="scan'208";a="250737408"
Received: from orsmga001.jf.intel.com ([10.7.209.18])
  by orsmga105.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 01 Mar 2021 21:08:03 -0800
IronPort-SDR: 
 5G8LRrQbF/S0hq5IjEtug5lmbU5pmIfb0V0kI48dIkFRFUh8GaDrB+sByBPHrm4Pbxqh1uDuyn
 l/NHyzCuAq/Q==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.81,216,1610438400";
   d="scan'208";a="444591287"
Received: from cfl-host.sh.intel.com ([10.239.158.118])
  by orsmga001.jf.intel.com with ESMTP; 01 Mar 2021 21:08:01 -0800
From: Fred Gao <fred.gao@intel.com>
To: kvm@vger.kernel.org, intel-gfx@lists.freedesktop.org
Cc: Fred Gao <fred.gao@intel.com>,
        Zhenyu Wang <zhenyuw@linux.intel.com>,
        Swee Yee Fonn <swee.yee.fonn@intel.com>
Subject: [PATCH v4] vfio/pci: Add support for opregion v2.1+
Date: Tue,  2 Mar 2021 21:02:20 +0800
Message-Id: <20210302130220.9349-1-fred.gao@intel.com>
X-Mailer: git-send-email 2.24.1.1.gb6d4d82bd5
In-Reply-To: <20210208170253.29968-1-fred.gao@intel.com>
References: <20210208170253.29968-1-fred.gao@intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Before opregion version 2.0 VBT data is stored in opregion mailbox #4,
However, When VBT data exceeds 6KB size and cannot be within mailbox #4
starting from opregion v2.0+, Extended VBT region, next to opregion, is
used to hold the VBT data, so the total size will be opregion size plus
extended VBT region size.

since opregion v2.0 with physical host VBT address should not be
practically available for end user, it is not supported.

Cc: Zhenyu Wang <zhenyuw@linux.intel.com>
Signed-off-by: Swee Yee Fonn <swee.yee.fonn@intel.com>
Signed-off-by: Fred Gao <fred.gao@intel.com>
---
 drivers/vfio/pci/vfio_pci_igd.c | 49 +++++++++++++++++++++++++++++++++
 1 file changed, 49 insertions(+)

```
#### [Patch v8 01/10] iommu: Report domain nesting info
##### From: Liu Yi L <yi.l.liu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Liu Yi L <yi.l.liu@intel.com>
X-Patchwork-Id: 12111783
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.7 required=3.0 tests=BAYES_00,
	DATE_IN_FUTURE_03_06,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E5CBAC433DB
	for <kvm@archiver.kernel.org>; Tue,  2 Mar 2021 16:08:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B877C64E7C
	for <kvm@archiver.kernel.org>; Tue,  2 Mar 2021 16:08:58 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1839067AbhCBQFV (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 2 Mar 2021 11:05:21 -0500
Received: from mga06.intel.com ([134.134.136.31]:20361 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1447110AbhCBMm1 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 2 Mar 2021 07:42:27 -0500
IronPort-SDR: 
 ktqCn+FioXP8fHZI3WSpjF7VgBzCUucNjykZWS+K9uRm+LdRnYIPnC1fPZjBk0noCKC8ch301s
 tMlYtwEaCe4w==
X-IronPort-AV: E=McAfee;i="6000,8403,9910"; a="248204708"
X-IronPort-AV: E=Sophos;i="5.81,216,1610438400";
   d="scan'208";a="248204708"
Received: from fmsmga004.fm.intel.com ([10.253.24.48])
  by orsmga104.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 02 Mar 2021 04:36:51 -0800
IronPort-SDR: 
 Brd43w0LOZbDrTFJ3gfLSRxZiSLsUs5bSdjubJavIBPvwqtn6bag80PX1fhIwkM2RuBtTCLCww
 +5TJsxfnaKiQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.81,216,1610438400";
   d="scan'208";a="427471988"
Received: from yiliu-dev.bj.intel.com (HELO dual-ub.bj.intel.com)
 ([10.238.156.135])
  by fmsmga004.fm.intel.com with ESMTP; 02 Mar 2021 04:36:47 -0800
From: Liu Yi L <yi.l.liu@intel.com>
To: alex.williamson@redhat.com, eric.auger@redhat.com,
        baolu.lu@linux.intel.com, joro@8bytes.org
Cc: kevin.tian@intel.com, jacob.jun.pan@linux.intel.com,
        ashok.raj@intel.com, yi.l.liu@intel.com, jun.j.tian@intel.com,
        yi.y.sun@intel.com, jean-philippe@linaro.org, peterx@redhat.com,
        jasowang@redhat.com, hao.wu@intel.com, stefanha@gmail.com,
        iommu@lists.linux-foundation.org, kvm@vger.kernel.org,
        jgg@nvidia.com, Lingshan.Zhu@intel.com, vivek.gautam@arm.com
Subject: [Patch v8 01/10] iommu: Report domain nesting info
Date: Wed,  3 Mar 2021 04:35:36 +0800
Message-Id: <20210302203545.436623-2-yi.l.liu@intel.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20210302203545.436623-1-yi.l.liu@intel.com>
References: <20210302203545.436623-1-yi.l.liu@intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

IOMMUs that support nesting translation needs report the capability info
to userspace. It gives information about requirements the userspace needs
to implement plus other features characterizing the physical implementation.

This patch introduces a new IOMMU UAPI struct that gives information about
the nesting capabilities and features. This struct is supposed to be returned
by iommu_domain_get_attr() with DOMAIN_ATTR_NESTING attribute parameter, with
one domain whose type has been set to DOMAIN_ATTR_NESTING.

Cc: Kevin Tian <kevin.tian@intel.com>
CC: Jacob Pan <jacob.jun.pan@linux.intel.com>
Cc: Alex Williamson <alex.williamson@redhat.com>
Cc: Eric Auger <eric.auger@redhat.com>
Cc: Jean-Philippe Brucker <jean-philippe@linaro.org>
Cc: Joerg Roedel <joro@8bytes.org>
Cc: Lu Baolu <baolu.lu@linux.intel.com>
Signed-off-by: Liu Yi L <yi.l.liu@intel.com>
Signed-off-by: Jacob Pan <jacob.jun.pan@linux.intel.com>
---
v7 -> v8:
*) add padding in struct iommu_nesting_info_vtd
*) describe future extension rules for struct iommu_nesting_info in iommu.rst.
*) remove SYSWIDE_PASID

v6 -> v7:
*) rephrase the commit message, replace the @data[] field in struct
   iommu_nesting_info with union per comments from Eric Auger.

v5 -> v6:
*) rephrase the feature notes per comments from Eric Auger.
*) rename @size of struct iommu_nesting_info to @argsz.

v4 -> v5:
*) address comments from Eric Auger.

v3 -> v4:
*) split the SMMU driver changes to be a separate patch
*) move the @addr_width and @pasid_bits from vendor specific
   part to generic part.
*) tweak the description for the @features field of struct
   iommu_nesting_info.
*) add description on the @data[] field of struct iommu_nesting_info

v2 -> v3:
*) remvoe cap/ecap_mask in iommu_nesting_info.
*) reuse DOMAIN_ATTR_NESTING to get nesting info.
*) return an empty iommu_nesting_info for SMMU drivers per Jean'
   suggestion.
---
 Documentation/userspace-api/iommu.rst |  5 +-
 include/uapi/linux/iommu.h            | 72 +++++++++++++++++++++++++++
 2 files changed, 76 insertions(+), 1 deletion(-)

```
#### [PATCH] vhost-vdpa: honor CAP_IPC_LOCK
##### From: Jason Wang <jasowang@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 12111739
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 43B51C41620
	for <kvm@archiver.kernel.org>; Tue,  2 Mar 2021 15:57:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 63DAB64F2C
	for <kvm@archiver.kernel.org>; Tue,  2 Mar 2021 15:57:29 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1838964AbhCBPzj (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 2 Mar 2021 10:55:39 -0500
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:30370 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1837954AbhCBJQE (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 2 Mar 2021 04:16:04 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1614676475;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc; bh=WYVZDzb7gHIYm3imGALkt41Cwtj1qA0Mv6difRe4t9U=;
        b=O93qc2YrGFJeBXwVsU7jAlfvlCgycm65BpXoil3A+CN4Zz/Eq3tdRfcSE/+F+2pT0+0HQC
        wBKboYw/q1YKbKp3ppIXHROhDk+UCiutdRadtfqKV2IFM+YAIc+HHCPiZ8LmWhMULbBcK5
        +8gXPSe4nEBwGorTb6jdW+e9OWB9Kko=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-16-mQrM1frOMlG3b2oYMD35iA-1; Tue, 02 Mar 2021 04:14:31 -0500
X-MC-Unique: mQrM1frOMlG3b2oYMD35iA-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 4EB3D1005501;
        Tue,  2 Mar 2021 09:14:30 +0000 (UTC)
Received: from hp-dl380pg8-01.lab.eng.pek2.redhat.com
 (hp-dl380pg8-01.lab.eng.pek2.redhat.com [10.73.8.10])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 2383D10016FA;
        Tue,  2 Mar 2021 09:14:20 +0000 (UTC)
From: Jason Wang <jasowang@redhat.com>
To: mst@redhat.com, jasowang@redhat.com, kvm@vger.kernel.org
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH] vhost-vdpa: honor CAP_IPC_LOCK
Date: Tue,  2 Mar 2021 04:14:18 -0500
Message-Id: <20210302091418.7226-1-jasowang@redhat.com>
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When CAP_IPC_LOCK is set we should not check locked memory against
rlimit as what has been implemented in mlock().

Signed-off-by: Jason Wang <jasowang@redhat.com>
---
 drivers/vhost/vdpa.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
