#### [kvm-unit-tests PATCH 1/6] arm64: microbench: get correct ipi recieved num
##### From: Jingyi Wang <wangjingyi11@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jingyi Wang <wangjingyi11@huawei.com>
X-Patchwork-Id: 11554097
Return-Path: <SRS0=6WZD=67=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4BC5C1746
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 17 May 2020 10:11:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3E2D3206D5
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 17 May 2020 10:11:33 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727882AbgEQKL3 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 17 May 2020 06:11:29 -0400
Received: from szxga05-in.huawei.com ([45.249.212.191]:4806 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1727834AbgEQKL2 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 17 May 2020 06:11:28 -0400
Received: from DGGEMS413-HUB.china.huawei.com (unknown [172.30.72.60])
        by Forcepoint Email with ESMTP id 2215CAA0C3E83D9B1840;
        Sun, 17 May 2020 18:11:24 +0800 (CST)
Received: from DESKTOP-FPN2511.china.huawei.com (10.173.222.58) by
 DGGEMS413-HUB.china.huawei.com (10.3.19.213) with Microsoft SMTP Server id
 14.3.487.0; Sun, 17 May 2020 18:11:13 +0800
From: Jingyi Wang <wangjingyi11@huawei.com>
To: <drjones@redhat.com>, <kvm@vger.kernel.org>,
        <kvmarm@lists.cs.columbia.edu>, <wangjingyi11@huawei.com>
CC: <maz@kernel.org>, <wanghaibin.wang@huawei.com>,
        <yuzenghui@huawei.com>, <eric.auger@redhat.com>
Subject: [kvm-unit-tests PATCH 1/6] arm64: microbench: get correct ipi
 recieved num
Date: Sun, 17 May 2020 18:08:55 +0800
Message-ID: <20200517100900.30792-2-wangjingyi11@huawei.com>
X-Mailer: git-send-email 2.14.1.windows.1
In-Reply-To: <20200517100900.30792-1-wangjingyi11@huawei.com>
References: <20200517100900.30792-1-wangjingyi11@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.173.222.58]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If ipi_exec() fails because of timeout, we shouldn't increase
the number of ipi received.

Signed-off-by: Jingyi Wang <wangjingyi11@huawei.com>
---
 arm/micro-bench.c | 4 +++-
 1 file changed, 3 insertions(+), 1 deletion(-)

