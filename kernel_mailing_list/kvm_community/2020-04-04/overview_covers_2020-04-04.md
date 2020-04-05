

#### [PATCH kvm-unit-tests 0/2] A couple runtime fixes
##### From: Andrew Jones <drjones@redhat.com>

```c
From patchwork Sat Apr  4 15:47:37 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11474397
Return-Path: <SRS0=tmdL=5U=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6DD6792A
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat,  4 Apr 2020 15:47:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4A2CF206F8
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat,  4 Apr 2020 15:47:52 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="KJpkrIHq"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726258AbgDDPrv (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 4 Apr 2020 11:47:51 -0400
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:46795 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726039AbgDDPrv (ORCPT
        <rfc822;kvm@vger.kernel.org>); Sat, 4 Apr 2020 11:47:51 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1586015270;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=KqJABbeQAUt4oY7RO5Tn674jBtLn2R2l8D+XAXGuzvg=;
        b=KJpkrIHqKSVWVLvmZq3J20BaaXQSwzsdndgosNFkN+YFupBUFOGmBabG1LZcj7yokDIwl/
        auelCgwbSwnmtDX3iVzfYAtv+D+bFtbsqMAf8WtdULaZA2ys/D/d0t5wJzO00o8nppKEGo
        yEbCoVyx9Gw05dp7kaUAj6ev5nyZ2QQ=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-186-hBOKSepMPKO_4c8r6XX5uQ-1; Sat, 04 Apr 2020 11:47:48 -0400
X-MC-Unique: hBOKSepMPKO_4c8r6XX5uQ-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 8471918A6EC1;
        Sat,  4 Apr 2020 15:47:47 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.40.192.30])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 757975E000;
        Sat,  4 Apr 2020 15:47:42 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org
Cc: lvivier@redhat.com, thuth@redhat.com, david@redhat.com,
        frankja@linux.ibm.com, pbonzini@redhat.com
Subject: [PATCH kvm-unit-tests 0/2] A couple runtime fixes
Date: Sat,  4 Apr 2020 17:47:37 +0200
Message-Id: <20200404154739.217584-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

While testing the recent arm pull request I stumbled on to a couple
issues with the runtime scripts.

Andrew Jones (2):
  run_migration: Implement our own wait
  runtime: Always honor the unittests.cfg accel requirement

 scripts/arch-run.bash | 6 +++++-
 scripts/runtime.bash  | 9 ++++++++-
 2 files changed, 13 insertions(+), 2 deletions(-)
```
