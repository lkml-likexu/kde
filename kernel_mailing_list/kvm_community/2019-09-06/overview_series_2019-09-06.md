#### [PATCH v18 1/6] hw/arm/virt: Introduce RAS platform version and RAS machine option
##### From: Xiang Zheng <zhengxiang9@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xiang Zheng <zhengxiang9@huawei.com>
X-Patchwork-Id: 11134759
Return-Path: <SRS0=9Awg=XB=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E44E0924
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Sep 2019 08:33:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id C6D462084F
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Sep 2019 08:33:18 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2387580AbfIFIdR (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 6 Sep 2019 04:33:17 -0400
Received: from szxga07-in.huawei.com ([45.249.212.35]:46198 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1732683AbfIFIdR (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 6 Sep 2019 04:33:17 -0400
Received: from DGGEMS403-HUB.china.huawei.com (unknown [172.30.72.58])
        by Forcepoint Email with ESMTP id B1284F9680A2F91B9579;
        Fri,  6 Sep 2019 16:33:15 +0800 (CST)
Received: from HGHY1z004218071.china.huawei.com (10.177.29.32) by
 DGGEMS403-HUB.china.huawei.com (10.3.19.203) with Microsoft SMTP Server id
 14.3.439.0; Fri, 6 Sep 2019 16:33:08 +0800
From: Xiang Zheng <zhengxiang9@huawei.com>
To: <pbonzini@redhat.com>, <mst@redhat.com>, <imammedo@redhat.com>,
        <shannon.zhaosl@gmail.com>, <peter.maydell@linaro.org>,
        <lersek@redhat.com>, <james.morse@arm.com>,
        <gengdongjiu@huawei.com>, <mtosatti@redhat.com>, <rth@twiddle.net>,
        <ehabkost@redhat.com>, <jonathan.cameron@huawei.com>,
        <xuwei5@huawei.com>, <kvm@vger.kernel.org>,
        <qemu-devel@nongnu.org>, <qemu-arm@nongnu.org>,
        <linuxarm@huawei.com>
CC: <zhengxiang9@huawei.com>, <wanghaibin.wang@huawei.com>
Subject: [PATCH v18 1/6] hw/arm/virt: Introduce RAS platform version and RAS
 machine option
Date: Fri, 6 Sep 2019 16:31:47 +0800
Message-ID: <20190906083152.25716-2-zhengxiang9@huawei.com>
X-Mailer: git-send-email 2.15.1.windows.2
In-Reply-To: <20190906083152.25716-1-zhengxiang9@huawei.com>
References: <20190906083152.25716-1-zhengxiang9@huawei.com>
MIME-Version: 1.0
Content-Type: text/plain
X-Originating-IP: [10.177.29.32]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Dongjiu Geng <gengdongjiu@huawei.com>

Support RAS Virtualization feature since version 4.2, disable it by
default in the old versions. Also add a machine option which allows user
to enable it explicitly.

Signed-off-by: Dongjiu Geng <gengdongjiu@huawei.com>
Signed-off-by: Xiang Zheng <zhengxiang9@huawei.com>
---
 hw/arm/virt.c         | 33 +++++++++++++++++++++++++++++++++
 include/hw/arm/virt.h |  2 ++
 2 files changed, 35 insertions(+)

```
#### [PATCH v8 QEMU 2/3] virtio-balloon: Add bit to notify guest of unused page reporting
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Duyck <alexander.duyck@gmail.com>
X-Patchwork-Id: 11135493
Return-Path: <SRS0=9Awg=XB=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 010311395
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Sep 2019 14:54:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D45F92082C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Sep 2019 14:54:48 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="u2UtpKj+"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2394692AbfIFOyp (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 6 Sep 2019 10:54:45 -0400
Received: from mail-pg1-f196.google.com ([209.85.215.196]:36383 "EHLO
        mail-pg1-f196.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726019AbfIFOyp (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 6 Sep 2019 10:54:45 -0400
Received: by mail-pg1-f196.google.com with SMTP id l21so3647841pgm.3;
        Fri, 06 Sep 2019 07:54:44 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=subject:from:to:cc:date:message-id:in-reply-to:references
         :user-agent:mime-version:content-transfer-encoding;
        bh=VitjQQFQG7H0A5JYqbYhHy/YWDiYO6QESupJyX3H62U=;
        b=u2UtpKj+SdvdC7zNNCRKGfWXo1ykUbLduiISlK7UKVNWKJFj7hQRsxtRsM+Ng+JDcs
         v7XIQ4GRg8UpI0VLI4x3HWqouyCX8JuhCd7BtITu+IvldqmAvamdMQRLR/oEiIkIDVDP
         VFzD84K523Z9VpGyOqGTX8ekpRwerKs9WPfJYRFvR5/Yc/QO9drW8rNetKJQZCnQNepA
         1bO3dX5jPRDMkcPBCJdcwOBp6JxR6PqiCYzLbc8uX5ds6xPdIum29TV7dqmdR/fHlT16
         ao4s/16BbpHnyyT0U1nuALIAl+ZaBH0Apbb5NbsVqY6TVc44rduuB/3bWDd/yhsJtFEB
         pXjQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:subject:from:to:cc:date:message-id:in-reply-to
         :references:user-agent:mime-version:content-transfer-encoding;
        bh=VitjQQFQG7H0A5JYqbYhHy/YWDiYO6QESupJyX3H62U=;
        b=NSJJg4d8h/AlvhdO5Um4RjOM/rUzWn8pBpyYrQgZbQxuo8Fn7NCeSGFaufHzo4A/i3
         LN1rvL30CI20UbyvIcu4lmg4DIB8FXQoAOnY7GlFOphWFI6Bbu9ScEOg2q5qjhlNHHBK
         eKFxNt1HUdqbDVPhXNuuC+Vp+Nx6T8vl1n+LUtIkM4DwQ6ADyS/4yTpM3LcXicr2OVwe
         S5cr1NS7R0Pq7kyPYcTPD5UCWozVk8jd6+GUtAnRjIW9r8Luna660IOur7YbLVX6x8NQ
         qXqNzm4JDd0Vbh3C6UHuvtOzEENQZI5an011ZZA8ycvzCeiSKrDHLpfG+YqTsyoWkphD
         Flmg==
X-Gm-Message-State: APjAAAXUH/wytxB8ov5RFW3gwYCTihL8OGXicWuf0f0aDDJLMQDqGKL7
        E3HNc7qVdd9Dz1q6uQvPgxU=
X-Google-Smtp-Source: 
 APXvYqyq7c3ys8bBHJp63ctlkK7wT7XGiRX8LnzlMCbygnwq1ZTX0Wq3ookzg6WHVMz7aVn1zyE+5Q==
X-Received: by 2002:a65:464d:: with SMTP id k13mr1589674pgr.99.1567781684235;
        Fri, 06 Sep 2019 07:54:44 -0700 (PDT)
Received: from localhost.localdomain ([2001:470:b:9c3:9e5c:8eff:fe4f:f2d0])
        by smtp.gmail.com with ESMTPSA id
 k14sm6784077pfi.98.2019.09.06.07.54.43
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Fri, 06 Sep 2019 07:54:43 -0700 (PDT)
Subject: [PATCH v8 QEMU 2/3] virtio-balloon: Add bit to notify guest of
 unused page reporting
From: Alexander Duyck <alexander.duyck@gmail.com>
To: nitesh@redhat.com, kvm@vger.kernel.org, mst@redhat.com,
        david@redhat.com, dave.hansen@intel.com,
        linux-kernel@vger.kernel.org, linux-mm@kvack.org,
        akpm@linux-foundation.org, virtio-dev@lists.oasis-open.org
Cc: yang.zhang.wz@gmail.com, pagupta@redhat.com, riel@surriel.com,
        konrad.wilk@oracle.com, willy@infradead.org,
        lcapitulino@redhat.com, wei.w.wang@intel.com, aarcange@redhat.com,
        pbonzini@redhat.com, dan.j.williams@intel.com, mhocko@kernel.org,
        alexander.h.duyck@linux.intel.com, osalvador@suse.de
Date: Fri, 06 Sep 2019 07:54:43 -0700
Message-ID: <20190906145443.574.8266.stgit@localhost.localdomain>
In-Reply-To: <20190906145213.32552.30160.stgit@localhost.localdomain>
References: <20190906145213.32552.30160.stgit@localhost.localdomain>
User-Agent: StGit/0.17.1-dirty
MIME-Version: 1.0
Content-Type: text/plain; charset="utf-8"
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Alexander Duyck <alexander.h.duyck@linux.intel.com>

Add a bit for the page reporting feature provided by virtio-balloon.

This patch should be replaced once the feature is added to the Linux kernel
and the bit is backported into this exported kernel header.

Signed-off-by: Alexander Duyck <alexander.h.duyck@linux.intel.com>
---
 include/standard-headers/linux/virtio_balloon.h |    1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH v8 QEMU 3/3] virtio-balloon: Provide a interface for unused page reporting
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Duyck <alexander.duyck@gmail.com>
X-Patchwork-Id: 11135497
Return-Path: <SRS0=9Awg=XB=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7EAF61395
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Sep 2019 14:54:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 57B25214DE
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Sep 2019 14:54:55 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="K7Hb+8Hh"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2405670AbfIFOyv (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 6 Sep 2019 10:54:51 -0400
Received: from mail-pf1-f194.google.com ([209.85.210.194]:45554 "EHLO
        mail-pf1-f194.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2394700AbfIFOyv (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 6 Sep 2019 10:54:51 -0400
Received: by mail-pf1-f194.google.com with SMTP id y72so4626481pfb.12;
        Fri, 06 Sep 2019 07:54:50 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=subject:from:to:cc:date:message-id:in-reply-to:references
         :user-agent:mime-version:content-transfer-encoding;
        bh=R9EIePxtKgh7rutMNGBvqWvR/nyIQIv1yBQVlI6lc80=;
        b=K7Hb+8Hh6OGFNptrd3xhs0dSBGL89ydD/TEtpjhiu9tPxvrsGW3oZrKONgKiu45x/P
         dAbz7znolXERw89jByTZcAJWibJCzG0jedqFEGgpoJoUBO8qpsB7BBgraJiTg8Ry2NjA
         cFWicLV2bexuIOGZulOA00dHHT+tzHPWjOnL3X8puT4y/bCgbfvETE/JpOryD+JF7qb6
         f4DJmu/f0YRPuc0T7TkL7ScmlDt8nGyn0uxI7SXUFtPtXo01hwiAi1PxcFeYZTMEZcxU
         nse6Vg4Q57o1ncXt/v2IDpjPPRvRkrAZoEnIkkaUX6KReSNrAhmG/BdcGcpJCeov5gII
         nPDQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:subject:from:to:cc:date:message-id:in-reply-to
         :references:user-agent:mime-version:content-transfer-encoding;
        bh=R9EIePxtKgh7rutMNGBvqWvR/nyIQIv1yBQVlI6lc80=;
        b=oPlorYZOg+/dMDI2y8KWunxDTdl3FJdc/9qzOZYBDxhR9PHxTT/jvTB6CS6NRnW+cC
         heRVfzBIhAHC12LynP9LYqfAMiNUD9qj34hquQuh5b+YXVeCntT/5SIedvinnOU4hCB0
         Nd00XoV+iyYvavyxXQidZxKt/DzOMW4m5CFNIInwFMDoeG1bsbdlyrkh/VfRw+eFtFXn
         xCTHt+Y3Gs2TsOa0yaxzYCjzUUa8TDYVTQISkFv9hjj/9RVeF3QwEO0+066+Gb58VTKa
         XY/5az66XMrM1+nw+flMmaHhvs3Q11f4sbNINKXbEu1M8BbQRoPRyS7s9Teh4DDcNfhO
         /MLw==
X-Gm-Message-State: APjAAAWrTR/+lLDpW7Vsqt6/pngP1biaCgW0Ygc1uv9QxYnXaAvO0cQe
        2VsR8ZZUlGgUd78Z3b2Q7Cc=
X-Google-Smtp-Source: 
 APXvYqyR/D4tsD7rhNX2PQcMu+Gyd4kcgZa1BS+hYcFptabaRpV4hgMyTPouaYkRi3vtvC8wwpCvOQ==
X-Received: by 2002:a17:90a:c20c:: with SMTP id
 e12mr10459302pjt.14.1567781690374;
        Fri, 06 Sep 2019 07:54:50 -0700 (PDT)
Received: from localhost.localdomain ([2001:470:b:9c3:9e5c:8eff:fe4f:f2d0])
        by smtp.gmail.com with ESMTPSA id
 v7sm3096573pjr.29.2019.09.06.07.54.49
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Fri, 06 Sep 2019 07:54:49 -0700 (PDT)
Subject: [PATCH v8 QEMU 3/3] virtio-balloon: Provide a interface for unused
 page reporting
From: Alexander Duyck <alexander.duyck@gmail.com>
To: nitesh@redhat.com, kvm@vger.kernel.org, mst@redhat.com,
        david@redhat.com, dave.hansen@intel.com,
        linux-kernel@vger.kernel.org, linux-mm@kvack.org,
        akpm@linux-foundation.org, virtio-dev@lists.oasis-open.org
Cc: yang.zhang.wz@gmail.com, pagupta@redhat.com, riel@surriel.com,
        konrad.wilk@oracle.com, willy@infradead.org,
        lcapitulino@redhat.com, wei.w.wang@intel.com, aarcange@redhat.com,
        pbonzini@redhat.com, dan.j.williams@intel.com, mhocko@kernel.org,
        alexander.h.duyck@linux.intel.com, osalvador@suse.de
Date: Fri, 06 Sep 2019 07:54:49 -0700
Message-ID: <20190906145449.574.85741.stgit@localhost.localdomain>
In-Reply-To: <20190906145213.32552.30160.stgit@localhost.localdomain>
References: <20190906145213.32552.30160.stgit@localhost.localdomain>
User-Agent: StGit/0.17.1-dirty
MIME-Version: 1.0
Content-Type: text/plain; charset="utf-8"
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Alexander Duyck <alexander.h.duyck@linux.intel.com>

Add support for what I am referring to as "unused page reporting".
Basically the idea is to function very similar to how the balloon works
in that we basically end up madvising the page as not being used. However
we don't really need to bother with any deflate type logic since the page
will be faulted back into the guest when it is read or written to.

This is meant to be a simplification of the existing balloon interface
to use for providing hints to what memory needs to be freed. I am assuming
this is safe to do as the deflate logic does not actually appear to do very
much other than tracking what subpages have been released and which ones
haven't.

Signed-off-by: Alexander Duyck <alexander.h.duyck@linux.intel.com>
---
 hw/virtio/virtio-balloon.c         |   46 ++++++++++++++++++++++++++++++++++--
 include/hw/virtio/virtio-balloon.h |    2 +-
 2 files changed, 45 insertions(+), 3 deletions(-)

```
#### [kvm-unit-tests RESEND PATCH] x86: Fix id_map buffer overflow and PT corruption
##### From: Evgeny Yakovlev <eyakovlev3@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Evgeny Yakovlev <eyakovlev3@gmail.com>
X-Patchwork-Id: 11134635
Return-Path: <SRS0=9Awg=XB=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D2159112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Sep 2019 07:49:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id AC3AE2081B
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Sep 2019 07:49:29 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="cCzemkjL"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730236AbfIFHt2 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 6 Sep 2019 03:49:28 -0400
Received: from mail-lf1-f66.google.com ([209.85.167.66]:38350 "EHLO
        mail-lf1-f66.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727213AbfIFHt2 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 6 Sep 2019 03:49:28 -0400
Received: by mail-lf1-f66.google.com with SMTP id c12so4212011lfh.5
        for <kvm@vger.kernel.org>; Fri, 06 Sep 2019 00:49:27 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=UvwpR0D53MJISg/ZERTKztEJ07NJptfmY7VJ59LQcZM=;
        b=cCzemkjLXSVSb5MJkMA2lAjuCJh79wlt2+KqFep+qrRTlGL41tJD/f8FCRKwWV2qWA
         /zawOez08ps09gy5cDB1Y2qjEebLaxLl1muZ1wNcKoqXSbti/2hxlRxOsVk0Ny0cJ6Ex
         zAm6aEemfjfDQJRJ+hhrRQMLjYq6ykHGeiUNVslcTUjw77erigHdat1s+7JBvVNbiznz
         90agUTPO38jnfJ2WJ0liQr125rJNk9QABk3jLCen23gLLAc2w6uA2apTVRmfjNWEp1aD
         QqEm9DCskmk1bSX5gOzF38WY+jEVvWULJa/RAFdL0wvF05O/EOCNrya/TuAyykRP/gqv
         mLQg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=UvwpR0D53MJISg/ZERTKztEJ07NJptfmY7VJ59LQcZM=;
        b=tLVbQcA7HgrkrOlT5ADQL1NLFV9jzXzPNZ9UNfZgQWh+QFZS6p7KvDoXvgd9fpqmD1
         gB2YaDhhQTSezn+73nzZOR1Dw1BpYAVyXV2XMeDevqkijf7qYUdodjSw5TbqDSGQj1t1
         lb2Dod4jeRxxPPFxG1ROUQCz5DmE4VamyMa8PuO6eEzPjGnvVBptkmtiHhX19AtrrOab
         WYeJcIXQnrqsXyH1/twBCjtmEsPm4tv4zJ4GPhaP5+XUSg+iiucO5MWEEoXpjbK94ki5
         33OZrc9SlEjVmMl6yQldHhSzR8Ti2MdV8FU2GnlKtxs8hIKvDUfKfbByIfF8m02dcdx+
         lmEA==
X-Gm-Message-State: APjAAAXEfWZ0B24nWvrCuV4i1uvpxhEAmMIfqX043bbjzeeXFCYSPnLI
        25v3bXDae9zhbvgntG50HTWkDZ2U/4I=
X-Google-Smtp-Source: 
 APXvYqxa6avYFbmfFBXmiFTLxIeErK/gT9+8P/j4rSf3RhM7mtTC5AulOvI1QItYttzx3d+gJmuRMQ==
X-Received: by 2002:a19:5215:: with SMTP id m21mr5427767lfb.89.1567756166352;
        Fri, 06 Sep 2019 00:49:26 -0700 (PDT)
Received: from wrfsh-ub14.yandex.net ([2a02:6b8:0:40c:f68c:50ff:fee9:44bd])
        by smtp.gmail.com with ESMTPSA id
 q13sm950702lfk.51.2019.09.06.00.49.25
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-SHA bits=128/128);
        Fri, 06 Sep 2019 00:49:25 -0700 (PDT)
From: Evgeny Yakovlev <eyakovlev3@gmail.com>
X-Google-Original-From: Evgeny Yakovlev <wrfsh@yandex-team.ru>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, rkrcmar@redhat.com, yc-core@yandex-team.ru,
        wrfsh@yandex-team.ru
Subject: [kvm-unit-tests RESEND PATCH] x86: Fix id_map buffer overflow and PT
 corruption
Date: Fri,  6 Sep 2019 10:49:19 +0300
Message-Id: <1567756159-512600-1-git-send-email-wrfsh@yandex-team.ru>
X-Mailer: git-send-email 2.7.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Commit 18a34cce introduced init_apic_map. It iterates over
sizeof(online_cpus) * 8 items and sets APIC ids in id_map.
However, online_cpus is defined (in x86/cstart[64].S) as a 64-bit
variable. After i >= 64, init_apic_map begins to read out of bounds of
online_cpus. If it finds a non-zero value there enough times,
it then proceeds to potentially overflow id_map in assignment.

In our test case id_map was linked close to pg_base. As a result page
table was corrupted and we've seen sporadic failures of ioapic test.

Signed-off-by: Evgeny Yakovlev <wrfsh@yandex-team.ru>
---
 lib/x86/apic.c | 9 ++++++---
 1 file changed, 6 insertions(+), 3 deletions(-)

```
#### [PATCH v4 1/9] KVM: nVMX: Use kvm_set_msr to load IA32_PERF_GLOBAL_CTRL
##### From: Oliver Upton <oupton@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Oliver Upton <oupton@google.com>
X-Patchwork-Id: 11136059
Return-Path: <SRS0=9Awg=XB=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AB1D41599
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Sep 2019 21:03:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 8DD122178F
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Sep 2019 21:03:25 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="eQfLtdvR"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2389254AbfIFVDY (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 6 Sep 2019 17:03:24 -0400
Received: from mail-pf1-f201.google.com ([209.85.210.201]:55779 "EHLO
        mail-pf1-f201.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725872AbfIFVDY (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 6 Sep 2019 17:03:24 -0400
Received: by mail-pf1-f201.google.com with SMTP id w126so4233465pfd.22
        for <kvm@vger.kernel.org>; Fri, 06 Sep 2019 14:03:24 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=CNdrlb0ULLVdEI+amDkztM5kVgEihq12ic/7nJruJWA=;
        b=eQfLtdvRyr1zcRwiuY/gGorUEG/JtUGoXsYHtT760bxrpeVvhvwIZpAiedupv8u9eg
         Rpt+Du45VehsyyTfohyp4Mi+qgArouJaudAkf7maOixuKTwqfW8EJZoRWSY958De95sI
         wzCyzmtG5S6F7IDZRnViUQojSMhvN7J0KkZrHxPKb6fshTEbkhVwrsZeTbhIjiNi1wYB
         amHtYP3/Len52v57QMfYA+msg8c157rIVhlYcpFDlXyCwhXRqni+3gux0rcSFJkx8Nq9
         wFWBLgtlORbvAIIFaXde/xgflOUREqGP7ddW5wFL9wfZy2XpxABtNmoglZaWthi59BSi
         cLSA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=CNdrlb0ULLVdEI+amDkztM5kVgEihq12ic/7nJruJWA=;
        b=HS6WsDn1IlVnz5JWMoWUjXnBXFIvo2+maDswhQSK8fWmzUVsqhKlSfE+vuWWd70Vli
         GNqaEe6wvkrGjoG8lgFEhaBPcraXwue5fHGlVxVz9gMa6e5qM2XmZKLBjJRbDMrYcZt/
         xH5pJFVMOr5KkmHM7/dGZ1OKLqZhBNv8vGwkz+HuteZBO3mhGsxXjcSbDmUa3E2/UsaV
         6HGRlDsPWFnqEv9/xp7NNRZOL1q6xRQf/Gp+KIrSfutR2jUzz6lxk9gBj8AYutEV5T+r
         /r5rjVECuVRBPiKyB8y+h//LvbZjWcK1X2XrchVkHoauV98t06qA2/4osKNL3kXBIVdK
         CJKg==
X-Gm-Message-State: APjAAAW04Q3K8KEyYzAV1Xae/uNjS9JVCpyObn6HSpTvPuzbLuhw9vfg
        NDgNxD+oSRb82uKOT/YtP3kDWczHerMzq7Pl6kKoOsgv73aBGVycmprUst5lenx9cgFXu0Ljn/X
        mpGOvr+KmjWwyAAggVgEv/q9wW2CCuc8Dm5MKoZCxUxAfFGT8e8V8he8FIA==
X-Google-Smtp-Source: 
 APXvYqxal6kWb12vc5ZYGfvikIizmgLlOf/F6n8mtymbjl8QQRHHARbD3za9szERunWq135iI4LNGp0Ygrc=
X-Received: by 2002:a63:b919:: with SMTP id z25mr9563029pge.201.1567803803148;
 Fri, 06 Sep 2019 14:03:23 -0700 (PDT)
Date: Fri,  6 Sep 2019 14:03:05 -0700
In-Reply-To: <20190906210313.128316-1-oupton@google.com>
Message-Id: <20190906210313.128316-2-oupton@google.com>
Mime-Version: 1.0
References: <20190906210313.128316-1-oupton@google.com>
X-Mailer: git-send-email 2.23.0.187.g17f5b7556c-goog
Subject: [PATCH v4 1/9] KVM: nVMX: Use kvm_set_msr to load
 IA32_PERF_GLOBAL_CTRL
 on vmexit
From: Oliver Upton <oupton@google.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>, "
	=?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= " <rkrcmar@redhat.com>
Cc: Jim Mattson <jmattson@google.com>, Peter Shier <pshier@google.com>,
        Krish Sadhukhan <krish.sadhukhan@oracle.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Oliver Upton <oupton@google.com>
Content-Type: text/plain; charset="UTF-8"
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The existing implementation for loading the IA32_PERF_GLOBAL_CTRL MSR
on VM-exit was incorrect, as the next call to atomic_switch_perf_msrs()
could cause this value to be overwritten. Instead, call kvm_set_msr()
which will allow atomic_switch_perf_msrs() to correctly set the values.

Suggested-by: Jim Mattson <jmattson@google.com>
Co-developed-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Signed-off-by: Oliver Upton <oupton@google.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
---
 arch/x86/kvm/vmx/nested.c | 13 ++++++++++---
 1 file changed, 10 insertions(+), 3 deletions(-)

```
#### [PATCH v4 1/4] KVM: X86: Trace vcpu_id for vmexit
##### From: Peter Xu <peterx@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11134255
Return-Path: <SRS0=9Awg=XB=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B2EF71398
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Sep 2019 02:17:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B0A7120870
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Sep 2019 02:17:58 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2404340AbfIFCRi (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 5 Sep 2019 22:17:38 -0400
Received: from mx1.redhat.com ([209.132.183.28]:50996 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728507AbfIFCRg (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 5 Sep 2019 22:17:36 -0400
Received: from mail-pf1-f199.google.com (mail-pf1-f199.google.com
 [209.85.210.199])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-GCM-SHA256 (128/128 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id C63F0806A2
        for <kvm@vger.kernel.org>; Fri,  6 Sep 2019 02:17:36 +0000 (UTC)
Received: by mail-pf1-f199.google.com with SMTP id w126so2080960pfd.22
        for <kvm@vger.kernel.org>; Thu, 05 Sep 2019 19:17:36 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=PI0dvyELfgDR6EZuTiL1mpi7X9aW26KSG8PfN04SbrI=;
        b=oN0NHEgxCElw0qORey0AzjgBHphZBkwdVms0p0rKcOHc8FcUwHToFdNK9joGSEY3cd
         bhG3Q764w1fjpyaz/XSGKOqlB8aQhCBlJNP1Nyh/7aRZ3cXtuncU9Z5d9b2WBtRnnMRL
         A9VWRhaZrtf2UOXXd2xpXDcrg0A+GAyqN/ljSObzI7wkyxvD90h3PLoFaUCftwPWZyXH
         CDKSiEvtUirpnGjLg/J7aExwUngjJv5eejYfaOAmrA1ccelu5UXgsujgYamfPAMXBoJP
         ZPTM54X4VbGEiOpOxrgylm9GGQJUM+se4fSvWstow1oosDIuSCpeQAgCxOOEcueqRCnt
         xIIA==
X-Gm-Message-State: APjAAAVwm2fWgjD72/no5vpLnLSpaFbSg5YACJo3HdEySWGucrHPdPYB
        3Pj5yLhB34PQkxWTSwh6T3U35q5VLCjf1zNr2WK4Z2ExxoJpeI5cOXgZA1A/R72tltW9LL4VZjK
        O6pm3mmDc8pEX
X-Received: by 2002:a17:902:a507:: with SMTP id
 s7mr6835202plq.66.1567736256237;
        Thu, 05 Sep 2019 19:17:36 -0700 (PDT)
X-Google-Smtp-Source: 
 APXvYqyHNmYW/Tb/4gB158GISbxVxqvjGZfcetpu67IukX/XY4cAL70pd1u6vIEnBjmgKmkvmFrjng==
X-Received: by 2002:a17:902:a507:: with SMTP id
 s7mr6835191plq.66.1567736256066;
        Thu, 05 Sep 2019 19:17:36 -0700 (PDT)
Received: from xz-x1.redhat.com ([209.132.188.80])
        by smtp.gmail.com with ESMTPSA id
 a11sm8212359pfg.94.2019.09.05.19.17.33
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 05 Sep 2019 19:17:35 -0700 (PDT)
From: Peter Xu <peterx@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Wanpeng Li <kernellwp@gmail.com>,
        Krish Sadhukhan <krish.sadhukhan@oracle.com>, peterx@redhat.com
Subject: [PATCH v4 1/4] KVM: X86: Trace vcpu_id for vmexit
Date: Fri,  6 Sep 2019 10:17:19 +0800
Message-Id: <20190906021722.2095-2-peterx@redhat.com>
X-Mailer: git-send-email 2.21.0
In-Reply-To: <20190906021722.2095-1-peterx@redhat.com>
References: <20190906021722.2095-1-peterx@redhat.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Tracing the ID helps to pair vmenters and vmexits for guests with
multiple vCPUs.

Reviewed-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Peter Xu <peterx@redhat.com>
---
 arch/x86/kvm/trace.h | 5 ++++-
 1 file changed, 4 insertions(+), 1 deletion(-)

```
#### [PATCH v8 1/7] mm: Add per-cpu logic to page shufflingFrom: Alexander Duyck <alexander.duyck@gmail.com>
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Duyck <alexander.duyck@gmail.com>
X-Patchwork-Id: 11135461
Return-Path: <SRS0=9Awg=XB=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7DD63112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Sep 2019 14:53:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5EB9B206A5
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Sep 2019 14:53:33 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="Mag0NQ/B"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2394675AbfIFOxa (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 6 Sep 2019 10:53:30 -0400
Received: from mail-pl1-f195.google.com ([209.85.214.195]:40857 "EHLO
        mail-pl1-f195.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2394669AbfIFOx3 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 6 Sep 2019 10:53:29 -0400
Received: by mail-pl1-f195.google.com with SMTP id y10so3255778pll.7;
        Fri, 06 Sep 2019 07:53:29 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=subject:from:to:cc:date:message-id:in-reply-to:references
         :user-agent:mime-version:content-transfer-encoding;
        bh=y1UWMqHdCnekLv2dWzC/1NNH0fQiwzlC8Wszz/ILY4M=;
        b=Mag0NQ/BaY/evlZK7rDqVpVa4SoD20yegY2gnU1J5QJ3cQlPeV/WcjiNsMRjYj4UlO
         j47A4eB1Yyu6XTdDMn6pahVscdhXahzaiE5xjJhESZqtYaG0lzLUqBsiW6/Fy9NG09xg
         C0aLIvy/oDX59quZyauouhcpPyWzxdO81zIGT2WvnflPokAj/pLHMhQ3mj+xzsqp14Ls
         7ab/Q7uvHBNht0vduEP9dnyrW2UuVdwFLJ4a6jdGsKR41YoqTUo9nnlYCGO6X4dQ9RcX
         uROSr2vodVMG9kRIlO3cfEccObq9fvrETCZcgM7na40pGHl+LKkghJ1Aria9vjVlnarm
         gZnw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:subject:from:to:cc:date:message-id:in-reply-to
         :references:user-agent:mime-version:content-transfer-encoding;
        bh=y1UWMqHdCnekLv2dWzC/1NNH0fQiwzlC8Wszz/ILY4M=;
        b=D+QuEgMur72/ZwM1Z/RDG1Fqr+haTXeSz+4w83cyAkq31F9tg1zQkTFqLFDQwfxU0j
         pHNcOxaQwMMAC36k2+td+Ut+bCV0Xi9ybUaADbQ9s0LipMBG42du8TSy1QWnGbCLSAx/
         lbxSpQyLRVHc7paX/8Hs0cSVua6Y+FoquQ9HPx+CDYMd23f+y2fHbo8wi3gnS187YAG2
         6mbOE9s4r/T0XLCNYw90KAhthzT53FTYmiqWBaz6IxDZeFcde9yoN02d1yYfpCDEuCba
         qIQ1hs0H8t0WcdtT2w41Ui2iE11pyALweJLj79HG2fgK9xtDdoz4OWFZhOQ6ZCvajqi9
         UTGg==
X-Gm-Message-State: APjAAAUe1RHFRLCm/VzIlaOILYS0K0APQXxCbdAOBSCLhhvpzAYpUgNu
        DfUEPAppWr1vb5ci/4kN/u8=
X-Google-Smtp-Source: 
 APXvYqwXbA80G+oF/wmxkLk0iz+eT1kKPHeORFg6MaYksK5+TYFebrUDE34FVzIfkIJ4DDYs9NYZbQ==
X-Received: by 2002:a17:902:a01:: with SMTP id
 1mr9873072plo.278.1567781608953;
        Fri, 06 Sep 2019 07:53:28 -0700 (PDT)
Received: from localhost.localdomain ([2001:470:b:9c3:9e5c:8eff:fe4f:f2d0])
        by smtp.gmail.com with ESMTPSA id
 c1sm11390068pfb.135.2019.09.06.07.53.28
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Fri, 06 Sep 2019 07:53:28 -0700 (PDT)
Subject: [PATCH v8 1/7] mm: Add per-cpu logic to page shuffling
From: Alexander Duyck <alexander.duyck@gmail.com>
To: nitesh@redhat.com, kvm@vger.kernel.org, mst@redhat.com,
        david@redhat.com, dave.hansen@intel.com,
        linux-kernel@vger.kernel.org, willy@infradead.org,
        mhocko@kernel.org, linux-mm@kvack.org, akpm@linux-foundation.org,
        virtio-dev@lists.oasis-open.org, osalvador@suse.de
Cc: yang.zhang.wz@gmail.com, pagupta@redhat.com, riel@surriel.com,
        konrad.wilk@oracle.com, lcapitulino@redhat.com,
        wei.w.wang@intel.com, aarcange@redhat.com, pbonzini@redhat.com,
        dan.j.williams@intel.com, alexander.h.duyck@linux.intel.com
Date: Fri, 06 Sep 2019 07:53:27 -0700
Message-ID: <20190906145327.32552.39455.stgit@localhost.localdomain>
In-Reply-To: <20190906145213.32552.30160.stgit@localhost.localdomain>
References: <20190906145213.32552.30160.stgit@localhost.localdomain>
User-Agent: StGit/0.17.1-dirty
MIME-Version: 1.0
Content-Type: text/plain; charset="utf-8"
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Alexander Duyck <alexander.h.duyck@linux.intel.com>

Change the logic used to generate randomness in the suffle path so that we
can avoid cache line bouncing. The previous logic was sharing the offset
and entropy word between all CPUs. As such this can result in cache line
bouncing and will ultimately hurt performance when enabled.

To resolve this I have moved to a per-cpu logic for maintaining a unsigned
long containing some amount of bits, and an offset value for which bit we
can use for entropy with each call.

Signed-off-by: Alexander Duyck <alexander.h.duyck@linux.intel.com>
Reviewed-by: Dan Williams <dan.j.williams@intel.com>
---
 mm/shuffle.c |   33 +++++++++++++++++++++++----------
 1 file changed, 23 insertions(+), 10 deletions(-)

```
#### [PULL] vhost, virtio: last minute fixes
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 11135291
Return-Path: <SRS0=9Awg=XB=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 07C7814ED
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Sep 2019 13:41:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E520B20650
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Sep 2019 13:41:09 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2391948AbfIFNlI (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 6 Sep 2019 09:41:08 -0400
Received: from mx1.redhat.com ([209.132.183.28]:53390 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2387994AbfIFNlI (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 6 Sep 2019 09:41:08 -0400
Received: from mail-wm1-f71.google.com (mail-wm1-f71.google.com
 [209.85.128.71])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-GCM-SHA256 (128/128 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 27DCC7CB80
        for <kvm@vger.kernel.org>; Fri,  6 Sep 2019 13:41:08 +0000 (UTC)
Received: by mail-wm1-f71.google.com with SMTP id v4so1002395wmh.9
        for <kvm@vger.kernel.org>; Fri, 06 Sep 2019 06:41:08 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:mime-version
         :content-disposition;
        bh=BOudiuHTDG2nanChju52HFlrYGD+TT2yIrow4eQVhPo=;
        b=VTkfLOw/wRyoKElziJgtxGh1qqKur0FaQMDN6utQwoqA+4qwCn0TTNbSUFBV2N+zNn
         fY9a/gGfXD9M6Cj4XjdCGgbl6+64gyc7F4qoRqnTNbJ5jsvxlVqUZ1GOdRnbAE9wQ1oA
         WsABLwQfIHFEOBPNZEe+s6UxG1pfwU59Zq7c6kpo7CeZmj2+vC5zkBySFRRxMkEyKPnb
         eQ9GQIosJoMVlxVDwN2lvVQzzEqGY1SYRrpgLeAAj2RfuZAIpr41pvsHNGKC1KNA1IiL
         inFuK22SIOZDnx+UioFfBRcsbhrw8UMQkPNicBEESNFJ0cRmI8xosKB1fUDjkcTTEZzY
         AeOg==
X-Gm-Message-State: APjAAAWIIXDQy/tZKMsjOw9b6QSW3F8GC3Wakv2UT7Dg2O3OU67NEHen
        kKysuqmExFg6kZ2a0DjoEiTqKo504ijNd7PIY9Ie7/CF5vqWc54sSIxqAO6INjAa8eVGTRWHQ6e
        hAxko9L5iALUN
X-Received: by 2002:a5d:68c9:: with SMTP id p9mr7195685wrw.95.1567777266881;
        Fri, 06 Sep 2019 06:41:06 -0700 (PDT)
X-Google-Smtp-Source: 
 APXvYqxreY3DmoX89vqmIPvQ3JR7SKig36Ux54jbeXQCW2FgTU0YSZ0FueKQ+54ktkhW991OFZYpRA==
X-Received: by 2002:a5d:68c9:: with SMTP id p9mr7195662wrw.95.1567777266677;
        Fri, 06 Sep 2019 06:41:06 -0700 (PDT)
Received: from redhat.com (bzq-79-176-40-226.red.bezeqint.net.
 [79.176.40.226])
        by smtp.gmail.com with ESMTPSA id
 r17sm6169766wrt.68.2019.09.06.06.41.04
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 06 Sep 2019 06:41:05 -0700 (PDT)
Date: Fri, 6 Sep 2019 09:41:03 -0400
From: "Michael S. Tsirkin" <mst@redhat.com>
To: Linus Torvalds <torvalds@linux-foundation.org>
Cc: kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org, linux-kernel@vger.kernel.org,
        jasowang@redhat.com, jiangkidd@hotmail.com, linyunsheng@huawei.com,
        mst@redhat.com, namit@vmware.com, tiwei.bie@intel.com
Subject: [PULL] vhost, virtio: last minute fixes
Message-ID: <20190906094103-mutt-send-email-mst@kernel.org>
MIME-Version: 1.0
Content-Type: text/plain; charset=us-ascii
Content-Disposition: inline
X-Mutt-Fcc: =sent
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hope this can still make it.
I was not sure about virtio-net change but it seems that it prevents
livelocks for some people.

The following changes since commit 089cf7f6ecb266b6a4164919a2e69bd2f938374a:

  Linux 5.3-rc7 (2019-09-02 09:57:40 -0700)

are available in the Git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/mst/vhost.git tags/for_linus

for you to fetch changes up to 02fa5d7b17a761f53ef1eedfc254e1f33bd226b0:

  mm/balloon_compaction: suppress allocation warnings (2019-09-04 07:42:01 -0400)

----------------------------------------------------------------
virtio, vhost, balloon: bugfixes

A couple of last minute bugfixes. And a revert of a failed attempt at
metadata access optimization - we'll try again in the next cycle.

Signed-off-by: Michael S. Tsirkin <mst@redhat.com>

----------------------------------------------------------------
? jiang (1):
      virtio-net: lower min ring num_free for efficiency

Michael S. Tsirkin (1):
      Revert "vhost: access vq metadata through kernel virtual address"

Nadav Amit (1):
      mm/balloon_compaction: suppress allocation warnings

Tiwei Bie (2):
      vhost/test: fix build for vhost test
      vhost/test: fix build for vhost test

Yunsheng Lin (1):
      vhost: Remove unnecessary variable

 drivers/net/virtio_net.c |   2 +-
 drivers/vhost/test.c     |  13 +-
 drivers/vhost/vhost.c    | 520 +----------------------------------------------
 drivers/vhost/vhost.h    |  41 ----
 mm/balloon_compaction.c  |   3 +-
 5 files changed, 17 insertions(+), 562 deletions(-)
```
#### [PATCH RESEND v3 1/5] KVM: LAPIC: Tune lapic_timer_advance_ns smoothly
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11134177
Return-Path: <SRS0=9Awg=XB=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F3AEA1398
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Sep 2019 01:30:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id BCE9D2082C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Sep 2019 01:30:41 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="XklUKNyK"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2391901AbfIFBaQ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 5 Sep 2019 21:30:16 -0400
Received: from mail-pg1-f194.google.com ([209.85.215.194]:46396 "EHLO
        mail-pg1-f194.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1732899AbfIFBaQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 5 Sep 2019 21:30:16 -0400
Received: by mail-pg1-f194.google.com with SMTP id m3so2469674pgv.13;
        Thu, 05 Sep 2019 18:30:15 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=7A2filp88gYNW30KqtsTddaPW1vJgWmE/N1oJgsUja0=;
        b=XklUKNyKTyc8Hs/8yMz9srJeGYceQ07QmpMhvNcGHY0j4mDq7EZxkMStITo3oi2SSL
         TEE1SoOfl8PMBs2woEl3CWqFQjanlC25C4Lpvl0M5X5f45VcFoCyoenBiKcRZ0WsdGWj
         Mxi9Ycgn4YInJoKs6WWbqU3uahUSK2fzZ7JPuwuHtLhALEqujI/GcfNlg+dLByduWDJC
         9u8EmoB1gmmfutKEDWhph/H2xjA1VKKjaKtAss/qGopsF8ahpeiNB6nlzlCBidRaj3gg
         mKJlz/3t59Lh0tNrV6Y+ncQK8hZmtXqzQ2VrppvCRM/gZhxMaSgbym1jnKmS1QscDfQs
         TPQw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=7A2filp88gYNW30KqtsTddaPW1vJgWmE/N1oJgsUja0=;
        b=Es6MjbV/6v6+Nxr7uBcXzKAVjqGj0aDV046pg49m/lVDRry4WJZLn9TR62mX2qglfF
         wCfDHjAVbogJEcnSDkPw2KGdMBzIWl4cVopuZ8xkOtxmYVqB6H2W1qUpLA24InP2LLK/
         I1IYOc9UU7AO6fuFzZNS0lkUKA+29PYLOabls3gjj4+6B0K33oJvaH0/Wnq8hndRwE0H
         ek0QTm4oMRANLKtoM1JO+SvIFNzlO4k5lh/pEnS1FjruU3WU7+lIw/66P5V507Qgmpnc
         Sro9uFFUAgVrp9tDKknjsEIWbFR8QkerFkwA+KfhtwWCOIsqwUKvMpT8mUY9PTp3nChk
         pDKA==
X-Gm-Message-State: APjAAAWp5UdGCnNl9oqAtYx+ulom1tQhkKX4mCle7tfS4uyRAmmWrn3m
        /mNltoW49PauVFyCIkZNwzbgLlUi
X-Google-Smtp-Source: 
 APXvYqxFnG3Y8aMXP4FrpIDRhqZF/OXp0uMbOHjN2dV0BlzC+z2Y978K+5JoexAfJO0pNIphklpvPA==
X-Received: by 2002:a17:90a:983:: with SMTP id 3mr7227355pjo.57.1567733415131;
        Thu, 05 Sep 2019 18:30:15 -0700 (PDT)
Received: from localhost.localdomain ([203.205.141.123])
        by smtp.googlemail.com with ESMTPSA id
 g11sm3332294pgu.11.2019.09.05.18.30.12
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-SHA bits=128/128);
        Thu, 05 Sep 2019 18:30:14 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Sean Christopherson <sean.j.christopherson@intel.com>,
 Vitaly Kuznetsov <vkuznets@redhat.com>, Wanpeng Li <wanpengli@tencent.com>,
 Jim Mattson <jmattson@google.com>, Joerg Roedel <joro@8bytes.org>
Subject: [PATCH RESEND v3 1/5] KVM: LAPIC: Tune lapic_timer_advance_ns
 smoothly
Date: Fri,  6 Sep 2019 09:30:00 +0800
Message-Id: <1567733404-7759-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

Using a moving average based on per-vCPU lapic_timer_advance_ns to tune
smoothly, filter out drastic fluctuation which prevents this before,
let's assume it is 10000 cycles.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kvm/lapic.c | 18 ++++++++++++------
 1 file changed, 12 insertions(+), 6 deletions(-)

```
#### [RFC][PATCH] KVM: nVMX: Don't leak L1 MMIO regions to L2From: Jim Mattson <jmattson@google.com>
##### From: Jim Mattson <jmattson@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jim Mattson <jmattson@google.com>
X-Patchwork-Id: 11135845
Return-Path: <SRS0=9Awg=XB=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 872471599
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Sep 2019 18:59:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5F3BB208C3
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Sep 2019 18:59:58 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="maT/bg7g"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2405146AbfIFS75 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 6 Sep 2019 14:59:57 -0400
Received: from mail-pg1-f201.google.com ([209.85.215.201]:45347 "EHLO
        mail-pg1-f201.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729790AbfIFS75 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 6 Sep 2019 14:59:57 -0400
Received: by mail-pg1-f201.google.com with SMTP id i12so3870592pgm.12
        for <kvm@vger.kernel.org>; Fri, 06 Sep 2019 11:59:56 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=2LI5oCHBJ4+di3wYUteHFQEnU1+M8HQU/92dv+apGkM=;
        b=maT/bg7g4TtNqrIFSwhu2ZQaiiqnJMd2JWbEIbi0SMD9CSwBmMCs3tcV65BXanY+Ov
         3ExsV0RcQ8fMQXjazOavotXqTZcHnYrSC56TXwdwLk8GdM78fDYPFY+j+rW8+HrMGsNR
         /4/oYTx6cEAUgx29NpQwNo6+/DD7vqqUG8dm5jk/WtCE1UmPF7M2nx40OUXGXU/AHOFr
         qw64rRPXwBhUeoV2Zx/K5O2O8uM9Y/UYLgt7blFjHlzyUciPK5bZwHGkAqA1ukA4njcU
         wZZAOHkcM13T3brSjdQ0AV/PZvdPUh8gJHjOWcgguUsRhH+VvLqQxwT6GT3wFuNPQbnf
         OK7w==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=2LI5oCHBJ4+di3wYUteHFQEnU1+M8HQU/92dv+apGkM=;
        b=YAixGlyY0c5HCNQNkpRi23+k4on+PHBOe0M0+osC3DIKmiQZWidUyA51znfXID07nS
         XyJ1eko6xZoWE1l9SmM9fvRZIGfCom0Bag3F+fwKKdnv11evxWVeiTyfBto9OXnLs/1S
         SRdoz/9c4yuQPTc0mkkN/R3H9k5kwWiV2mxo2nbEtwgwgbugCTRMOv/VKE70/5oD+CeS
         4xnbtQpFD0nUP00fC74vIGSLH+v7Zm2fWDF8bEODWXhsOvfRlbhxxceyPeu8BC9U4OPY
         8vWuG4vSWnDLeQtAcdksWqBeiJSoASAbQoSE2NDaWczvrIak7HjahNlkOgms2YKH59UQ
         TKFA==
X-Gm-Message-State: APjAAAVtfDg4VbnpDcBezvDVJc8xr3+v5sfDCN9bg35jSCmU5l8p4nhU
        hudoa/p/GfvKqf/dUaGbcTL3d/+X1IYc41OcgsrVJsnfrZKRoIfxcjzdAkSaPv9JrdUAD+ZGBpW
        TTeYw6sFiQD3JQF6lc8NUa064Okz/uRabCRDhLP9jUHhFTZiZVGbcvX/zbjMQbJU=
X-Google-Smtp-Source: 
 APXvYqwGDO//F5Xovg1g38E2cBFbvHQ2Nqx67Ny5J1pbtFk5T5yuMqNwEQ0nzwj2CKMH1+Xfc9fK2Cs0RFXnag==
X-Received: by 2002:a63:1f1f:: with SMTP id f31mr9112786pgf.353.1567796395708;
 Fri, 06 Sep 2019 11:59:55 -0700 (PDT)
Date: Fri,  6 Sep 2019 11:59:45 -0700
Message-Id: <20190906185945.230946-1-jmattson@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.23.0.187.g17f5b7556c-goog
Subject: [RFC][PATCH] KVM: nVMX: Don't leak L1 MMIO regions to L2
From: Jim Mattson <jmattson@google.com>
To: kvm@vger.kernel.org
Cc: Jim Mattson <jmattson@google.com>, Dan Cross <dcross@google.com>,
        Marc Orr <marcorr@google.com>, Peter Shier <pshier@google.com>
Content-Type: text/plain; charset="UTF-8"
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If the "virtualize APIC accesses" VM-execution control is set in the
VMCS, the APIC virtualization hardware is triggered when a page walk
in VMX non-root mode terminates at a PTE wherein the address of the 4k
page frame matches the APIC-access address specified in the VMCS. On
hardware, the APIC-access address may be any valid 4k-aligned physical
address.

KVM's nVMX implementation enforces the additional constraint that the
APIC-access address specified in the vmcs12 must be backed by
cacheable memory in L1. If not, L0 will simply clear the "virtualize
APIC accesses" VM-execution control in the vmcs02.

The problem with this approach is that the L1 guest has arranged the
vmcs12 EPT tables--or shadow page tables, if the "enable EPT"
VM-execution control is clear in the vmcs12--so that the L2 guest
physical address(es)--or L2 guest linear address(es)--that reference
the L2 APIC map to the APIC-access address specified in the
vmcs12. Without the "virtualize APIC accesses" VM-execution control in
the vmcs02, the APIC accesses in the L2 guest will directly access the
APIC-access page in L1.

When L0 has no mapping whatsoever for the APIC-access address in L1,
the L2 VM just loses the intended APIC virtualization. However, when
the L2 APIC-access address is mapped to an MMIO region in L1, the L2
guest gets direct access to the L1 MMIO device. For example, if the
APIC-access address specified in the vmcs12 is 0xfee00000, then L2
gets direct access to L1's APIC.

Fixing this correctly is complicated. Since this vmcs12 configuration
is something that KVM cannot faithfully emulate, the appropriate
response is to exit to userspace with
KVM_INTERNAL_ERROR_EMULATION. Sadly, the kvm-unit-tests fail, so I'm
posting this as an RFC.

Note that the 'Code' line emitted by qemu in response to this error
shows the guest %rip two instructions after the
vmlaunch/vmresume. Hmmm.

Fixes: fe3ef05c7572 ("KVM: nVMX: Prepare vmcs02 from vmcs01 and vmcs12")
Reported-by: Dan Cross <dcross@google.com>
Signed-off-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Marc Orr <marcorr@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
Reviewed-by: Dan Cross <dcross@google.com>
---
 arch/x86/include/asm/kvm_host.h |  2 +-
 arch/x86/kvm/vmx/nested.c       | 55 ++++++++++++++++++++++-----------
 arch/x86/kvm/x86.c              |  9 ++++--
 3 files changed, 45 insertions(+), 21 deletions(-)

```
#### [PATCH v8 QEMU 1/3] virtio-ballon: Implement support for page poison tracking feature
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Duyck <alexander.duyck@gmail.com>
X-Patchwork-Id: 11135489
Return-Path: <SRS0=9Awg=XB=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 521A9112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Sep 2019 14:54:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 29799214DE
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Sep 2019 14:54:43 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="DPoTj8DV"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2391291AbfIFOyj (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 6 Sep 2019 10:54:39 -0400
Received: from mail-pl1-f194.google.com ([209.85.214.194]:36658 "EHLO
        mail-pl1-f194.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1732466AbfIFOyj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 6 Sep 2019 10:54:39 -0400
Received: by mail-pl1-f194.google.com with SMTP id f19so3265494plr.3;
        Fri, 06 Sep 2019 07:54:38 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=subject:from:to:cc:date:message-id:in-reply-to:references
         :user-agent:mime-version:content-transfer-encoding;
        bh=a/jqoVnZMS4gCQHlsNMs0Wm0i9/bhDBfzuCMndLKGiI=;
        b=DPoTj8DVCabydhuxDk7kerFrocuL1iWaVKaQ0C9IbaGj6H8ji6PXGo4riQpuaPtVio
         uwbIHn0UPhlDK06YsXdAVAVDbPx34Q/J66NssePdsIVjtqxH85+dnZRD/KCtQ3njFYXF
         oKaZ8AAxmORq6XDNq6qYd2ZqhKDp8kMX0I7sY4/j3vIHutWRx6rwji0iS0+Cx3yVhn1x
         bDxwrpbaC4jAmR9xPEXH9GGU167HEcYqrCM8A9Yq7FljOgraaFB3A64ZSRPMAxsoTdZz
         PB/jOIG5ANrPeGuZCX70J2SyIj21SFb4NdDFXLAbJ0GZ7k1ziLFGnlCBj6vnf0m4qBE6
         ekpw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:subject:from:to:cc:date:message-id:in-reply-to
         :references:user-agent:mime-version:content-transfer-encoding;
        bh=a/jqoVnZMS4gCQHlsNMs0Wm0i9/bhDBfzuCMndLKGiI=;
        b=XrgXIq1lOrsXbsBVFfYEQX78kEZICKvVbOZpF+6xb/2sMc1bRX5Lve/dX4Tv7vkKOh
         2ATvMw77WymMTEeOpjw/bxyX/ULWJaLHx4FCqw+WQ9qy0ga+qtpgqb8epr4iM2HUvpvF
         Tfv1xLZETpFN6XZDs0aiDMMUDdfEccwXk84YCgCxZ+aOITkBiB4fbyvRo4jvBC6bJ2pd
         VpC8ecKYEAZY9Wu1yaj9Ss198LlyzPuRE0Q02ewcs07KflmCQoKSlqBsJdFc/yRHWivG
         g9PP1O64DD42q6pT06/YeFQcvG0vaFpUDRyRvfdTQDxTm4vQjSObsSZDg6Cn21S3cdJn
         JtqA==
X-Gm-Message-State: APjAAAXfuABIY0/YaGuZrLVvk6xnXnzraEk4IpvVXu6iqcjvQLZ7fKYU
        Sd9tZ2RWxroOyRP2rsMsML8=
X-Google-Smtp-Source: 
 APXvYqzlvA0YHyg+DxohlJ052fxzXyIcwom3/8AKBDk+6dSxshfUFLwRwFQdgZd2p6vDS7M5BTzDOA==
X-Received: by 2002:a17:902:e406:: with SMTP id
 ci6mr9420298plb.207.1567781678201;
        Fri, 06 Sep 2019 07:54:38 -0700 (PDT)
Received: from localhost.localdomain ([2001:470:b:9c3:9e5c:8eff:fe4f:f2d0])
        by smtp.gmail.com with ESMTPSA id
 q2sm10489442pfg.144.2019.09.06.07.54.37
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Fri, 06 Sep 2019 07:54:37 -0700 (PDT)
Subject: [PATCH v8 QEMU 1/3] virtio-ballon: Implement support for page
 poison tracking feature
From: Alexander Duyck <alexander.duyck@gmail.com>
To: nitesh@redhat.com, kvm@vger.kernel.org, mst@redhat.com,
        david@redhat.com, dave.hansen@intel.com,
        linux-kernel@vger.kernel.org, linux-mm@kvack.org,
        akpm@linux-foundation.org, virtio-dev@lists.oasis-open.org
Cc: yang.zhang.wz@gmail.com, pagupta@redhat.com, riel@surriel.com,
        konrad.wilk@oracle.com, willy@infradead.org,
        lcapitulino@redhat.com, wei.w.wang@intel.com, aarcange@redhat.com,
        pbonzini@redhat.com, dan.j.williams@intel.com, mhocko@kernel.org,
        alexander.h.duyck@linux.intel.com, osalvador@suse.de
Date: Fri, 06 Sep 2019 07:54:37 -0700
Message-ID: <20190906145437.574.38479.stgit@localhost.localdomain>
In-Reply-To: <20190906145213.32552.30160.stgit@localhost.localdomain>
References: <20190906145213.32552.30160.stgit@localhost.localdomain>
User-Agent: StGit/0.17.1-dirty
MIME-Version: 1.0
Content-Type: text/plain; charset="utf-8"
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Alexander Duyck <alexander.h.duyck@linux.intel.com>

We need to make certain to advertise support for page poison tracking if
we want to actually get data on if the guest will be poisoning pages. So
if free page hinting is active we should add page poisoning support and
let the guest disable it if it isn't using it.

Page poisoning will result in a page being dirtied on free. As such we
cannot really avoid having to copy the page at least one more time since
we will need to write the poison value to the destination. As such we can
just ignore free page hinting if page poisoning is enabled as it will
actually reduce the work we have to do.

Signed-off-by: Alexander Duyck <alexander.h.duyck@linux.intel.com>
---
 hw/virtio/virtio-balloon.c         |   25 +++++++++++++++++++++----
 include/hw/virtio/virtio-balloon.h |    1 +
 2 files changed, 22 insertions(+), 4 deletions(-)

```
#### [kvm-unit-tests PATCH 1/3] x86: Fix out of bounds access when processing online_cpus
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11135685
Return-Path: <SRS0=9Awg=XB=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9A04A13BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Sep 2019 16:34:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7A084207FC
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Sep 2019 16:34:53 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2390539AbfIFQew (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 6 Sep 2019 12:34:52 -0400
Received: from mga02.intel.com ([134.134.136.20]:9378 "EHLO mga02.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2390335AbfIFQev (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 6 Sep 2019 12:34:51 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga007.jf.intel.com ([10.7.209.58])
  by orsmga101.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 06 Sep 2019 09:34:50 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.64,473,1559545200";
   d="scan'208";a="174327227"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.41])
  by orsmga007.jf.intel.com with ESMTP; 06 Sep 2019 09:34:50 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>
Cc: kvm@vger.kernel.org, Evgeny Yakovlev <wrfsh@yandex-team.ru>
Subject: [kvm-unit-tests PATCH 1/3] x86: Fix out of bounds access when
 processing online_cpus
Date: Fri,  6 Sep 2019 09:34:48 -0700
Message-Id: <20190906163450.30797-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.22.0
In-Reply-To: <20190906163450.30797-1-sean.j.christopherson@intel.com>
References: <20190906163450.30797-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

online_cpus is misdeclared as a 64 *byte* variable instead of a 64 *bit*
variable.  This causes init_apic_map() to test random bytes when it
iterates over online_cpus, which in turn can cause it to overflow id_map
and corrupt rnadom memory, e.g. pg_base.  Declare online_cpus using
MAX_TEST_CPUS, which presumably is set explicitly to match the storage
size of online_cpus (64-bit values == max of 64 CPUS).

Reported-by: Evgeny Yakovlev <wrfsh@yandex-team.ru>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 lib/x86/apic.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
