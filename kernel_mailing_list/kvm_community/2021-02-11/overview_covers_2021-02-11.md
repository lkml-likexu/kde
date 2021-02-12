

#### [PATCH 0/3] AMD invpcid exception fix
##### From: Bandan Das <bsd@redhat.com>

```c
From patchwork Thu Feb 11 21:22:36 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Bandan Das <bsd@redhat.com>
X-Patchwork-Id: 12084183
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.3 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id BA827C433E0
	for <kvm@archiver.kernel.org>; Thu, 11 Feb 2021 21:25:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 71CF264E42
	for <kvm@archiver.kernel.org>; Thu, 11 Feb 2021 21:25:09 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229803AbhBKVZI (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 11 Feb 2021 16:25:08 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:21675 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S229626AbhBKVZG (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 11 Feb 2021 16:25:06 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1613078618;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=HQD4b05vmCkFCNkT5YGv47RFnOOYPkLtMqdC6jU6IdY=;
        b=PO+0E7C/FR8BNwpI1mWk5s+UwyAhJFG00kLwEvhKA8e80mMpMWpBqRACa5fHQ6yFfb9mX4
        inve5Zdpjr9I2plIc6O/3Ld0p5gJgHouQGl59jU0N/ZoSvDEsj/2a/a4ukTGJfUSteUCUf
        alE4azQ7+svrxb2XiAVqKBJn/SaJ+XI=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-171-lyd8M8z4OPWyiyMt-qITJQ-1; Thu, 11 Feb 2021 16:23:35 -0500
X-MC-Unique: lyd8M8z4OPWyiyMt-qITJQ-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 02475803F60;
        Thu, 11 Feb 2021 21:23:33 +0000 (UTC)
Received: from gigantic.usersys.redhat.com (helium.bos.redhat.com
 [10.18.17.132])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 7A61E60C9A;
        Thu, 11 Feb 2021 21:23:32 +0000 (UTC)
From: Bandan Das <bsd@redhat.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com, wei.huang2@amd.com,
        babu.moger@amd.com
Subject: [PATCH 0/3] AMD invpcid exception fix
Date: Thu, 11 Feb 2021 16:22:36 -0500
Message-Id: <20210211212241.3958897-1-bsd@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The pcid-disabled test from kvm-unit-tests fails on a Milan host because the
processor injects a #GP while the test expects #UD. While setting the intercept
when the guest has it disabled seemed like the obvious thing to do, Babu Moger (AMD)
pointed me to an earlier discussion here - https://lkml.org/lkml/2020/6/11/949

Jim points out there that  #GP has precedence over the intercept bit when invpcid is
called with CPL > 0 and so even if we intercept invpcid, the guest would end up with getting
and "incorrect" exception. To inject the right exception, I created an entry for the instruction
in the emulator to decode it successfully and then inject a UD instead of a GP when
the guest has it disabled.

Bandan Das (3):
  KVM: Add a stub for invpcid in the emulator table
  KVM: SVM: Handle invpcid during gp interception
  KVM: SVM:  check if we need to track GP intercept for invpcid

 arch/x86/kvm/emulate.c |  3 ++-
 arch/x86/kvm/svm/svm.c | 22 +++++++++++++++++++++-
 2 files changed, 23 insertions(+), 2 deletions(-)
```
