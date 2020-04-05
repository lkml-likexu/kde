#### [PATCH kvm-unit-tests 1/2] run_migration: Implement our own wait
##### From: Andrew Jones <drjones@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11474399
Return-Path: <SRS0=tmdL=5U=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9969892A
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat,  4 Apr 2020 15:47:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 6ECBD206F8
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat,  4 Apr 2020 15:47:55 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="TfsVg8Db"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726402AbgDDPry (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 4 Apr 2020 11:47:54 -0400
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:52446 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726269AbgDDPry (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 4 Apr 2020 11:47:54 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1586015273;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=/vnt8+N5RBipBuCDN1bwVcH7MsY/pHwnnja9bLS5Y4k=;
        b=TfsVg8Dbd8FUFV+aKcQj1zwgY7z00dEtMtFmWpVsZhroRWpAHDP/MpGiBfWLkI5dWGE/Um
        ic9DVWZl2oL2ImRUjFeeO4PdCvivvKU6hVxKdiAf4QWQuVv9zmGrcvDLOkg7ks83JDl4Z0
        3Tlt6Db88pjs7hhKIYa9k+ZOwOLT2q4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-16-_aa2KBvUMeSLHSaD9ltaWw-1; Sat, 04 Apr 2020 11:47:51 -0400
X-MC-Unique: _aa2KBvUMeSLHSaD9ltaWw-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 64C99DB60;
        Sat,  4 Apr 2020 15:47:50 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.40.192.30])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 038A85E000;
        Sat,  4 Apr 2020 15:47:47 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org
Cc: lvivier@redhat.com, thuth@redhat.com, david@redhat.com,
        frankja@linux.ibm.com, pbonzini@redhat.com
Subject: [PATCH kvm-unit-tests 1/2] run_migration: Implement our own wait
Date: Sat,  4 Apr 2020 17:47:38 +0200
Message-Id: <20200404154739.217584-2-drjones@redhat.com>
In-Reply-To: <20200404154739.217584-1-drjones@redhat.com>
References: <20200404154739.217584-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Bash 5.0 changed 'wait' with no arguments to also wait for all
process substitutions. For example, with Bash 4.4 this completes,
after waiting for the sleep

  (
    sleep 1 &
    wait
  ) > >(tee /dev/null)

but with Bash 5.0 it does not. The kvm-unit-tests (overly) complex
bash scripts have a 'run_migration ... 2> >(tee /dev/stderr)'
where the '2> >(tee /dev/stderr)' comes from 'run_qemu'. Since
'run_migration' calls 'wait' it will never complete with Bash 5.0.
Resolve by implementing our own wait; just a loop on job count.

Signed-off-by: Andrew Jones <drjones@redhat.com>
---
 scripts/arch-run.bash | 6 +++++-
 1 file changed, 5 insertions(+), 1 deletion(-)

