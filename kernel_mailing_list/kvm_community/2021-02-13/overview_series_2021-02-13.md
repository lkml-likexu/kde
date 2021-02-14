#### [PATCH] arch: s390: kvm: Fix oustanding to outstanding in the file kvm-s390.c
##### From: Bhaskar Chowdhury <unixbhaskar@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Bhaskar Chowdhury <unixbhaskar@gmail.com>
X-Patchwork-Id: 12086907
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7089CC433E0
	for <kvm@archiver.kernel.org>; Sat, 13 Feb 2021 15:33:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3584A64D5D
	for <kvm@archiver.kernel.org>; Sat, 13 Feb 2021 15:33:45 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229693AbhBMPda (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sat, 13 Feb 2021 10:33:30 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:48070 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229649AbhBMPd1 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 13 Feb 2021 10:33:27 -0500
Received: from mail-qt1-x82e.google.com (mail-qt1-x82e.google.com
 [IPv6:2607:f8b0:4864:20::82e])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 61F79C061574;
        Sat, 13 Feb 2021 07:32:46 -0800 (PST)
Received: by mail-qt1-x82e.google.com with SMTP id e15so1905974qte.9;
        Sat, 13 Feb 2021 07:32:46 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=aPNiAFSqGubBl+g6zZSnfdiPci9YUIDPO5OPK2PIv7A=;
        b=kYskrqxNavsZf/AJgDpl4C8BOguF2R5HEewIyHxRfSl1t2YrXv4tdgRK8fkTkNZ/dj
         lbF2VoW4IewHowoTvx1GjViA+W0oYN5dtcjf1TykTmYUAnUXY/5JrmkPcJNiFT3GdthM
         AlU7ENS0+6hUNyJNsgRDYBE1SkYocsm9ytf4c3FhjG7/tUqKYuxDb+wKMojdMyMfg+pn
         uwHCQEB8RNJ4EX+TggV81UgBbVYBvJ6h3OMQgQNBzj2i53K1TeRD0EK8ysloacCTAutW
         Xd/lBGIcbh5QC7KPIUH83dL3WgXV5r8ow3fO6tyhSwYZ6unFr38T5BsdeqkRJ9zuzZ5D
         FI/Q==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=aPNiAFSqGubBl+g6zZSnfdiPci9YUIDPO5OPK2PIv7A=;
        b=o32CjniqusbmOXXZrA2jsg1yAT4wkGyf9yzbu8e+PuT0A9d8oa9jigmHOjvhPM7Ecw
         IPLKHsOOfEMlQF4hgXGtZwwubVZOww0OTIMOgGsutBhSBD5E94W3eALTRmqJCA0srEPn
         4uTVkVgbnNDtt1IGVU4a4KZFnluYnDZLLElPIdd9HhfOrZa4hHjlUSWpGuRE/BfLWWKd
         iXj8sonsJtXw/EPksmUZWgHwQYHDOtTlrXvsuTe5l2CA10njdoE9jnEm2ryDDMfmcOXZ
         Mp2MoOjc/MndEX6GaQJe9Et9UxJBK1EsvAwlv1ZTohm1Pfc5wP4uy5SrGbRJoS5L2IYc
         xv5w==
X-Gm-Message-State: AOAM531TBAjAt78pe2dHo/bMGV7ye/1vqKjGSLPmEYoKsBY0ZowcTi4n
        s7LRDU4kcBcfW+A9+lf+bkw=
X-Google-Smtp-Source: 
 ABdhPJwMr1Wei88g5Xh7RlX+z1UVfs29ZUxTQEwjEWIm8B3AQ7CK122kZD8OQppjy+tjarjI6HfDNw==
X-Received: by 2002:ac8:35d5:: with SMTP id l21mr7307551qtb.59.1613230365219;
        Sat, 13 Feb 2021 07:32:45 -0800 (PST)
Received: from localhost.localdomain ([156.146.55.129])
        by smtp.gmail.com with ESMTPSA id
 d1sm7514332qtq.94.2021.02.13.07.32.39
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Sat, 13 Feb 2021 07:32:44 -0800 (PST)
From: Bhaskar Chowdhury <unixbhaskar@gmail.com>
To: borntraeger@de.ibm.com, frankja@linux.ibm.com, david@redhat.com,
        cohuck@redhat.com, imbrenda@linux.ibm.com, hca@linux.ibm.com,
        gor@linux.ibm.com, kvm@vger.kernel.org, linux-s390@vger.kernel.org,
        linux-kernel@vger.kernel.org
Cc: rdunlap@infradead.org, Bhaskar Chowdhury <unixbhaskar@gmail.com>
Subject: [PATCH] arch: s390: kvm: Fix oustanding to outstanding in the file
 kvm-s390.c
Date: Sat, 13 Feb 2021 21:02:27 +0530
Message-Id: <20210213153227.1640682-1-unixbhaskar@gmail.com>
X-Mailer: git-send-email 2.30.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

s/oustanding/outstanding/

Signed-off-by: Bhaskar Chowdhury <unixbhaskar@gmail.com>
Acked-by: Randy Dunlap <rdunlap@infradead.org>
---
 arch/s390/kvm/kvm-s390.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

--
2.30.1

```
#### [RFC PATCH v5 01/26] x86/cpufeatures: Make SGX_LC feature bit depend on SGX bit
##### From: Kai Huang <kai.huang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kai Huang <kai.huang@intel.com>
X-Patchwork-Id: 12086785
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C657EC433E6
	for <kvm@archiver.kernel.org>; Sat, 13 Feb 2021 13:29:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9A04864E43
	for <kvm@archiver.kernel.org>; Sat, 13 Feb 2021 13:29:38 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229716AbhBMN3i (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sat, 13 Feb 2021 08:29:38 -0500
Received: from mga03.intel.com ([134.134.136.65]:7913 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229672AbhBMN3h (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 13 Feb 2021 08:29:37 -0500
IronPort-SDR: 
 pQYqVCKAsOG/Vwibii8kNwFxoSTkCcNK2504S0v7ZnhjfIIov+8abCMe/fg4QxpCa6L1bpp/QZ
 IDjcLu8MERVw==
X-IronPort-AV: E=McAfee;i="6000,8403,9893"; a="182595696"
X-IronPort-AV: E=Sophos;i="5.81,176,1610438400";
   d="scan'208";a="182595696"
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by orsmga103.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 13 Feb 2021 05:28:52 -0800
IronPort-SDR: 
 gPE7mGMsn3IeGoDBj6klW4wYM4Sv8T77Koug4qFtmzMamg3LMcF+l/aZ4E5wz3FkQ4alEMrB5E
 WSIwFe31RMbw==
X-IronPort-AV: E=Sophos;i="5.81,176,1610438400";
   d="scan'208";a="398365945"
Received: from kshah-mobl1.amr.corp.intel.com (HELO
 khuang2-desk.gar.corp.intel.com) ([10.255.230.239])
  by orsmga008-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 13 Feb 2021 05:28:49 -0800
From: Kai Huang <kai.huang@intel.com>
To: linux-sgx@vger.kernel.org, kvm@vger.kernel.org, x86@kernel.org
Cc: seanjc@google.com, jarkko@kernel.org, luto@kernel.org,
        dave.hansen@intel.com, rick.p.edgecombe@intel.com,
        haitao.huang@intel.com, pbonzini@redhat.com, bp@alien8.de,
        tglx@linutronix.de, mingo@redhat.com, hpa@zytor.com,
        Kai Huang <kai.huang@intel.com>
Subject: [RFC PATCH v5 01/26] x86/cpufeatures: Make SGX_LC feature bit depend
 on SGX bit
Date: Sun, 14 Feb 2021 02:28:35 +1300
Message-Id: 
 <8e6a1963b3666215223c247193e5a3e09a8c3698.1613221549.git.kai.huang@intel.com>
X-Mailer: git-send-email 2.29.2
In-Reply-To: <cover.1613221549.git.kai.huang@intel.com>
References: <cover.1613221549.git.kai.huang@intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Move SGX_LC feature bit to CPUID dependency table to make clearing all
SGX feature bits easier. Also remove clear_sgx_caps() since it is just
a wrapper of setup_clear_cpu_cap(X86_FEATURE_SGX) now.

Suggested-by: Sean Christopherson <seanjc@google.com>
Acked-by: Dave Hansen <dave.hansen@intel.com>
Acked-by: Jarkko Sakkinen <jarkko@kernel.org>
Signed-off-by: Kai Huang <kai.huang@intel.com>
---
v4->v5:

 - No code change.

v3->v4:

 - Changed patch order with the patch that introduced new SGX1/SGX2 bits, since
   it is improvement of existing code, per Jarkko.

---
 arch/x86/kernel/cpu/cpuid-deps.c |  1 +
 arch/x86/kernel/cpu/feat_ctl.c   | 12 +++---------
 2 files changed, 4 insertions(+), 9 deletions(-)

```
#### [PATCH 1/9] KVM: x86: Remove emulator's broken checks on CR0/CR3/CR4 loads
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12086475
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7274DC433E0
	for <kvm@archiver.kernel.org>; Sat, 13 Feb 2021 01:06:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3C3A464E05
	for <kvm@archiver.kernel.org>; Sat, 13 Feb 2021 01:06:16 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232148AbhBMBGM (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 12 Feb 2021 20:06:12 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:33042 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S231743AbhBMBGK (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 12 Feb 2021 20:06:10 -0500
Received: from mail-qk1-x749.google.com (mail-qk1-x749.google.com
 [IPv6:2607:f8b0:4864:20::749])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 8750CC0613D6
        for <kvm@vger.kernel.org>; Fri, 12 Feb 2021 17:05:30 -0800 (PST)
Received: by mail-qk1-x749.google.com with SMTP id r15so1033012qke.5
        for <kvm@vger.kernel.org>; Fri, 12 Feb 2021 17:05:30 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:reply-to:date:in-reply-to:message-id:mime-version:references
         :subject:from:to:cc;
        bh=OtznJizRN0hv7fVgLX6rnwrrxkCPL4lVRSWsCFjNnfE=;
        b=t56RiT1euE1E7CnLH3sOlDJSwYjYPxoxi/65GUwODU+vZGxsdYuG5+JudpeiQbYM/C
         ZFbuxsVlODgPdGNe/ORKCDGDUs6vPLRE4eEUhTNPQMTF/7ka0IiZrgOjzUUfSW1pCy8F
         yQexKIkRIlzOiBzSslW2f8bGyujBRRESZvdG1tDQJEuEA1sb+qmvq0d+f+dWDsOh887m
         rICHWD3PzXVRf37UTmBrWq6W5h+X1QzvK6HHtVDPG/lCd16qAg2vUCA4GEUP1MpAPHb1
         2CwxXyh/k7TV8L3H8XmmhMcOgp4UegSpqOBvho3GdgNScCjqgwBzUv3s+SCQmCUIax6N
         ISVw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:reply-to:date:in-reply-to:message-id
         :mime-version:references:subject:from:to:cc;
        bh=OtznJizRN0hv7fVgLX6rnwrrxkCPL4lVRSWsCFjNnfE=;
        b=lNQCG5H5G/r1JoQZ2vYT0QmI1jQMgklb/Ykk63clxY0fCn2+Xjrxh3+EEPUXfoFtH6
         qWTp43cc8lV7saPIWXJhf3jQx8ZbiD5elr43QzIjkKRWeyYVmqZ+BtaH3ZBDq+Z3aF5w
         eOor/thkzZOHn1aRszHhNDHk5aX7+3Ok8ddhg4u2jDbwcgTiK7I85w3uFxfpfXbJO1eq
         Buf2Ym/Z0lAW4t6c6FZWVRjdyCHbVyAIgKp2hGhvDeYnqqkv7exfvzo43h6may6PaFXv
         fTC7XhtO4bOcnjGbgefM6oRiBAypDvnpmewvUTd609BGQ+8hiaUj16UoSolub0YJJz/9
         nKtQ==
X-Gm-Message-State: AOAM533hyQKEu9anRCYnebDMOw91LXX/wllOUib8e701lj6jMLUm9SJW
        P7BGbH5YH9aP6mzKvzqkk4r0FgICYug=
X-Google-Smtp-Source: 
 ABdhPJyHJCYOfqtyA0CEPVTw5ctoK1eVWrcbTWX8UBaNeZKIu8zioYMpaKyl/EHcdeGYZhRTW+srES5FTOQ=
Sender: "seanjc via sendgmr" <seanjc@seanjc798194.pdx.corp.google.com>
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:b407:1780:13d2:b27])
 (user=seanjc job=sendgmr) by 2002:a05:6214:20a1:: with SMTP id
 1mr5147613qvd.30.1613178329654; Fri, 12 Feb 2021 17:05:29 -0800 (PST)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Fri, 12 Feb 2021 17:05:10 -0800
In-Reply-To: <20210213010518.1682691-1-seanjc@google.com>
Message-Id: <20210213010518.1682691-2-seanjc@google.com>
Mime-Version: 1.0
References: <20210213010518.1682691-1-seanjc@google.com>
X-Mailer: git-send-email 2.30.0.478.g8a0d178c01-goog
Subject: [PATCH 1/9] KVM: x86: Remove emulator's broken checks on CR0/CR3/CR4
 loads
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Babu Moger <babu.moger@amd.com>,
        Joao Martins <joao.m.martins@oracle.com>,
        David Woodhouse <dwmw@amazon.co.uk>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Remove the emulator's checks for illegal CR0, CR3, and CR4 values, as
the checks are redundant, outdated, and in the case of SEV's C-bit,
broken.  The emulator manually calculates MAXPHYADDR from CPUID and
neglects to mask off the C-bit.  For all other checks, kvm_set_cr*() are
a superset of the emulator checks, e.g. see CR4.LA57.

Fixes: a780a3ea6282 ("KVM: X86: Fix reserved bits check for MOV to CR3")
Cc: Babu Moger <babu.moger@amd.com>
Signed-off-by: Sean Christopherson <seanjc@google.com>
---
 arch/x86/kvm/emulate.c | 68 +-----------------------------------------
 1 file changed, 1 insertion(+), 67 deletions(-)

```
#### [PATCH 01/14] KVM: x86/mmu: Expand collapsible SPTE zap for TDP MMU to ZONE_DEVICE pages
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12086435
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id A18FEC433E6
	for <kvm@archiver.kernel.org>; Sat, 13 Feb 2021 00:51:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7B53E64E02
	for <kvm@archiver.kernel.org>; Sat, 13 Feb 2021 00:51:33 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229650AbhBMAvW (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 12 Feb 2021 19:51:22 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:57986 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S232005AbhBMAvE (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 12 Feb 2021 19:51:04 -0500
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 70F13C061786
        for <kvm@vger.kernel.org>; Fri, 12 Feb 2021 16:50:24 -0800 (PST)
Received: by mail-yb1-xb4a.google.com with SMTP id 203so1567722ybz.2
        for <kvm@vger.kernel.org>; Fri, 12 Feb 2021 16:50:24 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:reply-to:date:in-reply-to:message-id:mime-version:references
         :subject:from:to:cc;
        bh=4X8Xawmkqq6JrMI8EQ6Ez131d+8bBQcFXdbpvRYDUz4=;
        b=GnlMk7vhQFA5V4yJOVvifabbC2ElQwDOtmcUG44rof+fgdTrwGAFwFX4p3LG9fLNL1
         WaxcclGNJu64urykhUWGvJ++jy5bkggdIO7iB0nOvezt1DQxBx70ZyzB109ZGWQ1KRko
         xZsW64uIrhXxCvXyhiJx0h7L9Uk00AEvRY166UfiWKCjhiiylBRnm1R2ZpOX5tDzX5zp
         NGGTV/eaLw78lGrN8y9luYglA6il47mudOSGjs0bmXxZE8aqUeEyjJucAdH9kbulQwob
         TdW9q/RIhC7ZZxuXKxHk127puPNTRLP8Xmmyd5SNT83kU/GrswKAKKeqb5+lePK25SbG
         d+JQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:reply-to:date:in-reply-to:message-id
         :mime-version:references:subject:from:to:cc;
        bh=4X8Xawmkqq6JrMI8EQ6Ez131d+8bBQcFXdbpvRYDUz4=;
        b=SOUt0c6V58Ma9zlSrVBgQuO2eGsNypU5om49zYCBAYceCwUMLGWgXh5LuchR8z2G/Q
         LDW5YZCUd93Mgic4Hwaxu9omFysxPOe8eFqCCiwl7+wDotmgT+Qcx5VQH94cPKMdnQ0m
         kGhvJW42xWX+5rgAbVPHu9zZUwPpQQrz+bzXUMl5Y/LiX7mYXpOdIpVBFYmzekOj0JYQ
         Q+ZW1baSbvg+Z7g1ed1IDjIEb4A6HMi3CYvQGZSbqE0XNKynq4yfrDbRvco9CB7nqIj9
         UzXf0oIev1ej28jHAhS5PLtUA4cw+83QRW7kllcntsDXiH4zQimqzJga1GlCvCQ6GXDv
         OmHw==
X-Gm-Message-State: AOAM533B9x1/KKXXO2Qj3uVj1tbQGDzmiSfwG7OVNkdh86SI/nx9LLg2
        buBqynFbVICBiufRuH47kct0C2yIQh8=
X-Google-Smtp-Source: 
 ABdhPJwisJLVUO82g7ZpXF02safHacPg3WhZ69zQ2JPkhSdW2WAFwkbFqEizlPxxQ/9Fc1CQ+oCBmi5Py7E=
Sender: "seanjc via sendgmr" <seanjc@seanjc798194.pdx.corp.google.com>
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:b407:1780:13d2:b27])
 (user=seanjc job=sendgmr) by 2002:a25:e010:: with SMTP id
 x16mr7990153ybg.17.1613177423616;
 Fri, 12 Feb 2021 16:50:23 -0800 (PST)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Fri, 12 Feb 2021 16:50:02 -0800
In-Reply-To: <20210213005015.1651772-1-seanjc@google.com>
Message-Id: <20210213005015.1651772-2-seanjc@google.com>
Mime-Version: 1.0
References: <20210213005015.1651772-1-seanjc@google.com>
X-Mailer: git-send-email 2.30.0.478.g8a0d178c01-goog
Subject: [PATCH 01/14] KVM: x86/mmu: Expand collapsible SPTE zap for TDP MMU
 to ZONE_DEVICE pages
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Ben Gardon <bgardon@google.com>,
        Makarand Sonare <makarandsonare@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Zap SPTEs that are backed by ZONE_DEVICE pages when zappings SPTEs to
rebuild them as huge pages in the TDP MMU.  ZONE_DEVICE huge pages are
managed differently than "regular" pages and are not compound pages.

Cc: Ben Gardon <bgardon@google.com>
Fixes: 14881998566d ("kvm: x86/mmu: Support disabling dirty logging for the tdp MMU")
Signed-off-by: Sean Christopherson <seanjc@google.com>
---
 arch/x86/kvm/mmu/tdp_mmu.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [PATCH] selftests: kvm: add hardware_disable testFrom: Marc Orr <marcorr@google.com>
##### From: Marc Orr <marcorr@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Orr <marcorr@google.com>
X-Patchwork-Id: 12086383
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=unavailable autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D9EE3C433DB
	for <kvm@archiver.kernel.org>; Sat, 13 Feb 2021 00:16:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A308F64E9A
	for <kvm@archiver.kernel.org>; Sat, 13 Feb 2021 00:16:16 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232191AbhBMAQM (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 12 Feb 2021 19:16:12 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:50478 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S232140AbhBMAPy (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 12 Feb 2021 19:15:54 -0500
Received: from mail-pl1-x64a.google.com (mail-pl1-x64a.google.com
 [IPv6:2607:f8b0:4864:20::64a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 7F1FCC061756
        for <kvm@vger.kernel.org>; Fri, 12 Feb 2021 16:15:11 -0800 (PST)
Received: by mail-pl1-x64a.google.com with SMTP id d5so1018382plg.16
        for <kvm@vger.kernel.org>; Fri, 12 Feb 2021 16:15:11 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:message-id:mime-version:subject:from:to:cc;
        bh=LFYECqnkpVnS9ezPEnkkGsIKGemq65IEfeP4v4FCXC0=;
        b=MNJaPCb6kCwQDqWE0VHDBWLh/jpZooOs4BybtKx0hSsGmWH2dSznyNmvm+qKf3ZdsL
         BvMMcNNILVaCUuAysU3V9NkNcV5Vfk0XUYnuvkpqedOgOwQMSzUmaqfPG9CI8pzG4Yk+
         pcYbLHCV0CPfWXhXiURTZR2eoW+EFlReBpX8ob392Cr0s6wfzsq4+S16MBcEfPA2gM7q
         32C/aYhTo0QEE75SU4pjwqlyrMNmbuxe+DBeNmlkudmt+sB7cMOveagRIJ1+4LGL1Sdl
         NwCfB46R+51EH50MjffcfFu5WNbGWqkcHD1TLQ0LUVrLfVbU2J1DFq33Z2s8kz+B2C7N
         5qSg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:message-id:mime-version:subject:from
         :to:cc;
        bh=LFYECqnkpVnS9ezPEnkkGsIKGemq65IEfeP4v4FCXC0=;
        b=mmnHQGGGMXIVn5r7L0QxelIov1oSXHRYkgNc/DcEK9z63ZJZwgfqNCQRt5vOeSrGUG
         G/lLQiF4DvkswevbowAk/LsMPA6tgL4D5ZVc1L4lPdUX+AiDMzQZwcGoXi4jSPSwNDxM
         VvJ19ph/7Q6WPEytSpyc5BBWS8XeFw9smAWNWNmYxSorTdV7apdA/h1JldOd0vb5Aw8a
         6P8G1mk90KIyAZubO+6xDvT1jBkHkITFnFW/kQy0bFHrSOexts5WMZ2oWzgUtGMZn3CJ
         jHJPv4Q/OxGEDUburIR+CYtT5iRrm5kAD7i2dSB8y6m0qpJaKUQVUJyQglZzleBY57lp
         McuA==
X-Gm-Message-State: AOAM5329pOAhUo3ukqOYSpQJ/srwAk1fu5v28cOjQaChOdSTACiBe8NB
        TPNFsD/oVi+ut98WewQI51UIMjTkrkoE
X-Google-Smtp-Source: 
 ABdhPJwK7FIiWqa0ahuLvd8FzrmfmaE3R47CXzIOG11ep2x3akfjtG1jGl1a3i/2TYw6gn210AVTmbmdlvYN
Sender: "marcorr via sendgmr" <marcorr@marcorr-sp.c.googlers.com>
X-Received: from marcorr-sp.c.googlers.com
 ([fda3:e722:ac3:10:7f:e700:c0a8:e50])
 (user=marcorr job=sendgmr) by 2002:aa7:86d8:0:b029:1b5:1121:729a with SMTP id
 h24-20020aa786d80000b02901b51121729amr5213353pfo.57.1613175310890; Fri, 12
 Feb 2021 16:15:10 -0800 (PST)
Date: Sat, 13 Feb 2021 00:14:52 +0000
Message-Id: <20210213001452.1719001-1-marcorr@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.30.0.478.g8a0d178c01-goog
Subject: [PATCH] selftests: kvm: add hardware_disable test
From: Marc Orr <marcorr@google.com>
To: ikalvarado@google.com, pbonzini@redhat.com, huah@kernel.org,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        linux-kselftest@vger.kernel.org, brijesh.singh@amd.com,
        Thomas.Lendacky@amd.com, jmattson@google.com
Cc: Marc Orr <marcorr@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Ignacio Alvarado <ikalvarado@google.com>

This test launches 512 VMs in serial and kills them after a random
amount of time.

The test was original written to exercise KVM user notifiers in
the context of1650b4ebc99d:
- KVM: Disable irq while unregistering user notifier
- https://lore.kernel.org/kvm/CACXrx53vkO=HKfwWwk+fVpvxcNjPrYmtDZ10qWxFvVX_PTGp3g@mail.gmail.com/

Recently, this test piqued my interest because it proved useful to
for AMD SNP in exercising the "in-use" pages, described in APM section
15.36.12, "Running SNP-Active Virtual Machines".

To run the test, first compile:
$ make "CPPFLAGS=-static -Wl,--whole-archive -lpthread -Wl,--no-whole-archive" \
    -C tools/testing/selftests/kvm/

Then, copy the test over to a machine with the kernel and run:
$ ./hardware_disable_test

Signed-off-by: Ignacio Alvarado <ikalvarado@google.com>
Signed-off-by: Marc Orr <marcorr@google.com>
---
 tools/testing/selftests/kvm/.gitignore        |   1 +
 tools/testing/selftests/kvm/Makefile          |   1 +
 .../selftests/kvm/hardware_disable_test.c     | 165 ++++++++++++++++++
 3 files changed, 167 insertions(+)
 create mode 100644 tools/testing/selftests/kvm/hardware_disable_test.c

```
