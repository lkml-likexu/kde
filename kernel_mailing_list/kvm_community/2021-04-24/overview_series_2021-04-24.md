#### [GIT PULL] KVM fix for 5.12 final
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 12222539
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-20.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,INCLUDES_PULL_REQUEST,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,
	SPF_HELO_NONE,SPF_PASS autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 42F71C433ED
	for <kvm@archiver.kernel.org>; Sat, 24 Apr 2021 08:26:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 16A1F6137D
	for <kvm@archiver.kernel.org>; Sat, 24 Apr 2021 08:26:58 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233770AbhDXI0k (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sat, 24 Apr 2021 04:26:40 -0400
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:48541 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S233104AbhDXIZN (ORCPT
        <rfc822;kvm@vger.kernel.org>); Sat, 24 Apr 2021 04:25:13 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1619252641;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=JG5lz1zucN+SOqKs9Q0DF5YgOmDD8WYIPbDEuaJ2ii4=;
        b=bK9sRkrwrQw+ab3PI3IwOchfeVMuTox5T+OhPx/Ks4XHSMTy5UR/GVH2FUXvZc75G9XYsE
        GPpBgUE+eLZS9zoeysdS0ybkTrVmEHB3zoVIaugesqCqleuNjNcow4S5qI+LVVZJdCT4jZ
        JsoFF3wWIZk9xTKfL/K86uec6D2t7tk=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-192-7EKwWYWbO6GMl3EdSzzoag-1; Sat, 24 Apr 2021 04:21:12 -0400
X-MC-Unique: 7EKwWYWbO6GMl3EdSzzoag-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 4C061343A2;
        Sat, 24 Apr 2021 08:21:11 +0000 (UTC)
Received: from virtlab511.virt.lab.eng.bos.redhat.com
 (virtlab511.virt.lab.eng.bos.redhat.com [10.19.152.198])
        by smtp.corp.redhat.com (Postfix) with ESMTP id F0DC55D6DC;
        Sat, 24 Apr 2021 08:21:10 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: torvalds@linux-foundation.org
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [GIT PULL] KVM fix for 5.12 final
Date: Sat, 24 Apr 2021 04:21:10 -0400
Message-Id: <20210424082110.1773621-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Linus,

The following changes since commit bf05bf16c76bb44ab5156223e1e58e26dfe30a88:

  Linux 5.12-rc8 (2021-04-18 14:45:32 -0700)

are available in the Git repository at:

  https://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to 9c1a07442c95f6e64dc8de099e9f35ea73db7852:

  KVM: x86/xen: Take srcu lock when accessing kvm_memslots() (2021-04-23 17:00:50 -0400)

----------------------------------------------------------------
SRCU bug introduced in the merge window

----------------------------------------------------------------
Wanpeng Li (1):
      KVM: x86/xen: Take srcu lock when accessing kvm_memslots()

 arch/x86/kvm/x86.c | 20 +++++++++-----------
 1 file changed, 9 insertions(+), 11 deletions(-)
```
#### [PATCH 01/43] KVM: nVMX: Set LDTR to its architecturally defined value on nested VM-Exit
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12222111
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A66B8C433B4
	for <kvm@archiver.kernel.org>; Sat, 24 Apr 2021 00:47:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7EE6C61465
	for <kvm@archiver.kernel.org>; Sat, 24 Apr 2021 00:47:11 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S243974AbhDXAro (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 23 Apr 2021 20:47:44 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:36716 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S237240AbhDXArl (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 23 Apr 2021 20:47:41 -0400
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id CA75DC06174A
        for <kvm@vger.kernel.org>; Fri, 23 Apr 2021 17:47:02 -0700 (PDT)
Received: by mail-yb1-xb4a.google.com with SMTP id
 u73-20020a25ab4f0000b0290410f38a2f81so26212013ybi.22
        for <kvm@vger.kernel.org>; Fri, 23 Apr 2021 17:47:02 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=reply-to:date:in-reply-to:message-id:mime-version:references
         :subject:from:to:cc;
        bh=RHGsqWwH1zxHj0xIe8K4VtoI6F8/53X2i4hvFea/Jtc=;
        b=OPjwaJ3YTXeq24If+8hQOW0VyJ+bADxa0ZRW5sPafB80mG4gzK4fam3t9CjRIQWl7T
         wGw7HJd4vszwt8ioG7VoGFwsLhoabf0qd/kaDt6vxb6365MyOLPhCdgvplw3BaMQ2qs8
         No6dsSgvzPfQcYF09OgMhnG4ahp0tp7RHLuXXmJ8jKSi2UmICvWZbzP2d/nJLz71SmY9
         lWxco2nnDLF9nUs8asjapZgxqWC9N3Z/d9gP+9Gmrj6EzMj0uHmP/G6vRkJPYNyoVxgz
         5l+Kvb6xbV4lSKxLTbI/+68iCD6p8msMn5HQemfW0SzONRC/SXhKoPbgtQYkTQWLFvJy
         O2cw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:reply-to:date:in-reply-to:message-id
         :mime-version:references:subject:from:to:cc;
        bh=RHGsqWwH1zxHj0xIe8K4VtoI6F8/53X2i4hvFea/Jtc=;
        b=e981HZOg+yUbP0igHDM0VB5yqwq09laBsbPb9w5yUmFc5M4P/yOW4hfMpe+/t8Gb9s
         eF8R8/K6yDmI41jqTZUA4vbBywBIR9Vx+tcil5joRag42cZLFjl1JcUot51wz957veEY
         01BxgasFmoSny4Wn3autnO+mb/AgiVm1LAhcNPp5n72f46gUQlRXBm0qKT8YMbzQkHTG
         M58sGb4hvZp0evcpIQmHc0jIYoDJgs+WRjQ3/I/JAQvawgOq8e2PFxZQwZJnMYsBkRo+
         TQx0iRrn0vGem/FBGcdZKXWMjVV1D8Mi8NmDEOkGfJAfa+oNe1j/8RaDVT4zUQFewEDx
         4xZg==
X-Gm-Message-State: AOAM532YKPYyCdCq5pOH9GXbfF72XpaaoJLgF+FWpj0YOj3QnPC0H77x
        /LyfyvMn0C6JBdQ8hHpnYra3+o01xaU=
X-Google-Smtp-Source: 
 ABdhPJzX+waosmfrUN513JsYHxpFuDWHWvyn4N/ji2D0vC9EQhyeKOU7/v4bDJ04Jc3LfwehTPEuiQqvW2Q=
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:ad52:3246:e190:f070])
 (user=seanjc job=sendgmr) by 2002:a25:ac9b:: with SMTP id
 x27mr8963271ybi.120.1619225222104;
 Fri, 23 Apr 2021 17:47:02 -0700 (PDT)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Fri, 23 Apr 2021 17:46:03 -0700
In-Reply-To: <20210424004645.3950558-1-seanjc@google.com>
Message-Id: <20210424004645.3950558-2-seanjc@google.com>
Mime-Version: 1.0
References: <20210424004645.3950558-1-seanjc@google.com>
X-Mailer: git-send-email 2.31.1.498.g6c1eba8ee3d-goog
Subject: [PATCH 01/43] KVM: nVMX: Set LDTR to its architecturally defined
 value on nested VM-Exit
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Set L1's LDTR on VM-Exit per the Intel SDM:

  The host-state area does not contain a selector field for LDTR. LDTR is
  established as follows on all VM exits: the selector is cleared to
  0000H, the segment is marked unusable and is otherwise undefined
  (although the base address is always canonical).

This is likely a benign bug since the LDTR is unusable, as it means the
L1 VMM is conditioned to reload its LDTR in order to function properly on
bare metal.

Fixes: 4704d0befb07 ("KVM: nVMX: Exiting from L2 to L1")
Signed-off-by: Sean Christopherson <seanjc@google.com>
---
 arch/x86/kvm/vmx/nested.c | 4 ++++
 1 file changed, 4 insertions(+)

```
