#### [PATCH] kvm: selftests: aarch64: dirty_log_test: Remove unnecessary ifdefs
##### From: Andrew Jones <drjones@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11350193
Return-Path: <SRS0=8och=3N=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2B9D0139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Jan 2020 12:47:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 09F732077C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Jan 2020 12:47:09 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="hNHEMZ0+"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388812AbgAXMrI (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 24 Jan 2020 07:47:08 -0500
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:47721 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S2387709AbgAXMrH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 24 Jan 2020 07:47:07 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1579870026;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=ChLDmdrX0uO5zFp9WY4jkSOIQvobAH+yrFsmG1ZcUzY=;
        b=hNHEMZ0+PN70xguWEiqziOzBvyNrYjAxa29q0nwKgBWYTu5Gqd2haMN18bRhabjZvHb4OU
        dA7N23m01qaR27qz6+V6GhaFLITuz8PVpOGVye6qM63GvagW+jHseehghHssyR9cJSpguB
        95kTpl4SlG0xX3oAwNee2YmbjBkeDlQ=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-255-X_TKEVurOSKMwFWtWgpp3A-1; Fri, 24 Jan 2020 07:47:05 -0500
X-MC-Unique: X_TKEVurOSKMwFWtWgpp3A-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 173BA800D41
        for <kvm@vger.kernel.org>; Fri, 24 Jan 2020 12:47:04 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.43.2.160])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 40B6819C69;
        Fri, 24 Jan 2020 12:47:03 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com
Subject: [PATCH] kvm: selftests: aarch64: dirty_log_test: Remove unnecessary
 ifdefs
Date: Fri, 24 Jan 2020 13:47:01 +0100
Message-Id: <20200124124701.32688-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Signed-off-by: Andrew Jones <drjones@redhat.com>
---
 tools/testing/selftests/kvm/dirty_log_test.c | 21 +++++++++-----------
 1 file changed, 9 insertions(+), 12 deletions(-)

