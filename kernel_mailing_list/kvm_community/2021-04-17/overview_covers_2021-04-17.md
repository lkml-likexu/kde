

#### [PATCH v3 0/2] KVM: selftests: fix races in dirty log test
##### From: Peter Xu <peterx@redhat.com>

```c
From patchwork Sat Apr 17 14:36:00 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 12209837
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 0FEE0C433B4
	for <kvm@archiver.kernel.org>; Sat, 17 Apr 2021 14:36:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D3220611AF
	for <kvm@archiver.kernel.org>; Sat, 17 Apr 2021 14:36:10 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S236486AbhDQOgd (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sat, 17 Apr 2021 10:36:33 -0400
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:32614 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S233008AbhDQOgd (ORCPT
        <rfc822;kvm@vger.kernel.org>); Sat, 17 Apr 2021 10:36:33 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1618670166;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=uonscLDjjSQatsblqLj37tpJBFSD05Khz4gELao+w6I=;
        b=M6faNwAuzck/F1LJYYZXmgjjRKXEO/yXYUkBig430nRxRg+SHM6qrPkZkr1EgmhVYJC8qe
        8ZOH3Ybv6fyqBT3QP3dJgitaBMxna6ZywG/uGqf8VSbalojw3iGYms6Bf9kacqyoN8VIiP
        oQ9yPxg3sEktHj5oegQDaPPOGFXKfHY=
Received: from mail-qv1-f71.google.com (mail-qv1-f71.google.com
 [209.85.219.71]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-28-b6ShR01jPJeZXA9chYziNg-1; Sat, 17 Apr 2021 10:36:05 -0400
X-MC-Unique: b6ShR01jPJeZXA9chYziNg-1
Received: by mail-qv1-f71.google.com with SMTP id
 99-20020a0c80ec0000b029017de514d56fso5673740qvb.17
        for <kvm@vger.kernel.org>; Sat, 17 Apr 2021 07:36:05 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=uonscLDjjSQatsblqLj37tpJBFSD05Khz4gELao+w6I=;
        b=lG3Y03EahWiHjwneKH/DGl1LICTRn2mZeKCwhr7BoqgFCG2sVCtJeWnYfyOcNLLnjt
         AUwOPSZxOqwNT2Q+uRULDUsLcrL0S9S29+8grspfJeOSkqFW4Go1jGAdwycExAC6jijH
         gzCH2uI4uEnoDmw0k6oXhQIUBnEbO1zCL7KdqRH8HOOrev/nwPbVF8v6e88n/9xcPmZM
         iKnays2ebB/NzRpbUjla/rrYmQm8NeKy0N3G/+aKwqGltoc8MEa4q0cwjrHu7Fc7zPYC
         ZwYGsWF7h5q09QeIJLZ3rmTFl37l2tfhEVqhY6NYhDluU9/fJ0HiB4vInr5SseG/ycUY
         iyyA==
X-Gm-Message-State: AOAM531O4cisf9nluI7IsgfEDXUyuDttDyVGorow0emc7SteKFea2OPO
        wI9f4I5bOspt/ZtpHZpWIDsMAZxSNbGgMLAiR7CyeIlV+cwGKJJWpNsCIXCHnn0gfG/De+ryl+J
        +DGvIIsb4g9LY
X-Received: by 2002:a05:620a:40ce:: with SMTP id
 g14mr4165037qko.190.1618670164292;
        Sat, 17 Apr 2021 07:36:04 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJxVO94n1NTk52uvMDVYt17h3ZZy04karbCuTj3Aylmb/lvHJlagc8HMuTdgRH/vXwhlSWmlgQ==
X-Received: by 2002:a05:620a:40ce:: with SMTP id
 g14mr4165019qko.190.1618670164007;
        Sat, 17 Apr 2021 07:36:04 -0700 (PDT)
Received: from xz-x1.redhat.com
 (bras-base-toroon474qw-grc-88-174-93-75-154.dsl.bell.ca. [174.93.75.154])
        by smtp.gmail.com with ESMTPSA id
 l12sm378159qtq.34.2021.04.17.07.36.02
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Sat, 17 Apr 2021 07:36:03 -0700 (PDT)
From: Peter Xu <peterx@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Andrew Jones <drjones@redhat.com>, peterx@redhat.com,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>
Subject: [PATCH v3 0/2] KVM: selftests: fix races in dirty log test
Date: Sat, 17 Apr 2021 10:36:00 -0400
Message-Id: <20210417143602.215059-1-peterx@redhat.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Please consider overtake the previous v2 [1] of this patch which is a single
patch, also please find more information in the commit message of each patch.

I kept the versioning since it solves the same problem, but mostly rewritten.

I've run a few hours of below workloads in parallel to test this patch:

  (1) while :; do taskset -c 1 ./dirty_log_test; done
  (2) taskset -c 1 bash -c "while :; do :; done"

Review comments are greatly welcomed.

Thanks,

[1] https://lore.kernel.org/lkml/20210413213641.23742-1-peterx@redhat.com/

Peter Xu (2):
  KVM: selftests: Sync data verify of dirty logging with guest sync
  KVM: selftests: Wait for vcpu thread before signal setup

 tools/testing/selftests/kvm/dirty_log_test.c | 68 +++++++++++++++++---
 1 file changed, 58 insertions(+), 10 deletions(-)
```
