#### [PATCH v8 1/5] Revert "KVM: X86: Fix setup the virt_spin_lock_key before static key get initialized"
##### From: Zhenzhong Duan <zhenzhong.duan@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhenzhong Duan <zhenzhong.duan@oracle.com>
X-Patchwork-Id: 11206363
Return-Path: <SRS0=2s9g=YQ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DBB4B1390
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Oct 2019 11:19:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id BA7562064A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Oct 2019 11:19:28 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="oG5lPmNM"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2404713AbfJWLTY (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 23 Oct 2019 07:19:24 -0400
Received: from userp2130.oracle.com ([156.151.31.86]:52696 "EHLO
        userp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2404543AbfJWLTT (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 23 Oct 2019 07:19:19 -0400
Received: from pps.filterd (userp2130.oracle.com [127.0.0.1])
        by userp2130.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 x9NB9Rdq066205;
        Wed, 23 Oct 2019 11:17:12 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references; s=corp-2019-08-05;
 bh=Rba9xErGxwUOOcVXLsuAqyh9LPvNTmKNCGcbMviKams=;
 b=oG5lPmNMGT7oRnyx5EPn5RIYKLrUlkR1ya78gjkq1izslklewkJJEcfyhDnbD6le5FrN
 gFzAVplT+RfTwWeO1/akoBp1bBdj9ga0M7rR65CXAaKV/VWq3hLHfvWmSkkqnDivqxJK
 vME7lmhQzkUibKvHL5LqPxeFUJgtUpnO3DGceNO2ErkS5inEQqOVL2d6U/faTb80NJ2Z
 KdYWret3cYiZX2tE/LAxtAn9tSn9giyjmyxNBPeIZNFREhDiK28xa+9WYY0104IctvIL
 Q2KbrKZCsDwL4VJH57YzrGpp+ToptDi8cMRAWpFAmvvpNd1IknuSzH8CQQkwzQmG9RdH zw==
Received: from userp3020.oracle.com (userp3020.oracle.com [156.151.31.79])
        by userp2130.oracle.com with ESMTP id 2vqswtmren-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 23 Oct 2019 11:17:12 +0000
Received: from pps.filterd (userp3020.oracle.com [127.0.0.1])
        by userp3020.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 x9NBDXth139491;
        Wed, 23 Oct 2019 11:17:11 GMT
Received: from userv0122.oracle.com (userv0122.oracle.com [156.151.31.75])
        by userp3020.oracle.com with ESMTP id 2vsp4229cv-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 23 Oct 2019 11:17:11 +0000
Received: from abhmp0015.oracle.com (abhmp0015.oracle.com [141.146.116.21])
        by userv0122.oracle.com (8.14.4/8.14.4) with ESMTP id x9NBH8rp012026;
        Wed, 23 Oct 2019 11:17:08 GMT
Received: from z2.cn.oracle.com (/10.182.71.218)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Wed, 23 Oct 2019 04:17:08 -0700
From: Zhenzhong Duan <zhenzhong.duan@oracle.com>
To: linux-kernel@vger.kernel.org
Cc: tglx@linutronix.de, mingo@redhat.com, bp@alien8.de, x86@kernel.org,
        pbonzini@redhat.com, rkrcmar@redhat.com,
        sean.j.christopherson@intel.com, vkuznets@redhat.com,
        wanpengli@tencent.com, jmattson@google.com, joro@8bytes.org,
        boris.ostrovsky@oracle.com, jgross@suse.com, peterz@infradead.org,
        will@kernel.org, linux-hyperv@vger.kernel.org, kvm@vger.kernel.org,
        mikelley@microsoft.com, kys@microsoft.com, haiyangz@microsoft.com,
        sthemmin@microsoft.com, sashal@kernel.org,
        Zhenzhong Duan <zhenzhong.duan@oracle.com>,
        "H. Peter Anvin" <hpa@zytor.com>
Subject: [PATCH v8 1/5] Revert "KVM: X86: Fix setup the virt_spin_lock_key
 before static key get initialized"
Date: Wed, 23 Oct 2019 19:16:20 +0800
Message-Id: <1571829384-5309-2-git-send-email-zhenzhong.duan@oracle.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1571829384-5309-1-git-send-email-zhenzhong.duan@oracle.com>
References: <1571829384-5309-1-git-send-email-zhenzhong.duan@oracle.com>
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9418
 signatures=668684
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=1
 malwarescore=0
 phishscore=0 bulkscore=0 spamscore=0 mlxscore=0 mlxlogscore=999
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.0.1-1908290000 definitions=main-1910230114
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9418
 signatures=668684
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 priorityscore=1501 malwarescore=0
 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0 clxscore=1015
 lowpriorityscore=0 mlxscore=0 impostorscore=0 mlxlogscore=999 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.0.1-1908290000
 definitions=main-1910230114
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This reverts commit 34226b6b70980a8f81fff3c09a2c889f77edeeff.

Commit 8990cac6e5ea ("x86/jump_label: Initialize static branching
early") adds jump_label_init() call in setup_arch() to make static
keys initialized early, so we could use the original simpler code
again.

The similar change for XEN is in commit 090d54bcbc54 ("Revert
"x86/paravirt: Set up the virt_spin_lock_key after static keys get
initialized"")

Signed-off-by: Zhenzhong Duan <zhenzhong.duan@oracle.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krcmar <rkrcmar@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>
Cc: Wanpeng Li <wanpengli@tencent.com>
Cc: Jim Mattson <jmattson@google.com>
Cc: Joerg Roedel <joro@8bytes.org>
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: Borislav Petkov <bp@alien8.de>
Cc: "H. Peter Anvin" <hpa@zytor.com>
---
 arch/x86/kernel/kvm.c | 12 +++---------
 1 file changed, 3 insertions(+), 9 deletions(-)

```
#### [patch V2 01/17] x86/entry/32: Remove unused resume_userspace labelReferences: <20191023122705.198339581@linutronix.de>
##### From: Thomas Gleixner <tglx@linutronix.de>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Gleixner <tglx@linutronix.de>
X-Patchwork-Id: 11206563
Return-Path: <SRS0=2s9g=YQ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CAA1C112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Oct 2019 12:31:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B1C5821928
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Oct 2019 12:31:40 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2391357AbfJWMbk (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 23 Oct 2019 08:31:40 -0400
Received: from Galois.linutronix.de ([193.142.43.55]:49086 "EHLO
        Galois.linutronix.de" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2389662AbfJWMbj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 23 Oct 2019 08:31:39 -0400
Received: from localhost ([127.0.0.1] helo=nanos.tec.linutronix.de)
        by Galois.linutronix.de with esmtp (Exim 4.80)
        (envelope-from <tglx@linutronix.de>)
        id 1iNFnb-00016u-4Z; Wed, 23 Oct 2019 14:31:35 +0200
Message-Id: <20191023123117.686514045@linutronix.de>
User-Agent: quilt/0.65
Date: Wed, 23 Oct 2019 14:27:06 +0200
From: Thomas Gleixner <tglx@linutronix.de>
To: LKML <linux-kernel@vger.kernel.org>
Cc: x86@kernel.org, Peter Zijlstra <peterz@infradead.org>,
        Andy Lutomirski <luto@kernel.org>,
        Will Deacon <will@kernel.org>,
        Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org,
        linux-arch@vger.kernel.org, Mike Rapoport <rppt@linux.ibm.com>,
        Josh Poimboeuf <jpoimboe@redhat.com>,
        Miroslav Benes <mbenes@suse.cz>
Subject: [patch V2 01/17] x86/entry/32: Remove unused resume_userspace label
References: <20191023122705.198339581@linutronix.de>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The C reimplementation of SYSENTER left that unused ENTRY() label
around. Remove it.

Fixes: 5f310f739b4c ("x86/entry/32: Re-implement SYSENTER using the new C path")
Originally-by: Peter Zijlstra <peterz@infradead.org>
Signed-off-by: Thomas Gleixner <tglx@linutronix.de>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/entry/entry_32.S |    1 -
```
#### [GIT PULL] VFIO fixes for v5.4-rc5
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alex Williamson <alex.williamson@redhat.com>
X-Patchwork-Id: 11207251
Return-Path: <SRS0=2s9g=YQ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 08BD313BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Oct 2019 17:08:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D937B2086D
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Oct 2019 17:08:27 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="HSA3CAJQ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727811AbfJWRI0 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 23 Oct 2019 13:08:26 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:51713 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1727648AbfJWRI0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 23 Oct 2019 13:08:26 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1571850505;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=5i2V5gs6KA30KkIAaoVKaoCZzrYOsax9Xuom4ymjp0I=;
        b=HSA3CAJQCcWfRrg5C4QFw1ua+dqI7FIP+K+yt7PSlewtX4IvVM8PUsAYAGv0MZA2zqG16x
        R9sgK9PJzXj4SdfmAM/Hc2ezh9XOcDNMhNxBeiA/DHISf+dYO20/yI6JBY757XZHOcgtff
        smkANaaRKOCkrMvPgvTlhdLomETVXqI=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-261-k0Itp5FhNDqb_6KHYPi4AQ-1; Wed, 23 Oct 2019 13:08:23 -0400
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 0BC6C800D49;
        Wed, 23 Oct 2019 17:08:23 +0000 (UTC)
Received: from x1.home (ovpn-118-102.phx2.redhat.com [10.3.118.102])
        by smtp.corp.redhat.com (Postfix) with ESMTP id C424260BE1;
        Wed, 23 Oct 2019 17:08:22 +0000 (UTC)
Date: Wed, 23 Oct 2019 11:08:22 -0600
From: Alex Williamson <alex.williamson@redhat.com>
To: Linus Torvalds <torvalds@linux-foundation.org>
Cc: "kvm@vger.kernel.org" <kvm@vger.kernel.org>,
        "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>
Subject: [GIT PULL] VFIO fixes for v5.4-rc5
Message-ID: <20191023110822.6122562f@x1.home>
Organization: Red Hat
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
X-MC-Unique: k0Itp5FhNDqb_6KHYPi4AQ-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Linus,

The following changes since commit 4f5cafb5cb8471e54afdc9054d973535614f7675:

  Linux 5.4-rc3 (2019-10-13 16:37:36 -0700)

are available in the Git repository at:

  git://github.com/awilliam/linux-vfio.git tags/vfio-v5.4-rc5

for you to fetch changes up to 95f89e090618efca63918b658c2002e57d393036:

  vfio/type1: Initialize resv_msi_base (2019-10-15 14:07:01 -0600)

----------------------------------------------------------------
VFIO fixes for v5.4-rc5

 - Fix (false) uninitialized variable warning (Joerg Roedel)

----------------------------------------------------------------
Joerg Roedel (1):
      vfio/type1: Initialize resv_msi_base

 drivers/vfio/vfio_iommu_type1.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)
```
#### [PATCH v2 1/3] kcov: remote coverage supportFrom: Andrey Konovalov <andreyknvl@google.com>
##### From: Andrey Konovalov <andreyknvl@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrey Konovalov <andreyknvl@google.com>
X-Patchwork-Id: 11207025
Return-Path: <SRS0=2s9g=YQ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6268F13BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Oct 2019 15:25:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 2C8EF21D71
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Oct 2019 15:25:05 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="vdU45X1q"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2392432AbfJWPZE (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 23 Oct 2019 11:25:04 -0400
Received: from mail-wr1-f73.google.com ([209.85.221.73]:54162 "EHLO
        mail-wr1-f73.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2406682AbfJWPYm (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 23 Oct 2019 11:24:42 -0400
Received: by mail-wr1-f73.google.com with SMTP id i10so11172358wrb.20
        for <kvm@vger.kernel.org>; Wed, 23 Oct 2019 08:24:39 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=QEWok5XzYtqqso1VZwcCBlXTZxUGFCIPb4s7g3hvBiY=;
        b=vdU45X1qI1SPQIwqFB2P3CsFq1aw79uRooHnC0Lkplyf/8ekhc9prAYo5Wr/DZOkaN
         CWSuhHd87FjaN7oPX04E2hgEZYr+NKYFYfqdsgiAOhVOYKJER3OlYmbPcZYDF/tAmi8p
         yPjdAi9blln+d4Uf+x01xV91rGhSPygELcDRyO4IPQudZyHwhfilKWDv4LZ638ZTr6nr
         HeyBTjMqOG55o0kvy/sVH+oOtkMdoZSPE2XAgHb8oOb3yq7btXOuRcmzk7g4+/Q86pxZ
         e+reMgYA++g5Sled6JnQdV/gh+WbSrGtbL8Hq6rK7rsc1Rngsk3Y/6sa7MCqMYOhwp+n
         E0Cg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=QEWok5XzYtqqso1VZwcCBlXTZxUGFCIPb4s7g3hvBiY=;
        b=d5mwZO8PWCZr4djGtWGzvYLgbrWHfEJFAjS+eZ1tkzDQjvGnaYkF8Sl90zSQ+sBPLP
         LEU0dKk0VHRcji8pfefYmk4t0wGNTEx3ZMW4ZyyoQYVEsH7+dKtj4+dGs+IVer7RwOcw
         O2k4k6kqYabWX6k12hxQHXCYImSp99Ips7iej+kueRQR/17//wwur0r6vBfQss57Qejk
         7b8lohVJ0EvFi4kRSZwTd/UXMrTtuojXbLmbFMWgiMRmwn1hThu2b2CtV/3vC9PK/Xgt
         DWRiHINZq3AKTREMVoQQwuW0XfKhlk95WkKqAPAiLkkBKl+czPDQOoXNJN/nBluI4bp5
         l6NQ==
X-Gm-Message-State: APjAAAWxMfpmXFMZf2SwtaAv2BOpVfK3J6+PLVRNFe/i11QVu6RHIlo4
        oCg9SV4OejzwtiXhxpgMau1JKA2mWvWKPvIG
X-Google-Smtp-Source: 
 APXvYqwZKhKN1SJ+sA9bxS3UfAxxydol53Yhl+Y5tllj2eT1BNWf31IGlf8fxR2T9vCUVEbAH1mzbAFB+K4wtMIw
X-Received: by 2002:a5d:4847:: with SMTP id n7mr8847419wrs.398.1571844278984;
 Wed, 23 Oct 2019 08:24:38 -0700 (PDT)
Date: Wed, 23 Oct 2019 17:24:29 +0200
In-Reply-To: <cover.1571844200.git.andreyknvl@google.com>
Message-Id: 
 <beeae42e313ef57b4630cc9f36e2e78ad42fd5b7.1571844200.git.andreyknvl@google.com>
Mime-Version: 1.0
References: <cover.1571844200.git.andreyknvl@google.com>
X-Mailer: git-send-email 2.24.0.rc0.303.g954a862665-goog
Subject: [PATCH v2 1/3] kcov: remote coverage support
From: Andrey Konovalov <andreyknvl@google.com>
To: linux-usb@vger.kernel.org, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        linux-kernel@vger.kernel.org, Dmitry Vyukov <dvyukov@google.com>,
        Greg Kroah-Hartman <gregkh@linuxfoundation.org>,
        Alan Stern <stern@rowland.harvard.edu>,
        "Michael S . Tsirkin" <mst@redhat.com>,
        Jason Wang <jasowang@redhat.com>
Cc: Andrew Morton <akpm@linux-foundation.org>,
        Arnd Bergmann <arnd@arndb.de>,
        Steven Rostedt <rostedt@goodmis.org>,
        David Windsor <dwindsor@gmail.com>,
        Elena Reshetova <elena.reshetova@intel.com>,
        Anders Roxell <anders.roxell@linaro.org>,
        Alexander Potapenko <glider@google.com>,
        Marco Elver <elver@google.com>,
        Andrey Konovalov <andreyknvl@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch adds background thread coverage collection ability to kcov.

With KCOV_ENABLE coverage is collected only for syscalls that are issued
from the current process. With KCOV_REMOTE_ENABLE it's possible to collect
coverage for arbitrary parts of the kernel code, provided that those parts
are annotated with kcov_remote_start()/kcov_remote_stop().

This allows to collect coverage from two types of kernel background
threads: the global ones, that are spawned during kernel boot and are
always running (e.g. USB hub_event()); and the local ones, that are
spawned when a user interacts with some kernel interface (e.g. vhost
workers).

To enable collecting coverage from a global background thread, a unique
global handle must be assigned and passed to the corresponding
kcov_remote_start() call. Then a userspace process can pass a list of such
handles to the KCOV_REMOTE_ENABLE ioctl in the handles array field of the
kcov_remote_arg struct. This will attach the used kcov device to the code
sections, that are referenced by those handles.

Since there might be many local background threads spawned from different
userspace processes, we can't use a single global handle per annotation.
Instead, the userspace process passes a non-zero handle through the
common_handle field of the kcov_remote_arg struct. This common handle gets
saved to the kcov_handle field in the current task_struct and needs to be
passed to the newly spawned threads via custom annotations. Those threads
should in turn be annotated with kcov_remote_start()/kcov_remote_stop().

Internally kcov stores handles as u64 integers. The top byte of a handle
is used to denote the id of a subsystem that this handle belongs to, and
the lower 4 bytes are used to denote a handle id within that subsystem.
A reserved value 0 is used as a subsystem id for common handles as they
don't belong to a particular subsystem. The bytes 4-7 are currently
reserved and must be zero. In the future the number of bytes used for the
subsystem or handle ids might be increased.

When a particular userspace proccess collects coverage by via a common
handle, kcov will collect coverage for each code section that is annotated
to use the common handle obtained as kcov_handle from the current
task_struct. However non common handles allow to collect coverage
selectively from different subsystems.

Signed-off-by: Andrey Konovalov <andreyknvl@google.com>
---
 Documentation/dev-tools/kcov.rst | 128 +++++++++
 include/linux/kcov.h             |  23 ++
 include/linux/sched.h            |   6 +
 include/uapi/linux/kcov.h        |  25 ++
 kernel/kcov.c                    | 480 ++++++++++++++++++++++++++++---
 5 files changed, 627 insertions(+), 35 deletions(-)

```
#### [PATCH] kvm: call kvm_arch_destroy_vm if vm creation failsFrom: Jim Mattson <jmattson@google.com>
##### From: Jim Mattson <jmattson@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jim Mattson <jmattson@google.com>
X-Patchwork-Id: 11207285
Return-Path: <SRS0=2s9g=YQ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D5906112C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Oct 2019 17:14:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B3EB921925
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Oct 2019 17:14:48 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="smHdWwvV"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728244AbfJWROr (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 23 Oct 2019 13:14:47 -0400
Received: from mail-pl1-f202.google.com ([209.85.214.202]:45338 "EHLO
        mail-pl1-f202.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727079AbfJWROr (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 23 Oct 2019 13:14:47 -0400
Received: by mail-pl1-f202.google.com with SMTP id c8so176786pll.12
        for <kvm@vger.kernel.org>; Wed, 23 Oct 2019 10:14:47 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=WJ/03uRoTlVpADfzmCIe76ZMMoZAaSrMg9ZFGLQJXxY=;
        b=smHdWwvV8h/6x4uHdE7piSpoaY0fkzYr//VL02d0BTCFk13SZpWyLSV0mSgPiSdlBK
         DeS8A+YwBhWJZdeTL6pBRyRUguTiHO3NcsteSNXgge9xhKwsg92rOlNL1hPgrbbDNpN5
         Pm4UnOzzUI6zv7rvZ2dsHYhyk8Kw3VZ2NdckRn7Q1TgyefSnNTEJeYrv1O9L5N0JquEw
         AR/BdqBkFOziAUwjMxa101pR5+RBojV0356Zjua6foTfTqAbrzwGzvwEdbyVmylDmpmg
         RYiOUgjUa6I2F21MSEVixPAytb5XiWOOWi7JJtr94iozzDJWwABz3d31eG9uA61366gX
         QRsg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=WJ/03uRoTlVpADfzmCIe76ZMMoZAaSrMg9ZFGLQJXxY=;
        b=JXAAvDAxKjSZ7NupU0EzsP0YJED7m3omNiAWuc1l0WvSnE5gr/83j58Z5miCQDoD2l
         XAkughIA+N9LtOntuWcxV/ISNBv0YV8JoeHCMbgu68jkO7MIPYafgF8QCBjfNu5VwPRm
         0ZBIXppA81MvMaDwcRV18XOrc1i4Ue8xMc+vXm92Cqg1jCBPl9mmIMLHt4jszYLK7pgX
         mh3j9LB8JxREA3F7FZe3M07fA2DbaoYmUTSTSiboSsqQ3uSJcIA3DZGL7OB1IK3yucKk
         blHrX/DlVE/N2sO2A8+KZsY8Bm1aYLS2aSU1EbAKr6s+1JFVMQl7eAMX0MCPJ5Ug+CL3
         3FCg==
X-Gm-Message-State: APjAAAVGoK5/Ivpud7pUcZJYAMyH9ZcmcXf7+CFoZF0JNuR72e4wUEL7
        YGHa9fUgDIWo2PrImol9FWS77NSfbpQrfeQR93SQKSoaxZ6hbBqSaMgH5824JDCSLlCQqrO8ew7
        Qi3Cot4PQXJA9Tjb/68GRgDnBiTnFB036ZJQH9ZV4xcQZka6nEe9gpF2yOUdx2yE=
X-Google-Smtp-Source: 
 APXvYqyxHz53bvCG8ncILIL85SxrTEuT40NjvKBHrPUWufe0tMQxSB3jYG+9wwX0Oto5OT4AUyDRz9ZKyAgB2A==
X-Received: by 2002:a63:1c24:: with SMTP id
 c36mr11116121pgc.292.1571850886485;
 Wed, 23 Oct 2019 10:14:46 -0700 (PDT)
Date: Wed, 23 Oct 2019 10:14:35 -0700
Message-Id: <20191023171435.46287-1-jmattson@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.23.0.866.gb869b98d4c-goog
Subject: [PATCH] kvm: call kvm_arch_destroy_vm if vm creation fails
From: Jim Mattson <jmattson@google.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: John Sperbeck <jsperbeck@google.com>,
        Jim Mattson <jmattson@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: John Sperbeck <jsperbeck@google.com>

In kvm_create_vm(), if we've successfully called kvm_arch_init_vm(), but
then fail later in the function, we need to call kvm_arch_destroy_vm()
so that it can do any necessary cleanup (like freeing memory).

Fixes: 44a95dae1d229a ("KVM: x86: Detect and Initialize AVIC support")
Signed-off-by: John Sperbeck <jsperbeck@google.com>
Signed-off-by: Jim Mattson <jmattson@google.com>
---
 virt/kvm/kvm_main.c | 4 +++-
 1 file changed, 3 insertions(+), 1 deletion(-)

```
#### [PATCH kvm-unit-tests] Revert "lib: use an argument which doesn't require default argument promotion"
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11206051
Return-Path: <SRS0=2s9g=YQ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5B8B813BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Oct 2019 09:03:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 388F221925
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Oct 2019 09:03:48 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="tXiLamF0"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2390846AbfJWJDr (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 23 Oct 2019 05:03:47 -0400
Received: from mail-wm1-f68.google.com ([209.85.128.68]:35189 "EHLO
        mail-wm1-f68.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2390828AbfJWJDq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 23 Oct 2019 05:03:46 -0400
Received: by mail-wm1-f68.google.com with SMTP id v6so1839673wmj.0
        for <kvm@vger.kernel.org>; Wed, 23 Oct 2019 02:03:45 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=roq6c70I9GjqFiiJIml3zwcN2Gf7Xs/5uP2UjYMVVNs=;
        b=tXiLamF0x3ALrB7lD6lXpSU2Bnm1OzuFcUxDSPnSK3yenyUrvbtMJBI6BxvWXdhM3U
         BWrZPYfRxiAuIv2Fdg5WSwlkTzN0SZNEY9WiBp2XUKOdseqauAMqLKPkno/8iPu/VzBW
         mrRCp3E5QS0LlE7JigmxCBwRA1FOMA3PSKFcUFJrVhgAWcRita3AjP5FOKSxQ6Srl6f1
         lsZqIeKPwxEofFw0kVRld225z6Kor2VGszeP7GoeKte6zNd5FhymqOZFagZP4UjSVsbi
         +3epGUgSk2oSe3d/fht0fiCMtNHwLt/uhTqmy89Utzgedi89fKvTGYsfdJbSw2kyyJeB
         lpOg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id
         :mime-version:content-transfer-encoding;
        bh=roq6c70I9GjqFiiJIml3zwcN2Gf7Xs/5uP2UjYMVVNs=;
        b=pautK0Megws82af+DnxbsSIKNJwG/5viIY3mxdbQBqgAvXeu2yGC95DHWt/VYK7OrP
         /xMswAoypmTyDJraP/hvsAA6fE/VKT4Ku1h35Id5CbA7EBZo52HS1iXQbKe+NDFPjwiU
         WYuXeO2gKEOMtnyQLZF+pffsrL+5EXN3fCm1lWkwZPzFc+0vpQNCss735i3YGwvZk7N2
         Ghd9EzGvgACNW0+VadnRJ2y149vpD/CJ6pePsgdAjrGR+TwH5sRBX2BYZ82/Q/d+Sl2B
         sCQF3RG+T/FB/GSqmv26OUnqY9dynDdHamCYYWKLNIxA1pJov4uFi4mIg35UifOuMnGC
         JGdA==
X-Gm-Message-State: APjAAAVfElO81ex0kcPShTrQH4H6NV6ArfkcjHXaMDVhikQc6AocMmyG
        qU6K3z84ev2KFJWhVl+1Z3+fEYCG
X-Google-Smtp-Source: 
 APXvYqwyaVs2q4cjr8NVZAnNe9P2nAAKovR3WDd064gNU86GlGf8WQEeggEyxZDqHmZR3fJGJIwM1w==
X-Received: by 2002:a7b:c24a:: with SMTP id b10mr6693651wmj.124.1571821424052;
        Wed, 23 Oct 2019 02:03:44 -0700 (PDT)
Received: from donizetti.lan ([2001:b07:6468:f312:51de:b137:4c45:7cea])
        by smtp.gmail.com with ESMTPSA id
 u7sm14997531wre.59.2019.10.23.02.03.43
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 23 Oct 2019 02:03:43 -0700 (PDT)
From: Paolo Bonzini <pbonzini@redhat.com>
To: kvm@vger.kernel.org
Cc: Thomas Huth <thuth@redhat.com>
Subject: [PATCH kvm-unit-tests] Revert "lib: use an argument which doesn't
 require default argument promotion"
Date: Wed, 23 Oct 2019 11:03:43 +0200
Message-Id: <20191023090343.7064-1-pbonzini@redhat.com>
X-Mailer: git-send-email 2.21.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This reverts commit c09c54c66b1df63cd11a75859cf53527d1c6e959.
The s390x selftest, for example, passes a uintptr_t whose nonzero bits
are all above bit 31.  Therefore, the argument is truncated to zero if
it is unsigned rather than bool.

Reported-by: Thomas Huth <thuth@redhat.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 lib/libcflat.h | 4 ++--
 lib/report.c   | 4 ++--
 2 files changed, 4 insertions(+), 4 deletions(-)

```
#### [kvm-unit-tests PATCH] s390x: Fix selftest malloc check
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11205987
Return-Path: <SRS0=2s9g=YQ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F257E13B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Oct 2019 08:40:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D9DE121872
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Oct 2019 08:40:30 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2390150AbfJWIka (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 23 Oct 2019 04:40:30 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:43010 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S2390034AbfJWIk3 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 23 Oct 2019 04:40:29 -0400
Received: from pps.filterd (m0098413.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 x9N8atcC023281
        for <kvm@vger.kernel.org>; Wed, 23 Oct 2019 04:40:28 -0400
Received: from e06smtp05.uk.ibm.com (e06smtp05.uk.ibm.com [195.75.94.101])
        by mx0b-001b2d01.pphosted.com with ESMTP id 2vtgjrwr1w-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Wed, 23 Oct 2019 04:40:28 -0400
Received: from localhost
        by e06smtp05.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Wed, 23 Oct 2019 09:40:26 +0100
Received: from b06avi18878370.portsmouth.uk.ibm.com (9.149.26.194)
        by e06smtp05.uk.ibm.com (192.168.101.135) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Wed, 23 Oct 2019 09:40:23 +0100
Received: from d06av25.portsmouth.uk.ibm.com (d06av25.portsmouth.uk.ibm.com
 [9.149.105.61])
        by b06avi18878370.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id x9N8eMNd41157048
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 23 Oct 2019 08:40:23 GMT
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id DB77611C050;
        Wed, 23 Oct 2019 08:40:22 +0000 (GMT)
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 02E5E11C058;
        Wed, 23 Oct 2019 08:40:22 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.152.224.131])
        by d06av25.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Wed, 23 Oct 2019 08:40:21 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, thuth@redhat.com, david@redhat.com,
        borntraeger@de.ibm.com
Subject: [kvm-unit-tests PATCH] s390x: Fix selftest malloc check
Date: Wed, 23 Oct 2019 04:40:17 -0400
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 19102308-0020-0000-0000-0000037CF971
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19102308-0021-0000-0000-000021D339B5
Message-Id: <20191023084017.13142-1-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-10-23_02:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=878 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1908290000 definitions=main-1910230086
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Commit c09c54c ("lib: use an argument which doesn't require default
argument promotion") broke the selftest. Let's fix it by converting
the binary operations to bool.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
---
 s390x/selftest.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH V5 1/6] mdev: class id support
##### From: Jason Wang <jasowang@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 11206793
Return-Path: <SRS0=2s9g=YQ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8E44A139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Oct 2019 13:14:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5AB6E21925
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Oct 2019 13:14:33 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="FFzYOHOp"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2404801AbfJWNOc (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 23 Oct 2019 09:14:32 -0400
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:26887 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1731608AbfJWNO3 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 23 Oct 2019 09:14:29 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1571836467;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=TjCPajc4CEGR5rS6ag/k9ArXmJclaoe4P99dbfRjJ0k=;
        b=FFzYOHOp5bgyHv0UgvTqBFGERcfrWY5YIROkg1QANj2GybafZtrmKe1680U4G+H24Ghz6Y
        mO2Yz0wBjfsBX6lcXr5FZpdSPO0qofxjmsll8qcN50SXCv0LVx4Ss5CWnW8OlnGu3GbDLZ
        nVESK3Mlw3hvDFsd3USaekz2a6OnFTo=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-295-p1Bzi35XNCiDsbI1W_34VA-1; Wed, 23 Oct 2019 09:14:23 -0400
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 5AA7B800D58;
        Wed, 23 Oct 2019 13:14:17 +0000 (UTC)
Received: from jason-ThinkPad-X1-Carbon-6th.redhat.com
 (ovpn-12-126.pek2.redhat.com [10.72.12.126])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 90B7460161;
        Wed, 23 Oct 2019 13:11:00 +0000 (UTC)
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
Subject: [PATCH V5 1/6] mdev: class id support
Date: Wed, 23 Oct 2019 21:07:47 +0800
Message-Id: <20191023130752.18980-2-jasowang@redhat.com>
In-Reply-To: <20191023130752.18980-1-jasowang@redhat.com>
References: <20191023130752.18980-1-jasowang@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
X-MC-Unique: p1Bzi35XNCiDsbI1W_34VA-1
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

Signed-off-by: Jason Wang <jasowang@redhat.com>
Reviewed-by: Parav Pandit <parav@mellanox.com>
---
 .../driver-api/vfio-mediated-device.rst       |  5 +++++
 drivers/gpu/drm/i915/gvt/kvmgt.c              |  1 +
 drivers/s390/cio/vfio_ccw_ops.c               |  1 +
 drivers/s390/crypto/vfio_ap_ops.c             |  1 +
 drivers/vfio/mdev/mdev_core.c                 | 18 +++++++++++++++
 drivers/vfio/mdev/mdev_driver.c               | 22 +++++++++++++++++++
 drivers/vfio/mdev/mdev_private.h              |  1 +
 drivers/vfio/mdev/vfio_mdev.c                 |  6 +++++
 include/linux/mdev.h                          |  8 +++++++
 include/linux/mod_devicetable.h               |  8 +++++++
 samples/vfio-mdev/mbochs.c                    |  1 +
 samples/vfio-mdev/mdpy.c                      |  1 +
 samples/vfio-mdev/mtty.c                      |  1 +
 13 files changed, 74 insertions(+)

```
#### [PATCH v2] kvm: call kvm_arch_destroy_vm if vm creation failsFrom: Jim Mattson <jmattson@google.com>
##### From: Jim Mattson <jmattson@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jim Mattson <jmattson@google.com>
X-Patchwork-Id: 11207671
Return-Path: <SRS0=2s9g=YQ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9FA1F14E5
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Oct 2019 20:32:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7CDDF21A4C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Oct 2019 20:32:25 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="MDqELEo4"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2391687AbfJWUcY (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 23 Oct 2019 16:32:24 -0400
Received: from mail-pf1-f202.google.com ([209.85.210.202]:39517 "EHLO
        mail-pf1-f202.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2388677AbfJWUcY (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 23 Oct 2019 16:32:24 -0400
Received: by mail-pf1-f202.google.com with SMTP id b13so17090295pfp.6
        for <kvm@vger.kernel.org>; Wed, 23 Oct 2019 13:32:23 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=txjVxphi0JgMAhiXdu45Aboz+iV2caaNMJ4JRuuqpxE=;
        b=MDqELEo47/NaPNHQuqgkxJrOLAaVgO0yban7wY336qIsboI0+z5rOubRTnm3MnPffx
         0S0PN/N3RvgLK0s1XCK0FzBdTwHukXA6G0DEuC3FqHD2m981ZJEaV5Xif4xi4azuJlsS
         WRTLIho9mwz2E25N5SvZT5a9PATbZc/K7etAny1V8AsfUSfnj0sDOLsRGn050APUeK+2
         zbJExbp4Hy41U4wQVvHMIEzlpqyCOGPT5++0MTcMK6eRXnJdngsFP6x6AqmEZN5kyIyR
         7XBMtyBu8GlAJLUECGog5xBTbn/bfBUrFtX/6mLZkYTW2i/jCqKJs1tx8HwLYxxuT1BP
         7xpA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=txjVxphi0JgMAhiXdu45Aboz+iV2caaNMJ4JRuuqpxE=;
        b=YUUm3KT1/Umrl7i3Z3CYXaosWX3P2h4ERcyQqLw4sJA0A7/rJoX5kcxx6ndatJc+Hj
         ccfFRVqRAJ3AbFlxXVvt4wSIysbkVPXH+Isz9TXuoy7s8PSauiyt+1zcAUlgqB2H+GYq
         rg1/JydOxpsuuVM97y6MnSj/Xt0p5oFmKCCz6CaTn/xE3Fb8nExNVzMkq31QGqqafna5
         TTyV9RdhlQr2J1qrrYTZllAxFwWH77e4PxgnZ988fFpUeTR3M365xJvxfAZ9myl04ksX
         VcGiyuugJESjIcRzlyiSwBiT1u+t0AfNfd7EGhPdB8zwjMNjb8EKirK+vwFQY1X/ETlq
         BQ0Q==
X-Gm-Message-State: APjAAAXzt58LZBBOocmv3ELiDV7BeTSPV9fuQqx7eqOI2/I1YMIlCQGR
        cYjwGA+7llCja25AmHu+dzP3QFKkpYt/D65stj763SC7L16LNJXLXB3P5IA231AseqsZPkD6Bqg
        3IwXzgCDm5KSns0ZI2kBAyRqh1FFtN5n6yj1sCOYgeeEvnAdBgIkVofiHHylnOhs=
X-Google-Smtp-Source: 
 APXvYqx+xU0D9wXKBzKqRj8NkoyW4D9BV8hhAJgwCufWVNS/RVGae6b5w0uGKo6OJd6J8PtxS58t3BLowMNmtw==
X-Received: by 2002:a63:5d04:: with SMTP id r4mr8975223pgb.22.1571862743209;
 Wed, 23 Oct 2019 13:32:23 -0700 (PDT)
Date: Wed, 23 Oct 2019 13:32:14 -0700
Message-Id: <20191023203214.93252-1-jmattson@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.24.0.rc0.303.g954a862665-goog
Subject: [PATCH v2] kvm: call kvm_arch_destroy_vm if vm creation fails
From: Jim Mattson <jmattson@google.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>
Cc: John Sperbeck <jsperbeck@google.com>,
        Jim Mattson <jmattson@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: John Sperbeck <jsperbeck@google.com>

In kvm_create_vm(), if we've successfully called kvm_arch_init_vm(), but
then fail later in the function, we need to call kvm_arch_destroy_vm()
so that it can do any necessary cleanup (like freeing memory).

Fixes: 44a95dae1d229a ("KVM: x86: Detect and Initialize AVIC support")
Signed-off-by: John Sperbeck <jsperbeck@google.com>
Signed-off-by: Jim Mattson <jmattson@google.com>
---
 v1 -> v2: Call kvm_arch_destroy_vm before refcount_set
 
 virt/kvm/kvm_main.c | 4 +++-
 1 file changed, 3 insertions(+), 1 deletion(-)

```
#### [PATCH net-next 01/14] vsock/vmci: remove unused VSOCK_DEFAULT_CONNECT_TIMEOUT
##### From: Stefano Garzarella <sgarzare@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stefano Garzarella <sgarzare@redhat.com>
X-Patchwork-Id: 11206193
Return-Path: <SRS0=2s9g=YQ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D77D81575
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Oct 2019 09:56:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B63972064B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Oct 2019 09:56:28 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="azPWANGd"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2390321AbfJWJ4W (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 23 Oct 2019 05:56:22 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:20634 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S2390978AbfJWJ4V (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 23 Oct 2019 05:56:21 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1571824580;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=aPIIe5WRZMPBUYONsseioAXZoYWf/JAlNNMg8lPt4/Q=;
        b=azPWANGdvj4l7XN7Fvr1B/9iA+AJyk8SeV3A7cvN3uLpWd84r4Xq13Dn4zJx7pNUo6yoS9
        QrhcL7LU8enuJ978G/bzo17GQRjWC4aLgdVmb9lAagq3mAS7sOJ99ziUxYWfZfflBLcNlZ
        2uM8/WKV2zH0Bl3BnSmQ8kP7cluHtbw=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-378-FiyjSVSIOxmusT0AUBY3yw-1; Wed, 23 Oct 2019 05:56:16 -0400
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 87C66107AD33;
        Wed, 23 Oct 2019 09:56:14 +0000 (UTC)
Received: from steredhat.redhat.com (unknown [10.36.118.164])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 11CFC5C1B2;
        Wed, 23 Oct 2019 09:56:05 +0000 (UTC)
From: Stefano Garzarella <sgarzare@redhat.com>
To: netdev@vger.kernel.org
Cc: "Michael S. Tsirkin" <mst@redhat.com>, kvm@vger.kernel.org,
        Greg Kroah-Hartman <gregkh@linuxfoundation.org>,
        Jason Wang <jasowang@redhat.com>,
        "David S. Miller" <davem@davemloft.net>,
        Dexuan Cui <decui@microsoft.com>,
        Haiyang Zhang <haiyangz@microsoft.com>,
        Jorgen Hansen <jhansen@vmware.com>,
        Sasha Levin <sashal@kernel.org>, linux-kernel@vger.kernel.org,
        Arnd Bergmann <arnd@arndb.de>,
        Stefan Hajnoczi <stefanha@redhat.com>,
        linux-hyperv@vger.kernel.org,
        "K. Y. Srinivasan" <kys@microsoft.com>,
        Stephen Hemminger <sthemmin@microsoft.com>,
        virtualization@lists.linux-foundation.org
Subject: [PATCH net-next 01/14] vsock/vmci: remove unused
 VSOCK_DEFAULT_CONNECT_TIMEOUT
Date: Wed, 23 Oct 2019 11:55:41 +0200
Message-Id: <20191023095554.11340-2-sgarzare@redhat.com>
In-Reply-To: <20191023095554.11340-1-sgarzare@redhat.com>
References: <20191023095554.11340-1-sgarzare@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
X-MC-Unique: FiyjSVSIOxmusT0AUBY3yw-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The VSOCK_DEFAULT_CONNECT_TIMEOUT definition was introduced with
commit d021c344051af ("VSOCK: Introduce VM Sockets"), but it is
never used in the net/vmw_vsock/vmci_transport.c.

VSOCK_DEFAULT_CONNECT_TIMEOUT is used and defined in
net/vmw_vsock/af_vsock.c

Cc: Jorgen Hansen <jhansen@vmware.com>
Reviewed-by: Stefan Hajnoczi <stefanha@redhat.com>
Signed-off-by: Stefano Garzarella <sgarzare@redhat.com>
---
 net/vmw_vsock/vmci_transport.c | 5 -----
 1 file changed, 5 deletions(-)

```
