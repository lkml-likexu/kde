#### [kvm-unit-tests PATCH] x86: realmode: Test interrupt delivery after STI
##### From: Roman Bolshakov <r.bolshakov@yadro.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Roman Bolshakov <r.bolshakov@yadro.com>
X-Patchwork-Id: 11463917
Return-Path: <SRS0=zb6b=5O=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 22DF913A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 29 Mar 2020 07:13:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id EE8CB206E6
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 29 Mar 2020 07:13:07 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=yadro.com header.i=@yadro.com
 header.b="U2FLUuXb"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727384AbgC2HLl (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 29 Mar 2020 03:11:41 -0400
Received: from mta-02.yadro.com ([89.207.88.252]:38724 "EHLO mta-01.yadro.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1727302AbgC2HLk (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 29 Mar 2020 03:11:40 -0400
Received: from localhost (unknown [127.0.0.1])
        by mta-01.yadro.com (Postfix) with ESMTP id C9FCC412CB;
        Sun, 29 Mar 2020 07:11:38 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=yadro.com; h=
        content-type:content-type:content-transfer-encoding:mime-version
        :x-mailer:message-id:date:date:subject:subject:from:from
        :received:received:received; s=mta-01; t=1585465897; x=
        1587280298; bh=2cSHbNB51jSlGHATfwhD/NrmlqCB0ieKHzp9nS9g3JE=; b=U
        2FLUuXbaNBZIBg18Jxi/hO1aZslgzvjGtfpZRF8sVGcWDl1O1cn8eltQxXm7gzNa
        PstaM+oWHMnGMKsXixp+nJdmQ8jmF+6iF7o4uDbOJOyvFqmw1csmN1hxV+y1YZ7/
        C0QwbsgUAJxJxYLrWN/8x+ImJ/pM1hD0y96md7zYWI=
X-Virus-Scanned: amavisd-new at yadro.com
Received: from mta-01.yadro.com ([127.0.0.1])
        by localhost (mta-01.yadro.com [127.0.0.1]) (amavisd-new, port 10024)
        with ESMTP id wGDyf2UlRISQ; Sun, 29 Mar 2020 10:11:37 +0300 (MSK)
Received: from T-EXCH-02.corp.yadro.com (t-exch-02.corp.yadro.com
 [172.17.10.102])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-SHA384 (256/256 bits))
        (No client certificate requested)
        by mta-01.yadro.com (Postfix) with ESMTPS id ACE854127D;
        Sun, 29 Mar 2020 10:11:37 +0300 (MSK)
Received: from localhost (172.17.204.212) by T-EXCH-02.corp.yadro.com
 (172.17.10.102) with Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA384_P384) id 15.1.669.32; Sun, 29
 Mar 2020 10:11:38 +0300
From: Roman Bolshakov <r.bolshakov@yadro.com>
To: <kvm@vger.kernel.org>
CC: Roman Bolshakov <r.bolshakov@yadro.com>,
        Cameron Esfahani <dirty@apple.com>
Subject: [kvm-unit-tests PATCH] x86: realmode: Test interrupt delivery after
 STI
Date: Sun, 29 Mar 2020 10:11:25 +0300
Message-ID: <20200329071125.79253-1-r.bolshakov@yadro.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
X-Originating-IP: [172.17.204.212]
X-ClientProxiedBy: T-EXCH-01.corp.yadro.com (172.17.10.101) To
 T-EXCH-02.corp.yadro.com (172.17.10.102)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If interrupts are disabled, STI is inhibiting interrupts for the
instruction following it. If STI is followed by HLT, the CPU is going to
handle all pending or new interrupts as soon as HLT is executed.

Test if emulator properly clears inhibition state and allows the
scenario outlined above.

Cc: Cameron Esfahani <dirty@apple.com>
Signed-off-by: Roman Bolshakov <r.bolshakov@yadro.com>
---
 x86/realmode.c | 21 +++++++++++++++++++++
 1 file changed, 21 insertions(+)

```
#### [PATCH 1/6] tools/virtio: Add --batch option
##### From: =?utf-8?q?Eugenio_P=C3=A9rez?= <eperezma@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Eugenio Perez Martin <eperezma@redhat.com>
X-Patchwork-Id: 11463985
Return-Path: <SRS0=zb6b=5O=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 59C9692C
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 29 Mar 2020 11:34:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 38978207FF
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 29 Mar 2020 11:34:22 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="PLtrQ8uz"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728120AbgC2LeU (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 29 Mar 2020 07:34:20 -0400
Received: from us-smtp-delivery-74.mimecast.com ([63.128.21.74]:45225 "EHLO
        us-smtp-delivery-74.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728113AbgC2LeT (ORCPT
        <rfc822;kvm@vger.kernel.org>); Sun, 29 Mar 2020 07:34:19 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1585481658;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=FFJYGGwUu9B8h+W1ItcNL0y6xF04SMRsuHG1jktXLH4=;
        b=PLtrQ8uziCAMWyeHZXbg7QetMFztB8/Sl/A6hFeoXqF6DOkpUgPh4OmsPYzrjAyfTwY+pE
        ok+0qaO+Sc5kUYOWrA5Ucc+MLJjtm3kqenqJYAGmc57TZX+32T/mv5UWllrrY0mWvUvEkZ
        0Z8tEs4JoVL6VOkRuws5/IgINCrkEeA=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-16-swojiZ69Pxe0wVSPYtiZMg-1; Sun, 29 Mar 2020 07:34:14 -0400
X-MC-Unique: swojiZ69Pxe0wVSPYtiZMg-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 1E0EA107ACC9;
        Sun, 29 Mar 2020 11:34:13 +0000 (UTC)
Received: from eperezma.remote.csb (ovpn-112-95.ams2.redhat.com
 [10.36.112.95])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 857725C1BE;
        Sun, 29 Mar 2020 11:34:10 +0000 (UTC)
From: =?utf-8?q?Eugenio_P=C3=A9rez?= <eperezma@redhat.com>
To: "Michael S. Tsirkin" <mst@redhat.com>
Cc: "virtualization@lists.linux-foundation.org"
  <virtualization@lists.linux-foundation.org>,
 Halil Pasic <pasic@linux.ibm.com>,
 =?utf-8?q?Eugenio_P=C3=A9rez?= <eperezma@redhat.com>,
 Stephen Rothwell <sfr@canb.auug.org.au>,
 Linux Next Mailing List <linux-next@vger.kernel.org>,
 kvm list <kvm@vger.kernel.org>, Cornelia Huck <cohuck@redhat.com>,
 Christian Borntraeger <borntraeger@de.ibm.com>,
 "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>
Subject: [PATCH 1/6] tools/virtio: Add --batch option
Date: Sun, 29 Mar 2020 13:33:54 +0200
Message-Id: <20200329113359.30960-2-eperezma@redhat.com>
In-Reply-To: <20200329113359.30960-1-eperezma@redhat.com>
References: <20200329113359.30960-1-eperezma@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This allow to test vhost having >1 buffers in flight

Signed-off-by: Eugenio Pérez <eperezma@redhat.com>
---
 tools/virtio/virtio_test.c | 47 ++++++++++++++++++++++++++++++--------
 1 file changed, 37 insertions(+), 10 deletions(-)

```
