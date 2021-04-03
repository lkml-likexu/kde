

#### [PATCH v2 00/10] KVM: Consolidate and optimize MMU notifiers
##### From: Sean Christopherson <seanjc@google.com>

```c
From patchwork Fri Apr  2 00:56:48 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12180123
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 2B216C43460
	for <kvm@archiver.kernel.org>; Fri,  2 Apr 2021 00:57:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id F051D61132
	for <kvm@archiver.kernel.org>; Fri,  2 Apr 2021 00:57:05 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233975AbhDBA5E (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 1 Apr 2021 20:57:04 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:40326 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S233849AbhDBA5E (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 1 Apr 2021 20:57:04 -0400
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id D48B1C061788
        for <kvm@vger.kernel.org>; Thu,  1 Apr 2021 17:57:01 -0700 (PDT)
Received: by mail-yb1-xb49.google.com with SMTP id o129so7549930ybg.23
        for <kvm@vger.kernel.org>; Thu, 01 Apr 2021 17:57:01 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=FViJNMuAQXVG92IcJ9ASyfw+gqYDqmookinTy4APMz8=;
        b=tM5HW6/xk4O5sMn2fgKiWu76aEhiiETLruJpg/eDqJDR4WtSvS9+XoKICGLJgo/aR9
         PHUygm3nt6Iyd9H+hRkE+aN2uWXSniHsrGAukhueCHEWKNiGLvDdvm/C35c51KL7qq/J
         fgt3utJuyw2N+OiFjKc36bNdeTZMCG2OXJjHEkQxFIqyXipTvjAOsKRQR3H93WpjXiTJ
         zZlKgCHu1/48AstcZ0TNb2v8J6l74NmyyCG68O3osE84/6JpVuFsdO2EgEGawRt1qn/R
         MTRQMS94V9rHBAev+i0CHpGE75U1N9vbPoIhstygJ3ud1d//b6oFND6DleWTsUfEpKQo
         REdQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:reply-to:date:message-id:mime-version:subject
         :from:to:cc;
        bh=FViJNMuAQXVG92IcJ9ASyfw+gqYDqmookinTy4APMz8=;
        b=BltyHRAR3NEHbnoM6pKRF++1ivOZryQ40sqHPcKmXbGYjbepPXbfhzbN5QwZ3eGJI/
         RguuBwRjak3nf9jU9P6PNilhqZCQL+F/KFVIt4ugXAuA+7iaIJtB1RKOgfTNi3/46dXh
         J+dhJUT2CMgUwNahL2KVRJ1xT9o+eyQwfKIeYRff4+9O/+MB4pHlgzayFD2PwAbUg6S3
         HF+cS6EDRqMwxf8gDphiaN2aa7NZfxfrfqAsC0Gk0K8z0L5eoP9rnnusAiVDBslEY2XD
         vdCGs4EKWmoJjtTxWo56S6MeLFLHdr+iNGpCQAoGLDHnudADNI6CyyZSopiENFtmG74L
         Z6cQ==
X-Gm-Message-State: AOAM532AvSm4Fde09CBhrvV6TxhAqYj4K3tn2tMa0rRU9zA/nl+01zwp
        RNFxLVZ0c1VxWjPFKHS7cFwMrOFy2fg=
X-Google-Smtp-Source: 
 ABdhPJzX9kzo85wBh2DvMcR2Y9UxX/gVfIA/wY1qXyxNt7lm9J3jjA4HAyWrYbcDrQf6yDOm390BaT3pn8k=
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:c0b4:8b8:bb34:6a56])
 (user=seanjc job=sendgmr) by 2002:a25:a187:: with SMTP id
 a7mr8464267ybi.377.1617325020964;
 Thu, 01 Apr 2021 17:57:00 -0700 (PDT)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Thu,  1 Apr 2021 17:56:48 -0700
Message-Id: <20210402005658.3024832-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.0.208.g409f899ff0-goog
Subject: [PATCH v2 00/10] KVM: Consolidate and optimize MMU notifiers
From: Sean Christopherson <seanjc@google.com>
To: Marc Zyngier <maz@kernel.org>, Huacai Chen <chenhuacai@kernel.org>,
        Aleksandar Markovic <aleksandar.qemu.devel@gmail.com>,
        Paul Mackerras <paulus@ozlabs.org>,
        Paolo Bonzini <pbonzini@redhat.com>
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        linux-mips@vger.kernel.org, kvm@vger.kernel.org,
        kvm-ppc@vger.kernel.org, linux-kernel@vger.kernel.org,
        Ben Gardon <bgardon@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The end goal of this series is to optimize the MMU notifiers to take
mmu_lock if and only if the notification is relevant to KVM, i.e. the hva
range overlaps a memslot.   Large VMs (hundreds of vCPUs) are very
sensitive to mmu_lock being taken for write at inopportune times, and
such VMs also tend to be "static", e.g. backed by HugeTLB with minimal
page shenanigans.  The vast majority of notifications for these VMs will
be spurious (for KVM), and eliding mmu_lock for spurious notifications
avoids an otherwise unacceptable disruption to the guest.

To get there without potentially degrading performance, e.g. due to
multiple memslot lookups, especially on non-x86 where the use cases are
largely unknown (from my perspective), first consolidate the MMU notifier
logic by moving the hva->gfn lookups into common KVM.

Based on kvm/queue, commit 5f986f748438 ("KVM: x86: dump_vmcs should
include the autoload/autostore MSR lists").

Well tested on Intel and AMD.  Compile tested for arm64, MIPS, PPC,
PPC e500, and s390.  Absolutely needs to be tested for real on non-x86,
I give it even odds that I introduced an off-by-one bug somewhere.

v2:
 - Drop the patches that have already been pushed to kvm/queue.
 - Drop two selftest changes that had snuck in via "git commit -a".
 - Add a patch to assert that mmu_notifier_count is elevated when
   .change_pte() runs. [Paolo]
 - Split out moving KVM_MMU_(UN)LOCK() to __kvm_handle_hva_range() to a
   separate patch.  Opted not to squash it with the introduction of the
   common hva walkers (patch 02), as that prevented sharing code between
   the old and new APIs. [Paolo]
 - Tweak the comment in kvm_vm_destroy() above the smashing of the new
   slots lock. [Paolo]
 - Make mmu_notifier_slots_lock unconditional to avoid #ifdefs. [Paolo]

v1:
 - https://lkml.kernel.org/r/20210326021957.1424875-1-seanjc@google.com

Sean Christopherson (10):
  KVM: Assert that notifier count is elevated in .change_pte()
  KVM: Move x86's MMU notifier memslot walkers to generic code
  KVM: arm64: Convert to the gfn-based MMU notifier callbacks
  KVM: MIPS/MMU: Convert to the gfn-based MMU notifier callbacks
  KVM: PPC: Convert to the gfn-based MMU notifier callbacks
  KVM: Kill off the old hva-based MMU notifier callbacks
  KVM: Move MMU notifier's mmu_lock acquisition into common helper
  KVM: Take mmu_lock when handling MMU notifier iff the hva hits a
    memslot
  KVM: Don't take mmu_lock for range invalidation unless necessary
  KVM: x86/mmu: Allow yielding during MMU notifier unmap/zap, if
    possible

 arch/arm64/kvm/mmu.c                   | 117 +++------
 arch/mips/kvm/mmu.c                    |  97 ++------
 arch/powerpc/include/asm/kvm_book3s.h  |  12 +-
 arch/powerpc/include/asm/kvm_ppc.h     |   9 +-
 arch/powerpc/kvm/book3s.c              |  18 +-
 arch/powerpc/kvm/book3s.h              |  10 +-
 arch/powerpc/kvm/book3s_64_mmu_hv.c    |  98 ++------
 arch/powerpc/kvm/book3s_64_mmu_radix.c |  25 +-
 arch/powerpc/kvm/book3s_hv.c           |  12 +-
 arch/powerpc/kvm/book3s_pr.c           |  56 ++---
 arch/powerpc/kvm/e500_mmu_host.c       |  27 +-
 arch/x86/kvm/mmu/mmu.c                 | 127 ++++------
 arch/x86/kvm/mmu/tdp_mmu.c             | 245 +++++++------------
 arch/x86/kvm/mmu/tdp_mmu.h             |  14 +-
 include/linux/kvm_host.h               |  22 +-
 virt/kvm/kvm_main.c                    | 325 +++++++++++++++++++------
 16 files changed, 552 insertions(+), 662 deletions(-)
```
#### [PATCH 0/5 v6] KVM: nSVM: Check addresses of MSR bitmap and IO bitmap
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
From patchwork Fri Apr  2 00:43:26 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 12180177
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 29395C43461
	for <kvm@archiver.kernel.org>; Fri,  2 Apr 2021 01:33:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DA2A961006
	for <kvm@archiver.kernel.org>; Fri,  2 Apr 2021 01:33:05 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234069AbhDBBdD (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 1 Apr 2021 21:33:03 -0400
Received: from aserp2120.oracle.com ([141.146.126.78]:33962 "EHLO
        aserp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S233786AbhDBBdA (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 1 Apr 2021 21:33:00 -0400
Received: from pps.filterd (aserp2120.oracle.com [127.0.0.1])
        by aserp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 1321V0GR002164;
        Fri, 2 Apr 2021 01:32:53 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : content-transfer-encoding : content-type :
 mime-version; s=corp-2020-01-29;
 bh=A9DrAPFRME0EFjpPvd3tD1m46PApLu8MrhvXyOLkS8s=;
 b=J0YJBMi6bfkm6a8EgXd1y5IO6bAf3c8iqH4o8LvilXknyB5AaY4tXuHn5VXihPN3+/Tw
 DQDvp48oV4SwpftxnZji5cGMgSHRRnn51EidxmXDSD40UJhJMqB4Bd1P7zn7U9pttdH3
 OcmT0ZVFqCktslJjiU45Lz2Z/OJs3lbBv8WpRnMjMwaR9mbNaLoa9gibwGJBDdOqM+TB
 AU5y6Kx0Ernuj8RIrI606o8cd7/uRbY/r4UK7X19SGRCiVRiTfPdgCOOvJcSwXcy1SSJ
 /LXuKMHm6YuJxN7MdGoh9tXdisUyB+7VwtbkvRj4e9x6RGEoN+DjlGvUsDHkK3TlNC/3 4w==
Received: from aserp3020.oracle.com (aserp3020.oracle.com [141.146.126.70])
        by aserp2120.oracle.com with ESMTP id 37n2akkk5v-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 02 Apr 2021 01:32:52 +0000
Received: from pps.filterd (aserp3020.oracle.com [127.0.0.1])
        by aserp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 1321Uw7L018855;
        Fri, 2 Apr 2021 01:32:52 GMT
Received: from nam10-mw2-obe.outbound.protection.outlook.com
 (mail-mw2nam10lp2101.outbound.protection.outlook.com [104.47.55.101])
        by aserp3020.oracle.com with ESMTP id 37n2abyytf-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 02 Apr 2021 01:32:52 +0000
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=HBiqd+bB+ow6mZ96MM3TZMkKnJwVdfFz81df5e8dYOWGYo2HPXaD+9waa2RSUnMWZp30muYyZQbzO42KH6rVVngCmOMqlNuPo5h8XpieWIPn5GWYUmTC5vXr5zBUFDB23AecbH6xkWyI3+22rVDwF5OqsthwP3eBOWxbc7dnTwgRe+OOFmfiI7R8AuoaRk3r+yG9Lkt6dV6+I6w8d3Y4TR9W0cFVofF+tm3sfBbO6TZBikclJPNUTQ2AmwFNEHpRhIlgpP72ZFPLb2/UvNyWT1dXikmr9d5h8n74afacBgQ5nWcOhDwXvQUcu1e8xo+AAOCrxPcxSMj4XVbe+3f7/Q==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=A9DrAPFRME0EFjpPvd3tD1m46PApLu8MrhvXyOLkS8s=;
 b=oI80pSwtzGM+qaGW5XbSM9fxajTU+22zXlCvTBycv6czvvC4Ls92uoFiUwfQDpAKPtkap2CB0yBavRI3NaozLTtHwZlss/FLOS+6LBSI4Wn86C9LusiiOE9+Tz/OJnrJlfeXw4pwb1pXSPAbxhNrPk7m9T9yMKIVjtrqc6lQANvG59GvlIn9sZYyf7cmxn0OATL6nL7R5mKzlkv7Iqo87GjzCKlnV5M2c1vfnh3Vk48O75PfJqL1bxU3w5E6TiqPeymgrWwmFn0HvQYDeRUcJ30d0kA1yE501vt+4wfOr1riqe+hza/j1+qE4jT4qa5RrlGZEgWwccpYk7I/OY3C5g==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=oracle.com; dmarc=pass action=none header.from=oracle.com;
 dkim=pass header.d=oracle.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=oracle.onmicrosoft.com; s=selector2-oracle-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=A9DrAPFRME0EFjpPvd3tD1m46PApLu8MrhvXyOLkS8s=;
 b=VIvKG1JC5h/w/rnalZcaEOqBjVFNakvuiBxlSbXS3KKL+CXYGnjJqAQIu8bJh6DR0ePXNnsP5ukqLzb17eL3xNkWAjH9a7r5G4VQ6+welrmvXMUCE3A9BxoMBrrp9om87OmfcVQAa67aiWkv5Ys1yRK+akYcolv3F9q6Lh/WHnA=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=oracle.com;
Received: from SN6PR10MB3021.namprd10.prod.outlook.com (2603:10b6:805:cc::19)
 by SA2PR10MB4795.namprd10.prod.outlook.com (2603:10b6:806:11d::14) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3999.28; Fri, 2 Apr
 2021 01:32:50 +0000
Received: from SN6PR10MB3021.namprd10.prod.outlook.com
 ([fe80::5911:9489:e05c:2d44]) by SN6PR10MB3021.namprd10.prod.outlook.com
 ([fe80::5911:9489:e05c:2d44%5]) with mapi id 15.20.3999.029; Fri, 2 Apr 2021
 01:32:50 +0000
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com, seanjc@google.com
Subject: [PATCH 0/5 v6] KVM: nSVM: Check addresses of MSR bitmap and IO bitmap
 tables on vmrun of nested guests
Date: Thu,  1 Apr 2021 20:43:26 -0400
Message-Id: <20210402004331.91658-1-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.25.4
X-Originating-IP: [138.3.201.29]
X-ClientProxiedBy: SJ0PR13CA0024.namprd13.prod.outlook.com
 (2603:10b6:a03:2c0::29) To SN6PR10MB3021.namprd10.prod.outlook.com
 (2603:10b6:805:cc::19)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from ban25x6uut29.us.oracle.com (138.3.201.29) by
 SJ0PR13CA0024.namprd13.prod.outlook.com (2603:10b6:a03:2c0::29) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4020.9 via Frontend
 Transport; Fri, 2 Apr 2021 01:32:49 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 0bde9b43-911f-4fc3-a913-08d8f5773a79
X-MS-TrafficTypeDiagnostic: SA2PR10MB4795:
X-Microsoft-Antispam-PRVS: 
 <SA2PR10MB4795DAA2AE18686A56971041817A9@SA2PR10MB4795.namprd10.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:2657;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 61eUQLrSMnw0X5NoEn2WMk+tkgCodU+HriKNDYPheyjpu3tICNEmq8PlwobwvVw6X1p0oJ4SW6dE38jyhp6vBiF1GICYrulYG74842C70YlNJzCqUCKrQnLV1ovqWQI5fkTAYKwZuNDxY5LDSV1uNt8aw8Iq9BXU56GinG6UTKe/3Tjhc8YcIC1o0FindE/G5zt/2agkXcWz7lc3IAoMm7opnOVyCnSy1bbAQ+vwN0muxQ9UffwI6Pb0q75KjXwi3vffL+EMxEQk7WvfAwpwVnQ0i1BA7YovDhwdPFU6SA4jMQ0Jd0J7hAvQx/MtnqP0yI5uNegsf0Am2CDGfMOYxWbfvcEH5P2ZNstMd3uaDHCA6x4LJazUHUV9YiQOSUD3Cz3Vba3T4dLQCyERZW950r3CsMHoq2q8d0fXVJSzwz7pKezLZx6L04gaEUmS4tg7GO9tRiNq3mb/a0Td0JoO127P32iKMqgSn3FJ69+RCRmJHHZstWXa5H6VT5d658faHdAchRyLE4viX4wKgIS47eA/HBIGjujeL+OuM5QUI/5zJVm48Sy51cya26/HQ8CeY1vPcpsFoFA3FFew690Fi7/0a/AdTJB/z68Fl0U0Cw21xKNsuMaQNkeBiEvJ5oMUcrZhXqJV8KAndfb9JskQ7g==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN6PR10MB3021.namprd10.prod.outlook.com;PTR:;CAT:NONE;SFS:(376002)(366004)(346002)(396003)(39860400002)(136003)(6666004)(26005)(36756003)(316002)(83380400001)(1076003)(66556008)(5660300002)(16526019)(66476007)(186003)(7696005)(6486002)(2616005)(44832011)(52116002)(956004)(8936002)(38100700001)(4744005)(8676002)(6916009)(2906002)(66946007)(86362001)(4326008)(478600001);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 fFmz3bycadulDdDm77FaFJfv7/SyMEMkxXNclsS4LJSb0ytNwR9EWlniSUiKznKoaBq1xogrz0JPkylemUF7fJXLEv4ACodAOO/7tmjcdpmXubiOi4/8cSnNxV57V1QWgZJI9cTwJGLjf0oDrkQ6rjoz6QPJRYQIO+KJuSAdlrlUDegCgQnCu5xmjbHXqlCbI3tOZvLe1SMj90gzqrm6AUJK9854n0SWxVTz+xevj5BJUKgLnhj0ikFRN2zADT15xzx78rN4SYgXdt2y3usN9bHRRl7D8mKpuzxpI11NQDbWnVHSCoz0QzCLf2zWuWfBP7LpQPADfKNcQJqZBjbOc0jwpgJVCA88msY2PWimeRxpcBPGdFAm70JlXYkJKkQ7z9reU3U1uCuacgWLFjYf0pf17GSKKOAoXrq55IRvqyn5aV8xWuUJ2xtwF6KK1gj1Enj7eYkmbvjiuyxD0fWi/FXsctLQYr53N5LxzuI9Vx0AW5cCUiTvkAnLKntON4he8+OlQuUX6yI+st9M8VJIfBtg3LiQtqOXOFs5oixLIC1S2l+HKAoQFLzc3E+KhiCh52/1pmWKaBcoHEu9tq/gSw0uKZSjhe5QxgrOp93i/eiY/3s6BYp9Z1jbjPn94+XGauE2QfIUwaRWA3xtbFRrEmo3GfFgklAGddXQMpMSrOoKxBqdUVQ8d8HasWHMYvABj19hR5WDxaZXHAdQ7D52V44RNL7ABDCE+ryfiY8ZDs01rsHivqkmOFDHDHbPOZHL7GRBCcK/LtqpaP/FcbknPYPpVVbESbS6VgwESKF3S2VZX/EcQ13Q20XbewwyV0zhVqzZtmnXVIU5kDP4LyTuwqSaw7hEyQGUYJHV67EzUNStxxMx84HB9UG3yVjYUu2kCq5Cx4M4zkHo9iZVgpkdgaTxMC48bvYRug0qlPo7WENtgDxkQv/gWy6V7f5ICzuVnV/i9CsnVlQ5Tc878ELegEYJrcBMHFEjokx1kHhdHXWMnB9TyVDz99ZjHbeXcchyoXefnEOJEf3GoBjSnnrwm473noVN2+YyS0oZGqAsUiRJ2cTd5pOWcwcsGwf66NYqIbolEBML7QX6si26opfnPuYUV75UdqvAYJHuuhEy5PMDAlWK/MSKpYcv+p8tbObBAyDj8enYjIcNoSm8pDI0N11U8zL7zf03HDFAl/bjW/iIBkBvKgnEk2Zku2HPOlVza9rVQb1PEFE4um0BBHuRIrRxXWOCqo9d0jwjpZ7kdQGl7vOhnvZJizZpjStXHu80z9vRcmyZ+/Omkg2FIt/6GV/o+T0S8oiM3OHog2nf9iO0E08/hVo8KPVUq6+CuaQB
X-OriginatorOrg: oracle.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 0bde9b43-911f-4fc3-a913-08d8f5773a79
X-MS-Exchange-CrossTenant-AuthSource: SN6PR10MB3021.namprd10.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 02 Apr 2021 01:32:50.7458
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 4e2c6054-71cb-48f1-bd6c-3a9705aca71b
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 fic7n4QFmiRH4XYM6BIksdJUV3eoXaUCdwuVQCC408nnwE0qUBG3LzQMukF3jnQmGDjkadZS1mPRbmndg8fEizypbMYQ41ZyAaBTsp3quX0=
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SA2PR10MB4795
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9941
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 adultscore=0
 mlxscore=0 bulkscore=0
 suspectscore=0 phishscore=0 malwarescore=0 mlxlogscore=999 spamscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2103310000
 definitions=main-2104020008
X-Proofpoint-ORIG-GUID: rHDyIgTZUBQKVB7uHmn6sMzM-7UnWyV_
X-Proofpoint-GUID: rHDyIgTZUBQKVB7uHmn6sMzM-7UnWyV_
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9941
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 mlxscore=0
 impostorscore=0 phishscore=0
 bulkscore=0 adultscore=0 clxscore=1015 malwarescore=0 priorityscore=1501
 suspectscore=0 spamscore=0 mlxlogscore=999 lowpriorityscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2103310000
 definitions=main-2104020008
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

v5 -> v6:
	Rebased all patches.

[PATCH 1/5 v6] KVM: SVM: Define actual size of IOPM and MSRPM tables
[PATCH 2/5 v6] nSVM: Check addresses of MSR and IO permission maps
[PATCH 3/5 v6] KVM: nSVM: Cleanup in nested_svm_vmrun()
[PATCH 4/5 v6] nSVM: Test addresses of MSR and IO permissions maps
[PATCH 5/5 v6] SVM: Use ALIGN macro when aligning 'io_bitmap_area'

 arch/x86/kvm/svm/nested.c | 54 ++++++++++++++++++++++++++++++-----------------
 arch/x86/kvm/svm/svm.c    | 20 +++++++++---------
 arch/x86/kvm/svm/svm.h    |  3 +++
 3 files changed, 48 insertions(+), 29 deletions(-)

Krish Sadhukhan (3):
      KVM: SVM: Define actual size of IOPM and MSRPM tables
      nSVM: Check addresses of MSR and IO permission maps
      KVM: nSVM: Cleanup in nested_svm_vmrun()

 x86/svm.c       |  2 +-
 x86/svm_tests.c | 42 +++++++++++++++++++++++++++++++++++++++++-
 2 files changed, 42 insertions(+), 2 deletions(-)

Krish Sadhukhan (2):
      nSVM: Test addresses of MSR and IO permissions maps
      SVM: Use ALIGN macro when aligning 'io_bitmap_area'
```
#### [RFCv1 0/7] TDX and guest memory unmapping
##### From: "Kirill A. Shutemov" <kirill@shutemov.name>
X-Google-Original-From: "Kirill A. Shutemov" <kirill.shutemov@linux.intel.com>

```c
From patchwork Fri Apr  2 15:26:38 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Kirill A. Shutemov" <kirill@shutemov.name>
X-Patchwork-Id: 12181159
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D7DF3C43460
	for <kvm@archiver.kernel.org>; Fri,  2 Apr 2021 15:27:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B2ADF61165
	for <kvm@archiver.kernel.org>; Fri,  2 Apr 2021 15:27:04 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S235961AbhDBP1D (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 2 Apr 2021 11:27:03 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:58498 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S235198AbhDBP1B (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 2 Apr 2021 11:27:01 -0400
Received: from mail-lf1-x12e.google.com (mail-lf1-x12e.google.com
 [IPv6:2a00:1450:4864:20::12e])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 1AE46C0613E6
        for <kvm@vger.kernel.org>; Fri,  2 Apr 2021 08:27:00 -0700 (PDT)
Received: by mail-lf1-x12e.google.com with SMTP id o126so8115888lfa.0
        for <kvm@vger.kernel.org>; Fri, 02 Apr 2021 08:26:59 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=shutemov-name.20150623.gappssmtp.com; s=20150623;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=ZjsS1bI2uKq/2mrnLoFtUTJW7+/w5vjC+pfAdCGzd/4=;
        b=sLsxFjLldrKmyHyURfqQVaKuUqWfHVD0j45vA/YcBUS7CK7j45ipCGAFB8I3JUaul7
         EeEMeHuOsEsTv/LrV3rlZXAaQxWH6eHqX/HhMPc2amFnqgahdYRDYS01rQ3A3gNG09Q6
         /wpQeMSCIKilbzP9PBU+7XDjS3/CKdHWx5T4wwUIHeCsLzuHQfv2lJ0sHOn2ypoBLhsr
         ffP0o/FDsjV36uhUX+CKEbJ28/nBdgfXMNS+cPDy0ExO4c6D5sPQoPmVHZnpD4tMFq0A
         jDdGh3Vgx9XQFa3JfbWE5j+nPUsokwi2vRJ+mCVB5TiW94Z81EUfv0ybUkXSh2ftQIiD
         tN/g==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=ZjsS1bI2uKq/2mrnLoFtUTJW7+/w5vjC+pfAdCGzd/4=;
        b=ueOA2CBom28vTXeRF4Jo7KN9SxObl36rPVjngY0WdFS4irE+8X+3T/2l5L2FztozAn
         TAo7z6vgwsJjM3QpiVKQrnoyU0FJ0kK39FuaIep83SDd1jJWsMGb2pSZFbq4RSjZtlpy
         go6RmHC/Dh/ZH8Orw4dM4+btGv9L66EDRIxORzYllzYazby23D2+CQyOGI9kq7ndebxb
         wg3DBdTN+GXCQLD5212YKF21fzT0QS6wt8y9IS4mslvESYnHerqy2LPNJeQ+c/5ZidBZ
         PWMKyoJ8Yvp05tmvNOZfsLEwdrxaifh0YUts+H7SWQpzIFnHdfnRumYkn1V84IZT3kOS
         i7Qg==
X-Gm-Message-State: AOAM5322IBJod/4gCZK8GA2XQT5Rm9pnfeTWfmUWcjZ57gAqOFrdnk61
        z4k7anX/pCrtYCICjVrufcfnqw==
X-Google-Smtp-Source: 
 ABdhPJz8iSga8n37GQkADy+ssjbmrF28xrjeJGW7r3kmWl1I/wA1rNnTc3V3f/miI9fjdcL6UCQoyw==
X-Received: by 2002:a05:6512:21a:: with SMTP id
 a26mr9409958lfo.507.1617377218429;
        Fri, 02 Apr 2021 08:26:58 -0700 (PDT)
Received: from box.localdomain ([86.57.175.117])
        by smtp.gmail.com with ESMTPSA id
 o11sm950978ljg.42.2021.04.02.08.26.57
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 02 Apr 2021 08:26:57 -0700 (PDT)
From: "Kirill A. Shutemov" <kirill@shutemov.name>
X-Google-Original-From: "Kirill A. Shutemov" <kirill.shutemov@linux.intel.com>
Received: by box.localdomain (Postfix, from userid 1000)
        id 1E1E310257C; Fri,  2 Apr 2021 18:26:59 +0300 (+03)
To: Dave Hansen <dave.hansen@linux.intel.com>,
        Andy Lutomirski <luto@kernel.org>,
        Peter Zijlstra <peterz@infradead.org>,
        Sean Christopherson <seanjc@google.com>,
        Jim Mattson <jmattson@google.com>
Cc: David Rientjes <rientjes@google.com>,
        "Edgecombe, Rick P" <rick.p.edgecombe@intel.com>,
        "Kleen, Andi" <andi.kleen@intel.com>,
        "Yamahata, Isaku" <isaku.yamahata@intel.com>, x86@kernel.org,
        kvm@vger.kernel.org, linux-mm@kvack.org,
        linux-kernel@vger.kernel.org,
        "Kirill A. Shutemov" <kirill.shutemov@linux.intel.com>
Subject: [RFCv1 0/7] TDX and guest memory unmapping
Date: Fri,  2 Apr 2021 18:26:38 +0300
Message-Id: <20210402152645.26680-1-kirill.shutemov@linux.intel.com>
X-Mailer: git-send-email 2.26.3
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

TDX integrity check failures may lead to system shutdown host kernel must
not allow any writes to TD-private memory. This requirment clashes with
KVM design: KVM expects the guest memory to be mapped into host userspace
(e.g. QEMU).

This patchset aims to start discussion on how we can approach the issue.

The core of the change is in the last patch. Please see more detailed
description of the issue and proposoal of the solution there.

The patchset can also be found here:

git://git.kernel.org/pub/scm/linux/kernel/git/kas/linux.git kvm-unmapped-poison

Kirill A. Shutemov (7):
  x86/mm: Move force_dma_unencrypted() to common code
  x86/kvm: Introduce KVM memory protection feature
  x86/kvm: Make DMA pages shared
  x86/kvm: Use bounce buffers for KVM memory protection
  x86/kvmclock: Share hvclock memory with the host
  x86/realmode: Share trampoline area if KVM memory protection enabled
  KVM: unmap guest memory using poisoned pages

 arch/x86/Kconfig                     |   9 +-
 arch/x86/include/asm/cpufeatures.h   |   1 +
 arch/x86/include/asm/io.h            |   4 +-
 arch/x86/include/asm/kvm_para.h      |   5 +
 arch/x86/include/asm/mem_encrypt.h   |   7 +-
 arch/x86/include/uapi/asm/kvm_para.h |   3 +-
 arch/x86/kernel/kvm.c                |  20 ++++
 arch/x86/kernel/kvmclock.c           |   2 +-
 arch/x86/kernel/pci-swiotlb.c        |   3 +-
 arch/x86/kvm/Kconfig                 |   1 +
 arch/x86/kvm/cpuid.c                 |   3 +-
 arch/x86/kvm/mmu/mmu.c               |  15 ++-
 arch/x86/kvm/mmu/paging_tmpl.h       |  10 +-
 arch/x86/kvm/x86.c                   |   6 +
 arch/x86/mm/Makefile                 |   2 +
 arch/x86/mm/mem_encrypt.c            |  74 ------------
 arch/x86/mm/mem_encrypt_common.c     |  87 ++++++++++++++
 arch/x86/mm/pat/set_memory.c         |  10 ++
 arch/x86/realmode/init.c             |   7 +-
 include/linux/kvm_host.h             |  12 ++
 include/linux/swapops.h              |  20 ++++
 include/uapi/linux/kvm_para.h        |   5 +-
 mm/gup.c                             |  31 +++--
 mm/memory.c                          |  45 +++++++-
 mm/page_vma_mapped.c                 |   8 +-
 mm/rmap.c                            |   2 +-
 mm/shmem.c                           |   7 ++
 virt/kvm/Kconfig                     |   3 +
 virt/kvm/kvm_main.c                  | 164 ++++++++++++++++++++++++---
 29 files changed, 442 insertions(+), 124 deletions(-)
 create mode 100644 arch/x86/mm/mem_encrypt_common.c
```
#### [PATCH 0/4] KVM: MIPS: cleanup TLB flushing callbacks
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
From patchwork Fri Apr  2 15:58:03 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 12181275
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 415BFC433ED
	for <kvm@archiver.kernel.org>; Fri,  2 Apr 2021 15:58:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 197AC6115A
	for <kvm@archiver.kernel.org>; Fri,  2 Apr 2021 15:58:13 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S235716AbhDBP6N (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 2 Apr 2021 11:58:13 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:37130 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S235304AbhDBP6M (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 2 Apr 2021 11:58:12 -0400
Received: from mail-wr1-x434.google.com (mail-wr1-x434.google.com
 [IPv6:2a00:1450:4864:20::434])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id EAA15C0613E6;
        Fri,  2 Apr 2021 08:58:10 -0700 (PDT)
Received: by mail-wr1-x434.google.com with SMTP id v11so5098183wro.7;
        Fri, 02 Apr 2021 08:58:10 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=S0QE5Nife2NIX13JY3vSkhHVDcNV6ya5TJk20SNgM60=;
        b=NC+pT0qgC9xQpmNaSTJsqEc39jCvteZfOcGp7rQ8n19dtPtGdd30thQtLIPM5zqE74
         tqh9aqT/1FDmBkauXsR1FiRphQ/jL6Qq8T74rCSJgDAEYvnkvWr0QJ/uIPVYEoPh1ykT
         E8Jrm6YjqW/7qPJ6kvrWfoeihZzpLEENP4W3MYJgHwKHALs9PY1d5t+b/joXrF8KzBgn
         +VqgT1AE1Y72XP2vwQ40S9W8h6a20LU1ST9qcY5+AMvOhIiOLPw0w0LxkLG1b6GueSDX
         NQIMWBSxeG2Q4sYNMMNKM/h3s5f9V4fCowB0tghpxfohDglC36GsrtkvlydeL2HEzMZk
         g7FA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id
         :mime-version:content-transfer-encoding;
        bh=S0QE5Nife2NIX13JY3vSkhHVDcNV6ya5TJk20SNgM60=;
        b=IbjS3MPudPV3vKsz9g7OBkL6twqWTb01INRcZUjSBHVmBgi1D8pJ6wVjgSKw+J/0fO
         jOPYfYvUx2vKzPfhZZ/V8uNPkId+YTPB5pWs3DmKUsOifd2icfIatysbW+tvM5rHvPuw
         FFoV4YZ1cLIfo2DNlwgpKBLvsXh2fIEB052VDVAOOS821Lq13V3BN+zME9Sx5gYkjBqH
         gSQrGca8QO6ep9BS0rjHsEy9Zdu6aCMMaUOxnDOHBdbwIv/jattu1wOy6cx7uRkt5QAz
         o/izq+GzLimhqkJrdeaYZBYX7KchXFrLHK+t71s9/R7JScwFjKBOsxz+/V2vk17C6+2I
         qO/w==
X-Gm-Message-State: AOAM532gYF1dzG9D6Dare2OMwQt7hbZ8q44wTvBFT3fybBgV7R98VlXd
        Xt6BahwOEe3MBYxJSKZytlNZA6SXxBQ=
X-Google-Smtp-Source: 
 ABdhPJwNkDphDY/S8Bx896Z9h9IrXl46gV4kgtBZUbxfi2p8nYXB6gnA9bVu/jBYmNF4nAZvBgVXgw==
X-Received: by 2002:adf:8562:: with SMTP id 89mr16125989wrh.101.1617379089568;
        Fri, 02 Apr 2021 08:58:09 -0700 (PDT)
Received: from avogadro.lan ([2001:b07:6468:f312:c8dd:75d4:99ab:290a])
        by smtp.gmail.com with ESMTPSA id
 w11sm2293625wmb.35.2021.04.02.08.58.08
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 02 Apr 2021 08:58:09 -0700 (PDT)
Sender: Paolo Bonzini <paolo.bonzini@gmail.com>
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: chenhuacai@kernel.org, aleksandar.qemu.devel@gmail.com,
        seanjc@google.com, linux-mips@vger.kernel.org
Subject: [PATCH 0/4] KVM: MIPS: cleanup TLB flushing callbacks
Date: Fri,  2 Apr 2021 17:58:03 +0200
Message-Id: <20210402155807.49976-1-pbonzini@redhat.com>
X-Mailer: git-send-email 2.30.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series cleans up the flush_shadow_all and flush_shadow_memslot
callbacks, turning them into a single function that can be called from
kvm_arch_flush_remote_tlb.  This lets MIPS use the generic TLB flushing
code in the MMU notifiers.  With the upcoming refactoring of generic
MMU notifier code, without this patch MIPS would not be able to
coalesce TLB flushes anymore across multiple memslots.

Patch 1 is an unrelated cleanup that is needed for the rest to compile
(due to a call to kvm_arch_flush_remote_tlbs_memslot with a const
argument).

Paolo

Paolo Bonzini (4):
  KVM: constify kvm_arch_flush_remote_tlbs_memslot
  KVM: MIPS: rework flush_shadow_* callbacks into one that prepares the
    flush
  KVM: MIPS: let generic code call prepare_flush_shadow
  KVM: MIPS: defer flush to generic MMU notifier code

 arch/arm64/kvm/arm.c             |  2 +-
 arch/mips/include/asm/kvm_host.h | 12 ++++--------
 arch/mips/kvm/mips.c             | 21 +++++++++++----------
 arch/mips/kvm/mmu.c              | 12 ++----------
 arch/mips/kvm/trap_emul.c        | 13 ++-----------
 arch/mips/kvm/vz.c               | 19 ++++---------------
 arch/x86/kvm/mmu/mmu.c           |  2 +-
 include/linux/kvm_host.h         |  2 +-
 8 files changed, 26 insertions(+), 57 deletions(-)
```
#### [PATCH 0/4] KVM statistics data fd-based binary interface
##### From: Jing Zhang <jingzhangos@google.com>

```c
From patchwork Fri Apr  2 22:43:55 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jing Zhang <jingzhangos@google.com>
X-Patchwork-Id: 12181731
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.2 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id DF1FCC43460
	for <kvm@archiver.kernel.org>; Fri,  2 Apr 2021 22:44:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AF37861154
	for <kvm@archiver.kernel.org>; Fri,  2 Apr 2021 22:44:19 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S235626AbhDBWoT (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 2 Apr 2021 18:44:19 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:40424 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S234488AbhDBWoQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 2 Apr 2021 18:44:16 -0400
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 52370C061794
        for <kvm@vger.kernel.org>; Fri,  2 Apr 2021 15:44:14 -0700 (PDT)
Received: by mail-yb1-xb49.google.com with SMTP id f18so7785561ybq.3
        for <kvm@vger.kernel.org>; Fri, 02 Apr 2021 15:44:14 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=irIfy9SDJhrUqaDE5ZN6w1PVEQaG5IbsoR3bDTu0jl4=;
        b=oINmMmgMmoW/oyIcAkt+qHnpbVapAHO0BtBXorG5hnuc57P8B5zKJ7zBvQRstcANLe
         g5n4RamBX4W+J0lM7mec5Dp6K9/13ohk6ZXhVLCPFigMH64M84+iBExfaQf9hmAzQUiH
         bZY7VNQunFlIiJhRNQFdKfJbFOB0Z5ctHSCkx6H0TH0GoqpNH18oGgLzf1ZN153zxYSn
         am8EWHgEB72tVSDwUwtxKSTamIpb7vD/rP8Huv89Yo4aqk6V3/tf8JCDm3oqnXL+hCsQ
         02z6sYthCN9r+ritpQhL7w8X3C0Qqdj7AVHhTJsVELFIHoQjykQwl0v9h8r/bTrDVKjH
         X99w==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=irIfy9SDJhrUqaDE5ZN6w1PVEQaG5IbsoR3bDTu0jl4=;
        b=lxd9nHkpMeP8PxCJCYBwN2fU2PQuP092JRvdIim0UYckeTfK/BsMgk6R0fjPPnKzOg
         34vOGCIt6uE75MhjXrullrPvxbEQtVaRYvQ+I6UyaEw7iV0X8Kf8+/HG2gFjBTMqGjZt
         zWwu4nvwM4WNQurCRWXuJ/iFbzhhwRnFBw/LumGPdCGcNcvoGkC3aKUp3Rom2ULkgxAV
         9JfuRAxG3wtWqc305bU1ZVLvC72fkwoZ/Apn0eEYtWIIiJ9hAqTJq5BnaYGPKyrWNjRf
         HVD3I92vzOovZmOqUMgcxENuCxPoo+VPanBkEefya/j7j2V5EfJqNFa/CZmLlMRs1zJD
         j/iw==
X-Gm-Message-State: AOAM532IF0qSdqccO3QPJFi4hbzbBBiiKJzDXWdESUJR5m+n812EgFhg
        MF2d6Qi7xc9ORjwcLnpvfeo6fWv3wtK8meWlGfusARu2Eh4IB6suB30mhpuqaUbidqwkkFxr+AF
        plmkaQ088X8CF9jqFu9JKzvrGqAG5lLqvdeziT4xK6qYz9qtIMRFyTq6PpYQZiuBPtzlI4DI=
X-Google-Smtp-Source: 
 ABdhPJyjY/9bgZ4cfSTi5H9NxDPqiTmNCSs6veZkAE2t6SvpxZwTxmf38XzA4gMlvXfjJgmYTh/5eLdnr+RrZ8+4Rw==
X-Received: from jingzhangos.c.googlers.com
 ([fda3:e722:ac3:10:2b:ff92:c0a8:513])
 (user=jingzhangos job=sendgmr) by 2002:a25:4dc4:: with SMTP id
 a187mr21783146ybb.78.1617403453215; Fri, 02 Apr 2021 15:44:13 -0700 (PDT)
Date: Fri,  2 Apr 2021 22:43:55 +0000
Message-Id: <20210402224359.2297157-1-jingzhangos@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.0.208.g409f899ff0-goog
Subject: [PATCH 0/4] KVM statistics data fd-based binary interface
From: Jing Zhang <jingzhangos@google.com>
To: KVM <kvm@vger.kernel.org>, KVMARM <kvmarm@lists.cs.columbia.edu>,
        LinuxMIPS <linux-mips@vger.kernel.org>,
        KVMPPC <kvm-ppc@vger.kernel.org>,
        LinuxS390 <linux-s390@vger.kernel.org>,
        Linuxkselftest <linux-kselftest@vger.kernel.org>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Marc Zyngier <maz@kernel.org>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Will Deacon <will@kernel.org>,
        Huacai Chen <chenhuacai@kernel.org>,
        Aleksandar Markovic <aleksandar.qemu.devel@gmail.com>,
        Thomas Bogendoerfer <tsbogend@alpha.franken.de>,
        Paul Mackerras <paulus@ozlabs.org>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Janosch Frank <frankja@linux.ibm.com>,
        David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Claudio Imbrenda <imbrenda@linux.ibm.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Peter Shier <pshier@google.com>,
        Oliver Upton <oupton@google.com>,
        David Rientjes <rientjes@google.com>,
        Emanuele Giuseppe Esposito <eesposit@redhat.com>
Cc: Jing Zhang <jingzhangos@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patchset provides a file descriptor for every VM and VCPU to read
KVM statistics data in binary format.
It is meant to provide a lightweight, flexible, scalable and efficient
lock-free solution for user space telemetry applications to pull the
statistics data periodically for large scale systems. The pulling
frequency could be as high as a few times per second.
In this patchset, every statistics data are treated to have some
attributes as below:
  * architecture dependent or common
  * VM statistics data or VCPU statistics data
  * type: cumulative, instantaneous,
  * unit: none for simple counter, nanosecond, microsecond,
    millisecond, second, Byte, KiByte, MiByte, GiByte. Clock Cycles
Since no lock/synchronization is used, the consistency between all
the statistics data is not guaranteed. That means not all statistics
data are read out at the exact same time, since the statistics date
are still being updated by KVM subsystems while they are read out.

Jing Zhang (4):
  KVM: stats: Separate common stats from architecture specific ones
  KVM: stats: Add fd-based API to read binary stats data
  KVM: stats: Add documentation for statistics data binary interface
  KVM: selftests: Add selftest for KVM statistics data binary interface

 Documentation/virt/kvm/api.rst                | 169 ++++++++
 arch/arm64/include/asm/kvm_host.h             |   9 +-
 arch/arm64/kvm/guest.c                        |  42 +-
 arch/mips/include/asm/kvm_host.h              |   9 +-
 arch/mips/kvm/mips.c                          |  67 +++-
 arch/powerpc/include/asm/kvm_host.h           |   9 +-
 arch/powerpc/kvm/book3s.c                     |  68 +++-
 arch/powerpc/kvm/book3s_hv.c                  |  12 +-
 arch/powerpc/kvm/book3s_pr.c                  |   2 +-
 arch/powerpc/kvm/book3s_pr_papr.c             |   2 +-
 arch/powerpc/kvm/booke.c                      |  63 ++-
 arch/s390/include/asm/kvm_host.h              |   9 +-
 arch/s390/kvm/kvm-s390.c                      | 133 ++++++-
 arch/x86/include/asm/kvm_host.h               |   9 +-
 arch/x86/kvm/x86.c                            |  71 +++-
 include/linux/kvm_host.h                      | 132 ++++++-
 include/linux/kvm_types.h                     |  12 +
 include/uapi/linux/kvm.h                      |  48 +++
 tools/testing/selftests/kvm/.gitignore        |   1 +
 tools/testing/selftests/kvm/Makefile          |   3 +
 .../testing/selftests/kvm/include/kvm_util.h  |   3 +
 .../selftests/kvm/kvm_bin_form_stats.c        | 370 ++++++++++++++++++
 tools/testing/selftests/kvm/lib/kvm_util.c    |  11 +
 virt/kvm/kvm_main.c                           | 237 ++++++++++-
 24 files changed, 1401 insertions(+), 90 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/kvm_bin_form_stats.c


base-commit: f96be2deac9bca3ef5a2b0b66b71fcef8bad586d
```
