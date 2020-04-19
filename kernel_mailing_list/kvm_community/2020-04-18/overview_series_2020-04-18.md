#### [PATCH] KVM: s390: remove unneeded semicolon in gisa_vcpu_kicker()
##### From: Jason Yan <yanaijie@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Yan <yanaijie@huawei.com>
X-Patchwork-Id: 11496343
Return-Path: <SRS0=772H=6C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 672AC92C
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 18 Apr 2020 07:53:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5887421D82
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 18 Apr 2020 07:53:17 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726069AbgDRHxN (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 18 Apr 2020 03:53:13 -0400
Received: from szxga07-in.huawei.com ([45.249.212.35]:35880 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1725862AbgDRHxN (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 18 Apr 2020 03:53:13 -0400
Received: from DGGEMS410-HUB.china.huawei.com (unknown [172.30.72.60])
        by Forcepoint Email with ESMTP id 68869CE304963797192C;
        Sat, 18 Apr 2020 15:53:10 +0800 (CST)
Received: from huawei.com (10.175.124.28) by DGGEMS410-HUB.china.huawei.com
 (10.3.19.210) with Microsoft SMTP Server id 14.3.487.0; Sat, 18 Apr 2020
 15:53:00 +0800
From: Jason Yan <yanaijie@huawei.com>
To: <borntraeger@de.ibm.com>, <frankja@linux.ibm.com>,
        <david@redhat.com>, <cohuck@redhat.com>,
        <heiko.carstens@de.ibm.com>, <gor@linux.ibm.com>,
        <Ulrich.Weigand@de.ibm.com>, <kvm@vger.kernel.org>,
        <linux-s390@vger.kernel.org>, <linux-kernel@vger.kernel.org>
CC: Jason Yan <yanaijie@huawei.com>, Hulk Robot <hulkci@huawei.com>
Subject: [PATCH] KVM: s390: remove unneeded semicolon in gisa_vcpu_kicker()
Date: Sat, 18 Apr 2020 16:19:26 +0800
Message-ID: <20200418081926.41666-1-yanaijie@huawei.com>
X-Mailer: git-send-email 2.21.1
MIME-Version: 1.0
X-Originating-IP: [10.175.124.28]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Fix the following coccicheck warning:

arch/s390/kvm/interrupt.c:3085:2-3: Unneeded semicolon

Reported-by: Hulk Robot <hulkci@huawei.com>
Signed-off-by: Jason Yan <yanaijie@huawei.com>
---
 arch/s390/kvm/interrupt.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v3 1/8] vhost: Not cleaning batched descs in VHOST_SET_VRING_BASE ioctl
##### From: =?utf-8?q?Eugenio_P=C3=A9rez?= <eperezma@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Eugenio_P=C3=A9rez?= <eperezma@redhat.com>
X-Patchwork-Id: 11496487
Return-Path: <SRS0=772H=6C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9D42613B2
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 18 Apr 2020 10:23:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 83F42221F4
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 18 Apr 2020 10:23:15 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="AseJXGrX"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725892AbgDRKWq (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 18 Apr 2020 06:22:46 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:37487 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1725949AbgDRKWi (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 18 Apr 2020 06:22:38 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1587205355;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=vwWNaCCFGnInUmv5tpeoOpCpadYnvdzVMsJO2bg1Nbc=;
        b=AseJXGrX8C7TSRWz0YQQaO0TSMHyNHhSG63iV6BaUbhgXO2EXFTqIJPmY6teFu3jK9AKT1
        uFfv4gK28TM5L+Bkzzs9rOPDYXhnuQRp/MaJSX1ESn/lNATOYDK2Ezz2oOdAgpYETz5daW
        YhgLlcAaNfnzQDhaz8Xn/iz+9nMzLI0=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-353-5AHjK9raMU2HXAvB4v78SQ-1; Sat, 18 Apr 2020 06:22:30 -0400
X-MC-Unique: 5AHjK9raMU2HXAvB4v78SQ-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 70BEB8018A3;
        Sat, 18 Apr 2020 10:22:29 +0000 (UTC)
Received: from eperezma.remote.csb (ovpn-112-94.ams2.redhat.com
 [10.36.112.94])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 137831001DC2;
        Sat, 18 Apr 2020 10:22:26 +0000 (UTC)
From: =?utf-8?q?Eugenio_P=C3=A9rez?= <eperezma@redhat.com>
To: "Michael S. Tsirkin" <mst@redhat.com>
Cc: "virtualization@lists.linux-foundation.org"
  <virtualization@lists.linux-foundation.org>,
 "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>,
 Halil Pasic <pasic@linux.ibm.com>, Cornelia Huck <cohuck@redhat.com>,
	=?utf-8?q?Eugenio_P=C3=A9rez?= <eperezma@redhat.com>,
 Christian Borntraeger <borntraeger@de.ibm.com>,
 kvm list <kvm@vger.kernel.org>, Stephen Rothwell <sfr@canb.auug.org.au>,
 Linux Next Mailing List <linux-next@vger.kernel.org>
Subject: [PATCH v3 1/8] vhost: Not cleaning batched descs in
 VHOST_SET_VRING_BASE ioctl
Date: Sat, 18 Apr 2020 12:22:10 +0200
Message-Id: <20200418102217.32327-2-eperezma@redhat.com>
In-Reply-To: <20200418102217.32327-1-eperezma@redhat.com>
References: <20200418102217.32327-1-eperezma@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

They are cleaned in vhost_vq_set_backend, which can be called with an
active backend. To set and remove backends already clean batched
descriptors, so to do it here is completely redundant.

Fixes: ("e7539c20a4a6 vhost: batching fetches")

Signed-off-by: Eugenio Pérez <eperezma@redhat.com>
---
 drivers/vhost/vhost.c | 1 -
 1 file changed, 1 deletion(-)

```
