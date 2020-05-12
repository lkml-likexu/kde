#### [PATCH] ifcvf: move IRQ request/free to status change handlers
##### From: Zhu Lingshan <lingshan.zhu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhu Lingshan <lingshan.zhu@intel.com>
X-Patchwork-Id: 11539837
Return-Path: <SRS0=C6NV=6Z=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 790A5912
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 May 2020 07:22:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6A59E2080C
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 May 2020 07:22:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728649AbgEKHWz (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 11 May 2020 03:22:55 -0400
Received: from mga09.intel.com ([134.134.136.24]:47789 "EHLO mga09.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725790AbgEKHWy (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 11 May 2020 03:22:54 -0400
IronPort-SDR: 
 BI9hI/3MW6a27ZB11cjbKBadyspLaOyCfDUYCd2ZfbNkns44tkie5Y7AIIq5Kt5eEUPOusMVAW
 PFFsHcwFVLDA==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga006.fm.intel.com ([10.253.24.20])
  by orsmga102.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 11 May 2020 00:22:54 -0700
IronPort-SDR: 
 O46fw8gdu1vnp0OfkTQA5RLAW6uGPfxssD+DnyEYWYEHV4PUgk9zzwLbmFNdDI5H/osLoDmXGt
 9t4moQ5nMhOQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,378,1583222400";
   d="scan'208";a="463290725"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.240.192.105])
  by fmsmga006.fm.intel.com with ESMTP; 11 May 2020 00:22:49 -0700
From: Zhu Lingshan <lingshan.zhu@intel.com>
To: mst@redhat.com, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org,
        linux-kernel@vger.kernel.org, netdev@vger.kernel.org,
        jasowang@redhat.com
Cc: lulu@redhat.com, dan.daly@intel.com, cunming.liang@intel.com,
        Zhu Lingshan <lingshan.zhu@intel.com>
Subject: [PATCH] ifcvf: move IRQ request/free to status change handlers
Date: Mon, 11 May 2020 15:19:23 +0800
Message-Id: <1589181563-38400-1-git-send-email-lingshan.zhu@intel.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This commit move IRQ request and free operations from probe()
to VIRTIO status change handler to comply with VIRTIO spec.

VIRTIO spec 1.1, section 2.1.2 Device Requirements: Device Status Field
The device MUST NOT consume buffers or send any used buffer
notifications to the driver before DRIVER_OK.

Signed-off-by: Zhu Lingshan <lingshan.zhu@intel.com>
---
 drivers/vdpa/ifcvf/ifcvf_main.c | 119 ++++++++++++++++++++++++----------------
 1 file changed, 73 insertions(+), 46 deletions(-)

