#### [PATCH v3 01/21] vfio: introduce vfio_iova_rw to read/write a range of IOVAs
##### From: Peter Xu <peterx@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11325885
Return-Path: <SRS0=hq+s=26=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 116DA1398
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Jan 2020 14:57:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D8B192072E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Jan 2020 14:57:40 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="I4vxO4kv"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731904AbgAIO5k (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 9 Jan 2020 09:57:40 -0500
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:42830 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1728737AbgAIO5j (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 9 Jan 2020 09:57:39 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1578581858;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=gDGiLHLaS/+Io2Phnnfgd/F37FeteIfvFFEQMfXM9RA=;
        b=I4vxO4kvES6dyJp5GiiSzsDObNjvHp0j4hy8RSvzfW0CN1JF9lxD593H9eC98Tk2Bhe/gZ
        +num04urfX6sZ0+n+oXUrIcUCHTRreqQDi11C1RZhsukR2gptTRjH+On0fcQYIfSdFQq7x
        MYdTeVVX2GjllxUqGUVwGKUHEgSe7hA=
Received: from mail-qv1-f71.google.com (mail-qv1-f71.google.com
 [209.85.219.71]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-368-JBvgo9C2MTuTk0hsVIUiFg-1; Thu, 09 Jan 2020 09:57:37 -0500
X-MC-Unique: JBvgo9C2MTuTk0hsVIUiFg-1
Received: by mail-qv1-f71.google.com with SMTP id v5so4250765qvn.21
        for <kvm@vger.kernel.org>; Thu, 09 Jan 2020 06:57:36 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=gDGiLHLaS/+Io2Phnnfgd/F37FeteIfvFFEQMfXM9RA=;
        b=H1zPXitV4HzVekxKQ/O3Kf9Oh70lxDhh0TKB4+2yB5e5dPqG7Gwl7zkT3aHJ4aqhvj
         fCI0AvM4iZT28LXfF/Q7krgOrkjIk6TJM9Eom2Hni9A0RGfNMqrK3jc15XmIEYVxL1tU
         boutkVjdi/LYeqSFvUrxgTQCW0xZyAoj8vWKdiDwqh4Y3Ko8x3xZ8vY+10h+Za+zl6Oc
         y+2FWr9bcPDp6A7JbxOopNgbpzttnsqxzRf91CdDToV/D/C3MkOB9X2BpHvo+r/fhOSZ
         KoTfjLF2boZd44Hvkh1NfdAg8dnePR6Pa8dEFw7o+FqN9o4UxgrzYWIA35+QQNfgNMKU
         AOJw==
X-Gm-Message-State: APjAAAWd/TkpKehRjQaJ+U39ReTkiYvIYhxHVEYOzZLlXgCzNj/eSrpE
        98aw9W2CUmQdKSCumZKp515TDXFBHwFX6TEGvPYoCS4Dt21qZ9Z66ICc1dTcgDpz0yVdwxwaDlf
        3sM/l+nmlJaYS
X-Received: by 2002:a05:620a:102e:: with SMTP id
 a14mr9510823qkk.159.1578581855559;
        Thu, 09 Jan 2020 06:57:35 -0800 (PST)
X-Google-Smtp-Source: 
 APXvYqw9fW22cpWNa0ej5q9Tvxem01vg3v97AmZT7K2M9MRr1qsTUoG9MFfgUMx1bfEecySbeqsNlQ==
X-Received: by 2002:a05:620a:102e:: with SMTP id
 a14mr9510799qkk.159.1578581855290;
        Thu, 09 Jan 2020 06:57:35 -0800 (PST)
Received: from xz-x1.yyz.redhat.com ([104.156.64.74])
        by smtp.gmail.com with ESMTPSA id q2sm3124179qkm.5.2020.01.09.06.57.32
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 09 Jan 2020 06:57:33 -0800 (PST)
From: Peter Xu <peterx@redhat.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: Christophe de Dinechin <dinechin@redhat.com>,
        "Michael S . Tsirkin" <mst@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Yan Zhao <yan.y.zhao@intel.com>,
        Alex Williamson <alex.williamson@redhat.com>,
        Jason Wang <jasowang@redhat.com>,
        Kevin Kevin <kevin.tian@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>, peterx@redhat.com,
        "Dr . David Alan Gilbert" <dgilbert@redhat.com>
Subject: [PATCH v3 01/21] vfio: introduce vfio_iova_rw to read/write a range
 of IOVAs
Date: Thu,  9 Jan 2020 09:57:09 -0500
Message-Id: <20200109145729.32898-2-peterx@redhat.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20200109145729.32898-1-peterx@redhat.com>
References: <20200109145729.32898-1-peterx@redhat.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Yan Zhao <yan.y.zhao@intel.com>

vfio_iova_rw will read/write a range of userspace memory (starting form
device iova to iova + len -1) into a kenrel buffer without pinning the
userspace memory.

TODO: vfio needs to mark the iova dirty if vfio_iova_rw(write) is
called.

Cc: Kevin Tian <kevin.tian@intel.com>
Signed-off-by: Yan Zhao <yan.y.zhao@intel.com>
Signed-off-by: Peter Xu <peterx@redhat.com>
---
 drivers/vfio/vfio.c             | 45 ++++++++++++++++++
 drivers/vfio/vfio_iommu_type1.c | 81 +++++++++++++++++++++++++++++++++
 include/linux/vfio.h            |  5 ++
 3 files changed, 131 insertions(+)

```
#### [PATCH] KVM: s390: check if kernel irqchip is actually enabled
##### From: Cornelia Huck <cohuck@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Cornelia Huck <cohuck@redhat.com>
X-Patchwork-Id: 11325711
Return-Path: <SRS0=hq+s=26=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 29236139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Jan 2020 13:47:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id F21822077B
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Jan 2020 13:47:26 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="OuiLXYR7"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731165AbgAINr0 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 9 Jan 2020 08:47:26 -0500
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:32228 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1725839AbgAINr0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 9 Jan 2020 08:47:26 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1578577644;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=wcxAGEZpymOZcLKXkHX/7V/8SWLuXIEYNtbnwOyzIC8=;
        b=OuiLXYR7g9xAinhmz30O6Ad6s2yAGh1lWZP6n9R2Wfivgcrgt9VzsNttdCNf/oNIaxyZqa
        JevgtJZ/yz81lhc4Z68Yv/HPZphh94VOvsufF7xQeaXTzMRTPS3pLH/xVpYm9TMHt8E47L
        FcgefttY7OXtI7yVotLBxY+007jB4Vs=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-267-z7PXUMgZPNK1HSE7hpByfw-1; Thu, 09 Jan 2020 08:47:21 -0500
X-MC-Unique: z7PXUMgZPNK1HSE7hpByfw-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 94E2B1088392;
        Thu,  9 Jan 2020 13:47:20 +0000 (UTC)
Received: from localhost (dhcp-192-245.str.redhat.com [10.33.192.245])
        by smtp.corp.redhat.com (Postfix) with ESMTPS id 8297D5DA2C;
        Thu,  9 Jan 2020 13:47:17 +0000 (UTC)
From: Cornelia Huck <cohuck@redhat.com>
To: Christian Borntraeger <borntraeger@de.ibm.com>,
        Janosch Frank <frankja@linux.ibm.com>
Cc: David Hildenbrand <david@redhat.com>, kvm@vger.kernel.org,
        linux-s390@vger.kernel.org, Cornelia Huck <cohuck@redhat.com>
Subject: [PATCH] KVM: s390: check if kernel irqchip is actually enabled
Date: Thu,  9 Jan 2020 14:47:13 +0100
Message-Id: <20200109134713.14755-1-cohuck@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

On s390, we only allow userspace to create an in-kernel irqchip
if it has first enabled the KVM_CAP_S390_IRQCHIP vm capability.
Let's assume that a userspace that enabled that capability has
created an irqchip as well.

Fixes: 84223598778b ("KVM: s390: irq routing for adapter interrupts.")
Signed-off-by: Cornelia Huck <cohuck@redhat.com>
---

A more precise check would be to add a field in kvm_arch that tracks
whether an irqchip has actually been created; not sure if that is
really needed.

Found while trying to hunt down QEMU crashes with kvm-irqchip=off;
this is not sufficient, though. I *think* everything but irqfds
should work without kvm-irqchip as well, but have not found the problem
yet.

---
 arch/s390/kvm/irq.h | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] KVM: squelch uninitialized variable warningFrom: Barret Rhoden <brho@google.com>
##### From: Barret Rhoden <brho@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Barret Rhoden <brho@google.com>
X-Patchwork-Id: 11326351
Return-Path: <SRS0=hq+s=26=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 784D3138D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Jan 2020 19:59:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 50ACC2067D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Jan 2020 19:59:07 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="S0pffzvI"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732904AbgAIT7D (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 9 Jan 2020 14:59:03 -0500
Received: from mail-qk1-f201.google.com ([209.85.222.201]:55829 "EHLO
        mail-qk1-f201.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1732883AbgAIT7D (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 9 Jan 2020 14:59:03 -0500
Received: by mail-qk1-f201.google.com with SMTP id f124so4885543qkb.22
        for <kvm@vger.kernel.org>; Thu, 09 Jan 2020 11:59:03 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=Jf5B4EbQ+30kjad3rYjf3nQGksGo1BPEiNIOzLgULXA=;
        b=S0pffzvIDcM3Erqu+B6kTPNDcpFqNGr5Lgn1Fru3tO/n7DHI2gxYrjybPEJWWCh8qJ
         Pq0rgh1x4T67aJo9Y/zOOMYHmaBy/jb6Su0M5dUAAiR9WjHyU+YkuKRtnzHYWGCyWKyE
         MqwTw1DzPgVrFVIXrMNlxC3ecz6b3un5RTrwDgI00pOnvxkf6Wy1J5pEUYd0lVc4izWr
         VWOj3Nyud4Ev6G1bkQDxfDiynv0ORLWJeBXNAAy1Xa4s5vRAYDSYRYx6SXZbxDu/s+fy
         17QqQeerEc+n7g0sUmMtpqMYLtTi71Zc7Mkp0zM6VJIhpvpLIV8t7L68BkFDNQTCyWfp
         85Kw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=Jf5B4EbQ+30kjad3rYjf3nQGksGo1BPEiNIOzLgULXA=;
        b=tsAgOBDpUTn3/vo0zxewHV5UmBYLRR2/dATR9qTcd2WzfseN0JrFIOkZLG+4xm0Vru
         /hRaW21Ur6KDyo5s/mZWOAx2eT0iC4NqOcPexOXxw0at2SVmXImxbU/HP8qug9xQdSxQ
         tlehjaJZ7mON7rv7CUAmG3cR9nSU5M6O+OtjoRysIZ0ZgG+R63fsbUoM94ZooXXjX5WK
         UtMrk0aL2FbekTLTnaw8gWAIDbHQfHcVsT6UqRz3su/dhAlcIGneS1vnmESE+8E/WNGc
         BQk3zWjCnn42XtXjv/qZFsydgVPHNgt63qkbowcSLFUob54JE/ScyoEwnVz9PyzATvTz
         H+TA==
X-Gm-Message-State: APjAAAVcwb8aGCbQduqYOhqEJF2Lmiv0VuLR7O7DTLg02JqKqV/lk1Os
        InfVj88LGLF9GyCnZSmxCrGFtLHD
X-Google-Smtp-Source: 
 APXvYqyFkOSjGrU2IETPDfcC3pAk3kZTILvTb6+kfTasc242E8aC+Ee9MsLPq6k3SOTw1KCiopXNnjnf
X-Received: by 2002:a37:e507:: with SMTP id e7mr11506262qkg.358.1578599942496;
 Thu, 09 Jan 2020 11:59:02 -0800 (PST)
Date: Thu,  9 Jan 2020 14:58:55 -0500
Message-Id: <20200109195855.17353-1-brho@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.25.0.rc1.283.g88dfdc4193-goog
Subject: [PATCH] KVM: squelch uninitialized variable warning
From: Barret Rhoden <brho@google.com>
To: pbonzini@redhat.com
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If gfn_to_hva_many() fails, __kvm_gfn_to_hva_cache_init() will return an
error.  Before it does, it might use nr_pages_avail, which my compiler
complained about:

	virt/kvm/kvm_main.c:2193:13: warning: 'nr_pages_avail' may be
	used uninitialized in this function [-Wmaybe-uninitialized]

	   start_gfn += nr_pages_avail;

Signed-off-by: Barret Rhoden <brho@google.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 virt/kvm/kvm_main.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH 01/15] target/arm/kvm: Use CPUState::kvm_state in kvm_arm_pmu_supported()
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
 <philmd@redhat.com>
X-Patchwork-Id: 11325943
Return-Path: <SRS0=hq+s=26=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 772A692A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Jan 2020 15:22:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4A5CD2072E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Jan 2020 15:22:05 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="ZqIs0MvK"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732318AbgAIPWE (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 9 Jan 2020 10:22:04 -0500
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:35072 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1732315AbgAIPWE (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 9 Jan 2020 10:22:04 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1578583323;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=GkPqCUD4XkIHW5a1LsjZ+v2acwoaiMCCGZAUZ9gBdJI=;
        b=ZqIs0MvKBp3Jw6mqFNsuF4jFd0gLAmShCZq6B89inz9D1linMFjfSCGVJ/rRPx7c1tVJkn
        aJhhjfNArdgXWVvGSZJ/pJ5G5AXrRBUJkwkurgDsVLxxhQxgDQizzlcpRjSWD9uHLIxM2d
        ZTWtWLi9FBSOf23BMa3QbuIfH07EQv8=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-235-Gscak5j0MSqJfyybuFHsGw-1; Thu, 09 Jan 2020 10:21:59 -0500
X-MC-Unique: Gscak5j0MSqJfyybuFHsGw-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id CAC11804910;
        Thu,  9 Jan 2020 15:21:57 +0000 (UTC)
Received: from x1w.redhat.com (ovpn-204-180.brq.redhat.com [10.40.204.180])
        by smtp.corp.redhat.com (Postfix) with ESMTPS id 44F1180608;
        Thu,  9 Jan 2020 15:21:45 +0000 (UTC)
From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>
To: qemu-devel@nongnu.org
Cc: Marcelo Tosatti <mtosatti@redhat.com>,
 Peter Maydell <peter.maydell@linaro.org>, qemu-arm@nongnu.org,
 Eduardo Habkost <ehabkost@redhat.com>, Juan Quintela <quintela@redhat.com>,
 kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>,
 Marcel Apfelbaum <marcel.apfelbaum@gmail.com>,
 Alistair Francis <alistair.francis@wdc.com>, qemu-ppc@nongnu.org,
 "Dr. David Alan Gilbert" <dgilbert@redhat.com>,
 Richard Henderson <rth@twiddle.net>,
 David Gibson <david@gibson.dropbear.id.au>, =?utf-8?q?Philippe_Mathieu-Daud?=
	=?utf-8?q?=C3=A9?= <philmd@redhat.com>
Subject: [PATCH 01/15] target/arm/kvm: Use CPUState::kvm_state in
 kvm_arm_pmu_supported()
Date: Thu,  9 Jan 2020 16:21:19 +0100
Message-Id: <20200109152133.23649-2-philmd@redhat.com>
In-Reply-To: <20200109152133.23649-1-philmd@redhat.com>
References: <20200109152133.23649-1-philmd@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

KVMState is already accessible via CPUState::kvm_state, use it.

Signed-off-by: Philippe Mathieu-Daudé <philmd@redhat.com>
---
 target/arm/kvm.c | 4 +---
 1 file changed, 1 insertion(+), 3 deletions(-)

```
#### [kvm-unit-tests PATCH v6 1/4] s390x: export sclp_setup_int
##### From: Claudio Imbrenda <imbrenda@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Claudio Imbrenda <imbrenda@linux.ibm.com>
X-Patchwork-Id: 11326123
Return-Path: <SRS0=hq+s=26=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1A73F139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Jan 2020 16:16:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id F04202075D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Jan 2020 16:16:35 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2387538AbgAIQQf (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 9 Jan 2020 11:16:35 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:20102 "EHLO
        mx0b-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S2387531AbgAIQQe (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 9 Jan 2020 11:16:34 -0500
Received: from pps.filterd (m0127361.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 009G9n9j012408
        for <kvm@vger.kernel.org>; Thu, 9 Jan 2020 11:16:33 -0500
Received: from e06smtp03.uk.ibm.com (e06smtp03.uk.ibm.com [195.75.94.99])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2xdx6k4gu7-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Thu, 09 Jan 2020 11:16:32 -0500
Received: from localhost
        by e06smtp03.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <imbrenda@linux.ibm.com>;
        Thu, 9 Jan 2020 16:16:29 -0000
Received: from b06avi18878370.portsmouth.uk.ibm.com (9.149.26.194)
        by e06smtp03.uk.ibm.com (192.168.101.133) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Thu, 9 Jan 2020 16:16:27 -0000
Received: from d06av22.portsmouth.uk.ibm.com (d06av22.portsmouth.uk.ibm.com
 [9.149.105.58])
        by b06avi18878370.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 009GGP5a21102930
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 9 Jan 2020 16:16:25 GMT
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id D14904C044;
        Thu,  9 Jan 2020 16:16:25 +0000 (GMT)
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 8C8894C04A;
        Thu,  9 Jan 2020 16:16:25 +0000 (GMT)
Received: from p-imbrenda.boeblingen.de.ibm.com (unknown [9.152.224.108])
        by d06av22.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Thu,  9 Jan 2020 16:16:25 +0000 (GMT)
From: Claudio Imbrenda <imbrenda@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, thuth@redhat.com, david@redhat.com,
        borntraeger@de.ibm.com, frankja@linux.ibm.com
Subject: [kvm-unit-tests PATCH v6 1/4] s390x: export sclp_setup_int
Date: Thu,  9 Jan 2020 17:16:22 +0100
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20200109161625.154894-1-imbrenda@linux.ibm.com>
References: <20200109161625.154894-1-imbrenda@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 20010916-0012-0000-0000-0000037BF8C1
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 20010916-0013-0000-0000-000021B81AA7
Message-Id: <20200109161625.154894-2-imbrenda@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-01-09_03:2020-01-09,2020-01-09 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 adultscore=0
 lowpriorityscore=0 phishscore=0 priorityscore=1501 bulkscore=0
 suspectscore=1 spamscore=0 mlxscore=0 malwarescore=0 impostorscore=0
 mlxlogscore=999 clxscore=1015 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-1910280000 definitions=main-2001090138
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Export sclp_setup_int() so that it can be used in tests.

Needed for an upcoming unit test.

Signed-off-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
Reviewed-by: Janosch Frank <frankja@linux.ibm.com>
---
 lib/s390x/sclp.h | 1 +
 lib/s390x/sclp.c | 2 +-
 2 files changed, 2 insertions(+), 1 deletion(-)

```
#### [PATCH v4] KVM: s390: Add new reset vcpu API
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11326041
Return-Path: <SRS0=hq+s=26=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 10EEE139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Jan 2020 15:56:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D7DDD2072A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Jan 2020 15:56:20 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731024AbgAIP4U (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 9 Jan 2020 10:56:20 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:43382 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1729591AbgAIP4T (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 9 Jan 2020 10:56:19 -0500
Received: from pps.filterd (m0187473.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 009FsO3o069652
        for <kvm@vger.kernel.org>; Thu, 9 Jan 2020 10:56:18 -0500
Received: from e06smtp05.uk.ibm.com (e06smtp05.uk.ibm.com [195.75.94.101])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2xe00wr422-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Thu, 09 Jan 2020 10:56:17 -0500
Received: from localhost
        by e06smtp05.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Thu, 9 Jan 2020 15:56:14 -0000
Received: from b06cxnps3075.portsmouth.uk.ibm.com (9.149.109.195)
        by e06smtp05.uk.ibm.com (192.168.101.135) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Thu, 9 Jan 2020 15:56:11 -0000
Received: from d06av24.portsmouth.uk.ibm.com (d06av24.portsmouth.uk.ibm.com
 [9.149.105.60])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 009FuApw58065086
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 9 Jan 2020 15:56:10 GMT
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 3B90A42041;
        Thu,  9 Jan 2020 15:56:10 +0000 (GMT)
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 7CBB74203F;
        Thu,  9 Jan 2020 15:56:08 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.145.166.75])
        by d06av24.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Thu,  9 Jan 2020 15:56:08 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: thuth@redhat.com, borntraeger@de.ibm.com,
        linux-s390@vger.kernel.org, david@redhat.com, cohuck@redhat.com
Subject: [PATCH v4] KVM: s390: Add new reset vcpu API
Date: Thu,  9 Jan 2020 10:56:01 -0500
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 20010915-0020-0000-0000-0000039F4B21
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 20010915-0021-0000-0000-000021F6AFCB
Message-Id: <20200109155602.18985-1-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-01-09_03:2020-01-09,2020-01-09 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 suspectscore=1 mlxscore=0
 adultscore=0 clxscore=1015 bulkscore=0 mlxlogscore=999 phishscore=0
 lowpriorityscore=0 impostorscore=0 malwarescore=0 spamscore=0
 priorityscore=1501 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-1910280000 definitions=main-2001090137
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The architecture states that we need to reset local IRQs for all CPU
resets. Because the old reset interface did not support the normal CPU
reset we never did that on a normal reset.

Let's implement an interface for the missing normal and clear resets
and reset all local IRQs, registers and control structures as stated
in the architecture.

Userspace might already reset the registers via the vcpu run struct,
but as we need the interface for the interrupt clearing part anyway,
we implement the resets fully and don't rely on userspace to reset the
rest.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
---

I dropped the reviews, as I changed quite a lot.  

Keep in mind, that now we'll need a new parameter in normal and
initial reset for protected virtualization to indicate that we need to
do the reset via the UV call. The Ultravisor does only accept the
needed reset, not any subset resets.

---
 Documentation/virt/kvm/api.txt |  46 ++++++++++++++
 arch/s390/kvm/kvm-s390.c       | 106 +++++++++++++++++++++++----------
 include/uapi/linux/kvm.h       |   5 ++
 3 files changed, 127 insertions(+), 30 deletions(-)

```
