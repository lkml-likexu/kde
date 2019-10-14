

#### [PATCH RFC v3 0/4] vhost: ring format independence
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
From patchwork Sun Oct 13 08:07:52 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 11187279
Return-Path: <SRS0=sfVV=YG=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 430FD1575
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 13 Oct 2019 08:08:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 25104206A3
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 13 Oct 2019 08:08:11 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728322AbfJMIH7 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 13 Oct 2019 04:07:59 -0400
Received: from mx1.redhat.com ([209.132.183.28]:46522 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728073AbfJMIH7 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 13 Oct 2019 04:07:59 -0400
Received: from mail-qt1-f197.google.com (mail-qt1-f197.google.com
 [209.85.160.197])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-GCM-SHA256 (128/128 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 1AB3E81F18
        for <kvm@vger.kernel.org>; Sun, 13 Oct 2019 08:07:59 +0000 (UTC)
Received: by mail-qt1-f197.google.com with SMTP id t25so14544255qtq.9
        for <kvm@vger.kernel.org>; Sun, 13 Oct 2019 01:07:59 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:mime-version
         :content-disposition;
        bh=yhYWl1Umy/1VTjIbbiNd2BN64NH6epCZE/mb8RSLaXM=;
        b=A3rAC975lbPOLzEhXGDqIVGPvxIbP28sgE7xBMU1GqmcIvgZiq/DeAXfpJ7MtJFVYl
         mwhIE85vtS142sPlR+EIYsSDvmlSpTWEORGojjJE7v+ZdlDzeudLr7e1jpvMb/pe5YnP
         wb1QbKs6Ei+LvhdEM3Iz+6SBlVD/6AvyHZfnw0bcDc61MeVWA8DoHCLaliohh/EjUx9i
         ddFC7yTNjeVfU9qToOnjCCt77KWEKJ2gYFuCA2B/kbELTcjVESh6Bw7rWPm03pxXAzQh
         RpccmG6hUESByvu3ZOU9cHpfKuLBtBvy8VtItJBTwRLx9ZJxFyxeZEwbQIOsPfuJ+dgP
         eI1A==
X-Gm-Message-State: APjAAAU3xbFGLqgBjv+sjIJvuKb4lWU7G95SJuWs5ut2x+QODe34SiHm
        ManVYwO0iA+OP8v7OdMt3m4AENP6Lm7dGYPbv94CoV3XXha3LSrFTBHRhhpuDiCrYTVRyruXlAU
        TgE2JT+4kXnx8
X-Received: by 2002:a37:9a05:: with SMTP id c5mr23746934qke.98.1570954078376;
        Sun, 13 Oct 2019 01:07:58 -0700 (PDT)
X-Google-Smtp-Source: 
 APXvYqxdHllinWFJ1shL2L0dscS9heDbinJBHlNcirUbgmYpZ/ksUyJvF3jXeQkMuv9YmookTDp0DQ==
X-Received: by 2002:a37:9a05:: with SMTP id c5mr23746919qke.98.1570954078076;
        Sun, 13 Oct 2019 01:07:58 -0700 (PDT)
Received: from redhat.com (bzq-79-176-10-77.red.bezeqint.net. [79.176.10.77])
        by smtp.gmail.com with ESMTPSA id
 q8sm7301621qtj.76.2019.10.13.01.07.54
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Sun, 13 Oct 2019 01:07:57 -0700 (PDT)
Date: Sun, 13 Oct 2019 04:07:52 -0400
From: "Michael S. Tsirkin" <mst@redhat.com>
To: linux-kernel@vger.kernel.org
Cc: kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org, Jason Wang <jasowang@redhat.com>
Subject: [PATCH RFC v3 0/4] vhost: ring format independence
Message-ID: <20191013080742.16211-1-mst@redhat.com>
MIME-Version: 1.0
Content-Disposition: inline
X-Mailer: git-send-email 2.22.0.678.g13338e74b8
X-Mutt-Fcc: =sent
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This adds infrastructure required for supporting
multiple ring formats.

The idea is as follows: we convert descriptors to an
independent format first, and process that converting to
iov later.

The point is that we have a tight loop that fetches
descriptors, which is good for cache utilization.
This will also allow all kind of batching tricks -
e.g. it seems possible to keep SMAP disabled while
we are fetching multiple descriptors.

This seems to perform exactly the same as the original
code already based on a microbenchmark.
Lightly tested.
More testing would be very much appreciated.

To use new code:
	echo 1 > /sys/module/vhost_test/parameters/newcode
or
	echo 1 > /sys/module/vhost_net/parameters/newcode

Changes from v2:
	- fixed indirect descriptor batching

Changes from v1:
	- typo fixes


Michael S. Tsirkin (4):
  vhost: option to fetch descriptors through an independent struct
  vhost/test: add an option to test new code
  vhost: batching fetches
  vhost/net: add an option to test new code

 drivers/vhost/net.c   |  32 +++-
 drivers/vhost/test.c  |  19 ++-
 drivers/vhost/vhost.c | 340 +++++++++++++++++++++++++++++++++++++++++-
 drivers/vhost/vhost.h |  20 ++-
 4 files changed, 397 insertions(+), 14 deletions(-)
```
#### [PATCH RFC v4 0/5] vhost: ring format independence
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
From patchwork Sun Oct 13 11:41:55 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 11187361
Return-Path: <SRS0=sfVV=YG=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 951C214DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 13 Oct 2019 11:42:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7F62520882
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 13 Oct 2019 11:42:05 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729141AbfJMLmE (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 13 Oct 2019 07:42:04 -0400
Received: from mx1.redhat.com ([209.132.183.28]:60700 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728997AbfJMLmE (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 13 Oct 2019 07:42:04 -0400
Received: from mail-qk1-f198.google.com (mail-qk1-f198.google.com
 [209.85.222.198])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-GCM-SHA256 (128/128 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id EC41A83F3E
        for <kvm@vger.kernel.org>; Sun, 13 Oct 2019 11:42:03 +0000 (UTC)
Received: by mail-qk1-f198.google.com with SMTP id s28so14077100qkm.5
        for <kvm@vger.kernel.org>; Sun, 13 Oct 2019 04:42:03 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:mime-version
         :content-disposition;
        bh=WhM42HnkXorw8ZktlIqV/yS0IRHKb5HISbW//fiFIIA=;
        b=Xjk2l5DfNnEPpgnM0bsdK8kfEkJCH8adjOMU+0Jye07xyfaFZyRA6ADwS4PqwzdPiR
         X2TldZCKsdw6ZXfQIXDu8F3QsUwHi6z7b/ILa23dyfM1kk7CRlE7NPMcxORL/rGA0+T5
         J4IfitsuYj3jAh3VW3i+gUoloM5VHaooVEH58JnfauV0HDzODEV5/MQgAC0mDiLshYsx
         rZfDS8nZEk5kWuVb0D6boGXcs+DO5/2CWy4jcv6Zq6lpHeQ1MBB/COOTXzuPzh2IQ4gN
         c7CYJX63B1SsUIyJBguX4rhBS6FGirL3ykmd7ePLhB6/P9gJlQve9c9VvWuflJPOEhhn
         /PUg==
X-Gm-Message-State: APjAAAU60Hg15tayfiIHcM6p/ni5aAOD5+WBeWAvPrM1DGlHFAtRPhOP
        7uBOoW4rvS1jEeDMmFy3tN6J6SpuWzPA937e8Kf0MvmA/YDyjUjo8iIJRFRQ0RkHQGjm4vWst0z
        qPIaDNKe7FXaH
X-Received: by 2002:a37:a14d:: with SMTP id
 k74mr25294018qke.308.1570966922926;
        Sun, 13 Oct 2019 04:42:02 -0700 (PDT)
X-Google-Smtp-Source: 
 APXvYqxJbPZHmjjRtZPdn0OIP4+7Md8xReA9OfG4qhSoToCuN8Mn6p7CW5fNAnas5HTHE7lcLL2Caw==
X-Received: by 2002:a37:a14d:: with SMTP id
 k74mr25293998qke.308.1570966922588;
        Sun, 13 Oct 2019 04:42:02 -0700 (PDT)
Received: from redhat.com (bzq-79-176-10-77.red.bezeqint.net. [79.176.10.77])
        by smtp.gmail.com with ESMTPSA id
 d25sm1763837qtj.84.2019.10.13.04.41.59
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Sun, 13 Oct 2019 04:42:01 -0700 (PDT)
Date: Sun, 13 Oct 2019 07:41:55 -0400
From: "Michael S. Tsirkin" <mst@redhat.com>
To: linux-kernel@vger.kernel.org
Cc: kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org, Jason Wang <jasowang@redhat.com>
Subject: [PATCH RFC v4 0/5] vhost: ring format independence
Message-ID: <20191013113940.2863-1-mst@redhat.com>
MIME-Version: 1.0
Content-Disposition: inline
X-Mailer: git-send-email 2.22.0.678.g13338e74b8
X-Mutt-Fcc: =sent
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This adds infrastructure required for supporting
multiple ring formats.

The idea is as follows: we convert descriptors to an
independent format first, and process that converting to
iov later.

The point is that we have a tight loop that fetches
descriptors, which is good for cache utilization.
This will also allow all kind of batching tricks -
e.g. it seems possible to keep SMAP disabled while
we are fetching multiple descriptors.

This seems to perform exactly the same as the original
code already based on a microbenchmark.
Lightly tested.
More testing would be very much appreciated.

To use new code:
	echo 1 > /sys/module/vhost_test/parameters/newcode
or
	echo 1 > /sys/module/vhost_net/parameters/newcode

changes from v3:
        - fixed error handling in case of indirect descriptors
        - add BUG_ON to detect buffer overflow in case of bugs
                in response to comment by Jason Wang
        - minor code tweaks

Changes from v2:
	- fixed indirect descriptor batching
                reported by Jason Wang

Changes from v1:
	- typo fixes


Michael S. Tsirkin (5):
  vhost: option to fetch descriptors through an independent struct
  vhost/test: add an option to test new code
  vhost: batching fetches
  vhost/net: add an option to test new code
  vhost: last descriptor must have NEXT clear

 drivers/vhost/net.c   |  32 ++++-
 drivers/vhost/test.c  |  19 ++-
 drivers/vhost/vhost.c | 328 +++++++++++++++++++++++++++++++++++++++++-
 drivers/vhost/vhost.h |  20 ++-
 4 files changed, 385 insertions(+), 14 deletions(-)
```
