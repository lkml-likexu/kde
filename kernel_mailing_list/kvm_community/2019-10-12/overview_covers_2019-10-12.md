

#### [PATCH net-next 0/3] vhost_net: access ptr ring using tap recvmsg
##### From: prashantbhole.linux@gmail.com
From: Prashant Bhole <prashantbhole.linux@gmail.com>

```c
From patchwork Sat Oct 12 01:53:54 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: prashantbhole.linux@gmail.com
X-Patchwork-Id: 11186537
Return-Path: <SRS0=yg+T=YF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D1C0E14ED
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 12 Oct 2019 01:54:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B1CD6214E0
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 12 Oct 2019 01:54:36 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="U1Z90jMN"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728059AbfJLByf (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 11 Oct 2019 21:54:35 -0400
Received: from mail-pf1-f194.google.com ([209.85.210.194]:41408 "EHLO
        mail-pf1-f194.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726903AbfJLBye (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 11 Oct 2019 21:54:34 -0400
Received: by mail-pf1-f194.google.com with SMTP id q7so7079266pfh.8;
        Fri, 11 Oct 2019 18:54:34 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=XR2n34xXjC/7ocn7v74lqd3awYFNRTOmHAVF9A1J9OU=;
        b=U1Z90jMNlXgVvmjnXsQs15YRgwC9WJW/iX0G0SRcbHymiifo6JzpAQYHoXocJ6yv8t
         TKqjH2rU5JWMzPYgeDIWdtm5qt/7/xJ1KtCW+O1A9mjPG0R7nttRHX2fWG3aUyIS5vBM
         +FTNr4d0NzroXLjHENuu4NgU9bIz3ROH5xhkr2H2wpVot0ZaDpPdmQXLOKdvyo+mwt/T
         RDxJUHbabpnHeD1fjmadNUtQArLDunRG3S7vJ4Z9Z5JvRIdP457Ny8DgrpmqOPPNNCk1
         rze9Hc1fZhJZ1U/RkD8Y83GAhkC+fE42IyhXkiOxcb/wA+fgtnJ+qW/osJ79Fz7B9WCM
         41RQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=XR2n34xXjC/7ocn7v74lqd3awYFNRTOmHAVF9A1J9OU=;
        b=FKl7KuODxSmBFQYFhZd6XaF+1EiwyOxzm6QMwBtsuJ4FxDUBxG2tRvpsvwGEFTxQ1V
         W/blJ/IYQffLqMzVYb91X/OQ01lACm9+dYacNrc7F91D3mcVCM4Os8/bogBKpN3ezH/u
         UwNhivOaPZRL9UZSexgDkhuxIAD2ydWNgkYWUoJpNulDUEJRZcbiiNgoYwM+sH5x1+Ml
         02Dx5dxEq2nKOk+nR5TubAiDqmJP4zvVHdD4Z8MHV5gl1RXm4fOjOXIl/s8G95nx/pbE
         dSU3DCFQQjcKge0Jk/Pn8XJ7ndWZe/1L/Vr0wpL7k7vG6KVT6hFXZnuKx+8gCQIk7YHV
         BTKQ==
X-Gm-Message-State: APjAAAUIPqKyBx4TT4kiIxHrO50p2uoq2pZStQYvnIiP2O1br+lJs+P6
        lOhGw/PGRCl3m5bU8FF5ROo=
X-Google-Smtp-Source: 
 APXvYqzGEv7ahV5HYDXwoKttYyR7AVek3+lc6pBmvHkkAjwJAxR1YRK6ZUHwVhBEaytbBLk75yk88Q==
X-Received: by 2002:a62:2783:: with SMTP id
 n125mr1983129pfn.167.1570845274086;
        Fri, 11 Oct 2019 18:54:34 -0700 (PDT)
Received: from localhost.localdomain (KD124211219252.ppp-bb.dion.ne.jp.
 [124.211.219.252])
        by smtp.gmail.com with ESMTPSA id
 e127sm10992187pfe.37.2019.10.11.18.54.31
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 11 Oct 2019 18:54:33 -0700 (PDT)
From: prashantbhole.linux@gmail.com
To: "Michael S . Tsirkin" <mst@redhat.com>,
        Jason Wang <jasowang@redhat.com>,
        "David S . Miller" <davem@davemloft.net>
Cc: Prashant Bhole <prashantbhole.linux@gmail.com>,
        David Ahern <dsahern@gmail.com>, kvm@vger.kernel.org,
        netdev@vger.kernel.org
Subject: [PATCH net-next 0/3] vhost_net: access ptr ring using tap recvmsg
Date: Sat, 12 Oct 2019 10:53:54 +0900
Message-Id: <20191012015357.1775-1-prashantbhole.linux@gmail.com>
X-Mailer: git-send-email 2.21.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Prashant Bhole <prashantbhole.linux@gmail.com>

vhost_net needs to peek tun packet sizes to allocate virtio buffers.
Currently it directly accesses tap ptr ring to do it. Jason Wang
suggested to achieve this using msghdr->msg_control and modifying the
behavior of tap recvmsg.

This change will be useful in future in case of virtio-net XDP
offload. Where packets will be XDP processed in tap recvmsg and vhost
will see only non XDP_DROP'ed packets.

Patch 1: reorganizes the tun_msg_ctl so that it can be extended by
 the means of different commands. tap sendmsg recvmsg will behave
 according to commands.

Patch 2: modifies recvmsg implementation to produce packet pointers.
 vhost_net uses recvmsg API instead of ptr_ring_consume().

Patch 3: removes ptr ring usage in vhost and functions those export
 ptr ring from tun/tap.

Prashant Bhole (3):
  tuntap: reorganize tun_msg_ctl usage
  vhost_net: user tap recvmsg api to access ptr ring
  tuntap: remove usage of ptr ring in vhost_net

 drivers/net/tap.c      | 44 ++++++++++++++---------
 drivers/net/tun.c      | 45 +++++++++++++++---------
 drivers/vhost/net.c    | 79 ++++++++++++++++++++++--------------------
 include/linux/if_tun.h |  9 +++--
 4 files changed, 103 insertions(+), 74 deletions(-)
```
#### [PATCH RFC v2 0/2] vhost: ring format independence
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
From patchwork Sat Oct 12 19:18:44 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 11186945
Return-Path: <SRS0=yg+T=YF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7AE66912
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 12 Oct 2019 19:18:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 65260222C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 12 Oct 2019 19:18:55 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729806AbfJLTSw (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 12 Oct 2019 15:18:52 -0400
Received: from mx1.redhat.com ([209.132.183.28]:33704 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729432AbfJLTSv (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 12 Oct 2019 15:18:51 -0400
Received: from mail-qt1-f197.google.com (mail-qt1-f197.google.com
 [209.85.160.197])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-GCM-SHA256 (128/128 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 17AAD81DE8
        for <kvm@vger.kernel.org>; Sat, 12 Oct 2019 19:18:51 +0000 (UTC)
Received: by mail-qt1-f197.google.com with SMTP id r15so13302993qtn.12
        for <kvm@vger.kernel.org>; Sat, 12 Oct 2019 12:18:51 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:mime-version
         :content-disposition;
        bh=XSSfcNJSuQK6tbBIRVqD8nyyhs8/n5qs+oek7V16gWg=;
        b=qEuJ2ms49Bte6lnK+Lg4qvrcZlgJb+5I2mEAZ3Lial1Y2rULG/07wIlaJjQoYsdusn
         4L0VuThAJfRknCihRlfhy2Yks0DRo53V/GAqzh2iEgNpvvvgZoBIQOTJu4TXuOsdbUO8
         WVRdAQ8SmA35AwCMHKMZyeDhmG9E2EFgp2r3KRKPuhXNmCeBVlicQ+xPOF9ZAKhyxxPC
         jVjdsWY+Zf2WXxuLs7+PIYndSK/suWuaLne0Q9ccOhxu0o+tjnkbDY8uHduQORsyXkai
         mfXNbODGa63xWqQhW19Jw/hAO5OF3byZlbLCAnan1Pyisp1AcPbT6RwAYxXiJajlk1C3
         haTQ==
X-Gm-Message-State: APjAAAUzgfPhwnKt1ytCdWF/kNWhHV7cYHIb/1G52l+vwzyuncRffO4z
        da3MYHpyizAzCq6hb9H4/NmINthvhYpLlbgHOg3xWi2lbJzMwcelKm4d6wStKRUG0bS9Uu02I/f
        6oEoraHs9MMh4
X-Received: by 2002:a37:b8f:: with SMTP id 137mr21665700qkl.466.1570907930052;
        Sat, 12 Oct 2019 12:18:50 -0700 (PDT)
X-Google-Smtp-Source: 
 APXvYqyYVcRWvZEcwbiX5JXr6fNk4W01ojqCtNq7uXnEznHUo/iukXYBpKClYnD6en9lTNPNSsx0Ow==
X-Received: by 2002:a37:b8f:: with SMTP id 137mr21665681qkl.466.1570907929802;
        Sat, 12 Oct 2019 12:18:49 -0700 (PDT)
Received: from redhat.com (bzq-79-176-10-77.red.bezeqint.net. [79.176.10.77])
        by smtp.gmail.com with ESMTPSA id
 x55sm7350774qta.74.2019.10.12.12.18.46
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Sat, 12 Oct 2019 12:18:48 -0700 (PDT)
Date: Sat, 12 Oct 2019 15:18:44 -0400
From: "Michael S. Tsirkin" <mst@redhat.com>
To: linux-kernel@vger.kernel.org
Cc: kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org, Jason Wang <jasowang@redhat.com>
Subject: [PATCH RFC v2 0/2] vhost: ring format independence
Message-ID: <20191012191820.8050-1-mst@redhat.com>
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
More testing would be very much appreciated.

Biggest TODO before this first step is ready to go in is to
batch indirect descriptors as well.

Integrating into vhost-net is basically
s/vhost_get_vq_desc/vhost_get_vq_desc_batch/ -
or add a module parameter like I did in the test module.


Changes from v1:
	- typo fixes

Michael S. Tsirkin (2):
  vhost: option to fetch descriptors through an independent struct
  vhost: batching fetches

 drivers/vhost/test.c  |  19 ++-
 drivers/vhost/vhost.c | 333 +++++++++++++++++++++++++++++++++++++++++-
 drivers/vhost/vhost.h |  20 ++-
 3 files changed, 365 insertions(+), 7 deletions(-)
```
