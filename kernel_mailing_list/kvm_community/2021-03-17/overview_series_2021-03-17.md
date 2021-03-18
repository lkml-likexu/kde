#### [PATCH] KVM: arm: memcg awareness
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 12144851
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 42287C433DB
	for <kvm@archiver.kernel.org>; Wed, 17 Mar 2021 05:47:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0B37264F8C
	for <kvm@archiver.kernel.org>; Wed, 17 Mar 2021 05:47:51 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229707AbhCQFrK (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 17 Mar 2021 01:47:10 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:53842 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229505AbhCQFqi (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 17 Mar 2021 01:46:38 -0400
Received: from mail-pj1-x1033.google.com (mail-pj1-x1033.google.com
 [IPv6:2607:f8b0:4864:20::1033])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 8106FC06174A;
        Tue, 16 Mar 2021 22:46:38 -0700 (PDT)
Received: by mail-pj1-x1033.google.com with SMTP id
 j6-20020a17090adc86b02900cbfe6f2c96so735967pjv.1;
        Tue, 16 Mar 2021 22:46:38 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=sFTz8R2vigLKi9iWMm18EDY9PtezCXHbF1qxsbTA9V8=;
        b=kF9n2d9+uTFBuq2VaPeXXOyF8Qnw1Wsqzb7UKEXl7ar5PrLbwd81nsHSLfxkTVnISc
         +aXQilVPfyfwK44D51PHoVex0TA1TPmC5yROYAtk5/cWEu0NJaxjaIKTV82p7wDXu48H
         eGEfJjAB7swZi1FGw/A1cKBUeKM3puivg64cJMimefTVBOwVIUjs3wrelmPY2qhBPKvM
         Mlb5FAQgk8+sfP8ZqpdF9fJLdVjTQ5fJW4d0wG82iON+8xSnqJHEygMj5nwAUhB/urvB
         bC8jVOerxWilrEloQm+MyCipAiKexn7GicaUl2sqkrE6Gn/GYZvJPCmBcU6jmntoJbrX
         GyQg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=sFTz8R2vigLKi9iWMm18EDY9PtezCXHbF1qxsbTA9V8=;
        b=bXfV/2qHCxjHTuXMuiXcu20UY4GkFbgCdrQg9YcEqq66uwJ4+6CfDAv1BuhtuxMfEM
         iZCej1br8/IKlkzt1Gbod4h0V9rJ0Qk7lkQlfTgT6q+6icBS07NiomyYq2dLMx4/ymZP
         ml6o3qdOeiu0T/UBXrNBLwCwMbHBMScYriQ8ySxgi0kwn95I3bEc19Fj9NaHHOZSmlOH
         ZC6xEHWeVIm2JI9gvq4t+pebsdPd/iNSrpPTCUO6cjVqgpl5uu6aPJJQ0bbVqttC6SkL
         xeC7EQmI55vyfbVENIVhLmGuwjX3WXrh3iEluYBpGNv+GDSMKrZV/Kg6+0ZN4WXpE3JG
         JAig==
X-Gm-Message-State: AOAM533turufVoFXQ4la5n/8KUWy0LaEnZShuyFtllP8Vxf88bMpVSZW
        4dcB8NHcU6mnqWzEUrNliQFuKGf/DW8=
X-Google-Smtp-Source: 
 ABdhPJyUgQR7mBw9H3mhAkzBcPXVCK0KCgfJTy/xGnHVDgoL/DbAKl8A/M7m1DsNAdhvsQmkHpXT3g==
X-Received: by 2002:a17:902:9786:b029:e6:508a:7b8c with SMTP id
 q6-20020a1709029786b02900e6508a7b8cmr2928412plp.44.1615959997715;
        Tue, 16 Mar 2021 22:46:37 -0700 (PDT)
Received: from localhost.localdomain ([103.7.29.6])
        by smtp.googlemail.com with ESMTPSA id
 gw20sm1183198pjb.3.2021.03.16.22.46.35
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Tue, 16 Mar 2021 22:46:36 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>, Marc Zyngier <maz@kernel.org>
Subject: [PATCH] KVM: arm: memcg awareness
Date: Wed, 17 Mar 2021 13:46:24 +0800
Message-Id: <1615959984-7122-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

KVM allocations in the arm kvm code which are tied to the life 
of the VM process should be charged to the VM process's cgroup.
This will help the memcg controler to do the right decisions.

Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/arm64/kvm/arm.c               |  5 +++--
 arch/arm64/kvm/hyp/pgtable.c       |  4 ++--
 arch/arm64/kvm/mmu.c               |  4 ++--
 arch/arm64/kvm/pmu-emul.c          |  2 +-
 arch/arm64/kvm/reset.c             |  2 +-
 arch/arm64/kvm/vgic/vgic-debug.c   |  2 +-
 arch/arm64/kvm/vgic/vgic-init.c    |  2 +-
 arch/arm64/kvm/vgic/vgic-irqfd.c   |  2 +-
 arch/arm64/kvm/vgic/vgic-its.c     | 14 +++++++-------
 arch/arm64/kvm/vgic/vgic-mmio-v3.c |  2 +-
 arch/arm64/kvm/vgic/vgic-v4.c      |  2 +-
 11 files changed, 21 insertions(+), 20 deletions(-)

```
#### [PATCH] KVM: nSVM: Additions to optimizing L12 to L2 vmcb.save copies
##### From: Cathy Avery <cavery@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Cathy Avery <cavery@redhat.com>
X-Patchwork-Id: 12146391
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 20F14C433E0
	for <kvm@archiver.kernel.org>; Wed, 17 Mar 2021 16:30:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B5FC264EFC
	for <kvm@archiver.kernel.org>; Wed, 17 Mar 2021 16:30:13 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232503AbhCQQ3l (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 17 Mar 2021 12:29:41 -0400
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:33172 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S232348AbhCQQ3g (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 17 Mar 2021 12:29:36 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1615998576;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=Ec77b3T6zhXo/PBg8ex/iLP72N94UqDgNwEoG/Vb6t8=;
        b=DqO4PpVzp42TlZ4IPAicNaT/VxcNiaEMvT6Are+TUUzejoQPfhKG2xOl9tVJ/sBTXTwlPA
        5oH8jD1XI08YsmucwpJltdexU5vozXvzlsS0hSnJEDN8zuotntWnRYiBgAMIU+EQZgpbeZ
        MuimchvWrsbKAHFL4NUFl2wAKNGd7mY=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-268-nxFpyJPkO1eddoAvyEObOw-1; Wed, 17 Mar 2021 12:29:32 -0400
X-MC-Unique: nxFpyJPkO1eddoAvyEObOw-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 505EA107B7CC;
        Wed, 17 Mar 2021 16:29:31 +0000 (UTC)
Received: from virtlab710.virt.lab.eng.bos.redhat.com
 (virtlab710.virt.lab.eng.bos.redhat.com [10.19.152.252])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 8CACA607CB;
        Wed, 17 Mar 2021 16:29:30 +0000 (UTC)
From: Cathy Avery <cavery@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        pbonzini@redhat.com
Cc: vkuznets@redhat.com, wei.huang2@amd.com, seanjc@google.com
Subject: [PATCH] KVM: nSVM: Additions to optimizing L12 to L2 vmcb.save copies
Date: Wed, 17 Mar 2021 12:29:30 -0400
Message-Id: <20210317162930.28135-1-cavery@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Extend using the vmcb12 control clean field to determine which
vmcb12.save registers were marked dirty in order to minimize
register copies by including the CR bit.

This patch also fixes the init of last_vmcb12_gpa by using an invalid
physical address instead of 0.

Tested:
kvm-unit-tests
kvm selftests
Fedora L1 L2

Signed-off-by: Cathy Avery <cavery@redhat.com>
---
 arch/x86/kvm/svm/nested.c | 9 ++++++---
 arch/x86/kvm/svm/svm.c    | 2 +-
 2 files changed, 7 insertions(+), 4 deletions(-)

```
#### [PATCH] selftests/kvm: add set_boot_cpu_id test
##### From: Emanuele Giuseppe Esposito <eesposit@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Emanuele Giuseppe Esposito <eesposit@redhat.com>
X-Patchwork-Id: 12145053
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 001BDC433E0
	for <kvm@archiver.kernel.org>; Wed, 17 Mar 2021 07:45:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BE8F964F97
	for <kvm@archiver.kernel.org>; Wed, 17 Mar 2021 07:45:40 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229944AbhCQHpI (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 17 Mar 2021 03:45:08 -0400
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:54961 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S230037AbhCQHog (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 17 Mar 2021 03:44:36 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1615967076;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=E7lOQe7PvDbVUdX18nkCBlvg+ruDLnYJ/lmRsra5G8U=;
        b=Hdn+pKCAW143O6ufoaYicbSy4P9pRnI1bawc3hymBYS9XTVreXTCIgCzwrKlNp0VBi3/zS
        mzIv7UesSWjjlJCshCyVr9qgnnpTqazm4XTtEqgduyUi2IcooQJLsJPG2E1yhbXDX7Hj4h
        2nHCMqpMUgvqnvOukHgJw5m+2YXQEss=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-168-ChyaVYWaPBurYg5UPcvknA-1; Wed, 17 Mar 2021 03:44:32 -0400
X-MC-Unique: ChyaVYWaPBurYg5UPcvknA-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 6989C1007467;
        Wed, 17 Mar 2021 07:44:31 +0000 (UTC)
Received: from localhost.localdomain.com (ovpn-113-104.ams2.redhat.com
 [10.36.113.104])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 5D75D6268D;
        Wed, 17 Mar 2021 07:44:29 +0000 (UTC)
From: Emanuele Giuseppe Esposito <eesposit@redhat.com>
To: linux-kselftest@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>, Shuah Khan <shuah@kernel.org>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [PATCH] selftests/kvm: add set_boot_cpu_id test
Date: Wed, 17 Mar 2021 08:44:26 +0100
Message-Id: <20210317074426.8224-1-eesposit@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Test for the KVM_SET_BOOT_CPU_ID ioctl.
Check that it correctly allows to change the BSP vcpu.

Signed-off-by: Emanuele Giuseppe Esposito <eesposit@redhat.com>
---
 tools/testing/selftests/kvm/.gitignore        |   1 +
 tools/testing/selftests/kvm/Makefile          |   1 +
 .../selftests/kvm/x86_64/set_boot_cpu_id.c    | 151 ++++++++++++++++++
 3 files changed, 153 insertions(+)
 create mode 100644 tools/testing/selftests/kvm/x86_64/set_boot_cpu_id.c

```
#### [PATCH] selftests/kvm: add test for KVM_GET_MSR_FEATURE_INDEX_LIST
##### From: Emanuele Giuseppe Esposito <eesposit@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Emanuele Giuseppe Esposito <eesposit@redhat.com>
X-Patchwork-Id: 12145055
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 9D4EAC433DB
	for <kvm@archiver.kernel.org>; Wed, 17 Mar 2021 07:46:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 56A8F64EE1
	for <kvm@archiver.kernel.org>; Wed, 17 Mar 2021 07:46:44 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230112AbhCQHqM (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 17 Mar 2021 03:46:12 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:37708 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S229707AbhCQHp7 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 17 Mar 2021 03:45:59 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1615967158;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=RxzIT3AkxMjKIkvJDSVtAjMrZXxeLg+sSQ13b2gtYgk=;
        b=g4SFaHvaSYqBO1xaV60qzCppLP1TZwoWHZ3/waRnox1GQxhNWWlpTflTA70uykQM6hOVZD
        WnCPTF9vFThwcPc0lxJ3hw8lYSAxUWzW4Y7xh6Nivo4cx358C3wAO3j0ClUEVcCnxVBgX7
        T7KCiLcdZAr9HPPGtUw5vkubJXvseQo=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-15-odNBIqSpPBGlYb2scz6QYA-1; Wed, 17 Mar 2021 03:45:56 -0400
X-MC-Unique: odNBIqSpPBGlYb2scz6QYA-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 58E71189CD09;
        Wed, 17 Mar 2021 07:45:55 +0000 (UTC)
Received: from localhost.localdomain.com (ovpn-113-104.ams2.redhat.com
 [10.36.113.104])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 5DACF189BB;
        Wed, 17 Mar 2021 07:45:53 +0000 (UTC)
From: Emanuele Giuseppe Esposito <eesposit@redhat.com>
To: linux-kselftest@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>, Shuah Khan <shuah@kernel.org>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Andrew Jones <drjones@redhat.com>,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [PATCH] selftests/kvm: add test for KVM_GET_MSR_FEATURE_INDEX_LIST
Date: Wed, 17 Mar 2021 08:45:52 +0100
Message-Id: <20210317074552.8550-1-eesposit@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Extend the kvm_get_feature_msr function to cover also
KVM_GET_MSR_FEATURE_INDEX_LIST.

Signed-off-by: Emanuele Giuseppe Esposito <eesposit@redhat.com>
---
 tools/testing/selftests/kvm/lib/x86_64/processor.c | 7 +++++++
 1 file changed, 7 insertions(+)

```
#### [PATCH v3 1/1] irqchip/gic-v4.1: Disable vSGI upon (GIC CPUIF < v4.1) detection
##### From: Lorenzo Pieralisi <lorenzo.pieralisi@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Lorenzo Pieralisi <lorenzo.pieralisi@arm.com>
X-Patchwork-Id: 12145407
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C037CC433E9
	for <kvm@archiver.kernel.org>; Wed, 17 Mar 2021 10:08:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8479B64F5E
	for <kvm@archiver.kernel.org>; Wed, 17 Mar 2021 10:08:15 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229749AbhCQKHp (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 17 Mar 2021 06:07:45 -0400
Received: from foss.arm.com ([217.140.110.172]:56178 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229864AbhCQKH0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 17 Mar 2021 06:07:26 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id C5799101E;
        Wed, 17 Mar 2021 03:07:25 -0700 (PDT)
Received: from e121166-lin.cambridge.arm.com (e121166-lin.cambridge.arm.com
 [10.1.196.255])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 1EEA63F70D;
        Wed, 17 Mar 2021 03:07:25 -0700 (PDT)
From: Lorenzo Pieralisi <lorenzo.pieralisi@arm.com>
To: linux-kernel@vger.kernel.org
Cc: Marc Zyngier <maz@kernel.org>,
        LAKML <linux-arm-kernel@lists.infradead.org>,
        KVM <kvm@vger.kernel.org>
Subject: [PATCH v3 1/1] irqchip/gic-v4.1: Disable vSGI upon (GIC CPUIF < v4.1)
 detection
Date: Wed, 17 Mar 2021 10:07:19 +0000
Message-Id: <20210317100719.3331-2-lorenzo.pieralisi@arm.com>
X-Mailer: git-send-email 2.29.1
In-Reply-To: <20210317100719.3331-1-lorenzo.pieralisi@arm.com>
References: <20210302102744.12692-1-lorenzo.pieralisi@arm.com>
 <20210317100719.3331-1-lorenzo.pieralisi@arm.com>
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
 arch/arm64/kvm/vgic/vgic-mmio-v3.c |  4 ++--
 drivers/irqchip/irq-gic-v4.c       | 27 +++++++++++++++++++++++++--
 include/linux/irqchip/arm-gic-v4.h |  2 ++
 3 files changed, 29 insertions(+), 4 deletions(-)

```
#### [PATCH V5 1/7] vDPA/ifcvf: get_vendor_id returns a device specific vendor id
##### From: Zhu Lingshan <lingshan.zhu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhu Lingshan <lingshan.zhu@intel.com>
X-Patchwork-Id: 12145337
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B7681C43381
	for <kvm@archiver.kernel.org>; Wed, 17 Mar 2021 09:55:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 99D9964F6C
	for <kvm@archiver.kernel.org>; Wed, 17 Mar 2021 09:55:27 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229926AbhCQJyz (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 17 Mar 2021 05:54:55 -0400
Received: from mga04.intel.com ([192.55.52.120]:59767 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229658AbhCQJyo (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 17 Mar 2021 05:54:44 -0400
IronPort-SDR: 
 2SewFoZHUFOjfedgrWyEZjT9DFMNpIsZu0f+MKNuskfsAUyhL2TNBX3/wuoO7VY5DUrnlpmXC2
 PnO5fWBsuKzw==
X-IronPort-AV: E=McAfee;i="6000,8403,9925"; a="187058668"
X-IronPort-AV: E=Sophos;i="5.81,255,1610438400";
   d="scan'208";a="187058668"
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by fmsmga104.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 17 Mar 2021 02:54:44 -0700
IronPort-SDR: 
 VfzgDxxndlBbQuklan0wiatpYmNeTDnNFpyU9A9dExTwkCnpyU7jfre+SC/6YGrf1r52nLIXMW
 iETrflmn8pLA==
X-IronPort-AV: E=Sophos;i="5.81,255,1610438400";
   d="scan'208";a="405873175"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.240.193.73])
  by fmsmga008-auth.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 17 Mar 2021 02:54:41 -0700
From: Zhu Lingshan <lingshan.zhu@intel.com>
To: jasowang@redhat.com, mst@redhat.com, lulu@redhat.com,
        leonro@nvidia.com
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Zhu Lingshan <lingshan.zhu@intel.com>
Subject: [PATCH V5 1/7] vDPA/ifcvf: get_vendor_id returns a device specific
 vendor id
Date: Wed, 17 Mar 2021 17:49:27 +0800
Message-Id: <20210317094933.16417-2-lingshan.zhu@intel.com>
X-Mailer: git-send-email 2.27.0
In-Reply-To: <20210317094933.16417-1-lingshan.zhu@intel.com>
References: <20210317094933.16417-1-lingshan.zhu@intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In this commit, ifcvf_get_vendor_id() will return
a device specific vendor id of the probed pci device
than a hard code.

Signed-off-by: Zhu Lingshan <lingshan.zhu@intel.com>
Acked-by: Jason Wang <jasowang@redhat.com>
---
 drivers/vdpa/ifcvf/ifcvf_main.c | 5 ++++-
 1 file changed, 4 insertions(+), 1 deletion(-)

```
#### [PATCH v2 5/4] KVM: x86: hyper-v: Briefly document enum hv_tsc_page_status
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 12145563
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B3FEFC433DB
	for <kvm@archiver.kernel.org>; Wed, 17 Mar 2021 11:20:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7828264F09
	for <kvm@archiver.kernel.org>; Wed, 17 Mar 2021 11:20:22 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229865AbhCQLTv (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 17 Mar 2021 07:19:51 -0400
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:36337 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S231179AbhCQLTl (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 17 Mar 2021 07:19:41 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1615979980;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=DWegNjY6jdpOK3nQ6dsMm+ViORSOfIsbAq2kyIiD81M=;
        b=SAtbvVJ70LmOsp/wUkpBWu67s/IQmcpDoBEMvAVSlh6Dane9mzuksyRQvyQMQy1lHenzoV
        DXwqQMhUJ2FpmAWk34SlVWJBCZFPmX0ENanmcmnZkhWCwRU0bBgoaAA0b3qUTYpGkCcHhY
        DidFzaeZWsl0HCjyxsOoPFaeH8c43rk=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-368-q2CLEAEaPaKDnMXyHCZBOw-1; Wed, 17 Mar 2021 07:19:38 -0400
X-MC-Unique: q2CLEAEaPaKDnMXyHCZBOw-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 5F0C4107B274;
        Wed, 17 Mar 2021 11:19:37 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.192.211])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 49C6A19C66;
        Wed, 17 Mar 2021 11:19:35 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Marcelo Tosatti <mtosatti@redhat.com>
Subject: [PATCH v2 5/4] KVM: x86: hyper-v: Briefly document enum
 hv_tsc_page_status
Date: Wed, 17 Mar 2021 12:19:34 +0100
Message-Id: <20210317111934.993523-1-vkuznets@redhat.com>
In-Reply-To: <71484ff3-491a-e8a2-3ef4-e21adb4259ee@redhat.com>
References: <71484ff3-491a-e8a2-3ef4-e21adb4259ee@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add comments to enum hv_tsc_page_status documenting what each state means.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/include/asm/kvm_host.h | 7 +++++++
 1 file changed, 7 insertions(+)

```
