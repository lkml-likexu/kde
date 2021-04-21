#### [PATCH kvm-unit-tests v2 1/8] arm/arm64: Reorganize cstart assembler
##### From: Andrew Jones <drjones@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 12214987
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 158CBC433B4
	for <kvm@archiver.kernel.org>; Tue, 20 Apr 2021 19:00:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D2FA2613E0
	for <kvm@archiver.kernel.org>; Tue, 20 Apr 2021 19:00:24 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233689AbhDTTAz (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 20 Apr 2021 15:00:55 -0400
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:49216 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S233509AbhDTTAz (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 20 Apr 2021 15:00:55 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1618945223;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=9sUjdHh8ywF8sopKmZL5sjMWGDVoNwoKZ8hLmiIzFnQ=;
        b=PKg+fJB9fjDg2AIKOtj23kMxchL8a5W/PoUvNGsWZ/ZTiYN3Thaic93iV0uzi0+EwI3yqk
        QnnhMz+5Sn7rzIU6ooSsVbrlAdd9omi7F+9eLSKddhLpj0HVrISoK38aK4S0Y0yPTgVxk5
        MPm82ZZ/KdaVU2BB0kX6RVQS6Ks5zic=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-354-poO-f7sfPyCoYUVIQGcNBQ-1; Tue, 20 Apr 2021 15:00:21 -0400
X-MC-Unique: poO-f7sfPyCoYUVIQGcNBQ-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 499FC87A83C;
        Tue, 20 Apr 2021 19:00:20 +0000 (UTC)
Received: from gator.home (unknown [10.40.195.207])
        by smtp.corp.redhat.com (Postfix) with ESMTP id B29AD19726;
        Tue, 20 Apr 2021 19:00:16 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org
Cc: alexandru.elisei@arm.com, nikos.nikoleris@arm.com,
        andre.przywara@arm.com, eric.auger@redhat.com
Subject: [PATCH kvm-unit-tests v2 1/8] arm/arm64: Reorganize cstart assembler
Date: Tue, 20 Apr 2021 20:59:55 +0200
Message-Id: <20210420190002.383444-2-drjones@redhat.com>
In-Reply-To: <20210420190002.383444-1-drjones@redhat.com>
References: <20210420190002.383444-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Move secondary_entry helper functions out of .init and into .text,
since secondary_entry isn't run at at "init" time. Actually, anything
that is used after init time should be in .text, as we may not include
.init in some build configurations.

Reviewed-by Nikos Nikoleris <nikos.nikoleris@arm.com>
Signed-off-by: Andrew Jones <drjones@redhat.com>
---
 arm/cstart.S   | 66 +++++++++++++++++++++++++++++---------------------
 arm/cstart64.S | 18 ++++++++------
 2 files changed, 49 insertions(+), 35 deletions(-)

```
#### [kvm-unit-tests RFC PATCH 1/1] configure: arm: Replace --vmm with --target
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexandru Elisei <alexandru.elisei@arm.com>
X-Patchwork-Id: 12214625
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 12B48C433B4
	for <kvm@archiver.kernel.org>; Tue, 20 Apr 2021 16:13:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CAB86613CA
	for <kvm@archiver.kernel.org>; Tue, 20 Apr 2021 16:13:12 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232951AbhDTQNn (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 20 Apr 2021 12:13:43 -0400
Received: from foss.arm.com ([217.140.110.172]:37754 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S232901AbhDTQNm (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 20 Apr 2021 12:13:42 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id EAC3214BF;
        Tue, 20 Apr 2021 09:13:10 -0700 (PDT)
Received: from monolith.localdoman (unknown [172.31.20.19])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 280633F73B;
        Tue, 20 Apr 2021 09:13:10 -0700 (PDT)
From: Alexandru Elisei <alexandru.elisei@arm.com>
To: drjones@redhat.com, kvm@vger.kernel.org,
        kvmarm@lists.cs.columbia.edu
Cc: pbonzini@redhat.com
Subject: [kvm-unit-tests RFC PATCH 1/1] configure: arm: Replace --vmm with
 --target
Date: Tue, 20 Apr 2021 17:13:38 +0100
Message-Id: <20210420161338.70914-2-alexandru.elisei@arm.com>
X-Mailer: git-send-email 2.31.1
In-Reply-To: <20210420161338.70914-1-alexandru.elisei@arm.com>
References: <20210420161338.70914-1-alexandru.elisei@arm.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The --vmm configure option was added to distinguish between the two virtual
machine managers that kvm-unit-tests supports, qemu or kvmtool. There are
plans to make kvm-unit-tests work as an EFI app, which will require changes
to the way tests are compiled. Instead of adding a new configure option
specifically for EFI and have it coexist with --vmm, or overloading the
semantics of the existing --vmm option, let's replace --vmm with the more
generic name --target.

--vmm has been kept for now as to avoid breaking existing users, but it has
been modified to shadow value of --target and a message will be displayed
to notify users that it will be removed at some point in the future.

Signed-off-by: Alexandru Elisei <alexandru.elisei@arm.com>
---
 configure | 30 +++++++++++++++++++++++-------
 1 file changed, 23 insertions(+), 7 deletions(-)

```
#### [PATCH] KVM: selftests: Always run vCPU thread with blocked SIG_IPI
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 12213521
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D16B7C433ED
	for <kvm@archiver.kernel.org>; Tue, 20 Apr 2021 08:16:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 90776611C9
	for <kvm@archiver.kernel.org>; Tue, 20 Apr 2021 08:16:30 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229593AbhDTIRA (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 20 Apr 2021 04:17:00 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:42716 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S229521AbhDTIQ7 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 20 Apr 2021 04:16:59 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1618906588;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=XJFMVyj4cgN/sZsxR0u2d2bEIw2+LpoMcRwhutx6v+U=;
        b=aX/jw5Y58mF9GBFaVOBnXWZ2FO+w6OrVJJnhweCtERgS+ZiaQKtxV4QYqkkh/XclZy0u4C
        7AGL7uBtEliJXYiSwQNJOyNKQBnB2ZIX6G2z4GtPC5Xe+HkK8H1tWbx/dbAvBj2N2QpoLP
        GzuNDhMcvuxLohcZAJQpcVTgi9Xp/d4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-267-ZGHcG1ceOoCtUrwHvtHcNw-1; Tue, 20 Apr 2021 04:16:20 -0400
X-MC-Unique: ZGHcG1ceOoCtUrwHvtHcNw-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 772C484B9B0;
        Tue, 20 Apr 2021 08:16:19 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id B55591F04F;
        Tue, 20 Apr 2021 08:16:15 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Peter Xu <peterx@redhat.com>, stable@vger.kernel.org
Subject: [PATCH] KVM: selftests: Always run vCPU thread with blocked SIG_IPI
Date: Tue, 20 Apr 2021 04:16:14 -0400
Message-Id: <20210420081614.684787-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The main thread could start to send SIG_IPI at any time, even before signal
blocked on vcpu thread.  Therefore, start the vcpu thread with the signal
blocked.

Without this patch, on very busy cores the dirty_log_test could fail directly
on receiving a SIGUSR1 without a handler (when vcpu runs far slower than main).

Reported-by: Peter Xu <peterx@redhat.com>
Cc: stable@vger.kernel.org
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Peter Xu <peterx@redhat.com>
---
 tools/testing/selftests/kvm/dirty_log_test.c | 9 +++++++--
 1 file changed, 7 insertions(+), 2 deletions(-)

```
#### [PATCH v4 1/2] KVM: selftests: Sync data verify of dirty logging with guest sync
##### From: Peter Xu <peterx@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 12214517
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 504EAC43460
	for <kvm@archiver.kernel.org>; Tue, 20 Apr 2021 15:39:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0958F613CA
	for <kvm@archiver.kernel.org>; Tue, 20 Apr 2021 15:39:37 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232951AbhDTPkI (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 20 Apr 2021 11:40:08 -0400
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:42999 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S232174AbhDTPkH (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 20 Apr 2021 11:40:07 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1618933175;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=VQROlc+OeyGZWexjfeI5DkN1h4it7ZtOPD/Y6S64EkE=;
        b=XdCH2nOmzfcIGVHIFV0Wu+TDv0LBkima316eKfoIOgp9Fa5HXs2kdJvo3r12sfTLvC3F1X
        4XxdOsxNmCFycLAi/XtIwEH8y6al0aigOTdWMO5va+i6AUgB7BPetrfzvlryUMwKl9g/N/
        AlkSe4gPU32yYssI2OGqdcWgyndRnn8=
Received: from mail-qv1-f69.google.com (mail-qv1-f69.google.com
 [209.85.219.69]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-160-fFXheLrRPjOuujDK-P_dqg-1; Tue, 20 Apr 2021 11:39:34 -0400
X-MC-Unique: fFXheLrRPjOuujDK-P_dqg-1
Received: by mail-qv1-f69.google.com with SMTP id
 f7-20020a0562141d27b029019a6fd0a183so11695287qvd.23
        for <kvm@vger.kernel.org>; Tue, 20 Apr 2021 08:39:34 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=VQROlc+OeyGZWexjfeI5DkN1h4it7ZtOPD/Y6S64EkE=;
        b=erj2HYedpLXd/WGQZTybALYoBe+stmDvonN+JAkbRQ+BelNwF6PWbq6Hp+YsEFaT7w
         V92boF7x1rl9KyhV3omNlpaF6t5MooFPJruNnCvVJh80nmd73kmPO1ZJZ/Q4GLpyNaDf
         vEO0d+q6ZJuuzEovGNNnQb9qv+/jQJYmyJ58JptMszY2/7Feg8yja8UHnfPEpV2rVwPZ
         vpDR5cgKqht7vViYp/40yEb45NHvGKaBhaYd1PTZFplAj5cZSYdQhxr6uHdfP6naN5Hq
         +xTygKgh/lKmUvswITNcIvJp85vzvxfuEb3XvMYvTfrjUXp6/SU8T031j561yd3o7Mth
         EGrg==
X-Gm-Message-State: AOAM5327p42JdOoN1H4QSEgX0eIwjzw3nBFVyh/JgsKItfmvvE46ERuh
        8ULNlMZSqaKtn4FUbGjretqaX9sryecyr3GhGtSlqbfKYr5Xdpj7kr05ZRSvjWG4jNbXOjGA4KG
        2q9/6CelKsXdHkOZkXvSGcjsyisn+0Uu74BbGwn40LkzdgwmGZRSRXRGbxxkNWA==
X-Received: by 2002:ac8:5211:: with SMTP id
 r17mr13144775qtn.179.1618933173624;
        Tue, 20 Apr 2021 08:39:33 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJyx788RWtu3yNEcSOoXG9InX91GFPv3sAMNKtitjKsZi6xwq4T0JutImzI2/i7wU4um1ng7PA==
X-Received: by 2002:ac8:5211:: with SMTP id
 r17mr13144748qtn.179.1618933173297;
        Tue, 20 Apr 2021 08:39:33 -0700 (PDT)
Received: from xz-x1.redhat.com
 (bras-base-toroon474qw-grc-88-174-93-75-154.dsl.bell.ca. [174.93.75.154])
        by smtp.gmail.com with ESMTPSA id
 f12sm11633325qtq.84.2021.04.20.08.39.31
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 20 Apr 2021 08:39:32 -0700 (PDT)
From: Peter Xu <peterx@redhat.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>, peterx@redhat.com,
        Sean Christopherson <seanjc@google.com>,
        Andrew Jones <drjones@redhat.com>
Subject: [PATCH v4 1/2] KVM: selftests: Sync data verify of dirty logging with
 guest sync
Date: Tue, 20 Apr 2021 11:39:28 -0400
Message-Id: <20210420153929.482810-2-peterx@redhat.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20210420153929.482810-1-peterx@redhat.com>
References: <20210420153929.482810-1-peterx@redhat.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This fixes a bug that can trigger with e.g. "taskset -c 0 ./dirty_log_test" or
when the testing host is very busy.

A similar previous attempt is done [1] but that is not enough, the reason is
stated in the reply [2].

As a summary (partly quotting from [2]):

The problem is I think one guest memory write operation (of this specific test)
contains a few micro-steps when page is during kvm dirty tracking (here I'm
only considering write-protect rather than pml but pml should be similar at
least when the log buffer is full):

  (1) Guest read 'iteration' number into register, prepare to write, page fault
  (2) Set dirty bit in either dirty bitmap or dirty ring
  (3) Return to guest, data written

When we verify the data, we assumed that all these steps are "atomic", say,
when (1) happened for this page, we assume (2) & (3) must have happened.  We
had some trick to workaround "un-atomicity" of above three steps, as previous
version of this patch wanted to fix atomicity of step (2)+(3) by explicitly
letting the main thread wait for at least one vmenter of vcpu thread, which
should work.  However what I overlooked is probably that we still have race
when (1) and (2) can be interrupted.

One example calltrace when it could happen that we read an old interation, got
interrupted before even setting the dirty bit and flushing data:

    __schedule+1742
    __cond_resched+52
    __get_user_pages+530
    get_user_pages_unlocked+197
    hva_to_pfn+206
    try_async_pf+132
    direct_page_fault+320
    kvm_mmu_page_fault+103
    vmx_handle_exit+288
    vcpu_enter_guest+2460
    kvm_arch_vcpu_ioctl_run+325
    kvm_vcpu_ioctl+526
    __x64_sys_ioctl+131
    do_syscall_64+51
    entry_SYSCALL_64_after_hwframe+68

It means iteration number cached in vcpu register can be very old when dirty
bit set and data flushed.

So far I don't see an easy way to guarantee all steps 1-3 atomicity but to sync
at the GUEST_SYNC() point of guest code when we do verification of the dirty
bits as what this patch does.

[1] https://lore.kernel.org/lkml/20210413213641.23742-1-peterx@redhat.com/
[2] https://lore.kernel.org/lkml/20210417140956.GV4440@xz-x1/

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>
Cc: Andrew Jones <drjones@redhat.com>
Signed-off-by: Peter Xu <peterx@redhat.com>
---
 tools/testing/selftests/kvm/dirty_log_test.c | 62 ++++++++++++++++----
 1 file changed, 51 insertions(+), 11 deletions(-)

```
#### [PATCH] KVM: x86: add MSR_KVM_MIGRATION_CONTROL
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 12213753
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 8830EC433B4
	for <kvm@archiver.kernel.org>; Tue, 20 Apr 2021 10:59:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 48B0361026
	for <kvm@archiver.kernel.org>; Tue, 20 Apr 2021 10:59:36 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231717AbhDTLAF (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 20 Apr 2021 07:00:05 -0400
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:51971 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S231415AbhDTK75 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 20 Apr 2021 06:59:57 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1618916366;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=T/UowxEhrgES9Z8e890ShmFG6Jnrs7CSOo/ni1CNTGY=;
        b=SbTOQMJoK1s/jO1+doA5xsDbRhpGyiSLrON6QNDPyL93eSMUZPXG8a/ICmlnzXmw6pqnqO
        Ih18pfdIHBOVIlz3ztQWJlLdS0n/LUR3IfW5aDcBflKw1gKp98RhN7ntFQ33IL2HiiN2j+
        3bWrqCsXF8ztBiYTEsPqynMtGSBplrI=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-386-27crLentM5Wiw6DBkRVYuw-1; Tue, 20 Apr 2021 06:59:24 -0400
X-MC-Unique: 27crLentM5Wiw6DBkRVYuw-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 75814107ACC7;
        Tue, 20 Apr 2021 10:59:23 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 35B5063BAF;
        Tue, 20 Apr 2021 10:59:23 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [PATCH] KVM: x86: add MSR_KVM_MIGRATION_CONTROL
Date: Tue, 20 Apr 2021 06:59:22 -0400
Message-Id: <20210420105922.730705-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add a new MSR that can be used to communicate whether the page
encryption status bitmap is up to date and therefore whether live
migration of an encrypted guest is possible.

The MSR should be processed by userspace if it is going to live
migrate the guest; the default implementation does nothing.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 Documentation/virt/kvm/cpuid.rst     |  3 ++-
 Documentation/virt/kvm/msr.rst       | 10 ++++++++++
 arch/x86/include/uapi/asm/kvm_para.h |  3 +++
 arch/x86/kvm/x86.c                   | 14 ++++++++++++++
 4 files changed, 29 insertions(+), 1 deletion(-)

```
#### [PATCH] KVM: x86: document behavior of measurement ioctls with len==0
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 12213657
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 23272C433ED
	for <kvm@archiver.kernel.org>; Tue, 20 Apr 2021 09:34:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id EAA096101E
	for <kvm@archiver.kernel.org>; Tue, 20 Apr 2021 09:34:19 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231255AbhDTJet (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 20 Apr 2021 05:34:49 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:38837 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S230491AbhDTJer (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 20 Apr 2021 05:34:47 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1618911255;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=HR9PGFeuseuv+4p0efVgdR4ZvWDR0WWeCLxvhuktGw8=;
        b=RDx/XDB48pjHJzSqYv+bdY95dViPBnmwOM4bVD3C6NFbCJnZaeCbrq6TbUrjSney5DaPpw
        uvfokhh/er6zIUkJmsykLmk1kyyQVtj3dCUe794YZcYrelIHOBgNQYdJFbZer3yfuIRElC
        cUVmTXPR3iNqTJDN5hbgOBYH0VWqQ0w=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-319-SJp_Z5AbNziPaAD3TyvAdw-1; Tue, 20 Apr 2021 05:34:13 -0400
X-MC-Unique: SJp_Z5AbNziPaAD3TyvAdw-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id C5736107ACCA;
        Tue, 20 Apr 2021 09:34:12 +0000 (UTC)
Received: from virtlab511.virt.lab.eng.bos.redhat.com
 (virtlab511.virt.lab.eng.bos.redhat.com [10.19.152.198])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 6152710016FE;
        Tue, 20 Apr 2021 09:34:12 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Brijesh Singh <brijesh.singh@amd.com>
Subject: [PATCH] KVM: x86: document behavior of measurement ioctls with len==0
Date: Tue, 20 Apr 2021 05:34:11 -0400
Message-Id: <20210420093411.1498840-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Brijesh Singh <brijesh.singh@amd.com>
---
 Documentation/virt/kvm/amd-memory-encryption.rst | 6 ++++++
 1 file changed, 6 insertions(+)

```
#### [RFC PATCH 01/10] KVM: x86/mmu: make kvm_mmu_do_page_fault() receive single argument
##### From: Isaku Yamahata <isaku.yamahata@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Isaku Yamahata <isaku.yamahata@intel.com>
X-Patchwork-Id: 12213709
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.9 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,UNWANTED_LANGUAGE_BODY,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A73BBC433B4
	for <kvm@archiver.kernel.org>; Tue, 20 Apr 2021 10:41:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 73FE4611C9
	for <kvm@archiver.kernel.org>; Tue, 20 Apr 2021 10:41:48 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231671AbhDTKmR (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 20 Apr 2021 06:42:17 -0400
Received: from mga17.intel.com ([192.55.52.151]:34977 "EHLO mga17.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S230408AbhDTKmP (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 20 Apr 2021 06:42:15 -0400
IronPort-SDR: 
 TUoqpsJHxP4vLmk11bgj4/ZvxnzMowg7iwMdfkS5NjpsZUz/FNG8rF7Hyr7IcnSv42gQzWwlUm
 zAXIANzrt0PQ==
X-IronPort-AV: E=McAfee;i="6200,9189,9959"; a="175590747"
X-IronPort-AV: E=Sophos;i="5.82,236,1613462400";
   d="scan'208";a="175590747"
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by fmsmga107.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 20 Apr 2021 03:41:43 -0700
IronPort-SDR: 
 PgcJyC6Spz86JsutWm9mJTNo0SjljbSXcmSx+1ZYxWRD9PgUHgaj7NQik0/pGcNlp8XlIL1qj4
 MzpwujgIilxg==
X-IronPort-AV: E=Sophos;i="5.82,236,1613462400";
   d="scan'208";a="426872760"
Received: from ls.sc.intel.com (HELO localhost) ([143.183.96.54])
  by orsmga008-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 20 Apr 2021 03:41:43 -0700
From: Isaku Yamahata <isaku.yamahata@intel.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>
Cc: isaku.yamahata@gmail.com, Isaku Yamahata <isaku.yamahata@intel.com>
Subject: [RFC PATCH 01/10] KVM: x86/mmu: make kvm_mmu_do_page_fault() receive
 single argument
Date: Tue, 20 Apr 2021 03:39:11 -0700
Message-Id: 
 <0148ecd4045e672a28e32ba0e07a787d39ed1bbd.1618914692.git.isaku.yamahata@intel.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <cover.1618914692.git.isaku.yamahata@intel.com>
References: <cover.1618914692.git.isaku.yamahata@intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Introduce struct kvm_page_fault handler and its initialization function.
Make the caller of kvm page fault handler allocate/initialize
struct kvm_page_fault, and pass it to kvm_mmu_do_page_fault() instead
of many arguments.

No functional change is intended.

Signed-off-by: Isaku Yamahata <isaku.yamahata@intel.com>
---
 arch/x86/kvm/mmu.h     | 29 ++++++++++++++++++++++++-----
 arch/x86/kvm/mmu/mmu.c |  6 ++++--
 arch/x86/kvm/x86.c     |  4 +++-
 3 files changed, 31 insertions(+), 8 deletions(-)

```
#### [PATCH net] vsock/virtio: free queued packets when closing socket
##### From: Stefano Garzarella <sgarzare@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stefano Garzarella <sgarzare@redhat.com>
X-Patchwork-Id: 12213761
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 8D763C433B4
	for <kvm@archiver.kernel.org>; Tue, 20 Apr 2021 11:07:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 546FF61363
	for <kvm@archiver.kernel.org>; Tue, 20 Apr 2021 11:07:48 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231745AbhDTLIR (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 20 Apr 2021 07:08:17 -0400
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:27873 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S231785AbhDTLIK (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 20 Apr 2021 07:08:10 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1618916858;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=1FXQjKbNaNL0tsKFqOzmlYeQlOg2nURcqX1NM0c2SiM=;
        b=JwUCHlqiNkBsq+jcZM4jFJxG39pc0+5vbZiDZrGKpdL0L+viIA8uXjQq/bdpDgcF8o7nFq
        JHmojww/UgGDiE/I0PDvx37t0IvdBcHbxV3Txa8+rkNhzVaCX6LCcH29ZgTgTs2xho9O98
        rULovxZ04xWi/vPbgGpnl1sTy7tfCtc=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-396-x_2yPielOtq0wODMkkYNBA-1; Tue, 20 Apr 2021 07:07:35 -0400
X-MC-Unique: x_2yPielOtq0wODMkkYNBA-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 0B7028189D2;
        Tue, 20 Apr 2021 11:07:34 +0000 (UTC)
Received: from steredhat.redhat.com (ovpn-113-240.ams2.redhat.com
 [10.36.113.240])
        by smtp.corp.redhat.com (Postfix) with ESMTP id E3BA11002EF0;
        Tue, 20 Apr 2021 11:07:28 +0000 (UTC)
From: Stefano Garzarella <sgarzare@redhat.com>
To: netdev@vger.kernel.org
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        virtualization@lists.linux-foundation.org,
        "David S. Miller" <davem@davemloft.net>,
        Jakub Kicinski <kuba@kernel.org>,
        Stefano Garzarella <sgarzare@redhat.com>,
        Stefan Hajnoczi <stefanha@redhat.com>
Subject: [PATCH net] vsock/virtio: free queued packets when closing socket
Date: Tue, 20 Apr 2021 13:07:27 +0200
Message-Id: <20210420110727.139945-1-sgarzare@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

As reported by syzbot [1], there is a memory leak while closing the
socket. We partially solved this issue with commit ac03046ece2b
("vsock/virtio: free packets during the socket release"), but we
forgot to drain the RX queue when the socket is definitely closed by
the scheduled work.

To avoid future issues, let's use the new virtio_transport_remove_sock()
to drain the RX queue before removing the socket from the af_vsock lists
calling vsock_remove_sock().

[1] https://syzkaller.appspot.com/bug?extid=24452624fc4c571eedd9

Fixes: ac03046ece2b ("vsock/virtio: free packets during the socket release")
Reported-and-tested-by: syzbot+24452624fc4c571eedd9@syzkaller.appspotmail.com
Signed-off-by: Stefano Garzarella <sgarzare@redhat.com>
---
 net/vmw_vsock/virtio_transport_common.c | 28 +++++++++++++++++--------
 1 file changed, 19 insertions(+), 9 deletions(-)

```
#### 
##### 

```c
```
