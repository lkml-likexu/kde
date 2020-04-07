#### [PATCH v2 2/2] vhost: disable for OABI
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 11475473
Return-Path: <SRS0=xvKj=5W=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 66AD4112C
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  6 Apr 2020 12:12:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 3BE5721835
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  6 Apr 2020 12:12:58 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="FL/Hz1sY"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727968AbgDFMMy (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 6 Apr 2020 08:12:54 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:36671 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1727931AbgDFMMw (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 6 Apr 2020 08:12:52 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1586175170;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         in-reply-to:in-reply-to:references:references;
        bh=dQAEJjJ23njMAMzpYV3TzkQNiOgjGmbglBN46bPRZ/k=;
        b=FL/Hz1sYb5fZql6/Fw1IbPDUj7GjcUk7wl/0uMI2lk4fOixhHzpKkZK0i5ieH4xOiRtKBD
        gWUrnf6ZODujrN0nUvj/XI1mbagBckJ6MEzSTpk3t5OvMFZ8gSTReAruTMljcPYAr5pKoj
        mgBhuh41G9opgLqiFR5EQRpVqfu9YWY=
Received: from mail-wr1-f69.google.com (mail-wr1-f69.google.com
 [209.85.221.69]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-504-CAmUjOQcOLS9IGvvteZaAA-1; Mon, 06 Apr 2020 08:12:49 -0400
X-MC-Unique: CAmUjOQcOLS9IGvvteZaAA-1
Received: by mail-wr1-f69.google.com with SMTP id v14so8271276wrq.13
        for <kvm@vger.kernel.org>; Mon, 06 Apr 2020 05:12:48 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:references
         :mime-version:content-disposition:in-reply-to;
        bh=dQAEJjJ23njMAMzpYV3TzkQNiOgjGmbglBN46bPRZ/k=;
        b=ZwrEAOqRT8Ga1zrjN/Z2YONLMh4mn2mpxFPCRVLvEER+UC3OiTj8XsKX/MJqnespEy
         1//TndlEo3xWeZFsU862Ikv3a8siZEyihLp5VeabpVVg5ZsEzFW6guEw03hulAAOIZLM
         TCW4a6nrT8hlbX8E16UOSYc/BgqX6IAKy01eeWrCp+FD0xmmxWmxfoiRYnxUbfCD6Q6S
         iFogV+0xKOh4jUIYV/F+kEr/iUe7MOnF2uuKY/U92Bt2tIPsmZ0MEZ8LWmei0fnZKygi
         PwEdUIttxYi6CjGhvRuAHh75Zw/ZLH4T0zyOBSuv5frJOCQXZVjR20+TB080yYBiMWbZ
         5NlA==
X-Gm-Message-State: AGi0PuZy9cBQcNAuEpcrfPr7PUazdlXZdMYjLd4W3fgjcGgaFzXFbF7z
        K8MklpFjIeWY6F4jAklshmQ6Odxaa/MI66vXfDaKVMujBfJ/QsRY4FAoHr2jz3d+YKcQsK9rySD
        xiKufAwaskow6
X-Received: by 2002:adf:bc12:: with SMTP id
 s18mr25165005wrg.220.1586175167830;
        Mon, 06 Apr 2020 05:12:47 -0700 (PDT)
X-Google-Smtp-Source: 
 APiQypLwgTks29i/561QCQdpKOflCqiUKEhbZa/gBiQmA5aq0hS0WhmnIdFdpGtSrxr+GiRrPLsSEg==
X-Received: by 2002:adf:bc12:: with SMTP id
 s18mr25164995wrg.220.1586175167620;
        Mon, 06 Apr 2020 05:12:47 -0700 (PDT)
Received: from redhat.com (bzq-79-176-51-222.red.bezeqint.net.
 [79.176.51.222])
        by smtp.gmail.com with ESMTPSA id
 c20sm11334886wmd.36.2020.04.06.05.12.45
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 06 Apr 2020 05:12:47 -0700 (PDT)
Date: Mon, 6 Apr 2020 08:12:44 -0400
From: "Michael S. Tsirkin" <mst@redhat.com>
To: linux-kernel@vger.kernel.org
Cc: Ard Biesheuvel <ardb@kernel.org>,
        "richard.henderson@linaro.org" <richard.henderson@linaro.org>,
        "christophe.lyon@st.com" <christophe.lyon@st.com>,
        kbuild test robot <lkp@intel.com>,
        "daniel.santos@pobox.com" <daniel.santos@pobox.com>,
        Jason Wang <jasowang@redhat.com>,
        "kbuild-all@lists.01.org" <kbuild-all@lists.01.org>,
        Russell King <rmk+kernel@armlinux.org.uk>,
        Linux ARM <linux-arm-kernel@lists.infradead.org>,
        Richard Earnshaw <Richard.Earnshaw@arm.com>,
        Sudeep Dutt <sudeep.dutt@intel.com>,
        Ashutosh Dixit <ashutosh.dixit@intel.com>,
        Arnd Bergmann <arnd@arndb.de>,
        Greg Kroah-Hartman <gregkh@linuxfoundation.org>,
        "David S. Miller" <davem@davemloft.net>, netdev@vger.kernel.org,
        virtualization@lists.linux-foundation.org, kvm@vger.kernel.org
Subject: [PATCH v2 2/2] vhost: disable for OABI
Message-ID: <20200406121233.109889-3-mst@redhat.com>
References: <20200406121233.109889-1-mst@redhat.com>
MIME-Version: 1.0
Content-Disposition: inline
In-Reply-To: <20200406121233.109889-1-mst@redhat.com>
X-Mailer: git-send-email 2.24.1.751.gd10ce2899c
X-Mutt-Fcc: =sent
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

vhost is currently broken on the default ARM config.

The reason is that that uses apcs-gnu which is the ancient OABI that is been
deprecated for a long time.

Given that virtio support on such ancient systems is not needed in the
first place, let's just add something along the lines of

	depends on !ARM || AEABI

to the virtio Kconfig declaration, and add a comment that it has to do
with struct member alignment.

Note: we can't make VHOST and VHOST_RING themselves have
a dependency since these are selected. Add a new symbol for that.

Suggested-by: Ard Biesheuvel <ardb@kernel.org>
Siggested-by: Richard Earnshaw <Richard.Earnshaw@arm.com>
Signed-off-by: Michael S. Tsirkin <mst@redhat.com>
---
 drivers/misc/mic/Kconfig |  2 +-
 drivers/net/caif/Kconfig |  2 +-
 drivers/vdpa/Kconfig     |  2 +-
 drivers/vhost/Kconfig    | 17 +++++++++++++----
 4 files changed, 16 insertions(+), 7 deletions(-)

```
