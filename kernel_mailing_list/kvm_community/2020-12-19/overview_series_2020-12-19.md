#### [PATCH] KVM: SVM: Add register operand to vmsave call in sev_es_vcpu_load
##### From: Nathan Chancellor <natechancellor@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Nathan Chancellor <natechancellor@gmail.com>
X-Patchwork-Id: 11983351
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-20.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 4389BC3526C
	for <kvm@archiver.kernel.org>; Sat, 19 Dec 2020 06:38:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 090A523BDD
	for <kvm@archiver.kernel.org>; Sat, 19 Dec 2020 06:38:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726347AbgLSGiR (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sat, 19 Dec 2020 01:38:17 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:38866 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726333AbgLSGiR (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 19 Dec 2020 01:38:17 -0500
Received: from mail-io1-xd33.google.com (mail-io1-xd33.google.com
 [IPv6:2607:f8b0:4864:20::d33])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 1AB67C0617B0;
        Fri, 18 Dec 2020 22:37:37 -0800 (PST)
Received: by mail-io1-xd33.google.com with SMTP id n4so4137099iow.12;
        Fri, 18 Dec 2020 22:37:37 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=oQNPVL/Z8kaYEUYKx/1vCF4SResp7qAIYrNtCxrI8Hs=;
        b=dbQbmyo5SSYm96Eu50fEtimgqoUT7AywYk6xMMomV2XhSc6SQN1SHqP6yP00HKXdxN
         gedpdDZ7Sv4fuQeWnHrcel0l49J6UCZcNNYSla8IcoGUAogv3bbvrMhBd9GGt/dEFVfS
         bIv8ZB1as3dqGKNPtO7WdY6p00vd+KJwoZvsJvof8iEtMPc8SocF4F1FQaFzqBL41aZt
         vO3ffQBGaLrKbA9DEe2vo7xpPq7LLVzgRgUEgkcv4n5qklAsbhCmFwAQ7YyySM7cHi01
         ExD8Gjvn9hr9uwbo/R3f1JJIcaFJlLyHkJnEyCE9sjEhcB/302vSQIAOgODU5gnQQmMx
         cvZw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=oQNPVL/Z8kaYEUYKx/1vCF4SResp7qAIYrNtCxrI8Hs=;
        b=m8Upqy1lt5YSaAO87UITOU1sXMC5KM5Kld/ERTLGaDqw5ROnI1XVQDklHg9E1AD2z4
         s4jpwuwJNJ0FfDHncl6dnojCbXQH9R8rj5NIjpKx0CqmrcV9tjW7CJVLdrNtBIII1xd5
         vHY/+87HsoK9L5hgkpVI0HVzUfhPH/eDaIsdDUnb/1t2374MW+KeMCzP73j0NlI6pywZ
         nwU935pb63v4h8jWgmC+TPLXbI7osl1zbY9ldV7T16y6MG8Tg1QjVpCenEcN6f8nNQ9b
         pfYYZUCsCUr7PfNQLrHLoeuEP1azk7o9wPgcGpxvm6F0gUbYCWvxMhKZPxSFY9M+8O+C
         Acmg==
X-Gm-Message-State: AOAM530swKTU4D+ednPXytChSU8Y8S7bfvoVM4Md1U7pbjJTb8LS1PbJ
        Tf1cRmHKYU3/oRWQZPnjcMk=
X-Google-Smtp-Source: 
 ABdhPJyLLzoc4pzFChs81f4F8v/+bdu96xVL1DTrtuWW/kiigpHo+mJmmZWOZQcdDCZmJKJWjLHqRQ==
X-Received: by 2002:a05:6602:81d:: with SMTP id
 z29mr7035171iow.62.1608359855758;
        Fri, 18 Dec 2020 22:37:35 -0800 (PST)
Received: from localhost.localdomain ([2604:1380:45f1:1d00::1])
        by smtp.gmail.com with ESMTPSA id
 l78sm8660998ild.30.2020.12.18.22.37.33
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 18 Dec 2020 22:37:34 -0800 (PST)
From: Nathan Chancellor <natechancellor@gmail.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Tom Lendacky <thomas.lendacky@amd.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        x86@kernel.org, kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        clang-built-linux@googlegroups.com,
        Nick Desaulniers <ndesaulniers@google.com>,
        Sami Tolvanen <samitolvanen@google.com>,
        Nathan Chancellor <natechancellor@gmail.com>
Subject: [PATCH] KVM: SVM: Add register operand to vmsave call in
 sev_es_vcpu_load
Date: Fri, 18 Dec 2020 23:37:11 -0700
Message-Id: <20201219063711.3526947-1-natechancellor@gmail.com>
X-Mailer: git-send-email 2.30.0.rc0
MIME-Version: 1.0
X-Patchwork-Bot: notify
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When using LLVM's integrated assembler (LLVM_IAS=1) while building
x86_64_defconfig + CONFIG_KVM=y + CONFIG_KVM_AMD=y, the following build
error occurs:

 $ make LLVM=1 LLVM_IAS=1 arch/x86/kvm/svm/sev.o
 arch/x86/kvm/svm/sev.c:2004:15: error: too few operands for instruction
         asm volatile(__ex("vmsave") : : "a" (__sme_page_pa(sd->save_area)) : "memory");
                      ^
 arch/x86/kvm/svm/sev.c:28:17: note: expanded from macro '__ex'
 #define __ex(x) __kvm_handle_fault_on_reboot(x)
                 ^
 ./arch/x86/include/asm/kvm_host.h:1646:10: note: expanded from macro '__kvm_handle_fault_on_reboot'
         "666: \n\t"                                                     \
                 ^
 <inline asm>:2:2: note: instantiated into assembly here
         vmsave
         ^
 1 error generated.

This happens because LLVM currently does not support calling vmsave
without the fixed register operand (%rax for 64-bit and %eax for
32-bit). This will be fixed in LLVM 12 but the kernel currently supports
LLVM 10.0.1 and newer so this needs to be handled.

Add the proper register using the _ASM_AX macro, which matches the
vmsave call in vmenter.S.

Fixes: 861377730aa9 ("KVM: SVM: Provide support for SEV-ES vCPU loading")
Link: https://reviews.llvm.org/D93524
Link: https://github.com/ClangBuiltLinux/linux/issues/1216
Signed-off-by: Nathan Chancellor <natechancellor@gmail.com>
---
 arch/x86/kvm/svm/sev.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
