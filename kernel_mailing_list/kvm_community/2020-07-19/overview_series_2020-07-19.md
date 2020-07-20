#### [PATCH] MIPS: KVM: Fix build error caused by 'kvm_run' cleanup
##### From: Huacai Chen <chenhc@lemote.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Huacai Chen <chenhc@lemote.com>
X-Patchwork-Id: 11672403
Return-Path: <SRS0=qD0G=A6=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5F079618
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 19 Jul 2020 10:21:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 46BB320734
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 19 Jul 2020 10:21:25 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="b8PS/gz0"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726038AbgGSKVY (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 19 Jul 2020 06:21:24 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:51520 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725836AbgGSKVX (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 19 Jul 2020 06:21:23 -0400
Received: from mail-pg1-x541.google.com (mail-pg1-x541.google.com
 [IPv6:2607:f8b0:4864:20::541])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 7D28DC0619D2;
        Sun, 19 Jul 2020 03:21:23 -0700 (PDT)
Received: by mail-pg1-x541.google.com with SMTP id l63so8891009pge.12;
        Sun, 19 Jul 2020 03:21:23 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id;
        bh=jEXavRvD3y6/Bjh0tIzjOCNSq6rpCbWUQWApQCUf4mo=;
        b=b8PS/gz0a3rtMBdf/w1wHbRCMi+F8WpQCLeALDgjSaFe5r2bqFz84K/g1LOeqpeV03
         VSGp5TLNmZJm+Nzz6KHGwy3uoZggI4FJSX6c0vH9mCmMPQTldtv+ZIBh9AFSdt9XKVje
         04CNpDfhq2h1WOWvrbr1nCWmLUUl6HPnBLPcRxWuKrBI1Fms2ig5s6+aq0uvCf5LDogO
         rn+2blzqbjUOSQnRdpT3R4Y8MHEz6QANUNctCGtp4zyFRjQeUthf4v/cLyk82NK1d7PN
         FNNyjExD3W4K67gCDBSY4qxGxXDPvh08aRPAAYtxptLibzuuJKypxU+yz4r++fdNWG2s
         mdMw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id;
        bh=jEXavRvD3y6/Bjh0tIzjOCNSq6rpCbWUQWApQCUf4mo=;
        b=YfwueNY6Qgw+FwUwCTE/9Z6lz79JN8iadLPVATzjdHUPUknu5MdmATm/zXRaStOd6Q
         /QOSnyf3PW1dJayirq2Jm0MlSXK9/3BAXjAxq7JamCeHuPOXJvEp8Ay2Ya2V4BZorZo2
         NH9580Iowz42QhA75X4H+FZmjqf5psypn9cRAh0BvuwIqN5CIbk3+ZAcMBTtPKwCIdaN
         hLtE4UtgJXZ4mM5UTPpeFcHIgz9vbw5gdcYSNLUQU+cXdf8NNKX/mPgm+JwzsBxubhUp
         daVUCwMe5cRLkcbaVaj+rDD0onBR3awXVSiDjaYEtX/Evcungimfc9Kwba8w9QkSlyXK
         UBPw==
X-Gm-Message-State: AOAM532E52/r6Oc8v/Q9x0gDn6GN5Hf8OlYshsmQ5F+KtiyfO2Qf6yEq
        u7A6SuAw4iR6LW1WQibuuC0=
X-Google-Smtp-Source: 
 ABdhPJwsTcLBZugd0mm+nvjiAfP8wQ1pBLMr5m4acjjtaBQyGW1s9tYBpVXyWwzlDjNFaNC49Qtm1g==
X-Received: by 2002:a62:f905:: with SMTP id o5mr15709242pfh.244.1595154082015;
        Sun, 19 Jul 2020 03:21:22 -0700 (PDT)
Received: from software.domain.org ([45.77.13.216])
        by smtp.gmail.com with ESMTPSA id
 137sm12635263pgg.72.2020.07.19.03.21.17
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Sun, 19 Jul 2020 03:21:21 -0700 (PDT)
From: Huacai Chen <chenhc@lemote.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Thomas Bogendoerfer <tsbogend@alpha.franken.de>,
        Aleksandar Markovic <aleksandar.qemu.devel@gmail.com>
Cc: kvm@vger.kernel.org, linux-mips@vger.kernel.org,
        Fuxin Zhang <zhangfx@lemote.com>,
        Huacai Chen <chenhuacai@gmail.com>,
        Jiaxun Yang <jiaxun.yang@flygoat.com>,
        Huacai Chen <chenhc@lemote.com>,
        Tianjia Zhang <tianjia.zhang@linux.alibaba.com>
Subject: [PATCH] MIPS: KVM: Fix build error caused by 'kvm_run' cleanup
Date: Sun, 19 Jul 2020 18:23:27 +0800
Message-Id: <1595154207-9787-1-git-send-email-chenhc@lemote.com>
X-Mailer: git-send-email 2.7.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Commit c34b26b98caca48ec9ee9 ("KVM: MIPS: clean up redundant 'kvm_run'
parameters") remove the 'kvm_run' parameter in kvm_mips_complete_mmio_
load(), but forget to update all callers.

Fixes: c34b26b98caca48ec9ee9 ("KVM: MIPS: clean up redundant 'kvm_run' parameters")
Reported-by: kernel test robot <lkp@intel.com>
Cc: Tianjia Zhang <tianjia.zhang@linux.alibaba.com>
Signed-off-by: Huacai Chen <chenhc@lemote.com>
---
I have reviewed Tianjia's patch but hadn't found the bug, I'm very very
sorry for that.

 arch/mips/kvm/emulate.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
