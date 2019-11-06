#### [PATCH v2 1/4] kvm: nested: Introduce read_and_check_msr_entry()From: Aaron Lewis <aaronlewis@google.com>
##### From: Aaron Lewis <aaronlewis@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Aaron Lewis <aaronlewis@google.com>
X-Patchwork-Id: 11228441
Return-Path: <SRS0=X2oT=Y5=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2EB081515
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 Nov 2019 19:19:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1700921928
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 Nov 2019 19:19:20 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="fxRm2S13"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2390865AbfKETTT (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 5 Nov 2019 14:19:19 -0500
Received: from mail-pl1-f202.google.com ([209.85.214.202]:51978 "EHLO
        mail-pl1-f202.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2390846AbfKETTT (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 5 Nov 2019 14:19:19 -0500
Received: by mail-pl1-f202.google.com with SMTP id h7so8752092pll.18
        for <kvm@vger.kernel.org>; Tue, 05 Nov 2019 11:19:18 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=zuF7sKZCPT+TK1RMBRSi/baQpV2Rh8fSC5oFHVCBvvc=;
        b=fxRm2S13cZxdOTIxyNOX/QX1BC3mC1jd1AMzjYxWmsN8JVfMmr5CP49gwlzXCU6q/T
         i08VeQ1tm9bObGKhWQvtZiGFSJQI4L8+lkAbQzTecRmB1y9jJEWb7EeBwyEUtG/lYi4c
         589gPdN6JGID9VFgompDh/r1cg8edoX2/1JHpTjHr039iGBpoON9rjFkrIU7P4Bo7AGm
         LU9gH8mLPQYzphKZpqAcymmsuHAv7udPXKH579lfWtARxY3kLnV0VQCSaxJzXIyCscIp
         eMu3BbbC03rHbkpqqKqAAdtFq7e1SZDFufUkDYCu7igGbC/L3YUByty572pSg/PRV+Ly
         NQOQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=zuF7sKZCPT+TK1RMBRSi/baQpV2Rh8fSC5oFHVCBvvc=;
        b=lxlA3vKT4V8YL7B9fpmUE7irpdPlLwC/13IU0gV5o/j2Y1DIFPfwdx3AeE46HfzGZB
         +lfiU++aUzg3OitB9V1q4Z5RM9ph8lkAQ9YDaJHl6BJv0AkxS9eZw46ra0C8pA249D3p
         m2cPVm5rs8NITrA0TLP/06yP2IuIGnHcBpHbCTo2wc2nlH9H/xsnwjSQyFuD7QuiBwCV
         AauGog6MxyvJ5nXjZbWnUznVQDDh7reS+u0DvY4hBh43Ir2UkvI6VGaadXUD8jqhePqk
         wFbElxMrMF2sfpiN6vawg518RWeoPc6ljonEiPobiJ4OBUV6xCFPKqLbGzOsfEBSgBv4
         FjiQ==
X-Gm-Message-State: APjAAAXNDJBkDV0JTPm2J5xIs5/8EI+q1LxW67arFb9VCyNj4ncuUbCV
        pxKXaIxT65ib14VSRRKjiBP+/95vsxMxcQLZdcdiY3jSLr0iNIiSzBUdlgldYtaZOl6JyQgKc1I
        OEUsthvskwjVYB8ZOCmA5B7lE89jlgzztzC0aJsmHPTj6Yh1eBGZJJ9KXk/J04As4gv5u
X-Google-Smtp-Source: 
 APXvYqzcPLdhfbgNu8QkgzNk9uVEb7eZdeeZ16LOp9wb1vAHAgFnP7+7QePdZNT9XSkCU+4dIo+tGQ70f7UiC//G
X-Received: by 2002:a63:d44a:: with SMTP id
 i10mr38553263pgj.105.1572981557994;
 Tue, 05 Nov 2019 11:19:17 -0800 (PST)
Date: Tue,  5 Nov 2019 11:19:07 -0800
In-Reply-To: <20191105191910.56505-1-aaronlewis@google.com>
Message-Id: <20191105191910.56505-2-aaronlewis@google.com>
Mime-Version: 1.0
References: <20191105191910.56505-1-aaronlewis@google.com>
X-Mailer: git-send-email 2.24.0.rc1.363.gb1bccd3e3d-goog
Subject: [PATCH v2 1/4] kvm: nested: Introduce read_and_check_msr_entry()
From: Aaron Lewis <aaronlewis@google.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Aaron Lewis <aaronlewis@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add the function read_and_check_msr_entry() which just pulls some code
out of nested_vmx_store_msr() for now, however, this is in preparation
for a change later in this series were we reuse the code in
read_and_check_msr_entry().

Reviewed-by: Jim Mattson <jmattson@google.com>
Signed-off-by: Aaron Lewis <aaronlewis@google.com>
Reviewed-by: Liran Alon <liran.alon@oracle.com>
---
 arch/x86/kvm/vmx/nested.c | 35 ++++++++++++++++++++++-------------
 1 file changed, 22 insertions(+), 13 deletions(-)

--
2.24.0.rc1.363.gb1bccd3e3d-goog

```
#### [PATCH v13 QEMU 2/3] virtio-balloon: Add bit to notify guest of unused page reporting
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Duyck <alexander.duyck@gmail.com>
X-Patchwork-Id: 11228861
Return-Path: <SRS0=X2oT=Y5=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EDB0015AB
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 Nov 2019 22:06:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D2C6F21929
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 Nov 2019 22:06:52 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="dpkpTXim"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2387487AbfKEWGt (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 5 Nov 2019 17:06:49 -0500
Received: from mail-pl1-f193.google.com ([209.85.214.193]:33665 "EHLO
        mail-pl1-f193.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2387476AbfKEWGs (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 5 Nov 2019 17:06:48 -0500
Received: by mail-pl1-f193.google.com with SMTP id ay6so3340081plb.0;
        Tue, 05 Nov 2019 14:06:48 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=subject:from:to:cc:date:message-id:in-reply-to:references
         :user-agent:mime-version:content-transfer-encoding;
        bh=VitjQQFQG7H0A5JYqbYhHy/YWDiYO6QESupJyX3H62U=;
        b=dpkpTXimibOaJbaCEiTOvdx4Sg5R+LPRID9WsbtvON8KZsyg5WRQCqiDmRtWwPFB79
         RvgSWM9iHwKfMh2W5qgOcvx5JdZ6+YfOZ73d8qankdkJ0NZoTPx3C9md1kpI5j4U13Em
         zg5yln/gzdsI1DZWnNU9+MwtueFrJAapdH9GJlTNRDy55EnKRXFrK3TO3dlkji91QCP7
         tcQm1AQrdI9k1QD+2ji4RsKZELTpKKWww2Y08CeINqdVXoF3lSDTIjEd+JzW+HDGTyjJ
         lulviB87wO4x4Jtr4cUUAcCZv/6UiNENfYxGZIFj1H0XsNJgvF7SeYx+hi97qvy9YHQ/
         2ZbA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:subject:from:to:cc:date:message-id:in-reply-to
         :references:user-agent:mime-version:content-transfer-encoding;
        bh=VitjQQFQG7H0A5JYqbYhHy/YWDiYO6QESupJyX3H62U=;
        b=B6xeSJPTb/KUAbOgHdolIsFzjDgI1LiPxr/j1xLr5km9+q3iE3jKqOJy3ZGDonfgqN
         bD0bdWqaTHiBcnO1OMiw9JM+R+D5+yY29BIoeQ5hxD7dVjQtZgcX/mAc90uiA79UEOd7
         TPeXbc5/V+x8KgM3sdSDJ3SXKJ4FPOuHliJ4yx3TIUiQzgZ0Wjibu3RfBEGVZVFaox+4
         OA7QdYwuGO98xQ/hnSKCSTOlFP3WecIEc5xsh+okflTR0Wg42mxFQ7Sv3rVPEW02osgE
         Vdh1BDcO2U3qxE01AK0u2u9fNsMooFoK68I9eGvG+Z6hz2kWceX7BVRgThJ3+tjlUe8L
         u/nQ==
X-Gm-Message-State: APjAAAWguXkwQaZ9seBA2/lpiJ8fBS4GbKOQSFbNoUPPW0sP9ygHzCFa
        oEh4EGBZdLrOrpBanjipxLw=
X-Google-Smtp-Source: 
 APXvYqxd2Q0rTJz608ziiC7guBdp3u7fxjo1jKTOG90Pc2Yi/iRJ5ku6rmBeJgZMazGaqQnjvrOw0A==
X-Received: by 2002:a17:902:9347:: with SMTP id
 g7mr35245872plp.291.1572991607655;
        Tue, 05 Nov 2019 14:06:47 -0800 (PST)
Received: from localhost.localdomain ([2001:470:b:9c3:9e5c:8eff:fe4f:f2d0])
        by smtp.gmail.com with ESMTPSA id
 x10sm18021600pgl.53.2019.11.05.14.06.46
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Tue, 05 Nov 2019 14:06:47 -0800 (PST)
Subject: [PATCH v13 QEMU 2/3] virtio-balloon: Add bit to notify guest of
 unused page reporting
From: Alexander Duyck <alexander.duyck@gmail.com>
To: kvm@vger.kernel.org, mst@redhat.com, linux-kernel@vger.kernel.org,
        willy@infradead.org, mhocko@kernel.org, linux-mm@kvack.org,
        akpm@linux-foundation.org, mgorman@techsingularity.net,
        vbabka@suse.cz
Cc: yang.zhang.wz@gmail.com, nitesh@redhat.com, konrad.wilk@oracle.com,
        david@redhat.com, pagupta@redhat.com, riel@surriel.com,
        lcapitulino@redhat.com, dave.hansen@intel.com,
        wei.w.wang@intel.com, aarcange@redhat.com, pbonzini@redhat.com,
        dan.j.williams@intel.com, alexander.h.duyck@linux.intel.com,
        osalvador@suse.de
Date: Tue, 05 Nov 2019 14:06:46 -0800
Message-ID: <20191105220646.15373.19405.stgit@localhost.localdomain>
In-Reply-To: <20191105215940.15144.65968.stgit@localhost.localdomain>
References: <20191105215940.15144.65968.stgit@localhost.localdomain>
User-Agent: StGit/0.17.1-dirty
MIME-Version: 1.0
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
#### [PATCH v13 QEMU 3/3] virtio-balloon: Provide a interface for unused page reporting
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Duyck <alexander.duyck@gmail.com>
X-Patchwork-Id: 11228865
Return-Path: <SRS0=X2oT=Y5=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 600AE139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 Nov 2019 22:06:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 3AC1021929
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 Nov 2019 22:06:59 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="VH6IuWxq"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2387552AbfKEWGz (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 5 Nov 2019 17:06:55 -0500
Received: from mail-pl1-f194.google.com ([209.85.214.194]:39988 "EHLO
        mail-pl1-f194.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2387428AbfKEWGz (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 5 Nov 2019 17:06:55 -0500
Received: by mail-pl1-f194.google.com with SMTP id e3so8217139plt.7;
        Tue, 05 Nov 2019 14:06:54 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=subject:from:to:cc:date:message-id:in-reply-to:references
         :user-agent:mime-version:content-transfer-encoding;
        bh=IYnIZF3ya8GRMyw0Z8v44wRFjachYcZ/Qaw0Oz7Yqys=;
        b=VH6IuWxq+4/4s0yCVQGds5R1YSjZbjgGZYqMH/43ZaOyXpgNeOZHnwNWid+sB52+iD
         KWKjlv6SwAxWit1DFmlNIeCB4I+vRHFK4C8033BExeRp/KKOC+rz9poYIGwNbCvOXZVS
         o/IDbLmMsaaCOxlOYb5HVEeD8MYNh/PjERx2BKvCme1iV64K3xyTsxNJY8ru5CXua6wB
         aO/pp2PZJDebPreHlWp4VUDI0BbOd5YaWHSEA1bjy4J0fdjvOuwDGbf+WOzZ65Gq3lAr
         5xqAQ3nsmmX1twja7wEvT+mg6WOq3VYgK2jwmoJ4jR13ubqjEwczrYRy5YkACvGhuaNp
         1XQA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:subject:from:to:cc:date:message-id:in-reply-to
         :references:user-agent:mime-version:content-transfer-encoding;
        bh=IYnIZF3ya8GRMyw0Z8v44wRFjachYcZ/Qaw0Oz7Yqys=;
        b=ij9v5xo1A87yhtBlzwy1euBIlqMHU90vn404fIJlASLY97dfG+t+UNz+eoFaZoTa55
         xFezWCUI79zgQku+BVr4fAW+mrWcHfbZeFmPj/KD+4jhaGjnOZ0oeCr5qiCy9fQYPUbT
         rQb+KZeQxNDphF9EfqwZUGjHUN+umrIVS8xa7I0plIHNZRxMDmjotFQduFWxuC5AV/Gh
         swpxPoqEBWwbZJPBAfjumoGR7YLSIDm4+OXu3imUvrVwfKbxV/mo/i8ZgyJ6465FiAmd
         ihFpfgzVLpMwzGbtDMGx8bVwBKQNk0cuZdPh9znMzEx6Xwb5HtdcCB8V6dNgg4VAmkSb
         SQkg==
X-Gm-Message-State: APjAAAWc3fdyf8Ez6ZHJ2ICTWPa6C2IekN1zOhgjv6S9dI4u4jPlWqTx
        40De1nFm4wnWVou0Pu7+6Yg=
X-Google-Smtp-Source: 
 APXvYqwZYsPGacbb5rgtO0Qje5s17EoKhvENCkQzsutsaB418YulXgadq2A3Ag4BrWWKA7Vre67pOA==
X-Received: by 2002:a17:902:ab82:: with SMTP id
 f2mr3383748plr.39.1572991613795;
        Tue, 05 Nov 2019 14:06:53 -0800 (PST)
Received: from localhost.localdomain ([2001:470:b:9c3:9e5c:8eff:fe4f:f2d0])
        by smtp.gmail.com with ESMTPSA id
 12sm16042503pfp.79.2019.11.05.14.06.53
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Tue, 05 Nov 2019 14:06:53 -0800 (PST)
Subject: [PATCH v13 QEMU 3/3] virtio-balloon: Provide a interface for unused
 page reporting
From: Alexander Duyck <alexander.duyck@gmail.com>
To: kvm@vger.kernel.org, mst@redhat.com, linux-kernel@vger.kernel.org,
        willy@infradead.org, mhocko@kernel.org, linux-mm@kvack.org,
        akpm@linux-foundation.org, mgorman@techsingularity.net,
        vbabka@suse.cz
Cc: yang.zhang.wz@gmail.com, nitesh@redhat.com, konrad.wilk@oracle.com,
        david@redhat.com, pagupta@redhat.com, riel@surriel.com,
        lcapitulino@redhat.com, dave.hansen@intel.com,
        wei.w.wang@intel.com, aarcange@redhat.com, pbonzini@redhat.com,
        dan.j.williams@intel.com, alexander.h.duyck@linux.intel.com,
        osalvador@suse.de
Date: Tue, 05 Nov 2019 14:06:52 -0800
Message-ID: <20191105220652.15373.45960.stgit@localhost.localdomain>
In-Reply-To: <20191105215940.15144.65968.stgit@localhost.localdomain>
References: <20191105215940.15144.65968.stgit@localhost.localdomain>
User-Agent: StGit/0.17.1-dirty
MIME-Version: 1.0
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
#### [PATCH 1/2] IFC hardware operation layer
##### From: Zhu Lingshan <lingshan.zhu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhu Lingshan <lingshan.zhu@intel.com>
X-Patchwork-Id: 11227405
Return-Path: <SRS0=X2oT=Y5=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3292B1747
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 Nov 2019 09:39:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 078772190F
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 Nov 2019 09:39:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730965AbfKEJjz (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 5 Nov 2019 04:39:55 -0500
Received: from mga02.intel.com ([134.134.136.20]:24242 "EHLO mga02.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1730630AbfKEJjy (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 5 Nov 2019 04:39:54 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by orsmga101.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 05 Nov 2019 01:39:53 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.68,270,1569308400";
   d="scan'208";a="200323055"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.240.193.79])
  by fmsmga008.fm.intel.com with ESMTP; 05 Nov 2019 01:39:51 -0800
From: Zhu Lingshan <lingshan.zhu@intel.com>
To: mst@redhat.com, jasowang@redhat.com, alex.williamson@redhat.com
Cc: linux-kernel@vger.kernel.org,
        virtualization@lists.linux-foundation.org, kvm@vger.kernel.org,
        netdev@vger.kernel.org, dan.daly@intel.com,
        cunming.liang@intel.com, tiwei.bie@intel.com, jason.zeng@intel.com,
        Zhu Lingshan <lingshan.zhu@intel.com>
Subject: [PATCH 1/2] IFC hardware operation layer
Date: Tue,  5 Nov 2019 17:37:39 +0800
Message-Id: <1572946660-26265-2-git-send-email-lingshan.zhu@intel.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1572946660-26265-1-git-send-email-lingshan.zhu@intel.com>
References: <1572946660-26265-1-git-send-email-lingshan.zhu@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This commit introduced ifcvf_base layer, which handles hardware
operations and configurations.

Signed-off-by: Zhu Lingshan <lingshan.zhu@intel.com>
---
 drivers/vhost/ifcvf/ifcvf_base.c | 344 +++++++++++++++++++++++++++++++++++++++
 drivers/vhost/ifcvf/ifcvf_base.h | 132 +++++++++++++++
 2 files changed, 476 insertions(+)
 create mode 100644 drivers/vhost/ifcvf/ifcvf_base.c
 create mode 100644 drivers/vhost/ifcvf/ifcvf_base.h

diff --git a/drivers/vhost/ifcvf/ifcvf_base.c b/drivers/vhost/ifcvf/ifcvf_base.c
new file mode 100644
index 0000000..0659f41
--- /dev/null
+++ b/drivers/vhost/ifcvf/ifcvf_base.c
@@ -0,0 +1,344 @@
+// SPDX-License-Identifier: GPL-2.0-only
+/*
+ * Copyright (C) 2019 Intel Corporation.
+ */
+
+#include "ifcvf_base.h"
+
+static void *get_cap_addr(struct ifcvf_hw *hw, struct virtio_pci_cap *cap)
+{
+	struct ifcvf_adapter *ifcvf;
+	u32 length, offset;
+	u8 bar;
+
+	length = le32_to_cpu(cap->length);
+	offset = le32_to_cpu(cap->offset);
+	bar = le32_to_cpu(cap->bar);
+
+	ifcvf = container_of(hw, struct ifcvf_adapter, vf);
+
+	if (bar >= IFCVF_PCI_MAX_RESOURCE) {
+		IFC_DBG(ifcvf->dev,
+			"Invalid bar number %u to get capabilities.\n", bar);
+		return NULL;
+	}
+
+	if (offset + length < offset) {
+		IFC_DBG(ifcvf->dev, "offset(%u) + length(%u) overflows\n",
+			offset, length);
+		return NULL;
+	}
+
+	if (offset + length > hw->mem_resource[cap->bar].len) {
+		IFC_DBG(ifcvf->dev,
+			"offset(%u) + len(%u) overflows bar%u to get capabilities.\n",
+			offset, length, bar);
+		return NULL;
+	}
+
+	return hw->mem_resource[bar].addr + offset;
+}
+
+int ifcvf_read_config_range(struct pci_dev *dev,
+			uint32_t *val, int size, int where)
+{
+	int ret, i;
+
+	for (i = 0; i < size; i += 4) {
+		ret = pci_read_config_dword(dev, where + i, val + i / 4);
+		if (ret < 0)
+			return ret;
+	}
+
+	return 0;
+}
+
+int ifcvf_init_hw(struct ifcvf_hw *hw, struct pci_dev *dev)
+{
+	struct virtio_pci_cap cap;
+	u16 notify_off;
+	int ret;
+	u8 pos;
+	u32 i;
+
+	ret = pci_read_config_byte(dev, PCI_CAPABILITY_LIST, &pos);
+
+	if (ret < 0) {
+		IFC_ERR(&dev->dev, "Failed to read PCI capability list.\n");
+		return -EIO;
+	}
+
+	while (pos) {
+		ret = ifcvf_read_config_range(dev, (u32 *)&cap,
+					      sizeof(cap), pos);
+
+		if (ret < 0) {
+			IFC_ERR(&dev->dev, "Failed to get PCI capability at %x",
+				pos);
+			break;
+		}
+
+		if (cap.cap_vndr != PCI_CAP_ID_VNDR)
+			goto next;
+
+		IFC_DBG(&dev->dev, "read PCI config: config type: %u, PCI bar: %u,\
+			 PCI bar offset: %u, PCI config len: %u.\n",
+			cap.cfg_type, cap.bar, cap.offset, cap.length);
+
+		switch (cap.cfg_type) {
+		case VIRTIO_PCI_CAP_COMMON_CFG:
+			hw->common_cfg = get_cap_addr(hw, &cap);
+			IFC_INFO(&dev->dev, "hw->common_cfg = %p.\n",
+				 hw->common_cfg);
+			break;
+		case VIRTIO_PCI_CAP_NOTIFY_CFG:
+			pci_read_config_dword(dev, pos + sizeof(cap),
+					      &hw->notify_off_multiplier);
+			hw->notify_bar = cap.bar;
+			hw->notify_base = get_cap_addr(hw, &cap);
+			IFC_INFO(&dev->dev, "hw->notify_base = %p.\n",
+				 hw->notify_base);
+			break;
+		case VIRTIO_PCI_CAP_ISR_CFG:
+			hw->isr = get_cap_addr(hw, &cap);
+			IFC_INFO(&dev->dev, "hw->isr = %p.\n", hw->isr);
+			break;
+		case VIRTIO_PCI_CAP_DEVICE_CFG:
+			hw->net_cfg = get_cap_addr(hw, &cap);
+			IFC_INFO(&dev->dev, "hw->net_cfg = %p.\n", hw->net_cfg);
+			break;
+		}
+next:
+		pos = cap.cap_next;
+	}
+
+	if (hw->common_cfg == NULL || hw->notify_base == NULL ||
+	    hw->isr == NULL || hw->net_cfg == NULL) {
+		IFC_DBG(&dev->dev, "Incomplete PCI capabilities.\n");
+		return -1;
+	}
+
+	for (i = 0; i < IFCVF_MAX_QUEUE_PAIRS * 2; i++) {
+		iowrite16(i, &hw->common_cfg->queue_select);
+		notify_off = ioread16(&hw->common_cfg->queue_notify_off);
+		hw->notify_addr[i] = (void *)((u8 *)hw->notify_base +
+				     notify_off * hw->notify_off_multiplier);
+	}
+
+	hw->lm_cfg = hw->mem_resource[IFCVF_LM_BAR].addr;
+
+	IFC_DBG(&dev->dev, "PCI capability mapping: common cfg: %p,\
+		notify base: %p\n, isr cfg: %p, device cfg: %p,\
+		multiplier: %u\n",
+		hw->common_cfg, hw->notify_base, hw->isr,
+		hw->net_cfg, hw->notify_off_multiplier);
+
+	return 0;
+}
+
+u8 ifcvf_get_status(struct ifcvf_hw *hw)
+{
+	u8 old_gen, new_gen, status;
+
+	do {
+		old_gen = ioread8(&hw->common_cfg->config_generation);
+		status = ioread8(&hw->common_cfg->device_status);
+		new_gen = ioread8(&hw->common_cfg->config_generation);
+	} while (old_gen != new_gen);
+
+	return status;
+}
+
+void ifcvf_set_status(struct ifcvf_hw *hw, u8 status)
+{
+	iowrite8(status, &hw->common_cfg->device_status);
+}
+
+void ifcvf_reset(struct ifcvf_hw *hw)
+{
+	ifcvf_set_status(hw, 0);
+	ifcvf_get_status(hw);
+}
+
+static void ifcvf_add_status(struct ifcvf_hw *hw, u8 status)
+{
+	if (status != 0)
+		status |= ifcvf_get_status(hw);
+
+	ifcvf_set_status(hw, status);
+	ifcvf_get_status(hw);
+}
+
+u64 ifcvf_get_features(struct ifcvf_hw *hw)
+{
+	struct virtio_pci_common_cfg *cfg = hw->common_cfg;
+	u32 features_lo, features_hi;
+
+	iowrite32(0, &cfg->device_feature_select);
+	features_lo = ioread32(&cfg->device_feature);
+
+	iowrite32(1, &cfg->device_feature_select);
+	features_hi = ioread32(&cfg->device_feature);
+
+	return ((u64)features_hi << 32) | features_lo;
+}
+
+void ifcvf_read_net_config(struct ifcvf_hw *hw, u64 offset,
+		       void *dst, int length)
+{
+	u8 old_gen, new_gen, *p;
+	int i;
+
+	WARN_ON(offset + length > sizeof (struct ifcvf_net_config));
+
+	do {
+		old_gen = ioread8(&hw->common_cfg->config_generation);
+		p = dst;
+
+		for (i = 0; i < length; i++)
+			*p++ = ioread8((u8 *)hw->net_cfg + offset + i);
+
+		new_gen = ioread8(&hw->common_cfg->config_generation);
+	} while (old_gen != new_gen);
+}
+
+void ifcvf_write_net_config(struct ifcvf_hw *hw, u64 offset,
+			    const void *src, int length)
+{
+	const u8 *p;
+	int i;
+
+	p = src;
+	WARN_ON(offset + length > sizeof (struct ifcvf_net_config));
+
+	for (i = 0; i < length; i++)
+		iowrite8(*p++, (u8 *)hw->net_cfg + offset + i);
+}
+
+static void ifcvf_set_features(struct ifcvf_hw *hw, u64 features)
+{
+	struct virtio_pci_common_cfg *cfg = hw->common_cfg;
+
+	iowrite32(0, &cfg->guest_feature_select);
+	iowrite32(features & ((1ULL << 32) - 1), &cfg->guest_feature);
+
+	iowrite32(1, &cfg->guest_feature_select);
+	iowrite32(features >> 32, &cfg->guest_feature);
+}
+
+static int ifcvf_config_features(struct ifcvf_hw *hw)
+{
+	struct ifcvf_adapter *ifcvf;
+
+	ifcvf =	container_of(hw, struct ifcvf_adapter, vf);
+	ifcvf_set_features(hw, hw->req_features);
+	ifcvf_add_status(hw, VIRTIO_CONFIG_S_FEATURES_OK);
+
+	if (!(ifcvf_get_status(hw) & VIRTIO_CONFIG_S_FEATURES_OK)) {
+		IFC_ERR(ifcvf->dev, "Failed to set FEATURES_OK status\n");
+		return -EIO;
+	}
+
+	return 0;
+}
+
+void io_write64_twopart(u64 val, u32 *lo, u32 *hi)
+{
+	iowrite32(val & ((1ULL << 32) - 1), lo);
+	iowrite32(val >> 32, hi);
+}
+
+static int ifcvf_hw_enable(struct ifcvf_hw *hw)
+{
+	struct virtio_pci_common_cfg *cfg;
+	struct ifcvf_adapter *ifcvf;
+	u8 *lm_cfg;
+	u32 i;
+
+	ifcvf = container_of(hw, struct ifcvf_adapter, vf);
+	cfg = hw->common_cfg;
+	lm_cfg = hw->lm_cfg;
+	iowrite16(IFCVF_MSI_CONFIG_OFF, &cfg->msix_config);
+
+	if (ioread16(&cfg->msix_config) == VIRTIO_MSI_NO_VECTOR) {
+		IFC_ERR(ifcvf->dev, "No msix vector for device config.\n");
+		return -1;
+	}
+
+	for (i = 0; i < hw->nr_vring; i++) {
+		iowrite16(i, &cfg->queue_select);
+		io_write64_twopart(hw->vring[i].desc, &cfg->queue_desc_lo,
+				&cfg->queue_desc_hi);
+		io_write64_twopart(hw->vring[i].avail, &cfg->queue_avail_lo,
+				&cfg->queue_avail_hi);
+		io_write64_twopart(hw->vring[i].used, &cfg->queue_used_lo,
+				&cfg->queue_used_hi);
+		iowrite16(hw->vring[i].size, &cfg->queue_size);
+
+		*(u32 *)(lm_cfg + IFCVF_LM_RING_STATE_OFFSET +
+				(i / 2) * IFCVF_LM_CFG_SIZE + (i % 2) * 4) =
+			(u32)hw->vring[i].last_avail_idx |
+			((u32)hw->vring[i].last_used_idx << 16);
+
+		iowrite16(i + IFCVF_MSI_QUEUE_OFF, &cfg->queue_msix_vector);
+		if (ioread16(&cfg->queue_msix_vector) ==
+		    VIRTIO_MSI_NO_VECTOR) {
+			IFC_ERR(ifcvf->dev,
+				"No msix vector for queue %u.\n", i);
+			return -1;
+		}
+
+		iowrite16(1, &cfg->queue_enable);
+	}
+
+	return 0;
+}
+
+static void ifcvf_hw_disable(struct ifcvf_hw *hw)
+{
+	struct virtio_pci_common_cfg *cfg;
+	u32 i;
+
+	cfg = hw->common_cfg;
+	iowrite16(VIRTIO_MSI_NO_VECTOR, &cfg->msix_config);
+
+	for (i = 0; i < hw->nr_vring; i++) {
+		iowrite16(i, &cfg->queue_select);
+		iowrite16(0, &cfg->queue_enable);
+		iowrite16(VIRTIO_MSI_NO_VECTOR, &cfg->queue_msix_vector);
+	}
+}
+
+int ifcvf_start_hw(struct ifcvf_hw *hw)
+{
+	ifcvf_reset(hw);
+	ifcvf_add_status(hw, VIRTIO_CONFIG_S_ACKNOWLEDGE);
+	ifcvf_add_status(hw, VIRTIO_CONFIG_S_DRIVER);
+
+	if (ifcvf_config_features(hw) < 0)
+		return -1;
+
+	if (ifcvf_hw_enable(hw) < 0)
+		return -1;
+
+	ifcvf_add_status(hw, VIRTIO_CONFIG_S_DRIVER_OK);
+
+	return 0;
+}
+
+void ifcvf_stop_hw(struct ifcvf_hw *hw)
+{
+	ifcvf_hw_disable(hw);
+	ifcvf_reset(hw);
+}
+
+void ifcvf_notify_queue(struct ifcvf_hw *hw, u16 qid)
+{
+	iowrite16(qid, hw->notify_addr[qid]);
+}
+
+u64 ifcvf_get_queue_notify_off(struct ifcvf_hw *hw, int qid)
+{
+	return (u8 *)hw->notify_addr[qid] -
+		(u8 *)hw->mem_resource[hw->notify_bar].addr;
+}
diff --git a/drivers/vhost/ifcvf/ifcvf_base.h b/drivers/vhost/ifcvf/ifcvf_base.h
new file mode 100644
index 0000000..c97f0eb
--- /dev/null
+++ b/drivers/vhost/ifcvf/ifcvf_base.h
@@ -0,0 +1,132 @@
+/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
+/*
+ * Copyright (C) 2019 Intel Corporation.
+ */
+
+#ifndef _IFCVF_H_
+#define _IFCVF_H_
+
+#include <linux/virtio_mdev_ops.h>
+#include <linux/mdev.h>
+#include <linux/pci.h>
+#include <linux/pci_regs.h>
+#include <uapi/linux/virtio_net.h>
+#include <uapi/linux/virtio_config.h>
+#include <uapi/linux/virtio_pci.h>
+
+#define IFCVF_VENDOR_ID         0x1AF4
+#define IFCVF_DEVICE_ID         0x1041
+#define IFCVF_SUBSYS_VENDOR_ID  0x8086
+#define IFCVF_SUBSYS_DEVICE_ID  0x001A
+
+#define IFCVF_MDEV_LIMIT	1
+
+/*
+ * Some ifcvf feature bits (currently bits 28 through 31) are
+ * reserved for the transport being used (eg. ifcvf_ring), the
+ * rest are per-device feature bits.
+ */
+#define IFCVF_TRANSPORT_F_START 28
+#define IFCVF_TRANSPORT_F_END   34
+
+#define IFC_SUPPORTED_FEATURES \
+		((1ULL << VIRTIO_NET_F_MAC)			| \
+		 (1ULL << VIRTIO_F_ANY_LAYOUT)			| \
+		 (1ULL << VIRTIO_F_VERSION_1)			| \
+		 (1ULL << VIRTIO_F_ORDER_PLATFORM)			| \
+		 (1ULL << VIRTIO_NET_F_GUEST_ANNOUNCE)		| \
+		 (1ULL << VIRTIO_NET_F_CTRL_VQ)			| \
+		 (1ULL << VIRTIO_NET_F_STATUS)			| \
+		 (1ULL << VIRTIO_NET_F_MRG_RXBUF)) /* not fully supported */
+
+//Not support MQ, only one queue pair for now.
+#define IFCVF_MAX_QUEUE_PAIRS		1
+#define IFCVF_MAX_QUEUES		2
+
+#define IFCVF_QUEUE_ALIGNMENT		PAGE_SIZE
+
+#define IFCVF_MSI_CONFIG_OFF	0
+#define IFCVF_MSI_QUEUE_OFF	1
+#define IFCVF_PCI_MAX_RESOURCE	6
+
+#define IFCVF_LM_CFG_SIZE		0x40
+#define IFCVF_LM_RING_STATE_OFFSET	0x20
+#define IFCVF_LM_BAR	4
+
+#define IFCVF_32_BIT_MASK		0xffffffff
+
+#define IFC_ERR(dev, fmt, ...)	dev_err(dev, fmt, ##__VA_ARGS__)
+#define IFC_DBG(dev, fmt, ...)	dev_dbg(dev, fmt, ##__VA_ARGS__)
+#define IFC_INFO(dev, fmt, ...)	dev_info(dev, fmt, ##__VA_ARGS__)
+
+#define IFC_PRIVATE_TO_VF(adapter) \
+	(&((struct ifcvf_adapter *)adapter)->vf)
+
+#define IFCVF_MAX_INTR (IFCVF_MAX_QUEUE_PAIRS * 2 + 1)
+
+struct ifcvf_net_config {
+	u8    mac[6];
+	u16   status;
+	u16   max_virtqueue_pairs;
+} __packed;
+
+struct ifcvf_pci_mem_resource {
+	/* Physical address, 0 if not resource. */
+	u64      phys_addr;
+	/* Length of the resource. */
+	u64      len;
+	/* Virtual address, NULL when not mapped. */
+	u8       *addr;
+};
+
+struct vring_info {
+	u64 desc;
+	u64 avail;
+	u64 used;
+	u16 size;
+	u16 last_avail_idx;
+	u16 last_used_idx;
+	bool ready;
+	char msix_name[256];
+	struct virtio_mdev_callback cb;
+};
+
+struct ifcvf_hw {
+	u8	*isr;
+	u8	notify_bar;
+	u8	*lm_cfg;
+	u8	nr_vring;
+	u16	*notify_base;
+	u16	*notify_addr[IFCVF_MAX_QUEUE_PAIRS * 2];
+	u32	notify_off_multiplier;
+	u64	req_features;
+	struct	virtio_pci_common_cfg *common_cfg;
+	struct	ifcvf_net_config *net_cfg;
+	struct	vring_info vring[IFCVF_MAX_QUEUE_PAIRS * 2];
+	struct	ifcvf_pci_mem_resource mem_resource[IFCVF_PCI_MAX_RESOURCE];
+};
+
+struct ifcvf_adapter {
+	struct	device *dev;
+	struct	mutex mdev_lock;
+	int	mdev_count;
+	int	vectors;
+	struct	ifcvf_hw vf;
+};
+
+int ifcvf_init_hw(struct ifcvf_hw *hw, struct pci_dev *dev);
+int ifcvf_start_hw(struct ifcvf_hw *hw);
+void ifcvf_stop_hw(struct ifcvf_hw *hw);
+void ifcvf_notify_queue(struct ifcvf_hw *hw, u16 qid);
+u8 ifcvf_get_linkstatus(struct ifcvf_hw *hw);
+void ifcvf_read_net_config(struct ifcvf_hw *hw, u64 offset,
+			   void *dst, int length);
+void ifcvf_write_net_config(struct ifcvf_hw *hw, u64 offset,
+			    const void *src, int length);
+u8 ifcvf_get_status(struct ifcvf_hw *hw);
+void ifcvf_set_status(struct ifcvf_hw *hw, u8 status);
+void io_write64_twopart(u64 val, u32 *lo, u32 *hi);
+void ifcvf_reset(struct ifcvf_hw *hw);
+u64 ifcvf_get_features(struct ifcvf_hw *hw);
+
+#endif /* _IFCVF_H_ */

From patchwork Tue Nov  5 09:37:40 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhu Lingshan <lingshan.zhu@intel.com>
X-Patchwork-Id: 11227407
Return-Path: <SRS0=X2oT=Y5=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id ADA471864
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 Nov 2019 09:40:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 826B7217F5
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 Nov 2019 09:40:02 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730980AbfKEJj6 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 5 Nov 2019 04:39:58 -0500
Received: from mga02.intel.com ([134.134.136.20]:24242 "EHLO mga02.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1730856AbfKEJj5 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 5 Nov 2019 04:39:57 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by orsmga101.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 05 Nov 2019 01:39:57 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.68,270,1569308400";
   d="scan'208";a="200323066"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.240.193.79])
  by fmsmga008.fm.intel.com with ESMTP; 05 Nov 2019 01:39:54 -0800
From: Zhu Lingshan <lingshan.zhu@intel.com>
To: mst@redhat.com, jasowang@redhat.com, alex.williamson@redhat.com
Cc: linux-kernel@vger.kernel.org,
        virtualization@lists.linux-foundation.org, kvm@vger.kernel.org,
        netdev@vger.kernel.org, dan.daly@intel.com,
        cunming.liang@intel.com, tiwei.bie@intel.com, jason.zeng@intel.com,
        Zhu Lingshan <lingshan.zhu@intel.com>
Subject: [PATCH 2/2] IFC VDPA layer
Date: Tue,  5 Nov 2019 17:37:40 +0800
Message-Id: <1572946660-26265-3-git-send-email-lingshan.zhu@intel.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1572946660-26265-1-git-send-email-lingshan.zhu@intel.com>
References: <1572946660-26265-1-git-send-email-lingshan.zhu@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This commit introduced IFC operations for vdpa, which complys to
virtio_mdev and vhost_mdev interfaces, handles IFC VF
initialization, configuration and removal.

Signed-off-by: Zhu Lingshan <lingshan.zhu@intel.com>
---
 drivers/vhost/ifcvf/ifcvf_main.c | 605 +++++++++++++++++++++++++++++++++++++++
 1 file changed, 605 insertions(+)
 create mode 100644 drivers/vhost/ifcvf/ifcvf_main.c

diff --git a/drivers/vhost/ifcvf/ifcvf_main.c b/drivers/vhost/ifcvf/ifcvf_main.c
new file mode 100644
index 0000000..7165457
--- /dev/null
+++ b/drivers/vhost/ifcvf/ifcvf_main.c
@@ -0,0 +1,605 @@
+// SPDX-License-Identifier: GPL-2.0-only
+/*
+ * Copyright (C) 2019 Intel Corporation.
+ */
+
+#include <linux/interrupt.h>
+#include <linux/module.h>
+#include <linux/mdev.h>
+#include <linux/pci.h>
+#include <linux/sysfs.h>
+#include "ifcvf_base.h"
+
+#define VERSION_STRING	"0.1"
+#define DRIVER_AUTHOR	"Intel Corporation"
+#define IFCVF_DRIVER_NAME	"ifcvf"
+
+static struct ifcvf_hw *mdev_to_vf(struct mdev_device *mdev)
+{
+	struct ifcvf_asapter *adapter = mdev_get_drvdata(mdev);
+	struct ifcvf_hw *vf = IFC_PRIVATE_TO_VF(adapter);
+
+	return vf;
+}
+
+static irqreturn_t ifcvf_intr_handler(int irq, void *arg)
+{
+	struct vring_info *vring = arg;
+
+	if (vring->cb.callback)
+		return vring->cb.callback(vring->cb.private);
+
+	return IRQ_HANDLED;
+}
+
+static u64 ifcvf_mdev_get_features(struct mdev_device *mdev)
+{
+	struct ifcvf_hw *vf = mdev_to_vf(mdev);
+
+	return ifcvf_get_features(vf);
+}
+
+static int ifcvf_mdev_set_features(struct mdev_device *mdev, u64 features)
+{
+	struct ifcvf_hw *vf = mdev_to_vf(mdev);
+
+	vf->req_features = features;
+
+	return 0;
+}
+
+static u64 ifcvf_mdev_get_vq_state(struct mdev_device *mdev, u16 qid)
+{
+	struct ifcvf_hw *vf = mdev_to_vf(mdev);
+	u16 last_avail_idx;
+
+	last_avail_idx = *(u16 *)(vf->lm_cfg + IFCVF_LM_RING_STATE_OFFSET +
+			 (qid / 2) * IFCVF_LM_CFG_SIZE + (qid % 2) * 4);
+
+	return last_avail_idx;
+}
+
+static int ifcvf_mdev_set_vq_state(struct mdev_device *mdev, u16 qid, u64 num)
+{
+	struct ifcvf_hw *vf = mdev_to_vf(mdev);
+
+	vf->vring[qid].last_avail_idx = num;
+
+	return 0;
+}
+
+static int ifcvf_mdev_set_vq_address(struct mdev_device *mdev, u16 idx,
+				     u64 desc_area, u64 driver_area,
+				     u64 device_area)
+{
+	struct ifcvf_hw *vf = mdev_to_vf(mdev);
+
+	vf->vring[idx].desc = desc_area;
+	vf->vring[idx].avail = driver_area;
+	vf->vring[idx].used = device_area;
+
+	return 0;
+}
+
+static void ifcvf_mdev_set_vq_num(struct mdev_device *mdev, u16 qid, u32 num)
+{
+	struct ifcvf_hw *vf = mdev_to_vf(mdev);
+
+	vf->vring[qid].size = num;
+}
+
+static void ifcvf_mdev_set_vq_ready(struct mdev_device *mdev,
+				    u16 qid, bool ready)
+{
+	struct ifcvf_hw *vf = mdev_to_vf(mdev);
+
+	vf->vring[qid].ready = ready;
+}
+
+static bool ifcvf_mdev_get_vq_ready(struct mdev_device *mdev, u16 qid)
+{
+	struct ifcvf_hw *vf = mdev_to_vf(mdev);
+
+	return vf->vring[qid].ready;
+}
+
+static void ifcvf_mdev_set_vq_cb(struct mdev_device *mdev, u16 idx,
+				 struct virtio_mdev_callback *cb)
+{
+	struct ifcvf_hw *vf = mdev_to_vf(mdev);
+
+	vf->vring[idx].cb = *cb;
+}
+
+static void ifcvf_mdev_kick_vq(struct mdev_device *mdev, u16 idx)
+{
+	struct ifcvf_hw *vf = mdev_to_vf(mdev);
+
+	ifcvf_notify_queue(vf, idx);
+}
+
+static u8 ifcvf_mdev_get_status(struct mdev_device *mdev)
+{
+	struct ifcvf_hw *vf = mdev_to_vf(mdev);
+
+	return ifcvf_get_status(vf);
+}
+
+static u32 ifcvf_mdev_get_generation(struct mdev_device *mdev)
+{
+	struct ifcvf_hw *vf = mdev_to_vf(mdev);
+
+	return ioread8(&vf->common_cfg->config_generation);
+}
+
+static u32 ifcvf_mdev_get_device_id(struct mdev_device *mdev)
+{
+	return VIRTIO_ID_NET;
+}
+
+static u32 ifcvf_mdev_get_vendor_id(struct mdev_device *mdev)
+{
+	return IFCVF_VENDOR_ID;
+}
+
+static u16 ifcvf_mdev_get_vq_align(struct mdev_device *mdev)
+{
+	return IFCVF_QUEUE_ALIGNMENT;
+}
+
+static u64 ifcvf_mdev_get_mdev_features(struct mdev_device *mdev)
+{
+	return VIRTIO_MDEV_F_VERSION_1;
+}
+
+static int ifcvf_start_datapath(void *private)
+{
+	struct ifcvf_hw *vf = IFC_PRIVATE_TO_VF(private);
+	struct ifcvf_adapter *ifcvf;
+	int i, ret = 0;
+
+	ifcvf = container_of(vf, struct ifcvf_adapter, vf);
+
+	for (i = 0; i < IFCVF_MAX_QUEUE_PAIRS * 2; i++) {
+		if (!vf->vring[i].ready) {
+			IFC_ERR(ifcvf->dev,
+				"Failed to start datapath, vring %d not ready.\n", i);
+			return -EINVAL;
+		}
+
+		if (!vf->vring[i].size) {
+			IFC_ERR(ifcvf->dev,
+				"Failed to start datapath, vring %d size is zero.\n", i);
+			return -EINVAL;
+		}
+
+		if (!vf->vring[i].desc || !vf->vring[i].avail ||
+			!vf->vring[i].used) {
+			IFC_ERR(ifcvf->dev,
+				"Failed to start datapath, "
+				"invaild value for vring %d desc,"
+				"avail_idx or usex_idx.\n", i);
+			return -EINVAL;
+		}
+	}
+
+	vf->nr_vring = i;
+	ret = ifcvf_start_hw(vf);
+
+	return ret;
+}
+
+static int ifcvf_stop_datapath(void *private)
+{
+	struct ifcvf_hw *vf = IFC_PRIVATE_TO_VF(private);
+	int i;
+
+	for (i = 0; i < IFCVF_MAX_QUEUES; i++)
+		vf->vring[i].cb.callback = NULL;
+
+	ifcvf_stop_hw(vf);
+
+	return 0;
+}
+
+static void ifcvf_reset_vring(struct ifcvf_adapter *adapter)
+{
+	struct ifcvf_hw *vf = IFC_PRIVATE_TO_VF(adapter);
+	struct virtio_pci_common_cfg *cfg;
+	u8 *lm_cfg;
+	int i;
+
+	cfg = vf->common_cfg;
+	lm_cfg = vf->lm_cfg;
+
+	for (i = 0; i < IFCVF_MAX_QUEUE_PAIRS * 2; i++) {
+		vf->vring[i].last_used_idx = 0;
+		vf->vring[i].last_avail_idx = 0;
+		vf->vring[i].desc = 0;
+		vf->vring[i].avail = 0;
+		vf->vring[i].used = 0;
+		vf->vring[i].ready = 0;
+		vf->vring->cb.callback = NULL;
+		vf->vring->cb.private = NULL;
+
+	}
+
+	ifcvf_reset(vf);
+}
+
+static void ifcvf_mdev_set_status(struct mdev_device *mdev, u8 status)
+{
+	struct ifcvf_adapter *adapter = mdev_get_drvdata(mdev);
+	struct ifcvf_hw *vf = IFC_PRIVATE_TO_VF(adapter);
+	int ret = 0;
+
+	if (status == 0) {
+		ifcvf_stop_datapath(adapter);
+		ifcvf_reset_vring(adapter);
+		return;
+	}
+
+	if (status & VIRTIO_CONFIG_S_DRIVER_OK) {
+		ret = ifcvf_start_datapath(adapter);
+
+		if (ret)
+			IFC_ERR(adapter->dev, "Failed to set mdev status %u.\n",
+				status);
+	}
+
+	ifcvf_set_status(vf, status);
+}
+
+static u16 ifcvf_mdev_get_vq_num_max(struct mdev_device *mdev)
+{
+	struct ifcvf_hw *vf = mdev_to_vf(mdev);
+
+	return vf->vring[0].size;
+}
+static void ifcvf_mdev_get_config(struct mdev_device *mdev, unsigned int offset,
+			     void *buf, unsigned int len)
+{
+	struct ifcvf_hw *vf = mdev_to_vf(mdev);
+
+	WARN_ON(offset + len > sizeof(struct ifcvf_net_config));
+	ifcvf_read_net_config(vf, offset, buf, len);
+}
+
+static void ifcvf_mdev_set_config(struct mdev_device *mdev, unsigned int offset,
+			     const void *buf, unsigned int len)
+{
+	struct ifcvf_hw *vf = mdev_to_vf(mdev);
+
+	WARN_ON(offset + len > sizeof(struct ifcvf_net_config));
+	ifcvf_write_net_config(vf, offset, buf, len);
+}
+
+static struct virtio_mdev_device_ops ifc_mdev_ops = {
+	.get_features  = ifcvf_mdev_get_features,
+	.set_features  = ifcvf_mdev_set_features,
+	.get_status    = ifcvf_mdev_get_status,
+	.set_status    = ifcvf_mdev_set_status,
+	.get_vq_num_max = ifcvf_mdev_get_vq_num_max,
+	.get_vq_state   = ifcvf_mdev_get_vq_state,
+	.set_vq_state   = ifcvf_mdev_set_vq_state,
+	.set_vq_cb      = ifcvf_mdev_set_vq_cb,
+	.set_vq_ready   = ifcvf_mdev_set_vq_ready,
+	.get_vq_ready	= ifcvf_mdev_get_vq_ready,
+	.set_vq_num     = ifcvf_mdev_set_vq_num,
+	.set_vq_address = ifcvf_mdev_set_vq_address,
+	.kick_vq        = ifcvf_mdev_kick_vq,
+	.get_generation	= ifcvf_mdev_get_generation,
+	.get_device_id	= ifcvf_mdev_get_device_id,
+	.get_vendor_id	= ifcvf_mdev_get_vendor_id,
+	.get_vq_align	= ifcvf_mdev_get_vq_align,
+	.get_config	= ifcvf_mdev_get_config,
+	.set_config	= ifcvf_mdev_set_config,
+	.get_mdev_features = ifcvf_mdev_get_mdev_features,
+};
+
+static int ifcvf_init_msix(struct ifcvf_adapter *adapter)
+{
+	struct pci_dev *pdev = to_pci_dev(adapter->dev);
+	struct ifcvf_hw *vf = &adapter->vf;
+	int vector, i, ret, irq;
+
+	ret = pci_alloc_irq_vectors(pdev, IFCVF_MAX_INTR,
+				    IFCVF_MAX_INTR, PCI_IRQ_MSIX);
+	if (ret < 0) {
+		IFC_ERR(adapter->dev, "Failed to alloc irq vectors.\n");
+		return ret;
+	}
+
+	for (i = 0; i < IFCVF_MAX_QUEUE_PAIRS * 2; i++) {
+		vector = i + IFCVF_MSI_QUEUE_OFF;
+		irq = pci_irq_vector(pdev, vector);
+		ret = request_irq(irq, ifcvf_intr_handler, 0,
+				pci_name(pdev), &vf->vring[i]);
+		if (ret) {
+			IFC_ERR(adapter->dev,
+				"Failed to request irq for vq %d.\n", i);
+			return ret;
+		}
+	}
+
+	return 0;
+}
+
+static void ifcvf_destroy_adapter(struct ifcvf_adapter *adapter)
+{
+	struct ifcvf_hw *vf = IFC_PRIVATE_TO_VF(adapter);
+	struct pci_dev *pdev = to_pci_dev(adapter->dev);
+	int i, vector, irq;
+
+	for (i = 0; i < IFCVF_MAX_QUEUE_PAIRS * 2; i++) {
+		vector = i + IFCVF_MSI_QUEUE_OFF;
+		irq = pci_irq_vector(pdev, vector);
+		free_irq(irq, &vf->vring[i]);
+	}
+}
+
+static ssize_t name_show(struct kobject *kobj, struct device *dev, char *buf)
+{
+	const char *name = "vhost accelerator (virtio ring compatible)";
+
+	return sprintf(buf, "%s\n", name);
+}
+MDEV_TYPE_ATTR_RO(name);
+
+static ssize_t device_api_show(struct kobject *kobj, struct device *dev,
+			       char *buf)
+{
+	return sprintf(buf, "%s\n", VIRTIO_MDEV_DEVICE_API_STRING);
+}
+MDEV_TYPE_ATTR_RO(device_api);
+
+static ssize_t available_instances_show(struct kobject *kobj,
+					struct device *dev, char *buf)
+{
+	struct pci_dev *pdev;
+	struct ifcvf_adapter *adapter;
+
+	pdev = to_pci_dev(dev);
+	adapter = pci_get_drvdata(pdev);
+
+	return sprintf(buf, "%d\n", adapter->mdev_count);
+}
+
+MDEV_TYPE_ATTR_RO(available_instances);
+
+static ssize_t type_show(struct kobject *kobj,
+			struct device *dev, char *buf)
+{
+	return sprintf(buf, "%s\n", "net");
+}
+
+MDEV_TYPE_ATTR_RO(type);
+
+
+static struct attribute *mdev_types_attrs[] = {
+	&mdev_type_attr_name.attr,
+	&mdev_type_attr_device_api.attr,
+	&mdev_type_attr_available_instances.attr,
+	&mdev_type_attr_type.attr,
+	NULL,
+};
+
+static struct attribute_group mdev_type_group_virtio = {
+	.name  = "virtio_mdev",
+	.attrs = mdev_types_attrs,
+};
+
+static struct attribute_group mdev_type_group_vhost = {
+	.name  = "vhost_mdev",
+	.attrs = mdev_types_attrs,
+};
+
+static struct attribute_group *mdev_type_groups[] = {
+	&mdev_type_group_virtio,
+	&mdev_type_group_vhost,
+	NULL,
+};
+
+const struct attribute_group *mdev_dev_groups[] = {
+	NULL,
+};
+
+static int ifcvf_mdev_create(struct kobject *kobj, struct mdev_device *mdev)
+{
+	struct device *dev = mdev_parent_dev(mdev);
+	struct pci_dev *pdev = to_pci_dev(dev);
+	struct ifcvf_adapter *adapter = pci_get_drvdata(pdev);
+	int ret = 0;
+
+	mutex_lock(&adapter->mdev_lock);
+
+	if (adapter->mdev_count < IFCVF_MDEV_LIMIT) {
+		IFC_ERR(&pdev->dev,
+			"Can not create mdev, reached limitation %d.\n",
+			IFCVF_MDEV_LIMIT);
+		ret = -EINVAL;
+		goto out;
+	}
+
+	if (!strcmp(kobj->name, "ifcvf-virtio_mdev"))
+		mdev_set_virtio_ops(mdev, &ifc_mdev_ops);
+
+	if (!strcmp(kobj->name, "ifcvf-vhost_mdev"))
+		mdev_set_vhost_ops(mdev, &ifc_mdev_ops);
+
+	mdev_set_drvdata(mdev, adapter);
+	mdev_set_iommu_device(mdev_dev(mdev), dev);
+	adapter->mdev_count--;
+
+out:
+	mutex_unlock(&adapter->mdev_lock);
+	return ret;
+}
+
+static int ifcvf_mdev_remove(struct mdev_device *mdev)
+{
+	struct device *dev = mdev_parent_dev(mdev);
+	struct pci_dev *pdev = to_pci_dev(dev);
+	struct ifcvf_adapter *adapter = pci_get_drvdata(pdev);
+
+	mutex_lock(&adapter->mdev_lock);
+	adapter->mdev_count++;
+	mutex_unlock(&adapter->mdev_lock);
+
+	return 0;
+}
+
+static struct mdev_parent_ops ifcvf_mdev_fops = {
+	.owner			= THIS_MODULE,
+	.supported_type_groups	= mdev_type_groups,
+	.mdev_attr_groups	= mdev_dev_groups,
+	.create			= ifcvf_mdev_create,
+	.remove			= ifcvf_mdev_remove,
+};
+
+static int ifcvf_probe(struct pci_dev *pdev, const struct pci_device_id *id)
+{
+	struct device *dev = &pdev->dev;
+	struct ifcvf_adapter *adapter;
+	struct ifcvf_hw *vf;
+	int ret, i;
+
+	adapter = kzalloc(sizeof(struct ifcvf_adapter), GFP_KERNEL);
+
+	if (adapter == NULL) {
+		ret = -ENOMEM;
+		goto fail;
+	}
+
+	mutex_init(&adapter->mdev_lock);
+	adapter->mdev_count = IFCVF_MDEV_LIMIT;
+	adapter->dev = dev;
+	pci_set_drvdata(pdev, adapter);
+	ret = pci_enable_device(pdev);
+
+	if (ret) {
+		IFC_ERR(adapter->dev, "Failed to enable device.\n");
+		goto free_adapter;
+	}
+
+	ret = pci_request_regions(pdev, IFCVF_DRIVER_NAME);
+
+	if (ret) {
+		IFC_ERR(adapter->dev, "Failed to request MMIO region.\n");
+		goto disable_device;
+	}
+
+	pci_set_master(pdev);
+	ret = ifcvf_init_msix(adapter);
+
+	if (ret) {
+		IFC_ERR(adapter->dev, "Failed to initialize MSIX.\n");
+		goto free_msix;
+	}
+
+	vf = &adapter->vf;
+	
+	for (i = 0; i < IFCVF_PCI_MAX_RESOURCE; i++) {
+		vf->mem_resource[i].phys_addr = pci_resource_start(pdev, i);
+		vf->mem_resource[i].len = pci_resource_len(pdev, i);
+		if (!vf->mem_resource[i].len) {
+			vf->mem_resource[i].addr = NULL;
+			continue;
+		}
+
+		vf->mem_resource[i].addr = pci_iomap_range(pdev, i, 0,
+				vf->mem_resource[i].len);
+		if (!vf->mem_resource[i].addr) {
+			IFC_ERR(adapter->dev, "Failed to map IO resource %d\n",
+				i);
+			ret = -1;
+			goto free_msix;
+		}
+	}
+
+	if (ifcvf_init_hw(vf, pdev) < 0) {
+		ret = -1;
+		goto destroy_adapter;
+	}
+
+	ret = mdev_register_device(dev, &ifcvf_mdev_fops);
+
+	if (ret) {
+		IFC_ERR(adapter->dev,  "Failed to register mdev device\n");
+		goto destroy_adapter;
+	}
+
+	return 0;
+
+destroy_adapter:
+	ifcvf_destroy_adapter(adapter);
+free_msix:
+	pci_free_irq_vectors(pdev);
+	pci_release_regions(pdev);
+disable_device:
+	pci_disable_device(pdev);
+free_adapter:
+	kfree(adapter);
+fail:
+	return ret;
+}
+
+static void ifcvf_remove(struct pci_dev *pdev)
+{
+	struct ifcvf_adapter *adapter = pci_get_drvdata(pdev);
+	struct device *dev = &pdev->dev;
+	struct ifcvf_hw *vf;
+	int i;
+
+	mdev_unregister_device(dev);
+
+	vf = &adapter->vf;
+	for (i = 0; i < IFCVF_PCI_MAX_RESOURCE; i++) {
+		if (vf->mem_resource[i].addr) {
+			pci_iounmap(pdev, vf->mem_resource[i].addr);
+			vf->mem_resource[i].addr = NULL;
+		}
+	}
+
+	ifcvf_destroy_adapter(adapter);
+	pci_free_irq_vectors(pdev);
+	pci_release_regions(pdev);
+	pci_disable_device(pdev);
+	kfree(adapter);
+}
+
+static struct pci_device_id ifcvf_pci_ids[] = {
+	{ PCI_DEVICE_SUB(IFCVF_VENDOR_ID,
+			IFCVF_DEVICE_ID,
+			IFCVF_SUBSYS_VENDOR_ID,
+			IFCVF_SUBSYS_DEVICE_ID) },
+	{ 0 },
+};
+MODULE_DEVICE_TABLE(pci, ifcvf_pci_ids);
+
+static struct pci_driver ifcvf_driver = {
+	.name     = IFCVF_DRIVER_NAME,
+	.id_table = ifcvf_pci_ids,
+	.probe    = ifcvf_probe,
+	.remove   = ifcvf_remove,
+};
+
+static int __init ifcvf_init_module(void)
+{
+	int ret;
+
+	ret = pci_register_driver(&ifcvf_driver);
+	return ret;
+}
+
+static void __exit ifcvf_exit_module(void)
+{
+	pci_unregister_driver(&ifcvf_driver);
+}
+
+module_init(ifcvf_init_module);
+module_exit(ifcvf_exit_module);
+
+MODULE_LICENSE("GPL v2");
+MODULE_VERSION(VERSION_STRING);
+MODULE_AUTHOR(DRIVER_AUTHOR);
```
#### [PATCH v4 1/5] KVM: x86: Move memcache allocation to GFP_PGTABLE_USER
##### From: Christoffer Dall <christoffer.dall@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christoffer Dall <christoffer.dall@arm.com>
X-Patchwork-Id: 11228487
Return-Path: <SRS0=X2oT=Y5=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5E5D11850
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 Nov 2019 20:29:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 50F4F21D7D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 Nov 2019 20:29:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729524AbfKEU36 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 5 Nov 2019 15:29:58 -0500
Received: from foss.arm.com ([217.140.110.172]:59886 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725806AbfKEU35 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 5 Nov 2019 15:29:57 -0500
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 9213468D;
        Tue,  5 Nov 2019 12:29:56 -0800 (PST)
Received: from localhost (e113682-lin.copenhagen.arm.com [10.32.145.14])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 0018D3FE49;
        Tue,  5 Nov 2019 03:04:02 -0800 (PST)
From: Christoffer Dall <christoffer.dall@arm.com>
To: kvm@vger.kernel.org
Cc: kvmarm@lists.cs.columbia.edu, Christoffer Dall <christoffer.dall@arm.com>,
 James Hogan <jhogan@kernel.org>, Paolo Bonzini <pbonzini@redhat.com>,
	=?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Joerg Roedel <joro@8bytes.org>, Marc Zyngier <maz@kernel.org>,
 Paul Mackerras <paulus@ozlabs.org>,
 Christian Borntraeger <borntraeger@de.ibm.com>,
 Anshuman Khandual <anshuman.khandual@arm.com>,
 Suzuki K Poulose <suzuki.poulose@arm.com>, James Morse <james.morse@arm.com>,
 Julien Thierry <julien.thierry.kdev@gmail.com>,
 Sean Christopherson <sean.j.christopherson@intel.com>,
 Vitaly Kuznetsov <vkuznets@redhat.com>, Wanpeng Li <wanpengli@tencent.com>,
 Jim Mattson <jmattson@google.com>, Mike Rapoport <rppt@linux.ibm.com>
Subject: [PATCH v4 1/5] KVM: x86: Move memcache allocation to GFP_PGTABLE_USER
Date: Tue,  5 Nov 2019 12:03:53 +0100
Message-Id: <20191105110357.8607-2-christoffer.dall@arm.com>
X-Mailer: git-send-email 2.18.0
In-Reply-To: <20191105110357.8607-1-christoffer.dall@arm.com>
References: <20191105110357.8607-1-christoffer.dall@arm.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Recent commit 50f11a8a4620eee6b6831e69ab5d42456546d7d8 moved page table
allocations for both KVM and normal user page table allocations to
GFP_PGTABLE_USER in order to get __GFP_ACCOUNT for the page tables.

However, while KVM on other architectures such as arm64 were included in
this change, curiously KVM on x86 was not.

Currently, KVM on x86 uses kmem_cache_zalloc(GFP_KERNEL_ACCOUNT) for
kmem_cache-based allocations, which expands in the following way:
  kmem_cache_zalloc(..., GFP_KERNEL_ACCOUNT) =>
  kmem_cache_alloc(..., GFP_KERNEL_ACCOUNT | __GFP_ZERO) =>
  kmem_cache_alloc(..., GFP_KERNEL | __GFP_ACCOUNT | __GFP_ZERO)

It so happens that GFP_PGTABLE_USER expands as:
  GFP_PGTABLE_USER =>
  (GFP_PGTABLE_KERNEL | __GFP_ACCOUNT) =>
  ((GFP_KERNEL | __GFP_ZERO) | __GFP_ACCOUNT) =>
  (GFP_KERNEL | __GFP_ACCOUNT | __GFP_ZERO)

Which means that we can replace the current KVM on x86 call as:
-  obj = kmem_cache_zalloc(base_cache, GFP_KERNEL_ACCOUNT);
+  obj = kmem_cache_alloc(base_cache, GFP_PGTABLE_USER);

For the single page cache topup allocation, KVM on x86 currently uses
__get_free_page(GFP_KERNEL_ACCOUNT).  It seems to me that is equivalent
to the above, except that the allocated page is not guaranteed to be
zero (unless I missed the place where __get_free_page(!__GFP_ZERO) is
still guaranteed to be zeroed.  It seems natural (and in fact desired)
to have both topup functions implement the same expectations towards the
caller, and we therefore move to GFP_PGTABLE_USER here as well.

This will make it easier to unify the memchace implementation between
architectures.

Signed-off-by: Christoffer Dall <christoffer.dall@arm.com>
---
 arch/x86/kvm/mmu.c | 5 +++--
 1 file changed, 3 insertions(+), 2 deletions(-)

```
#### [PATCH kvm-unit-tests] svm: Verify a pending interrupt queued before entering the guest is not lost
##### From: Cathy Avery <cavery@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Cathy Avery <cavery@redhat.com>
X-Patchwork-Id: 11228105
Return-Path: <SRS0=X2oT=Y5=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DC88A139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 Nov 2019 15:12:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id BAE0B21929
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 Nov 2019 15:12:38 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="ZZOis8xC"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2389015AbfKEPMh (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 5 Nov 2019 10:12:37 -0500
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:28347 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1727889AbfKEPMh (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 5 Nov 2019 10:12:37 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1572966756;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=OlkoVdflSMC+hZrDHTdU7MNDmd7YVwliCib2kuv9TNg=;
        b=ZZOis8xCVhpqZGrP7W5WooBxB3w5CLlvIUtpBBINt2d++aNIYQWwrEvcCqvAnngFH1Tgk0
        /wiqH/jFal+2aPuJdS+UfPqZTFS2LCZLwcHD13GSHYzN4RoGIPDZ+7yUWFFM7nslrrOfl9
        PYrr7ennUwjLPyw3/jZ+lReazuYzaHg=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-13-_6cQfoz1MrCDdL_Xh9BPSw-1; Tue, 05 Nov 2019 10:12:35 -0500
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 4C3BC1005500
        for <kvm@vger.kernel.org>; Tue,  5 Nov 2019 15:12:34 +0000 (UTC)
Received: from localhost.localdomain.com (ovpn-120-170.rdu2.redhat.com
 [10.10.120.170])
        by smtp.corp.redhat.com (Postfix) with ESMTP id CA7975C3F8;
        Tue,  5 Nov 2019 15:12:33 +0000 (UTC)
From: Cathy Avery <cavery@redhat.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com
Subject: [PATCH kvm-unit-tests] svm: Verify a pending interrupt queued before
 entering the guest is not lost
Date: Tue,  5 Nov 2019 10:12:34 -0500
Message-Id: <20191105151234.28160-1-cavery@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
X-MC-Unique: _6cQfoz1MrCDdL_Xh9BPSw-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch is based on Liran Aloni <liran.alon@oracle.com>
commit fd056f5b89ac for vmx.

The test configures VMCB to intercept external-interrupts and then
queues an interrupt by disabling interrupts and issue a self-IPI.
At this point, we enter guest and we expect CPU to immediately exit
guest on external-interrupt. To complete the test, we then re-enable
interrupts, verify interrupt is dispatched and re-enter guest to verify
it completes execution.

Signed-off-by: Cathy Avery <cavery@redhat.com>
---
 x86/svm.c | 93 +++++++++++++++++++++++++++++++++++++++++++++++++++++++
 1 file changed, 93 insertions(+)

```
#### [PATCH] KVM: X86: Dynamically allocating MSR number lists(msrs_to_save[], emulated_msrs[], msr_based_features[])
##### From: Chenyi Qiang <chenyi.qiang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Chenyi Qiang <chenyi.qiang@intel.com>
X-Patchwork-Id: 11227327
Return-Path: <SRS0=X2oT=Y5=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BAE181390
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 Nov 2019 09:20:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 9901821D6C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 Nov 2019 09:20:33 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730574AbfKEJUa (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 5 Nov 2019 04:20:30 -0500
Received: from mga01.intel.com ([192.55.52.88]:41924 "EHLO mga01.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727093AbfKEJUa (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 5 Nov 2019 04:20:30 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga004.jf.intel.com ([10.7.209.38])
  by fmsmga101.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 05 Nov 2019 01:20:27 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.68,270,1569308400";
   d="scan'208";a="353093772"
Received: from chenyi-pc.sh.intel.com ([10.239.159.72])
  by orsmga004.jf.intel.com with ESMTP; 05 Nov 2019 01:20:25 -0800
From: Chenyi Qiang <chenyi.qiang@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Sean Christopherson <sean.j.christopherson@intel.com>,
 Vitaly Kuznetsov <vkuznets@redhat.com>, Jim Mattson <jmattson@google.com>,
 Joerg Roedel <joro@8bytes.org>
Cc: Xiaoyao Li <xiaoyao.li@intel.com>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, stable@vger.kernel.org
Subject: [PATCH] KVM: X86: Dynamically allocating MSR number
 lists(msrs_to_save[], emulated_msrs[], msr_based_features[])
Date: Tue,  5 Nov 2019 17:20:31 +0800
Message-Id: <20191105092031.8064-1-chenyi.qiang@intel.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The three msr number lists(msrs_to_save[], emulated_msrs[] and
msr_based_features[]) are global arrays of kvm.ko, which are
initialized/adjusted (copy supported MSRs forward to override the
unsupported MSRs) when installing kvm-{intel,amd}.ko, but it doesn't
reset these three arrays to their initial value when uninstalling
kvm-{intel,amd}.ko. Thus, at the next installation, kvm-{intel,amd}.ko
will initialize the modified arrays with some MSRs lost and some MSRs
duplicated.

So allocate and initialize these three MSR number lists dynamically when
installing kvm-{intel,amd}.ko and free them when uninstalling.

Cc: stable@vger.kernel.org
Reviewed-by: Xiaoyao Li <xiaoyao.li@intel.com>
Signed-off-by: Chenyi Qiang <chenyi.qiang@intel.com>
---
 arch/x86/kvm/x86.c | 86 ++++++++++++++++++++++++++++++----------------
 1 file changed, 57 insertions(+), 29 deletions(-)

```
#### [PATCH V8 1/6] mdev: class id support
##### From: Jason Wang <jasowang@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 11227371
Return-Path: <SRS0=X2oT=Y5=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9BB771850
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 Nov 2019 09:34:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 656A921D7D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 Nov 2019 09:34:35 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Z7LJr10L"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388098AbfKEJee (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 5 Nov 2019 04:34:34 -0500
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:33953 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S2387918AbfKEJee (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 5 Nov 2019 04:34:34 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1572946472;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=GL0EV7S/CVbjypEmKRQzwBPJlNCKfeApryMypohNTFY=;
        b=Z7LJr10LI2LY1i9OhgQI3zhxx3FlneYIgthMljE9pOWWmzWiLCa2+2g773Ji4+Z4Tc+5G7
        Rr5Gih1NyURBy7REfJt4UniU4cumry3tYT7sCc5CWyibglbEIIE24S+9G/scNFAhJZS/xY
        4uM/E56WAPVCfcSVfDedN32cl023OA4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-426-1iW_xGK-NTulqHvSRxjzDg-1; Tue, 05 Nov 2019 04:34:29 -0500
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 503561800D4A;
        Tue,  5 Nov 2019 09:34:25 +0000 (UTC)
Received: from jason-ThinkPad-X1-Carbon-6th.redhat.com
 (ovpn-12-252.pek2.redhat.com [10.72.12.252])
        by smtp.corp.redhat.com (Postfix) with ESMTP id A2ED65C1D8;
        Tue,  5 Nov 2019 09:33:42 +0000 (UTC)
From: Jason Wang <jasowang@redhat.com>
To: kvm@vger.kernel.org, linux-s390@vger.kernel.org,
        linux-kernel@vger.kernel.org, dri-devel@lists.freedesktop.org,
        intel-gfx@lists.freedesktop.org,
        intel-gvt-dev@lists.freedesktop.org, kwankhede@nvidia.com,
        alex.williamson@redhat.com, mst@redhat.com, tiwei.bie@intel.com
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        cohuck@redhat.com, maxime.coquelin@redhat.com,
        cunming.liang@intel.com, zhihong.wang@intel.com,
        rob.miller@broadcom.com, xiao.w.wang@intel.com,
        haotian.wang@sifive.com, zhenyuw@linux.intel.com,
        zhi.a.wang@intel.com, jani.nikula@linux.intel.com,
        joonas.lahtinen@linux.intel.com, rodrigo.vivi@intel.com,
        airlied@linux.ie, daniel@ffwll.ch, farman@linux.ibm.com,
        pasic@linux.ibm.com, sebott@linux.ibm.com, oberpar@linux.ibm.com,
        heiko.carstens@de.ibm.com, gor@linux.ibm.com,
        borntraeger@de.ibm.com, akrowiak@linux.ibm.com,
        freude@linux.ibm.com, lingshan.zhu@intel.com, idos@mellanox.com,
        eperezma@redhat.com, lulu@redhat.com, parav@mellanox.com,
        christophe.de.dinechin@gmail.com, kevin.tian@intel.com,
        stefanha@redhat.com, Jason Wang <jasowang@redhat.com>
Subject: [PATCH V8 1/6] mdev: class id support
Date: Tue,  5 Nov 2019 17:32:35 +0800
Message-Id: <20191105093240.5135-2-jasowang@redhat.com>
In-Reply-To: <20191105093240.5135-1-jasowang@redhat.com>
References: <20191105093240.5135-1-jasowang@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
X-MC-Unique: 1iW_xGK-NTulqHvSRxjzDg-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Mdev bus only supports vfio driver right now, so it doesn't implement
match method. But in the future, we may add drivers other than vfio,
the first driver could be virtio-mdev. This means we need to add
device class id support in bus match method to pair the mdev device
and mdev driver correctly.

So this patch adds id_table to mdev_driver and class_id for mdev
device with the match method for mdev bus.

Reviewed-by: Parav Pandit <parav@mellanox.com>
Signed-off-by: Jason Wang <jasowang@redhat.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---
 .../driver-api/vfio-mediated-device.rst       |  5 ++++
 drivers/gpu/drm/i915/gvt/kvmgt.c              |  1 +
 drivers/s390/cio/vfio_ccw_ops.c               |  1 +
 drivers/s390/crypto/vfio_ap_ops.c             |  1 +
 drivers/vfio/mdev/mdev_core.c                 | 17 +++++++++++++
 drivers/vfio/mdev/mdev_driver.c               | 25 +++++++++++++++++++
 drivers/vfio/mdev/mdev_private.h              |  1 +
 drivers/vfio/mdev/vfio_mdev.c                 |  6 +++++
 include/linux/mdev.h                          |  8 ++++++
 include/linux/mod_devicetable.h               |  8 ++++++
 samples/vfio-mdev/mbochs.c                    |  1 +
 samples/vfio-mdev/mdpy.c                      |  1 +
 samples/vfio-mdev/mtty.c                      |  1 +
 13 files changed, 76 insertions(+)

```
#### [PATCH v13 1/6] mm: Adjust shuffle code to allow for future coalescing
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Duyck <alexander.duyck@gmail.com>
X-Patchwork-Id: 11228831
Return-Path: <SRS0=X2oT=Y5=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 646141515
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 Nov 2019 22:02:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 3F82121929
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 Nov 2019 22:02:13 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="bFXSnYX0"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730279AbfKEWCK (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 5 Nov 2019 17:02:10 -0500
Received: from mail-pl1-f194.google.com ([209.85.214.194]:46690 "EHLO
        mail-pl1-f194.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729747AbfKEWCJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 5 Nov 2019 17:02:09 -0500
Received: by mail-pl1-f194.google.com with SMTP id l4so5081695plt.13;
        Tue, 05 Nov 2019 14:02:08 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=subject:from:to:cc:date:message-id:in-reply-to:references
         :user-agent:mime-version:content-transfer-encoding;
        bh=i4Pj4oR+V08pVNadxlEGqPfJoWSfrMh8VdQBKoieZtk=;
        b=bFXSnYX0KHMaqYAudxt/ZKAOjXg7f/AI3kpdfKGV3E4LutcsiZavdrL7VwF/UZpw+6
         0dK2FFZHJid5YtXeWDy0lXwQGG9q3YFlnXDoXO6YWvFCVMOflfaoLQ5GrJqcvC78k4U5
         IRPNbdabq4GFbKoqIx8jB7U5Ldn+mn2YgJuly2ja01tycsTQhqble86uQQUPp/YKH3CI
         1qTG2s4F5kM/z9dITv7g1cSWXY60l8T4M8jKi9CVPNzTNKkqjSBS/gzUHZ6DRTPihBln
         XzgFNer86hX4lzUApIj904pj6TTz5TDWT6MEGFVqWAuBb/ItXw7HjWfgwjS1tYSChvWL
         ztEQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:subject:from:to:cc:date:message-id:in-reply-to
         :references:user-agent:mime-version:content-transfer-encoding;
        bh=i4Pj4oR+V08pVNadxlEGqPfJoWSfrMh8VdQBKoieZtk=;
        b=aveS1OzuBArrvho5KcFI9YlhTPcr2S1wNTEyrvzIZDPAvABzKGRVAGYCSUIhCvAcJJ
         HRSWJLhUtnamnKXbOoYjhRV2195tYDS5ZKWlSe/0WAi3mawvQZYhFRs8Nq9zzEO0U7ob
         6Vm2Ve65Yxr2/7cC4DTAVBgTlF/uRuAwQuzJZ3vmoRdCbx8QIiVNAunO2W+xSvVwdK1Q
         VET88x4PFRb8qwKCsG0ktsEgkjpsh1CNe9/BfDXQS0kiULf5QRTZX2uzftGmEzZAswuu
         N38zUmZa3jnSqrHQWGCkNyyI7QBGpZZ8JwzBeqEQQuxVELg8P5PM3BH3+ueMq2Xq2Wbd
         KA5Q==
X-Gm-Message-State: APjAAAXP272+Z+z422wOFWXDChnZn0Gsz0eydukZ9LbLT+CjAQ1Ws62+
        wkmoM0fB7cEmroE6c7h/VFg=
X-Google-Smtp-Source: 
 APXvYqzKjudW8fUnUrJWRHusKNShU6INWXSkltd7Te9vyU9aGAqlLdgBCwH1s68upZJCTyo9wR5Bgg==
X-Received: by 2002:a17:902:848e:: with SMTP id
 c14mr4241977plo.62.1572991328117;
        Tue, 05 Nov 2019 14:02:08 -0800 (PST)
Received: from localhost.localdomain ([2001:470:b:9c3:9e5c:8eff:fe4f:f2d0])
        by smtp.gmail.com with ESMTPSA id
 a16sm1749665pfc.56.2019.11.05.14.02.07
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Tue, 05 Nov 2019 14:02:07 -0800 (PST)
Subject: [PATCH v13 1/6] mm: Adjust shuffle code to allow for future
 coalescing
From: Alexander Duyck <alexander.duyck@gmail.com>
To: kvm@vger.kernel.org, mst@redhat.com, linux-kernel@vger.kernel.org,
        willy@infradead.org, mhocko@kernel.org, linux-mm@kvack.org,
        akpm@linux-foundation.org, mgorman@techsingularity.net,
        vbabka@suse.cz
Cc: yang.zhang.wz@gmail.com, nitesh@redhat.com, konrad.wilk@oracle.com,
        david@redhat.com, pagupta@redhat.com, riel@surriel.com,
        lcapitulino@redhat.com, dave.hansen@intel.com,
        wei.w.wang@intel.com, aarcange@redhat.com, pbonzini@redhat.com,
        dan.j.williams@intel.com, alexander.h.duyck@linux.intel.com,
        osalvador@suse.de
Date: Tue, 05 Nov 2019 14:02:07 -0800
Message-ID: <20191105220207.15144.8826.stgit@localhost.localdomain>
In-Reply-To: <20191105215940.15144.65968.stgit@localhost.localdomain>
References: <20191105215940.15144.65968.stgit@localhost.localdomain>
User-Agent: StGit/0.17.1-dirty
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Alexander Duyck <alexander.h.duyck@linux.intel.com>

Move the head/tail adding logic out of the shuffle code and into the
__free_one_page function since ultimately that is where it is really
needed anyway. By doing this we should be able to reduce the overhead
and can consolidate all of the list addition bits in one spot.

Acked-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Dan Williams <dan.j.williams@intel.com>
Signed-off-by: Alexander Duyck <alexander.h.duyck@linux.intel.com>
---
 include/linux/mmzone.h |   12 --------
 mm/page_alloc.c        |   71 ++++++++++++++++++++++++++++--------------------
 mm/shuffle.c           |   12 ++++----
 mm/shuffle.h           |    6 ++++
 4 files changed, 54 insertions(+), 47 deletions(-)

```
#### [PATCH RFC] KVM: x86: tell guests if the exposed SMT topology is trustworthy
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11228261
Return-Path: <SRS0=X2oT=Y5=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 09D5D139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 Nov 2019 16:17:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id DB2ED2087E
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 Nov 2019 16:17:47 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2390141AbfKEQRq (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 5 Nov 2019 11:17:46 -0500
Received: from mx1.redhat.com ([209.132.183.28]:5413 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2390007AbfKEQRo (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 5 Nov 2019 11:17:44 -0500
Received: from mail-wm1-f70.google.com (mail-wm1-f70.google.com
 [209.85.128.70])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-GCM-SHA256 (128/128 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 0083236898
        for <kvm@vger.kernel.org>; Tue,  5 Nov 2019 16:17:42 +0000 (UTC)
Received: by mail-wm1-f70.google.com with SMTP id i23so7849776wmb.3
        for <kvm@vger.kernel.org>; Tue, 05 Nov 2019 08:17:42 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=Bl1aLROn7TtgvMqB5D32TvDdvphYW0zF7b8CCLtoaP0=;
        b=m0+fNZ96cGQzFBgmNhwe1dD2N6ngOxx1AtFP1BjcJUdoRyLGKzefS+XQpacvdtincZ
         qfxPsPZYZJLIPGWGIu+CMVk4SO+G3hitJO9RRhs9FTUCPNUEkt3RJOhx5KqkFc/jBgzk
         LEzXfPNeLWfQY0UiCxBPQLf0lJH4cdTojrjb7W3Oyk2kIh1ze+XKRul1MRSuNMNKrJp1
         oUulZKd+1bRUgz8T24oRpLuePdxkFKSmjV+7jYoe8DRuBfOaXsnD1u/GFCgJWNOTbmX+
         xCWYyVNt5s/3Z2Jk/rbg6aV0+urlxDePeMD3ldKXVbQAXo05xbA3w9h5k2Cm5f1TiHTu
         yw5g==
X-Gm-Message-State: APjAAAWaGlI2oldJq5FqonpETTJsYpKleAgmYbNGiH+eeqA8jMuTF9z+
        gfpPZkwrln3qGyq3U482SOqEzbFMnglMtrTx5q155658szjTlrRcJ4c9MsaCpvmad1DwL1afxhR
        ofOVHpwn3PO9F
X-Received: by 2002:a5d:5284:: with SMTP id c4mr11058206wrv.376.1572970661249;
        Tue, 05 Nov 2019 08:17:41 -0800 (PST)
X-Google-Smtp-Source: 
 APXvYqxNKHp7hctL2Eiz7XQJJw1P0Hq4TMFa85ILfamcF3qBzHreXyW4j2okrurW+bkcNpSiMgZORQ==
X-Received: by 2002:a5d:5284:: with SMTP id c4mr11058116wrv.376.1572970660030;
        Tue, 05 Nov 2019 08:17:40 -0800 (PST)
Received: from vitty.brq.redhat.com (nat-pool-brq-t.redhat.com.
 [213.175.37.10])
        by smtp.gmail.com with ESMTPSA id
 e27sm1569410wra.21.2019.11.05.08.17.38
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 05 Nov 2019 08:17:39 -0800 (PST)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org
Cc: x86@kernel.org, Paolo Bonzini <pbonzini@redhat.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Jim Mattson <jmattson@google.com>,
        Liran Alon <liran.alon@oracle.com>,
        linux-kernel@vger.kernel.org, "H. Peter Anvin" <hpa@zytor.com>,
        "Peter Zijlstra (Intel)" <peterz@infradead.org>
Subject: [PATCH RFC] KVM: x86: tell guests if the exposed SMT topology is
 trustworthy
Date: Tue,  5 Nov 2019 17:17:37 +0100
Message-Id: <20191105161737.21395-1-vkuznets@redhat.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Virtualized guests may pick a different strategy to mitigate hardware
vulnerabilities when it comes to hyper-threading: disable SMT completely,
use core scheduling, or, for example, opt in for STIBP. Making the
decision, however, requires an extra bit of information which is currently
missing: does the topology the guest see match hardware or if it is 'fake'
and two vCPUs which look like different cores from guest's perspective can
actually be scheduled on the same physical core. Disabling SMT or doing
core scheduling only makes sense when the topology is trustworthy.

Add two feature bits to KVM: KVM_FEATURE_TRUSTWORTHY_SMT with the meaning
that KVM_HINTS_TRUSTWORTHY_SMT bit answers the question if the exposed SMT
topology is actually trustworthy. It would, of course, be possible to get
away with a single bit (e.g. 'KVM_FEATURE_FAKE_SMT') and not lose backwards
compatibility but the current approach looks more straightforward.

There were some offline discussions on whether this new feature bit should
be complemented with a 're-enlightenment' mechanism for live migration (so
it can change in guest's lifetime) but it doesn't seem to be very
practical: what a sane guest is supposed to do if it's told that SMT
topology is about to become fake other than kill itself? Also, it seems to
make little sense to do e.g. CPU pinning on the source but not on the
destination.

There is also one additional piece of the information missing. A VM can be
sharing physical cores with other VMs (or other userspace tasks on the
host) so does KVM_FEATURE_TRUSTWORTHY_SMT imply that it's not the case or
not? It is unclear if this changes anything and can probably be left out
of scope (just don't do that).

Similar to the already existent 'NoNonArchitecturalCoreSharing' Hyper-V
enlightenment, the default value of KVM_HINTS_TRUSTWORTHY_SMT is set to
!cpu_smt_possible(). KVM userspace is thus supposed to pass it to guest's
CPUIDs in case it is '1' (meaning no SMT on the host at all) or do some
extra work (like CPU pinning and exposing the correct topology) before
passing '1' to the guest.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 Documentation/virt/kvm/cpuid.rst     | 27 +++++++++++++++++++--------
 arch/x86/include/uapi/asm/kvm_para.h |  2 ++
 arch/x86/kvm/cpuid.c                 |  7 ++++++-
 3 files changed, 27 insertions(+), 9 deletions(-)

```
#### [kvm-unit-tests PATCH 1/2] s390x: Add CR save area
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11228269
Return-Path: <SRS0=X2oT=Y5=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9554713BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 Nov 2019 16:29:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7E64121929
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 Nov 2019 16:29:47 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2390163AbfKEQ3q (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 5 Nov 2019 11:29:46 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:8358 "EHLO
        mx0b-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S2390123AbfKEQ3q (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 5 Nov 2019 11:29:46 -0500
Received: from pps.filterd (m0127361.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 xA5GQ7xO068138
        for <kvm@vger.kernel.org>; Tue, 5 Nov 2019 11:29:45 -0500
Received: from e06smtp03.uk.ibm.com (e06smtp03.uk.ibm.com [195.75.94.99])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2w14m4kd63-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Tue, 05 Nov 2019 11:29:43 -0500
Received: from localhost
        by e06smtp03.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Tue, 5 Nov 2019 16:29:03 -0000
Received: from b06cxnps3074.portsmouth.uk.ibm.com (9.149.109.194)
        by e06smtp03.uk.ibm.com (192.168.101.133) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Tue, 5 Nov 2019 16:29:00 -0000
Received: from d06av24.portsmouth.uk.ibm.com (mk.ibm.com [9.149.105.60])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id xA5GSxlh32374886
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 5 Nov 2019 16:28:59 GMT
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 12E4542042;
        Tue,  5 Nov 2019 16:28:59 +0000 (GMT)
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 59EAE42049;
        Tue,  5 Nov 2019 16:28:58 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.152.224.131])
        by d06av24.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue,  5 Nov 2019 16:28:58 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, thuth@redhat.com, david@redhat.com
Subject: [kvm-unit-tests PATCH 1/2] s390x: Add CR save area
Date: Tue,  5 Nov 2019 11:28:27 -0500
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20191105162828.2490-1-frankja@linux.ibm.com>
References: <20191105162828.2490-1-frankja@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 19110516-0012-0000-0000-00000360F329
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19110516-0013-0000-0000-0000219C4D2A
Message-Id: <20191105162828.2490-2-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-11-05_06:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=999 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1908290000 definitions=main-1911050135
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If we run with DAT enabled and do a reset, we need to save the CRs to
backup our ASCEs on a diag308 for example.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
---
 lib/s390x/asm-offsets.c  | 2 +-
 lib/s390x/asm/arch_def.h | 4 ++--
 lib/s390x/interrupt.c    | 4 ++--
 lib/s390x/smp.c          | 2 +-
 s390x/cstart64.S         | 9 ++++++---
 5 files changed, 12 insertions(+), 9 deletions(-)

```
#### [PATCH v3 1/2] x86/Kconfig: Rename UMIP config parameterThread-Topic: [PATCH v3 1/2] x86/Kconfig: Rename UMIP config parameter
##### From: "Moger, Babu" <Babu.Moger@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Moger, Babu" <babu.moger@amd.com>
X-Patchwork-Id: 11228755
Return-Path: <SRS0=X2oT=Y5=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6AE59139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 Nov 2019 21:25:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 3CAA121929
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 Nov 2019 21:25:41 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="qsHpgIcG"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729985AbfKEVZh (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 5 Nov 2019 16:25:37 -0500
Received: from mail-eopbgr680076.outbound.protection.outlook.com
 ([40.107.68.76]:15246
        "EHLO NAM04-BN3-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1729976AbfKEVZh (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 5 Nov 2019 16:25:37 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=SDOLt9GGp4T0AU9m9ux0B4sIyMha04S7zuHk50o8vZL9/N6NwAGtgN+lfBIv5Exp+xhbnP5QeY/MlkOgvpS6VqlOqrEqvxNUO1RNNzkerUJEPLoltnXo+1UQ9vz1o+//c9U0MQ4hvmTuRPVM58wONz5OPW3n+Tn8gWCiPn4Rx52GdNXpM27y218zAzgp56HiPTNO5D87JS0ds5E18oeXDPPNx0PgmshMlNEWzTCimJPDLZizi1yBTTcslBXUoFv+HdSXx0yjfEy8pNqonsK4mvl75rUsXBWBk8l1Q9c6TlqPP9/ibxA6odDISpg8VYyiRdztEA6+BN4CyttC/8Yz/Q==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=UHaVTCAPAa2PXuzAYcJxBwSPmQecCgZXVdVUs4LVvF0=;
 b=kcnCd1ajDKo9gVHRE/Sy90anVKf6fZifKrvgKWPgoX4WIZWk0BK+8FUsoRr6BIYsjDOaBL3SWOLkn0WIwsnYiYywM8wVtzmHpiRXYn7aEXvmRoQ9vdIWxi3HR0RfmTu6MeC8OF8wbFvxCpNjtcFgYVbasFcfv52Nc67lyVdURXZ/faX7PIpVFg4ei1u77rfXecLS+ounty4vFR5Iu/kGEQQfT5OVfl1JlWgKef/23NAIKYxu93mfksxn3iXp9wpU34/AKKTbCPkfNiXY5HgEe5whPmIqiSK6y4/zWKssqiRvj6a/9MaAB6CamMdfyyB4aoV8hagPmMrzseMMKA4taw==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=UHaVTCAPAa2PXuzAYcJxBwSPmQecCgZXVdVUs4LVvF0=;
 b=qsHpgIcG6lMqZSQ4C3gfoHyORO1w0UNB7y96WH3dg2i84qemj4kuxuFUoG4jS4sz1mmcg04V7cfuIlIUJFC7YYCT0G7vaFTzRCh4KAqZdigymynININPZq7e9I2XbLKJZj2Lri+vgQJXRa7ppaNkpyn7IaW53mi5Z0RgHMhzTXE=
Received: from DM5PR12MB2471.namprd12.prod.outlook.com (52.132.141.138) by
 DM5PR12MB1195.namprd12.prod.outlook.com (10.168.240.14) with Microsoft SMTP
 Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.2408.24; Tue, 5 Nov 2019 21:25:32 +0000
Received: from DM5PR12MB2471.namprd12.prod.outlook.com
 ([fe80::c5a3:6a2e:8699:1999]) by DM5PR12MB2471.namprd12.prod.outlook.com
 ([fe80::c5a3:6a2e:8699:1999%6]) with mapi id 15.20.2408.024; Tue, 5 Nov 2019
 21:25:32 +0000
From: "Moger, Babu" <Babu.Moger@amd.com>
To: "tglx@linutronix.de" <tglx@linutronix.de>,
        "mingo@redhat.com" <mingo@redhat.com>,
        "bp@alien8.de" <bp@alien8.de>, "hpa@zytor.com" <hpa@zytor.com>,
        "pbonzini@redhat.com" <pbonzini@redhat.com>,
        "rkrcmar@redhat.com" <rkrcmar@redhat.com>,
        "sean.j.christopherson@intel.com" <sean.j.christopherson@intel.com>,
        "vkuznets@redhat.com" <vkuznets@redhat.com>,
        "wanpengli@tencent.com" <wanpengli@tencent.com>,
        "jmattson@google.com" <jmattson@google.com>
CC: "x86@kernel.org" <x86@kernel.org>,
        "joro@8bytes.org" <joro@8bytes.org>,
        "Moger, Babu" <Babu.Moger@amd.com>,
        "luto@kernel.org" <luto@kernel.org>,
        "zohar@linux.ibm.com" <zohar@linux.ibm.com>,
        "yamada.masahiro@socionext.com" <yamada.masahiro@socionext.com>,
        "nayna@linux.ibm.com" <nayna@linux.ibm.com>,
        "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>,
        "kvm@vger.kernel.org" <kvm@vger.kernel.org>,
        "zohar@linux.ibm.com" <zohar@linux.ibm.com>,
        "yamada.masahiro@socionext.com" <yamada.masahiro@socionext.com>,
        "ebiederm@xmission.com" <ebiederm@xmission.com>,
        "ricardo.neri-calderon@linux.intel.com"
        <ricardo.neri-calderon@linux.intel.com>,
        "bshanks@codeweavers.com" <bshanks@codeweavers.com>
Subject: [PATCH v3 1/2] x86/Kconfig: Rename UMIP config parameter
Thread-Topic: [PATCH v3 1/2] x86/Kconfig: Rename UMIP config parameter
Thread-Index: AQHVlB+O3ASEuWoCTkuU8z7yyrBiRA==
Date: Tue, 5 Nov 2019 21:25:32 +0000
Message-ID: <157298912544.17462.2018334793891409521.stgit@naples-babu.amd.com>
References: <157298900783.17462.2778215498449243912.stgit@naples-babu.amd.com>
In-Reply-To: 
 <157298900783.17462.2778215498449243912.stgit@naples-babu.amd.com>
Accept-Language: en-US
Content-Language: en-US
X-MS-Has-Attach: 
X-MS-TNEF-Correlator: 
x-clientproxiedby: SN6PR04CA0059.namprd04.prod.outlook.com
 (2603:10b6:805:2a::36) To DM5PR12MB2471.namprd12.prod.outlook.com
 (2603:10b6:4:b5::10)
authentication-results: spf=none (sender IP is )
 smtp.mailfrom=Babu.Moger@amd.com;
x-ms-exchange-messagesentrepresentingtype: 1
x-originating-ip: [165.204.78.2]
x-ms-publictraffictype: Email
x-ms-office365-filtering-ht: Tenant
x-ms-office365-filtering-correlation-id: f1b24793-9b72-4653-0924-08d76236b06a
x-ms-traffictypediagnostic: DM5PR12MB1195:
x-ms-exchange-transport-forked: True
x-microsoft-antispam-prvs: 
 <DM5PR12MB1195DD36483FF76316E65DE1957E0@DM5PR12MB1195.namprd12.prod.outlook.com>
x-ms-oob-tlc-oobclassifiers: OLM:6790;
x-forefront-prvs: 0212BDE3BE
x-forefront-antispam-report: 
 SFV:NSPM;SFS:(10009020)(4636009)(39860400002)(396003)(376002)(366004)(136003)(346002)(199004)(189003)(2201001)(54906003)(110136005)(8676002)(7416002)(103116003)(305945005)(81156014)(81166006)(66946007)(478600001)(25786009)(66556008)(64756008)(99286004)(66476007)(7736002)(316002)(26005)(2501003)(3846002)(102836004)(52116002)(6116002)(6436002)(6506007)(386003)(86362001)(66446008)(8936002)(2906002)(76176011)(14454004)(71200400001)(71190400001)(446003)(256004)(6512007)(476003)(486006)(186003)(4326008)(11346002)(14444005)(5660300002)(6486002)(66066001)(921003)(1121003);DIR:OUT;SFP:1101;SCL:1;SRVR:DM5PR12MB1195;H:DM5PR12MB2471.namprd12.prod.outlook.com;FPR:;SPF:None;LANG:en;PTR:InfoNoRecords;A:1;MX:1;
received-spf: None (protection.outlook.com: amd.com does not designate
 permitted sender hosts)
x-ms-exchange-senderadcheck: 1
x-microsoft-antispam: BCL:0;
x-microsoft-antispam-message-info: 
 ClSbpkyoYOR8wv0hOslz+teUZvAaJ0bhbL1mAd/teMgxh4jPhn+muqf7IvBt/MB8AVjhZx/7rzk3wNBVTnvJcx8bnXzUSeoHRYB8kEMsMMWKEaFlLFv1ucYDavJZpBzcBxlzcYF4YrX6kSmAdCFWZo4P7laEebnnx4w5qwpB8rGQEI5zfJfbVRHAfZLxPWCVKDD/FybvamVJpoZMOuWgYnMWJU2W0ztnEy32wlQsm2ioMW0XexLak2Fq2g5L4He4YbQwvtNSntSkB5hUu2Yti+NlZuRecHm5ZSKIdoyRFWufqR5N+F1YQZmkh5lUNQgezlrofL/kOdiV4LwY0c/PHUOeCeOBkScZjlLo/2xaKovHR4FWL4B4+iS64xBRx8h0lLN9FckzjKypD6P4hhVEDtqnLNLuytDIWHlqgKjNC20yhrSrTvSaHLUV6CA2yhCO
Content-ID: <BB5CA5287769514C809EE01D42582920@namprd12.prod.outlook.com>
MIME-Version: 1.0
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 f1b24793-9b72-4653-0924-08d76236b06a
X-MS-Exchange-CrossTenant-originalarrivaltime: 05 Nov 2019 21:25:32.6178
 (UTC)
X-MS-Exchange-CrossTenant-fromentityheader: Hosted
X-MS-Exchange-CrossTenant-id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-mailboxtype: HOSTED
X-MS-Exchange-CrossTenant-userprincipalname: 
 e0feHaupNd+ZncqL/7giuXPSjEoF7LB9RTQgGcVk3ySvPm9S+mfW/oEfmg125hyN
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM5PR12MB1195
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

AMD 2nd generation EPYC processors support the UMIP (User-Mode
Instruction Prevention) feature. So, rename X86_INTEL_UMIP to
generic X86_UMIP and modify the text to cover both Intel and AMD.

Signed-off-by: Babu Moger <babu.moger@amd.com>
---
 arch/x86/Kconfig                         |   10 +++++-----
 arch/x86/include/asm/disabled-features.h |    2 +-
 arch/x86/include/asm/umip.h              |    4 ++--
 arch/x86/kernel/Makefile                 |    2 +-
 4 files changed, 9 insertions(+), 9 deletions(-)

```
#### [PATCH v13 QEMU 1/3] virtio-ballon: Implement support for page poison tracking feature
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Duyck <alexander.duyck@gmail.com>
X-Patchwork-Id: 11228857
Return-Path: <SRS0=X2oT=Y5=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3CB94139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 Nov 2019 22:06:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 163EF20869
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 Nov 2019 22:06:46 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="sfmsKGds"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2387450AbfKEWGm (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 5 Nov 2019 17:06:42 -0500
Received: from mail-pf1-f195.google.com ([209.85.210.195]:36402 "EHLO
        mail-pf1-f195.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1730083AbfKEWGm (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 5 Nov 2019 17:06:42 -0500
Received: by mail-pf1-f195.google.com with SMTP id v19so17032992pfm.3;
        Tue, 05 Nov 2019 14:06:42 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=subject:from:to:cc:date:message-id:in-reply-to:references
         :user-agent:mime-version:content-transfer-encoding;
        bh=yOvpSx16yNanZpbvFfAUMxFv0SM7m3MFplEES/wscuI=;
        b=sfmsKGdscqK5HXDJ59tIoAlNoKkUGgfkWw8NJcFwhgLwRt4OQzjym85o3l1YVjC+pi
         +HdA/Ay4ZTsLeMytL4cofohhUFIioyauyxCOOSG921zFJmaZ94vdkhv7YsvN2jUPXydu
         LttVuCUSeu7RxTmsjo0B0nEe8yiv6CMqrnnrlJQA1XKA6zwITpRcoDBtGLKhKne+Se5W
         GDUcCKHMb9YNYX9vyGo0tFvCAi7NcZPOSjK19otr6sP82rlNodmd7HDiEq4DpFXccKNx
         q+VqfK1+VCnUi+eT5PeJsW47nhoEX+C/NlwAI/Qk6H0Iqhr/JNkT8gG+Ndht53ikBWSn
         ek+g==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:subject:from:to:cc:date:message-id:in-reply-to
         :references:user-agent:mime-version:content-transfer-encoding;
        bh=yOvpSx16yNanZpbvFfAUMxFv0SM7m3MFplEES/wscuI=;
        b=uO1l7YxEO/KOWp/Vyskta31LAlx7GFuKWWwhFP6QbXeVzBb+xot+RaGtgu9G0FYL6p
         2Uhl+aeY83t5Wi3jgExrNjde5KnCEIicjSfBMhQjw7wE+7wbhnwvJ3P4ZNlmNkJTDXo6
         Xh3J9EL1zlfmEyb/bbhhwwxvEXZk8PEPJHxl2090DqIVX+wSXanscd5yakA+jJpml97L
         x3N58MbKu8UfKH65QsKDdoj8t0WdUJ0k5HNouXeKDaxMWL6abDA+66sSR89DP7FdnPYo
         OWuoAiUKMb/wZ3fantdjCRZUuEO6mkQZNWosUu8UesPbZ3I9IbB0FpX70Jd38hvAACnz
         1DUQ==
X-Gm-Message-State: APjAAAWWpuXhcBjjXgVwanNfuIyo4dRyAeFROut8TCaAscoTClWDW8/w
        LJ8P8TXIZYhxKWrQu/sR664=
X-Google-Smtp-Source: 
 APXvYqzgwwFFrTh7Adpv3K30O16A20Hes3LHqWFEB/7MNKNyZDMR7Y0zF8YN8nTa3John2C3+nLP+A==
X-Received: by 2002:a62:14d0:: with SMTP id
 199mr11836005pfu.147.1572991601497;
        Tue, 05 Nov 2019 14:06:41 -0800 (PST)
Received: from localhost.localdomain ([2001:470:b:9c3:9e5c:8eff:fe4f:f2d0])
        by smtp.gmail.com with ESMTPSA id
 o1sm19677459pgm.1.2019.11.05.14.06.40
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Tue, 05 Nov 2019 14:06:41 -0800 (PST)
Subject: [PATCH v13 QEMU 1/3] virtio-ballon: Implement support for page
 poison tracking feature
From: Alexander Duyck <alexander.duyck@gmail.com>
To: kvm@vger.kernel.org, mst@redhat.com, linux-kernel@vger.kernel.org,
        willy@infradead.org, mhocko@kernel.org, linux-mm@kvack.org,
        akpm@linux-foundation.org, mgorman@techsingularity.net,
        vbabka@suse.cz
Cc: yang.zhang.wz@gmail.com, nitesh@redhat.com, konrad.wilk@oracle.com,
        david@redhat.com, pagupta@redhat.com, riel@surriel.com,
        lcapitulino@redhat.com, dave.hansen@intel.com,
        wei.w.wang@intel.com, aarcange@redhat.com, pbonzini@redhat.com,
        dan.j.williams@intel.com, alexander.h.duyck@linux.intel.com,
        osalvador@suse.de
Date: Tue, 05 Nov 2019 14:06:40 -0800
Message-ID: <20191105220640.15373.82064.stgit@localhost.localdomain>
In-Reply-To: <20191105215940.15144.65968.stgit@localhost.localdomain>
References: <20191105215940.15144.65968.stgit@localhost.localdomain>
User-Agent: StGit/0.17.1-dirty
MIME-Version: 1.0
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
#### [PATCH v5] vhost: introduce mdev based hardware backend
##### From: Tiwei Bie <tiwei.bie@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tiwei Bie <tiwei.bie@intel.com>
X-Patchwork-Id: 11227581
Return-Path: <SRS0=X2oT=Y5=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EC8CC14E5
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 Nov 2019 11:52:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B6C1221D6C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 Nov 2019 11:52:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730892AbfKELwz (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 5 Nov 2019 06:52:55 -0500
Received: from mga07.intel.com ([134.134.136.100]:14806 "EHLO mga07.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1730667AbfKELwy (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 5 Nov 2019 06:52:54 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by orsmga105.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 05 Nov 2019 03:52:52 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.68,271,1569308400";
   d="scan'208";a="212527270"
Received: from dpdk-virtio-tbie-2.sh.intel.com ([10.67.104.74])
  by fmsmga001.fm.intel.com with ESMTP; 05 Nov 2019 03:52:49 -0800
From: Tiwei Bie <tiwei.bie@intel.com>
To: mst@redhat.com, jasowang@redhat.com, alex.williamson@redhat.com,
        maxime.coquelin@redhat.com
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        dan.daly@intel.com, cunming.liang@intel.com,
        zhihong.wang@intel.com, lingshan.zhu@intel.com, tiwei.bie@intel.com
Subject: [PATCH v5] vhost: introduce mdev based hardware backend
Date: Tue,  5 Nov 2019 19:53:32 +0800
Message-Id: <20191105115332.11026-1-tiwei.bie@intel.com>
X-Mailer: git-send-email 2.23.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch introduces a mdev based hardware vhost backend.
This backend is built on top of the same abstraction used
in virtio-mdev and provides a generic vhost interface for
userspace to accelerate the virtio devices in guest.

This backend is implemented as a mdev device driver on top
of the same mdev device ops used in virtio-mdev but using
a different mdev class id, and it will register the device
as a VFIO device for userspace to use. Userspace can setup
the IOMMU with the existing VFIO container/group APIs and
then get the device fd with the device name. After getting
the device fd, userspace can use vhost ioctls on top of it
to setup the backend.

Signed-off-by: Tiwei Bie <tiwei.bie@intel.com>
---
This patch depends on below series:
https://lkml.org/lkml/2019/11/5/217

v4 -> v5:
- Rebase on top of virtio-mdev series v8;
- Use the virtio_ops of mdev_device in vhost-mdev (Jason);
- Some minor improvements on commit log;

v3 -> v4:
- Rebase on top of virtio-mdev series v6;
- Some minor tweaks and improvements;

v2 -> v3:
- Fix the return value (Jason);
- Don't cache unnecessary information in vhost-mdev (Jason);
- Get rid of the memset in open (Jason);
- Add comments for VHOST_SET_MEM_TABLE, ... (Jason);
- Filter out unsupported features in vhost-mdev (Jason);
- Add _GET_DEVICE_ID ioctl (Jason);
- Add _GET_CONFIG/_SET_CONFIG ioctls (Jason);
- Drop _GET_QUEUE_NUM ioctl (Jason);
- Fix the copy-paste errors in _IOW/_IOR usage;
- Some minor fixes and improvements;

v1 -> v2:
- Replace _SET_STATE with _SET_STATUS (MST);
- Check status bits at each step (MST);
- Report the max ring size and max number of queues (MST);
- Add missing MODULE_DEVICE_TABLE (Jason);
- Only support the network backend w/o multiqueue for now;
- Some minor fixes and improvements;
- Rebase on top of virtio-mdev series v4;

RFC v4 -> v1:
- Implement vhost-mdev as a mdev device driver directly and
  connect it to VFIO container/group. (Jason);
- Pass ring addresses as GPAs/IOVAs in vhost-mdev to avoid
  meaningless HVA->GPA translations (Jason);

RFC v3 -> RFC v4:
- Build vhost-mdev on top of the same abstraction used by
  virtio-mdev (Jason);
- Introduce vhost fd and pass VFIO fd via SET_BACKEND ioctl (MST);

RFC v2 -> RFC v3:
- Reuse vhost's ioctls instead of inventing a VFIO regions/irqs
  based vhost protocol on top of vfio-mdev (Jason);

RFC v1 -> RFC v2:
- Introduce a new VFIO device type to build a vhost protocol
  on top of vfio-mdev;

 drivers/vfio/mdev/mdev_core.c    |  21 ++
 drivers/vhost/Kconfig            |  12 +
 drivers/vhost/Makefile           |   3 +
 drivers/vhost/mdev.c             | 553 +++++++++++++++++++++++++++++++
 include/linux/mdev.h             |   5 +
 include/uapi/linux/vhost.h       |  18 +
 include/uapi/linux/vhost_types.h |   8 +
 7 files changed, 620 insertions(+)
 create mode 100644 drivers/vhost/mdev.c

```
