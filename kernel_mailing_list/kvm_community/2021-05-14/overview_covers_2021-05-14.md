

#### [PATCH V2 0/2] vDPA/ifcvf: implement doorbell mapping feature
##### From: Zhu Lingshan <lingshan.zhu@intel.com>

```c
From patchwork Fri May 14 09:59:11 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhu Lingshan <lingshan.zhu@intel.com>
X-Patchwork-Id: 12257361
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E26ACC43460
	for <kvm@archiver.kernel.org>; Fri, 14 May 2021 10:04:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C43D96101D
	for <kvm@archiver.kernel.org>; Fri, 14 May 2021 10:04:45 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232942AbhENKFy (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 14 May 2021 06:05:54 -0400
Received: from mga04.intel.com ([192.55.52.120]:4949 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S232625AbhENKFw (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 14 May 2021 06:05:52 -0400
IronPort-SDR: 
 Jf50Z092V4IMmWRIjyqckEZeTOc4OTXp+C43zV10IIKMzIKVGqPWj1lGwoH5tpXhNWPzgv2YLo
 CSd7G5BEOSLw==
X-IronPort-AV: E=McAfee;i="6200,9189,9983"; a="198195246"
X-IronPort-AV: E=Sophos;i="5.82,299,1613462400";
   d="scan'208";a="198195246"
Received: from fmsmga005.fm.intel.com ([10.253.24.32])
  by fmsmga104.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 14 May 2021 03:04:40 -0700
IronPort-SDR: 
 A4IWqA20U77VG6FTbgwb+VNwWKVpKGidEqjxEffwOWIMbbAVnOrwK67sxI9aUFlyF8/LPiW55p
 l8cTanR8KM2w==
X-IronPort-AV: E=Sophos;i="5.82,299,1613462400";
   d="scan'208";a="626910425"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.240.193.73])
  by fmsmga005-auth.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 14 May 2021 03:04:39 -0700
From: Zhu Lingshan <lingshan.zhu@intel.com>
To: jasowang@redhat.com, mst@redhat.com
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        kvm@vger.kernel.org, Zhu Lingshan <lingshan.zhu@intel.com>
Subject: [PATCH V2 0/2] vDPA/ifcvf: implement doorbell mapping feature
Date: Fri, 14 May 2021 17:59:11 +0800
Message-Id: <20210514095913.41777-1-lingshan.zhu@intel.com>
X-Mailer: git-send-email 2.27.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series implements doorbell mapping feature for ifcvf.

Please help review

Thanks!

Chagnes from V1:
calculate the doorbell address per vq than per device(Jason)
let upper layer driver decide how to use the non page_size
aligned doorbell(Jason)

Zhu Lingshan (2):
  vDPA/ifcvf: record virtio notify base
  vDPA/ifcvf: implement doorbell mapping for ifcvf

 drivers/vdpa/ifcvf/ifcvf_base.c |  4 ++++
 drivers/vdpa/ifcvf/ifcvf_base.h |  2 ++
 drivers/vdpa/ifcvf/ifcvf_main.c | 16 ++++++++++++++++
 3 files changed, 22 insertions(+)
```
#### [PATCH v2 0/2] KVM: arm64: Fixup PC updates on exit to userspace
##### From: Marc Zyngier <maz@kernel.org>
X-SA-Exim-Mail-From: maz@kernel.org

```c
From patchwork Fri May 14 10:40:40 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 12257443
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.0 required=3.0 tests=BAYES_00,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 8BA2AC433ED
	for <kvm@archiver.kernel.org>; Fri, 14 May 2021 10:40:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 66C3A6145B
	for <kvm@archiver.kernel.org>; Fri, 14 May 2021 10:40:50 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231916AbhENKmA (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 14 May 2021 06:42:00 -0400
Received: from mail.kernel.org ([198.145.29.99]:46924 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S230444AbhENKl7 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 14 May 2021 06:41:59 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 5030861457;
        Fri, 14 May 2021 10:40:48 +0000 (UTC)
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94.2)
        (envelope-from <maz@kernel.org>)
        id 1lhVFO-001N6Q-7B; Fri, 14 May 2021 11:40:46 +0100
From: Marc Zyngier <maz@kernel.org>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
        linux-arm-kernel@lists.infradead.org
Cc: Zenghui Yu <yuzenghui@huawei.com>, Fuad Tabba <tabba@google.com>,
        James Morse <james.morse@arm.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Alexandru Elisei <alexandru.elisei@arm.com>,
        kernel-team@android.com
Subject: [PATCH v2 0/2] KVM: arm64: Fixup PC updates on exit to userspace
Date: Fri, 14 May 2021 11:40:40 +0100
Message-Id: <20210514104042.1929168-1-maz@kernel.org>
X-Mailer: git-send-email 2.29.2
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
 linux-arm-kernel@lists.infradead.org, yuzenghui@huawei.com, tabba@google.com,
 james.morse@arm.com, suzuki.poulose@arm.com, alexandru.elisei@arm.com,
 kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We recently moved anything related to PC updates into the guest entry
code to help with the protected KVM effort. However, I missed a
critical point: userspace needs to be able to observe state changes
when the vcpu exits. Otherwise, live migration is a bit broken and
vcpu reset can fail (as reported by Zenghui). Not good.

These two patches aim at fixing the above, and carry a Cc stable.

* From v1:
  - Sanitized flag checking
  - Added comment about relying on __kvm_adjust_pc() being preempt-safe
  - Dropped superfluous includes

Marc Zyngier (2):
  KVM: arm64: Move __adjust_pc out of line
  KVM: arm64: Commit pending PC adjustemnts before returning to
    userspace

 arch/arm64/include/asm/kvm_asm.h           |  3 +++
 arch/arm64/kvm/arm.c                       | 10 ++++++++++
 arch/arm64/kvm/hyp/exception.c             | 18 +++++++++++++++++-
 arch/arm64/kvm/hyp/include/hyp/adjust_pc.h | 18 ------------------
 arch/arm64/kvm/hyp/nvhe/hyp-main.c         |  8 ++++++++
 arch/arm64/kvm/hyp/nvhe/switch.c           |  3 +--
 arch/arm64/kvm/hyp/vhe/switch.c            |  3 +--
 7 files changed, 40 insertions(+), 23 deletions(-)
Reviewed-by: Zenghui Yu <yuzenghui@huawei.com>
Tested-by: Zenghui Yu <yuzenghui@huawei.com>
```
#### [PATCH net-next 0/3] net: use XDP helpers
##### From: Matteo Croce <mcroce@linux.microsoft.com>
From: Matteo Croce <mcroce@microsoft.com>

