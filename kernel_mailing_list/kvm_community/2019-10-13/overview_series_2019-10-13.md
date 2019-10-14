#### [kvm-unit-tests PATCH 1/1] x86: use pointer for end of exception table
##### From: Bill Wendling <morbo@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Bill Wendling <morbo@google.com>
X-Patchwork-Id: 11187253
Return-Path: <SRS0=sfVV=YG=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BDA301668
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 13 Oct 2019 07:22:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 9DE7A20700
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 13 Oct 2019 07:22:57 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="t3ajNdFA"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728285AbfJMHSc (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 13 Oct 2019 03:18:32 -0400
Received: from mail-ua1-f73.google.com ([209.85.222.73]:54864 "EHLO
        mail-ua1-f73.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727738AbfJMHSb (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 13 Oct 2019 03:18:31 -0400
Received: by mail-ua1-f73.google.com with SMTP id t16so3322643uae.21
        for <kvm@vger.kernel.org>; Sun, 13 Oct 2019 00:18:31 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=+jS/fgeA9g5b7maojEvnHW9C5zu2iR1VcbKtchXrGvo=;
        b=t3ajNdFAPbH26YVnunixwCMh9vPN7BKt9D6YzrtC3ehk7ZhWr/jvbrqDsDRAvud9hf
         kaGdgVDpgjHGN97SH/VxrfXqVae3h6a9Qt0Q2+bqDIz5afycMeGoqq3mUQ/HCrtVT8Bm
         MhDT8SzREjjpRnmF7JE09zhoFOJx7pH0UysOi0qkT1utQefu/BW00y4ZlwVpCEBFqKED
         hkksIT9+F3sYke8BZ5NGSMnTbdm0ouXmKSIXuzKiB6MNpHD/rr/c0ve960+RpQ6txZvd
         go7uLkDbk0206+x8UeeyqOcKliYef/5cbSH0CpK01fEm1oJ7Rk9w6Ip1C1VK7FrXfCzb
         yRIA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=+jS/fgeA9g5b7maojEvnHW9C5zu2iR1VcbKtchXrGvo=;
        b=hLgif0WqANvYo099urrcYgT78OTSJB1djDEpEU30jzEUAMCDnAg3QlNjyYi+P7jBED
         vsuLIO8FjCl63JB7Y/Uuf30YHBmlVhCFyfkh5zLk9+1emczLA1IazHFvuJKD+Iu7xgw1
         i8ehYRcGjgSfWi1JSVSOt8Su1VeJ+ayUEReWIweAcMNiOcUBR2VK49lfjwy2FkDtcxTE
         rR7aHARFyF7f8p5HbcP9mQJZI/wc3UYAzxiay/VGnSzVakbHsglFBS38Z69dvfSgN0fq
         eeMla7cKtlD6d0k7K97OfuEldzCXCBUzsWL+FUTMdt7aBLtZzanT9r1r6omQjmcfvmU2
         t0Pw==
X-Gm-Message-State: APjAAAWgG0ZExFTLdfjQ4q2mCumvDDqMk32B5kGE/hX+GRG8EevLj37w
        aQIBMSjatmc6/hi7SkimZLEisvc3sWmDZ0ERfz3JwYO3NUosCHSgMIsbES/tR5K6NAYNCvYap3d
        zqMfTDU9uyyfoU4neoV/8dlVeoa5BAEoqaYRKnFkfcfoibLfOA5gftw==
X-Google-Smtp-Source: 
 APXvYqynd2e3ep5GXfzDTkYLzLXqia4dttmm50W9SXS9/5bSl3EjdABMtGtRsx3EJHUEQGnMwEd9gqif2g==
X-Received: by 2002:ab0:1644:: with SMTP id l4mr7507361uae.30.1570951110442;
 Sun, 13 Oct 2019 00:18:30 -0700 (PDT)
Date: Sun, 13 Oct 2019 00:18:24 -0700
In-Reply-To: <20191012074454.208377-2-morbo@google.com>
Message-Id: <20191013071824.222946-1-morbo@google.com>
Mime-Version: 1.0
References: <20191012074454.208377-2-morbo@google.com>
X-Mailer: git-send-email 2.23.0.700.g56cf767bdb-goog
Subject: [kvm-unit-tests PATCH 1/1] x86: use pointer for end of exception
 table
From: Bill Wendling <morbo@google.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com, alexandru.elisei@arm.com
Cc: jmattson@google.com, Bill Wendling <morbo@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Two global objects can't have the same address in C. Clang uses this
fact to omit the check on the first iteration of the loop in
check_exception_table.

Signed-off-by: Bill Wendling <morbo@google.com>
---
 lib/x86/desc.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH RFC v3 1/4] vhost: option to fetch descriptors through an independent struct
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 11187281
Return-Path: <SRS0=sfVV=YG=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 615DD17EE
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 13 Oct 2019 08:08:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 43734206B7
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 13 Oct 2019 08:08:11 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728647AbfJMIIF (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 13 Oct 2019 04:08:05 -0400
Received: from mx1.redhat.com ([209.132.183.28]:33198 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728587AbfJMIIF (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 13 Oct 2019 04:08:05 -0400
Received: from mail-qk1-f200.google.com (mail-qk1-f200.google.com
 [209.85.222.200])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-GCM-SHA256 (128/128 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 7B279C049E12
        for <kvm@vger.kernel.org>; Sun, 13 Oct 2019 08:08:04 +0000 (UTC)
Received: by mail-qk1-f200.google.com with SMTP id k67so13797007qkc.3
        for <kvm@vger.kernel.org>; Sun, 13 Oct 2019 01:08:04 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:references
         :mime-version:content-disposition:in-reply-to;
        bh=+/GkkSCzJmvqURCVbcPYAZb5gFGG07qWLd0OPmKAkg0=;
        b=PQ/B9KW+AP1/G9qXts66xWuLSj9arO8aI2BiMi4mHzxPjK2gTgoTGzLPwVCkG8lLRU
         YRtMFeE2llgvQLuP96gDRnPqAQJCollluLX97ojbSIeU/j2qJ6gwGFywHZQTTr1Xc0Y1
         oX4LmWSAtf+QkI5aA2rHP3xui9cZrpcWQp3wpY9HcSi6f/FMo/sMg7NbjVcPg9lrql1Y
         jxiPafk9berEEqaCaK29LZ6qjieiX6MGy9DvowL3o5JCjw5haEjxIUXMlxSr7E9ZoLiO
         wYmZTkG5mtjtrCdaH16Q/bs5nxOnVqeM8MpwmIZVIAQBi4L3k/D9NeTb/oQC+8UucMiL
         iPwg==
X-Gm-Message-State: APjAAAWbD+iEMkcUEwR8qalSRBLHxfWU8QwOH6L9fUpqpceRp9QpkC5c
        R1w6Ojp0QV/zwVEBIuhchGXa+qvx5SFpGC65lUglKllirLnRz25Xj8pBoxMk0uT2t4am+kwKY/i
        wyHXJJB7iJqF7
X-Received: by 2002:a05:620a:6d5:: with SMTP id
 21mr23669511qky.117.1570954083571;
        Sun, 13 Oct 2019 01:08:03 -0700 (PDT)
X-Google-Smtp-Source: 
 APXvYqwnMw3QIAs0zZSqJpMV0lu1jHX2CoIEd/DOACXEIn/p9jR4/KSrQuRKhIFs+UObqO/nKMU+3Q==
X-Received: by 2002:a05:620a:6d5:: with SMTP id
 21mr23669488qky.117.1570954083017;
        Sun, 13 Oct 2019 01:08:03 -0700 (PDT)
Received: from redhat.com (bzq-79-176-10-77.red.bezeqint.net. [79.176.10.77])
        by smtp.gmail.com with ESMTPSA id
 m15sm6070763qka.104.2019.10.13.01.08.00
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Sun, 13 Oct 2019 01:08:02 -0700 (PDT)
Date: Sun, 13 Oct 2019 04:07:58 -0400
From: "Michael S. Tsirkin" <mst@redhat.com>
To: linux-kernel@vger.kernel.org
Cc: kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org, Jason Wang <jasowang@redhat.com>
Subject: [PATCH RFC v3 1/4] vhost: option to fetch descriptors through an
 independent struct
Message-ID: <20191013080742.16211-2-mst@redhat.com>
References: <20191013080742.16211-1-mst@redhat.com>
MIME-Version: 1.0
Content-Disposition: inline
In-Reply-To: <20191013080742.16211-1-mst@redhat.com>
X-Mailer: git-send-email 2.22.0.678.g13338e74b8
X-Mutt-Fcc: =sent
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The idea is to support multiple ring formats by converting
to a format-independent array of descriptors.

This costs extra cycles, but we gain in ability
to fetch a batch of descriptors in one go, which
is good for code cache locality.

When used, this causes a minor performance degradation,
it's been kept as simple as possible for ease of review.
A follow-up patch gets us back the performance by adding batching.

To simplify benchmarking, I kept the old code around so one can switch
back and forth between old and new code. This will go away in the final
submission.

Signed-off-by: Michael S. Tsirkin <mst@redhat.com>
---
 drivers/vhost/vhost.c | 308 +++++++++++++++++++++++++++++++++++++++++-
 drivers/vhost/vhost.h |  16 +++
 2 files changed, 323 insertions(+), 1 deletion(-)

```
#### [PATCH RFC v4 1/5] vhost: option to fetch descriptors through an independent struct
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 11187371
Return-Path: <SRS0=sfVV=YG=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7E73014DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 13 Oct 2019 11:42:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 592AE207FF
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 13 Oct 2019 11:42:42 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729202AbfJMLmK (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 13 Oct 2019 07:42:10 -0400
Received: from mx1.redhat.com ([209.132.183.28]:49776 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729180AbfJMLmJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 13 Oct 2019 07:42:09 -0400
Received: from mail-qt1-f198.google.com (mail-qt1-f198.google.com
 [209.85.160.198])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-GCM-SHA256 (128/128 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id DB3473DE0C
        for <kvm@vger.kernel.org>; Sun, 13 Oct 2019 11:42:08 +0000 (UTC)
Received: by mail-qt1-f198.google.com with SMTP id h20so14846510qto.7
        for <kvm@vger.kernel.org>; Sun, 13 Oct 2019 04:42:08 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:references
         :mime-version:content-disposition:in-reply-to;
        bh=PI1OE6x8g5LqN3R020BkL+Iyzzcb4S2vFUq4EN7DNS8=;
        b=cV16oKRReYj1tBb6iJ8QYJnE3obvb/gA3L2bhVd5VmTtCKiOtdxix9xEDmxbbiahU/
         I6RHUBFyt1D7Q1n9VxYA72D5XqjnWh2DeRVqtux2sU6f4lwHf5k4akvBO1wX1zIu4G2g
         uUKXtB1QXXru2oazZ0FK3AKlpcIqzfhyiTQ4VONFO5V3QQW4GEwQMICOS+CfjbuMwGYI
         bZqmD882kOkHa3Z5C98db810Ig3PIzYAgoivLcXXYei4QKPd28uOYFemXnclY8UYuBD3
         PYLV4ooPwEKpiokMO9My38vdIkAFgQP3hTw67RaZ/fpVKDd6gFmj8HoUE5zSy2QjyD/q
         k/eQ==
X-Gm-Message-State: APjAAAXpElUsJlWl4cDiEAvqgmqzpSgIEY43LSo2st2feyYkB0sDf+GR
        So+YRdF3jGeJ0MztoNj6vqIlb1r4feHHDtYHB4s/BohR1K+RWSJFK/PtJRos50OJQAYjzo1juF4
        cL2wpCjjdAnMq
X-Received: by 2002:ac8:4749:: with SMTP id k9mr27114066qtp.257.1570966928039;
        Sun, 13 Oct 2019 04:42:08 -0700 (PDT)
X-Google-Smtp-Source: 
 APXvYqy3RLJYrJ5NNXdkUElIuLiGnQ2C3NgTOU/0E+J9k43WX/uk/sb7gBiRk0kW3qclPV96RCq62w==
X-Received: by 2002:ac8:4749:: with SMTP id k9mr27114042qtp.257.1570966927565;
        Sun, 13 Oct 2019 04:42:07 -0700 (PDT)
Received: from redhat.com (bzq-79-176-10-77.red.bezeqint.net. [79.176.10.77])
        by smtp.gmail.com with ESMTPSA id
 187sm7059026qki.80.2019.10.13.04.42.05
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Sun, 13 Oct 2019 04:42:06 -0700 (PDT)
Date: Sun, 13 Oct 2019 07:42:03 -0400
From: "Michael S. Tsirkin" <mst@redhat.com>
To: linux-kernel@vger.kernel.org
Cc: kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org, Jason Wang <jasowang@redhat.com>
Subject: [PATCH RFC v4 1/5] vhost: option to fetch descriptors through an
 independent struct
Message-ID: <20191013113940.2863-2-mst@redhat.com>
References: <20191013113940.2863-1-mst@redhat.com>
MIME-Version: 1.0
Content-Disposition: inline
In-Reply-To: <20191013113940.2863-1-mst@redhat.com>
X-Mailer: git-send-email 2.22.0.678.g13338e74b8
X-Mutt-Fcc: =sent
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The idea is to support multiple ring formats by converting
to a format-independent array of descriptors.

This costs extra cycles, but we gain in ability
to fetch a batch of descriptors in one go, which
is good for code cache locality.

When used, this causes a minor performance degradation,
it's been kept as simple as possible for ease of review.
A follow-up patch gets us back the performance by adding batching.

To simplify benchmarking, I kept the old code around so one can switch
back and forth between old and new code. This will go away in the final
submission.

Signed-off-by: Michael S. Tsirkin <mst@redhat.com>
---
 drivers/vhost/vhost.c | 294 +++++++++++++++++++++++++++++++++++++++++-
 drivers/vhost/vhost.h |  16 +++
 2 files changed, 309 insertions(+), 1 deletion(-)

```