```
#### [PATCH V6 01/15] KVM: MIPS: Define KVM_ENTRYHI_ASID to cpu_asid_mask(&boot_cpu_data)
##### From: Huacai Chen <chenhc@lemote.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Huacai Chen <chenhc@lemote.com>
X-Patchwork-Id: 11553871
Return-Path: <SRS0=6WZD=67=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4368914B7
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 17 May 2020 04:07:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 299DE207BB
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 17 May 2020 04:07:01 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="B2yMKegh"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726617AbgEQEHA (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 17 May 2020 00:07:00 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:48378 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726279AbgEQEHA (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 17 May 2020 00:07:00 -0400
Received: from mail-pj1-x1043.google.com (mail-pj1-x1043.google.com
 [IPv6:2607:f8b0:4864:20::1043])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 14E59C061A0C;
        Sat, 16 May 2020 21:07:00 -0700 (PDT)
Received: by mail-pj1-x1043.google.com with SMTP id nu7so501286pjb.0;
        Sat, 16 May 2020 21:07:00 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id:in-reply-to:references;
        bh=j/OSBdV9DXY2ETWsIc3eeYNxFXzAjwLns12YdEbp9AY=;
        b=B2yMKeghdKEalQL1S/6cpbziQB/gYSCUjWQq8KZc7BlNnE15ZV1g+FNLK1L12KtzKW
         zaUeGEGitoqvSfLH7ELQw5N0AYwW2CL5qnB9zdZxLI4CjdAt88AkdaJVuakXOkTabRWQ
         rq8B4t5xY98WbScJYvwcio9LlKB0bVooVyDve/r5pLS9PpCCyDIzUHYP390kzISUHf/T
         ihSmj0mZr2uHCWtqO4dB8JdS3o8hRiv6odiNAxIj/Hn9bp4J6iYFawkSjIgUXyKMPI1o
         YHcqawQ/MEmLSs+vBvQZdByS7zKZAnwrM0wQo7+Gm8CeA+nBrooTFuXp2/mKFe8PQz5/
         eB9g==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id
         :in-reply-to:references;
        bh=j/OSBdV9DXY2ETWsIc3eeYNxFXzAjwLns12YdEbp9AY=;
        b=eoyadwHHLY9BkPo5UoEMHeDubb1HqlRBC19RMy27aEyAxoH3m9Ujhel7xpDehgtwIO
         5xLhl1vHJpZJ0ePcvUQROvoLwcl6lCQpJdSwOCW6g1Rwdnnlwm/87K1Cf2HiE8seLpMd
         g3xgGTcZQ6ZjRMdAUwA6qOWSvXT++0gv9SAycaJekKx75fESl4FuEOLWhPMqmXsTAPoc
         6sOTX74Gu4ctkv9H/X+WZT/BFfvouVx+c3KuumX2pj7Fv5k/kcEtmejKAYpLpCngnHTG
         ORBwiNXKXIMhwUPKRG6CjYJXBIH+ImMhwRGVbLHAFHqmg06xEc0/hQrUrsracXUyfXxJ
         eIxw==
X-Gm-Message-State: AOAM530JNDTYKiqzrVTh7OCzS/wWsRaSCGYbdGQa1sTexPn8PO8zd4PI
        M8U+qKByjESDPYZosyq6J8g=
X-Google-Smtp-Source: 
 ABdhPJwdG4WjNuaZ0mEN6ll9DPFldhOiQbQ7WYxPL89UBUCmDLxP9iYuwEuUDqbnsoa+kQZPOuUbAw==
X-Received: by 2002:a17:90a:ee85:: with SMTP id
 i5mr11721106pjz.165.1589688419666;
        Sat, 16 May 2020 21:06:59 -0700 (PDT)
Received: from software.domain.org (28.144.92.34.bc.googleusercontent.com.
 [34.92.144.28])
        by smtp.gmail.com with ESMTPSA id
 n9sm5081630pjt.29.2020.05.16.21.06.54
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Sat, 16 May 2020 21:06:59 -0700 (PDT)
From: Huacai Chen <chenhc@lemote.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Thomas Bogendoerfer <tsbogend@alpha.franken.de>,
        Aleksandar Markovic <aleksandar.qemu.devel@gmail.com>
Cc: kvm@vger.kernel.org, linux-mips@vger.kernel.org,
        Fuxin Zhang <zhangfx@lemote.com>,
        Huacai Chen <chenhuacai@gmail.com>,
        Jiaxun Yang <jiaxun.yang@flygoat.com>,
        Xing Li <lixing@loongson.cn>, stable@vger.kernel.org,
        Huacai Chen <chenhc@lemote.com>
Subject: [PATCH V6 01/15] KVM: MIPS: Define KVM_ENTRYHI_ASID to
 cpu_asid_mask(&boot_cpu_data)
Date: Sun, 17 May 2020 12:05:58 +0800
Message-Id: <1589688372-3098-2-git-send-email-chenhc@lemote.com>
X-Mailer: git-send-email 2.7.0
In-Reply-To: <1589688372-3098-1-git-send-email-chenhc@lemote.com>
References: <1589688372-3098-1-git-send-email-chenhc@lemote.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Xing Li <lixing@loongson.cn>

The code in decode_config4() of arch/mips/kernel/cpu-probe.c

        asid_mask = MIPS_ENTRYHI_ASID;
        if (config4 & MIPS_CONF4_AE)
                asid_mask |= MIPS_ENTRYHI_ASIDX;
        set_cpu_asid_mask(c, asid_mask);

set asid_mask to cpuinfo->asid_mask.

So in order to support variable ASID_MASK, KVM_ENTRYHI_ASID should also
be changed to cpu_asid_mask(&boot_cpu_data).

Cc: stable@vger.kernel.org
Reviewed-by: Aleksandar Markovic <aleksandar.qemu.devel@gmail.com>
Signed-off-by: Xing Li <lixing@loongson.cn>
[Huacai: Change current_cpu_data to boot_cpu_data for optimization]
Signed-off-by: Huacai Chen <chenhc@lemote.com>
---
 arch/mips/include/asm/kvm_host.h | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH kvmtool] net: uip: Fix GCC 10 warning about checksum calculation
##### From: Andre Przywara <andre.przywara@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Andr=C3=A9_Przywara?=
 <andre.przywara@arm.com>
X-Patchwork-Id: 11554175
Return-Path: <SRS0=6WZD=67=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D24EB90
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 17 May 2020 15:28:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C46DA204EC
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 17 May 2020 15:28:56 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728046AbgEQP2z (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 17 May 2020 11:28:55 -0400
Received: from foss.arm.com ([217.140.110.172]:55194 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727981AbgEQP2z (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 17 May 2020 11:28:55 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 8D00531B;
        Sun, 17 May 2020 08:28:54 -0700 (PDT)
Received: from donnerap.arm.com (donnerap.cambridge.arm.com [10.1.197.25])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 BF0E93F52E;
        Sun, 17 May 2020 08:28:53 -0700 (PDT)
From: Andre Przywara <andre.przywara@arm.com>
To: Will Deacon <will@kernel.org>,
        Julien Thierry <julien.thierry.kdev@gmail.com>
Cc: Alexandru Elisei <alexandru.elisei@arm.com>, kvm@vger.kernel.org
Subject: [PATCH kvmtool] net: uip: Fix GCC 10 warning about checksum
 calculation
Date: Sun, 17 May 2020 16:28:49 +0100
Message-Id: <20200517152849.204717-1-andre.przywara@arm.com>
X-Mailer: git-send-email 2.17.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

GCC 10.1 generates a warning in net/ip/csum.c about exceeding a buffer
limit in a memcpy operation:
------------------
In function ‘memcpy’,
    inlined from ‘uip_csum_udp’ at net/uip/csum.c:58:3:
/usr/include/aarch64-linux-gnu/bits/string_fortified.h:34:10: error: writing 1 byte into a region of size 0 [-Werror=stringop-overflow=]
   34 |   return __builtin___memcpy_chk (__dest, __src, __len, __bos0 (__dest));
      |          ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
In file included from net/uip/csum.c:1:
net/uip/csum.c: In function ‘uip_csum_udp’:
include/kvm/uip.h:132:6: note: at offset 0 to object ‘sport’ with size 2 declared here
  132 |  u16 sport;
------------------

This warning originates from the code taking the address of the "sport"
member, then using that with some pointer arithmetic in a memcpy call.
GCC now sees that the object is only a u16, so copying 12 bytes into it
cannot be any good.
It's somewhat debatable whether this is a legitimate warning, as there
is enough storage at that place, and we knowingly use the struct and
its variabled-sized member at the end.

However we can also rewrite the code, to not abuse the "&" operation of
some *member*, but take the address of the struct itself.
This makes the code less dodgy, and indeed appeases GCC 10.

Signed-off-by: Andre Przywara <andre.przywara@arm.com>
Reported-by: Alexandru Elisei <alexandru.elisei@arm.com>
---
 net/uip/csum.c | 26 ++++++++++++--------------
 1 file changed, 12 insertions(+), 14 deletions(-)

```
