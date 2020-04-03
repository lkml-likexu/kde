#### [kvm-unit-tests PATCH v4 01/12] arm64: Provide read/write_sysreg_s
##### From: Eric Auger <eric.auger@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Auger Eric <eric.auger@redhat.com>
X-Patchwork-Id: 11471939
Return-Path: <SRS0=Xk8+=5T=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5FD2B92A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Apr 2020 07:13:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 3352920CC7
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Apr 2020 07:13:45 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="AmaEZl22"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2389104AbgDCHNo (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 3 Apr 2020 03:13:44 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:24733 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S2388959AbgDCHNn (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 3 Apr 2020 03:13:43 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1585898022;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=5QgGQR5lmCzHdU2tw8u26Dp0LVz138MaKuXfv7AyzLc=;
        b=AmaEZl22Q6IctKMMzB+rgc+I1AJAJjjmCPvgwSxYbp1F/7g70ROC+W/WgheZZZrnrpsD0w
        HJn3BGdNJ6XD6i09ZsLqX/OtUMQi7+MlinhASqRimz9VP1UZJhENS/jSWEkmmxfjHB/SX3
        jhSyQK9eZihjj2v+7n0051UbQpd95Rc=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-246-6uK3z0ZZOhS9hY4FytW9qg-1; Fri, 03 Apr 2020 03:13:40 -0400
X-MC-Unique: 6uK3z0ZZOhS9hY4FytW9qg-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id D63AF107ACC4;
        Fri,  3 Apr 2020 07:13:38 +0000 (UTC)
Received: from laptop.redhat.com (ovpn-112-58.ams2.redhat.com [10.36.112.58])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 1D68C5C1C6;
        Fri,  3 Apr 2020 07:13:35 +0000 (UTC)
From: Eric Auger <eric.auger@redhat.com>
To: eric.auger.pro@gmail.com, eric.auger@redhat.com, maz@kernel.org,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        qemu-devel@nongnu.org, qemu-arm@nongnu.org
Cc: drjones@redhat.com, andrew.murray@arm.com, andre.przywara@arm.com,
        peter.maydell@linaro.org, alexandru.elisei@arm.com
Subject: [kvm-unit-tests PATCH v4 01/12] arm64: Provide read/write_sysreg_s
Date: Fri,  3 Apr 2020 09:13:15 +0200
Message-Id: <20200403071326.29932-2-eric.auger@redhat.com>
In-Reply-To: <20200403071326.29932-1-eric.auger@redhat.com>
References: <20200403071326.29932-1-eric.auger@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
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
