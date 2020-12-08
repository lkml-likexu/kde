#### [RFC V2 01/37] fs: introduce dmemfs module
##### From: yulei.kernel@gmail.com

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: yulei zhang <yulei.kernel@gmail.com>
X-Patchwork-Id: 11955357
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 30B1EC433FE
	for <kvm@archiver.kernel.org>; Mon,  7 Dec 2020 11:32:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D93092339F
	for <kvm@archiver.kernel.org>; Mon,  7 Dec 2020 11:32:50 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726343AbgLGLce (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 7 Dec 2020 06:32:34 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:40482 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726790AbgLGLcb (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 7 Dec 2020 06:32:31 -0500
Received: from mail-pf1-x443.google.com (mail-pf1-x443.google.com
 [IPv6:2607:f8b0:4864:20::443])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 61917C0613D0;
        Mon,  7 Dec 2020 03:31:45 -0800 (PST)
Received: by mail-pf1-x443.google.com with SMTP id c79so9606637pfc.2;
        Mon, 07 Dec 2020 03:31:45 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=ewpiaZqTRGdJ05S6FvGPc0qF7vcc593bt6ShYsuckHQ=;
        b=RPs0JFNrA34b2v6m4o0WKzzEMoIgFha8rYwcJlJYFwLi4ku7d2HYbJ7wKa//+yfUBX
         tJ3QIj9uXjYAV7QDBPF4i8kWN/WukA9vB1cJPlVE8J6zlIPP6dECt3+Gy067gGDUNMfT
         pq4e3VandG+gI0X1miFP+Ome0AN6naVoR6X8H6B3T3wm6ewpqwDAyeGbGhKie5qRvkry
         7yhUTV47Un0jRI9sEq2r17tOIMitEH+ebYmdWLf4zCGTHh9IVoeUf8FE6QbNebsYSzAi
         pNi6cX4KjaxtUH7vfGNTEGN+cfuBtxZeaa5w5yXo88wxc/a85VdJd282dDdVw8c3iW1Q
         p9eQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=ewpiaZqTRGdJ05S6FvGPc0qF7vcc593bt6ShYsuckHQ=;
        b=sbhDI1PjE1U3BKnCMrFIfes99h7royl/4sU1UGkeL4p1CWx29sDp3xLL2JQr0NXSVP
         f7JfPKx7anfkTX054xWF7iAB9vqTXgnHWGZH27rCEiSP/N2ypkKZE5548ZiPEhtno2ut
         UTHxvcrF7mUl/gONcDN1kJivGc9I8RPxSgiX+wMuehhjJtffqPHSTG6AOWxJY+qpqRdJ
         r3rJYbTc1T2PY1aTUZAt8SNg+Ex9HDFgEub82BRY2H9JdN/otqWQi5GzNC5soXVzUoBz
         Fvcpem59njBQ2u/QlDZ5IG9lT4ELtQrIvOUqFjL14WVd9js04zfGwCZYQNCL2fC8leuW
         yz1Q==
X-Gm-Message-State: AOAM5325RfVR96+MDZLAC58QoA2fwqZDGgRv3wg4o00U5izWAMwLXQ/N
        ExEIhFlmoY9QQ10R19tM+8c=
X-Google-Smtp-Source: 
 ABdhPJyMmiiecC7lQBFkhMTn89Ja1IhAR/H6fUYhXm8PI2Ykcxu8WlFJkRhL9epCDiG6RPld96HGHg==
X-Received: by 2002:a17:902:8341:b029:d8:d123:2297 with SMTP id
 z1-20020a1709028341b02900d8d1232297mr15889510pln.65.1607340704982;
        Mon, 07 Dec 2020 03:31:44 -0800 (PST)
Received: from localhost.localdomain ([203.205.141.39])
        by smtp.gmail.com with ESMTPSA id
 d4sm14219822pfo.127.2020.12.07.03.31.41
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Mon, 07 Dec 2020 03:31:44 -0800 (PST)
From: yulei.kernel@gmail.com
X-Google-Original-From: yuleixzhang@tencent.com
To: linux-mm@kvack.org, akpm@linux-foundation.org,
        linux-fsdevel@vger.kernel.org, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, naoya.horiguchi@nec.com,
        viro@zeniv.linux.org.uk, pbonzini@redhat.com
Cc: joao.m.martins@oracle.com, rdunlap@infradead.org,
        sean.j.christopherson@intel.com, xiaoguangrong.eric@gmail.com,
        kernellwp@gmail.com, lihaiwei.kernel@gmail.com,
        Yulei Zhang <yuleixzhang@tencent.com>,
        Xiao Guangrong <gloryxiao@tencent.com>
Subject: [RFC V2 01/37] fs: introduce dmemfs module
Date: Mon,  7 Dec 2020 19:30:54 +0800
Message-Id: 
 <d3e9df357201a1dc99678128b825c79713f35e0c.1607332046.git.yuleixzhang@tencent.com>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <cover.1607332046.git.yuleixzhang@tencent.com>
References: <cover.1607332046.git.yuleixzhang@tencent.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Yulei Zhang <yuleixzhang@tencent.com>

dmemfs (Direct Memory filesystem) is device memory or reserved
memory based filesystem. This kind of memory is special as it
is not managed by kernel and it is not associated with 'struct page'.

The original purpose for dmemfs is to drop the usage of
'struct page' to save extra system memory in public cloud
enviornment.

This patch introduces the basic framework of dmemfs and only
mkdir and create regular file are supported.

Signed-off-by: Xiao Guangrong  <gloryxiao@tencent.com>
Signed-off-by: Yulei Zhang <yuleixzhang@tencent.com>
---
 fs/Kconfig                 |   1 +
 fs/Makefile                |   1 +
 fs/dmemfs/Kconfig          |  13 +++
 fs/dmemfs/Makefile         |   7 ++
 fs/dmemfs/inode.c          | 266 +++++++++++++++++++++++++++++++++++++++++++++
 include/uapi/linux/magic.h |   1 +
 6 files changed, 289 insertions(+)
 create mode 100644 fs/dmemfs/Kconfig
 create mode 100644 fs/dmemfs/Makefile
 create mode 100644 fs/dmemfs/inode.c

```
#### [PATCH v2 1/5] gitlab-ci: Document 'build-tcg-disabled' is a KVM X86 job
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
 <philmd@redhat.com>
X-Patchwork-Id: 11955315
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 1AEA8C4167B
	for <kvm@archiver.kernel.org>; Mon,  7 Dec 2020 11:25:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BB6BD2310B
	for <kvm@archiver.kernel.org>; Mon,  7 Dec 2020 11:25:32 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726677AbgLGLZb (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 7 Dec 2020 06:25:31 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:30369 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726653AbgLGLZb (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 7 Dec 2020 06:25:31 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1607340245;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=U6QCRjxKvIwhYoV/41s2s2+6dI4wCbnqhxRPlqlth8U=;
        b=EfzQpQ/kqV49/D6sGFTAsOqsOLFZiRI2HKbkO+YuCnpL5UmPxJVmcpQyIpWrAOg2QMSpnF
        1/k90VajmPa2g2TPI5nIS809Km5vRJ5nnV5BwbaaBjyoWGJEq+73dWNZKyL9fWN6Z3RKGw
        dkU9z6fFhaV/DULnOwAUXui7lob1Ubg=
Received: from mail-wm1-f71.google.com (mail-wm1-f71.google.com
 [209.85.128.71]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-221-sxPFdyLgN3GGBmp2ZfU51w-1; Mon, 07 Dec 2020 06:24:03 -0500
X-MC-Unique: sxPFdyLgN3GGBmp2ZfU51w-1
Received: by mail-wm1-f71.google.com with SMTP id u123so4020579wmu.5
        for <kvm@vger.kernel.org>; Mon, 07 Dec 2020 03:24:03 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=U6QCRjxKvIwhYoV/41s2s2+6dI4wCbnqhxRPlqlth8U=;
        b=hsvWHAFURQRdZ7bSTOR1fJWplZWU7u1b98qlNBfW5jLpEQiFM1qNcfXbtZggGAGRYI
         yy2DXrscWB0emXR02wh1NKA2Ok2J/5Lf/MGncq96dweH0z1ojYxuTwABbVhhtxMgg68W
         5XDFgTf3WVGtJRakVm9+8M9eD7pizaTSokiTeTml/S4NvZCOuBF2ZBX/iayR82uU9d2E
         FR22nn69+H1rsFP93vWPH7RTQf3ORmf/d6up+9cMER0ZqW21o3m5cftG4g7NhguoUZ0v
         yUmq+oTbEkynlnLRnqVuP2EV0Q3c8/1oMiF3Eif2/sNIAI2VMHx0qt6TGkrQRuqoMVNj
         YX2w==
X-Gm-Message-State: AOAM530SqGZBPmvt2Qup7v2xT3/uZQziwWcVHlyuyWBuSiTsU1CdTGo7
        oXNfkJrbHmUFHq69p2pZluAMLswr8fblmQB/WaIJUN+AJGGuUYJRp7SxRGb0264/fTB+qHI23mo
        1j+bXtKzzSiK9
X-Received: by 2002:a1c:4907:: with SMTP id w7mr10183693wma.175.1607340242504;
        Mon, 07 Dec 2020 03:24:02 -0800 (PST)
X-Google-Smtp-Source: 
 ABdhPJyUOPOj91GL2D5bWSF19z1crpAKZX/6htMwNjDW7CLNGlfCM/ktiYiE4SKzGGKVP6p9Vp9lvg==
X-Received: by 2002:a1c:4907:: with SMTP id w7mr10183684wma.175.1607340242361;
        Mon, 07 Dec 2020 03:24:02 -0800 (PST)
Received: from localhost.localdomain (101.red-88-21-206.staticip.rima-tde.net.
 [88.21.206.101])
        by smtp.gmail.com with ESMTPSA id
 k11sm13362266wmj.42.2020.12.07.03.24.00
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 07 Dec 2020 03:24:01 -0800 (PST)
From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>
To: qemu-devel@nongnu.org
Cc: Halil Pasic <pasic@linux.ibm.com>, Thomas Huth <thuth@redhat.com>,
 Christian Borntraeger <borntraeger@de.ibm.com>,
 Cornelia Huck <cohuck@redhat.com>, Claudio Fontana <cfontana@suse.de>,
 Willian Rampazzo <wrampazz@redhat.com>, qemu-s390x@nongnu.org,
 Anthony Perard <anthony.perard@citrix.com>,
 =?utf-8?q?Alex_Benn=C3=A9e?= <alex.bennee@linaro.org>,
 Wainer dos Santos Moschetta <wainersm@redhat.com>,
 xen-devel@lists.xenproject.org, Paul Durrant <paul@xen.org>,
 Marcelo Tosatti <mtosatti@redhat.com>, Paolo Bonzini <pbonzini@redhat.com>,
 kvm@vger.kernel.org,
 =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>,
 Stefano Stabellini <sstabellini@kernel.org>
Subject: [PATCH v2 1/5] gitlab-ci: Document 'build-tcg-disabled' is a KVM X86
 job
Date: Mon,  7 Dec 2020 12:23:49 +0100
Message-Id: <20201207112353.3814480-2-philmd@redhat.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20201207112353.3814480-1-philmd@redhat.com>
References: <20201207112353.3814480-1-philmd@redhat.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Document what this job cover (build X86 targets with
KVM being the single accelerator available).

Signed-off-by: Philippe Mathieu-Daudé <philmd@redhat.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
---
 .gitlab-ci.yml | 5 +++++
 1 file changed, 5 insertions(+)

```
#### [PATCH v3 1/5] gitlab-ci: Document 'build-tcg-disabled' is a KVM X86 job
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
 <philmd@redhat.com>
X-Patchwork-Id: 11955799
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 50AAEC4361B
	for <kvm@archiver.kernel.org>; Mon,  7 Dec 2020 13:16:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 23A33233A0
	for <kvm@archiver.kernel.org>; Mon,  7 Dec 2020 13:16:43 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725981AbgLGNQm (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 7 Dec 2020 08:16:42 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:43893 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1725550AbgLGNQm (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 7 Dec 2020 08:16:42 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1607346915;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=DUD443fjC7TlYCq2Zs7qkYPHzlFo7vsq2RAf28zHG0Y=;
        b=b49Y+4DyR6uXgzYr3drfs9eM2NaovpAiJryrok+zE1zpgP+0GZJlY/9Apr+vIgcT8Xveo7
        jbAkDr/2jZGDMDIb95XFKAd+21AM+VaEWpYUvgc8DOa8nclMXIV3lg9Dzf2dkKPa5In1yf
        QnNEFAFVp14994KiswEMc6UsNe7OdU0=
Received: from mail-wm1-f70.google.com (mail-wm1-f70.google.com
 [209.85.128.70]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-491-86ymiXs0Mx-a8AJMAzopVA-1; Mon, 07 Dec 2020 08:15:13 -0500
X-MC-Unique: 86ymiXs0Mx-a8AJMAzopVA-1
Received: by mail-wm1-f70.google.com with SMTP id a205so4075006wme.9
        for <kvm@vger.kernel.org>; Mon, 07 Dec 2020 05:15:13 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=DUD443fjC7TlYCq2Zs7qkYPHzlFo7vsq2RAf28zHG0Y=;
        b=XDxXNINrnSAESnrcpu0Qwp8hqX76v4V4Yq34PR37noFN9j8dUAtQAgsLPmGq5SnJgL
         UtN7kPa2JJpBqldAQpDRvcR8EFAwjGNPa/TM3BO4Rh2C4X9sq+WWi9eC+Vx9hojsYRWf
         sDVCbgb+cHK41AVm4v+K21YVDpLYJHWX9OwT8sW2V7gZ1vBTl8M40oeE603AgbGyG3pJ
         yFXo4+yx8cz2Xg0d7G3Px11RF/kjevteeNlKo/rPs+oHwfLJlBZntLHx5c26vQuEdCLW
         vA3QWj+yKQuGfsA6kHFRMfF2IOtJXKEAZy26cZBQh7owjxNSjLtSemkboWWergENDcTh
         HhPA==
X-Gm-Message-State: AOAM531LwtNKaf6J4q2QSPIrwXk1Ul6eiLxReRxaMv+Iez/H5ejF5Mjr
        2imjOfEP/ztbBgDYo3wP5GGq6fcY66FFQvAjmee7vpeBdPnKrufcW8dRxOhrXEdGZ+7lxQVLw4H
        gx5hAXzEZPIEX
X-Received: by 2002:a1c:c2d4:: with SMTP id
 s203mr18470507wmf.58.1607346912724;
        Mon, 07 Dec 2020 05:15:12 -0800 (PST)
X-Google-Smtp-Source: 
 ABdhPJx0KSXp7DP6CDis0L6tP1I2Gzz9cpg1u4ccuV+5/oiKxMdma/cepl4uO8AaAxQi4CtlwH61VQ==
X-Received: by 2002:a1c:c2d4:: with SMTP id
 s203mr18470485wmf.58.1607346912558;
        Mon, 07 Dec 2020 05:15:12 -0800 (PST)
Received: from localhost.localdomain (101.red-88-21-206.staticip.rima-tde.net.
 [88.21.206.101])
        by smtp.gmail.com with ESMTPSA id
 k18sm2265572wrd.45.2020.12.07.05.15.11
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 07 Dec 2020 05:15:11 -0800 (PST)
From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>
To: qemu-devel@nongnu.org
Cc: Thomas Huth <thuth@redhat.com>,
 Christian Borntraeger <borntraeger@de.ibm.com>,
 Stefano Stabellini <sstabellini@kernel.org>,
 Marcelo Tosatti <mtosatti@redhat.com>, kvm@vger.kernel.org,
 Paolo Bonzini <pbonzini@redhat.com>,
 Anthony Perard <anthony.perard@citrix.com>, =?utf-8?q?Philippe_Mathieu-Daud?=
	=?utf-8?q?=C3=A9?= <philmd@redhat.com>, qemu-s390x@nongnu.org,
 Halil Pasic <pasic@linux.ibm.com>, Willian Rampazzo <wrampazz@redhat.com>,
 Paul Durrant <paul@xen.org>, Cornelia Huck <cohuck@redhat.com>,
 xen-devel@lists.xenproject.org,
 =?utf-8?q?Alex_Benn=C3=A9e?= <alex.bennee@linaro.org>,
 Claudio Fontana <cfontana@suse.de>,
 Wainer dos Santos Moschetta <wainersm@redhat.com>
Subject: [PATCH v3 1/5] gitlab-ci: Document 'build-tcg-disabled' is a KVM X86
 job
Date: Mon,  7 Dec 2020 14:14:59 +0100
Message-Id: <20201207131503.3858889-2-philmd@redhat.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20201207131503.3858889-1-philmd@redhat.com>
References: <20201207131503.3858889-1-philmd@redhat.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Document what this job cover (build X86 targets with
KVM being the single accelerator available).

Reviewed-by: Thomas Huth <thuth@redhat.com>
Signed-off-by: Philippe Mathieu-Daudé <philmd@redhat.com>
---
 .gitlab-ci.yml | 5 +++++
 1 file changed, 5 insertions(+)

```
#### [PATCH 1/2 v4] KVM: nSVM: Check reserved values for 'Type' and invalid vectors in EVENTINJ
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11956631
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	UNPARSEABLE_RELAY,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 35D90C4361B
	for <kvm@archiver.kernel.org>; Mon,  7 Dec 2020 19:42:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 088A4238A1
	for <kvm@archiver.kernel.org>; Mon,  7 Dec 2020 19:42:44 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726472AbgLGTm2 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 7 Dec 2020 14:42:28 -0500
Received: from userp2130.oracle.com ([156.151.31.86]:51154 "EHLO
        userp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725877AbgLGTm1 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 7 Dec 2020 14:42:27 -0500
Received: from pps.filterd (userp2130.oracle.com [127.0.0.1])
        by userp2130.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 0B7Je3JL004397;
        Mon, 7 Dec 2020 19:41:43 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=corp-2020-01-29;
 bh=YznBnGGBSe/ExXpZhWJv2v3AfxSsYP+g6lEvIIUivu8=;
 b=PhYp3b4bX2EXecjtm0XhlhAFxuSwyfnyQXy9fFR4lssMPuazwBt+ELh+nfahT60DoqNL
 H6gm6PiLlpkpzwllL4qpxbjSX9ybC/SdBABbDjPjAhG+tmtf84fK0XAYMnD1GExkTYJY
 HOtX/IojXzxHloW3lNGzPGilgjFzdXpz5UzFuiMyrbRm5mWxtwgZwuNEQXmKsmtLifQ3
 4sYE4eJcJvDJAveqkgGnGbKfhkZnbkbphjCbh4SPH2/Zh6rwe2uNKGX3OLZ3dwd7v+Y6
 eDTGFRap9EHWRX95DsWSIm7JQdf9eXlCsZL6c7YDpRBINo8JD6Ip1RyWFVtPKGCrj4Bv wA==
Received: from aserp3030.oracle.com (aserp3030.oracle.com [141.146.126.71])
        by userp2130.oracle.com with ESMTP id 3581mqq66c-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=FAIL);
        Mon, 07 Dec 2020 19:41:43 +0000
Received: from pps.filterd (aserp3030.oracle.com [127.0.0.1])
        by aserp3030.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 0B7JeiJO044487;
        Mon, 7 Dec 2020 19:41:42 GMT
Received: from userv0122.oracle.com (userv0122.oracle.com [156.151.31.75])
        by aserp3030.oracle.com with ESMTP id 358ksmn0xt-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 07 Dec 2020 19:41:42 +0000
Received: from abhmp0014.oracle.com (abhmp0014.oracle.com [141.146.116.20])
        by userv0122.oracle.com (8.14.4/8.14.4) with ESMTP id 0B7JffDK015262;
        Mon, 7 Dec 2020 19:41:41 GMT
Received: from nsvm-sadhukhan.osdevelopmeniad.oraclevcn.com (/100.100.230.216)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Mon, 07 Dec 2020 11:41:41 -0800
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com, seanjc@google.com
Subject: [PATCH 1/2 v4] KVM: nSVM: Check reserved values for 'Type' and
 invalid vectors in EVENTINJ
Date: Mon,  7 Dec 2020 19:41:28 +0000
Message-Id: <20201207194129.7543-2-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.27.0
In-Reply-To: <20201207194129.7543-1-krish.sadhukhan@oracle.com>
References: <20201207194129.7543-1-krish.sadhukhan@oracle.com>
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9828
 signatures=668682
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 mlxlogscore=999
 suspectscore=1
 bulkscore=0 malwarescore=0 phishscore=0 mlxscore=0 spamscore=0
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2012070126
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9828
 signatures=668682
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=1
 mlxlogscore=999
 clxscore=1015 malwarescore=0 priorityscore=1501 adultscore=0
 lowpriorityscore=0 phishscore=0 spamscore=0 impostorscore=0 mlxscore=0
 bulkscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2012070126
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

According to sections "Canonicalization and Consistency Checks" and "Event
Injection" in APM vol 2

    VMRUN exits with VMEXIT_INVALID error code if either:
      - Reserved values of TYPE have been specified, or
      - TYPE = 3 (exception) has been specified with a vector that does not
	correspond to an exception (this includes vector 2, which is an NMI,
	not an exception).

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 arch/x86/include/asm/svm.h |  4 ++++
 arch/x86/kvm/svm/nested.c  | 14 ++++++++++++++
 2 files changed, 18 insertions(+)

```
#### [PATCH v4] self_tests/kvm: sync_regs test for diag318
##### From: Collin Walling <walling@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Collin Walling <walling@linux.ibm.com>
X-Patchwork-Id: 11956235
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D2DFBC433FE
	for <kvm@archiver.kernel.org>; Mon,  7 Dec 2020 15:42:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A39B623731
	for <kvm@archiver.kernel.org>; Mon,  7 Dec 2020 15:42:11 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725973AbgLGPmL (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 7 Dec 2020 10:42:11 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:40900 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1725822AbgLGPmL (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 7 Dec 2020 10:42:11 -0500
Received: from pps.filterd (m0098409.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 0B7FXHse036425;
        Mon, 7 Dec 2020 10:41:30 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=fNQPyWhNjGrlgpxap1kvGOs+bzmJ4XK4GY2RYPuxJJk=;
 b=JJYzLoUyqqWHzVeQj3rrufT9Jo+NWPRSXzkdCbEa1kTAA7Nu0lMddd9EmwrRgtdM7oWY
 Gf4UHNSX5lX8bNNkbZv11QUn0yXcuecj4CF+ovg0UczGN7zn5Q+sPCxSXVHQ67/EoS+8
 RGd0LAUfuevn35iz2zPmCC/mU7A6ERloVLeGRCLKztBKmvQj91c64bmrbNkDZxD+y8WM
 4jBYljmiFJp+YtOKovh1rGy4YHECstPhmCWrK5Yji5A6cGUiOjFpNNU8dNykHhh5RTVF
 IZaY8kOy2QQZFrOvymRy2ufAWNYmTr1k0PrrZCvrj5wJNpnrjdjY6d7voYjyd6Lz6Onz GA==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 359m5774dj-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 07 Dec 2020 10:41:30 -0500
Received: from m0098409.ppops.net (m0098409.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 0B7FXuW6039054;
        Mon, 7 Dec 2020 10:41:30 -0500
Received: from ppma02dal.us.ibm.com (a.bd.3ea9.ip4.static.sl-reverse.com
 [169.62.189.10])
        by mx0a-001b2d01.pphosted.com with ESMTP id 359m5774d7-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 07 Dec 2020 10:41:30 -0500
Received: from pps.filterd (ppma02dal.us.ibm.com [127.0.0.1])
        by ppma02dal.us.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 0B7FVtqY023305;
        Mon, 7 Dec 2020 15:41:29 GMT
Received: from b01cxnp23032.gho.pok.ibm.com (b01cxnp23032.gho.pok.ibm.com
 [9.57.198.27])
        by ppma02dal.us.ibm.com with ESMTP id 3581u9csbv-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 07 Dec 2020 15:41:29 +0000
Received: from b01ledav002.gho.pok.ibm.com (b01ledav002.gho.pok.ibm.com
 [9.57.199.107])
        by b01cxnp23032.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id 0B7FfSrD19267908
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 7 Dec 2020 15:41:28 GMT
Received: from b01ledav002.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 50FC5124054;
        Mon,  7 Dec 2020 15:41:28 +0000 (GMT)
Received: from b01ledav002.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 120BA124053;
        Mon,  7 Dec 2020 15:41:28 +0000 (GMT)
Received: from localhost.localdomain.com (unknown [9.85.174.71])
        by b01ledav002.gho.pok.ibm.com (Postfix) with ESMTP;
        Mon,  7 Dec 2020 15:41:27 +0000 (GMT)
From: Collin Walling <walling@linux.ibm.com>
To: kvm@vger.kernel.org, linux-kselftest@vger.kernel.org
Cc: frankja@linux.ibm.com, david@redhat.com, thuth@redhat.com,
        cohuck@redhat.com, borntraeger@de.ibm.com, pbonzini@redhat.com,
        imbrenda@linux.ibm.com
Subject: [PATCH v4] self_tests/kvm: sync_regs test for diag318
Date: Mon,  7 Dec 2020 10:41:25 -0500
Message-Id: <20201207154125.10322-1-walling@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.343,18.0.737
 definitions=2020-12-07_11:2020-12-04,2020-12-07 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 bulkscore=0 suspectscore=25
 malwarescore=0 phishscore=0 adultscore=0 clxscore=1015 spamscore=0
 mlxlogscore=999 mlxscore=0 priorityscore=1501 lowpriorityscore=0
 impostorscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2012070100
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The DIAGNOSE 0x0318 instruction, unique to s390x, is a privileged call
that must be intercepted via SIE, handled in userspace, and the
information set by the instruction is communicated back to KVM.

To test the instruction interception, an ad-hoc handler is defined which
simply has a VM execute the instruction and then userspace will extract
the necessary info. The handler is defined such that the instruction
invocation occurs only once. It is up to the caller to determine how the
info returned by this handler should be used.

The diag318 info is communicated from userspace to KVM via a sync_regs
call. This is tested During a sync_regs test, where the diag318 info is
requested via the handler, then the info is stored in the appropriate
register in KVM via a sync registers call.

If KVM does not support diag318, then the tests will print a message
stating that diag318 was skipped, and the asserts will simply test
against a value of 0.

Signed-off-by: Collin Walling <walling@linux.ibm.com>
Acked-by: Janosch Frank <frankja@linux.ibm.com>
Acked-by: Cornelia Huck <cohuck@redhat.com>
Signed-off-by: Collin Walling <walling@linux.ibm.com>
Acked-by: Janosch Frank <frankja@linux.ibm.com>
Acked-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 tools/testing/selftests/kvm/Makefile          |  2 +-
 .../kvm/include/s390x/diag318_test_handler.h  | 13 +++
 .../kvm/lib/s390x/diag318_test_handler.c      | 82 +++++++++++++++++++
 .../selftests/kvm/s390x/sync_regs_test.c      | 16 +++-
 4 files changed, 111 insertions(+), 2 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/include/s390x/diag318_test_handler.h
 create mode 100644 tools/testing/selftests/kvm/lib/s390x/diag318_test_handler.c

```
#### [PATCH v11 01/81] KVM: UAPI: add error codes used by the VM introspection code
##### From: =?utf-8?q?Adalbert_Laz=C4=83r?= <alazar@bitdefender.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Adalbert_Laz=C4=83r?=
 <alazar@bitdefender.com>
X-Patchwork-Id: 11956651
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 44FAAC4361B
	for <kvm@archiver.kernel.org>; Mon,  7 Dec 2020 20:47:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 18AA2238A0
	for <kvm@archiver.kernel.org>; Mon,  7 Dec 2020 20:47:10 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726188AbgLGUqy (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 7 Dec 2020 15:46:54 -0500
Received: from mx01.bbu.dsd.mx.bitdefender.com ([91.199.104.161]:41864 "EHLO
        mx01.bbu.dsd.mx.bitdefender.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726671AbgLGUqy (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 7 Dec 2020 15:46:54 -0500
Received: from smtp.bitdefender.com (smtp01.buh.bitdefender.com [10.17.80.75])
        by mx01.bbu.dsd.mx.bitdefender.com (Postfix) with ESMTPS id
 F1A1730462E0;
        Mon,  7 Dec 2020 22:46:11 +0200 (EET)
Received: from localhost.localdomain (unknown [91.199.104.27])
        by smtp.bitdefender.com (Postfix) with ESMTPSA id D30C03072785;
        Mon,  7 Dec 2020 22:46:11 +0200 (EET)
From: =?utf-8?q?Adalbert_Laz=C4=83r?= <alazar@bitdefender.com>
To: kvm@vger.kernel.org
Cc: virtualization@lists.linux-foundation.org,
 Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?q?Adalbert_Laz=C4=83r?= <alazar@bitdefender.com>
Subject: [PATCH v11 01/81] KVM: UAPI: add error codes used by the VM
 introspection code
Date: Mon,  7 Dec 2020 22:45:02 +0200
Message-Id: <20201207204622.15258-2-alazar@bitdefender.com>
In-Reply-To: <20201207204622.15258-1-alazar@bitdefender.com>
References: <20201207204622.15258-1-alazar@bitdefender.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

These new error codes help the introspection tool to identify the cause
of the introspection command failure and to recover from some error
cases or to give more information to the user.

Signed-off-by: Adalbert Lazăr <alazar@bitdefender.com>
---
 include/uapi/linux/kvm_para.h | 4 ++++
 1 file changed, 4 insertions(+)

```
#### [PATCH 1/2] x86/cpufeatures: Add the Virtual SPEC_CTRL featureFrom: Babu Moger <babu.moger@amd.com>
##### From: Babu Moger <babu.moger@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Babu Moger <babu.moger@amd.com>
X-Patchwork-Id: 11957005
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 4CBCEC1B0D9
	for <kvm@archiver.kernel.org>; Mon,  7 Dec 2020 22:39:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 04C56238E3
	for <kvm@archiver.kernel.org>; Mon,  7 Dec 2020 22:39:00 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728039AbgLGWiv (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 7 Dec 2020 17:38:51 -0500
Received: from mail-bn8nam12on2086.outbound.protection.outlook.com
 ([40.107.237.86]:2913
        "EHLO NAM12-BN8-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1725917AbgLGWiv (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 7 Dec 2020 17:38:51 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=f0JO43OQEYOwSsJ53fEgMAl/tyAv3gjeLdiuVmKUs2WX7iqHV8vlzhccVFXQvCzaI662RVCQHVye8IrQqJgMi9tZq6ZgjJ952thVtAHXWEYA3QvWGNtSfR4EH6mc6R04dQF2l+TNoD8pxbXJg8VRCDTVcwjRAn0iCymo6UOZsIK9f/zTCrEHEK4djVMYnAXe/NXkw7CgQxf2JwcM/sxF2rkPWU43eNIVFzE1lOita0MVGX4ZU5HT72s/Pjy1h+3wmiaj2/Y5tjgXsZQ5kS7srAfiJAigpqbYLvgNf/AECVMQXMoexNqhDrM1FAK6gM90HNE9y892baatw3QRSBJ2bA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=KoQYyh6yGJCrZs5BesxAmBbidfZrsBZzhpoIav534RY=;
 b=JGI26UA5PJ/KbF2UoqQYv1IsNZUCzeu3tlMO1k1M6woDVwhW5/Pbzs/yzNFqnWiDcn4Eoen0AvCkUyZmSzJgL260c3AEk4j7ajG5gFL4Ye9EFqVFWTOZYGH5EU5Im580Mf3mVCxBfhR/9YjzDswI99PkX/ZyKpHNihyTEclEk1ePay+O3vk/0bFC+WZyGGktd92A6pxbVswhnOCb2S2krBIVL8xSJbT74LOXpAXHrWhLESTSo7U5tR9MzGsHWfSU5X0eq8qbTYOcznfgIttQsw+ShW8BPsxKMzVWvEnxXbRlmRO7P9wCBcHl9AJXTG5zGR+G7ifBAYK9wA0YyiiO2Q==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=KoQYyh6yGJCrZs5BesxAmBbidfZrsBZzhpoIav534RY=;
 b=j8L1uFLsgE0k1/zNFGoIm/tdh7tUOSsU3R9K9mqtW0zuL54m0U3TLg6sN0lEz3jEiKiKDkvtJ0KGepj9+X9EWQo52trYf5zeJsOVrwlz+yVvPOAovYD4TfptA5iu8ezuKxFhCwd+uJh3bfW6S7JEPq/veVEyckkMzwa8UzE+CdA=
Authentication-Results: tencent.com; dkim=none (message not signed)
 header.d=none;tencent.com; dmarc=none action=none header.from=amd.com;
Received: from SN1PR12MB2560.namprd12.prod.outlook.com (2603:10b6:802:26::19)
 by SN1PR12MB2384.namprd12.prod.outlook.com (2603:10b6:802:25::25) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3632.22; Mon, 7 Dec
 2020 22:37:55 +0000
Received: from SN1PR12MB2560.namprd12.prod.outlook.com
 ([fe80::d877:baf6:9425:ece]) by SN1PR12MB2560.namprd12.prod.outlook.com
 ([fe80::d877:baf6:9425:ece%3]) with mapi id 15.20.3632.023; Mon, 7 Dec 2020
 22:37:54 +0000
Subject: [PATCH 1/2] x86/cpufeatures: Add the Virtual SPEC_CTRL feature
From: Babu Moger <babu.moger@amd.com>
To: pbonzini@redhat.com, tglx@linutronix.de, mingo@redhat.com,
        bp@alien8.de
Cc: fenghua.yu@intel.com, tony.luck@intel.com, wanpengli@tencent.com,
        kvm@vger.kernel.org, thomas.lendacky@amd.com, peterz@infradead.org,
        seanjc@google.com, joro@8bytes.org, x86@kernel.org,
        kyung.min.park@intel.com, linux-kernel@vger.kernel.org,
        krish.sadhukhan@oracle.com, hpa@zytor.com, mgross@linux.intel.com,
        vkuznets@redhat.com, kim.phillips@amd.com, wei.huang2@amd.com,
        jmattson@google.com
Date: Mon, 07 Dec 2020 16:37:51 -0600
Message-ID: <160738067105.28590.10158084163761735153.stgit@bmoger-ubuntu>
In-Reply-To: <160738054169.28590.5171339079028237631.stgit@bmoger-ubuntu>
References: <160738054169.28590.5171339079028237631.stgit@bmoger-ubuntu>
User-Agent: StGit/0.17.1-dirty
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: CH2PR03CA0021.namprd03.prod.outlook.com
 (2603:10b6:610:59::31) To SN1PR12MB2560.namprd12.prod.outlook.com
 (2603:10b6:802:26::19)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from [127.0.1.1] (165.204.77.1) by
 CH2PR03CA0021.namprd03.prod.outlook.com (2603:10b6:610:59::31) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3632.17 via Frontend
 Transport; Mon, 7 Dec 2020 22:37:52 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 2abbbe8a-3ef4-4531-6b6b-08d89b00bd39
X-MS-TrafficTypeDiagnostic: SN1PR12MB2384:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SN1PR12MB2384E171611A3B7C12C447C995CE0@SN1PR12MB2384.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:1227;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 ZbvmMG1b9VXHlo1Bar6PU5RPeVRGgeP6CTYV13eJcdpPFPYEC5u7ckMUhRRyXn/3ymWLdB3Y3gScnlSMHTrDcsmrS/mDYG5GRM21Fm+Gp8gmyqHUsDPGCOxltDmNhVsPtpQ3oNm/vyqb/iv5eZkMY2DgtWx0kikm8CWNLnHiUxZVTFNs3juzrkuQF4r64YP/bL62klGMHTu6tHQ22kEdRzCf2qVftCgkt9kg1KsM1WwOp04339wDmal5oFrETs1WK9D/b85I8OKwmtYmJa7PS8WuGGz0Lb9b+hA9F6NW+2eHap87MOHP5+VCiiMRnVDdiaGSkNlGUVhKT6nz+8I3Cw==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN1PR12MB2560.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(7916004)(346002)(396003)(39860400002)(376002)(366004)(136003)(2906002)(7416002)(9686003)(478600001)(8676002)(103116003)(16576012)(956004)(8936002)(186003)(86362001)(44832011)(66476007)(6486002)(52116002)(26005)(33716001)(66946007)(5660300002)(16526019)(66556008)(4326008)(316002);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: =?utf-8?q?y6QnE7/fhZUiW2XlWxt/uLr0OCoe8c?=
	=?utf-8?q?t7RPT2K8CB/CRULJ6mM0zK/N64iQ3O9crqZcSff85tbZxwAMVEHqAplahHOVA+VdF?=
	=?utf-8?q?LR73TnKKMiyQuoFiWoQVG5FNc0kWhPIMYAqgwI7D9Y19qlkmYbDfrVUJXYP/+TygG?=
	=?utf-8?q?DefdkuqfPIR1QE2fI8ysHLKVOs2q0yMu/ifuZ0JheKo/RRIwTzBIRXth/g9PE/k3I?=
	=?utf-8?q?wxmSBfsrB+ncyK5S3MhI59tmkrJoUa9OPZX6LmkwX1jT2Wfdw2G0apgYmiVLTsdgj?=
	=?utf-8?q?FzN/4+VmD2YIV4rNNCyMcb6WVNKFmxzZalsDO+SA0mYXxqYhYhG1/YVdLJ1uoCewx?=
	=?utf-8?q?hoTlXDUIBhSFY88KjQW/s9BKoFoa96m5dbjiuSGwfA6HEf8NZ8Y2/JI/i//ckM9Of?=
	=?utf-8?q?Z+TTUdtivKepQkYSaIGue/fhOIrm5LNHKVSaJoLvLWImRKqXCxt6LCbPCz7VEtcSE?=
	=?utf-8?q?G7a4DkFjYaLCd+5GPSiyp4CGF757TFwvQTe22H7ZU4gEMC2sjP11z5GE1UQqSA3Fc?=
	=?utf-8?q?kPP0zNKojKrj0BWwNd1ksQg6+OkfpYogKQ52mP1xYpgQ94QFgEgHP1VJ275rz3qnu?=
	=?utf-8?q?CqW9WmNcMZOAvE7dsUuRB7ezKxb0mhsHfKgtfSosoU3IOmcwPr3iyP32M7NsmthEJ?=
	=?utf-8?q?lX6ewPdJ0tzQ8KP6jOlAQsDZ2syumPXeZdR3XNYLXWXQ6VO++oAtAdAV7pLzPYDuP?=
	=?utf-8?q?GN8+xJSzGyDn+LIOBgH1QEXkzYbTuWqTu1KjOlE2uBm5pssEgcPT7bqbQyCmo62gI?=
	=?utf-8?q?xlMlXWMDpdQyJSl656U5ZTdfX26eoICfYgaAunPLEMtoxjSe/0dxq1zaaNK6EGr1H?=
	=?utf-8?q?VlJPOMDtWS4H3dKuPBiglos32cSVvtGPTW7elyesBiOG5kVr61hZwFaS5MhHqGrJw?=
	=?utf-8?q?zUZhu8QUMjjywywdevhjhLlc54IWe3YvTHEFgKG89Se8WBvVrVTi94bTMwmdKjRkx?=
	=?utf-8?q?bgdbpKhkQ3zafU0ER4T?=
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-AuthSource: SN1PR12MB2560.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 07 Dec 2020 22:37:54.4660
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 2abbbe8a-3ef4-4531-6b6b-08d89b00bd39
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 K6puj/OVV5ncsIarbv+aklFDXmN72WKI14Zk6WxMum8IJtcA0sV8utCmbSY8q1B9
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SN1PR12MB2384
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Newer AMD processors have a feature to virtualize the use of the SPEC_CTRL
MSR. This feature is identified via CPUID 0x8000000A_EDX[20]. When present,
the SPEC_CTRL MSR is automatically virtualized and no longer requires
hypervisor intervention.

Signed-off-by: Babu Moger <babu.moger@amd.com>
---
 arch/x86/include/asm/cpufeatures.h |    1 +
 1 file changed, 1 insertion(+)

```
