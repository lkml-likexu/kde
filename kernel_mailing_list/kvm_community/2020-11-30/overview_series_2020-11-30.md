#### [GIT PULL] vhost,vdpa: bugfixes
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 11939953
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-27.2 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,INCLUDES_PULL_REQUEST,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7906CC63777
	for <kvm@archiver.kernel.org>; Mon, 30 Nov 2020 08:52:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1DF922076E
	for <kvm@archiver.kernel.org>; Mon, 30 Nov 2020 08:52:49 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="dIU5rRB5"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727136AbgK3Iwh (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 30 Nov 2020 03:52:37 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:42541 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726762AbgK3Iwg (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 30 Nov 2020 03:52:36 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1606726270;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type;
        bh=IfhR367gJyQi+IqH9Qg+155OiV0npyw4vEgjmNlOLaQ=;
        b=dIU5rRB5mnZqJ9gQpaqkMMJzsa48qjZ7U2XXFRjvXyAtEl3ZccDjmnmJDh3yMtxjqZ6H78
        T0pAO0RXO4346xUsv63ftiMcLy+TgEc/yH3rw6RzzJpMyGIeQXQYP+vL7r2WjbunImDrPQ
        /IjqQwUjhwIOniiOWjkHvdldqG3oiTY=
Received: from mail-wm1-f72.google.com (mail-wm1-f72.google.com
 [209.85.128.72]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-91-pWKbxCe4NG-s-2QTMoNU4Q-1; Mon, 30 Nov 2020 03:50:15 -0500
X-MC-Unique: pWKbxCe4NG-s-2QTMoNU4Q-1
Received: by mail-wm1-f72.google.com with SMTP id o203so4061511wmo.3
        for <kvm@vger.kernel.org>; Mon, 30 Nov 2020 00:50:15 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:mime-version
         :content-disposition;
        bh=IfhR367gJyQi+IqH9Qg+155OiV0npyw4vEgjmNlOLaQ=;
        b=T9G1Qy3rK4sdZJlwXnIS8nrYiG07JyZfRtYOx9kv81D4BbJTER2EjvDU7ocIbf32Aj
         /Ucpb89J3tUnDcPfQkfAv6PK6DRAAfvrksZxbIA5Q9vtTKNdQMrdKYA4lTBajCmIkDAf
         mSIVrA1Qw7a26w8B7lsTbA35Nzz6HALiI4dH1oBaRPS5g4OjFr/SllHtQghmy4t7xsgF
         jvEgZ6oZmoKakIpucx474DR77t+aOFsvZ5ixn+sqO3c2R4Cv+QE+/T6BGkwhTtSP9G8E
         +iEXnNxSFbScUWg4IyI8JBcVqobU63ITw/8co+1NEpLv4tuDdbJiBGnyD95kQnPXK61w
         nbGQ==
X-Gm-Message-State: AOAM530bDnTafS7HWbewVelBWqfpzdJ0NF8KfvLs5rJP8AG8lhIhE6AM
        IpDF9ISoRT6bt2/kQC4KmFg1cUmPDCIs7AGEy5p6oS1ezS7q7XV8diVzILPNe3zSFNrmW12h0us
        oQvR6+CZNTdvN
X-Received: by 2002:a1c:9a4d:: with SMTP id c74mr15059096wme.5.1606726213696;
        Mon, 30 Nov 2020 00:50:13 -0800 (PST)
X-Google-Smtp-Source: 
 ABdhPJx0lcq9LYEeQweeQ1PUtnvowfMkCnfs7A6y+pZ1luBu47l3TNrIhMMTxE9tXFN2kqV6KXqSzQ==
X-Received: by 2002:a1c:9a4d:: with SMTP id c74mr15059071wme.5.1606726213486;
        Mon, 30 Nov 2020 00:50:13 -0800 (PST)
Received: from redhat.com (bzq-79-176-44-197.red.bezeqint.net.
 [79.176.44.197])
        by smtp.gmail.com with ESMTPSA id
 21sm12930310wme.0.2020.11.30.00.50.11
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 30 Nov 2020 00:50:12 -0800 (PST)
Date: Mon, 30 Nov 2020 03:50:10 -0500
From: "Michael S. Tsirkin" <mst@redhat.com>
To: Linus Torvalds <torvalds@linux-foundation.org>
Cc: kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org, linux-kernel@vger.kernel.org,
        jasowang@redhat.com, michael.christie@oracle.com, mst@redhat.com,
        sgarzare@redhat.com, si-wei.liu@oracle.com, stefanha@redhat.com
Subject: [GIT PULL] vhost,vdpa: bugfixes
Message-ID: <20201130035010-mutt-send-email-mst@kernel.org>
MIME-Version: 1.0
Content-Disposition: inline
X-Mutt-Fcc: =sent
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The following changes since commit 418baf2c28f3473039f2f7377760bd8f6897ae18:

  Linux 5.10-rc5 (2020-11-22 15:36:08 -0800)

are available in the Git repository at:

  https://git.kernel.org/pub/scm/linux/kernel/git/mst/vhost.git tags/for_linus

for you to fetch changes up to ad89653f79f1882d55d9df76c9b2b94f008c4e27:

  vhost-vdpa: fix page pinning leakage in error path (rework) (2020-11-25 04:29:07 -0500)

----------------------------------------------------------------
vhost,vdpa: fixes

A couple of minor fixes.

Signed-off-by: Michael S. Tsirkin <mst@redhat.com>

----------------------------------------------------------------
Mike Christie (1):
      vhost scsi: fix lun reset completion handling

Si-Wei Liu (1):
      vhost-vdpa: fix page pinning leakage in error path (rework)

Stefano Garzarella (1):
      vringh: fix vringh_iov_push_*() documentation

 drivers/vhost/scsi.c   |  4 ++-
 drivers/vhost/vdpa.c   | 80 ++++++++++++++++++++++++++++++++++++++------------
 drivers/vhost/vringh.c |  6 ++--
 3 files changed, 68 insertions(+), 22 deletions(-)
```
#### [PATCH 1/2 v3] KVM: nSVM: Check reserved values for 'Type' and invalid vectors in EVENTINJ
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11941451
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-20.2 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	UNPARSEABLE_RELAY,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 4BDBDC64E7B
	for <kvm@archiver.kernel.org>; Mon, 30 Nov 2020 22:54:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DA96920725
	for <kvm@archiver.kernel.org>; Mon, 30 Nov 2020 22:54:44 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="FAJrgfm6"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388769AbgK3WyC (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 30 Nov 2020 17:54:02 -0500
Received: from aserp2120.oracle.com ([141.146.126.78]:58078 "EHLO
        aserp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1730855AbgK3WyB (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 30 Nov 2020 17:54:01 -0500
Received: from pps.filterd (aserp2120.oracle.com [127.0.0.1])
        by aserp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 0AUMdO7D035941;
        Mon, 30 Nov 2020 22:53:16 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=corp-2020-01-29;
 bh=JGVygv4vHzUJ71gIuU1M2dX+kKCuEAFztkCxmZAPKbc=;
 b=FAJrgfm6prnBbMKWtRU0HmGjjqYaonlZVetn8xKSW9+gUCMTbZAFtkbKRY/PTqwjZPW3
 t3uaakn+mGoK79R60ngg691rQtWzBKZozqdd98Z0OefsUdaMh+fhoEKIDeOVgMJs8WvT
 pD400d8T98NEuHt35GbXtBB5cnjX40zNMoprqkdXVHvkzSFv5ayLAe+F15QejEUda7Zb
 1Nvar3yTf8AY9aOgCDhBqCJ5OTU2Q+5lLi2R+VRRd+aLal2R81nPFI02iLZLilgIceAz
 5Dz40NY0oPteof9uGsWUmA1LB+nMRlheaTsIZDxkwOf8X6tb17lRm0aWypgzxOnP4Y8V 5A==
Received: from userp3020.oracle.com (userp3020.oracle.com [156.151.31.79])
        by aserp2120.oracle.com with ESMTP id 353egkfqvn-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=FAIL);
        Mon, 30 Nov 2020 22:53:16 +0000
Received: from pps.filterd (userp3020.oracle.com [127.0.0.1])
        by userp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 0AUMeDhP106972;
        Mon, 30 Nov 2020 22:53:15 GMT
Received: from userv0122.oracle.com (userv0122.oracle.com [156.151.31.75])
        by userp3020.oracle.com with ESMTP id 3540ar8tae-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 30 Nov 2020 22:53:15 +0000
Received: from abhmp0003.oracle.com (abhmp0003.oracle.com [141.146.116.9])
        by userv0122.oracle.com (8.14.4/8.14.4) with ESMTP id 0AUMrFqB010381;
        Mon, 30 Nov 2020 22:53:15 GMT
Received: from nsvm-sadhukhan.osdevelopmeniad.oraclevcn.com (/100.100.230.216)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Mon, 30 Nov 2020 14:53:14 -0800
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com, seanjc@google.com
Subject: [PATCH 1/2 v3] KVM: nSVM: Check reserved values for 'Type' and
 invalid vectors in EVENTINJ
Date: Mon, 30 Nov 2020 22:53:05 +0000
Message-Id: <20201130225306.15075-2-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.27.0
In-Reply-To: <20201130225306.15075-1-krish.sadhukhan@oracle.com>
References: <20201130225306.15075-1-krish.sadhukhan@oracle.com>
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9821
 signatures=668682
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 mlxlogscore=999
 bulkscore=0
 phishscore=0 mlxscore=0 adultscore=0 malwarescore=0 suspectscore=1
 spamscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2011300141
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9821
 signatures=668682
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 mlxscore=0
 bulkscore=0 suspectscore=1
 phishscore=0 mlxlogscore=999 lowpriorityscore=0 malwarescore=0
 priorityscore=1501 spamscore=0 impostorscore=0 clxscore=1011 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2011300141
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

According to sections "Canonicalization and Consistency Checks" and "Event
Injection" in APM vol 2

    VMRUN exits with VMEXIT_INVALID error code if either:
       - Reserved values of TYPE have been specified, or
       - TYPE = 3 (exception) has been specified with a vector that does not
         correspond to an exception (this includes vector 2, which is an NMI,
         not an exception).

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 arch/x86/include/asm/svm.h |  4 ++++
 arch/x86/kvm/svm/nested.c  | 14 ++++++++++++++
 2 files changed, 18 insertions(+)

```
#### [PATCH] KVM: x86: adjust SEV for commit 7e8e6eed75e
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11940733
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-17.2 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 6411FC64E90
	for <kvm@archiver.kernel.org>; Mon, 30 Nov 2020 14:41:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 06BC920725
	for <kvm@archiver.kernel.org>; Mon, 30 Nov 2020 14:41:32 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="gCvjFIJg"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727559AbgK3Ola (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 30 Nov 2020 09:41:30 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:34146 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726220AbgK3Ol3 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 30 Nov 2020 09:41:29 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1606747203;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=cPuNmdbqLgkjH8YEAT3ik4nIW0hCX379Trx0CgGX7Vg=;
        b=gCvjFIJgr18cOM0ErD3++EZCMEWjNzyfcg6J4qBFn0t2hgGF/T32uKOZoDgOleFSVWx6uA
        HNRT4UJqZ+BgZOTr/kALZx9J4MJCSwdVm9naiMnUTFOoj49uo/f3p3DC3784OJcq4V46Z4
        paaXmZdef+xYJmP4uQBC3/75ncUjnac=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-137-f6kD4QFNNFq5arfZiyo9Bg-1; Mon, 30 Nov 2020 09:40:01 -0500
X-MC-Unique: f6kD4QFNNFq5arfZiyo9Bg-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 76917107ACFA;
        Mon, 30 Nov 2020 14:40:00 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 154D460C62;
        Mon, 30 Nov 2020 14:40:00 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Ashish Kalra <Ashish.Kalra@amd.com>
Subject: [PATCH] KVM: x86: adjust SEV for commit 7e8e6eed75e
Date: Mon, 30 Nov 2020 09:39:59 -0500
Message-Id: <20201130143959.3636394-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Since the ASID is now stored in svm->asid, pre_sev_run should also place
it there and not directly in the VMCB control area.

Reported-by: Ashish Kalra <Ashish.Kalra@amd.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/svm/sev.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH 1/2] KVM: x86: implement KVM_SET_TSC_PRECISE/KVM_GET_TSC_PRECISE
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 11940569
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-17.2 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 0489FC8300F
	for <kvm@archiver.kernel.org>; Mon, 30 Nov 2020 13:38:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9AA96206F9
	for <kvm@archiver.kernel.org>; Mon, 30 Nov 2020 13:38:23 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Tt1dGVel"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727133AbgK3Nhv (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 30 Nov 2020 08:37:51 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:52603 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726562AbgK3Nhv (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 30 Nov 2020 08:37:51 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1606743383;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=bKiFS6Lws9oA3rk7NRSCGQgXKIwwrIC+IctjguilsU0=;
        b=Tt1dGVel1RMQ9Q/NF4fRzx7Xs04ZJZRZh/LJTGjFUr2JKcca5Wj6qVudXrPViQhlO6AWe4
        11mTfO3Wb82x9ysV5/SBNHJjEEs0ZqYZ97pVeLrbsGYHzUR8tato/953qub09DGg9oMz7i
        cqAoui1PLQSsblsWqrNCqW7Em9+EVHg=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-160-WcSt1KFBNEGqxdl7x2Dpvw-1; Mon, 30 Nov 2020 08:36:21 -0500
X-MC-Unique: WcSt1KFBNEGqxdl7x2Dpvw-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 2A98E873116;
        Mon, 30 Nov 2020 13:36:18 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.206.90])
        by smtp.corp.redhat.com (Postfix) with ESMTP id C136360C4D;
        Mon, 30 Nov 2020 13:36:11 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Oliver Upton <oupton@google.com>,
        Ingo Molnar <mingo@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        linux-kernel@vger.kernel.org (open list),
        Marcelo Tosatti <mtosatti@redhat.com>,
        Jonathan Corbet <corbet@lwn.net>,
        Wanpeng Li <wanpengli@tencent.com>,
        Borislav Petkov <bp@alien8.de>,
        Jim Mattson <jmattson@google.com>,
        "H. Peter Anvin" <hpa@zytor.com>,
        linux-doc@vger.kernel.org (open list:DOCUMENTATION),
        Joerg Roedel <joro@8bytes.org>,
        x86@kernel.org (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT)),
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH 1/2] KVM: x86: implement
 KVM_SET_TSC_PRECISE/KVM_GET_TSC_PRECISE
