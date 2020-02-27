#### [kvm-unit-tests PATCH v2 2/7] x86: provide enabled and disabled variation of the PCID test
##### From: Bill Wendling <morbo@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Bill Wendling <morbo@google.com>
X-Patchwork-Id: 11405765
Return-Path: <SRS0=q2E5=4O=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 52CE7138D
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 26 Feb 2020 09:44:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 3292624673
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 26 Feb 2020 09:44:51 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="GKYFWXZM"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727869AbgBZJot (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 26 Feb 2020 04:44:49 -0500
Received: from mail-pl1-f202.google.com ([209.85.214.202]:54445 "EHLO
        mail-pl1-f202.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727755AbgBZJos (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 26 Feb 2020 04:44:48 -0500
Received: by mail-pl1-f202.google.com with SMTP id s13so1414097plr.21
        for <kvm@vger.kernel.org>; Wed, 26 Feb 2020 01:44:48 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=pvcm8MZ0RliZCFtd81lkqdkPVzbXHWhtbZtW9VB8qF8=;
        b=GKYFWXZMT949uGz4XdlCigNh/jwxaX0pc4SSP7+VRrxgUkeD4/n5IBsMsW5pWoQPUv
         bgSn9l1DEuAsreiE/RPKlnZi7zuyBGJl7X/owPouB/BDyfdJGF1cpwGBUxIjTnBHrsEk
         3xETsWcY0KY6W0piMqJeBmd4BfChgMoFExJp6eLAHo1lqBuUzUsWR4lswYgORtlxvIwD
         ptVpnGZIyruiwxQdRIsYfD2pf2WONkjHy74FDOHMEk0uB/OLPByMgTVGZuijzh2/RAur
         XG4KuWlTGekZy1nYedazSGkRO3tnr2DghKhE9GYWs+ad3xJ1JW3LW3MsMzjlxs95HQlc
         UQkQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=pvcm8MZ0RliZCFtd81lkqdkPVzbXHWhtbZtW9VB8qF8=;
        b=CX+pvh2GdT2MK5crCxd2tn1pIcnqBx01YkjsyHhJnEZsQzGoSVM9Srbw7N3KKYJOAX
         jGTLfFW5Cj2XAQn9h3kAN1ghcuOXLdS/pRSM8jzj1sIZFAOlbyRSlERla2Im4dsX/5Pp
         7NE2JuQkoBTymML3oJ1WPSB4shjxkij3aw7cav6+dYUcDYpMSSCvsiAzBXqy8sWoGjM7
         8IfbY3bUWckj4iSvQqc4hsl76w6rqWAczUJMLYuM3KIUOiY5odfwgb0eOtC1W8GrWXC/
         ENJeq8EbcrCvUea42TRoIps/G9q+ayJv3Z+VSuI9eflH8N0wv9euEMdfn4pywIgr5y5L
         ZT5w==
X-Gm-Message-State: APjAAAUS4/4bNeY1i/eSSmb1DQe3Al1En69Vrkx9JAPYGF0F8izGBl37
        MLW5Tg2a1dAkyL4oFyiZBWaR+ZzUOtDCog9HOnCGkAz87krJNqWbX/dpaisxWmtkR2dSUMbToxz
        Vg1fz6x8O6W1Z+SaaoSEwLroC+bjE4zVKQ3KTSSAIyQFHO+TCQH/8dg==
X-Google-Smtp-Source: 
 APXvYqwHmXbP9rkukxJXuE3CdXnMQZsD0VxWHav+57GZr0j9ZCP2jEAanA51bO6CZGw+X+WVe8VA6GU1YQ==
X-Received: by 2002:a63:df02:: with SMTP id u2mr2859344pgg.403.1582710287454;
 Wed, 26 Feb 2020 01:44:47 -0800 (PST)
Date: Wed, 26 Feb 2020 01:44:23 -0800
In-Reply-To: <20200226094433.210968-1-morbo@google.com>
Message-Id: <20200226094433.210968-5-morbo@google.com>
Mime-Version: 1.0
References: <20200226074427.169684-1-morbo@google.com>
 <20200226094433.210968-1-morbo@google.com>
X-Mailer: git-send-email 2.25.0.265.gbab2e86ba0-goog
Subject: [kvm-unit-tests PATCH v2 2/7] x86: provide enabled and disabled
 variation of the PCID test
From: Bill Wendling <morbo@google.com>
To: kvm@vger.kernel.org
Cc: oupton@google.com, pbonzini@redhat.com, drjones@redhat.com,
        Bill Wendling <morbo@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Paolo Bonzini <pbonzini@redhat.com>

The PCID test checks for exceptions when PCID=0 or INVPCID=0 in
CPUID.  Cover that by adding a separate testcase with different
CPUID.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Bill Wendling <morbo@google.com>
---
 x86/unittests.cfg | 7 ++++++-
 1 file changed, 6 insertions(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH 3/7] x86: realmode: syscall: add explicit size suffix to ambiguous instructions
##### From: Bill Wendling <morbo@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Bill Wendling <morbo@google.com>
X-Patchwork-Id: 11405769
Return-Path: <SRS0=q2E5=4O=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6342314D5
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 26 Feb 2020 09:44:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 41B1C2467D
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 26 Feb 2020 09:44:55 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="CLavvEzE"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727912AbgBZJoy (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 26 Feb 2020 04:44:54 -0500
Received: from mail-pj1-f74.google.com ([209.85.216.74]:37947 "EHLO
        mail-pj1-f74.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727889AbgBZJox (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 26 Feb 2020 04:44:53 -0500
Received: by mail-pj1-f74.google.com with SMTP id 14so1663143pjo.3
        for <kvm@vger.kernel.org>; Wed, 26 Feb 2020 01:44:53 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=ZriTMGPJdIBl60+ly0kTO53DNTTG646ayUk1xBLJ7Ls=;
        b=CLavvEzEBBBh55R2mU+kQkVXAtm9zE5JBnu8k6n4ANx6ioS7Q9Hqq991Qi4Jpdea80
         7+OH7AIV13iuwO/sl1ARkliD0Ba61LVHe6PmBrj/9fNPndDLvPvfvMhvvpYS+e4q+uWZ
         7YVBCay9Mlv99eKkj1RnY647ey7cy441I7GBG0BdhDU5P7WWhhjubUHY9Awz4tTX4z0k
         Tbo2F44Yn0R5WigHdxSsoEDmYdQGkIRZcDzQoItjOQ2Pk2pj3PkUsRCey8NEFhzGQWEV
         wFgbIxwgr/41aSC5zjHrfZGgxTMNeyFJpBjXrIT+VGV9hKShym1LxC3zM8UMnDqGb6Fe
         njDg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=ZriTMGPJdIBl60+ly0kTO53DNTTG646ayUk1xBLJ7Ls=;
        b=UgyIQMdOj/ESe4ivk5jlkIK682wgshVbCfZVKY6pByviB3PkaCDM77aDqicVmZoR53
         G+UyNdyMKMOJieWkiX9i/MQIfSuuBkI4SoCp0LRO84TOml3wsDHE84Dya1mZme1tWB14
         80vA5o9iLCSKlBnBvsUnsge0o9DKnRwxinHpuGrkAIwjjDGAc7okGvlYQQ6Kh01S6ra5
         UITk/K9/vKf+u05LoQMngRF6KOTXWrygXTr+WGK6jYRrI3isIngM6TyjcTM6b6gyLUid
         ssreaQNOolRcl/sWk3LTvW4IB/tfG8v2oQJMVHaBK/67Ibsgr+6LEZ224H/XQA0uu2k2
         ILzQ==
X-Gm-Message-State: APjAAAX/+QRpdvRlbJ/wyztblopRjPtuqXpQBY1QwETypV5FwhcVqMC6
        DjCB489rOeNpBchclUzemQ7FQ5iKJAnb6pU7P0Itd6p9h4VHX53oT+8u20K1DYuRdG6dtvcxwY4
        cR9QuQYgPajwGLgWkiqz9MQXAV7koEkQxxXJuldwxNidSIlpAiUp1Lw==
X-Google-Smtp-Source: 
 APXvYqz+rTxnSQEQ/WeXDZSmmEWNVYpSKSgj7yQ6H8GbaIW7ibrKP3Cllg1KLwROqGOyi/blfRfcuH5aVg==
X-Received: by 2002:a63:4c66:: with SMTP id m38mr3098817pgl.313.1582710292205;
 Wed, 26 Feb 2020 01:44:52 -0800 (PST)
Date: Wed, 26 Feb 2020 01:44:25 -0800
In-Reply-To: <20200226094433.210968-1-morbo@google.com>
Message-Id: <20200226094433.210968-7-morbo@google.com>
Mime-Version: 1.0
References: <20200226074427.169684-1-morbo@google.com>
 <20200226094433.210968-1-morbo@google.com>
X-Mailer: git-send-email 2.25.0.265.gbab2e86ba0-goog
Subject: [kvm-unit-tests PATCH 3/7] x86: realmode: syscall: add explicit size
 suffix to ambiguous instructions
From: Bill Wendling <morbo@google.com>
To: kvm@vger.kernel.org
Cc: oupton@google.com, pbonzini@redhat.com, drjones@redhat.com,
        Bill Wendling <morbo@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Clang requires explicit size suffixes for potentially ambiguous
instructions:

x86/realmode.c:1647:2: error: ambiguous instructions require an explicit suffix (could be 'cmpb', 'cmpw', or 'cmpl')
        MK_INSN_PERF(perf_memory_load, "cmp $0, (%edi)");
        ^
x86/realmode.c:1591:10: note: expanded from macro 'MK_INSN_PERF'
                      "1:" insn "\n"                            \
                       ^
<inline asm>:8:3: note: instantiated into assembly here
1:cmp $0, (%edi)
  ^

The 'w' and 'l' suffixes generate code that's identical to the gcc
version without them.

Signed-off-by: Bill Wendling <morbo@google.com>
---
 x86/realmode.c | 6 +++---
 x86/syscall.c  | 2 +-
 2 files changed, 4 insertions(+), 4 deletions(-)

```
#### [kvm-unit-tests PATCH v2 4/7] vmx: tweak XFAILS for #DB testFrom: Bill Wendling <morbo@google.com>
##### From: Bill Wendling <morbo@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Bill Wendling <morbo@google.com>
X-Patchwork-Id: 11405773
Return-Path: <SRS0=q2E5=4O=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id ACDCC14D5
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 26 Feb 2020 09:44:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 8CC042467D
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 26 Feb 2020 09:44:59 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="F4NeoXtL"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727872AbgBZJo6 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 26 Feb 2020 04:44:58 -0500
Received: from mail-pg1-f202.google.com ([209.85.215.202]:37562 "EHLO
        mail-pg1-f202.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727929AbgBZJo6 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 26 Feb 2020 04:44:58 -0500
Received: by mail-pg1-f202.google.com with SMTP id b22so1516579pgs.4
        for <kvm@vger.kernel.org>; Wed, 26 Feb 2020 01:44:57 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=1mPKloEPT/3VCCmlRL4FcBxSmIuE32tpcUsdGN9GJ5o=;
        b=F4NeoXtLHXoCwc4PdenpmA5NxQAorTZCsyq/xBgLD0gPky+X6yF/yk1ujOuIKD9zzD
         c25stG1mTrAoInMHeMbywmDMPfoxGqhSAqJ3VP636ckjU89UwXZxxbUImPzLSTpTnGjX
         gUjbvRR2Tmca9c6pUj7hCyA/YJAClIcoZhSkrClNsX2ilHtELA64WSyLhhX7ia1lwOnn
         5BS0KH4RAaCt+zAXTFQhtqmbkWP3Q2rumWj4vlqbSHilrid/EWpBQYgrPorCuNtRCKF/
         xDE7xu1iY3Cx2KibGcpnsf7idJyvGIB4eRklySWsRWqqvelEbT3afy/6y93ttMX5ikLA
         wYdw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=1mPKloEPT/3VCCmlRL4FcBxSmIuE32tpcUsdGN9GJ5o=;
        b=gCT8JtAorqvX8m11OG8Bxyf0K6c+8jIdacxvf+ie+Kvw3ENUQgPvn1Fnonz/C1Oge+
         kjLJeUCRIfW+jXxNnJFpSS0OWlJSDzFlkcepGvtqpxZQ2MEepvF8JWqgr0N4K9osoAhm
         cW0zEFbR3Jw8aidobM50Bd3ulBBQDNPzk2CNvz7f43jvFKDAyqibzoJzQOC2ogUFEOJJ
         s5yvA59HF8MxQQDwYe6taZ63WNa37Jw0uEQ1nizROaQpuDGivYFf4/a8ZhRxjFdtG6no
         wQbXvFG3BR1rkewRzdx7nLYzkPWU5Kyj3vR0dFZR9Y+M1PufI4B2hYbnfEX8Iu1j3nkk
         fNaQ==
X-Gm-Message-State: APjAAAUM6oOL9feez9J4a3/yJ0yRmw1iihACFRauxqtzYOlW6jDsJnns
        0bktrPy1a4LTj48YGS0nW2qCVurnmyjEpIz4RbEY9fGkSYCAwnLzXx8PHRajKH+cco15B6UMvfl
        n6VrjKYJChxnZMCjf8larIOocgku5KbistMD/2M884WSCB4Xj3igRbw==
X-Google-Smtp-Source: 
 APXvYqwLIWtbqy5cx1/Tw/c2SNlzlbilPkrk1wgKMBUmZEwWn0N/EhnEKoAfVrW8NP8IrMr14e1WGs+nrQ==
X-Received: by 2002:a63:48f:: with SMTP id 137mr2915616pge.245.1582710297195;
 Wed, 26 Feb 2020 01:44:57 -0800 (PST)
Date: Wed, 26 Feb 2020 01:44:27 -0800
In-Reply-To: <20200226094433.210968-1-morbo@google.com>
Message-Id: <20200226094433.210968-9-morbo@google.com>
Mime-Version: 1.0
References: <20200226074427.169684-1-morbo@google.com>
 <20200226094433.210968-1-morbo@google.com>
X-Mailer: git-send-email 2.25.0.265.gbab2e86ba0-goog
Subject: [kvm-unit-tests PATCH v2 4/7] vmx: tweak XFAILS for #DB test
From: Bill Wendling <morbo@google.com>
To: kvm@vger.kernel.org
Cc: oupton@google.com, pbonzini@redhat.com, drjones@redhat.com,
        Bill Wendling <morbo@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Paolo Bonzini <pbonzini@redhat.com>

These were already fixed by KVM_CAP_EXCEPTION_PAYLOAD, but they were failing
on old QEMUs that did not support it.  The recent KVM patch "KVM: x86: Deliver
exception payload on KVM_GET_VCPU_EVENTS" however fixed them even there, so
it is about time to flip the arguments to check_db_exit and avoid ugly XPASS
results with newer versions of QEMU.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Bill Wendling <morbo@google.com>
---
 x86/vmx_tests.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [kvm-unit-tests PATCH v2 5/7] x86: VMX: Add tests for monitor trap flag
##### From: Bill Wendling <morbo@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Bill Wendling <morbo@google.com>
X-Patchwork-Id: 11405777
Return-Path: <SRS0=q2E5=4O=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 94C2014D5
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 26 Feb 2020 09:45:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 6ACE62467A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 26 Feb 2020 09:45:06 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="G5aNBFlQ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727968AbgBZJpE (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 26 Feb 2020 04:45:04 -0500
Received: from mail-qv1-f73.google.com ([209.85.219.73]:51186 "EHLO
        mail-qv1-f73.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727952AbgBZJpE (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 26 Feb 2020 04:45:04 -0500
Received: by mail-qv1-f73.google.com with SMTP id c1so3152450qvw.17
        for <kvm@vger.kernel.org>; Wed, 26 Feb 2020 01:45:03 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=X8sk38JcHcyj3teXeT7Jj1TNQ3W5tYgn8rNWYfS/zck=;
        b=G5aNBFlQLED8pf5uEEbDE/9htzAgojcJ92v/B9SXLqHaeB7nu8sW98f4IurmSL2+ap
         S0kcTCUNlm7xx4MAHnQMfjOMBl/33f6Tcr2xM4apxR6vKGqcPrY7jbaHWcqsm51lyBYc
         7haqBk7n1fWwH2arwRCgDmrraR2vuTgQDVrEpXMZAZaId1ROjATK7rhmTupaOap3YYYa
         SBuNBUPahPsZJcxUkq5F2UxmVqp3yAco66JLJ7kEJFmTi5uxqLz6oiJzHVqYr7LYl89Z
         VI5tMuMayVBN203Ix6LANAdZrgum9Kxgjc/lvcFNWsUIhSI80RAa8dfUfXG5Ummt/612
         rH2g==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=X8sk38JcHcyj3teXeT7Jj1TNQ3W5tYgn8rNWYfS/zck=;
        b=KkXXDKCAhV4ezxu4LgK+QC8Q5SOL5OAOObO6e9bklHU9dgKazBPEe/Js91qm0WrEtl
         aRJXQlEvRaSJURGObjl+Y5C/Klqh9NrjdHEbSqGfnMa1B5W8K1nJ8N7PQy7HLf2BaShG
         /nHZnS58CJVq4liIGtUC6ase19qSMmcoN0ybQkpWfAGEMnitqUcevw9BHRP6rwYKCz3o
         6lwrTccMbsKBl3GilNfnVdu/OhroPDCHFh1qbncqViYT6fOGtE/UuRqoExItkz7NdMaa
         d2UbrkYGH84n2YMVXgSA5cXYL78yCO7cVj7Xo7Omq+C18kWkya3VGsZ4opWC1hD1OANc
         vylQ==
X-Gm-Message-State: APjAAAVq5y9ZUNiSPkHAbsjud8Ng2KFsZTAYTOZfzJsgG732gAHmRzqb
        EpkbFd93Pkv77aII8sBGEdLejiNsP8GuUSrqg+vt3yBLGh3QgDPJdpmVdkwhu8h0llV0huNscEv
        P46ChxLC14RSRCcQT0OFchnWfObkEYnWRYcJUybZSYlqIDGS0WOmkcw==
X-Google-Smtp-Source: 
 APXvYqxPzL4WoT4R6nk4hX7bPsf19ptKB1Psb2Id6qzb6C0JW0ulSvBV/eklvely4sPU2TN2f+Jscq8Sfw==
X-Received: by 2002:ac8:4cc9:: with SMTP id l9mr3558474qtv.207.1582710302954;
 Wed, 26 Feb 2020 01:45:02 -0800 (PST)
Date: Wed, 26 Feb 2020 01:44:29 -0800
In-Reply-To: <20200226094433.210968-1-morbo@google.com>
Message-Id: <20200226094433.210968-11-morbo@google.com>
Mime-Version: 1.0
References: <20200226074427.169684-1-morbo@google.com>
 <20200226094433.210968-1-morbo@google.com>
X-Mailer: git-send-email 2.25.0.265.gbab2e86ba0-goog
Subject: [kvm-unit-tests PATCH v2 5/7] x86: VMX: Add tests for monitor trap
 flag
From: Bill Wendling <morbo@google.com>
To: kvm@vger.kernel.org
Cc: oupton@google.com, pbonzini@redhat.com, drjones@redhat.com,
        Jim Mattson <jmattson@google.com>,
        Bill Wendling <morbo@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Oliver Upton <oupton@google.com>

Test to verify that MTF VM-exits into host are synthesized when the
'monitor trap flag' processor-based VM-execution control is set under
various conditions.

Expect an MTF VM-exit if instruction execution produces no events other
than MTF. Should instruction execution produce a concurrent debug-trap
and MTF event, expect an MTF VM-exit with the 'pending debug exceptions'
VMCS field set. Expect an MTF VM-exit to follow event delivery should
instruction execution generate a higher-priority event, such as a
general-protection fault. Lastly, expect an MTF VM-exit to follow
delivery of a debug-trap software exception (INT1/INT3/INTO/INT n).

Signed-off-by: Oliver Upton <oupton@google.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Bill Wendling <morbo@google.com>
---
 x86/vmx.h       |   1 +
 x86/vmx_tests.c | 157 ++++++++++++++++++++++++++++++++++++++++++++++++
 2 files changed, 158 insertions(+)

```
#### [kvm-unit-tests PATCH 6/7] x86: VMX: use inline asm to get stack pointer
##### From: Bill Wendling <morbo@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Bill Wendling <morbo@google.com>
X-Patchwork-Id: 11405781
Return-Path: <SRS0=q2E5=4O=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 66075138D
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 26 Feb 2020 09:45:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4522F2467B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 26 Feb 2020 09:45:12 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="MBfEqHLx"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727983AbgBZJpL (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 26 Feb 2020 04:45:11 -0500
Received: from mail-qt1-f201.google.com ([209.85.160.201]:55181 "EHLO
        mail-qt1-f201.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727946AbgBZJpL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 26 Feb 2020 04:45:11 -0500
Received: by mail-qt1-f201.google.com with SMTP id l1so3653650qtp.21
        for <kvm@vger.kernel.org>; Wed, 26 Feb 2020 01:45:09 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=4WOJEMcFAo8Q+bRyqnBtGx2pV60RRZcS3M/cilyPn98=;
        b=MBfEqHLxyPlYpdt2lHrUY07WKLYXKd7LRvvMgJnDZszkwjMxMDapwX5ufVUCz9E5o4
         BPpLPnK8alVTCw+yZtbXYtR2Bv6KaJnb9Ph8g/kActNfDCNFxuUmvj4lvjrns8Y4GAM0
         1Ro/gJPxAWxlgeV8ISYM3VmpPbQIFKEBIMid1w1haHRZd93idr1MAjIBgIYxX91/Jchw
         6mWjLm7axFpcOYnXzS+pDejlEQgCL3OD8O7T9bUHONre3V25P7bWjS7KMI4W+UIuc4qF
         /XsNPc03JUVaxmD4ZMZDwv2z99LV9Y6n/1MXHTraAd6kjsEcYYybTLekHLeOYTWd8rr/
         HjfQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=4WOJEMcFAo8Q+bRyqnBtGx2pV60RRZcS3M/cilyPn98=;
        b=batSOcBY6aPjhbc1+Hd5wxAtlPmfRQqvGSjuLhBOHXgoge2HrPKL1RE3XFcsUkbAEU
         rwM+mqq8t87qoQjR+Ua4Eng/c+Jf+v2sumbFVyfaIBYCHIPbb65H4OquM+BrwMEsnru7
         QUvJauYjopLBdf2xgMpUt22pWLhIgnhWhFkXVX1axVXXQgaDRCpn/zjfkB/499PEo+R+
         uZzVjBtXe/fLy9Izl4FQ29yctc4nF0AVjVYqAgOP99sVIw5WVKu0FCFJCOFhIfhewjlH
         lZCTtithkDwqFthyZ4YWRdwuDZQVbc4t7RlAUWxzFss7+Dx3zWdUmH0bhDquUBXTE6hU
         9b/g==
X-Gm-Message-State: APjAAAVDlolrbU76FzcnqAHpssksLdaQFs5+otElIi24gF/Xmb7aTqYc
        DVyQOcuZsyV29bxOH9qwxi1hUHv2Nd745PEUUl520GZpsrOWZKFhVHJAqI+Lwt90DilrTN06QsQ
        0IHpu4hA5YWHR8Oia2L3rhhQtRZZtEqFlnYL8ws5NaP5Q9kbKKcbgxA==
X-Google-Smtp-Source: 
 APXvYqxCN/GwM3JCkKF+6xdOBTWqDYPleeTVJgNz1MBMtd7UCwBaVNd9xRkADQ7wrTIhzbVFdGCgcLDPdw==
X-Received: by 2002:aed:3e61:: with SMTP id m30mr4289513qtf.347.1582710308206;
 Wed, 26 Feb 2020 01:45:08 -0800 (PST)
Date: Wed, 26 Feb 2020 01:44:31 -0800
In-Reply-To: <20200226094433.210968-1-morbo@google.com>
Message-Id: <20200226094433.210968-13-morbo@google.com>
Mime-Version: 1.0
References: <20200226074427.169684-1-morbo@google.com>
 <20200226094433.210968-1-morbo@google.com>
X-Mailer: git-send-email 2.25.0.265.gbab2e86ba0-goog
Subject: [kvm-unit-tests PATCH 6/7] x86: VMX: use inline asm to get stack
 pointer
From: Bill Wendling <morbo@google.com>
To: kvm@vger.kernel.org
Cc: oupton@google.com, pbonzini@redhat.com, drjones@redhat.com,
        Bill Wendling <morbo@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The only supported use of a local register variable is to specify
registers for input and output operands when calling Extended asm. Using
it to automatically collect the value in the register isn't supported as
the contents of the register aren't guaranteed. Instead use inline asm
to get the stack pointer explicitly.

Signed-off-by: Bill Wendling <morbo@google.com>
---
 x86/vmx_tests.c | 6 ++++--
 1 file changed, 4 insertions(+), 2 deletions(-)

```
#### [kvm-unit-tests PATCH 7/7] x86: VMX: the "noclone" attribute is gcc-specific
##### From: Bill Wendling <morbo@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Bill Wendling <morbo@google.com>
X-Patchwork-Id: 11405785
Return-Path: <SRS0=q2E5=4O=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B6B9214D5
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 26 Feb 2020 09:45:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 96C0B2467C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 26 Feb 2020 09:45:20 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="bSg/lgzO"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728000AbgBZJpP (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 26 Feb 2020 04:45:15 -0500
Received: from mail-pg1-f201.google.com ([209.85.215.201]:32874 "EHLO
        mail-pg1-f201.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727973AbgBZJpO (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 26 Feb 2020 04:45:14 -0500
Received: by mail-pg1-f201.google.com with SMTP id 37so1523816pgq.0
        for <kvm@vger.kernel.org>; Wed, 26 Feb 2020 01:45:14 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=ansmD08qeSQd3zCEhBBHvF2ZiEtCQ7Cypjwva684W3Y=;
        b=bSg/lgzO8EyFmpdJa2X9yE+aw7omAzEe9b9MN0UpOqHdJFzplGKmhAesP+WMvUIDrI
         d3/0M5sRUyLVelAeJxhhqyo5hXn4A02sR3tS0HIs8rO4FuedRefAi9WxyNETryov/+ru
         VzhtVqsEQ1YQlWwDviU76BXc7+2G+D9UXp4mxzdyhicvhhvycR23ofF65zNCLC1E25ul
         fmX0NbdyEq2cKOw7lfVIe5C421n0RzvVZouIJH/mW9x4RVPyV3QEYLvvi9ehwRJTXY2W
         eL53JViDy4p776qC8pXqse9wztUajrD+U7oUc4rfdi80447xXd9pJAZY5kWGpG4DpzWq
         k6Ng==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=ansmD08qeSQd3zCEhBBHvF2ZiEtCQ7Cypjwva684W3Y=;
        b=nL/FglODf68Coo6OhgC0mo6I0SglRq6rbbVZGouDew5f0JzDs6e4lbB6p7d3+vpgRX
         9tuZEXODFJdKPP1GrIbPCyhEhzG/LKSmjxeEyd2zazkTTaYptZ5E3gEnkdYOUuvjJCA+
         /HJ/DrPKAKUFihxo/COMsNW4LYuCU/NrDYSUDbOCu35qrdwU34r26YoJM7SFsTPuVc80
         JpdNFInkTwfsGTs1DlbAypD2kyjvucqMDg0FrPAukM9xvjt5Vj3AHLByPazp6LflSRaw
         LlRZQgIMLZOj6T1idL1RfbdnGlLGadKAdAgKWRlq+EYD+GIeghn+6YSHMu9ZShEs7uEu
         8YVw==
X-Gm-Message-State: APjAAAWheNpyyn6NXTsLEF5K5X6AcXDn1naB6uo+UQV9sret0RcaifQO
        NSG7hwXZaDBWwp1lyT29QcMVfiOywjsvPDvHpaUy5HOyOQV1NN8dmsUFiqoGf7WmSazs672TW8l
        RCOGWZ2pThQ7fBU1Nqo90jD3tRV4zghyUdU1S6GPHqJprKJJQ8mXrgA==
X-Google-Smtp-Source: 
 APXvYqxtDaimY5cY7HlA/FVJiMnSVTNbWXaOP/GHptQrOggE8upKzyNBA59154aPbwXqe4FyTqfA8XtYJQ==
X-Received: by 2002:a63:68a:: with SMTP id 132mr3136042pgg.12.1582710313516;
 Wed, 26 Feb 2020 01:45:13 -0800 (PST)
Date: Wed, 26 Feb 2020 01:44:33 -0800
In-Reply-To: <20200226094433.210968-1-morbo@google.com>
Message-Id: <20200226094433.210968-15-morbo@google.com>
Mime-Version: 1.0
References: <20200226074427.169684-1-morbo@google.com>
 <20200226094433.210968-1-morbo@google.com>
X-Mailer: git-send-email 2.25.0.265.gbab2e86ba0-goog
Subject: [kvm-unit-tests PATCH 7/7] x86: VMX: the "noclone" attribute is
 gcc-specific
From: Bill Wendling <morbo@google.com>
To: kvm@vger.kernel.org
Cc: oupton@google.com, pbonzini@redhat.com, drjones@redhat.com,
        Bill Wendling <morbo@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Don't use the "noclone" attribute for clang as it's not supported.

Signed-off-by: Bill Wendling <morbo@google.com>
---
 x86/vmx_tests.c | 5 ++++-
 1 file changed, 4 insertions(+), 1 deletion(-)

```
#### [PATCH v4.6 09/36] KVM: s390: protvirt: Add initial vm and cpu lifecycle handling
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11406813
Return-Path: <SRS0=q2E5=4O=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 263F31395
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 26 Feb 2020 17:00:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D570224680
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 26 Feb 2020 17:00:29 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728259AbgBZRA2 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 26 Feb 2020 12:00:28 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:64290 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727933AbgBZRA2 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 26 Feb 2020 12:00:28 -0500
Received: from pps.filterd (m0098396.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 01QGnC1O009123;
        Wed, 26 Feb 2020 12:00:26 -0500
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2ydcntpv2y-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 26 Feb 2020 12:00:26 -0500
Received: from m0098396.ppops.net (m0098396.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 01QGo8wa012709;
        Wed, 26 Feb 2020 12:00:25 -0500
Received: from ppma03dal.us.ibm.com (b.bd.3ea9.ip4.static.sl-reverse.com
 [169.62.189.11])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2ydcntpv2a-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 26 Feb 2020 12:00:25 -0500
Received: from pps.filterd (ppma03dal.us.ibm.com [127.0.0.1])
        by ppma03dal.us.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 01QH032m021574;
        Wed, 26 Feb 2020 17:00:24 GMT
Received: from b01cxnp23032.gho.pok.ibm.com (b01cxnp23032.gho.pok.ibm.com
 [9.57.198.27])
        by ppma03dal.us.ibm.com with ESMTP id 2ydcmkrd3q-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 26 Feb 2020 17:00:24 +0000
Received: from b01ledav004.gho.pok.ibm.com (b01ledav004.gho.pok.ibm.com
 [9.57.199.109])
        by b01cxnp23032.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id 01QH0Mjj47186278
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 26 Feb 2020 17:00:22 GMT
Received: from b01ledav004.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 0999D112063;
        Wed, 26 Feb 2020 17:00:22 +0000 (GMT)
Received: from b01ledav004.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id D183511206E;
        Wed, 26 Feb 2020 17:00:21 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.114.17.106])
        by b01ledav004.gho.pok.ibm.com (Postfix) with ESMTP;
        Wed, 26 Feb 2020 17:00:21 +0000 (GMT)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: cohuck@redhat.com
Cc: Ulrich.Weigand@de.ibm.com, borntraeger@de.ibm.com,
        david@redhat.com, frankja@linux.ibm.com,
        frankja@linux.vnet.ibm.com, gor@linux.ibm.com,
        imbrenda@linux.ibm.com, kvm@vger.kernel.org,
        linux-s390@vger.kernel.org, mimu@linux.ibm.com, thuth@redhat.com
Subject: [PATCH v4.6 09/36] KVM: s390: protvirt: Add initial vm and cpu
 lifecycle handling
Date: Wed, 26 Feb 2020 12:00:20 -0500
Message-Id: <20200226170020.9061-1-borntraeger@de.ibm.com>
X-Mailer: git-send-email 2.25.0
In-Reply-To: <20200226175428.40143164.cohuck@redhat.com>
References: <20200226175428.40143164.cohuck@redhat.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-02-26_06:2020-02-26,2020-02-26 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 adultscore=0 lowpriorityscore=0 impostorscore=0 clxscore=1015
 malwarescore=0 spamscore=0 suspectscore=4 mlxscore=0 bulkscore=0
 phishscore=0 mlxlogscore=999 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-2001150001 definitions=main-2002260113
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Janosch Frank <frankja@linux.ibm.com>

This contains 3 main changes:
1. changes in SIE control block handling for secure guests
2. helper functions for create/destroy/unpack secure guests
3. KVM_S390_PV_COMMAND ioctl to allow userspace dealing with secure
machines

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
[borntraeger@de.ibm.com: patch merging, splitting, fixing]
Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---
 arch/s390/include/asm/kvm_host.h |  24 ++-
 arch/s390/include/asm/uv.h       |  69 ++++++++
 arch/s390/kvm/Makefile           |   2 +-
 arch/s390/kvm/kvm-s390.c         | 214 ++++++++++++++++++++++++-
 arch/s390/kvm/kvm-s390.h         |  33 ++++
 arch/s390/kvm/pv.c               | 267 +++++++++++++++++++++++++++++++
 include/uapi/linux/kvm.h         |  31 ++++
 7 files changed, 636 insertions(+), 4 deletions(-)
 create mode 100644 arch/s390/kvm/pv.c

```
#### [kvm-unit-tests PATCH 1/7] x86: emulator: use "SSE2" for the targetFrom: morbo@google.com
##### From: morbo@google.com

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Bill Wendling <morbo@google.com>
X-Patchwork-Id: 11405443
Return-Path: <SRS0=q2E5=4O=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5E9A014BC
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 26 Feb 2020 07:44:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 352F221D7E
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 26 Feb 2020 07:44:57 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="Mo7o+9Y/"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727278AbgBZHoy (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 26 Feb 2020 02:44:54 -0500
Received: from mail-pg1-f202.google.com ([209.85.215.202]:48905 "EHLO
        mail-pg1-f202.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726587AbgBZHoy (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 26 Feb 2020 02:44:54 -0500
Received: by mail-pg1-f202.google.com with SMTP id h14so1288318pgd.15
        for <kvm@vger.kernel.org>; Tue, 25 Feb 2020 23:44:52 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=6pHSqsqhtQpsZBK8Kdeyx8XvutwVtDm2Afb6gQYh6DM=;
        b=Mo7o+9Y/ti+/X/PgbqFLsbuMoAos1ylIUguffoKM/q1+tZMkkLiS3bKoF1Xt71eQMO
         SwH73Tf5agOP65C8J1jNOrAFkhHypCfXDmdtYlFy1SmGljB2ueHbz+GTszrV+ifKTkvm
         WcQAniJR0v19zRpV2RgFwQOZRqUonvbBc5l2lVK8+Zj7JeYSE8H4zos8gZWMattSJ7fK
         SGCF7Vg24sDbLa5RTqjLOJF4+PnKSpFR4GKiHJv+clh60Gl1qJjdCLwb5MipvQTYM3NZ
         VtakBEUOoGrQkTI98Ope7F59FyS9nhrfw1d2+jPL17TER4LUQedF786FMWAzSr7MWk27
         Yg7A==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=6pHSqsqhtQpsZBK8Kdeyx8XvutwVtDm2Afb6gQYh6DM=;
        b=pO1oCBQGZcdVC1lDf4aY2gaa8CnfqD56DopfNLwWd6/t3wT6rfpdmYUFQf/somqBWd
         00zOf6/O6DCxF5gA33c8nnSWxCnCvd4mzXVvIASfrb6AcnIn8oS9vt8dlc4jCUBLjSV4
         cPSsE9H/qWdKj/NK50J2TTtDfj6ThORJZbk4WywZcosyRLtXZGwFC7Su7ilhpD6qoUYq
         Tln8LDkuNqL3b1xrI9K9JafrocUc/pSNCFaAmKUSiVSiSkfVWQ4x6xdw5DEm1ySmIa0i
         m/Dc35KMAQDA88lrNeBKwPHjFnOkgQ8pfNhQMqwgy2Rn1J0vAhqwdqEMvQnE0dMPkz/4
         cXuQ==
X-Gm-Message-State: APjAAAVMJ5RFt6FNZBCs1IXCsxnioim2EY4jjaala1mi1R4O7U3puRrE
        uahij6XaARoZ8e2JI1DI+4H/sJIJdyejOEDwGAqpaW6qanjeerBlK301/itOPGYKq6yzM0AnECA
        U8kxRzBI403lUp1EDkP5466r1AkwS8CUCS3hEk0t5vUBYzZzUF/M0+Q==
X-Google-Smtp-Source: 
 APXvYqwaNVMvUNxZClWOF2TGyEiGmrzZMxTbrVTH2vXi7Z4vUDkf+R75cl/YWQFkXRVTZnDSna6Sg7oraQ==
X-Received: by 2002:a63:6d01:: with SMTP id i1mr2528728pgc.55.1582703091894;
 Tue, 25 Feb 2020 23:44:51 -0800 (PST)
Date: Tue, 25 Feb 2020 23:44:21 -0800
In-Reply-To: <20200226074427.169684-1-morbo@google.com>
Message-Id: <20200226074427.169684-2-morbo@google.com>
Mime-Version: 1.0
References: <20200226074427.169684-1-morbo@google.com>
X-Mailer: git-send-email 2.25.0.265.gbab2e86ba0-goog
Subject: [kvm-unit-tests PATCH 1/7] x86: emulator: use "SSE2" for the target
From: morbo@google.com
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, Bill Wendling <morbo@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Bill Wendling <morbo@google.com>

The movdqu and movapd instructions are SSE2 instructions. Clang
interprets the __attribute__((target("sse"))) as allowing SSE only
instructions. Using SSE2 instructions cause an error.

Signed-off-by: Bill Wendling <morbo@google.com>
---
 x86/emulator.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH 1/7] x86: emulator: use "SSE2" for the targetFrom: Bill Wendling <morbo@google.com>
##### From: Bill Wendling <morbo@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Bill Wendling <morbo@google.com>
X-Patchwork-Id: 11405757
Return-Path: <SRS0=q2E5=4O=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D48A71580
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 26 Feb 2020 09:44:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id AA38B24673
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 26 Feb 2020 09:44:43 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="YB4rwED4"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727574AbgBZJom (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 26 Feb 2020 04:44:42 -0500
Received: from mail-pf1-f202.google.com ([209.85.210.202]:38020 "EHLO
        mail-pf1-f202.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726764AbgBZJom (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 26 Feb 2020 04:44:42 -0500
Received: by mail-pf1-f202.google.com with SMTP id 203so1755220pfx.5
        for <kvm@vger.kernel.org>; Wed, 26 Feb 2020 01:44:40 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=UtzL/mOBJbhx1wqaitkgRIuidwcFWAMCohGe1UdpshI=;
        b=YB4rwED48l9nJfaTI5YVya96asUrFfT6Ic7DMgyUT8gXrA/y9a7VEAN68hI66ir1Iq
         andqqs41SMbE8G6wbHb4bD09HfYV6/gf9xzuHIQ/X+tOQ/SeVLbLoPAyCN/fjiriA576
         CYbclruU5fYRrooTgG2O7DXmCcKALKKuTbFT2szF7NVL3gfPSSaiKPuKwL4pPQGvpsNf
         qvyaisnLb9+iohMALrhE4pePkyiuNXPVIBrpDLXaXZspVneRBrVUDqWvyp7Be//VTdGV
         iwD5fOGUQRnLUVfqLoDHS1NeL04www9Ilz+Zn33KcgXx+cgCA7EMoM6L7hDZecm9ndb2
         +OdA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=UtzL/mOBJbhx1wqaitkgRIuidwcFWAMCohGe1UdpshI=;
        b=nBpD/EtFCMRRMLL3P1zQ77JfM6ezpFWa30mJhJQYM+wM+4PXKauKgDSI3BljETj/u6
         9IyifqOICLn2UN42esg1DOzzLE5aSQ7oOICwV6l7ziW73I+4h0saIJYph2XVy4m374+Q
         yfRyn+CqNZZJSKnKkPPDY9Byx/ZIAkjTfBesWYl99cnfqkz2X3rUaDiTxtGhiC+L7n2K
         mx7ZQjYdp2Yekn7nDm5CAZwIq35audmKcqYJEY0Z5ZsaAU5cH8gi5OR/vKg3wCOWn0Ra
         Q2Lqrg8Z7kDzj/4ElCliCLUHg3Fxts3UT2h+fw3+460Co7TXzPwNip7pisDenuesk8ZM
         rARg==
X-Gm-Message-State: APjAAAXANvKrOFSiRBaHfqQPERR3yKaeg8wREzX9ypG/7gBgK3eM0RTI
        YGblGEDXUaWU8qPwY6X51YrEqiNfVMoUpNYi6U/x5fgP553/+XG07S83EwUGmWrjQBq8ARGI/8y
        Ikbd2WW530a9Ixoqt2oc90f3Rq7PE/OnQc3pqof43HKo/jbfSh3q+WQ==
X-Google-Smtp-Source: 
 APXvYqwxT+4LC0iHQbbifqhH9DQSutpnUXG4GHzFGL9fE6shs+QQt21j0iJgs3w2V4KuNAYEzxY3oJNnmg==
X-Received: by 2002:a63:f0a:: with SMTP id e10mr2772684pgl.402.1582710279605;
 Wed, 26 Feb 2020 01:44:39 -0800 (PST)
Date: Wed, 26 Feb 2020 01:44:20 -0800
In-Reply-To: <20200226094433.210968-1-morbo@google.com>
Message-Id: <20200226094433.210968-2-morbo@google.com>
Mime-Version: 1.0
References: <20200226074427.169684-1-morbo@google.com>
 <20200226094433.210968-1-morbo@google.com>
X-Mailer: git-send-email 2.25.0.265.gbab2e86ba0-goog
Subject: [kvm-unit-tests PATCH 1/7] x86: emulator: use "SSE2" for the target
From: Bill Wendling <morbo@google.com>
To: kvm@vger.kernel.org
Cc: oupton@google.com, pbonzini@redhat.com, drjones@redhat.com,
        Bill Wendling <morbo@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The movdqu and movapd instructions are SSE2 instructions. Clang
interprets the __attribute__((target("sse"))) as allowing SSE only
instructions. Using SSE2 instructions cause an error.

Signed-off-by: Bill Wendling <morbo@google.com>
---
 x86/emulator.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH v3 1/7] x86: emulator: use "SSE2" for the target
##### From: Bill Wendling <morbo@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Bill Wendling <morbo@google.com>
X-Patchwork-Id: 11407133
Return-Path: <SRS0=q2E5=4O=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 70F80930
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 26 Feb 2020 20:13:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4252F24672
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 26 Feb 2020 20:13:07 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="tvBy16g+"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727335AbgBZUNG (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 26 Feb 2020 15:13:06 -0500
Received: from mail-pl1-f202.google.com ([209.85.214.202]:37197 "EHLO
        mail-pl1-f202.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727240AbgBZUNG (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 26 Feb 2020 15:13:06 -0500
Received: by mail-pl1-f202.google.com with SMTP id t12so350920plo.4
        for <kvm@vger.kernel.org>; Wed, 26 Feb 2020 12:13:05 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=RIB7zoLlqFIQoJvqoI2dpWIxGsE/dMGJkqPhxqkMWkE=;
        b=tvBy16g+l1UdG6TNTnJ2Mq7UwRcD9jLdze/j7ZtM8llI83AtzFBSamQCQiyvV9tzXO
         RNGdcZbVTTD5IKQWO52jRwmcXSVzX1tdhQpRiN+MAkYkr7WdFdn9ysBj5Tj9YFhi1GRM
         CNkHJWqNE3o78dnk0P/PxJXWHkr0cHEK01ah7suwahUnC8y41z0XP5A6fcRgUI13L/Sw
         OZqwlI6GWJB2AfC0DjfSYLCBpls74+4bst5xR4fE219ixvo/PQM0my+FAEtRX6RFbefv
         qU/Lgr0Akf6MLzyziSboAWjEPWos/PNrjNxZtVV1o6OZ30eVHW28XzLaODyXYLDK9ClN
         qJLw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=RIB7zoLlqFIQoJvqoI2dpWIxGsE/dMGJkqPhxqkMWkE=;
        b=BjW81TptoQV4F0I/ccPLPdTWTlhVaKzqCSdPejCDtfQmRcz+8VpP3NFJofNRvcFgoH
         3nSMjyX9v0sy/HOCXukbPDjACR07LexdntXM4IE5jemK7qh/g57imHoSViH8oxQFWT6x
         sOkROGlMWzjmIoIWlnlghaepGuexzxrfadjhNw2S+x4WIhwKpmJw44h/lGOi/NEPYjPs
         mliKBieqgZ4otBcsTo4f8xh8YZZPSecI7fwlbAMca2MLIpDFqmZkfGvH24vIgDjcsN+M
         bfKoPx/XJnuH0h1/7155jGMQj8MzHUW/lMbpw2bWIA4/WpbYKSDfHQ2DO/0UhnJVJmvq
         MkYg==
X-Gm-Message-State: APjAAAXuRtLT72FT8pmPnhYo6kzNhfi/HohxONE6uRIsztizu6XcMs1J
        HAA3HfWZgEdHDk8HKjAyPvHLsGIIXZGVNGE1b7RwUirakS0BukiH5uG3f2FXJAPq4UD5l3Y4o2B
        COC4NI9UvdLFW3i3ZVjt2ZsbTDnE/VM7wnQ73Xi0siMpmUEqYXUihnQ==
X-Google-Smtp-Source: 
 APXvYqy1OUTt879OCKhac5X76HmflHSqbTYXTIuLsgQzglZqBNOdO7pUAZ1q+tSVPLhqmJBM8B/eEFxjtQ==
X-Received: by 2002:a63:6101:: with SMTP id v1mr527939pgb.318.1582747985132;
 Wed, 26 Feb 2020 12:13:05 -0800 (PST)
Date: Wed, 26 Feb 2020 12:12:37 -0800
In-Reply-To: <20200226201243.86988-1-morbo@google.com>
Message-Id: <20200226201243.86988-2-morbo@google.com>
Mime-Version: 1.0
References: <20200226094433.210968-1-morbo@google.com>
 <20200226201243.86988-1-morbo@google.com>
X-Mailer: git-send-email 2.25.1.481.gfbce0eb801-goog
Subject: [kvm-unit-tests PATCH v3 1/7] x86: emulator: use "SSE2" for the
 target
From: Bill Wendling <morbo@google.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, oupton@google.com, drjones@redhat.com,
        Bill Wendling <morbo@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The movdqu and movapd instructions are SSE2 instructions. Clang
interprets the __attribute__((target("sse"))) as allowing SSE only
instructions. Using SSE2 instructions cause an error.

Signed-off-by: Bill Wendling <morbo@google.com>
---
 x86/emulator.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] KVM: Remove unecessary asm/kvm_host.h includes
##### From: Peter Xu <peterx@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11406629
Return-Path: <SRS0=q2E5=4O=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 94D5D92A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 26 Feb 2020 15:56:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 6A8B424670
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 26 Feb 2020 15:56:06 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="M0zCA2Z8"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728658AbgBZP4F (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 26 Feb 2020 10:56:05 -0500
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:25395 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1728073AbgBZP4F (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 26 Feb 2020 10:56:05 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1582732564;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=/g3Gs6VDiPT1QYPbL+OndFSLPCBMmybI6k/WRvA9aKw=;
        b=M0zCA2Z8dZWdjzUmCVf2MF7yiznfiRUlRv7B1gpxi3oaL+2EaWBHbYlw7ODw5qoLMR19Yu
        7YeZqGQF4XlXF1Z46sw4TtvgQPXwvsdPiulEOVeNBbMA/KiwQXYk1q8w65Za4xVlGlORVc
        ZC3k7T2leOtKG5FuXLqRh8K1D6a8tGo=
Received: from mail-qt1-f199.google.com (mail-qt1-f199.google.com
 [209.85.160.199]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-477-jP10h2vuOf64TZSv9bmu8w-1; Wed, 26 Feb 2020 10:56:01 -0500
X-MC-Unique: jP10h2vuOf64TZSv9bmu8w-1
Received: by mail-qt1-f199.google.com with SMTP id k20so4926580qtm.11
        for <kvm@vger.kernel.org>; Wed, 26 Feb 2020 07:56:01 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=/g3Gs6VDiPT1QYPbL+OndFSLPCBMmybI6k/WRvA9aKw=;
        b=kYre5zOGuRtKI1ZjNoxJp8rTiBb0uZQmRTzZKzSCPXy3EKnvIBiwe4Vu8ykzv0+hK9
         LqDWeqJq24JCU5CIIvYmUBCePHL7CHcZT0May9SIf6toIuxlWqHvmTkul6MtOiyRXZtB
         ExzhN3q+QEh20a5SYnNewokni0Sx4BdZdp6NEtvForjZTvktHr5aXoPsyV5XQ89xvrs1
         HkBFzS+eQgqdr8i4jj03f0FGrIgeBK5rOWGDmNWC0Q0QiD3NloNNcijQsHeJn2lU9wMt
         oG6wOwOXlMDXMpJ22dsEpPrX+x9pQxDMbrSBUjDQVT1UsV6d7KYn38fjhs3Fd5AWX+Ka
         RZrA==
X-Gm-Message-State: APjAAAXSlTeHL9Y/q7nRW0X+WasWbh2UUBHneKC/YmPZJoccb5lF+Fqc
        KrtzlvusrmEuunWJUi9pAmH/RSvQeQM1pTjZF+ZxvFFRwzkfigjDBVfgiamaTnTjZYBcBS4e0Vw
        HbBeIpW4fNZ58
X-Received: by 2002:a05:620a:42:: with SMTP id
 t2mr6812728qkt.45.1582732560690;
        Wed, 26 Feb 2020 07:56:00 -0800 (PST)
X-Google-Smtp-Source: 
 APXvYqxUtK+kn5dwXfcN05C4cimB/Hkd5ivHt4kkovs/4KfLs5Cjvj2XGzCzXVVOvLta6kthdvWhHA==
X-Received: by 2002:a05:620a:42:: with SMTP id
 t2mr6812699qkt.45.1582732560379;
        Wed, 26 Feb 2020 07:56:00 -0800 (PST)
Received: from xz-x1.redhat.com
 (CPEf81d0fb19163-CMf81d0fb19160.cpe.net.fido.ca. [72.137.123.47])
        by smtp.gmail.com with ESMTPSA id
 w134sm1307026qka.127.2020.02.26.07.55.59
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 26 Feb 2020 07:55:59 -0800 (PST)
From: Peter Xu <peterx@redhat.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>, jianjay.zhou@huawei.com,
        peterx@redhat.com
Subject: [PATCH] KVM: Remove unecessary asm/kvm_host.h includes
Date: Wed, 26 Feb 2020 10:55:58 -0500
Message-Id: <20200226155558.175021-1-peterx@redhat.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

linux/kvm_host.h and asm/kvm_host.h have a dependency in that the asm
header should be included first, then we can define arch-specific
macros in asm/ header and use "#ifndef" in linux/ header to define the
generic value of the macro.  One example is KVM_MAX_VCPU_ID.

Now in many C files we've got both the headers included, and
linux/kvm_host.h is included even earlier.  It's working only because
in linux/kvm_host.h we also included asm/kvm_host.h anyway so the
explicit inclusion of asm/kvm_host.h in the C files are meaningless.

To avoid the confusion, remove the asm/ header if the linux/ header is
included.

Signed-off-by: Peter Xu <peterx@redhat.com>
---
 arch/arm/kvm/coproc.c                | 1 -
 arch/arm64/kvm/fpsimd.c              | 1 -
 arch/arm64/kvm/guest.c               | 1 -
 arch/arm64/kvm/hyp/switch.c          | 1 -
 arch/arm64/kvm/sys_regs.c            | 1 -
 arch/arm64/kvm/sys_regs_generic_v8.c | 1 -
 arch/powerpc/kvm/book3s_64_vio.c     | 1 -
 arch/powerpc/kvm/book3s_64_vio_hv.c  | 1 -
 arch/powerpc/kvm/book3s_hv.c         | 1 -
 arch/powerpc/kvm/mpic.c              | 1 -
 arch/powerpc/kvm/powerpc.c           | 1 -
 arch/powerpc/kvm/timing.h            | 1 -
 arch/s390/kvm/intercept.c            | 1 -
 arch/x86/kvm/mmu/page_track.c        | 1 -
 virt/kvm/arm/psci.c                  | 1 -
 15 files changed, 15 deletions(-)

```
#### [kvm-unit-tests PATCH v2 1/7] x86: pmu: Test WRMSR on a running counter
##### From: Bill Wendling <morbo@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Bill Wendling <morbo@google.com>
X-Patchwork-Id: 11405761
Return-Path: <SRS0=q2E5=4O=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 603A81580
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 26 Feb 2020 09:44:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 3F7602467B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 26 Feb 2020 09:44:47 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="rhDAbplK"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727686AbgBZJop (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 26 Feb 2020 04:44:45 -0500
Received: from mail-pf1-f201.google.com ([209.85.210.201]:36687 "EHLO
        mail-pf1-f201.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726494AbgBZJop (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 26 Feb 2020 04:44:45 -0500
Received: by mail-pf1-f201.google.com with SMTP id 6so1758273pfv.3
        for <kvm@vger.kernel.org>; Wed, 26 Feb 2020 01:44:42 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=PBRYnIoV16uqyH4JmWNsaFktK3dmGET/qpGByqmujow=;
        b=rhDAbplKaH64XrsJAmvMtnimK/aTADpfEVX3NKDL1B6aeVZ+3VhNR+mTrXm90edO9n
         jRVtaMzwDoEyBi6xOdPGFv8Cd2AEi8E9SOmhDvsUH9edYFs+29+z9Iz7ytafGfBv8RYM
         etIUL9uhMmhTyRIdbvVWtaRGs9EN4pCKUjcVJMyrzSRMsCA9HLDUHdm+99/5EtWWa4RM
         9mH+5MOOJJay2phpDrdb6VZ7GmLd9EcPJ3KRcv9VJkcGTR2QEs6pY5UvCBD5f0UfGe5s
         7HK3Z2oPV9PtaDluKp8SnIu6DAIDS1uWx++BQL+ua+wAHE+e7001UpG2539AVWbpAr/2
         NpNg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=PBRYnIoV16uqyH4JmWNsaFktK3dmGET/qpGByqmujow=;
        b=P9dPpOEbOkxgEp8oN0yWux1wuqRY1JB2yGj6JFLWcN8Jgdcj9MVlh1HeOj9L/WLuXD
         PrZY0Jsqf1BUNZP87yV3Q0LboLPmFXO42e67l3drCjgUD1A0OhOqT+3O1Ux5ZeV+/Q7l
         qqMFBHED5neH8IUwLCecV6ir6/MqpERDOnkrW6jZsDNL2kLAFVdocV2pibUkYtU8LE3U
         RB5N1ghjNLWkzAvCxj+TshGTiFFNuE9xYvAP5pr2JMR0alRSBNqGRC6uwAIL1PrtAMml
         c519N5vY2anoJQF2M8sx7S+lW+qX8W/lJVWQlGEzYl3WWIlH+frTxEYdHejaoyf0aLS0
         JPGg==
X-Gm-Message-State: APjAAAW9LtGUSiPrmkEmvrAnffOHfldDVXwUjdRaR1VSEcLfcKkPBVpV
        YalxEmV9S6vjZCBfuZ1+D2AprIY8i6gcEf89YhDCxSWdgpnHXCtBNuVwkcYy4/b+yJobZt7o9NT
        BadNhVJ/TjdzO4ngasyEHYydB7G7p54dF/sdLX8x8ul0+o48ifAgzuw==
X-Google-Smtp-Source: 
 APXvYqwybOsPdYGUOXUMeRRh5YOjbhUYwb73Qj59M7gQNeQjD1IJSJ84ir742XGN3L9E8FM10rGu2bmnNA==
X-Received: by 2002:a65:40c8:: with SMTP id u8mr3040026pgp.188.1582710282232;
 Wed, 26 Feb 2020 01:44:42 -0800 (PST)
Date: Wed, 26 Feb 2020 01:44:21 -0800
In-Reply-To: <20200226094433.210968-1-morbo@google.com>
Message-Id: <20200226094433.210968-3-morbo@google.com>
Mime-Version: 1.0
References: <20200226074427.169684-1-morbo@google.com>
 <20200226094433.210968-1-morbo@google.com>
X-Mailer: git-send-email 2.25.0.265.gbab2e86ba0-goog
Subject: [kvm-unit-tests PATCH v2 1/7] x86: pmu: Test WRMSR on a running
 counter
From: Bill Wendling <morbo@google.com>
To: kvm@vger.kernel.org
Cc: oupton@google.com, pbonzini@redhat.com, drjones@redhat.com,
        Eric Hankland <ehankland@google.com>,
        Bill Wendling <morbo@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Eric Hankland <ehankland@google.com>

Ensure that the value of the counter was successfully set to 0 after
writing it while the counter was running.

Signed-off-by: Eric Hankland <ehankland@google.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Bill Wendling <morbo@google.com>
---
 x86/pmu.c | 16 ++++++++++++++++
 1 file changed, 16 insertions(+)

```
#### mm/gup/writeback: add callbacks for inaccessible pages: fixup for linux-next
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11406087
Return-Path: <SRS0=q2E5=4O=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 40A4092A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 26 Feb 2020 11:12:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1FAFF24689
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 26 Feb 2020 11:12:36 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728139AbgBZLMf (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 26 Feb 2020 06:12:35 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:49598 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726787AbgBZLMe (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 26 Feb 2020 06:12:34 -0500
Received: from pps.filterd (m0098420.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 01QBBb1J019705
        for <kvm@vger.kernel.org>; Wed, 26 Feb 2020 06:12:33 -0500
Received: from e06smtp03.uk.ibm.com (e06smtp03.uk.ibm.com [195.75.94.99])
        by mx0b-001b2d01.pphosted.com with ESMTP id 2ydcp8ayyu-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Wed, 26 Feb 2020 06:12:33 -0500
Received: from localhost
        by e06smtp03.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <borntraeger@de.ibm.com>;
        Wed, 26 Feb 2020 11:12:31 -0000
Received: from b06avi18878370.portsmouth.uk.ibm.com (9.149.26.194)
        by e06smtp03.uk.ibm.com (192.168.101.133) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Wed, 26 Feb 2020 11:12:28 -0000
Received: from d06av22.portsmouth.uk.ibm.com (d06av22.portsmouth.uk.ibm.com
 [9.149.105.58])
        by b06avi18878370.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 01QBCRcu37945602
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 26 Feb 2020 11:12:27 GMT
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 622EE4C044;
        Wed, 26 Feb 2020 11:12:27 +0000 (GMT)
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 333194C040;
        Wed, 26 Feb 2020 11:12:27 +0000 (GMT)
Received: from oc7455500831.ibm.com (unknown [9.152.224.219])
        by d06av22.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Wed, 26 Feb 2020 11:12:27 +0000 (GMT)
To: Andrew Morton <akpm@linux-foundation.org>,
        Claudio Imbrenda <imbrenda@linux.ibm.com>
Cc: linux-mm@kvack.org, kvm list <kvm@vger.kernel.org>,
        linux-s390 <linux-s390@vger.kernel.org>
From: Christian Borntraeger <borntraeger@de.ibm.com>
Subject: mm/gup/writeback: add callbacks for inaccessible pages: fixup for
 linux-next
Autocrypt: addr=borntraeger@de.ibm.com; prefer-encrypt=mutual; keydata=
 xsFNBE6cPPgBEAC2VpALY0UJjGmgAmavkL/iAdqul2/F9ONz42K6NrwmT+SI9CylKHIX+fdf
 J34pLNJDmDVEdeb+brtpwC9JEZOLVE0nb+SR83CsAINJYKG3V1b3Kfs0hydseYKsBYqJTN2j
 CmUXDYq9J7uOyQQ7TNVoQejmpp5ifR4EzwIFfmYDekxRVZDJygD0wL/EzUr8Je3/j548NLyL
 4Uhv6CIPf3TY3/aLVKXdxz/ntbLgMcfZsDoHgDk3lY3r1iwbWwEM2+eYRdSZaR4VD+JRD7p8
 0FBadNwWnBce1fmQp3EklodGi5y7TNZ/CKdJ+jRPAAnw7SINhSd7PhJMruDAJaUlbYaIm23A
 +82g+IGe4z9tRGQ9TAflezVMhT5J3ccu6cpIjjvwDlbxucSmtVi5VtPAMTLmfjYp7VY2Tgr+
 T92v7+V96jAfE3Zy2nq52e8RDdUo/F6faxcumdl+aLhhKLXgrozpoe2nL0Nyc2uqFjkjwXXI
 OBQiaqGeWtxeKJP+O8MIpjyGuHUGzvjNx5S/592TQO3phpT5IFWfMgbu4OreZ9yekDhf7Cvn
 /fkYsiLDz9W6Clihd/xlpm79+jlhm4E3xBPiQOPCZowmHjx57mXVAypOP2Eu+i2nyQrkapaY
 IdisDQfWPdNeHNOiPnPS3+GhVlPcqSJAIWnuO7Ofw1ZVOyg/jwARAQABzUNDaHJpc3RpYW4g
 Qm9ybnRyYWVnZXIgKDJuZCBJQk0gYWRkcmVzcykgPGJvcm50cmFlZ2VyQGxpbnV4LmlibS5j
 b20+wsF5BBMBAgAjBQJdP/hMAhsDBwsJCAcDAgEGFQgCCQoLBBYCAwECHgECF4AACgkQEXu8
 gLWmHHy/pA/+JHjpEnd01A0CCyfVnb5fmcOlQ0LdmoKWLWPvU840q65HycCBFTt6V62cDljB
 kXFFxMNA4y/2wqU0H5/CiL963y3gWIiJsZa4ent+KrHl5GK1nIgbbesfJyA7JqlB0w/E/SuY
 NRQwIWOo/uEvOgXnk/7+rtvBzNaPGoGiiV1LZzeaxBVWrqLtmdi1iulW/0X/AlQPuF9dD1Px
 hx+0mPjZ8ClLpdSp5d0yfpwgHtM1B7KMuQPQZGFKMXXTUd3ceBUGGczsgIMipZWJukqMJiJj
 QIMH0IN7XYErEnhf0GCxJ3xAn/J7iFpPFv8sFZTvukntJXSUssONnwiKuld6ttUaFhSuSoQg
 OFYR5v7pOfinM0FcScPKTkrRsB5iUvpdthLq5qgwdQjmyINt3cb+5aSvBX2nNN135oGOtlb5
 tf4dh00kUR8XFHRrFxXx4Dbaw4PKgV3QLIHKEENlqnthH5t0tahDygQPnSucuXbVQEcDZaL9
 WgJqlRAAj0pG8M6JNU5+2ftTFXoTcoIUbb0KTOibaO9zHVeGegwAvPLLNlKHiHXcgLX1tkjC
 DrvE2Z0e2/4q7wgZgn1kbvz7ZHQZB76OM2mjkFu7QNHlRJ2VXJA8tMXyTgBX6kq1cYMmd/Hl
 OhFrAU3QO1SjCsXA2CDk9MM1471mYB3CTXQuKzXckJnxHkHOwU0ETpw8+AEQAJjyNXvMQdJN
 t07BIPDtbAQk15FfB0hKuyZVs+0lsjPKBZCamAAexNRk11eVGXK/YrqwjChkk60rt3q5i42u
 PpNMO9aS8cLPOfVft89Y654Qd3Rs1WRFIQq9xLjdLfHh0i0jMq5Ty+aiddSXpZ7oU6E+ud+X
 Czs3k5RAnOdW6eV3+v10sUjEGiFNZwzN9Udd6PfKET0J70qjnpY3NuWn5Sp1ZEn6lkq2Zm+G
 9G3FlBRVClT30OWeiRHCYB6e6j1x1u/rSU4JiNYjPwSJA8EPKnt1s/Eeq37qXXvk+9DYiHdT
 PcOa3aNCSbIygD3jyjkg6EV9ZLHibE2R/PMMid9FrqhKh/cwcYn9FrT0FE48/2IBW5mfDpAd
 YvpawQlRz3XJr2rYZJwMUm1y+49+1ZmDclaF3s9dcz2JvuywNq78z/VsUfGz4Sbxy4ShpNpG
 REojRcz/xOK+FqNuBk+HoWKw6OxgRzfNleDvScVmbY6cQQZfGx/T7xlgZjl5Mu/2z+ofeoxb
 vWWM1YCJAT91GFvj29Wvm8OAPN/+SJj8LQazd9uGzVMTz6lFjVtH7YkeW/NZrP6znAwv5P1a
 DdQfiB5F63AX++NlTiyA+GD/ggfRl68LheSskOcxDwgI5TqmaKtX1/8RkrLpnzO3evzkfJb1
 D5qh3wM1t7PZ+JWTluSX8W25ABEBAAHCwV8EGAECAAkFAk6cPPgCGwwACgkQEXu8gLWmHHz8
 2w//VjRlX+tKF3szc0lQi4X0t+pf88uIsvR/a1GRZpppQbn1jgE44hgF559K6/yYemcvTR7r
 6Xt7cjWGS4wfaR0+pkWV+2dbw8Xi4DI07/fN00NoVEpYUUnOnupBgychtVpxkGqsplJZQpng
 v6fauZtyEcUK3dLJH3TdVQDLbUcL4qZpzHbsuUnTWsmNmG4Vi0NsEt1xyd/Wuw+0kM/oFEH1
 4BN6X9xZcG8GYUbVUd8+bmio8ao8m0tzo4pseDZFo4ncDmlFWU6hHnAVfkAs4tqA6/fl7RLN
 JuWBiOL/mP5B6HDQT9JsnaRdzqF73FnU2+WrZPjinHPLeE74istVgjbowvsgUqtzjPIG5pOj
 cAsKoR0M1womzJVRfYauWhYiW/KeECklci4TPBDNx7YhahSUlexfoftltJA8swRshNA/M90/
 i9zDo9ySSZHwsGxG06ZOH5/MzG6HpLja7g8NTgA0TD5YaFm/oOnsQVsf2DeAGPS2xNirmknD
 jaqYefx7yQ7FJXXETd2uVURiDeNEFhVZWb5CiBJM5c6qQMhmkS4VyT7/+raaEGgkEKEgHOWf
 ZDP8BHfXtszHqI3Fo1F4IKFo/AP8GOFFxMRgbvlAs8z/+rEEaQYjxYJqj08raw6P4LFBqozr
 nS4h0HDFPrrp1C2EMVYIQrMokWvlFZbCpsdYbBI=
Date: Wed, 26 Feb 2020 12:12:27 +0100
User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:68.0) Gecko/20100101
 Thunderbird/68.4.1
MIME-Version: 1.0
Content-Language: en-US
X-TM-AS-GCONF: 00
x-cbid: 20022611-0012-0000-0000-0000038A6941
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 20022611-0013-0000-0000-000021C70EDA
Message-Id: <1da2ebcf-59bd-65a1-222a-26af953ac7c5@de.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-02-26_03:2020-02-26,2020-02-26 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 adultscore=0
 lowpriorityscore=0 mlxlogscore=714 suspectscore=0 priorityscore=1501
 mlxscore=0 impostorscore=0 spamscore=0 clxscore=1015 malwarescore=0
 bulkscore=0 phishscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2001150001 definitions=main-2002260085
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Claudio,

the patch with the arch callbacks has a (simple) merge conflict with
the longterm pinning changes in next. Can you maybe re-do this patch
on top of linux-next and send this patch to Andrew. This actually 
also means that this patch should ideally go via Andrew and not via
my tree.

Patch is here.

https://git.kernel.org/pub/scm/linux/kernel/git/kvms390/linux.git/commit/?h=next&id=732b80e677b80813e2f862ce92448436540222a3

this is my quick attempt to fix this up

+++ b/mm/gup.c
@@@ -470,11 -269,18 +468,17 @@@ retry
                goto retry;
        }
  
 -      if (flags & FOLL_GET) {
 -              if (unlikely(!try_get_page(page))) {
 -                      page = ERR_PTR(-ENOMEM);
 -                      goto out;
 -              }
 -              ret = arch_make_page_accessible(page);
 -              if (ret) {
 -                      put_page(page);
 -                      page = ERR_PTR(ret);
 -                      goto out;
 -              }
 +      /* try_grab_page() does nothing unless FOLL_GET or FOLL_PIN is set. */
 +      if (unlikely(!try_grab_page(page, flags))) {
 +              page = ERR_PTR(-ENOMEM);
 +              goto out;
 +      }
++      ret = arch_make_page_accessible(page);
++      if (ret) {
++              put_page(page);
++              page = ERR_PTR(ret);
++              goto out;
+       }
        if (flags & FOLL_TOUCH) {
                if ((flags & FOLL_WRITE) &&
                    !pte_dirty(pte) && !PageDirty(page))

```
#### [PATCH net] vsock: fix potential deadlock in transport->release()
##### From: Stefano Garzarella <sgarzare@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stefano Garzarella <sgarzare@redhat.com>
X-Patchwork-Id: 11406011
Return-Path: <SRS0=q2E5=4O=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9FE4D930
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 26 Feb 2020 10:58:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 759D32468B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 26 Feb 2020 10:58:27 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="RHotRtlz"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728056AbgBZK60 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 26 Feb 2020 05:58:26 -0500
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:21107 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1727785AbgBZK6Z (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 26 Feb 2020 05:58:25 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1582714703;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=Ao4shkARYBOlBvwWDPYByOMa60o0c7ck0bB41Z0If+w=;
        b=RHotRtlz2HwjcRYuV3KsYRtyzp2Tm3L7DJxRx+CnmYtI1CnR6wlF/ZOp+bGVXtNy5EmfcA
        yQOHo+OD9/HnYdmVt3WABoeVCERCnqbMWD40XCgn7ef72byiRqaUDZECNXk/pXtA45lDk0
        rJyUeKd9eey5XZV9TAg8f4Qx1fubnhM=
Received: from mail-wm1-f71.google.com (mail-wm1-f71.google.com
 [209.85.128.71]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-258-WckLKU3WMMmV_tbPePJ6jA-1; Wed, 26 Feb 2020 05:58:22 -0500
X-MC-Unique: WckLKU3WMMmV_tbPePJ6jA-1
Received: by mail-wm1-f71.google.com with SMTP id m4so758413wmi.5
        for <kvm@vger.kernel.org>; Wed, 26 Feb 2020 02:58:22 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=Ao4shkARYBOlBvwWDPYByOMa60o0c7ck0bB41Z0If+w=;
        b=sdhvuj6+f0ZYWGokOKH1cbybi9bOs8uQd70k0L5PX2F6RKDU+8GXaDKYICGA7sAZ2c
         9UOFgAr03AZi+HuxyQzJMouH5kLiHT6dttDRPkTYX/wj1HvwkGabYb39ObzqdsyGpflP
         SWXQddqVXNo2x2g1YcYvnfjtwopdFaQmai61POON1fGtm7+D0lVahAvzp6zcf6ojhAhq
         N/r/93a+2sIXiVlgGvnC0heg0NYcCk9nDFE6Qyrw5Sg/Cz9NinZKFPMu1v7gUBKYFxZP
         DbKO5p7IwmKDVek69ZHuSGx8WCflk9v4QHL8Ltno45QPbJ8CI2S5B8rs6UBXBb4ZLdtg
         EgUg==
X-Gm-Message-State: APjAAAXCIsfV5QF1a0goiPDF3jiZd1kQxSIeb4zx+130+A/Qe6vVDXVG
        zxcPmBOF91P6+h813MFUuSSF8WyOH0Ye6UcJHyJMFwoWnzoEfaEHbK8ZY7sllPU3hbtC5gsK6tg
        8zFcuq8snY5LL
X-Received: by 2002:a5d:526c:: with SMTP id l12mr5137375wrc.117.1582714700516;
        Wed, 26 Feb 2020 02:58:20 -0800 (PST)
X-Google-Smtp-Source: 
 APXvYqyh+hNuja55nNfaQjP9nDbwKYYMHtCqsv8lSLIfOPeY/HkJFiCny/r2KQbRfkc32TKRz7Lunw==
X-Received: by 2002:a5d:526c:: with SMTP id l12mr5137321wrc.117.1582714700113;
        Wed, 26 Feb 2020 02:58:20 -0800 (PST)
Received: from steredhat.redhat.com
 (host209-4-dynamic.27-79-r.retail.telecomitalia.it. [79.27.4.209])
        by smtp.gmail.com with ESMTPSA id
 l132sm2619123wmf.16.2020.02.26.02.58.18
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 26 Feb 2020 02:58:19 -0800 (PST)
From: Stefano Garzarella <sgarzare@redhat.com>
To: davem@davemloft.net
Cc: Dexuan Cui <decui@microsoft.com>, Hillf Danton <hdanton@sina.com>,
        virtualization@lists.linux-foundation.org,
        "K. Y. Srinivasan" <kys@microsoft.com>, kvm@vger.kernel.org,
        Stephen Hemminger <sthemmin@microsoft.com>,
        syzbot+731710996d79d0d58fbc@syzkaller.appspotmail.com,
        netdev@vger.kernel.org, Sasha Levin <sashal@kernel.org>,
        Sunil Muthuswamy <sunilmut@microsoft.com>,
        Stefano Garzarella <sgarzare@redhat.com>,
        linux-kernel@vger.kernel.org, linux-hyperv@vger.kernel.org,
        Jakub Kicinski <kuba@kernel.org>,
        Haiyang Zhang <haiyangz@microsoft.com>,
        Stefan Hajnoczi <stefanha@redhat.com>,
        Jorgen Hansen <jhansen@vmware.com>
Subject: [PATCH net] vsock: fix potential deadlock in transport->release()
Date: Wed, 26 Feb 2020 11:58:18 +0100
Message-Id: <20200226105818.36055-1-sgarzare@redhat.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Some transports (hyperv, virtio) acquire the sock lock during the
.release() callback.

In the vsock_stream_connect() we call vsock_assign_transport(); if
the socket was previously assigned to another transport, the
vsk->transport->release() is called, but the sock lock is already
held in the vsock_stream_connect(), causing a deadlock reported by
syzbot:

    INFO: task syz-executor280:9768 blocked for more than 143 seconds.
      Not tainted 5.6.0-rc1-syzkaller #0
    "echo 0 > /proc/sys/kernel/hung_task_timeout_secs" disables this message.
    syz-executor280 D27912  9768   9766 0x00000000
    Call Trace:
     context_switch kernel/sched/core.c:3386 [inline]
     __schedule+0x934/0x1f90 kernel/sched/core.c:4082
     schedule+0xdc/0x2b0 kernel/sched/core.c:4156
     __lock_sock+0x165/0x290 net/core/sock.c:2413
     lock_sock_nested+0xfe/0x120 net/core/sock.c:2938
     virtio_transport_release+0xc4/0xd60 net/vmw_vsock/virtio_transport_common.c:832
     vsock_assign_transport+0xf3/0x3b0 net/vmw_vsock/af_vsock.c:454
     vsock_stream_connect+0x2b3/0xc70 net/vmw_vsock/af_vsock.c:1288
     __sys_connect_file+0x161/0x1c0 net/socket.c:1857
     __sys_connect+0x174/0x1b0 net/socket.c:1874
     __do_sys_connect net/socket.c:1885 [inline]
     __se_sys_connect net/socket.c:1882 [inline]
     __x64_sys_connect+0x73/0xb0 net/socket.c:1882
     do_syscall_64+0xfa/0x790 arch/x86/entry/common.c:294
     entry_SYSCALL_64_after_hwframe+0x49/0xbe

To avoid this issue, this patch remove the lock acquiring in the
.release() callback of hyperv and virtio transports, and it holds
the lock when we call vsk->transport->release() in the vsock core.

Reported-by: syzbot+731710996d79d0d58fbc@syzkaller.appspotmail.com
Fixes: 408624af4c89 ("vsock: use local transport when it is loaded")
Signed-off-by: Stefano Garzarella <sgarzare@redhat.com>
---
 net/vmw_vsock/af_vsock.c                | 20 ++++++++++++--------
 net/vmw_vsock/hyperv_transport.c        |  3 ---
 net/vmw_vsock/virtio_transport_common.c |  2 --
 3 files changed, 12 insertions(+), 13 deletions(-)

```
#### [PATCH] Revert "KVM: x86: enable -Werror"
##### From: Christoph Hellwig <hch@lst.de>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Christoph Hellwig <hch@lst.de>
X-Patchwork-Id: 11406583
Return-Path: <SRS0=q2E5=4O=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 504CB14BC
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 26 Feb 2020 15:39:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 2F2762468A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 26 Feb 2020 15:39:35 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=infradead.org header.i=@infradead.org header.b="VAxOAnW9"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728297AbgBZPjb (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 26 Feb 2020 10:39:31 -0500
Received: from bombadil.infradead.org ([198.137.202.133]:41394 "EHLO
        bombadil.infradead.org" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726148AbgBZPja (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 26 Feb 2020 10:39:30 -0500
DKIM-Signature: v=1; a=rsa-sha256; q=dns/txt; c=relaxed/relaxed;
        d=infradead.org; s=bombadil.20170209; h=Content-Transfer-Encoding:
        Content-Type:MIME-Version:Message-Id:Date:Subject:Cc:To:From:Sender:Reply-To:
        Content-ID:Content-Description:In-Reply-To:References;
        bh=WkRU+rCfqZmSiK2T/WyxuA5RO2CVcs+N/iUY+k8Bf6w=;
 b=VAxOAnW9pzTfuKbV+ZL+X4PvH1
        W9K6olNaZozucBl5tM0rP97/7AIiCC2wehQYtiI/3pg0Y9j5nWbKoAjIRAAlcsKP5Al3Zx0Flmkjp
        EPwKob8UwqDLMtoHWC1zXmmrnyoc1eWUeKk8mAvPerkADPxf2TZJOSPKuJfZZBcsra3bd3mFwTEYE
        7x6vQBzPwzNU9Z3zR9S5lvR2X0hxQgGfSFoTgqCnBtT3gZre3ddfhBgMcKUAmih2aLnT3mQrC+3WO
        /YC3vQ3BpKZkNLgbBr8ax0E1NRV+2nWLe87NfJqAm0qskdqxU4W93CDwBAPYtXpwC2J49SS/55Kon
        b+JOhB2w==;
Received: from [4.28.11.157] (helo=localhost)
        by bombadil.infradead.org with esmtpsa (Exim 4.92.3 #3 (Red Hat
 Linux))
        id 1j6ymY-0000Y3-7U; Wed, 26 Feb 2020 15:39:30 +0000
From: Christoph Hellwig <hch@lst.de>
To: torvalds@linux-foundation.org
Cc: kvm@vger.kernel.org, pbonzini@redhat.com,
        linux-kernel@vger.kernel.org
Subject: [PATCH] Revert "KVM: x86: enable -Werror"
Date: Wed, 26 Feb 2020 07:39:29 -0800
Message-Id: <20200226153929.786743-1-hch@lst.de>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
X-SRS-Rewrite: SMTP reverse-path rewritten from <hch@infradead.org> by
 bombadil.infradead.org. See http://www.infradead.org/rpr.html
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This reverts commit ead68df94d248c80fdbae220ae5425eb5af2e753.

Using the brain dead Werror flag fixes the build for me due to mostly
harmless KASAN or similar warnings:

arch/x86/kvm/x86.c: In function ‘kvm_timer_init’:
arch/x86/kvm/x86.c:7209:1: error: the frame size of 1112 bytes is larger than 1024 bytes [-Werror=frame-larger-than=]
 7209 | }

Feel free to add a CONFIG_WERROR if you care strong enough, but don't break
peoples builds for absolutely no good reason.

Signed-off-by: Christoph Hellwig <hch@lst.de>
---
 arch/x86/kvm/Makefile | 1 -
 1 file changed, 1 deletion(-)

```
#### [PATCH v3] KVM: LAPIC: Recalculate apic map in batch
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11405129
Return-Path: <SRS0=q2E5=4O=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 33D8414E3
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 26 Feb 2020 02:43:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id EEEED222C2
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 26 Feb 2020 02:43:36 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="pOChUaeg"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729618AbgBZCnd (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 25 Feb 2020 21:43:33 -0500
Received: from mail-pf1-f195.google.com ([209.85.210.195]:43787 "EHLO
        mail-pf1-f195.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728989AbgBZCnd (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 25 Feb 2020 21:43:33 -0500
Received: by mail-pf1-f195.google.com with SMTP id s1so622980pfh.10;
        Tue, 25 Feb 2020 18:43:32 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=hZA4u0VcAs2hGDMJ33Ka/j6vQozadffCnX1cmWtUmiQ=;
        b=pOChUaegSa+Z+ZNabbooCPT1GLG17w52SLUOdwLlrz8OaX7Q+Xn35vgCpdTSt+P4L7
         LcQBu2JuYeqJ8D8oleAMfpA1wOSYXrBZiufIMveQhXr7xhm1z846awXJKTzb6o3ZrkhG
         d5CrKcqnAxeZMHu/E+cvrrHHpaCJWEXxIeHjh2CfuE138fBYR/C1ssIZ4pdRPKi+cGoW
         rQYaStGiI8HrxYC/aTqBrVxAUROVWxVy7xe/zceb4doGYRZTOoCI+6z/+FmhjQ9pptjw
         D+YMRWFiY432/kAUKufQyCczz30B1Ol1iNmmcbwnS+HzdXu82lvenBXgm0TBJNbmNKwo
         qq4w==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=hZA4u0VcAs2hGDMJ33Ka/j6vQozadffCnX1cmWtUmiQ=;
        b=CyRd7IJiqBawIVgEvorZrdu8FnT56iCMg4v8G4hwgsEVe7jw2k9meJ4pO763Zx1eIY
         dL/yVCHNeGS7vwpUhjT1xwgSHxUZpQQu+2D4Vk/bUFi/juSm8r3frsQ08oZR7fuIjOWJ
         XeWFyEGdHqVbr46hJhbZeLHo24lzo7VsUWQNsTZyrxwMvd8gc05UlP67g8eQlZduxrJt
         t3m/P7M9fEl+OnG2QisJ8gtpTkKBr5uuVr2s9psMt9ornviKfMMzRL8DyE4cSRu4wPzk
         pM9pIR1tF38JnGOOpKi0KKDZY9bqw2GLlNCag18xplwUeDUHLT0wEWnEwGYfAE8JJjTL
         pMFw==
X-Gm-Message-State: APjAAAUZySuDqlRPdn7jhmA42hHKpzyprJpaVypzVzvpINSZL1sAvDsh
        4fJr7R4w4RUDqkcvNFeOXTMrLUJwkkfbYg==
X-Google-Smtp-Source: 
 APXvYqzOSBlJNiiistgKgmOEiGdvnog8jte8czKMOT8HacBKN2AkY4ZFWJRcmfjYaWkbJ4Ni7fZZ5Q==
X-Received: by 2002:a62:e414:: with SMTP id r20mr1862138pfh.154.1582685011211;
        Tue, 25 Feb 2020 18:43:31 -0800 (PST)
Received: from kernel.DHCP ([120.244.140.54])
        by smtp.googlemail.com with ESMTPSA id
 z16sm442771pff.125.2020.02.25.18.43.23
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-SHA bits=128/128);
        Tue, 25 Feb 2020 18:43:30 -0800 (PST)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>
Subject: [PATCH v3] KVM: LAPIC: Recalculate apic map in batch
Date: Wed, 26 Feb 2020 10:41:02 +0800
Message-Id: <1582684862-10880-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

In the vCPU reset and set APIC_BASE MSR path, the apic map will be recalculated 
several times, each time it will consume 10+ us observed by ftrace in my 
non-overcommit environment since the expensive memory allocate/mutex/rcu etc 
operations. This patch optimizes it by recaluating apic map in batch, I hope 
this can benefit the serverless scenario which can frequently create/destroy 
VMs. 

Before patch:

kvm_lapic_reset  ~27us

After patch:

kvm_lapic_reset  ~14us 

Observed by ftrace, improve ~48%.

Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
v2 -> v3:
 * move apic_map_dirty to kvm_arch
 * add the suggestions from Paolo

v1 -> v2:
 * add apic_map_dirty to kvm_lapic
 * error condition in kvm_apic_set_state, do recalcuate  unconditionally

 arch/x86/include/asm/kvm_host.h |  1 +
 arch/x86/kvm/lapic.c            | 46 ++++++++++++++++++++++++++++++++---------
 arch/x86/kvm/lapic.h            |  1 +
 arch/x86/kvm/x86.c              |  1 +
 4 files changed, 39 insertions(+), 10 deletions(-)

```
#### [PATCH V5 1/5] vhost: factor out IOTLB
##### From: Jason Wang <jasowang@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 11405325
Return-Path: <SRS0=q2E5=4O=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7D319138D
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 26 Feb 2020 06:07:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 37476222C2
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 26 Feb 2020 06:07:18 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="E7UeC4wL"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727102AbgBZGHB (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 26 Feb 2020 01:07:01 -0500
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:33680 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727031AbgBZGHB (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 26 Feb 2020 01:07:01 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1582697218;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=ml9H1AmRrIhm2m0bwg8M889YMUbt04Z+O1VPWamuLiM=;
        b=E7UeC4wLCtBzePL01gmtWXS+RW5a+oq2zQzID3mou053c0fJ8a+QcSHNZsiYbFO9DAdqkb
        Uv7e+KkrIoY9r86NElCP2aRzsy4+KbrPwMvkBUbWNPZcjT47kbibhyz4Z1Ymp6ijA4l9Ey
        JXj55/pkF7HK5CQk7aRsN1yq5DX3VZc=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-184-Dg1kHleFMQS3_q8IS43uZw-1; Wed, 26 Feb 2020 01:06:56 -0500
X-MC-Unique: Dg1kHleFMQS3_q8IS43uZw-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id E3C32107ACCD;
        Wed, 26 Feb 2020 06:06:53 +0000 (UTC)
Received: from jason-ThinkPad-X1-Carbon-6th.redhat.com
 (ovpn-13-217.pek2.redhat.com [10.72.13.217])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 5F42092966;
        Wed, 26 Feb 2020 06:05:54 +0000 (UTC)
From: Jason Wang <jasowang@redhat.com>
To: mst@redhat.com, linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org
Cc: tiwei.bie@intel.com, jgg@mellanox.com, maxime.coquelin@redhat.com,
        cunming.liang@intel.com, zhihong.wang@intel.com,
        rob.miller@broadcom.com, xiao.w.wang@intel.com,
        haotian.wang@sifive.com, lingshan.zhu@intel.com,
        eperezma@redhat.com, lulu@redhat.com, parav@mellanox.com,
        kevin.tian@intel.com, stefanha@redhat.com, rdunlap@infradead.org,
        hch@infradead.org, aadam@redhat.com, jiri@mellanox.com,
        shahafs@mellanox.com, hanand@xilinx.com, mhabets@solarflare.com,
        gdawar@xilinx.com, saugatm@xilinx.com, vmireyno@marvell.com,
        Jason Wang <jasowang@redhat.com>
Subject: [PATCH V5 1/5] vhost: factor out IOTLB
Date: Wed, 26 Feb 2020 14:04:52 +0800
Message-Id: <20200226060456.27275-2-jasowang@redhat.com>
In-Reply-To: <20200226060456.27275-1-jasowang@redhat.com>
References: <20200226060456.27275-1-jasowang@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch factors out IOTLB into a dedicated module in order to be
reused by other modules like vringh. User may choose to enable the
automatic retiring by specifying VHOST_IOTLB_FLAG_RETIRE flag to fit
for the case of vhost device IOTLB implementation.

Signed-off-by: Jason Wang <jasowang@redhat.com>
---
 MAINTAINERS                 |   1 +
 drivers/vhost/Kconfig       |   6 +
 drivers/vhost/Makefile      |   2 +
 drivers/vhost/net.c         |   2 +-
 drivers/vhost/vhost.c       | 221 +++++++++++-------------------------
 drivers/vhost/vhost.h       |  36 ++----
 drivers/vhost/vhost_iotlb.c | 171 ++++++++++++++++++++++++++++
 include/linux/vhost_iotlb.h |  45 ++++++++
 8 files changed, 303 insertions(+), 181 deletions(-)
 create mode 100644 drivers/vhost/vhost_iotlb.c
 create mode 100644 include/linux/vhost_iotlb.h

```
