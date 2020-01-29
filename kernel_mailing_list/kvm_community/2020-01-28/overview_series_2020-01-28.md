#### [kvm-unit-tests PATCH v3 01/14] libcflat: Add other size defines
##### From: Eric Auger <eric.auger@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Auger Eric <eric.auger@redhat.com>
X-Patchwork-Id: 11354001
Return-Path: <SRS0=gQxY=3R=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2EAA692A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Jan 2020 10:35:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 041CF2468D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Jan 2020 10:35:25 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="bbPilG3n"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726010AbgA1KfY (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 28 Jan 2020 05:35:24 -0500
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:49062 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1725948AbgA1KfX (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 28 Jan 2020 05:35:23 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1580207722;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=g1Y7SAIkQ6YKL70iv+PevVOHVnPkk+5bW/+E3fVVoME=;
        b=bbPilG3naIr1ePcnMiUJ3aQKVM3AHb3amhlnB97UkX8XdnBPhT78yu0Mo/oQJY8n85x4Gu
        e6IL6Y0DX0+liZVzX5nsmgZ7wWvcCsbPK3zN2b9rBAa6V7759hBVInJhYge5pK3eH3qwxW
        bFTAacgfLNdbRAZIbKrb8FcAkxxhx8A=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-226-60MnbJ6RNh6DWtQjzWJD4g-1; Tue, 28 Jan 2020 05:35:17 -0500
X-MC-Unique: 60MnbJ6RNh6DWtQjzWJD4g-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 47B7B1005510;
        Tue, 28 Jan 2020 10:35:16 +0000 (UTC)
Received: from laptop.redhat.com (ovpn-116-37.ams2.redhat.com [10.36.116.37])
        by smtp.corp.redhat.com (Postfix) with ESMTP id E70F91001B30;
        Tue, 28 Jan 2020 10:35:10 +0000 (UTC)
From: Eric Auger <eric.auger@redhat.com>
To: eric.auger.pro@gmail.com, eric.auger@redhat.com, maz@kernel.org,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        qemu-devel@nongnu.org, qemu-arm@nongnu.org
Cc: drjones@redhat.com, andre.przywara@arm.com,
        peter.maydell@linaro.org, yuzenghui@huawei.com,
        alexandru.elisei@arm.com, thuth@redhat.com
Subject: [kvm-unit-tests PATCH v3 01/14] libcflat: Add other size defines
Date: Tue, 28 Jan 2020 11:34:46 +0100
Message-Id: <20200128103459.19413-2-eric.auger@redhat.com>
In-Reply-To: <20200128103459.19413-1-eric.auger@redhat.com>
References: <20200128103459.19413-1-eric.auger@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
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
#### [PATCH 01/27] docs: kvm: add arm/pvtime.rst to index.rst
##### From: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
X-Patchwork-Id: 11354485
Return-Path: <SRS0=gQxY=3R=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 090831398
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Jan 2020 14:49:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id DCB3F2173E
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Jan 2020 14:49:55 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1580222995;
	bh=RQJBSrCBQoRjRPzNpPiEOUwoi4zmhWHM5Ddo22O4ojU=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=Mquz/Fw3g1S759F+YqDzrvScss7Pq3oDEuyWD+xCTa11pcc+q2FU1c1K19rlrCr7c
	 oRLq6OZOJK67ppXoISyHM9VDsmUA3SzuczTbngJ1Pwjf2+o1JNvPVNda22e57dYdy0
	 5qCqoT3GtY+vfksXMjGpLwuBwGTUcmSCX7ZGTCAM=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727423AbgA1Oty (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 28 Jan 2020 09:49:54 -0500
Received: from bombadil.infradead.org ([198.137.202.133]:59266 "EHLO
        bombadil.infradead.org" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726401AbgA1OAq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 28 Jan 2020 09:00:46 -0500
DKIM-Signature: v=1; a=rsa-sha256; q=dns/txt; c=relaxed/relaxed;
        d=infradead.org; s=bombadil.20170209;
 h=Sender:Content-Transfer-Encoding:
        MIME-Version:References:In-Reply-To:Message-Id:Date:Subject:Cc:To:From:
        Reply-To:Content-Type:Content-ID:Content-Description:Resent-Date:Resent-From:
        Resent-Sender:Resent-To:Resent-Cc:Resent-Message-ID:List-Id:List-Help:
        List-Unsubscribe:List-Subscribe:List-Post:List-Owner:List-Archive;
        bh=/hfBTm+pwI/qMUzI6610HUXH01FV0FRb49kTIzGz0Ww=;
 b=E/bWrY8g75zMz0ST+qe+W7HFkj
        wDMeKMTZMTAyuysD4oyzDqiPBfq5PJjaqrBHRbO3DRwETGjT76NiTJ+IDOMcElzDWhEGVr0YMtfgb
        Clq9k7LePmOncq0P8ZEpqRb4REj15uCz1EE3YO/SQx7Te3aX6CBCynK+ysJpcYHSeApyw70qoM2FZ
        CygR3aUEr9lg6MIKD0scM8wD3QBwwk1XO81cIcUdFdBrMDw8SKV1R3NrFnsnmCuKVVR1x3S50fLpY
        ev1Ps5YqW1PODTcpYMtybxkqWu9DCRG1cTwVDZKrG4uz8OS7M4zwQegY/h4bWibcDsKxbLZ6dt7Ny
        MU2bgp0A==;
Received: from [177.41.103.99] (helo=bombadil.infradead.org)
        by bombadil.infradead.org with esmtpsa (Exim 4.92.3 #3 (Red Hat
 Linux))
        id 1iwRQ5-0007iZ-9c; Tue, 28 Jan 2020 14:00:45 +0000
Received: from mchehab by bombadil.infradead.org with local (Exim 4.92.3)
        (envelope-from <mchehab@bombadil.infradead.org>)
        id 1iwRPp-001BNG-6Z; Tue, 28 Jan 2020 15:00:29 +0100
From: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
To: Linux Media Mailing List <linux-media@vger.kernel.org>
Cc: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>,
        Mauro Carvalho Chehab <mchehab@infradead.org>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Jonathan Corbet <corbet@lwn.net>, kvm@vger.kernel.org,
        linux-doc@vger.kernel.org
Subject: [PATCH 01/27] docs: kvm: add arm/pvtime.rst to index.rst
Date: Tue, 28 Jan 2020 15:00:02 +0100
Message-Id: 
 <8efe846ddd76d97a62a150a997619e5d7d992774.1580219586.git.mchehab+huawei@kernel.org>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <cover.1580219586.git.mchehab+huawei@kernel.org>
References: <cover.1580219586.git.mchehab+huawei@kernel.org>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add this file to a new kvm/arm index.rst, in order for it to
be shown as part of the virt book.

Signed-off-by: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
---
 Documentation/virt/kvm/arm/index.rst | 10 ++++++++++
 Documentation/virt/kvm/index.rst     |  2 ++
 2 files changed, 12 insertions(+)
 create mode 100644 Documentation/virt/kvm/arm/index.rst

diff --git a/Documentation/virt/kvm/arm/index.rst b/Documentation/virt/kvm/arm/index.rst
new file mode 100644
index 000000000000..e039d9b1e076
--- /dev/null
+++ b/Documentation/virt/kvm/arm/index.rst
@@ -0,0 +1,10 @@
+.. SPDX-License-Identifier: GPL-2.0
+
+===
+ARM
+===
+
+.. toctree::
+   :maxdepth: 2
+
+   pvtime
```
#### [PATCH v2 1/5] KVM: x86: Mask off reserved bit from #DB exception payload
##### From: Oliver Upton <oupton@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Oliver Upton <oupton@google.com>
X-Patchwork-Id: 11353861
Return-Path: <SRS0=gQxY=3R=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D4D55138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Jan 2020 09:27:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B2EB324688
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Jan 2020 09:27:31 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="k4wersvP"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725953AbgA1J1b (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 28 Jan 2020 04:27:31 -0500
Received: from mail-pj1-f73.google.com ([209.85.216.73]:44855 "EHLO
        mail-pj1-f73.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725922AbgA1J1a (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 28 Jan 2020 04:27:30 -0500
Received: by mail-pj1-f73.google.com with SMTP id c31so1128595pje.9
        for <kvm@vger.kernel.org>; Tue, 28 Jan 2020 01:27:30 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=nioYHgWtzuJX0bGGHSnAcIx7clPoYS+RyTzHFfHLiC0=;
        b=k4wersvPQpScFKgypDDZhrTlz2Tiv91+qRRQMaNpNlAHjISZCuXpObMYK6G8w4xJ9U
         77ZWAhVxTCXsoMsx6kkhPFBAQNLE5EyJcHJpTw8KlHyoSwZK9lNsLFOkpM0GgNuWlilC
         DJbXzCjv+/ux8RyJP+p3CcVQXGcLwx6A7OFKG/du4GJehbgZkYahCD7vIiF/esJOO7s9
         IbxIjkmqmuETjqHytNnsoxUHAqxYBiXrn/8mq//XMeqzl96BiWT5Ns8d7M150bNCzuOj
         D8kVvv+azEBzZNX+xAnvTPGPCbB0p2qRp5sqrgFh+FyYCCNtzE4Eh9EvigzEk07zRWLV
         +Fag==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=nioYHgWtzuJX0bGGHSnAcIx7clPoYS+RyTzHFfHLiC0=;
        b=qanlwMKinkAOKSphOQKrZ9QOnrx272CeIhnEFDSNH/cCx6wHqG5DvyyJYVAC8ppnVo
         sN28GrKOdRow6tRyospkjgPEqL0dUfpi+Y9NQYFfJ7kyyIBDmANIOTcXnpE8p7eAqMXA
         mFdCet8IyKEdeUyKO/jTssaCzvNBKImYUNZv6aHhC2Ps/NwaLyLcfIDGStAabKhJSPqP
         i7wLmfM/A1ifqKGmtdkgPILlAMXOspLNPOvQ1g5GPdFYmMordLFjkN4YzAXjelMdwSJY
         GG5ymOf7a8CXAz/HsnENzodO+QX89PQ0yKEc07qO9+A2VgnPuYvs8oPo3IrrqAl0Zjpf
         LScw==
X-Gm-Message-State: APjAAAW/fRhooOip+I3lgZFtf+tfIkxBThYl1r6pQVodLSK7wCw5dUmj
        SLDyRiFflUQJEMc8YciHZOdpq8uJ+j8yxWQP7qjrtYcO7QyMSxxokk/Dyl8a+shtqySWiF4vWyW
        NWTrtB04AA15FrzXUVixlR4WOMJO1HvUQcpyt+ygBf4y435pNFQ3T/z1SSA==
X-Google-Smtp-Source: 
 APXvYqy0cehjxUbWNumChAd1siL4XK+9M6zowjeV4zuou3ingY61ee2Z+Hjbqozv2qBQZ4wdtqm9RR46lmc=
X-Received: by 2002:a63:78b:: with SMTP id 133mr23439750pgh.379.1580203649548;
 Tue, 28 Jan 2020 01:27:29 -0800 (PST)
Date: Tue, 28 Jan 2020 01:27:11 -0800
In-Reply-To: <20200128092715.69429-1-oupton@google.com>
Message-Id: <20200128092715.69429-2-oupton@google.com>
Mime-Version: 1.0
References: <20200128092715.69429-1-oupton@google.com>
X-Mailer: git-send-email 2.25.0.341.g760bfbb309-goog
Subject: [PATCH v2 1/5] KVM: x86: Mask off reserved bit from #DB exception
 payload
From: Oliver Upton <oupton@google.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Peter Shier <pshier@google.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Oliver Upton <oupton@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

KVM defines the #DB payload as compatible with the 'pending debug
exceptions' field under VMX, not DR6. Mask off bit 12 when applying the
payload to DR6, as it is reserved on DR6 but not the 'pending debug
exceptions' field.

Fixes: f10c729ff965 ("kvm: vmx: Defer setting of DR6 until #DB delivery")
Signed-off-by: Oliver Upton <oupton@google.com>
---
 arch/x86/kvm/x86.c | 8 ++++++++
 1 file changed, 8 insertions(+)

```
#### [PATCH v2] kvm: selftests: Introduce num-pages conversion utilities
##### From: Andrew Jones <drjones@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11353873
Return-Path: <SRS0=gQxY=3R=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F2922112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Jan 2020 09:34:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id CFE2F24681
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Jan 2020 09:34:51 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="STdYTK24"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725903AbgA1Jev (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 28 Jan 2020 04:34:51 -0500
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:39274 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1725853AbgA1Jev (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 28 Jan 2020 04:34:51 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1580204089;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=p1cuTqBpAu7dAS53tDA9Lq4+9PX3cIAy2MQULa5xpEQ=;
        b=STdYTK24uz6gMt5puqlaK0Lem8Y1ERAQl40Sg38kSwIKNqUh4+CMIAAb1i57AQhRtxPZUu
        QHmbDKWCgLYy5+HzNbFF4YA72Z1Xx66eXuS5Tm8YCj9t3A2xxI0Xlu7dWq6J+1dZe7n+WH
        GC3wIkhdFb+42CrhWVQjM8+6RQhfxqY=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-216-EWIXQv4wOgynUEChqEiFrg-1; Tue, 28 Jan 2020 04:34:47 -0500
X-MC-Unique: EWIXQv4wOgynUEChqEiFrg-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 6051E800EBB;
        Tue, 28 Jan 2020 09:34:46 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.43.2.160])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 302F788821;
        Tue, 28 Jan 2020 09:34:45 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, thuth@redhat.com, bgardon@google.com
Subject: [PATCH v2] kvm: selftests: Introduce num-pages conversion utilities
Date: Tue, 28 Jan 2020 10:34:43 +0100
Message-Id: <20200128093443.25414-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Guests and hosts don't have to have the same page size. This means
calculations are necessary when selecting the number of guest pages
to allocate in order to ensure the number is compatible with the
host. Provide utilities to help with those calculations.

Signed-off-by: Andrew Jones <drjones@redhat.com>
Reviewed-by: Ben Gardon <bgardon@google.com>
---
 tools/testing/selftests/kvm/dirty_log_test.c  | 10 ++++----
 .../testing/selftests/kvm/include/kvm_util.h  |  3 +++
 .../testing/selftests/kvm/include/test_util.h |  2 ++
 tools/testing/selftests/kvm/lib/kvm_util.c    | 24 +++++++++++++++++++
 4 files changed, 33 insertions(+), 6 deletions(-)

```
