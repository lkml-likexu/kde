#### [PATCH] dynamically allocate struct cpumask
##### From: Nick Desaulniers <nick.desaulniers@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Nick Desaulniers <nick.desaulniers@gmail.com>
X-Patchwork-Id: 11352125
Return-Path: <SRS0=3aXV=3Q=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C6D2D13A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 27 Jan 2020 07:16:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 9B6DC214AF
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 27 Jan 2020 07:16:26 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="tsfuDBGT"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726670AbgA0HQS (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 27 Jan 2020 02:16:18 -0500
Received: from mail-ot1-f66.google.com ([209.85.210.66]:44622 "EHLO
        mail-ot1-f66.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725840AbgA0HQS (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 27 Jan 2020 02:16:18 -0500
Received: by mail-ot1-f66.google.com with SMTP id h9so7404093otj.11;
        Sun, 26 Jan 2020 23:16:17 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=ZTshCe94WzSsfXve6ziu+qTyps0fLQU+BDDkCbT6Bso=;
        b=tsfuDBGTQVhy70maJJPR3yaIKX8BjW23nAIzNWcWsDqNiB/oBXDoWDJ1whQefG8H5T
         qA+zgESqYPhbL05359SxdqjN7XPsc4ZCVcF60/E3vAaWD8dyjnpXX28Bw5HW44X/bShJ
         IspH7PC33TbNJdg9v4cXf5eQGf0WRNIbH5gI0DPlFwQAM2ZU/+tQtoN+KcJK15Uw4zgj
         AX5NwHYvM2nrcqgjzy2uOE8dE1NndLkC3lfJU+MUH4T9vVKIR5yoBQYrclHpQuUBjq5A
         MMAZ4I80FDACK65hhPDSWN3aS18HSk1chsTDXMUCsJy4Dh/Ppk5sCK+P9WP6kjloGkb6
         Lu+w==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=ZTshCe94WzSsfXve6ziu+qTyps0fLQU+BDDkCbT6Bso=;
        b=oE35V4duXWT75m32qjpdodBvoe5fnRW5N+jSjPEmxTV8U1U2LQmzbWUMVJE1Kwb7vA
         Thc4hvMFWlaITAwG0KwPdEqVmXvuCcVJFOlrU+JiwAhJ6ny3KKbL1e7e4WnCIC1oBM0/
         mL8L+Hyb4GNO+dMi5571Z+tOchCy+Ehv//R/cuk+rfVLpjspUWsAjxZsMmpgIhhytvsR
         198qC9qmrOBhhREaCthwP2tElnn+myfv7uZQQanKdBEA+qST+l54uGSPo/SnlcO5Phfk
         QyHqC4UC9mDn5Hej9lsJHFZ8Z/blrzHD2VGJl/fLpGZcvzX9FtnUSzK1NSMSkREn62oi
         h8qA==
X-Gm-Message-State: APjAAAVqM5TAOgHE3z7rJpqmHcIqs0kKlAiz0hCIEyABkolwCylB0EUN
        p0TO5upCK9q6IgseX5jB8UI=
X-Google-Smtp-Source: 
 APXvYqyBvsPV5HUfCbEOF6ZmFCmj7SSgxfXyaKHBatxbogtKM0leCRK+ExTQvjrYuSeo/zgeV0umsQ==
X-Received: by 2002:a9d:729c:: with SMTP id t28mr8584637otj.66.1580109377176;
        Sun, 26 Jan 2020 23:16:17 -0800 (PST)
Received: from nick-Blade-Stealth.attlocal.net
 (23-121-157-107.lightspeed.sntcca.sbcglobal.net. [23.121.157.107])
        by smtp.googlemail.com with ESMTPSA id
 n25sm4500248oic.6.2020.01.26.23.16.14
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Sun, 26 Jan 2020 23:16:16 -0800 (PST)
From: Nick Desaulniers <nick.desaulniers@gmail.com>
To: pbonzini@redhat.com, tglx@linutronix.de, mingo@redhat.com,
        bp@alien8.de
Cc: Nick Desaulniers <nick.desaulniers@gmail.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        "H. Peter Anvin" <hpa@zytor.com>, x86@kernel.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        clang-built-linux@googlegroups.com
Subject: [PATCH] dynamically allocate struct cpumask
Date: Sun, 26 Jan 2020 23:16:02 -0800
Message-Id: <20200127071602.11460-1-nick.desaulniers@gmail.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This helps avoid avoid a potentially large stack allocation.

When building with:
$ make CC=clang arch/x86/ CFLAGS=-Wframe-larger-than=1000
The following warning is observed:
arch/x86/kernel/kvm.c:494:13: warning: stack frame size of 1064 bytes in
function 'kvm_send_ipi_mask_allbutself' [-Wframe-larger-than=]
static void kvm_send_ipi_mask_allbutself(const struct cpumask *mask, int
vector)
            ^
Debugging with:
https://github.com/ClangBuiltLinux/frame-larger-than
via:
$ python3 frame_larger_than.py arch/x86/kernel/kvm.o \
  kvm_send_ipi_mask_allbutself
points to the stack allocated `struct cpumask newmask` in
`kvm_send_ipi_mask_allbutself`. The size of a `struct cpumask` is
potentially large, as it's CONFIG_NR_CPUS divided by BITS_PER_LONG for
the target architecture. CONFIG_NR_CPUS for X86_64 can be as high as
8192, making a single instance of a `struct cpumask` 1024 B.

Signed-off-by: Nick Desaulniers <nick.desaulniers@gmail.com>
---
 arch/x86/kernel/kvm.c | 10 ++++++----
 1 file changed, 6 insertions(+), 4 deletions(-)

```
#### [PATCH] kvm: selftests: Introduce num-pages conversion utilities
##### From: Andrew Jones <drjones@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11352931
Return-Path: <SRS0=3aXV=3Q=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0E968924
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 27 Jan 2020 17:04:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E0A90214D8
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 27 Jan 2020 17:04:15 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="U/7/WaBz"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726099AbgA0REO (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 27 Jan 2020 12:04:14 -0500
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:52488 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1725845AbgA0REO (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 27 Jan 2020 12:04:14 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1580144653;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=MZLoh5Tjj+Hm+iXUIZGeRq3iuD5be54ScqNixZPGvlE=;
        b=U/7/WaBzq/JYHMNEOwA8oUOO/YEtzxpKe3gJRuUqbRDK8GkID+ipcPuUlnvAyXxnrNFfA7
        hwPtxVQHKP/q+4yoRhR9QzqjjCVNBBBVQHBJ7vmxluOK/81zaT7mwn3RYgYoEFxjwPO+aE
        vPXGQNe/gDepVlc8WuZkcLnLrw0F8uU=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-399-W3tzF6zhOj2dqWmbncTGJg-1; Mon, 27 Jan 2020 12:04:09 -0500
X-MC-Unique: W3tzF6zhOj2dqWmbncTGJg-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 62CB218C8C30;
        Mon, 27 Jan 2020 17:04:08 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.43.2.160])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 3EC4710018FF;
        Mon, 27 Jan 2020 17:04:07 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, thuth@redhat.com, bgardon@google.com
Subject: [PATCH] kvm: selftests: Introduce num-pages conversion utilities
Date: Mon, 27 Jan 2020 18:04:05 +0100
Message-Id: <20200127170405.17503-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Guests and hosts don't have to have the same page size. This means
calculations are necessary when selecting the number of guest pages
to allocate in order to ensure the number is compatible with the
host. Provide utilities to help with those calculations.

Signed-off-by: Andrew Jones <drjones@redhat.com>
---
 tools/testing/selftests/kvm/dirty_log_test.c  |  3 +--
 .../testing/selftests/kvm/include/kvm_util.h  |  3 +++
 tools/testing/selftests/kvm/lib/kvm_util.c    | 26 +++++++++++++++++++
 3 files changed, 30 insertions(+), 2 deletions(-)

```
#### [kvmtool RFC PATCH v2 1/8] update_headers: Sync-up ABI headers with Linux-5.5-rc3
##### From: Anup Patel <Anup.Patel@wdc.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Anup Patel <Anup.Patel@wdc.com>
X-Patchwork-Id: 11352593
Return-Path: <SRS0=3aXV=3Q=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2D0BF924
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 27 Jan 2020 12:36:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 00AA220CC7
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 27 Jan 2020 12:36:05 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=wdc.com header.i=@wdc.com header.b="T9pPwsAY";
	dkim=pass (1024-bit key) header.d=sharedspace.onmicrosoft.com
 header.i=@sharedspace.onmicrosoft.com header.b="dUZGJ8HF"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730078AbgA0MgE (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 27 Jan 2020 07:36:04 -0500
Received: from esa4.hgst.iphmx.com ([216.71.154.42]:4509 "EHLO
        esa4.hgst.iphmx.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729868AbgA0MgD (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 27 Jan 2020 07:36:03 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=simple/simple;
  d=wdc.com; i=@wdc.com; q=dns/txt; s=dkim.wdc.com;
  t=1580128562; x=1611664562;
  h=from:to:cc:subject:date:message-id:references:
   in-reply-to:content-transfer-encoding:mime-version;
  bh=9uAyxwPTbPHGRWGGdDPJKb3hPSPge7ga0ymvBLIQCjE=;
  b=T9pPwsAYlWGHcO8z5NPptLze70a5nl+Tv0sQXA4Q41bDbL76j+ZULSOn
   mi2sFPqY96lkhxQc9jggRDT2oX5a3tjPJF3VObsyhRpiRcmi35ozaFNcz
   uc1INjvUQLHzlU2J1L9Aw7aCuO+/AKUuFjR7EwAbtLA7CydLqy8fO6meg
   BimNgXRahqTItR6cI7fep9I9IvP+3bxWqC3i0H7T6Lzw3/GcPVgYIL6Fi
   eDB6owj33Wka9IsZhaGRXo/2EXaWF8ynIFDV97HdDmYOH16GbAtmGgFKw
   s7B4EL+7x4cbp2g21rIEqSbBVeOXv3ppf4PX9ubrjlnjaOIaVt+By76CU
   g==;
IronPort-SDR: 
 fsOLWJarsRyPf8E8BdyN5iGfQQz6x00MHwgMqRRedRuU4lEZ+VnJHwEIfx9sQ9YYrkMTBOOFIt
 KkNrCcyMRsHqtr0CRWUOgI8EKy6wqLhHo4Mh+W3xunu6IZr3kDD91OmRgMsszbCAyCbO01W0ei
 34lT2p/+wEI9mgFFG9gOhQ0mIoL8yoiLwVBcSFUVhBJkG6PnLTnuuBnLSKhTkfBnWrR62XM+0s
 LW6bAvbrKXsHHL74I447tXwGKuGkohe04uhBeJyFIGVzxu8mND20HqseUoUtExh2Bz5HbhNQPF
 dzo=
X-IronPort-AV: E=Sophos;i="5.70,369,1574092800";
   d="scan'208";a="128476082"
Received: from mail-mw2nam12lp2048.outbound.protection.outlook.com (HELO
 NAM12-MW2-obe.outbound.protection.outlook.com) ([104.47.66.48])
  by ob1.hgst.iphmx.com with ESMTP; 27 Jan 2020 20:36:02 +0800
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=nu6WBoiKvKpX2Go97ayYnLQev5oJ6cf+ayTMC9RDrlH+wO6Wyt7Afluuu+a4yCitRScg9cwgmSQeYGB8sNqwFh5sNpsyuP19+MX0g4Z6y7oWdSczf6jyc/vesF9NHA/FdgydFFdi6fk9P+o07jaBevs+7u/oxCQbVkDQXUEFwwIY1MKlrxumKdWt3UnUCjDjpmeKUls433otWFA2a98z9UEnlf5b7DSnWDDBXD2q+3FUZM+1DDhvb6QLzWfFgUwS/Vr2pcVNys58PeArdTq5zXsDUwZJO5wLaJTtK1dFViOiYqdCbMPyy1eB8tfA9Gx1enKuTxYYDbstIvMLSs081Q==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=Z4YkFa03dgbiSlO2HLH5jlHKon49iUZYuIiYSldGZj4=;
 b=b7JYaXMdO/vV39mMvjhZPIp5oY1h0RhGLtoIt55K7OsJV7dx/jw1PvqXQ1e09zbNwkbLJ+6R7CzwYfewOXTF2r8MUj34mUABfMw148r2W3VyYNFx6u7NaVn/cPYPcJpfPplFddQO8OBSjo3c4SQwpMpuHqcZvx+op4LYEeL6hN95UUPrdf2R7aS2gvTeYu6gdfyKPYIGAXF9mkhj91LHDAyVxOGCV0cBQTdj/gb3xVM+IcgqzGpeXZHCXtNtbQqOgPzjWO0PacV7zNv+E7PISJNGt2f2uoEtHoCEmxowOT4LBj8YoK5aMf90sl9SV5BM8lPIF3uIlyftE+YklWLtNg==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=wdc.com; dmarc=pass action=none header.from=wdc.com; dkim=pass
 header.d=wdc.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=sharedspace.onmicrosoft.com; s=selector2-sharedspace-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=Z4YkFa03dgbiSlO2HLH5jlHKon49iUZYuIiYSldGZj4=;
 b=dUZGJ8HFJS7WXGFcVQyjelM65oL5MgQDMMXD0WKL70eBqOkmOuAUlNNhtDMvXr0HqEOqdS99ENegqFI9RJi1sC1IboswQX070P3z2EtdOdk6Hevfv3A/KS98y/K8X+BDAvf/HbsnWTuOYGwIggw8Mdwo0ZXlYft421PHG4Jbroo=
Received: from MN2PR04MB6061.namprd04.prod.outlook.com (20.178.246.15) by
 MN2PR04MB6735.namprd04.prod.outlook.com (10.186.147.148) with Microsoft SMTP
 Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.2665.22; Mon, 27 Jan 2020 12:36:01 +0000
Received: from MN2PR04MB6061.namprd04.prod.outlook.com
 ([fe80::a9a0:3ffa:371f:ad89]) by MN2PR04MB6061.namprd04.prod.outlook.com
 ([fe80::a9a0:3ffa:371f:ad89%7]) with mapi id 15.20.2665.017; Mon, 27 Jan 2020
 12:36:01 +0000
Received: from wdc.com (49.207.48.168) by
 MA1PR01CA0095.INDPRD01.PROD.OUTLOOK.COM (2603:1096:a00:1::11) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.2665.22 via Frontend
 Transport; Mon, 27 Jan 2020 12:35:57 +0000
From: Anup Patel <Anup.Patel@wdc.com>
To: Will Deacon <will.deacon@arm.com>
CC: Paolo Bonzini <pbonzini@redhat.com>,
        Atish Patra <Atish.Patra@wdc.com>,
        Alistair Francis <Alistair.Francis@wdc.com>,
        Anup Patel <anup@brainfault.org>,
        "kvm@vger.kernel.org" <kvm@vger.kernel.org>,
        "kvm-riscv@lists.infradead.org" <kvm-riscv@lists.infradead.org>,
        Anup Patel <Anup.Patel@wdc.com>
Subject: [kvmtool RFC PATCH v2 1/8] update_headers: Sync-up ABI headers with
 Linux-5.5-rc3
Thread-Topic: [kvmtool RFC PATCH v2 1/8] update_headers: Sync-up ABI headers
 with Linux-5.5-rc3
Thread-Index: AQHV1Q5VSbgZvVYGzUe/2Q+qCGEMkA==
Date: Mon, 27 Jan 2020 12:36:01 +0000
Message-ID: <20200127123527.106825-2-anup.patel@wdc.com>
References: <20200127123527.106825-1-anup.patel@wdc.com>
In-Reply-To: <20200127123527.106825-1-anup.patel@wdc.com>
Accept-Language: en-US
Content-Language: en-US
X-MS-Has-Attach: 
X-MS-TNEF-Correlator: 
x-clientproxiedby: MA1PR01CA0095.INDPRD01.PROD.OUTLOOK.COM
 (2603:1096:a00:1::11) To MN2PR04MB6061.namprd04.prod.outlook.com
 (2603:10b6:208:d8::15)
authentication-results: spf=none (sender IP is )
 smtp.mailfrom=Anup.Patel@wdc.com;
x-ms-exchange-messagesentrepresentingtype: 1
x-mailer: git-send-email 2.17.1
x-originating-ip: [49.207.48.168]
x-ms-publictraffictype: Email
x-ms-office365-filtering-ht: Tenant
x-ms-office365-filtering-correlation-id: c620bad7-dab8-4784-e753-08d7a325776c
x-ms-traffictypediagnostic: MN2PR04MB6735:
x-ms-exchange-transport-forked: True
x-microsoft-antispam-prvs: 
 <MN2PR04MB67359AB2449D890FE67CA40F8D0B0@MN2PR04MB6735.namprd04.prod.outlook.com>
wdcipoutbound: EOP-TRUE
x-ms-oob-tlc-oobclassifiers: OLM:541;
x-forefront-prvs: 02951C14DC
x-forefront-antispam-report: 
 SFV:NSPM;SFS:(10019020)(4636009)(39860400002)(136003)(396003)(366004)(346002)(376002)(189003)(199004)(2616005)(956004)(44832011)(86362001)(186003)(16526019)(4326008)(54906003)(2906002)(5660300002)(55016002)(26005)(316002)(6916009)(55236004)(71200400001)(8886007)(8936002)(8676002)(6666004)(1006002)(81166006)(81156014)(36756003)(52116002)(7696005)(1076003)(66946007)(478600001)(64756008)(66556008)(66446008)(66476007);DIR:OUT;SFP:1102;SCL:1;SRVR:MN2PR04MB6735;H:MN2PR04MB6061.namprd04.prod.outlook.com;FPR:;SPF:None;LANG:en;PTR:InfoNoRecords;MX:1;A:1;
x-ms-exchange-senderadcheck: 1
x-microsoft-antispam: BCL:0;
x-microsoft-antispam-message-info: 
 RFsymJo+opCHZ+oLA6qzRRylPduH15IjMEbeiuzxHb2nvpOBhCxqbGpRcO8H3w/h4N06uQf3+WcCF+DgNJT8Z+2//vvdNi/51OBUE2avQ0OnSUDm5R8Ii3YUTeuhDSUxG9ygpc8bXbhg/PvjPqZbKvp8E3N0Bfp6Ig+pWdp42s2OkakWm5OzBsKhsOqCK+ZkIpJXEDLy+ETJkhzdk64nijO3idzm8zzlCz20CP2u/pkqG190K242LEdFGMkVDpsAiwGWoHVh1YjOi3NSqf0vlyhGARXA4bpAq7Ggs2Bnu2AQ/cAeHK1VA9D6qowiG4AoDVPgaXWuuZyb2mL+dEPdyss0cu49z6zpQL9riMeIiSE+aeIg69EdVxhYFt99Ws0IIU+lpUn+Ge3K7TFehmDt/gpyv0WyEE5ornjyovG3lJm+diACr/CXxJXuKgwvaY2T
x-ms-exchange-antispam-messagedata: 
 CJcWpwbrbGhS7w+2LvQSFRnFH6s+rQxYvJnmJY0j9baPpYJx0Tdl/A66XRG2/ZzroYfzxOoPbbp95IBjYbFiI058D5DOzHs+rh3cki2g08p0EKHqyLuTPRDvEOudy3Qxo7wx1fERxN5AUd2r+Zo/Kg==
MIME-Version: 1.0
X-OriginatorOrg: wdc.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 c620bad7-dab8-4784-e753-08d7a325776c
X-MS-Exchange-CrossTenant-originalarrivaltime: 27 Jan 2020 12:36:01.1426
 (UTC)
X-MS-Exchange-CrossTenant-fromentityheader: Hosted
X-MS-Exchange-CrossTenant-id: b61c8803-16f3-4c35-9b17-6f65f441df86
X-MS-Exchange-CrossTenant-mailboxtype: HOSTED
X-MS-Exchange-CrossTenant-userprincipalname: 
 QHyYN9dzm1Ey42+kWiVL1O3Tcw1vo2sBGahX6TQdGc5GFc8E+H3WFKSyx+5WfSh+iR5AfuVwfEjjksVAk9zdDQ==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: MN2PR04MB6735
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We sync-up all ABI headers with Linux-5.5-rc3. This will allow
us to use ONE_REG interface for KVMTOOL RISC-V port.

Signed-off-by: Anup Patel <anup.patel@wdc.com>
---
 arm/aarch32/include/asm/kvm.h |  7 +++++--
 arm/aarch64/include/asm/kvm.h |  9 +++++++--
 include/linux/kvm.h           | 25 +++++++++++++++++++++++++
 powerpc/include/asm/kvm.h     |  3 +++
 4 files changed, 40 insertions(+), 4 deletions(-)

```
#### [kvm-unit-tests] x86: Group APIC tests
##### From: Wainer dos Santos Moschetta <wainersm@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wainer dos Santos Moschetta <wainersm@redhat.com>
X-Patchwork-Id: 11353227
Return-Path: <SRS0=3aXV=3Q=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 70EB692A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 27 Jan 2020 20:12:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4F3A42467B
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 27 Jan 2020 20:12:48 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="bsmu97AG"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726099AbgA0UMr (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 27 Jan 2020 15:12:47 -0500
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:41601 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1725975AbgA0UMr (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 27 Jan 2020 15:12:47 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1580155966;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=4ImoCkA2rMAj5OwG4X8CC6lkF8ZqmZqxCa+9EPE6Pdk=;
        b=bsmu97AGWNgo7WXgDMP8NKYXi78JwdQBUKa6eKUeQ3lyuQ/WGOe4arkfEwN28/cYzwVoyE
        j8CjA/m305Ckp8VKYXa8r0AO2Ui6hPfo+qxD0uUqI2VhpRw7GzsdilKxuYiEG8F3JxwWHB
        rAcmj+JjmRdZpj7hcTPAOv2665r8RqU=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-85-Mciqd0yTPUC6CeSuJwxu6Q-1; Mon, 27 Jan 2020 15:12:43 -0500
X-MC-Unique: Mciqd0yTPUC6CeSuJwxu6Q-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id D7107800D48
        for <kvm@vger.kernel.org>; Mon, 27 Jan 2020 20:12:42 +0000 (UTC)
Received: from localhost.localdomain (ovpn-116-27.gru2.redhat.com
 [10.97.116.27])
        by smtp.corp.redhat.com (Postfix) with ESMTP id EED5F8DC35;
        Mon, 27 Jan 2020 20:12:41 +0000 (UTC)
From: Wainer dos Santos Moschetta <wainersm@redhat.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com
Subject: [kvm-unit-tests] x86: Group APIC tests
Date: Mon, 27 Jan 2020 17:12:40 -0300
Message-Id: <20200127201240.6429-1-wainersm@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This creates the 'apic' group in x86/unittests.cfg to allow
the execution of all APIC tests (including IO-APIC) together.

Signed-off-by: Wainer dos Santos Moschetta <wainersm@redhat.com>
---
 x86/unittests.cfg | 4 ++++
 1 file changed, 4 insertions(+)

```
#### [PATCH] KVM: x86: Fix perfctr WRMSR for running countersFrom: Eric Hankland <ehankland@google.com>
##### From: Eric Hankland <ehankland@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Hankland <ehankland@google.com>
X-Patchwork-Id: 11353251
Return-Path: <SRS0=3aXV=3Q=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 676251398
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 27 Jan 2020 21:23:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 459E724679
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 27 Jan 2020 21:23:05 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="nQCoMeg5"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726205AbgA0VXB (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 27 Jan 2020 16:23:01 -0500
Received: from mail-pg1-f202.google.com ([209.85.215.202]:54332 "EHLO
        mail-pg1-f202.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725946AbgA0VXB (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 27 Jan 2020 16:23:01 -0500
Received: by mail-pg1-f202.google.com with SMTP id i21so7267955pgm.21
        for <kvm@vger.kernel.org>; Mon, 27 Jan 2020 13:23:00 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=M7uDook8T4JuFhQPKzSHd/4CKNgbM46H4EUNpVdKl20=;
        b=nQCoMeg5/E+KDXBiPl89mZrX/Kg1XuVS5rl428w6rs8LyHFj8aVDYpYacV9NcKKeEg
         I5vAbvKzZSe21rKyTDluGc9cKcpMpZvjlp/lhl0vvJ6wENBCcWLDosQ0+D9vhuClnUOI
         upl33DmT7LzNNtkcaKyNxk3VTMVFyXpPXQkWxaHFDPqJj+kFbmmzDcjMseirRMpI0gfK
         ah5uQV/ilEnZmwn2oOiwRRuVjHhWnzXvrDjF4LSsOr9bKaZP3HayadlgPM/BAdgn4TI6
         R00A86ey46B9XNod6zeVEXD6N7ebi95rOqgYc410VknfnRFkZ80cF8yTiUZu9KFYK4zV
         wX5A==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=M7uDook8T4JuFhQPKzSHd/4CKNgbM46H4EUNpVdKl20=;
        b=f+5Q+szJ4E8qpBXFq3Y0MkOOGQ8+0rrYXJaSbxmcZUpSMKG0euOIms4dq4RxZkVjCa
         4W3di4WeNzEPSBiD7SFCdZmyVL/0/4wcn8NDyUtOQJGo9COj4a/nTJJEEbEGzgOiNwLN
         7M+zhqpzlEWylygzdwrh1k1V0CUbDojEzCFYvp5YJBvonaikk+qlEazC2kt0PjuRicIc
         SEtubIphEaMzRhWUa89UFJamy60IGN30BnrUWHvTrfy1uBxP5NGzonfOhnWL+0cknI8y
         dd5b9KX8uH4xHsZxVEAxG7Oo2vDzHOWCIYwWyQQFaxB1GME5ovrYidDwbfRn7kr4gqk3
         2veQ==
X-Gm-Message-State: APjAAAXiI1L+01PS5uNfv9XA8hBtSI2aPFtPSi+o0CPQeQ3duw9sesYt
        z/HR1l+mZMaTomi4H5IxK1U5f8RWgc5l7Fo=
X-Google-Smtp-Source: 
 APXvYqztwCCBeFLwUdmvoDFFpxL4zFNAytONdjZTYtHWUot99zcOcBOoTdZdb7LJZVxpMkDMsscdqyNegKD5ym8=
X-Received: by 2002:a63:1756:: with SMTP id 22mr21988920pgx.109.1580160180456;
 Mon, 27 Jan 2020 13:23:00 -0800 (PST)
Date: Mon, 27 Jan 2020 13:22:56 -0800
Message-Id: <20200127212256.194310-1-ehankland@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.25.0.341.g760bfbb309-goog
Subject: [PATCH] KVM: x86: Fix perfctr WRMSR for running counters
From: Eric Hankland <ehankland@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Peter Shier <pshier@google.com>
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        Eric Hankland <ehankland@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Correct the logic in intel_pmu_set_msr() for fixed and general purpose
counters. This was recently changed to set pmc->counter without taking
in to account the value of pmc_read_counter() which will be incorrect if
the counter is currently running and non-zero; this changes back to the
old logic which accounted for the value of currently running counters.

Signed-off-by: Eric Hankland <ehankland@google.com>
---
 arch/x86/kvm/vmx/pmu_intel.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [PATCH] KVM: x86: Unexport x86_fpu_cache and make it static
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11352051
Return-Path: <SRS0=3aXV=3Q=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C2F97139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 27 Jan 2020 00:14:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A10992083E
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 27 Jan 2020 00:14:47 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726922AbgA0ANd (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 26 Jan 2020 19:13:33 -0500
Received: from mga05.intel.com ([192.55.52.43]:22801 "EHLO mga05.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726444AbgA0ANc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 26 Jan 2020 19:13:32 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga006.jf.intel.com ([10.7.209.51])
  by fmsmga105.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 26 Jan 2020 16:13:32 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,367,1574150400";
   d="scan'208";a="231218374"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by orsmga006.jf.intel.com with ESMTP; 26 Jan 2020 16:13:32 -0800
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: x86: Unexport x86_fpu_cache and make it static
Date: Sun, 26 Jan 2020 16:13:30 -0800
Message-Id: <20200127001330.27741-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Make x86_fpu_cache static now that FPU allocation and destruction is
handled entirely by common x86 code.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---

Pretty sure I meant to include this in the vCPU creation cleanup, but
completely forgot about it.

 arch/x86/include/asm/kvm_host.h | 1 -
 arch/x86/kvm/x86.c              | 3 +--
 2 files changed, 1 insertion(+), 3 deletions(-)

```
#### [PATCH 1/3] KVM: x86: Gracefully handle __vmalloc() failure during VM allocation
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11352057
Return-Path: <SRS0=3aXV=3Q=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 20BA214B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 27 Jan 2020 00:41:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 0920920720
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 27 Jan 2020 00:41:31 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728890AbgA0AlZ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 26 Jan 2020 19:41:25 -0500
Received: from mga09.intel.com ([134.134.136.24]:63120 "EHLO mga09.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726654AbgA0AlQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 26 Jan 2020 19:41:16 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by orsmga102.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 26 Jan 2020 16:41:15 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,367,1574150400";
   d="scan'208";a="223116777"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by fmsmga008.fm.intel.com with ESMTP; 26 Jan 2020 16:41:15 -0800
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH 1/3] KVM: x86: Gracefully handle __vmalloc() failure during VM
 allocation
Date: Sun, 26 Jan 2020 16:41:11 -0800
Message-Id: <20200127004113.25615-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20200127004113.25615-1-sean.j.christopherson@intel.com>
References: <20200127004113.25615-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Check the result of __vmalloc() to avoid dereferencing a NULL pointer in
the event that allocation failres.

Fixes: 40bbb9d03f05d ("KVM: VMX: add struct kvm_vmx to hold VMX specific KVM vars")
Fixes: 81811c162d4da ("KVM: SVM: add struct kvm_svm to hold SVM specific KVM vars")
Fixes: d1e5b0e98ea27 ("kvm: Make VM ioctl do valloc for some archs")
Cc: stable@vger.kernel.org
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/svm.c     | 4 ++++
 arch/x86/kvm/vmx/vmx.c | 4 ++++
 2 files changed, 8 insertions(+)

```
#### [PATCH 3/3] KVM: x86: Consolidate VM allocation and free for VMX and SVM
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11352053
Return-Path: <SRS0=3aXV=3Q=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3AB1514B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 27 Jan 2020 00:41:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 177B120720
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 27 Jan 2020 00:41:26 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728266AbgA0AlQ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 26 Jan 2020 19:41:16 -0500
Received: from mga09.intel.com ([134.134.136.24]:63120 "EHLO mga09.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727479AbgA0AlQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 26 Jan 2020 19:41:16 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by orsmga102.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 26 Jan 2020 16:41:15 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,367,1574150400";
   d="scan'208";a="223116783"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by fmsmga008.fm.intel.com with ESMTP; 26 Jan 2020 16:41:15 -0800
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH 3/3] KVM: x86: Consolidate VM allocation and free for VMX and
 SVM
Date: Sun, 26 Jan 2020 16:41:13 -0800
Message-Id: <20200127004113.25615-4-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20200127004113.25615-1-sean.j.christopherson@intel.com>
References: <20200127004113.25615-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Move the VM allocation and free code to common x86 as the logic is
more or less identical across SVM and VMX.

Note, although hyperv.hv_pa_pg is part of the common kvm->arch, it's
(currently) only allocated by VMX VMs.  But, since kfree() plays nice
when passed a NULL pointer, the superfluous call for SVM is harmless
and avoids future churn if SVM gains support for HyperV's direct TLB
flush.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/include/asm/kvm_host.h | 12 ++++--------
 arch/x86/kvm/svm.c              | 13 +++----------
 arch/x86/kvm/vmx/vmx.c          | 14 +++-----------
 arch/x86/kvm/x86.c              |  7 +++++++
 4 files changed, 17 insertions(+), 29 deletions(-)

```
