#### [kvm-unit-tests PATCH 1/2] arm/arm64: gic: Add IPI latency test
##### From: Jingyi Wang <wangjingyi11@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jingyi Wang <wangjingyi11@huawei.com>
X-Patchwork-Id: 11468857
Return-Path: <SRS0=PGN4=5R=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 799D9912
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  1 Apr 2020 10:08:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5896620BED
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  1 Apr 2020 10:08:51 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732107AbgDAKIu (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 1 Apr 2020 06:08:50 -0400
Received: from szxga06-in.huawei.com ([45.249.212.32]:36296 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1731951AbgDAKIu (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 1 Apr 2020 06:08:50 -0400
Received: from DGGEMS408-HUB.china.huawei.com (unknown [172.30.72.58])
        by Forcepoint Email with ESMTP id 89E3E897F185FC9B8DBD;
        Wed,  1 Apr 2020 18:08:35 +0800 (CST)
Received: from DESKTOP-FPN2511.china.huawei.com (10.173.222.58) by
 DGGEMS408-HUB.china.huawei.com (10.3.19.208) with Microsoft SMTP Server id
 14.3.487.0; Wed, 1 Apr 2020 18:08:28 +0800
From: Jingyi Wang <wangjingyi11@huawei.com>
To: <drjones@redhat.com>, <kvm@vger.kernel.org>,
        <kvmarm@lists.cs.columbia.edu>
CC: <wanghaibin.wang@huawei.com>, <yuzenghui@huawei.com>,
        Jingyi Wang <wangjingyi11@huawei.com>
Subject: [kvm-unit-tests PATCH 1/2] arm/arm64: gic: Add IPI latency test
Date: Wed, 1 Apr 2020 18:08:11 +0800
Message-ID: <20200401100812.27616-2-wangjingyi11@huawei.com>
X-Mailer: git-send-email 2.14.1.windows.1
In-Reply-To: <20200401100812.27616-1-wangjingyi11@huawei.com>
References: <20200401100812.27616-1-wangjingyi11@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.173.222.58]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch add a test to measure the latency of IPI injection.

Signed-off-by: Jingyi Wang <wangjingyi11@huawei.com>
---
 arm/gic.c | 27 +++++++++++++++++++++++++++
 1 file changed, 27 insertions(+)

```
#### [PATCH 1/2] KVM: arm64: PSCI: Narrow input registers when using 32bit functions
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11469345
Return-Path: <SRS0=PGN4=5R=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F09A017EF
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  1 Apr 2020 16:58:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id CC5582078C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  1 Apr 2020 16:58:32 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1585760312;
	bh=FuGfYh1+EXJyAtf5C2GDqinq2NnOg9RLDsgqd9Et3Fc=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=M0SPLSPrvKUvhgm05j4Vw9IMCsdAJgrhzKlw47r7P+vnpUc63guvDpaaD51mQXF9C
	 XW5t3kWRzPA0+8NyPPCwK5V0vee5RlmnoOUh7YKIW9QEiye00AnAH2XDL1zEcmW59y
	 GKUE9xQNfpv6uzhaKnxtSefghWXOqRn5NsJThg5g=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1733112AbgDAQ6c (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 1 Apr 2020 12:58:32 -0400
Received: from mail.kernel.org ([198.145.29.99]:57620 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1732747AbgDAQ6b (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 1 Apr 2020 12:58:31 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 27DFE20714;
        Wed,  1 Apr 2020 16:58:31 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1585760311;
        bh=FuGfYh1+EXJyAtf5C2GDqinq2NnOg9RLDsgqd9Et3Fc=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=i28ZEb0cbGWPWRXxU2+ocBpFuSiIGV3bRbJUY/uTnhC2OaYZvpgPpBAAmKBvgHsg8
         IhxMs03xJXiVPZ4SVzWURn8PR6Mttt+C1AXPzpBP5JWJDt3dc6REQuFkWCOQNs1/yz
         T159f8D3kIbJ+77A/BnSFuoATrUrPIq7qb2SIxKs=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1jJghB-00Haev-Bt; Wed, 01 Apr 2020 17:58:29 +0100
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: Christoffer Dall <Christoffer.Dall@arm.com>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Christoffer Dall <christoffer.dall@arm.com>
Subject: [PATCH 1/2] KVM: arm64: PSCI: Narrow input registers when using 32bit
 functions
Date: Wed,  1 Apr 2020 17:58:15 +0100
Message-Id: <20200401165816.530281-2-maz@kernel.org>
X-Mailer: git-send-email 2.25.0
In-Reply-To: <20200401165816.530281-1-maz@kernel.org>
References: <20200401165816.530281-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, Christoffer.Dall@arm.com,
 james.morse@arm.com, julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 christoffer.dall@arm.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When a guest delibarately uses an SSMC32 function number (which is allowed),
we should make sure we drop the top 32bits from the input arguments, as they
could legitimately be junk.

Reported-by: Christoffer Dall <christoffer.dall@arm.com>
Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 virt/kvm/arm/psci.c | 16 ++++++++++++++++
 1 file changed, 16 insertions(+)

```
#### [PATCH] KVM: Fix spelling in code commentsFrom: Fuad Tabba <tabba@google.com>
##### From: Fuad Tabba <tabba@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Fuad Tabba <tabba@google.com>
X-Patchwork-Id: 11469119
Return-Path: <SRS0=PGN4=5R=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CDFBC92A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  1 Apr 2020 14:03:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 99A762078E
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  1 Apr 2020 14:03:17 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="vZtoXntu"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732901AbgDAODQ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 1 Apr 2020 10:03:16 -0400
Received: from mail-wr1-f74.google.com ([209.85.221.74]:56589 "EHLO
        mail-wr1-f74.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1732843AbgDAODQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 1 Apr 2020 10:03:16 -0400
Received: by mail-wr1-f74.google.com with SMTP id w12so14581080wrl.23
        for <kvm@vger.kernel.org>; Wed, 01 Apr 2020 07:03:14 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=RNlyOyyI+iDwlolb7pJpaxUUdy3zyUpQyBfu38tGvPM=;
        b=vZtoXntumcdQh2rFxP4pdzt/3hOC88omg5zB+2DbEAjSZ3pVshACbEjhd6ZlRBnOQG
         KyCS/19w+XwA6o3rL+zd1ZVtQJp7lBwT2xLbG6Md96O9UU5fS7SuA7ki463KdLj5tTj5
         rqWfEWEXW+uf42ffGEKQ3Yto+VkIgAlfzWCOkTddQ9Gqv0KCyM/0r8VBRxS0UaEXbF3E
         U0oCCfWLQGdh2BoiM5F73MQ/iduE8dF9Cr2D5BsUUlcej2D35B08pTYAhu1Ct1ga4tSI
         t1F0pHsbRXwcmcyzukSnEZGrtSY+/HXa0Clrvdpoy+MUMOeNqHPHrzATOWvkcC188Lcw
         /O6Q==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=RNlyOyyI+iDwlolb7pJpaxUUdy3zyUpQyBfu38tGvPM=;
        b=khe4LfRmz48+GOUkJQ/2X7x70exiPdP2umdstk+thEdgmZXUE0oXEpVySObhoKfk7y
         mzv8N8VIXd1rBFg6ljqPZgdoqhUg338AdjvYFBKDbjl0uOf0Ad32x7kbbEo2O2Sx1a+I
         gF/qFUVSA37JuwI2sJy/K6rjVGXu3v4/AQDoRmArp6QATJ4aPIYRkJNCuiofh0dr4Y46
         UG9943aZ00yaGENg47yXIbM8m/Wa45eQTZFfAdssp+pCMi+1mOW2J/q0LU9/1JNPs6s2
         YXXGRMgKPwk08e0fAdmbH7B4L14oB55bedQtJD01NFrJen3gH4NK5VyHWPE0nnNGGPL7
         18aA==
X-Gm-Message-State: ANhLgQ0Z5w8DmJ4FE4zqt9FJyJYGlGRWY4ZX3yiXfQ1ZetSxtqp6RGmO
        PZQVptGhQjz27YD4OOSEvA2PbGLpIg==
X-Google-Smtp-Source: 
 ADFU+vutiq7Y+aqFIGo4/ZvNBTjU0X6gU1aG6CNXLmHGSj0SkssqD/jojO8Ka3Q/mjh+BeUzhZ8yJCa4iw==
X-Received: by 2002:a5d:6742:: with SMTP id l2mr27528686wrw.124.1585749793647;
 Wed, 01 Apr 2020 07:03:13 -0700 (PDT)
Date: Wed,  1 Apr 2020 15:03:10 +0100
Message-Id: <20200401140310.29701-1-tabba@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.26.0.rc2.310.g2932bb562d-goog
Subject: [PATCH] KVM: Fix spelling in code comments
From: Fuad Tabba <tabba@google.com>
To: maz@kernel.org
Cc: catalin.marinas@arm.com, will@kernel.org, kvm@vger.kernel.org,
        kvmarm@lists.cs.columbia.edu, trivial@kernel.org, jeffv@google.com,
        tabba@google.com
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Fix spelling and typos (e.g., repeated words) in comments.

Signed-off-by: Fuad Tabba <tabba@google.com>
---
 arch/arm64/kvm/guest.c        | 4 ++--
 arch/arm64/kvm/reset.c        | 6 +++---
 arch/arm64/kvm/sys_regs.c     | 6 +++---
 virt/kvm/arm/arm.c            | 6 +++---
 virt/kvm/arm/hyp/vgic-v3-sr.c | 2 +-
 virt/kvm/arm/mmio.c           | 2 +-
 virt/kvm/arm/mmu.c            | 6 +++---
 virt/kvm/arm/psci.c           | 6 +++---
 virt/kvm/arm/vgic/vgic-v3.c   | 2 +-
 virt/kvm/coalesced_mmio.c     | 2 +-
 virt/kvm/eventfd.c            | 2 +-
 virt/kvm/kvm_main.c           | 2 +-
 12 files changed, 23 insertions(+), 23 deletions(-)

```
#### [kvm-unit-tests PATCH v1] s390x: STFLE operates on doublewords
##### From: David Hildenbrand <david@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Hildenbrand <david@redhat.com>
X-Patchwork-Id: 11469293
Return-Path: <SRS0=PGN4=5R=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 01C221392
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  1 Apr 2020 16:33:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D09CA215A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  1 Apr 2020 16:33:20 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="YESoXzyM"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2387822AbgDAQdT (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 1 Apr 2020 12:33:19 -0400
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:32293 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S2388522AbgDAQdQ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 1 Apr 2020 12:33:16 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1585758794;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=/uHYR3Hg3qBZEmTsxulFkg4E+9gG5trSXBJP5OBFkXs=;
        b=YESoXzyMYgJdOZDNqVsEF8DN2Qqr9YOOdqqqI+c/sdAuk3VxQE7mloSYn2uMGcCVxx8SSK
        n8R5UmcmWIW6krIlrANU7UFMMmqUOCiT6/OP188C1o6SUbx4+4WDVdK3OdcC+LrDofzOeM
        f+/wJB+c5MeeS66Bdes8n/0cWDXdvl4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-465-g5E3kL6HOg2sxZlQy6C5Mw-1; Wed, 01 Apr 2020 12:33:11 -0400
X-MC-Unique: g5E3kL6HOg2sxZlQy6C5Mw-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 02A3019067E0;
        Wed,  1 Apr 2020 16:33:10 +0000 (UTC)
Received: from t480s.redhat.com (ovpn-114-59.ams2.redhat.com [10.36.114.59])
        by smtp.corp.redhat.com (Postfix) with ESMTP id E229B166B7;
        Wed,  1 Apr 2020 16:33:05 +0000 (UTC)
From: David Hildenbrand <david@redhat.com>
To: kvm@vger.kernel.org
Cc: Thomas Huth <thuth@redhat.com>,
        Janosch Frank <frankja@linux.ibm.com>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Cornelia Huck <cohuck@redhat.com>,
        David Hildenbrand <david@redhat.com>
Subject: [kvm-unit-tests PATCH v1] s390x: STFLE operates on doublewords
Date: Wed,  1 Apr 2020 18:33:05 +0200
Message-Id: <20200401163305.31550-1-david@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

STFLE operates on doublewords, not bytes. Passing in "256" resulted in
some ignored bits getting set. Not bad, but also not clean.

Let's just convert our stfle handling code to operate on doublewords.

Signed-off-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 lib/s390x/asm/facility.h | 14 +++++++-------
 lib/s390x/io.c           |  2 +-
 2 files changed, 8 insertions(+), 8 deletions(-)

```
#### [PATCH] KVM: VMX: fix crash cleanup when KVM wasn't used
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11468753
Return-Path: <SRS0=PGN4=5R=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6B00692A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  1 Apr 2020 08:13:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4931A20787
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  1 Apr 2020 08:13:57 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="JIfjUAga"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732083AbgDAINz (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 1 Apr 2020 04:13:55 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:48864 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1731982AbgDAINz (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 1 Apr 2020 04:13:55 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1585728834;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=cU+okLsMKSqHOKUW7pNlWD/YMAsYMmyQn6ZUscB8aaA=;
        b=JIfjUAgavdfZxV8lDnIxQGpcL30vF1IJ9UKRcvaoOKiemSt/2c/i8oyO3uknY9G9oagel5
        Kg9CMq5QYzHpP10hUHGuYfHA6x4chazxKSaY59OPZRse7EsNDQpCK1MHKI/wF35Y+vzEYD
        sq+r5Nh6E1SsV0+jMBXDV5FG1zT2WME=
Received: from mail-wr1-f70.google.com (mail-wr1-f70.google.com
 [209.85.221.70]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-420-r-G_YilxMWm2oxqK3OZFzQ-1; Wed, 01 Apr 2020 04:13:52 -0400
X-MC-Unique: r-G_YilxMWm2oxqK3OZFzQ-1
Received: by mail-wr1-f70.google.com with SMTP id y1so14207913wrn.10
        for <kvm@vger.kernel.org>; Wed, 01 Apr 2020 01:13:52 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=cU+okLsMKSqHOKUW7pNlWD/YMAsYMmyQn6ZUscB8aaA=;
        b=AA2yzg6V2d5tcz26u6gd2HNJpk7GL7Imj5UOsKoquZRRJH3O7BVGYR0UeLZq90A+Fz
         BrvRIwxu7YBgj1mNKuqZMbQkVmPGSLAbNYN9l6qXNBQ0LQTgNhqOgo2ACyVzfivm2mFN
         6ZVHPDDl1CqAypYbxaH6KtPzPHeXDiND4LVGqc5/qR1s4nbVTDs99Vi+ExVQhYb4uZKI
         ASUdDwPf0pkzh17srHeoifuKbpYJU4SrlrrAnqszaiBMSOZQ/sXiYSsl+pqMRwjP3tqJ
         pFAAsxqyc9OUbnaBx1cRQBpcJgdwWKk5c9tTl0BQdihRjP+94ifLlhT+5PANUVJKmrf2
         /+ZA==
X-Gm-Message-State: ANhLgQ0yBIoVQvwhtnf5BRYuFB5ckQWVZ4aRl0SUu8ON1pt7D+6qlQAh
        3PGcVcG8D9YEixzHCsiE5rSD4GztjrnrNq7E+4+jy8nNpP/iBQgXliTfRjxVuE9+YoIxM4qx432
        aSOFg+wXzsATA
X-Received: by 2002:adf:82c5:: with SMTP id 63mr24282615wrc.312.1585728831193;
        Wed, 01 Apr 2020 01:13:51 -0700 (PDT)
X-Google-Smtp-Source: 
 ADFU+vulGMjI4Nsim53ni39KXrS3G3GMQJsPvuNJhEQA50Sov48kj3Pwv0cKCOqLAqS/Et+Hnnw+HQ==
X-Received: by 2002:adf:82c5:: with SMTP id 63mr24282595wrc.312.1585728830954;
        Wed, 01 Apr 2020 01:13:50 -0700 (PDT)
Received: from vitty.brq.redhat.com (g-server-2.ign.cz. [91.219.240.2])
        by smtp.gmail.com with ESMTPSA id
 x206sm1662492wmg.17.2020.04.01.01.13.49
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 01 Apr 2020 01:13:50 -0700 (PDT)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>
Cc: Jim Mattson <jmattson@google.com>,
        Wanpeng Li <wanpengli@tencent.com>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: VMX: fix crash cleanup when KVM wasn't used
Date: Wed,  1 Apr 2020 10:13:48 +0200
Message-Id: <20200401081348.1345307-1-vkuznets@redhat.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If KVM wasn't used at all before we crash the cleanup procedure fails with
 BUG: unable to handle page fault for address: ffffffffffffffc8
 #PF: supervisor read access in kernel mode
 #PF: error_code(0x0000) - not-present page
 PGD 23215067 P4D 23215067 PUD 23217067 PMD 0
 Oops: 0000 [#8] SMP PTI
 CPU: 0 PID: 3542 Comm: bash Kdump: loaded Tainted: G      D           5.6.0-rc2+ #823
 RIP: 0010:crash_vmclear_local_loaded_vmcss.cold+0x19/0x51 [kvm_intel]

The root cause is that loaded_vmcss_on_cpu list is not yet initialized,
we initialize it in hardware_enable() but this only happens when we start
a VM.

Previously, we used to have a bitmap with enabled CPUs and that was
preventing [masking] the issue.

Initialized loaded_vmcss_on_cpu list earlier, right before we assign
crash_vmclear_loaded_vmcss pointer. blocked_vcpu_on_cpu list and
blocked_vcpu_on_cpu_lock are moved altogether for consistency.

Fixes: 31603d4fc2bb ("KVM: VMX: Always VMCLEAR in-use VMCSes during crash with kexec support")
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/vmx/vmx.c | 12 +++++++-----
 1 file changed, 7 insertions(+), 5 deletions(-)

```
#### [PATCH v5 1/3] Add a new LSM-supporting anonymous inode interfaceFrom: Daniel Colascione <dancol@google.com>
##### From: Daniel Colascione <dancol@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Daniel Colascione <dancol@google.com>
X-Patchwork-Id: 11469603
Return-Path: <SRS0=PGN4=5R=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A4F7F81
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  1 Apr 2020 21:39:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 65AD4206E9
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  1 Apr 2020 21:39:37 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="HxNEkkJW"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1733278AbgDAVjg (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 1 Apr 2020 17:39:36 -0400
Received: from mail-pf1-f201.google.com ([209.85.210.201]:33375 "EHLO
        mail-pf1-f201.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1733228AbgDAVjS (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 1 Apr 2020 17:39:18 -0400
Received: by mail-pf1-f201.google.com with SMTP id o5so928955pfp.0
        for <kvm@vger.kernel.org>; Wed, 01 Apr 2020 14:39:15 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=YscA6Q2kVGFH1HcouLoCM3aSD8oDJbRIEKtVaQfAjvc=;
        b=HxNEkkJW57bngbpunni/nBN68oGx9Jk1oR8bT8TaxxsfN6UE5XlCMGp8B8G/8qpFHN
         mWiJmKNww3fp2vAVCu1Eq4KptGDaloPVraWXiOziSCTp+AUKIpi9V9Cue0gNKfzKR0qi
         UrbwHShuv4eBtA3ZrTSJ2CDw2TENj3o6pM1hm6g/mJRA3uuvxWFGNZB4CEdWpdg+3zlU
         q8PLQN5SMzbWfOOvd/6e4m5UmQh4qXm+AJxgSD8IkUSyJDGIKwJMUzDT+imovohlgS4E
         1Gx6Nq3cwDMfgRcIZnUglk5alJOpmTeb62Ux0nhoBQI7iHCsYw0MQ+VwlQET6eywUcKA
         vNIA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=YscA6Q2kVGFH1HcouLoCM3aSD8oDJbRIEKtVaQfAjvc=;
        b=Gb6CEXwZxCkS7fwMO89N20B6anRI9fRkQli20xGmDSjqMm5rWr7YqbtQMQYRDIF/Hg
         kuvFfLE2lV9OMpu3RNcyCp0IHZCoF+qzAMdMuRABwgf05hradbL0yJv6M94yOrfsujt3
         UpaJ3zfQ5P2jeG0OScdTKVyYZaiWO07irHJETsFTBUC2prS24nwDR9XI7CuEjjPblvdp
         mZ/Kvk0OUca9dD4GhiF4mUpHgQsux3VVsJ9Gwtr+y23ZopC6Zp5dHik1FP3LfmLs53IB
         5uyQC0VUd/mYtmkDfkIxWKCfP28q43122uiuYffoTMcrDmRS65CWJDrMlOr6XW0nrnN5
         YlLg==
X-Gm-Message-State: AGi0PuaLiXCPel3jGGmxcwY2qE788X1rdi5xUJX0j1mEsfvgBn+BiePh
        sOnEPd0qokV/YF9dKye8sOTzVYrpTbA=
X-Google-Smtp-Source: 
 APiQypJuo8aeRmGJ4byP6CTvKUFIfWx8pqjZ6dBD9ad0ON5qSiHMKr9nsy8NzdNxdNSGqmuTyTe+36UsNos=
X-Received: by 2002:a17:90a:1b22:: with SMTP id
 q31mr15047pjq.109.1585777154601;
 Wed, 01 Apr 2020 14:39:14 -0700 (PDT)
Date: Wed,  1 Apr 2020 14:39:01 -0700
In-Reply-To: <20200401213903.182112-1-dancol@google.com>
Message-Id: <20200401213903.182112-2-dancol@google.com>
Mime-Version: 1.0
References: <20200326200634.222009-1-dancol@google.com>
 <20200401213903.182112-1-dancol@google.com>
X-Mailer: git-send-email 2.26.0.rc2.310.g2932bb562d-goog
Subject: [PATCH v5 1/3] Add a new LSM-supporting anonymous inode interface
From: Daniel Colascione <dancol@google.com>
To: timmurray@google.com, selinux@vger.kernel.org,
        linux-security-module@vger.kernel.org,
        linux-fsdevel@vger.kernel.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, viro@zeniv.linux.org.uk, paul@paul-moore.com,
        nnk@google.com, sds@tycho.nsa.gov, lokeshgidra@google.com,
        jmorris@namei.org
Cc: Daniel Colascione <dancol@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This change adds two new functions, anon_inode_getfile_secure and
anon_inode_getfd_secure, that create anonymous-node files with
individual non-S_PRIVATE inodes to which security modules can apply
policy. Existing callers continue using the original singleton-inode
kind of anonymous-inode file. We can transition anonymous inode users
to the new kind of anonymous inode in individual patches for the sake
of bisection and review.

The new functions accept an optional context_inode parameter that
callers can use to provide additional contextual information to
security modules, e.g., indicating that one anonymous struct file is a
logical child of another, allowing a security model to propagate
security information from one to the other.

Signed-off-by: Daniel Colascione <dancol@google.com>
---
 fs/anon_inodes.c            | 191 ++++++++++++++++++++++++++++--------
 include/linux/anon_inodes.h |  13 +++
 include/linux/lsm_hooks.h   |  11 +++
 include/linux/security.h    |   3 +
 security/security.c         |   9 ++
 5 files changed, 186 insertions(+), 41 deletions(-)

```
#### [PATCH v2 1/2] KVM: X86: Filter out the broadcast dest for IPI fastpath
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11468495
Return-Path: <SRS0=PGN4=5R=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4411A159A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  1 Apr 2020 00:19:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 166B920772
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  1 Apr 2020 00:19:49 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="qV7Egt69"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731508AbgDAATd (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 31 Mar 2020 20:19:33 -0400
Received: from mail-pg1-f193.google.com ([209.85.215.193]:34194 "EHLO
        mail-pg1-f193.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1731470AbgDAATd (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 31 Mar 2020 20:19:33 -0400
Received: by mail-pg1-f193.google.com with SMTP id l14so4060986pgb.1;
        Tue, 31 Mar 2020 17:19:32 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=8Z8cYPNA1Nnx+ynlfYUK6Uh1qA4I2RWYXKrKRt2N0YE=;
        b=qV7Egt69AFSYm63oan9OEeaDZCWNVhxRplH9ijcJinhqTPrM/ZGkiqPbKmU8fTx2Yn
         sdAno83KlgvyAT7AxdzAGOzk1JBDZFky9/yTNV6jYBfe2iUy+eODWvlMPOVSNnjBr8PC
         LMsn5q0GBsIUWIEM3ZiQxfcS0Jy/9SNx2hizD27ai+aVMAX4HjQ2NEm7GFMmcoP39JC1
         Wz8pU4/8gRyBREb7ZdQolpMu9mNcr5xZBu1Qq7S5FNNRnops2NqT5ZPGwJFqNDUq7At+
         AbXqAqsdSyfWZmRrzP7bpo/12+Kw7jw+BHEhPeqQBFUeZqzqQiTYh7Eg4z4O06E92eZ5
         xEfw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=8Z8cYPNA1Nnx+ynlfYUK6Uh1qA4I2RWYXKrKRt2N0YE=;
        b=iJ6eHLI3V7OEzQZFNvPelCJ41HLIKaSlP0BWjRgikvVEQ9GyiSRlcb1JFsAwGzMCHW
         GBS5DLpJzRw3P3HpiTm/IhXqR/ffdtx7ahkressPzUsTTCr2+ZC/xHa7oTlcTXJVyDVS
         52+QKJCBK9CLj0yD2xF1w82UguvoOgSbIptm3taQLM2Y76Hnxb8UXb2FIKyv+yNzjbO/
         wMQRkTWMK40klL42k0oy0TK/vdpJ06+cg7+TWz7DaX9cpwmlECEJyy8FzZtp1K/IZ93N
         vvuk5483GiA8dxEq2sh4lfANPnCCvIMWi1MwWLlKbsMQDif3MjrSoaQ9ekKIOljRvjSz
         xbxg==
X-Gm-Message-State: ANhLgQ3wXLmIEVVv+Z1aONHd3WtjRn0ZNbgoD2mmS+RrM0cH+o6/U1Yt
        6MVnP62AgQcuvuNkhmnXW+b/zX/r
X-Google-Smtp-Source: 
 ADFU+vuyLauhhsGiDnxRt45W7U5JB4YVBUGUkpBSElEOAwA/hE43H+Hki5xQrb+Z9SntSrnZUNFKRA==
X-Received: by 2002:aa7:9844:: with SMTP id n4mr19644750pfq.98.1585700371738;
        Tue, 31 Mar 2020 17:19:31 -0700 (PDT)
Received: from localhost.localdomain ([103.7.29.6])
        by smtp.googlemail.com with ESMTPSA id
 ci18sm206978pjb.23.2020.03.31.17.19.29
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-SHA bits=128/128);
        Tue, 31 Mar 2020 17:19:31 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>
Subject: [PATCH v2 1/2] KVM: X86: Filter out the broadcast dest for IPI
 fastpath
Date: Wed,  1 Apr 2020 08:19:21 +0800
Message-Id: <1585700362-11892-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

Except destination shorthand, a destination value 0xffffffff is used to
broadcast interrupts, let's also filter out this for single target IPI 
fastpath.

Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
v1 -> v2:
 * update subject and patch description

 arch/x86/kvm/lapic.c | 3 ---
 arch/x86/kvm/lapic.h | 3 +++
 arch/x86/kvm/x86.c   | 3 ++-
 3 files changed, 5 insertions(+), 4 deletions(-)

```
#### [PATCH] vfio: Ignore -ENODEV when getting MSI cookie
##### From: Andre Przywara <andre.przywara@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andre Przywara <andre.przywara@arm.com>
X-Patchwork-Id: 11468891
Return-Path: <SRS0=PGN4=5R=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A2EF492C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  1 Apr 2020 10:27:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 8BCF12080C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  1 Apr 2020 10:27:37 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732166AbgDAK1e (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 1 Apr 2020 06:27:34 -0400
Received: from foss.arm.com ([217.140.110.172]:48212 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728225AbgDAK1b (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 1 Apr 2020 06:27:31 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 722E11FB;
        Wed,  1 Apr 2020 03:27:30 -0700 (PDT)
Received: from donnerap.arm.com (donnerap.cambridge.arm.com [10.1.197.25])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 239CC3F52E;
        Wed,  1 Apr 2020 03:27:29 -0700 (PDT)
From: Andre Przywara <andre.przywara@arm.com>
To: Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>
Cc: Robin Murphy <robin.murphy@arm.com>, Will Deacon <will@kernel.org>,
        Eric Auger <eric.auger@redhat.com>, kvm@vger.kernel.org,
        iommu@lists.linux-foundation.org, linux-kernel@vger.kernel.org,
        linux-arm-kernel@lists.infradead.org
Subject: [PATCH] vfio: Ignore -ENODEV when getting MSI cookie
Date: Wed,  1 Apr 2020 11:27:24 +0100
Message-Id: <20200401102724.161712-1-andre.przywara@arm.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When we try to get an MSI cookie for a VFIO device, that can fail if
CONFIG_IOMMU_DMA is not set. In this case iommu_get_msi_cookie() returns
-ENODEV, and that should not be fatal.

Ignore that case and proceed with the initialisation.

This fixes VFIO with a platform device on the Calxeda Midway (no MSIs).

Fixes: f6810c15cf973f ("iommu/arm-smmu: Clean up early-probing workarounds")
Signed-off-by: Andre Przywara <andre.przywara@arm.com>
Acked-by: Robin Murphy <robin.murphy@arm.com>
Reviewed-by: Eric Auger <eric.auger@redhat.com>
---
 drivers/vfio/vfio_iommu_type1.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v4 1/7] vhost: option to fetch descriptors through an independent struct
##### From: =?utf-8?q?Eugenio_P=C3=A9rez?= <eperezma@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Eugenio Perez Martin <eperezma@redhat.com>
X-Patchwork-Id: 11469395
Return-Path: <SRS0=PGN4=5R=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4C0AC913
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  1 Apr 2020 18:31:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 16682208FE
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  1 Apr 2020 18:31:38 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="TN9b3/A9"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732677AbgDASbh (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 1 Apr 2020 14:31:37 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:29602 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1732979AbgDASbf (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 1 Apr 2020 14:31:35 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1585765893;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=IrU9ncNjbn1K5Fs1mRXL7NsJC/LkFAIBP9NEw8v9ThY=;
        b=TN9b3/A9EEp+w/4Af3WaWwplxpgnFd9+C19O4ktwSMGuAILpEtZMl2EU1XOUatohF2Az5Z
        lXPhCkLOssM4t9WbpsoQL/9iyUajibVOS1pk1Vi6kHRHStd9rY/yTF+i5DlZgX7dEqJwNF
        wci/C5czKs+RE6LogUkg4j1DfoW8lh8=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-209-bbq3A0CKOfGR4ZFxbLRNPg-1; Wed, 01 Apr 2020 14:31:31 -0400
X-MC-Unique: bbq3A0CKOfGR4ZFxbLRNPg-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 5AC31149C3;
        Wed,  1 Apr 2020 18:31:30 +0000 (UTC)
Received: from eperezma.remote.csb (ovpn-113-73.ams2.redhat.com
 [10.36.113.73])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 0058F99DEE;
        Wed,  1 Apr 2020 18:31:27 +0000 (UTC)
From: =?utf-8?q?Eugenio_P=C3=A9rez?= <eperezma@redhat.com>
To: "Michael S. Tsirkin" <mst@redhat.com>
Cc: "virtualization@lists.linux-foundation.org"
  <virtualization@lists.linux-foundation.org>,
 =?utf-8?q?Eugenio_P=C3=A9rez?= <eperezma@redhat.com>,
 Linux Next Mailing List <linux-next@vger.kernel.org>,
 Stephen Rothwell <sfr@canb.auug.org.au>, kvm list <kvm@vger.kernel.org>,
 Halil Pasic <pasic@linux.ibm.com>,
 "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>,
 Cornelia Huck <cohuck@redhat.com>,
 Christian Borntraeger <borntraeger@de.ibm.com>
Subject: [PATCH v4 1/7] vhost: option to fetch descriptors through an
 independent struct
Date: Wed,  1 Apr 2020 20:31:12 +0200
Message-Id: <20200401183118.8334-2-eperezma@redhat.com>
In-Reply-To: <20200401183118.8334-1-eperezma@redhat.com>
References: <20200401183118.8334-1-eperezma@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: "Michael S. Tsirkin" <mst@redhat.com>

The idea is to support multiple ring formats by converting
to a format-independent array of descriptors.

This costs extra cycles, but we gain in ability
to fetch a batch of descriptors in one go, which
is good for code cache locality.

When used, this causes a minor performance degradation,
it's been kept as simple as possible for ease of review.
A follow-up patch gets us back the performance by adding batching.

To simplify benchmarking, I kept the old code around so one can switch
back and forth between old and new code. This will go away in the final
submission.

Signed-off-by: Michael S. Tsirkin <mst@redhat.com>
Signed-off-by: Eugenio Pérez <eperezma@redhat.com>
---
 drivers/vhost/vhost.c | 297 +++++++++++++++++++++++++++++++++++++++++-
 drivers/vhost/vhost.h |  16 +++
 2 files changed, 312 insertions(+), 1 deletion(-)

```
#### [PATCH] virtio/test: fix up after IOTLB changes
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 11469325
Return-Path: <SRS0=PGN4=5R=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6E7471667
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  1 Apr 2020 16:51:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4329220714
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  1 Apr 2020 16:51:25 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Zl+mPrT+"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2389316AbgDAQvV (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 1 Apr 2020 12:51:21 -0400
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:47069 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S2389038AbgDAQvS (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 1 Apr 2020 12:51:18 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1585759876;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=gdTaOIE7tD6LkJdCn+pe1n6Y0DWtGxJuzhgJo7to01o=;
        b=Zl+mPrT+wTj1BlFRJjU62IjUeGvXvOvwpELvoGM8zT+W+/cFrx/GhAHcnd8qbXW/tls/2s
        +Nw/vvYqXLVAXchYIywsQcgsst6zgMdaCKefe8mo4tweeRjInODgTZh/oDeKTzylTX8BPW
        gqT/9uzv73dqU5COlt34sCifzJZN+9A=
Received: from mail-wm1-f70.google.com (mail-wm1-f70.google.com
 [209.85.128.70]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-491-Lsr5C-TDPUWVy3tUOzD-jg-1; Wed, 01 Apr 2020 12:51:15 -0400
X-MC-Unique: Lsr5C-TDPUWVy3tUOzD-jg-1
Received: by mail-wm1-f70.google.com with SMTP id s15so219146wmc.0
        for <kvm@vger.kernel.org>; Wed, 01 Apr 2020 09:51:14 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:mime-version
         :content-disposition:content-transfer-encoding;
        bh=gdTaOIE7tD6LkJdCn+pe1n6Y0DWtGxJuzhgJo7to01o=;
        b=NxKCcwbVXpC15lLgq7ApkECm0R/KGq5hnj9tqx3116JxrQvp2iz38W0+C3v+Fn72Jz
         uROq6ToBNXzhcY9I7ALMwaHtZJbVLsUC9wrtioz+4E6fLf5Vt9iZjo+4+XQ1vB6EOFM7
         1D1VYZcLf3FhbuTZ8YfAABIW6QvxdlQPsK9J4HHswqATs1OmJHJTVMSCFX69JKYesGmG
         WZM4n6o/O4y8iMBBAkjENuZV5KeR8/QtMnMDdx/aUiJtXrQdM3qsQylljc4HZVmgBJkq
         Ki2uGBheYcEDHjawIhkt1oou6aRmpNiMR0+adbPcw9NoKlcWKYOqWSdL0d7ZK7rgTbkD
         UNDQ==
X-Gm-Message-State: ANhLgQ2ftip/h3LmDJktQd/YFpDor7cAnbobgkODTfpeY7JOl4234Bgx
        V0Dn24TqbELGUqP9BkaDSEfQ/UJ55bhGcK3TAcakAl0uUdWbHmFeP0Frlo/UWLgLQjS7zv1fytf
        FI6lRDfnfTRc3
X-Received: by 2002:a5d:400d:: with SMTP id
 n13mr26967268wrp.396.1585759873769;
        Wed, 01 Apr 2020 09:51:13 -0700 (PDT)
X-Google-Smtp-Source: 
 ADFU+vvJ0pgx1SXPbI4O/8Day6ptgGE9mSEX0BpL2/jsBTqjtCm3uyzZttDISrsxNqevsV0Dl4mtNQ==
X-Received: by 2002:a5d:400d:: with SMTP id
 n13mr26967250wrp.396.1585759873521;
        Wed, 01 Apr 2020 09:51:13 -0700 (PDT)
Received: from redhat.com (bzq-79-176-51-222.red.bezeqint.net.
 [79.176.51.222])
        by smtp.gmail.com with ESMTPSA id
 z12sm3729253wrt.27.2020.04.01.09.51.11
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 01 Apr 2020 09:51:12 -0700 (PDT)
Date: Wed, 1 Apr 2020 12:51:11 -0400
From: "Michael S. Tsirkin" <mst@redhat.com>
To: linux-kernel@vger.kernel.org
Cc: Jason Wang <jasowang@redhat.com>,
 Eugenio =?utf-8?b?UMOpcmV6?= <eperezma@redhat.com>, kvm@vger.kernel.org,
 virtualization@lists.linux-foundation.org, netdev@vger.kernel.org
Subject: [PATCH] virtio/test: fix up after IOTLB changes
Message-ID: <20200401165100.276039-1-mst@redhat.com>
MIME-Version: 1.0
Content-Disposition: inline
X-Mailer: git-send-email 2.24.1.751.gd10ce2899c
X-Mutt-Fcc: =sent
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Allow building vringh without IOTLB (that's the case for userspace
builds, will be useful for CAIF/VOD down the road too).
Update for API tweaks.
Don't include vringh with kernel builds.

Cc: Jason Wang <jasowang@redhat.com>
Cc: Eugenio Pérez <eperezma@redhat.com>
Signed-off-by: Michael S. Tsirkin <mst@redhat.com>
---
 drivers/vhost/test.c   | 4 ++--
 drivers/vhost/vringh.c | 5 +++++
 include/linux/vringh.h | 2 ++
 tools/virtio/Makefile  | 3 ++-
 4 files changed, 11 insertions(+), 3 deletions(-)

```
