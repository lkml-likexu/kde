#### [PATCH] KVM: fix memory leak in kvm_io_bus_unregister_dev()
##### From: Rustam Kovhaev <rkovhaev@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Rustam Kovhaev <rkovhaev@gmail.com>
X-Patchwork-Id: 11744677
Return-Path: <SRS0=+TZr=CI=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EAEC7722
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 30 Aug 2020 04:34:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C91A12074A
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 30 Aug 2020 04:34:42 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="nmmq4yt2"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725872AbgH3EeG (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 30 Aug 2020 00:34:06 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:41414 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725766AbgH3EeD (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 30 Aug 2020 00:34:03 -0400
Received: from mail-pf1-x443.google.com (mail-pf1-x443.google.com
 [IPv6:2607:f8b0:4864:20::443])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 66E63C061573;
        Sat, 29 Aug 2020 21:34:03 -0700 (PDT)
Received: by mail-pf1-x443.google.com with SMTP id g207so2754174pfb.1;
        Sat, 29 Aug 2020 21:34:03 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=xT5hOA3Q9LtPiLNaX+syaa1JIKrmhIwC08WtkEEf/0E=;
        b=nmmq4yt2jDGvMdopd9AnAONRTa4o80logLsYKaV7kuMUI6EYuTNs8A+SfJOCmrCiGU
         9TBCTO6Zqp1UghiKDOh/jVOVEyMWWfPDJBL4frWHmSCarqcERdZRwSZ/9HXxAcup6yBJ
         O+GUy7CSvKdtoFN43GxKYsQt8ubs+YyGw/Wszeo8IDodUaLRakVbXoP0n3IG/SdWSSdk
         5jY//dKbifCKbHgxugw5kOulA5x/kU6Gh0DFvYakBca5HCLZfTJgvxXzX4PoZdBTYJ7u
         mkyp+gSWke2XO9T0/gCDh4ej+fpHY0Tror4tF+qoCf0We3od1htIhkJgY1WpnZ+u1mb2
         Io8w==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=xT5hOA3Q9LtPiLNaX+syaa1JIKrmhIwC08WtkEEf/0E=;
        b=VJD/r6QdEp1wLiuzgsBAei/nyIkw7saOi8YvE120pt5DYXSeo100Kimkk+R0FUlohc
         dloDlFVheAjDvU4wdYtxGcF+G/7jZqiGT7LTbGVevimeQoeglKQKRQW2aafwMHIIYCJE
         E+CLmwxWxUO3NXEJqaUIfdCZpUQcjQAnlfC19TwD6nebxnA/DekfJBd8yDSkI5YdnYTv
         Alhfrr6qrQldOSaqAx4y+Yecdljag+2t/XQbQSj7J3wfIh7kyXxvP3Yyh85GLieTaz1u
         4BR/toqhzXV4qzZTvXrDegm5sbaCHevC/S0mvqzT0GOrMyaQyxk+Flk6f2uADXtFwa+u
         BOrQ==
X-Gm-Message-State: AOAM530mDrN86cA4Gh3J9ZdNPpagV21siDWjhw7F4SC8BDjNaCi8lMQI
        101Yli3qU+gJ/NFOODIl+Zw=
X-Google-Smtp-Source: 
 ABdhPJxL59CylV1nSHfWdYJMO6uDnfQ8foYdlMNRTWw78U3S/+mM5nt5uIsDFHhRw3bTt+il0JrooA==
X-Received: by 2002:a63:fe06:: with SMTP id p6mr4181417pgh.337.1598762039854;
        Sat, 29 Aug 2020 21:33:59 -0700 (PDT)
Received: from thinkpad.teksavvy.com (104.36.148.139.aurocloud.com.
 [104.36.148.139])
        by smtp.gmail.com with ESMTPSA id
 j18sm3740390pgm.30.2020.08.29.21.33.58
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Sat, 29 Aug 2020 21:33:59 -0700 (PDT)
From: Rustam Kovhaev <rkovhaev@gmail.com>
To: pbonzini@redhat.com, kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, gregkh@linuxfoundation.org,
        Rustam Kovhaev <rkovhaev@gmail.com>
Subject: [PATCH] KVM: fix memory leak in kvm_io_bus_unregister_dev()
Date: Sat, 29 Aug 2020 21:34:05 -0700
Message-Id: <20200830043405.268044-1-rkovhaev@gmail.com>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

when kmalloc() fails in kvm_io_bus_unregister_dev(), before removing
the bus, we should iterate over all other devices linked to it and call
kvm_iodevice_destructor() for them

Reported-and-tested-by: syzbot+f196caa45793d6374707@syzkaller.appspotmail.com
Link: https://syzkaller.appspot.com/bug?extid=f196caa45793d6374707
Signed-off-by: Rustam Kovhaev <rkovhaev@gmail.com>
---
 virt/kvm/kvm_main.c | 7 ++++++-
 1 file changed, 6 insertions(+), 1 deletion(-)

```