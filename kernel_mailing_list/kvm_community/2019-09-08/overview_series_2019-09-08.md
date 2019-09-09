#### [RFC PATCH untested] vhost: block speculation of translated descriptors
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 11136907
Return-Path: <SRS0=veOC=XD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8033E13BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun,  8 Sep 2019 11:05:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 68FB5207FC
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun,  8 Sep 2019 11:05:46 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728757AbfIHLFp (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 8 Sep 2019 07:05:45 -0400
Received: from mx1.redhat.com ([209.132.183.28]:34288 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728747AbfIHLFp (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 8 Sep 2019 07:05:45 -0400
Received: from mail-qk1-f200.google.com (mail-qk1-f200.google.com
 [209.85.222.200])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-GCM-SHA256 (128/128 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id A79CE81DF7
        for <kvm@vger.kernel.org>; Sun,  8 Sep 2019 11:05:44 +0000 (UTC)
Received: by mail-qk1-f200.google.com with SMTP id q62so12691854qkd.3
        for <kvm@vger.kernel.org>; Sun, 08 Sep 2019 04:05:44 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:mime-version
         :content-disposition;
        bh=mJ79VyQiPMiGxBu7/NgWOAdwnTdH8zf8E/dxV83oJIQ=;
        b=sFxTE4NFquMN4NTjp+8/Rjy0v5KJbI3GqZ1Q/4ewHtfZgRzYiJH2WcsfvjJfj4ugTr
         Y1yjqVvCs7+5UvRXIOfjqJZ8iGcODWpvA/6KYc4Ge/voZOawZvLxAbInrYuXhuTJdrJx
         IdlS5gp1SE84t0cb0mBqh4MkIKmZrHW0cWfkKq5GWxrSAGunZHULeCQhAyavdB0V6VbT
         ORQdPZ6JzMNJN1jWC9E+TUbi06NKexz9YA1mqAuBtdokZGXLGwQFfniSfHJhic8w9oGZ
         Vlj9xi0np7Y8Hl20jHZg+uuPG9cH/qZC66nWTTknrVCOhj2F80wCrk5btis4jnn1ODna
         a5kw==
X-Gm-Message-State: APjAAAUnVDb74NMkkV81YzkkPkGtB6fqpJ1/jATLf310cj9UY3xBLOzn
        uQUOJIOmLBkLvYr/Ir5rJ0iAOvPLicaopoPFPMeGm7ZCZJ9ey/zdIsgG6aK1fbkj3gALVv8uzl0
        LMKunsYUyYgbV
X-Received: by 2002:ac8:845:: with SMTP id x5mr18054486qth.42.1567940744063;
        Sun, 08 Sep 2019 04:05:44 -0700 (PDT)
X-Google-Smtp-Source: 
 APXvYqzWSBaHX6xbj2IMf12T1d2jOLe4XYAW+o7heTvxil6hRKkUH9dOz/sVHUORF99wcOY9BFlSSQ==
X-Received: by 2002:ac8:845:: with SMTP id x5mr18054478qth.42.1567940743938;
        Sun, 08 Sep 2019 04:05:43 -0700 (PDT)
Received: from redhat.com ([212.92.124.241])
        by smtp.gmail.com with ESMTPSA id
 139sm5217532qkf.14.2019.09.08.04.05.41
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Sun, 08 Sep 2019 04:05:43 -0700 (PDT)
Date: Sun, 8 Sep 2019 07:05:39 -0400
From: "Michael S. Tsirkin" <mst@redhat.com>
To: linux-kernel@vger.kernel.org
Cc: Jason Wang <jasowang@redhat.com>, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org
Subject: [RFC PATCH untested] vhost: block speculation of translated
 descriptors
Message-ID: <20190908110521.4031-1-mst@redhat.com>
MIME-Version: 1.0
Content-Type: text/plain; charset=us-ascii
Content-Disposition: inline
X-Mailer: git-send-email 2.22.0.678.g13338e74b8
X-Mutt-Fcc: =sent
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

iovec addresses coming from vhost are assumed to be
pre-validated, but in fact can be speculated to a value
out of range.

Userspace address are later validated with array_index_nospec so we can
be sure kernel info does not leak through these addresses, but vhost
must also not leak userspace info outside the allowed memory table to
guests.

Following the defence in depth principle, make sure
the address is not validated out of node range.

Signed-off-by: Michael S. Tsirkin <mst@redhat.com>
---
 drivers/vhost/vhost.c | 4 +++-
 1 file changed, 3 insertions(+), 1 deletion(-)

```
