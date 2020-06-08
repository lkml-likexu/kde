#### [PATCH RFC v5 01/13] vhost: option to fetch descriptors through an independent struct
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 11591561
Return-Path: <SRS0=2dUt=7U=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9A89F13B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun,  7 Jun 2020 14:11:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7B567206C3
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun,  7 Jun 2020 14:11:37 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="IB38MuSE"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726679AbgFGOLf (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 7 Jun 2020 10:11:35 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:52593 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726595AbgFGOLa (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 7 Jun 2020 10:11:30 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1591539088;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=rBDX8velINEAtqraPcdgZxMSF664hQ9MVgqoZQFcfGw=;
        b=IB38MuSEWDqKRM50jCvbbuWuPxslUxiq1eqoJP0ByyNg4GqbK1xVbbPqWsAfL8z+bmmaDI
        qBOet6RPmh3NAB/ArKr14yjXQd+ojNjKfK2rHaegyhU3+Qehgn6U1FsuAYvuXIKZGyxmHy
        sZkA3WRETOoUCzbqStCXR9lemH0w5b8=
Received: from mail-wm1-f72.google.com (mail-wm1-f72.google.com
 [209.85.128.72]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-167-WBBEnereMTuEf6j9TMLc9g-1; Sun, 07 Jun 2020 10:11:26 -0400
X-MC-Unique: WBBEnereMTuEf6j9TMLc9g-1
Received: by mail-wm1-f72.google.com with SMTP id b63so4801091wme.1
        for <kvm@vger.kernel.org>; Sun, 07 Jun 2020 07:11:26 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:references
         :mime-version:content-disposition:content-transfer-encoding
         :in-reply-to;
        bh=rBDX8velINEAtqraPcdgZxMSF664hQ9MVgqoZQFcfGw=;
        b=fD25koOlNorzCqdLIwLY4tLFvS2TTDWG7cKo0gOr9rn6dM64bYRYPTJetLbZpi1BLJ
         VR5rHypksVQ7u/GrVhY5YEdObxNTAKcF4y41SkNB3bKXYAZeGisYBYAi58Urr1Aj5tKk
         gkUySNYYz6J1bGKwAkgxaaH4DlGkefLDzXEjrMELenYeqC/F54N+ajnL3Jld9lL2vsMx
         tmOMM5b202uYWLkUMWJJro9JFEeVlVuyD19E+56Epz0qeaAWtNwf3dCTLrmGR6DIDlkO
         KqOwhhZHG0KVtVEQBdzJTvDuaqa6kOYO4cIfgtD4unTNQ6g7QXByfw/B0tUDHOhpWshQ
         U2eA==
X-Gm-Message-State: AOAM530Vai7pgaHvukc8xFM0Eb6EYjez+vOCGIa7gjTL56rzvB3Y9kBP
        LzZ3TGBZBT/jHkkLRdS9Ta0c2U1tmc9B/rQKi4/sVlMWQnUAxtuQvB+2ZLZEWv04BJbUfa/ObnD
        2BnMECB4u1FUk
X-Received: by 2002:a7b:c113:: with SMTP id
 w19mr12670023wmi.161.1591539085345;
        Sun, 07 Jun 2020 07:11:25 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJxEhtivajEdaPK1Pzo4yqci7IekOFKYqVhoG5Q5Z658BdHAzA73gmATehqEd3Al5/RTgQTFWg==
X-Received: by 2002:a7b:c113:: with SMTP id
 w19mr12669994wmi.161.1591539084981;
        Sun, 07 Jun 2020 07:11:24 -0700 (PDT)
Received: from redhat.com (bzq-82-81-31-23.red.bezeqint.net. [82.81.31.23])
        by smtp.gmail.com with ESMTPSA id
 u9sm16315460wme.16.2020.06.07.07.11.23
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Sun, 07 Jun 2020 07:11:24 -0700 (PDT)
Date: Sun, 7 Jun 2020 10:11:23 -0400
From: "Michael S. Tsirkin" <mst@redhat.com>
To: linux-kernel@vger.kernel.org
Cc: kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org, Jason Wang <jasowang@redhat.com>,
        eperezma@redhat.com
Subject: [PATCH RFC v5 01/13] vhost: option to fetch descriptors through an
 independent struct
Message-ID: <20200607141057.704085-2-mst@redhat.com>
References: <20200607141057.704085-1-mst@redhat.com>
MIME-Version: 1.0
Content-Disposition: inline
In-Reply-To: <20200607141057.704085-1-mst@redhat.com>
X-Mailer: git-send-email 2.24.1.751.gd10ce2899c
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
Signed-off-by: Eugenio Pérez <eperezma@redhat.com>
Link: https://lore.kernel.org/r/20200401183118.8334-2-eperezma@redhat.com
Signed-off-by: Michael S. Tsirkin <mst@redhat.com>
---
 drivers/vhost/vhost.c | 302 +++++++++++++++++++++++++++++++++++++++++-
 drivers/vhost/vhost.h |  16 +++
 2 files changed, 317 insertions(+), 1 deletion(-)

```
