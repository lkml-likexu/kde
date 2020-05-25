#### [PATCH V8 01/15] KVM: MIPS: Define KVM_ENTRYHI_ASID to cpu_asid_mask(&boot_cpu_data)
##### From: Huacai Chen <chenhc@lemote.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Huacai Chen <chenhc@lemote.com>
X-Patchwork-Id: 11567295
Return-Path: <SRS0=k1lv=7G=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 498791392
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 24 May 2020 11:13:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 301DC207FB
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 24 May 2020 11:13:14 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="qxV8znGS"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728091AbgEXLNN (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 24 May 2020 07:13:13 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:45770 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727842AbgEXLNM (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 24 May 2020 07:13:12 -0400
Received: from mail-pj1-x1041.google.com (mail-pj1-x1041.google.com
 [IPv6:2607:f8b0:4864:20::1041])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 2B404C05BD43;
        Sun, 24 May 2020 04:13:11 -0700 (PDT)
Received: by mail-pj1-x1041.google.com with SMTP id t8so5128838pju.3;
        Sun, 24 May 2020 04:13:11 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id:in-reply-to:references;
        bh=WuyhKwGEWNBKEIWUWbDKke+4SVYP5RK6xsvzYyjPUOs=;
        b=qxV8znGSeA9I1xuySErWxun71aul8o1iyvqA3YomhBbQN56syQU3pdsebg2dHZ9Dl0
         kxDTCUAS9dqtG8H+zNc3WeWy51EYYYd27Ts/Qb2Uhe/6zBSZqiIQb1kt1Ua8cds2IdEw
         cbDc6AWq0eoLncc+uGIWahOJnxn7/F/8vpmwQ+Nm3BtJITi4A/onxgb4skd/7sbiVeIj
         0IUhnGmJrXnj1Mt4FcrA7MTcoBckY5TzJGa6Ujk23N2D2gMrzQlJnRTEffabHDdiiUnV
         Zqo1thlM+/lm3c2CjRIs9HsxrmUBXbiGqvVmhel4zbb10NMxy3XN7YOxds3cItYZ1fnk
         JOsQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id
         :in-reply-to:references;
        bh=WuyhKwGEWNBKEIWUWbDKke+4SVYP5RK6xsvzYyjPUOs=;
        b=q/8sz8rZuBeaFM+KpPbCpjM/I52upSGYhEA7Or5CHJiYi11javd5PDArxq7HKsDos4
         SPvz8whwHplzJ6UOBquxn1RlXzF9GBI0O+9K75pnos+LzIQcq+DQ0sja20qK3cOis1J9
         K5iyuefAr2xJXT4/RX7o9xQUBVxcCk1dXpbHt/GKkqlPmOBG9dN8wLi8UQsl2sHdznDg
         C4QQ7b+oPzI8b0VlaGjQid5F0RaSi3SIrF+wMW8rAmJsvCFv+4ZvPN0TRLVhflMS17er
         q0gVovjSg3/1AiguaAXC2I4e0f782zhEDklTcGn8MXvprpmFtZuYbWHLK0/RpJNQZrvQ
         adVw==
X-Gm-Message-State: AOAM531H9MZuOWZjcjRBwaic+8gb8QvnwKIKN8uNL0DHO6fsCKifMFyn
        zGkzDFFu4NcWx4PwcVTIlzfazaBhjURPBQ==
X-Google-Smtp-Source: 
 ABdhPJwBzT1LoSKouDtictZI3N5bJev1OiQg4Q/0sd5NJmGiumBvGZZxePmAV2IrixJ0Toaso82EtA==
X-Received: by 2002:a17:902:930b:: with SMTP id
 bc11mr23559343plb.2.1590318790688;
        Sun, 24 May 2020 04:13:10 -0700 (PDT)
Received: from software.domain.org (28.144.92.34.bc.googleusercontent.com.
 [34.92.144.28])
        by smtp.gmail.com with ESMTPSA id
 192sm1971719pfu.202.2020.05.24.04.13.07
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Sun, 24 May 2020 04:13:09 -0700 (PDT)
From: Huacai Chen <chenhc@lemote.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Thomas Bogendoerfer <tsbogend@alpha.franken.de>,
        Aleksandar Markovic <aleksandar.qemu.devel@gmail.com>
Cc: kvm@vger.kernel.org, linux-mips@vger.kernel.org,
        Fuxin Zhang <zhangfx@lemote.com>,
        Huacai Chen <chenhuacai@gmail.com>,
        Jiaxun Yang <jiaxun.yang@flygoat.com>,
        Xing Li <lixing@loongson.cn>,
        "Stable #4 . 9+" <stable@vger.kernel.org>,
        Huacai Chen <chenhc@lemote.com>
Subject: [PATCH V8 01/15] KVM: MIPS: Define KVM_ENTRYHI_ASID to
 cpu_asid_mask(&boot_cpu_data)
Date: Sun, 24 May 2020 19:13:25 +0800
Message-Id: <1590318819-24520-2-git-send-email-chenhc@lemote.com>
X-Mailer: git-send-email 2.7.0
In-Reply-To: <1590318819-24520-1-git-send-email-chenhc@lemote.com>
References: <1590318819-24520-1-git-send-email-chenhc@lemote.com>
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

Cc: Stable <stable@vger.kernel.org>  #4.9+
Reviewed-by: Aleksandar Markovic <aleksandar.qemu.devel@gmail.com>
Signed-off-by: Xing Li <lixing@loongson.cn>
[Huacai: Change current_cpu_data to boot_cpu_data for optimization]
Signed-off-by: Huacai Chen <chenhc@lemote.com>
---
 arch/mips/include/asm/kvm_host.h | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [linux-next RFC v2] mm/gup.c: Convert to use get_user_{page|pages}_fast_only()
##### From: Souptick Joarder <jrdr.linux@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Souptick Joarder <jrdr.linux@gmail.com>
X-Patchwork-Id: 11567145
Return-Path: <SRS0=k1lv=7G=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 58DE960D
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 24 May 2020 04:19:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3602620812
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 24 May 2020 04:19:37 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="SKwou8TE"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725821AbgEXETU (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 24 May 2020 00:19:20 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:38490 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725300AbgEXETS (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 24 May 2020 00:19:18 -0400
Received: from mail-pf1-x443.google.com (mail-pf1-x443.google.com
 [IPv6:2607:f8b0:4864:20::443])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 8078CC061A0E;
        Sat, 23 May 2020 21:19:18 -0700 (PDT)
Received: by mail-pf1-x443.google.com with SMTP id n18so7180501pfa.2;
        Sat, 23 May 2020 21:19:18 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=nI7E7mDYIZ61oHLf9W/arr0PR7H6a7nLS1eN6Z5GiPg=;
        b=SKwou8TE1YQ+4ESVLgMDigH9YD5+f2R5IBahu2GmE4moAfHfdvADANaFTY7lOCaD6k
         heHfbWB3VQzbQc4u8GE09NfCAOAxh6x/bFPMhkwMh4hriLnlv3xMg/dqD2EFwtgqi5a+
         5k5bSw+qfEUQ+V2qw2lktSJLUjzR66s14480r3A7GyvgjCWyJWd1KgoOcq9b5ARCaFTi
         0pg/6XdKUL0cT5CLfUNebadHwNfJjcUiEkpLdv5jYZRwpW3Jn+0i8TWXmepa5rFQQMNW
         HBlue3L/mbfsuRVCPA9/MPMfsK/HlZ0m2hKLVN/vsgo0nZlERPQYK7Nv5MUGmauMTyRR
         RJkA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=nI7E7mDYIZ61oHLf9W/arr0PR7H6a7nLS1eN6Z5GiPg=;
        b=nIAtw58CTsZ9sJvpduitzbhQzTGUbSYvHiGQoJ5FYohF2meEtV04t1scFNo+n2y/kk
         0NU/IPLJB3xLRHZYiGdl+onTwbFGdyvJ9BWIijt0n7UaglTuMxpCSdUzDAQyMzLp2TbP
         Q/n594a2Usb5nc0/tX6aHt1tb6hPw3SEBbTFnYcIOw4J3s4Xu8/CjiKAiBGFqcz33PbM
         Oj+5PBWyLxKeISf7+Dbwf53SGxW5o5kmr2d0Q4VMRR+XYNDDlr1A10opOnGEFckySFVg
         +Z8VlOmhV4mnK3Q4B+9T+23glw7Siw6yAxvsy1hfAqSWSProEUagyqnQRC4YNcpw6/8V
         L++A==
X-Gm-Message-State: AOAM530S7/HZoYRDEygfGGLxbyR9hrg3qPR1Fe2hawY0waplehgabdFe
        6wqiw/yrt5PEdO1lHaVDaU59wke4
X-Google-Smtp-Source: 
 ABdhPJx76K603I8mK1DZzCQ6qFXjZ45wWgT8uW3UzUi5xHivw3zZc4RuAAi69DNQPRBXz6t6UrZ4OQ==
X-Received: by 2002:aa7:9f5a:: with SMTP id h26mr10894617pfr.51.1590293957683;
        Sat, 23 May 2020 21:19:17 -0700 (PDT)
Received: from jordon-HP-15-Notebook-PC.domain.name ([122.167.154.105])
        by smtp.gmail.com with ESMTPSA id
 z16sm9540613pfq.125.2020.05.23.21.19.10
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Sat, 23 May 2020 21:19:16 -0700 (PDT)
From: Souptick Joarder <jrdr.linux@gmail.com>
To: paulus@ozlabs.org, mpe@ellerman.id.au, benh@kernel.crashing.org,
        akpm@linux-foundation.org, peterz@infradead.org, mingo@redhat.com,
        acme@kernel.org, mark.rutland@arm.com,
        alexander.shishkin@linux.intel.com, jolsa@redhat.com,
        namhyung@kernel.org, pbonzini@redhat.com, sfr@canb.auug.org.au,
        rppt@linux.ibm.com, aneesh.kumar@linux.ibm.com, msuchanek@suse.de
Cc: kvm-ppc@vger.kernel.org, linuxppc-dev@lists.ozlabs.org,
        linux-kernel@vger.kernel.org, linux-mm@kvack.org,
        kvm@vger.kernel.org, Souptick Joarder <jrdr.linux@gmail.com>,
        John Hubbard <jhubbard@nvidia.com>,
        Matthew Wilcox <willy@infradead.org>
Subject: [linux-next RFC v2] mm/gup.c: Convert to use
 get_user_{page|pages}_fast_only()
Date: Sun, 24 May 2020 09:57:14 +0530
Message-Id: <1590294434-19125-1-git-send-email-jrdr.linux@gmail.com>
X-Mailer: git-send-email 1.9.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

API __get_user_pages_fast() renamed to get_user_pages_fast_only()
to align with pin_user_pages_fast_only().

As part of this we will get rid of write parameter. Instead caller
will pass FOLL_WRITE to get_user_pages_fast_only(). This will not
change any existing functionality of the API.

All the callers are changed to pass FOLL_WRITE.

There are few places where 1 is passed to 2nd parameter of
__get_user_pages_fast() and return value is checked for 1
like [1]. Those are replaced with new inline
get_user_page_fast_only().

[1] if (__get_user_pages_fast(hva, 1, 1, &page) == 1)

Updated the documentation of the API.

Signed-off-by: Souptick Joarder <jrdr.linux@gmail.com>
Cc: John Hubbard <jhubbard@nvidia.com>
Cc: Matthew Wilcox <willy@infradead.org>
---
v2:
	Updated the subject line and change log.
	Address Matthew's comment to fix a bug and added
	new inline get_user_page_fast_only().

 arch/powerpc/kvm/book3s_64_mmu_hv.c    |  2 +-
 arch/powerpc/kvm/book3s_64_mmu_radix.c |  2 +-
 arch/powerpc/perf/callchain_64.c       |  4 +---
 include/linux/mm.h                     | 10 ++++++++--
 kernel/events/core.c                   |  4 ++--
 mm/gup.c                               | 29 ++++++++++++++++-------------
 virt/kvm/kvm_main.c                    |  8 +++-----
 7 files changed, 32 insertions(+), 27 deletions(-)

```