Date: Mon, 30 Nov 2020 15:35:58 +0200
Message-Id: <20201130133559.233242-2-mlevitsk@redhat.com>
In-Reply-To: <20201130133559.233242-1-mlevitsk@redhat.com>
References: <20201130133559.233242-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

These two new ioctls allow to more precisly capture and
restore guest's TSC state.

Both ioctls are meant to be used to accurately migrate guest TSC
even when there is a significant downtime during the migration.

Suggested-by: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Maxim Levitsky <mlevitsk@redhat.com>
---
 Documentation/virt/kvm/api.rst | 56 +++++++++++++++++++++++++++
 arch/x86/kvm/x86.c             | 69 ++++++++++++++++++++++++++++++++++
 include/uapi/linux/kvm.h       | 14 +++++++
 3 files changed, 139 insertions(+)

```
#### [PATCH 1/2] Update the kernel headers for 5.10-rc5 + TSC
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 11940575
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-17.2 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id BB1F0C64E7B
	for <kvm@archiver.kernel.org>; Mon, 30 Nov 2020 13:40:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 651B620727
	for <kvm@archiver.kernel.org>; Mon, 30 Nov 2020 13:40:39 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Dy6mme3t"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727320AbgK3Nka (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 30 Nov 2020 08:40:30 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:44476 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726426AbgK3Nk3 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 30 Nov 2020 08:40:29 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1606743542;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=uohsauvIsjYEA0XUxpazEHeSKdAgOCIc129bvX1wErE=;
        b=Dy6mme3tWeYDqCbdiEOzYEizlZw9VOoMLn3uxearhjeGCIbL1rxlBnkFmrIeUBsafj3lbQ
        A67D6HNFeOlTT6sTpIt2eyHSPRDRugb4ZIIF7ltrynwbpbLPlqcds0sbJLg3jLGZHat5bb
        y//Yr8VNEnh2D6t/a1zDxqpe3inVDHI=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-244-dur6NQcVP3WZhMlsigyNIg-1; Mon, 30 Nov 2020 08:38:58 -0500
X-MC-Unique: dur6NQcVP3WZhMlsigyNIg-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 7AD0C1009462;
        Mon, 30 Nov 2020 13:38:57 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.206.90])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 4982D60867;
        Mon, 30 Nov 2020 13:38:53 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: qemu-devel@nongnu.org
Cc: Richard Henderson <richard.henderson@linaro.org>,
        Marcelo Tosatti <mtosatti@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Eduardo Habkost <ehabkost@redhat.com>, kvm@vger.kernel.org,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH 1/2] Update the kernel headers for 5.10-rc5 + TSC
Date: Mon, 30 Nov 2020 15:38:44 +0200
Message-Id: <20201130133845.233552-2-mlevitsk@redhat.com>
In-Reply-To: <20201130133845.233552-1-mlevitsk@redhat.com>
References: <20201130133845.233552-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Signed-off-by: Maxim Levitsky <mlevitsk@redhat.com>
---
 include/standard-headers/asm-x86/kvm_para.h |  1 +
 linux-headers/asm-x86/kvm.h                 |  2 +
 linux-headers/linux/kvm.h                   | 70 ++++++++++++++++++++-
 3 files changed, 72 insertions(+), 1 deletion(-)

```
