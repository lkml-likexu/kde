#### [PATCH 13/13] samples: vfio-mdev: constify fb ops
##### From: Jani Nikula <jani.nikula@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jani Nikula <jani.nikula@intel.com>
X-Patchwork-Id: 11264511
Return-Path: <SRS0=T3S3=ZT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7D18915AB
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 27 Nov 2019 16:34:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 6780F204FD
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 27 Nov 2019 16:34:07 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727120AbfK0QeG (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 27 Nov 2019 11:34:06 -0500
Received: from mga12.intel.com ([192.55.52.136]:5329 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726514AbfK0QeG (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 27 Nov 2019 11:34:06 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga003.fm.intel.com ([10.253.24.29])
  by fmsmga106.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 27 Nov 2019 08:33:49 -0800
X-IronPort-AV: E=Sophos;i="5.69,250,1571727600";
   d="scan'208";a="261045075"
Received: from jnikula-mobl3.fi.intel.com (HELO localhost) ([10.237.66.161])
  by fmsmga003-auth.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 27 Nov 2019 08:33:47 -0800
From: Jani Nikula <jani.nikula@intel.com>
To: linux-fbdev@vger.kernel.org, dri-devel@lists.freedesktop.org
Cc: ville.syrjala@linux.intel.com, intel-gfx@lists.freedesktop.org,
        jani.nikula@intel.com, Kirti Wankhede <kwankhede@nvidia.com>,
        kvm@vger.kernel.org
Subject: [PATCH 13/13] samples: vfio-mdev: constify fb ops
Date: Wed, 27 Nov 2019 18:32:09 +0200
Message-Id: 
 <fc8342eef9fcd2f55c86fcd78f7df52f7c76fa87.1574871797.git.jani.nikula@intel.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <cover.1574871797.git.jani.nikula@intel.com>
References: <cover.1574871797.git.jani.nikula@intel.com>
MIME-Version: 1.0
Organization: Intel Finland Oy - BIC 0357606-4 - Westendinkatu 7, 02160 Espoo
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Now that the fbops member of struct fb_info is const, we can star making
the ops const as well.

Cc: Kirti Wankhede <kwankhede@nvidia.com>
Cc: kvm@vger.kernel.org
Signed-off-by: Jani Nikula <jani.nikula@intel.com>
Reviewed-by: Daniel Vetter <daniel.vetter@ffwll.ch>
---
 samples/vfio-mdev/mdpy-fb.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] KVM: SVM: Fix "error" isn't initialized
##### From: Haiwei Li <lihaiwei.kernel@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Haiwei Li <lihaiwei.kernel@gmail.com>
X-Patchwork-Id: 11263353
Return-Path: <SRS0=T3S3=ZT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F42191390
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 27 Nov 2019 03:05:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D210D2075C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 27 Nov 2019 03:05:45 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="Pfm4Jbgb"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726655AbfK0DFl (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 26 Nov 2019 22:05:41 -0500
Received: from mail-pj1-f67.google.com ([209.85.216.67]:40881 "EHLO
        mail-pj1-f67.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726304AbfK0DFl (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 26 Nov 2019 22:05:41 -0500
Received: by mail-pj1-f67.google.com with SMTP id ep1so9249123pjb.7;
        Tue, 26 Nov 2019 19:05:40 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=to:cc:from:subject:message-id:date:user-agent:mime-version
         :content-language:content-transfer-encoding;
        bh=i34ebQ7c/s5886cOtfqmhdiKMr1NWUArCMVccSTOyxU=;
        b=Pfm4JbgbDK8Hg8YjSkmdCPGylzWp994a1QuRB61z+ZK0BmYqGgYlLY1KUekaYs2Djd
         4gZozuSsPwNNcNh47tXjoMMX0AvaRYVmz510JslIjS2LGIV6UcEDvkueNR6zfTwM5cag
         FrVXMdyOlub4ccCM3B0pjz9I8GBwKYjslxy27Cye6AClqADDkd0aoLMXUFcEtA6H2XiM
         maqHJMuK+xbdkGg1NY+zo0od8Kcb88H0DTLtXeBwPHOnhin64DRbii6/6IygZEUNaEsi
         WH/9+af1phMZGFeU8dhsPDw8DG8EJH5uqDZ9gqehpJ5I/dZE56vKw5QQSHkqZk6vWcbU
         dehg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:to:cc:from:subject:message-id:date:user-agent
         :mime-version:content-language:content-transfer-encoding;
        bh=i34ebQ7c/s5886cOtfqmhdiKMr1NWUArCMVccSTOyxU=;
        b=UDh4XxFVYLZvFvkDECZpfLN75J4RVUO2+9J/51pFFqeXJ2WLaGvGreI0hjoCMW51Ga
         /rdg/EJNRBjITc2sCk/tUZMpWyDIUB5eznYKPcWp9C+Io6lx7UECwLOfYdLD49S/N8nn
         ax7LrA3ZsAa2YJrAzjrvoB+DkCMOGvVWxPCUknTHMvL5XPKp3YiF9S8hpr5mZKM5fE5e
         225kFqj3bU8Cwd65RrCyrBI2mMI6Rjy82v8vNcISmr+cPzWywyukJZyykYet5KYTeAn1
         T0KCD0rs2odZXbksQQ4cryp04VF541Dm6B+W9zg+KdgIMeocJ1pgg9W8dZ0B07+Iavkl
         eoFw==
X-Gm-Message-State: APjAAAWMkFBSEiX/vL1SM5Wait4AUmvyLJshZkhgOvRGw4uZiWHdI5zM
        mwr23zr+a40QQcezAVCnbA==
X-Google-Smtp-Source: 
 APXvYqwkqFrtKPql4uSZmaiVCUopiUt+Vc/mcofIk3c8sjgtYAEWiAqNAIZKx7yR75jVY9qqGm95nA==
X-Received: by 2002:a17:90a:2c1:: with SMTP id
 d1mr2925498pjd.137.1574823940271;
        Tue, 26 Nov 2019 19:05:40 -0800 (PST)
Received: from [10.72.166.40] ([203.205.141.123])
        by smtp.gmail.com with ESMTPSA id
 x4sm3841439pgg.61.2019.11.26.19.05.36
        (version=TLS1_3 cipher=TLS_AES_128_GCM_SHA256 bits=128/128);
        Tue, 26 Nov 2019 19:05:39 -0800 (PST)
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org, x86@kernel.org
Cc: pbonzini@redhat.com, rkrcmar@redhat.com,
        sean.j.christopherson@intel.com, vkuznets@redhat.com,
        wanpengli@tencent.com, jmattson@google.com, joro@8bytes.org,
        tglx@linutronix.de, mingo@redhat.com, bp@alien8.de, hpa@zytor.com
From: Haiwei Li <lihaiwei.kernel@gmail.com>
Subject: [PATCH] KVM: SVM: Fix "error" isn't initialized
Message-ID: <f0bac432-ad0f-8d6a-eb92-6135f68d16d6@gmail.com>
Date: Wed, 27 Nov 2019 11:05:30 +0800
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:68.0)
 Gecko/20100101 Thunderbird/68.2.2
MIME-Version: 1.0
Content-Language: en-US
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From d32ebcf6f426385942fe6c469255e73188cd7d38 Mon Sep 17 00:00:00 2001
From: Haiwei Li <lihaiwei@tencent.com>
Date: Wed, 27 Nov 2019 11:03:21 +0800
Subject: [PATCH] initialize 'error'

There are a bunch of error paths were "error" isn't initialized.

Signed-off-by: Haiwei Li <lihaiwei@tencent.com>
Reported-by: Dan Carpenter <dan.carpenter@oracle.com>
---
  arch/x86/kvm/svm.c | 3 ++-
  1 file changed, 2 insertions(+), 1 deletion(-)

--
1.8.3.1

```
#### [PATCH] kvm/x86: export kvm_vector_hashing_enabled() is unnecessary
##### From: Peng Hao <richard.peng@oppo.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peng Hao <richard.peng@oppo.com>
X-Patchwork-Id: 11263161
Return-Path: <SRS0=T3S3=ZT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0BBF013A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 27 Nov 2019 00:30:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E74AC2075C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 27 Nov 2019 00:30:33 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727008AbfK0Aaa (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 26 Nov 2019 19:30:30 -0500
Received: from m17618.mail.qiye.163.com ([59.111.176.18]:19773 "EHLO
        m17618.mail.qiye.163.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726701AbfK0Aaa (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 26 Nov 2019 19:30:30 -0500
Received: from localhost.localdomain.localdomain (unknown [121.12.147.250])
        by m17618.mail.qiye.163.com (Hmail) with ESMTPA id 708184E1718;
        Wed, 27 Nov 2019 08:30:27 +0800 (CST)
From: Peng Hao <richard.peng@oppo.com>
To: pbonzini@redhat.com, rkrcmar@redhat.com
Cc: x86@kernel.org, kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Peng Hao <richard.peng@oppo.com>
Subject: [PATCH] kvm/x86: export kvm_vector_hashing_enabled() is unnecessary
Date: Wed, 27 Nov 2019 08:30:25 +0800
Message-Id: <1574814625-29295-1-git-send-email-richard.peng@oppo.com>
X-Mailer: git-send-email 1.8.3.1
X-HM-Spam-Status: e1kfGhgUHx5ZQUtXWQgYFAkeWUFZVk9VSkJPS0tKSkJMQ0pPQk9ZV1koWU
        FJSUtLSjdXWS1ZQUlXWQkOFx4IWUFZNTQpNjo3JCkuNz5ZBg++
X-HM-Sender-Digest: e1kMHhlZQR0aFwgeV1kSHx4VD1lBWUc6PRw6IRw*ODg#MgMDCjc2Og9J
        PEgKCUxVSlVKTkxPQ0pPTUlDS0JPVTMWGhIXVQkSGBMaCR9VCx4VHDsUCwsUVRgUFkVZV1kSC1lB
        WUpJSlVKSVVKT0xVSU5LWVdZCAFZQUpIS0k3Bg++
X-HM-Tid: 0a6eaa44384b9376kuws708184e1718
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

kvm_vector_hashing_enabled() is just called in kvm.ko module.

Signed-off-by: Peng Hao <richard.peng@oppo.com>
Reviewed-by: Liran Alon <liran.alon@oracle.com>
---
 arch/x86/kvm/x86.c | 1 -
 1 file changed, 1 deletion(-)

```
#### [PATCH v2] KVM: SVM: Fix "error" isn't initializedCc: "pbonzini@redhat.com" <pbonzini@redhat.com>,
##### From: Haiwei Li <lihaiwei.kernel@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Haiwei Li <lihaiwei.kernel@gmail.com>
X-Patchwork-Id: 11263527
Return-Path: <SRS0=T3S3=ZT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AB8FD138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 27 Nov 2019 07:23:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 883FB206F0
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 27 Nov 2019 07:23:34 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="LUVyaSWC"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726545AbfK0HXZ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 27 Nov 2019 02:23:25 -0500
Received: from mail-pf1-f196.google.com ([209.85.210.196]:36414 "EHLO
        mail-pf1-f196.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726133AbfK0HXZ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 27 Nov 2019 02:23:25 -0500
Received: by mail-pf1-f196.google.com with SMTP id b19so10535354pfd.3;
        Tue, 26 Nov 2019 23:23:25 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=to:from:subject:cc:message-id:date:user-agent:mime-version
         :content-language:content-transfer-encoding;
        bh=+dIEa+jclTmXr02IdnKWGZL7TW+4WBFOQZr27PMe7Hc=;
        b=LUVyaSWC8ur/hYdxkd01ssliYl8hgfyWz8MGHZr/pgpnMxFKjZpDYmTiv5Xbg35YPw
         T7bstW0FN20orFDv24ZfFaJmwxuZnbyCm54i/lY2fVlxZbGc+I9mpTj4zMKF9Ao6ITw2
         Pqnh/fqvQvU3kNZJNw/psAiDHpbFzjG3kozmrkJ8QM9ZMm6dGbruFw1jJA7yYEEGQdc1
         tRj7XHGlxPWtJGHXutDg9aXe2QGMH7qZl3vERWQ2qifuLNk6n3KUgSvN+sVc3O5zlV55
         Ku58NI1qssmv0EJdTyunl9MYkZI8Yro68/kLXxZNDAz/+hbcbrJn1ibZystLXwOv6OOY
         Djrw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:to:from:subject:cc:message-id:date:user-agent
         :mime-version:content-language:content-transfer-encoding;
        bh=+dIEa+jclTmXr02IdnKWGZL7TW+4WBFOQZr27PMe7Hc=;
        b=EfnypMnCH7Jbfw/qBdSWtUoPPEypwm4ywGbAzIEZ3QdK+oS1KNkji2PZgDPMDWKIZo
         +D+P1L8ra94nIVxbqHRYtngHeZPYnIzRqd0nSnIB9tK0eamAAhXm2k8ZLMVjNFZiz5VC
         2EsNftTsn0Xg2w6w/Q4RXXSeCZPQ8YyN0a0gkMu4CAokD9s4Y7Olzj3g/xGn23anJqGr
         l/+//tdjIuOnHdZPNjEhwl0EqGQ//weaUI/6zUeamY+PfCUyb4mNSEMYSPZ2XTinDDcv
         suaPa73lHJa4bDmLdURaLceRF9ELSN2hzBywUFAhNqTLrdeuMehJE8EG20M75uzElX8c
         8xYw==
X-Gm-Message-State: APjAAAUtvVeXW33jJtnmZBisMSpHjQ8kwjlzT8B+Wi9l5+JvBVr5fYIs
        ImGxWVZAhdS5A0XtghuIoQ==
X-Google-Smtp-Source: 
 APXvYqzS17o0cTwSBMikvDtpI2vJkGXunqmsk69ZCLz76soXE2RAFfo2u+HPnSMvKaOmoDyyDIMEnw==
X-Received: by 2002:a63:ea09:: with SMTP id c9mr3283058pgi.232.1574839404727;
        Tue, 26 Nov 2019 23:23:24 -0800 (PST)
Received: from [127.0.0.1] ([203.205.141.52])
        by smtp.gmail.com with ESMTPSA id
 g7sm14609829pgr.52.2019.11.26.23.23.16
        (version=TLS1_3 cipher=TLS_AES_128_GCM_SHA256 bits=128/128);
        Tue, 26 Nov 2019 23:23:24 -0800 (PST)
To: "x86@kernel.org" <x86@kernel.org>, kvm@vger.kernel.org,
        "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>,
        linux-crypto@vger.kernel.org
From: Haiwei Li <lihaiwei.kernel@gmail.com>
Subject: [PATCH v2] KVM: SVM: Fix "error" isn't initialized
Cc: "pbonzini@redhat.com" <pbonzini@redhat.com>,
        "rkrcmar@redhat.com" <rkrcmar@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        "vkuznets@redhat.com" <vkuznets@redhat.com>,
        "wanpengli@tencent.com" <wanpengli@tencent.com>,
        "jmattson@google.com" <jmattson@google.com>,
        "joro@8bytes.org" <joro@8bytes.org>,
        "tglx@linutronix.de" <tglx@linutronix.de>,
        "mingo@redhat.com" <mingo@redhat.com>,
        "bp@alien8.de" <bp@alien8.de>, "hpa@zytor.com" <hpa@zytor.com>,
        thomas.lendacky@amd.com, gary.hook@amd.com,
        herbert@gondor.apana.org.au, davem@davemloft.net
Message-ID: <2967bd12-21bf-3223-e90b-96b4eaa8c4c2@gmail.com>
Date: Wed, 27 Nov 2019 15:23:09 +0800
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:68.0)
 Gecko/20100101 Thunderbird/68.2.2
MIME-Version: 1.0
Content-Language: en-US
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From e7f9c786e43ef4f890b8a01f15f8f00786f4b14a Mon Sep 17 00:00:00 2001
From: Haiwei Li <lihaiwei@tencent.com>
Date: Wed, 27 Nov 2019 15:00:49 +0800
Subject: [PATCH v2] fix: 'error' is not initialized

There are a bunch of error paths were "error" isn't initialized.

Signed-off-by: Haiwei Li <lihaiwei@tencent.com>
Reported-by: Dan Carpenter <dan.carpenter@oracle.com>
---
  arch/x86/kvm/svm.c           | 3 ++-
  drivers/crypto/ccp/psp-dev.c | 2 ++
  2 files changed, 4 insertions(+), 1 deletion(-)


--
1.8.3.1

```
#### [kvm-unit-tests PATCH 01/18] lib: arm/arm64: Remove unnecessary dcache maintenance operations
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexandru Elisei <alexandru.elisei@arm.com>
X-Patchwork-Id: 11264205
Return-Path: <SRS0=T3S3=ZT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 095476C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 27 Nov 2019 14:25:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E6A9C206F0
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 27 Nov 2019 14:25:07 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727209AbfK0OZH (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 27 Nov 2019 09:25:07 -0500
Received: from foss.arm.com ([217.140.110.172]:48178 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726558AbfK0OZG (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 27 Nov 2019 09:25:06 -0500
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 58BAA328;
        Wed, 27 Nov 2019 06:25:06 -0800 (PST)
Received: from e123195-lin.cambridge.arm.com (e123195-lin.cambridge.arm.com
 [10.1.196.63])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPA id
 3D11A3F68E;
        Wed, 27 Nov 2019 06:25:05 -0800 (PST)
From: Alexandru Elisei <alexandru.elisei@arm.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, rkrcmar@redhat.com, drjones@redhat.com,
        maz@kernel.org, andre.przywara@arm.com, vladimir.murzin@arm.com,
        mark.rutland@arm.com
Subject: [kvm-unit-tests PATCH 01/18] lib: arm/arm64: Remove unnecessary
 dcache maintenance operations
Date: Wed, 27 Nov 2019 14:23:53 +0000
Message-Id: <20191127142410.1994-2-alexandru.elisei@arm.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20191127142410.1994-1-alexandru.elisei@arm.com>
References: <20191127142410.1994-1-alexandru.elisei@arm.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

On ARMv7 with multiprocessing extensions (which are mandated by the
virtualization extensions [1]), and on ARMv8, translation table walks are
coherent [2][3], which means that no dcache maintenance operations are
required when changing the tables. Remove the maintenance operations so
that we do only the minimum required to ensure correctness.

Translation table walks are coherent if the memory where the tables
themselves reside have the same shareability and cacheability attributes
as the translation table walks. For ARMv8, this is already the case, and
it is only a matter of removing the cache operations.

However, for ARMv7, translation table walks were being configured as
Non-shareable (TTBCR.SH0 = 0b00) and Non-cacheable
(TTBCR.{I,O}RGN0 = 0b00). Fix that by marking them as Inner Shareable,
Normal memory, Inner and Outer Write-Back Write-Allocate Cacheable.

The ARM ARM uses a DSB ISH in the example code for updating a
translation table entry [4], however we use a DSB ISHST. It turns out
that the ARM ARM is being overly cautious and our approach is similar to
what the Linux kernel does (see commit 98f7685ee69f ("arm64: barriers:
make use of barrier options with explicit barriers")); it also makes
sense to use a store DSB barrier to make sure the new value is seen by
by the next table walk, which is not a memory operation and not affected
by a DMB.

Because translation table walks are now coherent on arm, replace the
TLBIMVAA operation with TLBIMVAAIS in flush_tlb_page, which acts on the
Inner Shareable domain instead of being private to the PE.

The functions that update the translation table are called when the MMU
is off, or to modify permissions, in the case of the cache test, so
break-before-make is not necessary.

[1] ARM DDI 0406C.d, section B1.7
[2] ARM DDI 0406C.d, section B3.3.1
[3] ARM DDI 0487E.a, section D13.2.72
[4] ARM DDI 0487E.a, section K11.5.3

Reported-by: Mark Rutland <mark.rutland@arm.com>
Signed-off-by: Alexandru Elisei <alexandru.elisei@arm.com>
---
 lib/arm/asm/mmu.h           |  4 ++--
 lib/arm/asm/pgtable-hwdef.h |  8 ++++++++
 lib/arm/mmu.c               | 18 +++++-------------
 arm/cstart.S                |  7 +++++--
 4 files changed, 20 insertions(+), 17 deletions(-)

```
#### [PATCH] vfio: call irq_bypass_unregister_producer() before freeing irq
##### From: Jiang Yi <giangyi@amazon.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jiang Yi <giangyi@amazon.com>
X-Patchwork-Id: 11264577
Return-Path: <SRS0=T3S3=ZT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B878214DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 27 Nov 2019 16:49:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 8F34A207DD
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 27 Nov 2019 16:49:45 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amazon.com header.i=@amazon.com
 header.b="X3gAA8Oo"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727008AbfK0Qto (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 27 Nov 2019 11:49:44 -0500
Received: from smtp-fw-9102.amazon.com ([207.171.184.29]:2766 "EHLO
        smtp-fw-9102.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726909AbfK0Qto (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 27 Nov 2019 11:49:44 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.com; i=@amazon.com; q=dns/txt; s=amazon201209;
  t=1574873384; x=1606409384;
  h=from:to:cc:subject:date:message-id;
  bh=eQhzbtK33bAPiznFgsly4Gjgsjra5pEl6cMAgAK27Co=;
  b=X3gAA8OoWYcv2+kuZ/LPGlAADMtbn5RHOaACNAMlVAgKRcb8e9K8o1lI
   Sobdiia4G5cBfNhKT+46/dIK8tSUvqYOptXvxnlr8YvxFhgNX8OBuqA03
   dUnSDwDQ+NHSDqwewDdnQgSoWEb/VhG33PCg+/zA9WJIXnTekV8jKHMqF
   8=;
IronPort-SDR: 
 qZiodDjbJRpZvCLsnk5E3jdX9kb4Ej5uhQiX3JkG+RC1463A/jU5SdWMRB5dquDEdbVDTOjS3Y
 0xraSK5E8bjw==
X-IronPort-AV: E=Sophos;i="5.69,250,1571702400";
   d="scan'208";a="10251277"
Received: from sea32-co-svc-lb4-vlan3.sea.corp.amazon.com (HELO
 email-inbound-relay-1d-98acfc19.us-east-1.amazon.com) ([10.47.23.38])
  by smtp-border-fw-out-9102.sea19.amazon.com with ESMTP;
 27 Nov 2019 16:49:31 +0000
Received: from u5992c35209ee5c.ant.amazon.com
 (iad7-ws-svc-lb50-vlan3.amazon.com [10.0.93.214])
        by email-inbound-relay-1d-98acfc19.us-east-1.amazon.com (Postfix) with
 ESMTPS id AD920A247C;
        Wed, 27 Nov 2019 16:49:28 +0000 (UTC)
Received: from u5992c35209ee5c.ant.amazon.com (localhost [127.0.0.1])
        by u5992c35209ee5c.ant.amazon.com (8.15.2/8.15.2/Debian-3) with ESMTPS
 id xARGnQlJ016125
        (version=TLSv1.3 cipher=TLS_AES_256_GCM_SHA384 bits=256 verify=NOT);
        Wed, 27 Nov 2019 17:49:26 +0100
Received: (from giangyi@localhost)
        by u5992c35209ee5c.ant.amazon.com (8.15.2/8.15.2/Submit) id
 xARGnPIw016123;
        Wed, 27 Nov 2019 17:49:25 +0100
From: Jiang Yi <giangyi@amazon.com>
To: kvm@vger.kernel.org
Cc: adulea@amazon.de, jschoenh@amazon.de, maz@kernel.org,
        alex.williamson@redhat.com, cohuck@redhat.com,
        Jiang Yi <giangyi@amazon.com>
Subject: [PATCH] vfio: call irq_bypass_unregister_producer() before freeing
 irq
Date: Wed, 27 Nov 2019 17:49:10 +0100
Message-Id: <20191127164910.15888-1-giangyi@amazon.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Since irq_bypass_register_producer() is called after request_irq(), we
should do tear-down in reverse order: irq_bypass_unregister_producer()
then free_irq().

Signed-off-by: Jiang Yi <giangyi@amazon.com>
Reviewed-by: Marc Zyngier <maz@kernel.org>
---
 drivers/vfio/pci/vfio_pci_intrs.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
