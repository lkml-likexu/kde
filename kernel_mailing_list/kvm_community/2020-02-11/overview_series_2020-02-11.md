#### [PATCH v17 QEMU 2/3] virtio-balloon: Add support for providing free page reports to host
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Duyck <alexander.duyck@gmail.com>
X-Patchwork-Id: 11377069
Return-Path: <SRS0=UyAS=37=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1B5AF14E3
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 11 Feb 2020 22:51:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id EE6A120714
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 11 Feb 2020 22:51:35 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="EqmHEL7y"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727791AbgBKWvd (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 11 Feb 2020 17:51:33 -0500
Received: from mail-wr1-f66.google.com ([209.85.221.66]:45134 "EHLO
        mail-wr1-f66.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727199AbgBKWvc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 11 Feb 2020 17:51:32 -0500
Received: by mail-wr1-f66.google.com with SMTP id g3so13519768wrs.12;
        Tue, 11 Feb 2020 14:51:32 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=subject:from:to:cc:date:message-id:in-reply-to:references
         :user-agent:mime-version:content-transfer-encoding;
        bh=IOMlbjfXWuE+0u1ners+vpffTKgzzJDssD1Ouo69X0c=;
        b=EqmHEL7y0QA2mqPEAqNBo3EgWQVzlqdF9y2t1wKN6PRG19ziObA6wDoKpFUh4SvKoW
         JIoBJOMevTGYbyetGQWgQuRDrtj2apJTSBrrgiKrUyT8ACmpgeyOyf05wGeThVJwQ8ra
         iEzwxO72XwKzR7K8P9+XUPv/0z9RWpsCtZF/sD1Zj8A0OHrJg14V/LLV8jKDkidNv+4u
         gzRtI6WebEcA75xwVcH5PdmA8LUkM2wrL8EtpHLePZBGhVspRCBbjOO/Yq4tEAcOVS2z
         M07L2pq6fKNMQ8JKIz/QhLY/pVehO3b95DspSwcM6KezGAsVEU2jVWwRSiIRMQDvpYcN
         CmTw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:subject:from:to:cc:date:message-id:in-reply-to
         :references:user-agent:mime-version:content-transfer-encoding;
        bh=IOMlbjfXWuE+0u1ners+vpffTKgzzJDssD1Ouo69X0c=;
        b=NR+bnkvhu+o5ip+XoFPzXyP33BmQ+WzaTllKPxYs+wxo9CK1XImugHkrJ60xMZrNh2
         Vq+IN4GA6HqHA8ybKDn2fn6LvUv1mqVNR6JFbMoHmwKDgYx9FzLKJzraNHfjnSXV69U+
         YeBlTpP6FyQ+z4Wt8xi6Uq4ICTzelUuvlX08KgYlb9uJ4nwgTC1UQlpZllBiER22GtoO
         IzB/mPt1YuZOiHI/kaR2ckOcSxTsLZO6wqYoGN6DPWjy5KdcR5SoGX/hMtH97vYNgE4o
         meWVq1NTYjuboM+cdSuWVX0rkdMyrS/khFwtc6jRixoaxTL77fFf/JBp5RhFHrUbwBwl
         /9Hg==
X-Gm-Message-State: APjAAAXR5axWToRwjJ2d8my4MUtr3LTTYzYF2LD3rrYrc0a29PCukqzO
        cWm+3u+VqUlS3uJE8yRJ0vk=
X-Google-Smtp-Source: 
 APXvYqx+93e8f6Snf8Nwn26W6HHkSao0doTNZ1FIT+zSN0DdE7/fhQjcDfKypFQyi4PFtnreFzPiRg==
X-Received: by 2002:a5d:4e0a:: with SMTP id
 p10mr11687705wrt.229.1581461491313;
        Tue, 11 Feb 2020 14:51:31 -0800 (PST)
Received: from localhost.localdomain ([2001:470:b:9c3:9e5c:8eff:fe4f:f2d0])
        by smtp.gmail.com with ESMTPSA id
 k16sm7418136wru.0.2020.02.11.14.51.26
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Tue, 11 Feb 2020 14:51:30 -0800 (PST)
Subject: [PATCH v17 QEMU 2/3] virtio-balloon: Add support for providing free
 page reports to host
From: Alexander Duyck <alexander.duyck@gmail.com>
To: virtio-dev@lists.oasis-open.org, kvm@vger.kernel.org,
        mst@redhat.com, david@redhat.com, linux-kernel@vger.kernel.org,
        linux-mm@kvack.org, akpm@linux-foundation.org
Cc: yang.zhang.wz@gmail.com, pagupta@redhat.com,
        konrad.wilk@oracle.com, nitesh@redhat.com, riel@surriel.com,
        willy@infradead.org, lcapitulino@redhat.com, dave.hansen@intel.com,
        wei.w.wang@intel.com, aarcange@redhat.com, pbonzini@redhat.com,
        dan.j.williams@intel.com, mhocko@kernel.org,
        mgorman@techsingularity.net, alexander.h.duyck@linux.intel.com,
        vbabka@suse.cz, osalvador@suse.de
Date: Tue, 11 Feb 2020 14:51:25 -0800
Message-ID: <20200211225125.30409.98370.stgit@localhost.localdomain>
In-Reply-To: <20200211224416.29318.44077.stgit@localhost.localdomain>
References: <20200211224416.29318.44077.stgit@localhost.localdomain>
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
https://lore.kernel.org/lkml/20200211224657.29318.68624.stgit@localhost.localdomain/

Signed-off-by: Alexander Duyck <alexander.h.duyck@linux.intel.com>
---
 include/standard-headers/linux/virtio_balloon.h |    1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH v17 QEMU 3/3] virtio-balloon: Provide a interface for free page reporting
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Duyck <alexander.duyck@gmail.com>
X-Patchwork-Id: 11377073
Return-Path: <SRS0=UyAS=37=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4475813A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 11 Feb 2020 22:51:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 197A52082F
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 11 Feb 2020 22:51:49 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="RWg0DHYs"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727811AbgBKWvp (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 11 Feb 2020 17:51:45 -0500
Received: from mail-wr1-f66.google.com ([209.85.221.66]:37048 "EHLO
        mail-wr1-f66.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727646AbgBKWvp (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 11 Feb 2020 17:51:45 -0500
Received: by mail-wr1-f66.google.com with SMTP id w15so14627155wru.4;
        Tue, 11 Feb 2020 14:51:43 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=subject:from:to:cc:date:message-id:in-reply-to:references
         :user-agent:mime-version:content-transfer-encoding;
        bh=gbRBokZUeADxG1Js0n3CcSXLvNNKI4dY2r2GfqE2RsE=;
        b=RWg0DHYshDumqM8KMtdD8WzZEBRBdtcqeptU7cfM++emlBM0larEOBvFM99t8D9+IF
         f+yjlO17jmr2gdU6vRzDtyc6jwPXblwrne+kIvat6vJnJIGf9MR51g2wmcuMUTcI+8uY
         oPy/m7ue6+e0HA7536dalkZxz/vAaSTsyrOY7xBgdR6VokqoBmxGaBIt2yCOg+5kkzrl
         GxdidR52st8cameycVetD0lo8nHhVmMrHBklSFA1l/bBTEBqSzDngjidW1S0TngyWLgS
         XqMi9DzkafK93/r9NhbP7IhbmwGuE6fUM3t5jdOepH9eqfHCf8CnmJ4/DKYeGxesaCtu
         4WOw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:subject:from:to:cc:date:message-id:in-reply-to
         :references:user-agent:mime-version:content-transfer-encoding;
        bh=gbRBokZUeADxG1Js0n3CcSXLvNNKI4dY2r2GfqE2RsE=;
        b=gAh/YIkN8eHEF+s3sNXVEDXJcsigFiytW7fHKritA+SCphTZ2okOHkPIsg6f9Nnf9B
         8fIs45EFC97OSxheh/uFmT4GlRGyqqcD3iwQay/WisWToqJoJd5xOxp3/upIagTbFkUL
         QK3Jjo/YNpbTXEsfkYrL4sOg0Oo86Dk+Dgh1DS6lhW+ng8xyGPQOHPrFHEyF/26PQE3W
         skzHDFubZIX53kC5MayVI8n8C8iYeHsz4et182QuwsHixpCRiaI0hY9WckZmqE/fcakC
         mAZj8JF7R4sPe3PBYD4tt5hlmb6mdwLpJVDtlg9Ve8KFTw1TToG+bH4omHn7fZ126xM7
         100g==
X-Gm-Message-State: APjAAAXOPMIvkpaa1NJgv40RD6iInNP/HIWrKLFTg+vJ35F1muQOK7Vf
        Mz+ziTG4cDbIIODXIvjNd8I=
X-Google-Smtp-Source: 
 APXvYqzkuhT8IIjfBmSkf1LMLzuqn/V5z54dpY3u54czC6sPEmwWmluvmOO2tESqZZOptp3wLYYUJQ==
X-Received: by 2002:adf:9c8d:: with SMTP id
 d13mr11670626wre.392.1581461502576;
        Tue, 11 Feb 2020 14:51:42 -0800 (PST)
Received: from localhost.localdomain ([2001:470:b:9c3:9e5c:8eff:fe4f:f2d0])
        by smtp.gmail.com with ESMTPSA id
 d204sm5547055wmd.30.2020.02.11.14.51.38
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Tue, 11 Feb 2020 14:51:42 -0800 (PST)
Subject: [PATCH v17 QEMU 3/3] virtio-balloon: Provide a interface for free
 page reporting
From: Alexander Duyck <alexander.duyck@gmail.com>
To: virtio-dev@lists.oasis-open.org, kvm@vger.kernel.org,
        mst@redhat.com, david@redhat.com, linux-kernel@vger.kernel.org,
        linux-mm@kvack.org, akpm@linux-foundation.org
Cc: yang.zhang.wz@gmail.com, pagupta@redhat.com,
        konrad.wilk@oracle.com, nitesh@redhat.com, riel@surriel.com,
        willy@infradead.org, lcapitulino@redhat.com, dave.hansen@intel.com,
        wei.w.wang@intel.com, aarcange@redhat.com, pbonzini@redhat.com,
        dan.j.williams@intel.com, mhocko@kernel.org,
        mgorman@techsingularity.net, alexander.h.duyck@linux.intel.com,
        vbabka@suse.cz, osalvador@suse.de
Date: Tue, 11 Feb 2020 14:51:36 -0800
Message-ID: <20200211225136.30409.19938.stgit@localhost.localdomain>
In-Reply-To: <20200211224416.29318.44077.stgit@localhost.localdomain>
References: <20200211224416.29318.44077.stgit@localhost.localdomain>
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
#### [PATCH v17 QEMU 4/3 RFC] memory: Add support for MADV_FREE as mechanism to lazy discard pages
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Duyck <alexander.duyck@gmail.com>
X-Patchwork-Id: 11377077
Return-Path: <SRS0=UyAS=37=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9E99513A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 11 Feb 2020 22:53:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 73A7D2073C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 11 Feb 2020 22:53:30 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="jSBrLcrA"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727597AbgBKWx1 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 11 Feb 2020 17:53:27 -0500
Received: from mail-wm1-f66.google.com ([209.85.128.66]:53370 "EHLO
        mail-wm1-f66.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727199AbgBKWx1 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 11 Feb 2020 17:53:27 -0500
Received: by mail-wm1-f66.google.com with SMTP id s10so5817143wmh.3;
        Tue, 11 Feb 2020 14:53:25 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=subject:from:to:cc:date:message-id:in-reply-to:references
         :user-agent:mime-version:content-transfer-encoding;
        bh=S1eHB/ml3ctPQzFmJyOptm0m86oSEkXU1wRBmsiOhmM=;
        b=jSBrLcrAG1ltGRBRq4U2VE5u9yNE3cjbueJAk+fuoekSc36pMuMCbACNJV1w0tSNAF
         S1ONMJgbLb2a9GJV5tPUW6YKTQyYfcwa5dhdIjBJJg7YMV/DLtD1TqnFJo43lOkxJlAy
         crG0C/egrX4U+xGq5NSnyNGMdcZggAG8D16OX8PzzoST8qcF1+9F0Enj5K8qVRwn4wfj
         Fxkp2AFdbQuigpmFSoyEHKWAAOHkH1EB6oY3cwxzS/mm+3aacujad/Za1gkDNR/5rpv9
         1SIwobT7+uqgvdeCezpcWBpcaW8FV1YtQl7Q8e4QLTQs/NhCW0/BMrUqBGtdzpYQE4fF
         fXWw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:subject:from:to:cc:date:message-id:in-reply-to
         :references:user-agent:mime-version:content-transfer-encoding;
        bh=S1eHB/ml3ctPQzFmJyOptm0m86oSEkXU1wRBmsiOhmM=;
        b=pkAuBkJWEe/IA3znWvEtZYo/gsMu5Z/Annu46cvC5UlYPilUa6aMeqyIvH3UKo69t4
         aSSi2CaUzkAzNvW3Z0k5yp915dbufXWUk4Wlcj8DbFpRKkdtqNRc6jAhJ5y9YiDnHJJb
         FwnsiJTlz1gCbXhJvnKJR3HvEAbkkWdxVQJdaCk1EXDFep3LlPOdga2P8IwvXB5A2z0l
         WC+2htqjrPBVWRogU7h4CWi+8lY6bUDy9RKVKVUpw68OS94ycXjEXdn9XiSrKQXE4VWB
         hAyaX059Zkxr9PcUtlslMmukNTjueedM57m9Q9pO8/mrflg+Z3BoY5nkA4LvKrsQop99
         37sA==
X-Gm-Message-State: APjAAAUID2NycZDt6x3IfwB7JV/i1qTM5uRicohuy5X3VQicZ7Izk3LP
        y9hoB8zatF2P51Q+Bzgq27Q=
X-Google-Smtp-Source: 
 APXvYqzqlf5oxNgk8th18WowzQtUb3awrK2YQcMVxb29DDDmi7fe37ioHUaSOFJ2r6tjOtRseRlyPg==
X-Received: by 2002:a1c:a5c7:: with SMTP id
 o190mr2079763wme.183.1581461604557;
        Tue, 11 Feb 2020 14:53:24 -0800 (PST)
Received: from localhost.localdomain ([2001:470:b:9c3:9e5c:8eff:fe4f:f2d0])
        by smtp.gmail.com with ESMTPSA id
 z11sm6981099wrv.96.2020.02.11.14.53.20
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Tue, 11 Feb 2020 14:53:24 -0800 (PST)
Subject: [PATCH v17 QEMU 4/3 RFC] memory: Add support for MADV_FREE as
 mechanism to lazy discard pages
From: Alexander Duyck <alexander.duyck@gmail.com>
To: virtio-dev@lists.oasis-open.org, kvm@vger.kernel.org,
        mst@redhat.com, david@redhat.com, linux-kernel@vger.kernel.org,
        linux-mm@kvack.org, akpm@linux-foundation.org
Cc: yang.zhang.wz@gmail.com, pagupta@redhat.com,
        konrad.wilk@oracle.com, nitesh@redhat.com, riel@surriel.com,
        willy@infradead.org, lcapitulino@redhat.com, dave.hansen@intel.com,
        wei.w.wang@intel.com, aarcange@redhat.com, pbonzini@redhat.com,
        dan.j.williams@intel.com, mhocko@kernel.org,
        mgorman@techsingularity.net, alexander.h.duyck@linux.intel.com,
        vbabka@suse.cz, osalvador@suse.de
Date: Tue, 11 Feb 2020 14:53:18 -0800
Message-ID: <20200211225220.30596.80416.stgit@localhost.localdomain>
In-Reply-To: <20200211224416.29318.44077.stgit@localhost.localdomain>
References: <20200211224416.29318.44077.stgit@localhost.localdomain>
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
#### [kvm-unit-tests PATCH 1/3] arm/arm64: gic: Move gic_state enumeration to asm/gic.h
##### From: Zenghui Yu <yuzenghui@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zenghui Yu <yuzenghui@huawei.com>
X-Patchwork-Id: 11375073
Return-Path: <SRS0=UyAS=37=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A056B139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 11 Feb 2020 08:40:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7558520848
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 11 Feb 2020 08:40:44 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727728AbgBKIkn (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 11 Feb 2020 03:40:43 -0500
Received: from szxga06-in.huawei.com ([45.249.212.32]:52208 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1727653AbgBKIkn (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 11 Feb 2020 03:40:43 -0500
Received: from DGGEMS407-HUB.china.huawei.com (unknown [172.30.72.59])
        by Forcepoint Email with ESMTP id 8259A53757EA3401812D;
        Tue, 11 Feb 2020 16:40:40 +0800 (CST)
Received: from DESKTOP-8RFUVS3.china.huawei.com (10.173.222.27) by
 DGGEMS407-HUB.china.huawei.com (10.3.19.207) with Microsoft SMTP Server id
 14.3.439.0; Tue, 11 Feb 2020 16:40:33 +0800
From: Zenghui Yu <yuzenghui@huawei.com>
To: <drjones@redhat.com>, <kvm@vger.kernel.org>,
        <kvmarm@lists.cs.columbia.edu>
CC: <alexandru.elisei@arm.com>, <wanghaibin.wang@huawei.com>,
        Zenghui Yu <yuzenghui@huawei.com>
Subject: [kvm-unit-tests PATCH 1/3] arm/arm64: gic: Move gic_state enumeration
 to asm/gic.h
Date: Tue, 11 Feb 2020 16:38:59 +0800
Message-ID: <20200211083901.1478-2-yuzenghui@huawei.com>
X-Mailer: git-send-email 2.23.0.windows.1
In-Reply-To: <20200211083901.1478-1-yuzenghui@huawei.com>
References: <20200211083901.1478-1-yuzenghui@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.173.222.27]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The status of each interrupt are defined by the GIC architecture and
maintained by GIC hardware.  They're not specified to the timer HW.
Let's move this software enumeration to a more proper place.

Signed-off-by: Zenghui Yu <yuzenghui@huawei.com>
---
 arm/timer.c       | 7 -------
 lib/arm/asm/gic.h | 7 +++++++
 2 files changed, 7 insertions(+), 7 deletions(-)

```
#### [RFC PATCH v3 1/9] vfio/pci: export vfio_pci_device public and add vfio_pci_device_private
##### From: Yan Zhao <yan.y.zhao@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yan Zhao <yan.y.zhao@intel.com>
X-Patchwork-Id: 11375159
Return-Path: <SRS0=UyAS=37=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2805E921
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 11 Feb 2020 10:20:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id C83B32086A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 11 Feb 2020 10:20:07 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728245AbgBKKUE (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 11 Feb 2020 05:20:04 -0500
Received: from mga12.intel.com ([192.55.52.136]:55698 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727805AbgBKKUE (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 11 Feb 2020 05:20:04 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga007.jf.intel.com ([10.7.209.58])
  by fmsmga106.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 11 Feb 2020 02:20:01 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,428,1574150400";
   d="scan'208";a="221888182"
Received: from joy-optiplex-7040.sh.intel.com ([10.239.13.16])
  by orsmga007.jf.intel.com with ESMTP; 11 Feb 2020 02:19:58 -0800
From: Yan Zhao <yan.y.zhao@intel.com>
To: alex.williamson@redhat.com
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        cohuck@redhat.com, zhenyuw@linux.intel.com, zhi.a.wang@intel.com,
        kevin.tian@intel.com, shaopeng.he@intel.com, yi.l.liu@intel.com,
        Yan Zhao <yan.y.zhao@intel.com>
Subject: [RFC PATCH v3 1/9] vfio/pci: export vfio_pci_device public and add
 vfio_pci_device_private
Date: Tue, 11 Feb 2020 05:10:38 -0500
Message-Id: <20200211101038.20772-1-yan.y.zhao@intel.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200211095727.20426-1-yan.y.zhao@intel.com>
References: <20200211095727.20426-1-yan.y.zhao@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

(1) make vfio_pci_device public, so it is accessible from external code.
(2) add a private struct vfio_pci_device_private, which is only accessible
from internal code. It extends struct vfio_pci_device.

Signed-off-by: Yan Zhao <yan.y.zhao@intel.com>
---
 drivers/vfio/pci/vfio_pci.c         | 256 +++++++++++++++-------------
 drivers/vfio/pci/vfio_pci_config.c  | 186 ++++++++++++--------
 drivers/vfio/pci/vfio_pci_igd.c     |  19 ++-
 drivers/vfio/pci/vfio_pci_intrs.c   | 186 +++++++++++---------
 drivers/vfio/pci/vfio_pci_nvlink2.c |  22 +--
 drivers/vfio/pci/vfio_pci_private.h |   7 +-
 drivers/vfio/pci/vfio_pci_rdwr.c    |  40 +++--
 include/linux/vfio.h                |   5 +
 8 files changed, 408 insertions(+), 313 deletions(-)

```
#### [PATCH v2 01/94] KVM: arm64: Move __load_guest_stage2 to kvm_mmu.h
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11376111
Return-Path: <SRS0=UyAS=37=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 831C014B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 11 Feb 2020 17:49:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 6134E208C3
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 11 Feb 2020 17:49:58 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1581443398;
	bh=CDfmi4wjycuxqXp0yX9NnOipKJiEr/tNVdnuxQnjckU=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=QSpzdHBx1dsa25704iwsWlao000g5VouJA3dqPCq5D0jvZCdrN2gkHPtmQ4p3VlLd
	 DeVlRHlFVrPXf47Mv0uMSrXSGlRzO1YEOdfSGtMoBkYEfJ60TbrcRc8Iw8sLv97nqp
	 DWT6X44O1Ohh/LozMtRSjQ+ozwWtlnTTSQE/JnTI=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729410AbgBKRt5 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 11 Feb 2020 12:49:57 -0500
Received: from mail.kernel.org ([198.145.29.99]:52246 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728601AbgBKRt5 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 11 Feb 2020 12:49:57 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 1CB14206CC;
        Tue, 11 Feb 2020 17:49:56 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1581443396;
        bh=CDfmi4wjycuxqXp0yX9NnOipKJiEr/tNVdnuxQnjckU=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=AiLkh9rTX0sSunjQf5l8DcZvGYeqfXpGnAP+AYT82nTxYjF654jf1FVFloOgavoxc
         fdhGEQ3XsYP1Ju0ACwNFv7GdEOAPKKrXvXzkXrwkSlQ6zbmxiZIwkV6KluCrIQezRo
         0uHQlTlODNKyYfyplOwlmuWuCnJVrFY7LM+XzI7s=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1j1ZfW-004O7k-E0; Tue, 11 Feb 2020 17:49:54 +0000
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: Andre Przywara <andre.przywara@arm.com>,
        Christoffer Dall <christoffer.dall@arm.com>,
        Dave Martin <Dave.Martin@arm.com>,
        Jintack Lim <jintack@cs.columbia.edu>,
        Alexandru Elisei <alexandru.elisei@arm.com>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>
Subject: [PATCH v2 01/94] KVM: arm64: Move __load_guest_stage2 to kvm_mmu.h
Date: Tue, 11 Feb 2020 17:48:05 +0000
Message-Id: <20200211174938.27809-2-maz@kernel.org>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20200211174938.27809-1-maz@kernel.org>
References: <20200211174938.27809-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, andre.przywara@arm.com,
 christoffer.dall@arm.com, Dave.Martin@arm.com, jintack@cs.columbia.edu,
 alexandru.elisei@arm.com, james.morse@arm.com, julien.thierry.kdev@gmail.com,
 suzuki.poulose@arm.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Having __load_guest_stage2 in kvm_hyp.h is quickly going to trigger
a circular include problem. In order to avoid this, let's move
it to kvm_mmu.h, where it will be a better fit anyway.

In the process, drop the __hyp_text annotation, which doesn't help
as the function is marked as __always_inline.

Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 arch/arm64/include/asm/kvm_hyp.h | 18 ------------------
 arch/arm64/include/asm/kvm_mmu.h | 17 +++++++++++++++++
 2 files changed, 17 insertions(+), 18 deletions(-)

```
#### [PATCH kvm-unit-tests] arm64: timer: Speed up gic-timer-state check
##### From: Andrew Jones <drjones@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11375369
Return-Path: <SRS0=UyAS=37=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 409E8138D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 11 Feb 2020 12:35:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1E88F20873
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 11 Feb 2020 12:35:30 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="QQXq1/Oo"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728521AbgBKMfa (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 11 Feb 2020 07:35:30 -0500
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:50988 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1728031AbgBKMf3 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 11 Feb 2020 07:35:29 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1581424529;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=SvgnBksltlfdKTQjesT7j5JDJyAmqiI6NDbtZfxaBYc=;
        b=QQXq1/OoeobxBPDl6j3B5I1tadgyW1YEXwsq4mHwMSHTEIXIuZjPzWxIV9CGFclNA3t/t5
        HP4X9patdwnrDvu4ES0l9u0qe7rlnWHIRloUCno5wj854CmVm1R+O0TqLzpKIWt3LcZJrk
        iOnGyYOFgm/600OST0T8WRr7eYgarvk=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-393-p6630gJaMpGBbeTuArspaw-1; Tue, 11 Feb 2020 07:35:25 -0500
X-MC-Unique: p6630gJaMpGBbeTuArspaw-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 2CAF9477;
        Tue, 11 Feb 2020 12:35:24 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.43.2.160])
        by smtp.corp.redhat.com (Postfix) with ESMTP id A15976055B;
        Tue, 11 Feb 2020 12:35:22 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu
Cc: alexandru.elisei@arm.com, yuzenghui@huawei.com
Subject: [PATCH kvm-unit-tests] arm64: timer: Speed up gic-timer-state check
Date: Tue, 11 Feb 2020 13:35:21 +0100
Message-Id: <20200211123521.13637-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Let's bail out of the wait loop if we see the expected state
to save about seven seconds of run time. Make sure we wait a
bit before reading the registers, though, to somewhat mitigate
the chance of the expected state being stale.

Signed-off-by: Andrew Jones <drjones@redhat.com>
---
 arm/timer.c | 17 ++++++++++-------
 1 file changed, 10 insertions(+), 7 deletions(-)

```
#### [PATCH kvm-unit-tests v2] arm64: timer: Speed up gic-timer-state check
##### From: Andrew Jones <drjones@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11375517
Return-Path: <SRS0=UyAS=37=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D3494921
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 11 Feb 2020 13:37:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B2AD620848
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 11 Feb 2020 13:37:15 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="XCoLoi91"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728245AbgBKNhP (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 11 Feb 2020 08:37:15 -0500
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:55565 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1728091AbgBKNhO (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 11 Feb 2020 08:37:14 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1581428233;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=Nx7UfFP0sIiH35S7kPPK91DRlS1gGk3KRmm0NaUAgl4=;
        b=XCoLoi91gJUR2zOyu+o1ao+8Nv16cDzuosEdCzwJfaEfLOrPXiRx5NuRx7FqGtHwIRcsln
        heZ6mEQLGjjk1XyyVgRmZxgfRPpkKvOgfYm1lWm+FU3oTwMb4nOKrv8WP096zIzKmQBgN5
        bGCYfVkYPfG7/jRW7ParPhUt5Dr0qSc=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-58-mwDLRYU3N7G8fTlDMoOOWg-1; Tue, 11 Feb 2020 08:37:09 -0500
X-MC-Unique: mwDLRYU3N7G8fTlDMoOOWg-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 274ED1005514;
        Tue, 11 Feb 2020 13:37:08 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.43.2.160])
        by smtp.corp.redhat.com (Postfix) with ESMTP id B9D8887B34;
        Tue, 11 Feb 2020 13:37:06 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu
Cc: alexandru.elisei@arm.com, yuzenghui@huawei.com
Subject: [PATCH kvm-unit-tests v2] arm64: timer: Speed up gic-timer-state
 check
Date: Tue, 11 Feb 2020 14:37:05 +0100
Message-Id: <20200211133705.1398-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Let's bail out of the wait loop if we see the expected state
to save over six seconds of run time. Make sure we wait a bit
before reading the registers and double check again after,
though, to somewhat mitigate the chance of seeing the expected
state by accident.

We also take this opportunity to push more IRQ state code to
the library.

Signed-off-by: Andrew Jones <drjones@redhat.com>
Reviewed-by: Alexandru Elisei <alexandru.elisei@arm.com>
Reviewed-by: Zenghui Yu <yuzenghui@huawei.com>
Tested-by: Zenghui Yu <yuzenghui@huawei.com>
---
 arm/timer.c       | 30 ++++++++++++------------------
 lib/arm/asm/gic.h | 11 ++++++-----
 lib/arm/gic.c     | 33 +++++++++++++++++++++++++++++++++
 3 files changed, 51 insertions(+), 23 deletions(-)

```
#### [PATCH] KVM: x86: do not reset microcode version on INIT or RESET
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11376407
Return-Path: <SRS0=UyAS=37=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9F5EC924
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 11 Feb 2020 18:04:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7E22C20714
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 11 Feb 2020 18:04:47 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="I87ccuce"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730160AbgBKSEo (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 11 Feb 2020 13:04:44 -0500
Received: from mail-wr1-f67.google.com ([209.85.221.67]:39891 "EHLO
        mail-wr1-f67.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728712AbgBKSEo (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 11 Feb 2020 13:04:44 -0500
Received: by mail-wr1-f67.google.com with SMTP id y11so13596092wrt.6;
        Tue, 11 Feb 2020 10:04:42 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:subject:date:message-id;
        bh=q8IlFsAzW42BdHawcbUm+vPgezsGHOH9GeI0fUJDSVM=;
        b=I87ccuceFBGwZWz6MWVVHLS9yZqJ4oxZ8rVMt3h/dieBPIXmTksaUGIK9emDsbPJ72
         72KObeNgooFPdyUFIkNE9tfG9YCQT6DX97igWnoTk5XILeoDrV7XmBmNHZ6wxbM8Pmtd
         ZWogo0fjRb3v4pOrlrDwa/TkzDxv79WtPnZGLikTvYVSmqKOdPgekvANTruoPe8hQVKg
         Q8ke+MOLP8bEfh1RqNNqqj250UkVxF57F9Nw8ItyeGJqfXF0ht/pwYs3rJ8NaEpULXf7
         4shrJgs+Hi1V6e1ec38bHvO7j+2I/5AcC3i48ib6FRo+YneO8Psd2BR1w1z+iHS0GGNP
         T6Vw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:subject:date:message-id;
        bh=q8IlFsAzW42BdHawcbUm+vPgezsGHOH9GeI0fUJDSVM=;
        b=ZTFCevzZLRLYONXoarrtdgaFG+qMN6VxIt7PBilJy3UOKW4tQCEpUL/7qA60CNe6pZ
         mlTrYp5fDU4FyCUbjlXe4dx/yxsIIir7pasBqevJ2eKBVnnbAVBqNRGg39+js6lyKmaS
         F0C2zVr0VIewR5aJhL9TkWtLVc/dbaDKHiMijGJApR2YExzJR35wbme5EcXz/U6DqVBr
         jtvzrlF7+1OdwN0FoqTF/2SW87vAPbIsjdADPKnaqgBsUMBoN/AYxZRrc4juSGKicgV5
         aWmCWd325/f21woo4fVZcNTy1IrWJQG78tRXhaWFbqHXUk4HJ9b921IJkOMk+DvlaTMZ
         gRgA==
X-Gm-Message-State: APjAAAUGacB7d3EcZO27bNCwchIJjs35NH0FEfcZP+BFXRWwziORzaiB
        ScbXnaveeogU/BA+bbAusiXB+BlX
X-Google-Smtp-Source: 
 APXvYqyhLYqPjSzy0F1s0h9EYZQPJT9P7yUxxdFIy+Dr2hO87FpztILGHBFxMSyYce9J9y6V8rVzgQ==
X-Received: by 2002:adf:e8c9:: with SMTP id k9mr9870271wrn.168.1581444281212;
        Tue, 11 Feb 2020 10:04:41 -0800 (PST)
Received: from 640k.lan ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 h128sm168982wmh.33.2020.02.11.10.04.40
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Tue, 11 Feb 2020 10:04:40 -0800 (PST)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [PATCH] KVM: x86: do not reset microcode version on INIT or RESET
Date: Tue, 11 Feb 2020 19:04:39 +0100
Message-Id: <1581444279-10033-1-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The microcode version should be set just once, since it is essentially
a CPU feature; so do it on vCPU creation rather than reset.

Userspace can tie the fix to the availability of MSR_IA32_UCODE_REV in
the list of emulated MSRs.

Reported-by: Alex Williamson <alex.williamson@redhat.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/svm.c     | 2 +-
 arch/x86/kvm/vmx/vmx.c | 2 +-
 2 files changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH 01/62] KVM: SVM: Add GHCB definitions
##### From: Joerg Roedel <joro@8bytes.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Joerg Roedel <joro@8bytes.org>
X-Patchwork-Id: 11375671
Return-Path: <SRS0=UyAS=37=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8344C13A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 11 Feb 2020 13:59:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 634972173E
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 11 Feb 2020 13:59:24 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729390AbgBKNxJ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 11 Feb 2020 08:53:09 -0500
Received: from 8bytes.org ([81.169.241.247]:51778 "EHLO theia.8bytes.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729384AbgBKNxI (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 11 Feb 2020 08:53:08 -0500
Received: by theia.8bytes.org (Postfix, from userid 1000)
        id 57E762F0; Tue, 11 Feb 2020 14:53:07 +0100 (CET)
From: Joerg Roedel <joro@8bytes.org>
To: x86@kernel.org
Cc: hpa@zytor.com, Andy Lutomirski <luto@kernel.org>,
        Dave Hansen <dave.hansen@linux.intel.com>,
        Peter Zijlstra <peterz@infradead.org>,
        Thomas Hellstrom <thellstrom@vmware.com>,
        Jiri Slaby <jslaby@suse.cz>,
        Dan Williams <dan.j.williams@intel.com>,
        Tom Lendacky <thomas.lendacky@amd.com>,
        Juergen Gross <jgross@suse.com>,
        Kees Cook <keescook@chromium.org>,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org,
        Joerg Roedel <joro@8bytes.org>, Joerg Roedel <jroedel@suse.de>
Subject: [PATCH 01/62] KVM: SVM: Add GHCB definitions
Date: Tue, 11 Feb 2020 14:51:55 +0100
Message-Id: <20200211135256.24617-2-joro@8bytes.org>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200211135256.24617-1-joro@8bytes.org>
References: <20200211135256.24617-1-joro@8bytes.org>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Tom Lendacky <thomas.lendacky@amd.com>

Extend the vmcb_safe_area with SEV-ES fields and add a new
'struct ghcb' which will be used for guest-hypervisor communication.

Signed-off-by: Tom Lendacky <thomas.lendacky@amd.com>
Signed-off-by: Joerg Roedel <jroedel@suse.de>
---
 arch/x86/include/asm/svm.h | 42 ++++++++++++++++++++++++++++++++++++++
 1 file changed, 42 insertions(+)

```
#### [PATCH v17 1/9] mm: Adjust shuffle code to allow for future coalescing
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Duyck <alexander.duyck@gmail.com>
X-Patchwork-Id: 11377029
Return-Path: <SRS0=UyAS=37=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E62BB1580
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 11 Feb 2020 22:46:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id BC49620842
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 11 Feb 2020 22:46:14 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="FbcHNTAc"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727668AbgBKWqL (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 11 Feb 2020 17:46:11 -0500
Received: from mail-wr1-f67.google.com ([209.85.221.67]:41282 "EHLO
        mail-wr1-f67.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727549AbgBKWqK (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 11 Feb 2020 17:46:10 -0500
Received: by mail-wr1-f67.google.com with SMTP id c9so14624039wrw.8;
        Tue, 11 Feb 2020 14:46:09 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=subject:from:to:cc:date:message-id:in-reply-to:references
         :user-agent:mime-version:content-transfer-encoding;
        bh=umJOijGEv1easm1z5ldt6/FMaBLvZ4Knoos61QS3/A0=;
        b=FbcHNTAcLoUcLHlS3D6lF5/4k+MqR5ciridY9PM8sctd4ZK3PhcAWaD5cLSoPWS8rK
         3RQSMd7XMdd3jrnAjxp56HW5TWjLfOIHmYLKlApYhVWtyOXB0RR4RhPcyT/61wLEJI00
         hajuFr77kf3/mpT7r40EhUCm4Slr+BR/xNslvlCHChnxBSaiTBgcDZQMw6cyKHvjN/+q
         2/Xy8sa+ezI3uUFcRolm4QVu8uAAF3H9niBs4QqWcpfsCHfmKAdV8iYxI7eqPklBicLF
         rTBdmEIapsrNSNHbOFSSPQGcnw1oK78F29TF/Kn/ew8GQrBz+ngcUjw3ji+CV2jyiPmk
         vrpQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:subject:from:to:cc:date:message-id:in-reply-to
         :references:user-agent:mime-version:content-transfer-encoding;
        bh=umJOijGEv1easm1z5ldt6/FMaBLvZ4Knoos61QS3/A0=;
        b=kI1fme8IX6mIr/mTqjWMDYGEXkCAKMmBRRQUljpFb3l3BJJaso4Am2tLYjKNsTIkVb
         iSikFGz4Cv8ZGZheqCjLJp+PYcDYA6FUTGTr6x2mQvoYp87YH31Hv6FPXKYT3vAtdN2J
         CTeHaDHEp10TKeh3qAWMsfcR31IRWtnQmPMzsBoIx6j7EvWjqjyiCg8ZKBgNZDWAwzk0
         v2X4Nf8tHrI76OjzFE+Y9tCKD7+SYD9Md12B0txZfsEEBsMhaAO7Svsf/nsrg/96hlyP
         70mYLozOcSVPljDZ1QVcx7pOvZ9iDW4Yqi/dMMnwUhF9V/dYsMycpNVR5pXuD6zO/Zux
         vWXw==
X-Gm-Message-State: APjAAAVuybSyeU8ri0byqzQyFCSLSKCuN80QAJigMEjcyLFO5ypjl25r
        IbviUViJkrLfM0try/XWC1I=
X-Google-Smtp-Source: 
 APXvYqxJz4EiIxr6iFRbuoCKcPodjqLlxdt+r1SuBMbn7NJJ9unloGs6fgx9hYNWkOr4NgYduTF0Qg==
X-Received: by 2002:adf:cd04:: with SMTP id w4mr11630017wrm.219.1581461168567;
        Tue, 11 Feb 2020 14:46:08 -0800 (PST)
Received: from localhost.localdomain ([2001:470:b:9c3:9e5c:8eff:fe4f:f2d0])
        by smtp.gmail.com with ESMTPSA id
 a62sm5740338wmh.33.2020.02.11.14.46.04
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Tue, 11 Feb 2020 14:46:07 -0800 (PST)
Subject: [PATCH v17 1/9] mm: Adjust shuffle code to allow for future
 coalescing
From: Alexander Duyck <alexander.duyck@gmail.com>
To: kvm@vger.kernel.org, david@redhat.com, mst@redhat.com,
        linux-kernel@vger.kernel.org, linux-mm@kvack.org,
        akpm@linux-foundation.org, mgorman@techsingularity.net
Cc: yang.zhang.wz@gmail.com, pagupta@redhat.com,
        konrad.wilk@oracle.com, nitesh@redhat.com, riel@surriel.com,
        willy@infradead.org, lcapitulino@redhat.com, dave.hansen@intel.com,
        wei.w.wang@intel.com, aarcange@redhat.com, pbonzini@redhat.com,
        dan.j.williams@intel.com, mhocko@kernel.org,
        alexander.h.duyck@linux.intel.com, vbabka@suse.cz,
        osalvador@suse.de
Date: Tue, 11 Feb 2020 14:46:02 -0800
Message-ID: <20200211224602.29318.84523.stgit@localhost.localdomain>
In-Reply-To: <20200211224416.29318.44077.stgit@localhost.localdomain>
References: <20200211224416.29318.44077.stgit@localhost.localdomain>
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
#### [RFC PATCH 1/2] KVM: CPUID: Enable supervisor XSAVE states in CPUID enumeration and XSS
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Weijiang <weijiang.yang@intel.com>
X-Patchwork-Id: 11374881
Return-Path: <SRS0=UyAS=37=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0FD5C109A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 11 Feb 2020 06:53:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id DD84C206D7
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 11 Feb 2020 06:53:10 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727966AbgBKGxJ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 11 Feb 2020 01:53:09 -0500
Received: from mga11.intel.com ([192.55.52.93]:28362 "EHLO mga11.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727768AbgBKGxJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 11 Feb 2020 01:53:09 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga005.jf.intel.com ([10.7.209.41])
  by fmsmga102.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 10 Feb 2020 22:53:08 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,427,1574150400";
   d="scan'208";a="405848668"
Received: from local-michael-cet-test.sh.intel.com ([10.239.159.128])
  by orsmga005.jf.intel.com with ESMTP; 10 Feb 2020 22:53:06 -0800
From: Yang Weijiang <weijiang.yang@intel.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com,
        sean.j.christopherson@intel.com, jmattson@google.com,
        aaronlewis@google.com
Cc: Yang Weijiang <weijiang.yang@intel.com>
Subject: [RFC PATCH 1/2] KVM: CPUID: Enable supervisor XSAVE states in CPUID
 enumeration and XSS
Date: Tue, 11 Feb 2020 14:57:05 +0800
Message-Id: <20200211065706.3462-1-weijiang.yang@intel.com>
X-Mailer: git-send-email 2.17.2
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

CPUID.(EAX=DH, ECX={i}H i>=0) enumerates XSAVE related leaves/sub-leaves,
but supervisor states are not taken into account. Meanwhile,more and more
new features, e.g., CET, PT, LBR, rely on supervisor states to enhance
performance, so updating related KVM code becomes necessary.

With Aaron Lewis's <aaronlewis@google.com> patches in place, i.e.,
{c90992bfb080, 52297436199d, 864e2ab2b46d, 139a12cfe1a0, 9753d68865c5,
312a1c87798e, 78958563d802, c034f2aa8622, 7204160eb780}, this patch
is to enable suppervisor XSAVE states support in CPUID enumeration and
MSR IA32_XSS. KVM_SUPPORTED_XSS is a static mask for KVM/Guest supervisor
states and guest_supported_xss is a dynamic mask which consolidates
current host IA32_XSS and QEMU configuration together with static mask.

Right now, supervisor states in IA32_XSS haven't been used in upstreamed
KVM code, so set KVM_SUPPORTED_XSS to 0 in the patch, new XSAVES related
features can expand the macro to enable save/restore with XSAVES/XSTORS
instruction.

To test the patch, I first set the KVM_SUPPORTED_XSS to 0x3900 and inject
value to IA32_XSS too, 0x3900 corresponds to the most recent possible
candidate supervisor states on Intel platforms, tested on TGL platform as
results below:

cpuid.[d.0]: eax = 0x000002e7, ebx = 0x00000a88, ecx = 0x00000a88, edx = 0x00000000
cpuid.[d.1]: eax = 0x0000000f, ebx = 0x00000a38, ecx = 0x00003900, edx = 0x00000000
cpuid.[d.2]: eax = 0x00000100, ebx = 0x00000240, ecx = 0x00000000, edx = 0x00000000
cpuid.[d.5]: eax = 0x00000040, ebx = 0x00000440, ecx = 0x00000000, edx = 0x00000000
cpuid.[d.6]: eax = 0x00000200, ebx = 0x00000480, ecx = 0x00000000, edx = 0x00000000
cpuid.[d.7]: eax = 0x00000400, ebx = 0x00000680, ecx = 0x00000000, edx = 0x00000000
cpuid.[d.8]: eax = 0x00000080, ebx = 0x00000000, ecx = 0x00000001, edx = 0x00000000
cpuid.[d.9]: eax = 0x00000008, ebx = 0x00000a80, ecx = 0x00000000, edx = 0x00000000
cpuid.[d.11]: eax = 0x00000010, ebx = 0x00000000, ecx = 0x00000001, edx = 0x00000000
cpuid.[d.12]: eax = 0x00000018, ebx = 0x00000000, ecx = 0x00000001, edx = 0x00000000
cpuid.[d.13]: eax = 0x00000008, ebx = 0x00000000, ecx = 0x00000001, edx = 0x00000000
bit[8] in MSR_IA32_XSS is supported
bit[11] in MSR_IA32_XSS is supported
bit[12] in MSR_IA32_XSS is supported
bit[13] in MSR_IA32_XSS is supported
Supported bit mask in MSR_IA32_XSS is : 0x3900

When IA32_XSS and KVM_SUPPORTED_XSS are 0, got below output:
cpuid.[d.0]: eax = 0x000002e7, ebx = 0x00000a88, ecx = 0x00000a88, edx = 0x00000000
cpuid.[d.1]: eax = 0x0000000f, ebx = 0x00000988, ecx = 0x00000000, edx = 0x00000000
cpuid.[d.2]: eax = 0x00000100, ebx = 0x00000240, ecx = 0x00000000, edx = 0x00000000
cpuid.[d.5]: eax = 0x00000040, ebx = 0x00000440, ecx = 0x00000000, edx = 0x00000000
cpuid.[d.6]: eax = 0x00000200, ebx = 0x00000480, ecx = 0x00000000, edx = 0x00000000
cpuid.[d.7]: eax = 0x00000400, ebx = 0x00000680, ecx = 0x00000000, edx = 0x00000000
cpuid.[d.9]: eax = 0x00000008, ebx = 0x00000a80, ecx = 0x00000000, edx = 0x00000000
Supported bit mask in MSR_IA32_XSS is : 0x0

Signed-off-by: Yang Weijiang <weijiang.yang@intel.com>
---
 arch/x86/include/asm/kvm_host.h |   1 +
 arch/x86/kvm/cpuid.c            | 111 ++++++++++++++++++++++----------
 arch/x86/kvm/x86.c              |   4 +-
 arch/x86/kvm/x86.h              |   8 +++
 4 files changed, 87 insertions(+), 37 deletions(-)

```
#### [PATCH v17 QEMU 1/3] virtio-ballon: Implement support for page poison tracking feature
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Duyck <alexander.duyck@gmail.com>
X-Patchwork-Id: 11377065
Return-Path: <SRS0=UyAS=37=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7AAFC13A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 11 Feb 2020 22:51:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 502272082F
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 11 Feb 2020 22:51:26 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="tkJ7Jpuj"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727729AbgBKWvX (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 11 Feb 2020 17:51:23 -0500
Received: from mail-wr1-f48.google.com ([209.85.221.48]:45404 "EHLO
        mail-wr1-f48.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727199AbgBKWvX (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 11 Feb 2020 17:51:23 -0500
Received: by mail-wr1-f48.google.com with SMTP id g3so13519339wrs.12;
        Tue, 11 Feb 2020 14:51:20 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=subject:from:to:cc:date:message-id:in-reply-to:references
         :user-agent:mime-version:content-transfer-encoding;
        bh=V78oNbusAm5S3e7SX3vKPs7Z58CB44qhuhwypR7BDJE=;
        b=tkJ7JpujzDe/vkZ7f0cEcHQmCX/gFd6QYBQA87yNi8nsa73sXyMOvE9gt0JKVqF/r/
         KTFdJ8XrayTXODVP0ZiabnUGNw1sY5YptGY7Rtg+9WsToxeWxCw5FAzPSnYdQSbQPfpo
         Mw6eydDn+0mEwIVWLLN/j9SFgokKtCPEAnp8jgsuldgU1t6z3w9+DvoonjlyjSbzxfUv
         XyzRFsOezR4J7SqKC5wTkWiFkqzMVpJXClvc28OB8BNSdJPj2J4FYCjWq6niTxbg0GYP
         LnB2Hl/XE7Wp+INlpdJw/YIlure+u3hxuLlnHMbBnGccGd/X3+tqDF9tQ6haf7O9VI9S
         CRaQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:subject:from:to:cc:date:message-id:in-reply-to
         :references:user-agent:mime-version:content-transfer-encoding;
        bh=V78oNbusAm5S3e7SX3vKPs7Z58CB44qhuhwypR7BDJE=;
        b=pnSwFWlQ+0r/xoMB2zSbSTr55IvdHFWu7HcfIDtcRwBKCuS1NlTjAV/TSozGKTMKIv
         S7LAJVEZzTMg2Fuv5H+1c1lLuevgChBxNIqx9BffS7KIMfBwBmK0dSy6Nxi38v6BsWej
         LNpA2HLQ6DrcWNzHYAcaXipr5aQUSPGfdMfopf/26ehcRrImgfXaFhfwv3YXj8knFmhp
         B+0QkDt60LV9diFBJxX1m3ya7wZ3w0URqKacw/Kj75rOIwLTxxUXO6EsPSXkUQ9aPuEz
         5SR7WbMXd4geqPSHjSgDZPexu2O85VZXn2RPfEJxsOOttFDrLPs0LDlcQqff5r6q9wpl
         LpCw==
X-Gm-Message-State: APjAAAVgB/1jpNGrcXONndne1UnCyEkSNS4wh90L2/8jAwVHC0oHNTy9
        +RZPxhuaSigT9nsfSL2RlUs=
X-Google-Smtp-Source: 
 APXvYqyWvUNn0Zh0X0txT2rjYhlQesS3m83PdisyyeVh5FX2cc1ZW1sF6ykII9WMGQUBmq25CcQqBw==
X-Received: by 2002:a5d:4692:: with SMTP id
 u18mr11162348wrq.206.1581461480116;
        Tue, 11 Feb 2020 14:51:20 -0800 (PST)
Received: from localhost.localdomain ([2001:470:b:9c3:9e5c:8eff:fe4f:f2d0])
        by smtp.gmail.com with ESMTPSA id
 r1sm6869786wrx.11.2020.02.11.14.51.15
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Tue, 11 Feb 2020 14:51:19 -0800 (PST)
Subject: [PATCH v17 QEMU 1/3] virtio-ballon: Implement support for page
 poison tracking feature
From: Alexander Duyck <alexander.duyck@gmail.com>
To: virtio-dev@lists.oasis-open.org, kvm@vger.kernel.org,
        mst@redhat.com, david@redhat.com, linux-kernel@vger.kernel.org,
        linux-mm@kvack.org, akpm@linux-foundation.org
Cc: yang.zhang.wz@gmail.com, pagupta@redhat.com,
        konrad.wilk@oracle.com, nitesh@redhat.com, riel@surriel.com,
        willy@infradead.org, lcapitulino@redhat.com, dave.hansen@intel.com,
        wei.w.wang@intel.com, aarcange@redhat.com, pbonzini@redhat.com,
        dan.j.williams@intel.com, mhocko@kernel.org,
        mgorman@techsingularity.net, alexander.h.duyck@linux.intel.com,
        vbabka@suse.cz, osalvador@suse.de
Date: Tue, 11 Feb 2020 14:51:14 -0800
Message-ID: <20200211225114.30409.17424.stgit@localhost.localdomain>
In-Reply-To: <20200211224416.29318.44077.stgit@localhost.localdomain>
References: <20200211224416.29318.44077.stgit@localhost.localdomain>
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
#### [PATCH v2 RFC] KVM: s390/interrupt: do not pin adapter interrupt pages
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11375099
Return-Path: <SRS0=UyAS=37=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 74F1E14E3
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 11 Feb 2020 09:23:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4CA8A20848
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 11 Feb 2020 09:23:56 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727665AbgBKJXz (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 11 Feb 2020 04:23:55 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:3230 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727121AbgBKJXz (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 11 Feb 2020 04:23:55 -0500
Received: from pps.filterd (m0098409.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 01B9JKiK120432;
        Tue, 11 Feb 2020 04:23:51 -0500
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2y3pqf5ebj-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 11 Feb 2020 04:23:51 -0500
Received: from m0098409.ppops.net (m0098409.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 01B9K2nL122629;
        Tue, 11 Feb 2020 04:23:51 -0500
Received: from ppma02dal.us.ibm.com (a.bd.3ea9.ip4.static.sl-reverse.com
 [169.62.189.10])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2y3pqf5eb5-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 11 Feb 2020 04:23:51 -0500
Received: from pps.filterd (ppma02dal.us.ibm.com [127.0.0.1])
        by ppma02dal.us.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 01B9MhJU003454;
        Tue, 11 Feb 2020 09:23:50 GMT
Received: from b03cxnp08026.gho.boulder.ibm.com
 (b03cxnp08026.gho.boulder.ibm.com [9.17.130.18])
        by ppma02dal.us.ibm.com with ESMTP id 2y1mm7dn65-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 11 Feb 2020 09:23:50 +0000
Received: from b03ledav001.gho.boulder.ibm.com
 (b03ledav001.gho.boulder.ibm.com [9.17.130.232])
        by b03cxnp08026.gho.boulder.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 01B9NkD855640528
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 11 Feb 2020 09:23:46 GMT
Received: from b03ledav001.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id C6E6A6E052;
        Tue, 11 Feb 2020 09:23:46 +0000 (GMT)
Received: from b03ledav001.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id E09266E04C;
        Tue, 11 Feb 2020 09:23:45 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.114.17.106])
        by b03ledav001.gho.boulder.ibm.com (Postfix) with ESMTP;
        Tue, 11 Feb 2020 09:23:45 +0000 (GMT)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: david@redhat.com
Cc: Ulrich.Weigand@de.ibm.com, aarcange@redhat.com,
        akpm@linux-foundation.org, borntraeger@de.ibm.com,
        cohuck@redhat.com, frankja@linux.vnet.ibm.com, gor@linux.ibm.com,
        imbrenda@linux.ibm.com, kvm@vger.kernel.org, linux-mm@kvack.org,
        linux-s390@vger.kernel.org, mimu@linux.ibm.com, thuth@redhat.com
Subject: [PATCH v2 RFC] KVM: s390/interrupt: do not pin adapter interrupt
 pages
Date: Tue, 11 Feb 2020 04:23:41 -0500
Message-Id: <20200211092341.3965-1-borntraeger@de.ibm.com>
X-Mailer: git-send-email 2.24.0
In-Reply-To: <567B980B-BDA5-4EF3-A96E-1542D11F2BD4@redhat.com>
References: <567B980B-BDA5-4EF3-A96E-1542D11F2BD4@redhat.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-02-11_02:2020-02-10,2020-02-11 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 impostorscore=0 clxscore=1015
 bulkscore=0 malwarescore=0 mlxlogscore=841 adultscore=0 spamscore=0
 lowpriorityscore=0 mlxscore=0 suspectscore=4 phishscore=0
 priorityscore=1501 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2001150001 definitions=main-2002110069
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Ulrich Weigand <Ulrich.Weigand@de.ibm.com>

The adapter interrupt page containing the indicator bits is currently
pinned. That means that a guest with many devices can pin a lot of
memory pages in the host. This also complicates the reference tracking
which is needed for memory management handling of protected virtual
machines.
We can simply try to get the userspace page set the bits and free the
page. By storing the userspace address in the irq routing entry instead
of the guest address we can actually avoid many lookups and list walks
so that this variant is very likely not slower.

Signed-off-by: Ulrich Weigand <Ulrich.Weigand@de.ibm.com>
[borntraeger@de.ibm.com: patch simplification]
Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
quick and dirty, how this could look like


 arch/s390/include/asm/kvm_host.h |   3 -
 arch/s390/kvm/interrupt.c        | 146 +++++++++++--------------------
 2 files changed, 49 insertions(+), 100 deletions(-)

```
#### [PATCH 1/7] vfio: Include optional device match in vfio_device_ops callbacks
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alex Williamson <alex.williamson@redhat.com>
X-Patchwork-Id: 11377099
Return-Path: <SRS0=UyAS=37=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 85489921
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 11 Feb 2020 23:05:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 657F020848
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 11 Feb 2020 23:05:35 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="AUHJ/TVI"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727835AbgBKXFe (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 11 Feb 2020 18:05:34 -0500
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:33067 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1727806AbgBKXFd (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 11 Feb 2020 18:05:33 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1581462333;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=QeJkTOJSqucr7TuGuD5+LQV+rMV+lFuwF5Rz1IX0QZ4=;
        b=AUHJ/TVItGI7dWtbt+QURvfIUHetC0IhReML0kP2YgwYqKu00KH/dZ/kqFEcaP8S5ohycJ
        LdzIxLRgq2penhH0n1+xRP1IT3Oz9GDw0icetmwbO5CsJKF9ZIbvzdkXHR2RQoQmWAu9nr
        3LdY/57Lo9GQLN0Y3WrUmZxZZVqekOk=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-383-HcVH2L5WMN-9KW4I4nN_ww-1; Tue, 11 Feb 2020 18:05:31 -0500
X-MC-Unique: HcVH2L5WMN-9KW4I4nN_ww-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 288951005502;
        Tue, 11 Feb 2020 23:05:29 +0000 (UTC)
Received: from gimli.home (ovpn-116-28.phx2.redhat.com [10.3.116.28])
        by smtp.corp.redhat.com (Postfix) with ESMTP id E2CCF26FAA;
        Tue, 11 Feb 2020 23:05:25 +0000 (UTC)
Subject: [PATCH 1/7] vfio: Include optional device match in vfio_device_ops
 callbacks
From: Alex Williamson <alex.williamson@redhat.com>
To: kvm@vger.kernel.org
Cc: linux-pci@vger.kernel.org, linux-kernel@vger.kernel.org,
        dev@dpdk.org, mtosatti@redhat.com, thomas@monjalon.net,
        bluca@debian.org, jerinjacobk@gmail.com,
        bruce.richardson@intel.com, cohuck@redhat.com
Date: Tue, 11 Feb 2020 16:05:25 -0700
Message-ID: <158146232551.16827.14170770732904274160.stgit@gimli.home>
In-Reply-To: <158145472604.16827.15751375540102298130.stgit@gimli.home>
References: <158145472604.16827.15751375540102298130.stgit@gimli.home>
User-Agent: StGit/0.19-dirty
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Allow bus drivers to provide their own callback to match a device to
the user provided string.

Signed-off-by: Alex Williamson <alex.williamson@redhat.com>
---
 drivers/vfio/vfio.c  |   20 ++++++++++++++++----
 include/linux/vfio.h |    4 ++++
 2 files changed, 20 insertions(+), 4 deletions(-)

```
