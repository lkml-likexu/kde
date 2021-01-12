#### [PATCH v5 01/16] KVM: x86/xen: fix Xen hypercall page msr handling
##### From: David Woodhouse <dwmw2@infradead.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Woodhouse <dwmw2@infradead.org>
X-Patchwork-Id: 12011635
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 0ABAFC43331
	for <kvm@archiver.kernel.org>; Mon, 11 Jan 2021 19:59:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D247D22BF3
	for <kvm@archiver.kernel.org>; Mon, 11 Jan 2021 19:59:38 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2391468AbhAKT7M (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 11 Jan 2021 14:59:12 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:52200 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2391460AbhAKT7J (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 11 Jan 2021 14:59:09 -0500
Received: from casper.infradead.org (casper.infradead.org
 [IPv6:2001:8b0:10b:1236::1])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 5FA13C0617B9
        for <kvm@vger.kernel.org>; Mon, 11 Jan 2021 11:58:11 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; q=dns/txt; c=relaxed/relaxed;
        d=infradead.org; s=casper.20170209;
 h=Sender:Content-Transfer-Encoding:
        MIME-Version:References:In-Reply-To:Message-Id:Date:Subject:Cc:To:From:
        Reply-To:Content-Type:Content-ID:Content-Description;
        bh=jn9vB4nTR5tbpnMqolft0PXhkvxxJugyPZVztcv18zg=;
 b=BO+nzdyBTb/qcWOkJhs8UuXdHK
        O2/RjdenMBxbDe6HQgQQDO06Y9VFvpGMSoGg2C6ZvL/BijH/P2e1sCF49qvGFcLAnHeBI63K19vsv
        s0AsZXBp1Ck9NfU7Jw00oeFa35SzdwS3pI0Xw+Cltsra0tFxWQamkaQL+5iNlurV4o/Lpovbzh4vO
        Vs3jbJUOU18cxG/HEg0vVjH4NSScu1mHRCS7azT4++nuGEzSDsxvBWmkBV/z8nM97MR50EPvdjlj1
        sEFfZJvj7UYYcVgqqDZykJnXOrvvK9EGgm1br6JdvI4z5E60SOhO4rUxJbCv0zgtCiVdl8Nfz7YSL
        NH6mKQKw==;
Received: from i7.infradead.org ([2001:8b0:10b:1:21e:67ff:fecb:7a92])
        by casper.infradead.org with esmtpsa (Exim 4.94 #2 (Red Hat Linux))
        id 1kz3Jf-003kSW-Rr; Mon, 11 Jan 2021 19:57:37 +0000
Received: from dwoodhou by i7.infradead.org with local (Exim 4.94 #2 (Red Hat
 Linux))
        id 1kz3Jf-0001HO-Dd; Mon, 11 Jan 2021 19:57:27 +0000
From: David Woodhouse <dwmw2@infradead.org>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Ankur Arora <ankur.a.arora@oracle.com>,
        Joao Martins <joao.m.martins@oracle.com>,
        Boris Ostrovsky <boris.ostrovsky@oracle.com>,
        Sean Christopherson <seanjc@google.com>, graf@amazon.com,
        iaslan@amazon.de, pdurrant@amazon.com, aagch@amazon.com,
        fandree@amazon.com, hch@infradead.org
Subject: [PATCH v5 01/16] KVM: x86/xen: fix Xen hypercall page msr handling
Date: Mon, 11 Jan 2021 19:57:10 +0000
Message-Id: <20210111195725.4601-2-dwmw2@infradead.org>
X-Mailer: git-send-email 2.29.2
In-Reply-To: <20210111195725.4601-1-dwmw2@infradead.org>
References: <20210111195725.4601-1-dwmw2@infradead.org>
MIME-Version: 1.0
Sender: David Woodhouse <dwmw2@infradead.org>
X-SRS-Rewrite: SMTP reverse-path rewritten from <dwmw2@infradead.org> by
 casper.infradead.org. See http://www.infradead.org/rpr.html
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Joao Martins <joao.m.martins@oracle.com>

Xen usually places its MSR at 0x40000000 or 0x40000200 depending on
whether it is running in viridian mode or not. Note that this is not
ABI guaranteed, so it is possible for Xen to advertise the MSR some
place else.

Given the way xen_hvm_config() is handled, if the former address is
selected, this will conflict with Hyper-V's MSR
(HV_X64_MSR_GUEST_OS_ID) which unconditionally uses the same address.

Given that the MSR location is arbitrary, move the xen_hvm_config()
handling to the top of kvm_set_msr_common() before falling through.

Signed-off-by: Joao Martins <joao.m.martins@oracle.com>
Signed-off-by: David Woodhouse <dwmw@amazon.co.uk>
---
 arch/x86/kvm/x86.c | 5 +++--
 1 file changed, 3 insertions(+), 2 deletions(-)

```
#### [PATCH] KVM: update depracated jump label API
##### From: Cun Li <cun.jia.li@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Cun Li <cun.jia.li@gmail.com>
X-Patchwork-Id: 12010993
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 09060C433E0
	for <kvm@archiver.kernel.org>; Mon, 11 Jan 2021 15:26:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A91B8225AC
	for <kvm@archiver.kernel.org>; Mon, 11 Jan 2021 15:26:36 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728122AbhAKP0O (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 11 Jan 2021 10:26:14 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:49746 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726890AbhAKP0N (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 11 Jan 2021 10:26:13 -0500
Received: from mail-pf1-x42e.google.com (mail-pf1-x42e.google.com
 [IPv6:2607:f8b0:4864:20::42e])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id AA678C061786;
        Mon, 11 Jan 2021 07:25:33 -0800 (PST)
Received: by mail-pf1-x42e.google.com with SMTP id h10so98806pfo.9;
        Mon, 11 Jan 2021 07:25:33 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=4hOSDGgkDnFPvYf9DJjuBTyvbvtjcYcDYsmPDVQCkDg=;
        b=UYN45O/J9mSramH9w5A9EwdD7SdqZrbkVsBvZHKdukFzZvoUQ8NPzR3XFh3mGR6z/i
         B7MEu+YU/RyTVyS2oLtsnq1SGSadC/KQxyEmWOxSQVu7kwuE+yHnjmetvc3GNZvCyDPv
         CU6HoCkun1F1Hz7vQL9wTCSn2HZHSOnLGTKTSrrwxUtxhk6Sg9DG8uG2VWNZMwilGTdi
         lWfgz6f4HDziUBO+AQOhQPhbmc/6jIxd/Eczybx2eB22l5YjXA1ps+JNZ3jwq3eR1vhj
         lebnTVdPunwuctwSPFzlY9/fn7XFUHfkBM0ZswUU2bGLq3x0XiSlp5aU0J/YerYb8kVA
         wK6A==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=4hOSDGgkDnFPvYf9DJjuBTyvbvtjcYcDYsmPDVQCkDg=;
        b=F8wqvrn5KsA5ckC3pxH12Ls7F0rQLJTUynfKL+LD7oXiG+OT0sQ8+D8qOfYrv4GH02
         dNSd0zl3JN0D5Rn9YIt7toolkQ/JNLaMUiOCXK/imDNUVqmp3kzt/Zxh1Bc9NU2P4o26
         2oqEv6ePSmdvw4HpWxmYy2nRdO5sRuyb65OiMsnkH0ejfPhWacZKE/Coy8H2H/PrqvZp
         /iNyYW4VXUSxmTbvsf29WzR0oGCgXKxYGNDMxrh3TWNsUH/SYmm8/MwFLG8b3S2O+0MT
         gmXMs1RK3Xjcm1FCv48IGoIOA+56UayurdjERFknOWixwE5+nFsW0LsykM0GRvQBWWB0
         IDXA==
X-Gm-Message-State: AOAM5313q4DUdzmYd5sIGJsJJoPPVoCzKp3wAXauy+dSadayAtscyhF1
        t3AK7Su9vqc42lHRyrNOeR8YfdUDU2k6cjiFmHw=
X-Google-Smtp-Source: 
 ABdhPJzMtPA8XCAbsqXwOgxYVDFx82LNqlBqMJ08fv6H1UuzMk2ut3SjFMdj2C+USgOUZlnP3Y7A2A==
X-Received: by 2002:a62:5e44:0:b029:1a4:daae:e765 with SMTP id
 s65-20020a625e440000b02901a4daaee765mr16733227pfb.8.1610378733172;
        Mon, 11 Jan 2021 07:25:33 -0800 (PST)
Received: from localhost.localdomain ([117.136.0.45])
        by smtp.gmail.com with ESMTPSA id
 h17sm18791126pfo.220.2021.01.11.07.25.24
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 11 Jan 2021 07:25:32 -0800 (PST)
From: Cun Li <cun.jia.li@gmail.com>
To: pbonzini@redhat.com
Cc: seanjc@google.com, vkuznets@redhat.com, wanpengli@tencent.com,
        jmattson@google.com, joro@8bytes.org, tglx@linutronix.de,
        mingo@redhat.com, bp@alien8.de, x86@kernel.org, hpa@zytor.com,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Cun Li <cun.jia.li@gmail.com>
Subject: [PATCH] KVM: update depracated jump label API
Date: Mon, 11 Jan 2021 23:24:35 +0800
Message-Id: <20210111152435.50275-1-cun.jia.li@gmail.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The use of 'struct static_key' and 'static_key_false' is
deprecated. Use the new API.

Signed-off-by: Cun Li <cun.jia.li@gmail.com>
---
 arch/x86/kvm/lapic.h         | 6 +++---
 arch/x86/kvm/mmu/mmu_audit.c | 4 ++--
 arch/x86/kvm/x86.c           | 2 +-
 3 files changed, 6 insertions(+), 6 deletions(-)

```
#### [PATCH 1/2] sysemu/runstate: Let runstate_is_running() return bool
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
 <philmd@redhat.com>
X-Patchwork-Id: 12010989
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-19.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 516E6C433DB
	for <kvm@archiver.kernel.org>; Mon, 11 Jan 2021 15:22:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 16636229CA
	for <kvm@archiver.kernel.org>; Mon, 11 Jan 2021 15:22:04 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731237AbhAKPWB (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 11 Jan 2021 10:22:01 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:37423 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1730627AbhAKPWA (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 11 Jan 2021 10:22:00 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1610378434;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=97BNT6jh6NRO0TVk+TL23RreQDhzFRma0TINePq+NK8=;
        b=gkISrOGj+re/41lTjOkWdcVMMaJMWpIBT1Bln1bCFxYZdv3LHcMD14FsqGWJmJJrs0v6HY
        TQ+2qNUyLHpXS12AK3JxwGaya7Sv12ZMHIg/QECG0TxArJWnBO2P+/wXdazOkNNWD/o0Qf
        sbIbuUKFYGtt8PUb2knBezRBaXVXfKM=
Received: from mail-ed1-f70.google.com (mail-ed1-f70.google.com
 [209.85.208.70]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-280-n7ta02GeOW-PDGuiDveqGw-1; Mon, 11 Jan 2021 10:20:32 -0500
X-MC-Unique: n7ta02GeOW-PDGuiDveqGw-1
Received: by mail-ed1-f70.google.com with SMTP id dh21so8361204edb.6
        for <kvm@vger.kernel.org>; Mon, 11 Jan 2021 07:20:32 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=97BNT6jh6NRO0TVk+TL23RreQDhzFRma0TINePq+NK8=;
        b=mdVCp523hSIxe6uzLpkDZU0/HTh7wjamcvq6iocZGOnK1ix2WgIqhzAFd1LqwRquOD
         LJcbHV+2+2XcdcO5QOja474US/ktRRucNaAnR9w9cCPfPGRoqlIkKKBQrhpus90b44Zc
         Dga8sfp/Nl4+rFD5xTFyOCyEkQc0cqivKpmsfs+GEL7b4mj/87FS6F8zi4umIenJrYpx
         fcnACB/0ZxLrVO2Eliobi7FoY+SgmKfGo3C4S2iX9WZ/BvJaphgtGFMZoAE7B3IjJKVv
         3TEuIOId6rg6BB9ai3tHezxLyfShwW1IE95sBK3mfKFuGq/y7ZHg84mbbJERt19wBmL7
         vOKA==
X-Gm-Message-State: AOAM5329r2mC9z/nC98BxJN5lK6ZeggL8QO7N7GjeWusCTR6nOfCDGiP
        lf7uwNNkc+DGj2Xh3PIvy9MWX6CWTYomjye/6lSpmrQWuecyopxj7hBjeTchAQSrPSvMZYOqfZI
        O3NIlME4pYpK5
X-Received: by 2002:aa7:cdc3:: with SMTP id h3mr14237006edw.52.1610378431356;
        Mon, 11 Jan 2021 07:20:31 -0800 (PST)
X-Google-Smtp-Source: 
 ABdhPJxfzQ4g/Xi77uXbjKsyJn2nZrlWGnmTOg2kIy8FkRbXj1BTf3rxwC5MxkZMkcW73D4xDrLEXw==
X-Received: by 2002:aa7:cdc3:: with SMTP id h3mr14236981edw.52.1610378431207;
        Mon, 11 Jan 2021 07:20:31 -0800 (PST)
Received: from x1w.redhat.com (129.red-88-21-205.staticip.rima-tde.net.
 [88.21.205.129])
        by smtp.gmail.com with ESMTPSA id c12sm76932edw.55.2021.01.11.07.20.28
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 11 Jan 2021 07:20:30 -0800 (PST)
From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>
To: qemu-devel@nongnu.org
Cc: Huacai Chen <chenhuacai@kernel.org>, Greg Kurz <groug@kaod.org>,
 "Michael S. Tsirkin" <mst@redhat.com>, qemu-trivial@nongnu.org,
 Amit Shah <amit@kernel.org>, Dmitry Fleytman <dmitry.fleytman@gmail.com>,
 qemu-arm@nongnu.org, John Snow <jsnow@redhat.com>, qemu-s390x@nongnu.org,
 Paul Durrant <paul@xen.org>, Anthony Perard <anthony.perard@citrix.com>,
 Eduardo Habkost <ehabkost@redhat.com>, =?utf-8?q?Philippe_Mathieu-Daud?=
	=?utf-8?q?=C3=A9?= <philmd@redhat.com>, Gerd Hoffmann <kraxel@redhat.com>,
 Kevin Wolf <kwolf@redhat.com>, Marcelo Tosatti <mtosatti@redhat.com>,
 Max Reitz <mreitz@redhat.com>, Alex Williamson <alex.williamson@redhat.com>,
 Aurelien Jarno <aurelien@aurel32.net>,
 Aleksandar Rikalo <aleksandar.rikalo@syrmia.com>,
 Marcel Apfelbaum <marcel.apfelbaum@gmail.com>,
 Jason Wang <jasowang@redhat.com>, Peter Maydell <peter.maydell@linaro.org>,
	=?utf-8?q?C=C3=A9dric_Le_Goater?= <clg@kaod.org>,
 Halil Pasic <pasic@linux.ibm.com>, Fam Zheng <fam@euphon.net>,
 qemu-ppc@nongnu.org, Paolo Bonzini <pbonzini@redhat.com>,
 kvm@vger.kernel.org, Stefano Stabellini <sstabellini@kernel.org>,
 xen-devel@lists.xenproject.org, Cornelia Huck <cohuck@redhat.com>,
 David Hildenbrand <david@redhat.com>, qemu-block@nongnu.org,
 Christian Borntraeger <borntraeger@de.ibm.com>,
 Sunil Muthuswamy <sunilmut@microsoft.com>,
 David Gibson <david@gibson.dropbear.id.au>,
 Richard Henderson <richard.henderson@linaro.org>, =?utf-8?q?Alex_Benn=C3=A9?=
	=?utf-8?q?e?= <alex.bennee@linaro.org>, Laurent Vivier <laurent@vivier.eu>,
 Thomas Huth <thuth@redhat.com>, Stefan Hajnoczi <stefanha@redhat.com>,
 Jiaxun Yang <jiaxun.yang@flygoat.com>
Subject: [PATCH 1/2] sysemu/runstate: Let runstate_is_running() return bool
Date: Mon, 11 Jan 2021 16:20:19 +0100
Message-Id: <20210111152020.1422021-2-philmd@redhat.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20210111152020.1422021-1-philmd@redhat.com>
References: <20210111152020.1422021-1-philmd@redhat.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

runstate_check() returns a boolean. runstate_is_running()
returns what runstate_check() returns, also a boolean.

Signed-off-by: Philippe Mathieu-Daudé <philmd@redhat.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Alex Bennée <alex.bennee@linaro.org>
---
 include/sysemu/runstate.h | 2 +-
 softmmu/runstate.c        | 2 +-
 2 files changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH 1/2] KVM: x86: introduce definitions to support static calls for kvm_x86_ops
##### From: Jason Baron <jbaron@akamai.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Baron <jbaron@akamai.com>
X-Patchwork-Id: 12011187
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-19.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B0C4FC433DB
	for <kvm@archiver.kernel.org>; Mon, 11 Jan 2021 17:22:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 75A4E22AAD
	for <kvm@archiver.kernel.org>; Mon, 11 Jan 2021 17:22:54 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2389455AbhAKRW3 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 11 Jan 2021 12:22:29 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:46598 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2389190AbhAKRW2 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 11 Jan 2021 12:22:28 -0500
Received: from mx0b-00190b01.pphosted.com (mx0b-00190b01.pphosted.com
 [IPv6:2620:100:9005:57f::1])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 4B25EC061794;
        Mon, 11 Jan 2021 09:21:48 -0800 (PST)
Received: from pps.filterd (m0050102.ppops.net [127.0.0.1])
        by m0050102.ppops.net-00190b01. (8.16.0.43/8.16.0.43) with SMTP id
 10BGxmHx031812;
        Mon, 11 Jan 2021 17:00:24 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=akamai.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references : in-reply-to :
 references; s=jan2016.eng;
 bh=dglWV6e1a4y6WpadEHuansAWTupX/SHWQYswrhyYurY=;
 b=FGkwO1S3tb/Ton5Y1/LvjasxFJQjkWLOATpznce2CGBeZ340pZ+p3YdMkOEAuHRSmkbu
 lZwgf8Z91mgA7tKzGJ2hS9lxz4qbPHLa5wTS1BNdCkq7cE2cWVMvx1sdYybMDW96jNGV
 izA9cYcIZ+QJxftYs/7XP8vMT3v1zRvAqMCZL1QGaYkmD2Vl2vOlZb0K0FbTRVle+40F
 RHzAsoZn6uRA9oY3+VbSFA+Y0DmqX0hLu8gomX94vYDaPXZ5ZEH2k6U01Xd/22IB86v0
 2QSjCMeC+uI5lEZdlGUdKlFhgurv0Im0I4jz3bM3v+aZ8Sqwo40p1OckUnldO8i/XSgR Mw==
Received: from prod-mail-ppoint4
 (a72-247-45-32.deploy.static.akamaitechnologies.com [72.247.45.32] (may be
 forged))
        by m0050102.ppops.net-00190b01. with ESMTP id 35yq20bute-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 11 Jan 2021 17:00:24 +0000
Received: from pps.filterd (prod-mail-ppoint4.akamai.com [127.0.0.1])
        by prod-mail-ppoint4.akamai.com (8.16.0.43/8.16.0.43) with SMTP id
 10BGn2GY017989;
        Mon, 11 Jan 2021 12:00:08 -0500
Received: from prod-mail-relay18.dfw02.corp.akamai.com ([172.27.165.172])
        by prod-mail-ppoint4.akamai.com with ESMTP id 35y8q31r00-1;
        Mon, 11 Jan 2021 12:00:07 -0500
Received: from bos-lpjec.145bw.corp.akamai.com (unknown [172.28.3.71])
        by prod-mail-relay18.dfw02.corp.akamai.com (Postfix) with ESMTP id
 58EB2400;
        Mon, 11 Jan 2021 17:00:07 +0000 (GMT)
From: Jason Baron <jbaron@akamai.com>
To: pbonzini@redhat.com, kvm@vger.kernel.org
Cc: tglx@linutronix.de, mingo@redhat.com, bp@alien8.de,
        peterz@infradead.org, aarcange@redhat.com, x86@kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH 1/2] KVM: x86: introduce definitions to support static calls
 for kvm_x86_ops
Date: Mon, 11 Jan 2021 11:57:27 -0500
Message-Id: 
 <ce483ce4a1920a3c1c4e5deea11648d75f2a7b80.1610379877.git.jbaron@akamai.com>
X-Mailer: git-send-email 2.7.4
In-Reply-To: <cover.1610379877.git.jbaron@akamai.com>
References: <cover.1610379877.git.jbaron@akamai.com>
In-Reply-To: <cover.1610379877.git.jbaron@akamai.com>
References: <cover.1610379877.git.jbaron@akamai.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.343,18.0.737
 definitions=2021-01-11_28:2021-01-11,2021-01-11 signatures=0
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 adultscore=0
 mlxscore=0 malwarescore=0
 spamscore=0 bulkscore=0 suspectscore=0 phishscore=0 mlxlogscore=486
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2101110098
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.343,18.0.737
 definitions=2021-01-11_28:2021-01-11,2021-01-11 signatures=0
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 adultscore=0
 priorityscore=1501
 mlxscore=0 clxscore=1015 lowpriorityscore=0 malwarescore=0 bulkscore=0
 mlxlogscore=392 spamscore=0 suspectscore=0 impostorscore=0 phishscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2101110099
X-Agari-Authentication-Results: mx.akamai.com;
 spf=${SPFResult} (sender IP is 72.247.45.32)
 smtp.mailfrom=jbaron@akamai.com smtp.helo=prod-mail-ppoint4
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Use static calls to improve kvm_x86_ops performance. Introduce the
definitions that will be used by a subsequent patch to actualize the
savings.

Note that all kvm_x86_ops are covered here except for 'pmu_ops' and
'nested ops'. I think they can be covered by static calls in a simlilar
manner, but were omitted from this series to reduce scope and because
I don't think they have as large of a performance impact.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: Borislav Petkov <bp@alien8.de>
Cc: Peter Zijlstra <peterz@infradead.org>
Cc: Andrea Arcangeli <aarcange@redhat.com>
Signed-off-by: Jason Baron <jbaron@akamai.com>
---
 arch/x86/include/asm/kvm_host.h | 65 +++++++++++++++++++++++++++++++++++++++++
 arch/x86/kvm/x86.c              |  5 ++++
 2 files changed, 70 insertions(+)

```