```c
From patchwork Fri May 14 18:39:51 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Matteo Croce <mcroce@linux.microsoft.com>
X-Patchwork-Id: 12258621
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=unavailable autolearn_force=no
 version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 805ACC433ED
	for <kvm@archiver.kernel.org>; Fri, 14 May 2021 18:40:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5D52161457
	for <kvm@archiver.kernel.org>; Fri, 14 May 2021 18:40:23 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231576AbhENSla (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 14 May 2021 14:41:30 -0400
Received: from mail-ej1-f54.google.com ([209.85.218.54]:44642 "EHLO
        mail-ej1-f54.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229906AbhENSl3 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 14 May 2021 14:41:29 -0400
Received: by mail-ej1-f54.google.com with SMTP id lz27so60226ejb.11;
        Fri, 14 May 2021 11:40:17 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=Lxrxc/3Z3jVIsCsgfSFIGV92bNeYHWS7yDIGi9KJTvU=;
        b=P5DTGQqiLEKFQcq8lCsvNn+4u/gQL6UlonT2HW1PJCH9kUnRFYQ5UlqOLG9VPD46kp
         O9sie0Mag4RGJw68HItyRxxrUQTzUOu/+xSiYXE8V0ux7HGqj1lzbgsti45xX3p5lRu5
         pEv5nzHr4lafdwoTq80Nlq3ILTpsSKSU2/huYoQeZEH15UnRh5sUgzZYdogeuC71AgG8
         hHbsDdhUFY/9W2+3y9t6TdVVD1U2k88ug1kNxscTC/RTZOhZKJbWDV+6/hmmTqHUrp/Q
         92w7t2oiuU99l5n5q8XWG/18153/cA4UVqY7XnB95yamA2Bf6TeR73JXpbuD1VtKC8oB
         5slA==
X-Gm-Message-State: AOAM531UxwOBkMn1eOWtHJwdumVE2OIInMC2tBsWqAl4ZMWtiuB2dpuQ
        qOXQIwHwbd/wtFES5wzGZhsgA94+L/tc4nyj
X-Google-Smtp-Source: 
 ABdhPJxBodBBYmBXuen9Ejp5wfOYCaCjxZ1MET6PdnzFoJwHDXVXjsBYdM8lj2LlwI6HA+CHmlPOAQ==
X-Received: by 2002:a17:906:c0c3:: with SMTP id
 bn3mr50194763ejb.498.1621017616765;
        Fri, 14 May 2021 11:40:16 -0700 (PDT)
Received: from turbo.teknoraver.net (net-5-94-253-60.cust.vodafonedsl.it.
 [5.94.253.60])
        by smtp.gmail.com with ESMTPSA id
 dj17sm5081505edb.7.2021.05.14.11.40.15
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 14 May 2021 11:40:16 -0700 (PDT)
From: Matteo Croce <mcroce@linux.microsoft.com>
To: netdev@vger.kernel.org, bpf@vger.kernel.org,
        intel-wired-lan@lists.osuosl.org,
        linux-stm32@st-md-mailman.stormreply.com, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org
Cc: linux-kernel@vger.kernel.org,
        Jesse Brandeburg <jesse.brandeburg@intel.com>,
        Tony Nguyen <anthony.l.nguyen@intel.com>,
        "David S. Miller" <davem@davemloft.net>,
        Jakub Kicinski <kuba@kernel.org>,
        Giuseppe Cavallaro <peppe.cavallaro@st.com>,
        Alexandre Torgue <alexandre.torgue@foss.st.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Jason Wang <jasowang@redhat.com>
Subject: [PATCH net-next 0/3] net: use XDP helpers
Date: Fri, 14 May 2021 20:39:51 +0200
Message-Id: <20210514183954.7129-1-mcroce@linux.microsoft.com>
X-Mailer: git-send-email 2.31.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Matteo Croce <mcroce@microsoft.com>

The commit 43b5169d8355 ("net, xdp: Introduce xdp_init_buff utility
routine") and commit be9df4aff65f ("net, xdp: Introduce xdp_prepare_buff
utility routine") introduces two useful helpers to populate xdp_buff.
Use it in drivers which still open codes that routines.

Matteo Croce (3):
  stmmac: use XDP helpers
  igc: use XDP helpers
  vhost_net: use XDP helpers

 drivers/net/ethernet/intel/igc/igc_main.c         | 9 +++------
 drivers/net/ethernet/stmicro/stmmac/stmmac_main.c | 9 +++------
 drivers/vhost/net.c                               | 6 ++----
 3 files changed, 8 insertions(+), 16 deletions(-)
```