```
#### [PATCH 1/2] KVM: selftests: Rework debug message printing
##### From: Andrew Jones <drjones@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11350605
Return-Path: <SRS0=8och=3N=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E09EC109A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Jan 2020 15:37:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B58F9214AF
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Jan 2020 15:37:43 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="aNOKOW+f"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388610AbgAXPhm (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 24 Jan 2020 10:37:42 -0500
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:23868 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S2388032AbgAXPhm (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 24 Jan 2020 10:37:42 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1579880260;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=wPQZMPHMuLudlUICNOjLZWEM1dq74c0+KGBbOEg0s1U=;
        b=aNOKOW+fiLEV7KtVdbYndekfTyebDLEPNhvEmEBoClF3Ta2tZqIXNG1ISAaVX7T/7j34Ns
        nbuX39XcoZKicc4oIhOy3iv1rx9etXdyWG6svqdv9oKf63x1Ki3Gn+zE0A4IUv/s96wsoL
        mXJGJtp6dNmJzkgsqprvFg5TAwBdU44=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-197-T1Oa006gPtqgoHmnQ67Qdw-1; Fri, 24 Jan 2020 10:37:37 -0500
X-MC-Unique: T1Oa006gPtqgoHmnQ67Qdw-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 712F5151ED3
        for <kvm@vger.kernel.org>; Fri, 24 Jan 2020 15:37:30 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.43.2.160])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 958D41001B28;
        Fri, 24 Jan 2020 15:37:29 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com
Subject: [PATCH 1/2] KVM: selftests: Rework debug message printing
Date: Fri, 24 Jan 2020 16:37:25 +0100
Message-Id: <20200124153726.15455-2-drjones@redhat.com>
In-Reply-To: <20200124153726.15455-1-drjones@redhat.com>
References: <20200124153726.15455-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

There were a few problems with the way we output "debug" messages.
The first is that we used DEBUG() which is defined when NDEBUG is
not defined, but NDEBUG will never be defined for kselftests
because it relies too much on assert(). The next is that most
of the DEBUG() messages were actually "info" messages, which
users may want to turn off if they just want a silent test that
either completes or asserts. Finally, a debug message output from
a library function, and thus for all tests, was annoying when its
information wasn't interesting for a test.

Rework these messages so debug messages only output when DEBUG
is defined and info messages output unless QUIET is defined.
Also name the functions pr_debug and pr_info and make sure that
when they're disabled we eat all the inputs. The later avoids
unused variable warnings when the variables were only defined
for the purpose of printing.

Signed-off-by: Andrew Jones <drjones@redhat.com>
---
 tools/testing/selftests/kvm/dirty_log_test.c     | 16 +++++++++-------
 tools/testing/selftests/kvm/include/kvm_util.h   | 13 ++++++++++---
 .../selftests/kvm/lib/aarch64/processor.c        |  2 +-
 tools/testing/selftests/kvm/lib/kvm_util.c       |  7 ++++---
 4 files changed, 24 insertions(+), 14 deletions(-)

```
#### linux-next: manual merge of the kvm tree with Linus' tree
##### From: Stephen Rothwell <sfr@canb.auug.org.au>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stephen Rothwell <sfr@canb.auug.org.au>
X-Patchwork-Id: 11349571
Return-Path: <SRS0=8och=3N=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E351517EA
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Jan 2020 02:57:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id BD90321D7E
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Jan 2020 02:57:34 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=canb.auug.org.au header.i=@canb.auug.org.au
 header.b="cvtN5YcH"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730547AbgAXC5b (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 23 Jan 2020 21:57:31 -0500
Received: from ozlabs.org ([203.11.71.1]:46361 "EHLO ozlabs.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729841AbgAXC5b (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 23 Jan 2020 21:57:31 -0500
Received: from authenticated.ozlabs.org (localhost [127.0.0.1])
        (using TLSv1.3 with cipher TLS_AES_256_GCM_SHA384 (256/256 bits)
         key-exchange ECDHE (P-256) server-signature RSA-PSS (4096 bits)
 server-digest SHA256)
        (No client certificate requested)
        by mail.ozlabs.org (Postfix) with ESMTPSA id 483kMW2mW6z9sRK;
        Fri, 24 Jan 2020 13:57:27 +1100 (AEDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=canb.auug.org.au;
        s=201702; t=1579834648;
        bh=q8ffQqdirptsDf8OczDeNcXp3ch/G5iyXyRmUhpQ7xA=;
        h=Date:From:To:Cc:Subject:From;
        b=cvtN5YcHGJtpouxbY2undLOtEunTEaJ3Z9Jkztl/HmNzAQuRUJakQHM8Kc/NPU1Tf
         MPGh3HHHbrCFRQg9DfW/d1XY2xaogzv4EP/xFWIZX/snz7TDo9FpbibHMgEIZK+moK
         FSLCVu+F+82aSlStdqFuI8DpVyvxOB2/PZswHoqhMRPI+foiyuse6tT6ZkrSdqx3wY
         K7yyEN1AwoLZsaxGA17+p+C8no4XExo/qt4K/i2qJZcF01EQ0GJcxwUTKF41uS6oS9
         hkq0Gej50KzTS/sLjATFQI4gFIyETcWgK6I+pbhbzlfyKLG+uFocuaT639LfZCDKGt
         WI6bjTSyD0OGQ==
Date: Fri, 24 Jan 2020 13:57:26 +1100
From: Stephen Rothwell <sfr@canb.auug.org.au>
To: Paolo Bonzini <pbonzini@redhat.com>,
 Radim =?utf-8?b?S3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 KVM <kvm@vger.kernel.org>
Cc: Linux Next Mailing List <linux-next@vger.kernel.org>,
        Linux Kernel Mailing List <linux-kernel@vger.kernel.org>,
        "Kirill A. Shutemov" <kirill@shutemov.name>,
        Linus Torvalds <torvalds@linux-foundation.org>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Andrew Morton <akpm@linux-foundation.org>
Subject: linux-next: manual merge of the kvm tree with Linus' tree
Message-ID: <20200124135726.5fa8d146@canb.auug.org.au>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all,

Today's linux-next merge of the kvm tree got a conflict in:

  mm/huge_memory.c

between commit:

  97d3d0f9a1cf ("mm/huge_memory.c: thp: fix conflict of above-47bit hint address and PMD alignment")

from Linus' tree and commit:

  0638468d2282 ("mm: thp: KVM: Explicitly check for THP when populating secondary MMU")

from the kvm tree.

I fixed it up (see below) and can carry the fix as necessary. This
is now fixed as far as linux-next is concerned, but any non trivial
conflicts should be mentioned to your upstream maintainer when your tree
is submitted for merging.  You may also want to consider cooperating
with the maintainer of the conflicting tree to minimise any particularly
complex conflicts.

```
#### [PATCH] selftests: use $(MAKE) instead of "make"
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11349869
Return-Path: <SRS0=8och=3N=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 95FBC138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Jan 2020 08:51:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 6F9052087E
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Jan 2020 08:51:13 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="PLx6tZ7B"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729921AbgAXIvJ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 24 Jan 2020 03:51:09 -0500
Received: from mail-wm1-f68.google.com ([209.85.128.68]:33807 "EHLO
        mail-wm1-f68.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726173AbgAXIvJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 24 Jan 2020 03:51:09 -0500
Received: by mail-wm1-f68.google.com with SMTP id s144so3592721wme.1;
        Fri, 24 Jan 2020 00:51:07 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id;
        bh=kKTpSe2SaSEyXCdh9QLkR7mYGqSy34t2TTsozXj1tMk=;
        b=PLx6tZ7BRNarGA3y/pH+yOQV5kK1Owzj4nw505iXbHyr3X0mjfTyFH5Jfw/TOi/gNX
         dyIneGCvmIQks9TCpcP7VIwaYxL3d1qvKHkGPz/DiNZXbR6Aj7W6dTOHd3cp7ij53fHa
         m+uLZ7p6AYP9gsGA1gsFEkby+386mNHbW7KewXlCkhokcJDMNGlMwlWjNuE9275EzW2t
         l/L/2pHBVLQutILiIcCj4i7sCh2C+ctlst7FiWiXvip/knCTCRgdlhzqaGgQ/PBTONlN
         cH3ocibrMfKJGcyRyHlyWWXda8godZJpfB9zKNSfwAMIvXj/Zix/icgt2ZWpwUJ+dIdC
         CulQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id;
        bh=kKTpSe2SaSEyXCdh9QLkR7mYGqSy34t2TTsozXj1tMk=;
        b=rnHYfrvIZhWrq42a2Ed6pFG3Mg8+2hOlrj2OCF5lMUWS6mCXN8TwBoKr9YAbjKwTP7
         tT1fhDyTw+KaxmTFb+BBvcoDaffQv3reAU7Oy6LyecbVMwxnW+Rv5O4IJ/WwzcADevj2
         LvXKOSs2yCpAcizsYos2bLZWHY51BRcymHp3cPNZGZ2JUWsqWwPKMXAhCX+2HdQiTYhu
         SGXh3f+gHLqeYhy9E4xmDdsDWjQoG04d0FSgwNU7nohZx0hiMa3tjYPEYCTuXfx/kc/W
         J6KdYVvbD5SuuURoRKrI8c54c1TaTJfR7LrKfBwT4gR9ovzDOPkNLXHNWGLkGudQbHRv
         xaaQ==
X-Gm-Message-State: APjAAAU6OmFxQ35jNGbbTAUyWT0B2Df0Txhaa5MNxFpr86WqsnHjFt2h
        pC2wm7HshyU4612bfIXkZMhDsd13
X-Google-Smtp-Source: 
 APXvYqxZD/4yDV+ILxmbPxnChfFi60uvl3bEnm7jADz9aXBbfHBmAxOEoeXg246AukJzSe4m7QhDwQ==
X-Received: by 2002:a1c:7d93:: with SMTP id
 y141mr2226507wmc.111.1579855866591;
        Fri, 24 Jan 2020 00:51:06 -0800 (PST)
Received: from 640k.localdomain.com ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 s139sm5933048wme.35.2020.01.24.00.51.05
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Fri, 24 Jan 2020 00:51:05 -0800 (PST)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Shuah Khan <skhan@linuxfoundation.org>
Subject: [PATCH] selftests: use $(MAKE) instead of "make"
Date: Fri, 24 Jan 2020 09:51:03 +0100
Message-Id: <1579855863-56484-1-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This avoids a warning:

    make[1]: warning: jobserver unavailable: using -j1.  Add `+' to parent make rule.

Cc: Shuah Khan <skhan@linuxfoundation.org>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 tools/testing/selftests/lib.mk | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH v1 1/1] vfio-ccw: Don't free channel programs for unrelated interrupts
##### From: Eric Farman <farman@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Farman <farman@linux.ibm.com>
X-Patchwork-Id: 11350531
Return-Path: <SRS0=8och=3N=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1A87392A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Jan 2020 14:55:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id ECE6220704
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Jan 2020 14:55:05 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729631AbgAXOzF (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 24 Jan 2020 09:55:05 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:38426 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1729567AbgAXOzE (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 24 Jan 2020 09:55:04 -0500
Received: from pps.filterd (m0098396.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 00OEljIm053008
        for <kvm@vger.kernel.org>; Fri, 24 Jan 2020 09:55:03 -0500
Received: from e06smtp05.uk.ibm.com (e06smtp05.uk.ibm.com [195.75.94.101])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2xqmjtakx7-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Fri, 24 Jan 2020 09:55:03 -0500
Received: from localhost
        by e06smtp05.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <farman@linux.ibm.com>;
        Fri, 24 Jan 2020 14:55:01 -0000
Received: from b06cxnps4076.portsmouth.uk.ibm.com (9.149.109.198)
        by e06smtp05.uk.ibm.com (192.168.101.135) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Fri, 24 Jan 2020 14:54:59 -0000
Received: from d06av26.portsmouth.uk.ibm.com (d06av26.portsmouth.uk.ibm.com
 [9.149.105.62])
        by b06cxnps4076.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 00OEswqC53542930
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 24 Jan 2020 14:54:58 GMT
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id E6D30AE045;
        Fri, 24 Jan 2020 14:54:57 +0000 (GMT)
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id CE78DAE04D;
        Fri, 24 Jan 2020 14:54:57 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av26.portsmouth.uk.ibm.com (Postfix) with ESMTPS;
        Fri, 24 Jan 2020 14:54:57 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 4958)
        id 695D1E03C2; Fri, 24 Jan 2020 15:54:57 +0100 (CET)
From: Eric Farman <farman@linux.ibm.com>
To: Cornelia Huck <cohuck@redhat.com>,
        Halil Pasic <pasic@linux.ibm.com>
Cc: "Jason J . Herne" <jjherne@linux.ibm.com>,
        Jared Rossi <jrossi@linux.ibm.com>, linux-s390@vger.kernel.org,
        kvm@vger.kernel.org, Eric Farman <farman@linux.ibm.com>
Subject: [PATCH v1 1/1] vfio-ccw: Don't free channel programs for unrelated
 interrupts
Date: Fri, 24 Jan 2020 15:54:55 +0100
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200124145455.51181-1-farman@linux.ibm.com>
References: <20200124145455.51181-1-farman@linux.ibm.com>
X-TM-AS-GCONF: 00
x-cbid: 20012414-0020-0000-0000-000003A3A48A
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 20012414-0021-0000-0000-000021FB4289
Message-Id: <20200124145455.51181-2-farman@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-01-24_04:2020-01-24,2020-01-24 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 suspectscore=2
 impostorscore=0 clxscore=1011 adultscore=0 mlxlogscore=875
 priorityscore=1501 spamscore=0 bulkscore=0 lowpriorityscore=0
 malwarescore=0 mlxscore=0 phishscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-1910280000 definitions=main-2001240124
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

With the addition of asynchronous channel programs (HALT or CLEAR
SUBCHANNEL instructions), the hardware can receive interrupts that
are not related to any channel program currently active.  An attempt
is made to ensure that only associated resources are freed, but the
host can fail in unpleasant ways:

[ 1051.330289] Unable to handle kernel pointer dereference in virtual kernel address space
[ 1051.330360] Failing address: c880003d16572000 TEID: c880003d16572803
[ 1051.330365] Fault in home space mode while using kernel ASCE.
[ 1051.330372] AS:00000000fde9c007 R3:0000000000000024
...snip...
[ 1051.330539]  [<00000000fccbd33e>] __kmalloc+0xd6/0x3d8
[ 1051.330543] ([<00000000fccbd514>] __kmalloc+0x2ac/0x3d8)
[ 1051.330550]  [<000003ff801452b4>] cp_prefetch+0xc4/0x3b8 [vfio_ccw]
[ 1051.330554]  [<000003ff801471e4>] fsm_io_request+0x2d4/0x7b8 [vfio_ccw]
[ 1051.330559]  [<000003ff80145d9c>] vfio_ccw_mdev_write+0x17c/0x300 [vfio_ccw]
[ 1051.330564]  [<00000000fccf0d20>] vfs_write+0xb0/0x1b8
[ 1051.330568]  [<00000000fccf1236>] ksys_pwrite64+0x7e/0xb8
[ 1051.330574]  [<00000000fd4524c0>] system_call+0xdc/0x2d8

The problem is corruption of the dma-kmalloc-8 slab [1], if an interrupt
occurs for a CLEAR or HALT that is not obviously associated with the
current channel program.  If the channel_program struct is freed AND
another interrupt for that I/O occurs, then this may occur:

583.612967 00          cp_prefetch  NEW SSCH
583.613180 03 vfio_ccw_sch_io_todo  orb.cpa=03012690 irb.cpa=03012698
                                    ccw=2704004203015600 *cda=1955d8fb8
                                    irb: fctl=4 actl=0 stctl=7
587.039292 04          cp_prefetch  NEW SSCH
587.039296 01 vfio_ccw_sch_io_todo  orb.cpa=7fe209f0 irb.cpa=03012698
                                    ccw=3424000c030a4068 *cda=1999e9cf0
                                    irb: fctl=2 actl=0 stctl=1
587.039505 01 vfio_ccw_sch_io_todo  orb.cpa=7fe209f0 irb.cpa=7fe209f8
                                    ccw=3424000c030a4068 *cda=0030a4070
                                    irb: fctl=4 actl=0 stctl=7

Note how the last vfio_ccw_sch_io_todo() call has a ccw.cda that is
right next to its supposed IDAW, compared to the previous one?  That
is the result of the previous one freeing the cp (and its IDAL), and
kfree writing the next available address at the beginning of the
newly released memory.  When the channel goes to store data, it
believes the IDAW is valid and overwrites that pointer and causes
kmalloc to fail some time later.

Since the vfio-ccw interrupt handler walks the list of ccwchain structs
to determine if the guest SCSW needs to be updated, it can be changed
to indicate whether the interrupt points within the channel_program.
If yes, then the channel_program is valid and its resources can be freed.
It not, then another interrupt is expected to do that later.

[1] It could be other dma-kmalloc-xxx slabs; this just happens to be the
one driven most frequently in my testing.

Fixes: f4c9939433bd ("vfio-ccw: Don't call cp_free if we are processing a channel program")
Signed-off-by: Eric Farman <farman@linux.ibm.com>
---
 drivers/s390/cio/vfio_ccw_cp.c  | 11 +++++++++--
 drivers/s390/cio/vfio_ccw_cp.h  |  2 +-
 drivers/s390/cio/vfio_ccw_drv.c |  4 ++--
 3 files changed, 12 insertions(+), 5 deletions(-)

```
