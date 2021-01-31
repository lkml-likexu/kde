#### [PATCH v5 01/11] exec: Restrict TCG specific headers
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <f4bug@amsat.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
 <f4bug@amsat.org>
X-Patchwork-Id: 12056723
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C4841C433E6
	for <kvm@archiver.kernel.org>; Sat, 30 Jan 2021 01:56:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 82A6464E0C
	for <kvm@archiver.kernel.org>; Sat, 30 Jan 2021 01:56:33 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233110AbhA3BzC (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 29 Jan 2021 20:55:02 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:46262 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S232798AbhA3BxV (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 29 Jan 2021 20:53:21 -0500
Received: from mail-wr1-x430.google.com (mail-wr1-x430.google.com
 [IPv6:2a00:1450:4864:20::430])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id C066FC06174A
        for <kvm@vger.kernel.org>; Fri, 29 Jan 2021 17:52:36 -0800 (PST)
Received: by mail-wr1-x430.google.com with SMTP id g10so10624810wrx.1
        for <kvm@vger.kernel.org>; Fri, 29 Jan 2021 17:52:36 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=TWOO2zfu8P4UM754zwKeQRqNcelSJ+Vi3BwaB87IrgI=;
        b=EZ4R0A6K45GJEpt3ikVxK/mZ5uOp/qSvLKwjO7LS5PbjeX+3sWdmNlr+4p56lnPtqL
         CUdY1yW1rTe7NWAKG6FtSRNNZKnZUAI2VEHfT9t/GySrE8ds9BQbysvGJYiW2faVZNpm
         DGZ+2ZzDYpOjHkDu0jST31KidNc+L9/fohOoZJZMRjKENmO2boj+1Bne8nOdoKsZZOk2
         hms4LiJZ9snctfQC29BzW0EhHYsmNCX7dzY+CxfZJyC29i8WBBxcI2hmd0NS7su5sU/F
         vCixTZjkQ3F8hOmBQQBzuo5d3mfiya1x/ZzCDk9XbkWe7CW7UiXUFmxJzINuRhOtpEh6
         vHGA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id
         :in-reply-to:references:mime-version:content-transfer-encoding;
        bh=TWOO2zfu8P4UM754zwKeQRqNcelSJ+Vi3BwaB87IrgI=;
        b=CbN8iVsVgsaJMV15gM3hgmUA3LHo514arjKMVZctXaQIhp26L69dQH45Vhqkb7BD/X
         NjiNYn8C6BzUpBzQ+ofZFf25vJS1jycaObQqDauLUBCsdfLK7/ki7SOXOleTdsRmIMrT
         SzeO5GhDUBeH1M50KViTYOlGdvA3PrmqWLfHdPlB+iMZURAGGQgBp5+ohxPbm5ZO3AkP
         Uqtr1hY+twv2W2USymj36kz9eIYiu8gGb6VccT74le2D2SO3iyparAYT+bTch1uJlg2u
         N0s1FgRnZ3KQ0jq6xbhfluLRTacNobKsNtjDEc6rUkzWeOQFqaMIBavvNM3sUIPVnshs
         RiQw==
X-Gm-Message-State: AOAM533MUKJigGXr4rsY3cZ/HyUTqnbgpbee3rdn7x2HYAf+rCoEqLcu
        GM3kk0Yh4jnYoNOK8FEND7Y=
X-Google-Smtp-Source: 
 ABdhPJwm3L7bSc0x4zKW4ljahz5/V9fkUWnJDpwudDy2IcbG2e/6dOTMtKI7Na8SK+4UY4kLg/lEbg==
X-Received: by 2002:adf:e4c9:: with SMTP id v9mr7191301wrm.277.1611971555621;
        Fri, 29 Jan 2021 17:52:35 -0800 (PST)
Received: from localhost.localdomain (13.red-83-57-169.dynamicip.rima-tde.net.
 [83.57.169.13])
        by smtp.gmail.com with ESMTPSA id
 u14sm11707719wml.19.2021.01.29.17.52.34
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 29 Jan 2021 17:52:35 -0800 (PST)
Sender: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
  <philippe.mathieu.daude@gmail.com>
From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <f4bug@amsat.org>
To: qemu-devel@nongnu.org
Cc: Richard Henderson <richard.henderson@linaro.org>, kvm@vger.kernel.org,
 Peter Maydell <peter.maydell@linaro.org>, Fam Zheng <fam@euphon.net>,
 Thomas Huth <thuth@redhat.com>, Paolo Bonzini <pbonzini@redhat.com>,
	=?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>,
 Richard Henderson <rth@twiddle.net>, Claudio Fontana <cfontana@suse.de>,
	=?utf-8?q?Alex_Benn=C3=A9e?= <alex.bennee@linaro.org>, qemu-arm@nongnu.org,
	=?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <f4bug@amsat.org>
Subject: [PATCH v5 01/11] exec: Restrict TCG specific headers
Date: Sat, 30 Jan 2021 02:52:17 +0100
Message-Id: <20210130015227.4071332-2-f4bug@amsat.org>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20210130015227.4071332-1-f4bug@amsat.org>
References: <20210130015227.4071332-1-f4bug@amsat.org>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Fixes when building with --disable-tcg:

  In file included from target/arm/helper.c:16:
  include/exec/helper-proto.h:42:10: fatal error: tcg-runtime.h: No such file or directory
     42 | #include "tcg-runtime.h"
        |          ^~~~~~~~~~~~~~~

Signed-off-by: Philippe Mathieu-Daudé <f4bug@amsat.org>
---
 include/exec/helper-proto.h | 2 ++
 1 file changed, 2 insertions(+)

```
