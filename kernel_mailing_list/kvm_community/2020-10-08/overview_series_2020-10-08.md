#### [PATCH 01/35] fs: introduce dmemfs module
##### From: yulei.kernel@gmail.com

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: yulei zhang <yulei.kernel@gmail.com>
X-Patchwork-Id: 11822301
Return-Path: <SRS0=lzrU=DP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EAC00109B
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  8 Oct 2020 07:53:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AC43521924
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  8 Oct 2020 07:53:32 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="oj426ml9"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728418AbgJHHx3 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 8 Oct 2020 03:53:29 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:51786 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725899AbgJHHx3 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 8 Oct 2020 03:53:29 -0400
Received: from mail-pf1-x442.google.com (mail-pf1-x442.google.com
 [IPv6:2607:f8b0:4864:20::442])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 25448C0613D2;
        Thu,  8 Oct 2020 00:53:29 -0700 (PDT)
Received: by mail-pf1-x442.google.com with SMTP id x22so3294014pfo.12;
        Thu, 08 Oct 2020 00:53:29 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :in-reply-to:references;
        bh=PpGMDQVveSnL4hAMh4jtybKG1eOjYS1M5jvQhB105cE=;
        b=oj426ml97WT/RNTqwQTs0CwCzfg2cbYR4xc2iVimdK+SNB5/05si5k8oCoHNrZCNXg
         jIW8j9PshRowyt6PiAfXAhfM3XJniAM/xcTHsbW35YSJnV5alOjZB/my8FbSswkgtbAi
         ZR2vPJQQ2mS1CT5xR18pJgwdXigmlqAhowEFs1HyR/b548A4DfV6eJofS4HYTCZ1KExQ
         F1m4sK+1NXRtr73xe1dkO4hxUtvO8lnbcLvEASSDIiG0z2CLtWZX6+cyjHweqc863QIq
         CyL+a6zrvLApUrtvUTnfVQAQhh6n7oecOV7vpOOMknvlua/nF9ac7zpeNUCm8YXTyibQ
         eLHA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:in-reply-to:references;
        bh=PpGMDQVveSnL4hAMh4jtybKG1eOjYS1M5jvQhB105cE=;
        b=slpIil7lZ1Tuz36xU48cBrrCVOzlx4Jo2yWczPjLUW/1dOmtHdvHatYXHRPj2myuKf
         XycYpdHD7EG7O7wBNPzIUsNRoDuHiNHX391qxXsjuGwjG/NCd5E1Za7DsN1R3Z9QAXe8
         NDURb6cofFowdtiQkD26lXhdSjM36z2gcOG30L8OCI1BMOXiEouV4yf5ukT2JDqrAfoC
         GH4vtfw7j9A3zF2cqWkoHaaK7QLZ25hxXisSPqRRDzsnIv1JWu6/rzvC5RiwDDHRikFe
         vA5QGqpjpJc7WumPNov7IulfpLdP04ULiMCXB+YX5SqsRHX3B+6oq1OIoiEW6RA6c7AL
         9v5g==
X-Gm-Message-State: AOAM533VxQIkiH2fsGsm6R7K/SgydVm31jE2Df0pyTb0njpn9dMYxY/u
        HaH91Qqens+bznP8DTumRXo=
X-Google-Smtp-Source: 
 ABdhPJxJedQZTY5EG7HomEYXY1tfz0id+kobQNH9f2jmxI3zfeVYTcxCbti+nlZAWEbUMHaUDjVH5g==
X-Received: by 2002:a63:7841:: with SMTP id t62mr6279888pgc.183.1602143608642;
        Thu, 08 Oct 2020 00:53:28 -0700 (PDT)
Received: from localhost.localdomain ([203.205.141.61])
        by smtp.gmail.com with ESMTPSA id
 k206sm6777106pfd.126.2020.10.08.00.53.25
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 08 Oct 2020 00:53:28 -0700 (PDT)
From: yulei.kernel@gmail.com
X-Google-Original-From: yuleixzhang@tencent.com
To: akpm@linux-foundation.org, naoya.horiguchi@nec.com,
        viro@zeniv.linux.org.uk, pbonzini@redhat.com
