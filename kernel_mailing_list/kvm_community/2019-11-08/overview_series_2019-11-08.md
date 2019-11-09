#### [PATCH v4 1/4] kvm: nested: Introduce read_and_check_msr_entry()From: Aaron Lewis <aaronlewis@google.com>
##### From: Aaron Lewis <aaronlewis@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Aaron Lewis <aaronlewis@google.com>
X-Patchwork-Id: 11234093
Return-Path: <SRS0=CHcm=ZA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0A3C1139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  8 Nov 2019 05:14:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id DC82821848
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  8 Nov 2019 05:14:49 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="WAogCnEi"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726618AbfKHFOs (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 8 Nov 2019 00:14:48 -0500
Received: from mail-pg1-f201.google.com ([209.85.215.201]:36665 "EHLO
        mail-pg1-f201.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726103AbfKHFOs (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 8 Nov 2019 00:14:48 -0500
Received: by mail-pg1-f201.google.com with SMTP id h12so3850241pgd.3
        for <kvm@vger.kernel.org>; Thu, 07 Nov 2019 21:14:48 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=XTXOT3PTQaYYqLr+YkwfmLP4vZijQPTV+yL5uM5usc8=;
        b=WAogCnEiNAjEpBBxEA04jsBppJNAzct4MnqswJ4df8s0CHWbVXwLLGkOzH9/XnK78l
         Ztq6FgnCus8aHki7P7WecVfTPt5EYarJ+OQAiWFpAEHZeA6vqBhKIihvLIuriWEKuEaM
         kHQmxUipNGVqi7QpO9OLUeRLrB4S36kGvGRG41JTdBn+Kfno6y0QIcDR+/Gf+JNvKI3O
         hCx61N6poBlNEua4/w6gUjkC1SQBrPkYu5dWVxc1D2XcxFiNk0rcjc3kZkwH8l+ovBaO
         OQ1UVHS4/vDfhNBKp8YpJDayzuChbeQB/xSgZcYTliFrBNdjGIiZ79NDbIPBW8y53xug
         BrGw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=XTXOT3PTQaYYqLr+YkwfmLP4vZijQPTV+yL5uM5usc8=;
        b=aQZXotbWrJdTxXGBAK7/oo+ipvp3pA3Fapocgjp3S9tSNfZVXkNSNNjig9Dt2Rulzk
         MOAktzWI2AgJ29tKms3ummwekh4zo+2kX3Ns7m04XyGu39RkFz3QQ0WboEcBJF+KHZgK
         7ZmK24nYb1GzNqxOCIJk4x5rTXsCbJEPe6C0mUyx5eZX+SFefjD4ADKP7BxqyHxuMOwS
         CjwZSeZTDDtVX0KOuwSecBFaGAIQTbUScgK6Rx3/av/NLcOQx6MMCwkrTwSG+WTh+kqV
         xCyLw5dHy9G0VFISp45Jh9aNSlKsF81000ZhAxZXghieYZpurELuYEcLm+uUHyWhvhNu
         hBcg==
X-Gm-Message-State: APjAAAVuMTjSbMGP+hjDjnLWV37rglIyvJNsHNxrz7cFTU6uCi1zh0HR
        7740D+mKnWC1UqQl/CBhPoOnSIInyiAv1ob8TaCXHuGB/Y5WKNnsbqmmnaIVgrUHc7tloAslrE2
        O9UMUm1eBoAv5fhbKB0nDj7dCa962vpZSUWtrlvOQ85YC5r58p6zgWVO/5mL/3vBB9wQ0
X-Google-Smtp-Source: 
 APXvYqwDF6ec+rIwZYgX2E84SGvt778JBkSQfQtR5T+gmWXNXHdoNP9EMbmLQxvGrjNi/yM9WpCEYhBrBKgEJDpw
X-Received: by 2002:a63:5508:: with SMTP id j8mr9132147pgb.97.1573190087463;
 Thu, 07 Nov 2019 21:14:47 -0800 (PST)
Date: Thu,  7 Nov 2019 21:14:36 -0800
In-Reply-To: <20191108051439.185635-1-aaronlewis@google.com>
Message-Id: <20191108051439.185635-2-aaronlewis@google.com>
Mime-Version: 1.0
References: <20191108051439.185635-1-aaronlewis@google.com>
X-Mailer: git-send-email 2.24.0.432.g9d3f5f5b63-goog
Subject: [PATCH v4 1/4] kvm: nested: Introduce read_and_check_msr_entry()
From: Aaron Lewis <aaronlewis@google.com>
To: kvm@vger.kernel.org
Cc: Jim Mattson <jmattson@google.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Aaron Lewis <aaronlewis@google.com>,
        Liran Alon <liran.alon@oracle.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add the function read_and_check_msr_entry() which just pulls some code
out of nested_vmx_store_msr().  This will be useful as reusable code in
upcoming patches.

Reviewed-by: Liran Alon <liran.alon@oracle.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
Signed-off-by: Aaron Lewis <aaronlewis@google.com>
---
 arch/x86/kvm/vmx/nested.c | 35 ++++++++++++++++++++++-------------
 1 file changed, 22 insertions(+), 13 deletions(-)

```
#### [kvm-unit-tests PATCH 01/17] arm: gic: Enable GIC MMIO tests for GICv3 as well
##### From: Andre Przywara <andre.przywara@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andre Przywara <andre.przywara@arm.com>
X-Patchwork-Id: 11234977
Return-Path: <SRS0=CHcm=ZA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E72991599
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  8 Nov 2019 14:42:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id CFBED222C5
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  8 Nov 2019 14:42:53 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726977AbfKHOmx (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 8 Nov 2019 09:42:53 -0500
Received: from foss.arm.com ([217.140.110.172]:44522 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726036AbfKHOmw (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 8 Nov 2019 09:42:52 -0500
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id D80CD7A7;
        Fri,  8 Nov 2019 06:42:51 -0800 (PST)
Received: from donnerap.arm.com (donnerap.cambridge.arm.com [10.1.197.44])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 BAD8A3F719;
        Fri,  8 Nov 2019 06:42:50 -0800 (PST)
From: Andre Przywara <andre.przywara@arm.com>
To: Andrew Jones <drjones@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>
Cc: kvmarm@lists.cs.columbia.edu, linux-arm-kernel@lists.infradead.org,
        kvm@vger.kernel.org, Marc Zyngier <maz@kernel.org>,
        Alexandru Elisei <alexandru.elisei@arm.com>
Subject: [kvm-unit-tests PATCH 01/17] arm: gic: Enable GIC MMIO tests for
 GICv3 as well
Date: Fri,  8 Nov 2019 14:42:24 +0000
Message-Id: <20191108144240.204202-2-andre.przywara@arm.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20191108144240.204202-1-andre.przywara@arm.com>
References: <20191108144240.204202-1-andre.przywara@arm.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

So far the GIC MMIO tests were only enabled for a GICv2 guest. Modern
machines tend to have a GICv3-only GIC, so can't run those tests.
It turns out that most GIC distributor registers we test in the unit
tests are actually the same in GICv3, so we can just enable those tests
for GICv3 guests as well.
The only exception is the CPU number in the TYPER register, which is
only valid in the GICv2 compat mode (ARE=0), which KVM does not support.
So we protect this test against running on a GICv3 guest.

Signed-off-by: Andre Przywara <andre.przywara@arm.com>
---
 arm/gic.c            | 13 +++++++++++--
 arm/unittests.cfg    | 26 ++++++++++++++++++++++----
 lib/arm/asm/gic-v3.h |  2 ++
 3 files changed, 35 insertions(+), 6 deletions(-)

```
#### [PATCH 1/3] kvm: arm: VGIC: Prepare for handling two interrupt groups
##### From: Andre Przywara <andre.przywara@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andre Przywara <andre.przywara@arm.com>
X-Patchwork-Id: 11235321
Return-Path: <SRS0=CHcm=ZA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B8DFB1850
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  8 Nov 2019 17:50:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 99200222C4
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  8 Nov 2019 17:50:02 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730968AbfKHRuB (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 8 Nov 2019 12:50:01 -0500
Received: from foss.arm.com ([217.140.110.172]:47726 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729775AbfKHRuB (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 8 Nov 2019 12:50:01 -0500
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id A5C3B7A7;
        Fri,  8 Nov 2019 09:50:00 -0800 (PST)
Received: from donnerap.arm.com (donnerap.cambridge.arm.com [10.1.197.44])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 55FD23F719;
        Fri,  8 Nov 2019 09:49:59 -0800 (PST)
From: Andre Przywara <andre.przywara@arm.com>
To: Marc Zyngier <maz@kernel.org>
Cc: kvmarm@lists.cs.columbia.edu, linux-arm-kernel@lists.infradead.org,
        kvm@vger.kernel.org,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>
Subject: [PATCH 1/3] kvm: arm: VGIC: Prepare for handling two interrupt groups
Date: Fri,  8 Nov 2019 17:49:50 +0000
Message-Id: <20191108174952.740-2-andre.przywara@arm.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20191108174952.740-1-andre.przywara@arm.com>
References: <20191108174952.740-1-andre.przywara@arm.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The GIC specification describes support for two distinct interrupt
groups, which can be enabled independently from each other. At the
moment our VGIC emulation does not really honour this, so using
Group0 interrupts with the GICv3 emulation does not work as expected
at the moment.

Prepare the code for dealing with the *two* interrupt groups:
Allow to handle the two enable bits in the distributor, by providing
accessors. At the moment this still only honours group1, because we
need more code to properly differentiate the group enables.
Also provide a stub function to later implement the re-scanning of all
IRQs, should the group enable bit for a group change.

This patch does not change the current behaviour yet, but just provides
the infrastructure bits separately, mostly for review purposes.

Signed-off-by: Andre Przywara <andre.przywara@arm.com>
---
 include/kvm/arm_vgic.h           |  7 ++-
 virt/kvm/arm/vgic/vgic-debug.c   |  2 +-
 virt/kvm/arm/vgic/vgic-mmio-v2.c | 23 ++++++----
 virt/kvm/arm/vgic/vgic-mmio-v3.c | 22 +++++----
 virt/kvm/arm/vgic/vgic.c         | 76 +++++++++++++++++++++++++++++++-
 virt/kvm/arm/vgic/vgic.h         |  3 ++
 6 files changed, 110 insertions(+), 23 deletions(-)

```
#### [PATCH] vsock/virtio: fix sock refcnt holding during the shutdown
##### From: Stefano Garzarella <sgarzare@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stefano Garzarella <sgarzare@redhat.com>
X-Patchwork-Id: 11235225
Return-Path: <SRS0=CHcm=ZA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A9F6714E5
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  8 Nov 2019 16:09:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 8778421924
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  8 Nov 2019 16:09:00 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="c7ZMerKl"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726843AbfKHQI7 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 8 Nov 2019 11:08:59 -0500
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:55683 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726036AbfKHQI7 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 8 Nov 2019 11:08:59 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1573229338;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=K93xC4W4XxB9V/XDY2JHTux4Xj+XQzupJKYWOTL6WL8=;
        b=c7ZMerKlfRKJ2H93YM+oF0OGzVsrGZNSQ8Ke/1uY8xoPjN+HtrPerX+asLLhbVTGyPI5uE
        NB418KZGA1d5BEZVx8mmkKinLOtSRCrJSUUTfpP8DfVtyCcVOoS2KoU34MQrhCzgY/F9gG
        l7kdpbvXQJl6/Qc5verSIAu7tj+ra+o=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-387-ko3GzfECMG-Z6GrtGtEBvw-1; Fri, 08 Nov 2019 11:08:57 -0500
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 9EDCC1005500;
        Fri,  8 Nov 2019 16:08:55 +0000 (UTC)
Received: from steredhat.redhat.com (ovpn-117-238.ams2.redhat.com
 [10.36.117.238])
        by smtp.corp.redhat.com (Postfix) with ESMTP id E69AC60BE2;
        Fri,  8 Nov 2019 16:08:50 +0000 (UTC)
From: Stefano Garzarella <sgarzare@redhat.com>
To: netdev@vger.kernel.org
Cc: linux-kernel@vger.kernel.org,
        Stephen Barber <smbarber@chromium.org>,
        Stefan Hajnoczi <stefanha@redhat.com>, kvm@vger.kernel.org,
        "David S. Miller" <davem@davemloft.net>,
        virtualization@lists.linux-foundation.org
Subject: [PATCH] vsock/virtio: fix sock refcnt holding during the shutdown
Date: Fri,  8 Nov 2019 17:08:50 +0100
Message-Id: <20191108160850.51278-1-sgarzare@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
X-MC-Unique: ko3GzfECMG-Z6GrtGtEBvw-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The "42f5cda5eaf4" commit rightly set SOCK_DONE on peer shutdown,
but there is an issue if we receive the SHUTDOWN(RDWR) while the
virtio_transport_close_timeout() is scheduled.
In this case, when the timeout fires, the SOCK_DONE is already
set and the virtio_transport_close_timeout() will not call
virtio_transport_reset() and virtio_transport_do_close().
This causes that both sockets remain open and will never be released,
preventing the unloading of [virtio|vhost]_transport modules.

This patch fixes this issue, calling virtio_transport_reset() and
virtio_transport_do_close() when we receive the SHUTDOWN(RDWR)
and there is nothing left to read.

Fixes: 42f5cda5eaf4 ("vsock/virtio: set SOCK_DONE on peer shutdown")
Cc: Stephen Barber <smbarber@chromium.org>
Signed-off-by: Stefano Garzarella <sgarzare@redhat.com>
---
 net/vmw_vsock/virtio_transport_common.c | 8 +++++---
 1 file changed, 5 insertions(+), 3 deletions(-)

```
