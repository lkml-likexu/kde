#### [kvm-unit-tests PATCH v4 01/13] libcflat: Add other size defines
##### From: Eric Auger <eric.auger@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Auger Eric <eric.auger@redhat.com>
X-Patchwork-Id: 11426605
Return-Path: <SRS0=BDOO=42=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 75709138D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  9 Mar 2020 10:24:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4C7972146E
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  9 Mar 2020 10:24:43 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="JrkgJR3k"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726643AbgCIKYm (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 9 Mar 2020 06:24:42 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:55778 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726637AbgCIKYm (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 9 Mar 2020 06:24:42 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1583749481;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=g1Y7SAIkQ6YKL70iv+PevVOHVnPkk+5bW/+E3fVVoME=;
        b=JrkgJR3k5ausWefJvBkltKkWZ+ctGVvpV7+/wcqgrmyKQPSMTqDwVKOqCgvdfgQqIKI+S0
        jUk7Im42t+AOThYvjyG9ZmXyz+gJvlZdRR/cIYbmzRsFQzE9zlDlykITbl1afbMU5wqPte
        CexF811yQajm52e3xcuXljCbHZQ+1fs=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-154-o3NGrAlvMNy5JyZNJLr89w-1; Mon, 09 Mar 2020 06:24:38 -0400
X-MC-Unique: o3NGrAlvMNy5JyZNJLr89w-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id AF398800D53;
        Mon,  9 Mar 2020 10:24:36 +0000 (UTC)
Received: from laptop.redhat.com (ovpn-116-59.ams2.redhat.com [10.36.116.59])
        by smtp.corp.redhat.com (Postfix) with ESMTP id B323490779;
        Mon,  9 Mar 2020 10:24:33 +0000 (UTC)
From: Eric Auger <eric.auger@redhat.com>
To: eric.auger.pro@gmail.com, eric.auger@redhat.com, maz@kernel.org,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        qemu-devel@nongnu.org, qemu-arm@nongnu.org
Cc: drjones@redhat.com, andre.przywara@arm.com,
        peter.maydell@linaro.org, yuzenghui@huawei.com,
        alexandru.elisei@arm.com, thuth@redhat.com
Subject: [kvm-unit-tests PATCH v4 01/13] libcflat: Add other size defines
Date: Mon,  9 Mar 2020 11:24:08 +0100
Message-Id: <20200309102420.24498-2-eric.auger@redhat.com>
In-Reply-To: <20200309102420.24498-1-eric.auger@redhat.com>
References: <20200309102420.24498-1-eric.auger@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Introduce additional SZ_256, SZ_8K, SZ_16K macros that will
be used by ITS tests.

Signed-off-by: Eric Auger <eric.auger@redhat.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
---
 lib/libcflat.h | 3 +++
 1 file changed, 3 insertions(+)

```
#### [GIT PULL 01/36] s390/protvirt: introduce host side setup
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11426391
Return-Path: <SRS0=BDOO=42=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 067E714B7
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  9 Mar 2020 08:51:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D22502083E
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  9 Mar 2020 08:51:37 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726492AbgCIIvg (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 9 Mar 2020 04:51:36 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:30526 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726384AbgCIIvf (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 9 Mar 2020 04:51:35 -0400
Received: from pps.filterd (m0098409.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 0298pG0q005025
        for <kvm@vger.kernel.org>; Mon, 9 Mar 2020 04:51:34 -0400
Received: from e06smtp07.uk.ibm.com (e06smtp07.uk.ibm.com [195.75.94.103])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2ym7t6ds7m-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Mon, 09 Mar 2020 04:51:34 -0400
Received: from localhost
        by e06smtp07.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <borntraeger@de.ibm.com>;
        Mon, 9 Mar 2020 08:51:31 -0000
Received: from b06cxnps3075.portsmouth.uk.ibm.com (9.149.109.195)
        by e06smtp07.uk.ibm.com (192.168.101.137) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Mon, 9 Mar 2020 08:51:29 -0000
Received: from d06av24.portsmouth.uk.ibm.com (d06av24.portsmouth.uk.ibm.com
 [9.149.105.60])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 0298pRvv38142162
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 9 Mar 2020 08:51:27 GMT
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id A187E4204B;
        Mon,  9 Mar 2020 08:51:27 +0000 (GMT)
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 830A042042;
        Mon,  9 Mar 2020 08:51:27 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av24.portsmouth.uk.ibm.com (Postfix) with ESMTPS;
        Mon,  9 Mar 2020 08:51:27 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 25651)
        id 3E00FE0269; Mon,  9 Mar 2020 09:51:27 +0100 (CET)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: KVM <kvm@vger.kernel.org>,
        Janosch Frank <frankja@linux.vnet.ibm.com>,
        David Hildenbrand <david@redhat.com>,
        Claudio Imbrenda <imbrenda@linux.ibm.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Michael Mueller <mimu@linux.ibm.com>,
        Vasily Gorbik <gor@linux.ibm.com>,
        Ulrich Weigand <uweigand@de.ibm.com>,
        linux-s390 <linux-s390@vger.kernel.org>,
        Heiko Carstens <heiko.carstens@de.ibm.com>
Subject: [GIT PULL 01/36] s390/protvirt: introduce host side setup
Date: Mon,  9 Mar 2020 09:50:51 +0100
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20200309085126.3334302-1-borntraeger@de.ibm.com>
References: <20200309085126.3334302-1-borntraeger@de.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 20030908-0028-0000-0000-000003E2343B
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 20030908-0029-0000-0000-000024A770F2
Message-Id: <20200309085126.3334302-2-borntraeger@de.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-03-09_02:2020-03-06,2020-03-09 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 impostorscore=0 spamscore=0
 bulkscore=0 mlxscore=0 adultscore=0 clxscore=1015 priorityscore=1501
 lowpriorityscore=0 malwarescore=0 phishscore=0 mlxlogscore=999
 suspectscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2001150001 definitions=main-2003090066
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Vasily Gorbik <gor@linux.ibm.com>

Add "prot_virt" command line option which controls if the kernel
protected VMs support is enabled at early boot time. This has to be
done early, because it needs large amounts of memory and will disable
some features like STP time sync for the lpar.

Extend ultravisor info definitions and expose it via uv_info struct
filled in during startup.

Signed-off-by: Vasily Gorbik <gor@linux.ibm.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
Acked-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Acked-by: Christian Borntraeger <borntraeger@de.ibm.com>
[borntraeger@de.ibm.com: patch merging, splitting, fixing]
Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 .../admin-guide/kernel-parameters.txt         |  5 ++
 arch/s390/boot/Makefile                       |  2 +-
 arch/s390/boot/uv.c                           | 20 +++++++
 arch/s390/include/asm/uv.h                    | 45 +++++++++++++++-
 arch/s390/kernel/Makefile                     |  1 +
 arch/s390/kernel/setup.c                      |  4 --
 arch/s390/kernel/uv.c                         | 52 +++++++++++++++++++
 7 files changed, 122 insertions(+), 7 deletions(-)
 create mode 100644 arch/s390/kernel/uv.c

```
#### [GIT PULL] virtio: fixes
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 11426147
Return-Path: <SRS0=BDOO=42=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 20A9D138D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  9 Mar 2020 08:08:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 00B1120728
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  9 Mar 2020 08:08:40 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="djy4DDw0"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726498AbgCIIIh (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 9 Mar 2020 04:08:37 -0400
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:43549 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726217AbgCIIIg (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 9 Mar 2020 04:08:36 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1583741316;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type;
        bh=T8KT/+n14Cn5HelmWM4TG6Zo6L21o7FLn2E43AQONUI=;
        b=djy4DDw0GWO/FlipTcCuReTRQdxU7CCeyznNX6plnt1Fnk2hzBgVjY0Gg7u9QOHKd/V6op
        qCM0yiU97aSGDOJCMWfyvInwVJaWxcCD1HH9MymtbUWe59vQc4VQ0uOFroV8eDrs6LCZ6f
        UaCVAZ64wWh/fxmffJE0CZtx4OiW2A8=
Received: from mail-qk1-f200.google.com (mail-qk1-f200.google.com
 [209.85.222.200]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-107-0xLf21sZPNe_ca2UoHEFjw-1; Mon, 09 Mar 2020 04:08:33 -0400
X-MC-Unique: 0xLf21sZPNe_ca2UoHEFjw-1
Received: by mail-qk1-f200.google.com with SMTP id t186so6703189qkh.22
        for <kvm@vger.kernel.org>; Mon, 09 Mar 2020 01:08:33 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:mime-version
         :content-disposition;
        bh=T8KT/+n14Cn5HelmWM4TG6Zo6L21o7FLn2E43AQONUI=;
        b=r5Cfunm7j3CalAFyuIuLU8G9p3diuRqMPqWKdTOC43+6hUomxQrQK5vY9MevQrt/M1
         JYNPGubKw8GzIDWr6m0AeIY7votWKimRyuD0tvvMWvAx7ttRMBlkwhQXtqa0ATIR8aPR
         1r1a2AVgZ1p0f+Eelvq3EVjewy58L7UYiqovctKq4GpPSZ3ZrcEM899b+x2RbZ26cJaF
         lamlXI0Ker4bCLMoXSyVsMyaniT67LudeFNNcsvTAYrHptmUaTAyUYSh1jvoJO0SMbt7
         MZB9dwIYFkc2bnGzDjx8TqyAuZ5a0jfOFlp1GHy5nU3ke3PuvvjmbYTgIlsNeqgzn+9C
         07bA==
X-Gm-Message-State: ANhLgQ2NJd8H1hAephK0x1oCo57DKyd7lwHVmUGyykVz/II1E4ceDdfJ
        oiP25JTwNoIcXKFBM6HyY2YHNeKeyoLNJFlEqXzkbBS0nDLDgE+ixY09lO0/IVIclUuZKm8aWH9
        CEoQaBTZDnToy
X-Received: by 2002:a0c:c244:: with SMTP id w4mr13815581qvh.104.1583741311604;
        Mon, 09 Mar 2020 01:08:31 -0700 (PDT)
X-Google-Smtp-Source: 
 ADFU+vsDCYFx3tgEt/18zqy2Hj0onYaUrEMtYoBKu3yJ+l1tw+IzBr80xlV0fKvKv/QcwEaRhnxGPw==
X-Received: by 2002:a0c:c244:: with SMTP id w4mr13815565qvh.104.1583741311386;
        Mon, 09 Mar 2020 01:08:31 -0700 (PDT)
Received: from redhat.com (bzq-79-178-2-19.red.bezeqint.net. [79.178.2.19])
        by smtp.gmail.com with ESMTPSA id
 k11sm21885175qti.68.2020.03.09.01.08.27
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 09 Mar 2020 01:08:30 -0700 (PDT)
Date: Mon, 9 Mar 2020 04:08:25 -0400
From: "Michael S. Tsirkin" <mst@redhat.com>
To: Linus Torvalds <torvalds@linux-foundation.org>
Cc: kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org, linux-kernel@vger.kernel.org,
        axboe@kernel.dk, jasowang@redhat.com, mst@redhat.com,
        natechancellor@gmail.com, pasic@linux.ibm.com, s-anna@ti.com
Subject: [GIT PULL] virtio: fixes
Message-ID: <20200309040825-mutt-send-email-mst@kernel.org>
MIME-Version: 1.0
Content-Disposition: inline
X-Mutt-Fcc: =sent
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The following changes since commit 98d54f81e36ba3bf92172791eba5ca5bd813989b:

  Linux 5.6-rc4 (2020-03-01 16:38:46 -0600)

are available in the Git repository at:

  https://git.kernel.org/pub/scm/linux/kernel/git/mst/vhost.git tags/for_linus

for you to fetch changes up to 6ae4edab2fbf86ec92fbf0a8f0c60b857d90d50f:

  virtio_balloon: Adjust label in virtballoon_probe (2020-03-08 05:35:24 -0400)

----------------------------------------------------------------
virtio: fixes

Some bug fixes all over the place.

Signed-off-by: Michael S. Tsirkin <mst@redhat.com>

----------------------------------------------------------------
Halil Pasic (2):
      virtio-blk: fix hw_queue stopped on arbitrary error
      virtio-blk: improve virtqueue error to BLK_STS

Nathan Chancellor (1):
      virtio_balloon: Adjust label in virtballoon_probe

Suman Anna (1):
      virtio_ring: Fix mem leak with vring_new_virtqueue()

 drivers/block/virtio_blk.c      | 17 ++++++++++++-----
 drivers/virtio/virtio_balloon.c |  2 +-
 drivers/virtio/virtio_ring.c    |  4 ++--
 3 files changed, 15 insertions(+), 8 deletions(-)
```
#### [PATCH v2 1/2] KVM: arm64: Add PMU event filtering infrastructure
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11427087
Return-Path: <SRS0=BDOO=42=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 43D1F1874
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  9 Mar 2020 12:48:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 24C0C20727
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  9 Mar 2020 12:48:55 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1583758135;
	bh=e1nBsQ/vz68q/AvY4dl3gcOvfqAMi9CmFVoaruDGhh8=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=PoaDtMDp96p8AjZA56GqbvVP0M0eOluuIVT49Wvlzm/G145vjeGC7rDKLWBRVT4tP
	 Mfje2eA8DUDCkwSIK+aaV4HCiJnxKFqxdTh2RlhsshhOplCAa1ysbl+Sv0RxD/HnCv
	 wugA5jqYw7TXynQ/ELRwAox0JnurmhLVWXHCq9Bg=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726446AbgCIMsq (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 9 Mar 2020 08:48:46 -0400
Received: from mail.kernel.org ([198.145.29.99]:55236 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726426AbgCIMsq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 9 Mar 2020 08:48:46 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id A3EB720828;
        Mon,  9 Mar 2020 12:48:44 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1583758124;
        bh=e1nBsQ/vz68q/AvY4dl3gcOvfqAMi9CmFVoaruDGhh8=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=EAn1idXsaxSzdmXKj4M7e2GOj3CRnvEBXqBjRDhudWEDvpX5lvI7Rw/6c9Qyttrs0
         jJwhbKiyi6qY2C4FSsaCwvoj0pKiCtpKaopNkqxTdlJcS44fDVh4OZKeKRxLW+tzFu
         LNeK4Vzmh+XvcuZq2kSyFlQnylpn4hoieAw4m5ig=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1jBHpq-00BHiN-V3; Mon, 09 Mar 2020 12:48:43 +0000
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Robin Murphy <robin.murphy@arm.com>,
        Mark Rutland <mark.rutland@arm.com>,
        Eric Auger <eric.auger@redhat.com>
Subject: [PATCH v2 1/2] KVM: arm64: Add PMU event filtering infrastructure
Date: Mon,  9 Mar 2020 12:48:36 +0000
Message-Id: <20200309124837.19908-2-maz@kernel.org>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20200309124837.19908-1-maz@kernel.org>
References: <20200309124837.19908-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com, robin.murphy@arm.com,
 mark.rutland@arm.com, eric.auger@redhat.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

It can be desirable to expose a PMU to a guest, and yet not want the
guest to be able to count some of the implemented events (because this
would give information on shared resources, for example.

For this, let's extend the PMUv3 device API, and offer a way to setup a
bitmap of the allowed events (the default being no bitmap, and thus no
filtering).

Userspace can thus allow/deny ranges of event. The default policy
depends on the "polarity" of the first filter setup (default deny if the
filter allows events, and default allow if the filter denies events).
This allows to setup exactly what is allowed for a given guest.

Note that although the ioctl is per-vcpu, the map of allowed events is
global to the VM (it can be setup from any vcpu until the vcpu PMU is
initialized).

Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 arch/arm64/include/asm/kvm_host.h |  6 +++
 arch/arm64/include/uapi/asm/kvm.h | 16 ++++++
 virt/kvm/arm/arm.c                |  2 +
 virt/kvm/arm/pmu.c                | 84 +++++++++++++++++++++++++------
 4 files changed, 92 insertions(+), 16 deletions(-)

```
#### [PATCH v6 01/14] KVM: X86: Change parameter for fast_page_fault tracepoint
##### From: Peter Xu <peterx@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11428127
Return-Path: <SRS0=BDOO=42=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DA4A7139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  9 Mar 2020 21:44:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id BA84E24655
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  9 Mar 2020 21:44:37 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="RMnb+NvC"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727142AbgCIVog (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 9 Mar 2020 17:44:36 -0400
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:34584 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726536AbgCIVog (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 9 Mar 2020 17:44:36 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1583790274;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=zL6sq31OFwBXF/RS7PK1GArrpq69jRR45bepTSw46TU=;
        b=RMnb+NvCYpUUCZ1w9CSsUi3LHg2Le/DHtnnszUvK/PfF6aShebqp9TWextIdZt+PFJ90Qp
        cHkqcGiL0NtqhYF04bU0peA61Frn+bfGWrnWnH9hxyMRtLBlS71V7ny/0jS3MoK7tQWSZ5
        1z5IBhSpAjtEAadpnVy61GXC/TnA1S4=
Received: from mail-qv1-f70.google.com (mail-qv1-f70.google.com
 [209.85.219.70]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-328-rGdOoHvhME6IU1BmzGGxxQ-1; Mon, 09 Mar 2020 17:44:31 -0400
X-MC-Unique: rGdOoHvhME6IU1BmzGGxxQ-1
Received: by mail-qv1-f70.google.com with SMTP id l16so7674781qvo.15
        for <kvm@vger.kernel.org>; Mon, 09 Mar 2020 14:44:30 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=zL6sq31OFwBXF/RS7PK1GArrpq69jRR45bepTSw46TU=;
        b=Dk0rFyP+nAzdk7AASHebzhxyg5iv1x1LqT2H9x6JJPWBCz1jEdyk+dE/NiS+SID85G
         MC41E8ol026ML2p6CU/90bXvIUy27YC+z9U1hIJl/OatvgO64JI/cgvKfcGzdNCtMTMP
         45hlzPQDhzn4v5WQHCMur9/kH3wNeDlr/zHsRlfpVnB7smSiQsabnTOal01TntB9RgrG
         R372Hdsov6H0ecXjeGiBGUza+E88nQjuFjNyJUC7ESQyoiJtFLg+9zibasnjBZBBqNyx
         A0YI1ozxWzBc6M2GgwP9M6CnPCRoMBV/0SgtwdM5MCB9VWYF7wBnNX7B26xch5QKl2tO
         DC/w==
X-Gm-Message-State: ANhLgQ0x6K2WjfliG+8m8rIFhbqIV+GJlHHDEkm7md5uwnzdc63urRUR
        8Qk6xWuRC7OIqDqyfK21etF9UmE+pvZXasW+VUOBNxCTtVuzI7CAHBPArbeDipBP04y9vXqQlQ0
        gwC0uQzPtatPb
X-Received: by 2002:ac8:7613:: with SMTP id
 t19mr15821442qtq.203.1583790270264;
        Mon, 09 Mar 2020 14:44:30 -0700 (PDT)
X-Google-Smtp-Source: 
 ADFU+vtNsKwrUcoUekUZLm7aMwtJB3yh7uevNGAMIN8cX3luE4VyH2NbSx/AJmszLvjz/oRxyaNn7A==
X-Received: by 2002:ac8:7613:: with SMTP id
 t19mr15821436qtq.203.1583790270038;
        Mon, 09 Mar 2020 14:44:30 -0700 (PDT)
Received: from xz-x1.redhat.com ([2607:9880:19c0:32::2])
        by smtp.gmail.com with ESMTPSA id
 65sm22758686qtc.4.2020.03.09.14.44.28
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 09 Mar 2020 14:44:29 -0700 (PDT)
From: Peter Xu <peterx@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Yan Zhao <yan.y.zhao@intel.com>, Jason Wang <jasowang@redhat.com>,
        Alex Williamson <alex.williamson@redhat.com>,
        peterx@redhat.com, Vitaly Kuznetsov <vkuznets@redhat.com>,
        "Dr . David Alan Gilbert" <dgilbert@redhat.com>,
        Christophe de Dinechin <dinechin@redhat.com>,
        "Michael S . Tsirkin" <mst@redhat.com>,
        Kevin Tian <kevin.tian@intel.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>
Subject: [PATCH v6 01/14] KVM: X86: Change parameter for fast_page_fault
 tracepoint
Date: Mon,  9 Mar 2020 17:44:11 -0400
Message-Id: <20200309214424.330363-2-peterx@redhat.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20200309214424.330363-1-peterx@redhat.com>
References: <20200309214424.330363-1-peterx@redhat.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

It would be clearer to dump the return value to know easily on whether
did we go through the fast path for handling current page fault.
Remove the old two last parameters because after all the old/new sptes
were dumped in the same line.

Signed-off-by: Peter Xu <peterx@redhat.com>
---
 arch/x86/kvm/mmutrace.h | 9 ++-------
 1 file changed, 2 insertions(+), 7 deletions(-)

```
#### [PATCH 1/6] KVM: nVMX: avoid NULL pointer dereference with incorrect EVMCS GPAs
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11427471
Return-Path: <SRS0=BDOO=42=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 491C91800
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  9 Mar 2020 15:52:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 2A795208C3
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  9 Mar 2020 15:52:52 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="RgnK5S4O"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727125AbgCIPwt (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 9 Mar 2020 11:52:49 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:56595 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1727124AbgCIPwc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 9 Mar 2020 11:52:32 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1583769150;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=3E4LIBi/eaTA+USlOTfstaQ+9ylrR99sJyL6v/S7Fzk=;
        b=RgnK5S4OCgxqO6Kh/A4QZ4z7op1FUFfSat1Ittg5vuPUPn9WUaANF97ml6bdntVLf5UsWH
        LchrrAkz48sR/zjiUOMfe7RT/RbCZrzwEHMYImHg4HZHlWx58XVekxaC2kezF2hcNVT0y/
        wmIGBBaSpnSldytrQmWCuRhlqRwHGQ0=
Received: from mail-wr1-f72.google.com (mail-wr1-f72.google.com
 [209.85.221.72]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-304-7uG4iJMsNrSZhcnKuntN5Q-1; Mon, 09 Mar 2020 11:52:23 -0400
X-MC-Unique: 7uG4iJMsNrSZhcnKuntN5Q-1
Received: by mail-wr1-f72.google.com with SMTP id p11so5383391wrn.10
        for <kvm@vger.kernel.org>; Mon, 09 Mar 2020 08:52:23 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=3E4LIBi/eaTA+USlOTfstaQ+9ylrR99sJyL6v/S7Fzk=;
        b=NWO2AWnUdmZvo1FflMDyWlNQBi7XbO8WyVQc2pkPK59ZknwHQiOT2/sjB62sksSMVP
         R3Ggy3RufWIN/bVYJ5FZmoWaqNl+PvrMcl9tnOcB30wHkayjsyeuwE4a9X+TjY4BrygW
         Vm4EIhFdjK+rxfHhIq7i4HMS9eG6oqDz6/1Oa36dWXrn78NcXO0TG/13Y9Ut5uP59Rpk
         ZZI1LSh1iNfDXmQ6079jIO1o7XTCZqBWMbfnO0ZcIskLsvdQ69ihM4icxQx9deMf9kpf
         CIR+CEPjwotuqOqSJzVnQXG9ASf2U0Orgm3t4jRuAmOtyKNCG42MMxPQ9mjzptoHR6/o
         HzAA==
X-Gm-Message-State: ANhLgQ3Wc7UKGviPXnhg7O9dJpPjp1r72lsTNd1sid+szZBHs0BaIJO9
        p8ThfScJMWg81WXGm+KsHs1DV01yJOTk9Vg4sdcpsjPDndxJ+PodQbwpHkE2uhi842wVrWZs8i3
        OusSexISJOHcf
X-Received: by 2002:a5d:5411:: with SMTP id g17mr20557077wrv.4.1583769142618;
        Mon, 09 Mar 2020 08:52:22 -0700 (PDT)
X-Google-Smtp-Source: 
 ADFU+vs9pNoq6eROQLSMnQjOi+/bC2QHYG7NKgj7y/VTWqWWzCnhRUMXrJkC1KQDPqK4jhMpsxv/EA==
X-Received: by 2002:a5d:5411:: with SMTP id g17mr20557054wrv.4.1583769142367;
        Mon, 09 Mar 2020 08:52:22 -0700 (PDT)
Received: from vitty.brq.redhat.com (nat-pool-brq-t.redhat.com.
 [213.175.37.10])
        by smtp.gmail.com with ESMTPSA id
 q4sm17294521wro.56.2020.03.09.08.52.19
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 09 Mar 2020 08:52:20 -0700 (PDT)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Jim Mattson <jmattson@google.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Liran Alon <liran.alon@oracle.com>,
        Miaohe Lin <linmiaohe@huawei.com>
Subject: [PATCH 1/6] KVM: nVMX: avoid NULL pointer dereference with incorrect
 EVMCS GPAs
Date: Mon,  9 Mar 2020 16:52:11 +0100
Message-Id: <20200309155216.204752-2-vkuznets@redhat.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20200309155216.204752-1-vkuznets@redhat.com>
References: <20200309155216.204752-1-vkuznets@redhat.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When an EVMCS enabled L1 guest on KVM will tries doing enlightened VMEnter
with EVMCS GPA = 0 the host crashes because the

evmcs_gpa != vmx->nested.hv_evmcs_vmptr

condition in nested_vmx_handle_enlightened_vmptrld() will evaluate to
false (as nested.hv_evmcs_vmptr is zeroed after init). The crash will
happen on vmx->nested.hv_evmcs pointer dereference.

Another problematic EVMCS ptr value is '-1' but it only causes host crash
after nested_release_evmcs() invocation. The problem is exactly the same as
with '0', we mistakenly think that the EVMCS pointer hasn't changed and
thus nested.hv_evmcs_vmptr is valid.

Resolve the issue by adding an additional !vmx->nested.hv_evmcs
check to nested_vmx_handle_enlightened_vmptrld(), this way we will
always be trying kvm_vcpu_map() when nested.hv_evmcs is NULL
and this is supposed to catch all invalid EVMCS GPAs.

Also, initialize hv_evmcs_vmptr to '0' in nested_release_evmcs()
to be consistent with initialization where we don't currently
set hv_evmcs_vmptr to '-1'.

Cc: stable@vger.kernel.org
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/vmx/nested.c | 5 +++--
 1 file changed, 3 insertions(+), 2 deletions(-)

```
#### [PATCH 1/4] selftests: KVM: s390: fix early guest crash
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11427337
Return-Path: <SRS0=BDOO=42=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C16FB924
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  9 Mar 2020 15:04:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id ABBD921655
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  9 Mar 2020 15:04:23 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726892AbgCIPEX (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 9 Mar 2020 11:04:23 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:17948 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726617AbgCIPEX (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 9 Mar 2020 11:04:23 -0400
Received: from pps.filterd (m0098416.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 029ExI98019588;
        Mon, 9 Mar 2020 11:04:21 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 2ym648psxk-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 09 Mar 2020 11:04:20 -0400
Received: from m0098416.ppops.net (m0098416.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 029F1awp056635;
        Mon, 9 Mar 2020 11:02:36 -0400
Received: from ppma03dal.us.ibm.com (b.bd.3ea9.ip4.static.sl-reverse.com
 [169.62.189.11])
        by mx0b-001b2d01.pphosted.com with ESMTP id 2ym648pn6s-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 09 Mar 2020 11:02:36 -0400
Received: from pps.filterd (ppma03dal.us.ibm.com [127.0.0.1])
        by ppma03dal.us.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 029F0Qsc019769;
        Mon, 9 Mar 2020 15:00:35 GMT
Received: from b01cxnp23033.gho.pok.ibm.com (b01cxnp23033.gho.pok.ibm.com
 [9.57.198.28])
        by ppma03dal.us.ibm.com with ESMTP id 2ym386fw1d-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 09 Mar 2020 15:00:35 +0000
Received: from b01ledav001.gho.pok.ibm.com (b01ledav001.gho.pok.ibm.com
 [9.57.199.106])
        by b01cxnp23033.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id 029F0Yvm49807852
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 9 Mar 2020 15:00:34 GMT
Received: from b01ledav001.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id B1CA72806E;
        Mon,  9 Mar 2020 15:00:34 +0000 (GMT)
Received: from b01ledav001.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id A38A028067;
        Mon,  9 Mar 2020 15:00:34 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.114.17.106])
        by b01ledav001.gho.pok.ibm.com (Postfix) with ESMTP;
        Mon,  9 Mar 2020 15:00:34 +0000 (GMT)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: Christian Borntraeger <borntraeger@de.ibm.com>,
        Janosch Frank <frankja@linux.vnet.ibm.com>
Cc: KVM <kvm@vger.kernel.org>, Cornelia Huck <cohuck@redhat.com>,
        David Hildenbrand <david@redhat.com>,
        Thomas Huth <thuth@redhat.com>,
        linux-s390 <linux-s390@vger.kernel.org>
Subject: [PATCH 1/4] selftests: KVM: s390: fix early guest crash
Date: Mon,  9 Mar 2020 11:00:23 -0400
Message-Id: <20200309150026.4329-2-borntraeger@de.ibm.com>
X-Mailer: git-send-email 2.25.0
In-Reply-To: <20200309150026.4329-1-borntraeger@de.ibm.com>
References: <20200309150026.4329-1-borntraeger@de.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-03-09_06:2020-03-09,2020-03-09 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 adultscore=0
 priorityscore=1501 mlxscore=0 suspectscore=0 bulkscore=0 spamscore=0
 clxscore=1015 phishscore=0 malwarescore=0 impostorscore=0 mlxlogscore=999
 lowpriorityscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2001150001 definitions=main-2003090104
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The guest crashes very early due to changes in the control registers
used by dynamic address translation. Let us use different registers
that will not crash the guest.

Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 tools/testing/selftests/kvm/s390x/resets.c | 27 +++++++++++-----------
 1 file changed, 13 insertions(+), 14 deletions(-)

```
#### [kvm-unit-tests PATCH] x86: Bump apicv timeout to 30s to play nice with running in L1
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11427955
Return-Path: <SRS0=BDOO=42=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0BEBD92A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  9 Mar 2020 20:09:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id EB4442253D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  9 Mar 2020 20:09:17 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726528AbgCIUJR (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 9 Mar 2020 16:09:17 -0400
Received: from mga03.intel.com ([134.134.136.65]:35230 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726169AbgCIUJR (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 9 Mar 2020 16:09:17 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga006.jf.intel.com ([10.7.209.51])
  by orsmga103.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 09 Mar 2020 13:09:16 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,534,1574150400";
   d="scan'208";a="245452413"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by orsmga006.jf.intel.com with ESMTP; 09 Mar 2020 13:09:16 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org
Subject: [kvm-unit-tests PATCH] x86: Bump apicv timeout to 30s to play nice
 with running in L1
Date: Mon,  9 Mar 2020 13:09:15 -0700
Message-Id: <20200309200915.17244-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Increase the timeout for the apicv testcase to 30 seconds to avoid false
positives on the timeout when running the test in L1.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 x86/unittests.cfg | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [RFC] KVM: arm64: support enabling dirty log graually in small chunks
##### From: Keqian Zhu <zhukeqian1@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Keqian Zhu <zhukeqian1@huawei.com>
X-Patchwork-Id: 11426465
Return-Path: <SRS0=BDOO=42=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C39EC14B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  9 Mar 2020 08:59:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A5ED82467D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  9 Mar 2020 08:59:51 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726451AbgCII7r (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 9 Mar 2020 04:59:47 -0400
Received: from szxga07-in.huawei.com ([45.249.212.35]:41624 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726027AbgCII7r (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 9 Mar 2020 04:59:47 -0400
Received: from DGGEMS409-HUB.china.huawei.com (unknown [172.30.72.58])
        by Forcepoint Email with ESMTP id 609C5D3890AF7904DCED;
        Mon,  9 Mar 2020 16:59:41 +0800 (CST)
Received: from linux-kDCJWP.huawei.com (10.175.104.212) by
 DGGEMS409-HUB.china.huawei.com (10.3.19.209) with Microsoft SMTP Server id
 14.3.487.0; Mon, 9 Mar 2020 16:59:35 +0800
From: Keqian Zhu <zhukeqian1@huawei.com>
To: <kvmarm@lists.cs.columbia.edu>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>,
        <linux-arm-kernel@lists.infradead.org>
CC: <wanghaibin.wang@huawei.com>, Keqian Zhu <zhukeqian1@huawei.com>,
        Jay Zhou <jianjay.zhou@huawei.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Peter Xu <peterx@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>
Subject: [RFC] KVM: arm64: support enabling dirty log graually in small chunks
Date: Mon, 9 Mar 2020 16:57:27 +0800
Message-ID: <20200309085727.1106-1-zhukeqian1@huawei.com>
X-Mailer: git-send-email 2.19.1
MIME-Version: 1.0
X-Originating-IP: [10.175.104.212]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

There is already support of enabling dirty log graually
in small chunks for x86. This adds support for arm64.

Under the Huawei Kunpeng 920 2.6GHz platform, I did some
tests with a 128G linux VM and counted the time taken of
memory_global_dirty_log_start, here is the numbers:

VM Size        Before    After optimization
128G           527ms     4ms

Signed-off-by: Keqian Zhu <zhukeqian1@huawei.com>
---
Cc: Jay Zhou <jianjay.zhou@huawei.com>
Cc: Paolo Bonzini <pbonzini@redhat.com> 
Cc: Peter Xu <peterx@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
---
 Documentation/virt/kvm/api.rst    |  2 +-
 arch/arm64/include/asm/kvm_host.h |  4 ++++
 virt/kvm/arm/mmu.c                | 30 ++++++++++++++++++++++--------
 3 files changed, 27 insertions(+), 9 deletions(-)

```
#### [PATCH v4 1/5] x86/kvm/hyper-v: Explicitly align hcall param for kvm_hyperv_exit
##### From: Jon Doron <arilou@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jon Doron <arilou@gmail.com>
X-Patchwork-Id: 11427659
Return-Path: <SRS0=BDOO=42=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 29EFF1800
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  9 Mar 2020 18:20:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 007D020873
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  9 Mar 2020 18:20:32 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="NEpL5p7M"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727508AbgCISUc (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 9 Mar 2020 14:20:32 -0400
Received: from mail-wm1-f68.google.com ([209.85.128.68]:37802 "EHLO
        mail-wm1-f68.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727502AbgCISUa (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 9 Mar 2020 14:20:30 -0400
Received: by mail-wm1-f68.google.com with SMTP id a141so192786wme.2;
        Mon, 09 Mar 2020 11:20:28 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=SzCDulvogxwKt7aiMDZq2QO3RMFcK9aQnem/Q86V3aw=;
        b=NEpL5p7Mww5MMTwqj2WaKdEvcPAPyYLssCOkEAYYcZm0ybpz9yNLeWa1E0aMiFPTGc
         E5cwlf2qPGq1SG1lkhgTXntrRhs7PsDPq/5CuDQr6i//wOiNQFKPosVBZFCY1sHTah5T
         BTCb1BMCOPCG08+Qjb8l//NzP9KIySAvUqgqH0rPQtjdePVeAvJIh6DFmjQcH0J2+g/P
         3QhwDFVQWMEqA9E9we3K4/yupllk2nZOlVJzsoYwW6TkWbpY2kNjREpDyuI1abwluoq7
         xHiEbi0tmWinhQfmPl6deIouCofUfPCs093L10yPVYhSgdpkBZ/ZMvUMfrbePZxmg5uc
         dlvQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=SzCDulvogxwKt7aiMDZq2QO3RMFcK9aQnem/Q86V3aw=;
        b=V9pjoXMO76LwBAGBZmpdLyqwf6iDzj7Ec5VQGsI3SjzGONjEerP2u49AjKJ0/qW0xx
         F5etLjtpB220tAaVhDHbWmS/XjnjzBRNrnupCs+6lVQd9xAOtRAphDNE1GIz0STPgkDq
         9AjIy/hoPRcbGK2XhFuw+/Ljzncdg8J5IG4NDNMsoGVbs7vtBHhlSoPINfS40MFcxfzq
         UEHVOgxjADY8s+bTNeB8G/ciwB24SaOlAwOK1et8Fk3a0O0+SQ1DeUa/UjyP4aQ39GuU
         N0+guu6ZYhKks+vmRFbe7scZ1M73wCGDf4z+Oruqm9PXHATV7Yd/k5BbAPDnz68vHulj
         W90w==
X-Gm-Message-State: ANhLgQ14gHkGEZ3xgyWyP4qf+7sTcg4aGMXCCR3K8bdSUP7/mWhmiNzA
        Bogm0qaW55kAaPJ4no8BfDLt7ytiKz4=
X-Google-Smtp-Source: 
 ADFU+vvETPKN726tkV16p7/ZwpuGoXi+/a91mzvJzrYld0P7/ARbZ8SOB/rI5omzHV8Pf4SKPhhL5w==
X-Received: by 2002:a1c:1f14:: with SMTP id f20mr510404wmf.61.1583778028100;
        Mon, 09 Mar 2020 11:20:28 -0700 (PDT)
Received: from linux.local ([31.154.166.148])
        by smtp.gmail.com with ESMTPSA id
 t6sm8371828wrr.49.2020.03.09.11.20.27
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 09 Mar 2020 11:20:27 -0700 (PDT)
From: Jon Doron <arilou@gmail.com>
To: kvm@vger.kernel.org, linux-hyperv@vger.kernel.org
Cc: vkuznets@redhat.com, Jon Doron <arilou@gmail.com>
Subject: [PATCH v4 1/5] x86/kvm/hyper-v: Explicitly align hcall param for
 kvm_hyperv_exit
Date: Mon,  9 Mar 2020 20:20:13 +0200
Message-Id: <20200309182017.3559534-2-arilou@gmail.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20200309182017.3559534-1-arilou@gmail.com>
References: <20200309182017.3559534-1-arilou@gmail.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Signed-off-by: Jon Doron <arilou@gmail.com>
---
 include/uapi/linux/kvm.h | 1 +
 1 file changed, 1 insertion(+)

```
