#### [PATCH v3 1/5] KVM: selftests: Rename vm_handle_exceptionFrom: Ricardo Koller <ricarkol@google.com>
##### From: Ricardo Koller <ricarkol@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ricardo Koller <ricarkol@google.com>
X-Patchwork-Id: 12255009
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 70669C433B4
	for <kvm@archiver.kernel.org>; Thu, 13 May 2021 00:37:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5544061413
	for <kvm@archiver.kernel.org>; Thu, 13 May 2021 00:37:18 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S239454AbhEMAiY (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 12 May 2021 20:38:24 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:55950 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1346522AbhEMAgg (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 12 May 2021 20:36:36 -0400
Received: from mail-pl1-x64a.google.com (mail-pl1-x64a.google.com
 [IPv6:2607:f8b0:4864:20::64a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 26C73C061362
        for <kvm@vger.kernel.org>; Wed, 12 May 2021 17:28:07 -0700 (PDT)
Received: by mail-pl1-x64a.google.com with SMTP id
 z15-20020a170903018fb02900ef27498ce1so5697017plg.8
        for <kvm@vger.kernel.org>; Wed, 12 May 2021 17:28:07 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=JNTIckp/c/wIJdLM9riA2E5Tzb0NAF8GpY3mjrOIzWw=;
        b=mR1g+4RKX5l67W45s/ogwNgDOgsP/pBqA8UHoATQdQkE4dWvETmBmqh5Y9kHtV1S9Q
         GeopUrzMowsC6kJ99C6fiMDH1C31jwOH89Rl0BtW2ox6IAl81luouwI4XTn28qWjTkFJ
         CEMDKJ1dvdsk9sdXGT+AQpcjRa917+0kDxTCI/hLCgx2Yd7yC37Bg4OKH3yVFRyiwQFE
         JpLubN6jRxBOo66SoZAHwIReDzinXngPGRl4riYsQT3mjpFraXDHlldMJzLC494J6kr7
         /bysmEBIb50y/NGmQ8ZfJl7iKS82HakYl/+4Ro9Gq1iWhaWjwRYeoXWERPjbGmuFp8z1
         prOw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=JNTIckp/c/wIJdLM9riA2E5Tzb0NAF8GpY3mjrOIzWw=;
        b=Pi37QE8oX3L0jf+KIXKKprGNi766MXq+SS+krps3Cak+sMTkntDh3THixF+KP4nGXP
         n0ZYgqdnKu61QHyoc4iuxWLtnaBaO+SE+NVCGz81d7q80GxV+nxC67DDPChd5vMipJYw
         CxtQJZrO9WtySdsDKPgRXeROh9U4x8aD7P+AyIkE9WUmbGTTnAQJL4yJDNw3e4GrGrK7
         pHRkU3gVui1zxJf5lQm1buJv6nCF9CrvpZf4QLbLcZeYFNC1WqEqOq443nYihxOu+WPc
         F/k9pKXjjV3mZXZ4DW0UJaN7+9KU5HH+QaaiFi7xd0fhENIzIEIn9ojDiltDjTAm7lmS
         //Dw==
X-Gm-Message-State: AOAM531+qmgLlcUB9EdkTXAqYZxDJafY/9Ld8ki0gFn5gPUUsYYY2aGA
        LCvBaj4CBaZ5V5q3dCxTSOE9+1uUV0Bu3OYOGB5glI5W6/r0X0Gpa7KrPoEWSE0kUda7tAOQ0FV
        DPfNOm58XB+EGEQmdJ+T/nInNRJGR6oSB/adkyTXj93eu1Vy11dUl0MuIwA0IyM8=
X-Google-Smtp-Source: 
 ABdhPJxNkQIDpG9TnashRF3YpGekq+hYFaWJw5BUV9b8Pe+Qu17xFimV42Yz2Tk9sYx2fF+JqDCKAd8VB87k/g==
X-Received: from ricarkol2.c.googlers.com
 ([fda3:e722:ac3:10:24:72f4:c0a8:62fe])
 (user=ricarkol job=sendgmr) by 2002:a17:902:7589:b029:ed:492a:6ac6 with SMTP
 id j9-20020a1709027589b02900ed492a6ac6mr38534508pll.62.1620865686436; Wed, 12
 May 2021 17:28:06 -0700 (PDT)
Date: Wed, 12 May 2021 17:27:58 -0700
In-Reply-To: <20210513002802.3671838-1-ricarkol@google.com>
Message-Id: <20210513002802.3671838-2-ricarkol@google.com>
Mime-Version: 1.0
References: <20210513002802.3671838-1-ricarkol@google.com>
X-Mailer: git-send-email 2.31.1.607.g51e8a6a459-goog
Subject: [PATCH v3 1/5] KVM: selftests: Rename vm_handle_exception
From: Ricardo Koller <ricarkol@google.com>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu
Cc: pbonzini@redhat.com, maz@kernel.org, drjones@redhat.com,
        alexandru.elisei@arm.com, eric.auger@redhat.com,
        Ricardo Koller <ricarkol@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Rename the vm_handle_exception function to a name that indicates more
clearly that it installs something: vm_install_vector_handler.

Reviewed-by: Andrew Jones <drjones@redhat.com>
Reviewed-by: Eric Auger <eric.auger@redhat.com>
Suggested-by: Marc Zyngier <maz@kernel.org>
Suggested-by: Andrew Jones <drjones@redhat.com>
Signed-off-by: Ricardo Koller <ricarkol@google.com>
---
 tools/testing/selftests/kvm/include/x86_64/processor.h    | 2 +-
 tools/testing/selftests/kvm/lib/x86_64/processor.c        | 4 ++--
 tools/testing/selftests/kvm/x86_64/kvm_pv_test.c          | 2 +-
 .../selftests/kvm/x86_64/userspace_msr_exit_test.c        | 8 ++++----
 tools/testing/selftests/kvm/x86_64/xapic_ipi_test.c       | 2 +-
 5 files changed, 9 insertions(+), 9 deletions(-)

```
#### [PATCH v2 1/4] KVM: PPC: Book3S HV: exit halt polling on need_resched() as well
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 12255093
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id C5F51C433ED
	for <kvm@archiver.kernel.org>; Thu, 13 May 2021 01:58:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8EC4361412
	for <kvm@archiver.kernel.org>; Thu, 13 May 2021 01:58:22 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229854AbhEMB7a (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 12 May 2021 21:59:30 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:46474 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229801AbhEMB71 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 12 May 2021 21:59:27 -0400
Received: from mail-pf1-x429.google.com (mail-pf1-x429.google.com
 [IPv6:2607:f8b0:4864:20::429])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 86107C061574;
        Wed, 12 May 2021 18:58:17 -0700 (PDT)
Received: by mail-pf1-x429.google.com with SMTP id c13so6829360pfv.4;
        Wed, 12 May 2021 18:58:17 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=s6yds0eAnM4G0Wdu571RvhPi3TKjI+npGap0XFILkfE=;
        b=klaPh4iM4ryJKcK4ak5Gfiffhss4QGvganMQRvxA3qZPdfc3DZscvNZalHS2iYY7l7
         eh7k3GoMAAuKHe4bKB7A2eIgoI5YkAhZbeevFgMnQzAniRwfzgmKbrXup6XMFcuJXzuH
         OTlFUIcDR5se3vDF+RbYMJYyBuY5lpPA70fczLto5JJvhn+VQnWUDFXrYzSWT9dJ2oC+
         bYVn24RIOEWg2b48Qn3ScdJAyLMfMnOOUtnHVJqAmMP/lqcWIHUXK1eQJNwma3vxR9FZ
         cSwcvzxAwEXITjApPsOQginDTlbi1fzYtvh0sB9yAoez58SOwXoF5cuRkZ6ZGJQIblYE
         Qxbw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=s6yds0eAnM4G0Wdu571RvhPi3TKjI+npGap0XFILkfE=;
        b=dpfba45GmFGAh0uE1qSEakZRVq9vIFCvbZz3v4rq8I/ZyRQ/xRblrR5pdf6hHgwdh3
         5blhSSVvu1drDNzHFIpPl4XvUzA7uctGho9Ow6Mxzwr/cgZhnF/y/ffqqWGpCszga/XN
         /wHU5x2LuuDVyeiD4AdL12xfIDoXKYlFZtmmwz4bpvWYVZnW/+Rxe/F/Q4grxOwfDOUf
         80CAJHgBWrYP10Q8uy9JE9GqwA6kcAUKe8VS+u2OEM/TzoJOX0yxBvYnrF6rQ/jYYnld
         /1iWyop8ffVGau9hQIOBPk84fHEZgQ6aZd+Q5sfuT3x6M7c3GElQKRS6f3bvSAwePVT4
         5m1A==
X-Gm-Message-State: AOAM533Brl+1339A0uPd18e5vaL0d4PJGtRUCwxjA61qyDSuvK+zHWIr
        bvwhQh9/FAj6clDw5ohADCpvWNfiJoo=
X-Google-Smtp-Source: 
 ABdhPJwlNz0fWh1ClQWl8HOGpto3Gg0232jmHcD6gUChaiSQ/a7krLx/KvJDva1shE16JBeioyGFvQ==
X-Received: by 2002:a17:90a:fd95:: with SMTP id
 cx21mr1777447pjb.137.1620871096858;
        Wed, 12 May 2021 18:58:16 -0700 (PDT)
Received: from localhost.localdomain ([103.7.29.6])
        by smtp.googlemail.com with ESMTPSA id
 b7sm799560pjq.36.2021.05.12.18.58.12
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Wed, 12 May 2021 18:58:15 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Ben Segall <bsegall@google.com>,
        Venkatesh Srinivas <venkateshs@chromium.org>,
        David Matlack <dmatlack@google.com>,
        Paul Mackerras <paulus@ozlabs.org>,
        Suraj Jitindar Singh <sjitindarsingh@gmail.com>
Subject: [PATCH v2 1/4] KVM: PPC: Book3S HV: exit halt polling on
 need_resched() as well
Date: Thu, 13 May 2021 09:58:04 +0800
Message-Id: <1620871084-4639-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

Inspired by commit 262de4102c7bb8 (kvm: exit halt polling on need_resched()
as well), CFS_BANDWIDTH throttling will use resched_task() when there is just
one task to get the task to block. It was likely allowing VMs to overrun their
quota when halt polling. Due to PPC implements an arch specific halt polling
logic, we should add the need_resched() checking there as well.

Cc: Ben Segall <bsegall@google.com>
Cc: Venkatesh Srinivas <venkateshs@chromium.org>
Cc: Jim Mattson <jmattson@google.com> 
Cc: David Matlack <dmatlack@google.com>
Cc: Paul Mackerras <paulus@ozlabs.org>
Cc: Suraj Jitindar Singh <sjitindarsingh@gmail.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
v1 -> v2:
 * update patch description

 arch/powerpc/kvm/book3s_hv.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
