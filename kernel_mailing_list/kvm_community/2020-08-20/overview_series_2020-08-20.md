#### [PATCH v2 41/58] kvm: Move QOM macros to kvm.h
##### From: Eduardo Habkost <ehabkost@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eduardo Habkost <ehabkost@redhat.com>
X-Patchwork-Id: 11725199
Return-Path: <SRS0=1nBL=B6=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B6025109B
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 20 Aug 2020 00:14:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9EDF7214F1
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 20 Aug 2020 00:14:26 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="L9r7TOfS"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728670AbgHTAOZ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 19 Aug 2020 20:14:25 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:31570 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728082AbgHTAOU (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 19 Aug 2020 20:14:20 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1597882459;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=7EkdIlxETPfIAzHkOFinRG+mYgIs7T56rbnwrgrdbzk=;
        b=L9r7TOfSa7U0D/tivPefChBdu2DFSo6+gohnUZjsweNmlqXfE/9HIrBSnsGcykgEIzg5xM
        knlYuObxOY5+qK43V+8UW0E1CRWagHbmMRhbiaNbH3a33754LzQig0zE7/Jqx6zb1XC4Gm
        u3xscLURMDVVa0KoqP8q5scC7Gi3a30=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-251-P48DF9CMNx281CAIqhZFHA-1; Wed, 19 Aug 2020 20:14:17 -0400
X-MC-Unique: P48DF9CMNx281CAIqhZFHA-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id ADC0B8030A4;
        Thu, 20 Aug 2020 00:14:16 +0000 (UTC)
Received: from localhost (ovpn-117-244.rdu2.redhat.com [10.10.117.244])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 7549C757C0;
        Thu, 20 Aug 2020 00:14:16 +0000 (UTC)
From: Eduardo Habkost <ehabkost@redhat.com>
To: qemu-devel@nongnu.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        "Daniel P. Berrange" <berrange@redhat.com>, kvm@vger.kernel.org
Subject: [PATCH v2 41/58] kvm: Move QOM macros to kvm.h
Date: Wed, 19 Aug 2020 20:12:19 -0400
Message-Id: <20200820001236.1284548-42-ehabkost@redhat.com>
In-Reply-To: <20200820001236.1284548-1-ehabkost@redhat.com>
References: <20200820001236.1284548-1-ehabkost@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Move QOM macros close to the KVMState typedef.

This will make future conversion to OBJECT_DECLARE* easier.

Signed-off-by: Eduardo Habkost <ehabkost@redhat.com>
---
Changes series v1 -> v2: new patch in series v2

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org
Cc: qemu-devel@nongnu.org
---
 include/sysemu/kvm.h     | 6 ++++++
 include/sysemu/kvm_int.h | 5 -----
 2 files changed, 6 insertions(+), 5 deletions(-)

```
#### [PATCH 1/8] KVM: SVM: rename a variable in the svm_create_vcpu
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 11725947
Return-Path: <SRS0=1nBL=B6=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 52F2E14F6
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 20 Aug 2020 09:13:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 367272078D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 20 Aug 2020 09:13:56 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="OvSaWWD7"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726872AbgHTJNu (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 20 Aug 2020 05:13:50 -0400
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:51945 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726723AbgHTJNn (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 20 Aug 2020 05:13:43 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1597914822;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=ZcRR+zhuRSPQz3y/P4w6mA/wG4YpwsNTibjI7+ECMsI=;
        b=OvSaWWD7xj8YvzyQD0P7ebQwjDCMEyYNIEt9ACIt8F7mGqRbfAF7fJBe1UdCNh0gR4HEgq
        6DlXhrjOOzED9TVbA5cy700Bj9l3UjyuZg2CuIVEYhB4U8ih63hvALYy2gX9IAiWJiuNCK
        /N0aEBxDGzoXzJsebivZRsztlYBoWec=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-355-dQH393HBP0y4UCERGNaR3w-1; Thu, 20 Aug 2020 05:13:38 -0400
X-MC-Unique: dQH393HBP0y4UCERGNaR3w-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id EC759801A9E;
        Thu, 20 Aug 2020 09:13:36 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.206.173])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 257C1747B0;
        Thu, 20 Aug 2020 09:13:32 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: Jim Mattson <jmattson@google.com>, Joerg Roedel <joro@8bytes.org>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Borislav Petkov <bp@alien8.de>,
        Thomas Gleixner <tglx@linutronix.de>,
        "H. Peter Anvin" <hpa@zytor.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        linux-kernel@vger.kernel.org (open list:X86 ARCHITECTURE (32-BIT AND
        64-BIT)),
        x86@kernel.org (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT)),
        Ingo Molnar <mingo@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH 1/8] KVM: SVM: rename a variable in the svm_create_vcpu
Date: Thu, 20 Aug 2020 12:13:20 +0300
Message-Id: <20200820091327.197807-2-mlevitsk@redhat.com>
In-Reply-To: <20200820091327.197807-1-mlevitsk@redhat.com>
References: <20200820091327.197807-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The 'page' is to hold the vcpu's vmcb so name it as such to
avoid confusion.

Signed-off-by: Maxim Levitsky <mlevitsk@redhat.com>
---
 arch/x86/kvm/svm/svm.c | 12 ++++++------
 1 file changed, 6 insertions(+), 6 deletions(-)

```
#### [PATCH v2 1/7] KVM: SVM: rename a variable in the svm_create_vcpu
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 11726311
Return-Path: <SRS0=1nBL=B6=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CD75F618
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 20 Aug 2020 13:34:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B575422CAE
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 20 Aug 2020 13:34:02 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="XdNkq5Vq"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729089AbgHTNeA (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 20 Aug 2020 09:34:00 -0400
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:37916 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1729599AbgHTNdy (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 20 Aug 2020 09:33:54 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1597930433;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=ZcRR+zhuRSPQz3y/P4w6mA/wG4YpwsNTibjI7+ECMsI=;
        b=XdNkq5VqQDVCYwCNGxNGzOTpi2uGtfx/HLAmePtf4F3NQLFD3CLYf1X3RasRusOPcxAVgE
        6oR3p3g512U+mE1k1caylfPEQ5NToUOoIK75rzY7xPMeC/b/HxKT/rYdyOnZxdwFgyVwbx
        uP+Q8NQ5hlwx8CPY5FnbpROFqFWx+YU=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-294-6L8uOrMdMvGGcxaphrCzKw-1; Thu, 20 Aug 2020 09:33:49 -0400
X-MC-Unique: 6L8uOrMdMvGGcxaphrCzKw-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id B2652106C0FF;
        Thu, 20 Aug 2020 13:33:47 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.206.173])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 20BA716E25;
        Thu, 20 Aug 2020 13:33:43 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: x86@kernel.org (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT)),
        Jim Mattson <jmattson@google.com>,
        Ingo Molnar <mingo@redhat.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        linux-kernel@vger.kernel.org (open list:X86 ARCHITECTURE (32-BIT AND
        64-BIT)), "H. Peter Anvin" <hpa@zytor.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Joerg Roedel <joro@8bytes.org>,
        Wanpeng Li <wanpengli@tencent.com>,
        Borislav Petkov <bp@alien8.de>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH v2 1/7] KVM: SVM: rename a variable in the svm_create_vcpu
