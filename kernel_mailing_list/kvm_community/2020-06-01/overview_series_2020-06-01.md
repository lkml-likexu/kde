#### [PATCH v3 1/4] kvm: svm: Prefer vcpu->cpu to raw_smp_processor_id()From: Jim Mattson <jmattson@google.com>
##### From: Jim Mattson <jmattson@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jim Mattson <jmattson@google.com>
X-Patchwork-Id: 11582765
Return-Path: <SRS0=ZHpL=7O=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 22E3D912
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  1 Jun 2020 22:24:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0B8372076B
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  1 Jun 2020 22:24:41 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="D4EjhKlj"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728779AbgFAWYk (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 1 Jun 2020 18:24:40 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:50756 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728216AbgFAWYj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 1 Jun 2020 18:24:39 -0400
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 838E1C061A0E
        for <kvm@vger.kernel.org>; Mon,  1 Jun 2020 15:24:38 -0700 (PDT)
Received: by mail-yb1-xb49.google.com with SMTP id h129so14284840ybc.3
        for <kvm@vger.kernel.org>; Mon, 01 Jun 2020 15:24:38 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=8LGvgjxPtHovpdfipQl4OzIV0OZgS4Psratbe52QpYI=;
        b=D4EjhKljo66zAmzcE74W2Z6+2+uQP/r15aP1E7YXkTeFsGejV8IN0LAr9ks2Qn79iS
         58Oifvol/eu8k2vKR5YcmX6vx1a5USb1rNTyTO/ksTT4mPKBMe3nhgyHhja5+N2l+GPq
         CaEidxMPzHumpImm8hDSYEGEZeIFeECfLLVks0kGFgYaTi77floy5w0pYpm17enssPbG
         sixq+sMRjGZg37jQ779JWmWp2uSIGea1GYj74IIdPQHxggRkLDdqP3GaHnhiFmP8Cj7e
         c+KpmDrMzyiMccxo3Jp7VuToIQDAeLo+KMGKs45qkO+dvgUvWAfoHEZ5d5H4x+WyvOcY
         2wJw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=8LGvgjxPtHovpdfipQl4OzIV0OZgS4Psratbe52QpYI=;
        b=HZTLlzWVlYOvkN0dgaEwtmOjsJdF+ujzrOhTXfKUHkSjevUEAs002Dms9xTvEBKPQv
         htmfJGOxdWAzjXa3zZCFRDjmQP2jOqxncRaUbm/kC+Fxf0CgpCg1QPYsZTjGWDvkBn2r
         kRc5227BeQT75rPpXZFQrnEUmSHfQLNDsoERcnXlX7c60J4gjuBii9PqvQ6t/VhwEwvC
         y9OBDBg6pvQ5DcTSMNf6FJimZK72blC6QRm7IDTWP6fF801UdrBrKFePPEZP7ydLF7m/
         uqf3rbV5QoChEjnU8csIJ91fNaubf9Tk3HaRmuyY+UZPWhlgfpQINXX/PHCv8CDjZLIL
         tNgQ==
X-Gm-Message-State: AOAM5332kdU6rG15SGLR6cpdINnErwgwm2tRu2tyXWV8Uq/NC/xunib8
        qN7LKcpHgWnhAXBh3WnqU6tAve7IfQv5xmGDGrX2MBZpzMaZ8wJB8hVwJVEZDEtRO8A/ghV82eG
        NJuYHtr9Igxuyj312d+Kfa5aWhWWGohcURVXJDAdvniC16Jlw7EpCzPck2CrL98c=
X-Google-Smtp-Source: 
 ABdhPJwDJsoqPna/zuF6W+qLXYqSsCNqtDOzJxdnOsvSqE35jPUb+ipOCIUXYKgn+PgPdxRyFeEsRHZU237UGA==
X-Received: by 2002:a25:ab4a:: with SMTP id
 u68mr13912680ybi.271.1591050277722;
 Mon, 01 Jun 2020 15:24:37 -0700 (PDT)
Date: Mon,  1 Jun 2020 15:24:13 -0700
In-Reply-To: <20200601222416.71303-1-jmattson@google.com>
Message-Id: <20200601222416.71303-2-jmattson@google.com>
Mime-Version: 1.0
References: <20200601222416.71303-1-jmattson@google.com>
X-Mailer: git-send-email 2.27.0.rc2.251.g90737beb825-goog
Subject: [PATCH v3 1/4] kvm: svm: Prefer vcpu->cpu to raw_smp_processor_id()
From: Jim Mattson <jmattson@google.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Liran Alon <liran.alon@oracle.com>,
        Oliver Upton <oupton@google.com>,
        Peter Shier <pshier@google.com>,
        Jim Mattson <jmattson@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The current logical processor id is cached in vcpu->cpu. Use it
instead of raw_smp_processor_id() when a kvm_vcpu struct is available.

Signed-off-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Oliver Upton <oupton@google.com>
---
 arch/x86/kvm/svm/svm.c | 9 +++------
 1 file changed, 3 insertions(+), 6 deletions(-)

```
#### [PATCH] KVM: check userspace_addr for all memslots
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11581719
Return-Path: <SRS0=ZHpL=7O=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 70E2E1391
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  1 Jun 2020 08:21:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4B8EE2076B
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  1 Jun 2020 08:21:56 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="SFDKu3m9"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728146AbgFAIVv (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 1 Jun 2020 04:21:51 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:23791 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726142AbgFAIVv (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 1 Jun 2020 04:21:51 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1590999710;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=59Xri5z2WaS+00aj02VDCABWd90XAuhG4yZyC959x+8=;
        b=SFDKu3m98Ql1gLMzpWZDfRJHDi3Q7npEWEM+oeqiYOREHFdhs4JbH1mYN8/qg4jsgKO9EQ
        VlAPYWss6ptrr9mO5GrNLKIj/Cy0nK5HFyt7PsvBmxQaUGEINelojJPaomzPPzDFvCaNub
        N+9bN8FyNTx3uwbHFx6QJsrvbwxRuAw=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-338-9bZyvJ5BMiGy1PQhamh2Lw-1; Mon, 01 Jun 2020 04:21:48 -0400
X-MC-Unique: 9bZyvJ5BMiGy1PQhamh2Lw-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 6B0048463A1;
        Mon,  1 Jun 2020 08:21:47 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 0709861985;
        Mon,  1 Jun 2020 08:21:46 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Linus Torvalds <torvalds@linux-foundation.org>
Subject: [PATCH] KVM: check userspace_addr for all memslots
Date: Mon,  1 Jun 2020 04:21:46 -0400
Message-Id: <20200601082146.18969-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The userspace_addr alignment and range checks are not performed for private
memory slots that are prepared by KVM itself.  This is unnecessary and makes
it questionable to use __*_user functions to access memory later on.  We also
rely on the userspace address being aligned since we have an entire family
of functions to map gfn to pfn.

Fortunately skipping the check is completely unnecessary.  Only x86 uses
private memslots and their userspace_addr is obtained from vm_mmap,
therefore it must be below PAGE_OFFSET.  In fact, any attempt to pass
an address above PAGE_OFFSET would have failed because such an address
would return true for kvm_is_error_hva.

Reported-by: Linus Torvalds <torvalds@linux-foundation.org>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 virt/kvm/kvm_main.c | 5 ++---
 1 file changed, 2 insertions(+), 3 deletions(-)

```
#### [PATCH v10 01/14] KVM: X86: Change parameter for fast_page_fault tracepoint
##### From: Peter Xu <peterx@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11581907
Return-Path: <SRS0=ZHpL=7O=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 99F04739
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  1 Jun 2020 12:00:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7F245207D5
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  1 Jun 2020 12:00:13 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="exF4SfdS"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726101AbgFAMAI (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 1 Jun 2020 08:00:08 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:48638 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1725978AbgFAMAH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 1 Jun 2020 08:00:07 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1591012805;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=Ble7s/BrlGwUPRHQ34ii4/VsZgKqdI5xssnXt1KNNb0=;
        b=exF4SfdSq8NUWQ83LTtCdVb9np64EW8+TEyiE3V8aOWFTJowp8bBHYLBm9KcW3Nttq9eYh
        y1o9Q/NOieGE5UivGK4UnjIR6jNzZWQhfrpDUb5QuDAOHUsoGuEkFfzPs2gwiXIMxF5kVg
        R9FSfKxBjK7Gd+F8LNs+kEffjwuT0WU=
Received: from mail-qv1-f72.google.com (mail-qv1-f72.google.com
 [209.85.219.72]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-141-EgGtZWuHON2LESpJQLAZJw-1; Mon, 01 Jun 2020 08:00:04 -0400
X-MC-Unique: EgGtZWuHON2LESpJQLAZJw-1
Received: by mail-qv1-f72.google.com with SMTP id h4so4336631qvr.21
        for <kvm@vger.kernel.org>; Mon, 01 Jun 2020 05:00:04 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=Ble7s/BrlGwUPRHQ34ii4/VsZgKqdI5xssnXt1KNNb0=;
        b=ryDcf3W/RO8j2PVgNU+fi2M85bbPafsaKpWmearz0G6fRqNI7dSyNrJsRxfArcmlhs
         Qy1HZvEH+S5wMpclSkD0YbLK9d1uYytrRxreHADvyvShGAIKfeLR229dNWqwZOnEzu0i
         WpPU2vUpOu+jKUVNoWRaVyW+ANWpCPFYS6b6xxGLExJKV11SNhwu4x4EYW6SLsbW0WJN
         lDt3J7+14eMVn1nfvI/UZRbCEKd23uW+vWfSRNXh2UwWPQ3/X5t35oj8YiyEAb3pUBv3
         z7vr+jxA1xdqzgP5eKaYoH5KPT2j9+KFHxz0NkYFxdy//ualBFEj7ByJU24jyQSoiA3H
         mTWQ==
X-Gm-Message-State: AOAM532LLGpCRB28BK0hbatreOYjsxS1zqObvIJRhZU6HaN/LyKVtUTH
        Gy0l9EdCCC7s7MvgvrR7haGzSqJoXiGoTBp1Oi+iiarpY1uCCDieHbl3uSa+YPUPgp10hxFgjb1
        K72pCYt3iojyu
X-Received: by 2002:a05:6214:1925:: with SMTP id
 es5mr6763770qvb.165.1591012803607;
        Mon, 01 Jun 2020 05:00:03 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJx1IzJyVR4DX6Bk9zy7p1HwJtJsrkQD4MdK4Y0U0kfd9WqtIBE8ch0XnsLCcU23iyKC/g0N/Q==
X-Received: by 2002:a05:6214:1925:: with SMTP id
 es5mr6763743qvb.165.1591012803378;
        Mon, 01 Jun 2020 05:00:03 -0700 (PDT)
Received: from xz-x1.redhat.com ([2607:9880:19c0:32::2])
        by smtp.gmail.com with ESMTPSA id
 l9sm14474185qki.90.2020.06.01.05.00.01
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 01 Jun 2020 05:00:02 -0700 (PDT)
From: Peter Xu <peterx@redhat.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: "Dr . David Alan Gilbert" <dgilbert@redhat.com>,
        Andrew Jones <drjones@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        "Michael S . Tsirkin" <mst@redhat.com>,
        Jason Wang <jasowang@redhat.com>, peterx@redhat.com,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Kevin Tian <kevin.tian@intel.com>
Subject: [PATCH v10 01/14] KVM: X86: Change parameter for fast_page_fault
 tracepoint
Date: Mon,  1 Jun 2020 07:59:44 -0400
Message-Id: <20200601115957.1581250-2-peterx@redhat.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20200601115957.1581250-1-peterx@redhat.com>
References: <20200601115957.1581250-1-peterx@redhat.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

It would be clearer to dump the return value to know easily on whether
did we go through the fast path for handling current page fault.
Remove the old two last parameters because after all the old/new sptes
were dumped in the same line.

Signed-off-by: Peter Xu <peterx@redhat.com>
---
 arch/x86/kvm/mmutrace.h | 9 ++-------
 1 file changed, 2 insertions(+), 7 deletions(-)

```
#### [PATCH] KVM: selftests: fix rdtsc() for vmx_tsc_adjust_test
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11582343
Return-Path: <SRS0=ZHpL=7O=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 872B91391
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  1 Jun 2020 15:47:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6F0F8207D5
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  1 Jun 2020 15:47:35 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="G3nJ86NC"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727826AbgFAPre (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 1 Jun 2020 11:47:34 -0400
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:58905 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726075AbgFAPre (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 1 Jun 2020 11:47:34 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1591026452;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=3CnZZGZdEnXK3gksb+xJ+ZM+qYctQV1EojEAwTVHULU=;
        b=G3nJ86NCEGD87yo1FCCcl5m5b9o+8EhVrWK1Uh3wMzlsF92JXiMp7VJw3UVrTOYf8s2MCb
        KCH3uqMBXbDEhCWHBdWUR5z3p76RxFuVTcQwNBcYW/nyoSawZVC9cp6f6jgOyyqQMRWthW
        W4folI/hVSs2wddggt44CmHVHApghjM=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-317-7Xci_c89NmSrIrh2KVb8sw-1; Mon, 01 Jun 2020 11:47:31 -0400
X-MC-Unique: 7Xci_c89NmSrIrh2KVb8sw-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id E0834108C303;
        Mon,  1 Jun 2020 15:47:29 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.195.152])
        by smtp.corp.redhat.com (Postfix) with ESMTP id BBF8410013D9;
        Mon,  1 Jun 2020 15:47:27 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Makarand Sonare <makarandsonare@google.com>
Subject: [PATCH] KVM: selftests: fix rdtsc() for vmx_tsc_adjust_test
Date: Mon,  1 Jun 2020 17:47:26 +0200
Message-Id: <20200601154726.261868-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

vmx_tsc_adjust_test fails with:

IA32_TSC_ADJUST is -4294969448 (-1 * TSC_ADJUST_VALUE + -2152).
IA32_TSC_ADJUST is -4294969448 (-1 * TSC_ADJUST_VALUE + -2152).
IA32_TSC_ADJUST is 281470681738540 (65534 * TSC_ADJUST_VALUE + 4294962476).
==== Test Assertion Failure ====
  x86_64/vmx_tsc_adjust_test.c:153: false
  pid=19738 tid=19738 - Interrupted system call
     1	0x0000000000401192: main at vmx_tsc_adjust_test.c:153
     2	0x00007fe1ef8583d4: ?? ??:0
     3	0x0000000000401201: _start at ??:?
  Failed guest assert: (adjust <= max)

The problem is that is 'tsc_val' should be u64, not u32 or the reading
gets truncated.

Fixes: 8d7fbf01f9afc ("KVM: selftests: VMX preemption timer migration test")
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 tools/testing/selftests/kvm/include/x86_64/processor.h | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v2 1/2] docs: mm/gup: pin_user_pages.rst: add a "case 5"
##### From: John Hubbard <jhubbard@nvidia.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: John Hubbard <jhubbard@nvidia.com>
X-Patchwork-Id: 11581265
Return-Path: <SRS0=ZHpL=7O=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 006131391
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  1 Jun 2020 05:26:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DA81D206E2
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  1 Jun 2020 05:26:47 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=nvidia.com header.i=@nvidia.com
 header.b="qK1j9GFq"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726103AbgFAF0l (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 1 Jun 2020 01:26:41 -0400
Received: from hqnvemgate25.nvidia.com ([216.228.121.64]:13033 "EHLO
        hqnvemgate25.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726002AbgFAF0k (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 1 Jun 2020 01:26:40 -0400
Received: from hqpgpgate101.nvidia.com (Not Verified[216.228.121.13]) by
 hqnvemgate25.nvidia.com (using TLS: TLSv1.2, DES-CBC3-SHA)
        id <B5ed491390000>; Sun, 31 May 2020 22:25:13 -0700
Received: from hqmail.nvidia.com ([172.20.161.6])
  by hqpgpgate101.nvidia.com (PGP Universal service);
  Sun, 31 May 2020 22:26:39 -0700
X-PGP-Universal: processed;
        by hqpgpgate101.nvidia.com on Sun, 31 May 2020 22:26:39 -0700
Received: from HQMAIL105.nvidia.com (172.20.187.12) by HQMAIL101.nvidia.com
 (172.20.187.10) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Mon, 1 Jun
 2020 05:26:39 +0000
Received: from rnnvemgw01.nvidia.com (10.128.109.123) by HQMAIL105.nvidia.com
 (172.20.187.12) with Microsoft SMTP Server (TLS) id 15.0.1473.3 via Frontend
 Transport; Mon, 1 Jun 2020 05:26:38 +0000
Received: from sandstorm.nvidia.com (Not Verified[10.2.56.10]) by
 rnnvemgw01.nvidia.com with Trustwave SEG (v7,5,8,10121)
        id <B5ed4918d0001>; Sun, 31 May 2020 22:26:38 -0700
From: John Hubbard <jhubbard@nvidia.com>
To: Andrew Morton <akpm@linux-foundation.org>
CC: "Michael S . Tsirkin" <mst@redhat.com>, Jason Wang <jasowang@redhat.com>,
 Vlastimil Babka <vbabka@suse.cz>,
 =?utf-8?b?SsOpcsO0bWUgR2xpc3Nl?= <jglisse@redhat.com>,
 Jan Kara <jack@suse.cz>, Dave Chinner <david@fromorbit.com>,
 Souptick Joarder <jrdr.linux@gmail.com>, Jonathan Corbet <corbet@lwn.net>,
 <linux-doc@vger.kernel.org>, <linux-fsdevel@vger.kernel.org>,
 <kvm@vger.kernel.org>, <virtualization@lists.linux-foundation.org>,
 <netdev@vger.kernel.org>, LKML <linux-kernel@vger.kernel.org>,
 <linux-mm@kvack.org>, John Hubbard <jhubbard@nvidia.com>
Subject: [PATCH v2 1/2] docs: mm/gup: pin_user_pages.rst: add a "case 5"
Date: Sun, 31 May 2020 22:26:32 -0700
Message-ID: <20200601052633.853874-2-jhubbard@nvidia.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20200601052633.853874-1-jhubbard@nvidia.com>
References: <20200601052633.853874-1-jhubbard@nvidia.com>
MIME-Version: 1.0
X-NVConfidentiality: public
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1590989113; bh=t7FWcHHh76dL2ntq5uEZcJXrRdIPUbkPCP1hpf5ZyJs=;
        h=X-PGP-Universal:From:To:CC:Subject:Date:Message-ID:X-Mailer:
         In-Reply-To:References:MIME-Version:X-NVConfidentiality:
         Content-Type:Content-Transfer-Encoding;
        b=qK1j9GFqbfQmVpQy1H0RYKNlXRO1BkoJ29m7kmpMnNPQuUtvQfBwg2vMMsSvFveYZ
         B4RJF6yYzDWJPbA+0xaMNCl5pIiwE9zxqS3DmytXMMVogrqpR6QR5ifPBK/4OdqkAx
         5sQJ9sxAAQ3GrAOxexuMi6vvC13lWsy/ISJCnIhPlJoIMi/2csU1MFDnTggQ4T94oK
         Tod2zq/E8lTiWlfYGrPfl+Wiu7+lAkY4xGFHT6UWkLNH8s/BwSkflVnW/N7ALhfKyH
         hwASUzab4eDY3/262l16OFARt1OWnabnYoH3Ab53hs03ClSVHIf+sK0Fj9TGdPcb8l
         GptD7xNG4tqcw==
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

There are four cases listed in pin_user_pages.rst. These are
intended to help developers figure out whether to use
get_user_pages*(), or pin_user_pages*(). However, the four cases
do not cover all the situations. For example, drivers/vhost/vhost.c
has a "pin, write to page, set page dirty, unpin" case.

Add a fifth case, to help explain that there is a general pattern
that requires pin_user_pages*() API calls.

Cc: Vlastimil Babka <vbabka@suse.cz>
Cc: Jan Kara <jack@suse.cz>
Cc: Jérôme Glisse <jglisse@redhat.com>
Cc: Dave Chinner <david@fromorbit.com>
Cc: Jonathan Corbet <corbet@lwn.net>
Cc: linux-doc@vger.kernel.org
Cc: linux-fsdevel@vger.kernel.org
Signed-off-by: John Hubbard <jhubbard@nvidia.com>
Reviewed-by: Jan Kara <jack@suse.cz>
---
 Documentation/core-api/pin_user_pages.rst | 18 ++++++++++++++++++
 1 file changed, 18 insertions(+)

```
