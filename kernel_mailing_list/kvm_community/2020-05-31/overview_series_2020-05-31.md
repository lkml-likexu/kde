#### [PULL 01/25] scripts/qemugdb: Remove shebang header
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
 <philmd@redhat.com>
X-Patchwork-Id: 11580721
Return-Path: <SRS0=4Gy4=7N=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DDD9790
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 31 May 2020 16:39:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C6305207BB
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 31 May 2020 16:39:01 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="AbucRe59"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728105AbgEaQjA (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 31 May 2020 12:39:00 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:29745 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1725912AbgEaQi7 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 31 May 2020 12:38:59 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1590943138;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
  content-type:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=Ly/BNyoFscwcUlEdMi1CDGrrxngHJB98Yaq6NCa8Sss=;
        b=AbucRe5984FPtG1hKWIxCZp1xnfgZp8OLWH8sgnO/XNKeCyhp/wtKhJpVVgU4GF6mHiunE
        IJbFm2YM1IMPOCdk9v8U0y31TFepGr/PG4QW8YfaZNmtgKlc3JN+BiEv1nGM9IioDKU2+S
        EmYS/8jmCxhhrFU6vNUbvj/+O/7RhWs=
Received: from mail-wr1-f70.google.com (mail-wr1-f70.google.com
 [209.85.221.70]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-79-O7qQmQCQOey1fmplPEslBg-1; Sun, 31 May 2020 12:38:57 -0400
X-MC-Unique: O7qQmQCQOey1fmplPEslBg-1
Received: by mail-wr1-f70.google.com with SMTP id o1so3589337wrm.17
        for <kvm@vger.kernel.org>; Sun, 31 May 2020 09:38:56 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=Ly/BNyoFscwcUlEdMi1CDGrrxngHJB98Yaq6NCa8Sss=;
        b=BitRgJ2tbJZKP9T2JFd1BS4f5GhJv8mrWD/XgEEHPTIuRZtxyyIf8/+Ihwlq4MdzpO
         IXDneuWec0LfIEyZpSsGyz2x6y37PhhpbywBnYJfz74IQAVZKR+meiCq4GcydmZ33Cn0
         19YYuu/QtiH+lL/h+ZbkNeQIFf8s7k+E3mmTSUYf83axr2+7LM2pJ+guZ5SF9pGybK5F
         fUfx4ajbGxreuq9l6IlT938B7W0i36+IEXG/C2fMTiNS49T9w3utk+scSnXLLTUmznDt
         BJ4Brtz2XNbwS2CeDjSjV7+pJMou4khMDdToDDyJKBAGFnHHFfHZs/AahJMhtxMQB75+
         D8rQ==
X-Gm-Message-State: AOAM533imrY0DxNbD3bKhZy/I0UX1twyVwuyoAemhrbrpylIvjmwo4WN
        Y5yJJwDMCmRvPV+O91ngZtPtqUvdkZwdCSXititiRyuQMKPYnlgswvhy+8ieDHZp0eCrZR0BUdS
        H4nOrOfEIlsbu
X-Received: by 2002:a5d:4e03:: with SMTP id p3mr18519105wrt.350.1590943135174;
        Sun, 31 May 2020 09:38:55 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJxe7sJn4ZGtJgKpS26KNwTyhpDQC9oFjhczDjqsHEXGXaRKqr+VepBPJMpNihdteRynA8wNuA==
X-Received: by 2002:a5d:4e03:: with SMTP id p3mr18519096wrt.350.1590943134994;
        Sun, 31 May 2020 09:38:54 -0700 (PDT)
Received: from localhost.localdomain (43.red-83-51-162.dynamicip.rima-tde.net.
 [83.51.162.43])
        by smtp.gmail.com with ESMTPSA id
 v7sm8920008wme.46.2020.05.31.09.38.53
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Sun, 31 May 2020 09:38:54 -0700 (PDT)
From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>
To: qemu-devel@nongnu.org
Cc: Cleber Rosa <crosa@redhat.com>, Kevin Wolf <kwolf@redhat.com>,
 kvm@vger.kernel.org, Richard Henderson <rth@twiddle.net>,
 Fam Zheng <fam@euphon.net>, Eduardo Habkost <ehabkost@redhat.com>,
	=?utf-8?q?Alex_Benn=C3=A9e?= <alex.bennee@linaro.org>,
 Paolo Bonzini <pbonzini@redhat.com>, Max Reitz <mreitz@redhat.com>,
	=?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>,
 Stefan Hajnoczi <stefanha@redhat.com>, Markus Armbruster <armbru@redhat.com>,
 Marcelo Tosatti <mtosatti@redhat.com>, qemu-block@nongnu.org, =?utf-8?q?Phi?=
	=?utf-8?q?lippe_Mathieu-Daud=C3=A9?= <f4bug@amsat.org>,
 John Snow <jsnow@redhat.com>
Subject: [PULL 01/25] scripts/qemugdb: Remove shebang header
Date: Sun, 31 May 2020 18:38:22 +0200
Message-Id: <20200531163846.25363-2-philmd@redhat.com>
X-Mailer: git-send-email 2.21.3
In-Reply-To: <20200531163846.25363-1-philmd@redhat.com>
References: <20200531163846.25363-1-philmd@redhat.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Philippe Mathieu-Daudé <f4bug@amsat.org>

These scripts are loaded as plugin by GDB (and they don't
have any __main__ entry point). Remove the shebang header.

Signed-off-by: Philippe Mathieu-Daudé <f4bug@amsat.org>
Acked-by: Alex Bennée <alex.bennee@linaro.org>
Reviewed-by: John Snow <jsnow@redhat.com>
Reviewed-by: Kevin Wolf <kwolf@redhat.com>
Message-Id: <20200512103238.7078-2-philmd@redhat.com>
Signed-off-by: Philippe Mathieu-Daudé <philmd@redhat.com>
---
 scripts/qemugdb/__init__.py  | 3 +--
 scripts/qemugdb/aio.py       | 3 +--
 scripts/qemugdb/coroutine.py | 3 +--
 scripts/qemugdb/mtree.py     | 4 +---
 scripts/qemugdb/tcg.py       | 1 -
 scripts/qemugdb/timers.py    | 1 -
 6 files changed, 4 insertions(+), 11 deletions(-)

```
