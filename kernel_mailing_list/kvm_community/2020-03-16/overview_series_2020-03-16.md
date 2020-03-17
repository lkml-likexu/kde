#### [PATCH 1/2] fixup! KVM: selftests: Introduce steal-time test
##### From: Andrew Jones <drjones@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11440185
Return-Path: <SRS0=tnJv=5B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CD85514E5
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 16 Mar 2020 11:01:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id AE55020724
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 16 Mar 2020 11:01:54 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="iNZdO54L"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730766AbgCPLBx (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 16 Mar 2020 07:01:53 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:28403 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1730761AbgCPLBx (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 16 Mar 2020 07:01:53 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1584356512;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=ViKxMbqsfCIjJmn/ueBPsXB6IQB265H3nN3VLpBkljw=;
        b=iNZdO54LchTQsdiIggnFlgEXU9OIW+6EQQSm9Bsap4b8lXCc6BS/ITELtILgFsEO35FknC
        zT0mTz/o3DJ0VkJpphQQgIc4m6lHKiNv1kMXbcdV4IyR29FKxqa0uu0PVmHPYu4WBZgrdM
        0mi5quqAd7jf/oncLco/igfyEQAYB8w=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-243-xDXaXnaLOziUILr8CtTw-w-1; Mon, 16 Mar 2020 07:01:45 -0400
X-MC-Unique: xDXaXnaLOziUILr8CtTw-w-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 77F50192D79F
        for <kvm@vger.kernel.org>; Mon, 16 Mar 2020 11:01:44 +0000 (UTC)
Received: from kamzik.brq.redhat.com (ovpn-204-240.brq.redhat.com
 [10.40.204.240])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 347C35E242;
        Mon, 16 Mar 2020 11:01:39 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com
Subject: [PATCH 1/2] fixup! KVM: selftests: Introduce steal-time test
Date: Mon, 16 Mar 2020 12:01:35 +0100
Message-Id: <20200316110136.31326-2-drjones@redhat.com>
In-Reply-To: <20200316110136.31326-1-drjones@redhat.com>
References: <20200316110136.31326-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Change the pr_info's to printf's as they're already guarded by verbose,
so shouldn't be dependent on QUIET. Also remove a pointless TEST_ASSERT.

Signed-off-by: Andrew Jones <drjones@redhat.com>
---
 tools/testing/selftests/kvm/steal_time.c | 37 +++++++++++-------------
 1 file changed, 17 insertions(+), 20 deletions(-)

```
#### [PATCH v2 1/2] fixup! KVM: selftests: Introduce steal-time test
##### From: Andrew Jones <drjones@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11441047
Return-Path: <SRS0=tnJv=5B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A001213B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 16 Mar 2020 18:01:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7FC6720658
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 16 Mar 2020 18:01:04 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="PCKFXvny"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732252AbgCPSBD (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 16 Mar 2020 14:01:03 -0400
Received: from us-smtp-delivery-74.mimecast.com ([216.205.24.74]:22159 "EHLO
        us-smtp-delivery-74.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1730437AbgCPSBD (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 16 Mar 2020 14:01:03 -0400
X-Greylist: delayed 331 seconds by postgrey-1.27 at vger.kernel.org;
 Mon, 16 Mar 2020 14:01:02 EDT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1584381662;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=ViKxMbqsfCIjJmn/ueBPsXB6IQB265H3nN3VLpBkljw=;
        b=PCKFXvnyvj9mTgKcrNv2svM8CFyOjmmzCBfbqIhd8NNetl2/ToEbpKMaY8486doUwaJUo/
        z9wKaqaoFUmtDLdn0rz4vcNxp6gOgSx76zOjHt9l86rSfFqjUM0k8/7n3h6oKh0f24dli2
        r2ejaUeWYbHnVSDIvLxQRRgl4+QRzbk=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-84-ZCxCI5JyPqKtJ6_kXspjgA-1; Mon, 16 Mar 2020 13:52:54 -0400
X-MC-Unique: ZCxCI5JyPqKtJ6_kXspjgA-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id CF594925064
        for <kvm@vger.kernel.org>; Mon, 16 Mar 2020 17:37:13 +0000 (UTC)
Received: from kamzik.brq.redhat.com (ovpn-204-240.brq.redhat.com
 [10.40.204.240])
        by smtp.corp.redhat.com (Postfix) with ESMTP id C44837E300;
        Mon, 16 Mar 2020 17:37:12 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com
Subject: [PATCH v2 1/2] fixup! KVM: selftests: Introduce steal-time test
Date: Mon, 16 Mar 2020 18:37:02 +0100
Message-Id: <20200316173703.12785-2-drjones@redhat.com>
In-Reply-To: <20200316173703.12785-1-drjones@redhat.com>
References: <20200316173703.12785-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Change the pr_info's to printf's as they're already guarded by verbose,
so shouldn't be dependent on QUIET. Also remove a pointless TEST_ASSERT.

Signed-off-by: Andrew Jones <drjones@redhat.com>
---
 tools/testing/selftests/kvm/steal_time.c | 37 +++++++++++-------------
 1 file changed, 17 insertions(+), 20 deletions(-)

```
#### [PATCH v3 01/19] target/arm: Rename KVM set_feature() as kvm_set_feature()
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
 <philmd@redhat.com>
X-Patchwork-Id: 11440699
Return-Path: <SRS0=tnJv=5B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6C38114E5
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 16 Mar 2020 16:18:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4C3F820719
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 16 Mar 2020 16:18:42 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="ZyxYnznZ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732005AbgCPQSk (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 16 Mar 2020 12:18:40 -0400
Received: from us-smtp-delivery-74.mimecast.com ([63.128.21.74]:30854 "EHLO
        us-smtp-delivery-74.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1731545AbgCPQSj (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 16 Mar 2020 12:18:39 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1584375518;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
  content-type:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=WUQmK3jX+ITRgjT53gJOYB77qbIWiqXEgYr8J8FbjTA=;
        b=ZyxYnznZFFpwgBIrvnEqFnHvPDDy5LxYF/LBIMfhNjAATkXGrnZ4BRJXAyeghwRXmliayO
        yynP63D8i4L4TOXPfQRDZ9tSc5XPA0xfMRn0Q9l0iivXZr5oRRnlTe7P54AGXXrXbeY/FK
        7YHRq4LEb4CH/bmfAnxtLEdbt0i3pAQ=
Received: from mail-wr1-f69.google.com (mail-wr1-f69.google.com
 [209.85.221.69]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-139-8fK9p7SXPHKMlaIwDbeE-w-1; Mon, 16 Mar 2020 12:06:45 -0400
X-MC-Unique: 8fK9p7SXPHKMlaIwDbeE-w-1
Received: by mail-wr1-f69.google.com with SMTP id w11so9253211wrp.20
        for <kvm@vger.kernel.org>; Mon, 16 Mar 2020 09:06:44 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=WUQmK3jX+ITRgjT53gJOYB77qbIWiqXEgYr8J8FbjTA=;
        b=qJN0epzUfboFFZAZdVODeqvnhgFgOcI/6odg5TAL+1+1ueS2a5LlA9ruG6TPXIYFq+
         d5qooN85LMszAm+upWjA8Omtd5T7aPm5aItOJ/KmRDWEW6HPBxIs+ExD8WuC1dSBeYEH
         tmg9lX0jqaIETJcbE7bU5z3Gr8uzqw+u236p6+UkXtFT+59ow90wG/C9YB7Yt2KBAsbN
         l98uoRnU9YOst1njAG2d5T58wIQ1NimXAAUXvtFM1NM3OL16SRCdSnwFQU9CTeQc1Tnl
         kEcIVNY2A2S3jMzKFPjKR1cYczWj5wGn2+yD8jXCGEdddzE7Ztr2rr/tG7wX2qUeGwMl
         Uq0Q==
X-Gm-Message-State: ANhLgQ2BlHpf4c0rEkg+dtmwvRu6+QdiRpB0KieQ7tglxuFeAKQOGK0P
        KPl68p4dow+zXEb+3FwIcN+3zE0HfyRIjzI5/9OZJsPJLA5fw52EiIvj4mEIDwbWEyeGeBfC70S
        wT0nzXiW9TgtY
X-Received: by 2002:a1c:ab04:: with SMTP id u4mr28378905wme.88.1584374803976;
        Mon, 16 Mar 2020 09:06:43 -0700 (PDT)
X-Google-Smtp-Source: 
 ADFU+vtV0XnwGOD9HZ+gDhSELi6gG1sO2wgoMuiEbFWxHuGz29Lw9cyiUjcbAj92lhznjafti4kUQw==
X-Received: by 2002:a1c:ab04:: with SMTP id u4mr28378818wme.88.1584374802766;
        Mon, 16 Mar 2020 09:06:42 -0700 (PDT)
Received: from localhost.localdomain (96.red-83-59-163.dynamicip.rima-tde.net.
 [83.59.163.96])
        by smtp.gmail.com with ESMTPSA id
 a10sm480884wrv.89.2020.03.16.09.06.41
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 16 Mar 2020 09:06:42 -0700 (PDT)
From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>
To: qemu-devel@nongnu.org
Cc: =?utf-8?q?Alex_Benn=C3=A9e?= <alex.bennee@linaro.org>,
 kvm@vger.kernel.org, Thomas Huth <thuth@redhat.com>, qemu-arm@nongnu.org,
 Fam Zheng <fam@euphon.net>,
 =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>,
 Paolo Bonzini <pbonzini@redhat.com>,
 Peter Maydell <peter.maydell@linaro.org>,
 Richard Henderson <richard.henderson@linaro.org>
Subject: [PATCH v3 01/19] target/arm: Rename KVM set_feature() as
 kvm_set_feature()
Date: Mon, 16 Mar 2020 17:06:16 +0100
Message-Id: <20200316160634.3386-2-philmd@redhat.com>
X-Mailer: git-send-email 2.21.1
In-Reply-To: <20200316160634.3386-1-philmd@redhat.com>
References: <20200316160634.3386-1-philmd@redhat.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Signed-off-by: Philippe Mathieu-Daudé <philmd@redhat.com>
---
 target/arm/kvm32.c | 10 +++++-----
 target/arm/kvm64.c | 16 ++++++++--------
 2 files changed, 13 insertions(+), 13 deletions(-)

```
