#### [PATCH v16 QEMU 2/3] virtio-balloon: Add support for providing free page reports to host
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Duyck <alexander.duyck@gmail.com>
X-Patchwork-Id: 11317455
Return-Path: <SRS0=EQ1L=2Y=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0AE3C14B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Jan 2020 21:21:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id DE63F22314
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Jan 2020 21:21:21 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="IReGa2gp"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728813AbgACVVR (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 3 Jan 2020 16:21:17 -0500
Received: from mail-pf1-f196.google.com ([209.85.210.196]:34226 "EHLO
        mail-pf1-f196.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728657AbgACVVQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 3 Jan 2020 16:21:16 -0500
Received: by mail-pf1-f196.google.com with SMTP id i6so17193111pfc.1;
        Fri, 03 Jan 2020 13:21:16 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=subject:from:to:cc:date:message-id:in-reply-to:references
         :user-agent:mime-version:content-transfer-encoding;
        bh=S67ROGEQCcp+6ozGSJjGTXgu/nEqa4BuBwrMv8wLSMo=;
        b=IReGa2gpjzbzT0DsrzpVX4qSADu6S+wBF/3HbzQ38dE/yvPaRm79BSAATDSruM5kwO
         TIidBoo1i73CWujrF0OeIRZd0YQ5WzAE3H2eyU+sju2ugoESBnpg4FOJxoh0meQNodz/
         QPcpExtgV33WERambn2oj57Od9YVHVuq7jaHpYiC6rgRkn6APMqmI/wmzYgrqBl5Xuq7
         zKMLN8iW1k2J2PMzgPPULqG/EQE/bOebpzRdeS7szwKV25U74c2SJp/gBGw/GxANc14N
         QxzER9uQWzXPYKgg6YT4iT7rKGg+mGn7QnNvHGOvmZF32Avp366kDbZd1vb/B2XVHuJF
         o1+w==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:subject:from:to:cc:date:message-id:in-reply-to
         :references:user-agent:mime-version:content-transfer-encoding;
        bh=S67ROGEQCcp+6ozGSJjGTXgu/nEqa4BuBwrMv8wLSMo=;
        b=MZpjzqg4ZiZXTlTi3Y+AthhdXmlNs1+nxD/BKunhky9tebXqXx/9hlZM2NPSYRP3rS
         w2w+a05Jt9J1nz+SAyPodjZo6vi7ZPtXyRxOPTB2xFDGf9BpodXxaIkRXCID91AU/feU
         b6uXFn41tp8RHbKlgnZ4+1AwsKi5J8p1uxT23uydTXQEWXGj5m8uD8YjLDPfC4jkQOS2
         gxjPxCJq5R2DqeMKuaCcdCICPDWsT+rHXVsn0VA4BQ4cod5clszcgSYOVgbEjAJ8ylIY
         dc+kpLzDIWhTISjZRIKDlyoOwEMyyzgcxb4ZzEYgp3geLCfEZBuLzjbv2x3yiruuKppm
         nbpg==
X-Gm-Message-State: APjAAAUscAhDLueAWZ592wdSGG7qF9Y1SYzHHHuhqVEuZrClETVemyrc
        MLvO1A6IhoFJytb/vZIhb2I=
X-Google-Smtp-Source: 
 APXvYqzpGZPeSqmK+zMTQ5LdDqI3o5o9Ha0+h7iu+L/6VZ89kc7BfukT01TLxUdVF4Ok/9jq0oZijg==
X-Received: by 2002:aa7:951c:: with SMTP id b28mr94501152pfp.97.1578086475886;
        Fri, 03 Jan 2020 13:21:15 -0800 (PST)
Received: from localhost.localdomain ([2001:470:b:9c3:9e5c:8eff:fe4f:f2d0])
        by smtp.gmail.com with ESMTPSA id
 q63sm46101348pfb.149.2020.01.03.13.21.15
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Fri, 03 Jan 2020 13:21:15 -0800 (PST)
Subject: [PATCH v16 QEMU 2/3] virtio-balloon: Add support for providing free
 page reports to host
From: Alexander Duyck <alexander.duyck@gmail.com>
To: virtio-dev@lists.oasis-open.org, kvm@vger.kernel.org,
        mst@redhat.com, linux-kernel@vger.kernel.org, willy@infradead.org,
        mhocko@kernel.org, linux-mm@kvack.org, akpm@linux-foundation.org,
        mgorman@techsingularity.net, vbabka@suse.cz
Cc: yang.zhang.wz@gmail.com, nitesh@redhat.com, konrad.wilk@oracle.com,
        david@redhat.com, pagupta@redhat.com, riel@surriel.com,
        lcapitulino@redhat.com, dave.hansen@intel.com,
        wei.w.wang@intel.com, aarcange@redhat.com, pbonzini@redhat.com,
        dan.j.williams@intel.com, alexander.h.duyck@linux.intel.com,
        osalvador@suse.de
Date: Fri, 03 Jan 2020 13:21:14 -0800
Message-ID: <20200103212114.29681.69388.stgit@localhost.localdomain>
In-Reply-To: <20200103210509.29237.18426.stgit@localhost.localdomain>
References: <20200103210509.29237.18426.stgit@localhost.localdomain>
User-Agent: StGit/0.17.1-dirty
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Alexander Duyck <alexander.h.duyck@linux.intel.com>

Add support for the page reporting feature provided by virtio-balloon.
Reporting differs from the regular balloon functionality in that is is
much less durable than a standard memory balloon. Instead of creating a
list of pages that cannot be accessed the pages are only inaccessible
while they are being indicated to the virtio interface. Once the
interface has acknowledged them they are placed back into their respective
free lists and are once again accessible by the guest system.

Unlike a standard balloon we don't inflate and deflate the pages. Instead
we perform the reporting, and once the reporting is completed it is
assumed that the page has been dropped from the guest and will be faulted
back in the next time the page is accessed.

This patch is a subset of the UAPI patch that was submitted for the Linux
kernel. The original patch can be found at:
https://lore.kernel.org/lkml/20200103211651.29237.84528.stgit@localhost.localdomain/

Signed-off-by: Alexander Duyck <alexander.h.duyck@linux.intel.com>
---
 include/standard-headers/linux/virtio_balloon.h |    1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH v16 QEMU 3/3] virtio-balloon: Provide a interface for free page reporting
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Duyck <alexander.duyck@gmail.com>
X-Patchwork-Id: 11317459
Return-Path: <SRS0=EQ1L=2Y=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0305F1395
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Jan 2020 21:21:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id CBBBC206DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Jan 2020 21:21:28 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="fgD2WG3T"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728826AbgACVVX (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 3 Jan 2020 16:21:23 -0500
Received: from mail-pf1-f195.google.com ([209.85.210.195]:35243 "EHLO
        mail-pf1-f195.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728722AbgACVVX (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 3 Jan 2020 16:21:23 -0500
Received: by mail-pf1-f195.google.com with SMTP id i23so18625240pfo.2;
        Fri, 03 Jan 2020 13:21:22 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=subject:from:to:cc:date:message-id:in-reply-to:references
         :user-agent:mime-version:content-transfer-encoding;
        bh=k/7N+WeIMLf1qaqKurny6a/721nmeSdfaWITRnU52O8=;
        b=fgD2WG3TALiBHmWa/NBkwqNO6YFTOB6RXKGmmWKBUKdNgmIThmkPiI+bj2BM+fNBsd
         93bEQEQT1nH2hfNr3OMqr1zXq7fYVINLZbtuYfLm2EgCqw+s61lZqaYhivXGbfklXqqc
         GG/yyeCO6FeQpP/8byirqQ3MHETYofPljjxMdglG1m5JFmfFP2tnDIpYYNdLAqmwdfD2
         rX8c9AMOdL1bYseVhwLI08K03iK960LlMvL6Vvyz/9tepIuXwr6mAgyTQUUNeFpPZx0s
         +FzuTOIqFaDCTNUb6jOmj8w8V0e26P1/MYuY5kRit3qhmE4yWid2AxUhNIvTgDCVQf2a
         9sSA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:subject:from:to:cc:date:message-id:in-reply-to
         :references:user-agent:mime-version:content-transfer-encoding;
        bh=k/7N+WeIMLf1qaqKurny6a/721nmeSdfaWITRnU52O8=;
        b=jvuhvBRd0ZXkAtbZkj47K0Vxu8Ftgb/43+cC7YMTNQbi4sBNo7R0c5ilHCYACbCAYD
         Y0lNaNOfw4FPXiVOupt8Mns29SBaPDW0aav4tN3hWPgwL6PDGFq0aWxrgwc+pZrNDgdh
         YYD3BHTySUzSho13YzZWKywNQhRWcYRdThZZjN+HQMxqOjXniiIfgcrUACL+8NT2/sp2
         0/DCbyCLcSJJeaJhrfG6N2dkYF5nZG2Hfdzm+MZP7K+7YDW2vibQPuV2UPsHn0YoXot1
         j6PWPQzIOSbxLjb2VXFVrmdwax65Xo4x4sncsIG/ELnbDSC4vgRw8UgbQWeY0UWaVl3Y
         XvsA==
X-Gm-Message-State: APjAAAXc36cokR5/5rcP/oUdaRWmmqWI3VexNEi28PrbyUgAuXuebjAM
        +T+0sBwIWhH8CFQbT2AtdBg=
X-Google-Smtp-Source: 
 APXvYqx12Ey0NunsKUZzmZ5aRdGnjpdEnYE9dsNE3MlNVxBfzNG2Yzs+Q/CUPkU6941tThRo91CYoA==
X-Received: by 2002:a63:7944:: with SMTP id
 u65mr84122620pgc.298.1578086481966;
        Fri, 03 Jan 2020 13:21:21 -0800 (PST)
Received: from localhost.localdomain ([2001:470:b:9c3:9e5c:8eff:fe4f:f2d0])
        by smtp.gmail.com with ESMTPSA id
 f81sm69930500pfa.118.2020.01.03.13.21.21
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Fri, 03 Jan 2020 13:21:21 -0800 (PST)
Subject: [PATCH v16 QEMU 3/3] virtio-balloon: Provide a interface for free
 page reporting
From: Alexander Duyck <alexander.duyck@gmail.com>
To: virtio-dev@lists.oasis-open.org, kvm@vger.kernel.org,
        mst@redhat.com, linux-kernel@vger.kernel.org, willy@infradead.org,
        mhocko@kernel.org, linux-mm@kvack.org, akpm@linux-foundation.org,
        mgorman@techsingularity.net, vbabka@suse.cz
Cc: yang.zhang.wz@gmail.com, nitesh@redhat.com, konrad.wilk@oracle.com,
        david@redhat.com, pagupta@redhat.com, riel@surriel.com,
        lcapitulino@redhat.com, dave.hansen@intel.com,
        wei.w.wang@intel.com, aarcange@redhat.com, pbonzini@redhat.com,
        dan.j.williams@intel.com, alexander.h.duyck@linux.intel.com,
        osalvador@suse.de
Date: Fri, 03 Jan 2020 13:21:20 -0800
Message-ID: <20200103212120.29681.4564.stgit@localhost.localdomain>
In-Reply-To: <20200103210509.29237.18426.stgit@localhost.localdomain>
References: <20200103210509.29237.18426.stgit@localhost.localdomain>
User-Agent: StGit/0.17.1-dirty
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Alexander Duyck <alexander.h.duyck@linux.intel.com>

Add support for what I am referring to as "free page reporting".
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
#### [PATCH v16 QEMU 4/3 RFC] memory: Add support for MADV_FREE as mechanism to lazy discard pages
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Duyck <alexander.duyck@gmail.com>
X-Patchwork-Id: 11317463
Return-Path: <SRS0=EQ1L=2Y=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 983721395
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Jan 2020 21:24:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 6CFEF21835
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Jan 2020 21:24:20 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="rXB1CvTJ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728645AbgACVYQ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 3 Jan 2020 16:24:16 -0500
Received: from mail-pf1-f193.google.com ([209.85.210.193]:46936 "EHLO
        mail-pf1-f193.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728567AbgACVYQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 3 Jan 2020 16:24:16 -0500
Received: by mail-pf1-f193.google.com with SMTP id n9so16173381pff.13;
        Fri, 03 Jan 2020 13:24:15 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=subject:from:to:cc:date:message-id:in-reply-to:references
         :user-agent:mime-version:content-transfer-encoding;
        bh=R+UOvEIvAKvV92s1Oao0n2zpHAWrzhC1LqeTb2UW2HA=;
        b=rXB1CvTJ6A9GhMN42hgYg/qS0Xy+3wuP23OMsdSchPUiu75AHNojATGXwFrAigRx6/
         qvZXOsLYwpJ5Ttf5dejWTslhzKpQocZjfk7+bpoKBW0KmYIYq6B5hVwujEt97/Q33sVf
         SnNJ2lZTNR/+aGDeNkR1mqkWxJFOv75Zlv32khd1Tx/okf+rDl8dxfpu1QFXncUtMxbr
         wxBKwTdl2xxpVe34MGN8TBeTY21dgptqgpQ/xWMKYUYgkXuEpi9P48qluxa9UTJ0Xy9c
         Xpq/y+E2f1AKxBeqKeD7/Br2IGioPQ5Ovxks6S4U7h2Q2IOvbKLewj4ggKujYeF5QYXI
         beWQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:subject:from:to:cc:date:message-id:in-reply-to
         :references:user-agent:mime-version:content-transfer-encoding;
        bh=R+UOvEIvAKvV92s1Oao0n2zpHAWrzhC1LqeTb2UW2HA=;
        b=XnkDtFc5ikBEuYxWf4FKKd8KWq2AHiUishVnCLOrkyC7HuRYSqWr/Y5tYYe8Gkn0E7
         oo5FM9pZAVlx2qr2YQT1OENe0ELbnj9LQUxnAa6n0Dbkhx1BxBySnANP7101F0xjSkRU
         Ypib/52Nv8K5uDaRpReIIzeKNjQsadFN0b4kf0+mquCXOjJKO9h2GsjM/kxSR1+kes0a
         GBssV1NCOuHsQmc1zwtB363XmiuFdg9tRmflrQ8Mtff5mUkAsBfqGlSnqr6Ioj8Vmjug
         RTw71weKpyt6KqVDggu6h6bgck05JUJZ47YjdpNgGbEJV0sVkvNybczMYdakGcIJqEyb
         K3kw==
X-Gm-Message-State: APjAAAWy/wuBjdpiETj/n5VvYrC8TwubNSBx8boF75pcRoJDN9cXVAUN
        y80ILmszj8o6SwY+6aVQr9o=
X-Google-Smtp-Source: 
 APXvYqybTyKvXei4N7XcHa7h/QWfnTj20X/f0SCjkOdjAZ6X/HleMJe2ybbwn56JEMDhin5x0CRs4w==
X-Received: by 2002:a62:a206:: with SMTP id m6mr86696087pff.210.1578086655318;
        Fri, 03 Jan 2020 13:24:15 -0800 (PST)
Received: from localhost.localdomain ([2001:470:b:9c3:9e5c:8eff:fe4f:f2d0])
        by smtp.gmail.com with ESMTPSA id
 w123sm50624962pfb.167.2020.01.03.13.24.14
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Fri, 03 Jan 2020 13:24:14 -0800 (PST)
Subject: [PATCH v16 QEMU 4/3 RFC] memory: Add support for MADV_FREE as
 mechanism to lazy discard pages
From: Alexander Duyck <alexander.duyck@gmail.com>
To: virtio-dev@lists.oasis-open.org, kvm@vger.kernel.org,
        mst@redhat.com, linux-kernel@vger.kernel.org, willy@infradead.org,
        mhocko@kernel.org, linux-mm@kvack.org, akpm@linux-foundation.org,
        mgorman@techsingularity.net, vbabka@suse.cz
Cc: yang.zhang.wz@gmail.com, nitesh@redhat.com, konrad.wilk@oracle.com,
        david@redhat.com, pagupta@redhat.com, riel@surriel.com,
        lcapitulino@redhat.com, dave.hansen@intel.com,
        wei.w.wang@intel.com, aarcange@redhat.com, pbonzini@redhat.com,
        dan.j.williams@intel.com, alexander.h.duyck@linux.intel.com,
        osalvador@suse.de
Date: Fri, 03 Jan 2020 13:24:14 -0800
Message-ID: <20200103212339.29849.99817.stgit@localhost.localdomain>
In-Reply-To: <20200103210509.29237.18426.stgit@localhost.localdomain>
References: <20200103210509.29237.18426.stgit@localhost.localdomain>
User-Agent: StGit/0.17.1-dirty
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Alexander Duyck <alexander.h.duyck@linux.intel.com>

Add support for the MADV_FREE advice argument when discarding pages.
Specifically we add an option to perform a lazy discard for use with free
page reporting as this allows us to avoid expensive page zeroing in the
case that the system is not under memory pressure.

To enable this I simply extended the ram_block_discard_range function to
add an extra parameter for "lazy" freeing. I then renamed the function,
wrapped it in a function defined using the original name and defaulting
lazy to false. From there I created a second wrapper for
ram_block_free_range and updated the page reporting code to use that.

Signed-off-by: Alexander Duyck <alexander.h.duyck@linux.intel.com>
---
 exec.c                     |   39 +++++++++++++++++++++++++++------------
 hw/virtio/virtio-balloon.c |    2 +-
 include/exec/cpu-common.h  |    1 +
 3 files changed, 29 insertions(+), 13 deletions(-)

```
#### [PATCH v16 1/9] mm: Adjust shuffle code to allow for future coalescing
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Duyck <alexander.duyck@gmail.com>
X-Patchwork-Id: 11317405
Return-Path: <SRS0=EQ1L=2Y=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3836E14B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Jan 2020 21:16:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1774A22314
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Jan 2020 21:16:33 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="KYliLu7W"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728678AbgACVQX (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 3 Jan 2020 16:16:23 -0500
Received: from mail-pf1-f196.google.com ([209.85.210.196]:46435 "EHLO
        mail-pf1-f196.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728462AbgACVQW (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 3 Jan 2020 16:16:22 -0500
Received: by mail-pf1-f196.google.com with SMTP id n9so16165911pff.13;
        Fri, 03 Jan 2020 13:16:22 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=subject:from:to:cc:date:message-id:in-reply-to:references
         :user-agent:mime-version:content-transfer-encoding;
        bh=nGjz5CxUAKYp6WMiD/ZoHk/Q6LgCdxFGQ5sPCnHiLQ4=;
        b=KYliLu7WptqgB+gxQH7IRYKQr1Sg6h+Ays7yLsBtqSlDuEDgA8rV9LNP5ubiF/NWzj
         RA1/yZKaAP638EQVd+AQ2V+Kk+Gv78x69VHJYJmGFkz51WxU8Ct7tkLE65WCG6IMSaa0
         xMzuczTIv8+nW7DH0db+9QlLgm1KmpCHbbXe2gz+A8j2kEi8h9N1ZHy+ByGjD0BysLlN
         +MS72w/ClxgCXNxbZ+qn1B8PEnVoGWBCspJhiqcNZEDmmR9ybZtJgtcr5jifneM8qdGI
         Rrhub3x11D/bWQW1JG2nJEND1VMJ4cIpc9vE0UNO9u7XTvUOkzHgvWUnlM64iwlQDnN6
         Ib6Q==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:subject:from:to:cc:date:message-id:in-reply-to
         :references:user-agent:mime-version:content-transfer-encoding;
        bh=nGjz5CxUAKYp6WMiD/ZoHk/Q6LgCdxFGQ5sPCnHiLQ4=;
        b=Nnidz6lLgjTAoh9VNtmNnTsFZzQWPYBVfNb5yExDmt9BMobu9JFAWXZ5XJiJEIZ/Es
         i7GcmzOZIPEVf3L820ceZa8JmKznAq+sOcCzG6cJjJvK2FrTcKq9wgHyYbcMVYn1WMbi
         4YnRTVqIZo9QgLRmTbwTic5PEoegIb8UIflIi4m7vQCCl9NCixYVx9P8cLlusTMKA3qq
         J5cbLhbawVWZj4WY/uoZlYf3gB94Uk3MDyxouS52U4Vcdn0++kwx5ABWh4eJ9Rf1GtDS
         oBOt2Yq1AYXT/Mj+SeRkHp/s6ebxbvHS0fgvLT+p0A2JGV30NbokCTyvKWLuNJwCyOG8
         OZHg==
X-Gm-Message-State: APjAAAUSVc242aapPshJ+Zsqupa/zWovsY57SNSjXroNNhh9DKxGVwEG
        VDHzDx5YExaHxMhOJx/kufk=
X-Google-Smtp-Source: 
 APXvYqyCcTdW0ISpVJFhPsSKEkqmov38rMJhCcsvHK0W6V6zVVV/6g6gstqBAIAaFkEqU6ByA+85Xw==
X-Received: by 2002:a62:ac08:: with SMTP id v8mr98702364pfe.83.1578086181985;
        Fri, 03 Jan 2020 13:16:21 -0800 (PST)
Received: from localhost.localdomain ([2001:470:b:9c3:9e5c:8eff:fe4f:f2d0])
        by smtp.gmail.com with ESMTPSA id
 a28sm68176390pfh.119.2020.01.03.13.16.21
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Fri, 03 Jan 2020 13:16:21 -0800 (PST)
Subject: [PATCH v16 1/9] mm: Adjust shuffle code to allow for future
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
Date: Fri, 03 Jan 2020 13:16:20 -0800
Message-ID: <20200103211620.29237.31778.stgit@localhost.localdomain>
In-Reply-To: <20200103210509.29237.18426.stgit@localhost.localdomain>
References: <20200103210509.29237.18426.stgit@localhost.localdomain>
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

Acked-by: Mel Gorman <mgorman@techsingularity.net>
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
#### [PATCH 1/2] vfio: introduce vfio_iova_rw to read/write a range of IOVAs
##### From: Yan Zhao <yan.y.zhao@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yan Zhao <yan.y.zhao@intel.com>
X-Patchwork-Id: 11316221
Return-Path: <SRS0=EQ1L=2Y=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6E0881395
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Jan 2020 01:11:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4C7E721D56
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Jan 2020 01:11:07 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726089AbgACBLD (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 2 Jan 2020 20:11:03 -0500
Received: from mga02.intel.com ([134.134.136.20]:59866 "EHLO mga02.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725872AbgACBLD (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 2 Jan 2020 20:11:03 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga006.jf.intel.com ([10.7.209.51])
  by orsmga101.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 02 Jan 2020 17:11:02 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.69,388,1571727600";
   d="scan'208";a="221511337"
Received: from joy-optiplex-7040.sh.intel.com ([10.239.13.9])
  by orsmga006.jf.intel.com with ESMTP; 02 Jan 2020 17:11:01 -0800
From: Yan Zhao <yan.y.zhao@intel.com>
To: alex.williamson@redhat.com
Cc: zhenyuw@linux.intel.com, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, intel-gvt@eclists.intel.com,
        pbonzini@redhat.com, kevin.tian@intel.com,
        Yan Zhao <yan.y.zhao@intel.com>
Subject: [PATCH 1/2] vfio: introduce vfio_iova_rw to read/write a range of
 IOVAs
Date: Thu,  2 Jan 2020 20:02:17 -0500
Message-Id: <20200103010217.4201-1-yan.y.zhao@intel.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200103010055.4140-1-yan.y.zhao@intel.com>
References: <20200103010055.4140-1-yan.y.zhao@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

vfio_iova_rw will read/write a range of userspace memory (starting form
device iova to iova + len -1) into a kenrel buffer without pinning the
userspace memory.

TODO: vfio needs to mark the iova dirty if vfio_iova_rw(write) is
called.

Cc: Kevin Tian <kevin.tian@intel.com>
Signed-off-by: Yan Zhao <yan.y.zhao@intel.com>
---
 drivers/vfio/vfio.c             | 45 ++++++++++++++++++
 drivers/vfio/vfio_iommu_type1.c | 81 +++++++++++++++++++++++++++++++++
 include/linux/vfio.h            |  5 ++
 3 files changed, 131 insertions(+)

```
#### [PATCH v16 QEMU 1/3] virtio-ballon: Implement support for page poison tracking feature
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Duyck <alexander.duyck@gmail.com>
X-Patchwork-Id: 11317451
Return-Path: <SRS0=EQ1L=2Y=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B788F1395
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Jan 2020 21:21:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 8BC34206DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Jan 2020 21:21:15 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="aUnnZPoy"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728795AbgACVVL (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 3 Jan 2020 16:21:11 -0500
Received: from mail-pf1-f196.google.com ([209.85.210.196]:40968 "EHLO
        mail-pf1-f196.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728549AbgACVVK (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 3 Jan 2020 16:21:10 -0500
Received: by mail-pf1-f196.google.com with SMTP id w62so24036119pfw.8;
        Fri, 03 Jan 2020 13:21:10 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=subject:from:to:cc:date:message-id:in-reply-to:references
         :user-agent:mime-version:content-transfer-encoding;
        bh=yOvpSx16yNanZpbvFfAUMxFv0SM7m3MFplEES/wscuI=;
        b=aUnnZPoyzNSRZI+t0GKzb0TiRDWqBbMy6GlerfoXN1OAqft7NaJEzn11o9T/3DMq5m
         D5lh3LBDCt0ZanoRzaNEMVxEkXPa0M9P1E220EWP2F59b00BA4OG79c6V2n3y9Eo545d
         QD+tLlReeFsllG9KaJ1OekusQGVfJ7Zxdtv429ovUZUEnqUK+51gA6eOLfHUomr1Aet/
         yfDu+Y5PiczTZwrNZ08YNf8D4DJfGSplZfhj7UDe8L2wCHMDBpqFijZfgOsn+VLS9Omz
         GPxhdghSOZjPtQ7giiRMtP7rnfLzWPfAIykW/Fx50jiJapPwSY2jeAOSPwumC1Mn8U+A
         qhvQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:subject:from:to:cc:date:message-id:in-reply-to
         :references:user-agent:mime-version:content-transfer-encoding;
        bh=yOvpSx16yNanZpbvFfAUMxFv0SM7m3MFplEES/wscuI=;
        b=OcdLZocLD6egBy0h+rZO5qteULckBqn2ghJFqSnnsiMor3RYLt20MyhHl27h1tjeog
         H0WTEN2i4HhBE1/CtOCFPBEGDmnpvFWyTTGGHnHOV8k4BLnWxwZmfJVAPhAmQFPkxA70
         VP1efGbu+yziE2kEiwmZ9ZzjAzpUPIq3T1tRLlgwqBNhs7bMkNd2EupUyl0UDzrxuWqw
         tnZpB+VQf6KoNA0e+ZR3l4BroAWdUyEZKfiRf3piB1p+mp6x9dnoqwm1UcwSAC7LP6IB
         d3UmmR2luwBSKNh6bp07iTgldMxBfmaYkaXLGgO0KG29lfMy9McFaJ2DZenUnsXbaNKb
         D6Hg==
X-Gm-Message-State: APjAAAUnyJB1C+IPgRAxBYOBvF+1yI05ED2Lxw+nzUSw/gDZ6CGlipvN
        6ioeGnNuHUdsf5RXN/V3dRc=
X-Google-Smtp-Source: 
 APXvYqyl/OVK4piGSFsYxsF33xMxvHQ/DgomiEAziuxRDwCwRMxsSuZnqK2aGPyyvqltNieLPJI63Q==
X-Received: by 2002:a63:3d8e:: with SMTP id k136mr97287157pga.4.1578086469815;
        Fri, 03 Jan 2020 13:21:09 -0800 (PST)
Received: from localhost.localdomain ([2001:470:b:9c3:9e5c:8eff:fe4f:f2d0])
        by smtp.gmail.com with ESMTPSA id
 z22sm61861872pfr.83.2020.01.03.13.21.09
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Fri, 03 Jan 2020 13:21:09 -0800 (PST)
Subject: [PATCH v16 QEMU 1/3] virtio-ballon: Implement support for page
 poison tracking feature
From: Alexander Duyck <alexander.duyck@gmail.com>
To: virtio-dev@lists.oasis-open.org, kvm@vger.kernel.org,
        mst@redhat.com, linux-kernel@vger.kernel.org, willy@infradead.org,
        mhocko@kernel.org, linux-mm@kvack.org, akpm@linux-foundation.org,
        mgorman@techsingularity.net, vbabka@suse.cz
Cc: yang.zhang.wz@gmail.com, nitesh@redhat.com, konrad.wilk@oracle.com,
        david@redhat.com, pagupta@redhat.com, riel@surriel.com,
        lcapitulino@redhat.com, dave.hansen@intel.com,
        wei.w.wang@intel.com, aarcange@redhat.com, pbonzini@redhat.com,
        dan.j.williams@intel.com, alexander.h.duyck@linux.intel.com,
        osalvador@suse.de
Date: Fri, 03 Jan 2020 13:21:08 -0800
Message-ID: <20200103212108.29681.99290.stgit@localhost.localdomain>
In-Reply-To: <20200103210509.29237.18426.stgit@localhost.localdomain>
References: <20200103210509.29237.18426.stgit@localhost.localdomain>
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