Cc: linux-fsdevel@vger.kernel.org, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, xiaoguangrong.eric@gmail.com,
        kernellwp@gmail.com, lihaiwei.kernel@gmail.com,
        Yulei Zhang <yuleixzhang@tencent.com>,
        Xiao Guangrong <gloryxiao@tencent.com>
Subject: [PATCH 01/35] fs: introduce dmemfs module
Date: Thu,  8 Oct 2020 15:53:51 +0800
Message-Id: 
 <aa553faf9e97ee9306ecd5a67d3324a34f9ed4be.1602093760.git.yuleixzhang@tencent.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <cover.1602093760.git.yuleixzhang@tencent.com>
References: <cover.1602093760.git.yuleixzhang@tencent.com>
In-Reply-To: <cover.1602093760.git.yuleixzhang@tencent.com>
References: <cover.1602093760.git.yuleixzhang@tencent.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Yulei Zhang <yuleixzhang@tencent.com>

dmemfs (Direct Memory filesystem) is device memory or reserved
memory based filesystem. This kind of memory is special as it
is not managed by kernel and it is without 'struct page'.

The original purpose of dmemfs is to drop the usage of
'struct page' to save extra system memory.

This patch introduces the basic framework of dmemfs and only
mkdir and create regular file are supported.

Signed-off-by: Xiao Guangrong  <gloryxiao@tencent.com>
Signed-off-by: Yulei Zhang <yuleixzhang@tencent.com>
---
 fs/Kconfig                 |   1 +
 fs/Makefile                |   1 +
 fs/dmemfs/Kconfig          |  13 ++
 fs/dmemfs/Makefile         |   7 +
 fs/dmemfs/inode.c          | 275 +++++++++++++++++++++++++++++++++++++
 include/uapi/linux/magic.h |   1 +
 6 files changed, 298 insertions(+)
 create mode 100644 fs/dmemfs/Kconfig
 create mode 100644 fs/dmemfs/Makefile
 create mode 100644 fs/dmemfs/inode.c