Date: Thu, 20 Aug 2020 16:33:33 +0300
Message-Id: <20200820133339.372823-2-mlevitsk@redhat.com>
In-Reply-To: <20200820133339.372823-1-mlevitsk@redhat.com>
References: <20200820133339.372823-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The 'page' is to hold the vcpu's vmcb so name it as such to
avoid confusion.

Signed-off-by: Maxim Levitsky <mlevitsk@redhat.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 arch/x86/kvm/svm/svm.c | 12 ++++++------
 1 file changed, 6 insertions(+), 6 deletions(-)

```
#### [PATCH v2] KVM: nVMX: Update VMCS02 when L2 PAE PDPTE updates detected
##### From: Peter Shier <pshier@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Shier <pshier@google.com>
X-Patchwork-Id: 11727175
Return-Path: <SRS0=1nBL=B6=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AE35D13A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 20 Aug 2020 23:06:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8820E207DF
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 20 Aug 2020 23:06:42 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=google.com header.i=@google.com header.b="ZVw4lRp2"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728586AbgHTXGk (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 20 Aug 2020 19:06:40 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:42240 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728368AbgHTXGi (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 20 Aug 2020 19:06:38 -0400
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id C6BD4C061385
        for <kvm@vger.kernel.org>; Thu, 20 Aug 2020 16:06:37 -0700 (PDT)
Received: by mail-yb1-xb49.google.com with SMTP id n19so195636ybf.0
        for <kvm@vger.kernel.org>; Thu, 20 Aug 2020 16:06:37 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:message-id:mime-version:subject:from:to:cc;
        bh=TsA9eo6gus4tmwAOJeW6cMJwIWxsbvKQsdWBenQmfc8=;
        b=ZVw4lRp2WPxpzwrLYPQ0zYWa9MejRcHXz4yw3Ny9ZuSw2wukA594d5J9LRW73sepsz
         soyDdk+y5dHIFTka/pZCRhDk9DFitmVjpX8BnWSoMKwtntf5I5/LOV2FCUGBs4PzBcad
         AGO86s3IonSfEkvL5qbfuMIJVh5z5RHNeQzAI80W/glhMzSYOLe5HPezJt52iNL30QUR
         0gacfFjg7ElRimXFb+3FzQGdxcRCk3yEA0Zd8z6WfEhrFCmu1q1ObKTZ/BO10RV0bV7b
         1l9ig1ZybvI6DJLVCehieMUoEjJvgzG5t7Ki0Mug03OwdvaimRYon7iTd1/DKGDNfKSl
         //+g==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:message-id:mime-version:subject:from
         :to:cc;
        bh=TsA9eo6gus4tmwAOJeW6cMJwIWxsbvKQsdWBenQmfc8=;
        b=QMjPeTow1wMUIhW44DLnpiypwVfcaDYGnsMawhxcssLLQ221KaPQN4ovzDTAkaxdXD
         iaQM63/GQvQV/4fMebLy4G1rKBTsHWTy3hOLAZvr3xhWsXbga6A7KDMgI2FfpLztLfJm
         08SK8yZHCDfNRatO5Pv7m90ZRd50dD0AcmHwpg7s7ydTQ2kDa5zXqJpOIlAxXEtNRFop
         yUlWtFuDo4dD6z+m8M5MUKezYdOhgFhhGh3LLBfSjZoeQuYK/EGVC4C1sj4pyC4vuCXD
         VT5PzfkuWOuSMUlpR5dtBqZpvRfJn4kErtNE1RwhBFWawyI7e+/KhAS/iobucCjcRyDb
         QktQ==
X-Gm-Message-State: AOAM531A/ZXkXMAfmck76eJLy/K3Y4w+ZfzfrRMoXwn5aMsCEPbjZYCX
        qG5T3esr7QzWmPZuGp5JfZ1QfKY5kXGtUwyNsQBNqS3OT2L3GvZsYOL5BVTJSltsnLQpzKlTdDo
        FbmYu4wCRO1J4cvjUfbJldF2f1qICJYG6pG8pyl4cy4KxCqsRqO1cLaKQQw==
X-Google-Smtp-Source: 
 ABdhPJxApaoxhQoGQMNnAMKhy7xJ6k4Mc68ZmUsGWnOwK2JJ4w7jNisP4PMnNLJ09HJpamsMsjMnsd8cb8g=
X-Received: from pshier-linuxworkstation.sea.corp.google.com
 ([2620:15c:100:202:a28c:fdff:fee1:c360]) (user=pshier job=sendgmr) by
 2002:a25:d486:: with SMTP id m128mr121838ybf.188.1597964796987; Thu, 20 Aug
 2020 16:06:36 -0700 (PDT)
Date: Thu, 20 Aug 2020 16:05:45 -0700
Message-Id: <20200820230545.2411347-1-pshier@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.28.0.297.g1956fa8f8d-goog
Subject: [PATCH v2] KVM: nVMX: Update VMCS02 when L2 PAE PDPTE updates
 detected
From: Peter Shier <pshier@google.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, Peter Shier <pshier@google.com>,
        Jim Mattson <jmattson@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When L2 uses PAE, L0 intercepts of L2 writes to CR0/CR3/CR4 call
load_pdptrs to read the possibly updated PDPTEs from the guest
physical address referenced by CR3.  It loads them into
vcpu->arch.walk_mmu->pdptrs and sets VCPU_EXREG_PDPTR in
vcpu->arch.regs_dirty.

At the subsequent assumed reentry into L2, the mmu will call
vmx_load_mmu_pgd which calls ept_load_pdptrs. ept_load_pdptrs sees
VCPU_EXREG_PDPTR set in vcpu->arch.regs_dirty and loads
VMCS02.GUEST_PDPTRn from vcpu->arch.walk_mmu->pdptrs[]. This all works
if the L2 CRn write intercept always resumes L2.

The resume path calls vmx_check_nested_events which checks for
exceptions, MTF, and expired VMX preemption timers. If
vmx_check_nested_events finds any of these conditions pending it will
reflect the corresponding exit into L1. Live migration at this point
would also cause a missed immediate reentry into L2.

After L1 exits, vmx_vcpu_run calls vmx_register_cache_reset which
clears VCPU_EXREG_PDPTR in vcpu->arch.regs_dirty.  When L2 next
resumes, ept_load_pdptrs finds VCPU_EXREG_PDPTR clear in
vcpu->arch.regs_dirty and does not load VMCS02.GUEST_PDPTRn from
vcpu->arch.walk_mmu->pdptrs[]. prepare_vmcs02 will then load
VMCS02.GUEST_PDPTRn from vmcs12->pdptr0/1/2/3 which contain the stale
values stored at last L2 exit. A repro of this bug showed L2 entering
triple fault immediately due to the bad VMCS02.GUEST_PDPTRn values.

When L2 is in PAE paging mode add a call to ept_load_pdptrs before
leaving L2. This will update VMCS02.GUEST_PDPTRn if they are dirty in
vcpu->arch.walk_mmu->pdptrs[].

Tested:
kvm-unit-tests with new directed test: vmx_mtf_pdpte_test.
Verified that test fails without the fix.

Also ran Google internal VMM with an Ubuntu 16.04 4.4.0-83 guest running a
custom hypervisor with a 32-bit Windows XP L2 guest using PAE. Prior to fix
would repro readily. Ran 14 simultaneous L2s for 140 iterations with no
failures.

Signed-off-by: Peter Shier <pshier@google.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
v1 -> v2:

* Per Sean's suggestion removed the new x86 op and calling ept_load_pdptrs from
  nested_vmx_vmexit

 arch/x86/kvm/vmx/nested.c | 7 +++++++
 arch/x86/kvm/vmx/vmx.c    | 4 ++--
 arch/x86/kvm/vmx/vmx.h    | 1 +
 3 files changed, 10 insertions(+), 2 deletions(-)

```
