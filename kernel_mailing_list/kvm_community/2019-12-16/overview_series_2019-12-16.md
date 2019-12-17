#### [kvm-unit-tests PATCH 01/16] libcflat: Add other size defines
##### From: Eric Auger <eric.auger@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Auger <eric.auger@redhat.com>
X-Patchwork-Id: 11294247
Return-Path: <SRS0=hJeD=2G=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 41210930
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 16 Dec 2019 14:03:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1584020717
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 16 Dec 2019 14:03:37 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="LDc6WR51"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728025AbfLPODf (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 16 Dec 2019 09:03:35 -0500
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:23115 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1727894AbfLPODf (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 16 Dec 2019 09:03:35 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1576505014;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=t6+fViJWtutY+mnVSFTppbDOaIGnV3IhxBHpKWV/0xQ=;
        b=LDc6WR51wNInv8gAo6dIG2p4Qwracdn5fkDCl2v5mv6i63VkxMq3JkVw5wmwzW1wrqfSuG
        LcL5vKs5QhTwzxKYRTQbz89hFjMJ9A3RdyuGC+dTC5iBbld1eyoNvVs2dPLeCoAxZY80HQ
        0qMLhUGDd2WmPFbW3ssUt/kBL51S7Ug=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-325-EIXWn0LVPAK0NyPECAhhcQ-1; Mon, 16 Dec 2019 09:03:33 -0500
X-MC-Unique: EIXWn0LVPAK0NyPECAhhcQ-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 060CF8024DA;
        Mon, 16 Dec 2019 14:03:31 +0000 (UTC)
Received: from laptop.redhat.com (ovpn-116-117.ams2.redhat.com
 [10.36.116.117])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 24908675BF;
        Mon, 16 Dec 2019 14:03:22 +0000 (UTC)
From: Eric Auger <eric.auger@redhat.com>
To: eric.auger.pro@gmail.com, eric.auger@redhat.com, maz@kernel.org,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        qemu-devel@nongnu.org, qemu-arm@nongnu.org
Cc: drjones@redhat.com, andre.przywara@arm.com,
        peter.maydell@linaro.org, yuzenghui@huawei.com,
        alexandru.elisei@arm.com, thuth@redhat.com
Subject: [kvm-unit-tests PATCH 01/16] libcflat: Add other size defines
Date: Mon, 16 Dec 2019 15:02:20 +0100
Message-Id: <20191216140235.10751-2-eric.auger@redhat.com>
In-Reply-To: <20191216140235.10751-1-eric.auger@redhat.com>
References: <20191216140235.10751-1-eric.auger@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Introduce additional SZ_256, SZ_8K, SZ_16K macros that will
be used by ITS tests.

Signed-off-by: Eric Auger <eric.auger@redhat.com>
---
 lib/libcflat.h | 3 +++
 1 file changed, 3 insertions(+)

```
#### [PATCH v2 8/8] KVM: selftests: Add parameter to _vm_create for memslot 0 base paddr
##### From: Ben Gardon <bgardon@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ben Gardon <bgardon@google.com>
X-Patchwork-Id: 11295349
Return-Path: <SRS0=hJeD=2G=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 84E766C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 16 Dec 2019 21:36:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 6285924672
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 16 Dec 2019 21:36:22 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="WpvSEkDZ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727742AbfLPVgI (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 16 Dec 2019 16:36:08 -0500
Received: from mail-pf1-f202.google.com ([209.85.210.202]:43587 "EHLO
        mail-pf1-f202.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727785AbfLPVgH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 16 Dec 2019 16:36:07 -0500
Received: by mail-pf1-f202.google.com with SMTP id x199so7715409pfc.10
        for <kvm@vger.kernel.org>; Mon, 16 Dec 2019 13:36:07 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=uVc2axwkCnCZhi+X312ppAdnVSbc0L4toMqGqZnNMKw=;
        b=WpvSEkDZ3zGJQkjjyek7brDRW8CLSSj/z+kyUghXynSz0CIPG/Pkh7uHpylMv+lsCV
         TBEOmtduByp41X120yvyW+L8fCIYUmgUBI2aEGCvxzdYsI003XS4/mLtP0CVM1msY+Hk
         5WO1bpSwfIZ7uZQCdxwxrvfo2tA7Ek7XaxrYgUxw9C2BdjXTgXH9m8uVA2BgZNxcZJ5S
         /NOeN4RMYprVaCR06rF4KVOnuh8Dj7m4BetXNrBKpZt0L7wLeuagWrJS0QyOcKe/dODK
         sID4umEhHdU1D/KEoA6ciVgckNKpatKM3u+B/Qu76ggC+9Fw1kJa86qkXsaUrnSxE8kA
         XBaw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=uVc2axwkCnCZhi+X312ppAdnVSbc0L4toMqGqZnNMKw=;
        b=qe/MPJPwpVLrzuDjqEzxer2+SelbdLp92ZQNWD3R+DvqkTXxlSAeHdekaI9fMjuKc2
         xSoxeIyuaUzz8CkGWoeGf5XdC9ZRkDPeBn8E4xjHJWkQZUGec6q/pmvLODRn6vIKh2y7
         IomALZGcUXzUI8nbxysE58oxmdQzUHMGn5LodqFHca6nsczUIMp8tjbCoQwYRdcHOdyb
         W3goUhIcJXzdZBopAkr7+93GMpxhzva0CozMMTYJRGFgUTcfcxayRsRQwUtGqpyZtTzh
         MhR0SznULGAib8lLA2Zh9WGWlPMWQxEhJzGfeRZdoh3g/TwMtp7Xl6ehlnoTZUUDwp8m
         J5bw==
X-Gm-Message-State: APjAAAXiPYmCPF9j6jPHTnhgj6fCP0TsnzpDW4lr5ViYcvAtJ1HF0Ex0
        0DLy6EPFhFjtF3vtL8cUsXhuonw1M8o3
X-Google-Smtp-Source: 
 APXvYqxAvjI7NezKNIRCnRAWCElstJUl5eVy0r8/FtYh7zCfXc8erNLof+lG3knmkBtIjjVxutbT4Tg4gE8y
X-Received: by 2002:a63:1662:: with SMTP id 34mr20427182pgw.77.1576532166453;
 Mon, 16 Dec 2019 13:36:06 -0800 (PST)
Date: Mon, 16 Dec 2019 13:35:31 -0800
In-Reply-To: <20191216213532.91237-1-bgardon@google.com>
Message-Id: <20191216213532.91237-9-bgardon@google.com>
Mime-Version: 1.0
References: <20191216213532.91237-1-bgardon@google.com>
X-Mailer: git-send-email 2.24.1.735.g03f4e72817-goog
Subject: [PATCH v2 8/8] KVM: selftests: Add parameter to _vm_create for
 memslot 0 base paddr
From: Ben Gardon <bgardon@google.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        linux-kselftest@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Cannon Matthews <cannonmatthews@google.com>,
        Peter Xu <peterx@redhat.com>,
        Andrew Jones <drjones@redhat.com>,
        Ben Gardon <bgardon@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

KVM creates internal memslots between 3 and 4 GiB paddrs on the first
vCPU creation. If memslot 0 is large enough it collides with these
memslots an causes vCPU creation to fail. Add a paddr parameter for
memslot 0 so that tests which support large VMs can relocate memslot 0
above 4 GiB.

Signed-off-by: Ben Gardon <bgardon@google.com>
---
 tools/testing/selftests/kvm/lib/kvm_util.c | 15 +++++++++++----
 1 file changed, 11 insertions(+), 4 deletions(-)

```
#### [PATCH v2 1/8] KVM: selftests: Create a demand paging testFrom: Ben Gardon <bgardon@google.com>
##### From: Ben Gardon <bgardon@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ben Gardon <bgardon@google.com>
X-Patchwork-Id: 11295365
Return-Path: <SRS0=hJeD=2G=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 150E317F0
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 16 Dec 2019 21:36:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D389224676
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 16 Dec 2019 21:36:41 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="iDB0rV3J"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727639AbfLPVfx (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 16 Dec 2019 16:35:53 -0500
Received: from mail-pj1-f73.google.com ([209.85.216.73]:37613 "EHLO
        mail-pj1-f73.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727548AbfLPVfx (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 16 Dec 2019 16:35:53 -0500
Received: by mail-pj1-f73.google.com with SMTP id a31so5237599pje.4
        for <kvm@vger.kernel.org>; Mon, 16 Dec 2019 13:35:52 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=bxiiqlGhMy/IAtaVqxDYYBiF2ABUxURzQMEyaZ64Y2g=;
        b=iDB0rV3JcfDyBM4wT1ltyqRyslcXYT6h6I14++IL+DD4H1uC6KzHd/KyttG4MVK/9w
         MZZXDJSqReAnjcqvyy62+Tf+OJbMQAfBQYfD8LrRVmaolgyYYiglULVDxERvm7e697oj
         M9cqdvS/sh3h4geOWqOXIbsXoEKek3TtJLATVbc4twu4fT8mtYBj1pFT67ej/IplwFWE
         9WxXbWpZWKhhX3B3gOfF3dmphpyX/L+6kK4YGdg3ENavvvnNZDRKIr6ijuso8Pgm1+cK
         y7JUtLOGHREecsz1UyYBuUvzIGKHim78rhxJw+DLQZwYmCYHdPix8+H48Q/ZRtpE/laa
         j3Mw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=bxiiqlGhMy/IAtaVqxDYYBiF2ABUxURzQMEyaZ64Y2g=;
        b=pGOhZlTyHGELNd2MZY7ukfB9oRY7oAbKwdOkRI5H9bc4603Pl0vRR2C5KgPdi/QIud
         KSeEtvGXXmgO7JHoERiRKM1KoQ4qTLxz9ywgObnS//jeFRw/RhYxhDlcnOzjZ2oH5NAa
         uh33LVgKP/JWdcbjU/uANP4oPg3udmkqx+ILGE0Aa3Gr/azrOccCSp1UQ9yKmu1+Eoy2
         tYqXxDIDVybz00rm/lQ3cKirWYLLQnQaNpfcJdKbySyU2cCJ5GOngnAQDqtFFRzTDGiP
         MzrgrS675epVgsE//nNFCIDGZU8LLoVSnbD27l7EuKNa2jFFAtMOrkDmjwUP1bHQcLPc
         Lj3w==
X-Gm-Message-State: APjAAAWRh8O7dCxSXnqSaVZ98pSgo/UvgRylvM30/x12jTFHP6rmzmpY
        oh+gEXen1Ms6I3XEWMrz/VuKoH84bbPb
X-Google-Smtp-Source: 
 APXvYqyoWbO4KPlJHmaBROqSVBcbRFaCxjydZ0hsIO9QD7lI8cvjcA8wD5ysHCKxUKOnk77q/i6GXgpZPQfp
X-Received: by 2002:a63:d543:: with SMTP id v3mr20522511pgi.285.1576532151702;
 Mon, 16 Dec 2019 13:35:51 -0800 (PST)
Date: Mon, 16 Dec 2019 13:35:24 -0800
In-Reply-To: <20191216213532.91237-1-bgardon@google.com>
Message-Id: <20191216213532.91237-2-bgardon@google.com>
Mime-Version: 1.0
References: <20191216213532.91237-1-bgardon@google.com>
X-Mailer: git-send-email 2.24.1.735.g03f4e72817-goog
Subject: [PATCH v2 1/8] KVM: selftests: Create a demand paging test
From: Ben Gardon <bgardon@google.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        linux-kselftest@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Cannon Matthews <cannonmatthews@google.com>,
        Peter Xu <peterx@redhat.com>,
        Andrew Jones <drjones@redhat.com>,
        Ben Gardon <bgardon@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

While userfaultfd, KVM's demand paging implementation, is not specific
to KVM, having a benchmark for its performance will be useful for
guiding performance improvements to KVM. As a first step towards creating
a userfaultfd demand paging test, create a simple memory access test,
based on dirty_log_test.

Signed-off-by: Ben Gardon <bgardon@google.com>
---
 tools/testing/selftests/kvm/.gitignore        |   1 +
 tools/testing/selftests/kvm/Makefile          |   1 +
 .../selftests/kvm/demand_paging_test.c        | 268 ++++++++++++++++++
 3 files changed, 270 insertions(+)
 create mode 100644 tools/testing/selftests/kvm/demand_paging_test.c

```
#### [PATCH v3 1/8] KVM: selftests: Create a demand paging testFrom: Ben Gardon <bgardon@google.com>
##### From: Ben Gardon <bgardon@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ben Gardon <bgardon@google.com>
X-Patchwork-Id: 11295371
Return-Path: <SRS0=hJeD=2G=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6156F109A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 16 Dec 2019 21:39:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 33E3B24676
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 16 Dec 2019 21:39:10 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="GqPzjsSz"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727644AbfLPVjJ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 16 Dec 2019 16:39:09 -0500
Received: from mail-yb1-f201.google.com ([209.85.219.201]:35930 "EHLO
        mail-yb1-f201.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727283AbfLPVjJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 16 Dec 2019 16:39:09 -0500
Received: by mail-yb1-f201.google.com with SMTP id 132so7612386ybd.3
        for <kvm@vger.kernel.org>; Mon, 16 Dec 2019 13:39:08 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=bxiiqlGhMy/IAtaVqxDYYBiF2ABUxURzQMEyaZ64Y2g=;
        b=GqPzjsSzHp6J/PfxddF3hz9NLSvH0IZzJWyTzZ1VDFTzisdLDz0J5w37FhwQ/PiXAG
         A/3WNPqjFzzw7ZR0SCj6mnbRMQN4z04aEEKqIkqDzbrhYSw1yyWPcjnBPWXzf5NHBrt2
         HCkSwReA4LiKFgnbqQlamMMXlBqp9Lov/z4xShyuSZpnqvTmkBACZIrS/eg5zDk1fjz6
         HElel7voQsRYj3mmDX1g3K9LoNfZAlf0PtQ8mq5cfVqiHeY2R/yd3CRDef7slhz+Zb99
         HNJzhtHAIeCTrZ+mVQlXuyX+Yb3BDrnCCnc7PhBnuMSkl6ATkpjXUeWxlrIQrGjFI5+P
         ugYA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=bxiiqlGhMy/IAtaVqxDYYBiF2ABUxURzQMEyaZ64Y2g=;
        b=L6uqVes6cjbd7SCmzpAOfdsSd8urvoUtV8LYnyBwXNRVbSUY4mjdQLB3DQm7kd8DZ4
         nI8AN6cXd/pLRtmVLv3RPu2GkIGpFeIq6pBuBlzQuIgyX3AUq1VH2FIy3anZopFjedHF
         wEWXBkAtAkQGCtrB9+BQmPFfFr7K6z7ZhW4WqEB9pL0aDEuoVPgFfY4iSJZj6B9RcUkB
         v4/UZzP/SNwxB8cO6cq0HgdCnFqXRgjq8CLgTiINbhAPlsqI/RNW9csCjroWBIMBnVYe
         i8b+9mYoPW62TDgjQQRYgq17SdNShhTXqJNbAQuCV/qoydTNYbNjXjQlqkM1aezas9oG
         9kiA==
X-Gm-Message-State: APjAAAXlLRknpX2y6CUDjG7qrCmvJ6wgT6lZUJlEt6PIbUmbe2m8c9KI
        TCh0oevsQsdIftdb/HNZQi7qBRgH8IW/
X-Google-Smtp-Source: 
 APXvYqyES5e5iIolFxxBkzyJ+r1/AHVqE8XHO3sSbGror5h8fa8ZHlF/ACgHdzQYe9m++jQMbSu+qbu4p33c
X-Received: by 2002:a25:7502:: with SMTP id q2mr21638052ybc.480.1576532347342;
 Mon, 16 Dec 2019 13:39:07 -0800 (PST)
Date: Mon, 16 Dec 2019 13:38:54 -0800
In-Reply-To: <20191216213901.106941-1-bgardon@google.com>
Message-Id: <20191216213901.106941-2-bgardon@google.com>
Mime-Version: 1.0
References: <20191216213901.106941-1-bgardon@google.com>
X-Mailer: git-send-email 2.24.1.735.g03f4e72817-goog
Subject: [PATCH v3 1/8] KVM: selftests: Create a demand paging test
From: Ben Gardon <bgardon@google.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        linux-kselftest@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Cannon Matthews <cannonmatthews@google.com>,
        Peter Xu <peterx@redhat.com>,
        Andrew Jones <drjones@redhat.com>,
        Ben Gardon <bgardon@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

While userfaultfd, KVM's demand paging implementation, is not specific
to KVM, having a benchmark for its performance will be useful for
guiding performance improvements to KVM. As a first step towards creating
a userfaultfd demand paging test, create a simple memory access test,
based on dirty_log_test.

Signed-off-by: Ben Gardon <bgardon@google.com>
---
 tools/testing/selftests/kvm/.gitignore        |   1 +
 tools/testing/selftests/kvm/Makefile          |   1 +
 .../selftests/kvm/demand_paging_test.c        | 268 ++++++++++++++++++
 3 files changed, 270 insertions(+)
 create mode 100644 tools/testing/selftests/kvm/demand_paging_test.c

```
#### [PATCH v10 Kernel 1/5] vfio: KABI for migration interface for device state
##### From: Kirti Wankhede <kwankhede@nvidia.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kirti Wankhede <kwankhede@nvidia.com>
X-Patchwork-Id: 11295251
Return-Path: <SRS0=hJeD=2G=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AA3BB138D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 16 Dec 2019 20:50:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7D78D218AC
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 16 Dec 2019 20:50:38 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=nvidia.com header.i=@nvidia.com
 header.b="oOuDhHab"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726663AbfLPUuh (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 16 Dec 2019 15:50:37 -0500
Received: from hqnvemgate25.nvidia.com ([216.228.121.64]:15785 "EHLO
        hqnvemgate25.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726530AbfLPUuh (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 16 Dec 2019 15:50:37 -0500
Received: from hqpgpgate101.nvidia.com (Not Verified[216.228.121.13]) by
 hqnvemgate25.nvidia.com (using TLS: TLSv1.2, DES-CBC3-SHA)
        id <B5df7ee120001>; Mon, 16 Dec 2019 12:50:26 -0800
Received: from hqmail.nvidia.com ([172.20.161.6])
  by hqpgpgate101.nvidia.com (PGP Universal service);
  Mon, 16 Dec 2019 12:50:35 -0800
X-PGP-Universal: processed;
        by hqpgpgate101.nvidia.com on Mon, 16 Dec 2019 12:50:35 -0800
Received: from HQMAIL105.nvidia.com (172.20.187.12) by HQMAIL105.nvidia.com
 (172.20.187.12) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Mon, 16 Dec
 2019 20:50:34 +0000
Received: from kwankhede-dev.nvidia.com (10.124.1.5) by HQMAIL105.nvidia.com
 (172.20.187.12) with Microsoft SMTP Server (TLS) id 15.0.1473.3 via Frontend
 Transport; Mon, 16 Dec 2019 20:50:27 +0000
From: Kirti Wankhede <kwankhede@nvidia.com>
To: <alex.williamson@redhat.com>, <cjia@nvidia.com>
CC: <kevin.tian@intel.com>, <ziye.yang@intel.com>,
        <changpeng.liu@intel.com>, <yi.l.liu@intel.com>,
        <mlevitsk@redhat.com>, <eskultet@redhat.com>, <cohuck@redhat.com>,
        <dgilbert@redhat.com>, <jonathan.davies@nutanix.com>,
        <eauger@redhat.com>, <aik@ozlabs.ru>, <pasic@linux.ibm.com>,
        <felipe@nutanix.com>, <Zhengxiao.zx@Alibaba-inc.com>,
        <shuangtai.tst@alibaba-inc.com>, <Ken.Xue@amd.com>,
        <zhi.a.wang@intel.com>, <yan.y.zhao@intel.com>,
        <qemu-devel@nongnu.org>, <kvm@vger.kernel.org>,
        Kirti Wankhede <kwankhede@nvidia.com>
Subject: [PATCH v10 Kernel 1/5] vfio: KABI for migration interface for device
 state
Date: Tue, 17 Dec 2019 01:51:36 +0530
Message-ID: <1576527700-21805-2-git-send-email-kwankhede@nvidia.com>
X-Mailer: git-send-email 2.7.0
In-Reply-To: <1576527700-21805-1-git-send-email-kwankhede@nvidia.com>
References: <1576527700-21805-1-git-send-email-kwankhede@nvidia.com>
X-NVConfidentiality: public
MIME-Version: 1.0
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1576529426; bh=IxVUQFInkIkXlBC++lY6n5LPiVRy+YaYSpOpnkQ5ZkQ=;
        h=X-PGP-Universal:From:To:CC:Subject:Date:Message-ID:X-Mailer:
         In-Reply-To:References:X-NVConfidentiality:MIME-Version:
         Content-Type;
        b=oOuDhHabqDlh3SmZBSKrqKnD5Mko69ynU2KZ5S6hGekQnmWSQT0l2KvaWRW0oJ8sA
         rinsout+G1kN5mS7TcRr/1XYFhftD6N88OSx/0yAn2EApf4HQdb47T4j4Fu/WF+L54
         MraZbLtePTYyM7i1LuQqHBlPJf49ahpOVyJlSyFn3ltoHaKbS54DWFf2119B0ynhCS
         AgIL0/z65ljSOUr4q4p0Dn7jHBhSGQ/SKvAVkOmgFVdQGG1XwQI9IDPPNYOe6J/ylu
         rPTGEM1Evdp+D0GT6fgc3HPnGIfqPqaSPYEpt6FTSVB7brV8SGcrHyYIKSjkiJ71gm
         toBshCNdx7wsg==
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

- Defined MIGRATION region type and sub-type.

- Defined vfio_device_migration_info structure which will be placed at 0th
  offset of migration region to get/set VFIO device related information.
  Defined members of structure and usage on read/write access.

- Defined device states and added state transition details in the comment.

- Added sequence to be followed while saving and resuming VFIO device state

Signed-off-by: Kirti Wankhede <kwankhede@nvidia.com>
Reviewed-by: Neo Jia <cjia@nvidia.com>
---
 include/uapi/linux/vfio.h | 180 ++++++++++++++++++++++++++++++++++++++++++++++
 1 file changed, 180 insertions(+)

```
#### [kvm-unit-tests PATCH 01/10] arm64: Provide read/write_sysreg_s
##### From: Eric Auger <eric.auger@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Auger <eric.auger@redhat.com>
X-Patchwork-Id: 11295221
Return-Path: <SRS0=hJeD=2G=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 35F371580
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 16 Dec 2019 20:48:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1489924683
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 16 Dec 2019 20:48:20 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="JuT3wKT0"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727435AbfLPUsQ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 16 Dec 2019 15:48:16 -0500
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:32342 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1727036AbfLPUsO (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 16 Dec 2019 15:48:14 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1576529294;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=5QgGQR5lmCzHdU2tw8u26Dp0LVz138MaKuXfv7AyzLc=;
        b=JuT3wKT0NUxnVUL8Gyg/dpTnyQoBym9nVOgh7O523VxgLg16wTTrR8XwacysfLy3N4Z3VT
        pxi4oGbx5gpTW6aOO6jv28TTY0FisaXEoQltAep1ztiMamCqhIvgZ3s0jEZoRVpnKQbU75
        Im3JH9SwdXCDxTxbinBcqRvqPOntw8c=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-209-BnUFytWeO2mWLhhFFJvweA-1; Mon, 16 Dec 2019 15:48:12 -0500
X-MC-Unique: BnUFytWeO2mWLhhFFJvweA-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id AA7BC108EE8B;
        Mon, 16 Dec 2019 20:48:10 +0000 (UTC)
Received: from laptop.redhat.com (ovpn-116-117.ams2.redhat.com
 [10.36.116.117])
        by smtp.corp.redhat.com (Postfix) with ESMTP id F38875D9C9;
        Mon, 16 Dec 2019 20:48:07 +0000 (UTC)
From: Eric Auger <eric.auger@redhat.com>
To: eric.auger.pro@gmail.com, eric.auger@redhat.com, maz@kernel.org,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        qemu-devel@nongnu.org, qemu-arm@nongnu.org
Cc: drjones@redhat.com, andrew.murray@arm.com, andre.przywara@arm.com,
        peter.maydell@linaro.org, alexandru.elisei@arm.com
Subject: [kvm-unit-tests PATCH 01/10] arm64: Provide read/write_sysreg_s
Date: Mon, 16 Dec 2019 21:47:48 +0100
Message-Id: <20191216204757.4020-2-eric.auger@redhat.com>
In-Reply-To: <20191216204757.4020-1-eric.auger@redhat.com>
References: <20191216204757.4020-1-eric.auger@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Andrew Jones <drjones@redhat.com>

Sometimes we need to test access to system registers which are
missing assembler mnemonics.

Signed-off-by: Andrew Jones <drjones@redhat.com>
Reviewed-by: Alexandru Elisei <alexandru.elisei@arm.com>
---
 lib/arm64/asm/sysreg.h | 11 +++++++++++
 1 file changed, 11 insertions(+)

```
#### [PATCH v11 01/25] mm/gup: factor out duplicate code from four routines
##### From: John Hubbard <jhubbard@nvidia.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: John Hubbard <jhubbard@nvidia.com>
X-Patchwork-Id: 11295909
Return-Path: <SRS0=hJeD=2G=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C34C0112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 16 Dec 2019 22:29:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 9539F21D7D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 16 Dec 2019 22:29:30 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=nvidia.com header.i=@nvidia.com
 header.b="JXf9WyI8"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728435AbfLPW33 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 16 Dec 2019 17:29:29 -0500
Received: from hqnvemgate26.nvidia.com ([216.228.121.65]:11979 "EHLO
        hqnvemgate26.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727801AbfLPWZt (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 16 Dec 2019 17:25:49 -0500
Received: from hqpgpgate102.nvidia.com (Not Verified[216.228.121.13]) by
 hqnvemgate26.nvidia.com (using TLS: TLSv1.2, DES-CBC3-SHA)
        id <B5df8045b0001>; Mon, 16 Dec 2019 14:25:31 -0800
Received: from hqmail.nvidia.com ([172.20.161.6])
  by hqpgpgate102.nvidia.com (PGP Universal service);
  Mon, 16 Dec 2019 14:25:40 -0800
X-PGP-Universal: processed;
        by hqpgpgate102.nvidia.com on Mon, 16 Dec 2019 14:25:40 -0800
Received: from HQMAIL109.nvidia.com (172.20.187.15) by HQMAIL101.nvidia.com
 (172.20.187.10) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Mon, 16 Dec
 2019 22:25:39 +0000
Received: from HQMAIL107.nvidia.com (172.20.187.13) by HQMAIL109.nvidia.com
 (172.20.187.15) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Mon, 16 Dec
 2019 22:25:39 +0000
Received: from hqnvemgw03.nvidia.com (10.124.88.68) by HQMAIL107.nvidia.com
 (172.20.187.13) with Microsoft SMTP Server (TLS) id 15.0.1473.3 via Frontend
 Transport; Mon, 16 Dec 2019 22:25:39 +0000
Received: from blueforge.nvidia.com (Not Verified[10.110.48.28]) by
 hqnvemgw03.nvidia.com with Trustwave SEG (v7,5,8,10121)
        id <B5df804630002>; Mon, 16 Dec 2019 14:25:39 -0800
From: John Hubbard <jhubbard@nvidia.com>
To: Andrew Morton <akpm@linux-foundation.org>
CC: Al Viro <viro@zeniv.linux.org.uk>,
 Alex Williamson <alex.williamson@redhat.com>,
 Benjamin Herrenschmidt <benh@kernel.crashing.org>, =?utf-8?b?QmrDtnJuIFQ=?=
	=?utf-8?b?w7ZwZWw=?= <bjorn.topel@intel.com>,
 Christoph Hellwig <hch@infradead.org>,
 Dan Williams <dan.j.williams@intel.com>, Daniel Vetter <daniel@ffwll.ch>,
 Dave Chinner <david@fromorbit.com>, David Airlie <airlied@linux.ie>,
 "David S . Miller" <davem@davemloft.net>, Ira Weiny <ira.weiny@intel.com>,
 Jan Kara <jack@suse.cz>, Jason Gunthorpe <jgg@ziepe.ca>,
 Jens Axboe <axboe@kernel.dk>, Jonathan Corbet <corbet@lwn.net>,
	=?utf-8?b?SsOpcsO0bWUgR2xpc3Nl?= <jglisse@redhat.com>,
 Magnus Karlsson <magnus.karlsson@intel.com>,
 "Mauro Carvalho Chehab" <mchehab@kernel.org>,
 Michael Ellerman <mpe@ellerman.id.au>, Michal Hocko <mhocko@suse.com>,
 Mike Kravetz <mike.kravetz@oracle.com>, "Paul Mackerras" <paulus@samba.org>,
 Shuah Khan <shuah@kernel.org>, Vlastimil Babka <vbabka@suse.cz>,
 <bpf@vger.kernel.org>, <dri-devel@lists.freedesktop.org>,
 <kvm@vger.kernel.org>, <linux-block@vger.kernel.org>,
 <linux-doc@vger.kernel.org>, <linux-fsdevel@vger.kernel.org>,
 <linux-kselftest@vger.kernel.org>, <linux-media@vger.kernel.org>,
 <linux-rdma@vger.kernel.org>, <linuxppc-dev@lists.ozlabs.org>,
 <netdev@vger.kernel.org>, <linux-mm@kvack.org>,
 LKML <linux-kernel@vger.kernel.org>, John Hubbard <jhubbard@nvidia.com>,
 "Christoph Hellwig" <hch@lst.de>,
 "Aneesh Kumar K . V" <aneesh.kumar@linux.ibm.com>
Subject: [PATCH v11 01/25] mm/gup: factor out duplicate code from four
 routines
Date: Mon, 16 Dec 2019 14:25:13 -0800
Message-ID: <20191216222537.491123-2-jhubbard@nvidia.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20191216222537.491123-1-jhubbard@nvidia.com>
References: <20191216222537.491123-1-jhubbard@nvidia.com>
MIME-Version: 1.0
X-NVConfidentiality: public
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1576535131; bh=HWyNjs6ywGvdqZPFXTnFG85letSRuTmGeFnSWXnBMB0=;
        h=X-PGP-Universal:From:To:CC:Subject:Date:Message-ID:X-Mailer:
         In-Reply-To:References:MIME-Version:X-NVConfidentiality:
         Content-Type:Content-Transfer-Encoding;
        b=JXf9WyI84yLWm1KspnvQLa5nDdAOS6RuWp1sE0TvmP1FtTCq2PQxdNrB19hslAYa/
         NIsH/oLIq/YgsSflPBxJ/2530usBGdFv0BrfVUWaPVWxeNnWcWwDifcQlXGSiHyOFf
         ZW27GWt0ji60B6wfH4TfJ55oeagB+3WKWcw1kQ8P5Jtwre220oYwf3/qMVbLwWFL3Z
         UNmg5YpbxjZpyGozuGfQzxe4wyOm8tDVs5A9vsedBOg4KAEK/wxfief6tmAyrjRzbN
         bZ3IjOBm03aIJ/nyS+rDYvR5t0iZsx++4h1lgWxcWFfYomIts7kuBaRihCxUbseFlP
         uMogSAUw7CkxQ==
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

There are four locations in gup.c that have a fair amount of code
duplication. This means that changing one requires making the same
changes in four places, not to mention reading the same code four
times, and wondering if there are subtle differences.

Factor out the common code into static functions, thus reducing the
overall line count and the code's complexity.

Also, take the opportunity to slightly improve the efficiency of the
error cases, by doing a mass subtraction of the refcount, surrounded
by get_page()/put_page().

Also, further simplify (slightly), by waiting until the the successful
end of each routine, to increment *nr.

Reviewed-by: Christoph Hellwig <hch@lst.de>
Reviewed-by: Jérôme Glisse <jglisse@redhat.com>
Reviewed-by: Jan Kara <jack@suse.cz>
Cc: Ira Weiny <ira.weiny@intel.com>
Cc: Christoph Hellwig <hch@lst.de>
Cc: Aneesh Kumar K.V <aneesh.kumar@linux.ibm.com>
Signed-off-by: John Hubbard <jhubbard@nvidia.com>
---
 mm/gup.c | 91 ++++++++++++++++++++++----------------------------------
 1 file changed, 36 insertions(+), 55 deletions(-)

```
