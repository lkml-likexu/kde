#### [kvm-unit-tests PATCH] Fixes for the umip test
##### From: Thomas Huth <thuth@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Thomas Huth <thuth@redhat.com>
X-Patchwork-Id: 11346031
Return-Path: <SRS0=nF9W=3L=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 52FE7921
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 22 Jan 2020 16:09:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 314732071E
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 22 Jan 2020 16:09:59 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="OGsqUEjP"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726181AbgAVQJ6 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 22 Jan 2020 11:09:58 -0500
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:20289 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1725989AbgAVQJ5 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 22 Jan 2020 11:09:57 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1579709396;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=vG9YtgnEg9fUpGzN49dJA/kQOLEXuZAYvw61FY32mRA=;
        b=OGsqUEjPPO5C+cK6zaebBS7LT9O5tE3hdkSe3UyUL9BAKH6cgmN5XbR/TJvRlSU/zXQWy8
        +UpircdxkmQiXy8+1vP8HZiqEAJpAucVoC05hU9qdQ9lrq9bYpt4zjuVGeIIJsAArAqgwU
        3hWm9IM5ulnmm6qUq5iPyD7/O2FlaL0=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-185-ZeYO0t_aO8KbM9gYXKyjVg-1; Wed, 22 Jan 2020 11:09:52 -0500
X-MC-Unique: ZeYO0t_aO8KbM9gYXKyjVg-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id BCE81100550E
        for <kvm@vger.kernel.org>; Wed, 22 Jan 2020 16:09:51 +0000 (UTC)
Received: from thuth.com (ovpn-116-176.ams2.redhat.com [10.36.116.176])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 415CB9CA3;
        Wed, 22 Jan 2020 16:09:48 +0000 (UTC)
From: Thomas Huth <thuth@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: David Hildenbrand <david@redhat.com>,
        Drew Jones <drjones@redhat.com>
Subject: [kvm-unit-tests PATCH] Fixes for the umip test
Date: Wed, 22 Jan 2020 17:09:44 +0100
Message-Id: <20200122160944.29750-1-thuth@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When compiling umip.c with -O2 instead of -O1, there are currently
two problems. First, the compiler complains:

 x86/umip.c: In function ‘do_ring3’:
 x86/umip.c:162:37: error: array subscript 4096 is above array bounds of
    ‘unsigned char[4096]’ [-Werror=array-bounds]
       [user_stack_top]"m"(user_stack[sizeof user_stack]),
                           ~~~~~~~~~~^~~~~~~~~~~~~~~~~~~

This can be fixed by initializing the stack to point to one of the last
bytes of the array instead.

The second problem is that some tests are failing - and this is due
to the fact that the GP_ASM macro uses inline asm without the "volatile"
keyword - so that the compiler reorders this code in certain cases
where it should not. Fix it by adding "volatile" here.

Signed-off-by: Thomas Huth <thuth@redhat.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 x86/umip.c | 5 +++--
 1 file changed, 3 insertions(+), 2 deletions(-)