```
#### [PATCH kvm-unit-tests] arch-run: Add reserved variables to the default environ
##### From: Andrew Jones <drjones@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11474419
Return-Path: <SRS0=tmdL=5U=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C3B5A17EA
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat,  4 Apr 2020 17:22:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 8E0DD206E6
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat,  4 Apr 2020 17:22:54 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="MqtTXC2e"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726246AbgDDRWx (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 4 Apr 2020 13:22:53 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:48741 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726066AbgDDRWx (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 4 Apr 2020 13:22:53 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1586020971;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=ZCCdVWSfV0c6U3cyZbiv8Vt2n/y32og0HL8bxYgBpkY=;
        b=MqtTXC2e0IhvKiE5ISmSW1z+jukHYxSnWZt4EH8v87YTQem3DzwIa4jBBHrD6c2vgnJkMJ
        2/H9m0tBjGQ+jZzs3JuVO8jxb4vIYSuTHK9REfAa8LTP5XHeqFtfRu6sjEdqz+VrfdV1kQ
        3iU44qrv3uK/JkTMXaKI4+dLWBK2HII=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-491-eVdGsW3UN4SwIXCJ2GcnTg-1; Sat, 04 Apr 2020 13:22:44 -0400
X-MC-Unique: eVdGsW3UN4SwIXCJ2GcnTg-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 2BB2A8017CE;
        Sat,  4 Apr 2020 17:22:43 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.40.192.30])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 1FE6BB19A6;
        Sat,  4 Apr 2020 17:22:37 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org
Cc: lvivier@redhat.com, thuth@redhat.com, david@redhat.com,
        frankja@linux.ibm.com, pbonzini@redhat.com
Subject: [PATCH kvm-unit-tests] arch-run: Add reserved variables to the
 default environ
Date: Sat,  4 Apr 2020 19:22:35 +0200
Message-Id: <20200404172235.238065-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add the already reserved (see README) variables to the default
environ. To do so neatly we rework the environ creation a bit too.
mkstandalone also learns to honor config.mak as to whether or not
to make environs, and we allow the $ERRATATXT file to be selected
at configure time.

Signed-off-by: Andrew Jones <drjones@redhat.com>
---
 configure               |  12 +++-
 scripts/arch-run.bash   | 120 ++++++++++++++++++++++++----------------
 scripts/mkstandalone.sh |   4 +-
 3 files changed, 86 insertions(+), 50 deletions(-)

```
#### [PULL kvm-unit-tests 01/39] Makefile: Use no-stack-protector compiler options
##### From: Andrew Jones <drjones@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11474321
Return-Path: <SRS0=tmdL=5U=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0147615AB
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat,  4 Apr 2020 14:38:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D490E20731
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat,  4 Apr 2020 14:38:11 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="axxVR5v+"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726353AbgDDOh5 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 4 Apr 2020 10:37:57 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:34679 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726248AbgDDOh4 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 4 Apr 2020 10:37:56 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1586011076;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=4TH7o6uPii+FVWXIRQDwrHwi8uTL0Zd9SNThpzh1Yhs=;
        b=axxVR5v+RL5nxtCS+ru3FnMTEtQpustGR9fQVFKCglWZqyLQQJTcaxAsqgwqjA4fsWgBB2
        y+9J6UxaJ24KDMMa7BlZQqptjJsr3Y6xPG/OAUMhxhehpEp2e8bUaw66eXWC8+dccjoVdW
        NmLSD/l6TAgWVeA5/xopP4Qyk/CTXyY=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-321-jqwY0IBlPfCljN1pw65vkw-1; Sat, 04 Apr 2020 10:37:53 -0400
X-MC-Unique: jqwY0IBlPfCljN1pw65vkw-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 7CD5B107B113;
        Sat,  4 Apr 2020 14:37:41 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.40.192.30])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 42CBA9B912;
        Sat,  4 Apr 2020 14:37:35 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: pbonzini@redhat.com
Cc: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
        Alexandru Elisei <alexandru.elisei@arm.com>,
        Drew Jones <drjones@redhat.com>,
        Laurent Vivier <lvivier@redhat.com>,
        Thomas Huth <thuth@redhat.com>,
        David Hildenbrand <david@redhat.com>,
        Janosch Frank <frankja@linux.ibm.com>
Subject: [PULL kvm-unit-tests 01/39] Makefile: Use no-stack-protector compiler
 options
Date: Sat,  4 Apr 2020 16:36:53 +0200
Message-Id: <20200404143731.208138-2-drjones@redhat.com>
In-Reply-To: <20200404143731.208138-1-drjones@redhat.com>
References: <20200404143731.208138-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Alexandru Elisei <alexandru.elisei@arm.com>

Let's fix the typos so that the -fno-stack-protector and
-fno-stack-protector-all compiler options are actually used.

Tested by compiling for arm64, x86_64 and ppc64 little endian. Before the
patch, the arguments were missing from the gcc invocation; after the patch,
they were present. Also fixes a compilation error that I was seeing with
aarch64 gcc version 9.2.0, where the linker was complaining about an
undefined reference to the symbol __stack_chk_guard.

Fixes: e5c73790f5f0 ("build: don't reevaluate cc-option shell command")
CC: Paolo Bonzini <pbonzini@redhat.com>
CC: Drew Jones <drjones@redhat.com>
CC: Laurent Vivier <lvivier@redhat.com>
CC: Thomas Huth <thuth@redhat.com>
CC: David Hildenbrand <david@redhat.com>
CC: Janosch Frank <frankja@linux.ibm.com>
Signed-off-by: Alexandru Elisei <alexandru.elisei@arm.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
Reviewed-by: Laurent Vivier <lvivier@redhat.com>
Signed-off-by: Andrew Jones <drjones@redhat.com>
---
 Makefile | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
