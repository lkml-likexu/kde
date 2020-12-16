#### [PATCH kvmtool] pci: Deactivate BARs before reactivating
##### From: Sergey Temerkhanov <s.temerkhanov@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sergey Temerkhanov <s.temerkhanov@gmail.com>
X-Patchwork-Id: 11974927
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 37CC4C2BB9A
	for <kvm@archiver.kernel.org>; Tue, 15 Dec 2020 14:36:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0136222516
	for <kvm@archiver.kernel.org>; Tue, 15 Dec 2020 14:36:26 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729130AbgLOOgQ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 15 Dec 2020 09:36:16 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:43380 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729034AbgLOOgC (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 15 Dec 2020 09:36:02 -0500
Received: from mail-lf1-x144.google.com (mail-lf1-x144.google.com
 [IPv6:2a00:1450:4864:20::144])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 00A1BC06179C
        for <kvm@vger.kernel.org>; Tue, 15 Dec 2020 06:35:21 -0800 (PST)
Received: by mail-lf1-x144.google.com with SMTP id a9so39897024lfh.2
        for <kvm@vger.kernel.org>; Tue, 15 Dec 2020 06:35:21 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=jHo9eRpcVbowVem3+A/2C+0RJYKD+KBjZqYkwvwjgmE=;
        b=QLDx14aQMb+UuKM/FWXhNMbv+GprX9K9cAWs0Lz/YUFM/vjU3ojksLrIfKT7B1mtwA
         PHosrhOnnO86SbgKDJ2TP2YTgZ88oPLUQC6pGZArum3yvJyUwpWM0ecEXg/sv4QXPHG+
         1321P2lfo+/8Vj7UVfGVcPx1Uf5cFVKQEnDV8Kf9Rb9muBKt1HHZVSeE2oXVuZMgQ9mR
         XLzx/SdL2L/jYkBUc5CCuQnY9Sxwmyd8Cu0u05YUBDxmSKAqfE+Et3UDIeLtbaMqLtwq
         14VER2XtOYtSORk2jGXjSoc9upbmLHBdVu1w+KdeTwH4kH2J2QB16ppis8i3ry5MgWAt
         1TGg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=jHo9eRpcVbowVem3+A/2C+0RJYKD+KBjZqYkwvwjgmE=;
        b=gECbPIrHtQuqz2Q0eUKqARs0M2fgEkNDGMk6w59W4j5QGodqGBNR+rHcbnQOxmcrO1
         uxdjQI4i5WoRGLoWXfVS84YAsTvWQ0kl+CnnVJka/HUww/UIZ6Z7HdigCn/2hqXjh8i7
         smcX4u5cbf+BYISSfuY0N2EiEjV0kYMrPfxjjT637gjSPR6KK0nY74mlfCFZ7fS5oN9F
         cbsS/TuzCjqEanuss1U0ExGLKt9hO6d6267q7WKGV3HHzAJKSQnQJW/QQ8c1eAaMJdxm
         jrEQtU7AqNbfLYsM4YigEt0Gnr+UpDQZaTYXDRSXE/7fn/W2fRrKhfznMWrHlir4V7r4
         4KxQ==
X-Gm-Message-State: AOAM530izVKyUlVbWW8DOveGHlrOQhkwWRu1mzNB2FCbBB1q8fPhVSRN
        DBud51HhDtbTSGeI2nM3rBhsXUDHMEsmsRm1
X-Google-Smtp-Source: 
 ABdhPJw8N1OdDLRB1QGHnXvUDAFeNKyzffcK4rvBCFsVaBdj1x3PfYRv8RT1fxhIB4FWawiAeU1nkg==
X-Received: by 2002:a2e:7c01:: with SMTP id x1mr8676155ljc.397.1608042919073;
        Tue, 15 Dec 2020 06:35:19 -0800 (PST)
Received: from localhost.localdomain (109-252-202-142.dynamic.spd-mgts.ru.
 [109.252.202.142])
        by smtp.gmail.com with ESMTPSA id
 o26sm2365749ljg.55.2020.12.15.06.35.18
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 15 Dec 2020 06:35:18 -0800 (PST)
From: Sergey Temerkhanov <s.temerkhanov@gmail.com>
To: kvm@vger.kernel.org, Will Deacon <will@kernel.org>,
        Julien Thierry <julien.thierry.kdev@gmail.com>
Cc: Sergey Temerkhanov <s.temerkhanov@gmail.com>
Subject: [PATCH kvmtool] pci: Deactivate BARs before reactivating
Date: Tue, 15 Dec 2020 17:35:12 +0300
Message-Id: <20201215143512.559367-1-s.temerkhanov@gmail.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Deactivate BARs before reactivating them to avoid breakage.
Some firmware components do not check whether the COMMAND
register contains any values before writing BARs which leads
to kvmtool errors during subsequent BAR deactivation

Signed-off-by: Sergey Temerkhanov <s.temerkhanov@gmail.com>
---
 pci.c | 4 ----
 1 file changed, 4 deletions(-)

```
#### [PATCH v2 01/24] target/mips/translate: Extract decode_opc_legacy() from decode_opc()
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <f4bug@amsat.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
 <f4bug@amsat.org>
X-Patchwork-Id: 11975911
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7719AC2BB48
	for <kvm@archiver.kernel.org>; Tue, 15 Dec 2020 22:58:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 41FA022D05
	for <kvm@archiver.kernel.org>; Tue, 15 Dec 2020 22:58:50 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727952AbgLOW6r (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 15 Dec 2020 17:58:47 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:37584 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726181AbgLOW6r (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 15 Dec 2020 17:58:47 -0500
Received: from mail-ej1-x643.google.com (mail-ej1-x643.google.com
 [IPv6:2a00:1450:4864:20::643])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 242B6C061793
        for <kvm@vger.kernel.org>; Tue, 15 Dec 2020 14:58:07 -0800 (PST)
Received: by mail-ej1-x643.google.com with SMTP id j22so12047867eja.13
        for <kvm@vger.kernel.org>; Tue, 15 Dec 2020 14:58:07 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=eBR/KP1XMbhrcgssotJd4G/2avIMrBZMV7G4WmoiWo8=;
        b=YrR0Z5DqkFBEJMEr1NVzef+bcwtTkoahx68HU/I9evKCqeSbblFgtzi4VwkRteuGlB
         alrA8YVrKnFX+Qmh04SBwbi4UktTCu8JTa5GIZoLuSqedrTqamgZjvge9k/ZMuj6RZv9
         0RmgIsSUZFdr60RFQPWxo20uMyRah+OAv4Hg0lBOEJrNCJXPTkVex4JsV7Td9l1UrgH8
         18sLjhIGG44a2+kwmIh29I3kxxH6eUDWLFp+NT3KAxoazrkdaDiEpHpw4+vvcikbRRB9
         Hpab1AIgsyW6ZGURc5Qrd31/2aT5JgQyU4ESaIVP0R1q+at+GxzUWO0g1NhFgG7SS0xd
         o/Zg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id
         :in-reply-to:references:mime-version:content-transfer-encoding;
        bh=eBR/KP1XMbhrcgssotJd4G/2avIMrBZMV7G4WmoiWo8=;
        b=UdWRhzdeQzwrgw/Zo8zW3JAkbuSjJ1QVRaKys5WZMm8dk5qcTSdFQtgQ1evx5D6lkg
         TSzrONUnbbx/ziO4fBd76oH2Ac+7c8nkmlXotzAimpUrJiOk9zpS1WZfeXoKSBJnNa8s
         qxDs4ulVZMWRnswXUUDkb7AL+THe8CN6Gmcc3zPPkLCWvWmmtvkLA8NnbujwCTVQzqSL
         8/sxamq82Vy35vcdvcfj6pDm7jb+O/MsnF/lzo9IfUinEGhiXKqgkZ4EEdUrxFYP3caE
         QDTxJQ8a2xYkDew+2YIePirBNXRGR5X23rBU/Clah6hoeoHssaXdgeSVL83ku/IKxJHC
         zRPg==
X-Gm-Message-State: AOAM5311oTzyDKj3UdTKLjHxLPbreKpNtkwtVrOHZf44kIQnQ71hZMQ/
        QOW0JzFzwAyHK7zE+lYn6tU=
X-Google-Smtp-Source: 
 ABdhPJw8ylReeQsh/8yN74nzFbXTfd16F9/1BaCqotQgh4xKhIEOL+x+fifCJ+4D13ea5/hOaaDSYg==
X-Received: by 2002:a17:906:4a4f:: with SMTP id
 a15mr29198657ejv.541.1608073085939;
        Tue, 15 Dec 2020 14:58:05 -0800 (PST)
Received: from x1w.redhat.com (101.red-88-21-206.staticip.rima-tde.net.
 [88.21.206.101])
        by smtp.gmail.com with ESMTPSA id
 o33sm19828818edd.50.2020.12.15.14.58.04
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 15 Dec 2020 14:58:05 -0800 (PST)
Sender: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
  <philippe.mathieu.daude@gmail.com>
From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <f4bug@amsat.org>
To: Richard Henderson <richard.henderson@linaro.org>,
        qemu-devel@nongnu.org
Cc: kvm@vger.kernel.org, Aleksandar Rikalo <aleksandar.rikalo@syrmia.com>,
 Paolo Bonzini <pbonzini@redhat.com>, Aurelien Jarno <aurelien@aurel32.net>,
 Jiaxun Yang <jiaxun.yang@flygoat.com>, =?utf-8?q?Philippe_Mathieu-Daud?=
	=?utf-8?q?=C3=A9?= <f4bug@amsat.org>, Huacai Chen <chenhuacai@kernel.org>
Subject: [PATCH v2 01/24] target/mips/translate: Extract decode_opc_legacy()
 from decode_opc()
Date: Tue, 15 Dec 2020 23:57:34 +0100
Message-Id: <20201215225757.764263-2-f4bug@amsat.org>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20201215225757.764263-1-f4bug@amsat.org>
References: <20201215225757.764263-1-f4bug@amsat.org>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

As we will slowly move to decodetree generated decoders,
extract the legacy decoding from decode_opc(), so new
decoders are added in decode_opc() while old code is
removed from decode_opc_legacy().

Signed-off-by: Philippe Mathieu-Daudé <f4bug@amsat.org>
---
 target/mips/translate.c | 45 ++++++++++++++++++++++++-----------------
 1 file changed, 26 insertions(+), 19 deletions(-)

```
#### [PATCH V2] kvm: check tlbs_dirty directly
##### From: Lai Jiangshan <jiangshanlai@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Lai Jiangshan <jiangshanlai@gmail.com>
X-Patchwork-Id: 11974861
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 16F03C4361B
	for <kvm@archiver.kernel.org>; Tue, 15 Dec 2020 13:53:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CD2F7224B8
	for <kvm@archiver.kernel.org>; Tue, 15 Dec 2020 13:53:35 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728904AbgLONxG (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 15 Dec 2020 08:53:06 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:36666 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728010AbgLONxG (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 15 Dec 2020 08:53:06 -0500
Received: from mail-pj1-x1041.google.com (mail-pj1-x1041.google.com
 [IPv6:2607:f8b0:4864:20::1041])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id C1896C06179C;
        Tue, 15 Dec 2020 05:52:25 -0800 (PST)
Received: by mail-pj1-x1041.google.com with SMTP id iq13so1246210pjb.3;
        Tue, 15 Dec 2020 05:52:25 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=kA8Dwcq079V/BJPEpdlGaQgTJviaipiaUEGQZv3ilX8=;
        b=daoTMTDrO6Fl4hCPzcXNElDZryGJXL62M45+T1ejKcPGICQMEA6H3bAEC61eqISyXJ
         jGEIYG0WB4KaOhEHWsZQlA5JvR9eRijwjcZNF+1GngNN6B1aFJg+jhz67K9qaaMilDz6
         AnXtO3LfNOuyTWA2DiWycSYA6wk5eaMQbe8QfUTmsdrUFkPzyPQ3twFdaCRiFNMEL5TX
         G3eeURYq79byly8utQxZ4vwHvXHakwBUpp/RxRbkOCszAJdPv4BanQGB1NmxYfrmaffc
         ucsAguqzRSAKTl+iZPTELMWIua7BSwizb0SrOvAeDaSDUfAGi5bpGBVkPJj+nH/fUPcv
         FdMA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=kA8Dwcq079V/BJPEpdlGaQgTJviaipiaUEGQZv3ilX8=;
        b=aNsJ6qJdDc2rbbvW1OYruw2ucBW+XLzBQiF2bwUwuc4lf1toyr+n8BnGnH6nBPcSDP
         SuL8eBnYut3TAuZuvJYtRpnJGMuIn30mGv3pIq/G9mpZgBRz9tHHoD8GWOOdVHNr1HvH
         PbhQtbpJkKMgMR+bdDVy8EsfrVNgSsAeml/6bPB4TdB8cckrdaHRvC69YshBdx4Fa3Hs
         B3T2dGNnhmiMIzSrO6bleMjY2HgLJBjf8zEv0Cl17Z53MBxlS/ZsEhgVwrKmZA1Dj+os
         dfgy/iqXIw6AF/BG3MMD6J1Xib3egJS7ce/rfOFxnjx45Ur3BUhxHeYV2WseReimVHz6
         o3gg==
X-Gm-Message-State: AOAM532vUp3+ZWiBOJ977KRvXTqFn5ledFVG23vMmXcAsWe04Migj2D5
        0UcIGBRcE2ky4cX7mN2mORKPdMjw9pD4lw==
X-Google-Smtp-Source: 
 ABdhPJw0R9lG114WLwNTwfAx6zsDTaCbuaJEOOvbsRp076YUCHHb3kSKWTKR0C/HtM2Eid2CmO60mQ==
X-Received: by 2002:a17:90a:f404:: with SMTP id
 ch4mr29284264pjb.78.1608040345186;
        Tue, 15 Dec 2020 05:52:25 -0800 (PST)
Received: from localhost ([198.11.176.14])
        by smtp.gmail.com with ESMTPSA id
 b1sm22000363pjh.54.2020.12.15.05.52.24
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Tue, 15 Dec 2020 05:52:24 -0800 (PST)
From: Lai Jiangshan <jiangshanlai@gmail.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Lai Jiangshan <laijs@linux.alibaba.com>, stable@vger.kernel.org
Subject: [PATCH V2] kvm: check tlbs_dirty directly
Date: Tue, 15 Dec 2020 22:52:59 +0800
Message-Id: <20201215145259.18684-1-jiangshanlai@gmail.com>
X-Mailer: git-send-email 2.19.1.6.gb485710b
In-Reply-To: <ea0938d2-f766-99de-2019-9daf5798ccac@redhat.com>
References: <ea0938d2-f766-99de-2019-9daf5798ccac@redhat.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Lai Jiangshan <laijs@linux.alibaba.com>

In kvm_mmu_notifier_invalidate_range_start(), tlbs_dirty is used as:
        need_tlb_flush |= kvm->tlbs_dirty;
with need_tlb_flush's type being int and tlbs_dirty's type being long.

It means that tlbs_dirty is always used as int and the higher 32 bits
is useless.  We need to check tlbs_dirty in a correct way and this
change checks it directly without propagating it to need_tlb_flush.

And need_tlb_flush is changed to boolean because it is used as a
boolean and its name starts with "need".

Note: it's _extremely_ unlikely this neglecting of higher 32 bits can
cause problems in practice.  It would require encountering tlbs_dirty
on a 4 billion count boundary, and KVM would need to be using shadow
paging or be running a nested guest.

Cc: stable@vger.kernel.org
Fixes: a4ee1ca4a36e ("KVM: MMU: delay flush all tlbs on sync_page path")
Signed-off-by: Lai Jiangshan <laijs@linux.alibaba.com>
---
Changed from V1:
	Update the patch and the changelog as Sean Christopherson suggested.

 virt/kvm/kvm_main.c | 10 +++++-----
 1 file changed, 5 insertions(+), 5 deletions(-)

```
#### [PATCH 1/3] asm-generic/atomic: Add try_cmpxchg64() instrumentation
##### From: Uros Bizjak <ubizjak@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Uros Bizjak <ubizjak@gmail.com>
X-Patchwork-Id: 11975581
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 952E4C4361B
	for <kvm@archiver.kernel.org>; Tue, 15 Dec 2020 18:29:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 61F5A22B2D
	for <kvm@archiver.kernel.org>; Tue, 15 Dec 2020 18:29:45 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731564AbgLOS3i (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 15 Dec 2020 13:29:38 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:51258 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1731330AbgLOS3h (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 15 Dec 2020 13:29:37 -0500
Received: from mail-ed1-x52b.google.com (mail-ed1-x52b.google.com
 [IPv6:2a00:1450:4864:20::52b])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id E830AC06179C;
        Tue, 15 Dec 2020 10:28:26 -0800 (PST)
Received: by mail-ed1-x52b.google.com with SMTP id v22so22079662edt.9;
        Tue, 15 Dec 2020 10:28:26 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=BxbWIyImdzA25H+jox/xdDou7lPmQDmqOAV4NhorkHw=;
        b=anIFo0HqTUq6Q8OaS1iLz+7sCpz1Y4IOXhJShH09+NYu0z9Rr0qoEuOoDxbrJ7gzyb
         2a62VVwMNDulYctUXaNPfBDjKX50+5yIqhSUXnJz/cZefSNG7nlkbHKbWCvjt5cg+jY1
         6TeVsaZa2rrMsBB0GnJXUNPw7kKlXJkMOJpiucQdaCgmg/ooxGyzw6hViXA2EnW000j/
         M4rvd0QxEI7vCFFRXZYNvc2sx43swlLmKhMKkxtojgpTrNQI9qt1pbbKo2PgtNTAhhdp
         PDvIBld6sAdaVONM7RLJ/oPYJZSpWwzvaHHcxhLpE5hP8d4J+wc3uucVsI5eQlzWTfvZ
         gKgA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=BxbWIyImdzA25H+jox/xdDou7lPmQDmqOAV4NhorkHw=;
        b=BzlUoHHgyrlTkMykKVGgrGLMvb0VAswGgLfCaPDpUwKWaw152NF0ZQV3+3SBARhZY6
         +GsmCujFEceapsgEi7cRQU3H1PDvHPT76iy/jNw496Q5bMZ8tbVPWAyZncy2i8JVQ2Db
         +Ya/S+ygi6b3hweRL5RDZxYSu8su4l55ZOkp0WGxu+m/JrpYzaQrAR4ihS9U4kPGX2Qk
         YXoNiP7amzigEN5x1jL9tbSEnf3Xcxw+Do3AtMR5nwRcKFa8D86gFGg8mg52n99/NcPN
         Gn4CJpmmbomk6I8z15DTLbupgNaMxSNDlNWXS/ue2298v6KTuoa852Qk7X10+V/3X32O
         wuMQ==
X-Gm-Message-State: AOAM533+3qzm9gOx5NGwjK31UM5o+A/Bmpka2vPOjLCVBgfjtb3Bwd92
        HH/2tubl7bQWssQeehawH14=
X-Google-Smtp-Source: 
 ABdhPJyox0k1n+HV1FwaAD5wwobWoXwd0wa0XsldkrCgtmGdlyI4j0i36Yg+iy3nzoqOjwxlEchmOQ==
X-Received: by 2002:aa7:d750:: with SMTP id
 a16mr31144433eds.252.1608056905681;
        Tue, 15 Dec 2020 10:28:25 -0800 (PST)
Received: from localhost.localdomain (93-103-18-160.static.t-2.net.
 [93.103.18.160])
        by smtp.gmail.com with ESMTPSA id
 r21sm7369228eds.91.2020.12.15.10.28.24
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 15 Dec 2020 10:28:25 -0800 (PST)
From: Uros Bizjak <ubizjak@gmail.com>
To: x86@kernel.org, kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: Uros Bizjak <ubizjak@gmail.com>, Will Deacon <will@kernel.org>,
        Peter Zijlstra <peterz@infradead.org>,
        Boqun Feng <boqun.feng@gmail.com>
Subject: [PATCH 1/3] asm-generic/atomic: Add try_cmpxchg64() instrumentation
Date: Tue, 15 Dec 2020 19:28:03 +0100
Message-Id: <20201215182805.53913-2-ubizjak@gmail.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20201215182805.53913-1-ubizjak@gmail.com>
References: <20201215182805.53913-1-ubizjak@gmail.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Instrument try_cmpxchg64() similar to try_cmpxchg().

Signed-off-by: Uros Bizjak <ubizjak@gmail.com>
Cc: Will Deacon <will@kernel.org>
Cc: Peter Zijlstra <peterz@infradead.org>
Cc: Boqun Feng <boqun.feng@gmail.com>
---
 include/asm-generic/atomic-instrumented.h | 46 ++++++++++++++++++++++-
 scripts/atomic/gen-atomic-instrumented.sh |  2 +-
 2 files changed, 46 insertions(+), 2 deletions(-)

```
