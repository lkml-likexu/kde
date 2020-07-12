#### [PATCH 1/5] KVM: arm64: pvtime: steal-time is only supported when configured
##### From: Andrew Jones <drjones@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11657827
Return-Path: <SRS0=yQtk=AW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A4CE513B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 11 Jul 2020 10:04:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8C95F207D4
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 11 Jul 2020 10:04:48 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="jDc2COYM"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726480AbgGKKEq (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 11 Jul 2020 06:04:46 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:50489 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726208AbgGKKEp (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 11 Jul 2020 06:04:45 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1594461884;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=W+UmIX9bjp1SsTNPgtJx0GFQxPx7B6KTaPKfrg10fpU=;
        b=jDc2COYMRS+PqXB5tQFln31AOne/CgSW1KBxDFzbbDvmtbAv8FiENo2lKO1g1nlgZGb5Fy
        ci8eXt2wHuGhdbgjZ0KspDooArHCSDjFzB5Wt76MV5hXnkQ46j9XZilXcXE70Y/Y4bopw9
        m1ngueaXejzOtj1NVEAtjNO4miMaCKc=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-287-LzASmirmOQ2Eg7629F0cTw-1; Sat, 11 Jul 2020 06:04:40 -0400
X-MC-Unique: LzASmirmOQ2Eg7629F0cTw-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 980F780183C;
        Sat, 11 Jul 2020 10:04:39 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.40.192.42])
        by smtp.corp.redhat.com (Postfix) with ESMTP id EA87619D61;
        Sat, 11 Jul 2020 10:04:37 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu
Cc: pbonzini@redhat.com, maz@kernel.org, steven.price@arm.com
Subject: [PATCH 1/5] KVM: arm64: pvtime: steal-time is only supported when
 configured
Date: Sat, 11 Jul 2020 12:04:30 +0200
Message-Id: <20200711100434.46660-2-drjones@redhat.com>
In-Reply-To: <20200711100434.46660-1-drjones@redhat.com>
References: <20200711100434.46660-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Don't confuse the guest by saying steal-time is supported when
it hasn't been configured by userspace and won't work.

Signed-off-by: Andrew Jones <drjones@redhat.com>
---
 arch/arm64/kvm/pvtime.c | 5 ++++-
 1 file changed, 4 insertions(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH] x86: reverse FW_CFG_MAX_ENTRY and FW_CFG_MAX_RAM
##### From: Nadav Amit <namit@vmware.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Nadav Amit <namit@vmware.com>
X-Patchwork-Id: 11657919
Return-Path: <SRS0=yQtk=AW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6ABC492A
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 11 Jul 2020 16:16:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 56085207DD
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 11 Jul 2020 16:16:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728623AbgGKQQ7 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 11 Jul 2020 12:16:59 -0400
Received: from ex13-edg-ou-002.vmware.com ([208.91.0.190]:15133 "EHLO
        EX13-EDG-OU-002.vmware.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728441AbgGKQQ6 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Sat, 11 Jul 2020 12:16:58 -0400
Received: from sc9-mailhost3.vmware.com (10.113.161.73) by
 EX13-EDG-OU-002.vmware.com (10.113.208.156) with Microsoft SMTP Server id
 15.0.1156.6; Sat, 11 Jul 2020 09:16:52 -0700
Received: from sc2-haas01-esx0118.eng.vmware.com
 (sc2-haas01-esx0118.eng.vmware.com [10.172.44.118])
        by sc9-mailhost3.vmware.com (Postfix) with ESMTP id 7D63D4060D;
        Sat, 11 Jul 2020 09:16:58 -0700 (PDT)
From: Nadav Amit <namit@vmware.com>
To: Paolo Bonzini <pbonzini@redhat.com>
CC: <kvm@vger.kernel.org>, Nadav Amit <namit@vmware.com>
Subject: [kvm-unit-tests PATCH] x86: reverse FW_CFG_MAX_ENTRY and
 FW_CFG_MAX_RAM
Date: Sat, 11 Jul 2020 09:14:32 -0700
Message-ID: <20200711161432.32862-1-namit@vmware.com>
X-Mailer: git-send-email 2.17.1
MIME-Version: 1.0
Received-SPF: None (EX13-EDG-OU-002.vmware.com: namit@vmware.com does not
 designate permitted sender hosts)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

FW_CFG_MAX_ENTRY should obviously be the last entry.

Signed-off-by: Nadav Amit <namit@vmware.com>
---
 lib/x86/fwcfg.h | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