```
#### [kvm-unit-tests PATCH] Makefile: Compile the kvm-unit-tests with -fno-strict-aliasing
##### From: Thomas Huth <thuth@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Huth <thuth@redhat.com>
X-Patchwork-Id: 11345905
Return-Path: <SRS0=nF9W=3L=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3F3EC6C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 22 Jan 2020 15:23:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1D5B021835
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 22 Jan 2020 15:23:56 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="LJbZByBT"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725933AbgAVPXy (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 22 Jan 2020 10:23:54 -0500
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:44260 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1725802AbgAVPXy (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 22 Jan 2020 10:23:54 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1579706633;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc; bh=I2itWS0wOOp7E/+TSJmQdtjNsnsLCGY7CKG4AUVHbKI=;
        b=LJbZByBTgHQ8j5l+qP5u++HrZvZUhFoLCuh2oRAarWOoRAANymkEMLzsWoGMraE0gwGm0X
        0tHvKqCNWS4KBykm/AfGHW/424TM6QUKtnW0D7pwVRtt1DpuuCF7KCAuM0PnYf7EQOECRH
        0A2Kbu0gBnCDgacpX8XjfnCwWLq1g0k=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-145-LaBonfrhNkeL1UMsZ5v-nw-1; Wed, 22 Jan 2020 10:23:52 -0500
X-MC-Unique: LaBonfrhNkeL1UMsZ5v-nw-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 2E516800D55
        for <kvm@vger.kernel.org>; Wed, 22 Jan 2020 15:23:51 +0000 (UTC)
Received: from thuth.com (ovpn-116-176.ams2.redhat.com [10.36.116.176])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 0746386452;
        Wed, 22 Jan 2020 15:23:38 +0000 (UTC)
From: Thomas Huth <thuth@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: David Hildenbrand <david@redhat.com>,
        Laurent Vivier <lvivier@redhat.com>,
        Drew Jones <drjones@redhat.com>
Subject: [kvm-unit-tests PATCH] Makefile: Compile the kvm-unit-tests with
 -fno-strict-aliasing
Date: Wed, 22 Jan 2020 16:23:31 +0100
Message-Id: <20200122152331.14062-1-thuth@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Strict aliasing bugs are often hard to find and understand (when the compiler
did not omit a warning), and kvm-unit-tests are mainly written by kernel
developers who are used to compile their code with -fno-strict-aliasing. So
let's use this flag for the kvm-unit-tests, too.

Signed-off-by: Thomas Huth <thuth@redhat.com>
Acked-by: David Hildenbrand <david@redhat.com>
---
 Makefile | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH v2] x86: VMX: Check precondition for RDTSC testFrom: Oliver Upton <oupton@google.com>
##### From: Oliver Upton <oupton@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Oliver Upton <oupton@google.com>
X-Patchwork-Id: 11345425
Return-Path: <SRS0=nF9W=3L=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CB9F2924
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 22 Jan 2020 10:04:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A59662465A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 22 Jan 2020 10:04:02 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="XRmzJa+u"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729263AbgAVKEB (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 22 Jan 2020 05:04:01 -0500
Received: from mail-pl1-f202.google.com ([209.85.214.202]:42126 "EHLO
        mail-pl1-f202.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726204AbgAVKEB (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 22 Jan 2020 05:04:01 -0500
Received: by mail-pl1-f202.google.com with SMTP id b4so3236614plr.9
        for <kvm@vger.kernel.org>; Wed, 22 Jan 2020 02:04:01 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=WPWlBAFrYfOfqMEgSjQJiZF1KWEAEaOIklSy0CoEty4=;
        b=XRmzJa+u7iTLj4vDydOb/0VgZ2k7pIvxKNX21eeFetfNMwNyBjHbvsaUhXSVOb4jaj
         02V62CPs8nv84vAV+37mF1kdGd16b/A56MhcBZV0VrzGvN+f2T6ne61bSBo0n2wOSsnh
         7SP/hY3IWRVtmVO3i4PmpFTMNi5HHSpj9Ocvy7GsP4u6sNY0rOU/aMMhmsbBGBr87iVc
         p4mBPJBhu0jsLABy6OmlL1COSnh+wf8IxeM2nf0j0NiN/Lsbc1ROaOsmQHeESad2Vc30
         p8top+p/Eey8cw/wIvMRhOQK7y2TB9Y8BnTT5ePBSt+pct4vAkBDS0UvHSFNqtMPumhM
         Y8Kw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=WPWlBAFrYfOfqMEgSjQJiZF1KWEAEaOIklSy0CoEty4=;
        b=KZNqsgxIenNXRYij6K0Oj/RtlvE9NCHSNKhgBtg8w+rq49qy1f6mrQo+FnpGCPZi4U
         lHeNUSpDLLwHostVMhg7Cwfqnd96xPMUWso0EuKi25O/TM/0iUm3Vq6L7ypVxgLLrs1y
         dYNF217gUipufmjvX1s03j7l36zzlKjxKKbr68Ca67O6Ul82WXipHOXWjo766K8LMaFm
         ATJRBuE73iqZaIqbfpGMS88AGbbOtMqfPXLJDGmeFxBwHQidB73Zve6+MnBhHyN7Uw20
         eU1xb9dmiqiae/rLjZZNV6HfI2Y/Im72j3wH/IbZhTPE5RDDCw5TpY1Aw1fXlm9a0Hrm
         S59A==
X-Gm-Message-State: APjAAAULA4dPysEQGRoN+Zqr0JeUatF4yGmt5Y764yFQwVINqzTSnHWi
        pxOI1TjZRhM4tcX2IbH6C6M7585CJkRmqfHmLcEeoup8D1Dnb8gOLZ176pGnh7ey0uXXSPqiz5X
        8OAUJPZWpAMAStozSpiv0Iy8vY0HOW0bjv77jHCAE/habXJM9iz0mngsyPg==
X-Google-Smtp-Source: 
 APXvYqyM/XfUJWsVszHM6os7VYA/SIo8fnSxv45hZNk4AA+i3kSV1KUioTUKFsz+wL6EWSPV25PM5myg1NE=
X-Received: by 2002:a63:4f1b:: with SMTP id d27mr9989509pgb.102.1579687440408;
 Wed, 22 Jan 2020 02:04:00 -0800 (PST)
Date: Wed, 22 Jan 2020 02:03:56 -0800
Message-Id: <20200122100356.240412-1-oupton@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.25.0.341.g760bfbb309-goog
Subject: [kvm-unit-tests PATCH v2] x86: VMX: Check precondition for RDTSC test
From: Oliver Upton <oupton@google.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Oliver Upton <oupton@google.com>,
        Aaron Lewis <aaronlewis@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The RDTSC VM-exit test requires the 'use TSC offsetting' processor-based
VM-execution control be allowed on the host. Check this precondition
before running the test rather than asserting it later on to avoid
erroneous failures on a host without TSC offsetting.

Cc: Aaron Lewis <aaronlewis@google.com>
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>
Signed-off-by: Oliver Upton <oupton@google.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 x86/vmx_tests.c | 6 +++---
 1 file changed, 3 insertions(+), 3 deletions(-)

```
#### [kvm-unit-tests PATCH] x86: VMX: Check preconditions for RDTSC testFrom: Oliver Upton <oupton@google.com>
##### From: Oliver Upton <oupton@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Oliver Upton <oupton@google.com>
X-Patchwork-Id: 11345125
Return-Path: <SRS0=nF9W=3L=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 01E1F92A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 22 Jan 2020 07:40:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D413A24655
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 22 Jan 2020 07:40:06 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="UsQS5RxT"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726078AbgAVHkF (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 22 Jan 2020 02:40:05 -0500
Received: from mail-vs1-f74.google.com ([209.85.217.74]:43028 "EHLO
        mail-vs1-f74.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725883AbgAVHkF (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 22 Jan 2020 02:40:05 -0500
Received: by mail-vs1-f74.google.com with SMTP id j8so482711vsm.10
        for <kvm@vger.kernel.org>; Tue, 21 Jan 2020 23:40:04 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=Z571meg0eiiQxxoTP0BBBQ9SBLJ25qlGL+t6+g4n4iI=;
        b=UsQS5RxTjA06dw7M1OmdUOdvKBp7v8qg5OSEvcasBXyuL58IWM9a2gGVb3VcaOUMwW
         nR6kdxSAFuWw8NLRMkOxGOPdCSA8hkxNBPWeoav5pBQEWZ3SL+mRPh3h4Ax9u7k2UV9O
         DudaKmtb1XD7BruasrfvzCPy9U3nVyrIV7kJQhtx/W1GihnpncxzBVtiTGaFqbpdRzC2
         GhjqZdpe2zJtdFzPFGocrSHruNL3V+1AhD70i5UX5YSB70RNX8mICuSP/cyuu0W+YCDS
         fEAsIuSxyUwMIW1zN8zd/2pXlTyszirsPxuozkP/PgzK/zZuXcvQ/yEjFpMURsmvdeHO
         vLIg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=Z571meg0eiiQxxoTP0BBBQ9SBLJ25qlGL+t6+g4n4iI=;
        b=IQJdzAgEVvgV5Sl8o4gDtBJ1/0roP3NY7jL/WpJ2S6CYXODrhe6CYJdt7cFa7tHs6H
         QokovdHPlfZmPsHixZ7D9CUduINNfZTyXgpgjneVPekAQAKDS+tGLH0omv+8caH3gk0t
         tzeIsUWKX3shfemqYgGgIQN+xQ9mOlEGDhao9bfaOj7HHlJZmPMXlWkYB25Lw5MM3Z+n
         NuD4XaXLmQ2JlpRKZqgx8oc1AkwSDhh6rnJrQkWccu4a+ZsUehAZie3iLbpZiHIIUn7g
         k7bJurnrpldaOsPt7Wvdo4xmI7/trMMeU+Ncu/nS6NHlHqLxm5SmZfEAx8CHYsH8epfp
         U7QQ==
X-Gm-Message-State: APjAAAX4+lLvYc6f8LaymwUtw6c6ei6CAo6I8okqe4oTpbX8nlFIFB3A
        zIVqtHr7qBNLN2zDN/c8JzZi9++ce+c75l7BiRPJJZWa6qr5/75AF0iFhvQ6z7kEXh14UnMQF8p
        aAvmo5lHcjpt6MtPRSKyHP4Jmcbc1SpuX9neaXFl4xhXktZvrKtN8jghTVw==
X-Google-Smtp-Source: 
 APXvYqzPUW3RAtQTN19/aaPWJ3VyhXGw3aRLwGp1ojJWcCU6sV8JJI+Vqa5cT6BqHnVokuA2y5Lwl1HsFFw=
X-Received: by 2002:a67:6842:: with SMTP id d63mr1846521vsc.171.1579678804266;
 Tue, 21 Jan 2020 23:40:04 -0800 (PST)
Date: Tue, 21 Jan 2020 23:39:59 -0800
Message-Id: <20200122073959.192050-1-oupton@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.25.0.341.g760bfbb309-goog
Subject: [kvm-unit-tests PATCH] x86: VMX: Check preconditions for RDTSC test
From: Oliver Upton <oupton@google.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Oliver Upton <oupton@google.com>,
        Aaron Lewis <aaronlewis@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The RDTSC VM-exit test requires the 'use TSC offsetting' processor-based
VM-execution control be allowed on the host. Check this precondition
before running the test rather than asserting it later on to avoid
erroneous failures on a host without TSC offsetting.

Cc: Aaron Lewis <aaronlewis@google.com>
Signed-off-by: Oliver Upton <oupton@google.com>
---
 x86/vmx_tests.c | 8 +++++---
 1 file changed, 5 insertions(+), 3 deletions(-)

```
#### [PATCH] KVM: X86: Add 'else' to unify fastop and execute call path
##### From: linmiaohe <linmiaohe@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: linmiaohe <linmiaohe@huawei.com>
X-Patchwork-Id: 11344935
Return-Path: <SRS0=nF9W=3L=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6AAC8139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 22 Jan 2020 03:19:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 526D12465B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 22 Jan 2020 03:19:56 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729225AbgAVDTw (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 21 Jan 2020 22:19:52 -0500
Received: from szxga06-in.huawei.com ([45.249.212.32]:55916 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1728779AbgAVDTw (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 21 Jan 2020 22:19:52 -0500
Received: from DGGEMS413-HUB.china.huawei.com (unknown [172.30.72.60])
        by Forcepoint Email with ESMTP id D98259FE338F0A416F4A;
        Wed, 22 Jan 2020 11:19:50 +0800 (CST)
Received: from huawei.com (10.175.105.18) by DGGEMS413-HUB.china.huawei.com
 (10.3.19.213) with Microsoft SMTP Server id 14.3.439.0; Wed, 22 Jan 2020
 11:19:40 +0800
From: linmiaohe <linmiaohe@huawei.com>
To: <pbonzini@redhat.com>, <rkrcmar@redhat.com>,
        <sean.j.christopherson@intel.com>, <vkuznets@redhat.com>,
        <wanpengli@tencent.com>, <jmattson@google.com>, <joro@8bytes.org>,
        <tglx@linutronix.de>, <mingo@redhat.com>, <bp@alien8.de>,
        <hpa@zytor.com>
CC: <linmiaohe@huawei.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <x86@kernel.org>
Subject: [PATCH] KVM: X86: Add 'else' to unify fastop and execute call path
Date: Wed, 22 Jan 2020 11:21:44 +0800
Message-ID: <1579663304-14524-1-git-send-email-linmiaohe@huawei.com>
X-Mailer: git-send-email 1.8.3.1
MIME-Version: 1.0
X-Originating-IP: [10.175.105.18]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Miaohe Lin <linmiaohe@huawei.com>

It also helps eliminate some duplicated code.

Signed-off-by: Miaohe Lin <linmiaohe@huawei.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/emulate.c | 6 ++----
 1 file changed, 2 insertions(+), 4 deletions(-)

```
#### [PATCH 1/2] KVM: x86: reorganize pvclock_gtod_data members
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11345827
Return-Path: <SRS0=nF9W=3L=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4EE761580
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 22 Jan 2020 14:22:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 238AC2467F
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 22 Jan 2020 14:22:42 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="RFA64HBb"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728831AbgAVOWl (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 22 Jan 2020 09:22:41 -0500
Received: from mail-wr1-f67.google.com ([209.85.221.67]:39357 "EHLO
        mail-wr1-f67.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726061AbgAVOWj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 22 Jan 2020 09:22:39 -0500
Received: by mail-wr1-f67.google.com with SMTP id y11so7455567wrt.6;
        Wed, 22 Jan 2020 06:22:38 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id:in-reply-to:references;
        bh=esYJabAjEgQ+OJupE3wTIjAvn1sA/T0ZDbrjIrXhr+k=;
        b=RFA64HBbUjHV2WGXea+HfIKNhwiDb4fasmwxzaPEWlT+vjBhAM8FVXI3+LEVeWUKvJ
         q1Xy0N9hOSr1efO/HbT7XJeUFGosw7090YKpsDLS8ULmvKLRa33EYOoSO8NaRyiQVznU
         PXr+XkB6rZCP1FyIfM/FZ57CF7xC0fSXB5Tve1kOn9Z7A0LOMdQzvG9C0gsV2z3hoYex
         Vz0KS8qZIjMMj7D1LZx0x6KnStU/SqS4gSfdzu3CWy2xnsseSzzgGTf5CBr83PCdjybF
         9iwWTTK90hiZcIh77RWd9J8zZ2NuX2T/jH95KaLZJFr75jp7ki8RsI+uci9DBoWjQJrr
         03wA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id
         :in-reply-to:references;
        bh=esYJabAjEgQ+OJupE3wTIjAvn1sA/T0ZDbrjIrXhr+k=;
        b=t0ztN2Gp6U7xHV22F7XKnc3WkM25jyYVHsB1iBHI2b64idwS11oqvq1GnP/hueCqf0
         6t4CUfUqvRqju+WtIiu/+TieeF92Lqb57yOP35gq3lKhlQZPzsjhbj11fw2B7qUb+eBZ
         HQ8vyRz0pGEQ3GfffN6bppGRkReJDX0/4+YlHOjY4h7u8tuanYnjtbZ/z1sK6OA6DkUm
         WuZOADmekN1UPPnbtToVY9VIUIsuA0zTVBroA55O3FDmePTaV6t5x3QDmJ82CqogHKA2
         IuriqkqPyJDYKqs2i9FGrBMq4rqlKYEe84dE0YdWahhsRWCj7zPU9aNsSV0KmY+Yqtk2
         VZLA==
X-Gm-Message-State: APjAAAXLXBACtvYuNoehdyqCGEcVvFWtYV5ncnBWNSAoiQrkIfv94iB5
        1Co5l4+fjf6DTmZgnduRPDX5QPKw
X-Google-Smtp-Source: 
 APXvYqzS3Ld2f5YX9vXRWxiASD+S6dfNkhQTU9CMja25hxOIQ2dZCWYWh/87OWuz7uMEg7TCSMu8og==
X-Received: by 2002:a5d:608a:: with SMTP id
 w10mr10943148wrt.136.1579702957407;
        Wed, 22 Jan 2020 06:22:37 -0800 (PST)
Received: from 640k.localdomain ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 x11sm4172282wmg.46.2020.01.22.06.22.36
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Wed, 22 Jan 2020 06:22:36 -0800 (PST)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: mtosatti@redhat.com, stable@vger.kernel.org
Subject: [PATCH 1/2] KVM: x86: reorganize pvclock_gtod_data members
Date: Wed, 22 Jan 2020 15:22:32 +0100
Message-Id: <1579702953-24184-2-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1579702953-24184-1-git-send-email-pbonzini@redhat.com>
References: <1579702953-24184-1-git-send-email-pbonzini@redhat.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We will need a copy of tk->offs_boot in the next patch.  Store it and
cleanup the struct: instead of storing tk->tkr_xxx.base with the tk->offs_boot
included, store the raw value in struct pvclock_clock and sum tk->offs_boot
in do_monotonic_raw and do_realtime.   tk->tkr_xxx.xtime_nsec also moves
to struct pvclock_clock.

While at it, fix a (usually harmless) typo in do_monotonic_raw, which
was using gtod->clock.shift instead of gtod->raw_clock.shift.

Fixes: 53fafdbb8b21f ("KVM: x86: switch KVMCLOCK base to monotonic raw clock")
Cc: stable@vger.kernel.org
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/x86.c | 29 ++++++++++++-----------------
 1 file changed, 12 insertions(+), 17 deletions(-)

```
#### [PATCH v16.1 1/9] mm: Adjust shuffle code to allow for future coalescing
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Duyck <alexander.duyck@gmail.com>
X-Patchwork-Id: 11346167
Return-Path: <SRS0=nF9W=3L=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 31EBF921
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 22 Jan 2020 17:43:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 067182465A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 22 Jan 2020 17:43:22 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="Yawhn1PR"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729165AbgAVRnS (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 22 Jan 2020 12:43:18 -0500
Received: from mail-pg1-f195.google.com ([209.85.215.195]:45124 "EHLO
        mail-pg1-f195.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725802AbgAVRnS (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 22 Jan 2020 12:43:18 -0500
Received: by mail-pg1-f195.google.com with SMTP id b9so3864023pgk.12;
        Wed, 22 Jan 2020 09:43:17 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=subject:from:to:cc:date:message-id:in-reply-to:references
         :user-agent:mime-version:content-transfer-encoding;
        bh=U5nqS48VkVvRnyHBjFiWdK30Nd7uygAKlLKY0VqrQZ0=;
        b=Yawhn1PRyhFUU7ZXSffeeRdt5LlXMZy8hSYhR5tRFQqMBp46BrEy/CvAEdQaWYyMTS
         xlcUFCAq8HjJjcvKrHFmiqBmCI/Dw4hmeruF4DBrz0Ha8hFAmQ2QEorjZYfrbK1d/XeT
         gzmsNRi2xECXJHOH+9akZ24kciDKpYMcSwAwxd6sLW716QZj7yJZSgaAHdhmY9PXLeE/
         C7dchnut3wIP+oLsHbq3AKIw6ZFV49JZ7w4YCpyjRixAMEinwdk0tfnJpN8PjPG+6cng
         s0JXt4otXM9fqAIY1LY4DJq98TKbnVT+SFFlUNorJ/l78iC9win9lgbDCTphteaXZWSP
         jjNw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:subject:from:to:cc:date:message-id:in-reply-to
         :references:user-agent:mime-version:content-transfer-encoding;
        bh=U5nqS48VkVvRnyHBjFiWdK30Nd7uygAKlLKY0VqrQZ0=;
        b=nXL8Z1u40c2jTPNRRNr0eljChn73NtdNaRHCib/tEAa2z4NcCiXXlGXj2bxZg4T5s8
         qKEMrjWC0t3C3oQ61lRjnf7FumTGWHsCxd+nMs4IKhzprwHnZOEB0wmTU7h22dT45wve
         R1MZjcpTIzdXRDTzPHtHWARP90v4MzThRQsIVbO4mVL9mckPdHJ8/yeoccmzvX3DLDN7
         R4mJsDgySnOwIoevdprsYtacCP3d1PMzHVCCzrWE6sOjoY574U1kmrY/D33aCEihTTz3
         Eh0FyAXIOXg5rX8L78JlVIFOoflF27qlOnjsbIsCFvJ1wKAI92EJpOzzRMds2yK9mco0
         Fj/w==
X-Gm-Message-State: APjAAAW+JNubdGdz3TSCc6rf4qhFaN5OfYtd5od2BtAnprmyuN3KnhaP
        Qf6F2xG5zKCmsp+64bwavoOB5p0Af7BPLw==
X-Google-Smtp-Source: 
 APXvYqyIHZfLbsL94JHkjIMgi28d6n2Jc32B0ndImQ7VaEuEFtaxBgwllDfoYIBET/RAZe+I7APPjQ==
X-Received: by 2002:a62:e509:: with SMTP id n9mr3502073pff.159.1579714997197;
        Wed, 22 Jan 2020 09:43:17 -0800 (PST)
Received: from localhost.localdomain ([2001:470:b:9c3:9e5c:8eff:fe4f:f2d0])
        by smtp.gmail.com with ESMTPSA id
 c15sm4667086pja.30.2020.01.22.09.43.16
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Wed, 22 Jan 2020 09:43:16 -0800 (PST)
Subject: [PATCH v16.1 1/9] mm: Adjust shuffle code to allow for future
 coalescing
From: Alexander Duyck <alexander.duyck@gmail.com>
To: kvm@vger.kernel.org, mst@redhat.com, linux-kernel@vger.kernel.org,
        willy@infradead.org, mhocko@kernel.org, linux-mm@kvack.org,
        akpm@linux-foundation.org, mgorman@techsingularity.net,
        vbabka@suse.cz
Cc: yang.zhang.wz@gmail.com, nitesh@redhat.com, konrad.wilk@oracle.com,
        david@redhat.com, pagupta@redhat.com, riel@surriel.com,
        lcapitulino@redhat.com, dave.hansen@intel.com,
        wei.w.wang@intel.com, aarcange@redhat.com, pbonzini@redhat.com,
        dan.j.williams@intel.com, alexander.h.duyck@linux.intel.com,
        osalvador@suse.de
Date: Wed, 22 Jan 2020 09:43:16 -0800
Message-ID: <20200122174316.6142.63457.stgit@localhost.localdomain>
In-Reply-To: <20200122173040.6142.39116.stgit@localhost.localdomain>
References: <20200122173040.6142.39116.stgit@localhost.localdomain>
User-Agent: StGit/0.17.1-dirty
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Alexander Duyck <alexander.h.duyck@linux.intel.com>

Move the head/tail adding logic out of the shuffle code and into the
__free_one_page function since ultimately that is where it is really
needed anyway. By doing this we should be able to reduce the overhead
and can consolidate all of the list addition bits in one spot.

Acked-by: Mel Gorman <mgorman@techsingularity.net>
Acked-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Dan Williams <dan.j.williams@intel.com>
Signed-off-by: Alexander Duyck <alexander.h.duyck@linux.intel.com>
---
 include/linux/mmzone.h |   12 --------
 mm/page_alloc.c        |   71 ++++++++++++++++++++++++++++--------------------
 mm/shuffle.c           |   12 ++++----
 mm/shuffle.h           |    6 ++++
 4 files changed, 54 insertions(+), 47 deletions(-)

```