```
#### [GIT PULL] vhost,vdpa: last minute fixes
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 11824523
Return-Path: <SRS0=lzrU=DP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8749D1752
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  8 Oct 2020 20:31:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5E1E522227
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  8 Oct 2020 20:31:03 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="M2zZYYdJ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730449AbgJHUa7 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 8 Oct 2020 16:30:59 -0400
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:40538 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1730427AbgJHUa6 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 8 Oct 2020 16:30:58 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1602189057;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type;
        bh=lgT/Pao2dhRy7r2cOmOSyyn/G9gLMf1e4iWJG7ETJJY=;
        b=M2zZYYdJ5+q+9TleHTorYoPeLeaQ/nhamfBEfqyigEje8LU5drjh6BmyAOpV+aVx+XGfx5
        4X5eo7mbSVR9yA90vRjWjRWEHmxQ2cbzdo/DTxpi6Zpzcz8AAm2aKKC+kqTyQq6Ut6F14D
        hzjlO1nKEtxYHCUWWHgT5KogDayU0CQ=
Received: from mail-wr1-f70.google.com (mail-wr1-f70.google.com
 [209.85.221.70]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-38-UiQ-HzdaM0W3lmMvC-bfBQ-1; Thu, 08 Oct 2020 16:30:55 -0400
X-MC-Unique: UiQ-HzdaM0W3lmMvC-bfBQ-1
Received: by mail-wr1-f70.google.com with SMTP id u15so4333816wrn.4
        for <kvm@vger.kernel.org>; Thu, 08 Oct 2020 13:30:55 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:mime-version
         :content-disposition;
        bh=lgT/Pao2dhRy7r2cOmOSyyn/G9gLMf1e4iWJG7ETJJY=;
        b=cBVfdqM8638cQ0Q9boyrcHdTFLQXOyVVrJQTBV0XTdQbGO8WcbtOVi3jdZEvmWybhO
         KckJrGOOnRYKlsZD4+khJGr1PorGUmJ/qhWmCAFhETSGEjSpjjJpfnAQFvJTD1PCub9I
         8TTVMy9KQw/JFJbi7m66giJdR9jQxT5l19hScdXIl9LsRXxerQrLRPvx/WWtOV82eHNQ
         hqKThVuL+Pedce4XfNWx+fHhLaQH0n3J88UAVf2OnToEDbo5Jvl2+LwdEbss5Ciw3xM6
         3dKQtN18ljJiIXNbgbKwLxm7qq5gSZuJEh9+Z28ncbqwcAZxyxUjqF9WD7wF1enLqH1B
         ydQw==
X-Gm-Message-State: AOAM533mOhHT3Hk7MH3Zbxv1tLZUpmbNXQT9DveuCSi06I3OktmdOKBn
        G9VNrrQW6sfjuD6r7ZER+q6p6G4pqd8r9fEJFEf8oRLM0EPhPXJ9T+td/Ac+xJBIRSZYgh3GZZO
        tLBIMYq0RPOrD
X-Received: by 2002:a7b:c305:: with SMTP id k5mr10972361wmj.102.1602189054221;
        Thu, 08 Oct 2020 13:30:54 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJz39hXz1Of1vVfE+ExLOVbu6aOgDjiquQ4GfgQ/XcsmEw8zvuDHbrPJdW4dVAvGz1TOUqEloQ==
X-Received: by 2002:a7b:c305:: with SMTP id k5mr10972350wmj.102.1602189054015;
        Thu, 08 Oct 2020 13:30:54 -0700 (PDT)
Received: from redhat.com (bzq-79-179-71-128.red.bezeqint.net.
 [79.179.71.128])
        by smtp.gmail.com with ESMTPSA id
 a81sm9549014wmf.32.2020.10.08.13.30.51
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 08 Oct 2020 13:30:53 -0700 (PDT)
Date: Thu, 8 Oct 2020 16:30:51 -0400
From: "Michael S. Tsirkin" <mst@redhat.com>
To: Linus Torvalds <torvalds@linux-foundation.org>
Cc: kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org, linux-kernel@vger.kernel.org,
        elic@nvidia.com, groug@kaod.org, jasowang@redhat.com,
        lkp@intel.com, michael.christie@oracle.com, mst@redhat.com,
        si-wei.liu@oracle.com, stable@vger.kernel.org
Subject: [GIT PULL] vhost,vdpa: last minute fixes
Message-ID: <20201008163051-mutt-send-email-mst@kernel.org>
MIME-Version: 1.0
Content-Disposition: inline
X-Mutt-Fcc: =sent
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The following changes since commit a127c5bbb6a8eee851cbdec254424c480b8edd75:

  vhost-vdpa: fix backend feature ioctls (2020-09-24 05:54:36 -0400)

are available in the Git repository at:

  https://git.kernel.org/pub/scm/linux/kernel/git/mst/vhost.git tags/for_linus

for you to fetch changes up to aff90770e54cdb40228f2ab339339e95d0aa0c9a:

  vdpa/mlx5: Fix dependency on MLX5_CORE (2020-10-08 16:02:00 -0400)

----------------------------------------------------------------
vhost,vdpa: last minute fixes

Some last minute fixes. The last two of them haven't been in next but
they do seem kind of obvious, very small and safe, fix bugs reported in
the field, and they are both in a new mlx5 vdpa driver, so it's not like
we can introduce regressions.

Signed-off-by: Michael S. Tsirkin <mst@redhat.com>

----------------------------------------------------------------
Eli Cohen (1):
      vdpa/mlx5: Fix dependency on MLX5_CORE

Greg Kurz (3):
      vhost: Don't call access_ok() when using IOTLB
      vhost: Use vhost_get_used_size() in vhost_vring_set_addr()
      vhost: Don't call log_access_ok() when using IOTLB

Mike Christie (1):
      vhost vdpa: fix vhost_vdpa_open error handling

Si-Wei Liu (3):
      vhost-vdpa: fix vhost_vdpa_map() on error condition
      vhost-vdpa: fix page pinning leakage in error path
      vdpa/mlx5: should keep avail_index despite device status

 drivers/vdpa/Kconfig              |   7 +--
 drivers/vdpa/mlx5/net/mlx5_vnet.c |  20 ++++--
 drivers/vhost/vdpa.c              | 127 +++++++++++++++++++++++---------------
 drivers/vhost/vhost.c             |  33 +++++++---
 4 files changed, 117 insertions(+), 70 deletions(-)
```
#### [KVMTOOL][PATCHv2] vhost-net: enable multiqueue supportThread-Topic: [KVMTOOL][PATCHv2] vhost-net: enable multiqueue support
##### From: BARBALACE Antonio <antonio.barbalace@ed.ac.uk>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: BARBALACE Antonio <antonio.barbalace@ed.ac.uk>
X-Patchwork-Id: 11822525
Return-Path: <SRS0=lzrU=DP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 05D5D14D5
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  8 Oct 2020 09:33:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CDBB92168B
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  8 Oct 2020 09:33:22 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726304AbgJHJdV convert rfc822-to-8bit (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 8 Oct 2020 05:33:21 -0400
Received: from loire.is.ed.ac.uk ([129.215.16.10]:58282 "EHLO
        loire.is.ed.ac.uk" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725852AbgJHJdV (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 8 Oct 2020 05:33:21 -0400
Received: from exseed.ed.ac.uk (hbdkb3.is.ed.ac.uk [129.215.235.37])
        by loire.is.ed.ac.uk (8.14.7/8.14.7) with ESMTP id 0989XBim022186
        (version=TLSv1/SSLv3 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128
 verify=NOT);
        Thu, 8 Oct 2020 10:33:13 +0100
Received: from hbdat3.is.ed.ac.uk (129.215.235.38) by hbdkb3.is.ed.ac.uk
 (129.215.235.37) with Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256) id 15.1.1979.3; Thu, 8 Oct 2020
 10:32:52 +0100
Received: from EUR03-VE1-obe.outbound.protection.outlook.com (104.47.9.59) by
 hbdat3.is.ed.ac.uk (129.215.235.38) with Microsoft SMTP Server
 (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256) id 15.1.1979.3
 via Frontend Transport; Thu, 8 Oct 2020 10:32:52 +0100
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=cbna8jBR232KeHUcgM9R4umKBQagquoZP6Xgth4In6jMcO9Hq17JYoqd7atTWqzKLa/WK/M9bxPhkPWqVqZAuObwz8SexpWDfcMFWjc0hmKbWhyCWF+pwXRvX9fIO8x0Cz37PqLVgopUrbCZihN3eAlHvko4OQfSKbeeo0v7h6Q8y6iUVaEPioGq9w2L98hi1NvHj+DHPyciIg7nqVnhwerSUdqtAQEKplMLlLEwO6jMM7rRMwforOb2RsPcC8EtfumeM32Ayr1hhv1X3gZNKAdrPTWBOWHKcwrMZetmJfQqeRbAIncJiX+FKMNwpxp5r+Iuky0X7lI81z7Dkg25cA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=n7dPhnQN1wt8kuY2HJBu8aVom3glChCXsK0YxGRsq18=;
 b=J81ZI2HWr9CPjqBuH6Uf4wA78/d1TpowcxXe9h0tuErAzZIA3pbH8SzzpPX+SCrGxgzr6PXNVrBmE9RRZwdDBy3wSjMQ+1wtXV1ycb6npbSv84maDWFq7htyJDLftgpyyKF0rWNUsy4LnIK602q6jOzZFye3jA2e9cJl4D28zLZ46V11LAPYRIPXgz62e399y1NwEEPOkLUNt6499EdPSppoWiYhW2CiDQoqZnqb4xzMLrjhLtbr2aUpFSczvZ/eGd08m7bhPqgbnc5wg3xbF8QstlZNCFj+j2eqVIgZ78U4ZMnfD0O23lNTbzOkWZl+VnHcmI721xMW17GoDKEUSw==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=ed.ac.uk; dmarc=pass action=none header.from=ed.ac.uk;
 dkim=pass header.d=ed.ac.uk; arc=none
Received: from AM7PR05MB7076.eurprd05.prod.outlook.com (2603:10a6:20b:1af::19)
 by AM6PR05MB4261.eurprd05.prod.outlook.com (2603:10a6:209:48::28) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3433.37; Thu, 8 Oct
 2020 09:32:50 +0000
Received: from AM7PR05MB7076.eurprd05.prod.outlook.com
 ([fe80::c9af:88a9:6fef:7b63]) by AM7PR05MB7076.eurprd05.prod.outlook.com
 ([fe80::c9af:88a9:6fef:7b63%5]) with mapi id 15.20.3433.045; Thu, 8 Oct 2020
 09:32:50 +0000
From: BARBALACE Antonio <antonio.barbalace@ed.ac.uk>
To: "kvm@vger.kernel.org" <kvm@vger.kernel.org>
CC: "will@kernel.org" <will@kernel.org>,
        "julien.thierry.kdev@gmail.com" <julien.thierry.kdev@gmail.com>
Subject: [KVMTOOL][PATCHv2] vhost-net: enable multiqueue support
Thread-Topic: [KVMTOOL][PATCHv2] vhost-net: enable multiqueue support
Thread-Index: AdadVWEwOQ9y4UqITcOAQyOmbaWZGw==
Date: Thu, 8 Oct 2020 09:32:50 +0000
Message-ID: 
 <AM7PR05MB7076C36757D01A87A86FF330CC0B0@AM7PR05MB7076.eurprd05.prod.outlook.com>
Accept-Language: en-GB, en-US
Content-Language: en-US
X-MS-Has-Attach: 
X-MS-TNEF-Correlator: 
authentication-results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=ed.ac.uk;
x-originating-ip: [82.38.204.131]
x-ms-publictraffictype: Email
x-ms-office365-filtering-correlation-id: d19d1ac3-1ba5-4960-7030-08d86b6d2025
x-ms-traffictypediagnostic: AM6PR05MB4261:
x-microsoft-antispam-prvs: 
 <AM6PR05MB4261160CA560B8437F0D12E0CC0B0@AM6PR05MB4261.eurprd05.prod.outlook.com>
x-ms-oob-tlc-oobclassifiers: OLM:4303;
x-ms-exchange-senderadcheck: 1
x-microsoft-antispam: BCL:0;
x-microsoft-antispam-message-info: 
 0txeHuX0KNG5RecswD/yAnJNILFNTAcUmteTV+gKOsg4W+CynnAo2tPdpFlaN7xsg24Ktw/oJqZ2MAlIOzkRHeC1YBNT0IRin2u65chAOmejVfVhA7OA8oaRyHNABjyDbuq+PNkxGXX2lu6Npr1XopZ0DflVk1KPl53DcgpMKbHblsY3UNKfeVF4lcEUizHuak6G0UxpgGElKCU2m6NH1OnIIVcjGZKqfrikf9rvkada1n1oZ/tbHOUp0hqWVBJbevIMiF3qVzqZWztRLOwNctQCgSys9h0CBK9RZ8wBJs5tfGI89d7rhpCPm2KyhDSo5DnEmHbRoKIZIyPMt4sIbg==
x-forefront-antispam-report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:AM7PR05MB7076.eurprd05.prod.outlook.com;PTR:;CAT:NONE;SFS:(346002)(396003)(366004)(39860400002)(376002)(136003)(52536014)(71200400001)(9686003)(5660300002)(8676002)(83380400001)(6916009)(54906003)(8936002)(4326008)(26005)(76116006)(478600001)(316002)(55016002)(6506007)(64756008)(7696005)(2906002)(33656002)(66476007)(186003)(86362001)(66946007)(66556008)(786003)(66446008);DIR:OUT;SFP:1101;
x-ms-exchange-antispam-messagedata: 
 m1/QI39JQqP7ObKqcU5KH+iZm+EwrDw0zDq+c8Ai69g7aBx75mpMuMsZnKj2wxcRiy4hVY7ERHWW/onnRn//J9LK2lxlp9ATu+gujBgxahuHZRA/LprnHDNP4Za9aHDZnejM0frADbpP5q3CNuonzTltnEy5YI64uxTxodP1vcX37irqoYM3N/4SxppCnbass8Lmt1ZITVyMeImuKDNJ2KMkZqtabDuQ9BcvINMzkS3G0UjL2FAqc8QY+fOF+NpLfugRTccO3lrsU+dLcgUGVRqrd5eiH8Z7nKFB6aUnmhxLV6poBnIBbuZD4DG0A1DkwapsCjJr9rkPkMarRwIMJpEn/TgmWajCYOSfhFfsCGKCNvbNeTt9Jz5JGBxNkj6xMBy0zjjTRjVEEETtGzx3W4UKUYTx+uhQiI+j5r1zDjShSU5GZXJqc1Pfpn5GWZMvKz6H7PYQwTjf339rQq5XmfTN+BPx+vJYXcmzVZMwsBfd8NzK+yiyhs4LsGEGGdmjxslsBNpfvoMJjZ0Mgrmj/SkCCmugT2DSIsfae2s6n/ZH50mUDlz9w61QJx1x6gcDXkObjEu3fWsUNgqWZ8ro+qvFQtwNU9z0CFCsjQpelkQMAkR+0ndDKWapd9ATdj+DyypTfJhCaqtjs8pYNsXYSQ==
x-ms-exchange-transport-forked: True
MIME-Version: 1.0
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-AuthSource: AM7PR05MB7076.eurprd05.prod.outlook.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 d19d1ac3-1ba5-4960-7030-08d86b6d2025
X-MS-Exchange-CrossTenant-originalarrivaltime: 08 Oct 2020 09:32:50.7189
 (UTC)
X-MS-Exchange-CrossTenant-fromentityheader: Hosted
X-MS-Exchange-CrossTenant-id: 2e9f06b0-1669-4589-8789-10a06934dc61
X-MS-Exchange-CrossTenant-mailboxtype: HOSTED
X-MS-Exchange-CrossTenant-userprincipalname: 
 upfMp6Yp7PRtTCBLcPypCMU2J8abLRJr7ghvIByzy/AbialKEZrUVPgxaTGH1Sz97RX8Ee89fVQMLR4sZ+yEsw==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: AM6PR05MB4261
X-OriginatorOrg: ed.ac.uk
X-Edinburgh-Scanned: at loire.is.ed.ac.uk
    with MIMEDefang 2.84, Sophie, Sophos Anti-Virus, Clam AntiVirus
X-Scanned-By: MIMEDefang 2.84 on 129.215.16.10
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch enables vhost-net multi queue support in kvmtool, without any Linux kernel modification.
The patch takes the same approach as QEMU -- for each queue pair a new /dev/vhost-net fd is created.
Fds are kept in ndev->vhost_fds, with ndev->vhost_fd == ndev->vhost_fds[0] (to avoid further modification to the existent source code).
Thanks, Antonio Barbalace

----




The University of Edinburgh is a charitable body, registered in Scotland, with registration number SC005336.

```
#### [PATCH v2] vringh: fix __vringh_iov() when riov and wiov are different
##### From: Stefano Garzarella <sgarzare@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stefano Garzarella <sgarzare@redhat.com>
X-Patchwork-Id: 11824533
Return-Path: <SRS0=lzrU=DP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DDFE81592
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  8 Oct 2020 20:43:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B88F021D46
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  8 Oct 2020 20:43:11 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="XntqAV6R"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729038AbgJHUnH (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 8 Oct 2020 16:43:07 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:46265 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728901AbgJHUnH (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 8 Oct 2020 16:43:07 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1602189785;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=huKURS9xZVwjRl6HwVKXLMhhJbFrna5oxeAZtRaNfLM=;
        b=XntqAV6R1GvrlFkLdDIUC/xMyHYjio6kfZv35RvU8oZm2LQ7ab3J4QTY2VlTAW9a6WKQlr
        +3jYcB0QSYCA3Q18i9LGBI1tltuO2Mhwg89ZrjXTHBfqRs/LsVdHkNLn6/2fAf6EnbAg+r
        SB4hJ6oxNm0YJ+n0igiAt+eQh0fgXHE=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-367-0rDDCUGZOiWINQ_Q48nHTg-1; Thu, 08 Oct 2020 16:43:03 -0400
X-MC-Unique: 0rDDCUGZOiWINQ_Q48nHTg-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 6B147425EB;
        Thu,  8 Oct 2020 20:43:02 +0000 (UTC)
Received: from steredhat.redhat.com (ovpn-112-116.ams2.redhat.com
 [10.36.112.116])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 556BD55786;
        Thu,  8 Oct 2020 20:42:57 +0000 (UTC)
From: Stefano Garzarella <sgarzare@redhat.com>
To: mst@redhat.com
Cc: kvm@vger.kernel.org, netdev@vger.kernel.org,
        virtualization@lists.linux-foundation.org,
        linux-kernel@vger.kernel.org, stable@vger.kernel.org,
        Rusty Russell <rusty@rustcorp.com.au>,
        Jason Wang <jasowang@redhat.com>
Subject: [PATCH v2] vringh: fix __vringh_iov() when riov and wiov are
 different
Date: Thu,  8 Oct 2020 22:42:56 +0200
Message-Id: <20201008204256.162292-1-sgarzare@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If riov and wiov are both defined and they point to different
objects, only riov is initialized. If the wiov is not initialized
by the caller, the function fails returning -EINVAL and printing
"Readable desc 0x... after writable" error message.

This issue happens when descriptors have both readable and writable
buffers (eg. virtio-blk devices has virtio_blk_outhdr in the readable
buffer and status as last byte of writable buffer) and we call
__vringh_iov() to get both type of buffers in two different iovecs.

Let's replace the 'else if' clause with 'if' to initialize both
riov and wiov if they are not NULL.

As checkpatch pointed out, we also avoid crashing the kernel
when riov and wiov are both NULL, replacing BUG() with WARN_ON()
and returning -EINVAL.

Fixes: f87d0fbb5798 ("vringh: host-side implementation of virtio rings.")
Cc: stable@vger.kernel.org
Signed-off-by: Stefano Garzarella <sgarzare@redhat.com>
---
 drivers/vhost/vringh.c | 9 +++++----
 1 file changed, 5 insertions(+), 4 deletions(-)

```
#### [PATCH] vringh: fix __vringh_iov() when riov and wiov are different
##### From: Stefano Garzarella <sgarzare@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stefano Garzarella <sgarzare@redhat.com>
X-Patchwork-Id: 11824165
Return-Path: <SRS0=lzrU=DP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0E029139F
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  8 Oct 2020 16:13:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DF27F221FD
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  8 Oct 2020 16:13:33 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="EpYxopIo"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730750AbgJHQNc (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 8 Oct 2020 12:13:32 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:57205 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1725802AbgJHQN1 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 8 Oct 2020 12:13:27 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1602173606;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=M5rKlvyqoDFzwipoeIl60H9emhyCrrxKsQPGoqtwZ9M=;
        b=EpYxopIoc5XxU0cz9/gdgUYyudi+Esa4CwbXVwU2CEcMzLoRFOtzghSDobmeS1wnmpUZr0
        xNnYACGyye8vfj+CwpRjlkFzKTesZAw7LEBuPYnxpgfICfYpBctmrrjEsWq5+A7Z10tpkF
        JWDisYTMaHLZ0npBO/esTWwOiuFhA7o=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-9-j20hkdD8N7KaClBXpnB_5A-1; Thu, 08 Oct 2020 12:13:22 -0400
X-MC-Unique: j20hkdD8N7KaClBXpnB_5A-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 33A1387952A;
        Thu,  8 Oct 2020 16:13:20 +0000 (UTC)
Received: from steredhat.redhat.com (ovpn-112-116.ams2.redhat.com
 [10.36.112.116])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 2B8855C1BD;
        Thu,  8 Oct 2020 16:13:11 +0000 (UTC)
From: Stefano Garzarella <sgarzare@redhat.com>
To: mst@redhat.com
Cc: netdev@vger.kernel.org, virtualization@lists.linux-foundation.org,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        Rusty Russell <rusty@rustcorp.com.au>, stable@vger.kernel.org,
        Jason Wang <jasowang@redhat.com>
Subject: [PATCH] vringh: fix __vringh_iov() when riov and wiov are different
Date: Thu,  8 Oct 2020 18:13:11 +0200
Message-Id: <20201008161311.114398-1-sgarzare@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If riov and wiov are both defined and they point to different
objects, only riov is initialized. If the wiov is not initialized
by the caller, the function fails returning -EINVAL and printing
"Readable desc 0x... after writable" error message.

Let's replace the 'else if' clause with 'if' to initialize both
riov and wiov if they are not NULL.

As checkpatch pointed out, we also avoid crashing the kernel
when riov and wiov are both NULL, replacing BUG() with WARN_ON()
and returning -EINVAL.

Fixes: f87d0fbb5798 ("vringh: host-side implementation of virtio rings.")
Cc: stable@vger.kernel.org
Signed-off-by: Stefano Garzarella <sgarzare@redhat.com>
---
 drivers/vhost/vringh.c | 9 +++++----
 1 file changed, 5 insertions(+), 4 deletions(-)

```