```
#### [PATCH kvm-unit-tests] Fix out-of-tree builds
##### From: Andrew Jones <drjones@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11539767
Return-Path: <SRS0=C6NV=6Z=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 044B481
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 May 2020 07:06:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DFDD0206F5
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 May 2020 07:06:53 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Ckul+kG8"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727927AbgEKHGs (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 11 May 2020 03:06:48 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:57114 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1725790AbgEKHGs (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 11 May 2020 03:06:48 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1589180806;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=+0nK95Gol8cOO8JjWXBWUs+keMg9tHm7nh5wZygjNM4=;
        b=Ckul+kG8BcYwHwzXXJ72IcJxGH+S9pO21pmjXIGJ2ewP0rUOGm1tSjDqICQMTgAqak0Pv4
        +rZfMOLXaMAM3fcur4zaXheaprlTRf0np3IvpDaZzUkxPapQKSErdAkiCf+hbr/TelVjWp
        7hKUJL0/UY6V25+bPsH9bgZyezCc0d4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-62-yIVPVYrXMm2OrkuQANLqvg-1; Mon, 11 May 2020 03:06:45 -0400
X-MC-Unique: yIVPVYrXMm2OrkuQANLqvg-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 342B81895A41
        for <kvm@vger.kernel.org>; Mon, 11 May 2020 07:06:44 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.40.192.233])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 1425D60635;
        Mon, 11 May 2020 07:06:42 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, Thomas Huth <thuth@redhat.com>
Subject: [PATCH kvm-unit-tests] Fix out-of-tree builds
Date: Mon, 11 May 2020 09:06:41 +0200
Message-Id: <20200511070641.23492-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Since b16df9ee5f3b out-of-tree builds have been broken because we
started validating the newly user-configurable $erratatxt file
before linking it into the build dir. We fix this not by moving
the validation, but by removing the linking and instead using the
full path of the $erratatxt file. This allows one to keep that file
separate from the src and build dirs.

Fixes: b16df9ee5f3b ("arch-run: Add reserved variables to the default environ")
Reported-by: Thomas Huth <thuth@redhat.com>
Signed-off-by: Andrew Jones <drjones@redhat.com>
---
 configure | 8 +++-----
 1 file changed, 3 insertions(+), 5 deletions(-)

```
#### [PATCH kvm-unit-tests] x86: avoid multiply defined symbol
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11541337
Return-Path: <SRS0=C6NV=6Z=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CC51192A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 May 2020 17:00:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B30442070B
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 May 2020 17:00:04 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="bs1VBD1J"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730739AbgEKRAD (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 11 May 2020 13:00:03 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:34788 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1730066AbgEKRAD (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 11 May 2020 13:00:03 -0400
Received: from mail-wr1-x442.google.com (mail-wr1-x442.google.com
 [IPv6:2a00:1450:4864:20::442])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id F363BC061A0C
        for <kvm@vger.kernel.org>; Mon, 11 May 2020 10:00:02 -0700 (PDT)
Received: by mail-wr1-x442.google.com with SMTP id x17so11917873wrt.5
        for <kvm@vger.kernel.org>; Mon, 11 May 2020 10:00:02 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=9kWXNAxgTfIQIU7fxFBJpa0sS9+TkbaWh3pDq6++0rA=;
        b=bs1VBD1JIL44wVJ24en8AeeQKL9fARRQgMeYcZZTzIyEZ58qGou8X63Y8fF3o56azJ
         KfwXivx/UEpQpEXxj9gg0pZohGa7L13g4sNgCEns2Ax1X4TNVjJWHc202d23y8NA/6YP
         S+F37AyBsMuVYuH/HvzjOXUzjVl0gZpbNsSkhj5fps4+o3zyZOeck5H1gXNrBvfxvNJi
         hv8QVU58pW1+jKghF9OPlbd4RkGXFVNJk1PHnM0n9WttDnZ48dyNDoWQD1KgDlQS+wjB
         QMsPoPSXnVw3yqu4TR2w2pHFcOTExOMhO7kHn1Bq1dQsEXKCYo4FREkFTmNbQRvlFPym
         bXUQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id
         :mime-version:content-transfer-encoding;
        bh=9kWXNAxgTfIQIU7fxFBJpa0sS9+TkbaWh3pDq6++0rA=;
        b=Owa8J08Ejn0CvWr+pqOKYnQLWC0U0TgrlftMhD2jLtrveFaPq4SEs3Z/gXTBF7rm+r
         vHaxB/cE+SR5B7mmnG8C7LuOEHTsR42wUKXpgJunm81LRiSvJqLc1KBgJW0eCj9ecogr
         DkqjBQGGEWOo6u6hZcvtE43cwlZowWoQ2Krl1PQC84QpXR8BL24slJFBdL44fnJXiCyK
         as98FVJIl87dQ5xVMkmTZqWzPi/hqccAIqaPOj9TAHRe9kLePFkrf/JffGvQsCj+gbkG
         fYlBz/kXcZ0z75OydcBbHYnCog3OloWJpb/12n37CbcSOrv+yKYK4rIIlTERQRBcl7g6
         PUxw==
X-Gm-Message-State: AGi0PuZIl03QAPwnVtlKXubWerz3vvejT95E+VcOlO9FAEYmTfsVnc4T
        9mbHzTJ3hLQZ3eM0CRqPZ8GsHjd8EHI=
X-Google-Smtp-Source: 
 APiQypKTlfhnV9AY9ECkxury0177vlKVo++RPFjZ/bv7HU0qlkkzVUb1NxRuMceFP1oLwQwDa5isUQ==
X-Received: by 2002:adf:afd6:: with SMTP id
 y22mr19681325wrd.417.1589216401444;
        Mon, 11 May 2020 10:00:01 -0700 (PDT)
Received: from donizetti.redhat.com ([2001:b07:6468:f312:4c95:a679:8cf7:9fb6])
        by smtp.gmail.com with ESMTPSA id
 m3sm2947258wrn.96.2020.05.11.10.00.00
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 11 May 2020 10:00:00 -0700 (PDT)
From: Paolo Bonzini <pbonzini@redhat.com>
To: kvm@vger.kernel.org
Cc: "Dr . David Alan Gilbert" <dgilbert@redhat.com>
Subject: [PATCH kvm-unit-tests] x86: avoid multiply defined symbol
Date: Mon, 11 May 2020 18:59:59 +0200
Message-Id: <20200511165959.42442-1-pbonzini@redhat.com>
X-Mailer: git-send-email 2.23.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Fedora 32 croaks about a symbol that is defined twice, fix it.

Reported-by: Dr. David Alan Gilbert <dgilbert@redhat.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 lib/x86/fault_test.c |  2 +-
 lib/x86/usermode.c   |  2 +-
 2 files changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH] KVM: x86: Fix off-by-one error in kvm_vcpu_ioctl_x86_setup_mce
##### From: Jim Mattson <jmattson@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jim Mattson <jmattson@google.com>
X-Patchwork-Id: 11541857
Return-Path: <SRS0=C6NV=6Z=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 38F771668
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 May 2020 22:57:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 164332070B
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 May 2020 22:57:03 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="BrN8i96P"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726079AbgEKW5C (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 11 May 2020 18:57:02 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:34062 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-FAIL-OK-FAIL)
        by vger.kernel.org with ESMTP id S1725854AbgEKW5B (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 11 May 2020 18:57:01 -0400
Received: from mail-qv1-xf4a.google.com (mail-qv1-xf4a.google.com
 [IPv6:2607:f8b0:4864:20::f4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 47E4BC061A0C
        for <kvm@vger.kernel.org>; Mon, 11 May 2020 15:57:00 -0700 (PDT)
Received: by mail-qv1-xf4a.google.com with SMTP id y60so9387710qvy.13
        for <kvm@vger.kernel.org>; Mon, 11 May 2020 15:57:00 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=VTdpLz5V6/LGlvRs4Pjdcz6Ell8P6OcCKx2MGJVF8uc=;
        b=BrN8i96Patmx0wBxgndIVZrgUBR4dw7eIKuHDar+HyJVTT6QqVTHolRVtwbmCYjqnm
         lu+dPn0CeyHU/Jnu31O1jVWcbXysRCr8x+ve9nLW/lcKzs2kLoB8TL7w2HB2ba4cjLsq
         feSOgcbA+M7ndKlGzozd7HAknoNu7O5Egnuu4qoIqL9Ix7TbpACtd/5ZLwMZMAKQscKe
         OXrSSWm0prZ9mN+cbcJ+5yo985+SqGg7GRWUAccKhSCs3I9OswpTwR8WFieWz7XEQUpM
         PMB91Ayu3PRldho7BlXCBS6WePWjBKg6g7XkxKvK5Lp7Tb4uoOKLS0r+E4P1jDh6yp/T
         f5iQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=VTdpLz5V6/LGlvRs4Pjdcz6Ell8P6OcCKx2MGJVF8uc=;
        b=nYQkhaxycY72sK6Yo/MJCIkuQAeoDfhC6m8A8KCmfB22FfScZDxcY5QQFcuS/ZlALs
         M+LfvDl6O+7vfaaYPfOgEr/Is7PW8pvkLKvXZfJzeZWzFkTypZa+8XkQsrGM/t5sPSfE
         7C4XhMGJOjY9FeZIEtAEEk/xtlD0yJQ9C2mNVBSiFZ1EOfxf/A85bO6E9e76jAFTnAcC
         kzMTpGK76lumqKFU2rsk0hI6IpDZBRaSaaTk6ee42OkCaOWFeMBIikUn2qwQJq+/faUe
         2YWaX43UtBfgDFlR/0W2gry0jVsXNdj3vKUnF7h+5Rwgvpttb3K0XCAIH8ExQE+LyYzX
         cZXQ==
X-Gm-Message-State: AGi0PuaPMoeJJMoF009uPKxKX0U0RbHzEtFD2nRJ28JEYUFpOkUdrteL
        s/lwxv32kHFSsef9siRGh06ATlAj3p0PGurr+J5CnnDcxxbuJgOtNu/OD6QlikOEsTUKlP2/l7a
        0EfZ3vxPqJqCXQdzMWIRHx/qEtLdDurfRyeAFh5zKuBVveMDtRRNfNaZs0UkLKxM=
X-Google-Smtp-Source: 
 APiQypJNIV9Soq4zFlRo7C4w9sAwU9layBGNtrWixcjD+1Oc1m3Tl3L1CUAiqIEcDjNfC78LeyGlWDBmTobeFA==
X-Received: by 2002:a0c:e7c2:: with SMTP id c2mr7976983qvo.118.1589237819159;
 Mon, 11 May 2020 15:56:59 -0700 (PDT)
Date: Mon, 11 May 2020 15:56:16 -0700
Message-Id: <20200511225616.19557-1-jmattson@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.26.2.645.ge9eca65c58-goog
Subject: [PATCH] KVM: x86: Fix off-by-one error in
 kvm_vcpu_ioctl_x86_setup_mce
From: Jim Mattson <jmattson@google.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Jim Mattson <jmattson@google.com>, Jue Wang <juew@google.com>,
        Peter Shier <pshier@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Bank_num is a one-based count of banks, not a zero-based index. It
overflows the allocated space only when strictly greater than
KVM_MAX_MCE_BANKS.

Fixes: a9e38c3e01ad ("KVM: x86: Catch potential overrun in MCE setup")
Signed-off-by: Jue Wang <juew@google.com>
Signed-off-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
---
 arch/x86/kvm/x86.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH 1/8] Revert "KVM: async_pf: Fix #DF due to inject "Page not Present" and "Page Ready" exceptions simultaneously"
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11541319
Return-Path: <SRS0=C6NV=6Z=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9DD0E912
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 May 2020 16:48:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 85F2B20722
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 May 2020 16:48:16 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="APxScxYU"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730730AbgEKQsN (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 11 May 2020 12:48:13 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:52086 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1729613AbgEKQsN (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 11 May 2020 12:48:13 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1589215692;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=HhwY47nxj1UdfQsjm+9VtE1yq6uitrdcNiNFnzaGmSs=;
        b=APxScxYUnyiPa8iq3DXwIRzVQL0EBUy3akyKB530FfpvwmW3Mt3cAjz6nlvanEG4TTWAZT
        kcl2LIWxk5EsU3nFPal+hv9F3yF6Yo+E61lij1AenVO9U6ZHTjdofiBCR71XzAUPvprOhK
        nqzjtLRXE5UEWRBJfeg3dHgWdUaOpc4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-123-i1Ob4udyNbKM9TEIVonvRw-1; Mon, 11 May 2020 12:48:07 -0400
X-MC-Unique: i1Ob4udyNbKM9TEIVonvRw-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id BAA87100CCC0;
        Mon, 11 May 2020 16:48:00 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.195.255])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 4FA44341FF;
        Mon, 11 May 2020 16:47:57 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, x86@kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Andy Lutomirski <luto@kernel.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Borislav Petkov <bp@alien8.de>,
        "H. Peter Anvin" <hpa@zytor.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Jim Mattson <jmattson@google.com>,
        Vivek Goyal <vgoyal@redhat.com>, Gavin Shan <gshan@redhat.com>,
        Peter Zijlstra <peterz@infradead.org>,
        linux-kernel@vger.kernel.org
Subject: [PATCH 1/8] Revert "KVM: async_pf: Fix #DF due to inject "Page not
 Present" and "Page Ready" exceptions simultaneously"
Date: Mon, 11 May 2020 18:47:45 +0200
Message-Id: <20200511164752.2158645-2-vkuznets@redhat.com>
In-Reply-To: <20200511164752.2158645-1-vkuznets@redhat.com>
References: <20200511164752.2158645-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Commit 9a6e7c39810e (""KVM: async_pf: Fix #DF due to inject "Page not
Present" and "Page Ready" exceptions simultaneously") added a protection
against 'page ready' notification coming before 'page not ready' is
delivered. This situation seems to be impossible since commit 2a266f23550b
("KVM MMU: check pending exception before injecting APF) which added
'vcpu->arch.exception.pending' check to kvm_can_do_async_pf.

On x86, kvm_arch_async_page_present() has only one call site:
kvm_check_async_pf_completion() loop and we only enter the loop when
kvm_arch_can_inject_async_page_present(vcpu) which when async pf msr
is enabled, translates into kvm_can_do_async_pf().

There is also one problem with the cancellation mechanism. We don't seem
to check that the 'page not ready' notification we're canceling matches
the 'page ready' notification so in theory, we may erroneously drop two
valid events.

Revert the commit.

Reviewed-by: Gavin Shan <gshan@redhat.com>
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/x86.c | 23 +----------------------
 1 file changed, 1 insertion(+), 22 deletions(-)

```
#### [RFC PATCH] KVM: Add module for IRQ forwarding
##### From: Micah Morton <mortonm@chromium.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Micah Morton <mortonm@chromium.org>
X-Patchwork-Id: 11541797
Return-Path: <SRS0=C6NV=6Z=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8625514C0
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 May 2020 22:00:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 616742070B
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 May 2020 22:00:53 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=chromium.org header.i=@chromium.org
 header.b="JGRQh414"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727898AbgEKWAw (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 11 May 2020 18:00:52 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:53646 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-FAIL-OK-FAIL)
        by vger.kernel.org with ESMTP id S1725860AbgEKWAv (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 11 May 2020 18:00:51 -0400
Received: from mail-pg1-x544.google.com (mail-pg1-x544.google.com
 [IPv6:2607:f8b0:4864:20::544])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id C710EC061A0C
        for <kvm@vger.kernel.org>; Mon, 11 May 2020 15:00:51 -0700 (PDT)
Received: by mail-pg1-x544.google.com with SMTP id r10so4684987pgv.8
        for <kvm@vger.kernel.org>; Mon, 11 May 2020 15:00:51 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=chromium.org; s=google;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=yUQSZ/QJsH+GnnKfGI0/uIF5VRRwzEYlI439G/kMBbE=;
        b=JGRQh414yNTT6zgAi7akMzr1Dii+BpmM0aB73XtfMhXynkm+p3olpVtU7IJPbF7tzV
         bZpgxEuPgiHkwQjxiT4Lnb7vZ3swLCdrMKPn8Qe4lSQxUyLx1ztYmIkUQBqF8w4M1l5r
         xhvXlZoP9wRxENUOPIOGxDL9nVE86TBvyCCmI=
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=yUQSZ/QJsH+GnnKfGI0/uIF5VRRwzEYlI439G/kMBbE=;
        b=Psbtt4h56M3Dbljqy+nLwl4dFLOrmTupzA4kYYxyS6T1KjTYt67b5grMiLlBJ/Oirv
         kmoCpr8HvgAIjHbN/KfAjusRPTi5V0dOiuz0KBQjYeFVWEu3/hdao9w2n646QNR82s45
         oO1Z/aTk+MQk6L0W05vl2w63AmMFieyIaUBtVJATW4pLcyjnvWxwnWUqngTpXmQhEIb6
         m1paIqmieZoTBimG09KcBtZgsnEVF1/KfGZJkO636Hb8yAcryOnza+8b7dctkXW+09N2
         2PbSubPYnn8lv82LqzPIkA6rGagMKqrZ/P6+myHsR4E1AaPgPsjmACC2RGlCIXeENasv
         fsWg==
X-Gm-Message-State: AGi0PuaUgbU11JYbOy5ezOUYvM0YzExEuyJs27XFQD16J+Nu4x0szrgN
        iOIDMZNGngHq/0+ioXxhxNfoKqWT+/4=
X-Google-Smtp-Source: 
 APiQypL/DZRhoFoQ9pDr9BCiPLTpc/QN90GBu/zct7XP3cRTfRzIAiu+yKL6qnuLqz0o4IbE054wYA==
X-Received: by 2002:a63:a101:: with SMTP id b1mr16669217pgf.292.1589234450511;
        Mon, 11 May 2020 15:00:50 -0700 (PDT)
Received: from localhost ([2620:15c:202:200:c921:befc:7379:cdab])
        by smtp.gmail.com with ESMTPSA id
 a129sm10230283pfb.102.2020.05.11.15.00.49
        (version=TLS1_3 cipher=TLS_AES_128_GCM_SHA256 bits=128/128);
        Mon, 11 May 2020 15:00:49 -0700 (PDT)
From: Micah Morton <mortonm@chromium.org>
To: kvm@vger.kernel.org, pbonzini@redhat.com,
        alex.williamson@redhat.com, jmattson@google.com
Cc: Micah Morton <mortonm@chromium.org>
Subject: [RFC PATCH] KVM: Add module for IRQ forwarding
Date: Mon, 11 May 2020 15:00:46 -0700
Message-Id: <20200511220046.120206-1-mortonm@chromium.org>
X-Mailer: git-send-email 2.26.2.645.ge9eca65c58-goog
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Relevant KVM maintainers:
I'm looking for comments on the feasibility of adding a module like
this in KVM for solving the problem described below:


Currently, KVM/VFIO offers no way to forward interrupts into a guest
from devices that are implicitly assigned to the VM by nature of being
downstream from a bus controller PCI device (e.g. I2C controller) that
gets explicitly assigned to the VM. This module allows for forwarding
arbitrary interrupts on the host system into the guest, supporting this
platform-device-behind-PCI-controller scenario.

This code is mostly inspired/taken from the equivalent code in VFIO. It
is not a finished product, but I wanted to check in with the KVM mailing
list in order to assess feasibility before doing any more work on it.

One obvious question would be why not just add this support to VFIO?
See https://www.redhat.com/archives/vfio-users/2019-December/msg00008.html
and the encompassing thread for a discussion as to why this probably
isn't the way to go.

Forwarding arbitrary IRQs to a guest VM does require the VMM to "tell"
the guest about the interrupt (e.g. through ACPI), since such info is
not discoverable by the guest like it is for PCI devices. So separate
logic is needed in the VMM to set this up -- this isn't something done
by the module shared here.

Forwarding platform IRQs can have a big payoff for getting platform
devices to work in a guest, especially when the platform devices sit
behind a PCI bus controller that can be easily passed through to the
guest. On an Intel device I'm using for development, this module allowed
me to get multiple devices (keyboard, touchscreen, touchpad) working in
a VM guest on the device that wouldn't have worked otherwise -- straight
out of the box after passing through the PCI bus controller with
vfio-pci (plus constructing some AML for the guest in the VMM).

NOTE: This code works for forwarding IRQs to a guest (with the VMM
calling the appropriate ioctls with the appropriate args), although it's
missing some code and testing related to shutdown/irq disable/reboot.
Works well enough to demonstrate the feasibility though.

Developed on top of v5.7-rc4.

Signed-off-by: Micah Morton <mortonm@chromium.org>
---
 include/linux/irqfd.h           |  22 +++
 include/linux/miscdevice.h      |   1 +
 include/uapi/linux/irqforward.h |  55 ++++++
 virt/lib/Kconfig                |   3 +
 virt/lib/Makefile               |   1 +
 virt/lib/irqfd.c                | 146 ++++++++++++++++
 virt/lib/irqforward.c           | 289 ++++++++++++++++++++++++++++++++
 7 files changed, 517 insertions(+)
 create mode 100644 include/linux/irqfd.h
 create mode 100644 include/uapi/linux/irqforward.h
 create mode 100644 virt/lib/irqfd.c
 create mode 100644 virt/lib/irqforward.c

diff --git a/include/linux/irqfd.h b/include/linux/irqfd.h
new file mode 100644
index 000000000000..79d2a8c779e1
--- /dev/null
+++ b/include/linux/irqfd.h
@@ -0,0 +1,22 @@
+/*
+ * This program is free software; you can redistribute it and/or modify
+ * it under the terms of the GNU General Public License version 2 as
+ * published by the Free Software Foundation.
+ */
+#ifndef IRQFD_H
+#define IRQFD_H
+
+#include <linux/poll.h>
+
+struct irq_forward_irqfd {
+	struct eventfd_ctx	*eventfd;
+	int			(*handler)(void *, void *);
+	void			*data;
+	wait_queue_entry_t	wait;
+	poll_table		pt;
+	struct work_struct	shutdown;
+	struct irq_forward_irqfd		**pirqfd;
+};
+
+int irq_forward_irqfd_enable(int (*handler)(void *, void *), void *data, struct irq_forward_irqfd **pirqfd, int fd);
+#endif /* IRQFD_H */
```
#### [PATCH v3] KVM: nVMX: Tweak handling of failure code for nested VM-Enter failure
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11541799
Return-Path: <SRS0=C6NV=6Z=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 45B43159A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 May 2020 22:05:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2CD13206F5
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 May 2020 22:05:36 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727125AbgEKWFd (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 11 May 2020 18:05:33 -0400
Received: from mga05.intel.com ([192.55.52.43]:22436 "EHLO mga05.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725860AbgEKWFc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 11 May 2020 18:05:32 -0400
IronPort-SDR: 
 zLkLsT+bWY49JnWP2W73+wJYuJXRdEQhaQrEb3BBEKAMe5kIGdIr7a+loPLVyGzRpSlMWmFeOd
 4/Z7OWYtlv1w==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga007.fm.intel.com ([10.253.24.52])
  by fmsmga105.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 11 May 2020 15:05:31 -0700
IronPort-SDR: 
 kHqOJzJSe172729f+kh6nTCkRXgHWriwhyIPr/rKS9zHYCgli/BmF1N7ZEQmyrxM5Q82p0as6J
 sjJtVqAq/LQg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,381,1583222400";
   d="scan'208";a="251276107"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.152])
  by fmsmga007.fm.intel.com with ESMTP; 11 May 2020 15:05:30 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v3] KVM: nVMX: Tweak handling of failure code for nested
 VM-Enter failure
Date: Mon, 11 May 2020 15:05:29 -0700
Message-Id: <20200511220529.11402-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Use an enum for passing around the failure code for a failed VM-Enter
that results in VM-Exit to provide a level of indirection from the final
resting place of the failure code, vmcs.EXIT_QUALIFICATION.  The exit
qualification field is an unsigned long, e.g. passing around
'u32 exit_qual' throws up red flags as it suggests KVM may be dropping
bits when reporting errors to L1.  This is a red herring because the
only defined failure codes are 0, 2, 3, and 4, i.e. don't come remotely
close to overflowing a u32.

Setting vmcs.EXIT_QUALIFICATION on entry failure is further complicated
by the MSR load list, which returns the (1-based) entry that failed, and
the number of MSRs to load is a 32-bit VMCS field.  At first blush, it
would appear that overflowing a u32 is possible, but the number of MSRs
that can be loaded is hardcapped at 4096 (limited by MSR_IA32_VMX_MISC).

In other words, there are two completely disparate types of data that
eventually get stuffed into vmcs.EXIT_QUALIFICATION, neither of which is
an 'unsigned long' in nature.  This was presumably the reasoning for
switching to 'u32' when the related code was refactored in commit
ca0bde28f2ed6 ("kvm: nVMX: Split VMCS checks from nested_vmx_run()").

Using an enum for the failure code addresses the technically-possible-
but-will-never-happen scenario where Intel defines a failure code that
doesn't fit in a 32-bit integer.  The enum variables and values will
either be automatically sized (gcc 5.4 behavior) or be subjected to some
combination of truncation.  The former case will simply work, while the
latter will trigger a compile-time warning unless the compiler is being
particularly unhelpful.

Separating the failure code from the failed MSR entry allows for
disassociating both from vmcs.EXIT_QUALIFICATION, which avoids the
conundrum where KVM has to choose between 'u32 exit_qual' and tracking
values as 'unsigned long' that have no business being tracked as such.
To cement the split, set vmcs12->exit_qualification directly from the
entry error code or failed MSR index instead of bouncing through a local
variable.

Opportunistically rename the variables in load_vmcs12_host_state() and
vmx_set_nested_state() to call out that they're ignored, set exit_reason
on demand on nested VM-Enter failure, and add a comment in
nested_vmx_load_msr() to call out that returning 'i + 1' can't wrap.

No functional change intended.

Reported-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Cc: Jim Mattson <jmattson@google.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---

v3:
  - Set exit qual and reason in prepare_vmcs02() failure path. [kernel
    test robot]

v2:
  - Set vmcs12->exit_qualification directly to avoid writing the failed
    MSR index (a u32) to the entry_failure_code enum. [Jim]
  - Set exit_reason on demand since the "goto vm_exit" paths need to set
    vmcs12->exit_qualification anyways, i.e. already have curly braces.

 arch/x86/include/asm/vmx.h | 10 ++++----
 arch/x86/kvm/vmx/nested.c  | 47 +++++++++++++++++++++++---------------
 2 files changed, 34 insertions(+), 23 deletions(-)

```
#### [PATCH] vfio/pci: fix memory leaks of eventfd ctx
##### From: Qian Cai <cai@lca.pw>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Qian Cai <cai@lca.pw>
X-Patchwork-Id: 11539675
Return-Path: <SRS0=C6NV=6Z=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F060992A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 May 2020 04:35:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CD3522184D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 May 2020 04:35:17 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=lca.pw header.i=@lca.pw header.b="KAW6y7vm"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726528AbgEKEfB (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 11 May 2020 00:35:01 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:59966 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-FAIL-OK-FAIL)
        by vger.kernel.org with ESMTP id S1725854AbgEKEfB (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 11 May 2020 00:35:01 -0400
Received: from mail-qv1-xf43.google.com (mail-qv1-xf43.google.com
 [IPv6:2607:f8b0:4864:20::f43])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 0AF92C061A0E
        for <kvm@vger.kernel.org>; Sun, 10 May 2020 21:35:01 -0700 (PDT)
Received: by mail-qv1-xf43.google.com with SMTP id fb4so3791498qvb.7
        for <kvm@vger.kernel.org>; Sun, 10 May 2020 21:35:00 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=lca.pw; s=google;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=eAd4gbb0pcNnApGm6Og5wCWvp0yRJHJXtLCgR/gxdK4=;
        b=KAW6y7vm9lCjNEy0YAU6G7q+RuEfJEjJ0WGtTcfF5+EDnb0VUdt+EuDEMmnxAU8uuI
         6Vg7JkVSpSPv1CCUzufDIZVzUXHtCFf1UHZ45JvPn8T8NOs84T++3dXQkIG0VtvW9mAY
         2oiemNvUY9qm/uOTIy3Kg7w1rraNMNR8GsEVXJEnFU0g6iK2ov0qr8ILjlfx1jrGXavX
         PYqT/1iOUrnXjiTtFVU+eziz5YUmPIUOaXDIlyUAy+GxwFrI6rCeuun67mfiqth3ixx8
         xc1mqCVnn1+SD2CTriYUIJFRsYVJ6fCEp0wdh+uytF8zDHHLgHUv6oJx3qm1JFVJwxCZ
         v3Zw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=eAd4gbb0pcNnApGm6Og5wCWvp0yRJHJXtLCgR/gxdK4=;
        b=iXdvuLyworDtwaBx/4qI9JQc3RLntjZTHLA2VmCZGtMsqQf12gxAlpmlNq0ELGLZq/
         S3bTQNTN0YC6veYbiimQDq0X1pok1NSmqn01fYiA39Fn3GsHXVneNEBDJVlU53SfZdQK
         aEIv1tZGkelqe7d84IdUDuz5UJYmPFy+uNnFBvwerQmUKw/czlLjzUTy2bAprRjYYImt
         ueawUc9xMTfDf0X25xNLzBqcFG4gKBYjFfGkiP6rgKWm7jElNSpA7h45uDJMqs8DwYtf
         6HDudnN3pR/gn3wCdy8Mzpa80nLZ2hWFDEanvWOHg1nI8/4WOsozIiO0eYn5O0LKc2MB
         VFlw==
X-Gm-Message-State: AGi0PuaeGOMCl0EC+EiaPiCNBqWvVzq4+AJpyKAneg3Z2bQ+ZFa2xtKQ
        AqvK0juaj8EcN+ignezn5eQs5g==
X-Google-Smtp-Source: 
 APiQypLFNnKP7c/SRXW2/x9gJo9sMJpGIWsLIMrsDdA2a1mki4zFpL/KN4MNfuGlgTnwSxSkYBzbJA==
X-Received: by 2002:a0c:f70c:: with SMTP id w12mr13674265qvn.28.1589171699967;
        Sun, 10 May 2020 21:34:59 -0700 (PDT)
Received: from ovpn-112-210.rdu2.redhat.com
 (pool-71-184-117-43.bstnma.fios.verizon.net. [71.184.117.43])
        by smtp.gmail.com with ESMTPSA id
 e16sm8384451qtc.92.2020.05.10.21.34.58
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Sun, 10 May 2020 21:34:59 -0700 (PDT)
From: Qian Cai <cai@lca.pw>
To: alex.williamson@redhat.com
Cc: cohuck@redhat.com, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Qian Cai <cai@lca.pw>
Subject: [PATCH] vfio/pci: fix memory leaks of eventfd ctx
Date: Mon, 11 May 2020 00:34:50 -0400
Message-Id: <20200511043450.2718-1-cai@lca.pw>
X-Mailer: git-send-email 2.21.0 (Apple Git-122.2)
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Finished a qemu-kvm (-device vfio-pci,host=0001:01:00.0) triggers a few
memory leaks after a while because vfio_pci_set_ctx_trigger_single()
calls eventfd_ctx_fdget() without the matching eventfd_ctx_put() later.
Fix it by calling eventfd_ctx_put() for those memory in
vfio_pci_release() before vfio_device_release().

unreferenced object 0xebff008981cc2b00 (size 128):
  comm "qemu-kvm", pid 4043, jiffies 4294994816 (age 9796.310s)
  hex dump (first 32 bytes):
    01 00 00 00 6b 6b 6b 6b 00 00 00 00 ad 4e ad de  ....kkkk.....N..
    ff ff ff ff 6b 6b 6b 6b ff ff ff ff ff ff ff ff  ....kkkk........
  backtrace:
    [<00000000917e8f8d>] slab_post_alloc_hook+0x74/0x9c
    [<00000000df0f2aa2>] kmem_cache_alloc_trace+0x2b4/0x3d4
    [<000000005fcec025>] do_eventfd+0x54/0x1ac
    [<0000000082791a69>] __arm64_sys_eventfd2+0x34/0x44
    [<00000000b819758c>] do_el0_svc+0x128/0x1dc
    [<00000000b244e810>] el0_sync_handler+0xd0/0x268
    [<00000000d495ef94>] el0_sync+0x164/0x180
unreferenced object 0x29ff008981cc4180 (size 128):
  comm "qemu-kvm", pid 4043, jiffies 4294994818 (age 9796.290s)
  hex dump (first 32 bytes):
    01 00 00 00 6b 6b 6b 6b 00 00 00 00 ad 4e ad de  ....kkkk.....N..
    ff ff ff ff 6b 6b 6b 6b ff ff ff ff ff ff ff ff  ....kkkk........
  backtrace:
    [<00000000917e8f8d>] slab_post_alloc_hook+0x74/0x9c
    [<00000000df0f2aa2>] kmem_cache_alloc_trace+0x2b4/0x3d4
    [<000000005fcec025>] do_eventfd+0x54/0x1ac
    [<0000000082791a69>] __arm64_sys_eventfd2+0x34/0x44
    [<00000000b819758c>] do_el0_svc+0x128/0x1dc
    [<00000000b244e810>] el0_sync_handler+0xd0/0x268
    [<00000000d495ef94>] el0_sync+0x164/0x180

Signed-off-by: Qian Cai <cai@lca.pw>
---
 drivers/vfio/pci/vfio_pci.c | 4 ++++
 1 file changed, 4 insertions(+)

```
#### [PATCH] vhost: scsi: notify TCM about the maximum sg entries supported per command.
##### From: Sudhakar Panneerselvam <sudhakar.panneerselvam@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sudhakar Panneerselvam
 <sudhakar.panneerselvam@oracle.com>
X-Patchwork-Id: 11541803
Return-Path: <SRS0=C6NV=6Z=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id ABEA715AB
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 May 2020 22:19:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 92EC420736
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 May 2020 22:19:07 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="i4/9+jpI"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725881AbgEKWTG (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 11 May 2020 18:19:06 -0400
Received: from userp2130.oracle.com ([156.151.31.86]:52060 "EHLO
        userp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725836AbgEKWTG (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 11 May 2020 18:19:06 -0400
Received: from pps.filterd (userp2130.oracle.com [127.0.0.1])
        by userp2130.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 04BMCeEX016297;
        Mon, 11 May 2020 22:19:01 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id; s=corp-2020-01-29;
 bh=0udyAlAcqwN6BbJGZkL7OUkK/UgYraR4SM77vi3XkY0=;
 b=i4/9+jpI3Bc33iUu2umOMfn7A+vt6Q9kp/VzA8Ft9Y0Fdsv9f2ow77rM+1eYyn4YxzP2
 7pBi8uTtLSTL5lU5SBoUKzTIU8bwySaN7JODfT7E0kRKcVIVAcmOVLq06dObMsgFg/Ym
 Y2cqjeKDy33Vd0oCU/NNFiAfGouGrQ4ZEX6h9YLYLoexCbPwMWiE9tJFokoDZvaxe6XN
 b01m0SKOxoMAIwbkSTKaFnLzmZq7Ja9p5QFfhIdKaaCQhcClscKGJeTJazuGa+aux1Pm
 q+qT5ZGPOmdxCbwC1BIdrLVb4zxEjLmUnrP3ZR4EU9bQopiwJVxQymn18KlT6VWxbRxn yg==
Received: from aserp3020.oracle.com (aserp3020.oracle.com [141.146.126.70])
        by userp2130.oracle.com with ESMTP id 30x3gmftg9-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=FAIL);
        Mon, 11 May 2020 22:19:01 +0000
Received: from pps.filterd (aserp3020.oracle.com [127.0.0.1])
        by aserp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 04BMIVK8089743;
        Mon, 11 May 2020 22:19:00 GMT
Received: from aserv0122.oracle.com (aserv0122.oracle.com [141.146.126.236])
        by aserp3020.oracle.com with ESMTP id 30xbgfxdc4-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 11 May 2020 22:19:00 +0000
Received: from abhmp0014.oracle.com (abhmp0014.oracle.com [141.146.116.20])
        by aserv0122.oracle.com (8.14.4/8.14.4) with ESMTP id 04BMJ0iS018952;
        Mon, 11 May 2020 22:19:00 GMT
Received: from supannee-devvm-ol7.osdevelopmeniad.oraclevcn.com
 (/100.100.231.179)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Mon, 11 May 2020 15:19:00 -0700
From: Sudhakar Panneerselvam <sudhakar.panneerselvam@oracle.com>
To: mst@redhat.com, jasowang@redhat.com, pbonzini@redhat.com,
        stefanha@redhat.com
Cc: virtualization@lists.linux-foundation.org, kvm@vger.kernel.org,
        Sudhakar Panneerselvam <sudhakar.panneerselvam@oracle.com>
Subject: [PATCH] vhost: scsi: notify TCM about the maximum sg entries
 supported per command.
Date: Mon, 11 May 2020 22:18:52 +0000
Message-Id: 
 <1589235532-10333-1-git-send-email-sudhakar.panneerselvam@oracle.com>
X-Mailer: git-send-email 1.8.3.1
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9618
 signatures=668687
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 adultscore=0
 mlxlogscore=999
 spamscore=0 suspectscore=0 phishscore=0 bulkscore=0 mlxscore=0
 malwarescore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2003020000 definitions=main-2005110166
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9618
 signatures=668687
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 adultscore=0
 mlxlogscore=999
 clxscore=1011 spamscore=0 lowpriorityscore=0 phishscore=0 bulkscore=0
 malwarescore=0 priorityscore=1501 mlxscore=0 suspectscore=0
 impostorscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2003020000 definitions=main-2005110165
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

vhost-scsi pre-allocates the maximum sg entries per command and if a
command requires more than VHOST_SCSI_PREALLOC_SGLS entries, then that
command is failed by it. This patch lets vhost communicate the max sg limit
when it registers vhost_scsi_ops with TCM. With this change, TCM would
report the max sg entries through "Block Limits" VPD page which will be
typically queried by the SCSI initiator during device discovery. By knowing
this limit, the initiator could ensure the maximum transfer length is less
than or equal to what is reported by vhost-scsi.

Signed-off-by: Sudhakar Panneerselvam <sudhakar.panneerselvam@oracle.com>
---
 drivers/vhost/scsi.c | 1 +
 1 file changed, 1 insertion(+)

```
